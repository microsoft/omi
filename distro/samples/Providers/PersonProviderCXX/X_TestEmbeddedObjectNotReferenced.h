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


/*
**==============================================================================
**
** X_TestEmbeddedObjectNotReferenced_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_TestEmbeddedObjectNotReferenced_Class : public Instance
{
public:
    
    typedef X_TestEmbeddedObjectNotReferenced Self;
    
    X_TestEmbeddedObjectNotReferenced_Class() :
        Instance(&X_TestEmbeddedObjectNotReferenced_rtti)
    {
    }
    
    X_TestEmbeddedObjectNotReferenced_Class(
        const X_TestEmbeddedObjectNotReferenced* instanceName,
        bool keysOnly) :
        Instance(
            &X_TestEmbeddedObjectNotReferenced_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_TestEmbeddedObjectNotReferenced_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_TestEmbeddedObjectNotReferenced_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_TestEmbeddedObjectNotReferenced_Class& operator=(
        const X_TestEmbeddedObjectNotReferenced_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_TestEmbeddedObjectNotReferenced_Class(
        const X_TestEmbeddedObjectNotReferenced_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_TestEmbeddedObjectNotReferenced_rtti;
    }

    //
    // X_TestEmbeddedObjectNotReferenced_Class.ObjectID
    //
    
    const Field<Uint64>& ObjectID() const
    {
        const size_t n = offsetof(Self, ObjectID);
        return GetField<Uint64>(n);
    }
    
    void ObjectID(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, ObjectID);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& ObjectID_value() const
    {
        const size_t n = offsetof(Self, ObjectID);
        return GetField<Uint64>(n).value;
    }
    
    void ObjectID_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, ObjectID);
        GetField<Uint64>(n).Set(x);
    }
    
    bool ObjectID_exists() const
    {
        const size_t n = offsetof(Self, ObjectID);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void ObjectID_clear()
    {
        const size_t n = offsetof(Self, ObjectID);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<X_TestEmbeddedObjectNotReferenced_Class> X_TestEmbeddedObjectNotReferenced_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_TestEmbeddedObjectNotReferenced_h */
