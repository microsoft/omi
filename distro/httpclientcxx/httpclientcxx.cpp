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

#include "httpclientcxx.h"

#include <iostream>
#include <memory>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <semaphore.h>
#include <base/atomic.h>
#include <base/time.h>

#include <common.h>
#include <http/httpclient.h>
#include <sock/thread.h>

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

static sem_t            connectionSemaphore;
static bool             connectionSemaphoreInitialized;
static pthread_mutex_t  connectionSemaphoreLock;
static sem_t            sendSemaphore;
static pthread_mutex_t  sendLock;
static bool             notifySet = false;

using namespace std;

// callback for thread (run function)
BEGIN_EXTERNC
static void* MI_CALL _proc(void*);

// callback for user's functions executed in background thread
static void threadDelegation(void* self, Message* message);

// HTTP callbacks
static void httpClientCallbackOnStatus(
    ::HttpClient* http,
    void* callbackData,
    MI_Result result);

static MI_Boolean httpClientCallbackOnResponse(
    ::HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data);

END_EXTERNC

/*
 Convert a 4-bit binary value to its hexadecimal character representation, using uppercase
 A - F and leading zero, as needed, as per RFC 3986.

 @param[in]     n - the number to be converted

 @returns       the hexadecimal representation of n
*/
static unsigned int ToHexit(unsigned int n)
{
    if (n <= 9)
    {
        return n + '0';
    }
    if (n <= 15)
    {
        return n + 'A' - 10;
    }
    return '?';
}

/*
 Replace a hostname or URI string encoded using the UTF-8 character set with
 another string that specifies the same hostname or URI encoded using the
 escapes specified in RFC 3986.  For a URI, as specified in the RFC, escaping
 stops at the first '?' character after the last slash.

 The scheme, for example, "http:", and host name are not normalized to lower case
 as specified in RFC 3986; neither are path segments normalized.

 This function does not check for correctly-formatted UTF-8 multibyte characters,
 it simply encodes the characters in the input string character-by-character.

 @param[in]     UriString - the unescaped URI string

 @returns       the escaped URI string
*/
static std::string EscapeUriString(const char* UriString, bool UriSyntax)
{
    std::string EscapedUriString;

    EscapedUriString.reserve(strlen(UriString) * 3);    // reserve space so the "+=" operator is more efficient
    for (const char* Uri = UriString; *Uri != '\0'; Uri++)
    {
        unsigned char c = (unsigned char)*Uri;

        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            strchr("-._~/,!'$&%:;*\\", (int)c) != NULL)
        {
            // an unreserved character or delimiter
            EscapedUriString += (char)c;
        }
        else if (c == '?')
        {
            // a '?': if a URI, check for '?' before or after the final '/'
            EscapedUriString += '?';
            if (UriSyntax && strchr(Uri, '/') == NULL)
            {
                // if a URI and there is no '/' after this, this finishes translation
                if (*(Uri + 1) != '\0')
                {
                    EscapedUriString += std::string(Uri + 1);
                }
                break;
            }
        }
        else
        {
            // a character that must be escaped
            EscapedUriString += '%';
            EscapedUriString += ToHexit((unsigned int)c >> 4);
            EscapedUriString += ToHexit((unsigned int)c & 0x0000000F);
        }
    }
    return EscapedUriString;
}

HTTPCLIENT_BEGIN

/* helper structure used to post messages from calling thread
    to background processing thread
*/
class NotifyItem
{
public:
    // data generic for all calls
    enum Type {
        CONNECT, START_REQUEST, DELETE_HTTP, SET_TIMEOUT
    } _type;
    HttpClientRep* _rep;
    Message* _msg;

    /* Connect-specific */
    std::string _host;
    unsigned short _port;
    bool _secure;
    std::string _trustedCertsDir;
    std::string _certFile;
    std::string _privateKeyFile;
    sem_t      *_connectionSemaphore;
    bool       *_connectWorked;
    bool       *_connectComplete;

    /* start-request- specific */
    std::string _verb;
    std::string _uri;
    std::map< std::string, std::string > _extraHeaders;
    std::vector< unsigned char > _data;

    // connect request
    NotifyItem(
        class HttpClientRep* rep,
        const char* host,
        unsigned short port,
        bool secure,
        const char* trustedCertsDir,
        const char* certFile,
        const char* privateKeyFile,
        sem_t     * connectionSemaphore,
        bool      * connectWorked,
        bool      * connectComplete):
        _type(CONNECT),
        _rep(rep),
        _host(host),
        _port(port),
        _secure(secure),
        _trustedCertsDir(trustedCertsDir == NULL ? "" : trustedCertsDir),
        _certFile(certFile == NULL ? "" : certFile),
        _privateKeyFile(privateKeyFile == NULL ? "" : privateKeyFile),
        _connectionSemaphore(connectionSemaphore),
        _connectWorked(connectWorked),
        _connectComplete(connectComplete)
    {
        _InitMsg();
    }

    // start-request
    NotifyItem(
        class HttpClientRep* rep,
        const char* verb,
        const char* uri,
        const std::map< std::string, std::string >& extraHeaders,
        const std::vector< unsigned char >& data):
        _type(START_REQUEST),
        _rep(rep),
        _port(0),
        _secure(false),
        _verb(verb),
        _uri(uri),
        _extraHeaders(extraHeaders),
        _data(data)
    {
        _InitMsg();
    }

    // delete-http item
    NotifyItem(
        class HttpClientRep* rep):
        _type(DELETE_HTTP),
        _rep(rep),
        _port(0),
        _secure(false)
    {
        _InitMsg();
    }

    // set Timeout item
    NotifyItem(
        class HttpClientRep* rep,
        int /*timeout*/):
        _type(SET_TIMEOUT),
        _rep(rep),
        _port(0),
        _secure(false)
    {
        _InitMsg();
    }

    ~NotifyItem()
    {
        Message_Release(_msg);
    }

private:
    NotifyItem(const NotifyItem&);
    void operator=(const NotifyItem&);

    void _InitMsg()
    {
        _msg = __Message_New(NoOpReqTag, sizeof(NoOpReq), 0, 0);
        *((void**)&_msg->clientID) = this;
    }
};

/* Helper class - background thread operations */
class IOThread
{
public:
    IOThread();
    ~IOThread();

    bool Start();

    /* delegate work to background thread */
    bool PostItem(NotifyItem* item);

//private:
    // not supported
    IOThread(const IOThread&);
    void operator = (const IOThread&);

    // impl

    // mirror functions for public API.
    // note: these functions are always called from the context of the background thread

    void ConnectTh(NotifyItem* item);
    void StartRequestTh(NotifyItem* item);
    void DeleteHttpTh(NotifyItem* item);
    void SetTimeoutTh(NotifyItem* item);

    // data
    ThreadHandle    _th;
    Selector        _selector;
};

/* thread handle - used to store ref-counted pointer to IOThread */
class IOThreadHandle
{
    struct Item {
        AtomicInt   ref;
        IOThread    t;

        Item() :ref(0){}
    };

    Item* _p;

    void _AddRef()
    {
        if (_p != NULL)
            AtomicInc(&_p->ref);
    }

    void _Release()
    {
        if (_p != NULL && AtomicDec(&_p->ref))
        {
            delete _p;
            _p = NULL;
        }
    }
public:

    // full set of ctors/dtors/assign operators
    ~IOThreadHandle() {_Release();}
    IOThreadHandle() : _p(0) {}
    IOThreadHandle(const IOThreadHandle& x) : _p(x._p) {_AddRef();}
    IOThreadHandle& operator =(const IOThreadHandle& x)
    {
        if (_p != x._p)
        {
            _Release();
            _p = x._p;
            _AddRef();
        }
        return *this;
    }

    // accessor
    IOThread* operator ->()
    {
        return &_p->t;
    }

    // allocator
    void Alloc()
    {
        _Release();
        _p = new Item;
        _AddRef();
    }
};

// forward declaration
static IOThreadHandle _GetThreadObj();

/* impl class */
class HttpClientRep
{
public:
    HttpClientRep(HttpClientCallback* callback) :
      _callback(callback),
      _timeoutMS(1000),
      _httpClient(NULL),
      _notify(false),
      _lastStatus(httpclient::OKAY)
    {
        _th = _GetThreadObj();
    }

    virtual ~HttpClientRep()
    {
        if (_httpClient != NULL)
        {
            HttpClient_Delete(_httpClient);
            _httpClient = NULL;
        }
    }

    // data
    HttpClientCallback* _callback;
    IOThreadHandle _th;
    int _timeoutMS;
    ::HttpClient* _httpClient;
    bool _notify;
    httpclient::Result _lastStatus;
};


/* ****************************************************** */

IOThread::IOThread() :
    _th(0)
{
}

IOThread::~IOThread()
{
    // notify about stopping!
    Selector_StopRunning(&_selector);

    if (_th)
        Thread_Destroy(_th, MI_TRUE);

    // clean up
    Selector_RemoveAllHandlers(&_selector);
    Selector_Destroy(&_selector);
}

bool IOThread::Start()
{
    if (MI_RESULT_OK != Selector_Init(&_selector))
        return false;

    Selector_SetAllowEmptyFlag(&_selector, MI_TRUE);

    if (MI_RESULT_OK != Thread_Create(_proc, this, &_th))
        return false;

    return true;
}

bool IOThread::PostItem(NotifyItem* item)
{
#ifdef ENABLE_TRACING
    LOGD2((ZT("IoThread::PostItem - Posting item: %d (%s)"), item->_type, notifyitemtypestr(item->_type)));
    if (item->_type == NotifyItem::CONNECT)
    {
        LOGD2((ZT("PostItem - CONNECT. host: %s, port %d"), item->_host.c_str(), item->_port));
    }
    if (item->_type == NotifyItem::START_REQUEST)
    {
        LOGD2((ZT("PostItem - START_REQUEST. verb: %s, URI: %s"), item->_verb.c_str(), item->_uri.c_str()));
    }
#endif

    MI_Result res = Selector_CallInIOThread(&_selector, threadDelegation, this, item->_msg);

    return res == MI_RESULT_OK;
}

void IOThread::ConnectTh(NotifyItem* item)
{
    MI_Result res = HttpClient_New_Connector(
        &item->_rep->_httpClient,
        &_selector,
        item->_host.c_str(),
        item->_port,
        item->_secure,
        httpClientCallbackOnStatus,
        httpClientCallbackOnResponse,
        item->_rep,
        item->_trustedCertsDir.c_str(),
        item->_certFile.c_str(),
        item->_privateKeyFile.c_str());

    if (res != MI_RESULT_OK)
    {
        *item->_connectWorked = false;
        item->_rep->_callback->OnStatus(httpclient::FAILED);
        item->_rep->_notify = true;
        LOGE2((ZT("IOThread::ConnectTh - Connection failed with error: %d (%s)"), (int)res, mistrerror(res)));
        notifySet = true;
    }
    else
    {
        // item->_rep->_callback->OnStatus(httpclient::OKAY);
        *item->_connectWorked = true;
    }

    *item->_connectComplete = true;

    HttpClient_SetTimeout(item->_rep->_httpClient, (MI_Uint64)item->_rep->_timeoutMS * 1000);

    sem_post(&connectionSemaphore);

    LOGD2((ZT("IOThread::ConnectTh - HttpClient_New_Connector returned result: %d (%s), timeout: %d ms"), (int)res, mistrerror(res), item->_rep->_timeoutMS));
}

void IOThread::StartRequestTh(NotifyItem* item)
{
    Page* c_data = NULL;
    const char* c_verb = item->_verb.c_str();
    HttpClientRequestHeaders c_headers;
    std::vector< std::string > headers_strings;
    std::vector< const char* > headers_pointers;

    memset(&c_headers, 0, sizeof(c_headers));

    if (!item->_data.empty() > 0)
    {
        c_data = (Page*)malloc(item->_data.size() + sizeof (Page));

        /* clear header */
        memset(c_data, 0, sizeof(Page));

        c_data->u.s.size = (unsigned int)item->_data.size();

        memcpy(c_data+1, &item->_data[0], item->_data.size());
    }

    if (!item->_extraHeaders.empty())
    {
        // create array of strings
        for (std::map< std::string, std::string >::const_iterator it = item->_extraHeaders.begin(); it != item->_extraHeaders.end(); it++)
        {
            std::string s = it->first;
            s += ": ";
            s += it->second;
            headers_strings.push_back(s);
        }

        // create array of pointers
        for (size_t i = 0; i < headers_strings.size(); i++)
        {
            headers_pointers.push_back(headers_strings[i].c_str());
        }

        // initialize c-struct:
        c_headers.size = headers_pointers.size();
        c_headers.data = &headers_pointers[0];
    }

    MI_Result res = HttpClient_StartRequest(
        item->_rep->_httpClient,
        c_verb,
        item->_uri.c_str(),
        &c_headers,
        &c_data);

    if (c_data != NULL)
    {
        free(c_data);
        c_data = NULL;
    }

    if (MI_RESULT_OK != res)
    {
        LOGE2((ZT("IOThread::_StartRequestTh - HTTP client request failed with error: %d (%s)"), (int)res, mistrerror(res)));
        item->_rep->_callback->OnStatus(res == MI_RESULT_TIME_OUT ? httpclient::TIMEOUT : httpclient::FAILED);
    }
/*
    else
    {
        item->_rep->_callback->OnStatus(httpclient::OKAY);
    }
*/
    return;
}

void IOThread::DeleteHttpTh(NotifyItem* item)
{
    LOGD2((ZT("_DeleteHttpTh - Deleting HTTP thread")));

    MI_Result res = HttpClient_Delete(item->_rep->_httpClient);

    // Clean up here as the first thread is not waiting for any signal for this to be completed.
}

void IOThread::SetTimeoutTh(NotifyItem* item)
{
    HttpClient_SetTimeout(item->_rep->_httpClient, ((MI_Uint64)item->_rep->_timeoutMS * 1000));

    // Clean up here as the first thread is not waiting for any signal for this to be completed.
}

static IOThreadHandle _GetThreadObj()
{
    static IOThreadHandle s_obj;
    static int s_init = 0;
    static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

    /* check if we may need to init */
    if (!s_init)
    {
        pthread_mutex_lock(&s_mutex);

        /* check if we really need to init or get here by race-condition */
        if (!s_init)
        {
            s_obj.Alloc();
            s_obj->Start();
            s_init = 1;
        }

        pthread_mutex_unlock(&s_mutex);

    }

    return s_obj;
}

/* ******************************************** */

HttpClient::~HttpClient()
{
    pthread_mutex_lock(&m_httpClientLock);

    if (_rep != NULL)
    {
        delete _rep;
    }

    pthread_mutex_unlock(&m_httpClientLock);
    LOGD2((ZT("HttpClient::~HttpClient finished")));
}

HttpClient::HttpClient(HttpClientCallback* callback)
{
    pthread_mutex_init(&m_httpClientLock, NULL);

    pthread_mutex_lock(&m_httpClientLock);
    _rep = new HttpClientRep(callback);
    pthread_mutex_unlock(&m_httpClientLock);
}

Result HttpClient::Connect(
    const char* host,
    unsigned short port,
    bool secure,
    const char* trustedCertsDir,
    const char* certFile,
    const char* privateKeyFile)
{
    if (!connectionSemaphoreInitialized)
    {
        connectionSemaphoreInitialized = true;
        sem_init(&connectionSemaphore, 0, 0);
        sem_init(&sendSemaphore, 0, 0);
        pthread_mutex_init(&connectionSemaphoreLock, NULL);
        pthread_mutex_init(&sendLock, NULL);
    }

    pthread_mutex_lock(&connectionSemaphoreLock);

    bool connectWorked = false;
    bool connectComplete = false;

    LOGD2((ZT("HttpClient::Connect - host: %s, port: %u"), host, (unsigned int)port));
    std::string EncodedHost(EscapeUriString(host, false));

    NotifyItem* item = new NotifyItem(_rep,
                                      EncodedHost.empty() ? "" : EncodedHost.c_str(),
                                      port,
                                      secure,
                                      trustedCertsDir,
                                      certFile,
                                      privateKeyFile,
                                      &connectionSemaphore,
                                      &connectWorked,
                                      &connectComplete);

    if (!_rep->_th->PostItem(item))
    {
        LOGE2((ZT("HttpClient::Connect - PostItem failed")));
        return httpclient::FAILED;
    }

    LOGD2((ZT("HttpClient::Connect - Waiting for connection complete semaphore")));

#if 1 // defined(__hpux) || defined(macos) || defined(__SunOS_5_9)   // these OSs don't have sem_timedwait
    // Yeah, sure, this is async.  You betcha.  That's why we're going to wait
    // here until the connect is complete.
    while (!connectComplete)
    {
        LOGD2((ZT("Waiting for connection complete semaphore")));
        sem_wait(&connectionSemaphore);
        LOGD2((ZT("Connection complete semaphore received.  connectComplete was %s"), connectComplete ? "True" : "False"));
    }
#else
    // Wait 30 seconds until the connect is complete or there was an error.
    struct timespec timeout_time;
    time_t current_time = time(NULL);

    timeout_time.tv_sec = current_time + 31;   // 30 - 31 seconds, since we don't compute tv_nsec.
    timeout_time.tv_nsec = 0;
    if (sem_timedwait(&connectionSemaphore, &timeout_time) < 0)
    {                                   // in most cases, errno here will be ETIMEDOUT
        LOGD2((ZT("HttpClient::Connect - Connect process error: %d (%s)"), errno, strerror(errno)));
    }
#endif
    LOGD2((ZT("HttpClient::Connect - Connection complete or error. connectComplete was %d, connectWorked was: %d"), connectComplete, connectComplete));
    // sem_destroy(&connectionSemaphore);

    pthread_mutex_unlock(&connectionSemaphoreLock);
    if (!connectWorked)
    {
        // failure
        LOGE2((ZT("HttpClient::Connect - connection failed")));
        return httpclient::FAILED;
    }

    LOGD2((ZT("HttpClient::Connect - OK")));
    return httpclient::OKAY;
}

Result HttpClient::StartRequest(
    const char* verb,
    const char* uri,
    const std::map< std::string, std::string >& extraHeaders,
    const std::vector<unsigned char >& data,
    bool blockUntilCompleted)
{
    pthread_mutex_lock(&sendLock);

    std::string EncodedUri(EscapeUriString(uri, true));

    LOGD2((ZT("HttpClient::StartRequest - verb: %s, URI: %s"), verb, uri));
    NotifyItem* item = new NotifyItem(_rep, verb, EncodedUri.empty() ? "" : EncodedUri.c_str(), extraHeaders, data);

    _rep->_notify = false;
    notifySet = false;
    if (!_rep->_th->PostItem(item))
    {
        LOGE2((ZT("HttpClient::StartRequest - PostItem failed")));
        pthread_mutex_unlock(&sendLock);
        return httpclient::FAILED;
    }

    if (blockUntilCompleted)
    {
        httpclient::Result res;

#if defined(__hpux) || defined(macos) || defined(__SunOS_5_9)   // these OSs don't have sem_timedwait
        // Yeah, sure, this is async.  You betcha.  That's why we're going to wait
        // here until the send is complete.
        while (!notifySet)
        {
            sem_wait(&sendSemaphore);
        }
#else
        // Wait 30 seconds until the send is complete or there was an error
        struct timespec timeout_time;
        time_t current_time = time(NULL);

        LOGD2((ZT("HttpClient::StartRequest - Waiting for send semaphore")));
        timeout_time.tv_sec = current_time + 31;   // 30 - 31 seconds, since we don't compute tv_nsec.
        timeout_time.tv_nsec = 0;
        if (sem_timedwait(&sendSemaphore, &timeout_time) < 0)
        {                               // in most cases, errno here will be ETIMEDOUT
            LOGE2((ZT("HttpClient::StartRequest - Error: %d (%s)"), errno, strerror(errno)));
        }
#endif

        if (!_rep->_notify)
        {
            LOGE2((ZT("HttpClient::StartRequest - Timed out")));
            res = httpclient::TIMEOUT;
        }
        else
        {
            res = _rep->_lastStatus;
        }

        _rep->_notify = false;
        pthread_mutex_unlock(&sendLock);
        return res;
    }

    pthread_mutex_unlock(&sendLock);
    return httpclient::OKAY;
}

void HttpClient::SetOperationTimeout(
    int timeoutMS)
{
    _rep->_timeoutMS = timeoutMS;

    NotifyItem* item = new NotifyItem(_rep, timeoutMS);

    if (!_rep->_th->PostItem(item))
    {
        LOGE2((ZT("HttpClient::SetOperationTimeout - PostItem failed")));
    }
}

HTTPCLIENT_END

static void* _proc(void* self)
{
    httpclient::IOThread* pThis = (httpclient::IOThread*)self;
    // keep runnning until terminated
    Selector_Run(&pThis->_selector, TIME_NEVER);

    return 0;
}

static void threadDelegation(void* self, Message* message)
{
    httpclient::IOThread* pThis = (httpclient::IOThread*)self;
    httpclient::NotifyItem* item =(httpclient::NotifyItem*)*((void**)&message->clientID);

    if (item != NULL)
    {
        switch (item->_type)
        {
        case httpclient::NotifyItem::CONNECT:
            pThis->ConnectTh(item);
            delete item;
            // item = NULL;
            break;

        case httpclient::NotifyItem::START_REQUEST:
            pThis->StartRequestTh(item);
            delete item;
            // item = NULL;
            break;

        case httpclient::NotifyItem::DELETE_HTTP:
            pThis->DeleteHttpTh(item);
            delete item->_rep;
            delete item;
            item = NULL;
            break;

        case httpclient::NotifyItem::SET_TIMEOUT:
            pThis->SetTimeoutTh(item);
            delete item;
            // item = NULL;
            break;

        default:
            assert(!"unexpected item type");
            break;
        }
    }
}

static void httpClientCallbackOnStatus(
    ::HttpClient* http,
    void* callbackData,
    MI_Result result)
{
    httpclient::HttpClientRep* rep = (httpclient::HttpClientRep*)callbackData;
    httpclient::Result user_res = httpclient::FAILED;

    LOGD2((ZT("httpClientCallbackOnstatus - Begin. MI result: %d (%s)"), (int)result, mistrerror(result)));
    if (MI_RESULT_OK == result)
    {
        user_res = httpclient::OKAY;
    }
    else if (MI_RESULT_TIME_OUT == result)
    {
        user_res = httpclient::TIMEOUT;
    }
    else if (MI_RESULT_NOT_FOUND == result)
    {
        user_res = httpclient::FAILED;
    }
    else if (MI_RESULT_FAILED == result)
    {
        user_res = httpclient::FAILED;
    }

    if (rep != NULL && rep->_callback != NULL)
    {
        LOGD2((ZT("httpClientCallbackOnStatus - Calling caller's callback. HTTP client status: %d (%s)"), user_res, clientstatusstr(user_res)));
        rep->_callback->OnStatus(user_res);
    }

    rep->_notify = true;
    rep->_lastStatus = user_res;
    LOGD2((ZT("httpClientCallbackOnstatus - Notify was set")));
    notifySet = true;
    sem_post(&sendSemaphore);
}

static MI_Boolean httpClientCallbackOnResponse(
    ::HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean lastChunk,
    Page** data)
{
    httpclient::HttpClientRep* rep = (httpclient::HttpClientRep*)callbackData;
    LOGD2((ZT("httpClientCallbackOnResponse - contentSize: %ld (< 0 means use chunk size), lastChunk: %d"), (unsigned long)contentSize, (int)lastChunk));

    if (headers != NULL)
    {
        std::map< std::string, std::string > user_headers;

        for (MI_Uint32 i = 0; i < headers->sizeHeaders; i++)
        {
            user_headers[headers->headers[i].name] = headers->headers[i].value;
            LOGD2((ZT("httpClientCallbackOnResponse - H: %s --> %s"), headers->headers[i].name, headers->headers[i].value));
        }

        if (headers->httpError < 100 || headers->httpError > 999)
        {
            LOGE2((ZT("httpClientCallbackOnResponse - HTTP status < 100 or > 999 in callback: %d"), headers->httpError));
        }
        LOGD2((ZT("httpClientCallbackOnResponse - Returning %d bytes (< 0 means use chunk size) data. HTTP status: %d"), (int)contentSize, headers->httpError));
        if (!rep->_callback->OnResponseHeader(headers->httpError, user_headers, (int)contentSize))
        {
            LOGE2((ZT("httpClientCallbackOnResponse - Error returning header")));
            return MI_FALSE;
        }
    }

    if (data != NULL && *data != NULL)
    {
        LOGD2((ZT("httpClientCallbackOnResponse - Returning %u bytes data"), (unsigned int)(*data)->u.s.size));
        std::vector< unsigned char > user_data(
            (unsigned char*)(*data + 1), (unsigned char*)(*data + 1) + (*data)->u.s.size);
        if (!rep->_callback->OnResponseData(user_data, lastChunk))
        {
            LOGE2((ZT("httpClientCallbackOnResponse - Error from OnResponseData")));
            return MI_FALSE;
        }
    }

    LOGD2((ZT("httpClientCallbackOnStatusResponse - Returning OK (MI_TRUE)")));
    return MI_TRUE;
}
