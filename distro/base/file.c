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

#include <stdio.h>
#include "file.h"
#include <io/io.h>

int File_Copy(const char* src, const char* dest)
{
    FILE* is = NULL;
    FILE* os = NULL;
    char buf[4096];

    /* Open input file */
    is = Fopen(src, "rb");
    if (!is)
        return -1;

#if defined(CONFIG_POSIX)

    /* Unlink output file if it exists */
    if (access(dest, F_OK) == 0)
    {
        unlink(dest);
    }

#endif

    /* Open output file */
    os = Fopen(dest, "wb");
    if (!os)
    {
        fclose(is);
        return -1;
    }

    /* Copy file */
    for (;;)
    {
#if defined(CONFIG_OS_WINDOWS)
        long n = (long)fread(buf, 1, sizeof(buf), is);
        long m;
#else
        ssize_t n = fread(buf, 1, sizeof(buf), is);
        ssize_t m;
#endif

        if (n <= 0)
            break;

#if defined(CONFIG_OS_WINDOWS)
        m  = (long)fwrite(buf, 1, n, os);
#else
        m  = fwrite(buf, 1, n, os);
#endif

        if (m != n)
        {
            fclose(is);
            fclose(os);
            return -1;
        }
    }

    fclose(is);
    fclose(os);
    return 0;
}
