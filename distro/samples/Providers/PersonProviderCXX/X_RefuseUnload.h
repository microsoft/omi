/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_RefuseUnload_h
#define _X_RefuseUnload_h

#include <MI.h>

/*
**==============================================================================
**
** X_RefuseUnload [X_RefuseUnload]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_RefuseUnload
{
    MI_Instance __instance;
    /* X_RefuseUnload properties */
    /*KEY*/ MI_ConstUint64Field id;
}
X_RefuseUnload;

typedef struct _X_RefuseUnload_Ref
{
    X_RefuseUnload* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_RefuseUnload_Ref;

typedef struct _X_RefuseUnload_ConstRef
{
    MI_CONST X_RefuseUnload* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_RefuseUnload_ConstRef;

typedef struct _X_RefuseUnload_Array
{
    struct _X_RefuseUnload** data;
    MI_Uint32 size;
}
X_RefuseUnload_Array;

typedef struct _X_RefuseUnload_ConstArray
{
    struct _X_RefuseUnload MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_RefuseUnload_ConstArray;

typedef struct _X_RefuseUnload_ArrayRef
{
    X_RefuseUnload_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_RefuseUnload_ArrayRef;

typedef struct _X_RefuseUnload_ConstArrayRef
{
    X_RefuseUnload_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_RefuseUnload_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_RefuseUnload_rtti;

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Construct(
    X_RefuseUnload* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_RefuseUnload_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Clone(
    const X_RefuseUnload* self,
    X_RefuseUnload** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_RefuseUnload_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_RefuseUnload_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Destruct(X_RefuseUnload* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Delete(X_RefuseUnload* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Post(
    const X_RefuseUnload* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Set_id(
    X_RefuseUnload* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_Clear_id(
    X_RefuseUnload* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_RefuseUnload.RequestUnload()
**
**==============================================================================
*/

typedef struct _X_RefuseUnload_RequestUnload
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
X_RefuseUnload_RequestUnload;

MI_EXTERN_C MI_CONST MI_MethodDecl X_RefuseUnload_RequestUnload_rtti;

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Construct(
    X_RefuseUnload_RequestUnload* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_RefuseUnload_RequestUnload_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Clone(
    const X_RefuseUnload_RequestUnload* self,
    X_RefuseUnload_RequestUnload** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Destruct(
    X_RefuseUnload_RequestUnload* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Delete(
    X_RefuseUnload_RequestUnload* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Post(
    const X_RefuseUnload_RequestUnload* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Set_MIReturn(
    X_RefuseUnload_RequestUnload* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_RefuseUnload_RequestUnload_Clear_MIReturn(
    X_RefuseUnload_RequestUnload* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_RefuseUnload provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_RefuseUnload_Self X_RefuseUnload_Self;

MI_EXTERN_C void MI_CALL X_RefuseUnload_Load(
    X_RefuseUnload_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_RefuseUnload_Unload(
    X_RefuseUnload_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_RefuseUnload_EnumerateInstances(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_RefuseUnload_GetInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_RefuseUnload_CreateInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* newInstance);

MI_EXTERN_C void MI_CALL X_RefuseUnload_ModifyInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_RefuseUnload_DeleteInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* instanceName);

MI_EXTERN_C void MI_CALL X_RefuseUnload_Invoke_RequestUnload(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_RefuseUnload* instanceName,
    const X_RefuseUnload_RequestUnload* in);


/*
**==============================================================================
**
** X_RefuseUnload_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_RefuseUnload_Class : public Instance
{
public:
    
    typedef X_RefuseUnload Self;
    
    X_RefuseUnload_Class() :
        Instance(&X_RefuseUnload_rtti)
    {
    }
    
    X_RefuseUnload_Class(
        const X_RefuseUnload* instanceName,
        bool keysOnly) :
        Instance(
            &X_RefuseUnload_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_RefuseUnload_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_RefuseUnload_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_RefuseUnload_Class& operator=(
        const X_RefuseUnload_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_RefuseUnload_Class(
        const X_RefuseUnload_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_RefuseUnload_rtti;
    }

    //
    // X_RefuseUnload_Class.id
    //
    
    const Field<Uint64>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n);
    }
    
    void id(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).value;
    }
    
    void id_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<X_RefuseUnload_Class> X_RefuseUnload_ClassA;

class X_RefuseUnload_RequestUnload_Class : public Instance
{
public:
    
    typedef X_RefuseUnload_RequestUnload Self;
    
    X_RefuseUnload_RequestUnload_Class() :
        Instance(&X_RefuseUnload_RequestUnload_rtti)
    {
    }
    
    X_RefuseUnload_RequestUnload_Class(
        const X_RefuseUnload_RequestUnload* instanceName,
        bool keysOnly) :
        Instance(
            &X_RefuseUnload_RequestUnload_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_RefuseUnload_RequestUnload_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_RefuseUnload_RequestUnload_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_RefuseUnload_RequestUnload_Class& operator=(
        const X_RefuseUnload_RequestUnload_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_RefuseUnload_RequestUnload_Class(
        const X_RefuseUnload_RequestUnload_Class& x) :
        Instance(x)
    {
    }

    //
    // X_RefuseUnload_RequestUnload_Class.MIReturn
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

typedef Array<X_RefuseUnload_RequestUnload_Class> X_RefuseUnload_RequestUnload_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_RefuseUnload_h */
