/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MILargeEvent_h
#define _MILargeEvent_h

#include <MI.h>
#include "ETW_Event.h"
#include "ETW_EventHeader.h"

/*
**==============================================================================
**
** MILargeEvent [MILargeEvent]
**
** Keys:
**    ID
**
**==============================================================================
*/

typedef struct _MILargeEvent /* extends ETW_Event */
{
    MI_Instance __instance;
    /* ETW_Event properties */
    ETW_EventHeader_ConstRef Header;
    /* MILargeEvent properties */
    /*KEY*/ MI_ConstUint32Field ID;
    MI_ConstUint32Field number1;
    MI_ConstUint32Field number2;
    MI_ConstUint32Field number3;
    MI_ConstUint32Field number4;
    MI_ConstUint32Field number5;
    MI_ConstUint32Field number6;
    MI_ConstUint32Field number7;
    MI_ConstUint32Field number8;
    MI_ConstUint32Field number9;
    MI_ConstUint32Field number10;
    MI_ConstStringField string1;
    MI_ConstStringField string2;
    MI_ConstStringField string3;
    MI_ConstStringField string4;
    MI_ConstStringField string5;
    MI_ConstStringField string6;
    MI_ConstStringField string7;
    MI_ConstStringField string8;
    MI_ConstStringField string9;
    MI_ConstStringField string10;
}
MILargeEvent;

typedef struct _MILargeEvent_Ref
{
    MILargeEvent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MILargeEvent_Ref;

typedef struct _MILargeEvent_ConstRef
{
    MI_CONST MILargeEvent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MILargeEvent_ConstRef;

typedef struct _MILargeEvent_Array
{
    struct _MILargeEvent** data;
    MI_Uint32 size;
}
MILargeEvent_Array;

typedef struct _MILargeEvent_ConstArray
{
    struct _MILargeEvent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MILargeEvent_ConstArray;

typedef struct _MILargeEvent_ArrayRef
{
    MILargeEvent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MILargeEvent_ArrayRef;

typedef struct _MILargeEvent_ConstArrayRef
{
    MILargeEvent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MILargeEvent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MILargeEvent_rtti;

MI_INLINE MI_Result MI_CALL MILargeEvent_Construct(
    MILargeEvent* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MILargeEvent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clone(
    const MILargeEvent* self,
    MILargeEvent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MILargeEvent_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MILargeEvent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Destruct(MILargeEvent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Delete(MILargeEvent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Post(
    const MILargeEvent* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_Header(
    MILargeEvent* self,
    const ETW_EventHeader* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_Header(
    MILargeEvent* self,
    const ETW_EventHeader* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_Header(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_ID(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ID)->value = x;
    ((MI_Uint32Field*)&self->ID)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_ID(
    MILargeEvent* self)
{
    memset((void*)&self->ID, 0, sizeof(self->ID));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number1(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number1)->value = x;
    ((MI_Uint32Field*)&self->number1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number1(
    MILargeEvent* self)
{
    memset((void*)&self->number1, 0, sizeof(self->number1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number2(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number2)->value = x;
    ((MI_Uint32Field*)&self->number2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number2(
    MILargeEvent* self)
{
    memset((void*)&self->number2, 0, sizeof(self->number2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number3(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number3)->value = x;
    ((MI_Uint32Field*)&self->number3)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number3(
    MILargeEvent* self)
{
    memset((void*)&self->number3, 0, sizeof(self->number3));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number4(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number4)->value = x;
    ((MI_Uint32Field*)&self->number4)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number4(
    MILargeEvent* self)
{
    memset((void*)&self->number4, 0, sizeof(self->number4));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number5(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number5)->value = x;
    ((MI_Uint32Field*)&self->number5)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number5(
    MILargeEvent* self)
{
    memset((void*)&self->number5, 0, sizeof(self->number5));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number6(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number6)->value = x;
    ((MI_Uint32Field*)&self->number6)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number6(
    MILargeEvent* self)
{
    memset((void*)&self->number6, 0, sizeof(self->number6));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number7(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number7)->value = x;
    ((MI_Uint32Field*)&self->number7)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number7(
    MILargeEvent* self)
{
    memset((void*)&self->number7, 0, sizeof(self->number7));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number8(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number8)->value = x;
    ((MI_Uint32Field*)&self->number8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number8(
    MILargeEvent* self)
{
    memset((void*)&self->number8, 0, sizeof(self->number8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number9(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number9)->value = x;
    ((MI_Uint32Field*)&self->number9)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number9(
    MILargeEvent* self)
{
    memset((void*)&self->number9, 0, sizeof(self->number9));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_number10(
    MILargeEvent* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->number10)->value = x;
    ((MI_Uint32Field*)&self->number10)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_number10(
    MILargeEvent* self)
{
    memset((void*)&self->number10, 0, sizeof(self->number10));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string1(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string1(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string1(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string2(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string2(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string2(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string3(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string3(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string3(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string4(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string4(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string4(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string5(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string5(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string5(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string6(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string6(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string6(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string7(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string7(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string7(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string8(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string8(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string8(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string9(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string9(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string9(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Set_string10(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_SetPtr_string10(
    MILargeEvent* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MILargeEvent_Clear_string10(
    MILargeEvent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

/*
**==============================================================================
**
** MILargeEvent provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MILargeEvent_Self MILargeEvent_Self;

MI_EXTERN_C void MI_CALL MILargeEvent_Load(
    MILargeEvent_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MILargeEvent_Unload(
    MILargeEvent_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MILargeEvent_EnumerateInstances(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MILargeEvent_GetInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MILargeEvent_CreateInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* newInstance);

MI_EXTERN_C void MI_CALL MILargeEvent_ModifyInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MILargeEvent_DeleteInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* instanceName);


#endif /* _MILargeEvent_h */
