/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_ProcessCreation_h
#define _ABC_ProcessCreation_h

#include <MI.h>
#include "CIM_InstCreation.h"

/*
**==============================================================================
**
** ABC_ProcessCreation [ABC_ProcessCreation]
**
** Keys:
**
**==============================================================================
*/

typedef struct _ABC_ProcessCreation /* extends CIM_InstCreation */
{
    MI_Instance __instance;
    /* CIM_Indication properties */
    MI_ConstStringField IndicationIdentifier;
    MI_ConstStringAField CorrelatedIndications;
    MI_ConstDatetimeField IndicationTime;
    MI_ConstUint16Field PerceivedSeverity;
    MI_ConstStringField OtherSeverity;
    MI_ConstStringField IndicationFilterName;
    MI_ConstStringField SequenceContext;
    MI_ConstSint64Field SequenceNumber;
    /* CIM_InstIndication properties */
    MI_ConstReferenceField SourceInstance;
    MI_ConstStringField SourceInstanceModelPath;
    MI_ConstStringField SourceInstanceHost;
    /* CIM_InstCreation properties */
    /* ABC_ProcessCreation properties */
}
ABC_ProcessCreation;

typedef struct _ABC_ProcessCreation_Ref
{
    ABC_ProcessCreation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ProcessCreation_Ref;

typedef struct _ABC_ProcessCreation_ConstRef
{
    MI_CONST ABC_ProcessCreation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ProcessCreation_ConstRef;

typedef struct _ABC_ProcessCreation_Array
{
    struct _ABC_ProcessCreation** data;
    MI_Uint32 size;
}
ABC_ProcessCreation_Array;

typedef struct _ABC_ProcessCreation_ConstArray
{
    struct _ABC_ProcessCreation MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_ProcessCreation_ConstArray;

typedef struct _ABC_ProcessCreation_ArrayRef
{
    ABC_ProcessCreation_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ProcessCreation_ArrayRef;

typedef struct _ABC_ProcessCreation_ConstArrayRef
{
    ABC_ProcessCreation_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ProcessCreation_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_ProcessCreation_rtti;

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Construct(
    ABC_ProcessCreation* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_ProcessCreation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clone(
    const ABC_ProcessCreation* self,
    ABC_ProcessCreation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_ProcessCreation_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_ProcessCreation_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Destruct(ABC_ProcessCreation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Delete(ABC_ProcessCreation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Post(
    const ABC_ProcessCreation* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_IndicationIdentifier(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_IndicationIdentifier(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_IndicationIdentifier(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_CorrelatedIndications(
    ABC_ProcessCreation* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_CorrelatedIndications(
    ABC_ProcessCreation* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_CorrelatedIndications(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_IndicationTime(
    ABC_ProcessCreation* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_IndicationTime(
    ABC_ProcessCreation* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_PerceivedSeverity(
    ABC_ProcessCreation* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_PerceivedSeverity(
    ABC_ProcessCreation* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_OtherSeverity(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_OtherSeverity(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_OtherSeverity(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_IndicationFilterName(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_IndicationFilterName(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_IndicationFilterName(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_SequenceContext(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_SequenceContext(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_SequenceContext(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_SequenceNumber(
    ABC_ProcessCreation* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_SequenceNumber(
    ABC_ProcessCreation* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_SourceInstance(
    ABC_ProcessCreation* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_SourceInstance(
    ABC_ProcessCreation* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_SourceInstance(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_SourceInstanceModelPath(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_SourceInstanceModelPath(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_SourceInstanceModelPath(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Set_SourceInstanceHost(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_SetPtr_SourceInstanceHost(
    ABC_ProcessCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ProcessCreation_Clear_SourceInstanceHost(
    ABC_ProcessCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

/*
**==============================================================================
**
** ABC_ProcessCreation provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_ProcessCreation_Self ABC_ProcessCreation_Self;

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_Load(
    ABC_ProcessCreation_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_Unload(
    ABC_ProcessCreation_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_EnableIndications(
    ABC_ProcessCreation_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_DisableIndications(
    ABC_ProcessCreation_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_Subscribe(
    ABC_ProcessCreation_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL ABC_ProcessCreation_Unsubscribe(
    ABC_ProcessCreation_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _ABC_ProcessCreation_h */
