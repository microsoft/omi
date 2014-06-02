/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ProvidesEndpoint_h
#define _CIM_ProvidesEndpoint_h

#include <MI.h>
#include "CIM_ServiceAccessBySAP.h"
#include "CIM_Service.h"
#include "CIM_ProtocolEndpoint.h"

/*
**==============================================================================
**
** CIM_ProvidesEndpoint [CIM_ProvidesEndpoint]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_ProvidesEndpoint /* extends CIM_ServiceAccessBySAP */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_Service_ConstRef Antecedent;
    /*KEY*/ CIM_ProtocolEndpoint_ConstRef Dependent;
    /* CIM_ServiceAccessBySAP properties */
    /* CIM_ProvidesEndpoint properties */
}
CIM_ProvidesEndpoint;

typedef struct _CIM_ProvidesEndpoint_Ref
{
    CIM_ProvidesEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ProvidesEndpoint_Ref;

typedef struct _CIM_ProvidesEndpoint_ConstRef
{
    MI_CONST CIM_ProvidesEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ProvidesEndpoint_ConstRef;

typedef struct _CIM_ProvidesEndpoint_Array
{
    struct _CIM_ProvidesEndpoint** data;
    MI_Uint32 size;
}
CIM_ProvidesEndpoint_Array;

typedef struct _CIM_ProvidesEndpoint_ConstArray
{
    struct _CIM_ProvidesEndpoint MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ProvidesEndpoint_ConstArray;

typedef struct _CIM_ProvidesEndpoint_ArrayRef
{
    CIM_ProvidesEndpoint_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ProvidesEndpoint_ArrayRef;

typedef struct _CIM_ProvidesEndpoint_ConstArrayRef
{
    CIM_ProvidesEndpoint_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ProvidesEndpoint_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ProvidesEndpoint_rtti;

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Construct(
    _Out_ CIM_ProvidesEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ProvidesEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Clone(
    _In_ const CIM_ProvidesEndpoint* self,
    _Outptr_ CIM_ProvidesEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ProvidesEndpoint_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ProvidesEndpoint_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Destruct(_Inout_ CIM_ProvidesEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Delete(_Inout_ CIM_ProvidesEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Post(
    _In_ const CIM_ProvidesEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Set_Antecedent(
    _Inout_ CIM_ProvidesEndpoint* self,
    _In_ const CIM_Service* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_SetPtr_Antecedent(
    _Inout_ CIM_ProvidesEndpoint* self,
    _In_ const CIM_Service* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Clear_Antecedent(
    _Inout_ CIM_ProvidesEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Set_Dependent(
    _Inout_ CIM_ProvidesEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_SetPtr_Dependent(
    _Inout_ CIM_ProvidesEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ProvidesEndpoint_Clear_Dependent(
    _Inout_ CIM_ProvidesEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_ProvidesEndpoint provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ProvidesEndpoint_Self CIM_ProvidesEndpoint_Self;

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_Load(
    _Outptr_result_maybenull_ CIM_ProvidesEndpoint_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_Unload(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_EnumerateInstances(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_GetInstance(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProvidesEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_CreateInstance(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProvidesEndpoint* newInstance);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_ModifyInstance(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProvidesEndpoint* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_DeleteInstance(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProvidesEndpoint* instanceName);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_AssociatorInstancesAntecedent(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Service* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_AssociatorInstancesDependent(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProtocolEndpoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_ReferenceInstancesAntecedent(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Service* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ProvidesEndpoint_ReferenceInstancesDependent(
    _In_opt_ CIM_ProvidesEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProtocolEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_ProvidesEndpoint_h */
