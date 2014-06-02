/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_AssociatedSensor_h
#define _ABC_AssociatedSensor_h

#include <MI.h>
#include "CIM_AssociatedSensor.h"
#include "ABC_NumericSensor.h"
#include "ABC_Fan.h"

/*
**==============================================================================
**
** ABC_AssociatedSensor [ABC_AssociatedSensor]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _ABC_AssociatedSensor /* extends CIM_AssociatedSensor */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ ABC_NumericSensor_ConstRef Antecedent;
    /*KEY*/ ABC_Fan_ConstRef Dependent;
    /* CIM_AssociatedSensor properties */
    /* ABC_AssociatedSensor properties */
}
ABC_AssociatedSensor;

typedef struct _ABC_AssociatedSensor_Ref
{
    ABC_AssociatedSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedSensor_Ref;

typedef struct _ABC_AssociatedSensor_ConstRef
{
    MI_CONST ABC_AssociatedSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedSensor_ConstRef;

typedef struct _ABC_AssociatedSensor_Array
{
    struct _ABC_AssociatedSensor** data;
    MI_Uint32 size;
}
ABC_AssociatedSensor_Array;

typedef struct _ABC_AssociatedSensor_ConstArray
{
    struct _ABC_AssociatedSensor MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_AssociatedSensor_ConstArray;

typedef struct _ABC_AssociatedSensor_ArrayRef
{
    ABC_AssociatedSensor_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedSensor_ArrayRef;

typedef struct _ABC_AssociatedSensor_ConstArrayRef
{
    ABC_AssociatedSensor_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_AssociatedSensor_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_AssociatedSensor_rtti;

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Construct(
    ABC_AssociatedSensor* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_AssociatedSensor_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Clone(
    const ABC_AssociatedSensor* self,
    ABC_AssociatedSensor** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_AssociatedSensor_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_AssociatedSensor_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Destruct(ABC_AssociatedSensor* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Delete(ABC_AssociatedSensor* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Post(
    const ABC_AssociatedSensor* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Set_Antecedent(
    ABC_AssociatedSensor* self,
    const ABC_NumericSensor* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_SetPtr_Antecedent(
    ABC_AssociatedSensor* self,
    const ABC_NumericSensor* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Clear_Antecedent(
    ABC_AssociatedSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Set_Dependent(
    ABC_AssociatedSensor* self,
    const ABC_Fan* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_SetPtr_Dependent(
    ABC_AssociatedSensor* self,
    const ABC_Fan* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_AssociatedSensor_Clear_Dependent(
    ABC_AssociatedSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_AssociatedSensor provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_AssociatedSensor_Self ABC_AssociatedSensor_Self;

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_Load(
    ABC_AssociatedSensor_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_Unload(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_EnumerateInstances(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_GetInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_CreateInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* newInstance);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_ModifyInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_DeleteInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* instanceName);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_AssociatorInstancesAntecedent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_AssociatorInstancesDependent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_ReferenceInstancesAntecedent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_AssociatedSensor_ReferenceInstancesDependent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_AssociatedSensor_h */
