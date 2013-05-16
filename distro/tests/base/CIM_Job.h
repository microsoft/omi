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
#ifndef _CIM_Job_h
#define _CIM_Job_h

#include <MI.h>
#include "CIM_LogicalElement.h"

/*
**==============================================================================
**
** CIM_Job [CIM_Job]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Job /* extends CIM_LogicalElement */
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
    /* CIM_Job properties */
    MI_ConstStringField JobStatus;
    MI_ConstDatetimeField TimeSubmitted;
    MI_ConstDatetimeField ScheduledStartTime;
    MI_ConstDatetimeField StartTime;
    MI_ConstDatetimeField ElapsedTime;
    MI_ConstUint32Field JobRunTimes;
    MI_ConstUint8Field RunMonth;
    MI_ConstSint8Field RunDay;
    MI_ConstSint8Field RunDayOfWeek;
    MI_ConstDatetimeField RunStartInterval;
    MI_ConstUint16Field LocalOrUtcTime;
    MI_ConstDatetimeField UntilTime;
    MI_ConstStringField Notify;
    MI_ConstStringField Owner;
    MI_ConstUint32Field Priority;
    MI_ConstUint16Field PercentComplete;
    MI_ConstBooleanField DeleteOnCompletion;
    MI_ConstUint16Field ErrorCode;
    MI_ConstStringField ErrorDescription;
    MI_ConstUint16Field RecoveryAction;
    MI_ConstStringField OtherRecoveryAction;
}
CIM_Job;

typedef struct _CIM_Job_Ref
{
    CIM_Job* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_Ref;

typedef struct _CIM_Job_ConstRef
{
    MI_CONST CIM_Job* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ConstRef;

typedef struct _CIM_Job_Array
{
    struct _CIM_Job** data;
    MI_Uint32 size;
}
CIM_Job_Array;

typedef struct _CIM_Job_ConstArray
{
    struct _CIM_Job MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Job_ConstArray;

typedef struct _CIM_Job_ArrayRef
{
    CIM_Job_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ArrayRef;

typedef struct _CIM_Job_ConstArrayRef
{
    CIM_Job_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Job_rtti;

/*
**==============================================================================
**
** CIM_Job.KillJob()
**
**==============================================================================
*/

typedef struct _CIM_Job_KillJob
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField DeleteOnKill;
}
CIM_Job_KillJob;


/*
**==============================================================================
**
** CIM_Job_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_Job_Class : public CIM_LogicalElement_Class
{
public:
    
    typedef CIM_Job Self;
    
    CIM_Job_Class() :
        CIM_LogicalElement_Class(&CIM_Job_rtti)
    {
    }
    
    CIM_Job_Class(
        const CIM_Job* instanceName,
        bool keysOnly) :
        CIM_LogicalElement_Class(
            &CIM_Job_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_Job_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_LogicalElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_Job_Class(
        const MI_ClassDecl* clDecl) :
        CIM_LogicalElement_Class(clDecl)
    {
    }
    
    CIM_Job_Class& operator=(
        const CIM_Job_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_Job_Class(
        const CIM_Job_Class& x) :
        CIM_LogicalElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_Job_rtti;
    }

    //
    // CIM_Job_Class.JobStatus
    //
    
    const Field<String>& JobStatus() const
    {
        const size_t n = offsetof(Self, JobStatus);
        return GetField<String>(n);
    }
    
    void JobStatus(const Field<String>& x)
    {
        const size_t n = offsetof(Self, JobStatus);
        GetField<String>(n) = x;
    }
    
    const String& JobStatus_value() const
    {
        const size_t n = offsetof(Self, JobStatus);
        return GetField<String>(n).value;
    }
    
    void JobStatus_value(const String& x)
    {
        const size_t n = offsetof(Self, JobStatus);
        GetField<String>(n).Set(x);
    }
    
    bool JobStatus_exists() const
    {
        const size_t n = offsetof(Self, JobStatus);
        return GetField<String>(n).exists ? true : false;
    }
    
    void JobStatus_clear()
    {
        const size_t n = offsetof(Self, JobStatus);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Job_Class.TimeSubmitted
    //
    
    const Field<Datetime>& TimeSubmitted() const
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        return GetField<Datetime>(n);
    }
    
    void TimeSubmitted(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TimeSubmitted_value() const
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        return GetField<Datetime>(n).value;
    }
    
    void TimeSubmitted_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TimeSubmitted_exists() const
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TimeSubmitted_clear()
    {
        const size_t n = offsetof(Self, TimeSubmitted);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.ScheduledStartTime
    //
    
    const Field<Datetime>& ScheduledStartTime() const
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        return GetField<Datetime>(n);
    }
    
    void ScheduledStartTime(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& ScheduledStartTime_value() const
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        return GetField<Datetime>(n).value;
    }
    
    void ScheduledStartTime_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        GetField<Datetime>(n).Set(x);
    }
    
    bool ScheduledStartTime_exists() const
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void ScheduledStartTime_clear()
    {
        const size_t n = offsetof(Self, ScheduledStartTime);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.StartTime
    //
    
    const Field<Datetime>& StartTime() const
    {
        const size_t n = offsetof(Self, StartTime);
        return GetField<Datetime>(n);
    }
    
    void StartTime(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, StartTime);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& StartTime_value() const
    {
        const size_t n = offsetof(Self, StartTime);
        return GetField<Datetime>(n).value;
    }
    
    void StartTime_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, StartTime);
        GetField<Datetime>(n).Set(x);
    }
    
    bool StartTime_exists() const
    {
        const size_t n = offsetof(Self, StartTime);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void StartTime_clear()
    {
        const size_t n = offsetof(Self, StartTime);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.ElapsedTime
    //
    
    const Field<Datetime>& ElapsedTime() const
    {
        const size_t n = offsetof(Self, ElapsedTime);
        return GetField<Datetime>(n);
    }
    
    void ElapsedTime(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, ElapsedTime);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& ElapsedTime_value() const
    {
        const size_t n = offsetof(Self, ElapsedTime);
        return GetField<Datetime>(n).value;
    }
    
    void ElapsedTime_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, ElapsedTime);
        GetField<Datetime>(n).Set(x);
    }
    
    bool ElapsedTime_exists() const
    {
        const size_t n = offsetof(Self, ElapsedTime);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void ElapsedTime_clear()
    {
        const size_t n = offsetof(Self, ElapsedTime);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.JobRunTimes
    //
    
    const Field<Uint32>& JobRunTimes() const
    {
        const size_t n = offsetof(Self, JobRunTimes);
        return GetField<Uint32>(n);
    }
    
    void JobRunTimes(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, JobRunTimes);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& JobRunTimes_value() const
    {
        const size_t n = offsetof(Self, JobRunTimes);
        return GetField<Uint32>(n).value;
    }
    
    void JobRunTimes_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, JobRunTimes);
        GetField<Uint32>(n).Set(x);
    }
    
    bool JobRunTimes_exists() const
    {
        const size_t n = offsetof(Self, JobRunTimes);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void JobRunTimes_clear()
    {
        const size_t n = offsetof(Self, JobRunTimes);
        GetField<Uint32>(n).Clear();
    }

    //
    // CIM_Job_Class.RunMonth
    //
    
    const Field<Uint8>& RunMonth() const
    {
        const size_t n = offsetof(Self, RunMonth);
        return GetField<Uint8>(n);
    }
    
    void RunMonth(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, RunMonth);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& RunMonth_value() const
    {
        const size_t n = offsetof(Self, RunMonth);
        return GetField<Uint8>(n).value;
    }
    
    void RunMonth_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, RunMonth);
        GetField<Uint8>(n).Set(x);
    }
    
    bool RunMonth_exists() const
    {
        const size_t n = offsetof(Self, RunMonth);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void RunMonth_clear()
    {
        const size_t n = offsetof(Self, RunMonth);
        GetField<Uint8>(n).Clear();
    }

    //
    // CIM_Job_Class.RunDay
    //
    
    const Field<Sint8>& RunDay() const
    {
        const size_t n = offsetof(Self, RunDay);
        return GetField<Sint8>(n);
    }
    
    void RunDay(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, RunDay);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& RunDay_value() const
    {
        const size_t n = offsetof(Self, RunDay);
        return GetField<Sint8>(n).value;
    }
    
    void RunDay_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, RunDay);
        GetField<Sint8>(n).Set(x);
    }
    
    bool RunDay_exists() const
    {
        const size_t n = offsetof(Self, RunDay);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void RunDay_clear()
    {
        const size_t n = offsetof(Self, RunDay);
        GetField<Sint8>(n).Clear();
    }

    //
    // CIM_Job_Class.RunDayOfWeek
    //
    
    const Field<Sint8>& RunDayOfWeek() const
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        return GetField<Sint8>(n);
    }
    
    void RunDayOfWeek(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& RunDayOfWeek_value() const
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        return GetField<Sint8>(n).value;
    }
    
    void RunDayOfWeek_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        GetField<Sint8>(n).Set(x);
    }
    
    bool RunDayOfWeek_exists() const
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void RunDayOfWeek_clear()
    {
        const size_t n = offsetof(Self, RunDayOfWeek);
        GetField<Sint8>(n).Clear();
    }

    //
    // CIM_Job_Class.RunStartInterval
    //
    
    const Field<Datetime>& RunStartInterval() const
    {
        const size_t n = offsetof(Self, RunStartInterval);
        return GetField<Datetime>(n);
    }
    
    void RunStartInterval(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, RunStartInterval);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& RunStartInterval_value() const
    {
        const size_t n = offsetof(Self, RunStartInterval);
        return GetField<Datetime>(n).value;
    }
    
    void RunStartInterval_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, RunStartInterval);
        GetField<Datetime>(n).Set(x);
    }
    
    bool RunStartInterval_exists() const
    {
        const size_t n = offsetof(Self, RunStartInterval);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void RunStartInterval_clear()
    {
        const size_t n = offsetof(Self, RunStartInterval);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.LocalOrUtcTime
    //
    
    const Field<Uint16>& LocalOrUtcTime() const
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        return GetField<Uint16>(n);
    }
    
    void LocalOrUtcTime(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& LocalOrUtcTime_value() const
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        return GetField<Uint16>(n).value;
    }
    
    void LocalOrUtcTime_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        GetField<Uint16>(n).Set(x);
    }
    
    bool LocalOrUtcTime_exists() const
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void LocalOrUtcTime_clear()
    {
        const size_t n = offsetof(Self, LocalOrUtcTime);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Job_Class.UntilTime
    //
    
    const Field<Datetime>& UntilTime() const
    {
        const size_t n = offsetof(Self, UntilTime);
        return GetField<Datetime>(n);
    }
    
    void UntilTime(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, UntilTime);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& UntilTime_value() const
    {
        const size_t n = offsetof(Self, UntilTime);
        return GetField<Datetime>(n).value;
    }
    
    void UntilTime_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, UntilTime);
        GetField<Datetime>(n).Set(x);
    }
    
    bool UntilTime_exists() const
    {
        const size_t n = offsetof(Self, UntilTime);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void UntilTime_clear()
    {
        const size_t n = offsetof(Self, UntilTime);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_Job_Class.Notify
    //
    
    const Field<String>& Notify() const
    {
        const size_t n = offsetof(Self, Notify);
        return GetField<String>(n);
    }
    
    void Notify(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Notify);
        GetField<String>(n) = x;
    }
    
    const String& Notify_value() const
    {
        const size_t n = offsetof(Self, Notify);
        return GetField<String>(n).value;
    }
    
    void Notify_value(const String& x)
    {
        const size_t n = offsetof(Self, Notify);
        GetField<String>(n).Set(x);
    }
    
    bool Notify_exists() const
    {
        const size_t n = offsetof(Self, Notify);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Notify_clear()
    {
        const size_t n = offsetof(Self, Notify);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Job_Class.Owner
    //
    
    const Field<String>& Owner() const
    {
        const size_t n = offsetof(Self, Owner);
        return GetField<String>(n);
    }
    
    void Owner(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Owner);
        GetField<String>(n) = x;
    }
    
    const String& Owner_value() const
    {
        const size_t n = offsetof(Self, Owner);
        return GetField<String>(n).value;
    }
    
    void Owner_value(const String& x)
    {
        const size_t n = offsetof(Self, Owner);
        GetField<String>(n).Set(x);
    }
    
    bool Owner_exists() const
    {
        const size_t n = offsetof(Self, Owner);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Owner_clear()
    {
        const size_t n = offsetof(Self, Owner);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Job_Class.Priority
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
    // CIM_Job_Class.PercentComplete
    //
    
    const Field<Uint16>& PercentComplete() const
    {
        const size_t n = offsetof(Self, PercentComplete);
        return GetField<Uint16>(n);
    }
    
    void PercentComplete(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, PercentComplete);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& PercentComplete_value() const
    {
        const size_t n = offsetof(Self, PercentComplete);
        return GetField<Uint16>(n).value;
    }
    
    void PercentComplete_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, PercentComplete);
        GetField<Uint16>(n).Set(x);
    }
    
    bool PercentComplete_exists() const
    {
        const size_t n = offsetof(Self, PercentComplete);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void PercentComplete_clear()
    {
        const size_t n = offsetof(Self, PercentComplete);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Job_Class.DeleteOnCompletion
    //
    
    const Field<Boolean>& DeleteOnCompletion() const
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        return GetField<Boolean>(n);
    }
    
    void DeleteOnCompletion(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& DeleteOnCompletion_value() const
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        return GetField<Boolean>(n).value;
    }
    
    void DeleteOnCompletion_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        GetField<Boolean>(n).Set(x);
    }
    
    bool DeleteOnCompletion_exists() const
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void DeleteOnCompletion_clear()
    {
        const size_t n = offsetof(Self, DeleteOnCompletion);
        GetField<Boolean>(n).Clear();
    }

    //
    // CIM_Job_Class.ErrorCode
    //
    
    const Field<Uint16>& ErrorCode() const
    {
        const size_t n = offsetof(Self, ErrorCode);
        return GetField<Uint16>(n);
    }
    
    void ErrorCode(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, ErrorCode);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& ErrorCode_value() const
    {
        const size_t n = offsetof(Self, ErrorCode);
        return GetField<Uint16>(n).value;
    }
    
    void ErrorCode_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, ErrorCode);
        GetField<Uint16>(n).Set(x);
    }
    
    bool ErrorCode_exists() const
    {
        const size_t n = offsetof(Self, ErrorCode);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void ErrorCode_clear()
    {
        const size_t n = offsetof(Self, ErrorCode);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Job_Class.ErrorDescription
    //
    
    const Field<String>& ErrorDescription() const
    {
        const size_t n = offsetof(Self, ErrorDescription);
        return GetField<String>(n);
    }
    
    void ErrorDescription(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ErrorDescription);
        GetField<String>(n) = x;
    }
    
    const String& ErrorDescription_value() const
    {
        const size_t n = offsetof(Self, ErrorDescription);
        return GetField<String>(n).value;
    }
    
    void ErrorDescription_value(const String& x)
    {
        const size_t n = offsetof(Self, ErrorDescription);
        GetField<String>(n).Set(x);
    }
    
    bool ErrorDescription_exists() const
    {
        const size_t n = offsetof(Self, ErrorDescription);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ErrorDescription_clear()
    {
        const size_t n = offsetof(Self, ErrorDescription);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Job_Class.RecoveryAction
    //
    
    const Field<Uint16>& RecoveryAction() const
    {
        const size_t n = offsetof(Self, RecoveryAction);
        return GetField<Uint16>(n);
    }
    
    void RecoveryAction(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, RecoveryAction);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& RecoveryAction_value() const
    {
        const size_t n = offsetof(Self, RecoveryAction);
        return GetField<Uint16>(n).value;
    }
    
    void RecoveryAction_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, RecoveryAction);
        GetField<Uint16>(n).Set(x);
    }
    
    bool RecoveryAction_exists() const
    {
        const size_t n = offsetof(Self, RecoveryAction);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void RecoveryAction_clear()
    {
        const size_t n = offsetof(Self, RecoveryAction);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Job_Class.OtherRecoveryAction
    //
    
    const Field<String>& OtherRecoveryAction() const
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        return GetField<String>(n);
    }
    
    void OtherRecoveryAction(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        GetField<String>(n) = x;
    }
    
    const String& OtherRecoveryAction_value() const
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        return GetField<String>(n).value;
    }
    
    void OtherRecoveryAction_value(const String& x)
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        GetField<String>(n).Set(x);
    }
    
    bool OtherRecoveryAction_exists() const
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OtherRecoveryAction_clear()
    {
        const size_t n = offsetof(Self, OtherRecoveryAction);
        GetField<String>(n).Clear();
    }
};

typedef Array<CIM_Job_Class> CIM_Job_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_Job_h */
