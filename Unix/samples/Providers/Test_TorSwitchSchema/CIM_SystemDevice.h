/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SystemDevice_h
#define _CIM_SystemDevice_h

#include <MI.h>
#include "CIM_SystemComponent.h"
#include "CIM_System.h"
#include "CIM_LogicalDevice.h"

/*
**==============================================================================
**
** CIM_SystemDevice [CIM_SystemDevice]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_SystemDevice /* extends CIM_SystemComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_System_ConstRef GroupComponent;
    /*KEY*/ CIM_LogicalDevice_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
    /* CIM_SystemDevice properties */
}
CIM_SystemDevice;

typedef struct _CIM_SystemDevice_Ref
{
    CIM_SystemDevice* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemDevice_Ref;

typedef struct _CIM_SystemDevice_ConstRef
{
    MI_CONST CIM_SystemDevice* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemDevice_ConstRef;

typedef struct _CIM_SystemDevice_Array
{
    struct _CIM_SystemDevice** data;
    MI_Uint32 size;
}
CIM_SystemDevice_Array;

typedef struct _CIM_SystemDevice_ConstArray
{
    struct _CIM_SystemDevice MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SystemDevice_ConstArray;

typedef struct _CIM_SystemDevice_ArrayRef
{
    CIM_SystemDevice_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemDevice_ArrayRef;

typedef struct _CIM_SystemDevice_ConstArrayRef
{
    CIM_SystemDevice_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemDevice_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SystemDevice_rtti;

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Construct(
    _Out_ CIM_SystemDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_SystemDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clone(
    _In_ const CIM_SystemDevice* self,
    _Outptr_ CIM_SystemDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SystemDevice_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SystemDevice_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Destruct(_Inout_ CIM_SystemDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Delete(_Inout_ CIM_SystemDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Post(
    _In_ const CIM_SystemDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Set_GroupComponent(
    _Inout_ CIM_SystemDevice* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_SetPtr_GroupComponent(
    _Inout_ CIM_SystemDevice* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clear_GroupComponent(
    _Inout_ CIM_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Set_PartComponent(
    _Inout_ CIM_SystemDevice* self,
    _In_ const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_SetPtr_PartComponent(
    _Inout_ CIM_SystemDevice* self,
    _In_ const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clear_PartComponent(
    _Inout_ CIM_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_SystemDevice provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_SystemDevice_Self CIM_SystemDevice_Self;

MI_EXTERN_C void MI_CALL CIM_SystemDevice_Load(
    _Outptr_result_maybenull_ CIM_SystemDevice_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_Unload(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_EnumerateInstances(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_GetInstance(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemDevice* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_CreateInstance(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemDevice* newInstance);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_ModifyInstance(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemDevice* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_DeleteInstance(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemDevice* instanceName);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_AssociatorInstancesGroupComponent(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_AssociatorInstancesPartComponent(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LogicalDevice* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_ReferenceInstancesGroupComponent(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SystemDevice_ReferenceInstancesPartComponent(
    _In_opt_ CIM_SystemDevice_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LogicalDevice* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_SystemDevice_h */
