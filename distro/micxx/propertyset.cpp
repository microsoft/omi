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
