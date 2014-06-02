/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyArrayParamArrayQualsMethodsClass_h
#define _MyArrayParamArrayQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass [MyArrayParamArrayQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass
{
    MI_Instance __instance;
    /* MyArrayParamArrayQualsMethodsClass properties */
}
MyArrayParamArrayQualsMethodsClass;

typedef struct _MyArrayParamArrayQualsMethodsClass_Ref
{
    MyArrayParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamArrayQualsMethodsClass_Ref;

typedef struct _MyArrayParamArrayQualsMethodsClass_ConstRef
{
    MI_CONST MyArrayParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamArrayQualsMethodsClass_ConstRef;

typedef struct _MyArrayParamArrayQualsMethodsClass_Array
{
    struct _MyArrayParamArrayQualsMethodsClass** data;
    MI_Uint32 size;
}
MyArrayParamArrayQualsMethodsClass_Array;

typedef struct _MyArrayParamArrayQualsMethodsClass_ConstArray
{
    struct _MyArrayParamArrayQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyArrayParamArrayQualsMethodsClass_ConstArray;

typedef struct _MyArrayParamArrayQualsMethodsClass_ArrayRef
{
    MyArrayParamArrayQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamArrayQualsMethodsClass_ArrayRef;

typedef struct _MyArrayParamArrayQualsMethodsClass_ConstArrayRef
{
    MyArrayParamArrayQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamArrayQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyArrayParamArrayQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Construct(
    MyArrayParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyArrayParamArrayQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Clone(
    const MyArrayParamArrayQualsMethodsClass* self,
    MyArrayParamArrayQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyArrayParamArrayQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyArrayParamArrayQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Destruct(MyArrayParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Delete(MyArrayParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Post(
    const MyArrayParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanAField booleanParam;
}
MyArrayParamArrayQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Construct(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Clone(
    const MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
    MyArrayParamArrayQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Destruct(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Delete(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Post(
    const MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Set_booleanParam(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_SetPtr_booleanParam(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_BooleanMethod_Clear_booleanParam(
    MyArrayParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringAField stringParam;
}
MyArrayParamArrayQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Construct(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Clone(
    const MyArrayParamArrayQualsMethodsClass_StringMethod* self,
    MyArrayParamArrayQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Destruct(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Delete(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Post(
    const MyArrayParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Set_stringParam(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_SetPtr_stringParam(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_StringMethod_Clear_stringParam(
    MyArrayParamArrayQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16AField char16Param;
}
MyArrayParamArrayQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Char16Method* self,
    MyArrayParamArrayQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Set_char16Param(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_SetPtr_char16Param(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Char16Method_Clear_char16Param(
    MyArrayParamArrayQualsMethodsClass_Char16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8AField uint8Param;
}
MyArrayParamArrayQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
    MyArrayParamArrayQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Set_uint8Param(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_SetPtr_uint8Param(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint8Method_Clear_uint8Param(
    MyArrayParamArrayQualsMethodsClass_Uint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8AField sint8Param;
}
MyArrayParamArrayQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
    MyArrayParamArrayQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Set_sint8Param(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_SetPtr_sint8Param(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint8Method_Clear_sint8Param(
    MyArrayParamArrayQualsMethodsClass_Sint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16AField uint16Param;
}
MyArrayParamArrayQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
    MyArrayParamArrayQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Set_uint16Param(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_SetPtr_uint16Param(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint16Method_Clear_uint16Param(
    MyArrayParamArrayQualsMethodsClass_Uint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16AField sint16Param;
}
MyArrayParamArrayQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
    MyArrayParamArrayQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Set_sint16Param(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_SetPtr_sint16Param(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint16Method_Clear_sint16Param(
    MyArrayParamArrayQualsMethodsClass_Sint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32AField uint32Param;
}
MyArrayParamArrayQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
    MyArrayParamArrayQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Set_uint32Param(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_SetPtr_uint32Param(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint32Method_Clear_uint32Param(
    MyArrayParamArrayQualsMethodsClass_Uint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32AField sint32Param;
}
MyArrayParamArrayQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
    MyArrayParamArrayQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Set_sint32Param(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_SetPtr_sint32Param(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint32Method_Clear_sint32Param(
    MyArrayParamArrayQualsMethodsClass_Sint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64AField uint64Param;
}
MyArrayParamArrayQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
    MyArrayParamArrayQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Set_uint64Param(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_SetPtr_uint64Param(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Uint64Method_Clear_uint64Param(
    MyArrayParamArrayQualsMethodsClass_Uint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64AField sint64Param;
}
MyArrayParamArrayQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
    MyArrayParamArrayQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Set_sint64Param(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_SetPtr_sint64Param(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Sint64Method_Clear_sint64Param(
    MyArrayParamArrayQualsMethodsClass_Sint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32AField real32Param;
}
MyArrayParamArrayQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Real32Method* self,
    MyArrayParamArrayQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Set_real32Param(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_SetPtr_real32Param(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real32Method_Clear_real32Param(
    MyArrayParamArrayQualsMethodsClass_Real32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64AField real64Param;
}
MyArrayParamArrayQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Construct(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Clone(
    const MyArrayParamArrayQualsMethodsClass_Real64Method* self,
    MyArrayParamArrayQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Destruct(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Delete(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Post(
    const MyArrayParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Set_real64Param(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_SetPtr_real64Param(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_Real64Method_Clear_real64Param(
    MyArrayParamArrayQualsMethodsClass_Real64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamArrayQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeAField datetimeParam;
}
MyArrayParamArrayQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Construct(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Clone(
    const MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Destruct(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Delete(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Post(
    const MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Set_datetimeParam(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_SetPtr_datetimeParam(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamArrayQualsMethodsClass_DatetimeMethod_Clear_datetimeParam(
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyArrayParamArrayQualsMethodsClass_Self MyArrayParamArrayQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Load(
    MyArrayParamArrayQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Unload(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_BooleanMethod(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_StringMethod(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Char16Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Uint8Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Sint8Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Uint16Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Sint16Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Uint32Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Sint32Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Uint64Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Sint64Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Real32Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_Real64Method(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamArrayQualsMethodsClass_Invoke_DatetimeMethod(
    MyArrayParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamArrayQualsMethodsClass* instanceName,
    const MyArrayParamArrayQualsMethodsClass_DatetimeMethod* in);


#endif /* _MyArrayParamArrayQualsMethodsClass_h */
