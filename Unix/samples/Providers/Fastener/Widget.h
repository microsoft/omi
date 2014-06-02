/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Widget_h
#define _Widget_h

#include <MI.h>

/*
**==============================================================================
**
** Widget [MSFT_Widget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Widget
{
    MI_Instance __instance;
    /* Widget properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstReal32Field W1;
    MI_ConstReal32Field X1;
    MI_ConstReal32Field Y1;
    MI_ConstReal32Field Z1;
    MI_ConstReal64Field W2;
    MI_ConstReal64Field X2;
    MI_ConstReal64Field Y2;
    MI_ConstReal64Field Z2;
}
Widget;

typedef struct _Widget_Ref
{
    Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_Ref;

typedef struct _Widget_ConstRef
{
    MI_CONST Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstRef;

typedef struct _Widget_Array
{
    struct _Widget** data;
    MI_Uint32 size;
}
Widget_Array;

typedef struct _Widget_ConstArray
{
    struct _Widget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Widget_ConstArray;

typedef struct _Widget_ArrayRef
{
    Widget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ArrayRef;

typedef struct _Widget_ConstArrayRef
{
    Widget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Widget_rtti;

MI_INLINE MI_Result MI_CALL Widget_Construct(
    Widget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Widget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Clone(
    const Widget* self,
    Widget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Widget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Widget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Widget_Destruct(Widget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Delete(Widget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Post(
    const Widget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Set_Key(
    Widget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Key(
    Widget* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_W1(
    Widget* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->W1)->value = x;
    ((MI_Real32Field*)&self->W1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_W1(
    Widget* self)
{
    memset((void*)&self->W1, 0, sizeof(self->W1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_X1(
    Widget* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->X1)->value = x;
    ((MI_Real32Field*)&self->X1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_X1(
    Widget* self)
{
    memset((void*)&self->X1, 0, sizeof(self->X1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Y1(
    Widget* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Y1)->value = x;
    ((MI_Real32Field*)&self->Y1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Y1(
    Widget* self)
{
    memset((void*)&self->Y1, 0, sizeof(self->Y1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Z1(
    Widget* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Z1)->value = x;
    ((MI_Real32Field*)&self->Z1)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Z1(
    Widget* self)
{
    memset((void*)&self->Z1, 0, sizeof(self->Z1));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_W2(
    Widget* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->W2)->value = x;
    ((MI_Real64Field*)&self->W2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_W2(
    Widget* self)
{
    memset((void*)&self->W2, 0, sizeof(self->W2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_X2(
    Widget* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->X2)->value = x;
    ((MI_Real64Field*)&self->X2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_X2(
    Widget* self)
{
    memset((void*)&self->X2, 0, sizeof(self->X2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Y2(
    Widget* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->Y2)->value = x;
    ((MI_Real64Field*)&self->Y2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Y2(
    Widget* self)
{
    memset((void*)&self->Y2, 0, sizeof(self->Y2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Z2(
    Widget* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->Z2)->value = x;
    ((MI_Real64Field*)&self->Z2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Z2(
    Widget* self)
{
    memset((void*)&self->Z2, 0, sizeof(self->Z2));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Widget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Widget_Self Widget_Self;

MI_EXTERN_C void MI_CALL Widget_Load(
    Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Widget_Unload(
    Widget_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Widget_EnumerateInstances(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Widget_GetInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Widget_CreateInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* newInstance);

MI_EXTERN_C void MI_CALL Widget_ModifyInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Widget_DeleteInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName);


#endif /* _Widget_h */
