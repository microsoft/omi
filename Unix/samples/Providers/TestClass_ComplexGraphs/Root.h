/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Root_h
#define _Root_h

#include <MI.h>

/*
**==============================================================================
**
** Root [Root]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Root
{
    MI_Instance __instance;
    /* Root properties */
    MI_ConstUint32Field Uint32Property;
}
Root;

typedef struct _Root_Ref
{
    Root* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Root_Ref;

typedef struct _Root_ConstRef
{
    MI_CONST Root* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Root_ConstRef;

typedef struct _Root_Array
{
    struct _Root** data;
    MI_Uint32 size;
}
Root_Array;

typedef struct _Root_ConstArray
{
    struct _Root MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Root_ConstArray;

typedef struct _Root_ArrayRef
{
    Root_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Root_ArrayRef;

typedef struct _Root_ConstArrayRef
{
    Root_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Root_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Root_rtti;

MI_INLINE MI_Result MI_CALL Root_Construct(
    _Out_ Root* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &Root_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Root_Clone(
    _In_ const Root* self,
    _Outptr_ Root** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Root_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Root_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Root_Destruct(_Inout_ Root* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Root_Delete(_Inout_ Root* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Root_Post(
    _In_ const Root* self,
    _In_ MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    _In_z_ const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context,
        &self->__instance,
        subscriptionIDCount,
        bookmark);
}

MI_INLINE MI_Result MI_CALL Root_Set_Uint32Property(
    _Inout_ Root* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Uint32Property)->value = x;
    ((MI_Uint32Field*)&self->Uint32Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Root_Clear_Uint32Property(
    _Inout_ Root* self)
{
    memset((void*)&self->Uint32Property, 0, sizeof(self->Uint32Property));
    return MI_RESULT_OK;
}


#endif /* _Root_h */
