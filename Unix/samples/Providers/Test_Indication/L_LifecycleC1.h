/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_LifecycleC1_h
#define _L_LifecycleC1_h

#include <MI.h>
#include "L_Lifecycle.h"

/*
**==============================================================================
**
** L_LifecycleC1 [L_LifecycleC1]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _L_LifecycleC1 /* extends L_Lifecycle */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* L_Lifecycle properties */
    /* L_LifecycleC1 properties */
}
L_LifecycleC1;

typedef struct _L_LifecycleC1_Ref
{
    L_LifecycleC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC1_Ref;

typedef struct _L_LifecycleC1_ConstRef
{
    MI_CONST L_LifecycleC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC1_ConstRef;

typedef struct _L_LifecycleC1_Array
{
    struct _L_LifecycleC1** data;
    MI_Uint32 size;
}
L_LifecycleC1_Array;

typedef struct _L_LifecycleC1_ConstArray
{
    struct _L_LifecycleC1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_LifecycleC1_ConstArray;

typedef struct _L_LifecycleC1_ArrayRef
{
    L_LifecycleC1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC1_ArrayRef;

typedef struct _L_LifecycleC1_ConstArrayRef
{
    L_LifecycleC1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC1_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_LifecycleC1_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Construct(
    L_LifecycleC1* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_LifecycleC1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Clone(
    const L_LifecycleC1* self,
    L_LifecycleC1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_LifecycleC1_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_LifecycleC1_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Destruct(L_LifecycleC1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Delete(L_LifecycleC1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Post(
    const L_LifecycleC1* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Set_key(
    L_LifecycleC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_SetPtr_key(
    L_LifecycleC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Clear_key(
    L_LifecycleC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Set_value(
    L_LifecycleC1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_Clear_value(
    L_LifecycleC1* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC1.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _L_LifecycleC1_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_LifecycleC1_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC1_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Construct(
    L_LifecycleC1_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC1_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Clone(
    const L_LifecycleC1_GenericInstMethod* self,
    L_LifecycleC1_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Destruct(
    L_LifecycleC1_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Delete(
    L_LifecycleC1_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Post(
    const L_LifecycleC1_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Set_MIReturn(
    L_LifecycleC1_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericInstMethod_Clear_MIReturn(
    L_LifecycleC1_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC1.GenericMethod()
**
**==============================================================================
*/

typedef struct _L_LifecycleC1_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_LifecycleC1_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC1_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Construct(
    L_LifecycleC1_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC1_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Clone(
    const L_LifecycleC1_GenericMethod* self,
    L_LifecycleC1_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Destruct(
    L_LifecycleC1_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Delete(
    L_LifecycleC1_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Post(
    const L_LifecycleC1_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Set_MIReturn(
    L_LifecycleC1_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_GenericMethod_Clear_MIReturn(
    L_LifecycleC1_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC1.ThreadControl()
**
**==============================================================================
*/

typedef struct _L_LifecycleC1_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
L_LifecycleC1_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC1_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Construct(
    L_LifecycleC1_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC1_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Clone(
    const L_LifecycleC1_ThreadControl* self,
    L_LifecycleC1_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Destruct(
    L_LifecycleC1_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Delete(
    L_LifecycleC1_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Post(
    const L_LifecycleC1_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Set_MIReturn(
    L_LifecycleC1_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Clear_MIReturn(
    L_LifecycleC1_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Set_operation(
    L_LifecycleC1_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC1_ThreadControl_Clear_operation(
    L_LifecycleC1_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC1 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _L_LifecycleC1_Self L_LifecycleC1_Self;

MI_EXTERN_C void MI_CALL L_LifecycleC1_Load(
    L_LifecycleC1_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_LifecycleC1_Unload(
    L_LifecycleC1_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_LifecycleC1_EnumerateInstances(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL L_LifecycleC1_GetInstance(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC1* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_LifecycleC1_CreateInstance(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC1* newInstance);

MI_EXTERN_C void MI_CALL L_LifecycleC1_ModifyInstance(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC1* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_LifecycleC1_DeleteInstance(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC1* instanceName);

MI_EXTERN_C void MI_CALL L_LifecycleC1_Invoke_GenericInstMethod(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC1* instanceName,
    const L_LifecycleC1_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL L_LifecycleC1_Invoke_GenericMethod(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC1* instanceName,
    const L_LifecycleC1_GenericMethod* in);

MI_EXTERN_C void MI_CALL L_LifecycleC1_Invoke_ThreadControl(
    L_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC1* instanceName,
    const L_LifecycleC1_ThreadControl* in);


#endif /* _L_LifecycleC1_h */
