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

#include "oicommon.h"
#include "EmptyGen.h"
#include <pal/strings.h>
#include <stdio.h>

#define FILE_CGEN_START NL \
    "#include <oi/oi_noop.h>" NL \
     NL

#define FUNCTIONSTART "void "

static PAL_Boolean _AddEvents(
    _In_ FILE * out,
    _In_ OIEvent * events)
{
    char buf[BUFFER_SIZE];
    OIEvent * current = events;

    while(current)
    {
        OIEvent * next = current->next;
        OIArgument * arg = current->Argument;
        int wrote;

        buf[0] = 0;

#if defined(CONFIG_OS_WINDOWS)
        wrote = sprintf_s(buf, BUFFER_SIZE, FUNCTIONSTART);
#else
        wrote = sprintf(buf, FUNCTIONSTART);
#endif
        if (wrote >= BUFFER_SIZE)
            goto error;

        if (Strcat(buf, BUFFER_SIZE, current->Name) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, "( ") == 0)
            goto error;

        while(arg)
        {
            OIArgument * next = arg->next;

            if (Strcat(buf, BUFFER_SIZE, arg->Type) == 0)
                goto error;
            if (Strcat(buf, BUFFER_SIZE, " ") == 0)
                goto error;
            if (Strcat(buf, BUFFER_SIZE, arg->Name) == 0)
                goto error;

            if (next)
            {
                if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
                    goto error;
            }
            arg = next;            
        }
        
        if (Strcat(buf, BUFFER_SIZE, " ) {}") == 0)
            goto error;

        /* buf may contain '%' which we need to preserve */
        fprintf(out, "%s", buf);
        fprintf(out, NL);

        current = next;
    }

    return PAL_TRUE;

error:
    OIERROR1("Out of buffer space while generating! Buffer so far was [%s]", buf);
    return PAL_FALSE;
}


/************* Public Definitions ******************/

_Use_decl_annotations_
PAL_Boolean GenerateEmpty(
    OIEvent * events,
    const char * target)
{
    /* overwrite existing file */
    FILE* out = fopen(target, "w");
    if (!out)
    {
        OIERROR1("Failed to open file [%s] for writing!", target);
        return PAL_FALSE;
    }

    fprintf(out, FILE_CGEN_START);
    fprintf(out, NL);

    if (!_AddEvents(out, events))
    {
        fclose(out);
        OIERROR1("Failed to generate logging implementation for file [%s]!", target);
        return PAL_FALSE;
    }

    fclose(out);

    OITRACE("Success!");
    return PAL_TRUE;
}
