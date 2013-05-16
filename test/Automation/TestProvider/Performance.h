/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Performance_h
#define _Performance_h

#include <MI.h>

/*
**==============================================================================
**
** Performance [Demo_Performance]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _Performance
{
    MI_Instance __instance;
    /* Performance properties */
    /*KEY*/ MI_ConstUint32Field id;
}
Performance;

typedef struct _Performance_Ref
{
    Performance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Performance_Ref;

typedef struct _Performance_ConstRef
{
    MI_CONST Performance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Performance_ConstRef;

typedef struct _Performance_Array
{
    struct _Performance** data;
    MI_Uint32 size;
}
Performance_Array;

typedef struct _Performance_ConstArray
{
    struct _Performance MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Performance_ConstArray;

typedef struct _Performance_ArrayRef
{
    Performance_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Performance_ArrayRef;

typedef struct _Performance_ConstArrayRef
{
    Performance_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Performance_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Performance_rtti;

MI_INLINE MI_Result MI_CALL Performance_Construct(
    Performance* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Performance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Performance_Clone(
    const Performance* self,
    Performance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Performance_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Performance_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Performance_Destruct(Performance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Performance_Delete(Performance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Performance_Post(
    const Performance* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Performance_Set_id(
    Performance* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Performance_Clear_id(
    Performance* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Performance provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Performance_Self Performance_Self;

MI_EXTERN_C void MI_CALL Performance_Load(
    Performance_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Performance_Unload(
    Performance_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Performance_EnumerateInstances(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Performance_GetInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Performance_CreateInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* newInstance);

MI_EXTERN_C void MI_CALL Performance_ModifyInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Performance_DeleteInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* instanceName);


/*
**==============================================================================
**
** Performance_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Performance_Class : public Instance
{
public:
    
    typedef Performance Self;
    
    Performance_Class() :
        Instance(&Performance_rtti)
    {
    }
    
    Performance_Class(
        const Performance* instanceName,
        bool keysOnly) :
        Instance(
            &Performance_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Performance_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Performance_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Performance_Class& operator=(
        const Performance_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Performance_Class(
        const Performance_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Performance_rtti;
    }

    //
    // Performance_Class.id
    //
    
    const Field<Uint32>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint32>(n);
    }
    
    void id(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint32>(n).value;
    }
    
    void id_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint32>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<Performance_Class> Performance_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Performance_h */
