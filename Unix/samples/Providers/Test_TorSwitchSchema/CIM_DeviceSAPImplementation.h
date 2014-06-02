/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_DeviceSAPImplementation_h
#define _CIM_DeviceSAPImplementation_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_LogicalDevice.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_DeviceSAPImplementation [CIM_DeviceSAPImplementation]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_DeviceSAPImplementation /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_LogicalDevice_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_DeviceSAPImplementation properties */
}
CIM_DeviceSAPImplementation;

typedef struct _CIM_DeviceSAPImplementation_Ref
{
    CIM_DeviceSAPImplementation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DeviceSAPImplementation_Ref;

typedef struct _CIM_DeviceSAPImplementation_ConstRef
{
    MI_CONST CIM_DeviceSAPImplementation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DeviceSAPImplementation_ConstRef;

typedef struct _CIM_DeviceSAPImplementation_Array
{
    struct _CIM_DeviceSAPImplementation** data;
    MI_Uint32 size;
}
CIM_DeviceSAPImplementation_Array;

typedef struct _CIM_DeviceSAPImplementation_ConstArray
{
    struct _CIM_DeviceSAPImplementation MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_DeviceSAPImplementation_ConstArray;

typedef struct _CIM_DeviceSAPImplementation_ArrayRef
{
    CIM_DeviceSAPImplementation_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DeviceSAPImplementation_ArrayRef;

typedef struct _CIM_DeviceSAPImplementation_ConstArrayRef
{
    CIM_DeviceSAPImplementation_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_DeviceSAPImplementation_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_DeviceSAPImplementation_rtti;

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Construct(
    _Out_ CIM_DeviceSAPImplementation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_DeviceSAPImplementation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Clone(
    _In_ const CIM_DeviceSAPImplementation* self,
    _Outptr_ CIM_DeviceSAPImplementation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_DeviceSAPImplementation_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_DeviceSAPImplementation_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Destruct(_Inout_ CIM_DeviceSAPImplementation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Delete(_Inout_ CIM_DeviceSAPImplementation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Post(
    _In_ const CIM_DeviceSAPImplementation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Set_Antecedent(
    _Inout_ CIM_DeviceSAPImplementation* self,
    _In_ const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_SetPtr_Antecedent(
    _Inout_ CIM_DeviceSAPImplementation* self,
    _In_ const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Clear_Antecedent(
    _Inout_ CIM_DeviceSAPImplementation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Set_Dependent(
    _Inout_ CIM_DeviceSAPImplementation* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_SetPtr_Dependent(
    _Inout_ CIM_DeviceSAPImplementation* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_DeviceSAPImplementation_Clear_Dependent(
    _Inout_ CIM_DeviceSAPImplementation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_DeviceSAPImplementation provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_DeviceSAPImplementation_Self CIM_DeviceSAPImplementation_Self;

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_Load(
    _Outptr_result_maybenull_ CIM_DeviceSAPImplementation_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_Unload(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_EnumerateInstances(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_GetInstance(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_DeviceSAPImplementation* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_CreateInstance(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_DeviceSAPImplementation* newInstance);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_ModifyInstance(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_DeviceSAPImplementation* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_DeleteInstance(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_DeviceSAPImplementation* instanceName);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_AssociatorInstancesAntecedent(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LogicalDevice* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_AssociatorInstancesDependent(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_ReferenceInstancesAntecedent(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_LogicalDevice* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_DeviceSAPImplementation_ReferenceInstancesDependent(
    _In_opt_ CIM_DeviceSAPImplementation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_DeviceSAPImplementation_h */
