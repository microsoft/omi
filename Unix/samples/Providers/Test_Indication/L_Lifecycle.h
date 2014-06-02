/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_Lifecycle_h
#define _L_Lifecycle_h

#include <MI.h>
#include "Test_Class.h"

/*
**==============================================================================
**
** L_Lifecycle [L_Lifecycle]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _L_Lifecycle /* extends Test_Class */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* L_Lifecycle properties */
}
L_Lifecycle;

typedef struct _L_Lifecycle_Ref
{
    L_Lifecycle* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Lifecycle_Ref;

typedef struct _L_Lifecycle_ConstRef
{
    MI_CONST L_Lifecycle* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Lifecycle_ConstRef;

typedef struct _L_Lifecycle_Array
{
    struct _L_Lifecycle** data;
    MI_Uint32 size;
}
L_Lifecycle_Array;

typedef struct _L_Lifecycle_ConstArray
{
    struct _L_Lifecycle MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_Lifecycle_ConstArray;

typedef struct _L_Lifecycle_ArrayRef
{
    L_Lifecycle_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Lifecycle_ArrayRef;

typedef struct _L_Lifecycle_ConstArrayRef
{
    L_Lifecycle_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_Lifecycle_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_Lifecycle_rtti;

MI_INLINE MI_Result MI_CALL L_Lifecycle_Construct(
    L_Lifecycle* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_Lifecycle_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Clone(
    const L_Lifecycle* self,
    L_Lifecycle** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_Lifecycle_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_Lifecycle_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Destruct(L_Lifecycle* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Delete(L_Lifecycle* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Post(
    const L_Lifecycle* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Set_key(
    L_Lifecycle* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_SetPtr_key(
    L_Lifecycle* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Clear_key(
    L_Lifecycle* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Set_value(
    L_Lifecycle* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_Clear_value(
    L_Lifecycle* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_Lifecycle.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _L_Lifecycle_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_Lifecycle_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_Lifecycle_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Construct(
    L_Lifecycle_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_Lifecycle_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Clone(
    const L_Lifecycle_GenericInstMethod* self,
    L_Lifecycle_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Destruct(
    L_Lifecycle_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Delete(
    L_Lifecycle_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Post(
    const L_Lifecycle_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Set_MIReturn(
    L_Lifecycle_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericInstMethod_Clear_MIReturn(
    L_Lifecycle_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_Lifecycle.GenericMethod()
**
**==============================================================================
*/

typedef struct _L_Lifecycle_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
L_Lifecycle_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl L_Lifecycle_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Construct(
    L_Lifecycle_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_Lifecycle_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Clone(
    const L_Lifecycle_GenericMethod* self,
    L_Lifecycle_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Destruct(
    L_Lifecycle_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Delete(
    L_Lifecycle_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Post(
    const L_Lifecycle_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Set_MIReturn(
    L_Lifecycle_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_GenericMethod_Clear_MIReturn(
    L_Lifecycle_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_Lifecycle.ThreadControl()
**
**==============================================================================
*/

typedef struct _L_Lifecycle_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
L_Lifecycle_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl L_Lifecycle_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Construct(
    L_Lifecycle_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &L_Lifecycle_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Clone(
    const L_Lifecycle_ThreadControl* self,
    L_Lifecycle_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Destruct(
    L_Lifecycle_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Delete(
    L_Lifecycle_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Post(
    const L_Lifecycle_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Set_MIReturn(
    L_Lifecycle_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Clear_MIReturn(
    L_Lifecycle_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Set_operation(
    L_Lifecycle_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_Lifecycle_ThreadControl_Clear_operation(
    L_Lifecycle_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_Lifecycle provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _L_Lifecycle_Self L_Lifecycle_Self;

MI_EXTERN_C void MI_CALL L_Lifecycle_Load(
    L_Lifecycle_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_Lifecycle_Unload(
    L_Lifecycle_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_Lifecycle_EnumerateInstances(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL L_Lifecycle_GetInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_Lifecycle_CreateInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* newInstance);

MI_EXTERN_C void MI_CALL L_Lifecycle_ModifyInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL L_Lifecycle_DeleteInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* instanceName);

MI_EXTERN_C void MI_CALL L_Lifecycle_Invoke_GenericInstMethod(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL L_Lifecycle_Invoke_GenericMethod(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_GenericMethod* in);

MI_EXTERN_C void MI_CALL L_Lifecycle_Invoke_ThreadControl(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_ThreadControl* in);


#endif /* _L_Lifecycle_h */
