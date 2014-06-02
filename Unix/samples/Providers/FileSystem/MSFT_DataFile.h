/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_DataFile_h
#define _MSFT_DataFile_h

#include <MI.h>
#include "MSFT_LogicalFile.h"

/*
**==============================================================================
**
** MSFT_DataFile [MSFT_DataFile]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_DataFile /* extends MSFT_LogicalFile */
{
    MI_Instance __instance;
    /* MSFT_LogicalFile properties */
    /*KEY*/ MI_ConstStringField Name;
    /* MSFT_DataFile properties */
    MI_ConstUint32Field Size;
}
MSFT_DataFile;

typedef struct _MSFT_DataFile_Ref
{
    MSFT_DataFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DataFile_Ref;

typedef struct _MSFT_DataFile_ConstRef
{
    MI_CONST MSFT_DataFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DataFile_ConstRef;

typedef struct _MSFT_DataFile_Array
{
    struct _MSFT_DataFile** data;
    MI_Uint32 size;
}
MSFT_DataFile_Array;

typedef struct _MSFT_DataFile_ConstArray
{
    struct _MSFT_DataFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_DataFile_ConstArray;

typedef struct _MSFT_DataFile_ArrayRef
{
    MSFT_DataFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DataFile_ArrayRef;

typedef struct _MSFT_DataFile_ConstArrayRef
{
    MSFT_DataFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_DataFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_DataFile_rtti;

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Construct(
    MSFT_DataFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_DataFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Clone(
    const MSFT_DataFile* self,
    MSFT_DataFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_DataFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_DataFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Destruct(MSFT_DataFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Delete(MSFT_DataFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Post(
    const MSFT_DataFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Set_Name(
    MSFT_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_SetPtr_Name(
    MSFT_DataFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Clear_Name(
    MSFT_DataFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Set_Size(
    MSFT_DataFile* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Size)->value = x;
    ((MI_Uint32Field*)&self->Size)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_DataFile_Clear_Size(
    MSFT_DataFile* self)
{
    memset((void*)&self->Size, 0, sizeof(self->Size));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_DataFile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_DataFile_Self MSFT_DataFile_Self;

MI_EXTERN_C void MI_CALL MSFT_DataFile_Load(
    MSFT_DataFile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DataFile_Unload(
    MSFT_DataFile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_DataFile_EnumerateInstances(
    MSFT_DataFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_DataFile_GetInstance(
    MSFT_DataFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DataFile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_DataFile_CreateInstance(
    MSFT_DataFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DataFile* newInstance);

MI_EXTERN_C void MI_CALL MSFT_DataFile_ModifyInstance(
    MSFT_DataFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DataFile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_DataFile_DeleteInstance(
    MSFT_DataFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_DataFile* instanceName);


#endif /* _MSFT_DataFile_h */
