/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_FailedAtLoad_h
#define _X_FailedAtLoad_h

#include <MI.h>

/*
**==============================================================================
**
** X_FailedAtLoad [X_FailedAtLoad]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_FailedAtLoad
{
    MI_Instance __instance;
    /* X_FailedAtLoad properties */
    /*KEY*/ MI_ConstUint64Field id;
}
X_FailedAtLoad;

typedef struct _X_FailedAtLoad_Ref
{
    X_FailedAtLoad* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_FailedAtLoad_Ref;

typedef struct _X_FailedAtLoad_ConstRef
{
    MI_CONST X_FailedAtLoad* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_FailedAtLoad_ConstRef;

typedef struct _X_FailedAtLoad_Array
{
    struct _X_FailedAtLoad** data;
    MI_Uint32 size;
}
X_FailedAtLoad_Array;

typedef struct _X_FailedAtLoad_ConstArray
{
    struct _X_FailedAtLoad MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_FailedAtLoad_ConstArray;

typedef struct _X_FailedAtLoad_ArrayRef
{
    X_FailedAtLoad_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_FailedAtLoad_ArrayRef;

typedef struct _X_FailedAtLoad_ConstArrayRef
{
    X_FailedAtLoad_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_FailedAtLoad_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_FailedAtLoad_rtti;

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Construct(
    X_FailedAtLoad* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_FailedAtLoad_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Clone(
    const X_FailedAtLoad* self,
    X_FailedAtLoad** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_FailedAtLoad_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_FailedAtLoad_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Destruct(X_FailedAtLoad* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Delete(X_FailedAtLoad* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Post(
    const X_FailedAtLoad* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Set_id(
    X_FailedAtLoad* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_FailedAtLoad_Clear_id(
    X_FailedAtLoad* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_FailedAtLoad provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_FailedAtLoad_Self X_FailedAtLoad_Self;

MI_EXTERN_C void MI_CALL X_FailedAtLoad_Load(
    X_FailedAtLoad_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_Unload(
    X_FailedAtLoad_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_EnumerateInstances(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_GetInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_CreateInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* newInstance);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_ModifyInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_FailedAtLoad_DeleteInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName);


/*
**==============================================================================
**
** X_FailedAtLoad_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_FailedAtLoad_Class : public Instance
{
public:
    
    typedef X_FailedAtLoad Self;
    
    X_FailedAtLoad_Class() :
        Instance(&X_FailedAtLoad_rtti)
    {
    }
    
    X_FailedAtLoad_Class(
        const X_FailedAtLoad* instanceName,
        bool keysOnly) :
        Instance(
            &X_FailedAtLoad_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_FailedAtLoad_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_FailedAtLoad_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_FailedAtLoad_Class& operator=(
        const X_FailedAtLoad_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_FailedAtLoad_Class(
        const X_FailedAtLoad_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_FailedAtLoad_rtti;
    }

    //
    // X_FailedAtLoad_Class.id
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

typedef Array<X_FailedAtLoad_Class> X_FailedAtLoad_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_FailedAtLoad_h */
