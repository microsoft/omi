/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Indication_h
#define _CIM_Indication_h

#include <MI.h>

/*
**==============================================================================
**
** CIM_Indication [CIM_Indication]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Indication
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
}
CIM_Indication;

typedef struct _CIM_Indication_Ref
{
    CIM_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Indication_Ref;

typedef struct _CIM_Indication_ConstRef
{
    MI_CONST CIM_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Indication_ConstRef;

typedef struct _CIM_Indication_Array
{
    struct _CIM_Indication** data;
    MI_Uint32 size;
}
CIM_Indication_Array;

typedef struct _CIM_Indication_ConstArray
{
    struct _CIM_Indication MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Indication_ConstArray;

typedef struct _CIM_Indication_ArrayRef
{
    CIM_Indication_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Indication_ArrayRef;

typedef struct _CIM_Indication_ConstArrayRef
{
    CIM_Indication_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Indication_ConstArrayRef;

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_IndicationIdentifier(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_SetPtr_IndicationIdentifier(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_IndicationIdentifier(
    CIM_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_CorrelatedIndications(
    CIM_Indication* self,
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

MI_INLINE MI_Result MI_CALL CIM_Indication_SetPtr_CorrelatedIndications(
    CIM_Indication* self,
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

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_CorrelatedIndications(
    CIM_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_IndicationTime(
    CIM_Indication* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_IndicationTime(
    CIM_Indication* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_PerceivedSeverity(
    CIM_Indication* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_PerceivedSeverity(
    CIM_Indication* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_OtherSeverity(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_SetPtr_OtherSeverity(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_OtherSeverity(
    CIM_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_IndicationFilterName(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_SetPtr_IndicationFilterName(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_IndicationFilterName(
    CIM_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_SequenceContext(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_SetPtr_SequenceContext(
    CIM_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_SequenceContext(
    CIM_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Set_SequenceNumber(
    CIM_Indication* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Indication_Clear_SequenceNumber(
    CIM_Indication* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}


#endif /* _CIM_Indication_h */
