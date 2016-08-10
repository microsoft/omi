/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
