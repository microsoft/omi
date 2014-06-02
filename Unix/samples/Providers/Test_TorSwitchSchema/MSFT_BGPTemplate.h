/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_BGPTemplate_h
#define _MSFT_BGPTemplate_h

#include <MI.h>
#include "MSFT_AutonomousSystemSettingData.h"

/*
**==============================================================================
**
** MSFT_BGPTemplate [MSFT_BGPTemplate]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_BGPTemplate /* extends MSFT_AutonomousSystemSettingData */
{
    MI_Instance __instance;
    /* MSFT_AutonomousSystemSettingData properties */
    MI_ConstUint32Field ASNumber;
    /* MSFT_BGPTemplate properties */
    MI_ConstBooleanField LogNeighborChanges;
}
MSFT_BGPTemplate;

typedef struct _MSFT_BGPTemplate_Ref
{
    MSFT_BGPTemplate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPTemplate_Ref;

typedef struct _MSFT_BGPTemplate_ConstRef
{
    MI_CONST MSFT_BGPTemplate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPTemplate_ConstRef;

typedef struct _MSFT_BGPTemplate_Array
{
    struct _MSFT_BGPTemplate** data;
    MI_Uint32 size;
}
MSFT_BGPTemplate_Array;

typedef struct _MSFT_BGPTemplate_ConstArray
{
    struct _MSFT_BGPTemplate MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_BGPTemplate_ConstArray;

typedef struct _MSFT_BGPTemplate_ArrayRef
{
    MSFT_BGPTemplate_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPTemplate_ArrayRef;

typedef struct _MSFT_BGPTemplate_ConstArrayRef
{
    MSFT_BGPTemplate_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPTemplate_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_BGPTemplate_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Construct(
    _Out_ MSFT_BGPTemplate* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_BGPTemplate_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Clone(
    _In_ const MSFT_BGPTemplate* self,
    _Outptr_ MSFT_BGPTemplate** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_BGPTemplate_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_BGPTemplate_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Destruct(_Inout_ MSFT_BGPTemplate* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Delete(_Inout_ MSFT_BGPTemplate* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Post(
    _In_ const MSFT_BGPTemplate* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Set_ASNumber(
    _Inout_ MSFT_BGPTemplate* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ASNumber)->value = x;
    ((MI_Uint32Field*)&self->ASNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Clear_ASNumber(
    _Inout_ MSFT_BGPTemplate* self)
{
    memset((void*)&self->ASNumber, 0, sizeof(self->ASNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Set_LogNeighborChanges(
    _Inout_ MSFT_BGPTemplate* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->LogNeighborChanges)->value = x;
    ((MI_BooleanField*)&self->LogNeighborChanges)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPTemplate_Clear_LogNeighborChanges(
    _Inout_ MSFT_BGPTemplate* self)
{
    memset((void*)&self->LogNeighborChanges, 0, sizeof(self->LogNeighborChanges));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_BGPTemplate provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_BGPTemplate_Self MSFT_BGPTemplate_Self;

MI_EXTERN_C void MI_CALL MSFT_BGPTemplate_Load(
    _Outptr_result_maybenull_ MSFT_BGPTemplate_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BGPTemplate_Unload(
    _In_opt_ MSFT_BGPTemplate_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_BGPTemplate_h */
