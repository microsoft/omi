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

#ifndef __util_h
#define __util_h

#include <MI.h>
#include <stdlib.h>
#include <pal/strings.h>

#if defined(__cplusplus)
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define BEGIN_EXTERNC
# define END_EXTERNC
#endif

BEGIN_EXTERNC

char* TToStr(_Out_writes_z_(size) char* buf, size_t size, _In_z_ const TChar* src);

END_EXTERNC

#endif /* __util_h */
