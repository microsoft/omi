/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyActionInPolicyRule_h
#define _CIM_PolicyActionInPolicyRule_h

#include <MI.h>
#include "CIM_PolicyActionStructure.h"
#include "CIM_PolicyRule.h"
#include "CIM_PolicyAction.h"

/*
**==============================================================================
**
** CIM_PolicyActionInPolicyRule [CIM_PolicyActionInPolicyRule]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicyActionInPolicyRule /* extends CIM_PolicyActionStructure */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_PolicyRule_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicyAction_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* CIM_PolicyActionStructure properties */
    MI_ConstUint16Field ActionOrder;
    /* CIM_PolicyActionInPolicyRule properties */
}
CIM_PolicyActionInPolicyRule;

typedef struct _CIM_PolicyActionInPolicyRule_Ref
{
    CIM_PolicyActionInPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionInPolicyRule_Ref;

typedef struct _CIM_PolicyActionInPolicyRule_ConstRef
{
    MI_CONST CIM_PolicyActionInPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionInPolicyRule_ConstRef;

typedef struct _CIM_PolicyActionInPolicyRule_Array
{
    struct _CIM_PolicyActionInPolicyRule** data;
    MI_Uint32 size;
}
CIM_PolicyActionInPolicyRule_Array;

typedef struct _CIM_PolicyActionInPolicyRule_ConstArray
{
    struct _CIM_PolicyActionInPolicyRule MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyActionInPolicyRule_ConstArray;

typedef struct _CIM_PolicyActionInPolicyRule_ArrayRef
{
    CIM_PolicyActionInPolicyRule_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionInPolicyRule_ArrayRef;

typedef struct _CIM_PolicyActionInPolicyRule_ConstArrayRef
{
    CIM_PolicyActionInPolicyRule_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionInPolicyRule_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyActionInPolicyRule_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Construct(
    _Out_ CIM_PolicyActionInPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyActionInPolicyRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Clone(
    _In_ const CIM_PolicyActionInPolicyRule* self,
    _Outptr_ CIM_PolicyActionInPolicyRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyActionInPolicyRule_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyActionInPolicyRule_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Destruct(_Inout_ CIM_PolicyActionInPolicyRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Delete(_Inout_ CIM_PolicyActionInPolicyRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Post(
    _In_ const CIM_PolicyActionInPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Set_GroupComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self,
    _In_ const CIM_PolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_SetPtr_GroupComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self,
    _In_ const CIM_PolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Clear_GroupComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Set_PartComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self,
    _In_ const CIM_PolicyAction* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_SetPtr_PartComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self,
    _In_ const CIM_PolicyAction* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Clear_PartComponent(
    _Inout_ CIM_PolicyActionInPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Set_ActionOrder(
    _Inout_ CIM_PolicyActionInPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ActionOrder)->value = x;
    ((MI_Uint16Field*)&self->ActionOrder)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionInPolicyRule_Clear_ActionOrder(
    _Inout_ CIM_PolicyActionInPolicyRule* self)
{
    memset((void*)&self->ActionOrder, 0, sizeof(self->ActionOrder));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_PolicyActionInPolicyRule provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_PolicyActionInPolicyRule_Self CIM_PolicyActionInPolicyRule_Self;

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_Load(
    _Outptr_result_maybenull_ CIM_PolicyActionInPolicyRule_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_Unload(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_EnumerateInstances(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_GetInstance(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyActionInPolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_CreateInstance(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyActionInPolicyRule* newInstance);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_ModifyInstance(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyActionInPolicyRule* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_DeleteInstance(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyActionInPolicyRule* instanceName);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_AssociatorInstancesGroupComponent(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyRule* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_AssociatorInstancesPartComponent(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyAction* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_ReferenceInstancesGroupComponent(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyActionInPolicyRule_ReferenceInstancesPartComponent(
    _In_opt_ CIM_PolicyActionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyAction* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_PolicyActionInPolicyRule_h */
