/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_RedundancySet_h
#define _CIM_RedundancySet_h

#include <MI.h>
#include "CIM_SystemSpecificCollection.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_RedundancySet [CIM_RedundancySet]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_RedundancySet /* extends CIM_SystemSpecificCollection */
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
}
CIM_RedundancySet;

typedef struct _CIM_RedundancySet_Ref
{
    CIM_RedundancySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RedundancySet_Ref;

typedef struct _CIM_RedundancySet_ConstRef
{
    MI_CONST CIM_RedundancySet* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RedundancySet_ConstRef;

typedef struct _CIM_RedundancySet_Array
{
    struct _CIM_RedundancySet** data;
    MI_Uint32 size;
}
CIM_RedundancySet_Array;

typedef struct _CIM_RedundancySet_ConstArray
{
    struct _CIM_RedundancySet MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_RedundancySet_ConstArray;

typedef struct _CIM_RedundancySet_ArrayRef
{
    CIM_RedundancySet_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RedundancySet_ArrayRef;

typedef struct _CIM_RedundancySet_ConstArrayRef
{
    CIM_RedundancySet_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_RedundancySet_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_RedundancySet_rtti;

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Construct(
    CIM_RedundancySet* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_RedundancySet_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clone(
    const CIM_RedundancySet* self,
    CIM_RedundancySet** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_RedundancySet_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_RedundancySet_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Destruct(CIM_RedundancySet* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Delete(CIM_RedundancySet* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Post(
    const CIM_RedundancySet* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_InstanceID(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_InstanceID(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_InstanceID(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_Caption(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_Caption(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_Caption(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_Description(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_Description(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_Description(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_ElementName(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_ElementName(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_ElementName(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_RedundancyStatus(
    CIM_RedundancySet* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RedundancyStatus)->value = x;
    ((MI_Uint16Field*)&self->RedundancyStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_RedundancyStatus(
    CIM_RedundancySet* self)
{
    memset((void*)&self->RedundancyStatus, 0, sizeof(self->RedundancyStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_TypeOfSet(
    CIM_RedundancySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_TypeOfSet(
    CIM_RedundancySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_TypeOfSet(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_MinNumberNeeded(
    CIM_RedundancySet* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MinNumberNeeded)->value = x;
    ((MI_Uint32Field*)&self->MinNumberNeeded)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_MinNumberNeeded(
    CIM_RedundancySet* self)
{
    memset((void*)&self->MinNumberNeeded, 0, sizeof(self->MinNumberNeeded));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_MaxNumberSupported(
    CIM_RedundancySet* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxNumberSupported)->value = x;
    ((MI_Uint32Field*)&self->MaxNumberSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_MaxNumberSupported(
    CIM_RedundancySet* self)
{
    memset((void*)&self->MaxNumberSupported, 0, sizeof(self->MaxNumberSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_VendorIdentifyingInfo(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_VendorIdentifyingInfo(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_VendorIdentifyingInfo(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_OtherTypeOfSet(
    CIM_RedundancySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_OtherTypeOfSet(
    CIM_RedundancySet* self,
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

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_OtherTypeOfSet(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_LoadBalanceAlgorithm(
    CIM_RedundancySet* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LoadBalanceAlgorithm)->value = x;
    ((MI_Uint16Field*)&self->LoadBalanceAlgorithm)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_LoadBalanceAlgorithm(
    CIM_RedundancySet* self)
{
    memset((void*)&self->LoadBalanceAlgorithm, 0, sizeof(self->LoadBalanceAlgorithm));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Set_OtherLoadBalanceAlgorithm(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_SetPtr_OtherLoadBalanceAlgorithm(
    CIM_RedundancySet* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Clear_OtherLoadBalanceAlgorithm(
    CIM_RedundancySet* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

/*
**==============================================================================
**
** CIM_RedundancySet.Failover()
**
**==============================================================================
*/

typedef struct _CIM_RedundancySet_Failover
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedElement_ConstRef FailoverFrom;
    /*IN*/ CIM_ManagedElement_ConstRef FailoverTo;
}
CIM_RedundancySet_Failover;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_RedundancySet_Failover_rtti;

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Construct(
    CIM_RedundancySet_Failover* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_RedundancySet_Failover_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Clone(
    const CIM_RedundancySet_Failover* self,
    CIM_RedundancySet_Failover** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Destruct(
    CIM_RedundancySet_Failover* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Delete(
    CIM_RedundancySet_Failover* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Post(
    const CIM_RedundancySet_Failover* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Set_MIReturn(
    CIM_RedundancySet_Failover* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Clear_MIReturn(
    CIM_RedundancySet_Failover* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Set_FailoverFrom(
    CIM_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_SetPtr_FailoverFrom(
    CIM_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Clear_FailoverFrom(
    CIM_RedundancySet_Failover* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Set_FailoverTo(
    CIM_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_SetPtr_FailoverTo(
    CIM_RedundancySet_Failover* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_RedundancySet_Failover_Clear_FailoverTo(
    CIM_RedundancySet_Failover* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}


#endif /* _CIM_RedundancySet_h */
