/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyCondition_h
#define _CIM_NetworkPolicyCondition_h

#include <MI.h>
#include "CIM_Policy.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyCondition [CIM_NetworkPolicyCondition]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyCondition /* extends CIM_Policy */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Policy properties */
    MI_ConstStringField CommonName;
    MI_ConstStringAField PolicyKeywords;
    /* CIM_NetworkPolicyCondition properties */
    MI_ConstUint16Field ParameterType;
    MI_ConstUint16Field Operator;
    MI_ConstStringField ParameterValue;
}
CIM_NetworkPolicyCondition;

typedef struct _CIM_NetworkPolicyCondition_Ref
{
    CIM_NetworkPolicyCondition* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyCondition_Ref;

typedef struct _CIM_NetworkPolicyCondition_ConstRef
{
    MI_CONST CIM_NetworkPolicyCondition* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyCondition_ConstRef;

typedef struct _CIM_NetworkPolicyCondition_Array
{
    struct _CIM_NetworkPolicyCondition** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyCondition_Array;

typedef struct _CIM_NetworkPolicyCondition_ConstArray
{
    struct _CIM_NetworkPolicyCondition MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyCondition_ConstArray;

typedef struct _CIM_NetworkPolicyCondition_ArrayRef
{
    CIM_NetworkPolicyCondition_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyCondition_ArrayRef;

typedef struct _CIM_NetworkPolicyCondition_ConstArrayRef
{
    CIM_NetworkPolicyCondition_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyCondition_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyCondition_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Construct(
    _Out_ CIM_NetworkPolicyCondition* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyCondition_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clone(
    _In_ const CIM_NetworkPolicyCondition* self,
    _Outptr_ CIM_NetworkPolicyCondition** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyCondition_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyCondition_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Destruct(_Inout_ CIM_NetworkPolicyCondition* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Delete(_Inout_ CIM_NetworkPolicyCondition* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Post(
    _In_ const CIM_NetworkPolicyCondition* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_Caption(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_Caption(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_Description(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_Description(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_ElementName(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_CommonName(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_CommonName(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_CommonName(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyCondition* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyCondition* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_ParameterType(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ParameterType)->value = x;
    ((MI_Uint16Field*)&self->ParameterType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_ParameterType(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    memset((void*)&self->ParameterType, 0, sizeof(self->ParameterType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_Operator(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Operator)->value = x;
    ((MI_Uint16Field*)&self->Operator)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_Operator(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    memset((void*)&self->Operator, 0, sizeof(self->Operator));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Set_ParameterValue(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_SetPtr_ParameterValue(
    _Inout_ CIM_NetworkPolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyCondition_Clear_ParameterValue(
    _Inout_ CIM_NetworkPolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** CIM_NetworkPolicyCondition provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyCondition_Self CIM_NetworkPolicyCondition_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyCondition_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_Unload(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_GetInstance(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyCondition* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_CreateInstance(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyCondition* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyCondition* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyCondition_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyCondition_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyCondition* instanceName);


#endif /* _CIM_NetworkPolicyCondition_h */
