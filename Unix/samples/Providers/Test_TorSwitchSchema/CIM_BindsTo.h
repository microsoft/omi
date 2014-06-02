/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_BindsTo_h
#define _CIM_BindsTo_h

#include <MI.h>
#include "CIM_SAPSAPDependency.h"
#include "CIM_ProtocolEndpoint.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_BindsTo [CIM_BindsTo]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_BindsTo /* extends CIM_SAPSAPDependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ProtocolEndpoint_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_SAPSAPDependency properties */
    /* CIM_BindsTo properties */
}
CIM_BindsTo;

typedef struct _CIM_BindsTo_Ref
{
    CIM_BindsTo* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsTo_Ref;

typedef struct _CIM_BindsTo_ConstRef
{
    MI_CONST CIM_BindsTo* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsTo_ConstRef;

typedef struct _CIM_BindsTo_Array
{
    struct _CIM_BindsTo** data;
    MI_Uint32 size;
}
CIM_BindsTo_Array;

typedef struct _CIM_BindsTo_ConstArray
{
    struct _CIM_BindsTo MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_BindsTo_ConstArray;

typedef struct _CIM_BindsTo_ArrayRef
{
    CIM_BindsTo_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsTo_ArrayRef;

typedef struct _CIM_BindsTo_ConstArrayRef
{
    CIM_BindsTo_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_BindsTo_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_BindsTo_rtti;

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Construct(
    _Out_ CIM_BindsTo* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_BindsTo_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Clone(
    _In_ const CIM_BindsTo* self,
    _Outptr_ CIM_BindsTo** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_BindsTo_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_BindsTo_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Destruct(_Inout_ CIM_BindsTo* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Delete(_Inout_ CIM_BindsTo* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Post(
    _In_ const CIM_BindsTo* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Set_Antecedent(
    _Inout_ CIM_BindsTo* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_SetPtr_Antecedent(
    _Inout_ CIM_BindsTo* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Clear_Antecedent(
    _Inout_ CIM_BindsTo* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Set_Dependent(
    _Inout_ CIM_BindsTo* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_SetPtr_Dependent(
    _Inout_ CIM_BindsTo* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_BindsTo_Clear_Dependent(
    _Inout_ CIM_BindsTo* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_BindsTo provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_BindsTo_Self CIM_BindsTo_Self;

MI_EXTERN_C void MI_CALL CIM_BindsTo_Load(
    _Outptr_result_maybenull_ CIM_BindsTo_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_BindsTo_Unload(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_BindsTo_EnumerateInstances(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsTo_GetInstance(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsTo* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_BindsTo_CreateInstance(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsTo* newInstance);

MI_EXTERN_C void MI_CALL CIM_BindsTo_ModifyInstance(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsTo* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_BindsTo_DeleteInstance(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_BindsTo* instanceName);

MI_EXTERN_C void MI_CALL CIM_BindsTo_AssociatorInstancesAntecedent(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProtocolEndpoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsTo_AssociatorInstancesDependent(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsTo_ReferenceInstancesAntecedent(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ProtocolEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_BindsTo_ReferenceInstancesDependent(
    _In_opt_ CIM_BindsTo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_BindsTo_h */
