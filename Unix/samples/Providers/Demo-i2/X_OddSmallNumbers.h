/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_OddSmallNumbers_h
#define _X_OddSmallNumbers_h

#include <MI.h>
#include "X_AllNumbers.h"
#include "X_SmallNumber.h"
#include "X_NumberWorld.h"

/*
**==============================================================================
**
** X_OddSmallNumbers [X_OddSmallNumbers]
**
** Keys:
**    number
**    world
**
**==============================================================================
*/

typedef struct _X_OddSmallNumbers /* extends X_AllNumbers */
{
    MI_Instance __instance;
    /* X_AllNumbers properties */
    /*KEY*/ X_SmallNumber_ConstRef number;
    /*KEY*/ X_NumberWorld_ConstRef world;
    /* X_OddSmallNumbers properties */
    MI_ConstUint64AField factors;
}
X_OddSmallNumbers;

typedef struct _X_OddSmallNumbers_Ref
{
    X_OddSmallNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_OddSmallNumbers_Ref;

typedef struct _X_OddSmallNumbers_ConstRef
{
    MI_CONST X_OddSmallNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_OddSmallNumbers_ConstRef;

typedef struct _X_OddSmallNumbers_Array
{
    struct _X_OddSmallNumbers** data;
    MI_Uint32 size;
}
X_OddSmallNumbers_Array;

typedef struct _X_OddSmallNumbers_ConstArray
{
    struct _X_OddSmallNumbers MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_OddSmallNumbers_ConstArray;

typedef struct _X_OddSmallNumbers_ArrayRef
{
    X_OddSmallNumbers_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_OddSmallNumbers_ArrayRef;

typedef struct _X_OddSmallNumbers_ConstArrayRef
{
    X_OddSmallNumbers_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_OddSmallNumbers_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_OddSmallNumbers_rtti;

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Construct(
    X_OddSmallNumbers* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_OddSmallNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Clone(
    const X_OddSmallNumbers* self,
    X_OddSmallNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_OddSmallNumbers_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_OddSmallNumbers_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Destruct(X_OddSmallNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Delete(X_OddSmallNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Post(
    const X_OddSmallNumbers* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Set_number(
    X_OddSmallNumbers* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_SetPtr_number(
    X_OddSmallNumbers* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Clear_number(
    X_OddSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Set_world(
    X_OddSmallNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_SetPtr_world(
    X_OddSmallNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Clear_world(
    X_OddSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Set_factors(
    X_OddSmallNumbers* self,
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

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_SetPtr_factors(
    X_OddSmallNumbers* self,
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

MI_INLINE MI_Result MI_CALL X_OddSmallNumbers_Clear_factors(
    X_OddSmallNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** X_OddSmallNumbers provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_OddSmallNumbers_Self X_OddSmallNumbers_Self;

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_Load(
    X_OddSmallNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_Unload(
    X_OddSmallNumbers_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_EnumerateInstances(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_GetInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_CreateInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* newInstance);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_ModifyInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_DeleteInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* instanceName);

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_AssociatorInstances(
    X_OddSmallNumbers_Self* self,
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

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_ReferenceInstances(
    X_OddSmallNumbers_Self* self,
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
** X_OddSmallNumbers_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_OddSmallNumbers_Class : public X_AllNumbers_Class
{
public:
    
    typedef X_OddSmallNumbers Self;
    
    X_OddSmallNumbers_Class() :
        X_AllNumbers_Class(&X_OddSmallNumbers_rtti)
    {
    }
    
    X_OddSmallNumbers_Class(
        const X_OddSmallNumbers* instanceName,
        bool keysOnly) :
        X_AllNumbers_Class(
            &X_OddSmallNumbers_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_OddSmallNumbers_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_AllNumbers_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_OddSmallNumbers_Class(
        const MI_ClassDecl* clDecl) :
        X_AllNumbers_Class(clDecl)
    {
    }
    
    X_OddSmallNumbers_Class& operator=(
        const X_OddSmallNumbers_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_OddSmallNumbers_Class(
        const X_OddSmallNumbers_Class& x) :
        X_AllNumbers_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_OddSmallNumbers_rtti;
    }

    //
    // X_OddSmallNumbers_Class.factors
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
};

typedef Array<X_OddSmallNumbers_Class> X_OddSmallNumbers_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_OddSmallNumbers_h */
