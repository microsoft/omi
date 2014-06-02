/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Test_Indication_h
#define _Test_Indication_h

#include <MI.h>
#include "Test_Class.h"

/*
**==============================================================================
**
** Test_Indication [Test_Indication]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Test_Indication
{
    MI_Instance __instance;
    /* Test_Indication properties */
    MI_ConstUint32Field id;
    MI_ConstStringField message;
    MI_ConstBooleanField sbool;
    MI_ConstUint8Field suint8;
    MI_ConstSint8Field ssint8;
    MI_ConstUint16Field sUINT16;
    MI_ConstSint16Field ssint16;
    MI_ConstUint32Field suint32;
    MI_ConstSint32Field ssint32;
    MI_ConstUint64Field suint64;
    MI_ConstSint64Field ssint64;
    MI_ConstReal32Field srEal32;
    MI_ConstReal64Field sREAL64;
    MI_ConstChar16Field schar16;
    MI_ConstStringField sstring;
    MI_ConstDatetimeField sDATETIME;
    MI_ConstBooleanAField a_bool;
    MI_ConstUint8AField a_uint8;
    MI_ConstSint8AField a_sint8;
    MI_ConstUint16AField a_UINT16;
    MI_ConstSint16AField a_sint16;
    MI_ConstUint32AField a_uint32;
    MI_ConstSint32AField a_sint32;
    MI_ConstUint64AField a_uint64;
    MI_ConstSint64AField a_sint64;
    MI_ConstReal32AField a_rEal32;
    MI_ConstReal64AField a_REAL64;
    MI_ConstChar16AField a_char16;
    MI_ConstStringAField a_string;
    MI_ConstDatetimeAField a_DATETIME;
    MI_ConstUint8AField a_octetBytes;
    MI_ConstStringAField a_octetStrings;
    Test_Class_ConstRef embeddedinstance;
    Test_Class_ConstArrayRef embeddedinstancearray;
    MI_ConstReferenceField embeddedobject;
    MI_ConstReferenceAField embeddedobjectarray;
}
Test_Indication;

typedef struct _Test_Indication_Ref
{
    Test_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Indication_Ref;

typedef struct _Test_Indication_ConstRef
{
    MI_CONST Test_Indication* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Indication_ConstRef;

typedef struct _Test_Indication_Array
{
    struct _Test_Indication** data;
    MI_Uint32 size;
}
Test_Indication_Array;

typedef struct _Test_Indication_ConstArray
{
    struct _Test_Indication MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Test_Indication_ConstArray;

typedef struct _Test_Indication_ArrayRef
{
    Test_Indication_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Indication_ArrayRef;

typedef struct _Test_Indication_ConstArrayRef
{
    Test_Indication_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Test_Indication_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Test_Indication_rtti;

MI_INLINE MI_Result MI_CALL Test_Indication_Construct(
    Test_Indication* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Test_Indication_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clone(
    const Test_Indication* self,
    Test_Indication** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Test_Indication_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Test_Indication_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Destruct(Test_Indication* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Delete(Test_Indication* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Post(
    const Test_Indication* self,
    MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_id(
    Test_Indication* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->id)->value = x;
    ((MI_Uint32Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_id(
    Test_Indication* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_message(
    Test_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_message(
    Test_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_message(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_sbool(
    Test_Indication* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->sbool)->value = x;
    ((MI_BooleanField*)&self->sbool)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_sbool(
    Test_Indication* self)
{
    memset((void*)&self->sbool, 0, sizeof(self->sbool));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_suint8(
    Test_Indication* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->suint8)->value = x;
    ((MI_Uint8Field*)&self->suint8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_suint8(
    Test_Indication* self)
{
    memset((void*)&self->suint8, 0, sizeof(self->suint8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_ssint8(
    Test_Indication* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->ssint8)->value = x;
    ((MI_Sint8Field*)&self->ssint8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_ssint8(
    Test_Indication* self)
{
    memset((void*)&self->ssint8, 0, sizeof(self->ssint8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_sUINT16(
    Test_Indication* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->sUINT16)->value = x;
    ((MI_Uint16Field*)&self->sUINT16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_sUINT16(
    Test_Indication* self)
{
    memset((void*)&self->sUINT16, 0, sizeof(self->sUINT16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_ssint16(
    Test_Indication* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->ssint16)->value = x;
    ((MI_Sint16Field*)&self->ssint16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_ssint16(
    Test_Indication* self)
{
    memset((void*)&self->ssint16, 0, sizeof(self->ssint16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_suint32(
    Test_Indication* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->suint32)->value = x;
    ((MI_Uint32Field*)&self->suint32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_suint32(
    Test_Indication* self)
{
    memset((void*)&self->suint32, 0, sizeof(self->suint32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_ssint32(
    Test_Indication* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->ssint32)->value = x;
    ((MI_Sint32Field*)&self->ssint32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_ssint32(
    Test_Indication* self)
{
    memset((void*)&self->ssint32, 0, sizeof(self->ssint32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_suint64(
    Test_Indication* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->suint64)->value = x;
    ((MI_Uint64Field*)&self->suint64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_suint64(
    Test_Indication* self)
{
    memset((void*)&self->suint64, 0, sizeof(self->suint64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_ssint64(
    Test_Indication* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->ssint64)->value = x;
    ((MI_Sint64Field*)&self->ssint64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_ssint64(
    Test_Indication* self)
{
    memset((void*)&self->ssint64, 0, sizeof(self->ssint64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_srEal32(
    Test_Indication* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->srEal32)->value = x;
    ((MI_Real32Field*)&self->srEal32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_srEal32(
    Test_Indication* self)
{
    memset((void*)&self->srEal32, 0, sizeof(self->srEal32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_sREAL64(
    Test_Indication* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->sREAL64)->value = x;
    ((MI_Real64Field*)&self->sREAL64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_sREAL64(
    Test_Indication* self)
{
    memset((void*)&self->sREAL64, 0, sizeof(self->sREAL64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_schar16(
    Test_Indication* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->schar16)->value = x;
    ((MI_Char16Field*)&self->schar16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_schar16(
    Test_Indication* self)
{
    memset((void*)&self->schar16, 0, sizeof(self->schar16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_sstring(
    Test_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_sstring(
    Test_Indication* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_sstring(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_sDATETIME(
    Test_Indication* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->sDATETIME)->value = x;
    ((MI_DatetimeField*)&self->sDATETIME)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_sDATETIME(
    Test_Indication* self)
{
    memset((void*)&self->sDATETIME, 0, sizeof(self->sDATETIME));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_bool(
    Test_Indication* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_bool(
    Test_Indication* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_bool(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_uint8(
    Test_Indication* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_uint8(
    Test_Indication* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_uint8(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_sint8(
    Test_Indication* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_sint8(
    Test_Indication* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_sint8(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_UINT16(
    Test_Indication* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_UINT16(
    Test_Indication* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_UINT16(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_sint16(
    Test_Indication* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_sint16(
    Test_Indication* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_sint16(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_uint32(
    Test_Indication* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_uint32(
    Test_Indication* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_uint32(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_sint32(
    Test_Indication* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_sint32(
    Test_Indication* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_sint32(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_uint64(
    Test_Indication* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_uint64(
    Test_Indication* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_uint64(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_sint64(
    Test_Indication* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_sint64(
    Test_Indication* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_sint64(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_rEal32(
    Test_Indication* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_rEal32(
    Test_Indication* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_rEal32(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_REAL64(
    Test_Indication* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_REAL64(
    Test_Indication* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_REAL64(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_char16(
    Test_Indication* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_char16(
    Test_Indication* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_char16(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_string(
    Test_Indication* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_string(
    Test_Indication* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_string(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_DATETIME(
    Test_Indication* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_DATETIME(
    Test_Indication* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_DATETIME(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_octetBytes(
    Test_Indication* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_octetBytes(
    Test_Indication* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_octetBytes(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_a_octetStrings(
    Test_Indication* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_a_octetStrings(
    Test_Indication* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_a_octetStrings(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_embeddedinstance(
    Test_Indication* self,
    const Test_Class* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_embeddedinstance(
    Test_Indication* self,
    const Test_Class* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_embeddedinstance(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_embeddedinstancearray(
    Test_Indication* self,
    const Test_Class * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_embeddedinstancearray(
    Test_Indication* self,
    const Test_Class * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_embeddedinstancearray(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        33);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_embeddedobject(
    Test_Indication* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_embeddedobject(
    Test_Indication* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_embeddedobject(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        34);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Set_embeddedobjectarray(
    Test_Indication* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL Test_Indication_SetPtr_embeddedobjectarray(
    Test_Indication* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Test_Indication_Clear_embeddedobjectarray(
    Test_Indication* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

/*
**==============================================================================
**
** Test_Indication provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Test_Indication_Self Test_Indication_Self;

MI_EXTERN_C void MI_CALL Test_Indication_Load(
    Test_Indication_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_Indication_Unload(
    Test_Indication_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Test_Indication_EnableIndications(
    Test_Indication_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL Test_Indication_DisableIndications(
    Test_Indication_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL Test_Indication_Subscribe(
    Test_Indication_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL Test_Indication_Unsubscribe(
    Test_Indication_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _Test_Indication_h */
