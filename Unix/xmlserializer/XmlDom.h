/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#ifndef _mixmldom_h
#define _mixmldom_h

#include <MI.h>
#include <xml/xml.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _XMLDOM_Attr XMLDOM_Attr;

struct _XMLDOM_Attr
{
    const MI_Char *name;
    size_t nameLength;
    const MI_Char *value;
    size_t valueLength;
    const MI_Char *namespaceUri;
    size_t namespaceUriLength;
    MI_Char namespaceId;

    XMLDOM_Attr *next;
};

typedef struct _XMLDOM_ElemValue XMLDOM_ElemValue;

struct _XMLDOM_ElemValue
{
    const MI_Char *value;
    size_t valueLength;

    XMLDOM_ElemValue *next;
};

typedef struct _XMLDOM_Elem XMLDOM_Elem;

struct _XMLDOM_Elem
{
    const MI_Char *name;
    size_t nameLength;
    const MI_Char *namespaceUri;
    size_t namespaceUriLength;
    MI_Char namespaceId;

    XMLDOM_ElemValue *value_first;
    XMLDOM_ElemValue *value_last;

    XMLDOM_Attr *attr_first;
    XMLDOM_Attr *attr_last;

    XMLDOM_Elem *child_first;    
    XMLDOM_Elem *child_last;    

    XMLDOM_Elem *sibling_next;
    
    XMLDOM_Elem *parent;
};

typedef struct _XMLDOM_Doc
{
    XMLDOM_Attr *instructions_first;
    XMLDOM_Attr *instructions_last;
    XMLDOM_Elem *root;
} XMLDOM_Doc;


MI_Result XMLDOM_Parse(_In_z_ MI_Char *xmlString, _Outptr_result_z_ MI_Char **endOfXml, _Outptr_ XMLDOM_Doc **xmlDoc, _Outptr_opt_result_maybenull_ MI_Instance **errorObject);
void XMLDOM_Free(_Inout_ XMLDOM_Doc *xmlDoc);
void XMLDOM_Dump(_In_ XMLDOM_Doc *xmlDoc);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* _mixmldom_h */
