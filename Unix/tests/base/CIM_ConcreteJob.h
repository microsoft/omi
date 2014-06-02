/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ConcreteJob_h
#define _CIM_ConcreteJob_h

#include <MI.h>
#include "CIM_Job.h"
#include "CIM_Error.h"

/*
**==============================================================================
**
** CIM_ConcreteJob [CIM_ConcreteJob]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob /* extends CIM_Job */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
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
    /* CIM_ConcreteJob properties */
    MI_ConstUint16Field JobState;
    MI_ConstDatetimeField TimeOfLastStateChange;
    MI_ConstDatetimeField TimeBeforeRemoval;
}
CIM_ConcreteJob;

typedef struct _CIM_ConcreteJob_Ref
{
    CIM_ConcreteJob* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_Ref;

typedef struct _CIM_ConcreteJob_ConstRef
{
    MI_CONST CIM_ConcreteJob* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ConstRef;

typedef struct _CIM_ConcreteJob_Array
{
    struct _CIM_ConcreteJob** data;
    MI_Uint32 size;
}
CIM_ConcreteJob_Array;

typedef struct _CIM_ConcreteJob_ConstArray
{
    struct _CIM_ConcreteJob MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ConcreteJob_ConstArray;

typedef struct _CIM_ConcreteJob_ArrayRef
{
    CIM_ConcreteJob_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ArrayRef;

typedef struct _CIM_ConcreteJob_ConstArrayRef
{
    CIM_ConcreteJob_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ConcreteJob_rtti;

/*
**==============================================================================
**
** CIM_ConcreteJob.KillJob()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_KillJob
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField DeleteOnKill;
}
CIM_ConcreteJob_KillJob;

/*
**==============================================================================
**
** CIM_ConcreteJob.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_ConcreteJob_RequestStateChange;

/*
**==============================================================================
**
** CIM_ConcreteJob.GetError()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_GetError
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ CIM_Error_ConstRef Error;
}
CIM_ConcreteJob_GetError;


/*
**==============================================================================
**
** CIM_ConcreteJob_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_ConcreteJob_Class : public CIM_Job_Class
{
public:
    
    typedef CIM_ConcreteJob Self;
    
    CIM_ConcreteJob_Class() :
        CIM_Job_Class(&CIM_ConcreteJob_rtti)
    {
    }
    
    CIM_ConcreteJob_Class(
        const CIM_ConcreteJob* instanceName,
        bool keysOnly) :
        CIM_Job_Class(
            &CIM_ConcreteJob_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_ConcreteJob_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_Job_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_ConcreteJob_Class(
        const MI_ClassDecl* clDecl) :
        CIM_Job_Class(clDecl)
    {
    }
    
    CIM_ConcreteJob_Class& operator=(
        const CIM_ConcreteJob_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_ConcreteJob_Class(
        const CIM_ConcreteJob_Class& x) :
        CIM_Job_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_ConcreteJob_rtti;
    }

    //
    // CIM_ConcreteJob_Class.JobState
    //
    
    const Field<Uint16>& JobState() const
    {
        const size_t n = offsetof(Self, JobState);
        return GetField<Uint16>(n);
    }
    
    void JobState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, JobState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& JobState_value() const
    {
        const size_t n = offsetof(Self, JobState);
        return GetField<Uint16>(n).value;
    }
    
    void JobState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, JobState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool JobState_exists() const
    {
        const size_t n = offsetof(Self, JobState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void JobState_clear()
    {
        const size_t n = offsetof(Self, JobState);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_ConcreteJob_Class.TimeOfLastStateChange
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
    // CIM_ConcreteJob_Class.TimeBeforeRemoval
    //
    
    const Field<Datetime>& TimeBeforeRemoval() const
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        return GetField<Datetime>(n);
    }
    
    void TimeBeforeRemoval(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TimeBeforeRemoval_value() const
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        return GetField<Datetime>(n).value;
    }
    
    void TimeBeforeRemoval_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TimeBeforeRemoval_exists() const
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TimeBeforeRemoval_clear()
    {
        const size_t n = offsetof(Self, TimeBeforeRemoval);
        GetField<Datetime>(n).Clear();
    }
};

typedef Array<CIM_ConcreteJob_Class> CIM_ConcreteJob_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_ConcreteJob_h */
