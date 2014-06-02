/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _L_IndicationC3_h
#define _L_IndicationC3_h

#include <MI.h>
#include "L_IndicationC2.h"

/*
**==============================================================================
**
** L_IndicationC3 [L_IndicationC3]
**
** Keys:
**
**==============================================================================
*/

typedef struct _L_IndicationC3 /* extends L_IndicationC2 */
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
    /* L_IndicationC2 properties */
    MI_ConstUint32Field lcode2;
    /* L_IndicationC3 properties */
    MI_ConstUint32Field lcode3;
}
L_IndicationC3;

typedef struct _L_IndicationC3_Ref
{
    L_IndicationC3* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC3_Ref;

typedef struct _L_IndicationC3_ConstRef
{
    MI_CONST L_IndicationC3* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC3_ConstRef;

typedef struct _L_IndicationC3_Array
{
    struct _L_IndicationC3** data;
    MI_Uint32 size;
}
L_IndicationC3_Array;

typedef struct _L_IndicationC3_ConstArray
{
    struct _L_IndicationC3 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
L_IndicationC3_ConstArray;

typedef struct _L_IndicationC3_ArrayRef
{
    L_IndicationC3_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC3_ArrayRef;

typedef struct _L_IndicationC3_ConstArrayRef
{
    L_IndicationC3_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
L_IndicationC3_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl L_IndicationC3_rtti;

MI_INLINE MI_Result MI_CALL L_IndicationC3_Construct(
    L_IndicationC3* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &L_IndicationC3_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clone(
    const L_IndicationC3* self,
    L_IndicationC3** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL L_IndicationC3_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &L_IndicationC3_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Destruct(L_IndicationC3* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Delete(L_IndicationC3* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Post(
    const L_IndicationC3* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_IndicationIdentifier(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_IndicationIdentifier(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_IndicationIdentifier(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_CorrelatedIndications(
    L_IndicationC3* self,
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

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_CorrelatedIndications(
    L_IndicationC3* self,
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

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_CorrelatedIndications(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_IndicationTime(
    L_IndicationC3* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->IndicationTime)->value = x;
    ((MI_DatetimeField*)&self->IndicationTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_IndicationTime(
    L_IndicationC3* self)
{
    memset((void*)&self->IndicationTime, 0, sizeof(self->IndicationTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_PerceivedSeverity(
    L_IndicationC3* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PerceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->PerceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_PerceivedSeverity(
    L_IndicationC3* self)
{
    memset((void*)&self->PerceivedSeverity, 0, sizeof(self->PerceivedSeverity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_OtherSeverity(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_OtherSeverity(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_OtherSeverity(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_IndicationFilterName(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_IndicationFilterName(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_IndicationFilterName(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_SequenceContext(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_SequenceContext(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_SequenceContext(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_SequenceNumber(
    L_IndicationC3* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->SequenceNumber)->value = x;
    ((MI_Sint64Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_SequenceNumber(
    L_IndicationC3* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_id(
    L_IndicationC3* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_id(
    L_IndicationC3* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_message(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_SetPtr_message(
    L_IndicationC3* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_message(
    L_IndicationC3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_lcode1(
    L_IndicationC3* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->lcode1)->value = x;
    ((MI_Uint32Field*)&self->lcode1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_lcode1(
    L_IndicationC3* self)
{
    memset((void*)&self->lcode1, 0, sizeof(self->lcode1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_lcode2(
    L_IndicationC3* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->lcode2)->value = x;
    ((MI_Uint32Field*)&self->lcode2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_lcode2(
    L_IndicationC3* self)
{
    memset((void*)&self->lcode2, 0, sizeof(self->lcode2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Set_lcode3(
    L_IndicationC3* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->lcode3)->value = x;
    ((MI_Uint32Field*)&self->lcode3)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL L_IndicationC3_Clear_lcode3(
    L_IndicationC3* self)
{
    memset((void*)&self->lcode3, 0, sizeof(self->lcode3));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** L_IndicationC3 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _L_IndicationC3_Self L_IndicationC3_Self;

MI_EXTERN_C void MI_CALL L_IndicationC3_Load(
    L_IndicationC3_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_IndicationC3_Unload(
    L_IndicationC3_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL L_IndicationC3_EnableIndications(
    L_IndicationC3_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL L_IndicationC3_DisableIndications(
    L_IndicationC3_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL L_IndicationC3_Subscribe(
    L_IndicationC3_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL L_IndicationC3_Unsubscribe(
    L_IndicationC3_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _L_IndicationC3_h */
