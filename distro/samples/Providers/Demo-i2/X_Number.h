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
#ifndef _X_Number_h
#define _X_Number_h

#include <MI.h>
#include "X_ManagedElement.h"

/*
**==============================================================================
**
** X_Number [X_Number]
**
** Keys:
**    Number
**
**==============================================================================
*/

typedef struct _X_Number /* extends X_ManagedElement */
{
    MI_Instance __instance;
    /* X_ManagedElement properties */
    MI_ConstStringField Description;
    /* X_Number properties */
    /*KEY*/ MI_ConstUint64Field Number;
}
X_Number;

typedef struct _X_Number_Ref
{
    X_Number* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number_Ref;

typedef struct _X_Number_ConstRef
{
    MI_CONST X_Number* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number_ConstRef;

typedef struct _X_Number_Array
{
    struct _X_Number** data;
    MI_Uint32 size;
}
X_Number_Array;

typedef struct _X_Number_ConstArray
{
    struct _X_Number MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Number_ConstArray;

typedef struct _X_Number_ArrayRef
{
    X_Number_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number_ArrayRef;

typedef struct _X_Number_ConstArrayRef
{
    X_Number_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Number_rtti;

MI_INLINE MI_Result MI_CALL X_Number_Construct(
    X_Number* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Number_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number_Clone(
    const X_Number* self,
    X_Number** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Number_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Number_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Number_Destruct(X_Number* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number_Delete(X_Number* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number_Post(
    const X_Number* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number_Set_Description(
    X_Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number_SetPtr_Description(
    X_Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number_Clear_Description(
    X_Number* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number_Set_Number(
    X_Number* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Number)->value = x;
    ((MI_Uint64Field*)&self->Number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number_Clear_Number(
    X_Number* self)
{
    memset((void*)&self->Number, 0, sizeof(self->Number));
    return MI_RESULT_OK;
}


/*
**==============================================================================
**
** X_Number_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Number_Class : public X_ManagedElement_Class
{
public:

    typedef X_Number Self;

    X_Number_Class() :
        X_ManagedElement_Class(&X_Number_rtti)
    {
    }

    X_Number_Class(
        const X_Number* instanceName,
        bool keysOnly) :
        X_ManagedElement_Class(
            &X_Number_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_Number_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_ManagedElement_Class(clDecl, instance, keysOnly)
    {
    }

    X_Number_Class(
        const MI_ClassDecl* clDecl) :
        X_ManagedElement_Class(clDecl)
    {
    }

    X_Number_Class& operator=(
        const X_Number_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_Number_Class(
        const X_Number_Class& x) :
        X_ManagedElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Number_rtti;
    }

    //
    // X_Number_Class.Number
    //

    const Field<Uint64>& Number() const
    {
        const size_t n = offsetof(Self, Number);
        return GetField<Uint64>(n);
    }

    void Number(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, Number);
        GetField<Uint64>(n) = x;
    }

    const Uint64& Number_value() const
    {
        const size_t n = offsetof(Self, Number);
        return GetField<Uint64>(n).value;
    }

    void Number_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, Number);
        GetField<Uint64>(n).Set(x);
    }

    bool Number_exists() const
    {
        const size_t n = offsetof(Self, Number);
        return GetField<Uint64>(n).exists ? true : false;
    }

    void Number_clear()
    {
        const size_t n = offsetof(Self, Number);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<X_Number_Class> X_Number_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Number_h */
