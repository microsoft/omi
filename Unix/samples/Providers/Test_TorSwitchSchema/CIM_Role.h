/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Role_h
#define _CIM_Role_h

#include <MI.h>
#include "CIM_Collection.h"

/*
**==============================================================================
**
** CIM_Role [CIM_Role]
**
** Keys:
**    CreationClassName
**    Name
**
**==============================================================================
*/

typedef struct _CIM_Role /* extends CIM_Collection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_Role properties */
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField BusinessCategory;
    MI_ConstStringField CommonName;
    MI_ConstUint16AField RoleCharacteristics;
}
CIM_Role;

typedef struct _CIM_Role_Ref
{
    CIM_Role* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Role_Ref;

typedef struct _CIM_Role_ConstRef
{
    MI_CONST CIM_Role* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Role_ConstRef;

typedef struct _CIM_Role_Array
{
    struct _CIM_Role** data;
    MI_Uint32 size;
}
CIM_Role_Array;

typedef struct _CIM_Role_ConstArray
{
    struct _CIM_Role MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Role_ConstArray;

typedef struct _CIM_Role_ArrayRef
{
    CIM_Role_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Role_ArrayRef;

typedef struct _CIM_Role_ConstArrayRef
{
    CIM_Role_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Role_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Role_rtti;

MI_INLINE MI_Result MI_CALL CIM_Role_Construct(
    _Out_ CIM_Role* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_Role_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clone(
    _In_ const CIM_Role* self,
    _Outptr_ CIM_Role** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Role_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Role_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Role_Destruct(_Inout_ CIM_Role* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Delete(_Inout_ CIM_Role* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Post(
    _In_ const CIM_Role* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_InstanceID(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_InstanceID(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_InstanceID(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_Caption(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_Caption(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_Caption(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_Description(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_Description(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_Description(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_ElementName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_ElementName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_ElementName(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_CreationClassName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_CreationClassName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_CreationClassName(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_Name(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_Name(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_Name(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_BusinessCategory(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_BusinessCategory(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_BusinessCategory(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_CommonName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_CommonName(
    _Inout_ CIM_Role* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_CommonName(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Set_RoleCharacteristics(
    _Inout_ CIM_Role* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Role_SetPtr_RoleCharacteristics(
    _Inout_ CIM_Role* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Role_Clear_RoleCharacteristics(
    _Inout_ CIM_Role* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** CIM_Role provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_Role_Self CIM_Role_Self;

MI_EXTERN_C void MI_CALL CIM_Role_Load(
    _Outptr_result_maybenull_ CIM_Role_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Role_Unload(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_Role_EnumerateInstances(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_Role_GetInstance(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Role* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Role_CreateInstance(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Role* newInstance);

MI_EXTERN_C void MI_CALL CIM_Role_ModifyInstance(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Role* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_Role_DeleteInstance(
    _In_opt_ CIM_Role_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Role* instanceName);


#endif /* _CIM_Role_h */
