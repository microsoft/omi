/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AssociatedAddressFamily_h
#define _MSFT_AssociatedAddressFamily_h

#include <MI.h>
#include "CIM_SystemComponent.h"
#include "CIM_AutonomousSystem.h"
#include "CIM_Collection.h"

/*
**==============================================================================
**
** MSFT_AssociatedAddressFamily [MSFT_AssociatedAddressFamily]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _MSFT_AssociatedAddressFamily /* extends CIM_SystemComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_AutonomousSystem_ConstRef GroupComponent;
    /*KEY*/ CIM_Collection_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
    /* MSFT_AssociatedAddressFamily properties */
}
MSFT_AssociatedAddressFamily;

typedef struct _MSFT_AssociatedAddressFamily_Ref
{
    MSFT_AssociatedAddressFamily* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamily_Ref;

typedef struct _MSFT_AssociatedAddressFamily_ConstRef
{
    MI_CONST MSFT_AssociatedAddressFamily* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamily_ConstRef;

typedef struct _MSFT_AssociatedAddressFamily_Array
{
    struct _MSFT_AssociatedAddressFamily** data;
    MI_Uint32 size;
}
MSFT_AssociatedAddressFamily_Array;

typedef struct _MSFT_AssociatedAddressFamily_ConstArray
{
    struct _MSFT_AssociatedAddressFamily MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AssociatedAddressFamily_ConstArray;

typedef struct _MSFT_AssociatedAddressFamily_ArrayRef
{
    MSFT_AssociatedAddressFamily_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamily_ArrayRef;

typedef struct _MSFT_AssociatedAddressFamily_ConstArrayRef
{
    MSFT_AssociatedAddressFamily_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamily_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AssociatedAddressFamily_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Construct(
    _Out_ MSFT_AssociatedAddressFamily* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AssociatedAddressFamily_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Clone(
    _In_ const MSFT_AssociatedAddressFamily* self,
    _Outptr_ MSFT_AssociatedAddressFamily** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AssociatedAddressFamily_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AssociatedAddressFamily_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Destruct(_Inout_ MSFT_AssociatedAddressFamily* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Delete(_Inout_ MSFT_AssociatedAddressFamily* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Post(
    _In_ const MSFT_AssociatedAddressFamily* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Set_GroupComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_SetPtr_GroupComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self,
    _In_ const CIM_AutonomousSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Clear_GroupComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Set_PartComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_SetPtr_PartComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamily_Clear_PartComponent(
    _Inout_ MSFT_AssociatedAddressFamily* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_AssociatedAddressFamily provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AssociatedAddressFamily_Self MSFT_AssociatedAddressFamily_Self;

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_Load(
    _Outptr_result_maybenull_ MSFT_AssociatedAddressFamily_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_Unload(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_EnumerateInstances(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_GetInstance(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamily* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_CreateInstance(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamily* newInstance);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_ModifyInstance(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamily* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_DeleteInstance(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamily* instanceName);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_AssociatorInstancesGroupComponent(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_AssociatorInstancesPartComponent(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_ReferenceInstancesGroupComponent(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AutonomousSystem* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamily_ReferenceInstancesPartComponent(
    _In_opt_ MSFT_AssociatedAddressFamily_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_AssociatedAddressFamily_h */
