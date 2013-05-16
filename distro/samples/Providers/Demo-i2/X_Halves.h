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
#ifndef _X_Halves_h
#define _X_Halves_h

#include <MI.h>
#include "X_SmallNumber.h"

/*
**==============================================================================
**
** X_Halves [X_Halves]
**
** Keys:
**    number
**    half
**
**==============================================================================
*/

typedef struct _X_Halves
{
    MI_Instance __instance;
    /* X_Halves properties */
    /*KEY*/ X_SmallNumber_ConstRef number;
    /*KEY*/ X_SmallNumber_ConstRef half;
}
X_Halves;

typedef struct _X_Halves_Ref
{
    X_Halves* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Halves_Ref;

typedef struct _X_Halves_ConstRef
{
    MI_CONST X_Halves* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Halves_ConstRef;

typedef struct _X_Halves_Array
{
    struct _X_Halves** data;
    MI_Uint32 size;
}
X_Halves_Array;

typedef struct _X_Halves_ConstArray
{
    struct _X_Halves MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Halves_ConstArray;

typedef struct _X_Halves_ArrayRef
{
    X_Halves_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Halves_ArrayRef;

typedef struct _X_Halves_ConstArrayRef
{
    X_Halves_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Halves_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Halves_rtti;

MI_INLINE MI_Result MI_CALL X_Halves_Construct(
    X_Halves* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Halves_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Halves_Clone(
    const X_Halves* self,
    X_Halves** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Halves_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Halves_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Halves_Destruct(X_Halves* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Halves_Delete(X_Halves* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Halves_Post(
    const X_Halves* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Halves_Set_number(
    X_Halves* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Halves_SetPtr_number(
    X_Halves* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Halves_Clear_number(
    X_Halves* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_Halves_Set_half(
    X_Halves* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Halves_SetPtr_half(
    X_Halves* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Halves_Clear_half(
    X_Halves* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_Halves provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_Halves_Self X_Halves_Self;

MI_EXTERN_C void MI_CALL X_Halves_Load(
    X_Halves_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Halves_Unload(
    X_Halves_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Halves_EnumerateInstances(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_Halves_GetInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Halves_CreateInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* newInstance);

MI_EXTERN_C void MI_CALL X_Halves_ModifyInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Halves_DeleteInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* instanceName);

MI_EXTERN_C void MI_CALL X_Halves_AssociatorInstances(
    X_Halves_Self* self,
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

MI_EXTERN_C void MI_CALL X_Halves_ReferenceInstances(
    X_Halves_Self* self,
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
** X_Halves_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Halves_Class : public Instance
{
public:

    typedef X_Halves Self;

    X_Halves_Class() :
        Instance(&X_Halves_rtti)
    {
    }

    X_Halves_Class(
        const X_Halves* instanceName,
        bool keysOnly) :
        Instance(
            &X_Halves_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_Halves_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_Halves_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_Halves_Class& operator=(
        const X_Halves_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_Halves_Class(
        const X_Halves_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Halves_rtti;
    }

    //
    // X_Halves_Class.number
    //

    const Field<X_SmallNumber_Class>& number() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_SmallNumber_Class>(n);
    }

    void number(const Field<X_SmallNumber_Class>& x)
    {
        const size_t n = offsetof(Self, number);
        GetField<X_SmallNumber_Class>(n) = x;
    }

    const X_SmallNumber_Class& number_value() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_SmallNumber_Class>(n).value;
    }

    void number_value(const X_SmallNumber_Class& x)
    {
        const size_t n = offsetof(Self, number);
        GetField<X_SmallNumber_Class>(n).Set(x);
    }

    bool number_exists() const
    {
        const size_t n = offsetof(Self, number);
        return GetField<X_SmallNumber_Class>(n).exists ? true : false;
    }

    void number_clear()
    {
        const size_t n = offsetof(Self, number);
        GetField<X_SmallNumber_Class>(n).Clear();
    }

    //
    // X_Halves_Class.half
    //

    const Field<X_SmallNumber_Class>& half() const
    {
        const size_t n = offsetof(Self, half);
        return GetField<X_SmallNumber_Class>(n);
    }

    void half(const Field<X_SmallNumber_Class>& x)
    {
        const size_t n = offsetof(Self, half);
        GetField<X_SmallNumber_Class>(n) = x;
    }

    const X_SmallNumber_Class& half_value() const
    {
        const size_t n = offsetof(Self, half);
        return GetField<X_SmallNumber_Class>(n).value;
    }

    void half_value(const X_SmallNumber_Class& x)
    {
        const size_t n = offsetof(Self, half);
        GetField<X_SmallNumber_Class>(n).Set(x);
    }

    bool half_exists() const
    {
        const size_t n = offsetof(Self, half);
        return GetField<X_SmallNumber_Class>(n).exists ? true : false;
    }

    void half_clear()
    {
        const size_t n = offsetof(Self, half);
        GetField<X_SmallNumber_Class>(n).Clear();
    }
};

typedef Array<X_Halves_Class> X_Halves_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Halves_h */
