/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestEmbeddedOperations_h
#define _TestEmbeddedOperations_h

#include <MI.h>
#include "MSFT_Person.h"
#include "X_TestObject.h"
#include "X_TestEmbeddedInstanceMIReturnObject.h"

/*
**==============================================================================
**
** TestEmbeddedOperations [TestEmbeddedOperations]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _TestEmbeddedOperations
{
    MI_Instance __instance;
    /* TestEmbeddedOperations properties */
    /*KEY*/ MI_ConstUint32Field key;
    MSFT_Person_ConstRef person;
    MSFT_Person_ConstArrayRef threePersons;
}
TestEmbeddedOperations;

typedef struct _TestEmbeddedOperations_Ref
{
    TestEmbeddedOperations* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestEmbeddedOperations_Ref;

typedef struct _TestEmbeddedOperations_ConstRef
{
    MI_CONST TestEmbeddedOperations* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestEmbeddedOperations_ConstRef;

typedef struct _TestEmbeddedOperations_Array
{
    struct _TestEmbeddedOperations** data;
    MI_Uint32 size;
}
TestEmbeddedOperations_Array;

typedef struct _TestEmbeddedOperations_ConstArray
{
    struct _TestEmbeddedOperations MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestEmbeddedOperations_ConstArray;

typedef struct _TestEmbeddedOperations_ArrayRef
{
    TestEmbeddedOperations_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestEmbeddedOperations_ArrayRef;

typedef struct _TestEmbeddedOperations_ConstArrayRef
{
    TestEmbeddedOperations_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestEmbeddedOperations_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestEmbeddedOperations_rtti;

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Construct(
    TestEmbeddedOperations* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &TestEmbeddedOperations_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Clone(
    const TestEmbeddedOperations* self,
    TestEmbeddedOperations** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestEmbeddedOperations_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestEmbeddedOperations_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Destruct(TestEmbeddedOperations* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Delete(TestEmbeddedOperations* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Post(
    const TestEmbeddedOperations* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Set_key(
    TestEmbeddedOperations* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->key)->value = x;
    ((MI_Uint32Field*)&self->key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Clear_key(
    TestEmbeddedOperations* self)
{
    memset((void*)&self->key, 0, sizeof(self->key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Set_person(
    TestEmbeddedOperations* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_SetPtr_person(
    TestEmbeddedOperations* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Clear_person(
    TestEmbeddedOperations* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Set_threePersons(
    TestEmbeddedOperations* self,
    const MSFT_Person * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_SetPtr_threePersons(
    TestEmbeddedOperations* self,
    const MSFT_Person * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_Clear_threePersons(
    TestEmbeddedOperations* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** TestEmbeddedOperations.TestEmbedded()
**
**==============================================================================
*/

typedef struct _TestEmbeddedOperations_TestEmbedded
{
    MI_Instance __instance;
    /*OUT*/ X_TestObject_ConstRef MIReturn;
    /*IN-OUT*/ MI_ConstReferenceAField objectsArray;
    /*IN-OUT*/ MI_ConstReferenceField objectSingle;
    /*IN-OUT*/ X_TestObject_ConstArrayRef testObjectsArray;
    /*IN-OUT*/ X_TestObject_ConstRef testObjectSingle;
}
TestEmbeddedOperations_TestEmbedded;

MI_EXTERN_C MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbedded_rtti;

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Construct(
    TestEmbeddedOperations_TestEmbedded* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestEmbeddedOperations_TestEmbedded_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clone(
    const TestEmbeddedOperations_TestEmbedded* self,
    TestEmbeddedOperations_TestEmbedded** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Destruct(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Delete(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Post(
    const TestEmbeddedOperations_TestEmbedded* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Set_MIReturn(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_SetPtr_MIReturn(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clear_MIReturn(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Set_objectsArray(
    TestEmbeddedOperations_TestEmbedded* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_SetPtr_objectsArray(
    TestEmbeddedOperations_TestEmbedded* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clear_objectsArray(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Set_objectSingle(
    TestEmbeddedOperations_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_SetPtr_objectSingle(
    TestEmbeddedOperations_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clear_objectSingle(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Set_testObjectsArray(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_SetPtr_testObjectsArray(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clear_testObjectsArray(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Set_testObjectSingle(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_SetPtr_testObjectSingle(
    TestEmbeddedOperations_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbedded_Clear_testObjectSingle(
    TestEmbeddedOperations_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** TestEmbeddedOperations.TestEmbeddedInstanceReturnKey20100609()
**
**==============================================================================
*/

typedef struct _TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609
{
    MI_Instance __instance;
    /*OUT*/ X_TestEmbeddedInstanceMIReturnObject_ConstRef MIReturn;
}
TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609;

MI_EXTERN_C MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti;

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Construct(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Clone(
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self,
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Destruct(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Delete(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Post(
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Set_MIReturn(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self,
    const X_TestEmbeddedInstanceMIReturnObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_SetPtr_MIReturn(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self,
    const X_TestEmbeddedInstanceMIReturnObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Clear_MIReturn(
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** TestEmbeddedOperations.TestEmbeddedObjectReturnKey20100609()
**
**==============================================================================
*/

typedef struct _TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReferenceField MIReturn;
}
TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609;

MI_EXTERN_C MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti;

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Construct(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Clone(
    const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self,
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Destruct(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Delete(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Post(
    const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Set_MIReturn(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_SetPtr_MIReturn(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Clear_MIReturn(
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** TestEmbeddedOperations provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestEmbeddedOperations_Self TestEmbeddedOperations_Self;

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Load(
    TestEmbeddedOperations_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Unload(
    TestEmbeddedOperations_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_EnumerateInstances(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_GetInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_CreateInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* newInstance);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_ModifyInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_DeleteInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbedded(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbedded* in);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedInstanceReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* in);

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedObjectReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* in);


/*
**==============================================================================
**
** TestEmbeddedOperations_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class TestEmbeddedOperations_Class : public Instance
{
public:
    
    typedef TestEmbeddedOperations Self;
    
    TestEmbeddedOperations_Class() :
        Instance(&TestEmbeddedOperations_rtti)
    {
    }
    
    TestEmbeddedOperations_Class(
        const TestEmbeddedOperations* instanceName,
        bool keysOnly) :
        Instance(
            &TestEmbeddedOperations_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    TestEmbeddedOperations_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    TestEmbeddedOperations_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    TestEmbeddedOperations_Class& operator=(
        const TestEmbeddedOperations_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    TestEmbeddedOperations_Class(
        const TestEmbeddedOperations_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &TestEmbeddedOperations_rtti;
    }

    //
    // TestEmbeddedOperations_Class.key
    //
    
    const Field<Uint32>& key() const
    {
        const size_t n = offsetof(Self, key);
        return GetField<Uint32>(n);
    }
    
    void key(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, key);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& key_value() const
    {
        const size_t n = offsetof(Self, key);
        return GetField<Uint32>(n).value;
    }
    
    void key_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, key);
        GetField<Uint32>(n).Set(x);
    }
    
    bool key_exists() const
    {
        const size_t n = offsetof(Self, key);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void key_clear()
    {
        const size_t n = offsetof(Self, key);
        GetField<Uint32>(n).Clear();
    }

    //
    // TestEmbeddedOperations_Class.person
    //
    
    const Field<MSFT_Person_Class>& person() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n);
    }
    
    void person(const Field<MSFT_Person_Class>& x)
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n) = x;
    }
    
    const MSFT_Person_Class& person_value() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n).value;
    }
    
    void person_value(const MSFT_Person_Class& x)
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n).Set(x);
    }
    
    bool person_exists() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n).exists ? true : false;
    }
    
    void person_clear()
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n).Clear();
    }

    //
    // TestEmbeddedOperations_Class.threePersons
    //
    
    const Field<MSFT_Person_ClassA>& threePersons() const
    {
        const size_t n = offsetof(Self, threePersons);
        return GetField<MSFT_Person_ClassA>(n);
    }
    
    void threePersons(const Field<MSFT_Person_ClassA>& x)
    {
        const size_t n = offsetof(Self, threePersons);
        GetField<MSFT_Person_ClassA>(n) = x;
    }
    
    const MSFT_Person_ClassA& threePersons_value() const
    {
        const size_t n = offsetof(Self, threePersons);
        return GetField<MSFT_Person_ClassA>(n).value;
    }
    
    void threePersons_value(const MSFT_Person_ClassA& x)
    {
        const size_t n = offsetof(Self, threePersons);
        GetField<MSFT_Person_ClassA>(n).Set(x);
    }
    
    bool threePersons_exists() const
    {
        const size_t n = offsetof(Self, threePersons);
        return GetField<MSFT_Person_ClassA>(n).exists ? true : false;
    }
    
    void threePersons_clear()
    {
        const size_t n = offsetof(Self, threePersons);
        GetField<MSFT_Person_ClassA>(n).Clear();
    }
};

typedef Array<TestEmbeddedOperations_Class> TestEmbeddedOperations_ClassA;

class TestEmbeddedOperations_TestEmbedded_Class : public Instance
{
public:
    
    typedef TestEmbeddedOperations_TestEmbedded Self;
    
    TestEmbeddedOperations_TestEmbedded_Class() :
        Instance(&TestEmbeddedOperations_TestEmbedded_rtti)
    {
    }
    
    TestEmbeddedOperations_TestEmbedded_Class(
        const TestEmbeddedOperations_TestEmbedded* instanceName,
        bool keysOnly) :
        Instance(
            &TestEmbeddedOperations_TestEmbedded_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbedded_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbedded_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    TestEmbeddedOperations_TestEmbedded_Class& operator=(
        const TestEmbeddedOperations_TestEmbedded_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    TestEmbeddedOperations_TestEmbedded_Class(
        const TestEmbeddedOperations_TestEmbedded_Class& x) :
        Instance(x)
    {
    }

    //
    // TestEmbeddedOperations_TestEmbedded_Class.MIReturn
    //
    
    const Field<X_TestObject_Class>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestObject_Class>(n);
    }
    
    void MIReturn(const Field<X_TestObject_Class>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestObject_Class>(n) = x;
    }
    
    const X_TestObject_Class& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestObject_Class>(n).value;
    }
    
    void MIReturn_value(const X_TestObject_Class& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestObject_Class>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestObject_Class>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestObject_Class>(n).Clear();
    }

    //
    // TestEmbeddedOperations_TestEmbedded_Class.objectsArray
    //
    
    const Field<InstanceA>& objectsArray() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n);
    }
    
    void objectsArray(const Field<InstanceA>& x)
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n) = x;
    }
    
    const InstanceA& objectsArray_value() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n).value;
    }
    
    void objectsArray_value(const InstanceA& x)
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n).Set(x);
    }
    
    bool objectsArray_exists() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n).exists ? true : false;
    }
    
    void objectsArray_clear()
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n).Clear();
    }

    //
    // TestEmbeddedOperations_TestEmbedded_Class.objectSingle
    //
    
    const Field<Instance>& objectSingle() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n);
    }
    
    void objectSingle(const Field<Instance>& x)
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n) = x;
    }
    
    const Instance& objectSingle_value() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n).value;
    }
    
    void objectSingle_value(const Instance& x)
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n).Set(x);
    }
    
    bool objectSingle_exists() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n).exists ? true : false;
    }
    
    void objectSingle_clear()
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n).Clear();
    }

    //
    // TestEmbeddedOperations_TestEmbedded_Class.testObjectsArray
    //
    
    const Field<X_TestObject_ClassA>& testObjectsArray() const
    {
        const size_t n = offsetof(Self, testObjectsArray);
        return GetField<X_TestObject_ClassA>(n);
    }
    
    void testObjectsArray(const Field<X_TestObject_ClassA>& x)
    {
        const size_t n = offsetof(Self, testObjectsArray);
        GetField<X_TestObject_ClassA>(n) = x;
    }
    
    const X_TestObject_ClassA& testObjectsArray_value() const
    {
        const size_t n = offsetof(Self, testObjectsArray);
        return GetField<X_TestObject_ClassA>(n).value;
    }
    
    void testObjectsArray_value(const X_TestObject_ClassA& x)
    {
        const size_t n = offsetof(Self, testObjectsArray);
        GetField<X_TestObject_ClassA>(n).Set(x);
    }
    
    bool testObjectsArray_exists() const
    {
        const size_t n = offsetof(Self, testObjectsArray);
        return GetField<X_TestObject_ClassA>(n).exists ? true : false;
    }
    
    void testObjectsArray_clear()
    {
        const size_t n = offsetof(Self, testObjectsArray);
        GetField<X_TestObject_ClassA>(n).Clear();
    }

    //
    // TestEmbeddedOperations_TestEmbedded_Class.testObjectSingle
    //
    
    const Field<X_TestObject_Class>& testObjectSingle() const
    {
        const size_t n = offsetof(Self, testObjectSingle);
        return GetField<X_TestObject_Class>(n);
    }
    
    void testObjectSingle(const Field<X_TestObject_Class>& x)
    {
        const size_t n = offsetof(Self, testObjectSingle);
        GetField<X_TestObject_Class>(n) = x;
    }
    
    const X_TestObject_Class& testObjectSingle_value() const
    {
        const size_t n = offsetof(Self, testObjectSingle);
        return GetField<X_TestObject_Class>(n).value;
    }
    
    void testObjectSingle_value(const X_TestObject_Class& x)
    {
        const size_t n = offsetof(Self, testObjectSingle);
        GetField<X_TestObject_Class>(n).Set(x);
    }
    
    bool testObjectSingle_exists() const
    {
        const size_t n = offsetof(Self, testObjectSingle);
        return GetField<X_TestObject_Class>(n).exists ? true : false;
    }
    
    void testObjectSingle_clear()
    {
        const size_t n = offsetof(Self, testObjectSingle);
        GetField<X_TestObject_Class>(n).Clear();
    }
};

typedef Array<TestEmbeddedOperations_TestEmbedded_Class> TestEmbeddedOperations_TestEmbedded_ClassA;

class TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class : public Instance
{
public:
    
    typedef TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609 Self;
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class() :
        Instance(&TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class(
        const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* instanceName,
        bool keysOnly) :
        Instance(
            &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class& operator=(
        const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class(
        const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class& x) :
        Instance(x)
    {
    }

    //
    // TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class.MIReturn
    //
    
    const Field<X_TestEmbeddedInstanceMIReturnObject_Class>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n);
    }
    
    void MIReturn(const Field<X_TestEmbeddedInstanceMIReturnObject_Class>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n) = x;
    }
    
    const X_TestEmbeddedInstanceMIReturnObject_Class& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n).value;
    }
    
    void MIReturn_value(const X_TestEmbeddedInstanceMIReturnObject_Class& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<X_TestEmbeddedInstanceMIReturnObject_Class>(n).Clear();
    }
};

typedef Array<TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class> TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_ClassA;

class TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class : public Instance
{
public:
    
    typedef TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609 Self;
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class() :
        Instance(&TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class(
        const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* instanceName,
        bool keysOnly) :
        Instance(
            &TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class& operator=(
        const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class(
        const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class& x) :
        Instance(x)
    {
    }

    //
    // TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class.MIReturn
    //
    
    const Field<Instance>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Instance>(n);
    }
    
    void MIReturn(const Field<Instance>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Instance>(n) = x;
    }
    
    const Instance& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Instance>(n).value;
    }
    
    void MIReturn_value(const Instance& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Instance>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Instance>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Instance>(n).Clear();
    }
};

typedef Array<TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class> TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _TestEmbeddedOperations_h */
