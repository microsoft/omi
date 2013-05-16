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
#ifndef _Outer_h
#define _Outer_h

#include <MI.h>
#include "Inner.h"

/*
**==============================================================================
**
** Outer [Outer]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Outer
{
    MI_Instance __instance;
    /* Outer properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstBooleanField booleanScalar;
    MI_ConstUint8Field uint8Scalar;
    MI_ConstSint8Field sint8Scalar;
    MI_ConstUint16Field uint16Scalar;
    MI_ConstSint16Field sint16Scalar;
    MI_ConstUint32Field uint32Scalar;
    MI_ConstSint32Field sint32Scalar;
    MI_ConstUint64Field uint64Scalar;
    MI_ConstSint64Field sint64Scalar;
    MI_ConstReal32Field real32Scalar;
    MI_ConstReal64Field real64Scalar;
    MI_ConstChar16Field char16Scalar;
    MI_ConstDatetimeField datetimeScalar;
    MI_ConstStringField stringScalar;
    Inner_ConstRef instanceScalar;
    MI_ConstBooleanAField booleanArray;
    MI_ConstUint8AField uint8Array;
    MI_ConstSint8AField sint8Array;
    MI_ConstUint16AField uint16Array;
    MI_ConstSint16AField sint16Array;
    MI_ConstUint32AField uint32Array;
    MI_ConstSint32AField sint32Array;
    MI_ConstUint64AField uint64Array;
    MI_ConstSint64AField sint64Array;
    MI_ConstReal32AField real32Array;
    MI_ConstReal64AField real64Array;
    MI_ConstChar16AField char16Array;
    MI_ConstDatetimeAField datetimeArray;
    MI_ConstStringAField stringArray;
    Inner_ConstArrayRef instanceArray;
}
Outer;

typedef struct _Outer_Ref
{
    Outer* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Outer_Ref;

typedef struct _Outer_ConstRef
{
    MI_CONST Outer* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Outer_ConstRef;

typedef struct _Outer_Array
{
    struct _Outer** data;
    MI_Uint32 size;
}
Outer_Array;

typedef struct _Outer_ConstArray
{
    struct _Outer MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Outer_ConstArray;

typedef struct _Outer_ArrayRef
{
    Outer_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Outer_ArrayRef;

typedef struct _Outer_ConstArrayRef
{
    Outer_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Outer_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Outer_rtti;


/*
**==============================================================================
**
** Outer_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Outer_Class : public Instance
{
public:
    
    typedef Outer Self;
    
    Outer_Class() :
        Instance(&Outer_rtti)
    {
    }
    
    Outer_Class(
        const Outer* instanceName,
        bool keysOnly) :
        Instance(
            &Outer_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Outer_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Outer_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Outer_Class& operator=(
        const Outer_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Outer_Class(
        const Outer_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Outer_rtti;
    }

    //
    // Outer_Class.Key
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
    // Outer_Class.booleanScalar
    //
    
    const Field<Boolean>& booleanScalar() const
    {
        const size_t n = offsetof(Self, booleanScalar);
        return GetField<Boolean>(n);
    }
    
    void booleanScalar(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, booleanScalar);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& booleanScalar_value() const
    {
        const size_t n = offsetof(Self, booleanScalar);
        return GetField<Boolean>(n).value;
    }
    
    void booleanScalar_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, booleanScalar);
        GetField<Boolean>(n).Set(x);
    }
    
    bool booleanScalar_exists() const
    {
        const size_t n = offsetof(Self, booleanScalar);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void booleanScalar_clear()
    {
        const size_t n = offsetof(Self, booleanScalar);
        GetField<Boolean>(n).Clear();
    }

    //
    // Outer_Class.uint8Scalar
    //
    
    const Field<Uint8>& uint8Scalar() const
    {
        const size_t n = offsetof(Self, uint8Scalar);
        return GetField<Uint8>(n);
    }
    
    void uint8Scalar(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, uint8Scalar);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& uint8Scalar_value() const
    {
        const size_t n = offsetof(Self, uint8Scalar);
        return GetField<Uint8>(n).value;
    }
    
    void uint8Scalar_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, uint8Scalar);
        GetField<Uint8>(n).Set(x);
    }
    
    bool uint8Scalar_exists() const
    {
        const size_t n = offsetof(Self, uint8Scalar);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void uint8Scalar_clear()
    {
        const size_t n = offsetof(Self, uint8Scalar);
        GetField<Uint8>(n).Clear();
    }

    //
    // Outer_Class.sint8Scalar
    //
    
    const Field<Sint8>& sint8Scalar() const
    {
        const size_t n = offsetof(Self, sint8Scalar);
        return GetField<Sint8>(n);
    }
    
    void sint8Scalar(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, sint8Scalar);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& sint8Scalar_value() const
    {
        const size_t n = offsetof(Self, sint8Scalar);
        return GetField<Sint8>(n).value;
    }
    
    void sint8Scalar_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, sint8Scalar);
        GetField<Sint8>(n).Set(x);
    }
    
    bool sint8Scalar_exists() const
    {
        const size_t n = offsetof(Self, sint8Scalar);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void sint8Scalar_clear()
    {
        const size_t n = offsetof(Self, sint8Scalar);
        GetField<Sint8>(n).Clear();
    }

    //
    // Outer_Class.uint16Scalar
    //
    
    const Field<Uint16>& uint16Scalar() const
    {
        const size_t n = offsetof(Self, uint16Scalar);
        return GetField<Uint16>(n);
    }
    
    void uint16Scalar(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, uint16Scalar);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& uint16Scalar_value() const
    {
        const size_t n = offsetof(Self, uint16Scalar);
        return GetField<Uint16>(n).value;
    }
    
    void uint16Scalar_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, uint16Scalar);
        GetField<Uint16>(n).Set(x);
    }
    
    bool uint16Scalar_exists() const
    {
        const size_t n = offsetof(Self, uint16Scalar);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void uint16Scalar_clear()
    {
        const size_t n = offsetof(Self, uint16Scalar);
        GetField<Uint16>(n).Clear();
    }

    //
    // Outer_Class.sint16Scalar
    //
    
    const Field<Sint16>& sint16Scalar() const
    {
        const size_t n = offsetof(Self, sint16Scalar);
        return GetField<Sint16>(n);
    }
    
    void sint16Scalar(const Field<Sint16>& x)
    {
        const size_t n = offsetof(Self, sint16Scalar);
        GetField<Sint16>(n) = x;
    }
    
    const Sint16& sint16Scalar_value() const
    {
        const size_t n = offsetof(Self, sint16Scalar);
        return GetField<Sint16>(n).value;
    }
    
    void sint16Scalar_value(const Sint16& x)
    {
        const size_t n = offsetof(Self, sint16Scalar);
        GetField<Sint16>(n).Set(x);
    }
    
    bool sint16Scalar_exists() const
    {
        const size_t n = offsetof(Self, sint16Scalar);
        return GetField<Sint16>(n).exists ? true : false;
    }
    
    void sint16Scalar_clear()
    {
        const size_t n = offsetof(Self, sint16Scalar);
        GetField<Sint16>(n).Clear();
    }

    //
    // Outer_Class.uint32Scalar
    //
    
    const Field<Uint32>& uint32Scalar() const
    {
        const size_t n = offsetof(Self, uint32Scalar);
        return GetField<Uint32>(n);
    }
    
    void uint32Scalar(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, uint32Scalar);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& uint32Scalar_value() const
    {
        const size_t n = offsetof(Self, uint32Scalar);
        return GetField<Uint32>(n).value;
    }
    
    void uint32Scalar_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, uint32Scalar);
        GetField<Uint32>(n).Set(x);
    }
    
    bool uint32Scalar_exists() const
    {
        const size_t n = offsetof(Self, uint32Scalar);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void uint32Scalar_clear()
    {
        const size_t n = offsetof(Self, uint32Scalar);
        GetField<Uint32>(n).Clear();
    }

    //
    // Outer_Class.sint32Scalar
    //
    
    const Field<Sint32>& sint32Scalar() const
    {
        const size_t n = offsetof(Self, sint32Scalar);
        return GetField<Sint32>(n);
    }
    
    void sint32Scalar(const Field<Sint32>& x)
    {
        const size_t n = offsetof(Self, sint32Scalar);
        GetField<Sint32>(n) = x;
    }
    
    const Sint32& sint32Scalar_value() const
    {
        const size_t n = offsetof(Self, sint32Scalar);
        return GetField<Sint32>(n).value;
    }
    
    void sint32Scalar_value(const Sint32& x)
    {
        const size_t n = offsetof(Self, sint32Scalar);
        GetField<Sint32>(n).Set(x);
    }
    
    bool sint32Scalar_exists() const
    {
        const size_t n = offsetof(Self, sint32Scalar);
        return GetField<Sint32>(n).exists ? true : false;
    }
    
    void sint32Scalar_clear()
    {
        const size_t n = offsetof(Self, sint32Scalar);
        GetField<Sint32>(n).Clear();
    }

    //
    // Outer_Class.uint64Scalar
    //
    
    const Field<Uint64>& uint64Scalar() const
    {
        const size_t n = offsetof(Self, uint64Scalar);
        return GetField<Uint64>(n);
    }
    
    void uint64Scalar(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, uint64Scalar);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& uint64Scalar_value() const
    {
        const size_t n = offsetof(Self, uint64Scalar);
        return GetField<Uint64>(n).value;
    }
    
    void uint64Scalar_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, uint64Scalar);
        GetField<Uint64>(n).Set(x);
    }
    
    bool uint64Scalar_exists() const
    {
        const size_t n = offsetof(Self, uint64Scalar);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void uint64Scalar_clear()
    {
        const size_t n = offsetof(Self, uint64Scalar);
        GetField<Uint64>(n).Clear();
    }

    //
    // Outer_Class.sint64Scalar
    //
    
    const Field<Sint64>& sint64Scalar() const
    {
        const size_t n = offsetof(Self, sint64Scalar);
        return GetField<Sint64>(n);
    }
    
    void sint64Scalar(const Field<Sint64>& x)
    {
        const size_t n = offsetof(Self, sint64Scalar);
        GetField<Sint64>(n) = x;
    }
    
    const Sint64& sint64Scalar_value() const
    {
        const size_t n = offsetof(Self, sint64Scalar);
        return GetField<Sint64>(n).value;
    }
    
    void sint64Scalar_value(const Sint64& x)
    {
        const size_t n = offsetof(Self, sint64Scalar);
        GetField<Sint64>(n).Set(x);
    }
    
    bool sint64Scalar_exists() const
    {
        const size_t n = offsetof(Self, sint64Scalar);
        return GetField<Sint64>(n).exists ? true : false;
    }
    
    void sint64Scalar_clear()
    {
        const size_t n = offsetof(Self, sint64Scalar);
        GetField<Sint64>(n).Clear();
    }

    //
    // Outer_Class.real32Scalar
    //
    
    const Field<Real32>& real32Scalar() const
    {
        const size_t n = offsetof(Self, real32Scalar);
        return GetField<Real32>(n);
    }
    
    void real32Scalar(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, real32Scalar);
        GetField<Real32>(n) = x;
    }
    
    const Real32& real32Scalar_value() const
    {
        const size_t n = offsetof(Self, real32Scalar);
        return GetField<Real32>(n).value;
    }
    
    void real32Scalar_value(const Real32& x)
    {
        const size_t n = offsetof(Self, real32Scalar);
        GetField<Real32>(n).Set(x);
    }
    
    bool real32Scalar_exists() const
    {
        const size_t n = offsetof(Self, real32Scalar);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void real32Scalar_clear()
    {
        const size_t n = offsetof(Self, real32Scalar);
        GetField<Real32>(n).Clear();
    }

    //
    // Outer_Class.real64Scalar
    //
    
    const Field<Real64>& real64Scalar() const
    {
        const size_t n = offsetof(Self, real64Scalar);
        return GetField<Real64>(n);
    }
    
    void real64Scalar(const Field<Real64>& x)
    {
        const size_t n = offsetof(Self, real64Scalar);
        GetField<Real64>(n) = x;
    }
    
    const Real64& real64Scalar_value() const
    {
        const size_t n = offsetof(Self, real64Scalar);
        return GetField<Real64>(n).value;
    }
    
    void real64Scalar_value(const Real64& x)
    {
        const size_t n = offsetof(Self, real64Scalar);
        GetField<Real64>(n).Set(x);
    }
    
    bool real64Scalar_exists() const
    {
        const size_t n = offsetof(Self, real64Scalar);
        return GetField<Real64>(n).exists ? true : false;
    }
    
    void real64Scalar_clear()
    {
        const size_t n = offsetof(Self, real64Scalar);
        GetField<Real64>(n).Clear();
    }

    //
    // Outer_Class.char16Scalar
    //
    
    const Field<Char16>& char16Scalar() const
    {
        const size_t n = offsetof(Self, char16Scalar);
        return GetField<Char16>(n);
    }
    
    void char16Scalar(const Field<Char16>& x)
    {
        const size_t n = offsetof(Self, char16Scalar);
        GetField<Char16>(n) = x;
    }
    
    const Char16& char16Scalar_value() const
    {
        const size_t n = offsetof(Self, char16Scalar);
        return GetField<Char16>(n).value;
    }
    
    void char16Scalar_value(const Char16& x)
    {
        const size_t n = offsetof(Self, char16Scalar);
        GetField<Char16>(n).Set(x);
    }
    
    bool char16Scalar_exists() const
    {
        const size_t n = offsetof(Self, char16Scalar);
        return GetField<Char16>(n).exists ? true : false;
    }
    
    void char16Scalar_clear()
    {
        const size_t n = offsetof(Self, char16Scalar);
        GetField<Char16>(n).Clear();
    }

    //
    // Outer_Class.datetimeScalar
    //
    
    const Field<Datetime>& datetimeScalar() const
    {
        const size_t n = offsetof(Self, datetimeScalar);
        return GetField<Datetime>(n);
    }
    
    void datetimeScalar(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, datetimeScalar);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& datetimeScalar_value() const
    {
        const size_t n = offsetof(Self, datetimeScalar);
        return GetField<Datetime>(n).value;
    }
    
    void datetimeScalar_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, datetimeScalar);
        GetField<Datetime>(n).Set(x);
    }
    
    bool datetimeScalar_exists() const
    {
        const size_t n = offsetof(Self, datetimeScalar);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void datetimeScalar_clear()
    {
        const size_t n = offsetof(Self, datetimeScalar);
        GetField<Datetime>(n).Clear();
    }

    //
    // Outer_Class.stringScalar
    //
    
    const Field<String>& stringScalar() const
    {
        const size_t n = offsetof(Self, stringScalar);
        return GetField<String>(n);
    }
    
    void stringScalar(const Field<String>& x)
    {
        const size_t n = offsetof(Self, stringScalar);
        GetField<String>(n) = x;
    }
    
    const String& stringScalar_value() const
    {
        const size_t n = offsetof(Self, stringScalar);
        return GetField<String>(n).value;
    }
    
    void stringScalar_value(const String& x)
    {
        const size_t n = offsetof(Self, stringScalar);
        GetField<String>(n).Set(x);
    }
    
    bool stringScalar_exists() const
    {
        const size_t n = offsetof(Self, stringScalar);
        return GetField<String>(n).exists ? true : false;
    }
    
    void stringScalar_clear()
    {
        const size_t n = offsetof(Self, stringScalar);
        GetField<String>(n).Clear();
    }

    //
    // Outer_Class.instanceScalar
    //
    
    const Field<Inner_Class>& instanceScalar() const
    {
        const size_t n = offsetof(Self, instanceScalar);
        return GetField<Inner_Class>(n);
    }
    
    void instanceScalar(const Field<Inner_Class>& x)
    {
        const size_t n = offsetof(Self, instanceScalar);
        GetField<Inner_Class>(n) = x;
    }
    
    const Inner_Class& instanceScalar_value() const
    {
        const size_t n = offsetof(Self, instanceScalar);
        return GetField<Inner_Class>(n).value;
    }
    
    void instanceScalar_value(const Inner_Class& x)
    {
        const size_t n = offsetof(Self, instanceScalar);
        GetField<Inner_Class>(n).Set(x);
    }
    
    bool instanceScalar_exists() const
    {
        const size_t n = offsetof(Self, instanceScalar);
        return GetField<Inner_Class>(n).exists ? true : false;
    }
    
    void instanceScalar_clear()
    {
        const size_t n = offsetof(Self, instanceScalar);
        GetField<Inner_Class>(n).Clear();
    }

    //
    // Outer_Class.booleanArray
    //
    
    const Field<BooleanA>& booleanArray() const
    {
        const size_t n = offsetof(Self, booleanArray);
        return GetField<BooleanA>(n);
    }
    
    void booleanArray(const Field<BooleanA>& x)
    {
        const size_t n = offsetof(Self, booleanArray);
        GetField<BooleanA>(n) = x;
    }
    
    const BooleanA& booleanArray_value() const
    {
        const size_t n = offsetof(Self, booleanArray);
        return GetField<BooleanA>(n).value;
    }
    
    void booleanArray_value(const BooleanA& x)
    {
        const size_t n = offsetof(Self, booleanArray);
        GetField<BooleanA>(n).Set(x);
    }
    
    bool booleanArray_exists() const
    {
        const size_t n = offsetof(Self, booleanArray);
        return GetField<BooleanA>(n).exists ? true : false;
    }
    
    void booleanArray_clear()
    {
        const size_t n = offsetof(Self, booleanArray);
        GetField<BooleanA>(n).Clear();
    }

    //
    // Outer_Class.uint8Array
    //
    
    const Field<Uint8A>& uint8Array() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n);
    }
    
    void uint8Array(const Field<Uint8A>& x)
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n) = x;
    }
    
    const Uint8A& uint8Array_value() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n).value;
    }
    
    void uint8Array_value(const Uint8A& x)
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n).Set(x);
    }
    
    bool uint8Array_exists() const
    {
        const size_t n = offsetof(Self, uint8Array);
        return GetField<Uint8A>(n).exists ? true : false;
    }
    
    void uint8Array_clear()
    {
        const size_t n = offsetof(Self, uint8Array);
        GetField<Uint8A>(n).Clear();
    }

    //
    // Outer_Class.sint8Array
    //
    
    const Field<Sint8A>& sint8Array() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n);
    }
    
    void sint8Array(const Field<Sint8A>& x)
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n) = x;
    }
    
    const Sint8A& sint8Array_value() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n).value;
    }
    
    void sint8Array_value(const Sint8A& x)
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n).Set(x);
    }
    
    bool sint8Array_exists() const
    {
        const size_t n = offsetof(Self, sint8Array);
        return GetField<Sint8A>(n).exists ? true : false;
    }
    
    void sint8Array_clear()
    {
        const size_t n = offsetof(Self, sint8Array);
        GetField<Sint8A>(n).Clear();
    }

    //
    // Outer_Class.uint16Array
    //
    
    const Field<Uint16A>& uint16Array() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n);
    }
    
    void uint16Array(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& uint16Array_value() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n).value;
    }
    
    void uint16Array_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool uint16Array_exists() const
    {
        const size_t n = offsetof(Self, uint16Array);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void uint16Array_clear()
    {
        const size_t n = offsetof(Self, uint16Array);
        GetField<Uint16A>(n).Clear();
    }

    //
    // Outer_Class.sint16Array
    //
    
    const Field<Sint16A>& sint16Array() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n);
    }
    
    void sint16Array(const Field<Sint16A>& x)
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n) = x;
    }
    
    const Sint16A& sint16Array_value() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n).value;
    }
    
    void sint16Array_value(const Sint16A& x)
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n).Set(x);
    }
    
    bool sint16Array_exists() const
    {
        const size_t n = offsetof(Self, sint16Array);
        return GetField<Sint16A>(n).exists ? true : false;
    }
    
    void sint16Array_clear()
    {
        const size_t n = offsetof(Self, sint16Array);
        GetField<Sint16A>(n).Clear();
    }

    //
    // Outer_Class.uint32Array
    //
    
    const Field<Uint32A>& uint32Array() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n);
    }
    
    void uint32Array(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& uint32Array_value() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n).value;
    }
    
    void uint32Array_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool uint32Array_exists() const
    {
        const size_t n = offsetof(Self, uint32Array);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void uint32Array_clear()
    {
        const size_t n = offsetof(Self, uint32Array);
        GetField<Uint32A>(n).Clear();
    }

    //
    // Outer_Class.sint32Array
    //
    
    const Field<Sint32A>& sint32Array() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n);
    }
    
    void sint32Array(const Field<Sint32A>& x)
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n) = x;
    }
    
    const Sint32A& sint32Array_value() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n).value;
    }
    
    void sint32Array_value(const Sint32A& x)
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n).Set(x);
    }
    
    bool sint32Array_exists() const
    {
        const size_t n = offsetof(Self, sint32Array);
        return GetField<Sint32A>(n).exists ? true : false;
    }
    
    void sint32Array_clear()
    {
        const size_t n = offsetof(Self, sint32Array);
        GetField<Sint32A>(n).Clear();
    }

    //
    // Outer_Class.uint64Array
    //
    
    const Field<Uint64A>& uint64Array() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n);
    }
    
    void uint64Array(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& uint64Array_value() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n).value;
    }
    
    void uint64Array_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool uint64Array_exists() const
    {
        const size_t n = offsetof(Self, uint64Array);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void uint64Array_clear()
    {
        const size_t n = offsetof(Self, uint64Array);
        GetField<Uint64A>(n).Clear();
    }

    //
    // Outer_Class.sint64Array
    //
    
    const Field<Sint64A>& sint64Array() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n);
    }
    
    void sint64Array(const Field<Sint64A>& x)
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n) = x;
    }
    
    const Sint64A& sint64Array_value() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n).value;
    }
    
    void sint64Array_value(const Sint64A& x)
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n).Set(x);
    }
    
    bool sint64Array_exists() const
    {
        const size_t n = offsetof(Self, sint64Array);
        return GetField<Sint64A>(n).exists ? true : false;
    }
    
    void sint64Array_clear()
    {
        const size_t n = offsetof(Self, sint64Array);
        GetField<Sint64A>(n).Clear();
    }

    //
    // Outer_Class.real32Array
    //
    
    const Field<Real32A>& real32Array() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n);
    }
    
    void real32Array(const Field<Real32A>& x)
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n) = x;
    }
    
    const Real32A& real32Array_value() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n).value;
    }
    
    void real32Array_value(const Real32A& x)
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n).Set(x);
    }
    
    bool real32Array_exists() const
    {
        const size_t n = offsetof(Self, real32Array);
        return GetField<Real32A>(n).exists ? true : false;
    }
    
    void real32Array_clear()
    {
        const size_t n = offsetof(Self, real32Array);
        GetField<Real32A>(n).Clear();
    }

    //
    // Outer_Class.real64Array
    //
    
    const Field<Real64A>& real64Array() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n);
    }
    
    void real64Array(const Field<Real64A>& x)
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n) = x;
    }
    
    const Real64A& real64Array_value() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n).value;
    }
    
    void real64Array_value(const Real64A& x)
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n).Set(x);
    }
    
    bool real64Array_exists() const
    {
        const size_t n = offsetof(Self, real64Array);
        return GetField<Real64A>(n).exists ? true : false;
    }
    
    void real64Array_clear()
    {
        const size_t n = offsetof(Self, real64Array);
        GetField<Real64A>(n).Clear();
    }

    //
    // Outer_Class.char16Array
    //
    
    const Field<Char16A>& char16Array() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n);
    }
    
    void char16Array(const Field<Char16A>& x)
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n) = x;
    }
    
    const Char16A& char16Array_value() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n).value;
    }
    
    void char16Array_value(const Char16A& x)
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n).Set(x);
    }
    
    bool char16Array_exists() const
    {
        const size_t n = offsetof(Self, char16Array);
        return GetField<Char16A>(n).exists ? true : false;
    }
    
    void char16Array_clear()
    {
        const size_t n = offsetof(Self, char16Array);
        GetField<Char16A>(n).Clear();
    }

    //
    // Outer_Class.datetimeArray
    //
    
    const Field<DatetimeA>& datetimeArray() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n);
    }
    
    void datetimeArray(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& datetimeArray_value() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n).value;
    }
    
    void datetimeArray_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool datetimeArray_exists() const
    {
        const size_t n = offsetof(Self, datetimeArray);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void datetimeArray_clear()
    {
        const size_t n = offsetof(Self, datetimeArray);
        GetField<DatetimeA>(n).Clear();
    }

    //
    // Outer_Class.stringArray
    //
    
    const Field<StringA>& stringArray() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n);
    }
    
    void stringArray(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n) = x;
    }
    
    const StringA& stringArray_value() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n).value;
    }
    
    void stringArray_value(const StringA& x)
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n).Set(x);
    }
    
    bool stringArray_exists() const
    {
        const size_t n = offsetof(Self, stringArray);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void stringArray_clear()
    {
        const size_t n = offsetof(Self, stringArray);
        GetField<StringA>(n).Clear();
    }

    //
    // Outer_Class.instanceArray
    //
    
    const Field<Inner_ClassA>& instanceArray() const
    {
        const size_t n = offsetof(Self, instanceArray);
        return GetField<Inner_ClassA>(n);
    }
    
    void instanceArray(const Field<Inner_ClassA>& x)
    {
        const size_t n = offsetof(Self, instanceArray);
        GetField<Inner_ClassA>(n) = x;
    }
    
    const Inner_ClassA& instanceArray_value() const
    {
        const size_t n = offsetof(Self, instanceArray);
        return GetField<Inner_ClassA>(n).value;
    }
    
    void instanceArray_value(const Inner_ClassA& x)
    {
        const size_t n = offsetof(Self, instanceArray);
        GetField<Inner_ClassA>(n).Set(x);
    }
    
    bool instanceArray_exists() const
    {
        const size_t n = offsetof(Self, instanceArray);
        return GetField<Inner_ClassA>(n).exists ? true : false;
    }
    
    void instanceArray_clear()
    {
        const size_t n = offsetof(Self, instanceArray);
        GetField<Inner_ClassA>(n).Clear();
    }
};

typedef Array<Outer_Class> Outer_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Outer_h */

