/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AutonomousSystemSettingData_h
#define _MSFT_AutonomousSystemSettingData_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_AutonomousSystemSettingData [MSFT_AutonomousSystemSettingData]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_AutonomousSystemSettingData
{
    MI_Instance __instance;
    /* MSFT_AutonomousSystemSettingData properties */
    MI_ConstUint32Field ASNumber;
}
MSFT_AutonomousSystemSettingData;

typedef struct _MSFT_AutonomousSystemSettingData_Ref
{
    MSFT_AutonomousSystemSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AutonomousSystemSettingData_Ref;

typedef struct _MSFT_AutonomousSystemSettingData_ConstRef
{
    MI_CONST MSFT_AutonomousSystemSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AutonomousSystemSettingData_ConstRef;

typedef struct _MSFT_AutonomousSystemSettingData_Array
{
    struct _MSFT_AutonomousSystemSettingData** data;
    MI_Uint32 size;
}
MSFT_AutonomousSystemSettingData_Array;

typedef struct _MSFT_AutonomousSystemSettingData_ConstArray
{
    struct _MSFT_AutonomousSystemSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AutonomousSystemSettingData_ConstArray;

typedef struct _MSFT_AutonomousSystemSettingData_ArrayRef
{
    MSFT_AutonomousSystemSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AutonomousSystemSettingData_ArrayRef;

typedef struct _MSFT_AutonomousSystemSettingData_ConstArrayRef
{
    MSFT_AutonomousSystemSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AutonomousSystemSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AutonomousSystemSettingData_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Construct(
    _Out_ MSFT_AutonomousSystemSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AutonomousSystemSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Clone(
    _In_ const MSFT_AutonomousSystemSettingData* self,
    _Outptr_ MSFT_AutonomousSystemSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AutonomousSystemSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AutonomousSystemSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Destruct(_Inout_ MSFT_AutonomousSystemSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Delete(_Inout_ MSFT_AutonomousSystemSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Post(
    _In_ const MSFT_AutonomousSystemSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Set_ASNumber(
    _Inout_ MSFT_AutonomousSystemSettingData* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ASNumber)->value = x;
    ((MI_Uint32Field*)&self->ASNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_AutonomousSystemSettingData_Clear_ASNumber(
    _Inout_ MSFT_AutonomousSystemSettingData* self)
{
    memset((void*)&self->ASNumber, 0, sizeof(self->ASNumber));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_AutonomousSystemSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AutonomousSystemSettingData_Self MSFT_AutonomousSystemSettingData_Self;

MI_EXTERN_C void MI_CALL MSFT_AutonomousSystemSettingData_Load(
    _Outptr_result_maybenull_ MSFT_AutonomousSystemSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AutonomousSystemSettingData_Unload(
    _In_opt_ MSFT_AutonomousSystemSettingData_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_AutonomousSystemSettingData_h */
