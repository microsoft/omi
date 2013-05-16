/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Perf_NoPsSemantics_h
#define _Perf_NoPsSemantics_h

#include <MI.h>
#include "Perf_Embedded.h"
#include "Perf_WithPsSemantics.h"

/*
**==============================================================================
**
** Perf_NoPsSemantics [Perf_NoPsSemantics]
**
** Keys:
**    v_uint64_key
**
**==============================================================================
*/

typedef struct _Perf_NoPsSemantics
{
    MI_Instance __instance;
    /* Perf_NoPsSemantics properties */
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
Perf_NoPsSemantics;

typedef struct _Perf_NoPsSemantics_Ref
{
    Perf_NoPsSemantics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_NoPsSemantics_Ref;

typedef struct _Perf_NoPsSemantics_ConstRef
{
    MI_CONST Perf_NoPsSemantics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_NoPsSemantics_ConstRef;

typedef struct _Perf_NoPsSemantics_Array
{
    struct _Perf_NoPsSemantics** data;
    MI_Uint32 size;
}
Perf_NoPsSemantics_Array;

typedef struct _Perf_NoPsSemantics_ConstArray
{
    struct _Perf_NoPsSemantics MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Perf_NoPsSemantics_ConstArray;

typedef struct _Perf_NoPsSemantics_ArrayRef
{
    Perf_NoPsSemantics_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_NoPsSemantics_ArrayRef;

typedef struct _Perf_NoPsSemantics_ConstArrayRef
{
    Perf_NoPsSemantics_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_NoPsSemantics_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Perf_NoPsSemantics_rtti;

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Construct(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Perf_NoPsSemantics_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clone(
    _In_ const Perf_NoPsSemantics* self,
    _Outptr_ Perf_NoPsSemantics** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Perf_NoPsSemantics_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Perf_NoPsSemantics_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Destruct(_Inout_ Perf_NoPsSemantics* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Delete(_Inout_ Perf_NoPsSemantics* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Post(
    _In_ const Perf_NoPsSemantics* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_sint8(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Sint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_sint8(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Sint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_sint8(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_uint16(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->v_uint16)->value = x;
    ((MI_Uint16Field*)&self->v_uint16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_uint16(
    _Inout_ Perf_NoPsSemantics* self)
{
    memset((void*)&self->v_uint16, 0, sizeof(self->v_uint16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_sint32(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_sint32(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_sint32(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_uint64_key(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_uint64_key)->value = x;
    ((MI_Uint64Field*)&self->v_uint64_key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_uint64_key(
    _Inout_ Perf_NoPsSemantics* self)
{
    memset((void*)&self->v_uint64_key, 0, sizeof(self->v_uint64_key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_string(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_string(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_string(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_boolean(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->v_boolean)->value = x;
    ((MI_BooleanField*)&self->v_boolean)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_boolean(
    _Inout_ Perf_NoPsSemantics* self)
{
    memset((void*)&self->v_boolean, 0, sizeof(self->v_boolean));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_real32(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Real32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_real32(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Real32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_real32(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_real64(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Real64 x)
{
    ((MI_Real64Field*)&self->v_real64)->value = x;
    ((MI_Real64Field*)&self->v_real64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_real64(
    _Inout_ Perf_NoPsSemantics* self)
{
    memset((void*)&self->v_real64, 0, sizeof(self->v_real64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_datetime(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Datetime* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_datetime(
    _Inout_ Perf_NoPsSemantics* self,
    _In_reads_opt_(size) const MI_Datetime* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_datetime(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_char16(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ MI_Char16 x)
{
    ((MI_Char16Field*)&self->v_char16)->value = x;
    ((MI_Char16Field*)&self->v_char16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_char16(
    _Inout_ Perf_NoPsSemantics* self)
{
    memset((void*)&self->v_char16, 0, sizeof(self->v_char16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Set_v_embedded(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetPtr_v_embedded(
    _Inout_ Perf_NoPsSemantics* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_Clear_v_embedded(
    _Inout_ Perf_NoPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

/*
**==============================================================================
**
** Perf_NoPsSemantics.SetBehaviour()
**
**==============================================================================
*/

typedef struct _Perf_NoPsSemantics_SetBehaviour
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field maxInstances;
    /*IN*/ MI_ConstUint32Field streamInstances;
    /*IN*/ MI_ConstUint32Field psSemanticsFlags;
    /*IN*/ MI_ConstUint32Field psSemanticsCount;
}
Perf_NoPsSemantics_SetBehaviour;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_NoPsSemantics_SetBehaviour_rtti;

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Construct(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_NoPsSemantics_SetBehaviour_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clone(
    _In_ const Perf_NoPsSemantics_SetBehaviour* self,
    _Outptr_ Perf_NoPsSemantics_SetBehaviour** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Destruct(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Delete(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Post(
    _In_ const Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Set_MIReturn(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clear_MIReturn(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Set_maxInstances(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->maxInstances)->value = x;
    ((MI_Uint32Field*)&self->maxInstances)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clear_maxInstances(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->maxInstances, 0, sizeof(self->maxInstances));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Set_streamInstances(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->streamInstances)->value = x;
    ((MI_Uint32Field*)&self->streamInstances)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clear_streamInstances(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->streamInstances, 0, sizeof(self->streamInstances));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Set_psSemanticsFlags(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->psSemanticsFlags)->value = x;
    ((MI_Uint32Field*)&self->psSemanticsFlags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clear_psSemanticsFlags(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->psSemanticsFlags, 0, sizeof(self->psSemanticsFlags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Set_psSemanticsCount(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->psSemanticsCount)->value = x;
    ((MI_Uint32Field*)&self->psSemanticsCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_SetBehaviour_Clear_psSemanticsCount(
    _Inout_ Perf_NoPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->psSemanticsCount, 0, sizeof(self->psSemanticsCount));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_NoPsSemantics.PingBackParameters()
**
**==============================================================================
*/

typedef struct _Perf_NoPsSemantics_PingBackParameters
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Perf_Embedded_ConstRef inbound;
    /*OUT*/ Perf_Embedded_ConstRef outbound;
}
Perf_NoPsSemantics_PingBackParameters;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_NoPsSemantics_PingBackParameters_rtti;

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Construct(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_NoPsSemantics_PingBackParameters_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Clone(
    _In_ const Perf_NoPsSemantics_PingBackParameters* self,
    _Outptr_ Perf_NoPsSemantics_PingBackParameters** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Destruct(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Delete(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Post(
    _In_ const Perf_NoPsSemantics_PingBackParameters* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Set_MIReturn(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Clear_MIReturn(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Set_inbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_SetPtr_inbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Clear_inbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Set_outbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_SetPtr_outbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_PingBackParameters_Clear_outbound(
    _Inout_ Perf_NoPsSemantics_PingBackParameters* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** Perf_NoPsSemantics.streamingInstances()
**
**==============================================================================
*/

typedef struct _Perf_NoPsSemantics_streamingInstances
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Perf_NoPsSemantics_streamingInstances;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_NoPsSemantics_streamingInstances_rtti;

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Construct(
    _Inout_ Perf_NoPsSemantics_streamingInstances* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_NoPsSemantics_streamingInstances_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Clone(
    _In_ const Perf_NoPsSemantics_streamingInstances* self,
    _Outptr_ Perf_NoPsSemantics_streamingInstances** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Destruct(
    _Inout_ Perf_NoPsSemantics_streamingInstances* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Delete(
    _Inout_ Perf_NoPsSemantics_streamingInstances* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Post(
    _In_ const Perf_NoPsSemantics_streamingInstances* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Set_MIReturn(
    _Inout_ Perf_NoPsSemantics_streamingInstances* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingInstances_Clear_MIReturn(
    _Inout_ Perf_NoPsSemantics_streamingInstances* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_NoPsSemantics.streamingPrimitive()
**
**==============================================================================
*/

typedef struct _Perf_NoPsSemantics_streamingPrimitive
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Perf_NoPsSemantics_streamingPrimitive;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_NoPsSemantics_streamingPrimitive_rtti;

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Construct(
    _Inout_ Perf_NoPsSemantics_streamingPrimitive* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_NoPsSemantics_streamingPrimitive_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Clone(
    _In_ const Perf_NoPsSemantics_streamingPrimitive* self,
    _Outptr_ Perf_NoPsSemantics_streamingPrimitive** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Destruct(
    _Inout_ Perf_NoPsSemantics_streamingPrimitive* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Delete(
    _Inout_ Perf_NoPsSemantics_streamingPrimitive* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Post(
    _In_ const Perf_NoPsSemantics_streamingPrimitive* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Set_MIReturn(
    _Inout_ Perf_NoPsSemantics_streamingPrimitive* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_NoPsSemantics_streamingPrimitive_Clear_MIReturn(
    _Inout_ Perf_NoPsSemantics_streamingPrimitive* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_NoPsSemantics provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Perf_NoPsSemantics_Self Perf_NoPsSemantics_Self;

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Load(
    _Outptr_result_maybenull_ Perf_NoPsSemantics_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Unload(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_EnumerateInstances(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_GetInstance(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_CreateInstance(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* newInstance);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_ModifyInstance(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_DeleteInstance(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Invoke_SetBehaviour(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_SetBehaviour* in);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Invoke_PingBackParameters(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_PingBackParameters* in);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Invoke_streamingInstances(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_streamingInstances* in);

MI_EXTERN_C void MI_CALL Perf_NoPsSemantics_Invoke_streamingPrimitive(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_streamingPrimitive* in);


#endif /* _Perf_NoPsSemantics_h */
