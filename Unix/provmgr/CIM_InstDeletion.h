/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_InstDeletion_h
#define _CIM_InstDeletion_h

#include <MI.h>
#include "CIM_InstIndication.h"

/*
**==============================================================================
**
** CIM_InstDeletion [CIM_InstDeletion]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_InstDeletion /* extends CIM_InstIndication */
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
    /* CIM_InstDeletion properties */
}
CIM_InstDeletion;

typedef struct _CIM_InstDeletion_Ref
{
    CIM_InstDeletion* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstDeletion_Ref;

typedef struct _CIM_InstDeletion_ConstRef
{
    MI_CONST CIM_InstDeletion* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstDeletion_ConstRef;

typedef struct _CIM_InstDeletion_Array
{
    struct _CIM_InstDeletion** data;
    MI_Uint32 size;
}
CIM_InstDeletion_Array;

typedef struct _CIM_InstDeletion_ConstArray
{
    struct _CIM_InstDeletion MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_InstDeletion_ConstArray;

typedef struct _CIM_InstDeletion_ArrayRef
{
    CIM_InstDeletion_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstDeletion_ArrayRef;

typedef struct _CIM_InstDeletion_ConstArrayRef
{
    CIM_InstDeletion_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstDeletion_ConstArrayRef;

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_IndicationIdentifier(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_IndicationIdentifier(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_IndicationIdentifier(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_CorrelatedIndications(
    CIM_InstDeletion* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_CorrelatedIndications(
    CIM_InstDeletion* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_CorrelatedIndications(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_IndicationTime(
    CIM_InstDeletion* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_IndicationTime(
    CIM_InstDeletion* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_PerceivedSeverity(
    CIM_InstDeletion* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_PerceivedSeverity(
    CIM_InstDeletion* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_OtherSeverity(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_OtherSeverity(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_OtherSeverity(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_IndicationFilterName(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_IndicationFilterName(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_IndicationFilterName(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_SequenceContext(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_SequenceContext(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_SequenceContext(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_SequenceNumber(
    CIM_InstDeletion* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_SequenceNumber(
    CIM_InstDeletion* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_SourceInstance(
    CIM_InstDeletion* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_SourceInstance(
    CIM_InstDeletion* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_SourceInstance(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_SourceInstanceModelPath(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_SourceInstanceModelPath(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_SourceInstanceModelPath(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Set_SourceInstanceHost(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_SetPtr_SourceInstanceHost(
    CIM_InstDeletion* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstDeletion_Clear_SourceInstanceHost(
    CIM_InstDeletion* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}


#endif /* _CIM_InstDeletion_h */
