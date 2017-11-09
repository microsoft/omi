/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
    if (Strcmp(priority, "LOG_VERBOSE") == 0)
        return PAL_TRUE;
    else
        return PAL_FALSE;
}

PAL_END_EXTERNC

#endif /* _OI_common_h_ */
