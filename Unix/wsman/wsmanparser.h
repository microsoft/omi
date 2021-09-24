/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
    const TChar* rqtResourceUri;
    const TChar* rqtClassname;
    const TChar* rqtNamespace;
    const TChar* rqtMessageID;
    const TChar* rqtLocale;
    const TChar* rqtDataLocale;
    const TChar* unknownMandatoryTag;
    MI_DatetimeField operationTimeout;

    /* Attributes of the response */
    const TChar* rspRelatesTo;

    /* instance that holds keys of operation (invoke/get/delete etc) */
    MI_Instance* instance;
    Batch* instanceBatch;

    MI_Instance* options;

    /* invoke-specific */
    const TChar* rqtMethod;
    const TChar* rqtServer;

    enum SchemaRequestType
    {
        NOT_A_SCHEMA_REQUEST,
        CIM_XML_SCHEMA_REQUEST,
        WS_CIM_SCHEMA_REQUEST
    } schemaRequestType;

    MI_Boolean includeInheritanceHierarchy;
    MI_Boolean includeInheritedElements;
    MI_Boolean includeQualifiers;
    MI_Boolean includeClassOrigin;
    MI_Boolean usePreciseArrays;
#ifndef DISABLE_SHELL
    MI_Boolean isShellOperation;
    MI_Boolean isCompressed;
#endif

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
    MI_Boolean isAssociatorOperation;
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

    MI_Instance *selectorFilter;

    /* Association operation requested */
    MI_Boolean foundAssociationOperation;

    WSMAN_AssociationFilter associationFilter;
}
WSMAN_WSEnumeratePullBody;

typedef struct _WSMAN_WSFault
{
    MI_Char code[256];
    MI_Char subcode[256];
    MI_Char *reason;
    MI_Char *detail;
    int mi_result;
    MI_Char *mi_message;
}
WSMAN_WSFault;

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
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction);

int WS_ParseCreateBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean *isShellOperation);

int WS_ParseIdentifyBody(
    XML* xml);

int WS_ParseInstanceBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction);

int WS_ParseCreateResponseBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Char ** epr,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean isShell);

int WS_ParseEmptyBody(
    XML* xml);

int WS_ParseFaultBody(
    XML* xml,
    WSMAN_WSFault *fault);

int WS_ParseEnumerateResponse(
    XML* xml, 
    const MI_Char **context,
    MI_Boolean *endOfSequence,
    Batch *dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean firstResponse,
    MI_Boolean *getNextInstance,
    XML_Elem *e);

#ifndef DISABLE_INDICATION
int WS_ParseSubscribeBody(
    XML* xml,
    WSMAN_WSEnumeratePullBody* wssubbody);

int WS_ParseUnsubscribeBody(
    XML* xml,
    WSMAN_WSEnumeratePullBody* wssubbody);
#endif /* ifndef DISABLE_INDICATION */

#ifndef DISABLE_SHELL
int WS_ParseSignalBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);
int WS_ParseReceiveBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);
int WS_ParseSendBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);
int WS_ParseCreateShellBody(
    XML* xml,
    XML_Elem *bodyElem,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);
#endif

int WS_GetInstance(
    XML* xml,
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction);
END_EXTERNC

#endif /* _omi_wsman_wsmanparser_h */
