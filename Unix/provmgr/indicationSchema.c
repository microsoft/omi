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
#include "CIM_Indication.h"
#include "CIM_InstCreation.h"
#include "CIM_InstDeletion.h"
#include "CIM_InstIndication.h"
#include "CIM_InstMethodCall.h"
#include "CIM_InstModification.h"
#include "CIM_InstRead.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl indicationSchemaDecl;

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
** CIM_Indication
**
**==============================================================================
*/

/* property CIM_Indication.IndicationIdentifier */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationIdentifier_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697214, /* code */
    MI_T("IndicationIdentifier"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationIdentifier), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.CorrelatedIndications */
static MI_CONST MI_PropertyDecl CIM_Indication_CorrelatedIndications_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637315, /* code */
    MI_T("CorrelatedIndications"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, CorrelatedIndications), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationTime */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650E, /* code */
    MI_T("IndicationTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationTime), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, PerceivedSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.OtherSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_OtherSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790D, /* code */
    MI_T("OtherSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, OtherSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationFilterName */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationFilterName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696514, /* code */
    MI_T("IndicationFilterName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationFilterName), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceContext */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceContext_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740F, /* code */
    MI_T("SequenceContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceContext), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceNumber */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720E, /* code */
    MI_T("SequenceNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceNumber), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
};

static MI_CONST MI_Char* CIM_Indication_Version_qual_value = MI_T("2.24.0");

static MI_CONST MI_Qualifier CIM_Indication_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Indication_Version_qual_value
};

static MI_CONST MI_Char* CIM_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_quals[] =
{
    &CIM_Indication_Version_qual,
    &CIM_Indication_UMLPackagePath_qual,
};

/* class CIM_Indication */
MI_CONST MI_ClassDecl CIM_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x00636E0E, /* code */
    MI_T("CIM_Indication"), /* name */
    (struct _MI_Qualifier**)CIM_Indication_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_quals), /* numQualifiers */
    (struct _MI_PropertyDecl**)CIM_Indication_props, /* properties */
    MI_COUNT(CIM_Indication_props), /* numProperties */
    sizeof(CIM_Indication), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstIndication
**
**==============================================================================
*/

/* property CIM_InstIndication.SourceInstance */
static MI_CONST MI_PropertyDecl CIM_InstIndication_SourceInstance_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x0073650E, /* code */
    MI_T("SourceInstance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstIndication, SourceInstance), /* offset */
    MI_T("CIM_InstIndication"), /* origin */
    MI_T("CIM_InstIndication"), /* propagator */
    NULL,
};

/* property CIM_InstIndication.SourceInstanceModelPath */
static MI_CONST MI_PropertyDecl CIM_InstIndication_SourceInstanceModelPath_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736817, /* code */
    MI_T("SourceInstanceModelPath"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstIndication, SourceInstanceModelPath), /* offset */
    MI_T("CIM_InstIndication"), /* origin */
    MI_T("CIM_InstIndication"), /* propagator */
    NULL,
};

/* property CIM_InstIndication.SourceInstanceHost */
static MI_CONST MI_PropertyDecl CIM_InstIndication_SourceInstanceHost_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737412, /* code */
    MI_T("SourceInstanceHost"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstIndication, SourceInstanceHost), /* offset */
    MI_T("CIM_InstIndication"), /* origin */
    MI_T("CIM_InstIndication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstIndication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
};

static MI_CONST MI_Char* CIM_InstIndication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstIndication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstIndication_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstIndication_Version_qual_value = MI_T("2.29.0");

static MI_CONST MI_Qualifier CIM_InstIndication_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstIndication_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstIndication_quals[] =
{
    &CIM_InstIndication_UMLPackagePath_qual,
    &CIM_InstIndication_Version_qual,
};

/* class CIM_InstIndication */
MI_CONST MI_ClassDecl CIM_InstIndication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x00636E12, /* code */
    MI_T("CIM_InstIndication"), /* name */
	(struct _MI_Qualifier**)CIM_InstIndication_quals, /* qualifiers */
    MI_COUNT(CIM_InstIndication_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstIndication_props, /* properties */
    MI_COUNT(CIM_InstIndication_props), /* numProperties */
    sizeof(CIM_InstIndication), /* size */
    (MI_CONST MI_Char*)MI_T("CIM_Indication"), /* superClass */
    (MI_ClassDecl*)&CIM_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstCreation
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstCreation_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
};

static MI_CONST MI_Char* CIM_InstCreation_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstCreation_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstCreation_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstCreation_Version_qual_value = MI_T("2.27.0");

static MI_CONST MI_Qualifier CIM_InstCreation_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstCreation_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstCreation_quals[] =
{
    &CIM_InstCreation_UMLPackagePath_qual,
    &CIM_InstCreation_Version_qual,
};

/* class CIM_InstCreation */
MI_CONST MI_ClassDecl CIM_InstCreation_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00636E10, /* code */
    MI_T("CIM_InstCreation"), /* name */
	(struct _MI_Qualifier**)CIM_InstCreation_quals, /* qualifiers */
    MI_COUNT(CIM_InstCreation_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstCreation_props, /* properties */
    MI_COUNT(CIM_InstCreation_props), /* numProperties */
    sizeof(CIM_InstCreation), /* size */
	(MI_CONST MI_Char*)MI_T("CIM_InstIndication"), /* superClass */
	(MI_ClassDecl*)&CIM_InstIndication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstDeletion
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstDeletion_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
};

static MI_CONST MI_Char* CIM_InstDeletion_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstDeletion_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstDeletion_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstDeletion_Version_qual_value = MI_T("2.27.0");

static MI_CONST MI_Qualifier CIM_InstDeletion_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstDeletion_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstDeletion_quals[] =
{
    &CIM_InstDeletion_UMLPackagePath_qual,
    &CIM_InstDeletion_Version_qual,
};

/* class CIM_InstDeletion */
MI_CONST MI_ClassDecl CIM_InstDeletion_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00636E10, /* code */
    MI_T("CIM_InstDeletion"), /* name */
	(struct _MI_Qualifier**)CIM_InstDeletion_quals, /* qualifiers */
    MI_COUNT(CIM_InstDeletion_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstDeletion_props, /* properties */
    MI_COUNT(CIM_InstDeletion_props), /* numProperties */
    sizeof(CIM_InstDeletion), /* size */
	(MI_CONST MI_Char*)MI_T("CIM_InstIndication"), /* superClass */
	(MI_ClassDecl*)&CIM_InstIndication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstMethodCall
**
**==============================================================================
*/

/* property CIM_InstMethodCall.MethodName */
static MI_CONST MI_PropertyDecl CIM_InstMethodCall_MethodName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006D650A, /* code */
    MI_T("MethodName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstMethodCall, MethodName), /* offset */
    MI_T("CIM_InstMethodCall"), /* origin */
    MI_T("CIM_InstMethodCall"), /* propagator */
    NULL,
};

/* property CIM_InstMethodCall.MethodParameters */
static MI_CONST MI_PropertyDecl CIM_InstMethodCall_MethodParameters_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D7310, /* code */
    MI_T("MethodParameters"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstMethodCall, MethodParameters), /* offset */
    MI_T("CIM_InstMethodCall"), /* origin */
    MI_T("CIM_InstMethodCall"), /* propagator */
    NULL,
};

/* property CIM_InstMethodCall.ReturnValue */
static MI_CONST MI_PropertyDecl CIM_InstMethodCall_ReturnValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("ReturnValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstMethodCall, ReturnValue), /* offset */
    MI_T("CIM_InstMethodCall"), /* origin */
    MI_T("CIM_InstMethodCall"), /* propagator */
    NULL,
};

/* property CIM_InstMethodCall.PreCall */
static MI_CONST MI_PropertyDecl CIM_InstMethodCall_PreCall_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00706C07, /* code */
    MI_T("PreCall"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstMethodCall, PreCall), /* offset */
    MI_T("CIM_InstMethodCall"), /* origin */
    MI_T("CIM_InstMethodCall"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstMethodCall_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
    &CIM_InstMethodCall_MethodName_prop,
    &CIM_InstMethodCall_MethodParameters_prop,
    &CIM_InstMethodCall_ReturnValue_prop,
    &CIM_InstMethodCall_PreCall_prop,
};

static MI_CONST MI_Char* CIM_InstMethodCall_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstMethodCall_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstMethodCall_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstMethodCall_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_InstMethodCall_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstMethodCall_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstMethodCall_quals[] =
{
    &CIM_InstMethodCall_UMLPackagePath_qual,
    &CIM_InstMethodCall_Version_qual,
};

/* class CIM_InstMethodCall */
MI_CONST MI_ClassDecl CIM_InstMethodCall_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00636C12, /* code */
    MI_T("CIM_InstMethodCall"), /* name */
	(struct _MI_Qualifier**)CIM_InstMethodCall_quals, /* qualifiers */
    MI_COUNT(CIM_InstMethodCall_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstMethodCall_props, /* properties */
    MI_COUNT(CIM_InstMethodCall_props), /* numProperties */
    sizeof(CIM_InstMethodCall), /* size */
	(MI_CONST MI_Char*)MI_T("CIM_InstIndication"), /* superClass */
	(MI_ClassDecl*)&CIM_InstIndication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstModification
**
**==============================================================================
*/

/* property CIM_InstModification.PreviousInstance */
static MI_CONST MI_PropertyDecl CIM_InstModification_PreviousInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706510, /* code */
    MI_T("PreviousInstance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstModification, PreviousInstance), /* offset */
    MI_T("CIM_InstModification"), /* origin */
    MI_T("CIM_InstModification"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstModification_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
    &CIM_InstModification_PreviousInstance_prop,
};

static MI_CONST MI_Char* CIM_InstModification_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstModification_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstModification_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstModification_Version_qual_value = MI_T("2.27.0");

static MI_CONST MI_Qualifier CIM_InstModification_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstModification_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstModification_quals[] =
{
    &CIM_InstModification_UMLPackagePath_qual,
    &CIM_InstModification_Version_qual,
};

/* class CIM_InstModification */
MI_CONST MI_ClassDecl CIM_InstModification_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00636E14, /* code */
    MI_T("CIM_InstModification"), /* name */
	(struct _MI_Qualifier**)CIM_InstModification_quals, /* qualifiers */
    MI_COUNT(CIM_InstModification_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstModification_props, /* properties */
    MI_COUNT(CIM_InstModification_props), /* numProperties */
    sizeof(CIM_InstModification), /* size */
	(MI_CONST MI_Char*)MI_T("CIM_InstIndication"), /* superClass */
	(MI_ClassDecl*)&CIM_InstIndication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstRead
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstRead_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &CIM_InstIndication_SourceInstance_prop,
    &CIM_InstIndication_SourceInstanceModelPath_prop,
    &CIM_InstIndication_SourceInstanceHost_prop,
};

static MI_CONST MI_Char* CIM_InstRead_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_InstRead_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstRead_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstRead_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_InstRead_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstRead_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstRead_quals[] =
{
    &CIM_InstRead_UMLPackagePath_qual,
    &CIM_InstRead_Version_qual,
};

/* class CIM_InstRead */
MI_CONST MI_ClassDecl CIM_InstRead_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x0063640C, /* code */
    MI_T("CIM_InstRead"), /* name */
	(struct _MI_Qualifier**)CIM_InstRead_quals, /* qualifiers */
    MI_COUNT(CIM_InstRead_quals), /* numQualifiers */
	(struct _MI_PropertyDecl**)CIM_InstRead_props, /* properties */
    MI_COUNT(CIM_InstRead_props), /* numProperties */
    sizeof(CIM_InstRead), /* size */
	(MI_CONST MI_Char*)MI_T("CIM_InstIndication"), /* superClass */
	(MI_ClassDecl*)&CIM_InstIndication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &indicationSchemaDecl, /* schema */
    NULL, /* functions */
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
    &CIM_Indication_rtti,
    &CIM_InstCreation_rtti,
    &CIM_InstDeletion_rtti,
    &CIM_InstIndication_rtti,
    &CIM_InstMethodCall_rtti,
    &CIM_InstModification_rtti,
    &CIM_InstRead_rtti,
};

MI_SchemaDecl indicationSchemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

