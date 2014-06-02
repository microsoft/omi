/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicySet_h
#define _CIM_PolicySet_h

#include <MI.h>
#include "CIM_Policy.h"

/*
**==============================================================================
**
** CIM_PolicySet [CIM_PolicySet]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_PolicySet /* extends CIM_Policy */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Policy properties */
    MI_ConstStringField CommonName;
    MI_ConstStringAField PolicyKeywords;
    /* CIM_PolicySet properties */
    MI_ConstUint16Field PolicyDecisionStrategy;
    MI_ConstStringAField PolicyRoles;
    MI_ConstUint16Field Enabled;
}
CIM_PolicySet;

typedef struct _CIM_PolicySet_Ref
{
    CIM_PolicySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySet_Ref;

typedef struct _CIM_PolicySet_ConstRef
{
    MI_CONST CIM_PolicySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySet_ConstRef;

typedef struct _CIM_PolicySet_Array
{
    struct _CIM_PolicySet** data;
    MI_Uint32 size;
}
CIM_PolicySet_Array;

typedef struct _CIM_PolicySet_ConstArray
{
    struct _CIM_PolicySet MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicySet_ConstArray;

typedef struct _CIM_PolicySet_ArrayRef
{
    CIM_PolicySet_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySet_ArrayRef;

typedef struct _CIM_PolicySet_ConstArrayRef
{
    CIM_PolicySet_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySet_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicySet_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Construct(
    _Out_ CIM_PolicySet* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicySet_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clone(
    _In_ const CIM_PolicySet* self,
    _Outptr_ CIM_PolicySet** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicySet_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicySet_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Destruct(_Inout_ CIM_PolicySet* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Delete(_Inout_ CIM_PolicySet* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Post(
    _In_ const CIM_PolicySet* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_InstanceID(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_InstanceID(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_InstanceID(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_Caption(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_Caption(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_Caption(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_Description(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_Description(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_Description(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_ElementName(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_ElementName(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_ElementName(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_CommonName(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_CommonName(
    _Inout_ CIM_PolicySet* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_CommonName(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_PolicyKeywords(
    _Inout_ CIM_PolicySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_PolicyKeywords(
    _Inout_ CIM_PolicySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_PolicyKeywords(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_PolicyDecisionStrategy(
    _Inout_ CIM_PolicySet* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->value = x;
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_PolicyDecisionStrategy(
    _Inout_ CIM_PolicySet* self)
{
    memset((void*)&self->PolicyDecisionStrategy, 0, sizeof(self->PolicyDecisionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_PolicyRoles(
    _Inout_ CIM_PolicySet* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_SetPtr_PolicyRoles(
    _Inout_ CIM_PolicySet* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_PolicyRoles(
    _Inout_ CIM_PolicySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Set_Enabled(
    _Inout_ CIM_PolicySet* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Enabled)->value = x;
    ((MI_Uint16Field*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySet_Clear_Enabled(
    _Inout_ CIM_PolicySet* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}


#endif /* _CIM_PolicySet_h */
