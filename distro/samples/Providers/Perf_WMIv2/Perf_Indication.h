/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Perf_Indication_h
#define _Perf_Indication_h

#include <MI.h>
#include "CIM_Indication.h"
#include "Perf_Embedded.h"

/*
**==============================================================================
**
** Perf_Indication [Perf_Indication]
**
** Keys:
**    v_uint64_key
**
**==============================================================================
*/

typedef struct _Perf_Indication /* extends CIM_Indication */
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
    /* Perf_Indication properties */
    MI_ConstSint8AField v_sint8;
    MI_ConstUint16Field v_uint16;
    MI_ConstSint32AField v_sint32;
    /*KEY*/ MI_ConstUint64Field v_uint64_key;
    MI_ConstStringAField v_string;
    MI_ConstBooleanField v_boolean;
    MI_ConstReal32AField v_real32;
    MI_ConstReal64Field v_real64;
    MI_ConstDatetimeAField v_datetime;
    MI_ConstChar16Field v_char16;
    Perf_Embedded_ConstRef v_embedded;
}
Perf_Indication;

typedef struct _Perf_Indication_Ref
{
    Perf_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Indication_Ref;

typedef struct _Perf_Indication_ConstRef
{
    MI_CONST Perf_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Indication_ConstRef;

typedef struct _Perf_Indication_Array
{
    struct _Perf_Indication** data;
    MI_Uint32 size;
}
Perf_Indication_Array;

typedef struct _Perf_Indication_ConstArray
{
    struct _Perf_Indication MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Perf_Indication_ConstArray;

typedef struct _Perf_Indication_ArrayRef
{
    Perf_Indication_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Indication_ArrayRef;

typedef struct _Perf_Indication_ConstArrayRef
{
    Perf_Indication_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Indication_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Perf_Indication_rtti;

MI_INLINE MI_Result MI_CALL Perf_Indication_Construct(
    _Inout_ Perf_Indication* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Perf_Indication_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clone(
    _In_ const Perf_Indication* self,
    _Outptr_ Perf_Indication** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Perf_Indication_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Perf_Indication_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Destruct(_Inout_ Perf_Indication* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Delete(_Inout_ Perf_Indication* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Post(
    _In_ const Perf_Indication* self,
    _In_ MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    _In_z_ const MI_Char* bookmark)
{
    return MI_PostIndication(context,
        &self->__instance,
        subscriptionIDCount,
        bookmark);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_IndicationIdentifier(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_IndicationIdentifier(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_IndicationIdentifier(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_CorrelatedIndications(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_CorrelatedIndications(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_CorrelatedIndications(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_IndicationTime(
    _Inout_ Perf_Indication* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_IndicationTime(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_PerceivedSeverity(
    _Inout_ Perf_Indication* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_PerceivedSeverity(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_OtherSeverity(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_OtherSeverity(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_OtherSeverity(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_IndicationFilterName(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_IndicationFilterName(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_IndicationFilterName(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_SequenceContext(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_SequenceContext(
    _Inout_ Perf_Indication* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_SequenceContext(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_SequenceNumber(
    _Inout_ Perf_Indication* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_SequenceNumber(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_sint8(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Sint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_sint8(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Sint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_sint8(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_uint16(
    _Inout_ Perf_Indication* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->v_uint16)->value = x;
    ((MI_Uint16Field*)&self->v_uint16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_uint16(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->v_uint16, 0, sizeof(self->v_uint16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_sint32(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_sint32(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_sint32(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_uint64_key(
    _Inout_ Perf_Indication* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_uint64_key)->value = x;
    ((MI_Uint64Field*)&self->v_uint64_key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_uint64_key(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->v_uint64_key, 0, sizeof(self->v_uint64_key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_string(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_string(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_string(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_boolean(
    _Inout_ Perf_Indication* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->v_boolean)->value = x;
    ((MI_BooleanField*)&self->v_boolean)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_boolean(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->v_boolean, 0, sizeof(self->v_boolean));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_real32(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Real32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_real32(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Real32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_real32(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_real64(
    _Inout_ Perf_Indication* self,
    _In_ MI_Real64 x)
{
    ((MI_Real64Field*)&self->v_real64)->value = x;
    ((MI_Real64Field*)&self->v_real64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_real64(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->v_real64, 0, sizeof(self->v_real64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_datetime(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Datetime* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_datetime(
    _Inout_ Perf_Indication* self,
    _In_reads_opt_(size) const MI_Datetime* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_datetime(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_char16(
    _Inout_ Perf_Indication* self,
    _In_ MI_Char16 x)
{
    ((MI_Char16Field*)&self->v_char16)->value = x;
    ((MI_Char16Field*)&self->v_char16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_char16(
    _Inout_ Perf_Indication* self)
{
    memset((void*)&self->v_char16, 0, sizeof(self->v_char16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Set_v_embedded(
    _Inout_ Perf_Indication* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_SetPtr_v_embedded(
    _Inout_ Perf_Indication* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Indication_Clear_v_embedded(
    _Inout_ Perf_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

/*
**==============================================================================
**
** Perf_Indication provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Perf_Indication_Self Perf_Indication_Self;

MI_EXTERN_C void MI_CALL Perf_Indication_Load(
    _Outptr_result_maybenull_ Perf_Indication_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_Indication_Unload(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_Indication_EnableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className);

MI_EXTERN_C void MI_CALL Perf_Indication_DisableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className);

MI_EXTERN_C void MI_CALL Perf_Indication_Subscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    _In_ MI_Uint64  subscriptionID,
    _Outptr_result_maybenull_ void** subscriptionSelf);

MI_EXTERN_C void MI_CALL Perf_Indication_Unsubscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ MI_Uint64  subscriptionID,
    _In_opt_ void* subscriptionSelf);


#endif /* _Perf_Indication_h */
