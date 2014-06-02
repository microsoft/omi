/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_Indication_h
#define _L_Indication_h

#include <MI.h>
#include "CIM_Indication.h"

/*
**==============================================================================
**
** L_Indication [L_Indication]
**
** Keys:
**
**==============================================================================
*/

typedef struct _L_Indication /* extends CIM_Indication */
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
    /* L_Indication properties */
    MI_ConstUint32Field id;
    MI_ConstStringField message;
}
L_Indication;

typedef struct _L_Indication_Ref
{
    L_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Indication_Ref;

typedef struct _L_Indication_ConstRef
{
    MI_CONST L_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Indication_ConstRef;

typedef struct _L_Indication_Array
{
    struct _L_Indication** data;
    MI_Uint32 size;
}
L_Indication_Array;

typedef struct _L_Indication_ConstArray
{
    struct _L_Indication MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_Indication_ConstArray;

typedef struct _L_Indication_ArrayRef
{
    L_Indication_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Indication_ArrayRef;

typedef struct _L_Indication_ConstArrayRef
{
    L_Indication_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Indication_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_Indication_rtti;

MI_INLINE MI_Result MI_CALL L_Indication_Construct(
    L_Indication* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_Indication_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clone(
    const L_Indication* self,
    L_Indication** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_Indication_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_Indication_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_Indication_Destruct(L_Indication* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Indication_Delete(L_Indication* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Indication_Post(
    const L_Indication* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_IndicationIdentifier(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_IndicationIdentifier(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_IndicationIdentifier(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_CorrelatedIndications(
    L_Indication* self,
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

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_CorrelatedIndications(
    L_Indication* self,
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

MI_INLINE MI_Result MI_CALL L_Indication_Clear_CorrelatedIndications(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_IndicationTime(
    L_Indication* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_IndicationTime(
    L_Indication* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_PerceivedSeverity(
    L_Indication* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_PerceivedSeverity(
    L_Indication* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_OtherSeverity(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_OtherSeverity(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_OtherSeverity(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_IndicationFilterName(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_IndicationFilterName(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_IndicationFilterName(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_SequenceContext(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_SequenceContext(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_SequenceContext(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_SequenceNumber(
    L_Indication* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_SequenceNumber(
    L_Indication* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_id(
    L_Indication* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_id(
    L_Indication* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Indication_Set_message(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Indication_SetPtr_message(
    L_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Indication_Clear_message(
    L_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_Result MI_CALL L_Indication_SetIndicationProperties(
    void* cfg,
    MI_Instance* indication);

#endif /* _L_Indication_h */
