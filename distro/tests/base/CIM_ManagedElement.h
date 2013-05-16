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
#ifndef _CIM_ManagedElement_h
#define _CIM_ManagedElement_h

#include <MI.h>

/*
**==============================================================================
**
** CIM_ManagedElement [CIM_ManagedElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_ManagedElement
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
}
CIM_ManagedElement;

typedef struct _CIM_ManagedElement_Ref
{
    CIM_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_Ref;

typedef struct _CIM_ManagedElement_ConstRef
{
    MI_CONST CIM_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ConstRef;

typedef struct _CIM_ManagedElement_Array
{
    struct _CIM_ManagedElement** data;
    MI_Uint32 size;
}
CIM_ManagedElement_Array;

typedef struct _CIM_ManagedElement_ConstArray
{
    struct _CIM_ManagedElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ManagedElement_ConstArray;

typedef struct _CIM_ManagedElement_ArrayRef
{
    CIM_ManagedElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ArrayRef;

typedef struct _CIM_ManagedElement_ConstArrayRef
{
    CIM_ManagedElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ManagedElement_rtti;


/*
**==============================================================================
**
** CIM_ManagedElement_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_ManagedElement_Class : public Instance
{
public:
    
    typedef CIM_ManagedElement Self;
    
    CIM_ManagedElement_Class() :
        Instance(&CIM_ManagedElement_rtti)
    {
    }
    
    CIM_ManagedElement_Class(
        const CIM_ManagedElement* instanceName,
        bool keysOnly) :
        Instance(
            &CIM_ManagedElement_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_ManagedElement_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    CIM_ManagedElement_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    CIM_ManagedElement_Class& operator=(
        const CIM_ManagedElement_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_ManagedElement_Class(
        const CIM_ManagedElement_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_ManagedElement_rtti;
    }

    //
    // CIM_ManagedElement_Class.InstanceID
    //
    
    const Field<String>& InstanceID() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n);
    }
    
    void InstanceID(const Field<String>& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n) = x;
    }
    
    const String& InstanceID_value() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).value;
    }
    
    void InstanceID_value(const String& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Set(x);
    }
    
    bool InstanceID_exists() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).exists ? true : false;
    }
    
    void InstanceID_clear()
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Clear();
    }

    //
    // CIM_ManagedElement_Class.Caption
    //
    
    const Field<String>& Caption() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n);
    }
    
    void Caption(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n) = x;
    }
    
    const String& Caption_value() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n).value;
    }
    
    void Caption_value(const String& x)
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n).Set(x);
    }
    
    bool Caption_exists() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Caption_clear()
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n).Clear();
    }

    //
    // CIM_ManagedElement_Class.Description
    //
    
    const Field<String>& Description() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n);
    }
    
    void Description(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n) = x;
    }
    
    const String& Description_value() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).value;
    }
    
    void Description_value(const String& x)
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Set(x);
    }
    
    bool Description_exists() const
    {
        const size_t n = offsetof(Self, Description);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Description_clear()
    {
        const size_t n = offsetof(Self, Description);
        GetField<String>(n).Clear();
    }

    //
    // CIM_ManagedElement_Class.ElementName
    //
    
    const Field<String>& ElementName() const
    {
        const size_t n = offsetof(Self, ElementName);
        return GetField<String>(n);
    }
    
    void ElementName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ElementName);
        GetField<String>(n) = x;
    }
    
    const String& ElementName_value() const
    {
        const size_t n = offsetof(Self, ElementName);
        return GetField<String>(n).value;
    }
    
    void ElementName_value(const String& x)
    {
        const size_t n = offsetof(Self, ElementName);
        GetField<String>(n).Set(x);
    }
    
    bool ElementName_exists() const
    {
        const size_t n = offsetof(Self, ElementName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ElementName_clear()
    {
        const size_t n = offsetof(Self, ElementName);
        GetField<String>(n).Clear();
    }
};

typedef Array<CIM_ManagedElement_Class> CIM_ManagedElement_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_ManagedElement_h */
