/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/file.h>
#include <pal/format.h>
#include "indiprvdconfig.h"
#include <base/instance.h>

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast(disable:28719)
#pragma prefast(disable:26006)
#pragma prefast(disable:22103)
#pragma prefast(disable:6031)  
#endif

const char* g_AlertIndicationClassNames_All[] =
{
    "L_IndicationC1",
    "L_IndicationC2",
    "L_IndicationC3",
    "R_IndicationC1",
    "R_IndicationC2",
    "R_IndicationC3",
};
MI_Uint32 g_classcount_All = 6;

const char* g_AlertIndicationClassNames_Left[] =
{
    "L_IndicationC1",
    "L_IndicationC2",
    "L_IndicationC3",
};
MI_Uint32 g_classcount_Left = 3;

const char* g_AlertIndicationClassNames_Right[] =
{
    "R_IndicationC1",
    "R_IndicationC2",
    "R_IndicationC3",
};
MI_Uint32 g_classcount_Right = 3;

const char* gformat1 = 
        "testGroup=%d\r\n"
        "intervalMS=%d\r\n"
        "failAfterCount=%d\r\n"
        "failResult=%d\r\n"
        "initBehavior=%d\r\n"
        "initResultCode=%d\r\n"
        "initTimeoutMS=%d\r\n"
        "finalizeBehavior=%d\r\n"
        "finalizeResultCode=%d\r\n"
        "postBehavior=%d\r\n"
        "miscTestSubGroup=%d\r\n"
        "evalResult=%d\r\n"
        "logLoadUnloadCall=%d\r\n";

const char* gformat2 = 
        "subscribeBookmark=%s\r\n"
        "providerBookmark=%s\r\n"
        "dialect=%s\r\n"
        "expression=%s\r\n";


#ifdef _MSC_VER
    const char* filenameformat = "%s\\%s.%s";
    const char* dirformat = "%s\\%s";
#else
    const char* filenameformat = "%s/%s.%s";
    const char* dirformat = "%s/%s";
#endif

void LifecycleEventQueue_Init(_Out_ LifecycleEventQueue* queue)
{    
    queue->head = NULL;
    queue->tail = NULL;
    ReadWriteLock_Init ( &queue->lock );
    Sem_Init( &queue->sem, SEM_USER_ACCESS_ALLOW_ALL, 0 );
}

void LifecycleEventQueue_Finalize(_Inout_ LifecycleEventQueue* queue)
{
    LifecycleEvent* event = LifecycleEventQueue_Remove(queue);
    while (event)
    {
        LifecycleEvent_Free(event);
        event = LifecycleEventQueue_Remove(queue);
    }

    Sem_Destroy( &queue->sem );
}

void LifecycleEventQueue_Add(_Inout_ LifecycleEventQueue* queue, _In_ LifecycleEvent* event)
{
    ReadWriteLock_AcquireWrite(&queue->lock);
    
    if (queue->tail)
    {
        queue->tail->next = event;
        queue->tail = event;
    }
    else
    {
        queue->head = event;
        queue->tail = event;
    }

    ReadWriteLock_ReleaseWrite(&queue->lock);
}

LifecycleEvent* LifecycleEventQueue_Remove(_Inout_ LifecycleEventQueue* queue)
{
    LifecycleEvent* firstEvent = NULL;
    ReadWriteLock_AcquireWrite(&queue->lock);

    if (queue->head)
    {
        firstEvent = queue->head;
        queue->head = firstEvent->next;
        if (firstEvent->next == NULL)
        {
            queue->tail = NULL;
        }
    }

    ReadWriteLock_ReleaseWrite(&queue->lock);
    return firstEvent;
}

void LifecycleEvent_Free(_In_ LifecycleEvent* event)
{
    if (event)
    {
        if (event->sourceInstance)
        {
            MI_Instance_Delete(event->sourceInstance);
        }
        if (event->previousInstance)
        {
            MI_Instance_Delete(event->previousInstance);
        }
        if (event->methodParam)
        {
            MI_Instance_Delete(event->methodParam);
        }
        PAL_Free(event);
    }
}

_Use_decl_annotations_
void readconfig(const char* classname, Config* config)
{
    static size_t nbufsize = 256;
    FILE* configfile;
    char* configfilepath = (char*)Batch_Get(g_batch, nbufsize);
    char* apilogfilepath = (char*)Batch_Get(g_batch, nbufsize);

    config->className = classname;
    
    if (!configfilepath)
    {
        config->configFilepath = "outofmemory";
        return;
    }
    if (!apilogfilepath)
    {
        config->APIlogFilepath = "outofmemory";
        return;
    }

    sprintf(configfilepath, filenameformat, g_dirpath, classname, "config");
    sprintf(apilogfilepath, filenameformat, g_dirpath, config->className, "apilog");
    config->configFilepath = configfilepath;
    config->APIlogFilepath = apilogfilepath;

    configfile = File_Open(configfilepath, "r");
    if (!configfile)
    {
        /* create one */
        config->subscribeBookmark = ".";
        config->providerBookmark = ".";
        config->dialect = ".";
        config->expression = ".";
        config->failAfterCount = MAX_UINT32;
        config->intervalMS = 1000;
        writeconfig(config);
    }
    else
    {
        config->subscribeBookmark = (char*)Batch_GetClear(g_batch, nbufsize);
        config->providerBookmark = (char*)Batch_GetClear(g_batch, nbufsize);
        config->dialect = (char*)Batch_GetClear(g_batch, nbufsize);
        config->expression = (char*)Batch_GetClear(g_batch, nbufsize);
        
        if (!config->subscribeBookmark || !config->providerBookmark  ||
            !config->dialect || !config->expression)
        {
            config->configFilepath = "FAILED";
            File_Close(configfile);
            return;
        }
        /* read config from file */
        fscanf(configfile, gformat1,
            &config->testGroup,
            &config->intervalMS,
            &config->failAfterCount,
            &config->failResult,
            &config->initBehavior,
            &config->initResultCode,
            &config->initTimeoutMS,
            &config->finalizeBehavior,
            &config->finalizeResultCode,
            &config->postBehavior,
            &config->miscTestSubGroup,
            &config->evalResult,
            &config->logLoadUnloadCall);

        fscanf(configfile, "subscribeBookmark=%[^\r\n]", config->subscribeBookmark);
        fscanf(configfile, "\r\n");
        fscanf(configfile, "providerBookmark=%[^\r\n]", config->providerBookmark);
        fscanf(configfile, "\r\n");
        fscanf(configfile, "dialect=%[^\r\n]", config->dialect);
        fscanf(configfile, "\r\n");
        fscanf(configfile, "expression=%[^\r\n]", config->expression);
        File_Close(configfile);
    }
    config->apicallseqcount = readAPIlog(config, config->apicallseq);
    Config_Reopenlogfile(config);
    LOGMSG(("read config file (%s)", config->configFilepath));
}

/* write config to file */
void writeconfig(_In_ Config* config)
{
    FILE* configfile = File_Open(config->configFilepath, "w");
    if (!configfile)
    {
        return;
    }
    LOGMSG(("created config file (%s)", config->configFilepath));
    fprintf(configfile, gformat1,
            config->testGroup,
            config->intervalMS,
            config->failAfterCount,
            config->failResult,
            config->initBehavior,
            config->initResultCode,
            config->initTimeoutMS,
            config->finalizeBehavior,
            config->finalizeResultCode,
            config->postBehavior,
            config->miscTestSubGroup,
            config->evalResult,
            config->logLoadUnloadCall);

    fprintf(configfile, gformat2,
            config->subscribeBookmark,
            config->providerBookmark,
            config->dialect,
            config->expression);
    File_Close(configfile);
}

FILE* _reopenAPIlogfile(_In_ Config* config)
{
    FILE* file;
    File_Remove(config->APIlogFilepath);
    file = File_Open(config->APIlogFilepath, "w");
    if (file == NULL)
        LOGMSG(("!!Failed to create apilog file (%s)!!", config->APIlogFilepath));
    return file;
}

_Use_decl_annotations_
void writeAPIlog(Config* config, const char* fmt, ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    ReadWriteLock_AcquireRead(&config->lock);

    va_start(ap, fmt);
    Vfprintf(config->apilogfile, fmt, ap);
    va_end(ap);

    fprintf(config->apilogfile, "\r\n");
    FlushLog(config->apilogfile);

    ReadWriteLock_ReleaseRead(&config->lock);
}

/* read apilog for given class, return the count of log entries in the file */
_Use_decl_annotations_
int readAPIlog(Config* config, char* logs[MAXLOGENTRY])
{
    FILE* apilogfile = File_Open(config->APIlogFilepath, "r");
    int entrycount = 0;
    static size_t nbufsize = 128;
    char* buf = (char*)Batch_Get(g_batch, nbufsize);
    memset(logs, 0, sizeof(*logs));
    if (!apilogfile || !buf)
    {
        return 0;
    }
    while(fscanf(apilogfile, "%s\r\n", buf) > 0)
    {
        logs[entrycount++] = buf;
        if (entrycount >= MAXLOGENTRY)
            break;
        buf = (char*)Batch_Get(g_batch, nbufsize);
        if (!buf)
            break;
    }
    File_Close(apilogfile);
    return entrycount;
}


const char* n_TestGroup[] =
{
    "Default",
    "Initialize fault",
    "Finalize fault",
    "Post",
    "misc",
};

const char* n_InitBehavior[] =
{
    "No Fault",
    "ClassLoadFail",
    "EnableFail",
    "SubscribeFail",
    "ClassLoadTimeout",
    "EnableTimeout",
    "SubscribeTimeout",
};

const char* n_FinalizeBehavior[] =
{
    "No fault",
    "ClassUnloadFail",
    "DisableFail",
    "UnsubscribeFail",
};

const char* n_PostBehavior[] =
{
    "Enable Context on Diff Thread",
    "Subscribe Context on Diff Thread",
    "Enable Context on Call Thread",
    "Subscribe Context on Call Thread",
};

const char* n_MiscTestGroup[] =
{
    "Default",
    "GetExpression on Filter",
    "Evaluate on Filter",
    "ContextTest",
    "Bookmark",
    "SelfTest",
};

/* Dump config to log in a readable manner */
void DumpConfig(_In_ Config* config)
{
    LOGMSG(("\tCONFIG: { class (%s); testgroup (%s); ", config->className, n_TestGroup[(int)config->testGroup]));
    LOGMSG(("\t\tInterval (%d ms); fail after (%u); fail result (%d);", config->intervalMS, config->failAfterCount, config->failResult));
    LOGMSG(("\t\tInitialize (%s); init code (%d); timeout (%d ms);", n_InitBehavior[(int)config->initBehavior], config->initResultCode, config->initTimeoutMS));
    LOGMSG(("\t\tFinalize (%s); finalize code (%d);", n_FinalizeBehavior[(int)config->finalizeBehavior], config->finalizeResultCode));
    LOGMSG(("\t\tPost behavior (%s);", n_PostBehavior[(int)config->postBehavior]));
    LOGMSG(("\t\tMisc test group (%s);", n_MiscTestGroup[(int)config->miscTestSubGroup]));
    LOGMSG(("\t\tLog Load/Unload API call (%d);", config->logLoadUnloadCall));
    LOGMSG(("\t\tLifecycle current types (%d) and supported types (%d)", config->currentSubscriptionTypes, config->supportedSubscriptionTypes));
    LOGMSG(("\t\t}"));
}

_Use_decl_annotations_
MI_Result Config_Finalize(Config* config)
{
    if ( config->apilogfile )
    {
        File_Close( config->apilogfile );
        config->apilogfile = NULL;
    }
    LifecycleEventQueue_Finalize( &config->lifecycleQueue );
    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result Config_Initialize(Config* config)
{
    memset(config, 0, sizeof(Config));
    ReadWriteLock_Init(&config->lock);
    LifecycleEventQueue_Init(&config->lifecycleQueue);
    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result Config_Reopenlogfile(Config* config)
{
    if ( config->APIlogFilepath )
    {
        ReadWriteLock_AcquireWrite( &config->lock );
        if ( config->apilogfile )
            File_Close( config->apilogfile );
        config->apilogfile = _reopenAPIlogfile( config );
        ReadWriteLock_ReleaseWrite( &config->lock );
        if ( NULL != config->apilogfile )
            return MI_RESULT_OK;
    }
    return MI_RESULT_FAILED;
}


#define CONFIG_CLASSNAME MI_T("Test_IndicationConfig")

/* Convert config to instance */
_Use_decl_annotations_
MI_Result Config_ToInstance(
    Batch* batch,
    const Config* config,
    MI_Instance **instanceOut)
{
    MI_Instance *instance;
    MI_Result r;
    MI_Value value;

    MI_Char* className = Batch_StrTcsdup(batch, config->className);
    r = Instance_NewDynamic(&instance, CONFIG_CLASSNAME, MI_FLAG_CLASS, batch);
    if (r != MI_RESULT_OK)
        return r;
    value.string = className;
    r = MI_Instance_AddElement(instance, MI_T("className"), &value, MI_STRING, MI_FLAG_KEY);
    if (r != MI_RESULT_OK)
        return r;

    /*
    value.string = Batch_StrTcsdup(batch, config->configFilepath);
    r = MI_Instance_AddElement(instance, MI_T("configFilepath"), &value, MI_STRING, 0);
    if (r != MI_RESULT_OK)
        return r;
    */

    value.uint32 = config->testGroup;
    r = MI_Instance_AddElement(instance, MI_T("testGroup"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->intervalMS;
    r = MI_Instance_AddElement(instance, MI_T("intervalMS"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->failAfterCount;
    r = MI_Instance_AddElement(instance, MI_T("failAfterCount"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->failResult;
    r = MI_Instance_AddElement(instance, MI_T("failResult"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->initBehavior;
    r = MI_Instance_AddElement(instance, MI_T("initBehavior"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->initResultCode;
    r = MI_Instance_AddElement(instance, MI_T("initResultCode"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->initTimeoutMS;
    r = MI_Instance_AddElement(instance, MI_T("initTimeoutMS"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->finalizeBehavior;
    r = MI_Instance_AddElement(instance, MI_T("finalizeBehavior"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->finalizeResultCode;
    r = MI_Instance_AddElement(instance, MI_T("finalizeResultCode"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->postBehavior;
    r = MI_Instance_AddElement(instance, MI_T("postBehavior"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->miscTestSubGroup;
    r = MI_Instance_AddElement(instance, MI_T("miscTestSubGroup"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    if (config->subscribeBookmark)
    {
        value.string = Batch_StrTcsdup(batch, config->subscribeBookmark);
        r = MI_Instance_AddElement(instance, MI_T("subscribeBookmark"), &value, MI_STRING, 0);
        if (r != MI_RESULT_OK)
            return r;
    }

    if (config->providerBookmark)
    {
        value.string = Batch_StrTcsdup(batch, config->providerBookmark);
        r = MI_Instance_AddElement(instance, MI_T("providerBookmark"), &value, MI_STRING, 0);
        if (r != MI_RESULT_OK)
            return r;
    }

    if (config->dialect)
    {
        value.string = Batch_StrTcsdup(batch, config->dialect);
        r = MI_Instance_AddElement(instance, MI_T("dialect"), &value, MI_STRING, 0);
        if (r != MI_RESULT_OK)
            return r;
    }

    if (config->expression)
    {
        value.string = Batch_StrTcsdup(batch, config->expression);
        r = MI_Instance_AddElement(instance, MI_T("expression"), &value, MI_STRING, 0);
        if (r != MI_RESULT_OK)
            return r;
    }

    value.uint32 = config->evalResult;
    r = MI_Instance_AddElement(instance, MI_T("evalResult"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->logLoadUnloadCall;
    r = MI_Instance_AddElement(instance, MI_T("logLoadUnloadCall"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->currentSubscriptionTypes;
    r = MI_Instance_AddElement(instance, MI_T("currentSubscriptionTypes"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    value.uint32 = config->supportedSubscriptionTypes;
    r = MI_Instance_AddElement(instance, MI_T("supportedSubscriptionTypes"), &value, MI_UINT32, 0);
    if (r != MI_RESULT_OK)
        return r;

    *instanceOut = instance;
    return MI_RESULT_OK;
}

/* Get config from instance */
_Use_decl_annotations_
MI_Result Config_FromInstance(
    Batch* batch,
    const MI_Instance *instance,
    Config* config)
{
    MI_Value v;
    MI_Type t;
    MI_Uint32 f;
    MI_Result r;
    memset((void*)config, 0, sizeof(Config));
    r = MI_Instance_GetElement(instance, MI_T("className"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->className = (const char*)Batch_ZStrdup(batch, v.string);
    
    r = MI_Instance_GetElement(instance, MI_T("configFilepath"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->configFilepath = (const char*)Batch_ZStrdup(batch, v.string);
    
    r = MI_Instance_GetElement(instance, MI_T("testGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->testGroup = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("testGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->testGroup = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("intervalMS"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->intervalMS = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("failAfterCount"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->failAfterCount = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("failResult"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->failResult = (MI_Result)v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("initBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initBehavior = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("initResultCode"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initResultCode = (MI_Result)v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("initTimeoutMS"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->initTimeoutMS = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("finalizeBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->finalizeBehavior = v.uint32;
    
    r = MI_Instance_GetElement(instance, MI_T("finalizeResultCode"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->finalizeResultCode = (MI_Result)v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("postBehavior"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->postBehavior = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("miscTestSubGroup"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->miscTestSubGroup = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("subscribeBookmark"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->subscribeBookmark = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("providerBookmark"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->providerBookmark = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("dialect"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->dialect = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("expression"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (v.string)
        config->expression = Batch_ZStrdup(batch, v.string);

    r = MI_Instance_GetElement(instance, MI_T("evalResult"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->evalResult = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("logLoadUnloadCall"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->logLoadUnloadCall = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("currentSubscriptionTypes"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->currentSubscriptionTypes = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("supportedSubscriptionTypes"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    config->supportedSubscriptionTypes = v.uint32;

    r = MI_Instance_GetElement(instance, MI_T("apicallseq"), &v, &t, &f, NULL);
    if (r != MI_RESULT_OK)
        return r;
    if (t != MI_STRINGA)
        return MI_RESULT_INVALID_PARAMETER;

    {
        MI_Uint32 count = MAXLOGENTRY;
        MI_Uint32 i;
        if (v.stringa.size < count)
            count =v.stringa.size;
        if (v.stringa.data)
        {
            for (i = 0; i < count; i++)
            {
                if (v.stringa.data[i])
                {
                    char *str = Batch_ZStrdup(batch, v.stringa.data[i]);
                    if (!str)
                        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    config->apicallseq[i] = str;
                }
            }
        }
        config->apicallseqcount = count;
    }
    return r;
}

/*
**==============================================================================
**
** Setup config object
**
**==============================================================================
*/
_Use_decl_annotations_
void SetConfig(Config* config,
    const char* className,
    MI_Uint32 testGroup,
    MI_Uint32 intervalMS,
    MI_Uint32 failAfterCount,
    MI_Result failResult,
    MI_Uint32 initBehavior,
    MI_Result initResultCode,
    MI_Uint32 initTimeoutMS,
    MI_Uint32 finalizeBehavior,
    MI_Result finalizeResultCode,
    MI_Uint32 postBehavior,
    MI_Uint32 miscTestSubGroup,
    const char* subscribeBookmark,
    const char* providerBookmark,
    const char* dialect,
    const char* expression,
    MI_Uint32   evalResult,
    MI_Uint32  logLoadUnloadCall,
    MI_Uint32 currentSubscriptionTypes,
    MI_Uint32 supportedSubscriptionTypes)
{
    config->className = className;
    config->testGroup = testGroup;
    config->intervalMS = intervalMS;
    config->failAfterCount = failAfterCount;
    config->failResult = failResult;
    config->initBehavior = initBehavior;
    config->initResultCode = initResultCode;
    config->initTimeoutMS = initTimeoutMS;
    config->finalizeBehavior = finalizeBehavior;
    config->finalizeResultCode = finalizeResultCode;
    config->postBehavior = postBehavior;
    config->miscTestSubGroup = miscTestSubGroup;
    config->subscribeBookmark = (char*)subscribeBookmark;
    config->providerBookmark = (char*)providerBookmark;
    config->dialect = (char*)dialect;
    config->expression = (char*)expression;
    config->evalResult = evalResult;
    config->logLoadUnloadCall = logLoadUnloadCall;
    config->currentSubscriptionTypes = currentSubscriptionTypes; 
    config->supportedSubscriptionTypes = supportedSubscriptionTypes; 
}

/* Setup config objects for multiple classes */
_Use_decl_annotations_
void SetConfigs(
    MI_Uint32 size,
    Config* configs,
    const char* classNames[],
    MI_Uint32 testGroup,
    MI_Uint32 intervalMS,
    MI_Uint32 failAfterCount,
    MI_Result failResult,
    MI_Uint32 initBehavior,
    MI_Result initResultCode,
    MI_Uint32 initTimeoutMS,
    MI_Uint32 finalizeBehavior,
    MI_Result finalizeResultCode,
    MI_Uint32 postBehavior,
    MI_Uint32 miscTestSubGroup,
    const char* subscribeBookmark,
    const char* providerBookmark,
    const char* dialect,
    const char* expression,
    MI_Uint32   evalResult,
    MI_Uint32  logLoadUnloadCall,
    MI_Uint32 currentSubscriptionTypes,
    MI_Uint32 supportedSubscriptionTypes)
{
    MI_Uint32 i;
    DEBUG_ASSERT( size > 0 );
    for ( i = 0; i < size; i++ )
    {
        SetConfig(&configs[i], classNames[i], 
            testGroup,
            intervalMS,
            failAfterCount,
            failResult,
            initBehavior,
            initResultCode,
            initTimeoutMS,
            finalizeBehavior,
            finalizeResultCode,
            postBehavior,
            miscTestSubGroup,
            subscribeBookmark,
            providerBookmark,
            dialect,
            expression,
            evalResult,
            logLoadUnloadCall,
            currentSubscriptionTypes,
            supportedSubscriptionTypes);
    }
}

#ifdef _PREFAST_
    #pragma prefast(pop)
#endif

