/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _President_h
#define _President_h

#include <MI.h>

/*
**==============================================================================
**
** President [MSFT_President]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _President
{
    MI_Instance __instance;
    /* President properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstStringField First;
    MI_ConstStringField Last;
}
President;

typedef struct _President_Ref
{
    President* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
President_Ref;

typedef struct _President_ConstRef
{
    MI_CONST President* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
President_ConstRef;

typedef struct _President_Array
{
    struct _President** data;
    MI_Uint32 size;
}
President_Array;

typedef struct _President_ConstArray
{
    struct _President MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
President_ConstArray;

typedef struct _President_ArrayRef
{
    President_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
President_ArrayRef;

typedef struct _President_ConstArrayRef
{
    President_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
President_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl President_rtti;

MI_INLINE MI_Result MI_CALL President_Construct(
    President* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &President_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL President_Clone(
    const President* self,
    President** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL President_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &President_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL President_Destruct(President* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL President_Delete(President* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL President_Post(
    const President* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL President_Set_Key(
    President* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL President_Clear_Key(
    President* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL President_Set_First(
    President* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL President_SetPtr_First(
    President* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL President_Clear_First(
    President* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL President_Set_Last(
    President* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL President_SetPtr_Last(
    President* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL President_Clear_Last(
    President* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** President provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _President_Self President_Self;

MI_EXTERN_C void MI_CALL President_Load(
    President_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL President_Unload(
    President_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL President_EnumerateInstances(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL President_GetInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL President_CreateInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* newInstance);

MI_EXTERN_C void MI_CALL President_ModifyInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL President_DeleteInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* instanceName);


#endif /* _President_h */
