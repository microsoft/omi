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

#ifndef _omi_pidfile_h
#define _omi_pidfile_h

#include <common.h>
#include <pal/strings.h>

BEGIN_EXTERNC

#if defined(CONFIG_POSIX)

int PIDFile_OpenWrite();

int PIDFile_Delete();

int PIDFile_Read(int* pid);

int PIDFile_Signal(int sig);

int PIDFile_IsRunning();

#endif /* defined(CONFIG_POSIX) */

END_EXTERNC

#endif /* _omi_pidfile_h */
