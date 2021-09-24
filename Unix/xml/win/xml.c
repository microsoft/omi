/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "xml.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <wchar.h>
#include <stdarg.h>
#include <pal/strings.h>

#define INLINE __inline
typedef Char wchar_t;
#define wmemcmp(x, y, z) memcmp(x, y, z*sizeof(Char))
#define MI_UNUSED(x) x;
#define T(CHAR) L##CHAR

void XML_Raise(__inout XML* self, unsigned errorStringId, ...);

//extern HMODULE g_hModule; /*From DllMain */

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

INLINE int _IsSpace(Char c)
{
    /* Space characters include [\n\t\r ]
     *     _spaceChar['\n'] => 1
     *     _spaceChar['\r'] => 2
     *     _spaceChar['\t'] => 2
     *     _spaceChar[' '] => 2
     */
    static const unsigned char _table[256] =
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

    if (c < 256)
        return _table[(unsigned int)c];
    else
        return 0;
}

/* Matches XML name characters of the form: [A-Za-z_][A-Za-z0-9_-.:]*
 *     _nameChar[A-Za-z_] => 2 (first character)
 *     _nameChar[A-Za-z0-9_-.:] => 1 or 2 (inner character)
 */
static const unsigned char _nameCharTable[256] =
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

INLINE int _IsFirst(Char c)
{
    if (c < 256)
        return _nameCharTable[(unsigned int)c] & 2;
    else 
        return 0;
}

INLINE int _IsInner(Char c)
{
    if (c < 256)
        return _nameCharTable[(unsigned char)c];
    else
        return 0;
}

INLINE Char* _SkipInner(__in_z Char* p)
{
    while (*p && _IsInner(*p))
        p++;

    return p;
}

static Char* _SkipSpacesAux(__inout XML* self, __in_z Char* p)
{
    Char x;
    size_t n = 0;

    while (*p && (x = (Char)_IsSpace(*p)) != 0)
    {
        n += 0x01 & x;
        p++;
    }

    self->line += n;
    return p;
}

INLINE Char* _SkipSpaces(__inout XML* self, __in_z Char* p)
{
    if ((p[0] == '\0') || !_IsSpace(p[0]))
        return p;

    if (p[0] == '\n')
        self->line++;

    if ((p[1] == '\0') || !_IsSpace(p[1]))
        return &p[1];

    if (p[1] == '\n')
        self->line++;

    if ((p[2] == '\0') || !_IsSpace(p[2]))
        return &p[2];

    if (p[2] == '\n')
        self->line++;

    return _SkipSpacesAux(self, &p[3]);
}

INLINE Char* _ToEntityRef(
    __inout XML* self, 
    __in_z Char* p, 
    __inout_z Char* ch)
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

    XML_Raise(self, ID_MIUTILS_XMLPARSER_BAD_ENTITY_REFERENCE);
    return p;
}

INLINE Char* _ToCharRef(__inout XML* self, __in_z Char* p, __inout_z Char* ch)
{
    Char* end = NULL;
    unsigned long x;

    if (*p == 'x')
    {
        p++;
        x = wcstoul(p, &end, 16);
    }
    else
    {
        x = wcstoul(p, &end, 10);
    }

    if (end == p || *end != ';' || x > 255)
    {
        *ch = '\0';
        XML_Raise(self, ID_MIUTILS_XMLPARSER_BAD_CHARACTER_REFERENCE);
        return p;
    }

    *ch = (Char)x;

    return end + 1;
}

INLINE Char* _ToRef(__inout XML* self, __in_z Char* p, __inout_z Char* ch)
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


static int _Match1(Char c)
{
    /* Matches all but '\0', '\'', '"', and '&'. All matching characters
     * yeild 2, except for '\n', which yields 1 
     */
    static const unsigned char _match[256] =
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

    if (c < 256)
        return _match[(unsigned char)c];
    else
        return 1;
}

/* Reduce entity references and remove leading and trailing whitespace */
static Char* _ReduceAttrValue(__inout XML* self, __deref_inout_z Char** pInOut, Char eos)
{
    Char* p = *pInOut;
    Char* end;
    size_t n = 0;

    /* Skip uninteresting characters */
    for (;;)
    {
        while (*p && _Match1(*p))
            p++;

        if (*p != '\n')
            break;

        self->line++;
        p++;
    }

    end = p;

    while (*p && *p != eos)
    {
        if (*p == '&')
        {
            Char c = '\0';
            Char* tmp;
            
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

static int _Match2(Char c)
{
    /* Match all but these: '\0', '<', '&', '\n' */
    static const unsigned char _match[256] =
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

    if (c < 256)
        return _match[(unsigned char)c];
    else
        return 1;
}

/* Reduce character data, advance p, and return pointer to end */
static Char* _ReduceCharData(__inout XML* self, __deref_inout_z Char** pInOut)
{
    Char* p = *pInOut;
    Char* end;
    size_t n = 0;

    for (;;)
    {
        while (*p && (_Match2(*p)))
            p++;

        if (*p != '\n')
            break;

        p++;
        self->line++;
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
    while (*p && *p != '<')
    {
        if (*p == '&')
        {
            Char c = '\0';
            Char* tmp;
            
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
                while (_Match2(*p))
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

INLINE unsigned int _HashCode(__in_ecount_z(n) const Char* s, size_t n)
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
static Char _FindNamespaceID(
    __inout XML* self, 
    __in_ecount_z(uriSize) const Char* uri,
    size_t uriSize)
{
    size_t i;
    unsigned int code = _HashCode(uri, uriSize);

    /* Resolve from client namespace registrations */
    for (i = 0; i < self->registeredNameSpacesSize; i++)
    {
        XML_RegisteredNameSpace* rns = &self->registeredNameSpaces[i];

        if (rns->uriCode == code && wcscmp(rns->uri, uri) == 0)
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
static const XML_NameSpace* _FindNamespace(__inout XML* self, __in_z const Char* prefix)
{
    static const XML_NameSpace s_empty = {T(""), 0, T(""), 0, '\0', 0};
    static const XML_NameSpace s_xml = {T("xml"), 3 ^ 'l', T_XML_NS, XML_NS_LEN, '\0', 0};
    static const XML_NameSpace s_xmlns = {T("xmlns"), 5 ^ 's', T_XMLNS_NS, XMLNS_NS_LEN, '\0', 0};
    unsigned int code = _HashCode(prefix, wcslen(prefix));
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
        const XML_NameSpace* ns = &self->nameSpaces[self->nameSpacesCacheIndex];

        if (ns->nameCode == code && wcscmp(ns->name, prefix) == 0)
        {
            return ns;
        }
    }

    /* Translate name to the one found in the nameSpaces[] array */
    for (i = self->nameSpacesSize; i--; )
    {
        const XML_NameSpace* ns = &self->nameSpaces[i];

        if (ns->nameCode == code && wcscmp(ns->name, prefix) == 0)
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
        XML_Raise(self, ID_MIUTILS_XMLPARSER_UNDEFINED_NAMESPACE_PREFIX, prefix);
        return NULL;
    }

    return &s_empty;
}

static void _ParseAttr(
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __deref_inout_z Char** pInOut)
{
    Char* p = *pInOut;
    Char* name;
    Char* nameEnd;
    Char* value;
    Char* valueEnd;
    Char* colon = NULL;
    Char* tag = p;
    Char* prefix = T("");

    /* Parse the attribute name */
    {
        name = p;

        if (!_IsFirst(*p))
        {
            XML_Raise(self, ID_MIUTILS_XMLPARSER_EXPECTED_ATTRIBUTE_NAME);
            return;
        }

        p++;

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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_EXPECTED_ATTRIBUTE_EQUALS, name);
            return;
        }
    }

    /* Null-terminate name now that we are beyond the '=' */
    *nameEnd = '\0';

    /* Skip spaces */
    p = _SkipSpaces(self, p);

    /* Parse the value */
    {
        Char quote;

        /* Expect opening quote */
        if (*p != '"' && *p != '\'')
        {
            XML_Raise(self, ID_MIUTILS_XMLPARSER_EXPECTED_ATTRIBUTE_OPENING_QUOTES, name);
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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_EXPECTED_ATTRIBUTE_CLOSING_QUOTES, name);
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
                XML_Raise(self, ID_MIUTILS_XMLPARSER_TOO_MANY_NAMESPACES,
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
            elem->data.data[elem->data.size] = 0;   //May not have been null termated yet
            XML_Raise(self, ID_MIUTILS_XMLPARSER_TOO_MANY_ATTRIBUTES, elem->data.data, (int)XML_MAX_ATTRIBUTES);
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
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    /* <?xml version="1.0" encoding="UTF-8" standalone="yes"?> */
    Char* start;
    Char* end;

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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_END_OF_XML_INSTRUCTION);
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
        XML_Raise(self, ID_MIUTILS_XMLPARSER_END_OF_INSTRUCTION_MISSING);
        return;
    }

    /* Return element object */
    elem->data.namespaceUri = L"";
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
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    Char* name;
    Char* nameEnd;
    Char* colon = NULL;
    Char* prefix = T("");
    const XML_NameSpace* ns;
    size_t attr;

    /* Found the root */
    self->foundRoot = 1;

    /* Get tag identifier */
    {
        name = p;

        if (!*p || !_IsFirst(*p++))
        {
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_EXPECTED);
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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_PREMATURE_END);
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
    /* Unprefixed attributes inherit from the element */
    for (attr = 0; attr < elem->attrsSize; attr++)
    {
        XML_Attr* item = elem->attrs + attr;
        const XML_NameSpace* itemNS = ns;

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
                XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_DEPTH_OVERFLOW, 
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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_NOT_CLOSED, elem->data.data);
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
        XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_NOT_CLOSED, elem->data.data);
        return;
    }

    /* Zero-terminate the name tag */
    *nameEnd = '\0';

    /* Push opening tag */
    {
        if (self->stackSize == XML_MAX_NESTED)
        {
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_DEPTH_OVERFLOW, 
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
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    /* Closing element: </name> */
    Char* name;
    Char* nameEnd;
    Char* colon = NULL;
    Char* prefix = T("");
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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_EXPECTED_ELEM_END);
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
        XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_NAME_PREMATURE_END_ELEM_END);
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
        XML_Raise(self,ID_MIUTILS_XMLPARSER_ELEMENT_NAME_NOT_CLOSED_ELEM_END);
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
            XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_TOO_MANY_ENDS, name);
            return;
        }

        self->nesting--;

        /* Check that closing name matches opening name */
        {
            XML_Name* xn = &self->stack[self->stackSize];

            if (wcscmp(xn->data, name) != 0 ||
                xn->namespaceId != ns->id ||
                (ns->id == 0 && wcscmp(xn->namespaceUri, ns->uri) != 0))
            {
                XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_END_ELEMENT_TAG_NOT_MATCH_START_TAG, 
                    self->stack[self->stackSize].data, name);
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
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    /* Comment: <!-- blah blah blah --> */
    Char* start;
    Char* end;

    if (!p[0] || !p[1])
    {
    XML_Raise(self, ID_MIUTILS_XMLPARSER_COMMENT_PREMATURE_END);
        return;
    }
    p += 2;
    start = p;

    while (*p)
    {
        if (p[0] == '-' && p[1] == '-')
        {
            if (p[2] != '>')
            {
                XML_Raise(self, ID_MIUTILS_XMLPARSER_COMMENT_END_EXPECTED);
                return;
            }

            /* Null-terminate this comment */
            end = p;
            p += 3;

            /* Prepare element */
            elem->type = XML_COMMENT;
            elem->data.data = start;
            elem->data.size = end - start;
            elem->data.namespaceUri = L"";
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

    XML_Raise(self, ID_MIUTILS_XMLPARSER_COMMENT_PREMATURE_END);
}

static void _ParseCDATA(
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    /* <![CDATA[...]]> */
    Char* start;
    Char* end;

    /* Recognize <!DOCTYPE ...> */
    if (!p[0] || !p[1] || !p[2] || !p[3] || !p[4] || !p[5] || !p[6])
    {
        XML_Raise(self, ID_MIUTILS_XMLPARSER_CDATA_PREMATURE_END);
        return;
    }
    p += 7;
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
            elem->data.namespaceUri = L"";
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

    XML_Raise(self, ID_MIUTILS_XMLPARSER_CDATA_PREMATURE_END);
    return;
}

static void _ParseDOCTYPE(
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    MI_UNUSED(elem);

    /* Recognize <!DOCTYPE ...> */
    if (!p[0] || !p[1] || !p[2] || !p[3] || !p[4] || !p[5] || !p[6])
    {
        XML_Raise(self, ID_MIUTILS_XMLPARSER_DOCTYPE_PREMATURE_END);
        return;
    }
    p += 7;

    while (*p != '\0' && *p != '>')
    {
        if (p[0] == '\n')
            self->line++;

        p++;
    }

    if (*p++ != '>')
    {
        XML_Raise(self, ID_MIUTILS_XMLPARSER_DOCTYPE_PREMATURE_END);
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
    __inout XML* self, 
    __inout XML_Elem* elem, 
    __in_z Char* p)
{
    Char* start;
    Char* end;

#if 0
    pca: Need function to strip leading and trailing white space on a needed basis
    /* Skip leading spaces */
    p = _SkipSpaces(self, p);
#endif
    /* Reject input if it does appear inside tags */
    if (self->stackSize == 0)
    {
        /* Finished parsing document */
        self->status = 1;
        self->ptr = p;
        return 0;
    }

#if 0
    pca: Need function to strip leading and trailing white space on a needed basis
    /* Remove leading spaces */
    p = _SkipSpaces(self, p);
#endif

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
        XML_Raise(self, ID_MIUTILS_XMLPARSER_CHARDATA_EXPECTED_ELEMENT_END_TAG);
        return 0;
    }

#if 0
    pca: Need function to strip leading and trailing white space on a needed basis
    /* Remove trailing spaces (the newlines have already been counted) */
    {
        /* Remove trainling spaces from the character data */
        start[-1] = '\0';

        while (_IsSpace(end[-1]))
            end--;
    }
#endif

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
    elem->data.namespaceUri = L"";
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

const Char* XML_Elem_GetAttr(
    __inout XML_Elem* self,
    __in_z const Char* name)
{
    size_t i;

    for (i = 0; i < self->attrsSize; i++)
    {
        if (wcscmp(name, self->attrs[i].name.data) == 0)
            return self->attrs[i].value;
    }

    /* Not found! */
    return NULL;
}

void XML_Elem_Dump(
    __in const XML_Elem* s)
{
    static const Char* _typeNames[] =
    {
        T("NONE"),
        T("START"),
        T("END"),
        T("INSTRUCTION"),
        T("CHARS"),
        T("COMMENT"),
    };
    size_t i;

    wprintf(T("==== XML_Elem:\n"));
    wprintf(T("type={%s}\n"), _typeNames[(int)s->type]);
    wprintf(T("data={%s}\n"), s->data.data);
    wprintf(T("size=%u\n"), (int)s->data.size);

    if (s->attrsSize)
    {
        for (i = 0; i < s->attrsSize; i++)
        {
            const XML_Attr* attr = &s->attrs[i];
            wprintf(T("%s=%s\n"), attr->name.data, attr->value);
        }
    }

    putchar('\n');
}

void XML_NameSpace_Dump(
    __in XML_NameSpace* self)
{
    wprintf(T("==== XML_NameSpace:\n"));
    wprintf(T("name={%s}\n"), self->name);
    wprintf(T("id={%c}\n"), (int)self->id);
    wprintf(T("uri={%s}\n"), self->uri);
    wprintf(T("depth={%u}\n"), (int)self->depth);
    wprintf(T("\n"));
}

void XML_Init(
    __out XML* self)
{
    memset(self, 0, sizeof(XML));

    self->nameSpacesCacheIndex = (size_t)-1;
}

void XML_SetText(
    __inout XML* self,
    __in_z Char* text)
{
    self->text = text;
    self->ptr = text;
    self->line = 1;
    self->state = STATE_START;
}

int XML_Next(
    __inout XML* self,
    __out XML_Elem* elem)
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
                Char* p = self->ptr;

                /* Skip spaces */
                p = _SkipSpaces(self, p);

                /* Expect '<' */
                if (*p != '<')
                {
                    XML_Raise(self, ID_MIUTILS_XMLPARSER_OPEN_ANGLE_BRACKET_EXPECTED);
                    return -1;
                }

                self->ptr = p + 1;
                self->state = STATE_TAG;
                break;
            }
            case STATE_TAG:
            {
                Char* p = self->ptr;

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
                    else if (wmemcmp(p, T("[CDATA["), 7) == 0)
                    {
                        _ParseCDATA(self, elem, p);
                        return self->status;
                    }
                    else if (wmemcmp(p, T("DOCTYPE"), 7) == 0)
                    {
                        _ParseDOCTYPE(self, elem, p);

                        if (self->status)
                            return -1;

                        break;
                    }
                    else
                    {
                        XML_Raise(self, ID_MIUTILS_XMLPARSER_COMMENT_CDATA_DOCTYPE_EXPECTED);
                        return -1;
                    }
                }
                else
                {
                    XML_Raise(self, ID_MIUTILS_XMLPARSER_ELEMENT_EXPECTED);
                    return-1;
                }
                break;
            }
            case STATE_CHARS:
            {
                Char* p = self->ptr;

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
                XML_Raise(self, ID_MIUTILS_XMLPARSER_UNEXPECTED_STATE);
                return -1;
            }
        }
    }

    //return 0;
}

int XML_Expect(
    __inout XML* self,
    __out XML_Elem* elem,
    XML_Type type,
    Char knownNamespaceID,   /* 0 means not well known */
    __in_z_opt const Char * namespaceURI, /* NULL if expectedNamespace is not 0, otherwise real URL */
    __in_z const Char* name)
{
    if (XML_Next(self, elem) == 0 && 
        elem->type == type && 
        (!name || wcscmp(elem->data.data, name) == 0))
    {
        if (!name)
        {
            return 0; /* No name means no namespace! */
        }
        if (knownNamespaceID)
        {
            if ( knownNamespaceID == elem->data.namespaceId)
            {
                return 0; /* Known namespace IDs the same */
            }
            XML_Raise2(self, T("Namespace URI IDs do not match: <%c>: %c"), knownNamespaceID, elem->data.namespaceId);
            return -1;
        }
        else
        {
            if (namespaceURI && elem->data.namespaceUri && 
                (wcscmp(namespaceURI, elem->data.namespaceUri)== 0))
            {
                /* Non-standard namespace URIs match */
                return 0;
            }
            XML_Raise2(self, T("Namespace URIs do not match: <%s>: %s"), namespaceURI, elem->data.namespaceUri);
            return -1;
        }
    }

    if (type == XML_START)
        XML_Raise2(self, T("expected element: <%s>: %s"), name, elem->data.data);
    else if (type == XML_END)
        XML_Raise2(self, T("expected element: </%s>: %s"), name, elem->data.data);
    else if (type == XML_CHARS)
        XML_Raise2(self, T("expected character data"));

    return -1;
}

int XML_Skip(
    __inout XML* self)
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
    __inout XML* self,
    Char id,
    __in_z const Char* uri)
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
    rns.uriCode = _HashCode(uri, wcslen(uri));

    self->registeredNameSpaces[self->registeredNameSpacesSize++] = rns;

    return 0;
}

int XML_PutBack(
    __inout XML* self,
    __in const XML_Elem* elem)
{
    /* Check for stack overflow */
    if (self->elemStackSize == XML_MAX_NESTED)
    {
        XML_Raise2(self, T("element stack overflow (>%u)"), XML_MAX_NESTED);
        return -1;
    }

    self->elemStack[self->elemStackSize++] = *elem;
    return 0;
}

void XML_Dump(
    __in XML* self)
{
    size_t i;

    printf("==== XML:\n");
    printf("nameSpaces:\n");

    for (i = 0; i < self->nameSpacesSize; i++)
    {
        XML_NameSpace_Dump(&self->nameSpaces[i]);
    }

    putchar('\n');
}

void XML_PutError(__inout XML* self)
{
    if (self->status == -1)
        fwprintf(stderr, T("line %u: %s\n"), (int)self->line, self->message);
}

void XML_Raise2(XML* self, const Char* format, ...)
{
    int n;
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    self->status = -1;
    self->message[0] = '\0';

    va_start(ap, format);
    n = _vsnwprintf(self->message, sizeof(self->message), format, ap);
    va_end(ap);
}

void XML_Raise(__inout XML* self, unsigned formatStringId, ...)
{
#if 0
    Char formatMsg[MAX_PATH];
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    self->status = -1;
    self->message[0] = '\0';

    if(LoadStringW(g_hModule, formatStringId, formatMsg, MAX_PATH))
    {
        va_start(ap, formatStringId);
        FormatMessageW(FORMAT_MESSAGE_FROM_STRING, formatMsg, 0, 0, self->message, sizeof(self->message)/sizeof(self->message[0]), &ap);
        va_end(ap);
    }
#endif
    XML_Raise2(self, T("An XML error occured!"));
}

void XML_FormatError(__inout XML* self, __out_ecount_z(size) Char* format, size_t size)
{
    *format = '\0';

    if (self->status == -1)
        _swprintf_c(format, size, T("%u: error: %s"), 
            (unsigned int)self->line, self->message);
}


int XML_StripWhitespace(
    __inout XML_Elem* elem)
{
    if (elem->type != XML_CHARS)
    {
        return 0;
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
