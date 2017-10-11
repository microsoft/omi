
/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/
#include <oi/oi_file.h>


#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_AllocFailed() trace_ProvMgr_AllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_ProvMgr_AllocFailed() trace_ProvMgr_AllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(10000, trace_ProvMgr_AllocFailed_Impl, LOG_CRIT, PAL_T("allocation failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnknownMessageType(a0) trace_UnknownMessageType_Impl(__FILE__, __LINE__, a0)
#else
#define trace_UnknownMessageType(a0) trace_UnknownMessageType_Impl(0, 0, a0)
#endif
FILE_EVENT1(10001, trace_UnknownMessageType_Impl, LOG_CRIT, PAL_T("unknown message type: %u"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CreatePIDFileFailed(a0) trace_CreatePIDFileFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_CreatePIDFileFailed(a0) trace_CreatePIDFileFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(10002, trace_CreatePIDFileFailed_Impl, LOG_CRIT, PAL_T("failed to create PID file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispatchInitFailed(a0) trace_DispatchInitFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_DispatchInitFailed(a0) trace_DispatchInitFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(10003, trace_DispatchInitFailed_Impl, LOG_CRIT, PAL_T("failed to initialize the dispatcher: %u"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ParentProcessTerminated(a0, a1) trace_ParentProcessTerminated_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ParentProcessTerminated(a0, a1) trace_ParentProcessTerminated_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(10004, trace_ParentProcessTerminated_Impl, LOG_CRIT, PAL_T("abnormal termination of parent process detected. Old parent: %d, New parent: %d"), int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineProcessTerminated() trace_EngineProcessTerminated_Impl(__FILE__, __LINE__)
#else
#define trace_EngineProcessTerminated() trace_EngineProcessTerminated_Impl(0, 0)
#endif
FILE_EVENT0(10005, trace_EngineProcessTerminated_Impl, LOG_CRIT, PAL_T("abnormal termination of engine process detected...shutting down server"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CriticalError(a0) trace_CriticalError_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_CriticalError(a0) trace_CriticalError_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(10006, trace_CriticalError_Impl, LOG_CRIT, PAL_T("%T"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentMgrHandleRequestForNS(a0) trace_AgentMgrHandleRequestForNS_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_AgentMgrHandleRequestForNS(a0) trace_AgentMgrHandleRequestForNS_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20000, trace_AgentMgrHandleRequestForNS_Impl, LOG_ERR, PAL_T("AgentMgr_HandleRequest failed for namespace: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_ProvMgrNewRequest_Failed(a0) trace_Agent_ProvMgrNewRequest_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Agent_ProvMgrNewRequest_Failed(a0) trace_Agent_ProvMgrNewRequest_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20001, trace_Agent_ProvMgrNewRequest_Failed_Impl, LOG_ERR, PAL_T("Agent _RequestCallback: ProvMgr_NewRequest failed with result %d !"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_FDParameterIsMissing() trace_Agent_FDParameterIsMissing_Impl(__FILE__, __LINE__)
#else
#define trace_Agent_FDParameterIsMissing() trace_Agent_FDParameterIsMissing_Impl(0, 0)
#endif
FILE_EVENT0(20002, trace_Agent_FDParameterIsMissing_Impl, LOG_ERR, PAL_T("parameter is missing (fd)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MessagePackCloneForBinarySending_AllocFailed(a0) trace_MessagePackCloneForBinarySending_AllocFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MessagePackCloneForBinarySending_AllocFailed(a0) trace_MessagePackCloneForBinarySending_AllocFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20003, trace_MessagePackCloneForBinarySending_AllocFailed_Impl, LOG_ERR, PAL_T("MessagePackCloneForBinarySending, cannot allocate message %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MessagePackCloneForBinarySending_CloneFailed(a0, a1) trace_MessagePackCloneForBinarySending_CloneFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MessagePackCloneForBinarySending_CloneFailed(a0, a1) trace_MessagePackCloneForBinarySending_CloneFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20004, trace_MessagePackCloneForBinarySending_CloneFailed_Impl, LOG_ERR, PAL_T("MessagePackCloneForBinarySending, cannot clone message tag: %d, error: %d"), MI_Uint32, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInPost_NewOpFailed(a0) trace_ConnectionInPost_NewOpFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ConnectionInPost_NewOpFailed(a0) trace_ConnectionInPost_NewOpFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20005, trace_ConnectionInPost_NewOpFailed_Impl, LOG_ERR, PAL_T("_ConnectionIn_Post: Cannot create new operation with operationId %p !"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInPost_CannotAddNewOp(a0) trace_ConnectionInPost_CannotAddNewOp_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ConnectionInPost_CannotAddNewOp(a0) trace_ConnectionInPost_CannotAddNewOp_Impl(0, 0, a0)
#endif
FILE_EVENT1(20006, trace_ConnectionInPost_CannotAddNewOp_Impl, LOG_ERR, PAL_T("_ConnectionIn_Post: Cannot add new operation with operationId %p !"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInPost_MessageAllocFailed(a0) trace_ConnectionInPost_MessageAllocFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ConnectionInPost_MessageAllocFailed(a0) trace_ConnectionInPost_MessageAllocFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20007, trace_ConnectionInPost_MessageAllocFailed_Impl, LOG_ERR, PAL_T("_ConnectionIn_Post: Cannot allocate message to post failed result %d !"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionIn_PostCancelError(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_PostCancelError_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4, a5, a6)
#else
#define trace_ConnectionIn_PostCancelError(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_PostCancelError_Impl(0, 0, a0, a1, a2, tcs(a3), a4, a5, a6)
#endif
FILE_EVENT7(20008, trace_ConnectionIn_PostCancelError_Impl, LOG_ERR, PAL_T("ConnectionIn: %p Post cancel cannot find entry for msg(%p:%d:%T:%x) on interaction [%p]<-%p"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MuxInOpen_AllocFailed() trace_MuxInOpen_AllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_MuxInOpen_AllocFailed() trace_MuxInOpen_AllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(20009, trace_MuxInOpen_AllocFailed_Impl, LOG_ERR, PAL_T("MuxIn_Open: cannot allocate ConnectionIn"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_AddCanceled(a0, a1, a2, a3, a4) trace_StrandEntryOperation_AddCanceled_Impl(__FILE__, __LINE__, a0, a1, scs(a2), a3, scs(a4))
#else
#define trace_StrandEntryOperation_AddCanceled(a0, a1, a2, a3, a4) trace_StrandEntryOperation_AddCanceled_Impl(0, 0, a0, a1, scs(a2), a3, scs(a4))
#endif
FILE_EVENT5(20010, trace_StrandEntryOperation_AddCanceled_Impl, LOG_ERR, PAL_T("_StrandEntryOperation_Add: Canceled %d entries %p(%s): %p(%s)"), unsigned int, StrandMany *, const char *, Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_AddFailed(a0, a1, a2, a3, a4) trace_StrandEntryOperation_AddFailed_Impl(__FILE__, __LINE__, a0, a1, scs(a2), a3, scs(a4))
#else
#define trace_StrandEntryOperation_AddFailed(a0, a1, a2, a3, a4) trace_StrandEntryOperation_AddFailed_Impl(0, 0, a0, a1, scs(a2), a3, scs(a4))
#endif
FILE_EVENT5(20011, trace_StrandEntryOperation_AddFailed_Impl, LOG_ERR, PAL_T("_StrandEntryOperation_Add: Failed %d entries %p(%s): %p(%s)"), unsigned int, StrandMany *, const char *, Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_CannotDelete(a0, a1, a2, a3) trace_Strand_CannotDelete_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_Strand_CannotDelete(a0, a1, a2, a3) trace_Strand_CannotDelete_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENT4(20012, trace_Strand_CannotDelete_Impl, LOG_ERR, PAL_T("Strand %p(%s), cannot delete entry %p(%s)"), Strand *, const char *, Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ScheduleFailed(a0, a1, a2, a3, a4) trace_Strand_ScheduleFailed_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4)
#else
#define trace_Strand_ScheduleFailed(a0, a1, a2, a3, a4) trace_Strand_ScheduleFailed_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4)
#endif
FILE_EVENT5(20013, trace_Strand_ScheduleFailed_Impl, LOG_ERR, PAL_T("_Strand_Schedule: %p(%s) FAILED Taking over opening, state %x(%s), methodBit: %x"), Strand *, const char *, ptrdiff_t, const char *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UserAuth_FailedToRead(a0) trace_UserAuth_FailedToRead_Impl(__FILE__, __LINE__, a0)
#else
#define trace_UserAuth_FailedToRead(a0) trace_UserAuth_FailedToRead_Impl(0, 0, a0)
#endif
FILE_EVENT1(20014, trace_UserAuth_FailedToRead_Impl, LOG_ERR, PAL_T("failed to read result from child; errno (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMany_CannotFindItem(a0, a1) trace_StrandMany_CannotFindItem_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandMany_CannotFindItem(a0, a1) trace_StrandMany_CannotFindItem_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20015, trace_StrandMany_CannotFindItem_Impl, LOG_ERR, PAL_T("cannot find request item %p; agent for user %d !"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItem_PostFailed(a0) trace_RequestItem_PostFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestItem_PostFailed(a0) trace_RequestItem_PostFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20016, trace_RequestItem_PostFailed_Impl, LOG_ERR, PAL_T("_RequestItem_Post: _PrepareMessageForAgent failed %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItem_Cancel_PrepMessageFailed(a0) trace_RequestItem_Cancel_PrepMessageFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestItem_Cancel_PrepMessageFailed(a0) trace_RequestItem_Cancel_PrepMessageFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20017, trace_RequestItem_Cancel_PrepMessageFailed_Impl, LOG_ERR, PAL_T("_RequestItem_Cancel: _PrepareMessageForAgent failed %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItem_Cancel_CancelMsg_NewFailed() trace_RequestItem_Cancel_CancelMsg_NewFailed_Impl(__FILE__, __LINE__)
#else
#define trace_RequestItem_Cancel_CancelMsg_NewFailed() trace_RequestItem_Cancel_CancelMsg_NewFailed_Impl(0, 0)
#endif
FILE_EVENT0(20018, trace_RequestItem_Cancel_CancelMsg_NewFailed_Impl, LOG_ERR, PAL_T("_RequestItem_Cancel: CancelMsg_New failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispatchEnumerateInstancesReq_OutOfMemory() trace_DispatchEnumerateInstancesReq_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace_DispatchEnumerateInstancesReq_OutOfMemory() trace_DispatchEnumerateInstancesReq_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENT0(20019, trace_DispatchEnumerateInstancesReq_OutOfMemory_Impl, LOG_ERR, PAL_T("_DispatchEnumerateInstancesReq() out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace__DispatchAssocReq_OutOfMemory() trace__DispatchAssocReq_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace__DispatchAssocReq_OutOfMemory() trace__DispatchAssocReq_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENT0(20020, trace__DispatchAssocReq_OutOfMemory_Impl, LOG_ERR, PAL_T("_DispatchAssocReq() out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_RequestAllocFailed(a0) trace_HTTP_RequestAllocFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_HTTP_RequestAllocFailed(a0) trace_HTTP_RequestAllocFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20021, trace_HTTP_RequestAllocFailed_Impl, LOG_ERR, PAL_T("HTTP: Error on allocating HttpRequest(%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpSocket_CannotPostMessage(a0, a1, a2, a3) trace_HttpSocket_CannotPostMessage_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_HttpSocket_CannotPostMessage(a0, a1, a2, a3) trace_HttpSocket_CannotPostMessage_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENT4(20022, trace_HttpSocket_CannotPostMessage_Impl, LOG_ERR, PAL_T("HttpSocket: %p Cannot posting message %p for interaction [%p]<-%p"), void *, Message *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_FailedToOpenPrivateKeyFile(a0) trace_SSL_FailedToOpenPrivateKeyFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_FailedToOpenPrivateKeyFile(a0) trace_SSL_FailedToOpenPrivateKeyFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20023, trace_SSL_FailedToOpenPrivateKeyFile_Impl, LOG_ERR, PAL_T("---> SSL: failed to open private key file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_FailedToCreatePrivateKey() trace_SSL_FailedToCreatePrivateKey_Impl(__FILE__, __LINE__)
#else
#define trace_SSL_FailedToCreatePrivateKey() trace_SSL_FailedToCreatePrivateKey_Impl(0, 0)
#endif
FILE_EVENT0(20024, trace_SSL_FailedToCreatePrivateKey_Impl, LOG_ERR, PAL_T("---> SSL: failed to create private key"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_NoPrivateKeyFound(a0) trace_SSL_NoPrivateKeyFound_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_NoPrivateKeyFound(a0) trace_SSL_NoPrivateKeyFound_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20025, trace_SSL_NoPrivateKeyFound_Impl, LOG_ERR, PAL_T("---> SSL: no private key found in %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_PrivateAndPublicKeyDonotMatch() trace_SSL_PrivateAndPublicKeyDonotMatch_Impl(__FILE__, __LINE__)
#else
#define trace_SSL_PrivateAndPublicKeyDonotMatch() trace_SSL_PrivateAndPublicKeyDonotMatch_Impl(0, 0)
#endif
FILE_EVENT0(20026, trace_SSL_PrivateAndPublicKeyDonotMatch_Impl, LOG_ERR, PAL_T("---> SSL: Private and public key do not match"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_CannotCreateContext() trace_SSL_CannotCreateContext_Impl(__FILE__, __LINE__)
#else
#define trace_SSL_CannotCreateContext() trace_SSL_CannotCreateContext_Impl(0, 0)
#endif
FILE_EVENT0(20027, trace_SSL_CannotCreateContext_Impl, LOG_ERR, PAL_T("---> SSL: cannot create ssl context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_CannotSetOptions(a0) trace_SSL_CannotSetOptions_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SSL_CannotSetOptions(a0) trace_SSL_CannotSetOptions_Impl(0, 0, a0)
#endif
FILE_EVENT1(20028, trace_SSL_CannotSetOptions_Impl, LOG_ERR, PAL_T("---> SSL: Unable to set server options for options flag %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_NoServerCertFound(a0, a1) trace_SSL_NoServerCertFound_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_SSL_NoServerCertFound(a0, a1) trace_SSL_NoServerCertFound_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(20029, trace_SSL_NoServerCertFound_Impl, LOG_ERR, PAL_T("---> SSL: No server certificate found in %s. %s"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_BadCipherList(a0) trace_SSL_BadCipherList_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_BadCipherList(a0) trace_SSL_BadCipherList_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20030, trace_SSL_BadCipherList_Impl, LOG_ERR, PAL_T("---> SSL: No matching ciphers found for: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ObjectContainerIsNotNull(a0, a1) trace_ObjectContainerIsNotNull_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ObjectContainerIsNotNull(a0, a1) trace_ObjectContainerIsNotNull_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20031, trace_ObjectContainerIsNotNull_Impl, LOG_ERR, PAL_T("Object %p's container is not NULL (%p)."), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ObjectUnexpectedContainer(a0, a1, a2) trace_ObjectUnexpectedContainer_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ObjectUnexpectedContainer(a0, a1, a2) trace_ObjectUnexpectedContainer_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENT3(20032, trace_ObjectUnexpectedContainer_Impl, LOG_ERR, PAL_T("Object %p has container (%p), expected (%p)."), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ObjectIsNotAValidFilter(a0) trace_ObjectIsNotAValidFilter_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ObjectIsNotAValidFilter(a0) trace_ObjectIsNotAValidFilter_Impl(0, 0, a0)
#endif
FILE_EVENT1(20033, trace_ObjectIsNotAValidFilter_Impl, LOG_ERR, PAL_T("Object %p is not a valid filter object."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ObjectIsnotValidListener(a0) trace_ObjectIsnotValidListener_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ObjectIsnotValidListener(a0) trace_ObjectIsnotValidListener_Impl(0, 0, a0)
#endif
FILE_EVENT1(20034, trace_ObjectIsnotValidListener_Impl, LOG_ERR, PAL_T("Object %p is not a valid Listener object."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ParseQueryFailed(a0) trace_ParseQueryFailed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_ParseQueryFailed(a0) trace_ParseQueryFailed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20035, trace_ParseQueryFailed_Impl, LOG_ERR, PAL_T("Parse query '%T' failed."), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnsupportedQueryLanguage(a0) trace_UnsupportedQueryLanguage_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_UnsupportedQueryLanguage(a0) trace_UnsupportedQueryLanguage_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20036, trace_UnsupportedQueryLanguage_Impl, LOG_ERR, PAL_T("Unsupported query language '%T'."), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TempSubscrCanHaveOnlyOneNamespace() trace_TempSubscrCanHaveOnlyOneNamespace_Impl(__FILE__, __LINE__)
#else
#define trace_TempSubscrCanHaveOnlyOneNamespace() trace_TempSubscrCanHaveOnlyOneNamespace_Impl(0, 0)
#endif
FILE_EVENT0(20037, trace_TempSubscrCanHaveOnlyOneNamespace_Impl, LOG_ERR, PAL_T("Temporary subscription can have only 1 target namespace."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotOpenAuthFile(a0) trace_CannotOpenAuthFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_CannotOpenAuthFile(a0) trace_CannotOpenAuthFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20038, trace_CannotOpenAuthFile_Impl, LOG_ERR, PAL_T("cannot open auth data file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotReadAuthFile(a0) trace_CannotReadAuthFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_CannotReadAuthFile(a0) trace_CannotReadAuthFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20039, trace_CannotReadAuthFile_Impl, LOG_ERR, PAL_T("cannot read from auth data file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PackInstanceFailed(a0) trace_PackInstanceFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_PackInstanceFailed(a0) trace_PackInstanceFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20040, trace_PackInstanceFailed_Impl, LOG_ERR, PAL_T("failed to pack instance: %u"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnmatchedFilterType() trace_UnmatchedFilterType_Impl(__FILE__, __LINE__)
#else
#define trace_UnmatchedFilterType() trace_UnmatchedFilterType_Impl(0, 0)
#endif
FILE_EVENT0(20041, trace_UnmatchedFilterType_Impl, LOG_ERR, PAL_T("Unmatched filter type"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProviderEnableIndication_Failed() trace_ProviderEnableIndication_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_ProviderEnableIndication_Failed() trace_ProviderEnableIndication_Failed_Impl(0, 0)
#endif
FILE_EVENT0(20042, trace_ProviderEnableIndication_Failed_Impl, LOG_ERR, PAL_T("_Provider_InvokeEnable: Provider posted final result during EnableIndications call"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AggregationContext_InitFailed() trace_AggregationContext_InitFailed_Impl(__FILE__, __LINE__)
#else
#define trace_AggregationContext_InitFailed() trace_AggregationContext_InitFailed_Impl(0, 0)
#endif
FILE_EVENT0(20043, trace_AggregationContext_InitFailed_Impl, LOG_ERR, PAL_T("AggregationContext allocation failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContextFailed() trace_SubscrContextFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SubscrContextFailed() trace_SubscrContextFailed_Impl(0, 0)
#endif
FILE_EVENT0(20044, trace_SubscrContextFailed_Impl, LOG_ERR, PAL_T("Failed to create SubscriptionContext"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToAddSubscrMgr() trace_FailedToAddSubscrMgr_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToAddSubscrMgr() trace_FailedToAddSubscrMgr_Impl(0, 0)
#endif
FILE_EVENT0(20045, trace_FailedToAddSubscrMgr_Impl, LOG_ERR, PAL_T("Failed to add subscription to manager"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EnableIndication_Failed(a0) trace_EnableIndication_Failed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_EnableIndication_Failed(a0) trace_EnableIndication_Failed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20046, trace_EnableIndication_Failed_Impl, LOG_ERR, PAL_T("Failed to enable indications on class (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnloadingActiveProvider(a0, a1) trace_UnloadingActiveProvider_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_UnloadingActiveProvider(a0, a1) trace_UnloadingActiveProvider_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(20047, trace_UnloadingActiveProvider_Impl, LOG_ERR, PAL_T("Unloading active provider %T, with ref counter %d"), const TChar *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnloadingActiveProviderWithLib(a0, a1) trace_UnloadingActiveProviderWithLib_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_UnloadingActiveProviderWithLib(a0, a1) trace_UnloadingActiveProviderWithLib_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20048, trace_UnloadingActiveProviderWithLib_Impl, LOG_ERR, PAL_T("Unloading active provider for lib %s, ref counter %d"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnloadingActiveProvider_ServerExit(a0) trace_UnloadingActiveProvider_ServerExit_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_UnloadingActiveProvider_ServerExit(a0) trace_UnloadingActiveProvider_ServerExit_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20049, trace_UnloadingActiveProvider_ServerExit_Impl, LOG_ERR, PAL_T("omiserver exited due to unloading active provider (%s). Please restart"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_AllocFailed() trace_SubMgrSubscription_AllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SubMgrSubscription_AllocFailed() trace_SubMgrSubscription_AllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(20050, trace_SubMgrSubscription_AllocFailed_Impl, LOG_ERR, PAL_T("SubMgrSubscription allocation failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionContext_InitFailed() trace_SubscriptionContext_InitFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SubscriptionContext_InitFailed() trace_SubscriptionContext_InitFailed_Impl(0, 0)
#endif
FILE_EVENT0(20051, trace_SubscriptionContext_InitFailed_Impl, LOG_ERR, PAL_T("SubscriptionContext init failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_AllocFailed() trace_InstanceFilter_AllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_AllocFailed() trace_InstanceFilter_AllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(20052, trace_InstanceFilter_AllocFailed_Impl, LOG_ERR, PAL_T("Instance filter allocation failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_InitPALTIME_Error(a0) trace_SelectorRun_InitPALTIME_Error_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SelectorRun_InitPALTIME_Error(a0) trace_SelectorRun_InitPALTIME_Error_Impl(0, 0, a0)
#endif
FILE_EVENT1(20053, trace_SelectorRun_InitPALTIME_Error_Impl, LOG_ERR, PAL_T("Selector_Run: %p Error on initial PAL_Time"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_SetSocketEventsError(a0, a1, a2) trace_SelectorRun_SetSocketEventsError_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SelectorRun_SetSocketEventsError(a0, a1, a2) trace_SelectorRun_SetSocketEventsError_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENT3(20054, trace_SelectorRun_SetSocketEventsError_Impl, LOG_ERR, PAL_T("Selector_Run: %p error %d on _SetSockEvents for handler: %p"), void *, int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_EmptyList(a0) trace_SelectorRun_EmptyList_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SelectorRun_EmptyList(a0) trace_SelectorRun_EmptyList_Impl(0, 0, a0)
#endif
FILE_EVENT1(20055, trace_SelectorRun_EmptyList_Impl, LOG_ERR, PAL_T("Selector_Run: %p Empty List"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_WaitError(a0, a1) trace_SelectorRun_WaitError_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SelectorRun_WaitError(a0, a1) trace_SelectorRun_WaitError_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20056, trace_SelectorRun_WaitError_Impl, LOG_ERR, PAL_T("Selector_Run: %p, Error on WaitForMultipleObjectsEx: %d"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_PALTimeError(a0) trace_SelectorRun_PALTimeError_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SelectorRun_PALTimeError(a0) trace_SelectorRun_PALTimeError_Impl(0, 0, a0)
#endif
FILE_EVENT1(20057, trace_SelectorRun_PALTimeError_Impl, LOG_ERR, PAL_T("Selector_Run: %p Error on PAL_Time"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_GetSocketEventsError(a0, a1, a2) trace_SelectorRun_GetSocketEventsError_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SelectorRun_GetSocketEventsError(a0, a1, a2) trace_SelectorRun_GetSocketEventsError_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENT3(20058, trace_SelectorRun_GetSocketEventsError_Impl, LOG_ERR, PAL_T("Selector_Run: %p error %d on _GetSockEvents for handler: %p"), void *, int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_HttpResponseMsg_ConversionError() trace_Wsman_HttpResponseMsg_ConversionError_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_HttpResponseMsg_ConversionError() trace_Wsman_HttpResponseMsg_ConversionError_Impl(0, 0)
#endif
FILE_EVENT0(20059, trace_Wsman_HttpResponseMsg_ConversionError_Impl, LOG_ERR, PAL_T("Conversion of response page to UTF-8 failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockWrite_Failed(a0) trace_SockWrite_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SockWrite_Failed(a0) trace_SockWrite_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20060, trace_SockWrite_Failed_Impl, LOG_ERR, PAL_T("Sock_Write failed with unknown error (%u)"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketFilePathTooLong(a0, a1) trace_SocketFilePathTooLong_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_SocketFilePathTooLong(a0, a1) trace_SocketFilePathTooLong_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENT2(20061, trace_SocketFilePathTooLong_Impl, LOG_ERR, PAL_T("socket file path too long (> %u): '%s'"), MI_Uint32, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_HttpResponseMsgPage_AllocError(a0) trace_Wsman_HttpResponseMsgPage_AllocError_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_HttpResponseMsgPage_AllocError(a0) trace_Wsman_HttpResponseMsgPage_AllocError_Impl(0, 0, a0)
#endif
FILE_EVENT1(20062, trace_Wsman_HttpResponseMsgPage_AllocError_Impl, LOG_ERR, PAL_T("Wsman: Error on allocating HttpResponseMsg Page (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_HttpResponseMsg_AllocError(a0) trace_Wsman_HttpResponseMsg_AllocError_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_HttpResponseMsg_AllocError(a0) trace_Wsman_HttpResponseMsg_AllocError_Impl(0, 0, a0)
#endif
FILE_EVENT1(20063, trace_Wsman_HttpResponseMsg_AllocError_Impl, LOG_ERR, PAL_T("Wsman: Error on allocating HttpResponseMsg (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess(a0) trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess(a0) trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess_Impl(0, 0, a0)
#endif
FILE_EVENT1(20064, trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess_Impl, LOG_ERR, PAL_T("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) received duplicate success subscribe response"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpCallbackOnNewConnection_OutOfMemory() trace_HttpCallbackOnNewConnection_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace_HttpCallbackOnNewConnection_OutOfMemory() trace_HttpCallbackOnNewConnection_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENT0(20065, trace_HttpCallbackOnNewConnection_OutOfMemory_Impl, LOG_ERR, PAL_T("_HttpCallbackOnNewConnection: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OutOfMemory() trace_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace_OutOfMemory() trace_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENT0(20066, trace_OutOfMemory_Impl, LOG_ERR, PAL_T("out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OpenCloseMismatch(a0, a1) trace_OpenCloseMismatch_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_OpenCloseMismatch(a0, a1) trace_OpenCloseMismatch_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(20067, trace_OpenCloseMismatch_Impl, LOG_ERR, PAL_T("open/close mismatch: {%T}{%T}"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifeCycleSubscription_UnsupportedClass(a0) trace_LifeCycleSubscription_UnsupportedClass_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_LifeCycleSubscription_UnsupportedClass(a0) trace_LifeCycleSubscription_UnsupportedClass_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20068, trace_LifeCycleSubscription_UnsupportedClass_Impl, LOG_ERR, PAL_T("Lifecycle subscription request for unsupported class (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToConstructInstance(a0) trace_FailedToConstructInstance_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_FailedToConstructInstance(a0) trace_FailedToConstructInstance_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20069, trace_FailedToConstructInstance_Impl, LOG_ERR, PAL_T("Failed to construct instance of %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_CommonProperties(a0) trace_FailedToSet_CommonProperties_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_FailedToSet_CommonProperties(a0) trace_FailedToSet_CommonProperties_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(20070, trace_FailedToSet_CommonProperties_Impl, LOG_ERR, PAL_T("Failed to set common properties for %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_CorrelatedIndications() trace_FailedToSet_CorrelatedIndications_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_CorrelatedIndications() trace_FailedToSet_CorrelatedIndications_Impl(0, 0)
#endif
FILE_EVENT0(20071, trace_FailedToSet_CorrelatedIndications_Impl, LOG_ERR, PAL_T("Failed to set CorrelatedIndications with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_IndicationFilterName() trace_FailedToSet_IndicationFilterName_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_IndicationFilterName() trace_FailedToSet_IndicationFilterName_Impl(0, 0)
#endif
FILE_EVENT0(20072, trace_FailedToSet_IndicationFilterName_Impl, LOG_ERR, PAL_T("Failed to set IndicationFilterName with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_IndicationIdentifier() trace_FailedToSet_IndicationIdentifier_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_IndicationIdentifier() trace_FailedToSet_IndicationIdentifier_Impl(0, 0)
#endif
FILE_EVENT0(20073, trace_FailedToSet_IndicationIdentifier_Impl, LOG_ERR, PAL_T("Failed to set IndicationIdentifier with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_IndicationTime() trace_FailedToSet_IndicationTime_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_IndicationTime() trace_FailedToSet_IndicationTime_Impl(0, 0)
#endif
FILE_EVENT0(20074, trace_FailedToSet_IndicationTime_Impl, LOG_ERR, PAL_T("Failed to set IndicationTime with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_MethodName() trace_FailedToSet_MethodName_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_MethodName() trace_FailedToSet_MethodName_Impl(0, 0)
#endif
FILE_EVENT0(20075, trace_FailedToSet_MethodName_Impl, LOG_ERR, PAL_T("Failed to set MethodName"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_MethodParameters() trace_FailedToSet_MethodParameters_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_MethodParameters() trace_FailedToSet_MethodParameters_Impl(0, 0)
#endif
FILE_EVENT0(20076, trace_FailedToSet_MethodParameters_Impl, LOG_ERR, PAL_T("Failed to set MethodParameters"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_OtherSeverity() trace_FailedToSet_OtherSeverity_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_OtherSeverity() trace_FailedToSet_OtherSeverity_Impl(0, 0)
#endif
FILE_EVENT0(20077, trace_FailedToSet_OtherSeverity_Impl, LOG_ERR, PAL_T("Failed to set OtherSeverity with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_PerceivedSeverity() trace_FailedToSet_PerceivedSeverity_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_PerceivedSeverity() trace_FailedToSet_PerceivedSeverity_Impl(0, 0)
#endif
FILE_EVENT0(20078, trace_FailedToSet_PerceivedSeverity_Impl, LOG_ERR, PAL_T("Failed to set PerceivedSeverity with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_PreCall() trace_FailedToSet_PreCall_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_PreCall() trace_FailedToSet_PreCall_Impl(0, 0)
#endif
FILE_EVENT0(20079, trace_FailedToSet_PreCall_Impl, LOG_ERR, PAL_T("Failed to set PreCall"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_PreviousInstance() trace_FailedToSet_PreviousInstance_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_PreviousInstance() trace_FailedToSet_PreviousInstance_Impl(0, 0)
#endif
FILE_EVENT0(20080, trace_FailedToSet_PreviousInstance_Impl, LOG_ERR, PAL_T("Failed to set PreviousInstance"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_ReturnValue() trace_FailedToSet_ReturnValue_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_ReturnValue() trace_FailedToSet_ReturnValue_Impl(0, 0)
#endif
FILE_EVENT0(20081, trace_FailedToSet_ReturnValue_Impl, LOG_ERR, PAL_T("Failed to set ReturnValue"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_SequenceContext() trace_FailedToSet_SequenceContext_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_SequenceContext() trace_FailedToSet_SequenceContext_Impl(0, 0)
#endif
FILE_EVENT0(20082, trace_FailedToSet_SequenceContext_Impl, LOG_ERR, PAL_T("Failed to set SequenceContext with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_SequenceNumber() trace_FailedToSet_SequenceNumber_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_SequenceNumber() trace_FailedToSet_SequenceNumber_Impl(0, 0)
#endif
FILE_EVENT0(20083, trace_FailedToSet_SequenceNumber_Impl, LOG_ERR, PAL_T("Failed to set SequenceNumber with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_SourceInstance() trace_FailedToSet_SourceInstance_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_SourceInstance() trace_FailedToSet_SourceInstance_Impl(0, 0)
#endif
FILE_EVENT0(20084, trace_FailedToSet_SourceInstance_Impl, LOG_ERR, PAL_T("Failed to set SourceInstance with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_SourceInstanceHost() trace_FailedToSet_SourceInstanceHost_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_SourceInstanceHost() trace_FailedToSet_SourceInstanceHost_Impl(0, 0)
#endif
FILE_EVENT0(20085, trace_FailedToSet_SourceInstanceHost_Impl, LOG_ERR, PAL_T("Failed to set SourceInstanceHost with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToSet_SourceInstanceModelPath() trace_FailedToSet_SourceInstanceModelPath_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToSet_SourceInstanceModelPath() trace_FailedToSet_SourceInstanceModelPath_Impl(0, 0)
#endif
FILE_EVENT0(20086, trace_FailedToSet_SourceInstanceModelPath_Impl, LOG_ERR, PAL_T("Failed to set SourceInstanceModelPath with ABC"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifecycleSubscription_UnsupportedTargetType(a0, a1, a2) trace_LifecycleSubscription_UnsupportedTargetType_Impl(__FILE__, __LINE__, tcs(a0), a1, a2)
#else
#define trace_LifecycleSubscription_UnsupportedTargetType(a0, a1, a2) trace_LifecycleSubscription_UnsupportedTargetType_Impl(0, 0, tcs(a0), a1, a2)
#endif
FILE_EVENT3(20087, trace_LifecycleSubscription_UnsupportedTargetType_Impl, LOG_ERR, PAL_T("Lifecycle subscription request of class (%T) for unsupported targetType (%d). Supported is (0x%X)"), const TChar *, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provmgr_NullModulePointer(a0, a1) trace_Provmgr_NullModulePointer_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_Provmgr_NullModulePointer(a0, a1) trace_Provmgr_NullModulePointer_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(20088, trace_Provmgr_NullModulePointer_Impl, LOG_ERR, PAL_T("NULL module pointer returned by shared library: %s: %s"), const char*, const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provmgr_FailedToLoadProvider(a0, a1, a2, a3, a4, a5, a6) trace_Provmgr_FailedToLoadProvider_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3, a4, a5, a6)
#else
#define trace_Provmgr_FailedToLoadProvider(a0, a1, a2, a3, a4, a5, a6) trace_Provmgr_FailedToLoadProvider_Impl(0, 0, scs(a0), a1, a2, a3, a4, a5, a6)
#endif
FILE_EVENT7(20089, trace_Provmgr_FailedToLoadProvider_Impl, LOG_ERR, PAL_T("Failed to load provider %s, due to it's version (%d.%d.%d) is newer than server version (%d.%d.%d)"), const char*, MI_Uint16, MI_Uint16, MI_Uint16, MI_Uint16, MI_Uint16, MI_Uint16)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_EvaluateWithNullInput() trace_InstanceFilter_EvaluateWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_EvaluateWithNullInput() trace_InstanceFilter_EvaluateWithNullInput_Impl(0, 0)
#endif
FILE_EVENT0(20090, trace_InstanceFilter_EvaluateWithNullInput_Impl, LOG_ERR, PAL_T("InstanceFilter_Evaluate: NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_GetExpressionWithNullInput() trace_InstanceFilter_GetExpressionWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_GetExpressionWithNullInput() trace_InstanceFilter_GetExpressionWithNullInput_Impl(0, 0)
#endif
FILE_EVENT0(20091, trace_InstanceFilter_GetExpressionWithNullInput_Impl, LOG_ERR, PAL_T("InstanceFilter_GetExpression: NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_NewWithNullInput() trace_InstanceFilter_NewWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_NewWithNullInput() trace_InstanceFilter_NewWithNullInput_Impl(0, 0)
#endif
FILE_EVENT0(20092, trace_InstanceFilter_NewWithNullInput_Impl, LOG_ERR, PAL_T("InstanceFilter_New: NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag() trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag() trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag_Impl(0, 0)
#endif
FILE_EVENT0(20093, trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag_Impl, LOG_ERR, PAL_T("InstanceFilter_GetQueyExpression: Unsupported Message Tag"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag() trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag_Impl(__FILE__, __LINE__)
#else
#define trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag() trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag_Impl(0, 0)
#endif
FILE_EVENT0(20094, trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag_Impl, LOG_ERR, PAL_T("InstanceFilter_GetQueryLanguage: Unsupported Message Tag"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIFailedToOpenConfigFile(a0) trace_MIFailedToOpenConfigFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_MIFailedToOpenConfigFile(a0) trace_MIFailedToOpenConfigFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20095, trace_MIFailedToOpenConfigFile_Impl, LOG_ERR, PAL_T("failed to open configuration file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIFailedToReadConfigValue(a0, a1) trace_MIFailedToReadConfigValue_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_MIFailedToReadConfigValue(a0, a1) trace_MIFailedToReadConfigValue_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(20096, trace_MIFailedToReadConfigValue_Impl, LOG_ERR, PAL_T("%s: %s\n"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIConfig_InvalidValue(a0, a1, a2, a3) trace_MIConfig_InvalidValue_Impl(__FILE__, __LINE__, scs(a0), a1, scs(a2), scs(a3))
#else
#define trace_MIConfig_InvalidValue(a0, a1, a2, a3) trace_MIConfig_InvalidValue_Impl(0, 0, scs(a0), a1, scs(a2), scs(a3))
#endif
FILE_EVENT4(20097, trace_MIConfig_InvalidValue_Impl, LOG_ERR, PAL_T("%s(%u): invalid value for '%s': %s"), const char *, unsigned int, const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MILeaveSession(a0, a1) trace_MILeaveSession_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MILeaveSession(a0, a1) trace_MILeaveSession_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20098, trace_MILeaveSession_Impl, LOG_ERR, PAL_T("Leave %s with session (%p)."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIInvalidSession(a0, a1) trace_MIInvalidSession_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MIInvalidSession(a0, a1) trace_MIInvalidSession_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20099, trace_MIInvalidSession_Impl, LOG_ERR, PAL_T("Leave %s due to invalid session (%p) or it has invalid thunkHandle."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MISessionInvalidThunkHandle(a0, a1) trace_MISessionInvalidThunkHandle_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MISessionInvalidThunkHandle(a0, a1) trace_MISessionInvalidThunkHandle_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20100, trace_MISessionInvalidThunkHandle_Impl, LOG_ERR, PAL_T("Leave %s due to session (%p) has invalid thunkHandle."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MISession_AccessCheckFailed(a0, a1) trace_MISession_AccessCheckFailed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MISession_AccessCheckFailed(a0, a1) trace_MISession_AccessCheckFailed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20101, trace_MISession_AccessCheckFailed_Impl, LOG_ERR, PAL_T("Leave %s due to Session AccessCheck on session (%p) failed."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MISession_InvalidSessionThunk(a0, a1) trace_MISession_InvalidSessionThunk_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MISession_InvalidSessionThunk(a0, a1) trace_MISession_InvalidSessionThunk_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20102, trace_MISession_InvalidSessionThunk_Impl, LOG_ERR, PAL_T("Leave %s due to session (%p) has invalid sessionThunk."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MiSession_AccessCheckFailed(a0, a1) trace_MiSession_AccessCheckFailed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MiSession_AccessCheckFailed(a0, a1) trace_MiSession_AccessCheckFailed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20103, trace_MiSession_AccessCheckFailed_Impl, LOG_ERR, PAL_T("Leave %s due to Session AccessCheck on session (%p) failed."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIThunk_InvalidHandle(a0) trace_MIThunk_InvalidHandle_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MIThunk_InvalidHandle(a0) trace_MIThunk_InvalidHandle_Impl(0, 0, a0)
#endif
FILE_EVENT1(20104, trace_MIThunk_InvalidHandle_Impl, LOG_ERR, PAL_T("Trying to thunk invalid generic handle: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIThunk_OldVersion(a0) trace_MIThunk_OldVersion_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MIThunk_OldVersion(a0) trace_MIThunk_OldVersion_Impl(0, 0, a0)
#endif
FILE_EVENT1(20105, trace_MIThunk_OldVersion_Impl, LOG_ERR, PAL_T("Trying to thunk generic handle that has an old version number: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIThunk_AlreadyShutdown(a0) trace_MIThunk_AlreadyShutdown_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MIThunk_AlreadyShutdown(a0) trace_MIThunk_AlreadyShutdown_Impl(0, 0, a0)
#endif
FILE_EVENT1(20106, trace_MIThunk_AlreadyShutdown_Impl, LOG_ERR, PAL_T("Trying to thunk generic handle that has been shutdown already: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_CannotStartTimer_AlreadyRunning(a0) trace_Timer_CannotStartTimer_AlreadyRunning_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_CannotStartTimer_AlreadyRunning(a0) trace_Timer_CannotStartTimer_AlreadyRunning_Impl(0, 0, a0)
#endif
FILE_EVENT1(20107, trace_Timer_CannotStartTimer_AlreadyRunning_Impl, LOG_ERR, PAL_T("Timer_Start:Timer (%p) already running"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Initialization_Failed(a0) trace_Timer_Initialization_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Initialization_Failed(a0) trace_Timer_Initialization_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(20108, trace_Timer_Initialization_Failed_Impl, LOG_ERR, PAL_T("Timer_Start:Timer cannot be initialized - Error (%x)"), PAL_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Selector_Missing(a0) trace_Timer_Selector_Missing_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Selector_Missing(a0) trace_Timer_Selector_Missing_Impl(0, 0, a0)
#endif
FILE_EVENT1(20109, trace_Timer_Selector_Missing_Impl, LOG_ERR, PAL_T("Timer_Start:Selector not specified or initialized (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Cannot_AccessCurrentTime() trace_Timer_Cannot_AccessCurrentTime_Impl(__FILE__, __LINE__)
#else
#define trace_Timer_Cannot_AccessCurrentTime() trace_Timer_Cannot_AccessCurrentTime_Impl(0, 0)
#endif
FILE_EVENT0(20110, trace_Timer_Cannot_AccessCurrentTime_Impl, LOG_ERR, PAL_T("Timer: Unable to access current time"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Cannot_AddHandlerToSelector(a0) trace_Timer_Cannot_AddHandlerToSelector_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Cannot_AddHandlerToSelector(a0) trace_Timer_Cannot_AddHandlerToSelector_Impl(0, 0, a0)
#endif
FILE_EVENT1(20111, trace_Timer_Cannot_AddHandlerToSelector_Impl, LOG_ERR, PAL_T("Timer_Start: Unable to add handler to selector (%p"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Double_Close(a0) trace_Timer_Double_Close_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Double_Close(a0) trace_Timer_Double_Close_Impl(0, 0, a0)
#endif
FILE_EVENT1(20112, trace_Timer_Double_Close_Impl, LOG_ERR, PAL_T("Timer_Close: Double close of timer (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Unexpected_Selector_Mask(a0) trace_Timer_Unexpected_Selector_Mask_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Unexpected_Selector_Mask(a0) trace_Timer_Unexpected_Selector_Mask_Impl(0, 0, a0)
#endif
FILE_EVENT1(20113, trace_Timer_Unexpected_Selector_Mask_Impl, LOG_ERR, PAL_T("Timer_Callback: Unexpected Selector mask %u"), PAL_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InvalidOperationTimeoutValue_Timestamp() trace_Wsman_InvalidOperationTimeoutValue_Timestamp_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_InvalidOperationTimeoutValue_Timestamp() trace_Wsman_InvalidOperationTimeoutValue_Timestamp_Impl(0, 0)
#endif
FILE_EVENT0(20114, trace_Wsman_InvalidOperationTimeoutValue_Timestamp_Impl, LOG_ERR, PAL_T("_ValidateHeader: OperationTimeout must be xs:duration"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PreExecFailed(a0) trace_PreExecFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_PreExecFailed(a0) trace_PreExecFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20115, trace_PreExecFailed_Impl, LOG_ERR, PAL_T("Failed to execute PREEXEC program: {%s}"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InvokeSubscribeWithInvalidTargetType(a0) trace_InvokeSubscribeWithInvalidTargetType_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InvokeSubscribeWithInvalidTargetType(a0) trace_InvokeSubscribeWithInvalidTargetType_Impl(0, 0, a0)
#endif
FILE_EVENT1(20116, trace_InvokeSubscribeWithInvalidTargetType_Impl, LOG_ERR, PAL_T("_Provider_InvokeSubscribe: Unsupported subscription type %x"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_SessionAlreadyConnected(a0) trace_MI_SessionAlreadyConnected_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MI_SessionAlreadyConnected(a0) trace_MI_SessionAlreadyConnected_Impl(0, 0, a0)
#endif
FILE_EVENT1(20117, trace_MI_SessionAlreadyConnected_Impl, LOG_ERR, PAL_T("MI Session already connected, operation %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_OutOfMemoryInOperation(a0) trace_MI_OutOfMemoryInOperation_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MI_OutOfMemoryInOperation(a0) trace_MI_OutOfMemoryInOperation_Impl(0, 0, a0)
#endif
FILE_EVENT1(20118, trace_MI_OutOfMemoryInOperation_Impl, LOG_ERR, PAL_T("Out of memory error, operation %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_SocketConnectorFailed(a0, a1) trace_MI_SocketConnectorFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MI_SocketConnectorFailed(a0, a1) trace_MI_SocketConnectorFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20119, trace_MI_SocketConnectorFailed_Impl, LOG_ERR, PAL_T("MI Socket connector failed, operation %p, result %d"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_FailedToStartRunThread(a0) trace_MI_FailedToStartRunThread_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MI_FailedToStartRunThread(a0) trace_MI_FailedToStartRunThread_Impl(0, 0, a0)
#endif
FILE_EVENT1(20120, trace_MI_FailedToStartRunThread_Impl, LOG_ERR, PAL_T("MI client failed to start run thread, operation %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_SessionFailed(a0, a1) trace_MI_SessionFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MI_SessionFailed(a0, a1) trace_MI_SessionFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20121, trace_MI_SessionFailed_Impl, LOG_ERR, PAL_T("MI session init failed, session %p, result %d"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_OutOfMemoryInSession(a0) trace_MI_OutOfMemoryInSession_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MI_OutOfMemoryInSession(a0) trace_MI_OutOfMemoryInSession_Impl(0, 0, a0)
#endif
FILE_EVENT1(20122, trace_MI_OutOfMemoryInSession_Impl, LOG_ERR, PAL_T("Out of memory error, session %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_SessionConnectFailed(a0, a1) trace_MI_SessionConnectFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MI_SessionConnectFailed(a0, a1) trace_MI_SessionConnectFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20123, trace_MI_SessionConnectFailed_Impl, LOG_ERR, PAL_T("InteractionProtocolHandler_Session_Connect failed, session %p, result %d"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MI_InstanceToBatch_Failed(a0, a1) trace_MI_InstanceToBatch_Failed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MI_InstanceToBatch_Failed(a0, a1) trace_MI_InstanceToBatch_Failed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(20124, trace_MI_InstanceToBatch_Failed_Impl, LOG_ERR, PAL_T("InstantchToBatch failed in MI session, session %p, result %d"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketConnectorFailed(a0) trace_SocketConnectorFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SocketConnectorFailed(a0) trace_SocketConnectorFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20125, trace_SocketConnectorFailed_Impl, LOG_ERR, PAL_T("Socket connect failed, locator %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LocalSocketFailed(a0) trace_LocalSocketFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_LocalSocketFailed(a0) trace_LocalSocketFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20126, trace_LocalSocketFailed_Impl, LOG_ERR, PAL_T("Local socket failed on socket() call, sock %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LocalSocket_SetOnExecFailed(a0) trace_LocalSocket_SetOnExecFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_LocalSocket_SetOnExecFailed(a0) trace_LocalSocket_SetOnExecFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20127, trace_LocalSocket_SetOnExecFailed_Impl, LOG_ERR, PAL_T("Socket SetOnExec failed, %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LocalSocket_SetBlockingFailed(a0) trace_LocalSocket_SetBlockingFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_LocalSocket_SetBlockingFailed(a0) trace_LocalSocket_SetBlockingFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20128, trace_LocalSocket_SetBlockingFailed_Impl, LOG_ERR, PAL_T("Socket SetBlocking failed, %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LocalSocket_ConnectFailed(a0, a1) trace_LocalSocket_ConnectFailed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_LocalSocket_ConnectFailed(a0, a1) trace_LocalSocket_ConnectFailed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(20129, trace_LocalSocket_ConnectFailed_Impl, LOG_ERR, PAL_T("Socket connect() failed, %s, error %d"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_VerifyFailed(a0, a1) trace_SSL_VerifyFailed_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_SSL_VerifyFailed(a0, a1) trace_SSL_VerifyFailed_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENT2(20130, trace_SSL_VerifyFailed_Impl, LOG_ERR, PAL_T("SSL error %d verifying with certificate: %s"), int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_BadTrustDir(a0) trace_SSL_BadTrustDir_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_BadTrustDir(a0) trace_SSL_BadTrustDir_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20131, trace_SSL_BadTrustDir_Impl, LOG_ERR, PAL_T("Bad SSL trusted certificates directory: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_ProvRegEntry_NULLLibraryName(a0, a1) trace_ProvReg_ProvRegEntry_NULLLibraryName_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_ProvReg_ProvRegEntry_NULLLibraryName(a0, a1) trace_ProvReg_ProvRegEntry_NULLLibraryName_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(20132, trace_ProvReg_ProvRegEntry_NULLLibraryName_Impl, LOG_ERR, PAL_T("Library name is NULL for class: %S, in namespace: %S. Library Name should NOT be NULL"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_SkipRegFile(a0) trace_ProvReg_SkipRegFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_ProvReg_SkipRegFile(a0) trace_ProvReg_SkipRegFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20133, trace_ProvReg_SkipRegFile_Impl, LOG_ERR, PAL_T("Reg file %s is corrupted. It will be skipped by the server"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_MissingLibraryTag(a0) trace_RegFile_MissingLibraryTag_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_RegFile_MissingLibraryTag(a0) trace_RegFile_MissingLibraryTag_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20134, trace_RegFile_MissingLibraryTag_Impl, LOG_ERR, PAL_T("LIBRARY tag is missing in reg file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NtlmCredFileInvalid(a0) trace_NtlmCredFileInvalid_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_NtlmCredFileInvalid(a0) trace_NtlmCredFileInvalid_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20135, trace_NtlmCredFileInvalid_Impl, LOG_ERR, PAL_T("NTLM Credentials file does not exist or invalid permissions: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InvalidEngineCredentials() trace_InvalidEngineCredentials_Impl(__FILE__, __LINE__)
#else
#define trace_InvalidEngineCredentials() trace_InvalidEngineCredentials_Impl(0, 0)
#endif
FILE_EVENT0(20136, trace_InvalidEngineCredentials_Impl, LOG_ERR, PAL_T("Invalid engine credentials"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineCredentialsNotReceived() trace_EngineCredentialsNotReceived_Impl(__FILE__, __LINE__)
#else
#define trace_EngineCredentialsNotReceived() trace_EngineCredentialsNotReceived_Impl(0, 0)
#endif
FILE_EVENT0(20137, trace_EngineCredentialsNotReceived_Impl, LOG_ERR, PAL_T("Engine credentials have not been received"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TrackerHashMapError() trace_TrackerHashMapError_Impl(__FILE__, __LINE__)
#else
#define trace_TrackerHashMapError() trace_TrackerHashMapError_Impl(0, 0)
#endif
FILE_EVENT0(20138, trace_TrackerHashMapError_Impl, LOG_ERR, PAL_T("Tracker hash map error"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClientCredentialsNotVerified(a0) trace_ClientCredentialsNotVerified_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ClientCredentialsNotVerified(a0) trace_ClientCredentialsNotVerified_Impl(0, 0, a0)
#endif
FILE_EVENT1(20139, trace_ClientCredentialsNotVerified_Impl, LOG_ERR, PAL_T("Client credentials not yet verified. Msg type = %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClientCredentialsNotReceived(a0) trace_ClientCredentialsNotReceived_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ClientCredentialsNotReceived(a0) trace_ClientCredentialsNotReceived_Impl(0, 0, a0)
#endif
FILE_EVENT1(20140, trace_ClientCredentialsNotReceived_Impl, LOG_ERR, PAL_T("Client credentials not yet received. Msg type = %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedNewServerConnection() trace_FailedNewServerConnection_Impl(__FILE__, __LINE__)
#else
#define trace_FailedNewServerConnection() trace_FailedNewServerConnection_Impl(0, 0)
#endif
FILE_EVENT0(20141, trace_FailedNewServerConnection_Impl, LOG_ERR, PAL_T("Failed to create new server connection"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedSendPamRequest() trace_FailedSendPamRequest_Impl(__FILE__, __LINE__)
#else
#define trace_FailedSendPamRequest() trace_FailedSendPamRequest_Impl(0, 0)
#endif
FILE_EVENT0(20142, trace_FailedSendPamRequest_Impl, LOG_ERR, PAL_T("Failed to send PAM auth request to server"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerFailedPamFile() trace_ServerFailedPamFile_Impl(__FILE__, __LINE__)
#else
#define trace_ServerFailedPamFile() trace_ServerFailedPamFile_Impl(0, 0)
#endif
FILE_EVENT0(20143, trace_ServerFailedPamFile_Impl, LOG_ERR, PAL_T("Server failed to open PAM file"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InvalidInProcProvider(a0) trace_InvalidInProcProvider_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_InvalidInProcProvider(a0) trace_InvalidInProcProvider_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(20144, trace_InvalidInProcProvider_Impl, LOG_ERR, PAL_T("InProc providers are no longer supported: (%s). Defaulting to @requestor"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineAuthenticateNullHandler() trace_EngineAuthenticateNullHandler_Impl(__FILE__, __LINE__)
#else
#define trace_EngineAuthenticateNullHandler() trace_EngineAuthenticateNullHandler_Impl(0, 0)
#endif
FILE_EVENT0(20145, trace_EngineAuthenticateNullHandler_Impl, LOG_ERR, PAL_T("Engine AskServerToAuthenticate received NULL handle"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineAuthenticateNullCallback() trace_EngineAuthenticateNullCallback_Impl(__FILE__, __LINE__)
#else
#define trace_EngineAuthenticateNullCallback() trace_EngineAuthenticateNullCallback_Impl(0, 0)
#endif
FILE_EVENT0(20146, trace_EngineAuthenticateNullCallback_Impl, LOG_ERR, PAL_T("Engine AskServerToAuthenticate received NULL callback"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_ClientAuthFailed(a0, a1) trace_HTTP_ClientAuthFailed_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_HTTP_ClientAuthFailed(a0, a1) trace_HTTP_ClientAuthFailed_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(20147, trace_HTTP_ClientAuthFailed_Impl, LOG_ERR, PAL_T("HTTP: Client Authorization failed. gss:(%s) mech:(%s)"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace__FindSubRequest_CannotFindKey(a0, a1, a2) trace__FindSubRequest_CannotFindKey_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace__FindSubRequest_CannotFindKey(a0, a1, a2) trace__FindSubRequest_CannotFindKey_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENT3(30000, trace__FindSubRequest_CannotFindKey_Impl, LOG_WARNING, PAL_T("__FindSubRequest: SubscribeElem %p(%p), Cannot find key: %x"), void *, Strand *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentElem_FindRequest_CannotFindKey(a0, a1, a2) trace_AgentElem_FindRequest_CannotFindKey_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_AgentElem_FindRequest_CannotFindKey(a0, a1, a2) trace_AgentElem_FindRequest_CannotFindKey_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENT3(30001, trace_AgentElem_FindRequest_CannotFindKey_Impl, LOG_WARNING, PAL_T("_AgentElem_FindRequest, Agent %p(%p), Cannot find key: %x"), void *, Strand *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverIndicationClass_CreateInstanceFailed(a0) trace_DiscoverIndicationClass_CreateInstanceFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_DiscoverIndicationClass_CreateInstanceFailed(a0) trace_DiscoverIndicationClass_CreateInstanceFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30002, trace_DiscoverIndicationClass_CreateInstanceFailed_Impl, LOG_WARNING, PAL_T("_DiscoverIndicationClass: Create error instance failed with (%d)"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverIndicationClass_InvalidLifeCycleQuery() trace_DiscoverIndicationClass_InvalidLifeCycleQuery_Impl(__FILE__, __LINE__)
#else
#define trace_DiscoverIndicationClass_InvalidLifeCycleQuery() trace_DiscoverIndicationClass_InvalidLifeCycleQuery_Impl(0, 0)
#endif
FILE_EVENT0(30003, trace_DiscoverIndicationClass_InvalidLifeCycleQuery_Impl, LOG_WARNING, PAL_T("_DiscoverIndicationClass: Invalid lifecycle query"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverIndicationClass_UnsupportedTargetClassType(a0) trace_DiscoverIndicationClass_UnsupportedTargetClassType_Impl(__FILE__, __LINE__, a0)
#else
#define trace_DiscoverIndicationClass_UnsupportedTargetClassType(a0) trace_DiscoverIndicationClass_UnsupportedTargetClassType_Impl(0, 0, a0)
#endif
FILE_EVENT1(30004, trace_DiscoverIndicationClass_UnsupportedTargetClassType_Impl, LOG_WARNING, PAL_T("_DiscoverIndicationClass: Unsupported target class type (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_EvalHasMoreThanOneSymbol(a0) trace_FindLifecycleClass_EvalHasMoreThanOneSymbol_Impl(__FILE__, __LINE__, a0)
#else
#define trace_FindLifecycleClass_EvalHasMoreThanOneSymbol(a0) trace_FindLifecycleClass_EvalHasMoreThanOneSymbol_Impl(0, 0, a0)
#endif
FILE_EVENT1(30005, trace_FindLifecycleClass_EvalHasMoreThanOneSymbol_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Evaluation result does not have exactly one symbol (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_EvalResultIsNotBool() trace_FindLifecycleClass_EvalResultIsNotBool_Impl(__FILE__, __LINE__)
#else
#define trace_FindLifecycleClass_EvalResultIsNotBool() trace_FindLifecycleClass_EvalResultIsNotBool_Impl(0, 0)
#endif
FILE_EVENT0(30006, trace_FindLifecycleClass_EvalResultIsNotBool_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Evaluation result is not boolean"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_FoundISAOperator(a0, a1) trace_FindLifecycleClass_FoundISAOperator_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_FindLifecycleClass_FoundISAOperator(a0, a1) trace_FindLifecycleClass_FoundISAOperator_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(30007, trace_FindLifecycleClass_FoundISAOperator_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Found ISA operator for embedded property (%T), target class (%T)"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_InvalidEmbeddedProperty(a0) trace_FindLifecycleClass_InvalidEmbeddedProperty_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_FindLifecycleClass_InvalidEmbeddedProperty(a0) trace_FindLifecycleClass_InvalidEmbeddedProperty_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30008, trace_FindLifecycleClass_InvalidEmbeddedProperty_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Invalid embedded property name (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_InvalidLifecycleQuery() trace_FindLifecycleClass_InvalidLifecycleQuery_Impl(__FILE__, __LINE__)
#else
#define trace_FindLifecycleClass_InvalidLifecycleQuery() trace_FindLifecycleClass_InvalidLifecycleQuery_Impl(0, 0)
#endif
FILE_EVENT0(30009, trace_FindLifecycleClass_InvalidLifecycleQuery_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Invalid lifecycle query due to ISA operator is within an OR operator sub clause"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_InvalidTokenType() trace_FindLifecycleClass_InvalidTokenType_Impl(__FILE__, __LINE__)
#else
#define trace_FindLifecycleClass_InvalidTokenType() trace_FindLifecycleClass_InvalidTokenType_Impl(0, 0)
#endif
FILE_EVENT0(30010, trace_FindLifecycleClass_InvalidTokenType_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Invalid token type"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_TooFewOperandsISA() trace_FindLifecycleClass_TooFewOperandsISA_Impl(__FILE__, __LINE__)
#else
#define trace_FindLifecycleClass_TooFewOperandsISA() trace_FindLifecycleClass_TooFewOperandsISA_Impl(0, 0)
#endif
FILE_EVENT0(30011, trace_FindLifecycleClass_TooFewOperandsISA_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Too few operands for ISA operator"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindLifecycleClass_UnsupportedLifecycleQuery() trace_FindLifecycleClass_UnsupportedLifecycleQuery_Impl(__FILE__, __LINE__)
#else
#define trace_FindLifecycleClass_UnsupportedLifecycleQuery() trace_FindLifecycleClass_UnsupportedLifecycleQuery_Impl(0, 0)
#endif
FILE_EVENT0(30012, trace_FindLifecycleClass_UnsupportedLifecycleQuery_Impl, LOG_WARNING, PAL_T("_FindLifecycleClass: Unsupported lifecycle query, which has more than 1 ISA operators"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetNameValuePair_Failed() trace_GetNameValuePair_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_GetNameValuePair_Failed() trace_GetNameValuePair_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30013, trace_GetNameValuePair_Failed_Impl, LOG_WARNING, PAL_T("_getNameValuePair failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetRequestLine_failed() trace_GetRequestLine_failed_Impl(__FILE__, __LINE__)
#else
#define trace_GetRequestLine_failed() trace_GetRequestLine_failed_Impl(0, 0)
#endif
FILE_EVENT0(30014, trace_GetRequestLine_failed_Impl, LOG_WARNING, PAL_T("_getRequestLine failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PrepareMessageForAgent_Failed(a0) trace_PrepareMessageForAgent_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_PrepareMessageForAgent_Failed(a0) trace_PrepareMessageForAgent_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30015, trace_PrepareMessageForAgent_Failed_Impl, LOG_WARNING, PAL_T("_PrepareMessageForAgent: failed %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallbackWrite_Failed() trace_RequestCallbackWrite_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_RequestCallbackWrite_Failed() trace_RequestCallbackWrite_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30016, trace_RequestCallbackWrite_Failed_Impl, LOG_WARNING, PAL_T("_RequestCallbackWrite failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItem_ParentPost_AfterClose(a0, a1) trace_RequestItem_ParentPost_AfterClose_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_RequestItem_ParentPost_AfterClose(a0, a1) trace_RequestItem_ParentPost_AfterClose_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30017, trace_RequestItem_ParentPost_AfterClose_Impl, LOG_WARNING, PAL_T("_RequestItem_ParentPost: %p, receiving msg %p when already closed"), void *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Message_InvalidMagic() trace_Message_InvalidMagic_Impl(__FILE__, __LINE__)
#else
#define trace_Message_InvalidMagic() trace_Message_InvalidMagic_Impl(0, 0)
#endif
FILE_EVENT0(30018, trace_Message_InvalidMagic_Impl, LOG_WARNING, PAL_T("_SendIN_IO_thread: invalid magic !"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendIN_IO_thread_HttpSocket_WriteFailed() trace_SendIN_IO_thread_HttpSocket_WriteFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SendIN_IO_thread_HttpSocket_WriteFailed() trace_SendIN_IO_thread_HttpSocket_WriteFailed_Impl(0, 0)
#endif
FILE_EVENT0(30019, trace_SendIN_IO_thread_HttpSocket_WriteFailed_Impl, LOG_WARNING, PAL_T("_SendIN_IO_thread_HttpSocket: _RequestCallbackWrite failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendIN_IO_thread_HttpSocket_InvalidHandler(a0) trace_SendIN_IO_thread_HttpSocket_InvalidHandler_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SendIN_IO_thread_HttpSocket_InvalidHandler(a0) trace_SendIN_IO_thread_HttpSocket_InvalidHandler_Impl(0, 0, a0)
#endif
FILE_EVENT1(30020, trace_SendIN_IO_thread_HttpSocket_InvalidHandler_Impl, LOG_WARNING, PAL_T("_SendIN_IO_thread_HttpSocket: cannot send message: invalid handler (%p)\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendRequestToAgent_Batch_Strdup_Failed() trace_SendRequestToAgent_Batch_Strdup_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SendRequestToAgent_Batch_Strdup_Failed() trace_SendRequestToAgent_Batch_Strdup_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30021, trace_SendRequestToAgent_Batch_Strdup_Failed_Impl, LOG_WARNING, PAL_T("_SendRequestToAgent: Batch_Strdup failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendRequestToAgent_MessageCloneFailed(a0) trace_SendRequestToAgent_MessageCloneFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SendRequestToAgent_MessageCloneFailed(a0) trace_SendRequestToAgent_MessageCloneFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30022, trace_SendRequestToAgent_MessageCloneFailed_Impl, LOG_WARNING, PAL_T("_SendRequestToAgent: message clone failed %d\n"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendRequestToAgent_StrandNewFailed() trace_SendRequestToAgent_StrandNewFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SendRequestToAgent_StrandNewFailed() trace_SendRequestToAgent_StrandNewFailed_Impl(0, 0)
#endif
FILE_EVENT0(30023, trace_SendRequestToAgent_StrandNewFailed_Impl, LOG_WARNING, PAL_T("_SendRequestToAgent: StrandEntry_New failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeElem_CheckSendFinalResult(a0, a1) trace_SubscribeElem_CheckSendFinalResult_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_SubscribeElem_CheckSendFinalResult(a0, a1) trace_SubscribeElem_CheckSendFinalResult_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENT2(30024, trace_SubscribeElem_CheckSendFinalResult_Impl, LOG_WARNING, PAL_T("_SubscribeElem_CheckSendFinalResult: self (%p) status (%T), ignore"), void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeElem_EntryPost_UnexpectedMsg(a0, a1, a2, a3) trace_SubscribeElem_EntryPost_UnexpectedMsg_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_SubscribeElem_EntryPost_UnexpectedMsg(a0, a1, a2, a3) trace_SubscribeElem_EntryPost_UnexpectedMsg_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENT4(30025, trace_SubscribeElem_EntryPost_UnexpectedMsg_Impl, LOG_WARNING, PAL_T("_SubscribeElem_EntryPost: Unexpected msg (%p:%d:%T:%x)"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentLaunch_Failed(a0, a1) trace_AgentLaunch_Failed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_AgentLaunch_Failed(a0, a1) trace_AgentLaunch_Failed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(30026, trace_AgentLaunch_Failed_Impl, LOG_WARNING, PAL_T("agent launching: failed to exec %s, errno %d"), const char *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PostSchemaMsg_Failed() trace_PostSchemaMsg_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_PostSchemaMsg_Failed() trace_PostSchemaMsg_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30027, trace_PostSchemaMsg_Failed_Impl, LOG_WARNING, PAL_T("allocating PostSchemaMsg failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AuthFailed_RandomDataMismatch() trace_AuthFailed_RandomDataMismatch_Impl(__FILE__, __LINE__)
#else
#define trace_AuthFailed_RandomDataMismatch() trace_AuthFailed_RandomDataMismatch_Impl(0, 0)
#endif
FILE_EVENT0(30028, trace_AuthFailed_RandomDataMismatch_Impl, LOG_WARNING, PAL_T("auth failed - random data mismatch"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AuthFailed_ForUser(a0) trace_AuthFailed_ForUser_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_AuthFailed_ForUser(a0) trace_AuthFailed_ForUser_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30029, trace_AuthFailed_ForUser_Impl, LOG_WARNING, PAL_T("auth failed for user [%s]"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Base64_DecodeErrorInBasic(a0) trace_Base64_DecodeErrorInBasic_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_Base64_DecodeErrorInBasic(a0) trace_Base64_DecodeErrorInBasic_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30030, trace_Base64_DecodeErrorInBasic_Impl, LOG_WARNING, PAL_T("base64 decoding error in Basic auth: [%s]\n"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Base64Dec_Failed() trace_Base64Dec_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_Base64Dec_Failed() trace_Base64Dec_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30031, trace_Base64Dec_Failed_Impl, LOG_WARNING, PAL_T("Base64Dec failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_BatchFixPointerFailed() trace_BatchFixPointerFailed_Impl(__FILE__, __LINE__)
#else
#define trace_BatchFixPointerFailed() trace_BatchFixPointerFailed_Impl(0, 0)
#endif
FILE_EVENT0(30032, trace_BatchFixPointerFailed_Impl, LOG_WARNING, PAL_T("batch fix pointer failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EnumContexAllocFailed_OutOfMemory() trace_EnumContexAllocFailed_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace_EnumContexAllocFailed_OutOfMemory() trace_EnumContexAllocFailed_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENT0(30033, trace_EnumContexAllocFailed_OutOfMemory_Impl, LOG_WARNING, PAL_T("Cannot allocate new enumerate context - (out of memory)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EnumContexAllocFailed_TooManyConcurrent() trace_EnumContexAllocFailed_TooManyConcurrent_Impl(__FILE__, __LINE__)
#else
#define trace_EnumContexAllocFailed_TooManyConcurrent() trace_EnumContexAllocFailed_TooManyConcurrent_Impl(0, 0)
#endif
FILE_EVENT0(30034, trace_EnumContexAllocFailed_TooManyConcurrent_Impl, LOG_WARNING, PAL_T("Cannot allocate new enumerate context - all used (too many concurrent enumerations)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotCreateFileForUser(a0) trace_CannotCreateFileForUser_Impl(__FILE__, __LINE__, a0)
#else
#define trace_CannotCreateFileForUser(a0) trace_CannotCreateFileForUser_Impl(0, 0, a0)
#endif
FILE_EVENT1(30035, trace_CannotCreateFileForUser_Impl, LOG_WARNING, PAL_T("cannot create file for user uid [%d]"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotFindEnumerateContext(a0) trace_CannotFindEnumerateContext_Impl(__FILE__, __LINE__, a0)
#else
#define trace_CannotFindEnumerateContext(a0) trace_CannotFindEnumerateContext_Impl(0, 0, a0)
#endif
FILE_EVENT1(30036, trace_CannotFindEnumerateContext_Impl, LOG_WARNING, PAL_T("Cannot find enumerate context: %x"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SharedLibrary_CannotFindSymbol(a0, a1) trace_SharedLibrary_CannotFindSymbol_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_SharedLibrary_CannotFindSymbol(a0, a1) trace_SharedLibrary_CannotFindSymbol_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(30037, trace_SharedLibrary_CannotFindSymbol_Impl, LOG_WARNING, PAL_T("cannot find symbol in shared library: %s: %s"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotFormatLogFilename() trace_CannotFormatLogFilename_Impl(__FILE__, __LINE__)
#else
#define trace_CannotFormatLogFilename() trace_CannotFormatLogFilename_Impl(0, 0)
#endif
FILE_EVENT0(30038, trace_CannotFormatLogFilename_Impl, LOG_WARNING, PAL_T("cannot format log file name\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotGetUserGidForUid(a0) trace_CannotGetUserGidForUid_Impl(__FILE__, __LINE__, a0)
#else
#define trace_CannotGetUserGidForUid(a0) trace_CannotGetUserGidForUid_Impl(0, 0, a0)
#endif
FILE_EVENT1(30039, trace_CannotGetUserGidForUid_Impl, LOG_WARNING, PAL_T("cannot get user's gid for uid %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SharedLib_CannotOpen(a0) trace_SharedLib_CannotOpen_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SharedLib_CannotOpen(a0) trace_SharedLib_CannotOpen_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30040, trace_SharedLib_CannotOpen_Impl, LOG_WARNING, PAL_T("cannot open shared library: {%s}"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SharedLib_CannotOpenSecondTry(a0, a1) trace_SharedLib_CannotOpenSecondTry_Impl(__FILE__, __LINE__, scs(a0), tcs(a1))
#else
#define trace_SharedLib_CannotOpenSecondTry(a0, a1) trace_SharedLib_CannotOpenSecondTry_Impl(0, 0, scs(a0), tcs(a1))
#endif
FILE_EVENT2(30041, trace_SharedLib_CannotOpenSecondTry_Impl, LOG_WARNING, PAL_T("cannot open shared library: {%s}: %T"), const char *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SharedLib_CannotOpenFirstTry(a0, a1) trace_SharedLib_CannotOpenFirstTry_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_SharedLib_CannotOpenFirstTry(a0, a1) trace_SharedLib_CannotOpenFirstTry_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(30042, trace_SharedLib_CannotOpenFirstTry_Impl, LOG_WARNING, PAL_T("cannot open shared library: {%T}: %T"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Message_ExpiredHandler(a0) trace_Message_ExpiredHandler_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Message_ExpiredHandler(a0) trace_Message_ExpiredHandler_Impl(0, 0, a0)
#endif
FILE_EVENT1(30043, trace_Message_ExpiredHandler_Impl, LOG_WARNING, PAL_T("cannot send message: expired handler (msg->clientID) %p\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueueOverflowOrConnectionAbort(a0) trace_QueueOverflowOrConnectionAbort_Impl(__FILE__, __LINE__, a0)
#else
#define trace_QueueOverflowOrConnectionAbort(a0) trace_QueueOverflowOrConnectionAbort_Impl(0, 0, a0)
#endif
FILE_EVENT1(30044, trace_QueueOverflowOrConnectionAbort_Impl, LOG_WARNING, PAL_T("cannot send message: queue overflow on Listener or connection aborted, %p\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueueOverflow(a0) trace_QueueOverflow_Impl(__FILE__, __LINE__, a0)
#else
#define trace_QueueOverflow(a0) trace_QueueOverflow_Impl(0, 0, a0)
#endif
FILE_EVENT1(30045, trace_QueueOverflow_Impl, LOG_WARNING, PAL_T("cannot send message: queue overflow) %p\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotSpawnChildProcess() trace_CannotSpawnChildProcess_Impl(__FILE__, __LINE__)
#else
#define trace_CannotSpawnChildProcess() trace_CannotSpawnChildProcess_Impl(0, 0)
#endif
FILE_EVENT0(30046, trace_CannotSpawnChildProcess_Impl, LOG_WARNING, PAL_T("cannot spawn a child process\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClassIsNotIndication(a0) trace_ClassIsNotIndication_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_ClassIsNotIndication(a0) trace_ClassIsNotIndication_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30047, trace_ClassIsNotIndication_Impl, LOG_WARNING, PAL_T("Class %T is not an indication class"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CloseWithActiveAggregationContext() trace_CloseWithActiveAggregationContext_Impl(__FILE__, __LINE__)
#else
#define trace_CloseWithActiveAggregationContext() trace_CloseWithActiveAggregationContext_Impl(0, 0)
#endif
FILE_EVENT0(30048, trace_CloseWithActiveAggregationContext_Impl, LOG_WARNING, PAL_T("Close with active aggregation context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_Http_Listener_SocketDataAllocFailed() trace_SocketClose_Http_Listener_SocketDataAllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_Http_Listener_SocketDataAllocFailed() trace_SocketClose_Http_Listener_SocketDataAllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(30049, trace_SocketClose_Http_Listener_SocketDataAllocFailed_Impl, LOG_WARNING, PAL_T("closing socket due to Http_Listener_SocketData alloc failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_Http_SR_SocketDataAllocFailed() trace_SocketClose_Http_SR_SocketDataAllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_Http_SR_SocketDataAllocFailed() trace_SocketClose_Http_SR_SocketDataAllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(30050, trace_SocketClose_Http_SR_SocketDataAllocFailed_Impl, LOG_WARNING, PAL_T("closing socket due to Http_SR_SocketData calloc failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_recvBuffer_AllocFailed() trace_SocketClose_recvBuffer_AllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_recvBuffer_AllocFailed() trace_SocketClose_recvBuffer_AllocFailed_Impl(0, 0)
#endif
FILE_EVENT0(30051, trace_SocketClose_recvBuffer_AllocFailed_Impl, LOG_WARNING, PAL_T("closing socket due to recvBuffer calloc failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_Selector_AddHandlerFailed() trace_SocketClose_Selector_AddHandlerFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_Selector_AddHandlerFailed() trace_SocketClose_Selector_AddHandlerFailed_Impl(0, 0)
#endif
FILE_EVENT0(30052, trace_SocketClose_Selector_AddHandlerFailed_Impl, LOG_WARNING, PAL_T("closing socket due to Selector_AddHandler failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_SetBlockingFailed() trace_SocketClose_SetBlockingFailed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_SetBlockingFailed() trace_SocketClose_SetBlockingFailed_Impl(0, 0)
#endif
FILE_EVENT0(30053, trace_SocketClose_SetBlockingFailed_Impl, LOG_WARNING, PAL_T("closing socket due to Sock_SetBlocking failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContentLength_MaxCheck_Failed() trace_ContentLength_MaxCheck_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_ContentLength_MaxCheck_Failed() trace_ContentLength_MaxCheck_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30054, trace_ContentLength_MaxCheck_Failed_Impl, LOG_WARNING, PAL_T("contentLength max check failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EnumHasNoClassname() trace_EnumHasNoClassname_Impl(__FILE__, __LINE__)
#else
#define trace_EnumHasNoClassname() trace_EnumHasNoClassname_Impl(0, 0)
#endif
FILE_EVENT0(30055, trace_EnumHasNoClassname_Impl, LOG_WARNING, PAL_T("Enumeration has no class name"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedCallLibraryUnload(a0, a1) trace_FailedCallLibraryUnload_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_FailedCallLibraryUnload(a0, a1) trace_FailedCallLibraryUnload_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENT2(30056, trace_FailedCallLibraryUnload_Impl, LOG_WARNING, PAL_T("failed to call library unload: %u:%s"), MI_Result, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedCallModuleLoad(a0, a1) trace_FailedCallModuleLoad_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_FailedCallModuleLoad(a0, a1) trace_FailedCallModuleLoad_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENT2(30057, trace_FailedCallModuleLoad_Impl, LOG_WARNING, PAL_T("failed to call module load with result %u; library: %s"), MI_Result, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedProviderLoad(a0, a1) trace_FailedProviderLoad_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_FailedProviderLoad(a0, a1) trace_FailedProviderLoad_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENT2(30058, trace_FailedProviderLoad_Impl, LOG_WARNING, PAL_T("failed to call provider's load with result %d; class: %T"), MI_Result, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ChownAuthFile_Failed(a0) trace_ChownAuthFile_Failed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_ChownAuthFile_Failed(a0) trace_ChownAuthFile_Failed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30059, trace_ChownAuthFile_Failed_Impl, LOG_WARNING, PAL_T("failed to chown auth file %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CreateAuthFile_Failed(a0) trace_CreateAuthFile_Failed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_CreateAuthFile_Failed(a0) trace_CreateAuthFile_Failed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30060, trace_CreateAuthFile_Failed_Impl, LOG_WARNING, PAL_T("failed to create auth file %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CreateLogFile_Failed(a0, a1) trace_CreateLogFile_Failed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_CreateLogFile_Failed(a0, a1) trace_CreateLogFile_Failed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(30061, trace_CreateLogFile_Failed_Impl, LOG_WARNING, PAL_T("failed to create log file %s; errno %d"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedInitSalt() trace_FailedInitSalt_Impl(__FILE__, __LINE__)
#else
#define trace_FailedInitSalt() trace_FailedInitSalt_Impl(0, 0)
#endif
FILE_EVENT0(30062, trace_FailedInitSalt_Impl, LOG_WARNING, PAL_T("failed to init salt"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedLoadDevUrandom() trace_FailedLoadDevUrandom_Impl(__FILE__, __LINE__)
#else
#define trace_FailedLoadDevUrandom() trace_FailedLoadDevUrandom_Impl(0, 0)
#endif
FILE_EVENT0(30063, trace_FailedLoadDevUrandom_Impl, LOG_WARNING, PAL_T("failed to load /dev/urandom"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedLoadProviderAgent() trace_FailedLoadProviderAgent_Impl(__FILE__, __LINE__)
#else
#define trace_FailedLoadProviderAgent() trace_FailedLoadProviderAgent_Impl(0, 0)
#endif
FILE_EVENT0(30064, trace_FailedLoadProviderAgent_Impl, LOG_WARNING, PAL_T("failed to load provider agent"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OpenProviderLib_Failed(a0) trace_OpenProviderLib_Failed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_OpenProviderLib_Failed(a0) trace_OpenProviderLib_Failed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30065, trace_OpenProviderLib_Failed_Impl, LOG_WARNING, PAL_T("failed to open provider library: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OpenProvider_FailedForClass(a0, a1) trace_OpenProvider_FailedForClass_Impl(__FILE__, __LINE__, scs(a0), tcs(a1))
#else
#define trace_OpenProvider_FailedForClass(a0, a1) trace_OpenProvider_FailedForClass_Impl(0, 0, scs(a0), tcs(a1))
#endif
FILE_EVENT2(30066, trace_OpenProvider_FailedForClass_Impl, LOG_WARNING, PAL_T("failed to open the provider %s for class %T"), const char *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedToProduceRandomData() trace_FailedToProduceRandomData_Impl(__FILE__, __LINE__)
#else
#define trace_FailedToProduceRandomData() trace_FailedToProduceRandomData_Impl(0, 0)
#endif
FILE_EVENT0(30067, trace_FailedToProduceRandomData_Impl, LOG_WARNING, PAL_T("failed to produce random data"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FailedRemovePIDFile(a0) trace_FailedRemovePIDFile_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_FailedRemovePIDFile(a0) trace_FailedRemovePIDFile_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30068, trace_FailedRemovePIDFile_Impl, LOG_WARNING, PAL_T("failed to remove PID file: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMessage_Failed(a0, a1) trace_RestoreMessage_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_RestoreMessage_Failed(a0, a1) trace_RestoreMessage_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENT2(30069, trace_RestoreMessage_Failed_Impl, LOG_WARNING, PAL_T("failed to restore message %d [%T]\n"), MI_Result, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_fcntl_failed(a0) trace_fcntl_failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_fcntl_failed(a0) trace_fcntl_failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30070, trace_fcntl_failed_Impl, LOG_WARNING, PAL_T("fcntl(F_SETFD) failed %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetUserUidGid_Failed(a0) trace_GetUserUidGid_Failed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_GetUserUidGid_Failed(a0) trace_GetUserUidGid_Failed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30071, trace_GetUserUidGid_Failed_Impl, LOG_WARNING, PAL_T("get user [%s] uid/gid"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_getpwnamr_Failed(a0) trace_getpwnamr_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_getpwnamr_Failed(a0) trace_getpwnamr_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30072, trace_getpwnamr_Failed_Impl, LOG_WARNING, PAL_T("getpwnam_r filed, errno %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_getHomeDir_Failed() trace_getHomeDir_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_getHomeDir_Failed() trace_getHomeDir_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30073, trace_getHomeDir_Failed_Impl, LOG_WARNING, PAL_T("getpwuid_r failed: errno (%d)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_getpwuidr_Failed(a0) trace_getpwuidr_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_getpwuidr_Failed(a0) trace_getpwuidr_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30074, trace_getpwuidr_Failed_Impl, LOG_WARNING, PAL_T("GetHomeDir Failed"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpChunkHeaderIsTooBig() trace_HttpChunkHeaderIsTooBig_Impl(__FILE__, __LINE__)
#else
#define trace_HttpChunkHeaderIsTooBig() trace_HttpChunkHeaderIsTooBig_Impl(0, 0)
#endif
FILE_EVENT0(30075, trace_HttpChunkHeaderIsTooBig_Impl, LOG_WARNING, PAL_T("http chunk header is too big; dropping connection\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpHeaderIsTooBig() trace_HttpHeaderIsTooBig_Impl(__FILE__, __LINE__)
#else
#define trace_HttpHeaderIsTooBig() trace_HttpHeaderIsTooBig_Impl(0, 0)
#endif
FILE_EVENT0(30076, trace_HttpHeaderIsTooBig_Impl, LOG_WARNING, PAL_T("http header is too big; dropping connection\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpPayloadIsBiggerThanContentLength() trace_HttpPayloadIsBiggerThanContentLength_Impl(__FILE__, __LINE__)
#else
#define trace_HttpPayloadIsBiggerThanContentLength() trace_HttpPayloadIsBiggerThanContentLength_Impl(0, 0)
#endif
FILE_EVENT0(30077, trace_HttpPayloadIsBiggerThanContentLength_Impl, LOG_WARNING, PAL_T("http payload is bigger than content-length\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribeReq_StrandNewFailed(a0) trace_IndiMgr_HandleSubscribeReq_StrandNewFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_HandleSubscribeReq_StrandNewFailed(a0) trace_IndiMgr_HandleSubscribeReq_StrandNewFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30078, trace_IndiMgr_HandleSubscribeReq_StrandNewFailed_Impl, LOG_WARNING, PAL_T("IndiMgr_HandleSubscribeReq: StrandEntry_New failed, req (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_initgroups_Failed(a0) trace_initgroups_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_initgroups_Failed(a0) trace_initgroups_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30079, trace_initgroups_Failed_Impl, LOG_WARNING, PAL_T("initgroups failed: errno (%d)"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InstanceConversionFailed(a0, a1) trace_InstanceConversionFailed_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_InstanceConversionFailed(a0, a1) trace_InstanceConversionFailed_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENT2(30080, trace_InstanceConversionFailed_Impl, LOG_WARNING, PAL_T("instance conversion failed: %T, err %d"), const TChar *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InvalidQueryExpression(a0) trace_InvalidQueryExpression_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_InvalidQueryExpression(a0) trace_InvalidQueryExpression_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30081, trace_InvalidQueryExpression_Impl, LOG_WARNING, PAL_T("invalid query expression: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LibraryUnload_DidnotPostResult() trace_LibraryUnload_DidnotPostResult_Impl(__FILE__, __LINE__)
#else
#define trace_LibraryUnload_DidnotPostResult() trace_LibraryUnload_DidnotPostResult_Impl(0, 0)
#endif
FILE_EVENT0(30082, trace_LibraryUnload_DidnotPostResult_Impl, LOG_WARNING, PAL_T("library unload did not call post result"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ModuleLoad_FailedPostResult() trace_ModuleLoad_FailedPostResult_Impl(__FILE__, __LINE__)
#else
#define trace_ModuleLoad_FailedPostResult() trace_ModuleLoad_FailedPostResult_Impl(0, 0)
#endif
FILE_EVENT0(30083, trace_ModuleLoad_FailedPostResult_Impl, LOG_WARNING, PAL_T("module load failed to call post result"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NoDigestAvailable() trace_NoDigestAvailable_Impl(__FILE__, __LINE__)
#else
#define trace_NoDigestAvailable() trace_NoDigestAvailable_Impl(0, 0)
#endif
FILE_EVENT0(30084, trace_NoDigestAvailable_Impl, LOG_WARNING, PAL_T("no digest available"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProviderLoad_DidnotPostResult() trace_ProviderLoad_DidnotPostResult_Impl(__FILE__, __LINE__)
#else
#define trace_ProviderLoad_DidnotPostResult() trace_ProviderLoad_DidnotPostResult_Impl(0, 0)
#endif
FILE_EVENT0(30085, trace_ProviderLoad_DidnotPostResult_Impl, LOG_WARNING, PAL_T("provider load did not call post result"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueryValidationFailed(a0) trace_QueryValidationFailed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_QueryValidationFailed(a0) trace_QueryValidationFailed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30086, trace_QueryValidationFailed_Impl, LOG_WARNING, PAL_T("query validation failed: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueryEnumClassnameMismatch(a0, a1) trace_QueryEnumClassnameMismatch_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_QueryEnumClassnameMismatch(a0, a1) trace_QueryEnumClassnameMismatch_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(30087, trace_QueryEnumClassnameMismatch_Impl, LOG_WARNING, PAL_T("query/enumeration class name mismatch: %T/%T"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueryLanguageOrExpressionMissing() trace_QueryLanguageOrExpressionMissing_Impl(__FILE__, __LINE__)
#else
#define trace_QueryLanguageOrExpressionMissing() trace_QueryLanguageOrExpressionMissing_Impl(0, 0)
#endif
FILE_EVENT0(30088, trace_QueryLanguageOrExpressionMissing_Impl, LOG_WARNING, PAL_T("queryLanguage or queryExpression is missing"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_FirstTime() trace_RestoreMsgFailed_FirstTime_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_FirstTime() trace_RestoreMsgFailed_FirstTime_Impl(0, 0)
#endif
FILE_EVENT0(30089, trace_RestoreMsgFailed_FirstTime_Impl, LOG_WARNING, PAL_T("restore msg failed first time\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_InvalidTag(a0) trace_RestoreMsgFailed_InvalidTag_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RestoreMsgFailed_InvalidTag(a0) trace_RestoreMsgFailed_InvalidTag_Impl(0, 0, a0)
#endif
FILE_EVENT1(30090, trace_RestoreMsgFailed_InvalidTag_Impl, LOG_WARNING, PAL_T("restore msg failed for invalid tag: %d\n"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_SecondTime(a0) trace_RestoreMsgFailed_SecondTime_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RestoreMsgFailed_SecondTime(a0) trace_RestoreMsgFailed_SecondTime_Impl(0, 0, a0)
#endif
FILE_EVENT1(30091, trace_RestoreMsgFailed_SecondTime_Impl, LOG_WARNING, PAL_T("restore msg failed second time for tag: %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_PointerIsNull() trace_RestoreMsgFailed_PointerIsNull_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_PointerIsNull() trace_RestoreMsgFailed_PointerIsNull_Impl(0, 0)
#endif
FILE_EVENT0(30092, trace_RestoreMsgFailed_PointerIsNull_Impl, LOG_WARNING, PAL_T("restore msg failed since pointer is null for mft_pointer"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_PtrPackedMissing() trace_RestoreMsgFailed_PtrPackedMissing_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_PtrPackedMissing() trace_RestoreMsgFailed_PtrPackedMissing_Impl(0, 0)
#endif
FILE_EVENT0(30093, trace_RestoreMsgFailed_PtrPackedMissing_Impl, LOG_WARNING, PAL_T("restore msg failed since there is no ptrPacked for mft_instance"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_ThirdTime(a0) trace_RestoreMsgFailed_ThirdTime_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RestoreMsgFailed_ThirdTime(a0) trace_RestoreMsgFailed_ThirdTime_Impl(0, 0, a0)
#endif
FILE_EVENT1(30094, trace_RestoreMsgFailed_ThirdTime_Impl, LOG_WARNING, PAL_T("restore msg failed third time for tag\n"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_PointersForMstInstance() trace_RestoreMsgFailed_PointersForMstInstance_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_PointersForMstInstance() trace_RestoreMsgFailed_PointersForMstInstance_Impl(0, 0)
#endif
FILE_EVENT0(30095, trace_RestoreMsgFailed_PointersForMstInstance_Impl, LOG_WARNING, PAL_T("restore msg failed while fixing batch pointers for mft_instance\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_PointersForMstPointer() trace_RestoreMsgFailed_PointersForMstPointer_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_PointersForMstPointer() trace_RestoreMsgFailed_PointersForMstPointer_Impl(0, 0)
#endif
FILE_EVENT0(30096, trace_RestoreMsgFailed_PointersForMstPointer_Impl, LOG_WARNING, PAL_T("restore msg failed while fixing batch pointers for mft_pointer"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RestoreMsgFailed_UnpackingInstance() trace_RestoreMsgFailed_UnpackingInstance_Impl(__FILE__, __LINE__)
#else
#define trace_RestoreMsgFailed_UnpackingInstance() trace_RestoreMsgFailed_UnpackingInstance_Impl(0, 0)
#endif
FILE_EVENT0(30097, trace_RestoreMsgFailed_UnpackingInstance_Impl, LOG_WARNING, PAL_T("restore msg failed while unpacking instance for mft_instance"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SchemaConversion_ToCimXmlFailed(a0) trace_SchemaConversion_ToCimXmlFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SchemaConversion_ToCimXmlFailed(a0) trace_SchemaConversion_ToCimXmlFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30098, trace_SchemaConversion_ToCimXmlFailed_Impl, LOG_WARNING, PAL_T("Schema conversion into cim-xml failed with error %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SchemaConversion_ToInstanceFailed(a0) trace_SchemaConversion_ToInstanceFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SchemaConversion_ToInstanceFailed(a0) trace_SchemaConversion_ToInstanceFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30099, trace_SchemaConversion_ToInstanceFailed_Impl, LOG_WARNING, PAL_T("Schema conversion into instance failed %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SchemaInstancePackaging_Failed(a0) trace_SchemaInstancePackaging_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SchemaInstancePackaging_Failed(a0) trace_SchemaInstancePackaging_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30100, trace_SchemaInstancePackaging_Failed_Impl, LOG_WARNING, PAL_T("Schema instance packaging failed %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorAddHandler_Failed() trace_SelectorAddHandler_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SelectorAddHandler_Failed() trace_SelectorAddHandler_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30101, trace_SelectorAddHandler_Failed_Impl, LOG_WARNING, PAL_T("Selector_AddHandler() failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionClosed_Timeout() trace_ConnectionClosed_Timeout_Impl(__FILE__, __LINE__)
#else
#define trace_ConnectionClosed_Timeout() trace_ConnectionClosed_Timeout_Impl(0, 0)
#endif
FILE_EVENT0(30102, trace_ConnectionClosed_Timeout_Impl, LOG_WARNING, PAL_T("SELECTOR_TIMEOUT reached; so failed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SetNonBlocking_Failed() trace_SetNonBlocking_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SetNonBlocking_Failed() trace_SetNonBlocking_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30103, trace_SetNonBlocking_Failed_Impl, LOG_WARNING, PAL_T("set non-blocking failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_setgid_Failed(a0) trace_setgid_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_setgid_Failed(a0) trace_setgid_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30104, trace_setgid_Failed_Impl, LOG_WARNING, PAL_T("setgid failed: errno (%d)"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timeout_InvalidMagic() trace_Timeout_InvalidMagic_Impl(__FILE__, __LINE__)
#else
#define trace_Timeout_InvalidMagic() trace_Timeout_InvalidMagic_Impl(0, 0)
#endif
FILE_EVENT0(30105, trace_Timeout_InvalidMagic_Impl, LOG_WARNING, PAL_T("setTimeout: invalid magic !"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_setuid_Failed(a0) trace_setuid_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_setuid_Failed(a0) trace_setuid_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30106, trace_setuid_Failed_Impl, LOG_WARNING, PAL_T("setuid failed: errno (%d)"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockRead_Failed(a0) trace_SockRead_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SockRead_Failed(a0) trace_SockRead_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30107, trace_SockRead_Failed_Impl, LOG_WARNING, PAL_T("Sock_Read: Error %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockReadV_Failed(a0) trace_SockReadV_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SockReadV_Failed(a0) trace_SockReadV_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30108, trace_SockReadV_Failed_Impl, LOG_WARNING, PAL_T("Sock_ReadV: Error %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockSetBlocking_Failed() trace_SockSetBlocking_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SockSetBlocking_Failed() trace_SockSetBlocking_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30109, trace_SockSetBlocking_Failed_Impl, LOG_WARNING, PAL_T("Sock_SetBlocking() failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockWriteV_Failed(a0) trace_SockWriteV_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SockWriteV_Failed(a0) trace_SockWriteV_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30110, trace_SockWriteV_Failed_Impl, LOG_WARNING, PAL_T("Sock_WriteV: Error %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ConnectionClosed(a0) trace_Socket_ConnectionClosed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ConnectionClosed(a0) trace_Socket_ConnectionClosed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30111, trace_Socket_ConnectionClosed_Impl, LOG_WARNING, PAL_T("Socket: %p, Connection closed\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadingHeader_Error(a0, a1) trace_Socket_ReadingHeader_Error_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Socket_ReadingHeader_Error(a0, a1) trace_Socket_ReadingHeader_Error_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30112, trace_Socket_ReadingHeader_Error_Impl, LOG_WARNING, PAL_T("Socket: %p, Error: %d while reading header\n"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_Read_Error(a0, a1) trace_Socket_Read_Error_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Socket_Read_Error(a0, a1) trace_Socket_Read_Error_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30113, trace_Socket_Read_Error_Impl, LOG_WARNING, PAL_T("Socket: %p, Error: %d while reading\n"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_Sending_Error(a0, a1) trace_Socket_Sending_Error_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Socket_Sending_Error(a0, a1) trace_Socket_Sending_Error_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30114, trace_Socket_Sending_Error_Impl, LOG_WARNING, PAL_T("Socket: %p, Error: %d while sending\n"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketPair_Failed() trace_SocketPair_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SocketPair_Failed() trace_SocketPair_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30115, trace_SocketPair_Failed_Impl, LOG_WARNING, PAL_T("socketpair() failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSLNew_Failed() trace_SSLNew_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SSLNew_Failed() trace_SSLNew_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30116, trace_SSLNew_Failed_Impl, LOG_WARNING, PAL_T("ssl_new() failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_setfd_Failed() trace_SSL_setfd_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_SSL_setfd_Failed() trace_SSL_setfd_Failed_Impl(0, 0)
#endif
FILE_EVENT0(30117, trace_SSL_setfd_Failed_Impl, LOG_WARNING, PAL_T("ssl_set_fd() failed\n"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSLRead_Error(a0, a1) trace_SSLRead_Error_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_SSLRead_Error(a0, a1) trace_SSLRead_Error_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENT2(30118, trace_SSLRead_Error_Impl, LOG_WARNING, PAL_T("ssl-read error: %d [%s]\n"), int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSLRead_UnexpectedSysError(a0) trace_SSLRead_UnexpectedSysError_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SSLRead_UnexpectedSysError(a0) trace_SSLRead_UnexpectedSysError_Impl(0, 0, a0)
#endif
FILE_EVENT1(30119, trace_SSLRead_UnexpectedSysError_Impl, LOG_WARNING, PAL_T("ssl-read: unexpected sys error %d\n"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSLWrite_UnexpectedSysError(a0) trace_SSLWrite_UnexpectedSysError_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SSLWrite_UnexpectedSysError(a0) trace_SSLWrite_UnexpectedSysError_Impl(0, 0, a0)
#endif
FILE_EVENT1(30120, trace_SSLWrite_UnexpectedSysError_Impl, LOG_WARNING, PAL_T("ssl-write: unexpected sys error %d\n"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StartRequest_ConnectionClosed() trace_StartRequest_ConnectionClosed_Impl(__FILE__, __LINE__)
#else
#define trace_StartRequest_ConnectionClosed() trace_StartRequest_ConnectionClosed_Impl(0, 0)
#endif
FILE_EVENT0(30121, trace_StartRequest_ConnectionClosed_Impl, LOG_WARNING, PAL_T("start-request: connection was closed"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StartRequest_InvalidMagic() trace_StartRequest_InvalidMagic_Impl(__FILE__, __LINE__)
#else
#define trace_StartRequest_InvalidMagic() trace_StartRequest_InvalidMagic_Impl(0, 0)
#endif
FILE_EVENT0(30122, trace_StartRequest_InvalidMagic_Impl, LOG_WARNING, PAL_T("start-request: invalid magic !"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnumerationcontext_HeartbeatTimeout(a0, a1) trace_WsmanEnumerationcontext_HeartbeatTimeout_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanEnumerationcontext_HeartbeatTimeout(a0, a1) trace_WsmanEnumerationcontext_HeartbeatTimeout_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30123, trace_WsmanEnumerationcontext_HeartbeatTimeout_Impl, LOG_WARNING, PAL_T("Heartbeat timeout: Sending partial results or heartbeat for enumeration context %p (%u)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TooManyHttpHeaders(a0, a1) trace_TooManyHttpHeaders_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_TooManyHttpHeaders(a0, a1) trace_TooManyHttpHeaders_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENT2(30124, trace_TooManyHttpHeaders_Impl, LOG_WARNING, PAL_T("too many http headers; skipping %s: %s\n"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AggregationContext_UnhandledState(a0) trace_AggregationContext_UnhandledState_Impl(__FILE__, __LINE__, a0)
#else
#define trace_AggregationContext_UnhandledState(a0) trace_AggregationContext_UnhandledState_Impl(0, 0, a0)
#endif
FILE_EVENT1(30125, trace_AggregationContext_UnhandledState_Impl, LOG_WARNING, PAL_T("Unhandled AggregationContext state %u"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadingHeader_ErrorPageCount(a0) trace_Socket_ReadingHeader_ErrorPageCount_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ReadingHeader_ErrorPageCount(a0) trace_Socket_ReadingHeader_ErrorPageCount_Impl(0, 0, a0)
#endif
FILE_EVENT1(30126, trace_Socket_ReadingHeader_ErrorPageCount_Impl, LOG_WARNING, PAL_T("Socket: %p, Error PageCount while reading header\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadingHeader_ErrorMagic(a0) trace_Socket_ReadingHeader_ErrorMagic_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ReadingHeader_ErrorMagic(a0) trace_Socket_ReadingHeader_ErrorMagic_Impl(0, 0, a0)
#endif
FILE_EVENT1(30127, trace_Socket_ReadingHeader_ErrorMagic_Impl, LOG_WARNING, PAL_T("Socket: %p, Error Magic while reading header\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadingHeader_ErrorBatchSize(a0) trace_Socket_ReadingHeader_ErrorBatchSize_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ReadingHeader_ErrorBatchSize(a0) trace_Socket_ReadingHeader_ErrorBatchSize_Impl(0, 0, a0)
#endif
FILE_EVENT1(30128, trace_Socket_ReadingHeader_ErrorBatchSize_Impl, LOG_WARNING, PAL_T("Socket: %p, Error BatchSize while reading header\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadingHeader_ErrorCreatingBatch(a0) trace_Socket_ReadingHeader_ErrorCreatingBatch_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ReadingHeader_ErrorCreatingBatch(a0) trace_Socket_ReadingHeader_ErrorCreatingBatch_Impl(0, 0, a0)
#endif
FILE_EVENT1(30129, trace_Socket_ReadingHeader_ErrorCreatingBatch_Impl, LOG_WARNING, PAL_T("Socket: %p, Error CreatingBatch while reading header\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage(a0) trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage(a0) trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage_Impl(0, 0, a0)
#endif
FILE_EVENT1(30130, trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage_Impl, LOG_WARNING, PAL_T("wsman: _InteractionWsman_Right_Post: unexpected message tag %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage(a0) trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage(a0) trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage_Impl(0, 0, a0)
#endif
FILE_EVENT1(30131, trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage_Impl, LOG_WARNING, PAL_T("wsman: _InteractionWsmanEnum_Right_Post: unexpected message tag %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_AuthenticationFailed(a0) trace_Wsman_AuthenticationFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_Wsman_AuthenticationFailed(a0) trace_Wsman_AuthenticationFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30132, trace_Wsman_AuthenticationFailed_Impl, LOG_WARNING, PAL_T("wsman: authentication failed for user [%s]"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnsupportedAuthentication(a0) trace_Wsman_UnsupportedAuthentication_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_Wsman_UnsupportedAuthentication(a0) trace_Wsman_UnsupportedAuthentication_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30133, trace_Wsman_UnsupportedAuthentication_Impl, LOG_WARNING, PAL_T("wsman: Unsupported authentication [%s]"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_CharsetIsNotSupported(a0) trace_Wsman_CharsetIsNotSupported_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_Wsman_CharsetIsNotSupported(a0) trace_Wsman_CharsetIsNotSupported_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30134, trace_Wsman_CharsetIsNotSupported_Impl, LOG_WARNING, PAL_T("wsman: charset is not supported [%s]"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InstanceNameParameterMissing() trace_Wsman_InstanceNameParameterMissing_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_InstanceNameParameterMissing() trace_Wsman_InstanceNameParameterMissing_Impl(0, 0)
#endif
FILE_EVENT0(30135, trace_Wsman_InstanceNameParameterMissing_Impl, LOG_WARNING, PAL_T("wsman: delete-instance: instance name parameter is missing"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_FailedParseSOAPEnvelope() trace_Wsman_FailedParseSOAPEnvelope_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_FailedParseSOAPEnvelope() trace_Wsman_FailedParseSOAPEnvelope_Impl(0, 0)
#endif
FILE_EVENT0(30136, trace_Wsman_FailedParseSOAPEnvelope_Impl, LOG_WARNING, PAL_T("wsman: failed to parse SOAP envelope"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_FailedParseWSHeader() trace_Wsman_FailedParseWSHeader_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_FailedParseWSHeader() trace_Wsman_FailedParseWSHeader_Impl(0, 0)
#endif
FILE_EVENT0(30137, trace_Wsman_FailedParseWSHeader_Impl, LOG_WARNING, PAL_T("wsman: failed to parse WS header"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_NoActionOrIdentify() trace_Wsman_NoActionOrIdentify_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_NoActionOrIdentify() trace_Wsman_NoActionOrIdentify_Impl(0, 0)
#endif
FILE_EVENT0(30138, trace_Wsman_NoActionOrIdentify_Impl, LOG_WARNING, PAL_T("wsman: found neither Action or Identify"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanGet_UnsupportedResourceURI() trace_WsmanGet_UnsupportedResourceURI_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanGet_UnsupportedResourceURI() trace_WsmanGet_UnsupportedResourceURI_Impl(0, 0)
#endif
FILE_EVENT0(30139, trace_WsmanGet_UnsupportedResourceURI_Impl, LOG_WARNING, PAL_T("wsman: Get : Unsupported ws-cim resourceUri"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanGetInstance_InstanceNameParameterMissing() trace_WsmanGetInstance_InstanceNameParameterMissing_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanGetInstance_InstanceNameParameterMissing() trace_WsmanGetInstance_InstanceNameParameterMissing_Impl(0, 0)
#endif
FILE_EVENT0(30140, trace_WsmanGetInstance_InstanceNameParameterMissing_Impl, LOG_WARNING, PAL_T("wsman: get-instance: instance name parameter is missing"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InvalidMissingContentType(a0) trace_Wsman_InvalidMissingContentType_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_InvalidMissingContentType(a0) trace_Wsman_InvalidMissingContentType_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30141, trace_Wsman_InvalidMissingContentType_Impl, LOG_WARNING, PAL_T("wsman: invalid/missing content type in request [%T]"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_ParametersMissing() trace_WsmanEnum_ParametersMissing_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanEnum_ParametersMissing() trace_WsmanEnum_ParametersMissing_Impl(0, 0)
#endif
FILE_EVENT0(30142, trace_WsmanEnum_ParametersMissing_Impl, LOG_WARNING, PAL_T("wsman: mandatory parameters (className, namespace) are missing for enumerate request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_MaxEnvelopeIsTooSmall(a0) trace_Wsman_MaxEnvelopeIsTooSmall_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_MaxEnvelopeIsTooSmall(a0) trace_Wsman_MaxEnvelopeIsTooSmall_Impl(0, 0, a0)
#endif
FILE_EVENT1(30143, trace_Wsman_MaxEnvelopeIsTooSmall_Impl, LOG_WARNING, PAL_T("wsman: max-envelope is too small even for one message; message size %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanPut_InstanceNameParameterMissing() trace_WsmanPut_InstanceNameParameterMissing_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanPut_InstanceNameParameterMissing() trace_WsmanPut_InstanceNameParameterMissing_Impl(0, 0)
#endif
FILE_EVENT0(30144, trace_WsmanPut_InstanceNameParameterMissing_Impl, LOG_WARNING, PAL_T("wsman: Put-instance: instance name parameter is missing"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_RequestedEnvelopeSizeIsTooSmall(a0) trace_Wsman_RequestedEnvelopeSizeIsTooSmall_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_RequestedEnvelopeSizeIsTooSmall(a0) trace_Wsman_RequestedEnvelopeSizeIsTooSmall_Impl(0, 0, a0)
#endif
FILE_EVENT1(30145, trace_Wsman_RequestedEnvelopeSizeIsTooSmall_Impl, LOG_WARNING, PAL_T("wsman: requested envelope size (%d) is too small; expected at least 8K"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_BufferSizeIsZero() trace_Wsman_BufferSizeIsZero_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_BufferSizeIsZero() trace_Wsman_BufferSizeIsZero_Impl(0, 0)
#endif
FILE_EVENT0(30146, trace_Wsman_BufferSizeIsZero_Impl, LOG_WARNING, PAL_T("wsman: size of buffer is 0"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_UnableToParseXml() trace_WsmanEnum_UnableToParseXml_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanEnum_UnableToParseXml() trace_WsmanEnum_UnableToParseXml_Impl(0, 0)
#endif
FILE_EVENT0(30147, trace_WsmanEnum_UnableToParseXml_Impl, LOG_WARNING, PAL_T("wsman: unable to parse incoming xml/ enumerate request body"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanPull_UnableToParseXml() trace_WsmanPull_UnableToParseXml_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanPull_UnableToParseXml() trace_WsmanPull_UnableToParseXml_Impl(0, 0)
#endif
FILE_EVENT0(30148, trace_WsmanPull_UnableToParseXml_Impl, LOG_WARNING, PAL_T("wsman: unable to parse incoming xml/ Pull request body"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanRelease_UnableToParseXml() trace_WsmanRelease_UnableToParseXml_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanRelease_UnableToParseXml() trace_WsmanRelease_UnableToParseXml_Impl(0, 0)
#endif
FILE_EVENT0(30149, trace_WsmanRelease_UnableToParseXml_Impl, LOG_WARNING, PAL_T("wsman: unable to parse incoming xml/ Release request body"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanCreate_UnableToProcessRequest() trace_WsmanCreate_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanCreate_UnableToProcessRequest() trace_WsmanCreate_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30150, trace_WsmanCreate_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process Create request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanDelete_UnableToProcessRequest() trace_WsmanDelete_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanDelete_UnableToProcessRequest() trace_WsmanDelete_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30151, trace_WsmanDelete_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process delete-instance request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanGetClass_UnableToProcessRequest() trace_WsmanGetClass_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanGetClass_UnableToProcessRequest() trace_WsmanGetClass_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30152, trace_WsmanGetClass_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process get-class request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanGetInstance_UnableToProcessRequest() trace_WsmanGetInstance_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanGetInstance_UnableToProcessRequest() trace_WsmanGetInstance_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30153, trace_WsmanGetInstance_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process get-instance request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanInvoke_UnableToProcessRequest() trace_WsmanInvoke_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanInvoke_UnableToProcessRequest() trace_WsmanInvoke_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30154, trace_WsmanInvoke_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process invoke request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanPutInstance_UnableToProcessRequest() trace_WsmanPutInstance_UnableToProcessRequest_Impl(__FILE__, __LINE__)
#else
#define trace_WsmanPutInstance_UnableToProcessRequest() trace_WsmanPutInstance_UnableToProcessRequest_Impl(0, 0)
#endif
FILE_EVENT0(30155, trace_WsmanPutInstance_UnableToProcessRequest_Impl, LOG_WARNING, PAL_T("wsman: unable to process Put-instance request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnexpectedCloseTag(a0) trace_Wsman_UnexpectedCloseTag_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_UnexpectedCloseTag(a0) trace_Wsman_UnexpectedCloseTag_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30156, trace_Wsman_UnexpectedCloseTag_Impl, LOG_WARNING, PAL_T("wsman: unexpected close tag [%T] in incoming xml"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnknownCustomAction() trace_Wsman_UnknownCustomAction_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_UnknownCustomAction() trace_Wsman_UnknownCustomAction_Impl(0, 0)
#endif
FILE_EVENT0(30157, trace_Wsman_UnknownCustomAction_Impl, LOG_WARNING, PAL_T("wsman: unknown custom action"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_UnknownDialect(a0) trace_WsmanEnum_UnknownDialect_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_WsmanEnum_UnknownDialect(a0) trace_WsmanEnum_UnknownDialect_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30158, trace_WsmanEnum_UnknownDialect_Impl, LOG_WARNING, PAL_T("wsman: unknown dialect in enumeration: [%T]"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnknownMandatoryTag(a0) trace_Wsman_UnknownMandatoryTag_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_UnknownMandatoryTag(a0) trace_Wsman_UnknownMandatoryTag_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30159, trace_Wsman_UnknownMandatoryTag_Impl, LOG_WARNING, PAL_T("wsman: unknown mandatory tag [%T]; aborted"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnsupportedAction(a0) trace_Wsman_UnsupportedAction_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_UnsupportedAction(a0) trace_Wsman_UnsupportedAction_Impl(0, 0, a0)
#endif
FILE_EVENT1(30160, trace_Wsman_UnsupportedAction_Impl, LOG_WARNING, PAL_T("wsman: unsupported action [%d]"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_ProcessInstance_Expired(a0) trace_WsmanConnection_ProcessInstance_Expired_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanConnection_ProcessInstance_Expired(a0) trace_WsmanConnection_ProcessInstance_Expired_Impl(0, 0, a0)
#endif
FILE_EVENT1(30161, trace_WsmanConnection_ProcessInstance_Expired_Impl, LOG_WARNING, PAL_T("WsmanConnection: %p _ProcessInstanceConnectionData: expired"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_ProcessResult_NoRequest(a0) trace_WsmanConnection_ProcessResult_NoRequest_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanConnection_ProcessResult_NoRequest(a0) trace_WsmanConnection_ProcessResult_NoRequest_Impl(0, 0, a0)
#endif
FILE_EVENT1(30162, trace_WsmanConnection_ProcessResult_NoRequest_Impl, LOG_WARNING, PAL_T("WsmanConnection: %p _ProcessResultConnectionData: no request"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_ProcessSchema_Expired(a0) trace_WsmanConnection_ProcessSchema_Expired_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanConnection_ProcessSchema_Expired(a0) trace_WsmanConnection_ProcessSchema_Expired_Impl(0, 0, a0)
#endif
FILE_EVENT1(30163, trace_WsmanConnection_ProcessSchema_Expired_Impl, LOG_WARNING, PAL_T("WsmanConnection: %p _ProcessSchemaConnectionData: expired"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_XmlSerializer_SerializeClass(a0) trace_XmlSerializer_SerializeClass_Impl(__FILE__, __LINE__, a0)
#else
#define trace_XmlSerializer_SerializeClass(a0) trace_XmlSerializer_SerializeClass_Impl(0, 0, a0)
#endif
FILE_EVENT1(30164, trace_XmlSerializer_SerializeClass_Impl, LOG_WARNING, PAL_T("XmlSerializer_SerializeClass with flags %x"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_CannotFindEnumerateContext(a0) trace_Wsman_CannotFindEnumerateContext_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_CannotFindEnumerateContext(a0) trace_Wsman_CannotFindEnumerateContext_Impl(0, 0, a0)
#endif
FILE_EVENT1(30165, trace_Wsman_CannotFindEnumerateContext_Impl, LOG_WARNING, PAL_T("Cannot find enumerate context: %x"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_Destroy_Join_nonioThread(a0) trace_ProvMgr_Destroy_Join_nonioThread_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProvMgr_Destroy_Join_nonioThread(a0) trace_ProvMgr_Destroy_Join_nonioThread_Impl(0, 0, a0)
#endif
FILE_EVENT1(30166, trace_ProvMgr_Destroy_Join_nonioThread_Impl, LOG_WARNING, PAL_T("ProvMgr_Destroy: Join nonio thread result %d"), PAL_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_ProcessResult_InvalidState(a0, a1, a2, a3) trace_SubscrContext_ProcessResult_InvalidState_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_SubscrContext_ProcessResult_InvalidState(a0, a1, a2, a3) trace_SubscrContext_ProcessResult_InvalidState_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENT4(30167, trace_SubscrContext_ProcessResult_InvalidState_Impl, LOG_WARNING, PAL_T("_SubscrContext_ProcessResult: Thread %x: ctx (%p) subscription (%p); post final result to invalid subscription, state (%d) "), unsigned int, void*, void*, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Cannot_Start_Timer(a0, a1) trace_Strand_Cannot_Start_Timer_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Strand_Cannot_Start_Timer(a0, a1) trace_Strand_Cannot_Start_Timer_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30168, trace_Strand_Cannot_Start_Timer_Impl, LOG_WARNING, PAL_T("Strand_StartTimer: unable to start timer(%p). Timer already executing on strand (%p)"), void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Cannot_Fire_Timer(a0) trace_Strand_Cannot_Fire_Timer_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Strand_Cannot_Fire_Timer(a0) trace_Strand_Cannot_Fire_Timer_Impl(0, 0, a0)
#endif
FILE_EVENT1(30169, trace_Strand_Cannot_Fire_Timer_Impl, LOG_WARNING, PAL_T("Strand_FireTimer: Timer not initialized on strand (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotOpenHttptraceFile(a0, a1) trace_CannotOpenHttptraceFile_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_CannotOpenHttptraceFile(a0, a1) trace_CannotOpenHttptraceFile_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENT2(30170, trace_CannotOpenHttptraceFile_Impl, LOG_WARNING, PAL_T("cannot open http trace file: %s, errno %d"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_NewFromDispFailed(a0) trace_IndiMgr_NewFromDispFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_NewFromDispFailed(a0) trace_IndiMgr_NewFromDispFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30171, trace_IndiMgr_NewFromDispFailed_Impl, LOG_WARNING, PAL_T("IndiMgr_NewFromDisp: Failed to initialize IndicationHost with disp (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostUnexpectedFinal(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostUnexpectedFinal_Impl(__FILE__, __LINE__, a0, tcs(a1), a2, a3, tcs(a4), a5)
#else
#define trace_SubscribeEntry_PostUnexpectedFinal(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostUnexpectedFinal_Impl(0, 0, a0, tcs(a1), a2, a3, tcs(a4), a5)
#endif
FILE_EVENT6(30172, trace_SubscribeEntry_PostUnexpectedFinal_Impl, LOG_WARNING, PAL_T("_SubscribeEntry_Post: entry (%p) in status (%T), received unexpected final msg(%p:%d:%T:%x)"), void *, const TChar *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostUnexpectedSubscribe(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostUnexpectedSubscribe_Impl(__FILE__, __LINE__, a0, tcs(a1), a2, a3, tcs(a4), a5)
#else
#define trace_SubscribeEntry_PostUnexpectedSubscribe(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostUnexpectedSubscribe_Impl(0, 0, a0, tcs(a1), a2, a3, tcs(a4), a5)
#endif
FILE_EVENT6(30173, trace_SubscribeEntry_PostUnexpectedSubscribe_Impl, LOG_WARNING, PAL_T("_SubscribeEntry_Post: entry (%p) in status (%T), received unexpected SubscribeRes msg(%p:%d:%T:%x)"), void *, const TChar *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostUnsupportedMessage(a0, a1, a2, a3) trace_SubscribeEntry_PostUnsupportedMessage_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_SubscribeEntry_PostUnsupportedMessage(a0, a1, a2, a3) trace_SubscribeEntry_PostUnsupportedMessage_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENT4(30174, trace_SubscribeEntry_PostUnsupportedMessage_Impl, LOG_WARNING, PAL_T("_SubscribeEntry_Post: Unsupported msg(%p:%d:%T:%x)"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndicationClassList_NewByFilter_NoClassFound(a0) trace_IndicationClassList_NewByFilter_NoClassFound_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_IndicationClassList_NewByFilter_NoClassFound(a0) trace_IndicationClassList_NewByFilter_NoClassFound_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30175, trace_IndicationClassList_NewByFilter_NoClassFound_Impl, LOG_WARNING, PAL_T("IndicationClassList_NewByFilter: No class found for filter (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed(a0) trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed(a0) trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30176, trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed_Impl, LOG_WARNING, PAL_T("IndiMgr_HandleSubscribeReq: StrandMany_New failed, req (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribeReq_FailedCreate(a0) trace_IndiMgr_HandleSubscribeReq_FailedCreate_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_HandleSubscribeReq_FailedCreate(a0) trace_IndiMgr_HandleSubscribeReq_FailedCreate_Impl(0, 0, a0)
#endif
FILE_EVENT1(30177, trace_IndiMgr_HandleSubscribeReq_FailedCreate_Impl, LOG_WARNING, PAL_T("IndiMgr_HandleSubscribeReq: Failed to create All StrandEntries or All SubscribeReq msg; req (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ObjectIsnotAValidSubscr(a0) trace_ObjectIsnotAValidSubscr_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ObjectIsnotAValidSubscr(a0) trace_ObjectIsnotAValidSubscr_Impl(0, 0, a0)
#endif
FILE_EVENT1(30178, trace_ObjectIsnotAValidSubscr_Impl, LOG_WARNING, PAL_T("Object %p is not a valid Subscription object."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_NotValidSubscr(a0) trace_Subscription_OnAdd_NotValidSubscr_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnAdd_NotValidSubscr(a0) trace_Subscription_OnAdd_NotValidSubscr_Impl(0, 0, a0)
#endif
FILE_EVENT1(30179, trace_Subscription_OnAdd_NotValidSubscr_Impl, LOG_WARNING, PAL_T("Subscription_OnAdd: Object %p is not a valid Subscription object."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_CimBaseOnAddFailed(a0) trace_Subscription_OnAdd_CimBaseOnAddFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnAdd_CimBaseOnAddFailed(a0) trace_Subscription_OnAdd_CimBaseOnAddFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30180, trace_Subscription_OnAdd_CimBaseOnAddFailed_Impl, LOG_WARNING, PAL_T("Subscription_OnAdd: Call CimBase_OnAdd Failed with %d."), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_FailedAddFilter(a0) trace_Subscription_OnAdd_FailedAddFilter_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnAdd_FailedAddFilter(a0) trace_Subscription_OnAdd_FailedAddFilter_Impl(0, 0, a0)
#endif
FILE_EVENT1(30181, trace_Subscription_OnAdd_FailedAddFilter_Impl, LOG_WARNING, PAL_T("Subscription_OnAdd: Failed to add filter, error %d."), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_FailedAddListener(a0) trace_Subscription_OnAdd_FailedAddListener_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnAdd_FailedAddListener(a0) trace_Subscription_OnAdd_FailedAddListener_Impl(0, 0, a0)
#endif
FILE_EVENT1(30182, trace_Subscription_OnAdd_FailedAddListener_Impl, LOG_WARNING, PAL_T("Subscription_OnAdd: Failed to add listener, error %d."), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_ProvRegIsNull() trace_Subscription_OnAdd_ProvRegIsNull_Impl(__FILE__, __LINE__)
#else
#define trace_Subscription_OnAdd_ProvRegIsNull() trace_Subscription_OnAdd_ProvRegIsNull_Impl(0, 0)
#endif
FILE_EVENT0(30183, trace_Subscription_OnAdd_ProvRegIsNull_Impl, LOG_WARNING, PAL_T("Subscription_OnAdd: ProvReg object is NULL"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnRemove_NotValidSubscr(a0) trace_Subscription_OnRemove_NotValidSubscr_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnRemove_NotValidSubscr(a0) trace_Subscription_OnRemove_NotValidSubscr_Impl(0, 0, a0)
#endif
FILE_EVENT1(30184, trace_Subscription_OnRemove_NotValidSubscr_Impl, LOG_WARNING, PAL_T("Subscription_OnRemove: Object %p is not a valid Subscription object."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnRemove_RemoveFailed(a0, a1) trace_Subscription_OnRemove_RemoveFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Subscription_OnRemove_RemoveFailed(a0, a1) trace_Subscription_OnRemove_RemoveFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30185, trace_Subscription_OnRemove_RemoveFailed_Impl, LOG_WARNING, PAL_T("Subscription_OnRemove: Failed to remove subscription %p from container %p."), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnRemove_RemoveFilterFailed(a0) trace_Subscription_OnRemove_RemoveFilterFailed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_OnRemove_RemoveFilterFailed(a0) trace_Subscription_OnRemove_RemoveFilterFailed_Impl(0, 0, a0)
#endif
FILE_EVENT1(30186, trace_Subscription_OnRemove_RemoveFilterFailed_Impl, LOG_WARNING, PAL_T("Subscription_OnRemove: Call IndiMgr_RemoveFilter() Failed with %d."), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifecycleSubscription_ContextNotInitialized(a0) trace_LifecycleSubscription_ContextNotInitialized_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_LifecycleSubscription_ContextNotInitialized(a0) trace_LifecycleSubscription_ContextNotInitialized_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30187, trace_LifecycleSubscription_ContextNotInitialized_Impl, LOG_WARNING, PAL_T("Provider_InvokeSubscribe: Lifecycle context not initialized for class (%T)."), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Disp_ErrorInteractionAlloc() trace_Disp_ErrorInteractionAlloc_Impl(__FILE__, __LINE__)
#else
#define trace_Disp_ErrorInteractionAlloc() trace_Disp_ErrorInteractionAlloc_Impl(0, 0)
#endif
FILE_EVENT0(30188, trace_Disp_ErrorInteractionAlloc_Impl, LOG_WARNING, PAL_T("Dispatcher cannot allocate interaction"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Disp_ErrorEnumEntryAlloc() trace_Disp_ErrorEnumEntryAlloc_Impl(__FILE__, __LINE__)
#else
#define trace_Disp_ErrorEnumEntryAlloc() trace_Disp_ErrorEnumEntryAlloc_Impl(0, 0)
#endif
FILE_EVENT0(30189, trace_Disp_ErrorEnumEntryAlloc_Impl, LOG_WARNING, PAL_T("Dispatcher cannot allocate EnumEntry"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Disp_ErrorAddEntry() trace_Disp_ErrorAddEntry_Impl(__FILE__, __LINE__)
#else
#define trace_Disp_ErrorAddEntry() trace_Disp_ErrorAddEntry_Impl(0, 0)
#endif
FILE_EVENT0(30190, trace_Disp_ErrorAddEntry_Impl, LOG_WARNING, PAL_T("Dispatcher cannot add entry"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_Outofmemory(a0) trace_IndiMgr_HandleSubscribe_Outofmemory_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_HandleSubscribe_Outofmemory(a0) trace_IndiMgr_HandleSubscribe_Outofmemory_Impl(0, 0, a0)
#endif
FILE_EVENT1(30191, trace_IndiMgr_HandleSubscribe_Outofmemory_Impl, LOG_WARNING, PAL_T("IndiMgr_HandleSubscribeReq: %p Out of memory"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnsupportedDeliveryMode(a0) trace_Wsman_UnsupportedDeliveryMode_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_UnsupportedDeliveryMode(a0) trace_Wsman_UnsupportedDeliveryMode_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30192, trace_Wsman_UnsupportedDeliveryMode_Impl, LOG_WARNING, PAL_T("WS_ParseSubscribeBody: Unsupported delivery mode %T"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_ExpectedDeliveryMode() trace_Wsman_ExpectedDeliveryMode_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_ExpectedDeliveryMode() trace_Wsman_ExpectedDeliveryMode_Impl(0, 0)
#endif
FILE_EVENT0(30193, trace_Wsman_ExpectedDeliveryMode_Impl, LOG_WARNING, PAL_T("WS_ParseSubscribeBody: Delivery mode expected, but not specified by client"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast(a0) trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast(a0) trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(30194, trace_Wsman_SubscribeRequest_InvalidExpires_TimeInPast_Impl, LOG_WARNING, PAL_T("_ValidateSubscribeRequest: Expires date %T is in the past"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported() trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported() trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported_Impl(0, 0)
#endif
FILE_EVENT0(30195, trace_Wsman_SubscribeRequest_InvalidExpires_WallClockNotSupported_Impl, LOG_WARNING, PAL_T("_ValidateSubscribeRequest: Wall clock time not supported"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeRequest_InvalidExpiresValue() trace_Wsman_SubscribeRequest_InvalidExpiresValue_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_SubscribeRequest_InvalidExpiresValue() trace_Wsman_SubscribeRequest_InvalidExpiresValue_Impl(0, 0)
#endif
FILE_EVENT0(30196, trace_Wsman_SubscribeRequest_InvalidExpiresValue_Impl, LOG_WARNING, PAL_T("_ValidateSubscribeRequest: Invalid duration specified.  Cannot be zero"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InvalidHeartbeatType() trace_Wsman_InvalidHeartbeatType_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_InvalidHeartbeatType() trace_Wsman_InvalidHeartbeatType_Impl(0, 0)
#endif
FILE_EVENT0(30197, trace_Wsman_InvalidHeartbeatType_Impl, LOG_WARNING, PAL_T("_ValidateSubscribeRequest: Heartbeat must be xs:duration"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_InvalidActionRequest() trace_Wsman_InvalidActionRequest_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_InvalidActionRequest() trace_Wsman_InvalidActionRequest_Impl(0, 0)
#endif
FILE_EVENT0(30198, trace_Wsman_InvalidActionRequest_Impl, LOG_WARNING, PAL_T("_ValidateHeader: Unsupported requested action"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnsupportedConnectionRetry() trace_Wsman_UnsupportedConnectionRetry_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_UnsupportedConnectionRetry() trace_Wsman_UnsupportedConnectionRetry_Impl(0, 0)
#endif
FILE_EVENT0(30199, trace_Wsman_UnsupportedConnectionRetry_Impl, LOG_WARNING, PAL_T("_ValidateHeader: Unsupported feature: connection retry"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_PullRequest_InvalidMaxTimeValue() trace_Wsman_PullRequest_InvalidMaxTimeValue_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_PullRequest_InvalidMaxTimeValue() trace_Wsman_PullRequest_InvalidMaxTimeValue_Impl(0, 0)
#endif
FILE_EVENT0(30200, trace_Wsman_PullRequest_InvalidMaxTimeValue_Impl, LOG_WARNING, PAL_T("_ValidatePullRequest: Invalid MaxTime specified.  Cannot be zero"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER(a0, a1) trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER(a0, a1) trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30201, trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER_Impl, LOG_WARNING, PAL_T("Unable to convert specified timeout.  Using (%I64u) instead for request %d"), PAL_Uint64, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnableToconvertDatetimeToUsec_POSIX(a0, a1) trace_Wsman_UnableToconvertDatetimeToUsec_POSIX_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_UnableToconvertDatetimeToUsec_POSIX(a0, a1) trace_Wsman_UnableToconvertDatetimeToUsec_POSIX_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30202, trace_Wsman_UnableToconvertDatetimeToUsec_POSIX_Impl, LOG_WARNING, PAL_T("Unable to convert specified timeout.  Using (%llu) instead for request %d"), PAL_Uint64, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnumerationcontext_HeartbeatMissingPull(a0, a1) trace_WsmanEnumerationcontext_HeartbeatMissingPull_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanEnumerationcontext_HeartbeatMissingPull(a0, a1) trace_WsmanEnumerationcontext_HeartbeatMissingPull_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30203, trace_WsmanEnumerationcontext_HeartbeatMissingPull_Impl, LOG_WARNING, PAL_T("Heartbeat timeout: No PullRequest attached! Terminating enumeration context %p (%u)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnumerationcontext_HeartbeatCancelled(a0, a1) trace_WsmanEnumerationcontext_HeartbeatCancelled_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanEnumerationcontext_HeartbeatCancelled(a0, a1) trace_WsmanEnumerationcontext_HeartbeatCancelled_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30204, trace_WsmanEnumerationcontext_HeartbeatCancelled_Impl, LOG_WARNING, PAL_T("Heartbeat timeout: Timer cancelled for enumeration context %p (%u)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnectionData_OperationCancelled(a0, a1) trace_WsmanConnectionData_OperationCancelled_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanConnectionData_OperationCancelled(a0, a1) trace_WsmanConnectionData_OperationCancelled_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30205, trace_WsmanConnectionData_OperationCancelled_Impl, LOG_WARNING, PAL_T("Operation timeout: Timer cancelled for connection data %p action (%d)"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnectionData_OperationTimeout(a0, a1) trace_WsmanConnectionData_OperationTimeout_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanConnectionData_OperationTimeout(a0, a1) trace_WsmanConnectionData_OperationTimeout_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30206, trace_WsmanConnectionData_OperationTimeout_Impl, LOG_WARNING, PAL_T("Operation timeout: Timeout for connection data %p action (%d)"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeBookmark_Empty() trace_Wsman_SubscribeBookmark_Empty_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_SubscribeBookmark_Empty() trace_Wsman_SubscribeBookmark_Empty_Impl(0, 0)
#endif
FILE_EVENT0(30207, trace_Wsman_SubscribeBookmark_Empty_Impl, LOG_WARNING, PAL_T("_ValidateSubscribeRequest: The specified bookmark is invalid (empty)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NonRootUserAccessInprocProvider(a0, a1, a2) trace_NonRootUserAccessInprocProvider_Impl(__FILE__, __LINE__, scs(a0), tcs(a1), tcs(a2))
#else
#define trace_NonRootUserAccessInprocProvider(a0, a1, a2) trace_NonRootUserAccessInprocProvider_Impl(0, 0, scs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENT3(30208, trace_NonRootUserAccessInprocProvider_Impl, LOG_WARNING, PAL_T("AgentMgr_HandleRequest: Access denied. User (%s) attempted to access class (%T) under namespace (%T) from an in-process provider."), const char*, const TChar*, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ChildProcessTerminatedAbnormally(a0) trace_ChildProcessTerminatedAbnormally_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ChildProcessTerminatedAbnormally(a0) trace_ChildProcessTerminatedAbnormally_Impl(0, 0, a0)
#endif
FILE_EVENT1(30209, trace_ChildProcessTerminatedAbnormally_Impl, LOG_WARNING, PAL_T("child process with PID=[%d] terminated abnormally"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NtlmEnvIgnored(a0) trace_NtlmEnvIgnored_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_NtlmEnvIgnored(a0) trace_NtlmEnvIgnored_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(30210, trace_NtlmEnvIgnored_Impl, LOG_WARNING, PAL_T("NTLM_USER_FILE environment variable [%s] ignored"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Http_SslCompressionNotPresent() trace_Http_SslCompressionNotPresent_Impl(__FILE__, __LINE__)
#else
#define trace_Http_SslCompressionNotPresent() trace_Http_SslCompressionNotPresent_Impl(0, 0)
#endif
FILE_EVENT0(30211, trace_Http_SslCompressionNotPresent_Impl, LOG_WARNING, PAL_T("SSL Compression was disabled in the OMI configuration, but the version of SSL used by OMI does not support it."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TrackerHashMapAlreadyExists(a0, a1) trace_TrackerHashMapAlreadyExists_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_TrackerHashMapAlreadyExists(a0, a1) trace_TrackerHashMapAlreadyExists_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(30212, trace_TrackerHashMapAlreadyExists_Impl, LOG_WARNING, PAL_T("Tracker hash map item already exists (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Selector_AddHandler_AlreadyThere(a0, a1, a2) trace_Selector_AddHandler_AlreadyThere_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_Selector_AddHandler_AlreadyThere(a0, a1, a2) trace_Selector_AddHandler_AlreadyThere_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENT3(30213, trace_Selector_AddHandler_AlreadyThere_Impl, LOG_WARNING, PAL_T("Selector_AddHandler: selector=%p, handler=%p, name=%T ALREADY REGISTERED"), Selector *, Handler *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Selector_RemoveHandler_NotThere(a0, a1, a2) trace_Selector_RemoveHandler_NotThere_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_Selector_RemoveHandler_NotThere(a0, a1, a2) trace_Selector_RemoveHandler_NotThere_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENT3(30214, trace_Selector_RemoveHandler_NotThere_Impl, LOG_WARNING, PAL_T("Selector_RemoveHandler: selector=%p, handler=%p, name=%T NOT REGISTERED"), Selector *, Handler *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_DisconnectedFromServer() trace_Agent_DisconnectedFromServer_Impl(__FILE__, __LINE__)
#else
#define trace_Agent_DisconnectedFromServer() trace_Agent_DisconnectedFromServer_Impl(0, 0)
#endif
FILE_EVENT0(40000, trace_Agent_DisconnectedFromServer_Impl, LOG_INFO, PAL_T("disconnected form server; exiting"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_SendingIdleNotification() trace_Agent_SendingIdleNotification_Impl(__FILE__, __LINE__)
#else
#define trace_Agent_SendingIdleNotification() trace_Agent_SendingIdleNotification_Impl(0, 0)
#endif
FILE_EVENT0(40001, trace_Agent_SendingIdleNotification_Impl, LOG_INFO, PAL_T("sending 'agent-idle' notification to the server"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_ChangingIdleTimeout(a0) trace_Agent_ChangingIdleTimeout_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Agent_ChangingIdleTimeout(a0) trace_Agent_ChangingIdleTimeout_Impl(0, 0, a0)
#endif
FILE_EVENT1(40002, trace_Agent_ChangingIdleTimeout_Impl, LOG_INFO, PAL_T("changing idle timeout to %x sec"), MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Agent_Started(a0) trace_Agent_Started_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Agent_Started(a0) trace_Agent_Started_Impl(0, 0, a0)
#endif
FILE_EVENT1(40003, trace_Agent_Started_Impl, LOG_INFO, PAL_T("agent started; fd %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentMgr_SendErrorResponse(a0) trace_AgentMgr_SendErrorResponse_Impl(__FILE__, __LINE__, a0)
#else
#define trace_AgentMgr_SendErrorResponse(a0) trace_AgentMgr_SendErrorResponse_Impl(0, 0, a0)
#endif
FILE_EVENT1(40004, trace_AgentMgr_SendErrorResponse_Impl, LOG_INFO, PAL_T("_SendErrorResponse, RequestItem: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentMgr_SendRequestToAgent(a0, a1, a2, a3, a4, a5) trace_AgentMgr_SendRequestToAgent_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4, a5)
#else
#define trace_AgentMgr_SendRequestToAgent(a0, a1, a2, a3, a4, a5) trace_AgentMgr_SendRequestToAgent_Impl(0, 0, a0, a1, tcs(a2), a3, a4, a5)
#endif
FILE_EVENT6(40005, trace_AgentMgr_SendRequestToAgent_Impl, LOG_INFO, PAL_T("_SendRequestToAgent msg(%p:%d:%T:%x), from original operationId: %x to %x"), Message *, MI_Uint32, const TChar *, MI_Uint64, MI_Uint64, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispEnum_UnknownClass(a0, a1) trace_DispEnum_UnknownClass_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_DispEnum_UnknownClass(a0, a1) trace_DispEnum_UnknownClass_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENT2(40006, trace_DispEnum_UnknownClass_Impl, LOG_INFO, PAL_T("unknown class in enumerate request: %T:%T"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_LoadingServerCert(a0) trace_SSL_LoadingServerCert_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_LoadingServerCert(a0) trace_SSL_LoadingServerCert_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40007, trace_SSL_LoadingServerCert_Impl, LOG_INFO, PAL_T("---> SSL: Loading server certificate from: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SSL_LoadingCertPrivateKey(a0) trace_SSL_LoadingCertPrivateKey_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SSL_LoadingCertPrivateKey(a0) trace_SSL_LoadingCertPrivateKey_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40008, trace_SSL_LoadingCertPrivateKey_Impl, LOG_INFO, PAL_T("---> SSL: Loading certificate's private key from: %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SockAccept_Failed(a0) trace_SockAccept_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SockAccept_Failed(a0) trace_SockAccept_Failed_Impl(0, 0, a0)
#endif
FILE_EVENT1(40009, trace_SockAccept_Failed_Impl, LOG_INFO, PAL_T("Sock_Accept() failed; err %d\n"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketClose_REMOVEDESTROY() trace_SocketClose_REMOVEDESTROY_Impl(__FILE__, __LINE__)
#else
#define trace_SocketClose_REMOVEDESTROY() trace_SocketClose_REMOVEDESTROY_Impl(0, 0)
#endif
FILE_EVENT0(40010, trace_SocketClose_REMOVEDESTROY_Impl, LOG_INFO, PAL_T("closing socket due to SELECTOR_REMOVE or SELECTOR_DESTROY"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReceivedMessage(a0, a1, a2, a3) trace_Socket_ReceivedMessage_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_Socket_ReceivedMessage(a0, a1, a2, a3) trace_Socket_ReceivedMessage_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENT4(40011, trace_Socket_ReceivedMessage_Impl, LOG_INFO, PAL_T("done with receiving msg(%p:%d:%T:%x)"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ClosingConnection(a0, a1) trace_Socket_ClosingConnection_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Socket_ClosingConnection(a0, a1) trace_Socket_ClosingConnection_Impl(0, 0, a0, a1)
#endif
FILE_EVENT2(40012, trace_Socket_ClosingConnection_Impl, LOG_INFO, PAL_T("Socket: %p, closing connection (mask %x)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnloadingIdleProviders() trace_UnloadingIdleProviders_Impl(__FILE__, __LINE__)
#else
#define trace_UnloadingIdleProviders() trace_UnloadingIdleProviders_Impl(0, 0)
#endif
FILE_EVENT0(40013, trace_UnloadingIdleProviders_Impl, LOG_INFO, PAL_T("Unloading idle providers"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerReceivedNoOpReqTag(a0) trace_ServerReceivedNoOpReqTag_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ServerReceivedNoOpReqTag(a0) trace_ServerReceivedNoOpReqTag_Impl(0, 0, a0)
#endif
FILE_EVENT1(40014, trace_ServerReceivedNoOpReqTag_Impl, LOG_INFO, PAL_T("Received NoOpReqTag, terminateByNoop: %u"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_ProtocolRun(a0) trace_Server_ProtocolRun_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Server_ProtocolRun(a0) trace_Server_ProtocolRun_Impl(0, 0, a0)
#endif
FILE_EVENT1(40015, trace_Server_ProtocolRun_Impl, LOG_INFO, PAL_T("after run, r %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_LiveTimeExpired() trace_Server_LiveTimeExpired_Impl(__FILE__, __LINE__)
#else
#define trace_Server_LiveTimeExpired() trace_Server_LiveTimeExpired_Impl(0, 0)
#endif
FILE_EVENT0(40016, trace_Server_LiveTimeExpired_Impl, LOG_INFO, PAL_T("livetime expired; server stopped"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerTerminated() trace_ServerTerminated_Impl(__FILE__, __LINE__)
#else
#define trace_ServerTerminated() trace_ServerTerminated_Impl(0, 0)
#endif
FILE_EVENT0(40017, trace_ServerTerminated_Impl, LOG_INFO, PAL_T("server terminated"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerReReadingConfig() trace_ServerReReadingConfig_Impl(__FILE__, __LINE__)
#else
#define trace_ServerReReadingConfig() trace_ServerReReadingConfig_Impl(0, 0)
#endif
FILE_EVENT0(40018, trace_ServerReReadingConfig_Impl, LOG_INFO, PAL_T("re-reading configuration"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerExiting(a0) trace_ServerExiting_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_ServerExiting(a0) trace_ServerExiting_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40019, trace_ServerExiting_Impl, LOG_INFO, PAL_T("%s exiting"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_DelayingResponse(a0) trace_WsmanEnum_DelayingResponse_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanEnum_DelayingResponse(a0) trace_WsmanEnum_DelayingResponse_Impl(0, 0, a0)
#endif
FILE_EVENT1(40020, trace_WsmanEnum_DelayingResponse_Impl, LOG_INFO, PAL_T("WsmanEnum: %p, Delaying response"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetFlagsFromWsmanOptions(a0, a1, a2, a3, a4) trace_GetFlagsFromWsmanOptions_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_GetFlagsFromWsmanOptions(a0, a1, a2, a3, a4) trace_GetFlagsFromWsmanOptions_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENT5(40021, trace_GetFlagsFromWsmanOptions_Impl, LOG_INFO, PAL_T("includeClassOrigin = %d includeInheritanceHierarchy = %d includeInheritedElements = %d includeQualifiers = %d usePreciseArrays = %d"), int, int, int, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ListeningOnPort(a0) trace_ListeningOnPort_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ListeningOnPort(a0) trace_ListeningOnPort_Impl(0, 0, a0)
#endif
FILE_EVENT1(40022, trace_ListeningOnPort_Impl, LOG_INFO, PAL_T("listening on port: http %u"), unsigned short)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ListeningOnEncryptedPort(a0) trace_ListeningOnEncryptedPort_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ListeningOnEncryptedPort(a0) trace_ListeningOnEncryptedPort_Impl(0, 0, a0)
#endif
FILE_EVENT1(40023, trace_ListeningOnEncryptedPort_Impl, LOG_INFO, PAL_T("listening on port: https %u"), unsigned short)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PreExecOk(a0) trace_PreExecOk_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_PreExecOk(a0) trace_PreExecOk_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40024, trace_PreExecOk_Impl, LOG_INFO, PAL_T("Executed PREEXEC program: {%s}"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgr_CanPostIndication_Fail(a0) trace_SubMgr_CanPostIndication_Fail_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubMgr_CanPostIndication_Fail(a0) trace_SubMgr_CanPostIndication_Fail_Impl(0, 0, a0)
#endif
FILE_EVENT1(40025, trace_SubMgr_CanPostIndication_Fail_Impl, LOG_INFO, PAL_T("SubMgr_CanPostIndication: Thread %x: it is not supported to post indication on the thread invoking EnableIndication and Subscribe"), unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionList_EnsureArray_Overflow(a0) trace_SubscriptionList_EnsureArray_Overflow_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubscriptionList_EnsureArray_Overflow(a0) trace_SubscriptionList_EnsureArray_Overflow_Impl(0, 0, a0)
#endif
FILE_EVENT1(40026, trace_SubscriptionList_EnsureArray_Overflow_Impl, LOG_INFO, PAL_T("_SubscriptionList_EnsureArray: Thread %x: subscription list capacity overflowed"), unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_DeliveryMode(a0) trace_Wsman_DeliveryMode_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_DeliveryMode(a0) trace_Wsman_DeliveryMode_Impl(0, 0, tcs(a0))
#endif
FILE_EVENT1(40027, trace_Wsman_DeliveryMode_Impl, LOG_INFO, PAL_T("WS_ParseSubscribeBody: Delivery mode %T specified"), const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_ReadHeader_ConnectionClosed(a0) trace_Socket_ReadHeader_ConnectionClosed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_ReadHeader_ConnectionClosed(a0) trace_Socket_ReadHeader_ConnectionClosed_Impl(0, 0, a0)
#endif
FILE_EVENT1(40028, trace_Socket_ReadHeader_ConnectionClosed_Impl, LOG_INFO, PAL_T("Socket: %p, Connection Closed while reading header\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_Read_ConnectionClosed(a0) trace_Socket_Read_ConnectionClosed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_Read_ConnectionClosed(a0) trace_Socket_Read_ConnectionClosed_Impl(0, 0, a0)
#endif
FILE_EVENT1(40029, trace_Socket_Read_ConnectionClosed_Impl, LOG_INFO, PAL_T("Socket: %p, Connection Closed while reading\n"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestList_ScheduleItem_CreateNonIOThreadFailed(a0, a1) trace_RequestList_ScheduleItem_CreateNonIOThreadFailed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_RequestList_ScheduleItem_CreateNonIOThreadFailed(a0, a1) trace_RequestList_ScheduleItem_CreateNonIOThreadFailed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENT2(40030, trace_RequestList_ScheduleItem_CreateNonIOThreadFailed_Impl, LOG_INFO, PAL_T("RequestList_ScheduleItem: Failed to create non-io thread. error (%d : %T)"), int, const TChar*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentClosedConnection(a0) trace_AgentClosedConnection_Impl(__FILE__, __LINE__, a0)
#else
#define trace_AgentClosedConnection(a0) trace_AgentClosedConnection_Impl(0, 0, a0)
#endif
FILE_EVENT1(40031, trace_AgentClosedConnection_Impl, LOG_INFO, PAL_T("agent running as [%d] closed its connection to the server"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Selector_AddHandler(a0, a1, a2) trace_Selector_AddHandler_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_Selector_AddHandler(a0, a1, a2) trace_Selector_AddHandler_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENT3(40032, trace_Selector_AddHandler_Impl, LOG_INFO, PAL_T("Selector_AddHandler: selector=%p, handler=%p, name=%T"), void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Selector_RemoveHandler(a0, a1, a2) trace_Selector_RemoveHandler_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_Selector_RemoveHandler(a0, a1, a2) trace_Selector_RemoveHandler_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENT3(40033, trace_Selector_RemoveHandler_Impl, LOG_INFO, PAL_T("Selector_RemoveHandler: selector=%p, handler=%p, name=%T"), void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Selector_RemoveAllHandlers(a0, a1, a2) trace_Selector_RemoveAllHandlers_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_Selector_RemoveAllHandlers(a0, a1, a2) trace_Selector_RemoveAllHandlers_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENT3(40034, trace_Selector_RemoveAllHandlers_Impl, LOG_INFO, PAL_T("Selector_RemoveAllHandlers: selector=%p, handler=%p, name=%T"), void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerFailedPamCheckUser(a0) trace_ServerFailedPamCheckUser_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_ServerFailedPamCheckUser(a0) trace_ServerFailedPamCheckUser_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40035, trace_ServerFailedPamCheckUser_Impl, LOG_INFO, PAL_T("Server failed to authenticate user: (%s)"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SigHUP_received(a0) trace_SigHUP_received_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SigHUP_received(a0) trace_SigHUP_received_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40036, trace_SigHUP_received_Impl, LOG_INFO, PAL_T("SIGHUP received at: (%s)"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SigTERM_received(a0) trace_SigTERM_received_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_SigTERM_received(a0) trace_SigTERM_received_Impl(0, 0, scs(a0))
#endif
FILE_EVENT1(40037, trace_SigTERM_received_Impl, LOG_INFO, PAL_T("SIGTERM received at: (%s)"), const char*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FunctionEntered(a0, a1) trace_FunctionEntered_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_FunctionEntered(a0, a1) trace_FunctionEntered_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENTD2(45000, trace_FunctionEntered_Impl, LOG_DEBUG, PAL_T("LOGTRACE: %s(%u)"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_BatchZdup_Failed() trace_BatchZdup_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_BatchZdup_Failed() trace_BatchZdup_Failed_Impl(0, 0)
#endif
FILE_EVENTD0(45001, trace_BatchZdup_Failed_Impl, LOG_DEBUG, PAL_T("Batch_Zdup() failed: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_BatchAllocFailed() trace_BatchAllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_BatchAllocFailed() trace_BatchAllocFailed_Impl(0, 0)
#endif
FILE_EVENTD0(45002, trace_BatchAllocFailed_Impl, LOG_DEBUG, PAL_T("Batch allocation failed: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_BatchCreationFailed() trace_BatchCreationFailed_Impl(__FILE__, __LINE__)
#else
#define trace_BatchCreationFailed() trace_BatchCreationFailed_Impl(0, 0)
#endif
FILE_EVENTD0(45003, trace_BatchCreationFailed_Impl, LOG_DEBUG, PAL_T("Batch creation failed: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HeapMemoryAllocFailed() trace_HeapMemoryAllocFailed_Impl(__FILE__, __LINE__)
#else
#define trace_HeapMemoryAllocFailed() trace_HeapMemoryAllocFailed_Impl(0, 0)
#endif
FILE_EVENTD0(45004, trace_HeapMemoryAllocFailed_Impl, LOG_DEBUG, PAL_T("Heap memory allocation failed: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MessageFromBatch(a0, a1) trace_MessageFromBatch_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MessageFromBatch(a0, a1) trace_MessageFromBatch_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45005, trace_MessageFromBatch_Impl, LOG_DEBUG, PAL_T("MessageFromBatch:- msg tag is %d, index: %d"), MI_Uint32, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentElemPostingMessage(a0, a1) trace_AgentElemPostingMessage_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_AgentElemPostingMessage(a0, a1) trace_AgentElemPostingMessage_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45006, trace_AgentElemPostingMessage_Impl, LOG_DEBUG, PAL_T("AgentElem: Posting message for interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentElemAck(a0, a1) trace_AgentElemAck_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_AgentElemAck(a0, a1) trace_AgentElemAck_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45007, trace_AgentElemAck_Impl, LOG_DEBUG, PAL_T("AgentElem: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentElemFoundKey(a0, a1, a2, a3, a4) trace_AgentElemFoundKey_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_AgentElemFoundKey(a0, a1, a2, a3, a4) trace_AgentElemFoundKey_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45008, trace_AgentElemFoundKey_Impl, LOG_DEBUG, PAL_T("_AgentElem_FindRequest, Agent %p(%p), Found key: %x, Request: %p(%p)"), void *, Strand *, MI_Uint64, void *, Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItemPostingMessage(a0, a1, a2) trace_RequestItemPostingMessage_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_RequestItemPostingMessage(a0, a1, a2) trace_RequestItemPostingMessage_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45009, trace_RequestItemPostingMessage_Impl, LOG_DEBUG, PAL_T("RequestItem: %p Posting message for interaction [%p]<-%p"), Strand *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItemAck(a0, a1) trace_RequestItemAck_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_RequestItemAck(a0, a1) trace_RequestItemAck_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45010, trace_RequestItemAck_Impl, LOG_DEBUG, PAL_T("RequestItem: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItemCancel(a0) trace_RequestItemCancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestItemCancel(a0) trace_RequestItemCancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45011, trace_RequestItemCancel_Impl, LOG_DEBUG, PAL_T("_RequestItem_Cancel: on RequestItem (%p))"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendMessageToAgent(a0) trace_SendMessageToAgent_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SendMessageToAgent(a0) trace_SendMessageToAgent_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45012, trace_SendMessageToAgent_Impl, LOG_DEBUG, PAL_T("_SendMessageToAgent msg tag = %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentMgrHandleRequest(a0, a1) trace_AgentMgrHandleRequest_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_AgentMgrHandleRequest(a0, a1) trace_AgentMgrHandleRequest_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45013, trace_AgentMgrHandleRequest_Impl, LOG_DEBUG, PAL_T("AgentMgr_HandleRequest %p (tag %d)"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_BeginClasses_Failed(a0, a1) trace_ProvReg_BeginClasses_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_BeginClasses_Failed(a0, a1) trace_ProvReg_BeginClasses_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45014, trace_ProvReg_BeginClasses_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_BeginClasses() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_NextClass_Failed(a0, a1) trace_ProvReg_NextClass_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_NextClass_Failed(a0, a1) trace_ProvReg_NextClass_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45015, trace_ProvReg_NextClass_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_NextClass() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_EndClasses_Failed(a0, a1) trace_ProvReg_EndClasses_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_EndClasses_Failed(a0, a1) trace_ProvReg_EndClasses_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45016, trace_ProvReg_EndClasses_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_EndClasses() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_BeginAssocClasses_Failed(a0, a1) trace_ProvReg_BeginAssocClasses_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_BeginAssocClasses_Failed(a0, a1) trace_ProvReg_BeginAssocClasses_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45017, trace_ProvReg_BeginAssocClasses_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_BeginAssocClasses() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_NextAssocClass_Failed(a0, a1) trace_ProvReg_NextAssocClass_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_NextAssocClass_Failed(a0, a1) trace_ProvReg_NextAssocClass_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45018, trace_ProvReg_NextAssocClass_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_NextAssocClass() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvReg_EndAssocClasses_Failed(a0, a1) trace_ProvReg_EndAssocClasses_Failed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvReg_EndAssocClasses_Failed(a0, a1) trace_ProvReg_EndAssocClasses_Failed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45019, trace_ProvReg_EndAssocClasses_Failed_Impl, LOG_DEBUG, PAL_T("ProvReg_EndAssocClasses() failed: %u: %T"), unsigned short, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FoundNoProvider(a0) trace_FoundNoProvider_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_FoundNoProvider(a0) trace_FoundNoProvider_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45020, trace_FoundNoProvider_Impl, LOG_DEBUG, PAL_T("found no providers for class: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispDeleteInteraction(a0) trace_DispDeleteInteraction_Impl(__FILE__, __LINE__, a0)
#else
#define trace_DispDeleteInteraction(a0) trace_DispDeleteInteraction_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45021, trace_DispDeleteInteraction_Impl, LOG_DEBUG, PAL_T("Disp: delete interaction [%p]"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispatchEnumDispInteraction(a0) trace_DispatchEnumDispInteraction_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_DispatchEnumDispInteraction(a0) trace_DispatchEnumDispInteraction_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45022, trace_DispatchEnumDispInteraction_Impl, LOG_DEBUG, PAL_T("_DispatchEnumerateInstancesReq() for class: %T (Thru Dispatcher Interaction)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispatchEnumDirectly(a0) trace_DispatchEnumDirectly_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_DispatchEnumDirectly(a0) trace_DispatchEnumDirectly_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45023, trace_DispatchEnumDirectly_Impl, LOG_DEBUG, PAL_T("_DispatchEnumerateInstancesReq() for class: %T (Directly)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispatchAssoc(a0) trace_DispatchAssoc_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_DispatchAssoc(a0) trace_DispatchAssoc_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45024, trace_DispatchAssoc_Impl, LOG_DEBUG, PAL_T("_DispatchAssocReq() for class: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispPostingMessage(a0, a1) trace_DispPostingMessage_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_DispPostingMessage(a0, a1) trace_DispPostingMessage_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45025, trace_DispPostingMessage_Impl, LOG_DEBUG, PAL_T("Disp: Posting message for enum/assoc/ref interaction %p<-[%p]"), Interaction *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispAckBaseInteraction(a0, a1) trace_DispAckBaseInteraction_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_DispAckBaseInteraction(a0, a1) trace_DispAckBaseInteraction_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45026, trace_DispAckBaseInteraction_Impl, LOG_DEBUG, PAL_T("Disp: Ack on base interaction [%p]<-%p"), Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NoProviderForClass(a0, a1) trace_NoProviderForClass_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_NoProviderForClass(a0, a1) trace_NoProviderForClass_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENTD2(45027, trace_NoProviderForClass_Impl, LOG_DEBUG, PAL_T("cannot find provider for class: %T/%T"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgrHandleSub(a0) trace_IndiMgrHandleSub_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgrHandleSub(a0) trace_IndiMgrHandleSub_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45028, trace_IndiMgrHandleSub_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq() returns: %u"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClassNameIsExpectedForInvoke() trace_ClassNameIsExpectedForInvoke_Impl(__FILE__, __LINE__)
#else
#define trace_ClassNameIsExpectedForInvoke() trace_ClassNameIsExpectedForInvoke_Impl(0, 0)
#endif
FILE_EVENTD0(45029, trace_ClassNameIsExpectedForInvoke_Impl, LOG_DEBUG, PAL_T("class name is expected for invoke"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispHandleInteractionRequest(a0, a1, a2, a3, a4, a5) trace_DispHandleInteractionRequest_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4), a5)
#else
#define trace_DispHandleInteractionRequest(a0, a1, a2, a3, a4, a5) trace_DispHandleInteractionRequest_Impl(0, 0, a0, a1, a2, a3, tcs(a4), a5)
#endif
FILE_EVENTD6(45030, trace_DispHandleInteractionRequest_Impl, LOG_DEBUG, PAL_T("Disp_HandleInteractionRequest: self (%p), interaction(%p), msg(%p:%d:%T:%x)"), void *, Interaction *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispUnsupportedMessage(a0, a1, a2, a3, a4, a5) trace_DispUnsupportedMessage_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4), a5)
#else
#define trace_DispUnsupportedMessage(a0, a1, a2, a3, a4, a5) trace_DispUnsupportedMessage_Impl(0, 0, a0, a1, a2, a3, tcs(a4), a5)
#endif
FILE_EVENTD6(45031, trace_DispUnsupportedMessage_Impl, LOG_DEBUG, PAL_T("Disp_HandleInteractionRequest: self (%p), interaction(%p), Unsupported msg(%p:%d:%T:%x)"), void *, Interaction *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispHandlRequest() trace_DispHandlRequest_Impl(__FILE__, __LINE__)
#else
#define trace_DispHandlRequest() trace_DispHandlRequest_Impl(0, 0)
#endif
FILE_EVENTD0(45032, trace_DispHandlRequest_Impl, LOG_DEBUG, PAL_T("Disp_HandleRequest"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpSocketPosting(a0, a1) trace_HttpSocketPosting_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_HttpSocketPosting(a0, a1) trace_HttpSocketPosting_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45033, trace_HttpSocketPosting_Impl, LOG_DEBUG, PAL_T("HttpSocket: Posting message for interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpSocketAck(a0, a1) trace_HttpSocketAck_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_HttpSocketAck(a0, a1) trace_HttpSocketAck_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45034, trace_HttpSocketAck_Impl, LOG_DEBUG, PAL_T("HttpSocket: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpSocketFinish(a0) trace_HttpSocketFinish_Impl(__FILE__, __LINE__, a0)
#else
#define trace_HttpSocketFinish(a0) trace_HttpSocketFinish_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45035, trace_HttpSocketFinish_Impl, LOG_DEBUG, PAL_T("HttpSocket: %p _HttpSocket_Finish"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HttpSocketAuxNewRequest(a0, a1) trace_HttpSocketAuxNewRequest_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_HttpSocketAuxNewRequest(a0, a1) trace_HttpSocketAuxNewRequest_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45036, trace_HttpSocketAuxNewRequest_Impl, LOG_DEBUG, PAL_T("HttpSocket: %p _HttpSocket_Aux_NewRequest, Request: %p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestItemParentPost(a0, a1) trace_RequestItemParentPost_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_RequestItemParentPost(a0, a1) trace_RequestItemParentPost_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45037, trace_RequestItemParentPost_Impl, LOG_DEBUG, PAL_T("_RequestItem_ParentPost: %p, msg: %p"), void *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AgentItemCreated(a0) trace_AgentItemCreated_Impl(__FILE__, __LINE__, a0)
#else
#define trace_AgentItemCreated(a0) trace_AgentItemCreated_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45038, trace_AgentItemCreated_Impl, LOG_DEBUG, PAL_T("AgentItem created: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesFoundTypeClass(a0, a1) trace_DiscoverClassesFoundTypeClass_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_DiscoverClassesFoundTypeClass(a0, a1) trace_DiscoverClassesFoundTypeClass_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENTD2(45039, trace_DiscoverClassesFoundTypeClass_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: Found %T class (%T)"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesFailedToAdd(a0, a1) trace_DiscoverClassesFailedToAdd_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_DiscoverClassesFailedToAdd(a0, a1) trace_DiscoverClassesFailedToAdd_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45040, trace_DiscoverClassesFailedToAdd_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: Failed to add ProvRegEntry for class (%T), error code (%d)"), const TChar *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesNoRegInfo(a0, a1, a2) trace_DiscoverClassesNoRegInfo_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define trace_DiscoverClassesNoRegInfo(a0, a1, a2) trace_DiscoverClassesNoRegInfo_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENTD3(45041, trace_DiscoverClassesNoRegInfo_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: No reginfo for %T class (%T) under namespace (%T)"), const TChar *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesBeginFailed(a0, a1, a2, a3) trace_DiscoverClassesBeginFailed_Impl(__FILE__, __LINE__, a0, tcs(a1), tcs(a2), tcs(a3))
#else
#define trace_DiscoverClassesBeginFailed(a0, a1, a2, a3) trace_DiscoverClassesBeginFailed_Impl(0, 0, a0, tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENTD4(45042, trace_DiscoverClassesBeginFailed_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: ProvReg_BeginClasses failed: %u: %T; namespace (%T), classname (%T)"), MI_Result, const TChar *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesNextFailed(a0, a1, a2, a3) trace_DiscoverClassesNextFailed_Impl(__FILE__, __LINE__, a0, tcs(a1), tcs(a2), tcs(a3))
#else
#define trace_DiscoverClassesNextFailed(a0, a1, a2, a3) trace_DiscoverClassesNextFailed_Impl(0, 0, a0, tcs(a1), tcs(a2), tcs(a3))
#endif
FILE_EVENTD4(45043, trace_DiscoverClassesNextFailed_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: ProvReg_NextClass failed: %u: %T; namespace (%T), classname (%T)"), MI_Result, const TChar *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesBeginFailedProvRegEntry(a0, a1) trace_DiscoverClassesBeginFailedProvRegEntry_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_DiscoverClassesBeginFailedProvRegEntry(a0, a1) trace_DiscoverClassesBeginFailedProvRegEntry_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45044, trace_DiscoverClassesBeginFailedProvRegEntry_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: Failed to add ProvRegEntry for class (%T), error (%d)."), const TChar *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverClassesEndFailed(a0, a1) trace_DiscoverClassesEndFailed_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_DiscoverClassesEndFailed(a0, a1) trace_DiscoverClassesEndFailed_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45045, trace_DiscoverClassesEndFailed_Impl, LOG_DEBUG, PAL_T("_DiscoverClassAndChildrenClasses: ProvReg_EndClasses failed: %u: %T"), MI_Result, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DiscoverIndicationFoundClasses(a0) trace_DiscoverIndicationFoundClasses_Impl(__FILE__, __LINE__, a0)
#else
#define trace_DiscoverIndicationFoundClasses(a0) trace_DiscoverIndicationFoundClasses_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45046, trace_DiscoverIndicationFoundClasses_Impl, LOG_DEBUG, PAL_T("_DiscoverIndicationClass: Found %d classes"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndicationClassListCreated(a0) trace_IndicationClassListCreated_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndicationClassListCreated(a0) trace_IndicationClassListCreated_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45047, trace_IndicationClassListCreated_Impl, LOG_DEBUG, PAL_T("IndicationClassList_NewByFilter: created clist(%p) succeed"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndicationClassListDelete(a0) trace_IndicationClassListDelete_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndicationClassListDelete(a0) trace_IndicationClassListDelete_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45048, trace_IndicationClassListDelete_Impl, LOG_DEBUG, PAL_T("IndicationClassList_Delete: self(%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndicationClassListDeleteCompleted(a0) trace_IndicationClassListDeleteCompleted_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndicationClassListDeleteCompleted(a0) trace_IndicationClassListDeleteCompleted_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45049, trace_IndicationClassListDeleteCompleted_Impl, LOG_DEBUG, PAL_T("IndicationClassList_Delete: self(%p) complete"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_QueueingSocket(a0) trace_QueueingSocket_Impl(__FILE__, __LINE__, a0)
#else
#define trace_QueueingSocket(a0) trace_QueueingSocket_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45050, trace_QueueingSocket_Impl, LOG_DEBUG, PAL_T("Queueing on socket: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_FindSubRequest_FoundKey(a0, a1, a2, a3, a4) trace_FindSubRequest_FoundKey_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_FindSubRequest_FoundKey(a0, a1, a2, a3, a4) trace_FindSubRequest_FoundKey_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45051, trace_FindSubRequest_FoundKey_Impl, LOG_DEBUG, PAL_T("__FindSubRequest: SubscribeElem %p(%p), Found key: %x, Request: %p(%p)"), void *, Strand *, MI_Uint64, void *, Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInAuxPostOther(a0, a1, a2, a3, a4) trace_ConnectionInAuxPostOther_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_ConnectionInAuxPostOther(a0, a1, a2, a3, a4) trace_ConnectionInAuxPostOther_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45052, trace_ConnectionInAuxPostOther_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_Aux_PostOther: %p, posting msg(%p:%d:%T:%x)"), Strand *, Message *, int, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInClose(a0, a1) trace_ConnectionInClose_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ConnectionInClose(a0, a1) trace_ConnectionInClose_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45053, trace_ConnectionInClose_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_Close: Closed on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInFindRequest_CannotFind(a0, a1, a2) trace_ConnectionInFindRequest_CannotFind_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ConnectionInFindRequest_CannotFind(a0, a1, a2) trace_ConnectionInFindRequest_CannotFind_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45054, trace_ConnectionInFindRequest_CannotFind_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_FindRequest, Agent %p(%p), Cannot find key: %x (may be new request)"), void *, Strand *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInFindRequest_Found(a0, a1, a2, a3, a4) trace_ConnectionInFindRequest_Found_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_ConnectionInFindRequest_Found(a0, a1, a2, a3, a4) trace_ConnectionInFindRequest_Found_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45055, trace_ConnectionInFindRequest_Found_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_FindRequest, Agent %p(%p), Found key: %x, Request: %p(%p)"), void *, Strand *, MI_Uint64, void *, Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionIn_Post(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_Post_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4, a5, a6)
#else
#define trace_ConnectionIn_Post(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_Post_Impl(0, 0, a0, a1, a2, tcs(a3), a4, a5, a6)
#endif
FILE_EVENTD7(45056, trace_ConnectionIn_Post_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_Post: %p Post msg(%p:%d:%T:%x) for interaction [%p]<-%p"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInPost_NewOp(a0, a1, a2) trace_ConnectionInPost_NewOp_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_ConnectionInPost_NewOp(a0, a1, a2) trace_ConnectionInPost_NewOp_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(45057, trace_ConnectionInPost_NewOp_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_Post: New operation with operationId (%p), msg (%p:%T)"), void *, void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionIn_PostCancel(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_PostCancel_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4, a5, a6)
#else
#define trace_ConnectionIn_PostCancel(a0, a1, a2, a3, a4, a5, a6) trace_ConnectionIn_PostCancel_Impl(0, 0, a0, a1, a2, tcs(a3), a4, a5, a6)
#endif
FILE_EVENTD7(45058, trace_ConnectionIn_PostCancel_Impl, LOG_DEBUG, PAL_T("ConnectionIn: %p Post cancel msg(%p:%d:%T:%x) on interaction [%p]<-%p"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextAuxPostLeft(a0, a1) trace_ContextAuxPostLeft_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ContextAuxPostLeft(a0, a1) trace_ContextAuxPostLeft_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45059, trace_ContextAuxPostLeft_Impl, LOG_DEBUG, PAL_T("_Context_Aux_PostLeft: %p, thisAckPending: %d"), Strand *, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextAuxPostLeftNotify(a0) trace_ContextAuxPostLeftNotify_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ContextAuxPostLeftNotify(a0) trace_ContextAuxPostLeftNotify_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45060, trace_ContextAuxPostLeftNotify_Impl, LOG_DEBUG, PAL_T("_Context_Aux_PostLeft_Notify: %p"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextAuxPostLeftNotify_IoThread(a0) trace_ContextAuxPostLeftNotify_IoThread_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ContextAuxPostLeftNotify_IoThread(a0) trace_ContextAuxPostLeftNotify_IoThread_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45061, trace_ContextAuxPostLeftNotify_IoThread_Impl, LOG_DEBUG, PAL_T("_Context_Aux_PostLeft_Notify(IoThread): %p"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define Context_PostMessageLeft_IoThread(a0) Context_PostMessageLeft_IoThread_Impl(__FILE__, __LINE__, a0)
#else
#define Context_PostMessageLeft_IoThread(a0) Context_PostMessageLeft_IoThread_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45062, Context_PostMessageLeft_IoThread_Impl, LOG_DEBUG, PAL_T("Context_PostMessageLeft_IoThread: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_Enter(a0, a1, a2) trace_SelectorRun_Enter_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SelectorRun_Enter(a0, a1, a2) trace_SelectorRun_Enter_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45063, trace_SelectorRun_Enter_Impl, LOG_DEBUG, PAL_T("SelectorRun(Enter): %p"), void *, MI_Uint64, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_Exit(a0) trace_SelectorRun_Exit_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SelectorRun_Exit(a0) trace_SelectorRun_Exit_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45064, trace_SelectorRun_Exit_Impl, LOG_DEBUG, PAL_T("SelectorRun(Exit): %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SelectorRun_Exit_Timeout(a0) trace_SelectorRun_Exit_Timeout_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SelectorRun_Exit_Timeout(a0) trace_SelectorRun_Exit_Timeout_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45065, trace_SelectorRun_Exit_Timeout_Impl, LOG_DEBUG, PAL_T("SelectorRun(Exit-Timeout): %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextCancel(a0) trace_ContextCancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ContextCancel(a0) trace_ContextCancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45066, trace_ContextCancel_Impl, LOG_DEBUG, PAL_T("_Context_Cancel: self (%p)"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextClose(a0, a1, a2) trace_ContextClose_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ContextClose(a0, a1, a2) trace_ContextClose_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45067, trace_ContextClose_Impl, LOG_DEBUG, PAL_T("_Context_Close: Close on context %p, interaction %p->[%p]"), Strand *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextFinish(a0) trace_ContextFinish_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ContextFinish(a0) trace_ContextFinish_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45068, trace_ContextFinish_Impl, LOG_DEBUG, PAL_T("Context: %p, finish called"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextAck(a0, a1, a2, a3, a4, a5) trace_ContextAck_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4, a5)
#else
#define trace_ContextAck(a0, a1, a2, a3, a4, a5) trace_ContextAck_Impl(0, 0, a0, a1, a2, a3, a4, a5)
#endif
FILE_EVENTD6(45069, trace_ContextAck_Impl, LOG_DEBUG, PAL_T("Context: Ack on context %p, interaction %p->[%p], (Transport Closed: ByThis: %d, ByOther: %d), tryingToPostLeft: %x"), Strand *, Interaction *, Interaction *, MI_Boolean, MI_Boolean, ptrdiff_t)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextDestroy(a0, a1, a2) trace_ContextDestroy_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ContextDestroy(a0, a1, a2) trace_ContextDestroy_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45070, trace_ContextDestroy_Impl, LOG_DEBUG, PAL_T("Context: Destroy %p (strand: %p, interaction [%p])"), void *, Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ContextNew(a0, a1, a2) trace_ContextNew_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ContextNew(a0, a1, a2) trace_ContextNew_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45071, trace_ContextNew_Impl, LOG_DEBUG, PAL_T("Context: New context %p with interaction: %p->[%p]"), void *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OperationOut_Ack(a0, a1) trace_OperationOut_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_OperationOut_Ack(a0, a1) trace_OperationOut_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45072, trace_OperationOut_Ack_Impl, LOG_DEBUG, PAL_T("OperationOut: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OperationOut_Cancel(a0) trace_OperationOut_Cancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_OperationOut_Cancel(a0) trace_OperationOut_Cancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45073, trace_OperationOut_Cancel_Impl, LOG_DEBUG, PAL_T("_OperationOut_Cancel: on OperationOut (%p))"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OperationOut_Close(a0, a1) trace_OperationOut_Close_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_OperationOut_Close(a0, a1) trace_OperationOut_Close_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45074, trace_OperationOut_Close_Impl, LOG_DEBUG, PAL_T("OperationOut: Close on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_OperationIn_Ack(a0, a1) trace_OperationIn_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_OperationIn_Ack(a0, a1) trace_OperationIn_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45075, trace_OperationIn_Ack_Impl, LOG_DEBUG, PAL_T("ConnectionIn: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispEnumDone(a0, a1, a2) trace_DispEnumDone_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_DispEnumDone(a0, a1, a2) trace_DispEnumDone_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45076, trace_DispEnumDone_Impl, LOG_DEBUG, PAL_T("Disp EnumDone (%p) total: %d Result: %d"), void *, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DispEntryDeleted(a0, a1, a2) trace_DispEntryDeleted_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_DispEntryDeleted(a0, a1, a2) trace_DispEntryDeleted_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45077, trace_DispEntryDeleted_Impl, LOG_DEBUG, PAL_T("Disp EntryDeleted total: %d Done %d"), void *, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_SetLastError(a0, a1, a2) trace_IndiMgr_SetLastError_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_IndiMgr_SetLastError(a0, a1, a2) trace_IndiMgr_SetLastError_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45078, trace_IndiMgr_SetLastError_Impl, LOG_DEBUG, PAL_T("_IndiMgr_SetLastError: self (%p) result(%d), error(%p)"), void *, MI_Result, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_New(a0) trace_IndiMgr_New_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_New(a0) trace_IndiMgr_New_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45079, trace_IndiMgr_New_Impl, LOG_DEBUG, PAL_T("IndiMgr_New: created IndicationManager (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_Delete(a0) trace_IndiMgr_Delete_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_Delete(a0) trace_IndiMgr_Delete_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45080, trace_IndiMgr_Delete_Impl, LOG_DEBUG, PAL_T("IndiMgr_Delete: self (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_Shutdown(a0) trace_IndiMgr_Shutdown_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_Shutdown(a0) trace_IndiMgr_Shutdown_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45081, trace_IndiMgr_Shutdown_Impl, LOG_DEBUG, PAL_T("IndiMgr_Shutdown: self (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_AddFilter(a0, a1) trace_IndiMgr_AddFilter_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_AddFilter(a0, a1) trace_IndiMgr_AddFilter_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45082, trace_IndiMgr_AddFilter_Impl, LOG_DEBUG, PAL_T("IndiMgr_AddFilter: self (%p), filter (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_RemoveFilter(a0, a1) trace_IndiMgr_RemoveFilter_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_RemoveFilter(a0, a1) trace_IndiMgr_RemoveFilter_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45083, trace_IndiMgr_RemoveFilter_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveFilter: self (%p), filter (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_FilterNotRemoved(a0, a1) trace_IndiMgr_FilterNotRemoved_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_FilterNotRemoved(a0, a1) trace_IndiMgr_FilterNotRemoved_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45084, trace_IndiMgr_FilterNotRemoved_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveFilter: Filter (%p) was not removed from IndicationManager (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_AddListener(a0, a1) trace_IndiMgr_AddListener_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_AddListener(a0, a1) trace_IndiMgr_AddListener_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45085, trace_IndiMgr_AddListener_Impl, LOG_DEBUG, PAL_T("IndiMgr_AddListener: self (%p), listener (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_RemoveListener(a0, a1) trace_IndiMgr_RemoveListener_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_RemoveListener(a0, a1) trace_IndiMgr_RemoveListener_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45086, trace_IndiMgr_RemoveListener_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveListener: self (%p), listener (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_ListenerNotRemoved(a0, a1) trace_IndiMgr_ListenerNotRemoved_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_ListenerNotRemoved(a0, a1) trace_IndiMgr_ListenerNotRemoved_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45087, trace_IndiMgr_ListenerNotRemoved_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveListener: Listener (%p) was not removed from IndicationManager (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_AddSubscription(a0, a1) trace_IndiMgr_AddSubscription_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_AddSubscription(a0, a1) trace_IndiMgr_AddSubscription_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45088, trace_IndiMgr_AddSubscription_Impl, LOG_DEBUG, PAL_T("IndiMgr_AddSubscription: self (%p), subscrip (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_RemoveSubscription(a0, a1) trace_IndiMgr_RemoveSubscription_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_RemoveSubscription(a0, a1) trace_IndiMgr_RemoveSubscription_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45089, trace_IndiMgr_RemoveSubscription_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveSubscription: self (%p), subscrip (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_SubscriptionNotRemoved(a0, a1) trace_IndiMgr_SubscriptionNotRemoved_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_SubscriptionNotRemoved(a0, a1) trace_IndiMgr_SubscriptionNotRemoved_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45090, trace_IndiMgr_SubscriptionNotRemoved_Impl, LOG_DEBUG, PAL_T("IndiMgr_RemoveSubscription: Subscription (%p) was not removed from IndicationManager (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_ObjectExists(a0) trace_IndiMgr_ObjectExists_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_IndiMgr_ObjectExists(a0) trace_IndiMgr_ObjectExists_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45091, trace_IndiMgr_ObjectExists_Impl, LOG_DEBUG, PAL_T("Object %T already exists."), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_CannotFindObject(a0) trace_IndiMgr_CannotFindObject_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_IndiMgr_CannotFindObject(a0) trace_IndiMgr_CannotFindObject_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45092, trace_IndiMgr_CannotFindObject_Impl, LOG_DEBUG, PAL_T("_List_RemoveObjectByID: Cannot find object (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_PostComplete(a0, a1, a2, a3, a4) trace_SubElem_PostComplete_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_SubElem_PostComplete(a0, a1, a2, a3, a4) trace_SubElem_PostComplete_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45093, trace_SubElem_PostComplete_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Post: self (%p), msg(%p:%d:%T:%x) complete"), StrandMany *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_PostCancelSubscribe(a0, a1, a2, a3, a4) trace_SubElem_PostCancelSubscribe_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_SubElem_PostCancelSubscribe(a0, a1, a2, a3, a4) trace_SubElem_PostCancelSubscribe_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45094, trace_SubElem_PostCancelSubscribe_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Post: self (%p), msg(%p:%d:%T:%x), cancel all SubscribeEntries"), StrandMany *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_Post(a0, a1, a2, a3, a4) trace_SubElem_Post_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_SubElem_Post(a0, a1, a2, a3, a4) trace_SubElem_Post_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45095, trace_SubElem_Post_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Post: self (%p), unsupported msg(%p:%d:%T:%x)"), StrandMany *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_Ack(a0, a1, a2) trace_SubElem_Ack_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubElem_Ack(a0, a1, a2) trace_SubElem_Ack_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45096, trace_SubElem_Ack_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Ack: self (%p) interaction [%p]<-%p"), Strand *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_Cancel(a0, a1, a2) trace_SubElem_Cancel_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubElem_Cancel(a0, a1, a2) trace_SubElem_Cancel_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45097, trace_SubElem_Cancel_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Cancel: self (%p) interaction [%p]<-%p"), StrandMany *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_Finish(a0, a1, a2) trace_SubElem_Finish_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubElem_Finish(a0, a1, a2) trace_SubElem_Finish_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45098, trace_SubElem_Finish_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Finish: self (%p) interaction [%p]<-%p"), void *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_CheckSendFinalResult(a0) trace_SubElem_CheckSendFinalResult_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubElem_CheckSendFinalResult(a0) trace_SubElem_CheckSendFinalResult_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45099, trace_SubElem_CheckSendFinalResult_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_CheckSendFinalResult: self(%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_CheckSendComplete(a0, a1, a2) trace_SubElem_CheckSendComplete_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_SubElem_CheckSendComplete(a0, a1, a2) trace_SubElem_CheckSendComplete_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45100, trace_SubElem_CheckSendComplete_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_CheckSendFinalResult: self (%p) status (%T); (%d) classes was handled; send final result message to protocol and closed self"), void *, const TChar *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_NewEntry(a0, a1, a2, a3, a4, a5) trace_SubElem_NewEntry_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4), a5)
#else
#define trace_SubElem_NewEntry(a0, a1, a2, a3, a4, a5) trace_SubElem_NewEntry_Impl(0, 0, a0, a1, a2, a3, tcs(a4), a5)
#endif
FILE_EVENTD6(45101, trace_SubElem_NewEntry_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_NewEntry: self(%p) newEntry(%p) msg(%p:%d:%T:%x)"), StrandMany *, StrandEntry *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_NewEntry_UnexpectedMessage(a0, a1, a2, a3) trace_SubElem_NewEntry_UnexpectedMessage_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_SubElem_NewEntry_UnexpectedMessage(a0, a1, a2, a3) trace_SubElem_NewEntry_UnexpectedMessage_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(45102, trace_SubElem_NewEntry_UnexpectedMessage_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_NewEntry: Unexpected msg(%p:%x:%T:%x)"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubItem_HandleRequest(a0, a1, a2) trace_SubItem_HandleRequest_Impl(__FILE__, __LINE__, a0, tcs(a1), tcs(a2))
#else
#define trace_SubItem_HandleRequest(a0, a1, a2) trace_SubItem_HandleRequest_Impl(0, 0, a0, tcs(a1), tcs(a2))
#endif
FILE_EVENTD3(45103, trace_SubItem_HandleRequest_Impl, LOG_DEBUG, PAL_T("_SubscribeItem_Added: self(%p) handle request namespace(%T), class(%T)"), void *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElement_NewDone(a0, a1, a2, a3, a4, a5, a6, a7) trace_SubElement_NewDone_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4, a5, a6, a7)
#else
#define trace_SubElement_NewDone(a0, a1, a2, a3, a4, a5, a6, a7) trace_SubElement_NewDone_Impl(0, 0, a0, a1, a2, a3, a4, a5, a6, a7)
#endif
FILE_EVENTD8(45104, trace_SubElement_NewDone_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_NewEntry: DONE. self(%p); Classes: (%d)Scheduled; (%d)Sent; (%d)Handled (%d)Subscribed (%d)Failed (%d)Complete; Aggregate result (%d)"), StrandMany *, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_EntryPost(a0, a1, a2, a3, a4, a5) trace_SubElem_EntryPost_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4), a5)
#else
#define trace_SubElem_EntryPost(a0, a1, a2, a3, a4, a5) trace_SubElem_EntryPost_Impl(0, 0, a0, a1, a2, a3, tcs(a4), a5)
#endif
FILE_EVENTD6(45105, trace_SubElem_EntryPost_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_EntryPost: Posting message for interaction [%p]<-%p; msg(%p:%d:%T:%x)"), Interaction *, Interaction *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_PostSendSuccessResponse(a0, a1) trace_SubElem_PostSendSuccessResponse_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_SubElem_PostSendSuccessResponse(a0, a1) trace_SubElem_PostSendSuccessResponse_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45106, trace_SubElem_PostSendSuccessResponse_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_EntryPost: self (%p) status (%T); send success response to protocol"), void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_EntryPost_PassToLeft(a0, a1, a2, a3, a4) trace_SubElem_EntryPost_PassToLeft_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_SubElem_EntryPost_PassToLeft(a0, a1, a2, a3, a4) trace_SubElem_EntryPost_PassToLeft_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45107, trace_SubElem_EntryPost_PassToLeft_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_EntryPost: Self (%p) received msg(%p:%d:%T:%x), pass to left"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_EntryPostDone(a0, a1, a2, a3, a4, a5, a6, a7) trace_SubElem_EntryPostDone_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4, a5, a6, a7)
#else
#define trace_SubElem_EntryPostDone(a0, a1, a2, a3, a4, a5, a6, a7) trace_SubElem_EntryPostDone_Impl(0, 0, a0, a1, a2, a3, a4, a5, a6, a7)
#endif
FILE_EVENTD8(45108, trace_SubElem_EntryPostDone_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_EntryPost: DONE. self(%p); Classes: (%d)Scheduled; (%d)Sent; (%d)Handled (%d)Subscribed (%d)Failed (%d)Complete; Aggregate result (%d)"), void *, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubElem_EntryClose() trace_SubElem_EntryClose_Impl(__FILE__, __LINE__)
#else
#define trace_SubElem_EntryClose() trace_SubElem_EntryClose_Impl(0, 0)
#endif
FILE_EVENTD0(45109, trace_SubElem_EntryClose_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_EntryClose: Done"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe(a0, a1, a2, a3) trace_IndiMgr_HandleSubscribe_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_IndiMgr_HandleSubscribe(a0, a1, a2, a3) trace_IndiMgr_HandleSubscribe_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45110, trace_IndiMgr_HandleSubscribe_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: self (%p) interaction (%p) req (%p : OPID=%x)"), void *, Interaction *, void *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_InvalidParameters() trace_IndiMgr_HandleSubscribe_InvalidParameters_Impl(__FILE__, __LINE__)
#else
#define trace_IndiMgr_HandleSubscribe_InvalidParameters() trace_IndiMgr_HandleSubscribe_InvalidParameters_Impl(0, 0)
#endif
FILE_EVENTD0(45111, trace_IndiMgr_HandleSubscribe_InvalidParameters_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: invalid parameter(s)"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_FailedToSetNamespace(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToSetNamespace_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_HandleSubscribe_FailedToSetNamespace(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToSetNamespace_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45112, trace_IndiMgr_HandleSubscribe_FailedToSetNamespace_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: Failed to set namespace to filter (%p), req (%p)."), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_FailedToAddSub(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToAddSub_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_HandleSubscribe_FailedToAddSub(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToAddSub_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45113, trace_IndiMgr_HandleSubscribe_FailedToAddSub_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: Failed to add subscription (%p), req (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_NoClassFound(a0) trace_IndiMgr_HandleSubscribe_NoClassFound_Impl(__FILE__, __LINE__, a0)
#else
#define trace_IndiMgr_HandleSubscribe_NoClassFound(a0) trace_IndiMgr_HandleSubscribe_NoClassFound_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45114, trace_IndiMgr_HandleSubscribe_NoClassFound_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: No class found, req(%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_FailedToCreateMessage(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToCreateMessage_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_IndiMgr_HandleSubscribe_FailedToCreateMessage(a0, a1) trace_IndiMgr_HandleSubscribe_FailedToCreateMessage_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45115, trace_IndiMgr_HandleSubscribe_FailedToCreateMessage_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: Failed to create subscribereq message for class %T, req (%p)"), const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_BeginAddingEntry(a0, a1, a2, a3) trace_IndiMgr_HandleSubscribe_BeginAddingEntry_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_IndiMgr_HandleSubscribe_BeginAddingEntry(a0, a1, a2, a3) trace_IndiMgr_HandleSubscribe_BeginAddingEntry_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(45116, trace_IndiMgr_HandleSubscribe_BeginAddingEntry_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: begin to add entry (%p) msg (%p:%T), req(%p)"), void *, Message *, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_AddingEntryDone(a0, a1) trace_IndiMgr_HandleSubscribe_AddingEntryDone_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_IndiMgr_HandleSubscribe_AddingEntryDone(a0, a1) trace_IndiMgr_HandleSubscribe_AddingEntryDone_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45117, trace_IndiMgr_HandleSubscribe_AddingEntryDone_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: end add entry (%p), req (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_IndiMgr_HandleSubscribe_Done(a0, a1, a2, a3, a4) trace_IndiMgr_HandleSubscribe_Done_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_IndiMgr_HandleSubscribe_Done(a0, a1, a2, a3, a4) trace_IndiMgr_HandleSubscribe_Done_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45118, trace_IndiMgr_HandleSubscribe_Done_Impl, LOG_DEBUG, PAL_T("IndiMgr_HandleSubscribeReq: self (%p) interaction (%p) req (%p : OPID=%x); done result (%d)"), void *, Interaction *, void *, MI_Uint64, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_Finalize(a0) trace_Subscription_Finalize_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Subscription_Finalize(a0) trace_Subscription_Finalize_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45119, trace_Subscription_Finalize_Impl, LOG_DEBUG, PAL_T("Subscription_Finalize: self(%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd(a0, a1) trace_Subscription_OnAdd_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Subscription_OnAdd(a0, a1) trace_Subscription_OnAdd_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45120, trace_Subscription_OnAdd_Impl, LOG_DEBUG, PAL_T("Subscription_OnAdd: self(%p), container (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_Failed() trace_Subscription_OnAdd_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_Subscription_OnAdd_Failed() trace_Subscription_OnAdd_Failed_Impl(0, 0)
#endif
FILE_EVENTD0(45121, trace_Subscription_OnAdd_Failed_Impl, LOG_DEBUG, PAL_T("Subscription_OnAdd: Failed to create class list"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnAdd_Success(a0, a1) trace_Subscription_OnAdd_Success_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Subscription_OnAdd_Success(a0, a1) trace_Subscription_OnAdd_Success_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45122, trace_Subscription_OnAdd_Success_Impl, LOG_DEBUG, PAL_T("Subscription_OnAdd: self(%p), container (%p) succeed"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnRemove(a0, a1) trace_Subscription_OnRemove_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Subscription_OnRemove(a0, a1) trace_Subscription_OnRemove_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45123, trace_Subscription_OnRemove_Impl, LOG_DEBUG, PAL_T("Subscription_OnRemove: self(%p), container (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_OnRemove_Result(a0, a1, a2) trace_Subscription_OnRemove_Result_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_Subscription_OnRemove_Result(a0, a1, a2) trace_Subscription_OnRemove_Result_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45124, trace_Subscription_OnRemove_Result_Impl, LOG_DEBUG, PAL_T("Subscription_OnRemove: self(%p), container (%p), result (%d)"), void *, void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Client_Ack_Post(a0) trace_InteractionProtocolHandler_Client_Ack_Post_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Client_Ack_Post(a0) trace_InteractionProtocolHandler_Client_Ack_Post_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45125, trace_InteractionProtocolHandler_Client_Ack_Post_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Client_Ack_PostToInteraction %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Client_Ack_NoPost(a0) trace_InteractionProtocolHandler_Client_Ack_NoPost_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Client_Ack_NoPost(a0) trace_InteractionProtocolHandler_Client_Ack_NoPost_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45126, trace_InteractionProtocolHandler_Client_Ack_NoPost_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Client_Ack_NoPostToInteraction %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_StrandPost(a0, a1, a2, a3, a4) trace_InteractionProtocolHandler_Operation_StrandPost_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_InteractionProtocolHandler_Operation_StrandPost(a0, a1, a2, a3, a4) trace_InteractionProtocolHandler_Operation_StrandPost_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45127, trace_InteractionProtocolHandler_Operation_StrandPost_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Post: %p, msg(%p:%d:%T:%x)"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIResult(a0) trace_MIResult_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_MIResult(a0) trace_MIResult_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45128, trace_MIResult_Impl, LOG_DEBUG, PAL_T("MI_Result = %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_NoopRspTag() trace_InteractionProtocolHandler_NoopRspTag_Impl(__FILE__, __LINE__)
#else
#define trace_InteractionProtocolHandler_NoopRspTag() trace_InteractionProtocolHandler_NoopRspTag_Impl(0, 0)
#endif
FILE_EVENTD0(45129, trace_InteractionProtocolHandler_NoopRspTag_Impl, LOG_DEBUG, PAL_T("NoOpRspTag"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_PostControl(a0) trace_InteractionProtocolHandler_Operation_Strand_PostControl_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_PostControl(a0) trace_InteractionProtocolHandler_Operation_Strand_PostControl_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45130, trace_InteractionProtocolHandler_Operation_Strand_PostControl_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_PostControl %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Session_ProtocolConnecting() trace_InteractionProtocolHandler_Session_ProtocolConnecting_Impl(__FILE__, __LINE__)
#else
#define trace_InteractionProtocolHandler_Session_ProtocolConnecting() trace_InteractionProtocolHandler_Session_ProtocolConnecting_Impl(0, 0)
#endif
FILE_EVENTD0(45131, trace_InteractionProtocolHandler_Session_ProtocolConnecting_Impl, LOG_DEBUG, PAL_T("==== InteractionProtocolHandler_Session_ConnectionEvents() PROTOCOLEVENT_CONNECT"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Session_ConnectFailed() trace_InteractionProtocolHandler_Session_ConnectFailed_Impl(__FILE__, __LINE__)
#else
#define trace_InteractionProtocolHandler_Session_ConnectFailed() trace_InteractionProtocolHandler_Session_ConnectFailed_Impl(0, 0)
#endif
FILE_EVENTD0(45132, trace_InteractionProtocolHandler_Session_ConnectFailed_Impl, LOG_DEBUG, PAL_T("==== InteractionProtocolHandler_Session_ConnectionEvents() PROTOCOLEVENT_CONNECT_FAILED"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_Ack(a0) trace_InteractionProtocolHandler_Operation_Strand_Ack_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_Ack(a0) trace_InteractionProtocolHandler_Operation_Strand_Ack_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45133, trace_InteractionProtocolHandler_Operation_Strand_Ack_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Ack %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_Cancel(a0) trace_InteractionProtocolHandler_Operation_Strand_Cancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_Cancel(a0) trace_InteractionProtocolHandler_Operation_Strand_Cancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45134, trace_InteractionProtocolHandler_Operation_Strand_Cancel_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Cancel %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_Close(a0) trace_InteractionProtocolHandler_Operation_Strand_Close_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_Close(a0) trace_InteractionProtocolHandler_Operation_Strand_Close_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45135, trace_InteractionProtocolHandler_Operation_Strand_Close_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Close %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_Finish(a0) trace_InteractionProtocolHandler_Operation_Strand_Finish_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_Finish(a0) trace_InteractionProtocolHandler_Operation_Strand_Finish_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45136, trace_InteractionProtocolHandler_Operation_Strand_Finish_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Finish %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Close(a0) trace_InteractionProtocolHandler_Operation_Close_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Close(a0) trace_InteractionProtocolHandler_Operation_Close_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45137, trace_InteractionProtocolHandler_Operation_Close_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Close %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Cancel(a0) trace_InteractionProtocolHandler_Operation_Cancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Cancel(a0) trace_InteractionProtocolHandler_Operation_Cancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45138, trace_InteractionProtocolHandler_Operation_Cancel_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Cancel %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_CancelAfterFinal(a0) trace_InteractionProtocolHandler_Operation_CancelAfterFinal_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_CancelAfterFinal(a0) trace_InteractionProtocolHandler_Operation_CancelAfterFinal_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45139, trace_InteractionProtocolHandler_Operation_CancelAfterFinal_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Cancel %p -- ignoring because we have already posted the final result"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Session_Close(a0, a1) trace_InteractionProtocolHandler_Session_Close_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_InteractionProtocolHandler_Session_Close(a0, a1) trace_InteractionProtocolHandler_Session_Close_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45140, trace_InteractionProtocolHandler_Session_Close_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Session_Close %p (CompletionCallback %p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Protocol_RunThread() trace_InteractionProtocolHandler_Protocol_RunThread_Impl(__FILE__, __LINE__)
#else
#define trace_InteractionProtocolHandler_Protocol_RunThread() trace_InteractionProtocolHandler_Protocol_RunThread_Impl(0, 0)
#endif
FILE_EVENTD0(45141, trace_InteractionProtocolHandler_Protocol_RunThread_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Protocol_RunThread"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Protocol_RunThread_WithResult(a0) trace_InteractionProtocolHandler_Protocol_RunThread_WithResult_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Protocol_RunThread_WithResult(a0) trace_InteractionProtocolHandler_Protocol_RunThread_WithResult_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45142, trace_InteractionProtocolHandler_Protocol_RunThread_WithResult_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Protocol_RunThread finished with return %u"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SessionCloseCompletion_Release_CompletionCallback(a0, a1) trace_SessionCloseCompletion_Release_CompletionCallback_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SessionCloseCompletion_Release_CompletionCallback(a0, a1) trace_SessionCloseCompletion_Release_CompletionCallback_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45143, trace_SessionCloseCompletion_Release_CompletionCallback_Impl, LOG_DEBUG, PAL_T("SessionCloseCompletion_Release %p with CompletionCallback %p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SessionCloseCompletion_Release_Count(a0, a1) trace_SessionCloseCompletion_Release_Count_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SessionCloseCompletion_Release_Count(a0, a1) trace_SessionCloseCompletion_Release_Count_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45144, trace_SessionCloseCompletion_Release_Count_Impl, LOG_DEBUG, PAL_T("SessionCloseCompletion_Release %p count is %d"), void *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_SessionConnect_Passed() trace_InteractionProtocolHandler_SessionConnect_Passed_Impl(__FILE__, __LINE__)
#else
#define trace_InteractionProtocolHandler_SessionConnect_Passed() trace_InteractionProtocolHandler_SessionConnect_Passed_Impl(0, 0)
#endif
FILE_EVENTD0(45145, trace_InteractionProtocolHandler_SessionConnect_Passed_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Session_Connect passed !"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_TimeoutTrigger(a0) trace_ProtocolSocket_TimeoutTrigger_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProtocolSocket_TimeoutTrigger(a0) trace_ProtocolSocket_TimeoutTrigger_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45146, trace_ProtocolSocket_TimeoutTrigger_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: triggering timeout on %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_PostingOnInteraction(a0, a1) trace_ProtocolSocket_PostingOnInteraction_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ProtocolSocket_PostingOnInteraction(a0, a1) trace_ProtocolSocket_PostingOnInteraction_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45147, trace_ProtocolSocket_PostingOnInteraction_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: Posting message for interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_PostFailed(a0, a1) trace_ProtocolSocket_PostFailed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ProtocolSocket_PostFailed(a0, a1) trace_ProtocolSocket_PostFailed_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45148, trace_ProtocolSocket_PostFailed_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: Post for interaction [%p]<-%p FAILED"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_CancelReceived(a0, a1, a2) trace_ProtocolSocket_CancelReceived_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ProtocolSocket_CancelReceived(a0, a1, a2) trace_ProtocolSocket_CancelReceived_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45149, trace_ProtocolSocket_CancelReceived_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: Cancel received (closed other: %d) on interaction [%p]<-%p"), MI_Boolean, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_Ack(a0, a1) trace_ProtocolSocket_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ProtocolSocket_Ack(a0, a1) trace_ProtocolSocket_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45150, trace_ProtocolSocket_Ack_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: Ack on interaction [%p]<-%p"), Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_Close(a0, a1, a2) trace_ProtocolSocket_Close_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ProtocolSocket_Close(a0, a1, a2) trace_ProtocolSocket_Close_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45151, trace_ProtocolSocket_Close_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: Close received (closed other: %d) on interaction [%p]<-%p"), MI_Boolean, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_Finish(a0) trace_ProtocolSocket_Finish_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProtocolSocket_Finish(a0) trace_ProtocolSocket_Finish_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45152, trace_ProtocolSocket_Finish_Impl, LOG_DEBUG, PAL_T("ProtocolSocket: %p _ProtocolSocket_Finish"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SocketSendCompleted(a0) trace_SocketSendCompleted_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SocketSendCompleted(a0) trace_SocketSendCompleted_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45153, trace_SocketSendCompleted_Impl, LOG_DEBUG, PAL_T("Socket: %p, All send"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallbackRead_Failed(a0) trace_RequestCallbackRead_Failed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestCallbackRead_Failed(a0) trace_RequestCallbackRead_Failed_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45154, trace_RequestCallbackRead_Failed_Impl, LOG_DEBUG, PAL_T("Protocol _RequestCallback: _RequestCallbackRead fails for ProtocolSocket %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallback_Connect_OnFirstRead(a0) trace_RequestCallback_Connect_OnFirstRead_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestCallback_Connect_OnFirstRead(a0) trace_RequestCallback_Connect_OnFirstRead_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45155, trace_RequestCallback_Connect_OnFirstRead_Impl, LOG_DEBUG, PAL_T("Protocol _RequestCallback: scheduling connect event on first read for ProtocolSocket %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallback_Connect_OnFirstWrite(a0) trace_RequestCallback_Connect_OnFirstWrite_Impl(__FILE__, __LINE__, a0)
#else
#define trace_RequestCallback_Connect_OnFirstWrite(a0) trace_RequestCallback_Connect_OnFirstWrite_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45156, trace_RequestCallback_Connect_OnFirstWrite_Impl, LOG_DEBUG, PAL_T("Protocol _RequestCallback: scheduling connect event on first write for ProtocolSocket %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallback_Connect_ClosingAfterMask(a0, a1) trace_RequestCallback_Connect_ClosingAfterMask_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_RequestCallback_Connect_ClosingAfterMask(a0, a1) trace_RequestCallback_Connect_ClosingAfterMask_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45157, trace_RequestCallback_Connect_ClosingAfterMask_Impl, LOG_DEBUG, PAL_T("Protocol _RequestCallback: closing %p after mask %x"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RequestCallback_Connect_RemovingHandler(a0, a1, a2) trace_RequestCallback_Connect_RemovingHandler_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_RequestCallback_Connect_RemovingHandler(a0, a1, a2) trace_RequestCallback_Connect_RemovingHandler_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45158, trace_RequestCallback_Connect_RemovingHandler_Impl, LOG_DEBUG, PAL_T("Protocol _RequestCallback: removing %p (mask %x, prev: %x)"), void *, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_PostResult(a0) trace_Provider_PostResult_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Provider_PostResult(a0) trace_Provider_PostResult_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45159, trace_Provider_PostResult_Impl, LOG_DEBUG, PAL_T("post result from provider, %d"), MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EvaluateIndicationWithNull() trace_EvaluateIndicationWithNull_Impl(__FILE__, __LINE__)
#else
#define trace_EvaluateIndicationWithNull() trace_EvaluateIndicationWithNull_Impl(0, 0)
#endif
FILE_EVENTD0(45160, trace_EvaluateIndicationWithNull_Impl, LOG_DEBUG, PAL_T("EvaluateIndication with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PostIndicationWithUnsubscribedContext() trace_PostIndicationWithUnsubscribedContext_Impl(__FILE__, __LINE__)
#else
#define trace_PostIndicationWithUnsubscribedContext() trace_PostIndicationWithUnsubscribedContext_Impl(0, 0)
#endif
FILE_EVENTD0(45161, trace_PostIndicationWithUnsubscribedContext_Impl, LOG_DEBUG, PAL_T("PostIndication with unsubscribed context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TerminateWithNullProvider() trace_TerminateWithNullProvider_Impl(__FILE__, __LINE__)
#else
#define trace_TerminateWithNullProvider() trace_TerminateWithNullProvider_Impl(0, 0)
#endif
FILE_EVENTD0(45162, trace_TerminateWithNullProvider_Impl, LOG_DEBUG, PAL_T("Terminate with NULL provider"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_ProviderPostingFailure(a0, a1, a2) trace_SubscrContext_ProviderPostingFailure_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_SubscrContext_ProviderPostingFailure(a0, a1, a2) trace_SubscrContext_ProviderPostingFailure_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45163, trace_SubscrContext_ProviderPostingFailure_Impl, LOG_DEBUG, PAL_T("_SubscrContext_ProcessResult: Provider posted failure result (%d) while %T subscription (%p). Send final result"), MI_Result, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PostIndicationWithNullInput() trace_PostIndicationWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_PostIndicationWithNullInput() trace_PostIndicationWithNullInput_Impl(0, 0)
#endif
FILE_EVENTD0(45164, trace_PostIndicationWithNullInput_Impl, LOG_DEBUG, PAL_T("PostIndication with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PostIndicationOnDisabledAggContext() trace_PostIndicationOnDisabledAggContext_Impl(__FILE__, __LINE__)
#else
#define trace_PostIndicationOnDisabledAggContext() trace_PostIndicationOnDisabledAggContext_Impl(0, 0)
#endif
FILE_EVENTD0(45165, trace_PostIndicationOnDisabledAggContext_Impl, LOG_DEBUG, PAL_T("PostIndication on disabled aggregation context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_PostCalledWithInvalidContext() trace_PostCalledWithInvalidContext_Impl(__FILE__, __LINE__)
#else
#define trace_PostCalledWithInvalidContext() trace_PostCalledWithInvalidContext_Impl(0, 0)
#endif
FILE_EVENTD0(45166, trace_PostCalledWithInvalidContext_Impl, LOG_DEBUG, PAL_T("Post called with invalid context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnknownIndicationContextType(a0) trace_UnknownIndicationContextType_Impl(__FILE__, __LINE__, a0)
#else
#define trace_UnknownIndicationContextType(a0) trace_UnknownIndicationContextType_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45167, trace_UnknownIndicationContextType_Impl, LOG_DEBUG, PAL_T("Unknown indication context type %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeContext_Cancel(a0) trace_SubscribeContext_Cancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubscribeContext_Cancel(a0) trace_SubscribeContext_Cancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45168, trace_SubscribeContext_Cancel_Impl, LOG_DEBUG, PAL_T("_SubscribeContext_Cancel: self (%p);"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeContext_CancelDone(a0) trace_SubscribeContext_CancelDone_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubscribeContext_CancelDone(a0) trace_SubscribeContext_CancelDone_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45169, trace_SubscribeContext_CancelDone_Impl, LOG_DEBUG, PAL_T("_SubscribeContext_Cancel: unsubscribe self (%p) done"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CreateFilterWithNullInput() trace_CreateFilterWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_CreateFilterWithNullInput() trace_CreateFilterWithNullInput_Impl(0, 0)
#endif
FILE_EVENTD0(45170, trace_CreateFilterWithNullInput_Impl, LOG_DEBUG, PAL_T("Create filter with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EvaluateWQLWithNullInput() trace_EvaluateWQLWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_EvaluateWQLWithNullInput() trace_EvaluateWQLWithNullInput_Impl(0, 0)
#endif
FILE_EVENTD0(45171, trace_EvaluateWQLWithNullInput_Impl, LOG_DEBUG, PAL_T("Evaluate WQL with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetProviderByClassName(a0) trace_GetProviderByClassName_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_GetProviderByClassName(a0) trace_GetProviderByClassName_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45172, trace_GetProviderByClassName_Impl, LOG_DEBUG, PAL_T("_GetProviderByClassName{%T}"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InitIndicationWithNullInput() trace_InitIndicationWithNullInput_Impl(__FILE__, __LINE__)
#else
#define trace_InitIndicationWithNullInput() trace_InitIndicationWithNullInput_Impl(0, 0)
#endif
FILE_EVENTD0(45173, trace_InitIndicationWithNullInput_Impl, LOG_DEBUG, PAL_T("InitIndication with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MultipleIndication_InitOfProviderForClass(a0) trace_MultipleIndication_InitOfProviderForClass_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_MultipleIndication_InitOfProviderForClass(a0) trace_MultipleIndication_InitOfProviderForClass_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45174, trace_MultipleIndication_InitOfProviderForClass_Impl, LOG_DEBUG, PAL_T("Multiple indication initialization of provider for class %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProviderInvokeSubscribe_Begin(a0, a1, a2, a3, a4) trace_ProviderInvokeSubscribe_Begin_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_ProviderInvokeSubscribe_Begin(a0, a1, a2, a3, a4) trace_ProviderInvokeSubscribe_Begin_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45175, trace_ProviderInvokeSubscribe_Begin_Impl, LOG_DEBUG, PAL_T("_Provider_InvokeSubscribe: Start  Thread %x: provider (%p), msg (%p) with tag (%d), subcription (%p)"), unsigned int, void *, void *, MI_Uint32, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProviderInvokeSubscribe_End(a0, a1, a2) trace_ProviderInvokeSubscribe_End_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_ProviderInvokeSubscribe_End(a0, a1, a2) trace_ProviderInvokeSubscribe_End_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45176, trace_ProviderInvokeSubscribe_End_Impl, LOG_DEBUG, PAL_T("_Provider_InvokeSubscribe: Complete Thread %x: provider (%p), result (%d)"), unsigned int, void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CannotUnloadNullProvider() trace_CannotUnloadNullProvider_Impl(__FILE__, __LINE__)
#else
#define trace_CannotUnloadNullProvider() trace_CannotUnloadNullProvider_Impl(0, 0)
#endif
FILE_EVENTD0(45177, trace_CannotUnloadNullProvider_Impl, LOG_DEBUG, PAL_T("Cannot unload NULL provider"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_PostingSchemaInWsmanToCallback() trace_ProvMgr_PostingSchemaInWsmanToCallback_Impl(__FILE__, __LINE__)
#else
#define trace_ProvMgr_PostingSchemaInWsmanToCallback() trace_ProvMgr_PostingSchemaInWsmanToCallback_Impl(0, 0)
#endif
FILE_EVENTD0(45178, trace_ProvMgr_PostingSchemaInWsmanToCallback_Impl, LOG_DEBUG, PAL_T("Posting schema in wsman form to callback from provmgr"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_GetClassReq(a0, a1) trace_ProvMgr_GetClassReq_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1))
#else
#define trace_ProvMgr_GetClassReq(a0, a1) trace_ProvMgr_GetClassReq_Impl(0, 0, tcs(a0), tcs(a1))
#endif
FILE_EVENTD2(45179, trace_ProvMgr_GetClassReq_Impl, LOG_DEBUG, PAL_T("GetClassReq for class %T namespace %T came to the provmgr"), const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_ClassNotFound(a0) trace_ProvMgr_ClassNotFound_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_ProvMgr_ClassNotFound(a0) trace_ProvMgr_ClassNotFound_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45180, trace_ProvMgr_ClassNotFound_Impl, LOG_DEBUG, PAL_T("Class not found %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_EnumerateInstancesOfClass(a0) trace_ProvMgr_EnumerateInstancesOfClass_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_ProvMgr_EnumerateInstancesOfClass(a0) trace_ProvMgr_EnumerateInstancesOfClass_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45181, trace_ProvMgr_EnumerateInstancesOfClass_Impl, LOG_DEBUG, PAL_T("enumerate instances of %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_UnloadingProvider(a0) trace_ProvMgr_UnloadingProvider_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_ProvMgr_UnloadingProvider(a0) trace_ProvMgr_UnloadingProvider_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45182, trace_ProvMgr_UnloadingProvider_Impl, LOG_DEBUG, PAL_T("Unloading provider %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_UnloadingLibrary(a0) trace_ProvMgr_UnloadingLibrary_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_ProvMgr_UnloadingLibrary(a0) trace_ProvMgr_UnloadingLibrary_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(45183, trace_ProvMgr_UnloadingLibrary_Impl, LOG_DEBUG, PAL_T("Unloading lib %s"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProvMgr_NewRequest_UnsupportedMessage(a0, a1) trace_ProvMgr_NewRequest_UnsupportedMessage_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_ProvMgr_NewRequest_UnsupportedMessage(a0, a1) trace_ProvMgr_NewRequest_UnsupportedMessage_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45184, trace_ProvMgr_NewRequest_UnsupportedMessage_Impl, LOG_DEBUG, PAL_T("ProvMgr_NewRequest: Unsupported message (%p:%T)"), Message *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_CloseWithExistingSubscriptions() trace_CloseWithExistingSubscriptions_Impl(__FILE__, __LINE__)
#else
#define trace_CloseWithExistingSubscriptions() trace_CloseWithExistingSubscriptions_Impl(0, 0)
#endif
FILE_EVENTD0(45185, trace_CloseWithExistingSubscriptions_Impl, LOG_DEBUG, PAL_T("Close with existing subscriptions"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgr_CancelAllSubscriptions(a0, a1) trace_SubMgr_CancelAllSubscriptions_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubMgr_CancelAllSubscriptions(a0, a1) trace_SubMgr_CancelAllSubscriptions_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45186, trace_SubMgr_CancelAllSubscriptions_Impl, LOG_DEBUG, PAL_T("SubMgr_CancelAllSubscriptions: Thread %x: mgr (%p)"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetSubscription_NoSubscrPresent() trace_GetSubscription_NoSubscrPresent_Impl(__FILE__, __LINE__)
#else
#define trace_GetSubscription_NoSubscrPresent() trace_GetSubscription_NoSubscrPresent_Impl(0, 0)
#endif
FILE_EVENTD0(45187, trace_GetSubscription_NoSubscrPresent_Impl, LOG_DEBUG, PAL_T("No subscriptions present"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AddFilter_NullParameter() trace_AddFilter_NullParameter_Impl(__FILE__, __LINE__)
#else
#define trace_AddFilter_NullParameter() trace_AddFilter_NullParameter_Impl(0, 0)
#endif
FILE_EVENTD0(45188, trace_AddFilter_NullParameter_Impl, LOG_DEBUG, PAL_T("AddFilter with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SendResp_NullParameter() trace_SendResp_NullParameter_Impl(__FILE__, __LINE__)
#else
#define trace_SendResp_NullParameter() trace_SendResp_NullParameter_Impl(0, 0)
#endif
FILE_EVENTD0(45189, trace_SendResp_NullParameter_Impl, LOG_DEBUG, PAL_T("SendResp with NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionContext_NullParameter() trace_SubscriptionContext_NullParameter_Impl(__FILE__, __LINE__)
#else
#define trace_SubscriptionContext_NullParameter() trace_SubscriptionContext_NullParameter_Impl(0, 0)
#endif
FILE_EVENTD0(45190, trace_SubscriptionContext_NullParameter_Impl, LOG_DEBUG, PAL_T("SubscriptionContext init with NULL input"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_SendFinalResultMsg(a0, a1) trace_SubscrContext_SendFinalResultMsg_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscrContext_SendFinalResultMsg(a0, a1) trace_SubscrContext_SendFinalResultMsg_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45191, trace_SubscrContext_SendFinalResultMsg_Impl, LOG_DEBUG, PAL_T("SubscrContext_SendFinalResultMsg: subCtx (%p) result (%d)"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_SendFinalResultMsg_Sent(a0, a1, a2, a3) trace_SubscrContext_SendFinalResultMsg_Sent_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3))
#else
#define trace_SubscrContext_SendFinalResultMsg_Sent(a0, a1, a2, a3) trace_SubscrContext_SendFinalResultMsg_Sent_Impl(0, 0, a0, a1, a2, tcs(a3))
#endif
FILE_EVENTD4(45192, trace_SubscrContext_SendFinalResultMsg_Sent_Impl, LOG_DEBUG, PAL_T("SubscrContext_SendFinalResultMsg: subCtx (%p), result %d, msg(%p:%T) sent"), void *, MI_Result, void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_SendSubscribeResponseMsg(a0) trace_SubscrContext_SendSubscribeResponseMsg_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubscrContext_SendSubscribeResponseMsg(a0) trace_SubscrContext_SendSubscribeResponseMsg_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45193, trace_SubscrContext_SendSubscribeResponseMsg_Impl, LOG_DEBUG, PAL_T("SubscrContext_SendSubscribeResponseMsg: subCtx (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_SendSubscribeResponseMsg_Sent(a0, a1, a2) trace_SubscrContext_SendSubscribeResponseMsg_Sent_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_SubscrContext_SendSubscribeResponseMsg_Sent(a0, a1, a2) trace_SubscrContext_SendSubscribeResponseMsg_Sent_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(45194, trace_SubscrContext_SendSubscribeResponseMsg_Sent_Impl, LOG_DEBUG, PAL_T("SubscrContext_SendSubscribeResponseMsg: subCtx (%p), msg(%p:%T) sent"), void *, void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_Unsubscribe(a0, a1, a2) trace_SubscrContext_Unsubscribe_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubscrContext_Unsubscribe(a0, a1, a2) trace_SubscrContext_Unsubscribe_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45195, trace_SubscrContext_Unsubscribe_Impl, LOG_DEBUG, PAL_T("SubscrContext_Unsubscribe: subCtx (%p), provider (%p), subscription (%p) start"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_AlreadyUnsubscribed(a0) trace_SubscrContext_AlreadyUnsubscribed_Impl(__FILE__, __LINE__, a0)
#else
#define trace_SubscrContext_AlreadyUnsubscribed(a0) trace_SubscrContext_AlreadyUnsubscribed_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45196, trace_SubscrContext_AlreadyUnsubscribed_Impl, LOG_DEBUG, PAL_T("Subscription (%p) was already unsubscribed"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Subscription_StateInvalid(a0, a1) trace_Subscription_StateInvalid_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_Subscription_StateInvalid(a0, a1) trace_Subscription_StateInvalid_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45197, trace_Subscription_StateInvalid_Impl, LOG_DEBUG, PAL_T("Subscription state %u is invalid for unsubscribe on class %T"), int, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_UnsubscribeDone(a0, a1, a2) trace_SubscrContext_UnsubscribeDone_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubscrContext_UnsubscribeDone(a0, a1, a2) trace_SubscrContext_UnsubscribeDone_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45198, trace_SubscrContext_UnsubscribeDone_Impl, LOG_DEBUG, PAL_T("SubscrContext_Unsubscribe: subCtx (%p), provider (%p), subscription (%p); Complete"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_UnsubprvdOrSendfinalmsgStart(a0, a1, a2, a3) trace_SubscrContext_UnsubprvdOrSendfinalmsgStart_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_SubscrContext_UnsubprvdOrSendfinalmsgStart(a0, a1, a2, a3) trace_SubscrContext_UnsubprvdOrSendfinalmsgStart_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45199, trace_SubscrContext_UnsubprvdOrSendfinalmsgStart_Impl, LOG_DEBUG, PAL_T("SubscrContext_UnsubprvdOrSendfinalmsg: subCtx (%p), provider (%p), subscription (%p), invokeUnsubscribe(%d); start"), void *, void *, void *, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish(a0, a1, a2, a3) trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish(a0, a1, a2, a3) trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45200, trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish_Impl, LOG_DEBUG, PAL_T("SubscrContext_UnsubprvdOrSendfinalmsg: subCtx (%p), provider (%p), subscription (%p), invokeUnsubscribe(%d); Complete"), void *, void *, void *, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_ParseIndication_ClassValueFailed() trace_RegFile_ParseIndication_ClassValueFailed_Impl(__FILE__, __LINE__)
#else
#define trace_RegFile_ParseIndication_ClassValueFailed() trace_RegFile_ParseIndication_ClassValueFailed_Impl(0, 0)
#endif
FILE_EVENTD0(45201, trace_RegFile_ParseIndication_ClassValueFailed_Impl, LOG_DEBUG, PAL_T("Parse indication class value failed."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_AllocFailure() trace_RegFile_AllocFailure_Impl(__FILE__, __LINE__)
#else
#define trace_RegFile_AllocFailure() trace_RegFile_AllocFailure_Impl(0, 0)
#endif
FILE_EVENTD0(45202, trace_RegFile_AllocFailure_Impl, LOG_DEBUG, PAL_T("Allocate memory for RegClass failed."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_IndicationClassCannotHaveRefClass() trace_RegFile_IndicationClassCannotHaveRefClass_Impl(__FILE__, __LINE__)
#else
#define trace_RegFile_IndicationClassCannotHaveRefClass() trace_RegFile_IndicationClassCannotHaveRefClass_Impl(0, 0)
#endif
FILE_EVENTD0(45203, trace_RegFile_IndicationClassCannotHaveRefClass_Impl, LOG_DEBUG, PAL_T("Indication class can not have reference class."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_OutOfMemory_Name() trace_RegFile_OutOfMemory_Name_Impl(__FILE__, __LINE__)
#else
#define trace_RegFile_OutOfMemory_Name() trace_RegFile_OutOfMemory_Name_Impl(0, 0)
#endif
FILE_EVENTD0(45204, trace_RegFile_OutOfMemory_Name_Impl, LOG_DEBUG, PAL_T("Out of memory when duplicating name."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RegFile_OutOfMemory_Hosting() trace_RegFile_OutOfMemory_Hosting_Impl(__FILE__, __LINE__)
#else
#define trace_RegFile_OutOfMemory_Hosting() trace_RegFile_OutOfMemory_Hosting_Impl(0, 0)
#endif
FILE_EVENTD0(45205, trace_RegFile_OutOfMemory_Hosting_Impl, LOG_DEBUG, PAL_T("Out of memory when duplicating hosting."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Sock_SendingOnOwnThread(a0, a1, a2, a3) trace_Sock_SendingOnOwnThread_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_Sock_SendingOnOwnThread(a0, a1, a2, a3) trace_Sock_SendingOnOwnThread_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(45206, trace_Sock_SendingOnOwnThread_Impl, LOG_DEBUG, PAL_T("Sending msg(%p:%d:%T:%x) on own thread"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Sock_Sending(a0, a1, a2, a3, a4, a5, a6) trace_Sock_Sending_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4, a5, a6)
#else
#define trace_Sock_Sending(a0, a1, a2, a3, a4, a5, a6) trace_Sock_Sending_Impl(0, 0, a0, a1, tcs(a2), a3, a4, a5, a6)
#endif
FILE_EVENTD7(45207, trace_Sock_Sending_Impl, LOG_DEBUG, PAL_T("Sending msg(%p:%d:%T:%x), outstandingInstances: %d, MAX: %d, numberOfItem: %d"), Message *, MI_Uint32, const TChar *, MI_Uint64, ptrdiff_t, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Sock_SentResult(a0, a1, a2, a3, a4) trace_Sock_SentResult_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4)
#else
#define trace_Sock_SentResult(a0, a1, a2, a3, a4) trace_Sock_SentResult_Impl(0, 0, a0, a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(45208, trace_Sock_SentResult_Impl, LOG_DEBUG, PAL_T("Sending msg(%p:%d:%T:%x), result: %d"), Message *, MI_Uint32, const TChar *, MI_Uint64, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_GotoFailed(a0, a1) trace_Wsman_GotoFailed_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_Wsman_GotoFailed(a0, a1) trace_Wsman_GotoFailed_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENTD2(45209, trace_Wsman_GotoFailed_Impl, LOG_DEBUG, PAL_T("goto failed: %s:%u"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_ExpiredTimerForEnumerate(a0, a1) trace_Wsman_ExpiredTimerForEnumerate_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_ExpiredTimerForEnumerate(a0, a1) trace_Wsman_ExpiredTimerForEnumerate_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45210, trace_Wsman_ExpiredTimerForEnumerate_Impl, LOG_DEBUG, PAL_T("Expired timer for enumerate context %p (%u)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_EC_CheckCloseLeft(a0, a1) trace_Wsman_EC_CheckCloseLeft_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_EC_CheckCloseLeft(a0, a1) trace_Wsman_EC_CheckCloseLeft_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45211, trace_Wsman_EC_CheckCloseLeft_Impl, LOG_DEBUG, PAL_T("_EC_CheckCloseLeft: Left Closed: %d, activeConnection: %p"), int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_EC_CheckCloseRight(a0, a1) trace_Wsman_EC_CheckCloseRight_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_EC_CheckCloseRight(a0, a1) trace_Wsman_EC_CheckCloseRight_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45212, trace_Wsman_EC_CheckCloseRight_Impl, LOG_DEBUG, PAL_T("_EC_CheckCloseRight: haveTimer: %d, Right Closed: %d"), int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessResultEnumerationContext(a0, a1) trace_ProcessResultEnumerationContext_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ProcessResultEnumerationContext(a0, a1) trace_ProcessResultEnumerationContext_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45213, trace_ProcessResultEnumerationContext_Impl, LOG_DEBUG, PAL_T("_ProcessResultEnumerationContext: selfEC (%p) result (%d)"), void *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessSubscribeResponseEnumerationContext(a0) trace_ProcessSubscribeResponseEnumerationContext_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProcessSubscribeResponseEnumerationContext(a0) trace_ProcessSubscribeResponseEnumerationContext_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45214, trace_ProcessSubscribeResponseEnumerationContext_Impl, LOG_DEBUG, PAL_T("_ProcessSubscribeResponseEnumerationContext: selfEC (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessSubscribeResponseEnumerationContext_Success(a0) trace_ProcessSubscribeResponseEnumerationContext_Success_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProcessSubscribeResponseEnumerationContext_Success(a0) trace_ProcessSubscribeResponseEnumerationContext_Success_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45215, trace_ProcessSubscribeResponseEnumerationContext_Success_Impl, LOG_DEBUG, PAL_T("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) sent success subscribe response"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum(a0, a1, a2, a3) trace_WsmanEnum_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_WsmanEnum(a0, a1, a2, a3) trace_WsmanEnum_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45216, trace_WsmanEnum_Impl, LOG_DEBUG, PAL_T("WsmanEnum: %p _ProcessInstanceEnumerationContext: compeleted: %d, totalResponses: %d, totalResponseSize: %d"), void *, MI_Boolean, MI_Uint32, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_PostingMsg(a0, a1, a2, a3, a4, a5, a6) trace_WsmanConnection_PostingMsg_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4, a5, a6)
#else
#define trace_WsmanConnection_PostingMsg(a0, a1, a2, a3, a4, a5, a6) trace_WsmanConnection_PostingMsg_Impl(0, 0, a0, a1, tcs(a2), a3, a4, a5, a6)
#endif
FILE_EVENTD7(45217, trace_WsmanConnection_PostingMsg_Impl, LOG_DEBUG, PAL_T("WsmanConnection: Posting msg(%p:%d:%T:%x) on interaction %p<-[%p]<-%p"), Message *, MI_Uint32, const TChar *, MI_Uint64, Interaction *, Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_Ack(a0, a1) trace_WsmanConnection_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanConnection_Ack(a0, a1) trace_WsmanConnection_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45218, trace_WsmanConnection_Ack_Impl, LOG_DEBUG, PAL_T("WsmanConnection: Ack on interaction [%p]<-%p"), Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanConnection_Close(a0, a1, a2, a3) trace_WsmanConnection_Close_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_WsmanConnection_Close(a0, a1, a2, a3) trace_WsmanConnection_Close_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45219, trace_WsmanConnection_Close_Impl, LOG_DEBUG, PAL_T("WsmanConnection: Close on interaction [%p]<-%p outstandingRequest: %d, single_message: %p"), Strand *, Interaction *, MI_Boolean, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_Finish(a0) trace_WsmanEnum_Finish_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanEnum_Finish(a0) trace_WsmanEnum_Finish_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45220, trace_WsmanEnum_Finish_Impl, LOG_DEBUG, PAL_T("WsmanEnum: Finish: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionWsmanEnum_Left_SubscribeReAttached(a0, a1, a2, a3, a4) trace_InteractionWsmanEnum_Left_SubscribeReAttached_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_InteractionWsmanEnum_Left_SubscribeReAttached(a0, a1, a2, a3, a4) trace_InteractionWsmanEnum_Left_SubscribeReAttached_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(45221, trace_InteractionWsmanEnum_Left_SubscribeReAttached_Impl, LOG_DEBUG, PAL_T("_InteractionWsmanEnum_Left_SubscribeReAttached: %p, msg(%p:%d:%T:%x)"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_PostingMsg(a0, a1, a2, a3, a4, a5, a6) trace_WsmanEnum_PostingMsg_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4, a5, a6)
#else
#define trace_WsmanEnum_PostingMsg(a0, a1, a2, a3, a4, a5, a6) trace_WsmanEnum_PostingMsg_Impl(0, 0, a0, a1, tcs(a2), a3, a4, a5, a6)
#endif
FILE_EVENTD7(45222, trace_WsmanEnum_PostingMsg_Impl, LOG_DEBUG, PAL_T("WsmanEnum: Posting msg(%p:%d:%T:%x) on interaction %p<-[%p]<-%p"), Message *, MI_Uint32, const TChar *, MI_Uint64, Interaction *, Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanEnum_Ack(a0, a1) trace_WsmanEnum_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_WsmanEnum_Ack(a0, a1) trace_WsmanEnum_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45223, trace_WsmanEnum_Ack_Impl, LOG_DEBUG, PAL_T("WsmanEnum: Ack on interaction [%p]<-%p"), Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_AddSubscribeResponse(a0, a1) trace_Wsman_AddSubscribeResponse_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Wsman_AddSubscribeResponse(a0, a1) trace_Wsman_AddSubscribeResponse_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45224, trace_Wsman_AddSubscribeResponse_Impl, LOG_DEBUG, PAL_T("_WSMAN_AddSubscribeResponse: selfEC (%p), contextID(%x)"), void *, MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_ParametersMissingInSubscribeRequest() trace_Wsman_ParametersMissingInSubscribeRequest_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_ParametersMissingInSubscribeRequest() trace_Wsman_ParametersMissingInSubscribeRequest_Impl(0, 0)
#endif
FILE_EVENTD0(45225, trace_Wsman_ParametersMissingInSubscribeRequest_Impl, LOG_DEBUG, PAL_T("wsman: mandatory parameters (className, namespace) are not provided for subscribe request"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessUnsubscribeRequest(a0) trace_ProcessUnsubscribeRequest_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProcessUnsubscribeRequest(a0) trace_ProcessUnsubscribeRequest_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45226, trace_ProcessUnsubscribeRequest_Impl, LOG_DEBUG, PAL_T("_ProcessUnsubscribeRequest: selfCD (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnableToFindContext(a0) trace_Wsman_UnableToFindContext_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_UnableToFindContext(a0) trace_Wsman_UnableToFindContext_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45227, trace_Wsman_UnableToFindContext_Impl, LOG_DEBUG, PAL_T("wsman: unable to find wsman context for unsubscribe request (contextID=%x)."), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessUnsubscribeRequest_Complete(a0, a1, a2) trace_ProcessUnsubscribeRequest_Complete_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_ProcessUnsubscribeRequest_Complete(a0, a1, a2) trace_ProcessUnsubscribeRequest_Complete_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(45228, trace_ProcessUnsubscribeRequest_Complete_Impl, LOG_DEBUG, PAL_T("_ProcessUnsubscribeRequest: selfCD (%p), msg (%p:%T) complete"), void *, Message *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnableToParseXMLSubscribe() trace_Wsman_UnableToParseXMLSubscribe_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_UnableToParseXMLSubscribe() trace_Wsman_UnableToParseXMLSubscribe_Impl(0, 0)
#endif
FILE_EVENTD0(45229, trace_Wsman_UnableToParseXMLSubscribe_Impl, LOG_DEBUG, PAL_T("wsman: unable to parse incoming xml/ subscribe request body"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnableToParseXMLUnsubscribe() trace_Wsman_UnableToParseXMLUnsubscribe_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_UnableToParseXMLUnsubscribe() trace_Wsman_UnableToParseXMLUnsubscribe_Impl(0, 0)
#endif
FILE_EVENTD0(45230, trace_Wsman_UnableToParseXMLUnsubscribe_Impl, LOG_DEBUG, PAL_T("wsman: unable to parse incoming xml/ unsubscribe request body"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanReturn(a0, a1) trace_WsmanReturn_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_WsmanReturn(a0, a1) trace_WsmanReturn_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENTD2(45231, trace_WsmanReturn_Impl, LOG_DEBUG, PAL_T("RETURN{%s:%d}"), const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_BatchTcsDup_Failed() trace_BatchTcsDup_Failed_Impl(__FILE__, __LINE__)
#else
#define trace_BatchTcsDup_Failed() trace_BatchTcsDup_Failed_Impl(0, 0)
#endif
FILE_EVENTD0(45232, trace_BatchTcsDup_Failed_Impl, LOG_DEBUG, PAL_T("Batch_Tcsdup() failed: out of memory"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_GetSingleProperty_Failed(a0) trace_GetSingleProperty_Failed_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_GetSingleProperty_Failed(a0) trace_GetSingleProperty_Failed_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45233, trace_GetSingleProperty_Failed_Impl, LOG_DEBUG, PAL_T("_GetSingleProperty() failed: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_XsiTypeInvalidValue(a0) trace_XsiTypeInvalidValue_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_XsiTypeInvalidValue(a0) trace_XsiTypeInvalidValue_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45234, trace_XsiTypeInvalidValue_Impl, LOG_DEBUG, PAL_T("invalid value of xsi:type: %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WsmanUnsubscribe(a0) trace_WsmanUnsubscribe_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WsmanUnsubscribe(a0) trace_WsmanUnsubscribe_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45235, trace_WsmanUnsubscribe_Impl, LOG_DEBUG, PAL_T("Unsubscribe e:identifier {%d}"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnexpectedCloseTagWithNamespace(a0, a1) trace_Wsman_UnexpectedCloseTagWithNamespace_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_Wsman_UnexpectedCloseTagWithNamespace(a0, a1) trace_Wsman_UnexpectedCloseTagWithNamespace_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45236, trace_Wsman_UnexpectedCloseTagWithNamespace_Impl, LOG_DEBUG, PAL_T("wsman: unexpected close tag [%c:%T] in incoming xml"), TChar, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnknownMandatoryTagWithNamespace(a0, a1) trace_Wsman_UnknownMandatoryTagWithNamespace_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_Wsman_UnknownMandatoryTagWithNamespace(a0, a1) trace_Wsman_UnknownMandatoryTagWithNamespace_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45237, trace_Wsman_UnknownMandatoryTagWithNamespace_Impl, LOG_DEBUG, PAL_T("wsman: unknown mandatory tag [%c:%T]; aborted"), TChar, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_FilterTagMissingDialectAttribute() trace_Wsman_FilterTagMissingDialectAttribute_Impl(__FILE__, __LINE__)
#else
#define trace_Wsman_FilterTagMissingDialectAttribute() trace_Wsman_FilterTagMissingDialectAttribute_Impl(0, 0)
#endif
FILE_EVENTD0(45238, trace_Wsman_FilterTagMissingDialectAttribute_Impl, LOG_DEBUG, PAL_T("wsman: Filter tag missing Dialect attribute"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_UnknownDialect(a0) trace_Wsman_UnknownDialect_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_UnknownDialect(a0) trace_Wsman_UnknownDialect_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45239, trace_Wsman_UnknownDialect_Impl, LOG_DEBUG, PAL_T("wsman: Unknown dialect (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeDialect(a0) trace_Wsman_SubscribeDialect_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_SubscribeDialect(a0) trace_Wsman_SubscribeDialect_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45240, trace_Wsman_SubscribeDialect_Impl, LOG_DEBUG, PAL_T("wsman: Subscribe dialect (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_SubscribeFilter(a0) trace_Wsman_SubscribeFilter_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_Wsman_SubscribeFilter(a0) trace_Wsman_SubscribeFilter_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45241, trace_Wsman_SubscribeFilter_Impl, LOG_DEBUG, PAL_T("wsman: Subscribe filter (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_XmlSerializer_CurrentParent(a0) trace_XmlSerializer_CurrentParent_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_XmlSerializer_CurrentParent(a0) trace_XmlSerializer_CurrentParent_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45242, trace_XmlSerializer_CurrentParent_Impl, LOG_DEBUG, PAL_T("current parent {%T}"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_XmlSerializer_WriteBuffer_MiPropertyDecls(a0, a1, a2) trace_XmlSerializer_WriteBuffer_MiPropertyDecls_Impl(__FILE__, __LINE__, tcs(a0), tcs(a1), tcs(a2))
#else
#define trace_XmlSerializer_WriteBuffer_MiPropertyDecls(a0, a1, a2) trace_XmlSerializer_WriteBuffer_MiPropertyDecls_Impl(0, 0, tcs(a0), tcs(a1), tcs(a2))
#endif
FILE_EVENTD3(45243, trace_XmlSerializer_WriteBuffer_MiPropertyDecls_Impl, LOG_DEBUG, PAL_T("class = {%T} propagator = {%T} propertyName = %T"), const TChar *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostInteraction(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostInteraction_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4), a5)
#else
#define trace_SubscribeEntry_PostInteraction(a0, a1, a2, a3, a4, a5) trace_SubscribeEntry_PostInteraction_Impl(0, 0, a0, a1, a2, a3, tcs(a4), a5)
#endif
FILE_EVENTD6(45244, trace_SubscribeEntry_PostInteraction_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Post: Interaction [%p]<-%p, msg(%p:%d:%T:%x)"), Interaction *, Interaction *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostClosedSelf(a0, a1) trace_SubscribeEntry_PostClosedSelf_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_SubscribeEntry_PostClosedSelf(a0, a1) trace_SubscribeEntry_PostClosedSelf_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45245, trace_SubscribeEntry_PostClosedSelf_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Post: entry (%p) in status (%T). closed self."), void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostEntry(a0, a1) trace_SubscribeEntry_PostEntry_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_SubscribeEntry_PostEntry(a0, a1) trace_SubscribeEntry_PostEntry_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45246, trace_SubscribeEntry_PostEntry_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Post: entry (%p) in status (%T)"), void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostedMsg(a0, a1, a2, a3) trace_SubscribeEntry_PostedMsg_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_SubscribeEntry_PostedMsg(a0, a1, a2, a3) trace_SubscribeEntry_PostedMsg_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(45247, trace_SubscribeEntry_PostedMsg_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Post: Posted msg(%p:%d:%T:%x) to parent"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_Ack(a0, a1) trace_SubscribeEntry_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscribeEntry_Ack(a0, a1) trace_SubscribeEntry_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45248, trace_SubscribeEntry_Ack_Impl, LOG_DEBUG, PAL_T("SubscribeEntry: Ack on interaction [%p]<-%p"), Strand *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_Cancel(a0, a1, a2) trace_SubscribeEntry_Cancel_Impl(__FILE__, __LINE__, a0, tcs(a1), tcs(a2))
#else
#define trace_SubscribeEntry_Cancel(a0, a1, a2) trace_SubscribeEntry_Cancel_Impl(0, 0, a0, tcs(a1), tcs(a2))
#endif
FILE_EVENTD3(45249, trace_SubscribeEntry_Cancel_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Cancel: SubscribeEntry (%p); namespace (%T), class (%T)"), void *, const TChar *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_Finish() trace_SubscribeEntry_Finish_Impl(__FILE__, __LINE__)
#else
#define trace_SubscribeEntry_Finish() trace_SubscribeEntry_Finish_Impl(0, 0)
#endif
FILE_EVENTD0(45250, trace_SubscribeEntry_Finish_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Finish: Done"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Client_Post(a0, a1, a2, a3) trace_Client_Post_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_Client_Post(a0, a1, a2, a3) trace_Client_Post_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(45251, trace_Client_Post_Impl, LOG_DEBUG, PAL_T("_Client_Post: msg(%p:%d:%T:%x)"), Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Client_Ack() trace_Client_Ack_Impl(__FILE__, __LINE__)
#else
#define trace_Client_Ack() trace_Client_Ack_Impl(0, 0)
#endif
FILE_EVENTD0(45252, trace_Client_Ack_Impl, LOG_DEBUG, PAL_T("_Client_Ack"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Client_Close() trace_Client_Close_Impl(__FILE__, __LINE__)
#else
#define trace_Client_Close() trace_Client_Close_Impl(0, 0)
#endif
FILE_EVENTD0(45253, trace_Client_Close_Impl, LOG_DEBUG, PAL_T("_Client_Close"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Client_Finish() trace_Client_Finish_Impl(__FILE__, __LINE__)
#else
#define trace_Client_Finish() trace_Client_Finish_Impl(0, 0)
#endif
FILE_EVENTD0(45254, trace_Client_Finish_Impl, LOG_DEBUG, PAL_T("_Client_Finish"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Client_PostMessage(a0) trace_Client_PostMessage_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Client_PostMessage(a0) trace_Client_PostMessage_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45255, trace_Client_PostMessage_Impl, LOG_DEBUG, PAL_T("_Client_Post: message tag: %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NullInputParameter() trace_NullInputParameter_Impl(__FILE__, __LINE__)
#else
#define trace_NullInputParameter() trace_NullInputParameter_Impl(0, 0)
#endif
FILE_EVENTD0(45256, trace_NullInputParameter_Impl, LOG_DEBUG, PAL_T("NULL input parameter"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_NullInputParameterForClass(a0) trace_NullInputParameterForClass_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_NullInputParameterForClass(a0) trace_NullInputParameterForClass_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45257, trace_NullInputParameterForClass_Impl, LOG_DEBUG, PAL_T("NULL input parameter for %T"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifecycleContext_Cancel(a0) trace_LifecycleContext_Cancel_Impl(__FILE__, __LINE__, a0)
#else
#define trace_LifecycleContext_Cancel(a0) trace_LifecycleContext_Cancel_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45258, trace_LifecycleContext_Cancel_Impl, LOG_DEBUG, PAL_T("_LifecycleContext_Cancel: self (%p);"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifecycleContext_Cancel_Done(a0) trace_LifecycleContext_Cancel_Done_Impl(__FILE__, __LINE__, a0)
#else
#define trace_LifecycleContext_Cancel_Done(a0) trace_LifecycleContext_Cancel_Done_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45259, trace_LifecycleContext_Cancel_Done_Impl, LOG_DEBUG, PAL_T("_LifecycleContext_Cancel: unsubscribe self (%p) done"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_InvokeSubscribe(a0) trace_Provider_InvokeSubscribe_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Provider_InvokeSubscribe(a0) trace_Provider_InvokeSubscribe_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45260, trace_Provider_InvokeSubscribe_Impl, LOG_DEBUG, PAL_T("_Provider_InvokeSubscribe: subscription(%p) successfully subscribed. Send subscribe response"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeElem_Close(a0, a1, a2) trace_SubscribeElem_Close_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubscribeElem_Close(a0, a1, a2) trace_SubscribeElem_Close_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45261, trace_SubscribeElem_Close_Impl, LOG_DEBUG, PAL_T("_SubscribeElem_Close: self_ (%p) interaction [%p]<-%p"), Strand *, Interaction *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_TerminateIndication_Start(a0, a1, a2) trace_Provider_TerminateIndication_Start_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_Provider_TerminateIndication_Start(a0, a1, a2) trace_Provider_TerminateIndication_Start_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45262, trace_Provider_TerminateIndication_Start_Impl, LOG_DEBUG, PAL_T("Provider_TerminateIndication: Thread %x: class (%T) of provider (%p) start"), unsigned int, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_TerminateIndication_Complete(a0, a1, a2) trace_Provider_TerminateIndication_Complete_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_Provider_TerminateIndication_Complete(a0, a1, a2) trace_Provider_TerminateIndication_Complete_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45263, trace_Provider_TerminateIndication_Complete_Impl, LOG_DEBUG, PAL_T("Provider_TerminateIndication: Thread %x: class (%T) of provider (%p) complete"), unsigned int, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_DisablingLifeCycleIndicationsForClass(a0) trace_DisablingLifeCycleIndicationsForClass_Impl(__FILE__, __LINE__, tcs(a0))
#else
#define trace_DisablingLifeCycleIndicationsForClass(a0) trace_DisablingLifeCycleIndicationsForClass_Impl(0, 0, tcs(a0))
#endif
FILE_EVENTD1(45264, trace_DisablingLifeCycleIndicationsForClass_Impl, LOG_DEBUG, PAL_T("Disabling lifecycle indications for provider (%T)"), const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EnablingIndicationsForClass(a0, a1) trace_EnablingIndicationsForClass_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_EnablingIndicationsForClass(a0, a1) trace_EnablingIndicationsForClass_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45265, trace_EnablingIndicationsForClass_Impl, LOG_DEBUG, PAL_T("Enabling indications for class (%T) of provider (%p)"), const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InitializedIndicationsForClass(a0, a1) trace_InitializedIndicationsForClass_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_InitializedIndicationsForClass(a0, a1) trace_InitializedIndicationsForClass_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45266, trace_InitializedIndicationsForClass_Impl, LOG_DEBUG, PAL_T("Initialized indications for class (%T) of provider (%p)"), const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory(a0) trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory(a0) trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45267, trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Cancel %p, out of memory while creating UnsubscribeReq"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq(a0) trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq_Impl(__FILE__, __LINE__, a0)
#else
#define trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq(a0) trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45268, trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Cancel %p, post UnsubscribeReq"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_InteractionProtocolHandler_Operation_Strand_Post(a0, a1) trace_InteractionProtocolHandler_Operation_Strand_Post_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_InteractionProtocolHandler_Operation_Strand_Post(a0, a1) trace_InteractionProtocolHandler_Operation_Strand_Post_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45269, trace_InteractionProtocolHandler_Operation_Strand_Post_Impl, LOG_DEBUG, PAL_T("InteractionProtocolHandler_Operation_Strand_Post: Post Indication to MIDLL. %p, indication instance (%p)"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_InvokeDisable_Start(a0, a1, a2) trace_Provider_InvokeDisable_Start_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_Provider_InvokeDisable_Start(a0, a1, a2) trace_Provider_InvokeDisable_Start_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45270, trace_Provider_InvokeDisable_Start_Impl, LOG_DEBUG, PAL_T("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) start"), unsigned int, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_InvokeDisable_Complete(a0, a1, a2) trace_Provider_InvokeDisable_Complete_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_Provider_InvokeDisable_Complete(a0, a1, a2) trace_Provider_InvokeDisable_Complete_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45271, trace_Provider_InvokeDisable_Complete_Impl, LOG_DEBUG, PAL_T("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) complete"), unsigned int, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded(a0, a1, a2) trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded_Impl(__FILE__, __LINE__, a0, tcs(a1), a2)
#else
#define trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded(a0, a1, a2) trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded_Impl(0, 0, a0, tcs(a1), a2)
#endif
FILE_EVENTD3(45272, trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded_Impl, LOG_DEBUG, PAL_T("Provider_InvokeDisable: Thread %x: class (%T) of provider (%p) abandoned since new subscription was added"), unsigned int, const TChar *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_LifecycleContext_Post_InvalidState() trace_LifecycleContext_Post_InvalidState_Impl(__FILE__, __LINE__)
#else
#define trace_LifecycleContext_Post_InvalidState() trace_LifecycleContext_Post_InvalidState_Impl(0, 0)
#endif
FILE_EVENTD0(45273, trace_LifecycleContext_Post_InvalidState_Impl, LOG_DEBUG, PAL_T("Post on lifecycle context in invalid state"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrState_InvalidForUnsubscribe(a0, a1) trace_SubscrState_InvalidForUnsubscribe_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_SubscrState_InvalidForUnsubscribe(a0, a1) trace_SubscrState_InvalidForUnsubscribe_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45274, trace_SubscrState_InvalidForUnsubscribe_Impl, LOG_DEBUG, PAL_T("Subscription state %u is invalid for unsubscribe on class %T"), int, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UnsupportedLifecycleIndicationContext() trace_UnsupportedLifecycleIndicationContext_Impl(__FILE__, __LINE__)
#else
#define trace_UnsupportedLifecycleIndicationContext() trace_UnsupportedLifecycleIndicationContext_Impl(0, 0)
#endif
FILE_EVENTD0(45275, trace_UnsupportedLifecycleIndicationContext_Impl, LOG_DEBUG, PAL_T("Unsupported lifecycle indication context"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrForEvents_Succeeded_MSC(a0, a1) trace_SubscrForEvents_Succeeded_MSC_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_SubscrForEvents_Succeeded_MSC(a0, a1) trace_SubscrForEvents_Succeeded_MSC_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45276, trace_SubscrForEvents_Succeeded_MSC_Impl, LOG_DEBUG, PAL_T("Subscription succeeded for events of class (%T) with subscriptionID %I64u"), const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrForLifecycle_Succeeded_MSC(a0, a1) trace_SubscrForLifecycle_Succeeded_MSC_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_SubscrForLifecycle_Succeeded_MSC(a0, a1) trace_SubscrForLifecycle_Succeeded_MSC_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45277, trace_SubscrForLifecycle_Succeeded_MSC_Impl, LOG_DEBUG, PAL_T("Subscription succeeded for lifecycle events of class (%T) and subscriptionID %I64u"), const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RemovingSubscriptionForClass_MSC(a0, a1) trace_RemovingSubscriptionForClass_MSC_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_RemovingSubscriptionForClass_MSC(a0, a1) trace_RemovingSubscriptionForClass_MSC_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45278, trace_RemovingSubscriptionForClass_MSC_Impl, LOG_DEBUG, PAL_T("Removing subscription (%I64u) of class (%T)"), MI_Uint64, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrForEvents_Succeeded(a0, a1) trace_SubscrForEvents_Succeeded_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_SubscrForEvents_Succeeded(a0, a1) trace_SubscrForEvents_Succeeded_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45279, trace_SubscrForEvents_Succeeded_Impl, LOG_DEBUG, PAL_T("Subscription succeeded for events of class (%T) with subscriptionID %llu"), const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrForLifecycle_Succeeded(a0, a1) trace_SubscrForLifecycle_Succeeded_Impl(__FILE__, __LINE__, tcs(a0), a1)
#else
#define trace_SubscrForLifecycle_Succeeded(a0, a1) trace_SubscrForLifecycle_Succeeded_Impl(0, 0, tcs(a0), a1)
#endif
FILE_EVENTD2(45280, trace_SubscrForLifecycle_Succeeded_Impl, LOG_DEBUG, PAL_T("Subscription succeeded for lifecycle events of class (%T) and subscriptionID %llu"), const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_RemovingSubscriptionForClass(a0, a1) trace_RemovingSubscriptionForClass_Impl(__FILE__, __LINE__, a0, tcs(a1))
#else
#define trace_RemovingSubscriptionForClass(a0, a1) trace_RemovingSubscriptionForClass_Impl(0, 0, a0, tcs(a1))
#endif
FILE_EVENTD2(45281, trace_RemovingSubscriptionForClass_Impl, LOG_DEBUG, PAL_T("Removing subscription (%llu) of class (%T)"), MI_Uint64, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_ProcessReleaseRequest(a0) trace_Wsman_ProcessReleaseRequest_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_ProcessReleaseRequest(a0) trace_Wsman_ProcessReleaseRequest_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45282, trace_Wsman_ProcessReleaseRequest_Impl, LOG_DEBUG, PAL_T("_ProcessReleaseRequest: %x"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIApplicationEnter(a0, a1, a2, a3, a4) trace_MIApplicationEnter_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), tcs(a3), a4)
#else
#define trace_MIApplicationEnter(a0, a1, a2, a3, a4) trace_MIApplicationEnter_Impl(0, 0, scs(a0), a1, tcs(a2), tcs(a3), a4)
#endif
FILE_EVENTD5(45283, trace_MIApplicationEnter_Impl, LOG_DEBUG, PAL_T("Enter %s with application (%p), protocol (%T), destination(%T), session (%p)."), const char *, void *, const MI_Char *, const MI_Char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MILeavingSession(a0, a1) trace_MILeavingSession_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MILeavingSession(a0, a1) trace_MILeavingSession_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENTD2(45284, trace_MILeavingSession_Impl, LOG_DEBUG, PAL_T("Leave %s with session (%p)."), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIThunkAfterShutdown(a0) trace_MIThunkAfterShutdown_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MIThunkAfterShutdown(a0) trace_MIThunkAfterShutdown_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45285, trace_MIThunkAfterShutdown_Impl, LOG_DEBUG, PAL_T("Trying to thunk a handle after shutdown called: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIShuttingDownThunkHandle(a0) trace_MIShuttingDownThunkHandle_Impl(__FILE__, __LINE__, a0)
#else
#define trace_MIShuttingDownThunkHandle(a0) trace_MIShuttingDownThunkHandle_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45286, trace_MIShuttingDownThunkHandle_Impl, LOG_DEBUG, PAL_T("Shutting down thunk handle: %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MISessionEnter(a0, a1, a2, a3, a4) trace_MISessionEnter_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), tcs(a3), a4)
#else
#define trace_MISessionEnter(a0, a1, a2, a3, a4) trace_MISessionEnter_Impl(0, 0, scs(a0), a1, tcs(a2), tcs(a3), a4)
#endif
FILE_EVENTD5(45287, trace_MISessionEnter_Impl, LOG_DEBUG, PAL_T("Enter %s with application (%p), protocol (%T), destination(%T), session (%p)."), const char *, void *, const MI_Char *, const MI_Char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MISessionClose(a0, a1, a2, a3) trace_MISessionClose_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3)
#else
#define trace_MISessionClose(a0, a1, a2, a3) trace_MISessionClose_Impl(0, 0, scs(a0), a1, a2, a3)
#endif
FILE_EVENTD4(45288, trace_MISessionClose_Impl, LOG_DEBUG, PAL_T("Enter %s with session (%p), completionContext (%p), completionCallback (%p)."), const char *, void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIEnter(a0, a1) trace_MIEnter_Impl(__FILE__, __LINE__, scs(a0), a1)
#else
#define trace_MIEnter(a0, a1) trace_MIEnter_Impl(0, 0, scs(a0), a1)
#endif
FILE_EVENTD2(45289, trace_MIEnter_Impl, LOG_DEBUG, PAL_T("Enter %s - session (%p)"), const char *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MILeavingSessionWithOperation(a0, a1, a2) trace_MILeavingSessionWithOperation_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2))
#else
#define trace_MILeavingSessionWithOperation(a0, a1, a2) trace_MILeavingSessionWithOperation_Impl(0, 0, scs(a0), a1, tcs(a2))
#endif
FILE_EVENTD3(45290, trace_MILeavingSessionWithOperation_Impl, LOG_DEBUG, PAL_T("Leave %s on session (%p) with for operation (%T)."), const char *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppInit(a0, a1) trace_MIClient_AppInit_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_AppInit(a0, a1) trace_MIClient_AppInit_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45291, trace_MIClient_AppInit_Impl, LOG_DEBUG, PAL_T("MI_Client Application Initialize: application=%p, internal-application=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppClose(a0, a1) trace_MIClient_AppClose_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_AppClose(a0, a1) trace_MIClient_AppClose_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45292, trace_MIClient_AppClose_Impl, LOG_DEBUG, PAL_T("MI_Client Application Close: application=%p, internal-application=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppCloseCancelingAll(a0, a1, a2) trace_MIClient_AppCloseCancelingAll_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_AppCloseCancelingAll(a0, a1, a2) trace_MIClient_AppCloseCancelingAll_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45293, trace_MIClient_AppCloseCancelingAll_Impl, LOG_DEBUG, PAL_T("MI_Client Application Close: Cancelling all operations on application=%p, internal-application=%p, session=%p"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppCloseWaitingOnSessions(a0, a1, a2) trace_MIClient_AppCloseWaitingOnSessions_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_AppCloseWaitingOnSessions(a0, a1, a2) trace_MIClient_AppCloseWaitingOnSessions_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45294, trace_MIClient_AppCloseWaitingOnSessions_Impl, LOG_DEBUG, PAL_T("MI_Client Application Close: Waiting for all sessions to shutdown on application=%p, internal-application=%p, number left=%llu"), void *, void *, ptrdiff_t)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppCloseWaitingOnHostedProviders(a0, a1, a2) trace_MIClient_AppCloseWaitingOnHostedProviders_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_AppCloseWaitingOnHostedProviders(a0, a1, a2) trace_MIClient_AppCloseWaitingOnHostedProviders_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45295, trace_MIClient_AppCloseWaitingOnHostedProviders_Impl, LOG_DEBUG, PAL_T("MI_Client Application Close: Waiting for all hosted providers to shutdown on application=%p, internal-application=%p, number left=%llu"), void *, void *, ptrdiff_t)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AppCloseCompleted(a0, a1) trace_MIClient_AppCloseCompleted_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_AppCloseCompleted(a0, a1) trace_MIClient_AppCloseCompleted_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45296, trace_MIClient_AppCloseCompleted_Impl, LOG_DEBUG, PAL_T("MI_Client Application Close: completed application=%p, internal-application=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_SessionCreate(a0, a1, a2) trace_MIClient_SessionCreate_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_SessionCreate(a0, a1, a2) trace_MIClient_SessionCreate_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45297, trace_MIClient_SessionCreate_Impl, LOG_DEBUG, PAL_T("MI_Client Session Create: application=%p, session=%p, internal-session=%p"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_SessionCloseCompleted(a0, a1) trace_MIClient_SessionCloseCompleted_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_SessionCloseCompleted(a0, a1) trace_MIClient_SessionCloseCompleted_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45298, trace_MIClient_SessionCloseCompleted_Impl, LOG_DEBUG, PAL_T("MI_Client Session Close: Completed session=%p, internal-session=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_SessionClose(a0, a1) trace_MIClient_SessionClose_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_SessionClose(a0, a1) trace_MIClient_SessionClose_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45299, trace_MIClient_SessionClose_Impl, LOG_DEBUG, PAL_T("MI_Client Session Close: session=%p, internal-session=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_SessionClose_WaitingOnOperations(a0, a1, a2) trace_MIClient_SessionClose_WaitingOnOperations_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_SessionClose_WaitingOnOperations(a0, a1, a2) trace_MIClient_SessionClose_WaitingOnOperations_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45300, trace_MIClient_SessionClose_WaitingOnOperations_Impl, LOG_DEBUG, PAL_T("MI_Client Session Close: waiting for all operations to shutdown session=%p, internal-session=%p, number left=%llu"), void *, void *, ptrdiff_t)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationInstancResultAsync(a0, a1, a2, a3, a4) trace_MIClient_OperationInstancResultAsync_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_OperationInstancResultAsync(a0, a1, a2, a3, a4) trace_MIClient_OperationInstancResultAsync_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45301, trace_MIClient_OperationInstancResultAsync_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Instance Result (async): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationInstanceResult_WaitingForClient(a0, a1, a2, a3, a4) trace_MIClient_OperationInstanceResult_WaitingForClient_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_OperationInstanceResult_WaitingForClient(a0, a1, a2, a3, a4) trace_MIClient_OperationInstanceResult_WaitingForClient_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45302, trace_MIClient_OperationInstanceResult_WaitingForClient_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Instance Result (sync, waiting for client to get it): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationClassResult(a0, a1, a2, a3, a4) trace_MIClient_OperationClassResult_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_OperationClassResult(a0, a1, a2, a3, a4) trace_MIClient_OperationClassResult_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45303, trace_MIClient_OperationClassResult_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Class Result: session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationIndicationResult(a0, a1, a2, a3, a4) trace_MIClient_OperationIndicationResult_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_OperationIndicationResult(a0, a1, a2, a3, a4) trace_MIClient_OperationIndicationResult_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45304, trace_MIClient_OperationIndicationResult_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Indication Result: session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationCloseCompleted(a0, a1, a2) trace_MIClient_OperationCloseCompleted_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_OperationCloseCompleted(a0, a1, a2) trace_MIClient_OperationCloseCompleted_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45305, trace_MIClient_OperationCloseCompleted_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Close: Complete session=%p, operation=%p, internal-operation=%p"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationClose(a0, a1) trace_MIClient_OperationClose_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_OperationClose(a0, a1) trace_MIClient_OperationClose_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45306, trace_MIClient_OperationClose_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Close: operation=%p, internal-operation=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationClose_WaitingForFinalResult(a0, a1) trace_MIClient_OperationClose_WaitingForFinalResult_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_OperationClose_WaitingForFinalResult(a0, a1) trace_MIClient_OperationClose_WaitingForFinalResult_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45307, trace_MIClient_OperationClose_WaitingForFinalResult_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Close: Waiting for the final result to be retrieved.  Client should retrieve the final result before calling MI_Operation_Close.  operation=%p, internal-operation=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationCancel(a0, a1) trace_MIClient_OperationCancel_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_MIClient_OperationCancel(a0, a1) trace_MIClient_OperationCancel_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45308, trace_MIClient_OperationCancel_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Cancel: operation=%p, internal-operation=%p"), void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_GetInstance(a0, a1, a2, a3) trace_MIClient_GetInstance_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3))
#else
#define trace_MIClient_GetInstance(a0, a1, a2, a3) trace_MIClient_GetInstance_Impl(0, 0, a0, a1, a2, tcs(a3))
#endif
FILE_EVENTD4(45309, trace_MIClient_GetInstance_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Get Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T"), void *, void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_Invoke(a0, a1, a2, a3, a4, a5) trace_MIClient_Invoke_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#else
#define trace_MIClient_Invoke(a0, a1, a2, a3, a4, a5) trace_MIClient_Invoke_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#endif
FILE_EVENTD6(45310, trace_MIClient_Invoke_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Invoke: session=%p, operation=%p, internal-operation=%p, namespace=%T, classname=%T, methodname=%T"), void *, void *, void *, const MI_Char *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_EnumerateInstance(a0, a1, a2, a3, a4) trace_MIClient_EnumerateInstance_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4))
#else
#define trace_MIClient_EnumerateInstance(a0, a1, a2, a3, a4) trace_MIClient_EnumerateInstance_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4))
#endif
FILE_EVENTD5(45311, trace_MIClient_EnumerateInstance_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Enumerate Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, classname=%T"), void *, void *, void *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_QueryInstances(a0, a1, a2, a3, a4, a5) trace_MIClient_QueryInstances_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#else
#define trace_MIClient_QueryInstances(a0, a1, a2, a3, a4, a5) trace_MIClient_QueryInstances_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#endif
FILE_EVENTD6(45312, trace_MIClient_QueryInstances_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Query Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, queryDialect=%T, queryExpression=%T"), void *, void *, void *, const MI_Char *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OperationInstancResultSync(a0, a1, a2, a3, a4) trace_MIClient_OperationInstancResultSync_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_OperationInstancResultSync(a0, a1, a2, a3, a4) trace_MIClient_OperationInstancResultSync_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45313, trace_MIClient_OperationInstancResultSync_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Instance Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_IndicationResultSync(a0, a1, a2, a3, a4) trace_MIClient_IndicationResultSync_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_IndicationResultSync(a0, a1, a2, a3, a4) trace_MIClient_IndicationResultSync_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45314, trace_MIClient_IndicationResultSync_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Indication Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_ClassResultSync(a0, a1, a2, a3, a4) trace_MIClient_ClassResultSync_Impl(__FILE__, __LINE__, a0, a1, a2, a3, tcs(a4))
#else
#define trace_MIClient_ClassResultSync(a0, a1, a2, a3, a4) trace_MIClient_ClassResultSync_Impl(0, 0, a0, a1, a2, a3, tcs(a4))
#endif
FILE_EVENTD5(45315, trace_MIClient_ClassResultSync_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Class Result (sync): session=%p, operation=%p, internal-operation=%p, resultCode=%u, moreResults=%T"), void *, void *, void *, MI_Result, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_AssociatorInstances(a0, a1, a2, a3, a4, a5, a6, a7, a8) trace_MIClient_AssociatorInstances_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4, tcs(a5), tcs(a6), tcs(a7), tcs(a8))
#else
#define trace_MIClient_AssociatorInstances(a0, a1, a2, a3, a4, a5, a6, a7, a8) trace_MIClient_AssociatorInstances_Impl(0, 0, a0, a1, a2, tcs(a3), a4, tcs(a5), tcs(a6), tcs(a7), tcs(a8))
#endif
FILE_EVENTD9(45316, trace_MIClient_AssociatorInstances_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Associator Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, instance=%p, assocClass=%T, resultClass=%T, role=%T, resultRole=%T"), void *, void *, void *, const MI_Char *, void *, const MI_Char *, const MI_Char *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_ReferenceInstances(a0, a1, a2, a3, a4, a5) trace_MIClient_ReferenceInstances_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#else
#define trace_MIClient_ReferenceInstances(a0, a1, a2, a3, a4, a5) trace_MIClient_ReferenceInstances_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#endif
FILE_EVENTD6(45317, trace_MIClient_ReferenceInstances_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Reference Instances: session=%p, operation=%p, internal-operation=%p, namespace=%T, resultClass=%T, role=%T"), void *, void *, void *, const MI_Char *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_ModifyInstance(a0, a1, a2, a3) trace_MIClient_ModifyInstance_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3))
#else
#define trace_MIClient_ModifyInstance(a0, a1, a2, a3) trace_MIClient_ModifyInstance_Impl(0, 0, a0, a1, a2, tcs(a3))
#endif
FILE_EVENTD4(45318, trace_MIClient_ModifyInstance_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Modify Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T"), void *, void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_CreateInstance(a0, a1, a2, a3) trace_MIClient_CreateInstance_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3))
#else
#define trace_MIClient_CreateInstance(a0, a1, a2, a3) trace_MIClient_CreateInstance_Impl(0, 0, a0, a1, a2, tcs(a3))
#endif
FILE_EVENTD4(45319, trace_MIClient_CreateInstance_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Create Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T"), void *, void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_DeleteInstance(a0, a1, a2, a3) trace_MIClient_DeleteInstance_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3))
#else
#define trace_MIClient_DeleteInstance(a0, a1, a2, a3) trace_MIClient_DeleteInstance_Impl(0, 0, a0, a1, a2, tcs(a3))
#endif
FILE_EVENTD4(45320, trace_MIClient_DeleteInstance_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Delete Instance: session=%p, operation=%p, internal-operation=%p, namespace=%T"), void *, void *, void *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_GetClass(a0, a1, a2, a3, a4) trace_MIClient_GetClass_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4))
#else
#define trace_MIClient_GetClass(a0, a1, a2, a3, a4) trace_MIClient_GetClass_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4))
#endif
FILE_EVENTD5(45321, trace_MIClient_GetClass_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Get Class: session=%p, operation=%p, internal-operation=%p, namespace=%T, className=%T"), void *, void *, void *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_EnumerateClasses(a0, a1, a2, a3, a4) trace_MIClient_EnumerateClasses_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4))
#else
#define trace_MIClient_EnumerateClasses(a0, a1, a2, a3, a4) trace_MIClient_EnumerateClasses_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4))
#endif
FILE_EVENTD5(45322, trace_MIClient_EnumerateClasses_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Enumerate Classes: session=%p, operation=%p, internal-operation=%p, namespace=%s, className=%s"), void *, void *, void *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_Subscribe(a0, a1, a2, a3, a4, a5) trace_MIClient_Subscribe_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#else
#define trace_MIClient_Subscribe(a0, a1, a2, a3, a4, a5) trace_MIClient_Subscribe_Impl(0, 0, a0, a1, a2, tcs(a3), tcs(a4), tcs(a5))
#endif
FILE_EVENTD6(45323, trace_MIClient_Subscribe_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Subscribe: session=%p, operation=%p, internal-operation=%p, namespace=%T, queryDialect=%T, queryExpression=%T"), void *, void *, void *, const MI_Char *, const MI_Char *, const MI_Char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_TestConnection(a0, a1, a2) trace_MIClient_TestConnection_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_MIClient_TestConnection(a0, a1, a2) trace_MIClient_TestConnection_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45324, trace_MIClient_TestConnection_Impl, LOG_DEBUG, PAL_T("MI_Client Operation Test Connection: session=%p, operation=%p, internal-operation=%p"), void *, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MIClient_OutOfMemory() trace_MIClient_OutOfMemory_Impl(__FILE__, __LINE__)
#else
#define trace_MIClient_OutOfMemory() trace_MIClient_OutOfMemory_Impl(0, 0)
#endif
FILE_EVENTD0(45325, trace_MIClient_OutOfMemory_Impl, LOG_DEBUG, PAL_T("MI_Client Out of memory!"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgr_DeleteSubscription_Start(a0, a1, a2, a3, a4, a5) trace_SubMgr_DeleteSubscription_Start_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4, a5)
#else
#define trace_SubMgr_DeleteSubscription_Start(a0, a1, a2, a3, a4, a5) trace_SubMgr_DeleteSubscription_Start_Impl(0, 0, a0, a1, a2, a3, a4, a5)
#endif
FILE_EVENTD6(45326, trace_SubMgr_DeleteSubscription_Start_Impl, LOG_DEBUG, PAL_T("SubMgr_DeleteSubscription: Start    Thread %x: mgr (%p) Subscription (%p); (%d) active subscriptions;  header (%p), tail (%p)"), unsigned int, void*, void *, unsigned int, void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgr_DeleteSubscription_Complete(a0, a1, a2, a3, a4) trace_SubMgr_DeleteSubscription_Complete_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_SubMgr_DeleteSubscription_Complete(a0, a1, a2, a3, a4) trace_SubMgr_DeleteSubscription_Complete_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(45327, trace_SubMgr_DeleteSubscription_Complete_Impl, LOG_DEBUG, PAL_T("SubMgr_DeleteSubscription: Complete Thread %x: mgr (%p); remains (%d) subscriptions; header (%p), tail (%p)"), unsigned int, void*, unsigned int, void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ScheduleRequest_UnsubscribeProvider(a0, a1) trace_ScheduleRequest_UnsubscribeProvider_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ScheduleRequest_UnsubscribeProvider(a0, a1) trace_ScheduleRequest_UnsubscribeProvider_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45328, trace_ScheduleRequest_UnsubscribeProvider_Impl, LOG_DEBUG, PAL_T("Schedule_UnsubscribeProvider: Thread %x: scheduled unsubscribe request for subscription (%p)"), unsigned int, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ScheduleRequest_SubscribeProvider(a0, a1, a2, a3) trace_ScheduleRequest_SubscribeProvider_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_ScheduleRequest_SubscribeProvider(a0, a1, a2, a3) trace_ScheduleRequest_SubscribeProvider_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(45329, trace_ScheduleRequest_SubscribeProvider_Impl, LOG_DEBUG, PAL_T("Schedule_SubscribeRequest: Thread %x: scheduled subscribe request provider (%p), msg (%p), subContext (%p)"), unsigned int, void*, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_noniothread_proc_start(a0) trace_noniothread_proc_start_Impl(__FILE__, __LINE__, a0)
#else
#define trace_noniothread_proc_start(a0) trace_noniothread_proc_start_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45330, trace_noniothread_proc_start_Impl, LOG_DEBUG, PAL_T("noniothread_proc_start: Thread %x:"), unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_noniothread_proc_end(a0) trace_noniothread_proc_end_Impl(__FILE__, __LINE__, a0)
#else
#define trace_noniothread_proc_end(a0) trace_noniothread_proc_end_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45331, trace_noniothread_proc_end_Impl, LOG_DEBUG, PAL_T("noniothread_proc_end: Thread %x:"), unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_nioproc_FreeRequestItem(a0) trace_nioproc_FreeRequestItem_Impl(__FILE__, __LINE__, a0)
#else
#define trace_nioproc_FreeRequestItem(a0) trace_nioproc_FreeRequestItem_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45332, trace_nioproc_FreeRequestItem_Impl, LOG_DEBUG, PAL_T("Free RequestItem : %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_nioproc_CreateRequestItem(a0) trace_nioproc_CreateRequestItem_Impl(__FILE__, __LINE__, a0)
#else
#define trace_nioproc_CreateRequestItem(a0) trace_nioproc_CreateRequestItem_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45333, trace_nioproc_CreateRequestItem_Impl, LOG_DEBUG, PAL_T("Create RequestItem : %p"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_ShouldCallUnsubscribe(a0, a1, a2) trace_SubMgrSubscription_ShouldCallUnsubscribe_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubMgrSubscription_ShouldCallUnsubscribe(a0, a1, a2) trace_SubMgrSubscription_ShouldCallUnsubscribe_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45334, trace_SubMgrSubscription_ShouldCallUnsubscribe_Impl, LOG_DEBUG, PAL_T("SubMgrSubscription_ShouldCallUnsubscribe: Thread %x:; subscription (%p); should unsubscribe (%d)"), unsigned int, void*, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed(a0, a1) trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed(a0, a1) trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45335, trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed_Impl, LOG_DEBUG, PAL_T("SubMgrSubscription_ShouldCallUnsubscribe: Thread %x:; subscription (%p) was already unsubscribed"), unsigned int, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_ShouldSendFinalMsg(a0, a1, a2) trace_SubMgrSubscription_ShouldSendFinalMsg_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubMgrSubscription_ShouldSendFinalMsg(a0, a1, a2) trace_SubMgrSubscription_ShouldSendFinalMsg_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45336, trace_SubMgrSubscription_ShouldSendFinalMsg_Impl, LOG_DEBUG, PAL_T("SubMgrSubscription_ShouldSendFinalMsg: Thread %x:; subscription (%p); should send final message (%d)"), unsigned int, void*, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent(a0, a1) trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent(a0, a1) trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45337, trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent_Impl, LOG_DEBUG, PAL_T("SubMgrSubscription_ShouldSendFinalMsg: Thread %x:; subscription (%p) already sent final message"), unsigned int, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgr_GetSubscriptionByContext_NotFound(a0, a1, a2) trace_SubMgr_GetSubscriptionByContext_NotFound_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubMgr_GetSubscriptionByContext_NotFound(a0, a1, a2) trace_SubMgr_GetSubscriptionByContext_NotFound_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45338, trace_SubMgr_GetSubscriptionByContext_NotFound_Impl, LOG_DEBUG, PAL_T("SubMgr_GetSubscriptionByContext: Thread %x:; mgr (%p) subscription (%p) not found"), unsigned int, void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscrContext_ProcessResult(a0, a1, a2) trace_SubscrContext_ProcessResult_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubscrContext_ProcessResult(a0, a1, a2) trace_SubscrContext_ProcessResult_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45339, trace_SubscrContext_ProcessResult_Impl, LOG_DEBUG, PAL_T("_SubscrContext_ProcessResult: Thread %x: ctx (%p) subscription (%p)"), unsigned int, void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Started_MSCVER(a0) trace_Timer_Started_MSCVER_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Started_MSCVER(a0) trace_Timer_Started_MSCVER_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45340, trace_Timer_Started_MSCVER_Impl, LOG_DEBUG, PAL_T("Timer started with timeout value %I64u"), PAL_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Started_POSIX(a0) trace_Timer_Started_POSIX_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Started_POSIX(a0) trace_Timer_Started_POSIX_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45341, trace_Timer_Started_POSIX_Impl, LOG_DEBUG, PAL_T("Timer started with timeout value %llu"), PAL_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_ManualTrigger(a0, a1) trace_Timer_ManualTrigger_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Timer_ManualTrigger(a0, a1) trace_Timer_ManualTrigger_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45342, trace_Timer_ManualTrigger_Impl, LOG_DEBUG, PAL_T("Timer_Fire: Manual trigger of timer (%p) on strand (%p)"), void*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Close(a0) trace_Timer_Close_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Timer_Close(a0) trace_Timer_Close_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45343, trace_Timer_Close_Impl, LOG_DEBUG, PAL_T("Timer_Close: Closing timer (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_CallbackMayRunLong_True() trace_Timer_CallbackMayRunLong_True_Impl(__FILE__, __LINE__)
#else
#define trace_Timer_CallbackMayRunLong_True() trace_Timer_CallbackMayRunLong_True_Impl(0, 0)
#endif
FILE_EVENTD0(45344, trace_Timer_CallbackMayRunLong_True_Impl, LOG_DEBUG, PAL_T("Timer_Callback: CallbackMayRunLong is TRUE"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_CallbackMayRunLong_False() trace_Timer_CallbackMayRunLong_False_Impl(__FILE__, __LINE__)
#else
#define trace_Timer_CallbackMayRunLong_False() trace_Timer_CallbackMayRunLong_False_Impl(0, 0)
#endif
FILE_EVENTD0(45345, trace_Timer_CallbackMayRunLong_False_Impl, LOG_DEBUG, PAL_T("Timer_Callback: CallbackMayRunLong is FALSE"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Timer_Selector_Added() trace_Timer_Selector_Added_Impl(__FILE__, __LINE__)
#else
#define trace_Timer_Selector_Added() trace_Timer_Selector_Added_Impl(0, 0)
#endif
FILE_EVENTD0(45346, trace_Timer_Selector_Added_Impl, LOG_DEBUG, PAL_T("Timer_Callback: SELECTOR_ADD"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Unsubscribe_DisableProvider(a0, a1) trace_Unsubscribe_DisableProvider_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_Unsubscribe_DisableProvider(a0, a1) trace_Unsubscribe_DisableProvider_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45347, trace_Unsubscribe_DisableProvider_Impl, LOG_DEBUG, PAL_T("DisableProvider: Thread %x: scheduled disable indications request for provider (%p)"), unsigned int, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Socket_Accept(a0) trace_Socket_Accept_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Socket_Accept(a0) trace_Socket_Accept_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45348, trace_Socket_Accept_Impl, LOG_DEBUG, PAL_T("Sock_Accept: sock (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Sock_Close(a0) trace_Sock_Close_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Sock_Close(a0) trace_Sock_Close_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45349, trace_Sock_Close_Impl, LOG_DEBUG, PAL_T("Sock_Close: sock (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ConnectionInPost_IgnoreUnsubscribeReq(a0, a1) trace_ConnectionInPost_IgnoreUnsubscribeReq_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ConnectionInPost_IgnoreUnsubscribeReq(a0, a1) trace_ConnectionInPost_IgnoreUnsubscribeReq_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45350, trace_ConnectionInPost_IgnoreUnsubscribeReq_Impl, LOG_DEBUG, PAL_T("_ConnectionIn_Post: binary protocol ignore UnsubscribeReq msg (%p), operationId (%x)"), void *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscribeEntry_PostFinalMsg(a0, a1, a2, a3, a4, a5, a6) trace_SubscribeEntry_PostFinalMsg_Impl(__FILE__, __LINE__, a0, tcs(a1), a2, a3, tcs(a4), a5, a6)
#else
#define trace_SubscribeEntry_PostFinalMsg(a0, a1, a2, a3, a4, a5, a6) trace_SubscribeEntry_PostFinalMsg_Impl(0, 0, a0, tcs(a1), a2, a3, tcs(a4), a5, a6)
#endif
FILE_EVENTD7(45351, trace_SubscribeEntry_PostFinalMsg_Impl, LOG_DEBUG, PAL_T("_SubscribeEntry_Post: entry (%p) in status (%T), received final msg(%p:%d:%T:%x), result (%d)"), void *, const TChar *, Message *, MI_Uint32, const TChar *, MI_Uint64, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_Release_Finalized(a0, a1) trace_SubMgrSubscription_Release_Finalized_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubMgrSubscription_Release_Finalized(a0, a1) trace_SubMgrSubscription_Release_Finalized_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45352, trace_SubMgrSubscription_Release_Finalized_Impl, LOG_DEBUG, PAL_T("SubMgrSubscription_Release: Thread %x: finalize subscription (%p), refcount is 0"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored(a0, a1, a2) trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored(a0, a1, a2) trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45353, trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored_Impl, LOG_DEBUG, PAL_T("_InteractionWsmanEnum_Left_ConnectionDataTimeout: Ignored because Post or Close already occurred on CD RM=%p, SM=%p, closed=%d"), void*, void*, MI_Boolean)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WSManEnumerationContext_CD_Timeout_notifier(a0) trace_WSManEnumerationContext_CD_Timeout_notifier_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WSManEnumerationContext_CD_Timeout_notifier(a0) trace_WSManEnumerationContext_CD_Timeout_notifier_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45354, trace_WSManEnumerationContext_CD_Timeout_notifier_Impl, LOG_DEBUG, PAL_T("_InteractionWsmanEnum_Left_ConnectionDataTimeout: CD notifier for EC %p"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest(a0) trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest(a0) trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45355, trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest_Impl, LOG_DEBUG, PAL_T("_ProcessSubscribeResponseEnumerationContext: selfEC (%p) Ignoring response to timed out request."), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineCredentialsVerified(a0) trace_EngineCredentialsVerified_Impl(__FILE__, __LINE__, a0)
#else
#define trace_EngineCredentialsVerified(a0) trace_EngineCredentialsVerified_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45356, trace_EngineCredentialsVerified_Impl, LOG_DEBUG, PAL_T("Engine credentials verified (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerClosingSocket(a0, a1) trace_ServerClosingSocket_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ServerClosingSocket(a0, a1) trace_ServerClosingSocket_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45357, trace_ServerClosingSocket_Impl, LOG_DEBUG, PAL_T("Server closing socket (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineClosingSocket(a0, a1) trace_EngineClosingSocket_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_EngineClosingSocket(a0, a1) trace_EngineClosingSocket_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45358, trace_EngineClosingSocket_Impl, LOG_DEBUG, PAL_T("Engine closing socket (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerEstablishingSocket(a0, a1) trace_ServerEstablishingSocket_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_ServerEstablishingSocket(a0, a1) trace_ServerEstablishingSocket_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45359, trace_ServerEstablishingSocket_Impl, LOG_DEBUG, PAL_T("Server establishing socket with engine (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_EngineEstablishingSocket(a0, a1) trace_EngineEstablishingSocket_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_EngineEstablishingSocket(a0, a1) trace_EngineEstablishingSocket_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45360, trace_EngineEstablishingSocket_Impl, LOG_DEBUG, PAL_T("Engine establishing socket with server (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ServerInfoReceived() trace_ServerInfoReceived_Impl(__FILE__, __LINE__)
#else
#define trace_ServerInfoReceived() trace_ServerInfoReceived_Impl(0, 0)
#endif
FILE_EVENTD0(45361, trace_ServerInfoReceived_Impl, LOG_DEBUG, PAL_T("Server connection info received"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TrackerHashMapAdd(a0, a1) trace_TrackerHashMapAdd_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_TrackerHashMapAdd(a0, a1) trace_TrackerHashMapAdd_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45362, trace_TrackerHashMapAdd_Impl, LOG_DEBUG, PAL_T("Tracker hash map added (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TrackerHashMapRemove(a0) trace_TrackerHashMapRemove_Impl(__FILE__, __LINE__, a0)
#else
#define trace_TrackerHashMapRemove(a0) trace_TrackerHashMapRemove_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45363, trace_TrackerHashMapRemove_Impl, LOG_DEBUG, PAL_T("Tracker hash map removeded (%d)"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TrackerHashMapFind(a0, a1) trace_TrackerHashMapFind_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_TrackerHashMapFind(a0, a1) trace_TrackerHashMapFind_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(45364, trace_TrackerHashMapFind_Impl, LOG_DEBUG, PAL_T("Tracker hash map found (%p, %d)"), void*, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClientCredentialsVerfied(a0) trace_ClientCredentialsVerfied_Impl(__FILE__, __LINE__, a0)
#else
#define trace_ClientCredentialsVerfied(a0) trace_ClientCredentialsVerfied_Impl(0, 0, a0)
#endif
FILE_EVENTD1(45365, trace_ClientCredentialsVerfied_Impl, LOG_DEBUG, PAL_T("Engine: Client Credentials Verified (%p)"), void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ClientCredentialsVerfied2() trace_ClientCredentialsVerfied2_Impl(__FILE__, __LINE__)
#else
#define trace_ClientCredentialsVerfied2() trace_ClientCredentialsVerfied2_Impl(0, 0)
#endif
FILE_EVENTD0(45366, trace_ClientCredentialsVerfied2_Impl, LOG_DEBUG, PAL_T("Client: Client Credentials Verified"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AuthStates(a0, a1, a2) trace_AuthStates_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_AuthStates(a0, a1, a2) trace_AuthStates_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(45367, trace_AuthStates_Impl, LOG_DEBUG, PAL_T("Handle:(%p), ClientAuthState = %d, EngineAuthState = %d"), void*, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_AskServerToAuthenticate() trace_AskServerToAuthenticate_Impl(__FILE__, __LINE__)
#else
#define trace_AskServerToAuthenticate() trace_AskServerToAuthenticate_Impl(0, 0)
#endif
FILE_EVENTD0(45368, trace_AskServerToAuthenticate_Impl, LOG_DEBUG, PAL_T("Asking Server to PAM authenticate"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Action(a0, a1, a2) trace_Strand_Action_Impl(__FILE__, __LINE__, a0, scs(a1), scs(a2))
#else
#define trace_Strand_Action(a0, a1, a2) trace_Strand_Action_Impl(0, 0, a0, scs(a1), scs(a2))
#endif
FILE_EVENTD3(55000, trace_Strand_Action_Impl, LOG_VERBOSE, PAL_T("Strand %p(%s), action: %s"), Strand *, const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandFlags(a0, a1, a2, a3, a4, a5, a6, a7, a8) trace_StrandFlags_Impl(__FILE__, __LINE__, a0, scs(a1), a2, a3, a4, a5, a6, a7, a8)
#else
#define trace_StrandFlags(a0, a1, a2, a3, a4, a5, a6, a7, a8) trace_StrandFlags_Impl(0, 0, a0, scs(a1), a2, a3, a4, a5, a6, a7, a8)
#endif
FILE_EVENTD9(55001, trace_StrandFlags_Impl, LOG_VERBOSE, PAL_T("Strand %p(%s), %s: interaction: %p, opened: %d, thisClosedOther: %d, thisAckPending: %d, otherClosedThis: %d, otherAckPending: %d, ackPassthru: %d"), Strand *, const char *, Interaction *, int, int, int, int, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Add(a0, a1, a2, a3, a4) trace_StrandEntryOperation_Add_Impl(__FILE__, __LINE__, a0, a1, scs(a2), a3, scs(a4))
#else
#define trace_StrandEntryOperation_Add(a0, a1, a2, a3, a4) trace_StrandEntryOperation_Add_Impl(0, 0, a0, a1, scs(a2), a3, scs(a4))
#endif
FILE_EVENTD5(55002, trace_StrandEntryOperation_Add_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Add: %d entries %p(%s): %p(%s)"), unsigned int, StrandMany *, const char *, Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Cancel(a0, a1, a2) trace_StrandEntryOperation_Cancel_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_Cancel(a0, a1, a2) trace_StrandEntryOperation_Cancel_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55003, trace_StrandEntryOperation_Cancel_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Cancel: %p(%s) canceling on parent (canceled: %d)"), StrandMany *, const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_PostControl_PostIgnored(a0, a1, a2) trace_StrandEntryOperation_PostControl_PostIgnored_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_PostControl_PostIgnored(a0, a1, a2) trace_StrandEntryOperation_PostControl_PostIgnored_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55004, trace_StrandEntryOperation_PostControl_PostIgnored_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_PostControl: %p(%s) Post on parent ignored after interaction is closed, msg: %p"), StrandMany *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_PostControl_ToParent(a0, a1, a2) trace_StrandEntryOperation_PostControl_ToParent_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_PostControl_ToParent(a0, a1, a2) trace_StrandEntryOperation_PostControl_ToParent_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55005, trace_StrandEntryOperation_PostControl_ToParent_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_PostControl: %p(%s) Posting control msg on parent, msg: %p"), StrandMany *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Post_IgnoredAfterClose(a0, a1, a2) trace_StrandEntryOperation_Post_IgnoredAfterClose_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_Post_IgnoredAfterClose(a0, a1, a2) trace_StrandEntryOperation_Post_IgnoredAfterClose_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55006, trace_StrandEntryOperation_Post_IgnoredAfterClose_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Post: %p(%s) Post on parent ignored after interaction is closed, msg: %p"), StrandMany *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Post_ToParent(a0, a1, a2) trace_StrandEntryOperation_Post_ToParent_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_Post_ToParent(a0, a1, a2) trace_StrandEntryOperation_Post_ToParent_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55007, trace_StrandEntryOperation_Post_ToParent_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Post: %p(%s) Posting on parent, msg: %p"), StrandMany *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Post_CannotPostWaitingOnAck(a0, a1, a2) trace_StrandEntryOperation_Post_CannotPostWaitingOnAck_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_Post_CannotPostWaitingOnAck(a0, a1, a2) trace_StrandEntryOperation_Post_CannotPostWaitingOnAck_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55008, trace_StrandEntryOperation_Post_CannotPostWaitingOnAck_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Post: %p(%s) cannot post on parent (waiting ack), msg: %p"), StrandMany *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Close(a0, a1, a2) trace_StrandEntryOperation_Close_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandEntryOperation_Close(a0, a1, a2) trace_StrandEntryOperation_Close_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55009, trace_StrandEntryOperation_Close_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Close: %p(%s) close on parent (closed: %d)"), StrandMany *, const char *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandEntryOperation_Deleted(a0, a1, a2, a3) trace_StrandEntryOperation_Deleted_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_StrandEntryOperation_Deleted(a0, a1, a2, a3) trace_StrandEntryOperation_Deleted_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENTD4(55010, trace_StrandEntryOperation_Deleted_Impl, LOG_VERBOSE, PAL_T("_StrandEntryOperation_Deleted: %p(%s): %p(%s)"), StrandMany *, const char *, void *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_RunPendingOp(a0, a1, a2, a3) trace_Strand_RunPendingOp_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_Strand_RunPendingOp(a0, a1, a2, a3) trace_Strand_RunPendingOp_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENTD4(55011, trace_Strand_RunPendingOp_Impl, LOG_VERBOSE, PAL_T("Strand_RunPendingOp: %p(%s), bit: %d(%s)"), Strand *, const char *, int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_RunPendingOp_CannotComplete(a0, a1, a2, a3) trace_Strand_RunPendingOp_CannotComplete_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_Strand_RunPendingOp_CannotComplete(a0, a1, a2, a3) trace_Strand_RunPendingOp_CannotComplete_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENTD4(55012, trace_Strand_RunPendingOp_CannotComplete_Impl, LOG_VERBOSE, PAL_T("Strand_RunPendingOp: %p(%s), operation Cannot complete, bit: %d(%s)"), Strand *, const char *, int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_RunPendingOp_EntryDeleted(a0, a1, a2, a3) trace_Strand_RunPendingOp_EntryDeleted_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_Strand_RunPendingOp_EntryDeleted(a0, a1, a2, a3) trace_Strand_RunPendingOp_EntryDeleted_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENTD4(55013, trace_Strand_RunPendingOp_EntryDeleted_Impl, LOG_VERBOSE, PAL_T("Strand_RunPendingOp: %p(%s), deleted entry, bit: %d(%s)"), Strand *, const char *, int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMethod_Entry_CancelInternal(a0, a1) trace_StrandMethod_Entry_CancelInternal_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_StrandMethod_Entry_CancelInternal(a0, a1) trace_StrandMethod_Entry_CancelInternal_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENTD2(55014, trace_StrandMethod_Entry_CancelInternal_Impl, LOG_VERBOSE, PAL_T("_StrandMethod_Entry_CancelInternal: %p(%s)"), Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMethod_Entry_PostControlInternal(a0, a1, a2) trace_StrandMethod_Entry_PostControlInternal_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandMethod_Entry_PostControlInternal(a0, a1, a2) trace_StrandMethod_Entry_PostControlInternal_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55015, trace_StrandMethod_Entry_PostControlInternal_Impl, LOG_VERBOSE, PAL_T("_StrandMethod_Entry_PostControlInternal: %p(%s) Control msg from parent, msg: %p"), Strand *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMethod_Entry_PostInternal(a0, a1, a2) trace_StrandMethod_Entry_PostInternal_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_StrandMethod_Entry_PostInternal(a0, a1, a2) trace_StrandMethod_Entry_PostInternal_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55016, trace_StrandMethod_Entry_PostInternal_Impl, LOG_VERBOSE, PAL_T("_StrandMethod_Entry_PostInternal: %p(%s) Msg from parent, msg: %p"), Strand *, const char *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMethod_Entry_AckInternal(a0, a1) trace_StrandMethod_Entry_AckInternal_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_StrandMethod_Entry_AckInternal(a0, a1) trace_StrandMethod_Entry_AckInternal_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENTD2(55017, trace_StrandMethod_Entry_AckInternal_Impl, LOG_VERBOSE, PAL_T("_StrandMethod_Entry_AckInternal: %p(%s)"), Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandMethod_Entry_CloseInternal(a0, a1, a2, a3) trace_StrandMethod_Entry_CloseInternal_Impl(__FILE__, __LINE__, a0, scs(a1), a2, a3)
#else
#define trace_StrandMethod_Entry_CloseInternal(a0, a1, a2, a3) trace_StrandMethod_Entry_CloseInternal_Impl(0, 0, a0, scs(a1), a2, a3)
#endif
FILE_EVENTD4(55018, trace_StrandMethod_Entry_CloseInternal_Impl, LOG_VERBOSE, PAL_T("_StrandMethod_Entry_CloseInternal: %p(%s) opened: %d, closed other: %d"), Strand *, const char *, int, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_DeletedEntry(a0, a1, a2, a3) trace_Strand_DeletedEntry_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3))
#else
#define trace_Strand_DeletedEntry(a0, a1, a2, a3) trace_Strand_DeletedEntry_Impl(0, 0, a0, scs(a1), a2, scs(a3))
#endif
FILE_EVENTD4(55019, trace_Strand_DeletedEntry_Impl, LOG_VERBOSE, PAL_T("Strand %p(%s), deleting entry %p(%s)"), Strand *, const char *, void *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExecLoop(a0, a1, a2, a3, a4, a5, a6) trace_Strand_ExecLoop_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4, scs(a5), scs(a6))
#else
#define trace_Strand_ExecLoop(a0, a1, a2, a3, a4, a5, a6) trace_Strand_ExecLoop_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4, scs(a5), scs(a6))
#endif
FILE_EVENTD7(55020, trace_Strand_ExecLoop_Impl, LOG_VERBOSE, PAL_T("Strand_ExecLoop: %p(%s) state %x(%s), bit: %d(%s) [%s]"), Strand *, const char *, ptrdiff_t, const char *, int, const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExecLoop_Leave(a0, a1, a2, a3) trace_Strand_ExecLoop_Leave_Impl(__FILE__, __LINE__, a0, a1, a2, a3)
#else
#define trace_Strand_ExecLoop_Leave(a0, a1, a2, a3) trace_Strand_ExecLoop_Leave_Impl(0, 0, a0, a1, a2, a3)
#endif
FILE_EVENTD4(55021, trace_Strand_ExecLoop_Leave_Impl, LOG_VERBOSE, PAL_T("Strand_ExecLoop: %p LEAVE occurred, previous state %x, bit: %d (%x)"), Strand *, ptrdiff_t, int, ptrdiff_t)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExecuteLoop_AboutToExit(a0, a1, a2) trace_Strand_ExecuteLoop_AboutToExit_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_Strand_ExecuteLoop_AboutToExit(a0, a1, a2) trace_Strand_ExecuteLoop_AboutToExit_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(55022, trace_Strand_ExecuteLoop_AboutToExit_Impl, LOG_VERBOSE, PAL_T("Strand_ExecuteLoop: %p About to exit, state %x, About To Finish: %d"), Strand *, ptrdiff_t, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExecLoop_Exits(a0, a1, a2, a3, a4) trace_Strand_ExecLoop_Exits_Impl(__FILE__, __LINE__, a0, scs(a1), a2, a3, scs(a4))
#else
#define trace_Strand_ExecLoop_Exits(a0, a1, a2, a3, a4) trace_Strand_ExecLoop_Exits_Impl(0, 0, a0, scs(a1), a2, a3, scs(a4))
#endif
FILE_EVENTD5(55023, trace_Strand_ExecLoop_Exits_Impl, LOG_VERBOSE, PAL_T("Strand_ExecLoop: %p(%s) Exits, state %x, ToFinish: %d [%s]"), Strand *, const char *, ptrdiff_t, int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExecLoop_DoesntExit(a0, a1, a2, a3, a4, a5, a6) trace_Strand_ExecLoop_DoesntExit_Impl(__FILE__, __LINE__, a0, scs(a1), a2, a3, scs(a4), a5, scs(a6))
#else
#define trace_Strand_ExecLoop_DoesntExit(a0, a1, a2, a3, a4, a5, a6) trace_Strand_ExecLoop_DoesntExit_Impl(0, 0, a0, scs(a1), a2, a3, scs(a4), a5, scs(a6))
#endif
FILE_EVENTD7(55024, trace_Strand_ExecLoop_DoesntExit_Impl, LOG_VERBOSE, PAL_T("Strand_ExecLoop: %p(%s) DOESN'T Exit, state %x, newState: %x(%s), ToFinish: %d [%s]"), Strand *, const char *, ptrdiff_t, ptrdiff_t, const char *, int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ScheduleParent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) trace_Strand_ScheduleParent_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4, scs(a5), a6, scs(a7), a8, scs(a9))
#else
#define trace_Strand_ScheduleParent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) trace_Strand_ScheduleParent_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4, scs(a5), a6, scs(a7), a8, scs(a9))
#endif
FILE_EVENTD10(55025, trace_Strand_ScheduleParent_Impl, LOG_VERBOSE, PAL_T("_Strand_ScheduleParent: %p(%s) state %x(%s), bit:%x(%s) from %p(%s); methodBit: %x(%s)"), Strand *, const char *, ptrdiff_t, const char *, int, const char *, Strand *, const char *, unsigned int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ScheduleEntry(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) trace_Strand_ScheduleEntry_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4, scs(a5), a6, scs(a7), a8, scs(a9))
#else
#define trace_Strand_ScheduleEntry(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) trace_Strand_ScheduleEntry_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4, scs(a5), a6, scs(a7), a8, scs(a9))
#endif
FILE_EVENTD10(55026, trace_Strand_ScheduleEntry_Impl, LOG_VERBOSE, PAL_T("_Strand_ScheduleEntry: %p(%s) state %x(%s), bit:%x(%s) from %p(%s); methodBit: %x(%s)"), Strand *, const char *, ptrdiff_t, const char *, int, const char *, Strand *, const char *, unsigned int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Schedule(a0, a1, a2, a3, a4, a5) trace_Strand_Schedule_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4, scs(a5))
#else
#define trace_Strand_Schedule(a0, a1, a2, a3, a4, a5) trace_Strand_Schedule_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4, scs(a5))
#endif
FILE_EVENTD6(55027, trace_Strand_Schedule_Impl, LOG_VERBOSE, PAL_T("_Strand_Schedule: %p(%s) state %x(%s), methodBit: %x(%s)"), Strand *, const char *, ptrdiff_t, const char *, unsigned int, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Schedule2(a0, a1, a2) trace_Strand_Schedule2_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_Strand_Schedule2(a0, a1, a2) trace_Strand_Schedule2_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(55028, trace_Strand_Schedule2_Impl, LOG_VERBOSE, PAL_T("_Strand_Schedule: %p state %x, methodBit: %x"), Strand *, ptrdiff_t, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Schedule_TakingOver(a0, a1, a2, a3, a4, a5, a6) trace_Strand_Schedule_TakingOver_Impl(__FILE__, __LINE__, a0, scs(a1), a2, scs(a3), a4, a5, scs(a6))
#else
#define trace_Strand_Schedule_TakingOver(a0, a1, a2, a3, a4, a5, a6) trace_Strand_Schedule_TakingOver_Impl(0, 0, a0, scs(a1), a2, scs(a3), a4, a5, scs(a6))
#endif
FILE_EVENTD7(55029, trace_Strand_Schedule_TakingOver_Impl, LOG_VERBOSE, PAL_T("_Strand_Schedule: %p(%s) Taking over opening, state %x(%s), methodBit: %x, currentMethodBit: %x(%s)"), Strand *, const char *, ptrdiff_t, const char *, unsigned int, ptrdiff_t, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_EnterStrand(a0, a1) trace_Strand_EnterStrand_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_Strand_EnterStrand(a0, a1) trace_Strand_EnterStrand_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENTD2(55030, trace_Strand_EnterStrand_Impl, LOG_VERBOSE, PAL_T("_Strand_EnterStrand: %p(%s)"), Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_ExitStrand(a0, a1) trace_Strand_ExitStrand_Impl(__FILE__, __LINE__, a0, scs(a1))
#else
#define trace_Strand_ExitStrand(a0, a1) trace_Strand_ExitStrand_Impl(0, 0, a0, scs(a1))
#endif
FILE_EVENTD2(55031, trace_Strand_ExitStrand_Impl, LOG_VERBOSE, PAL_T("_Strand_ExitStrand: %p(%s)"), Strand *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_TracePost(a0, a1, a2, a3, a4) trace_Strand_TracePost_Impl(__FILE__, __LINE__, a0, a1, a2, tcs(a3), a4)
#else
#define trace_Strand_TracePost(a0, a1, a2, a3, a4) trace_Strand_TracePost_Impl(0, 0, a0, a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(55032, trace_Strand_TracePost_Impl, LOG_VERBOSE, PAL_T("_Strand_TracePost: %p, msg(%p:%d:%T:%x)"), void *, Message *, MI_Uint32, const TChar *, MI_Uint64)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_TracePostResult(a0, a1, a2, a3, a4) trace_Strand_TracePostResult_Impl(__FILE__, __LINE__, a0, a1, a2, a3, a4)
#else
#define trace_Strand_TracePostResult(a0, a1, a2, a3, a4) trace_Strand_TracePostResult_Impl(0, 0, a0, a1, a2, a3, a4)
#endif
FILE_EVENTD5(55033, trace_Strand_TracePostResult_Impl, LOG_VERBOSE, PAL_T("_Strand_TracePost: %p, msg(%p:%d:%x) PostResultMsg:%d"), void *, Message *, MI_Uint32, MI_Uint64, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Strand_Leave(a0, a1, a2) trace_Strand_Leave_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_Strand_Leave(a0, a1, a2) trace_Strand_Leave_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(55034, trace_Strand_Leave_Impl, LOG_VERBOSE, PAL_T("Strand_Leave: %p(%s) (strandStealedFlag %p)"), void*, const char*, void*)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_New(a0, a1, a2, a3, a4) trace_SubMgrSubscription_New_Impl(__FILE__, __LINE__, scs(a0), a1, a2, tcs(a3), a4)
#else
#define trace_SubMgrSubscription_New(a0, a1, a2, a3, a4) trace_SubMgrSubscription_New_Impl(0, 0, scs(a0), a1, a2, tcs(a3), a4)
#endif
FILE_EVENTD5(55035, trace_SubMgrSubscription_New_Impl, LOG_VERBOSE, PAL_T("SubMgrSubscription_New: (%s:%u) Subscription (%p: class=%T), Refcount (%u)"), const char*, MI_Uint32, void *, const TChar*, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_Addref(a0, a1, a2, a3) trace_SubMgrSubscription_Addref_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3)
#else
#define trace_SubMgrSubscription_Addref(a0, a1, a2, a3) trace_SubMgrSubscription_Addref_Impl(0, 0, scs(a0), a1, a2, a3)
#endif
FILE_EVENTD4(55036, trace_SubMgrSubscription_Addref_Impl, LOG_VERBOSE, PAL_T("SubMgrSubscription_Addref: (%s:%u) Subscription (%p), Refcount (%u)"), const char*, MI_Uint32, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_Release(a0, a1, a2, a3) trace_SubMgrSubscription_Release_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3)
#else
#define trace_SubMgrSubscription_Release(a0, a1, a2, a3) trace_SubMgrSubscription_Release_Impl(0, 0, scs(a0), a1, a2, a3)
#endif
FILE_EVENTD4(55037, trace_SubMgrSubscription_Release_Impl, LOG_VERBOSE, PAL_T("SubMgrSubscription_Release: (%s:%u) Subscription (%p), Refcount (%u)"), const char*, MI_Uint32, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_AcquirePostLock(a0, a1, a2) trace_SubMgrSubscription_AcquirePostLock_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubMgrSubscription_AcquirePostLock(a0, a1, a2) trace_SubMgrSubscription_AcquirePostLock_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(55038, trace_SubMgrSubscription_AcquirePostLock_Impl, LOG_VERBOSE, PAL_T("SubMgrSubscription_AcquirePostLock: Thread %x: Subscription (%p), context (%p), acquired postlock"), unsigned int, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubMgrSubscription_ReleasePostLock(a0, a1, a2) trace_SubMgrSubscription_ReleasePostLock_Impl(__FILE__, __LINE__, a0, a1, a2)
#else
#define trace_SubMgrSubscription_ReleasePostLock(a0, a1, a2) trace_SubMgrSubscription_ReleasePostLock_Impl(0, 0, a0, a1, a2)
#endif
FILE_EVENTD3(55039, trace_SubMgrSubscription_ReleasePostLock_Impl, LOG_VERBOSE, PAL_T("SubMgrSubscription_ReleasePostLock: Thread %x: Subscription (%p), context (%p), to release postlock"), unsigned int, void *, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_Start(a0, a1, a2) trace_SubscriptionManager_AcquireEnableLock_Start_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_SubscriptionManager_AcquireEnableLock_Start(a0, a1, a2) trace_SubscriptionManager_AcquireEnableLock_Start_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(55040, trace_SubscriptionManager_AcquireEnableLock_Start_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), operation type (%T) started"), unsigned int, void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated(a0, a1) trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated(a0, a1) trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55041, trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), agggregation context terminated, acquire lock failed"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall(a0, a1) trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall(a0, a1) trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55042, trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); ignore disable call since there are still active subscriptions"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_CancelAll(a0, a1) trace_SubscriptionManager_AcquireEnableLock_CancelAll_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_AcquireEnableLock_CancelAll(a0, a1) trace_SubscriptionManager_AcquireEnableLock_CancelAll_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55043, trace_SubscriptionManager_AcquireEnableLock_CancelAll_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); cancel all subscriptions"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_ReleaseLock(a0, a1) trace_SubscriptionManager_AcquireEnableLock_ReleaseLock_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_AcquireEnableLock_ReleaseLock(a0, a1) trace_SubscriptionManager_AcquireEnableLock_ReleaseLock_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55044, trace_SubscriptionManager_AcquireEnableLock_ReleaseLock_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p); aggregation context active, found new subsription(s), release lock"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_AcquireEnableLock_Complete(a0, a1, a2) trace_SubscriptionManager_AcquireEnableLock_Complete_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_SubscriptionManager_AcquireEnableLock_Complete(a0, a1, a2) trace_SubscriptionManager_AcquireEnableLock_Complete_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(55045, trace_SubscriptionManager_AcquireEnableLock_Complete_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_AcquireEnableLock: Thread %x: SubscriptionManager (%p), operation type (%T), acquired enablelock"), unsigned int, void *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_ReleaseEnableLock(a0, a1) trace_SubscriptionManager_ReleaseEnableLock_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_ReleaseEnableLock(a0, a1) trace_SubscriptionManager_ReleaseEnableLock_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55046, trace_SubscriptionManager_ReleaseEnableLock_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_ReleaseEnableLock: Thread %x: SubscriptionManager (%p), released enablelock"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked(a0, a1) trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked(a0, a1) trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(55047, trace_SubscriptionManager_ReleaseEnableLock_DisableAlreadyUnlocked_Impl, LOG_VERBOSE, PAL_T("SubscriptionManager_ReleaseEnableLock: Thread %x: SubscriptionManager (%p), enablelock was already released for disable case"), unsigned int, void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Wsman_PackFieldNil(a0) trace_Wsman_PackFieldNil_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Wsman_PackFieldNil(a0) trace_Wsman_PackFieldNil_Impl(0, 0, a0)
#endif
FILE_EVENTD1(55048, trace_Wsman_PackFieldNil_Impl, LOG_VERBOSE, PAL_T("_PackFieldNil with usePreciseArrays = %d"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WSManEnumerateContext_CD_Timeout_on_inactive_context() trace_WSManEnumerateContext_CD_Timeout_on_inactive_context_Impl(__FILE__, __LINE__)
#else
#define trace_WSManEnumerateContext_CD_Timeout_on_inactive_context() trace_WSManEnumerateContext_CD_Timeout_on_inactive_context_Impl(0, 0)
#endif
FILE_EVENTD0(55049, trace_WSManEnumerateContext_CD_Timeout_on_inactive_context_Impl, LOG_VERBOSE, PAL_T("EC_Left_ConnectionDataTimeout: activeConnection is NULL"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_WSManEnumerateContext_CD_Timeout_during_initial_operation(a0) trace_WSManEnumerateContext_CD_Timeout_during_initial_operation_Impl(__FILE__, __LINE__, a0)
#else
#define trace_WSManEnumerateContext_CD_Timeout_during_initial_operation(a0) trace_WSManEnumerateContext_CD_Timeout_during_initial_operation_Impl(0, 0, a0)
#endif
FILE_EVENTD1(55050, trace_WSManEnumerateContext_CD_Timeout_during_initial_operation_Impl, LOG_VERBOSE, PAL_T("EC_Left_ConnectionDataTimeout: action %d timed out"), int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Message_New(a0, a1, a2, a3, a4) trace_Message_New_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), a3, a4)
#else
#define trace_Message_New(a0, a1, a2, a3, a4) trace_Message_New_Impl(0, 0, scs(a0), a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(55051, trace_Message_New_Impl, LOG_VERBOSE, PAL_T("Message_New: %s(%u): __Message_New(%T): %p: refs=%u"), const char*, MI_Uint32, const TChar *, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Message_AddRef(a0, a1, a2, a3, a4) trace_Message_AddRef_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), a3, a4)
#else
#define trace_Message_AddRef(a0, a1, a2, a3, a4) trace_Message_AddRef_Impl(0, 0, scs(a0), a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(55052, trace_Message_AddRef_Impl, LOG_VERBOSE, PAL_T("Message_Addref: %s(%u): __Message_AddRef(%T): %p: refs=%u"), const char*, MI_Uint32, const TChar *, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Message_Release(a0, a1, a2, a3, a4) trace_Message_Release_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), a3, a4)
#else
#define trace_Message_Release(a0, a1, a2, a3, a4) trace_Message_Release_Impl(0, 0, scs(a0), a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(55053, trace_Message_Release_Impl, LOG_VERBOSE, PAL_T("Message_Release: %s(%u): __Message_Release(%T): %p: refs=%u"), const char*, MI_Uint32, const TChar *, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_MessageFromBatch_Complete(a0, a1, a2, a3, a4) trace_MessageFromBatch_Complete_Impl(__FILE__, __LINE__, scs(a0), a1, tcs(a2), a3, a4)
#else
#define trace_MessageFromBatch_Complete(a0, a1, a2, a3, a4) trace_MessageFromBatch_Complete_Impl(0, 0, scs(a0), a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(55054, trace_MessageFromBatch_Complete_Impl, LOG_VERBOSE, PAL_T("MessageFromBatch: %s(%u): __MessageFromBatch(%T): %p: refs=%u"), const char*, MI_Uint32, const TChar *, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_Addref(a0, a1, a2, a3) trace_ProtocolSocket_Addref_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3)
#else
#define trace_ProtocolSocket_Addref(a0, a1, a2, a3) trace_ProtocolSocket_Addref_Impl(0, 0, scs(a0), a1, a2, a3)
#endif
FILE_EVENTD4(55055, trace_ProtocolSocket_Addref_Impl, LOG_VERBOSE, PAL_T("ProtocolSocket_Addref: %s(%u): self %p: refs=%u"), const char*, MI_Uint32, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_ProtocolSocket_Release(a0, a1, a2, a3) trace_ProtocolSocket_Release_Impl(__FILE__, __LINE__, scs(a0), a1, a2, a3)
#else
#define trace_ProtocolSocket_Release(a0, a1, a2, a3) trace_ProtocolSocket_Release_Impl(0, 0, scs(a0), a1, a2, a3)
#endif
FILE_EVENTD4(55056, trace_ProtocolSocket_Release_Impl, LOG_VERBOSE, PAL_T("ProtocolSocket_Release: %s(%u): self %p: refs=%u"), const char*, MI_Uint32, void *, unsigned int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Post(a0, a1, a2) trace_StrandProtocol_Post_Impl(__FILE__, __LINE__, a0, a1, tcs(a2))
#else
#define trace_StrandProtocol_Post(a0, a1, a2) trace_StrandProtocol_Post_Impl(0, 0, a0, a1, tcs(a2))
#endif
FILE_EVENTD3(60000, trace_StrandProtocol_Post_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Post: self (%p), msg (%p:%T)"), Strand *, Message *, const TChar *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Post_ClosedSelf(a0) trace_StrandProtocol_Post_ClosedSelf_Impl(__FILE__, __LINE__, a0)
#else
#define trace_StrandProtocol_Post_ClosedSelf(a0) trace_StrandProtocol_Post_ClosedSelf_Impl(0, 0, a0)
#endif
FILE_EVENTD1(60001, trace_StrandProtocol_Post_ClosedSelf_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Post: closed self (%p)"), Strand *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Post_Total(a0, a1, a2, a3) trace_StrandProtocol_Post_Total_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_StrandProtocol_Post_Total(a0, a1, a2, a3) trace_StrandProtocol_Post_Total_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(60002, trace_StrandProtocol_Post_Total_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Post: self (%p), msg (%p:%T). Total (%d) posts"), Strand *, Message *, const TChar *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Ack(a0, a1) trace_StrandProtocol_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandProtocol_Ack(a0, a1) trace_StrandProtocol_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60003, trace_StrandProtocol_Ack_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Ack: self (%p). Total (%d) Ack"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Cancel(a0, a1) trace_StrandProtocol_Cancel_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandProtocol_Cancel(a0, a1) trace_StrandProtocol_Cancel_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60004, trace_StrandProtocol_Cancel_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Cancel: self (%p). Total (%d) Cancel"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandProtocol_Finished(a0, a1) trace_StrandProtocol_Finished_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandProtocol_Finished(a0, a1) trace_StrandProtocol_Finished_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60005, trace_StrandProtocol_Finished_Impl, LOG_VERBOSE, PAL_T("_StrandProtocol_Finished: self (%p). Total (%d) Finished"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_Ack(a0, a1) trace_StrandSimAgentMgr_Ack_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_Ack(a0, a1) trace_StrandSimAgentMgr_Ack_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60006, trace_StrandSimAgentMgr_Ack_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s)"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_AckCloseSelf(a0, a1) trace_StrandSimAgentMgr_AckCloseSelf_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_AckCloseSelf(a0, a1) trace_StrandSimAgentMgr_AckCloseSelf_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60007, trace_StrandSimAgentMgr_AckCloseSelf_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: close self (%p). Total (%d) Ack(s)"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_AckStopByDesign(a0, a1) trace_StrandSimAgentMgr_AckStopByDesign_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_AckStopByDesign(a0, a1) trace_StrandSimAgentMgr_AckStopByDesign_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60008, trace_StrandSimAgentMgr_AckStopByDesign_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s); Stop send message due to first response was design to FAILED"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_AckStopAllSent(a0, a1) trace_StrandSimAgentMgr_AckStopAllSent_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_AckStopAllSent(a0, a1) trace_StrandSimAgentMgr_AckStopAllSent_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60009, trace_StrandSimAgentMgr_AckStopAllSent_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: self (%p). Total (%d) Ack(s); Stop send message due to all message were sent"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_AckPostIndication(a0, a1) trace_StrandSimAgentMgr_AckPostIndication_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_AckPostIndication(a0, a1) trace_StrandSimAgentMgr_AckPostIndication_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60010, trace_StrandSimAgentMgr_AckPostIndication_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: self (%p). Post Indication Message (%p)"), Strand *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_AckPostFinal(a0, a1) trace_StrandSimAgentMgr_AckPostFinal_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_AckPostFinal(a0, a1) trace_StrandSimAgentMgr_AckPostFinal_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60011, trace_StrandSimAgentMgr_AckPostFinal_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Ack: self (%p). Post final message (%p)"), Strand *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_Cancel(a0, a1) trace_StrandSimAgentMgr_Cancel_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_Cancel(a0, a1) trace_StrandSimAgentMgr_Cancel_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60012, trace_StrandSimAgentMgr_Cancel_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Cancel: self (%p). Total (%d) Cancel"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_CancelFinalMessage(a0, a1) trace_StrandSimAgentMgr_CancelFinalMessage_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_CancelFinalMessage(a0, a1) trace_StrandSimAgentMgr_CancelFinalMessage_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60013, trace_StrandSimAgentMgr_CancelFinalMessage_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Cancel: self (%p). Post final message (%p)"), Strand *, Message *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_StrandSimAgentMgr_Finished(a0, a1) trace_StrandSimAgentMgr_Finished_Impl(__FILE__, __LINE__, a0, a1)
#else
#define trace_StrandSimAgentMgr_Finished(a0, a1) trace_StrandSimAgentMgr_Finished_Impl(0, 0, a0, a1)
#endif
FILE_EVENTD2(60014, trace_StrandSimAgentMgr_Finished_Impl, LOG_VERBOSE, PAL_T("_StrandSimAgentMgr_Finished: self (%p). Total (%d) Finished"), Strand *, int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UT_HandleRequest(a0, a1, a2, a3) trace_UT_HandleRequest_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3)
#else
#define trace_UT_HandleRequest(a0, a1, a2, a3) trace_UT_HandleRequest_Impl(0, 0, a0, a1, tcs(a2), a3)
#endif
FILE_EVENTD4(60015, trace_UT_HandleRequest_Impl, LOG_VERBOSE, PAL_T("_UT_HandleRequest: context (%p), msg (%p:%T), interaction(%p)"), void *, Message *, const TChar *, Interaction *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_UT_HandleRequestFailed(a0, a1, a2, a3, a4) trace_UT_HandleRequestFailed_Impl(__FILE__, __LINE__, a0, a1, tcs(a2), a3, a4)
#else
#define trace_UT_HandleRequestFailed(a0, a1, a2, a3, a4) trace_UT_HandleRequestFailed_Impl(0, 0, a0, a1, tcs(a2), a3, a4)
#endif
FILE_EVENTD5(60016, trace_UT_HandleRequestFailed_Impl, LOG_VERBOSE, PAL_T("_UT_HandleRequest: context (%p), msg (%p:%T), interaction(%p); Failed with result (%d)"), void *, Message *, const TChar *, Interaction *, MI_Result)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_Post(a0) trace_Server_Post_Impl(__FILE__, __LINE__, a0)
#else
#define trace_Server_Post(a0) trace_Server_Post_Impl(0, 0, a0)
#endif
FILE_EVENTD1(60017, trace_Server_Post_Impl, LOG_VERBOSE, PAL_T("_Server_Post: message tag: %d"), MI_Uint32)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_Ack() trace_Server_Ack_Impl(__FILE__, __LINE__)
#else
#define trace_Server_Ack() trace_Server_Ack_Impl(0, 0)
#endif
FILE_EVENTD0(60018, trace_Server_Ack_Impl, LOG_VERBOSE, PAL_T("_Server_Ack"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_Close() trace_Server_Close_Impl(__FILE__, __LINE__)
#else
#define trace_Server_Close() trace_Server_Close_Impl(0, 0)
#endif
FILE_EVENTD0(60019, trace_Server_Close_Impl, LOG_VERBOSE, PAL_T("_Server_Close"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_Server_Finish() trace_Server_Finish_Impl(__FILE__, __LINE__)
#else
#define trace_Server_Finish() trace_Server_Finish_Impl(0, 0)
#endif
FILE_EVENTD0(60020, trace_Server_Finish_Impl, LOG_VERBOSE, PAL_T("_Server_Finish"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe() trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe_Impl(__FILE__, __LINE__)
#else
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe() trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe_Impl(0, 0)
#endif
FILE_EVENTD0(60021, trace_TestMgr_Subscribe_Unsubscribe_Cancel_Unsubscribe_Impl, LOG_VERBOSE, PAL_T("TestMgr_Subscribe_Unsubscribe_Cancel: Unsubscribe"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel() trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel_Impl(__FILE__, __LINE__)
#else
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel() trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel_Impl(0, 0)
#endif
FILE_EVENTD0(60022, trace_TestMgr_Subscribe_Unsubscribe_Cancel_Cancel_Impl, LOG_VERBOSE, PAL_T("TestMgr_Subscribe_Unsubscribe_Cancel: Cancel"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule(a0) trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule_Impl(__FILE__, __LINE__, a0)
#else
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule(a0) trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule_Impl(0, 0, a0)
#endif
FILE_EVENTD1(60023, trace_TestMgr_Subscribe_Unsubscribe_Cancel_Schedule_Impl, LOG_VERBOSE, PAL_T("TestMgr_Subscribe_Unsubscribe_Cancel: schedule cancel on protocol (%p)"), void *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers() trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers_Impl(__FILE__, __LINE__)
#else
#define trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers() trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers_Impl(0, 0)
#endif
FILE_EVENTD0(60024, trace_TestMgr_Subscribe_Unsubscribe_Cancel_FinalizeAgentManagers_Impl, LOG_VERBOSE, PAL_T("TestMgr_Subscribe_Unsubscribe_Cancel: Finalize Agent Managers"))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_EncryptionFailed() trace_HTTP_EncryptionFailed_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_EncryptionFailed() trace_HTTP_EncryptionFailed_Impl(0, 0)
#endif
FILE_EVENTD0(60000, trace_HTTP_EncryptionFailed_Impl, LOG_DEBUG, PAL_T("HTTP: Encryption failed."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_GssStatus(a0, a1, a2) trace_HTTP_GssStatus_Impl(__FILE__, __LINE__, a0, scs(a1), a2)
#else
#define trace_HTTP_GssStatus(a0, a1, a2) trace_HTTP_GssStatus_Impl(0, 0, a0, scs(a1), a2)
#endif
FILE_EVENTD3(60001, trace_HTTP_GssStatus_Impl, LOG_DEBUG, PAL_T("HTTP: GSSstatus. gss:(%.*%s) mech:(%s) min_status:(%x)"), const int, const char *, const int)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_GssNtlmStatus(a0, a1) trace_HTTP_GssNtlmStatus_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_HTTP_GssNtlmStatus(a0, a1) trace_HTTP_GssNtlmStatus_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENTD2(60002, trace_HTTP_GssNtlmStatus_Impl, LOG_DEBUG, PAL_T("HTTP: gss ntlm status:(%s) username:(%s)"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_GssError(a0) trace_HTTP_GssError_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_GssError(a0) trace_HTTP_GssError_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60003, trace_HTTP_GssError_Impl, LOG_DEBUG, PAL_T("HTTP: gss error:(%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_GetAddrInfoError(a0) trace_HTTP_GetAddrInfoError_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_GetAddrInfoError(a0) trace_HTTP_GetAddrInfoError_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60004, trace_HTTP_GetAddrInfoError_Impl, LOG_DEBUG, PAL_T("HTTP: get addr info error:(%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_LoadGssFailed(a0) trace_HTTP_LoadGssFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_LoadGssFailed(a0) trace_HTTP_LoadGssFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60005, trace_HTTP_LoadGssFailed_Impl, LOG_DEBUG, PAL_T("HTTP: Gss Library Load Failed:(%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_GssFunctionNotPresent(a0) trace_HTTP_GssFunctionNotPresent_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_GssFunctionNotPresent(a0) trace_HTTP_GssFunctionNotPresent_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60006, trace_HTTP_GssFunctionNotPresent_Impl, LOG_DEBUG, PAL_T("HTTP: Gss Function Not Present:(%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_AuthMallocFailed(a0) trace_HTTP_AuthMallocFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_AuthMallocFailed(a0) trace_HTTP_AuthMallocFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60007, trace_HTTP_AuthMallocFailed_Impl, LOG_DEBUG, PAL_T("HTTP: Authorization Malloc Failed:(%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_CryptInvalidArg(a0, a1) trace_HTTP_CryptInvalidArg_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_HTTP_CryptInvalidArg(a0, a1) trace_HTTP_CryptInvalidArg_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENTD2(60008, trace_HTTP_CryptInvalidArg_Impl, LOG_DEBUG, PAL_T("HTTP: Http_Encrypt/Decrpyt invalid arg:(%s %s)"), const char *, const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_UserAuthFailed(a0) trace_HTTP_UserAuthFailed_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_UserAuthFailed(a0) trace_HTTP_UserAuthFailed_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60009, trace_HTTP_UserAuthFailed_Impl, LOG_DEBUG, PAL_T("HTTP: User Authorization failed. (%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_AuthComplete() trace_HTTP_AuthComplete_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_AuthComplete() trace_HTTP_AuthComplete_Impl(0, 0)
#endif
FILE_EVENTD0(60010, trace_HTTP_AuthComplete_Impl, LOG_DEBUG, PAL_T("HTTP: Authorization Complete."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_AuthContinue() trace_HTTP_AuthContinue_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_AuthContinue() trace_HTTP_AuthContinue_Impl(0, 0)
#endif
FILE_EVENTD0(60011, trace_HTTP_AuthContinue_Impl, LOG_DEBUG, PAL_T("HTTP: Authorization Continue."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_LoadingGssApi(a0) trace_HTTP_LoadingGssApi_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_LoadingGssApi(a0) trace_HTTP_LoadingGssApi_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60012, trace_HTTP_LoadingGssApi_Impl, LOG_DEBUG, PAL_T("HTTP: Loading gss api. (%s)"), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_SendNextAuthReply() trace_HTTP_SendNextAuthReply_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_SendNextAuthReply() trace_HTTP_SendNextAuthReply_Impl(0, 0)
#endif
FILE_EVENTD0(60013, trace_HTTP_SendNextAuthReply_Impl, LOG_DEBUG, PAL_T("HTTP: Send Next Auth Reply."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_InvalidAuthToken() trace_HTTP_InvalidAuthToken_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_InvalidAuthToken() trace_HTTP_InvalidAuthToken_Impl(0, 0)
#endif
FILE_EVENTD0(60014, trace_HTTP_InvalidAuthToken_Impl, LOG_DEBUG, PAL_T("HTTP Auth: Input Token Invalid."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_SupplimentaryInfo(a0) trace_HTTP_SupplimentaryInfo_Impl(__FILE__, __LINE__, scs(a0))
#else
#define trace_HTTP_SupplimentaryInfo(a0) trace_HTTP_SupplimentaryInfo_Impl(0, 0, scs(a0))
#endif
FILE_EVENTD1(60015, trace_HTTP_SupplimentaryInfo_Impl, LOG_DEBUG, PAL_T("HTTP Auth: SupplimentaryInfo: (%s)."), const char *)
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_CannotBuildAuthResponse() trace_HTTP_CannotBuildAuthResponse_Impl(__FILE__, __LINE__)
#else
#define trace_HTTP_CannotBuildAuthResponse() trace_HTTP_CannotBuildAuthResponse_Impl(0, 0)
#endif
FILE_EVENTD0(60016, trace_HTTP_CannotBuildAuthResponse_Impl, LOG_DEBUG, PAL_T("HTTP Auth: Cannot build response."))
#if defined(CONFIG_ENABLE_DEBUG)
#define trace_HTTP_StatusMsg(a0, a1) trace_HTTP_StatusMsg_Impl(__FILE__, __LINE__, scs(a0), scs(a1))
#else
#define trace_HTTP_StatusMsg(a0, a1) trace_HTTP_StatusMsg_Impl(0, 0, scs(a0), scs(a1))
#endif
FILE_EVENTD2(60017, trace_HTTP_StatusMsg_Impl, LOG_DEBUG, PAL_T("HTTP: (%s):(%s)"), const char *, const char *)
