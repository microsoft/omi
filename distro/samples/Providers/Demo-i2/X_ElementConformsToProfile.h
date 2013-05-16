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
#ifndef _X_ElementConformsToProfile_h
#define _X_ElementConformsToProfile_h

#include <MI.h>
#include "X_Profile.h"
#include "X_ManagedElement.h"

/*
**==============================================================================
**
** X_ElementConformsToProfile [X_ElementConformsToProfile]
**
** Keys:
**    Profile
**    Element
**
**==============================================================================
*/

typedef struct _X_ElementConformsToProfile
{
    MI_Instance __instance;
    /* X_ElementConformsToProfile properties */
    /*KEY*/ X_Profile_ConstRef Profile;
    /*KEY*/ X_ManagedElement_ConstRef Element;
}
X_ElementConformsToProfile;

typedef struct _X_ElementConformsToProfile_Ref
{
    X_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ElementConformsToProfile_Ref;

typedef struct _X_ElementConformsToProfile_ConstRef
{
    MI_CONST X_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ElementConformsToProfile_ConstRef;

typedef struct _X_ElementConformsToProfile_Array
{
    struct _X_ElementConformsToProfile** data;
    MI_Uint32 size;
}
X_ElementConformsToProfile_Array;

typedef struct _X_ElementConformsToProfile_ConstArray
{
    struct _X_ElementConformsToProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_ElementConformsToProfile_ConstArray;

typedef struct _X_ElementConformsToProfile_ArrayRef
{
    X_ElementConformsToProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ElementConformsToProfile_ArrayRef;

typedef struct _X_ElementConformsToProfile_ConstArrayRef
{
    X_ElementConformsToProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_ElementConformsToProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_ElementConformsToProfile_rtti;

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Construct(
    X_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_ElementConformsToProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Clone(
    const X_ElementConformsToProfile* self,
    X_ElementConformsToProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_ElementConformsToProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_ElementConformsToProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Destruct(X_ElementConformsToProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Delete(X_ElementConformsToProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Post(
    const X_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Set_Profile(
    X_ElementConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_SetPtr_Profile(
    X_ElementConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Clear_Profile(
    X_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Set_Element(
    X_ElementConformsToProfile* self,
    const X_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_SetPtr_Element(
    X_ElementConformsToProfile* self,
    const X_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_ElementConformsToProfile_Clear_Element(
    X_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


/*
**==============================================================================
**
** X_ElementConformsToProfile_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_ElementConformsToProfile_Class : public Instance
{
public:

    typedef X_ElementConformsToProfile Self;

    X_ElementConformsToProfile_Class() :
        Instance(&X_ElementConformsToProfile_rtti)
    {
    }

    X_ElementConformsToProfile_Class(
        const X_ElementConformsToProfile* instanceName,
        bool keysOnly) :
        Instance(
            &X_ElementConformsToProfile_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_ElementConformsToProfile_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_ElementConformsToProfile_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_ElementConformsToProfile_Class& operator=(
        const X_ElementConformsToProfile_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_ElementConformsToProfile_Class(
        const X_ElementConformsToProfile_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_ElementConformsToProfile_rtti;
    }

    //
    // X_ElementConformsToProfile_Class.Profile
    //

    const Field<X_Profile_Class>& Profile() const
    {
        const size_t n = offsetof(Self, Profile);
        return GetField<X_Profile_Class>(n);
    }

    void Profile(const Field<X_Profile_Class>& x)
    {
        const size_t n = offsetof(Self, Profile);
        GetField<X_Profile_Class>(n) = x;
    }

    const X_Profile_Class& Profile_value() const
    {
        const size_t n = offsetof(Self, Profile);
        return GetField<X_Profile_Class>(n).value;
    }

    void Profile_value(const X_Profile_Class& x)
    {
        const size_t n = offsetof(Self, Profile);
        GetField<X_Profile_Class>(n).Set(x);
    }

    bool Profile_exists() const
    {
        const size_t n = offsetof(Self, Profile);
        return GetField<X_Profile_Class>(n).exists ? true : false;
    }

    void Profile_clear()
    {
        const size_t n = offsetof(Self, Profile);
        GetField<X_Profile_Class>(n).Clear();
    }

    //
    // X_ElementConformsToProfile_Class.Element
    //

    const Field<X_ManagedElement_Class>& Element() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<X_ManagedElement_Class>(n);
    }

    void Element(const Field<X_ManagedElement_Class>& x)
    {
        const size_t n = offsetof(Self, Element);
        GetField<X_ManagedElement_Class>(n) = x;
    }

    const X_ManagedElement_Class& Element_value() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<X_ManagedElement_Class>(n).value;
    }

    void Element_value(const X_ManagedElement_Class& x)
    {
        const size_t n = offsetof(Self, Element);
        GetField<X_ManagedElement_Class>(n).Set(x);
    }

    bool Element_exists() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<X_ManagedElement_Class>(n).exists ? true : false;
    }

    void Element_clear()
    {
        const size_t n = offsetof(Self, Element);
        GetField<X_ManagedElement_Class>(n).Clear();
    }
};

typedef Array<X_ElementConformsToProfile_Class> X_ElementConformsToProfile_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_ElementConformsToProfile_h */
