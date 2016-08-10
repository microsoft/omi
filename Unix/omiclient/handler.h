/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
