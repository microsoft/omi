/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Gadget_h
#define _Gadget_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Gadget [XYZ_Gadget]
**
** Keys:
**    SerialNumber
**
**==============================================================================
*/

typedef struct _Gadget
{
    MI_Instance __instance;
    /* Gadget properties */
    /*KEY*/ MI_ConstUint32Field SerialNumber;
    MI_ConstUint32Field ModelNumber;
    MI_ConstUint32Field Size;
    MI_ConstUint32Field State;
    Widget_ConstRef Embedded;
}
Gadget;

typedef struct _Gadget_Ref
{
    Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_Ref;

typedef struct _Gadget_ConstRef
{
    MI_CONST Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstRef;

typedef struct _Gadget_Array
{
    struct _Gadget** data;
    MI_Uint32 size;
}
Gadget_Array;

typedef struct _Gadget_ConstArray
{
    struct _Gadget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Gadget_ConstArray;

typedef struct _Gadget_ArrayRef
{
    Gadget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ArrayRef;

typedef struct _Gadget_ConstArrayRef
{
    Gadget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Gadget_rtti;

MI_INLINE MI_Result MI_CALL Gadget_Construct(
    Gadget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Gadget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Clone(
    const Gadget* self,
    Gadget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Gadget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Gadget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Gadget_Destruct(Gadget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Delete(Gadget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Post(
    const Gadget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Set_SerialNumber(
    Gadget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SerialNumber)->value = x;
    ((MI_Uint32Field*)&self->SerialNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_SerialNumber(
    Gadget* self)
{
    memset((void*)&self->SerialNumber, 0, sizeof(self->SerialNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Set_ModelNumber(
    Gadget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ModelNumber)->value = x;
    ((MI_Uint32Field*)&self->ModelNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_ModelNumber(
    Gadget* self)
{
    memset((void*)&self->ModelNumber, 0, sizeof(self->ModelNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Set_Size(
    Gadget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Size)->value = x;
    ((MI_Uint32Field*)&self->Size)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_Size(
    Gadget* self)
{
    memset((void*)&self->Size, 0, sizeof(self->Size));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Set_State(
    Gadget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->State)->value = x;
    ((MI_Uint32Field*)&self->State)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_State(
    Gadget* self)
{
    memset((void*)&self->State, 0, sizeof(self->State));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Set_Embedded(
    Gadget* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Gadget_SetPtr_Embedded(
    Gadget* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_Embedded(
    Gadget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** Gadget.ChangeState()
**
**==============================================================================
*/

typedef struct _Gadget_ChangeState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field NewState;
    /*OUT*/ MI_ConstUint32Field OldState;
}
Gadget_ChangeState;

MI_EXTERN_C MI_CONST MI_MethodDecl Gadget_ChangeState_rtti;

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Construct(
    Gadget_ChangeState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Gadget_ChangeState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Clone(
    const Gadget_ChangeState* self,
    Gadget_ChangeState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Destruct(
    Gadget_ChangeState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Delete(
    Gadget_ChangeState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Post(
    const Gadget_ChangeState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Set_MIReturn(
    Gadget_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Clear_MIReturn(
    Gadget_ChangeState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Set_NewState(
    Gadget_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->NewState)->value = x;
    ((MI_Uint32Field*)&self->NewState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Clear_NewState(
    Gadget_ChangeState* self)
{
    memset((void*)&self->NewState, 0, sizeof(self->NewState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Set_OldState(
    Gadget_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->OldState)->value = x;
    ((MI_Uint32Field*)&self->OldState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_ChangeState_Clear_OldState(
    Gadget_ChangeState* self)
{
    memset((void*)&self->OldState, 0, sizeof(self->OldState));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Gadget.Foo()
**
**==============================================================================
*/

typedef struct _Gadget_Foo
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Gadget_ConstRef Arg;
}
Gadget_Foo;

MI_EXTERN_C MI_CONST MI_MethodDecl Gadget_Foo_rtti;

MI_INLINE MI_Result MI_CALL Gadget_Foo_Construct(
    Gadget_Foo* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Gadget_Foo_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Clone(
    const Gadget_Foo* self,
    Gadget_Foo** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Destruct(
    Gadget_Foo* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Delete(
    Gadget_Foo* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Post(
    const Gadget_Foo* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Set_MIReturn(
    Gadget_Foo* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Clear_MIReturn(
    Gadget_Foo* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Set_Arg(
    Gadget_Foo* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_SetPtr_Arg(
    Gadget_Foo* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Gadget_Foo_Clear_Arg(
    Gadget_Foo* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Gadget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Gadget_Self Gadget_Self;

MI_EXTERN_C void MI_CALL Gadget_Load(
    Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Gadget_Unload(
    Gadget_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Gadget_EnumerateInstances(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Gadget_GetInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Gadget_CreateInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* newInstance);

MI_EXTERN_C void MI_CALL Gadget_ModifyInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Gadget_DeleteInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName);

MI_EXTERN_C void MI_CALL Gadget_Invoke_ChangeState(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_ChangeState* in);

MI_EXTERN_C void MI_CALL Gadget_Invoke_Foo(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_Foo* in);


#endif /* _Gadget_h */
