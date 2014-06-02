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

#include "ut.h"

#if defined(CONFIG_ENABLE_FAULTINJECTION)

using namespace TestSystem;

NitsModuleSetup(OMIFaultSimTestSetup)
    NitsTrace(PAL_T("OMIFaultSimTestSetup being run"));
    NitsEnableFaultSimAll();
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup

NitsCleanup(OMIFaultSimTestSetup)
    NitsTrace(PAL_T("Cleanup of OMIFaultSimTestSetup being run"));
    NitsDisableFaultSimAll();
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

#endif
