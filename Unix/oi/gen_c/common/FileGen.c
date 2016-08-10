/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "oicommon.h"
#include "FileGen.h"
#include <pal/strings.h>
#include <stdio.h>

#define FILE_CGEN_START NL \
    "#include <oi/oi_file.h>" NL \
     NL

#define FILEEVENT  "FILE_EVENT%d("
#define FILEEVENTD "FILE_EVENTD%d("

#define FILECALLIMPL0 \
    "#if defined(CONFIG_ENABLE_DEBUG)" NL \
    "#define %s(%s) %s_Impl(__FILE__, __LINE__%s)" NL \
    "#else" NL \
    "#define %s(%s) %s_Impl(0, 0%s)" NL \
    "#endif" NL
#define FILECALLIMPLN \
    "#if defined(CONFIG_ENABLE_DEBUG)" NL \
    "#define %s(%s) %s_Impl(__FILE__, __LINE__, %s)" NL \
    "#else" NL \
    "#define %s(%s) %s_Impl(0, 0, %s)" NL \
    "#endif" NL

#define TSTRING_TYPE1 "const TChar *"
#define TSTRING_TYPE2 "const TChar*"
#define TSTRING_TYPE3 "const MI_Char *"
#define TSTRING_TYPE4 "const MI_Char*"
#define TSTRING_TYPE5 "TChar *"
#define TSTRING_TYPE6 "TChar*"
#define TSTRING_TYPE7 "MI_Char *"
#define TSTRING_TYPE8 "MI_Char*"

PAL_Boolean _isTStringType(_In_z_ const char * type)
{
    return ((Strcmp(type, TSTRING_TYPE1) == 0)
         || (Strcmp(type, TSTRING_TYPE2) == 0)
         || (Strcmp(type, TSTRING_TYPE3) == 0)
         || (Strcmp(type, TSTRING_TYPE4) == 0)
         || (Strcmp(type, TSTRING_TYPE5) == 0)
         || (Strcmp(type, TSTRING_TYPE6) == 0)
         || (Strcmp(type, TSTRING_TYPE7) == 0)
         || (Strcmp(type, TSTRING_TYPE8) == 0));
}   

#define STRING_TYPE1 "const char *"
#define STRING_TYPE2 "const char*"
#define STRING_TYPE3 "char *"
#define STRING_TYPE4 "char*"

PAL_Boolean __isStringType(_In_z_ const char * type)
{
    return ((Strcmp(type, STRING_TYPE1) == 0)
        || (Strcmp(type, STRING_TYPE2) == 0)
        || (Strcmp(type, STRING_TYPE3) == 0)
        || (Strcmp(type, STRING_TYPE4) == 0));
}
         

static PAL_Boolean _AddEvents(
    _In_ FILE * out,
    _In_ OIEvent * events)
{
    char buf[BUFFER_SIZE];
    OIEvent * current = events;

    while(current)
    {
        OIEvent * next = current->next;
        OIArgument * arg;
        int ArgCount = CountArguments(current->Argument);
        int wrote;

        {
            int i = 0;
            char plist1[BUFFER_SIZE];
            char plist2[BUFFER_SIZE];
            plist1[0] = 0;
            plist2[0] = 0;
            arg = current->Argument;
            while(arg)
            {
                char param1[BUFFER_SIZE];
                char param2[BUFFER_SIZE];
                const char * argType = arg->Type;
                char * formatString1 = "a%d";
                char * formatString2 = formatString1;

                param1[0] = 0;
                param2[0] = 0;
                if (_isTStringType(argType))
                {
                    formatString2 = "tcs(a%d)";
                }
                else if (__isStringType(argType))
                {
                    formatString2 = "scs(a%d)";
                }

                  
#if defined(CONFIG_OS_WINDOWS)
                wrote = sprintf_s(param1, BUFFER_SIZE, formatString1, i);
                wrote = sprintf_s(param2, BUFFER_SIZE, formatString2, i);
#else
                wrote = sprintf(param1, formatString1, i);
                wrote = sprintf(param2, formatString2, i);
#endif
                if (wrote >= BUFFER_SIZE)
                    goto error;

                if (Strcat(plist1, BUFFER_SIZE, param1) == 0)
                    goto error;
                
                if (Strcat(plist2, BUFFER_SIZE, param2) == 0)
                    goto error;

                // add a comma if this is NOT the last argument
                arg = arg->next;
                i++;
                if (arg)
                {
                    if (Strcat(plist1, BUFFER_SIZE, ", ") == 0)
                        goto error;
                    if (Strcat(plist2, BUFFER_SIZE, ", ") == 0)
                        goto error;
                }
            }

            buf[0] = 0;
#if defined(CONFIG_OS_WINDOWS)
            wrote = sprintf_s(buf, BUFFER_SIZE, (ArgCount == 0)? FILECALLIMPL0 : FILECALLIMPLN, 
#else
            wrote = sprintf(buf, (ArgCount == 0)? FILECALLIMPL0 : FILECALLIMPLN, 
#endif
                current->Name, plist1, current->Name, plist2, current->Name, plist1, current->Name, plist2);

            fprintf(out, "%s", buf);
        }

        buf[0] = 0;
#if defined(CONFIG_OS_WINDOWS)
        wrote = sprintf_s(buf, BUFFER_SIZE, UseDebugMacro(current->Priority) ? FILEEVENTD : FILEEVENT, ArgCount);
#else
        wrote = sprintf(buf, UseDebugMacro(current->Priority) ? FILEEVENTD : FILEEVENT, ArgCount );
#endif
        if (wrote >= BUFFER_SIZE)
            goto error;

        if (Strcat(buf, BUFFER_SIZE, current->EventId) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, current->Name) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, "_Impl") == 0)
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

        arg = current->Argument;
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
PAL_Boolean GenerateFile(
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
