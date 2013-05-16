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
#ifndef _MSFT_Person_h
#define _MSFT_Person_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_Person [MSFT_Person]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_Person
{
    MI_Instance __instance;
    /* MSFT_Person properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstStringField First;
    MI_ConstStringField Last;
    MI_ConstStringAField Colors;
    MI_ConstUint32AField Numbers;
    MI_ConstUint32Field Nothing;
}
MSFT_Person;

typedef struct _MSFT_Person_Ref
{
    MSFT_Person* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_Ref;

typedef struct _MSFT_Person_ConstRef
{
    MI_CONST MSFT_Person* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ConstRef;

typedef struct _MSFT_Person_Array
{
    struct _MSFT_Person** data;
    MI_Uint32 size;
}
MSFT_Person_Array;

typedef struct _MSFT_Person_ConstArray
{
    struct _MSFT_Person MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Person_ConstArray;

typedef struct _MSFT_Person_ArrayRef
{
    MSFT_Person_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ArrayRef;

typedef struct _MSFT_Person_ConstArrayRef
{
    MSFT_Person_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Person_rtti;


/*
**==============================================================================
**
** MSFT_Person_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Person_Class : public Instance
{
public:
    
    typedef MSFT_Person Self;
    
    MSFT_Person_Class() :
        Instance(&MSFT_Person_rtti)
    {
    }
    
    MSFT_Person_Class(
        const MSFT_Person* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Person_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Person_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Person_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Person_Class& operator=(
        const MSFT_Person_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Person_Class(
        const MSFT_Person_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Person_rtti;
    }

    //
    // MSFT_Person_Class.Key
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
    // MSFT_Person_Class.First
    //
    
    const Field<String>& First() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n);
    }
    
    void First(const Field<String>& x)
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n) = x;
    }
    
    const String& First_value() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n).value;
    }
    
    void First_value(const String& x)
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n).Set(x);
    }
    
    bool First_exists() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n).exists ? true : false;
    }
    
    void First_clear()
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_Person_Class.Last
    //
    
    const Field<String>& Last() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n);
    }
    
    void Last(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n) = x;
    }
    
    const String& Last_value() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n).value;
    }
    
    void Last_value(const String& x)
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n).Set(x);
    }
    
    bool Last_exists() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Last_clear()
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_Person_Class.Colors
    //
    
    const Field<StringA>& Colors() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n);
    }
    
    void Colors(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n) = x;
    }
    
    const StringA& Colors_value() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n).value;
    }
    
    void Colors_value(const StringA& x)
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n).Set(x);
    }
    
    bool Colors_exists() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void Colors_clear()
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n).Clear();
    }

    //
    // MSFT_Person_Class.Numbers
    //
    
    const Field<Uint32A>& Numbers() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n);
    }
    
    void Numbers(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& Numbers_value() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n).value;
    }
    
    void Numbers_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool Numbers_exists() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void Numbers_clear()
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n).Clear();
    }

    //
    // MSFT_Person_Class.Nothing
    //
    
    const Field<Uint32>& Nothing() const
    {
        const size_t n = offsetof(Self, Nothing);
        return GetField<Uint32>(n);
    }
    
    void Nothing(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Nothing);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Nothing_value() const
    {
        const size_t n = offsetof(Self, Nothing);
        return GetField<Uint32>(n).value;
    }
    
    void Nothing_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Nothing);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Nothing_exists() const
    {
        const size_t n = offsetof(Self, Nothing);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Nothing_clear()
    {
        const size_t n = offsetof(Self, Nothing);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<MSFT_Person_Class> MSFT_Person_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Person_h */
