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

/* Hand coded Windows version of config.h */
#ifndef _config_h
#define _config_h

#define CONFIG_PLATFORM "WINDOWS_IX86_MSVC"
#define CONFIG_OS "WINDOWS"

#if defined(_M_X64)
# define CONFIG_ARCH "X86_64"
# define CONFIG_ARCH_X86_64
#else
# define CONFIG_ARCH "IX86"
# define CONFIG_ARCH_IX86
#endif

#define CONFIG_COMPILER "MSVC"
#define CONFIG_PLATFORM_WINDOWS_IX86_MSVC
#define CONFIG_OS_WINDOWS
#define CONFIG_COMPILER_MSVC

#if defined(_DEBUG)
# define CONFIG_ENABLE_DEBUG
#endif

#define CONFIG_HAVE_FUNCTION_MACRO 1

#define CONFIG_NAMESPACE "root/cimv2"

#define CONFIG_PREFIX "."
#define CONFIG_LOCALSTATEDIR "./var"
#define CONFIG_AUTHDIR "./var/omiauth"
#define CONFIG_SYSCONFDIR "./etc"
#define CONFIG_PROVIDERDIR "./lib"
#define CONFIG_CERTSDIR "./etc/ssl/certs"
#define CONFIG_CERTSDIR "./etc/ssl/certs"
#define CONFIG_DATADIR "./share"
#define CONFIG_INCLUDEDIR "./include"
#define CONFIG_TMPDIR "./tmp"
#define CONFIG_BINPORT 7777
#define CONFIG_HTTPPORT 7778
#define CONFIG_HTTPSPORT 7779


#if defined(_DEBUG) && defined(_WIN64)
#define CONFIG_LIBDIR "./Deliverables/omi/Debug/x64"
#define CONFIG_BINDIR "./Deliverables/omi/Debug/x64"
#elif defined(_DEBUG) && !defined(_WIN64)
#define CONFIG_LIBDIR "./Deliverables/omi/Debug/Win32"
#define CONFIG_BINDIR "./Deliverables/omi/Debug/Win32"
#elif !defined(_DEBUG) && defined(_WIN64)
#define CONFIG_LIBDIR "./Deliverables/omi/Release/x64"
#define CONFIG_BINDIR "./Deliverables/omi/Release/x64"
#elif !defined(_DEBUG) && !defined(_WIN64)
#define CONFIG_LIBDIR "./Deliverables/omi/Release/Win32"
#define CONFIG_BINDIR "./Deliverables/omi/Release/Win32"
#else
# error "unexpected"
#endif

#define CONFIG_SHLIBEXT "dll"

#endif /* _config_h */
