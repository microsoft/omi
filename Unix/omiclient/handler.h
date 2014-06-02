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

#ifndef _mi_handler_h
#define _mi_handler_h

#include <micxx/micxx.h>
#include <micxx/dinstance.h>
#include "linkage.h"

MI_BEGIN_NAMESPACE

class OMICLIENT_LINKAGE Handler
{
public:

    virtual ~Handler();

    virtual void HandleConnect();

    virtual void HandleConnectFailed();

    virtual void HandleDisconnect();

    virtual void HandleNoOp(Uint64 operationId);

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance);

    virtual void HandleResult(Uint64 operationId, MI_Result result);

    virtual void HandleResult(Uint64 operationId, MI_Result result, const MI_Char *errorMessage, const DInstance* cimError);
};

MI_END_NAMESPACE

#endif /* _mi_handler_h */
