/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SAPSAPDependency_h
#define _CIM_SAPSAPDependency_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_SAPSAPDependency [CIM_SAPSAPDependency]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_SAPSAPDependency /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_SAPSAPDependency properties */
}
CIM_SAPSAPDependency;

typedef struct _CIM_SAPSAPDependency_Ref
{
    CIM_SAPSAPDependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SAPSAPDependency_Ref;

typedef struct _CIM_SAPSAPDependency_ConstRef
{
    MI_CONST CIM_SAPSAPDependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SAPSAPDependency_ConstRef;

typedef struct _CIM_SAPSAPDependency_Array
{
    struct _CIM_SAPSAPDependency** data;
    MI_Uint32 size;
}
CIM_SAPSAPDependency_Array;

typedef struct _CIM_SAPSAPDependency_ConstArray
{
    struct _CIM_SAPSAPDependency MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SAPSAPDependency_ConstArray;

typedef struct _CIM_SAPSAPDependency_ArrayRef
{
    CIM_SAPSAPDependency_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SAPSAPDependency_ArrayRef;

typedef struct _CIM_SAPSAPDependency_ConstArrayRef
{
    CIM_SAPSAPDependency_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SAPSAPDependency_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SAPSAPDependency_rtti;

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Construct(
    _Out_ CIM_SAPSAPDependency* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_SAPSAPDependency_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Clone(
    _In_ const CIM_SAPSAPDependency* self,
    _Outptr_ CIM_SAPSAPDependency** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SAPSAPDependency_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SAPSAPDependency_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Destruct(_Inout_ CIM_SAPSAPDependency* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Delete(_Inout_ CIM_SAPSAPDependency* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Post(
    _In_ const CIM_SAPSAPDependency* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Set_Antecedent(
    _Inout_ CIM_SAPSAPDependency* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_SetPtr_Antecedent(
    _Inout_ CIM_SAPSAPDependency* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Clear_Antecedent(
    _Inout_ CIM_SAPSAPDependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Set_Dependent(
    _Inout_ CIM_SAPSAPDependency* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_SetPtr_Dependent(
    _Inout_ CIM_SAPSAPDependency* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SAPSAPDependency_Clear_Dependent(
    _Inout_ CIM_SAPSAPDependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_SAPSAPDependency provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_SAPSAPDependency_Self CIM_SAPSAPDependency_Self;

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_Load(
    _Outptr_result_maybenull_ CIM_SAPSAPDependency_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_Unload(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_EnumerateInstances(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_GetInstance(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SAPSAPDependency* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_CreateInstance(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SAPSAPDependency* newInstance);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_ModifyInstance(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SAPSAPDependency* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_DeleteInstance(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SAPSAPDependency* instanceName);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_AssociatorInstancesAntecedent(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_AssociatorInstancesDependent(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_ReferenceInstancesAntecedent(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_SAPSAPDependency_ReferenceInstancesDependent(
    _In_opt_ CIM_SAPSAPDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_SAPSAPDependency_h */
