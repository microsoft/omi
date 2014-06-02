/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_OwningCollectionElement_h
#define _ABC_OwningCollectionElement_h

#include <MI.h>
#include "CIM_OwningCollectionElement.h"
#include "CIM_ManagedElement.h"
#include "CIM_Collection.h"

/*
**==============================================================================
**
** ABC_OwningCollectionElement [ABC_OwningCollectionElement]
**
** Keys:
**    OwningElement
**    OwnedElement
**
**==============================================================================
*/

typedef struct _ABC_OwningCollectionElement /* extends CIM_OwningCollectionElement */
{
    MI_Instance __instance;
    /* CIM_OwningCollectionElement properties */
    /*KEY*/ CIM_ManagedElement_ConstRef OwningElement;
    /*KEY*/ CIM_Collection_ConstRef OwnedElement;
    /* ABC_OwningCollectionElement properties */
}
ABC_OwningCollectionElement;

typedef struct _ABC_OwningCollectionElement_Ref
{
    ABC_OwningCollectionElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_OwningCollectionElement_Ref;

typedef struct _ABC_OwningCollectionElement_ConstRef
{
    MI_CONST ABC_OwningCollectionElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_OwningCollectionElement_ConstRef;

typedef struct _ABC_OwningCollectionElement_Array
{
    struct _ABC_OwningCollectionElement** data;
    MI_Uint32 size;
}
ABC_OwningCollectionElement_Array;

typedef struct _ABC_OwningCollectionElement_ConstArray
{
    struct _ABC_OwningCollectionElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_OwningCollectionElement_ConstArray;

typedef struct _ABC_OwningCollectionElement_ArrayRef
{
    ABC_OwningCollectionElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_OwningCollectionElement_ArrayRef;

typedef struct _ABC_OwningCollectionElement_ConstArrayRef
{
    ABC_OwningCollectionElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_OwningCollectionElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_OwningCollectionElement_rtti;

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Construct(
    ABC_OwningCollectionElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_OwningCollectionElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Clone(
    const ABC_OwningCollectionElement* self,
    ABC_OwningCollectionElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_OwningCollectionElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_OwningCollectionElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Destruct(ABC_OwningCollectionElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Delete(ABC_OwningCollectionElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Post(
    const ABC_OwningCollectionElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Set_OwningElement(
    ABC_OwningCollectionElement* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_SetPtr_OwningElement(
    ABC_OwningCollectionElement* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Clear_OwningElement(
    ABC_OwningCollectionElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Set_OwnedElement(
    ABC_OwningCollectionElement* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_SetPtr_OwnedElement(
    ABC_OwningCollectionElement* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_OwningCollectionElement_Clear_OwnedElement(
    ABC_OwningCollectionElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_OwningCollectionElement provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_OwningCollectionElement_Self ABC_OwningCollectionElement_Self;

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_Load(
    ABC_OwningCollectionElement_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_Unload(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_EnumerateInstances(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_GetInstance(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_OwningCollectionElement* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_CreateInstance(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_OwningCollectionElement* newInstance);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_ModifyInstance(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_OwningCollectionElement* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_DeleteInstance(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_OwningCollectionElement* instanceName);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_AssociatorInstancesOwningElement(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_AssociatorInstancesOwnedElement(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_Collection* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_ReferenceInstancesOwningElement(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_OwningCollectionElement_ReferenceInstancesOwnedElement(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_Collection* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_OwningCollectionElement_h */
