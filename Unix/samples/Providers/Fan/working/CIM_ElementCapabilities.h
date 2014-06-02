/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ElementCapabilities_h
#define _CIM_ElementCapabilities_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_Capabilities.h"

/*
**==============================================================================
**
** CIM_ElementCapabilities [CIM_ElementCapabilities]
**
** Keys:
**    ManagedElement
**    Capabilities
**
**==============================================================================
*/

typedef struct _CIM_ElementCapabilities
{
    MI_Instance __instance;
    /* CIM_ElementCapabilities properties */
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
    /*KEY*/ CIM_Capabilities_ConstRef Capabilities;
    MI_ConstUint16AField Characteristics;
}
CIM_ElementCapabilities;

typedef struct _CIM_ElementCapabilities_Ref
{
    CIM_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_Ref;

typedef struct _CIM_ElementCapabilities_ConstRef
{
    MI_CONST CIM_ElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ConstRef;

typedef struct _CIM_ElementCapabilities_Array
{
    struct _CIM_ElementCapabilities** data;
    MI_Uint32 size;
}
CIM_ElementCapabilities_Array;

typedef struct _CIM_ElementCapabilities_ConstArray
{
    struct _CIM_ElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ElementCapabilities_ConstArray;

typedef struct _CIM_ElementCapabilities_ArrayRef
{
    CIM_ElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ArrayRef;

typedef struct _CIM_ElementCapabilities_ConstArrayRef
{
    CIM_ElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Construct(
    CIM_ElementCapabilities* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_ElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clone(
    const CIM_ElementCapabilities* self,
    CIM_ElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ElementCapabilities_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Destruct(CIM_ElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Delete(CIM_ElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Post(
    const CIM_ElementCapabilities* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_ManagedElement(
    CIM_ElementCapabilities* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_ManagedElement(
    CIM_ElementCapabilities* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_ManagedElement(
    CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_Capabilities(
    CIM_ElementCapabilities* self,
    const CIM_Capabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_Capabilities(
    CIM_ElementCapabilities* self,
    const CIM_Capabilities* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_Capabilities(
    CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Set_Characteristics(
    CIM_ElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_SetPtr_Characteristics(
    CIM_ElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementCapabilities_Clear_Characteristics(
    CIM_ElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}


#endif /* _CIM_ElementCapabilities_h */
