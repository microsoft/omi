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

#ifndef _xml_xml_h
#define _xml_xml_h

#include <stddef.h>
#include "config.h"
#include <common.h>

#if defined(CONFIG_ENABLE_WCHAR)
# include <wchar.h>
#endif

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

#if defined(CONFIG_ENABLE_WCHAR)
typedef wchar_t XML_Char;
typedef wchar_t XML_UChar;
#else
typedef char XML_Char;
typedef unsigned char XML_UChar;
#endif

typedef _Null_terminated_ XML_Char* XMLCharPtr;
typedef _Null_terminated_ XML_UChar* XMLUCharPtr;

#if defined(__cplusplus)
extern "C" {
#endif

/* Represents an XML name */
typedef struct _XML_Name
{
    /* Pointer to name */
    XML_Char* data;
    /* Size of name (excluding zero-terminator) */
    size_t size;
}
XML_Name;

/* Represents an XML namespace as registered by the client */
typedef struct _XML_RegisteredNameSpace
{
    /* URI for this namespace */
    const XML_Char* uri;

    /* Hash code for uri */
    unsigned int uriCode;

    /* Single character namespace name expected by client */
    XML_Char id;
}
XML_RegisteredNameSpace;

/* Represents an XML namespace as encountered during parsing */
typedef struct _XML_NameSpace
{
    /* Namespace name */
    const XML_Char* name;

    /* Hash code for name */
    unsigned int nameCode;

    /* URI for this namespace */
    const XML_Char* uri;

    /* Single character namespace name expected by client */
    XML_Char id;

    /* Depth at which this definition was encountered */
    size_t depth;
}
XML_NameSpace;

void XML_NameSpace_Dump(
    XML_NameSpace* self);

/* Represents an XML attributes */
typedef struct _XML_Attr
{
    const XML_Char* name;
    const XML_Char* value;
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

/* Represents one XML element */
typedef struct _XML_Elem
{
    /* Type of this XML object */
    XML_Type type;

    /* Character data or tag name */
    const XML_Char* data;
    size_t size;

    /* Attributes */
    XML_Attr attrs[XML_MAX_ATTRIBUTES];
    size_t attrsSize;
}
XML_Elem;

const XML_Char* XML_Elem_GetAttr(
    XML_Elem* self,
    const XML_Char* name);

void XML_Elem_Dump(
    const XML_Elem* self);

typedef struct _XML
{
    /* Points to first text character zero-terminated text */
    XML_Char* text;

    /* Pointer to current character */
    XML_Char* ptr;

    /* Line number */
    size_t line;

    /* Status: 0=Okay, 1=Done, 2=Failed */
    int status;

    /* Error message */
    XML_Char message[256];

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
    XML* self);

void XML_SetText(
    XML* self,
    _In_z_ XML_Char* text);

int XML_Next(
    XML* self,
    XML_Elem* elem);

int XML_Expect(
    XML* self,
    XML_Elem* elem,
    XML_Type type,
    const XML_Char* name);

int XML_Skip(
    XML* self);

int XML_RegisterNameSpace(
    XML* self,
    XML_Char id,
    const XML_Char* uri);

int XML_PutBack(
    XML* self,
    const XML_Elem* elem);

void XML_Dump(
    XML* self);

void XML_PutError(XML* self);

void XML_Raise(XML* self, const XML_Char* format, ...);

void XML_FormatError(XML* self, _Out_writes_z_(size) XML_Char* buffer, _In_ size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* _xml_xml_h */
