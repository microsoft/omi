/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_MatchedPolicyComponent_h
#define _MSFT_MatchedPolicyComponent_h

#include <MI.h>
#include "CIM_PolicyComponent.h"
#include "CIM_NetworkPolicyRule.h"
#include "CIM_PolicySet.h"

/*
**==============================================================================
**
** MSFT_MatchedPolicyComponent [MSFT_MatchedPolicyComponent]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _MSFT_MatchedPolicyComponent /* extends CIM_PolicyComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_NetworkPolicyRule_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicySet_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* MSFT_MatchedPolicyComponent properties */
}
MSFT_MatchedPolicyComponent;

typedef struct _MSFT_MatchedPolicyComponent_Ref
{
    MSFT_MatchedPolicyComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_MatchedPolicyComponent_Ref;

typedef struct _MSFT_MatchedPolicyComponent_ConstRef
{
    MI_CONST MSFT_MatchedPolicyComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_MatchedPolicyComponent_ConstRef;

typedef struct _MSFT_MatchedPolicyComponent_Array
{
    struct _MSFT_MatchedPolicyComponent** data;
    MI_Uint32 size;
}
MSFT_MatchedPolicyComponent_Array;

typedef struct _MSFT_MatchedPolicyComponent_ConstArray
{
    struct _MSFT_MatchedPolicyComponent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_MatchedPolicyComponent_ConstArray;

typedef struct _MSFT_MatchedPolicyComponent_ArrayRef
{
    MSFT_MatchedPolicyComponent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_MatchedPolicyComponent_ArrayRef;

typedef struct _MSFT_MatchedPolicyComponent_ConstArrayRef
{
    MSFT_MatchedPolicyComponent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_MatchedPolicyComponent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_MatchedPolicyComponent_rtti;

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Construct(
    _Out_ MSFT_MatchedPolicyComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_MatchedPolicyComponent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Clone(
    _In_ const MSFT_MatchedPolicyComponent* self,
    _Outptr_ MSFT_MatchedPolicyComponent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_MatchedPolicyComponent_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_MatchedPolicyComponent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Destruct(_Inout_ MSFT_MatchedPolicyComponent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Delete(_Inout_ MSFT_MatchedPolicyComponent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Post(
    _In_ const MSFT_MatchedPolicyComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Set_GroupComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_SetPtr_GroupComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Clear_GroupComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Set_PartComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_SetPtr_PartComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_MatchedPolicyComponent_Clear_PartComponent(
    _Inout_ MSFT_MatchedPolicyComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_MatchedPolicyComponent provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_MatchedPolicyComponent_Self MSFT_MatchedPolicyComponent_Self;

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_Load(
    _Outptr_result_maybenull_ MSFT_MatchedPolicyComponent_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_Unload(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_EnumerateInstances(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_GetInstance(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_MatchedPolicyComponent* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_CreateInstance(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_MatchedPolicyComponent* newInstance);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_ModifyInstance(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_MatchedPolicyComponent* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_DeleteInstance(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_MatchedPolicyComponent* instanceName);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_AssociatorInstancesGroupComponent(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_AssociatorInstancesPartComponent(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_ReferenceInstancesGroupComponent(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_MatchedPolicyComponent_ReferenceInstancesPartComponent(
    _In_opt_ MSFT_MatchedPolicyComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_MatchedPolicyComponent_h */
