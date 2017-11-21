/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
Open Instrumentation event declarations for OMI

Helpful tips:
- Visual Studio will pull up the format for the event via intellisense if you encase OI macro in C-style comments
- PAL_T is automatically added to all format strings in this header.
- So don't wrap PAL_T around format strings, it may confuse C preprocessor
- OI parser does not correctly parse 'char*name'. Please use 'char* name' or 'char * name' instead.
*/

#ifndef _oi_traces_h
#define _oi_traces_h

#include <oi/oi.h>

/* 
    OMI specific data structures
    References to very basic structures only.
    The rest will be referenced here as 'void *'
*/
#include "omistructures.h"

BEGIN_EXTERNC

/******************************** FATAL ERRORS ***********************************/

OI_SETDEFAULT(PRIORITY(LOG_CRIT))
OI_SETDEFAULT(STARTID(10000))
OI_SETDEFAULT(CHANNEL(Operational))

OI_EVENT("allocation failed")
void trace_ProvMgr_AllocFailed();
OI_EVENT("unknown message type: %u")
void trace_UnknownMessageType(MI_Uint32 msgTag);
OI_EVENT("failed to create PID file: %s")
void trace_CreatePIDFileFailed(const char * idpidfile);
OI_EVENT("failed to initialize the dispatcher: %u")
void trace_DispatchInitFailed(MI_Result r);
OI_EVENT("abnormal termination of parent process detected. Old parent: %d, New parent: %d")
void trace_ParentProcessTerminated(int old_pid, int new_pid);
OI_EVENT("abnormal termination of engine process detected...shutting down server")
void trace_EngineProcessTerminated();
OI_EVENT("%T")
void trace_CriticalError(const TChar* s);


/******************************** ERRORS ***********************************/

OI_SETDEFAULT(PRIORITY(LOG_ERR))
OI_SETDEFAULT(STARTID(20000))
OI_SETDEFAULT(CHANNEL(Operational))

OI_EVENT("AgentMgr_HandleRequest failed for namespace: %T")
void trace_AgentMgrHandleRequestForNS(const TChar * nameSpace);
OI_EVENT("Agent _RequestCallback: ProvMgr_NewRequest failed with result %d !")
void trace_Agent_ProvMgrNewRequest_Failed(MI_Result result);
OI_EVENT("parameter is missing (fd)")
void trace_Agent_FDParameterIsMissing();
OI_EVENT("MessagePackCloneForBinarySending, cannot allocate message %d")
void trace_MessagePackCloneForBinarySending_AllocFailed(MI_Uint32 tag);
OI_EVENT("MessagePackCloneForBinarySending, cannot clone message tag: %d, error: %d")
void trace_MessagePackCloneForBinarySending_CloneFailed(MI_Uint32 tag, MI_Result result);
OI_EVENT("_ConnectionIn_Post: Cannot create new operation with operationId %p !")
void trace_ConnectionInPost_NewOpFailed(void * operationId);
OI_EVENT("_ConnectionIn_Post: Cannot add new operation with operationId %p !")
void trace_ConnectionInPost_CannotAddNewOp(void * operationId);
OI_EVENT("_ConnectionIn_Post: Cannot allocate message to post failed result %d !")
void trace_ConnectionInPost_MessageAllocFailed(MI_Result result);
OI_EVENT("ConnectionIn: %p Post cancel cannot find entry for msg(%p:%d:%T:%x) on interaction [%p]<-%p")
void trace_ConnectionIn_PostCancelError(void * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId, Interaction * selfInteraction, Interaction * otherInteraction);
OI_EVENT("MuxIn_Open: cannot allocate ConnectionIn")
void trace_MuxInOpen_AllocFailed();

OI_EVENT("_StrandEntryOperation_Add: Canceled %d entries %p(%s): %p(%s)")
void trace_StrandEntryOperation_AddCanceled(unsigned int numEntries, StrandMany * self, const char * selfTrand, Strand * entry, const char * entryStrandName);
OI_EVENT("_StrandEntryOperation_Add: Failed %d entries %p(%s): %p(%s)")
void trace_StrandEntryOperation_AddFailed(unsigned int numEntries, StrandMany * self, const char * selfTrand, Strand * entry, const char * entryStrandName);
OI_EVENT("Strand %p(%s), cannot delete entry %p(%s)")
void trace_Strand_CannotDelete(Strand * selfStrand, const char * selfStrandName, Strand * entryStrand, const char * entryStrandName);
OI_EVENT("_Strand_Schedule: %p(%s) FAILED Taking over opening, state %x(%s), methodBit: %x")
void trace_Strand_ScheduleFailed(Strand * self, const char * selfStrandName, ptrdiff_t state, const char * stateName, unsigned int bit);

OI_EVENT("failed to read result from child; errno (%d)")
void trace_UserAuth_FailedToRead(int err);
OI_EVENT("cannot find request item %p; agent for user %d !")
void trace_StrandMany_CannotFindItem(void * operationId, int uid);
OI_EVENT("_RequestItem_Post: _PrepareMessageForAgent failed %d")
void trace_RequestItem_PostFailed(MI_Result result);
OI_EVENT("_RequestItem_Cancel: _PrepareMessageForAgent failed %d")
void trace_RequestItem_Cancel_PrepMessageFailed(MI_Result result);
OI_EVENT("_RequestItem_Cancel: CancelMsg_New failed")
void trace_RequestItem_Cancel_CancelMsg_NewFailed();
OI_EVENT("_DispatchEnumerateInstancesReq() out of memory")
void trace_DispatchEnumerateInstancesReq_OutOfMemory();
OI_EVENT("_DispatchAssocReq() out of memory")
void trace__DispatchAssocReq_OutOfMemory();

OI_EVENT("HTTP: Error on allocating HttpRequest(%p)")
void trace_HTTP_RequestAllocFailed(void * handler);
OI_EVENT("HttpSocket: %p Cannot posting message %p for interaction [%p]<-%p")
void trace_HttpSocket_CannotPostMessage(void * self, Message * msg, Interaction * selfInteraction, Interaction * other);
OI_EVENT("---> SSL: failed to open private key file: %s")
void trace_SSL_FailedToOpenPrivateKeyFile(const char * file);
OI_EVENT("---> SSL: failed to create private key")
void trace_SSL_FailedToCreatePrivateKey();
OI_EVENT("---> SSL: no private key found in %s")
void trace_SSL_NoPrivateKeyFound(const char * keyPath);
OI_EVENT("---> SSL: Private and public key do not match")
void trace_SSL_PrivateAndPublicKeyDonotMatch();
OI_EVENT("---> SSL: cannot create ssl context")
void trace_SSL_CannotCreateContext();
OI_EVENT("---> SSL: Unable to set server options for options flag %d")
void trace_SSL_CannotSetOptions(int options);
OI_EVENT("---> SSL: No server certificate found in %s. %s")
void trace_SSL_NoServerCertFound(const char * keyPath, const char * error);
OI_EVENT("---> SSL: No matching ciphers found for: %s")
void trace_SSL_BadCipherList(const char * sslCVipherList);

OI_EVENT("Object %p's container is not NULL (%p).")
void trace_ObjectContainerIsNotNull(void * self, void * container);
OI_EVENT("Object %p has container (%p), expected (%p).")
void trace_ObjectUnexpectedContainer(void * self, void * selfContainer, void * expected);
OI_EVENT("Object %p is not a valid filter object.")
void trace_ObjectIsNotAValidFilter(void * self);
OI_EVENT("Object %p is not a valid Listener object.")
void trace_ObjectIsnotValidListener(void * self);
OI_EVENT("Parse query '%T' failed.")
void trace_ParseQueryFailed(const TChar * filterQuery);
OI_EVENT("Unsupported query language '%T'.")
void trace_UnsupportedQueryLanguage(const TChar * filterQueryLanguage);
OI_EVENT("Temporary subscription can have only 1 target namespace.")
void trace_TempSubscrCanHaveOnlyOneNamespace();

OI_EVENT("cannot open auth data file: %s")
void trace_CannotOpenAuthFile(const char * file);
OI_EVENT("cannot read from auth data file: %s")
void trace_CannotReadAuthFile(const char * file);
OI_EVENT("failed to pack instance: %u")
void trace_PackInstanceFailed(MI_Result r);
OI_EVENT("Unmatched filter type")
void trace_UnmatchedFilterType();
OI_EVENT("_Provider_InvokeEnable: Provider posted final result during EnableIndications call")
void trace_ProviderEnableIndication_Failed();
OI_EVENT("AggregationContext allocation failed")
void trace_AggregationContext_InitFailed();
OI_EVENT("Failed to create SubscriptionContext")
void trace_SubscrContextFailed();
OI_EVENT("Failed to add subscription to manager")
void trace_FailedToAddSubscrMgr();
OI_EVENT("Failed to enable indications on class (%T)")
void trace_EnableIndication_Failed(const TChar * className);
OI_EVENT("Unloading active provider %T, with ref counter %d")
void trace_UnloadingActiveProvider(const TChar * className, int refCount);
OI_EVENT("Unloading active provider for lib %s, ref counter %d")
void trace_UnloadingActiveProviderWithLib(const char * lib, int refCount);
OI_EVENT("omiserver exited due to unloading active provider (%s). Please restart")
void trace_UnloadingActiveProvider_ServerExit(const char * lib);
OI_EVENT("SubMgrSubscription allocation failed")
void trace_SubMgrSubscription_AllocFailed();
OI_EVENT("SubscriptionContext init failed")
void trace_SubscriptionContext_InitFailed();
OI_EVENT("Instance filter allocation failed")
void trace_InstanceFilter_AllocFailed();

OI_EVENT("Selector_Run: %p Error on initial PAL_Time")
void trace_SelectorRun_InitPALTIME_Error(void * self);
OI_EVENT("Selector_Run: %p error %d on _SetSockEvents for handler: %p")
void trace_SelectorRun_SetSocketEventsError(void * self, int r, void * handler);
OI_EVENT("Selector_Run: %p Empty List")
void trace_SelectorRun_EmptyList(void * self);
OI_EVENT("Selector_Run: %p, Error on WaitForMultipleObjectsEx: %d")
void trace_SelectorRun_WaitError(void * self, int result);
OI_EVENT("Selector_Run: %p Error on PAL_Time")
void trace_SelectorRun_PALTimeError(void * self);
OI_EVENT("Selector_Run: %p error %d on _GetSockEvents for handler: %p")
void trace_SelectorRun_GetSocketEventsError(void * self, int r, void * handler);

OI_EVENT("Conversion of response page to UTF-8 failed")
void trace_Wsman_HttpResponseMsg_ConversionError();

OI_EVENT("Sock_Write failed with unknown error (%u)")
void trace_SockWrite_Failed(MI_Uint32 err);
OI_EVENT("socket file path too long (> %u): '%s'")
void trace_SocketFilePathTooLong(MI_Uint32 length, const char * file);
OI_EVENT("Wsman: Error on allocating HttpResponseMsg Page (%d)")
void trace_Wsman_HttpResponseMsgPage_AllocError(int httpErrorCode);
OI_EVENT("Wsman: Error on allocating HttpResponseMsg (%d)")
void trace_Wsman_HttpResponseMsg_AllocError(int httpErrorCode);
OI_EVENT("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) received duplicate success subscribe response")
void trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess(void * self);
OI_EVENT("_HttpCallbackOnNewConnection: out of memory")
void trace_HttpCallbackOnNewConnection_OutOfMemory();
OI_EVENT("out of memory")
void trace_OutOfMemory();
OI_EVENT("open/close mismatch: {%T}{%T}")
void trace_OpenCloseMismatch(const TChar * propNameChar, const TChar * name);
OI_EVENT("Lifecycle subscription request for unsupported class (%T)")
void trace_LifeCycleSubscription_UnsupportedClass(const TChar * className);
OI_EVENT("Failed to construct instance of %T")
void trace_FailedToConstructInstance(const TChar * className);
OI_EVENT("Failed to set common properties for %T")
void trace_FailedToSet_CommonProperties(const TChar * className);
OI_EVENT("Failed to set CorrelatedIndications with ABC")
void trace_FailedToSet_CorrelatedIndications();
OI_EVENT("Failed to set IndicationFilterName with ABC")
void trace_FailedToSet_IndicationFilterName();
OI_EVENT("Failed to set IndicationIdentifier with ABC")
void trace_FailedToSet_IndicationIdentifier();
OI_EVENT("Failed to set IndicationTime with ABC")
void trace_FailedToSet_IndicationTime();
OI_EVENT("Failed to set MethodName")
void trace_FailedToSet_MethodName();
OI_EVENT("Failed to set MethodParameters")
void trace_FailedToSet_MethodParameters();
OI_EVENT("Failed to set OtherSeverity with ABC")
void trace_FailedToSet_OtherSeverity();
OI_EVENT("Failed to set PerceivedSeverity with ABC")
void trace_FailedToSet_PerceivedSeverity();
OI_EVENT("Failed to set PreCall")
void trace_FailedToSet_PreCall();
OI_EVENT("Failed to set PreviousInstance")
void trace_FailedToSet_PreviousInstance();
OI_EVENT("Failed to set ReturnValue")
void trace_FailedToSet_ReturnValue();
OI_EVENT("Failed to set SequenceContext with ABC")
void trace_FailedToSet_SequenceContext();
OI_EVENT("Failed to set SequenceNumber with ABC")
void trace_FailedToSet_SequenceNumber();
OI_EVENT("Failed to set SourceInstance with ABC")
void trace_FailedToSet_SourceInstance();
OI_EVENT("Failed to set SourceInstanceHost with ABC")
void trace_FailedToSet_SourceInstanceHost();
OI_EVENT("Failed to set SourceInstanceModelPath with ABC")
void trace_FailedToSet_SourceInstanceModelPath();
OI_EVENT("Lifecycle subscription request of class (%T) for unsupported targetType (%d). Supported is (0x%X)")
void trace_LifecycleSubscription_UnsupportedTargetType(const TChar * className, MI_Uint32 targetType, MI_Uint32 supported);

OI_EVENT("NULL module pointer returned by shared library: %s: %s")
void trace_Provmgr_NullModulePointer(const char* libraryName, const char* mainfuncname);
OI_EVENT("Failed to load provider %s, due to it's version (%d.%d.%d) is newer than server version (%d.%d.%d)")
void trace_Provmgr_FailedToLoadProvider(const char* libraryName, MI_Uint16 providermajor, MI_Uint16 providerminor, MI_Uint16 providerrevision, MI_Uint16 servermajor, MI_Uint16 serverminor, MI_Uint16 serverrevision);

OI_EVENT("InstanceFilter_Evaluate: NULL input parameter")
void trace_InstanceFilter_EvaluateWithNullInput();
OI_EVENT("InstanceFilter_GetExpression: NULL input parameter")
void trace_InstanceFilter_GetExpressionWithNullInput();
OI_EVENT("InstanceFilter_New: NULL input parameter")
void trace_InstanceFilter_NewWithNullInput();
OI_EVENT("InstanceFilter_GetQueyExpression: Unsupported Message Tag")
void trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag();
OI_EVENT("InstanceFilter_GetQueryLanguage: Unsupported Message Tag")
void trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag();

OI_EVENT("failed to open configuration file: %s")
void trace_MIFailedToOpenConfigFile(const char * file);
OI_EVENT("%s: %s\n")
void trace_MIFailedToReadConfigValue(const char * file, const char * error);
OI_EVENT("%s(%u): invalid value for '%s': %s")
void trace_MIConfig_InvalidValue(const char * path, unsigned int line, const char * key, const char * value);
OI_EVENT("Leave %s with session (%p).")
void trace_MILeaveSession(const char * func, void * session);
OI_EVENT("Leave %s due to invalid session (%p) or it has invalid thunkHandle.")
void trace_MIInvalidSession(const char * func, void * session);
OI_EVENT("Leave %s due to session (%p) has invalid thunkHandle.")
void trace_MISessionInvalidThunkHandle(const char * func, void * session);
OI_EVENT("Leave %s due to Session AccessCheck on session (%p) failed.")
void trace_MISession_AccessCheckFailed(const char * func, void * session);
OI_EVENT("Leave %s due to session (%p) has invalid sessionThunk.")
void trace_MISession_InvalidSessionThunk(const char * func, void * session);
OI_EVENT("Leave %s due to Session AccessCheck on session (%p) failed.")
void trace_MiSession_AccessCheckFailed(const char * func, void * session);
OI_EVENT("Trying to thunk invalid generic handle: %p")
void trace_MIThunk_InvalidHandle(void * handle);
OI_EVENT("Trying to thunk generic handle that has an old version number: %p")
void trace_MIThunk_OldVersion(void * handle);
OI_EVENT("Trying to thunk generic handle that has been shutdown already: %p")
void trace_MIThunk_AlreadyShutdown(void * handle);

OI_EVENT("Timer_Start:Timer (%p) already running")
void trace_Timer_CannotStartTimer_AlreadyRunning(void* timer);
OI_EVENT("Timer_Start:Timer cannot be initialized - Error (%x)")
void trace_Timer_Initialization_Failed(PAL_Uint32 error);
OI_EVENT("Timer_Start:Selector not specified or initialized (%p)")
void trace_Timer_Selector_Missing(void* selector);
OI_EVENT("Timer: Unable to access current time")
void trace_Timer_Cannot_AccessCurrentTime();
OI_EVENT("Timer_Start: Unable to add handler to selector (%p")
void trace_Timer_Cannot_AddHandlerToSelector(void* selector);
OI_EVENT("Timer_Close: Double close of timer (%p)")
void trace_Timer_Double_Close(void* timer);
OI_EVENT("Timer_Callback: Unexpected Selector mask %u")
void trace_Timer_Unexpected_Selector_Mask(PAL_Uint32 mask);
OI_EVENT("_ValidateHeader: OperationTimeout must be xs:duration")
void trace_Wsman_InvalidOperationTimeoutValue_Timestamp();
OI_EVENT("Failed to execute PREEXEC program: {%s}")
void trace_PreExecFailed(const char* path);
OI_EVENT("_Provider_InvokeSubscribe: Unsupported subscription type %x")
void trace_InvokeSubscribeWithInvalidTargetType(MI_Uint32 targetType);

OI_EVENT("MI Session already connected, operation %p")
void trace_MI_SessionAlreadyConnected(void * operation);
OI_EVENT("Out of memory error, operation %p")
void trace_MI_OutOfMemoryInOperation(void * operation);
OI_EVENT("MI Socket connector failed, operation %p, result %d")
void trace_MI_SocketConnectorFailed(void * operation, MI_Result miResult);
OI_EVENT("MI client failed to start run thread, operation %p")
void trace_MI_FailedToStartRunThread(void * operation);
OI_EVENT("MI session init failed, session %p, result %d")
void trace_MI_SessionFailed(void * session, MI_Result miResult);
OI_EVENT("Out of memory error, session %p")
void trace_MI_OutOfMemoryInSession(void * session);
OI_EVENT("InteractionProtocolHandler_Session_Connect failed, session %p, result %d")
void trace_MI_SessionConnectFailed(void * session, MI_Result miResult);
OI_EVENT("InstantchToBatch failed in MI session, session %p, result %d")
void trace_MI_InstanceToBatch_Failed(void * session, MI_Result miResult);

OI_EVENT("Socket connect failed, locator %s")
void trace_SocketConnectorFailed(const char * locator);
OI_EVENT("Local socket failed on socket() call, sock %s")
void trace_LocalSocketFailed(const char * socketName);
OI_EVENT("Socket SetOnExec failed, %s")
void trace_LocalSocket_SetOnExecFailed(const char * socketName);
OI_EVENT("Socket SetBlocking failed, %s")
void trace_LocalSocket_SetBlockingFailed(const char * socketName);
OI_EVENT("Socket connect() failed, %s, error %d")
void trace_LocalSocket_ConnectFailed(const char * socketName, int error);

OI_EVENT("SSL error %d verifying with certificate: %s")
void trace_SSL_VerifyFailed(int error, const char * certificateSubject);
OI_EVENT("Bad SSL trusted certificates directory: %s")
void trace_SSL_BadTrustDir(const char * directory);

OI_EVENT("Library name is NULL for class: %S, in namespace: %S. Library Name should NOT be NULL")
void trace_ProvReg_ProvRegEntry_NULLLibraryName(const char * nspace, const char * classname);
OI_EVENT("Reg file %s is corrupted. It will be skipped by the server")
void trace_ProvReg_SkipRegFile(const char * filePath);
OI_EVENT("LIBRARY tag is missing in reg file: %s")
void trace_RegFile_MissingLibraryTag(const char * filePath);

OI_EVENT("Invalid engine credentials")
void trace_InvalidEngineCredentials();
OI_EVENT("Engine credentials have not been received")
void trace_EngineCredentialsNotReceived();
OI_EVENT("Tracker hash map error");
void trace_TrackerHashMapError();
OI_EVENT("Client credentials not yet verified. Msg type = %d");
void trace_ClientCredentialsNotVerified(int type);
OI_EVENT("Client credentials not yet received. Msg type = %d");
void trace_ClientCredentialsNotReceived(int type);
OI_EVENT("Failed to create new server connection")
void trace_FailedNewServerConnection();
OI_EVENT("Failed to send PAM auth request to server")
void trace_FailedSendPamRequest();
OI_EVENT("Server failed to open PAM file")
void trace_ServerFailedPamFile();
OI_EVENT("InProc providers are no longer supported: (%s). Defaulting to @requestor")
void trace_InvalidInProcProvider(const char* name);
OI_EVENT("Engine AskServerToAuthenticate received NULL handle")
void trace_EngineAuthenticateNullHandler();
OI_EVENT("Engine AskServerToAuthenticate received NULL callback")
void trace_EngineAuthenticateNullCallback();
OI_EVENT("HTTP: Client Authorization failed. gss:(%s) mech:(%s)")
void trace_HTTP_ClientAuthFailed(const char * major, const char * minor);



/******************************** WARNINGS ***********************************/

OI_SETDEFAULT(PRIORITY(LOG_WARNING))
OI_SETDEFAULT(STARTID(30000))
OI_SETDEFAULT(CHANNEL(Analytic))

OI_EVENT("__FindSubRequest: SubscribeElem %p(%p), Cannot find key: %x")
void trace__FindSubRequest_CannotFindKey(void * self, Strand * selfStrand, MI_Uint64 key);
OI_EVENT("_AgentElem_FindRequest, Agent %p(%p), Cannot find key: %x")
void trace_AgentElem_FindRequest_CannotFindKey(void * agent, Strand * strand, MI_Uint64 key);
OI_EVENT("_DiscoverIndicationClass: Create error instance failed with (%d)")
void trace_DiscoverIndicationClass_CreateInstanceFailed(MI_Result res);
OI_EVENT("_DiscoverIndicationClass: Invalid lifecycle query")
void trace_DiscoverIndicationClass_InvalidLifeCycleQuery();
OI_EVENT("_DiscoverIndicationClass: Unsupported target class type (%d)")
void trace_DiscoverIndicationClass_UnsupportedTargetClassType(int targetType);
OI_EVENT("_FindLifecycleClass: Evaluation result does not have exactly one symbol (%d)")
void trace_FindLifecycleClass_EvalHasMoreThanOneSymbol(int nsymbols);
OI_EVENT("_FindLifecycleClass: Evaluation result is not boolean")
void trace_FindLifecycleClass_EvalResultIsNotBool();
OI_EVENT("_FindLifecycleClass: Found ISA operator for embedded property (%T), target class (%T)")
void trace_FindLifecycleClass_FoundISAOperator(const TChar * property, const TChar * className);
OI_EVENT("_FindLifecycleClass: Invalid embedded property name (%T)")
void trace_FindLifecycleClass_InvalidEmbeddedProperty(const TChar * name);
OI_EVENT("_FindLifecycleClass: Invalid lifecycle query due to ISA operator is within an OR operator sub clause")
void trace_FindLifecycleClass_InvalidLifecycleQuery();
OI_EVENT("_FindLifecycleClass: Invalid token type")
void trace_FindLifecycleClass_InvalidTokenType();
OI_EVENT("_FindLifecycleClass: Too few operands for ISA operator")
void trace_FindLifecycleClass_TooFewOperandsISA();
OI_EVENT("_FindLifecycleClass: Unsupported lifecycle query, which has more than 1 ISA operators")
void trace_FindLifecycleClass_UnsupportedLifecycleQuery();
OI_EVENT("_getNameValuePair failed")
void trace_GetNameValuePair_Failed();
OI_EVENT("_getRequestLine failed")
void trace_GetRequestLine_failed();
OI_EVENT("_PrepareMessageForAgent: failed %d")
void trace_PrepareMessageForAgent_Failed(MI_Result result);
OI_EVENT("_RequestCallbackWrite failed")
void trace_RequestCallbackWrite_Failed();
OI_EVENT("_RequestItem_ParentPost: %p, receiving msg %p when already closed")
void trace_RequestItem_ParentPost_AfterClose(void * requestItem, Message * msg);
OI_EVENT("_SendIN_IO_thread: invalid magic !")
void trace_Message_InvalidMagic();
OI_EVENT("_SendIN_IO_thread_HttpSocket: _RequestCallbackWrite failed")
void trace_SendIN_IO_thread_HttpSocket_WriteFailed();
OI_EVENT("_SendIN_IO_thread_HttpSocket: cannot send message: invalid handler (%p)\n")
void trace_SendIN_IO_thread_HttpSocket_InvalidHandler(void * sendSock);
OI_EVENT("_SendRequestToAgent: Batch_Strdup failed\n")
void trace_SendRequestToAgent_Batch_Strdup_Failed();
OI_EVENT("_SendRequestToAgent: message clone failed %d\n")
void trace_SendRequestToAgent_MessageCloneFailed(MI_Result result);
OI_EVENT("_SendRequestToAgent: StrandEntry_New failed\n")
void trace_SendRequestToAgent_StrandNewFailed();
OI_EVENT("_SubscribeElem_CheckSendFinalResult: self (%p) status (%T), ignore")
void trace_SubscribeElem_CheckSendFinalResult(void * self, const TChar * status);
OI_EVENT("_SubscribeElem_EntryPost: Unexpected msg (%p:%d:%T:%x)")
void trace_SubscribeElem_EntryPost_UnexpectedMsg(Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("agent launching: failed to exec %s, errno %d")
void trace_AgentLaunch_Failed(const char * program, MI_Uint32 error);
OI_EVENT("allocating PostSchemaMsg failed")
void trace_PostSchemaMsg_Failed();
OI_EVENT("auth failed - random data mismatch")
void trace_AuthFailed_RandomDataMismatch();
OI_EVENT("auth failed for user [%s]")
void trace_AuthFailed_ForUser(const char * user);
OI_EVENT("base64 decoding error in Basic auth: [%s]\n")
void trace_Base64_DecodeErrorInBasic(const char * value);
OI_EVENT("Base64Dec failed")
void trace_Base64Dec_Failed();
OI_EVENT("batch fix pointer failed\n")
void trace_BatchFixPointerFailed();
OI_EVENT("Cannot allocate new enumerate context - (out of memory)")
void trace_EnumContexAllocFailed_OutOfMemory();
OI_EVENT("Cannot allocate new enumerate context - all used (too many concurrent enumerations)")
void trace_EnumContexAllocFailed_TooManyConcurrent();
OI_EVENT("cannot create file for user uid [%d]")
void trace_CannotCreateFileForUser(int uid);
OI_EVENT("Cannot find enumerate context: %x")
void trace_CannotFindEnumerateContext(MI_Uint32 enumerationContextID);
OI_EVENT("cannot find symbol in shared library: %s: %s")
void trace_SharedLibrary_CannotFindSymbol(const char * library, const char * symbol);
OI_EVENT("cannot format log file name\n")
void trace_CannotFormatLogFilename();
OI_EVENT("cannot get user's gid for uid %d")
void trace_CannotGetUserGidForUid(int uid);
OI_EVENT("cannot open shared library: {%s}")
void trace_SharedLib_CannotOpen(const char * library);
OI_EVENT("cannot open shared library: {%s}: %T")
void trace_SharedLib_CannotOpenSecondTry(const char * library, const TChar * error);
OI_EVENT("cannot open shared library: {%T}: %T")
void trace_SharedLib_CannotOpenFirstTry(const TChar * library, const TChar * error);
OI_EVENT("cannot send message: expired handler (msg->clientID) %p\n")
void trace_Message_ExpiredHandler(void * sendSock);
OI_EVENT("cannot send message: queue overflow on Listener or connection aborted, %p\n")
void trace_QueueOverflowOrConnectionAbort(void * sendSock);
OI_EVENT("cannot send message: queue overflow) %p\n")
void trace_QueueOverflow(void * sendSock);
OI_EVENT("cannot spawn a child process\n")
void trace_CannotSpawnChildProcess();
OI_EVENT("Class %T is not an indication class")
void trace_ClassIsNotIndication(const TChar * className);
OI_EVENT("Close with active aggregation context")
void trace_CloseWithActiveAggregationContext();
OI_EVENT("closing socket due to Http_Listener_SocketData alloc failed")
void trace_SocketClose_Http_Listener_SocketDataAllocFailed();
OI_EVENT("closing socket due to Http_SR_SocketData calloc failed")
void trace_SocketClose_Http_SR_SocketDataAllocFailed();
OI_EVENT("closing socket due to recvBuffer calloc failed")
void trace_SocketClose_recvBuffer_AllocFailed();
OI_EVENT("closing socket due to Selector_AddHandler failed")
void trace_SocketClose_Selector_AddHandlerFailed();
OI_EVENT("closing socket due to Sock_SetBlocking failed")
void trace_SocketClose_SetBlockingFailed();
OI_EVENT("contentLength max check failed")
void trace_ContentLength_MaxCheck_Failed();
OI_EVENT("Enumeration has no class name")
void trace_EnumHasNoClassname();
OI_EVENT("failed to call library unload: %u:%s")
void trace_FailedCallLibraryUnload(MI_Result result, const char * library);
OI_EVENT("failed to call module load with result %u; library: %s")
void trace_FailedCallModuleLoad(MI_Result result, const char * library);
OI_EVENT("failed to call provider's load with result %d; class: %T")
void trace_FailedProviderLoad(MI_Result result, const TChar * className);
OI_EVENT("failed to chown auth file %s")
void trace_ChownAuthFile_Failed(const char * path);
OI_EVENT("failed to create auth file %s")
void trace_CreateAuthFile_Failed(const char * path);
OI_EVENT("failed to create log file %s; errno %d")
void trace_CreateLogFile_Failed(const char * path, int error);
OI_EVENT("failed to init salt")
void trace_FailedInitSalt();
OI_EVENT("failed to load /dev/urandom")
void trace_FailedLoadDevUrandom();
OI_EVENT("failed to load provider agent")
void trace_FailedLoadProviderAgent();
OI_EVENT("failed to open provider library: %s")
void trace_OpenProviderLib_Failed(const char * libraryName);
OI_EVENT("failed to open the provider %s for class %T")
void trace_OpenProvider_FailedForClass(const char * libraryName, const TChar * className);
OI_EVENT("failed to produce random data")
void trace_FailedToProduceRandomData();
OI_EVENT("failed to remove PID file: %s")
void trace_FailedRemovePIDFile(const char * path);
OI_EVENT("failed to restore message %d [%T]\n")
void trace_RestoreMessage_Failed(MI_Result r, const TChar * error);
OI_EVENT("fcntl(F_SETFD) failed %d")
void trace_fcntl_failed(int err);
OI_EVENT("get user [%s] uid/gid")
void trace_GetUserUidGid_Failed(const char * user);
OI_EVENT("getpwnam_r filed, errno %d")
void trace_getpwnamr_Failed(MI_Uint32 err);
OI_EVENT("getpwuid_r failed: errno (%d)")
void trace_getHomeDir_Failed();
OI_EVENT("GetHomeDir Failed")
void trace_getpwuidr_Failed(MI_Uint32 err);
OI_EVENT("http chunk header is too big; dropping connection\n")
void trace_HttpChunkHeaderIsTooBig();
OI_EVENT("http header is too big; dropping connection\n")
void trace_HttpHeaderIsTooBig();
OI_EVENT("http payload is bigger than content-length\n")
void trace_HttpPayloadIsBiggerThanContentLength();
OI_EVENT("IndiMgr_HandleSubscribeReq: StrandEntry_New failed, req (%p)")
void trace_IndiMgr_HandleSubscribeReq_StrandNewFailed(void * req);
OI_EVENT("initgroups failed: errno (%d)")
void trace_initgroups_Failed(MI_Uint32 err);
OI_EVENT("instance conversion failed: %T, err %d")
void trace_InstanceConversionFailed(const TChar * name, MI_Result r);
OI_EVENT("invalid query expression: %T")
void trace_InvalidQueryExpression(const TChar * filter);
OI_EVENT("library unload did not call post result")
void trace_LibraryUnload_DidnotPostResult();
OI_EVENT("module load failed to call post result")
void trace_ModuleLoad_FailedPostResult();
OI_EVENT("no digest available")
void trace_NoDigestAvailable();
OI_EVENT("NTLM Credentials file does not exist or invalid permissions: %s")
void trace_NtlmCredFileInvalid(const char * ntlmfile);
OI_EVENT("provider load did not call post result")
void trace_ProviderLoad_DidnotPostResult();
OI_EVENT("query validation failed: %T")
void trace_QueryValidationFailed(const TChar * text);
OI_EVENT("query/enumeration class name mismatch: %T/%T")
void trace_QueryEnumClassnameMismatch(const TChar * first, const TChar * second);
OI_EVENT("queryLanguage or queryExpression is missing")
void trace_QueryLanguageOrExpressionMissing();

OI_EVENT("restore msg failed first time\n")
void trace_RestoreMsgFailed_FirstTime();
OI_EVENT("restore msg failed for invalid tag: %d\n")
void trace_RestoreMsgFailed_InvalidTag(MI_Uint32 msgtag);
OI_EVENT("restore msg failed second time for tag: %d")
void trace_RestoreMsgFailed_SecondTime(MI_Uint32 msgtag);
OI_EVENT("restore msg failed since pointer is null for mft_pointer")
void trace_RestoreMsgFailed_PointerIsNull();
OI_EVENT("restore msg failed since there is no ptrPacked for mft_instance")
void trace_RestoreMsgFailed_PtrPackedMissing();
OI_EVENT("restore msg failed third time for tag\n")
void trace_RestoreMsgFailed_ThirdTime(MI_Uint32 msgtag);
OI_EVENT("restore msg failed while fixing batch pointers for mft_instance\n")
void trace_RestoreMsgFailed_PointersForMstInstance();
OI_EVENT("restore msg failed while fixing batch pointers for mft_pointer")
void trace_RestoreMsgFailed_PointersForMstPointer();
OI_EVENT("restore msg failed while unpacking instance for mft_instance")
void trace_RestoreMsgFailed_UnpackingInstance();
OI_EVENT("Schema conversion into cim-xml failed with error %d")
void trace_SchemaConversion_ToCimXmlFailed(MI_Result result);
OI_EVENT("Schema conversion into instance failed %d")
void trace_SchemaConversion_ToInstanceFailed(MI_Result result);
OI_EVENT("Schema instance packaging failed %d")
void trace_SchemaInstancePackaging_Failed(MI_Result result);
OI_EVENT("Selector_AddHandler() failed\n")
void trace_SelectorAddHandler_Failed();
OI_EVENT("SELECTOR_TIMEOUT reached; so failed")
void trace_ConnectionClosed_Timeout();
OI_EVENT("set non-blocking failed\n")
void trace_SetNonBlocking_Failed();
OI_EVENT("setgid failed: errno (%d)")
void trace_setgid_Failed(MI_Uint32 err);
OI_EVENT("setTimeout: invalid magic !")
void trace_Timeout_InvalidMagic();
OI_EVENT("setuid failed: errno (%d)")
void trace_setuid_Failed(MI_Uint32 err);
OI_EVENT("Sock_Read: Error %d")
void trace_SockRead_Failed(int error);
OI_EVENT("Sock_ReadV: Error %d")
void trace_SockReadV_Failed(int error);
OI_EVENT("Sock_SetBlocking() failed\n")
void trace_SockSetBlocking_Failed();
OI_EVENT("Sock_WriteV: Error %d")
void trace_SockWriteV_Failed(int error);
OI_EVENT("Socket: %p, Connection closed\n")
void trace_Socket_ConnectionClosed(void * handler);
OI_EVENT("Socket: %p, Error: %d while reading header\n")
void trace_Socket_ReadingHeader_Error(void * handler, MI_Result r);
OI_EVENT("Socket: %p, Error: %d while reading\n")
void trace_Socket_Read_Error(void * handler, MI_Result r);
OI_EVENT("Socket: %p, Error: %d while sending\n")
void trace_Socket_Sending_Error(void * handler, MI_Result r);
OI_EVENT("socketpair() failed\n")
void trace_SocketPair_Failed();
OI_EVENT("ssl_new() failed\n")
void trace_SSLNew_Failed();
OI_EVENT("ssl_set_fd() failed\n")
void trace_SSL_setfd_Failed();
OI_EVENT("ssl-read error: %d [%s]\n")
void trace_SSLRead_Error(int err, const char * errtxt);
OI_EVENT("ssl-read: unexpected sys error %d\n")
void trace_SSLRead_UnexpectedSysError(int err);
OI_EVENT("ssl-write: unexpected sys error %d\n")
void trace_SSLWrite_UnexpectedSysError(int err);
OI_EVENT("start-request: connection was closed")
void trace_StartRequest_ConnectionClosed();
OI_EVENT("start-request: invalid magic !")
void trace_StartRequest_InvalidMagic();
OI_EVENT("Heartbeat timeout: Sending partial results or heartbeat for enumeration context %p (%u)")
void trace_WsmanEnumerationcontext_HeartbeatTimeout(void * self, MI_Uint32 enumerationContextID);
OI_EVENT("too many http headers; skipping %s: %s\n")
void trace_TooManyHttpHeaders(const char * name, const char * value);
OI_EVENT("Unhandled AggregationContext state %u")
void trace_AggregationContext_UnhandledState(int state);
OI_EVENT("Socket: %p, Error PageCount while reading header\n")
void trace_Socket_ReadingHeader_ErrorPageCount(void * handler);
OI_EVENT("Socket: %p, Error Magic while reading header\n")
void trace_Socket_ReadingHeader_ErrorMagic(void * handler);
OI_EVENT("Socket: %p, Error BatchSize while reading header\n")
void trace_Socket_ReadingHeader_ErrorBatchSize(void * handler);
OI_EVENT("Socket: %p, Error CreatingBatch while reading header\n")
void trace_Socket_ReadingHeader_ErrorCreatingBatch(void * handler);

OI_EVENT("wsman: _InteractionWsman_Right_Post: unexpected message tag %d")
void trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage(MI_Uint32 msgtag);
OI_EVENT("wsman: _InteractionWsmanEnum_Right_Post: unexpected message tag %d")
void trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage(MI_Uint32 msgtag);
OI_EVENT("wsman: authentication failed for user [%s]")
void trace_Wsman_AuthenticationFailed(const char * user);
OI_EVENT("wsman: Unsupported authentication [%s]")
void trace_Wsman_UnsupportedAuthentication(const char * Authen);
OI_EVENT("wsman: charset is not supported [%s]")
void trace_Wsman_CharsetIsNotSupported(const char * charset);
OI_EVENT("wsman: delete-instance: instance name parameter is missing")
void trace_Wsman_InstanceNameParameterMissing();
OI_EVENT("wsman: failed to parse SOAP envelope")
void trace_Wsman_FailedParseSOAPEnvelope();
OI_EVENT("wsman: failed to parse WS header")
void trace_Wsman_FailedParseWSHeader();
OI_EVENT("wsman: found neither Action or Identify")
void trace_Wsman_NoActionOrIdentify();
OI_EVENT("wsman: Get : Unsupported ws-cim resourceUri")
void trace_WsmanGet_UnsupportedResourceURI();
OI_EVENT("wsman: get-instance: instance name parameter is missing")
void trace_WsmanGetInstance_InstanceNameParameterMissing();
OI_EVENT("wsman: invalid/missing content type in request [%T]")
void trace_Wsman_InvalidMissingContentType(const TChar * type);
OI_EVENT("wsman: mandatory parameters (className, namespace) are missing for enumerate request")
void trace_WsmanEnum_ParametersMissing();
OI_EVENT("wsman: max-envelope is too small even for one message; message size %d")
void trace_Wsman_MaxEnvelopeIsTooSmall(int messageSize);
OI_EVENT("wsman: Put-instance: instance name parameter is missing")
void trace_WsmanPut_InstanceNameParameterMissing();
OI_EVENT("wsman: requested envelope size (%d) is too small; expected at least 8K")
void trace_Wsman_RequestedEnvelopeSizeIsTooSmall(int envelopeSize);
OI_EVENT("wsman: size of buffer is 0")
void trace_Wsman_BufferSizeIsZero();
OI_EVENT("wsman: unable to parse incoming xml/ enumerate request body")
void trace_WsmanEnum_UnableToParseXml();
OI_EVENT("wsman: unable to parse incoming xml/ Pull request body")
void trace_WsmanPull_UnableToParseXml();
OI_EVENT("wsman: unable to parse incoming xml/ Release request body")
void trace_WsmanRelease_UnableToParseXml();
OI_EVENT("wsman: unable to process Create request")
void trace_WsmanCreate_UnableToProcessRequest();
OI_EVENT("wsman: unable to process delete-instance request")
void trace_WsmanDelete_UnableToProcessRequest();
OI_EVENT("wsman: unable to process get-class request")
void trace_WsmanGetClass_UnableToProcessRequest();
OI_EVENT("wsman: unable to process get-instance request")
void trace_WsmanGetInstance_UnableToProcessRequest();
OI_EVENT("wsman: unable to process invoke request")
void trace_WsmanInvoke_UnableToProcessRequest();
OI_EVENT("wsman: unable to process Put-instance request")
void trace_WsmanPutInstance_UnableToProcessRequest();
OI_EVENT("wsman: unexpected close tag [%T] in incoming xml")
void trace_Wsman_UnexpectedCloseTag(const TChar * tag);
OI_EVENT("wsman: unknown custom action")
void trace_Wsman_UnknownCustomAction();
OI_EVENT("wsman: unknown dialect in enumeration: [%T]")
void trace_WsmanEnum_UnknownDialect(const TChar * dialect);
OI_EVENT("wsman: unknown mandatory tag [%T]; aborted")
void trace_Wsman_UnknownMandatoryTag(const TChar * tag);
OI_EVENT("wsman: unsupported action [%d]")
void trace_Wsman_UnsupportedAction(int rqtAction);
OI_EVENT("WsmanConnection: %p _ProcessInstanceConnectionData: expired")
void trace_WsmanConnection_ProcessInstance_Expired(void * selfCD);
OI_EVENT("WsmanConnection: %p _ProcessResultConnectionData: no request")
void trace_WsmanConnection_ProcessResult_NoRequest(void * selfCD);
OI_EVENT("WsmanConnection: %p _ProcessSchemaConnectionData: expired")
void trace_WsmanConnection_ProcessSchema_Expired(void * selfCD);

OI_EVENT("XmlSerializer_SerializeClass with flags %x")
void trace_XmlSerializer_SerializeClass(MI_Uint32 flags);

OI_EVENT("Cannot find enumerate context: %x")
void trace_Wsman_CannotFindEnumerateContext( MI_Uint32 enumerationContextID );

OI_EVENT("ProvMgr_Destroy: Join nonio thread result %d")
void trace_ProvMgr_Destroy_Join_nonioThread( PAL_Uint32 result );

OI_EVENT("_SubscrContext_ProcessResult: Thread %x: ctx (%p) subscription (%p); post final result to invalid subscription, state (%d) ")
void trace_SubscrContext_ProcessResult_InvalidState(unsigned int threadid, void* ctx, void* sub, unsigned int state);
OI_EVENT("Strand_StartTimer: unable to start timer(%p). Timer already executing on strand (%p)")
void trace_Strand_Cannot_Start_Timer(void* timer, void* strand);
OI_EVENT("Strand_FireTimer: Timer not initialized on strand (%p)")
void trace_Strand_Cannot_Fire_Timer(void* strand);

OI_EVENT("cannot open http trace file: %s, errno %d")
void trace_CannotOpenHttptraceFile(const char * file, int err);

OI_EVENT("IndiMgr_NewFromDisp: Failed to initialize IndicationHost with disp (%p)")
void trace_IndiMgr_NewFromDispFailed(void * disp);
OI_EVENT("_SubscribeEntry_Post: entry (%p) in status (%T), received unexpected final msg(%p:%d:%T:%x)")
void trace_SubscribeEntry_PostUnexpectedFinal(void * self, const TChar * iceStatus, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeEntry_Post: entry (%p) in status (%T), received unexpected SubscribeRes msg(%p:%d:%T:%x)")
void trace_SubscribeEntry_PostUnexpectedSubscribe(void * self, const TChar * iceStatus, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeEntry_Post: Unsupported msg(%p:%d:%T:%x)")
void trace_SubscribeEntry_PostUnsupportedMessage(Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("IndicationClassList_NewByFilter: No class found for filter (%T)")
void trace_IndicationClassList_NewByFilter_NoClassFound(const TChar * filterQuery);

OI_EVENT("IndiMgr_HandleSubscribeReq: StrandMany_New failed, req (%p)")
void trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed(void * req);
OI_EVENT("IndiMgr_HandleSubscribeReq: Failed to create All StrandEntries or All SubscribeReq msg; req (%p)")
void trace_IndiMgr_HandleSubscribeReq_FailedCreate(void * req);
OI_EVENT("Object %p is not a valid Subscription object.")
void trace_ObjectIsnotAValidSubscr(void * self);
OI_EVENT("Subscription_OnAdd: Object %p is not a valid Subscription object.")
void trace_Subscription_OnAdd_NotValidSubscr(void * self);
OI_EVENT("Subscription_OnAdd: Call CimBase_OnAdd Failed with %d.")
void trace_Subscription_OnAdd_CimBaseOnAddFailed(int r);
OI_EVENT("Subscription_OnAdd: Failed to add filter, error %d.")
void trace_Subscription_OnAdd_FailedAddFilter(int r);
OI_EVENT("Subscription_OnAdd: Failed to add listener, error %d.")
void trace_Subscription_OnAdd_FailedAddListener(int r);
OI_EVENT("Subscription_OnAdd: ProvReg object is NULL")
void trace_Subscription_OnAdd_ProvRegIsNull();
OI_EVENT("Subscription_OnRemove: Object %p is not a valid Subscription object.")
void trace_Subscription_OnRemove_NotValidSubscr(void * self);
OI_EVENT("Subscription_OnRemove: Failed to remove subscription %p from container %p.")
void trace_Subscription_OnRemove_RemoveFailed(void * self, void * container);
OI_EVENT("Subscription_OnRemove: Call IndiMgr_RemoveFilter() Failed with %d.")
void trace_Subscription_OnRemove_RemoveFilterFailed(int r);
OI_EVENT("Provider_InvokeSubscribe: Lifecycle context not initialized for class (%T).")
void trace_LifecycleSubscription_ContextNotInitialized(const TChar* className);

OI_EVENT("Dispatcher cannot allocate interaction")
void trace_Disp_ErrorInteractionAlloc();
OI_EVENT("Dispatcher cannot allocate EnumEntry")
void trace_Disp_ErrorEnumEntryAlloc();
OI_EVENT("Dispatcher cannot add entry")
void trace_Disp_ErrorAddEntry();

OI_EVENT("IndiMgr_HandleSubscribeReq: %p Out of memory")
void trace_IndiMgr_HandleSubscribe_Outofmemory(void * self);

OI_EVENT("WS_ParseSubscribeBody: Unsupported delivery mode %T")
void trace_Wsman_UnsupportedDeliveryMode(const TChar* mode);
OI_EVENT("WS_ParseSubscribeBody: Delivery mode expected, but not specified by client")
void trace_Wsman_ExpectedDeliveryMode();
OI_EVENT("_ValidateSubscribeRequest: Expires date %T is in the past")
void trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast(const TChar* expiresTime);
OI_EVENT("_ValidateSubscribeRequest: Wall clock time not supported")
void trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported();
OI_EVENT("_ValidateSubscribeRequest: Invalid duration specified.  Cannot be zero")
void trace_Wsman_SubscribeRequest_InvalidExpiresValue();
OI_EVENT("_ValidateSubscribeRequest: Heartbeat must be xs:duration")
void trace_Wsman_InvalidHeartbeatType();
OI_EVENT("_ValidateHeader: Unsupported requested action")
void trace_Wsman_InvalidActionRequest();
OI_EVENT("_ValidateHeader: Unsupported feature: connection retry")
void trace_Wsman_UnsupportedConnectionRetry();
OI_EVENT("_ValidatePullRequest: Invalid MaxTime specified.  Cannot be zero")
void trace_Wsman_PullRequest_InvalidMaxTimeValue();
OI_EVENT("Unable to convert specified timeout.  Using (%I64u) instead for request %d")
void trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER(PAL_Uint64 timeoutUsed, MI_Uint32 req);
OI_EVENT("Unable to convert specified timeout.  Using (%llu) instead for request %d")
void trace_Wsman_UnableToconvertDatetimeToUsec_POSIX(PAL_Uint64 timeoutUsed, MI_Uint32 req);
OI_EVENT("Heartbeat timeout: No PullRequest attached! Terminating enumeration context %p (%u)")
void trace_WsmanEnumerationcontext_HeartbeatMissingPull(void * self, MI_Uint32 enumerationContextID);
OI_EVENT("Heartbeat timeout: Timer cancelled for enumeration context %p (%u)")
void trace_WsmanEnumerationcontext_HeartbeatCancelled(void * self, MI_Uint32 enumerationContextID);
OI_EVENT("Operation timeout: Timer cancelled for connection data %p action (%d)")
void trace_WsmanConnectionData_OperationCancelled(void * self, int action);
OI_EVENT("Operation timeout: Timeout for connection data %p action (%d)")
void trace_WsmanConnectionData_OperationTimeout(void * self, int action);
OI_EVENT("_ValidateSubscribeRequest: The specified bookmark is invalid (empty)")
void trace_Wsman_SubscribeBookmark_Empty();

OI_EVENT("AgentMgr_HandleRequest: Access denied. User (%s) attempted to access class (%T) under namespace (%T) from an in-process provider.")
void trace_NonRootUserAccessInprocProvider(const char* username, const TChar* classname, const TChar* nameSpace);

OI_EVENT("child process with PID=[%d] terminated abnormally")
void trace_ChildProcessTerminatedAbnormally(int uid);

OI_EVENT("NTLM_USER_FILE environment variable [%s] ignored")
void trace_NtlmEnvIgnored(const char * ntlm_user_file);

OI_EVENT("SSL Compression was disabled in the OMI configuration, but the version of SSL used by OMI does not support it.")
void trace_Http_SslCompressionNotPresent();

OI_EVENT("Tracker hash map item already exists (%p, %d)")
void trace_TrackerHashMapAlreadyExists(void* handle, int socket);

OI_EVENT("Selector_AddHandler: selector=%p, handler=%p, name=%T ALREADY REGISTERED")
void trace_Selector_AddHandler_AlreadyThere(Selector * selector, Handler * handler, const TChar * name);
OI_EVENT("Selector_RemoveHandler: selector=%p, handler=%p, name=%T NOT REGISTERED")
void trace_Selector_RemoveHandler_NotThere(Selector * selector, Handler * handler, const TChar * name);


/******************************** INFORMATIONAL ***********************************/

OI_SETDEFAULT(PRIORITY(LOG_INFO))
OI_SETDEFAULT(STARTID(40000))
OI_SETDEFAULT(CHANNEL(Analytic))

OI_EVENT("disconnected form server; exiting")
void trace_Agent_DisconnectedFromServer();
OI_EVENT("sending 'agent-idle' notification to the server")
void trace_Agent_SendingIdleNotification();
OI_EVENT("changing idle timeout to %x sec")
void trace_Agent_ChangingIdleTimeout(MI_Uint64 idletimeout);
OI_EVENT("agent started; fd %d")
void trace_Agent_Started(int fd);
OI_EVENT("_SendErrorResponse, RequestItem: %p")
void trace_AgentMgr_SendErrorResponse(void * requestItem);
OI_EVENT("_SendRequestToAgent msg(%p:%d:%T:%x), from original operationId: %x to %x")
void trace_AgentMgr_SendRequestToAgent(Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId, MI_Uint64 from, MI_Uint64 to);
OI_EVENT("unknown class in enumerate request: %T:%T")
void trace_DispEnum_UnknownClass(const TChar * nameSpace, const TChar * className);
OI_EVENT("---> SSL: Loading server certificate from: %s")
void trace_SSL_LoadingServerCert(const char * source);
OI_EVENT("---> SSL: Loading certificate's private key from: %s")
void trace_SSL_LoadingCertPrivateKey(const char * source);
OI_EVENT("Sock_Accept() failed; err %d\n")
void trace_SockAccept_Failed(int err);
OI_EVENT("closing socket due to SELECTOR_REMOVE or SELECTOR_DESTROY")
void trace_SocketClose_REMOVEDESTROY();
OI_EVENT("done with receiving msg(%p:%d:%T:%x)")
void trace_Socket_ReceivedMessage(Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("Socket: %p, closing connection (mask %x)")
void trace_Socket_ClosingConnection(void * handler, MI_Uint32 mask);
OI_EVENT("Unloading idle providers")
void trace_UnloadingIdleProviders();
OI_EVENT("Received NoOpReqTag, terminateByNoop: %u")
void trace_ServerReceivedNoOpReqTag(int terminateByNoop);
OI_EVENT("after run, r %d")
void trace_Server_ProtocolRun(MI_Result r);
OI_EVENT("livetime expired; server stopped")
void trace_Server_LiveTimeExpired();
OI_EVENT("server terminated")
void trace_ServerTerminated();
OI_EVENT("re-reading configuration")
void trace_ServerReReadingConfig();
OI_EVENT("%s exiting")
void trace_ServerExiting(const char * server);
OI_EVENT("WsmanEnum: %p, Delaying response")
void trace_WsmanEnum_DelayingResponse(void * selfEC);
OI_EVENT("includeClassOrigin = %d includeInheritanceHierarchy = %d includeInheritedElements = %d includeQualifiers = %d usePreciseArrays = %d")
void trace_GetFlagsFromWsmanOptions(int includeClassOrigin, int includeInheritanceHierarchy, int includeInheritedElements, int includeQualifiers, int usePreciseArrays);
OI_EVENT("listening on port: http %u")
void trace_ListeningOnPort(unsigned short httpport);
OI_EVENT("listening on port: https %u")
void trace_ListeningOnEncryptedPort(unsigned short httpport);

OI_EVENT("Executed PREEXEC program: {%s}")
void trace_PreExecOk(const char* path);

OI_EVENT("SubMgr_CanPostIndication: Thread %x: it is not supported to post indication on the thread invoking EnableIndication and Subscribe")
void trace_SubMgr_CanPostIndication_Fail(unsigned int threadid);

OI_EVENT("_SubscriptionList_EnsureArray: Thread %x: subscription list capacity overflowed")
void trace_SubscriptionList_EnsureArray_Overflow(unsigned int threadid);
OI_EVENT("WS_ParseSubscribeBody: Delivery mode %T specified")
void trace_Wsman_DeliveryMode(const TChar* mode);

OI_EVENT("Socket: %p, Connection Closed while reading header\n")
void trace_Socket_ReadHeader_ConnectionClosed(void * handler);
OI_EVENT("Socket: %p, Connection Closed while reading\n")
void trace_Socket_Read_ConnectionClosed(void * handler);

OI_EVENT("RequestList_ScheduleItem: Failed to create non-io thread. error (%d : %T)")
void trace_RequestList_ScheduleItem_CreateNonIOThreadFailed(int err, const TChar* errmsg);

OI_EVENT("agent running as [%d] closed its connection to the server")
void trace_AgentClosedConnection(int uid);

OI_EVENT("Selector_AddHandler: selector=%p, handler=%p, name=%T")
void trace_Selector_AddHandler(void * selector, void * handler, const MI_Char * name);
OI_EVENT("Selector_RemoveHandler: selector=%p, handler=%p, name=%T")
void trace_Selector_RemoveHandler(void * selector, void * handler, const MI_Char * name);
OI_EVENT("Selector_RemoveAllHandlers: selector=%p, handler=%p, name=%T")
void trace_Selector_RemoveAllHandlers(void * selector, void * handler, const MI_Char * name);
OI_EVENT("Server failed to authenticate user: (%s)")
void trace_ServerFailedPamCheckUser(const char* user);
OI_EVENT("SIGHUP received at: (%s)")
void trace_SigHUP_received(const char* user);
OI_EVENT("SIGTERM received at: (%s)")
void trace_SigTERM_received(const char* user);
OI_EVENT("Starting %s: version: (%s), platform: (%s)")
void trace_Product_Version(const char* product, const char* version, const char* platform);
OI_EVENT("New request received: command=(%T), namespace=(%T), class=(%T)")
void trace_New_Request(const TChar* cmd, const TChar* namespace, const TChar* class);

/******************************** DEBUG TRACES ***********************************/

OI_SETDEFAULT(PRIORITY(LOG_DEBUG))
OI_SETDEFAULT(STARTID(45000))
OI_SETDEFAULT(CHANNEL(Debug))

OI_EVENT("LOGTRACE: %s(%u)")
void trace_FunctionEntered(const char * file, int line);
OI_EVENT("Batch_Zdup() failed: out of memory")
void trace_BatchZdup_Failed();
OI_EVENT("Batch allocation failed: out of memory")
void trace_BatchAllocFailed();
OI_EVENT("Batch creation failed: out of memory")
void trace_BatchCreationFailed();
OI_EVENT("Heap memory allocation failed: out of memory")
void trace_HeapMemoryAllocFailed();

OI_EVENT("MessageFromBatch:- msg tag is %d, index: %d")
void trace_MessageFromBatch(MI_Uint32 msgTag, int index);
OI_EVENT("AgentElem: Posting message for interaction [%p]<-%p")
void trace_AgentElemPostingMessage(Interaction * interaction, Interaction * other);
OI_EVENT("AgentElem: Ack on interaction [%p]<-%p")
void trace_AgentElemAck(Interaction * interaction, Interaction * other);
OI_EVENT("_AgentElem_FindRequest, Agent %p(%p), Found key: %x, Request: %p(%p)")
void trace_AgentElemFoundKey(void * agent, Strand * agentStrand, MI_Uint64 key, void * self, Strand * selfStrand);
OI_EVENT("RequestItem: %p Posting message for interaction [%p]<-%p")
void trace_RequestItemPostingMessage(Strand * self, Interaction * interaction, Interaction * other);
OI_EVENT("RequestItem: Ack on interaction [%p]<-%p")
void trace_RequestItemAck(Interaction * interaction, Interaction * other);
OI_EVENT("_RequestItem_Cancel: on RequestItem (%p))")
void trace_RequestItemCancel(Strand * item);
OI_EVENT("_SendMessageToAgent msg tag = %d")
void trace_SendMessageToAgent(int tag);
OI_EVENT("_PreExecRequest_Failed preexec = %u")
void trace_PreExecRequest_Failed(const TChar * preexec);
OI_EVENT("AgentMgr_HandleRequest %p (tag %d)")
void trace_AgentMgrHandleRequest(void * requestMsg, int msgTag);
OI_EVENT("ProvReg_BeginClasses() failed: %u: %T")
void trace_ProvReg_BeginClasses_Failed(unsigned short error, const TChar * message);
OI_EVENT("ProvReg_NextClass() failed: %u: %T")
void trace_ProvReg_NextClass_Failed(unsigned short error, const TChar * message);
OI_EVENT("ProvReg_EndClasses() failed: %u: %T")
void trace_ProvReg_EndClasses_Failed(unsigned short error, const TChar * message);
OI_EVENT("ProvReg_BeginAssocClasses() failed: %u: %T")
void trace_ProvReg_BeginAssocClasses_Failed(unsigned short error, const TChar * message);
OI_EVENT("ProvReg_NextAssocClass() failed: %u: %T")
void trace_ProvReg_NextAssocClass_Failed(unsigned short error, const TChar * message);
OI_EVENT("ProvReg_EndAssocClasses() failed: %u: %T")
void trace_ProvReg_EndAssocClasses_Failed(unsigned short error, const TChar * message);
OI_EVENT("found no providers for class: %T")
void trace_FoundNoProvider(const TChar * className);

OI_EVENT("Disp: delete interaction [%p]")
void trace_DispDeleteInteraction(void * self);
OI_EVENT("_DispatchEnumerateInstancesReq() for class: %T (Thru Dispatcher Interaction)")
void trace_DispatchEnumDispInteraction(const TChar * className);
OI_EVENT("_DispatchEnumerateInstancesReq() for class: %T (Directly)")
void trace_DispatchEnumDirectly(const TChar * className);
OI_EVENT("_DispatchAssocReq() for class: %T")
void trace_DispatchAssoc(const TChar * className);
OI_EVENT("Disp: Posting message for enum/assoc/ref interaction %p<-[%p]")
void trace_DispPostingMessage(Interaction * other, void * self);
OI_EVENT("Disp: Ack on base interaction [%p]<-%p")
void trace_DispAckBaseInteraction(Strand * self, Interaction * rightOther);

OI_EVENT("cannot find provider for class: %T/%T")
void trace_NoProviderForClass(const TChar * nameSpace, const TChar * className);
OI_EVENT("IndiMgr_HandleSubscribeReq() returns: %u")
void trace_IndiMgrHandleSub(MI_Result r);
OI_EVENT("class name is expected for invoke")
void trace_ClassNameIsExpectedForInvoke();
OI_EVENT("Disp_HandleInteractionRequest: self (%p), interaction(%p), msg(%p:%d:%T:%x)")
void trace_DispHandleInteractionRequest(void * self, Interaction * interaction, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("Disp_HandleInteractionRequest: self (%p), interaction(%p), Unsupported msg(%p:%d:%T:%x)")
void trace_DispUnsupportedMessage(void * self, Interaction * interaction, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("Disp_HandleRequest")
void trace_DispHandlRequest();

OI_EVENT("HttpSocket: Posting message for interaction [%p]<-%p")
void trace_HttpSocketPosting(Interaction * interaction, Interaction * other);
OI_EVENT("HttpSocket: Ack on interaction [%p]<-%p")
void trace_HttpSocketAck(Interaction * interaction, Interaction * other);
OI_EVENT("HttpSocket: %p _HttpSocket_Finish")
void trace_HttpSocketFinish(Strand * self);
OI_EVENT("HttpSocket: %p _HttpSocket_Aux_NewRequest, Request: %p")
void trace_HttpSocketAuxNewRequest(void * self, void * request);
OI_EVENT("_RequestItem_ParentPost: %p, msg: %p")
void trace_RequestItemParentPost(void * requestItem, Message * msg);
OI_EVENT("AgentItem created: %p")
void trace_AgentItemCreated(void * agent);
OI_EVENT("_DiscoverClassAndChildrenClasses: Found %T class (%T)")
void trace_DiscoverClassesFoundTypeClass(const TChar * regType, const TChar * className);
OI_EVENT("_DiscoverClassAndChildrenClasses: Failed to add ProvRegEntry for class (%T), error code (%d)")
void trace_DiscoverClassesFailedToAdd(const TChar * className, MI_Result r);
OI_EVENT("_DiscoverClassAndChildrenClasses: No reginfo for %T class (%T) under namespace (%T)")
void trace_DiscoverClassesNoRegInfo(const TChar * regType, const TChar * className, const TChar * nameSpace);
OI_EVENT("_DiscoverClassAndChildrenClasses: ProvReg_BeginClasses failed: %u: %T; namespace (%T), classname (%T)")
void trace_DiscoverClassesBeginFailed(MI_Result r, const TChar * regType, const TChar * className, const TChar * nameSpace);
OI_EVENT("_DiscoverClassAndChildrenClasses: ProvReg_NextClass failed: %u: %T; namespace (%T), classname (%T)")
void trace_DiscoverClassesNextFailed(MI_Result r, const TChar * regType, const TChar * className, const TChar * nameSpace);
OI_EVENT("_DiscoverClassAndChildrenClasses: Failed to add ProvRegEntry for class (%T), error (%d).")
void trace_DiscoverClassesBeginFailedProvRegEntry(const TChar * className, MI_Result r);
OI_EVENT("_DiscoverClassAndChildrenClasses: ProvReg_EndClasses failed: %u: %T")
void trace_DiscoverClassesEndFailed(MI_Result r, const TChar * error);
OI_EVENT("_DiscoverIndicationClass: Found %d classes")
void trace_DiscoverIndicationFoundClasses(MI_Uint32 classcount);
OI_EVENT("IndicationClassList_NewByFilter: created clist(%p) succeed")
void trace_IndicationClassListCreated(void * clist);
OI_EVENT("IndicationClassList_Delete: self(%p)")
void trace_IndicationClassListDelete(void * self);
OI_EVENT("IndicationClassList_Delete: self(%p) complete")
void trace_IndicationClassListDeleteCompleted(void * self);

OI_EVENT("Queueing on socket: %p")
void trace_QueueingSocket(void * handler);
OI_EVENT("__FindSubRequest: SubscribeElem %p(%p), Found key: %x, Request: %p(%p)")
void trace_FindSubRequest_FoundKey(void * subelem, Strand * subelemStrand, MI_Uint64 key, void * self, Strand * selfStrand);
OI_EVENT("_ConnectionIn_Aux_PostOther: %p, posting msg(%p:%d:%T:%x)")
void trace_ConnectionInAuxPostOther(Strand * self, Message * msg, int msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_ConnectionIn_Close: Closed on interaction [%p]<-%p")
void trace_ConnectionInClose(Interaction * interaction, Interaction * other);
OI_EVENT("_ConnectionIn_FindRequest, Agent %p(%p), Cannot find key: %x (may be new request)")
void trace_ConnectionInFindRequest_CannotFind(void * parent, Strand * strand, MI_Uint64 key );
OI_EVENT("_ConnectionIn_FindRequest, Agent %p(%p), Found key: %x, Request: %p(%p)")
void trace_ConnectionInFindRequest_Found(void * parent, Strand * parentStrand, MI_Uint64 key, void * self, Strand * selfStrand );
OI_EVENT("_ConnectionIn_Post: %p Post msg(%p:%d:%T:%x) for interaction [%p]<-%p")
void trace_ConnectionIn_Post(void * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId, Interaction * selfInteraction, Interaction * otherInteraction);
OI_EVENT("_ConnectionIn_Post: New operation with operationId (%p), msg (%p:%T)")
void trace_ConnectionInPost_NewOp(void * operationId, void * msg, const TChar * msgname);
OI_EVENT("ConnectionIn: %p Post cancel msg(%p:%d:%T:%x) on interaction [%p]<-%p")
void trace_ConnectionIn_PostCancel(void * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId, Interaction * selfInteraction, Interaction * otherInteraction);

OI_EVENT("_Context_Aux_PostLeft: %p, thisAckPending: %d")
void trace_ContextAuxPostLeft(Strand * self, MI_Boolean thisAckPending );
OI_EVENT("_Context_Aux_PostLeft_Notify: %p")
void trace_ContextAuxPostLeftNotify(Strand * self );
OI_EVENT("_Context_Aux_PostLeft_Notify(IoThread): %p")
void trace_ContextAuxPostLeftNotify_IoThread(Strand * self );
OI_EVENT("Context_PostMessageLeft_IoThread: %p")
void Context_PostMessageLeft_IoThread(void * self );

OI_EVENT("SelectorRun(Enter): %p")
void trace_SelectorRun_Enter(void * self, MI_Uint64 timeoutUsec, MI_Boolean noReadsMode );
OI_EVENT("SelectorRun(Exit): %p")
void trace_SelectorRun_Exit(void * self );
OI_EVENT("SelectorRun(Exit-Timeout): %p")
void trace_SelectorRun_Exit_Timeout(void * self );

OI_EVENT("_Context_Cancel: self (%p)")
void trace_ContextCancel(Strand * self);
OI_EVENT("_Context_Close: Close on context %p, interaction %p->[%p]")
void trace_ContextClose(Strand * self, Interaction * other, Interaction * selfInteraction);

OI_EVENT("Context: %p, finish called")
void trace_ContextFinish(Strand * self);
OI_EVENT("Context: Ack on context %p, interaction %p->[%p], (Transport Closed: ByThis: %d, ByOther: %d), tryingToPostLeft: %x")
void trace_ContextAck(Strand * self, Interaction * otherInteraction, Interaction * selfInteraction, MI_Boolean thisClosedOther, MI_Boolean otherClosedThis, ptrdiff_t tryingToPostLeftValue);
OI_EVENT("Context: Destroy %p (strand: %p, interaction [%p])")
void trace_ContextDestroy(void * self, Strand * strand, Interaction * interaction);
OI_EVENT("Context: New context %p with interaction: %p->[%p]")
void trace_ContextNew(void * self, Interaction * otherInteraction, Interaction * selfInteraction);

OI_EVENT("OperationOut: Ack on interaction [%p]<-%p")
void trace_OperationOut_Ack(Interaction * self, Interaction * otherInteraction);
OI_EVENT("_OperationOut_Cancel: on OperationOut (%p))")
void trace_OperationOut_Cancel(Strand * self);
OI_EVENT("OperationOut: Close on interaction [%p]<-%p")
void trace_OperationOut_Close(Interaction * self, Interaction * otherInteraction);
OI_EVENT("ConnectionIn: Ack on interaction [%p]<-%p")
void trace_OperationIn_Ack(Interaction * self, Interaction * otherInteraction);

OI_EVENT("Disp EnumDone (%p) total: %d Result: %d")
void trace_DispEnumDone(void * self, int total, int result);
OI_EVENT("Disp EntryDeleted total: %d Done %d")
void trace_DispEntryDeleted(void * self, int total, int done);

OI_EVENT("_IndiMgr_SetLastError: self (%p) result(%d), error(%p)")
void trace_IndiMgr_SetLastError(void * mgr, MI_Result result, void * errordetails);
OI_EVENT("IndiMgr_New: created IndicationManager (%p)")
void trace_IndiMgr_New(void * mgr);
OI_EVENT("IndiMgr_Delete: self (%p)")
void trace_IndiMgr_Delete(void * mgr);
OI_EVENT("IndiMgr_Shutdown: self (%p)")
void trace_IndiMgr_Shutdown(void * mgr);

OI_EVENT("IndiMgr_AddFilter: self (%p), filter (%p)")
void trace_IndiMgr_AddFilter(void * self, void * filter);
OI_EVENT("IndiMgr_RemoveFilter: self (%p), filter (%p)")
void trace_IndiMgr_RemoveFilter(void * self, void * filter);
OI_EVENT("IndiMgr_RemoveFilter: Filter (%p) was not removed from IndicationManager (%p)")
void trace_IndiMgr_FilterNotRemoved(void * self, void * filter);
OI_EVENT("IndiMgr_AddListener: self (%p), listener (%p)")
void trace_IndiMgr_AddListener(void * self, void * listener);
OI_EVENT("IndiMgr_RemoveListener: self (%p), listener (%p)")
void trace_IndiMgr_RemoveListener(void * self, void * listener);
OI_EVENT("IndiMgr_RemoveListener: Listener (%p) was not removed from IndicationManager (%p)")
void trace_IndiMgr_ListenerNotRemoved(void * listener, void * self);
OI_EVENT("IndiMgr_AddSubscription: self (%p), subscrip (%p)")
void trace_IndiMgr_AddSubscription(void * self, void * subscrip);
OI_EVENT("IndiMgr_RemoveSubscription: self (%p), subscrip (%p)")
void trace_IndiMgr_RemoveSubscription(void * self, void * subscrip);
OI_EVENT("IndiMgr_RemoveSubscription: Subscription (%p) was not removed from IndicationManager (%p)")
void trace_IndiMgr_SubscriptionNotRemoved(void * subscrip, void * self);

OI_EVENT("Object %T already exists.")
void trace_IndiMgr_ObjectExists(const TChar * identifier);
OI_EVENT("_List_RemoveObjectByID: Cannot find object (%T)")
void trace_IndiMgr_CannotFindObject(const TChar * identifier);

OI_EVENT("_SubscribeElem_Post: self (%p), msg(%p:%d:%T:%x) complete")
void trace_SubElem_PostComplete(StrandMany * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_Post: self (%p), msg(%p:%d:%T:%x), cancel all SubscribeEntries")
void trace_SubElem_PostCancelSubscribe(StrandMany * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_Post: self (%p), unsupported msg(%p:%d:%T:%x)")
void trace_SubElem_Post(StrandMany * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_Ack: self (%p) interaction [%p]<-%p")
void trace_SubElem_Ack(Strand * self, Interaction * selfInteraction, Interaction * otherInteraction);
OI_EVENT("_SubscribeElem_Cancel: self (%p) interaction [%p]<-%p")
void trace_SubElem_Cancel(StrandMany * self, Interaction * selfInteraction, Interaction * otherInteraction);
OI_EVENT("_SubscribeElem_Finish: self (%p) interaction [%p]<-%p")
void trace_SubElem_Finish(void * self, Interaction * selfInteraction, Interaction * otherInteraction);
OI_EVENT("_SubscribeElem_CheckSendFinalResult: self(%p)")
void trace_SubElem_CheckSendFinalResult(void * self);
OI_EVENT("_SubscribeElem_CheckSendFinalResult: self (%p) status (%T); (%d) classes was handled; send final result message to protocol and closed self")
void trace_SubElem_CheckSendComplete(void * se, const TChar * status, MI_Uint32 nHandled);
OI_EVENT("_SubscribeElem_NewEntry: self(%p) newEntry(%p) msg(%p:%d:%T:%x)")
void trace_SubElem_NewEntry(StrandMany * self, StrandEntry * newEntry, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_NewEntry: Unexpected msg(%p:%x:%T:%x)")
void trace_SubElem_NewEntry_UnexpectedMessage(Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeItem_Added: self(%p) handle request namespace(%T), class(%T)")
void trace_SubItem_HandleRequest(void * self, const TChar * nameSpace, const TChar * className);
OI_EVENT("_SubscribeElem_NewEntry: DONE. self(%p); Classes: (%d)Scheduled; (%d)Sent; (%d)Handled (%d)Subscribed (%d)Failed (%d)Complete; Aggregate result (%d)")
void trace_SubElement_NewDone(StrandMany * self, MI_Uint32 nScheduled, MI_Uint32 nSent, MI_Uint32 nHandled, MI_Uint32 nSubscribed, MI_Uint32 nFailed, MI_Uint32 nComplete, MI_Uint32 aggrresult);

OI_EVENT("_SubscribeElem_EntryPost: Posting message for interaction [%p]<-%p; msg(%p:%d:%T:%x)")
void trace_SubElem_EntryPost(Interaction * self, Interaction * other, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_EntryPost: self (%p) status (%T); send success response to protocol")
void trace_SubElem_PostSendSuccessResponse(void * self, const TChar * status);
OI_EVENT("_SubscribeElem_EntryPost: Self (%p) received msg(%p:%d:%T:%x), pass to left")
void trace_SubElem_EntryPost_PassToLeft(void * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeElem_EntryPost: DONE. self(%p); Classes: (%d)Scheduled; (%d)Sent; (%d)Handled (%d)Subscribed (%d)Failed (%d)Complete; Aggregate result (%d)")
void trace_SubElem_EntryPostDone(void * self, MI_Uint32 nScheduled, MI_Uint32 nSent, MI_Uint32 nHandled, MI_Uint32 nSubscribed, MI_Uint32 nFailed, MI_Uint32 nComplete, MI_Uint32 aggrresult);
OI_EVENT("_SubscribeElem_EntryClose: Done")
void trace_SubElem_EntryClose();

OI_EVENT("IndiMgr_HandleSubscribeReq: self (%p) interaction (%p) req (%p : OPID=%x)")
void trace_IndiMgr_HandleSubscribe(void * self, Interaction * interaction, void * request, MI_Uint64 opid);
OI_EVENT("IndiMgr_HandleSubscribeReq: invalid parameter(s)")
void trace_IndiMgr_HandleSubscribe_InvalidParameters();
OI_EVENT("IndiMgr_HandleSubscribeReq: Failed to set namespace to filter (%p), req (%p).")
void trace_IndiMgr_HandleSubscribe_FailedToSetNamespace(void * filter, void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: Failed to add subscription (%p), req (%p)")
void trace_IndiMgr_HandleSubscribe_FailedToAddSub(void * filter, void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: No class found, req(%p)")
void trace_IndiMgr_HandleSubscribe_NoClassFound(void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: Failed to create subscribereq message for class %T, req (%p)")
void trace_IndiMgr_HandleSubscribe_FailedToCreateMessage(const TChar * className, void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: begin to add entry (%p) msg (%p:%T), req(%p)")
void trace_IndiMgr_HandleSubscribe_BeginAddingEntry(void * entry, Message * message, const TChar * className, void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: end add entry (%p), req (%p)")
void trace_IndiMgr_HandleSubscribe_AddingEntryDone(void * entry, void * request);
OI_EVENT("IndiMgr_HandleSubscribeReq: self (%p) interaction (%p) req (%p : OPID=%x); done result (%d)")
void trace_IndiMgr_HandleSubscribe_Done(void * self, Interaction * interaction, void * request, MI_Uint64 opid, MI_Result result);

OI_EVENT("Subscription_Finalize: self(%p)")
void trace_Subscription_Finalize(void * self);
OI_EVENT("Subscription_OnAdd: self(%p), container (%p)")
void trace_Subscription_OnAdd(void * self, void * container);
OI_EVENT("Subscription_OnAdd: Failed to create class list")
void trace_Subscription_OnAdd_Failed();
OI_EVENT("Subscription_OnAdd: self(%p), container (%p) succeed")
void trace_Subscription_OnAdd_Success(void * self, void * container);
OI_EVENT("Subscription_OnRemove: self(%p), container (%p)")
void trace_Subscription_OnRemove(void * self, void * container);
OI_EVENT("Subscription_OnRemove: self(%p), container (%p), result (%d)")
void trace_Subscription_OnRemove_Result(void * self, void * container, int r);

OI_EVENT("InteractionProtocolHandler_Client_Ack_PostToInteraction %p")
void trace_InteractionProtocolHandler_Client_Ack_Post(void * operation);
OI_EVENT("InteractionProtocolHandler_Client_Ack_NoPostToInteraction %p")
void trace_InteractionProtocolHandler_Client_Ack_NoPost(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Post: %p, msg(%p:%d:%T:%x)")
void trace_InteractionProtocolHandler_Operation_StrandPost(void * self, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("MI_Result = %T")
void trace_MIResult(const TChar * result);
OI_EVENT("NoOpRspTag")
void trace_InteractionProtocolHandler_NoopRspTag();
OI_EVENT("InteractionProtocolHandler_Operation_Strand_PostControl %p")
void trace_InteractionProtocolHandler_Operation_Strand_PostControl(void * operation);
OI_EVENT("==== InteractionProtocolHandler_Session_ConnectionEvents() PROTOCOLEVENT_CONNECT")
void trace_InteractionProtocolHandler_Session_ProtocolConnecting();
OI_EVENT("==== InteractionProtocolHandler_Session_ConnectionEvents() PROTOCOLEVENT_CONNECT_FAILED")
void trace_InteractionProtocolHandler_Session_ConnectFailed();
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Ack %p")
void trace_InteractionProtocolHandler_Operation_Strand_Ack(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Cancel %p")
void trace_InteractionProtocolHandler_Operation_Strand_Cancel(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Close %p")
void trace_InteractionProtocolHandler_Operation_Strand_Close(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Finish %p")
void trace_InteractionProtocolHandler_Operation_Strand_Finish(void * operation);

OI_EVENT("InteractionProtocolHandler_Operation_Close %p")
void trace_InteractionProtocolHandler_Operation_Close(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Cancel %p")
void trace_InteractionProtocolHandler_Operation_Cancel(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Cancel %p -- ignoring because we have already posted the final result")
void trace_InteractionProtocolHandler_Operation_CancelAfterFinal(void * operation);

OI_EVENT("InteractionProtocolHandler_Session_Close %p (CompletionCallback %p)")
void trace_InteractionProtocolHandler_Session_Close(void * session, void * completionCallback);

OI_EVENT("InteractionProtocolHandler_Protocol_RunThread")
void trace_InteractionProtocolHandler_Protocol_RunThread();
OI_EVENT("InteractionProtocolHandler_Protocol_RunThread finished with return %u")
void trace_InteractionProtocolHandler_Protocol_RunThread_WithResult(MI_Result miResult);
OI_EVENT("SessionCloseCompletion_Release %p with CompletionCallback %p")
void trace_SessionCloseCompletion_Release_CompletionCallback(void * completion, void * completionCallback);
OI_EVENT("SessionCloseCompletion_Release %p count is %d")
void trace_SessionCloseCompletion_Release_Count(void * completion, int count);

OI_EVENT("InteractionProtocolHandler_Session_Connect passed !")
void trace_InteractionProtocolHandler_SessionConnect_Passed();

OI_EVENT("ProtocolSocket: triggering timeout on %p")
void trace_ProtocolSocket_TimeoutTrigger(void * self);
OI_EVENT("ProtocolSocket: Posting message for interaction [%p]<-%p")
void trace_ProtocolSocket_PostingOnInteraction(Interaction * self, Interaction * otherInteraction);
OI_EVENT("ProtocolSocket: Post for interaction [%p]<-%p FAILED")
void trace_ProtocolSocket_PostFailed(Interaction * self, Interaction * otherInteraction);
OI_EVENT("ProtocolSocket: Cancel received (closed other: %d) on interaction [%p]<-%p")
void trace_ProtocolSocket_CancelReceived(MI_Boolean closedOther, Interaction * self, Interaction * otherInteraction);
OI_EVENT("ProtocolSocket: Ack on interaction [%p]<-%p")
void trace_ProtocolSocket_Ack(Interaction * self, Interaction * otherInteraction);
OI_EVENT("ProtocolSocket: Close received (closed other: %d) on interaction [%p]<-%p")
void trace_ProtocolSocket_Close(MI_Boolean closedOther, Interaction * self, Interaction * otherInteraction);
OI_EVENT("ProtocolSocket: %p _ProtocolSocket_Finish")
void trace_ProtocolSocket_Finish(void * self);
OI_EVENT("Socket: %p, All send")
void trace_SocketSendCompleted(void * handler);

OI_EVENT("Protocol _RequestCallback: _RequestCallbackRead fails for ProtocolSocket %p")
void trace_RequestCallbackRead_Failed(void * handler);
OI_EVENT("Protocol _RequestCallback: scheduling connect event on first read for ProtocolSocket %p")
void trace_RequestCallback_Connect_OnFirstRead(void * handler);
OI_EVENT("Protocol _RequestCallback: scheduling connect event on first write for ProtocolSocket %p")
void trace_RequestCallback_Connect_OnFirstWrite(void * handler);
OI_EVENT("Protocol _RequestCallback: closing %p after mask %x")
void trace_RequestCallback_Connect_ClosingAfterMask(void * handler, MI_Uint32 mask);
OI_EVENT("Protocol _RequestCallback: removing %p (mask %x, prev: %x)")
void trace_RequestCallback_Connect_RemovingHandler(void * handler, MI_Uint32 mask, MI_Uint32 prev);

OI_EVENT("post result from provider, %d")
void trace_Provider_PostResult(MI_Result result);
OI_EVENT("EvaluateIndication with NULL input parameter")
void trace_EvaluateIndicationWithNull();
OI_EVENT("PostIndication with unsubscribed context")
void trace_PostIndicationWithUnsubscribedContext();
OI_EVENT("Terminate with NULL provider")
void trace_TerminateWithNullProvider();
OI_EVENT("_SubscrContext_ProcessResult: Provider posted failure result (%d) while %T subscription (%p). Send final result")
void trace_SubscrContext_ProviderPostingFailure(MI_Result result, const TChar * state, void * subscr);
OI_EVENT("PostIndication with NULL input parameter")
void trace_PostIndicationWithNullInput();
OI_EVENT("PostIndication on disabled aggregation context")
void trace_PostIndicationOnDisabledAggContext();
OI_EVENT("Post called with invalid context")
void trace_PostCalledWithInvalidContext();

OI_EVENT("Unknown indication context type %d")
void trace_UnknownIndicationContextType(int ctxType);
OI_EVENT("_SubscribeContext_Cancel: self (%p);")
void trace_SubscribeContext_Cancel(void * self);
OI_EVENT("_SubscribeContext_Cancel: unsubscribe self (%p) done")
void trace_SubscribeContext_CancelDone(void * self);
OI_EVENT("Create filter with NULL input parameter")
void trace_CreateFilterWithNullInput();
OI_EVENT("Evaluate WQL with NULL input parameter")
void trace_EvaluateWQLWithNullInput();
OI_EVENT("_GetProviderByClassName{%T}")
void trace_GetProviderByClassName(const TChar * className);
OI_EVENT("InitIndication with NULL input parameter")
void trace_InitIndicationWithNullInput();
OI_EVENT("Multiple indication initialization of provider for class %T")
void trace_MultipleIndication_InitOfProviderForClass(const TChar * className);

OI_EVENT("_Provider_InvokeSubscribe: Start  Thread %x: provider (%p), msg (%p) with tag (%d), subcription (%p)")
void trace_ProviderInvokeSubscribe_Begin(unsigned int threadid, void * provider, void * message, MI_Uint32 tag, void* subs);
OI_EVENT("_Provider_InvokeSubscribe: Complete Thread %x: provider (%p), result (%d)")
void trace_ProviderInvokeSubscribe_End(unsigned int threadid, void * provider, MI_Result result);
OI_EVENT("Cannot unload NULL provider")
void trace_CannotUnloadNullProvider();
OI_EVENT("Posting schema in wsman form to callback from provmgr")
void trace_ProvMgr_PostingSchemaInWsmanToCallback();
OI_EVENT("Class not found %T")
void trace_ProvMgr_ClassNotFound(const TChar * className);
OI_EVENT("enumerate instances of %T")
void trace_ProvMgr_EnumerateInstancesOfClass(const TChar * className);
OI_EVENT("Unloading provider %T")
void trace_ProvMgr_UnloadingProvider(const TChar * provider);
OI_EVENT("Unloading lib %s")
void trace_ProvMgr_UnloadingLibrary(const char * library);
OI_EVENT("ProvMgr_NewRequest: Unsupported message (%p:%T)")
void trace_ProvMgr_NewRequest_UnsupportedMessage(Message * message, const TChar * messageName);

OI_EVENT("Close with existing subscriptions")
void trace_CloseWithExistingSubscriptions();
OI_EVENT("SubMgr_CancelAllSubscriptions: Thread %x: mgr (%p)")
void trace_SubMgr_CancelAllSubscriptions(unsigned int threadid, void * mgr);
OI_EVENT("No subscriptions present")
void trace_GetSubscription_NoSubscrPresent();

OI_EVENT("AddFilter with NULL input parameter")
void trace_AddFilter_NullParameter();
OI_EVENT("SendResp with NULL input parameter")
void trace_SendResp_NullParameter();
OI_EVENT("SubscriptionContext init with NULL input")
void trace_SubscriptionContext_NullParameter();

OI_EVENT("SubscrContext_SendFinalResultMsg: subCtx (%p) result (%d)")
void trace_SubscrContext_SendFinalResultMsg(void * subCtx, MI_Result result);
OI_EVENT("SubscrContext_SendFinalResultMsg: subCtx (%p), result %d, msg(%p:%T) sent")
void trace_SubscrContext_SendFinalResultMsg_Sent(void * subCtx, MI_Result result, void * message, const TChar * messageName);
OI_EVENT("SubscrContext_SendSubscribeResponseMsg: subCtx (%p)")
void trace_SubscrContext_SendSubscribeResponseMsg(void * subCtx);
OI_EVENT("SubscrContext_SendSubscribeResponseMsg: subCtx (%p), msg(%p:%T) sent")
void trace_SubscrContext_SendSubscribeResponseMsg_Sent(void * subCtx, void * message, const TChar * messageName);
OI_EVENT("SubscrContext_Unsubscribe: subCtx (%p), provider (%p), subscription (%p) start")
void trace_SubscrContext_Unsubscribe(void * subCtx, void * provider, void * subscription);
OI_EVENT("Subscription (%p) was already unsubscribed")
void trace_SubscrContext_AlreadyUnsubscribed(void * subscription);
OI_EVENT("Subscription state %u is invalid for unsubscribe on class %T")
void trace_Subscription_StateInvalid(int state, const TChar * className);
OI_EVENT("SubscrContext_Unsubscribe: subCtx (%p), provider (%p), subscription (%p); Complete")
void trace_SubscrContext_UnsubscribeDone(void * subCtx, void * provider, void * subscription);

OI_EVENT("SubscrContext_UnsubprvdOrSendfinalmsg: subCtx (%p), provider (%p), subscription (%p), invokeUnsubscribe(%d); start")
void trace_SubscrContext_UnsubprvdOrSendfinalmsgStart(void * subCtx, void * provider, void * subscription, MI_Boolean invokeUnsubscribe);
OI_EVENT("SubscrContext_UnsubprvdOrSendfinalmsg: subCtx (%p), provider (%p), subscription (%p), invokeUnsubscribe(%d); Complete")
void trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish(void * subCtx, void * provider, void * subscription, MI_Boolean invokeUnsubscribe);

OI_EVENT("Parse indication class value failed.")
void trace_RegFile_ParseIndication_ClassValueFailed();
OI_EVENT("Allocate memory for RegClass failed.")
void trace_RegFile_AllocFailure();
OI_EVENT("Indication class can not have reference class.")
void trace_RegFile_IndicationClassCannotHaveRefClass();
OI_EVENT("Out of memory when duplicating name.")
void trace_RegFile_OutOfMemory_Name();
OI_EVENT("Out of memory when duplicating hosting.")
void trace_RegFile_OutOfMemory_Hosting();

OI_EVENT("Sending msg(%p:%d:%T:%x) on own thread")
void trace_Sock_SendingOnOwnThread(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("Sending msg(%p:%d:%T:%x), outstandingInstances: %d, MAX: %d, numberOfItem: %d")
void trace_Sock_Sending(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId, ptrdiff_t instances, int max, int item);
OI_EVENT("Sending msg(%p:%d:%T:%x), result: %d")
void trace_Sock_SentResult(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId, MI_Result result);

OI_EVENT("goto failed: %s:%u")
void trace_Wsman_GotoFailed(const char * file, int line);
OI_EVENT("Expired timer for enumerate context %p (%u)")
void trace_Wsman_ExpiredTimerForEnumerate(void * self, MI_Uint32 enumerationContextID);
OI_EVENT("_EC_CheckCloseLeft: Left Closed: %d, activeConnection: %p")
void trace_Wsman_EC_CheckCloseLeft(int leftClosed, void * activeConnection);
OI_EVENT("_EC_CheckCloseRight: haveTimer: %d, Right Closed: %d")
void trace_Wsman_EC_CheckCloseRight(int haveTimer, int rightClosed);
OI_EVENT("_ProcessResultEnumerationContext: selfEC (%p) result (%d)")
void trace_ProcessResultEnumerationContext(void * selfEC, MI_Result result);
OI_EVENT("_ProcessSubscribeResponseEnumerationContext: selfEC (%p)")
void trace_ProcessSubscribeResponseEnumerationContext(void * selfEC);
OI_EVENT("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) sent success subscribe response")
void trace_ProcessSubscribeResponseEnumerationContext_Success(void * selfEC);

OI_EVENT("WsmanEnum: %p _ProcessInstanceEnumerationContext: compeleted: %d, totalResponses: %d, totalResponseSize: %d")
void trace_WsmanEnum(void * self, MI_Boolean expired, MI_Uint32 totalResp, MI_Uint32 totalRespSize);
OI_EVENT("WsmanConnection: Posting msg(%p:%d:%T:%x) on interaction %p<-[%p]<-%p")
void trace_WsmanConnection_PostingMsg(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId, Interaction * left, Strand * self, Interaction * right);
OI_EVENT("WsmanConnection: Ack on interaction [%p]<-%p")
void trace_WsmanConnection_Ack(Strand * self, Interaction * other);
OI_EVENT("WsmanConnection: Close on interaction [%p]<-%p outstandingRequest: %d, single_message: %p")
void trace_WsmanConnection_Close(Strand * self, Interaction * other, MI_Boolean outstandingRequest, void* single_message);
OI_EVENT("WsmanEnum: Finish: %p")
void trace_WsmanEnum_Finish(void * self);

OI_EVENT("_InteractionWsmanEnum_Left_SubscribeReAttached: %p, msg(%p:%d:%T:%x)")
void trace_InteractionWsmanEnum_Left_SubscribeReAttached(void * self, Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("WsmanEnum: Posting msg(%p:%d:%T:%x) on interaction %p<-[%p]<-%p")
void trace_WsmanEnum_PostingMsg(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId, Interaction * left, Strand * self, Interaction * right);
OI_EVENT("WsmanEnum: Ack on interaction [%p]<-%p")
void trace_WsmanEnum_Ack(Strand * self, Interaction * other);
OI_EVENT("_WSMAN_AddSubscribeResponse: selfEC (%p), contextID(%x)")
void trace_Wsman_AddSubscribeResponse(void * self, MI_Uint32 context);
OI_EVENT("wsman: mandatory parameters (className, namespace) are not provided for subscribe request")
void trace_Wsman_ParametersMissingInSubscribeRequest();
OI_EVENT("_ProcessUnsubscribeRequest: selfCD (%p)")
void trace_ProcessUnsubscribeRequest(void * selfCD);
OI_EVENT("wsman: unable to find wsman context for unsubscribe request (contextID=%x).")
void trace_Wsman_UnableToFindContext(MI_Uint32 contextID);
OI_EVENT("_ProcessUnsubscribeRequest: selfCD (%p), msg (%p:%T) complete")
void trace_ProcessUnsubscribeRequest_Complete(void * self, Message * message, const TChar * messageName);
OI_EVENT("wsman: unable to parse incoming xml/ subscribe request body")
void trace_Wsman_UnableToParseXMLSubscribe();
OI_EVENT("wsman: unable to parse incoming xml/ unsubscribe request body")
void trace_Wsman_UnableToParseXMLUnsubscribe();
OI_EVENT("RETURN{%s:%d}")
void trace_WsmanReturn(const char * file, int line);

OI_EVENT("Batch_Tcsdup() failed: out of memory")
void trace_BatchTcsDup_Failed();
OI_EVENT("_GetSingleProperty() failed: %T")
void trace_GetSingleProperty_Failed(const TChar * propNameChar);
OI_EVENT("invalid value of xsi:type: %T")
void trace_XsiTypeInvalidValue(const TChar * propValue);
OI_EVENT("Unsubscribe e:identifier {%d}")
void trace_WsmanUnsubscribe(MI_Uint32 contextID);
OI_EVENT("wsman: unexpected close tag [%c:%T] in incoming xml")
void trace_Wsman_UnexpectedCloseTagWithNamespace(TChar namespaceId, const TChar * name);
OI_EVENT("wsman: unknown mandatory tag [%c:%T]; aborted")
void trace_Wsman_UnknownMandatoryTagWithNamespace(TChar namespaceId, const TChar * name);
OI_EVENT("wsman: Filter tag missing Dialect attribute")
void trace_Wsman_FilterTagMissingDialectAttribute();
OI_EVENT("wsman: Unknown dialect (%T)")
void trace_Wsman_UnknownDialect(const TChar * dialect);
OI_EVENT("wsman: Subscribe dialect (%T)")
void trace_Wsman_SubscribeDialect(const TChar * dialect);
OI_EVENT("wsman: Subscribe filter (%T)")
void trace_Wsman_SubscribeFilter(const TChar * filter);

OI_EVENT("current parent {%T}")
void trace_XmlSerializer_CurrentParent(const TChar * parent);
OI_EVENT("class = {%T} propagator = {%T} propertyName = %T")
void trace_XmlSerializer_WriteBuffer_MiPropertyDecls(const TChar * className, const TChar * propertyPropagatorClass, const TChar * propertyName);

OI_EVENT("_SubscribeEntry_Post: Interaction [%p]<-%p, msg(%p:%d:%T:%x)")
void trace_SubscribeEntry_PostInteraction(Interaction * self, Interaction * other, Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_SubscribeEntry_Post: entry (%p) in status (%T). closed self.")
void trace_SubscribeEntry_PostClosedSelf(void * entry, const TChar * status);
OI_EVENT("_SubscribeEntry_Post: entry (%p) in status (%T)")
void trace_SubscribeEntry_PostEntry(void * entry, const TChar * status);
OI_EVENT("_SubscribeEntry_Post: Posted msg(%p:%d:%T:%x) to parent")
void trace_SubscribeEntry_PostedMsg(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("SubscribeEntry: Ack on interaction [%p]<-%p")
void trace_SubscribeEntry_Ack(Strand * self, Interaction * other);
OI_EVENT("_SubscribeEntry_Cancel: SubscribeEntry (%p); namespace (%T), class (%T)")
void trace_SubscribeEntry_Cancel(void * entry, const TChar * nameSpace, const TChar * className);
OI_EVENT("_SubscribeEntry_Finish: Done")
void trace_SubscribeEntry_Finish();
OI_EVENT("_Client_Post: msg(%p:%d:%T:%x)")
void trace_Client_Post(Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_Client_Ack")
void trace_Client_Ack();
OI_EVENT("_Client_Close")
void trace_Client_Close();
OI_EVENT("_Client_Finish")
void trace_Client_Finish();
OI_EVENT("_Client_Post: message tag: %d")
void trace_Client_PostMessage(MI_Uint32 msgTag);
OI_EVENT("NULL input parameter")
void trace_NullInputParameter();
OI_EVENT("NULL input parameter for %T")
void trace_NullInputParameterForClass(const TChar * className);

OI_EVENT("_LifecycleContext_Cancel: self (%p);")
void trace_LifecycleContext_Cancel(void * subCtx);
OI_EVENT("_LifecycleContext_Cancel: unsubscribe self (%p) done")
void trace_LifecycleContext_Cancel_Done(void * subCtx);
OI_EVENT("_Provider_InvokeSubscribe: subscription(%p) successfully subscribed. Send subscribe response")
void trace_Provider_InvokeSubscribe(void * subscription);
OI_EVENT("_SubscribeElem_Close: self_ (%p) interaction [%p]<-%p")
void trace_SubscribeElem_Close(Strand * self, Interaction * selfInteraction, Interaction * other);
OI_EVENT("Provider_TerminateIndication: Thread %x: class (%T) of provider (%p) start")
void trace_Provider_TerminateIndication_Start(unsigned int threadid, const TChar * className, void * provider);
OI_EVENT("Provider_TerminateIndication: Thread %x: class (%T) of provider (%p) complete")
void trace_Provider_TerminateIndication_Complete(unsigned int threadid, const TChar * className, void * provider);
OI_EVENT("Disabling lifecycle indications for provider (%T)")
void trace_DisablingLifeCycleIndicationsForClass(const TChar * className);
OI_EVENT("Enabling indications for class (%T) of provider (%p)")
void trace_EnablingIndicationsForClass(const TChar * className, void * provider);
OI_EVENT("Initialized indications for class (%T) of provider (%p)")
void trace_InitializedIndicationsForClass(const TChar * className, void * provider);

OI_EVENT("InteractionProtocolHandler_Operation_Cancel %p, out of memory while creating UnsubscribeReq")
void trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Cancel %p, post UnsubscribeReq")
void trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq(void * operation);
OI_EVENT("InteractionProtocolHandler_Operation_Strand_Post: Post Indication to MIDLL. %p, indication instance (%p)")
void trace_InteractionProtocolHandler_Operation_Strand_Post(void * operation, void * instance);
OI_EVENT("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) start")
void trace_Provider_InvokeDisable_Start(unsigned int threadid, const TChar * className, void * provider);
OI_EVENT("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) complete")
void trace_Provider_InvokeDisable_Complete(unsigned int threadid, const TChar * className, void * provider);
OI_EVENT("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) abandoned since new subscription was added")
void trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded(unsigned int threadid, const TChar * className, void * provider);

OI_EVENT("Post on lifecycle context in invalid state")
void trace_LifecycleContext_Post_InvalidState();
OI_EVENT("Subscription state %u is invalid for unsubscribe on class %T")
void trace_SubscrState_InvalidForUnsubscribe(int state, const TChar * className);
OI_EVENT("Unsupported lifecycle indication context")
void trace_UnsupportedLifecycleIndicationContext();

OI_EVENT("Subscription succeeded for events of class (%T) with subscriptionID %I64u")
void trace_SubscrForEvents_Succeeded_MSC(const TChar * className, MI_Uint64 value);
OI_EVENT("Subscription succeeded for lifecycle events of class (%T) and subscriptionID %I64u")
void trace_SubscrForLifecycle_Succeeded_MSC(const TChar * className, MI_Uint64 value);
OI_EVENT("Removing subscription (%I64u) of class (%T)")
void trace_RemovingSubscriptionForClass_MSC(MI_Uint64 value, const TChar * className);

OI_EVENT("Subscription succeeded for events of class (%T) with subscriptionID %llu")
void trace_SubscrForEvents_Succeeded(const TChar * className, MI_Uint64 value);
OI_EVENT("Subscription succeeded for lifecycle events of class (%T) and subscriptionID %llu")
void trace_SubscrForLifecycle_Succeeded(const TChar * className, MI_Uint64 value);
OI_EVENT("Removing subscription (%llu) of class (%T)")
void trace_RemovingSubscriptionForClass(MI_Uint64 value, const TChar * className);

OI_EVENT("_ProcessReleaseRequest: %x")
void trace_Wsman_ProcessReleaseRequest( MI_Uint32 enumerationContextID );

OI_EVENT("Enter %s with application (%p), protocol (%T), destination(%T), session (%p).")
void trace_MIApplicationEnter(const char * func, void * application, const MI_Char * protocol, const MI_Char * destination, void * session);
OI_EVENT("Leave %s with session (%p).")
void trace_MILeavingSession(const char * func, void * session);
OI_EVENT("Trying to thunk a handle after shutdown called: %p")
void trace_MIThunkAfterShutdown(void * thunkHandle);
OI_EVENT("Shutting down thunk handle: %p")
void trace_MIShuttingDownThunkHandle(void * handle);
OI_EVENT("Enter %s with application (%p), protocol (%T), destination(%T), session (%p).")
void trace_MISessionEnter(const char * func, void * application, const MI_Char * protocol, const MI_Char * destination, void * session);
OI_EVENT("Enter %s with session (%p), completionContext (%p), completionCallback (%p).")
void trace_MISessionClose(const char * fun, void * session, void * context, void * callback);
OI_EVENT("Enter %s - session (%p)")
void trace_MIEnter(const char * func, void * session);
OI_EVENT("Leave %s on session (%p) with for operation (%T).")
void trace_MILeavingSessionWithOperation(const char * func, void * session, const MI_Char * operationName);
OI_EVENT("MI_Client Application Initialize: application=%p, internal-application=%p")
void trace_MIClient_AppInit(void * application, void * applicationObject);
OI_EVENT("MI_Client Application Close: application=%p, internal-application=%p")
void trace_MIClient_AppClose(void * application, void * applicationObject);
OI_EVENT("MI_Client Application Close: Cancelling all operations on application=%p, internal-application=%p, session=%p")
void trace_MIClient_AppCloseCancelingAll(void * application, void * applicationObject, void * debugHandlePointer);
OI_EVENT("MI_Client Application Close: Waiting for all sessions to shutdown on application=%p, internal-application=%p, number left=%llu")
void trace_MIClient_AppCloseWaitingOnSessions(void * application, void * applicationObject, ptrdiff_t curChildCount);
OI_EVENT("MI_Client Application Close: Waiting for all hosted providers to shutdown on application=%p, internal-application=%p, number left=%llu")
void trace_MIClient_AppCloseWaitingOnHostedProviders(void * application, void * applicationObject, ptrdiff_t curChildCount);
OI_EVENT("MI_Client Application Close: completed application=%p, internal-application=%p")
void trace_MIClient_AppCloseCompleted(void * application, void * applicationObject);
OI_EVENT("MI_Client Session Create: application=%p, session=%p, internal-session=%p")
void trace_MIClient_SessionCreate(void * application, void * session, void * sessionObject);
OI_EVENT("MI_Client Session Close: Completed session=%p, internal-session=%p")
void trace_MIClient_SessionCloseCompleted(void * clientSessionPtr, void * sessionObject);
OI_EVENT("MI_Client Session Close: session=%p, internal-session=%p")
void trace_MIClient_SessionClose(void * session, void * sessionObject);
OI_EVENT("MI_Client Session Close: waiting for all operations to shutdown session=%p, internal-session=%p, number left=%llu")
void trace_MIClient_SessionClose_WaitingOnOperations(void * session, void * sessionObject, ptrdiff_t left);
OI_EVENT("MI_Client Operation Instance Result (async): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_OperationInstancResultAsync(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Instance Result (sync, waiting for client to get it): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_OperationInstanceResult_WaitingForClient(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Class Result: session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_OperationClassResult(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Indication Result: session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_OperationIndicationResult(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Close: Complete session=%p, operation=%p, internal-operation=%p")
void trace_MIClient_OperationCloseCompleted(void * session, void * operation, void * internalOperation);
OI_EVENT("MI_Client Operation Close: operation=%p, internal-operation=%p")
void trace_MIClient_OperationClose(void * operation, void * operationObject);
OI_EVENT("MI_Client Operation Close: Waiting for the final result to be retrieved.  Client should retrieve the final result before calling MI_Operation_Close.  operation=%p, internal-operation=%p")
void trace_MIClient_OperationClose_WaitingForFinalResult(void * operation, void * operationObject);
OI_EVENT("MI_Client Operation Cancel: operation=%p, internal-operation=%p")
void trace_MIClient_OperationCancel(void * operation, void * operationObject);
OI_EVENT("MI_Client Operation Get Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T")
void trace_MIClient_GetInstance(void * session, void * operation, void * operationObject, const MI_Char * namespaceName);
OI_EVENT("MI_Client Operation Invoke: session=%p, operation=%p, internal-operation=%p, namespace=%T, classname=%T, methodname=%T")
void trace_MIClient_Invoke(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * className, const MI_Char * methodName);
OI_EVENT("MI_Client Operation Enumerate Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, classname=%T")
void trace_MIClient_EnumerateInstance(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * className);
OI_EVENT("MI_Client Operation Query Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, queryDialect=%T, queryExpression=%T")
void trace_MIClient_QueryInstances(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * queryDialect, const MI_Char * queryExpression);
OI_EVENT("MI_Client Operation Instance Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_OperationInstancResultSync(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Indication Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_IndicationResultSync(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Class Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T")
void trace_MIClient_ClassResultSync(void * session, void * operation, void * internalOperation, MI_Result code, const MI_Char * moreResults);
OI_EVENT("MI_Client Operation Associator Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, instance=%p, assocClass=%T, resultClass=%T, role=%T, resultRole=%T")
void trace_MIClient_AssociatorInstances(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, void * trace_instanceKey, const MI_Char * assocClass, const MI_Char * resultClass, const MI_Char * role, const MI_Char * resultRole);
OI_EVENT("MI_Client Operation Reference Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, resultClass=%T, role=%T")
void trace_MIClient_ReferenceInstances(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * trace_resultClass, const MI_Char * role);
OI_EVENT("MI_Client Operation Modify Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T")
void trace_MIClient_ModifyInstance(void * session, void * operation, void * operationObject, const MI_Char * namespaceName);
OI_EVENT("MI_Client Operation Create Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T")
void trace_MIClient_CreateInstance(void * session, void * operation, void * operationObject, const MI_Char * namespaceName);
OI_EVENT("MI_Client Operation Delete Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T")
void trace_MIClient_DeleteInstance(void * session, void * operation, void * operationObject, const MI_Char * namespaceName);
OI_EVENT("MI_Client Operation Get Class: session=%p, operation=%p, internal-operation=%p, namespace=%T, className=%T")
void trace_MIClient_GetClass(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * className);
OI_EVENT("MI_Client Operation Enumerate Classes: session=%p, operation=%p, internal-operation=%p, namespace=%s, className=%s")
void trace_MIClient_EnumerateClasses(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * className);
OI_EVENT("MI_Client Operation Subscribe: session=%p, operation=%p, internal-operation=%p, namespace=%T, queryDialect=%T, queryExpression=%T")
void trace_MIClient_Subscribe(void * session, void * operation, void * operationObject, const MI_Char * namespaceName, const MI_Char * trace_queryDialect, const MI_Char * queryExpression);
OI_EVENT("MI_Client Operation Test Connection: session=%p, operation=%p, internal-operation=%p")
void trace_MIClient_TestConnection(void * session, void * operation, void * operationObject);
OI_EVENT("MI_Client Out of memory!")
void trace_MIClient_OutOfMemory();

OI_EVENT("SubMgr_DeleteSubscription: Start    Thread %x: mgr (%p) Subscription (%p); (%d) active subscriptions;  header (%p), tail (%p)")
void trace_SubMgr_DeleteSubscription_Start(unsigned int threadid, void* mgr, void * self, unsigned int count, void* header, void* tail);
OI_EVENT("SubMgr_DeleteSubscription: Complete Thread %x: mgr (%p); remains (%d) subscriptions; header (%p), tail (%p)")
void trace_SubMgr_DeleteSubscription_Complete(unsigned int threadid, void* mgr, unsigned int count, void* header, void* tail);

OI_EVENT("Schedule_UnsubscribeProvider: Thread %x: scheduled unsubscribe request for subscription (%p)")
void trace_ScheduleRequest_UnsubscribeProvider(unsigned int threadid, void* sub);
OI_EVENT("Schedule_SubscribeRequest: Thread %x: scheduled subscribe request provider (%p), msg (%p), subContext (%p)")
void trace_ScheduleRequest_SubscribeProvider(unsigned int threadid, void* provider, void * msg, void * subContext);

OI_EVENT("noniothread_proc_start: Thread %x:")
void trace_noniothread_proc_start(unsigned int threadid);
OI_EVENT("noniothread_proc_end: Thread %x:")
void trace_noniothread_proc_end(unsigned int threadid);

OI_EVENT("Free RequestItem : %p")
void trace_nioproc_FreeRequestItem(void * requestItem);
OI_EVENT("Create RequestItem : %p")
void trace_nioproc_CreateRequestItem(void * requestItem);

OI_EVENT("SubMgrSubscription_ShouldCallUnsubscribe: Thread %x:; subscription (%p); should unsubscribe (%d)")
void trace_SubMgrSubscription_ShouldCallUnsubscribe(unsigned int threadid, void* self, MI_Boolean r);
OI_EVENT("SubMgrSubscription_ShouldCallUnsubscribe: Thread %x:; subscription (%p) was already unsubscribed")
void trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed(unsigned int threadid, void* self);
OI_EVENT("SubMgrSubscription_ShouldSendFinalMsg: Thread %x:; subscription (%p); should send final message (%d)")
void trace_SubMgrSubscription_ShouldSendFinalMsg(unsigned int threadid, void* self, MI_Boolean r);
OI_EVENT("SubMgrSubscription_ShouldSendFinalMsg: Thread %x:; subscription (%p) already sent final message")
void trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent(unsigned int threadid, void* self);
OI_EVENT("SubMgr_GetSubscriptionByContext: Thread %x:; mgr (%p) subscription (%p) not found")
void trace_SubMgr_GetSubscriptionByContext_NotFound(unsigned int threadid, void* mgr, void* self);
OI_EVENT("_SubscrContext_ProcessResult: Thread %x: ctx (%p) subscription (%p)")
void trace_SubscrContext_ProcessResult(unsigned int threadid, void* ctx, void* sub);
OI_EVENT("Timer started with timeout value %I64u")
void trace_Timer_Started_MSCVER(PAL_Uint64 subscriptionID);
OI_EVENT("Timer started with timeout value %llu")
void trace_Timer_Started_POSIX(PAL_Uint64 subscriptionID);
OI_EVENT("Timer_Fire: Manual trigger of timer (%p) on strand (%p)")
void trace_Timer_ManualTrigger(void* timer, void* strand);
OI_EVENT("Timer_Close: Closing timer (%p)")
void trace_Timer_Close(void* timer);
OI_EVENT("Timer_Callback: CallbackMayRunLong is TRUE")
void trace_Timer_CallbackMayRunLong_True();
OI_EVENT("Timer_Callback: CallbackMayRunLong is FALSE")
void trace_Timer_CallbackMayRunLong_False();
OI_EVENT("Timer_Callback: SELECTOR_ADD")
void trace_Timer_Selector_Added();
OI_EVENT("DisableProvider: Thread %x: scheduled disable indications request for provider (%p)")
void trace_Unsubscribe_DisableProvider(unsigned int threadid, void* provider);

OI_EVENT("Sock_Accept: sock (%d)")
void trace_Socket_Accept(int sock);
OI_EVENT("Sock_Close: sock (%d)")
void trace_Sock_Close(int sock);

OI_EVENT("_ConnectionIn_Post: binary protocol ignore UnsubscribeReq msg (%p), operationId (%x)")
void trace_ConnectionInPost_IgnoreUnsubscribeReq(void * msg, MI_Uint64 operationId);

OI_EVENT("_SubscribeEntry_Post: entry (%p) in status (%T), received final msg(%p:%d:%T:%x), result (%d)")
void trace_SubscribeEntry_PostFinalMsg(void * self, const TChar * iceStatus, Message * msg, MI_Uint32 msgTag, const TChar * messageName, MI_Uint64 operationId, MI_Result r);

OI_EVENT("SubMgrSubscription_Release: Thread %x: finalize subscription (%p), refcount is 0")
void trace_SubMgrSubscription_Release_Finalized(unsigned int threadid, void * self);
OI_EVENT("_InteractionWsmanEnum_Left_ConnectionDataTimeout: Ignored because Post or Close already occurred on CD RM=%p, SM=%p, closed=%d")
void trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored(void* rm, void* sm, MI_Boolean thisClosedOther);
OI_EVENT("_InteractionWsmanEnum_Left_ConnectionDataTimeout: CD notifier for EC %p")
void trace_WSManEnumerationContext_CD_Timeout_notifier(void* enumCtx);
OI_EVENT("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) Ignoring response to timed out request.")
void trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest(void * selfEC);
OI_EVENT("Engine credentials verified (%p)")
void trace_EngineCredentialsVerified(void* handle);
OI_EVENT("Server closing socket (%p, %d)")
void trace_ServerClosingSocket(void* handle, int socket);
OI_EVENT("Engine closing socket (%p, %d)")
void trace_EngineClosingSocket(void* handle, int socket);
OI_EVENT("Server establishing socket with engine (%p, %d)")
void trace_ServerEstablishingSocket(void* handle, int socket);
OI_EVENT("Engine establishing socket with server (%p, %d)")
void trace_EngineEstablishingSocket(void* handle, int socket);
OI_EVENT("Server connection info received")
void trace_ServerInfoReceived();
OI_EVENT("Tracker hash map added (%p, %d)")
void trace_TrackerHashMapAdd(void* handle, int socket);
OI_EVENT("Tracker hash map removeded (%d)")
void trace_TrackerHashMapRemove(int socket);
OI_EVENT("Tracker hash map found (%p, %d)")
void trace_TrackerHashMapFind(void* handle, int socket);
OI_EVENT("Engine: Client Credentials Verified (%p)")
void trace_ClientCredentialsVerfied(void* handle);
OI_EVENT("Client: Client Credentials Verified")
void trace_ClientCredentialsVerfied2();
OI_EVENT("Handle:(%p), ClientAuthState = %d, EngineAuthState = %d")
void trace_AuthStates(void* handle, int client, int engine);
OI_EVENT("Asking Server to PAM authenticate")
void trace_AskServerToAuthenticate();
OI_EVENT("AgentMgr_PreExec_RequestStrand_Post: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_Post(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_RequestStrand_PostControl: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_PostControl(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_RequestStrand_Ack: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_Ack(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_RequestStrand_Cancel: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_Cancel(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_RequestStrand_Close: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_Close(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_RequestStrand_Finish: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_RequestStrand_Finish(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_Post: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_Post(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_PostControl: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_PostControl(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_Ack: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_Ack(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_Cancel: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_Cancel(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_Close: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_Close(void* context, void* strand);
OI_EVENT("AgentMgr_PreExec_ResponseStrand_Finish: preexecContext (%p), strand (%p)")
void trace_AgentMgr_PreExec_ResponseStrand_Finish(void* context, void* strand);


/****************************** VERBOSE events ******************************/

OI_SETDEFAULT(PRIORITY(LOG_VERBOSE))
OI_SETDEFAULT(STARTID(55000))

OI_EVENT("Strand %p(%s), action: %s")
void trace_Strand_Action(Strand * self, const char * selfName, const char * operation);
OI_EVENT("Strand %p(%s), %s: interaction: %p, opened: %d, thisClosedOther: %d, thisAckPending: %d, otherClosedThis: %d, otherAckPending: %d, ackPassthru: %d")
void trace_StrandFlags(Strand * self, const char * selfName, Interaction * interaction, int opened, int thisClosedOther, int thisAckPending, int otherClosedThis, int otherAckPending, int ackPassthru);
OI_EVENT("_StrandEntryOperation_Add: %d entries %p(%s): %p(%s)")
void trace_StrandEntryOperation_Add(unsigned int entries, StrandMany * self, const char * selfName, Strand * entry, const char * entryName);
OI_EVENT("_StrandEntryOperation_Cancel: %p(%s) canceling on parent (canceled: %d)")
void trace_StrandEntryOperation_Cancel(StrandMany * self, const char * selfName, int canceled);
OI_EVENT("_StrandEntryOperation_PostControl: %p(%s) Post on parent ignored after interaction is closed, msg: %p")
void trace_StrandEntryOperation_PostControl_PostIgnored(StrandMany * self, const char * selfName, Message * message);
OI_EVENT("_StrandEntryOperation_PostControl: %p(%s) Posting control msg on parent, msg: %p")
void trace_StrandEntryOperation_PostControl_ToParent(StrandMany * self, const char * selfName, Message * message);
OI_EVENT("_StrandEntryOperation_Post: %p(%s) Post on parent ignored after interaction is closed, msg: %p")
void trace_StrandEntryOperation_Post_IgnoredAfterClose(StrandMany * self, const char * selfName, Message * message);
OI_EVENT("_StrandEntryOperation_Post: %p(%s) Posting on parent, msg: %p")
void trace_StrandEntryOperation_Post_ToParent(StrandMany * self, const char * selfName, Message * message);
OI_EVENT("_StrandEntryOperation_Post: %p(%s) cannot post on parent (waiting ack), msg: %p")
void trace_StrandEntryOperation_Post_CannotPostWaitingOnAck(StrandMany * self, const char * selfName, Message * message);
OI_EVENT("_StrandEntryOperation_Close: %p(%s) close on parent (closed: %d)")
void trace_StrandEntryOperation_Close(StrandMany * self, const char * selfName, int closed);
OI_EVENT("_StrandEntryOperation_Deleted: %p(%s): %p(%s)")
void trace_StrandEntryOperation_Deleted(StrandMany * self, const char * selfName, void * currentEntry, const char * currentEntryName);

OI_EVENT("Strand_RunPendingOp: %p(%s), bit: %d(%s)")
void trace_Strand_RunPendingOp(Strand * self, const char * strandName, int bitIndex, const char * indexName);
OI_EVENT("Strand_RunPendingOp: %p(%s), operation Cannot complete, bit: %d(%s)")
void trace_Strand_RunPendingOp_CannotComplete(Strand * self, const char * strandName, int bitIndex, const char * indexName);
OI_EVENT("Strand_RunPendingOp: %p(%s), deleted entry, bit: %d(%s)")
void trace_Strand_RunPendingOp_EntryDeleted(Strand * self, const char * strandName, int bitIndex, const char * indexName);

OI_EVENT("_StrandMethod_Entry_CancelInternal: %p(%s)")
void trace_StrandMethod_Entry_CancelInternal(Strand * self, const char * selfName);
OI_EVENT("_StrandMethod_Entry_PostControlInternal: %p(%s) Control msg from parent, msg: %p")
void trace_StrandMethod_Entry_PostControlInternal(Strand * self, const char * strandName, Message * controlMsg);
OI_EVENT("_StrandMethod_Entry_PostInternal: %p(%s) Msg from parent, msg: %p")
void trace_StrandMethod_Entry_PostInternal(Strand * self, const char * strandName, Message * msg);
OI_EVENT("_StrandMethod_Entry_AckInternal: %p(%s)")
void trace_StrandMethod_Entry_AckInternal(Strand * self, const char * strandName);
OI_EVENT("_StrandMethod_Entry_CloseInternal: %p(%s) opened: %d, closed other: %d")
void trace_StrandMethod_Entry_CloseInternal(Strand * self, const char * strandName, int opened, int closedOther);
OI_EVENT("Strand %p(%s), deleting entry %p(%s)")
void trace_Strand_DeletedEntry(Strand * self, const char * strandName, void * entry, const char * entryName);
OI_EVENT("Strand_ExecLoop: %p(%s) state %x(%s), bit: %d(%s) [%s]")
void trace_Strand_ExecLoop(Strand * self, const char * selfName, ptrdiff_t state, const char * stateName, int bit, const char * bitName, const char * infoState);
OI_EVENT("Strand_ExecLoop: %p LEAVE occurred, previous state %x, bit: %d (%x)")
void trace_Strand_ExecLoop_Leave(Strand * self, ptrdiff_t prevstate, int bit, ptrdiff_t methodBit);
OI_EVENT("Strand_ExecuteLoop: %p About to exit, state %x, About To Finish: %d")
void trace_Strand_ExecuteLoop_AboutToExit(Strand * self, ptrdiff_t state, int aboutToFinish);
OI_EVENT("Strand_ExecLoop: %p(%s) Exits, state %x, ToFinish: %d [%s]")
void trace_Strand_ExecLoop_Exits(Strand * self, const char * selfName, ptrdiff_t state, int toFinish, const char * infoState);
OI_EVENT("Strand_ExecLoop: %p(%s) DOESN'T Exit, state %x, newState: %x(%s), ToFinish: %d [%s]")
void trace_Strand_ExecLoop_DoesntExit(Strand * self, const char * selfName, ptrdiff_t state, ptrdiff_t newState, const char * newStateName, int toFinish, const char * infoState);
OI_EVENT("_Strand_ScheduleParent: %p(%s) state %x(%s), bit:%x(%s) from %p(%s); methodBit: %x(%s)")
void trace_Strand_ScheduleParent(Strand * self, const char * selfName, ptrdiff_t state, const char * stateName, int bit, const char * bitName, Strand * from, const char * fromName, unsigned int methodBit, const char * methodBitName);
OI_EVENT("_Strand_ScheduleEntry: %p(%s) state %x(%s), bit:%x(%s) from %p(%s); methodBit: %x(%s)")
void trace_Strand_ScheduleEntry(Strand * self, const char * selfName, ptrdiff_t state, const char * stateName, int bit, const char * bitName, Strand * from, const char * fromName, unsigned int methodBit, const char * methodBitName);
OI_EVENT("_Strand_Schedule: %p(%s) state %x(%s), methodBit: %x(%s)")
void trace_Strand_Schedule(Strand * self, const char * selfName, ptrdiff_t state, const char * stateName, unsigned int methodBit, const char * methodBitName);
OI_EVENT("_Strand_Schedule: %p state %x, methodBit: %x")
void trace_Strand_Schedule2(Strand * self, ptrdiff_t state, unsigned int methodBit);
OI_EVENT("_Strand_Schedule: %p(%s) Taking over opening, state %x(%s), methodBit: %x, currentMethodBit: %x(%s)")
void trace_Strand_Schedule_TakingOver(Strand * self, const char * selfName, ptrdiff_t state, const char * stateName, unsigned int methodBit, ptrdiff_t currentMethodBit, const char * currentMethodBitName);
OI_EVENT("_Strand_EnterStrand: %p(%s)")
void trace_Strand_EnterStrand(Strand * self, const char * selfName);
OI_EVENT("_Strand_ExitStrand: %p(%s)")
void trace_Strand_ExitStrand(Strand * self, const char * selfName);
OI_EVENT("_Strand_TracePost: %p, msg(%p:%d:%T:%x)")
void trace_Strand_TracePost(void * self, Message * message, MI_Uint32 tag, const TChar * messageName, MI_Uint64 operationId);
OI_EVENT("_Strand_TracePost: %p, msg(%p:%d:%x) PostResultMsg:%d")
void trace_Strand_TracePostResult(void * self, Message * message, MI_Uint32 tag, MI_Uint64 operationId, MI_Result result);
OI_EVENT("Strand_Leave: %p(%s) (strandStealedFlag %p)")
void trace_Strand_Leave(void* strand, const char* selfname, void* strandStealedFlag);

OI_EVENT("SubMgrSubscription_New: (%s:%u) Subscription (%p: class=%T), Refcount (%u)")
void trace_SubMgrSubscription_New(const char* file, MI_Uint32 line, void * self, const TChar* classname, unsigned int refcount);
OI_EVENT("SubMgrSubscription_Addref: (%s:%u) Subscription (%p), Refcount (%u)")
void trace_SubMgrSubscription_Addref(const char* file, MI_Uint32 line, void * self, unsigned int refcount);
OI_EVENT("SubMgrSubscription_Release: (%s:%u) Subscription (%p), Refcount (%u)")
void trace_SubMgrSubscription_Release(const char* file, MI_Uint32 line, void * self, unsigned int refcount);
OI_EVENT("SubMgrSubscription_AcquirePostLock: Thread %x: Subscription (%p), context (%p), acquired postlock")
void trace_SubMgrSubscription_AcquirePostLock(unsigned int threadid, void * self, void * context);
OI_EVENT("SubMgrSubscription_ReleasePostLock: Thread %x: Subscription (%p), context (%p), to release postlock")
void trace_SubMgrSubscription_ReleasePostLock(unsigned int threadid, void * self, void * context);

OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), operation type (%T) started")
void trace_SubscriptionManager_AcquireEnableLock_Start(unsigned int threadid, void * self, const TChar * optype);
OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), agggregation context terminated, acquire lock failed")
void trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated(unsigned int threadid, void * self);
OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); ignore disable call since there are still active subscriptions")
void trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall(unsigned int threadid, void * self);
OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); cancel all subscriptions")
void trace_SubscriptionManager_AcquireEnableLock_CancelAll(unsigned int threadid, void * self);
OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); aggregation context active, found new subsription(s), release lock")
void trace_SubscriptionManager_AcquireEnableLock_ReleaseLock(unsigned int threadid, void * self);
OI_EVENT("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), operation type (%T), acquired enablelock")
void trace_SubscriptionManager_AcquireEnableLock_Complete(unsigned int threadid, void * self, const TChar * optype);

OI_EVENT("SubscriptionManager_ReleaseEnableLock: Thread %x: SubscriptionManager (%p), released enablelock")
void trace_SubscriptionManager_ReleaseEnableLock(unsigned int threadid, void * self);
OI_EVENT("SubscriptionManager_ReleaseEnableLock: Thread %x: SubscriptionManager (%p), enablelock was already released for disable case")
void trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked(unsigned int threadid, void * self);
OI_EVENT("_PackFieldNil with usePreciseArrays = %d")
void trace_Wsman_PackFieldNil(int usePreciseArrays);
OI_EVENT("EC_Left_ConnectionDataTimeout: activeConnection is NULL")
void trace_WSManEnumerateContext_CD_Timeout_on_inactive_context();
OI_EVENT("EC_Left_ConnectionDataTimeout: action %d timed out")
void trace_WSManEnumerateContext_CD_Timeout_during_initial_operation(int rqtAction);

OI_EVENT("Message_New: %s(%u): __Message_New(%T): %p: refs=%u")
void trace_Message_New(const char* file, MI_Uint32 line, const TChar * name, void * self, unsigned int refcount);
OI_EVENT("Message_Addref: %s(%u): __Message_AddRef(%T): %p: refs=%u")
void trace_Message_AddRef(const char* file, MI_Uint32 line, const TChar * name, void * self, unsigned int refcount);
OI_EVENT("Message_Release: %s(%u): __Message_Release(%T): %p: refs=%u")
void trace_Message_Release(const char* file, MI_Uint32 line, const TChar * name, void * self, unsigned int refcount);
OI_EVENT("MessageFromBatch: %s(%u): __MessageFromBatch(%T): %p: refs=%u")
void trace_MessageFromBatch_Complete(const char* file, MI_Uint32 line, const TChar * name, void * self, unsigned int refcount);

OI_EVENT("ProtocolSocket_Addref: %s(%u): self %p: refs=%u")
void trace_ProtocolSocket_Addref(const char* file, MI_Uint32 line, void * self, unsigned int refcount);
OI_EVENT("ProtocolSocket_Release: %s(%u): self %p: refs=%u")
void trace_ProtocolSocket_Release(const char* file, MI_Uint32 line, void * self, unsigned int refcount);

/****************************** UNIT TEST TRACES ****************************/

OI_SETDEFAULT(PRIORITY(LOG_VERBOSE))
OI_SETDEFAULT(STARTID(60000))

OI_EVENT("_StrandProtocol_Post: self (%p), msg (%p:%T)")
void trace_StrandProtocol_Post(Strand * self, Message * message, const TChar * messageName);
OI_EVENT("_StrandProtocol_Post: closed self (%p)")
void trace_StrandProtocol_Post_ClosedSelf(Strand * self);
OI_EVENT("_StrandProtocol_Post: self (%p), msg (%p:%T). Total (%d) posts")
void trace_StrandProtocol_Post_Total(Strand * self, Message * message, const TChar * messageName, int totalPosts);
OI_EVENT("_StrandProtocol_Ack: self (%p). Total (%d) Ack")
void trace_StrandProtocol_Ack(Strand * self, int totalAcks);
OI_EVENT("_StrandProtocol_Cancel: self (%p). Total (%d) Cancel")
void trace_StrandProtocol_Cancel(Strand * self, int totalCancels);
OI_EVENT("_StrandProtocol_Finished: self (%p). Total (%d) Finished")
void trace_StrandProtocol_Finished(Strand * self, int totalFinished);

OI_EVENT("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s)")
void trace_StrandSimAgentMgr_Ack(Strand * self, int nAck);
OI_EVENT("_StrandSimAgentMgr_Ack: close self (%p). Total (%d) Ack(s)")
void trace_StrandSimAgentMgr_AckCloseSelf(Strand * self, int nAck);
OI_EVENT("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s); Stop send message due to first response was design to FAILED")
void trace_StrandSimAgentMgr_AckStopByDesign(Strand * self, int nAck);
OI_EVENT("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s); Stop send message due to all message were sent")
void trace_StrandSimAgentMgr_AckStopAllSent(Strand * self, int nAck);
OI_EVENT("_StrandSimAgentMgr_Ack: self (%p). Post Indication Message (%p)")
void trace_StrandSimAgentMgr_AckPostIndication(Strand * self, Message * message);
OI_EVENT("_StrandSimAgentMgr_Ack: self (%p). Post final message (%p)")
void trace_StrandSimAgentMgr_AckPostFinal(Strand * self, Message * message);
OI_EVENT("_StrandSimAgentMgr_Cancel: self (%p). Total (%d) Cancel")
void trace_StrandSimAgentMgr_Cancel(Strand * self, int totalCancels);
OI_EVENT("_StrandSimAgentMgr_Cancel: self (%p). Post final message (%p)")
void trace_StrandSimAgentMgr_CancelFinalMessage(Strand * self, Message * message);
OI_EVENT("_StrandSimAgentMgr_Finished: self (%p). Total (%d) Finished")
void trace_StrandSimAgentMgr_Finished(Strand * self, int totalFinished);

OI_EVENT("_UT_HandleRequest: context (%p), msg (%p:%T), interaction(%p)")
void trace_UT_HandleRequest(void * context, Message * message, const TChar * messageName, Interaction * interaction);
OI_EVENT("_UT_HandleRequest: context (%p), msg (%p:%T), interaction(%p); Failed with result (%d)")
void trace_UT_HandleRequestFailed(void * context, Message * message, const TChar * messageName, Interaction * interaction, MI_Result result);

OI_EVENT("_Server_Post: message tag: %d")
void trace_Server_Post(MI_Uint32 msgTag);
OI_EVENT("_Server_Ack")
void trace_Server_Ack();
OI_EVENT("_Server_Close")
void trace_Server_Close();
OI_EVENT("_Server_Finish")
void trace_Server_Finish();

OI_EVENT("TestMgr_Subscribe_Unsubscribe_Cancel: Unsubscribe")
void trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe();
OI_EVENT("TestMgr_Subscribe_Unsubscribe_Cancel: Cancel")
void trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel();
OI_EVENT("TestMgr_Subscribe_Unsubscribe_Cancel: schedule cancel on protocol (%p)")
void trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule(void * self);
OI_EVENT("TestMgr_Subscribe_Unsubscribe_Cancel: Finalize Agent Managers")
void trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers();

OI_SETDEFAULT(PRIORITY(LOG_DEBUG))
OI_SETDEFAULT(STARTID(60000))
OI_SETDEFAULT(CHANNEL(Debug))

OI_EVENT("HTTP: Encryption failed.")
void trace_HTTP_EncryptionFailed();

OI_EVENT("HTTP: GSSstatus. gss:(%.*%s) mech:(%s) min_status:(%x)")
void trace_HTTP_GssStatus(const int status_string_length, const char * status_string, const int min_status );

OI_EVENT("HTTP: gss ntlm status:(%s) username:(%s)")
void trace_HTTP_GssNtlmStatus(const char * status_string, const char * username);

OI_EVENT("HTTP: gss error:(%s)")
void trace_HTTP_GssError(const char * status_string);

OI_EVENT("HTTP: get addr info error:(%s)")
void trace_HTTP_GetAddrInfoError(const char * status_string);

OI_EVENT("HTTP: Gss Library Load Failed:(%s)")
void trace_HTTP_LoadGssFailed(const char * msg);

OI_EVENT("HTTP: Gss Function Not Present:(%s)")
void trace_HTTP_GssFunctionNotPresent(const char * msg);

OI_EVENT("HTTP: Authorization Malloc Failed:(%s)")
void trace_HTTP_AuthMallocFailed(const char * msg);

OI_EVENT("HTTP: Http_Encrypt/Decrpyt invalid arg:(%s %s)")
void trace_HTTP_CryptInvalidArg(const char * location, const char * msg);

OI_EVENT("HTTP: User Authorization failed. (%s)")
void trace_HTTP_UserAuthFailed(const char * msg);

OI_EVENT("HTTP: Authorization Complete.")
void trace_HTTP_AuthComplete();

OI_EVENT("HTTP: Authorization Continue.")
void trace_HTTP_AuthContinue();

OI_EVENT("HTTP: Loading gss api. (%s)")
void trace_HTTP_LoadingGssApi(const char * msg);

OI_EVENT("HTTP: Send Next Auth Reply.")
void trace_HTTP_SendNextAuthReply();

OI_EVENT("HTTP Auth: Input Token Invalid.")
void trace_HTTP_InvalidAuthToken();

OI_EVENT("HTTP Auth: SupplimentaryInfo: (%s).")
void trace_HTTP_SupplimentaryInfo(const char * msg);

OI_EVENT("HTTP Auth: Cannot build response.")
void trace_HTTP_CannotBuildAuthResponse();

OI_EVENT("HTTP: (%s):(%s)")
void trace_HTTP_StatusMsg(const char * func, const char * msg);

END_EXTERNC

#endif /* _oi_traces_h */
