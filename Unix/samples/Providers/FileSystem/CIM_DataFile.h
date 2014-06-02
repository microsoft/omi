/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_DataFile_h
#define _CIM_DataFile_h

#include <MI.h>
#include "CIM_LogicalFile.h"

/*
**==============================================================================
**
** CIM_DataFile [CIM_DataFile]
**
** Keys:
**    Name
**    CSCreationClassName
**    CSName
**    FSCreationClassName
**    FSName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _CIM_DataFile /* extends CIM_LogicalFile */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstStringAField StatusDescriptions;
    MI_ConstStringField Status;
    MI_ConstUint16Field HealthState;
    MI_ConstUint16Field CommunicationStatus;
    MI_ConstUint16Field DetailedStatus;
    MI_ConstUint16Field OperatingStatus;
    MI_ConstUint16Field PrimaryStatus;
    /* CIM_LogicalElement properties */
    /* CIM_LogicalFile properties */
    /*KEY*/ MI_ConstStringField CSCreationClassName;
    /*KEY*/ MI_ConstStringField CSName;
    /*KEY*/ MI_ConstStringField FSCreationClassName;
    /*KEY*/ MI_ConstStringField FSName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    MI_ConstUint64Field FileSize;
    MI_ConstDatetimeField CreationDate;
    MI_ConstDatetimeField LastModified;
    MI_ConstDatetimeField LastAccessed;
    MI_ConstBooleanField Readable;
    MI_ConstBooleanField Writeable;
    MI_ConstBooleanField Executable;
    MI_ConstStringField CompressionMethod;
    MI_ConstStringField EncryptionMethod;
    MI_ConstUint64Field InUseCount;
    /* CIM_DataFile properties */
}
CIM_DataFile;

typedef struct _CIM_DataFile_Ref
{
    CIM_DataFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DataFile_Ref;

typedef struct _CIM_DataFile_ConstRef
{
    MI_CONST CIM_DataFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DataFile_ConstRef;

typedef struct _CIM_DataFile_Array
{
    struct _CIM_DataFile** data;
    MI_Uint32 size;
}
CIM_DataFile_Array;

typedef struct _CIM_DataFile_ConstArray
{
    struct _CIM_DataFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_DataFile_ConstArray;

typedef struct _CIM_DataFile_ArrayRef
{
    CIM_DataFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DataFile_ArrayRef;

typedef struct _CIM_DataFile_ConstArrayRef
{
    CIM_DataFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DataFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_DataFile_rtti;

MI_INLINE MI_Result MI_CALL CIM_DataFile_Construct(
    CIM_DataFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_DataFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clone(
    const CIM_DataFile* self,
    CIM_DataFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_DataFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_DataFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Destruct(CIM_DataFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Delete(CIM_DataFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Post(
    const CIM_DataFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_InstanceID(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_InstanceID(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_InstanceID(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Caption(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_Caption(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Caption(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Description(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_Description(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Description(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_ElementName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_ElementName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_ElementName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_InstallDate(
    CIM_DataFile* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_InstallDate(
    CIM_DataFile* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Name(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_Name(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Name(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_OperationalStatus(
    CIM_DataFile* self,
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

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_OperationalStatus(
    CIM_DataFile* self,
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

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_OperationalStatus(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_StatusDescriptions(
    CIM_DataFile* self,
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

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_StatusDescriptions(
    CIM_DataFile* self,
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

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_StatusDescriptions(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Status(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_Status(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Status(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_HealthState(
    CIM_DataFile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_HealthState(
    CIM_DataFile* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CommunicationStatus(
    CIM_DataFile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CommunicationStatus(
    CIM_DataFile* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_DetailedStatus(
    CIM_DataFile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_DetailedStatus(
    CIM_DataFile* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_OperatingStatus(
    CIM_DataFile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_OperatingStatus(
    CIM_DataFile* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_PrimaryStatus(
    CIM_DataFile* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_PrimaryStatus(
    CIM_DataFile* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CSCreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_CSCreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CSCreationClassName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CSName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_CSName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CSName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_FSCreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_FSCreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_FSCreationClassName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_FSName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_FSName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_FSName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_CreationClassName(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CreationClassName(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_FileSize(
    CIM_DataFile* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->FileSize)->value = x;
    ((MI_Uint64Field*)&self->FileSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_FileSize(
    CIM_DataFile* self)
{
    memset((void*)&self->FileSize, 0, sizeof(self->FileSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CreationDate(
    CIM_DataFile* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreationDate)->value = x;
    ((MI_DatetimeField*)&self->CreationDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CreationDate(
    CIM_DataFile* self)
{
    memset((void*)&self->CreationDate, 0, sizeof(self->CreationDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_LastModified(
    CIM_DataFile* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->LastModified)->value = x;
    ((MI_DatetimeField*)&self->LastModified)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_LastModified(
    CIM_DataFile* self)
{
    memset((void*)&self->LastModified, 0, sizeof(self->LastModified));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_LastAccessed(
    CIM_DataFile* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->LastAccessed)->value = x;
    ((MI_DatetimeField*)&self->LastAccessed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_LastAccessed(
    CIM_DataFile* self)
{
    memset((void*)&self->LastAccessed, 0, sizeof(self->LastAccessed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Readable(
    CIM_DataFile* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Readable)->value = x;
    ((MI_BooleanField*)&self->Readable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Readable(
    CIM_DataFile* self)
{
    memset((void*)&self->Readable, 0, sizeof(self->Readable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Writeable(
    CIM_DataFile* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Writeable)->value = x;
    ((MI_BooleanField*)&self->Writeable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Writeable(
    CIM_DataFile* self)
{
    memset((void*)&self->Writeable, 0, sizeof(self->Writeable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_Executable(
    CIM_DataFile* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Executable)->value = x;
    ((MI_BooleanField*)&self->Executable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_Executable(
    CIM_DataFile* self)
{
    memset((void*)&self->Executable, 0, sizeof(self->Executable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_CompressionMethod(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_CompressionMethod(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_CompressionMethod(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_EncryptionMethod(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_SetPtr_EncryptionMethod(
    CIM_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_EncryptionMethod(
    CIM_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Set_InUseCount(
    CIM_DataFile* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->InUseCount)->value = x;
    ((MI_Uint64Field*)&self->InUseCount)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_DataFile_Clear_InUseCount(
    CIM_DataFile* self)
{
    memset((void*)&self->InUseCount, 0, sizeof(self->InUseCount));
    return MI_RESULT_OK;
}


#endif /* _CIM_DataFile_h */
