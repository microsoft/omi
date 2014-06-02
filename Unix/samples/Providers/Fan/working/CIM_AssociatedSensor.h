/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AssociatedSensor_h
#define _CIM_AssociatedSensor_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_Sensor.h"
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_AssociatedSensor [CIM_AssociatedSensor]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_AssociatedSensor /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_Sensor_ConstRef Antecedent;
    /*KEY*/ CIM_ManagedSystemElement_ConstRef Dependent;
    /* CIM_AssociatedSensor properties */
}
CIM_AssociatedSensor;

typedef struct _CIM_AssociatedSensor_Ref
{
    CIM_AssociatedSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedSensor_Ref;

typedef struct _CIM_AssociatedSensor_ConstRef
{
    MI_CONST CIM_AssociatedSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedSensor_ConstRef;

typedef struct _CIM_AssociatedSensor_Array
{
    struct _CIM_AssociatedSensor** data;
    MI_Uint32 size;
}
CIM_AssociatedSensor_Array;

typedef struct _CIM_AssociatedSensor_ConstArray
{
    struct _CIM_AssociatedSensor MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AssociatedSensor_ConstArray;

typedef struct _CIM_AssociatedSensor_ArrayRef
{
    CIM_AssociatedSensor_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedSensor_ArrayRef;

typedef struct _CIM_AssociatedSensor_ConstArrayRef
{
    CIM_AssociatedSensor_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedSensor_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AssociatedSensor_rtti;

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Construct(
    CIM_AssociatedSensor* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_AssociatedSensor_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Clone(
    const CIM_AssociatedSensor* self,
    CIM_AssociatedSensor** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AssociatedSensor_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AssociatedSensor_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Destruct(CIM_AssociatedSensor* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Delete(CIM_AssociatedSensor* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Post(
    const CIM_AssociatedSensor* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Set_Antecedent(
    CIM_AssociatedSensor* self,
    const CIM_Sensor* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_SetPtr_Antecedent(
    CIM_AssociatedSensor* self,
    const CIM_Sensor* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Clear_Antecedent(
    CIM_AssociatedSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Set_Dependent(
    CIM_AssociatedSensor* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_SetPtr_Dependent(
    CIM_AssociatedSensor* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedSensor_Clear_Dependent(
    CIM_AssociatedSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_AssociatedSensor_h */
