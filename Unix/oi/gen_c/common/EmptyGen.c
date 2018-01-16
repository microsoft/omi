/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

        wrote = sprintf(buf, FUNCTIONSTART);
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
