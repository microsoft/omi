/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimpleParamSimpleQualsMethodsClass_h
#define _MySimpleParamSimpleQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass [MySimpleParamSimpleQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass
{
    MI_Instance __instance;
    /* MySimpleParamSimpleQualsMethodsClass properties */
}
MySimpleParamSimpleQualsMethodsClass;

typedef struct _MySimpleParamSimpleQualsMethodsClass_Ref
{
    MySimpleParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamSimpleQualsMethodsClass_Ref;

typedef struct _MySimpleParamSimpleQualsMethodsClass_ConstRef
{
    MI_CONST MySimpleParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamSimpleQualsMethodsClass_ConstRef;

typedef struct _MySimpleParamSimpleQualsMethodsClass_Array
{
    struct _MySimpleParamSimpleQualsMethodsClass** data;
    MI_Uint32 size;
}
MySimpleParamSimpleQualsMethodsClass_Array;

typedef struct _MySimpleParamSimpleQualsMethodsClass_ConstArray
{
    struct _MySimpleParamSimpleQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimpleParamSimpleQualsMethodsClass_ConstArray;

typedef struct _MySimpleParamSimpleQualsMethodsClass_ArrayRef
{
    MySimpleParamSimpleQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamSimpleQualsMethodsClass_ArrayRef;

typedef struct _MySimpleParamSimpleQualsMethodsClass_ConstArrayRef
{
    MySimpleParamSimpleQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamSimpleQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimpleParamSimpleQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Construct(
    MySimpleParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimpleParamSimpleQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Clone(
    const MySimpleParamSimpleQualsMethodsClass* self,
    MySimpleParamSimpleQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimpleParamSimpleQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimpleParamSimpleQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Destruct(MySimpleParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Delete(MySimpleParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Post(
    const MySimpleParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanField booleanParam;
}
MySimpleParamSimpleQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Construct(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Clone(
    const MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self,
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Destruct(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Delete(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Post(
    const MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Set_booleanParam(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->booleanParam)->value = x;
    ((MI_BooleanField*)&self->booleanParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_BooleanMethod_Clear_booleanParam(
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->booleanParam, 0, sizeof(self->booleanParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringField stringParam;
}
MySimpleParamSimpleQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Construct(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Clone(
    const MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    MySimpleParamSimpleQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Destruct(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Delete(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Post(
    const MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Set_stringParam(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_SetPtr_stringParam(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_StringMethod_Clear_stringParam(
    MySimpleParamSimpleQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16Field char16Param;
}
MySimpleParamSimpleQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Char16Method* self,
    MySimpleParamSimpleQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Set_char16Param(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Param)->value = x;
    ((MI_Char16Field*)&self->char16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Char16Method_Clear_char16Param(
    MySimpleParamSimpleQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->char16Param, 0, sizeof(self->char16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8Field uint8Param;
}
MySimpleParamSimpleQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Uint8Method* self,
    MySimpleParamSimpleQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Set_uint8Param(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Param)->value = x;
    ((MI_Uint8Field*)&self->uint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint8Method_Clear_uint8Param(
    MySimpleParamSimpleQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->uint8Param, 0, sizeof(self->uint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8Field sint8Param;
}
MySimpleParamSimpleQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Sint8Method* self,
    MySimpleParamSimpleQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Set_sint8Param(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Param)->value = x;
    ((MI_Sint8Field*)&self->sint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint8Method_Clear_sint8Param(
    MySimpleParamSimpleQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->sint8Param, 0, sizeof(self->sint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16Field uint16Param;
}
MySimpleParamSimpleQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Uint16Method* self,
    MySimpleParamSimpleQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Set_uint16Param(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Param)->value = x;
    ((MI_Uint16Field*)&self->uint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint16Method_Clear_uint16Param(
    MySimpleParamSimpleQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->uint16Param, 0, sizeof(self->uint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16Field sint16Param;
}
MySimpleParamSimpleQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Sint16Method* self,
    MySimpleParamSimpleQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Set_sint16Param(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Param)->value = x;
    ((MI_Sint16Field*)&self->sint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint16Method_Clear_sint16Param(
    MySimpleParamSimpleQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->sint16Param, 0, sizeof(self->sint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32Field uint32Param;
}
MySimpleParamSimpleQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Uint32Method* self,
    MySimpleParamSimpleQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Set_uint32Param(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Param)->value = x;
    ((MI_Uint32Field*)&self->uint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint32Method_Clear_uint32Param(
    MySimpleParamSimpleQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->uint32Param, 0, sizeof(self->uint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32Field sint32Param;
}
MySimpleParamSimpleQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Sint32Method* self,
    MySimpleParamSimpleQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Set_sint32Param(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Param)->value = x;
    ((MI_Sint32Field*)&self->sint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint32Method_Clear_sint32Param(
    MySimpleParamSimpleQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->sint32Param, 0, sizeof(self->sint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64Field uint64Param;
}
MySimpleParamSimpleQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Uint64Method* self,
    MySimpleParamSimpleQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Set_uint64Param(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Param)->value = x;
    ((MI_Uint64Field*)&self->uint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Uint64Method_Clear_uint64Param(
    MySimpleParamSimpleQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->uint64Param, 0, sizeof(self->uint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64Field sint64Param;
}
MySimpleParamSimpleQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Sint64Method* self,
    MySimpleParamSimpleQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Set_sint64Param(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Param)->value = x;
    ((MI_Sint64Field*)&self->sint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Sint64Method_Clear_sint64Param(
    MySimpleParamSimpleQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->sint64Param, 0, sizeof(self->sint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32Field real32Param;
}
MySimpleParamSimpleQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Real32Method* self,
    MySimpleParamSimpleQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Set_real32Param(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Param)->value = x;
    ((MI_Real32Field*)&self->real32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real32Method_Clear_real32Param(
    MySimpleParamSimpleQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->real32Param, 0, sizeof(self->real32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64Field real64Param;
}
MySimpleParamSimpleQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Construct(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Clone(
    const MySimpleParamSimpleQualsMethodsClass_Real64Method* self,
    MySimpleParamSimpleQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Destruct(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Delete(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Post(
    const MySimpleParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Set_real64Param(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Param)->value = x;
    ((MI_Real64Field*)&self->real64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_Real64Method_Clear_real64Param(
    MySimpleParamSimpleQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->real64Param, 0, sizeof(self->real64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamSimpleQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeField datetimeParam;
}
MySimpleParamSimpleQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Construct(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Clone(
    const MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Destruct(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Delete(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Post(
    const MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Set_datetimeParam(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimeParam)->value = x;
    ((MI_DatetimeField*)&self->datetimeParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_Clear_datetimeParam(
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->datetimeParam, 0, sizeof(self->datetimeParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimpleParamSimpleQualsMethodsClass_Self MySimpleParamSimpleQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Load(
    MySimpleParamSimpleQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Unload(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_BooleanMethod(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_StringMethod(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Char16Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Uint8Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Sint8Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Uint16Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Sint16Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Uint32Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Sint32Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Uint64Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Sint64Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Real32Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_Real64Method(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamSimpleQualsMethodsClass_Invoke_DatetimeMethod(
    MySimpleParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamSimpleQualsMethodsClass* instanceName,
    const MySimpleParamSimpleQualsMethodsClass_DatetimeMethod* in);


#endif /* _MySimpleParamSimpleQualsMethodsClass_h */
