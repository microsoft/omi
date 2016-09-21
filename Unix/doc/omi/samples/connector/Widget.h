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
** Widget [XYZ_Widget]
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
    MI_ConstUint32Field ModelNumber;
    MI_ConstStringField Color;
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

MI_INLINE MI_Result MI_CALL Widget_Set_ModelNumber(
    Widget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ModelNumber)->value = x;
    ((MI_Uint32Field*)&self->ModelNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_ModelNumber(
    Widget* self)
{
    memset((void*)&self->ModelNumber, 0, sizeof(self->ModelNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Color(
    Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_Color(
    Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Color(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
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
