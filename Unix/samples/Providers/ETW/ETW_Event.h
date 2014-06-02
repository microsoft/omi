/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ETW_Event_h
#define _ETW_Event_h

#include <MI.h>
#include "ETW_EventHeader.h"

/*
**==============================================================================
**
** ETW_Event [ETW_Event]
**
** Keys:
**
**==============================================================================
*/

typedef struct _ETW_Event
{
    MI_Instance __instance;
    /* ETW_Event properties */
    ETW_EventHeader_ConstRef Header;
}
ETW_Event;

typedef struct _ETW_Event_Ref
{
    ETW_Event* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_Event_Ref;

typedef struct _ETW_Event_ConstRef
{
    MI_CONST ETW_Event* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_Event_ConstRef;

typedef struct _ETW_Event_Array
{
    struct _ETW_Event** data;
    MI_Uint32 size;
}
ETW_Event_Array;

typedef struct _ETW_Event_ConstArray
{
    struct _ETW_Event MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ETW_Event_ConstArray;

typedef struct _ETW_Event_ArrayRef
{
    ETW_Event_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_Event_ArrayRef;

typedef struct _ETW_Event_ConstArrayRef
{
    ETW_Event_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_Event_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ETW_Event_rtti;

MI_INLINE MI_Result MI_CALL ETW_Event_Construct(
    ETW_Event* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ETW_Event_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_Event_Clone(
    const ETW_Event* self,
    ETW_Event** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ETW_Event_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ETW_Event_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ETW_Event_Destruct(ETW_Event* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_Event_Delete(ETW_Event* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_Event_Post(
    const ETW_Event* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_Event_Set_Header(
    ETW_Event* self,
    const ETW_EventHeader* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL ETW_Event_SetPtr_Header(
    ETW_Event* self,
    const ETW_EventHeader* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ETW_Event_Clear_Header(
    ETW_Event* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}


#endif /* _ETW_Event_h */
