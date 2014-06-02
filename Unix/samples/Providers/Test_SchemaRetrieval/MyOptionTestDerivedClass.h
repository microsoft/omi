/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyOptionTestDerivedClass_h
#define _MyOptionTestDerivedClass_h

#include <MI.h>
#include "MyOptionTestClass.h"

/*
**==============================================================================
**
** MyOptionTestDerivedClass [MyOptionTestDerivedClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyOptionTestDerivedClass /* extends MyOptionTestClass */
{
    MI_Instance __instance;
    /* MyOptionTestClass properties */
    MI_ConstUint8Field uint8Prop;
    MI_ConstUint64AField uint64ArrayProp;
    MI_ConstSint8Field sint8PropWithSimpleQual;
    MI_ConstUint32Field uint32PropWithArrayQual;
    /* MyOptionTestDerivedClass properties */
    MI_ConstUint8Field uint8Property;
    MI_ConstUint64AField uint64ArrayProperty;
}
MyOptionTestDerivedClass;

typedef struct _MyOptionTestDerivedClass_Ref
{
    MyOptionTestDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestDerivedClass_Ref;

typedef struct _MyOptionTestDerivedClass_ConstRef
{
    MI_CONST MyOptionTestDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestDerivedClass_ConstRef;

typedef struct _MyOptionTestDerivedClass_Array
{
    struct _MyOptionTestDerivedClass** data;
    MI_Uint32 size;
}
MyOptionTestDerivedClass_Array;

typedef struct _MyOptionTestDerivedClass_ConstArray
{
    struct _MyOptionTestDerivedClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyOptionTestDerivedClass_ConstArray;

typedef struct _MyOptionTestDerivedClass_ArrayRef
{
    MyOptionTestDerivedClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestDerivedClass_ArrayRef;

typedef struct _MyOptionTestDerivedClass_ConstArrayRef
{
    MyOptionTestDerivedClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestDerivedClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyOptionTestDerivedClass_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Construct(
    MyOptionTestDerivedClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyOptionTestDerivedClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clone(
    const MyOptionTestDerivedClass* self,
    MyOptionTestDerivedClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyOptionTestDerivedClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyOptionTestDerivedClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Destruct(MyOptionTestDerivedClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Delete(MyOptionTestDerivedClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Post(
    const MyOptionTestDerivedClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_uint8Prop(
    MyOptionTestDerivedClass* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Prop)->value = x;
    ((MI_Uint8Field*)&self->uint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_uint8Prop(
    MyOptionTestDerivedClass* self)
{
    memset((void*)&self->uint8Prop, 0, sizeof(self->uint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_uint64ArrayProp(
    MyOptionTestDerivedClass* self,
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

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_SetPtr_uint64ArrayProp(
    MyOptionTestDerivedClass* self,
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

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_uint64ArrayProp(
    MyOptionTestDerivedClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_sint8PropWithSimpleQual(
    MyOptionTestDerivedClass* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8PropWithSimpleQual)->value = x;
    ((MI_Sint8Field*)&self->sint8PropWithSimpleQual)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_sint8PropWithSimpleQual(
    MyOptionTestDerivedClass* self)
{
    memset((void*)&self->sint8PropWithSimpleQual, 0, sizeof(self->sint8PropWithSimpleQual));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_uint32PropWithArrayQual(
    MyOptionTestDerivedClass* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32PropWithArrayQual)->value = x;
    ((MI_Uint32Field*)&self->uint32PropWithArrayQual)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_uint32PropWithArrayQual(
    MyOptionTestDerivedClass* self)
{
    memset((void*)&self->uint32PropWithArrayQual, 0, sizeof(self->uint32PropWithArrayQual));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_uint8Property(
    MyOptionTestDerivedClass* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Property)->value = x;
    ((MI_Uint8Field*)&self->uint8Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_uint8Property(
    MyOptionTestDerivedClass* self)
{
    memset((void*)&self->uint8Property, 0, sizeof(self->uint8Property));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Set_uint64ArrayProperty(
    MyOptionTestDerivedClass* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_SetPtr_uint64ArrayProperty(
    MyOptionTestDerivedClass* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Clear_uint64ArrayProperty(
    MyOptionTestDerivedClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** MyOptionTestDerivedClass.Uint32EmptyParamMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestDerivedClass_Uint32EmptyParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyOptionTestDerivedClass_Uint32EmptyParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestDerivedClass_Uint32EmptyParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Construct(
    MyOptionTestDerivedClass_Uint32EmptyParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestDerivedClass_Uint32EmptyParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Clone(
    const MyOptionTestDerivedClass_Uint32EmptyParamMethod* self,
    MyOptionTestDerivedClass_Uint32EmptyParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Destruct(
    MyOptionTestDerivedClass_Uint32EmptyParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Delete(
    MyOptionTestDerivedClass_Uint32EmptyParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Post(
    const MyOptionTestDerivedClass_Uint32EmptyParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Set_MIReturn(
    MyOptionTestDerivedClass_Uint32EmptyParamMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Uint32EmptyParamMethod_Clear_MIReturn(
    MyOptionTestDerivedClass_Uint32EmptyParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestDerivedClass.Sint64SimpleParamsMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestDerivedClass_Sint64SimpleParamsMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
    /*IN*/ MI_ConstUint16Field param1;
    /*OUT*/ MI_ConstSint16Field param2;
MI_ConstStringField param3;
}
MyOptionTestDerivedClass_Sint64SimpleParamsMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Construct(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Clone(
    const MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Destruct(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Delete(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Post(
    const MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Set_MIReturn(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Clear_MIReturn(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Set_param1(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->param1)->value = x;
    ((MI_Uint16Field*)&self->param1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Clear_param1(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->param1, 0, sizeof(self->param1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Set_param2(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->param2)->value = x;
    ((MI_Sint16Field*)&self->param2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Clear_param2(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->param2, 0, sizeof(self->param2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Set_param3(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_SetPtr_param3(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_Sint64SimpleParamsMethod_Clear_param3(
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MyOptionTestDerivedClass.MultiQualMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestDerivedClass_MultiQualMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64Field inputParam;
    /*OUT*/ MI_ConstUint64Field outputParam;
}
MyOptionTestDerivedClass_MultiQualMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestDerivedClass_MultiQualMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Construct(
    MyOptionTestDerivedClass_MultiQualMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestDerivedClass_MultiQualMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Clone(
    const MyOptionTestDerivedClass_MultiQualMethod* self,
    MyOptionTestDerivedClass_MultiQualMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Destruct(
    MyOptionTestDerivedClass_MultiQualMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Delete(
    MyOptionTestDerivedClass_MultiQualMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Post(
    const MyOptionTestDerivedClass_MultiQualMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Set_MIReturn(
    MyOptionTestDerivedClass_MultiQualMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Clear_MIReturn(
    MyOptionTestDerivedClass_MultiQualMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Set_inputParam(
    MyOptionTestDerivedClass_MultiQualMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->inputParam)->value = x;
    ((MI_Uint64Field*)&self->inputParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Clear_inputParam(
    MyOptionTestDerivedClass_MultiQualMethod* self)
{
    memset((void*)&self->inputParam, 0, sizeof(self->inputParam));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Set_outputParam(
    MyOptionTestDerivedClass_MultiQualMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->outputParam)->value = x;
    ((MI_Uint64Field*)&self->outputParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MultiQualMethod_Clear_outputParam(
    MyOptionTestDerivedClass_MultiQualMethod* self)
{
    memset((void*)&self->outputParam, 0, sizeof(self->outputParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestDerivedClass.MyMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestDerivedClass_MyMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32Field input;
}
MyOptionTestDerivedClass_MyMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestDerivedClass_MyMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Construct(
    MyOptionTestDerivedClass_MyMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestDerivedClass_MyMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Clone(
    const MyOptionTestDerivedClass_MyMethod* self,
    MyOptionTestDerivedClass_MyMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Destruct(
    MyOptionTestDerivedClass_MyMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Delete(
    MyOptionTestDerivedClass_MyMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Post(
    const MyOptionTestDerivedClass_MyMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Set_MIReturn(
    MyOptionTestDerivedClass_MyMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Clear_MIReturn(
    MyOptionTestDerivedClass_MyMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Set_input(
    MyOptionTestDerivedClass_MyMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->input)->value = x;
    ((MI_Uint32Field*)&self->input)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestDerivedClass_MyMethod_Clear_input(
    MyOptionTestDerivedClass_MyMethod* self)
{
    memset((void*)&self->input, 0, sizeof(self->input));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestDerivedClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyOptionTestDerivedClass_Self MyOptionTestDerivedClass_Self;

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Load(
    MyOptionTestDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Unload(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Invoke_Uint32EmptyParamMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_Uint32EmptyParamMethod* in);

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Invoke_Sint64SimpleParamsMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_Sint64SimpleParamsMethod* in);

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Invoke_MultiQualMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_MultiQualMethod* in);

MI_EXTERN_C void MI_CALL MyOptionTestDerivedClass_Invoke_MyMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_MyMethod* in);


#endif /* _MyOptionTestDerivedClass_h */
