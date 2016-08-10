/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "LifecycleContext.h"
#include "SubMgr.h"
#include "CIM_InstCreation.h"
#include "CIM_InstDeletion.h"
#include "CIM_InstMethodCall.h"
#include "CIM_InstModification.h"
#include "CIM_InstRead.h"
#include "indicationSchema.h"
#include <base/instance.h>
#include <base/log.h>
#include <pal/format.h>
#include <pal/cpu.h>
#include <pal/palcommon.h>
#include <indication/common/indilog.h>

static const MI_Uint32 _LIFECYCLE_MAGIC = 0xFEEDCAFE;

extern MI_CONST MI_ClassDecl CIM_InstCreation_rtti;
extern MI_CONST MI_ClassDecl CIM_InstDeletion_rtti;
extern MI_CONST MI_ClassDecl CIM_InstMethodCall_rtti;
extern MI_CONST MI_ClassDecl CIM_InstModification_rtti;
extern MI_CONST MI_ClassDecl CIM_InstRead_rtti;

/*
 * This method takes advantage of the fact that the underlying layout of
 * properties within all concrete lifecycle indication classes is identical.
 * If the layout ever changes, this method must be updated (highly unlikely).
 */
MI_Result _SetCommonProperties( 
    MI_Instance* instToFill,
    const MI_Instance* sourceInstance )
{
    MI_Result result = MI_RESULT_OK;
    MI_Value value;
    PAL_Datetime now;
    
    /* 
     * Set CIM_Indication properties 
     */
// TODO: Populate values correctly
    /* MI_ConstStringField IndicationIdentifier */
    value.string = PAL_T("MSFT:IndicationIdentifier");
    result = MI_Instance_SetElement( instToFill, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_IndicationIdentifier();
        return result;
    }

    /* MI_ConstStringAField CorrelatedIndications * /
    result = MI_Instance_SetElement( instToFill, PAL_T("CorrelatedIndications"), &value, MI_STRINGA, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_CorrelatedIndications();
        return result;
    }
    */
    
    /* MI_ConstDatetimeField IndicationTime */
    if (0 == CPU_GetLocalTimestamp(&now) )
    {
        memcpy( &value.datetime, &now, sizeof(MI_Datetime) );
        result = MI_Instance_SetElement( instToFill, PAL_T("IndicationTime"), &value, MI_DATETIME, 0 );
        if (MI_RESULT_OK != result)
        {
            trace_FailedToSet_IndicationTime();
            return result;
        }
    }
    
    /* MI_ConstUint16Field PerceivedSeverity * /
    result = MI_Instance_SetElement( instToFill, PAL_T("PerceivedSeverity"), &value, MI_UINT16, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_PerceivedSeverity();
        return result;
    }

    / * MI_ConstStringField OtherSeverity * /
    result = MI_Instance_SetElement( instToFill, PAL_T("OtherSeverity"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_OtherSeverity();
        return result;
    }

    / * MI_ConstStringField IndicationFilterName * /
    result = MI_Instance_SetElement( instToFill, PAL_T("IndicationFilterName"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_IndicationFilterName();
        return result;
    }

    / * MI_ConstStringField SequenceContext * /
    result = MI_Instance_SetElement( instToFill, PAL_T("SequenceContext"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_SequenceContext();
        return result;
    }

    / * MI_ConstSint64Field SequenceNumber * /
    result = MI_Instance_SetElement( instToFill, PAL_T("SequenceNumber"), &value, MI_SINT64, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_SequenceNumber();
        return result;
    }

    / *
     * Set CIM_InstIndication properties
     * /
    
    / * MI_ConstReferenceField SourceInstance */
    if (sourceInstance)
    {
        value.reference = (MI_Instance*)sourceInstance;
        result = MI_Instance_SetElement( instToFill, PAL_T("SourceInstance"), &value, MI_INSTANCE, 0 );
        if (MI_RESULT_OK != result)
        {
            trace_FailedToSet_SourceInstance();
            return result;
        }
    }

    /* MI_ConstStringField SourceInstanceModelPath * /
    result = MI_Instance_SetElement( instToFill, PAL_T("SourceInstanceModelPath"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_SourceInstanceModelPath();
        return result;
    }

    / * MI_ConstStringField SourceInstanceHost * /
    result = MI_Instance_SetElement( instToFill, PAL_T("SourceInstanceHost"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_SourceInstanceHost();
        return result;
    }
    */
    return MI_RESULT_OK;
}

MI_Result _PostToAllSubscribers(
    _In_ SubscriptionManager* subMgr,
    _In_ MI_Instance* instanceToPost,
    _In_ MI_Uint32 postTargetType )
{
    MI_Boolean atLeastOneDelivered = MI_FALSE;
    SubMgrSubscriptionPtr* sublist;
    MI_Result r;
    size_t count = 0;
    size_t i;

    r = SubMgr_GetSubscriptionList(subMgr, &sublist, &count);
    if ( r != MI_RESULT_OK )
        return r;

    /* For each subscription, use its context to PostInstance of instCreation. */
    r = MI_RESULT_FAILED;
    for (i = 0; i < count; i++)
    {
        /*
         * This action is done through Context to:
         * 1. Conform to the existing API
         * 2. Avoid exposure of internal code via Context.h
         * 3. Reuse indication posting code
         *
         * This is a best-effort action.  Intermediate failures will be 
         * ignored.
         */
        SubscriptionContext* ctx = sublist[i]->subscribeCtx;
        if (0 != (postTargetType & LifeContext_ConvertSupportedType( sublist[i]->msg->targetType )) )
        {
            if (MI_RESULT_OK == (r = MI_Context_PostIndication( &ctx->baseCtx.base, instanceToPost, 0, NULL ) ) )
            {
                atLeastOneDelivered = MI_TRUE;
            }
        }
        SubMgrSubscription_Release(sublist[i]);
    }
    return (atLeastOneDelivered ? MI_RESULT_OK : r);
}

/*
 * Groups all common indication preparation actions for re-use.  This
 * function is targetted for Post handlers that set additional properties
 * on the indication prior to forwarding it.
 * 
 * Note: The caller must call MI_Instance_Destruct on instanceToPost to ensure
 *       proper cleanup.
 */
MI_Result _CommonIndicationPrep(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ MI_Instance* indicationToPost,
    _In_ const MI_Instance* sourceInstance,
    _In_ const MI_ClassDecl* classDecl )
{
    MI_Result result = MI_RESULT_OK;
    LifecycleContext* lifeContext = (LifecycleContext*)context;
    SubscriptionManager* subMgr = lifeContext->provider->subMgr;

    /* Basic validity checks to prevent unnecessary work: don't create the
     * indication if there is no listener to receive it. */
    if ( (MI_FALSE == SubMgr_IsEnabled ( subMgr )) ||
         (MI_TRUE == SubMgr_IsSubListEmpty ( subMgr )))
    {
        trace_LifecycleContext_Post_InvalidState();
        return MI_RESULT_FAILED;
    }

    /* Create indication to post based on the input instance */

    result = Instance_Construct( indicationToPost, classDecl, NULL );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToConstructInstance(tcs(classDecl->name));
        return result;
    }

    result = _SetCommonProperties( indicationToPost, sourceInstance );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_CommonProperties(tcs(classDecl->name));
        return result;
    }

    return result;
}

/*
 * Wrapper for handling indications with no additional properties beyond
 * those from CIM_Indication and CIM_InstIndication.
 */
MI_Result _CommonPostSimple(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ MI_Instance* indicationToPost,
    _In_ const MI_Instance* sourceInstance,
    _In_ const MI_ClassDecl* classDecl,
    _In_ MI_Uint32 postTargetType )
{
    MI_Result result = MI_RESULT_OK;
    
    if (!context || !sourceInstance || ((LifecycleContext*)context)->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameterForClass(tcs(classDecl->name));
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    result = _CommonIndicationPrep( context, indicationToPost, sourceInstance, classDecl );
    if (MI_RESULT_OK != result)
    {
        goto Lifecycle_CommonEnd;
    }

    result = _PostToAllSubscribers( ((LifecycleContext*)context)->provider->subMgr, indicationToPost, postTargetType );
 
Lifecycle_CommonEnd:
    if (indicationToPost->ft)
    {
        MI_Instance_Destruct( indicationToPost );
    }
    return result;
}

MI_Result _PostCreate(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ const MI_Instance* instance)
{
    CIM_InstCreation instCreation;

    memset( &instCreation, 0, sizeof(CIM_InstCreation) );

    return _CommonPostSimple( context, &instCreation.__instance, instance, &CIM_InstCreation_rtti, MI_LIFECYCLE_INDICATION_CREATE );
}

MI_Result _PostModify(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ const MI_Instance* originalInstance,
    _In_ const MI_Instance* instance)
{
    MI_Result result = MI_RESULT_OK;
    CIM_InstModification instModification;
    MI_Value value;

    if (!context || !originalInstance || !instance || ((LifecycleContext*)context)->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameterForClass(tcs(CIM_InstModification_rtti.name));
        return MI_RESULT_INVALID_PARAMETER;
    }

    memset( &instModification, 0, sizeof(CIM_InstModification) );

    result = _CommonIndicationPrep( context, &instModification.__instance, instance, &CIM_InstModification_rtti );
    if (MI_RESULT_OK != result)
    {
        goto Lifecycle_ModifyEnd;
    }

    /* MI_ConstReferenceField PreviousInstance */
    value.reference = (MI_Instance*)originalInstance;
    result = MI_Instance_SetElement( &instModification.__instance, PAL_T("PreviousInstance"), &value, MI_INSTANCE, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_PreviousInstance();
        goto Lifecycle_ModifyEnd;
    }

    result = _PostToAllSubscribers( ((LifecycleContext*)context)->provider->subMgr, &instModification.__instance, MI_LIFECYCLE_INDICATION_MODIFY);
 
Lifecycle_ModifyEnd:
    if (instModification.__instance.ft)
    {
        MI_Instance_Destruct( &instModification.__instance );
    }
    return result;
}

MI_Result _PostDelete(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ const MI_Instance* originalInstance)
{
    CIM_InstDeletion instDeletion;

    memset( &instDeletion, 0, sizeof(CIM_InstDeletion) );

    return _CommonPostSimple( context, &instDeletion.__instance, originalInstance, &CIM_InstDeletion_rtti, MI_LIFECYCLE_INDICATION_DELETE );
}

MI_Result _PostRead(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ const MI_Instance* instance)
{
    CIM_InstRead instRead;

    memset( &instRead, 0, sizeof(CIM_InstRead) );

    return _CommonPostSimple( context, &instRead.__instance, instance, &CIM_InstRead_rtti, MI_LIFECYCLE_INDICATION_READ );
}

MI_Result _PostMethodCall(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ const MI_Instance* instance,
    _In_z_ const MI_Char* methodName,
    _In_ MI_Boolean precall,
    _In_opt_ const MI_Instance* parameter,
    _In_opt_z_ const MI_Char* returnvalue)
{
    MI_Result result = MI_RESULT_OK;
    CIM_InstMethodCall instMethodCall;
    MI_Value value;

    if (!context || !instance || !methodName || ((LifecycleContext*)context)->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameterForClass(tcs(CIM_InstMethodCall_rtti.name));
        return MI_RESULT_INVALID_PARAMETER;
    }

    memset( &instMethodCall, 0, sizeof(CIM_InstMethodCall) );
    
    result = _CommonIndicationPrep( context, &instMethodCall.__instance, instance, &CIM_InstMethodCall_rtti );
    if (MI_RESULT_OK != result)
    {
        goto Lifecycle_MethodCallEnd;
    }

    /* MI_ConstStringField MethodName */
    value.string = (MI_Char*)methodName;
    result = MI_Instance_SetElement( &instMethodCall.__instance, PAL_T("MethodName"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_MethodName();
        goto Lifecycle_MethodCallEnd;
    }
    
    /* MI_ConstReferenceField MethodParameters */
    value.reference = (MI_Instance*)parameter;
    result = MI_Instance_SetElement( &instMethodCall.__instance, PAL_T("MethodParameters"), &value, MI_INSTANCE, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_MethodParameters();
        goto Lifecycle_MethodCallEnd;
    }
    
    /* MI_ConstStringField ReturnValue */
    value.string = (MI_Char*)returnvalue;
    result = MI_Instance_SetElement( &instMethodCall.__instance, PAL_T("ReturnValue"), &value, MI_STRING, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_ReturnValue();
        goto Lifecycle_MethodCallEnd;
    }

    /* MI_ConstBooleanField PreCall */
    value.boolean = precall;
    result = MI_Instance_SetElement( &instMethodCall.__instance, PAL_T("PreCall"), &value, MI_BOOLEAN, 0 );
    if (MI_RESULT_OK != result)
    {
        trace_FailedToSet_PreCall();
        goto Lifecycle_MethodCallEnd;
    }

    result = _PostToAllSubscribers( ((LifecycleContext*)context)->provider->subMgr, &instMethodCall.__instance, MI_LIFECYCLE_INDICATION_METHODCALL);
 
Lifecycle_MethodCallEnd:
    if (instMethodCall.__instance.ft)
    {
        MI_Instance_Destruct( &instMethodCall.__instance );
    }
    return result;
}

MI_Result _PostResult(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ MI_Result result)
{
    LifecycleContext* lifeContext = (LifecycleContext*)context;
        
    if (!context || lifeContext->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }

    trace_DisablingLifeCycleIndicationsForClass(tcs(lifeContext->provider->classDecl->name));

    return Provider_TerminateIndication( lifeContext->provider, result, NULL, NULL );
}

// TODO: Only make this callable during provider load?
MI_Result MI_CALL _SetSupportedTypes(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ MI_Uint32 types)
{
    LifecycleContext* lifeContext = (LifecycleContext*)context;
        
    if (!context || lifeContext->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    lifeContext->supportedTypesFromProv = types;
    
    return MI_RESULT_OK;
}

MI_Result _GetLifecycleIndicationTypes(
    _In_ MI_LifecycleIndicationContext* context,
    _Out_ MI_Uint32* types)
{
    LifecycleContext* lifeContext = (LifecycleContext*)context;
        
    if (!context || !types || lifeContext->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    *types = lifeContext->supportedTypesFromProv;
    
    return MI_RESULT_OK;
}

MI_Result _RegisterLifecycleCallback(
    _In_ MI_LifecycleIndicationContext* context,
    _In_ MI_LifecycleIndicationCallback callback,
    _In_opt_ void* callbackData)
{
    LifecycleContext* lifeContext = (LifecycleContext*)context;
        
    if (!context || !callback || lifeContext->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }

    lifeContext->lifecycleCallback = callback;
    lifeContext->callbackData = callbackData;
    
    return MI_RESULT_OK;
}

static MI_Result _ValidateContext(MI_LifecycleIndicationContext* self_)
{
    LifecycleContext* lifeContext = (LifecycleContext*)self_;
    if (!self_ || lifeContext->magic != _LIFECYCLE_MAGIC)
    {
        trace_NullInputParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _ConstructInstance(
    MI_LifecycleIndicationContext* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
    MI_Result r = _ValidateContext(self_);
    if (r == MI_RESULT_OK)
        return Instance_Construct(instance, classDecl, NULL);
    return r;
}

static MI_Result MI_CALL _ConstructParameters(
    MI_LifecycleIndicationContext* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance* instance)
{
    MI_Result r = _ValidateContext(self_);
    if (r == MI_RESULT_OK)
        return Parameters_Init(instance, methodDecl, NULL);
    return r;
}

static MI_Result MI_CALL _NewInstance(
    MI_LifecycleIndicationContext* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance** instance)
{
    MI_Result r = _ValidateContext(self_);
    if (r == MI_RESULT_OK)
        return Instance_New(instance, classDecl, NULL);
    return r;
}

static MI_Result MI_CALL _NewDynamicInstance(
    MI_LifecycleIndicationContext* self_,
    const ZChar* className,
    MI_Uint32 flags,
    MI_Instance** instance)
{
    MI_Result r = _ValidateContext(self_);
    if (r == MI_RESULT_OK)
        return Instance_NewDynamic(instance, className, flags, NULL);
    return r;
}

static MI_Result MI_CALL _NewParameters(
    MI_LifecycleIndicationContext* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance** instance)
{
    
    return Parameters_New(instance, methodDecl, NULL);
}

MI_LifecycleIndicationContextFT __mi_lifecycle_contextFT =
{
    _PostCreate,
    _PostModify,
    _PostDelete,
    _PostRead,
    _PostMethodCall,
    _PostResult,
    _ConstructInstance,
    _ConstructParameters,
    _NewInstance,
    _NewDynamicInstance,
    _NewParameters,
    _SetSupportedTypes,
    _GetLifecycleIndicationTypes,
    _RegisterLifecycleCallback
};

LifecycleContext* LifeContext_New()
{
    LifecycleContext* context = (LifecycleContext*)PAL_Calloc(1, sizeof(LifecycleContext));
    if (!context)
        LOGD_ALLOC_OOM;
    return context;
}

_Use_decl_annotations_
void LifeContext_Delete(
    LifecycleContext* context )
{
    if (context)
    {
        memset(context, 0xFF, sizeof(LifecycleContext));
        PAL_Free(context);
    }
}

_Use_decl_annotations_
void LifeContext_Init(
    LifecycleContext* context,
    Provider* provider )
{
    DEBUG_ASSERT ( provider && provider->subMgr );

    context->base.ft = &__mi_lifecycle_contextFT;
    context->magic = _LIFECYCLE_MAGIC;
    context->provider = provider;
    context->supportedTypesFromProv = MI_LIFECYCLE_INDICATION_ALL;
}

/* 
 * Converts SubscriptionTargetType enum values to bit flags that are compatible
 * with the MI API's type field.
 */
_Use_decl_annotations_
MI_Uint32 LifeContext_ConvertSupportedType(
    SubscriptionTargetType type )
{
    MI_Uint32 miType = MI_LIFECYCLE_INDICATION_NONE;
    switch(type)
    {
        case SUBSCRIP_TARGET_LIFECYCLE_CREATE:
            miType = MI_LIFECYCLE_INDICATION_CREATE;
            break;
        case SUBSCRIP_TARGET_LIFECYCLE_MODIFY:
            miType = MI_LIFECYCLE_INDICATION_MODIFY;
            break;
        case SUBSCRIP_TARGET_LIFECYCLE_DELETE:
            miType = MI_LIFECYCLE_INDICATION_DELETE;
            break;
        case SUBSCRIP_TARGET_LIFECYCLE_READ:
            miType = MI_LIFECYCLE_INDICATION_READ;
            break;
        case SUBSCRIP_TARGET_LIFECYCLE_METHODCALL:
            miType = MI_LIFECYCLE_INDICATION_METHODCALL;
            break;
        case SUBSCRIP_TARGET_LIFECYCLE_ALL:
            miType = MI_LIFECYCLE_INDICATION_ALL;
            break;
        /* Fallthorugh intentional */
        case SUBSCRIP_TARGET_UNSUPPORTED:
        case SUBSCRIP_TARGET_DEFAULT:
        default:
            miType = MI_LIFECYCLE_INDICATION_NONE;
    }
    return miType;
}

/*
 * In this check, any requested bits that are not supported will get zeroed,
 * causing the comparison against the original value to fail.
 */
_Use_decl_annotations_
MI_Boolean LifeContext_IsTypeSupported(
    LifecycleContext* context,
    MI_Uint32 supportedTypeToCheck )
{
    MI_Uint32 convertedToMiType = LifeContext_ConvertSupportedType( supportedTypeToCheck );

    if ( MI_LIFECYCLE_INDICATION_NONE == context->supportedTypesFromProv ||
         MI_LIFECYCLE_INDICATION_NONE == convertedToMiType )
    {
        return MI_FALSE;
    }

    if ( context->supportedTypesFromProv & convertedToMiType )
    {
        return MI_TRUE;
    }
    else
    {
        return MI_FALSE;
    }
}

// TODO: return result here and check against the provider's advertised type.
_Use_decl_annotations_
void LifeContext_UpdateSupportedTypes(
    LifecycleContext* context )
{
    MI_Uint32 indicationType = MI_LIFECYCLE_INDICATION_NONE;
    SubscriptionManager* subMgr = NULL;
    SubMgrSubscription* sub = NULL;

    if (NULL == context->lifecycleCallback)
    {
        return;
    }

    /* Iterate through the subscriptions and gather the various subscriptions
     * additively. */
    subMgr = context->provider->subMgr;
    for (sub = (SubMgrSubscription*)subMgr->subscrList.head; sub; sub = sub->next)
    {
        indicationType |= LifeContext_ConvertSupportedType( sub->msg->targetType );
        if (MI_LIFECYCLE_INDICATION_ALL == indicationType)
        {
            break; /* All bits are set.  There is no point to continuing the search. */
        }
    }

    if (indicationType != context->supportedTypesAggr)
    {
        /* A change in registration occurred, so notify the provider. */
        context->supportedTypesAggr = indicationType;
        
        context->lifecycleCallback( indicationType, context->callbackData );
    }
}

