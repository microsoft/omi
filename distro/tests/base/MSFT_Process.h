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
#ifndef _MSFT_Process_h
#define _MSFT_Process_h

#include <MI.h>
#include "CIM_Process.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MSFT_Process [MSFT_Process]
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

typedef struct _MSFT_Process /* extends CIM_Process */
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
    /* MSFT_Process properties */
}
MSFT_Process;

typedef struct _MSFT_Process_Ref
{
    MSFT_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Process_Ref;

typedef struct _MSFT_Process_ConstRef
{
    MI_CONST MSFT_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Process_ConstRef;

typedef struct _MSFT_Process_Array
{
    struct _MSFT_Process** data;
    MI_Uint32 size;
}
MSFT_Process_Array;

typedef struct _MSFT_Process_ConstArray
{
    struct _MSFT_Process MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Process_ConstArray;

typedef struct _MSFT_Process_ArrayRef
{
    MSFT_Process_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Process_ArrayRef;

typedef struct _MSFT_Process_ConstArrayRef
{
    MSFT_Process_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Process_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Process_rtti;

/*
**==============================================================================
**
** MSFT_Process.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_Process_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_Process_RequestStateChange;


/*
**==============================================================================
**
** MSFT_Process_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Process_Class : public CIM_Process_Class
{
public:
    
    typedef MSFT_Process Self;
    
    MSFT_Process_Class() :
        CIM_Process_Class(&MSFT_Process_rtti)
    {
    }
    
    MSFT_Process_Class(
        const MSFT_Process* instanceName,
        bool keysOnly) :
        CIM_Process_Class(
            &MSFT_Process_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Process_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_Process_Class(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Process_Class(
        const MI_ClassDecl* clDecl) :
        CIM_Process_Class(clDecl)
    {
    }
    
    MSFT_Process_Class& operator=(
        const MSFT_Process_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Process_Class(
        const MSFT_Process_Class& x) :
        CIM_Process_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Process_rtti;
    }

};

typedef Array<MSFT_Process_Class> MSFT_Process_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Process_h */
