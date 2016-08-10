/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_log_h
#define _omi_log_h

#include "logbase.h"

#if defined(OI_INCLUDE_HEADER)
# include <base/oi_traces.h>
#else
# include "omistructures.h"
#endif
#if !defined(NOTINCLUDE_OMILOGGING)

#if defined(CONFIG_OS_WINDOWS)
# ifndef _oiwinomi_h
# define _oiwinomi_h
# include <base/oiwinomi.h>
# endif
#else
# ifndef _oiomi_h
# define _oiomi_h
# include <base/oiomi.h>
# endif
#endif //NOT_INCLUDE_OMILOGGING
#endif

BEGIN_EXTERNC

/* Creates log file name of the form "<LOGDIR>/prefix.log"*/
int CreateLogFileNameWithPrefix(_In_z_ const char *prefix, _Pre_writable_size_(PAL_MAX_PATH_SIZE) PAL_Char finalPath[PAL_MAX_PATH_SIZE]);

END_EXTERNC

#endif /* _omi_log_h */

