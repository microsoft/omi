/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _PS_ModuleFile_h
#define _PS_ModuleFile_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** PS_ModuleFile [PS_ModuleFile]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _PS_ModuleFile /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* PS_ModuleFile properties */
    MI_ConstStringField FileName;
    MI_ConstUint8AField FileData;
}
PS_ModuleFile;

typedef struct _PS_ModuleFile_Ref
{
    PS_ModuleFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleFile_Ref;

typedef struct _PS_ModuleFile_ConstRef
{
    MI_CONST PS_ModuleFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleFile_ConstRef;

typedef struct _PS_ModuleFile_Array
{
    struct _PS_ModuleFile** data;
    MI_Uint32 size;
}
PS_ModuleFile_Array;

typedef struct _PS_ModuleFile_ConstArray
{
    struct _PS_ModuleFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
PS_ModuleFile_ConstArray;

typedef struct _PS_ModuleFile_ArrayRef
{
    PS_ModuleFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleFile_ArrayRef;

typedef struct _PS_ModuleFile_ConstArrayRef
{
    PS_ModuleFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_ModuleFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl PS_ModuleFile_rtti;

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Construct(
    PS_ModuleFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &PS_ModuleFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clone(
    const PS_ModuleFile* self,
    PS_ModuleFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL PS_ModuleFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &PS_ModuleFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Destruct(PS_ModuleFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Delete(PS_ModuleFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Post(
    const PS_ModuleFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_InstanceID(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_InstanceID(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_InstanceID(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_Caption(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_Caption(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_Caption(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_Description(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_Description(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_Description(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_ElementName(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_ElementName(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_ElementName(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_FileName(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_FileName(
    PS_ModuleFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_FileName(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Set_FileData(
    PS_ModuleFile* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_SetPtr_FileData(
    PS_ModuleFile* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_ModuleFile_Clear_FileData(
    PS_ModuleFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** PS_ModuleFile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _PS_ModuleFile_Self PS_ModuleFile_Self;

MI_EXTERN_C void MI_CALL PS_ModuleFile_Load(
    PS_ModuleFile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_ModuleFile_Unload(
    PS_ModuleFile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_ModuleFile_EnumerateInstances(
    PS_ModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_ModuleFile_GetInstance(
    PS_ModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_ModuleFile_CreateInstance(
    PS_ModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* newInstance);

MI_EXTERN_C void MI_CALL PS_ModuleFile_ModifyInstance(
    PS_ModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_ModuleFile_DeleteInstance(
    PS_ModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_ModuleFile* instanceName);


#endif /* _PS_ModuleFile_h */
