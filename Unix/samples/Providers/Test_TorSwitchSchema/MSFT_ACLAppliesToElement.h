/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ACLAppliesToElement_h
#define _MSFT_ACLAppliesToElement_h

#include <MI.h>
#include "CIM_PolicySetAppliesToElement.h"
#include "CIM_PolicySet.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** MSFT_ACLAppliesToElement [MSFT_ACLAppliesToElement]
**
** Keys:
**    PolicySet
**    ManagedElement
**
**==============================================================================
*/

typedef struct _MSFT_ACLAppliesToElement /* extends CIM_PolicySetAppliesToElement */
{
    MI_Instance __instance;
    /* CIM_PolicySetAppliesToElement properties */
    /*KEY*/ CIM_PolicySet_ConstRef PolicySet;
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
    /* MSFT_ACLAppliesToElement properties */
    MI_ConstUint16Field Direction;
}
MSFT_ACLAppliesToElement;

typedef struct _MSFT_ACLAppliesToElement_Ref
{
    MSFT_ACLAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACLAppliesToElement_Ref;

typedef struct _MSFT_ACLAppliesToElement_ConstRef
{
    MI_CONST MSFT_ACLAppliesToElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACLAppliesToElement_ConstRef;

typedef struct _MSFT_ACLAppliesToElement_Array
{
    struct _MSFT_ACLAppliesToElement** data;
    MI_Uint32 size;
}
MSFT_ACLAppliesToElement_Array;

typedef struct _MSFT_ACLAppliesToElement_ConstArray
{
    struct _MSFT_ACLAppliesToElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ACLAppliesToElement_ConstArray;

typedef struct _MSFT_ACLAppliesToElement_ArrayRef
{
    MSFT_ACLAppliesToElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACLAppliesToElement_ArrayRef;

typedef struct _MSFT_ACLAppliesToElement_ConstArrayRef
{
    MSFT_ACLAppliesToElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACLAppliesToElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ACLAppliesToElement_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Construct(
    _Out_ MSFT_ACLAppliesToElement* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ACLAppliesToElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Clone(
    _In_ const MSFT_ACLAppliesToElement* self,
    _Outptr_ MSFT_ACLAppliesToElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ACLAppliesToElement_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ACLAppliesToElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Destruct(_Inout_ MSFT_ACLAppliesToElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Delete(_Inout_ MSFT_ACLAppliesToElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Post(
    _In_ const MSFT_ACLAppliesToElement* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Set_PolicySet(
    _Inout_ MSFT_ACLAppliesToElement* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_SetPtr_PolicySet(
    _Inout_ MSFT_ACLAppliesToElement* self,
    _In_ const CIM_PolicySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Clear_PolicySet(
    _Inout_ MSFT_ACLAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Set_ManagedElement(
    _Inout_ MSFT_ACLAppliesToElement* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_SetPtr_ManagedElement(
    _Inout_ MSFT_ACLAppliesToElement* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Clear_ManagedElement(
    _Inout_ MSFT_ACLAppliesToElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Set_Direction(
    _Inout_ MSFT_ACLAppliesToElement* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Direction)->value = x;
    ((MI_Uint16Field*)&self->Direction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACLAppliesToElement_Clear_Direction(
    _Inout_ MSFT_ACLAppliesToElement* self)
{
    memset((void*)&self->Direction, 0, sizeof(self->Direction));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_ACLAppliesToElement provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_ACLAppliesToElement_Self MSFT_ACLAppliesToElement_Self;

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_Load(
    _Outptr_result_maybenull_ MSFT_ACLAppliesToElement_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_Unload(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_EnumerateInstances(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_GetInstance(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACLAppliesToElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_CreateInstance(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACLAppliesToElement* newInstance);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_ModifyInstance(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACLAppliesToElement* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_DeleteInstance(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACLAppliesToElement* instanceName);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_AssociatorInstancesPolicySet(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_AssociatorInstancesManagedElement(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_ReferenceInstancesPolicySet(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicySet* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ACLAppliesToElement_ReferenceInstancesManagedElement(
    _In_opt_ MSFT_ACLAppliesToElement_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_ACLAppliesToElement_h */
