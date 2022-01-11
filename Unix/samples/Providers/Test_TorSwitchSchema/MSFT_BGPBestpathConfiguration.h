/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_BGPBestpathConfiguration_h
#define _MSFT_BGPBestpathConfiguration_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** MSFT_BGPBestpathConfiguration [MSFT_BGPBestpathConfiguration]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MSFT_BGPBestpathConfiguration /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* MSFT_BGPBestpathConfiguration properties */
    MI_ConstBooleanField IsAlwaysCompareMed;
    MI_ConstBooleanField ISAsPathMultiplePathRelax;
    MI_ConstBooleanField ISCompareRouteId;
    MI_ConstBooleanField IsCostCommunityIgnore;
    MI_ConstBooleanField IsMedConfed;
    MI_ConstBooleanField IsMedMissingAsWorst;
    MI_ConstBooleanField IsMedNonDeterministic;
}
MSFT_BGPBestpathConfiguration;

typedef struct _MSFT_BGPBestpathConfiguration_Ref
{
    MSFT_BGPBestpathConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPBestpathConfiguration_Ref;

typedef struct _MSFT_BGPBestpathConfiguration_ConstRef
{
    MI_CONST MSFT_BGPBestpathConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPBestpathConfiguration_ConstRef;

typedef struct _MSFT_BGPBestpathConfiguration_Array
{
    struct _MSFT_BGPBestpathConfiguration** data;
    MI_Uint32 size;
}
MSFT_BGPBestpathConfiguration_Array;

typedef struct _MSFT_BGPBestpathConfiguration_ConstArray
{
    struct _MSFT_BGPBestpathConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_BGPBestpathConfiguration_ConstArray;

typedef struct _MSFT_BGPBestpathConfiguration_ArrayRef
{
    MSFT_BGPBestpathConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPBestpathConfiguration_ArrayRef;

typedef struct _MSFT_BGPBestpathConfiguration_ConstArrayRef
{
    MSFT_BGPBestpathConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPBestpathConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_BGPBestpathConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Construct(
    _Out_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_BGPBestpathConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clone(
    _In_ const MSFT_BGPBestpathConfiguration* self,
    _Outptr_ MSFT_BGPBestpathConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_BGPBestpathConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_BGPBestpathConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Destruct(_Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Delete(_Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Post(
    _In_ const MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_InstanceID(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_SetPtr_InstanceID(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_InstanceID(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_Caption(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_SetPtr_Caption(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_Caption(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_Description(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_SetPtr_Description(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_Description(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_ElementName(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_SetPtr_ElementName(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_ElementName(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_IsAlwaysCompareMed(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsAlwaysCompareMed)->value = x;
    ((MI_BooleanField*)&self->IsAlwaysCompareMed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_IsAlwaysCompareMed(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->IsAlwaysCompareMed, 0, sizeof(self->IsAlwaysCompareMed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_ISAsPathMultiplePathRelax(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ISAsPathMultiplePathRelax)->value = x;
    ((MI_BooleanField*)&self->ISAsPathMultiplePathRelax)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_ISAsPathMultiplePathRelax(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->ISAsPathMultiplePathRelax, 0, sizeof(self->ISAsPathMultiplePathRelax));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_ISCompareRouteId(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ISCompareRouteId)->value = x;
    ((MI_BooleanField*)&self->ISCompareRouteId)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_ISCompareRouteId(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->ISCompareRouteId, 0, sizeof(self->ISCompareRouteId));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_IsCostCommunityIgnore(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsCostCommunityIgnore)->value = x;
    ((MI_BooleanField*)&self->IsCostCommunityIgnore)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_IsCostCommunityIgnore(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->IsCostCommunityIgnore, 0, sizeof(self->IsCostCommunityIgnore));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_IsMedConfed(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsMedConfed)->value = x;
    ((MI_BooleanField*)&self->IsMedConfed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_IsMedConfed(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->IsMedConfed, 0, sizeof(self->IsMedConfed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_IsMedMissingAsWorst(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsMedMissingAsWorst)->value = x;
    ((MI_BooleanField*)&self->IsMedMissingAsWorst)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_IsMedMissingAsWorst(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->IsMedMissingAsWorst, 0, sizeof(self->IsMedMissingAsWorst));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Set_IsMedNonDeterministic(
    _Inout_ MSFT_BGPBestpathConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsMedNonDeterministic)->value = x;
    ((MI_BooleanField*)&self->IsMedNonDeterministic)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPBestpathConfiguration_Clear_IsMedNonDeterministic(
    _Inout_ MSFT_BGPBestpathConfiguration* self)
{
    memset((void*)&self->IsMedNonDeterministic, 0, sizeof(self->IsMedNonDeterministic));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_BGPBestpathConfiguration provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_BGPBestpathConfiguration_Self MSFT_BGPBestpathConfiguration_Self;

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_Load(
    _Outptr_result_maybenull_ MSFT_BGPBestpathConfiguration_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_Unload(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_EnumerateInstances(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_GetInstance(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPBestpathConfiguration* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_CreateInstance(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPBestpathConfiguration* newInstance);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_ModifyInstance(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPBestpathConfiguration* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_BGPBestpathConfiguration_DeleteInstance(
    _In_opt_ MSFT_BGPBestpathConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPBestpathConfiguration* instanceName);


#endif /* _MSFT_BGPBestpathConfiguration_h */
