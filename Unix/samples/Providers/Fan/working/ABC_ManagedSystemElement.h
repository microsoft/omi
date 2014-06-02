/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_ManagedSystemElement_h
#define _ABC_ManagedSystemElement_h

#include <MI.h>
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** ABC_ManagedSystemElement [ABC_ManagedSystemElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _ABC_ManagedSystemElement /* extends CIM_ManagedSystemElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    MI_ConstStringField Name;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstStringAField StatusDescriptions;
    MI_ConstStringField Status;
    MI_ConstUint16Field HealthState;
    MI_ConstUint16Field CommunicationStatus;
    MI_ConstUint16Field DetailedStatus;
    MI_ConstUint16Field OperatingStatus;
    MI_ConstUint16Field PrimaryStatus;
    /* ABC_ManagedSystemElement properties */
}
ABC_ManagedSystemElement;

typedef struct _ABC_ManagedSystemElement_Ref
{
    ABC_ManagedSystemElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ManagedSystemElement_Ref;

typedef struct _ABC_ManagedSystemElement_ConstRef
{
    MI_CONST ABC_ManagedSystemElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ManagedSystemElement_ConstRef;

typedef struct _ABC_ManagedSystemElement_Array
{
    struct _ABC_ManagedSystemElement** data;
    MI_Uint32 size;
}
ABC_ManagedSystemElement_Array;

typedef struct _ABC_ManagedSystemElement_ConstArray
{
    struct _ABC_ManagedSystemElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_ManagedSystemElement_ConstArray;

typedef struct _ABC_ManagedSystemElement_ArrayRef
{
    ABC_ManagedSystemElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ManagedSystemElement_ArrayRef;

typedef struct _ABC_ManagedSystemElement_ConstArrayRef
{
    ABC_ManagedSystemElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ManagedSystemElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_ManagedSystemElement_rtti;

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Construct(
    ABC_ManagedSystemElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_ManagedSystemElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clone(
    const ABC_ManagedSystemElement* self,
    ABC_ManagedSystemElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_ManagedSystemElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_ManagedSystemElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Destruct(ABC_ManagedSystemElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Delete(ABC_ManagedSystemElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Post(
    const ABC_ManagedSystemElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_InstanceID(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_InstanceID(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_InstanceID(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_Caption(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_Caption(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_Caption(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_Description(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_Description(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_Description(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_ElementName(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_ElementName(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_ElementName(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_InstallDate(
    ABC_ManagedSystemElement* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_InstallDate(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_Name(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_Name(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_Name(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_OperationalStatus(
    ABC_ManagedSystemElement* self,
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

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_OperationalStatus(
    ABC_ManagedSystemElement* self,
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

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_OperationalStatus(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_StatusDescriptions(
    ABC_ManagedSystemElement* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_StatusDescriptions(
    ABC_ManagedSystemElement* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_StatusDescriptions(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_Status(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_SetPtr_Status(
    ABC_ManagedSystemElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_Status(
    ABC_ManagedSystemElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_HealthState(
    ABC_ManagedSystemElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_HealthState(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_CommunicationStatus(
    ABC_ManagedSystemElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_CommunicationStatus(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_DetailedStatus(
    ABC_ManagedSystemElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_DetailedStatus(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_OperatingStatus(
    ABC_ManagedSystemElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_OperatingStatus(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Set_PrimaryStatus(
    ABC_ManagedSystemElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ManagedSystemElement_Clear_PrimaryStatus(
    ABC_ManagedSystemElement* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_ManagedSystemElement provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_ManagedSystemElement_Self ABC_ManagedSystemElement_Self;

MI_EXTERN_C void MI_CALL ABC_ManagedSystemElement_Load(
    ABC_ManagedSystemElement_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ManagedSystemElement_Unload(
    ABC_ManagedSystemElement_Self* self,
    MI_Context* context);


#endif /* _ABC_ManagedSystemElement_h */
