/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Error_h
#define _CIM_Error_h

#include <MI.h>

/*
**==============================================================================
**
** CIM_Error [CIM_Error]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Error
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
}
CIM_Error;

typedef struct _CIM_Error_Ref
{
    CIM_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_Ref;

typedef struct _CIM_Error_ConstRef
{
    MI_CONST CIM_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ConstRef;

typedef struct _CIM_Error_Array
{
    struct _CIM_Error** data;
    MI_Uint32 size;
}
CIM_Error_Array;

typedef struct _CIM_Error_ConstArray
{
    struct _CIM_Error MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Error_ConstArray;

typedef struct _CIM_Error_ArrayRef
{
    CIM_Error_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ArrayRef;

typedef struct _CIM_Error_ConstArrayRef
{
    CIM_Error_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Error_rtti;

MI_INLINE MI_Result MI_CALL CIM_Error_Construct(
    CIM_Error* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Error_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clone(
    const CIM_Error* self,
    CIM_Error** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Error_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Error_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Destruct(CIM_Error* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Delete(CIM_Error* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Post(
    const CIM_Error* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_ErrorType(
    CIM_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorType)->value = x;
    ((MI_Uint16Field*)&self->ErrorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_ErrorType(
    CIM_Error* self)
{
    memset((void*)&self->ErrorType, 0, sizeof(self->ErrorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_OtherErrorType(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_OtherErrorType(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_OtherErrorType(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_OwningEntity(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_OwningEntity(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_OwningEntity(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_MessageID(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_MessageID(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_MessageID(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_Message(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_Message(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_Message(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_MessageArguments(
    CIM_Error* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_MessageArguments(
    CIM_Error* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_MessageArguments(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_PerceivedSeverity(
    CIM_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_PerceivedSeverity(
    CIM_Error* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_ProbableCause(
    CIM_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProbableCause)->value = x;
    ((MI_Uint16Field*)&self->ProbableCause)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_ProbableCause(
    CIM_Error* self)
{
    memset((void*)&self->ProbableCause, 0, sizeof(self->ProbableCause));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_ProbableCauseDescription(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_ProbableCauseDescription(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_ProbableCauseDescription(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_RecommendedActions(
    CIM_Error* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_RecommendedActions(
    CIM_Error* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_RecommendedActions(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_ErrorSource(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_ErrorSource(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_ErrorSource(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_ErrorSourceFormat(
    CIM_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->value = x;
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_ErrorSourceFormat(
    CIM_Error* self)
{
    memset((void*)&self->ErrorSourceFormat, 0, sizeof(self->ErrorSourceFormat));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_OtherErrorSourceFormat(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_OtherErrorSourceFormat(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_OtherErrorSourceFormat(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_CIMStatusCode(
    CIM_Error* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->CIMStatusCode)->value = x;
    ((MI_Uint32Field*)&self->CIMStatusCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_CIMStatusCode(
    CIM_Error* self)
{
    memset((void*)&self->CIMStatusCode, 0, sizeof(self->CIMStatusCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Error_Set_CIMStatusCodeDescription(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Error_SetPtr_CIMStatusCodeDescription(
    CIM_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Error_Clear_CIMStatusCodeDescription(
    CIM_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}


#endif /* _CIM_Error_h */
