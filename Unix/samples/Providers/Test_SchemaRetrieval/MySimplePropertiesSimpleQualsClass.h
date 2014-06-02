/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimplePropertiesSimpleQualsClass_h
#define _MySimplePropertiesSimpleQualsClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimplePropertiesSimpleQualsClass [MySimplePropertiesSimpleQualsClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimplePropertiesSimpleQualsClass
{
    MI_Instance __instance;
    /* MySimplePropertiesSimpleQualsClass properties */
    MI_ConstBooleanField booleanProp;
    MI_ConstStringField stringProp;
    MI_ConstChar16Field char16Prop;
    MI_ConstUint8Field uint8Prop;
    MI_ConstSint8Field sint8Prop;
    MI_ConstUint16Field uint16Prop;
    MI_ConstSint16Field sint16Prop;
    MI_ConstUint32Field uint32Prop;
    MI_ConstSint32Field sint32Prop;
    MI_ConstUint64Field uint64Prop;
    MI_ConstSint64Field sint64Prop;
    MI_ConstReal32Field real32Prop;
    MI_ConstReal64Field real64Prop;
    MI_ConstDatetimeField datetimeProp;
}
MySimplePropertiesSimpleQualsClass;

typedef struct _MySimplePropertiesSimpleQualsClass_Ref
{
    MySimplePropertiesSimpleQualsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesSimpleQualsClass_Ref;

typedef struct _MySimplePropertiesSimpleQualsClass_ConstRef
{
    MI_CONST MySimplePropertiesSimpleQualsClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesSimpleQualsClass_ConstRef;

typedef struct _MySimplePropertiesSimpleQualsClass_Array
{
    struct _MySimplePropertiesSimpleQualsClass** data;
    MI_Uint32 size;
}
MySimplePropertiesSimpleQualsClass_Array;

typedef struct _MySimplePropertiesSimpleQualsClass_ConstArray
{
    struct _MySimplePropertiesSimpleQualsClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimplePropertiesSimpleQualsClass_ConstArray;

typedef struct _MySimplePropertiesSimpleQualsClass_ArrayRef
{
    MySimplePropertiesSimpleQualsClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesSimpleQualsClass_ArrayRef;

typedef struct _MySimplePropertiesSimpleQualsClass_ConstArrayRef
{
    MySimplePropertiesSimpleQualsClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesSimpleQualsClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimplePropertiesSimpleQualsClass_rtti;

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Construct(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimplePropertiesSimpleQualsClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clone(
    const MySimplePropertiesSimpleQualsClass* self,
    MySimplePropertiesSimpleQualsClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimplePropertiesSimpleQualsClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimplePropertiesSimpleQualsClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Destruct(MySimplePropertiesSimpleQualsClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Delete(MySimplePropertiesSimpleQualsClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Post(
    const MySimplePropertiesSimpleQualsClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_booleanProp(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->booleanProp)->value = x;
    ((MI_BooleanField*)&self->booleanProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_booleanProp(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->booleanProp, 0, sizeof(self->booleanProp));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_stringProp(
    MySimplePropertiesSimpleQualsClass* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_SetPtr_stringProp(
    MySimplePropertiesSimpleQualsClass* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_stringProp(
    MySimplePropertiesSimpleQualsClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_char16Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Prop)->value = x;
    ((MI_Char16Field*)&self->char16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_char16Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->char16Prop, 0, sizeof(self->char16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_uint8Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Prop)->value = x;
    ((MI_Uint8Field*)&self->uint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_uint8Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->uint8Prop, 0, sizeof(self->uint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_sint8Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Prop)->value = x;
    ((MI_Sint8Field*)&self->sint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_sint8Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->sint8Prop, 0, sizeof(self->sint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_uint16Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Prop)->value = x;
    ((MI_Uint16Field*)&self->uint16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_uint16Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->uint16Prop, 0, sizeof(self->uint16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_sint16Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Prop)->value = x;
    ((MI_Sint16Field*)&self->sint16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_sint16Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->sint16Prop, 0, sizeof(self->sint16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_uint32Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Prop)->value = x;
    ((MI_Uint32Field*)&self->uint32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_uint32Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->uint32Prop, 0, sizeof(self->uint32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_sint32Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Prop)->value = x;
    ((MI_Sint32Field*)&self->sint32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_sint32Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->sint32Prop, 0, sizeof(self->sint32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_uint64Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Prop)->value = x;
    ((MI_Uint64Field*)&self->uint64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_uint64Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->uint64Prop, 0, sizeof(self->uint64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_sint64Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Prop)->value = x;
    ((MI_Sint64Field*)&self->sint64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_sint64Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->sint64Prop, 0, sizeof(self->sint64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_real32Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Prop)->value = x;
    ((MI_Real32Field*)&self->real32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_real32Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->real32Prop, 0, sizeof(self->real32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_real64Prop(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Prop)->value = x;
    ((MI_Real64Field*)&self->real64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_real64Prop(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->real64Prop, 0, sizeof(self->real64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Set_datetimeProp(
    MySimplePropertiesSimpleQualsClass* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimeProp)->value = x;
    ((MI_DatetimeField*)&self->datetimeProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesSimpleQualsClass_Clear_datetimeProp(
    MySimplePropertiesSimpleQualsClass* self)
{
    memset((void*)&self->datetimeProp, 0, sizeof(self->datetimeProp));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimplePropertiesSimpleQualsClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimplePropertiesSimpleQualsClass_Self MySimplePropertiesSimpleQualsClass_Self;

MI_EXTERN_C void MI_CALL MySimplePropertiesSimpleQualsClass_Load(
    MySimplePropertiesSimpleQualsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimplePropertiesSimpleQualsClass_Unload(
    MySimplePropertiesSimpleQualsClass_Self* self,
    MI_Context* context);


#endif /* _MySimplePropertiesSimpleQualsClass_h */
