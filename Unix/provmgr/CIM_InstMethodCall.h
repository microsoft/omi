/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_InstMethodCall_h
#define _CIM_InstMethodCall_h

#include <MI.h>
#include "CIM_InstIndication.h"

/*
**==============================================================================
**
** CIM_InstMethodCall [CIM_InstMethodCall]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_InstMethodCall /* extends CIM_InstIndication */
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
    /* CIM_InstMethodCall properties */
    MI_ConstStringField MethodName;
    MI_ConstReferenceField MethodParameters;
    MI_ConstStringField ReturnValue;
    MI_ConstBooleanField PreCall;
}
CIM_InstMethodCall;

typedef struct _CIM_InstMethodCall_Ref
{
    CIM_InstMethodCall* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstMethodCall_Ref;

typedef struct _CIM_InstMethodCall_ConstRef
{
    MI_CONST CIM_InstMethodCall* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstMethodCall_ConstRef;

typedef struct _CIM_InstMethodCall_Array
{
    struct _CIM_InstMethodCall** data;
    MI_Uint32 size;
}
CIM_InstMethodCall_Array;

typedef struct _CIM_InstMethodCall_ConstArray
{
    struct _CIM_InstMethodCall MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_InstMethodCall_ConstArray;

typedef struct _CIM_InstMethodCall_ArrayRef
{
    CIM_InstMethodCall_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstMethodCall_ArrayRef;

typedef struct _CIM_InstMethodCall_ConstArrayRef
{
    CIM_InstMethodCall_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_InstMethodCall_ConstArrayRef;

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_IndicationIdentifier(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_IndicationIdentifier(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_IndicationIdentifier(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_CorrelatedIndications(
    CIM_InstMethodCall* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_CorrelatedIndications(
    CIM_InstMethodCall* self,
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

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_CorrelatedIndications(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_IndicationTime(
    CIM_InstMethodCall* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_IndicationTime(
    CIM_InstMethodCall* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_PerceivedSeverity(
    CIM_InstMethodCall* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_PerceivedSeverity(
    CIM_InstMethodCall* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_OtherSeverity(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_OtherSeverity(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_OtherSeverity(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_IndicationFilterName(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_IndicationFilterName(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_IndicationFilterName(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_SequenceContext(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_SequenceContext(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_SequenceContext(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_SequenceNumber(
    CIM_InstMethodCall* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_SequenceNumber(
    CIM_InstMethodCall* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_SourceInstance(
    CIM_InstMethodCall* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_SourceInstance(
    CIM_InstMethodCall* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_SourceInstance(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_SourceInstanceModelPath(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_SourceInstanceModelPath(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_SourceInstanceModelPath(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_SourceInstanceHost(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_SourceInstanceHost(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_SourceInstanceHost(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_MethodName(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_MethodName(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_MethodName(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_MethodParameters(
    CIM_InstMethodCall* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_MethodParameters(
    CIM_InstMethodCall* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_MethodParameters(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_ReturnValue(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_SetPtr_ReturnValue(
    CIM_InstMethodCall* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_ReturnValue(
    CIM_InstMethodCall* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Set_PreCall(
    CIM_InstMethodCall* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PreCall)->value = x;
    ((MI_BooleanField*)&self->PreCall)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_InstMethodCall_Clear_PreCall(
    CIM_InstMethodCall* self)
{
    memset((void*)&self->PreCall, 0, sizeof(self->PreCall));
    return MI_RESULT_OK;
}


#endif /* _CIM_InstMethodCall_h */
