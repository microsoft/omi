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
#include <base/messages.h>

BEGIN_EXTERNC

#define DEFAULT_CIMNAMESPACE PAL_T("interop")

/* wsman header struct */
typedef struct _WSMAN_WSHeader
{
    /* True if an <s:Action> element was found */
    MI_Boolean foundAction;

    /* Attributes of the request */
    int rqtAction;
    MI_Uint32 maxEnvelopeSize;
    const TChar* rqtClassname;
    const TChar* rqtNamespace;
    const TChar* rqtMessageID;
    const TChar* unknownMandatoryTag;
    MI_DatetimeField operationTimeout;

    /* instance that holds keys of operation (invoke/get/delete etc) */
    MI_Instance* instance;
    Batch* instanceBatch;

    /* invoke-specific */
    const TChar* rqtMethod;
    const TChar* rqtServer;

    enum SchemaRequestType
    {
        NOT_A_SCHEMA_REQUEST,
        CIM_XML_SCHEMA_REQUEST,
        WS_CIM_SCHEMA_REQEUST
    } schemaRequestType;

    MI_Boolean includeInheritanceHierarchy;
    MI_Boolean includeInheritedElements;
    MI_Boolean includeQualifiers;
    MI_Boolean includeClassOrigin;
    MI_Boolean usePreciseArrays;

    /* Unsubscribe-specific */
    MI_Uint32 contextID;
}
WSMAN_WSHeader;

typedef struct _WSMAN_AssociationFilter
{
    const TChar* address;
    MI_Instance* referenceParameters;
    const TChar* associationClassName;
    const TChar* resultClassName;
    const TChar* role;
    const TChar* resultRole;

    /* True if <b:AssociatedInstances> element present false if <b:AssociationInstances>*/
    MI_Boolean isAssosiatorOperation;
}
WSMAN_AssociationFilter;

typedef struct _WSMAN_WSEnumeratePullBody
{
    /* Attributes of the enumerate/Pull request */
    MI_Uint32   maxElements;        /* xs:long (Optional) NOTE: This should be MI_Uint64 */
    MI_DatetimeField maxTime;       /* xs:duration (Optional) */
    MI_Uint64Field   maxCharacters; /* xs:long (Optional) */
    MI_Uint32   polymorphismMode;   /* WSMANTAG_ENUM_POLYMORPHISM_MODE_xxx */
    MI_Uint32   enumerationMode;    /* WSMANTAG_ENUM_MODE_xxx */
    MI_Boolean  allowOptimization;  /* tag wsman:OptimizeEnumeration present */
    MI_DatetimeField expires;       /* xs:duration or xs:datetime (Optional) */
    MI_DatetimeField heartbeat;     /* xs:duration (Optional) */
    MI_Boolean sendBookmarks;       /* Identifies whether the client wants bookmarks sent during Pulls(Optional) */
    const TChar* initialBookmark;   /* xs:any Initial bookmark to use for the subscription (Optional) */

    MI_DatetimeField connectionRetry; /* xs:duration (Optional) */

    /* Pull-specific */
    MI_Uint32   enumerationContextID;

    /* Fields from <w:Filter Dialect="?"> ... </w:Filter> element */
    const TChar* dialect;
    const TChar* filter;

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
    WSMAN_WSHeader* wsheader,
    UserAgent userAgent);

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

#ifndef DISABLE_INDICATION
int WS_ParseSubscribeBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wssubbody);

int WS_ParseUnsubscribeBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wssubbody);
#endif /* ifndef DISABLE_INDICATION */

END_EXTERNC

#endif /* _omi_wsman_wsmanparser_h */
