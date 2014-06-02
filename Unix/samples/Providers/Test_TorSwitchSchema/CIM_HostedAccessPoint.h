/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_HostedAccessPoint_h
#define _CIM_HostedAccessPoint_h

#include <MI.h>
#include "CIM_HostedDependency.h"
#include "CIM_System.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_HostedAccessPoint [CIM_HostedAccessPoint]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_HostedAccessPoint /* extends CIM_HostedDependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_System_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_HostedDependency properties */
    /* CIM_HostedAccessPoint properties */
}
CIM_HostedAccessPoint;

typedef struct _CIM_HostedAccessPoint_Ref
{
    CIM_HostedAccessPoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedAccessPoint_Ref;

typedef struct _CIM_HostedAccessPoint_ConstRef
{
    MI_CONST CIM_HostedAccessPoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedAccessPoint_ConstRef;

typedef struct _CIM_HostedAccessPoint_Array
{
    struct _CIM_HostedAccessPoint** data;
    MI_Uint32 size;
}
CIM_HostedAccessPoint_Array;

typedef struct _CIM_HostedAccessPoint_ConstArray
{
    struct _CIM_HostedAccessPoint MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_HostedAccessPoint_ConstArray;

typedef struct _CIM_HostedAccessPoint_ArrayRef
{
    CIM_HostedAccessPoint_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedAccessPoint_ArrayRef;

typedef struct _CIM_HostedAccessPoint_ConstArrayRef
{
    CIM_HostedAccessPoint_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedAccessPoint_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_HostedAccessPoint_rtti;

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Construct(
    _Out_ CIM_HostedAccessPoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_HostedAccessPoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Clone(
    _In_ const CIM_HostedAccessPoint* self,
    _Outptr_ CIM_HostedAccessPoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_HostedAccessPoint_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_HostedAccessPoint_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Destruct(_Inout_ CIM_HostedAccessPoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Delete(_Inout_ CIM_HostedAccessPoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Post(
    _In_ const CIM_HostedAccessPoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Set_Antecedent(
    _Inout_ CIM_HostedAccessPoint* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_SetPtr_Antecedent(
    _Inout_ CIM_HostedAccessPoint* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Clear_Antecedent(
    _Inout_ CIM_HostedAccessPoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Set_Dependent(
    _Inout_ CIM_HostedAccessPoint* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_SetPtr_Dependent(
    _Inout_ CIM_HostedAccessPoint* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedAccessPoint_Clear_Dependent(
    _Inout_ CIM_HostedAccessPoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_HostedAccessPoint provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_HostedAccessPoint_Self CIM_HostedAccessPoint_Self;

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_Load(
    _Outptr_result_maybenull_ CIM_HostedAccessPoint_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_Unload(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_EnumerateInstances(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_GetInstance(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_CreateInstance(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedAccessPoint* newInstance);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_ModifyInstance(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedAccessPoint* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_DeleteInstance(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedAccessPoint* instanceName);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_AssociatorInstancesAntecedent(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_AssociatorInstancesDependent(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_ReferenceInstancesAntecedent(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedAccessPoint_ReferenceInstancesDependent(
    _In_opt_ CIM_HostedAccessPoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_HostedAccessPoint_h */
