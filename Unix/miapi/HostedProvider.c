/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include <MI.h>
#include "Application.h"
#include "HostedProvider.h"

extern const MI_HostedProviderFT g_hostedProviderFT;

typedef struct _HostedProviderObject
{
    /* Linked list for child application hosted providers.  Includes clients hosted provider handle */
    ChildListNode hostedProviderNode;

    MI_Application clientApplication;

    ProtocolHandlerCacheItem *protocolHandlerItem;

    MI_HostedProvider protocolHandler_HP;
} HostedProviderObject;

/* When thunk handle ref count gets to zero means no one is referencing this object any more
 * so we can now delete the HostedProviderObject
 */
void HostedProvider_Destructor(
    _In_ ThunkHandle *thunkHandle)
{
    HostedProviderObject *hostedProviderObject = (HostedProviderObject*)thunkHandle->u.object;

    /* Unregister self from application */
    Application_UnregisterHostedProvider(&hostedProviderObject->clientApplication, &hostedProviderObject->hostedProviderNode);

    /* Free up object */
    PAL_Free(hostedProviderObject);
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL HostedProvider_Create(
    _In_  MI_Application *application,
    _In_z_  const MI_Char * namespaceName,
    _In_z_  const MI_Char * providerName,
    _In_  MI_MainFunction mi_Main,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_HostedProvider *hostedProvider)
{
    ProtocolHandlerCacheItem *protocolHandlerItem;
    HostedProviderObject *hpObject;
    MI_Result result;
    GenericHandle *genericHandle = (GenericHandle*) hostedProvider;

    if (hostedProvider)
    {
        memset(hostedProvider, 0, sizeof(MI_HostedProvider));
    }
    if (extendedError)
    {
        *extendedError = NULL;
    }
    if ((mi_Main == NULL) || (application == NULL) || (namespaceName == NULL) || (providerName == NULL) || (hostedProvider == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    result = Application_GetProtocolHandler(application, NULL, NULL, &protocolHandlerItem);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    if (protocolHandlerItem->application.ft->NewHostedProvider == NULL)
    {
        return MI_RESULT_NOT_SUPPORTED;
    }


    hpObject = PAL_Malloc(sizeof(HostedProviderObject));
    if (hpObject == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    memset(hpObject, 0, sizeof(HostedProviderObject));

    result = Application_NewGenericHandle(application, genericHandle);
    if (result != MI_RESULT_OK)
    {
        PAL_Free(hpObject);
        return result;
    }

    genericHandle->thunkHandle->u.object = hpObject;
    hpObject->clientApplication = *application;
    hpObject->protocolHandlerItem = protocolHandlerItem;
    hostedProvider->ft = &g_hostedProviderFT;

    hpObject->hostedProviderNode.clientHandle = *(GenericHandle*) hostedProvider;

    /* Need to register with application */
    result = Application_RegisterHostedProvider(application, &hpObject->hostedProviderNode);
    if (result != MI_RESULT_OK)
    {
        ThunkHandle_Shutdown(genericHandle->thunkHandle, HostedProvider_Destructor);
        hostedProvider->reserved1 = 0;
        hostedProvider->reserved2 = 0;
        hostedProvider->ft = NULL;
        return result;

    }

    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    result = protocolHandlerItem->application.ft->NewHostedProvider(&protocolHandlerItem->application, namespaceName, providerName, mi_Main, extendedError, &hpObject->protocolHandler_HP);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);
    if (result != MI_RESULT_OK)
    {
        ThunkHandle_Shutdown(genericHandle->thunkHandle, HostedProvider_Destructor);
        hostedProvider->reserved1 = 0;
        hostedProvider->reserved2 = 0;
        hostedProvider->ft = NULL;
    }
    return result;
}


MI_Result MI_CALL HostedProvider_Close(
        _In_  MI_HostedProvider *hostedProvider)
{
    MI_Result result = MI_RESULT_OK;
    if (hostedProvider)
    {
        GenericHandle *genericHandle = (GenericHandle*) hostedProvider;
        ThunkHandle *thunkHandle = NULL;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
        if (thunkHandle == NULL)
        {
            /* Failed means version was wrong or object was shutdown */
            return MI_RESULT_INVALID_PARAMETER;
        }

        /* Trigger shutdown */
        if (ThunkHandle_Shutdown(thunkHandle, HostedProvider_Destructor))
        {
            /* Only succeeds once so now call into provider */
            HostedProviderObject *hpObject = (HostedProviderObject*) thunkHandle->u.object;
            ProtocolHandlerCache_IncrementApiCount(hpObject->protocolHandlerItem);
            result = hpObject->protocolHandler_HP.ft->Close(&hpObject->protocolHandler_HP);
            ProtocolHandlerCache_DecrementApiCount(hpObject->protocolHandlerItem);
        }
        ThunkHandle_Release(thunkHandle);
    }
    return result;
}

MI_Result MI_CALL HostedProvider_GetApplication(
        _In_  MI_HostedProvider *hostedProvider,
        _Out_ MI_Application *application)
{
    if (application)
    {
        memset(application, 0, sizeof(MI_Application));
    }
    if (hostedProvider && application)
    {
        GenericHandle *genericHandle = (GenericHandle*) hostedProvider;
        ThunkHandle *thunkHandle = NULL;
        HostedProviderObject *hpObject = NULL;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
        if (thunkHandle == NULL)
        {
            /* Failed means version was wrong or object was shutdown */
            return MI_RESULT_INVALID_PARAMETER;
        }
        hpObject = (HostedProviderObject*) thunkHandle->u.object;
        *application = hpObject->clientApplication;

        ThunkHandle_Release(thunkHandle);
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}


const MI_HostedProviderFT g_hostedProviderFT = { 
    HostedProvider_Close, 
    HostedProvider_GetApplication 
};
