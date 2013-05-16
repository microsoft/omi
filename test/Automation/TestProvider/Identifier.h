/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Identifier_h
#define _Identifier_h

#include <MI.h>

/*
**==============================================================================
**
** Identifier [Demo_Identifier]
**
** Keys:
**    NameSpace
**    ClassName
**    MethodName
**    pid
**    uid
**    gid
**    user
**    group
**
**==============================================================================
*/

typedef struct _Identifier
{
    MI_Instance __instance;
    /* Identifier properties */
    /*KEY*/ MI_ConstStringField NameSpace;
    /*KEY*/ MI_ConstStringField ClassName;
    /*KEY*/ MI_ConstStringField MethodName;
    /*KEY*/ MI_ConstUint32Field pid;
    /*KEY*/ MI_ConstUint32Field uid;
    /*KEY*/ MI_ConstUint32Field gid;
    /*KEY*/ MI_ConstStringField user;
    /*KEY*/ MI_ConstStringField group;
}
Identifier;

typedef struct _Identifier_Ref
{
    Identifier* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identifier_Ref;

typedef struct _Identifier_ConstRef
{
    MI_CONST Identifier* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identifier_ConstRef;

typedef struct _Identifier_Array
{
    struct _Identifier** data;
    MI_Uint32 size;
}
Identifier_Array;

typedef struct _Identifier_ConstArray
{
    struct _Identifier MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Identifier_ConstArray;

typedef struct _Identifier_ArrayRef
{
    Identifier_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identifier_ArrayRef;

typedef struct _Identifier_ConstArrayRef
{
    Identifier_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Identifier_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Identifier_rtti;

MI_INLINE MI_Result MI_CALL Identifier_Construct(
    Identifier* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Identifier_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identifier_Clone(
    const Identifier* self,
    Identifier** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Identifier_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Identifier_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Identifier_Destruct(Identifier* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identifier_Delete(Identifier* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Identifier_Post(
    const Identifier* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Identifier_Set_NameSpace(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_SetPtr_NameSpace(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_NameSpace(
    Identifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_Set_ClassName(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_SetPtr_ClassName(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_ClassName(
    Identifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Identifier_Set_MethodName(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_SetPtr_MethodName(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_MethodName(
    Identifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Identifier_Set_pid(
    Identifier* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->pid)->value = x;
    ((MI_Uint32Field*)&self->pid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_pid(
    Identifier* self)
{
    memset((void*)&self->pid, 0, sizeof(self->pid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Set_uid(
    Identifier* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uid)->value = x;
    ((MI_Uint32Field*)&self->uid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_uid(
    Identifier* self)
{
    memset((void*)&self->uid, 0, sizeof(self->uid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Set_gid(
    Identifier* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->gid)->value = x;
    ((MI_Uint32Field*)&self->gid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_gid(
    Identifier* self)
{
    memset((void*)&self->gid, 0, sizeof(self->gid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Identifier_Set_user(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_SetPtr_user(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_user(
    Identifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL Identifier_Set_group(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Identifier_SetPtr_group(
    Identifier* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Identifier_Clear_group(
    Identifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** Identifier provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Identifier_Self Identifier_Self;

MI_EXTERN_C void MI_CALL Identifier_Load(
    Identifier_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Identifier_Unload(
    Identifier_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Identifier_EnumerateInstances(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Identifier_GetInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Identifier_CreateInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* newInstance);

MI_EXTERN_C void MI_CALL Identifier_ModifyInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Identifier_DeleteInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName);


/*
**==============================================================================
**
** Identifier_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Identifier_Class : public Instance
{
public:
    
    typedef Identifier Self;
    
    Identifier_Class() :
        Instance(&Identifier_rtti)
    {
    }
    
    Identifier_Class(
        const Identifier* instanceName,
        bool keysOnly) :
        Instance(
            &Identifier_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Identifier_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Identifier_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Identifier_Class& operator=(
        const Identifier_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Identifier_Class(
        const Identifier_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Identifier_rtti;
    }

    //
    // Identifier_Class.NameSpace
    //
    
    const Field<String>& NameSpace() const
    {
        const size_t n = offsetof(Self, NameSpace);
        return GetField<String>(n);
    }
    
    void NameSpace(const Field<String>& x)
    {
        const size_t n = offsetof(Self, NameSpace);
        GetField<String>(n) = x;
    }
    
    const String& NameSpace_value() const
    {
        const size_t n = offsetof(Self, NameSpace);
        return GetField<String>(n).value;
    }
    
    void NameSpace_value(const String& x)
    {
        const size_t n = offsetof(Self, NameSpace);
        GetField<String>(n).Set(x);
    }
    
    bool NameSpace_exists() const
    {
        const size_t n = offsetof(Self, NameSpace);
        return GetField<String>(n).exists ? true : false;
    }
    
    void NameSpace_clear()
    {
        const size_t n = offsetof(Self, NameSpace);
        GetField<String>(n).Clear();
    }

    //
    // Identifier_Class.ClassName
    //
    
    const Field<String>& ClassName() const
    {
        const size_t n = offsetof(Self, ClassName);
        return GetField<String>(n);
    }
    
    void ClassName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ClassName);
        GetField<String>(n) = x;
    }
    
    const String& ClassName_value() const
    {
        const size_t n = offsetof(Self, ClassName);
        return GetField<String>(n).value;
    }
    
    void ClassName_value(const String& x)
    {
        const size_t n = offsetof(Self, ClassName);
        GetField<String>(n).Set(x);
    }
    
    bool ClassName_exists() const
    {
        const size_t n = offsetof(Self, ClassName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ClassName_clear()
    {
        const size_t n = offsetof(Self, ClassName);
        GetField<String>(n).Clear();
    }

    //
    // Identifier_Class.MethodName
    //
    
    const Field<String>& MethodName() const
    {
        const size_t n = offsetof(Self, MethodName);
        return GetField<String>(n);
    }
    
    void MethodName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MethodName);
        GetField<String>(n) = x;
    }
    
    const String& MethodName_value() const
    {
        const size_t n = offsetof(Self, MethodName);
        return GetField<String>(n).value;
    }
    
    void MethodName_value(const String& x)
    {
        const size_t n = offsetof(Self, MethodName);
        GetField<String>(n).Set(x);
    }
    
    bool MethodName_exists() const
    {
        const size_t n = offsetof(Self, MethodName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MethodName_clear()
    {
        const size_t n = offsetof(Self, MethodName);
        GetField<String>(n).Clear();
    }

    //
    // Identifier_Class.pid
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
    // Identifier_Class.uid
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
    // Identifier_Class.gid
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
    // Identifier_Class.user
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
    // Identifier_Class.group
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
};

typedef Array<Identifier_Class> Identifier_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Identifier_h */
