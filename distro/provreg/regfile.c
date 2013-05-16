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

#include <stdio.h>
#include <ctype.h>
#include <base/strings.h>
#include <base/list.h>
#include <io/io.h>
#include "regfile.h"

// Parse an identifies of the form "[A-Za-z_][A-Za-z_0-9]*"
_Return_type_success_(return == 0)
static int _ParseIdentifier(_Inout_ CharPtr* pOut, _Out_ CharPtr* start, _Out_ CharPtr* end)
{
    char* p = *pOut;

    /* Skip leading whitespace */
    while (*p && isspace((unsigned char)(*p)))
        p++;

    /* Set start of identifier */
    *start = p;

    /* Expect [A-Za-z_] characters */
    if (!isalpha((unsigned char)(*p)) && *p != '_')
        return -1;

    /* Skip [A-Za-z_0-9] characters */
    while (*p && (isalnum((unsigned char)(*p)) || *p == '_'))
        p++;

    /* Set end of identifier */
    *end = p;

    *pOut = p;
    return 0;
}

// Parase class path of the form "CLASS1:CLASS2:CLASS3"
_Return_type_success_(return == 0)
static int _ParseClassPath(_Inout_ CharPtr* pOut, _Out_ CharPtr* start, _Out_ CharPtr* end)
{
    char* p = *pOut;

    /* Skip leading whitespace */
    while (*p && isspace((unsigned char)(*p)))
        p++;

    /* Set start of identifier */
    *start = p;

    /* Expect [A-Za-z_] characters */
    if (!isalpha((unsigned char)(*p)) && *p != '_')
        return -1;

    /* Skip [A-Za-z_0-9] characters */
    while (*p && (isalnum((unsigned char)(*p)) || *p == '_' || *p == ':'))
        p++;

    /* Set end of identifier */
    *end = p;

    *pOut = p;
    return 0;
}

_Return_type_success_(return == 0)
static int _ExpectChar(_Inout_ CharPtr* pOut, char ch)
{
    char* p = *pOut;

    /* Skip whitespace */
    while (*p && isspace((unsigned char)(*p)))
        p++;

    /* Expect character */
    if (*p != ch)
        return -1;
    p++;

    *pOut = p;
    return 0;
}

// Parse a line of the form 'KEY=VALUE'
_Return_type_success_(return == 0)
static int _ParseKeyValueLine(_Inout_ CharPtr* pOut, _Out_ CharPtr* keyOut, _Out_ CharPtr* valueOut)
{
    char* p = *pOut;
    char* keyEnd;

    /* Parse key */
    if (_ParseIdentifier(&p, keyOut, &keyEnd) != 0)
        return-1;

    /* If out of input, error out */
    if (!*p)
        return -1;

    /* Skip whitespace */
    if (_ExpectChar(&p, '=') != 0)
        return -1;

    /* Null-terminate the key */
    *keyEnd = '\0';

    /* Skip whitespace */
    while (*p && isspace((unsigned char)(*p)))
        p++;

    /* Set value */
    *valueOut = p;

    *pOut = p;
    return 0;
}

_Return_type_success_(return == 0)
static int _ParseClassValue(
    _Inout_ CharPtr* pOut,
    _Out_ CharPtr* nameOut,
    _Out_ CharPtr* refName1Out,
    _Out_ CharPtr* refName2Out)
{
    char* p = *pOut;
    char* start;
    char* end;

    /* Expect class name */
    if (_ParseClassPath(&p, &start, &end) != 0)
        return -1;

    /* Skip whitespace */
    while (*p && isspace((unsigned char)(*p)))
        p++;

    /* If end of line */
    if (!*p)
    {
        *nameOut = start;
        *end = '\0';
        *refName1Out = NULL;
        *refName2Out = NULL;
        *pOut = p;
        return 0;
    }

    /* Expect '{' character */
    if (_ExpectChar(&p, '{') != 0)
        return -1;

    /* Get 'name' */
    *nameOut = start;
    *end = '\0';

    /* Expect reference name */
    if (_ParseClassPath(&p, &start, &end) != 0)
        return -1;

    /* Expect ',' character */
    if (_ExpectChar(&p, ',') != 0)
        return -1;

    /* Get 'refName1' */
    *refName1Out = start;
    *end = '\0';

    /* Expect reference name */
    if (_ParseClassPath(&p, &start, &end) != 0)
        return -1;

    /* Expect '}' character */
    if (_ExpectChar(&p, '}') != 0)
        return -1;

    /* Get 'refName1' */
    *refName2Out = start;
    *end = '\0';

    *pOut = p;
    return 0;
}

RegFile* RegFile_New(const char* path)
{
    FILE* is;
    char buf[1024];
    int foundLibrary = 0;
    char* hosting = NULL;

    RegFile* self = 0;

    /* Open the file */
    is = Fopen(path, "rb");
    if (!is)
        return NULL;

    /* Allocate self structure */
    self = (RegFile*)calloc(1, sizeof(RegFile));
    if (!self)
    {
        fclose(is);
        return NULL;
    }

    /* Read line by line */
    while (fgets(buf, sizeof(buf), is) != NULL)
    {
        char* start = buf;
        char* p = start;
        char* key;
        char* value;

        /* Skip comment lines */
        if (*p == '#')
            continue;

        /* Remove trailing whitespace */
        {
            char* end = buf + strlen(buf);

            while (end != start && isspace((unsigned char)end[-1]))
                *--end = '\0';
        }

        /* Skip leading whitespace */
        while (*p && isspace((unsigned char)(*p)))
            p++;

        /* Skip blank lines */
        if (*p == '\0')
            continue;

        /* Look for LIBRARY= */
        if (_ParseKeyValueLine(&p, &key, &value) != 0)
            goto failed;

        if (strcmp(key, "LIBRARY") == 0)
        {
            if (foundLibrary)
                goto failed;

            self->library = Strdup(value);

            if (!self->library)
                goto failed;

            foundLibrary = 1;
        }
        else if (strcmp(key, "HOSTING") == 0)
        {
            if (hosting)
                free(hosting);

            hosting = Strdup(value);
        }
        else if (strcmp(key, "CLASS") == 0)
        {
            char* name;
            char* refName1;
            char* refName2;
            RegClass* rc;

            if (_ParseClassValue(&p, &name, &refName1, &refName2) != 0)
                goto failed;

            rc = (RegClass*)calloc(1, sizeof(RegClass));
            if (!rc)
                goto failed;

            List_Append(
                (ListElem**)&self->classesHead,
                (ListElem**)&self->classesTail,
                (ListElem*)rc);

            rc->name = Strdup(name);
            if (!rc->name)
                goto failed;

            if (refName1)
            {
                rc->refName1 = Strdup(refName1);
                if (!rc->refName1)
                    goto failed;
            }

            if (refName2)
            {
                rc->refName2 = Strdup(refName2);
                if (!rc->refName2)
                    goto failed;
            }

            if (hosting)
                rc->hosting = Strdup(hosting);
        }
    }

    if (hosting)
        free(hosting);

    fclose(is);

    return self;

failed:
    if (self)
        RegFile_Delete(self);

    if (is)
        fclose(is);

    return NULL;
}

void RegFile_Delete(RegFile* self)
{
    RegClass* rc;
    RegClass* next;

    if (!self)
        return;

    if (self->library)
        free(self->library);

    for (rc = self->classesHead; rc; rc = next)
    {
        if (rc->name)
            free(rc->name);

        if (rc->refName1)
            free(rc->refName1);

        if (rc->refName2)
            free(rc->refName2);

        if (rc->hosting)
            free(rc->hosting);

        next = rc->next;
        free(rc);
    }

    free(self);
}

void RegFile_Print(RegFile* self, FILE* os)
{
    RegClass* rc;

    Fzprintf(os, ZT("LIBRARY=%s\n"), scs(self->library));

    for (rc = self->classesHead; rc; rc = rc->next)
    {
        Fzprintf(os, ZT("CLASS=%s"), scs(rc->name));

        if (rc->refName1 && rc->refName2)
        {
            Fzprintf(os, ZT("{"));
            Fzprintf(os, ZT("%s"), scs(rc->refName1));
            Fzprintf(os, ZT(","));
            Fzprintf(os, ZT("%s"), scs(rc->refName2));
            Fzprintf(os, ZT("}"));
        }

        Fzprintf(os, ZT("\n"));
    }
}
