/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Datetime_h
#define _Datetime_h

#include <MI.h>

/*
**==============================================================================
**
** Datetime [OMI_Datetime]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Datetime
{
    MI_Instance __instance;
    /* Datetime properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstDatetimeField timestamp;
    MI_ConstDatetimeField interval;
    MI_ConstDatetimeAField timestamps;
    MI_ConstDatetimeAField intervals;
    MI_ConstDatetimeAField mixed;
}
Datetime;

typedef struct _Datetime_Ref
{
    Datetime* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Datetime_Ref;

typedef struct _Datetime_ConstRef
{
    MI_CONST Datetime* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Datetime_ConstRef;

typedef struct _Datetime_Array
{
    struct _Datetime** data;
    MI_Uint32 size;
}
Datetime_Array;

typedef struct _Datetime_ConstArray
{
    struct _Datetime MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Datetime_ConstArray;

typedef struct _Datetime_ArrayRef
{
    Datetime_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Datetime_ArrayRef;

typedef struct _Datetime_ConstArrayRef
{
    Datetime_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Datetime_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Datetime_rtti;

MI_INLINE MI_Result MI_CALL Datetime_Construct(
    Datetime* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Datetime_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Datetime_Clone(
    const Datetime* self,
    Datetime** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Datetime_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Datetime_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Datetime_Destruct(Datetime* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Datetime_Delete(Datetime* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Datetime_Post(
    const Datetime* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Datetime_Set_Key(
    Datetime* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Datetime_SetPtr_Key(
    Datetime* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_Key(
    Datetime* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Datetime_Set_timestamp(
    Datetime* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->timestamp)->value = x;
    ((MI_DatetimeField*)&self->timestamp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_timestamp(
    Datetime* self)
{
    memset((void*)&self->timestamp, 0, sizeof(self->timestamp));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Datetime_Set_interval(
    Datetime* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->interval)->value = x;
    ((MI_DatetimeField*)&self->interval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_interval(
    Datetime* self)
{
    memset((void*)&self->interval, 0, sizeof(self->interval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Datetime_Set_timestamps(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Datetime_SetPtr_timestamps(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_timestamps(
    Datetime* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Datetime_Set_intervals(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Datetime_SetPtr_intervals(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_intervals(
    Datetime* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Datetime_Set_mixed(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Datetime_SetPtr_mixed(
    Datetime* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Datetime_Clear_mixed(
    Datetime* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** Datetime provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Datetime_Self Datetime_Self;

MI_EXTERN_C void MI_CALL Datetime_Load(
    Datetime_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Datetime_Unload(
    Datetime_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Datetime_EnumerateInstances(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Datetime_GetInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Datetime_CreateInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* newInstance);

MI_EXTERN_C void MI_CALL Datetime_ModifyInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Datetime_DeleteInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* instanceName);


#endif /* _Datetime_h */
