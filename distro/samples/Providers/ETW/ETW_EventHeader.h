/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ETW_EventHeader_h
#define _ETW_EventHeader_h

#include <MI.h>
#include "ETW_GUID.h"

/*
**==============================================================================
**
** ETW_EventHeader [ETW_EventHeader]
**
** Keys:
**
**==============================================================================
*/

typedef struct _ETW_EventHeader
{
    MI_Instance __instance;
    /* ETW_EventHeader properties */
    MI_ConstUint64Field ThreadId;
    MI_ConstUint64Field ProcessId;
    MI_ConstDatetimeField TimeStamp;
    ETW_GUID_ConstRef ActivityId;
    ETW_GUID_ConstRef ProviderId;
    MI_ConstUint16Field EventId;
    MI_ConstUint8Field Version;
    MI_ConstUint8Field Channel;
    MI_ConstUint8Field Level;
    MI_ConstUint8Field Opcode;
    MI_ConstUint16Field Task;
    MI_ConstUint64Field Keyword;
}
ETW_EventHeader;

typedef struct _ETW_EventHeader_Ref
{
    ETW_EventHeader* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_EventHeader_Ref;

typedef struct _ETW_EventHeader_ConstRef
{
    MI_CONST ETW_EventHeader* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_EventHeader_ConstRef;

typedef struct _ETW_EventHeader_Array
{
    struct _ETW_EventHeader** data;
    MI_Uint32 size;
}
ETW_EventHeader_Array;

typedef struct _ETW_EventHeader_ConstArray
{
    struct _ETW_EventHeader MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ETW_EventHeader_ConstArray;

typedef struct _ETW_EventHeader_ArrayRef
{
    ETW_EventHeader_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_EventHeader_ArrayRef;

typedef struct _ETW_EventHeader_ConstArrayRef
{
    ETW_EventHeader_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_EventHeader_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ETW_EventHeader_rtti;

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Construct(
    ETW_EventHeader* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ETW_EventHeader_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clone(
    const ETW_EventHeader* self,
    ETW_EventHeader** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ETW_EventHeader_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ETW_EventHeader_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Destruct(ETW_EventHeader* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Delete(ETW_EventHeader* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Post(
    const ETW_EventHeader* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_ThreadId(
    ETW_EventHeader* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ThreadId)->value = x;
    ((MI_Uint64Field*)&self->ThreadId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_ThreadId(
    ETW_EventHeader* self)
{
    memset((void*)&self->ThreadId, 0, sizeof(self->ThreadId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_ProcessId(
    ETW_EventHeader* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ProcessId)->value = x;
    ((MI_Uint64Field*)&self->ProcessId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_ProcessId(
    ETW_EventHeader* self)
{
    memset((void*)&self->ProcessId, 0, sizeof(self->ProcessId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_TimeStamp(
    ETW_EventHeader* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeStamp)->value = x;
    ((MI_DatetimeField*)&self->TimeStamp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_TimeStamp(
    ETW_EventHeader* self)
{
    memset((void*)&self->TimeStamp, 0, sizeof(self->TimeStamp));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_ActivityId(
    ETW_EventHeader* self,
    const ETW_GUID* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_SetPtr_ActivityId(
    ETW_EventHeader* self,
    const ETW_GUID* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_ActivityId(
    ETW_EventHeader* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_ProviderId(
    ETW_EventHeader* self,
    const ETW_GUID* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_SetPtr_ProviderId(
    ETW_EventHeader* self,
    const ETW_GUID* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_ProviderId(
    ETW_EventHeader* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_EventId(
    ETW_EventHeader* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EventId)->value = x;
    ((MI_Uint16Field*)&self->EventId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_EventId(
    ETW_EventHeader* self)
{
    memset((void*)&self->EventId, 0, sizeof(self->EventId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Version(
    ETW_EventHeader* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Version)->value = x;
    ((MI_Uint8Field*)&self->Version)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Version(
    ETW_EventHeader* self)
{
    memset((void*)&self->Version, 0, sizeof(self->Version));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Channel(
    ETW_EventHeader* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Channel)->value = x;
    ((MI_Uint8Field*)&self->Channel)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Channel(
    ETW_EventHeader* self)
{
    memset((void*)&self->Channel, 0, sizeof(self->Channel));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Level(
    ETW_EventHeader* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Level)->value = x;
    ((MI_Uint8Field*)&self->Level)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Level(
    ETW_EventHeader* self)
{
    memset((void*)&self->Level, 0, sizeof(self->Level));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Opcode(
    ETW_EventHeader* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->Opcode)->value = x;
    ((MI_Uint8Field*)&self->Opcode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Opcode(
    ETW_EventHeader* self)
{
    memset((void*)&self->Opcode, 0, sizeof(self->Opcode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Task(
    ETW_EventHeader* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Task)->value = x;
    ((MI_Uint16Field*)&self->Task)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Task(
    ETW_EventHeader* self)
{
    memset((void*)&self->Task, 0, sizeof(self->Task));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Set_Keyword(
    ETW_EventHeader* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Keyword)->value = x;
    ((MI_Uint64Field*)&self->Keyword)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_EventHeader_Clear_Keyword(
    ETW_EventHeader* self)
{
    memset((void*)&self->Keyword, 0, sizeof(self->Keyword));
    return MI_RESULT_OK;
}


#endif /* _ETW_EventHeader_h */
