/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_HostedDependency_h
#define _CIM_HostedDependency_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_HostedDependency [CIM_HostedDependency]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_HostedDependency /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ManagedElement_ConstRef Antecedent;
    /*KEY*/ CIM_ManagedElement_ConstRef Dependent;
    /* CIM_HostedDependency properties */
}
CIM_HostedDependency;

typedef struct _CIM_HostedDependency_Ref
{
    CIM_HostedDependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedDependency_Ref;

typedef struct _CIM_HostedDependency_ConstRef
{
    MI_CONST CIM_HostedDependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedDependency_ConstRef;

typedef struct _CIM_HostedDependency_Array
{
    struct _CIM_HostedDependency** data;
    MI_Uint32 size;
}
CIM_HostedDependency_Array;

typedef struct _CIM_HostedDependency_ConstArray
{
    struct _CIM_HostedDependency MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_HostedDependency_ConstArray;

typedef struct _CIM_HostedDependency_ArrayRef
{
    CIM_HostedDependency_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedDependency_ArrayRef;

typedef struct _CIM_HostedDependency_ConstArrayRef
{
    CIM_HostedDependency_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedDependency_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_HostedDependency_rtti;

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Construct(
    _Out_ CIM_HostedDependency* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_HostedDependency_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Clone(
    _In_ const CIM_HostedDependency* self,
    _Outptr_ CIM_HostedDependency** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_HostedDependency_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_HostedDependency_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Destruct(_Inout_ CIM_HostedDependency* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Delete(_Inout_ CIM_HostedDependency* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Post(
    _In_ const CIM_HostedDependency* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Set_Antecedent(
    _Inout_ CIM_HostedDependency* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_SetPtr_Antecedent(
    _Inout_ CIM_HostedDependency* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Clear_Antecedent(
    _Inout_ CIM_HostedDependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Set_Dependent(
    _Inout_ CIM_HostedDependency* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_SetPtr_Dependent(
    _Inout_ CIM_HostedDependency* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedDependency_Clear_Dependent(
    _Inout_ CIM_HostedDependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_HostedDependency provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_HostedDependency_Self CIM_HostedDependency_Self;

MI_EXTERN_C void MI_CALL CIM_HostedDependency_Load(
    _Outptr_result_maybenull_ CIM_HostedDependency_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_Unload(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_EnumerateInstances(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_GetInstance(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedDependency* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_CreateInstance(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedDependency* newInstance);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_ModifyInstance(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedDependency* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_DeleteInstance(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedDependency* instanceName);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_AssociatorInstancesAntecedent(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_AssociatorInstancesDependent(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_ReferenceInstancesAntecedent(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedDependency_ReferenceInstancesDependent(
    _In_opt_ CIM_HostedDependency_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_HostedDependency_h */
