/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _R_LifecycleC2_h
#define _R_LifecycleC2_h

#include <MI.h>
#include "R_LifecycleC1.h"

/*
**==============================================================================
**
** R_LifecycleC2 [R_LifecycleC2]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _R_LifecycleC2 /* extends R_LifecycleC1 */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* R_Lifecycle properties */
    /* R_LifecycleC1 properties */
    /* R_LifecycleC2 properties */
}
R_LifecycleC2;

typedef struct _R_LifecycleC2_Ref
{
    R_LifecycleC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC2_Ref;

typedef struct _R_LifecycleC2_ConstRef
{
    MI_CONST R_LifecycleC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC2_ConstRef;

typedef struct _R_LifecycleC2_Array
{
    struct _R_LifecycleC2** data;
    MI_Uint32 size;
}
R_LifecycleC2_Array;

typedef struct _R_LifecycleC2_ConstArray
{
    struct _R_LifecycleC2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
R_LifecycleC2_ConstArray;

typedef struct _R_LifecycleC2_ArrayRef
{
    R_LifecycleC2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC2_ArrayRef;

typedef struct _R_LifecycleC2_ConstArrayRef
{
    R_LifecycleC2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_LifecycleC2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl R_LifecycleC2_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Construct(
    R_LifecycleC2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &R_LifecycleC2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Clone(
    const R_LifecycleC2* self,
    R_LifecycleC2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL R_LifecycleC2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &R_LifecycleC2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Destruct(R_LifecycleC2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Delete(R_LifecycleC2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Post(
    const R_LifecycleC2* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Set_key(
    R_LifecycleC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_SetPtr_key(
    R_LifecycleC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Clear_key(
    R_LifecycleC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Set_value(
    R_LifecycleC2* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_Clear_value(
    R_LifecycleC2* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC2.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _R_LifecycleC2_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_LifecycleC2_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC2_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Construct(
    R_LifecycleC2_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC2_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Clone(
    const R_LifecycleC2_GenericInstMethod* self,
    R_LifecycleC2_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Destruct(
    R_LifecycleC2_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Delete(
    R_LifecycleC2_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Post(
    const R_LifecycleC2_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Set_MIReturn(
    R_LifecycleC2_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericInstMethod_Clear_MIReturn(
    R_LifecycleC2_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC2.GenericMethod()
**
**==============================================================================
*/

typedef struct _R_LifecycleC2_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_LifecycleC2_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC2_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Construct(
    R_LifecycleC2_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC2_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Clone(
    const R_LifecycleC2_GenericMethod* self,
    R_LifecycleC2_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Destruct(
    R_LifecycleC2_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Delete(
    R_LifecycleC2_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Post(
    const R_LifecycleC2_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Set_MIReturn(
    R_LifecycleC2_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_GenericMethod_Clear_MIReturn(
    R_LifecycleC2_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC2.ThreadControl()
**
**==============================================================================
*/

typedef struct _R_LifecycleC2_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
R_LifecycleC2_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl R_LifecycleC2_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Construct(
    R_LifecycleC2_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_LifecycleC2_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Clone(
    const R_LifecycleC2_ThreadControl* self,
    R_LifecycleC2_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Destruct(
    R_LifecycleC2_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Delete(
    R_LifecycleC2_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Post(
    const R_LifecycleC2_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Set_MIReturn(
    R_LifecycleC2_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Clear_MIReturn(
    R_LifecycleC2_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Set_operation(
    R_LifecycleC2_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_LifecycleC2_ThreadControl_Clear_operation(
    R_LifecycleC2_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_LifecycleC2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _R_LifecycleC2_Self R_LifecycleC2_Self;

MI_EXTERN_C void MI_CALL R_LifecycleC2_Load(
    R_LifecycleC2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_LifecycleC2_Unload(
    R_LifecycleC2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_LifecycleC2_EnumerateInstances(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL R_LifecycleC2_GetInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_LifecycleC2_CreateInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* newInstance);

MI_EXTERN_C void MI_CALL R_LifecycleC2_ModifyInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_LifecycleC2_DeleteInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* instanceName);

MI_EXTERN_C void MI_CALL R_LifecycleC2_Invoke_GenericInstMethod(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL R_LifecycleC2_Invoke_GenericMethod(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_GenericMethod* in);

MI_EXTERN_C void MI_CALL R_LifecycleC2_Invoke_ThreadControl(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_ThreadControl* in);


#endif /* _R_LifecycleC2_h */
