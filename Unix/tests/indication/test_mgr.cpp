/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <algorithm>
#include <ut/ut.h>
#include <base/paths.h>
#include <base/log.h>
#include <pal/strings.h>
#include <indication/common/indicommon.h>
#include <indication/indimgr/mgr.h>
#include <omi_error/OMI_Error.h>
#include <omi_error/errorutil.h>
#include "util.h"

using namespace std;

/*
**==============================================================================
**
** Defines structure to control the behavior of StrandSimAgentMgr
** For test indication manager, we need to simulate the behavior of AgentMgr,
** it could,
**
**  (1) Fail inside _UT_HandleRequest
**      - Simulate Fail in AgentMgr_HandleRequest
**  (2) Succeed in _UT_HandleRequest and failed from StrandSimAgentMgr later
**      - Simulate succeed in AgentMgr_HandleRequest and failed in provider
**  (3) Succeed in StrandSimAgentMgr first and failed later
**      - Simulate succeed in provider first and failed later
**  (4) Succeed in StrandSimAgentMgr and get unsubscribed or cancelled
**      - Simulate succeed in provider and get unsubscribed or cancelled
**
**==============================================================================
*/
typedef struct _SimAgentMgrResponse
{
    MI_Result mrHandleRequest;  /* result from _UT_HandleRequest */
    MI_Result mrResponseFirst;  /* first result from StrandSimAgentMgr */
    MI_Result mrResponseSecond; /* second result from StrandSimAgentMgr */
    MI_Uint32 muIndicationMsg;    /* number of indications to send before terminate */
    MI_Uint32 muIndicationMsgSent;    /* number of indications already sent before terminate */
    MI_Uint32 muResponseMsgSent;  /* number of response msg already sent before terminate, 0 or 1 */
    MI_Uint32 muResultMsgSent;    /* number of result msg already sent before terminate, has to be 1 */

    MI_Boolean mbMessagesSent;  /* whether all message sent*/

    MI_Boolean mbOccupied;      /* indicate whether this object was used or not */
                                /* _UT_HandleRequest relies on this field to allocate */
                                /* one object for each StrandSimAgentMgr */
}SimAgentMgrResponse;


/*
**==============================================================================
**
** Release message list
**
**==============================================================================
*/
void MessageList_Release(_In_opt_ Message*head)
{
    Message* msg = head;
    while(msg)
    {
        Message* msgToRelease = msg;
        msg = msg->next;
        Message_Release(msgToRelease);
    }
}

/*
**==============================================================================
**
** Strand structure simulates protocols, verify the behavior of IndicationManager
**
**==============================================================================
*/
typedef struct _StrandProtocol
{
    Strand strand;

    size_t nPost;           /* Number of post call */
    Message* postedMsgList; /* List of posted messages */

    size_t nAck;
    size_t nCancel;
    size_t nFinished;

}StrandProtocol;

/* Reset StrandProtocol object */
void StrandProtocol_Reset(_Inout_ Strand* self) 
{
    StrandProtocol* sp = (StrandProtocol*)self;
    MessageList_Release(sp->postedMsgList);
    sp->postedMsgList = NULL;
    sp->nAck = 0;
    sp->nCancel = 0;
    sp->nFinished = 0;
    sp->nPost = 0;
}

/* Finalize StrandProtocol object */
void StrandProtocol_Finalize(_Inout_ Strand* self) 
{
    StrandProtocol_Reset(self);
}

NITS_EXTERN_C void _StrandProtocol_Post(_In_ Strand* self, _In_ Message* msg)
{
    StrandProtocol* sp = (StrandProtocol*)self;
    trace_StrandProtocol_Post(self, msg, MessageName(msg->tag));

    ++sp->nPost;

    /* Add reference to Message */
    Message_AddRef(msg);

    /* Insert message into list */
    msg->next = sp->postedMsgList;
    sp->postedMsgList = msg;

    /* Ack to indication manager */
    Strand_Ack(self);

    if (msg->tag == PostResultMsgTag)
    {
        /* Final message, close protocol strand */
        Strand_Close(self);
        trace_StrandProtocol_Post_ClosedSelf(self);
    }

    trace_StrandProtocol_Post_Total(self, msg, MessageName(msg->tag), sp->nPost);
}

NITS_EXTERN_C void _StrandProtocol_PostControl(_In_ Strand* self, _In_ Message* msg) 
{
    /* Not used now */
    NitsAssert(PAL_FALSE, PAL_T("_StrandProtocol_PostControl should not be called"));
}

NITS_EXTERN_C void _StrandProtocol_Ack(_In_ Strand* self) 
{
    StrandProtocol* sp = (StrandProtocol*)self;
    ++sp->nAck;

    trace_StrandProtocol_Ack(self, sp->nAck);
}

NITS_EXTERN_C void _StrandProtocol_Cancel(_In_ Strand* self) 
{
    StrandProtocol* sp = (StrandProtocol*)self;
    ++sp->nCancel;

    trace_StrandProtocol_Cancel(self, sp->nCancel);
}

NITS_EXTERN_C void _StrandProtocol_Finished( _In_ Strand* self) 
{
    StrandProtocol* sp = (StrandProtocol*)self;
    ++sp->nFinished;

    trace_StrandProtocol_Finished(self, sp->nFinished);

    /* Leave the finalize/delete after validation */
    /* TestMgr_Subscribe_Unsubscribe_Cancel calls StrandProtocol_Finalize */
    /* to clean up StrandProtocol */
}

StrandFT _StrandProtocolFT1 = { 
        _StrandProtocol_Post,
        _StrandProtocol_PostControl,
        _StrandProtocol_Ack,
        _StrandProtocol_Cancel,
        NULL,
        _StrandProtocol_Finished,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL};

/*
**==============================================================================
**
** Strand structure simulates AgentMgr, verify the behavior of IndicationManager
**
**==============================================================================
*/
typedef struct _StrandSimAgentMgr
{
    Strand strand;
    Message* msg;
    size_t nAck;
    size_t nCancel;
    size_t nFinished;

    /* do not release the object */
    SimAgentMgrResponse* response;

}StrandSimAgentMgr;

/* Reset StrandProtocol object */
void StrandStrandSimAgentMgr_Reset(_Inout_ Strand* self) 
{
    StrandSimAgentMgr* ssa = (StrandSimAgentMgr*)self;
    Message_Release(ssa->msg);
    ssa->msg = NULL;
    ssa->nAck = 0;
    ssa->nCancel = 0;
    ssa->nFinished = 0;
}

/* Finalize StrandProtocol object */
void StrandStrandSimAgentMgr_Finalize(_Inout_ Strand* self) 
{
    StrandStrandSimAgentMgr_Reset(self);
}

NITS_EXTERN_C void _StrandSimAgentMgr_Post(_In_ Strand* self, _In_ Message* msg)
{
    /* Not used now */
    NitsAssert(PAL_FALSE, PAL_T("_StrandSimAgentMgr_Post should not be called"));
}

NITS_EXTERN_C void _StrandSimAgentMgr_PostControl(_In_ Strand* self, _In_ Message* msg) 
{
    /* Not used now */
    NitsAssert(PAL_FALSE, PAL_T("_StrandSimAgentMgr_PostControl should not be called"));
}

NITS_EXTERN_C void _StrandSimAgentMgr_Ack(_In_ Strand* self) 
{
    StrandSimAgentMgr* ssa = (StrandSimAgentMgr*)self;
    ++ssa->nAck;

    trace_StrandSimAgentMgr_Ack(self, ssa->nAck);

    NitsAssert(NULL != ssa->response, PAL_T("Response object should NOT be NULL"));
    if (NULL == ssa->response)
    {
        /* Close self */
        Strand_Close(self);
        trace_StrandSimAgentMgr_AckCloseSelf(self, ssa->nAck);
        return;
    }

    /* Stop posting message if first result is not OK, since first message is the final message */
    if (ssa->response->mrResponseFirst != MI_RESULT_OK)
    {
        trace_StrandSimAgentMgr_AckStopByDesign(self, ssa->nAck);

        /* Last Message Close self */
        Strand_Close(self);
        trace_StrandSimAgentMgr_AckCloseSelf(self, ssa->nAck);
        return;
    }

    /* Stop posting message if all messages were sent */
    if (ssa->response->mbMessagesSent == MI_TRUE)
    {
        trace_StrandSimAgentMgr_AckStopAllSent(self, ssa->nAck);

        /* Last Message Close self */
        Strand_Close(self);
        trace_StrandSimAgentMgr_AckCloseSelf(self, ssa->nAck);
        return;
    }

    if (ssa->response->muIndicationMsgSent < ssa->response->muIndicationMsg)
    {
        /* Post indication message */
        PostIndicationMsg * res = PostIndicationMsg_New(0);
        NitsAssert(NULL != res, PAL_T("Failed to create PostIndicationMsg"));
        if (res)
        {
            /* TODO: to post real instance */
            res->base.instance = (MI_Instance*)(0x12345678);
            res->machineID = PAL_T("LOCALHOST");
            res->bookmark = PAL_T("2013010101:010101:123");
            trace_StrandSimAgentMgr_AckPostIndication(self, &res->base.base);
            Strand_Post(self, &res->base.base);
            Message_Release(&res->base.base);
        }
        ssa->response->muIndicationMsgSent++;
    }
    else if (ssa->response->mrResponseSecond != MI_RESULT_OK)
    {
        /* Post Final Result */
        PostResultMsg * res = PostResultMsg_New(0);
        NitsAssert(NULL != res, PAL_T("Failed to create PostResultMsg"));
        if (res)
        {
            res->result = ssa->response->mrResponseSecond;
            trace_StrandSimAgentMgr_AckPostFinal(self, &res->base);
            Strand_Post(self, &res->base);
            Message_Release(&res->base);
            ssa->response->muResultMsgSent ++;
        }
        ssa->response->mbMessagesSent = MI_TRUE;
    }
    // else if (ssa->response->mrResponseSecond == MI_RESULT_OK)
    // post final result in _StrandSimAgentMgr_Cancel
}

NITS_EXTERN_C void _StrandSimAgentMgr_Cancel(_In_ Strand* self)
{
    StrandSimAgentMgr* ssa = (StrandSimAgentMgr*)self;
    ++ssa->nCancel;

    trace_StrandSimAgentMgr_Cancel(self, ssa->nCancel);

    /* Post Final Result */
    PostResultMsg * res = PostResultMsg_New(0);
    NitsAssert(NULL != res, PAL_T("Failed to create PostResultMsg"));
    if (res)
    {
        res->result = ssa->response->mrResponseSecond;
        trace_StrandSimAgentMgr_CancelFinalMessage(self, &res->base);
        Strand_Post(self, &res->base);
        Message_Release(&res->base);
        ssa->response->muResultMsgSent ++;
    }
    ssa->response->mbMessagesSent = MI_TRUE;
}

NITS_EXTERN_C void _StrandSimAgentMgr_Finished( _In_ Strand* self) 
{
    StrandSimAgentMgr* ssa = (StrandSimAgentMgr*)self;
    ++ssa->nFinished;

    trace_StrandSimAgentMgr_Finished(self, ssa->nFinished);

    /* TestMgr_Subscribe_Unsubscribe_Cancel calls StrandSimAgentMgrList_Finalize */
    /* to clean up all StrandSimAgentMgr(s) */
}

StrandFT _StrandSimAgentMgrFT1 = { 
        _StrandSimAgentMgr_Post,
        _StrandSimAgentMgr_PostControl,
        _StrandSimAgentMgr_Ack,
        _StrandSimAgentMgr_Cancel,
        NULL,
        _StrandSimAgentMgr_Finished,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL};

STRAND_DEBUGNAME(StrandProtocol);
STRAND_DEBUGNAME(StrandSimAgentMgr);

/*
**==============================================================================
**
** Links all StrandSimAgentMgr object created for one test case,
** verification of each test case needs to iterate through all
** objects
**
**==============================================================================
*/
typedef  struct _StrandSimAgentMgrItem StrandSimAgentMgrItem;
struct _StrandSimAgentMgrItem
{
    StrandSimAgentMgr* ssa;
    StrandSimAgentMgrItem* next;
};

typedef struct _StrandSimAgentMgrList
{
    Batch* batch;
    StrandSimAgentMgrItem* head;
}StrandSimAgentMgrList;


/*
**==============================================================================
**
** Defines structure to hold response object and expected results
**
**==============================================================================
*/
typedef struct _ResponseAndExpectedResult
{
    /* Call subscribe or cancel to terminate the subscription */
    MI_Boolean callUnsubscribe;
    MI_Boolean protocolFinishedBeforeUnsubscribe;

    /* Responses from agent mgr */
    _Field_size_(samResponseSize) SimAgentMgrResponse* samResponse;
    MI_Uint32 samResponseSize;

    /* Expected results */
    MI_Uint32 muPostResultMsg;
    MI_Uint32 muPostResponseMsg;
    MI_Result mrFinalResult;
    MI_Uint32 muPostIndicationMsg;
    MI_Uint32 muClassCount; /* number of classes were handled */
    MI_Boolean hasLastErrordetails; /* Has error details instance */
}ResponseAndExpectedResult;

/*
**==============================================================================
**
** Test_IndiMgrStruct contains objects required for running all test cases
** within current file
**
**==============================================================================
*/
struct Test_IndiMgrStruct
{
    /* Properties do NOT need to be cleaned up */
    MI_ConstString query;
    MI_ConstString queryDialect;
    MI_ConstString nameSpace;
    IndicationHost host;
    StringTagElement* ste;
    MI_Uint32 steCount;

    /* Objects requires to be cleaned up */
    IndicationManager* _indimgr;
    Filter* _filter;
    Listener* _listener;
    Subscription* _subscrip;

    /* Objects may need clean up */
    MI_Boolean provregInited;
    ProvReg provreg;
    MI_Uint32 subid;

    /* StrandSimAgentMgr List */
    StrandSimAgentMgrList ssalist;

    /* Response and expected result */
    ResponseAndExpectedResult rar;

    /* Copy of ste */
    StringTagElement* stecopy;
};

int StrandSimAgentMgrList_Initialize(_Out_ StrandSimAgentMgrList* list)
{
    list->head = NULL;
    list->batch = Batch_New(64);
    return (list->batch == NULL) ? -1 : 0;
}

void StrandSimAgentMgrList_Finalize(_Inout_ StrandSimAgentMgrList* list)
{
    StrandSimAgentMgrItem* item = list->head;
    while (item)
    {
        if (item->ssa)
        {
            StrandStrandSimAgentMgr_Finalize(&item->ssa->strand);
            Strand_Delete(&item->ssa->strand);
            item->ssa = NULL;
        }
        item = item->next;
    }
    if (list->batch)
    {
        Batch_Delete(list->batch);
        list->batch = NULL;
    }
}

int StrandSimAgentMgrList_AddItem(_Inout_ StrandSimAgentMgrList* list,
    _In_ StrandSimAgentMgr* ssa)
{
    if (!list->batch)
        return -1;
    StrandSimAgentMgrItem* item = (StrandSimAgentMgrItem*)Batch_Get(
        list->batch, sizeof(StrandSimAgentMgrItem));
    if (!item)
        return -1;
    item->next = list->head;
    item->ssa = ssa;
    list->head = item;
    return 0;
}

MI_EXTERN_C void _UT_HandleRequest_NOOP(
    _In_ void* context,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ const ProvRegEntry* proventry)
{
    MI_UNREFERENCED_PARAMETER(context);
    MI_UNREFERENCED_PARAMETER(interactionParams);
    MI_UNREFERENCED_PARAMETER(proventry);
}

/*
**==============================================================================
**
** Setup function, it is called before running each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
NitsSetup0(TestMgr_Setup, Test_IndiMgrStruct)    

    Test_IndiMgrStruct* tis = NitsContext()->_Test_IndiMgrStruct;
    tis->provregInited = MI_FALSE;
    memset(&tis->provreg, 0, sizeof(ProvReg));
    tis->subid = 0;

    /* Setup the context pointer */
    tis->host.context = (void*)tis;
    IndicationManager* indimgr = IndiMgr_New(&tis->host);
    NitsAssert(indimgr != NULL, PAL_T("Failed to create indication manager"));
    if (indimgr == NULL)
        NitsReturn;
    tis->_indimgr = indimgr;

    Filter* filter = Filter_New(
        tis->query,
        tis->queryDialect,
        NULL);
    NitsAssert( NULL != filter, PAL_T("Failed to create filter"));
    if (NULL == filter)
        NitsReturn;
    tis->_filter = filter;

    Listener* listener = Listener_New(LISTENER_TEMP);
    NitsAssert( NULL != listener, PAL_T("Failed to create listener"));
    if (NULL == listener)
        NitsReturn;
    tis->_listener = listener;

    tis->_subscrip = Subscription_New((FilterBase*)
        tis->_filter,
        tis->_listener);
    NitsAssert( NULL != tis->_subscrip, PAL_T("Failed to create subscription"));

    memset(&tis->rar, 0, sizeof(ResponseAndExpectedResult));

    /* setup stecopy memory */
    if ((NULL != tis->ste) && (tis->steCount > 0))
    {
        tis->stecopy = (StringTagElement*)PAL_Malloc(tis->steCount * sizeof(StringTagElement));
        NitsAssert( NULL != tis->stecopy, PAL_T("Failed to create stecopy"));
    }
NitsEndSetup

/*
**==============================================================================
**
** Cleanup function, it is called after run each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
NitsCleanup(TestMgr_Setup)
    
    Test_IndiMgrStruct* tis = NitsContext()->_Test_IndiMgrStruct;
    if (tis->_indimgr)
    {
        IndiMgr_Shutdown(tis->_indimgr);
        tis->_indimgr = NULL;
    }
    if (tis->_filter)
    {
        Filter_Release(tis->_filter);
        tis->_filter = NULL;
    }
    if (tis->_listener)
    {
        Listener_Release(tis->_listener);
        tis->_listener = NULL;
    }
    if (tis->_subscrip)
    {
        Subscription_Release(tis->_subscrip);
        tis->_subscrip = NULL;
    }
    if (MI_TRUE == tis->provregInited)
    {
        ProvReg_Destroy(&tis->provreg);
        tis->provregInited = MI_FALSE;
        memset(&tis->provreg, 0, sizeof(ProvReg));
    }
    memset(&tis->rar, 0, sizeof(ResponseAndExpectedResult));
    if (tis->stecopy)
    {
        PAL_Free(tis->stecopy);
    }
NitsEndCleanup

MI_EXTERN_C ProvReg* _UT_GetProvReg(_In_ void* context)
{
    Test_IndiMgrStruct* ims = (Test_IndiMgrStruct*)context;
    string root = OMI_GetPath(ID_PREFIX);
    string omiregdir = root + "/tests/provreg/omiregister";
    /* This function might be called >1 times during one unit test fault injection run */
    /* So we need to clean up the provreg object if already initialized */
    if (MI_TRUE == ims->provregInited)
    {
        ProvReg_Destroy(&ims->provreg);
        ims->provregInited = MI_FALSE;
    }
    MI_Result r = ProvReg_Init(&ims->provreg, omiregdir.c_str());
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to initialize ProgReg"));
    ims->provregInited = (r == MI_RESULT_OK) ? MI_TRUE : MI_FALSE;
    return (r == MI_RESULT_OK) ? &ims->provreg : NULL;
}

static struct Test_IndiMgrStruct sTestIM1 = {
    MI_T("select * from CIM_Indication"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication"),
    {
        _UT_GetProvReg,
        _UT_HandleRequest_NOOP,
        NULL,
    },
    NULL,
    0,
    NULL,
    NULL,
    NULL,
    NULL};

NitsTest1(TestMgr_AddRemoveFilter, TestMgr_Setup, sTestIM1)
    NitsFaultSimMarkForRerun;    

    Filter* filter = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_filter;
    IndicationManager* indimgr = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_indimgr;
    int refFilter = Filter_GetRefcount(filter);
    NitsAssert( NULL == filter->base.base.identifier, PAL_T("filter identifier has to be NULL"));

    int r = IndiMgr_AddFilter(indimgr, (FilterBase*)filter);
    NitsAssert( r == 0, PAL_T("failed to add filter to indication manager"));
    if (r == 0)
    {
        NitsAssert( Filter_GetRefcount(filter) == (refFilter+1), PAL_T("filter has wrong ref count"));
        
        int c = Tcsncasecmp(filter->base.base.identifier, TEMP_FILTER_ID_PREFIX, MI_COUNT(TEMP_FILTER_ID_PREFIX)-1);
        NitsAssert( c == 0 , PAL_T("filter has wrong identifier"));

        r = IndiMgr_RemoveFilter(indimgr, (FilterBase*)filter);
        NitsAssert( r == 0 , PAL_T("failed to remove filter from indication manager"));

        NitsAssert( Filter_GetRefcount(filter) == refFilter, PAL_T("filter has wrong ref count"));
    }

NitsEndTest

NitsTest1(TestMgr_AddRemoveListener, TestMgr_Setup, sTestIM1)

    NitsFaultSimMarkForRerun;
    Listener* listener = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_listener;
    IndicationManager* indimgr = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_indimgr;

    int ref = Listener_GetRefcount(listener);

    NitsAssert( NULL == listener->base.identifier, PAL_T("listener identifier has to be NULL"));

    int r = IndiMgr_AddListener(indimgr, listener);
    NitsAssert( r == 0, PAL_T("Failed to add listener to indication manager"));
    if (r == 0)
    {
        NitsAssert(Listener_GetRefcount(listener) == (ref+1), PAL_T("listener has wrong ref count"));

        int c = Tcsncasecmp(listener->base.identifier, TEMP_LISTENER_ID_PREFIX, MI_COUNT(TEMP_LISTENER_ID_PREFIX)-1);
        NitsAssert( c == 0, PAL_T("listener has wrong identifier"));

        r = IndiMgr_RemoveListener(indimgr, listener);
        NitsAssert( r == 0, PAL_T("Failed to remove listener from indication manager"));

        NitsAssert( Listener_GetRefcount(listener) == ref, PAL_T("listener has wrong ref count"));
    }

NitsEndTest

NitsTest1(TestMgr_AddRemoveSubscription, TestMgr_Setup, sTestIM1)
    NitsFaultSimMarkForRerun;
    
    // Disable Nits Fault injection here, because in RegFile_New function (Called internally in ProvReg_Init) will 
    // return NULL in both cases Failure OR failed to allocate. And Nits doesn't like that.
    NitsDisableFaultSim;

    Filter* filter = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_filter;
    Listener* listener = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_listener;
    Subscription* sub = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_subscrip;
    IndicationManager* indimgr = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->_indimgr;
    int ref = Subscription_GetRefcount(sub);
    int refFilter = Filter_GetRefcount(filter);
    int refListener = Listener_GetRefcount(listener);

    {
        MI_StringA nsa;
        MI_Char* ns;
        nsa.size = 1;
        ns = (MI_Char*)NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct->nameSpace;
        nsa.data = &ns;
        if (Filter_SetNamespace(filter, &nsa) != 0)
        {
            NitsAssert(0, PAL_T("Set namespace failed"));
            NitsReturn;
        }
    }

    NitsAssert( NULL == sub->base.identifier, PAL_T("Subscription identifier has to be NULL"));
    sub->subscriptionID = 1;
    int r = IndiMgr_AddSubscription(indimgr, sub);
    NitsAssert( r == 0, PAL_T("Failed to add subscription to indication manager"));
    if (r == 0)
    {
        NitsAssert( Subscription_GetRefcount(sub) == (ref+1), PAL_T("Subscription object has wrong ref count"));
        NitsAssert( Filter_GetRefcount(filter) == (refFilter+1), PAL_T("filter object has wrong ref count"));
        NitsAssert( Listener_GetRefcount(listener) == (refListener+1), PAL_T("listener object has wrong ref count"));

        int c = Tcsncasecmp(sub->base.identifier, TEMP_SUBSCRIPTION_ID_PREFIX, MI_COUNT(TEMP_SUBSCRIPTION_ID_PREFIX)-1);
        NitsAssert( c == 0, PAL_T("subscription object has wrong identifier"));

        r = IndiMgr_RemoveSubscription(indimgr, sub);
        NitsAssert( r == 0, PAL_T("Failed to remove subscription from indication manager"));

        NitsAssert( Subscription_GetRefcount(sub) == ref, PAL_T("subscription object has wrong ref count"));
        NitsAssert( Filter_GetRefcount(filter) == refFilter, PAL_T("filter object has wrong ref count"));
        NitsAssert( Listener_GetRefcount(listener) == refListener, PAL_T("listener object has wrong ref count"));
    }

NitsEndTest


MI_EXTERN_C void _UT_HandleRequest(
    _In_ void* context,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ const ProvRegEntry* proventry)
{
    trace_UT_HandleRequest(context, interactionParams->msg, MessageName(interactionParams->msg->tag), interactionParams->interaction);

    Test_IndiMgrStruct* tts = (Test_IndiMgrStruct*)context;
    SimAgentMgrResponse* response = NULL;

    /* Find response object */
    MI_Uint32 i = 0;
    for (; i < tts->rar.samResponseSize; i ++)
    {
        if (tts->rar.samResponse[i].mbOccupied == MI_FALSE)
        {
            tts->rar.samResponse[i].mbOccupied = MI_TRUE;
            response = &tts->rar.samResponse[i];
            break;
        }
    }
    if ( i == tts->rar.samResponseSize)
    {
        NitsAssert(false, PAL_T("Failed to find response object for StrandSimAgentMgr"));
        Strand_FailOpen(interactionParams);
        return;
    }

    /* Return error code if handle request failed */
    if (response->mrHandleRequest != MI_RESULT_OK)
    {
        /* Terminate the operation if failed in HandleRequest */
        trace_UT_HandleRequestFailed(
            context, interactionParams->msg, MessageName(interactionParams->msg->tag), interactionParams->interaction, response->mrHandleRequest);
        Strand_FailOpenWithResult(interactionParams,response->mrHandleRequest, PostResultMsg_NewAndSerialize);
        return;
    }

    /* Handle subscribe request */
    StrandSimAgentMgr* ssa = (StrandSimAgentMgr*)Strand_New(
            STRAND_DEBUG(StrandSimAgentMgr)
            &_StrandSimAgentMgrFT1,
            sizeof(StrandSimAgentMgr),
            0,
            interactionParams);
    NitsAssert( NULL != ssa, PAL_T("Failed to create StrandSimAgentMgr"));
    if (NULL == ssa)
    {
        Strand_FailOpenWithResult(interactionParams,MI_RESULT_SERVER_LIMITS_EXCEEDED, PostResultMsg_NewAndSerialize);
        return;
    }

    /* Attach response */
    ssa->response = response;

    /* Add agentmgr to list */
    int r = StrandSimAgentMgrList_AddItem(&tts->ssalist, ssa);
    NitsAssert(r == 0, PAL_T("_UT_HandleRequest: Add StrandSimAgentMgr to list failed"));

    /* Attach message */
    Message_AddRef(interactionParams->msg);
    ssa->msg = interactionParams->msg;

    /* Ack to indication that this Strand opened */
    Strand_ScheduleAck(&ssa->strand);

    switch(interactionParams->msg->tag)
    {
    case SubscribeReqTag:
        /* Post result message based on response object */
        {
            if (ssa->response->mrResponseFirst != MI_RESULT_OK)
            {
                PostResultMsg * res = PostResultMsg_New(interactionParams->msg->operationId);
                NitsAssert(NULL != res, PAL_T("Failed to create PostResultMsg message"));
                if (!res)
                {
                    Strand_FailOpenWithResult(interactionParams,MI_RESULT_SERVER_LIMITS_EXCEEDED, PostResultMsg_NewAndSerialize);
                    return;
                }

                res->result = ssa->response->mrResponseFirst;
                ssa->response->muResultMsgSent ++;
                Strand_SchedulePost(&ssa->strand, &res->base);
                Message_Release(&res->base);
            }
            else
            {
                SubscribeRes * res = SubscribeRes_New(interactionParams->msg->operationId);
                NitsAssert(NULL != res, PAL_T("Failed to create PostResultMsg message"));
                if (!res)
                {
                    Strand_FailOpenWithResult(interactionParams,MI_RESULT_SERVER_LIMITS_EXCEEDED, PostResultMsg_NewAndSerialize);
                    return;
                }
                ssa->response->muResponseMsgSent ++;
                Strand_SchedulePost(&ssa->strand, &res->base);
                Message_Release(&res->base);
            }
        }
        break;
    default:
        NitsAssert(PAL_FALSE, PAL_T("_UT_HandleRequest: Unrecognized message"));
        Strand_FailOpenWithResult(interactionParams,MI_RESULT_FAILED, PostResultMsg_NewAndSerialize);
        return;
    }
}

/*
**==============================================================================
** Target indication classes list referred by following test cases
**==============================================================================
*/
const MI_Uint32 cClassCount = 5;
static StringTagElement _IndicationClassList[cClassCount] =
{
    { MI_T("XYZ_Indication"),0 , (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("XYZ_ChildIndication1"),0 , (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("XYZ_ChildIndication2"),0 , (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("XYZ_ChildIndication3"),0 , (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("XYZ_ChildIndication4"),0 , (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
};


static struct Test_IndiMgrStruct sTestIM2 = {
    MI_T("select * from CIM_Indication"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication"),
    {
        _UT_GetProvReg,
        _UT_HandleRequest,
        NULL,
    },
    _IndicationClassList,
    cClassCount,
    NULL,
    NULL,
    NULL,
    NULL};

/*
**==============================================================================
**
** Helper functions to validate indication manager can handle subscribe request,
** unsubscribe request and cancel operation correctly;
**
**==============================================================================
*/
void TestMgr_Subscribe_Unsubscribe_Cancel(_In_ Test_IndiMgrStruct* tts)
{
    /*Log_OpenStdErr();
    Log_SetLevel(LOG_VERBOSE);*/

    StrandProtocol* sp = (StrandProtocol*)Strand_New(
        STRAND_DEBUG(StrandProtocol)
        &_StrandProtocolFT1,
        sizeof(StrandProtocol),
        STRAND_FLAG_ENTERSTRAND,
        NULL);

    NitsAssert( NULL != sp, PAL_T("Failed to create StrandProtocol"));
    if (NULL == sp)
        return;

    IndicationManager* indimgr = tts->_indimgr;
    const MI_Uint64 subscriptionID = ++(tts->subid);
    MI_ConstString ns = tts->nameSpace;
    MI_ConstString cn = NULL;
    MI_ConstString qry = tts->query;
    MI_ConstString lang = tts->queryDialect;

    /* Copy _IndicationClassList to classlist */
    memcpy(tts->stecopy, tts->ste, tts->steCount * sizeof(StringTagElement));

    int ssalisInited = StrandSimAgentMgrList_Initialize(&tts->ssalist);
    NitsAssert(0 == ssalisInited, PAL_T("Failed to StrandSimAgentMgrList_Initialize"));
    if (0 != ssalisInited)
    {
        Strand_Leave( &sp->strand );
        goto Done;
    }
    
    /* Post subscribe message to indication manager*/
    {
        SubscribeReq* msg = SubscribeReq_New(0, 0);
        NitsAssert(NULL != msg, PAL_T("Failed to create SubscribeReq message"));
        if (!msg)
        {
            Strand_Leave( &sp->strand );
            goto Done;
        }

        msg->nameSpace = ns;
        msg->filter = qry;
        msg->language = lang;
        msg->className = cn; /* Optional for indication manager */
        msg->targetType = (MI_Uint32)SUBSCRIP_TARGET_DEFAULT;  /* Optional for indication manager */
        msg->subscriptionID = subscriptionID;

        Strand_Open(&sp->strand,IndiMgr_HandleSubscribeReq,indimgr,&msg->base.base,MI_TRUE);
        Message_Release(&msg->base.base);
    }

    if (MI_FALSE == tts->rar.protocolFinishedBeforeUnsubscribe)
    {
        /* Post unsubscribe request */
        if (tts->rar.callUnsubscribe == MI_TRUE)
        {
            trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe();

            UnsubscribeReq* msg = UnsubscribeReq_New(0, 0);
            NitsAssert(NULL != msg, PAL_T("Failed to create SubscribeReq message"));
            if (!msg)
                goto Done;

            Strand_SchedulePost(&sp->strand, &msg->base.base);
            Message_Release(&msg->base.base);
        }
        /* Cancel the subscription */
        else
        {
            trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel();

            Strand_ScheduleCancel(&sp->strand);
        }
    }

    /* Verify protocol side has correct state */
    {
        /* Verify protocol state */
        NitsCompare(1, sp->nFinished,  PAL_T("Expect protocol was closed/finished"));

        /* Verify messages sent by indication manager */
        {
            MI_Uint32 nMsgCount = tts->rar.muPostResultMsg + tts->rar.muPostResponseMsg + tts->rar.muPostIndicationMsg;
            NitsCompare(nMsgCount, sp->nPost, PAL_T("StrandProtocol received wrong number of messages"));
            NitsAssert(NULL != sp->postedMsgList, PAL_T("StrandProtocol got no messages"));

            Message* msg = sp->postedMsgList;
            MI_Uint32 resultMsgCount = 0;
            MI_Uint32 responseMsgCount = 0;
            MI_Uint32 indMsgCount = 0;
            MI_Result finalResult = MI_RESULT_FAILED;
            while (msg)
            {
                switch (msg->tag)
                {
                case PostResultMsgTag:
                    {
                        NitsAssert(resultMsgCount == 0, PAL_T("StrandProtocol got more than 1 result message"));
                        resultMsgCount++;
                        if (resultMsgCount == 1)
                        {
                            /* Final result is the first one in the list */
                            finalResult = ((PostResultMsg*)msg)->result;
                        }
                    }
                    break;

                case SubscribeResTag:
                    {
                        NitsAssert(responseMsgCount == 0, PAL_T("StrandProtocol got more than 1 response message"));
                        responseMsgCount++;
                    }
                    break;    

                case PostIndicationMsgTag:
                    {
                        indMsgCount++;
                    }
                    break;

                default:
                    NitsAssert(0, PAL_T("StrandProtocol got unexpected message"));
                    break;
                }
                msg = msg->next;
            }
            NitsCompare(tts->rar.muPostResultMsg, resultMsgCount, PAL_T("StrandProtocol received unexpected number of PostResultMsg"));
            NitsCompare(tts->rar.muPostResponseMsg, responseMsgCount, PAL_T("StrandProtocol received unexpected number of PostResponseMsg"));
            NitsCompare(tts->rar.muPostIndicationMsg, indMsgCount, PAL_T("StrandProtocol received unexpected number of indication messages"));
            NitsCompare(tts->rar.mrFinalResult, finalResult, PAL_T("StrandProtocol received unexpected final result value"));
        }
        /* Cleanup protocol */
        StrandProtocol_Reset(&sp->strand);
    }

    /* Verify agentmgr side has correct state */
    {
        StrandSimAgentMgrItem* item = tts->ssalist.head;
        MI_Uint32 itemCount = 0;
        while(item)
        {
            /* Verify subscribeReq message received by agentmgr */
            NitsAssert(NULL != item->ssa->msg, PAL_T("AgentMgr should received SubscribeReq message"));
            if (NULL != item->ssa->msg)
            {
                NitsCompare(SubscribeReqTag, item->ssa->msg->tag, PAL_T("AgentMgr should received SubscribeReq message"));
                StringTagElement* e = IsInArrayEx(((SubscribeReq*)item->ssa->msg)->className, tts->stecopy, tts->steCount);
                NitsCompare(1, e->tag, PAL_T("Unexpected class count found"));
                if (SubscribeReqTag == item->ssa->msg->tag)
                {
                    SubscribeReq* req = (SubscribeReq*)item->ssa->msg;
                    NitsCompare(req->targetType, e->reserved1, PAL_T("Unexpected target type"));
                }
            }

            /* Verify cancel/finish call to agentmgr */
            MI_Uint32 nCancelCount = 0;
            MI_Uint32 nFinishCount = 1;
            if ((item->ssa->response->mrResponseFirst == MI_RESULT_OK) &&
                (item->ssa->response->mrResponseSecond == MI_RESULT_OK))
            {
                /* agent item get cancelled call if and only if still subscribed */
                /* agent item will be closed if failed already */
                nCancelCount = 1;
            }
            NitsCompare(nCancelCount, item->ssa->nCancel,  PAL_T("expect agentmgrItem get cancel called once"));
            NitsCompare(nFinishCount, item->ssa->nFinished,  PAL_T("expect each agentmgrItem get finish called once"));

            /* Verify message acked correctly by indication mgr */
            MI_Uint32 nMsgCount = item->ssa->response->muIndicationMsgSent +
                item->ssa->response->muResponseMsgSent +
                item->ssa->response->muResultMsgSent;
            NitsCompare(nMsgCount, item->ssa->nAck,  PAL_T("wrong number of Ack called on agentmgrItem"));
            item = item->next;
            itemCount ++;
        }
        NitsCompare(tts->rar.muClassCount, itemCount, PAL_T("AgentMgr received wrong number of request"));
    }

Done:
    if (sp)
    {
        trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule(sp);
        /* Finalize StrandProtocol */
        StrandProtocol_Finalize(&sp->strand);
        Strand_Delete(&sp->strand);
    }
    if (0 == ssalisInited)
    {
        trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers();
        StrandSimAgentMgrList_Finalize(&tts->ssalist);
    }
}


/*
**==============================================================================
**
** For following tests, each test case needs to run twice w.r.t. the
** termination of the subscription; one by calling unsubscribe, another
** by calling cancel;
**
** To avoid the duplicate test code, Unsubscribe structure was introduced to
** indicate the way of terminating the subscribe operation
**
**==============================================================================
*/
struct Unsubscribe_Struct
{
    MI_Boolean shouldUnsubscribe;
};

NitsSetup1(Subscription_Unsubscibe, Unsubscribe_Struct, TestMgr_Setup, sTestIM2)
    NitsContext()->_Unsubscribe_Struct->shouldUnsubscribe = MI_TRUE;
NitsEndSetup

NitsSetup1(Subscription_Cancel, Unsubscribe_Struct, TestMgr_Setup, sTestIM2)
    NitsContext()->_Unsubscribe_Struct->shouldUnsubscribe = MI_FALSE;
NitsEndSetup

NitsSplit2(Subscription_UnsubCancel, Unsubscribe_Struct, Subscription_Unsubscibe, Subscription_Cancel)
NitsEndSplit

/*
**==============================================================================
**
** Validate subscribe request handled successfully with all classes succeeded
** and Unsubscribe request can be handled correctly afterwards
**
**==============================================================================
*/
NitsTest1(TestMgr_SubscribeAllSuccess_Unsubscribe, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;

    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 5;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest


/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  2. X response success and Y failed later (1<Y<X)
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_AllSuccess_SomeFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)        
    NitsFaultSimMarkForRerun;    
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK, MI_RESULT_CANCELED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK, MI_RESULT_CANCELED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 7;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  3. X response success and X failed later
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_AllSuccess_AllFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK, MI_RESULT_CANCELED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK, MI_RESULT_CANCELED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 7;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  4. M response success (2<M<X)
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_SomeSuccess, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 5;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  5. M response success and N failed later (1<N<M<X)
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_SomeSuccess_SomeFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 5;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  6. M response success and M failed later (2<M<X)
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_SomeSuccess_AllFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK, MI_RESULT_CANCELED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 5;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  7. 1 response success
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_OneSuccess, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsDisableFaultSim;
    NitsFaultSimMarkForRerun;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 2;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  8. 1 response success and 1 failed later
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_OneSuccess_FailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 2;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  9. X response failed
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Response_AllFailed, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_CANCELED, MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 0;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 0;
    tts->rar.muClassCount = cClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  10. M handled success; M succeeded from provider;
**      1<M<X
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_SomeSuccess_Response_AllSuccess, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 4;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = 3;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  11. M handled success; N succeeded from provider;
**      1<N<M<X
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_SomeSuccess_Response_SomeSuccess, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 2;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = 3;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  12. M handled success; N succeeded from provider; And P failed later
**      1<=P<N<M<X
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_SomeSuccess_Response_SomeSuccess_SomeFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 2;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = 3;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  13. M handled success; N succeeded from provider; And N failed later
**      1<<N<M<X
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_SomeSuccess_Response_SomeSuccess_AllFailedLater, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,   MI_RESULT_FAILED, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 2;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = 3;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  14. M handled success; M failed from provider;
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_SomeSuccess_Response_AllFailed, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_FAILED,   MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 0;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 0;
    tts->rar.muClassCount = 3;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
**  Following test case is designed to test the handling of subscribe responses
**  from provider; Say subscription is targeted to X classes, following are
**  all of the possible typical scenarios of Subscribe Responses,
**
**  15. X handled failed
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleSubscribe_Handle_AllFailed, Subscription_UnsubCancel, Subscription_UnsubCancelDefaults)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 2,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_FAILED,  MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_Subscription_UnsubCancel->_Subscription_Unsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_Subscription_UnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_FAILED;
    tts->rar.muPostIndicationMsg = 0;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 0;
    tts->rar.muClassCount = 0;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
** Lifecycle Indication Tests
**
**==============================================================================
*/
/*
**==============================================================================
** Target lifecycle indication classes list referred by following test cases
**==============================================================================
*/
static StringTagElement _LifecycleIndicationClassList[] =
{
    { MI_T("TEST_ProcessCreated"), 0, (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("TEST_ProcessTerminated"),0, (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("MSFT_Person"),0, (MI_Uint32)SUBSCRIP_TARGET_LIFECYCLE_ALL},
    { MI_T("MSFT_Person2"),0, (MI_Uint32)SUBSCRIP_TARGET_LIFECYCLE_ALL},
};
const MI_Uint32 cLCIndicationClassCount = MI_COUNT(_LifecycleIndicationClassList);
static struct Test_IndiMgrStruct sTestIM3 = {
    MI_T("select * from CIM_InstIndication where SourceInstance isa MSFT_Base"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication2"),
    {
        _UT_GetProvReg,
        _UT_HandleRequest,
        NULL,
    },
    _LifecycleIndicationClassList,
    cLCIndicationClassCount,
    NULL,
    NULL,
    NULL,
    NULL};

NitsSetup1(LCIndicationUnsubscibe, Unsubscribe_Struct, TestMgr_Setup, sTestIM3)
    NitsContext()->_Unsubscribe_Struct->shouldUnsubscribe = MI_TRUE;
NitsEndSetup

NitsSetup1(LCIndicationCancel, Unsubscribe_Struct, TestMgr_Setup, sTestIM3)
    NitsContext()->_Unsubscribe_Struct->shouldUnsubscribe = MI_FALSE;
NitsEndSetup

NitsSplit2(LCIndicationUnsubCancel, Unsubscribe_Struct, LCIndicationUnsubscibe, LCIndicationCancel)
NitsEndSplit

/*
**==============================================================================
**
** Validate subscribe request handled successfully with all classes succeeded
** and Unsubscribe request can be handled correctly afterwards
**
**==============================================================================
*/
NitsTest1(TestMgr_HandleIndicationResult_LifecycleIndication_Success, LCIndicationUnsubCancel, LCIndicationUnsubCancelDefaults)
    NitsDisableFaultSim;
    NitsFaultSimMarkForRerun;

    SimAgentMgrResponse responses[cLCIndicationClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_LCIndicationUnsubCancel->_LCIndicationUnsubscibe->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cLCIndicationClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = NitsContext()->_LCIndicationUnsubCancel->_Unsubscribe_Struct->shouldUnsubscribe;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = 4;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cLCIndicationClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest


/*
**==============================================================================
**
** Validate subscribe request handled successfully for InstDeletion class
**
**==============================================================================
*/
static StringTagElement _InstDeletionClassList[] =
{
    { MI_T("TEST_ProcessTerminated"),0, (MI_Uint32)SUBSCRIP_TARGET_DEFAULT},
    { MI_T("MSFT_Person"),0, (MI_Uint32)SUBSCRIP_TARGET_LIFECYCLE_DELETE},
    { MI_T("MSFT_Person2"),0, (MI_Uint32)SUBSCRIP_TARGET_LIFECYCLE_DELETE},
};
const MI_Uint32 cInstDeletionClassCount = MI_COUNT(_InstDeletionClassList);
static struct Test_IndiMgrStruct sTestIM4 = {
    MI_T("select * from CIM_InstDeletion where (SourceInstance isa MSFT_Animal)"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication2"),
    {
        _UT_GetProvReg,
        _UT_HandleRequest,
        NULL,
    },
    _InstDeletionClassList,
    cInstDeletionClassCount,
    NULL,
    NULL,
    NULL,
    NULL};
NitsTest1(TestMgr_HandleIndicationResult_LifecycleIndication_Success_InstDeletion, TestMgr_Setup, sTestIM4)
    NitsFaultSimMarkForRerun;
    NitsDisableFaultSim;
    SimAgentMgrResponse responses[cInstDeletionClassCount] = {
    /*Hdl Req Res       Resp First          Resp Second   nIndi IndSent ResSent AllSent     Occupied*/
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},
    {MI_RESULT_OK,      MI_RESULT_OK,       MI_RESULT_OK, 1,    0,      0,      MI_FALSE,   MI_FALSE},};

    Test_IndiMgrStruct* tts = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = cInstDeletionClassCount;
    tts->rar.samResponse = responses;
    tts->rar.callUnsubscribe = MI_TRUE;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_FALSE;
    tts->rar.mrFinalResult = MI_RESULT_OK;
    tts->rar.muPostIndicationMsg = cInstDeletionClassCount;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 1;
    tts->rar.muClassCount = cInstDeletionClassCount;
    tts->rar.hasLastErrordetails = MI_FALSE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest

/*
**==============================================================================
**
** Validate subscribe request handled successfully for a given NOT-supported query
** NOTE: Neither indication classe nor normal class will be discovered for this
** query
**
**==============================================================================
*/
static struct Test_IndiMgrStruct sTestIM5 = {
    MI_T("select * from CIM_InstRead where (SourceInstance isa MSFT_Base) OR (2 > 1)"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication2"),
    {
        _UT_GetProvReg,
        _UT_HandleRequest,
        NULL,
    },
    _LifecycleIndicationClassList,
    cLCIndicationClassCount,
    NULL,
    NULL,
    NULL,
    NULL};
NitsTest1(TestMgr_HandleIndicationResult_LifecycleIndication_InvalidQuery, TestMgr_Setup, sTestIM5)
    NitsFaultSimMarkForRerun;

    // Disable Nits Fault injection here, because in RegFile_New function (Called internally in ProvReg_Init) will 
    // return NULL in both cases Failure OR failed to allocate. And Nits doesn't like that.
    NitsDisableFaultSim;

    Test_IndiMgrStruct* tts = NitsContext()->_TestMgr_Setup->_Test_IndiMgrStruct;
    tts->rar.samResponseSize = 0;
    tts->rar.samResponse = NULL;
    tts->rar.callUnsubscribe = MI_TRUE;
    tts->rar.protocolFinishedBeforeUnsubscribe = MI_TRUE;
    tts->rar.mrFinalResult = MI_RESULT_NOT_SUPPORTED;
    tts->rar.muPostIndicationMsg = 0;
    tts->rar.muPostResultMsg = 1;
    tts->rar.muPostResponseMsg = 0;
    tts->rar.muClassCount = 0;
    tts->rar.hasLastErrordetails = MI_TRUE;
    TestMgr_Subscribe_Unsubscribe_Cancel(tts);

NitsEndTest
