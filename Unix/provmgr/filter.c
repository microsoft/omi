/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "filter.h"
#include <base/log.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <indication/common/indicommon.h>

static const MI_Uint32 _MAGIC = 0xDEADBEEF;

/*
 * Structure and handler for WQL queries.
 */
typedef struct _InstanceFilter_WQL
{
    InstanceFilter filterBase;

    WQL* wql;
} InstanceFilter_WQL;

/*
 * Structure and handler for CQL queries.  Right now, CQL queries are handled
 * exactly like WQL queries.
 */
typedef struct _InstanceFilter_CQL
{
    InstanceFilter filterBase;

    WQL* wql;
} InstanceFilter_CQL;

/*
 * Additional derived structures for new filter types go here.
 */

/*
 * Internal InstanceFilterFT function definitions
 */

MI_Result _DoWqlEval(
    WQL* wql,
    const MI_Instance* instance,
    MI_Boolean* isMatch )
{
    int r = 0;

    if (NULL == wql)
    {        
        *isMatch = MI_FALSE;
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    r = WQL_Eval(wql, WQL_LookupInstanceProperty, (void*)instance);
    if (r == 0)
    {
        /* Instance matched the query */
        *isMatch = MI_TRUE;
    }
    else
    {
        /* Mismatch */
        *isMatch = MI_FALSE;
    }

    return MI_RESULT_OK;
}

MI_Result _FilterFunc_WQL( 
    InstanceFilter* self, 
    const MI_Instance* instance,
    MI_Boolean* isMatch )
{
    return _DoWqlEval(((InstanceFilter_WQL*)self)->wql, instance, isMatch);
}

MI_Result _FilterFunc_CQL( 
    InstanceFilter* self, 
    const MI_Instance* instance,
    MI_Boolean* isMatch)
{
    return _DoWqlEval(((InstanceFilter_CQL*)self)->wql, instance, isMatch);
}

MI_Result _FilterFunc_UnFiltered( 
    InstanceFilter* self, 
    const MI_Instance* indication,
    MI_Boolean* isMatch)
{
    /*This Unfilter filter doesn't have wql or WQL is NULL, so evaluate doesn't have any meaning*/
    *isMatch = MI_FALSE;
    /*Return MI_RESULT_INVALID_PARAMETER and not MI_RESULT_NOT_SUPPORTED, just to follow MSDN documentation*/
    return MI_RESULT_INVALID_PARAMETER;
}

void _Destroy_WQL(
    _In_ InstanceFilter* self )
{
    WQL_Delete( ((InstanceFilter_WQL*)self)->wql );
}

void _Destroy_CQL(
    _In_ InstanceFilter* self )
{
    WQL_Delete( ((InstanceFilter_CQL*)self)->wql );
}

void _Destroy_UnFiltered(
    _In_ InstanceFilter* self )
{
    /*This Unfilter filter doesn't have WQL or WQL is NULL so there is nothing to clean*/
}

WQL* _GetWQL(
    _In_ InstanceFilter* self)
{
    return ((InstanceFilter_WQL*)self)->wql;
}

WQL* _GetCQL(
    _In_ InstanceFilter* self)
{
    return ((InstanceFilter_CQL*)self)->wql;
}

WQL* _GetUnFiltered(
    _In_ InstanceFilter* self)
{
    /*This Unfilter filter doesn't have wql or WQL is NULL*/
    return NULL;
}

InstanceFilterFT _filterFT_WQL =
{
    _FilterFunc_WQL,
    _Destroy_WQL,
    _GetWQL
};

InstanceFilterFT _filterFT_CQL =
{
    _FilterFunc_CQL,
    _Destroy_CQL,
    _GetCQL
};

InstanceFilterFT _filterFT_UnFiltered =
{
    _FilterFunc_UnFiltered,
    _Destroy_UnFiltered,
    _GetUnFiltered
};

MI_ConstString _GetQueryLanguage(
    _In_  Message* msg)
{
    if(!msg)
        return NULL;

    if(msg->tag == EnumerateInstancesReqTag)
    {
        /* This is EnumerateInstancesReq */
        EnumerateInstancesReq *enumMsg = (EnumerateInstancesReq*) msg;

        return enumMsg->queryLanguage;
    }
    else if(msg->tag == SubscribeReqTag)
    {
        /* This is SubscribeReq */
        SubscribeReq *subscMsg = (SubscribeReq*) msg;

        return subscMsg->language;
    }
    else 
    {
        trace_InstanceFilter_GetQueryLanguageUnsupportedMessageTag();
        return NULL;
    }
}

MI_ConstString _GetQueryExpression(
    _In_  Message* msg)
{
    if(!msg)
        return NULL;

    if(msg->tag == EnumerateInstancesReqTag)
    {
        /* This is EnumerateInstancesReq */
        EnumerateInstancesReq *enumMsg = (EnumerateInstancesReq*) msg;

        return enumMsg->queryExpression;
    }
    else if(msg->tag == SubscribeReqTag)
    {
        /* This is SubscribeReq */
        SubscribeReq *subscMsg = (SubscribeReq*) msg;

        return subscMsg->filter;
    }
    else 
    {
        trace_InstanceFilter_GetQueryExpressionUnsupportedMessageTag();
        return NULL;
    }
}

static MI_Result MI_CALL _Evaluate(
    _In_ const MI_Filter* self, 
    _In_ const MI_Instance* instance,
    _Out_ MI_Boolean* result)
{
    InstanceFilter* filter = (InstanceFilter*)self;

    if (!filter || filter->magic != _MAGIC || !instance || !result)
    {
        trace_InstanceFilter_EvaluateWithNullInput();
        return MI_RESULT_INVALID_PARAMETER;
    }

    return filter->ft->Filter( filter, instance, result );
}

static MI_Result MI_CALL _GetExpression(
    _In_ const MI_Filter* self, 
    _Outptr_result_maybenull_z_ const MI_Char** queryLang, 
    _Outptr_result_maybenull_z_ const MI_Char** queryExpr)
{
    InstanceFilter* filter = (InstanceFilter*)self;

    if (!filter || filter->magic != _MAGIC)
    {
        trace_InstanceFilter_GetExpressionWithNullInput();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (queryLang)
    {
        *queryLang = _GetQueryLanguage(filter->msg);
    }

    if (queryExpr)
    {
        *queryExpr = _GetQueryExpression(filter->msg);
    }

    return MI_RESULT_OK;
}

MI_FilterFT __mi_FilterFT =
{
    _Evaluate,
    _GetExpression
};

_Use_decl_annotations_
    InstanceFilter* InstanceFilter_New( 
    Message* msg)
{
    MI_ConstString queryLanguage = _GetQueryLanguage(msg);
    MI_ConstString queryExpression = _GetQueryExpression(msg);

    if (queryLanguage == NULL || queryExpression == NULL)
    {
        trace_InstanceFilter_NewWithNullInput();
        return NULL;
    }

    if (Tcscasecmp(queryLanguage, QUERY_LANGUAGE_WQL) == 0)
    {
        InstanceFilter_WQL* filter = (InstanceFilter_WQL*)Batch_GetClear(msg->batch, sizeof(InstanceFilter_WQL));

        if(!filter)
        {
            trace_OutOfMemory();
            return NULL;
        }
        /* Initialize "Base" struct */
        filter->filterBase.base.ft = &__mi_FilterFT;
        filter->filterBase.magic = _MAGIC;
        filter->filterBase.msg = msg;
        filter->filterBase.ft = &_filterFT_WQL;

        /* Initialize WQL extension */
        filter->wql = WQL_Parse(queryExpression, msg->batch, WQL_DIALECT_WQL);
        if (!filter->wql)
        {
            trace_InvalidQueryExpression(tcs(queryExpression));
            /* filter will be freed when the Batch destructs */
            return NULL;
        }

        return (InstanceFilter*)filter;
    }
    else if (Tcscasecmp(queryLanguage, QUERY_LANGUAGE_CQL) == 0)
    {
        InstanceFilter_CQL* filter = (InstanceFilter_CQL*)Batch_GetClear(msg->batch, sizeof(InstanceFilter_CQL));

        if(!filter)
        {
            trace_OutOfMemory();
            return NULL;
        }

        /* Initialize "Base" struct */
        filter->filterBase.base.ft = &__mi_FilterFT;
        filter->filterBase.magic = _MAGIC;
        filter->filterBase.msg = msg;
        filter->filterBase.ft = &_filterFT_CQL;

        /* Initialize WQL extension since CQL covers the same type of supported
        * expressions. */
        filter->wql = WQL_Parse(queryExpression, msg->batch, WQL_DIALECT_CQL);
        if (!filter->wql)
        {
            trace_InvalidQueryExpression(tcs(queryExpression));
            /* filter will be freed when the Batch destructs */
            return NULL;
        }

        return (InstanceFilter*)filter;
    }
    else
    {        
        InstanceFilter* filter = (InstanceFilter*)Batch_GetClear(msg->batch, sizeof(InstanceFilter));

        if(!filter)
        {
            trace_OutOfMemory();
            return NULL;
        }

        /* Initialize "Base" struct */
        filter->base.ft = &__mi_FilterFT;
        filter->magic = _MAGIC;
        filter->msg = msg;
        filter->ft = &_filterFT_UnFiltered;
        
        return filter;
    }
}

_Use_decl_annotations_
void InstanceFilter_Destroy(
    InstanceFilter* self )
{
    DEBUG_ASSERT( self );

    /* Clean up specific to derived structs */
    self->ft->Destroy( self );

    /* Common clean up */
    self->magic = 0xFFFFFFFF;
}

_Use_decl_annotations_
MI_Result InstanceFilter_Filter(
    InstanceFilter* self, 
    const MI_Instance* indication,
    MI_Boolean* isMatch )
{
    DEBUG_ASSERT( self );

    return self->ft->Filter( self, indication, isMatch );
}

//_Use_decl_annotations_
WQL* InstanceFilter_GetWQL(
    _In_ InstanceFilter* self )
{
    if(!self)
        return NULL;

    return self->ft->GetWQL( self );
}
