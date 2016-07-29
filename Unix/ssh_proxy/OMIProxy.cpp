#include <stdio.h>
#include <signal.h>
#include <MI.h>
#include <pal/file.h>
#include <pal/dir.h>
#include <pal/strings.h>
#include <pal/cpu.h>
#include <pal/format.h>
#include <pal/lock.h>
#include <pal/sleep.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <wql/wql.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/instance.h>
#include <base/log.h>
#include <base/result.h>
#include <base/strarr.h>
#include <base/ptrarray.h>
#include <protocol/protocol.h>
#include <xmlserializer/xmlserializer.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static FILE* sout;
static FILE* serr;
const MI_Char* arg0;
static MI_Operation gop = {0, 0, 0};

struct Options
{
    MI_Boolean help;
    MI_Boolean quiet;
    MI_Boolean summary;
    MI_Boolean suppressResults;
    MI_Boolean trace;
    MI_Boolean shallow;
    int repeat;
    const MI_Char *assocClass;
    const MI_Char *resultClass;
    const MI_Char *role;
    const MI_Char *resultRole;
    const MI_Char *auth;
    const MI_Char *user;
    const MI_Char *password;
    MI_Uint64 timeOut;
    const MI_Char *hostname;
    const MI_Char *protocol;
    unsigned int httpport;
    unsigned int httpsport;
    MI_Boolean nulls;
    const MI_Char *querylang;
    const MI_Char *queryexpr;
    MI_Boolean synchronous;
    MI_Boolean xml;
};

typedef struct _ClientReaderArgs
{
    Sock inputPipe;
    Sock outputPipe;
} ClientReaderArgs;

static struct Options opts =
{ MI_FALSE, MI_FALSE, MI_FALSE, MI_FALSE, MI_FALSE, MI_FALSE, 1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 90 * 1000 * 1000, NULL, NULL, CONFIG_HTTPPORT, CONFIG_HTTPSPORT, MI_FALSE, MI_T("wql"), NULL, MI_FALSE };

static void err(const ZChar* fmt, ...)
{
    va_list ap;

    Ftprintf(serr, PAL_T("%T: "), tcs(arg0));

    va_start(ap, fmt);
    Vftprintf(serr, fmt, ap);
    va_end(ap);

    Ftprintf(serr, PAL_T("\n"));
}

static MI_Uint64 s_numInstances = 0;
static ptrdiff_t s_startTime;
static MI_Result s_finalResult = MI_RESULT_FAILED;
static ptrdiff_t s_finished = 0;
static Sock      s_serverSock = -1;

// Find closing brace (assuming *p points to an opening brace).
static const MI_Char** FindClosingBrace(const MI_Char** p)
{
    int nesting = 1;

    if (Tcscmp(*p, MI_T("{")) != 0)
        return NULL;

    p++;

    while (*p)
    {
        if (Tcscmp(*p, MI_T("{")) == 0)
            nesting++;
        else if (Tcscmp(*p, MI_T("}")) == 0)
            nesting--;

        p++;

        if (nesting == 0)
            return p;
    }

    return NULL;
}

static void MI_MAIN_CALL _DeleteInstance(void* inst)
{
    MI_Instance_Delete((MI_Instance*)inst);
}

static MI_Boolean ArgsToInstance(
    const MI_Char*** _p,
    const MI_Char** end,
    MI_Uint32 metaType,
    MI_Boolean key,
    MI_Instance **instanceOut)
{
    MI_Instance *instance;
    MI_Uint32 keyFlag = 0;
    const MI_Char **p = *_p;

    if (key)
        keyFlag = MI_FLAG_KEY;

    if (p == end)
        return MI_FALSE;

    // Consume opening brace:
    if (Tcscmp(*p++, MI_T("{")) != 0)
        return MI_FALSE;

    if (p == end)
        return MI_FALSE;


    if (metaType == MI_FLAG_METHOD)
    {
        if (Instance_NewDynamic(&instance, MI_T("Parameters"), MI_FLAG_METHOD, NULL) != MI_RESULT_OK)
            return MI_FALSE;
    }
    else
    {
        if (Instance_NewDynamic(&instance, *p++, MI_FLAG_CLASS, NULL) != MI_RESULT_OK)
            return MI_FALSE;

        if (p == end)
        {
            MI_Instance_Delete(instance);
            return MI_FALSE;
        }
    }

    // Consume name/value pairs:
    for (;;)
    {
        const MI_Char *name;
        if (Tcscmp(*p, MI_T("}")) == 0)
        {
            p++;
            break;
        }

        // Get name:
        name = *p++;

        if (p == end)
        {
            MI_Instance_Delete(instance);
            return MI_FALSE;
        }

        // Get value:
        if (Tcscmp(*p, MI_T("{")) == 0)
        {
            const MI_Char** q = FindClosingBrace(p);
            MI_Instance *tmpInst;
            MI_Value value;

            if (!q || q == end)
            {
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }

            // Recursively call to obtain reference or embedded instance.

            if (!ArgsToInstance(&p, q, MI_FLAG_CLASS, key, &tmpInst))
            {
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }

            value.instance = tmpInst;
            if (MI_Instance_AddElement(instance, name, &value, MI_INSTANCE, keyFlag | MI_FLAG_ADOPT) != MI_RESULT_OK)
                //!instance.AddInstance(name, tmpInst, MI_FALSE, key))
            {
                MI_Instance_Delete(tmpInst);
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }
        }
        else if (Tcscmp(*p, MI_T("[")) == 0)
        {
            MI_Char** strArray = ZArr();
            PtrArray instanceArray;

            if (strArray == NULL)
            {
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }
            if (PtrArray_Construct(&instanceArray, 5, _DeleteInstance) != 0)
            {
                ZArrFree(strArray);
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }

            p++;

            // Find closing brace:
            while (*p && Tcscmp(*p, MI_T("]")) != 0)
            {
                if (Tcscmp(*p, MI_T("{")) == 0)
                {
                    const MI_Char** q = FindClosingBrace(p);
                    MI_Instance *tmpInst = NULL;

                    if (!q || q == end)
                    {
                        if (strArray)
                        {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                            ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                        }
                        PtrArray_Destruct(&instanceArray);
                        MI_Instance_Delete(instance);
                        return MI_FALSE;
                    }

                    if (!ArgsToInstance(&p, q, MI_FLAG_CLASS, key, &tmpInst))
                    {
                        if (strArray)
                        {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                            ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                        }
                        PtrArray_Destruct(&instanceArray);
                        MI_Instance_Delete(instance);
                        return MI_FALSE;
                    }
                    if (PtrArray_Append(&instanceArray, tmpInst) != 0)
                    {
                        if (strArray)
                        {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                            ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                        }
                        PtrArray_Destruct(&instanceArray);
                        MI_Instance_Delete(instance);
                        MI_Instance_Delete(tmpInst);
                        return MI_FALSE;
                    }
                }
                else
                {
                    MI_Char **_strArray = strArray;
                    ZArrCat(&_strArray, *p++);
                    if (_strArray == NULL)
                    {
                        /* Failed */
                        if (strArray)
                        {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                            ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                        }
                        PtrArray_Destruct(&instanceArray);
                        MI_Instance_Delete(instance);
                        return MI_FALSE;
                    }
                    strArray = _strArray;
                }
            }

            // Handle missing closing brace:
            if (p == end)
            {
                if (strArray)
                {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                    ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                }
                PtrArray_Destruct(&instanceArray);
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }

            if (instanceArray.size)
            {
                MI_Value value;
                MI_Uint32 flags = 0;
                value.instancea.data = (MI_Instance**) instanceArray.data;
                value.instancea.size = instanceArray.size;
                if (key)
                    flags = MI_FLAG_KEY;

                if (MI_Instance_AddElement(instance, name, &value, MI_INSTANCEA, flags) != MI_RESULT_OK)
                {
                    if (strArray)
                    {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                        ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                    }
                    PtrArray_Destruct(&instanceArray);
                    MI_Instance_Delete(instance);
                    return MI_FALSE;
                }
            }
            else
            {
                MI_Uint32 arrLength = ZArrLen(strArray);
                if (arrLength)
                {
                    MI_Value value;
                    MI_Uint32 flags = 0;
                    value.stringa.data = strArray;
                    value.stringa.size = arrLength;
                    if (key)
                        flags = MI_FLAG_KEY;

                    if (MI_Instance_AddElement(instance, name, &value, MI_STRINGA, flags) != MI_RESULT_OK)
                    {
                        if (strArray)
                        {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                            ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
                        }
                        PtrArray_Destruct(&instanceArray);
                        MI_Instance_Delete(instance);
                        return MI_FALSE;
                    }
                }
            }

            if (strArray)
            {
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26018)
#endif
                ZArrFree(strArray);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
            }
            PtrArray_Destruct(&instanceArray);
            p++;
        }
        else
        {
            MI_Value value;

            value.string = (MI_Char *)*p++;

            // Add property:
            if (MI_Instance_AddElement(instance, name, &value, MI_STRING, keyFlag | MI_FLAG_BORROW) != MI_RESULT_OK)
            {
                MI_Instance_Delete(instance);
                return MI_FALSE;
            }

            if (p == end)
                break;
        }
    }

    *_p = p;
    *instanceOut = instance;
    return MI_TRUE;
}

MI_Result CreateOperationOptions(_Inout_ MI_Session *session, _Out_ MI_OperationOptions *options)
{
    MI_Application application;
    MI_Result miResult;
    MI_Interval timeoutInterval;
    MI_Uint64 currentTimeout = opts.timeOut;


    miResult = MI_Session_GetApplication(session, &application);
    if (miResult != MI_RESULT_OK)
        return miResult;

    miResult = MI_Application_NewOperationOptions(&application, MI_FALSE, options);
    if (miResult != MI_RESULT_OK)
        return miResult;

    memset(&timeoutInterval, 0, sizeof(timeoutInterval));

    timeoutInterval.microseconds = currentTimeout % 1000000;
    currentTimeout /= 1000000;

    timeoutInterval.seconds = currentTimeout % 60;
    currentTimeout /= 60;

    timeoutInterval.minutes = currentTimeout % 60;
    currentTimeout /= 60;

    timeoutInterval.hours = currentTimeout % 24;
    currentTimeout /= 24;

    timeoutInterval.days = (MI_Uint32) currentTimeout;

    miResult = MI_OperationOptions_SetTimeout(options, &timeoutInterval);
    if (miResult != MI_RESULT_OK)
    {
        goto cleanup;
    }

    return miResult;

cleanup:
    MI_OperationOptions_Delete(options);
    memset(options, 0, sizeof(*options));
    return miResult;
}

void MI_CALL InstanceResults(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (instance)
    {
        s_numInstances++;

        if (!opts.quiet)
        {
            Instance_Print(instance, sout, 0, opts.nulls, MI_FALSE);
        }
    }

    if (moreResults == MI_FALSE)
    {
        if (resultCode != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(PAL_T("result: %T"), tcs(Result_ToString(resultCode)));
                if (errorString)
                {
                    err(PAL_T("result: %T"), tcs(errorString));
                }
                if (errorDetails)
                {
                    Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                }
            }
        }
        s_finalResult = resultCode;
        s_finished = 1;
        CondLock_Broadcast((ptrdiff_t)callbackContext);
    }
}

void MI_CALL IndicationResult(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
    _In_opt_z_ const MI_Char *bookmark,
    _In_opt_z_ const MI_Char *machineID,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (instance)
    {
        s_numInstances++;

        if (!opts.quiet)
        {
            Ftprintf(sout, PAL_T("Async subscribe. Bookmark: %T; MachineID: %T\n"), tcs(bookmark), tcs(machineID));
            Instance_Print(instance, sout, 0, opts.nulls, MI_FALSE);
        }
    }

    if (moreResults == MI_FALSE)
    {
        if (resultCode != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(PAL_T("result: %T"), tcs(Result_ToString(resultCode)));
                if (errorString)
                {
                    err(PAL_T("result: %T"), tcs(errorString));
                }
                if (errorDetails)
                {
                    Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                }
            }
        }
        s_finalResult = resultCode;
        s_finished = 1;
        CondLock_Broadcast((ptrdiff_t)callbackContext);
    }
}

static MI_Result ConsumeInstanceResults( MI_Operation *miOperation, Sock *serverSock)
{
    MI_Result miResult;
    ptrdiff_t finished;
    
    finished = s_finished;
    while (!finished)
    {
        CondLock_Wait((ptrdiff_t)&s_finished, &s_finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
        finished = s_finished;
    }
    miResult = s_finalResult;
    *serverSock = s_serverSock;

    return miResult;
}

void MI_CALL ClassResults(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Class *classObject,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (classObject)
    {
        s_numInstances++;

        if (!opts.quiet)
        {
            MI_Instance *instance;
            if (Instance_New(&instance, classObject->classDecl, NULL) == MI_RESULT_OK)
            {
                Instance_Print(instance, sout, 0, MI_TRUE, MI_TRUE);

                MI_Instance_Delete(instance);
            }
        }
    }

    if (moreResults == MI_FALSE)
    {
        if (resultCode != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(PAL_T("result: %T"), tcs(Result_ToString(resultCode)));
                if (errorString)
                {
                    err(PAL_T("result: %T"), tcs(errorString));
                }
                if (errorDetails)
                {
                    Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                }
            }
        }
        s_finalResult = resultCode;
        s_finished = 1;
        CondLock_Broadcast((ptrdiff_t)callbackContext);
    }
}

void MI_CALL NoOpResults(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (instance)
    {
        s_numInstances++;

        if (!opts.quiet)
        {
            Instance_Print(instance, sout, 0, opts.nulls, MI_FALSE);
        }
    }

    if (moreResults == MI_FALSE)
    {
        if (resultCode != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(PAL_T("result: %T"), tcs(Result_ToString(resultCode)));
                if (errorString)
                {
                    err(PAL_T("result: %T"), tcs(errorString));
                }
                if (errorDetails)
                {
                    Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                }
            }
        }
        else
        {
            Ftprintf(sout, PAL_T("got noop response\n"));

        }
        s_finalResult = resultCode;
        s_finished = 1;
        CondLock_Broadcast((ptrdiff_t)callbackContext);
    }
}

void MI_CALL SwitchProtocolResults(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_     Sock newSock,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (moreResults == MI_FALSE)
    {
        if (resultCode != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(PAL_T("result: %T"), tcs(Result_ToString(resultCode)));
                if (errorString)
                {
                    err(PAL_T("result: %T"), tcs(errorString));
                }
                if (errorDetails)
                {
                    Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                }
            }
        }
        else
        {
            Ftprintf(sout, PAL_T("got SwitchProtocol response\n"));

        }
        s_finalResult = resultCode;
        s_finished = 1;
        s_serverSock = newSock;
        CondLock_Broadcast((ptrdiff_t)callbackContext);
    }
}


static MI_Result SwitchProtocol(MI_Session *miSession, Sock *serverSock, int argc, const MI_Char* argv [])
{
    MI_Result miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Uint32 flags = 0;

    MI_UNUSED(argv);

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.switchProtocolResult = SwitchProtocolResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    MI_Session_SwitchProtocols(miSession, flags, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation, serverSock);

    MI_Operation_Close(&miOperation);

    return miResult;
}

static MI_Result FindConfigFile(_Pre_writable_size_(PAL_MAX_PATH_SIZE) char path[PAL_MAX_PATH_SIZE])
{
    char* home;
    /* Look in current directory */
    {
        Strlcpy(path, "./.omiclirc", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return MI_RESULT_OK;
    }

    /* Look in HOME directory */
    home = getenv("HOME");
    if (home)
    {
        Strlcpy(path, home, PAL_MAX_PATH_SIZE);
        Strlcat(path, "/.omiclirc", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
        {
            return MI_RESULT_OK;
        }
    }

    /* Look in system config directory */
    {
        Strlcpy(path, OMI_GetPath(ID_SYSCONFDIR), PAL_MAX_PATH_SIZE);
        Strlcat(path, "/omicli.conf", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return MI_RESULT_OK;
    }

    /* Not found */
    return MI_RESULT_FAILED;
}

static MI_Result GetConfigFileOptions()
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;
    MI_Result miResult = MI_RESULT_OK;

    /* Form the configuration file path (silently ignore if not found) */
    if (FindConfigFile(path) != 0)
        return MI_RESULT_OK;

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        err(PAL_T("failed to open configuration file: %s"), scs(path));
        return MI_RESULT_FAILED;
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            err(PAL_T("%s: %s\n"), scs(path), scs(Conf_Error(conf)));
            miResult = MI_RESULT_FAILED;
            goto cleanup;
        }

        if (r == 1)
            break;

        if (strcmp(key, "httpport") == 0)
        {
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(PAL_T("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                miResult = MI_RESULT_FAILED;
                goto cleanup;
            }

            opts.httpport = (unsigned short)x;
        }
        else if (strcmp(key, "httpsport") == 0)
        {
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(PAL_T("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                miResult = MI_RESULT_FAILED;
                goto cleanup;
            }

            opts.httpsport = (unsigned short)x;
        }
        else if (strcmp(key, "trace") == 0)
        {
            if (Strcasecmp(value, "MI_TRUE") == 0)
            {
                opts.trace = MI_TRUE;
            }
            else if (Strcasecmp(value, "MI_FALSE") == 0)
            {
                opts.trace = MI_FALSE;
            }
            else
            {
                err(PAL_T("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                miResult = MI_RESULT_FAILED;
                goto cleanup;
            }
        }
        else if (strcmp(key, "protocolhandler") == 0)
        {
            /* This is used in the miapi itself */
        }
        if (strcmp(key, "loglevel") == 0)
        {
            if (Log_SetLevelFromString(value) != 0)
            {
                err(PAL_T("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                miResult = MI_RESULT_FAILED;
                goto cleanup;
            }
        }
        else if (strcmp(key, "logpath") == 0)
        {
            /* TODO - this is just a test tool? */
        }
        else if (strcmp(key, "logfile") == 0)
        {
            /* TODO - this is just a test tool? */
        }
        else if (IsNickname(key))
        {
            if (SetPathFromNickname(key, value) != 0)
            {
                err(PAL_T("SetPathFromNickname() failed"));
                miResult = MI_RESULT_FAILED;
                goto cleanup;
            }
        }
        else
        {
            err(PAL_T("%s(%u): unknown key: %s"), scs(path), Conf_Line(conf),
                scs(key));
            miResult = MI_RESULT_FAILED;
            goto cleanup;
        }
    }

cleanup:
    /* Close configuration file */
    Conf_Close(conf);
    return miResult;
}

#define GETOPTSTATE_INITIALIZER { 0, { '\0' }, NULL, { '\0' } }
#define GETOPT_OPT_SIZE 512
#define GETOPT_ERR_SIZE 512

typedef struct _GetOptState
{
    int index;
    MI_Char opt[GETOPT_OPT_SIZE];
    const MI_Char* arg;
    MI_Char err[GETOPT_ERR_SIZE];
}
GetOptState;

/*
 * Signal handler that catch SIGINT signal, the signal
 * is triggered by CTRL+C from console; In case of
 * SIGINT signal, need to cancel the active operation
 * and exit
 *
 */
void MI_MAIN_CALL SignalHandler(int signo)
{
    err(PAL_T("Quit program upon receiving ctrl+c"), signo);
    if (gop.ft)
    {
        if (s_finished == 0)
        {
            s_finished = 1;
            CondLock_Broadcast((ptrdiff_t)(&s_finished));
        }

        Ftprintf(sout, MI_T("Cancel the operation"));
        MI_Operation_Cancel(&gop, MI_REASON_SHUTDOWN);
        /* Close opeartion will be unresponsive due to */
        /* the operation is not get final result yet */
        /* need to enable this code after end to end cancel was completed */
        /* MI_Operation_Close(&gop); */
        /* Ftprintf(sout, MI_T("Closed the operation")); */
        Sleep_Milliseconds(200);
    }
    exit(1);
}

/*
 * Set up signal handler to catch SIGINT signal
 *
 */
void CatchCtrlC()
{
    if (signal(SIGINT, SignalHandler) == SIG_ERR)
        err(PAL_T("cannot catch signal: SIGINT\n"));
}

MI_Result SendChangeProtocol(int argc, const char **argv, Sock *serverSock)
{
    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_Session miSession = MI_SESSION_NULL;
    MI_Result miResult;
    MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_DestinationOptions *miDestinationOptions = NULL;
    MI_UserCredentials miUserCredentials = {0};

    /*Log_OpenStdErr();
    Log_SetLevel(LOG_VERBOSE);*/
    CatchCtrlC();

    // Setup default stderr and stdout streams:
    serr = stderr;
    sout = stdout;

    arg0 = argv[0];

    // const MI_Uint64 CONNECT_TIMEOUT_USEC = 10 * 1000 * 1000;

    // Get configuration file options:
    miResult = GetConfigFileOptions();
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }

    miResult = MI_Application_Initialize(0, NULL, NULL, &miApplication);
    if (miResult != MI_RESULT_OK)
        return miResult;
    if (opts.user)
    {
        miDestinationOptions = &_miDestinationOptions;
        miResult = MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions);
        if (miResult != MI_RESULT_OK)
            goto CleanupApplication;

        if (opts.auth)
        {
            miUserCredentials.authenticationType = opts.auth;
        }
        else
        {
            miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
        }
        if (opts.hostname)
        {
            miUserCredentials.credentials.usernamePassword.domain = opts.hostname;
        }
        else
        {
            miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
        }
        miUserCredentials.credentials.usernamePassword.username = opts.user;
        miUserCredentials.credentials.usernamePassword.password = opts.password;

        miResult = MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials);
        if (miResult != MI_RESULT_OK)
            goto CleanupApplication;
    }

    miResult = MI_Application_NewSession(&miApplication, opts.protocol, opts.hostname, miDestinationOptions, NULL, NULL, &miSession);
    if (miResult != MI_RESULT_OK)
    {
        if (opts.hostname)
        {
            Ftprintf(sout, tcs(MI_T("omicli: Failed to create session to %T\n")), opts.hostname);
        }
        else
        {
            Ftprintf(sout, tcs(MI_T("omicli: Failed to create session to %T\n")), MI_T("local machine"));
        }
        goto CleanupApplication;
    }

    // Remember start time (will calculate total time in PrintSummary()
    s_startTime = CPU_GetTimeStamp();

    miResult = SwitchProtocol(&miSession, serverSock, argc, argv);
    if (miResult != MI_RESULT_OK)
        goto CleanupSession;

    printf("Switch Protocol Complete.  New server socket is %d.\n", *serverSock);

CleanupSession:
    MI_Session_Close(&miSession, NULL, NULL);

CleanupApplication:
    if (miDestinationOptions)
        MI_DestinationOptions_Delete(miDestinationOptions);

    MI_Application_Close(&miApplication);

    if (sout != stdout)
        fclose(sout);

    if (serr != stdout)
        fclose(serr);

    return miResult;
}

static void *ReaderWriter(void *args)
{
    fd_set myFdSet;
    char input[1024];
    int numBytes = 0;
    int numSel;
    struct timeval timeOut;
    timeOut.tv_sec = 5;
    timeOut.tv_usec = 0;
    int inputPipe;
    int outputPipe;
    char *RetSuccess;
    char *RetFailure;

    ClientReaderArgs *clientReaderArgs = (ClientReaderArgs *)args;

    inputPipe  = clientReaderArgs->inputPipe;
    outputPipe = clientReaderArgs->outputPipe;

    free(args);

    RetFailure = strdup("Failure");

    memset(input, 0, 1024);
    FD_ZERO(&myFdSet);
    FD_SET(inputPipe, &myFdSet);
    while ((numSel = select(inputPipe + 1, &myFdSet, NULL, NULL, &timeOut)) >= 0)
    {
        if (numSel > 0)
        {
            while ((numBytes = read(inputPipe, input, 1024)) > 0)
            {
                // Got something in -- now send it to the other side
                FD_ZERO(&myFdSet);
                FD_SET(outputPipe, &myFdSet);
                if ((numSel = select(outputPipe + 1, NULL, &myFdSet, NULL, &timeOut)) > 0)
                {
                    numBytes = write(outputPipe, input, numBytes);

                    if (numBytes < 0)
                    {
                        return RetFailure;
                    }
                }
                else if (numSel < 0)
                {
                    return RetFailure;
                }
            }

            // All input read and sent.  Terminate.
            break;
        }
    }

    if (numBytes < 0)
    {
        return RetFailure;
    }

    free(RetFailure);
    RetSuccess = strdup("Success");

    // Return on socket error.  This is most likely the socket closing
    return RetSuccess;
}

int main(int argc, const MI_Char* argv[])
{
    Sock serverSock;
    int inputPipe;
    int outputPipe;
    int i;

    static char *ServerOutOfMemory = "Server is out of memory\n";
    static char *ServerCannotInitThread = "Server unable to initialize IO threads\n";
    static char *ServerCannotCreateThread = "Server unable to create IO threads\n";

    ClientReaderArgs *clientReaderArgs;
    pthread_attr_t threadAttr;
    pthread_t *newReaderThread;
    pthread_t *clientReaderThread;
    pthread_t *serverReaderThread;
    void      *clientRes;
    void      *serverRes;

    if (MI_RESULT_OK != SendChangeProtocol(argc, argv, &serverSock))
    {
        printf("Unable to contact OMI server.  Is it running?\n");
        exit(-1);
    }

    printf("Contacted OMI server on socket %d.  Looking for a little read now...\n", serverSock);

    inputPipe = dup(0);
    outputPipe = dup(1);
    close(0);
    close(1);

    // Launch threads for reading from the client/writing to the server, and reading from
    // the server/writing to the client
    for (i = 0; i < 2; i++)
    {
        clientReaderArgs = (ClientReaderArgs *)malloc(sizeof(ClientReaderArgs));
        if (NULL == clientReaderArgs)
        {
            write(outputPipe, ServerOutOfMemory, strlen(ServerOutOfMemory));
            exit(-1);
        }
    
        // Assign the input and output channels.  Switch for the two sides
        clientReaderArgs->inputPipe = inputPipe;
        clientReaderArgs->outputPipe = serverSock;
        if (i%2 == 0)
        {
            clientReaderArgs->inputPipe = serverSock;
            clientReaderArgs->outputPipe = outputPipe;
        }
         
        if (0 != pthread_attr_init(&threadAttr))
        {
            write(outputPipe, ServerCannotInitThread, strlen(ServerCannotInitThread));
            exit(-1);
        } 

        newReaderThread = (pthread_t *)malloc(sizeof(pthread_t));
        if (0 != pthread_create(newReaderThread, &threadAttr, ReaderWriter, clientReaderArgs))
        {
            write(outputPipe, ServerCannotCreateThread, strlen(ServerCannotCreateThread));
            exit(-1);
        }

        if (i%2 == 0)
        {
            clientReaderThread = newReaderThread;
        }
        else
        {
            serverReaderThread = newReaderThread;
        }

        pthread_attr_destroy(&threadAttr);
    }

    // Wait for the threads to complete
    pthread_join(*clientReaderThread, &clientRes);
    pthread_join(*serverReaderThread, &serverRes);

    free(clientRes);
    free(serverRes);

    exit(0);
}
