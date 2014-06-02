/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_Cat_h
#define _X_Cat_h

#include <MI.h>

/*
**==============================================================================
**
** X_Cat [X_Cat]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _X_Cat
{
    MI_Instance __instance;
    /* X_Cat properties */
    /*KEY*/ MI_ConstStringField Key;
}
X_Cat;

typedef struct _X_Cat_Ref
{
    X_Cat* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Cat_Ref;

typedef struct _X_Cat_ConstRef
{
    MI_CONST X_Cat* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Cat_ConstRef;

typedef struct _X_Cat_Array
{
    struct _X_Cat** data;
    MI_Uint32 size;
}
X_Cat_Array;

typedef struct _X_Cat_ConstArray
{
    struct _X_Cat MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Cat_ConstArray;

typedef struct _X_Cat_ArrayRef
{
    X_Cat_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Cat_ArrayRef;

typedef struct _X_Cat_ConstArrayRef
{
    X_Cat_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Cat_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Cat_rtti;

MI_INLINE MI_Result MI_CALL X_Cat_Construct(
    X_Cat* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Cat_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Cat_Clone(
    const X_Cat* self,
    X_Cat** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Cat_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Cat_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Cat_Destruct(X_Cat* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Cat_Delete(X_Cat* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Cat_Post(
    const X_Cat* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Cat_Set_Key(
    X_Cat* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Cat_SetPtr_Key(
    X_Cat* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Cat_Clear_Key(
    X_Cat* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** X_Cat provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_Cat_Self X_Cat_Self;

MI_EXTERN_C void MI_CALL X_Cat_Load(
    X_Cat_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Cat_Unload(
    X_Cat_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Cat_EnumerateInstances(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_Cat_GetInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Cat_CreateInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* newInstance);

MI_EXTERN_C void MI_CALL X_Cat_ModifyInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Cat_DeleteInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* instanceName);


/*
**==============================================================================
**
** X_Cat_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Cat_Class : public Instance
{
public:
    
    typedef X_Cat Self;
    
    X_Cat_Class() :
        Instance(&X_Cat_rtti)
    {
    }
    
    X_Cat_Class(
        const X_Cat* instanceName,
        bool keysOnly) :
        Instance(
            &X_Cat_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Cat_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_Cat_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_Cat_Class& operator=(
        const X_Cat_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Cat_Class(
        const X_Cat_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Cat_rtti;
    }

    //
    // X_Cat_Class.Key
    //
    
    const Field<String>& Key() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n);
    }
    
    void Key(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n) = x;
    }
    
    const String& Key_value() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n).value;
    }
    
    void Key_value(const String& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n).Set(x);
    }
    
    bool Key_exists() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Key_clear()
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_Cat_Class> X_Cat_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Cat_h */
