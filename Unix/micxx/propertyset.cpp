/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "propertyset.h"

MI_BEGIN_NAMESPACE

PropertySet::PropertySet(MI_PropertySet* propertySet) : _rep(propertySet)
{
}

MI_Uint32 PropertySet::GetSize() const
{
    MI_Uint32 n;

    if (MI_PropertySet_GetElementCount(_rep, &n) != MI_RESULT_OK)
        return 0;

    return n;
}

bool PropertySet::Contains(const String& name) const
{
    MI_Boolean b;

    if (MI_PropertySet_ContainsElement(_rep, name.Str(), &b) != MI_RESULT_OK)
        return false;

    return b ? true : false;
}

bool PropertySet::Add(const String& name)
{
    if (MI_PropertySet_AddElement(_rep, name.Str()) != MI_RESULT_OK)
        return false;

    return true;
}

void PropertySet::Clear()
{
    MI_PropertySet_Clear(_rep);
}

bool PropertySet::Get(MI_Uint32 index, String& name) const
{
    const MI_Char* tmp;

    if (MI_PropertySet_GetElement(_rep, index, &tmp) != MI_RESULT_OK)
        return false;

    name = tmp;
    return true;
}

MI_END_NAMESPACE
