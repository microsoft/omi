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

#ifndef _micxx_propertyset_h
#define _micxx_propertyset_h

#include <MI.h>
#include <string.h>
#include <stdio.h>
#include "linkage.h"
#include "micxx_string.h"

MI_BEGIN_NAMESPACE

class MICXX_LINKAGE PropertySet
{
public:

    PropertySet(MI_PropertySet* propertySet);

    ~PropertySet();

    MI_Uint32 GetSize() const;

    bool Contains(const String& name) const;

    bool Add(const String& name);

    bool Get(MI_Uint32 index, String& name) const;

    void Clear();

private:
    PropertySet();
    PropertySet(const PropertySet&);
    PropertySet& operator=(const PropertySet&);
    friend const PropertySet& __PropertySet(const MI_PropertySet* propertySet);

    MI_PropertySet* _rep;
};

inline PropertySet::~PropertySet()
{
}

inline const PropertySet& __PropertySet(const MI_PropertySet* propertySet)
{
    PropertySet* ptr = reinterpret_cast<PropertySet*>(
        const_cast<MI_PropertySet**>(&propertySet));
    return *ptr;
}

MI_END_NAMESPACE

#endif /* _micxx_propertyset_h */
