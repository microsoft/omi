/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_NeighborTemplate_h
#define _MSFT_NeighborTemplate_h

#include <MI.h>
#include "MSFT_AutonomousSystemSettingData.h"

/*
**==============================================================================
**
** MSFT_NeighborTemplate [MSFT_NeighborTemplate]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MSFT_NeighborTemplate /* extends MSFT_AutonomousSystemSettingData */
{
    MI_Instance __instance;
    /* MSFT_AutonomousSystemSettingData properties */
    MI_ConstUint32Field ASNumber;
    /* MSFT_NeighborTemplate properties */
    MI_ConstStringField RouteMap;
    MI_ConstStringField Password;
    MI_ConstUint32Field KeyEncryptionMethod;
}
MSFT_NeighborTemplate;

typedef struct _MSFT_NeighborTemplate_Ref
{
    MSFT_NeighborTemplate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NeighborTemplate_Ref;

typedef struct _MSFT_NeighborTemplate_ConstRef
{
    MI_CONST MSFT_NeighborTemplate* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NeighborTemplate_ConstRef;

typedef struct _MSFT_NeighborTemplate_Array
{
    struct _MSFT_NeighborTemplate** data;
    MI_Uint32 size;
}
MSFT_NeighborTemplate_Array;

typedef struct _MSFT_NeighborTemplate_ConstArray
{
    struct _MSFT_NeighborTemplate MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_NeighborTemplate_ConstArray;

typedef struct _MSFT_NeighborTemplate_ArrayRef
{
    MSFT_NeighborTemplate_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NeighborTemplate_ArrayRef;

typedef struct _MSFT_NeighborTemplate_ConstArrayRef
{
    MSFT_NeighborTemplate_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NeighborTemplate_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_NeighborTemplate_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Construct(
    _Out_ MSFT_NeighborTemplate* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_NeighborTemplate_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Clone(
    _In_ const MSFT_NeighborTemplate* self,
    _Outptr_ MSFT_NeighborTemplate** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_NeighborTemplate_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_NeighborTemplate_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Destruct(_Inout_ MSFT_NeighborTemplate* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Delete(_Inout_ MSFT_NeighborTemplate* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Post(
    _In_ const MSFT_NeighborTemplate* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Set_ASNumber(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ASNumber)->value = x;
    ((MI_Uint32Field*)&self->ASNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Clear_ASNumber(
    _Inout_ MSFT_NeighborTemplate* self)
{
    memset((void*)&self->ASNumber, 0, sizeof(self->ASNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Set_RouteMap(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_SetPtr_RouteMap(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Clear_RouteMap(
    _Inout_ MSFT_NeighborTemplate* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Set_Password(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_SetPtr_Password(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Clear_Password(
    _Inout_ MSFT_NeighborTemplate* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Set_KeyEncryptionMethod(
    _Inout_ MSFT_NeighborTemplate* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->KeyEncryptionMethod)->value = x;
    ((MI_Uint32Field*)&self->KeyEncryptionMethod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NeighborTemplate_Clear_KeyEncryptionMethod(
    _Inout_ MSFT_NeighborTemplate* self)
{
    memset((void*)&self->KeyEncryptionMethod, 0, sizeof(self->KeyEncryptionMethod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_NeighborTemplate provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_NeighborTemplate_Self MSFT_NeighborTemplate_Self;

MI_EXTERN_C void MI_CALL MSFT_NeighborTemplate_Load(
    _Outptr_result_maybenull_ MSFT_NeighborTemplate_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_NeighborTemplate_Unload(
    _In_opt_ MSFT_NeighborTemplate_Self* self,
    _In_ MI_Context* context);


#endif /* _MSFT_NeighborTemplate_h */
