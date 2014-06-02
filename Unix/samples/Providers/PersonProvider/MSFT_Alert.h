/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Alert_h
#define _MSFT_Alert_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_Alert [MSFT_Alert]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_Alert
{
    MI_Instance __instance;
    /* MSFT_Alert properties */
    MI_ConstStringField Message;
}
MSFT_Alert;

typedef struct _MSFT_Alert_Ref
{
    MSFT_Alert* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Alert_Ref;

typedef struct _MSFT_Alert_ConstRef
{
    MI_CONST MSFT_Alert* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Alert_ConstRef;

typedef struct _MSFT_Alert_Array
{
    struct _MSFT_Alert** data;
    MI_Uint32 size;
}
MSFT_Alert_Array;

typedef struct _MSFT_Alert_ConstArray
{
    struct _MSFT_Alert MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Alert_ConstArray;

typedef struct _MSFT_Alert_ArrayRef
{
    MSFT_Alert_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Alert_ArrayRef;

typedef struct _MSFT_Alert_ConstArrayRef
{
    MSFT_Alert_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Alert_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Alert_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Alert_Construct(
    MSFT_Alert* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Alert_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Clone(
    const MSFT_Alert* self,
    MSFT_Alert** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Alert_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Alert_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Destruct(MSFT_Alert* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Delete(MSFT_Alert* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Post(
    const MSFT_Alert* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Set_Message(
    MSFT_Alert* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_SetPtr_Message(
    MSFT_Alert* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Alert_Clear_Message(
    MSFT_Alert* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MSFT_Alert provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_Alert_Self MSFT_Alert_Self;

MI_EXTERN_C void MI_CALL MSFT_Alert_Load(
    MSFT_Alert_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Alert_Unload(
    MSFT_Alert_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Alert_EnableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL MSFT_Alert_DisableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL MSFT_Alert_Subscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL MSFT_Alert_Unsubscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


#endif /* _MSFT_Alert_h */
