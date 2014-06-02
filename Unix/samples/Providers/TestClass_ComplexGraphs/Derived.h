/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Derived_h
#define _Derived_h

#include <MI.h>
#include "Base.h"
#include "Separate.h"
#include "Root.h"
#include "Derived.h"

/*
**==============================================================================
**
** Derived [Derived]
**
** Keys:
**
**==============================================================================
*/

struct _Derived;

typedef struct _Derived_Ref
{
    struct _Derived* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_Ref;

typedef struct _Derived_ConstRef
{
    MI_CONST struct _Derived* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ConstRef;

typedef struct _Derived_Array
{
    struct _Derived** data;
    MI_Uint32 size;
}
Derived_Array;

typedef struct _Derived_ConstArray
{
    struct _Derived MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Derived_ConstArray;

typedef struct _Derived_ArrayRef
{
    Derived_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ArrayRef;

typedef struct _Derived /* extends Base */
{
    MI_Instance __instance;
    /* Root properties */
    MI_ConstUint32Field Uint32Property;
    /* Base properties */
    Separate_ConstRef SeparateReference;
    Base_ConstRef BaseInstance;
    Base_ConstArrayRef BaseInstanceArray;
    Root_ConstRef RootReference;
    /* Derived properties */
    MI_ConstStringField StringProperty;
    Derived_ConstRef DerivedInstance;
}
Derived;

typedef struct _Derived_ConstArrayRef
{
    Derived_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Derived_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Derived_rtti;

MI_INLINE MI_Result MI_CALL Derived_Construct(
    _Out_ Derived* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &Derived_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Clone(
    _In_ const Derived* self,
    _Outptr_ Derived** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Derived_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Derived_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Derived_Destruct(_Inout_ Derived* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Delete(_Inout_ Derived* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Derived_Post(
    _In_ const Derived* self,
    _In_ MI_Context* context,
    MI_Uint32 subscriptionIDCount,
    _In_z_ const MI_Char* bookmark)
{
    return MI_Context_PostIndication(context,
        &self->__instance,
        subscriptionIDCount,
        bookmark);
}

MI_INLINE MI_Result MI_CALL Derived_Set_Uint32Property(
    _Inout_ Derived* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Uint32Property)->value = x;
    ((MI_Uint32Field*)&self->Uint32Property)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Clear_Uint32Property(
    _Inout_ Derived* self)
{
    memset((void*)&self->Uint32Property, 0, sizeof(self->Uint32Property));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Derived_Set_SeparateReference(
    _Inout_ Derived* self,
    _In_ const Separate* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Derived_SetPtr_SeparateReference(
    _Inout_ Derived* self,
    _In_ const Separate* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Derived_Clear_SeparateReference(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Derived_Set_BaseInstance(
    _Inout_ Derived* self,
    _In_ const Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Derived_SetPtr_BaseInstance(
    _Inout_ Derived* self,
    _In_ const Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Derived_Clear_BaseInstance(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Derived_Set_BaseInstanceArray(
    _Inout_ Derived* self,
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

MI_INLINE MI_Result MI_CALL Derived_SetPtr_BaseInstanceArray(
    _Inout_ Derived* self,
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

MI_INLINE MI_Result MI_CALL Derived_Clear_BaseInstanceArray(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Derived_Set_RootReference(
    _Inout_ Derived* self,
    _In_ const Root* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Derived_SetPtr_RootReference(
    _Inout_ Derived* self,
    _In_ const Root* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Derived_Clear_RootReference(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Derived_Set_StringProperty(
    _Inout_ Derived* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Derived_SetPtr_StringProperty(
    _Inout_ Derived* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Derived_Clear_StringProperty(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL Derived_Set_DerivedInstance(
    _Inout_ Derived* self,
    _In_ const Derived* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL Derived_SetPtr_DerivedInstance(
    _Inout_ Derived* self,
    _In_ const Derived* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Derived_Clear_DerivedInstance(
    _Inout_ Derived* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}


#endif /* _Derived_h */
