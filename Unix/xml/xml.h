/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omiar_xml_h
#define _omiar_xml_h

#include <stddef.h>
#include "config.h"
#include <common.h>

#ifdef _MSC_VER
#pragma prefast (disable: 28252)
#pragma prefast (disable: 28253)
#endif

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

    /* Full namespace URI */
    const XML_Char* namespaceUri;
    size_t namespaceUriSize;

    /* Nonzero if a registered namespace was used */
    XML_Char namespaceId;
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
    size_t uriSize;

    /* Single character namespace name expected by client */
    XML_Char id;

    /* Depth at which this definition was encountered */
    size_t depth;
}
XML_NameSpace;

void XML_NameSpace_Dump(
    _In_ XML_NameSpace* self);

/* Represents an XML attributes */
typedef struct _XML_Attr
{
    XML_Name name;
    const XML_Char* value;
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

const XML_Char* XML_Elem_GetAttr(
    _Inout_ XML_Elem* self,
    XML_Char nsId,
    _In_z_ const XML_Char* name);

void XML_Elem_Dump(
    _In_ const XML_Elem* self);

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
    _Out_ XML* self);

void XML_SetText(
    _Inout_ XML* self,
    _In_z_ XML_Char* text);

int XML_Next(
    _Inout_ XML* self,
    _Out_ XML_Elem* elem);

int GetNextSkipCharsAndComments(
    _Inout_ XML *xml, 
    _Out_ XML_Elem *e);

int XML_Expect(
    _Inout_ XML* self,
    _Out_ XML_Elem* elem,
    XML_Type type,
    XML_Char nsId,
    _In_z_ const XML_Char* name);

int XML_Skip(
    _Inout_ XML* self);

int XML_RegisterNameSpace(
    _Inout_ XML* self,
    XML_Char id,
    _In_z_ const XML_Char* uri);

int XML_PutBack(
    _Inout_ XML* self,
    _In_ const XML_Elem* elem);

int XML_StripWhitespace(
    _Inout_ XML_Elem* elem);

void XML_Dump(
    _In_ XML* self);

void XML_PutError(_Inout_ XML* self);

int XML_ParseCharFault(const XML *self, 
                       const XML_Char *data, 
                       XML_Char *buffer, 
                       size_t buf_size);

#if defined(_MSC_VER)
#include "xml_errors_ids.h"

void XML_Raise(_Inout_ XML* self, unsigned formatStringId, ...);
#else

#define XML_ERROR_BAD_ENTITY_REFERENCE ZT("Failed to parse XML. Bad entity reference. Only these are supported: '&lt;', '&gt;', '&amp;', '&quot;', '&apos;'.")
#define XML_ERROR_BAD_CHARACTER_REFERENCE ZT("Failed to parse XML. Bad character reference. Only character references in the range of 0 to 255 are supported.")
#define XML_ERROR_UNDEFINED_NAMESPACE_PREFIX ZT("Failed to parse XML. Undefined namespace prefix found '%T'.")
#define XML_ERROR_EXPECTED_ATTRIBUTE_NAME ZT("Failed to parse XML. An attribute name was expected.")
#define XML_ERROR_EXPECTED_ATTRIBUTE_EQUALS ZT("Failed to parse XML. An '=' character was expected while parsing attribute '%T'.")
#define XML_ERROR_EXPECTED_ATTRIBUTE_OPENING_QUOTES ZT("Failed to parse XML. An opening quote character was expected while parsing attribute '%T'.")
#define XML_ERROR_EXPECTED_ATTRIBUTE_CLOSING_QUOTES ZT("Failed to parse XML. An closing quote character was expected while parsing attribute '%T'.")
#define XML_ERROR_TOO_MANY_NAMESPACES ZT("Failed to parse XML. Too many namespaces were detected. A maximum of %u namespaces are allowed.")
#define XML_ERROR_TOO_MANY_ATTRIBUTES ZT("Failed to parse XML. Too many attributes were detected on element '%T'. A maximum of %u attributes are allowed per element.")
#define XML_ERROR_END_OF_XML_INSTRUCTION ZT("Failed to parse XML. The end of the XML was detected while processing an XML instruction.")
#define XML_ERROR_END_OF_INSTRUCTION_MISSING ZT("Failed to parse XML. The end of the XML instruction was not properly terminated with an '?>'.")
#define XML_ERROR_ELEMENT_NAME_EXPECTED ZT("Failed to parse XML. An element name was expected while decoding an element start tag.")
#define XML_ERROR_ELEMENT_NAME_PREMATURE_END ZT("Failed to parse XML. The end of the XML was detected while processing an XML element name for a element start tag.")
#define XML_ERROR_ELEMENT_DEPTH_OVERFLOW ZT("Failed to parse XML. XML element nesting is too deep. A maximum element depth of %u is supported.")
#define XML_ERROR_ELEMENT_NAME_NOT_CLOSED ZT("Failed to parse XML. The XML element '%T' was not terminated with a '>' while decoding an element start tag.")
#define XML_ERROR_ELEMENT_NAME_EXPECTED_ELEM_END ZT("Failed to parse XML. An element name was expected while decoding an element end tag.")
#define XML_ERROR_ELEMENT_NAME_PREMATURE_END_ELEM_END ZT("Failed to parse XML. The end of the XML was detected while processing an XML element name for a element end tag.")
#define XML_ERROR_ELEMENT_NAME_NOT_CLOSED_ELEM_END ZT("Failed to parse XML. The XML element '%T' was not terminated with a '>' while decoding an element end tag.")
#define XML_ERROR_ELEMENT_TOO_MANY_ENDS ZT("Failed to parse XML. More element end tags were found than element starting tags. The ending tag found is '%T'.")
#define XML_ERROR_ELEMENT_END_ELEMENT_TAG_NOT_MATCH_START_TAG ZT("Failed to parse XML. The XML element end tag expected was '%T', but what was found was '%T'.")
#define XML_ERROR_COMMENT_END_EXPECTED ZT("Failed to parse XML. Double minus signs in comments are not allowed, unless used to terminate comment. '>' was not found.")
#define XML_ERROR_COMMENT_PREMATURE_END ZT("Failed to parse XML. The end of the XML was detected while processing a comment.")
#define XML_ERROR_CDATA_PREMATURE_END ZT("Failed to parse XML. The end of the XML was detected while processing a CDATA.")
#define XML_ERROR_DOCTYPE_PREMATURE_END ZT("Failed to parse XML. The end of the XML was detected while processing a DOCTYPE.")
#define XML_ERROR_CHARDATA_EXPECTED_ELEMENT_END_TAG ZT("Failed to parse XML. While processing the element data no element end tag was discovered.")
#define XML_ERROR_OPEN_ANGLE_BRACKET_EXPECTED ZT("Failed to parse XML. An open angle bracket '<' was expected and not found.")
#define XML_ERROR_COMMENT_CDATA_DOCTYPE_EXPECTED ZT("Failed to parse XML. A comment, CDATA or DOCTYPE element was expected and not found.")
#define XML_ERROR_ELEMENT_EXPECTED ZT("Failed to parse XML. An XML element was expected and not found.")
#define XML_ERROR_UNEXPECTED_STATE ZT("Failed to parse XML. The XML parser hit an interal problem that stopped it from progressing.")
#define XML_ERROR_SPECIFIC_ELEMENT_EXPECTED ZT("Failed to parse XML. The element name %T was expected but %T was found instead.")
#define XML_ERROR_SPECIFIC_END_ELEMENT_EXPECTED ZT("Failed to parse XML. The element name %T end tag was expected but %T was found instead.")
#define XML_ERROR_CHARACTER_DATA_EXPECTED ZT("Failed to parse XML. Character data was expected but not found.")

#define WSMAN_ERROR_NO_CLASS_NAME_IN_SELECTOR ZT("Failed to process WS-Management packet. The class name was not found in the selector.")
#define WSMAN_ERROR_NO_RESOURCE_URI ZT("Failed to process WS-Management packet. The resource URI was not found.")
#define WSMAN_ERROR_OUTOFMEMORY ZT("Failed to process WS-Management packet. Out of memory.")
#define WSMAN_ERROR_BAD_SELECTOR ZT("Failed to process WS-Management packet. Character data or the element EndPointReference was expected in the selector but not found.")
#define WSMAN_ERROR_BAD_EPR_IN_SELECTOR ZT("Failed to process WS-Management packet. The element EndPointReference in the selector could not be parsed.")


void XML_Raise(XML* self, _In_z_ const XML_Char* format, ...);
#endif

void XML_FormatError(_Inout_ XML* self, _Out_writes_z_(size) XML_Char* buffer, size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* _omiar_xml_h */
