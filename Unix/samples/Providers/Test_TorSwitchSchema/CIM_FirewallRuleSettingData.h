/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_FirewallRuleSettingData_h
#define _CIM_FirewallRuleSettingData_h

#include <MI.h>
#include "CIM_NetworkPolicyRuleSettingData.h"

/*
**==============================================================================
**
** CIM_FirewallRuleSettingData [CIM_FirewallRuleSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_FirewallRuleSettingData /* extends CIM_NetworkPolicyRuleSettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_NetworkPolicyRuleSettingData properties */
    /* CIM_FirewallRuleSettingData properties */
    MI_ConstStringAField FromGroupMembers;
    MI_ConstStringAField ToGroupMembers;
    MI_ConstUint16AField FromGroupMemberType;
    MI_ConstUint16AField ToGroupMemberType;
}
CIM_FirewallRuleSettingData;

typedef struct _CIM_FirewallRuleSettingData_Ref
{
    CIM_FirewallRuleSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_FirewallRuleSettingData_Ref;

typedef struct _CIM_FirewallRuleSettingData_ConstRef
{
    MI_CONST CIM_FirewallRuleSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_FirewallRuleSettingData_ConstRef;

typedef struct _CIM_FirewallRuleSettingData_Array
{
    struct _CIM_FirewallRuleSettingData** data;
    MI_Uint32 size;
}
CIM_FirewallRuleSettingData_Array;

typedef struct _CIM_FirewallRuleSettingData_ConstArray
{
    struct _CIM_FirewallRuleSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_FirewallRuleSettingData_ConstArray;

typedef struct _CIM_FirewallRuleSettingData_ArrayRef
{
    CIM_FirewallRuleSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_FirewallRuleSettingData_ArrayRef;

typedef struct _CIM_FirewallRuleSettingData_ConstArrayRef
{
    CIM_FirewallRuleSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_FirewallRuleSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_FirewallRuleSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Construct(
    _Out_ CIM_FirewallRuleSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_FirewallRuleSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clone(
    _In_ const CIM_FirewallRuleSettingData* self,
    _Outptr_ CIM_FirewallRuleSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_FirewallRuleSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_FirewallRuleSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Destruct(_Inout_ CIM_FirewallRuleSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Delete(_Inout_ CIM_FirewallRuleSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Post(
    _In_ const CIM_FirewallRuleSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_InstanceID(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_InstanceID(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_InstanceID(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_Caption(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_Caption(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_Caption(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_Description(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_Description(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_Description(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_ElementName(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_ElementName(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_ElementName(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_FromGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_FromGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_FromGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_ToGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_ToGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_ToGroupMembers(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_FromGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_FromGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_FromGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Set_ToGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_SetPtr_ToGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_FirewallRuleSettingData_Clear_ToGroupMemberType(
    _Inout_ CIM_FirewallRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** CIM_FirewallRuleSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_FirewallRuleSettingData_Self CIM_FirewallRuleSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_Load(
    _Outptr_result_maybenull_ CIM_FirewallRuleSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_Unload(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_EnumerateInstances(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_GetInstance(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_FirewallRuleSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_CreateInstance(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_FirewallRuleSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_ModifyInstance(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_FirewallRuleSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_FirewallRuleSettingData_DeleteInstance(
    _In_opt_ CIM_FirewallRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_FirewallRuleSettingData* instanceName);


#endif /* _CIM_FirewallRuleSettingData_h */
