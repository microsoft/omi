/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Error_h
#define _CIM_Error_h

#include <MI.h>

/*
**==============================================================================
**
** CIM_Error [CIM_Error]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Error
{
    MI_Instance __instance;
    /* CIM_Error properties */
    MI_ConstUint16Field ErrorType;
    MI_ConstStringField OtherErrorType;
    MI_ConstStringField OwningEntity;
    MI_ConstStringField MessageID;
    MI_ConstStringField Message;
    MI_ConstStringAField MessageArguments;
    MI_ConstUint16Field PerceivedSeverity;
    MI_ConstUint16Field ProbableCause;
    MI_ConstStringField ProbableCauseDescription;
    MI_ConstStringAField RecommendedActions;
    MI_ConstStringField ErrorSource;
    MI_ConstUint16Field ErrorSourceFormat;
    MI_ConstStringField OtherErrorSourceFormat;
    MI_ConstUint32Field CIMStatusCode;
    MI_ConstStringField CIMStatusCodeDescription;
}
CIM_Error;

typedef struct _CIM_Error_Ref
{
    CIM_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_Ref;

typedef struct _CIM_Error_ConstRef
{
    MI_CONST CIM_Error* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ConstRef;

typedef struct _CIM_Error_Array
{
    struct _CIM_Error** data;
    MI_Uint32 size;
}
CIM_Error_Array;

typedef struct _CIM_Error_ConstArray
{
    struct _CIM_Error MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Error_ConstArray;

typedef struct _CIM_Error_ArrayRef
{
    CIM_Error_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ArrayRef;

typedef struct _CIM_Error_ConstArrayRef
{
    CIM_Error_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Error_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Error_rtti;


/*
**==============================================================================
**
** CIM_Error_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_Error_Class : public Instance
{
public:
    
    typedef CIM_Error Self;
    
    CIM_Error_Class() :
        Instance(&CIM_Error_rtti)
    {
    }
    
    CIM_Error_Class(
        const CIM_Error* instanceName,
        bool keysOnly) :
        Instance(
            &CIM_Error_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_Error_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    CIM_Error_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    CIM_Error_Class& operator=(
        const CIM_Error_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_Error_Class(
        const CIM_Error_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_Error_rtti;
    }

    //
    // CIM_Error_Class.ErrorType
    //
    
    const Field<Uint16>& ErrorType() const
    {
        const size_t n = offsetof(Self, ErrorType);
        return GetField<Uint16>(n);
    }
    
    void ErrorType(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, ErrorType);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& ErrorType_value() const
    {
        const size_t n = offsetof(Self, ErrorType);
        return GetField<Uint16>(n).value;
    }
    
    void ErrorType_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, ErrorType);
        GetField<Uint16>(n).Set(x);
    }
    
    bool ErrorType_exists() const
    {
        const size_t n = offsetof(Self, ErrorType);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void ErrorType_clear()
    {
        const size_t n = offsetof(Self, ErrorType);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Error_Class.OtherErrorType
    //
    
    const Field<String>& OtherErrorType() const
    {
        const size_t n = offsetof(Self, OtherErrorType);
        return GetField<String>(n);
    }
    
    void OtherErrorType(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OtherErrorType);
        GetField<String>(n) = x;
    }
    
    const String& OtherErrorType_value() const
    {
        const size_t n = offsetof(Self, OtherErrorType);
        return GetField<String>(n).value;
    }
    
    void OtherErrorType_value(const String& x)
    {
        const size_t n = offsetof(Self, OtherErrorType);
        GetField<String>(n).Set(x);
    }
    
    bool OtherErrorType_exists() const
    {
        const size_t n = offsetof(Self, OtherErrorType);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OtherErrorType_clear()
    {
        const size_t n = offsetof(Self, OtherErrorType);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.OwningEntity
    //
    
    const Field<String>& OwningEntity() const
    {
        const size_t n = offsetof(Self, OwningEntity);
        return GetField<String>(n);
    }
    
    void OwningEntity(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OwningEntity);
        GetField<String>(n) = x;
    }
    
    const String& OwningEntity_value() const
    {
        const size_t n = offsetof(Self, OwningEntity);
        return GetField<String>(n).value;
    }
    
    void OwningEntity_value(const String& x)
    {
        const size_t n = offsetof(Self, OwningEntity);
        GetField<String>(n).Set(x);
    }
    
    bool OwningEntity_exists() const
    {
        const size_t n = offsetof(Self, OwningEntity);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OwningEntity_clear()
    {
        const size_t n = offsetof(Self, OwningEntity);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.MessageID
    //
    
    const Field<String>& MessageID() const
    {
        const size_t n = offsetof(Self, MessageID);
        return GetField<String>(n);
    }
    
    void MessageID(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MessageID);
        GetField<String>(n) = x;
    }
    
    const String& MessageID_value() const
    {
        const size_t n = offsetof(Self, MessageID);
        return GetField<String>(n).value;
    }
    
    void MessageID_value(const String& x)
    {
        const size_t n = offsetof(Self, MessageID);
        GetField<String>(n).Set(x);
    }
    
    bool MessageID_exists() const
    {
        const size_t n = offsetof(Self, MessageID);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MessageID_clear()
    {
        const size_t n = offsetof(Self, MessageID);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.Message
    //
    
    const Field<String>& Message() const
    {
        const size_t n = offsetof(Self, Message);
        return GetField<String>(n);
    }
    
    void Message(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Message);
        GetField<String>(n) = x;
    }
    
    const String& Message_value() const
    {
        const size_t n = offsetof(Self, Message);
        return GetField<String>(n).value;
    }
    
    void Message_value(const String& x)
    {
        const size_t n = offsetof(Self, Message);
        GetField<String>(n).Set(x);
    }
    
    bool Message_exists() const
    {
        const size_t n = offsetof(Self, Message);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Message_clear()
    {
        const size_t n = offsetof(Self, Message);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.MessageArguments
    //
    
    const Field<StringA>& MessageArguments() const
    {
        const size_t n = offsetof(Self, MessageArguments);
        return GetField<StringA>(n);
    }
    
    void MessageArguments(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, MessageArguments);
        GetField<StringA>(n) = x;
    }
    
    const StringA& MessageArguments_value() const
    {
        const size_t n = offsetof(Self, MessageArguments);
        return GetField<StringA>(n).value;
    }
    
    void MessageArguments_value(const StringA& x)
    {
        const size_t n = offsetof(Self, MessageArguments);
        GetField<StringA>(n).Set(x);
    }
    
    bool MessageArguments_exists() const
    {
        const size_t n = offsetof(Self, MessageArguments);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void MessageArguments_clear()
    {
        const size_t n = offsetof(Self, MessageArguments);
        GetField<StringA>(n).Clear();
    }

    //
    // CIM_Error_Class.PerceivedSeverity
    //
    
    const Field<Uint16>& PerceivedSeverity() const
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        return GetField<Uint16>(n);
    }
    
    void PerceivedSeverity(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& PerceivedSeverity_value() const
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        return GetField<Uint16>(n).value;
    }
    
    void PerceivedSeverity_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        GetField<Uint16>(n).Set(x);
    }
    
    bool PerceivedSeverity_exists() const
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void PerceivedSeverity_clear()
    {
        const size_t n = offsetof(Self, PerceivedSeverity);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Error_Class.ProbableCause
    //
    
    const Field<Uint16>& ProbableCause() const
    {
        const size_t n = offsetof(Self, ProbableCause);
        return GetField<Uint16>(n);
    }
    
    void ProbableCause(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, ProbableCause);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& ProbableCause_value() const
    {
        const size_t n = offsetof(Self, ProbableCause);
        return GetField<Uint16>(n).value;
    }
    
    void ProbableCause_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, ProbableCause);
        GetField<Uint16>(n).Set(x);
    }
    
    bool ProbableCause_exists() const
    {
        const size_t n = offsetof(Self, ProbableCause);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void ProbableCause_clear()
    {
        const size_t n = offsetof(Self, ProbableCause);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Error_Class.ProbableCauseDescription
    //
    
    const Field<String>& ProbableCauseDescription() const
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        return GetField<String>(n);
    }
    
    void ProbableCauseDescription(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        GetField<String>(n) = x;
    }
    
    const String& ProbableCauseDescription_value() const
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        return GetField<String>(n).value;
    }
    
    void ProbableCauseDescription_value(const String& x)
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        GetField<String>(n).Set(x);
    }
    
    bool ProbableCauseDescription_exists() const
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ProbableCauseDescription_clear()
    {
        const size_t n = offsetof(Self, ProbableCauseDescription);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.RecommendedActions
    //
    
    const Field<StringA>& RecommendedActions() const
    {
        const size_t n = offsetof(Self, RecommendedActions);
        return GetField<StringA>(n);
    }
    
    void RecommendedActions(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, RecommendedActions);
        GetField<StringA>(n) = x;
    }
    
    const StringA& RecommendedActions_value() const
    {
        const size_t n = offsetof(Self, RecommendedActions);
        return GetField<StringA>(n).value;
    }
    
    void RecommendedActions_value(const StringA& x)
    {
        const size_t n = offsetof(Self, RecommendedActions);
        GetField<StringA>(n).Set(x);
    }
    
    bool RecommendedActions_exists() const
    {
        const size_t n = offsetof(Self, RecommendedActions);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void RecommendedActions_clear()
    {
        const size_t n = offsetof(Self, RecommendedActions);
        GetField<StringA>(n).Clear();
    }

    //
    // CIM_Error_Class.ErrorSource
    //
    
    const Field<String>& ErrorSource() const
    {
        const size_t n = offsetof(Self, ErrorSource);
        return GetField<String>(n);
    }
    
    void ErrorSource(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ErrorSource);
        GetField<String>(n) = x;
    }
    
    const String& ErrorSource_value() const
    {
        const size_t n = offsetof(Self, ErrorSource);
        return GetField<String>(n).value;
    }
    
    void ErrorSource_value(const String& x)
    {
        const size_t n = offsetof(Self, ErrorSource);
        GetField<String>(n).Set(x);
    }
    
    bool ErrorSource_exists() const
    {
        const size_t n = offsetof(Self, ErrorSource);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ErrorSource_clear()
    {
        const size_t n = offsetof(Self, ErrorSource);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.ErrorSourceFormat
    //
    
    const Field<Uint16>& ErrorSourceFormat() const
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        return GetField<Uint16>(n);
    }
    
    void ErrorSourceFormat(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& ErrorSourceFormat_value() const
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        return GetField<Uint16>(n).value;
    }
    
    void ErrorSourceFormat_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        GetField<Uint16>(n).Set(x);
    }
    
    bool ErrorSourceFormat_exists() const
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void ErrorSourceFormat_clear()
    {
        const size_t n = offsetof(Self, ErrorSourceFormat);
        GetField<Uint16>(n).Clear();
    }

    //
    // CIM_Error_Class.OtherErrorSourceFormat
    //
    
    const Field<String>& OtherErrorSourceFormat() const
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        return GetField<String>(n);
    }
    
    void OtherErrorSourceFormat(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        GetField<String>(n) = x;
    }
    
    const String& OtherErrorSourceFormat_value() const
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        return GetField<String>(n).value;
    }
    
    void OtherErrorSourceFormat_value(const String& x)
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        GetField<String>(n).Set(x);
    }
    
    bool OtherErrorSourceFormat_exists() const
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OtherErrorSourceFormat_clear()
    {
        const size_t n = offsetof(Self, OtherErrorSourceFormat);
        GetField<String>(n).Clear();
    }

    //
    // CIM_Error_Class.CIMStatusCode
    //
    
    const Field<Uint32>& CIMStatusCode() const
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        return GetField<Uint32>(n);
    }
    
    void CIMStatusCode(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& CIMStatusCode_value() const
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        return GetField<Uint32>(n).value;
    }
    
    void CIMStatusCode_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        GetField<Uint32>(n).Set(x);
    }
    
    bool CIMStatusCode_exists() const
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void CIMStatusCode_clear()
    {
        const size_t n = offsetof(Self, CIMStatusCode);
        GetField<Uint32>(n).Clear();
    }

    //
    // CIM_Error_Class.CIMStatusCodeDescription
    //
    
    const Field<String>& CIMStatusCodeDescription() const
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        return GetField<String>(n);
    }
    
    void CIMStatusCodeDescription(const Field<String>& x)
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        GetField<String>(n) = x;
    }
    
    const String& CIMStatusCodeDescription_value() const
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        return GetField<String>(n).value;
    }
    
    void CIMStatusCodeDescription_value(const String& x)
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        GetField<String>(n).Set(x);
    }
    
    bool CIMStatusCodeDescription_exists() const
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        return GetField<String>(n).exists ? true : false;
    }
    
    void CIMStatusCodeDescription_clear()
    {
        const size_t n = offsetof(Self, CIMStatusCodeDescription);
        GetField<String>(n).Clear();
    }
};

typedef Array<CIM_Error_Class> CIM_Error_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_Error_h */
