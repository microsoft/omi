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
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

PAL_BEGIN_EXTERNC

const char* GetFullyQualifiedDomainName();

PAL_END_EXTERNC

#endif /* _pal_host_h */
