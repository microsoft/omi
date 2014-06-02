/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_BindsToLANEndpoint_h
#define _CIM_BindsToLANEndpoint_h

#include <MI.h>
#include "CIM_BindsTo.h"
#include "CIM_LANEndpoint.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_BindsToLANEndpoint [CIM_BindsToLANEndpoint]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_BindsToLANEndpoint /* extends CIM_BindsTo */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_LANEndpoint_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_SAPSAPDependency properties */
    /* CIM_BindsTo properties */
    /* CIM_BindsToLANEndpoint properties */
    MI_ConstUint16Field FrameType;
}
CIM_BindsToLANEndpoint;

typedef struct _CIM_BindsToLANEndpoint_Ref
{
    CIM_BindsToLANEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsToLANEndpoint_Ref;

typedef struct _CIM_BindsToLANEndpoint_ConstRef
{
    MI_CONST CIM_BindsToLANEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsToLANEndpoint_ConstRef;

typedef struct _CIM_BindsToLANEndpoint_Array
{
    struct _CIM_BindsToLANEndpoint** data;
    MI_Uint32 size;
}
CIM_BindsToLANEndpoint_Array;

typedef struct _CIM_BindsToLANEndpoint_ConstArray
{
    struct _CIM_BindsToLANEndpoint MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_BindsToLANEndpoint_ConstArray;

typedef struct _CIM_BindsToLANEndpoint_ArrayRef
{
    CIM_BindsToLANEndpoint_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsToLANEndpoint_ArrayRef;

typedef struct _CIM_BindsToLANEndpoint_ConstArrayRef
{
    CIM_BindsToLANEndpoint_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsToLANEndpoint_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_BindsToLANEndpoint_rtti;

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Construct(
    _Out_ CIM_BindsToLANEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_BindsToLANEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Clone(
    _In_ const CIM_BindsToLANEndpoint* self,
    _Outptr_ CIM_BindsToLANEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_BindsToLANEndpoint_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_BindsToLANEndpoint_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Destruct(_Inout_ CIM_BindsToLANEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Delete(_Inout_ CIM_BindsToLANEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Post(
    _In_ const CIM_BindsToLANEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Set_Antecedent(
    _Inout_ CIM_BindsToLANEndpoint* self,
    _In_ const CIM_LANEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_SetPtr_Antecedent(
    _Inout_ CIM_BindsToLANEndpoint* self,
    _In_ const CIM_LANEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Clear_Antecedent(
    _Inout_ CIM_BindsToLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Set_Dependent(
    _Inout_ CIM_BindsToLANEndpoint* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_SetPtr_Dependent(
    _Inout_ CIM_BindsToLANEndpoint* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Clear_Dependent(
    _Inout_ CIM_BindsToLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Set_FrameType(
    _Inout_ CIM_BindsToLANEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->FrameType)->value = x;
    ((MI_Uint16Field*)&self->FrameType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_BindsToLANEndpoint_Clear_FrameType(
    _Inout_ CIM_BindsToLANEndpoint* self)
{
    memset((void*)&self->FrameType, 0, sizeof(self->FrameType));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_BindsToLANEndpoint provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_BindsToLANEndpoint_Self CIM_BindsToLANEndpoint_Self;

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_Load(
    _Outptr_result_maybenull_ CIM_BindsToLANEndpoint_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_Unload(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_EnumerateInstances(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_GetInstance(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsToLANEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_CreateInstance(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsToLANEndpoint* newInstance);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_ModifyInstance(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsToLANEndpoint* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_DeleteInstance(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsToLANEndpoint* instanceName);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_AssociatorInstancesAntecedent(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LANEndpoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_AssociatorInstancesDependent(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_ReferenceInstancesAntecedent(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LANEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsToLANEndpoint_ReferenceInstancesDependent(
    _In_opt_ CIM_BindsToLANEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_BindsToLANEndpoint_h */
