/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_AssociatedCooling_h
#define _ABC_AssociatedCooling_h

#include <MI.h>
#include "CIM_AssociatedCooling.h"
#include "CIM_CoolingDevice.h"
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** ABC_AssociatedCooling [ABC_AssociatedCooling]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _ABC_AssociatedCooling /* extends CIM_AssociatedCooling */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_CoolingDevice_ConstRef Antecedent;
    /*KEY*/ CIM_ManagedSystemElement_ConstRef Dependent;
    /* CIM_AssociatedCooling properties */
    /* ABC_AssociatedCooling properties */
}
ABC_AssociatedCooling;

typedef struct _ABC_AssociatedCooling_Ref
{
    ABC_AssociatedCooling* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedCooling_Ref;

typedef struct _ABC_AssociatedCooling_ConstRef
{
    MI_CONST ABC_AssociatedCooling* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedCooling_ConstRef;

typedef struct _ABC_AssociatedCooling_Array
{
    struct _ABC_AssociatedCooling** data;
    MI_Uint32 size;
}
ABC_AssociatedCooling_Array;

typedef struct _ABC_AssociatedCooling_ConstArray
{
    struct _ABC_AssociatedCooling MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_AssociatedCooling_ConstArray;

typedef struct _ABC_AssociatedCooling_ArrayRef
{
    ABC_AssociatedCooling_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedCooling_ArrayRef;

typedef struct _ABC_AssociatedCooling_ConstArrayRef
{
    ABC_AssociatedCooling_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedCooling_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_AssociatedCooling_rtti;

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Construct(
    ABC_AssociatedCooling* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_AssociatedCooling_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Clone(
    const ABC_AssociatedCooling* self,
    ABC_AssociatedCooling** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_AssociatedCooling_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_AssociatedCooling_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Destruct(ABC_AssociatedCooling* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Delete(ABC_AssociatedCooling* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Post(
    const ABC_AssociatedCooling* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Set_Antecedent(
    ABC_AssociatedCooling* self,
    const CIM_CoolingDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_SetPtr_Antecedent(
    ABC_AssociatedCooling* self,
    const CIM_CoolingDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Clear_Antecedent(
    ABC_AssociatedCooling* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Set_Dependent(
    ABC_AssociatedCooling* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_SetPtr_Dependent(
    ABC_AssociatedCooling* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedCooling_Clear_Dependent(
    ABC_AssociatedCooling* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_AssociatedCooling provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_AssociatedCooling_Self ABC_AssociatedCooling_Self;

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_Load(
    ABC_AssociatedCooling_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_Unload(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_EnumerateInstances(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_GetInstance(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedCooling* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_CreateInstance(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedCooling* newInstance);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_ModifyInstance(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedCooling* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_DeleteInstance(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedCooling* instanceName);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_AssociatorInstancesAntecedent(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_CoolingDevice* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_AssociatorInstancesDependent(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedSystemElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_ReferenceInstancesAntecedent(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_CoolingDevice* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedCooling_ReferenceInstancesDependent(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedSystemElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_AssociatedCooling_h */
