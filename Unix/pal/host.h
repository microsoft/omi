/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_host_h
#define _pal_host_h

#include "palcommon.h"

#if defined(_MSC_VER)
# include <io.h>
# include <direct.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
#endif

PAL_BEGIN_EXTERNC

const char* GetFullyQualifiedDomainName();

PAL_END_EXTERNC

#endif /* _pal_host_h */
