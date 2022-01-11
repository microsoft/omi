/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include <util.h>
#include "XYZ_Process.h"

/*
 * Defines number of process instances
 */
#define PROCESS_COUNT 10

/*
 * Defines self structure
 */
struct _XYZ_Process_Self
{
    SelfStruct self;
    MI_LifecycleIndicationContext* context;
    MI_Uint32 types;
    /* Instances of XYZ_Process class */
    XYZ_Process processes[PROCESS_COUNT];
    MI_Uint32 seqno;
};

/*
 * Declares global self object
 */
XYZ_Process_Self g_self;

/*
 * Compare two strings
 */
int micmp(
    _In_z_ const MI_Char* s1, 
    _In_z_ const MI_Char* s2)
{
#if defined(MI_USE_WCHAR)
    return wcscmp(s1, s2);
#else
    return strcmp(s1, s2);
#endif
}

/*
 * Callback function to receive lifecycle subscription notifications.
 * For example, if client(s) start subscription to the lifecycle indication of
 * XYZ_Process class with following query:
 *
 * SELECT * from CIM_InstCreation WHERE sourceInstance isA XYZ_PROCESS
 *
 * Then types' value will be MI_LIFECYCLE_INDICATION_CREATE, see MI.h for
 * all definitions about the LIFECYCLE query type
 *
 * The value of types parameter equals to the combination value of
 * all of the active lifecycle subscriptions' type (to this class).
 *
 */
void MI_CALL _LifecycleIndicationCallback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    XYZ_Process_Self* self = (XYZ_Process_Self*)callbackData;
    self->types = types;
}

/*
 * Set property values of given instance
 */
static MI_Result _SetPropertyValue(
    MI_Uint32 index,
    XYZ_Process* self)
{
    static MI_Char* strHandleArray[PROCESS_COUNT] = {
        MI_T("100"),
        MI_T("101"),
        MI_T("102"),
        MI_T("103"),
        MI_T("104"),
        MI_T("105"),
        MI_T("106"),
        MI_T("107"),
        MI_T("108"),
        MI_T("109")
    };
    static MI_Char* strCaptionArray[PROCESS_COUNT] = {
        MI_T("gedit"),
        MI_T("gcc"),
        MI_T("ssh"),
        MI_T("test"),
        MI_T("vi"),
        MI_T("eclipse"),
        MI_T("putty"),
        MI_T("cpp"),
        MI_T("bar"),
        MI_T("foo")
    };

    static MI_Char* strCSCreationClassName = MI_T("CIM_ComputerSystem");
    static MI_Char* strCSName = MI_T("Machine001");
    static MI_Char* strOSCreationClassName = MI_T("CIM_OperatingSystem");
    static MI_Char* strOSName = MI_T("CENTOS");
    static MI_Char* strCreationClassName = MI_T("XYZ_Process");

    MI_Result r;
    MI_Uint32 i = index;
    do
    {
        r = XYZ_Process_Set_runningTime(self, 100 * i);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_Handle(self, strHandleArray[i]);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_CSCreationClassName(self, strCSCreationClassName);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_CSName(self, strCSName);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_OSCreationClassName(self, strOSCreationClassName);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_OSName(self, strOSName);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_CreationClassName(self, strCreationClassName);
        if (r!= MI_RESULT_OK) break;

        r = XYZ_Process_Set_Caption(self, strCaptionArray[i]);
    }
    while (0);

    return r;
}

/*
 * Initialize process instances, which will be posted
 * within XYZ_Process_EnumerateInstances function
 */
static MI_Result _Initialize(
    MI_Context* context,
    XYZ_Process_Self* self)
{
    MI_Uint32 i;
    MI_Result r;

    for (i = 0; i < PROCESS_COUNT; i++)
    {
        r = XYZ_Process_Construct(&self->processes[i], context);
        if (r!= MI_RESULT_OK) break;
        _SetPropertyValue(i, &self->processes[i]);
    }
    return r;
}

/*
 * Destruct process instances
 */
static void _Finalize(
    XYZ_Process_Self* self)
{
    MI_Uint32 i;
    for (i = 0; i < PROCESS_COUNT; i++)
    {
        if (self->processes[i].__instance.ft)
            XYZ_Process_Destruct(&self->processes[i]);
    }
    memset(self, 0, sizeof(XYZ_Process_Self));
}


/*
 * Callback function to trigger lifecycle indication (CIM_InstCreation) for XYZ_Process
 * This function simulate the process creation events by posting CIM_InstCreation indication.
 *
 * In reality, provider may utilize system API to monitor system wide process creation event,
 * and generate corresponding CIM_InstCreation indication via lifecycle context; similarly for
 * CIM_InstDeletion, CIM_InstModification, CIM_InstRead, CIM_InstMethodCall, etc.
 *
 */
MI_Uint32 MI_CALL TriggerIndication(
    _In_ void* callbackdata)
{
    XYZ_Process_Self* self = (XYZ_Process_Self*)callbackdata;
    MI_LifecycleIndicationContext* context = self->context;
    MI_Uint32 seqno = self->seqno++;
    MI_Uint32 index = seqno % PROCESS_COUNT;

    /*
     * When practical, the provider developer needs to get the process creation event, such as 
     * monitoring a system event or responding to a system API, then trigger a Cim_InstCreation
     * indication.
     *
     * In order to trigger a CIM_InstCreation indication, the XYZ_Process instance needs to be created first. 
     * After that, call MI_LifecycleIndicationContext_PostCreate function.
     *
     * The following sample code shows how to create a XYZ_Process instance and trigger a CIM_InstCreation
     * indication of XYZ_Process.
     */
    if ( self->types & MI_LIFECYCLE_INDICATION_CREATE )
    {
        XYZ_Process process;
        MI_Result r;
        r = MI_LifecycleIndicationContext_ConstructInstance(context, &XYZ_Process_rtti, &process.__instance);
        if (r == MI_RESULT_OK)
        {
            r = _SetPropertyValue(index, &process);
            if ( r == MI_RESULT_OK )
                /* Post CIM_InstCreation indication from background thread */
                MI_LifecycleIndicationContext_PostCreate(context, &process.__instance);

            /* Destruct the instance */
            MI_Instance_Destruct(&process.__instance);
        }
    }
    return 1;
}

void MI_CALL XYZ_Process_Load(
    XYZ_Process_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = &g_self;
    memset(&g_self, 0, sizeof(g_self));

    /* get lifecycle context and store the context for posting indication usage */
    r = MI_Context_GetLifecycleIndicationContext(context, &(*self)->context);
    CHECKR_POST_RETURN_VOID(context, r);

    /* register a callback, which will be invoked if subscription changed, i.e., client cancelled a subscription or create a new subscription */
    r = MI_LifecycleIndicationContext_RegisterCallback(
        (*self)->context, _LifecycleIndicationCallback, (void*)(ptrdiff_t)(*self));
    CHECKR_POST_RETURN_VOID(context, r);

    /* notify server that what types of lifecycle indication supported by current class */
    r = MI_LifecycleIndicationContext_SetSupportedTypes(
        (*self)->context, MI_LIFECYCLE_INDICATION_CREATE);
    CHECKR_POST_RETURN_VOID(context, r);

    /* initialize global data */
    r = _Initialize(context, *self);
    if (r != MI_RESULT_OK)
    {
        _Finalize(*self);
        *self = NULL;
    }
    else
    {
        int code;
        (*self)->self.context = (*self)->context;
        (*self)->self.postindication = TriggerIndication;

         /*
         * Please note that lifecycle indications should only be posted from a background thread.
         *
         * This XYZ_Process example spawns a background thread that will periodically 
         * fire CIM_InstCreation indications to simulate process creation events.
         */
        code = Thread_Create(&(*self)->self.thread, fireIndication, (void*)(*self));
        if ( code != 0 )
        {
            /* Failed to create thread */
            r = MI_RESULT_FAILED;
            _Finalize(*self);
        }
    }
    MI_PostResult(context, r);
}

void MI_CALL XYZ_Process_Unload(
    XYZ_Process_Self* self,
    MI_Context* context)
{
    MI_Uint32 retValue;

    /* Shutdown the spawned thread */
    self->self.disabling = MI_TRUE;
    Thread_Join( & self->self.thread, &retValue );

    /* cleanup */
    _Finalize( self );
    MI_LifecycleIndicationContext_PostResult( self->context, MI_RESULT_OK );
    MI_PostResult( context, MI_RESULT_OK );
}

void MI_CALL XYZ_Process_EnumerateInstances(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_GetInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_CreateInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_ModifyInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_DeleteInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_Invoke_RequestStateChange(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_RequestStateChange* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_Invoke_Create(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_Create* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_Process_Invoke_GetRunTime(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_GetRunTime* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

