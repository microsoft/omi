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

#ifndef _context_h
#define _context_h

#include <common.h>
#include <base/base.h>
#include "provmgr.h"

BEGIN_EXTERNC

typedef enum _Context_Type
{
    CTX_TYPE_SINGLE_ITEM = 0,   /* regular execution, post results to the caller */
    CTX_TYPE_IND_NOTINITIALIZED,    /* un-initialized indication context */
    CTX_TYPE_IND_READY,             /* indication context that is ready for operation */
    CTX_TYPE_INVOKE_WITH_INSTANCE   /* calling get before invoke - call invoke with result instance */
}
Context_Type;

static const MI_Uint32 CONTEXT_UNPOSTED_MAGIC = 0x35EB3D3B;
static const MI_Uint32 CONTEXT_POSTED_MAGIC = 0x3BCC0435;

typedef struct _Context
{
    MI_Context base;
    MI_Uint32 magic;                    /* CONTEXT_UNPOSTED_MAGIC or CONTEXT_POSTED_MAGIC if in use; 0xFFFFFFFF if not */

    /* Pointer to the request message (containing the callback) */
    Message* request;
    Message* loadRequest;

    /* chain processing */
    Context_Type chainType;

    /* delayed invoke parameters */
    MI_MethodDecl* md;
    MI_Instance* inst;
    MI_Instance* instParams;
    void * prov_self;

    /* Cancelled flag */
    MI_Boolean cancelled;

    /* Reference to Provider */
    Provider* provider;

    /* Result to caller */
    MI_Result* result;

    /* If non-null, PostInstance() only forwards 1st matching instance. */
    MI_Instance* instanceName;

    /* Whether instanceName has been matched yet. */
    MI_Boolean matchedInstanceName;
}
Context;

void Context_Init(
    Context* self,
    Provider* provider);

void Context_Destroy(
    Context* self);

extern MI_ContextFT __mi_contextFT;

END_EXTERNC

#endif /* _context_h */
