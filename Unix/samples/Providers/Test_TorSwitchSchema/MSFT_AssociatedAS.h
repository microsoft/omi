/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AssociatedAS_h
#define _MSFT_AssociatedAS_h

#include <MI.h>
#include "CIM_SystemComponent.h"
#include "CIM_AutonomousSystem.h"

/*
**==============================================================================
**
** MSFT_AssociatedAS [MSFT_AssociatedAS]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _MSFT_AssociatedAS /* extends CIM_SystemComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_AutonomousSystem_ConstRef GroupComponent;
    /*KEY*/ CIM_AutonomousSystem_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
    /* MSFT_AssociatedAS properties */
}
MSFT_AssociatedAS;

typedef struct _MSFT_AssociatedAS_Ref
{
    MSFT_AssociatedAS* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAS_Ref;

typedef struct _MSFT_AssociatedAS_ConstRef
{
    MI_CONST MSFT_AssociatedAS* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAS_ConstRef;

typedef struct _MSFT_AssociatedAS_Array
{
    struct _MSFT_AssociatedAS** data;
    MI_Uint32 size;
}
MSFT_AssociatedAS_Array;

typedef struct _MSFT_AssociatedAS_ConstArray
{
    struct _MSFT_AssociatedAS MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AssociatedAS_ConstArray;

typedef struct _MSFT_AssociatedAS_ArrayRef
{
    MSFT_AssociatedAS_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAS_ArrayRef;

typedef struct _MSFT_AssociatedAS_ConstArrayRef
{
    MSFT_AssociatedAS_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAS_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AssociatedAS_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Construct(
    _Out_ MSFT_AssociatedAS* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AssociatedAS_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Clone(
    _In_ const MSFT_AssociatedAS* self,
    _Outptr_ MSFT_AssociatedAS** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AssociatedAS_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AssociatedAS_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Destruct(_Inout_ MSFT_AssociatedAS* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Delete(_Inout_ MSFT_AssociatedAS* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Post(
    _In_ const MSFT_AssociatedAS* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Set_GroupComponent(
    _Inout_ MSFT_AssociatedAS* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_SetPtr_GroupComponent(
    _Inout_ MSFT_AssociatedAS* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Clear_GroupComponent(
    _Inout_ MSFT_AssociatedAS* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Set_PartComponent(
    _Inout_ MSFT_AssociatedAS* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_SetPtr_PartComponent(
    _Inout_ MSFT_AssociatedAS* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAS_Clear_PartComponent(
    _Inout_ MSFT_AssociatedAS* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_AssociatedAS provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AssociatedAS_Self MSFT_AssociatedAS_Self;

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_Load(
    _Outptr_result_maybenull_ MSFT_AssociatedAS_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_Unload(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_EnumerateInstances(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_GetInstance(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAS* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_CreateInstance(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAS* newInstance);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_ModifyInstance(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAS* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_DeleteInstance(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAS* instanceName);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_AssociatorInstancesGroupComponent(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_AssociatorInstancesPartComponent(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_ReferenceInstancesGroupComponent(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAS_ReferenceInstancesPartComponent(
    _In_opt_ MSFT_AssociatedAS_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_AssociatedAS_h */
