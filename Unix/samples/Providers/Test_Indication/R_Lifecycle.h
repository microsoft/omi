/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _R_Lifecycle_h
#define _R_Lifecycle_h

#include <MI.h>
#include "Test_Class.h"

/*
**==============================================================================
**
** R_Lifecycle [R_Lifecycle]
**
** Keys:
**    key
**
**==============================================================================
*/

typedef struct _R_Lifecycle /* extends Test_Class */
{
    MI_Instance __instance;
    /* Test_Class properties */
    /*KEY*/ MI_ConstStringField key;
    MI_ConstUint32Field value;
    /* R_Lifecycle properties */
}
R_Lifecycle;

typedef struct _R_Lifecycle_Ref
{
    R_Lifecycle* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_Lifecycle_Ref;

typedef struct _R_Lifecycle_ConstRef
{
    MI_CONST R_Lifecycle* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_Lifecycle_ConstRef;

typedef struct _R_Lifecycle_Array
{
    struct _R_Lifecycle** data;
    MI_Uint32 size;
}
R_Lifecycle_Array;

typedef struct _R_Lifecycle_ConstArray
{
    struct _R_Lifecycle MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
R_Lifecycle_ConstArray;

typedef struct _R_Lifecycle_ArrayRef
{
    R_Lifecycle_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_Lifecycle_ArrayRef;

typedef struct _R_Lifecycle_ConstArrayRef
{
    R_Lifecycle_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_Lifecycle_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl R_Lifecycle_rtti;

MI_INLINE MI_Result MI_CALL R_Lifecycle_Construct(
    R_Lifecycle* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &R_Lifecycle_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Clone(
    const R_Lifecycle* self,
    R_Lifecycle** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL R_Lifecycle_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &R_Lifecycle_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Destruct(R_Lifecycle* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Delete(R_Lifecycle* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Post(
    const R_Lifecycle* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Set_key(
    R_Lifecycle* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_SetPtr_key(
    R_Lifecycle* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Clear_key(
    R_Lifecycle* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Set_value(
    R_Lifecycle* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->value)->value = x;
    ((MI_Uint32Field*)&self->value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_Clear_value(
    R_Lifecycle* self)
{
    memset((void*)&self->value, 0, sizeof(self->value));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_Lifecycle.GenericInstMethod()
**
**==============================================================================
*/

typedef struct _R_Lifecycle_GenericInstMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_Lifecycle_GenericInstMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_Lifecycle_GenericInstMethod_rtti;

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Construct(
    R_Lifecycle_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_Lifecycle_GenericInstMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Clone(
    const R_Lifecycle_GenericInstMethod* self,
    R_Lifecycle_GenericInstMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Destruct(
    R_Lifecycle_GenericInstMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Delete(
    R_Lifecycle_GenericInstMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Post(
    const R_Lifecycle_GenericInstMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Set_MIReturn(
    R_Lifecycle_GenericInstMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericInstMethod_Clear_MIReturn(
    R_Lifecycle_GenericInstMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_Lifecycle.GenericMethod()
**
**==============================================================================
*/

typedef struct _R_Lifecycle_GenericMethod
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
R_Lifecycle_GenericMethod;

MI_EXTERN_C MI_CONST MI_MethodDecl R_Lifecycle_GenericMethod_rtti;

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Construct(
    R_Lifecycle_GenericMethod* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_Lifecycle_GenericMethod_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Clone(
    const R_Lifecycle_GenericMethod* self,
    R_Lifecycle_GenericMethod** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Destruct(
    R_Lifecycle_GenericMethod* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Delete(
    R_Lifecycle_GenericMethod* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Post(
    const R_Lifecycle_GenericMethod* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Set_MIReturn(
    R_Lifecycle_GenericMethod* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_GenericMethod_Clear_MIReturn(
    R_Lifecycle_GenericMethod* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_Lifecycle.ThreadControl()
**
**==============================================================================
*/

typedef struct _R_Lifecycle_ThreadControl
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field operation;
}
R_Lifecycle_ThreadControl;

MI_EXTERN_C MI_CONST MI_MethodDecl R_Lifecycle_ThreadControl_rtti;

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Construct(
    R_Lifecycle_ThreadControl* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &R_Lifecycle_ThreadControl_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Clone(
    const R_Lifecycle_ThreadControl* self,
    R_Lifecycle_ThreadControl** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Destruct(
    R_Lifecycle_ThreadControl* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Delete(
    R_Lifecycle_ThreadControl* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Post(
    const R_Lifecycle_ThreadControl* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Set_MIReturn(
    R_Lifecycle_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Clear_MIReturn(
    R_Lifecycle_ThreadControl* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Set_operation(
    R_Lifecycle_ThreadControl* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->operation)->value = x;
    ((MI_Uint32Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_Lifecycle_ThreadControl_Clear_operation(
    R_Lifecycle_ThreadControl* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_Lifecycle provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _R_Lifecycle_Self R_Lifecycle_Self;

MI_EXTERN_C void MI_CALL R_Lifecycle_Load(
    R_Lifecycle_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_Lifecycle_Unload(
    R_Lifecycle_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_Lifecycle_EnumerateInstances(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL R_Lifecycle_GetInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_Lifecycle_CreateInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* newInstance);

MI_EXTERN_C void MI_CALL R_Lifecycle_ModifyInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL R_Lifecycle_DeleteInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* instanceName);

MI_EXTERN_C void MI_CALL R_Lifecycle_Invoke_GenericInstMethod(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_GenericInstMethod* in);

MI_EXTERN_C void MI_CALL R_Lifecycle_Invoke_GenericMethod(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_GenericMethod* in);

MI_EXTERN_C void MI_CALL R_Lifecycle_Invoke_ThreadControl(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_ThreadControl* in);


#endif /* _R_Lifecycle_h */
