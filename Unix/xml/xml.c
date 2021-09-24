/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#include <pal/format.h>
# define T(STR) STR
# define T(STR) STR
# define XML_strtoul strtoul
# define XML_strcmp strcmp
# define XML_strlen strlen

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
static const unsigned char _spaceChar[256] =
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
    int i = (int) c;
    if (i >= 0 && i< 256)
        return _spaceChar[i];
    return 0;
}

INLINE int _AllSpace(_In_z_ XML_Char *p, size_t count)
{
    size_t i;
    for (i = 0; i < count; ++i)
    {
        if (!_IsSpace(*p++))
            return 0;
    }
    return 1;
}

/* Matches XML name characters of the form: [A-Za-z_][A-Za-z0-9_-.:]*
 *     _nameChar[A-Za-z_] => 2 (first character)
 *     _nameChar[A-Za-z0-9_-.:] => 1 or 2 (inner character)
 */
static const unsigned char _nameChar[256] =
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
    int i = (int) c;
    if (i >= 0 && i< 256)
        return _nameChar[i] & 2;
    return 0;
}

INLINE int _IsInner(XML_Char c)
{
    int i = (int) c;
    if (i >= 0 && i< 256)
        return _nameChar[i];
    return 0;
}

INLINE XML_Char* _SkipInner(_In_z_ XML_Char* p)
{
    while (*p && _IsInner(*p))
        p++;

    return p;
}

static XML_Char* _SkipSpacesAux(_Inout_ XML* self, _In_z_ XML_Char* p)
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

INLINE XML_Char* _SkipSpaces(_Inout_ XML* self, _In_z_ XML_Char* p)
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

INLINE XML_Char* _ToEntityRef(_Inout_ XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
{
    /* Note: we collected the following statistics on the frequency of
     * each entity reference in a large body of XML documents:
     *     
     *     &quot; - 74,480 occurrences
     *     &apos; - 13,877 occurrences
     *     &lt;   -  9,919 occurrences
     *     &gt;   -  9,853 occurrences
     *     &amp;  -    111 occurrences
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
    XML_Raise(self, XML_ERROR_BAD_ENTITY_REFERENCE);
    return p;
}

INLINE XML_Char* _ToCharRef(_Inout_ XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
{
    XML_Char* end = NULL;
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
        XML_Raise(self, XML_ERROR_BAD_CHARACTER_REFERENCE);
        return p;
    }

    *ch = (XML_Char)x;

    return end + 1;
}

INLINE XML_Char* _ToRef(_Inout_ XML* self, _In_z_ XML_Char* p, _Out_ XML_Char* ch)
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

/* Matches all but '\0', '\'', '"', and '&'. All matching characters
 * yeild 2, except for '\n', which yields 1 
 */
static const unsigned char _ReduceAttrValueMatchChars[256] =
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
    int i = (int) c;
    if (i >= 0 && i< 256)
        return _ReduceAttrValueMatchChars[i];
    return 0;
}

/* Reduce entity references and remove leading and trailing whitespace */
static XML_Char* _ReduceAttrValue(_Inout_ XML* self, _Inout_ XMLCharPtr* pInOut, XML_Char eos)
{
    _Null_terminated_ XML_Char* p = *pInOut;
    _Null_terminated_ XML_Char* end;
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
            _Null_terminated_ XML_Char* tmp;
            
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
static const unsigned char _ReduceCharDataMatchChars[256] =
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
    int i = (int) c;
    if (i >= 0 && i< 256)
        return _ReduceCharDataMatchChars[i];
    return 1;
}

/* Reduce character data, advance p, and return pointer to end */
static XML_Char* _ReduceCharData(_Inout_ XML* self, _Inout_ XMLCharPtr* pInOut)
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
    /* OACR does not like loops inside loops that modify buffer pointers, the logic however is correct */
#endif
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

/* Calculate a fast hash code for a strings */
INLINE unsigned int _HashCode(_In_reads_z_(n) const XML_Char* s, size_t n)
{
    /* This hash algorithm excludes the first character since for many strings 
     * (e.g., URIs) the first character is not unique. Instead the hash 
     * comprises three components:
     *     (1) The length
     *     (3) The last character
     */
    return n ? (int)(n ^ s[n-1]) : 0;
}

/* Map a URI to a single character namespace identifier */
static XML_Char _FindNamespaceID(
    _Inout_ XML* self, 
    _In_reads_z_(uriSize) const XML_Char* uri,
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

#define XML_NS "http://www.w3.org/XML/1998/namespace"
#define T_XML_NS T("http://www.w3.org/XML/1998/namespace")
#define XML_NS_LEN (sizeof(XML_NS) - 1)

#define XMLNS_NS "http://www.w3.org/2000/xmlns/"
#define T_XMLNS_NS T("http://www.w3.org/2000/xmlns/")
#define XMLNS_NS_LEN (sizeof(XMLNS_NS) - 1)

/* Map a prefix to its XML namespace
 * A non-empty prefix that is unmapped results in an error */
static const XML_NameSpace* _FindNamespace(_Inout_ XML* self, _In_z_ const XML_Char* prefix)
{
    static const XML_NameSpace s_empty = {T(""), 0, T(""), 0, '\0', 0};
    static const XML_NameSpace s_xml = {T("xml"), 3 ^ 'l', T_XML_NS, XML_NS_LEN, '\0', 0};
    static const XML_NameSpace s_xmlns = {T("xmlns"), 5 ^ 's', T_XMLNS_NS, XMLNS_NS_LEN, '\0', 0};
    unsigned int code = _HashCode(prefix, XML_strlen(prefix));
    size_t i;

    /* Special case: the 'xml' and 'xmlns' namespaces are fixed. */
    if (prefix[0] == 'x' &&
        prefix[1] == 'm' &&
        prefix[2] == 'l')
    {
        if (prefix[3] == '\0')
            return &s_xml;
        else if (prefix[3] == 'n' &&
                 prefix[4] == 's' &&
                 prefix[5] == '\0')
            return &s_xmlns;
    }

    /* First check single entry cache */
    if (self->nameSpacesCacheIndex != (size_t)-1)
    {
        XML_NameSpace* ns;
        _Analysis_assume_(self->nameSpacesCacheIndex < XML_MAX_NAMESPACES);
        ns = &self->nameSpaces[self->nameSpacesCacheIndex];

        if (ns->nameCode == code && XML_strcmp(ns->name, prefix) == 0)
        {
            return ns;
        }
    }

    /* Translate name to the one found in the nameSpaces[] array */
    for (i = self->nameSpacesSize; i--; )
    {
        const XML_NameSpace* ns = &self->nameSpaces[i];

        if (ns && ns->nameCode == code && XML_strcmp(ns->name, prefix) == 0)
        {
            /* Cache */
            self->nameSpacesCacheIndex = i;

            return ns;
        }
    }

    /* No match
     * For the empty prefix this means there is no namespace
     * Otherwise, this is an error */
    if (prefix[0])
    {
        XML_Raise(self, XML_ERROR_UNDEFINED_NAMESPACE_PREFIX, tcs(prefix));
        return NULL;
    }

    return &s_empty;
}

static void _ParseAttr(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _Inout_ XMLCharPtr* pInOut)
{
    _Null_terminated_ XML_Char* p = *pInOut;
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* value;
    XML_Char* valueEnd;
    XML_Char* colon = NULL;
    XML_Char* tag = p;
    XML_Char* prefix = T("");

    if (!p)
    {
        XML_Raise(self, XML_ERROR_EXPECTED_ATTRIBUTE_NAME);
        return;
    }

    /* Parse the attribute name */
    {
        name = p;

        if (!*p || !_IsFirst(*p))
        {
            XML_Raise(self, XML_ERROR_EXPECTED_ATTRIBUTE_NAME);
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
            *nameEnd = '\0';
            XML_Raise(self, XML_ERROR_EXPECTED_ATTRIBUTE_EQUALS, tcs(name));
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
            XML_Raise(self, XML_ERROR_EXPECTED_ATTRIBUTE_OPENING_QUOTES, tcs(name));
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
            XML_Raise(self, XML_ERROR_EXPECTED_ATTRIBUTE_CLOSING_QUOTES, tcs(name));
            return;
        }

        /* Null-terminate the value */
        *valueEnd = '\0';
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Separate the prefix and tag */
    if (colon)
    {
        *colon = '\0';
        tag = colon + 1;
        prefix = name;
    }
    /* else prefix is "" and name is the tag */

    /* If the first/only token is "xmlns", extract namespace */
    if (name[0] == 'x' &&
        name[1] == 'm' &&
        name[2] == 'l' &&
        name[3] == 'n' &&
        name[4] == 's' &&
        name[5] == '\0')
    {
        unsigned int tagCode = 0;

        /* The namespace of the xmlns:x attribute is fixed */
        prefix = T("xmlns");

        if (colon)
        {
            /* For non-default namespaces */
            tagCode = _HashCode(tag, nameEnd - tag);
        }

        /* Add new namespace entry */
        {
            /* Check for stack overflow */
            if (self->nameSpacesSize == XML_MAX_NAMESPACES)
            {
                XML_Raise(self, XML_ERROR_TOO_MANY_NAMESPACES,
                    (int)XML_MAX_NAMESPACES);
                return;
            }
            {
                XML_NameSpace* newNs = &self->nameSpaces[self->nameSpacesSize++];
                newNs->name = colon ? tag : T("");
                newNs->nameCode = tagCode;
                newNs->id = _FindNamespaceID(self, value, valueEnd - value);
                newNs->uri = value;
                newNs->uriSize = valueEnd - value;
                newNs->depth = self->stackSize;
            }
        }
    }

    /* Append attribute to element */
    {
        XML_Attr* attr;

        /* Check for attribute array overflow */
        if (elem->attrsSize == XML_MAX_ATTRIBUTES)
        {
            elem->data.data[elem->data.size] = 0;   //May not have been null terminated yet
            XML_Raise(self, XML_ERROR_TOO_MANY_ATTRIBUTES, tcs(elem->data.data), (int)XML_MAX_ATTRIBUTES);
            return;
        }

        attr = &elem->attrs[elem->attrsSize++];
        attr->name.data = tag;
        attr->name.size = nameEnd - tag;
        attr->value = value;
        attr->valueSize = valueEnd - value;

        /* Save the namespace prefix, which will be translated by the caller */
        attr->name.namespaceUri = prefix;
    }

    *pInOut = p;
}

static void _ParseProcessingInstruction(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    /* <?xml version="1.0" encoding="UTF-8" standalone="yes"?> */
    XML_Char* start;
    XML_Char* end;

    /* Advance past '?' character */
    if (*p)
    {
        p++;
    }

    /* Get tag identifier */
    {
        start = p;

        if (*p)
        {
            p = _SkipInner(p);
        }

        if (*p == ':')
        {
            p++;
            if (*p)
            {
                p = _SkipInner(p);
            }
        }

        /* If input exhausted */
        if (*p == '\0')
        {
            XML_Raise(self, XML_ERROR_END_OF_XML_INSTRUCTION);
            return;
        }

        end = p;
    }

    /* Skip spaces */
    if (*p)
    {
        p = _SkipSpaces(self, p);
    }

    elem->type = XML_INSTRUCTION;
    elem->data.data = start;
    elem->data.size = end - start;

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

    if (*p)
    {
        p++;
    }

    /* Skip spaces */
    if (*p)
    {
        p = _SkipSpaces(self, p);
    }

    /* Expect '>' */
    if (*p++ != '>')
    {
        XML_Raise(self, XML_ERROR_END_OF_INSTRUCTION_MISSING);
        return;
    }

    /* Return element object */
    elem->data.namespaceUri = T("");
    elem->data.namespaceUriSize = 0;
    elem->data.namespaceId = '\0';
    *end = '\0';

    self->ptr = p;

    if (self->foundRoot)
        self->state = STATE_CHARS;
    else
        self->state = STATE_START;
}

static void _ParseStartTag(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* colon = NULL;
    XML_Char* prefix = T("");
    const XML_NameSpace* ns;
    size_t attr;

    /* Found the root */
    self->foundRoot = 1;

    /* Get tag identifier */
    {
        name = p;

        if (!*p || !_IsFirst(*p++))
        {
            XML_Raise(self, XML_ERROR_ELEMENT_NAME_EXPECTED);
            return;
        }

        if (*p)
        {
            p = _SkipInner(p);
        }

        if (*p == ':')
        {
            colon = p++;
            if (*p)
            {
                p = _SkipInner(p);
            }
        }

        /* If input exhausted */
        if (*p == '\0')
        {
            XML_Raise(self, XML_ERROR_ELEMENT_NAME_PREMATURE_END);
            return;
        }

        nameEnd = p;
    }

    if (colon)
    {
        *colon = '\0';
        prefix = name;
        name = colon + 1;
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    elem->type = XML_START;
    elem->data.data = name;
    elem->data.size = nameEnd - name;

    /* Process attributes */
    while (*p && *p != '/' && *p != '>')
    {
        _ParseAttr(self, elem, &p);

        if (self->status)
            return;
    }

    /* Translate the namespace after parsing xmlns attributes */
    ns = _FindNamespace(self, prefix);

    if (self->status)
        return;

    /* Now translate the attribute namespaces */
    /* Unprefixed attributes get a empty namespace */
    for (attr = 0; attr < elem->attrsSize; attr++)
    {
        static const XML_NameSpace s_empty = {T(""), 0, T(""), 0, '\0', 0};
        XML_Attr* item = elem->attrs + attr;
        const XML_NameSpace* itemNS = &s_empty;

        if (item->name.namespaceUri[0] != '\0')
        {
            /* The namespaceUri field contains the prefix */
            itemNS = _FindNamespace(self, item->name.namespaceUri);

            if (self->status)
                return;
        }

        item->name.namespaceUri = itemNS->uri;
        item->name.namespaceUriSize = itemNS->uriSize;
        item->name.namespaceId = itemNS->id;
    }

    /* Create the element */
    elem->type = XML_START;
    elem->data.data = name;
    elem->data.size = nameEnd - name;
    elem->data.namespaceUri = ns->uri;
    elem->data.namespaceUriSize = ns->uriSize;
    elem->data.namespaceId = ns->id;

    /* Check for empty tag */
    if (*p == '/')
    {
        p++;

        /* Null-terminate the tag */
        *nameEnd = '\0';

        /* Inject an empty tag onto element stack */
        {
            /* Check for stack overflow */
            if (self->elemStackSize == XML_MAX_NESTED)
            {
                XML_Raise(self, XML_ERROR_ELEMENT_DEPTH_OVERFLOW, 
                    (int)XML_MAX_NESTED);
                return;
            }

            self->elemStack[self->elemStackSize] = *elem;
            self->elemStack[self->elemStackSize].type = XML_END;
            self->elemStackSize++;
            self->nesting++;
        }

        /* Skip space */
        if (*p)
        {
            p = _SkipSpaces(self, p);
        }

        /* Expect '>' */
        if (*p++ != '>')
        {
            *nameEnd = '\0';
            XML_Raise(self, XML_ERROR_ELEMENT_NAME_NOT_CLOSED, tcs(elem->data.data));
            return;
        }

        self->ptr = p;
        self->state = STATE_CHARS;
        return;
    }

    /* Expect '>' */
    if (*p++ != '>')
    {
        *nameEnd = '\0';
        XML_Raise(self, XML_ERROR_ELEMENT_NAME_NOT_CLOSED, tcs(elem->data.data));
        return;
    }

    /* Zero-terminate the name tag */
    *nameEnd = '\0';

    /* Push opening tag */
    {
        if (self->stackSize == XML_MAX_NESTED)
        {
            XML_Raise(self, XML_ERROR_ELEMENT_DEPTH_OVERFLOW, 
                (int)XML_MAX_NESTED);
            return;
        }

        self->stack[self->stackSize] = elem->data;
        self->stackSize++;
        self->nesting++;
    }

    self->ptr = p;

    if (self->foundRoot)
        self->state = STATE_CHARS;
    else
        self->state = STATE_START;
}

static void _ParseEndTag(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    /* Closing element: </name> */
    XML_Char* name;
    XML_Char* nameEnd;
    XML_Char* colon = NULL;
    XML_Char* prefix = T("");
    const XML_NameSpace *ns;

    if (*p)
    {
        p++;
    }

    /* Skip space */
    if (*p)
    {
        p = _SkipSpaces(self, p);
    }

    name = p;

    /* Skip name */
    {
        if (!*p || !_IsFirst(*p++))
        {
            XML_Raise(self, XML_ERROR_ELEMENT_NAME_EXPECTED_ELEM_END);
            return;
        }

        if (*p)
        {
            p = _SkipInner(p);
        }

        if (*p == ':')
        {
            colon = p++;
            if (*p)
            {
                p = _SkipInner(p);
            }
        }
    }

    /* If input exhausted */
    if (*p == '\0')
    {
        XML_Raise(self, XML_ERROR_ELEMENT_NAME_PREMATURE_END_ELEM_END);
        return;
    }

    nameEnd = p;

    if (colon)
    {
        *colon = '\0';
        prefix = name;
        name = colon + 1;
    }

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Expect '>' */
    if (*p++ != '>')
    {
        XML_Raise(self,XML_ERROR_ELEMENT_NAME_NOT_CLOSED_ELEM_END, tcs(name));
        return;
    }

    /* Null terminate name */
    *nameEnd = '\0';

    ns = _FindNamespace(self, prefix);

    if (self->status)
        return;

    /* Return element object */
    elem->type = XML_END;
    elem->data.data = name;
    elem->data.size = nameEnd - name;
    elem->data.namespaceUri = ns->uri;
    elem->data.namespaceUriSize = ns->uriSize;
    elem->data.namespaceId = ns->id;

    /* Match opening name */
    {
        /* Check for stack underflow */
        if (self->stackSize-- == 0)
        {
            XML_Raise(self, XML_ERROR_ELEMENT_TOO_MANY_ENDS, tcs(name));
            return;
        }

        self->nesting--;

        /* Check that closing name matches opening name */
        {
            XML_Name* xn = &self->stack[self->stackSize];

            if (XML_strcmp(xn->data, name) != 0 ||
                xn->namespaceId != ns->id ||
                (ns->id == 0 && XML_strcmp(xn->namespaceUri, ns->uri) != 0))
            {
                XML_Raise(self, XML_ERROR_ELEMENT_END_ELEMENT_TAG_NOT_MATCH_START_TAG, 
                    tcs(self->stack[self->stackSize].data), tcs(name));
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
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    /* Comment: <!-- blah blah blah --> */
    XML_Char* start;
    XML_Char* end;

    p = _SkipChars(p, 2);
    if (!*p)
    {
        XML_Raise(self, XML_ERROR_COMMENT_PREMATURE_END);
        return;
    }
    start = p;

    while (*p)
    {
        if (p[0] == '-' && p[1] == '-')
        {
            if (p[2] != '>')
            {
                XML_Raise(self, XML_ERROR_COMMENT_END_EXPECTED);
                return;
            }

            /* Null-terminate this comment */
            end = p;
            p += 3;

            /* Prepare element */
            elem->type = XML_COMMENT;
            elem->data.data = start;
            elem->data.size = end - start;
            elem->data.namespaceUri = T("");
            elem->data.namespaceUriSize = 0;
            elem->data.namespaceId = '\0';
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

    XML_Raise(self, XML_ERROR_COMMENT_PREMATURE_END);
}

static void _ParseCDATA(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    /* <![CDATA[...]]> */
    XML_Char* start;
    XML_Char* end;

    p = _SkipChars(p, 7);
    if (!*p)
    {
        XML_Raise(self, XML_ERROR_CDATA_PREMATURE_END);
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
            elem->data.data = start;
            elem->data.size = end - start;
            elem->data.namespaceUri = T("");
            elem->data.namespaceUriSize = 0;
            elem->data.namespaceId = '\0';
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

    XML_Raise(self, XML_ERROR_CDATA_PREMATURE_END);
    return;
}

static void _ParseDOCTYPE(
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    MI_UNUSED(elem);

    /* Recognize <!DOCTYPE ...> */
    p = _SkipChars(p, 7);
    if (!*p)
    {
        XML_Raise(self, XML_ERROR_DOCTYPE_PREMATURE_END);
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
        XML_Raise(self, XML_ERROR_DOCTYPE_PREMATURE_END);
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
    _Inout_ XML* self, 
    _Inout_ XML_Elem* elem, 
    _In_z_ XML_Char* p)
{
    XML_Char* start;
    XML_Char* end;

    /* Reject input if it does appear inside tags */
    if (self->stackSize == 0)
    {
        /* Finished parsing document */
        self->status = 1;
        self->ptr = p;
        return 0;
    }

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
        XML_Raise(self, XML_ERROR_CHARDATA_EXPECTED_ELEMENT_END_TAG);
        return 0;
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
    elem->data.data = start;
    elem->data.size = end - start;
    elem->data.namespaceUri = T("");
    elem->data.namespaceUriSize = 0;
    elem->data.namespaceId = '\0';

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
    _Inout_ XML_Elem* self,
    XML_Char nsId,
    _In_z_ const XML_Char* name)
{
    size_t i;

    for (i = 0; i < self->attrsSize; i++)
    {
        if (nsId == self->attrs[i].name.namespaceId &&
            XML_strcmp(name, self->attrs[i].name.data) == 0)
            return self->attrs[i].value;
    }

    /* Not found! */
    return NULL;
}

void XML_Init(
    _Out_ XML* self)
{
    memset(self, 0, sizeof(XML));

    self->nameSpacesCacheIndex = (size_t)-1;
}

void XML_SetText(
    _Inout_ XML* self,
    _In_z_ XML_Char* text)
{
    self->text = text;
    self->ptr = text;
    self->line = 1;
    self->state = STATE_START;
}

int GetNextSkipCharsAndComments(XML *xml, XML_Elem *e)
{
    while (1)
    {
        if (XML_Next(xml, e) == 0)
        {
            switch (e->type)
            {
              case XML_CHARS:
                  if (_AllSpace(e->data.data, e->data.size))
                      continue;
                  else
                      return -1;

              case XML_COMMENT:
                  continue;

              default:
                  return 0;
            }
        }
        else
        {
            //ERROR
            return -1;
        }
    }
}

int XML_Next(
    _Inout_ XML* self,
    _Out_ XML_Elem* elem)
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
                    XML_Raise(self, XML_ERROR_OPEN_ANGLE_BRACKET_EXPECTED);
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
                        XML_Raise(self, XML_ERROR_COMMENT_CDATA_DOCTYPE_EXPECTED);
                        return -1;
                    }
                }
                else
                {
                    XML_Raise(self, XML_ERROR_ELEMENT_EXPECTED);
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
                XML_Raise(self, XML_ERROR_UNEXPECTED_STATE);
                return -1;
            }
        }
    }

    //return 0;
}

int XML_Expect(
    _Inout_ XML* self,
    _Out_ XML_Elem* elem,
    XML_Type type,
    XML_Char nsId,
    _In_z_ const XML_Char* name)
{
    if (XML_CHARS == type)
    {
        if (XML_Next(self, elem) == 0 && 
            elem->type == type)
        {
            return 0;
        }
    }
    else
    {
        if (GetNextSkipCharsAndComments(self, elem) == 0 && 
            elem->type == type && 
            nsId == elem->data.namespaceId &&
            (!name || XML_strcmp(elem->data.data, name) == 0))
        {
            return 0;
        }
    }

    if (type == XML_START)
        XML_Raise(self, XML_ERROR_ELEMENT_NAME_EXPECTED, 
            tcs(name), tcs(elem->data.data));
    else if (type == XML_END)
        XML_Raise(self, XML_ERROR_SPECIFIC_END_ELEMENT_EXPECTED,
            tcs(name), tcs(elem->data.data));
    else if (type == XML_CHARS)
        XML_Raise(self, XML_ERROR_CHARACTER_DATA_EXPECTED);

    return -1;
}

int XML_Skip(
    _Inout_ XML* self)
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
    _Inout_ XML* self,
    XML_Char id,
    _In_z_ const XML_Char* uri)
{
    XML_RegisteredNameSpace rns;
    /* ATTN: we do not check for duplicates */

    /* Reject out of range ids */
    if (id < 'a' || id > 'z')
        return -1;

    /* Check for overflow of the array */
    if (self->registeredNameSpacesSize == XML_MAX_REGISTERED_NAMESPACES)
        return -1;

    rns.id = id;
    rns.uri = uri;
    rns.uriCode = _HashCode(uri, XML_strlen(uri));

    self->registeredNameSpaces[self->registeredNameSpacesSize++] = rns;

    return 0;
}

int XML_PutBack(
    _Inout_ XML* self,
    _In_ const XML_Elem* elem)
{
    /* Check for stack overflow */
    if (self->elemStackSize == XML_MAX_NESTED)
    {
        XML_Raise(self, XML_ERROR_ELEMENT_DEPTH_OVERFLOW, 
            (int)XML_MAX_NESTED);
        return -1;
    }

    self->elemStack[self->elemStackSize++] = *elem;
    return 0;
}

void XML_Raise(XML* self, _In_z_ const XML_Char* format, ...)
{
    va_list ap;

    self->status = -1;
    self->message[0] = '\0';

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    Vstprintf(self->message, MI_COUNT(self->message), format, ap);
    va_end(ap);
}

void XML_FormatError(_Inout_ XML* self, _Out_writes_z_(size) XML_Char* buffer, size_t size)
{
    *buffer = '\0';

    if (self->status == -1)
    {
        Stprintf(
            buffer, 
            size, 
            PAL_T("%u: error: %T"), 
            (unsigned int)self->line, 
            tcs(self->message));
    }
}


int XML_StripWhitespace(
    _Inout_ XML_Elem* elem)
{
    if (elem->type != XML_CHARS)
    {
        return -1;
    }

    //Strip leading white space
    while (elem->data.size && _IsSpace(*elem->data.data))
    {
        elem->data.data++;
        elem->data.size--;
    }
    //Strip trailing white space
    while(elem->data.size && _IsSpace(elem->data.data[elem->data.size-1]))
    {
        elem->data.data[elem->data.size-1] = T('\0');
        elem->data.size--;
    }
    return 0;
}

int XML_ParseCharFault(const XML *self, const XML_Char *data, XML_Char *buffer, size_t buf_size)
{
#define PREFIX_SIZE 32
    XML_Char prefix[PREFIX_SIZE];
    int i, j, k, l;
    MI_Boolean prefixFound = MI_FALSE;

    for (i=0; i<PREFIX_SIZE-1; ++i)
    {
        if (data[i] == ':')
        {
            prefixFound = MI_TRUE;
            prefix[i] = '\0';
            break;
        }
        else
        {
            prefix[i] = data[i];
        }
    }

    if (MI_FALSE == prefixFound)
        return -1;

    unsigned int code = _HashCode(prefix, i);
    size_t faultLen = XML_strlen(&data[i+1]);

    for (j=0; j<self->nameSpacesSize; ++j)
    {
        const XML_NameSpace* ns = &self->nameSpaces[j];

        if (ns && ns->nameCode == code && XML_strcmp(ns->name, prefix) == 0)
        {
            if (buf_size < ns->uriSize + faultLen + 2)
                return -1;   // insufficient buffer size

            for (k = 0; k < ns->uriSize; ++k)
            {
                buffer[k] = ns->uri[k];
            }

            buffer[k] = ':';

            for(l = 0; l < faultLen; ++l)
            {
                buffer[k+l+1] = data[i+l+1];
            }

            buffer[k+l+1] = '\0';
            return 0;
        }
    }        
    return -1;
}

