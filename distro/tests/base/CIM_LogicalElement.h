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
#ifndef _CIM_LogicalElement_h
#define _CIM_LogicalElement_h

#include <MI.h>
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_LogicalElement [CIM_LogicalElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_LogicalElement /* extends CIM_ManagedSystemElement */
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
}
CIM_LogicalElement;

typedef struct _CIM_LogicalElement_Ref
{
    CIM_LogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_LogicalElement_Ref;

typedef struct _CIM_LogicalElement_ConstRef
{
    MI_CONST CIM_LogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_LogicalElement_ConstRef;

typedef struct _CIM_LogicalElement_Array
{
    struct _CIM_LogicalElement** data;
    MI_Uint32 size;
}
CIM_LogicalElement_Array;

typedef struct _CIM_LogicalElement_ConstArray
{
    struct _CIM_LogicalElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_LogicalElement_ConstArray;

typedef struct _CIM_LogicalElement_ArrayRef
{
    CIM_LogicalElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_LogicalElement_ArrayRef;

typedef struct _CIM_LogicalElement_ConstArrayRef
{
    CIM_LogicalElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_LogicalElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_LogicalElement_rtti;


/*
**==============================================================================
**
** CIM_LogicalElement_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_LogicalElement_Class : public CIM_ManagedSystemElement_Class
{
public:
    
    typedef CIM_LogicalElement Self;
    
    CIM_LogicalElement_Class() :
        CIM_ManagedSystemElement_Class(&CIM_LogicalElement_rtti)
    {
    }
    
    CIM_LogicalElement_Class(
        const CIM_LogicalElement* instanceName,
        bool keysOnly) :
        CIM_ManagedSystemElement_Class(
            &CIM_LogicalElement_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_LogicalElement_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_ManagedSystemElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_LogicalElement_Class(
        const MI_ClassDecl* clDecl) :
        CIM_ManagedSystemElement_Class(clDecl)
    {
    }
    
    CIM_LogicalElement_Class& operator=(
        const CIM_LogicalElement_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_LogicalElement_Class(
        const CIM_LogicalElement_Class& x) :
        CIM_ManagedSystemElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_LogicalElement_rtti;
    }

};

typedef Array<CIM_LogicalElement_Class> CIM_LogicalElement_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_LogicalElement_h */
