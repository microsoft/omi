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
#ifndef _CIM_Process_h
#define _CIM_Process_h

#include <MI.h>
#include "CIM_EnabledLogicalElement.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_Process [CIM_Process]
**
** Keys:
**    CSCreationClassName
**    CSName
**    OSCreationClassName
**    OSName
**    CreationClassName
**    Handle
**
**==============================================================================
*/

typedef struct _CIM_Process /* extends CIM_EnabledLogicalElement */
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
    /* CIM_Process properties */
    /*KEY*/ MI_ConstStringField CSCreationClassName;
    /*KEY*/ MI_ConstStringField CSName;
    /*KEY*/ MI_ConstStringField OSCreationClassName;
    /*KEY*/ MI_ConstStringField OSName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField Handle;
    MI_ConstUint32Field Priority;
    MI_ConstUint16Field ExecutionState;
    MI_ConstStringField OtherExecutionDescription;
    MI_ConstDatetimeField CreationDate;
    MI_ConstDatetimeField TerminationDate;
    MI_ConstUint64Field KernelModeTime;
    MI_ConstUint64Field UserModeTime;
    MI_ConstUint64Field WorkingSetSize;
}
CIM_Process;

typedef struct _CIM_Process_Ref
{
    CIM_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Process_Ref;

typedef struct _CIM_Process_ConstRef
{
    MI_CONST CIM_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Process_ConstRef;

typedef struct _CIM_Process_Array
{
    struct _CIM_Process** data;
    MI_Uint32 size;
}
CIM_Process_Array;

typedef struct _CIM_Process_ConstArray
{
    struct _CIM_Process MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Process_ConstArray;

typedef struct _CIM_Process_ArrayRef
{
    CIM_Process_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Process_ArrayRef;

typedef struct _CIM_Process_ConstArrayRef
{
    CIM_Process_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Process_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Process_rtti;

/*
**==============================================================================
**
** CIM_Process.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_Process_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_Process_RequestStateChange;


/*
**==============================================================================
**
** CIM_Process_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_Process_Class : public CIM_EnabledLogicalElement_Class
{
public:
    
    typedef CIM_Process Self;
    
    CIM_Process_Class() :
        CIM_EnabledLogicalElement_Class(&CIM_Process_rtti)
    {
    }
    
    CIM_Process_Class(
        const CIM_Process* instanceName,
        bool keysOnly) :
        CIM_EnabledLogicalElement_Class(
            &CIM_Process_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_Process_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_EnabledLogicalElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_Process_Class(
        const MI_ClassDecl* clDecl) :
        CIM_EnabledLogicalElement_Class(clDecl)
    {
    }
    
    CIM_Process_Class& operator=(
        const CIM_Process_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_Process_Class(
        const CIM_Process_Class& x) :
        CIM_EnabledLogicalElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_Process_rtti;
    }

    //
    // CIM_Process_Class.CSCreationClassName
    //
    
    const Field<String>& CSCreationClassName() const
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        return GetField<String>(n);
    }
    
    void CSCreationClassName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        GetField<String>(n) = x;
    }
    
    const String& CSCreationClassName_value() const
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        return GetField<String>(n).value;
    }
    
    void CSCreationClassName_value(const String& x)
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        GetField<String>(n).Set(x);
    }
    
    bool CSCreationClassName_exists() const
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void CSCreationClassName_clear()
    {
        const size_t n = offsetof(Self, CSCreationClassName);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.CSName
    //
    
    const Field<String>& CSName() const
    {
        const size_t n = offsetof(Self, CSName);
        return GetField<String>(n);
    }
    
    void CSName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, CSName);
        GetField<String>(n) = x;
    }
    
    const String& CSName_value() const
    {
        const size_t n = offsetof(Self, CSName);
        return GetField<String>(n).value;
    }
    
    void CSName_value(const String& x)
    {
        const size_t n = offsetof(Self, CSName);
        GetField<String>(n).Set(x);
    }
    
    bool CSName_exists() const
    {
        const size_t n = offsetof(Self, CSName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void CSName_clear()
    {
        const size_t n = offsetof(Self, CSName);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.OSCreationClassName
    //
    
    const Field<String>& OSCreationClassName() const
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        return GetField<String>(n);
    }
    
    void OSCreationClassName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        GetField<String>(n) = x;
    }
    
    const String& OSCreationClassName_value() const
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        return GetField<String>(n).value;
    }
    
    void OSCreationClassName_value(const String& x)
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        GetField<String>(n).Set(x);
    }
    
    bool OSCreationClassName_exists() const
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OSCreationClassName_clear()
    {
        const size_t n = offsetof(Self, OSCreationClassName);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.OSName
    //
    
    const Field<String>& OSName() const
    {
        const size_t n = offsetof(Self, OSName);
        return GetField<String>(n);
    }
    
    void OSName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OSName);
        GetField<String>(n) = x;
    }
    
    const String& OSName_value() const
    {
        const size_t n = offsetof(Self, OSName);
        return GetField<String>(n).value;
    }
    
    void OSName_value(const String& x)
    {
        const size_t n = offsetof(Self, OSName);
        GetField<String>(n).Set(x);
    }
    
    bool OSName_exists() const
    {
        const size_t n = offsetof(Self, OSName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OSName_clear()
    {
        const size_t n = offsetof(Self, OSName);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.CreationClassName
    //
    
    const Field<String>& CreationClassName() const
    {
        const size_t n = offsetof(Self, CreationClassName);
        return GetField<String>(n);
    }
    
    void CreationClassName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, CreationClassName);
        GetField<String>(n) = x;
    }
    
    const String& CreationClassName_value() const
    {
        const size_t n = offsetof(Self, CreationClassName);
        return GetField<String>(n).value;
    }
    
    void CreationClassName_value(const String& x)
    {
        const size_t n = offsetof(Self, CreationClassName);
        GetField<String>(n).Set(x);
    }
    
    bool CreationClassName_exists() const
    {
        const size_t n = offsetof(Self, CreationClassName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void CreationClassName_clear()
    {
        const size_t n = offsetof(Self, CreationClassName);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.Handle
    //
    
    const Field<String>& Handle() const
    {
        const size_t n = offsetof(Self, Handle);
        return GetField<String>(n);
    }
    
    void Handle(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Handle);
        GetField<String>(n) = x;
    }
    
    const String& Handle_value() const
    {
        const size_t n = offsetof(Self, Handle);
        return GetField<String>(n).value;
    }
    
    void Handle_value(const String& x)
    {
        const size_t n = offsetof(Self, Handle);
        GetField<String>(n).Set(x);
    }
    
    bool Handle_exists() const
    {
        const size_t n = offsetof(Self, Handle);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Handle_clear()
    {
        const size_t n = offsetof(Self, Handle);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.Priority
    //
    
    const Field<Uint32>& Priority() const
    {
        const size_t n = offsetof(Self, Priority);
        return GetField<Uint32>(n);
    }
    
    void Priority(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Priority);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Priority_value() const
    {
        const size_t n = offsetof(Self, Priority);
        return GetField<Uint32>(n).value;
    }
    
    void Priority_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Priority);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Priority_exists() const
    {
        const size_t n = offsetof(Self, Priority);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Priority_clear()
    {
        const size_t n = offsetof(Self, Priority);
        GetField<Uint32>(n).Clear();
    }

    //
    // CIM_Process_Class.ExecutionState
    //
    
    const Field<Uint16>& ExecutionState() const
    {
        const size_t n = offsetof(Self, ExecutionState);
        return GetField<Uint16>(n);
    }
    
    void ExecutionState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, ExecutionState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& ExecutionState_value() const
    {
        const size_t n = offsetof(Self, ExecutionState);
        return GetField<Uint16>(n).value;
    }
    
    void ExecutionState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, ExecutionState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool ExecutionState_exists() const
    {
        const size_t n = offsetof(Self, ExecutionState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void ExecutionState_clear()
    {
        const size_t n = offsetof(Self, ExecutionState);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Process_Class.OtherExecutionDescription
    //
    
    const Field<String>& OtherExecutionDescription() const
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        return GetField<String>(n);
    }
    
    void OtherExecutionDescription(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        GetField<String>(n) = x;
    }
    
    const String& OtherExecutionDescription_value() const
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        return GetField<String>(n).value;
    }
    
    void OtherExecutionDescription_value(const String& x)
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        GetField<String>(n).Set(x);
    }
    
    bool OtherExecutionDescription_exists() const
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OtherExecutionDescription_clear()
    {
        const size_t n = offsetof(Self, OtherExecutionDescription);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Process_Class.CreationDate
    //
    
    const Field<Datetime>& CreationDate() const
    {
        const size_t n = offsetof(Self, CreationDate);
        return GetField<Datetime>(n);
    }
    
    void CreationDate(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, CreationDate);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& CreationDate_value() const
    {
        const size_t n = offsetof(Self, CreationDate);
        return GetField<Datetime>(n).value;
    }
    
    void CreationDate_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, CreationDate);
        GetField<Datetime>(n).Set(x);
    }
    
    bool CreationDate_exists() const
    {
        const size_t n = offsetof(Self, CreationDate);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void CreationDate_clear()
    {
        const size_t n = offsetof(Self, CreationDate);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Process_Class.TerminationDate
    //
    
    const Field<Datetime>& TerminationDate() const
    {
        const size_t n = offsetof(Self, TerminationDate);
        return GetField<Datetime>(n);
    }
    
    void TerminationDate(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TerminationDate);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TerminationDate_value() const
    {
        const size_t n = offsetof(Self, TerminationDate);
        return GetField<Datetime>(n).value;
    }
    
    void TerminationDate_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TerminationDate);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TerminationDate_exists() const
    {
        const size_t n = offsetof(Self, TerminationDate);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TerminationDate_clear()
    {
        const size_t n = offsetof(Self, TerminationDate);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Process_Class.KernelModeTime
    //
    
    const Field<Uint64>& KernelModeTime() const
    {
        const size_t n = offsetof(Self, KernelModeTime);
        return GetField<Uint64>(n);
    }
    
    void KernelModeTime(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, KernelModeTime);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& KernelModeTime_value() const
    {
        const size_t n = offsetof(Self, KernelModeTime);
        return GetField<Uint64>(n).value;
    }
    
    void KernelModeTime_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, KernelModeTime);
        GetField<Uint64>(n).Set(x);
    }
    
    bool KernelModeTime_exists() const
    {
        const size_t n = offsetof(Self, KernelModeTime);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void KernelModeTime_clear()
    {
        const size_t n = offsetof(Self, KernelModeTime);
        GetField<Uint64>(n).Clear();
    }

    //
    // CIM_Process_Class.UserModeTime
    //
    
    const Field<Uint64>& UserModeTime() const
    {
        const size_t n = offsetof(Self, UserModeTime);
        return GetField<Uint64>(n);
    }
    
    void UserModeTime(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, UserModeTime);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& UserModeTime_value() const
    {
        const size_t n = offsetof(Self, UserModeTime);
        return GetField<Uint64>(n).value;
    }
    
    void UserModeTime_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, UserModeTime);
        GetField<Uint64>(n).Set(x);
    }
    
    bool UserModeTime_exists() const
    {
        const size_t n = offsetof(Self, UserModeTime);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void UserModeTime_clear()
    {
        const size_t n = offsetof(Self, UserModeTime);
        GetField<Uint64>(n).Clear();
    }

    //
    // CIM_Process_Class.WorkingSetSize
    //
    
    const Field<Uint64>& WorkingSetSize() const
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        return GetField<Uint64>(n);
    }
    
    void WorkingSetSize(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& WorkingSetSize_value() const
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        return GetField<Uint64>(n).value;
    }
    
    void WorkingSetSize_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        GetField<Uint64>(n).Set(x);
    }
    
    bool WorkingSetSize_exists() const
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void WorkingSetSize_clear()
    {
        const size_t n = offsetof(Self, WorkingSetSize);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<CIM_Process_Class> CIM_Process_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_Process_h */
