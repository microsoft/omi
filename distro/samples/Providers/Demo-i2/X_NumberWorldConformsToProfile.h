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
#ifndef _X_NumberWorldConformsToProfile_h
#define _X_NumberWorldConformsToProfile_h

#include <MI.h>
#include "X_ElementConformsToProfile.h"
#include "X_Profile.h"
#include "X_NumberWorld.h"

/*
**==============================================================================
**
** X_NumberWorldConformsToProfile [X_NumberWorldConformsToProfile]
**
** Keys:
**    Profile
**    Element
**
**==============================================================================
*/

typedef struct _X_NumberWorldConformsToProfile /* extends X_ElementConformsToProfile */
{
    MI_Instance __instance;
    /* X_ElementConformsToProfile properties */
    /*KEY*/ X_Profile_ConstRef Profile;
    /*KEY*/ X_NumberWorld_ConstRef Element;
    /* X_NumberWorldConformsToProfile properties */
}
X_NumberWorldConformsToProfile;

typedef struct _X_NumberWorldConformsToProfile_Ref
{
    X_NumberWorldConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorldConformsToProfile_Ref;

typedef struct _X_NumberWorldConformsToProfile_ConstRef
{
    MI_CONST X_NumberWorldConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorldConformsToProfile_ConstRef;

typedef struct _X_NumberWorldConformsToProfile_Array
{
    struct _X_NumberWorldConformsToProfile** data;
    MI_Uint32 size;
}
X_NumberWorldConformsToProfile_Array;

typedef struct _X_NumberWorldConformsToProfile_ConstArray
{
    struct _X_NumberWorldConformsToProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_NumberWorldConformsToProfile_ConstArray;

typedef struct _X_NumberWorldConformsToProfile_ArrayRef
{
    X_NumberWorldConformsToProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorldConformsToProfile_ArrayRef;

typedef struct _X_NumberWorldConformsToProfile_ConstArrayRef
{
    X_NumberWorldConformsToProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorldConformsToProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_NumberWorldConformsToProfile_rtti;

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Construct(
    X_NumberWorldConformsToProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_NumberWorldConformsToProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Clone(
    const X_NumberWorldConformsToProfile* self,
    X_NumberWorldConformsToProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_NumberWorldConformsToProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_NumberWorldConformsToProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Destruct(X_NumberWorldConformsToProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Delete(X_NumberWorldConformsToProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Post(
    const X_NumberWorldConformsToProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Set_Profile(
    X_NumberWorldConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_SetPtr_Profile(
    X_NumberWorldConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Clear_Profile(
    X_NumberWorldConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Set_Element(
    X_NumberWorldConformsToProfile* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_SetPtr_Element(
    X_NumberWorldConformsToProfile* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorldConformsToProfile_Clear_Element(
    X_NumberWorldConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_NumberWorldConformsToProfile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_NumberWorldConformsToProfile_Self X_NumberWorldConformsToProfile_Self;

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_Load(
    X_NumberWorldConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_Unload(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_EnumerateInstances(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_GetInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_CreateInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* newInstance);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_ModifyInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_DeleteInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* instanceName);

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_AssociatorInstances(
    X_NumberWorldConformsToProfile_Self* self,
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

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_ReferenceInstances(
    X_NumberWorldConformsToProfile_Self* self,
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
** X_NumberWorldConformsToProfile_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_NumberWorldConformsToProfile_Class : public X_ElementConformsToProfile_Class
{
public:

    typedef X_NumberWorldConformsToProfile Self;

    X_NumberWorldConformsToProfile_Class() :
        X_ElementConformsToProfile_Class(&X_NumberWorldConformsToProfile_rtti)
    {
    }

    X_NumberWorldConformsToProfile_Class(
        const X_NumberWorldConformsToProfile* instanceName,
        bool keysOnly) :
        X_ElementConformsToProfile_Class(
            &X_NumberWorldConformsToProfile_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_NumberWorldConformsToProfile_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_ElementConformsToProfile_Class(clDecl, instance, keysOnly)
    {
    }

    X_NumberWorldConformsToProfile_Class(
        const MI_ClassDecl* clDecl) :
        X_ElementConformsToProfile_Class(clDecl)
    {
    }

    X_NumberWorldConformsToProfile_Class& operator=(
        const X_NumberWorldConformsToProfile_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_NumberWorldConformsToProfile_Class(
        const X_NumberWorldConformsToProfile_Class& x) :
        X_ElementConformsToProfile_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_NumberWorldConformsToProfile_rtti;
    }

};

typedef Array<X_NumberWorldConformsToProfile_Class> X_NumberWorldConformsToProfile_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_NumberWorldConformsToProfile_h */
