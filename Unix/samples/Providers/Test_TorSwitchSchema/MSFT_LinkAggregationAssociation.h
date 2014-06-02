/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_LinkAggregationAssociation_h
#define _MSFT_LinkAggregationAssociation_h

#include <MI.h>
#include "CIM_EthernetPort.h"

/*
**==============================================================================
**
** MSFT_LinkAggregationAssociation [MSFT_LinkAggregationAssociation]
**
** Keys:
**    LinkAggregation
**    EthernetPorts
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregationAssociation
{
    MI_Instance __instance;
    /* MSFT_LinkAggregationAssociation properties */
    /*KEY*/ CIM_EthernetPort_ConstRef LinkAggregation;
    /*KEY*/ CIM_EthernetPort_ConstRef EthernetPorts;
}
MSFT_LinkAggregationAssociation;

typedef struct _MSFT_LinkAggregationAssociation_Ref
{
    MSFT_LinkAggregationAssociation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationAssociation_Ref;

typedef struct _MSFT_LinkAggregationAssociation_ConstRef
{
    MI_CONST MSFT_LinkAggregationAssociation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationAssociation_ConstRef;

typedef struct _MSFT_LinkAggregationAssociation_Array
{
    struct _MSFT_LinkAggregationAssociation** data;
    MI_Uint32 size;
}
MSFT_LinkAggregationAssociation_Array;

typedef struct _MSFT_LinkAggregationAssociation_ConstArray
{
    struct _MSFT_LinkAggregationAssociation MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_LinkAggregationAssociation_ConstArray;

typedef struct _MSFT_LinkAggregationAssociation_ArrayRef
{
    MSFT_LinkAggregationAssociation_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationAssociation_ArrayRef;

typedef struct _MSFT_LinkAggregationAssociation_ConstArrayRef
{
    MSFT_LinkAggregationAssociation_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregationAssociation_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_LinkAggregationAssociation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Construct(
    _Out_ MSFT_LinkAggregationAssociation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_LinkAggregationAssociation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Clone(
    _In_ const MSFT_LinkAggregationAssociation* self,
    _Outptr_ MSFT_LinkAggregationAssociation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_LinkAggregationAssociation_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_LinkAggregationAssociation_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Destruct(_Inout_ MSFT_LinkAggregationAssociation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Delete(_Inout_ MSFT_LinkAggregationAssociation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Post(
    _In_ const MSFT_LinkAggregationAssociation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Set_LinkAggregation(
    _Inout_ MSFT_LinkAggregationAssociation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_SetPtr_LinkAggregation(
    _Inout_ MSFT_LinkAggregationAssociation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Clear_LinkAggregation(
    _Inout_ MSFT_LinkAggregationAssociation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Set_EthernetPorts(
    _Inout_ MSFT_LinkAggregationAssociation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_SetPtr_EthernetPorts(
    _Inout_ MSFT_LinkAggregationAssociation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregationAssociation_Clear_EthernetPorts(
    _Inout_ MSFT_LinkAggregationAssociation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_LinkAggregationAssociation provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_LinkAggregationAssociation_Self MSFT_LinkAggregationAssociation_Self;

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_Load(
    _Outptr_result_maybenull_ MSFT_LinkAggregationAssociation_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_Unload(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_EnumerateInstances(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_GetInstance(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationAssociation* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_CreateInstance(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationAssociation* newInstance);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_ModifyInstance(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationAssociation* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_DeleteInstance(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregationAssociation* instanceName);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_AssociatorInstancesLinkAggregation(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EthernetPort* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_AssociatorInstancesEthernetPorts(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EthernetPort* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_ReferenceInstancesLinkAggregation(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EthernetPort* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregationAssociation_ReferenceInstancesEthernetPorts(
    _In_opt_ MSFT_LinkAggregationAssociation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EthernetPort* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_LinkAggregationAssociation_h */
