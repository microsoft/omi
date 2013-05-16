#include "wql.h"
#include <ctype.h>
#include <base/strings.h>
#include "state.h"
#include "wqlyacc.h"

extern void* wqlmalloc(size_t size);
extern MI_Char* wqlstrdup(const MI_Char* str);

int wqllex()
{
    const MI_Char* p = wqlstate.ptr;

    /* Skip whitespace */
    while (*p && isspace(*p))
        p++;

    /* Return on end-of-file */
    if (*p == '\0')
    {
        wqlstate.ptr = p;
        return 0;
    }

    /* Recognize identifier */
    if (isalpha(*p) || *p == '_')
    {
        const MI_Char* start = p++;
        size_t n;

        while (isalnum(*p) || *p == '_')
            p++;

        wqlstate.ptr = p;
        n = p - start;

        if (n == 6 && Zncasecmp(start, MI_T("select"), 6) == 0)
            return WQL_SELECT;
        else if (n == 4 && Zncasecmp(start, MI_T("from"), 4) == 0)
            return WQL_FROM;
        else if (n == 5 && Zncasecmp(start, MI_T("where"), 5) == 0)
            return WQL_WHERE;
        else if (n == 3 && Zncasecmp(start, MI_T("not"), 3) == 0)
            return WQL_NOT;
        else if (n == 3 && Zncasecmp(start, MI_T("and"), 3) == 0)
            return WQL_AND;
        else if (n == 2 && Zncasecmp(start, MI_T("or"), 2) == 0)
            return WQL_OR;
        else if (n == 4 && Zncasecmp(start, MI_T("null"), 4) == 0)
            return WQL_NULL;
        else if (n == 4 && Zncasecmp(start, MI_T("like"), 4) == 0)
            return WQL_LIKE;
        else if (n == 4 && Zncasecmp(start, MI_T("true"), 4) == 0)
        {
            wqllval.boolean = 1;
            return WQL_BOOLEAN;
        }
        else if (n == 5 && Zncasecmp(start, MI_T("false"), 5) == 0)
        {
            wqllval.boolean = 0;
            return WQL_BOOLEAN;
        }

        n = p - start;
        wqllval.string = (MI_Char*)wqlmalloc(n + 1);

        if (wqllval.string == NULL)
            return -1;

        memcpy(wqllval.string, start, n);
        wqllval.string[n] = '\0';

        return WQL_IDENTIFIER;
    }

    /* Recognize number (integer or double) */
    if (*p == '+' || *p == '-' || isdigit(*p))
    {
        const MI_Char* start = p++;

        while (isdigit(*p))
            p++;

        if (*p == '.')
        {
            MI_Char* end;
            wqllval.real = Ztod(start, &end);
            p = end;
            wqlstate.ptr = p;
            return WQL_REAL;
        }
        else
        {
            MI_Char* end;
            wqllval.integer = Ztoll(start, &end, 10);
            p = end;
            wqlstate.ptr = p;
            return WQL_INTEGER;
        }
    }

    /* Recognize string literal enclosed in '"' */
    if (*p == '"')
    {
        const MI_Char* start = ++p;
        size_t n = 0;
        MI_Char* q;

        /* Determine the length of the string */
        while (*p != '\0' && *p != '"')
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
            q = (MI_Char*)wqlmalloc(n + 1);

            if (q == NULL)
                return -1;

            wqllval.string = q;
        }

        /* Convert string */
        for (p = start; *p != '\0' && *p != '"'; )
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
                    case 'f':
                        *q++ = '\r';
                        break;
                    default:
                        *q++ = *p;
                }
                p++;
            }
            else
                *q++ = *p++;
        }

        /* String literal must be terminated or there is an error */
        if (*p == '\0')
            return -1;
        p++;

        /* NUL-terminate string */
        *q = '\0';
        wqlstate.ptr = p;
        return WQL_STRING;
    }

    /* Recognize string literal enclosed in "'" */
    if (*p == '\'')
    {
        const MI_Char* start = ++p;
        size_t n = 0;
        MI_Char* q;

        /* Determine the length of the string */
        while (*p != '\0' && *p != '\'')
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
            q = (MI_Char*)wqlmalloc(n + 1);

            if (q == NULL)
                return -1;

            wqllval.string = q;
        }

        /* Convert string */
        for (p = start; *p != '\0' && *p != '\''; )
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
                    case 'f':
                        *q++ = '\r';
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
        if (*p == '\0')
            return -1;
        p++;

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

    /* Unrecognized tokens */
    return WQL_ERROR;
}
