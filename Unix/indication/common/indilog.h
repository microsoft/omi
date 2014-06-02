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

#ifndef _indication_common_indilog_h
#define _indication_common_indilog_h

#include <base/log.h>

#define LOGD_BATCH_ZDUP_OOM     trace_BatchZdup_Failed()
#define LOGD_BATCH_OOM          trace_BatchAllocFailed()
#define LOGD_BATCH_CREATE_OOM   trace_BatchCreationFailed()
#define LOGD_ALLOC_OOM          trace_HeapMemoryAllocFailed()

#endif /* _indication_common_indilog_h */
