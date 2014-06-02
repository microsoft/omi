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

#ifndef _OI_common_h_
#define _OI_common_h_

#include <pal/palcommon.h>
#include <pal/strings.h>

PAL_BEGIN_EXTERNC

#define BUFFER_SIZE 1024
#define NL "\n"

#if 1
# define OIERRORPREFIX "[ERROR] %s:%d "
# define OITRACE printf
# define OIERROR(FORMAT) printf( OIERRORPREFIX FORMAT NL, __FILE__, __LINE__ )
# define OIERROR1(FORMAT, A0) printf( OIERRORPREFIX FORMAT NL, __FILE__, __LINE__, (A0) )
# define OIERROR2(FORMAT, A0, A1) printf( OIERRORPREFIX FORMAT NL, __FILE__, __LINE__, (A0), (A1) )
#else
# define OITRACE
# define OIERROR(FORMAT)
# define OIERROR1(FORMAT, A0)
#endif

PAL_INLINE PAL_Boolean UseDebugMacro(const char * priority)
{
    if ((Strcmp(priority, "LOG_DEBUG") == 0) || (Strcmp(priority, "LOG_VERBOSE") == 0))
        return PAL_TRUE;
    else
        return PAL_FALSE;
}

PAL_END_EXTERNC

#endif /* _OI_common_h_ */
