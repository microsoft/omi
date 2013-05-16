/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _PS_Module_h
#define _PS_Module_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** PS_Module [PS_Module]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _PS_Module /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* PS_Module properties */
    MI_ConstStringField ModuleName;
    MI_ConstUint16Field moduleType;
    MI_ConstUint8AField moduleManifestFileData;
}
PS_Module;

typedef struct _PS_Module_Ref
{
    PS_Module* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_Module_Ref;

typedef struct _PS_Module_ConstRef
{
    MI_CONST PS_Module* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_Module_ConstRef;

typedef struct _PS_Module_Array
{
    struct _PS_Module** data;
    MI_Uint32 size;
}
PS_Module_Array;

typedef struct _PS_Module_ConstArray
{
    struct _PS_Module MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
PS_Module_ConstArray;

typedef struct _PS_Module_ArrayRef
{
    PS_Module_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_Module_ArrayRef;

typedef struct _PS_Module_ConstArrayRef
{
    PS_Module_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PS_Module_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl PS_Module_rtti;

MI_INLINE MI_Result MI_CALL PS_Module_Construct(
    PS_Module* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &PS_Module_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clone(
    const PS_Module* self,
    PS_Module** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL PS_Module_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &PS_Module_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL PS_Module_Destruct(PS_Module* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_Module_Delete(PS_Module* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_Module_Post(
    const PS_Module* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_InstanceID(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_InstanceID(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_InstanceID(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_Caption(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_Caption(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_Caption(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_Description(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_Description(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_Description(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_ElementName(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_ElementName(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_ElementName(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_ModuleName(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_ModuleName(
    PS_Module* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_ModuleName(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_moduleType(
    PS_Module* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->moduleType)->value = x;
    ((MI_Uint16Field*)&self->moduleType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_moduleType(
    PS_Module* self)
{
    memset((void*)&self->moduleType, 0, sizeof(self->moduleType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL PS_Module_Set_moduleManifestFileData(
    PS_Module* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL PS_Module_SetPtr_moduleManifestFileData(
    PS_Module* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PS_Module_Clear_moduleManifestFileData(
    PS_Module* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

/*
**==============================================================================
**
** PS_Module provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _PS_Module_Self PS_Module_Self;

MI_EXTERN_C void MI_CALL PS_Module_Load(
    PS_Module_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_Module_Unload(
    PS_Module_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PS_Module_EnumerateInstances(
    PS_Module_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PS_Module_GetInstance(
    PS_Module_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_Module_CreateInstance(
    PS_Module_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* newInstance);

MI_EXTERN_C void MI_CALL PS_Module_ModifyInstance(
    PS_Module_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PS_Module_DeleteInstance(
    PS_Module_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PS_Module* instanceName);


#endif /* _PS_Module_h */
