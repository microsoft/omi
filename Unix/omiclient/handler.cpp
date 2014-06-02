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
