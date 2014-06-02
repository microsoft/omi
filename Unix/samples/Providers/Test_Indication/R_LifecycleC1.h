/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _R_LifecycleC1_h
#define _R_LifecycleC1_h

#include <MI.h>
#include "R_Lifecycle.h"

/*
**==============================================================================
**
** R_LifecycleC1 [R_LifecycleC1]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _R_LifecycleC1 /* extends R_Lifecycle */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* R_Lifecycle properties */
    /* R_LifecycleC1 properties */
}
R_LifecycleC1;

typedef struct _R_LifecycleC1_Ref
{
    R_LifecycleC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC1_Ref;

typedef struct _R_LifecycleC1_ConstRef
{
    MI_CONST R_LifecycleC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC1_ConstRef;

typedef struct _R_LifecycleC1_Array
{
    struct _R_LifecycleC1** data;
    MI_Uint32 size;
}
R_LifecycleC1_Array;

typedef struct _R_LifecycleC1_ConstArray
{
    struct _R_LifecycleC1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
R_LifecycleC1_ConstArray;

typedef struct _R_LifecycleC1_ArrayRef
{
    R_LifecycleC1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC1_ArrayRef;

typedef struct _R_LifecycleC1_ConstArrayRef
{
    R_LifecycleC1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC1_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl R_LifecycleC1_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Construct(
    R_LifecycleC1* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &R_LifecycleC1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Clone(
    const R_LifecycleC1* self,
    R_LifecycleC1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL R_LifecycleC1_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &R_LifecycleC1_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Destruct(R_LifecycleC1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Delete(R_LifecycleC1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Post(
    const R_LifecycleC1* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Set_key(
    R_LifecycleC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_SetPtr_key(
    R_LifecycleC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Clear_key(
    R_LifecycleC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Set_value(
    R_LifecycleC1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_Clear_value(
    R_LifecycleC1* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC1.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _R_LifecycleC1_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_LifecycleC1_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC1_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Construct(
    R_LifecycleC1_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC1_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Clone(
    const R_LifecycleC1_GenericInstMethod* self,
    R_LifecycleC1_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Destruct(
    R_LifecycleC1_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Delete(
    R_LifecycleC1_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Post(
    const R_LifecycleC1_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Set_MIReturn(
    R_LifecycleC1_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericInstMethod_Clear_MIReturn(
    R_LifecycleC1_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC1.GenericMethod()
**
**==============================================================================
*/

typedef struct _R_LifecycleC1_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_LifecycleC1_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC1_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Construct(
    R_LifecycleC1_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC1_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Clone(
    const R_LifecycleC1_GenericMethod* self,
    R_LifecycleC1_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Destruct(
    R_LifecycleC1_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Delete(
    R_LifecycleC1_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Post(
    const R_LifecycleC1_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Set_MIReturn(
    R_LifecycleC1_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_GenericMethod_Clear_MIReturn(
    R_LifecycleC1_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC1.ThreadControl()
**
**==============================================================================
*/

typedef struct _R_LifecycleC1_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
R_LifecycleC1_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC1_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Construct(
    R_LifecycleC1_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC1_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Clone(
    const R_LifecycleC1_ThreadControl* self,
    R_LifecycleC1_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Destruct(
    R_LifecycleC1_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Delete(
    R_LifecycleC1_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Post(
    const R_LifecycleC1_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Set_MIReturn(
    R_LifecycleC1_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Clear_MIReturn(
    R_LifecycleC1_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Set_operation(
    R_LifecycleC1_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC1_ThreadControl_Clear_operation(
    R_LifecycleC1_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC1 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _R_LifecycleC1_Self R_LifecycleC1_Self;

MI_EXTERN_C void MI_CALL R_LifecycleC1_Load(
    R_LifecycleC1_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_LifecycleC1_Unload(
    R_LifecycleC1_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_LifecycleC1_EnumerateInstances(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL R_LifecycleC1_GetInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_LifecycleC1_CreateInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* newInstance);

MI_EXTERN_C void MI_CALL R_LifecycleC1_ModifyInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_LifecycleC1_DeleteInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* instanceName);

MI_EXTERN_C void MI_CALL R_LifecycleC1_Invoke_GenericInstMethod(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL R_LifecycleC1_Invoke_GenericMethod(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_GenericMethod* in);

MI_EXTERN_C void MI_CALL R_LifecycleC1_Invoke_ThreadControl(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_ThreadControl* in);


#endif /* _R_LifecycleC1_h */
