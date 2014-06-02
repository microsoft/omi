/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyAction_h
#define _CIM_NetworkPolicyAction_h

#include <MI.h>
#include "CIM_Policy.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyAction [CIM_NetworkPolicyAction]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyAction /* extends CIM_Policy */
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
    /* CIM_NetworkPolicyAction properties */
    MI_ConstUint16AField ActionType;
    MI_ConstStringAField ActionTypeValue;
}
CIM_NetworkPolicyAction;

typedef struct _CIM_NetworkPolicyAction_Ref
{
    CIM_NetworkPolicyAction* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyAction_Ref;

typedef struct _CIM_NetworkPolicyAction_ConstRef
{
    MI_CONST CIM_NetworkPolicyAction* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyAction_ConstRef;

typedef struct _CIM_NetworkPolicyAction_Array
{
    struct _CIM_NetworkPolicyAction** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyAction_Array;

typedef struct _CIM_NetworkPolicyAction_ConstArray
{
    struct _CIM_NetworkPolicyAction MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyAction_ConstArray;

typedef struct _CIM_NetworkPolicyAction_ArrayRef
{
    CIM_NetworkPolicyAction_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyAction_ArrayRef;

typedef struct _CIM_NetworkPolicyAction_ConstArrayRef
{
    CIM_NetworkPolicyAction_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyAction_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyAction_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Construct(
    _Out_ CIM_NetworkPolicyAction* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyAction_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clone(
    _In_ const CIM_NetworkPolicyAction* self,
    _Outptr_ CIM_NetworkPolicyAction** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyAction_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyAction_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Destruct(_Inout_ CIM_NetworkPolicyAction* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Delete(_Inout_ CIM_NetworkPolicyAction* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Post(
    _In_ const CIM_NetworkPolicyAction* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_Caption(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_Caption(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_Description(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_Description(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_ElementName(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_CommonName(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_CommonName(
    _Inout_ CIM_NetworkPolicyAction* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_CommonName(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_ActionType(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_ActionType(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_ActionType(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Set_ActionTypeValue(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_SetPtr_ActionTypeValue(
    _Inout_ CIM_NetworkPolicyAction* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyAction_Clear_ActionTypeValue(
    _Inout_ CIM_NetworkPolicyAction* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** CIM_NetworkPolicyAction provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyAction_Self CIM_NetworkPolicyAction_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyAction_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_Unload(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_GetInstance(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyAction* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_CreateInstance(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyAction* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyAction* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyAction_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyAction_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyAction* instanceName);


#endif /* _CIM_NetworkPolicyAction_h */
