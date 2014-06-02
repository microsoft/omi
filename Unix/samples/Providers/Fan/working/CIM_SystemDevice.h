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
    CIM_SystemDevice* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_SystemDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clone(
    const CIM_SystemDevice* self,
    CIM_SystemDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SystemDevice_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SystemDevice_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Destruct(CIM_SystemDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Delete(CIM_SystemDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Post(
    const CIM_SystemDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Set_GroupComponent(
    CIM_SystemDevice* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_SetPtr_GroupComponent(
    CIM_SystemDevice* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clear_GroupComponent(
    CIM_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Set_PartComponent(
    CIM_SystemDevice* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_SetPtr_PartComponent(
    CIM_SystemDevice* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemDevice_Clear_PartComponent(
    CIM_SystemDevice* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_SystemDevice_h */
