/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _OI_Parser_h_
#define _OI_Parser_h_

#include "common.h"

BEGIN_EXTERNC

#define OI_MAX_LENGTH 1024

typedef struct _OIArgument OIArgument;
struct _OIArgument
{
    char Name[OI_MAX_LENGTH];
    char Type[OI_MAX_LENGTH];

    OIArgument * next;
};

typedef struct _OIEvent OIEvent;
struct _OIEvent
{
    /* Common properties */
    char EventId[OI_MAX_LENGTH];
    char Name   [OI_MAX_LENGTH];
    char Format [OI_MAX_LENGTH];

    /* ETW section */
    char Channel  [OI_MAX_LENGTH];
    char Keyword  [OI_MAX_LENGTH];
    char Opcode   [OI_MAX_LENGTH];
    char Severity [OI_MAX_LENGTH];
    char Task     [OI_MAX_LENGTH];    

    /* Syslog priority */
    char Priority[OI_MAX_LENGTH];

    OIArgument * Argument;

    OIEvent * next;
};

typedef struct _OIParser OIParser;
struct _OIParser
{
    OIEvent * head;
    OIEvent * end;

    char Header      [OI_MAX_LENGTH];
};

/*
    Parser_Init

    parser - self object
    header - path to C header to be parsed
*/
MI_Boolean Parser_Init(
    _In_ OIParser * parser,
    _In_z_ const char * header);

/*
    Parser_Parse

    parser -
    events - linked list of events
    count - number of trace events found
*/
MI_Boolean Parser_Parse(
    _Inout_ OIParser * parser,
    _Out_ OIEvent ** events,
    _Out_ int * count);

void Parser_Destroy(_In_ OIParser * parser);

int CountArguments(_In_ OIArgument * head);

const char * _GetEtwLevel(_In_z_ const char * in);

END_EXTERNC

#endif /* _OI_Parser_h_ */
