/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "MILargeEvent.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

/*
**==============================================================================
**
** ETW_GUID
**
**==============================================================================
*/

/* property ETW_GUID.Data1 */
static MI_CONST MI_PropertyDecl ETW_GUID_Data1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643105, /* code */
    MI_T("Data1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_GUID, Data1), /* offset */
    MI_T("ETW_GUID"), /* origin */
    MI_T("ETW_GUID"), /* propagator */
    NULL,
};

/* property ETW_GUID.Data2 */
static MI_CONST MI_PropertyDecl ETW_GUID_Data2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643205, /* code */
    MI_T("Data2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_GUID, Data2), /* offset */
    MI_T("ETW_GUID"), /* origin */
    MI_T("ETW_GUID"), /* propagator */
    NULL,
};

/* property ETW_GUID.Data3 */
static MI_CONST MI_PropertyDecl ETW_GUID_Data3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643305, /* code */
    MI_T("Data3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_GUID, Data3), /* offset */
    MI_T("ETW_GUID"), /* origin */
    MI_T("ETW_GUID"), /* propagator */
    NULL,
};

/* property ETW_GUID.Data4 */
static MI_CONST MI_PropertyDecl ETW_GUID_Data4_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643405, /* code */
    MI_T("Data4"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    8, /* subscript */
    offsetof(ETW_GUID, Data4), /* offset */
    MI_T("ETW_GUID"), /* origin */
    MI_T("ETW_GUID"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ETW_GUID_props[] =
{
    &ETW_GUID_Data1_prop,
    &ETW_GUID_Data2_prop,
    &ETW_GUID_Data3_prop,
    &ETW_GUID_Data4_prop,
};

/* class ETW_GUID */
MI_CONST MI_ClassDecl ETW_GUID_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00656408, /* code */
    MI_T("ETW_GUID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ETW_GUID_props, /* properties */
    MI_COUNT(ETW_GUID_props), /* numProperties */
    sizeof(ETW_GUID), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ETW_EventHeader
**
**==============================================================================
*/

/* property ETW_EventHeader.ThreadId */
static MI_CONST MI_PropertyDecl ETW_EventHeader_ThreadId_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746408, /* code */
    MI_T("ThreadId"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, ThreadId), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.ProcessId */
static MI_CONST MI_PropertyDecl ETW_EventHeader_ProcessId_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706409, /* code */
    MI_T("ProcessId"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, ProcessId), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.TimeStamp */
static MI_CONST MI_PropertyDecl ETW_EventHeader_TimeStamp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747009, /* code */
    MI_T("TimeStamp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, TimeStamp), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* ETW_EventHeader_ActivityId_EmbeddedInstance_qual_value = MI_T("ETW_GUID");

static MI_CONST MI_Qualifier ETW_EventHeader_ActivityId_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &ETW_EventHeader_ActivityId_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ETW_EventHeader_ActivityId_quals[] =
{
    &ETW_EventHeader_ActivityId_EmbeddedInstance_qual,
};

/* property ETW_EventHeader.ActivityId */
static MI_CONST MI_PropertyDecl ETW_EventHeader_ActivityId_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061640A, /* code */
    MI_T("ActivityId"), /* name */
    ETW_EventHeader_ActivityId_quals, /* qualifiers */
    MI_COUNT(ETW_EventHeader_ActivityId_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("ETW_GUID"), /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, ActivityId), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* ETW_EventHeader_ProviderId_EmbeddedInstance_qual_value = MI_T("ETW_GUID");

static MI_CONST MI_Qualifier ETW_EventHeader_ProviderId_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &ETW_EventHeader_ProviderId_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ETW_EventHeader_ProviderId_quals[] =
{
    &ETW_EventHeader_ProviderId_EmbeddedInstance_qual,
};

/* property ETW_EventHeader.ProviderId */
static MI_CONST MI_PropertyDecl ETW_EventHeader_ProviderId_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070640A, /* code */
    MI_T("ProviderId"), /* name */
    ETW_EventHeader_ProviderId_quals, /* qualifiers */
    MI_COUNT(ETW_EventHeader_ProviderId_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("ETW_GUID"), /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, ProviderId), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.EventId */
static MI_CONST MI_PropertyDecl ETW_EventHeader_EventId_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656407, /* code */
    MI_T("EventId"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, EventId), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Version */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Version_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766E07, /* code */
    MI_T("Version"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Version), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Channel */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Channel_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636C07, /* code */
    MI_T("Channel"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Channel), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Level */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Level_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6C05, /* code */
    MI_T("Level"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Level), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Opcode */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Opcode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6506, /* code */
    MI_T("Opcode"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Opcode), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Task */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Task_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746B04, /* code */
    MI_T("Task"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Task), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

/* property ETW_EventHeader.Keyword */
static MI_CONST MI_PropertyDecl ETW_EventHeader_Keyword_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B6407, /* code */
    MI_T("Keyword"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ETW_EventHeader, Keyword), /* offset */
    MI_T("ETW_EventHeader"), /* origin */
    MI_T("ETW_EventHeader"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ETW_EventHeader_props[] =
{
    &ETW_EventHeader_ThreadId_prop,
    &ETW_EventHeader_ProcessId_prop,
    &ETW_EventHeader_TimeStamp_prop,
    &ETW_EventHeader_ActivityId_prop,
    &ETW_EventHeader_ProviderId_prop,
    &ETW_EventHeader_EventId_prop,
    &ETW_EventHeader_Version_prop,
    &ETW_EventHeader_Channel_prop,
    &ETW_EventHeader_Level_prop,
    &ETW_EventHeader_Opcode_prop,
    &ETW_EventHeader_Task_prop,
    &ETW_EventHeader_Keyword_prop,
};

/* class ETW_EventHeader */
MI_CONST MI_ClassDecl ETW_EventHeader_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0065720F, /* code */
    MI_T("ETW_EventHeader"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ETW_EventHeader_props, /* properties */
    MI_COUNT(ETW_EventHeader_props), /* numProperties */
    sizeof(ETW_EventHeader), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ETW_Event
**
**==============================================================================
*/

static MI_CONST MI_Char* ETW_Event_Header_EmbeddedInstance_qual_value = MI_T("ETW_EventHeader");

static MI_CONST MI_Qualifier ETW_Event_Header_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &ETW_Event_Header_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ETW_Event_Header_quals[] =
{
    &ETW_Event_Header_EmbeddedInstance_qual,
};

/* property ETW_Event.Header */
static MI_CONST MI_PropertyDecl ETW_Event_Header_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00687206, /* code */
    MI_T("Header"), /* name */
    ETW_Event_Header_quals, /* qualifiers */
    MI_COUNT(ETW_Event_Header_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("ETW_EventHeader"), /* className */
    0, /* subscript */
    offsetof(ETW_Event, Header), /* offset */
    MI_T("ETW_Event"), /* origin */
    MI_T("ETW_Event"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ETW_Event_props[] =
{
    &ETW_Event_Header_prop,
};

/* class ETW_Event */
MI_CONST MI_ClassDecl ETW_Event_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00657409, /* code */
    MI_T("ETW_Event"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ETW_Event_props, /* properties */
    MI_COUNT(ETW_Event_props), /* numProperties */
    sizeof(ETW_Event), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MILargeEvent
**
**==============================================================================
*/

/* property MILargeEvent.ID */
static MI_CONST MI_PropertyDecl MILargeEvent_ID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("ID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, ID), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number1 */
static MI_CONST MI_PropertyDecl MILargeEvent_number1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3107, /* code */
    MI_T("number1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number1), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number2 */
static MI_CONST MI_PropertyDecl MILargeEvent_number2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3207, /* code */
    MI_T("number2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number2), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number3 */
static MI_CONST MI_PropertyDecl MILargeEvent_number3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3307, /* code */
    MI_T("number3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number3), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number4 */
static MI_CONST MI_PropertyDecl MILargeEvent_number4_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3407, /* code */
    MI_T("number4"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number4), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number5 */
static MI_CONST MI_PropertyDecl MILargeEvent_number5_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3507, /* code */
    MI_T("number5"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number5), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number6 */
static MI_CONST MI_PropertyDecl MILargeEvent_number6_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3607, /* code */
    MI_T("number6"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number6), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number7 */
static MI_CONST MI_PropertyDecl MILargeEvent_number7_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3707, /* code */
    MI_T("number7"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number7), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number8 */
static MI_CONST MI_PropertyDecl MILargeEvent_number8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3807, /* code */
    MI_T("number8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number8), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number9 */
static MI_CONST MI_PropertyDecl MILargeEvent_number9_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3907, /* code */
    MI_T("number9"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number9), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.number10 */
static MI_CONST MI_PropertyDecl MILargeEvent_number10_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3008, /* code */
    MI_T("number10"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, number10), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string1 */
static MI_CONST MI_PropertyDecl MILargeEvent_string1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733107, /* code */
    MI_T("string1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string1), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string2 */
static MI_CONST MI_PropertyDecl MILargeEvent_string2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733207, /* code */
    MI_T("string2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string2), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string3 */
static MI_CONST MI_PropertyDecl MILargeEvent_string3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733307, /* code */
    MI_T("string3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string3), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string4 */
static MI_CONST MI_PropertyDecl MILargeEvent_string4_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733407, /* code */
    MI_T("string4"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string4), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string5 */
static MI_CONST MI_PropertyDecl MILargeEvent_string5_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733507, /* code */
    MI_T("string5"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string5), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string6 */
static MI_CONST MI_PropertyDecl MILargeEvent_string6_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733607, /* code */
    MI_T("string6"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string6), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string7 */
static MI_CONST MI_PropertyDecl MILargeEvent_string7_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733707, /* code */
    MI_T("string7"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string7), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string8 */
static MI_CONST MI_PropertyDecl MILargeEvent_string8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733807, /* code */
    MI_T("string8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string8), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string9 */
static MI_CONST MI_PropertyDecl MILargeEvent_string9_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733907, /* code */
    MI_T("string9"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string9), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

/* property MILargeEvent.string10 */
static MI_CONST MI_PropertyDecl MILargeEvent_string10_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733008, /* code */
    MI_T("string10"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MILargeEvent, string10), /* offset */
    MI_T("MILargeEvent"), /* origin */
    MI_T("MILargeEvent"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MILargeEvent_props[] =
{
    &ETW_Event_Header_prop,
    &MILargeEvent_ID_prop,
    &MILargeEvent_number1_prop,
    &MILargeEvent_number2_prop,
    &MILargeEvent_number3_prop,
    &MILargeEvent_number4_prop,
    &MILargeEvent_number5_prop,
    &MILargeEvent_number6_prop,
    &MILargeEvent_number7_prop,
    &MILargeEvent_number8_prop,
    &MILargeEvent_number9_prop,
    &MILargeEvent_number10_prop,
    &MILargeEvent_string1_prop,
    &MILargeEvent_string2_prop,
    &MILargeEvent_string3_prop,
    &MILargeEvent_string4_prop,
    &MILargeEvent_string5_prop,
    &MILargeEvent_string6_prop,
    &MILargeEvent_string7_prop,
    &MILargeEvent_string8_prop,
    &MILargeEvent_string9_prop,
    &MILargeEvent_string10_prop,
};

static MI_CONST MI_ProviderFT MILargeEvent_funcs =
{
  (MI_ProviderFT_Load)MILargeEvent_Load,
  (MI_ProviderFT_Unload)MILargeEvent_Unload,
  (MI_ProviderFT_GetInstance)MILargeEvent_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MILargeEvent_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MILargeEvent_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MILargeEvent_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MILargeEvent_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MILargeEvent */
MI_CONST MI_ClassDecl MILargeEvent_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D740C, /* code */
    MI_T("MILargeEvent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MILargeEvent_props, /* properties */
    MI_COUNT(MILargeEvent_props), /* numProperties */
    sizeof(MILargeEvent), /* size */
    MI_T("ETW_Event"), /* superClass */
    &ETW_Event_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MILargeEvent_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &ETW_Event_rtti,
    &ETW_EventHeader_rtti,
    &ETW_GUID_rtti,
    &MILargeEvent_rtti,
};

MI_SchemaDecl schemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

/*
**==============================================================================
**
** MI_Server Methods
**
**==============================================================================
*/

MI_Result MI_CALL MI_Server_GetVersion(
    MI_Uint32* version){
    return __mi_server->serverFT->GetVersion(version);
}

MI_Result MI_CALL MI_Server_GetSystemName(
    const MI_Char** systemName)
{
    return __mi_server->serverFT->GetSystemName(systemName);
}

