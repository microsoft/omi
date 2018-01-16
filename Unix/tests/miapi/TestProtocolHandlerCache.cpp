/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <MI.h>
#include <miapi/ProtocolHandlerCache.h>

struct _TestProtocolHandler
{
    const char *protocolHandlerName;
    const MI_Char *protocolHandlerName_w;
    const char *protocolHandlerDll;
    const char *protocolHandlerEntryPoint;
};

const struct _TestProtocolHandler g_test1Transport =
{
    "Test1",
    PAL_T("Test1"),
    "libtest_miapi." CONFIG_SHLIBEXT,
    "Test1_Application_Initialize"
} ;

const struct _TestProtocolHandler g_test2Transport =
{
    "Test2",
    PAL_T("Test2"),
    "libtest_miapi." CONFIG_SHLIBEXT,
    "Test2_Application_Initialize"
} ;


NitsTest(ProtocolHandlerCache_InitDeInit)
{
    ProtocolHandlerCache cache;
    if (NitsCompare(ProtocolHandlerCache_Initialize(PAL_T("applicationID"), &cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_Initialize should succeed")))
    {
        NitsCompare(ProtocolHandlerCache_DeInitialize(&cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_DeInitialize should succeed"));
    }
}
NitsEndTest

NitsTest(ProtocolHandlerCache_GetHandler)
{
    ProtocolHandlerCache cache;
    ProtocolHandlerCacheItem *cacheItem = NULL;

    if (NitsCompare(ProtocolHandlerCache_Initialize(PAL_T("applicationID"), &cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_Initialize should succeed")))
    {
        if (NitsCompare(ProtocolHandlerCache_InsertProtocolEntries(&cache, g_test1Transport.protocolHandlerName, g_test1Transport.protocolHandlerDll, g_test1Transport.protocolHandlerEntryPoint, 1, 1, &cacheItem), MI_RESULT_OK, PAL_T("Registering test transport")) &&
           (NitsCompare(ProtocolHandlerCache_GetProtocolHandler(&cache, PAL_T("Test1"), &cacheItem), MI_RESULT_OK, PAL_T("Successfully get protocol handler"))))
        {
            NitsAssert(cacheItem->application.ft != NULL, PAL_T("We should have a function table in the returned protocol handler application"));
        }

        NitsCompare(ProtocolHandlerCache_DeInitialize(&cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_DeInitialize should succeed"));
    }
}
NitsEndTest

NitsTest(ProtocolHandlerCache_GetHandler_TwoTheSame)
{
    ProtocolHandlerCache cache;
    ProtocolHandlerCacheItem *cacheItem1 = NULL;
    ProtocolHandlerCacheItem *cacheItem2 = NULL;
    if (NitsCompare(ProtocolHandlerCache_Initialize(NULL, &cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_Initialize should succeed")))
    {
        if (NitsCompare(ProtocolHandlerCache_InsertProtocolEntries(&cache, g_test1Transport.protocolHandlerName, g_test1Transport.protocolHandlerDll, g_test1Transport.protocolHandlerEntryPoint, 1, 1, &cacheItem1), MI_RESULT_OK, PAL_T("Registering test transport")) &&
            NitsCompare(ProtocolHandlerCache_GetProtocolHandler(&cache, PAL_T("Test1"), &cacheItem1), MI_RESULT_OK, PAL_T("Successfully get protocol handler")) &&
            NitsCompare(ProtocolHandlerCache_GetProtocolHandler(&cache, PAL_T("Test1"), &cacheItem2), MI_RESULT_OK, PAL_T("Second call successfully get protocol handler")))
        {
            NitsAssert(cacheItem1->application.ft != NULL, PAL_T("We should have a function table in the returned protocol handler application"));
            NitsAssert(cacheItem2->application.ft != NULL, PAL_T("We should have a function table in the returned protocol handler application"));
            NitsAssert(cacheItem1->application.ft == cacheItem2->application.ft, PAL_T("function tables should be the same"));
        }

        NitsCompare(ProtocolHandlerCache_DeInitialize(&cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_DeInitialize should succeed"));
    }
}
NitsEndTest

NitsTest(ProtocolHandlerCache_GetHandler_TwoDifferent)
{
    ProtocolHandlerCache cache;
    ProtocolHandlerCacheItem *cacheItem1 = NULL;
    ProtocolHandlerCacheItem *cacheItem2 = NULL;
    if (NitsCompare(ProtocolHandlerCache_Initialize(PAL_T("applicationID"), &cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_Initialize should succeed")))
    {
        if (NitsCompare(ProtocolHandlerCache_InsertProtocolEntries(&cache, g_test1Transport.protocolHandlerName, g_test1Transport.protocolHandlerDll, g_test1Transport.protocolHandlerEntryPoint, 1, 1, &cacheItem1), MI_RESULT_OK, PAL_T("Registering test transport")) &&
            NitsCompare(ProtocolHandlerCache_InsertProtocolEntries(&cache, g_test2Transport.protocolHandlerName, g_test2Transport.protocolHandlerDll, g_test2Transport.protocolHandlerEntryPoint, 1, 1, &cacheItem1), MI_RESULT_OK, PAL_T("Registering test transport")) &&
            NitsCompare(ProtocolHandlerCache_GetProtocolHandler(&cache, PAL_T("Test1"), &cacheItem1), MI_RESULT_OK, PAL_T("Successfully get protocol handler")) &&
            NitsCompare(ProtocolHandlerCache_GetProtocolHandler(&cache, PAL_T("Test2"), &cacheItem2), MI_RESULT_OK, PAL_T("Second call successfully get protocol handler")))
        {
            NitsAssert(cacheItem1->application.ft != NULL, PAL_T("We should have a function table in the returned protocol handler application"));
            NitsAssert(cacheItem2->application.ft != NULL, PAL_T("We should have a function table in the returned protocol handler application"));
            NitsAssert(cacheItem1->application.ft != cacheItem2->application.ft, PAL_T("function tables should be different"));
        }

        NitsCompare(ProtocolHandlerCache_DeInitialize(&cache), MI_RESULT_OK, PAL_T("ProtocolHandlerCache_DeInitialize should succeed"));
    }
}
NitsEndTest
