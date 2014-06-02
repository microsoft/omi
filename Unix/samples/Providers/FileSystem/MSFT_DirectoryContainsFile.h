/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_DirectoryContainsFile_h
#define _MSFT_DirectoryContainsFile_h

#include <MI.h>
#include "MSFT_Directory.h"
#include "MSFT_LogicalFile.h"

/*
**==============================================================================
**
** MSFT_DirectoryContainsFile [MSFT_DirectoryContainsFile]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _MSFT_DirectoryContainsFile
{
    MI_Instance __instance;
    /* MSFT_DirectoryContainsFile properties */
    /*KEY*/ MSFT_Directory_ConstRef GroupComponent;
    /*KEY*/ MSFT_LogicalFile_ConstRef PartComponent;
}
MSFT_DirectoryContainsFile;

typedef struct _MSFT_DirectoryContainsFile_Ref
{
    MSFT_DirectoryContainsFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DirectoryContainsFile_Ref;

typedef struct _MSFT_DirectoryContainsFile_ConstRef
{
    MI_CONST MSFT_DirectoryContainsFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DirectoryContainsFile_ConstRef;

typedef struct _MSFT_DirectoryContainsFile_Array
{
    struct _MSFT_DirectoryContainsFile** data;
    MI_Uint32 size;
}
MSFT_DirectoryContainsFile_Array;

typedef struct _MSFT_DirectoryContainsFile_ConstArray
{
    struct _MSFT_DirectoryContainsFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DirectoryContainsFile_ConstArray;

typedef struct _MSFT_DirectoryContainsFile_ArrayRef
{
    MSFT_DirectoryContainsFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DirectoryContainsFile_ArrayRef;

typedef struct _MSFT_DirectoryContainsFile_ConstArrayRef
{
    MSFT_DirectoryContainsFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DirectoryContainsFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DirectoryContainsFile_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Construct(
    MSFT_DirectoryContainsFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_DirectoryContainsFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Clone(
    const MSFT_DirectoryContainsFile* self,
    MSFT_DirectoryContainsFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DirectoryContainsFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DirectoryContainsFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Destruct(MSFT_DirectoryContainsFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Delete(MSFT_DirectoryContainsFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Post(
    const MSFT_DirectoryContainsFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Set_GroupComponent(
    MSFT_DirectoryContainsFile* self,
    const MSFT_Directory* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_SetPtr_GroupComponent(
    MSFT_DirectoryContainsFile* self,
    const MSFT_Directory* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Clear_GroupComponent(
    MSFT_DirectoryContainsFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Set_PartComponent(
    MSFT_DirectoryContainsFile* self,
    const MSFT_LogicalFile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_SetPtr_PartComponent(
    MSFT_DirectoryContainsFile* self,
    const MSFT_LogicalFile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DirectoryContainsFile_Clear_PartComponent(
    MSFT_DirectoryContainsFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_DirectoryContainsFile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_DirectoryContainsFile_Self MSFT_DirectoryContainsFile_Self;

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_Load(
    MSFT_DirectoryContainsFile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_Unload(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_EnumerateInstances(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_GetInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_CreateInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* newInstance);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_ModifyInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_DeleteInstance(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DirectoryContainsFile* instanceName);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_AssociatorInstancesGroupComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_AssociatorInstancesPartComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_LogicalFile* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_ReferenceInstancesGroupComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_DirectoryContainsFile_ReferenceInstancesPartComponent(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_LogicalFile* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _MSFT_DirectoryContainsFile_h */
