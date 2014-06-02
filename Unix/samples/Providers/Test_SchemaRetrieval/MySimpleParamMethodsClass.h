/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimpleParamMethodsClass_h
#define _MySimpleParamMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimpleParamMethodsClass [MySimpleParamMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass
{
    MI_Instance __instance;
    /* MySimpleParamMethodsClass properties */
}
MySimpleParamMethodsClass;

typedef struct _MySimpleParamMethodsClass_Ref
{
    MySimpleParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamMethodsClass_Ref;

typedef struct _MySimpleParamMethodsClass_ConstRef
{
    MI_CONST MySimpleParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamMethodsClass_ConstRef;

typedef struct _MySimpleParamMethodsClass_Array
{
    struct _MySimpleParamMethodsClass** data;
    MI_Uint32 size;
}
MySimpleParamMethodsClass_Array;

typedef struct _MySimpleParamMethodsClass_ConstArray
{
    struct _MySimpleParamMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimpleParamMethodsClass_ConstArray;

typedef struct _MySimpleParamMethodsClass_ArrayRef
{
    MySimpleParamMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamMethodsClass_ArrayRef;

typedef struct _MySimpleParamMethodsClass_ConstArrayRef
{
    MySimpleParamMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleParamMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimpleParamMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Construct(
    MySimpleParamMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimpleParamMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Clone(
    const MySimpleParamMethodsClass* self,
    MySimpleParamMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimpleParamMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimpleParamMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Destruct(MySimpleParamMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Delete(MySimpleParamMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Post(
    const MySimpleParamMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.BooleanSimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_BooleanSimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
MI_ConstBooleanField booleanParam;
}
MySimpleParamMethodsClass_BooleanSimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_BooleanSimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Construct(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_BooleanSimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_BooleanSimpleParamMethod* self,
    MySimpleParamMethodsClass_BooleanSimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Delete(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Post(
    const MySimpleParamMethodsClass_BooleanSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Set_booleanParam(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->booleanParam)->value = x;
    ((MI_BooleanField*)&self->booleanParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_BooleanSimpleParamMethod_Clear_booleanParam(
    MySimpleParamMethodsClass_BooleanSimpleParamMethod* self)
{
    memset((void*)&self->booleanParam, 0, sizeof(self->booleanParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.StringSimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_StringSimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstStringField stringParam;
}
MySimpleParamMethodsClass_StringSimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_StringSimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Construct(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_StringSimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    MySimpleParamMethodsClass_StringSimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Delete(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Post(
    const MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_SetPtr_MIReturn(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Set_stringParam(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_SetPtr_stringParam(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_StringSimpleParamMethod_Clear_stringParam(
    MySimpleParamMethodsClass_StringSimpleParamMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Char16SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Char16SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
MI_ConstChar16Field char16Param;
}
MySimpleParamMethodsClass_Char16SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Char16SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Char16SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Char16SimpleParamMethod* self,
    MySimpleParamMethodsClass_Char16SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Char16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Set_char16Param(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Param)->value = x;
    ((MI_Char16Field*)&self->char16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Char16SimpleParamMethod_Clear_char16Param(
    MySimpleParamMethodsClass_Char16SimpleParamMethod* self)
{
    memset((void*)&self->char16Param, 0, sizeof(self->char16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Uint8SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Uint8SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
MI_ConstUint8Field uint8Param;
}
MySimpleParamMethodsClass_Uint8SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint8SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Uint8SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Uint8SimpleParamMethod* self,
    MySimpleParamMethodsClass_Uint8SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Uint8SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Set_uint8Param(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Param)->value = x;
    ((MI_Uint8Field*)&self->uint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint8SimpleParamMethod_Clear_uint8Param(
    MySimpleParamMethodsClass_Uint8SimpleParamMethod* self)
{
    memset((void*)&self->uint8Param, 0, sizeof(self->uint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Sint8SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Sint8SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
MI_ConstSint8Field sint8Param;
}
MySimpleParamMethodsClass_Sint8SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint8SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Sint8SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Sint8SimpleParamMethod* self,
    MySimpleParamMethodsClass_Sint8SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Sint8SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Set_sint8Param(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Param)->value = x;
    ((MI_Sint8Field*)&self->sint8Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint8SimpleParamMethod_Clear_sint8Param(
    MySimpleParamMethodsClass_Sint8SimpleParamMethod* self)
{
    memset((void*)&self->sint8Param, 0, sizeof(self->sint8Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Uint16SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Uint16SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
MI_ConstUint16Field uint16Param;
}
MySimpleParamMethodsClass_Uint16SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint16SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Uint16SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Uint16SimpleParamMethod* self,
    MySimpleParamMethodsClass_Uint16SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Uint16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Set_uint16Param(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Param)->value = x;
    ((MI_Uint16Field*)&self->uint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint16SimpleParamMethod_Clear_uint16Param(
    MySimpleParamMethodsClass_Uint16SimpleParamMethod* self)
{
    memset((void*)&self->uint16Param, 0, sizeof(self->uint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Sint16SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Sint16SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
MI_ConstSint16Field sint16Param;
}
MySimpleParamMethodsClass_Sint16SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint16SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Sint16SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Sint16SimpleParamMethod* self,
    MySimpleParamMethodsClass_Sint16SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Sint16SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Set_sint16Param(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Param)->value = x;
    ((MI_Sint16Field*)&self->sint16Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint16SimpleParamMethod_Clear_sint16Param(
    MySimpleParamMethodsClass_Sint16SimpleParamMethod* self)
{
    memset((void*)&self->sint16Param, 0, sizeof(self->sint16Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Uint32SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Uint32SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32Field uint32Param;
}
MySimpleParamMethodsClass_Uint32SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint32SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Uint32SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Uint32SimpleParamMethod* self,
    MySimpleParamMethodsClass_Uint32SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Uint32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Set_uint32Param(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Param)->value = x;
    ((MI_Uint32Field*)&self->uint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint32SimpleParamMethod_Clear_uint32Param(
    MySimpleParamMethodsClass_Uint32SimpleParamMethod* self)
{
    memset((void*)&self->uint32Param, 0, sizeof(self->uint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Sint32SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Sint32SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
MI_ConstSint32Field sint32Param;
}
MySimpleParamMethodsClass_Sint32SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint32SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Sint32SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Sint32SimpleParamMethod* self,
    MySimpleParamMethodsClass_Sint32SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Sint32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Set_sint32Param(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Param)->value = x;
    ((MI_Sint32Field*)&self->sint32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint32SimpleParamMethod_Clear_sint32Param(
    MySimpleParamMethodsClass_Sint32SimpleParamMethod* self)
{
    memset((void*)&self->sint32Param, 0, sizeof(self->sint32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Uint64SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Uint64SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
MI_ConstUint64Field uint64Param;
}
MySimpleParamMethodsClass_Uint64SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint64SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Uint64SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Uint64SimpleParamMethod* self,
    MySimpleParamMethodsClass_Uint64SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Uint64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Set_uint64Param(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Param)->value = x;
    ((MI_Uint64Field*)&self->uint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Uint64SimpleParamMethod_Clear_uint64Param(
    MySimpleParamMethodsClass_Uint64SimpleParamMethod* self)
{
    memset((void*)&self->uint64Param, 0, sizeof(self->uint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Sint64SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Sint64SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
MI_ConstSint64Field sint64Param;
}
MySimpleParamMethodsClass_Sint64SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint64SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Sint64SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Sint64SimpleParamMethod* self,
    MySimpleParamMethodsClass_Sint64SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Sint64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Set_sint64Param(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Param)->value = x;
    ((MI_Sint64Field*)&self->sint64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Sint64SimpleParamMethod_Clear_sint64Param(
    MySimpleParamMethodsClass_Sint64SimpleParamMethod* self)
{
    memset((void*)&self->sint64Param, 0, sizeof(self->sint64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Real32SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Real32SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
MI_ConstReal32Field real32Param;
}
MySimpleParamMethodsClass_Real32SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Real32SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Real32SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Real32SimpleParamMethod* self,
    MySimpleParamMethodsClass_Real32SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Real32SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Set_real32Param(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Param)->value = x;
    ((MI_Real32Field*)&self->real32Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real32SimpleParamMethod_Clear_real32Param(
    MySimpleParamMethodsClass_Real32SimpleParamMethod* self)
{
    memset((void*)&self->real32Param, 0, sizeof(self->real32Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.Real64SimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_Real64SimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
MI_ConstReal64Field real64Param;
}
MySimpleParamMethodsClass_Real64SimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Real64SimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Construct(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_Real64SimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_Real64SimpleParamMethod* self,
    MySimpleParamMethodsClass_Real64SimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Delete(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Post(
    const MySimpleParamMethodsClass_Real64SimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Set_real64Param(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Param)->value = x;
    ((MI_Real64Field*)&self->real64Param)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_Real64SimpleParamMethod_Clear_real64Param(
    MySimpleParamMethodsClass_Real64SimpleParamMethod* self)
{
    memset((void*)&self->real64Param, 0, sizeof(self->real64Param));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass.DatetimeSimpleParamMethod()
**
**==============================================================================
*/

typedef struct _MySimpleParamMethodsClass_DatetimeSimpleParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
MI_ConstDatetimeField datetimeParam;
}
MySimpleParamMethodsClass_DatetimeSimpleParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MySimpleParamMethodsClass_DatetimeSimpleParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Construct(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySimpleParamMethodsClass_DatetimeSimpleParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Clone(
    const MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self,
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Destruct(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Delete(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Post(
    const MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Set_MIReturn(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Clear_MIReturn(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Set_datetimeParam(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimeParam)->value = x;
    ((MI_DatetimeField*)&self->datetimeParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimpleParamMethodsClass_DatetimeSimpleParamMethod_Clear_datetimeParam(
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod* self)
{
    memset((void*)&self->datetimeParam, 0, sizeof(self->datetimeParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimpleParamMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimpleParamMethodsClass_Self MySimpleParamMethodsClass_Self;

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Load(
    MySimpleParamMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Unload(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_BooleanSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_BooleanSimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_StringSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_StringSimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Char16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Char16SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Uint8SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint8SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Sint8SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint8SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Uint16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint16SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Sint16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint16SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Uint32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint32SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Sint32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint32SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Uint64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint64SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Sint64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint64SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Real32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Real32SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_Real64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Real64SimpleParamMethod* in);

MI_EXTERN_C void MI_CALL MySimpleParamMethodsClass_Invoke_DatetimeSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_DatetimeSimpleParamMethod* in);


#endif /* _MySimpleParamMethodsClass_h */
