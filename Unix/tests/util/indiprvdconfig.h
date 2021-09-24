/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _tests_util_indiprvdconfig_h
#define _tests_util_indiprvdconfig_h

#include "util.h"
#include <pal/lock.h>

PAL_BEGIN_EXTERNC

/* callback function to setup a instance */
typedef MI_Result (MI_CALL * SetupIndicationProperties)(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication);

#define MAX_UINT32 0xFFFFFFFF

extern const char* filenameformat;
extern const char* dirformat;
extern char* g_dirpath;

#define MAXLOGENTRY 200

typedef enum _TestGroup
{
    TestGroup_Default = 0,
    TestGroup_Init = 1,
    TestGroup_Finalize = 2,
    TestGroup_Post = 3,
    TestGroup_Misc = 4
}TestGroup;

typedef enum _InitBehavior
{
    InitBehavior_Default = 0,
    InitBehavior_ClassLoadFail = 1,
    InitBehavior_EnableFail = 2,
    InitBehavior_SubscribeFail = 3,
    InitBehavior_ClassLoadTimeout = 4,
    InitBehavior_EnableTimeout = 5,
    InitBehavior_SubscribeTimeout = 6
}InitBehavior;

typedef enum _FinalizeBehavior
{
    FinalizeBehavior_Default = 0,
    FinalizeBehavior_ClassUnloadFail = 1,
    FinalizeBehavior_DisableFail = 2,
    FinalizeBehavior_UnsubscribeFail = 3
}FinalizeBehavior;

typedef enum _PostBehavior
{
    PostBehavior_Default = 0, /* Spawned thread to enable context */
    PostBehavior_Subcontext = 1, /* For MI_API_VERSION 1 & 2, post to subscribe context are not supported */
    PostBehavior_Enablecontext_PostOnCallThread = 2,
    PostBehavior_Subcontext_PostOnCallThread = 3 /* For MI_API_VERSION 1 & 2, post to subscribe context are not supported */
}PostBehavior;

typedef enum _MiscTestGroup
{
    MiscTestGroup_Default = 0, /* no misc test */
    MiscTestGroup_GetExpression = 1,
    MiscTestGroup_Evaluate = 2,
    MiscTestGroup_ContextTest = 3,
    MiscTestGroup_Bookmark = 4,
    MiscTestGroup_SelfTest = 5
}MiscTestGroup;

typedef struct _LifecycleEvent
{
    struct _LifecycleEvent* next;
    int type;

    MI_Instance* sourceInstance;
    MI_Instance* previousInstance;
    MI_Instance* methodParam;
} LifecycleEvent;

typedef struct _LifecycleEventQueue
{
    struct _LifecycleEvent* head;
    struct _LifecycleEvent* tail;

    ReadWriteLock lock;
    Sem sem;
} LifecycleEventQueue;

void LifecycleEventQueue_Init(_Out_ LifecycleEventQueue* queue);
void LifecycleEventQueue_Finalize(_Inout_ LifecycleEventQueue* queue);
void LifecycleEventQueue_Add(_Inout_ LifecycleEventQueue* queue, _In_ LifecycleEvent* event);
LifecycleEvent* LifecycleEventQueue_Remove(_Inout_ LifecycleEventQueue* queue); 
void LifecycleEvent_Free(_In_ LifecycleEvent* event);

typedef struct _Config
{
    /* 
     * ------------------------------------------------------------------
     * Following config items are loaded from config file for the class
     * ------------------------------------------------------------------
     */
    MI_Uint32 testGroup;        /* 0 - post indication
                                 * 1 - initialize fault
                                 * 2 - finalize fault
                                 * 3 - post
                                 * 4 - misc.
                                 */

    MI_Uint32 intervalMS;       /* interval of firing indication in millisecond */    
    MI_Uint32 failAfterCount;   /* fail the indication class after this count, MAX_UINT32 means infinite */
    MI_Result failResult;       /* the failure result code */

    MI_Uint32 initBehavior;     /* Initialization behavior
                                 *
                                 * 0 - Success
                                 * 1 - Class_Load failed
                                 * 2 - EnableIndication failed;
                                 * 3 - Subscribe failed;
                                 * 4 - Class_Load timeout
                                 * 5 - EnableIndication timeout
                                 * 6 - Subscribe timeout
                                 *
                                 */
    MI_Result initResultCode;
    MI_Uint32 initTimeoutMS;    /* timeout value for initialization */

    MI_Uint32 finalizeBehavior;  /* Finalization behavior
                                 *
                                 * 0 - Success
                                 * 1 - Class_Unload failed
                                 * 2 - DisableIndication failed;
                                 * 3 - UnSubscribe failed;
                                 * 
                                 */
    MI_Result finalizeResultCode;

    MI_Uint32 postBehavior;     /* post indication behavior
                                 *
                                 * 0 - from another thread on enableIndication context
                                 * 1 - from another thread on each subscribe context
                                 * 2 - inside EnableIndication function - not supported but make sure no AV
                                 * 3 - inside subscribe function - not supported but make sure no AV
                                 * 
                                 */

    MI_Uint32 miscTestSubGroup; /* Misc. test sub group
                                 *
                                 * 0 - No misc test
                                 * 1 - call MI_Filter_GetExpression
                                 * 2 - call MI_Filter_Evaluate
                                 * 3 - test load/unload/enable/disable/subscribe/unsubscribe context fts (low priority)
                                 * 4 - bookmark
                                 * 5 - subscriptionSelf & classSelf
                                 *
                                 */

    char* subscribeBookmark; /* bookmark from client */
    char* providerBookmark; /* bookmark sent by provider */   
    char* dialect;        /* expected dialect */
    char* expression;     /* expected query expression */
    MI_Uint32   evalResult;     /*
                                 * expected evaluation result
                                 * 0 - fail
                                 * 1 - success
                                 *
                                 */

    MI_Uint32  logLoadUnloadCall; /* 0 - default (not include)    1 - include */

    /*
        The subscription type bitmasks are defined in the following way in mi.h: 

            #define MI_LIFECYCLE_INDICATION_NONE    0
            #define MI_LIFECYCLE_INDICATION_CREATE  1
            #define MI_LIFECYCLE_INDICATION_MODIFY  2
            #define MI_LIFECYCLE_INDICATION_DELETE  4
            #define MI_LIFECYCLE_INDICATION_READ    8
            #define MI_LIFECYCLE_INDICATION_METHODCALL  16

    */
    MI_Uint32 currentSubscriptionTypes;  /* Current subscription types to this class */
    MI_Uint32 supportedSubscriptionTypes;  /* Subscription types allowed for this class */

    /*
     * ------------------------------------------------------------------
     * Following fields are set by each class
     * ------------------------------------------------------------------
     */
    const char* className; /* class identification */
    const char* configFilepath; /* config file path */
    const char* APIlogFilepath; /* api call log file path */
    FILE* apilogfile; /* file used to log api call sequence */

    MI_Context* postctx;    /* the context used to post indication */
    SetupIndicationProperties setprop; /* callback to setup indication instance */
    MI_Instance* indication; /* the instance used to post */
    void* context; /* the context used to call setprop */
    MI_Uint32 count; /* total indications has been posted */

    Thread thread; /* thread fire the indication */
    volatile ptrdiff_t threadrunning; /* thread still running or not */
    MI_Boolean disabled; /* MI_TRUE if the class was disabled */

    const MI_Filter* filter; /* filter object from subscribe call */
    MI_Uint64 subscriptionID; /* subscription ID from subscribe call */

    Sem sem; /* semaphore */
    MI_Boolean seminited; /* semaphore initialized */

    char* apicallseq[MAXLOGENTRY]; /* api call sequences */
    MI_Uint32 apicallseqcount; /* api call count */

    void* subscriptionSelf;     /* subscription self object set within <class>_Subscribe function */
    void* classSelf; /* class self object set within <class>_Load function */

    ReadWriteLock lock; /* protect resources such as apilogfile */

    MI_Instance* lifecycleInstance; /* Lifecycle indication instance used for test purposes */
    MI_LifecycleIndicationContext* lifecycleContext;  /* Context used to post lifecycle indications */
    MI_Uint32 lifecycleThreadControl;  /* Bit mask specifying which lifecycle indications are currently being fired */
    
    Thread lifecycleBackgroundThread; /* Background thread used to post lifecycle indications */
    MI_Boolean lifecycleThreadDisabled; /* Indicates whether the background thread was disabled */

    LifecycleEventQueue lifecycleQueue; /* Queue to keep track of lifecycle events that need to be posted by lifecycleBackgroundThread */

}Config;

void readconfig(_In_z_ const char* classname, _Inout_ Config* config);
void writeconfig(_In_ Config* config);

void writeAPIlog(_In_ Config* config, _In_z_ const char* fmt, ...);
/* read apilog for given class, return the count of log entries in the file */
int readAPIlog(_In_ Config* config, _Outptr_result_buffer_(MAXLOGENTRY) char* logs[MAXLOGENTRY]);

void DumpConfig(_In_ Config* config);

MI_Result Config_Finalize(_In_ Config* config);
MI_Result Config_Initialize(_In_ Config* config);
MI_Result Config_Reopenlogfile(_In_ Config* config);

/* Convert config to instance */
MI_Result Config_ToInstance(
    _In_ Batch* batch,
    _In_ const Config* config, 
    _Outptr_ MI_Instance **instanceOut);

/* Get config from instance */
MI_Result Config_FromInstance(
    _In_ Batch* batch,
    _In_ const MI_Instance *instance,
    _Out_ Config* config);

/* Setup config object */
void SetConfig(
    _In_ Config* config,
    _In_z_ const char* className,
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
    _In_opt_z_ const char* subscribeBookmark,
    _In_opt_z_ const char* providerBookmark,
    _In_opt_z_ const char* dialect,
    _In_opt_z_ const char* expression,
    MI_Uint32   evalResult,
    MI_Uint32  logLoadUnloadCall,
    MI_Uint32 currentSubscriptionTypes,
    MI_Uint32 supportedSubscriptionTypes);

/* Setup config objects for multiple classes */
void SetConfigs(
    _In_ MI_Uint32 size,
    _In_reads_(size) Config* config,
    _In_reads_z_(size) const char* classNames[],
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
    _In_opt_z_ const char* subscribeBookmark,
    _In_opt_z_ const char* providerBookmark,
    _In_opt_z_ const char* dialect,
    _In_opt_z_ const char* expression,
    MI_Uint32   evalResult,
    MI_Uint32  logLoadUnloadCall,
    MI_Uint32 currentSubscriptionTypes,
    MI_Uint32 supportedSubscriptionTypes);


extern const char* g_AlertIndicationClassNames_All[];
extern MI_Uint32 g_classcount_All;
extern const char* g_AlertIndicationClassNames_Left[];
extern MI_Uint32 g_classcount_Left;
extern const char* g_AlertIndicationClassNames_Right[];
extern MI_Uint32 g_classcount_Right;

PAL_END_EXTERNC

#endif /* _tests_util_indiprvdconfig_h */
