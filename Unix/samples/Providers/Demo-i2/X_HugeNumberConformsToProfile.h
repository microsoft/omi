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
#ifndef _X_HugeNumberConformsToProfile_h
#define _X_HugeNumberConformsToProfile_h

#include <MI.h>
#include "X_ElementConformsToProfile.h"
#include "X_Profile.h"
#include "X_HugeNumber.h"

/*
**==============================================================================
**
** X_HugeNumberConformsToProfile [X_HugeNumberConformsToProfile]
**
** Keys:
**    Profile
**    Element
**
**==============================================================================
*/

typedef struct _X_HugeNumberConformsToProfile /* extends X_ElementConformsToProfile */
{
    MI_Instance __instance;
    /* X_ElementConformsToProfile properties */
    /*KEY*/ X_Profile_ConstRef Profile;
    /*KEY*/ X_HugeNumber_ConstRef Element;
    /* X_HugeNumberConformsToProfile properties */
}
X_HugeNumberConformsToProfile;

typedef struct _X_HugeNumberConformsToProfile_Ref
{
    X_HugeNumberConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumberConformsToProfile_Ref;

typedef struct _X_HugeNumberConformsToProfile_ConstRef
{
    MI_CONST X_HugeNumberConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumberConformsToProfile_ConstRef;

typedef struct _X_HugeNumberConformsToProfile_Array
{
    struct _X_HugeNumberConformsToProfile** data;
    MI_Uint32 size;
}
X_HugeNumberConformsToProfile_Array;

typedef struct _X_HugeNumberConformsToProfile_ConstArray
{
    struct _X_HugeNumberConformsToProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_HugeNumberConformsToProfile_ConstArray;

typedef struct _X_HugeNumberConformsToProfile_ArrayRef
{
    X_HugeNumberConformsToProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumberConformsToProfile_ArrayRef;

typedef struct _X_HugeNumberConformsToProfile_ConstArrayRef
{
    X_HugeNumberConformsToProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumberConformsToProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_HugeNumberConformsToProfile_rtti;

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Construct(
    X_HugeNumberConformsToProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_HugeNumberConformsToProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Clone(
    const X_HugeNumberConformsToProfile* self,
    X_HugeNumberConformsToProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_HugeNumberConformsToProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_HugeNumberConformsToProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Destruct(X_HugeNumberConformsToProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Delete(X_HugeNumberConformsToProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Post(
    const X_HugeNumberConformsToProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Set_Profile(
    X_HugeNumberConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_SetPtr_Profile(
    X_HugeNumberConformsToProfile* self,
    const X_Profile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Clear_Profile(
    X_HugeNumberConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Set_Element(
    X_HugeNumberConformsToProfile* self,
    const X_HugeNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_SetPtr_Element(
    X_HugeNumberConformsToProfile* self,
    const X_HugeNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumberConformsToProfile_Clear_Element(
    X_HugeNumberConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_HugeNumberConformsToProfile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_HugeNumberConformsToProfile_Self X_HugeNumberConformsToProfile_Self;

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_Load(
    X_HugeNumberConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_Unload(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_EnumerateInstances(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_GetInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_CreateInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* newInstance);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_ModifyInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_DeleteInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* instanceName);

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_AssociatorInstances(
    X_HugeNumberConformsToProfile_Self* self,
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

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_ReferenceInstances(
    X_HugeNumberConformsToProfile_Self* self,
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
** X_HugeNumberConformsToProfile_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_HugeNumberConformsToProfile_Class : public X_ElementConformsToProfile_Class
{
public:
    
    typedef X_HugeNumberConformsToProfile Self;
    
    X_HugeNumberConformsToProfile_Class() :
        X_ElementConformsToProfile_Class(&X_HugeNumberConformsToProfile_rtti)
    {
    }
    
    X_HugeNumberConformsToProfile_Class(
        const X_HugeNumberConformsToProfile* instanceName,
        bool keysOnly) :
        X_ElementConformsToProfile_Class(
            &X_HugeNumberConformsToProfile_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HugeNumberConformsToProfile_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_ElementConformsToProfile_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_HugeNumberConformsToProfile_Class(
        const MI_ClassDecl* clDecl) :
        X_ElementConformsToProfile_Class(clDecl)
    {
    }
    
    X_HugeNumberConformsToProfile_Class& operator=(
        const X_HugeNumberConformsToProfile_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HugeNumberConformsToProfile_Class(
        const X_HugeNumberConformsToProfile_Class& x) :
        X_ElementConformsToProfile_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_HugeNumberConformsToProfile_rtti;
    }

};

typedef Array<X_HugeNumberConformsToProfile_Class> X_HugeNumberConformsToProfile_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_HugeNumberConformsToProfile_h */
