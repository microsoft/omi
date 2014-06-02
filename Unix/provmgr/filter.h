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

#ifndef _provmgr_filter_h
#define _provmgr_filter_h

#include <common.h>
#include <base/messages.h>
#include <wql/wql.h>

BEGIN_EXTERNC

typedef struct _InstanceFilter InstanceFilter;

/*
 * Defines common internal operations for structs derived from InstanceFilter.
 */
typedef struct _InstanceFilterFT
{
    /* Evaluates the specified instance using the pre-defined filter */
    MI_Result (*Filter)(
        _In_ InstanceFilter* self, 
        _In_ const MI_Instance* instance,
        _Out_ MI_Boolean* isMatch);

    /* Cleans up the InstanceFilter's internal state */
    void (*Destroy)(
        _In_ InstanceFilter* self);

    /* Gets the query WQL or CQL */
    WQL* (*GetWQL)(
        _In_ InstanceFilter* self);
}
InstanceFilterFT;

/*
 * Base structure for all "derived" InstanceFilter.
 */
struct _InstanceFilter
{
    MI_Filter base;
    MI_Uint32 magic;

    InstanceFilterFT* ft;

    Message* msg;
};



/*
 * Generates a "derived" InstanceFilter structure based on the specified
 * query within the message.  It allocates the filter using the msg's
 * Batch and initializes internal values.
 *
 * Returns newly allocated filter or NULL for failure.
 */
InstanceFilter* InstanceFilter_New( 
    _In_ Message* msg);

/*
 * Deactivates the filter and cleans it up.
 */
void InstanceFilter_Destroy(
    _Inout_ InstanceFilter* self );

MI_Result InstanceFilter_Filter(
    _In_ InstanceFilter* self, 
    _In_ const MI_Instance* instance,
    _Out_ MI_Boolean* isMatch );

WQL* InstanceFilter_GetWQL(
        _In_ InstanceFilter* self );

END_EXTERNC

#endif /* _provmgr_filter_h */

