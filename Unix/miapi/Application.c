/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "miapi_common.h"
#include "Application.h"
#include "Session.h"
#include "Operation.h"
#include "HostedProvider.h"
#include "SafeHandle.h"
#include "ChildList.h"
#include "ProtocolHandlerCache.h"
#include "Options.h"
#include <MI.h>
#include <pal/intsafe.h>
#include <pal/atomic.h>
#include <pal/lock.h>
#include <pal/format.h>
#include <base/instance.h>
#include <base/class.h>
#include <omi_error/OMI_Error.h>
#include <omi_error/omierror.h>
#include <codec/common/micodec.h>
//#include <common\propertySet.h>
//#include "XmlDeserializer.h"
#include "xmlserializer/xmlserializer.h"
#include <base/conf.h>
#include <base/paths.h>
#include <base/log.h>

//Used for application user ref count
#define ActiveBit 0x80000000
#define CountMask 0x7fffffff

/* Component for debug traces */
//LPWSTR componentName = L"MI_Client";


/* Define for real at end of file */
extern const MI_ApplicationFT g_applicationFT;
extern const MI_ApplicationFT g_applicationFT_OOM;

/* Real back-end MI_Application structure */
typedef struct _ApplicationObject
{
    ThunkHandleManager thunkManager; /* Needs to be aligned so always first in this structure */

    ChildList sessionList; /* Child sessions */
    ChildList hostedProviderList; /* Child hosted providers */
    ProtocolHandlerCache protocolHandlerCache; /* Holds active protocol handlers */

    volatile ptrdiff_t callersRefCount;

    //Our copy.  May be NULL
    MI_Char *applicationID;
} ApplicationObject;

/* Reads config file options: loglevel */
static MI_Result _GetLogOptionsFromConfigFile()
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;
    char logpath[PAL_MAX_PATH_SIZE];
    char logfile[PAL_MAX_PATH_SIZE];

    /* Form the configuration file path */
    Strlcpy(path, OMI_GetPath(ID_CLIENTCONFIGFILE), sizeof(path));
    Strlcpy(logpath, OMI_GetPath(ID_LOGDIR), PAL_MAX_PATH_SIZE);
    Strlcat(logpath, "/", PAL_MAX_PATH_SIZE);

    Strlcpy(logfile, "miclient.log", sizeof(logfile));

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        trace_MIFailedToOpenConfigFile(scs(path));
        return MI_RESULT_FAILED;
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            trace_MIFailedToReadConfigValue(path, scs(Conf_Error(conf)));
            goto error;
        }

        if (r == 1)
            break;

        if (strcmp(key, "loglevel") == 0)
        {
            if (Log_SetLevelFromString(value) != 0)
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
#if defined(OILOGSYSTEM_FILE)
        else if (strcmp(key, "logpath") == 0)
        {
            if (Strlcpy(logpath, value, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "logfile") == 0)
        {
            if (Strlcpy(logfile, value, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
#endif
    }

#if defined(OILOGSYSTEM_FILE)
    {
        ZChar pathtolog[PAL_MAX_PATH_SIZE];
        pathtolog[0] = 0;
        if (TcsStrlcpy(pathtolog, logpath, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        {
            trace_MIClient_OutOfMemory();
            goto error;
        }
        if (TcsStrlcat(pathtolog, logfile, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        {
            trace_MIClient_OutOfMemory();
            goto error;
        }

        if (Log_Open(pathtolog) != MI_RESULT_OK)
            goto error;
    }
#endif

    /* Close configuration file */
    Conf_Close(conf);

    return MI_RESULT_OK;

error:
    Conf_Close(conf);
    return MI_RESULT_INVALID_PARAMETER;
}

/* PUBLIC Application_NewGenericHandle
 * Retrieve a new generic handler.  This is a generic version of MI_Application/MI_Session/etc.
 * To recycle the handler back into the pool do this:
 *      ThunkHandle_Shutdown(genericHandle->thunkHandle);
 * application - top-level application that the handle will be attached to
 * handle - resultant handler
 *
 * Return code: MI_Result code
 */
MI_Result Application_NewGenericHandle(_Inout_ MI_Application *application, _Out_ GenericHandle *handle)
{
    ThunkHandle *thunkHandle = NULL;
    MI_Result miResult;

    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;
    miResult = ThunkHandleManager_GetHandle(&applicationObject->thunkManager, &thunkHandle);
    if (miResult == MI_RESULT_OK)
    {
        handle->thunkHandle = thunkHandle;
        handle->version = thunkHandle->version;
        handle->functionTable = NULL;
        }

    return miResult;
}

/*=============================================================================================
 * PUBLIC: Create a real application object and have the client point to it. This is the
 * primary DLL export for the client API.
 *=============================================================================================
 */
#define MI_LINKAGE MI_EXPORT

MI_LINKAGE MI_Result MI_MAIN_CALL MI_Application_InitializeV1(
               MI_Uint32 flags,
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *application)
{
    ApplicationObject *applicationObject;
    size_t applicationIDLength = 0;
    MI_Result miResult;

    /* Before we do anything zap the extended error if it is being asked for */
    if (extendedError != NULL)
    {
        *extendedError = NULL;
    }

    /* Minimal check of parameters before we zero out the application structure */
    if (application == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if(MI_RESULT_OK != _GetLogOptionsFromConfigFile())
    {
        NitsIgnoringError();
    }

    /* Zero out the application structure so if it fails it can still be passed
     * through to the MI_Application_Close function
     */
    memset(application, 0, sizeof(MI_Application));

    /* Rest of parameter validation */
    if (flags != 0)
    {
        application->ft = &g_applicationFT_OOM;
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Allocate the real back-end application object */
    applicationObject = (ApplicationObject*) _aligned_malloc(sizeof(ApplicationObject), MEMORY_ALLOCATION_ALIGNMENT);
    if (applicationObject == NULL)
    {
        application->ft = &g_applicationFT_OOM;
        return MI_RESULT_FAILED;
    }

    memset(applicationObject, 0, sizeof(ApplicationObject));

    applicationObject->callersRefCount = ActiveBit;

    miResult = ChildList_Initialize(&applicationObject->sessionList);
    if (miResult != MI_RESULT_OK)
    {
        application->ft = &g_applicationFT_OOM;
        _aligned_free(applicationObject);
        return miResult;
    }

    miResult = ChildList_Initialize(&applicationObject->hostedProviderList);
    if (miResult != MI_RESULT_OK)
    {
        ChildList_DeInitialize(&applicationObject->sessionList);
        application->ft = &g_applicationFT_OOM;
        _aligned_free(applicationObject);
        return miResult;
    }

    /* Initialize the free list for all RealHandle objects */
    ThunkHandleManager_Initialize(&applicationObject->thunkManager);

    if (applicationID)
    {
        applicationObject->applicationID = NULL;

        if (SizeTAdd(Tcslen(applicationID), 1, &applicationIDLength) == S_OK &&
            SizeTMult(applicationIDLength, sizeof(MI_Char), &applicationIDLength) == S_OK)
        {
            applicationObject->applicationID = (MI_Char*) PAL_Malloc(applicationIDLength);
        }

        if (applicationObject->applicationID == NULL)
        {
            ChildList_DeInitialize(&applicationObject->sessionList);
            ChildList_DeInitialize(&applicationObject->hostedProviderList);
            _aligned_free(applicationObject);
            application->ft = &g_applicationFT_OOM;
            return MI_RESULT_FAILED;
        }
        memcpy(applicationObject->applicationID, applicationID, applicationIDLength);
    }

    miResult = ProtocolHandlerCache_Initialize(applicationObject->applicationID, &applicationObject->protocolHandlerCache);
    if (miResult != MI_RESULT_OK)
    {
        ChildList_DeInitialize(&applicationObject->sessionList);
        ChildList_DeInitialize(&applicationObject->hostedProviderList);
        PAL_Free(applicationObject->applicationID);
        _aligned_free(applicationObject);
        application->ft = &g_applicationFT_OOM;
        return miResult;
    }

    /* Set up the client handle */
    application->reserved1 = 1;
    application->reserved2 = (ptrdiff_t) applicationObject;
    application->ft = &g_applicationFT;

    trace_MIClient_AppInit(application, applicationObject);

    return MI_RESULT_OK;
}

MI_Result Application_RegisterSession(
    _Inout_ MI_Application *application,
    _Inout_ ChildListNode *session)
{
    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;
    return ChildList_AddNode(&applicationObject->sessionList, session);
}

_Check_return_ long Application_AddRef(_Inout_ ApplicationObject *applicationObject)
{
    ptrdiff_t n;
    for (n = applicationObject->callersRefCount; n & ActiveBit; n = applicationObject->callersRefCount)
    {
        if (Atomic_CompareAndSwap(&applicationObject->callersRefCount, n, n + 1) == n)
        {
            /*We incremented the count and we weren't cancelled so return success.*/
            return 1;
        }
    }
    /*Another thread called Shutdown() so return false.*/
    return 0;
}

long Application_Release(_Inout_ ApplicationObject *applicationObject)
{
    ptrdiff_t n;

    n = Atomic_Dec(&applicationObject->callersRefCount);

    if (n == 0)
    {
        //We are done.  We now need to trigger the shutdown caller to wake up in case it is blocked on us
        CondLock_Broadcast((ptrdiff_t) applicationObject);
}

    return n & CountMask;
}

long Application_Shutdown(_Inout_ ApplicationObject *applicationObject)
{
    ptrdiff_t n;
    for (n = applicationObject->callersRefCount; n & ActiveBit; n = applicationObject->callersRefCount)
    {
        if (Atomic_CompareAndSwap(&applicationObject->callersRefCount, n, n & CountMask) == n)
        {
            //We are done!  We were the one who won  Now wait until the refcount hits zero
            ptrdiff_t curCallerCount = applicationObject->callersRefCount;
            while (curCallerCount)
            {
                /* Wait for operations to finish */
                CondLock_Wait((ptrdiff_t)applicationObject, &applicationObject->callersRefCount, curCallerCount, CONDLOCK_DEFAULT_SPINCOUNT);
                curCallerCount = applicationObject->callersRefCount;
            }
            return 1;
        }
    }

    /*Another thread cleared ActiveBit. That is rather worrisom*/
    return 0;
}

MI_Result Application_UnregisterSession(
    _Inout_ MI_Application *application,
    _Inout_ ChildListNode *session)
{
    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;
    ChildList_RemoveNode(&applicationObject->sessionList, session);

    return MI_RESULT_OK;
}

MI_Result Application_RegisterHostedProvider(
    _Inout_ MI_Application *application,
    _Inout_ ChildListNode *hostedProvider)
{
    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;
    return ChildList_AddNode(&applicationObject->hostedProviderList, hostedProvider);
}

MI_Result Application_UnregisterHostedProvider(
    _Inout_ MI_Application *application,
    _Inout_ ChildListNode *hostedProvider)
{
    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;
    ChildList_RemoveNode(&applicationObject->hostedProviderList, hostedProvider);

    return MI_RESULT_OK;
}

void Application_AllSessionsShutdown(void *context)
{
    ApplicationObject *applicationObject = (ApplicationObject *) context;
    CondLock_Broadcast((ptrdiff_t)applicationObject);
}

void Application_AllHostedProvidersShutdown(void *context)
{
    ApplicationObject *applicationObject = (ApplicationObject *) context;
    CondLock_Broadcast((ptrdiff_t)applicationObject);
}
/* MI_Application_Close implementation for transport API.
 */
_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_Close(
    _In_ MI_Application *application)
{
    /* Copy of client application so we can clear out theirs as soon as possible */
    ApplicationObject *applicationObject;

    if ((application == NULL) || (application->ft == NULL) ||
        (application->reserved2 == 0) || (application->reserved1 != 1))
    {
        /* Probably already deleted or failed to initialize */
        return MI_RESULT_INVALID_PARAMETER;
    }

    applicationObject = (ApplicationObject*) application->reserved2;

    trace_MIClient_AppClose(application, applicationObject);

    Application_Shutdown(applicationObject);

    /* clear the client handle */
    memset(application, 0, sizeof(MI_Application));

    /* Checking the application is somewhat pointless as once we are deleted the real handle
     * will be deleted anyway!
     */

    /* Signal that all sessions need to shutdown */
    {
        ChildListOutstandingHandles _smallBuffer[100];
        ChildListOutstandingHandles* outstandingSessions = _smallBuffer;
        ptrdiff_t outstandingSessionsSize = sizeof(_smallBuffer)/sizeof(_smallBuffer[0]);
        ptrdiff_t outstandingSessionsCount;

        int r = ChildList_Shutdown(&applicationObject->sessionList);
        if (r)
        {
            //We were the winner for doing the shutdown

            r = ChildList_GetCurrentList(&applicationObject->sessionList, outstandingSessions, (MI_Uint32)outstandingSessionsSize, &outstandingSessionsCount);
            if (r == 0 && (outstandingSessionsCount > outstandingSessionsSize))
            {
                outstandingSessions = PAL_Malloc(outstandingSessionsCount*sizeof(ChildListOutstandingHandles));
                if (outstandingSessions == NULL)
                {
                    //NitsAssert(outstandingSessions != NULL, MI_T("ignored memory allocation on purpose"));
                    //Note that we cannot cancel the sessions.
                    //It is completely up to the client to close all sessions in this case and it will cause it to not respond if they do not
                }
                else
                {
                    outstandingSessionsSize = outstandingSessionsCount;
                    r = ChildList_GetCurrentList(&applicationObject->sessionList, outstandingSessions, (MI_Uint32)outstandingSessionsSize, &outstandingSessionsCount);
                }
            }
            /* Cancel all child sessions */
            if (r)
            {
    #ifdef _PREFAST_
     #pragma prefast(push)
     #pragma prefast(disable:26015)
    #endif
                while (outstandingSessionsCount)
                {
                    MI_Session *session = (MI_Session*)&outstandingSessions[outstandingSessionsCount-1].clientHandle;

                    trace_MIClient_AppCloseCancelingAll(application, applicationObject, outstandingSessions[outstandingSessionsCount-1].debugHandlePointer);

                    /* Mode to next one as cancel may cause current operation to get deleted */
                    outstandingSessionsCount--;

                    Session_CancelAllOperations(session);
                }
    #ifdef _PREFAST_
     #pragma prefast(pop)
    #endif
            }
            if (outstandingSessions != _smallBuffer)
            {
                PAL_Free(outstandingSessions);
            }

            ChildList_RegisterShutdownCallback(&applicationObject->sessionList, Application_AllSessionsShutdown, applicationObject);
        }
    }


    /* Wait for child sessions to shut down */
    {
        ptrdiff_t curChildCount = applicationObject->sessionList.childCount;
        while (curChildCount)
        {
            trace_MIClient_AppCloseWaitingOnSessions(application, applicationObject, curChildCount);
            /* Wait for child session count to hit 0 */
            CondLock_Wait((ptrdiff_t)applicationObject, &applicationObject->sessionList.childCount, curChildCount, CONDLOCK_DEFAULT_SPINCOUNT);
            curChildCount = applicationObject->sessionList.childCount;
        }
    }

    ChildList_RegisterShutdownCallback(&applicationObject->hostedProviderList, Application_AllHostedProvidersShutdown, applicationObject);
    {
        ptrdiff_t curChildCount = applicationObject->hostedProviderList.childCount;
        while (curChildCount)
        {
            trace_MIClient_AppCloseWaitingOnHostedProviders(application, applicationObject, curChildCount);
            /* Wait for child hosted provider count to hit 0 */
            CondLock_Wait((ptrdiff_t)applicationObject, &applicationObject->hostedProviderList.childCount, curChildCount, CONDLOCK_DEFAULT_SPINCOUNT);
            curChildCount = applicationObject->hostedProviderList.childCount;
        }
    }

    /* Deinitialize the handle free-list */
    ThunkHandleManager_DeInitialize(&applicationObject->thunkManager);

    /* Deinitialize cache manager.  All operations are be finished by now */
    ProtocolHandlerCache_DeInitialize(&applicationObject->protocolHandlerCache);

    /* Free our copy of application ID */
    PAL_Free(applicationObject->applicationID);

    ChildList_DeInitialize(&applicationObject->sessionList);
    ChildList_DeInitialize(&applicationObject->hostedProviderList);


    /* Delete the real application handle */
    _aligned_free(applicationObject);

    trace_MIClient_AppCloseCompleted(application, applicationObject);

#if defined(OILOGSYSTEM_FILE)
    //TODO: Refactor MI logging as a file can get tramped if someone is using an MI app and then closes after someone else has open a different MI App
    // For now we just remove closing of the log as that doesnt have any effect (logs are flushed on every trace)
    Log_Close();
#endif

    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_NewPropertySet(
    _In_     MI_Application *application,
    _Out_ MI_PropertySet **propertySet)
{
    if ((application == NULL) || (propertySet == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
#if 0
    return PropertySet_New(propertySet);
#endif
    return MI_RESULT_NOT_SUPPORTED;
}
/* MI_Application_NewInstance implementation */
_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_NewInstance(
    _In_     MI_Application *application,
    _In_opt_z_ const MI_Char * className,
    _In_opt_ const MI_ClassDecl *classRTTI,
    _Out_    MI_Instance **instance)
{
    if ((application == NULL) || (instance == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (classRTTI)
    {
        return Instance_New(instance, classRTTI, NULL);
    }
    else
    {
        return Instance_NewDynamic(
            instance,
            className,
            MI_FLAG_CLASS /* TODO: API UPDATE... May be association/indication/etc */,
            NULL
            );
    }
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_NewInstanceFromClass(
    _In_     MI_Application *application,
    _In_opt_z_ const MI_Char * className,
    _In_opt_ const MI_Class *classObject,
    _Out_    MI_Instance **instance)
{
    const MI_ClassDecl *classDecl = NULL;
    if (classObject)
        classDecl = classObject->classDecl;

    return Application_NewInstance(application, className, classDecl, instance);
}

MI_Result MI_CALL Application_NewClass (
    _In_ MI_Application* application,
    _In_ const MI_ClassDecl* classDecl,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Outptr_ MI_Class** classObject)
{
    return Class_New(classDecl, namespaceName, serverName, classObject);
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_NewSession(
    _In_     MI_Application *application,
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session)
{
    MI_Result result = MI_RESULT_INVALID_PARAMETER;
    ApplicationObject *applicationObject;

    trace_MIApplicationEnter(__FUNCTION__, application, protocol, destination, session);

    if ((application == NULL) || (application->ft == NULL) ||
        (application->reserved2 == 0) || (application->reserved1 != 1))
    {
        /* Probably already deleted or failed to initialize */
        trace_MILeaveSession(__FUNCTION__, session);
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (extendedError)
        *extendedError = NULL;

    applicationObject = (ApplicationObject*) application->reserved2;

    if (Application_AddRef(applicationObject))
    {
        result = Session_Create(application, protocol,destination,options,callbacks,extendedError,session);

        Application_Release(applicationObject);
    }

    trace_MILeavingSession(__FUNCTION__, session);
    return result;
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Application_NewHostedProvider(
    _In_  MI_Application *application,
    _In_z_  const MI_Char * namespaceName,
    _In_z_  const MI_Char * providerName,
    _In_  MI_MainFunction mi_Main,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_HostedProvider *hostedProvider)
{
    if ((application == NULL) || (application->ft == NULL) ||
        (application->reserved2 == 0) || (application->reserved1 != 1))
    {
        /* Probably already deleted or failed to initialize */
        return MI_RESULT_INVALID_PARAMETER;
    }

    return HostedProvider_Create(application, namespaceName, providerName, mi_Main, extendedError, hostedProvider);
}

/* Used by test infrastructure to set a default protocol handler
 */
_Success_(return == MI_RESULT_OK)
MI_EXTERN_C MI_Result Application_SetTestTransport(
    _Inout_ MI_Application *clientMiApplication,
    _In_z_ const char *protocolHandlerName,
    _In_z_ const char *protocolHandlerDLL,
    _In_z_ const char *protocolHandlerDllEntryPoint,
    MI_Uint32 protocolHandlerMajorVersion,
    MI_Uint32 protocolHandlerMinorVersion,
    MI_Boolean overrideDefaultLocalTransport,
    MI_Boolean overrideDefaultRemoteTransport)
{
    ApplicationObject *applicationObject = (ApplicationObject*) clientMiApplication->reserved2;
    ProtocolHandlerCacheItem *cacheItem = NULL;
    MI_Result miResult;

    /* Set test handler */
    miResult = ProtocolHandlerCache_InsertProtocolEntries(&applicationObject->protocolHandlerCache, protocolHandlerName, protocolHandlerDLL, protocolHandlerDllEntryPoint, protocolHandlerMajorVersion, protocolHandlerMinorVersion, &cacheItem);
    if (miResult == MI_RESULT_OK)
    {
        if (overrideDefaultLocalTransport)
            applicationObject->protocolHandlerCache.defaultLocalItem = cacheItem;
        if (overrideDefaultRemoteTransport)
            applicationObject->protocolHandlerCache.defaultRemoteItem = cacheItem;
    }
    return miResult;
}

/* PUBLIC: Application_GetProtocolHandler
 * Retrieve the MI_Application of a protocol handler.  If protocol handler
 * is not loaded this function will load it.
 * It is not valid to have destination and protocolHandler NULL.  It needs
 * one to determine which handler to use.
 *
 * application - top-level application that the handler is attached to
 * destination - For local this should be NULL or empty string.  If protocol
 *               handler is NULL it will pick the default for local/remote
 *               destination.
 * protocolHandler - If specified is the protocol handler string.
 * protocolHandlerApplication - MI_Application for the protocll handler
 *               exposing the function table to the handler.
 *
 * Return code: MI_Result code
 */
_Success_(return == MI_RESULT_OK)
MI_Result Application_GetProtocolHandler(
    _In_ MI_Application *application,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_z_ const MI_Char *protocolHandler,
    _Outptr_ ProtocolHandlerCacheItem **protocolHandlerItem)
{
    ApplicationObject *applicationObject = (ApplicationObject*) application->reserved2;

    if (protocolHandler == NULL)
    {
        if (destination == NULL)
        {
            if (applicationObject->protocolHandlerCache.defaultLocalItem)
                protocolHandler = applicationObject->protocolHandlerCache.defaultLocalItem->name;
            else
                protocolHandler = MI_T("OMI_SOCKETS");
        }
        else
        {
            if (applicationObject->protocolHandlerCache.defaultRemoteItem)
                protocolHandler = applicationObject->protocolHandlerCache.defaultRemoteItem->name;
            else
                protocolHandler = MI_T("MI_REMOTE_WSMAN");
        }
    }

    /* Load protocol handler */
    return ProtocolHandlerCache_GetProtocolHandler(&applicationObject->protocolHandlerCache, protocolHandler, protocolHandlerItem);
}

MI_ErrorCategory MI_CALL Utilities_MapErrorToMiErrorCategory(_In_z_ const MI_Char *errorType, MI_Uint32 error)
{
    return ErrorCategoryFromErrorCode(error, errorType);
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Utilities_CimErrorFromErrorCode(MI_Uint32 errorCode,_In_z_ const MI_Char *errorType,
                                                  _In_z_ const MI_Char* errorMessage, _Outptr_opt_result_maybenull_ MI_Instance **cimError)
{
    return OMI_ErrorFromErrorCode(NULL, errorCode, errorType, errorMessage, (OMI_Error**)cimError);
}

/* Wrapper function to dispatch proper serializer codec */
MI_Result MI_CALL Serializer_Create(
    _In_ MI_Application *application,
    MI_Uint32 flags,
    _In_z_ MI_Char *format,
    _Out_ MI_Serializer *serializer)
{
    if ((application == NULL) || (flags != 0) || (format == NULL) || (serializer == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (Tcscmp(format, PAL_T("MI_XML")) == 0)
    {
        return XmlSerializer_Create(application, flags, format, serializer);
    }
    if (Tcscmp(format, MOFCODEC_FORMAT) == 0)
    {
        return MI_Application_NewSerializer_Mof(application, flags, format, serializer);
    }

    return MI_RESULT_NOT_SUPPORTED;
}

/* Wrapper function to dispatch proper deserializer codec */
MI_Result MI_CALL Deserializer_Create(
    _In_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer)
{
    if ((application == NULL) || (flags != 0) || (format == NULL) || (deserializer == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
// TODO: Uncomment this when we want to support XML Deserialization
//    if (Tcscmp(format, PAL_T("MI_XML")) == 0)
//    {
//      return XmlDeserializer_Create(application, flags, format, deserializer);
//    }
    if (Tcscmp(format, MOFCODEC_FORMAT) == 0)
    {
        return MI_Application_NewDeserializer_Mof(application, flags, format, deserializer);
    }

    return MI_RESULT_NOT_SUPPORTED;
}


MI_Result MI_CALL Serializer_Close(
                                   _Inout_ MI_Serializer *serializer)
{
    if (serializer->reserved1 == cCodecMagic)
    {
        ExtFunctionTable* eft = (ExtFunctionTable *) serializer->reserved2;
        //MI_SerializerFT * ft = (MI_SerializerFT *)serializer->reserved2;
        return eft->ft.Close(serializer);
    }
    else
    {
        return XmlSerializer_Close(serializer);
    }
}

MI_Result MI_CALL Serializer_SerializeClass(
                                            _Inout_ MI_Serializer *serializer,
                                            MI_Uint32 flags,
                                            _In_ const MI_Class *classObject,
                                            _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
                                            MI_Uint32 clientBufferLength,
                                            _Inout_ MI_Uint32 *clientBufferNeeded)
{
    if (serializer->reserved1 == cCodecMagic)
    {
        ExtFunctionTable* eft = (ExtFunctionTable *) serializer->reserved2;
        return eft->ft.SerializeClass(serializer, flags, classObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
    else
    {
        return XmlSerializer_SerializeClass(serializer, flags, classObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
}

MI_Result MI_CALL Serializer_SerializeInstance(
                                               _Inout_ MI_Serializer *serializer,
                                               MI_Uint32 flags,
                                               _In_ const MI_Instance *instanceObject,
                                               _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
                                               MI_Uint32 clientBufferLength,
                                               _Inout_ MI_Uint32 *clientBufferNeeded)
{
    if (serializer->reserved1 == cCodecMagic)
    {
        ExtFunctionTable* eft = (ExtFunctionTable *) serializer->reserved2;
        return eft->ft.SerializeInstance(serializer, flags, instanceObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
    else
    {
        return XmlSerializer_SerializeInstance(serializer, flags, instanceObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
}

MI_Result MI_CALL Deserializer_Close(
                                     _Inout_ MI_Deserializer *deserializer)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->Close(deserializer);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}

MI_Result MI_CALL Deserializer_DeserializeClass(
                                                _Inout_   MI_Deserializer *deserializer,
                                                MI_Uint32 flags,
                                                _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
                                                MI_Uint32 serializedBufferLength,
                                                _In_opt_ MI_Class *parentClass,
                                                _In_opt_z_ const MI_Char *serverName,
                                                _In_opt_z_ const MI_Char *namespaceName,
                                                _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
                                                _In_opt_ void *classObjectNeededContext,
                                                _Out_opt_ MI_Uint32 *serializedBufferRead,
                                                _Outptr_opt_result_maybenull_ MI_Class **classObject,
                                                _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->DeserializeClass(deserializer, flags, serializedBuffer, serializedBufferLength, parentClass, serverName, namespaceName, classObjectNeeded, classObjectNeededContext, serializedBufferRead, classObject, cimErrorDetails);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}


MI_Result MI_CALL Deserializer_Class_GetClassName(
                                                  _Inout_ MI_Deserializer *deserializer,
                                                  _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
                                                  MI_Uint32 serializedBufferLength,
                                                  _Out_writes_opt_(*classNameLength) MI_Char *className,
                                                  _Inout_ MI_Uint32 *classNameLength,
                                                  _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->Class_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}

MI_Result MI_CALL Deserializer_Class_GetParentClassName(
                                                        _Inout_ MI_Deserializer *deserializer,
                                                        _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
                                                        MI_Uint32 serializedBufferLength,
                                                        _Out_writes_opt_(*parentClassNameLength) MI_Char *parentClassName,
                                                        _Inout_ MI_Uint32 *parentClassNameLength,
                                                        _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->Class_GetParentClassName(deserializer, serializedBuffer, serializedBufferLength, parentClassName, parentClassNameLength, cimErrorDetails);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}

MI_Result MI_CALL Deserializer_DeserializeInstance(
                                                   _Inout_ MI_Deserializer *deserializer,
                                                   MI_Uint32 flags,
                                                   _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
                                                   MI_Uint32 serializedBufferLength,
                                                   _In_reads_opt_(numberClassObjects) MI_Class **classObjects,
                                                   MI_Uint32 numberClassObjects,
                                                   _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
                                                   _In_opt_ void *classObjectNeededContext,
                                                   _Out_opt_ MI_Uint32 *serializedBufferRead,
                                                   _Outptr_opt_result_maybenull_ MI_Instance **instanceObject,
                                                   _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->DeserializeInstance(deserializer, flags, serializedBuffer, serializedBufferLength, classObjects, numberClassObjects, classObjectNeeded, classObjectNeededContext, serializedBufferRead, instanceObject, cimErrorDetails);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}

MI_Result MI_CALL Deserializer_Instance_GetClassName(
                                                     _Inout_ MI_Deserializer *deserializer,
                                                     _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
                                                     MI_Uint32 serializedBufferLength,
                                                     _Out_writes_opt_(*classNameLength) MI_Char *className,
                                                     _Inout_ MI_Uint32 *classNameLength,
                                                     _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if (deserializer->reserved1 == cCodecMagic)
    {
        MI_DeserializerFT * ft = (MI_DeserializerFT *)deserializer->reserved2;
        return ft->Instance_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }
    else
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
}

const MI_ApplicationFT g_applicationFT = {
    Application_Close,
    Application_NewSession,
    Application_NewHostedProvider,
    Application_NewInstance,
    DestinationOptions_Create,
    OperationOptions_Create,
    SubscriptionDeliveryOptions_Create,
    Serializer_Create,
    Deserializer_Create,
    Application_NewInstanceFromClass,
    Application_NewClass
};

/* Out of memory version of table */
const MI_ApplicationFT g_applicationFT_OOM = {
    Application_Close,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};


const MI_SessionFT _sessionFT =
{
    Session_Close,
    Session_GetApplication,
    Operation_Execute_GetInstance,
    Operation_Execute_ModifyInstance,
    Operation_Execute_CreateInstance,
    Operation_Execute_DeleteInstance,
    Operation_Execute_Invoke,
    Operation_Execute_EnumerateInstances,
    Operation_Execute_QueryInstances,
    Operation_Execute_AssociatorInstances,
    Operation_Execute_ReferenceInstances,
    Operation_Execute_Subscribe,
    Operation_Execute_GetClass,
    Operation_Execute_EnumerateClasses
};

const MI_OperationFT _operationFT =
{
    Operation_Close,
    Operation_Cancel,
    Operation_GetParentSession,
    Operation_GetInstance_Result,
    Operation_GetIndication_Result,
    Operation_GetClass_Result
};

const MI_HostedProviderFT _hostedProviderFT =
{
    HostedProvider_Close,
    HostedProvider_GetApplication
};

MI_SerializerFT _serializerFT =
{
    Serializer_Close,
    Serializer_SerializeClass,
    Serializer_SerializeInstance
};

const MI_DeserializerFT _deserializerFT =
{
    Deserializer_Close,
    Deserializer_DeserializeClass,
    Deserializer_Class_GetClassName,
    Deserializer_Class_GetParentClassName,
    Deserializer_DeserializeInstance,
    Deserializer_Instance_GetClassName
};

const MI_UtilitiesFT _utilitiesFT =
{
    Utilities_MapErrorToMiErrorCategory,
    Utilities_CimErrorFromErrorCode
} ;

const MI_ClientFT_V1 _v1_Functions =
{
    &g_applicationFT,
    &_sessionFT,
    &_operationFT,
    &_hostedProviderFT,
    &_serializerFT,
    &_deserializerFT,
    &g_subscriptionDeliveryOptionsFT,
    &g_destinationOptionsFT,
    &g_operationOptionsFT,
    &_utilitiesFT
};

MI_EXPORT const MI_ClientFT_V1 *mi_clientFT_V1 = &_v1_Functions;
