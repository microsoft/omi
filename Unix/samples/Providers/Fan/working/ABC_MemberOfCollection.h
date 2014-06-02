/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_MemberOfCollection_h
#define _ABC_MemberOfCollection_h

#include <MI.h>
#include "CIM_MemberOfCollection.h"
#include "CIM_Collection.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** ABC_MemberOfCollection [ABC_MemberOfCollection]
**
** Keys:
**    Collection
**    Member
**
**==============================================================================
*/

typedef struct _ABC_MemberOfCollection /* extends CIM_MemberOfCollection */
{
    MI_Instance __instance;
    /* CIM_MemberOfCollection properties */
    /*KEY*/ CIM_Collection_ConstRef Collection;
    /*KEY*/ CIM_ManagedElement_ConstRef Member;
    /* ABC_MemberOfCollection properties */
}
ABC_MemberOfCollection;

typedef struct _ABC_MemberOfCollection_Ref
{
    ABC_MemberOfCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_MemberOfCollection_Ref;

typedef struct _ABC_MemberOfCollection_ConstRef
{
    MI_CONST ABC_MemberOfCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_MemberOfCollection_ConstRef;

typedef struct _ABC_MemberOfCollection_Array
{
    struct _ABC_MemberOfCollection** data;
    MI_Uint32 size;
}
ABC_MemberOfCollection_Array;

typedef struct _ABC_MemberOfCollection_ConstArray
{
    struct _ABC_MemberOfCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_MemberOfCollection_ConstArray;

typedef struct _ABC_MemberOfCollection_ArrayRef
{
    ABC_MemberOfCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_MemberOfCollection_ArrayRef;

typedef struct _ABC_MemberOfCollection_ConstArrayRef
{
    ABC_MemberOfCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_MemberOfCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_MemberOfCollection_rtti;

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Construct(
    ABC_MemberOfCollection* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_MemberOfCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Clone(
    const ABC_MemberOfCollection* self,
    ABC_MemberOfCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_MemberOfCollection_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_MemberOfCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Destruct(ABC_MemberOfCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Delete(ABC_MemberOfCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Post(
    const ABC_MemberOfCollection* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Set_Collection(
    ABC_MemberOfCollection* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_SetPtr_Collection(
    ABC_MemberOfCollection* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Clear_Collection(
    ABC_MemberOfCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Set_Member(
    ABC_MemberOfCollection* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_SetPtr_Member(
    ABC_MemberOfCollection* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_MemberOfCollection_Clear_Member(
    ABC_MemberOfCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_MemberOfCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_MemberOfCollection_Self ABC_MemberOfCollection_Self;

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_Load(
    ABC_MemberOfCollection_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_Unload(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_EnumerateInstances(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_GetInstance(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_MemberOfCollection* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_CreateInstance(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_MemberOfCollection* newInstance);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_ModifyInstance(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_MemberOfCollection* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_DeleteInstance(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_MemberOfCollection* instanceName);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_AssociatorInstancesCollection(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_Collection* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_AssociatorInstancesMember(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_ReferenceInstancesCollection(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_Collection* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_MemberOfCollection_ReferenceInstancesMember(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_MemberOfCollection_h */
