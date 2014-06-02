/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_SystemDevice_h
#define _ABC_SystemDevice_h

#include <MI.h>
#include "CIM_SystemDevice.h"
#include "CIM_System.h"
#include "CIM_LogicalDevice.h"

/*
**==============================================================================
**
** ABC_SystemDevice [ABC_SystemDevice]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _ABC_SystemDevice /* extends CIM_SystemDevice */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_System_ConstRef GroupComponent;
    /*KEY*/ CIM_LogicalDevice_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
    /* CIM_SystemDevice properties */
    /* ABC_SystemDevice properties */
}
ABC_SystemDevice;

typedef struct _ABC_SystemDevice_Ref
{
    ABC_SystemDevice* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_SystemDevice_Ref;

typedef struct _ABC_SystemDevice_ConstRef
{
    MI_CONST ABC_SystemDevice* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_SystemDevice_ConstRef;

typedef struct _ABC_SystemDevice_Array
{
    struct _ABC_SystemDevice** data;
    MI_Uint32 size;
}
ABC_SystemDevice_Array;

typedef struct _ABC_SystemDevice_ConstArray
{
    struct _ABC_SystemDevice MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_SystemDevice_ConstArray;

typedef struct _ABC_SystemDevice_ArrayRef
{
    ABC_SystemDevice_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_SystemDevice_ArrayRef;

typedef struct _ABC_SystemDevice_ConstArrayRef
{
    ABC_SystemDevice_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_SystemDevice_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_SystemDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Construct(
    ABC_SystemDevice* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_SystemDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Clone(
    const ABC_SystemDevice* self,
    ABC_SystemDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_SystemDevice_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_SystemDevice_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Destruct(ABC_SystemDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Delete(ABC_SystemDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Post(
    const ABC_SystemDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Set_GroupComponent(
    ABC_SystemDevice* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_SetPtr_GroupComponent(
    ABC_SystemDevice* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Clear_GroupComponent(
    ABC_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Set_PartComponent(
    ABC_SystemDevice* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_SetPtr_PartComponent(
    ABC_SystemDevice* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_SystemDevice_Clear_PartComponent(
    ABC_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_SystemDevice provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_SystemDevice_Self ABC_SystemDevice_Self;

MI_EXTERN_C void MI_CALL ABC_SystemDevice_Load(
    ABC_SystemDevice_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_Unload(
    ABC_SystemDevice_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_EnumerateInstances(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_GetInstance(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_SystemDevice* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_CreateInstance(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_SystemDevice* newInstance);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_ModifyInstance(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_SystemDevice* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_DeleteInstance(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_SystemDevice* instanceName);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_AssociatorInstancesGroupComponent(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_System* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_AssociatorInstancesPartComponent(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_LogicalDevice* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_ReferenceInstancesGroupComponent(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_System* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_SystemDevice_ReferenceInstancesPartComponent(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_LogicalDevice* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_SystemDevice_h */
