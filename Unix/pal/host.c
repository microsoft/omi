/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/strings.h>
#include <ctype.h>

#if defined(PAL_HAVE_POSIX)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#endif


/*
**==============================================================================
**
**  Host name (POSIX)
**
**
**==============================================================================
*/

#if defined(PAL_HAVE_POSIX)

/*
 *  char* getFullyQualifiedDomainName()
 *
 *  returns a new copy of he primary full qualified domain name as utf8/ascii. 
 *
 */ 

const char *
GetFullyQualifiedDomainName()

{
    struct addrinfo hints, *info;
    int gai_result;

    char hostname[1024];
    hostname[1023] = '\0';

    gethostname(hostname, 1023);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    /*either IPV4 or IPV6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    if ((gai_result = getaddrinfo(hostname, NULL, &hints, &info)) != 0)
    {
        return NULL;
    }

    if (!info)
    {
        return NULL;
    }

    if (!info->ai_canonname) 
    {
        return NULL;
    }

    return PAL_Strdup(info->ai_canonname);
}

#endif /* defined(PAL_HAVE_POSIX) */


