/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _EmbeddedInstance_h
#define _EmbeddedInstance_h

#include <MI.h>

/*
**==============================================================================
**
** EmbeddedInstance [XXX_EmbeddedInstance]
**
** Keys:
**    Id
**
**==============================================================================
*/

typedef struct _EmbeddedInstance
{
    MI_Instance __instance;
    /* EmbeddedInstance properties */
    /*KEY*/ MI_ConstUint32Field Id;
    MI_ConstStringAField Element;
}
EmbeddedInstance;

typedef struct _EmbeddedInstance_Ref
{
    EmbeddedInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
EmbeddedInstance_Ref;

typedef struct _EmbeddedInstance_ConstRef
{
    MI_CONST EmbeddedInstance* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
EmbeddedInstance_ConstRef;

typedef struct _EmbeddedInstance_Array
{
    struct _EmbeddedInstance** data;
    MI_Uint32 size;
}
EmbeddedInstance_Array;

typedef struct _EmbeddedInstance_ConstArray
{
    struct _EmbeddedInstance MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
EmbeddedInstance_ConstArray;

typedef struct _EmbeddedInstance_ArrayRef
{
    EmbeddedInstance_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
EmbeddedInstance_ArrayRef;

typedef struct _EmbeddedInstance_ConstArrayRef
{
    EmbeddedInstance_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
EmbeddedInstance_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl EmbeddedInstance_rtti;

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Construct(
    EmbeddedInstance* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &EmbeddedInstance_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Clone(
    const EmbeddedInstance* self,
    EmbeddedInstance** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL EmbeddedInstance_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &EmbeddedInstance_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Destruct(EmbeddedInstance* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Delete(EmbeddedInstance* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Post(
    const EmbeddedInstance* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Set_Id(
    EmbeddedInstance* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Id)->value = x;
    ((MI_Uint32Field*)&self->Id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Clear_Id(
    EmbeddedInstance* self)
{
    memset((void*)&self->Id, 0, sizeof(self->Id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Set_Element(
    EmbeddedInstance* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_SetPtr_Element(
    EmbeddedInstance* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL EmbeddedInstance_Clear_Element(
    EmbeddedInstance* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** EmbeddedInstance provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _EmbeddedInstance_Self EmbeddedInstance_Self;

MI_EXTERN_C void MI_CALL EmbeddedInstance_Load(
    EmbeddedInstance_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL EmbeddedInstance_Unload(
    EmbeddedInstance_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL EmbeddedInstance_EnumerateInstances(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL EmbeddedInstance_GetInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL EmbeddedInstance_CreateInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* newInstance);

MI_EXTERN_C void MI_CALL EmbeddedInstance_ModifyInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL EmbeddedInstance_DeleteInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* instanceName);


/*
**==============================================================================
**
** EmbeddedInstance_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class EmbeddedInstance_Class : public Instance
{
public:
    
    typedef EmbeddedInstance Self;
    
    EmbeddedInstance_Class() :
        Instance(&EmbeddedInstance_rtti)
    {
    }
    
    EmbeddedInstance_Class(
        const EmbeddedInstance* instanceName,
        bool keysOnly) :
        Instance(
            &EmbeddedInstance_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    EmbeddedInstance_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    EmbeddedInstance_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    EmbeddedInstance_Class& operator=(
        const EmbeddedInstance_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    EmbeddedInstance_Class(
        const EmbeddedInstance_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &EmbeddedInstance_rtti;
    }

    //
    // EmbeddedInstance_Class.Id
    //
    
    const Field<Uint32>& Id() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n);
    }
    
    void Id(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Id_value() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n).value;
    }
    
    void Id_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Id_exists() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Id_clear()
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n).Clear();
    }

    //
    // EmbeddedInstance_Class.Element
    //
    
    const Field<StringA>& Element() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<StringA>(n);
    }
    
    void Element(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, Element);
        GetField<StringA>(n) = x;
    }
    
    const StringA& Element_value() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<StringA>(n).value;
    }
    
    void Element_value(const StringA& x)
    {
        const size_t n = offsetof(Self, Element);
        GetField<StringA>(n).Set(x);
    }
    
    bool Element_exists() const
    {
        const size_t n = offsetof(Self, Element);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void Element_clear()
    {
        const size_t n = offsetof(Self, Element);
        GetField<StringA>(n).Clear();
    }
};

typedef Array<EmbeddedInstance_Class> EmbeddedInstance_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _EmbeddedInstance_h */
