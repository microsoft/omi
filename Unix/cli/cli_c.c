/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

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
#include <xmlserializer/xmlserializer.h>

static MI_Boolean ArgsToInstance(
    const MI_Char*** _p,
    const MI_Char** end,
    MI_Uint32 metaType,
    MI_Boolean key,
    MI_Instance **instanceOut);

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

static void PrintSummary()
{
    ptrdiff_t now = CPU_GetTimeStamp();
    MI_Uint64 msec = (now - s_startTime) / 1000;
    MI_Real64 seconds = (MI_Real64)msec / (MI_Real64)1000.0;

    Tprintf(PAL_T("number of instances: %u\n"), s_numInstances);
    Tprintf(PAL_T("seconds: %.3lf\n"), seconds);
    Tprintf(PAL_T("instances per second: %.3lf\n"), s_numInstances / seconds);
    Tprintf(PAL_T("\n"));
}

static MI_Result Encode(int argc, const MI_Char* argv[])
{
    MI_Instance *inst;
    if (argc < 3)
    {
        Ftprintf(serr, PAL_T("Usage: %s noop CLASSNAME KEYBINDING\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    argc -= 2;
    argv += 2;

    if (!ArgsToInstance(&argv, argv + argc, MI_FLAG_CLASS, MI_FALSE, &inst))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!opts.quiet)
    {
        Instance_Print(inst, sout, 0, opts.nulls, MI_FALSE);
    }

    MI_Instance_Delete(inst);

    s_numInstances++;

    return MI_RESULT_OK;
}



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

static MI_Result ConsumeInstanceResults(MI_Operation *miOperation)
{
    MI_Result miResult;
    const MI_Uint32 c_initBufferLength = 10000;

    if (opts.synchronous == MI_TRUE)
    {
        MI_Boolean moreResults = MI_FALSE;
        do
        {
            const MI_Instance *miInstanceResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;

            _miResult = MI_Operation_GetInstance(miOperation, &miInstanceResult, &moreResults, &miResult, &errorString, &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }
            if (miInstanceResult)
            {
                s_numInstances++;

                if (!opts.quiet)
                {
                    if (opts.xml == MI_TRUE)
                    {
                        MI_Application application;
                        MI_Serializer serializer;
                        MI_Uint8 *clientBuffer;
                        MI_Uint32 clientBufferLength = c_initBufferLength;
                        MI_Uint32 clientBufferNeeded = 0;
                        clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
                        MI_Application_Initialize(0,NULL,NULL, &application);
                        miResult = XmlSerializer_Create(&application, 0, MI_T("MI_XML"), &serializer);
                        if (miResult != MI_RESULT_OK)
                        {
                            MI_Application_Close(&application);
                            return miResult;
                        }

                        miResult = XmlSerializer_SerializeInstance( &serializer, 0, miInstanceResult, clientBuffer, clientBufferLength, &clientBufferNeeded);
                        if (miResult != MI_RESULT_OK)
                        {
                            free(clientBuffer);
                            if (clientBufferNeeded > 0)
                            {
                                // Try again with a buffer given to us by the clientBufferNeeded field
                                clientBufferLength = clientBufferNeeded;
                                clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
                                miResult = XmlSerializer_SerializeInstance( &serializer, 0, miInstanceResult, clientBuffer, clientBufferLength, &clientBufferNeeded);
                            }
                            else
                            {
                                XmlSerializer_Close(&serializer);
                                MI_Application_Close(&application);
                                return miResult;
                            }
                        }

                        XmlSerializer_Close(&serializer);
                        MI_Application_Close(&application);
                        if (miResult == MI_RESULT_OK)
                        {
                            clientBuffer[clientBufferNeeded] = '\0';
                            printf("%s", (char*)clientBuffer);
                        }
                        free(clientBuffer);
                    }
                    else
                    {
                        Instance_Print(miInstanceResult, sout, 0, opts.nulls, MI_FALSE);
                    }
                }
            }

            if (moreResults == MI_FALSE)
            {
                if (miResult != MI_RESULT_OK)
                {
                    if (!opts.suppressResults)
                    {
                        err(PAL_T("result: %T"), tcs(Result_ToString(miResult)));
                        if (errorString)
                        {
                            err(PAL_T("result: %T"), tcs(errorString));
                        }
                        if (errorDetails)
                        {

                            if (opts.xml == MI_TRUE)
                            {
                                MI_Application application;
                                MI_Serializer serializer;
                                MI_Uint8 *clientBuffer;
                                MI_Uint32 clientBufferLength = c_initBufferLength;
                                MI_Uint32 clientBufferNeeded = 0;
                                clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
                                MI_Application_Initialize(0,NULL,NULL, &application);
                                miResult = XmlSerializer_Create(&application, 0, MI_T("MI_XML"), &serializer);
                                if (miResult != MI_RESULT_OK)
                                {
                                    MI_Application_Close(&application);
                                    return miResult;
                                }
                                miResult = XmlSerializer_SerializeInstance( &serializer, 0, miInstanceResult, clientBuffer, clientBufferLength, &clientBufferNeeded);
                                if (miResult != MI_RESULT_OK)
                                {
                                    free(clientBuffer);
                                    if (clientBufferNeeded > 0)
                                    {
                                        // Try again with a buffer given to us by the clientBufferNeeded field
                                        clientBufferLength = clientBufferNeeded;
                                        clientBuffer = (MI_Uint8*)malloc(clientBufferLength + 1);
                                        miResult = XmlSerializer_SerializeInstance( &serializer, 0, miInstanceResult, clientBuffer, clientBufferLength, &clientBufferNeeded);
                                    }
                                    else
                                    {
                                        XmlSerializer_Close(&serializer);
                                        MI_Application_Close(&application);
                                        return miResult;
                                    }
                                }

                                XmlSerializer_Close(&serializer);
                                MI_Application_Close(&application);
                                if (miResult == MI_RESULT_OK)
                                {
                                    clientBuffer[clientBufferNeeded] = '\0';
                                    printf("%s", (char*)clientBuffer);
                                }
                                free(clientBuffer);
                            }
                            else
                            {
                                Instance_Print(errorDetails, sout, 0, opts.nulls, MI_FALSE);
                            }
                        }
                    }
                }
                s_finalResult = miResult;
                s_finished = 1;
            }

        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = s_finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&s_finished, &s_finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = s_finished;
        }
        miResult = s_finalResult;
    }

    return miResult;
}


static MI_Result ConsumeIndicationsResults(MI_Operation *miOperation)
{
    MI_Result miResult;

    if (opts.synchronous == MI_TRUE)
    {
        MI_Boolean moreResults = MI_FALSE;
        do
        {
            const MI_Instance *miInstanceResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;
            const MI_Char *bookmark;
            const MI_Char *machineid;

            _miResult = MI_Operation_GetIndication(miOperation, &miInstanceResult, &bookmark, &machineid, &moreResults, &miResult, &errorString, &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }

            if (miInstanceResult)
            {
                s_numInstances++;

                if (!opts.quiet)
                {
                    Ftprintf(sout, PAL_T("Sync subscribe. Bookmark: %T; MachineID: %T\n"), tcs(bookmark), tcs(machineid));
                    Instance_Print(miInstanceResult, sout, 0, opts.nulls, MI_FALSE);
                }
            }

            if (moreResults == MI_FALSE)
            {
                if (miResult != MI_RESULT_OK)
                {
                    if (!opts.suppressResults)
                    {
                        err(PAL_T("result: %T"), tcs(Result_ToString(miResult)));
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
                s_finalResult = miResult;
                s_finished = 1;
            }

        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = s_finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&s_finished, &s_finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = s_finished;
        }
        miResult = s_finalResult;
    }

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

static MI_Result ConsumeClassResults(MI_Operation *miOperation)
{
    MI_Result miResult;

    if (opts.synchronous == MI_TRUE)
    {
        MI_Boolean moreResults = MI_FALSE;
        do
        {
            const MI_Class *miClassResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;

            _miResult = MI_Operation_GetClass(miOperation, &miClassResult, &moreResults, &miResult, &errorString, &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }
            if (miClassResult)
            {
                s_numInstances++;

                if (!opts.quiet)
                {
                    MI_Instance *instance;
                    if (Instance_New(&instance, miClassResult->classDecl, NULL) == MI_RESULT_OK)
                    {
                        Instance_Print(instance, sout, 0, MI_TRUE, MI_TRUE);

                        MI_Instance_Delete(instance);
                    }
                }
            }

            if (moreResults == MI_FALSE)
            {
                if (miResult != MI_RESULT_OK)
                {
                    if (!opts.suppressResults)
                    {
                        err(PAL_T("result: %T"), tcs(Result_ToString(miResult)));
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
                s_finalResult = miResult;
                s_finished = 1;
            }

        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = s_finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&s_finished, &s_finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = s_finished;
        }
        miResult = s_finalResult;
    }

    return miResult;
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


static MI_Result NoOp(MI_Session *miSession, int argc, const MI_Char* argv [])
{
    MI_Result miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Uint32 flags = 0;

    MI_UNUSED(argv);

    if (argc != 2)
    {
        Ftprintf(serr, MI_T("Usage: %s noop\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = NoOpResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    MI_Session_TestConnection(miSession, flags, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    return miResult;
}

static MI_Result EnumerateInstances(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Uint32 flags = 0;

    if (argc != 4)
    {
        Ftprintf(serr, MI_T("Usage: %s ei NAMESPACE CLASSNAME\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.shallow)
    {
        flags = MI_OPERATIONFLAGS_POLYMORPHISM_SHALLOW;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_EnumerateInstances(miSession, flags, &miOperationOptions, argv[2], argv[3], MI_FALSE, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result QueryInstances(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;

    if (argc != 4)
    {
        Ftprintf(serr, MI_T("Usage: %s ei NAMESPACE CLASSNAME\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_QueryInstances(miSession, 0, &miOperationOptions, argv[2], opts.querylang, opts.queryexpr, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result Query(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    const MI_Char* dialect = NULL;

    if (argc != 4)
    {
        Ftprintf(serr, PAL_T("Usage: %T %T NAMESPACE QUERY\n\n"), tcs(arg0),
            tcs(argv[1]));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    // Determine query dialect:
    if (Tcscmp(argv[1], MI_T("wql")) == 0)
    {
        dialect = MI_T("WQL");
    }
    else if (Tcscmp(argv[1], MI_T("cql")) == 0)
    {
        dialect = MI_T("CQL");
    }
    else
    {
        err(MI_T("invalid query dialect: %T"), tcs(argv[1]));
    }

    // Extract query options.
    opts.queryexpr = argv[3];

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_QueryInstances(miSession, 0, &miOperationOptions, argv[2], dialect, argv[3], callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result GetInstance(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %s gi NAMESPACE INSTANCENAME\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(MI_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(MI_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }


    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_GetInstance(miSession, 0, &miOperationOptions, nameSpace, instance, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}


static MI_Result CreateInstance(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %s ci NAMESPACE INSTANCE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(PAL_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_CreateInstance(miSession, 0, &miOperationOptions, nameSpace, instance, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;

}

static MI_Result ModifyInstance(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %s mi NAMESPACE INSTANCE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(PAL_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_ModifyInstance(miSession, 0, &miOperationOptions, nameSpace, instance, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;

}

static MI_Result DeleteInstance(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %s di NAMESPACE INSTANCE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(PAL_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_DeleteInstance(miSession, 0, &miOperationOptions, nameSpace, instance, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;

}

static MI_Result Associators(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %s a NAMESPACE INSTANCE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(PAL_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_AssociatorInstances(miSession, 0, &miOperationOptions, nameSpace, instance, opts.assocClass, opts.resultClass, opts.role, opts.resultRole, MI_FALSE, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result References(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    const MI_Char *nameSpace;
    const MI_Char** p;
    const MI_Char** end;

    if (argc < 4)
    {
        Ftprintf(serr, MI_T("Usage: %T d NAMESPACE INSTANCE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p != end)
    {
        err(PAL_T("extraneous arguments after instance name"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_ReferenceInstances(miSession, 0, &miOperationOptions, nameSpace, instance, opts.resultClass, opts.role, MI_FALSE, callbacks, &miOperation);

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result Invoke(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    MI_Instance *instance;
    MI_Instance *inParams = NULL;
    const MI_Char *nameSpace;
    const MI_Char *methodName;
    const MI_Char** p;
    const MI_Char** end;
    MI_Uint32 elementCount = 0;

    if (argc < 5)
    {
        Ftprintf(serr,
            PAL_T("Usage: %s iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\n"),
            tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    argc -= 3;
    argv += 3;
    p = argv;
    end = p + argc;

    if (!ArgsToInstance(&p, end, MI_FLAG_CLASS, MI_TRUE, &instance))
    {
        err(PAL_T("invalid instance name specification"));
        return MI_RESULT_FAILED;
    }

    if (p == end)
    {
        err(PAL_T("expected method name"));
        MI_Instance_Delete(instance);
        return MI_RESULT_INVALID_PARAMETER;
    }

    methodName = *p;
    p++;

    if (p != end)
    {
        if (!ArgsToInstance(&p, end, MI_FLAG_METHOD, MI_TRUE, &inParams))
        {
            err(PAL_T("invalid instance name specification"));
            MI_Instance_Delete(instance);
            return MI_RESULT_FAILED;
        }
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.instanceResult = InstanceResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    if (MI_Instance_GetElementCount(instance, &elementCount) != MI_RESULT_OK)
    {
        err(PAL_T("Failed to get element count for instance"));
        MI_Instance_Delete(instance);
        MI_Instance_Delete(inParams);
        return MI_RESULT_FAILED;
    }

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
    {
        MI_Instance_Delete(instance);
        MI_Instance_Delete(inParams);
        return miResult;
    }

    if (elementCount)
    {
        MI_Session_Invoke(miSession, 0, NULL, nameSpace, instance->classDecl->name, methodName, instance, inParams, callbacks, &miOperation);
    }
    else
    {
        /* Static method */
        MI_Session_Invoke(miSession, 0, &miOperationOptions, nameSpace, instance->classDecl->name, methodName, NULL, inParams, callbacks, &miOperation);
    }

    miResult = ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_Instance_Delete(instance);
    if (inParams)
        MI_Instance_Delete(inParams);
    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result GetClass(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    const MI_Char *nameSpace;
    const MI_Char *className;

    if (argc != 4)
    {
        Ftprintf(serr, MI_T("Usage: %s gc NAMESPACE CLASSNAME\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    nameSpace = argv[2];
    className = argv[3];

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.classResult = ClassResults;
        callbacks = &_callbacks;
        s_finished = 0;
    }


    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
        return miResult;

    MI_Session_GetClass(miSession, 0, &miOperationOptions, nameSpace, className, callbacks, &miOperation);

    miResult = ConsumeClassResults(&miOperation);

    MI_Operation_Close(&miOperation);

    MI_OperationOptions_Delete(&miOperationOptions);

    return miResult;
}

static MI_Result Subscribe(MI_Session *miSession, int argc, const MI_Char* argv[])
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    const MI_Char *nameSpace;

    if (argc != 3 || opts.querylang == NULL || opts.queryexpr == NULL)
    {
        Ftprintf(serr, MI_T("Usage: %s [--querylang 'WQL/CQL'  --queryexpr ] sub NAMESPACE\n\n"), tcs(arg0));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (opts.synchronous == MI_FALSE)
    {
        _callbacks.callbackContext = &s_finished;
        _callbacks.indicationResult = IndicationResult;
        callbacks = &_callbacks;
        s_finished = 0;
    }

    nameSpace = argv[2];

    miResult = CreateOperationOptions(miSession, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
    {
        Ftprintf(serr, MI_T("Failed to create MI_OperationOptions, error code(%d)\n\n"), miResult);
        return miResult;
    }

    MI_Session_Subscribe(miSession, 0, &miOperationOptions, nameSpace, opts.querylang, opts.queryexpr, NULL, callbacks, &miOperation);

    /* Duplicate operation */
    memcpy(&gop, &miOperation, sizeof(MI_Operation));

    miResult = ConsumeIndicationsResults(&miOperation);

    /* Cleanup global operation since it is done */
    memset(&gop, 0, sizeof(MI_Operation));

    MI_Operation_Close(&miOperation);

    MI_OperationOptions_Delete(&miOperationOptions);

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

static MI_Result GetCommandLineDestDirOption(
    int* argc_,
    const MI_Char* argv[])
{
    int argc = *argc_;
    int i;
    const MI_Char* destdir = NULL;
    const MI_Char* socketfile = NULL;

    for (i = 1; i < argc; )
    {
        if (Tcscmp(argv[i], MI_T("--destdir")) == 0)
        {
            if (i + 1 == argc)
            {
                err(PAL_T("missing argument for --destdir option"));
                return MI_RESULT_INVALID_PARAMETER;
            }

            destdir = argv[i+1];
            memmove((char*)&argv[i], (char*)&argv[i+2],
                sizeof(char*) * (argc-i-1));
            argc -= 2;
        }
        else if (Tcsncmp(argv[i], MI_T("--destdir="), 10) == 0)
        {
            destdir = argv[i] + 10;
            memmove((char*)&argv[i], (char*)&argv[i+1],
                sizeof(char*) * (argc-i));

            argc -= 1;
        }
        if (Tcscmp(argv[i], MI_T("--socketfile")) == 0)
        {
            if (i + 1 == argc)
            {
                err(PAL_T("missing argument for --socketfile option"));
                return MI_RESULT_INVALID_PARAMETER;
            }

            socketfile = argv[i+1];
            memmove((char*)&argv[i], (char*)&argv[i+2],
                sizeof(char*) * (argc-i-1));
            argc -= 2;
        }
        else if (Tcsncmp(argv[i], MI_T("--socketfile="), 13) == 0)
        {
            socketfile = argv[i] + 13;
            memmove((char*)&argv[i], (char*)&argv[i+1],
                sizeof(char*) * (argc-i));

            argc -= 1;
        }
        else
            i++;
    }

    if (destdir)
    {
#if defined(CONFIG_ENABLE_WCHAR)
        char _destdir[PAL_MAX_PATH_SIZE];
        StrWcslcpy(_destdir, destdir, PAL_MAX_PATH_SIZE);
        if (SetPath(ID_DESTDIR, _destdir) != 0)
#else
        if (SetPath(ID_DESTDIR, destdir) != 0)
#endif
        {
            err(PAL_T("failed to set destdir"));
            return MI_RESULT_FAILED;
        }
    }

    if (socketfile)
    {
#if defined(CONFIG_ENABLE_WCHAR)
        char _socketfile[PAL_MAX_PATH_SIZE];
        StrWcslcpy(_socketfile, socketfile, PAL_MAX_PATH_SIZE);
        if (SetPath(ID_SOCKETFILE, _socketfile) != 0)
#else
        if (SetPath(ID_SOCKETFILE, socketfile) != 0)
#endif
        {
            err(PAL_T("failed to set socketfile"));
            return MI_RESULT_FAILED;
        }
    }

    *argc_ = argc;

    return MI_RESULT_OK;
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

static int GetOpt(
    int* argc,
    const MI_Char* argv[],
    const MI_Char* opts[],
    GetOptState* state)
{
    int i;
    int j;

    /* Clear state */
    state->opt[0] = '\0';
    state->arg = NULL;
    state->err[0] = '\0';

    for (i = state->index; i < *argc; i++)
    {
        if (argv[i][0] != '-')
        {
            state->index++;
            continue;
        }

        /* Find option argv[i] */
        for (j = 0; opts[j]; j++)
        {
            MI_Char opt[GETOPT_OPT_SIZE];
            size_t n;
            int hasArg;

            /* Copy option name */
            n = Tcslcpy(opt, opts[j], sizeof(opt)/sizeof(opt[0]));

            /* If option name too long */
            if (n >= sizeof(opt))
            {
                Tcslcpy(state->err, MI_T("bad parameter"), sizeof(state->err)/sizeof(state->err[0]));
                return -1;
            }

            /* If option name zero-length */
            if (n == 0)
            {
                Tcslcpy(state->err, MI_T("bad parameter"), sizeof(state->err)/sizeof(state->err[0]));
                return -1;
            }

            /* If option has argument */
    #ifdef _PREFAST_
     #pragma prefast(push)
     #pragma prefast(disable:26014)
    #endif
            if (opt[n-1] == ':')
            {
                hasArg = 1;
                opt[n-1] = '\0';
            }
            else
                hasArg = 0;
    #ifdef _PREFAST_
     #pragma prefast(pop)
    #endif

            /* Does argv[i] match this option? */
            if (Tcscmp(argv[i], opt) == 0)
            {
                if (hasArg)
                {
                    if (i + 1 == *argc)
                    {
                        Tcslcpy(state->err, MI_T("missing option argument: "),
                            sizeof(state->err)/sizeof(state->err[0]));
                        Tcslcat(state->err, opt, sizeof(state->err)/sizeof(state->err[0]));
                        return -1;
                    }

                    Tcslcpy(state->opt, argv[i], sizeof(state->opt)/sizeof(state->opt[0]));
                    state->arg =  argv[i+1];
                    memmove((void*)&argv[i], (void*)&argv[i+2],
                        sizeof(char*) * ((*argc) - i - 1));
                    *argc -= 2;
                    return 0;
                }
                else
                {
                    Tcslcpy(state->opt, argv[i], sizeof(state->opt)/sizeof(state->opt[0]));
                    memmove((void*)&argv[i], (void*)&argv[i+1],
                        sizeof(char*) * ((*argc) - i));
                    *argc -= 1;
                    return 0;
                }
            }
            else if (hasArg &&
                Tcsncmp(argv[i], opt, n-1) == 0 && argv[i][n-1] == '=')
            {
                Tcslcpy(state->opt, argv[i], sizeof(state->opt)/sizeof(state->opt[0]));
                state->opt[n-1] = '\0';
                state->arg =  &argv[i][n];
                memmove((void*)&argv[i], (void*)&argv[i+1],
                    sizeof(char*) * ((*argc) - i));
                *argc -= 1;
                return 0;
            }
        }

        /* Unknown option */
        Tcslcpy(state->err, MI_T("unknown option: "), sizeof(state->err)/sizeof(state->err[0]));
        Tcslcat(state->err, argv[i], sizeof(state->err)/sizeof(state->err[0]));
        return -1;
    }

    /* Done */
    return 1;
}
static MI_Result GetCommandLineOptions(
    int* argc,
    const MI_Char* argv[])
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const MI_Char* supportedOptions[] =
    {
        MI_T("-h"),
        MI_T("--help"),
        MI_T("-q"),
        MI_T("-t"),
        MI_T("-s"),
        MI_T("-shallow"),
        MI_T("-synchronous"),
        MI_T("-xml"),
        MI_T("-n"),
        MI_T("-R:"),
        MI_T("-ac:"),
        MI_T("-rc:"),
        MI_T("-r:"),
        MI_T("-rr:"),
        MI_T("-rc:"),
        MI_T("-u:"),
        MI_T("-p:"),
        MI_T("-S"),
        MI_T("--summary"),
        MI_T("--prefix:"),
        MI_T("--libdir:"),
        MI_T("--bindir:"),
        MI_T("--localstatedir:"),
        MI_T("--sysconfdir:"),
        MI_T("--providerdir:"),
        MI_T("--certsdir:"),
        MI_T("--rundir:"),
        MI_T("--logdir:"),
        MI_T("--pidfile:"),
        MI_T("--logfile:"),
        MI_T("--registerdir:"),
        MI_T("--socketfile:"),
        MI_T("--pemfile:"),
        MI_T("--keyfile:"),
        MI_T("--agentprogram:"),
        MI_T("--serverprogram:"),
        MI_T("--stdout:"),
        MI_T("--stderr:"),
        MI_T("--querylang:"),
        MI_T("--queryexpr:"),
        MI_T("--auth:"),
        MI_T("--hostname:"),
        MI_T("--protocol:"),
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(argc, argv, supportedOptions, &state);

        if (r == 1)
            break;

        if (r == -1)
        {
            Ftprintf(serr, PAL_T("error: %T\n"), tcs(state.err));
            Ftprintf(serr, PAL_T("Try -h for help\n"));
            return MI_RESULT_INVALID_PARAMETER;
        }

        if (Tcscmp(state.opt, PAL_T("-h")) == 0 || Tcscmp(state.opt, PAL_T("--help")) == 0)
        {
            opts.help = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-q")) == 0)
        {
            opts.quiet = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-t")) == 0)
        {
            opts.trace = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-s")) == 0)
        {
            opts.suppressResults = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-shallow")) == 0)
        {
            opts.shallow = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-synchronous")) == 0)
        {
            opts.synchronous = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-xml")) == 0)
        {
            opts.xml = MI_TRUE;
            opts.synchronous = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-n")) == 0)
        {
            opts.nulls = MI_TRUE;
        }
        else if (Tcscmp(state.opt,  PAL_T("-R")) == 0)
        {
            MI_Char *end;
            opts.repeat = Tcstol(state.arg, &end, 10);

            if (opts.repeat <= 0)
            {
                err(PAL_T("bad value for -R: %T"), tcs(state.arg));
                return MI_RESULT_INVALID_PARAMETER;
            }
        }
        else if (Tcscmp(state.opt,  PAL_T("-ac")) == 0)
        {
            opts.assocClass = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("-rc")) == 0)
        {
            opts.resultClass = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("-r")) == 0)
        {
            opts.role = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("-rr")) == 0)
        {
            opts.resultRole = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("-u")) == 0)
        {
            opts.user = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("-p")) == 0)
        {
            opts.password = state.arg;
        }
        else if (Tcscmp(state.opt,  PAL_T("--stdout")) == 0)
        {
            FILE* os;
#if defined(_MSC_VER)
            FILE* fp;
            os = (_wfopen_s(&fp, state.arg, PAL_T("wb")) == 0 ? fp : NULL);
#else
            {
#if defined(CONFIG_ENABLE_WCHAR)
                char tmp[PAL_MAX_PATH_SIZE];
                StrWcslcpy(tmp, state.arg, sizeof(tmp));
                os = File_Open(tmp, "wb");
#else
                os = File_Open(state.arg, "wb");
#endif
            }
#endif

            if (!os)
                err(PAL_T("failed to open: %T"), tcs(state.arg));

            sout = os;
        }
        else if (Tcscmp(state.opt, PAL_T("--stderr")) == 0)
        {
            FILE* os;
#if defined(_MSC_VER)
            FILE* fp;
            os = (_wfopen_s(&fp, state.arg, PAL_T("wb")) == 0 ? fp : NULL);
#else
            {
#if defined(CONFIG_ENABLE_WCHAR)
                char tmp[PAL_MAX_PATH_SIZE];
                StrWcslcpy(tmp, state.arg, sizeof(tmp));
                os = File_Open(tmp, "wb");
#else
                os = File_Open(state.arg, "wb");
#endif
            }
#endif

            if (!os)
                err(PAL_T("failed to open: %T"), tcs(state.arg));

            serr = os;
        }
        else if (Tcscmp(state.opt, PAL_T("--querylang")) == 0)
        {
            opts.querylang = state.arg;
        }
        else if (Tcscmp(state.opt, PAL_T("--queryexpr")) == 0)
        {
            opts.queryexpr = state.arg;
        }
        else if (Tcscmp(state.opt, PAL_T("--summary")) == 0 ||
                 Tcscmp(state.opt, PAL_T("-S")) == 0)
        {
            opts.summary = MI_TRUE;
        }
        else if (Tcscmp(state.opt, PAL_T("--auth")) == 0)
        {
            opts.auth = state.arg;
        }
         else if (Tcscmp(state.opt, PAL_T("--hostname")) == 0)
        {
            opts.hostname = state.arg;
        }
        else if (Tcscmp(state.opt, PAL_T("--protocol")) == 0)
        {
            opts.protocol = state.arg;
        }
 #if 0
        else if (Tcsncmp(state.opt, PAL_T("--"), 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
                err(PAL_T("SetPathFromNickname() failed"));
        }
#endif
    }

    return MI_RESULT_OK;
}

const MI_Char USAGE[] = MI_T("\
Usage: %T [OPTIONS] COMMAND ...\n\
\n\
This tool sends requests to the CIM server.\n\
\n\
OPTIONS:\n\
    -h, --help          Print this help message.\n\
    -q                  Operate quietly.\n\
    -t                  Enable diagnostic tracing.\n\
    -R N                Repeat command N times.\n\
    -shallow            Use shallow inheritance (see 'ei' command).\n\
    -synchronous        Executes command in synchronous mode.\n\
    -xml                Outputs the result in xml.\n\
    -ac CLASSNAME       Association class (see 'a' and 'r' commands).\n\
    -rc CLASSNAME       Result class (see 'a' command).\n\
    -r ROLE             Role (see 'a' and 'r' commands).\n\
    -rr ROLE            Result role (see 'a' command).\n\
    -n                  Show null properties.\n\
    -u USERNAME         Username.\n\
    -p PASSWORD         User's password.\n\
    -id                 Send identify request.\n\
    --socketfile PATH   Talk to the server server whose socket file resides\n\
                        at the location given by the path argument.\n\
    --auth A            Optional authentication scheme to use if hostname specified.\n\
    --hostname H        Optional target host name. Default is local if not specified.\n\
    --protocol P        Optional protocol to use instead of default.\n\
    --querylang LANG    Query language (for 'ei', 'sub' command).\n\
    --queryexpr EXP     Query expression (for 'ei', 'sub' command).\n\
\n\
COMMANDS:\n\
    noop\n\
        Perform a no-op operation.\n\
    gi NAMESPACE INSTANCENAME\n\
        Peform a CIM [g]et [i]nstance operation.\n\
    ci NAMESPACE NEWINSTANCE\n\
        Peform a CIM [c]reate [i]nstance operation.\n\
    mi NAMESPACE MODIFIEDINSTANCE\n\
        Peform a CIM [m]odify [i]nstance operation.\n\
    di NAMESPACE INSTANCENAME\n\
        Peform a CIM [d]elete [i]nstance operation.\n\
    ei [-shallow] NAMESPACE CLASSNAME\n\
        Peform a CIM [e]numerate [i]nstances operation.\n\
    iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\
        Peform a CIM extrinisic method [i]nvocation operation.\n\
    a [-ac -rc -r -rr ] NAMESPACE INSTANCENAME\n\
        Perform a CIM [a]ssociator instances operation.\n\
    r [-rc -r] NAMESPACE INSTANCENAME (references)\n\
        Perform a CIM [r]eference instances operation.\n\
    gc NAMESPACE CLASSENAME\n\
        Peform a CIM [g]et [c]lass operation.\n\
    enc INSTANCE\n\
        Attempt to encode and print the given instance representation.\n\
    wql NAMESPACE WQLQUERY\n\
        Peform a WQL query operation.\n\
    cql NAMESPACE CQLQUERY\n\
        Peform a CQL query operation.\n\
    sub NAMESPACE\n\
        Peform a subscribe to indication operation.\n\
\n\
INSTANCENAME and PARAMETERS format:\n\
    { class_name property_name property_value property_name property_value }\n\
        property_value is either a string value, or can be an INSTANCENAME.\n\
        property_value can also be an array taking the form [ property_value property_value ].\n\
\n");

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

MI_Result climain(int argc, const MI_Char* argv[])
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

    // Get the options:
    miResult = GetCommandLineDestDirOption(&argc, argv);
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }

    // Get configuration file options:
    miResult = GetConfigFileOptions();
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }

    // Get the options:
    miResult = GetCommandLineOptions(&argc, argv);
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }
    // There must be at least 1 argument left:
    if (argc < 2)
    {
        if (argc >= 1)
        {
            Ftprintf(sout, USAGE, tcs(argv[0]));
            if (opts.help)
                miResult = MI_RESULT_OK;
            else
                miResult = MI_RESULT_INVALID_PARAMETER;
        }
        else
        {
            Ftprintf(sout, USAGE, tcs(MI_T("omicli")));
            miResult = MI_RESULT_INVALID_PARAMETER;
        }
        return miResult;
    }

    if (Tcscmp(argv[1], MI_T("enc")) != 0)
    {
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
    }

    if (Tcscmp(argv[1], MI_T("ei")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            if (opts.queryexpr)
            {
                miResult = QueryInstances(&miSession, argc, argv);
                if (miResult != MI_RESULT_OK)
                    goto CleanupSession;
            }
            else
            {
                miResult = EnumerateInstances(&miSession, argc, argv);
                if (miResult != MI_RESULT_OK)
                    goto CleanupSession;
            }
        }
    }
    else if (Tcscmp(argv[1], MI_T("id")) == 0)
    {
        const MI_Char* args[5];
        int i;

        if (argc != 2)
        {
            Ftprintf(serr, PAL_T("Usage: %T id\n\n"), tcs(arg0));
            miResult = MI_RESULT_INVALID_PARAMETER;
            goto CleanupSession;
        }

        args[0]= argv[0];
        args[1]= MI_T("ei");
        args[2]= MI_T("root/omi");
        args[3]= MI_T("OMI_Identify");
        args[4]= NULL;

        for (i = 0; i < opts.repeat; i++)
        {
            miResult = EnumerateInstances(&miSession, 4, args);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("wql")) == 0 ||
             Tcscmp(argv[1], MI_T("cql")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = Query(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("noop")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = NoOp(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("enc")) == 0)
    {
        miResult = Encode(argc, argv);
        goto CleanupApplication;
    }
    else if (Tcscmp(argv[1], MI_T("gi")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = GetInstance(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("ci")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = CreateInstance(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("mi")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = ModifyInstance(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("di")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = DeleteInstance(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("iv")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = Invoke(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("a")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = Associators(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("r")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = References(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("gc")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = GetClass(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else if (Tcscmp(argv[1], MI_T("sub")) == 0)
    {
        int i;
        for (i = 0; i < opts.repeat; i++)
        {
            miResult = Subscribe(&miSession, argc, argv);
            if (miResult != MI_RESULT_OK)
                goto CleanupSession;
        }
    }
    else
    {
        err(PAL_T("unknown command: %T"), tcs(argv[1]));
        miResult = MI_RESULT_INVALID_PARAMETER;
        goto CleanupSession;
    }

    if (opts.summary)
        PrintSummary();

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
