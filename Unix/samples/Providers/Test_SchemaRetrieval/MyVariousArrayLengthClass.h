/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyVariousArrayLengthClass_h
#define _MyVariousArrayLengthClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyVariousArrayLengthClass [MyVariousArrayLengthClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyVariousArrayLengthClass
{
    MI_Instance __instance;
    /* MyVariousArrayLengthClass properties */
    MI_ConstReal32Field uninitializedValue;
    MI_ConstBooleanAField booleanUninitializedArray;
    MI_ConstUint16AField nullArray;
    MI_ConstUint32AField uint32Array;
    MI_ConstSint32AField sint32Array;
}
MyVariousArrayLengthClass;

typedef struct _MyVariousArrayLengthClass_Ref
{
    MyVariousArrayLengthClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyVariousArrayLengthClass_Ref;

typedef struct _MyVariousArrayLengthClass_ConstRef
{
    MI_CONST MyVariousArrayLengthClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyVariousArrayLengthClass_ConstRef;

typedef struct _MyVariousArrayLengthClass_Array
{
    struct _MyVariousArrayLengthClass** data;
    MI_Uint32 size;
}
MyVariousArrayLengthClass_Array;

typedef struct _MyVariousArrayLengthClass_ConstArray
{
    struct _MyVariousArrayLengthClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyVariousArrayLengthClass_ConstArray;

typedef struct _MyVariousArrayLengthClass_ArrayRef
{
    MyVariousArrayLengthClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyVariousArrayLengthClass_ArrayRef;

typedef struct _MyVariousArrayLengthClass_ConstArrayRef
{
    MyVariousArrayLengthClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyVariousArrayLengthClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyVariousArrayLengthClass_rtti;

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Construct(
    MyVariousArrayLengthClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyVariousArrayLengthClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clone(
    const MyVariousArrayLengthClass* self,
    MyVariousArrayLengthClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyVariousArrayLengthClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyVariousArrayLengthClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Destruct(MyVariousArrayLengthClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Delete(MyVariousArrayLengthClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Post(
    const MyVariousArrayLengthClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Set_uninitializedValue(
    MyVariousArrayLengthClass* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->uninitializedValue)->value = x;
    ((MI_Real32Field*)&self->uninitializedValue)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clear_uninitializedValue(
    MyVariousArrayLengthClass* self)
{
    memset((void*)&self->uninitializedValue, 0, sizeof(self->uninitializedValue));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Set_booleanUninitializedArray(
    MyVariousArrayLengthClass* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_SetPtr_booleanUninitializedArray(
    MyVariousArrayLengthClass* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clear_booleanUninitializedArray(
    MyVariousArrayLengthClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Set_nullArray(
    MyVariousArrayLengthClass* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_SetPtr_nullArray(
    MyVariousArrayLengthClass* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clear_nullArray(
    MyVariousArrayLengthClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Set_uint32Array(
    MyVariousArrayLengthClass* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_SetPtr_uint32Array(
    MyVariousArrayLengthClass* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clear_uint32Array(
    MyVariousArrayLengthClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Set_sint32Array(
    MyVariousArrayLengthClass* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_SetPtr_sint32Array(
    MyVariousArrayLengthClass* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_Clear_sint32Array(
    MyVariousArrayLengthClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MyVariousArrayLengthClass.MethodWithArrayParam()
**
**==============================================================================
*/

typedef struct _MyVariousArrayLengthClass_MethodWithArrayParam
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstSint64AField sint64ArrayParam;
}
MyVariousArrayLengthClass_MethodWithArrayParam;

MI_EXTERN_C MI_CONST MI_MethodDecl MyVariousArrayLengthClass_MethodWithArrayParam_rtti;

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Construct(
    MyVariousArrayLengthClass_MethodWithArrayParam* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyVariousArrayLengthClass_MethodWithArrayParam_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Clone(
    const MyVariousArrayLengthClass_MethodWithArrayParam* self,
    MyVariousArrayLengthClass_MethodWithArrayParam** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Destruct(
    MyVariousArrayLengthClass_MethodWithArrayParam* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Delete(
    MyVariousArrayLengthClass_MethodWithArrayParam* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Post(
    const MyVariousArrayLengthClass_MethodWithArrayParam* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Set_MIReturn(
    MyVariousArrayLengthClass_MethodWithArrayParam* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Clear_MIReturn(
    MyVariousArrayLengthClass_MethodWithArrayParam* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Set_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithArrayParam* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_SetPtr_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithArrayParam* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithArrayParam_Clear_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithArrayParam* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyVariousArrayLengthClass.MethodWithFixedSizeArrayParam()
**
**==============================================================================
*/

typedef struct _MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstSint64AField sint64ArrayParam;
}
MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam;

MI_EXTERN_C MI_CONST MI_MethodDecl MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_rtti;

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Construct(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Clone(
    const MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Destruct(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Delete(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Post(
    const MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Set_MIReturn(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Clear_MIReturn(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Set_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_SetPtr_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_Clear_sint64ArrayParam(
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyVariousArrayLengthClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyVariousArrayLengthClass_Self MyVariousArrayLengthClass_Self;

MI_EXTERN_C void MI_CALL MyVariousArrayLengthClass_Load(
    MyVariousArrayLengthClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyVariousArrayLengthClass_Unload(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyVariousArrayLengthClass_Invoke_MethodWithArrayParam(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyVariousArrayLengthClass* instanceName,
    const MyVariousArrayLengthClass_MethodWithArrayParam* in);

MI_EXTERN_C void MI_CALL MyVariousArrayLengthClass_Invoke_MethodWithFixedSizeArrayParam(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyVariousArrayLengthClass* instanceName,
    const MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* in);


#endif /* _MyVariousArrayLengthClass_h */
