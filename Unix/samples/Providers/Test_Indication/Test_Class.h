/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_Class_h
#define _Test_Class_h

#include <MI.h>

/*
**==============================================================================
**
** Test_Class [Test_Class]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _Test_Class
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
}
Test_Class;

typedef struct _Test_Class_Ref
{
    Test_Class* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Class_Ref;

typedef struct _Test_Class_ConstRef
{
    MI_CONST Test_Class* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Class_ConstRef;

typedef struct _Test_Class_Array
{
    struct _Test_Class** data;
    MI_Uint32 size;
}
Test_Class_Array;

typedef struct _Test_Class_ConstArray
{
    struct _Test_Class MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_Class_ConstArray;

typedef struct _Test_Class_ArrayRef
{
    Test_Class_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Class_ArrayRef;

typedef struct _Test_Class_ConstArrayRef
{
    Test_Class_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Class_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_Class_rtti;

MI_INLINE MI_Result MI_CALL Test_Class_Construct(
    Test_Class* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_Class_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_Clone(
    const Test_Class* self,
    Test_Class** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_Class_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_Class_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_Class_Destruct(Test_Class* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_Delete(Test_Class* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_Post(
    const Test_Class* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_Set_key(
    Test_Class* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Class_SetPtr_key(
    Test_Class* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Class_Clear_key(
    Test_Class* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Class_Set_value(
    Test_Class* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_Clear_value(
    Test_Class* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_Class.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _Test_Class_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Test_Class_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl Test_Class_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Construct(
    Test_Class_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Test_Class_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Clone(
    const Test_Class_GenericInstMethod* self,
    Test_Class_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Destruct(
    Test_Class_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Delete(
    Test_Class_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Post(
    const Test_Class_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Set_MIReturn(
    Test_Class_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericInstMethod_Clear_MIReturn(
    Test_Class_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_Class.GenericMethod()
**
**==============================================================================
*/

typedef struct _Test_Class_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Test_Class_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl Test_Class_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Construct(
    Test_Class_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Test_Class_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Clone(
    const Test_Class_GenericMethod* self,
    Test_Class_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Destruct(
    Test_Class_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Delete(
    Test_Class_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Post(
    const Test_Class_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Set_MIReturn(
    Test_Class_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_GenericMethod_Clear_MIReturn(
    Test_Class_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_Class.ThreadControl()
**
**==============================================================================
*/

typedef struct _Test_Class_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
Test_Class_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl Test_Class_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Construct(
    Test_Class_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Test_Class_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Clone(
    const Test_Class_ThreadControl* self,
    Test_Class_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Destruct(
    Test_Class_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Delete(
    Test_Class_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Post(
    const Test_Class_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Set_MIReturn(
    Test_Class_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Clear_MIReturn(
    Test_Class_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Set_operation(
    Test_Class_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Class_ThreadControl_Clear_operation(
    Test_Class_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Test_Class provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_Class_Self Test_Class_Self;

MI_EXTERN_C void MI_CALL Test_Class_Load(
    Test_Class_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_Class_Unload(
    Test_Class_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_Class_EnumerateInstances(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Test_Class_GetInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_Class_CreateInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* newInstance);

MI_EXTERN_C void MI_CALL Test_Class_ModifyInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Test_Class_DeleteInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* instanceName);

MI_EXTERN_C void MI_CALL Test_Class_Invoke_GenericInstMethod(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL Test_Class_Invoke_GenericMethod(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_GenericMethod* in);

MI_EXTERN_C void MI_CALL Test_Class_Invoke_ThreadControl(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_ThreadControl* in);


#endif /* _Test_Class_h */
