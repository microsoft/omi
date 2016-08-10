/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _oscar_xml_h
#define _oscar_xml_h

#include <stddef.h>

#if !defined(_MSC_VER)
# include <wchar.h>
# define __in
# define __out
# define __inout
# define __in_z
# define __in_z_opt
# define __inout_z
#endif

/* Unicode character */
typedef wchar_t Char;

/* The maximum number of nested XML elements */
#define XML_MAX_NESTED 64

/* The maximum number of XML namespaces */
#define XML_MAX_NAMESPACES 32

/* The maximum number of registered XML namespaces */
#define XML_MAX_REGISTERED_NAMESPACES 32

/* The maximum number of attributes in a start tag */
#define XML_MAX_ATTRIBUTES 32

/* Represents case where tag has no namespace */
#define XML_NAMESPACE_NONE 0

#if defined(__cplusplus)
extern "C" {
#endif

/* Represents an XML name */
typedef struct _XML_Name
{
    /* Pointer to name */
    Char* data;
    /* Size of name (excluding zero-terminator) */
    size_t size;

    /* Full namespace URI */
    const Char* namespaceUri;
    size_t namespaceUriSize;

    /* Nonzero if a registered namespace was used */
    Char namespaceId;
}
XML_Name;

/* Represents an XML namespace as registered by the client */
typedef struct _XML_RegisteredNameSpace
{
    /* URI for this namespace */
    const Char* uri;

    /* Hash code for uri */
    unsigned int uriCode;

    /* Single character namespace name expected by client */
    Char id;
}
XML_RegisteredNameSpace;

/* Represents an XML namespace as encountered during parsing */
typedef struct _XML_NameSpace
{
    /* Namespace name */
    const Char* name;

    /* Hash code for name */
    unsigned int nameCode;

    /* URI for this namespace */
    const Char* uri;
    size_t uriSize;

    /* Single character namespace name expected by client */
    Char id;

    /* Depth at which this definition was encountered */
    size_t depth;
}
XML_NameSpace;

void XML_NameSpace_Dump(
    __in XML_NameSpace* self);

/* Represents an XML attributes */
typedef struct _XML_Attr
{
    XML_Name name;
    const Char* value;
    size_t valueSize;
}
XML_Attr;

/* XML element type tag */
typedef enum _XML_Type
{
    XML_NONE,
    XML_START,
    XML_END,
    XML_INSTRUCTION,
    XML_CHARS,
    XML_COMMENT
}
XML_Type;

#if 0
/* Attribute info (for structure mappings) */
typedef struct _XML_AttrDecl
{
    /* Name of this attribute */
    const Char* name;

    /* 'S'=String 'L'=Long 'D'=Double */
    Char type;

    /* Offset of the field in destination structure */
    size_t offset;

    /* Whether this attribute is required */
    int required;

    /* Pointer to value (Char*, long*, or double*) */
    void* value;
}
XML_AttrDecl;
#endif

/* Represents one XML element */
typedef struct _XML_Elem
{
    /* Type of this XML object */
    XML_Type type;

    /* Tag or character data */
    XML_Name data;

    /* Attributes */
    XML_Attr attrs[XML_MAX_ATTRIBUTES];
    size_t attrsSize;
}
XML_Elem;

const Char* XML_Elem_GetAttr(
    __inout XML_Elem* self,
    __in_z const Char* name);

static __inline int XML_CompareName(
    __in   const XML_Name* self,
    Char namespaceId,
    __in_z const Char* name)
{
    if (self->namespaceId != namespaceId)
        return self->namespaceId - namespaceId;
    return wcscmp(self->data, name);
}

void XML_Elem_Dump(
    __in const XML_Elem* self);

typedef struct _XML
{
    /* Points to first text character zero-terminated text */
    Char* text;

    /* Pointer to current character */
    Char* ptr;

    /* Line number */
    size_t line;

    /* Status: 0=Okay, 1=Done, 2=Failed */
    int status;

    /* Error message */
    Char message[256];
    
    /* Stack of open tags (used to match closing tags) */
    XML_Name stack[XML_MAX_NESTED];
    size_t stackSize;

    /* Current nesting level */
    size_t nesting;

    /* Stack of dummy elements generated for empty tags and PutBack calls */
    XML_Elem elemStack[XML_MAX_NESTED];
    size_t elemStackSize;

    /* Array of namespaces */
    XML_NameSpace nameSpaces[XML_MAX_NAMESPACES];
    size_t nameSpacesSize;

    /* Index of last namespace lookup from nameSpaces[] array */
    size_t nameSpacesCacheIndex;

    /* Predefined namespaces */
    XML_RegisteredNameSpace registeredNameSpaces[XML_MAX_NAMESPACES];
    size_t registeredNameSpacesSize;

    /* Internal parser state */
    int state;

    /* Whether XML root element has been encountered */
    int foundRoot;
}
XML;

void XML_Init(
    __out XML* self);

void XML_SetText(
    __inout XML* self,
    __in_z Char* text);

int XML_Next(
    __inout XML* self,
    __out XML_Elem* elem);

int XML_Expect(
    __inout XML* self,
    __out XML_Elem* elem,
    XML_Type type,
    Char knownNamespaceID,   /* 0 means not well known */
    __in_z_opt const Char * namespaceURI, /* NULL if expectedNamespace is not 0, otherwise real URL */
    __in_z const Char* name);

int XML_Skip(
    __inout XML* self);

int XML_RegisterNameSpace(
    __inout XML* self,
    Char id,
    __in_z const Char* uri);

int XML_PutBack(
    __inout XML* self,
    __in const XML_Elem* elem);

int XML_StripWhitespace(
    __inout XML_Elem* elem);

void XML_Dump(
    __in XML* self);

void XML_PutError(__inout XML* self);

void XML_Raise(__inout XML* self, unsigned formatStringId, ...);
void XML_Raise2(__inout XML* self, const Char *format, ...);   //TODO: PROTOTYPE WORK, REMOVE AFTER

void XML_FormatError(__inout XML* self, __out_ecount_z(size) Char* format, size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* _oscar_xml_h */
