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

#ifndef _micxx_context_h
#define _micxx_context_h

#include <MI.h>
#include "linkage.h"
#include "instance.h"

MI_BEGIN_NAMESPACE

class CIM_Error_Class;

class MICXX_LINKAGE Context
{
public:

    Context(
        MI_Context* context);

    Context(
        MI_Context* context,
        MI_Result* result);

    Context(
        const Context& x);

    MI_Result Post(
        const Instance& instance);

    MI_Result Post(
        const Instance& indication, 
        MI_Uint32 subscriptionIDCount,
        const String& bookmark);

    MI_Result Post(MI_Result result);

    MI_Result Post(
        MI_Result result, 
        const String& message);

    MI_Result Post(
        MI_Result result, 
        const CIM_Error_Class& instance);

    MI_Result RequestUnload();

    MI_Result RefuseUnload();

private:

    Context();
    Context& operator=(const Context&);

    MI_Context* m_context;
    MI_Result*  m_result;
};

MI_END_NAMESPACE

#endif /* _micxx_context_h */
