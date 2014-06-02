/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_HostedCollection_h
#define _CIM_HostedCollection_h

#include <MI.h>
#include "CIM_HostedDependency.h"
#include "CIM_System.h"
#include "CIM_SystemSpecificCollection.h"

/*
**==============================================================================
**
** CIM_HostedCollection [CIM_HostedCollection]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_HostedCollection /* extends CIM_HostedDependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_System_ConstRef Antecedent;
    /*KEY*/ CIM_SystemSpecificCollection_ConstRef Dependent;
    /* CIM_HostedDependency properties */
    /* CIM_HostedCollection properties */
}
CIM_HostedCollection;

typedef struct _CIM_HostedCollection_Ref
{
    CIM_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_Ref;

typedef struct _CIM_HostedCollection_ConstRef
{
    MI_CONST CIM_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ConstRef;

typedef struct _CIM_HostedCollection_Array
{
    struct _CIM_HostedCollection** data;
    MI_Uint32 size;
}
CIM_HostedCollection_Array;

typedef struct _CIM_HostedCollection_ConstArray
{
    struct _CIM_HostedCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_HostedCollection_ConstArray;

typedef struct _CIM_HostedCollection_ArrayRef
{
    CIM_HostedCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ArrayRef;

typedef struct _CIM_HostedCollection_ConstArrayRef
{
    CIM_HostedCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_HostedCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Construct(
    _Out_ CIM_HostedCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_HostedCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clone(
    _In_ const CIM_HostedCollection* self,
    _Outptr_ CIM_HostedCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_HostedCollection_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_HostedCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Destruct(_Inout_ CIM_HostedCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Delete(_Inout_ CIM_HostedCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Post(
    _In_ const CIM_HostedCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Set_Antecedent(
    _Inout_ CIM_HostedCollection* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_SetPtr_Antecedent(
    _Inout_ CIM_HostedCollection* self,
    _In_ const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clear_Antecedent(
    _Inout_ CIM_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Set_Dependent(
    _Inout_ CIM_HostedCollection* self,
    _In_ const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_SetPtr_Dependent(
    _Inout_ CIM_HostedCollection* self,
    _In_ const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clear_Dependent(
    _Inout_ CIM_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_HostedCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_HostedCollection_Self CIM_HostedCollection_Self;

MI_EXTERN_C void MI_CALL CIM_HostedCollection_Load(
    _Outptr_result_maybenull_ CIM_HostedCollection_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_Unload(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_EnumerateInstances(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_GetInstance(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedCollection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_CreateInstance(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedCollection* newInstance);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_ModifyInstance(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedCollection* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_DeleteInstance(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_HostedCollection* instanceName);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_AssociatorInstancesAntecedent(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_AssociatorInstancesDependent(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_ReferenceInstancesAntecedent(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_System* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_HostedCollection_ReferenceInstancesDependent(
    _In_opt_ CIM_HostedCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_SystemSpecificCollection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_HostedCollection_h */
