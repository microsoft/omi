/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyNoParamArrayQualsMethodsClass_h
#define _MyNoParamArrayQualsMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass [MyNoParamArrayQualsMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass
{
    MI_Instance __instance;
    /* MyNoParamArrayQualsMethodsClass properties */
}
MyNoParamArrayQualsMethodsClass;

typedef struct _MyNoParamArrayQualsMethodsClass_Ref
{
    MyNoParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamArrayQualsMethodsClass_Ref;

typedef struct _MyNoParamArrayQualsMethodsClass_ConstRef
{
    MI_CONST MyNoParamArrayQualsMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamArrayQualsMethodsClass_ConstRef;

typedef struct _MyNoParamArrayQualsMethodsClass_Array
{
    struct _MyNoParamArrayQualsMethodsClass** data;
    MI_Uint32 size;
}
MyNoParamArrayQualsMethodsClass_Array;

typedef struct _MyNoParamArrayQualsMethodsClass_ConstArray
{
    struct _MyNoParamArrayQualsMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyNoParamArrayQualsMethodsClass_ConstArray;

typedef struct _MyNoParamArrayQualsMethodsClass_ArrayRef
{
    MyNoParamArrayQualsMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamArrayQualsMethodsClass_ArrayRef;

typedef struct _MyNoParamArrayQualsMethodsClass_ConstArrayRef
{
    MyNoParamArrayQualsMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamArrayQualsMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyNoParamArrayQualsMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Construct(
    MyNoParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyNoParamArrayQualsMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Clone(
    const MyNoParamArrayQualsMethodsClass* self,
    MyNoParamArrayQualsMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyNoParamArrayQualsMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyNoParamArrayQualsMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Destruct(MyNoParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Delete(MyNoParamArrayQualsMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Post(
    const MyNoParamArrayQualsMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
}
MyNoParamArrayQualsMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Construct(
    MyNoParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Clone(
    const MyNoParamArrayQualsMethodsClass_BooleanMethod* self,
    MyNoParamArrayQualsMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Destruct(
    MyNoParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Delete(
    MyNoParamArrayQualsMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Post(
    const MyNoParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_BooleanMethod_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
MyNoParamArrayQualsMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Construct(
    MyNoParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Clone(
    const MyNoParamArrayQualsMethodsClass_StringMethod* self,
    MyNoParamArrayQualsMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Destruct(
    MyNoParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Delete(
    MyNoParamArrayQualsMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Post(
    const MyNoParamArrayQualsMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_SetPtr_MIReturn(
    MyNoParamArrayQualsMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_StringMethod_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Construct(
    MyNoParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Char16Method* self,
    MyNoParamArrayQualsMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Delete(
    MyNoParamArrayQualsMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Post(
    const MyNoParamArrayQualsMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Char16Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Construct(
    MyNoParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Uint8Method* self,
    MyNoParamArrayQualsMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Delete(
    MyNoParamArrayQualsMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Post(
    const MyNoParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint8Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Construct(
    MyNoParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Sint8Method* self,
    MyNoParamArrayQualsMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Delete(
    MyNoParamArrayQualsMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Post(
    const MyNoParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint8Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Construct(
    MyNoParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Uint16Method* self,
    MyNoParamArrayQualsMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Delete(
    MyNoParamArrayQualsMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Post(
    const MyNoParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint16Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Construct(
    MyNoParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Sint16Method* self,
    MyNoParamArrayQualsMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Delete(
    MyNoParamArrayQualsMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Post(
    const MyNoParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint16Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Construct(
    MyNoParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Uint32Method* self,
    MyNoParamArrayQualsMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Delete(
    MyNoParamArrayQualsMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Post(
    const MyNoParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint32Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Construct(
    MyNoParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Sint32Method* self,
    MyNoParamArrayQualsMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Delete(
    MyNoParamArrayQualsMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Post(
    const MyNoParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint32Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Construct(
    MyNoParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Uint64Method* self,
    MyNoParamArrayQualsMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Delete(
    MyNoParamArrayQualsMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Post(
    const MyNoParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Uint64Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Construct(
    MyNoParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Sint64Method* self,
    MyNoParamArrayQualsMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Delete(
    MyNoParamArrayQualsMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Post(
    const MyNoParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Sint64Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Construct(
    MyNoParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Real32Method* self,
    MyNoParamArrayQualsMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Delete(
    MyNoParamArrayQualsMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Post(
    const MyNoParamArrayQualsMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real32Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
}
MyNoParamArrayQualsMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Construct(
    MyNoParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Clone(
    const MyNoParamArrayQualsMethodsClass_Real64Method* self,
    MyNoParamArrayQualsMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Destruct(
    MyNoParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Delete(
    MyNoParamArrayQualsMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Post(
    const MyNoParamArrayQualsMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_Real64Method_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamArrayQualsMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
}
MyNoParamArrayQualsMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Construct(
    MyNoParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamArrayQualsMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Clone(
    const MyNoParamArrayQualsMethodsClass_DatetimeMethod* self,
    MyNoParamArrayQualsMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Destruct(
    MyNoParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Delete(
    MyNoParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Post(
    const MyNoParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Set_MIReturn(
    MyNoParamArrayQualsMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamArrayQualsMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyNoParamArrayQualsMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyNoParamArrayQualsMethodsClass_Self MyNoParamArrayQualsMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Load(
    MyNoParamArrayQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Unload(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_BooleanMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_StringMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Char16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint8Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint8Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Real32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Real64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_DatetimeMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_DatetimeMethod* in);


#endif /* _MyNoParamArrayQualsMethodsClass_h */
