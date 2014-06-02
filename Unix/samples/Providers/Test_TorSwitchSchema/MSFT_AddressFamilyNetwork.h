/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AddressFamilyNetwork_h
#define _MSFT_AddressFamilyNetwork_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_AddressFamilyNetwork [MSFT_AddressFamilyNetwork]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_AddressFamilyNetwork
{
    MI_Instance __instance;
    /* MSFT_AddressFamilyNetwork properties */
    MI_ConstStringField RouteMap;
}
MSFT_AddressFamilyNetwork;

typedef struct _MSFT_AddressFamilyNetwork_Ref
{
    MSFT_AddressFamilyNetwork* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyNetwork_Ref;

typedef struct _MSFT_AddressFamilyNetwork_ConstRef
{
    MI_CONST MSFT_AddressFamilyNetwork* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyNetwork_ConstRef;

typedef struct _MSFT_AddressFamilyNetwork_Array
{
    struct _MSFT_AddressFamilyNetwork** data;
    MI_Uint32 size;
}
MSFT_AddressFamilyNetwork_Array;

typedef struct _MSFT_AddressFamilyNetwork_ConstArray
{
    struct _MSFT_AddressFamilyNetwork MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AddressFamilyNetwork_ConstArray;

typedef struct _MSFT_AddressFamilyNetwork_ArrayRef
{
    MSFT_AddressFamilyNetwork_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyNetwork_ArrayRef;

typedef struct _MSFT_AddressFamilyNetwork_ConstArrayRef
{
    MSFT_AddressFamilyNetwork_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyNetwork_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AddressFamilyNetwork_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Construct(
    _Out_ MSFT_AddressFamilyNetwork* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AddressFamilyNetwork_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Clone(
    _In_ const MSFT_AddressFamilyNetwork* self,
    _Outptr_ MSFT_AddressFamilyNetwork** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AddressFamilyNetwork_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AddressFamilyNetwork_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Destruct(_Inout_ MSFT_AddressFamilyNetwork* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Delete(_Inout_ MSFT_AddressFamilyNetwork* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Post(
    _In_ const MSFT_AddressFamilyNetwork* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Set_RouteMap(
    _Inout_ MSFT_AddressFamilyNetwork* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_SetPtr_RouteMap(
    _Inout_ MSFT_AddressFamilyNetwork* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyNetwork_Clear_RouteMap(
    _Inout_ MSFT_AddressFamilyNetwork* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** MSFT_AddressFamilyNetwork provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AddressFamilyNetwork_Self MSFT_AddressFamilyNetwork_Self;

MI_EXTERN_C void MI_CALL MSFT_AddressFamilyNetwork_Load(
    _Outptr_result_maybenull_ MSFT_AddressFamilyNetwork_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AddressFamilyNetwork_Unload(
    _In_opt_ MSFT_AddressFamilyNetwork_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_AddressFamilyNetwork_h */
