/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicySetAppliesToElement_h
#define _CIM_PolicySetAppliesToElement_h

#include <MI.h>
#include "CIM_PolicySet.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_PolicySetAppliesToElement [CIM_PolicySetAppliesToElement]
**
** Keys:
**    PolicySet
**    ManagedElement
**
**==============================================================================
*/

typedef struct _CIM_PolicySetAppliesToElement
{
    MI_Instance __instance;
    /* CIM_PolicySetAppliesToElement properties */
    /*KEY*/ CIM_PolicySet_ConstRef PolicySet;
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
}
CIM_PolicySetAppliesToElement;

typedef struct _CIM_PolicySetAppliesToElement_Ref
{
    CIM_PolicySetAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetAppliesToElement_Ref;

typedef struct _CIM_PolicySetAppliesToElement_ConstRef
{
    MI_CONST CIM_PolicySetAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetAppliesToElement_ConstRef;

typedef struct _CIM_PolicySetAppliesToElement_Array
{
    struct _CIM_PolicySetAppliesToElement** data;
    MI_Uint32 size;
}
CIM_PolicySetAppliesToElement_Array;

typedef struct _CIM_PolicySetAppliesToElement_ConstArray
{
    struct _CIM_PolicySetAppliesToElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicySetAppliesToElement_ConstArray;

typedef struct _CIM_PolicySetAppliesToElement_ArrayRef
{
    CIM_PolicySetAppliesToElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetAppliesToElement_ArrayRef;

typedef struct _CIM_PolicySetAppliesToElement_ConstArrayRef
{
    CIM_PolicySetAppliesToElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicySetAppliesToElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicySetAppliesToElement_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Construct(
    _Out_ CIM_PolicySetAppliesToElement* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicySetAppliesToElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Clone(
    _In_ const CIM_PolicySetAppliesToElement* self,
    _Outptr_ CIM_PolicySetAppliesToElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicySetAppliesToElement_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicySetAppliesToElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Destruct(_Inout_ CIM_PolicySetAppliesToElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Delete(_Inout_ CIM_PolicySetAppliesToElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Post(
    _In_ const CIM_PolicySetAppliesToElement* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Set_PolicySet(
    _Inout_ CIM_PolicySetAppliesToElement* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_SetPtr_PolicySet(
    _Inout_ CIM_PolicySetAppliesToElement* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Clear_PolicySet(
    _Inout_ CIM_PolicySetAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Set_ManagedElement(
    _Inout_ CIM_PolicySetAppliesToElement* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_SetPtr_ManagedElement(
    _Inout_ CIM_PolicySetAppliesToElement* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicySetAppliesToElement_Clear_ManagedElement(
    _Inout_ CIM_PolicySetAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_PolicySetAppliesToElement provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_PolicySetAppliesToElement_Self CIM_PolicySetAppliesToElement_Self;

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_Load(
    _Outptr_result_maybenull_ CIM_PolicySetAppliesToElement_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_Unload(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_EnumerateInstances(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_GetInstance(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetAppliesToElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_CreateInstance(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetAppliesToElement* newInstance);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_ModifyInstance(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetAppliesToElement* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_DeleteInstance(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySetAppliesToElement* instanceName);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_AssociatorInstancesPolicySet(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_AssociatorInstancesManagedElement(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_ReferenceInstancesPolicySet(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicySetAppliesToElement_ReferenceInstancesManagedElement(
    _In_opt_ CIM_PolicySetAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_PolicySetAppliesToElement_h */
