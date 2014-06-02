/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ASBGPIPEndpoints_h
#define _MSFT_ASBGPIPEndpoints_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_IPProtocolEndpoint.h"

/*
**==============================================================================
**
** MSFT_ASBGPIPEndpoints [MSFT_ASBGPIPEndpoints]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _MSFT_ASBGPIPEndpoints
{
    MI_Instance __instance;
    /* MSFT_ASBGPIPEndpoints properties */
    /*KEY*/ CIM_ManagedElement_ConstRef GroupComponent;
    /*KEY*/ CIM_IPProtocolEndpoint_ConstRef PartComponent;
}
MSFT_ASBGPIPEndpoints;

typedef struct _MSFT_ASBGPIPEndpoints_Ref
{
    MSFT_ASBGPIPEndpoints* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ASBGPIPEndpoints_Ref;

typedef struct _MSFT_ASBGPIPEndpoints_ConstRef
{
    MI_CONST MSFT_ASBGPIPEndpoints* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ASBGPIPEndpoints_ConstRef;

typedef struct _MSFT_ASBGPIPEndpoints_Array
{
    struct _MSFT_ASBGPIPEndpoints** data;
    MI_Uint32 size;
}
MSFT_ASBGPIPEndpoints_Array;

typedef struct _MSFT_ASBGPIPEndpoints_ConstArray
{
    struct _MSFT_ASBGPIPEndpoints MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ASBGPIPEndpoints_ConstArray;

typedef struct _MSFT_ASBGPIPEndpoints_ArrayRef
{
    MSFT_ASBGPIPEndpoints_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ASBGPIPEndpoints_ArrayRef;

typedef struct _MSFT_ASBGPIPEndpoints_ConstArrayRef
{
    MSFT_ASBGPIPEndpoints_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ASBGPIPEndpoints_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ASBGPIPEndpoints_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Construct(
    _Out_ MSFT_ASBGPIPEndpoints* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ASBGPIPEndpoints_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Clone(
    _In_ const MSFT_ASBGPIPEndpoints* self,
    _Outptr_ MSFT_ASBGPIPEndpoints** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ASBGPIPEndpoints_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ASBGPIPEndpoints_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Destruct(_Inout_ MSFT_ASBGPIPEndpoints* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Delete(_Inout_ MSFT_ASBGPIPEndpoints* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Post(
    _In_ const MSFT_ASBGPIPEndpoints* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Set_GroupComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_SetPtr_GroupComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Clear_GroupComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Set_PartComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self,
    _In_ const CIM_IPProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_SetPtr_PartComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self,
    _In_ const CIM_IPProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ASBGPIPEndpoints_Clear_PartComponent(
    _Inout_ MSFT_ASBGPIPEndpoints* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_ASBGPIPEndpoints provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_ASBGPIPEndpoints_Self MSFT_ASBGPIPEndpoints_Self;

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_Load(
    _Outptr_result_maybenull_ MSFT_ASBGPIPEndpoints_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_Unload(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_EnumerateInstances(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_GetInstance(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ASBGPIPEndpoints* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_CreateInstance(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ASBGPIPEndpoints* newInstance);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_ModifyInstance(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ASBGPIPEndpoints* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_DeleteInstance(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ASBGPIPEndpoints* instanceName);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_AssociatorInstancesGroupComponent(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_AssociatorInstancesPartComponent(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_ReferenceInstancesGroupComponent(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ASBGPIPEndpoints_ReferenceInstancesPartComponent(
    _In_opt_ MSFT_ASBGPIPEndpoints_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_ASBGPIPEndpoints_h */
