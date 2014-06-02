/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_InstCreation_h
#define _CIM_InstCreation_h

#include <MI.h>
#include "CIM_InstIndication.h"

/*
**==============================================================================
**
** CIM_InstCreation [CIM_InstCreation]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_InstCreation /* extends CIM_InstIndication */
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
}
CIM_InstCreation;

typedef struct _CIM_InstCreation_Ref
{
    CIM_InstCreation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstCreation_Ref;

typedef struct _CIM_InstCreation_ConstRef
{
    MI_CONST CIM_InstCreation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstCreation_ConstRef;

typedef struct _CIM_InstCreation_Array
{
    struct _CIM_InstCreation** data;
    MI_Uint32 size;
}
CIM_InstCreation_Array;

typedef struct _CIM_InstCreation_ConstArray
{
    struct _CIM_InstCreation MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_InstCreation_ConstArray;

typedef struct _CIM_InstCreation_ArrayRef
{
    CIM_InstCreation_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstCreation_ArrayRef;

typedef struct _CIM_InstCreation_ConstArrayRef
{
    CIM_InstCreation_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstCreation_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstCreation_rtti;

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Construct(
    CIM_InstCreation* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_InstCreation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clone(
    const CIM_InstCreation* self,
    CIM_InstCreation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_InstCreation_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_InstCreation_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Destruct(CIM_InstCreation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Delete(CIM_InstCreation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Post(
    const CIM_InstCreation* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_IndicationIdentifier(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_IndicationIdentifier(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_IndicationIdentifier(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_CorrelatedIndications(
    CIM_InstCreation* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_CorrelatedIndications(
    CIM_InstCreation* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_CorrelatedIndications(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_IndicationTime(
    CIM_InstCreation* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_IndicationTime(
    CIM_InstCreation* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_PerceivedSeverity(
    CIM_InstCreation* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_PerceivedSeverity(
    CIM_InstCreation* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_OtherSeverity(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_OtherSeverity(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_OtherSeverity(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_IndicationFilterName(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_IndicationFilterName(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_IndicationFilterName(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_SequenceContext(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_SequenceContext(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_SequenceContext(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_SequenceNumber(
    CIM_InstCreation* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_SequenceNumber(
    CIM_InstCreation* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_SourceInstance(
    CIM_InstCreation* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_SourceInstance(
    CIM_InstCreation* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_SourceInstance(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_SourceInstanceModelPath(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_SourceInstanceModelPath(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_SourceInstanceModelPath(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Set_SourceInstanceHost(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_SetPtr_SourceInstanceHost(
    CIM_InstCreation* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstCreation_Clear_SourceInstanceHost(
    CIM_InstCreation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}


#endif /* _CIM_InstCreation_h */
