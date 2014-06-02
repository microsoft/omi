/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_RedundancySet_h
#define _ABC_RedundancySet_h

#include <MI.h>
#include "CIM_RedundancySet.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** ABC_RedundancySet [ABC_RedundancySet]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _ABC_RedundancySet /* extends CIM_RedundancySet */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_SystemSpecificCollection properties */
    /* CIM_RedundancySet properties */
    MI_ConstUint16Field RedundancyStatus;
    MI_ConstUint16AField TypeOfSet;
    MI_ConstUint32Field MinNumberNeeded;
    MI_ConstUint32Field MaxNumberSupported;
    MI_ConstStringField VendorIdentifyingInfo;
    MI_ConstStringAField OtherTypeOfSet;
    MI_ConstUint16Field LoadBalanceAlgorithm;
    MI_ConstStringField OtherLoadBalanceAlgorithm;
    /* ABC_RedundancySet properties */
}
ABC_RedundancySet;

typedef struct _ABC_RedundancySet_Ref
{
    ABC_RedundancySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_RedundancySet_Ref;

typedef struct _ABC_RedundancySet_ConstRef
{
    MI_CONST ABC_RedundancySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_RedundancySet_ConstRef;

typedef struct _ABC_RedundancySet_Array
{
    struct _ABC_RedundancySet** data;
    MI_Uint32 size;
}
ABC_RedundancySet_Array;

typedef struct _ABC_RedundancySet_ConstArray
{
    struct _ABC_RedundancySet MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_RedundancySet_ConstArray;

typedef struct _ABC_RedundancySet_ArrayRef
{
    ABC_RedundancySet_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_RedundancySet_ArrayRef;

typedef struct _ABC_RedundancySet_ConstArrayRef
{
    ABC_RedundancySet_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_RedundancySet_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_RedundancySet_rtti;

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Construct(
    ABC_RedundancySet* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_RedundancySet_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clone(
    const ABC_RedundancySet* self,
    ABC_RedundancySet** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_RedundancySet_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_RedundancySet_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Destruct(ABC_RedundancySet* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Delete(ABC_RedundancySet* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Post(
    const ABC_RedundancySet* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_InstanceID(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_InstanceID(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_InstanceID(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_Caption(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_Caption(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_Caption(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_Description(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_Description(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_Description(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_ElementName(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_ElementName(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_ElementName(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_RedundancyStatus(
    ABC_RedundancySet* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RedundancyStatus)->value = x;
    ((MI_Uint16Field*)&self->RedundancyStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_RedundancyStatus(
    ABC_RedundancySet* self)
{
    memset((void*)&self->RedundancyStatus, 0, sizeof(self->RedundancyStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_TypeOfSet(
    ABC_RedundancySet* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_TypeOfSet(
    ABC_RedundancySet* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_TypeOfSet(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_MinNumberNeeded(
    ABC_RedundancySet* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MinNumberNeeded)->value = x;
    ((MI_Uint32Field*)&self->MinNumberNeeded)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_MinNumberNeeded(
    ABC_RedundancySet* self)
{
    memset((void*)&self->MinNumberNeeded, 0, sizeof(self->MinNumberNeeded));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_MaxNumberSupported(
    ABC_RedundancySet* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxNumberSupported)->value = x;
    ((MI_Uint32Field*)&self->MaxNumberSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_MaxNumberSupported(
    ABC_RedundancySet* self)
{
    memset((void*)&self->MaxNumberSupported, 0, sizeof(self->MaxNumberSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_VendorIdentifyingInfo(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_VendorIdentifyingInfo(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_VendorIdentifyingInfo(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_OtherTypeOfSet(
    ABC_RedundancySet* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_OtherTypeOfSet(
    ABC_RedundancySet* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_OtherTypeOfSet(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_LoadBalanceAlgorithm(
    ABC_RedundancySet* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LoadBalanceAlgorithm)->value = x;
    ((MI_Uint16Field*)&self->LoadBalanceAlgorithm)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_LoadBalanceAlgorithm(
    ABC_RedundancySet* self)
{
    memset((void*)&self->LoadBalanceAlgorithm, 0, sizeof(self->LoadBalanceAlgorithm));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Set_OtherLoadBalanceAlgorithm(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_SetPtr_OtherLoadBalanceAlgorithm(
    ABC_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Clear_OtherLoadBalanceAlgorithm(
    ABC_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

/*
**==============================================================================
**
** ABC_RedundancySet.Failover()
**
**==============================================================================
*/

typedef struct _ABC_RedundancySet_Failover
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedElement_ConstRef FailoverFrom;
    /*IN*/ CIM_ManagedElement_ConstRef FailoverTo;
}
ABC_RedundancySet_Failover;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_RedundancySet_Failover_rtti;

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Construct(
    ABC_RedundancySet_Failover* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_RedundancySet_Failover_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Clone(
    const ABC_RedundancySet_Failover* self,
    ABC_RedundancySet_Failover** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Destruct(
    ABC_RedundancySet_Failover* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Delete(
    ABC_RedundancySet_Failover* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Post(
    const ABC_RedundancySet_Failover* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Set_MIReturn(
    ABC_RedundancySet_Failover* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Clear_MIReturn(
    ABC_RedundancySet_Failover* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Set_FailoverFrom(
    ABC_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_SetPtr_FailoverFrom(
    ABC_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Clear_FailoverFrom(
    ABC_RedundancySet_Failover* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Set_FailoverTo(
    ABC_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_SetPtr_FailoverTo(
    ABC_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_RedundancySet_Failover_Clear_FailoverTo(
    ABC_RedundancySet_Failover* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** ABC_RedundancySet provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_RedundancySet_Self ABC_RedundancySet_Self;

MI_EXTERN_C void MI_CALL ABC_RedundancySet_Load(
    ABC_RedundancySet_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_Unload(
    ABC_RedundancySet_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_EnumerateInstances(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_GetInstance(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RedundancySet* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_CreateInstance(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RedundancySet* newInstance);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_ModifyInstance(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RedundancySet* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_DeleteInstance(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RedundancySet* instanceName);

MI_EXTERN_C void MI_CALL ABC_RedundancySet_Invoke_Failover(
    ABC_RedundancySet_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_RedundancySet* instanceName,
    const ABC_RedundancySet_Failover* in);


#endif /* _ABC_RedundancySet_h */
