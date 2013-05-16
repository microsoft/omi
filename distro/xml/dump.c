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

#include "xml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io/io.h>

#define T MI_T

void XML_Elem_Dump(
    const XML_Elem* s)
{
    static const XML_Char* _typeNames[] =
    {
        T("NONE"),
        T("START"),
        T("END"),
        T("INSTRUCTION"),
        T("CHARS"),
        T("COMMENT"),
    };
    size_t i;

    Zprintf(T("type={%Z}\n"), zcs(_typeNames[(int)s->type]));
    Zprintf(T("data={%Z}\n"), zcs(s->data));
    Zprintf(T("size=%u\n"), (int)s->size);

    if (s->attrsSize)
    {
        for (i = 0; i < s->attrsSize; i++)
        {
            const XML_Attr* attr = &s->attrs[i];
            Zprintf(T("%Z=%Z\n"), zcs(attr->name), zcs(attr->value));
        }
    }

    Zprintf(T("\n"));
}

void XML_NameSpace_Dump(
    XML_NameSpace* self)
{
    Zprintf(T("==== XML_NameSpace:\n"));
    Zprintf(T("name={%Z}\n"), zcs(self->name));
    Zprintf(T("id={%c}\n"), (int)self->id);
    Zprintf(T("uri={%Z}\n"), zcs(self->uri));
    Zprintf(T("depth={%u}\n"), (int)self->depth);
    Zprintf(T("\n"));
}

void XML_Dump(
    XML* self)
{
    size_t i;

    Zprintf(T("==== XML:\n"));
    Zprintf(T("nameSpaces:\n"));

    for (i = 0; i < self->nameSpacesSize; i++)
    {
        XML_NameSpace_Dump(&self->nameSpaces[i]);
    }

    Zprintf(T("\n"));
}

void XML_PutError(XML* self)
{
    if (self->status == -1)
    {
        Zprintf(
            T("line %u: %Z\n"),
            (int)self->line,
            zcs(self->message));
    }
}
