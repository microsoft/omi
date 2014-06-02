/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_LifecycleC2_h
#define _L_LifecycleC2_h

#include <MI.h>
#include "L_LifecycleC1.h"

/*
**==============================================================================
**
** L_LifecycleC2 [L_LifecycleC2]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _L_LifecycleC2 /* extends L_LifecycleC1 */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* L_Lifecycle properties */
    /* L_LifecycleC1 properties */
    /* L_LifecycleC2 properties */
}
L_LifecycleC2;

typedef struct _L_LifecycleC2_Ref
{
    L_LifecycleC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC2_Ref;

typedef struct _L_LifecycleC2_ConstRef
{
    MI_CONST L_LifecycleC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC2_ConstRef;

typedef struct _L_LifecycleC2_Array
{
    struct _L_LifecycleC2** data;
    MI_Uint32 size;
}
L_LifecycleC2_Array;

typedef struct _L_LifecycleC2_ConstArray
{
    struct _L_LifecycleC2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_LifecycleC2_ConstArray;

typedef struct _L_LifecycleC2_ArrayRef
{
    L_LifecycleC2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC2_ArrayRef;

typedef struct _L_LifecycleC2_ConstArrayRef
{
    L_LifecycleC2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_LifecycleC2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_LifecycleC2_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Construct(
    L_LifecycleC2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_LifecycleC2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Clone(
    const L_LifecycleC2* self,
    L_LifecycleC2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_LifecycleC2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_LifecycleC2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Destruct(L_LifecycleC2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Delete(L_LifecycleC2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Post(
    const L_LifecycleC2* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Set_key(
    L_LifecycleC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_SetPtr_key(
    L_LifecycleC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Clear_key(
    L_LifecycleC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Set_value(
    L_LifecycleC2* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_Clear_value(
    L_LifecycleC2* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC2.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _L_LifecycleC2_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_LifecycleC2_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC2_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Construct(
    L_LifecycleC2_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC2_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Clone(
    const L_LifecycleC2_GenericInstMethod* self,
    L_LifecycleC2_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Destruct(
    L_LifecycleC2_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Delete(
    L_LifecycleC2_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Post(
    const L_LifecycleC2_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Set_MIReturn(
    L_LifecycleC2_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericInstMethod_Clear_MIReturn(
    L_LifecycleC2_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC2.GenericMethod()
**
**==============================================================================
*/

typedef struct _L_LifecycleC2_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_LifecycleC2_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC2_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Construct(
    L_LifecycleC2_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC2_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Clone(
    const L_LifecycleC2_GenericMethod* self,
    L_LifecycleC2_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Destruct(
    L_LifecycleC2_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Delete(
    L_LifecycleC2_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Post(
    const L_LifecycleC2_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Set_MIReturn(
    L_LifecycleC2_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_GenericMethod_Clear_MIReturn(
    L_LifecycleC2_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC2.ThreadControl()
**
**==============================================================================
*/

typedef struct _L_LifecycleC2_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
L_LifecycleC2_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl L_LifecycleC2_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Construct(
    L_LifecycleC2_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_LifecycleC2_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Clone(
    const L_LifecycleC2_ThreadControl* self,
    L_LifecycleC2_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Destruct(
    L_LifecycleC2_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Delete(
    L_LifecycleC2_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Post(
    const L_LifecycleC2_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Set_MIReturn(
    L_LifecycleC2_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Clear_MIReturn(
    L_LifecycleC2_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Set_operation(
    L_LifecycleC2_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_LifecycleC2_ThreadControl_Clear_operation(
    L_LifecycleC2_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_LifecycleC2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _L_LifecycleC2_Self L_LifecycleC2_Self;

MI_EXTERN_C void MI_CALL L_LifecycleC2_Load(
    L_LifecycleC2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_LifecycleC2_Unload(
    L_LifecycleC2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_LifecycleC2_EnumerateInstances(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL L_LifecycleC2_GetInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_LifecycleC2_CreateInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* newInstance);

MI_EXTERN_C void MI_CALL L_LifecycleC2_ModifyInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_LifecycleC2_DeleteInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* instanceName);

MI_EXTERN_C void MI_CALL L_LifecycleC2_Invoke_GenericInstMethod(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL L_LifecycleC2_Invoke_GenericMethod(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_GenericMethod* in);

MI_EXTERN_C void MI_CALL L_LifecycleC2_Invoke_ThreadControl(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_ThreadControl* in);


#endif /* _L_LifecycleC2_h */
