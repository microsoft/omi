/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_BaseAddressFamily_h
#define _MSFT_BaseAddressFamily_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_BaseAddressFamily [MSFT_BaseAddressFamily]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_BaseAddressFamily
{
    MI_Instance __instance;
    /* MSFT_BaseAddressFamily properties */
    MI_ConstBooleanField IsSoftReconfigurationInbound;
}
MSFT_BaseAddressFamily;

typedef struct _MSFT_BaseAddressFamily_Ref
{
    MSFT_BaseAddressFamily* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseAddressFamily_Ref;

typedef struct _MSFT_BaseAddressFamily_ConstRef
{
    MI_CONST MSFT_BaseAddressFamily* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseAddressFamily_ConstRef;

typedef struct _MSFT_BaseAddressFamily_Array
{
    struct _MSFT_BaseAddressFamily** data;
    MI_Uint32 size;
}
MSFT_BaseAddressFamily_Array;

typedef struct _MSFT_BaseAddressFamily_ConstArray
{
    struct _MSFT_BaseAddressFamily MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_BaseAddressFamily_ConstArray;

typedef struct _MSFT_BaseAddressFamily_ArrayRef
{
    MSFT_BaseAddressFamily_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseAddressFamily_ArrayRef;

typedef struct _MSFT_BaseAddressFamily_ConstArrayRef
{
    MSFT_BaseAddressFamily_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BaseAddressFamily_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_BaseAddressFamily_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Construct(
    _Out_ MSFT_BaseAddressFamily* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_BaseAddressFamily_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Clone(
    _In_ const MSFT_BaseAddressFamily* self,
    _Outptr_ MSFT_BaseAddressFamily** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_BaseAddressFamily_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_BaseAddressFamily_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Destruct(_Inout_ MSFT_BaseAddressFamily* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Delete(_Inout_ MSFT_BaseAddressFamily* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Post(
    _In_ const MSFT_BaseAddressFamily* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Set_IsSoftReconfigurationInbound(
    _Inout_ MSFT_BaseAddressFamily* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsSoftReconfigurationInbound)->value = x;
    ((MI_BooleanField*)&self->IsSoftReconfigurationInbound)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BaseAddressFamily_Clear_IsSoftReconfigurationInbound(
    _Inout_ MSFT_BaseAddressFamily* self)
{
    memset((void*)&self->IsSoftReconfigurationInbound, 0, sizeof(self->IsSoftReconfigurationInbound));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_BaseAddressFamily provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_BaseAddressFamily_Self MSFT_BaseAddressFamily_Self;

MI_EXTERN_C void MI_CALL MSFT_BaseAddressFamily_Load(
    _Outptr_result_maybenull_ MSFT_BaseAddressFamily_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BaseAddressFamily_Unload(
    _In_opt_ MSFT_BaseAddressFamily_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_BaseAddressFamily_h */
