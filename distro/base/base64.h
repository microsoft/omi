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

#ifndef _omi_base64_h
#define _omi_base64_h

#include <common.h>

BEGIN_EXTERNC

typedef int (*Base64EncCallback)(
    const char* data, 
    size_t size, 
    void* callbackData);

int Base64Enc(
    const void* data,
    size_t size,
    Base64EncCallback callback,
    void* callbackData);

typedef int (*Base64DecCallback)(
    const void* data, 
    size_t size, 
    void* callbackData);

int Base64Dec(
    const void* data_,
    size_t size,
    Base64DecCallback callback,
    void* callbackData);

END_EXTERNC

#endif /* _omi_base64_h */
