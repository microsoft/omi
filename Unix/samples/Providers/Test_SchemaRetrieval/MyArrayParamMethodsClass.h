/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyArrayParamMethodsClass_h
#define _MyArrayParamMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyArrayParamMethodsClass [MyArrayParamMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass
{
    MI_Instance __instance;
    /* MyArrayParamMethodsClass properties */
}
MyArrayParamMethodsClass;

typedef struct _MyArrayParamMethodsClass_Ref
{
    MyArrayParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamMethodsClass_Ref;

typedef struct _MyArrayParamMethodsClass_ConstRef
{
    MI_CONST MyArrayParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamMethodsClass_ConstRef;

typedef struct _MyArrayParamMethodsClass_Array
{
    struct _MyArrayParamMethodsClass** data;
    MI_Uint32 size;
}
MyArrayParamMethodsClass_Array;

typedef struct _MyArrayParamMethodsClass_ConstArray
{
    struct _MyArrayParamMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyArrayParamMethodsClass_ConstArray;

typedef struct _MyArrayParamMethodsClass_ArrayRef
{
    MyArrayParamMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamMethodsClass_ArrayRef;

typedef struct _MyArrayParamMethodsClass_ConstArrayRef
{
    MyArrayParamMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayParamMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyArrayParamMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Construct(
    MyArrayParamMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyArrayParamMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Clone(
    const MyArrayParamMethodsClass* self,
    MyArrayParamMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyArrayParamMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyArrayParamMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Destruct(MyArrayParamMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Delete(MyArrayParamMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Post(
    const MyArrayParamMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanAField booleanParam;
}
MyArrayParamMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Construct(
    MyArrayParamMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Clone(
    const MyArrayParamMethodsClass_BooleanMethod* self,
    MyArrayParamMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Destruct(
    MyArrayParamMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Delete(
    MyArrayParamMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Post(
    const MyArrayParamMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Set_MIReturn(
    MyArrayParamMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Clear_MIReturn(
    MyArrayParamMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Set_booleanParam(
    MyArrayParamMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_SetPtr_booleanParam(
    MyArrayParamMethodsClass_BooleanMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_BooleanMethod_Clear_booleanParam(
    MyArrayParamMethodsClass_BooleanMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringAField stringParam;
}
MyArrayParamMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Construct(
    MyArrayParamMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Clone(
    const MyArrayParamMethodsClass_StringMethod* self,
    MyArrayParamMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Destruct(
    MyArrayParamMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Delete(
    MyArrayParamMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Post(
    const MyArrayParamMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Set_MIReturn(
    MyArrayParamMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_SetPtr_MIReturn(
    MyArrayParamMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Clear_MIReturn(
    MyArrayParamMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Set_stringParam(
    MyArrayParamMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_SetPtr_stringParam(
    MyArrayParamMethodsClass_StringMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_StringMethod_Clear_stringParam(
    MyArrayParamMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16AField char16Param;
}
MyArrayParamMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Construct(
    MyArrayParamMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Clone(
    const MyArrayParamMethodsClass_Char16Method* self,
    MyArrayParamMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Destruct(
    MyArrayParamMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Delete(
    MyArrayParamMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Post(
    const MyArrayParamMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Set_MIReturn(
    MyArrayParamMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Set_char16Param(
    MyArrayParamMethodsClass_Char16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_SetPtr_char16Param(
    MyArrayParamMethodsClass_Char16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Char16Method_Clear_char16Param(
    MyArrayParamMethodsClass_Char16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8AField uint8Param;
}
MyArrayParamMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Construct(
    MyArrayParamMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Clone(
    const MyArrayParamMethodsClass_Uint8Method* self,
    MyArrayParamMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Destruct(
    MyArrayParamMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Delete(
    MyArrayParamMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Post(
    const MyArrayParamMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Set_MIReturn(
    MyArrayParamMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Set_uint8Param(
    MyArrayParamMethodsClass_Uint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_SetPtr_uint8Param(
    MyArrayParamMethodsClass_Uint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint8Method_Clear_uint8Param(
    MyArrayParamMethodsClass_Uint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8AField sint8Param;
}
MyArrayParamMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Construct(
    MyArrayParamMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Clone(
    const MyArrayParamMethodsClass_Sint8Method* self,
    MyArrayParamMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Destruct(
    MyArrayParamMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Delete(
    MyArrayParamMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Post(
    const MyArrayParamMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Set_MIReturn(
    MyArrayParamMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Set_sint8Param(
    MyArrayParamMethodsClass_Sint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_SetPtr_sint8Param(
    MyArrayParamMethodsClass_Sint8Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint8Method_Clear_sint8Param(
    MyArrayParamMethodsClass_Sint8Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16AField uint16Param;
}
MyArrayParamMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Construct(
    MyArrayParamMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Clone(
    const MyArrayParamMethodsClass_Uint16Method* self,
    MyArrayParamMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Destruct(
    MyArrayParamMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Delete(
    MyArrayParamMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Post(
    const MyArrayParamMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Set_MIReturn(
    MyArrayParamMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Set_uint16Param(
    MyArrayParamMethodsClass_Uint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_SetPtr_uint16Param(
    MyArrayParamMethodsClass_Uint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint16Method_Clear_uint16Param(
    MyArrayParamMethodsClass_Uint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16AField sint16Param;
}
MyArrayParamMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Construct(
    MyArrayParamMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Clone(
    const MyArrayParamMethodsClass_Sint16Method* self,
    MyArrayParamMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Destruct(
    MyArrayParamMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Delete(
    MyArrayParamMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Post(
    const MyArrayParamMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Set_MIReturn(
    MyArrayParamMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Set_sint16Param(
    MyArrayParamMethodsClass_Sint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_SetPtr_sint16Param(
    MyArrayParamMethodsClass_Sint16Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint16Method_Clear_sint16Param(
    MyArrayParamMethodsClass_Sint16Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32AField uint32Param;
}
MyArrayParamMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Construct(
    MyArrayParamMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Clone(
    const MyArrayParamMethodsClass_Uint32Method* self,
    MyArrayParamMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Destruct(
    MyArrayParamMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Delete(
    MyArrayParamMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Post(
    const MyArrayParamMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Set_MIReturn(
    MyArrayParamMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Set_uint32Param(
    MyArrayParamMethodsClass_Uint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_SetPtr_uint32Param(
    MyArrayParamMethodsClass_Uint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint32Method_Clear_uint32Param(
    MyArrayParamMethodsClass_Uint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32AField sint32Param;
}
MyArrayParamMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Construct(
    MyArrayParamMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Clone(
    const MyArrayParamMethodsClass_Sint32Method* self,
    MyArrayParamMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Destruct(
    MyArrayParamMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Delete(
    MyArrayParamMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Post(
    const MyArrayParamMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Set_MIReturn(
    MyArrayParamMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Set_sint32Param(
    MyArrayParamMethodsClass_Sint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_SetPtr_sint32Param(
    MyArrayParamMethodsClass_Sint32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint32Method_Clear_sint32Param(
    MyArrayParamMethodsClass_Sint32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64AField uint64Param;
}
MyArrayParamMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Construct(
    MyArrayParamMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Clone(
    const MyArrayParamMethodsClass_Uint64Method* self,
    MyArrayParamMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Destruct(
    MyArrayParamMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Delete(
    MyArrayParamMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Post(
    const MyArrayParamMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Set_MIReturn(
    MyArrayParamMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Set_uint64Param(
    MyArrayParamMethodsClass_Uint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_SetPtr_uint64Param(
    MyArrayParamMethodsClass_Uint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Uint64Method_Clear_uint64Param(
    MyArrayParamMethodsClass_Uint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64AField sint64Param;
}
MyArrayParamMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Construct(
    MyArrayParamMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Clone(
    const MyArrayParamMethodsClass_Sint64Method* self,
    MyArrayParamMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Destruct(
    MyArrayParamMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Delete(
    MyArrayParamMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Post(
    const MyArrayParamMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Set_MIReturn(
    MyArrayParamMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Set_sint64Param(
    MyArrayParamMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_SetPtr_sint64Param(
    MyArrayParamMethodsClass_Sint64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Sint64Method_Clear_sint64Param(
    MyArrayParamMethodsClass_Sint64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32AField real32Param;
}
MyArrayParamMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Construct(
    MyArrayParamMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Clone(
    const MyArrayParamMethodsClass_Real32Method* self,
    MyArrayParamMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Destruct(
    MyArrayParamMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Delete(
    MyArrayParamMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Post(
    const MyArrayParamMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Set_MIReturn(
    MyArrayParamMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Set_real32Param(
    MyArrayParamMethodsClass_Real32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_SetPtr_real32Param(
    MyArrayParamMethodsClass_Real32Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real32Method_Clear_real32Param(
    MyArrayParamMethodsClass_Real32Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64AField real64Param;
}
MyArrayParamMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Construct(
    MyArrayParamMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Clone(
    const MyArrayParamMethodsClass_Real64Method* self,
    MyArrayParamMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Destruct(
    MyArrayParamMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Delete(
    MyArrayParamMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Post(
    const MyArrayParamMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Set_MIReturn(
    MyArrayParamMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Clear_MIReturn(
    MyArrayParamMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Set_real64Param(
    MyArrayParamMethodsClass_Real64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_SetPtr_real64Param(
    MyArrayParamMethodsClass_Real64Method* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_Real64Method_Clear_real64Param(
    MyArrayParamMethodsClass_Real64Method* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyArrayParamMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeAField datetimeParam;
}
MyArrayParamMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyArrayParamMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Construct(
    MyArrayParamMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyArrayParamMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Clone(
    const MyArrayParamMethodsClass_DatetimeMethod* self,
    MyArrayParamMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Destruct(
    MyArrayParamMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Delete(
    MyArrayParamMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Post(
    const MyArrayParamMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Set_MIReturn(
    MyArrayParamMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyArrayParamMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Set_datetimeParam(
    MyArrayParamMethodsClass_DatetimeMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_SetPtr_datetimeParam(
    MyArrayParamMethodsClass_DatetimeMethod* self,
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

MI_INLINE MI_Result MI_CALL MyArrayParamMethodsClass_DatetimeMethod_Clear_datetimeParam(
    MyArrayParamMethodsClass_DatetimeMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyArrayParamMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyArrayParamMethodsClass_Self MyArrayParamMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Load(
    MyArrayParamMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Unload(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_BooleanMethod(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_StringMethod(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Char16Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Uint8Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Sint8Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Uint16Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Sint16Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Uint32Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Sint32Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Uint64Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Sint64Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Real32Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_Real64Method(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyArrayParamMethodsClass_Invoke_DatetimeMethod(
    MyArrayParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamMethodsClass* instanceName,
    const MyArrayParamMethodsClass_DatetimeMethod* in);


#endif /* _MyArrayParamMethodsClass_h */
