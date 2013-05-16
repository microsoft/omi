/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_HostedCollection_h
#define _ABC_HostedCollection_h

#include <MI.h>
#include "CIM_HostedCollection.h"
#include "CIM_System.h"
#include "CIM_SystemSpecificCollection.h"

/*
**==============================================================================
**
** ABC_HostedCollection [ABC_HostedCollection]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _ABC_HostedCollection /* extends CIM_HostedCollection */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_System_ConstRef Antecedent;
    /*KEY*/ CIM_SystemSpecificCollection_ConstRef Dependent;
    /* CIM_HostedDependency properties */
    /* CIM_HostedCollection properties */
    /* ABC_HostedCollection properties */
}
ABC_HostedCollection;

typedef struct _ABC_HostedCollection_Ref
{
    ABC_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_HostedCollection_Ref;

typedef struct _ABC_HostedCollection_ConstRef
{
    MI_CONST ABC_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_HostedCollection_ConstRef;

typedef struct _ABC_HostedCollection_Array
{
    struct _ABC_HostedCollection** data;
    MI_Uint32 size;
}
ABC_HostedCollection_Array;

typedef struct _ABC_HostedCollection_ConstArray
{
    struct _ABC_HostedCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_HostedCollection_ConstArray;

typedef struct _ABC_HostedCollection_ArrayRef
{
    ABC_HostedCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_HostedCollection_ArrayRef;

typedef struct _ABC_HostedCollection_ConstArrayRef
{
    ABC_HostedCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_HostedCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_HostedCollection_rtti;

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Construct(
    ABC_HostedCollection* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_HostedCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Clone(
    const ABC_HostedCollection* self,
    ABC_HostedCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_HostedCollection_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_HostedCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Destruct(ABC_HostedCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Delete(ABC_HostedCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Post(
    const ABC_HostedCollection* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Set_Antecedent(
    ABC_HostedCollection* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_SetPtr_Antecedent(
    ABC_HostedCollection* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Clear_Antecedent(
    ABC_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Set_Dependent(
    ABC_HostedCollection* self,
    const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_SetPtr_Dependent(
    ABC_HostedCollection* self,
    const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_HostedCollection_Clear_Dependent(
    ABC_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_HostedCollection provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_HostedCollection_Self ABC_HostedCollection_Self;

MI_EXTERN_C void MI_CALL ABC_HostedCollection_Load(
    ABC_HostedCollection_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_Unload(
    ABC_HostedCollection_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_EnumerateInstances(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_GetInstance(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_HostedCollection* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_CreateInstance(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_HostedCollection* newInstance);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_ModifyInstance(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_HostedCollection* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_DeleteInstance(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_HostedCollection* instanceName);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_AssociatorInstancesAntecedent(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_System* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_AssociatorInstancesDependent(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_SystemSpecificCollection* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_ReferenceInstancesAntecedent(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_System* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_HostedCollection_ReferenceInstancesDependent(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_SystemSpecificCollection* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_HostedCollection_h */
