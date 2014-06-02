/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Identify_h
#define _Identify_h

#include <MI.h>

/*
**==============================================================================
**
** Identify [OMI_Identify]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _Identify
{
    MI_Instance __instance;
    /* Identify properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField SystemName;
    MI_ConstStringField ProductName;
    MI_ConstStringField ProductVendor;
    MI_ConstUint32Field ProductVersionMajor;
    MI_ConstUint32Field ProductVersionMinor;
    MI_ConstUint32Field ProductVersionRevision;
    MI_ConstStringField ProductVersionString;
    MI_ConstStringField Platform;
    MI_ConstStringField OperatingSystem;
    MI_ConstStringField Architecture;
    MI_ConstStringField Compiler;
    MI_ConstStringField ConfigPrefix;
    MI_ConstStringField ConfigLibDir;
    MI_ConstStringField ConfigBinDir;
    MI_ConstStringField ConfigIncludeDir;
    MI_ConstStringField ConfigDataDir;
    MI_ConstStringField ConfigLocalStateDir;
    MI_ConstStringField ConfigSysConfDir;
    MI_ConstStringField ConfigProviderDir;
    MI_ConstStringField ConfigLogFile;
    MI_ConstStringField ConfigPIDFile;
    MI_ConstStringField ConfigRegisterDir;
    MI_ConstStringField ConfigSchemaDir;
    MI_ConstStringAField ConfigNameSpaces;
}
Identify;

typedef struct _Identify_Ref
{
    Identify* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identify_Ref;

typedef struct _Identify_ConstRef
{
    MI_CONST Identify* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identify_ConstRef;

typedef struct _Identify_Array
{
    struct _Identify** data;
    MI_Uint32 size;
}
Identify_Array;

typedef struct _Identify_ConstArray
{
    struct _Identify MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Identify_ConstArray;

typedef struct _Identify_ArrayRef
{
    Identify_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identify_ArrayRef;

typedef struct _Identify_ConstArrayRef
{
    Identify_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identify_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Identify_rtti;

MI_INLINE MI_Result MI_CALL Identify_Construct(
    Identify* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Identify_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identify_Clone(
    const Identify* self,
    Identify** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Identify_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Identify_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Identify_Destruct(Identify* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identify_Delete(Identify* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identify_Post(
    const Identify* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Identify_Set_InstanceID(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_InstanceID(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_InstanceID(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_Set_SystemName(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_SystemName(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_SystemName(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductName(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ProductName(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductName(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductVendor(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ProductVendor(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductVendor(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductVersionMajor(
    Identify* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ProductVersionMajor)->value = x;
    ((MI_Uint32Field*)&self->ProductVersionMajor)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductVersionMajor(
    Identify* self)
{
    memset((void*)&self->ProductVersionMajor, 0, sizeof(self->ProductVersionMajor));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductVersionMinor(
    Identify* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ProductVersionMinor)->value = x;
    ((MI_Uint32Field*)&self->ProductVersionMinor)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductVersionMinor(
    Identify* self)
{
    memset((void*)&self->ProductVersionMinor, 0, sizeof(self->ProductVersionMinor));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductVersionRevision(
    Identify* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ProductVersionRevision)->value = x;
    ((MI_Uint32Field*)&self->ProductVersionRevision)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductVersionRevision(
    Identify* self)
{
    memset((void*)&self->ProductVersionRevision, 0, sizeof(self->ProductVersionRevision));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identify_Set_ProductVersionString(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ProductVersionString(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ProductVersionString(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL Identify_Set_Platform(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_Platform(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_Platform(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL Identify_Set_OperatingSystem(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_OperatingSystem(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_OperatingSystem(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL Identify_Set_Architecture(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_Architecture(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_Architecture(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL Identify_Set_Compiler(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_Compiler(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_Compiler(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigPrefix(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigPrefix(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigPrefix(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigLibDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigLibDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigLibDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigBinDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigBinDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigBinDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigIncludeDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigIncludeDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigIncludeDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigDataDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigDataDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigDataDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigLocalStateDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigLocalStateDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigLocalStateDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigSysConfDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigSysConfDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigSysConfDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigProviderDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigProviderDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigProviderDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigLogFile(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigLogFile(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigLogFile(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigPIDFile(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigPIDFile(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigPIDFile(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigRegisterDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigRegisterDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigRegisterDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigSchemaDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigSchemaDir(
    Identify* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigSchemaDir(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL Identify_Set_ConfigNameSpaces(
    Identify* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Identify_SetPtr_ConfigNameSpaces(
    Identify* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identify_Clear_ConfigNameSpaces(
    Identify* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

/*
**==============================================================================
**
** Identify provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Identify_Self Identify_Self;

MI_EXTERN_C void MI_CALL Identify_Load(
    Identify_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Identify_Unload(
    Identify_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Identify_EnumerateInstances(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Identify_GetInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Identify_CreateInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* newInstance);

MI_EXTERN_C void MI_CALL Identify_ModifyInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Identify_DeleteInstance(
    Identify_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identify* instanceName);


#endif /* _Identify_h */
