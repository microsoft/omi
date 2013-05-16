/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Main_h
#define _Main_h

#include <MI.h>
#include "EmbeddedInstance.h"

/*
**==============================================================================
**
** Main [XXX_Main]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _Main
{
    MI_Instance __instance;
    /* Main properties */
    /*KEY*/ MI_ConstStringField Name;
    EmbeddedInstance_ConstRef FristInstance;
    EmbeddedInstance_ConstRef SecondInstance;
}
Main;

typedef struct _Main_Ref
{
    Main* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_Ref;

typedef struct _Main_ConstRef
{
    MI_CONST Main* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ConstRef;

typedef struct _Main_Array
{
    struct _Main** data;
    MI_Uint32 size;
}
Main_Array;

typedef struct _Main_ConstArray
{
    struct _Main MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Main_ConstArray;

typedef struct _Main_ArrayRef
{
    Main_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ArrayRef;

typedef struct _Main_ConstArrayRef
{
    Main_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Main_rtti;

MI_INLINE MI_Result MI_CALL Main_Construct(
    Main* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Main_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Clone(
    const Main* self,
    Main** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Main_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Main_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Main_Destruct(Main* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Delete(Main* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Post(
    const Main* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Set_Name(
    Main* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Main_SetPtr_Name(
    Main* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Main_Clear_Name(
    Main* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Main_Set_FristInstance(
    Main* self,
    const EmbeddedInstance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Main_SetPtr_FristInstance(
    Main* self,
    const EmbeddedInstance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Main_Clear_FristInstance(
    Main* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Main_Set_SecondInstance(
    Main* self,
    const EmbeddedInstance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Main_SetPtr_SecondInstance(
    Main* self,
    const EmbeddedInstance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Main_Clear_SecondInstance(
    Main* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** Main provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Main_Self Main_Self;

MI_EXTERN_C void MI_CALL Main_Load(
    Main_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Main_Unload(
    Main_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Main_EnumerateInstances(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Main_GetInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Main_CreateInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* newInstance);

MI_EXTERN_C void MI_CALL Main_ModifyInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Main_DeleteInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName);


/*
**==============================================================================
**
** Main_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Main_Class : public Instance
{
public:
    
    typedef Main Self;
    
    Main_Class() :
        Instance(&Main_rtti)
    {
    }
    
    Main_Class(
        const Main* instanceName,
        bool keysOnly) :
        Instance(
            &Main_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Main_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Main_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Main_Class& operator=(
        const Main_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Main_Class(
        const Main_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Main_rtti;
    }

    //
    // Main_Class.Name
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
    // Main_Class.FristInstance
    //
    
    const Field<EmbeddedInstance_Class>& FristInstance() const
    {
        const size_t n = offsetof(Self, FristInstance);
        return GetField<EmbeddedInstance_Class>(n);
    }
    
    void FristInstance(const Field<EmbeddedInstance_Class>& x)
    {
        const size_t n = offsetof(Self, FristInstance);
        GetField<EmbeddedInstance_Class>(n) = x;
    }
    
    const EmbeddedInstance_Class& FristInstance_value() const
    {
        const size_t n = offsetof(Self, FristInstance);
        return GetField<EmbeddedInstance_Class>(n).value;
    }
    
    void FristInstance_value(const EmbeddedInstance_Class& x)
    {
        const size_t n = offsetof(Self, FristInstance);
        GetField<EmbeddedInstance_Class>(n).Set(x);
    }
    
    bool FristInstance_exists() const
    {
        const size_t n = offsetof(Self, FristInstance);
        return GetField<EmbeddedInstance_Class>(n).exists ? true : false;
    }
    
    void FristInstance_clear()
    {
        const size_t n = offsetof(Self, FristInstance);
        GetField<EmbeddedInstance_Class>(n).Clear();
    }

    //
    // Main_Class.SecondInstance
    //
    
    const Field<EmbeddedInstance_Class>& SecondInstance() const
    {
        const size_t n = offsetof(Self, SecondInstance);
        return GetField<EmbeddedInstance_Class>(n);
    }
    
    void SecondInstance(const Field<EmbeddedInstance_Class>& x)
    {
        const size_t n = offsetof(Self, SecondInstance);
        GetField<EmbeddedInstance_Class>(n) = x;
    }
    
    const EmbeddedInstance_Class& SecondInstance_value() const
    {
        const size_t n = offsetof(Self, SecondInstance);
        return GetField<EmbeddedInstance_Class>(n).value;
    }
    
    void SecondInstance_value(const EmbeddedInstance_Class& x)
    {
        const size_t n = offsetof(Self, SecondInstance);
        GetField<EmbeddedInstance_Class>(n).Set(x);
    }
    
    bool SecondInstance_exists() const
    {
        const size_t n = offsetof(Self, SecondInstance);
        return GetField<EmbeddedInstance_Class>(n).exists ? true : false;
    }
    
    void SecondInstance_clear()
    {
        const size_t n = offsetof(Self, SecondInstance);
        GetField<EmbeddedInstance_Class>(n).Clear();
    }
};

typedef Array<Main_Class> Main_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Main_h */
