/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/paths.h>
#include "ProtocolHandlerCache.h"
#include "InteractionProtocolHandler.h"
#include <pal/atomic.h>
#include <base/conf.h>
#include <unistd.h>

struct _staticProtocolHandlers
{
    MI_Char *name;
    ProtocolHandlerInitializeV1 dllFunctionPointer;
    MI_Boolean defaultLocal;
    MI_Boolean defaultRemote;
}  g_staticallyLoadedProtocolHandlers[] =
{
    { MI_T("OMI_SOCKETS"), InteractionProtocolHandler_Application_Initialize, MI_TRUE, MI_FALSE },
    { MI_T("MI_REMOTE_WSMAN"), InteractionProtocolHandler_Application_Initialize, MI_FALSE, MI_TRUE }
};

_Success_(return == MI_RESULT_OK)
MI_Result ProtocolHandlerCache_InsertProtocolEntries(_Inout_ ProtocolHandlerCache *cache,
            _In_z_ const char *protocolHandlerName,
            _In_z_ const char *protocolHandlerDLL,
            _In_z_ const char *protocolHandlerDllEntryPoint,
            MI_Uint32 protocolHandlerMajorVersion,
            MI_Uint32 protocolHandlerMinorVersion,
            _Outptr_ ProtocolHandlerCacheItem **cacheItem)
{
    ProtocolHandlerCacheItem *item;

    item = PAL_Malloc(sizeof(ProtocolHandlerCacheItem));
    if (item == NULL)
    {
        return  MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    memset(item, 0, sizeof(ProtocolHandlerCacheItem));

    TcsStrlcpy(item->name, protocolHandlerName, (sizeof(item->name)/sizeof(item->name[0])));
    Strlcpy(item->dllPath, protocolHandlerDLL, sizeof(item->dllPath)/sizeof(item->dllPath[0]));
    Strlcpy(item->dllEntryPoint, protocolHandlerDllEntryPoint, sizeof(item->dllEntryPoint)/sizeof(item->dllEntryPoint[0]));

    /* Plug this into the head of the list */
    item->nextItem = cache->cacheList;
    cache->cacheList = item;
    *cacheItem = item;

    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result ProtocolHandlerCache_CreateAllProtocolEntries(_Inout_ ProtocolHandlerCache *cache)
{
    char _path[PAL_MAX_PATH_SIZE];
    const char *path = NULL;
    Conf *configSubSystem;
    MI_Result ret = MI_RESULT_OK;
    int staticHandlerLoop;
    MI_Char defaultremoteprotocolhandler[30] = { 0 };
    MI_Char defaultlocalprotocolhandler[30] = { 0 };
    ProtocolHandlerCacheItem *cacheItem = NULL;

    path = OMI_GetPath(ID_SYSCONFDIR);
    if (path == NULL)
    {
        return MI_RESULT_FAILED;
    }

    /* Only need to copy on Windows as the paths are dynamic */
    Strlcpy(_path, path, sizeof(_path)/sizeof(_path[0]));
    Strlcat(_path, "/omicli.conf", PAL_MAX_PATH_SIZE);
    path = _path;

    int omicli_conf_exists = access(path, F_OK);
    if (omicli_conf_exists == -1)
    {
        ret = MI_RESULT_OK;
    }
    else
    {
        configSubSystem = Conf_Open(path);
        if (!configSubSystem)
        {
            /* err(ZT("failed to open configuration file: %s"), scs(path)); */
            return MI_RESULT_FAILED;		
        }

        for (;;)
        {
            const char* key;
            const char* value;
            int r = Conf_Read(configSubSystem, &key, &value);
            
            if (r == -1)
            {
                /* err(ZT("%s: %s\n"), path, scs(Conf_Error(conf)));*/
                ret = MI_RESULT_FAILED;
                break;
            }

            if (r == 1)
                break;

            if (strncmp(key, "protocolhandler", 15) == 0)
            {
                char *cursor;
                const char *protocolHandlerName;
                const char *protocolHandlerDLL;
                const char *protocolHandlerDllEntryPoint;
                MI_Uint32 protocolHandlerMajorVersion;
                MI_Uint32 protocolHandlerMinorVersion;
                
                /* We found a protocol handler, need to */
                
                /* First protocol handler name */
                cursor = Strchr(value, ',');
                if (cursor == NULL)
                {
                    ret = MI_RESULT_FAILED;
                    break;
                }
                *cursor = '\0';
                protocolHandlerName = value;
                
                value = cursor+1; /* move past ',' */
                
                /* Second DLL*/
                cursor = Strchr(value, ',');
                if (cursor == NULL)
                {
                    ret = MI_RESULT_FAILED;
                    break;
                }
                
                protocolHandlerDLL = value;
                value = cursor+1; /* move past ',' */
                
                /* Third DLL entry point */
                cursor = Strchr(value, ',');
                if (cursor == NULL)
                {
                    ret = MI_RESULT_FAILED;
                    break;
                }
                protocolHandlerDllEntryPoint = value;
                value = cursor+1; /* move past ',' */
                
                /* Forth is major version */
                protocolHandlerMajorVersion = Strtoul(value, &cursor, 10);
                if (*cursor != ',')
                {
                    ret = MI_RESULT_FAILED;
                    break;
                }
                value = cursor+1; /* move past ',' */
                
                /* Fifth is minor version */
                protocolHandlerMinorVersion = Strtoul(value, &cursor, 10);
                if (*cursor != '\0')
                {
                    ret = MI_RESULT_FAILED;
                    break;
                }
                ret = ProtocolHandlerCache_InsertProtocolEntries(cache, protocolHandlerName, protocolHandlerDLL, protocolHandlerDllEntryPoint, protocolHandlerMajorVersion, protocolHandlerMinorVersion, &cacheItem);
                if (ret != MI_RESULT_OK)
                    break;
            }
            else if (strncmp(key, "defaultlocalprotocolhandler", 27) == 0)
            {
                TcsStrlcpy(defaultlocalprotocolhandler, value, sizeof(defaultlocalprotocolhandler)/sizeof(defaultlocalprotocolhandler[0]));
            }
            else if (strncmp(key, "defaultremoteprotocolhandler", 28) == 0)
            {
                TcsStrlcpy(defaultremoteprotocolhandler, value, sizeof(defaultremoteprotocolhandler)/sizeof(defaultremoteprotocolhandler[0]));
            }
        }
        /* Close configuration file */
        Conf_Close(configSubSystem);
    }
        
    /* Fix up the config-based default handlers */
    if (defaultlocalprotocolhandler[0] || defaultremoteprotocolhandler[0])
    {
        cacheItem = cache->cacheList;
        while (cacheItem)
        {
            if (Tcscmp(defaultlocalprotocolhandler, cacheItem->name) == 0)
            {
                cache->defaultLocalItem = cacheItem;
            }
            else if (Tcscmp(defaultremoteprotocolhandler, cacheItem->name) == 0)
            {
                cache->defaultRemoteItem = cacheItem;
            }
            cacheItem = cacheItem->nextItem;
        }
    }

    if (ret == MI_RESULT_OK)
    {
        /* Handler staticly compiled in ones now */
        for (staticHandlerLoop = 0; staticHandlerLoop != sizeof(g_staticallyLoadedProtocolHandlers)/sizeof(g_staticallyLoadedProtocolHandlers[0]); staticHandlerLoop++)
        {
            ProtocolHandlerCacheItem *item;
            if (g_staticallyLoadedProtocolHandlers[staticHandlerLoop].name == NULL)
                break;

            item = PAL_Malloc(sizeof(ProtocolHandlerCacheItem));
            if (item == NULL)
            {
                ret = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                break;
            }
            memset(item, 0, sizeof(ProtocolHandlerCacheItem));

            Tcslcpy(item->name, g_staticallyLoadedProtocolHandlers[staticHandlerLoop].name, sizeof(item->name)/sizeof(item->name[0]));

            item->dllFunctionPointer = g_staticallyLoadedProtocolHandlers[staticHandlerLoop].dllFunctionPointer;

            /* Plug this into the head of the list */
            item->nextItem = cache->cacheList;
            cache->cacheList = item;

            if (g_staticallyLoadedProtocolHandlers[staticHandlerLoop].defaultLocal && (cache->defaultLocalItem == NULL))
                cache->defaultLocalItem = item;
            if (g_staticallyLoadedProtocolHandlers[staticHandlerLoop].defaultRemote && (cache->defaultRemoteItem == NULL))
                cache->defaultRemoteItem = item;
        }
    }

    /* if there is an error, free all transports */
    if (ret != MI_RESULT_OK)
    {
        while (cache->cacheList)
        {
            ProtocolHandlerCacheItem *item;
            item = cache->cacheList;

            /* unlink this item from list */
            cache->cacheList = item->nextItem;

            PAL_Free(item);
        }
    }
    return ret;
}

/* PUBLIC: ProtocolHandlerCache_Initialize
 * Initializes the cache.  Cache needs to be deinitialized when finished with.
 *
 * cache - Pointer to a ProtocolHandlerCache to be initialized
 *
 * Returns:
 *      ERROR_OUTOFMEMORY
 *      ERROR_SUCCESS
 */
MI_EXTERN_C MI_Result ProtocolHandlerCache_Initialize(_In_opt_z_ const MI_Char *applicationId, _Out_ ProtocolHandlerCache *cache)
{
    memset(cache, 0, sizeof(ProtocolHandlerCache));

    cache->applicationID = applicationId;

    /* Initialize the cache lock */
    if (CachedLock_Init(&cache->lock, CACHEDLOCK_FLAG_SHARED) != 0)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    return ProtocolHandlerCache_CreateAllProtocolEntries(cache);
}

/* PRIVATE: Unload a protocol handler.  This will call MI_Application_Close on the handler
 * if there is a function table, which is a blocking option... therefore
 * it will try and cancel all active sessions and operations.  The client
 * will need to close any outstanding handles otherwise this will block forever.
 * When closed it unloads the DLL, so if there are any active threads after the
 * fact things will crash.  It is the responsibility of the protocol handler
 * to make sure this does not happen.
 */
void ProtocolHandlerCache_UnloadProtocolHandler(_Inout_  ProtocolHandlerCacheItem *itemPointer)
{
    ptrdiff_t currentApiCount;

    if (itemPointer->dllInitialized == MI_TRUE)
    {
        /*Wait for the API count to hit 0 */
        currentApiCount = itemPointer->outstandingProtocolHandlerCalls;
        while (currentApiCount != 0)
        {
            CondLock_Wait((ptrdiff_t)itemPointer, &(itemPointer)->outstandingProtocolHandlerCalls, currentApiCount, CONDLOCK_DEFAULT_SPINCOUNT);
            currentApiCount = (itemPointer)->outstandingProtocolHandlerCalls;
        }

        if (itemPointer->application.ft)
        {
            MI_Application_Close(&itemPointer->application);
        }
        if (itemPointer->dllHandle != NULL)
        {
            Shlib_Close(itemPointer->dllHandle);
        }

        itemPointer->dllInitialized = MI_FALSE;
    }
}

/* PUBLIC: ProtocolHandlerCache_DeInitialize
 * Shuts down the cache, unloading all cache entries in the process.
 *
 * cache - Pointer to a ProtocolHandlerCache to be deinitialized
 *
 * Returns:
 *      ERROR_SUCCESS
 */
MI_EXTERN_C MI_Result ProtocolHandlerCache_DeInitialize(_Inout_ ProtocolHandlerCache *cache)
{
    CachedLock_AcquireWrite(&cache->lock);

    /* Free all transports */
    while (cache->cacheList)
    {
        ProtocolHandlerCacheItem *item = cache->cacheList;

        /* unlink this item from list */
        cache->cacheList = cache->cacheList->nextItem;

        /* unload and free it */
        ProtocolHandlerCache_UnloadProtocolHandler(item);
        PAL_Free(item);
    }

    CachedLock_ReleaseWrite(&cache->lock);

    /* Cleanup lock */
    CachedLock_Destroy(&cache->lock);

    return MI_RESULT_OK;
}

/* LOCK MUST ALREADY BE ACQUIRED */
_Success_(return == MI_RESULT_OK)
MI_Result ProtocolHandlerCache_FindProtocolHandler(_Inout_ ProtocolHandlerCache *cache, _In_z_ const MI_Char *name, _Outptr_ ProtocolHandlerCacheItem **cacheItem)
{
    ProtocolHandlerCacheItem *currentItem = cache->cacheList;

    while (currentItem)
    {
        if (Tcscmp(name, currentItem->name) == 0)
        {
            /* Found it! */
            break;
        }
        currentItem = currentItem->nextItem;
    }
    if (currentItem)
    {
        *cacheItem = currentItem;
        return MI_RESULT_OK;
    }
    else
    {
        /* Not there */
        return MI_RESULT_NOT_FOUND;
    }
}


/* Assumption: Protocol handler has not already been loaded.
 * This method will get the details of the protocol handler from config, load it
 * and call the MI_Application_Initialize method on the handler.
*/
_Success_(return == MI_RESULT_OK)
MI_Result ProtocolHandlerCache_LoadProtocolHandler(_Inout_ ProtocolHandlerCache *cache, _Inout_ ProtocolHandlerCacheItem *item)
{
    MI_Result returnCode;
    ProtocolHandlerInitializeV1 initializerFunction;

    if (item->dllInitialized == MI_TRUE)
    {
        /* Already initialized */
        return MI_RESULT_OK;
    }

    if ((item->majorVersion != 1) && (item->minorVersion != 0))
    {
        /* Not a supported version */
        return MI_RESULT_FAILED;
    }

    if (item->dllFunctionPointer)
    {
        initializerFunction = item->dllFunctionPointer;
    }
    else
    {
        TChar buf[PAL_MAX_PATH_SIZE];
        if (TcsStrlcpy(buf, item->dllPath, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return MI_RESULT_FAILED;

        item->dllHandle = Shlib_Open(buf);
        if (item->dllHandle == NULL)
        {
            return MI_RESULT_FAILED;
        }

        initializerFunction = (ProtocolHandlerInitializeV1)Shlib_Sym(item->dllHandle, item->dllEntryPoint);
        if (initializerFunction == NULL)
        {
            Shlib_Close(item->dllHandle);
            item->dllHandle = NULL;
            return MI_RESULT_NOT_SUPPORTED;
        }
    }

    /* Handle flags, and extendedError! */
    returnCode = initializerFunction(0, cache->applicationID, NULL, &item->application);
    if (returnCode != MI_RESULT_OK)
    {
        if (item->dllHandle)
        {
            Shlib_Close(item->dllHandle);
            item->dllHandle = NULL;
        }

        if (item->dllEntryPoint[0] != '\0')
        {
            item->dllFunctionPointer = NULL;
        }
        return returnCode;
    }

    item->dllInitialized = MI_TRUE;
    return MI_RESULT_OK;
}

/* Retrieves a protocol handler.  If it has not been loaded and initialized it will do so.
 * Fast case is when it has already been loaded and it grabs a fast read lock.  If an update
 * is being done this call will block until that is complete.
 */
_Success_(return == MI_RESULT_OK)
MI_EXTERN_C MI_Result ProtocolHandlerCache_GetProtocolHandler(_Inout_ ProtocolHandlerCache *cache, _In_z_ const MI_Char *name, _Outptr_ ProtocolHandlerCacheItem **cacheItem)
{
    MI_Result returnCode = MI_RESULT_OK;

    *cacheItem = NULL;

    /* Read lock to determine if the object exists.  This is the fast path. */
    ReadWriteLock_AcquireRead(&cache->lock);

    returnCode = ProtocolHandlerCache_FindProtocolHandler(cache, name, cacheItem);

    ReadWriteLock_ReleaseRead(&cache->lock);

    if (returnCode != MI_RESULT_OK)
    {
        return returnCode;
    }

    if ((*cacheItem)->dllInitialized == MI_FALSE)
    {
        ReadWriteLock_AcquireWrite(&cache->lock);
        returnCode = ProtocolHandlerCache_LoadProtocolHandler(cache, *cacheItem);
        ReadWriteLock_ReleaseWrite(&cache->lock);
    }

    return returnCode;
}

MI_Result ProtocolHandlerCache_IncrementApiCount(_Inout_ ProtocolHandlerCacheItem *cacheItem)
{
    Atomic_Inc(&cacheItem->outstandingProtocolHandlerCalls);
    return MI_RESULT_OK;
}
MI_Result ProtocolHandlerCache_DecrementApiCount(_Inout_ ProtocolHandlerCacheItem *cacheItem)
{
    if (Atomic_Dec(&cacheItem->outstandingProtocolHandlerCalls) == 0)
    {
        //Signal we are at 0 in case we are trying to shutdown this item
        CondLock_Broadcast((ptrdiff_t)cacheItem);

    }
    return MI_RESULT_OK;
}
