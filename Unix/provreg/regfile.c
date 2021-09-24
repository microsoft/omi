/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <pal/strings.h>
#include <base/list.h>
#include <pal/format.h>
#include <pal/file.h>
#include <base/log.h>
#include "regfile.h"

#define REG_INDICATION_CLASS "INDICATIONCLASS"

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

// Parse class path of the form "CLASS1:CLASS2:CLASS3"
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

/*
 * Parses <value> from `*CLASS=<value>` of the forms from .reg file:
 * 1. `<ClassPath>`                             (Non-Association class)
 * 2. `<ClassPath>{<ClassPath>,<ClassPath>}`    (Association class)
 */
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



/* Parse indication class from reg file */
_Return_type_success_(return == 0)
int ParseIndicationClass(
    _Inout_ CharPtr* pOut,
    _Inout_ RegFile* self,
    _In_opt_z_ char* hosting,
    _In_ ProvRegType type)
{
#ifdef DISABLE_INDICATION
    /* Ignore indication classes */
    MI_UNUSED(pOut);
    MI_UNUSED(self);
    MI_UNUSED(hosting);
    MI_UNUSED(type);
    return 0;
#else /* ifndef DISABLE_INDICATION */
    char* name = NULL;
    char* refName1 = NULL;
    char* refName2 = NULL;
    RegClass* rc;

    if (_ParseClassValue(pOut, &name, &refName1, &refName2) != 0)
    {
        trace_RegFile_ParseIndication_ClassValueFailed();
        return -1;
    }

    rc = (RegClass*)PAL_Calloc(1, sizeof(RegClass));
    if (!rc)
    {
        trace_RegFile_AllocFailure();
        return -1;
    }

    List_Append(
        (ListElem**)&self->classesHead,
        (ListElem**)&self->classesTail,
        (ListElem*)rc);

    if (refName1 || refName2)
    {
        trace_RegFile_IndicationClassCannotHaveRefClass();
        return -1;
    }

    rc->name = PAL_Strdup(name);
    if (!rc->name)
    {
        trace_RegFile_OutOfMemory_Name();
        return -1;
    }

    if (hosting)
    {
        rc->hosting = PAL_Strdup(hosting);
        if(!rc->hosting)
        {
            trace_RegFile_OutOfMemory_Hosting();
            return -1;
        }
    }
    rc->regtype = type;
    return 0;
#endif /* ifndef DISABLE_INDICATION */
}


RegFile* RegFile_New(const char* path)
{
    FILE* is;
    char buf[MAX_LINE];
    int foundLibrary = 0;
    char* hosting = NULL;
    RegFile* self = 0;

    /* Open the file */
    is = File_Open(path, "rb");
    if (!is)
        return NULL;

    /* Allocate self structure */
    self = (RegFile*)PAL_Calloc(1, sizeof(RegFile));
    if (!self)
    {
        fclose(is);
        return NULL;
    }

    self->interpreter = NULL;
    self->startup = NULL;

    /* Read line by line */
    while (fgets(buf, sizeof(buf), is) != NULL)
    {
        char* start = buf;
        char* p = start;
        char* key;
        char* value;

        /* Skip leading whitespace */
        while (*p && isspace((unsigned char)(*p)))
            p++;

        /* Skip comment lines */
        if (*p == '#')
            continue;

        /* Remove trailing whitespace */
        {
            char* end = buf + strlen(buf);

            while (end != start && isspace((unsigned char)end[-1]))
                *--end = '\0';
        }
               
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

            self->library = PAL_Strdup(value);

            if (!self->library)
                goto failed;

            foundLibrary = 1;
        }
        else if (strcmp(key, "HOSTING") == 0)
        {
            if (hosting)
                PAL_Free(hosting);

            hosting = PAL_Strdup(value);
        }
        else if (strcmp(key, "INSTANCELIFETIME") == 0)
        {
            if (strcmp(value, "CONTEXT") == 0)
            {
                self->instanceLifetimeContext = 1;
            }
            else
            {
                goto failed;
            }
        }
#if defined(CONFIG_ENABLE_PREEXEC)
        else if (strcmp(key, "PREEXEC") == 0)
        {
            self->preexec = PAL_Strdup(value);
        }
#endif /* defined(CONFIG_ENABLE_PREEXEC) */
        else if (strcmp(key, "CLASS") == 0)
        {
            char* name;
            char* refName1;
            char* refName2;
            RegClass* rc;

            if (_ParseClassValue(&p, &name, &refName1, &refName2) != 0)
                goto failed;

            rc = (RegClass*)PAL_Calloc(1, sizeof(RegClass));
            if (!rc)
                goto failed;

            List_Append(
                (ListElem**)&self->classesHead,
                (ListElem**)&self->classesTail,
                (ListElem*)rc);

            rc->name = PAL_Strdup(name);
            if (!rc->name)
                goto failed;

            if (refName1)
            {
                rc->refName1 = PAL_Strdup(refName1);
                if (!rc->refName1)
                    goto failed;
            }

            if (refName2)
            {
                rc->refName2 = PAL_Strdup(refName2);
                if (!rc->refName2)
                    goto failed;
            }

            if (hosting)
            {
                rc->hosting = PAL_Strdup(hosting);
                if(!rc->hosting)
                    goto failed;
            }
        }
        else if (strcmp(key, "EXTRACLASS") == 0)
        {
            char* name;
            char* refName1;
            char* refName2;
            RegClass* rc;

            if (_ParseClassValue(&p, &name, &refName1, &refName2) != 0)
                goto failed;

            rc = (RegClass*)PAL_Calloc(1, sizeof(RegClass));
            if (!rc)
                goto failed;

            List_Append(
                (ListElem**)&self->extraClassesHead,
                (ListElem**)&self->extraClassesTail,
                (ListElem*)rc);

            rc->name = PAL_Strdup(name);
            if (!rc->name)
                goto failed;

            /* no need to use refName1, refName2 as the definition of these classes will be present as part of CLASSES list or EXTRACLASSES list */

            if (hosting)
            {
                rc->hosting = PAL_Strdup(hosting);
                if(!rc->hosting)
                    goto failed;
            }
        }
        else if (strcmp(key, REG_INDICATION_CLASS) == 0)
        {
            int r = ParseIndicationClass(&p, self, hosting, PROVREG_INDICATION);
            if (r == -1)
                goto failed;
        }
        else if (0 == strcmp (key, "INTERPRETER"))
        {
            if (self->interpreter)
            {
                goto failed;
            }
            if (NULL == value || 0 == strlen (value))
            {
                goto failed;
            }
            self->interpreter = PAL_Strdup(value);
            if (!self->interpreter)
            {
                goto failed;
            }
        }
        else if (0 == strcmp (key, "STARTUP"))
        {
            if (self->startup)
            {
                goto failed;
            }
            if (NULL == value || 0 == strlen (value))
            {
                goto failed;
            }
            self->startup = PAL_Strdup(value);
            if (!self->startup)
            {
                goto failed;
            }
        }
    }

    if (hosting)
        PAL_Free(hosting);

    /*If LIBRARY was not found (That should NOT happen),
    which means that this regfile is corrupted (The user might have modified it by hand). So go to failed*/
    if(!foundLibrary)
    {
        trace_RegFile_MissingLibraryTag(path);
        goto failed;
    }

    fclose(is);

    return self;

failed:
    if (self)
        RegFile_Delete(self);

    if (is)
        fclose(is);

    return NULL;
}

static void _RegClassList_Delete(RegClass *regClassHead)
{
    RegClass* rc;
    RegClass* next;
    
    for(rc = regClassHead; rc; rc = next)
    {
        if (rc->name)
            PAL_Free(rc->name);
        
        if (rc->refName1)
            PAL_Free(rc->refName1);
        
        if (rc->refName2)
            PAL_Free(rc->refName2);
        
        if (rc->hosting)
            PAL_Free(rc->hosting);
        
        next = rc->next;
        PAL_Free(rc);
    }
}

void RegFile_Delete(RegFile* self)
{
    if (!self)
        return;

    if (self->library)
        PAL_Free(self->library);

    if (self->interpreter)
        PAL_Free(self->interpreter);

    if (self->startup)
        PAL_Free(self->startup);

#if defined(CONFIG_ENABLE_PREEXEC)

    if (self->preexec)
        PAL_Free(self->preexec);

#endif /* defined(CONFIG_ENABLE_PREEXEC) */

    _RegClassList_Delete(self->classesHead);
    _RegClassList_Delete(self->extraClassesHead);

    PAL_Free(self);
}

void RegFile_Print(RegFile* self, FILE* os)
{
    RegClass* rc;

    Ftprintf(os, ZT("LIBRARY=%s\n"), scs(self->library));

#if defined(CONFIG_ENABLE_PREEXEC)

    Ftprintf(os, ZT("PREEXEC=%s\n"), scs(self->preexec));

#endif /* defined(CONFIG_ENABLE_PREEXEC) */

    for (rc = self->classesHead; rc; rc = rc->next)
    {
        Ftprintf(os, ZT("CLASS=%s"), scs(rc->name));

        if (rc->refName1 && rc->refName2)
        {
            Ftprintf(os, ZT("{"));
            Ftprintf(os, ZT("%s"), scs(rc->refName1));
            Ftprintf(os, ZT(","));
            Ftprintf(os, ZT("%s"), scs(rc->refName2));
            Ftprintf(os, ZT("}"));
        }

        Ftprintf(os, ZT("\n"));
    }
}
