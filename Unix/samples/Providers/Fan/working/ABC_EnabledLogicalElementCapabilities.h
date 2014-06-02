/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_EnabledLogicalElementCapabilities_h
#define _ABC_EnabledLogicalElementCapabilities_h

#include <MI.h>
#include "CIM_EnabledLogicalElementCapabilities.h"

/*
**==============================================================================
**
** ABC_EnabledLogicalElementCapabilities [ABC_EnabledLogicalElementCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _ABC_EnabledLogicalElementCapabilities /* extends CIM_EnabledLogicalElementCapabilities */
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
    /* ABC_EnabledLogicalElementCapabilities properties */
}
ABC_EnabledLogicalElementCapabilities;

typedef struct _ABC_EnabledLogicalElementCapabilities_Ref
{
    ABC_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EnabledLogicalElementCapabilities_Ref;

typedef struct _ABC_EnabledLogicalElementCapabilities_ConstRef
{
    MI_CONST ABC_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EnabledLogicalElementCapabilities_ConstRef;

typedef struct _ABC_EnabledLogicalElementCapabilities_Array
{
    struct _ABC_EnabledLogicalElementCapabilities** data;
    MI_Uint32 size;
}
ABC_EnabledLogicalElementCapabilities_Array;

typedef struct _ABC_EnabledLogicalElementCapabilities_ConstArray
{
    struct _ABC_EnabledLogicalElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_EnabledLogicalElementCapabilities_ConstArray;

typedef struct _ABC_EnabledLogicalElementCapabilities_ArrayRef
{
    ABC_EnabledLogicalElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EnabledLogicalElementCapabilities_ArrayRef;

typedef struct _ABC_EnabledLogicalElementCapabilities_ConstArrayRef
{
    ABC_EnabledLogicalElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EnabledLogicalElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_EnabledLogicalElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Construct(
    ABC_EnabledLogicalElementCapabilities* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_EnabledLogicalElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clone(
    const ABC_EnabledLogicalElementCapabilities* self,
    ABC_EnabledLogicalElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_EnabledLogicalElementCapabilities_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_EnabledLogicalElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Destruct(ABC_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Delete(ABC_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Post(
    const ABC_EnabledLogicalElementCapabilities* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_InstanceID(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_InstanceID(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_InstanceID(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_Caption(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_Caption(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_Caption(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_Description(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_Description(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_Description(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_ElementName(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_ElementName(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_ElementName(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_ElementNameEditSupported(
    ABC_EnabledLogicalElementCapabilities* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_ElementNameEditSupported(
    ABC_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_MaxElementNameLen(
    ABC_EnabledLogicalElementCapabilities* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_MaxElementNameLen(
    ABC_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_RequestedStatesSupported(
    ABC_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_RequestedStatesSupported(
    ABC_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_RequestedStatesSupported(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Set_ElementNameMask(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_SetPtr_ElementNameMask(
    ABC_EnabledLogicalElementCapabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EnabledLogicalElementCapabilities_Clear_ElementNameMask(
    ABC_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** ABC_EnabledLogicalElementCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_EnabledLogicalElementCapabilities_Self ABC_EnabledLogicalElementCapabilities_Self;

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_Load(
    ABC_EnabledLogicalElementCapabilities_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_Unload(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_EnumerateInstances(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_GetInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_CreateInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* newInstance);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_ModifyInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_EnabledLogicalElementCapabilities_DeleteInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName);


#endif /* _ABC_EnabledLogicalElementCapabilities_h */
