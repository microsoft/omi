/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyNoParamSimpleQualsMethodsClass_h
#define _MyNoParamSimpleQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass [MyNoParamSimpleQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass
{
    MI_Instance __instance;
    /* MyNoParamSimpleQualsMethodsClass properties */
}
MyNoParamSimpleQualsMethodsClass;

typedef struct _MyNoParamSimpleQualsMethodsClass_Ref
{
    MyNoParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamSimpleQualsMethodsClass_Ref;

typedef struct _MyNoParamSimpleQualsMethodsClass_ConstRef
{
    MI_CONST MyNoParamSimpleQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamSimpleQualsMethodsClass_ConstRef;

typedef struct _MyNoParamSimpleQualsMethodsClass_Array
{
    struct _MyNoParamSimpleQualsMethodsClass** data;
    MI_Uint32 size;
}
MyNoParamSimpleQualsMethodsClass_Array;

typedef struct _MyNoParamSimpleQualsMethodsClass_ConstArray
{
    struct _MyNoParamSimpleQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyNoParamSimpleQualsMethodsClass_ConstArray;

typedef struct _MyNoParamSimpleQualsMethodsClass_ArrayRef
{
    MyNoParamSimpleQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamSimpleQualsMethodsClass_ArrayRef;

typedef struct _MyNoParamSimpleQualsMethodsClass_ConstArrayRef
{
    MyNoParamSimpleQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamSimpleQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyNoParamSimpleQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Construct(
    MyNoParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyNoParamSimpleQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Clone(
    const MyNoParamSimpleQualsMethodsClass* self,
    MyNoParamSimpleQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyNoParamSimpleQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyNoParamSimpleQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Destruct(MyNoParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Delete(MyNoParamSimpleQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Post(
    const MyNoParamSimpleQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
}
MyNoParamSimpleQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Construct(
    MyNoParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Clone(
    const MyNoParamSimpleQualsMethodsClass_BooleanMethod* self,
    MyNoParamSimpleQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Destruct(
    MyNoParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Delete(
    MyNoParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Post(
    const MyNoParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
MyNoParamSimpleQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Construct(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Clone(
    const MyNoParamSimpleQualsMethodsClass_StringMethod* self,
    MyNoParamSimpleQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Destruct(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Delete(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Post(
    const MyNoParamSimpleQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_StringMethod_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Char16Method* self,
    MyNoParamSimpleQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Char16Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Uint8Method* self,
    MyNoParamSimpleQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Sint8Method* self,
    MyNoParamSimpleQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Uint16Method* self,
    MyNoParamSimpleQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Sint16Method* self,
    MyNoParamSimpleQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Uint32Method* self,
    MyNoParamSimpleQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Sint32Method* self,
    MyNoParamSimpleQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Uint64Method* self,
    MyNoParamSimpleQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Sint64Method* self,
    MyNoParamSimpleQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Real32Method* self,
    MyNoParamSimpleQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real32Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
}
MyNoParamSimpleQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Construct(
    MyNoParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Clone(
    const MyNoParamSimpleQualsMethodsClass_Real64Method* self,
    MyNoParamSimpleQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Destruct(
    MyNoParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Delete(
    MyNoParamSimpleQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Post(
    const MyNoParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_Real64Method_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamSimpleQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
}
MyNoParamSimpleQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Construct(
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Clone(
    const MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Destruct(
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Delete(
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Post(
    const MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamSimpleQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyNoParamSimpleQualsMethodsClass_Self MyNoParamSimpleQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Load(
    MyNoParamSimpleQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Unload(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_BooleanMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_StringMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Char16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint8Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint8Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Real32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Real64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_DatetimeMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_DatetimeMethod* in);


#endif /* _MyNoParamSimpleQualsMethodsClass_h */
