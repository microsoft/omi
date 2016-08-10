/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ManifestGen.h"
#include "oicommon.h"
#include <pal/strings.h>

static const char MANIFEST_HEADER[] = 
    "<?xml version='1.0' encoding='utf-8' standalone='yes'?>" NL \
    "<instrumentationManifest xmlns=\"http://schemas.microsoft.com/win/2004/08/events\">" NL \
    "  <instrumentation" NL \
    "      xmlns:win=\"http://manifests.microsoft.com/win/2004/08/windows/events\"" NL \
    "      xmlns:xs=\"http://www.w3.org/2001/XMLSchema\"" NL \
    "      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" NL \
    "      >" NL;

static const char MANIFEST_PROVIDERDECL[] =
    "    <events xmlns=\"http://schemas.microsoft.com/win/2004/08/events\">" NL \
    "      <provider" NL \
    "          guid=\"%s\"" NL \
    "          messageFileName=\"%s\"" NL \
    "          name=\"%s\"" NL \
    "          parameterFileName=\"%s\"" NL \
    "          resourceFileName=\"%s\"" NL \
    "          symbol=\"%s\"" NL \
    "          >" NL;

static const char MANIFEST_CHANNEL_TAG[] =
    "        <channels>" NL;

static const char MANIFEST_CHANNEL[] =
    "          <channel" NL \
    "              chid=\"%s\"" NL \
    "              enabled=\"%s\"" NL \
    "              name=\"%s/%s\"" NL \
    "              type=\"%s\"" NL \
    "              />" NL;

static const char MANIFEST_CHANNEL_CLOSE[] =
    "        </channels>" NL;

static const char MANIFEST_TASK_OPEN[] =
    "        <tasks>" NL;

static const char MANIFEST_TASK_DEF[] =
    "          <task" NL \
    "              message=\"$(string.Task.%s)\"" NL \
    "              name=\"%s\"" NL \
    "              symbol=\"TASK_%s\"" NL \
    "              value=\"%d\"/>" NL;

static const char MANIFEST_TASK_CLOSE[] =
    "        </tasks>" NL;

static const char MANIFEST_OPCODE_OPEN[] =
    "        <opcodes>" NL;

static const char MANIFEST_OPCODE_DEF[] =
    "          <opcode" NL \
    "              message=\"$(string.Opcode.%s)\"" NL \
    "              name=\"%s\"" NL \
    "              symbol=\"OPCODE_%s\"" NL \
    "              value=\"%d\"/>" NL;

static const char MANIFEST_OPCODE_CLOSE[] =
    "        </opcodes>" NL;

static const char MANIFEST_KEYWORD_OPEN[] =
    "        <keywords>" NL;

static const char MANIFEST_KEYWORD_DEF[] =
    "          <keyword" NL \
    "              mask=\"0x%I64x\"" NL \
    "              name=\"%s\"" NL \
    "              symbol=\"KEYWORD_%s\"/>" NL;

static const char MANIFEST_KEYWORD_CLOSE[] =
    "        </keywords>" NL;

static const char MANIFEST_EVENTSTAG[] =
    "        <events>" NL;

static const char EVENT_START[] =  
    "          <event" NL;
static const char EVENT_CHANNEL[] =  
    "              channel=\"%s\"" NL;
static const char EVENT_LEVELMESSAGESYMBOL[] =  
    "              level=\"%s\"" NL \
    "              message=\"$(string.%s)\"" NL \
    "              symbol=\"%s\"" NL;
static const char EVENT_TASK[] =  
    "              task=\"%s\"" NL;
static const char EVENT_TEMPLATEVALUE[] =  
    "              template=\"tid_%s\"" NL \
    "              value=\"%s\"" NL \
    "              />" NL;

static const char TEMPLATES_HEADER[] = 
    "        </events>" NL \
    "        <templates>" NL;

static const char TEMPLATE_HEADER[] = 
    "          <template tid=\"tid_%s\">" NL;

static const char DATA_TEMPLATE[] = 
    "            <data" NL \
    "                inType=\"%s\"" NL \
    "                name=\"%s\"" NL \
    "                />" NL;

static const char TEMPLATE_TAIL[] = 
    "          </template>" NL;

static const char TEMPLATE_EMPTY[] = 
    "          <template tid=\"tid_%s\"/>" NL;

static const char STRINGTABLE_HEADER[] = 
    "        </templates>" NL \
    "      </provider>" NL \
    "    </events>" NL \
    "  </instrumentation>" NL \
    "  <localization>" NL \
    "    <resources culture=\"en-US\">" NL \
    "      <stringTable>" NL;

static const char STRING_TEMPLATE[] = 
    "        <string" NL \
    "            id=\"%s\"" NL \
    "            value=%s" NL \
    "            />" NL;

static const char STRING_TEMPLATE_QUOTES[] = 
    "        <string" NL \
    "            id=\"%s\"" NL \
    "            value=\"%s\"" NL \
    "            />" NL;

static const char STRING_TASKOPCODE_TEMPLATE[] = 
    "        <string" NL \
    "            id=\"%s.%s\"" NL \
    "            value=\"%s\"" NL \
    "            />" NL;

static const char MANIFEST_TAIL[] = 
    "      </stringTable>" NL\
    "    </resources>" NL\
    "  </localization>" NL\
    "</instrumentationManifest>" NL;

static const char *TypeMapManifest[] = { 
    "const char *",     "win:AnsiString",
    "const char*",      "win:AnsiString",
    "char",             "win:AnsiString",
    "char*",            "win:AnsiString",
    "const wchar_t *",  "win:UnicodeString",
    "const wchar_t*",   "win:UnicodeString",
    "wchar_t*",         "win:UnicodeString",
    "TChar",            "win:UnicodeString",
    "const TChar *",    "win:UnicodeString",
    "const TChar*",     "win:UnicodeString",
    "const MI_Char *",  "win:UnicodeString", 
    "const MI_Char*",   "win:UnicodeString", 
    "MI_Sint8",         "win:Int8", 
    "MI_Uint8",         "win:UInt8", 
    "MI_Sint16",        "win:Int16", 
    "MI_Uint16",        "win:UInt16", 
    "unsigned short",   "win:UInt16",
    "int",              "win:Int32", 
    "MI_Sint32",        "win:Int32",
    "MI_Uint32",        "win:UInt32", 
    "MI_Result",        "win:UInt32",
    "unsigned int",     "win:UInt32", 
    "MI_Sint64",        "win:Int64",
    "ptrdiff_t",        "win:Int64",
    "MI_Uint64",        "win:UInt64", 
    "float",            "win:Float",
    "double",           "win:Double",
    "MI_Boolean",       "win:Boolean",
    "void *",           "win:Pointer",
    "Strand *",         "win:Pointer",
    "Interaction *",    "win:Pointer",
    "Message *",        "win:Pointer",
    "StrandMany *",     "win:Pointer",
    "StrandEntry *",    "win:Pointer",
};

static char * ETWChannelIDs[] = {
    "Admin",        "c1",
    "Operational",  "c2",
    "Analytic",     "c3",
    "Debug",        "c4",
};

static char * gTransferEvent[] = {
    "EventTransfer",        /* name */
    "500",                  /* event id */
    "c2",                   /* channel */
    "win:Informational",    /* level */
};

static const char * _GetManifestType(_In_z_ const char * in)
{
    int i;
    int count = (int)(sizeof(TypeMapManifest)/sizeof(char *));

    for(i = 0; i + 1 < count; i += 2)
    {
        if (Strcmp(in, TypeMapManifest[i]) == 0)
        {
            return TypeMapManifest[i+1];
        }
    }

    OIERROR1("Unknown type for ETW manifest [%s]\n", in);
    return NULL;
}

static const char * _GetChannelID(_In_z_ const char * in)
{
    int i;
    int count = (int)(sizeof(ETWChannelIDs)/sizeof(char *));

    for(i = 0; i + 1 < count; i += 2)
    {
        if (Strcmp(in, ETWChannelIDs[i]) == 0)
        {
            return ETWChannelIDs[i+1];
        }
    }

    OIERROR1("Unknown channel type for ETW [%s]\n", in);
    return NULL;
}

static MI_Boolean _WriteTaskOpcodeKeywords(_In_ FILE * out, _In_ Buckets * etwInfo)
{
    SigBucket * e;

    /* Tasks */
    if (fprintf(out, MANIFEST_TASK_OPEN) == -1)
        goto error;
    e = etwInfo->tasks;
    while(e)
    {
        SigBucket * next = e->next;

        if (fprintf(out, MANIFEST_TASK_DEF, e->key, e->key, e->key, (USHORT) e->value) == -1)
            goto error;

        e = next;
    }
    if (fprintf(out, MANIFEST_TASK_CLOSE) == -1)
        goto error;

    /* Opcodes */
    if (fprintf(out, MANIFEST_OPCODE_OPEN) == -1)
        goto error;
    e = etwInfo->opcodes;
    while(e)
    {
        SigBucket * next = e->next;

        if (fprintf(out, MANIFEST_OPCODE_DEF, e->key, e->key, e->key, (UCHAR) e->value) == -1)
            goto error;

        e = next;
    }
    if (fprintf(out, MANIFEST_OPCODE_CLOSE) == -1)
        goto error;

    /* Keywords */
    if (fprintf(out, MANIFEST_KEYWORD_OPEN) == -1)
        goto error;
    e = etwInfo->keywords;
    while(e)
    {
        SigBucket * next = e->next;

        if (fprintf(out, MANIFEST_KEYWORD_DEF, (ULONGLONG) e->value, e->key, e->key) == -1)
            goto error;

        e = next;
    }
    if (fprintf(out, MANIFEST_KEYWORD_CLOSE) == -1)
        goto error;

    return MI_TRUE;

error:
    OIERROR("_WriteTaskOpcodeKeywords failed to write to file");
    return MI_FALSE;
}

static MI_Boolean _WriteChannels(_In_ FILE * out, _In_z_ const char * providerName)
{
    int i;
    int count = (int)(sizeof(ETWChannelIDs)/sizeof(char *));

    if (fprintf(out, MANIFEST_CHANNEL_TAG) == -1)
    {
        OIERROR("Failed to write to file\n");
        return MI_FALSE;
    }

    for(i = 0; i + 1 < count; i += 2)
    {
        if (fprintf(out, MANIFEST_CHANNEL, ETWChannelIDs[i+1], "true", providerName, ETWChannelIDs[i], ETWChannelIDs[i]) == -1)
        {
            OIERROR1("Failed to write to file, channel = [%s]\n", ETWChannelIDs[i]);
            return MI_FALSE;
        }
    }

    if (fprintf(out, MANIFEST_CHANNEL_CLOSE) == -1)
    {
        OIERROR("Failed to write to file\n");
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Boolean _WriteEvents(_In_ FILE * out, _In_ OIEvent * events)
{
    OIEvent * e = events;

    if (fprintf(out, MANIFEST_EVENTSTAG) == -1)
    {
        OIERROR("Failed to write to file\n");
        return MI_FALSE;
    }

    /* activity transfer event */
    if (fprintf(out, EVENT_START) == -1)
        goto error;
    if (fprintf(out, EVENT_CHANNEL, gTransferEvent[2]) == -1)
        goto error;
    if (fprintf(out, EVENT_LEVELMESSAGESYMBOL, gTransferEvent[3], gTransferEvent[0], gTransferEvent[0]) == -1)
        goto error;
    if (fprintf(out, EVENT_TEMPLATEVALUE, gTransferEvent[1], gTransferEvent[1]) == -1)
        goto error;

    /* rest of events */
    while(e)
    {
        OIEvent * next = e->next;

        if (fprintf(out, EVENT_START) == -1)
        {
            OIERROR2("Failed to write to file, eventid = [%s] format = [%s]\n", e->EventId, e->Format);
            return MI_FALSE;
        }

        if (e->Channel && Strlen(e->Channel) > 0)
        {
            const char * chid = _GetChannelID(e->Channel);
            if (!chid)
            {
                OIERROR1("Failed to find channel id for channel [%s]\n", e->Channel);
                return MI_FALSE;
            }

            if (fprintf(out, EVENT_CHANNEL, chid) == -1)
            {
                OIERROR2("Failed to write to file, eventid = [%s] format = [%s]\n", e->EventId, e->Format);
                return MI_FALSE;
            }
        }

        /* 
        Note, keyword attribute is not supported in the schema for <event> element.
        Instead, it gets passed during API call to ETW in the generated code.
        */

        if (e->Severity && Strlen(e->Severity) > 0)
        {
            if (fprintf(out, EVENT_LEVELMESSAGESYMBOL, e->Severity, e->Name, e->Name) == -1)
            {
                OIERROR2("Failed to write to file, eventid = [%s] format = [%s]\n", e->EventId, e->Format);
                return MI_FALSE;
            }
        }

        if (e->Task && Strlen(e->Task) > 0)
        {
            if (fprintf(out, EVENT_TASK, e->Task) == -1)
            {
                OIERROR2("Failed to write to file, eventid = [%s] format = [%s]\n", e->EventId, e->Format);
                return MI_FALSE;
            }
        }

        if (fprintf(out, EVENT_TEMPLATEVALUE, e->EventId, e->EventId) == -1)
        {
            OIERROR2("Failed to write to file, eventid = [%s] format = [%s]\n", e->EventId, e->Format);
            return MI_FALSE;
        }

        e = next;
    }

    return MI_TRUE;

error:
    OIERROR("Failed to write to file");
    return MI_FALSE;
}

static MI_Boolean _WriteTemplates(_In_ FILE * out, _In_ OIEvent * events)
{
    OIEvent * e = events;

    /* activity transfer event */
    if (fprintf(out, TEMPLATE_EMPTY, gTransferEvent[1]) == -1)
    {
        OIERROR("Failed to write to file");
        return MI_FALSE;
    }

    while(e)
    {
        OIEvent * next = e->next;
        OIArgument * arg = e->Argument;

        if (!arg)
        {
            if (fprintf(out, TEMPLATE_EMPTY, e->EventId) == -1)
            {
                OIERROR1("Failed to write to file %s\n", e->EventId);
                return MI_FALSE;
            }
        }
        else
        {
            if (fprintf(out, TEMPLATE_HEADER, e->EventId) == -1)
            {
                OIERROR1("Failed to write to file %s\n", e->EventId);
                return MI_FALSE;
            }

            while(arg)
            {
                OIArgument * next = arg->next;
                const char * manifestType = _GetManifestType(arg->Type);
                if (!manifestType)
                {
                    OIERROR1("Failed to convert to manifest type for type %s\n", arg->Type);
                    return MI_FALSE;
                }

                if (fprintf(out, DATA_TEMPLATE, manifestType, arg->Name) == -1)
                {
                    OIERROR1("Failed to write to file %s\n", e->EventId);
                    return MI_FALSE;
                }

                arg = next;
            }

            if (fprintf(out, TEMPLATE_TAIL) == -1)
            {
                OIERROR1("Failed to write to file %s\n", e->EventId);
                return MI_FALSE;
            }
        }

        e = next;
    }

    return MI_TRUE;
}

/*
Replaces %[{h | l | I | I32 | I64}]type with %N, where N is incremented for each argument, starting with 1
*/
static MI_Boolean _PrintfFormatToManifestFormat(_In_z_ const char * in, _Out_writes_z_(size) char * out, int size)
{
    int argCount = 1; /* manifest argument count starts at 1 */
    int copySize = 0;
    const char * original = in;

    /* 
        state 0 - normal reading 
        state 1 - found %, checking to see if another '%' follows, otherwise it's an argument

        note %% is not an argument insertion
    */
    int state = 0;

    *out = 0;

    while(*in && copySize < size - 1)
    {
        if (state == 0)
        {
            if (*in == '%')
            {
                state = 1;
            }

            /* copy char and move on */
            *out = *in;
            copySize++;
            in++;
            out++;
        }
        else
        {
            state = 0;

            /* we have just passed '%' */
            if(*in == '%')
            {
                /* We found '%%', just copy char and move on */
                *out = *in;                
            }   
            else
            {
                switch (*in)
                {
                case 'l':
                case 'h':
                    /* skip over one more char */
                    in++;
                    if (*in == 0)
                    {
                        OIERROR1("Unexpected end of string while parsing format [%s]!\n", original);
                        return MI_FALSE;
                    }
                    break;
                case 'I':
                    /* I or I32 or I64 are possible here */
                    in++; /* skip over I */
                    if (*in == 0)
                    {
                        OIERROR1("Unexpected end of string while parsing format [%s]!\n", original);
                        return MI_FALSE;
                    }
                    if (*in == '3' || *in == '6')
                    {
                        /* skip over 32 or 64 */
                        in++;
                        if (*in == 0)
                        {
                            OIERROR1("Unexpected end of string while parsing format [%s]!\n", original);
                            return MI_FALSE;
                        }
                        in++;
                        if (*in == 0)
                        {
                            OIERROR1("Unexpected end of string while parsing format [%s]!\n", original);
                            return MI_FALSE;
                        }
                    }
                    break;
                default:
                    break;
                }

                /* insert arg number */
                *out = '0' + argCount;
                argCount++;
            }
            
            copySize++;
            in++;
            out++;
        }
    }

    *out = 0;

    if (copySize >= size - 1)
    {
        OIERROR("_PrintfFormatToManifestFormat internal error!\n");
        return MI_FALSE;
    }
    else
        return MI_TRUE;
}

static MI_Boolean _WriteStrings(_In_ FILE * out, _In_ OIEvent * events, _In_z_ const char * providerName, _In_ Buckets * etwInfo)
{
    SigBucket * i;
    OIEvent * e = events;

    if (fprintf(out, STRING_TEMPLATE_QUOTES, "Provider.Name", providerName) == -1)
    {
        OIERROR1("Failed to write to file while [%s]\n", providerName);
        return MI_FALSE;
    }

    /* Tasks */
    i = etwInfo->tasks;
    while(i)
    {
        SigBucket * next = i->next;
        if (fprintf(out, STRING_TASKOPCODE_TEMPLATE, "Task", i->key, i->key) == -1)
            goto error;
        i = next;
    }

    /* Opcodes */
    i = etwInfo->opcodes;
    while(i)
    {
        SigBucket * next = i->next;
        if (fprintf(out, STRING_TASKOPCODE_TEMPLATE, "Opcode", i->key, i->key) == -1)
            goto error;
        i = next;
    }

    /* activity transfer event */
    if (fprintf(out, STRING_TEMPLATE_QUOTES, gTransferEvent[0], gTransferEvent[0]) == -1)
        goto error;

    /* Event format strings */
    while(e)
    {
        OIEvent * next = e->next;
        char buf[BUFFER_SIZE];
        buf[0] = 0;

        if (!_PrintfFormatToManifestFormat(e->Format, buf, BUFFER_SIZE))
        {
            OIERROR1("_PrintfFormatToManifestFormat failed for event [%s]\n", e->EventId);
            return MI_FALSE;
        }

        if (fprintf(out, STRING_TEMPLATE, e->Name, buf) == -1)
            goto error;

        e = next;
    }

    return MI_TRUE;
error:
    OIERROR("_WriteStrings failed to write to file");
    return MI_FALSE;
}

/********* PUBLIC DEFINITIONS ***************************************/

_Use_decl_annotations_
MI_Boolean GenerateManifest(
    OIEvent * events,
    Buckets * etwInfo,
    char * providerName,
    char * providerId,
    char * binary,
    char * target)
{
    /* overwrite existing file */
    char buf[BUFFER_SIZE];
    FILE* out = fopen(target, "w");
    if (!out)
    {
        OIERROR1("Failed to open file [%s]\n", target);
        return MI_FALSE;
    }

    if (fprintf(out, MANIFEST_HEADER) == -1)
        goto error;

    if (fprintf(out, MANIFEST_PROVIDERDECL, providerId, binary, providerName, binary, binary, providerName) == -1)
        goto error;

    if (!_WriteChannels(out, providerName))
        goto error;

    if (!_WriteTaskOpcodeKeywords(out, etwInfo))
        goto error;

    if (!_WriteEvents(out, events))
        goto error;

    if (fprintf(out, TEMPLATES_HEADER) == -1)
        goto error;

    if (!_WriteTemplates(out, events))
        goto error;

    if (fprintf(out, STRINGTABLE_HEADER) == -1)
        goto error;

    if (!_WriteStrings(out, events, providerName, etwInfo))
        goto error;

    if (fprintf(out, MANIFEST_TAIL) == -1)
        goto error;

    fclose(out);
    return MI_TRUE;

error:
    OIERROR("GenerateManifest failed!\n");
    fclose(out);
    return MI_FALSE;
}
