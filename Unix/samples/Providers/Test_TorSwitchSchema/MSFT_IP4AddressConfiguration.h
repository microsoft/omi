/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_IP4AddressConfiguration_h
#define _MSFT_IP4AddressConfiguration_h

#include <MI.h>
#include "CIM_LogicalElement.h"

/*
**==============================================================================
**
** MSFT_IP4AddressConfiguration [MSFT_IP4AddressConfiguration]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MSFT_IP4AddressConfiguration /* extends CIM_LogicalElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
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
    /* CIM_LogicalElement properties */
    /* MSFT_IP4AddressConfiguration properties */
    MI_ConstStringField IPv4Address;
    MI_ConstUint16Field IPv4Prefix;
}
MSFT_IP4AddressConfiguration;

typedef struct _MSFT_IP4AddressConfiguration_Ref
{
    MSFT_IP4AddressConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_IP4AddressConfiguration_Ref;

typedef struct _MSFT_IP4AddressConfiguration_ConstRef
{
    MI_CONST MSFT_IP4AddressConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_IP4AddressConfiguration_ConstRef;

typedef struct _MSFT_IP4AddressConfiguration_Array
{
    struct _MSFT_IP4AddressConfiguration** data;
    MI_Uint32 size;
}
MSFT_IP4AddressConfiguration_Array;

typedef struct _MSFT_IP4AddressConfiguration_ConstArray
{
    struct _MSFT_IP4AddressConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_IP4AddressConfiguration_ConstArray;

typedef struct _MSFT_IP4AddressConfiguration_ArrayRef
{
    MSFT_IP4AddressConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_IP4AddressConfiguration_ArrayRef;

typedef struct _MSFT_IP4AddressConfiguration_ConstArrayRef
{
    MSFT_IP4AddressConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_IP4AddressConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_IP4AddressConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Construct(
    _Out_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_IP4AddressConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clone(
    _In_ const MSFT_IP4AddressConfiguration* self,
    _Outptr_ MSFT_IP4AddressConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_IP4AddressConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_IP4AddressConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Destruct(_Inout_ MSFT_IP4AddressConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Delete(_Inout_ MSFT_IP4AddressConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Post(
    _In_ const MSFT_IP4AddressConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_InstanceID(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_InstanceID(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_InstanceID(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_Caption(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_Caption(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_Caption(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_Description(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_Description(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_Description(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_ElementName(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_ElementName(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_ElementName(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_InstallDate(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_InstallDate(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_Name(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_Name(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_Name(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_OperationalStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_OperationalStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_OperationalStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_StatusDescriptions(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_StatusDescriptions(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_StatusDescriptions(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_Status(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_Status(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_Status(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_HealthState(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_HealthState(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_CommunicationStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_CommunicationStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_DetailedStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_DetailedStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_OperatingStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_OperatingStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_PrimaryStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_PrimaryStatus(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_IPv4Address(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_SetPtr_IPv4Address(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_IPv4Address(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Set_IPv4Prefix(
    _Inout_ MSFT_IP4AddressConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IPv4Prefix)->value = x;
    ((MI_Uint16Field*)&self->IPv4Prefix)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_IP4AddressConfiguration_Clear_IPv4Prefix(
    _Inout_ MSFT_IP4AddressConfiguration* self)
{
    memset((void*)&self->IPv4Prefix, 0, sizeof(self->IPv4Prefix));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_IP4AddressConfiguration provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_IP4AddressConfiguration_Self MSFT_IP4AddressConfiguration_Self;

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_Load(
    _Outptr_result_maybenull_ MSFT_IP4AddressConfiguration_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_Unload(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_EnumerateInstances(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_GetInstance(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_IP4AddressConfiguration* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_CreateInstance(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_IP4AddressConfiguration* newInstance);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_ModifyInstance(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_IP4AddressConfiguration* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_IP4AddressConfiguration_DeleteInstance(
    _In_opt_ MSFT_IP4AddressConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_IP4AddressConfiguration* instanceName);


#endif /* _MSFT_IP4AddressConfiguration_h */
