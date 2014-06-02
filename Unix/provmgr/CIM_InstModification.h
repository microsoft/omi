/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_InstModification_h
#define _CIM_InstModification_h

#include <MI.h>
#include "CIM_InstIndication.h"

/*
**==============================================================================
**
** CIM_InstModification [CIM_InstModification]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_InstModification /* extends CIM_InstIndication */
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
    /* CIM_InstModification properties */
    MI_ConstReferenceField PreviousInstance;
}
CIM_InstModification;

typedef struct _CIM_InstModification_Ref
{
    CIM_InstModification* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstModification_Ref;

typedef struct _CIM_InstModification_ConstRef
{
    MI_CONST CIM_InstModification* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstModification_ConstRef;

typedef struct _CIM_InstModification_Array
{
    struct _CIM_InstModification** data;
    MI_Uint32 size;
}
CIM_InstModification_Array;

typedef struct _CIM_InstModification_ConstArray
{
    struct _CIM_InstModification MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_InstModification_ConstArray;

typedef struct _CIM_InstModification_ArrayRef
{
    CIM_InstModification_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstModification_ArrayRef;

typedef struct _CIM_InstModification_ConstArrayRef
{
    CIM_InstModification_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstModification_ConstArrayRef;

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_IndicationIdentifier(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_IndicationIdentifier(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_IndicationIdentifier(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_CorrelatedIndications(
    CIM_InstModification* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_CorrelatedIndications(
    CIM_InstModification* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_CorrelatedIndications(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_IndicationTime(
    CIM_InstModification* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_IndicationTime(
    CIM_InstModification* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_PerceivedSeverity(
    CIM_InstModification* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_PerceivedSeverity(
    CIM_InstModification* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_OtherSeverity(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_OtherSeverity(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_OtherSeverity(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_IndicationFilterName(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_IndicationFilterName(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_IndicationFilterName(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_SequenceContext(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_SequenceContext(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_SequenceContext(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_SequenceNumber(
    CIM_InstModification* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_SequenceNumber(
    CIM_InstModification* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_SourceInstance(
    CIM_InstModification* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_SourceInstance(
    CIM_InstModification* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_SourceInstance(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_SourceInstanceModelPath(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_SourceInstanceModelPath(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_SourceInstanceModelPath(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_SourceInstanceHost(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_SourceInstanceHost(
    CIM_InstModification* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_SourceInstanceHost(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Set_PreviousInstance(
    CIM_InstModification* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_SetPtr_PreviousInstance(
    CIM_InstModification* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstModification_Clear_PreviousInstance(
    CIM_InstModification* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}


#endif /* _CIM_InstModification_h */
