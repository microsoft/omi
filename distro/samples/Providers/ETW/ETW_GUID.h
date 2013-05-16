/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ETW_GUID_h
#define _ETW_GUID_h

#include <MI.h>

/*
**==============================================================================
**
** ETW_GUID [ETW_GUID]
**
** Keys:
**
**==============================================================================
*/

typedef struct _ETW_GUID
{
    MI_Instance __instance;
    /* ETW_GUID properties */
    MI_ConstUint32Field Data1;
    MI_ConstUint16Field Data2;
    MI_ConstUint16Field Data3;
    MI_ConstUint8AField Data4;
}
ETW_GUID;

typedef struct _ETW_GUID_Ref
{
    ETW_GUID* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_GUID_Ref;

typedef struct _ETW_GUID_ConstRef
{
    MI_CONST ETW_GUID* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_GUID_ConstRef;

typedef struct _ETW_GUID_Array
{
    struct _ETW_GUID** data;
    MI_Uint32 size;
}
ETW_GUID_Array;

typedef struct _ETW_GUID_ConstArray
{
    struct _ETW_GUID MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ETW_GUID_ConstArray;

typedef struct _ETW_GUID_ArrayRef
{
    ETW_GUID_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_GUID_ArrayRef;

typedef struct _ETW_GUID_ConstArrayRef
{
    ETW_GUID_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ETW_GUID_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ETW_GUID_rtti;

MI_INLINE MI_Result MI_CALL ETW_GUID_Construct(
    ETW_GUID* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ETW_GUID_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Clone(
    const ETW_GUID* self,
    ETW_GUID** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ETW_GUID_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ETW_GUID_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Destruct(ETW_GUID* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Delete(ETW_GUID* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Post(
    const ETW_GUID* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Set_Data1(
    ETW_GUID* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Data1)->value = x;
    ((MI_Uint32Field*)&self->Data1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Clear_Data1(
    ETW_GUID* self)
{
    memset((void*)&self->Data1, 0, sizeof(self->Data1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Set_Data2(
    ETW_GUID* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Data2)->value = x;
    ((MI_Uint16Field*)&self->Data2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Clear_Data2(
    ETW_GUID* self)
{
    memset((void*)&self->Data2, 0, sizeof(self->Data2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Set_Data3(
    ETW_GUID* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Data3)->value = x;
    ((MI_Uint16Field*)&self->Data3)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Clear_Data3(
    ETW_GUID* self)
{
    memset((void*)&self->Data3, 0, sizeof(self->Data3));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Set_Data4(
    ETW_GUID* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_SetPtr_Data4(
    ETW_GUID* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ETW_GUID_Clear_Data4(
    ETW_GUID* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _ETW_GUID_h */
