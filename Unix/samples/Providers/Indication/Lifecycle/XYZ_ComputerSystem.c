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
#include <pal/sem.h>
#include "XYZ_ComputerSystem.h"

/*
 * Defines a lifecycle indication item that
 * represents one lifecycle indication to be fired
 */
typedef struct _LifecycleIndicationItem LifecycleIndicationItem;

struct _LifecycleIndicationItem
{
    MI_Uint32 type; /* lifecycle indication type, for example MI_LIFECYCLE_INDICATION_METHODCALL */
    MI_Instance* instance;
    union
    {
        struct _MethodCall
        {
            MI_Instance* parameter;
            MI_Char* methodName;
            MI_Char* returnvalue;
            MI_Boolean precall;
        }
        methodcall;
        struct _Modify
        {
            MI_Instance* originalInstance;
        }
        modify;
    }
    u;
    LifecycleIndicationItem* next;
};


/*
 * Create LifecycleIndicationItem
 */
MI_INLINE LifecycleIndicationItem* LifecycleIndicationItem_New(
    _In_ MI_Uint32 lifecycleIndicationType,
    _In_ const MI_Instance* instance,
    _In_opt_ const MI_Instance* originalInstance,
    _In_opt_ const MI_Instance* parameter,
    _In_opt_z_ const MI_Char* methodName,
    _In_opt_z_ const MI_Char* returnValue,
    _In_ MI_Boolean precall)
{
    MI_Result r;
    MI_Instance* clonedInstance = NULL;
    MI_Instance* clonedOriginalInstance = NULL;
    MI_Instance* clonedParameter = NULL;
    MI_Char* clonedMethodName = NULL;
    MI_Char* clonedReturnValue = NULL;
    LifecycleIndicationItem* temp;

    if (instance == NULL)
        return NULL;

    temp = (LifecycleIndicationItem*) calloc(1, sizeof(LifecycleIndicationItem));
    if (temp == NULL)
        return NULL;

    do
    {
        r = MI_Instance_Clone(instance, &clonedInstance);
        if (r != MI_RESULT_OK)
            break;

        switch(lifecycleIndicationType)
        {
        case MI_LIFECYCLE_INDICATION_CREATE:
            break;
        case MI_LIFECYCLE_INDICATION_MODIFY:
            if (originalInstance == NULL)
            {
                r = MI_RESULT_INVALID_PARAMETER;
            }
            else
            {
                r = MI_Instance_Clone(originalInstance, &clonedOriginalInstance);
            }
            break;
        case MI_LIFECYCLE_INDICATION_DELETE:
            break;
        case MI_LIFECYCLE_INDICATION_READ:
            break;
        case MI_LIFECYCLE_INDICATION_METHODCALL:
            if (parameter)
            {
                r = MI_Instance_Clone(parameter, &clonedParameter);
                if (r != MI_RESULT_OK)
                    break;
            }
            if (methodName)
            {
                r = MI_StringDup(methodName, &clonedMethodName);
                if (r != MI_RESULT_OK)
                    break;
            }
            else
            {
                r = MI_RESULT_INVALID_PARAMETER;
            }
            if ((!precall) && returnValue)
            {
                r = MI_StringDup(returnValue, &clonedReturnValue);
                if (r != MI_RESULT_OK)
                    break;
            }
            break;
        default:
            {
                r = MI_RESULT_INVALID_PARAMETER;
                break;
            }
        }
    }
    while(0);
    
    if (r != MI_RESULT_OK)
    {
        if (temp)
        {
            free(temp);
            temp = NULL;
        }
        if (clonedInstance)
            MI_Instance_Delete(clonedInstance);
        if (clonedParameter)
            MI_Instance_Delete(clonedParameter);
        if (clonedOriginalInstance)
            MI_Instance_Delete(clonedOriginalInstance);
        if (clonedMethodName)
            free (clonedMethodName);
        if (clonedReturnValue)
            free (clonedReturnValue);
        return NULL;
    }

    temp->type = lifecycleIndicationType;
    temp->instance = clonedInstance;
    switch(lifecycleIndicationType)
    {
    case MI_LIFECYCLE_INDICATION_MODIFY:
        temp->u.modify.originalInstance = clonedOriginalInstance;
        break;
    case MI_LIFECYCLE_INDICATION_METHODCALL:
        temp->u.methodcall.methodName = clonedMethodName;
        temp->u.methodcall.parameter = clonedParameter;
        temp->u.methodcall.returnvalue = clonedReturnValue;
        temp->u.methodcall.precall = precall;
        break;
    default:
        break;
    }
    return temp;
}

/*
 * Free LifecycleIndicationItem
 */
MI_INLINE void LifecycleIndicationItem_Free(
    _In_ _Post_invalid_ LifecycleIndicationItem* item)
{
    if (item)
    {
        if (item->instance)
            MI_Instance_Delete(item->instance);
        switch(item->type)
        {
        case MI_LIFECYCLE_INDICATION_MODIFY:
            if (item->u.modify.originalInstance)
                MI_Instance_Delete(item->u.modify.originalInstance);
            break;
        case MI_LIFECYCLE_INDICATION_METHODCALL:
            if (item->u.methodcall.parameter)
                MI_Instance_Delete(item->u.methodcall.parameter);
            if (item->u.methodcall.methodName)
                free (item->u.methodcall.methodName);
            if (item->u.methodcall.returnvalue)
                free (item->u.methodcall.returnvalue);
            break;
        default:
            break;
        }
        free (item);
    }
}

/*
 * Defines lifecycle indication(s) list,
 * caches list of pending lifecycle indication to be fired
 */
/*
 * Defines lifecycle indication item,
 * represents one lifecycle indication to be fired
 */
typedef struct _LifecycleIndicationItemList
{
    Lock lock;
    Sem sem;
    LifecycleIndicationItem* head;
    LifecycleIndicationItem* tail;
}
LifecycleIndicationItemList;

/*
 * Initialize list
 */
MI_INLINE void LifecycleIndicationItemList_Init(
    _Out_ LifecycleIndicationItemList* self)
{
    self->head = NULL;
    self->tail = NULL;
    Lock_Init(&self->lock);
    Sem_Init(&self->sem, SEM_USER_ACCESS_ALLOW_ALL, 0);
}

/*
 * Insert item to list
 */
MI_INLINE MI_Result LifecycleIndicationItemList_Insert(
    _In_ LifecycleIndicationItemList* self,
    _In_ LifecycleIndicationItem* item)
{
    Lock_Acquire(&self->lock);
    if (self->head == NULL)
    {
        self->head = self->tail = item;
        Sem_Post(&self->sem, 1);
    }
    else
    {
        self->tail->next = item;
    }
    Lock_Release(&self->lock);
    return MI_RESULT_OK;
}

/*
 * remove item from list
 */
MI_INLINE LifecycleIndicationItem* LifecycleIndicationItemList_Remove(
    _In_ LifecycleIndicationItemList* self)
{
    LifecycleIndicationItem* item;
    Lock_Acquire(&self->lock);
    if (self->head == NULL)
    {
        item = NULL;
    }
    else
    {
        item = self->head;
        self->head = item->next;
        if (self->head == NULL)
            self->tail = NULL;
    }
    Lock_Release(&self->lock);
    return item;
}

/*
 * Finalize list
 */
MI_INLINE void LifecycleIndicationItemList_Finalize(
    _In_ _Post_invalid_ LifecycleIndicationItemList* self)
{
    LifecycleIndicationItem* item = LifecycleIndicationItemList_Remove(self);
    while(item)
    {
        LifecycleIndicationItem_Free(item);
        item = LifecycleIndicationItemList_Remove(self);
    }
    Lock_Finalize(&self->lock);
    Sem_Destroy(&self->sem);
}

/*
 * Create LifecycleIndicationItem and add to list
 */
MI_INLINE MI_Result LifecycleIndicationItemList_Add(
    _In_ LifecycleIndicationItemList* self,
    _In_ MI_Uint32 lifecycleIndicationType,
    _In_ const MI_Instance* instance,
    _In_opt_ const MI_Instance* originalInstance,
    _In_opt_ const MI_Instance* parameter,
    _In_opt_z_ const MI_Char* methodName,
    _In_opt_z_ const MI_Char* returnValue,
    _In_ MI_Boolean precall)
{
    LifecycleIndicationItem* item = LifecycleIndicationItem_New(
        lifecycleIndicationType,
        instance,
        originalInstance,
        parameter,
        methodName,
        returnValue,
        precall);
    if (item == NULL)
        return MI_RESULT_FAILED;
    return LifecycleIndicationItemList_Insert(self, item);
}

/*
 * Defines self structure
 */
struct _XYZ_ComputerSystem_Self
{
    MI_LifecycleIndicationContext* context;
    MI_Uint32 types;
    XYZ_ComputerSystem cs;
    LifecycleIndicationItemList list;
    MI_Boolean disabling;
    Thread thread;
};

/*
**==============================================================================
**
** Thread proc to post lifecycle indication
**
**==============================================================================
*/
MI_Uint32 THREAD_API lifecycleindicationproc(void* param)
{
    XYZ_ComputerSystem_Self* self = (XYZ_ComputerSystem_Self*)param;
    MI_Uint32 exitvalue = 1;
    LifecycleIndicationItemList *list = &self->list;

    if ( !self || !self->context )
    {
        exitvalue = 0;
        goto EXIT;
    }

    while( MI_FALSE == self->disabling )
    {
        /* post lifecycle indication */
        LifecycleIndicationItem* item = LifecycleIndicationItemList_Remove(list);
        while(item)
        {
            if(item->type & self->types)
            {
                switch(item->type)
                {
                case MI_LIFECYCLE_INDICATION_CREATE:
                    MI_LifecycleIndicationContext_PostCreate(self->context, item->instance);
                    break;
                case MI_LIFECYCLE_INDICATION_DELETE:
                    MI_LifecycleIndicationContext_PostDelete(self->context, item->instance);
                    break;
                case MI_LIFECYCLE_INDICATION_READ:
                    MI_LifecycleIndicationContext_PostRead(self->context, item->instance);
                    break;
                case MI_LIFECYCLE_INDICATION_MODIFY:
                    MI_LifecycleIndicationContext_PostModify(self->context, item->u.modify.originalInstance, item->instance);
                    break;
                case MI_LIFECYCLE_INDICATION_METHODCALL:
                    if (item->u.methodcall.precall)
                    {
                        MI_LifecycleIndicationContext_PostMethodCall_Before(
                            self->context, item->instance, item->u.methodcall.methodName, item->u.methodcall.parameter);
                            
                    }
                    else
                    {
                        MI_LifecycleIndicationContext_PostMethodCall_After(
                            self->context, item->instance, item->u.methodcall.methodName, item->u.methodcall.parameter, item->u.methodcall.returnvalue);
                    }
                    break;
                default:
                    break;
                }
            }
            LifecycleIndicationItem_Free(item);
            item = LifecycleIndicationItemList_Remove(list);
        }

        /* wait for semophore, either provider is being unloaded or new lifecycle item scheduled */
        Sem_Wait(&self->list.sem);
    }

EXIT:
    Thread_Exit(exitvalue);
    return exitvalue;
}



/*
 * Callback function to receive lifecycle subscription notifications.
 * For example, if client(s) start subscription to the lifecycle indication of
 * XYZ_ComputerSystem class with following query:
 *
 * SELECT * from CIM_InstIndication WHERE sourceInstance isA XYZ_ComputerSystem
 *
 * Then types' value will be MI_LIFECYCLE_INDICATION_ALL, see MI.h for
 * all definitions about the LIFECYCLE query type
 *
 * The value of types parameter equals to the combination value of
 * all of the active lifecycle subscriptions' type (to this class).
 *
 */
void MI_CALL _XYZ_ComputerSystemLifecycleIndicationCallback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    XYZ_ComputerSystem_Self* self = (XYZ_ComputerSystem_Self*)callbackData;
    self->types = types;
}

/*
 * Initialization
 */
static MI_Result _Initialize(
    MI_Context* context,
    XYZ_ComputerSystem_Self* self)
{
    MI_Result r;
    r = XYZ_ComputerSystem_Construct(&self->cs, context);
    if (r!= MI_RESULT_OK) return r;
    r = XYZ_ComputerSystem_Set_Name(&self->cs, MI_T("mycomputer"));
    if (r!= MI_RESULT_OK) return r;
    r = XYZ_ComputerSystem_Set_CreationClassName(&self->cs, MI_T("XYZ_ComputerSystem"));

    LifecycleIndicationItemList_Init(&self->list);
    return r;
}

/*
 * Cleanup
 */
static void _Finalize(
    XYZ_ComputerSystem_Self* self)
{
    if (self->cs.__instance.ft)
        XYZ_ComputerSystem_Destruct(&self->cs);
    memset(self, 0, sizeof(XYZ_ComputerSystem_Self));

    LifecycleIndicationItemList_Finalize(&self->list);
}

/*
 * Declares global self object
 */
XYZ_ComputerSystem_Self g_csself;

void MI_CALL XYZ_ComputerSystem_Load(
    XYZ_ComputerSystem_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = &g_csself;
    memset(&g_csself, 0, sizeof(g_csself));

    /* get lifecycle context and store the context for posting indication usage */
    r = MI_Context_GetLifecycleIndicationContext(context, &(*self)->context);
    CHECKR_POST_RETURN_VOID(context, r);

    /* register a callback, which will be invoked if subscription changed, i.e., client cancelled a subscription or create a new subscription */
    r = MI_LifecycleIndicationContext_RegisterCallback(
        (*self)->context, _XYZ_ComputerSystemLifecycleIndicationCallback, (void*)(ptrdiff_t)(*self));
    CHECKR_POST_RETURN_VOID(context, r);

    /* notify server that what types of lifecycle indication supported by current class */
    r = MI_LifecycleIndicationContext_SetSupportedTypes(
        (*self)->context, MI_LIFECYCLE_INDICATION_ALL);
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

         /*
         * Please note that lifecycle indications should only be posted from a background thread.
         *
         * This XYZ_ComputerSystem example spawns a background thread that will periodically 
         * fire CIM_InstCreation indications to simulate process creation events.
         */
        code = Thread_Create(&(*self)->thread, lifecycleindicationproc, (void*)(*self));
        if ( code != 0 )
        {
            /* Failed to create thread */
            r = MI_RESULT_FAILED;
            _Finalize(*self);
        }
    }
    MI_PostResult(context, r);
}

void MI_CALL XYZ_ComputerSystem_Unload(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context)
{
    MI_Uint32 retValue;

    /* Shutdown the spawned thread */
    self->disabling = MI_TRUE;
    Sem_Post(&self->list.sem, 1);
    Thread_Join(&self->thread, &retValue);

    /* cleanup */
    _Finalize( self );
    MI_LifecycleIndicationContext_PostResult( self->context, MI_RESULT_OK );
    MI_PostResult( context, MI_RESULT_OK );
}

void MI_CALL XYZ_ComputerSystem_EnumerateInstances(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r;
    r = XYZ_ComputerSystem_Post(&self->cs, context);
    if (r == MI_RESULT_OK)
    {
        /*
         * Generate CIM_InstRead indication if lifecycle context is valid and
         * there is at least one client subscribed to CIM_InstRead indication of this class
         *
         */
        if (self->context && (self->types & MI_LIFECYCLE_INDICATION_READ))
        {
            LifecycleIndicationItemList_Add(&self->list,
                MI_LIFECYCLE_INDICATION_READ,
                &self->cs.__instance,
                NULL,
                NULL,
                NULL,
                NULL,
                MI_FALSE);
        }
    }
    MI_PostResult(context, r);
}

void MI_CALL XYZ_ComputerSystem_GetInstance(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_ComputerSystem* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result r;
    r = XYZ_ComputerSystem_Post(&self->cs, context);
    if (r == MI_RESULT_OK)
    {
        /*
         * Generate CIM_InstRead indication if lifecycle context is valid and
         * there is at least one client subscribed to CIM_InstRead indication of this class
         *
         */
        if (self->context && (self->types & MI_LIFECYCLE_INDICATION_READ))
        {
            LifecycleIndicationItemList_Add(&self->list,
                MI_LIFECYCLE_INDICATION_READ,
                &self->cs.__instance,
                NULL,
                NULL,
                NULL,
                NULL,
                MI_FALSE);
        }
    }
    MI_PostResult(context, r);
}

void MI_CALL XYZ_ComputerSystem_CreateInstance(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_ComputerSystem* newInstance)
{
    XYZ_ComputerSystem_Post(newInstance, context);
    if (self->context && (self->types & MI_LIFECYCLE_INDICATION_CREATE))
    {
        LifecycleIndicationItemList_Add(&self->list,
            MI_LIFECYCLE_INDICATION_CREATE,
            &newInstance->__instance,
            NULL,
            NULL,
            NULL,
            NULL,
            MI_FALSE);
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL XYZ_ComputerSystem_ModifyInstance(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_ComputerSystem* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    XYZ_ComputerSystem_Post(modifiedInstance, context);
    if (self->context && (self->types & MI_LIFECYCLE_INDICATION_MODIFY))
    {
        LifecycleIndicationItemList_Add(&self->list,
            MI_LIFECYCLE_INDICATION_MODIFY,
            &modifiedInstance->__instance,
            &self->cs.__instance,
            NULL,
            NULL,
            NULL,
            MI_FALSE);
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL XYZ_ComputerSystem_DeleteInstance(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_ComputerSystem* instanceName)
{
    if (self->context && (self->types & MI_LIFECYCLE_INDICATION_DELETE))
    {
        LifecycleIndicationItemList_Add(&self->list,
            MI_LIFECYCLE_INDICATION_DELETE,
            &instanceName->__instance,
            NULL,
            NULL,
            NULL,
            NULL,
            MI_FALSE);
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL XYZ_ComputerSystem_Invoke_RequestStateChange(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_ComputerSystem* instanceName,
    const XYZ_ComputerSystem_RequestStateChange* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL XYZ_ComputerSystem_Invoke_SetPowerState(
    XYZ_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_ComputerSystem* instanceName,
    const XYZ_ComputerSystem_SetPowerState* in)
{
    /* step 1: Post CIM_InstMethodCall indication before method executed */
    if ( self->types & MI_LIFECYCLE_INDICATION_METHODCALL )
    {
        LifecycleIndicationItemList_Add(&self->list,
            MI_LIFECYCLE_INDICATION_METHODCALL,
            &instanceName->__instance,
            NULL,
            &in->__instance,
            MI_T("SetPowerState"),
            NULL,
            MI_TRUE);
        MI_LifecycleIndicationContext_PostMethodCall_Before(self->context, &instanceName->__instance, MI_T("SetPowerState"), &in->__instance);
    }

    /*
     * step 2: Implements of create function
     */

    /* step 3: Post CIM_InstMethodCall indication after method executed */
    if ( self->types & MI_LIFECYCLE_INDICATION_METHODCALL )
    {
        LifecycleIndicationItemList_Add(&self->list,
            MI_LIFECYCLE_INDICATION_METHODCALL,
            &instanceName->__instance,
            NULL,
            &in->__instance,
            MI_T("SetPowerState"),
            MI_T("0"),
            MI_FALSE);
    }
    MI_PostResult(context, MI_RESULT_OK);
}

