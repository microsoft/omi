/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimpleParamArrayQualsMethodsClass_h
#define _MySimpleParamArrayQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass [MySimpleParamArrayQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass
{
    MI_Instance __instance;
    /* MySimpleParamArrayQualsMethodsClass properties */
}
MySimpleParamArrayQualsMethodsClass;

typedef struct _MySimpleParamArrayQualsMethodsClass_Ref
{
    MySimpleParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamArrayQualsMethodsClass_Ref;

typedef struct _MySimpleParamArrayQualsMethodsClass_ConstRef
{
    MI_CONST MySimpleParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamArrayQualsMethodsClass_ConstRef;

typedef struct _MySimpleParamArrayQualsMethodsClass_Array
{
    struct _MySimpleParamArrayQualsMethodsClass** data;
    MI_Uint32 size;
}
MySimpleParamArrayQualsMethodsClass_Array;

typedef struct _MySimpleParamArrayQualsMethodsClass_ConstArray
{
    struct _MySimpleParamArrayQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimpleParamArrayQualsMethodsClass_ConstArray;

typedef struct _MySimpleParamArrayQualsMethodsClass_ArrayRef
{
    MySimpleParamArrayQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamArrayQualsMethodsClass_ArrayRef;

typedef struct _MySimpleParamArrayQualsMethodsClass_ConstArrayRef
{
    MySimpleParamArrayQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamArrayQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimpleParamArrayQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Construct(
    MySimpleParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimpleParamArrayQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Clone(
    const MySimpleParamArrayQualsMethodsClass* self,
    MySimpleParamArrayQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimpleParamArrayQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimpleParamArrayQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Destruct(MySimpleParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Delete(MySimpleParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Post(
    const MySimpleParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanField booleanParam;
}
MySimpleParamArrayQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Construct(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Clone(
    const MySimpleParamArrayQualsMethodsClass_BooleanMethod* self,
    MySimpleParamArrayQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Destruct(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Delete(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Post(
    const MySimpleParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Set_booleanParam(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->booleanParam)->value = x;
    ((MI_BooleanField*)&self->booleanParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_BooleanMethod_Clear_booleanParam(
    MySimpleParamArrayQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->booleanParam, 0, sizeof(self->booleanParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringField stringParam;
}
MySimpleParamArrayQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Construct(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Clone(
    const MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    MySimpleParamArrayQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Destruct(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Delete(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Post(
    const MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Set_stringParam(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_SetPtr_stringParam(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_StringMethod_Clear_stringParam(
    MySimpleParamArrayQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16Field char16Param;
}
MySimpleParamArrayQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Char16Method* self,
    MySimpleParamArrayQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Set_char16Param(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Param)->value = x;
    ((MI_Char16Field*)&self->char16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Char16Method_Clear_char16Param(
    MySimpleParamArrayQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->char16Param, 0, sizeof(self->char16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8Field uint8Param;
}
MySimpleParamArrayQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Uint8Method* self,
    MySimpleParamArrayQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Set_uint8Param(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Param)->value = x;
    ((MI_Uint8Field*)&self->uint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint8Method_Clear_uint8Param(
    MySimpleParamArrayQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->uint8Param, 0, sizeof(self->uint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8Field sint8Param;
}
MySimpleParamArrayQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Sint8Method* self,
    MySimpleParamArrayQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Set_sint8Param(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Param)->value = x;
    ((MI_Sint8Field*)&self->sint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint8Method_Clear_sint8Param(
    MySimpleParamArrayQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->sint8Param, 0, sizeof(self->sint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16Field uint16Param;
}
MySimpleParamArrayQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Uint16Method* self,
    MySimpleParamArrayQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Set_uint16Param(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Param)->value = x;
    ((MI_Uint16Field*)&self->uint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint16Method_Clear_uint16Param(
    MySimpleParamArrayQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->uint16Param, 0, sizeof(self->uint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16Field sint16Param;
}
MySimpleParamArrayQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Sint16Method* self,
    MySimpleParamArrayQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Set_sint16Param(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Param)->value = x;
    ((MI_Sint16Field*)&self->sint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint16Method_Clear_sint16Param(
    MySimpleParamArrayQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->sint16Param, 0, sizeof(self->sint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32Field uint32Param;
}
MySimpleParamArrayQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Uint32Method* self,
    MySimpleParamArrayQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Set_uint32Param(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Param)->value = x;
    ((MI_Uint32Field*)&self->uint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint32Method_Clear_uint32Param(
    MySimpleParamArrayQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->uint32Param, 0, sizeof(self->uint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32Field sint32Param;
}
MySimpleParamArrayQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Sint32Method* self,
    MySimpleParamArrayQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Set_sint32Param(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Param)->value = x;
    ((MI_Sint32Field*)&self->sint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint32Method_Clear_sint32Param(
    MySimpleParamArrayQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->sint32Param, 0, sizeof(self->sint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64Field uint64Param;
}
MySimpleParamArrayQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Uint64Method* self,
    MySimpleParamArrayQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Set_uint64Param(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Param)->value = x;
    ((MI_Uint64Field*)&self->uint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Uint64Method_Clear_uint64Param(
    MySimpleParamArrayQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->uint64Param, 0, sizeof(self->uint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64Field sint64Param;
}
MySimpleParamArrayQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Sint64Method* self,
    MySimpleParamArrayQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Set_sint64Param(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Param)->value = x;
    ((MI_Sint64Field*)&self->sint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Sint64Method_Clear_sint64Param(
    MySimpleParamArrayQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->sint64Param, 0, sizeof(self->sint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32Field real32Param;
}
MySimpleParamArrayQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Real32Method* self,
    MySimpleParamArrayQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Set_real32Param(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Param)->value = x;
    ((MI_Real32Field*)&self->real32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real32Method_Clear_real32Param(
    MySimpleParamArrayQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->real32Param, 0, sizeof(self->real32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64Field real64Param;
}
MySimpleParamArrayQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Construct(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Clone(
    const MySimpleParamArrayQualsMethodsClass_Real64Method* self,
    MySimpleParamArrayQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Destruct(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Delete(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Post(
    const MySimpleParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Set_real64Param(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Param)->value = x;
    ((MI_Real64Field*)&self->real64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_Real64Method_Clear_real64Param(
    MySimpleParamArrayQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->real64Param, 0, sizeof(self->real64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamArrayQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeField datetimeParam;
}
MySimpleParamArrayQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Construct(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Clone(
    const MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self,
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Destruct(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Delete(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Post(
    const MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Set_datetimeParam(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimeParam)->value = x;
    ((MI_DatetimeField*)&self->datetimeParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamArrayQualsMethodsClass_DatetimeMethod_Clear_datetimeParam(
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->datetimeParam, 0, sizeof(self->datetimeParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimpleParamArrayQualsMethodsClass_Self MySimpleParamArrayQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Load(
    MySimpleParamArrayQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Unload(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_BooleanMethod(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_StringMethod(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Char16Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Uint8Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Sint8Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Uint16Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Sint16Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Uint32Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Sint32Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Uint64Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Sint64Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Real32Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_Real64Method(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MySimpleParamArrayQualsMethodsClass_Invoke_DatetimeMethod(
    MySimpleParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamArrayQualsMethodsClass* instanceName,
    const MySimpleParamArrayQualsMethodsClass_DatetimeMethod* in);


#endif /* _MySimpleParamArrayQualsMethodsClass_h */
