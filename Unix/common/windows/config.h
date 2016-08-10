/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#ifndef CONFIG_OS_WINDOWS
#define CONFIG_OS_WINDOWS
#endif
#define CONFIG_COMPILER_MSVC

#if defined(DBG) || defined(_DEBUG)
# define CONFIG_ENABLE_DEBUG
#endif

#define CONFIG_HAVE_FUNCTION_MACRO 1
#define CONFIG_ENABLE_WCHAR 1
#define CONFIG_HAVE_ATOMIC_INTRINSICS 1
#define CONFIG_HAVE_WCSTOLL 1
#define CONFIG_HAVE_WCSDUP 1
#define CONFIG_HAVE_WCSCASECMP 1
#define CONFIG_HAVE_BACKTRACE 1
#define CONFIG_HAVE_SYNC_SYNCHRONIZE 1
#define CONFIG_HAVE_SEM_TIMEDWAIT 1
#define CONFIG_HAVE_SCHED_GETCPU 1
#define CONFIG_HAVE_BUILTIN_CTZ 1
#define CONFIG_HAVE_BUILTIN_PREFETCH 1

#define CONFIG_NAMESPACE "root/cimv2"

#define CONFIG_PREFIX "."
#define CONFIG_SRCDIR "."
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

#include <ntverp.h>
/* TODO: Make these properly represented */
#define CONFIG_TIMESTAMP L"timestamp"
#define CONFIG_DATE L"date"

#define LVER_PRODUCTNAME_STR L"Microsoft (c) Windows (c) Operating System"
#define CONFIG_PRODUCT L" " LVER_PRODUCTNAME_STR
#define CONFIG_VERSION LVER_PRODUCTVERSION_STR
#define CONFIG_FULLPRODUCT CONFIG_PRODUCT L" " CONFIG_VERSION
#define CONFIG_MAJOR 0
#define CONFIG_MINOR 0
#define CONFIG_REVISION 0

#define CONFIG_SEMNAMEGLOBALPREFIX "Global\\"
#define CONFIG_SHMNAMEGLOBALPREFIX "Global\\"
#define CONFIG_SEMNAMELOCALPREFIX ""
#define CONFIG_SHMNAMELOCALPREFIX ""

#define CONFIG_ENABLE_FAULTINJECTION

#endif /* _config_h */
