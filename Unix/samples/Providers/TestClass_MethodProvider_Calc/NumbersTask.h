/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _NumbersTask_h
#define _NumbersTask_h

#include <MI.h>
#include "Numbers.h"

/*
**==============================================================================
**
** NumbersTask [NumbersTask]
**
** Keys:
**
**==============================================================================
*/

typedef struct _NumbersTask
{
    MI_Instance __instance;
    /* NumbersTask properties */
}
NumbersTask;

typedef struct _NumbersTask_Ref
{
    NumbersTask* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
NumbersTask_Ref;

typedef struct _NumbersTask_ConstRef
{
    MI_CONST NumbersTask* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
NumbersTask_ConstRef;

typedef struct _NumbersTask_Array
{
    struct _NumbersTask** data;
    MI_Uint32 size;
}
NumbersTask_Array;

typedef struct _NumbersTask_ConstArray
{
    struct _NumbersTask MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
NumbersTask_ConstArray;

typedef struct _NumbersTask_ArrayRef
{
    NumbersTask_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
NumbersTask_ArrayRef;

typedef struct _NumbersTask_ConstArrayRef
{
    NumbersTask_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
NumbersTask_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl NumbersTask_rtti;

MI_INLINE MI_Result MI_CALL NumbersTask_Construct(
    _Inout_ NumbersTask* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &NumbersTask_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_Clone(
    _In_ const NumbersTask* self,
    _Outptr_ NumbersTask** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL NumbersTask_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &NumbersTask_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL NumbersTask_Destruct(_Inout_ NumbersTask* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_Delete(_Inout_ NumbersTask* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_Post(
    _In_ const NumbersTask* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** NumbersTask.NewNumber()
**
**==============================================================================
*/

typedef struct _NumbersTask_NewNumber
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint64AField newDigits;
    /*OUT*/ Numbers_ConstRef newNum;
}
NumbersTask_NewNumber;

MI_EXTERN_C MI_CONST MI_MethodDecl NumbersTask_NewNumber_rtti;

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Construct(
    _Inout_ NumbersTask_NewNumber* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &NumbersTask_NewNumber_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Clone(
    _In_ const NumbersTask_NewNumber* self,
    _Outptr_ NumbersTask_NewNumber** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Destruct(
    _Inout_ NumbersTask_NewNumber* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Delete(
    _Inout_ NumbersTask_NewNumber* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Post(
    _In_ const NumbersTask_NewNumber* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Set_MIReturn(
    _Inout_ NumbersTask_NewNumber* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Clear_MIReturn(
    _Inout_ NumbersTask_NewNumber* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Set_newDigits(
    _Inout_ NumbersTask_NewNumber* self,
    _In_reads_opt_(size) const MI_Sint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_SetPtr_newDigits(
    _Inout_ NumbersTask_NewNumber* self,
    _In_reads_opt_(size) const MI_Sint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Clear_newDigits(
    _Inout_ NumbersTask_NewNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Set_newNum(
    _Inout_ NumbersTask_NewNumber* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_SetPtr_newNum(
    _Inout_ NumbersTask_NewNumber* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL NumbersTask_NewNumber_Clear_newNum(
    _Inout_ NumbersTask_NewNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** NumbersTask provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _NumbersTask_Self NumbersTask_Self;

MI_EXTERN_C void MI_CALL NumbersTask_Load(
    _Outptr_result_maybenull_ NumbersTask_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL NumbersTask_Unload(
    _In_opt_ NumbersTask_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL NumbersTask_Invoke_NewNumber(
    _In_opt_ NumbersTask_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const NumbersTask* instanceName,
    _In_opt_ const NumbersTask_NewNumber* in);


#endif /* _NumbersTask_h */
