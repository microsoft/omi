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

#ifndef _omi_wsman_wsmanparser_h
#define _omi_wsman_wsmanparser_h

#include "config.h"
#include <string.h>
#include <common.h>
#include <xml/xml.h>
#include <base/instance.h>

BEGIN_EXTERNC

/* wsman header struct */
typedef struct _WSMAN_WSHeader
{
    /* True if an <s:Action> element was found */
    MI_Boolean foundAction;

    /* Attributes of the request */
    int rqtAction;
    MI_Uint32 maxEnvelopeSize;
    const ZChar* rqtClassname;
    const ZChar* rqtNamespace;
    const ZChar* rqtMessageID;
    const ZChar* unknownMandatoryTag;

    /* instance that holds keys of operation (invoke/get/delete etc) */
    MI_Instance* instance;
    Batch* instanceBatch;

    /* invoke-specific */
    const ZChar* rqtMethod;
    const ZChar* rqtServer;
}
WSMAN_WSHeader;

typedef struct _WSMAN_AssociationFilter
{
    const ZChar* address;
    MI_Instance* referenceParameters;
    const ZChar* associationClassName;
    const ZChar* resultClassName;
    const ZChar* role;
    const ZChar* resultRole;

    /* True if <b:AssociatedInstances> element present false if <b:AssociationInstances>*/
    MI_Boolean isAssosiatorOperation;
}
WSMAN_AssociationFilter;

typedef struct _WSMAN_WSEnumeratePullBody
{
    /* Attributes of the enumerate/Pull request */
    MI_Uint32   maxElements;
    MI_Uint32   polymorphismMode;   /* WSMANTAG_ENUM_POLYMORPHISM_MODE_xxx */
    MI_Uint32   enumerationMode;     /* WSMANTAG_ENUM_MODE_xxx */
    MI_Boolean  allowOptimization;  /* tag wsman:OptimizeEnumeration present */
    /* Pull-specific */
    MI_Uint32   enumerationContextID;

    /* Fields from <w:Filter Dialect="?"> ... </w:Filter> element */
    const ZChar* dialect;
    const ZChar* filter;

    /* Association operation requested */
    MI_Boolean foundAssociationOperation;

    WSMAN_AssociationFilter associationFilter;
}
WSMAN_WSEnumeratePullBody;

/* WS xml parsing routines */
int WS_ParseSoapEnvelope(
    XML* xml);

int WS_ParseWSHeader(
    XML* xml,
    WSMAN_WSHeader* wsheader);

int WS_ParseEnumerateBody(
    XML* xml, 
    Batch** batch,
    WSMAN_WSEnumeratePullBody* wsenumbody);

int WS_ParsePullBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wsenumpullbody);

int WS_ParseReleaseBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wsenumpullbody);

int WS_ParseInvokeBody(
    XML* xml, 
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);

int WS_ParseCreateBody(
    XML* xml, 
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);

int WS_ParseIdentifyBody(
    XML* xml);

END_EXTERNC

#endif /* _omi_wsman_wsmanparser_h */
