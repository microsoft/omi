/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyOptionTestClass_h
#define _MyOptionTestClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyOptionTestClass [MyOptionTestClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyOptionTestClass
{
    MI_Instance __instance;
    /* MyOptionTestClass properties */
    MI_ConstUint8Field uint8Prop;
    MI_ConstUint64AField uint64ArrayProp;
    MI_ConstSint8Field sint8PropWithSimpleQual;
    MI_ConstUint32Field uint32PropWithArrayQual;
}
MyOptionTestClass;

typedef struct _MyOptionTestClass_Ref
{
    MyOptionTestClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestClass_Ref;

typedef struct _MyOptionTestClass_ConstRef
{
    MI_CONST MyOptionTestClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestClass_ConstRef;

typedef struct _MyOptionTestClass_Array
{
    struct _MyOptionTestClass** data;
    MI_Uint32 size;
}
MyOptionTestClass_Array;

typedef struct _MyOptionTestClass_ConstArray
{
    struct _MyOptionTestClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyOptionTestClass_ConstArray;

typedef struct _MyOptionTestClass_ArrayRef
{
    MyOptionTestClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestClass_ArrayRef;

typedef struct _MyOptionTestClass_ConstArrayRef
{
    MyOptionTestClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyOptionTestClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyOptionTestClass_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Construct(
    MyOptionTestClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyOptionTestClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Clone(
    const MyOptionTestClass* self,
    MyOptionTestClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyOptionTestClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyOptionTestClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Destruct(MyOptionTestClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Delete(MyOptionTestClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Post(
    const MyOptionTestClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Set_uint8Prop(
    MyOptionTestClass* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Prop)->value = x;
    ((MI_Uint8Field*)&self->uint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Clear_uint8Prop(
    MyOptionTestClass* self)
{
    memset((void*)&self->uint8Prop, 0, sizeof(self->uint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Set_uint64ArrayProp(
    MyOptionTestClass* self,
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

MI_INLINE MI_Result MI_CALL MyOptionTestClass_SetPtr_uint64ArrayProp(
    MyOptionTestClass* self,
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

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Clear_uint64ArrayProp(
    MyOptionTestClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Set_sint8PropWithSimpleQual(
    MyOptionTestClass* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8PropWithSimpleQual)->value = x;
    ((MI_Sint8Field*)&self->sint8PropWithSimpleQual)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Clear_sint8PropWithSimpleQual(
    MyOptionTestClass* self)
{
    memset((void*)&self->sint8PropWithSimpleQual, 0, sizeof(self->sint8PropWithSimpleQual));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Set_uint32PropWithArrayQual(
    MyOptionTestClass* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32PropWithArrayQual)->value = x;
    ((MI_Uint32Field*)&self->uint32PropWithArrayQual)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Clear_uint32PropWithArrayQual(
    MyOptionTestClass* self)
{
    memset((void*)&self->uint32PropWithArrayQual, 0, sizeof(self->uint32PropWithArrayQual));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestClass.Uint32EmptyParamMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestClass_Uint32EmptyParamMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MyOptionTestClass_Uint32EmptyParamMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestClass_Uint32EmptyParamMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Construct(
    MyOptionTestClass_Uint32EmptyParamMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestClass_Uint32EmptyParamMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Clone(
    const MyOptionTestClass_Uint32EmptyParamMethod* self,
    MyOptionTestClass_Uint32EmptyParamMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Destruct(
    MyOptionTestClass_Uint32EmptyParamMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Delete(
    MyOptionTestClass_Uint32EmptyParamMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Post(
    const MyOptionTestClass_Uint32EmptyParamMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Set_MIReturn(
    MyOptionTestClass_Uint32EmptyParamMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Uint32EmptyParamMethod_Clear_MIReturn(
    MyOptionTestClass_Uint32EmptyParamMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestClass.Sint64SimpleParamsMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestClass_Sint64SimpleParamsMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
    /*IN*/ MI_ConstUint16Field param1;
    /*OUT*/ MI_ConstSint16Field param2;
}
MyOptionTestClass_Sint64SimpleParamsMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestClass_Sint64SimpleParamsMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Construct(
    MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestClass_Sint64SimpleParamsMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Clone(
    const MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MyOptionTestClass_Sint64SimpleParamsMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Destruct(
    MyOptionTestClass_Sint64SimpleParamsMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Delete(
    MyOptionTestClass_Sint64SimpleParamsMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Post(
    const MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Set_MIReturn(
    MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Clear_MIReturn(
    MyOptionTestClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Set_param1(
    MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->param1)->value = x;
    ((MI_Uint16Field*)&self->param1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Clear_param1(
    MyOptionTestClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->param1, 0, sizeof(self->param1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Set_param2(
    MyOptionTestClass_Sint64SimpleParamsMethod* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->param2)->value = x;
    ((MI_Sint16Field*)&self->param2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_Sint64SimpleParamsMethod_Clear_param2(
    MyOptionTestClass_Sint64SimpleParamsMethod* self)
{
    memset((void*)&self->param2, 0, sizeof(self->param2));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestClass.MultiQualMethod()
**
**==============================================================================
*/

typedef struct _MyOptionTestClass_MultiQualMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64Field inputParam;
    /*OUT*/ MI_ConstUint64Field outputParam;
}
MyOptionTestClass_MultiQualMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl MyOptionTestClass_MultiQualMethod_rtti;

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Construct(
    MyOptionTestClass_MultiQualMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MyOptionTestClass_MultiQualMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Clone(
    const MyOptionTestClass_MultiQualMethod* self,
    MyOptionTestClass_MultiQualMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Destruct(
    MyOptionTestClass_MultiQualMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Delete(
    MyOptionTestClass_MultiQualMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Post(
    const MyOptionTestClass_MultiQualMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Set_MIReturn(
    MyOptionTestClass_MultiQualMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Clear_MIReturn(
    MyOptionTestClass_MultiQualMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Set_inputParam(
    MyOptionTestClass_MultiQualMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->inputParam)->value = x;
    ((MI_Uint64Field*)&self->inputParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Clear_inputParam(
    MyOptionTestClass_MultiQualMethod* self)
{
    memset((void*)&self->inputParam, 0, sizeof(self->inputParam));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Set_outputParam(
    MyOptionTestClass_MultiQualMethod* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->outputParam)->value = x;
    ((MI_Uint64Field*)&self->outputParam)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyOptionTestClass_MultiQualMethod_Clear_outputParam(
    MyOptionTestClass_MultiQualMethod* self)
{
    memset((void*)&self->outputParam, 0, sizeof(self->outputParam));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyOptionTestClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyOptionTestClass_Self MyOptionTestClass_Self;

MI_EXTERN_C void MI_CALL MyOptionTestClass_Load(
    MyOptionTestClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyOptionTestClass_Unload(
    MyOptionTestClass_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyOptionTestClass_Invoke_Uint32EmptyParamMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_Uint32EmptyParamMethod* in);

MI_EXTERN_C void MI_CALL MyOptionTestClass_Invoke_Sint64SimpleParamsMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_Sint64SimpleParamsMethod* in);

MI_EXTERN_C void MI_CALL MyOptionTestClass_Invoke_MultiQualMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_MultiQualMethod* in);


#endif /* _MyOptionTestClass_h */
