/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
