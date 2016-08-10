/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_EvenSmallNumbers_h
#define _X_EvenSmallNumbers_h

#include <MI.h>
#include "X_AllNumbers.h"
#include "X_SmallNumber.h"
#include "X_NumberWorld.h"

/*
**==============================================================================
**
** X_EvenSmallNumbers [X_EvenSmallNumbers]
**
** Keys:
**    number
**    world
**
**==============================================================================
*/

typedef struct _X_EvenSmallNumbers /* extends X_AllNumbers */
{
    MI_Instance __instance;
    /* X_AllNumbers properties */
    /*KEY*/ X_SmallNumber_ConstRef number;
    /*KEY*/ X_NumberWorld_ConstRef world;
    /* X_EvenSmallNumbers properties */
    MI_ConstUint64AField factors;
    MI_ConstBooleanField prime;
}
X_EvenSmallNumbers;

typedef struct _X_EvenSmallNumbers_Ref
{
    X_EvenSmallNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_EvenSmallNumbers_Ref;

typedef struct _X_EvenSmallNumbers_ConstRef
{
    MI_CONST X_EvenSmallNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_EvenSmallNumbers_ConstRef;

typedef struct _X_EvenSmallNumbers_Array
{
    struct _X_EvenSmallNumbers** data;
    MI_Uint32 size;
}
X_EvenSmallNumbers_Array;

typedef struct _X_EvenSmallNumbers_ConstArray
{
    struct _X_EvenSmallNumbers MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_EvenSmallNumbers_ConstArray;

typedef struct _X_EvenSmallNumbers_ArrayRef
{
    X_EvenSmallNumbers_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_EvenSmallNumbers_ArrayRef;

typedef struct _X_EvenSmallNumbers_ConstArrayRef
{
    X_EvenSmallNumbers_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_EvenSmallNumbers_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_EvenSmallNumbers_rtti;

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Construct(
    X_EvenSmallNumbers* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_EvenSmallNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Clone(
    const X_EvenSmallNumbers* self,
    X_EvenSmallNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_EvenSmallNumbers_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_EvenSmallNumbers_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Destruct(X_EvenSmallNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Delete(X_EvenSmallNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Post(
    const X_EvenSmallNumbers* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Set_number(
    X_EvenSmallNumbers* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_SetPtr_number(
    X_EvenSmallNumbers* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Clear_number(
    X_EvenSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Set_world(
    X_EvenSmallNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_SetPtr_world(
    X_EvenSmallNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Clear_world(
    X_EvenSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Set_factors(
    X_EvenSmallNumbers* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_SetPtr_factors(
    X_EvenSmallNumbers* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Clear_factors(
    X_EvenSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Set_prime(
    X_EvenSmallNumbers* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->prime)->value = x;
    ((MI_BooleanField*)&self->prime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_EvenSmallNumbers_Clear_prime(
    X_EvenSmallNumbers* self)
{
    memset((void*)&self->prime, 0, sizeof(self->prime));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_EvenSmallNumbers provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_EvenSmallNumbers_Self X_EvenSmallNumbers_Self;

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_Load(
    X_EvenSmallNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_Unload(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_EnumerateInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_GetInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_CreateInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* newInstance);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_ModifyInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_DeleteInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* instanceName);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_AssociatorInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_ReferenceInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


/*
**==============================================================================
**
** X_EvenSmallNumbers_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_EvenSmallNumbers_Class : public X_AllNumbers_Class
{
public:
    
    typedef X_EvenSmallNumbers Self;
    
    X_EvenSmallNumbers_Class() :
        X_AllNumbers_Class(&X_EvenSmallNumbers_rtti)
    {
    }
    
    X_EvenSmallNumbers_Class(
        const X_EvenSmallNumbers* instanceName,
        bool keysOnly) :
        X_AllNumbers_Class(
            &X_EvenSmallNumbers_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_EvenSmallNumbers_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_AllNumbers_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_EvenSmallNumbers_Class(
        const MI_ClassDecl* clDecl) :
        X_AllNumbers_Class(clDecl)
    {
    }
    
    X_EvenSmallNumbers_Class& operator=(
        const X_EvenSmallNumbers_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_EvenSmallNumbers_Class(
        const X_EvenSmallNumbers_Class& x) :
        X_AllNumbers_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_EvenSmallNumbers_rtti;
    }

    //
    // X_EvenSmallNumbers_Class.factors
    //
    
    const Field<Uint64A>& factors() const
    {
        const size_t n = offsetof(Self, factors);
        return GetField<Uint64A>(n);
    }
    
    void factors(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, factors);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& factors_value() const
    {
        const size_t n = offsetof(Self, factors);
        return GetField<Uint64A>(n).value;
    }
    
    void factors_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, factors);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool factors_exists() const
    {
        const size_t n = offsetof(Self, factors);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void factors_clear()
    {
        const size_t n = offsetof(Self, factors);
        GetField<Uint64A>(n).Clear();
    }

    //
    // X_EvenSmallNumbers_Class.prime
    //
    
    const Field<Boolean>& prime() const
    {
        const size_t n = offsetof(Self, prime);
        return GetField<Boolean>(n);
    }
    
    void prime(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, prime);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& prime_value() const
    {
        const size_t n = offsetof(Self, prime);
        return GetField<Boolean>(n).value;
    }
    
    void prime_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, prime);
        GetField<Boolean>(n).Set(x);
    }
    
    bool prime_exists() const
    {
        const size_t n = offsetof(Self, prime);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void prime_clear()
    {
        const size_t n = offsetof(Self, prime);
        GetField<Boolean>(n).Clear();
    }
};

typedef Array<X_EvenSmallNumbers_Class> X_EvenSmallNumbers_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_EvenSmallNumbers_h */
