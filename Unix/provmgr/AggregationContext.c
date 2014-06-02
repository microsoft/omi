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

#include "AggregationContext.h"
#include "SubMgr.h"
#include <indication/common/indilog.h>

AggregationContext* AggrContext_New()
{
    AggregationContext* newContext = (AggregationContext*)PAL_Calloc(1, sizeof(AggregationContext));
    if (!newContext)
    {
        LOGD_ALLOC_OOM;
        return NULL;
    }
    else
    {
        return newContext;
    }
}

_Use_decl_annotations_
void AggrContext_Delete(
    AggregationContext* self )
{
    DEBUG_ASSERT (self && (self->baseCtx.magic == 0x35eb3d3b));
    AggrContext_Close( self );
    PAL_Free(self);
}

/*
 * Perform initialization of an AggregationContext object.
 */
_Use_decl_annotations_
MI_Result AggrContext_Init(
    AggregationContext* self,
    Provider* provider,
    struct _SubscriptionManager* mgr )
{
    MI_Result result = MI_RESULT_OK;
    DEBUG_ASSERT (self && provider && mgr);

    /* Do AggregationContext set up prior to initializing its underlying 
     * Context because Context_Init also ACKs the Strand open request. 
     */
    self->mgr = mgr;

    result = Context_Init_ByType(&self->baseCtx, provider, NULL, CTX_TYPE_IND_AGGREGATION );
    if (MI_RESULT_OK != result)
        self->mgr = NULL;

    return result;
}

_Use_decl_annotations_
void AggrContext_Close(
    AggregationContext* self )
{
    DEBUG_ASSERT( self && (self->baseCtx.magic == 0x35eb3d3b) );
    Context_Close(&self->baseCtx);
}

_Use_decl_annotations_
struct _SubscriptionManager* AggrContext_GetManager(
    AggregationContext* self )
{
    return self->mgr;
}
