/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Realizes_h
#define _ABC_Realizes_h

#include <MI.h>
#include "CIM_Realizes.h"
#include "CIM_PhysicalElement.h"
#include "CIM_LogicalDevice.h"

/*
**==============================================================================
**
** ABC_Realizes [ABC_Realizes]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _ABC_Realizes /* extends CIM_Realizes */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_PhysicalElement_ConstRef Antecedent;
    /*KEY*/ CIM_LogicalDevice_ConstRef Dependent;
    /* CIM_Realizes properties */
    /* ABC_Realizes properties */
}
ABC_Realizes;

typedef struct _ABC_Realizes_Ref
{
    ABC_Realizes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Realizes_Ref;

typedef struct _ABC_Realizes_ConstRef
{
    MI_CONST ABC_Realizes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Realizes_ConstRef;

typedef struct _ABC_Realizes_Array
{
    struct _ABC_Realizes** data;
    MI_Uint32 size;
}
ABC_Realizes_Array;

typedef struct _ABC_Realizes_ConstArray
{
    struct _ABC_Realizes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Realizes_ConstArray;

typedef struct _ABC_Realizes_ArrayRef
{
    ABC_Realizes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Realizes_ArrayRef;

typedef struct _ABC_Realizes_ConstArrayRef
{
    ABC_Realizes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Realizes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Realizes_rtti;

MI_INLINE MI_Result MI_CALL ABC_Realizes_Construct(
    ABC_Realizes* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_Realizes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Clone(
    const ABC_Realizes* self,
    ABC_Realizes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_Realizes_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_Realizes_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Destruct(ABC_Realizes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Delete(ABC_Realizes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Post(
    const ABC_Realizes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Set_Antecedent(
    ABC_Realizes* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_SetPtr_Antecedent(
    ABC_Realizes* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Clear_Antecedent(
    ABC_Realizes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Set_Dependent(
    ABC_Realizes* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_SetPtr_Dependent(
    ABC_Realizes* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Realizes_Clear_Dependent(
    ABC_Realizes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_Realizes provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_Realizes_Self ABC_Realizes_Self;

MI_EXTERN_C void MI_CALL ABC_Realizes_Load(
    ABC_Realizes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Realizes_Unload(
    ABC_Realizes_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Realizes_EnumerateInstances(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Realizes_GetInstance(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Realizes* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Realizes_CreateInstance(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Realizes* newInstance);

MI_EXTERN_C void MI_CALL ABC_Realizes_ModifyInstance(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Realizes* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Realizes_DeleteInstance(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Realizes* instanceName);

MI_EXTERN_C void MI_CALL ABC_Realizes_AssociatorInstancesAntecedent(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_PhysicalElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Realizes_AssociatorInstancesDependent(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_LogicalDevice* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Realizes_ReferenceInstancesAntecedent(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_PhysicalElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Realizes_ReferenceInstancesDependent(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_LogicalDevice* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_Realizes_h */
