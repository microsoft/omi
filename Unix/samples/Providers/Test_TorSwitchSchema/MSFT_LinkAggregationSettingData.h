/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_LinkAggregationSettingData_h
#define _MSFT_LinkAggregationSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** MSFT_LinkAggregationSettingData [MSFT_LinkAggregationSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregationSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* MSFT_LinkAggregationSettingData properties */
    MI_ConstUint16Field PortPriority;
    MI_ConstUint16Field GroupNumber;
    MI_ConstUint16Field Mode;
    MI_ConstBooleanField RateFastEnable;
}
MSFT_LinkAggregationSettingData;

typedef struct _MSFT_LinkAggregationSettingData_Ref
{
    MSFT_LinkAggregationSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationSettingData_Ref;

typedef struct _MSFT_LinkAggregationSettingData_ConstRef
{
    MI_CONST MSFT_LinkAggregationSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationSettingData_ConstRef;

typedef struct _MSFT_LinkAggregationSettingData_Array
{
    struct _MSFT_LinkAggregationSettingData** data;
    MI_Uint32 size;
}
MSFT_LinkAggregationSettingData_Array;

typedef struct _MSFT_LinkAggregationSettingData_ConstArray
{
    struct _MSFT_LinkAggregationSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_LinkAggregationSettingData_ConstArray;

typedef struct _MSFT_LinkAggregationSettingData_ArrayRef
{
    MSFT_LinkAggregationSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationSettingData_ArrayRef;

typedef struct _MSFT_LinkAggregationSettingData_ConstArrayRef
{
    MSFT_LinkAggregationSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_LinkAggregationSettingData_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Construct(
    _Out_ MSFT_LinkAggregationSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_LinkAggregationSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clone(
    _In_ const MSFT_LinkAggregationSettingData* self,
    _Outptr_ MSFT_LinkAggregationSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_LinkAggregationSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_LinkAggregationSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Destruct(_Inout_ MSFT_LinkAggregationSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Delete(_Inout_ MSFT_LinkAggregationSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Post(
    _In_ const MSFT_LinkAggregationSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_InstanceID(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_SetPtr_InstanceID(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_InstanceID(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_Caption(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_SetPtr_Caption(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_Caption(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_Description(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_SetPtr_Description(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_Description(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_ElementName(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_SetPtr_ElementName(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_ElementName(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_PortPriority(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortPriority)->value = x;
    ((MI_Uint16Field*)&self->PortPriority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_PortPriority(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    memset((void*)&self->PortPriority, 0, sizeof(self->PortPriority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_GroupNumber(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->GroupNumber)->value = x;
    ((MI_Uint16Field*)&self->GroupNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_GroupNumber(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    memset((void*)&self->GroupNumber, 0, sizeof(self->GroupNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_Mode(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Mode)->value = x;
    ((MI_Uint16Field*)&self->Mode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_Mode(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    memset((void*)&self->Mode, 0, sizeof(self->Mode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Set_RateFastEnable(
    _Inout_ MSFT_LinkAggregationSettingData* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RateFastEnable)->value = x;
    ((MI_BooleanField*)&self->RateFastEnable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationSettingData_Clear_RateFastEnable(
    _Inout_ MSFT_LinkAggregationSettingData* self)
{
    memset((void*)&self->RateFastEnable, 0, sizeof(self->RateFastEnable));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregationSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_LinkAggregationSettingData_Self MSFT_LinkAggregationSettingData_Self;

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_Load(
    _Outptr_result_maybenull_ MSFT_LinkAggregationSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_Unload(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_EnumerateInstances(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_GetInstance(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_CreateInstance(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationSettingData* newInstance);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_ModifyInstance(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationSettingData_DeleteInstance(
    _In_opt_ MSFT_LinkAggregationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationSettingData* instanceName);


#endif /* _MSFT_LinkAggregationSettingData_h */
