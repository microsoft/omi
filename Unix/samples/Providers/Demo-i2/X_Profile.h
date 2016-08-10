/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_Profile_h
#define _X_Profile_h

#include <MI.h>

/*
**==============================================================================
**
** X_Profile [X_Profile]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _X_Profile
{
    MI_Instance __instance;
    /* X_Profile properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField RegisteredName;
}
X_Profile;

typedef struct _X_Profile_Ref
{
    X_Profile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Profile_Ref;

typedef struct _X_Profile_ConstRef
{
    MI_CONST X_Profile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Profile_ConstRef;

typedef struct _X_Profile_Array
{
    struct _X_Profile** data;
    MI_Uint32 size;
}
X_Profile_Array;

typedef struct _X_Profile_ConstArray
{
    struct _X_Profile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Profile_ConstArray;

typedef struct _X_Profile_ArrayRef
{
    X_Profile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Profile_ArrayRef;

typedef struct _X_Profile_ConstArrayRef
{
    X_Profile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Profile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Profile_rtti;

MI_INLINE MI_Result MI_CALL X_Profile_Construct(
    X_Profile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Profile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Profile_Clone(
    const X_Profile* self,
    X_Profile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Profile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Profile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Profile_Destruct(X_Profile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Profile_Delete(X_Profile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Profile_Post(
    const X_Profile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Profile_Set_InstanceID(
    X_Profile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Profile_SetPtr_InstanceID(
    X_Profile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Profile_Clear_InstanceID(
    X_Profile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_Profile_Set_RegisteredName(
    X_Profile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Profile_SetPtr_RegisteredName(
    X_Profile* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Profile_Clear_RegisteredName(
    X_Profile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_Profile provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_Profile_Self X_Profile_Self;

MI_EXTERN_C void MI_CALL X_Profile_Load(
    X_Profile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Profile_Unload(
    X_Profile_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Profile_EnumerateInstances(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_Profile_GetInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Profile_CreateInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* newInstance);

MI_EXTERN_C void MI_CALL X_Profile_ModifyInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Profile_DeleteInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* instanceName);


/*
**==============================================================================
**
** X_Profile_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Profile_Class : public Instance
{
public:
    
    typedef X_Profile Self;
    
    X_Profile_Class() :
        Instance(&X_Profile_rtti)
    {
    }
    
    X_Profile_Class(
        const X_Profile* instanceName,
        bool keysOnly) :
        Instance(
            &X_Profile_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Profile_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_Profile_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_Profile_Class& operator=(
        const X_Profile_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Profile_Class(
        const X_Profile_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Profile_rtti;
    }

    //
    // X_Profile_Class.InstanceID
    //
    
    const Field<String>& InstanceID() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n);
    }
    
    void InstanceID(const Field<String>& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n) = x;
    }
    
    const String& InstanceID_value() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).value;
    }
    
    void InstanceID_value(const String& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Set(x);
    }
    
    bool InstanceID_exists() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).exists ? true : false;
    }
    
    void InstanceID_clear()
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Clear();
    }

    //
    // X_Profile_Class.RegisteredName
    //
    
    const Field<String>& RegisteredName() const
    {
        const size_t n = offsetof(Self, RegisteredName);
        return GetField<String>(n);
    }
    
    void RegisteredName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, RegisteredName);
        GetField<String>(n) = x;
    }
    
    const String& RegisteredName_value() const
    {
        const size_t n = offsetof(Self, RegisteredName);
        return GetField<String>(n).value;
    }
    
    void RegisteredName_value(const String& x)
    {
        const size_t n = offsetof(Self, RegisteredName);
        GetField<String>(n).Set(x);
    }
    
    bool RegisteredName_exists() const
    {
        const size_t n = offsetof(Self, RegisteredName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void RegisteredName_clear()
    {
        const size_t n = offsetof(Self, RegisteredName);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_Profile_Class> X_Profile_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Profile_h */
