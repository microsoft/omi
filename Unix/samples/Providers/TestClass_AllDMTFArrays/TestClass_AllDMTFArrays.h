/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestClass_AllDMTFArrays_h
#define _TestClass_AllDMTFArrays_h

#include <MI.h>
#include "TestClass_PropertyValues.h"
#include "TestClass_ForEmbedded.h"

/*
**==============================================================================
**
** TestClass_AllDMTFArrays [TestClass_AllDMTFArrays]
**
** Keys:
**    v_Key
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays /* extends TestClass_PropertyValues */
{
    MI_Instance __instance;
    /* TestClass_PropertyValues properties */
    /*KEY*/ MI_ConstUint64Field v_Key;
    /* TestClass_AllDMTFArrays properties */
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
    TestClass_ForEmbedded_ConstRef embeddedReference;
    TestClass_ForEmbedded_ConstArrayRef a_embeddedInstance;
    MI_ConstReferenceAField a_embeddedObject;
}
TestClass_AllDMTFArrays;

typedef struct _TestClass_AllDMTFArrays_Ref
{
    TestClass_AllDMTFArrays* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFArrays_Ref;

typedef struct _TestClass_AllDMTFArrays_ConstRef
{
    MI_CONST TestClass_AllDMTFArrays* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFArrays_ConstRef;

typedef struct _TestClass_AllDMTFArrays_Array
{
    struct _TestClass_AllDMTFArrays** data;
    MI_Uint32 size;
}
TestClass_AllDMTFArrays_Array;

typedef struct _TestClass_AllDMTFArrays_ConstArray
{
    struct _TestClass_AllDMTFArrays MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestClass_AllDMTFArrays_ConstArray;

typedef struct _TestClass_AllDMTFArrays_ArrayRef
{
    TestClass_AllDMTFArrays_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFArrays_ArrayRef;

typedef struct _TestClass_AllDMTFArrays_ConstArrayRef
{
    TestClass_AllDMTFArrays_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFArrays_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestClass_AllDMTFArrays_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Construct(
    TestClass_AllDMTFArrays* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &TestClass_AllDMTFArrays_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clone(
    const TestClass_AllDMTFArrays* self,
    TestClass_AllDMTFArrays** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestClass_AllDMTFArrays_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestClass_AllDMTFArrays_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Destruct(TestClass_AllDMTFArrays* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Delete(TestClass_AllDMTFArrays* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Post(
    const TestClass_AllDMTFArrays* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_v_Key(
    TestClass_AllDMTFArrays* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_Key)->value = x;
    ((MI_Uint64Field*)&self->v_Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_v_Key(
    TestClass_AllDMTFArrays* self)
{
    memset((void*)&self->v_Key, 0, sizeof(self->v_Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_bool(
    TestClass_AllDMTFArrays* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_bool(
    TestClass_AllDMTFArrays* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_bool(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_uint8(
    TestClass_AllDMTFArrays* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_uint8(
    TestClass_AllDMTFArrays* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_uint8(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_sint8(
    TestClass_AllDMTFArrays* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_sint8(
    TestClass_AllDMTFArrays* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_sint8(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_UINT16(
    TestClass_AllDMTFArrays* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_UINT16(
    TestClass_AllDMTFArrays* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_UINT16(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_sint16(
    TestClass_AllDMTFArrays* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_sint16(
    TestClass_AllDMTFArrays* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_sint16(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_uint32(
    TestClass_AllDMTFArrays* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_uint32(
    TestClass_AllDMTFArrays* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_uint32(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_sint32(
    TestClass_AllDMTFArrays* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_sint32(
    TestClass_AllDMTFArrays* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_sint32(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_uint64(
    TestClass_AllDMTFArrays* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_uint64(
    TestClass_AllDMTFArrays* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_uint64(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_sint64(
    TestClass_AllDMTFArrays* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_sint64(
    TestClass_AllDMTFArrays* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_sint64(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_rEal32(
    TestClass_AllDMTFArrays* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_rEal32(
    TestClass_AllDMTFArrays* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_rEal32(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_REAL64(
    TestClass_AllDMTFArrays* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_REAL64(
    TestClass_AllDMTFArrays* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_REAL64(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_char16(
    TestClass_AllDMTFArrays* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_char16(
    TestClass_AllDMTFArrays* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_char16(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_string(
    TestClass_AllDMTFArrays* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_string(
    TestClass_AllDMTFArrays* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_string(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_DATETIME(
    TestClass_AllDMTFArrays* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_DATETIME(
    TestClass_AllDMTFArrays* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_DATETIME(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_embeddedReference(
    TestClass_AllDMTFArrays* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_embeddedReference(
    TestClass_AllDMTFArrays* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_embeddedReference(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_embeddedInstance(
    TestClass_AllDMTFArrays* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_embeddedInstance(
    TestClass_AllDMTFArrays* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_embeddedInstance(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Set_a_embeddedObject(
    TestClass_AllDMTFArrays* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetPtr_a_embeddedObject(
    TestClass_AllDMTFArrays* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_Clear_a_embeddedObject(
    TestClass_AllDMTFArrays* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetBooleanArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetBooleanArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstBooleanAField booleanArray;
}
TestClass_AllDMTFArrays_GetBooleanArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetBooleanArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Construct(
    TestClass_AllDMTFArrays_GetBooleanArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetBooleanArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Clone(
    const TestClass_AllDMTFArrays_GetBooleanArray* self,
    TestClass_AllDMTFArrays_GetBooleanArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Destruct(
    TestClass_AllDMTFArrays_GetBooleanArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Delete(
    TestClass_AllDMTFArrays_GetBooleanArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Post(
    const TestClass_AllDMTFArrays_GetBooleanArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetBooleanArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetBooleanArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Set_booleanArray(
    TestClass_AllDMTFArrays_GetBooleanArray* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_SetPtr_booleanArray(
    TestClass_AllDMTFArrays_GetBooleanArray* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetBooleanArray_Clear_booleanArray(
    TestClass_AllDMTFArrays_GetBooleanArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetBooleanArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetBooleanArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanAField booleanArray;
}
TestClass_AllDMTFArrays_SetBooleanArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetBooleanArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Construct(
    TestClass_AllDMTFArrays_SetBooleanArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetBooleanArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Clone(
    const TestClass_AllDMTFArrays_SetBooleanArray* self,
    TestClass_AllDMTFArrays_SetBooleanArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Destruct(
    TestClass_AllDMTFArrays_SetBooleanArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Delete(
    TestClass_AllDMTFArrays_SetBooleanArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Post(
    const TestClass_AllDMTFArrays_SetBooleanArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetBooleanArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetBooleanArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Set_booleanArray(
    TestClass_AllDMTFArrays_SetBooleanArray* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_SetPtr_booleanArray(
    TestClass_AllDMTFArrays_SetBooleanArray* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetBooleanArray_Clear_booleanArray(
    TestClass_AllDMTFArrays_SetBooleanArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetUint8Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetUint8Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint8AField uint8Array;
}
TestClass_AllDMTFArrays_GetUint8Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint8Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Construct(
    TestClass_AllDMTFArrays_GetUint8Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetUint8Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Clone(
    const TestClass_AllDMTFArrays_GetUint8Array* self,
    TestClass_AllDMTFArrays_GetUint8Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Destruct(
    TestClass_AllDMTFArrays_GetUint8Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Delete(
    TestClass_AllDMTFArrays_GetUint8Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Post(
    const TestClass_AllDMTFArrays_GetUint8Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetUint8Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetUint8Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Set_uint8Array(
    TestClass_AllDMTFArrays_GetUint8Array* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_SetPtr_uint8Array(
    TestClass_AllDMTFArrays_GetUint8Array* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint8Array_Clear_uint8Array(
    TestClass_AllDMTFArrays_GetUint8Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetUint8Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetUint8Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField uint8Array;
}
TestClass_AllDMTFArrays_SetUint8Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint8Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Construct(
    TestClass_AllDMTFArrays_SetUint8Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetUint8Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Clone(
    const TestClass_AllDMTFArrays_SetUint8Array* self,
    TestClass_AllDMTFArrays_SetUint8Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Destruct(
    TestClass_AllDMTFArrays_SetUint8Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Delete(
    TestClass_AllDMTFArrays_SetUint8Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Post(
    const TestClass_AllDMTFArrays_SetUint8Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetUint8Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetUint8Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Set_uint8Array(
    TestClass_AllDMTFArrays_SetUint8Array* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_SetPtr_uint8Array(
    TestClass_AllDMTFArrays_SetUint8Array* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint8Array_Clear_uint8Array(
    TestClass_AllDMTFArrays_SetUint8Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetSint8Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetSint8Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint8AField sint8Array;
}
TestClass_AllDMTFArrays_GetSint8Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint8Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Construct(
    TestClass_AllDMTFArrays_GetSint8Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetSint8Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Clone(
    const TestClass_AllDMTFArrays_GetSint8Array* self,
    TestClass_AllDMTFArrays_GetSint8Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Destruct(
    TestClass_AllDMTFArrays_GetSint8Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Delete(
    TestClass_AllDMTFArrays_GetSint8Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Post(
    const TestClass_AllDMTFArrays_GetSint8Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetSint8Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetSint8Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Set_sint8Array(
    TestClass_AllDMTFArrays_GetSint8Array* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_SetPtr_sint8Array(
    TestClass_AllDMTFArrays_GetSint8Array* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint8Array_Clear_sint8Array(
    TestClass_AllDMTFArrays_GetSint8Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetSint8Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetSint8Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint8AField sint8Array;
}
TestClass_AllDMTFArrays_SetSint8Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint8Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Construct(
    TestClass_AllDMTFArrays_SetSint8Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetSint8Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Clone(
    const TestClass_AllDMTFArrays_SetSint8Array* self,
    TestClass_AllDMTFArrays_SetSint8Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Destruct(
    TestClass_AllDMTFArrays_SetSint8Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Delete(
    TestClass_AllDMTFArrays_SetSint8Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Post(
    const TestClass_AllDMTFArrays_SetSint8Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetSint8Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetSint8Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Set_sint8Array(
    TestClass_AllDMTFArrays_SetSint8Array* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_SetPtr_sint8Array(
    TestClass_AllDMTFArrays_SetSint8Array* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint8Array_Clear_sint8Array(
    TestClass_AllDMTFArrays_SetSint8Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetUint16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetUint16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint16AField uint16Array;
}
TestClass_AllDMTFArrays_GetUint16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Construct(
    TestClass_AllDMTFArrays_GetUint16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetUint16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Clone(
    const TestClass_AllDMTFArrays_GetUint16Array* self,
    TestClass_AllDMTFArrays_GetUint16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Destruct(
    TestClass_AllDMTFArrays_GetUint16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Delete(
    TestClass_AllDMTFArrays_GetUint16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Post(
    const TestClass_AllDMTFArrays_GetUint16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetUint16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetUint16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Set_uint16Array(
    TestClass_AllDMTFArrays_GetUint16Array* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_SetPtr_uint16Array(
    TestClass_AllDMTFArrays_GetUint16Array* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint16Array_Clear_uint16Array(
    TestClass_AllDMTFArrays_GetUint16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetUint16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetUint16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16AField uint16Array;
}
TestClass_AllDMTFArrays_SetUint16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Construct(
    TestClass_AllDMTFArrays_SetUint16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetUint16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Clone(
    const TestClass_AllDMTFArrays_SetUint16Array* self,
    TestClass_AllDMTFArrays_SetUint16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Destruct(
    TestClass_AllDMTFArrays_SetUint16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Delete(
    TestClass_AllDMTFArrays_SetUint16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Post(
    const TestClass_AllDMTFArrays_SetUint16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetUint16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetUint16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Set_uint16Array(
    TestClass_AllDMTFArrays_SetUint16Array* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_SetPtr_uint16Array(
    TestClass_AllDMTFArrays_SetUint16Array* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint16Array_Clear_uint16Array(
    TestClass_AllDMTFArrays_SetUint16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetSint16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetSint16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint16AField sint16Array;
}
TestClass_AllDMTFArrays_GetSint16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Construct(
    TestClass_AllDMTFArrays_GetSint16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetSint16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Clone(
    const TestClass_AllDMTFArrays_GetSint16Array* self,
    TestClass_AllDMTFArrays_GetSint16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Destruct(
    TestClass_AllDMTFArrays_GetSint16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Delete(
    TestClass_AllDMTFArrays_GetSint16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Post(
    const TestClass_AllDMTFArrays_GetSint16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetSint16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetSint16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Set_sint16Array(
    TestClass_AllDMTFArrays_GetSint16Array* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_SetPtr_sint16Array(
    TestClass_AllDMTFArrays_GetSint16Array* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint16Array_Clear_sint16Array(
    TestClass_AllDMTFArrays_GetSint16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetSint16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetSint16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint16AField sint16Array;
}
TestClass_AllDMTFArrays_SetSint16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Construct(
    TestClass_AllDMTFArrays_SetSint16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetSint16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Clone(
    const TestClass_AllDMTFArrays_SetSint16Array* self,
    TestClass_AllDMTFArrays_SetSint16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Destruct(
    TestClass_AllDMTFArrays_SetSint16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Delete(
    TestClass_AllDMTFArrays_SetSint16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Post(
    const TestClass_AllDMTFArrays_SetSint16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetSint16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetSint16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Set_sint16Array(
    TestClass_AllDMTFArrays_SetSint16Array* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_SetPtr_sint16Array(
    TestClass_AllDMTFArrays_SetSint16Array* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint16Array_Clear_sint16Array(
    TestClass_AllDMTFArrays_SetSint16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetUint32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetUint32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint32AField uint32Array;
}
TestClass_AllDMTFArrays_GetUint32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Construct(
    TestClass_AllDMTFArrays_GetUint32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetUint32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Clone(
    const TestClass_AllDMTFArrays_GetUint32Array* self,
    TestClass_AllDMTFArrays_GetUint32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Destruct(
    TestClass_AllDMTFArrays_GetUint32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Delete(
    TestClass_AllDMTFArrays_GetUint32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Post(
    const TestClass_AllDMTFArrays_GetUint32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetUint32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetUint32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Set_uint32Array(
    TestClass_AllDMTFArrays_GetUint32Array* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_SetPtr_uint32Array(
    TestClass_AllDMTFArrays_GetUint32Array* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint32Array_Clear_uint32Array(
    TestClass_AllDMTFArrays_GetUint32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetUint32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetUint32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32AField uint32Array;
}
TestClass_AllDMTFArrays_SetUint32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Construct(
    TestClass_AllDMTFArrays_SetUint32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetUint32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Clone(
    const TestClass_AllDMTFArrays_SetUint32Array* self,
    TestClass_AllDMTFArrays_SetUint32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Destruct(
    TestClass_AllDMTFArrays_SetUint32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Delete(
    TestClass_AllDMTFArrays_SetUint32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Post(
    const TestClass_AllDMTFArrays_SetUint32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetUint32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetUint32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Set_uint32Array(
    TestClass_AllDMTFArrays_SetUint32Array* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_SetPtr_uint32Array(
    TestClass_AllDMTFArrays_SetUint32Array* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint32Array_Clear_uint32Array(
    TestClass_AllDMTFArrays_SetUint32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetSint32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetSint32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint32AField sint32Array;
}
TestClass_AllDMTFArrays_GetSint32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Construct(
    TestClass_AllDMTFArrays_GetSint32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetSint32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Clone(
    const TestClass_AllDMTFArrays_GetSint32Array* self,
    TestClass_AllDMTFArrays_GetSint32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Destruct(
    TestClass_AllDMTFArrays_GetSint32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Delete(
    TestClass_AllDMTFArrays_GetSint32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Post(
    const TestClass_AllDMTFArrays_GetSint32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetSint32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetSint32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Set_sint32Array(
    TestClass_AllDMTFArrays_GetSint32Array* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_SetPtr_sint32Array(
    TestClass_AllDMTFArrays_GetSint32Array* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint32Array_Clear_sint32Array(
    TestClass_AllDMTFArrays_GetSint32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetSint32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetSint32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint32AField sint32Array;
}
TestClass_AllDMTFArrays_SetSint32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Construct(
    TestClass_AllDMTFArrays_SetSint32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetSint32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Clone(
    const TestClass_AllDMTFArrays_SetSint32Array* self,
    TestClass_AllDMTFArrays_SetSint32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Destruct(
    TestClass_AllDMTFArrays_SetSint32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Delete(
    TestClass_AllDMTFArrays_SetSint32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Post(
    const TestClass_AllDMTFArrays_SetSint32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetSint32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetSint32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Set_sint32Array(
    TestClass_AllDMTFArrays_SetSint32Array* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_SetPtr_sint32Array(
    TestClass_AllDMTFArrays_SetSint32Array* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint32Array_Clear_sint32Array(
    TestClass_AllDMTFArrays_SetSint32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetUint64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetUint64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint64AField uint64Array;
}
TestClass_AllDMTFArrays_GetUint64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Construct(
    TestClass_AllDMTFArrays_GetUint64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetUint64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Clone(
    const TestClass_AllDMTFArrays_GetUint64Array* self,
    TestClass_AllDMTFArrays_GetUint64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Destruct(
    TestClass_AllDMTFArrays_GetUint64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Delete(
    TestClass_AllDMTFArrays_GetUint64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Post(
    const TestClass_AllDMTFArrays_GetUint64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetUint64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetUint64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Set_uint64Array(
    TestClass_AllDMTFArrays_GetUint64Array* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_SetPtr_uint64Array(
    TestClass_AllDMTFArrays_GetUint64Array* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetUint64Array_Clear_uint64Array(
    TestClass_AllDMTFArrays_GetUint64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetUint64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetUint64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64AField uint64Array;
}
TestClass_AllDMTFArrays_SetUint64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Construct(
    TestClass_AllDMTFArrays_SetUint64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetUint64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Clone(
    const TestClass_AllDMTFArrays_SetUint64Array* self,
    TestClass_AllDMTFArrays_SetUint64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Destruct(
    TestClass_AllDMTFArrays_SetUint64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Delete(
    TestClass_AllDMTFArrays_SetUint64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Post(
    const TestClass_AllDMTFArrays_SetUint64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetUint64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetUint64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Set_uint64Array(
    TestClass_AllDMTFArrays_SetUint64Array* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_SetPtr_uint64Array(
    TestClass_AllDMTFArrays_SetUint64Array* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetUint64Array_Clear_uint64Array(
    TestClass_AllDMTFArrays_SetUint64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetSint64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetSint64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint64AField sint64Array;
}
TestClass_AllDMTFArrays_GetSint64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Construct(
    TestClass_AllDMTFArrays_GetSint64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetSint64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Clone(
    const TestClass_AllDMTFArrays_GetSint64Array* self,
    TestClass_AllDMTFArrays_GetSint64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Destruct(
    TestClass_AllDMTFArrays_GetSint64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Delete(
    TestClass_AllDMTFArrays_GetSint64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Post(
    const TestClass_AllDMTFArrays_GetSint64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetSint64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetSint64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Set_sint64Array(
    TestClass_AllDMTFArrays_GetSint64Array* self,
    const MI_Sint64* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_SetPtr_sint64Array(
    TestClass_AllDMTFArrays_GetSint64Array* self,
    const MI_Sint64* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetSint64Array_Clear_sint64Array(
    TestClass_AllDMTFArrays_GetSint64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetSint64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetSint64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint64AField sint64Array;
}
TestClass_AllDMTFArrays_SetSint64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Construct(
    TestClass_AllDMTFArrays_SetSint64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetSint64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Clone(
    const TestClass_AllDMTFArrays_SetSint64Array* self,
    TestClass_AllDMTFArrays_SetSint64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Destruct(
    TestClass_AllDMTFArrays_SetSint64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Delete(
    TestClass_AllDMTFArrays_SetSint64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Post(
    const TestClass_AllDMTFArrays_SetSint64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetSint64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetSint64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Set_sint64Array(
    TestClass_AllDMTFArrays_SetSint64Array* self,
    const MI_Sint64* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_SetPtr_sint64Array(
    TestClass_AllDMTFArrays_SetSint64Array* self,
    const MI_Sint64* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetSint64Array_Clear_sint64Array(
    TestClass_AllDMTFArrays_SetSint64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetReal32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetReal32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstReal32AField real32Array;
}
TestClass_AllDMTFArrays_GetReal32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReal32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Construct(
    TestClass_AllDMTFArrays_GetReal32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetReal32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Clone(
    const TestClass_AllDMTFArrays_GetReal32Array* self,
    TestClass_AllDMTFArrays_GetReal32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Destruct(
    TestClass_AllDMTFArrays_GetReal32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Delete(
    TestClass_AllDMTFArrays_GetReal32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Post(
    const TestClass_AllDMTFArrays_GetReal32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetReal32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetReal32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Set_real32Array(
    TestClass_AllDMTFArrays_GetReal32Array* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_SetPtr_real32Array(
    TestClass_AllDMTFArrays_GetReal32Array* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal32Array_Clear_real32Array(
    TestClass_AllDMTFArrays_GetReal32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetReal32Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetReal32Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReal32AField real32Array;
}
TestClass_AllDMTFArrays_SetReal32Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReal32Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Construct(
    TestClass_AllDMTFArrays_SetReal32Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetReal32Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Clone(
    const TestClass_AllDMTFArrays_SetReal32Array* self,
    TestClass_AllDMTFArrays_SetReal32Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Destruct(
    TestClass_AllDMTFArrays_SetReal32Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Delete(
    TestClass_AllDMTFArrays_SetReal32Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Post(
    const TestClass_AllDMTFArrays_SetReal32Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetReal32Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetReal32Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Set_real32Array(
    TestClass_AllDMTFArrays_SetReal32Array* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_SetPtr_real32Array(
    TestClass_AllDMTFArrays_SetReal32Array* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal32Array_Clear_real32Array(
    TestClass_AllDMTFArrays_SetReal32Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetReal64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetReal64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstReal64AField real64Array;
}
TestClass_AllDMTFArrays_GetReal64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReal64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Construct(
    TestClass_AllDMTFArrays_GetReal64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetReal64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Clone(
    const TestClass_AllDMTFArrays_GetReal64Array* self,
    TestClass_AllDMTFArrays_GetReal64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Destruct(
    TestClass_AllDMTFArrays_GetReal64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Delete(
    TestClass_AllDMTFArrays_GetReal64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Post(
    const TestClass_AllDMTFArrays_GetReal64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetReal64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetReal64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Set_real64Array(
    TestClass_AllDMTFArrays_GetReal64Array* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_SetPtr_real64Array(
    TestClass_AllDMTFArrays_GetReal64Array* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReal64Array_Clear_real64Array(
    TestClass_AllDMTFArrays_GetReal64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetReal64Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetReal64Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReal64AField real64Array;
}
TestClass_AllDMTFArrays_SetReal64Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReal64Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Construct(
    TestClass_AllDMTFArrays_SetReal64Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetReal64Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Clone(
    const TestClass_AllDMTFArrays_SetReal64Array* self,
    TestClass_AllDMTFArrays_SetReal64Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Destruct(
    TestClass_AllDMTFArrays_SetReal64Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Delete(
    TestClass_AllDMTFArrays_SetReal64Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Post(
    const TestClass_AllDMTFArrays_SetReal64Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetReal64Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetReal64Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Set_real64Array(
    TestClass_AllDMTFArrays_SetReal64Array* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_SetPtr_real64Array(
    TestClass_AllDMTFArrays_SetReal64Array* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReal64Array_Clear_real64Array(
    TestClass_AllDMTFArrays_SetReal64Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetChar16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetChar16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstChar16AField charArray;
}
TestClass_AllDMTFArrays_GetChar16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetChar16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Construct(
    TestClass_AllDMTFArrays_GetChar16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetChar16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Clone(
    const TestClass_AllDMTFArrays_GetChar16Array* self,
    TestClass_AllDMTFArrays_GetChar16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Destruct(
    TestClass_AllDMTFArrays_GetChar16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Delete(
    TestClass_AllDMTFArrays_GetChar16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Post(
    const TestClass_AllDMTFArrays_GetChar16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_GetChar16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetChar16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Set_charArray(
    TestClass_AllDMTFArrays_GetChar16Array* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_SetPtr_charArray(
    TestClass_AllDMTFArrays_GetChar16Array* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetChar16Array_Clear_charArray(
    TestClass_AllDMTFArrays_GetChar16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetChar16Array()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetChar16Array
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstChar16AField charArray;
}
TestClass_AllDMTFArrays_SetChar16Array;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetChar16Array_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Construct(
    TestClass_AllDMTFArrays_SetChar16Array* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetChar16Array_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Clone(
    const TestClass_AllDMTFArrays_SetChar16Array* self,
    TestClass_AllDMTFArrays_SetChar16Array** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Destruct(
    TestClass_AllDMTFArrays_SetChar16Array* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Delete(
    TestClass_AllDMTFArrays_SetChar16Array* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Post(
    const TestClass_AllDMTFArrays_SetChar16Array* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Set_MIReturn(
    TestClass_AllDMTFArrays_SetChar16Array* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetChar16Array* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Set_charArray(
    TestClass_AllDMTFArrays_SetChar16Array* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_SetPtr_charArray(
    TestClass_AllDMTFArrays_SetChar16Array* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetChar16Array_Clear_charArray(
    TestClass_AllDMTFArrays_SetChar16Array* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetStringArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetStringArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstStringAField StringArray;
}
TestClass_AllDMTFArrays_GetStringArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetStringArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Construct(
    TestClass_AllDMTFArrays_GetStringArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetStringArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Clone(
    const TestClass_AllDMTFArrays_GetStringArray* self,
    TestClass_AllDMTFArrays_GetStringArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Destruct(
    TestClass_AllDMTFArrays_GetStringArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Delete(
    TestClass_AllDMTFArrays_GetStringArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Post(
    const TestClass_AllDMTFArrays_GetStringArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetStringArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetStringArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Set_StringArray(
    TestClass_AllDMTFArrays_GetStringArray* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_SetPtr_StringArray(
    TestClass_AllDMTFArrays_GetStringArray* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetStringArray_Clear_StringArray(
    TestClass_AllDMTFArrays_GetStringArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetStringArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetStringArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringAField StringArray;
}
TestClass_AllDMTFArrays_SetStringArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetStringArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Construct(
    TestClass_AllDMTFArrays_SetStringArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetStringArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Clone(
    const TestClass_AllDMTFArrays_SetStringArray* self,
    TestClass_AllDMTFArrays_SetStringArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Destruct(
    TestClass_AllDMTFArrays_SetStringArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Delete(
    TestClass_AllDMTFArrays_SetStringArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Post(
    const TestClass_AllDMTFArrays_SetStringArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetStringArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetStringArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Set_StringArray(
    TestClass_AllDMTFArrays_SetStringArray* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_SetPtr_StringArray(
    TestClass_AllDMTFArrays_SetStringArray* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetStringArray_Clear_StringArray(
    TestClass_AllDMTFArrays_SetStringArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetDateTimeArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetDateTimeArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstDatetimeAField datetimeArray;
}
TestClass_AllDMTFArrays_GetDateTimeArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetDateTimeArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Construct(
    TestClass_AllDMTFArrays_GetDateTimeArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetDateTimeArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Clone(
    const TestClass_AllDMTFArrays_GetDateTimeArray* self,
    TestClass_AllDMTFArrays_GetDateTimeArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Destruct(
    TestClass_AllDMTFArrays_GetDateTimeArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Delete(
    TestClass_AllDMTFArrays_GetDateTimeArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Post(
    const TestClass_AllDMTFArrays_GetDateTimeArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetDateTimeArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetDateTimeArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Set_datetimeArray(
    TestClass_AllDMTFArrays_GetDateTimeArray* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_SetPtr_datetimeArray(
    TestClass_AllDMTFArrays_GetDateTimeArray* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetDateTimeArray_Clear_datetimeArray(
    TestClass_AllDMTFArrays_GetDateTimeArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetdatetimeArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetdatetimeArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstDatetimeAField datetimeArray;
}
TestClass_AllDMTFArrays_SetdatetimeArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetdatetimeArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Construct(
    TestClass_AllDMTFArrays_SetdatetimeArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetdatetimeArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Clone(
    const TestClass_AllDMTFArrays_SetdatetimeArray* self,
    TestClass_AllDMTFArrays_SetdatetimeArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Destruct(
    TestClass_AllDMTFArrays_SetdatetimeArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Delete(
    TestClass_AllDMTFArrays_SetdatetimeArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Post(
    const TestClass_AllDMTFArrays_SetdatetimeArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetdatetimeArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetdatetimeArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Set_datetimeArray(
    TestClass_AllDMTFArrays_SetdatetimeArray* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_SetPtr_datetimeArray(
    TestClass_AllDMTFArrays_SetdatetimeArray* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetdatetimeArray_Clear_datetimeArray(
    TestClass_AllDMTFArrays_SetdatetimeArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetReferenceArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetReferenceArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ TestClass_ForEmbedded_ConstArrayRef embeddedRefArray;
}
TestClass_AllDMTFArrays_GetReferenceArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReferenceArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Construct(
    TestClass_AllDMTFArrays_GetReferenceArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetReferenceArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Clone(
    const TestClass_AllDMTFArrays_GetReferenceArray* self,
    TestClass_AllDMTFArrays_GetReferenceArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Destruct(
    TestClass_AllDMTFArrays_GetReferenceArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Delete(
    TestClass_AllDMTFArrays_GetReferenceArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Post(
    const TestClass_AllDMTFArrays_GetReferenceArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetReferenceArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetReferenceArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Set_embeddedRefArray(
    TestClass_AllDMTFArrays_GetReferenceArray* self,
    const TestClass_ForEmbedded* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_SetPtr_embeddedRefArray(
    TestClass_AllDMTFArrays_GetReferenceArray* self,
    const TestClass_ForEmbedded* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetReferenceArray_Clear_embeddedRefArray(
    TestClass_AllDMTFArrays_GetReferenceArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetReferenceArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetReferenceArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ TestClass_ForEmbedded_ConstArrayRef embeddedRefArray;
}
TestClass_AllDMTFArrays_SetReferenceArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReferenceArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Construct(
    TestClass_AllDMTFArrays_SetReferenceArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetReferenceArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Clone(
    const TestClass_AllDMTFArrays_SetReferenceArray* self,
    TestClass_AllDMTFArrays_SetReferenceArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Destruct(
    TestClass_AllDMTFArrays_SetReferenceArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Delete(
    TestClass_AllDMTFArrays_SetReferenceArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Post(
    const TestClass_AllDMTFArrays_SetReferenceArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetReferenceArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetReferenceArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Set_embeddedRefArray(
    TestClass_AllDMTFArrays_SetReferenceArray* self,
    const TestClass_ForEmbedded* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_SetPtr_embeddedRefArray(
    TestClass_AllDMTFArrays_SetReferenceArray* self,
    const TestClass_ForEmbedded* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetReferenceArray_Clear_embeddedRefArray(
    TestClass_AllDMTFArrays_SetReferenceArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetEmbeddedInstanceArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetEmbeddedInstanceArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ TestClass_ForEmbedded_ConstArrayRef embeddedInstanceArray;
}
TestClass_AllDMTFArrays_GetEmbeddedInstanceArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Construct(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Clone(
    const TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Destruct(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Delete(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Post(
    const TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Set_embeddedInstanceArray(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_SetPtr_embeddedInstanceArray(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Clear_embeddedInstanceArray(
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetEmbeddedInstanceArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetEmbeddedInstanceArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ TestClass_ForEmbedded_ConstArrayRef embeddedInstanceArray;
}
TestClass_AllDMTFArrays_SetEmbeddedInstanceArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Construct(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Clone(
    const TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Destruct(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Delete(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Post(
    const TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Set_embeddedInstanceArray(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_SetPtr_embeddedInstanceArray(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self,
    const TestClass_ForEmbedded * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Clear_embeddedInstanceArray(
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.GetEmbeddedObjectArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_GetEmbeddedObjectArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstReferenceAField embeddedObjectArray;
}
TestClass_AllDMTFArrays_GetEmbeddedObjectArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetEmbeddedObjectArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Construct(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_GetEmbeddedObjectArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Clone(
    const TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Destruct(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Delete(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Post(
    const TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Set_MIReturn(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Set_embeddedObjectArray(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_SetPtr_embeddedObjectArray(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Clear_embeddedObjectArray(
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays.SetEmbeddedObjectArray()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFArrays_SetEmbeddedObjectArray
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReferenceAField embeddedObjectArray;
}
TestClass_AllDMTFArrays_SetEmbeddedObjectArray;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetEmbeddedObjectArray_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Construct(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFArrays_SetEmbeddedObjectArray_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Clone(
    const TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Destruct(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Delete(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Post(
    const TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Set_MIReturn(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Clear_MIReturn(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Set_embeddedObjectArray(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_SetPtr_embeddedObjectArray(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Clear_embeddedObjectArray(
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFArrays provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestClass_AllDMTFArrays_Self
{
    MI_Uint32 loadInstances;
} TestClass_AllDMTFArrays_Self;

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Load(
    TestClass_AllDMTFArrays_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Unload(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_EnumerateInstances(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_GetInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_CreateInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* newInstance);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_ModifyInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_DeleteInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* instanceName);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetBooleanArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetBooleanArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetBooleanArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetBooleanArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint8Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint8Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint8Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint8Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReal32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReal32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReal32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReal32Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReal64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReal64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReal64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReal64Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetChar16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetChar16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetChar16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetChar16Array* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetStringArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetStringArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetStringArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetStringArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetDateTimeArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetDateTimeArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetdatetimeArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetdatetimeArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReferenceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReferenceArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReferenceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReferenceArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetEmbeddedInstanceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetEmbeddedInstanceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_GetEmbeddedObjectArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetEmbeddedObjectArray* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFArrays_Invoke_SetEmbeddedObjectArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetEmbeddedObjectArray* in);


#endif /* _TestClass_AllDMTFArrays_h */
