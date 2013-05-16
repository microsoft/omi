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

#ifndef _omi_time_h
#define _omi_time_h

#include <common.h>

BEGIN_EXTERNC

void Time_Sleep(MI_Uint64 msec);

/* invalid time value;
  based on 'memset(0) to init' philosophy; this value must be 0;
  do not re-assign it */
#define TIME_NEVER  0

/* returns current time in micro-sec (usec) since Epoch */
MI_Result Time_Now(
    MI_Uint64* time_usec);


END_EXTERNC

#endif /* _omi_time_h */
