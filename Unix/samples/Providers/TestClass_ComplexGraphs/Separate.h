/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Separate_h
#define _Separate_h

#include <MI.h>

/*
**==============================================================================
**
** Separate [Separate]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Separate
{
    MI_Instance __instance;
    /* Separate properties */
    MI_ConstBooleanField BooleanProperty;
}
Separate;

typedef struct _Separate_Ref
{
    Separate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Separate_Ref;

typedef struct _Separate_ConstRef
{
    MI_CONST Separate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Separate_ConstRef;

typedef struct _Separate_Array
{
    struct _Separate** data;
    MI_Uint32 size;
}
Separate_Array;

typedef struct _Separate_ConstArray
{
    struct _Separate MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Separate_ConstArray;

typedef struct _Separate_ArrayRef
{
    Separate_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Separate_ArrayRef;

typedef struct _Separate_ConstArrayRef
{
    Separate_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Separate_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Separate_rtti;

MI_INLINE MI_Result MI_CALL Separate_Construct(
    _Out_ Separate* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &Separate_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Separate_Clone(
    _In_ const Separate* self,
    _Outptr_ Separate** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Separate_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Separate_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Separate_Destruct(_Inout_ Separate* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Separate_Delete(_Inout_ Separate* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Separate_Post(
    _In_ const Separate* self,
    _In_ MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    _In_z_ const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context,
        &self->__instance,
        subscriptionIDCount,
        bookmark);
}

MI_INLINE MI_Result MI_CALL Separate_Set_BooleanProperty(
    _Inout_ Separate* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->BooleanProperty)->value = x;
    ((MI_BooleanField*)&self->BooleanProperty)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Separate_Clear_BooleanProperty(
    _Inout_ Separate* self)
{
    memset((void*)&self->BooleanProperty, 0, sizeof(self->BooleanProperty));
    return MI_RESULT_OK;
}


#endif /* _Separate_h */
