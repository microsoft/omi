/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omiclient_linkage_h
#define _omiclient_linkage_h

#include <common.h>

#ifdef BUILDING_OMICLIENT
#  define OMICLIENT_LINKAGE MI_EXPORT
#else
#  define OMICLIENT_LINKAGE 
#endif

#endif /* _omiclient_linkage_h */
