/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_IndicationConfig_h
#define _Test_IndicationConfig_h

#include <MI.h>

/*
**==============================================================================
**
** Test_IndicationConfig [Test_IndicationConfig]
**
** Keys:
**    className
**
**==============================================================================
*/

typedef struct _Test_IndicationConfig
{
    MI_Instance __instance;
    /* Test_IndicationConfig properties */
    /*KEY*/ MI_ConstStringField className;
    MI_ConstStringField configFilepath;
    MI_ConstUint32Field testGroup;
    MI_ConstUint32Field intervalMS;
    MI_ConstUint32Field failAfterCount;
    MI_ConstUint32Field failResult;
    MI_ConstUint32Field initBehavior;
    MI_ConstUint32Field initResultCode;
    MI_ConstUint32Field initTimeoutMS;
    MI_ConstUint32Field finalizeBehavior;
    MI_ConstUint32Field finalizeResultCode;
    MI_ConstUint32Field postBehavior;
    MI_ConstUint32Field miscTestSubGroup;
    MI_ConstStringField subscribeBookmark;
    MI_ConstStringField providerBookmark;
    MI_ConstStringField dialect;
    MI_ConstStringField expression;
    MI_ConstUint32Field evalResult;
    MI_ConstUint32Field logLoadUnloadCall;
    MI_ConstUint32Field supportedSubscriptionTypes;
    MI_ConstUint32Field currentSubscriptionTypes;
    MI_ConstStringAField apicallseq;
}
Test_IndicationConfig;

typedef struct _Test_IndicationConfig_Ref
{
    Test_IndicationConfig* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_IndicationConfig_Ref;

typedef struct _Test_IndicationConfig_ConstRef
{
    MI_CONST Test_IndicationConfig* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_IndicationConfig_ConstRef;

typedef struct _Test_IndicationConfig_Array
{
    struct _Test_IndicationConfig** data;
    MI_Uint32 size;
}
Test_IndicationConfig_Array;

typedef struct _Test_IndicationConfig_ConstArray
{
    struct _Test_IndicationConfig MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_IndicationConfig_ConstArray;

typedef struct _Test_IndicationConfig_ArrayRef
{
    Test_IndicationConfig_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_IndicationConfig_ArrayRef;

typedef struct _Test_IndicationConfig_ConstArrayRef
{
    Test_IndicationConfig_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_IndicationConfig_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_IndicationConfig_rtti;

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Construct(
    Test_IndicationConfig* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_IndicationConfig_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clone(
    const Test_IndicationConfig* self,
    Test_IndicationConfig** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_IndicationConfig_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_IndicationConfig_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Destruct(Test_IndicationConfig* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Delete(Test_IndicationConfig* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Post(
    const Test_IndicationConfig* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_className(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_className(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_className(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_configFilepath(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_configFilepath(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_configFilepath(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_testGroup(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->testGroup)->value = x;
    ((MI_Uint32Field*)&self->testGroup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_testGroup(
    Test_IndicationConfig* self)
{
    memset((void*)&self->testGroup, 0, sizeof(self->testGroup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_intervalMS(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->intervalMS)->value = x;
    ((MI_Uint32Field*)&self->intervalMS)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_intervalMS(
    Test_IndicationConfig* self)
{
    memset((void*)&self->intervalMS, 0, sizeof(self->intervalMS));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_failAfterCount(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->failAfterCount)->value = x;
    ((MI_Uint32Field*)&self->failAfterCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_failAfterCount(
    Test_IndicationConfig* self)
{
    memset((void*)&self->failAfterCount, 0, sizeof(self->failAfterCount));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_failResult(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->failResult)->value = x;
    ((MI_Uint32Field*)&self->failResult)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_failResult(
    Test_IndicationConfig* self)
{
    memset((void*)&self->failResult, 0, sizeof(self->failResult));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_initBehavior(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->initBehavior)->value = x;
    ((MI_Uint32Field*)&self->initBehavior)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_initBehavior(
    Test_IndicationConfig* self)
{
    memset((void*)&self->initBehavior, 0, sizeof(self->initBehavior));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_initResultCode(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->initResultCode)->value = x;
    ((MI_Uint32Field*)&self->initResultCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_initResultCode(
    Test_IndicationConfig* self)
{
    memset((void*)&self->initResultCode, 0, sizeof(self->initResultCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_initTimeoutMS(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->initTimeoutMS)->value = x;
    ((MI_Uint32Field*)&self->initTimeoutMS)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_initTimeoutMS(
    Test_IndicationConfig* self)
{
    memset((void*)&self->initTimeoutMS, 0, sizeof(self->initTimeoutMS));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_finalizeBehavior(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->finalizeBehavior)->value = x;
    ((MI_Uint32Field*)&self->finalizeBehavior)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_finalizeBehavior(
    Test_IndicationConfig* self)
{
    memset((void*)&self->finalizeBehavior, 0, sizeof(self->finalizeBehavior));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_finalizeResultCode(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->finalizeResultCode)->value = x;
    ((MI_Uint32Field*)&self->finalizeResultCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_finalizeResultCode(
    Test_IndicationConfig* self)
{
    memset((void*)&self->finalizeResultCode, 0, sizeof(self->finalizeResultCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_postBehavior(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->postBehavior)->value = x;
    ((MI_Uint32Field*)&self->postBehavior)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_postBehavior(
    Test_IndicationConfig* self)
{
    memset((void*)&self->postBehavior, 0, sizeof(self->postBehavior));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_miscTestSubGroup(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->miscTestSubGroup)->value = x;
    ((MI_Uint32Field*)&self->miscTestSubGroup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_miscTestSubGroup(
    Test_IndicationConfig* self)
{
    memset((void*)&self->miscTestSubGroup, 0, sizeof(self->miscTestSubGroup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_subscribeBookmark(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_subscribeBookmark(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_subscribeBookmark(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_providerBookmark(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_providerBookmark(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_providerBookmark(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_dialect(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_dialect(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_dialect(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_expression(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_expression(
    Test_IndicationConfig* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_expression(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_evalResult(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->evalResult)->value = x;
    ((MI_Uint32Field*)&self->evalResult)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_evalResult(
    Test_IndicationConfig* self)
{
    memset((void*)&self->evalResult, 0, sizeof(self->evalResult));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_logLoadUnloadCall(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->logLoadUnloadCall)->value = x;
    ((MI_Uint32Field*)&self->logLoadUnloadCall)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_logLoadUnloadCall(
    Test_IndicationConfig* self)
{
    memset((void*)&self->logLoadUnloadCall, 0, sizeof(self->logLoadUnloadCall));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_supportedSubscriptionTypes(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->supportedSubscriptionTypes)->value = x;
    ((MI_Uint32Field*)&self->supportedSubscriptionTypes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_supportedSubscriptionTypes(
    Test_IndicationConfig* self)
{
    memset((void*)&self->supportedSubscriptionTypes, 0, sizeof(self->supportedSubscriptionTypes));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_currentSubscriptionTypes(
    Test_IndicationConfig* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->currentSubscriptionTypes)->value = x;
    ((MI_Uint32Field*)&self->currentSubscriptionTypes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_currentSubscriptionTypes(
    Test_IndicationConfig* self)
{
    memset((void*)&self->currentSubscriptionTypes, 0, sizeof(self->currentSubscriptionTypes));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Set_apicallseq(
    Test_IndicationConfig* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_SetPtr_apicallseq(
    Test_IndicationConfig* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_IndicationConfig_Clear_apicallseq(
    Test_IndicationConfig* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

/*
**==============================================================================
**
** Test_IndicationConfig provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_IndicationConfig_Self Test_IndicationConfig_Self;

MI_EXTERN_C void MI_CALL Test_IndicationConfig_Load(
    Test_IndicationConfig_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_Unload(
    Test_IndicationConfig_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_EnumerateInstances(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_GetInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_CreateInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* newInstance);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_ModifyInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_IndicationConfig_DeleteInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* instanceName);


#endif /* _Test_IndicationConfig_h */
