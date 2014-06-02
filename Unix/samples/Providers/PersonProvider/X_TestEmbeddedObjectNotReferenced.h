/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_TestEmbeddedObjectNotReferenced_h
#define _X_TestEmbeddedObjectNotReferenced_h

#include <MI.h>

/*
**==============================================================================
**
** X_TestEmbeddedObjectNotReferenced [X_TestEmbeddedObjectNotReferenced]
**
** Keys:
**    ObjectID
**
**==============================================================================
*/

typedef struct _X_TestEmbeddedObjectNotReferenced
{
    MI_Instance __instance;
    /* X_TestEmbeddedObjectNotReferenced properties */
    /*KEY*/ MI_ConstUint64Field ObjectID;
}
X_TestEmbeddedObjectNotReferenced;

typedef struct _X_TestEmbeddedObjectNotReferenced_Ref
{
    X_TestEmbeddedObjectNotReferenced* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedObjectNotReferenced_Ref;

typedef struct _X_TestEmbeddedObjectNotReferenced_ConstRef
{
    MI_CONST X_TestEmbeddedObjectNotReferenced* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedObjectNotReferenced_ConstRef;

typedef struct _X_TestEmbeddedObjectNotReferenced_Array
{
    struct _X_TestEmbeddedObjectNotReferenced** data;
    MI_Uint32 size;
}
X_TestEmbeddedObjectNotReferenced_Array;

typedef struct _X_TestEmbeddedObjectNotReferenced_ConstArray
{
    struct _X_TestEmbeddedObjectNotReferenced MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_TestEmbeddedObjectNotReferenced_ConstArray;

typedef struct _X_TestEmbeddedObjectNotReferenced_ArrayRef
{
    X_TestEmbeddedObjectNotReferenced_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedObjectNotReferenced_ArrayRef;

typedef struct _X_TestEmbeddedObjectNotReferenced_ConstArrayRef
{
    X_TestEmbeddedObjectNotReferenced_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedObjectNotReferenced_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_TestEmbeddedObjectNotReferenced_rtti;

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Construct(
    X_TestEmbeddedObjectNotReferenced* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_TestEmbeddedObjectNotReferenced_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Clone(
    const X_TestEmbeddedObjectNotReferenced* self,
    X_TestEmbeddedObjectNotReferenced** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_TestEmbeddedObjectNotReferenced_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_TestEmbeddedObjectNotReferenced_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Destruct(X_TestEmbeddedObjectNotReferenced* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Delete(X_TestEmbeddedObjectNotReferenced* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Post(
    const X_TestEmbeddedObjectNotReferenced* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Set_ObjectID(
    X_TestEmbeddedObjectNotReferenced* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ObjectID)->value = x;
    ((MI_Uint64Field*)&self->ObjectID)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedObjectNotReferenced_Clear_ObjectID(
    X_TestEmbeddedObjectNotReferenced* self)
{
    memset((void*)&self->ObjectID, 0, sizeof(self->ObjectID));
    return MI_RESULT_OK;
}


#endif /* _X_TestEmbeddedObjectNotReferenced_h */
