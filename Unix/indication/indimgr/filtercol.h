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

#ifndef _indication_indimgr_filtercol_h
#define _indication_indimgr_filtercol_h

#include <common.h>
#include <base/list.h>
#include "filter.h"

#if defined(_MSC_VER)
#else
#endif

/*
**==============================================================================
** NOTE:
** CIM_FilterCollection is associated with CIM_IndicationFilter by following
** class:
**
** [Association] class CIM_MemberOfCollection {
**    [Key, Aggregate, Description ("The Collection that aggregates members." )]
**    CIM_Collection REF Collection;
**    [Key, Description ( "The aggregated member of the Collection." )]
**    CIM_ManagedElement REF Member;
**};
**
**==============================================================================
*/

BEGIN_EXTERNC

/*
**==============================================================================
**
** Represents a list of Filter
**
**==============================================================================
*/
typedef struct _FilterList
{
    FilterBase* head;
    FilterBase* tail;
}FilterList;


/*
**==============================================================================
**
** Represents a filter collection object,
**
** Based on DMTF:DSP1054:1.1.0:SECTION 7.6.2: Nested Filter Collections:
** An instance of CIM_FilterCollection may be associated with one or more
** instances of CIM_FilterCollection through an instance of
** CIM_MemberOfCollection.
**
**==============================================================================
*/
typedef struct _FilterCollection
{
    FilterBase base;

    /* Associated filter or filter collection object */
    FilterList filterList;

#if 0 /* To be enabled for indication profile */

    /* CIM_ManagedElement properties */
    MI_Char* InstanceID; /* override key*/
    MI_Char* Caption;
    MI_Char* Description;
    MI_Char* ElementName;

    /* CIM_FilterCollection properties */
    MI_Char* CollectionName;

#endif
}
FilterCollection;

/* Create a filter collection */
FilterCollection* FilterCollection_New();

/* Add a filter to collection */
/* FilterCollection holds a reference to the filter object upon succeed */
int FilterCollection_AddFilter(_In_ FilterCollection* self,
                               _In_ Filter* filter);

END_EXTERNC

#endif /* _indication_indimgr_filtercol_h */
