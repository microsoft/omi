/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _indication_indimgr_filter_h
#define _indication_indimgr_filter_h

#include <common.h>
#include "cimbase.h"
#include <wql/wql.h>

#define TEMP_FILTER_ID_PREFIX MI_T("_tempfilter")

BEGIN_EXTERNC

/*
**==============================================================================
**
** Defines filter types.
** 
** UNIARY_TEMP filter was created by subscription call.
**
** UNIARY_TEMP & UNIARY_CONFIG filter: indication manager is responsible for
** paring query string and filter result indication instance;
**
** EVENTSTREAM_TEMP & EVENTSTREAM_CONFIG filter, indication manager just pass
** through the filter instance to provider; pass through the result indication instance;
** 
** COLLECTION_CONFIG, it contains a set of UNIARY filters;
**
** For all *_CONFIG filters, it created by Create Instance operation on
** CIM_IndicationFilter or CIM_IndicationFilterCollection class.
**
** *Only Subscription_OnAdd can add *_TEMP filter to container
** *Only Subscription_OnRemove can remove *_TEMP filter to container
**
**==============================================================================
*/
typedef enum _FilterType
{
    FILTER_UNARY_TEMP,             /* Temporary */
    FILTER_UNIARY_CONFIG,          /* Configued by client: WQL & CQL */
    FILTER_COLLECTION_CONFIG       /* Configued by client: Contains a Set of UNIARY filters */
}
FilterType;


/*
**==============================================================================
**
** Defines base type of Filter and FilterCollection
**
**==============================================================================
*/
typedef struct _FilterBase
{
    CimBase base;
    FilterType type;
    ErrorHandler errhandler;       /* Associated Subscription object, might be NULL if not associated yet  */
}
FilterBase;


/*
**==============================================================================
**
** Represents a CIM indication filter object
**
**==============================================================================
*/
typedef struct _Filter
{
    FilterBase base;

#if 0 /* To be enabled for indication profile */

    /* CIM_ManagedElement properties */
    MI_Char* InstanceID;
    MI_Char* Caption;
    MI_Char* Description;
    MI_Char* ElementName;

    /* CIM_IndicationFilter properties */
    MI_Char* SystemCreationClassName; /*key*/
    MI_Char* SystemName; /*key*/
    MI_Char* CreationClassName; /*key*/
    MI_Char* Name; /*key, unique identifier */

#endif

    MI_StringA SourceNamespaces;
    MI_Boolean IndividualSubscriptionSupported; /* default: true */
    MI_Char* Query;
    MI_Char* QueryLanguage;

    /* wql object */
    WQL* wql;
}
Filter;

extern CimBaseFT g_filterft;
extern const MI_Uint32 g_FilterMagic;

/* Creates a filter object */
_Success_(return != NULL)
Filter* Filter_New(
    _In_opt_z_ const MI_Char* Query,
    _In_z_ const MI_Char* QueryLanguage,
    _Outptr_opt_result_maybenull_ MI_Instance** error);

/* Add a reference to a filter object */
int Filter_AddRef(
    _Inout_ Filter* self);

/* Release a reference to a filter object */
int Filter_Release(
    _Inout_ Filter* self);

/* Add a reference to a FilterBase object */
int FilterBase_AddRef(
    _Inout_ FilterBase* self);

/* Release a reference to a FilterBase object */
int FilterBase_Release(
    _Inout_ FilterBase* self);

/* Get reference count */
int Filter_GetRefcount(_In_ Filter *self);
int FilterBase_GetRefcount(_In_ FilterBase *self);

/* Set source namespace */
int Filter_SetNamespace(
    _Inout_ Filter* self,
    _In_ MI_StringA* namespaces);

/* Set last error */
void Filter_SetLastError(
    _Inout_ Filter* self,
    _In_opt_ MI_Instance* error,
    MI_Result result);


END_EXTERNC

#endif /* _indication_indimgr_filter_h */

