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

#include <common.h>
#include "xml.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <io/io.h>

#if defined(_MSC_VER)
/* PreFast - reviewed and believed to be false-positive*/

/* warning C6385: Invalid data: accessing '??', the readable size is 'x' bytes, but 'y' bytes might be read: Lines: ... */
# pragma warning(disable : 6385)
/* warning C6386: Buffer overrun: accessing 'self->registeredNameSpaces' ... */
# pragma warning(disable : 6386)

#endif /* _MSC_VER */

#if defined(CONFIG_ENABLE_WCHAR)
# define T(STR) L##STR
# define XML_strtoul wcstoul
# define XML_strcmp wcscmp
# define XML_strlen wcslen
#else
# define T(STR) STR
# define T(STR) STR
# define XML_strtoul strtoul
# define XML_strcmp strcmp
# define XML_strlen strlen
#endif

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

typedef enum _XML_State
{
    STATE_START,
    STATE_TAG,
    STATE_CHARS,
}
XML_State;

/* Space characters include [\n\t\r ]
 *     _spaceChar['\n'] => 1
 *     _spaceChar['\r'] => 2
 *     _spaceChar['\t'] => 2
 *     _spaceChar[' '] => 2
 */
static unsigned char _spaceChar[256] =
{
    0,0,0,0,0,0,0,0,0,2,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

INLINE int _IsSpace(XML_Char c)
{
#if defined(CONFIG_ENABLE_WCHAR)
    if (c >= 0 && c < 256)
        return _spaceChar[(unsigned char)c];
    else
        return 0;
#else
    return _spaceChar[(unsigned char)c];
#endif
}

/* Matches XML name characters of the form: [A-Za-z_][A-Za-z0-9_-.:]*
 *     _nameChar[A-Za-z_] => 2 (first character)
 *     _nameChar[A-Za-z0-9_-.:] => 1 or 2 (inner character)
 */
static unsigned char _nameChar[256] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
    0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,
    0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/*
    Skips N characters while checking that end of the string has not been hit
*/
INLINE XML_Char * _SkipChars(_In_z_ XML_Char* p, size_t count)
{
    size_t i;
    for (i = 0; i < count; ++i)
    {
        if (*p == 0)
        {
            return NULL;
        }

        p++;
    }

    return p;
}

INLINE int _IsFirst(XML_Char c)
{
#if defined(CONFIG_ENABLE_WCHAR)
    if (c >= 0 && c < 256)
        return _nameChar[(unsigned char)c] & 2;
    else
        return 0;
#else
    return _nameChar[(unsigned char)c] & 2;
#endif
}

INLINE int _IsInner(XML_Char c)
{
#if defined(CONFIG_ENABLE_WCHAR)
    if (c >= 0 && c < 256)
        return _nameChar[(unsigned char)c];
    else
        return 0;
#else
    return _nameChar[(unsigned char)c];
#endif
}

INLINE XML_Char* _SkipInner(_In_z_ XML_Char* p)
{
    while (*p && _IsInner(*p))
        p++;

    return p;
}

static XML_Char* _SkipSpacesAux(XML* self, _In_z_ XML_Char* p)
{
    XML_UChar x;
    size_t n = 0;

    while (*p && (x = (XML_UChar)_IsSpace(*p)) != 0)
    {
        n += 0x01 & x;
        p++;
    }

    self->line += n;
    return p;
}

INLINE XML_Char* _SkipSpaces(XML* self, _In_z_ XML_Char* p)
{
    if (!p[0] || !_IsSpace(p[0]))
        return p;

    if (p[0] == '\n')
        self->line++;

    if (!p[1] || !_IsSpace(p[1]))
        return &p[1];

    if (p[1] == '\n')
        self->line++;

    if (!p[2] || !_IsSpace(p[2]))
        return &p[2];

    if (p[2] == '\n')
        self->line++;

    return _SkipSpacesAux(self, &p[3]);
}

INLINE XML_Char* _ToEntityRef(XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
{
    /* Note: we collected the following statistics on the frequency of
     * each entity reference in a large body of XML documents:
     *
     *     &quot; - 74,480 occurences
     *     &apos; - 13,877 occurences
     *     &lt;   -  9,919 occurences
     *     &gt;   -  9,853 occurences
     *     &amp;  -    111 occurences
     *
     * The cases below are organized in order of statistical frequency.
     */

    /* Match one of these: "lt;", "gt;", "amp;", "quot;", "apos;" */

    if (p[0] == 'q' && p[1] == 'u' && p[2] == 'o' && p[3] == 't' && p[4] == ';')
    {
        *ch = '"';
        return p + 5;
    }

    if (p[0] == 'a' && p[1] == 'p' && p[2] == 'o' && p[3] == 's' && p[4] == ';')
    {
        *ch = '\'';
        return p + 5;
    }

    if (p[0] == 'l' && p[1] == 't' && p[2] == ';')
    {
        *ch = '<';
        return p + 3;
    }

    if (p[0] == 'g' && p[1] == 't' && p[2] == ';')
    {
        *ch = '>';
        return p + 3;
    }

    if (p[0] == 'a' && p[1] == 'm' && p[2] == 'p' && p[3] == ';')
    {
        *ch = '&';
        return p + 4;
    }

    *ch = 0;
    XML_Raise(self, T("bad entity reference"));
    return p;
}

INLINE XML_Char* _ToCharRef(XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
{
    XML_Char* end;
    unsigned long x;

    if (*p == 'x')
    {
        p++;
        x = XML_strtoul(p, &end, 16);
    }
    else
    {
        x = XML_strtoul(p, &end, 10);
    }

    if (end == p || *end != ';' || x > 255)
    {
        *ch = '\0';
        XML_Raise(self, T("bad character reference"));
        return p;
    }

    *ch = (XML_Char)x;

    return end + 1;
}

INLINE XML_Char* _ToRef(XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
{
    /* Examples:
     *     &#64;
     *     &xFF;
     *     &amp;
     *     &lt;
     */
    if (*p == '#')
        return _ToCharRef(self, p + 1, ch);
    else
        return _ToEntityRef(self, p, ch);
}

/* Matches all but '\0', '\'', '"', and '&'. All matching charcters
 * yeild 2, except for '\n', which yields 1
 */
static unsigned char _ReduceAttrValueMatchChars[256] =
{
    0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

INLINE int _ReduceAttrValueMatch(XML_Char c)
{
#if defined(CONFIG_ENABLE_WCHAR)
    if (c >= 0 && c < 256)
        return _ReduceAttrValueMatchChars[(unsigned char)c];
    else
        return 1;
#else
    return _ReduceAttrValueMatchChars[(unsigned char)c];
#endif
}

/* Reduce entity references and remove leading and trailing whitespace */
static XML_Char* _ReduceAttrValue(XML* self, _Inout_ XMLCharPtr* pInOut, XML_Char eos)
{
    _Null_terminated_ XML_Char* p = *pInOut;
    XML_Char* end;
    size_t n = 0;

    if (!p)
     return NULL;

    while (*p)
    {
        if (_ReduceAttrValueMatch(*p))
        {
            p++;
        }
        else
        {
            if (*p == '\0' || *p != '\n')
                break;

            self->line++;
            p++;
        }
    }

    end = p;

    while (*p && *p != eos)
    {
        if (*p == '&')
        {
            XML_Char c = '\0';
            XML_Char* tmp;

            p++;
            tmp = _ToRef(self, p, &c);

            if (self->status)
            {
                /* Propagate error */
                return NULL;
            }

            *end++ = c;
            p = tmp;
        }
        else
        {
            if (*p == '\n')
                n++;

            *end++ = *p++;
        }
    }

    *pInOut = p;
    self->line += n;

    return end;
}

/* Match all but these: '\0', '<', '&', '\n' */
static unsigned char _ReduceCharDataMatchChars[256] =
{
    0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

INLINE int _ReduceCharDataMatch(XML_Char c)
{
#if defined(CONFIG_ENABLE_WCHAR)
    if (c >= 0 && c < 256)
        return _ReduceCharDataMatchChars[(unsigned char)c];
    else
        return 1;
#else
    return _ReduceCharDataMatchChars[(unsigned char)c];
#endif
}

/* Reduce character data, advance p, and return pointer to end */
static XML_Char* _ReduceCharData(XML* self, _Inout_ XMLCharPtr* pInOut)
{
    XML_Char* p = *pInOut;
    XML_Char* end;
    size_t n = 0;

    if (!p)
        return NULL;

    while (*p)
    {
        if (_ReduceCharDataMatch(*p))
        {
            p++;
        }
        else
        {
            if (!*p || *p != '\n')
                break;

            self->line++;
            p++;
        }
    }

    end = p;

    /* Can we return now? */
    if (*p == '<')
    {
        *pInOut = p;
        self->line += n;
        return end;
    }

    /* Seek next tag start */
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26018)
#endif
    /* OACR does not like loops inside loops that modify buffer pointers, the logic however is correct */
    while (*p && *p != '<')
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
    {
        if (*p == '&')
        {
            XML_Char c = '\0';
            XML_Char* tmp;

            p++;
            tmp = _ToRef(self, p, &c);

            if (tmp == p)
                return NULL;

            *end++ = c;
            p = tmp;
        }
        else
        {
            for (;;)
            {
                while ((_ReduceCharDataMatch(*p)))
                    *end++ = *p++;

                if (*p != '\n')
                    break;

                *end++ = *p++;
                self->line++;
            }
        }
    }

    /* Document cannot end with character data */
    if (*p == '\0')
        return NULL;

    *pInOut = p;
    self->line += n;

    return end;
}

/* Calculate a fast hash code for a non-zero-length strings */
INLINE unsigned int _HashCode(const XML_Char* s, size_t n)
{
    /* This hash algorithm excludes the first character since for many strings
     * (e.g., URIs) the first character is not unique. Instead the hash
     * comprises three components:
     *     (1) The length
     *     (3) The last chacter
     */
    return (int)(n ^ s[n-1]);
}

/* Map a URI to a single character namespace identifier */
static XML_Char _FindNamespaceID(
    XML* self,
    const XML_Char* uri,
    size_t uriSize)
{
    size_t i;
    unsigned int code = _HashCode(uri, uriSize);

    /* Resolve from client namespace registrations */
    for (i = 0; i < self->registeredNameSpacesSize; i++)
    {
        XML_RegisteredNameSpace* rns = &self->registeredNameSpaces[i];

        if (rns->uriCode == code && XML_strcmp(rns->uri, uri) == 0)
            return rns->id;
    }

    /* Not found so return null id */
    return '\0';
}

/* Translate the namespace name used in the document to a single-character
 * namespace name specified by the client in the XML_RegisterNameSpace() call.
 * For example: "wsman:OptimizeEnumeration" => "w:OptimizeEnumeration".
 */
static XML_Char* _TranslateName(XML* self, _In_z_ XML_Char* name, _Out_ XML_Char* colon)
{
    unsigned int code;
    size_t i;

    /* Temporarily zero-out the ':' character */
    *colon = '\0';

    /* Calculate hash code */
    code = _HashCode(name, colon - name);

    /* First check single entry cache */
    if (self->nameSpacesCacheIndex != (size_t)-1)
    {
        XML_NameSpace* ns;
        _Analysis_assume_(self->nameSpacesCacheIndex < XML_MAX_NAMESPACES);
        ns = &self->nameSpaces[self->nameSpacesCacheIndex];

        if (ns->nameCode == code && XML_strcmp(ns->name, name) == 0)
        {
            if (ns->id)
            {
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001)
#endif
                /* disabling IPv6 OACR warnings - D3M bug 56 */
                colon[-1] = ns->id;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
                *colon = ':';
                return colon - 1;
            }
            else
            {
                *colon = ':';
                return name;
            }
        }
    }

    /* Translate name to the one found in the nameSpaces[] array */
    for (i = self->nameSpacesSize; i--; )
    {
        XML_NameSpace* ns = &self->nameSpaces[i];

        if (ns && ns->nameCode == code && XML_strcmp(ns->name, name) == 0)
        {
            /* Cache */
            self->nameSpacesCacheIndex = i;

            if (ns->id)
            {
                colon[-1] = ns->id;
                *colon = ':';
                return colon - 1;
            }
            else
            {
                *colon = ':';
                return name;
            }
        }
    }

    /* Restore the ':' character */
    *colon = ':';
    return name;
}

static void _ParseAttr(
    XML* self,
    XML_Elem* elem,
    _Inout_ XMLCharPtr* pInOut)
{
    _Null_terminated_ XML_Char* p = *pInOut;
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* value;
    XML_Char* valueEnd;
    XML_Char* colon = NULL;

    if (!p)
        return;

    /* Parse the attribute name */
    {
        name = p;

        if (!*p || !_IsFirst(*p))
        {
            XML_Raise(self, T("expected attribute name"));
            return;
        }

        p++;

        if (*p)
            p = _SkipInner(p);

        if (*p == ':')
        {
            colon = p++;
            p = _SkipInner(p);
        }

        nameEnd = p;
    }

    /* Seek the quote character (position p beyond quote) */
    {
        /* Skip spaces */
        p = _SkipSpaces(self, p);

        /* Expect a '=' character */
        if (*p++ != '=')
        {
            XML_Raise(self, T("expected '=' character"));
            return;
        }
    }

    /* Null-terminate name now that we are beyond the '=' */
    *nameEnd = '\0';

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Parse the value */
    {
        XML_Char quote;

        /* Expect opening quote */
        if (*p != '"' && *p != '\'')
        {
            XML_Raise(self, T("expected opening quote"));
            return;
        }

        quote = *p++;
        value = p;

        valueEnd = _ReduceAttrValue(self, &p, quote);

        if (self->status)
        {
            /* Propagate error */
            return;
        }

        /* Expect closing quote */
        if (*p++ != quote)
        {
            XML_Raise(self, T("expected closing quote"));
            return;
        }

        /* Null-terminate the value */
        *valueEnd = '\0';
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* If attribute name is "xmlns", extract namespace */
    if (name[0] == 'x' &&
        name[1] == 'm' &&
        name[2] == 'l' &&
        name[3] == 'n' &&
        name[4] == 's')
    {
        /* ATTN: implement default namespaces */
        if (name[5] != ':')
        {
            XML_Raise(self, T("default namespaces not supported: xmlns"));
            return;
        }

        /* Add new namespace entry */
        {
            /* Check for stack overflow */
            if (self->nameSpacesSize == XML_MAX_NAMESPACES)
            {
                XML_Raise(self, T("too many namespaces (>%u)"),
                    (int)XML_MAX_NAMESPACES);
                return;
            }
            {
                XML_NameSpace* ns = &self->nameSpaces[self->nameSpacesSize++];
                ns->name = &name[6];
                ns->nameCode = _HashCode(ns->name, nameEnd - ns->name);
                ns->id = _FindNamespaceID(self, value, valueEnd - value);
                ns->uri = value;
                ns->depth = self->stackSize;
            }
        }
    }
    else
    {
        /* Translate the name (possibly replacing namespace with single char) */
        if (colon)
            name = _TranslateName(self, name, colon);
    }

    /* Append attribute to element */
    {
        XML_Attr* attr;

        /* Check for attribute array overflow */
        if (elem->attrsSize == XML_MAX_ATTRIBUTES)
        {
            XML_Raise(self, T("too many attributes (>%u)"), XML_MAX_ATTRIBUTES);
            return;
        }

        attr = &elem->attrs[elem->attrsSize++];
        attr->name = name;
        attr->value = value;
    }

    *pInOut = p;
}

static void _ParseProcessingInstruction(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    /* <?xml version="1.0" encoding="UTF-8" standalone="yes"?> */
    XML_Char* start;
    XML_Char* end;

    if (!*p)
    {
        XML_Raise(self, T("premature end of input"));
        return;
    }

    /* Advance past '?' character */
    p++;

    /* Get tag identifier */
    {
        start = p;

        p = _SkipInner(p);

        if (*p == ':')
        {
            p++;
            p = _SkipInner(p);
        }

        /* If input exhuasted */
        if (*p == '\0')
        {
            XML_Raise(self, T("premature end of input"));
            return;
        }

        end = p;
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Process attributes */

    while (*p && *p != '?')
    {
        _ParseAttr(self, elem, &p);

        if (self->status)
        {
            /* Propagate error */
            return;
        }
    }

    p++;

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Expect '>' */
    if (*p++ != '>')
    {
        XML_Raise(self, T("expected closing angle bracket"));
        return;
    }

    /* Return element object */
    elem->type = XML_INSTRUCTION;
    elem->data = start;
    elem->size = end - start;
    *end = '\0';

    self->ptr = p;

    if (self->foundRoot)
        self->state = STATE_CHARS;
    else
        self->state = STATE_START;
}

static void _ParseStartTag(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* colon = NULL;

    /* Found the root */
    self->foundRoot = 1;

    /* Get tag identifier */
    {
        name = p;

        if (!*p)
        {
            XML_Raise(self, T("premature end of input"));
            return;
        }

        if (!_IsFirst(*p++))
        {
            XML_Raise(self, T("expected element name"));
            return;
        }

        p = _SkipInner(p);

        if (*p == ':')
        {
            colon = p++;
            p = _SkipInner(p);
        }

        /* If input exhuasted */
        if (*p == '\0')
        {
            XML_Raise(self, T("premature end of input"));
            return;
        }

        nameEnd = p;
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Process attributes */
    while (*p && *p != '/' && *p != '>')
    {
        _ParseAttr(self, elem, &p);

        if (self->status)
            return;
    }

    /* Check for empty tag */
    if (*p == '/')
    {
        p++;

        /* Null-terminate the tag */
        *nameEnd = '\0';

        /* Translate tag name (possibly replacing namespace with single char */
        if (colon)
            name = _TranslateName(self, name, colon);

        /* Create the element */
        elem->type = XML_START;
        elem->data = name;
        elem->size = nameEnd - name;

        /* Inject an empty tag onto element stack */
        {
            /* Check for stack overflow */
            if (self->elemStackSize == XML_MAX_NESTED)
            {
                XML_Raise(self, T("element stack overflow (>%u)"),
                    XML_MAX_NESTED);
                return;
            }

            self->elemStack[self->elemStackSize] = *elem;
            self->elemStack[self->elemStackSize].type = XML_END;
            self->elemStackSize++;
            self->nesting++;
        }

        /* Skip space */
        p = _SkipSpaces(self, p);

        /* Expect '>' */
        if (*p++ != '>')
        {
            XML_Raise(self, T("expected closing angle bracket"));
            return;
        }

        self->ptr = p;
        self->state = STATE_CHARS;
        return;
    }

    /* Expect '>' */
    if (*p++ != '>')
    {
        XML_Raise(self, T("expected closing angle bracket"));
        return;
    }

    /* Zero-terminate the name tag */
    *nameEnd = '\0';

    /* Translate the namespace prefix */
    if (colon)
        name = _TranslateName(self, name, colon);

    /* Push opening tag */
    {
        if (self->stackSize == XML_MAX_NESTED)
        {
            XML_Raise(self, T("element stack overflow (>%u)"), XML_MAX_NESTED);
            return;
        }

        self->stack[self->stackSize].data = name;
        self->stack[self->stackSize].size = nameEnd - name;
        self->stackSize++;
        self->nesting++;
    }

    /* Return element object */
    elem->type = XML_START;
    elem->data = name;
    elem->size = nameEnd - name;

    self->ptr = p;

    if (self->foundRoot)
        self->state = STATE_CHARS;
    else
        self->state = STATE_START;
}

static void _ParseEndTag(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    /* Closing element: </name> */
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* colon = NULL;

    if (!*p)
    {
        XML_Raise(self, T("premature end of input"));
        return;
    }

    p++;

    /* Skip space */
    p = _SkipSpaces(self, p);

    name = p;

    /* Skip name */
    {
        if (!_IsFirst(*p++))
        {
            XML_Raise(self, T("expected element name"));
            return;
        }

        p = _SkipInner(p);

        if (*p == ':')
        {
            colon = p++;
            p = _SkipInner(p);
        }
    }

    /* If input exhuasted */
    if (*p == '\0')
    {
        XML_Raise(self, T("premature end of input"));
        return;
    }

    nameEnd = p;

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Expect '>' */
    if (*p++ != '>')
    {
        XML_Raise(self, T("expected closing angle bracket"));
        return;
    }

    /* Null terminate name */
    *nameEnd = '\0';

    /* Tranlate the namespace part of the name */
    if (colon)
        name = _TranslateName(self, name, colon);

    /* Return element object */
    elem->type = XML_END;
    elem->data = name;
    elem->size = nameEnd - name;

    /* Match opening name */
    {
        /* Check for stack underflow */
        if (self->stackSize-- == 0)
        {
            XML_Raise(self, T("too many closing tags: %Z"), zcs(name));
            return;
        }

        self->nesting--;

        /* Check that closing name matches opening name */
        {
            XML_Name* xn = &self->stack[self->stackSize];

            if (memcmp(xn->data, name, xn->size * sizeof(XML_Char)) != 0)
            {
                XML_Raise(self, T("open/close tag mismatch: %Z/%Z"),
                    zcs(self->stack[self->stackSize].data), zcs(name));
                return;
            }
        }
    }

    /* Remove namespaces that have just gone out of scope */
    {
        size_t i;
        size_t n = 0;

        for (i = self->nameSpacesSize; i--; )
        {
            if (self->nameSpaces[i].depth >= self->stackSize)
                n++;
        }

        if (n)
        {
            self->nameSpacesSize -= n;

            /* Clear single-entry cache */
            if (self->nameSpacesCacheIndex >= self->nameSpacesSize)
                self->nameSpacesCacheIndex = (size_t)-1;
        }
    }

    /* Set next state */
    self->ptr = p;
    self->state = STATE_CHARS;
}

static void _ParseComment(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    /* Comment: <!-- blah blah blah --> */
    XML_Char* start;
    XML_Char* end;

    p = _SkipChars(p, 2);
    if (!*p)
    {
        XML_Raise(self, T("premature end of input"));
        return;
    }
    start = p;

    while (*p)
    {
        if (p[0] == '-' && p[1] == '-')
        {
            if (p[2] != '>')
            {
                XML_Raise(self, T("expected closing comment"));
                return;
            }

            /* Null-terminate this comment */
            end = p;
            p += 3;

            /* Prepare element */
            elem->type = XML_COMMENT;
            elem->data = start;
            elem->size = end - start;
            *end = '\0';

            /* Set next state */
            self->ptr = p;

            if (self->foundRoot)
                self->state = STATE_CHARS;
            else
                self->state = STATE_START;

            return;
        }
        else if (p[0] == '\n')
            self->line++;

        p++;
    }

    XML_Raise(self, T("malformed comment"));
}

static void _ParseCDATA(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    /* <![CDATA[...]]> */
    XML_Char* start;
    XML_Char* end;

    p = _SkipChars(p, 7);
    if (!*p)
    {
        XML_Raise(self, T("premature end of input"));
        return;
    }
    start = p;

    while (*p)
    {
        if (p[0] == ']' && p[1] == ']' && p[2] == '>')
        {
            end = p;
            p += 3;

            /* Prepare element */
            elem->type = XML_CHARS;
            elem->data = start;
            elem->size = end - start;
            *end = '\0';

            /* Set next state */
            self->ptr = p;
            self->state = STATE_CHARS;

            return;

        }
        else if (p[0] == '\n')
            self->line++;

        p++;
    }

    XML_Raise(self, T("unterminated CDATA section"));
    return;
}

static void _ParseDOCTYPE(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    MI_UNUSED(elem);

    /* Recognize <!DOCTYPE ...> */
    p = _SkipChars(p, 7);
    if (!*p)
    {
        XML_Raise(self, T("expected DOCTYPE element"));
        return;
    }

    while (*p && *p != '>')
    {
        if (p[0] == '\n')
            self->line++;

        p++;
    }

    if (*p++ != '>')
    {
        XML_Raise(self, T("unterminated DOCTYPE element"));
        return;
    }

    /* Set next state */
    self->ptr = p;

    if (self->foundRoot)
        self->state = STATE_CHARS;
    else
        self->state = STATE_START;
}

static int _ParseCharData(
    XML* self,
    XML_Elem* elem,
    _In_z_ XML_Char* p)
{
    XML_Char* start;
    XML_Char* end;

    /* Skip leading spaces */
    p = _SkipSpaces(self, p);

    /* Reject input if it does appear inside tags */
    if (self->stackSize == 0)
    {
        if (*p == '\0')
        {
            /* Proper end of input so set status to zero */
            self->status = 1;
            return 0;
        }

        XML_Raise(self, T("markup outside root element"));
        return 0;
    }

    /* Remove leading spaces */
    p = _SkipSpaces(self, p);

    if (*p == '<')
    {
        self->ptr = p + 1;
        self->state = STATE_TAG;
        return 0;
    }

    /* Save pointer to start of data */
    start = p;

    /* reduce character data */
    end = _ReduceCharData(self, &p);

    if (self->status)
    {
        /* Propagate error */
        return 0;
    }

    /* Process character data */
    if (*p != '<')
    {
        XML_Raise(self, T("expected opening angle bracket"));
        return 0;
    }

    /* Remove trailing spaces (the newlines have already been counted) */
    {
        /* Remove trainling spaces from the character data */
        start[-1] = '\0';

        while (_IsSpace(end[-1]))
            end--;
    }

    /* Set next state */
    self->ptr = p + 1;
    self->state = STATE_TAG;

    /* Return character data element if non-empty */
    if (end == start)
        return 0;

    /* Prepare element */
    *end = '\0';
    elem->type = XML_CHARS;
    elem->data = start;
    elem->size = end - start;

    /* Return 1 to indicate non-empty element */
    return 1;
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

const XML_Char* XML_Elem_GetAttr(
    XML_Elem* self,
    const XML_Char* name)
{
    size_t i;

    for (i = 0; i < self->attrsSize; i++)
    {
        if (XML_strcmp(name, self->attrs[i].name) == 0)
            return self->attrs[i].value;
    }

    /* Not found! */
    return NULL;
}

void XML_Init(
    XML* self)
{
    memset(self, 0, sizeof(XML));
    self->nameSpacesCacheIndex = (size_t)-1;
}

_Use_decl_annotations_
void XML_SetText(
    XML* self,
    XML_Char* text)
{
    self->text = text;
    self->ptr = text;
    self->line = 1;
    self->state = STATE_START;
}

int XML_Next(
    XML* self,
    XML_Elem* elem)
{
    if (self->elemStackSize)
    {
        *elem = self->elemStack[--self->elemStackSize];
        self->nesting--;
        return 0;
    }

    elem->attrsSize = 0;

    for (;;)
    {
        switch (self->state)
        {
            case STATE_START:
            {
                XML_Char* p = self->ptr;

                /* Skip spaces */
                p = _SkipSpaces(self, p);

                /* Expect '<' */
                if (*p != '<')
                {
                    XML_Raise(self, T("expected opening angle bracket"));
                    return -1;
                }

                self->ptr = p + 1;
                self->state = STATE_TAG;
                break;
            }
            case STATE_TAG:
            {
                XML_Char* p = self->ptr;

                /* Skip spaces */
                p = _SkipSpaces(self, p);

                /* Expect one of these */
                if (*p == '/')
                {
                    _ParseEndTag(self, elem, p);
                    return self->status;
                }
                else if (_IsFirst(*p))
                {
                    _ParseStartTag(self, elem, p);
                    return self->status;
                }
                else if (*p == '?')
                {
                    _ParseProcessingInstruction(self, elem, p);
                    return self->status;
                }
                else if (*p == '!')
                {
                    p++;

                    if (p[0] == '-' && p[1] == '-')
                    {
                        _ParseComment(self, elem, p);
                        return self->status;
                    }
                    else if (
                        memcmp(p, T("[CDATA["), 7 * sizeof(XML_Char)) == 0)
                    {
                        _ParseCDATA(self, elem, p);
                        return self->status;
                    }
                    else if (
                        memcmp(p, T("DOCTYPE"), 7 * sizeof(XML_Char)) == 0)
                    {
                        _ParseDOCTYPE(self, elem, p);

                        if (self->status)
                            return -1;

                        break;
                    }
                    else
                    {
                        XML_Raise(
                            self,
                            T("expected comment, CDATA, or DOCTYPE"));
                        return -1;
                    }
                }
                else
                {
                    XML_Raise(self, T("expected element"));
                    return-1;
                }
                break;
            }
            case STATE_CHARS:
            {
                XML_Char* p = self->ptr;

                if (_ParseCharData(self, elem, p) == 1)
                {
                    /* Return character data to caller */
                    return 0;
                }

                if (self->status)
                    return self->status;

                /* empty character data */
                break;
            }
            default:
            {
                XML_Raise(self, T("unexpected state"));
                return -1;
            }
        }
    }

    //return 0;
}

int XML_Expect(
    XML* self,
    XML_Elem* elem,
    XML_Type type,
    const XML_Char* name)
{
    if (XML_Next(self, elem) == 0 &&
        elem->type == type &&
        (!name || XML_strcmp(elem->data, name) == 0))
    {
        return 0;
    }

#if 0
    XML_Elem_Dump(elem);
#endif

    if (type == XML_START)
    {
        XML_Raise(self, T("expected element: <%Z>: %Z"),
            zcs(name), zcs(elem->data));
    }
    else if (type == XML_END)
    {
        XML_Raise(self, T("expected element: <%Z>: %Z"),
            zcs(name), zcs(elem->data));
    }
    else if (type == XML_CHARS)
    {
        XML_Raise(self, T("expected character data"));
    }

    return -1;
}

int XML_Skip(
    XML* self)
{
    XML_Elem tmp;
    size_t nesting = self->nesting;

    while (self->nesting >= nesting)
    {
        if (XML_Next(self, &tmp) != 0)
            return -1;
    }

    return 0;
}

int XML_RegisterNameSpace(
    XML* self,
    XML_Char id,
    const XML_Char* uri)
{
    XML_RegisteredNameSpace rns;
    /* ATTN: we do not check for duplicates */

    /* Reject out of range ids */
    if (id < 'a' || id > 'z')
        return -1;

    /* Check for overflow of the array */
    if (self->registeredNameSpacesSize == XML_MAX_REGISTERED_NAMESPACES)
        return -1;

    /* Reject zero-length URI's */
    if (uri[0] == '\0')
        return -1;

    rns.id = id;
    rns.uri = uri;
    rns.uriCode = _HashCode(uri, XML_strlen(uri));

    self->registeredNameSpaces[self->registeredNameSpacesSize++] = rns;

    return 0;
}

int XML_PutBack(
    XML* self,
    const XML_Elem* elem)
{
    /* Check for stack overflow */
    if (self->elemStackSize == XML_MAX_NESTED)
    {
        XML_Raise(self, T("element stack overflow (>%u)"), XML_MAX_NESTED);
        return -1;
    }

    self->elemStack[self->elemStackSize++] = *elem;
    return 0;
}

void XML_Raise(XML* self, const XML_Char* format, ...)
{
    va_list ap;

    self->status = -1;
    self->message[0] = '\0';

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    Vszprintf(self->message, MI_COUNT(self->message), format, ap);
    va_end(ap);
}

_Use_decl_annotations_
void XML_FormatError(XML* self, XML_Char* buffer, size_t size)
{
    *buffer = '\0';

    if (self->status == -1)
    {
        Szprintf(
            buffer,
            size,
            T("%u: error: %Z"),
            (unsigned int)self->line,
            zcs(self->message));
    }
}
