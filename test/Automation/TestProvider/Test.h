/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_h
#define _Test_h

#include <MI.h>
#include "Identifier.h"
#include "Reference.h"

/*
**==============================================================================
**
** Test [Demo_Test]
**
** Keys:
**    Id
**    Rf
**
**==============================================================================
*/

typedef struct _Test
{
    MI_Instance __instance;
    /* Test properties */
    /*KEY*/ Identifier_ConstRef Id;
    /*KEY*/ Reference_ConstRef Rf;
}
Test;

typedef struct _Test_Ref
{
    Test* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Ref;

typedef struct _Test_ConstRef
{
    MI_CONST Test* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_ConstRef;

typedef struct _Test_Array
{
    struct _Test** data;
    MI_Uint32 size;
}
Test_Array;

typedef struct _Test_ConstArray
{
    struct _Test MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_ConstArray;

typedef struct _Test_ArrayRef
{
    Test_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_ArrayRef;

typedef struct _Test_ConstArrayRef
{
    Test_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_rtti;

MI_INLINE MI_Result MI_CALL Test_Construct(
    Test* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Clone(
    const Test* self,
    Test** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_Destruct(Test* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Delete(Test* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Post(
    const Test* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Set_Id(
    Test* self,
    const Identifier* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_SetPtr_Id(
    Test* self,
    const Identifier* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Clear_Id(
    Test* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Set_Rf(
    Test* self,
    const Reference* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_SetPtr_Rf(
    Test* self,
    const Reference* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Clear_Rf(
    Test* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Test.StaticFun()
**
**==============================================================================
*/

typedef struct _Test_StaticFun
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Test_StaticFun;

MI_EXTERN_C MI_CONST MI_MethodDecl Test_StaticFun_rtti;

MI_INLINE MI_Result MI_CALL Test_StaticFun_Construct(
    Test_StaticFun* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Test_StaticFun_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Clone(
    const Test_StaticFun* self,
    Test_StaticFun** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Destruct(
    Test_StaticFun* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Delete(
    Test_StaticFun* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Post(
    const Test_StaticFun* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Set_MIReturn(
    Test_StaticFun* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_StaticFun_Clear_MIReturn(
    Test_StaticFun* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test.InstanceFun()
**
**==============================================================================
*/

typedef struct _Test_InstanceFun
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Test_InstanceFun;

MI_EXTERN_C MI_CONST MI_MethodDecl Test_InstanceFun_rtti;

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Construct(
    Test_InstanceFun* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Test_InstanceFun_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Clone(
    const Test_InstanceFun* self,
    Test_InstanceFun** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Destruct(
    Test_InstanceFun* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Delete(
    Test_InstanceFun* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Post(
    const Test_InstanceFun* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Set_MIReturn(
    Test_InstanceFun* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_InstanceFun_Clear_MIReturn(
    Test_InstanceFun* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_Self Test_Self;

MI_EXTERN_C void MI_CALL Test_Load(
    Test_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_Unload(
    Test_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_EnumerateInstances(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_GetInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_CreateInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* newInstance);

MI_EXTERN_C void MI_CALL Test_ModifyInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_DeleteInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* instanceName);

MI_EXTERN_C void MI_CALL Test_AssociatorInstancesId(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_AssociatorInstancesRf(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_ReferenceInstancesId(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_ReferenceInstancesRf(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_Invoke_StaticFun(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test* instanceName,
    const Test_StaticFun* in);

MI_EXTERN_C void MI_CALL Test_Invoke_InstanceFun(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test* instanceName,
    const Test_InstanceFun* in);


/*
**==============================================================================
**
** Test_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Test_Class : public Instance
{
public:
    
    typedef Test Self;
    
    Test_Class() :
        Instance(&Test_rtti)
    {
    }
    
    Test_Class(
        const Test* instanceName,
        bool keysOnly) :
        Instance(
            &Test_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Test_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Test_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Test_Class& operator=(
        const Test_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Test_Class(
        const Test_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Test_rtti;
    }

    //
    // Test_Class.Id
    //
    
    const Field<Identifier_Class>& Id() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Identifier_Class>(n);
    }
    
    void Id(const Field<Identifier_Class>& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Identifier_Class>(n) = x;
    }
    
    const Identifier_Class& Id_value() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Identifier_Class>(n).value;
    }
    
    void Id_value(const Identifier_Class& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Identifier_Class>(n).Set(x);
    }
    
    bool Id_exists() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Identifier_Class>(n).exists ? true : false;
    }
    
    void Id_clear()
    {
        const size_t n = offsetof(Self, Id);
        GetField<Identifier_Class>(n).Clear();
    }

    //
    // Test_Class.Rf
    //
    
    const Field<Reference_Class>& Rf() const
    {
        const size_t n = offsetof(Self, Rf);
        return GetField<Reference_Class>(n);
    }
    
    void Rf(const Field<Reference_Class>& x)
    {
        const size_t n = offsetof(Self, Rf);
        GetField<Reference_Class>(n) = x;
    }
    
    const Reference_Class& Rf_value() const
    {
        const size_t n = offsetof(Self, Rf);
        return GetField<Reference_Class>(n).value;
    }
    
    void Rf_value(const Reference_Class& x)
    {
        const size_t n = offsetof(Self, Rf);
        GetField<Reference_Class>(n).Set(x);
    }
    
    bool Rf_exists() const
    {
        const size_t n = offsetof(Self, Rf);
        return GetField<Reference_Class>(n).exists ? true : false;
    }
    
    void Rf_clear()
    {
        const size_t n = offsetof(Self, Rf);
        GetField<Reference_Class>(n).Clear();
    }
};

typedef Array<Test_Class> Test_ClassA;

class Test_StaticFun_Class : public Instance
{
public:
    
    typedef Test_StaticFun Self;
    
    Test_StaticFun_Class() :
        Instance(&Test_StaticFun_rtti)
    {
    }
    
    Test_StaticFun_Class(
        const Test_StaticFun* instanceName,
        bool keysOnly) :
        Instance(
            &Test_StaticFun_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Test_StaticFun_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Test_StaticFun_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Test_StaticFun_Class& operator=(
        const Test_StaticFun_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Test_StaticFun_Class(
        const Test_StaticFun_Class& x) :
        Instance(x)
    {
    }

    //
    // Test_StaticFun_Class.MIReturn
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

typedef Array<Test_StaticFun_Class> Test_StaticFun_ClassA;

class Test_InstanceFun_Class : public Instance
{
public:
    
    typedef Test_InstanceFun Self;
    
    Test_InstanceFun_Class() :
        Instance(&Test_InstanceFun_rtti)
    {
    }
    
    Test_InstanceFun_Class(
        const Test_InstanceFun* instanceName,
        bool keysOnly) :
        Instance(
            &Test_InstanceFun_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Test_InstanceFun_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Test_InstanceFun_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Test_InstanceFun_Class& operator=(
        const Test_InstanceFun_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Test_InstanceFun_Class(
        const Test_InstanceFun_Class& x) :
        Instance(x)
    {
    }

    //
    // Test_InstanceFun_Class.MIReturn
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

typedef Array<Test_InstanceFun_Class> Test_InstanceFun_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Test_h */
