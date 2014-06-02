/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyActionSettingData_h
#define _CIM_NetworkPolicyActionSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyActionSettingData [CIM_NetworkPolicyActionSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyActionSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_NetworkPolicyActionSettingData properties */
}
CIM_NetworkPolicyActionSettingData;

typedef struct _CIM_NetworkPolicyActionSettingData_Ref
{
    CIM_NetworkPolicyActionSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyActionSettingData_Ref;

typedef struct _CIM_NetworkPolicyActionSettingData_ConstRef
{
    MI_CONST CIM_NetworkPolicyActionSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyActionSettingData_ConstRef;

typedef struct _CIM_NetworkPolicyActionSettingData_Array
{
    struct _CIM_NetworkPolicyActionSettingData** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyActionSettingData_Array;

typedef struct _CIM_NetworkPolicyActionSettingData_ConstArray
{
    struct _CIM_NetworkPolicyActionSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyActionSettingData_ConstArray;

typedef struct _CIM_NetworkPolicyActionSettingData_ArrayRef
{
    CIM_NetworkPolicyActionSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyActionSettingData_ArrayRef;

typedef struct _CIM_NetworkPolicyActionSettingData_ConstArrayRef
{
    CIM_NetworkPolicyActionSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyActionSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyActionSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Construct(
    _Out_ CIM_NetworkPolicyActionSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyActionSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Clone(
    _In_ const CIM_NetworkPolicyActionSettingData* self,
    _Outptr_ CIM_NetworkPolicyActionSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyActionSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyActionSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Destruct(_Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Delete(_Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Post(
    _In_ const CIM_NetworkPolicyActionSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Set_Caption(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Clear_Caption(
    _Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Set_Description(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Clear_Description(
    _Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Set_ElementName(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyActionSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyActionSettingData_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyActionSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** CIM_NetworkPolicyActionSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyActionSettingData_Self CIM_NetworkPolicyActionSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyActionSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_Unload(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_GetInstance(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyActionSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_CreateInstance(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyActionSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyActionSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyActionSettingData_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyActionSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyActionSettingData* instanceName);


#endif /* _CIM_NetworkPolicyActionSettingData_h */
