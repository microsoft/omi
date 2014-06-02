/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Base_h
#define _Base_h

#include <MI.h>
#include "Root.h"
#include "Separate.h"
#include "Base.h"

/*
**==============================================================================
**
** Base [Base]
**
** Keys:
**
**==============================================================================
*/

struct _Base;

typedef struct _Base_Ref
{
    struct _Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_Ref;

typedef struct _Base_ConstRef
{
    MI_CONST struct _Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ConstRef;

typedef struct _Base_Array
{
    struct _Base** data;
    MI_Uint32 size;
}
Base_Array;

typedef struct _Base_ConstArray
{
    struct _Base MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Base_ConstArray;

typedef struct _Base_ArrayRef
{
    Base_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ArrayRef;

typedef struct _Base_ConstArrayRef
{
    Base_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Base_ConstArrayRef;

typedef struct _Base /* extends Root */
{
    MI_Instance __instance;
    /* Root properties */
    MI_ConstUint32Field Uint32Property;
    /* Base properties */
    Separate_ConstRef SeparateReference;
    Base_ConstRef BaseInstance;
    Base_ConstArrayRef BaseInstanceArray;
    Root_ConstRef RootReference;
}
Base;

MI_EXTERN_C MI_CONST MI_ClassDecl Base_rtti;

MI_INLINE MI_Result MI_CALL Base_Construct(
    _Out_ Base* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &Base_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Clone(
    _In_ const Base* self,
    _Outptr_ Base** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Base_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Base_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Base_Destruct(_Inout_ Base* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Delete(_Inout_ Base* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Base_Post(
    _In_ const Base* self,
    _In_ MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    _In_z_ const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context,
        &self->__instance,
        subscriptionIDCount,
        bookmark);
}

MI_INLINE MI_Result MI_CALL Base_Set_Uint32Property(
    _Inout_ Base* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Uint32Property)->value = x;
    ((MI_Uint32Field*)&self->Uint32Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Clear_Uint32Property(
    _Inout_ Base* self)
{
    memset((void*)&self->Uint32Property, 0, sizeof(self->Uint32Property));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Base_Set_SeparateReference(
    _Inout_ Base* self,
    _In_ const Separate* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Base_SetPtr_SeparateReference(
    _Inout_ Base* self,
    _In_ const Separate* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Base_Clear_SeparateReference(
    _Inout_ Base* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Base_Set_BaseInstance(
    _Inout_ Base* self,
    _In_ const Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Base_SetPtr_BaseInstance(
    _Inout_ Base* self,
    _In_ const Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Base_Clear_BaseInstance(
    _Inout_ Base* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Base_Set_BaseInstanceArray(
    _Inout_ Base* self,
    _In_reads_opt_(size) const Base * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL Base_SetPtr_BaseInstanceArray(
    _Inout_ Base* self,
    _In_reads_opt_(size) const Base * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Base_Clear_BaseInstanceArray(
    _Inout_ Base* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Base_Set_RootReference(
    _Inout_ Base* self,
    _In_ const Root* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Base_SetPtr_RootReference(
    _Inout_ Base* self,
    _In_ const Root* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Base_Clear_RootReference(
    _Inout_ Base* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}


#endif /* _Base_h */
