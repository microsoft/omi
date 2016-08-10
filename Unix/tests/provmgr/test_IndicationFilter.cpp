/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <pal/palcommon.h>
#include <pal/strings.h>
#include <provmgr/filter.h>
#include <indication/common/indicommon.h>
#include <provmgr/indicationSchema.h>
#include <provmgr/CIM_InstCreation.h>
#include <provmgr/CIM_InstDeletion.h>

SubscribeReq* subscribeReq = NULL;

MI_ConstString defaultInstanceFilter = MI_T("SELECT * FROM CIM_InstCreation WHERE IndicationIdentifier = \"MSFT:CreationIndicationIdentifier\"");
MI_ConstString indicationLanguageWql = MI_T("WQL");
MI_ConstString indicationLanguageCql = MI_T("CQL");

/*
**==============================================================================
**
** Setup function, it is called before running each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
NitsSetup(Test_InstanceFilter_SetupSubscribeReq)
{
    subscribeReq = SubscribeReq_New( 0, 0 );

    NitsAssertOrReturn(NULL != subscribeReq, PAL_T("Failed to initialize SubscribeReq"));

    subscribeReq->targetType = SUBSCRIP_TARGET_DEFAULT;
    subscribeReq->filter = defaultInstanceFilter;
    subscribeReq->language = indicationLanguageWql;
    subscribeReq->subscriptionID = 1;
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
NitsCleanup(Test_InstanceFilter_SetupSubscribeReq)
{
    if (subscribeReq)
    {
        SubscribeReq_Release( subscribeReq );
        subscribeReq = NULL;
    }
}
NitsEndCleanup

NitsSetup1(Test_InstanceFilter_SetupSubscribeReq_as_WQL, NitsEmptyStruct,
           Test_InstanceFilter_SetupSubscribeReq, NitsEmptyValue)
{
    subscribeReq->language = indicationLanguageWql;
}
NitsEndSetup

NitsSetup1(Test_InstanceFilter_SetupSubscribeReq_as_CQL, NitsEmptyStruct,
           Test_InstanceFilter_SetupSubscribeReq, NitsEmptyValue)
{
    subscribeReq->language = indicationLanguageCql;
}
NitsEndSetup

NitsSplit2(Test_InstanceFilter_SetupSubscribeReq_BothWays,NitsEmptyStruct,
           Test_InstanceFilter_SetupSubscribeReq_as_WQL,
           Test_InstanceFilter_SetupSubscribeReq_as_CQL)
NitsEndSplit

// InstanceFilter_New with invalid query SubscribeReq->language
// InstanceFilter_Destroy resets magic
NitsTest1(Test_InstanceFilter_New_with_unrecognized_query_language, Test_InstanceFilter_SetupSubscribeReq, NitsEmptyValue)
{

    InstanceFilter* filter = NULL;
    subscribeReq->language = MI_T("UnrecognizedQueryLanguage");

    filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssert(NULL != filter, PAL_T("Failed to initialize InstanceFilter with general or unrecognized (Not WQL/CQL) query language"));
    NitsAssert(NULL == InstanceFilter_GetWQL(filter), PAL_T("Failed to initialize InstanceFilter with eneral or unrecognized (Not WQL/CQL) query language"));
}
NitsEndTest

// InstanceFilter_New with WQL || CQL with invalid SubscribeReq->filter
// InstanceFilter_Destroy resets magic
NitsTest1(Test_InstanceFilter_New_with_invalid_query_filter, Test_InstanceFilter_SetupSubscribeReq_BothWays, NitsEmptyValue)
{
    subscribeReq->filter = MI_T("* FROM TEST_DummyIndicationClass");  // NO "SELECT"

    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssert(NULL == filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));
    NitsIgnoringError(); // negative test case and same error in OOM or otherwise
}
NitsEndTest

// InstanceFilter_New with WQL || CQL initialized
// InstanceFilter_Destroy resets magic
NitsTest1(Test_InstanceFilter_New, Test_InstanceFilter_SetupSubscribeReq_BothWays, NitsEmptyValue)
{
    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssertOrReturn(NULL != filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));
    NitsAssert(0xDEADBEEF == filter->magic, PAL_T("InstanceFilter: incorrect magic #"));
    NitsAssert(NULL != filter->ft, PAL_T("InstanceFilter: function table NOT set"));
    NitsAssert(subscribeReq == (SubscribeReq*)filter->msg, PAL_T("InstanceFilter: incorrect message"));

    InstanceFilter_Destroy( filter );

    NitsAssert(0xFFFFFFFF == filter->magic, PAL_T("InstanceFilter: magic # not reset following destroy"));
}
NitsEndTest

// InstanceFilter_Filter match with WQL || CQL
// MI_Filter Evaluate with WQL || CQL
NitsTest1(Test_InstanceFilter_Filter_match, Test_InstanceFilter_SetupSubscribeReq_BothWays, NitsEmptyValue)
{
    MI_Boolean isMatch = MI_FALSE;
    CIM_InstCreation indication;

    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssertOrReturn(NULL != filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));

    if ( NitsAssert( MI_RESULT_OK == Instance_Construct( &indication.__instance, &CIM_InstCreation_rtti, NULL ), PAL_T("Instance_Construct failed") ) )
    {
        MI_Value value;
        value.string = (MI_Char*)PAL_T("MSFT:CreationIndicationIdentifier");
        if ( ! NitsAssert(MI_RESULT_OK == MI_Instance_SetElement( &indication.__instance, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 ), PAL_T("Set key failed on indication")))
        {
            InstanceFilter_Destroy( filter );
            NitsReturn;
        }

        // Test the instance against the internal version of the call
        NitsAssert( MI_RESULT_OK == InstanceFilter_Filter( filter, &indication.__instance, &isMatch ), PAL_T("Filter failed") );
        NitsAssert( MI_TRUE == isMatch, PAL_T("Filter match failed") );

        // Also test same instance via external MI call
        NitsAssert( MI_RESULT_OK == MI_Filter_Evaluate( &filter->base, &indication.__instance, &isMatch ), PAL_T("Filter failed")  );
        NitsAssert( MI_TRUE == isMatch, PAL_T("Filter match failed") );
        NitsAssert( MI_RESULT_OK == MI_Instance_Destruct( &indication.__instance ), PAL_T("indication destruction failed") );
    }
       

    InstanceFilter_Destroy( filter );
    NitsAssert(0xFFFFFFFF == filter->magic, PAL_T("InstanceFilter: magic # not reset following destroy"));

}
NitsEndTest

// InstanceFilter_Filter NO match with WQL || CQL
// MI_Filter Evaluate with WQL || CQL
// TODO: Split of split to reduce duplication?
NitsTest1(Test_InstanceFilter_Filter_NO_match, Test_InstanceFilter_SetupSubscribeReq_BothWays, NitsEmptyValue)
{
    MI_Boolean isMatch = MI_FALSE;
    CIM_InstDeletion indication;

    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssertOrReturn(NULL != filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));

    if ( NitsAssert( MI_RESULT_OK == Instance_Construct( &indication.__instance, &CIM_InstDeletion_rtti, NULL ), PAL_T("Instance_Construct failed") ) )
    {
        MI_Value value;
        value.string = (MI_Char*)PAL_T("MSFT:DeletionIndicationIdentifier");
        if ( ! NitsAssert(MI_RESULT_OK == MI_Instance_SetElement( &indication.__instance, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 ), PAL_T("Set key failed on indication")) )
        {
            InstanceFilter_Destroy( filter );
            NitsReturn;
        }

        // Test the instance against the internal version of the call
        NitsAssert( MI_RESULT_OK == InstanceFilter_Filter( filter, &indication.__instance, &isMatch ), PAL_T("Filter failed") );
        NitsAssert( MI_FALSE == isMatch, PAL_T("Filter match when non-match expected") );

        // Also test same instance via external MI call
        NitsAssert( MI_RESULT_OK == MI_Filter_Evaluate( &filter->base, &indication.__instance, &isMatch ), PAL_T("Filter failed") );
        NitsAssert( MI_FALSE == isMatch, PAL_T("Filter match when non-match expected") ); NitsIgnoringError(); //negative test case and same error is returned when OOM or not found error occurs in WQL_LookupInstanceProperty

        NitsAssert( MI_RESULT_OK == MI_Instance_Destruct( &indication.__instance ), PAL_T("indication destruction failed") );
    }
    
    
    InstanceFilter_Destroy( filter );
    NitsAssert(0xFFFFFFFF == filter->magic, PAL_T("InstanceFilter: magic # not reset following destroy"));
    
}
NitsEndTest


// MI_Filter GetExpression
NitsTest1(Test_InstanceFilter_GetExpression, Test_InstanceFilter_SetupSubscribeReq, NitsEmptyValue)
{
    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssertOrReturn(NULL != filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));

    MI_Filter* miFilter = &filter->base;
    const MI_Char* queryLang = NULL;
    const MI_Char* queryExpr = NULL;
    NitsAssert( MI_RESULT_OK == MI_Filter_GetExpression( miFilter, &queryLang, &queryExpr ), PAL_T("MI_Filter_GetExpression failed") );

    NitsAssert( 0 == Tcsncmp( queryLang, indicationLanguageWql, Tcslen(indicationLanguageWql) ), PAL_T("Unmatched query language") );
    NitsAssert( 0 == Tcsncmp( queryExpr, defaultInstanceFilter, Tcslen(defaultInstanceFilter) ), PAL_T("Unmatched query string") );

    InstanceFilter_Destroy( filter );

    NitsAssert(0xFFFFFFFF == filter->magic, PAL_T("InstanceFilter: magic # not reset following destroy"));
}
NitsEndTest

// InstanceFilter InstanceFilter_GetWQL
NitsTest1(Test_InstanceFilter_GetWQL, Test_InstanceFilter_SetupSubscribeReq, NitsEmptyValue)
{
    InstanceFilter* filter = InstanceFilter_New( &(subscribeReq->base.base) );

    NitsAssertOrReturn(NULL != filter, PAL_T("Failed to initialize InstanceFilter with InvalidQueryLanguage"));

    WQL* wql = InstanceFilter_GetWQL(filter);

    NitsAssert( NULL != wql, PAL_T("InstanceFilter_GetWQL failed") );
    NitsAssert(  0 == Tcsncmp( wql->text, defaultInstanceFilter, Tcslen(defaultInstanceFilter) ), PAL_T("InstanceFilter_GetWQL failed") );

    InstanceFilter_Destroy( filter );

    NitsAssert(0xFFFFFFFF == filter->magic, PAL_T("InstanceFilter: magic # not reset following destroy"));
}
NitsEndTest

