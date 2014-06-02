/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_MemberOfCollection_h
#define _CIM_MemberOfCollection_h

#include <MI.h>
#include "CIM_Collection.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_MemberOfCollection [CIM_MemberOfCollection]
**
** Keys:
**    Collection
**    Member
**
**==============================================================================
*/

typedef struct _CIM_MemberOfCollection
{
    MI_Instance __instance;
    /* CIM_MemberOfCollection properties */
    /*KEY*/ CIM_Collection_ConstRef Collection;
    /*KEY*/ CIM_ManagedElement_ConstRef Member;
}
CIM_MemberOfCollection;

typedef struct _CIM_MemberOfCollection_Ref
{
    CIM_MemberOfCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_MemberOfCollection_Ref;

typedef struct _CIM_MemberOfCollection_ConstRef
{
    MI_CONST CIM_MemberOfCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_MemberOfCollection_ConstRef;

typedef struct _CIM_MemberOfCollection_Array
{
    struct _CIM_MemberOfCollection** data;
    MI_Uint32 size;
}
CIM_MemberOfCollection_Array;

typedef struct _CIM_MemberOfCollection_ConstArray
{
    struct _CIM_MemberOfCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_MemberOfCollection_ConstArray;

typedef struct _CIM_MemberOfCollection_ArrayRef
{
    CIM_MemberOfCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_MemberOfCollection_ArrayRef;

typedef struct _CIM_MemberOfCollection_ConstArrayRef
{
    CIM_MemberOfCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_MemberOfCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_MemberOfCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Construct(
    _Out_ CIM_MemberOfCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_MemberOfCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Clone(
    _In_ const CIM_MemberOfCollection* self,
    _Outptr_ CIM_MemberOfCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_MemberOfCollection_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_MemberOfCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Destruct(_Inout_ CIM_MemberOfCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Delete(_Inout_ CIM_MemberOfCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Post(
    _In_ const CIM_MemberOfCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Set_Collection(
    _Inout_ CIM_MemberOfCollection* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_SetPtr_Collection(
    _Inout_ CIM_MemberOfCollection* self,
    _In_ const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Clear_Collection(
    _Inout_ CIM_MemberOfCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Set_Member(
    _Inout_ CIM_MemberOfCollection* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_SetPtr_Member(
    _Inout_ CIM_MemberOfCollection* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_MemberOfCollection_Clear_Member(
    _Inout_ CIM_MemberOfCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_MemberOfCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_MemberOfCollection_Self CIM_MemberOfCollection_Self;

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_Load(
    _Outptr_result_maybenull_ CIM_MemberOfCollection_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_Unload(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_EnumerateInstances(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_GetInstance(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_MemberOfCollection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_CreateInstance(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_MemberOfCollection* newInstance);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_ModifyInstance(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_MemberOfCollection* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_DeleteInstance(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_MemberOfCollection* instanceName);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_AssociatorInstancesCollection(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_AssociatorInstancesMember(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_ReferenceInstancesCollection(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_Collection* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_MemberOfCollection_ReferenceInstancesMember(
    _In_opt_ CIM_MemberOfCollection_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ManagedElement* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_MemberOfCollection_h */
