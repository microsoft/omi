/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_RegisteredProfile_h
#define _CIM_RegisteredProfile_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_RegisteredProfile [CIM_RegisteredProfile]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_RegisteredProfile /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_RegisteredProfile properties */
    MI_ConstUint16Field RegisteredOrganization;
    MI_ConstStringField OtherRegisteredOrganization;
    MI_ConstStringField RegisteredName;
    MI_ConstStringField RegisteredVersion;
    MI_ConstUint16AField AdvertiseTypes;
    MI_ConstStringAField AdvertiseTypeDescriptions;
    MI_ConstStringAField ImplementedFeatures;
}
CIM_RegisteredProfile;

typedef struct _CIM_RegisteredProfile_Ref
{
    CIM_RegisteredProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RegisteredProfile_Ref;

typedef struct _CIM_RegisteredProfile_ConstRef
{
    MI_CONST CIM_RegisteredProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RegisteredProfile_ConstRef;

typedef struct _CIM_RegisteredProfile_Array
{
    struct _CIM_RegisteredProfile** data;
    MI_Uint32 size;
}
CIM_RegisteredProfile_Array;

typedef struct _CIM_RegisteredProfile_ConstArray
{
    struct _CIM_RegisteredProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_RegisteredProfile_ConstArray;

typedef struct _CIM_RegisteredProfile_ArrayRef
{
    CIM_RegisteredProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RegisteredProfile_ArrayRef;

typedef struct _CIM_RegisteredProfile_ConstArrayRef
{
    CIM_RegisteredProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RegisteredProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_RegisteredProfile_rtti;

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Construct(
    CIM_RegisteredProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_RegisteredProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clone(
    const CIM_RegisteredProfile* self,
    CIM_RegisteredProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_RegisteredProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_RegisteredProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Destruct(CIM_RegisteredProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Delete(CIM_RegisteredProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Post(
    const CIM_RegisteredProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_InstanceID(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_InstanceID(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_InstanceID(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_Caption(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_Caption(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_Caption(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_Description(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_Description(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_Description(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_ElementName(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_ElementName(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_ElementName(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_RegisteredOrganization(
    CIM_RegisteredProfile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RegisteredOrganization)->value = x;
    ((MI_Uint16Field*)&self->RegisteredOrganization)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_RegisteredOrganization(
    CIM_RegisteredProfile* self)
{
    memset((void*)&self->RegisteredOrganization, 0, sizeof(self->RegisteredOrganization));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_OtherRegisteredOrganization(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_OtherRegisteredOrganization(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_OtherRegisteredOrganization(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_RegisteredName(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_RegisteredName(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_RegisteredName(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_RegisteredVersion(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_RegisteredVersion(
    CIM_RegisteredProfile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_RegisteredVersion(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_AdvertiseTypes(
    CIM_RegisteredProfile* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_AdvertiseTypes(
    CIM_RegisteredProfile* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_AdvertiseTypes(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_AdvertiseTypeDescriptions(
    CIM_RegisteredProfile* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_AdvertiseTypeDescriptions(
    CIM_RegisteredProfile* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_AdvertiseTypeDescriptions(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Set_ImplementedFeatures(
    CIM_RegisteredProfile* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_SetPtr_ImplementedFeatures(
    CIM_RegisteredProfile* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_Clear_ImplementedFeatures(
    CIM_RegisteredProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

/*
**==============================================================================
**
** CIM_RegisteredProfile.CloseConformantInstances()
**
**==============================================================================
*/

typedef struct _CIM_RegisteredProfile_CloseConformantInstances
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField EnumerationContext;
}
CIM_RegisteredProfile_CloseConformantInstances;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_RegisteredProfile_CloseConformantInstances_rtti;

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Construct(
    CIM_RegisteredProfile_CloseConformantInstances* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_RegisteredProfile_CloseConformantInstances_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Clone(
    const CIM_RegisteredProfile_CloseConformantInstances* self,
    CIM_RegisteredProfile_CloseConformantInstances** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Destruct(
    CIM_RegisteredProfile_CloseConformantInstances* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Delete(
    CIM_RegisteredProfile_CloseConformantInstances* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Post(
    const CIM_RegisteredProfile_CloseConformantInstances* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Set_MIReturn(
    CIM_RegisteredProfile_CloseConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Clear_MIReturn(
    CIM_RegisteredProfile_CloseConformantInstances* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Set_EnumerationContext(
    CIM_RegisteredProfile_CloseConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_SetPtr_EnumerationContext(
    CIM_RegisteredProfile_CloseConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_CloseConformantInstances_Clear_EnumerationContext(
    CIM_RegisteredProfile_CloseConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_RegisteredProfile.OpenConformantInstances()
**
**==============================================================================
*/

typedef struct _CIM_RegisteredProfile_OpenConformantInstances
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField ResultClass;
    /*IN*/ MI_ConstStringAField IncludedPropertyList;
    /*IN*/ MI_ConstUint32Field OperationTimeout;
    /*IN*/ MI_ConstBooleanField ContinueOnError;
    /*IN*/ MI_ConstUint32Field MaxObjectCount;
    /*OUT*/ MI_ConstStringField EnumerationContext;
    /*OUT*/ MI_ConstBooleanField EndOfSequence;
    /*OUT*/ MI_ConstUint16AField InstanceType;
    /*OUT*/ CIM_ManagedElement_ConstArrayRef InstanceWithPathList;
}
CIM_RegisteredProfile_OpenConformantInstances;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_RegisteredProfile_OpenConformantInstances_rtti;

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Construct(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_RegisteredProfile_OpenConformantInstances_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clone(
    const CIM_RegisteredProfile_OpenConformantInstances* self,
    CIM_RegisteredProfile_OpenConformantInstances** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Destruct(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Delete(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Post(
    const CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_MIReturn(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_MIReturn(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_ResultClass(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_SetPtr_ResultClass(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_ResultClass(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_IncludedPropertyList(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_SetPtr_IncludedPropertyList(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_IncludedPropertyList(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_OperationTimeout(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->OperationTimeout)->value = x;
    ((MI_Uint32Field*)&self->OperationTimeout)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_OperationTimeout(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    memset((void*)&self->OperationTimeout, 0, sizeof(self->OperationTimeout));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_ContinueOnError(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ContinueOnError)->value = x;
    ((MI_BooleanField*)&self->ContinueOnError)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_ContinueOnError(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    memset((void*)&self->ContinueOnError, 0, sizeof(self->ContinueOnError));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_MaxObjectCount(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxObjectCount)->value = x;
    ((MI_Uint32Field*)&self->MaxObjectCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_MaxObjectCount(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    memset((void*)&self->MaxObjectCount, 0, sizeof(self->MaxObjectCount));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_EnumerationContext(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_SetPtr_EnumerationContext(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_EnumerationContext(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_EndOfSequence(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->EndOfSequence)->value = x;
    ((MI_BooleanField*)&self->EndOfSequence)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_EndOfSequence(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    memset((void*)&self->EndOfSequence, 0, sizeof(self->EndOfSequence));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_InstanceType(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_SetPtr_InstanceType(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_InstanceType(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Set_InstanceWithPathList(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const CIM_ManagedElement * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_SetPtr_InstanceWithPathList(
    CIM_RegisteredProfile_OpenConformantInstances* self,
    const CIM_ManagedElement * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_OpenConformantInstances_Clear_InstanceWithPathList(
    CIM_RegisteredProfile_OpenConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

/*
**==============================================================================
**
** CIM_RegisteredProfile.PullConformantInstances()
**
**==============================================================================
*/

typedef struct _CIM_RegisteredProfile_PullConformantInstances
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field MaxObjectCount;
    /*IN-OUT*/ MI_ConstStringField EnumerationContext;
    /*OUT*/ MI_ConstBooleanField EndOfSequence;
    /*OUT*/ MI_ConstUint16AField InstanceType;
    /*OUT*/ CIM_ManagedElement_ConstArrayRef InstanceWithPathList;
}
CIM_RegisteredProfile_PullConformantInstances;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_RegisteredProfile_PullConformantInstances_rtti;

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Construct(
    CIM_RegisteredProfile_PullConformantInstances* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_RegisteredProfile_PullConformantInstances_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clone(
    const CIM_RegisteredProfile_PullConformantInstances* self,
    CIM_RegisteredProfile_PullConformantInstances** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Destruct(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Delete(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Post(
    const CIM_RegisteredProfile_PullConformantInstances* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_MIReturn(
    CIM_RegisteredProfile_PullConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_MIReturn(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_MaxObjectCount(
    CIM_RegisteredProfile_PullConformantInstances* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxObjectCount)->value = x;
    ((MI_Uint32Field*)&self->MaxObjectCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_MaxObjectCount(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    memset((void*)&self->MaxObjectCount, 0, sizeof(self->MaxObjectCount));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_EnumerationContext(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_SetPtr_EnumerationContext(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_EnumerationContext(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_EndOfSequence(
    CIM_RegisteredProfile_PullConformantInstances* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->EndOfSequence)->value = x;
    ((MI_BooleanField*)&self->EndOfSequence)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_EndOfSequence(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    memset((void*)&self->EndOfSequence, 0, sizeof(self->EndOfSequence));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_InstanceType(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_SetPtr_InstanceType(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_InstanceType(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Set_InstanceWithPathList(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const CIM_ManagedElement * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_SetPtr_InstanceWithPathList(
    CIM_RegisteredProfile_PullConformantInstances* self,
    const CIM_ManagedElement * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RegisteredProfile_PullConformantInstances_Clear_InstanceWithPathList(
    CIM_RegisteredProfile_PullConformantInstances* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}


#endif /* _CIM_RegisteredProfile_h */
