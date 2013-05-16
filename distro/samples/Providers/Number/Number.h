/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Number_h
#define _Number_h

#include <MI.h>

/*
**==============================================================================
**
** Number [XYZ_Number]
**
** Keys:
**    Number
**
**==============================================================================
*/

typedef struct _Number
{
    MI_Instance __instance;
    /* Number properties */
    MI_ConstStringField Description;
    /*KEY*/ MI_ConstUint32Field Number;
    MI_ConstStringField NumberString;
}
Number;

typedef struct _Number_Ref
{
    Number* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Number_Ref;

typedef struct _Number_ConstRef
{
    MI_CONST Number* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Number_ConstRef;

typedef struct _Number_Array
{
    struct _Number** data;
    MI_Uint32 size;
}
Number_Array;

typedef struct _Number_ConstArray
{
    struct _Number MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Number_ConstArray;

typedef struct _Number_ArrayRef
{
    Number_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Number_ArrayRef;

typedef struct _Number_ConstArrayRef
{
    Number_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Number_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Number_rtti;

MI_INLINE MI_Result MI_CALL Number_Construct(
    Number* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Number_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Number_Clone(
    const Number* self,
    Number** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Number_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Number_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Number_Destruct(Number* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Number_Delete(Number* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Number_Post(
    const Number* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Number_Set_Description(
    Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Number_SetPtr_Description(
    Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Number_Clear_Description(
    Number* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Number_Set_Number(
    Number* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Number)->value = x;
    ((MI_Uint32Field*)&self->Number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Number_Clear_Number(
    Number* self)
{
    memset((void*)&self->Number, 0, sizeof(self->Number));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Number_Set_NumberString(
    Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Number_SetPtr_NumberString(
    Number* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Number_Clear_NumberString(
    Number* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** Number provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Number_Self Number_Self;

MI_EXTERN_C void MI_CALL Number_Load(
    Number_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Number_Unload(
    Number_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Number_EnumerateInstances(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Number_GetInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Number_CreateInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* newInstance);

MI_EXTERN_C void MI_CALL Number_ModifyInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Number_DeleteInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* instanceName);


#endif /* _Number_h */
