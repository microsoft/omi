/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Frog_h
#define _Frog_h

#include <MI.h>

/*
**==============================================================================
**
** Frog [Frog]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _Frog
{
    MI_Instance __instance;
    /* Frog properties */
    /*KEY*/ MI_ConstStringField id;
}
Frog;

typedef struct _Frog_Ref
{
    Frog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Frog_Ref;

typedef struct _Frog_ConstRef
{
    MI_CONST Frog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Frog_ConstRef;

typedef struct _Frog_Array
{
    struct _Frog** data;
    MI_Uint32 size;
}
Frog_Array;

typedef struct _Frog_ConstArray
{
    struct _Frog MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Frog_ConstArray;

typedef struct _Frog_ArrayRef
{
    Frog_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Frog_ArrayRef;

typedef struct _Frog_ConstArrayRef
{
    Frog_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Frog_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Frog_rtti;

MI_INLINE MI_Result MI_CALL Frog_Construct(
    Frog* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Frog_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Frog_Clone(
    const Frog* self,
    Frog** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Frog_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Frog_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Frog_Destruct(Frog* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Frog_Delete(Frog* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Frog_Post(
    const Frog* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Frog_Set_id(
    Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Frog_SetPtr_id(
    Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Frog_Clear_id(
    Frog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** Frog provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Frog_Self Frog_Self;

MI_EXTERN_C void MI_CALL Frog_Load(
    Frog_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Frog_Unload(
    Frog_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Frog_EnumerateInstances(
    Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Frog_GetInstance(
    Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Frog* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Frog_CreateInstance(
    Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Frog* newInstance);

MI_EXTERN_C void MI_CALL Frog_ModifyInstance(
    Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Frog* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Frog_DeleteInstance(
    Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Frog* instanceName);


/*
**==============================================================================
**
** Frog_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Frog_Class : public Instance
{
public:
    
    typedef Frog Self;
    
    Frog_Class() :
        Instance(&Frog_rtti)
    {
    }
    
    Frog_Class(
        const Frog* instanceName,
        bool keysOnly) :
        Instance(
            &Frog_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Frog_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Frog_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Frog_Class& operator=(
        const Frog_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Frog_Class(
        const Frog_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Frog_rtti;
    }

    //
    // Frog_Class.id
    //
    
    const Field<String>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<String>(n);
    }
    
    void id(const Field<String>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<String>(n) = x;
    }
    
    const String& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<String>(n).value;
    }
    
    void id_value(const String& x)
    {
        const size_t n = offsetof(Self, id);
        return GetField<String>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<String>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<String>(n).Clear();
    }
};

typedef Array<Frog_Class> Frog_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Frog_h */
