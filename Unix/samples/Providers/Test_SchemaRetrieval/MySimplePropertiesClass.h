/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimplePropertiesClass_h
#define _MySimplePropertiesClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimplePropertiesClass [MySimplePropertiesClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimplePropertiesClass
{
    MI_Instance __instance;
    /* MySimplePropertiesClass properties */
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
MySimplePropertiesClass;

typedef struct _MySimplePropertiesClass_Ref
{
    MySimplePropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesClass_Ref;

typedef struct _MySimplePropertiesClass_ConstRef
{
    MI_CONST MySimplePropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesClass_ConstRef;

typedef struct _MySimplePropertiesClass_Array
{
    struct _MySimplePropertiesClass** data;
    MI_Uint32 size;
}
MySimplePropertiesClass_Array;

typedef struct _MySimplePropertiesClass_ConstArray
{
    struct _MySimplePropertiesClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimplePropertiesClass_ConstArray;

typedef struct _MySimplePropertiesClass_ArrayRef
{
    MySimplePropertiesClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesClass_ArrayRef;

typedef struct _MySimplePropertiesClass_ConstArrayRef
{
    MySimplePropertiesClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimplePropertiesClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimplePropertiesClass_rtti;

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Construct(
    MySimplePropertiesClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimplePropertiesClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clone(
    const MySimplePropertiesClass* self,
    MySimplePropertiesClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimplePropertiesClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimplePropertiesClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Destruct(MySimplePropertiesClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Delete(MySimplePropertiesClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Post(
    const MySimplePropertiesClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_booleanProp(
    MySimplePropertiesClass* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->booleanProp)->value = x;
    ((MI_BooleanField*)&self->booleanProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_booleanProp(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->booleanProp, 0, sizeof(self->booleanProp));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_stringProp(
    MySimplePropertiesClass* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_SetPtr_stringProp(
    MySimplePropertiesClass* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_stringProp(
    MySimplePropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_char16Prop(
    MySimplePropertiesClass* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->char16Prop)->value = x;
    ((MI_Char16Field*)&self->char16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_char16Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->char16Prop, 0, sizeof(self->char16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_uint8Prop(
    MySimplePropertiesClass* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->uint8Prop)->value = x;
    ((MI_Uint8Field*)&self->uint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_uint8Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->uint8Prop, 0, sizeof(self->uint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_sint8Prop(
    MySimplePropertiesClass* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->sint8Prop)->value = x;
    ((MI_Sint8Field*)&self->sint8Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_sint8Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->sint8Prop, 0, sizeof(self->sint8Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_uint16Prop(
    MySimplePropertiesClass* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->uint16Prop)->value = x;
    ((MI_Uint16Field*)&self->uint16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_uint16Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->uint16Prop, 0, sizeof(self->uint16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_sint16Prop(
    MySimplePropertiesClass* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->sint16Prop)->value = x;
    ((MI_Sint16Field*)&self->sint16Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_sint16Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->sint16Prop, 0, sizeof(self->sint16Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_uint32Prop(
    MySimplePropertiesClass* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->uint32Prop)->value = x;
    ((MI_Uint32Field*)&self->uint32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_uint32Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->uint32Prop, 0, sizeof(self->uint32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_sint32Prop(
    MySimplePropertiesClass* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->sint32Prop)->value = x;
    ((MI_Sint32Field*)&self->sint32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_sint32Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->sint32Prop, 0, sizeof(self->sint32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_uint64Prop(
    MySimplePropertiesClass* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->uint64Prop)->value = x;
    ((MI_Uint64Field*)&self->uint64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_uint64Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->uint64Prop, 0, sizeof(self->uint64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_sint64Prop(
    MySimplePropertiesClass* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Prop)->value = x;
    ((MI_Sint64Field*)&self->sint64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_sint64Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->sint64Prop, 0, sizeof(self->sint64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_real32Prop(
    MySimplePropertiesClass* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->real32Prop)->value = x;
    ((MI_Real32Field*)&self->real32Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_real32Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->real32Prop, 0, sizeof(self->real32Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_real64Prop(
    MySimplePropertiesClass* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->real64Prop)->value = x;
    ((MI_Real64Field*)&self->real64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_real64Prop(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->real64Prop, 0, sizeof(self->real64Prop));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Set_datetimeProp(
    MySimplePropertiesClass* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->datetimeProp)->value = x;
    ((MI_DatetimeField*)&self->datetimeProp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySimplePropertiesClass_Clear_datetimeProp(
    MySimplePropertiesClass* self)
{
    memset((void*)&self->datetimeProp, 0, sizeof(self->datetimeProp));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySimplePropertiesClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimplePropertiesClass_Self MySimplePropertiesClass_Self;

MI_EXTERN_C void MI_CALL MySimplePropertiesClass_Load(
    MySimplePropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimplePropertiesClass_Unload(
    MySimplePropertiesClass_Self* self,
    MI_Context* context);


#endif /* _MySimplePropertiesClass_h */
