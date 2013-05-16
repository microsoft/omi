/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_EnabledLogicalElementCapabilities_h
#define _CIM_EnabledLogicalElementCapabilities_h

#include <MI.h>
#include "CIM_Capabilities.h"

/*
**==============================================================================
**
** CIM_EnabledLogicalElementCapabilities [CIM_EnabledLogicalElementCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElementCapabilities /* extends CIM_Capabilities */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Capabilities properties */
    /* CIM_EnabledLogicalElementCapabilities properties */
    MI_ConstBooleanField ElementNameEditSupported;
    MI_ConstUint16Field MaxElementNameLen;
    MI_ConstUint16AField RequestedStatesSupported;
    MI_ConstStringField ElementNameMask;
}
CIM_EnabledLogicalElementCapabilities;

typedef struct _CIM_EnabledLogicalElementCapabilities_Ref
{
    CIM_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_Ref;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstRef
{
    MI_CONST CIM_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ConstRef;

typedef struct _CIM_EnabledLogicalElementCapabilities_Array
{
    struct _CIM_EnabledLogicalElementCapabilities** data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElementCapabilities_Array;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstArray
{
    struct _CIM_EnabledLogicalElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElementCapabilities_ConstArray;

typedef struct _CIM_EnabledLogicalElementCapabilities_ArrayRef
{
    CIM_EnabledLogicalElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ArrayRef;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstArrayRef
{
    CIM_EnabledLogicalElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_EnabledLogicalElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Construct(
    CIM_EnabledLogicalElementCapabilities* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_EnabledLogicalElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clone(
    const CIM_EnabledLogicalElementCapabilities* self,
    CIM_EnabledLogicalElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_EnabledLogicalElementCapabilities_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_EnabledLogicalElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Destruct(CIM_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Delete(CIM_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Post(
    const CIM_EnabledLogicalElementCapabilities* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_InstanceID(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_InstanceID(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_InstanceID(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_Caption(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_Caption(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_Caption(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_Description(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_Description(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_Description(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementName(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_ElementName(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementName(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementNameEditSupported(
    CIM_EnabledLogicalElementCapabilities* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementNameEditSupported(
    CIM_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_MaxElementNameLen(
    CIM_EnabledLogicalElementCapabilities* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_MaxElementNameLen(
    CIM_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_RequestedStatesSupported(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_RequestedStatesSupported(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_RequestedStatesSupported(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementNameMask(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_ElementNameMask(
    CIM_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementNameMask(
    CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}


#endif /* _CIM_EnabledLogicalElementCapabilities_h */
