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
#ifndef _Inner_h
#define _Inner_h

#include <MI.h>

/*
**==============================================================================
**
** Inner [Inner]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Inner
{
    MI_Instance __instance;
    /* Inner properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstStringField Str;
}
Inner;

typedef struct _Inner_Ref
{
    Inner* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Inner_Ref;

typedef struct _Inner_ConstRef
{
    MI_CONST Inner* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Inner_ConstRef;

typedef struct _Inner_Array
{
    struct _Inner** data;
    MI_Uint32 size;
}
Inner_Array;

typedef struct _Inner_ConstArray
{
    struct _Inner MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Inner_ConstArray;

typedef struct _Inner_ArrayRef
{
    Inner_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Inner_ArrayRef;

typedef struct _Inner_ConstArrayRef
{
    Inner_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Inner_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Inner_rtti;


/*
**==============================================================================
**
** Inner_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Inner_Class : public Instance
{
public:
    
    typedef Inner Self;
    
    Inner_Class() :
        Instance(&Inner_rtti)
    {
    }
    
    Inner_Class(
        const Inner* instanceName,
        bool keysOnly) :
        Instance(
            &Inner_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Inner_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Inner_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Inner_Class& operator=(
        const Inner_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Inner_Class(
        const Inner_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Inner_rtti;
    }

    //
    // Inner_Class.Key
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
    // Inner_Class.Str
    //
    
    const Field<String>& Str() const
    {
        const size_t n = offsetof(Self, Str);
        return GetField<String>(n);
    }
    
    void Str(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Str);
        GetField<String>(n) = x;
    }
    
    const String& Str_value() const
    {
        const size_t n = offsetof(Self, Str);
        return GetField<String>(n).value;
    }
    
    void Str_value(const String& x)
    {
        const size_t n = offsetof(Self, Str);
        GetField<String>(n).Set(x);
    }
    
    bool Str_exists() const
    {
        const size_t n = offsetof(Self, Str);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Str_clear()
    {
        const size_t n = offsetof(Self, Str);
        GetField<String>(n).Clear();
    }
};

typedef Array<Inner_Class> Inner_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Inner_h */
