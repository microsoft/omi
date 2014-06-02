/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SystemComponent_h
#define _CIM_SystemComponent_h

#include <MI.h>
#include "CIM_Component.h"
#include "CIM_System.h"
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_SystemComponent [CIM_SystemComponent]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_SystemComponent /* extends CIM_Component */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_System_ConstRef GroupComponent;
    /*KEY*/ CIM_ManagedSystemElement_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
}
CIM_SystemComponent;

typedef struct _CIM_SystemComponent_Ref
{
    CIM_SystemComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_Ref;

typedef struct _CIM_SystemComponent_ConstRef
{
    MI_CONST CIM_SystemComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ConstRef;

typedef struct _CIM_SystemComponent_Array
{
    struct _CIM_SystemComponent** data;
    MI_Uint32 size;
}
CIM_SystemComponent_Array;

typedef struct _CIM_SystemComponent_ConstArray
{
    struct _CIM_SystemComponent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SystemComponent_ConstArray;

typedef struct _CIM_SystemComponent_ArrayRef
{
    CIM_SystemComponent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ArrayRef;

typedef struct _CIM_SystemComponent_ConstArrayRef
{
    CIM_SystemComponent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SystemComponent_rtti;

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Construct(
    _Out_ CIM_SystemComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_SystemComponent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clone(
    _In_ const CIM_SystemComponent* self,
    _Outptr_ CIM_SystemComponent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SystemComponent_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SystemComponent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Destruct(_Inout_ CIM_SystemComponent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Delete(_Inout_ CIM_SystemComponent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Post(
    _In_ const CIM_SystemComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Set_GroupComponent(
    _Inout_ CIM_SystemComponent* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_SetPtr_GroupComponent(
    _Inout_ CIM_SystemComponent* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clear_GroupComponent(
    _Inout_ CIM_SystemComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Set_PartComponent(
    _Inout_ CIM_SystemComponent* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_SetPtr_PartComponent(
    _Inout_ CIM_SystemComponent* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clear_PartComponent(
    _Inout_ CIM_SystemComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_SystemComponent provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_SystemComponent_Self CIM_SystemComponent_Self;

MI_EXTERN_C void MI_CALL CIM_SystemComponent_Load(
    _Outptr_result_maybenull_ CIM_SystemComponent_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_Unload(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_EnumerateInstances(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_GetInstance(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemComponent* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_CreateInstance(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemComponent* newInstance);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_ModifyInstance(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemComponent* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_DeleteInstance(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemComponent* instanceName);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_AssociatorInstancesGroupComponent(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_AssociatorInstancesPartComponent(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedSystemElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_ReferenceInstancesGroupComponent(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemComponent_ReferenceInstancesPartComponent(
    _In_opt_ CIM_SystemComponent_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedSystemElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_SystemComponent_h */
