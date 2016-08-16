/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_http_httpclient_h
#define _omi_http_httpclient_h

#include "config.h"
#include <common.h>
#include <base/batch.h>
#include <base/interaction.h>
#include <sock/selector.h>

BEGIN_EXTERNC

/* HTTP Client - internal C interface */
typedef struct _HttpClient HttpClient;

/* array of strings (as declared in mi.h)
    This strucutre has layout compatible with MI_StringArray
    and mi::StringA class
    This structure is used to send request.
    Sample of usage:
        const char* header_strings[] = {
            "Content-Type: text/html;charset=UTF-8",
            "User-Agent: xplat http client"
        };
        HttpClientRequestHeaders headers = {
            header_strings,
            MI_COUNT(header_strings) };
*/
typedef struct _HttpClientRequestHeaders
{
    const char* const* data;
    MI_Uint32 size;
}
HttpClientRequestHeaders;

/*
    This structure represents one http header field,
    received from server, as name/value pair.
*/
typedef struct _HttpClientHeaderField
{
    const char* name;
    const char* value;
}
HttpClientHeaderField;

/*
    This structure provides information about http response.
    Members:
    headers: array of name/value pairs
    sizeHeaders: number of pair in headers array
    httpError:  http error code. like 200, 400 etc
*/
typedef struct _HttpClientResponseHeader
{
    const HttpClientHeaderField*  headers;
    MI_Uint32 sizeHeaders;
    MI_Uint32   httpError;

}
HttpClientResponseHeader;

/* *** Callbacks *** */
/*
    Notifies user about completion of http request.
    That's the last call from http library for given http request

    Parameters:
    http - http client object
    callbackData - user-provided data
    result - 'OK' for successfully completed operations
        or corresponding error code
*/
typedef void (*HttpClientCallbackOnStatus)(
    HttpClient* http,
    void* callbackData,
    MI_Result result);
typedef void (*HttpClientCallbackOnConnect)(
        HttpClient* http,
        void* callbackData);
/*
    Notifies user about response from server.
    First time it provides response headers
    and may provide intial part of response content.
    It may be called several more times to deliver the rest of the content.

    Parameters:
    http - http client object
    callbackData - user-provided data
    headers - [opt] http headers from response.
        this parameter is only provided with first call
        and will be null with any additional calls
    contentSize - total size of the payload.
        '0' if no payload (empty response)
        'negative' if payload size is unknown (chunked encoding)
    lastChunk - indication of current chunk is the last one and entire
        content was downloaded. Useful for chunked encoding.
    data - [opt] content to send. if message is accepted to be sent,
        on return *data == null (taking memory ownership)

    Returns:
        'TRUE' if operation should continue;
        'FALSE' to abort operation and close socket connection.
*/
typedef MI_Boolean (*HttpClientCallbackOnResponse)(
    HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data);

/*
    Creates new http client.

    Parameters:
    selfOut - [out] newly created http object (or null if failed).
    selector - [opt] selector to use for socket monitoring. If selector not specified,
            private one is created.
    host - host address
    port - port number
    secure - flag that indicates if http or https connection is required

    Returns:
    'OK' on success or error code otherwise
*/
MI_Result HttpClient_New_Connector(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnStatus statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData,
    MI_DestinationOptions *pDestOptions);

/* HttpClient_New_Connector2 is same as HttpClient_New_connector
 * except it gives an OnConnect callback which is when the socket
 * will be ready to write the body.
 */
MI_Result HttpClient_New_Connector2(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnConnect statusConnect,
    HttpClientCallbackOnStatus statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData,
    MI_DestinationOptions *pDestOptions);

/*
    Deletes http object, disconnects form the server
    and frees all related resources.

    Parameters:
    self - http object

    Returns:
    OK
*/
MI_Result HttpClient_Delete(
    HttpClient* self);


/*
    Sends http request.

    Parameters:
    self - http object
    verb - [opt] "GET", "POST" or "PUT". Default is "POST"
    uri - request's URI
    headers - [opt] extra headers for request.
    data - [opt] content to send. if message is accepted to be sent,
        on return *data == null (taking memory ownership)

    Returns:
    OK or appropriate error
 */
MI_Result HttpClient_StartRequest(
    HttpClient* self,
    const char* verb,
    const char* uri,
    const char*contentType,
    Page** data);

/*
    Sets timeout for http connection.
    Default timeout is 1 minute

    Parameters:
    self - http object
    timeoutUsec - timeout in usecs
*/
MI_Result HttpClient_SetTimeout(
    HttpClient* self,
    MI_Uint64 timeoutUsec);

/*
    Runs selector to perform
*/
MI_Result HttpClient_Run(
    HttpClient* self,
    MI_Uint64 timeoutUsec);

Selector *HttpClient_GetSelector(HttpClient *self);

END_EXTERNC

#endif /* _omi_http_httpclient_h */
