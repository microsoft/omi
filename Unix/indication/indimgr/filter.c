/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <indication/common/indicommon.h>
#include <indication/common/indilog.h>
#include <base/strarr.h>
#include <pal/strings.h>
#include <omi_error/OMI_Error.h>
#include <omi_error/omierror.h>
#include "filter.h"
#include "filtercol.h"

const MI_Uint32 g_FilterMagic = 0xF11EE0FF;
MI_Uint32 g_FilterTempID = 1;

int _IsFilter(_In_ CimBase *self)
{
    if (self->_magic != g_FilterMagic)
    {
        trace_ObjectIsNotAValidFilter(self);
        return -1;
    }
    return 0;
}

void Filter_Finalize(CimBase *self)
{
    trace_FunctionEntered(__FILE__, __LINE__);
    
    /* Skip cleaning up wql since it was created on self's batch */

    return;
}

/* Create identifier of current object */
MI_Char* CreateFilterIdentifier(_In_ CimBase *self)
{
    FilterBase* fb;
    DEBUG_ASSERT(self);
    if (_IsFilter(self) != 0)
        return NULL;

    fb = (FilterBase*)self;
    switch(fb->type)
    {
    case FILTER_UNARY_TEMP:
        /* TODO: get filter ID thread safely */
        return GetID(g_FilterTempID++, TEMP_FILTER_ID_PREFIX, self->batch);
    case FILTER_UNARY_CONFIG:
        /* id is the filter instance's name/instanceid property */
        break;
    case FILTER_COLLECTION_CONFIG:
        break;
    }
    return NULL;
}

/* Add to container callback */
int Filter_OnAdd(_Inout_ CimBase *self, _In_ void* container)
{
    return CimBase_OnAdd(self, container);
}

CimBaseFT g_filterft = {
    CimBase_AddRef,
    CimBase_Release,
    Filter_Finalize,
    Filter_OnAdd,
    CimBase_OnRemove,
    CreateFilterIdentifier,
};

_Use_decl_annotations_
Filter* Filter_New(
    const MI_Char* Query,
    const MI_Char* QueryLanguage,
    MI_Instance** error)
{
    Filter * filter = NULL;
    MI_Boolean isWQL = MI_FALSE;
    MI_Boolean isCQL = MI_FALSE;
    const MI_Char* errmsg = STR_OUT_OF_MEMORY;
    MI_Result r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    DEBUG_ASSERT(QueryLanguage);
    do
    {
        if (error)
            *error = NULL;
        filter = (Filter*)CimBase_Create(sizeof(Filter));
        if (NULL == filter)
        {
            LOGD_BATCH_OOM;
            break;
        }

        if (Query)
        {
            filter->Query = Batch_Tcsdup(filter->base.base.batch, Query);
            if (NULL == filter->Query)
            {
                LOGD_BATCH_ZDUP_OOM;
                Batch_Delete(filter->base.base.batch);
                filter = NULL;
                break;
            }
        }
        filter->QueryLanguage = Batch_Tcsdup(filter->base.base.batch, QueryLanguage);
        if (NULL == filter->QueryLanguage)
        {
            LOGD_BATCH_ZDUP_OOM;
            Batch_Delete(filter->base.base.batch);
            filter = NULL;
            break;
        }

        if (Tcscasecmp(MI_QUERY_DIALECT_WQL, filter->QueryLanguage) == 0)
        {
            isWQL = MI_TRUE;
        }
        else if (Tcscasecmp(MI_QUERY_DIALECT_CQL, filter->QueryLanguage) == 0)
        {
            isCQL = MI_TRUE;
        }

        if (isWQL || isCQL)
        {
            WQL_Dialect dialect = isWQL ? WQL_DIALECT_WQL : WQL_DIALECT_CQL;

            filter->base.type = FILTER_UNARY_TEMP;
            /* parse query on filter's batch */
            filter->wql = WQL_Parse(
                filter->Query, 
                filter->base.base.batch, 
                dialect);

            if (!filter->wql)
            {
                trace_ParseQueryFailed(filter->Query);
                Batch_Delete(filter->base.base.batch);
                r = MI_RESULT_INVALID_QUERY;
                errmsg = STR_INVALID_FILTER;
                filter = NULL;
                break;
            }
        }
        else
        {
            trace_UnsupportedQueryLanguage(filter->QueryLanguage);
            Batch_Delete(filter->base.base.batch);
            r = MI_RESULT_NOT_SUPPORTED;
            errmsg = STR_NOT_SUPPORTED_QUERY_DIALECT;
            filter = NULL;
            break;
        }
        filter->IndividualSubscriptionSupported = MI_TRUE;
        CimBase_Set_Magic(&filter->base.base, g_FilterMagic);
        CimBase_Set_FT(&filter->base.base, &g_filterft);
        Filter_AddRef(filter);
    }
    while(0);
    if ((NULL == filter) && error)
    {
        OMI_ErrorFromErrorCode(
            NULL,
            r,
            MI_RESULT_TYPE_MI,
            errmsg,
            (OMI_Error**) error);

    }
    return filter;
}

_Use_decl_annotations_
int Filter_AddRef(Filter* self)
{
    DEBUG_ASSERT(self);
    return self->base.base._ft->addref((CimBase*)self);
}

_Use_decl_annotations_
int Filter_Release(Filter* self)
{
    DEBUG_ASSERT(self);
    return self->base.base._ft->release((CimBase*)self);
}

/* Add a reference to a FilterBase object */
_Use_decl_annotations_
int FilterBase_AddRef(FilterBase* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->addref((CimBase*)self);
}

/* Release a reference to a FilterBase object */
_Use_decl_annotations_
int FilterBase_Release(FilterBase* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->release((CimBase*)self);
}

/* Get reference count */
int Filter_GetRefcount(_In_ Filter *self)
{
    DEBUG_ASSERT(self);
    return CimBase_GetRefcount((CimBase*)self);
}

int FilterBase_GetRefcount(_In_ FilterBase *self)
{
    DEBUG_ASSERT(self);
    return CimBase_GetRefcount((CimBase*)self);
}

/* Set source namespace */
_Use_decl_annotations_
int Filter_SetNamespace(
    Filter* self,
    MI_StringA* namespaces)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(namespaces);
    /* Can only set namespace before add to indication manager */
    if (self->base.base._container == NULL)
    {
        switch(self->base.type)
        {
        case FILTER_UNARY_TEMP:
            if (namespaces->size != 1)
            {
                trace_TempSubscrCanHaveOnlyOneNamespace();
                return -1;
            }
            break;
        default:
            break;
        }

        if (namespaces->size)
        {
            self->SourceNamespaces.data = CloneStringArray(
                (const MI_Char**)namespaces->data, namespaces->size, self->base.base.batch);
            if (NULL == self->SourceNamespaces.data)
            {
                LOGD_BATCH_OOM;
                return -1;
            }
            self->SourceNamespaces.size = namespaces->size;
        }
    }
    return 0;
}

void Filter_SetLastError(
    _Inout_ Filter* self,
    _In_opt_ MI_Instance* error,
    MI_Result result)
{
    DEBUG_ASSERT(self);    
    DEBUG_ASSERT(result != MI_RESULT_OK);
    ErrorHandler_SetLastError(
        &self->base.errhandler,
        error,
        result);
}

