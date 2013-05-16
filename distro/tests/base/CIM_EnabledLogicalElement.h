/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_EnabledLogicalElement_h
#define _CIM_EnabledLogicalElement_h

#include <MI.h>
#include "CIM_LogicalElement.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_EnabledLogicalElement [CIM_EnabledLogicalElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElement /* extends CIM_LogicalElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    MI_ConstStringField Name;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstStringAField StatusDescriptions;
    MI_ConstStringField Status;
    MI_ConstUint16Field HealthState;
    MI_ConstUint16Field CommunicationStatus;
    MI_ConstUint16Field DetailedStatus;
    MI_ConstUint16Field OperatingStatus;
    MI_ConstUint16Field PrimaryStatus;
    /* CIM_LogicalElement properties */
    /* CIM_EnabledLogicalElement properties */
    MI_ConstUint16Field EnabledState;
    MI_ConstStringField OtherEnabledState;
    MI_ConstUint16Field RequestedState;
    MI_ConstUint16Field EnabledDefault;
    MI_ConstDatetimeField TimeOfLastStateChange;
    MI_ConstUint16AField AvailableRequestedStates;
    MI_ConstUint16Field TransitioningToState;
}
CIM_EnabledLogicalElement;

typedef struct _CIM_EnabledLogicalElement_Ref
{
    CIM_EnabledLogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_Ref;

typedef struct _CIM_EnabledLogicalElement_ConstRef
{
    MI_CONST CIM_EnabledLogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ConstRef;

typedef struct _CIM_EnabledLogicalElement_Array
{
    struct _CIM_EnabledLogicalElement** data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElement_Array;

typedef struct _CIM_EnabledLogicalElement_ConstArray
{
    struct _CIM_EnabledLogicalElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElement_ConstArray;

typedef struct _CIM_EnabledLogicalElement_ArrayRef
{
    CIM_EnabledLogicalElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ArrayRef;

typedef struct _CIM_EnabledLogicalElement_ConstArrayRef
{
    CIM_EnabledLogicalElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_EnabledLogicalElement_rtti;

/*
**==============================================================================
**
** CIM_EnabledLogicalElement.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElement_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_EnabledLogicalElement_RequestStateChange;


/*
**==============================================================================
**
** CIM_EnabledLogicalElement_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_EnabledLogicalElement_Class : public CIM_LogicalElement_Class
{
public:
    
    typedef CIM_EnabledLogicalElement Self;
    
    CIM_EnabledLogicalElement_Class() :
        CIM_LogicalElement_Class(&CIM_EnabledLogicalElement_rtti)
    {
    }
    
    CIM_EnabledLogicalElement_Class(
        const CIM_EnabledLogicalElement* instanceName,
        bool keysOnly) :
        CIM_LogicalElement_Class(
            &CIM_EnabledLogicalElement_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_EnabledLogicalElement_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_LogicalElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_EnabledLogicalElement_Class(
        const MI_ClassDecl* clDecl) :
        CIM_LogicalElement_Class(clDecl)
    {
    }
    
    CIM_EnabledLogicalElement_Class& operator=(
        const CIM_EnabledLogicalElement_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_EnabledLogicalElement_Class(
        const CIM_EnabledLogicalElement_Class& x) :
        CIM_LogicalElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_EnabledLogicalElement_rtti;
    }

    //
    // CIM_EnabledLogicalElement_Class.EnabledState
    //
    
    const Field<Uint16>& EnabledState() const
    {
        const size_t n = offsetof(Self, EnabledState);
        return GetField<Uint16>(n);
    }
    
    void EnabledState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, EnabledState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& EnabledState_value() const
    {
        const size_t n = offsetof(Self, EnabledState);
        return GetField<Uint16>(n).value;
    }
    
    void EnabledState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, EnabledState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool EnabledState_exists() const
    {
        const size_t n = offsetof(Self, EnabledState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void EnabledState_clear()
    {
        const size_t n = offsetof(Self, EnabledState);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.OtherEnabledState
    //
    
    const Field<String>& OtherEnabledState() const
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        return GetField<String>(n);
    }
    
    void OtherEnabledState(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        GetField<String>(n) = x;
    }
    
    const String& OtherEnabledState_value() const
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        return GetField<String>(n).value;
    }
    
    void OtherEnabledState_value(const String& x)
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        GetField<String>(n).Set(x);
    }
    
    bool OtherEnabledState_exists() const
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OtherEnabledState_clear()
    {
        const size_t n = offsetof(Self, OtherEnabledState);
        GetField<String>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.RequestedState
    //
    
    const Field<Uint16>& RequestedState() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n);
    }
    
    void RequestedState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& RequestedState_value() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n).value;
    }
    
    void RequestedState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool RequestedState_exists() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void RequestedState_clear()
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.EnabledDefault
    //
    
    const Field<Uint16>& EnabledDefault() const
    {
        const size_t n = offsetof(Self, EnabledDefault);
        return GetField<Uint16>(n);
    }
    
    void EnabledDefault(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, EnabledDefault);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& EnabledDefault_value() const
    {
        const size_t n = offsetof(Self, EnabledDefault);
        return GetField<Uint16>(n).value;
    }
    
    void EnabledDefault_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, EnabledDefault);
        GetField<Uint16>(n).Set(x);
    }
    
    bool EnabledDefault_exists() const
    {
        const size_t n = offsetof(Self, EnabledDefault);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void EnabledDefault_clear()
    {
        const size_t n = offsetof(Self, EnabledDefault);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.TimeOfLastStateChange
    //
    
    const Field<Datetime>& TimeOfLastStateChange() const
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        return GetField<Datetime>(n);
    }
    
    void TimeOfLastStateChange(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TimeOfLastStateChange_value() const
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        return GetField<Datetime>(n).value;
    }
    
    void TimeOfLastStateChange_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TimeOfLastStateChange_exists() const
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TimeOfLastStateChange_clear()
    {
        const size_t n = offsetof(Self, TimeOfLastStateChange);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.AvailableRequestedStates
    //
    
    const Field<Uint16A>& AvailableRequestedStates() const
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        return GetField<Uint16A>(n);
    }
    
    void AvailableRequestedStates(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& AvailableRequestedStates_value() const
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        return GetField<Uint16A>(n).value;
    }
    
    void AvailableRequestedStates_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool AvailableRequestedStates_exists() const
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void AvailableRequestedStates_clear()
    {
        const size_t n = offsetof(Self, AvailableRequestedStates);
        GetField<Uint16A>(n).Clear();
    }

    //
    // CIM_EnabledLogicalElement_Class.TransitioningToState
    //
    
    const Field<Uint16>& TransitioningToState() const
    {
        const size_t n = offsetof(Self, TransitioningToState);
        return GetField<Uint16>(n);
    }
    
    void TransitioningToState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, TransitioningToState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& TransitioningToState_value() const
    {
        const size_t n = offsetof(Self, TransitioningToState);
        return GetField<Uint16>(n).value;
    }
    
    void TransitioningToState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, TransitioningToState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool TransitioningToState_exists() const
    {
        const size_t n = offsetof(Self, TransitioningToState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void TransitioningToState_clear()
    {
        const size_t n = offsetof(Self, TransitioningToState);
        GetField<Uint16>(n).Clear();
    }
};

typedef Array<CIM_EnabledLogicalElement_Class> CIM_EnabledLogicalElement_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_EnabledLogicalElement_h */
