/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AddressFamilyIPv4_h
#define _MSFT_AddressFamilyIPv4_h

#include <MI.h>
#include "MSFT_BaseAddressFamily.h"

/*
**==============================================================================
**
** MSFT_AddressFamilyIPv4 [MSFT_AddressFamilyIPv4]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_AddressFamilyIPv4 /* extends MSFT_BaseAddressFamily */
{
    MI_Instance __instance;
    /* MSFT_BaseAddressFamily properties */
    MI_ConstBooleanField IsSoftReconfigurationInbound;
    /* MSFT_AddressFamilyIPv4 properties */
    MI_ConstUint32Field MaximumPaths;
}
MSFT_AddressFamilyIPv4;

typedef struct _MSFT_AddressFamilyIPv4_Ref
{
    MSFT_AddressFamilyIPv4* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyIPv4_Ref;

typedef struct _MSFT_AddressFamilyIPv4_ConstRef
{
    MI_CONST MSFT_AddressFamilyIPv4* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyIPv4_ConstRef;

typedef struct _MSFT_AddressFamilyIPv4_Array
{
    struct _MSFT_AddressFamilyIPv4** data;
    MI_Uint32 size;
}
MSFT_AddressFamilyIPv4_Array;

typedef struct _MSFT_AddressFamilyIPv4_ConstArray
{
    struct _MSFT_AddressFamilyIPv4 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AddressFamilyIPv4_ConstArray;

typedef struct _MSFT_AddressFamilyIPv4_ArrayRef
{
    MSFT_AddressFamilyIPv4_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyIPv4_ArrayRef;

typedef struct _MSFT_AddressFamilyIPv4_ConstArrayRef
{
    MSFT_AddressFamilyIPv4_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AddressFamilyIPv4_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AddressFamilyIPv4_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Construct(
    _Out_ MSFT_AddressFamilyIPv4* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AddressFamilyIPv4_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Clone(
    _In_ const MSFT_AddressFamilyIPv4* self,
    _Outptr_ MSFT_AddressFamilyIPv4** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AddressFamilyIPv4_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AddressFamilyIPv4_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Destruct(_Inout_ MSFT_AddressFamilyIPv4* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Delete(_Inout_ MSFT_AddressFamilyIPv4* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Post(
    _In_ const MSFT_AddressFamilyIPv4* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Set_IsSoftReconfigurationInbound(
    _Inout_ MSFT_AddressFamilyIPv4* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsSoftReconfigurationInbound)->value = x;
    ((MI_BooleanField*)&self->IsSoftReconfigurationInbound)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Clear_IsSoftReconfigurationInbound(
    _Inout_ MSFT_AddressFamilyIPv4* self)
{
    memset((void*)&self->IsSoftReconfigurationInbound, 0, sizeof(self->IsSoftReconfigurationInbound));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Set_MaximumPaths(
    _Inout_ MSFT_AddressFamilyIPv4* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaximumPaths)->value = x;
    ((MI_Uint32Field*)&self->MaximumPaths)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AddressFamilyIPv4_Clear_MaximumPaths(
    _Inout_ MSFT_AddressFamilyIPv4* self)
{
    memset((void*)&self->MaximumPaths, 0, sizeof(self->MaximumPaths));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_AddressFamilyIPv4 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AddressFamilyIPv4_Self MSFT_AddressFamilyIPv4_Self;

MI_EXTERN_C void MI_CALL MSFT_AddressFamilyIPv4_Load(
    _Outptr_result_maybenull_ MSFT_AddressFamilyIPv4_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AddressFamilyIPv4_Unload(
    _In_opt_ MSFT_AddressFamilyIPv4_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_AddressFamilyIPv4_h */
