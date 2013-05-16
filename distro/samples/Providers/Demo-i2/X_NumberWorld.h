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
#ifndef _X_NumberWorld_h
#define _X_NumberWorld_h

#include <MI.h>
#include "X_ManagedElement.h"

/*
**==============================================================================
**
** X_NumberWorld [X_NumberWorld]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _X_NumberWorld /* extends X_ManagedElement */
{
    MI_Instance __instance;
    /* X_ManagedElement properties */
    MI_ConstStringField Description;
    /* X_NumberWorld properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Version;
    MI_ConstUint32Field pid;
    MI_ConstUint32Field uid;
    MI_ConstUint32Field gid;
    MI_ConstStringField user;
    MI_ConstStringField group;
    MI_ConstStringField ns;
}
X_NumberWorld;

typedef struct _X_NumberWorld_Ref
{
    X_NumberWorld* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorld_Ref;

typedef struct _X_NumberWorld_ConstRef
{
    MI_CONST X_NumberWorld* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorld_ConstRef;

typedef struct _X_NumberWorld_Array
{
    struct _X_NumberWorld** data;
    MI_Uint32 size;
}
X_NumberWorld_Array;

typedef struct _X_NumberWorld_ConstArray
{
    struct _X_NumberWorld MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_NumberWorld_ConstArray;

typedef struct _X_NumberWorld_ArrayRef
{
    X_NumberWorld_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorld_ArrayRef;

typedef struct _X_NumberWorld_ConstArrayRef
{
    X_NumberWorld_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_NumberWorld_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_NumberWorld_rtti;

MI_INLINE MI_Result MI_CALL X_NumberWorld_Construct(
    X_NumberWorld* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_NumberWorld_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clone(
    const X_NumberWorld* self,
    X_NumberWorld** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_NumberWorld_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_NumberWorld_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Destruct(X_NumberWorld* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Delete(X_NumberWorld* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Post(
    const X_NumberWorld* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_Description(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_Description(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_Description(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_Name(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_Name(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_Name(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_Version(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_Version(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_Version(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_pid(
    X_NumberWorld* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->pid)->value = x;
    ((MI_Uint32Field*)&self->pid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_pid(
    X_NumberWorld* self)
{
    memset((void*)&self->pid, 0, sizeof(self->pid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_uid(
    X_NumberWorld* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uid)->value = x;
    ((MI_Uint32Field*)&self->uid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_uid(
    X_NumberWorld* self)
{
    memset((void*)&self->uid, 0, sizeof(self->uid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_gid(
    X_NumberWorld* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->gid)->value = x;
    ((MI_Uint32Field*)&self->gid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_gid(
    X_NumberWorld* self)
{
    memset((void*)&self->gid, 0, sizeof(self->gid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_user(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_user(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_user(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_group(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_group(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_group(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Set_ns(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_SetPtr_ns(
    X_NumberWorld* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Clear_ns(
    X_NumberWorld* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** X_NumberWorld.Terminate()
**
**==============================================================================
*/

typedef struct _X_NumberWorld_Terminate
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
X_NumberWorld_Terminate;

MI_EXTERN_C MI_CONST MI_MethodDecl X_NumberWorld_Terminate_rtti;

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Construct(
    X_NumberWorld_Terminate* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_NumberWorld_Terminate_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Clone(
    const X_NumberWorld_Terminate* self,
    X_NumberWorld_Terminate** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Destruct(
    X_NumberWorld_Terminate* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Delete(
    X_NumberWorld_Terminate* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Post(
    const X_NumberWorld_Terminate* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Set_MIReturn(
    X_NumberWorld_Terminate* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_Terminate_Clear_MIReturn(
    X_NumberWorld_Terminate* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_NumberWorld.ReturnNamespace()
**
**==============================================================================
*/

typedef struct _X_NumberWorld_ReturnNamespace
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
X_NumberWorld_ReturnNamespace;

MI_EXTERN_C MI_CONST MI_MethodDecl X_NumberWorld_ReturnNamespace_rtti;

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Construct(
    X_NumberWorld_ReturnNamespace* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_NumberWorld_ReturnNamespace_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Clone(
    const X_NumberWorld_ReturnNamespace* self,
    X_NumberWorld_ReturnNamespace** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Destruct(
    X_NumberWorld_ReturnNamespace* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Delete(
    X_NumberWorld_ReturnNamespace* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Post(
    const X_NumberWorld_ReturnNamespace* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Set_MIReturn(
    X_NumberWorld_ReturnNamespace* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_SetPtr_MIReturn(
    X_NumberWorld_ReturnNamespace* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_NumberWorld_ReturnNamespace_Clear_MIReturn(
    X_NumberWorld_ReturnNamespace* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** X_NumberWorld provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_NumberWorld_Self X_NumberWorld_Self;

MI_EXTERN_C void MI_CALL X_NumberWorld_Load(
    X_NumberWorld_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_NumberWorld_Unload(
    X_NumberWorld_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_NumberWorld_EnumerateInstances(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_NumberWorld_GetInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_NumberWorld_CreateInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* newInstance);

MI_EXTERN_C void MI_CALL X_NumberWorld_ModifyInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_NumberWorld_DeleteInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* instanceName);

MI_EXTERN_C void MI_CALL X_NumberWorld_Invoke_Terminate(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_NumberWorld* instanceName,
    const X_NumberWorld_Terminate* in);

MI_EXTERN_C void MI_CALL X_NumberWorld_Invoke_ReturnNamespace(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_NumberWorld* instanceName,
    const X_NumberWorld_ReturnNamespace* in);


/*
**==============================================================================
**
** X_NumberWorld_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_NumberWorld_Class : public X_ManagedElement_Class
{
public:

    typedef X_NumberWorld Self;

    X_NumberWorld_Class() :
        X_ManagedElement_Class(&X_NumberWorld_rtti)
    {
    }

    X_NumberWorld_Class(
        const X_NumberWorld* instanceName,
        bool keysOnly) :
        X_ManagedElement_Class(
            &X_NumberWorld_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_NumberWorld_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_ManagedElement_Class(clDecl, instance, keysOnly)
    {
    }

    X_NumberWorld_Class(
        const MI_ClassDecl* clDecl) :
        X_ManagedElement_Class(clDecl)
    {
    }

    X_NumberWorld_Class& operator=(
        const X_NumberWorld_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_NumberWorld_Class(
        const X_NumberWorld_Class& x) :
        X_ManagedElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_NumberWorld_rtti;
    }

    //
    // X_NumberWorld_Class.Name
    //

    const Field<String>& Name() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n);
    }

    void Name(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n) = x;
    }

    const String& Name_value() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).value;
    }

    void Name_value(const String& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Set(x);
    }

    bool Name_exists() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).exists ? true : false;
    }

    void Name_clear()
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Clear();
    }

    //
    // X_NumberWorld_Class.Version
    //

    const Field<String>& Version() const
    {
        const size_t n = offsetof(Self, Version);
        return GetField<String>(n);
    }

    void Version(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Version);
        GetField<String>(n) = x;
    }

    const String& Version_value() const
    {
        const size_t n = offsetof(Self, Version);
        return GetField<String>(n).value;
    }

    void Version_value(const String& x)
    {
        const size_t n = offsetof(Self, Version);
        GetField<String>(n).Set(x);
    }

    bool Version_exists() const
    {
        const size_t n = offsetof(Self, Version);
        return GetField<String>(n).exists ? true : false;
    }

    void Version_clear()
    {
        const size_t n = offsetof(Self, Version);
        GetField<String>(n).Clear();
    }

    //
    // X_NumberWorld_Class.pid
    //

    const Field<Uint32>& pid() const
    {
        const size_t n = offsetof(Self, pid);
        return GetField<Uint32>(n);
    }

    void pid(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, pid);
        GetField<Uint32>(n) = x;
    }

    const Uint32& pid_value() const
    {
        const size_t n = offsetof(Self, pid);
        return GetField<Uint32>(n).value;
    }

    void pid_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, pid);
        GetField<Uint32>(n).Set(x);
    }

    bool pid_exists() const
    {
        const size_t n = offsetof(Self, pid);
        return GetField<Uint32>(n).exists ? true : false;
    }

    void pid_clear()
    {
        const size_t n = offsetof(Self, pid);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_NumberWorld_Class.uid
    //

    const Field<Uint32>& uid() const
    {
        const size_t n = offsetof(Self, uid);
        return GetField<Uint32>(n);
    }

    void uid(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, uid);
        GetField<Uint32>(n) = x;
    }

    const Uint32& uid_value() const
    {
        const size_t n = offsetof(Self, uid);
        return GetField<Uint32>(n).value;
    }

    void uid_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, uid);
        GetField<Uint32>(n).Set(x);
    }

    bool uid_exists() const
    {
        const size_t n = offsetof(Self, uid);
        return GetField<Uint32>(n).exists ? true : false;
    }

    void uid_clear()
    {
        const size_t n = offsetof(Self, uid);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_NumberWorld_Class.gid
    //

    const Field<Uint32>& gid() const
    {
        const size_t n = offsetof(Self, gid);
        return GetField<Uint32>(n);
    }

    void gid(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, gid);
        GetField<Uint32>(n) = x;
    }

    const Uint32& gid_value() const
    {
        const size_t n = offsetof(Self, gid);
        return GetField<Uint32>(n).value;
    }

    void gid_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, gid);
        GetField<Uint32>(n).Set(x);
    }

    bool gid_exists() const
    {
        const size_t n = offsetof(Self, gid);
        return GetField<Uint32>(n).exists ? true : false;
    }

    void gid_clear()
    {
        const size_t n = offsetof(Self, gid);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_NumberWorld_Class.user
    //

    const Field<String>& user() const
    {
        const size_t n = offsetof(Self, user);
        return GetField<String>(n);
    }

    void user(const Field<String>& x)
    {
        const size_t n = offsetof(Self, user);
        GetField<String>(n) = x;
    }

    const String& user_value() const
    {
        const size_t n = offsetof(Self, user);
        return GetField<String>(n).value;
    }

    void user_value(const String& x)
    {
        const size_t n = offsetof(Self, user);
        GetField<String>(n).Set(x);
    }

    bool user_exists() const
    {
        const size_t n = offsetof(Self, user);
        return GetField<String>(n).exists ? true : false;
    }

    void user_clear()
    {
        const size_t n = offsetof(Self, user);
        GetField<String>(n).Clear();
    }

    //
    // X_NumberWorld_Class.group
    //

    const Field<String>& group() const
    {
        const size_t n = offsetof(Self, group);
        return GetField<String>(n);
    }

    void group(const Field<String>& x)
    {
        const size_t n = offsetof(Self, group);
        GetField<String>(n) = x;
    }

    const String& group_value() const
    {
        const size_t n = offsetof(Self, group);
        return GetField<String>(n).value;
    }

    void group_value(const String& x)
    {
        const size_t n = offsetof(Self, group);
        GetField<String>(n).Set(x);
    }

    bool group_exists() const
    {
        const size_t n = offsetof(Self, group);
        return GetField<String>(n).exists ? true : false;
    }

    void group_clear()
    {
        const size_t n = offsetof(Self, group);
        GetField<String>(n).Clear();
    }

    //
    // X_NumberWorld_Class.ns
    //

    const Field<String>& ns() const
    {
        const size_t n = offsetof(Self, ns);
        return GetField<String>(n);
    }

    void ns(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ns);
        GetField<String>(n) = x;
    }

    const String& ns_value() const
    {
        const size_t n = offsetof(Self, ns);
        return GetField<String>(n).value;
    }

    void ns_value(const String& x)
    {
        const size_t n = offsetof(Self, ns);
        GetField<String>(n).Set(x);
    }

    bool ns_exists() const
    {
        const size_t n = offsetof(Self, ns);
        return GetField<String>(n).exists ? true : false;
    }

    void ns_clear()
    {
        const size_t n = offsetof(Self, ns);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_NumberWorld_Class> X_NumberWorld_ClassA;

class X_NumberWorld_Terminate_Class : public Instance
{
public:

    typedef X_NumberWorld_Terminate Self;

    X_NumberWorld_Terminate_Class() :
        Instance(&X_NumberWorld_Terminate_rtti)
    {
    }

    X_NumberWorld_Terminate_Class(
        const X_NumberWorld_Terminate* instanceName,
        bool keysOnly) :
        Instance(
            &X_NumberWorld_Terminate_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_NumberWorld_Terminate_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_NumberWorld_Terminate_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_NumberWorld_Terminate_Class& operator=(
        const X_NumberWorld_Terminate_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_NumberWorld_Terminate_Class(
        const X_NumberWorld_Terminate_Class& x) :
        Instance(x)
    {
    }

    //
    // X_NumberWorld_Terminate_Class.MIReturn
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
};

typedef Array<X_NumberWorld_Terminate_Class> X_NumberWorld_Terminate_ClassA;

class X_NumberWorld_ReturnNamespace_Class : public Instance
{
public:

    typedef X_NumberWorld_ReturnNamespace Self;

    X_NumberWorld_ReturnNamespace_Class() :
        Instance(&X_NumberWorld_ReturnNamespace_rtti)
    {
    }

    X_NumberWorld_ReturnNamespace_Class(
        const X_NumberWorld_ReturnNamespace* instanceName,
        bool keysOnly) :
        Instance(
            &X_NumberWorld_ReturnNamespace_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }

    X_NumberWorld_ReturnNamespace_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }

    X_NumberWorld_ReturnNamespace_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }

    X_NumberWorld_ReturnNamespace_Class& operator=(
        const X_NumberWorld_ReturnNamespace_Class& x)
    {
        CopyRef(x);
        return *this;
    }

    X_NumberWorld_ReturnNamespace_Class(
        const X_NumberWorld_ReturnNamespace_Class& x) :
        Instance(x)
    {
    }

    //
    // X_NumberWorld_ReturnNamespace_Class.MIReturn
    //

    const Field<String>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n);
    }

    void MIReturn(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n) = x;
    }

    const String& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).value;
    }

    void MIReturn_value(const String& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Set(x);
    }

    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).exists ? true : false;
    }

    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_NumberWorld_ReturnNamespace_Class> X_NumberWorld_ReturnNamespace_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_NumberWorld_h */
