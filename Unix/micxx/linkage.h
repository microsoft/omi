/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_linkage_h
#define _micxx_linkage_h

#include <MI.h>

#ifdef BUILDING_MICXX
#  define MICXX_LINKAGE MI_EXPORT
#else
#  define MICXX_LINKAGE MI_IMPORT
#endif

#define MI_BEGIN_NAMESPACE namespace mi {
#define MI_END_NAMESPACE }

#endif /* _micxx_linkage_h */
