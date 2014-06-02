/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_HTTPHeader_h
#define _X_HTTPHeader_h

#include <MI.h>

/*
**==============================================================================
**
** X_HTTPHeader [X_HTTPHeader]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _X_HTTPHeader
{
    MI_Instance __instance;
    /* X_HTTPHeader properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstStringField Value;
}
X_HTTPHeader;

typedef struct _X_HTTPHeader_Ref
{
    X_HTTPHeader* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HTTPHeader_Ref;

typedef struct _X_HTTPHeader_ConstRef
{
    MI_CONST X_HTTPHeader* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HTTPHeader_ConstRef;

typedef struct _X_HTTPHeader_Array
{
    struct _X_HTTPHeader** data;
    MI_Uint32 size;
}
X_HTTPHeader_Array;

typedef struct _X_HTTPHeader_ConstArray
{
    struct _X_HTTPHeader MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_HTTPHeader_ConstArray;

typedef struct _X_HTTPHeader_ArrayRef
{
    X_HTTPHeader_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HTTPHeader_ArrayRef;

typedef struct _X_HTTPHeader_ConstArrayRef
{
    X_HTTPHeader_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HTTPHeader_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_HTTPHeader_rtti;

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Construct(
    X_HTTPHeader* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_HTTPHeader_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Clone(
    const X_HTTPHeader* self,
    X_HTTPHeader** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_HTTPHeader_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_HTTPHeader_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Destruct(X_HTTPHeader* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Delete(X_HTTPHeader* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Post(
    const X_HTTPHeader* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Set_Name(
    X_HTTPHeader* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_SetPtr_Name(
    X_HTTPHeader* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Clear_Name(
    X_HTTPHeader* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Set_Value(
    X_HTTPHeader* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_SetPtr_Value(
    X_HTTPHeader* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HTTPHeader_Clear_Value(
    X_HTTPHeader* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** X_HTTPHeader provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_HTTPHeader_Self X_HTTPHeader_Self;

MI_EXTERN_C void MI_CALL X_HTTPHeader_Load(
    X_HTTPHeader_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HTTPHeader_Unload(
    X_HTTPHeader_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HTTPHeader_EnumerateInstances(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_HTTPHeader_GetInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HTTPHeader_CreateInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* newInstance);

MI_EXTERN_C void MI_CALL X_HTTPHeader_ModifyInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HTTPHeader_DeleteInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* instanceName);


/*
**==============================================================================
**
** X_HTTPHeader_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_HTTPHeader_Class : public Instance
{
public:
    
    typedef X_HTTPHeader Self;
    
    X_HTTPHeader_Class() :
        Instance(&X_HTTPHeader_rtti)
    {
    }
    
    X_HTTPHeader_Class(
        const X_HTTPHeader* instanceName,
        bool keysOnly) :
        Instance(
            &X_HTTPHeader_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HTTPHeader_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_HTTPHeader_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_HTTPHeader_Class& operator=(
        const X_HTTPHeader_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HTTPHeader_Class(
        const X_HTTPHeader_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_HTTPHeader_rtti;
    }

    //
    // X_HTTPHeader_Class.Name
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
    // X_HTTPHeader_Class.Value
    //
    
    const Field<String>& Value() const
    {
        const size_t n = offsetof(Self, Value);
        return GetField<String>(n);
    }
    
    void Value(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Value);
        GetField<String>(n) = x;
    }
    
    const String& Value_value() const
    {
        const size_t n = offsetof(Self, Value);
        return GetField<String>(n).value;
    }
    
    void Value_value(const String& x)
    {
        const size_t n = offsetof(Self, Value);
        GetField<String>(n).Set(x);
    }
    
    bool Value_exists() const
    {
        const size_t n = offsetof(Self, Value);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Value_clear()
    {
        const size_t n = offsetof(Self, Value);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_HTTPHeader_Class> X_HTTPHeader_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_HTTPHeader_h */
