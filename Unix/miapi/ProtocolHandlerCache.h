/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_protocolHandlerCache_h_
#define _miapi_protocolHandlerCache_h_
#include <MI.h>
#include <pal/lock.h>
#include <pal/strings.h>
#include <pal/shlib.h>

typedef MI_Result (MI_MAIN_CALL *ProtocolHandlerInitializeV1)(
               MI_Uint32 flags, 
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *application);

/* ProtocolHandlerCacheItem
 * This object represents a specific protocol handler
 */
typedef struct _ProtocolHandlerCacheItem
{
    MI_Boolean dllInitialized;
    MI_Char name[30];  /* Protocol handler name string */
    char dllPath[PAL_MAX_PATH_SIZE]; /* Path to DLL */
    char dllEntryPoint[30]; /* Entry point name in the DLL to call */
    MI_Uint32 majorVersion;
    MI_Uint32 minorVersion;
    ProtocolHandlerInitializeV1 dllFunctionPointer; /* Statically loaded hander entry point */
    Shlib *dllHandle; /* Handle from LoadLibrary */
    MI_Application application; /* application returned when initialized */
    volatile ptrdiff_t outstandingProtocolHandlerCalls; /* If we are currently calling into a protocol handler within a thread we bump this and decrement straight after */
    struct _ProtocolHandlerCacheItem *nextItem; /* Next item in list */
} ProtocolHandlerCacheItem;

typedef struct _ProtocolHandlerCache
{
    /* fast read/write lock, optimized for many reads/few writes */
    ReadWriteLock lock;

    /* Array of transports */
    ProtocolHandlerCacheItem *cacheList;

    ProtocolHandlerCacheItem *defaultLocalItem;
    ProtocolHandlerCacheItem *defaultRemoteItem;

    const MI_Char *applicationID;
} ProtocolHandlerCache;

/* PUBLIC: ProtocolHandlerCache_Initialize
 * Initializes the cache.  Cache needs to be deinitialized when finished with.
 *
 * cache - Pointer to a ProtocolHandlerCache to be initialized
 *
 * Returns:
 *      ERROR_OUTOFMEMORY
 *      ERROR_SUCCESS
 */
MI_EXTERN_C MI_Result ProtocolHandlerCache_Initialize(_In_opt_z_ const MI_Char *applicationId, _Out_ ProtocolHandlerCache *Self);

/* PUBLIC: ProtocolHandlerCache_DeInitialize
 * Shuts down the cache, unloading all cache entries in the process.
 *
 * cache - Pointer to a ProtocolHandlerCache to be deinitialized
 *
 * Returns:
 *      ERROR_SUCCESS
 */
MI_EXTERN_C MI_Result ProtocolHandlerCache_DeInitialize(_Inout_ ProtocolHandlerCache *cache);

/* PUBLIC: ProtocolHandlerCache_GetProtocolHandler
 */
_Success_(return == MI_RESULT_OK)
MI_EXTERN_C MI_Result ProtocolHandlerCache_GetProtocolHandler(_Inout_ ProtocolHandlerCache *cache, _In_z_ const MI_Char *name, _Outptr_ ProtocolHandlerCacheItem **cacheItem);

MI_Result ProtocolHandlerCache_IncrementApiCount(_Inout_ ProtocolHandlerCacheItem *cacheItem);
MI_Result ProtocolHandlerCache_DecrementApiCount(_Inout_ ProtocolHandlerCacheItem *cacheItem);


_Success_(return == MI_RESULT_OK)
MI_EXTERN_C MI_Result ProtocolHandlerCache_InsertProtocolEntries(_Inout_ ProtocolHandlerCache *cache,
            _In_z_ const char *protocolHandlerName,
            _In_z_ const char *protocolHandlerDLL,
            _In_z_ const char *protocolHandlerDllEntryPoint,
            MI_Uint32 protocolHandlerMajorVersion,
            MI_Uint32 protocolHandlerMinorVersion,
            _Outptr_ ProtocolHandlerCacheItem **cacheItem);


#endif /* _miapi_protocolHandlerCache_h_ */

