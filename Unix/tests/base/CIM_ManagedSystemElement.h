/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ManagedSystemElement_h
#define _CIM_ManagedSystemElement_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_ManagedSystemElement [CIM_ManagedSystemElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_ManagedSystemElement /* extends CIM_ManagedElement */
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
}
CIM_ManagedSystemElement;

typedef struct _CIM_ManagedSystemElement_Ref
{
    CIM_ManagedSystemElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedSystemElement_Ref;

typedef struct _CIM_ManagedSystemElement_ConstRef
{
    MI_CONST CIM_ManagedSystemElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedSystemElement_ConstRef;

typedef struct _CIM_ManagedSystemElement_Array
{
    struct _CIM_ManagedSystemElement** data;
    MI_Uint32 size;
}
CIM_ManagedSystemElement_Array;

typedef struct _CIM_ManagedSystemElement_ConstArray
{
    struct _CIM_ManagedSystemElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ManagedSystemElement_ConstArray;

typedef struct _CIM_ManagedSystemElement_ArrayRef
{
    CIM_ManagedSystemElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedSystemElement_ArrayRef;

typedef struct _CIM_ManagedSystemElement_ConstArrayRef
{
    CIM_ManagedSystemElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedSystemElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ManagedSystemElement_rtti;


/*
**==============================================================================
**
** CIM_ManagedSystemElement_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_ManagedSystemElement_Class : public CIM_ManagedElement_Class
{
public:
    
    typedef CIM_ManagedSystemElement Self;
    
    CIM_ManagedSystemElement_Class() :
        CIM_ManagedElement_Class(&CIM_ManagedSystemElement_rtti)
    {
    }
    
    CIM_ManagedSystemElement_Class(
        const CIM_ManagedSystemElement* instanceName,
        bool keysOnly) :
        CIM_ManagedElement_Class(
            &CIM_ManagedSystemElement_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_ManagedSystemElement_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_ManagedElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_ManagedSystemElement_Class(
        const MI_ClassDecl* clDecl) :
        CIM_ManagedElement_Class(clDecl)
    {
    }
    
    CIM_ManagedSystemElement_Class& operator=(
        const CIM_ManagedSystemElement_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_ManagedSystemElement_Class(
        const CIM_ManagedSystemElement_Class& x) :
        CIM_ManagedElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_ManagedSystemElement_rtti;
    }

    //
    // CIM_ManagedSystemElement_Class.InstallDate
    //
    
    const Field<Datetime>& InstallDate() const
    {
        const size_t n = offsetof(Self, InstallDate);
        return GetField<Datetime>(n);
    }
    
    void InstallDate(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, InstallDate);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& InstallDate_value() const
    {
        const size_t n = offsetof(Self, InstallDate);
        return GetField<Datetime>(n).value;
    }
    
    void InstallDate_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, InstallDate);
        GetField<Datetime>(n).Set(x);
    }
    
    bool InstallDate_exists() const
    {
        const size_t n = offsetof(Self, InstallDate);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void InstallDate_clear()
    {
        const size_t n = offsetof(Self, InstallDate);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.Name
    //
    
    const Field<String>& Name() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n);
    }
    
    void Name(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n) = x;
    }
    
    const String& Name_value() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).value;
    }
    
    void Name_value(const String& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Set(x);
    }
    
    bool Name_exists() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Name_clear()
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.OperationalStatus
    //
    
    const Field<Uint16A>& OperationalStatus() const
    {
        const size_t n = offsetof(Self, OperationalStatus);
        return GetField<Uint16A>(n);
    }
    
    void OperationalStatus(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, OperationalStatus);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& OperationalStatus_value() const
    {
        const size_t n = offsetof(Self, OperationalStatus);
        return GetField<Uint16A>(n).value;
    }
    
    void OperationalStatus_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, OperationalStatus);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool OperationalStatus_exists() const
    {
        const size_t n = offsetof(Self, OperationalStatus);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void OperationalStatus_clear()
    {
        const size_t n = offsetof(Self, OperationalStatus);
        GetField<Uint16A>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.StatusDescriptions
    //
    
    const Field<StringA>& StatusDescriptions() const
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        return GetField<StringA>(n);
    }
    
    void StatusDescriptions(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        GetField<StringA>(n) = x;
    }
    
    const StringA& StatusDescriptions_value() const
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        return GetField<StringA>(n).value;
    }
    
    void StatusDescriptions_value(const StringA& x)
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        GetField<StringA>(n).Set(x);
    }
    
    bool StatusDescriptions_exists() const
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void StatusDescriptions_clear()
    {
        const size_t n = offsetof(Self, StatusDescriptions);
        GetField<StringA>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.Status
    //
    
    const Field<String>& Status() const
    {
        const size_t n = offsetof(Self, Status);
        return GetField<String>(n);
    }
    
    void Status(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Status);
        GetField<String>(n) = x;
    }
    
    const String& Status_value() const
    {
        const size_t n = offsetof(Self, Status);
        return GetField<String>(n).value;
    }
    
    void Status_value(const String& x)
    {
        const size_t n = offsetof(Self, Status);
        GetField<String>(n).Set(x);
    }
    
    bool Status_exists() const
    {
        const size_t n = offsetof(Self, Status);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Status_clear()
    {
        const size_t n = offsetof(Self, Status);
        GetField<String>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.HealthState
    //
    
    const Field<Uint16>& HealthState() const
    {
        const size_t n = offsetof(Self, HealthState);
        return GetField<Uint16>(n);
    }
    
    void HealthState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, HealthState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& HealthState_value() const
    {
        const size_t n = offsetof(Self, HealthState);
        return GetField<Uint16>(n).value;
    }
    
    void HealthState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, HealthState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool HealthState_exists() const
    {
        const size_t n = offsetof(Self, HealthState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void HealthState_clear()
    {
        const size_t n = offsetof(Self, HealthState);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.CommunicationStatus
    //
    
    const Field<Uint16>& CommunicationStatus() const
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        return GetField<Uint16>(n);
    }
    
    void CommunicationStatus(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& CommunicationStatus_value() const
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        return GetField<Uint16>(n).value;
    }
    
    void CommunicationStatus_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        GetField<Uint16>(n).Set(x);
    }
    
    bool CommunicationStatus_exists() const
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void CommunicationStatus_clear()
    {
        const size_t n = offsetof(Self, CommunicationStatus);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.DetailedStatus
    //
    
    const Field<Uint16>& DetailedStatus() const
    {
        const size_t n = offsetof(Self, DetailedStatus);
        return GetField<Uint16>(n);
    }
    
    void DetailedStatus(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, DetailedStatus);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& DetailedStatus_value() const
    {
        const size_t n = offsetof(Self, DetailedStatus);
        return GetField<Uint16>(n).value;
    }
    
    void DetailedStatus_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, DetailedStatus);
        GetField<Uint16>(n).Set(x);
    }
    
    bool DetailedStatus_exists() const
    {
        const size_t n = offsetof(Self, DetailedStatus);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void DetailedStatus_clear()
    {
        const size_t n = offsetof(Self, DetailedStatus);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.OperatingStatus
    //
    
    const Field<Uint16>& OperatingStatus() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<Uint16>(n);
    }
    
    void OperatingStatus(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& OperatingStatus_value() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<Uint16>(n).value;
    }
    
    void OperatingStatus_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<Uint16>(n).Set(x);
    }
    
    bool OperatingStatus_exists() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void OperatingStatus_clear()
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_ManagedSystemElement_Class.PrimaryStatus
    //
    
    const Field<Uint16>& PrimaryStatus() const
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        return GetField<Uint16>(n);
    }
    
    void PrimaryStatus(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& PrimaryStatus_value() const
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        return GetField<Uint16>(n).value;
    }
    
    void PrimaryStatus_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        GetField<Uint16>(n).Set(x);
    }
    
    bool PrimaryStatus_exists() const
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void PrimaryStatus_clear()
    {
        const size_t n = offsetof(Self, PrimaryStatus);
        GetField<Uint16>(n).Clear();
    }
};

typedef Array<CIM_ManagedSystemElement_Class> CIM_ManagedSystemElement_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_ManagedSystemElement_h */
