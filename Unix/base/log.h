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

