/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_IsSpare_h
#define _ABC_IsSpare_h

#include <MI.h>
#include "CIM_IsSpare.h"
#include "CIM_ManagedElement.h"
#include "CIM_RedundancySet.h"

/*
**==============================================================================
**
** ABC_IsSpare [ABC_IsSpare]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _ABC_IsSpare /* extends CIM_IsSpare */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ManagedElement_ConstRef Antecedent;
    /*KEY*/ CIM_RedundancySet_ConstRef Dependent;
    /* CIM_IsSpare properties */
    MI_ConstUint16Field SpareStatus;
    MI_ConstUint16Field FailoverSupported;
    /* ABC_IsSpare properties */
}
ABC_IsSpare;

typedef struct _ABC_IsSpare_Ref
{
    ABC_IsSpare* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_IsSpare_Ref;

typedef struct _ABC_IsSpare_ConstRef
{
    MI_CONST ABC_IsSpare* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_IsSpare_ConstRef;

typedef struct _ABC_IsSpare_Array
{
    struct _ABC_IsSpare** data;
    MI_Uint32 size;
}
ABC_IsSpare_Array;

typedef struct _ABC_IsSpare_ConstArray
{
    struct _ABC_IsSpare MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_IsSpare_ConstArray;

typedef struct _ABC_IsSpare_ArrayRef
{
    ABC_IsSpare_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_IsSpare_ArrayRef;

typedef struct _ABC_IsSpare_ConstArrayRef
{
    ABC_IsSpare_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_IsSpare_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_IsSpare_rtti;

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Construct(
    ABC_IsSpare* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_IsSpare_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Clone(
    const ABC_IsSpare* self,
    ABC_IsSpare** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_IsSpare_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_IsSpare_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Destruct(ABC_IsSpare* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Delete(ABC_IsSpare* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Post(
    const ABC_IsSpare* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Set_Antecedent(
    ABC_IsSpare* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_SetPtr_Antecedent(
    ABC_IsSpare* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Clear_Antecedent(
    ABC_IsSpare* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Set_Dependent(
    ABC_IsSpare* self,
    const CIM_RedundancySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_SetPtr_Dependent(
    ABC_IsSpare* self,
    const CIM_RedundancySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Clear_Dependent(
    ABC_IsSpare* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Set_SpareStatus(
    ABC_IsSpare* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SpareStatus)->value = x;
    ((MI_Uint16Field*)&self->SpareStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Clear_SpareStatus(
    ABC_IsSpare* self)
{
    memset((void*)&self->SpareStatus, 0, sizeof(self->SpareStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Set_FailoverSupported(
    ABC_IsSpare* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->FailoverSupported)->value = x;
    ((MI_Uint16Field*)&self->FailoverSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_IsSpare_Clear_FailoverSupported(
    ABC_IsSpare* self)
{
    memset((void*)&self->FailoverSupported, 0, sizeof(self->FailoverSupported));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_IsSpare provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_IsSpare_Self ABC_IsSpare_Self;

MI_EXTERN_C void MI_CALL ABC_IsSpare_Load(
    ABC_IsSpare_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_IsSpare_Unload(
    ABC_IsSpare_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_IsSpare_EnumerateInstances(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_IsSpare_GetInstance(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_IsSpare* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_IsSpare_CreateInstance(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_IsSpare* newInstance);

MI_EXTERN_C void MI_CALL ABC_IsSpare_ModifyInstance(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_IsSpare* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_IsSpare_DeleteInstance(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_IsSpare* instanceName);

MI_EXTERN_C void MI_CALL ABC_IsSpare_AssociatorInstancesAntecedent(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_IsSpare_AssociatorInstancesDependent(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_RedundancySet* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_IsSpare_ReferenceInstancesAntecedent(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_ManagedElement* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_IsSpare_ReferenceInstancesDependent(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const CIM_RedundancySet* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _ABC_IsSpare_h */
