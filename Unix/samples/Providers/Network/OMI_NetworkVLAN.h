/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_NetworkVLAN_h
#define _OMI_NetworkVLAN_h

#include <MI.h>
#include "CIM_NetworkVLAN.h"

/*
**==============================================================================
**
** OMI_NetworkVLAN [OMI_NetworkVLAN]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _OMI_NetworkVLAN /* extends CIM_NetworkVLAN */
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
    /* OMI_NetworkVLAN properties */
    MI_ConstBooleanField IsEnabled;
}
OMI_NetworkVLAN;

typedef struct _OMI_NetworkVLAN_Ref
{
    OMI_NetworkVLAN* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_NetworkVLAN_Ref;

typedef struct _OMI_NetworkVLAN_ConstRef
{
    MI_CONST OMI_NetworkVLAN* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_NetworkVLAN_ConstRef;

typedef struct _OMI_NetworkVLAN_Array
{
    struct _OMI_NetworkVLAN** data;
    MI_Uint32 size;
}
OMI_NetworkVLAN_Array;

typedef struct _OMI_NetworkVLAN_ConstArray
{
    struct _OMI_NetworkVLAN MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_NetworkVLAN_ConstArray;

typedef struct _OMI_NetworkVLAN_ArrayRef
{
    OMI_NetworkVLAN_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_NetworkVLAN_ArrayRef;

typedef struct _OMI_NetworkVLAN_ConstArrayRef
{
    OMI_NetworkVLAN_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_NetworkVLAN_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_NetworkVLAN_rtti;

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Construct(
    OMI_NetworkVLAN* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_NetworkVLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clone(
    const OMI_NetworkVLAN* self,
    OMI_NetworkVLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_NetworkVLAN_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_NetworkVLAN_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Destruct(OMI_NetworkVLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Delete(OMI_NetworkVLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Post(
    const OMI_NetworkVLAN* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_InstanceID(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_SetPtr_InstanceID(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_InstanceID(
    OMI_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_Caption(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_SetPtr_Caption(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_Caption(
    OMI_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_Description(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_SetPtr_Description(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_Description(
    OMI_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_ElementName(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_SetPtr_ElementName(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_ElementName(
    OMI_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_ConnectivityStatus(
    OMI_NetworkVLAN* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConnectivityStatus)->value = x;
    ((MI_Uint16Field*)&self->ConnectivityStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_ConnectivityStatus(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->ConnectivityStatus, 0, sizeof(self->ConnectivityStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_VLANId(
    OMI_NetworkVLAN* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->VLANId)->value = x;
    ((MI_Uint16Field*)&self->VLANId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_VLANId(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->VLANId, 0, sizeof(self->VLANId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_SAIdentifier(
    OMI_NetworkVLAN* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SAIdentifier)->value = x;
    ((MI_Uint32Field*)&self->SAIdentifier)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_SAIdentifier(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->SAIdentifier, 0, sizeof(self->SAIdentifier));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_TransmissionSize(
    OMI_NetworkVLAN* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->TransmissionSize)->value = x;
    ((MI_Sint32Field*)&self->TransmissionSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_TransmissionSize(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->TransmissionSize, 0, sizeof(self->TransmissionSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_TypeOfMedia(
    OMI_NetworkVLAN* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TypeOfMedia)->value = x;
    ((MI_Uint16Field*)&self->TypeOfMedia)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_TypeOfMedia(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->TypeOfMedia, 0, sizeof(self->TypeOfMedia));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_OtherTypeDescription(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_SetPtr_OtherTypeDescription(
    OMI_NetworkVLAN* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_OtherTypeDescription(
    OMI_NetworkVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Set_IsEnabled(
    OMI_NetworkVLAN* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsEnabled)->value = x;
    ((MI_BooleanField*)&self->IsEnabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_NetworkVLAN_Clear_IsEnabled(
    OMI_NetworkVLAN* self)
{
    memset((void*)&self->IsEnabled, 0, sizeof(self->IsEnabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_NetworkVLAN provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_NetworkVLAN_Self OMI_NetworkVLAN_Self;

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_Load(
    OMI_NetworkVLAN_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_Unload(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_EnumerateInstances(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_GetInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_CreateInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* newInstance);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_ModifyInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_NetworkVLAN_DeleteInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* instanceName);


#endif /* _OMI_NetworkVLAN_h */
