/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_HugeNumber_h
#define _X_HugeNumber_h

#include <MI.h>
#include "X_Number.h"
#include "X_SmallNumber.h"
#include "X_TestObject.h"

/*
**==============================================================================
**
** X_HugeNumber [X_HugeNumber]
**
** Keys:
**    Number
**
**==============================================================================
*/

typedef struct _X_HugeNumber /* extends X_Number */
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
}
X_HugeNumber;

typedef struct _X_HugeNumber_Ref
{
    X_HugeNumber* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumber_Ref;

typedef struct _X_HugeNumber_ConstRef
{
    MI_CONST X_HugeNumber* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumber_ConstRef;

typedef struct _X_HugeNumber_Array
{
    struct _X_HugeNumber** data;
    MI_Uint32 size;
}
X_HugeNumber_Array;

typedef struct _X_HugeNumber_ConstArray
{
    struct _X_HugeNumber MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_HugeNumber_ConstArray;

typedef struct _X_HugeNumber_ArrayRef
{
    X_HugeNumber_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumber_ArrayRef;

typedef struct _X_HugeNumber_ConstArrayRef
{
    X_HugeNumber_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_HugeNumber_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_HugeNumber_rtti;

MI_INLINE MI_Result MI_CALL X_HugeNumber_Construct(
    X_HugeNumber* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_HugeNumber_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clone(
    const X_HugeNumber* self,
    X_HugeNumber** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_HugeNumber_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_HugeNumber_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Destruct(X_HugeNumber* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Delete(X_HugeNumber* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Post(
    const X_HugeNumber* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_Description(
    X_HugeNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_Description(
    X_HugeNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_Description(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_Number(
    X_HugeNumber* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Number)->value = x;
    ((MI_Uint64Field*)&self->Number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_Number(
    X_HugeNumber* self)
{
    memset((void*)&self->Number, 0, sizeof(self->Number));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_Magnitude(
    X_HugeNumber* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Magnitude)->value = x;
    ((MI_Uint32Field*)&self->Magnitude)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_Magnitude(
    X_HugeNumber* self)
{
    memset((void*)&self->Magnitude, 0, sizeof(self->Magnitude));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_MagnitudeObj(
    X_HugeNumber* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_MagnitudeObj(
    X_HugeNumber* self,
    const X_SmallNumber* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_MagnitudeObj(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_Numbers123(
    X_HugeNumber* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_Numbers123(
    X_HugeNumber* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_Numbers123(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_Number0(
    X_HugeNumber* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_Number0(
    X_HugeNumber* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_Number0(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_TwoTestObjects(
    X_HugeNumber* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_TwoTestObjects(
    X_HugeNumber* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_TwoTestObjects(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Set_TestObject(
    X_HugeNumber* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SetPtr_TestObject(
    X_HugeNumber* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_Clear_TestObject(
    X_HugeNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** X_HugeNumber.SpellMagnitude()
**
**==============================================================================
*/

typedef struct _X_HugeNumber_SpellMagnitude
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
X_HugeNumber_SpellMagnitude;

MI_EXTERN_C MI_CONST MI_MethodDecl X_HugeNumber_SpellMagnitude_rtti;

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Construct(
    X_HugeNumber_SpellMagnitude* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_HugeNumber_SpellMagnitude_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Clone(
    const X_HugeNumber_SpellMagnitude* self,
    X_HugeNumber_SpellMagnitude** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Destruct(
    X_HugeNumber_SpellMagnitude* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Delete(
    X_HugeNumber_SpellMagnitude* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Post(
    const X_HugeNumber_SpellMagnitude* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Set_MIReturn(
    X_HugeNumber_SpellMagnitude* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_SetPtr_MIReturn(
    X_HugeNumber_SpellMagnitude* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_SpellMagnitude_Clear_MIReturn(
    X_HugeNumber_SpellMagnitude* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** X_HugeNumber.TestEmbedded()
**
**==============================================================================
*/

typedef struct _X_HugeNumber_TestEmbedded
{
    MI_Instance __instance;
    /*OUT*/ X_TestObject_ConstRef MIReturn;
    /*IN-OUT*/ MI_ConstReferenceAField objectsArray;
    /*IN-OUT*/ MI_ConstReferenceField objectSingle;
    /*IN-OUT*/ X_TestObject_ConstArrayRef testObjectsArray;
    /*IN-OUT*/ X_TestObject_ConstRef testObjectSingle;
}
X_HugeNumber_TestEmbedded;

MI_EXTERN_C MI_CONST MI_MethodDecl X_HugeNumber_TestEmbedded_rtti;

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Construct(
    X_HugeNumber_TestEmbedded* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_HugeNumber_TestEmbedded_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clone(
    const X_HugeNumber_TestEmbedded* self,
    X_HugeNumber_TestEmbedded** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Destruct(
    X_HugeNumber_TestEmbedded* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Delete(
    X_HugeNumber_TestEmbedded* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Post(
    const X_HugeNumber_TestEmbedded* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Set_MIReturn(
    X_HugeNumber_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_SetPtr_MIReturn(
    X_HugeNumber_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clear_MIReturn(
    X_HugeNumber_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Set_objectsArray(
    X_HugeNumber_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_SetPtr_objectsArray(
    X_HugeNumber_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clear_objectsArray(
    X_HugeNumber_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Set_objectSingle(
    X_HugeNumber_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_SetPtr_objectSingle(
    X_HugeNumber_TestEmbedded* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clear_objectSingle(
    X_HugeNumber_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Set_testObjectsArray(
    X_HugeNumber_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_SetPtr_testObjectsArray(
    X_HugeNumber_TestEmbedded* self,
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

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clear_testObjectsArray(
    X_HugeNumber_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Set_testObjectSingle(
    X_HugeNumber_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_SetPtr_testObjectSingle(
    X_HugeNumber_TestEmbedded* self,
    const X_TestObject* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_HugeNumber_TestEmbedded_Clear_testObjectSingle(
    X_HugeNumber_TestEmbedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** X_HugeNumber provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_HugeNumber_Self X_HugeNumber_Self;

MI_EXTERN_C void MI_CALL X_HugeNumber_Load(
    X_HugeNumber_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumber_Unload(
    X_HugeNumber_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_HugeNumber_EnumerateInstances(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_HugeNumber_GetInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumber_CreateInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* newInstance);

MI_EXTERN_C void MI_CALL X_HugeNumber_ModifyInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_HugeNumber_DeleteInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* instanceName);

MI_EXTERN_C void MI_CALL X_HugeNumber_Invoke_SpellMagnitude(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_HugeNumber* instanceName,
    const X_HugeNumber_SpellMagnitude* in);

MI_EXTERN_C void MI_CALL X_HugeNumber_Invoke_TestEmbedded(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_HugeNumber* instanceName,
    const X_HugeNumber_TestEmbedded* in);


/*
**==============================================================================
**
** X_HugeNumber_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_HugeNumber_Class : public X_Number_Class
{
public:
    
    typedef X_HugeNumber Self;
    
    X_HugeNumber_Class() :
        X_Number_Class(&X_HugeNumber_rtti)
    {
    }
    
    X_HugeNumber_Class(
        const X_HugeNumber* instanceName,
        bool keysOnly) :
        X_Number_Class(
            &X_HugeNumber_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HugeNumber_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_Number_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_HugeNumber_Class(
        const MI_ClassDecl* clDecl) :
        X_Number_Class(clDecl)
    {
    }
    
    X_HugeNumber_Class& operator=(
        const X_HugeNumber_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HugeNumber_Class(
        const X_HugeNumber_Class& x) :
        X_Number_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_HugeNumber_rtti;
    }

    //
    // X_HugeNumber_Class.Magnitude
    //
    
    const Field<Uint32>& Magnitude() const
    {
        const size_t n = offsetof(Self, Magnitude);
        return GetField<Uint32>(n);
    }
    
    void Magnitude(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Magnitude);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Magnitude_value() const
    {
        const size_t n = offsetof(Self, Magnitude);
        return GetField<Uint32>(n).value;
    }
    
    void Magnitude_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Magnitude);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Magnitude_exists() const
    {
        const size_t n = offsetof(Self, Magnitude);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Magnitude_clear()
    {
        const size_t n = offsetof(Self, Magnitude);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_HugeNumber_Class.MagnitudeObj
    //
    
    const Field<X_SmallNumber_Class>& MagnitudeObj() const
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        return GetField<X_SmallNumber_Class>(n);
    }
    
    void MagnitudeObj(const Field<X_SmallNumber_Class>& x)
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        GetField<X_SmallNumber_Class>(n) = x;
    }
    
    const X_SmallNumber_Class& MagnitudeObj_value() const
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        return GetField<X_SmallNumber_Class>(n).value;
    }
    
    void MagnitudeObj_value(const X_SmallNumber_Class& x)
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        GetField<X_SmallNumber_Class>(n).Set(x);
    }
    
    bool MagnitudeObj_exists() const
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        return GetField<X_SmallNumber_Class>(n).exists ? true : false;
    }
    
    void MagnitudeObj_clear()
    {
        const size_t n = offsetof(Self, MagnitudeObj);
        GetField<X_SmallNumber_Class>(n).Clear();
    }

    //
    // X_HugeNumber_Class.Numbers123
    //
    
    const Field<X_SmallNumber_ClassA>& Numbers123() const
    {
        const size_t n = offsetof(Self, Numbers123);
        return GetField<X_SmallNumber_ClassA>(n);
    }
    
    void Numbers123(const Field<X_SmallNumber_ClassA>& x)
    {
        const size_t n = offsetof(Self, Numbers123);
        GetField<X_SmallNumber_ClassA>(n) = x;
    }
    
    const X_SmallNumber_ClassA& Numbers123_value() const
    {
        const size_t n = offsetof(Self, Numbers123);
        return GetField<X_SmallNumber_ClassA>(n).value;
    }
    
    void Numbers123_value(const X_SmallNumber_ClassA& x)
    {
        const size_t n = offsetof(Self, Numbers123);
        GetField<X_SmallNumber_ClassA>(n).Set(x);
    }
    
    bool Numbers123_exists() const
    {
        const size_t n = offsetof(Self, Numbers123);
        return GetField<X_SmallNumber_ClassA>(n).exists ? true : false;
    }
    
    void Numbers123_clear()
    {
        const size_t n = offsetof(Self, Numbers123);
        GetField<X_SmallNumber_ClassA>(n).Clear();
    }

    //
    // X_HugeNumber_Class.Number0
    //
    
    const Field<Instance>& Number0() const
    {
        const size_t n = offsetof(Self, Number0);
        return GetField<Instance>(n);
    }
    
    void Number0(const Field<Instance>& x)
    {
        const size_t n = offsetof(Self, Number0);
        GetField<Instance>(n) = x;
    }
    
    const Instance& Number0_value() const
    {
        const size_t n = offsetof(Self, Number0);
        return GetField<Instance>(n).value;
    }
    
    void Number0_value(const Instance& x)
    {
        const size_t n = offsetof(Self, Number0);
        GetField<Instance>(n).Set(x);
    }
    
    bool Number0_exists() const
    {
        const size_t n = offsetof(Self, Number0);
        return GetField<Instance>(n).exists ? true : false;
    }
    
    void Number0_clear()
    {
        const size_t n = offsetof(Self, Number0);
        GetField<Instance>(n).Clear();
    }

    //
    // X_HugeNumber_Class.TwoTestObjects
    //
    
    const Field<InstanceA>& TwoTestObjects() const
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        return GetField<InstanceA>(n);
    }
    
    void TwoTestObjects(const Field<InstanceA>& x)
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        GetField<InstanceA>(n) = x;
    }
    
    const InstanceA& TwoTestObjects_value() const
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        return GetField<InstanceA>(n).value;
    }
    
    void TwoTestObjects_value(const InstanceA& x)
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        GetField<InstanceA>(n).Set(x);
    }
    
    bool TwoTestObjects_exists() const
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        return GetField<InstanceA>(n).exists ? true : false;
    }
    
    void TwoTestObjects_clear()
    {
        const size_t n = offsetof(Self, TwoTestObjects);
        GetField<InstanceA>(n).Clear();
    }

    //
    // X_HugeNumber_Class.TestObject
    //
    
    const Field<X_TestObject_Class>& TestObject() const
    {
        const size_t n = offsetof(Self, TestObject);
        return GetField<X_TestObject_Class>(n);
    }
    
    void TestObject(const Field<X_TestObject_Class>& x)
    {
        const size_t n = offsetof(Self, TestObject);
        GetField<X_TestObject_Class>(n) = x;
    }
    
    const X_TestObject_Class& TestObject_value() const
    {
        const size_t n = offsetof(Self, TestObject);
        return GetField<X_TestObject_Class>(n).value;
    }
    
    void TestObject_value(const X_TestObject_Class& x)
    {
        const size_t n = offsetof(Self, TestObject);
        GetField<X_TestObject_Class>(n).Set(x);
    }
    
    bool TestObject_exists() const
    {
        const size_t n = offsetof(Self, TestObject);
        return GetField<X_TestObject_Class>(n).exists ? true : false;
    }
    
    void TestObject_clear()
    {
        const size_t n = offsetof(Self, TestObject);
        GetField<X_TestObject_Class>(n).Clear();
    }
};

typedef Array<X_HugeNumber_Class> X_HugeNumber_ClassA;

class X_HugeNumber_SpellMagnitude_Class : public Instance
{
public:
    
    typedef X_HugeNumber_SpellMagnitude Self;
    
    X_HugeNumber_SpellMagnitude_Class() :
        Instance(&X_HugeNumber_SpellMagnitude_rtti)
    {
    }
    
    X_HugeNumber_SpellMagnitude_Class(
        const X_HugeNumber_SpellMagnitude* instanceName,
        bool keysOnly) :
        Instance(
            &X_HugeNumber_SpellMagnitude_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HugeNumber_SpellMagnitude_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_HugeNumber_SpellMagnitude_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_HugeNumber_SpellMagnitude_Class& operator=(
        const X_HugeNumber_SpellMagnitude_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HugeNumber_SpellMagnitude_Class(
        const X_HugeNumber_SpellMagnitude_Class& x) :
        Instance(x)
    {
    }

    //
    // X_HugeNumber_SpellMagnitude_Class.MIReturn
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

typedef Array<X_HugeNumber_SpellMagnitude_Class> X_HugeNumber_SpellMagnitude_ClassA;

class X_HugeNumber_TestEmbedded_Class : public Instance
{
public:
    
    typedef X_HugeNumber_TestEmbedded Self;
    
    X_HugeNumber_TestEmbedded_Class() :
        Instance(&X_HugeNumber_TestEmbedded_rtti)
    {
    }
    
    X_HugeNumber_TestEmbedded_Class(
        const X_HugeNumber_TestEmbedded* instanceName,
        bool keysOnly) :
        Instance(
            &X_HugeNumber_TestEmbedded_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_HugeNumber_TestEmbedded_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_HugeNumber_TestEmbedded_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_HugeNumber_TestEmbedded_Class& operator=(
        const X_HugeNumber_TestEmbedded_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_HugeNumber_TestEmbedded_Class(
        const X_HugeNumber_TestEmbedded_Class& x) :
        Instance(x)
    {
    }

    //
    // X_HugeNumber_TestEmbedded_Class.MIReturn
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
    // X_HugeNumber_TestEmbedded_Class.objectsArray
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
    // X_HugeNumber_TestEmbedded_Class.objectSingle
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
    // X_HugeNumber_TestEmbedded_Class.testObjectsArray
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
    // X_HugeNumber_TestEmbedded_Class.testObjectSingle
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

typedef Array<X_HugeNumber_TestEmbedded_Class> X_HugeNumber_TestEmbedded_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_HugeNumber_h */
