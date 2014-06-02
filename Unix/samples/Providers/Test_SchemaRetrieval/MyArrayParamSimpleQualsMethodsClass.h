/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyArrayParamSimpleQualsMethodsClass_h
#define _MyArrayParamSimpleQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass [MyArrayParamSimpleQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass
{
    MI_Instance __instance;
    /* MyArrayParamSimpleQualsMethodsClass properties */
}
MyArrayParamSimpleQualsMethodsClass;

typedef struct _MyArrayParamSimpleQualsMethodsClass_Ref
{
    MyArrayParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamSimpleQualsMethodsClass_Ref;

typedef struct _MyArrayParamSimpleQualsMethodsClass_ConstRef
{
    MI_CONST MyArrayParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamSimpleQualsMethodsClass_ConstRef;

typedef struct _MyArrayParamSimpleQualsMethodsClass_Array
{
    struct _MyArrayParamSimpleQualsMethodsClass** data;
    MI_Uint32 size;
}
MyArrayParamSimpleQualsMethodsClass_Array;

typedef struct _MyArrayParamSimpleQualsMethodsClass_ConstArray
{
    struct _MyArrayParamSimpleQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyArrayParamSimpleQualsMethodsClass_ConstArray;

typedef struct _MyArrayParamSimpleQualsMethodsClass_ArrayRef
{
    MyArrayParamSimpleQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamSimpleQualsMethodsClass_ArrayRef;

typedef struct _MyArrayParamSimpleQualsMethodsClass_ConstArrayRef
{
    MyArrayParamSimpleQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamSimpleQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyArrayParamSimpleQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Construct(
    MyArrayParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyArrayParamSimpleQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Clone(
    const MyArrayParamSimpleQualsMethodsClass* self,
    MyArrayParamSimpleQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyArrayParamSimpleQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyArrayParamSimpleQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Destruct(MyArrayParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Delete(MyArrayParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Post(
    const MyArrayParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanAField booleanParam;
}
MyArrayParamSimpleQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Construct(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Clone(
    const MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Destruct(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Delete(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Post(
    const MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Set_booleanParam(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_SetPtr_booleanParam(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_BooleanMethod_Clear_booleanParam(
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringAField stringParam;
}
MyArrayParamSimpleQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Construct(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Clone(
    const MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
    MyArrayParamSimpleQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Destruct(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Delete(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Post(
    const MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Set_stringParam(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_SetPtr_stringParam(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_StringMethod_Clear_stringParam(
    MyArrayParamSimpleQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16AField char16Param;
}
MyArrayParamSimpleQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    MyArrayParamSimpleQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Set_char16Param(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_SetPtr_char16Param(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Char16Method_Clear_char16Param(
    MyArrayParamSimpleQualsMethodsClass_Char16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8AField uint8Param;
}
MyArrayParamSimpleQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    MyArrayParamSimpleQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Set_uint8Param(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_SetPtr_uint8Param(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint8Method_Clear_uint8Param(
    MyArrayParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8AField sint8Param;
}
MyArrayParamSimpleQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    MyArrayParamSimpleQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Set_sint8Param(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_SetPtr_sint8Param(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint8Method_Clear_sint8Param(
    MyArrayParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16AField uint16Param;
}
MyArrayParamSimpleQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    MyArrayParamSimpleQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Set_uint16Param(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_SetPtr_uint16Param(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint16Method_Clear_uint16Param(
    MyArrayParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16AField sint16Param;
}
MyArrayParamSimpleQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    MyArrayParamSimpleQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Set_sint16Param(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_SetPtr_sint16Param(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint16Method_Clear_sint16Param(
    MyArrayParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32AField uint32Param;
}
MyArrayParamSimpleQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    MyArrayParamSimpleQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Set_uint32Param(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_SetPtr_uint32Param(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint32Method_Clear_uint32Param(
    MyArrayParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32AField sint32Param;
}
MyArrayParamSimpleQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    MyArrayParamSimpleQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Set_sint32Param(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_SetPtr_sint32Param(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint32Method_Clear_sint32Param(
    MyArrayParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64AField uint64Param;
}
MyArrayParamSimpleQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    MyArrayParamSimpleQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Set_uint64Param(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_SetPtr_uint64Param(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Uint64Method_Clear_uint64Param(
    MyArrayParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64AField sint64Param;
}
MyArrayParamSimpleQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
    MyArrayParamSimpleQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Set_sint64Param(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_SetPtr_sint64Param(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Sint64Method_Clear_sint64Param(
    MyArrayParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32AField real32Param;
}
MyArrayParamSimpleQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    MyArrayParamSimpleQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Set_real32Param(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_SetPtr_real32Param(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real32Method_Clear_real32Param(
    MyArrayParamSimpleQualsMethodsClass_Real32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64AField real64Param;
}
MyArrayParamSimpleQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Construct(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Clone(
    const MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    MyArrayParamSimpleQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Destruct(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Delete(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Post(
    const MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Set_real64Param(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_SetPtr_real64Param(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_Real64Method_Clear_real64Param(
    MyArrayParamSimpleQualsMethodsClass_Real64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamSimpleQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeAField datetimeParam;
}
MyArrayParamSimpleQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Construct(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Clone(
    const MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Destruct(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Delete(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Post(
    const MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Set_datetimeParam(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_SetPtr_datetimeParam(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_Clear_datetimeParam(
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyArrayParamSimpleQualsMethodsClass_Self MyArrayParamSimpleQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Load(
    MyArrayParamSimpleQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Unload(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_BooleanMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_StringMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Char16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint8Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint8Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Real32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Real64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_DatetimeMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* in);


#endif /* _MyArrayParamSimpleQualsMethodsClass_h */
