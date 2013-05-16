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


#endif /* _TestEmbeddedOperations_h */
