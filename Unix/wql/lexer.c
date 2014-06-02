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

#include "wql.h"
#include <ctype.h>

#if defined(CONFIG_POSIX)
# include <wctype.h>
#endif

#include <pal/strings.h>
#include <pal/format.h>
#include "state.h"
#include "wqlyacc.h"


extern void* wqlmalloc(size_t size);
extern ZChar* wqlstrdup(const ZChar* str);

MI_INLINE int _MatchToken(
    const ZChar* str,
    const ZChar* lcs, /* lower-case-string */
    size_t n)
{
#if (MI_CHAR_TYPE == 1)
    return tolower((int)str[0]) == lcs[0] &&
           Tcsncasecmp(str, lcs, n) == 0 &&
           !isalpha((int)str[n]) &&
           str[n] != '_';
#else
    return towlower(str[0]) == lcs[0] &&
           Tcsncasecmp(str, lcs, n) == 0 &&
           !isalpha((int)str[n] &&
           str[n] != '_';
#endif
}

int wqllex()
{
    const ZChar* p = wqlstate.ptr;

    /* Skip whitespace */
    while (*p && isspace((int)*p))
        p++;

    /* Return on end-of-file */
    if (*p == '\0')
    {
        wqlstate.ptr = p;
        return 0;
    }

    /* Recognize identifier */
    if (isalpha((int)*p) || *p == '_')
    {
        const ZChar* start = p++;
        size_t n;

        while (isalnum((int)*p) || *p == '_')
            p++;

        wqlstate.ptr = p;
        n = p - start;

        if (_MatchToken(start, MI_T("select"), 6))
            return WQL_SELECT;
        else if (_MatchToken(start, MI_T("from"), 4))
            return WQL_FROM;
        else if (_MatchToken(start, MI_T("where"), 5))
            return WQL_WHERE;
        else if (_MatchToken(start, MI_T("not"), 3))
            return WQL_NOT;
        else if (_MatchToken(start, MI_T("and"), 3))
            return WQL_AND;
        else if (_MatchToken(start, MI_T("or"), 2))
            return WQL_OR;
        else if (_MatchToken(start, MI_T("null"), 4))
            return WQL_NULL;
        else if (_MatchToken(start, MI_T("true"), 4))
        {
            wqllval.boolean = 1;
            return WQL_BOOLEAN;
        }
        else if (_MatchToken(start, MI_T("false"), 5))
        {
            wqllval.boolean = 0;
            return WQL_BOOLEAN;
        }
        else if (_MatchToken(start, MI_T("like"), 4))
            return WQL_LIKE;
        else if (_MatchToken(start, MI_T("isa"), 3))
            return WQL_ISA;

        wqllval.string = (ZChar*)wqlmalloc((n + 1) * sizeof(ZChar));

        if (!wqllval.string)
            return -1;

        memcpy(wqllval.string, start, n * sizeof(ZChar));
        wqllval.string[n] = '\0';

        return WQL_IDENTIFIER;
    }

    /* Recognize number (integer or double) */
    if (*p == '+' || *p == '-' || isdigit(*p))
    {
        const ZChar* start = p++;

        while (isdigit(*p))
            p++;

        if (*p == '.')
        {
            ZChar* end;
            wqllval.real = Tcstod(start, &end);
            p = end;
            wqlstate.ptr = p;
            return WQL_REAL;
        }
        else
        {
            ZChar* end;
            wqllval.integer = Tcstoll(start, &end, 10);
            p = end;
            wqlstate.ptr = p;
            return WQL_INTEGER;
        }
    }

    /* Recognize string literal, starting with full quote or semi quote */
    if (*p == '"' || *p == '\'')
    {
        ZChar term = *p;
        const ZChar* start = ++p;
        size_t n = 0;
        ZChar* q;

        /* Determine the length of the string */
        while (*p && *p != term)
        {
            if (*p == '\\')
            {
                if (*++p == '\0')
                    return -1;
            }

            p++;
            n++;
        }

        /* Allocate new string */
        {
            q = wqlmalloc((n + 1) * sizeof(ZChar));

            if (!q)
                return -1;

            wqllval.string = q;
        }

        /* Convert string */
        for (p = start; *p && *p != term; )
        {
            if (*p == '\\')
            {
                p++;
                switch (*p)
                {
                    case '\0':
                        return -1;
                    case 'n':
                        *q++ = '\n';
                        break;
                    case 'r':
                        *q++ = '\r';
                        break;
                    case 'f':
                        *q++ = '\r';
                        break;
                    case '"':
                        *q++ = '"';
                        break;
                    case '\\':
                        *q++ = '\\';
                        break;
                    default:
                        *q++ = *p;
                }
                p++;
            }
            else
                *q++ = *p++;
        }

        /* String literal must be terminated */
        if (*p++ != term)
            return -1;

        /* Null terminate string */
        *q = '\0';
        wqlstate.ptr = p;
        return WQL_STRING;
    }

    /* WQL_EQ */
    if (p[0] == '=')
    {
        wqlstate.ptr = p + 1;
        return WQL_EQ;
    }

    /* WQL_NE */
    if ((p[0] == '<' && p[1] == '>') || (p[0] == '!' && p[1] == '='))
    {
        wqlstate.ptr = p + 2;
        return WQL_NE;
    }

    /* WQL_LE */
    if (p[0] == '<' && p[1] == '=')
    {
        wqlstate.ptr = p + 2;
        return WQL_LE;
    }

    /* WQL_LT */
    if (p[0] == '<')
    {
        wqlstate.ptr = p + 1;
        return WQL_LT;
    }

    /* WQL_GE */
    if (p[0] == '>' && p[1] == '=')
    {
        wqlstate.ptr = p + 2;
        return WQL_GE;
    }

    /* WQL_GT */
    if (p[0] == '>')
    {
        wqlstate.ptr = p + 1;
        return WQL_GT;
    }

    /* Match single characters */
    if (*p == '*' || *p == '(' || *p == ')' || *p == ',')
    {
        wqlstate.ptr = p + 1;
        return *p;
    }

    /* WQL_GT */
    if (p[0] == '.')
    {
        wqlstate.ptr = p + 1;
        return WQL_DOT;
    }

    /* WQL_COLON */
    if (p[0] == ':')
    {
        wqlstate.ptr = p + 1;
        return WQL_COLON;
    }

    /* Unrecognized tokens */
    return WQL_ERROR;
}
