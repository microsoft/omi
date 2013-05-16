/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _AllTypes_h
#define _AllTypes_h

#include <MI.h>
#include "Main.h"
#include "Reference.h"

/*
**==============================================================================
**
** AllTypes [Demo_TestWithAllTypes]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _AllTypes
{
    MI_Instance __instance;
    /* AllTypes properties */
    /*KEY*/ MI_ConstUint64Field id;
    Main_ConstRef refMain;
    Reference_ConstRef refRef;
    MI_ConstBooleanField boolValue;
    MI_ConstUint8Field uint8Value;
    MI_ConstSint8Field sint8Value;
    MI_ConstUint16Field uint16Value;
    MI_ConstSint16Field sint16Value;
    MI_ConstUint32Field uint32Value;
    MI_ConstSint32Field sint32Value;
    MI_ConstUint64Field uint64Value;
    MI_ConstSint64Field sint64Value;
    MI_ConstReal32Field real32Value;
    MI_ConstReal64Field real64Value;
    MI_ConstDatetimeField datetimetValue;
    MI_ConstStringField stringValue;
    MI_ConstChar16Field char16Value;
    Main_ConstRef instanceTest;
    MI_ConstBooleanAField boolArray;
    MI_ConstUint8AField uint8Array;
    MI_ConstSint8AField sint8Array;
    MI_ConstUint16AField uint16Array;
    MI_ConstSint16AField sint16Array;
    MI_ConstUint32AField uint32Array;
    MI_ConstSint32AField sint32Array;
    MI_ConstUint64AField uint64Array;
    MI_ConstSint64AField sint64Array;
    MI_ConstReal32AField real32Array;
    MI_ConstReal64AField real64Array;
    MI_ConstDatetimeAField datetimeArray;
    MI_ConstStringAField stringArray;
    MI_ConstChar16AField char16Array;
    Main_ConstArrayRef instanceArrayTest;
}
AllTypes;

typedef struct _AllTypes_Ref
{
    AllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
AllTypes_Ref;

typedef struct _AllTypes_ConstRef
{
    MI_CONST AllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
AllTypes_ConstRef;

typedef struct _AllTypes_Array
{
    struct _AllTypes** data;
    MI_Uint32 size;
}
AllTypes_Array;

typedef struct _AllTypes_ConstArray
{
    struct _AllTypes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
AllTypes_ConstArray;

typedef struct _AllTypes_ArrayRef
{
    AllTypes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
AllTypes_ArrayRef;

typedef struct _AllTypes_ConstArrayRef
{
    AllTypes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
AllTypes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl AllTypes_rtti;

MI_INLINE MI_Result MI_CALL AllTypes_Construct(
    AllTypes* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &AllTypes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clone(
    const AllTypes* self,
    AllTypes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL AllTypes_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &AllTypes_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL AllTypes_Destruct(AllTypes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL AllTypes_Delete(AllTypes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL AllTypes_Post(
    const AllTypes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_id(
    AllTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_id(
    AllTypes* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_refMain(
    AllTypes* self,
    const Main* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_refMain(
    AllTypes* self,
    const Main* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_refMain(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_refRef(
    AllTypes* self,
    const Reference* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_refRef(
    AllTypes* self,
    const Reference* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_refRef(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_boolValue(
    AllTypes* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->boolValue)->value = x;
    ((MI_BooleanField*)&self->boolValue)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_boolValue(
    AllTypes* self)
{
    memset((void*)&self->boolValue, 0, sizeof(self->boolValue));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint8Value(
    AllTypes* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Value)->value = x;
    ((MI_Uint8Field*)&self->uint8Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint8Value(
    AllTypes* self)
{
    memset((void*)&self->uint8Value, 0, sizeof(self->uint8Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint8Value(
    AllTypes* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Value)->value = x;
    ((MI_Sint8Field*)&self->sint8Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint8Value(
    AllTypes* self)
{
    memset((void*)&self->sint8Value, 0, sizeof(self->sint8Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint16Value(
    AllTypes* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Value)->value = x;
    ((MI_Uint16Field*)&self->uint16Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint16Value(
    AllTypes* self)
{
    memset((void*)&self->uint16Value, 0, sizeof(self->uint16Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint16Value(
    AllTypes* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Value)->value = x;
    ((MI_Sint16Field*)&self->sint16Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint16Value(
    AllTypes* self)
{
    memset((void*)&self->sint16Value, 0, sizeof(self->sint16Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint32Value(
    AllTypes* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Value)->value = x;
    ((MI_Uint32Field*)&self->uint32Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint32Value(
    AllTypes* self)
{
    memset((void*)&self->uint32Value, 0, sizeof(self->uint32Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint32Value(
    AllTypes* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Value)->value = x;
    ((MI_Sint32Field*)&self->sint32Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint32Value(
    AllTypes* self)
{
    memset((void*)&self->sint32Value, 0, sizeof(self->sint32Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint64Value(
    AllTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Value)->value = x;
    ((MI_Uint64Field*)&self->uint64Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint64Value(
    AllTypes* self)
{
    memset((void*)&self->uint64Value, 0, sizeof(self->uint64Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint64Value(
    AllTypes* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Value)->value = x;
    ((MI_Sint64Field*)&self->sint64Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint64Value(
    AllTypes* self)
{
    memset((void*)&self->sint64Value, 0, sizeof(self->sint64Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_real32Value(
    AllTypes* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Value)->value = x;
    ((MI_Real32Field*)&self->real32Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_real32Value(
    AllTypes* self)
{
    memset((void*)&self->real32Value, 0, sizeof(self->real32Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_real64Value(
    AllTypes* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Value)->value = x;
    ((MI_Real64Field*)&self->real64Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_real64Value(
    AllTypes* self)
{
    memset((void*)&self->real64Value, 0, sizeof(self->real64Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_datetimetValue(
    AllTypes* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimetValue)->value = x;
    ((MI_DatetimeField*)&self->datetimetValue)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_datetimetValue(
    AllTypes* self)
{
    memset((void*)&self->datetimetValue, 0, sizeof(self->datetimetValue));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_stringValue(
    AllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_stringValue(
    AllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_stringValue(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_char16Value(
    AllTypes* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Value)->value = x;
    ((MI_Char16Field*)&self->char16Value)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_char16Value(
    AllTypes* self)
{
    memset((void*)&self->char16Value, 0, sizeof(self->char16Value));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_instanceTest(
    AllTypes* self,
    const Main* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_instanceTest(
    AllTypes* self,
    const Main* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_instanceTest(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_boolArray(
    AllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_boolArray(
    AllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_boolArray(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint8Array(
    AllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_uint8Array(
    AllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint8Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint8Array(
    AllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_sint8Array(
    AllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint8Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint16Array(
    AllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_uint16Array(
    AllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint16Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint16Array(
    AllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_sint16Array(
    AllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint16Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint32Array(
    AllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_uint32Array(
    AllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint32Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint32Array(
    AllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_sint32Array(
    AllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint32Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_uint64Array(
    AllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_uint64Array(
    AllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_uint64Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_sint64Array(
    AllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_sint64Array(
    AllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_sint64Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_real32Array(
    AllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_real32Array(
    AllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_real32Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_real64Array(
    AllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_real64Array(
    AllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_real64Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_datetimeArray(
    AllTypes* self,
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

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_datetimeArray(
    AllTypes* self,
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

MI_INLINE MI_Result MI_CALL AllTypes_Clear_datetimeArray(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_stringArray(
    AllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_stringArray(
    AllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_stringArray(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_char16Array(
    AllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_char16Array(
    AllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_char16Array(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

MI_INLINE MI_Result MI_CALL AllTypes_Set_instanceArrayTest(
    AllTypes* self,
    const Main * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL AllTypes_SetPtr_instanceArrayTest(
    AllTypes* self,
    const Main * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL AllTypes_Clear_instanceArrayTest(
    AllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

/*
**==============================================================================
**
** AllTypes provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _AllTypes_Self AllTypes_Self;

MI_EXTERN_C void MI_CALL AllTypes_Load(
    AllTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL AllTypes_Unload(
    AllTypes_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL AllTypes_EnumerateInstances(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL AllTypes_GetInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL AllTypes_CreateInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* newInstance);

MI_EXTERN_C void MI_CALL AllTypes_ModifyInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL AllTypes_DeleteInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* instanceName);

MI_EXTERN_C void MI_CALL AllTypes_AssociatorInstancesrefMain(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL AllTypes_AssociatorInstancesrefRef(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL AllTypes_ReferenceInstancesrefMain(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL AllTypes_ReferenceInstancesrefRef(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


/*
**==============================================================================
**
** AllTypes_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class AllTypes_Class : public Instance
{
public:
    
    typedef AllTypes Self;
    
    AllTypes_Class() :
        Instance(&AllTypes_rtti)
    {
    }
    
    AllTypes_Class(
        const AllTypes* instanceName,
        bool keysOnly) :
        Instance(
            &AllTypes_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    AllTypes_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    AllTypes_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    AllTypes_Class& operator=(
        const AllTypes_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    AllTypes_Class(
        const AllTypes_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &AllTypes_rtti;
    }

    //
    // AllTypes_Class.id
    //
    
    const Field<Uint64>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n);
    }
    
    void id(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).value;
    }
    
    void id_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Clear();
    }

    //
    // AllTypes_Class.refMain
    //
    
    const Field<Main_Class>& refMain() const
    {
        const size_t n = offsetof(Self, refMain);
        return GetField<Main_Class>(n);
    }
    
    void refMain(const Field<Main_Class>& x)
    {
        const size_t n = offsetof(Self, refMain);
        GetField<Main_Class>(n) = x;
    }
    
    const Main_Class& refMain_value() const
    {
        const size_t n = offsetof(Self, refMain);
        return GetField<Main_Class>(n).value;
    }
    
    void refMain_value(const Main_Class& x)
    {
        const size_t n = offsetof(Self, refMain);
        GetField<Main_Class>(n).Set(x);
    }
    
    bool refMain_exists() const
    {
        const size_t n = offsetof(Self, refMain);
        return GetField<Main_Class>(n).exists ? true : false;
    }
    
    void refMain_clear()
    {
        const size_t n = offsetof(Self, refMain);
        GetField<Main_Class>(n).Clear();
    }

    //
    // AllTypes_Class.refRef
    //
    
    const Field<Reference_Class>& refRef() const
    {
        const size_t n = offsetof(Self, refRef);
        return GetField<Reference_Class>(n);
    }
    
    void refRef(const Field<Reference_Class>& x)
    {
        const size_t n = offsetof(Self, refRef);
        GetField<Reference_Class>(n) = x;
    }
    
    const Reference_Class& refRef_value() const
    {
        const size_t n = offsetof(Self, refRef);
        return GetField<Reference_Class>(n).value;
    }
    
    void refRef_value(const Reference_Class& x)
    {
        const size_t n = offsetof(Self, refRef);
        GetField<Reference_Class>(n).Set(x);
    }
    
    bool refRef_exists() const
    {
        const size_t n = offsetof(Self, refRef);
        return GetField<Reference_Class>(n).exists ? true : false;
    }
    
    void refRef_clear()
    {
        const size_t n = offsetof(Self, refRef);
        GetField<Reference_Class>(n).Clear();
    }

    //
    // AllTypes_Class.boolValue
    //
    
    const Field<Boolean>& boolValue() const
    {
        const size_t n = offsetof(Self, boolValue);
        return GetField<Boolean>(n);
    }
    
    void boolValue(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, boolValue);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& boolValue_value() const
    {
        const size_t n = offsetof(Self, boolValue);
        return GetField<Boolean>(n).value;
    }
    
    void boolValue_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, boolValue);
        GetField<Boolean>(n).Set(x);
    }
    
    bool boolValue_exists() const
    {
        const size_t n = offsetof(Self, boolValue);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void boolValue_clear()
    {
        const size_t n = offsetof(Self, boolValue);
        GetField<Boolean>(n).Clear();
    }

    //
    // AllTypes_Class.uint8Value
    //
    
    const Field<Uint8>& uint8Value() const
    {
        const size_t n = offsetof(Self, uint8Value);
        return GetField<Uint8>(n);
    }
    
    void uint8Value(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, uint8Value);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& uint8Value_value() const
    {
        const size_t n = offsetof(Self, uint8Value);
        return GetField<Uint8>(n).value;
    }
    
    void uint8Value_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, uint8Value);
        GetField<Uint8>(n).Set(x);
    }
    
    bool uint8Value_exists() const
    {
        const size_t n = offsetof(Self, uint8Value);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void uint8Value_clear()
    {
        const size_t n = offsetof(Self, uint8Value);
        GetField<Uint8>(n).Clear();
    }

    //
    // AllTypes_Class.sint8Value
    //
    
    const Field<Sint8>& sint8Value() const
    {
        const size_t n = offsetof(Self, sint8Value);
        return GetField<Sint8>(n);
    }
    
    void sint8Value(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, sint8Value);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& sint8Value_value() const
    {
        const size_t n = offsetof(Self, sint8Value);
        return GetField<Sint8>(n).value;
    }
    
    void sint8Value_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, sint8Value);
        GetField<Sint8>(n).Set(x);
    }
    
    bool sint8Value_exists() const
    {
        const size_t n = offsetof(Self, sint8Value);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void sint8Value_clear()
    {
        const size_t n = offsetof(Self, sint8Value);
        GetField<Sint8>(n).Clear();
    }

    //
    // AllTypes_Class.uint16Value
    //
    
    const Field<Uint16>& uint16Value() const
    {
        const size_t n = offsetof(Self, uint16Value);
        return GetField<Uint16>(n);
    }
    
    void uint16Value(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, uint16Value);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& uint16Value_value() const
    {
        const size_t n = offsetof(Self, uint16Value);
        return GetField<Uint16>(n).value;
    }
    
    void uint16Value_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, uint16Value);
        GetField<Uint16>(n).Set(x);
    }
    
    bool uint16Value_exists() const
    {
        const size_t n = offsetof(Self, uint16Value);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void uint16Value_clear()
    {
        const size_t n = offsetof(Self, uint16Value);
        GetField<Uint16>(n).Clear();
    }

    //
    // AllTypes_Class.sint16Value
    //
    
    const Field<Sint16>& sint16Value() const
    {
        const size_t n = offsetof(Self, sint16Value);
        return GetField<Sint16>(n);
    }
    
    void sint16Value(const Field<Sint16>& x)
    {
        const size_t n = offsetof(Self, sint16Value);
        GetField<Sint16>(n) = x;
    }
    
    const Sint16& sint16Value_value() const
    {
        const size_t n = offsetof(Self, sint16Value);
        return GetField<Sint16>(n).value;
    }
    
    void sint16Value_value(const Sint16& x)
    {
        const size_t n = offsetof(Self, sint16Value);
        GetField<Sint16>(n).Set(x);
    }
    
    bool sint16Value_exists() const
    {
        const size_t n = offsetof(Self, sint16Value);
        return GetField<Sint16>(n).exists ? true : false;
    }
    
    void sint16Value_clear()
    {
        const size_t n = offsetof(Self, sint16Value);
        GetField<Sint16>(n).Clear();
    }

    //
    // AllTypes_Class.uint32Value
    //
    
    const Field<Uint32>& uint32Value() const
    {
        const size_t n = offsetof(Self, uint32Value);
        return GetField<Uint32>(n);
    }
    
    void uint32Value(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, uint32Value);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& uint32Value_value() const
    {
        const size_t n = offsetof(Self, uint32Value);
        return GetField<Uint32>(n).value;
    }
    
    void uint32Value_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, uint32Value);
        GetField<Uint32>(n).Set(x);
    }
    
    bool uint32Value_exists() const
    {
        const size_t n = offsetof(Self, uint32Value);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void uint32Value_clear()
    {
        const size_t n = offsetof(Self, uint32Value);
        GetField<Uint32>(n).Clear();
    }

    //
    // AllTypes_Class.sint32Value
    //
    
    const Field<Sint32>& sint32Value() const
    {
        const size_t n = offsetof(Self, sint32Value);
        return GetField<Sint32>(n);
    }
    
    void sint32Value(const Field<Sint32>& x)
    {
        const size_t n = offsetof(Self, sint32Value);
        GetField<Sint32>(n) = x;
    }
    
    const Sint32& sint32Value_value() const
    {
        const size_t n = offsetof(Self, sint32Value);
        return GetField<Sint32>(n).value;
    }
    
    void sint32Value_value(const Sint32& x)
    {
        const size_t n = offsetof(Self, sint32Value);
        GetField<Sint32>(n).Set(x);
    }
    
    bool sint32Value_exists() const
    {
        const size_t n = offsetof(Self, sint32Value);
        return GetField<Sint32>(n).exists ? true : false;
    }
    
    void sint32Value_clear()
    {
        const size_t n = offsetof(Self, sint32Value);
        GetField<Sint32>(n).Clear();
    }

    //
    // AllTypes_Class.uint64Value
    //
    
    const Field<Uint64>& uint64Value() const
    {
        const size_t n = offsetof(Self, uint64Value);
        return GetField<Uint64>(n);
    }
    
    void uint64Value(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, uint64Value);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& uint64Value_value() const
    {
        const size_t n = offsetof(Self, uint64Value);
        return GetField<Uint64>(n).value;
    }
    
    void uint64Value_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, uint64Value);
        GetField<Uint64>(n).Set(x);
    }
    
    bool uint64Value_exists() const
    {
        const size_t n = offsetof(Self, uint64Value);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void uint64Value_clear()
    {
        const size_t n = offsetof(Self, uint64Value);
        GetField<Uint64>(n).Clear();
    }

    //
    // AllTypes_Class.sint64Value
    //
    
    const Field<Sint64>& sint64Value() const
    {
        const size_t n = offsetof(Self, sint64Value);
        return GetField<Sint64>(n);
    }
    
    void sint64Value(const Field<Sint64>& x)
    {
        const size_t n = offsetof(Self, sint64Value);
        GetField<Sint64>(n) = x;
    }
    
    const Sint64& sint64Value_value() const
    {
        const size_t n = offsetof(Self, sint64Value);
        return GetField<Sint64>(n).value;
    }
    
    void sint64Value_value(const Sint64& x)
    {
        const size_t n = offsetof(Self, sint64Value);
        GetField<Sint64>(n).Set(x);
    }
    
    bool sint64Value_exists() const
    {
        const size_t n = offsetof(Self, sint64Value);
        return GetField<Sint64>(n).exists ? true : false;
    }
    
    void sint64Value_clear()
    {
        const size_t n = offsetof(Self, sint64Value);
        GetField<Sint64>(n).Clear();
    }

    //
    // AllTypes_Class.real32Value
    //
    
    const Field<Real32>& real32Value() const
    {
        const size_t n = offsetof(Self, real32Value);
        return GetField<Real32>(n);
    }
    
    void real32Value(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, real32Value);
        GetField<Real32>(n) = x;
    }
    
    const Real32& real32Value_value() const
    {
        const size_t n = offsetof(Self, real32Value);
        return GetField<Real32>(n).value;
    }
    
    void real32Value_value(const Real32& x)
    {
        const size_t n = offsetof(Self, real32Value);
        GetField<Real32>(n).Set(x);
    }
    
    bool real32Value_exists() const
    {
        const size_t n = offsetof(Self, real32Value);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void real32Value_clear()
    {
        const size_t n = offsetof(Self, real32Value);
        GetField<Real32>(n).Clear();
    }

    //
    // AllTypes_Class.real64Value
    //
    
    const Field<Real64>& real64Value() const
    {
        const size_t n = offsetof(Self, real64Value);
        return GetField<Real64>(n);
    }
    
    void real64Value(const Field<Real64>& x)
    {
        const size_t n = offsetof(Self, real64Value);
        GetField<Real64>(n) = x;
    }
    
    const Real64& real64Value_value() const
    {
        const size_t n = offsetof(Self, real64Value);
        return GetField<Real64>(n).value;
    }
    
    void real64Value_value(const Real64& x)
    {
        const size_t n = offsetof(Self, real64Value);
        GetField<Real64>(n).Set(x);
    }
    
    bool real64Value_exists() const
    {
        const size_t n = offsetof(Self, real64Value);
        return GetField<Real64>(n).exists ? true : false;
    }
    
    void real64Value_clear()
    {
        const size_t n = offsetof(Self, real64Value);
        GetField<Real64>(n).Clear();
    }

    //
    // AllTypes_Class.datetimetValue
    //
    
    const Field<Datetime>& datetimetValue() const
    {
        const size_t n = offsetof(Self, datetimetValue);
        return GetField<Datetime>(n);
    }
    
    void datetimetValue(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, datetimetValue);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& datetimetValue_value() const
    {
        const size_t n = offsetof(Self, datetimetValue);
        return GetField<Datetime>(n).value;
    }
    
    void datetimetValue_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, datetimetValue);
        GetField<Datetime>(n).Set(x);
    }
    
    bool datetimetValue_exists() const
    {
        const size_t n = offsetof(Self, datetimetValue);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void datetimetValue_clear()
    {
        const size_t n = offsetof(Self, datetimetValue);
        GetField<Datetime>(n).Clear();
    }

    //
    // AllTypes_Class.stringValue
    //
    
    const Field<String>& stringValue() const
    {
        const size_t n = offsetof(Self, stringValue);
        return GetField<String>(n);
    }
    
    void stringValue(const Field<String>& x)
    {
        const size_t n = offsetof(Self, stringValue);
        GetField<String>(n) = x;
    }
    
    const String& stringValue_value() const
    {
        const size_t n = offsetof(Self, stringValue);
        return GetField<String>(n).value;
    }
    
    void stringValue_value(const String& x)
    {
        const size_t n = offsetof(Self, stringValue);
        GetField<String>(n).Set(x);
    }
    
    bool stringValue_exists() const
    {
        const size_t n = offsetof(Self, stringValue);
        return GetField<String>(n).exists ? true : false;
    }
    
    void stringValue_clear()
    {
        const size_t n = offsetof(Self, stringValue);
        GetField<String>(n).Clear();
    }

    //
    // AllTypes_Class.char16Value
    //
    
    const Field<Char16>& char16Value() const
    {
        const size_t n = offsetof(Self, char16Value);
        return GetField<Char16>(n);
    }
    
    void char16Value(const Field<Char16>& x)
    {
        const size_t n = offsetof(Self, char16Value);
        GetField<Char16>(n) = x;
    }
    
    const Char16& char16Value_value() const
    {
        const size_t n = offsetof(Self, char16Value);
        return GetField<Char16>(n).value;
    }
    
    void char16Value_value(const Char16& x)
    {
        const size_t n = offsetof(Self, char16Value);
        GetField<Char16>(n).Set(x);
    }
    
    bool char16Value_exists() const
    {
        const size_t n = offsetof(Self, char16Value);
        return GetField<Char16>(n).exists ? true : false;
    }
    
    void char16Value_clear()
    {
        const size_t n = offsetof(Self, char16Value);
        GetField<Char16>(n).Clear();
    }

    //
    // AllTypes_Class.instanceTest
    //
    
    const Field<Main_Class>& instanceTest() const
    {
        const size_t n = offsetof(Self, instanceTest);
        return GetField<Main_Class>(n);
    }
    
    void instanceTest(const Field<Main_Class>& x)
    {
        const size_t n = offsetof(Self, instanceTest);
        GetField<Main_Class>(n) = x;
    }
    
    const Main_Class& instanceTest_value() const
    {
        const size_t n = offsetof(Self, instanceTest);
        return GetField<Main_Class>(n).value;
    }
    
    void instanceTest_value(const Main_Class& x)
    {
        const size_t n = offsetof(Self, instanceTest);
        GetField<Main_Class>(n).Set(x);
    }
    
    bool instanceTest_exists() const
    {
        const size_t n = offsetof(Self, instanceTest);
        return GetField<Main_Class>(n).exists ? true : false;
    }
    
    void instanceTest_clear()
    {
        const size_t n = offsetof(Self, instanceTest);
        GetField<Main_Class>(n).Clear();
    }

    //
    // AllTypes_Class.boolArray
    //
    
    const Field<BooleanA>& boolArray() const
    {
        const size_t n = offsetof(Self, boolArray);
        return GetField<BooleanA>(n);
    }
    
    void boolArray(const Field<BooleanA>& x)
    {
        const size_t n = offsetof(Self, boolArray);
        GetField<BooleanA>(n) = x;
    }
    
    const BooleanA& boolArray_value() const
    {
        const size_t n = offsetof(Self, boolArray);
        return GetField<BooleanA>(n).value;
    }
    
    void boolArray_value(const BooleanA& x)
    {
        const size_t n = offsetof(Self, boolArray);
        GetField<BooleanA>(n).Set(x);
    }
    
    bool boolArray_exists() const
    {
        const size_t n = offsetof(Self, boolArray);
        return GetField<BooleanA>(n).exists ? true : false;
    }
    
    void boolArray_clear()
    {
        const size_t n = offsetof(Self, boolArray);
        GetField<BooleanA>(n).Clear();
    }

    //
    // AllTypes_Class.uint8Array
    //
    
    const Field<Uint8A>& uint8Array() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n);
    }
    
    void uint8Array(const Field<Uint8A>& x)
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n) = x;
    }
    
    const Uint8A& uint8Array_value() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n).value;
    }
    
    void uint8Array_value(const Uint8A& x)
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n).Set(x);
    }
    
    bool uint8Array_exists() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n).exists ? true : false;
    }
    
    void uint8Array_clear()
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n).Clear();
    }

    //
    // AllTypes_Class.sint8Array
    //
    
    const Field<Sint8A>& sint8Array() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n);
    }
    
    void sint8Array(const Field<Sint8A>& x)
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n) = x;
    }
    
    const Sint8A& sint8Array_value() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n).value;
    }
    
    void sint8Array_value(const Sint8A& x)
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n).Set(x);
    }
    
    bool sint8Array_exists() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n).exists ? true : false;
    }
    
    void sint8Array_clear()
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n).Clear();
    }

    //
    // AllTypes_Class.uint16Array
    //
    
    const Field<Uint16A>& uint16Array() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n);
    }
    
    void uint16Array(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& uint16Array_value() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n).value;
    }
    
    void uint16Array_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool uint16Array_exists() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void uint16Array_clear()
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n).Clear();
    }

    //
    // AllTypes_Class.sint16Array
    //
    
    const Field<Sint16A>& sint16Array() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n);
    }
    
    void sint16Array(const Field<Sint16A>& x)
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n) = x;
    }
    
    const Sint16A& sint16Array_value() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n).value;
    }
    
    void sint16Array_value(const Sint16A& x)
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n).Set(x);
    }
    
    bool sint16Array_exists() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n).exists ? true : false;
    }
    
    void sint16Array_clear()
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n).Clear();
    }

    //
    // AllTypes_Class.uint32Array
    //
    
    const Field<Uint32A>& uint32Array() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n);
    }
    
    void uint32Array(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& uint32Array_value() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n).value;
    }
    
    void uint32Array_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool uint32Array_exists() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void uint32Array_clear()
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n).Clear();
    }

    //
    // AllTypes_Class.sint32Array
    //
    
    const Field<Sint32A>& sint32Array() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n);
    }
    
    void sint32Array(const Field<Sint32A>& x)
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n) = x;
    }
    
    const Sint32A& sint32Array_value() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n).value;
    }
    
    void sint32Array_value(const Sint32A& x)
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n).Set(x);
    }
    
    bool sint32Array_exists() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n).exists ? true : false;
    }
    
    void sint32Array_clear()
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n).Clear();
    }

    //
    // AllTypes_Class.uint64Array
    //
    
    const Field<Uint64A>& uint64Array() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n);
    }
    
    void uint64Array(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& uint64Array_value() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n).value;
    }
    
    void uint64Array_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool uint64Array_exists() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void uint64Array_clear()
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n).Clear();
    }

    //
    // AllTypes_Class.sint64Array
    //
    
    const Field<Sint64A>& sint64Array() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n);
    }
    
    void sint64Array(const Field<Sint64A>& x)
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n) = x;
    }
    
    const Sint64A& sint64Array_value() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n).value;
    }
    
    void sint64Array_value(const Sint64A& x)
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n).Set(x);
    }
    
    bool sint64Array_exists() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n).exists ? true : false;
    }
    
    void sint64Array_clear()
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n).Clear();
    }

    //
    // AllTypes_Class.real32Array
    //
    
    const Field<Real32A>& real32Array() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n);
    }
    
    void real32Array(const Field<Real32A>& x)
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n) = x;
    }
    
    const Real32A& real32Array_value() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n).value;
    }
    
    void real32Array_value(const Real32A& x)
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n).Set(x);
    }
    
    bool real32Array_exists() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n).exists ? true : false;
    }
    
    void real32Array_clear()
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n).Clear();
    }

    //
    // AllTypes_Class.real64Array
    //
    
    const Field<Real64A>& real64Array() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n);
    }
    
    void real64Array(const Field<Real64A>& x)
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n) = x;
    }
    
    const Real64A& real64Array_value() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n).value;
    }
    
    void real64Array_value(const Real64A& x)
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n).Set(x);
    }
    
    bool real64Array_exists() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n).exists ? true : false;
    }
    
    void real64Array_clear()
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n).Clear();
    }

    //
    // AllTypes_Class.datetimeArray
    //
    
    const Field<DatetimeA>& datetimeArray() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n);
    }
    
    void datetimeArray(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& datetimeArray_value() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n).value;
    }
    
    void datetimeArray_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool datetimeArray_exists() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void datetimeArray_clear()
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n).Clear();
    }

    //
    // AllTypes_Class.stringArray
    //
    
    const Field<StringA>& stringArray() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n);
    }
    
    void stringArray(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n) = x;
    }
    
    const StringA& stringArray_value() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n).value;
    }
    
    void stringArray_value(const StringA& x)
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n).Set(x);
    }
    
    bool stringArray_exists() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void stringArray_clear()
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n).Clear();
    }

    //
    // AllTypes_Class.char16Array
    //
    
    const Field<Char16A>& char16Array() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n);
    }
    
    void char16Array(const Field<Char16A>& x)
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n) = x;
    }
    
    const Char16A& char16Array_value() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n).value;
    }
    
    void char16Array_value(const Char16A& x)
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n).Set(x);
    }
    
    bool char16Array_exists() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n).exists ? true : false;
    }
    
    void char16Array_clear()
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n).Clear();
    }

    //
    // AllTypes_Class.instanceArrayTest
    //
    
    const Field<Main_ClassA>& instanceArrayTest() const
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        return GetField<Main_ClassA>(n);
    }
    
    void instanceArrayTest(const Field<Main_ClassA>& x)
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        GetField<Main_ClassA>(n) = x;
    }
    
    const Main_ClassA& instanceArrayTest_value() const
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        return GetField<Main_ClassA>(n).value;
    }
    
    void instanceArrayTest_value(const Main_ClassA& x)
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        GetField<Main_ClassA>(n).Set(x);
    }
    
    bool instanceArrayTest_exists() const
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        return GetField<Main_ClassA>(n).exists ? true : false;
    }
    
    void instanceArrayTest_clear()
    {
        const size_t n = offsetof(Self, instanceArrayTest);
        GetField<Main_ClassA>(n).Clear();
    }
};

typedef Array<AllTypes_Class> AllTypes_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _AllTypes_h */
