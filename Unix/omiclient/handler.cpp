/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "handler.h"

MI_BEGIN_NAMESPACE

Handler::~Handler() 
{ 
}

void Handler::HandleConnect()
{
}

void Handler::HandleConnectFailed()
{
}

void Handler::HandleDisconnect()
{
}

void Handler::HandleNoOp(Uint64 operationId)
{
}

void Handler::HandleInstance(Uint64 operationId, const DInstance& instance)
{
    MI_UNUSED(instance);
}

void Handler::HandleResult(Uint64 operationId, MI_Result result)
{
    MI_UNUSED(result);
}

/* If this version is not overridden then it calls into the original */
void Handler::HandleResult(Uint64 operationId, MI_Result result, const MI_Char *errorMessage, const DInstance* cimError)
{
    HandleResult(operationId, result);
    MI_UNUSED(errorMessage);
    MI_UNUSED(cimError);
}

MI_END_NAMESPACE
