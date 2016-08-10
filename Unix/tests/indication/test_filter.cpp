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
#include <indication/common/indicommon.h>
#include <indication/indimgr/filter.h>
#include <pal/strings.h>

using namespace std;

NitsSetup(TestFilterSetup)
NitsEndSetup

NitsCleanup(TestFilterSetup)
NitsEndCleanup

NitsTestWithSetup(TestCreateFilter, TestFilterSetup)
{
    int c;
    const MI_Char* query = MI_T("select * from CIM_Indication");
    Filter * filter = Filter_New(query, QUERY_LANGUAGE_WQL, NULL);
    UT_ASSERT( NULL != filter );
    if (filter)
    {
        UT_ASSERT( Filter_GetRefcount(filter) == 1 );

        // identifier gets generated upon adding to indication manager cache
        UT_ASSERT( NULL == filter->base.base.identifier );

        c = Tcscasecmp(filter->QueryLanguage, QUERY_LANGUAGE_WQL);
        UT_ASSERT( c == 0 );

        c = Tcscasecmp(filter->Query, query);
        UT_ASSERT( c == 0 );

        Filter_Release(filter);
    }

    query = MI_T("select * from CIM_Indication2");
    filter = Filter_New(query, QUERY_LANGUAGE_CQL, NULL);
    UT_ASSERT( NULL != filter );
    if (filter)
    {
        UT_ASSERT( Filter_GetRefcount(filter) == 1 );

        // identifier gets generated upon adding to indication manager cache
        UT_ASSERT( NULL == filter->base.base.identifier );

        c = Tcscasecmp(filter->QueryLanguage, QUERY_LANGUAGE_CQL);
        UT_ASSERT( c == 0 );

        c = Tcscasecmp(filter->Query, query);
        UT_ASSERT( c == 0 );

        Filter_AddRef(filter);
        UT_ASSERT( Filter_GetRefcount(filter) == 2);
        Filter_AddRef(filter);
        UT_ASSERT( Filter_GetRefcount(filter) == 3);
        Filter_AddRef(filter);
        UT_ASSERT( Filter_GetRefcount(filter) == 4);
        Filter_Release(filter);
        Filter_Release(filter);
        Filter_Release(filter);

        Filter_Release(filter);
    }
}
NitsEndTest

NitsTestWithSetup(TestCreateFilter_WQL, TestFilterSetup)
{
    const MI_Char* query = MI_T("select * from CIM_TestClass where 2 > 1");
    Filter * filter = Filter_New(query, QUERY_LANGUAGE_WQL, NULL);
    UT_ASSERT( NULL != filter );
    if (filter)
    {
        UT_ASSERT(NULL != filter->wql);
        UT_ASSERT(FILTER_UNARY_TEMP == filter->base.type);
        UT_ASSERT(Tcscasecmp(filter->wql->className, MI_T("CIM_TestClass")) == 0);

        /* Test Namespace */
        MI_StringA nsa;
        MI_String data[3];
        MI_String nsroot = (MI_Char*)MI_T("root");
        nsa.size = 3;
        nsa.data = data;
        data[0] = nsroot;
        data[1] = (MI_Char*)MI_T("interop");
        data[2] = (MI_Char*)MI_T("root/cimv2");

        /* Fail if namespace size is not 1 */
        int r = Filter_SetNamespace(filter, &nsa);
        UT_ASSERT( r == -1 );
        UT_ASSERT( filter->SourceNamespaces.data == NULL );
        nsa.size = 1;

        /* Success if namespace size is 1 */
        r = Filter_SetNamespace(filter, &nsa);
        UT_ASSERT( r == 0 );
        UT_ASSERT( filter->SourceNamespaces.data != NULL );
        UT_ASSERT( filter->SourceNamespaces.size == 1 );
        UT_ASSERT(Tcscasecmp(filter->SourceNamespaces.data[0], nsroot) == 0);

        /* NO-OP if filter already added to a container */
        /* i.e., namespaces property of filter should not change */
        filter->base.base._container = (void*)0xF;
        nsa.data = &data[1];
        r = Filter_SetNamespace(filter, &nsa);
        UT_ASSERT( r == 0 );
        UT_ASSERT( filter->SourceNamespaces.data != NULL );
        UT_ASSERT( filter->SourceNamespaces.size == 1 );
        UT_ASSERT(Tcscasecmp(filter->SourceNamespaces.data[0], nsroot) == 0);
        filter->base.base._container = NULL;

        Filter_Release(filter);
    }
}
NitsEndTest

// Following are negative test cases and out of memory or the negative input generates the same error
// TODO: one can check if error object has specific errorcode to make sure we return right error for unknown dialect vs OOM

NitsTestWithSetup(TestCreateFilter_NotSupportedQueryDialect, TestFilterSetup)
{
    const MI_Char* query = MI_T("select * from CIM_Indication");
    MI_Instance* error = NULL;
    Filter * filter = Filter_New(query, MI_T("UnknownDialect"), &error);
    UT_ASSERT( NULL == filter );
    UT_ASSERT( NULL != error );
    NitsIgnoringError(); 
    if (error)
        MI_Instance_Delete(error);
}
NitsEndTest

NitsTestWithSetup(TestCreateFilter_InvalidWQLQuery, TestFilterSetup)
{
    const MI_Char* query = MI_T("select * from CIM_Indication where");
    MI_Instance* error = NULL;
    Filter * filter = Filter_New(query, QUERY_LANGUAGE_WQL, &error);
    UT_ASSERT( NULL == filter );
    UT_ASSERT( NULL != error );
    NitsIgnoringError(); 
    if (error)
        MI_Instance_Delete(error);
}
NitsEndTest

NitsTestWithSetup(TestCreateFilter_NotSupportedCQLQuery, TestFilterSetup)
{
    const MI_Char* query = MI_T("select * from CIM_Indication, CIM_TestClass where (1=1)");
    MI_Instance* error = NULL;
    Filter * filter = Filter_New(query, QUERY_LANGUAGE_CQL, &error);
    UT_ASSERT( NULL == filter );
    UT_ASSERT( NULL != error );
    NitsIgnoringError(); 
    if (error)
        MI_Instance_Delete(error);
}
NitsEndTest





