/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestClass_AllDMTFTypes_h
#define _TestClass_AllDMTFTypes_h

#include <MI.h>
#include "TestClass_PropertyValues.h"
#include "TestClass_ForEmbedded.h"

/*
**==============================================================================
**
** TestClass_AllDMTFTypes [TestClass_AllDMTFTypes]
**
** Keys:
**    v_Key
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes /* extends TestClass_PropertyValues */
{
    MI_Instance __instance;
    /* TestClass_PropertyValues properties */
    /*KEY*/ MI_ConstUint64Field v_Key;
    /* TestClass_AllDMTFTypes properties */
    MI_ConstBooleanField v_bool;
    MI_ConstUint8Field v_uint8;
    MI_ConstSint8Field v_sint8;
    MI_ConstUint16Field v_UINT16;
    MI_ConstSint16Field v_sint16;
    MI_ConstUint32Field v_uint32;
    MI_ConstSint32Field v_sint32;
    MI_ConstUint64Field v_uint64;
    MI_ConstSint64Field v_sint64;
    MI_ConstReal32Field v_rEal32;
    MI_ConstReal64Field v_Real64;
    MI_ConstChar16Field v_char16;
    MI_ConstStringField v_string;
    MI_ConstDatetimeField v_DATETIME;
    MI_ConstReferenceField v_embeddedObject;
    TestClass_ForEmbedded_ConstRef v_embeddedInstance;
    TestClass_ForEmbedded_ConstRef v_reference;
    MI_ConstUint8AField v_octetUint8;
}
TestClass_AllDMTFTypes;

typedef struct _TestClass_AllDMTFTypes_Ref
{
    TestClass_AllDMTFTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFTypes_Ref;

typedef struct _TestClass_AllDMTFTypes_ConstRef
{
    MI_CONST TestClass_AllDMTFTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFTypes_ConstRef;

typedef struct _TestClass_AllDMTFTypes_Array
{
    struct _TestClass_AllDMTFTypes** data;
    MI_Uint32 size;
}
TestClass_AllDMTFTypes_Array;

typedef struct _TestClass_AllDMTFTypes_ConstArray
{
    struct _TestClass_AllDMTFTypes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestClass_AllDMTFTypes_ConstArray;

typedef struct _TestClass_AllDMTFTypes_ArrayRef
{
    TestClass_AllDMTFTypes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFTypes_ArrayRef;

typedef struct _TestClass_AllDMTFTypes_ConstArrayRef
{
    TestClass_AllDMTFTypes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_AllDMTFTypes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestClass_AllDMTFTypes_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Construct(
    TestClass_AllDMTFTypes* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &TestClass_AllDMTFTypes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clone(
    const TestClass_AllDMTFTypes* self,
    TestClass_AllDMTFTypes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestClass_AllDMTFTypes_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestClass_AllDMTFTypes_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Destruct(TestClass_AllDMTFTypes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Delete(TestClass_AllDMTFTypes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Post(
    const TestClass_AllDMTFTypes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_Key(
    TestClass_AllDMTFTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_Key)->value = x;
    ((MI_Uint64Field*)&self->v_Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_Key(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_Key, 0, sizeof(self->v_Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_bool(
    TestClass_AllDMTFTypes* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->v_bool)->value = x;
    ((MI_BooleanField*)&self->v_bool)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_bool(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_bool, 0, sizeof(self->v_bool));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_uint8(
    TestClass_AllDMTFTypes* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->v_uint8)->value = x;
    ((MI_Uint8Field*)&self->v_uint8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_uint8(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_uint8, 0, sizeof(self->v_uint8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_sint8(
    TestClass_AllDMTFTypes* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->v_sint8)->value = x;
    ((MI_Sint8Field*)&self->v_sint8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_sint8(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_sint8, 0, sizeof(self->v_sint8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_UINT16(
    TestClass_AllDMTFTypes* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->v_UINT16)->value = x;
    ((MI_Uint16Field*)&self->v_UINT16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_UINT16(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_UINT16, 0, sizeof(self->v_UINT16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_sint16(
    TestClass_AllDMTFTypes* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->v_sint16)->value = x;
    ((MI_Sint16Field*)&self->v_sint16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_sint16(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_sint16, 0, sizeof(self->v_sint16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_uint32(
    TestClass_AllDMTFTypes* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->v_uint32)->value = x;
    ((MI_Uint32Field*)&self->v_uint32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_uint32(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_uint32, 0, sizeof(self->v_uint32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_sint32(
    TestClass_AllDMTFTypes* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->v_sint32)->value = x;
    ((MI_Sint32Field*)&self->v_sint32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_sint32(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_sint32, 0, sizeof(self->v_sint32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_uint64(
    TestClass_AllDMTFTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->v_uint64)->value = x;
    ((MI_Uint64Field*)&self->v_uint64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_uint64(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_uint64, 0, sizeof(self->v_uint64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_sint64(
    TestClass_AllDMTFTypes* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->v_sint64)->value = x;
    ((MI_Sint64Field*)&self->v_sint64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_sint64(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_sint64, 0, sizeof(self->v_sint64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_rEal32(
    TestClass_AllDMTFTypes* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->v_rEal32)->value = x;
    ((MI_Real32Field*)&self->v_rEal32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_rEal32(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_rEal32, 0, sizeof(self->v_rEal32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_Real64(
    TestClass_AllDMTFTypes* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->v_Real64)->value = x;
    ((MI_Real64Field*)&self->v_Real64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_Real64(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_Real64, 0, sizeof(self->v_Real64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_char16(
    TestClass_AllDMTFTypes* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->v_char16)->value = x;
    ((MI_Char16Field*)&self->v_char16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_char16(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_char16, 0, sizeof(self->v_char16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_string(
    TestClass_AllDMTFTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetPtr_v_string(
    TestClass_AllDMTFTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_string(
    TestClass_AllDMTFTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_DATETIME(
    TestClass_AllDMTFTypes* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->v_DATETIME)->value = x;
    ((MI_DatetimeField*)&self->v_DATETIME)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_DATETIME(
    TestClass_AllDMTFTypes* self)
{
    memset((void*)&self->v_DATETIME, 0, sizeof(self->v_DATETIME));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_embeddedObject(
    TestClass_AllDMTFTypes* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetPtr_v_embeddedObject(
    TestClass_AllDMTFTypes* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_embeddedObject(
    TestClass_AllDMTFTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_embeddedInstance(
    TestClass_AllDMTFTypes* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetPtr_v_embeddedInstance(
    TestClass_AllDMTFTypes* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_embeddedInstance(
    TestClass_AllDMTFTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_reference(
    TestClass_AllDMTFTypes* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetPtr_v_reference(
    TestClass_AllDMTFTypes* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_reference(
    TestClass_AllDMTFTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Set_v_octetUint8(
    TestClass_AllDMTFTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetPtr_v_octetUint8(
    TestClass_AllDMTFTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_Clear_v_octetUint8(
    TestClass_AllDMTFTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetBoolValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetBoolValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstBooleanField boolVal;
}
TestClass_AllDMTFTypes_GetBoolValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetBoolValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Construct(
    TestClass_AllDMTFTypes_GetBoolValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetBoolValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Clone(
    const TestClass_AllDMTFTypes_GetBoolValue* self,
    TestClass_AllDMTFTypes_GetBoolValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Destruct(
    TestClass_AllDMTFTypes_GetBoolValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Delete(
    TestClass_AllDMTFTypes_GetBoolValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Post(
    const TestClass_AllDMTFTypes_GetBoolValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Set_MIReturn(
    TestClass_AllDMTFTypes_GetBoolValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetBoolValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Set_boolVal(
    TestClass_AllDMTFTypes_GetBoolValue* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->boolVal)->value = x;
    ((MI_BooleanField*)&self->boolVal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetBoolValue_Clear_boolVal(
    TestClass_AllDMTFTypes_GetBoolValue* self)
{
    memset((void*)&self->boolVal, 0, sizeof(self->boolVal));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetBoolValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetBoolValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField boolVal;
}
TestClass_AllDMTFTypes_SetBoolValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetBoolValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Construct(
    TestClass_AllDMTFTypes_SetBoolValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetBoolValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Clone(
    const TestClass_AllDMTFTypes_SetBoolValue* self,
    TestClass_AllDMTFTypes_SetBoolValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Destruct(
    TestClass_AllDMTFTypes_SetBoolValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Delete(
    TestClass_AllDMTFTypes_SetBoolValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Post(
    const TestClass_AllDMTFTypes_SetBoolValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Set_MIReturn(
    TestClass_AllDMTFTypes_SetBoolValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetBoolValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Set_boolVal(
    TestClass_AllDMTFTypes_SetBoolValue* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->boolVal)->value = x;
    ((MI_BooleanField*)&self->boolVal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetBoolValue_Clear_boolVal(
    TestClass_AllDMTFTypes_SetBoolValue* self)
{
    memset((void*)&self->boolVal, 0, sizeof(self->boolVal));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetUint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetUint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint8Field Uint8Val;
}
TestClass_AllDMTFTypes_GetUint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Construct(
    TestClass_AllDMTFTypes_GetUint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetUint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Clone(
    const TestClass_AllDMTFTypes_GetUint8Value* self,
    TestClass_AllDMTFTypes_GetUint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Destruct(
    TestClass_AllDMTFTypes_GetUint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Delete(
    TestClass_AllDMTFTypes_GetUint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Post(
    const TestClass_AllDMTFTypes_GetUint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetUint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetUint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Set_Uint8Val(
    TestClass_AllDMTFTypes_GetUint8Value* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Uint8Val)->value = x;
    ((MI_Uint8Field*)&self->Uint8Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint8Value_Clear_Uint8Val(
    TestClass_AllDMTFTypes_GetUint8Value* self)
{
    memset((void*)&self->Uint8Val, 0, sizeof(self->Uint8Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetUint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetUint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8Field Uint8Val;
}
TestClass_AllDMTFTypes_SetUint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Construct(
    TestClass_AllDMTFTypes_SetUint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetUint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Clone(
    const TestClass_AllDMTFTypes_SetUint8Value* self,
    TestClass_AllDMTFTypes_SetUint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Destruct(
    TestClass_AllDMTFTypes_SetUint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Delete(
    TestClass_AllDMTFTypes_SetUint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Post(
    const TestClass_AllDMTFTypes_SetUint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetUint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetUint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Set_Uint8Val(
    TestClass_AllDMTFTypes_SetUint8Value* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Uint8Val)->value = x;
    ((MI_Uint8Field*)&self->Uint8Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint8Value_Clear_Uint8Val(
    TestClass_AllDMTFTypes_SetUint8Value* self)
{
    memset((void*)&self->Uint8Val, 0, sizeof(self->Uint8Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetSint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetSint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint8Field Sint8Val;
}
TestClass_AllDMTFTypes_GetSint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Construct(
    TestClass_AllDMTFTypes_GetSint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetSint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Clone(
    const TestClass_AllDMTFTypes_GetSint8Value* self,
    TestClass_AllDMTFTypes_GetSint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Destruct(
    TestClass_AllDMTFTypes_GetSint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Delete(
    TestClass_AllDMTFTypes_GetSint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Post(
    const TestClass_AllDMTFTypes_GetSint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetSint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetSint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Set_Sint8Val(
    TestClass_AllDMTFTypes_GetSint8Value* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->Sint8Val)->value = x;
    ((MI_Sint8Field*)&self->Sint8Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint8Value_Clear_Sint8Val(
    TestClass_AllDMTFTypes_GetSint8Value* self)
{
    memset((void*)&self->Sint8Val, 0, sizeof(self->Sint8Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetSint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetSint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint8Field Sint8Val;
}
TestClass_AllDMTFTypes_SetSint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Construct(
    TestClass_AllDMTFTypes_SetSint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetSint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Clone(
    const TestClass_AllDMTFTypes_SetSint8Value* self,
    TestClass_AllDMTFTypes_SetSint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Destruct(
    TestClass_AllDMTFTypes_SetSint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Delete(
    TestClass_AllDMTFTypes_SetSint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Post(
    const TestClass_AllDMTFTypes_SetSint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetSint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetSint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Set_Sint8Val(
    TestClass_AllDMTFTypes_SetSint8Value* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->Sint8Val)->value = x;
    ((MI_Sint8Field*)&self->Sint8Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint8Value_Clear_Sint8Val(
    TestClass_AllDMTFTypes_SetSint8Value* self)
{
    memset((void*)&self->Sint8Val, 0, sizeof(self->Sint8Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetUint16Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetUint16Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint16Field Uint16Val;
}
TestClass_AllDMTFTypes_GetUint16Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint16Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Construct(
    TestClass_AllDMTFTypes_GetUint16Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetUint16Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Clone(
    const TestClass_AllDMTFTypes_GetUint16Value* self,
    TestClass_AllDMTFTypes_GetUint16Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Destruct(
    TestClass_AllDMTFTypes_GetUint16Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Delete(
    TestClass_AllDMTFTypes_GetUint16Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Post(
    const TestClass_AllDMTFTypes_GetUint16Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetUint16Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetUint16Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Set_Uint16Val(
    TestClass_AllDMTFTypes_GetUint16Value* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Uint16Val)->value = x;
    ((MI_Uint16Field*)&self->Uint16Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint16Value_Clear_Uint16Val(
    TestClass_AllDMTFTypes_GetUint16Value* self)
{
    memset((void*)&self->Uint16Val, 0, sizeof(self->Uint16Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetUint16Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetUint16Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field Uint16Val;
}
TestClass_AllDMTFTypes_SetUint16Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint16Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Construct(
    TestClass_AllDMTFTypes_SetUint16Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetUint16Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Clone(
    const TestClass_AllDMTFTypes_SetUint16Value* self,
    TestClass_AllDMTFTypes_SetUint16Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Destruct(
    TestClass_AllDMTFTypes_SetUint16Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Delete(
    TestClass_AllDMTFTypes_SetUint16Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Post(
    const TestClass_AllDMTFTypes_SetUint16Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetUint16Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetUint16Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Set_Uint16Val(
    TestClass_AllDMTFTypes_SetUint16Value* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Uint16Val)->value = x;
    ((MI_Uint16Field*)&self->Uint16Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint16Value_Clear_Uint16Val(
    TestClass_AllDMTFTypes_SetUint16Value* self)
{
    memset((void*)&self->Uint16Val, 0, sizeof(self->Uint16Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetSint16Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetSint16Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint16Field Sint16Val;
}
TestClass_AllDMTFTypes_GetSint16Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint16Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Construct(
    TestClass_AllDMTFTypes_GetSint16Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetSint16Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Clone(
    const TestClass_AllDMTFTypes_GetSint16Value* self,
    TestClass_AllDMTFTypes_GetSint16Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Destruct(
    TestClass_AllDMTFTypes_GetSint16Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Delete(
    TestClass_AllDMTFTypes_GetSint16Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Post(
    const TestClass_AllDMTFTypes_GetSint16Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetSint16Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetSint16Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Set_Sint16Val(
    TestClass_AllDMTFTypes_GetSint16Value* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->Sint16Val)->value = x;
    ((MI_Sint16Field*)&self->Sint16Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint16Value_Clear_Sint16Val(
    TestClass_AllDMTFTypes_GetSint16Value* self)
{
    memset((void*)&self->Sint16Val, 0, sizeof(self->Sint16Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetSint16Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetSint16Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint16Field Sint16Val;
}
TestClass_AllDMTFTypes_SetSint16Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint16Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Construct(
    TestClass_AllDMTFTypes_SetSint16Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetSint16Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Clone(
    const TestClass_AllDMTFTypes_SetSint16Value* self,
    TestClass_AllDMTFTypes_SetSint16Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Destruct(
    TestClass_AllDMTFTypes_SetSint16Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Delete(
    TestClass_AllDMTFTypes_SetSint16Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Post(
    const TestClass_AllDMTFTypes_SetSint16Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetSint16Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetSint16Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Set_Sint16Val(
    TestClass_AllDMTFTypes_SetSint16Value* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->Sint16Val)->value = x;
    ((MI_Sint16Field*)&self->Sint16Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint16Value_Clear_Sint16Val(
    TestClass_AllDMTFTypes_SetSint16Value* self)
{
    memset((void*)&self->Sint16Val, 0, sizeof(self->Sint16Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetUint32Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetUint32Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint32Field Uint32Val;
}
TestClass_AllDMTFTypes_GetUint32Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint32Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Construct(
    TestClass_AllDMTFTypes_GetUint32Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetUint32Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Clone(
    const TestClass_AllDMTFTypes_GetUint32Value* self,
    TestClass_AllDMTFTypes_GetUint32Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Destruct(
    TestClass_AllDMTFTypes_GetUint32Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Delete(
    TestClass_AllDMTFTypes_GetUint32Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Post(
    const TestClass_AllDMTFTypes_GetUint32Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetUint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetUint32Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Set_Uint32Val(
    TestClass_AllDMTFTypes_GetUint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Uint32Val)->value = x;
    ((MI_Uint32Field*)&self->Uint32Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint32Value_Clear_Uint32Val(
    TestClass_AllDMTFTypes_GetUint32Value* self)
{
    memset((void*)&self->Uint32Val, 0, sizeof(self->Uint32Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetUint32Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetUint32Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field Uint32Val;
}
TestClass_AllDMTFTypes_SetUint32Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint32Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Construct(
    TestClass_AllDMTFTypes_SetUint32Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetUint32Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Clone(
    const TestClass_AllDMTFTypes_SetUint32Value* self,
    TestClass_AllDMTFTypes_SetUint32Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Destruct(
    TestClass_AllDMTFTypes_SetUint32Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Delete(
    TestClass_AllDMTFTypes_SetUint32Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Post(
    const TestClass_AllDMTFTypes_SetUint32Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetUint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetUint32Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Set_Uint32Val(
    TestClass_AllDMTFTypes_SetUint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Uint32Val)->value = x;
    ((MI_Uint32Field*)&self->Uint32Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint32Value_Clear_Uint32Val(
    TestClass_AllDMTFTypes_SetUint32Value* self)
{
    memset((void*)&self->Uint32Val, 0, sizeof(self->Uint32Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetSint32Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetSint32Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint32Field Sint32Val;
}
TestClass_AllDMTFTypes_GetSint32Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint32Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Construct(
    TestClass_AllDMTFTypes_GetSint32Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetSint32Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Clone(
    const TestClass_AllDMTFTypes_GetSint32Value* self,
    TestClass_AllDMTFTypes_GetSint32Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Destruct(
    TestClass_AllDMTFTypes_GetSint32Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Delete(
    TestClass_AllDMTFTypes_GetSint32Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Post(
    const TestClass_AllDMTFTypes_GetSint32Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetSint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetSint32Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Set_Sint32Val(
    TestClass_AllDMTFTypes_GetSint32Value* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Sint32Val)->value = x;
    ((MI_Sint32Field*)&self->Sint32Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint32Value_Clear_Sint32Val(
    TestClass_AllDMTFTypes_GetSint32Value* self)
{
    memset((void*)&self->Sint32Val, 0, sizeof(self->Sint32Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetSint32Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetSint32Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint32Field Sint32Val;
}
TestClass_AllDMTFTypes_SetSint32Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint32Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Construct(
    TestClass_AllDMTFTypes_SetSint32Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetSint32Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Clone(
    const TestClass_AllDMTFTypes_SetSint32Value* self,
    TestClass_AllDMTFTypes_SetSint32Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Destruct(
    TestClass_AllDMTFTypes_SetSint32Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Delete(
    TestClass_AllDMTFTypes_SetSint32Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Post(
    const TestClass_AllDMTFTypes_SetSint32Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetSint32Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetSint32Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Set_Sint32Val(
    TestClass_AllDMTFTypes_SetSint32Value* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Sint32Val)->value = x;
    ((MI_Sint32Field*)&self->Sint32Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint32Value_Clear_Sint32Val(
    TestClass_AllDMTFTypes_SetSint32Value* self)
{
    memset((void*)&self->Sint32Val, 0, sizeof(self->Sint32Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetUint64Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetUint64Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint64Field Uint64Val;
}
TestClass_AllDMTFTypes_GetUint64Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint64Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Construct(
    TestClass_AllDMTFTypes_GetUint64Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetUint64Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Clone(
    const TestClass_AllDMTFTypes_GetUint64Value* self,
    TestClass_AllDMTFTypes_GetUint64Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Destruct(
    TestClass_AllDMTFTypes_GetUint64Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Delete(
    TestClass_AllDMTFTypes_GetUint64Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Post(
    const TestClass_AllDMTFTypes_GetUint64Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetUint64Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetUint64Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Set_Uint64Val(
    TestClass_AllDMTFTypes_GetUint64Value* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Uint64Val)->value = x;
    ((MI_Uint64Field*)&self->Uint64Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetUint64Value_Clear_Uint64Val(
    TestClass_AllDMTFTypes_GetUint64Value* self)
{
    memset((void*)&self->Uint64Val, 0, sizeof(self->Uint64Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetUint64Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetUint64Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64Field Uint64Val;
}
TestClass_AllDMTFTypes_SetUint64Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint64Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Construct(
    TestClass_AllDMTFTypes_SetUint64Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetUint64Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Clone(
    const TestClass_AllDMTFTypes_SetUint64Value* self,
    TestClass_AllDMTFTypes_SetUint64Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Destruct(
    TestClass_AllDMTFTypes_SetUint64Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Delete(
    TestClass_AllDMTFTypes_SetUint64Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Post(
    const TestClass_AllDMTFTypes_SetUint64Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetUint64Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetUint64Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Set_Uint64Val(
    TestClass_AllDMTFTypes_SetUint64Value* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Uint64Val)->value = x;
    ((MI_Uint64Field*)&self->Uint64Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetUint64Value_Clear_Uint64Val(
    TestClass_AllDMTFTypes_SetUint64Value* self)
{
    memset((void*)&self->Uint64Val, 0, sizeof(self->Uint64Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetSint64Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetSint64Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstSint64Field Sint64Val;
}
TestClass_AllDMTFTypes_GetSint64Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint64Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Construct(
    TestClass_AllDMTFTypes_GetSint64Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetSint64Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Clone(
    const TestClass_AllDMTFTypes_GetSint64Value* self,
    TestClass_AllDMTFTypes_GetSint64Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Destruct(
    TestClass_AllDMTFTypes_GetSint64Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Delete(
    TestClass_AllDMTFTypes_GetSint64Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Post(
    const TestClass_AllDMTFTypes_GetSint64Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetSint64Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetSint64Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Set_Sint64Val(
    TestClass_AllDMTFTypes_GetSint64Value* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Sint64Val)->value = x;
    ((MI_Sint64Field*)&self->Sint64Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetSint64Value_Clear_Sint64Val(
    TestClass_AllDMTFTypes_GetSint64Value* self)
{
    memset((void*)&self->Sint64Val, 0, sizeof(self->Sint64Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetSint64Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetSint64Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint64Field Sint64Val;
}
TestClass_AllDMTFTypes_SetSint64Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint64Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Construct(
    TestClass_AllDMTFTypes_SetSint64Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetSint64Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Clone(
    const TestClass_AllDMTFTypes_SetSint64Value* self,
    TestClass_AllDMTFTypes_SetSint64Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Destruct(
    TestClass_AllDMTFTypes_SetSint64Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Delete(
    TestClass_AllDMTFTypes_SetSint64Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Post(
    const TestClass_AllDMTFTypes_SetSint64Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetSint64Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetSint64Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Set_Sint64Val(
    TestClass_AllDMTFTypes_SetSint64Value* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Sint64Val)->value = x;
    ((MI_Sint64Field*)&self->Sint64Val)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetSint64Value_Clear_Sint64Val(
    TestClass_AllDMTFTypes_SetSint64Value* self)
{
    memset((void*)&self->Sint64Val, 0, sizeof(self->Sint64Val));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetStringCustomOption()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetStringCustomOption
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField optionName;
    /*OUT*/ MI_ConstStringField optionValue;
}
TestClass_AllDMTFTypes_GetStringCustomOption;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetStringCustomOption_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Construct(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetStringCustomOption_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Clone(
    const TestClass_AllDMTFTypes_GetStringCustomOption* self,
    TestClass_AllDMTFTypes_GetStringCustomOption** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Destruct(
    TestClass_AllDMTFTypes_GetStringCustomOption* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Delete(
    TestClass_AllDMTFTypes_GetStringCustomOption* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Post(
    const TestClass_AllDMTFTypes_GetStringCustomOption* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Set_MIReturn(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetStringCustomOption* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Set_optionName(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_SetPtr_optionName(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Clear_optionName(
    TestClass_AllDMTFTypes_GetStringCustomOption* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Set_optionValue(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_SetPtr_optionValue(
    TestClass_AllDMTFTypes_GetStringCustomOption* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetStringCustomOption_Clear_optionValue(
    TestClass_AllDMTFTypes_GetStringCustomOption* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetEmbeddedObjectValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetEmbeddedObjectValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstReferenceField EmbeddedObjectVal;
}
TestClass_AllDMTFTypes_GetEmbeddedObjectValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetEmbeddedObjectValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Construct(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetEmbeddedObjectValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Clone(
    const TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Destruct(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Delete(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Post(
    const TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Set_MIReturn(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Set_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_SetPtr_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Clear_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetEmbeddedObjectValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetEmbeddedObjectValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReferenceField EmbeddedObjectVal;
}
TestClass_AllDMTFTypes_SetEmbeddedObjectValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetEmbeddedObjectValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Construct(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetEmbeddedObjectValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Clone(
    const TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Destruct(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Delete(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Post(
    const TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Set_MIReturn(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Set_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_SetPtr_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Clear_EmbeddedObjectVal(
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetEmbeddedInstanceValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetEmbeddedInstanceValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ TestClass_ForEmbedded_ConstRef EmbeddedInstanceVal;
}
TestClass_AllDMTFTypes_GetEmbeddedInstanceValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Construct(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Clone(
    const TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Destruct(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Delete(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Post(
    const TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Set_MIReturn(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Set_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_SetPtr_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Clear_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetEmbeddedInstanceValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetEmbeddedInstanceValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ TestClass_ForEmbedded_ConstRef EmbeddedInstanceVal;
}
TestClass_AllDMTFTypes_SetEmbeddedInstanceValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Construct(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Clone(
    const TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Destruct(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Delete(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Post(
    const TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Set_MIReturn(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Set_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_SetPtr_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Clear_EmbeddedInstanceVal(
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetReferenceValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetReferenceValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ TestClass_ForEmbedded_ConstRef ReferenceVal;
}
TestClass_AllDMTFTypes_GetReferenceValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetReferenceValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Construct(
    TestClass_AllDMTFTypes_GetReferenceValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetReferenceValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Clone(
    const TestClass_AllDMTFTypes_GetReferenceValue* self,
    TestClass_AllDMTFTypes_GetReferenceValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Destruct(
    TestClass_AllDMTFTypes_GetReferenceValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Delete(
    TestClass_AllDMTFTypes_GetReferenceValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Post(
    const TestClass_AllDMTFTypes_GetReferenceValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Set_MIReturn(
    TestClass_AllDMTFTypes_GetReferenceValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetReferenceValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Set_ReferenceVal(
    TestClass_AllDMTFTypes_GetReferenceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_SetPtr_ReferenceVal(
    TestClass_AllDMTFTypes_GetReferenceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetReferenceValue_Clear_ReferenceVal(
    TestClass_AllDMTFTypes_GetReferenceValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetReferenceValue()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetReferenceValue
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ TestClass_ForEmbedded_ConstRef ReferenceVal;
}
TestClass_AllDMTFTypes_SetReferenceValue;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetReferenceValue_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Construct(
    TestClass_AllDMTFTypes_SetReferenceValue* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetReferenceValue_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Clone(
    const TestClass_AllDMTFTypes_SetReferenceValue* self,
    TestClass_AllDMTFTypes_SetReferenceValue** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Destruct(
    TestClass_AllDMTFTypes_SetReferenceValue* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Delete(
    TestClass_AllDMTFTypes_SetReferenceValue* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Post(
    const TestClass_AllDMTFTypes_SetReferenceValue* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Set_MIReturn(
    TestClass_AllDMTFTypes_SetReferenceValue* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetReferenceValue* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Set_ReferenceVal(
    TestClass_AllDMTFTypes_SetReferenceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_SetPtr_ReferenceVal(
    TestClass_AllDMTFTypes_SetReferenceValue* self,
    const TestClass_ForEmbedded* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetReferenceValue_Clear_ReferenceVal(
    TestClass_AllDMTFTypes_SetReferenceValue* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.GetOctetUint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_GetOctetUint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint8AField v_octetUint8Val;
}
TestClass_AllDMTFTypes_GetOctetUint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetOctetUint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Construct(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_GetOctetUint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Clone(
    const TestClass_AllDMTFTypes_GetOctetUint8Value* self,
    TestClass_AllDMTFTypes_GetOctetUint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Destruct(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Delete(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Post(
    const TestClass_AllDMTFTypes_GetOctetUint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Set_v_octetUint8Val(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_SetPtr_v_octetUint8Val(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_GetOctetUint8Value_Clear_v_octetUint8Val(
    TestClass_AllDMTFTypes_GetOctetUint8Value* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes.SetOctetUint8Value()
**
**==============================================================================
*/

typedef struct _TestClass_AllDMTFTypes_SetOctetUint8Value
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint8AField v_octetUint8Val;
}
TestClass_AllDMTFTypes_SetOctetUint8Value;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetOctetUint8Value_rtti;

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Construct(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_AllDMTFTypes_SetOctetUint8Value_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Clone(
    const TestClass_AllDMTFTypes_SetOctetUint8Value* self,
    TestClass_AllDMTFTypes_SetOctetUint8Value** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Destruct(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Delete(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Post(
    const TestClass_AllDMTFTypes_SetOctetUint8Value* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Set_MIReturn(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Clear_MIReturn(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Set_v_octetUint8Val(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_SetPtr_v_octetUint8Val(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self,
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

MI_INLINE MI_Result MI_CALL TestClass_AllDMTFTypes_SetOctetUint8Value_Clear_v_octetUint8Val(
    TestClass_AllDMTFTypes_SetOctetUint8Value* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** TestClass_AllDMTFTypes provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestClass_AllDMTFTypes_Self TestClass_AllDMTFTypes_Self;

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Load(
    TestClass_AllDMTFTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Unload(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_EnumerateInstances(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_GetInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_CreateInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* newInstance);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_ModifyInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_DeleteInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* instanceName);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetBoolValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetBoolValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetBoolValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetBoolValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint8Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint8Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint8Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint8Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint16Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint16Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint16Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint16Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint32Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint32Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint32Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint32Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint64Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint64Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint64Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint64Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetStringCustomOption(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetStringCustomOption* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetEmbeddedObjectValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetEmbeddedObjectValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetEmbeddedObjectValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetEmbeddedObjectValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetEmbeddedInstanceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetEmbeddedInstanceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetReferenceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetReferenceValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetReferenceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetReferenceValue* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_GetOctetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetOctetUint8Value* in);

MI_EXTERN_C void MI_CALL TestClass_AllDMTFTypes_Invoke_SetOctetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetOctetUint8Value* in);


#endif /* _TestClass_AllDMTFTypes_h */
