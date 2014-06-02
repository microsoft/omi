/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkVLAN_h
#define _CIM_NetworkVLAN_h

#include <MI.h>
#include "CIM_ConnectivityCollection.h"

/*
**==============================================================================
**
** CIM_NetworkVLAN [CIM_NetworkVLAN]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkVLAN /* extends CIM_ConnectivityCollection */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_SystemSpecificCollection properties */
    /* CIM_ConnectivityCollection properties */
    MI_ConstUint16Field ConnectivityStatus;
    /* CIM_NetworkVLAN properties */
    MI_ConstUint16Field VLANId;
    MI_ConstUint32Field SAIdentifier;
    MI_ConstSint32Field TransmissionSize;
    MI_ConstUint16Field TypeOfMedia;
    MI_ConstStringField OtherTypeDescription;
}
CIM_NetworkVLAN;

typedef struct _CIM_NetworkVLAN_Ref
{
    CIM_NetworkVLAN* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkVLAN_Ref;

typedef struct _CIM_NetworkVLAN_ConstRef
{
    MI_CONST CIM_NetworkVLAN* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkVLAN_ConstRef;

typedef struct _CIM_NetworkVLAN_Array
{
    struct _CIM_NetworkVLAN** data;
    MI_Uint32 size;
}
CIM_NetworkVLAN_Array;

typedef struct _CIM_NetworkVLAN_ConstArray
{
    struct _CIM_NetworkVLAN MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkVLAN_ConstArray;

typedef struct _CIM_NetworkVLAN_ArrayRef
{
    CIM_NetworkVLAN_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkVLAN_ArrayRef;

typedef struct _CIM_NetworkVLAN_ConstArrayRef
{
    CIM_NetworkVLAN_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkVLAN_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkVLAN_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Construct(
    _Out_ CIM_NetworkVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkVLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clone(
    _In_ const CIM_NetworkVLAN* self,
    _Outptr_ CIM_NetworkVLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkVLAN_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkVLAN_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Destruct(_Inout_ CIM_NetworkVLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Delete(_Inout_ CIM_NetworkVLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Post(
    _In_ const CIM_NetworkVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_InstanceID(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_SetPtr_InstanceID(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_InstanceID(
    _Inout_ CIM_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_Caption(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_SetPtr_Caption(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_Caption(
    _Inout_ CIM_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_Description(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_SetPtr_Description(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_Description(
    _Inout_ CIM_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_ElementName(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_SetPtr_ElementName(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_ElementName(
    _Inout_ CIM_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_ConnectivityStatus(
    _Inout_ CIM_NetworkVLAN* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConnectivityStatus)->value = x;
    ((MI_Uint16Field*)&self->ConnectivityStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_ConnectivityStatus(
    _Inout_ CIM_NetworkVLAN* self)
{
    memset((void*)&self->ConnectivityStatus, 0, sizeof(self->ConnectivityStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_VLANId(
    _Inout_ CIM_NetworkVLAN* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->VLANId)->value = x;
    ((MI_Uint16Field*)&self->VLANId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_VLANId(
    _Inout_ CIM_NetworkVLAN* self)
{
    memset((void*)&self->VLANId, 0, sizeof(self->VLANId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_SAIdentifier(
    _Inout_ CIM_NetworkVLAN* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SAIdentifier)->value = x;
    ((MI_Uint32Field*)&self->SAIdentifier)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_SAIdentifier(
    _Inout_ CIM_NetworkVLAN* self)
{
    memset((void*)&self->SAIdentifier, 0, sizeof(self->SAIdentifier));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_TransmissionSize(
    _Inout_ CIM_NetworkVLAN* self,
    _In_ MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->TransmissionSize)->value = x;
    ((MI_Sint32Field*)&self->TransmissionSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_TransmissionSize(
    _Inout_ CIM_NetworkVLAN* self)
{
    memset((void*)&self->TransmissionSize, 0, sizeof(self->TransmissionSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_TypeOfMedia(
    _Inout_ CIM_NetworkVLAN* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TypeOfMedia)->value = x;
    ((MI_Uint16Field*)&self->TypeOfMedia)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_TypeOfMedia(
    _Inout_ CIM_NetworkVLAN* self)
{
    memset((void*)&self->TypeOfMedia, 0, sizeof(self->TypeOfMedia));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Set_OtherTypeDescription(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_SetPtr_OtherTypeDescription(
    _Inout_ CIM_NetworkVLAN* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkVLAN_Clear_OtherTypeDescription(
    _Inout_ CIM_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

/*
**==============================================================================
**
** CIM_NetworkVLAN provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkVLAN_Self CIM_NetworkVLAN_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_Load(
    _Outptr_result_maybenull_ CIM_NetworkVLAN_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_Unload(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_EnumerateInstances(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_GetInstance(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkVLAN* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_CreateInstance(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkVLAN* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_ModifyInstance(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkVLAN* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkVLAN_DeleteInstance(
    _In_opt_ CIM_NetworkVLAN_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkVLAN* instanceName);


#endif /* _CIM_NetworkVLAN_h */
