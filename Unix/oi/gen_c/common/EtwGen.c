/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "EtwGen.h"
#include "oicommon.h"
#include <pal/strings.h>
#include "ManifestGen.h"

static const char *FILEHEADER = 
    NL \
    "#define ETW_PROVIDER_GUID(l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \\" NL \
    "    { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }" NL;

static const char *ETWGUIDTEMPLATE = "#define ETWGUIDVALUE ETW_PROVIDER_GUID(%s);" NL;

/*
The map is required for etw header implementation.
*/
static const char *TypeMapEtw[] = { 
    "const char *",     "LPCSTR",
    "const char*",      "LPCSTR",
    "char",             "LPCSTR",
    "char*",            "LPCSTR",
    "const wchar_t *",  "LPCWSTR",
    "const wchar_t*",   "LPCWSTR",
    "wchar_t*",         "LPCWSTR",
    "TChar",            "LPCWSTR",
    "const TChar *",    "LPCWSTR",
    "const TChar*",     "LPCWSTR",
    "const MI_Char *",  "LPCWSTR", 
    "const MI_Char*",   "LPCWSTR", 
    "MI_Sint8",         "MI_Sint8", 
    "MI_Uint8",         "MI_Uint8", 
    "MI_Sint16",        "MI_Sint16", 
    "MI_Uint16",        "MI_Uint16", 
    "unsigned short",   "MI_Uint16",
    "int",              "MI_Sint32", 
    "MI_Sint32",        "MI_Sint32",
    "MI_Uint32",        "MI_Uint32", 
    "MI_Result",        "MI_Uint32",
    "unsigned int",     "MI_Uint32", 
    "MI_Sint64",        "MI_Sint64",
    "ptrdiff_t",        "MI_Sint64",
    "MI_Uint64",        "MI_Uint64", 
    "float",            "float",
    "double",           "double",
    "MI_Boolean",       "MI_Boolean",
    "void *",           "PVOID",
    "Strand *",         "PVOID",
    "Interaction *",    "PVOID",
    "Message *",        "PVOID",
    "StrandMany *",     "PVOID",
    "StrandEntry *",    "PVOID",
};

static const char *TypeToGen[] = {
    "MI_Sint8",
    "MI_Uint8",
    "MI_Sint16",
    "MI_Uint16",
    "MI_Sint32",
    "MI_Uint32",
    "MI_Sint64",
    "MI_Uint64",
    "float",
    "double",
    "PVOID",
    "MI_Boolean",
    "DWORD",
    "HRESULT",
    "size_t",
    "BOOL",
    "TChar",
};

static MI_Boolean _AddTypeMacros(_In_ FILE * out)
{
    int i;
    int count = (int)(sizeof(TypeToGen)/sizeof(char *));

    fprintf(out, NL);
    for(i = 0; i < count; i++)
    {
        if (fprintf(out, "ETW_CREATEDESC_TYPE(%s)\n", TypeToGen[i]) == -1)
        {
            OIERROR("Failed to write to file, _AddSignatures");
            return MI_FALSE;
        }
    }
    fprintf(out, NL);

    return MI_TRUE;
}

/*
Sanity check that to make sure we can understand this type.
*/
static const char * _GetEtwType(_In_z_ const char * in)
{
    int i;
    int count = (int)(sizeof(TypeMapEtw)/sizeof(char *));

    for(i = 0; i + 1 < count; i += 2)
    {
        if (Strcmp(in, TypeMapEtw[i]) == 0)
        {
            return TypeMapEtw[i+1];
        }
    }

    OIERROR1("Unknown type for ETW generator [%s]\n", in);
    return NULL;
}

/*
    Returns MI_TRUE if an element exist in the linked list with key=key
*/
static MI_Boolean _FindBucket(_In_ SigBucket * self, _In_z_ char * key)
{
    SigBucket * s = self;

    if (!self)
        return MI_FALSE;

    while(s)
    {
        SigBucket * next = s->next;

        if (Strcmp(s->key, key) == 0)
            return MI_TRUE;

        s = next;
    }

    return MI_FALSE;
}

/* 
    Appends to the end of the list.
    Note: it walks to the end every time, so it could improved if needed.
*/
static MI_Boolean _AppendBucket(_Inout_ SigBucket ** self, _In_z_ char * key)
{
    SigBucket * newSig = (SigBucket *) PAL_Calloc(1, sizeof(SigBucket));
    if (!newSig)
        return MI_FALSE;

    newSig->key = PAL_Strdup(key);
    if (!newSig->key)
    {
        PAL_Free(newSig);
        return MI_FALSE;
    }

    if (!*self)
    {
        *self = newSig;
        return MI_TRUE;
    }
    else
    {
        SigBucket * marker = *self;
        while(marker && marker->next)
        {
            marker = marker->next;
        }

        marker->next = newSig;
        newSig->next = 0;
        
        return MI_TRUE;
    }
}

/* Releases the linked list and its contents */
static void _ReleaseList(_In_ SigBucket * self)
{
    SigBucket * s = self;
    while(s)
    {
        SigBucket * next = s->next;

        PAL_Free(s->key);
        PAL_Free(s);

        s = next;
    }
}

/* 
    Formats GUID into ETW macro style
*/
static MI_Boolean _ToGuidDef(_In_z_ char * guid, _Out_writes_z_(size) char * out, int size)
{
    char * next_token = 0;
    char * token = 0;
    char tmp[BUFFER_SIZE];
    int i;
    char seps[] = "{-}";
    char guidTmp[OI_MAX_LENGTH];

    *out = 0;

    if (Strlcpy(guidTmp, guid, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        return MI_FALSE;

    token = Strtok(guidTmp, seps, &next_token);

    for (i = 0; i < 3; i++)
    {
        if (!token)
            return MI_FALSE;
        if (Strcat(out, size, "0x") == 0)
            return MI_FALSE;
        if (Strcat(out, size, token) == 0)
            return MI_FALSE;
        if (Strcat(out, size, ", ") == 0)
            return MI_FALSE;
        token = Strtok(NULL, seps, &next_token);
    }

    if (Strlen(token) != 4)
        return MI_FALSE;

    sprintf(tmp, 
            "0x%c%c, 0x%c%c, ", *token, *(token+1), *(token+2), *(token+3));
    if (Strcat(out, size, tmp) == 0)
        return MI_FALSE;

    token = Strtok(NULL, seps, &next_token);
    if (Strlen(token) != 12)
        return MI_FALSE;

    sprintf(tmp,
        "0x%c%c, 0x%c%c, 0x%c%c, 0x%c%c, 0x%c%c, 0x%c%c", 
        *token, *(token+1),
        *(token+2), *(token+3),
        *(token+4), *(token+5),
        *(token+6), *(token+7),
        *(token+8), *(token+9),
        *(token+10), *(token+11));

    if (Strcat(out, size, tmp) == 0)
        return MI_FALSE;

    return MI_TRUE;
}

static char * _ChannelToUCHAR[] = {
    "Admin",        /* 1 */
    "Operational",  /* 2 */
    "Analytic",     /* 3 */
    "Debug",        /* 4 */
};

static MI_Boolean _GetChannelID(_In_z_ const char * in, UCHAR * out)
{
    int i;
    int count = (int)(sizeof(_ChannelToUCHAR)/sizeof(char *));

    for(i = 0; i < count; i++)
    {
        if (Strcmp(in, _ChannelToUCHAR[i]) == 0)
        {
            *out = i+1;
            return MI_TRUE;
        }
    }

    OIERROR1("_GetChannelID: Unknown channel for ETW manifest [%s]", in);
    return MI_FALSE;
}

static char * _SeverityToUCHAR[] = {
    /* 1 */ "win:Critical",
    /* 2 */ "win:Error",
    /* 3 */ "win:Warning",
    /* 4 */ "win:Informational",
    /* 5 */ "win:Verbose",
};

static MI_Boolean _GetSeverityID(_In_z_ const char * in, UCHAR * out)
{
    int i;
    int count = (int)(sizeof(_SeverityToUCHAR)/sizeof(char *));

    for(i = 0; i < count; i++)
    {
        if (Strcmp(in, _SeverityToUCHAR[i]) == 0)
        {
            *out = i+1;
            return MI_TRUE;
        }
    }

    OIERROR1("_GetSeverityID: Unknown severity level for ETW manifest [%s]", in);
    return MI_FALSE;
}

static MI_Boolean _GetValueForKey(_In_z_ const char * in, _Out_ ULONGLONG * out, _In_ SigBucket * set)
{
    SigBucket * marker = set;

    /*
    Special case: for an empty string or non at all, assume zero for ETW api
    */
    if (!in || Strlen(in) == 0)
    {
        *out = 0;
        return MI_TRUE;
    }

    while(marker)
    {
        SigBucket * next = marker->next;
        if (Strcmp(in, marker->key) == 0)
        {
            *out = marker->value;
            return MI_TRUE;
        }
        marker = next;
    }

    OIERROR1("_GetValueForKey couldn't find key (opcode, keyword, or task)! [%s]", in);
    return MI_FALSE;
}

/* 
    Write ETW event macros to the file
*/
static MI_Boolean _AddEvents(_In_ FILE * out, _In_ OIEvent * events, _In_ Buckets * set)
{
    char buf[BUFFER_SIZE];
    OIEvent * current = events;

    while(current)
    {
        OIEvent * next = current->next;
        OIArgument * arg = current->Argument;
        int ArgCount = CountArguments(arg);
        int wrote;
        UCHAR channel, level, opcode;
        USHORT task;
        ULONGLONG keyword, tmp;

        buf[0] = 0;
        if (!_GetChannelID(current->Channel, &channel))
        {
            OIERROR1("_GetChannelID Unknown channel %s", current->Channel);
            goto error;
        }
        if (!_GetSeverityID(current->Severity, &level))
        {
            OIERROR1("_GetSeverityID Unknown level %s", current->Severity);
            goto error;
        }

        if (!_GetValueForKey(current->Opcode, (ULONGLONG*) &tmp, set->opcodes))
        {
            OIERROR1("_GetOpCodeID Unknown opcode %s", current->Opcode);
            goto error;
        }
        else
        {
            opcode = (UCHAR) tmp;
        }
        if (!_GetValueForKey(current->Task, (ULONGLONG*) &tmp, set->tasks))
        {
            OIERROR1("_GetTaskID Unknown task %s", current->Task);
            goto error;
        }
        else
        {
            task = (USHORT) tmp;
        }
        if (!_GetValueForKey(current->Keyword, &keyword, set->keywords))
        {
            OIERROR1("_GetKeywordID Unknown keyword %s", current->Keyword);
            goto error;
        }

        wrote = sprintf_s(buf, BUFFER_SIZE, "ETW_EVENT%d(%s, %s, %d, %d, %d, %d, %I64u",
            ArgCount, current->EventId, current->Name, channel, level, opcode, task, keyword);
        if (wrote >= BUFFER_SIZE)
            goto error;

        /* add original types */
        while(arg)
        {
            if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
                goto error;
            if (Strcat(buf, BUFFER_SIZE, arg->Type) == 0)
                goto error;

            arg = arg->next;
        }

        /* add converted types */
        arg = current->Argument;
        while(arg)
        {
            OIArgument * next = arg->next;
            const char * etwType = _GetEtwType(arg->Type);
                                
            if (!etwType)
            {
                OIERROR1("Unknown type for etw [%s], contact support!", arg->Type);
                goto error;
            }

            if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
                goto error;
            if (Strcat(buf, BUFFER_SIZE, etwType) == 0)
                goto error;

            arg = next;
        }
        
        if (Strcat(buf, BUFFER_SIZE, ");") == 0)
            goto error;

        fprintf(out, buf);
        fprintf(out, NL);

        current = next;
    }

    return MI_TRUE;

error:
    OIERROR("_AddEvents failed");
    return MI_FALSE;
}

/* 
    _AddSignatures

    Adds signatures for the trace events, such as:
    ETW_EVENTSIG_IMPL1(int)
    ETW_EVENTSIG_IMPL2(int, char*)
    ETW_EVENTSIG_IMPL1(char*)
    etc.
*/
static MI_Boolean _AddSignatures(_In_ FILE * out, _In_ OIEvent * events)
{
    OIEvent * current = events;
    SigBucket * signatures = 0;

    while(current)
    {
        char buf[BUFFER_SIZE];
        OIEvent * next = current->next;
        int ArgCount = CountArguments(current->Argument);

        char atoibuf[12];
        size_t size;
        const char* str = Uint32ToStr(atoibuf, (MI_Uint32)ArgCount, &size);
        if (!str)
            goto error;

        buf[0] = 0;

        if (Strcat(buf, BUFFER_SIZE, "ETW_EVENTSIG_IMPL") == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, str) == 0)
            goto error;
        if (Strcat(buf, BUFFER_SIZE, "(") == 0)
            goto error;

        {
            OIArgument * arg = current->Argument;

            /* building "TYPE1, TYPE2, TYPE3, ..." */
            while(arg)
            {
                OIArgument * next = arg->next;
                const char * etwType = _GetEtwType(arg->Type);
                                
                if (!etwType)
                {
                    OIERROR1("Unknown type for etw [%s], contact support", arg->Type);
                    goto error;
                }

                if (Strcat(buf, BUFFER_SIZE, etwType) == 0)
                    goto error;
                if (next)
                    if (Strcat(buf, BUFFER_SIZE, ", ") == 0)
                        goto error;
                arg = next;
            }
        }

        if (Strcat(buf, BUFFER_SIZE, ")") == 0)
            goto error;

        /* add the signature to the list if new */
        if (!_FindBucket(signatures, buf))
        {
            if (!_AppendBucket(&signatures, buf))
                goto error;
        }

        current = next;
    }

    /* write unique signatures to the file */
    {
        SigBucket * s = signatures;
        while(s)
        {
            SigBucket * next = s->next;

            fprintf(out, s->key);
            fprintf(out, NL);

            s = next;
        }
    }

    _ReleaseList(signatures);
    return MI_TRUE;

error:
    _ReleaseList(signatures);
    return MI_FALSE;    
}

/********* PUBLIC DEFINITIONS ***************************************/

_Use_decl_annotations_
MI_Boolean GenerateEtw(
    OIEvent * events,
    Buckets * set,
    char * providerId,
    char * target)
{
    /* overwrite existing file */
    char buf[BUFFER_SIZE];
    MI_Boolean result = MI_FALSE;
    FILE* out = fopen(target, "w");
    
    if (!out)
    {
        OIERROR1("Failed to open file, %s\n", target);
        return MI_FALSE;
    }

    fprintf(out, FILEHEADER);
    fprintf(out, NL);

    if (!_ToGuidDef(providerId, buf, BUFFER_SIZE))
    {
        OIERROR1("_ToGuidDef failed, %s\n", providerId);
        goto cleanup;
    }
    fprintf(out, ETWGUIDTEMPLATE, buf);
    fprintf(out, NL);

    fprintf(out, "\n#include \"oi/oi_etw.h\"\n");
    fprintf(out, NL);

    if (!_AddTypeMacros(out))
    {
        OIERROR1("_AddTypeMacros failed, %s\n", target);
        goto cleanup;
    }

    if (!_AddSignatures(out, events))
    {
        OIERROR1("_AddSignatures failed, %s\n", target);
        goto cleanup;
    }

    if (!_AddEvents(out, events, set))
    {
        OIERROR1("_AddEvents failed, %s\n", target);
        goto cleanup;
    }

    result = MI_TRUE;

cleanup:
    fclose(out);

    return result;
}

_Use_decl_annotations_
void CleanupBuckets(Buckets * set)
{
    _ReleaseList(set->tasks);
    _ReleaseList(set->opcodes);
    _ReleaseList(set->keywords);
}

/*
1) Collects all unique tasks, opcodes, keywords in the order that they are defined.
2) Assigns ETW value to them that is used in manifest and code generate for ETW logging.

Tasks value can be [1, 228]
Opcodes values can be [11, 239]
Keywords are bitmasks
See http://msdn.microsoft.com/en-us/library/windows/desktop/dd996918(v=vs.85).aspx
[Note! Tasks must start at 1 despite what MSDN states!]
*/
_Use_decl_annotations_
MI_Boolean GenerateTaskOpcodeKeywords(OIEvent * events, Buckets * set)
{
    OIEvent * e = events;
    memset(set, 0, sizeof(Buckets));

    while(e)
    {
        OIEvent * next = e->next;

        /* add the signature to the list if new */
        if (Strlen(e->Task) > 0 && !_FindBucket(set->tasks, e->Task))
        {
            if (!_AppendBucket(&set->tasks, e->Task))
                goto error;
        }
        if (Strlen(e->Opcode) > 0 && !_FindBucket(set->opcodes, e->Opcode))
        {
            if (!_AppendBucket(&set->opcodes, e->Opcode))
                goto error;
        }
        if (Strlen(e->Keyword) > 0 && !_FindBucket(set->keywords, e->Keyword))
        {
            if (!_AppendBucket(&set->keywords, e->Keyword))
                goto error;
        }

        e = next;
    }

    /* tasks */
    {
        SigBucket * bucket = set->tasks;
        USHORT assignValue = 1;
        while(bucket)
        {
            SigBucket * next = bucket->next;
            bucket->value = assignValue++;
            if (assignValue > 228)
            {
                OIERROR("GenerateTaskOpcodeKeywords failed, ETW doesn't support more than 228 tasks!");
                return MI_FALSE;
            }
            bucket = next;
        }
    }

    /* opcodes */
    {
        SigBucket * bucket = set->opcodes;
        UCHAR assignValue = 11;
        while(bucket)
        {
            SigBucket * next = bucket->next;
            bucket->value = assignValue++;
            if (assignValue > 239)
            {
                OIERROR("GenerateTaskOpcodeKeywords failed, ETW doesn't support more than 228 opcodes!");
                return MI_FALSE;
            }
            bucket = next;
        }
    }

    /* keywords */
    {
        SigBucket * bucket = set->keywords;
        ULONGLONG assignValue = 1;
        while(bucket)
        {
            SigBucket * next = bucket->next;            
            bucket->value = assignValue;
            if (assignValue >= MAXLONGLONG)
            {
                OIERROR("GenerateTaskOpcodeKeywords failed, ETW keywords bitmask value overflowed!");
                return MI_FALSE;
            }
            assignValue *= 2;
            bucket = next;
        }
    }

    return MI_TRUE;

error:
    OIERROR("_TaskOpcodeKeyword failed!");
    return MI_FALSE;
}
