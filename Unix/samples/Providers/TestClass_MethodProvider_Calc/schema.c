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
#include "TestClass_MethodProvider_Calc.h"
#include "Numbers.h"
#include "NumbersTask.h"
#include "CIM_Error.h"

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

static MI_CONST MI_Boolean Abstract_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Abstract_qual_decl =
{
    MI_T("Abstract"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    &Abstract_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Aggregate_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Aggregate_qual_decl =
{
    MI_T("Aggregate"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Aggregate_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Aggregation_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Aggregation_qual_decl =
{
    MI_T("Aggregation"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Aggregation_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Alias_qual_decl =
{
    MI_T("Alias"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Char* ArrayType_qual_decl_value = MI_T("Bag");

static MI_CONST MI_QualifierDecl ArrayType_qual_decl =
{
    MI_T("ArrayType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &ArrayType_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Association_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Association_qual_decl =
{
    MI_T("Association"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Association_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl BitMap_qual_decl =
{
    MI_T("BitMap"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl BitValues_qual_decl =
{
    MI_T("BitValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ClassConstraint_qual_decl =
{
    MI_T("ClassConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Composition_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Composition_qual_decl =
{
    MI_T("Composition"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Composition_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Correlatable_qual_decl =
{
    MI_T("Correlatable"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Counter_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Counter_qual_decl =
{
    MI_T("Counter"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Counter_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Delete_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Delete_qual_decl =
{
    MI_T("Delete"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Delete_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Deprecated_qual_decl =
{
    MI_T("Deprecated"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Description_qual_decl =
{
    MI_T("Description"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl DisplayDescription_qual_decl =
{
    MI_T("DisplayDescription"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl DisplayName_qual_decl =
{
    MI_T("DisplayName"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean DN_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl DN_qual_decl =
{
    MI_T("DN"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &DN_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl EmbeddedInstance_qual_decl =
{
    MI_T("EmbeddedInstance"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean EmbeddedObject_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl EmbeddedObject_qual_decl =
{
    MI_T("EmbeddedObject"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &EmbeddedObject_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Exception_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Exception_qual_decl =
{
    MI_T("Exception"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Exception_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Expensive_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Expensive_qual_decl =
{
    MI_T("Expensive"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Expensive_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Experimental_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Experimental_qual_decl =
{
    MI_T("Experimental"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    &Experimental_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Gauge_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Gauge_qual_decl =
{
    MI_T("Gauge"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Gauge_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Ifdeleted_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Ifdeleted_qual_decl =
{
    MI_T("Ifdeleted"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Ifdeleted_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean In_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl In_qual_decl =
{
    MI_T("In"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &In_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Indication_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Indication_qual_decl =
{
    MI_T("Indication"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Indication_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Invisible_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Invisible_qual_decl =
{
    MI_T("Invisible"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Invisible_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean IsPUnit_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl IsPUnit_qual_decl =
{
    MI_T("IsPUnit"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &IsPUnit_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Key_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Key_qual_decl =
{
    MI_T("Key"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Key_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Large_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Large_qual_decl =
{
    MI_T("Large"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Large_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MappingStrings_qual_decl =
{
    MI_T("MappingStrings"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Max_qual_decl =
{
    MI_T("Max"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxLen_qual_decl =
{
    MI_T("MaxLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxValue_qual_decl =
{
    MI_T("MaxValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MethodConstraint_qual_decl =
{
    MI_T("MethodConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Uint32 Min_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl Min_qual_decl =
{
    MI_T("Min"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Min_qual_decl_value, /* value */
};

static MI_CONST MI_Uint32 MinLen_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl MinLen_qual_decl =
{
    MI_T("MinLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &MinLen_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MinValue_qual_decl =
{
    MI_T("MinValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ModelCorrespondence_qual_decl =
{
    MI_T("ModelCorrespondence"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Nonlocal_qual_decl =
{
    MI_T("Nonlocal"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl NonlocalType_qual_decl =
{
    MI_T("NonlocalType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl NullValue_qual_decl =
{
    MI_T("NullValue"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Octetstring_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Octetstring_qual_decl =
{
    MI_T("Octetstring"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Octetstring_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Out_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Out_qual_decl =
{
    MI_T("Out"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Out_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Override_qual_decl =
{
    MI_T("Override"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Propagated_qual_decl =
{
    MI_T("Propagated"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl PropertyConstraint_qual_decl =
{
    MI_T("PropertyConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Char* PropertyUsage_qual_decl_value = MI_T("CurrentContext");

static MI_CONST MI_QualifierDecl PropertyUsage_qual_decl =
{
    MI_T("PropertyUsage"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &PropertyUsage_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Provider_qual_decl =
{
    MI_T("Provider"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl PUnit_qual_decl =
{
    MI_T("PUnit"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Read_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl Read_qual_decl =
{
    MI_T("Read"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Read_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Required_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Required_qual_decl =
{
    MI_T("Required"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Required_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Revision_qual_decl =
{
    MI_T("Revision"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Schema_qual_decl =
{
    MI_T("Schema"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Source_qual_decl =
{
    MI_T("Source"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SourceType_qual_decl =
{
    MI_T("SourceType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Static_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Static_qual_decl =
{
    MI_T("Static"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Static_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Stream_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Stream_qual_decl =
{
    MI_T("Stream"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Stream_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Syntax_qual_decl =
{
    MI_T("Syntax"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SyntaxType_qual_decl =
{
    MI_T("SyntaxType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Terminal_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Terminal_qual_decl =
{
    MI_T("Terminal"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Terminal_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl TriggerType_qual_decl =
{
    MI_T("TriggerType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UMLPackagePath_qual_decl =
{
    MI_T("UMLPackagePath"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Units_qual_decl =
{
    MI_T("Units"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UnknownValues_qual_decl =
{
    MI_T("UnknownValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UnsupportedValues_qual_decl =
{
    MI_T("UnsupportedValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ValueMap_qual_decl =
{
    MI_T("ValueMap"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Values_qual_decl =
{
    MI_T("Values"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Version_qual_decl =
{
    MI_T("Version"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Weak_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Weak_qual_decl =
{
    MI_T("Weak"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Weak_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Write_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Write_qual_decl =
{
    MI_T("Write"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Write_qual_decl_value, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &Abstract_qual_decl,
    &Aggregate_qual_decl,
    &Aggregation_qual_decl,
    &Alias_qual_decl,
    &ArrayType_qual_decl,
    &Association_qual_decl,
    &BitMap_qual_decl,
    &BitValues_qual_decl,
    &ClassConstraint_qual_decl,
    &Composition_qual_decl,
    &Correlatable_qual_decl,
    &Counter_qual_decl,
    &Delete_qual_decl,
    &Deprecated_qual_decl,
    &Description_qual_decl,
    &DisplayDescription_qual_decl,
    &DisplayName_qual_decl,
    &DN_qual_decl,
    &EmbeddedInstance_qual_decl,
    &EmbeddedObject_qual_decl,
    &Exception_qual_decl,
    &Expensive_qual_decl,
    &Experimental_qual_decl,
    &Gauge_qual_decl,
    &Ifdeleted_qual_decl,
    &In_qual_decl,
    &Indication_qual_decl,
    &Invisible_qual_decl,
    &IsPUnit_qual_decl,
    &Key_qual_decl,
    &Large_qual_decl,
    &MappingStrings_qual_decl,
    &Max_qual_decl,
    &MaxLen_qual_decl,
    &MaxValue_qual_decl,
    &MethodConstraint_qual_decl,
    &Min_qual_decl,
    &MinLen_qual_decl,
    &MinValue_qual_decl,
    &ModelCorrespondence_qual_decl,
    &Nonlocal_qual_decl,
    &NonlocalType_qual_decl,
    &NullValue_qual_decl,
    &Octetstring_qual_decl,
    &Out_qual_decl,
    &Override_qual_decl,
    &Propagated_qual_decl,
    &PropertyConstraint_qual_decl,
    &PropertyUsage_qual_decl,
    &Provider_qual_decl,
    &PUnit_qual_decl,
    &Read_qual_decl,
    &Required_qual_decl,
    &Revision_qual_decl,
    &Schema_qual_decl,
    &Source_qual_decl,
    &SourceType_qual_decl,
    &Static_qual_decl,
    &Stream_qual_decl,
    &Syntax_qual_decl,
    &SyntaxType_qual_decl,
    &Terminal_qual_decl,
    &TriggerType_qual_decl,
    &UMLPackagePath_qual_decl,
    &Units_qual_decl,
    &UnknownValues_qual_decl,
    &UnsupportedValues_qual_decl,
    &ValueMap_qual_decl,
    &Values_qual_decl,
    &Version_qual_decl,
    &Weak_qual_decl,
    &Write_qual_decl,
};

/*
**==============================================================================
**
** Numbers
**
**==============================================================================
*/

/* property Numbers.numbers */
static MI_CONST MI_PropertyDecl Numbers_numbers_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7307, /* code */
    MI_T("numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Numbers, numbers), /* offset */
    MI_T("Numbers"), /* origin */
    MI_T("Numbers"), /* propagator */
    NULL,
};

/* property Numbers.count */
static MI_CONST MI_PropertyDecl Numbers_count_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637405, /* code */
    MI_T("count"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Numbers, count), /* offset */
    MI_T("Numbers"), /* origin */
    MI_T("Numbers"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Numbers_props[] =
{
    &Numbers_numbers_prop,
    &Numbers_count_prop,
};

static MI_CONST MI_ProviderFT Numbers_funcs =
{
  (MI_ProviderFT_Load)Numbers_Load,
  (MI_ProviderFT_Unload)Numbers_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Numbers */
MI_CONST MI_ClassDecl Numbers_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006E7307, /* code */
    MI_T("Numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Numbers_props, /* properties */
    MI_COUNT(Numbers_props), /* numProperties */
    sizeof(Numbers), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Numbers_funcs, /* functions */
};

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc
**
**==============================================================================
*/


/* parameter TestClass_MethodProvider_Calc.Add(): Left */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Add_Left_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Add, Left), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Add(): Right */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Add_Right_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Add, Right), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Add(): sum */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Add_sum_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736D03, /* code */
    MI_T("sum"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Add, sum), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Add(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Add_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Add, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Add_params[] =
{
    &TestClass_MethodProvider_Calc_Add_MIReturn_param,
    &TestClass_MethodProvider_Calc_Add_Left_param,
    &TestClass_MethodProvider_Calc_Add_Right_param,
    &TestClass_MethodProvider_Calc_Add_sum_param,
};

/* method TestClass_MethodProvider_Calc.Add() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Add_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00616403, /* code */
    MI_T("Add"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_MethodProvider_Calc_Add_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_Add_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_Add), /* size */
    MI_UINT64, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_Add, /* method */
};

static MI_CONST MI_Sint64 TestClass_MethodProvider_Calc_Subtract_MaxValue_qual_value = MI_LL(65535);

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Subtract_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &TestClass_MethodProvider_Calc_Subtract_MaxValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Subtract_quals[] =
{
    &TestClass_MethodProvider_Calc_Subtract_MaxValue_qual,
};

/* parameter TestClass_MethodProvider_Calc.Subtract(): Left */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Subtract_Left_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Subtract, Left), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Subtract(): Right */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Subtract_Right_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Subtract, Right), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Subtract(): difference */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Subtract_difference_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0064650A, /* code */
    MI_T("difference"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Subtract, difference), /* offset */
};

static MI_CONST MI_Sint64 TestClass_MethodProvider_Calc_Subtract_MIReturn_MaxValue_qual_value = MI_LL(65535);

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Subtract_MIReturn_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &TestClass_MethodProvider_Calc_Subtract_MIReturn_MaxValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Subtract_MIReturn_quals[] =
{
    &TestClass_MethodProvider_Calc_Subtract_MIReturn_MaxValue_qual,
};

/* parameter TestClass_MethodProvider_Calc.Subtract(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Subtract_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TestClass_MethodProvider_Calc_Subtract_MIReturn_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Subtract_MIReturn_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Subtract, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Subtract_params[] =
{
    &TestClass_MethodProvider_Calc_Subtract_MIReturn_param,
    &TestClass_MethodProvider_Calc_Subtract_Left_param,
    &TestClass_MethodProvider_Calc_Subtract_Right_param,
    &TestClass_MethodProvider_Calc_Subtract_difference_param,
};

/* method TestClass_MethodProvider_Calc.Subtract() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Subtract_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00737408, /* code */
    MI_T("Subtract"), /* name */
    TestClass_MethodProvider_Calc_Subtract_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Subtract_quals), /* numQualifiers */
    TestClass_MethodProvider_Calc_Subtract_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_Subtract_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_Subtract), /* size */
    MI_SINT64, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_Subtract, /* method */
};

static MI_CONST MI_Sint64 TestClass_MethodProvider_Calc_Divide_Numerator_MaxValue_qual_value = MI_LL(9223372036854775807);

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Divide_Numerator_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &TestClass_MethodProvider_Calc_Divide_Numerator_MaxValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Divide_Numerator_quals[] =
{
    &TestClass_MethodProvider_Calc_Divide_Numerator_MaxValue_qual,
};

/* parameter TestClass_MethodProvider_Calc.Divide(): Numerator */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Divide_Numerator_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E7209, /* code */
    MI_T("Numerator"), /* name */
    TestClass_MethodProvider_Calc_Divide_Numerator_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Divide_Numerator_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Divide, Numerator), /* offset */
};

static MI_CONST MI_Sint64 TestClass_MethodProvider_Calc_Divide_Denominator_MinValue_qual_value = MI_LL(1);

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Divide_Denominator_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &TestClass_MethodProvider_Calc_Divide_Denominator_MinValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Divide_Denominator_quals[] =
{
    &TestClass_MethodProvider_Calc_Divide_Denominator_MinValue_qual,
};

/* parameter TestClass_MethodProvider_Calc.Divide(): Denominator */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Divide_Denominator_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064720B, /* code */
    MI_T("Denominator"), /* name */
    TestClass_MethodProvider_Calc_Divide_Denominator_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Divide_Denominator_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Divide, Denominator), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Divide(): quotient */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Divide_quotient_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00717408, /* code */
    MI_T("quotient"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Divide, quotient), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Divide(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Divide_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Divide, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Divide_params[] =
{
    &TestClass_MethodProvider_Calc_Divide_MIReturn_param,
    &TestClass_MethodProvider_Calc_Divide_Numerator_param,
    &TestClass_MethodProvider_Calc_Divide_Denominator_param,
    &TestClass_MethodProvider_Calc_Divide_quotient_param,
};

/* method TestClass_MethodProvider_Calc.Divide() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Divide_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00646506, /* code */
    MI_T("Divide"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_MethodProvider_Calc_Divide_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_Divide_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_Divide), /* size */
    MI_SINT64, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_Divide, /* method */
};

static MI_CONST MI_Char* TestClass_MethodProvider_Calc_Multiply_DisplayName_qual_value = MI_T("1");

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Multiply_DisplayName_qual =
{
    MI_T("DisplayName"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TestClass_MethodProvider_Calc_Multiply_DisplayName_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Multiply_quals[] =
{
    &TestClass_MethodProvider_Calc_Multiply_DisplayName_qual,
};

/* parameter TestClass_MethodProvider_Calc.Multiply(): Left */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Multiply_Left_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Multiply, Left), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Multiply(): Right */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Multiply_Right_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Multiply, Right), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.Multiply(): product */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Multiply_product_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00707407, /* code */
    MI_T("product"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Multiply, product), /* offset */
};

static MI_CONST MI_Char* TestClass_MethodProvider_Calc_Multiply_MIReturn_DisplayName_qual_value = MI_T("1");

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_Multiply_MIReturn_DisplayName_qual =
{
    MI_T("DisplayName"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TestClass_MethodProvider_Calc_Multiply_MIReturn_DisplayName_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Multiply_MIReturn_quals[] =
{
    &TestClass_MethodProvider_Calc_Multiply_MIReturn_DisplayName_qual,
};

/* parameter TestClass_MethodProvider_Calc.Multiply(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_Multiply_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TestClass_MethodProvider_Calc_Multiply_MIReturn_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Multiply_MIReturn_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_Multiply, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_Multiply_params[] =
{
    &TestClass_MethodProvider_Calc_Multiply_MIReturn_param,
    &TestClass_MethodProvider_Calc_Multiply_Left_param,
    &TestClass_MethodProvider_Calc_Multiply_Right_param,
    &TestClass_MethodProvider_Calc_Multiply_product_param,
};

/* method TestClass_MethodProvider_Calc.Multiply() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Multiply_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x006D7908, /* code */
    MI_T("Multiply"), /* name */
    TestClass_MethodProvider_Calc_Multiply_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_Multiply_quals), /* numQualifiers */
    TestClass_MethodProvider_Calc_Multiply_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_Multiply_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_Multiply), /* size */
    MI_UINT64, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_Multiply, /* method */
};

static MI_CONST MI_Char* TestClass_MethodProvider_Calc_AddNumbers_numbers_EmbeddedInstance_qual_value = MI_T("Numbers");

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_AddNumbers_numbers_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_MethodProvider_Calc_AddNumbers_numbers_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_AddNumbers_numbers_quals[] =
{
    &TestClass_MethodProvider_Calc_AddNumbers_numbers_EmbeddedInstance_qual,
};

/* parameter TestClass_MethodProvider_Calc.AddNumbers(): numbers */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_AddNumbers_numbers_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x006E7307, /* code */
    MI_T("numbers"), /* name */
    TestClass_MethodProvider_Calc_AddNumbers_numbers_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_AddNumbers_numbers_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Numbers"), /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_AddNumbers, numbers), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.AddNumbers(): sum */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_AddNumbers_sum_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736D03, /* code */
    MI_T("sum"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_AddNumbers, sum), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.AddNumbers(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_AddNumbers_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_AddNumbers, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_AddNumbers_params[] =
{
    &TestClass_MethodProvider_Calc_AddNumbers_MIReturn_param,
    &TestClass_MethodProvider_Calc_AddNumbers_numbers_param,
    &TestClass_MethodProvider_Calc_AddNumbers_sum_param,
};

/* method TestClass_MethodProvider_Calc.AddNumbers() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_AddNumbers_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0061730A, /* code */
    MI_T("AddNumbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_MethodProvider_Calc_AddNumbers_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_AddNumbers_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_AddNumbers), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_AddNumbers, /* method */
};

/* parameter TestClass_MethodProvider_Calc.PrimeFactors(): number */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_PrimeFactors_number_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_PrimeFactors, number), /* offset */
};

static MI_CONST MI_Char* TestClass_MethodProvider_Calc_PrimeFactors_factors_EmbeddedInstance_qual_value = MI_T("Numbers");

static MI_CONST MI_Qualifier TestClass_MethodProvider_Calc_PrimeFactors_factors_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_MethodProvider_Calc_PrimeFactors_factors_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_MethodProvider_Calc_PrimeFactors_factors_quals[] =
{
    &TestClass_MethodProvider_Calc_PrimeFactors_factors_EmbeddedInstance_qual,
};

/* parameter TestClass_MethodProvider_Calc.PrimeFactors(): factors */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_PrimeFactors_factors_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00667307, /* code */
    MI_T("factors"), /* name */
    TestClass_MethodProvider_Calc_PrimeFactors_factors_quals, /* qualifiers */
    MI_COUNT(TestClass_MethodProvider_Calc_PrimeFactors_factors_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Numbers"), /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_PrimeFactors, factors), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.PrimeFactors(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_PrimeFactors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_PrimeFactors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_PrimeFactors_params[] =
{
    &TestClass_MethodProvider_Calc_PrimeFactors_MIReturn_param,
    &TestClass_MethodProvider_Calc_PrimeFactors_number_param,
    &TestClass_MethodProvider_Calc_PrimeFactors_factors_param,
};

/* method TestClass_MethodProvider_Calc.PrimeFactors() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_PrimeFactors_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0070730C, /* code */
    MI_T("PrimeFactors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_MethodProvider_Calc_PrimeFactors_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_PrimeFactors_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_PrimeFactors), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_PrimeFactors, /* method */
};

/* parameter TestClass_MethodProvider_Calc.HardError(): postError */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_HardError_postError_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707209, /* code */
    MI_T("postError"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_HardError, postError), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.HardError(): perceivedSeverity */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_HardError_perceivedSeverity_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707911, /* code */
    MI_T("perceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_HardError, perceivedSeverity), /* offset */
};

/* parameter TestClass_MethodProvider_Calc.HardError(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_MethodProvider_Calc_HardError_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_MethodProvider_Calc_HardError, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_HardError_params[] =
{
    &TestClass_MethodProvider_Calc_HardError_MIReturn_param,
    &TestClass_MethodProvider_Calc_HardError_postError_param,
    &TestClass_MethodProvider_Calc_HardError_perceivedSeverity_param,
};

/* method TestClass_MethodProvider_Calc.HardError() */
MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_HardError_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00687209, /* code */
    MI_T("HardError"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_MethodProvider_Calc_HardError_params, /* parameters */
    MI_COUNT(TestClass_MethodProvider_Calc_HardError_params), /* numParameters */
    sizeof(TestClass_MethodProvider_Calc_HardError), /* size */
    MI_UINT64, /* returnType */
    MI_T("TestClass_MethodProvider_Calc"), /* origin */
    MI_T("TestClass_MethodProvider_Calc"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_MethodProvider_Calc_Invoke_HardError, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TestClass_MethodProvider_Calc_meths[] =
{
    &TestClass_MethodProvider_Calc_Add_rtti,
    &TestClass_MethodProvider_Calc_Subtract_rtti,
    &TestClass_MethodProvider_Calc_Divide_rtti,
    &TestClass_MethodProvider_Calc_Multiply_rtti,
    &TestClass_MethodProvider_Calc_AddNumbers_rtti,
    &TestClass_MethodProvider_Calc_PrimeFactors_rtti,
    &TestClass_MethodProvider_Calc_HardError_rtti,
};

static MI_CONST MI_ProviderFT TestClass_MethodProvider_Calc_funcs =
{
  (MI_ProviderFT_Load)TestClass_MethodProvider_Calc_Load,
  (MI_ProviderFT_Unload)TestClass_MethodProvider_Calc_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class TestClass_MethodProvider_Calc */
MI_CONST MI_ClassDecl TestClass_MethodProvider_Calc_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074631D, /* code */
    MI_T("TestClass_MethodProvider_Calc"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(TestClass_MethodProvider_Calc), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    TestClass_MethodProvider_Calc_meths, /* methods */
    MI_COUNT(TestClass_MethodProvider_Calc_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TestClass_MethodProvider_Calc_funcs, /* functions */
};

/*
**==============================================================================
**
** NumbersTask
**
**==============================================================================
*/


/* parameter NumbersTask.NewNumber(): newDigits */
static MI_CONST MI_ParameterDecl NumbersTask_NewNumber_newDigits_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E7309, /* code */
    MI_T("newDigits"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(NumbersTask_NewNumber, newDigits), /* offset */
};

static MI_CONST MI_Char* NumbersTask_NewNumber_newNum_EmbeddedInstance_qual_value = MI_T("Numbers");

static MI_CONST MI_Qualifier NumbersTask_NewNumber_newNum_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &NumbersTask_NewNumber_newNum_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST NumbersTask_NewNumber_newNum_quals[] =
{
    &NumbersTask_NewNumber_newNum_EmbeddedInstance_qual,
};

/* parameter NumbersTask.NewNumber(): newNum */
static MI_CONST MI_ParameterDecl NumbersTask_NewNumber_newNum_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006E6D06, /* code */
    MI_T("newNum"), /* name */
    NumbersTask_NewNumber_newNum_quals, /* qualifiers */
    MI_COUNT(NumbersTask_NewNumber_newNum_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Numbers"), /* className */
    0, /* subscript */
    offsetof(NumbersTask_NewNumber, newNum), /* offset */
};

/* parameter NumbersTask.NewNumber(): MIReturn */
static MI_CONST MI_ParameterDecl NumbersTask_NewNumber_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(NumbersTask_NewNumber, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST NumbersTask_NewNumber_params[] =
{
    &NumbersTask_NewNumber_MIReturn_param,
    &NumbersTask_NewNumber_newDigits_param,
    &NumbersTask_NewNumber_newNum_param,
};

/* method NumbersTask.NewNumber() */
MI_CONST MI_MethodDecl NumbersTask_NewNumber_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x006E7209, /* code */
    MI_T("NewNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NumbersTask_NewNumber_params, /* parameters */
    MI_COUNT(NumbersTask_NewNumber_params), /* numParameters */
    sizeof(NumbersTask_NewNumber), /* size */
    MI_UINT32, /* returnType */
    MI_T("NumbersTask"), /* origin */
    MI_T("NumbersTask"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)NumbersTask_Invoke_NewNumber, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST NumbersTask_meths[] =
{
    &NumbersTask_NewNumber_rtti,
};

static MI_CONST MI_ProviderFT NumbersTask_funcs =
{
  (MI_ProviderFT_Load)NumbersTask_Load,
  (MI_ProviderFT_Unload)NumbersTask_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class NumbersTask */
MI_CONST MI_ClassDecl NumbersTask_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006E6B0B, /* code */
    MI_T("NumbersTask"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(NumbersTask), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NumbersTask_meths, /* methods */
    MI_COUNT(NumbersTask_meths), /* numMethods */
    &schemaDecl, /* schema */
    &NumbersTask_funcs, /* functions */
};

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

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
    0,
    &CIM_Error_ErrorType_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_Values_qual_data_value[] =
{
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
    0,
    &CIM_Error_ErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorType_quals[] =
{
    &CIM_Error_ErrorType_ValueMap_qual,
    &CIM_Error_ErrorType_Values_qual,
    &CIM_Error_ErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorType_quals[] =
{
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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

/* property CIM_Error.OwningEntity */
static MI_CONST MI_PropertyDecl CIM_Error_OwningEntity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790C, /* code */
    MI_T("OwningEntity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OwningEntity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
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
    0,
    &CIM_Error_MessageID_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageID_quals[] =
{
    &CIM_Error_MessageID_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageID */
static MI_CONST MI_PropertyDecl CIM_Error_MessageID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
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
    0,
    &CIM_Error_Message_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_Message_quals[] =
{
    &CIM_Error_Message_ModelCorrespondence_qual,
};

/* property CIM_Error.Message */
static MI_CONST MI_PropertyDecl CIM_Error_Message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageArguments_quals[] =
{
    &CIM_Error_MessageArguments_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageArguments */
static MI_CONST MI_PropertyDecl CIM_Error_MessageArguments_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_PerceivedSeverity_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Values_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("13"),
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
    &CIM_Error_PerceivedSeverity_ValueMap_qual,
    &CIM_Error_PerceivedSeverity_Values_qual,
};

/* property CIM_Error.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Error_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_ProbableCause_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_Values_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
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
    MI_T("6"),
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
    MI_T("131"),
    MI_T("132"),
    MI_T("133"),
    MI_T("134"),
    MI_T("135"),
    MI_T("136"),
    MI_T("137"),
    MI_T("138"),
    MI_T("139"),
    MI_T("140"),
    MI_T("141"),
    MI_T("142"),
    MI_T("143"),
    MI_T("144"),
    MI_T("145"),
    MI_T("146"),
    MI_T("147"),
    MI_T("13"),
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
    0,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCause_quals[] =
{
    &CIM_Error_ProbableCause_ValueMap_qual,
    &CIM_Error_ProbableCause_Values_qual,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCause */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCause_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCauseDescription_quals[] =
{
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCauseDescription */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCauseDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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

/* property CIM_Error.RecommendedActions */
static MI_CONST MI_PropertyDecl CIM_Error_RecommendedActions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727312, /* code */
    MI_T("RecommendedActions"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, RecommendedActions), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
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
    0,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSource_quals[] =
{
    &CIM_Error_ErrorSource_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorSource */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSource_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_ErrorSourceFormat_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Values_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("148"),
    MI_T("13"),
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
    0,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSourceFormat_quals[] =
{
    &CIM_Error_ErrorSourceFormat_ValueMap_qual,
    &CIM_Error_ErrorSourceFormat_Values_qual,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_Error_ErrorSourceFormat_value = 0;

/* property CIM_Error.ErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorSourceFormat_quals[] =
{
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_CIMStatusCode_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Values_qual_data_value[] =
{
    MI_T("149"),
    MI_T("150"),
    MI_T("151"),
    MI_T("152"),
    MI_T("153"),
    MI_T("154"),
    MI_T("155"),
    MI_T("156"),
    MI_T("157"),
    MI_T("158"),
    MI_T("159"),
    MI_T("160"),
    MI_T("161"),
    MI_T("162"),
    MI_T("163"),
    MI_T("164"),
    MI_T("165"),
    MI_T("166"),
    MI_T("167"),
    MI_T("168"),
    MI_T("169"),
    MI_T("170"),
    MI_T("171"),
    MI_T("172"),
    MI_T("173"),
    MI_T("174"),
    MI_T("175"),
    MI_T("176"),
    MI_T("177"),
    MI_T("13"),
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
    0,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCode_quals[] =
{
    &CIM_Error_CIMStatusCode_ValueMap_qual,
    &CIM_Error_CIMStatusCode_Values_qual,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCode */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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
    0,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCodeDescription_quals[] =
{
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCodeDescription */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCodeDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
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

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("178");

static MI_CONST MI_Qualifier CIM_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Error_Version_qual_value
};

static MI_CONST MI_Char* CIM_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Error_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_quals[] =
{
    &CIM_Error_Version_qual,
    &CIM_Error_UMLPackagePath_qual,
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
    &CIM_Error_rtti,
    &Numbers_rtti,
    &NumbersTask_rtti,
    &TestClass_MethodProvider_Calc_rtti,
};

MI_SchemaDecl schemaDecl =
{
    qualifierDecls, /* qualifierDecls */
    MI_COUNT(qualifierDecls), /* numQualifierDecls */
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

