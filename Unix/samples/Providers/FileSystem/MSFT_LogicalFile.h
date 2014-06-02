/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_LogicalFile_h
#define _MSFT_LogicalFile_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_LogicalFile [MSFT_LogicalFile]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _MSFT_LogicalFile
{
    MI_Instance __instance;
    /* MSFT_LogicalFile properties */
    /*KEY*/ MI_ConstStringField Name;
}
MSFT_LogicalFile;

typedef struct _MSFT_LogicalFile_Ref
{
    MSFT_LogicalFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogicalFile_Ref;

typedef struct _MSFT_LogicalFile_ConstRef
{
    MI_CONST MSFT_LogicalFile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogicalFile_ConstRef;

typedef struct _MSFT_LogicalFile_Array
{
    struct _MSFT_LogicalFile** data;
    MI_Uint32 size;
}
MSFT_LogicalFile_Array;

typedef struct _MSFT_LogicalFile_ConstArray
{
    struct _MSFT_LogicalFile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_LogicalFile_ConstArray;

typedef struct _MSFT_LogicalFile_ArrayRef
{
    MSFT_LogicalFile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogicalFile_ArrayRef;

typedef struct _MSFT_LogicalFile_ConstArrayRef
{
    MSFT_LogicalFile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LogicalFile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_LogicalFile_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Construct(
    MSFT_LogicalFile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_LogicalFile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Clone(
    const MSFT_LogicalFile* self,
    MSFT_LogicalFile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_LogicalFile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_LogicalFile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Destruct(MSFT_LogicalFile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Delete(MSFT_LogicalFile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Post(
    const MSFT_LogicalFile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Set_Name(
    MSFT_LogicalFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_SetPtr_Name(
    MSFT_LogicalFile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LogicalFile_Clear_Name(
    MSFT_LogicalFile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


#endif /* _MSFT_LogicalFile_h */
