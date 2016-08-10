/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "oicommon.h"
#include "Syslog.h"
#include <pal/strings.h>
#include <stdio.h>

#define SYSLOG_CGEN_START NL \
    "#define APPNAME \"%s\"" NL \
    "#define LOGOPT %s" NL \
    "#define LOGFACILITY %s" NL \
    "#include <oi/oi_syslog.h>" NL

#define SYSLOGEVENT  "SYSLOG_EVENT%d("
#define SYSLOGEVENTD "SYSLOG_EVENTD%d("

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
        int ArgCount = CountArguments(arg);
        int wrote;

        buf[0] = 0;

#if defined(CONFIG_OS_WINDOWS)
        wrote = sprintf_s(buf, BUFFER_SIZE, UseDebugMacro(current->Priority) ? SYSLOGEVENTD : SYSLOGEVENT, ArgCount);
#else
        wrote = sprintf(buf, UseDebugMacro(current->Priority) ? SYSLOGEVENTD : SYSLOGEVENT, ArgCount );
#endif
        if (wrote >= BUFFER_SIZE)
            goto error;

        if (Strcat(buf, BUFFER_SIZE, current->EventId) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, current->Name) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, current->Priority) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, ", PAL_T(") == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, current->Format) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, ")") == 0)
            goto error;

        while(arg)
        {
            OIArgument * next = arg->next;

            if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
                goto error;
            if (Strcat(buf, BUFFER_SIZE, arg->Type) == 0)
                goto error;

            arg = next;
        }
        
        if (Strcat(buf, BUFFER_SIZE, ")") == 0)
                goto error;

        /* buf may contain %d which we need to preserve */
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
PAL_Boolean GenerateSyslog(
    OIEvent * events,
    const char * ident,
    const char * options,
    const char * facility,
    const char * target)
{
    /* overwrite existing file */
    FILE* out = fopen(target, "w");
    if (!out)
    {
        OIERROR1("Failed to open file [%s] for writing!", target);
        return PAL_FALSE;
    }

    fprintf(out, SYSLOG_CGEN_START, ident, options, facility);
    fprintf(out, NL);

    if (!_AddEvents(out, events))
    {
        fclose(out);
        OIERROR1("Failed to generate syslog implementation for file [%s]!", target);
        return PAL_FALSE;
    }

    fclose(out);

    OITRACE("Success!");
    return PAL_TRUE;
}
