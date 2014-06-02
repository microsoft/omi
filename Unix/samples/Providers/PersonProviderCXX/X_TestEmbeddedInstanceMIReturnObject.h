/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_TestEmbeddedInstanceMIReturnObject_h
#define _X_TestEmbeddedInstanceMIReturnObject_h

#include <MI.h>

/*
**==============================================================================
**
** X_TestEmbeddedInstanceMIReturnObject [X_TestEmbeddedInstanceMIReturnObject]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_TestEmbeddedInstanceMIReturnObject
{
    MI_Instance __instance;
    /* X_TestEmbeddedInstanceMIReturnObject properties */
    /*KEY*/ MI_ConstUint64Field id;
    MI_ConstStringField s;
}
X_TestEmbeddedInstanceMIReturnObject;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_Ref
{
    X_TestEmbeddedInstanceMIReturnObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedInstanceMIReturnObject_Ref;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_ConstRef
{
    MI_CONST X_TestEmbeddedInstanceMIReturnObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedInstanceMIReturnObject_ConstRef;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_Array
{
    struct _X_TestEmbeddedInstanceMIReturnObject** data;
    MI_Uint32 size;
}
X_TestEmbeddedInstanceMIReturnObject_Array;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_ConstArray
{
    struct _X_TestEmbeddedInstanceMIReturnObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_TestEmbeddedInstanceMIReturnObject_ConstArray;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_ArrayRef
{
    X_TestEmbeddedInstanceMIReturnObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedInstanceMIReturnObject_ArrayRef;

typedef struct _X_TestEmbeddedInstanceMIReturnObject_ConstArrayRef
{
    X_TestEmbeddedInstanceMIReturnObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestEmbeddedInstanceMIReturnObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_TestEmbeddedInstanceMIReturnObject_rtti;

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Construct(
    X_TestEmbeddedInstanceMIReturnObject* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_TestEmbeddedInstanceMIReturnObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Clone(
    const X_TestEmbeddedInstanceMIReturnObject* self,
    X_TestEmbeddedInstanceMIReturnObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_TestEmbeddedInstanceMIReturnObject_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_TestEmbeddedInstanceMIReturnObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Destruct(X_TestEmbeddedInstanceMIReturnObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Delete(X_TestEmbeddedInstanceMIReturnObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Post(
    const X_TestEmbeddedInstanceMIReturnObject* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Set_id(
    X_TestEmbeddedInstanceMIReturnObject* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Clear_id(
    X_TestEmbeddedInstanceMIReturnObject* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Set_s(
    X_TestEmbeddedInstanceMIReturnObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_SetPtr_s(
    X_TestEmbeddedInstanceMIReturnObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_TestEmbeddedInstanceMIReturnObject_Clear_s(
    X_TestEmbeddedInstanceMIReturnObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


/*
**==============================================================================
**
** X_TestEmbeddedInstanceMIReturnObject_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_TestEmbeddedInstanceMIReturnObject_Class : public Instance
{
public:
    
    typedef X_TestEmbeddedInstanceMIReturnObject Self;
    
    X_TestEmbeddedInstanceMIReturnObject_Class() :
        Instance(&X_TestEmbeddedInstanceMIReturnObject_rtti)
    {
    }
    
    X_TestEmbeddedInstanceMIReturnObject_Class(
        const X_TestEmbeddedInstanceMIReturnObject* instanceName,
        bool keysOnly) :
        Instance(
            &X_TestEmbeddedInstanceMIReturnObject_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_TestEmbeddedInstanceMIReturnObject_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_TestEmbeddedInstanceMIReturnObject_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_TestEmbeddedInstanceMIReturnObject_Class& operator=(
        const X_TestEmbeddedInstanceMIReturnObject_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_TestEmbeddedInstanceMIReturnObject_Class(
        const X_TestEmbeddedInstanceMIReturnObject_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_TestEmbeddedInstanceMIReturnObject_rtti;
    }

    //
    // X_TestEmbeddedInstanceMIReturnObject_Class.id
    //
    
    const Field<Uint64>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n);
    }
    
    void id(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).value;
    }
    
    void id_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Clear();
    }

    //
    // X_TestEmbeddedInstanceMIReturnObject_Class.s
    //
    
    const Field<String>& s() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n);
    }
    
    void s(const Field<String>& x)
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n) = x;
    }
    
    const String& s_value() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n).value;
    }
    
    void s_value(const String& x)
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n).Set(x);
    }
    
    bool s_exists() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n).exists ? true : false;
    }
    
    void s_clear()
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_TestEmbeddedInstanceMIReturnObject_Class> X_TestEmbeddedInstanceMIReturnObject_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_TestEmbeddedInstanceMIReturnObject_h */
