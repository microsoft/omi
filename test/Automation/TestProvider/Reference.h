/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Reference_h
#define _Reference_h

#include <MI.h>

/*
**==============================================================================
**
** Reference [Demo_Reference]
**
** Keys:
**    Description
**
**==============================================================================
*/

typedef struct _Reference
{
    MI_Instance __instance;
    /* Reference properties */
    /*KEY*/ MI_ConstStringField Description;
}
Reference;

typedef struct _Reference_Ref
{
    Reference* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Reference_Ref;

typedef struct _Reference_ConstRef
{
    MI_CONST Reference* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Reference_ConstRef;

typedef struct _Reference_Array
{
    struct _Reference** data;
    MI_Uint32 size;
}
Reference_Array;

typedef struct _Reference_ConstArray
{
    struct _Reference MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Reference_ConstArray;

typedef struct _Reference_ArrayRef
{
    Reference_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Reference_ArrayRef;

typedef struct _Reference_ConstArrayRef
{
    Reference_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Reference_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Reference_rtti;

MI_INLINE MI_Result MI_CALL Reference_Construct(
    Reference* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Reference_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Reference_Clone(
    const Reference* self,
    Reference** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Reference_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Reference_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Reference_Destruct(Reference* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Reference_Delete(Reference* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Reference_Post(
    const Reference* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Reference_Set_Description(
    Reference* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Reference_SetPtr_Description(
    Reference* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Reference_Clear_Description(
    Reference* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** Reference provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Reference_Self Reference_Self;

MI_EXTERN_C void MI_CALL Reference_Load(
    Reference_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Reference_Unload(
    Reference_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Reference_EnumerateInstances(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Reference_GetInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Reference_CreateInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* newInstance);

MI_EXTERN_C void MI_CALL Reference_ModifyInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Reference_DeleteInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName);


/*
**==============================================================================
**
** Reference_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Reference_Class : public Instance
{
public:
    
    typedef Reference Self;
    
    Reference_Class() :
        Instance(&Reference_rtti)
    {
    }
    
    Reference_Class(
        const Reference* instanceName,
        bool keysOnly) :
        Instance(
            &Reference_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Reference_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Reference_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Reference_Class& operator=(
        const Reference_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Reference_Class(
        const Reference_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Reference_rtti;
    }

    //
    // Reference_Class.Description
    //
    
    const Field<String>& Description() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n);
    }
    
    void Description(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n) = x;
    }
    
    const String& Description_value() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).value;
    }
    
    void Description_value(const String& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Set(x);
    }
    
    bool Description_exists() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Description_clear()
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Clear();
    }
};

typedef Array<Reference_Class> Reference_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Reference_h */
