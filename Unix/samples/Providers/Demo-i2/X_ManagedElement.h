/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_ManagedElement_h
#define _X_ManagedElement_h

#include <MI.h>

/*
**==============================================================================
**
** X_ManagedElement [X_ManagedElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _X_ManagedElement
{
    MI_Instance __instance;
    /* X_ManagedElement properties */
    MI_ConstStringField Description;
}
X_ManagedElement;

typedef struct _X_ManagedElement_Ref
{
    X_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ManagedElement_Ref;

typedef struct _X_ManagedElement_ConstRef
{
    MI_CONST X_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ManagedElement_ConstRef;

typedef struct _X_ManagedElement_Array
{
    struct _X_ManagedElement** data;
    MI_Uint32 size;
}
X_ManagedElement_Array;

typedef struct _X_ManagedElement_ConstArray
{
    struct _X_ManagedElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_ManagedElement_ConstArray;

typedef struct _X_ManagedElement_ArrayRef
{
    X_ManagedElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ManagedElement_ArrayRef;

typedef struct _X_ManagedElement_ConstArrayRef
{
    X_ManagedElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ManagedElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_ManagedElement_rtti;

MI_INLINE MI_Result MI_CALL X_ManagedElement_Construct(
    X_ManagedElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_ManagedElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Clone(
    const X_ManagedElement* self,
    X_ManagedElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_ManagedElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_ManagedElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Destruct(X_ManagedElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Delete(X_ManagedElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Post(
    const X_ManagedElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Set_Description(
    X_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_SetPtr_Description(
    X_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_ManagedElement_Clear_Description(
    X_ManagedElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


/*
**==============================================================================
**
** X_ManagedElement_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_ManagedElement_Class : public Instance
{
public:
    
    typedef X_ManagedElement Self;
    
    X_ManagedElement_Class() :
        Instance(&X_ManagedElement_rtti)
    {
    }
    
    X_ManagedElement_Class(
        const X_ManagedElement* instanceName,
        bool keysOnly) :
        Instance(
            &X_ManagedElement_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_ManagedElement_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_ManagedElement_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_ManagedElement_Class& operator=(
        const X_ManagedElement_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_ManagedElement_Class(
        const X_ManagedElement_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_ManagedElement_rtti;
    }

    //
    // X_ManagedElement_Class.Description
    //
    
    const Field<String>& Description() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n);
    }
    
    void Description(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n) = x;
    }
    
    const String& Description_value() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).value;
    }
    
    void Description_value(const String& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Set(x);
    }
    
    bool Description_exists() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Description_clear()
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_ManagedElement_Class> X_ManagedElement_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_ManagedElement_h */
