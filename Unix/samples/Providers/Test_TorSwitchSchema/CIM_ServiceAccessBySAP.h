/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ServiceAccessBySAP_h
#define _CIM_ServiceAccessBySAP_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_Service.h"
#include "CIM_ServiceAccessPoint.h"

/*
**==============================================================================
**
** CIM_ServiceAccessBySAP [CIM_ServiceAccessBySAP]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_ServiceAccessBySAP /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_Service_ConstRef Antecedent;
    /*KEY*/ CIM_ServiceAccessPoint_ConstRef Dependent;
    /* CIM_ServiceAccessBySAP properties */
}
CIM_ServiceAccessBySAP;

typedef struct _CIM_ServiceAccessBySAP_Ref
{
    CIM_ServiceAccessBySAP* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ServiceAccessBySAP_Ref;

typedef struct _CIM_ServiceAccessBySAP_ConstRef
{
    MI_CONST CIM_ServiceAccessBySAP* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ServiceAccessBySAP_ConstRef;

typedef struct _CIM_ServiceAccessBySAP_Array
{
    struct _CIM_ServiceAccessBySAP** data;
    MI_Uint32 size;
}
CIM_ServiceAccessBySAP_Array;

typedef struct _CIM_ServiceAccessBySAP_ConstArray
{
    struct _CIM_ServiceAccessBySAP MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ServiceAccessBySAP_ConstArray;

typedef struct _CIM_ServiceAccessBySAP_ArrayRef
{
    CIM_ServiceAccessBySAP_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ServiceAccessBySAP_ArrayRef;

typedef struct _CIM_ServiceAccessBySAP_ConstArrayRef
{
    CIM_ServiceAccessBySAP_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ServiceAccessBySAP_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ServiceAccessBySAP_rtti;

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Construct(
    _Out_ CIM_ServiceAccessBySAP* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ServiceAccessBySAP_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Clone(
    _In_ const CIM_ServiceAccessBySAP* self,
    _Outptr_ CIM_ServiceAccessBySAP** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ServiceAccessBySAP_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ServiceAccessBySAP_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Destruct(_Inout_ CIM_ServiceAccessBySAP* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Delete(_Inout_ CIM_ServiceAccessBySAP* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Post(
    _In_ const CIM_ServiceAccessBySAP* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Set_Antecedent(
    _Inout_ CIM_ServiceAccessBySAP* self,
    _In_ const CIM_Service* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_SetPtr_Antecedent(
    _Inout_ CIM_ServiceAccessBySAP* self,
    _In_ const CIM_Service* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Clear_Antecedent(
    _Inout_ CIM_ServiceAccessBySAP* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Set_Dependent(
    _Inout_ CIM_ServiceAccessBySAP* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_SetPtr_Dependent(
    _Inout_ CIM_ServiceAccessBySAP* self,
    _In_ const CIM_ServiceAccessPoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ServiceAccessBySAP_Clear_Dependent(
    _Inout_ CIM_ServiceAccessBySAP* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_ServiceAccessBySAP provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ServiceAccessBySAP_Self CIM_ServiceAccessBySAP_Self;

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_Load(
    _Outptr_result_maybenull_ CIM_ServiceAccessBySAP_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_Unload(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_EnumerateInstances(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_GetInstance(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessBySAP* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_CreateInstance(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessBySAP* newInstance);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_ModifyInstance(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessBySAP* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_DeleteInstance(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessBySAP* instanceName);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_AssociatorInstancesAntecedent(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Service* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_AssociatorInstancesDependent(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_ReferenceInstancesAntecedent(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Service* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ServiceAccessBySAP_ReferenceInstancesDependent(
    _In_opt_ CIM_ServiceAccessBySAP_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ServiceAccessPoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_ServiceAccessBySAP_h */
