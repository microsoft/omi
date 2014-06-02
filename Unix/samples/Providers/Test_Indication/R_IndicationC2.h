/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _R_IndicationC2_h
#define _R_IndicationC2_h

#include <MI.h>
#include "R_IndicationC1.h"

/*
**==============================================================================
**
** R_IndicationC2 [R_IndicationC2]
**
** Keys:
**
**==============================================================================
*/

typedef struct _R_IndicationC2 /* extends R_IndicationC1 */
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
    /* L_Indication properties */
    MI_ConstUint32Field id;
    MI_ConstStringField message;
    /* R_Indication properties */
    /* R_IndicationC1 properties */
    MI_ConstUint32Field rcode1;
    /* R_IndicationC2 properties */
    MI_ConstUint32Field rcode2;
}
R_IndicationC2;

typedef struct _R_IndicationC2_Ref
{
    R_IndicationC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_IndicationC2_Ref;

typedef struct _R_IndicationC2_ConstRef
{
    MI_CONST R_IndicationC2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_IndicationC2_ConstRef;

typedef struct _R_IndicationC2_Array
{
    struct _R_IndicationC2** data;
    MI_Uint32 size;
}
R_IndicationC2_Array;

typedef struct _R_IndicationC2_ConstArray
{
    struct _R_IndicationC2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
R_IndicationC2_ConstArray;

typedef struct _R_IndicationC2_ArrayRef
{
    R_IndicationC2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_IndicationC2_ArrayRef;

typedef struct _R_IndicationC2_ConstArrayRef
{
    R_IndicationC2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
R_IndicationC2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl R_IndicationC2_rtti;

MI_INLINE MI_Result MI_CALL R_IndicationC2_Construct(
    R_IndicationC2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &R_IndicationC2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clone(
    const R_IndicationC2* self,
    R_IndicationC2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL R_IndicationC2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &R_IndicationC2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Destruct(R_IndicationC2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Delete(R_IndicationC2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Post(
    const R_IndicationC2* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_IndicationIdentifier(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_IndicationIdentifier(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_IndicationIdentifier(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_CorrelatedIndications(
    R_IndicationC2* self,
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

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_CorrelatedIndications(
    R_IndicationC2* self,
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

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_CorrelatedIndications(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_IndicationTime(
    R_IndicationC2* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_IndicationTime(
    R_IndicationC2* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_PerceivedSeverity(
    R_IndicationC2* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_PerceivedSeverity(
    R_IndicationC2* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_OtherSeverity(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_OtherSeverity(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_OtherSeverity(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_IndicationFilterName(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_IndicationFilterName(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_IndicationFilterName(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_SequenceContext(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_SequenceContext(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_SequenceContext(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_SequenceNumber(
    R_IndicationC2* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_SequenceNumber(
    R_IndicationC2* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_id(
    R_IndicationC2* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_id(
    R_IndicationC2* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_message(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_SetPtr_message(
    R_IndicationC2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_message(
    R_IndicationC2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_rcode1(
    R_IndicationC2* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->rcode1)->value = x;
    ((MI_Uint32Field*)&self->rcode1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_rcode1(
    R_IndicationC2* self)
{
    memset((void*)&self->rcode1, 0, sizeof(self->rcode1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Set_rcode2(
    R_IndicationC2* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->rcode2)->value = x;
    ((MI_Uint32Field*)&self->rcode2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL R_IndicationC2_Clear_rcode2(
    R_IndicationC2* self)
{
    memset((void*)&self->rcode2, 0, sizeof(self->rcode2));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** R_IndicationC2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _R_IndicationC2_Self R_IndicationC2_Self;

MI_EXTERN_C void MI_CALL R_IndicationC2_Load(
    R_IndicationC2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_IndicationC2_Unload(
    R_IndicationC2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL R_IndicationC2_EnableIndications(
    R_IndicationC2_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL R_IndicationC2_DisableIndications(
    R_IndicationC2_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL R_IndicationC2_Subscribe(
    R_IndicationC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL R_IndicationC2_Unsubscribe(
    R_IndicationC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _R_IndicationC2_h */
