/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_AssociatedAddressFamilyNetworks_h
#define _MSFT_AssociatedAddressFamilyNetworks_h

#include <MI.h>
#include "CIM_MemberOfCollection.h"
#include "CIM_Collection.h"
#include "MSFT_AddressFamilyNetwork.h"

/*
**==============================================================================
**
** MSFT_AssociatedAddressFamilyNetworks [MSFT_AssociatedAddressFamilyNetworks]
**
** Keys:
**    Collection
**    Member
**
**==============================================================================
*/

typedef struct _MSFT_AssociatedAddressFamilyNetworks /* extends CIM_MemberOfCollection */
{
    MI_Instance __instance;
    /* CIM_MemberOfCollection properties */
    /*KEY*/ CIM_Collection_ConstRef Collection;
    /*KEY*/ MSFT_AddressFamilyNetwork_ConstRef Member;
    /* MSFT_AssociatedAddressFamilyNetworks properties */
}
MSFT_AssociatedAddressFamilyNetworks;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_Ref
{
    MSFT_AssociatedAddressFamilyNetworks* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamilyNetworks_Ref;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_ConstRef
{
    MI_CONST MSFT_AssociatedAddressFamilyNetworks* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamilyNetworks_ConstRef;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_Array
{
    struct _MSFT_AssociatedAddressFamilyNetworks** data;
    MI_Uint32 size;
}
MSFT_AssociatedAddressFamilyNetworks_Array;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_ConstArray
{
    struct _MSFT_AssociatedAddressFamilyNetworks MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AssociatedAddressFamilyNetworks_ConstArray;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_ArrayRef
{
    MSFT_AssociatedAddressFamilyNetworks_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamilyNetworks_ArrayRef;

typedef struct _MSFT_AssociatedAddressFamilyNetworks_ConstArrayRef
{
    MSFT_AssociatedAddressFamilyNetworks_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AssociatedAddressFamilyNetworks_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AssociatedAddressFamilyNetworks_rtti;

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Construct(
    _Out_ MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_AssociatedAddressFamilyNetworks_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Clone(
    _In_ const MSFT_AssociatedAddressFamilyNetworks* self,
    _Outptr_ MSFT_AssociatedAddressFamilyNetworks** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_AssociatedAddressFamilyNetworks_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_AssociatedAddressFamilyNetworks_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Destruct(_Inout_ MSFT_AssociatedAddressFamilyNetworks* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Delete(_Inout_ MSFT_AssociatedAddressFamilyNetworks* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Post(
    _In_ const MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Set_Collection(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_SetPtr_Collection(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Clear_Collection(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Set_Member(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ const MSFT_AddressFamilyNetwork* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_SetPtr_Member(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self,
    _In_ const MSFT_AddressFamilyNetwork* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_AssociatedAddressFamilyNetworks_Clear_Member(
    _Inout_ MSFT_AssociatedAddressFamilyNetworks* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_AssociatedAddressFamilyNetworks provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_AssociatedAddressFamilyNetworks_Self MSFT_AssociatedAddressFamilyNetworks_Self;

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_Load(
    _Outptr_result_maybenull_ MSFT_AssociatedAddressFamilyNetworks_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_Unload(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_EnumerateInstances(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_GetInstance(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamilyNetworks* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_CreateInstance(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamilyNetworks* newInstance);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_ModifyInstance(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamilyNetworks* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_DeleteInstance(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AssociatedAddressFamilyNetworks* instanceName);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_AssociatorInstancesCollection(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_AssociatorInstancesMember(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AddressFamilyNetwork* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_ReferenceInstancesCollection(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_AssociatedAddressFamilyNetworks_ReferenceInstancesMember(
    _In_opt_ MSFT_AssociatedAddressFamilyNetworks_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_AddressFamilyNetwork* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _MSFT_AssociatedAddressFamilyNetworks_h */
