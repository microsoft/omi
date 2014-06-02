/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestSP_Method_h
#define _TestSP_Method_h

#include <MI.h>

/*
**==============================================================================
**
** TestSP_Method [TestSP_Method]
**
** Keys:
**
**==============================================================================
*/

typedef struct _TestSP_Method
{
    MI_Instance __instance;
    /* TestSP_Method properties */
}
TestSP_Method;

typedef struct _TestSP_Method_Ref
{
    TestSP_Method* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestSP_Method_Ref;

typedef struct _TestSP_Method_ConstRef
{
    MI_CONST TestSP_Method* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestSP_Method_ConstRef;

typedef struct _TestSP_Method_Array
{
    struct _TestSP_Method** data;
    MI_Uint32 size;
}
TestSP_Method_Array;

typedef struct _TestSP_Method_ConstArray
{
    struct _TestSP_Method MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestSP_Method_ConstArray;

typedef struct _TestSP_Method_ArrayRef
{
    TestSP_Method_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestSP_Method_ArrayRef;

typedef struct _TestSP_Method_ConstArrayRef
{
    TestSP_Method_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestSP_Method_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestSP_Method_rtti;

MI_INLINE MI_Result MI_CALL TestSP_Method_Construct(
    TestSP_Method* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &TestSP_Method_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_Clone(
    const TestSP_Method* self,
    TestSP_Method** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestSP_Method_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestSP_Method_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestSP_Method_Destruct(TestSP_Method* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_Delete(TestSP_Method* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_Post(
    const TestSP_Method* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** TestSP_Method.MyFunc()
**
**==============================================================================
*/

typedef struct _TestSP_Method_MyFunc
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint32Field v;
}
TestSP_Method_MyFunc;

MI_EXTERN_C MI_CONST MI_MethodDecl TestSP_Method_MyFunc_rtti;

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Construct(
    TestSP_Method_MyFunc* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestSP_Method_MyFunc_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Clone(
    const TestSP_Method_MyFunc* self,
    TestSP_Method_MyFunc** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Destruct(
    TestSP_Method_MyFunc* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Delete(
    TestSP_Method_MyFunc* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Post(
    const TestSP_Method_MyFunc* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Set_MIReturn(
    TestSP_Method_MyFunc* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Clear_MIReturn(
    TestSP_Method_MyFunc* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Set_v(
    TestSP_Method_MyFunc* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->v)->value = x;
    ((MI_Uint32Field*)&self->v)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestSP_Method_MyFunc_Clear_v(
    TestSP_Method_MyFunc* self)
{
    memset((void*)&self->v, 0, sizeof(self->v));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestSP_Method provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestSP_Method_Self TestSP_Method_Self;

MI_EXTERN_C void MI_CALL TestSP_Method_Load(
    TestSP_Method_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestSP_Method_Unload(
    TestSP_Method_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestSP_Method_Invoke_MyFunc(
    TestSP_Method_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestSP_Method* instanceName,
    const TestSP_Method_MyFunc* in);


#endif /* _TestSP_Method_h */
