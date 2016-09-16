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
#include "OMI_DebugError.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

MI_EXTERN_C MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Error_ErrorType_Description_qual_value = MI_T("Primary classification of the error. The following values are defined: \n2 - Communications Error. Errors of this type are principally associated with the procedures and/or processes required to convey information from one point to another. \n3 - Quality of Service Error. Errors of this type are principally associated with failures that result in reduced functionality or performance. \n4 - Software Error. Error of this type are principally associated with a software or processing fault. \n5 - Hardware Error. Errors of this type are principally associated with an equipment or hardware failure. \n6 - Environmental Error. Errors of this type are principally associated with a failure condition relating to the facility, or other environmental considerations. \n7 - Security Error. Errors of this type are associated with security violations, detection of viruses, and similar issues. \n8 - Oversubscription Error. Errors of this type are principally associated with the failure to allocate sufficient resources to complete the operation. \n9 - Unavailable Resource Error. Errors of this type are principally associated with the failure to access a required resource. \n10 -Unsupported Operation Error. Errors of this type are principally associated with requests that are not supported.");

static MI_CONST MI_Qualifier CIM_Error_ErrorType_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorType_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_ValueMap_qual_value =
{
    CIM_Error_ErrorType_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorType_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Communications Error"),
    MI_T("Quality of Service Error"),
    MI_T("Software Error"),
    MI_T("Hardware Error"),
    MI_T("Environmental Error"),
    MI_T("Security Error"),
    MI_T("Oversubscription Error"),
    MI_T("Unavailable Resource Error"),
    MI_T("Unsupported Operation Error"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_Values_qual_value =
{
    CIM_Error_ErrorType_Values_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorType_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.OtherErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorType_quals[] =
{
    &CIM_Error_ErrorType_Description_qual,
    &CIM_Error_ErrorType_ValueMap_qual,
    &CIM_Error_ErrorType_Values_qual,
    &CIM_Error_ErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorType_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorType"), /* name */
    CIM_Error_ErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorType_Description_qual_value = MI_T("A free-form string describing the ErrorType when 1, \"Other\", is specified as the ErrorType.");

static MI_CONST MI_Qualifier CIM_Error_OtherErrorType_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OtherErrorType_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorType_quals[] =
{
    &CIM_Error_OtherErrorType_Description_qual,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorType_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F650E, /* code */
    MI_T("OtherErrorType"), /* name */
    CIM_Error_OtherErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_OwningEntity_Description_qual_value = MI_T("A string that uniquely identifies the entity that owns the definition of the format of the Message described in this instance. OwningEntity MUST include a copyrighted, trademarked or otherwise unique name that is owned by the business entity or standards body defining the format.");

static MI_CONST MI_Qualifier CIM_Error_OwningEntity_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OwningEntity_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OwningEntity_quals[] =
{
    &CIM_Error_OwningEntity_Description_qual,
};

/* property CIM_Error.OwningEntity */
static MI_CONST MI_PropertyDecl CIM_Error_OwningEntity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F790C, /* code */
    MI_T("OwningEntity"), /* name */
    CIM_Error_OwningEntity_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OwningEntity_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OwningEntity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean CIM_Error_MessageID_Required_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_MessageID_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageID_Required_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageID_Description_qual_value = MI_T("An opaque string that uniquely identifies, within the scope of the OwningEntity, the format of the Message.");

static MI_CONST MI_Qualifier CIM_Error_MessageID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_MessageID_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageID_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.Message"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageID_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageID_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageID_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageID_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageID_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageID_quals[] =
{
    &CIM_Error_MessageID_Required_qual,
    &CIM_Error_MessageID_Description_qual,
    &CIM_Error_MessageID_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageID */
static MI_CONST MI_PropertyDecl CIM_Error_MessageID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D6409, /* code */
    MI_T("MessageID"), /* name */
    CIM_Error_MessageID_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageID), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_Message_Description_qual_value = MI_T("The formatted message. This message is constructed by combining some or all of the dynamic elements specified in the MessageArguments property with the static elements uniquely identified by the MessageID in a message registry or other catalog associated with the OwningEntity.");

static MI_CONST MI_Qualifier CIM_Error_Message_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_Message_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_Message_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_Message_ModelCorrespondence_qual_value =
{
    CIM_Error_Message_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_Message_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_Message_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Message_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_Message_quals[] =
{
    &CIM_Error_Message_Description_qual,
    &CIM_Error_Message_ModelCorrespondence_qual,
};

/* property CIM_Error.Message */
static MI_CONST MI_PropertyDecl CIM_Error_Message_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D6507, /* code */
    MI_T("Message"), /* name */
    CIM_Error_Message_quals, /* qualifiers */
    MI_COUNT(CIM_Error_Message_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, Message), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_MessageArguments_Description_qual_value = MI_T("An array containing the dynamic content of the message.");

static MI_CONST MI_Qualifier CIM_Error_MessageArguments_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_MessageArguments_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.Message"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageArguments_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageArguments_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageArguments_quals[] =
{
    &CIM_Error_MessageArguments_Description_qual,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageArguments */
static MI_CONST MI_PropertyDecl CIM_Error_MessageArguments_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D7310, /* code */
    MI_T("MessageArguments"), /* name */
    CIM_Error_MessageArguments_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageArguments_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageArguments), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Description_qual_value = MI_T("An enumerated value that describes the severity of the Indication from the notifier\'s point of view: \n0 - the Perceived Severity of the indication is unknown or indeterminate. \n1 - Other, by CIM convention, is used to indicate that the Severity\'s value can be found in the OtherSeverity property. \n2 - Information should be used when providing an informative response. \n3 - Degraded/Warning should be used when its appropriate to let the user decide if action is needed. \n4 - Minor should be used to indicate action is needed, but the situation is not serious at this time. \n5 - Major should be used to indicate action is needed NOW. \n6 - Critical should be used to indicate action is needed NOW and the scope is broad (perhaps an imminent outage to a critical resource will result). \n7 - Fatal/NonRecoverable should be used to indicate an error occurred, but it\'s too late to take remedial action. \n2 and 0 - Information and Unknown (respectively) follow common usage. Literally, the Error is purely informational or its severity is simply unknown.");

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_PerceivedSeverity_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_PerceivedSeverity_ValueMap_qual_value =
{
    CIM_Error_PerceivedSeverity_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_PerceivedSeverity_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_PerceivedSeverity_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Information"),
    MI_T("Degraded/Warning"),
    MI_T("Minor"),
    MI_T("Major"),
    MI_T("Critical"),
    MI_T("Fatal/NonRecoverable"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_Error_PerceivedSeverity_Values_qual_value =
{
    CIM_Error_PerceivedSeverity_Values_qual_data_value,
    MI_COUNT(CIM_Error_PerceivedSeverity_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_PerceivedSeverity_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_PerceivedSeverity_quals[] =
{
    &CIM_Error_PerceivedSeverity_Description_qual,
    &CIM_Error_PerceivedSeverity_ValueMap_qual,
    &CIM_Error_PerceivedSeverity_Values_qual,
};

/* property CIM_Error.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Error_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    CIM_Error_PerceivedSeverity_quals, /* qualifiers */
    MI_COUNT(CIM_Error_PerceivedSeverity_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, PerceivedSeverity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_Description_qual_value = MI_T("An enumerated value that describes the probable cause of the error.");

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCause_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T("30"),
    MI_T("31"),
    MI_T("32"),
    MI_T("33"),
    MI_T("34"),
    MI_T("35"),
    MI_T("36"),
    MI_T("37"),
    MI_T("38"),
    MI_T("39"),
    MI_T("40"),
    MI_T("41"),
    MI_T("42"),
    MI_T("43"),
    MI_T("44"),
    MI_T("45"),
    MI_T("46"),
    MI_T("47"),
    MI_T("48"),
    MI_T("49"),
    MI_T("50"),
    MI_T("51"),
    MI_T("52"),
    MI_T("53"),
    MI_T("54"),
    MI_T("55"),
    MI_T("56"),
    MI_T("57"),
    MI_T("58"),
    MI_T("59"),
    MI_T("60"),
    MI_T("61"),
    MI_T("62"),
    MI_T("63"),
    MI_T("64"),
    MI_T("65"),
    MI_T("66"),
    MI_T("67"),
    MI_T("68"),
    MI_T("69"),
    MI_T("70"),
    MI_T("71"),
    MI_T("72"),
    MI_T("73"),
    MI_T("74"),
    MI_T("75"),
    MI_T("76"),
    MI_T("77"),
    MI_T("78"),
    MI_T("79"),
    MI_T("80"),
    MI_T("81"),
    MI_T("82"),
    MI_T("83"),
    MI_T("84"),
    MI_T("85"),
    MI_T("86"),
    MI_T("87"),
    MI_T("88"),
    MI_T("89"),
    MI_T("90"),
    MI_T("91"),
    MI_T("92"),
    MI_T("93"),
    MI_T("94"),
    MI_T("95"),
    MI_T("96"),
    MI_T("97"),
    MI_T("98"),
    MI_T("99"),
    MI_T("100"),
    MI_T("101"),
    MI_T("102"),
    MI_T("103"),
    MI_T("104"),
    MI_T("105"),
    MI_T("106"),
    MI_T("107"),
    MI_T("108"),
    MI_T("109"),
    MI_T("110"),
    MI_T("111"),
    MI_T("112"),
    MI_T("113"),
    MI_T("114"),
    MI_T("115"),
    MI_T("116"),
    MI_T("117"),
    MI_T("118"),
    MI_T("119"),
    MI_T("120"),
    MI_T("121"),
    MI_T("122"),
    MI_T("123"),
    MI_T("124"),
    MI_T("125"),
    MI_T("126"),
    MI_T("127"),
    MI_T("128"),
    MI_T("129"),
    MI_T("130"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_ValueMap_qual_value =
{
    CIM_Error_ProbableCause_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCause_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Adapter/Card Error"),
    MI_T("Application Subsystem Failure"),
    MI_T("Bandwidth Reduced"),
    MI_T("Connection Establishment Error"),
    MI_T("Communications Protocol Error"),
    MI_T("Communications Subsystem Failure"),
    MI_T("Configuration/Customization Error"),
    MI_T("Congestion"),
    MI_T("Corrupt Data"),
    MI_T("CPU Cycles Limit Exceeded"),
    MI_T("Dataset/Modem Error"),
    MI_T("Degraded Signal"),
    MI_T("DTE-DCE Interface Error"),
    MI_T("Enclosure Door Open"),
    MI_T("Equipment Malfunction"),
    MI_T("Excessive Vibration"),
    MI_T("File Format Error"),
    MI_T("Fire Detected"),
    MI_T("Flood Detected"),
    MI_T("Framing Error"),
    MI_T("HVAC Problem"),
    MI_T("Humidity Unacceptable"),
    MI_T("I/O Device Error"),
    MI_T("Input Device Error"),
    MI_T("LAN Error"),
    MI_T("Non-Toxic Leak Detected"),
    MI_T("Local Node Transmission Error"),
    MI_T("Loss of Frame"),
    MI_T("Loss of Signal"),
    MI_T("Material Supply Exhausted"),
    MI_T("Multiplexer Problem"),
    MI_T("Out of Memory"),
    MI_T("Output Device Error"),
    MI_T("Performance Degraded"),
    MI_T("Power Problem"),
    MI_T("Pressure Unacceptable"),
    MI_T("Processor Problem (Internal Machine Error)"),
    MI_T("Pump Failure"),
    MI_T("Queue Size Exceeded"),
    MI_T("Receive Failure"),
    MI_T("Receiver Failure"),
    MI_T("Remote Node Transmission Error"),
    MI_T("Resource at or Nearing Capacity"),
    MI_T("Response Time Excessive"),
    MI_T("Retransmission Rate Excessive"),
    MI_T("Software Error"),
    MI_T("Software Program Abnormally Terminated"),
    MI_T("Software Program Error (Incorrect Results)"),
    MI_T("Storage Capacity Problem"),
    MI_T("Temperature Unacceptable"),
    MI_T("Threshold Crossed"),
    MI_T("Timing Problem"),
    MI_T("Toxic Leak Detected"),
    MI_T("Transmit Failure"),
    MI_T("Transmitter Failure"),
    MI_T("Underlying Resource Unavailable"),
    MI_T("Version Mismatch"),
    MI_T("Previous Alert Cleared"),
    MI_T("Login Attempts Failed"),
    MI_T("Software Virus Detected"),
    MI_T("Hardware Security Breached"),
    MI_T("Denial of Service Detected"),
    MI_T("Security Credential Mismatch"),
    MI_T("Unauthorized Access"),
    MI_T("Alarm Received"),
    MI_T("Loss of Pointer"),
    MI_T("Payload Mismatch"),
    MI_T("Transmission Error"),
    MI_T("Excessive Error Rate"),
    MI_T("Trace Problem"),
    MI_T("Element Unavailable"),
    MI_T("Element Missing"),
    MI_T("Loss of Multi Frame"),
    MI_T("Broadcast Channel Failure"),
    MI_T("Invalid Message Received"),
    MI_T("Routing Failure"),
    MI_T("Backplane Failure"),
    MI_T("Identifier Duplication"),
    MI_T("Protection Path Failure"),
    MI_T("Sync Loss or Mismatch"),
    MI_T("Terminal Problem"),
    MI_T("Real Time Clock Failure"),
    MI_T("Antenna Failure"),
    MI_T("Battery Charging Failure"),
    MI_T("Disk Failure"),
    MI_T("Frequency Hopping Failure"),
    MI_T("Loss of Redundancy"),
    MI_T("Power Supply Failure"),
    MI_T("Signal Quality Problem"),
    MI_T("Battery Discharging"),
    MI_T("Battery Failure"),
    MI_T("Commercial Power Problem"),
    MI_T("Fan Failure"),
    MI_T("Engine Failure"),
    MI_T("Sensor Failure"),
    MI_T("Fuse Failure"),
    MI_T("Generator Failure"),
    MI_T("Low Battery"),
    MI_T("Low Fuel"),
    MI_T("Low Water"),
    MI_T("Explosive Gas"),
    MI_T("High Winds"),
    MI_T("Ice Buildup"),
    MI_T("Smoke"),
    MI_T("Memory Mismatch"),
    MI_T("Out of CPU Cycles"),
    MI_T("Software Environment Problem"),
    MI_T("Software Download Failure"),
    MI_T("Element Reinitialized"),
    MI_T("Timeout"),
    MI_T("Logging Problems"),
    MI_T("Leak Detected"),
    MI_T("Protection Mechanism Failure"),
    MI_T("Protecting Resource Failure"),
    MI_T("Database Inconsistency"),
    MI_T("Authentication Failure"),
    MI_T("Breach of Confidentiality"),
    MI_T("Cable Tamper"),
    MI_T("Delayed Information"),
    MI_T("Duplicate Information"),
    MI_T("Information Missing"),
    MI_T("Information Modification"),
    MI_T("Information Out of Sequence"),
    MI_T("Key Expired"),
    MI_T("Non-Repudiation Failure"),
    MI_T("Out of Hours Activity"),
    MI_T("Out of Service"),
    MI_T("Procedural Error"),
    MI_T("Unexpected Information"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_Values_qual_value =
{
    CIM_Error_ProbableCause_Values_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCause_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCauseDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCause_quals[] =
{
    &CIM_Error_ProbableCause_Description_qual,
    &CIM_Error_ProbableCause_ValueMap_qual,
    &CIM_Error_ProbableCause_Values_qual,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCause */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCause_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0070650D, /* code */
    MI_T("ProbableCause"), /* name */
    CIM_Error_ProbableCause_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCause_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCause), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_Description_qual_value = MI_T("A free-form string describing the probable cause of the error.");

static MI_CONST MI_Qualifier CIM_Error_ProbableCauseDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCauseDescription_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCause"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCauseDescription_quals[] =
{
    &CIM_Error_ProbableCauseDescription_Description_qual,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCauseDescription */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCauseDescription_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00706E18, /* code */
    MI_T("ProbableCauseDescription"), /* name */
    CIM_Error_ProbableCauseDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCauseDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCauseDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_RecommendedActions_Description_qual_value = MI_T("A free-form string describing recommended actions to take to resolve the error.");

static MI_CONST MI_Qualifier CIM_Error_RecommendedActions_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_RecommendedActions_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_RecommendedActions_quals[] =
{
    &CIM_Error_RecommendedActions_Description_qual,
};

/* property CIM_Error.RecommendedActions */
static MI_CONST MI_PropertyDecl CIM_Error_RecommendedActions_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00727312, /* code */
    MI_T("RecommendedActions"), /* name */
    CIM_Error_RecommendedActions_quals, /* qualifiers */
    MI_COUNT(CIM_Error_RecommendedActions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, RecommendedActions), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSource_Description_qual_value = MI_T("The identifying information of the entity (i.e., the instance) generating the error. If this entity is modeled in the CIM Schema, this property contains the path of the instance encoded as a string parameter. If not modeled, the property contains some identifying string that names the entity that generated the error. The path or identifying string is formatted per the ErrorSourceFormat property.");

static MI_CONST MI_Qualifier CIM_Error_ErrorSource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSource_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSource_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSource_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSource_quals[] =
{
    &CIM_Error_ErrorSource_Description_qual,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorSource */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSource_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650B, /* code */
    MI_T("ErrorSource"), /* name */
    CIM_Error_ErrorSource_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSource_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSource), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Description_qual_value = MI_T("The format of the ErrorSource property is interpretable based on the value of this property. Values are defined as: \n0 - Unknown. The format is unknown or not meaningfully interpretable by a CIM client application. \n1 - Other. The format is defined by the value of the OtherErrorSourceFormat property.2 - CIMObjectPath. A CIM Object Path as defined in the CIM Infrastructure specification. Note: CIM 2.5 and earlier used the term object names.");

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSourceFormat_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_ValueMap_qual_value =
{
    CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSourceFormat_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("CIMObjectPath"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_Values_qual_value =
{
    CIM_Error_ErrorSourceFormat_Values_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSourceFormat_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSource"),
    MI_T("CIM_Error.OtherErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSourceFormat_quals[] =
{
    &CIM_Error_ErrorSourceFormat_Description_qual,
    &CIM_Error_ErrorSourceFormat_ValueMap_qual,
    &CIM_Error_ErrorSourceFormat_Values_qual,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_Error_ErrorSourceFormat_value = 0;

/* property CIM_Error.ErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00657411, /* code */
    MI_T("ErrorSourceFormat"), /* name */
    CIM_Error_ErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSourceFormat_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    &CIM_Error_ErrorSourceFormat_value,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_Description_qual_value = MI_T("A string defining \"Other\" values for ErrorSourceFormat. This value MUST be set to a non NULL value when ErrorSourceFormat is set to a value of 1 (\"Other\"). For all other values of ErrorSourceFormat, the value of this string must be set to NULL.");

static MI_CONST MI_Qualifier CIM_Error_OtherErrorSourceFormat_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OtherErrorSourceFormat_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorSourceFormat_quals[] =
{
    &CIM_Error_OtherErrorSourceFormat_Description_qual,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F7416, /* code */
    MI_T("OtherErrorSourceFormat"), /* name */
    CIM_Error_OtherErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Description_qual_value = MI_T("The CIM status code that characterizes this instance. \nThis property defines the status codes that MAY be returned by a conforming CIM Server or Listener. Note that not all status codes are valid for each operation. The specification for each operation SHOULD define the status codes that may be returned by that operation. \nThe following values for CIM status code are defined: \n1 - CIM_ERR_FAILED. A general error occurred that is not covered by a more specific error code. \n2 - CIM_ERR_ACCESS_DENIED. Access to a CIM resource was not available to the client. \n3 - CIM_ERR_INVALID_NAMESPACE. The target namespace does not exist. \n4 - CIM_ERR_INVALID_PARAMETER. One or more parameter values passed to the method were invalid. \n5 - CIM_ERR_INVALID_CLASS. The specified Class does not exist. \n6 - CIM_ERR_NOT_FOUND. The requested object could not be found. \n7 - CIM_ERR_NOT_SUPPORTED. The requested operation is not supported. \n8 - CIM_ERR_CLASS_HAS_CHILDREN. Operation cannot be carried out on this class since it has instances. \n9 - CIM_ERR_CLASS_HAS_INSTANCES. Operation cannot be carried out on this class since it has instances. \n10 - CIM_ERR_INVALID_SUPERCLASS. Operation cannot be carried out since the specified superclass does not exist. \n11 - CIM_ERR_ALREADY_EXISTS. Operation cannot be carried out because an object already exists. \n12 - CIM_ERR_NO_SUCH_PROPERTY. The specified Property does not exist. \n13 - CIM_ERR_TYPE_MISMATCH. The value supplied is incompatible with the type. \n14 - CIM_ERR_QUERY_LANGUAGE_NOT_SUPPORTED. The query language is not recognized or supported. \n15 - CIM_ERR_INVALID_QUERY. The query is not valid for the specified query language. \n16 - CIM_ERR_METHOD_NOT_AVAILABLE. The extrinsic Method could not be executed. \n17 - CIM_ERR_METHOD_NOT_FOUND. The specified extrinsic Method does not exist. \n18 - CIM_ERR_UNEXPECTED_RESPONSE. The returned response to the asynchronous operation was not expected. \n19 - CIM_ERR_INVALID_RESPONSE_DESTINATION. The specified destination for the asynchronous response is not valid. \n20 - CIM_ERR_NAMESPACE_NOT_EMPTY. The specified Namespace is not empty.\n21 - CIM_ERR_INVALID_ENUMERATION_CONTEXT. The enumeration context supplied is not valid.\n22 - CIM_ERR_INVALID_OPERATION_TIMEOUT. The specified Namespace is not empty.\n23 - CIM_ERR_PULL_HAS_BEEN_ABANDONED. The specified Namespace is not empty.\n24 - CIM_ERR_PULL_CANNOT_BE_ABANDONED. The attempt to abandon a pull operation has failed.\n25 - CIM_ERR_FILTERED_ENUMERATION_NOT_SUPPORTED. Filtered Enumeratrions are not supported.\n26 - CIM_ERR_CONTINUATION_ON_ERROR_NOT_SUPPORTED. Continue on error is not supported.\n27 - CIM_ERR_SERVER_LIMITS_EXCEEDED. The WBEM Server limits have been exceeded (e.g. memory, connections, ...).\n28 - CIM_ERR_SERVER_IS_SHUTTING_DOWN. The WBEM Server is shutting down.\n29 - CIM_ERR_QUERY_FEATURE_NOT_SUPPORTED. The specified Query Feature is not supported.");

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCode_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_ValueMap_qual_value =
{
    CIM_Error_CIMStatusCode_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCode_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Values_qual_data_value[] =
{
    MI_T("CIM_ERR_FAILED"),
    MI_T("CIM_ERR_ACCESS_DENIED"),
    MI_T("CIM_ERR_INVALID_NAMESPACE"),
    MI_T("CIM_ERR_INVALID_PARAMETER"),
    MI_T("CIM_ERR_INVALID_CLASS"),
    MI_T("CIM_ERR_NOT_FOUND"),
    MI_T("CIM_ERR_NOT_SUPPORTED"),
    MI_T("CIM_ERR_CLASS_HAS_CHILDREN"),
    MI_T("CIM_ERR_CLASS_HAS_INSTANCES"),
    MI_T("CIM_ERR_INVALID_SUPERCLASS"),
    MI_T("CIM_ERR_ALREADY_EXISTS"),
    MI_T("CIM_ERR_NO_SUCH_PROPERTY"),
    MI_T("CIM_ERR_TYPE_MISMATCH"),
    MI_T("CIM_ERR_QUERY_LANGUAGE_NOT_SUPPORTED"),
    MI_T("CIM_ERR_INVALID_QUERY"),
    MI_T("CIM_ERR_METHOD_NOT_AVAILABLE"),
    MI_T("CIM_ERR_METHOD_NOT_FOUND"),
    MI_T("CIM_ERR_UNEXPECTED_RESPONSE"),
    MI_T("CIM_ERR_INVALID_RESPONSE_DESTINATION"),
    MI_T("CIM_ERR_NAMESPACE_NOT_EMPTY"),
    MI_T("CIM_ERR_INVALID_ENUMERATION_CONTEXT"),
    MI_T("CIM_ERR_INVALID_OPERATION_TIMEOUT"),
    MI_T("CIM_ERR_PULL_HAS_BEEN_ABANDONED"),
    MI_T("CIM_ERR_PULL_CANNOT_BE_ABANDONED"),
    MI_T("CIM_ERR_FILTERED_ENUMERATION_NOT_SUPPORTED"),
    MI_T("CIM_ERR_CONTINUATION_ON_ERROR_NOT_SUPPORTED"),
    MI_T("CIM_ERR_SERVER_LIMITS_EXCEEDED"),
    MI_T("CIM_ERR_SERVER_IS_SHUTTING_DOWN"),
    MI_T("CIM_ERR_QUERY_FEATURE_NOT_SUPPORTED"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_Values_qual_value =
{
    CIM_Error_CIMStatusCode_Values_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCode_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCodeDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCode_quals[] =
{
    &CIM_Error_CIMStatusCode_Description_qual,
    &CIM_Error_CIMStatusCode_ValueMap_qual,
    &CIM_Error_CIMStatusCode_Values_qual,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCode */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCode_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063650D, /* code */
    MI_T("CIMStatusCode"), /* name */
    CIM_Error_CIMStatusCode_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCode_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCode), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_Description_qual_value = MI_T("A free-form string containing a human-readable description of CIMStatusCode. This description MAY extend, but MUST be consistent with, the definition of CIMStatusCode.");

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCodeDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCodeDescription_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCode"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCodeDescription_quals[] =
{
    &CIM_Error_CIMStatusCodeDescription_Description_qual,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCodeDescription */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCodeDescription_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00636E18, /* code */
    MI_T("CIMStatusCodeDescription"), /* name */
    CIM_Error_CIMStatusCodeDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCodeDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
};

static MI_CONST MI_Boolean CIM_Error_Indication_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Indication_qual_value
};

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("2.22.1");

static MI_CONST MI_Qualifier CIM_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Error_Version_qual_value
};

static MI_CONST MI_Boolean CIM_Error_Exception_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_Exception_qual =
{
    MI_T("Exception"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Exception_qual_value
};

static MI_CONST MI_Char* CIM_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Error_Description_qual_value = MI_T("CIM_Error is a specialized class that contains information about the severity, cause, recommended actions and other data related to the failure of a CIM Operation. Instances of this type MAY be included as part of the response to a CIM Operation.");

static MI_CONST MI_Qualifier CIM_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_quals[] =
{
    &CIM_Error_Indication_qual,
    &CIM_Error_Version_qual,
    &CIM_Error_Exception_qual,
    &CIM_Error_UMLPackagePath_qual,
    &CIM_Error_Description_qual,
};

/* class CIM_Error */
MI_CONST MI_ClassDecl CIM_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00637209, /* code */
    MI_T("CIM_Error"), /* name */
    CIM_Error_quals, /* qualifiers */
    MI_COUNT(CIM_Error_quals), /* numQualifiers */
    CIM_Error_props, /* properties */
    MI_COUNT(CIM_Error_props), /* numProperties */
    sizeof(CIM_Error), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** OMI_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* OMI_Error_error_Code_Description_qual_value = MI_T("Application-specific error code");

static MI_CONST MI_Qualifier OMI_Error_error_Code_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Code_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Code_quals[] =
{
    &OMI_Error_error_Code_Description_qual,
};

/* property OMI_Error.error_Code */
static MI_CONST MI_PropertyDecl OMI_Error_error_Code_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650A, /* code */
    MI_T("error_Code"), /* name */
    OMI_Error_error_Code_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Code_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Code), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_Error_error_Type_Description_qual_value = MI_T("The name of the error type, for example : 'HRESULT' or 'MI_RESULT' or 'Win32'");

static MI_CONST MI_Qualifier OMI_Error_error_Type_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Type_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Type_quals[] =
{
    &OMI_Error_error_Type_Description_qual,
};

/* property OMI_Error.error_Type */
static MI_CONST MI_PropertyDecl OMI_Error_error_Type_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650A, /* code */
    MI_T("error_Type"), /* name */
    OMI_Error_error_Type_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Type_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Type), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_Error_error_Category_Description_qual_value = MI_T("An enumeration corresponding to the category enum in MI.h");

static MI_CONST MI_Qualifier OMI_Error_error_Category_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Category_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_error_Category_Values_qual_data_value[] =
{
    MI_T("MI_ERRORCATEGORY_NOT_SPECIFIED"),
    MI_T("MI_ERRORCATEGORY_OPEN_ERROR"),
    MI_T("MI_ERRORCATEGORY_CLOSE_EERROR"),
    MI_T("MI_ERRORCATEGORY_DEVICE_ERROR"),
    MI_T("MI_ERRORCATEGORY_DEADLOCK_DETECTED"),
    MI_T("MI_ERRORCATEGORY_INVALID_ARGUMENT"),
    MI_T("MI_ERRORCATEGORY_INVALID_DATA"),
    MI_T("MI_ERRORCATEGORY_INVALID_OPERATION"),
    MI_T("MI_ERRORCATEGORY_INVALID_RESULT"),
    MI_T("MI_ERRORCATEGORY_INVALID_TYPE"),
    MI_T("MI_ERRORCATEGORY_METADATA_ERROR"),
    MI_T("MI_ERRORCATEGORY_NOT_IMPLEMENTED"),
    MI_T("MI_ERRORCATEGORY_NOT_INSTALLED"),
    MI_T("MI_ERRORCATEGORY_OBJECT_NOT_FOUND"),
    MI_T("MI_ERRORCATEGORY_OPERATION_STOPPED"),
    MI_T("MI_ERRORCATEGORY_OPERATION_TIMEOUT"),
    MI_T("MI_ERRORCATEGORY_SYNTAX_ERROR"),
    MI_T("MI_ERRORCATEGORY_PARSER_ERROR"),
    MI_T("MI_ERRORCATEGORY_ACCESS_DENIED"),
    MI_T("MI_ERRORCATEGORY_RESOURCE_BUSY"),
    MI_T("MI_ERRORCATEGORY_RESOURCE_EXISTS"),
    MI_T("MI_ERRORCATEGORY_RESOURCE_UNAVAILABLE"),
    MI_T("MI_ERRORCATEGORY_READ_ERROR"),
    MI_T("MI_ERRORCATEGORY_WRITE_ERROR"),
    MI_T("MI_ERRORCATEGORY_FROM_STDERR"),
    MI_T("MI_ERRORCATEGORY_SECURITY_ERROR"),
    MI_T("MI_ERRORCATEGORY_PROTOCOL_ERROR"),
    MI_T("MI_ERRORCATEGORY_CONNECTION_ERROR"),
    MI_T("MI_ERRORCATEGORY_AUTHENTICATION_ERROR"),
    MI_T("MI_ERRORCATEGORY_LIMITS_EXCEEDED"),
    MI_T("MI_ERRORCATEGORY_QUOTA_EXCEEDED"),
    MI_T("MI_ERRORCATEGORY_NOT_ENABLED"),
};

static MI_CONST MI_ConstStringA OMI_Error_error_Category_Values_qual_value =
{
    OMI_Error_error_Category_Values_qual_data_value,
    MI_COUNT(OMI_Error_error_Category_Values_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_Error_error_Category_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Category_Values_qual_value
};

static MI_CONST MI_Char* OMI_Error_error_Category_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T("30"),
    MI_T("31"),
};

static MI_CONST MI_ConstStringA OMI_Error_error_Category_ValueMap_qual_value =
{
    OMI_Error_error_Category_ValueMap_qual_data_value,
    MI_COUNT(OMI_Error_error_Category_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_Error_error_Category_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_error_Category_ValueMap_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Category_quals[] =
{
    &OMI_Error_error_Category_Description_qual,
    &OMI_Error_error_Category_Values_qual,
    &OMI_Error_error_Category_ValueMap_qual,
};

/* property OMI_Error.error_Category */
static MI_CONST MI_PropertyDecl OMI_Error_error_Category_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065790E, /* code */
    MI_T("error_Category"), /* name */
    OMI_Error_error_Category_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Category_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Category), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
    &OMI_Error_error_Code_prop,
    &OMI_Error_error_Type_prop,
    &OMI_Error_error_Category_prop,
};

static MI_CONST MI_Boolean OMI_Error_Indication_qual_value = 1;

static MI_CONST MI_Qualifier OMI_Error_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_Indication_qual_value
};

static MI_CONST MI_Boolean OMI_Error_Exception_qual_value = 1;

static MI_CONST MI_Qualifier OMI_Error_Exception_qual =
{
    MI_T("Exception"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_Exception_qual_value
};

static MI_CONST MI_Char* OMI_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier OMI_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* OMI_Error_Description_qual_value = MI_T("OMI_Error is a class used to report errors in the OMI infrastructure and components built on that infrastructure.");

static MI_CONST MI_Qualifier OMI_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_Version_qual_value = MI_T("2.22.1");

static MI_CONST MI_Qualifier OMI_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &OMI_Error_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_quals[] =
{
    &OMI_Error_Indication_qual,
    &OMI_Error_Exception_qual,
    &OMI_Error_UMLPackagePath_qual,
    &OMI_Error_Description_qual,
    &OMI_Error_Version_qual,
};

/* class OMI_Error */
MI_CONST MI_ClassDecl OMI_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006F7209, /* code */
    MI_T("OMI_Error"), /* name */
    OMI_Error_quals, /* qualifiers */
    MI_COUNT(OMI_Error_quals), /* numQualifiers */
    OMI_Error_props, /* properties */
    MI_COUNT(OMI_Error_props), /* numProperties */
    sizeof(OMI_Error), /* size */
    MI_T("CIM_Error"), /* superClass */
    &CIM_Error_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** OMI_DebugError
**
**==============================================================================
*/

/* property OMI_DebugError.OMI_BackTrace */
static MI_CONST MI_PropertyDecl OMI_DebugError_OMI_BackTrace_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F650D, /* code */
    MI_T("OMI_BackTrace"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_DebugError, OMI_BackTrace), /* offset */
    MI_T("OMI_DebugError"), /* origin */
    MI_T("OMI_DebugError"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_DebugError_inner_Error_EmbeddedObject_qual_value = 1;

static MI_CONST MI_Qualifier OMI_DebugError_inner_Error_EmbeddedObject_qual =
{
    MI_T("EmbeddedObject"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_DebugError_inner_Error_EmbeddedObject_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_DebugError_inner_Error_quals[] =
{
    &OMI_DebugError_inner_Error_EmbeddedObject_qual,
};

/* property OMI_DebugError.inner_Error */
static MI_CONST MI_PropertyDecl OMI_DebugError_inner_Error_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0069720B, /* code */
    MI_T("inner_Error"), /* name */
    OMI_DebugError_inner_Error_quals, /* qualifiers */
    MI_COUNT(OMI_DebugError_inner_Error_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_DebugError, inner_Error), /* offset */
    MI_T("OMI_DebugError"), /* origin */
    MI_T("OMI_DebugError"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_DebugError_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
    &OMI_Error_error_Code_prop,
    &OMI_Error_error_Type_prop,
    &OMI_Error_error_Category_prop,
    &OMI_DebugError_OMI_BackTrace_prop,
    &OMI_DebugError_inner_Error_prop,
};

static MI_CONST MI_Boolean OMI_DebugError_Indication_qual_value = 1;

static MI_CONST MI_Qualifier OMI_DebugError_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_DebugError_Indication_qual_value
};

static MI_CONST MI_Boolean OMI_DebugError_Exception_qual_value = 1;

static MI_CONST MI_Qualifier OMI_DebugError_Exception_qual =
{
    MI_T("Exception"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_DebugError_Exception_qual_value
};

static MI_CONST MI_Char* OMI_DebugError_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier OMI_DebugError_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_DebugError_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* OMI_DebugError_Description_qual_value = MI_T("Instances of OMI_DebugError contain information about interpretercontinuation stack that can be used to pinpoint the line of codethat failed, and the context it failed in.");

static MI_CONST MI_Qualifier OMI_DebugError_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_DebugError_Description_qual_value
};

static MI_CONST MI_Char* OMI_DebugError_Version_qual_value = MI_T("2.22.1");

static MI_CONST MI_Qualifier OMI_DebugError_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &OMI_DebugError_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_DebugError_quals[] =
{
    &OMI_DebugError_Indication_qual,
    &OMI_DebugError_Exception_qual,
    &OMI_DebugError_UMLPackagePath_qual,
    &OMI_DebugError_Description_qual,
    &OMI_DebugError_Version_qual,
};

/* class OMI_DebugError */
MI_CONST MI_ClassDecl OMI_DebugError_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006F720E, /* code */
    MI_T("OMI_DebugError"), /* name */
    OMI_DebugError_quals, /* qualifiers */
    MI_COUNT(OMI_DebugError_quals), /* numQualifiers */
    OMI_DebugError_props, /* properties */
    MI_COUNT(OMI_DebugError_props), /* numProperties */
    sizeof(OMI_DebugError), /* size */
    MI_T("OMI_Error"), /* superClass */
    &OMI_Error_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &CIM_Error_rtti,
    &OMI_DebugError_rtti,
    &OMI_Error_rtti,
};

MI_SchemaDecl schemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};
