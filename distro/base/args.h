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

#ifndef _omi_args_h
#define _omi_args_h

#include "config.h"
#include <string.h>
#include <common.h>

BEGIN_EXTERNC

/* Removes the i-th argument from the argc/argv array */
MI_INLINE void Args_Remove(int* argc, char*** argv, size_t i)
{
    memmove(&(*argv)[i], &(*argv)[i+1], sizeof(char*) * ((*argc)-i-1));
    *argc -= 1;
}

END_EXTERNC

#endif /* _omi_args_h */
