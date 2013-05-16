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
#ifndef _X_Dog_h
#define _X_Dog_h

#include <MI.h>
#include "X_Cat.h"

/*
**==============================================================================
**
** X_Dog [X_Dog]
**
** Keys:
**
**==============================================================================
*/

typedef struct _X_Dog
{
    MI_Instance __instance;
    /* X_Dog properties */
}
X_Dog;

typedef struct _X_Dog_Ref
{
    X_Dog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Dog_Ref;

typedef struct _X_Dog_ConstRef
{
    MI_CONST X_Dog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Dog_ConstRef;

typedef struct _X_Dog_Array
{
    struct _X_Dog** data;
    MI_Uint32 size;
}
X_Dog_Array;

typedef struct _X_Dog_ConstArray
{
    struct _X_Dog MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Dog_ConstArray;

typedef struct _X_Dog_ArrayRef
{
    X_Dog_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Dog_ArrayRef;

typedef struct _X_Dog_ConstArrayRef
{
    X_Dog_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Dog_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Dog_rtti;

MI_INLINE MI_Result MI_CALL X_Dog_Construct(
    X_Dog* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Dog_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Clone(
    const X_Dog* self,
    X_Dog** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Dog_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Dog_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Dog_Destruct(X_Dog* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Delete(X_Dog* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Post(
    const X_Dog* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** X_Dog.Fight()
**
**==============================================================================
*/

typedef struct _X_Dog_Fight
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ X_Cat_ConstArrayRef CatsIn;
    /*OUT*/ X_Cat_ConstArrayRef CatsOut;
}
X_Dog_Fight;

MI_EXTERN_C MI_CONST MI_MethodDecl X_Dog_Fight_rtti;

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Construct(
    X_Dog_Fight* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_Dog_Fight_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Clone(
    const X_Dog_Fight* self,
    X_Dog_Fight** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Destruct(
    X_Dog_Fight* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Delete(
    X_Dog_Fight* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Post(
    const X_Dog_Fight* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Set_MIReturn(
    X_Dog_Fight* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Clear_MIReturn(
    X_Dog_Fight* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Set_CatsIn(
    X_Dog_Fight* self,
    const X_Cat* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_SetPtr_CatsIn(
    X_Dog_Fight* self,
    const X_Cat* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Clear_CatsIn(
    X_Dog_Fight* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Set_CatsOut(
    X_Dog_Fight* self,
    const X_Cat* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_SetPtr_CatsOut(
    X_Dog_Fight* self,
    const X_Cat* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Dog_Fight_Clear_CatsOut(
    X_Dog_Fight* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** X_Dog provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_Dog_Self X_Dog_Self;

MI_EXTERN_C void MI_CALL X_Dog_Load(
    X_Dog_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Dog_Unload(
    X_Dog_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Dog_Invoke_Fight(
    X_Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Dog* instanceName,
    const X_Dog_Fight* in);


/*
**==============================================================================
**
** X_Dog_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Dog_Class : public Instance
{
public:

    typedef X_Dog Self;

    X_Dog_Class() :
        Instance(&X_Dog_rtti)
    {
    }

    X_Dog_Class(
        const X_Dog* instanceName,
        bool keysOnly) :
        Instance(
            &X_Dog_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_Dog_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_Dog_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_Dog_Class& operator=(
        const X_Dog_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_Dog_Class(
        const X_Dog_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Dog_rtti;
    }

};

typedef Array<X_Dog_Class> X_Dog_ClassA;

class X_Dog_Fight_Class : public Instance
{
public:

    typedef X_Dog_Fight Self;

    X_Dog_Fight_Class() :
        Instance(&X_Dog_Fight_rtti)
    {
    }

    X_Dog_Fight_Class(
        const X_Dog_Fight* instanceName,
        bool keysOnly) :
        Instance(
            &X_Dog_Fight_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_Dog_Fight_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_Dog_Fight_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_Dog_Fight_Class& operator=(
        const X_Dog_Fight_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_Dog_Fight_Class(
        const X_Dog_Fight_Class& x) :
        Instance(x)
    {
    }

    //
    // X_Dog_Fight_Class.MIReturn
    //

    const Field<Uint32>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n);
    }

    void MIReturn(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n) = x;
    }

    const Uint32& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).value;
    }

    void MIReturn_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Set(x);
    }

    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).exists ? true : false;
    }

    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_Dog_Fight_Class.CatsIn
    //

    const Field<X_Cat_ClassA>& CatsIn() const
    {
        const size_t n = offsetof(Self, CatsIn);
        return GetField<X_Cat_ClassA>(n);
    }

    void CatsIn(const Field<X_Cat_ClassA>& x)
    {
        const size_t n = offsetof(Self, CatsIn);
        GetField<X_Cat_ClassA>(n) = x;
    }

    const X_Cat_ClassA& CatsIn_value() const
    {
        const size_t n = offsetof(Self, CatsIn);
        return GetField<X_Cat_ClassA>(n).value;
    }

    void CatsIn_value(const X_Cat_ClassA& x)
    {
        const size_t n = offsetof(Self, CatsIn);
        GetField<X_Cat_ClassA>(n).Set(x);
    }

    bool CatsIn_exists() const
    {
        const size_t n = offsetof(Self, CatsIn);
        return GetField<X_Cat_ClassA>(n).exists ? true : false;
    }

    void CatsIn_clear()
    {
        const size_t n = offsetof(Self, CatsIn);
        GetField<X_Cat_ClassA>(n).Clear();
    }

    //
    // X_Dog_Fight_Class.CatsOut
    //

    const Field<X_Cat_ClassA>& CatsOut() const
    {
        const size_t n = offsetof(Self, CatsOut);
        return GetField<X_Cat_ClassA>(n);
    }

    void CatsOut(const Field<X_Cat_ClassA>& x)
    {
        const size_t n = offsetof(Self, CatsOut);
        GetField<X_Cat_ClassA>(n) = x;
    }

    const X_Cat_ClassA& CatsOut_value() const
    {
        const size_t n = offsetof(Self, CatsOut);
        return GetField<X_Cat_ClassA>(n).value;
    }

    void CatsOut_value(const X_Cat_ClassA& x)
    {
        const size_t n = offsetof(Self, CatsOut);
        GetField<X_Cat_ClassA>(n).Set(x);
    }

    bool CatsOut_exists() const
    {
        const size_t n = offsetof(Self, CatsOut);
        return GetField<X_Cat_ClassA>(n).exists ? true : false;
    }

    void CatsOut_clear()
    {
        const size_t n = offsetof(Self, CatsOut);
        GetField<X_Cat_ClassA>(n).Clear();
    }
};

typedef Array<X_Dog_Fight_Class> X_Dog_Fight_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Dog_h */
