/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyRuleSettingData_h
#define _CIM_NetworkPolicyRuleSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyRuleSettingData [CIM_NetworkPolicyRuleSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyRuleSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_NetworkPolicyRuleSettingData properties */
}
CIM_NetworkPolicyRuleSettingData;

typedef struct _CIM_NetworkPolicyRuleSettingData_Ref
{
    CIM_NetworkPolicyRuleSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRuleSettingData_Ref;

typedef struct _CIM_NetworkPolicyRuleSettingData_ConstRef
{
    MI_CONST CIM_NetworkPolicyRuleSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRuleSettingData_ConstRef;

typedef struct _CIM_NetworkPolicyRuleSettingData_Array
{
    struct _CIM_NetworkPolicyRuleSettingData** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyRuleSettingData_Array;

typedef struct _CIM_NetworkPolicyRuleSettingData_ConstArray
{
    struct _CIM_NetworkPolicyRuleSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyRuleSettingData_ConstArray;

typedef struct _CIM_NetworkPolicyRuleSettingData_ArrayRef
{
    CIM_NetworkPolicyRuleSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRuleSettingData_ArrayRef;

typedef struct _CIM_NetworkPolicyRuleSettingData_ConstArrayRef
{
    CIM_NetworkPolicyRuleSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRuleSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyRuleSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Construct(
    _Out_ CIM_NetworkPolicyRuleSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyRuleSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Clone(
    _In_ const CIM_NetworkPolicyRuleSettingData* self,
    _Outptr_ CIM_NetworkPolicyRuleSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyRuleSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyRuleSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Destruct(_Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Delete(_Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Post(
    _In_ const CIM_NetworkPolicyRuleSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Set_Caption(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Clear_Caption(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Set_Description(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Clear_Description(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Set_ElementName(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRuleSettingData_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyRuleSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** CIM_NetworkPolicyRuleSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyRuleSettingData_Self CIM_NetworkPolicyRuleSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyRuleSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_Unload(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_GetInstance(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRuleSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_CreateInstance(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRuleSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRuleSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRuleSettingData_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyRuleSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRuleSettingData* instanceName);


#endif /* _CIM_NetworkPolicyRuleSettingData_h */
