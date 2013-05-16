/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Directory_h
#define _MSFT_Directory_h

#include <MI.h>
#include "MSFT_LogicalFile.h"

/*
**==============================================================================
**
** MSFT_Directory [MSFT_Directory]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_Directory /* extends MSFT_LogicalFile */
{
    MI_Instance __instance;
    /* MSFT_LogicalFile properties */
    /*KEY*/ MI_ConstStringField Name;
    /* MSFT_Directory properties */
    MI_ConstUint32Field Count;
    MI_ConstStringAField FileNames;
}
MSFT_Directory;

typedef struct _MSFT_Directory_Ref
{
    MSFT_Directory* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Directory_Ref;

typedef struct _MSFT_Directory_ConstRef
{
    MI_CONST MSFT_Directory* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Directory_ConstRef;

typedef struct _MSFT_Directory_Array
{
    struct _MSFT_Directory** data;
    MI_Uint32 size;
}
MSFT_Directory_Array;

typedef struct _MSFT_Directory_ConstArray
{
    struct _MSFT_Directory MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Directory_ConstArray;

typedef struct _MSFT_Directory_ArrayRef
{
    MSFT_Directory_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Directory_ArrayRef;

typedef struct _MSFT_Directory_ConstArrayRef
{
    MSFT_Directory_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Directory_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Directory_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Directory_Construct(
    MSFT_Directory* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Directory_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Clone(
    const MSFT_Directory* self,
    MSFT_Directory** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Directory_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Directory_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Destruct(MSFT_Directory* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Delete(MSFT_Directory* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Post(
    const MSFT_Directory* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Set_Name(
    MSFT_Directory* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_SetPtr_Name(
    MSFT_Directory* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Clear_Name(
    MSFT_Directory* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Set_Count(
    MSFT_Directory* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Count)->value = x;
    ((MI_Uint32Field*)&self->Count)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Clear_Count(
    MSFT_Directory* self)
{
    memset((void*)&self->Count, 0, sizeof(self->Count));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Directory_Set_FileNames(
    MSFT_Directory* self,
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

MI_INLINE MI_Result MI_CALL MSFT_Directory_SetPtr_FileNames(
    MSFT_Directory* self,
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

MI_INLINE MI_Result MI_CALL MSFT_Directory_Clear_FileNames(
    MSFT_Directory* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_Directory provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_Directory_Self MSFT_Directory_Self;

MI_EXTERN_C void MI_CALL MSFT_Directory_Load(
    MSFT_Directory_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Directory_Unload(
    MSFT_Directory_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Directory_EnumerateInstances(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Directory_GetInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Directory_CreateInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* newInstance);

MI_EXTERN_C void MI_CALL MSFT_Directory_ModifyInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Directory_DeleteInstance(
    MSFT_Directory_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Directory* instanceName);


#endif /* _MSFT_Directory_h */
