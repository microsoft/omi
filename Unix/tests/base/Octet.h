/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Octet_h
#define _Octet_h

#include <MI.h>

/*
**==============================================================================
**
** Octet [Octet]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Octet
{
    MI_Instance __instance;
    /* Octet properties */
    MI_ConstUint8AField array;
}
Octet;

typedef struct _Octet_Ref
{
    Octet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Octet_Ref;

typedef struct _Octet_ConstRef
{
    MI_CONST Octet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Octet_ConstRef;

typedef struct _Octet_Array
{
    struct _Octet** data;
    MI_Uint32 size;
}
Octet_Array;

typedef struct _Octet_ConstArray
{
    struct _Octet MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Octet_ConstArray;

typedef struct _Octet_ArrayRef
{
    Octet_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Octet_ArrayRef;

typedef struct _Octet_ConstArrayRef
{
    Octet_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Octet_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Octet_rtti;

MI_INLINE MI_Result MI_CALL Octet_Set_array(
    Octet* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Octet_SetPtr_array(
    Octet* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Octet_Clear_array(
    Octet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


/*
**==============================================================================
**
** Octet_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Octet_Class : public Instance
{
public:
    
    typedef Octet Self;
    
    Octet_Class() :
        Instance(&Octet_rtti)
    {
    }
    
    Octet_Class(
        const Octet* instanceName,
        bool keysOnly) :
        Instance(
            &Octet_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Octet_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Octet_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Octet_Class& operator=(
        const Octet_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Octet_Class(
        const Octet_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Octet_rtti;
    }

    //
    // Octet_Class.array
    //
    
    const Field<Uint8A>& array() const
    {
        const size_t n = offsetof(Self, array);
        return GetField<Uint8A>(n);
    }
    
    void array(const Field<Uint8A>& x)
    {
        const size_t n = offsetof(Self, array);
        GetField<Uint8A>(n) = x;
    }
    
    const Uint8A& array_value() const
    {
        const size_t n = offsetof(Self, array);
        return GetField<Uint8A>(n).value;
    }
    
    void array_value(const Uint8A& x)
    {
        const size_t n = offsetof(Self, array);
        GetField<Uint8A>(n).Set(x);
    }
    
    bool array_exists() const
    {
        const size_t n = offsetof(Self, array);
        return GetField<Uint8A>(n).exists ? true : false;
    }
    
    void array_clear()
    {
        const size_t n = offsetof(Self, array);
        GetField<Uint8A>(n).Clear();
    }
};

typedef Array<Octet_Class> Octet_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Octet_h */
