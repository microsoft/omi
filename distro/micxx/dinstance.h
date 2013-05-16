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

#ifndef _micxx_dinstance_h
#define _micxx_dinstance_h

#include <MI.h>
#include "linkage.h"
#include "atomic.h"
#include "memory.h"
#include "micxx_string.h"
#include "array.h"
#include "types.h"
#include "instance.h"

MI_BEGIN_NAMESPACE

typedef class Array<class DInstance> DInstanceA;

#if defined(GetClassName)
# undef GetClassName
#endif

class MICXX_LINKAGE DInstance
{
public:

    enum MetaType { CLASS, ASSOCIATION, INDICATION, METHOD };

    DInstance();

    DInstance(const String& className, MetaType metaType);

    DInstance(const DInstance& x);

    ~DInstance();

    DInstance& operator=(const DInstance& x);

    void Swap(DInstance& x);

    const MI_ClassDecl* GetClassDecl() const;

    String GetClassName() const;

    void SetClassName(const String& className);

    String GetNamespace() const;

    void SetNamespace(const String& nameSpace);

    Uint32 Count() const;

    Uint32 Find(const String& name) const;

    bool GetType(Uint32 index, Type& type) const;

    bool GetName(Uint32 index, String& name) const;

    bool GetFlags(Uint32 index, Uint32& flags) const;

    bool Clear(const String& name);

    bool Clear(Uint32 index);

    bool AddValue(
        const String& name,
        const MI_Value* value,
        Type type,
        bool null,
        bool key);

    bool SetValue(
        const String& name,
        const MI_Value* value,
        Type type,
        bool null);

    bool GetValue(
        const String& name,
        MI_Value* value,
        Type& type,
        bool& null,
        bool& key) const;

    bool GetValueAsType(
        const String& name,
        MI_Value* value,
        Type expectedType,
        bool& null,
        bool& key) const;

    bool AddBoolean(
        const String& name,
        const Boolean& x,
        bool null = false,
        bool key = false);

    bool AddBooleanA(
        const String& name,
        const BooleanA& x,
        bool null = false,
        bool key = false);

    bool AddUint8(
        const String& name,
        const Uint8& x,
        bool null = false,
        bool key = false);

    bool AddUint8A(
        const String& name,
        const Uint8A& x,
        bool null = false,
        bool key = false);

    bool AddSint8(
        const String& name,
        const Sint8& x,
        bool null = false,
        bool key = false);

    bool AddSint8A(
        const String& name,
        const Sint8A& x,
        bool null = false,
        bool key = false);

    bool AddUint16(
        const String& name,
        const Uint16& x,
        bool null = false,
        bool key = false);

    bool AddUint16A(
        const String& name,
        const Uint16A& x,
        bool null = false,
        bool key = false);

    bool AddSint16(
        const String& name,
        const Sint16& x,
        bool null = false,
        bool key = false);

    bool AddSint16A(
        const String& name,
        const Sint16A& x,
        bool null = false,
        bool key = false);

    bool AddUint32(
        const String& name,
        const Uint32& x,
        bool null = false,
        bool key = false);

    bool AddUint32A(
        const String& name,
        const Uint32A& x,
        bool null = false,
        bool key = false);

    bool AddSint32(
        const String& name,
        const Sint32& x,
        bool null = false,
        bool key = false);

    bool AddSint32A(
        const String& name,
        const Sint32A& x,
        bool null = false,
        bool key = false);

    bool AddUint64(
        const String& name,
        const Uint64& x,
        bool null = false,
        bool key = false);

    bool AddUint64A(
        const String& name,
        const Uint64A& x,
        bool null = false,
        bool key = false);

    bool AddSint64(
        const String& name,
        const Sint64& x,
        bool null = false,
        bool key = false);

    bool AddSint64A(
        const String& name,
        const Sint64A& x,
        bool null = false,
        bool key = false);

    bool AddReal32(
        const String& name,
        const Real32& x,
        bool null = false,
        bool key = false);

    bool AddReal32A(
        const String& name,
        const Real32A& x,
        bool null = false,
        bool key = false);

    bool AddReal64(
        const String& name,
        const Real64& x,
        bool null = false,
        bool key = false);

    bool AddReal64A(
        const String& name,
        const Real64A& x,
        bool null = false,
        bool key = false);

    bool AddChar16(
        const String& name,
        const Char16& x,
        bool null = false,
        bool key = false);

    bool AddChar16A(
        const String& name,
        const Char16A& x,
        bool null = false,
        bool key = false);

    bool AddDatetime(
        const String& name,
        const Datetime& x,
        bool null = false,
        bool key = false);

    bool AddDatetimeA(
        const String& name,
        const DatetimeA& x,
        bool null = false,
        bool key = false);

    bool AddString(
        const String& name,
        const String& x,
        bool null = false,
        bool key = false);

    bool AddStringA(
        const String& name,
        const StringA& x,
        bool null = false,
        bool key = false);

    bool AddReference(
        const String& name,
        const DInstance& x,
        bool null = false,
        bool key = false);

    bool AddReferenceA(
        const String& name,
        const DInstanceA& x,
        bool null = false,
        bool key = false);

    bool AddInstance(
        const String& name,
        const DInstance& x,
        bool null = false,
        bool key = false);

    bool AddInstanceA(
        const String& name,
        const DInstanceA& x,
        bool null = false,
        bool key = false);

    bool SetBoolean(
        const String& name,
        const Boolean& x,
        bool null = false);

    bool SetBooleanA(
        const String& name,
        const BooleanA& x,
        bool null = false);

    bool SetUint8(
        const String& name,
        const Uint8& x,
        bool null = false);

    bool SetUint8A(
        const String& name,
        const Uint8A& x,
        bool null = false);

    bool SetSint8(
        const String& name,
        const Sint8& x,
        bool null = false);

    bool SetSint8A(
        const String& name,
        const Sint8A& x,
        bool null = false);

    bool SetUint16(
        const String& name,
        const Uint16& x,
        bool null = false);

    bool SetUint16A(
        const String& name,
        const Uint16A& x,
        bool null = false);

    bool SetSint16(
        const String& name,
        const Sint16& x,
        bool null = false);

    bool SetSint16A(
        const String& name,
        const Sint16A& x,
        bool null = false);

    bool SetUint32(
        const String& name,
        const Uint32& x,
        bool null = false);

    bool SetUint32A(
        const String& name,
        const Uint32A& x,
        bool null = false);

    bool SetSint32(
        const String& name,
        const Sint32& x,
        bool null = false);

    bool SetSint32A(
        const String& name,
        const Sint32A& x,
        bool null = false);

    bool SetUint64(
        const String& name,
        const Uint64& x,
        bool null = false);

    bool SetUint64A(
        const String& name,
        const Uint64A& x,
        bool null = false);

    bool SetSint64(
        const String& name,
        const Sint64& x,
        bool null = false);

    bool SetSint64A(
        const String& name,
        const Sint64A& x,
        bool null = false);

    bool SetReal32(
        const String& name,
        const Real32& x,
        bool null = false);

    bool SetReal32A(
        const String& name,
        const Real32A& x,
        bool null = false);

    bool SetReal64(
        const String& name,
        const Real64& x,
        bool null = false);

    bool SetReal64A(
        const String& name,
        const Real64A& x,
        bool null = false);

    bool SetChar16(
        const String& name,
        const Char16& x,
        bool null = false);

    bool SetChar16A(
        const String& name,
        const Char16A& x,
        bool null = false);

    bool SetDatetime(
        const String& name,
        const Datetime& x,
        bool null = false);

    bool SetDatetimeA(
        const String& name,
        const DatetimeA& x,
        bool null = false);

    bool SetString(
        const String& name,
        const String& x,
        bool null = false);

    bool SetStringA(
        const String& name,
        const StringA& x,
        bool null = false);

    bool SetReference(
        const String& name,
        const DInstance& x,
        bool null = false);

    bool SetReferenceA(
        const String& name,
        const DInstanceA& x,
        bool null = false);

    bool SetInstance(
        const String& name,
        const DInstance& x,
        bool null = false);

    bool SetInstanceA(
        const String& name,
        const DInstanceA& x,
        bool null = false);

    bool GetBoolean(
        const String& name,
        Boolean& x,
        bool& null,
        bool& key) const;

    bool GetBooleanA(
        const String& name,
        BooleanA& x,
        bool& null,
        bool& key) const;

    bool GetUint8(
        const String& name,
        Uint8& x,
        bool& null,
        bool& key) const;

    bool GetUint8A(
        const String& name,
        Uint8A& x,
        bool& null,
        bool& key) const;

    bool GetSint8(
        const String& name,
        Sint8& x,
        bool& null,
        bool& key) const;

    bool GetSint8A(
        const String& name,
        Sint8A& x,
        bool& null,
        bool& key) const;

    bool GetUint16(
        const String& name,
        Uint16& x,
        bool& null,
        bool& key) const;

    bool GetUint16A(
        const String& name,
        Uint16A& x,
        bool& null,
        bool& key) const;

    bool GetSint16(
        const String& name,
        Sint16& x,
        bool& null,
        bool& key) const;

    bool GetSint16A(
        const String& name,
        Sint16A& x,
        bool& null,
        bool& key) const;

    bool GetUint32(
        const String& name,
        Uint32& x,
        bool& null,
        bool& key) const;

    bool GetUint32A(
        const String& name,
        Uint32A& x,
        bool& null,
        bool& key) const;

    bool GetSint32(
        const String& name,
        Sint32& x,
        bool& null,
        bool& key) const;

    bool GetSint32A(
        const String& name,
        Sint32A& x,
        bool& null,
        bool& key) const;

    bool GetUint64(
        const String& name,
        Uint64& x,
        bool& null,
        bool& key) const;

    bool GetUint64A(
        const String& name,
        Uint64A& x,
        bool& null,
        bool& key) const;

    bool GetSint64(
        const String& name,
        Sint64& x,
        bool& null,
        bool& key) const;

    bool GetSint64A(
        const String& name,
        Sint64A& x,
        bool& null,
        bool& key) const;

    bool GetReal32(
        const String& name,
        Real32& x,
        bool& null,
        bool& key) const;

    bool GetReal32A(
        const String& name,
        Real32A& x,
        bool& null,
        bool& key) const;

    bool GetReal64(
        const String& name,
        Real64& x,
        bool& null,
        bool& key) const;

    bool GetReal64A(
        const String& name,
        Real64A& x,
        bool& null,
        bool& key) const;

    bool GetChar16(
        const String& name,
        Char16& x,
        bool& null,
        bool& key) const;

    bool GetChar16A(
        const String& name,
        Char16A& x,
        bool& null,
        bool& key) const;

    bool GetDatetime(
        const String& name,
        Datetime& x,
        bool& null,
        bool& key) const;

    bool GetDatetimeA(
        const String& name,
        DatetimeA& x,
        bool& null,
        bool& key) const;

    bool GetString(
        const String& name,
        String& x,
        bool& null,
        bool& key) const;

    bool GetStringA(
        const String& name,
        StringA& x,
        bool& null,
        bool& key) const;

    bool GetReference(
        const String& name,
        DInstance& x,
        bool& null,
        bool& key) const;

    bool GetReferenceA(
        const String& name,
        DInstanceA& x,
        bool& null,
        bool& key) const;

    bool GetInstance(
        const String& name,
        DInstance& x,
        bool& null,
        bool& key) const;

    bool GetInstanceA(
        const String& name,
        DInstanceA& x,
        bool& null,
        bool& key) const;

    bool GetBoolean(const String& name, Boolean& x) const;
    bool GetBooleanA(const String& name, BooleanA& x) const;
    bool GetUint8(const String& name, Uint8& x) const;
    bool GetUint8A(const String& name, Uint8A& x) const;
    bool GetSint8(const String& name, Sint8& x) const;
    bool GetSint8A(const String& name, Sint8A& x) const;
    bool GetUint16(const String& name, Uint16& x) const;
    bool GetUint16A(const String& name, Uint16A& x) const;
    bool GetSint16(const String& name, Sint16& x) const;
    bool GetSint16A(const String& name, Sint16A& x) const;
    bool GetUint32(const String& name, Uint32& x) const;
    bool GetUint32A(const String& name, Uint32A& x) const;
    bool GetSint32(const String& name, Sint32& x) const;
    bool GetSint32A(const String& name, Sint32A& x) const;
    bool GetUint64(const String& name, Uint64& x) const;
    bool GetUint64A(const String& name, Uint64A& x) const;
    bool GetSint64(const String& name, Sint64& x) const;
    bool GetSint64A(const String& name, Sint64A& x) const;
    bool GetReal32(const String& name, Real32& x) const;
    bool GetReal32A(const String& name, Real32A& x) const;
    bool GetReal64(const String& name, Real64& x) const;
    bool GetReal64A(const String& name, Real64A& x) const;
    bool GetChar16(const String& name, Char16& x) const;
    bool GetChar16A(const String& name, Char16A& x) const;
    bool GetDatetime(const String& name, Datetime& x) const;
    bool GetDatetimeA(const String& name, DatetimeA& x) const;
    bool GetString(const String& name, String& x) const;
    bool GetStringA(const String& name, StringA& x) const;
    bool GetReference(const String& name, DInstance& x) const;
    bool GetReferenceA(const String& name, DInstanceA& x) const;
    bool GetInstance(const String& name, DInstance& x) const;
    bool GetInstanceA(const String& name, DInstanceA& x) const;

    void Print(
        FILE* os = stdout,
        MI_Uint32 level = 0,
        bool showNulls = true) const;

    static bool DynamicToStatic(
        const DInstance& dynamicInstance,
        bool keysOnly,
        bool ignoreUnknownProperties,
        Instance& staticInstance);

    static bool StaticToDynamic(
        const Instance& sinst,
        bool keysOnly,
        DInstance& dinst);

private:

    enum AdoptTag { ADOPT };
    explicit DInstance(MI_Instance* self, AdoptTag);

    enum CloneTag { CLONE };
    explicit DInstance(MI_Instance* self, CloneTag);

    void COW();
    MI_Instance* m_self;
    friend class DValue;
    friend class ClientRep;
    friend class DInstanceFriend;
};

inline bool DInstance::AddBoolean(
    const String& name,
    const Boolean& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_BOOLEAN, null, key);
}

inline bool DInstance::AddBooleanA(
    const String& name,
    const BooleanA& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_BOOLEANA, null, key);
}

inline bool DInstance::AddUint8(
    const String& name,
    const Uint8& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT8, null, key);
}

inline bool DInstance::AddUint8A(
    const String& name,
    const Uint8A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT8A, null, key);
}

inline bool DInstance::AddSint8(
    const String& name,
    const Sint8& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT8, null, key);
}

inline bool DInstance::AddSint8A(
    const String& name,
    const Sint8A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT8A, null, key);
}

inline bool DInstance::AddUint16(
    const String& name,
    const Uint16& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT16, null, key);
}

inline bool DInstance::AddUint16A(
    const String& name,
    const Uint16A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT16A, null, key);
}

inline bool DInstance::AddSint16(
    const String& name,
    const Sint16& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT16, null, key);
}

inline bool DInstance::AddSint16A(
    const String& name,
    const Sint16A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT16A, null, key);
}

inline bool DInstance::AddUint32(
    const String& name,
    const Uint32& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT32, null, key);
}

inline bool DInstance::AddUint32A(
    const String& name,
    const Uint32A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT32A, null, key);
}

inline bool DInstance::AddSint32(
    const String& name,
    const Sint32& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT32, null, key);
}

inline bool DInstance::AddSint32A(
    const String& name,
    const Sint32A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT32A, null, key);
}

inline bool DInstance::AddUint64(
    const String& name,
    const Uint64& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT64, null, key);
}

inline bool DInstance::AddUint64A(
    const String& name,
    const Uint64A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_UINT64A, null, key);
}

inline bool DInstance::AddSint64(
    const String& name,
    const Sint64& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT64, null, key);
}

inline bool DInstance::AddSint64A(
    const String& name,
    const Sint64A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_SINT64A, null, key);
}

inline bool DInstance::AddReal32(
    const String& name,
    const Real32& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REAL32, null, key);
}

inline bool DInstance::AddReal32A(
    const String& name,
    const Real32A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REAL32A, null, key);
}

inline bool DInstance::AddReal64(
    const String& name,
    const Real64& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REAL64, null, key);
}

inline bool DInstance::AddReal64A(
    const String& name,
    const Real64A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REAL64A, null, key);
}

inline bool DInstance::AddChar16(
    const String& name,
    const Char16& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_CHAR16, null, key);
}

inline bool DInstance::AddChar16A(
    const String& name,
    const Char16A& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_CHAR16A, null, key);
}

inline bool DInstance::AddDatetime(
    const String& name,
    const Datetime& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_DATETIME, null, key);
}

inline bool DInstance::AddDatetimeA(
    const String& name,
    const DatetimeA& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_DATETIMEA, null, key);
}

inline bool DInstance::AddString(
    const String& name,
    const String& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_STRING, null, key);
}

inline bool DInstance::AddStringA(
    const String& name,
    const StringA& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_STRINGA, null, key);
}

inline bool DInstance::AddReference(
    const String& name,
    const DInstance& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REFERENCE, null, key);
}

inline bool DInstance::AddReferenceA(
    const String& name,
    const DInstanceA& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_REFERENCEA, null, key);
}

inline bool DInstance::AddInstance(
    const String& name,
    const DInstance& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_INSTANCE, null, key);
}

inline bool DInstance::AddInstanceA(
    const String& name,
    const DInstanceA& x,
    bool null,
    bool key)
{
    return AddValue(name, (MI_Value*)&x, MI_INSTANCEA, null, key);
}

inline bool DInstance::SetBoolean(
    const String& name,
    const Boolean& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_BOOLEAN, null);
}

inline bool DInstance::SetBooleanA(
    const String& name,
    const BooleanA& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_BOOLEANA, null);
}

inline bool DInstance::SetUint8(
    const String& name,
    const Uint8& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT8, null);
}

inline bool DInstance::SetUint8A(
    const String& name,
    const Uint8A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT8A, null);
}

inline bool DInstance::SetSint8(
    const String& name,
    const Sint8& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT8, null);
}

inline bool DInstance::SetSint8A(
    const String& name,
    const Sint8A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT8A, null);
}

inline bool DInstance::SetUint16(
    const String& name,
    const Uint16& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT16, null);
}

inline bool DInstance::SetUint16A(
    const String& name,
    const Uint16A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT16A, null);
}

inline bool DInstance::SetSint16(
    const String& name,
    const Sint16& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT16, null);
}

inline bool DInstance::SetSint16A(
    const String& name,
    const Sint16A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT16A, null);
}

inline bool DInstance::SetUint32(
    const String& name,
    const Uint32& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT32, null);
}

inline bool DInstance::SetUint32A(
    const String& name,
    const Uint32A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT32A, null);
}

inline bool DInstance::SetSint32(
    const String& name,
    const Sint32& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT32, null);
}

inline bool DInstance::SetSint32A(
    const String& name,
    const Sint32A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT32A, null);
}

inline bool DInstance::SetUint64(
    const String& name,
    const Uint64& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT64, null);
}

inline bool DInstance::SetUint64A(
    const String& name,
    const Uint64A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_UINT64A, null);
}

inline bool DInstance::SetSint64(
    const String& name,
    const Sint64& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT64, null);
}

inline bool DInstance::SetSint64A(
    const String& name,
    const Sint64A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_SINT64A, null);
}

inline bool DInstance::SetReal32(
    const String& name,
    const Real32& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REAL32, null);
}

inline bool DInstance::SetReal32A(
    const String& name,
    const Real32A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REAL32A, null);
}

inline bool DInstance::SetReal64(
    const String& name,
    const Real64& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REAL64, null);
}

inline bool DInstance::SetReal64A(
    const String& name,
    const Real64A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REAL64A, null);
}

inline bool DInstance::SetChar16(
    const String& name,
    const Char16& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_CHAR16, null);
}

inline bool DInstance::SetChar16A(
    const String& name,
    const Char16A& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_CHAR16A, null);
}

inline bool DInstance::SetDatetime(
    const String& name,
    const Datetime& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_DATETIME, null);
}

inline bool DInstance::SetDatetimeA(
    const String& name,
    const DatetimeA& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_DATETIMEA, null);
}

inline bool DInstance::SetString(
    const String& name,
    const String& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_STRING, null);
}

inline bool DInstance::SetStringA(
    const String& name,
    const StringA& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_STRINGA, null);
}

inline bool DInstance::SetReference(
    const String& name,
    const DInstance& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REFERENCE, null);
}

inline bool DInstance::SetReferenceA(
    const String& name,
    const DInstanceA& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_REFERENCEA, null);
}

inline bool DInstance::SetInstance(
    const String& name,
    const DInstance& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_INSTANCE, null);
}

inline bool DInstance::SetInstanceA(
    const String& name,
    const DInstanceA& x,
    bool null)
{
    return SetValue(name, (MI_Value*)&x, MI_INSTANCEA, null);
}

inline bool DInstance::GetBoolean(const String& name, Boolean& x) const
{
    bool dummy;
    return GetBoolean(name, x, dummy, dummy);
}

inline bool DInstance::GetBooleanA(const String& name, BooleanA& x) const
{
    bool dummy;
    return GetBooleanA(name, x, dummy, dummy);
}

inline bool DInstance::GetUint8(const String& name, Uint8& x) const
{
    bool dummy;
    return GetUint8(name, x, dummy, dummy);
}

inline bool DInstance::GetUint8A(const String& name, Uint8A& x) const
{
    bool dummy;
    return GetUint8A(name, x, dummy, dummy);
}

inline bool DInstance::GetSint8(const String& name, Sint8& x) const
{
    bool dummy;
    return GetSint8(name, x, dummy, dummy);
}

inline bool DInstance::GetSint8A(const String& name, Sint8A& x) const
{
    bool dummy;
    return GetSint8A(name, x, dummy, dummy);
}

inline bool DInstance::GetUint16(const String& name, Uint16& x) const
{
    bool dummy;
    return GetUint16(name, x, dummy, dummy);
}

inline bool DInstance::GetUint16A(const String& name, Uint16A& x) const
{
    bool dummy;
    return GetUint16A(name, x, dummy, dummy);
}

inline bool DInstance::GetSint16(const String& name, Sint16& x) const
{
    bool dummy;
    return GetSint16(name, x, dummy, dummy);
}

inline bool DInstance::GetSint16A(const String& name, Sint16A& x) const
{
    bool dummy;
    return GetSint16A(name, x, dummy, dummy);
}

inline bool DInstance::GetUint32(const String& name, Uint32& x) const
{
    bool dummy;
    return GetUint32(name, x, dummy, dummy);
}

inline bool DInstance::GetUint32A(const String& name, Uint32A& x) const
{
    bool dummy;
    return GetUint32A(name, x, dummy, dummy);
}

inline bool DInstance::GetSint32(const String& name, Sint32& x) const
{
    bool dummy;
    return GetSint32(name, x, dummy, dummy);
}

inline bool DInstance::GetSint32A(const String& name, Sint32A& x) const
{
    bool dummy;
    return GetSint32A(name, x, dummy, dummy);
}

inline bool DInstance::GetUint64(const String& name, Uint64& x) const
{
    bool dummy;
    return GetUint64(name, x, dummy, dummy);
}

inline bool DInstance::GetUint64A(const String& name, Uint64A& x) const
{
    bool dummy;
    return GetUint64A(name, x, dummy, dummy);
}

inline bool DInstance::GetSint64(const String& name, Sint64& x) const
{
    bool dummy;
    return GetSint64(name, x, dummy, dummy);
}

inline bool DInstance::GetSint64A(const String& name, Sint64A& x) const
{
    bool dummy;
    return GetSint64A(name, x, dummy, dummy);
}

inline bool DInstance::GetReal32(const String& name, Real32& x) const
{
    bool dummy;
    return GetReal32(name, x, dummy, dummy);
}

inline bool DInstance::GetReal32A(const String& name, Real32A& x) const
{
    bool dummy;
    return GetReal32A(name, x, dummy, dummy);
}

inline bool DInstance::GetReal64(const String& name, Real64& x) const
{
    bool dummy;
    return GetReal64(name, x, dummy, dummy);
}

inline bool DInstance::GetReal64A(const String& name, Real64A& x) const
{
    bool dummy;
    return GetReal64A(name, x, dummy, dummy);
}

inline bool DInstance::GetChar16(const String& name, Char16& x) const
{
    bool dummy;
    return GetChar16(name, x, dummy, dummy);
}

inline bool DInstance::GetChar16A(const String& name, Char16A& x) const
{
    bool dummy;
    return GetChar16A(name, x, dummy, dummy);
}

inline bool DInstance::GetDatetime(const String& name, Datetime& x) const
{
    bool dummy;
    return GetDatetime(name, x, dummy, dummy);
}

inline bool DInstance::GetDatetimeA(const String& name, DatetimeA& x) const
{
    bool dummy;
    return GetDatetimeA(name, x, dummy, dummy);
}

inline bool DInstance::GetString(const String& name, String& x) const
{
    bool dummy;
    return GetString(name, x, dummy, dummy);
}

inline bool DInstance::GetStringA(const String& name, StringA& x) const
{
    bool dummy;
    return GetStringA(name, x, dummy, dummy);
}

inline bool DInstance::GetReference(const String& name, DInstance& x) const
{
    bool dummy;
    return GetReference(name, x, dummy, dummy);
}

inline bool DInstance::GetReferenceA(const String& name, DInstanceA& x) const
{
    bool dummy;
    return GetReferenceA(name, x, dummy, dummy);
}

inline bool DInstance::GetInstance(const String& name, DInstance& x) const
{
    bool dummy;
    return GetInstance(name, x, dummy, dummy);
}

inline bool DInstance::GetInstanceA(const String& name, DInstanceA& x) const
{
    bool dummy;
    return GetInstanceA(name, x, dummy, dummy);
}

MI_END_NAMESPACE

#endif /* _micxx_dinstance_h */
