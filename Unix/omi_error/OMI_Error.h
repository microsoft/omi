/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_Error_h
#define _OMI_Error_h

#include <MI.h>
#include "CIM_Error.h"

/*
**==============================================================================
**
** OMI_Error [OMI_Error]
**
** Keys:
**
**==============================================================================
*/

typedef struct _OMI_Error /* extends CIM_Error */
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
    MI_ConstUint32Field OMI_Code;
    MI_ConstUint16Field OMI_Category;
    MI_ConstStringField OMI_Type;
    MI_ConstStringField OMI_ErrorMessage;
}
OMI_Error;

typedef struct _OMI_Error_Ref
{
    OMI_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Error_Ref;

typedef struct _OMI_Error_ConstRef
{
    MI_CONST OMI_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Error_ConstRef;

typedef struct _OMI_Error_Array
{
    struct _OMI_Error** data;
    MI_Uint32 size;
}
OMI_Error_Array;

typedef struct _OMI_Error_ConstArray
{
    struct _OMI_Error MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_Error_ConstArray;

typedef struct _OMI_Error_ArrayRef
{
    OMI_Error_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Error_ArrayRef;

typedef struct _OMI_Error_ConstArrayRef
{
    OMI_Error_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Error_ConstArrayRef;

MI_INLINE MI_Result MI_CALL OMI_Error_Set_ErrorType(
    OMI_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorType)->value = x;
    ((MI_Uint16Field*)&self->ErrorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_ErrorType(
    OMI_Error* self)
{
    memset((void*)&self->ErrorType, 0, sizeof(self->ErrorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OtherErrorType(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_OtherErrorType(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OtherErrorType(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OwningEntity(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_OwningEntity(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OwningEntity(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_MessageID(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_MessageID(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_MessageID(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_Message(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_Message(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_Message(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_MessageArguments(
    OMI_Error* self,
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

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_MessageArguments(
    OMI_Error* self,
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

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_MessageArguments(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_PerceivedSeverity(
    OMI_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_PerceivedSeverity(
    OMI_Error* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_ProbableCause(
    OMI_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProbableCause)->value = x;
    ((MI_Uint16Field*)&self->ProbableCause)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_ProbableCause(
    OMI_Error* self)
{
    memset((void*)&self->ProbableCause, 0, sizeof(self->ProbableCause));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_ProbableCauseDescription(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_ProbableCauseDescription(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_ProbableCauseDescription(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_RecommendedActions(
    OMI_Error* self,
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

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_RecommendedActions(
    OMI_Error* self,
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

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_RecommendedActions(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_ErrorSource(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_ErrorSource(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_ErrorSource(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_ErrorSourceFormat(
    OMI_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->value = x;
    ((MI_Uint16Field*)&self->ErrorSourceFormat)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_ErrorSourceFormat(
    OMI_Error* self)
{
    memset((void*)&self->ErrorSourceFormat, 0, sizeof(self->ErrorSourceFormat));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OtherErrorSourceFormat(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_OtherErrorSourceFormat(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OtherErrorSourceFormat(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_CIMStatusCode(
    OMI_Error* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->CIMStatusCode)->value = x;
    ((MI_Uint32Field*)&self->CIMStatusCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_CIMStatusCode(
    OMI_Error* self)
{
    memset((void*)&self->CIMStatusCode, 0, sizeof(self->CIMStatusCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_CIMStatusCodeDescription(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_CIMStatusCodeDescription(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_CIMStatusCodeDescription(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OMI_Code(
    OMI_Error* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->OMI_Code)->value = x;
    ((MI_Uint32Field*)&self->OMI_Code)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OMI_Code(
    OMI_Error* self)
{
    memset((void*)&self->OMI_Code, 0, sizeof(self->OMI_Code));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OMI_Category(
    OMI_Error* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OMI_Category)->value = x;
    ((MI_Uint16Field*)&self->OMI_Category)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OMI_Category(
    OMI_Error* self)
{
    memset((void*)&self->OMI_Category, 0, sizeof(self->OMI_Category));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OMI_Type(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_OMI_Type(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OMI_Type(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Set_OMI_ErrorMessage(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Error_SetPtr_OMI_ErrorMessage(
    OMI_Error* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Error_Clear_OMI_ErrorMessage(
    OMI_Error* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}


#endif /* _OMI_Error_h */
