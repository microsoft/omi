/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_DebugError_h
#define _OMI_DebugError_h

#include <MI.h>
#include "OMI_Error.h"

/*
**==============================================================================
**
** OMI_DebugError [OMI_DebugError]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_DebugError /* extends OMI_Error */
{
    MI_Instance __instance;
    /* CIM_Error properties */
    MI_ConstUint16Field ErrorType;
    MI_ConstStringField OtherErrorType;
    MI_ConstStringField OwningEntity;
    MI_ConstStringField MessageID;
    MI_ConstStringField Message;
    MI_ConstStringAField MessageArguments;
    MI_ConstUint16Field PerceivedSeverity;
    MI_ConstUint16Field ProbableCause;
    MI_ConstStringField ProbableCauseDescription;
    MI_ConstStringAField RecommendedActions;
    MI_ConstStringField ErrorSource;
    MI_ConstUint16Field ErrorSourceFormat;
    MI_ConstStringField OtherErrorSourceFormat;
    MI_ConstUint32Field CIMStatusCode;
    MI_ConstStringField CIMStatusCodeDescription;
    /* OMI_Error properties */
    MI_ConstUint32Field error_Code;
    MI_ConstStringField error_Type;
    MI_ConstUint16Field error_Category;
    /* OMI_DebugError properties */
    MI_ConstStringAField OMI_BackTrace;
    MI_ConstReferenceField inner_Error;
}
OMI_DebugError;

typedef struct _OMI_DebugError_Ref
{
    OMI_DebugError* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_DebugError_Ref;

typedef struct _OMI_DebugError_ConstRef
{
    MI_CONST OMI_DebugError* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_DebugError_ConstRef;

typedef struct _OMI_DebugError_Array
{
    struct _OMI_DebugError** data;
    MI_Uint32 size;
}
OMI_DebugError_Array;

typedef struct _OMI_DebugError_ConstArray
{
    struct _OMI_DebugError MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_DebugError_ConstArray;

typedef struct _OMI_DebugError_ArrayRef
{
    OMI_DebugError_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_DebugError_ArrayRef;

typedef struct _OMI_DebugError_ConstArrayRef
{
    OMI_DebugError_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_DebugError_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_DebugError_rtti;

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clone(
    _In_ const OMI_DebugError* self,
    _Outptr_ OMI_DebugError** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_DebugError_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_DebugError_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Destruct(_Inout_ OMI_DebugError* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Delete(_Inout_ OMI_DebugError* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_ErrorType(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorType)->value = x;
    ((MI_Uint16Field*)&self->ErrorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_ErrorType(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->ErrorType, 0, sizeof(self->ErrorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_OtherErrorType(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_OtherErrorType(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_OtherErrorType(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_OwningEntity(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_OwningEntity(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_OwningEntity(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_MessageID(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_MessageID(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_MessageID(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_Message(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_Message(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_Message(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_MessageArguments(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_MessageArguments(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_MessageArguments(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_PerceivedSeverity(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_PerceivedSeverity(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_ProbableCause(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProbableCause)->value = x;
    ((MI_Uint16Field*)&self->ProbableCause)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_ProbableCause(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->ProbableCause, 0, sizeof(self->ProbableCause));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_ProbableCauseDescription(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_ProbableCauseDescription(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_ProbableCauseDescription(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_RecommendedActions(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_RecommendedActions(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_RecommendedActions(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_ErrorSource(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_ErrorSource(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_ErrorSource(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_ErrorSourceFormat(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->value = x;
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_ErrorSourceFormat(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->ErrorSourceFormat, 0, sizeof(self->ErrorSourceFormat));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_OtherErrorSourceFormat(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_OtherErrorSourceFormat(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_OtherErrorSourceFormat(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_CIMStatusCode(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->CIMStatusCode)->value = x;
    ((MI_Uint32Field*)&self->CIMStatusCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_CIMStatusCode(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->CIMStatusCode, 0, sizeof(self->CIMStatusCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_CIMStatusCodeDescription(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_CIMStatusCodeDescription(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_CIMStatusCodeDescription(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_error_Code(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->error_Code)->value = x;
    ((MI_Uint32Field*)&self->error_Code)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_error_Code(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->error_Code, 0, sizeof(self->error_Code));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_error_Type(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_error_Type(
    _Inout_ OMI_DebugError* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_error_Type(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_error_Category(
    _Inout_ OMI_DebugError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->error_Category)->value = x;
    ((MI_Uint16Field*)&self->error_Category)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_error_Category(
    _Inout_ OMI_DebugError* self)
{
    memset((void*)&self->error_Category, 0, sizeof(self->error_Category));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_OMI_BackTrace(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_OMI_BackTrace(
    _Inout_ OMI_DebugError* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_OMI_BackTrace(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Set_inner_Error(
    _Inout_ OMI_DebugError* self,
    _In_ const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_SetPtr_inner_Error(
    _Inout_ OMI_DebugError* self,
    _In_ const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_DebugError_Clear_inner_Error(
    _Inout_ OMI_DebugError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}


#endif /* _OMI_DebugError_h */
