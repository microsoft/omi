/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_Number1000001_h
#define _X_Number1000001_h

#include <MI.h>
#include "X_HugeNumber.h"
#include "X_SmallNumber.h"
#include "X_TestObject.h"

/*
**==============================================================================
**
** X_Number1000001 [X_Number1000001]
**
** Keys:
**    Number
**
**==============================================================================
*/

typedef struct _X_Number1000001 /* extends X_HugeNumber */
{
    MI_Instance __instance;
    /* X_ManagedElement properties */
    MI_ConstStringField Description;
    /* X_Number properties */
    /*KEY*/ MI_ConstUint64Field Number;
    /* X_HugeNumber properties */
    MI_ConstUint32Field Magnitude;
    X_SmallNumber_ConstRef MagnitudeObj;
    X_SmallNumber_ConstArrayRef Numbers123;
    MI_ConstReferenceField Number0;
    MI_ConstReferenceAField TwoTestObjects;
    X_TestObject_ConstRef TestObject;
    /* X_Number1000001 properties */
    MI_ConstUint32Field Property0;
}
X_Number1000001;

typedef struct _X_Number1000001_Ref
{
    X_Number1000001* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number1000001_Ref;

typedef struct _X_Number1000001_ConstRef
{
    MI_CONST X_Number1000001* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number1000001_ConstRef;

typedef struct _X_Number1000001_Array
{
    struct _X_Number1000001** data;
    MI_Uint32 size;
}
X_Number1000001_Array;

typedef struct _X_Number1000001_ConstArray
{
    struct _X_Number1000001 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_Number1000001_ConstArray;

typedef struct _X_Number1000001_ArrayRef
{
    X_Number1000001_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number1000001_ArrayRef;

typedef struct _X_Number1000001_ConstArrayRef
{
    X_Number1000001_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_Number1000001_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_Number1000001_rtti;

MI_INLINE MI_Result MI_CALL X_Number1000001_Construct(
    X_Number1000001* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_Number1000001_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clone(
    const X_Number1000001* self,
    X_Number1000001** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_Number1000001_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_Number1000001_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Destruct(X_Number1000001* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Delete(X_Number1000001* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Post(
    const X_Number1000001* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Description(
    X_Number1000001* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_Description(
    X_Number1000001* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Description(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Number(
    X_Number1000001* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Number)->value = x;
    ((MI_Uint64Field*)&self->Number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Number(
    X_Number1000001* self)
{
    memset((void*)&self->Number, 0, sizeof(self->Number));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Magnitude(
    X_Number1000001* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Magnitude)->value = x;
    ((MI_Uint32Field*)&self->Magnitude)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Magnitude(
    X_Number1000001* self)
{
    memset((void*)&self->Magnitude, 0, sizeof(self->Magnitude));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_MagnitudeObj(
    X_Number1000001* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_MagnitudeObj(
    X_Number1000001* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_MagnitudeObj(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Numbers123(
    X_Number1000001* self,
    const X_SmallNumber * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_Numbers123(
    X_Number1000001* self,
    const X_SmallNumber * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Numbers123(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Number0(
    X_Number1000001* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_Number0(
    X_Number1000001* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Number0(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_TwoTestObjects(
    X_Number1000001* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_TwoTestObjects(
    X_Number1000001* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_TwoTestObjects(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_TestObject(
    X_Number1000001* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SetPtr_TestObject(
    X_Number1000001* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_TestObject(
    X_Number1000001* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Set_Property0(
    X_Number1000001* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Property0)->value = x;
    ((MI_Uint32Field*)&self->Property0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Clear_Property0(
    X_Number1000001* self)
{
    memset((void*)&self->Property0, 0, sizeof(self->Property0));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_Number1000001.SpellMagnitude()
**
**==============================================================================
*/

typedef struct _X_Number1000001_SpellMagnitude
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
X_Number1000001_SpellMagnitude;

MI_EXTERN_C MI_CONST MI_MethodDecl X_Number1000001_SpellMagnitude_rtti;

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Construct(
    X_Number1000001_SpellMagnitude* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_Number1000001_SpellMagnitude_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Clone(
    const X_Number1000001_SpellMagnitude* self,
    X_Number1000001_SpellMagnitude** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Destruct(
    X_Number1000001_SpellMagnitude* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Delete(
    X_Number1000001_SpellMagnitude* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Post(
    const X_Number1000001_SpellMagnitude* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Set_MIReturn(
    X_Number1000001_SpellMagnitude* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_SetPtr_MIReturn(
    X_Number1000001_SpellMagnitude* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_SpellMagnitude_Clear_MIReturn(
    X_Number1000001_SpellMagnitude* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** X_Number1000001.TestEmbedded()
**
**==============================================================================
*/

typedef struct _X_Number1000001_TestEmbedded
{
    MI_Instance __instance;
    /*OUT*/ X_TestObject_ConstRef MIReturn;
    /*IN-OUT*/ MI_ConstReferenceAField objectsArray;
    /*IN-OUT*/ MI_ConstReferenceField objectSingle;
    /*IN-OUT*/ X_TestObject_ConstArrayRef testObjectsArray;
    /*IN-OUT*/ X_TestObject_ConstRef testObjectSingle;
}
X_Number1000001_TestEmbedded;

MI_EXTERN_C MI_CONST MI_MethodDecl X_Number1000001_TestEmbedded_rtti;

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Construct(
    X_Number1000001_TestEmbedded* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_Number1000001_TestEmbedded_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clone(
    const X_Number1000001_TestEmbedded* self,
    X_Number1000001_TestEmbedded** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Destruct(
    X_Number1000001_TestEmbedded* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Delete(
    X_Number1000001_TestEmbedded* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Post(
    const X_Number1000001_TestEmbedded* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Set_MIReturn(
    X_Number1000001_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_SetPtr_MIReturn(
    X_Number1000001_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clear_MIReturn(
    X_Number1000001_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Set_objectsArray(
    X_Number1000001_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_SetPtr_objectsArray(
    X_Number1000001_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clear_objectsArray(
    X_Number1000001_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Set_objectSingle(
    X_Number1000001_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_SetPtr_objectSingle(
    X_Number1000001_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clear_objectSingle(
    X_Number1000001_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Set_testObjectsArray(
    X_Number1000001_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_SetPtr_testObjectsArray(
    X_Number1000001_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clear_testObjectsArray(
    X_Number1000001_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Set_testObjectSingle(
    X_Number1000001_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_SetPtr_testObjectSingle(
    X_Number1000001_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_TestEmbedded_Clear_testObjectSingle(
    X_Number1000001_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** X_Number1000001.Method1()
**
**==============================================================================
*/

typedef struct _X_Number1000001_Method1
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
X_Number1000001_Method1;

MI_EXTERN_C MI_CONST MI_MethodDecl X_Number1000001_Method1_rtti;

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Construct(
    X_Number1000001_Method1* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_Number1000001_Method1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Clone(
    const X_Number1000001_Method1* self,
    X_Number1000001_Method1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Destruct(
    X_Number1000001_Method1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Delete(
    X_Number1000001_Method1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Post(
    const X_Number1000001_Method1* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Set_MIReturn(
    X_Number1000001_Method1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_SetPtr_MIReturn(
    X_Number1000001_Method1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_Number1000001_Method1_Clear_MIReturn(
    X_Number1000001_Method1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** X_Number1000001 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_Number1000001_Self X_Number1000001_Self;

MI_EXTERN_C void MI_CALL X_Number1000001_Load(
    X_Number1000001_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Number1000001_Unload(
    X_Number1000001_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_Number1000001_EnumerateInstances(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_Number1000001_GetInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Number1000001_CreateInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* newInstance);

MI_EXTERN_C void MI_CALL X_Number1000001_ModifyInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_Number1000001_DeleteInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* instanceName);

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_SpellMagnitude(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_SpellMagnitude* in);

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_TestEmbedded(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_TestEmbedded* in);

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_Method1(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_Method1* in);


/*
**==============================================================================
**
** X_Number1000001_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_Number1000001_Class : public X_HugeNumber_Class
{
public:
    
    typedef X_Number1000001 Self;
    
    X_Number1000001_Class() :
        X_HugeNumber_Class(&X_Number1000001_rtti)
    {
    }
    
    X_Number1000001_Class(
        const X_Number1000001* instanceName,
        bool keysOnly) :
        X_HugeNumber_Class(
            &X_Number1000001_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Number1000001_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_HugeNumber_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_Number1000001_Class(
        const MI_ClassDecl* clDecl) :
        X_HugeNumber_Class(clDecl)
    {
    }
    
    X_Number1000001_Class& operator=(
        const X_Number1000001_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Number1000001_Class(
        const X_Number1000001_Class& x) :
        X_HugeNumber_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_Number1000001_rtti;
    }

    //
    // X_Number1000001_Class.Property0
    //
    
    const Field<Uint32>& Property0() const
    {
        const size_t n = offsetof(Self, Property0);
        return GetField<Uint32>(n);
    }
    
    void Property0(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Property0);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Property0_value() const
    {
        const size_t n = offsetof(Self, Property0);
        return GetField<Uint32>(n).value;
    }
    
    void Property0_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Property0);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Property0_exists() const
    {
        const size_t n = offsetof(Self, Property0);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Property0_clear()
    {
        const size_t n = offsetof(Self, Property0);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<X_Number1000001_Class> X_Number1000001_ClassA;

class X_Number1000001_SpellMagnitude_Class : public Instance
{
public:
    
    typedef X_Number1000001_SpellMagnitude Self;
    
    X_Number1000001_SpellMagnitude_Class() :
        Instance(&X_Number1000001_SpellMagnitude_rtti)
    {
    }
    
    X_Number1000001_SpellMagnitude_Class(
        const X_Number1000001_SpellMagnitude* instanceName,
        bool keysOnly) :
        Instance(
            &X_Number1000001_SpellMagnitude_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Number1000001_SpellMagnitude_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_Number1000001_SpellMagnitude_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_Number1000001_SpellMagnitude_Class& operator=(
        const X_Number1000001_SpellMagnitude_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Number1000001_SpellMagnitude_Class(
        const X_Number1000001_SpellMagnitude_Class& x) :
        Instance(x)
    {
    }

    //
    // X_Number1000001_SpellMagnitude_Class.MIReturn
    //
    
    const Field<String>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n);
    }
    
    void MIReturn(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n) = x;
    }
    
    const String& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).value;
    }
    
    void MIReturn_value(const String& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_Number1000001_SpellMagnitude_Class> X_Number1000001_SpellMagnitude_ClassA;

class X_Number1000001_TestEmbedded_Class : public Instance
{
public:
    
    typedef X_Number1000001_TestEmbedded Self;
    
    X_Number1000001_TestEmbedded_Class() :
        Instance(&X_Number1000001_TestEmbedded_rtti)
    {
    }
    
    X_Number1000001_TestEmbedded_Class(
        const X_Number1000001_TestEmbedded* instanceName,
        bool keysOnly) :
        Instance(
            &X_Number1000001_TestEmbedded_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Number1000001_TestEmbedded_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_Number1000001_TestEmbedded_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_Number1000001_TestEmbedded_Class& operator=(
        const X_Number1000001_TestEmbedded_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Number1000001_TestEmbedded_Class(
        const X_Number1000001_TestEmbedded_Class& x) :
        Instance(x)
    {
    }

    //
    // X_Number1000001_TestEmbedded_Class.MIReturn
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
    // X_Number1000001_TestEmbedded_Class.objectsArray
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
    // X_Number1000001_TestEmbedded_Class.objectSingle
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
    // X_Number1000001_TestEmbedded_Class.testObjectsArray
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
    // X_Number1000001_TestEmbedded_Class.testObjectSingle
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

typedef Array<X_Number1000001_TestEmbedded_Class> X_Number1000001_TestEmbedded_ClassA;

class X_Number1000001_Method1_Class : public Instance
{
public:
    
    typedef X_Number1000001_Method1 Self;
    
    X_Number1000001_Method1_Class() :
        Instance(&X_Number1000001_Method1_rtti)
    {
    }
    
    X_Number1000001_Method1_Class(
        const X_Number1000001_Method1* instanceName,
        bool keysOnly) :
        Instance(
            &X_Number1000001_Method1_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_Number1000001_Method1_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_Number1000001_Method1_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_Number1000001_Method1_Class& operator=(
        const X_Number1000001_Method1_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_Number1000001_Method1_Class(
        const X_Number1000001_Method1_Class& x) :
        Instance(x)
    {
    }

    //
    // X_Number1000001_Method1_Class.MIReturn
    //
    
    const Field<String>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n);
    }
    
    void MIReturn(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n) = x;
    }
    
    const String& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).value;
    }
    
    void MIReturn_value(const String& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_Number1000001_Method1_Class> X_Number1000001_Method1_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Number1000001_h */
