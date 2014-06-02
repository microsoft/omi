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
#ifndef _X_HugeNumbers_h
#define _X_HugeNumbers_h

#include <MI.h>
#include "X_AllNumbers.h"
#include "X_HugeNumber.h"
#include "X_NumberWorld.h"

/*
**==============================================================================
**
** X_HugeNumbers [X_HugeNumbers]
**
** Keys:
**    number
**    world
**
**==============================================================================
*/

typedef struct _X_HugeNumbers /* extends X_AllNumbers */
{
    MI_Instance __instance;
    /* X_AllNumbers properties */
    /*KEY*/ X_HugeNumber_ConstRef number;
    /*KEY*/ X_NumberWorld_ConstRef world;
    /* X_HugeNumbers properties */
}
X_HugeNumbers;

typedef struct _X_HugeNumbers_Ref
{
    X_HugeNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumbers_Ref;

typedef struct _X_HugeNumbers_ConstRef
{
    MI_CONST X_HugeNumbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumbers_ConstRef;

typedef struct _X_HugeNumbers_Array
{
    struct _X_HugeNumbers** data;
    MI_Uint32 size;
}
X_HugeNumbers_Array;

typedef struct _X_HugeNumbers_ConstArray
{
    struct _X_HugeNumbers MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_HugeNumbers_ConstArray;

typedef struct _X_HugeNumbers_ArrayRef
{
    X_HugeNumbers_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumbers_ArrayRef;

typedef struct _X_HugeNumbers_ConstArrayRef
{
    X_HugeNumbers_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumbers_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_HugeNumbers_rtti;

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Construct(
    X_HugeNumbers* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_HugeNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Clone(
    const X_HugeNumbers* self,
    X_HugeNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_HugeNumbers_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_HugeNumbers_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Destruct(X_HugeNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Delete(X_HugeNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Post(
    const X_HugeNumbers* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Set_number(
    X_HugeNumbers* self,
    const X_HugeNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_SetPtr_number(
    X_HugeNumbers* self,
    const X_HugeNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Clear_number(
    X_HugeNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Set_world(
    X_HugeNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_SetPtr_world(
    X_HugeNumbers* self,
    const X_NumberWorld* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumbers_Clear_world(
    X_HugeNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_HugeNumbers provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_HugeNumbers_Self X_HugeNumbers_Self;

MI_EXTERN_C void MI_CALL X_HugeNumbers_Load(
    X_HugeNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumbers_Unload(
    X_HugeNumbers_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumbers_EnumerateInstances(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_HugeNumbers_GetInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumbers_CreateInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* newInstance);

MI_EXTERN_C void MI_CALL X_HugeNumbers_ModifyInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumbers_DeleteInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* instanceName);

MI_EXTERN_C void MI_CALL X_HugeNumbers_AssociatorInstances(
    X_HugeNumbers_Self* self,
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

MI_EXTERN_C void MI_CALL X_HugeNumbers_ReferenceInstances(
    X_HugeNumbers_Self* self,
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
** X_HugeNumbers_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_HugeNumbers_Class : public X_AllNumbers_Class
{
public:
    
    typedef X_HugeNumbers Self;
    
    X_HugeNumbers_Class() :
        X_AllNumbers_Class(&X_HugeNumbers_rtti)
    {
    }
    
    X_HugeNumbers_Class(
        const X_HugeNumbers* instanceName,
        bool keysOnly) :
        X_AllNumbers_Class(
            &X_HugeNumbers_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HugeNumbers_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_AllNumbers_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_HugeNumbers_Class(
        const MI_ClassDecl* clDecl) :
        X_AllNumbers_Class(clDecl)
    {
    }
    
    X_HugeNumbers_Class& operator=(
        const X_HugeNumbers_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HugeNumbers_Class(
        const X_HugeNumbers_Class& x) :
        X_AllNumbers_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_HugeNumbers_rtti;
    }

};

typedef Array<X_HugeNumbers_Class> X_HugeNumbers_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_HugeNumbers_h */
