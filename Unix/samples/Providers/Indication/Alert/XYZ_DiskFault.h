/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_DiskFault_h
#define _XYZ_DiskFault_h

#include <MI.h>
#include "CIM_Indication.h"

/*
**==============================================================================
**
** XYZ_DiskFault [XYZ_DiskFault]
**
** Keys:
**
**==============================================================================
*/

typedef struct _XYZ_DiskFault /* extends CIM_Indication */
{
    MI_Instance __instance;
    /* CIM_Indication properties */
    MI_ConstStringField IndicationIdentifier;
    MI_ConstStringAField CorrelatedIndications;
    MI_ConstDatetimeField IndicationTime;
    MI_ConstUint16Field PerceivedSeverity;
    MI_ConstStringField OtherSeverity;
    MI_ConstStringField IndicationFilterName;
    MI_ConstStringField SequenceContext;
    MI_ConstSint64Field SequenceNumber;
    /* XYZ_DiskFault properties */
    MI_ConstStringField detailmessage;
}
XYZ_DiskFault;

typedef struct _XYZ_DiskFault_Ref
{
    XYZ_DiskFault* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_DiskFault_Ref;

typedef struct _XYZ_DiskFault_ConstRef
{
    MI_CONST XYZ_DiskFault* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_DiskFault_ConstRef;

typedef struct _XYZ_DiskFault_Array
{
    struct _XYZ_DiskFault** data;
    MI_Uint32 size;
}
XYZ_DiskFault_Array;

typedef struct _XYZ_DiskFault_ConstArray
{
    struct _XYZ_DiskFault MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_DiskFault_ConstArray;

typedef struct _XYZ_DiskFault_ArrayRef
{
    XYZ_DiskFault_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_DiskFault_ArrayRef;

typedef struct _XYZ_DiskFault_ConstArrayRef
{
    XYZ_DiskFault_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_DiskFault_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_DiskFault_rtti;

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Construct(
    XYZ_DiskFault* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_DiskFault_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clone(
    const XYZ_DiskFault* self,
    XYZ_DiskFault** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_DiskFault_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_DiskFault_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Destruct(XYZ_DiskFault* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Delete(XYZ_DiskFault* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Post(
    const XYZ_DiskFault* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_IndicationIdentifier(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_IndicationIdentifier(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_IndicationIdentifier(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_CorrelatedIndications(
    XYZ_DiskFault* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_CorrelatedIndications(
    XYZ_DiskFault* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_CorrelatedIndications(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_IndicationTime(
    XYZ_DiskFault* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_IndicationTime(
    XYZ_DiskFault* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_PerceivedSeverity(
    XYZ_DiskFault* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_PerceivedSeverity(
    XYZ_DiskFault* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_OtherSeverity(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_OtherSeverity(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_OtherSeverity(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_IndicationFilterName(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_IndicationFilterName(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_IndicationFilterName(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_SequenceContext(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_SequenceContext(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_SequenceContext(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_SequenceNumber(
    XYZ_DiskFault* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_SequenceNumber(
    XYZ_DiskFault* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Set_detailmessage(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_SetPtr_detailmessage(
    XYZ_DiskFault* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_DiskFault_Clear_detailmessage(
    XYZ_DiskFault* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** XYZ_DiskFault provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_DiskFault_Self XYZ_DiskFault_Self;

MI_EXTERN_C void MI_CALL XYZ_DiskFault_Load(
    XYZ_DiskFault_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_DiskFault_Unload(
    XYZ_DiskFault_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_DiskFault_EnableIndications(
    XYZ_DiskFault_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL XYZ_DiskFault_DisableIndications(
    XYZ_DiskFault_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL XYZ_DiskFault_Subscribe(
    XYZ_DiskFault_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL XYZ_DiskFault_Unsubscribe(
    XYZ_DiskFault_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _XYZ_DiskFault_h */
