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
#ifndef _MSFT_AllTypes_h
#define _MSFT_AllTypes_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_AllTypes [MSFT_AllTypes]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_AllTypes
{
    MI_Instance __instance;
    /* MSFT_AllTypes properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstBooleanField BooleanValue;
    MI_ConstUint8Field Uint8Value;
    MI_ConstSint8Field Sint8Value;
    MI_ConstUint16Field Uint16Value;
    MI_ConstSint16Field Sint16Value;
    MI_ConstUint32Field Uint32Value;
    MI_ConstSint32Field Sint32Value;
    MI_ConstUint64Field Uint64Value;
    MI_ConstSint64Field Sint64Value;
    MI_ConstReal32Field Real32Value;
    MI_ConstReal64Field Real64Value;
    MI_ConstChar16Field Char16Value;
    MI_ConstDatetimeField TimestampValue;
    MI_ConstDatetimeField IntervalValue;
    MI_ConstStringField StringValue;
    MI_ConstBooleanAField BooleanArray;
    MI_ConstUint8AField Uint8Array;
    MI_ConstSint8AField Sint8Array;
    MI_ConstUint16AField Uint16Array;
    MI_ConstSint16AField Sint16Array;
    MI_ConstUint32AField Uint32Array;
    MI_ConstSint32AField Sint32Array;
    MI_ConstUint64AField Uint64Array;
    MI_ConstSint64AField Sint64Array;
    MI_ConstReal32AField Real32Array;
    MI_ConstReal64AField Real64Array;
    MI_ConstChar16AField Char16Array;
    MI_ConstDatetimeAField DatetimeArray;
    MI_ConstStringAField StringArray;
}
MSFT_AllTypes;

typedef struct _MSFT_AllTypes_Ref
{
    MSFT_AllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AllTypes_Ref;

typedef struct _MSFT_AllTypes_ConstRef
{
    MI_CONST MSFT_AllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AllTypes_ConstRef;

typedef struct _MSFT_AllTypes_Array
{
    struct _MSFT_AllTypes** data;
    MI_Uint32 size;
}
MSFT_AllTypes_Array;

typedef struct _MSFT_AllTypes_ConstArray
{
    struct _MSFT_AllTypes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_AllTypes_ConstArray;

typedef struct _MSFT_AllTypes_ArrayRef
{
    MSFT_AllTypes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AllTypes_ArrayRef;

typedef struct _MSFT_AllTypes_ConstArrayRef
{
    MSFT_AllTypes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_AllTypes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_AllTypes_rtti;


/*
**==============================================================================
**
** MSFT_AllTypes_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_AllTypes_Class : public Instance
{
public:
    
    typedef MSFT_AllTypes Self;
    
    MSFT_AllTypes_Class() :
        Instance(&MSFT_AllTypes_rtti)
    {
    }
    
    MSFT_AllTypes_Class(
        const MSFT_AllTypes* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_AllTypes_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_AllTypes_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_AllTypes_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_AllTypes_Class& operator=(
        const MSFT_AllTypes_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_AllTypes_Class(
        const MSFT_AllTypes_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_AllTypes_rtti;
    }

    //
    // MSFT_AllTypes_Class.Key
    //
    
    const Field<Uint32>& Key() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n);
    }
    
    void Key(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Key_value() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).value;
    }
    
    void Key_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Key_exists() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Key_clear()
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.BooleanValue
    //
    
    const Field<Boolean>& BooleanValue() const
    {
        const size_t n = offsetof(Self, BooleanValue);
        return GetField<Boolean>(n);
    }
    
    void BooleanValue(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, BooleanValue);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& BooleanValue_value() const
    {
        const size_t n = offsetof(Self, BooleanValue);
        return GetField<Boolean>(n).value;
    }
    
    void BooleanValue_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, BooleanValue);
        GetField<Boolean>(n).Set(x);
    }
    
    bool BooleanValue_exists() const
    {
        const size_t n = offsetof(Self, BooleanValue);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void BooleanValue_clear()
    {
        const size_t n = offsetof(Self, BooleanValue);
        GetField<Boolean>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint8Value
    //
    
    const Field<Uint8>& Uint8Value() const
    {
        const size_t n = offsetof(Self, Uint8Value);
        return GetField<Uint8>(n);
    }
    
    void Uint8Value(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, Uint8Value);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& Uint8Value_value() const
    {
        const size_t n = offsetof(Self, Uint8Value);
        return GetField<Uint8>(n).value;
    }
    
    void Uint8Value_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, Uint8Value);
        GetField<Uint8>(n).Set(x);
    }
    
    bool Uint8Value_exists() const
    {
        const size_t n = offsetof(Self, Uint8Value);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void Uint8Value_clear()
    {
        const size_t n = offsetof(Self, Uint8Value);
        GetField<Uint8>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint8Value
    //
    
    const Field<Sint8>& Sint8Value() const
    {
        const size_t n = offsetof(Self, Sint8Value);
        return GetField<Sint8>(n);
    }
    
    void Sint8Value(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, Sint8Value);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& Sint8Value_value() const
    {
        const size_t n = offsetof(Self, Sint8Value);
        return GetField<Sint8>(n).value;
    }
    
    void Sint8Value_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, Sint8Value);
        GetField<Sint8>(n).Set(x);
    }
    
    bool Sint8Value_exists() const
    {
        const size_t n = offsetof(Self, Sint8Value);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void Sint8Value_clear()
    {
        const size_t n = offsetof(Self, Sint8Value);
        GetField<Sint8>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint16Value
    //
    
    const Field<Uint16>& Uint16Value() const
    {
        const size_t n = offsetof(Self, Uint16Value);
        return GetField<Uint16>(n);
    }
    
    void Uint16Value(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, Uint16Value);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& Uint16Value_value() const
    {
        const size_t n = offsetof(Self, Uint16Value);
        return GetField<Uint16>(n).value;
    }
    
    void Uint16Value_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, Uint16Value);
        GetField<Uint16>(n).Set(x);
    }
    
    bool Uint16Value_exists() const
    {
        const size_t n = offsetof(Self, Uint16Value);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void Uint16Value_clear()
    {
        const size_t n = offsetof(Self, Uint16Value);
        GetField<Uint16>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint16Value
    //
    
    const Field<Sint16>& Sint16Value() const
    {
        const size_t n = offsetof(Self, Sint16Value);
        return GetField<Sint16>(n);
    }
    
    void Sint16Value(const Field<Sint16>& x)
    {
        const size_t n = offsetof(Self, Sint16Value);
        GetField<Sint16>(n) = x;
    }
    
    const Sint16& Sint16Value_value() const
    {
        const size_t n = offsetof(Self, Sint16Value);
        return GetField<Sint16>(n).value;
    }
    
    void Sint16Value_value(const Sint16& x)
    {
        const size_t n = offsetof(Self, Sint16Value);
        GetField<Sint16>(n).Set(x);
    }
    
    bool Sint16Value_exists() const
    {
        const size_t n = offsetof(Self, Sint16Value);
        return GetField<Sint16>(n).exists ? true : false;
    }
    
    void Sint16Value_clear()
    {
        const size_t n = offsetof(Self, Sint16Value);
        GetField<Sint16>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint32Value
    //
    
    const Field<Uint32>& Uint32Value() const
    {
        const size_t n = offsetof(Self, Uint32Value);
        return GetField<Uint32>(n);
    }
    
    void Uint32Value(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Uint32Value);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Uint32Value_value() const
    {
        const size_t n = offsetof(Self, Uint32Value);
        return GetField<Uint32>(n).value;
    }
    
    void Uint32Value_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Uint32Value);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Uint32Value_exists() const
    {
        const size_t n = offsetof(Self, Uint32Value);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Uint32Value_clear()
    {
        const size_t n = offsetof(Self, Uint32Value);
        GetField<Uint32>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint32Value
    //
    
    const Field<Sint32>& Sint32Value() const
    {
        const size_t n = offsetof(Self, Sint32Value);
        return GetField<Sint32>(n);
    }
    
    void Sint32Value(const Field<Sint32>& x)
    {
        const size_t n = offsetof(Self, Sint32Value);
        GetField<Sint32>(n) = x;
    }
    
    const Sint32& Sint32Value_value() const
    {
        const size_t n = offsetof(Self, Sint32Value);
        return GetField<Sint32>(n).value;
    }
    
    void Sint32Value_value(const Sint32& x)
    {
        const size_t n = offsetof(Self, Sint32Value);
        GetField<Sint32>(n).Set(x);
    }
    
    bool Sint32Value_exists() const
    {
        const size_t n = offsetof(Self, Sint32Value);
        return GetField<Sint32>(n).exists ? true : false;
    }
    
    void Sint32Value_clear()
    {
        const size_t n = offsetof(Self, Sint32Value);
        GetField<Sint32>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint64Value
    //
    
    const Field<Uint64>& Uint64Value() const
    {
        const size_t n = offsetof(Self, Uint64Value);
        return GetField<Uint64>(n);
    }
    
    void Uint64Value(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, Uint64Value);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& Uint64Value_value() const
    {
        const size_t n = offsetof(Self, Uint64Value);
        return GetField<Uint64>(n).value;
    }
    
    void Uint64Value_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, Uint64Value);
        GetField<Uint64>(n).Set(x);
    }
    
    bool Uint64Value_exists() const
    {
        const size_t n = offsetof(Self, Uint64Value);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void Uint64Value_clear()
    {
        const size_t n = offsetof(Self, Uint64Value);
        GetField<Uint64>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint64Value
    //
    
    const Field<Sint64>& Sint64Value() const
    {
        const size_t n = offsetof(Self, Sint64Value);
        return GetField<Sint64>(n);
    }
    
    void Sint64Value(const Field<Sint64>& x)
    {
        const size_t n = offsetof(Self, Sint64Value);
        GetField<Sint64>(n) = x;
    }
    
    const Sint64& Sint64Value_value() const
    {
        const size_t n = offsetof(Self, Sint64Value);
        return GetField<Sint64>(n).value;
    }
    
    void Sint64Value_value(const Sint64& x)
    {
        const size_t n = offsetof(Self, Sint64Value);
        GetField<Sint64>(n).Set(x);
    }
    
    bool Sint64Value_exists() const
    {
        const size_t n = offsetof(Self, Sint64Value);
        return GetField<Sint64>(n).exists ? true : false;
    }
    
    void Sint64Value_clear()
    {
        const size_t n = offsetof(Self, Sint64Value);
        GetField<Sint64>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Real32Value
    //
    
    const Field<Real32>& Real32Value() const
    {
        const size_t n = offsetof(Self, Real32Value);
        return GetField<Real32>(n);
    }
    
    void Real32Value(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, Real32Value);
        GetField<Real32>(n) = x;
    }
    
    const Real32& Real32Value_value() const
    {
        const size_t n = offsetof(Self, Real32Value);
        return GetField<Real32>(n).value;
    }
    
    void Real32Value_value(const Real32& x)
    {
        const size_t n = offsetof(Self, Real32Value);
        GetField<Real32>(n).Set(x);
    }
    
    bool Real32Value_exists() const
    {
        const size_t n = offsetof(Self, Real32Value);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void Real32Value_clear()
    {
        const size_t n = offsetof(Self, Real32Value);
        GetField<Real32>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Real64Value
    //
    
    const Field<Real64>& Real64Value() const
    {
        const size_t n = offsetof(Self, Real64Value);
        return GetField<Real64>(n);
    }
    
    void Real64Value(const Field<Real64>& x)
    {
        const size_t n = offsetof(Self, Real64Value);
        GetField<Real64>(n) = x;
    }
    
    const Real64& Real64Value_value() const
    {
        const size_t n = offsetof(Self, Real64Value);
        return GetField<Real64>(n).value;
    }
    
    void Real64Value_value(const Real64& x)
    {
        const size_t n = offsetof(Self, Real64Value);
        GetField<Real64>(n).Set(x);
    }
    
    bool Real64Value_exists() const
    {
        const size_t n = offsetof(Self, Real64Value);
        return GetField<Real64>(n).exists ? true : false;
    }
    
    void Real64Value_clear()
    {
        const size_t n = offsetof(Self, Real64Value);
        GetField<Real64>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Char16Value
    //
    
    const Field<Char16>& Char16Value() const
    {
        const size_t n = offsetof(Self, Char16Value);
        return GetField<Char16>(n);
    }
    
    void Char16Value(const Field<Char16>& x)
    {
        const size_t n = offsetof(Self, Char16Value);
        GetField<Char16>(n) = x;
    }
    
    const Char16& Char16Value_value() const
    {
        const size_t n = offsetof(Self, Char16Value);
        return GetField<Char16>(n).value;
    }
    
    void Char16Value_value(const Char16& x)
    {
        const size_t n = offsetof(Self, Char16Value);
        GetField<Char16>(n).Set(x);
    }
    
    bool Char16Value_exists() const
    {
        const size_t n = offsetof(Self, Char16Value);
        return GetField<Char16>(n).exists ? true : false;
    }
    
    void Char16Value_clear()
    {
        const size_t n = offsetof(Self, Char16Value);
        GetField<Char16>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.TimestampValue
    //
    
    const Field<Datetime>& TimestampValue() const
    {
        const size_t n = offsetof(Self, TimestampValue);
        return GetField<Datetime>(n);
    }
    
    void TimestampValue(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TimestampValue);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TimestampValue_value() const
    {
        const size_t n = offsetof(Self, TimestampValue);
        return GetField<Datetime>(n).value;
    }
    
    void TimestampValue_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TimestampValue);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TimestampValue_exists() const
    {
        const size_t n = offsetof(Self, TimestampValue);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TimestampValue_clear()
    {
        const size_t n = offsetof(Self, TimestampValue);
        GetField<Datetime>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.IntervalValue
    //
    
    const Field<Datetime>& IntervalValue() const
    {
        const size_t n = offsetof(Self, IntervalValue);
        return GetField<Datetime>(n);
    }
    
    void IntervalValue(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, IntervalValue);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& IntervalValue_value() const
    {
        const size_t n = offsetof(Self, IntervalValue);
        return GetField<Datetime>(n).value;
    }
    
    void IntervalValue_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, IntervalValue);
        GetField<Datetime>(n).Set(x);
    }
    
    bool IntervalValue_exists() const
    {
        const size_t n = offsetof(Self, IntervalValue);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void IntervalValue_clear()
    {
        const size_t n = offsetof(Self, IntervalValue);
        GetField<Datetime>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.StringValue
    //
    
    const Field<String>& StringValue() const
    {
        const size_t n = offsetof(Self, StringValue);
        return GetField<String>(n);
    }
    
    void StringValue(const Field<String>& x)
    {
        const size_t n = offsetof(Self, StringValue);
        GetField<String>(n) = x;
    }
    
    const String& StringValue_value() const
    {
        const size_t n = offsetof(Self, StringValue);
        return GetField<String>(n).value;
    }
    
    void StringValue_value(const String& x)
    {
        const size_t n = offsetof(Self, StringValue);
        GetField<String>(n).Set(x);
    }
    
    bool StringValue_exists() const
    {
        const size_t n = offsetof(Self, StringValue);
        return GetField<String>(n).exists ? true : false;
    }
    
    void StringValue_clear()
    {
        const size_t n = offsetof(Self, StringValue);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.BooleanArray
    //
    
    const Field<BooleanA>& BooleanArray() const
    {
        const size_t n = offsetof(Self, BooleanArray);
        return GetField<BooleanA>(n);
    }
    
    void BooleanArray(const Field<BooleanA>& x)
    {
        const size_t n = offsetof(Self, BooleanArray);
        GetField<BooleanA>(n) = x;
    }
    
    const BooleanA& BooleanArray_value() const
    {
        const size_t n = offsetof(Self, BooleanArray);
        return GetField<BooleanA>(n).value;
    }
    
    void BooleanArray_value(const BooleanA& x)
    {
        const size_t n = offsetof(Self, BooleanArray);
        GetField<BooleanA>(n).Set(x);
    }
    
    bool BooleanArray_exists() const
    {
        const size_t n = offsetof(Self, BooleanArray);
        return GetField<BooleanA>(n).exists ? true : false;
    }
    
    void BooleanArray_clear()
    {
        const size_t n = offsetof(Self, BooleanArray);
        GetField<BooleanA>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint8Array
    //
    
    const Field<Uint8A>& Uint8Array() const
    {
        const size_t n = offsetof(Self, Uint8Array);
        return GetField<Uint8A>(n);
    }
    
    void Uint8Array(const Field<Uint8A>& x)
    {
        const size_t n = offsetof(Self, Uint8Array);
        GetField<Uint8A>(n) = x;
    }
    
    const Uint8A& Uint8Array_value() const
    {
        const size_t n = offsetof(Self, Uint8Array);
        return GetField<Uint8A>(n).value;
    }
    
    void Uint8Array_value(const Uint8A& x)
    {
        const size_t n = offsetof(Self, Uint8Array);
        GetField<Uint8A>(n).Set(x);
    }
    
    bool Uint8Array_exists() const
    {
        const size_t n = offsetof(Self, Uint8Array);
        return GetField<Uint8A>(n).exists ? true : false;
    }
    
    void Uint8Array_clear()
    {
        const size_t n = offsetof(Self, Uint8Array);
        GetField<Uint8A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint8Array
    //
    
    const Field<Sint8A>& Sint8Array() const
    {
        const size_t n = offsetof(Self, Sint8Array);
        return GetField<Sint8A>(n);
    }
    
    void Sint8Array(const Field<Sint8A>& x)
    {
        const size_t n = offsetof(Self, Sint8Array);
        GetField<Sint8A>(n) = x;
    }
    
    const Sint8A& Sint8Array_value() const
    {
        const size_t n = offsetof(Self, Sint8Array);
        return GetField<Sint8A>(n).value;
    }
    
    void Sint8Array_value(const Sint8A& x)
    {
        const size_t n = offsetof(Self, Sint8Array);
        GetField<Sint8A>(n).Set(x);
    }
    
    bool Sint8Array_exists() const
    {
        const size_t n = offsetof(Self, Sint8Array);
        return GetField<Sint8A>(n).exists ? true : false;
    }
    
    void Sint8Array_clear()
    {
        const size_t n = offsetof(Self, Sint8Array);
        GetField<Sint8A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint16Array
    //
    
    const Field<Uint16A>& Uint16Array() const
    {
        const size_t n = offsetof(Self, Uint16Array);
        return GetField<Uint16A>(n);
    }
    
    void Uint16Array(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, Uint16Array);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& Uint16Array_value() const
    {
        const size_t n = offsetof(Self, Uint16Array);
        return GetField<Uint16A>(n).value;
    }
    
    void Uint16Array_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, Uint16Array);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool Uint16Array_exists() const
    {
        const size_t n = offsetof(Self, Uint16Array);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void Uint16Array_clear()
    {
        const size_t n = offsetof(Self, Uint16Array);
        GetField<Uint16A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint16Array
    //
    
    const Field<Sint16A>& Sint16Array() const
    {
        const size_t n = offsetof(Self, Sint16Array);
        return GetField<Sint16A>(n);
    }
    
    void Sint16Array(const Field<Sint16A>& x)
    {
        const size_t n = offsetof(Self, Sint16Array);
        GetField<Sint16A>(n) = x;
    }
    
    const Sint16A& Sint16Array_value() const
    {
        const size_t n = offsetof(Self, Sint16Array);
        return GetField<Sint16A>(n).value;
    }
    
    void Sint16Array_value(const Sint16A& x)
    {
        const size_t n = offsetof(Self, Sint16Array);
        GetField<Sint16A>(n).Set(x);
    }
    
    bool Sint16Array_exists() const
    {
        const size_t n = offsetof(Self, Sint16Array);
        return GetField<Sint16A>(n).exists ? true : false;
    }
    
    void Sint16Array_clear()
    {
        const size_t n = offsetof(Self, Sint16Array);
        GetField<Sint16A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint32Array
    //
    
    const Field<Uint32A>& Uint32Array() const
    {
        const size_t n = offsetof(Self, Uint32Array);
        return GetField<Uint32A>(n);
    }
    
    void Uint32Array(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, Uint32Array);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& Uint32Array_value() const
    {
        const size_t n = offsetof(Self, Uint32Array);
        return GetField<Uint32A>(n).value;
    }
    
    void Uint32Array_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, Uint32Array);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool Uint32Array_exists() const
    {
        const size_t n = offsetof(Self, Uint32Array);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void Uint32Array_clear()
    {
        const size_t n = offsetof(Self, Uint32Array);
        GetField<Uint32A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint32Array
    //
    
    const Field<Sint32A>& Sint32Array() const
    {
        const size_t n = offsetof(Self, Sint32Array);
        return GetField<Sint32A>(n);
    }
    
    void Sint32Array(const Field<Sint32A>& x)
    {
        const size_t n = offsetof(Self, Sint32Array);
        GetField<Sint32A>(n) = x;
    }
    
    const Sint32A& Sint32Array_value() const
    {
        const size_t n = offsetof(Self, Sint32Array);
        return GetField<Sint32A>(n).value;
    }
    
    void Sint32Array_value(const Sint32A& x)
    {
        const size_t n = offsetof(Self, Sint32Array);
        GetField<Sint32A>(n).Set(x);
    }
    
    bool Sint32Array_exists() const
    {
        const size_t n = offsetof(Self, Sint32Array);
        return GetField<Sint32A>(n).exists ? true : false;
    }
    
    void Sint32Array_clear()
    {
        const size_t n = offsetof(Self, Sint32Array);
        GetField<Sint32A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Uint64Array
    //
    
    const Field<Uint64A>& Uint64Array() const
    {
        const size_t n = offsetof(Self, Uint64Array);
        return GetField<Uint64A>(n);
    }
    
    void Uint64Array(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, Uint64Array);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& Uint64Array_value() const
    {
        const size_t n = offsetof(Self, Uint64Array);
        return GetField<Uint64A>(n).value;
    }
    
    void Uint64Array_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, Uint64Array);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool Uint64Array_exists() const
    {
        const size_t n = offsetof(Self, Uint64Array);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void Uint64Array_clear()
    {
        const size_t n = offsetof(Self, Uint64Array);
        GetField<Uint64A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Sint64Array
    //
    
    const Field<Sint64A>& Sint64Array() const
    {
        const size_t n = offsetof(Self, Sint64Array);
        return GetField<Sint64A>(n);
    }
    
    void Sint64Array(const Field<Sint64A>& x)
    {
        const size_t n = offsetof(Self, Sint64Array);
        GetField<Sint64A>(n) = x;
    }
    
    const Sint64A& Sint64Array_value() const
    {
        const size_t n = offsetof(Self, Sint64Array);
        return GetField<Sint64A>(n).value;
    }
    
    void Sint64Array_value(const Sint64A& x)
    {
        const size_t n = offsetof(Self, Sint64Array);
        GetField<Sint64A>(n).Set(x);
    }
    
    bool Sint64Array_exists() const
    {
        const size_t n = offsetof(Self, Sint64Array);
        return GetField<Sint64A>(n).exists ? true : false;
    }
    
    void Sint64Array_clear()
    {
        const size_t n = offsetof(Self, Sint64Array);
        GetField<Sint64A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Real32Array
    //
    
    const Field<Real32A>& Real32Array() const
    {
        const size_t n = offsetof(Self, Real32Array);
        return GetField<Real32A>(n);
    }
    
    void Real32Array(const Field<Real32A>& x)
    {
        const size_t n = offsetof(Self, Real32Array);
        GetField<Real32A>(n) = x;
    }
    
    const Real32A& Real32Array_value() const
    {
        const size_t n = offsetof(Self, Real32Array);
        return GetField<Real32A>(n).value;
    }
    
    void Real32Array_value(const Real32A& x)
    {
        const size_t n = offsetof(Self, Real32Array);
        GetField<Real32A>(n).Set(x);
    }
    
    bool Real32Array_exists() const
    {
        const size_t n = offsetof(Self, Real32Array);
        return GetField<Real32A>(n).exists ? true : false;
    }
    
    void Real32Array_clear()
    {
        const size_t n = offsetof(Self, Real32Array);
        GetField<Real32A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Real64Array
    //
    
    const Field<Real64A>& Real64Array() const
    {
        const size_t n = offsetof(Self, Real64Array);
        return GetField<Real64A>(n);
    }
    
    void Real64Array(const Field<Real64A>& x)
    {
        const size_t n = offsetof(Self, Real64Array);
        GetField<Real64A>(n) = x;
    }
    
    const Real64A& Real64Array_value() const
    {
        const size_t n = offsetof(Self, Real64Array);
        return GetField<Real64A>(n).value;
    }
    
    void Real64Array_value(const Real64A& x)
    {
        const size_t n = offsetof(Self, Real64Array);
        GetField<Real64A>(n).Set(x);
    }
    
    bool Real64Array_exists() const
    {
        const size_t n = offsetof(Self, Real64Array);
        return GetField<Real64A>(n).exists ? true : false;
    }
    
    void Real64Array_clear()
    {
        const size_t n = offsetof(Self, Real64Array);
        GetField<Real64A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.Char16Array
    //
    
    const Field<Char16A>& Char16Array() const
    {
        const size_t n = offsetof(Self, Char16Array);
        return GetField<Char16A>(n);
    }
    
    void Char16Array(const Field<Char16A>& x)
    {
        const size_t n = offsetof(Self, Char16Array);
        GetField<Char16A>(n) = x;
    }
    
    const Char16A& Char16Array_value() const
    {
        const size_t n = offsetof(Self, Char16Array);
        return GetField<Char16A>(n).value;
    }
    
    void Char16Array_value(const Char16A& x)
    {
        const size_t n = offsetof(Self, Char16Array);
        GetField<Char16A>(n).Set(x);
    }
    
    bool Char16Array_exists() const
    {
        const size_t n = offsetof(Self, Char16Array);
        return GetField<Char16A>(n).exists ? true : false;
    }
    
    void Char16Array_clear()
    {
        const size_t n = offsetof(Self, Char16Array);
        GetField<Char16A>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.DatetimeArray
    //
    
    const Field<DatetimeA>& DatetimeArray() const
    {
        const size_t n = offsetof(Self, DatetimeArray);
        return GetField<DatetimeA>(n);
    }
    
    void DatetimeArray(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, DatetimeArray);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& DatetimeArray_value() const
    {
        const size_t n = offsetof(Self, DatetimeArray);
        return GetField<DatetimeA>(n).value;
    }
    
    void DatetimeArray_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, DatetimeArray);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool DatetimeArray_exists() const
    {
        const size_t n = offsetof(Self, DatetimeArray);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void DatetimeArray_clear()
    {
        const size_t n = offsetof(Self, DatetimeArray);
        GetField<DatetimeA>(n).Clear();
    }

    //
    // MSFT_AllTypes_Class.StringArray
    //
    
    const Field<StringA>& StringArray() const
    {
        const size_t n = offsetof(Self, StringArray);
        return GetField<StringA>(n);
    }
    
    void StringArray(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, StringArray);
        GetField<StringA>(n) = x;
    }
    
    const StringA& StringArray_value() const
    {
        const size_t n = offsetof(Self, StringArray);
        return GetField<StringA>(n).value;
    }
    
    void StringArray_value(const StringA& x)
    {
        const size_t n = offsetof(Self, StringArray);
        GetField<StringA>(n).Set(x);
    }
    
    bool StringArray_exists() const
    {
        const size_t n = offsetof(Self, StringArray);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void StringArray_clear()
    {
        const size_t n = offsetof(Self, StringArray);
        GetField<StringA>(n).Clear();
    }
};

typedef Array<MSFT_AllTypes_Class> MSFT_AllTypes_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_AllTypes_h */
