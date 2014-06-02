/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Privilege_h
#define _CIM_Privilege_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Privilege [CIM_Privilege]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_Privilege /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Privilege properties */
    MI_ConstBooleanField PrivilegeGranted;
    MI_ConstUint16AField Activities;
    MI_ConstStringAField ActivityQualifiers;
    MI_ConstUint16AField QualifierFormats;
    MI_ConstBooleanField RepresentsAuthorizationRights;
}
CIM_Privilege;

typedef struct _CIM_Privilege_Ref
{
    CIM_Privilege* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Privilege_Ref;

typedef struct _CIM_Privilege_ConstRef
{
    MI_CONST CIM_Privilege* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Privilege_ConstRef;

typedef struct _CIM_Privilege_Array
{
    struct _CIM_Privilege** data;
    MI_Uint32 size;
}
CIM_Privilege_Array;

typedef struct _CIM_Privilege_ConstArray
{
    struct _CIM_Privilege MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Privilege_ConstArray;

typedef struct _CIM_Privilege_ArrayRef
{
    CIM_Privilege_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Privilege_ArrayRef;

typedef struct _CIM_Privilege_ConstArrayRef
{
    CIM_Privilege_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Privilege_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Privilege_rtti;

MI_INLINE MI_Result MI_CALL CIM_Privilege_Construct(
    _Out_ CIM_Privilege* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_Privilege_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clone(
    _In_ const CIM_Privilege* self,
    _Outptr_ CIM_Privilege** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Privilege_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Privilege_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Destruct(_Inout_ CIM_Privilege* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Delete(_Inout_ CIM_Privilege* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Post(
    _In_ const CIM_Privilege* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_InstanceID(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_InstanceID(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_InstanceID(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_Caption(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_Caption(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_Caption(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_Description(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_Description(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_Description(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_ElementName(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_ElementName(
    _Inout_ CIM_Privilege* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_ElementName(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_PrivilegeGranted(
    _Inout_ CIM_Privilege* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PrivilegeGranted)->value = x;
    ((MI_BooleanField*)&self->PrivilegeGranted)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_PrivilegeGranted(
    _Inout_ CIM_Privilege* self)
{
    memset((void*)&self->PrivilegeGranted, 0, sizeof(self->PrivilegeGranted));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_Activities(
    _Inout_ CIM_Privilege* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_Activities(
    _Inout_ CIM_Privilege* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_Activities(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_ActivityQualifiers(
    _Inout_ CIM_Privilege* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_ActivityQualifiers(
    _Inout_ CIM_Privilege* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_ActivityQualifiers(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_QualifierFormats(
    _Inout_ CIM_Privilege* self,
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

MI_INLINE MI_Result MI_CALL CIM_Privilege_SetPtr_QualifierFormats(
    _Inout_ CIM_Privilege* self,
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

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_QualifierFormats(
    _Inout_ CIM_Privilege* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Set_RepresentsAuthorizationRights(
    _Inout_ CIM_Privilege* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RepresentsAuthorizationRights)->value = x;
    ((MI_BooleanField*)&self->RepresentsAuthorizationRights)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Privilege_Clear_RepresentsAuthorizationRights(
    _Inout_ CIM_Privilege* self)
{
    memset((void*)&self->RepresentsAuthorizationRights, 0, sizeof(self->RepresentsAuthorizationRights));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_Privilege provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_Privilege_Self CIM_Privilege_Self;

MI_EXTERN_C void MI_CALL CIM_Privilege_Load(
    _Outptr_result_maybenull_ CIM_Privilege_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Privilege_Unload(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Privilege_EnumerateInstances(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_Privilege_GetInstance(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Privilege* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Privilege_CreateInstance(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Privilege* newInstance);

MI_EXTERN_C void MI_CALL CIM_Privilege_ModifyInstance(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Privilege* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Privilege_DeleteInstance(
    _In_opt_ CIM_Privilege_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Privilege* instanceName);


#endif /* _CIM_Privilege_h */
