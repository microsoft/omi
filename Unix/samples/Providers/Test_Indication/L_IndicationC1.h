/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_IndicationC1_h
#define _L_IndicationC1_h

#include <MI.h>
#include "L_Indication.h"

/*
**==============================================================================
**
** L_IndicationC1 [L_IndicationC1]
**
** Keys:
**
**==============================================================================
*/

typedef struct _L_IndicationC1 /* extends L_Indication */
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
    /* L_IndicationC1 properties */
    MI_ConstUint32Field lcode1;
}
L_IndicationC1;

typedef struct _L_IndicationC1_Ref
{
    L_IndicationC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC1_Ref;

typedef struct _L_IndicationC1_ConstRef
{
    MI_CONST L_IndicationC1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC1_ConstRef;

typedef struct _L_IndicationC1_Array
{
    struct _L_IndicationC1** data;
    MI_Uint32 size;
}
L_IndicationC1_Array;

typedef struct _L_IndicationC1_ConstArray
{
    struct _L_IndicationC1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_IndicationC1_ConstArray;

typedef struct _L_IndicationC1_ArrayRef
{
    L_IndicationC1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC1_ArrayRef;

typedef struct _L_IndicationC1_ConstArrayRef
{
    L_IndicationC1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC1_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_IndicationC1_rtti;

MI_INLINE MI_Result MI_CALL L_IndicationC1_Construct(
    L_IndicationC1* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_IndicationC1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clone(
    const L_IndicationC1* self,
    L_IndicationC1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_IndicationC1_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_IndicationC1_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Destruct(L_IndicationC1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Delete(L_IndicationC1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Post(
    const L_IndicationC1* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_IndicationIdentifier(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_IndicationIdentifier(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_IndicationIdentifier(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_CorrelatedIndications(
    L_IndicationC1* self,
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

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_CorrelatedIndications(
    L_IndicationC1* self,
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

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_CorrelatedIndications(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_IndicationTime(
    L_IndicationC1* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_IndicationTime(
    L_IndicationC1* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_PerceivedSeverity(
    L_IndicationC1* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_PerceivedSeverity(
    L_IndicationC1* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_OtherSeverity(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_OtherSeverity(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_OtherSeverity(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_IndicationFilterName(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_IndicationFilterName(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_IndicationFilterName(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_SequenceContext(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_SequenceContext(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_SequenceContext(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_SequenceNumber(
    L_IndicationC1* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_SequenceNumber(
    L_IndicationC1* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_id(
    L_IndicationC1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_id(
    L_IndicationC1* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_message(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_SetPtr_message(
    L_IndicationC1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_message(
    L_IndicationC1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Set_lcode1(
    L_IndicationC1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->lcode1)->value = x;
    ((MI_Uint32Field*)&self->lcode1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC1_Clear_lcode1(
    L_IndicationC1* self)
{
    memset((void*)&self->lcode1, 0, sizeof(self->lcode1));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_IndicationC1 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _L_IndicationC1_Self L_IndicationC1_Self;

MI_EXTERN_C void MI_CALL L_IndicationC1_Load(
    L_IndicationC1_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_IndicationC1_Unload(
    L_IndicationC1_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_IndicationC1_EnableIndications(
    L_IndicationC1_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL L_IndicationC1_DisableIndications(
    L_IndicationC1_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL L_IndicationC1_Subscribe(
    L_IndicationC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL L_IndicationC1_Unsubscribe(
    L_IndicationC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _L_IndicationC1_h */
