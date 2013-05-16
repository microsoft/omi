/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Perf_WithPsSemantics_h
#define _Perf_WithPsSemantics_h

#include <MI.h>
#include "Perf_Embedded.h"
#include "Perf_WithPsSemantics.h"

/*
**==============================================================================
**
** Perf_WithPsSemantics [Perf_WithPsSemantics]
**
** Keys:
**    v_uint64_key
**
**==============================================================================
*/

typedef struct _Perf_WithPsSemantics
{
    MI_Instance __instance;
    /* Perf_WithPsSemantics properties */
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
Perf_WithPsSemantics;

typedef struct _Perf_WithPsSemantics_Ref
{
    Perf_WithPsSemantics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_WithPsSemantics_Ref;

typedef struct _Perf_WithPsSemantics_ConstRef
{
    MI_CONST Perf_WithPsSemantics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_WithPsSemantics_ConstRef;

typedef struct _Perf_WithPsSemantics_Array
{
    struct _Perf_WithPsSemantics** data;
    MI_Uint32 size;
}
Perf_WithPsSemantics_Array;

typedef struct _Perf_WithPsSemantics_ConstArray
{
    struct _Perf_WithPsSemantics MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Perf_WithPsSemantics_ConstArray;

typedef struct _Perf_WithPsSemantics_ArrayRef
{
    Perf_WithPsSemantics_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_WithPsSemantics_ArrayRef;

typedef struct _Perf_WithPsSemantics_ConstArrayRef
{
    Perf_WithPsSemantics_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_WithPsSemantics_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Perf_WithPsSemantics_rtti;

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Construct(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Perf_WithPsSemantics_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clone(
    _In_ const Perf_WithPsSemantics* self,
    _Outptr_ Perf_WithPsSemantics** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Perf_WithPsSemantics_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Perf_WithPsSemantics_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Destruct(_Inout_ Perf_WithPsSemantics* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Delete(_Inout_ Perf_WithPsSemantics* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Post(
    _In_ const Perf_WithPsSemantics* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_sint8(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_sint8(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_sint8(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_uint16(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->v_uint16)->value = x;
    ((MI_Uint16Field*)&self->v_uint16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_uint16(
    _Inout_ Perf_WithPsSemantics* self)
{
    memset((void*)&self->v_uint16, 0, sizeof(self->v_uint16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_sint32(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_sint32(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_sint32(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_uint64_key(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_uint64_key)->value = x;
    ((MI_Uint64Field*)&self->v_uint64_key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_uint64_key(
    _Inout_ Perf_WithPsSemantics* self)
{
    memset((void*)&self->v_uint64_key, 0, sizeof(self->v_uint64_key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_string(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_string(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_string(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_boolean(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->v_boolean)->value = x;
    ((MI_BooleanField*)&self->v_boolean)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_boolean(
    _Inout_ Perf_WithPsSemantics* self)
{
    memset((void*)&self->v_boolean, 0, sizeof(self->v_boolean));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_real32(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_real32(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_real32(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_real64(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Real64 x)
{
    ((MI_Real64Field*)&self->v_real64)->value = x;
    ((MI_Real64Field*)&self->v_real64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_real64(
    _Inout_ Perf_WithPsSemantics* self)
{
    memset((void*)&self->v_real64, 0, sizeof(self->v_real64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_datetime(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_datetime(
    _Inout_ Perf_WithPsSemantics* self,
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

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_datetime(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_char16(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ MI_Char16 x)
{
    ((MI_Char16Field*)&self->v_char16)->value = x;
    ((MI_Char16Field*)&self->v_char16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_char16(
    _Inout_ Perf_WithPsSemantics* self)
{
    memset((void*)&self->v_char16, 0, sizeof(self->v_char16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Set_v_embedded(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetPtr_v_embedded(
    _Inout_ Perf_WithPsSemantics* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_Clear_v_embedded(
    _Inout_ Perf_WithPsSemantics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

/*
**==============================================================================
**
** Perf_WithPsSemantics.SetBehaviour()
**
**==============================================================================
*/

typedef struct _Perf_WithPsSemantics_SetBehaviour
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field maxInstances;
    /*IN*/ MI_ConstUint32Field streamInstances;
    /*IN*/ MI_ConstUint32Field psSemanticsFlags;
    /*IN*/ MI_ConstUint32Field psSemanticsCount;
}
Perf_WithPsSemantics_SetBehaviour;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_WithPsSemantics_SetBehaviour_rtti;

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Construct(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_WithPsSemantics_SetBehaviour_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clone(
    _In_ const Perf_WithPsSemantics_SetBehaviour* self,
    _Outptr_ Perf_WithPsSemantics_SetBehaviour** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Destruct(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Delete(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Post(
    _In_ const Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Set_MIReturn(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clear_MIReturn(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Set_maxInstances(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->maxInstances)->value = x;
    ((MI_Uint32Field*)&self->maxInstances)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clear_maxInstances(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->maxInstances, 0, sizeof(self->maxInstances));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Set_streamInstances(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->streamInstances)->value = x;
    ((MI_Uint32Field*)&self->streamInstances)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clear_streamInstances(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->streamInstances, 0, sizeof(self->streamInstances));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Set_psSemanticsFlags(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->psSemanticsFlags)->value = x;
    ((MI_Uint32Field*)&self->psSemanticsFlags)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clear_psSemanticsFlags(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->psSemanticsFlags, 0, sizeof(self->psSemanticsFlags));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Set_psSemanticsCount(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->psSemanticsCount)->value = x;
    ((MI_Uint32Field*)&self->psSemanticsCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_SetBehaviour_Clear_psSemanticsCount(
    _Inout_ Perf_WithPsSemantics_SetBehaviour* self)
{
    memset((void*)&self->psSemanticsCount, 0, sizeof(self->psSemanticsCount));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_WithPsSemantics.PingBackParameters()
**
**==============================================================================
*/

typedef struct _Perf_WithPsSemantics_PingBackParameters
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Perf_Embedded_ConstRef inbound;
    /*OUT*/ Perf_Embedded_ConstRef outbound;
}
Perf_WithPsSemantics_PingBackParameters;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_WithPsSemantics_PingBackParameters_rtti;

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Construct(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_WithPsSemantics_PingBackParameters_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Clone(
    _In_ const Perf_WithPsSemantics_PingBackParameters* self,
    _Outptr_ Perf_WithPsSemantics_PingBackParameters** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Destruct(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Delete(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Post(
    _In_ const Perf_WithPsSemantics_PingBackParameters* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Set_MIReturn(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Clear_MIReturn(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Set_inbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_SetPtr_inbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Clear_inbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Set_outbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_SetPtr_outbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self,
    _In_ const Perf_Embedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_PingBackParameters_Clear_outbound(
    _Inout_ Perf_WithPsSemantics_PingBackParameters* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** Perf_WithPsSemantics.streamingInstances()
**
**==============================================================================
*/

typedef struct _Perf_WithPsSemantics_streamingInstances
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Perf_WithPsSemantics_streamingInstances;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_WithPsSemantics_streamingInstances_rtti;

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Construct(
    _Inout_ Perf_WithPsSemantics_streamingInstances* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_WithPsSemantics_streamingInstances_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Clone(
    _In_ const Perf_WithPsSemantics_streamingInstances* self,
    _Outptr_ Perf_WithPsSemantics_streamingInstances** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Destruct(
    _Inout_ Perf_WithPsSemantics_streamingInstances* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Delete(
    _Inout_ Perf_WithPsSemantics_streamingInstances* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Post(
    _In_ const Perf_WithPsSemantics_streamingInstances* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Set_MIReturn(
    _Inout_ Perf_WithPsSemantics_streamingInstances* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingInstances_Clear_MIReturn(
    _Inout_ Perf_WithPsSemantics_streamingInstances* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_WithPsSemantics.streamingPrimitive()
**
**==============================================================================
*/

typedef struct _Perf_WithPsSemantics_streamingPrimitive
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Perf_WithPsSemantics_streamingPrimitive;

MI_EXTERN_C MI_CONST MI_MethodDecl Perf_WithPsSemantics_streamingPrimitive_rtti;

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Construct(
    _Inout_ Perf_WithPsSemantics_streamingPrimitive* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &Perf_WithPsSemantics_streamingPrimitive_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Clone(
    _In_ const Perf_WithPsSemantics_streamingPrimitive* self,
    _Outptr_ Perf_WithPsSemantics_streamingPrimitive** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Destruct(
    _Inout_ Perf_WithPsSemantics_streamingPrimitive* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Delete(
    _Inout_ Perf_WithPsSemantics_streamingPrimitive* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Post(
    _In_ const Perf_WithPsSemantics_streamingPrimitive* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Set_MIReturn(
    _Inout_ Perf_WithPsSemantics_streamingPrimitive* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_WithPsSemantics_streamingPrimitive_Clear_MIReturn(
    _Inout_ Perf_WithPsSemantics_streamingPrimitive* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Perf_WithPsSemantics provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Perf_WithPsSemantics_Self Perf_WithPsSemantics_Self;

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Load(
    _Outptr_result_maybenull_ Perf_WithPsSemantics_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Unload(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_EnumerateInstances(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_GetInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_CreateInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* newInstance);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_ModifyInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_DeleteInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Invoke_SetBehaviour(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_SetBehaviour* in);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Invoke_PingBackParameters(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_PingBackParameters* in);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Invoke_streamingInstances(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_streamingInstances* in);

MI_EXTERN_C void MI_CALL Perf_WithPsSemantics_Invoke_streamingPrimitive(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_streamingPrimitive* in);


#endif /* _Perf_WithPsSemantics_h */
