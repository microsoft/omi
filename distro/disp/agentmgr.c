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

#include <base/strings.h>
#include <base/messages.h>
#include <base/log.h>
#include <base/strings.h>
#include <base/paths.h>
#include <io/io.h>
#include <protocol/protocol.h>
#include "agentmgr.h"

#if defined(CONFIG_POSIX)
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/wait.h>
#endif

/*
**==============================================================================
**
** Data structures
**
**==============================================================================
*/

#if defined(CONFIG_POSIX)

typedef struct _RequestItem RequestItem;
/*
    RequestItem - stores information about request sent to the agent/provider;
    this item stores original request's msgID (has to be substituted) and request pointer
    In case of agent disconnection, agent-mgr uses this list to send error responses to 
    outstanding requests.
*/
struct _RequestItem
{
    /* Linked-list support */
    RequestItem* next;
    RequestItem* prev;

    Message* request;
    MI_Uint64 originalMsgID;
};

/*
    AgentElem - stores information about single running agent
*/
struct _AgentElem
{
    /* Linked-list support */
    AgentElem* next;
    AgentElem* prev;

    /* outstanding requests */
    RequestItem* headRequests;
    RequestItem* tailRequests;

    /* hosting context */
    uid_t uid;
    gid_t gid;

    /* connection to the agent */
    Protocol*   protocol;

    /* link to manager */
    AgentMgr*   agentMgr;

    /* agent process pid */
    pid_t       agentPID;
};

/*
**==============================================================================
**
** Local functions
**
**==============================================================================
*/
static AgentElem* _FindAgent(
    AgentMgr* self,
    uid_t uid,
    gid_t gid)
{
    AgentElem* agent;

    agent = self->headAgents;

    while (agent)
    {
        if (uid == agent->uid && gid == agent->gid)
            return agent;

        agent = agent->next;
    }
    return 0;
}

static pid_t _SpawnAgentProcess(
    Sock s,
    int logfd,
    uid_t uid,
    gid_t gid,
    const char* provDir,
    MI_Uint32 idletimeout)
{
    pid_t child;
    int fdLimit;
    int fd;
    char param_sock[32];
    char param_logfd[32];
    char param_idletimeout[32];

    child = fork();

    if (child < 0)
        return -1;  /* Failed */

    if (child > 0)
        return child;   /* Started */

    /* We are in child process here */

    /* switch user */
    if (0 != SetUser(uid,gid))
    {
        _exit(1);
    }

    /* Close all open file descriptors except provided socket
     (Some systems have UNLIMITED of 2^64; limit to something reasonable) */

    fdLimit = getdtablesize();
    if (fdLimit > 2500 || fdLimit < 0)
    {
        fdLimit = 2500;
    }

    /* ATTN: close first 3 also! Left for debugging only */
    for (fd = 3; fd < fdLimit; ++fd)
    {
        if (fd != s && fd != logfd)
            close(fd);
    }

    /* prepare parameter:
        socket fd to attach */
    Snprintf(param_sock, sizeof(param_sock), "%d", (int)s);
    Snprintf(param_logfd, sizeof(param_logfd), "%d", (int)logfd);
    Snprintf(param_idletimeout, sizeof(param_idletimeout), "%d", (int)idletimeout);

    execl(GetPath(ID_AGENTPROGRAM), 
        GetPath(ID_AGENTPROGRAM), 
        param_sock,
        param_logfd,
        "--destdir",
        GetPath(ID_DESTDIR),
        "--providerdir",
        provDir,
        "--idletimeout",
        param_idletimeout,
        "--loglevel",
        Log_GetLevelString(Log_GetLevel()),
        NULL);

    LOGW((MI_T("agent launching: failed to exec %s, errno %d\n"), 
        scs(GetPath(ID_AGENTPROGRAM)),
        errno));
    _exit(1); 
    return -1;  /* never get here */
}

static void _SendErrorResponse(
    RequestItem* requestItem,
    MI_Result r)
{
    PostResultMsg* resp;

    resp = PostResultMsg_New( requestItem->originalMsgID );

    if (!resp)
        return;

    requestItem->request->msgID = requestItem->originalMsgID;
    resp->base.clientID = requestItem->request->clientID;

    resp->result = r;
    Message_SetRequest(&resp->base,requestItem->request);
    (*requestItem->request->callback)(&resp->base, requestItem->request->callbackData);

    PostResultMsg_Release(resp);
}

static void _FreeItem(
    AgentElem*agent)
{
    /* send error repsonses to all outstanding requests */
    while (agent->headRequests)
    {
        RequestItem* requestItem = agent->headRequests;

        _SendErrorResponse(requestItem, MI_RESULT_FAILED);

        /* free item from list */
        List_Remove(
            (ListElem**)&agent->headRequests, 
            (ListElem**)&agent->tailRequests, 
            (ListElem*)requestItem);

        /* Note:
            request item was allocated form message's batch so no need to free it directly;
            Message's release may free batch and invalidate requestItem */
        Message_Release(requestItem->request);
    }

    if (agent->protocol)
        Protocol_Delete(agent->protocol);

    /* SIGCHILD HANDLER will take care of pid waiting */
    /*if (agent->agentPID > 0)
    {
        int loc = 0;
        pid_t p = waitpid(agent->agentPID, &loc, WNOHANG);

        LOGI_CHAR(("waitpid returned %d, loc %d",(int)p, loc));

        if (p != agent->agentPID)
        {
            kill(agent->agentPID, SIGKILL);
            p = waitpid(agent->agentPID, &loc, WNOHANG);

            LOGW_CHAR(("sent KILL; waitpid returned %d, loc %d",(int)p, loc));
        }
    }*/

    free(agent);
}

static void _EventCallback(
    Protocol* protocol,
    ProtocolEvent event,
    void* data)
{
    AgentElem* agent = (AgentElem*)data;

    MI_UNUSED(protocol);
    MI_UNUSED(event);

    DEBUG_ASSERT(PROTOCOLEVENT_DISCONNECT == event);

    LOGW((ZT("lost connection to agent running as [%d]"), (int)agent->uid));
    /* lost connection to the agent:
        - send error repsonses to all outstanding requests ( within 'FreeItem' call)
        - remove agent form the list
    */

    /* remove agent from Mgr's list */
    List_Remove(
        (ListElem**)&agent->agentMgr->headAgents, 
        (ListElem**)&agent->agentMgr->tailAgents, 
        (ListElem*)agent);

    _FreeItem(agent);
}

static MI_Boolean _RequestCallback(
    Protocol* protocol_,
    Message* msg,
    void* data)
{
    AgentElem* self = (AgentElem*)data;
    RequestItem* requestItem;

    MI_UNUSED(protocol_);

    /* ATTN: verify unload message */
    if (BinProtocolNotificationTag == msg->tag)
    {
        BinProtocolNotification* notification = (BinProtocolNotification*)msg;
        if (BinNotificationAgentIdle == notification->type)
        {
            /* Check if this agnet has outstanding requests -
                if agent is idle, return false form callback 
                to close connection to it.
                It will forces protocl to close conneciton and send
                'disconnect' event to event-callback
                */
            if (self->headRequests)
                return MI_TRUE;
            else
                return MI_FALSE;
        }
        /* ignore service messages */
        return MI_TRUE;
    }


    /* get/verify request-item */
    requestItem = (RequestItem*)Uint64ToPtr(msg->msgID);

    /* ATTN: add verification if element is in list to prevent incorect pointer attack */
    {
        RequestItem* cur = self->headRequests;

        while (cur)
        {
            if (cur == requestItem)
                break;

            cur = cur->next;
        }

        if (cur != requestItem)
        {
            LOGE((ZT("cannot find request item %p; agent for user %d!\n"), requestItem, (int)self->uid));
            return MI_FALSE;
        }
    }

    /* restore msgID */
    requestItem->request->msgID = requestItem->originalMsgID;
    msg->msgID = requestItem->originalMsgID;
    msg->clientID = requestItem->request->clientID;

    /* Attach request and post repsonse */
    Message_SetRequest(msg,requestItem->request);
    (*requestItem->request->callback)(msg, requestItem->request->callbackData);

    /* remove item if result received */
    if (msg->tag == PostResultMsgTag)
    {
        List_Remove(
            (ListElem**)&self->headRequests, 
            (ListElem**)&self->tailRequests, 
            (ListElem*)requestItem);

        /* Note:
            request item was allocated form message's batch so no need to free it directly;
            Message's release may free batch and invalidate requestItem */
        Message_Release(requestItem->request);
    }

    return MI_TRUE;
}

static AgentElem* _CreateAgent(
    AgentMgr* self,
    uid_t uid,
    gid_t gid)
{
    AgentElem* agent = 0;
    Sock s[2];
    int logfd = -1;


    /* create communication pipe */
    if(0 != socketpair(AF_UNIX, SOCK_STREAM, 0, s))
    {
        LOGW((ZT("socketpair() failed\n")));
        return 0;
    }

    if (MI_RESULT_OK != Sock_SetBlocking(s[0], MI_FALSE) ||
        MI_RESULT_OK != Sock_SetBlocking(s[1], MI_FALSE))
    {
        LOGW((ZT("set non-blocking failed\n")));
        goto failed;
    }

    /* create/open log file for agent */
    {
        char path[MAX_PATH_SIZE];

        if (0 != FormatLogFileName(uid, gid, path))
        {
            LOGW((ZT("cannot format log file name\n")));
            goto failed;
        }

        /* Create/open fiel with permisisons 644 */
        logfd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
        if (logfd == -1)
        {
            LOGW((ZT("failed to create log file %s; errno %d"), 
                scs(path), (int)errno));
            goto failed;
        }
    }

    agent = (AgentElem*)calloc(1, sizeof(*agent));

    if (!agent)
        goto failed;

    agent->agentMgr = self;
    agent->uid = uid;
    agent->gid = gid;

    if ((agent->agentPID = 
        _SpawnAgentProcess(
            s[0], 
            logfd, 
            uid, 
            gid, 
            self->provDir, 
            (MI_Uint32)(self->provmgr.idleTimeoutUsec / 1000000))) < 0)
    {
        LOGW((ZT("cannot spawn a child process\n")));
        goto failed;
    }

    close(logfd);
    logfd = -1;

    /* Close socket 0 - it will be used by child process */
    Sock_Close(s[0]);
    s[0] = INVALID_SOCK;

    if (MI_RESULT_OK != Protocol_New_From_Socket(
        &agent->protocol,
        self->selector,
        s[1],
        MI_TRUE,
        _RequestCallback,
        agent,
        _EventCallback,
        agent))
            goto failed;

    s[1] = INVALID_SOCK;

    List_Append(
        (ListElem**)&self->headAgents, 
        (ListElem**)&self->tailAgents, 
        (ListElem*)agent);

    return agent;

failed:
    if (INVALID_SOCK != s[0]) 
        Sock_Close(s[0]);

    if (INVALID_SOCK != s[1]) 
        Sock_Close(s[1]);

    if (-1 != logfd) 
        close(logfd);

    if (agent)
        _FreeItem(agent);

    return 0;
}

static AgentElem* _FindOrCreateAgent(
    AgentMgr* self,
    uid_t uid,
    gid_t gid)
{
    AgentElem* agent = _FindAgent(self, uid, gid);

    if (!agent)
        agent = _CreateAgent(self, uid, gid);

    return agent;
}

static MI_Result _SendMessageToAgent(
    AgentElem* agent,
    Message* msg,
    const ProvRegEntry* proventry)
{
    RequestItem* newRequestItem;
    Message* req = 0;
    MI_Result r;

    LOGD((ZT("_SendMessageToAgent")));

    /* Allocate item form incoming message batch */ 
    newRequestItem = (RequestItem*) Batch_GetClear(msg->batch, sizeof(*newRequestItem));

    if (!newRequestItem)
        return MI_RESULT_FAILED;

    newRequestItem->request = msg;

    /* clone message (may be incoming message in some cases) */
    if (MI_RESULT_OK != MessagePackCloneForBinarySending(msg, &req))
    {
        LOGW((ZT("message clone failed\n")));
        return MI_RESULT_FAILED;
    }

    req->libraryName = Batch_Strdup(req->batch, proventry->libraryName);


    if (!req->libraryName)
    {
        Message_Release(req);
        return MI_RESULT_FAILED;
    }
    
    /* Add ref to keep request around until Result received */
    Message_AddRef(msg);

    newRequestItem->originalMsgID = msg->msgID;

    /* substitute message-id on time server->agent call;
    msgID has to be restored once first response is received */
    req->msgID = PtrToUint64(newRequestItem);

    List_Append(
        (ListElem**)&agent->headRequests, 
        (ListElem**)&agent->tailRequests, 
        (ListElem*)newRequestItem);

    r =  Protocol_Send(agent->protocol, req);
    Message_Release(req);

    return r;
}

#endif

/*
**==============================================================================
**
** Public API
**
**==============================================================================
*/
MI_Result AgentMgr_Init(
    AgentMgr* self,
    Selector* selector)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(*self));

    /* Initialize the provider manager */
    MI_RETURN_ERR(ProvMgr_Init(&self->provmgr, selector, NULL, NULL, GetPath(ID_PROVIDERDIR)));

    self->home = Strdup(GetPath(ID_PREFIX));
    self->provDir = Strdup(GetPath(ID_PROVIDERDIR));

    self->selector = selector;

    return MI_RESULT_OK;
}

MI_Result AgentMgr_Destroy(
    AgentMgr* self)
{
    ProvMgr_Destroy(&self->provmgr);
    free(self->home);
    free(self->provDir);

#if defined(CONFIG_POSIX)
    /*
        Free all outstanding agents
    */
    while (self->headAgents)
    {
        AgentElem* agent = self->headAgents;

        List_Remove(
            (ListElem**)&self->headAgents, 
            (ListElem**)&self->tailAgents, 
            (ListElem*)agent);

        _FreeItem(agent);
    }
#endif

    /* Invalidate self */
    memset(self, 0xdd, sizeof(*self));

    return MI_RESULT_OK;
}

MI_Result AgentMgr_HandleRequest(
    AgentMgr* self,
    Message* msg,
    const ProvRegEntry* proventry)
{
    AgentElem* agent;
    uid_t uid;
    gid_t gid;

    LOGD((ZT("AgentMgr_HandleRequest")));

    if (proventry->hosting == PROV_HOSTING_INPROC)
    {
        return ProvMgr_PostMessage(
            &self->provmgr,
            proventry->libraryName,
            msg);
    }

    if (proventry->hosting == PROV_HOSTING_USER)
    {
        if (0 != LookupUser(proventry->user, &uid, &gid))
        {
            LOGW((ZT("get user [%s] uid/gid"), scs(proventry->user)));
            return MI_RESULT_FAILED;
        }
    }
    else
    {
        uid = msg->uid;
        gid = msg->gid;
    }

#if defined(CONFIG_POSIX)

    agent = _FindOrCreateAgent(self, uid, gid);

    if (!agent)
    {
        LOGW((ZT("failed to load provider agent")));
        return MI_RESULT_FAILED;
    }

    return _SendMessageToAgent(agent, msg, proventry);

#else
    MI_UNUSED(agent);
    /* windows version hosts all providers as 'in-proc' */
    return ProvMgr_PostMessage(
            &self->provmgr,
            proventry->libraryName,
            msg);
#endif
}
