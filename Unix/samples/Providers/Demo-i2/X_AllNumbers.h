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
#ifndef _X_AllNumbers_h
#define _X_AllNumbers_h

#include <MI.h>
#include "X_Number.h"
#include "X_NumberWorld.h"

/*
**==============================================================================
**
** X_AllNumbers [X_AllNumbers]
**
** Keys:
**    number
**    world
**
**==============================================================================
*/

typedef struct _X_AllNumbers
{
    MI_Instance __instance;
    /* X_AllNumbers properties */
    /*KEY*/ X_Number_ConstRef number;
    /*KEY*/ X_NumberWorld_ConstRef world;
}
X_AllNumbers;

typedef struct _X_AllNumbers_Ref
{
    X_AllNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_AllNumbers_Ref;

typedef struct _X_AllNumbers_ConstRef
{
    MI_CONST X_AllNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_AllNumbers_ConstRef;

typedef struct _X_AllNumbers_Array
{
    struct _X_AllNumbers** data;
    MI_Uint32 size;
}
X_AllNumbers_Array;

typedef struct _X_AllNumbers_ConstArray
{
    struct _X_AllNumbers MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_AllNumbers_ConstArray;

typedef struct _X_AllNumbers_ArrayRef
{
    X_AllNumbers_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_AllNumbers_ArrayRef;

typedef struct _X_AllNumbers_ConstArrayRef
{
    X_AllNumbers_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_AllNumbers_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_AllNumbers_rtti;

MI_INLINE MI_Result MI_CALL X_AllNumbers_Construct(
    X_AllNumbers* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_AllNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Clone(
    const X_AllNumbers* self,
    X_AllNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_AllNumbers_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_AllNumbers_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Destruct(X_AllNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Delete(X_AllNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Post(
    const X_AllNumbers* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Set_number(
    X_AllNumbers* self,
    const X_Number* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_SetPtr_number(
    X_AllNumbers* self,
    const X_Number* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Clear_number(
    X_AllNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Set_world(
    X_AllNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_SetPtr_world(
    X_AllNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_AllNumbers_Clear_world(
    X_AllNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


/*
**==============================================================================
**
** X_AllNumbers_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_AllNumbers_Class : public Instance
{
public:
    
    typedef X_AllNumbers Self;
    
    X_AllNumbers_Class() :
        Instance(&X_AllNumbers_rtti)
    {
    }
    
    X_AllNumbers_Class(
        const X_AllNumbers* instanceName,
        bool keysOnly) :
        Instance(
            &X_AllNumbers_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_AllNumbers_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_AllNumbers_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_AllNumbers_Class& operator=(
        const X_AllNumbers_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_AllNumbers_Class(
        const X_AllNumbers_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_AllNumbers_rtti;
    }

    //
    // X_AllNumbers_Class.number
    //
    
    const Field<X_Number_Class>& number() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_Number_Class>(n);
    }
    
    void number(const Field<X_Number_Class>& x)
    {
        const size_t n = offsetof(Self, number);
        GetField<X_Number_Class>(n) = x;
    }
    
    const X_Number_Class& number_value() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_Number_Class>(n).value;
    }
    
    void number_value(const X_Number_Class& x)
    {
        const size_t n = offsetof(Self, number);
        GetField<X_Number_Class>(n).Set(x);
    }
    
    bool number_exists() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_Number_Class>(n).exists ? true : false;
    }
    
    void number_clear()
    {
        const size_t n = offsetof(Self, number);
        GetField<X_Number_Class>(n).Clear();
    }

    //
    // X_AllNumbers_Class.world
    //
    
    const Field<X_NumberWorld_Class>& world() const
    {
        const size_t n = offsetof(Self, world);
        return GetField<X_NumberWorld_Class>(n);
    }
    
    void world(const Field<X_NumberWorld_Class>& x)
    {
        const size_t n = offsetof(Self, world);
        GetField<X_NumberWorld_Class>(n) = x;
    }
    
    const X_NumberWorld_Class& world_value() const
    {
        const size_t n = offsetof(Self, world);
        return GetField<X_NumberWorld_Class>(n).value;
    }
    
    void world_value(const X_NumberWorld_Class& x)
    {
        const size_t n = offsetof(Self, world);
        GetField<X_NumberWorld_Class>(n).Set(x);
    }
    
    bool world_exists() const
    {
        const size_t n = offsetof(Self, world);
        return GetField<X_NumberWorld_Class>(n).exists ? true : false;
    }
    
    void world_clear()
    {
        const size_t n = offsetof(Self, world);
        GetField<X_NumberWorld_Class>(n).Clear();
    }
};

typedef Array<X_AllNumbers_Class> X_AllNumbers_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_AllNumbers_h */
