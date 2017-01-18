/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ctype.h>
#include <time.h>
#include <pal/file.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <base/process.h>
#include <pal/sleep.h>
#include <base/pidfile.h>
#include <base/paths.h>
#include <base/log.h>
#include <pal/dir.h>
#include <pal/lock.h>
#include "util.h"

#ifdef _MSC_VER
# include <windows.h>
# include <shlobj.h>
#else
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pwd.h>
# include <unistd.h>
#endif

#ifdef _PREFAST_
    #pragma prefast(push)
    /* ANSI API ('SHGetFolderPathA') should not be called from Unicode modules. */
    /* Calling ANSI APIs leads to unexpected results when handling multi-lingual */
    /* text or Unicode-only languages. Use the Unicode version of this API instead.*/
    #pragma prefast(disable:38020)
#endif

/*
**==============================================================================
**
** Consume instance
**
**==============================================================================
*/
static MI_Result _ConsumeInstanceResults(
    _In_ InstanceOperationStruct* ios,
    _In_ MI_Operation *miOperation)
{
    MI_Result miResult = MI_RESULT_FAILED;
    MI_Boolean moreResults = MI_FALSE;

    if (MI_TRUE == ios->sync)
    {
        do
        {
            const MI_Instance *miInstanceResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;

            _miResult = MI_Operation_GetInstance(
                miOperation,
                &miInstanceResult,
                &moreResults,
                &miResult,
                &errorString,
                &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }
            if (miInstanceResult)
                ios->count++;
        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = ios->finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&ios->finished, &ios->finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = ios->finished;
        }
        miResult = ios->finalResult;
    }

    return miResult;
}

/*
**==============================================================================
**
** Async operation, the callback to receive instance results
**
**==============================================================================
*/
static MI_Result g_finalResult;

static MI_Boolean g_called;
static MI_Boolean g_moreResults;
void MI_CALL _InstanceResultCallback(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    InstanceOperationStruct* ios = (InstanceOperationStruct*)callbackContext;
    if (instance)
        ios->count ++;
    if (moreResults == MI_FALSE)
    {
        ios->finalResult = resultCode;
        ios->finished = 1;
        CondLock_Broadcast((ptrdiff_t)&ios->finished);
    }
    g_finalResult = resultCode;
    g_called = MI_TRUE;
    g_moreResults = moreResults;
}


/*
**==============================================================================
**
** Read instance for given class
**
**==============================================================================
*/
_Use_decl_annotations_
MI_Result EnumerateInstance(
    InstanceOperationStruct* ios,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MI_Result miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;

    if (ios->sync == MI_FALSE)
    {
        _callbacks.callbackContext = ios;
        _callbacks.instanceResult = _InstanceResultCallback;
        callbacks = &_callbacks;
        ios->finished = 0;
        ios->finalResult = MI_RESULT_FAILED;
    }

    MI_Session_EnumerateInstances(&ios->session, 0, NULL, nameSpace, className, MI_FALSE, callbacks, &miOperation);
    miResult = _ConsumeInstanceResults(ios, &miOperation);
    MI_Operation_Close(&miOperation);
    return miResult;
}


static Process serverProcess;
MI_Char s_socketFile[PAL_MAX_PATH_SIZE];
char s_socketFile_a[PAL_MAX_PATH_SIZE];

/*
**==============================================================================
**
** Remember if the server is started or not
**
**==============================================================================
*/
int g_serverstarted = 0;

#if defined(_MSC_VER)
unsigned short _GetUnittestPortNumber()
{
    return 21718;
}
#else
unsigned short _GetUnittestPortNumber()
{
    return 10000 + ((geteuid() % 200) * 200);
}
unsigned short UnittestPortNumberWSMANHTTP()
{
    return _GetUnittestPortNumber() + 198;
}
unsigned short UnittestPortNumberWSMANHTTPS()
{
    return _GetUnittestPortNumber() + 197;
}
#endif

/* =============================================================================
**
** Kill Old Server Instance
**
   ============================================================================*/

/* We don't have a return value because this function will terminate the test 
 * if it can't kill the previous omiserver. So success or program exit
 */

void KillOldServerInstance()

{
    char buf[64];
    int tries = 0;
    static const int MAX_TRIES = 50;
    int pid = -1;
    int status = -1;
    
    while (tries < MAX_TRIES)
    {    

        pid = -1;
        status = PIDFile_Read(&pid);

        if (!status && pid != -1)
        {

#if defined(aix)
            sprintf(buf, "sudo kill -TERM %d", pid);
#else
            sprintf(buf, "kill -TERM %d", pid);
#endif
            system(buf);
            Sleep_Milliseconds(50);
            tries++;
        }
        else 
        {
            // Process is gone
            break;
        }        
    }

    if (tries >= MAX_TRIES)
    {
        // Killing the process didn't get rid of the file. Lets kill the file. IsRunning checks for a process or 
        // a stale file. Returns 0 if the file was stale

        if (PIDFile_IsRunning() != 0)
        {
            // We can't seem to get rid of it
             fprintf(stderr, "Could not kill pervious server instance process id = %d. Exiting\n", pid);

        }        
    }
}

MI_Result StartOmiserver()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[17];
    char http[32];
    char https[32];
    int i;
    InstanceOperationStruct ios;
    MI_Result r;

    memset(&ios, 0, sizeof(InstanceOperationStruct));

    KillOldServerInstance();
    Snprintf(http, sizeof(http),"%d", UnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", UnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = OMI_GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile_a;
    argv[6] = "--httpport";
    argv[7] = http;
    argv[8] = "--httpsport";
    argv[9] = https;
    argv[10] = "--livetime";
    argv[11] = "1800";

    argv[12] = "--loglevel";
    argv[13] = Log_GetLevelString(Log_GetLevel());
    argv[14] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
    {
        NitsAssert(0, PAL_T("Failed to create omiserver process"));
        return MI_RESULT_FAILED;
    }

    g_serverstarted = 1;

    /*  wait for server to start */
    r = MI_Application_Initialize(0, NULL, NULL, &ios.app);
    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to Initialize MI_Application"));
        return r;
    }

    for (i = 0; i < 100; i++)
    {
        Sleep_Milliseconds(50);
        r = MI_Application_NewSession(&ios.app, NULL, NULL, NULL, NULL, NULL, &ios.session);
        if (r == MI_RESULT_OK)
        {
            break;
        }
    }

    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to create session"));
        MI_Application_Close(&ios.app);
        return r;
    }

    /* TODO: Use MI_Session_TestConnection if it is implemented */
    for (i = 0; i < 1000; i++)
    {
        g_finalResult = MI_RESULT_OK;
        g_called = MI_FALSE;
        g_moreResults = MI_FALSE;
        ios.sync = MI_FALSE;
        r = EnumerateInstance(&ios, MI_T("root/omi"), MI_T("omi_identify"));
        if (r == MI_RESULT_OK)
        {
            break;
        }
        Sleep_Milliseconds(50);
    }
    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to enumerate omi_identify instance"));
    }
    MI_Session_Close(&ios.session, NULL, NULL);
    MI_Application_Close(&ios.app);
    return r;
}

MI_Result StopOmiserver()
{
    MI_Result r = MI_RESULT_OK;
    if (g_serverstarted == 1)
    {
        /*
         * For e2e test, server might be busy, and e2e cancellation is not complete yet,
         * sleep two seconds to mitigate server hang issues during shutting down.
         */
        Sleep_Milliseconds(2000);
        if (Process_StopChild(&serverProcess) != 0)
        {
            memset((void*)&serverProcess, 0, sizeof(Process));
            r = MI_RESULT_FAILED;
        }
        g_serverstarted = 0;
    }
    return r;
}




#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
