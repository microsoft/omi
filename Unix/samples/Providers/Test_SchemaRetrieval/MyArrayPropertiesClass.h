/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyArrayPropertiesClass_h
#define _MyArrayPropertiesClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyArrayPropertiesClass [MyArrayPropertiesClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyArrayPropertiesClass
{
    MI_Instance __instance;
    /* MyArrayPropertiesClass properties */
    MI_ConstBooleanAField booleanArrayProp;
    MI_ConstStringAField stringArrayProp;
    MI_ConstChar16AField char16ArrayProp;
    MI_ConstUint8AField uint8ArrayProp;
    MI_ConstSint8AField sint8ArrayProp;
    MI_ConstUint16AField uint16ArrayProp;
    MI_ConstSint16AField sint16ArrayProp;
    MI_ConstUint32AField uint32ArrayProp;
    MI_ConstSint32AField sint32ArrayProp;
    MI_ConstUint64AField uint64ArrayProp;
    MI_ConstSint64AField sint64ArrayProp;
    MI_ConstReal32AField real32ArrayProp;
    MI_ConstReal64AField real64ArrayProp;
    MI_ConstDatetimeAField datetimeArrayProp;
}
MyArrayPropertiesClass;

typedef struct _MyArrayPropertiesClass_Ref
{
    MyArrayPropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayPropertiesClass_Ref;

typedef struct _MyArrayPropertiesClass_ConstRef
{
    MI_CONST MyArrayPropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayPropertiesClass_ConstRef;

typedef struct _MyArrayPropertiesClass_Array
{
    struct _MyArrayPropertiesClass** data;
    MI_Uint32 size;
}
MyArrayPropertiesClass_Array;

typedef struct _MyArrayPropertiesClass_ConstArray
{
    struct _MyArrayPropertiesClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyArrayPropertiesClass_ConstArray;

typedef struct _MyArrayPropertiesClass_ArrayRef
{
    MyArrayPropertiesClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayPropertiesClass_ArrayRef;

typedef struct _MyArrayPropertiesClass_ConstArrayRef
{
    MyArrayPropertiesClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayPropertiesClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyArrayPropertiesClass_rtti;

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Construct(
    MyArrayPropertiesClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyArrayPropertiesClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clone(
    const MyArrayPropertiesClass* self,
    MyArrayPropertiesClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyArrayPropertiesClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyArrayPropertiesClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Destruct(MyArrayPropertiesClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Delete(MyArrayPropertiesClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Post(
    const MyArrayPropertiesClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_booleanArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_booleanArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_booleanArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_stringArrayProp(
    MyArrayPropertiesClass* self,
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

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_stringArrayProp(
    MyArrayPropertiesClass* self,
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

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_stringArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_char16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_char16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_char16ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_uint8ArrayProp(
    MyArrayPropertiesClass* self,
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

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_uint8ArrayProp(
    MyArrayPropertiesClass* self,
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

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_uint8ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_sint8ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_sint8ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_sint8ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_uint16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_uint16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_uint16ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_sint16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_sint16ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_sint16ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_uint32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_uint32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_uint32ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_sint32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_sint32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_sint32ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_uint64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_uint64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_uint64ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_sint64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_sint64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_sint64ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_real32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_real32ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_real32ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_real64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_real64ArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_real64ArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Set_datetimeArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_SetPtr_datetimeArrayProp(
    MyArrayPropertiesClass* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyArrayPropertiesClass_Clear_datetimeArrayProp(
    MyArrayPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

/*
**==============================================================================
**
** MyArrayPropertiesClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyArrayPropertiesClass_Self MyArrayPropertiesClass_Self;

MI_EXTERN_C void MI_CALL MyArrayPropertiesClass_Load(
    MyArrayPropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayPropertiesClass_Unload(
    MyArrayPropertiesClass_Self* self,
    MI_Context* context);


#endif /* _MyArrayPropertiesClass_h */
