/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "oicommon.h"
#include "OIParser.h"
#include <pal/strings.h>

/* Reserved by ETW code generate for Event Transfer event */
long gReservedID = 500;

typedef struct _OIDefaults
{
    /* Common properties */
    unsigned long NextID;

    /* Syslog */
    char Priority[OI_MAX_LENGTH];    

    /* ETW section */
    char Channel  [OI_MAX_LENGTH];
    char Keyword  [OI_MAX_LENGTH];
    char Opcode   [OI_MAX_LENGTH];
    char Severity [OI_MAX_LENGTH];
    char Task     [OI_MAX_LENGTH];  
}
OIDefaults;

static char * Priorities[] = {
    "LOG_EMERG",
    "LOG_ALERT",
    "LOG_CRIT",
    "LOG_ERR",
    "LOG_WARNING",
    "LOG_NOTICE",
    "LOG_INFO",
    "LOG_DEBUG",
    "LOG_VERBOSE",
};

static char * ETWChannels[] = {
    "Admin",
    "Operational",
    "Analytic",
    "Debug",
};

static char * _ETWLevels[] = {
    "LOG_EMERG",    "win:Critical",
    "LOG_ALERT",    "win:Critical",
    "LOG_CRIT",     "win:Critical",
    "LOG_ERR",      "win:Error",
    "LOG_WARNING",  "win:Warning",
    "LOG_NOTICE",   "win:Informational",
    "LOG_INFO",     "win:Informational",
    "LOG_DEBUG",    "win:Verbose",
    "LOG_VERBOSE",  "win:Verbose",
};

const char * _GetEtwLevel(_In_z_ const char * in)
{
    int i;
    int count = (int)(sizeof(_ETWLevels)/sizeof(char *));

    for(i = 0; i + 1 < count; i += 2)
    {
        if (Strcmp(in, _ETWLevels[i]) == 0)
        {
            return _ETWLevels[i+1];
        }
    }

    OIERROR1("_GetEtwLevel: Unknown severity level for ETW manifest [%s]\n", in);
    return NULL;
}

/*
Returns true if matches one of syslog priority constants
*/
static MI_Boolean _CheckSyslogPriority(_In_z_ char * priority)
{
    int i = 0;

    for(i = 0; i < (MI_Uint32)(sizeof(Priorities)/sizeof(char*)); ++i)
    {
        if (Strcmp(Priorities[i], priority) == 0)
            return MI_TRUE;
    }

    OIERROR1("Unknown syslog priority level found, %s", priority);
    return MI_FALSE;
}

/*
Returns true if channel is a proper ETW channel
*/
static MI_Boolean _CheckChannel(_In_z_ const char * channel)
{
    int i = 0;

    for(i = 0; i < (MI_Uint32)(sizeof(ETWChannels)/sizeof(char*)); ++i)
    {
        if (Strcmp(ETWChannels[i], channel) == 0)
            return MI_TRUE;
    }

    OIERROR1("Unknown ETW channel [%s]: Admin or Operational or Analytic or Debug", channel);
    return MI_FALSE;
}

/* 
    Trims off whitespace from both start and end of a string
    Modifies string in-place
*/
static char * _Trim(_In_z_ char * line)
{
    char * start;
    char * end;

    /* trim from the beginning */
    while( *line && (*line == ' ' || *line == '\t') )
        line++;

    start = line;

    /* find the end but not the null-end */
    end = line;
    while( *end && *(end+1) != 0 )
    {
        end++;
    }

    /* trim from the end */
    while( end > start )
    {
        if ( *end == ' ' || *end == '\t' )
        {
            *end = 0;
            end--;
        }
        else
            break;
    }

    return line;
}

/* 
    Return zero if 'line' does not start with 'str'.
    Non-zero otherwise.
*/
static int _StartsWith(_In_z_ char * line, _In_z_ char * str)
{
    if (!*line || !*str)
        return 0;

    while(*line == *str)
    {
        line++;
        str++;

        if (*line == 0)
            return 0;

        if (*str == 0)
            return 1;
    }

    return 0;
}

/* Strip away parentheses ( ); modifies string in-place */
static char * _GetArgsAsString(_In_z_ char * line)
{
    char * pos;

    line = strchr(line, '(');
    if (!line)
        return 0;

    line++;
    if (!*line)
        return 0;

    pos = strrchr(line, ')');
    if (!pos)
        return 0;

    *pos = '\0';

    return line;
}

static OIEvent * _Event_Create(_In_z_ const char * eventId, _In_z_ const char * format, _In_ OIDefaults * defaults)
{
    OIEvent * e = 0;

    e = (OIEvent *) PAL_Calloc(1, sizeof(OIEvent));
    if (!e)
        goto error;

    if (Strlcpy(e->EventId, eventId, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;
    if (Strlcpy(e->Format, format, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;

    if (Strlcpy(e->Priority, defaults->Priority, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;

    if (Strlcpy(e->Channel, defaults->Channel, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;
    if (Strlcpy(e->Keyword, defaults->Keyword, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;
    if (Strlcpy(e->Opcode, defaults->Opcode, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;
    if (Strlen(defaults->Severity) > 0)
    {
        if (Strlcpy(e->Severity, defaults->Severity, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
            goto error;
    }
    else
    {
        const char * level = _GetEtwLevel(defaults->Priority);
        if (!level)
        {
            OIERROR1("Unknown ETW level when converting general Priority level [%s]", defaults->Priority);
            goto error;
        }
        
        if (Strlcpy(e->Severity, level, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
            goto error;
    }
    if (Strlcpy(e->Task, defaults->Task, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;

    return e;

error:
    OIERROR("Out of memory while creating OIEvent object");
    if (e)
        PAL_Free(e);
    return 0;
}

/* Insert new event at the end of the linked list. */
static void _Parser_AddEvent(_In_ OIParser * parser, _In_ OIEvent * e)
{
    if (!parser->head)
    {
        parser->head = e;
        e->next = 0;
        parser->end = e;
    }
    else
    {
        parser->end->next = e;
        e->next = 0;
        parser->end = e;
    }
}

/* Modifies the string from [_x1_ _x2_ ... type] to [type] */
static char * _RemoveAnnotations(_In_z_ char * type)
{
    if (!type || !*type)
    {
        OIERROR("_RemoveAnnotations received an empty type");
        return 0;
    }

    while (*type && *type == '_')
    {
        /* move to next white-space, there may be multiple annotations [_x1_ _x2_ type] */
        while (*type)
        {
            if(*type!=' ' && *type!='\t')
                type++;
            else
                break;
        }

        /* now we should have at least have [type] or another annotation before <type> */
        if (!*type)
        {
            OIERROR1("_RemoveAnnotations found a wrong type [%s]", type);
            return 0;
        }
    }

    type = _Trim(type);
    return type;
}

/* buf should be of a format "(type1 name1, type2 name2, ...)" */
static MI_Boolean _ParseArgs(_In_ OIEvent * e, _In_z_ char * buf)
{
    char * next_token = 0;
    char * line = _GetArgsAsString(buf);
    char * token = Strtok(line, ",", &next_token);

    OIArgument * prev = 0;
    OIArgument * current = 0;

    while(token) /* type and name together */
    {
        char * varName = 0;

        token = _Trim(token);

        /* start new argument */
        current = (OIArgument *) PAL_Calloc(1, sizeof(OIArgument));
        if (!current)
        {
            OIERROR("Out of memory while creating OIArgument object");
            goto error;
        }

        varName = Strrchr(token, ' ');

        if (Strlcpy(current->Name, _Trim(varName), OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR("Out of memory while copying a string");
            goto error;
        }

        *varName = '\0';
        if (!(token = _RemoveAnnotations(_Trim(token))))
        {
            OIERROR("_RemoveAnnotations failed");
            goto error;
        }

        if (Strlcpy(current->Type, token, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR("_RemoveAnnotations failed");
            goto error;
        }

        /* add the argument to the list */
        if (prev)
        {
            prev->next = current;
            current->next = 0;
                
            prev = current;
        }
        else
        {
            /* this is the first argument */
            e->Argument = current;

            current->next = 0;                
            prev = current;
        }

        token = Strtok(NULL, ",", &next_token);
    }

    return MI_TRUE;

error:
    if (current)
        PAL_Free(current);
    return MI_FALSE;
}

static void _Event_Destroy(_In_ OIEvent * e)
{
    if (!e) return;

    if (e->Argument)
    {
        OIArgument * curr = e->Argument;
        while( curr )
        {
            OIArgument * next = curr->next;
            PAL_Free(curr);

            curr = next;
        }
    }

    PAL_Free(e);
}

/*
_ParseOIDefault

    Parses OI_SETDEFAULT(SETTING(VALUE)) and saves it to the defaults object

    line     - trimmed line
    defaults - the object with defaults for OI_EVENT's
*/
static MI_Boolean _ParseOIDefault(_In_z_ char * line, _In_ OIDefaults * defaults)
{
    char * next_token = 0;
    char *ignore, *setting, *value;

    /*
    First token is OI_SETDEFAULT
    Second is <SETTING>
    Third is <VALUE>
    */

    ignore = Strtok(line, "()", &next_token);    
    if(!ignore)
    {
        OIERROR1("Expected OI_SETDEFAULT(X(Y)) but found no parentheses characters at all! %s", line);
        return MI_FALSE;
    }

    setting = Strtok(NULL, "()", &next_token);
    if(!setting)
    {
        OIERROR1("Expected OI_SETDEFAULT(X(Y)) but found no setting X inside! %s", line);
        return MI_FALSE;
    }

    value = Strtok(NULL, "()", &next_token);
    if(!value)
    {
        OIERROR1("Expected OI_SETDEFAULT(X(Y)) but found no value Y inside! %s", line);
        return MI_FALSE;
    }

    /*
    List of currently supported values:

    PRIORITY (used by Syslog only)
    STARTID
    CHANNEL (ETW)
    KEYWORD (ETW)
    LEVEL   (ETW)
    OPCODE  (ETW)
    TASK    (ETW)
    */

    if (Strcasecmp(setting, "PRIORITY") == 0)
    {
        if (_CheckSyslogPriority(value) == MI_FALSE)
        {
            OIERROR1("Expected a Syslog priority here! %s", value);
            return MI_FALSE;
        }

        if (Strlcpy(defaults->Priority, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else if (Strcasecmp(setting, "STARTID") == 0)
    {
        long eventID = atol(value);
        if (eventID == gReservedID)
            eventID++;
        defaults->NextID = eventID;
    }
    else if (Strcasecmp(setting, "CHANNEL") == 0)
    {
        if (_CheckChannel(value) == MI_FALSE)
        {
            OIERROR1("Expected a proper ETW channel here! %s", value);
            return MI_FALSE;
        }

        if (Strlcpy(defaults->Channel, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else if (Strcasecmp(setting, "KEYWORD") == 0)
    {
        if (Strlcpy(defaults->Keyword, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else if (Strcasecmp(setting, "OPCODE") == 0)
    {
        if (Strlcpy(defaults->Opcode, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else if (Strcasecmp(setting, "TASK") == 0)
    {
        if (Strlcpy(defaults->Task, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else if (Strcasecmp(setting, "LEVEL") == 0)
    {
        if (Strlcpy(defaults->Severity, value, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        {
            OIERROR1("Out of memory while copying string! %s", value);
            return MI_FALSE;
        }
    }
    else
    {
        OIERROR1("Unknown OI_SETDEFAULT(X(Y)) value X = [%s]", setting);
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Boolean _SetOIDefaults(_In_ OIDefaults * defaults)
{
    defaults->NextID = 1;
    if (Strlcpy(defaults->Priority, "LOG_DEBUG", OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;
    if (Strlcpy(defaults->Channel, "Debug", OI_MAX_LENGTH) >= OI_MAX_LENGTH)
        goto error;

    defaults->Keyword[0] = 0;
    defaults->Opcode[0] = 0;
    defaults->Task[0] = 0;

    return MI_TRUE;

error:
    OIERROR("_SetOIDefaults out of memory!");
    return MI_FALSE;
}

static long _GetNextID(_In_ OIDefaults * defaults)
{
    /* skip over reserved value */
    if (defaults->NextID == gReservedID)
        defaults->NextID++;

    return defaults->NextID++;
}

/* Parsing SET_OIDEFAULT(X(Y)) */
static MI_Boolean _ParseOI_SetDefault(_In_z_ char * line, _In_ OIDefaults * defaults)
{
    if (_ParseOIDefault(line, defaults))
        return MI_TRUE;
    else
    {
        OIERROR1("Failed to parse OI_SETDEFAULT! %s", line);
        return MI_FALSE;
    }
}

/*
    OI_EVENT("format")
*/
static MI_Boolean _ParseOIEvent(_In_z_ char * line, _In_ OIDefaults * defaults, _Out_ OIEvent ** newEvent)
{
    char tmp[OI_MAX_LENGTH];
    char * format;
    char * eventId;

    *newEvent = 0;

    line = _GetArgsAsString(line);
    if (!line)
    {
        OIERROR("OI_EVENT had no content!");
        return MI_FALSE;
    }

    {   
        /* 
        This case is OI_EVENT(format) with automatic ID generation, so
        the first item is not event id but format.
        */
        long autoId = _GetNextID(defaults);
        size_t size;
        const char * out = Uint32ToStr(tmp, autoId, &size);
        if (!out)
        {
            OIERROR2("Failed to create an automatic ID from [%ld] for line [%s]! ", autoId, line);
            return MI_FALSE;
        }
            
        format = _Trim(line);
        eventId = (char *) out;
    }

    if ((*newEvent = _Event_Create(eventId, format, defaults)) == NULL)
    {
        OIERROR1("Failed creating an OIEvent object for line [%s]! ", line);
        goto error;
    }

    return MI_TRUE;

error:
    OIERROR("Failed while parsing a C header!");
    if (*newEvent)
        _Event_Destroy(*newEvent);
    return MI_FALSE;
}

/* 
    Next line should be function declaration of the trace, such as:
        void funcdecl(type1 name 1, ...);
*/
static MI_Boolean _ParseFunctionDecl(_In_z_ char * line, _In_ OIDefaults * defaults, _In_ OIEvent * newEvent)
{   
    char * line2;
    char * pos;
    size_t nameLength;

    /* void func(...) */
    line2 = _Trim(line);
    if (_StartsWith(line2, "void") == 0)
    {
        OIERROR1("Trace declaration function didn't start with void! [%s]", line2);
        goto error;
    }

    /* extract void FUNCTIONNAME(...) */
    pos = strchr(line2, '(');
    if (!pos)
    {
        OIERROR1("Trace declaration function didn't have a name! [%s] Expected void func(...);", line2);
        goto error;
    }

    /* discount "void " */
    nameLength = pos - line2 - 5;
    if (nameLength >= OI_MAX_LENGTH)
    {
        OIERROR1("Invalid trace declaration! [%s] Expected void func(...);", line2);
        goto error;
    }

    /* discount "void " */
    memcpy(newEvent->Name, line2 + 5, nameLength);

    if (!_ParseArgs(newEvent, pos))
    {
        OIERROR2("Failed to parse arguments of the trace declaration [%s] from position [%s]", line2, pos);
        goto error;
    }

    return MI_TRUE;

error:
    OIERROR("Failed while parsing a C header!");
    if (newEvent)
        _Event_Destroy(newEvent);
    return MI_FALSE;
}

/* Parses a C header */
static MI_Boolean _ParseHeader(_In_ OIParser * parser, _In_ FILE * file, _In_ int * count)
{
    int oieventCount = 0;
    int lineNumber = 0;
    char buf[OI_MAX_LENGTH];
    OIEvent * current = 0;
    OIDefaults oidefault;

    /*
        State - 0; anything but a function declaration
        State - 1; need a function declaration now
    */
    int state = 0;

    memset(&oidefault, 0, sizeof(OIDefaults));
    if (!_SetOIDefaults(&oidefault))
        return MI_FALSE;

    *count = 0;

    while( fgets(buf, OI_MAX_LENGTH, file) != NULL )
    {
        char * line = buf;
        char tmp[OI_MAX_LENGTH];        

        memset(&tmp, 0, OI_MAX_LENGTH);
        lineNumber++;
        line = _Trim(line);

        OITRACE("[TRACE] Parsing line [%d]: %s", lineNumber, line);

        /* Look for SET_OIDEFAULT definitions */
        if (_StartsWith(line, "OI_SETDEFAULT") != 0)
        {
            if (state == 1)
            {
                OIERROR1("Was expecting a function declaration but got: %s", line);
                goto error;
            }

            if (_ParseOI_SetDefault(line, &oidefault) != MI_TRUE)
                return MI_FALSE;
        }
        /* Look for OI_EVENT definitions */
        else if (_StartsWith(line, "OI_EVENT") != 0 || _StartsWith(line, "/*OI_EVENT") || _StartsWith(line, "/* OI_EVENT") != 0)
        {
            if (state == 1)
            {
                OIERROR1("Was expecting a function declaration but got: %s", line);
                goto error;
            }

            if (_ParseOIEvent(line, &oidefault, &current) != MI_TRUE)
                return MI_FALSE;
            else
                state = 1;
        }
        else if (state == 1)
        {
            if (_ParseFunctionDecl(line, &oidefault, current) != MI_TRUE)
                return MI_FALSE;
            else
            {
                state = 0;
                oieventCount++;

                _Parser_AddEvent(parser, current);
                current = 0;
            }
        }
    }

    *count = oieventCount;
    return MI_TRUE;

error:
    OIERROR("Failed while parsing a C header!");
    if (current)
        _Event_Destroy(current);
    return MI_FALSE;
}

/********* PUBLIC DEFINITIONS ***************************************/

_Use_decl_annotations_
MI_Boolean Parser_Init(
    OIParser * parser,
    const char * header)
{
    memset(parser, 0, sizeof(OIParser));

    if (Strlcpy(parser->Header, header, OI_MAX_LENGTH) >= OI_MAX_LENGTH)
    {
        OIERROR1("Out of memory while copying [%s]! Header name too long?", header);
        return MI_FALSE;
    }

    return MI_TRUE;
}

_Use_decl_annotations_
MI_Boolean Parser_Parse(OIParser * parser, OIEvent ** events, int * count)
{
    FILE * file = fopen( parser->Header, "r" );
    *events = 0;
    *count = 0;

    if ( file != NULL )
    {
        MI_Boolean ret = _ParseHeader(parser, file, count);
        fclose ( file );

        *events = parser->head;

        return ret;
    }
    else
    {
        OIERROR1("Failed to open file [%s]! Wrong path or name?", parser->Header);
        return MI_FALSE;
    }
}

_Use_decl_annotations_
void Parser_Destroy(OIParser * parser)
{
    OIEvent * curr = parser->head;
    while( curr )
    {
        OIEvent * next = curr->next;
        _Event_Destroy(curr);

        curr = next;
    }
}

/* Calculates the length of the linked list */
_Use_decl_annotations_
int CountArguments(OIArgument * head)
{
    int ArgCount = 0;
    OIArgument * arg = head;

    /* Count  */
    while(arg)
    {
        OIArgument * next = arg->next;
        ArgCount++;
        arg = next;
    }

    return ArgCount;
}
