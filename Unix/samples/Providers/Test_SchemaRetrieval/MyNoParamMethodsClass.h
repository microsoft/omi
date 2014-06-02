/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyNoParamMethodsClass_h
#define _MyNoParamMethodsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyNoParamMethodsClass [MyNoParamMethodsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass
{
    MI_Instance __instance;
    /* MyNoParamMethodsClass properties */
}
MyNoParamMethodsClass;

typedef struct _MyNoParamMethodsClass_Ref
{
    MyNoParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamMethodsClass_Ref;

typedef struct _MyNoParamMethodsClass_ConstRef
{
    MI_CONST MyNoParamMethodsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamMethodsClass_ConstRef;

typedef struct _MyNoParamMethodsClass_Array
{
    struct _MyNoParamMethodsClass** data;
    MI_Uint32 size;
}
MyNoParamMethodsClass_Array;

typedef struct _MyNoParamMethodsClass_ConstArray
{
    struct _MyNoParamMethodsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyNoParamMethodsClass_ConstArray;

typedef struct _MyNoParamMethodsClass_ArrayRef
{
    MyNoParamMethodsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamMethodsClass_ArrayRef;

typedef struct _MyNoParamMethodsClass_ConstArrayRef
{
    MyNoParamMethodsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyNoParamMethodsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyNoParamMethodsClass_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Construct(
    MyNoParamMethodsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyNoParamMethodsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Clone(
    const MyNoParamMethodsClass* self,
    MyNoParamMethodsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyNoParamMethodsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyNoParamMethodsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Destruct(MyNoParamMethodsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Delete(MyNoParamMethodsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Post(
    const MyNoParamMethodsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.BooleanMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_BooleanMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
}
MyNoParamMethodsClass_BooleanMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_BooleanMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Construct(
    MyNoParamMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_BooleanMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Clone(
    const MyNoParamMethodsClass_BooleanMethod* self,
    MyNoParamMethodsClass_BooleanMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Destruct(
    MyNoParamMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Delete(
    MyNoParamMethodsClass_BooleanMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Post(
    const MyNoParamMethodsClass_BooleanMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Set_MIReturn(
    MyNoParamMethodsClass_BooleanMethod* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_BooleanMethod_Clear_MIReturn(
    MyNoParamMethodsClass_BooleanMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.StringMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_StringMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
}
MyNoParamMethodsClass_StringMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_StringMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Construct(
    MyNoParamMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_StringMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Clone(
    const MyNoParamMethodsClass_StringMethod* self,
    MyNoParamMethodsClass_StringMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Destruct(
    MyNoParamMethodsClass_StringMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Delete(
    MyNoParamMethodsClass_StringMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Post(
    const MyNoParamMethodsClass_StringMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Set_MIReturn(
    MyNoParamMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_SetPtr_MIReturn(
    MyNoParamMethodsClass_StringMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_StringMethod_Clear_MIReturn(
    MyNoParamMethodsClass_StringMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Char16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Char16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstChar16Field MIReturn;
}
MyNoParamMethodsClass_Char16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Char16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Construct(
    MyNoParamMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Char16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Clone(
    const MyNoParamMethodsClass_Char16Method* self,
    MyNoParamMethodsClass_Char16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Destruct(
    MyNoParamMethodsClass_Char16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Delete(
    MyNoParamMethodsClass_Char16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Post(
    const MyNoParamMethodsClass_Char16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Set_MIReturn(
    MyNoParamMethodsClass_Char16Method* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->MIReturn)->value = x;
    ((MI_Char16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Char16Method_Clear_MIReturn(
    MyNoParamMethodsClass_Char16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Uint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Uint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint8Field MIReturn;
}
MyNoParamMethodsClass_Uint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Construct(
    MyNoParamMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Uint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Clone(
    const MyNoParamMethodsClass_Uint8Method* self,
    MyNoParamMethodsClass_Uint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Destruct(
    MyNoParamMethodsClass_Uint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Delete(
    MyNoParamMethodsClass_Uint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Post(
    const MyNoParamMethodsClass_Uint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Set_MIReturn(
    MyNoParamMethodsClass_Uint8Method* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->MIReturn)->value = x;
    ((MI_Uint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint8Method_Clear_MIReturn(
    MyNoParamMethodsClass_Uint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Sint8Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Sint8Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint8Field MIReturn;
}
MyNoParamMethodsClass_Sint8Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint8Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Construct(
    MyNoParamMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Sint8Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Clone(
    const MyNoParamMethodsClass_Sint8Method* self,
    MyNoParamMethodsClass_Sint8Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Destruct(
    MyNoParamMethodsClass_Sint8Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Delete(
    MyNoParamMethodsClass_Sint8Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Post(
    const MyNoParamMethodsClass_Sint8Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Set_MIReturn(
    MyNoParamMethodsClass_Sint8Method* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->MIReturn)->value = x;
    ((MI_Sint8Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint8Method_Clear_MIReturn(
    MyNoParamMethodsClass_Sint8Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Uint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Uint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint16Field MIReturn;
}
MyNoParamMethodsClass_Uint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Construct(
    MyNoParamMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Uint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Clone(
    const MyNoParamMethodsClass_Uint16Method* self,
    MyNoParamMethodsClass_Uint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Destruct(
    MyNoParamMethodsClass_Uint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Delete(
    MyNoParamMethodsClass_Uint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Post(
    const MyNoParamMethodsClass_Uint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Set_MIReturn(
    MyNoParamMethodsClass_Uint16Method* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MIReturn)->value = x;
    ((MI_Uint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint16Method_Clear_MIReturn(
    MyNoParamMethodsClass_Uint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Sint16Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Sint16Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint16Field MIReturn;
}
MyNoParamMethodsClass_Sint16Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint16Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Construct(
    MyNoParamMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Sint16Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Clone(
    const MyNoParamMethodsClass_Sint16Method* self,
    MyNoParamMethodsClass_Sint16Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Destruct(
    MyNoParamMethodsClass_Sint16Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Delete(
    MyNoParamMethodsClass_Sint16Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Post(
    const MyNoParamMethodsClass_Sint16Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Set_MIReturn(
    MyNoParamMethodsClass_Sint16Method* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->MIReturn)->value = x;
    ((MI_Sint16Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint16Method_Clear_MIReturn(
    MyNoParamMethodsClass_Sint16Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Uint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Uint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyNoParamMethodsClass_Uint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Construct(
    MyNoParamMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Uint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Clone(
    const MyNoParamMethodsClass_Uint32Method* self,
    MyNoParamMethodsClass_Uint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Destruct(
    MyNoParamMethodsClass_Uint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Delete(
    MyNoParamMethodsClass_Uint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Post(
    const MyNoParamMethodsClass_Uint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Set_MIReturn(
    MyNoParamMethodsClass_Uint32Method* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint32Method_Clear_MIReturn(
    MyNoParamMethodsClass_Uint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Sint32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Sint32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint32Field MIReturn;
}
MyNoParamMethodsClass_Sint32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Construct(
    MyNoParamMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Sint32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Clone(
    const MyNoParamMethodsClass_Sint32Method* self,
    MyNoParamMethodsClass_Sint32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Destruct(
    MyNoParamMethodsClass_Sint32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Delete(
    MyNoParamMethodsClass_Sint32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Post(
    const MyNoParamMethodsClass_Sint32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Set_MIReturn(
    MyNoParamMethodsClass_Sint32Method* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MIReturn)->value = x;
    ((MI_Sint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint32Method_Clear_MIReturn(
    MyNoParamMethodsClass_Sint32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Uint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Uint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
}
MyNoParamMethodsClass_Uint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Construct(
    MyNoParamMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Uint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Clone(
    const MyNoParamMethodsClass_Uint64Method* self,
    MyNoParamMethodsClass_Uint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Destruct(
    MyNoParamMethodsClass_Uint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Delete(
    MyNoParamMethodsClass_Uint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Post(
    const MyNoParamMethodsClass_Uint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Set_MIReturn(
    MyNoParamMethodsClass_Uint64Method* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Uint64Method_Clear_MIReturn(
    MyNoParamMethodsClass_Uint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Sint64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Sint64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
}
MyNoParamMethodsClass_Sint64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Construct(
    MyNoParamMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Sint64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Clone(
    const MyNoParamMethodsClass_Sint64Method* self,
    MyNoParamMethodsClass_Sint64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Destruct(
    MyNoParamMethodsClass_Sint64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Delete(
    MyNoParamMethodsClass_Sint64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Post(
    const MyNoParamMethodsClass_Sint64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Set_MIReturn(
    MyNoParamMethodsClass_Sint64Method* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Sint64Method_Clear_MIReturn(
    MyNoParamMethodsClass_Sint64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Real32Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Real32Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal32Field MIReturn;
}
MyNoParamMethodsClass_Real32Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Real32Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Construct(
    MyNoParamMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Real32Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Clone(
    const MyNoParamMethodsClass_Real32Method* self,
    MyNoParamMethodsClass_Real32Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Destruct(
    MyNoParamMethodsClass_Real32Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Delete(
    MyNoParamMethodsClass_Real32Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Post(
    const MyNoParamMethodsClass_Real32Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Set_MIReturn(
    MyNoParamMethodsClass_Real32Method* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->MIReturn)->value = x;
    ((MI_Real32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real32Method_Clear_MIReturn(
    MyNoParamMethodsClass_Real32Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.Real64Method()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_Real64Method
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstReal64Field MIReturn;
}
MyNoParamMethodsClass_Real64Method;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_Real64Method_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Construct(
    MyNoParamMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_Real64Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Clone(
    const MyNoParamMethodsClass_Real64Method* self,
    MyNoParamMethodsClass_Real64Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Destruct(
    MyNoParamMethodsClass_Real64Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Delete(
    MyNoParamMethodsClass_Real64Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Post(
    const MyNoParamMethodsClass_Real64Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Set_MIReturn(
    MyNoParamMethodsClass_Real64Method* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->MIReturn)->value = x;
    ((MI_Real64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_Real64Method_Clear_MIReturn(
    MyNoParamMethodsClass_Real64Method* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass.DatetimeMethod()
**
**==============================================================================
*/

typedef struct _MyNoParamMethodsClass_DatetimeMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstDatetimeField MIReturn;
}
MyNoParamMethodsClass_DatetimeMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyNoParamMethodsClass_DatetimeMethod_rtti;

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Construct(
    MyNoParamMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyNoParamMethodsClass_DatetimeMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Clone(
    const MyNoParamMethodsClass_DatetimeMethod* self,
    MyNoParamMethodsClass_DatetimeMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Destruct(
    MyNoParamMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Delete(
    MyNoParamMethodsClass_DatetimeMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Post(
    const MyNoParamMethodsClass_DatetimeMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Set_MIReturn(
    MyNoParamMethodsClass_DatetimeMethod* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MIReturn)->value = x;
    ((MI_DatetimeField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyNoParamMethodsClass_DatetimeMethod_Clear_MIReturn(
    MyNoParamMethodsClass_DatetimeMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyNoParamMethodsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyNoParamMethodsClass_Self MyNoParamMethodsClass_Self;

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Load(
    MyNoParamMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Unload(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_BooleanMethod(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_BooleanMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_StringMethod(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_StringMethod* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Char16Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Char16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Uint8Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Uint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Sint8Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Sint8Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Uint16Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Uint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Sint16Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Sint16Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Uint32Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Uint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Sint32Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Sint32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Uint64Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Uint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Sint64Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Sint64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Real32Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Real32Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_Real64Method(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_Real64Method* in);

MI_EXTERN_C void MI_CALL MyNoParamMethodsClass_Invoke_DatetimeMethod(
    MyNoParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamMethodsClass* instanceName,
    const MyNoParamMethodsClass_DatetimeMethod* in);


#endif /* _MyNoParamMethodsClass_h */
