/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "fire.h"
#include <sys/stat.h>
#include <pal/dir.h>
#include <pal/file.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <pal/atomic.h>
#include <time.h>

#ifdef _MSC_VER
# include <windows.h>
# include <shlobj.h>
#else
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pwd.h>
#endif

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast(disable:28719)
#endif

PAL_Uint32 THREAD_API fireindication(void* param)
{
    Config* config = (Config*)param;
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 failAfterCount = config->failAfterCount;
    MI_Result failResult = config->failResult;

    Atomic_Swap( &config->threadrunning, 1);
    LOGMSG(("Set threadrunning to 1 for config (%p)", config));

    config->count = 0;
    LOGMSG(("Start to fireindication for class (%s)", config->className));

    /* wait for the semaphore */
    LOGMSG(("Wait for semaphore to fire indication"));
    Sem_Wait(&config->sem);
    LOGMSG(("Received semaphore and start firing indication"));

    if (config->testGroup == (MI_Uint32)TestGroup_Misc)
    {
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_GetExpression:
        case MiscTestGroup_Evaluate:
        case MiscTestGroup_SelfTest:
            failAfterCount = 1;
            failResult = MI_RESULT_FAILED;
            break;
        default:
            break;
        }
    }

    while((MI_FALSE == config->disabled) && (config->count < failAfterCount))
    {
        config->count++;

        if (config->intervalMS > 0)
        {
            Sleep_Milliseconds(config->intervalMS);
        }
        if (r!= MI_RESULT_OK)
        {
            LOGMSG(("Set property value of indication failed (%d); Ignore #%d indication", r, config->count));
            continue;
        }
        if (config->lifecycleThreadControl == 0)
        {
            const MI_Char* bookmark = NULL;

            DEBUG_ASSERT( NULL != config->setprop );
            r = config->setprop(config->context, &config->indication);
            if (r == MI_RESULT_OK)
            {
                DEBUG_ASSERT( NULL != config->indication );

                if (config->subscribeBookmark &&
                    0 < Strlen(config->subscribeBookmark) &&
                    0 != Strcmp(config->subscribeBookmark, "."))
                {
                    // Only set bookmark if it is non-NULL and non-default
                    bookmark = ansiToMI(config->subscribeBookmark);
                }
                r = MI_Context_PostIndication(config->postctx, config->indication, 0, bookmark);
                if (r!= MI_RESULT_OK)
                {
                    LOGMSG(("Post #%d Indication failed (%d)", config->count, r));
                }

                /* Delete indication instance */
                MI_Instance_Delete( config->indication );
                config->indication = NULL;
            }
            else
            {
                LOGMSG(("config(%p:%s)->setprop failed to create indication instance(%d)", config, config->className, r));
            }
        }
        else
        {
            if (config->lifecycleContext && config->currentSubscriptionTypes != 0 && config->supportedSubscriptionTypes != 0)
            {
                // lifeCycleThreadControl other than 0 and a running thread indicates that we should schedule lifecycle events
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_CREATE)
                {
                    r = lifecycle_CreateInstance(config, config->lifecycleInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_CreateInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_MODIFY)
                {
                    r = lifecycle_ModifyInstance(config->lifecycleInstance, config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_ModifyInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_DELETE)
                {
                    r = lifecycle_DeleteInstance(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_DeleteInstance for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_READ)
                {
                    r = lifecycle_EnumerateInstances(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_EnumerateInstances for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                if (config->lifecycleThreadControl & MI_LIFECYCLE_INDICATION_METHODCALL)
                {
                    r = lifecycle_InvokeMethod(config);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("Lifecycle_InvokeMethod for class (%s) failed with result (%d)", config->className, r));
                    }
                }
            }
        }
        LOGMSG(("Fired #%d indication for class (%s)", config->count, config->className));
    }

    Atomic_Swap( &config->threadrunning, 0);
    LOGMSG(("Set threadrunning to 0 for config (%p)", config));

    if (MI_FALSE == config->disabled)
    {
        LOGMSG(("fireindication stopped due to class (%s) need to fail after firing (%d) indicaitons", config->className, failAfterCount));
#if !defined(_MSC_VER)
        // if not joined yet, release thread resources
        pthread_detach(config->thread.__impl);
# endif
        if (failResult != MI_RESULT_OK)
        {
            if (config->lifecycleThreadControl == 0)
            {
                MI_Context_PostResult(config->postctx, failResult);
            }
            else
            {
                MI_LifecycleIndicationContext_PostResult(config->lifecycleContext, failResult);
            }
            LOGMSG(("Stop the fireindication and failed the operation with error (%s:%d)", config->className, failResult));
        }
    }
    else
        LOGMSG(("fireindication stopped due to disable indication called"));
    LOGMSG(("Done fireindication for class (%s)", config->className));
    return 0;
}

PAL_Uint32 THREAD_API fireLifecycleEvents(void* param)
{
    MI_Result r = MI_RESULT_OK;
    Config* config = (Config*)param;
    LifecycleEvent* event = NULL;
    while (MI_FALSE == config->lifecycleThreadDisabled)
    {
        Sem_Wait(&config->lifecycleQueue.sem);
        event = LifecycleEventQueue_Remove(&config->lifecycleQueue);
        if (event)
        {
            switch (event->type)
            {
            case MI_LIFECYCLE_INDICATION_CREATE:
                if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_CREATE))
                {
                    r = MI_LifecycleIndicationContext_PostCreate(config->lifecycleContext, event->sourceInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostCreate for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                break;
            case MI_LIFECYCLE_INDICATION_MODIFY:
                if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_MODIFY))
                {
                    r = MI_LifecycleIndicationContext_PostModify(config->lifecycleContext, event->previousInstance, event->sourceInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostModify for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                break;
            case MI_LIFECYCLE_INDICATION_DELETE:
                if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_DELETE))
                {
                    r = MI_LifecycleIndicationContext_PostDelete(config->lifecycleContext, event->sourceInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostDelete for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                break;
            case MI_LIFECYCLE_INDICATION_READ:
                if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_READ))
                {
                    r = MI_LifecycleIndicationContext_PostRead(config->lifecycleContext, event->sourceInstance);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostRead for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                break;
            case MI_LIFECYCLE_INDICATION_METHODCALL:
                if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_METHODCALL))
                {
                    r = MI_LifecycleIndicationContext_PostMethodCall_Before(config->lifecycleContext, event->sourceInstance, MI_T("GenericInstMethod"), event->methodParam);
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostMethodCall_Before for class (%s) failed with result (%d)", config->className, r));
                    }
                    r = MI_LifecycleIndicationContext_PostMethodCall_After(config->lifecycleContext, event->sourceInstance, MI_T("GenericInstMethod"), event->methodParam, MI_T("0"));
                    if (r != MI_RESULT_OK)
                    {
                        LOGMSG(("MI_LifecycleIndicationContext_PostMethodCall_After for class (%s) failed with result (%d)", config->className, r));
                    }
                }
                break;
            default:
                break;
            }

            LifecycleEvent_Free(event);
        }
    }
    return 0;
}


Config cfgTest_Indication;
Config cfgL_IndicationC1;
Config cfgL_IndicationC2;
Config cfgL_IndicationC3;
Config cfgR_IndicationC1;
Config cfgR_IndicationC2;
Config cfgR_IndicationC3;
Config cfgTest_Class;
Config cfgL_LifecycleC1; 
Config cfgL_LifecycleC2; 
Config cfgR_LifecycleC1; 
Config cfgR_LifecycleC2; 

Batch* g_batch;
FILE* g_logfile;
char* g_logfilepath=NULL;
char* g_dirpath = NULL;

void ReloadConfig()
{
    readconfig("Test_Indication", &cfgTest_Indication);
    readconfig("L_IndicationC1", &cfgL_IndicationC1);
    readconfig("L_IndicationC2", &cfgL_IndicationC2);
    readconfig("L_IndicationC3", &cfgL_IndicationC3);
    readconfig("R_IndicationC1", &cfgR_IndicationC1);
    readconfig("R_IndicationC2", &cfgR_IndicationC2);
    readconfig("R_IndicationC3", &cfgR_IndicationC3);
    readconfig("Test_Class", &cfgTest_Class);
    readconfig("L_LifecycleC1", &cfgL_LifecycleC1);
    readconfig("L_LifecycleC2", &cfgL_LifecycleC2);
    readconfig("R_LifecycleC1", &cfgR_LifecycleC1);
    readconfig("R_LifecycleC2", &cfgR_LifecycleC2);
}

MI_Result Initialize()
{
    MI_Result r;
    static size_t nbufsize = 256;
    g_batch = Batch_New(64);
    if (!g_batch)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    g_dirpath = (char*)Batch_Get(g_batch, nbufsize);
    g_logfilepath = (char*)Batch_Get(g_batch, nbufsize);
    if (!g_logfilepath || !g_dirpath)
    {
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto error;
    }

    sprintf(g_dirpath, dirformat, gethomedir(), "indicationlog");
    if (Isdir(g_dirpath) == PAL_FALSE)
    {
        if (Mkdir(g_dirpath, 0777) != 0)
        {
            r = MI_RESULT_FAILED;
            goto error;
        }
    }
    sprintf(g_logfilepath, filenameformat, g_dirpath, "provider", "log");

#if !defined(_MSC_VER)
    {
        //
        // Delete file if larger than certain size
        //
        struct stat buf;
        if (stat(g_logfilepath, &buf) == 0)
        {
            if ( (unsigned long)buf.st_size > 0x800000UL )
                File_Remove(g_logfilepath);
        }
    }
#endif

    g_logfile = File_Open(g_logfilepath, "a+");
    if (!g_logfile)
    {
        r = MI_RESULT_FAILED;
        goto error;
    }

    Config_Initialize(&cfgTest_Indication);
    Config_Initialize(&cfgL_IndicationC1);
    Config_Initialize(&cfgL_IndicationC2);
    Config_Initialize(&cfgL_IndicationC3);
    Config_Initialize(&cfgR_IndicationC1);
    Config_Initialize(&cfgR_IndicationC2);
    Config_Initialize(&cfgR_IndicationC3);
    Config_Initialize(&cfgTest_Class);
    Config_Initialize(&cfgL_LifecycleC1);
    Config_Initialize(&cfgL_LifecycleC2);
    Config_Initialize(&cfgR_LifecycleC1);
    Config_Initialize(&cfgR_LifecycleC2);
    

    ReloadConfig();

    LOGMSG(("\r\n\r\n\r\n\r\n==================================================="));
    LOGMSG(("Initialize"));

    return MI_RESULT_OK;

error:
    if (g_logfile)
    {
        File_Close(g_logfile);
        g_logfile = NULL;
    }
    if (g_batch)
    {
        Batch_Delete(g_batch);
        g_batch = NULL;
    }
    return r;
}

MI_Result Finalize()
{
    LOGMSG(("Finaliize"));
    LOGMSG(("\r\n===================================================\r\n"));

    Config_Finalize(&cfgTest_Indication);
    Config_Finalize(&cfgL_IndicationC1);
    Config_Finalize(&cfgL_IndicationC2);
    Config_Finalize(&cfgL_IndicationC3);
    Config_Finalize(&cfgR_IndicationC1);
    Config_Finalize(&cfgR_IndicationC2);
    Config_Finalize(&cfgR_IndicationC3);
    Config_Finalize(&cfgTest_Class);
    Config_Finalize(&cfgL_LifecycleC1);
    Config_Finalize(&cfgL_LifecycleC2);
    Config_Finalize(&cfgR_LifecycleC1);
    Config_Finalize(&cfgR_LifecycleC2);

    if (g_logfile)
        File_Close(g_logfile);
    if (g_batch)
        Batch_Delete(g_batch);
    return MI_RESULT_OK;
}

#ifdef _PREFAST_
#pragma prefast(pop)
#endif

