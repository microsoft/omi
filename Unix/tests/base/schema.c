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
#include "MSFT_Person.h"
#include "MSFT_AllTypes.h"
#include "MSFT_Process.h"
#include "Inner.h"
#include "Outer.h"
#include "Octet.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl test_repos_classDecl;

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
** MSFT_Person
**
**==============================================================================
*/

/* property MSFT_Person.Key */
static MI_CONST MI_PropertyDecl MSFT_Person_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Key), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.First */
static MI_CONST MI_PropertyDecl MSFT_Person_First_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667405, /* code */
    MI_T("First"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, First), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.Last */
static MI_CONST MI_PropertyDecl MSFT_Person_Last_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Last"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Last), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.Colors */
static MI_CONST MI_PropertyDecl MSFT_Person_Colors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637306, /* code */
    MI_T("Colors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Colors), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.Numbers */
static MI_CONST MI_PropertyDecl MSFT_Person_Numbers_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7307, /* code */
    MI_T("Numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Numbers), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.Nothing */
static MI_CONST MI_PropertyDecl MSFT_Person_Nothing_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6707, /* code */
    MI_T("Nothing"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Nothing), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Person_props[] =
{
    &MSFT_Person_Key_prop,
    &MSFT_Person_First_prop,
    &MSFT_Person_Last_prop,
    &MSFT_Person_Colors_prop,
    &MSFT_Person_Numbers_prop,
    &MSFT_Person_Nothing_prop,
};

/* class MSFT_Person */
MI_CONST MI_ClassDecl MSFT_Person_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6E0B, /* code */
    MI_T("MSFT_Person"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Person_props, /* properties */
    MI_COUNT(MSFT_Person_props), /* numProperties */
    sizeof(MSFT_Person), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** MSFT_AllTypes
**
**==============================================================================
*/

/* property MSFT_AllTypes.Key */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Key), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.BooleanValue */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_BooleanValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062650C, /* code */
    MI_T("BooleanValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, BooleanValue), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint8Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint8Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650A, /* code */
    MI_T("Uint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint8Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint8Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint8Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("Sint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint8Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint16Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("Uint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint16Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint16Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("Sint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint16Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint32Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("Uint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint32Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint32Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("Sint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint32Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint64Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("Uint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint64Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint64Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("Sint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint64Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Real32Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Real32Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("Real32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Real32Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Real64Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Real64Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("Real64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Real64Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Char16Value */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Char16Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650B, /* code */
    MI_T("Char16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Char16Value), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.TimestampValue */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_TimestampValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074650E, /* code */
    MI_T("TimestampValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, TimestampValue), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.IntervalValue */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_IntervalValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650D, /* code */
    MI_T("IntervalValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, IntervalValue), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.StringValue */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_StringValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650B, /* code */
    MI_T("StringValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, StringValue), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.BooleanArray */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_BooleanArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062790C, /* code */
    MI_T("BooleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, BooleanArray), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint8Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790A, /* code */
    MI_T("Uint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint8Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint8Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790A, /* code */
    MI_T("Sint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint8Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint16Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("Uint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint16Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint16Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("Sint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint16Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint32Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("Uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint32Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint32Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("Sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint32Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Uint64Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Uint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("Uint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Uint64Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Sint64Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Sint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("Sint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Sint64Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Real32Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Real32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("Real32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Real32Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Real64Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Real64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("Real64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Real64Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.Char16Array */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_Char16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063790B, /* code */
    MI_T("Char16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, Char16Array), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.DatetimeArray */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_DatetimeArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064790D, /* code */
    MI_T("DatetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, DatetimeArray), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

/* property MSFT_AllTypes.StringArray */
static MI_CONST MI_PropertyDecl MSFT_AllTypes_StringArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("StringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_AllTypes, StringArray), /* offset */
    MI_T("MSFT_AllTypes"), /* origin */
    MI_T("MSFT_AllTypes"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_AllTypes_props[] =
{
    &MSFT_AllTypes_Key_prop,
    &MSFT_AllTypes_BooleanValue_prop,
    &MSFT_AllTypes_Uint8Value_prop,
    &MSFT_AllTypes_Sint8Value_prop,
    &MSFT_AllTypes_Uint16Value_prop,
    &MSFT_AllTypes_Sint16Value_prop,
    &MSFT_AllTypes_Uint32Value_prop,
    &MSFT_AllTypes_Sint32Value_prop,
    &MSFT_AllTypes_Uint64Value_prop,
    &MSFT_AllTypes_Sint64Value_prop,
    &MSFT_AllTypes_Real32Value_prop,
    &MSFT_AllTypes_Real64Value_prop,
    &MSFT_AllTypes_Char16Value_prop,
    &MSFT_AllTypes_TimestampValue_prop,
    &MSFT_AllTypes_IntervalValue_prop,
    &MSFT_AllTypes_StringValue_prop,
    &MSFT_AllTypes_BooleanArray_prop,
    &MSFT_AllTypes_Uint8Array_prop,
    &MSFT_AllTypes_Sint8Array_prop,
    &MSFT_AllTypes_Uint16Array_prop,
    &MSFT_AllTypes_Sint16Array_prop,
    &MSFT_AllTypes_Uint32Array_prop,
    &MSFT_AllTypes_Sint32Array_prop,
    &MSFT_AllTypes_Uint64Array_prop,
    &MSFT_AllTypes_Sint64Array_prop,
    &MSFT_AllTypes_Real32Array_prop,
    &MSFT_AllTypes_Real64Array_prop,
    &MSFT_AllTypes_Char16Array_prop,
    &MSFT_AllTypes_DatetimeArray_prop,
    &MSFT_AllTypes_StringArray_prop,
};

/* class MSFT_AllTypes */
MI_CONST MI_ClassDecl MSFT_AllTypes_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D730D, /* code */
    MI_T("MSFT_AllTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_AllTypes_props, /* properties */
    MI_COUNT(MSFT_AllTypes_props), /* numProperties */
    sizeof(MSFT_AllTypes), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_ManagedElement
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ManagedElement_InstanceID_Description_qual_value = MI_T("InstanceID is an optional property that may be used to opaquely and uniquely identify an instance of this class within the scope of the instantiating Namespace. Various subclasses of this class may override this property to make it required, or a key. Such subclasses may also modify the preferred algorithms for ensuring uniqueness that are defined below.\nTo ensure uniqueness within the NameSpace, the value of InstanceID should be constructed using the following \"preferred\" algorithm: \n<OrgID>:<LocalID> \nWhere <OrgID> and <LocalID> are separated by a colon (:), and where <OrgID> must include a copyrighted, trademarked, or otherwise unique name that is owned by the business entity that is creating or defining the InstanceID or that is a registered ID assigned to the business entity by a recognized global authority. (This requirement is similar to the <Schema Name>_<Class Name> structure of Schema class names.) In addition, to ensure uniqueness, <OrgID> must not contain a colon (:). When using this algorithm, the first colon to appear in InstanceID must appear between <OrgID> and <LocalID>. \n<LocalID> is chosen by the business entity and should not be reused to identify different underlying (real-world) elements. If not null and the above \"preferred\" algorithm is not used, the defining entity must assure that the resulting InstanceID is not reused across any InstanceIDs produced by this or other providers for the NameSpace of this instance. \nIf not set to null for DMTF-defined instances, the \"preferred\" algorithm must be used with the <OrgID> set to CIM.");

static MI_CONST MI_Qualifier CIM_ManagedElement_InstanceID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedElement_InstanceID_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_InstanceID_quals[] =
{
    &CIM_ManagedElement_InstanceID_Description_qual,
};

/* property CIM_ManagedElement.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_InstanceID_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_ManagedElement_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedElement_Caption_Description_qual_value = MI_T("The Caption property is a short textual description (one- line string) of the object.");

static MI_CONST MI_Qualifier CIM_ManagedElement_Caption_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedElement_Caption_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_ManagedElement_Caption_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_ManagedElement_Caption_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedElement_Caption_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_Caption_quals[] =
{
    &CIM_ManagedElement_Caption_Description_qual,
    &CIM_ManagedElement_Caption_MaxLen_qual,
};

/* property CIM_ManagedElement.Caption */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Caption_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E07, /* code */
    MI_T("Caption"), /* name */
    CIM_ManagedElement_Caption_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_Caption_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Caption), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedElement_Description_Description_qual_value = MI_T("The Description property provides a textual description of the object.");

static MI_CONST MI_Qualifier CIM_ManagedElement_Description_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedElement_Description_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_Description_quals[] =
{
    &CIM_ManagedElement_Description_Description_qual,
};

/* property CIM_ManagedElement.Description */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    CIM_ManagedElement_Description_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_Description_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Description), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedElement_ElementName_Description_qual_value = MI_T("A user-friendly name for the object. This property allows each instance to define a user-friendly name in addition to its key properties, identity data, and description information. \nNote that the Name property of ManagedSystemElement is also defined as a user-friendly name. But, it is often subclassed to be a Key. It is not reasonable that the same property can convey both identity and a user-friendly name, without inconsistencies. Where Name exists and is not a Key (such as for instances of LogicalDevice), the same information can be present in both the Name and ElementName properties. Note that if there is an associated instance of CIM_EnabledLogicalElementCapabilities, restrictions on this properties may exist as defined in ElementNameMask and MaxElementNameLen properties defined in that class.");

static MI_CONST MI_Qualifier CIM_ManagedElement_ElementName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedElement_ElementName_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_ElementName_quals[] =
{
    &CIM_ManagedElement_ElementName_Description_qual,
};

/* property CIM_ManagedElement.ElementName */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_ElementName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    CIM_ManagedElement_ElementName_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_ElementName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_ManagedElement_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_ManagedElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedElement_Version_qual_value
};

static MI_CONST MI_Char* CIM_ManagedElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ManagedElement_Description_qual_value = MI_T("ManagedElement is an abstract class that provides a common superclass (or top of the inheritance tree) for the non-association classes in the CIM Schema.");

static MI_CONST MI_Qualifier CIM_ManagedElement_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedElement_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_quals[] =
{
    &CIM_ManagedElement_Version_qual,
    &CIM_ManagedElement_UMLPackagePath_qual,
    &CIM_ManagedElement_Description_qual,
};

/* class CIM_ManagedElement */
MI_CONST MI_ClassDecl CIM_ManagedElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_ManagedElement"), /* name */
    CIM_ManagedElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_quals), /* numQualifiers */
    CIM_ManagedElement_props, /* properties */
    MI_COUNT(CIM_ManagedElement_props), /* numProperties */
    sizeof(CIM_ManagedElement), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_ManagedSystemElement
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ManagedSystemElement_InstallDate_Description_qual_value = MI_T("A datetime value that indicates when the object was installed. Lack of a value does not indicate that the object is not installed.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_InstallDate_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_InstallDate_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_InstallDate_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|ComponentID|001.5"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_InstallDate_MappingStrings_qual_value =
{
    CIM_ManagedSystemElement_InstallDate_MappingStrings_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_InstallDate_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_InstallDate_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_InstallDate_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_InstallDate_quals[] =
{
    &CIM_ManagedSystemElement_InstallDate_Description_qual,
    &CIM_ManagedSystemElement_InstallDate_MappingStrings_qual,
};

/* property CIM_ManagedSystemElement.InstallDate */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_InstallDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650B, /* code */
    MI_T("InstallDate"), /* name */
    CIM_ManagedSystemElement_InstallDate_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_InstallDate_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, InstallDate), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Name_Description_qual_value = MI_T("The Name property defines the label by which the object is known. When subclassed, the Name property can be overridden to be a Key property.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Name_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_Name_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Name_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Name_quals[] =
{
    &CIM_ManagedSystemElement_Name_Description_qual,
    &CIM_ManagedSystemElement_Name_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Name */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ManagedSystemElement_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_Description_qual_value = MI_T("Indicates the current statuses of the element. Various operational statuses are defined. Many of the enumeration\'s values are self-explanatory. However, a few are not and are described here in more detail. \n\"Stressed\" indicates that the element is functioning, but needs attention. Examples of \"Stressed\" states are overload, overheated, and so on. \n\"Predictive Failure\" indicates that an element is functioning nominally but predicting a failure in the near future. \n\"In Service\" describes an element being configured, maintained, cleaned, or otherwise administered. \n\"No Contact\" indicates that the monitoring system has knowledge of this element, but has never been able to establish communications with it. \n\"Lost Communication\" indicates that the ManagedSystem Element is known to exist and has been contacted successfully in the past, but is currently unreachable. \n\"Stopped\" and \"Aborted\" are similar, although the former implies a clean and orderly stop, while the latter implies an abrupt stop where the state and configuration of the element might need to be updated. \n\"Dormant\" indicates that the element is inactive or quiesced. \n\"Supporting Entity in Error\" indicates that this element might be \"OK\" but that another element, on which it is dependent, is in error. An example is a network service or endpoint that cannot function due to lower-layer networking problems. \n\"Completed\" indicates that the element has completed its operation. This value should be combined with either OK, Error, or Degraded so that a client can tell if the complete operation Completed with OK (passed), Completed with Error (failed), or Completed with Degraded (the operation finished, but it did not complete OK or did not report an error). \n\"Power Mode\" indicates that the element has additional power model information contained in the Associated PowerManagementService association. \nOperationalStatus replaces the Status property on ManagedSystemElement to provide a consistent approach to enumerations, to address implementation needs for an array property, and to provide a migration path from today\'s environment to the future. This change was not made earlier because it required the deprecated qualifier. Due to the widespread use of the existing Status property in management applications, it is strongly recommended that providers or instrumentation provide both the Status and OperationalStatus properties. Further, the first value of OperationalStatus should contain the primary status for the element. When instrumented, Status (because it is single-valued) should also provide the primary status of the element.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_OperationalStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual_data_value[] =
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
    MI_T(".."),
    MI_T("0x8000.."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("OK"),
    MI_T("Degraded"),
    MI_T("Stressed"),
    MI_T("Predictive Failure"),
    MI_T("Error"),
    MI_T("Non-Recoverable Error"),
    MI_T("Starting"),
    MI_T("Stopping"),
    MI_T("Stopped"),
    MI_T("In Service"),
    MI_T("No Contact"),
    MI_T("Lost Communication"),
    MI_T("Aborted"),
    MI_T("Dormant"),
    MI_T("Supporting Entity in Error"),
    MI_T("Completed"),
    MI_T("Power Mode"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperationalStatus_Values_qual_value =
{
    CIM_ManagedSystemElement_OperationalStatus_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_OperationalStatus_Values_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.StatusDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_OperationalStatus_quals[] =
{
    &CIM_ManagedSystemElement_OperationalStatus_Description_qual,
    &CIM_ManagedSystemElement_OperationalStatus_ValueMap_qual,
    &CIM_ManagedSystemElement_OperationalStatus_Values_qual,
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual,
    &CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.OperationalStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperationalStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7311, /* code */
    MI_T("OperationalStatus"), /* name */
    CIM_ManagedSystemElement_OperationalStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperationalStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_Description_qual_value = MI_T("Strings describing the various OperationalStatus array values. For example, if \"Stopping\" is the value assigned to OperationalStatus, then this property may contain an explanation as to why an object is being stopped. Note that entries in this array are correlated with those at the same array index in OperationalStatus.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_StatusDescriptions_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_StatusDescriptions_quals[] =
{
    &CIM_ManagedSystemElement_StatusDescriptions_Description_qual,
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual,
    &CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.StatusDescriptions */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_StatusDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737312, /* code */
    MI_T("StatusDescriptions"), /* name */
    CIM_ManagedSystemElement_StatusDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_StatusDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, StatusDescriptions), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Status_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_Status_Deprecated_qual_value =
{
    CIM_ManagedSystemElement_Status_Deprecated_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_Status_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Status_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Status_Description_qual_value = MI_T("A string indicating the current status of the object. Various operational and non-operational statuses are defined. This property is deprecated in lieu of OperationalStatus, which includes the same semantics in its enumeration. This change is made for 3 reasons: \n1) Status is more correctly defined as an array. This definition overcomes the limitation of describing status using a single value, when it is really a multi-valued property (for example, an element might be OK AND Stopped. \n2) A MaxLen of 10 is too restrictive and leads to unclear enumerated values. \n3) The change to a uint16 data type was discussed when CIM V2.0 was defined. However, existing V1.0 implementations used the string property and did not want to modify their code. Therefore, Status was grandfathered into the Schema. Use of the deprecated qualifier allows the maintenance of the existing property, but also permits an improved definition using OperationalStatus.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_Status_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Status_ValueMap_qual_data_value[] =
{
    MI_T("OK"),
    MI_T("Error"),
    MI_T("Degraded"),
    MI_T("Unknown"),
    MI_T("Pred Fail"),
    MI_T("Starting"),
    MI_T("Stopping"),
    MI_T("Service"),
    MI_T("Stressed"),
    MI_T("NonRecover"),
    MI_T("No Contact"),
    MI_T("Lost Comm"),
    MI_T("Stopped"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_Status_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_Status_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_Status_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_Status_ValueMap_qual_value
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Status_MaxLen_qual_value = 10U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Status_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Status_quals[] =
{
    &CIM_ManagedSystemElement_Status_Deprecated_qual,
    &CIM_ManagedSystemElement_Status_Description_qual,
    &CIM_ManagedSystemElement_Status_ValueMap_qual,
    &CIM_ManagedSystemElement_Status_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Status */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Status_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737306, /* code */
    MI_T("Status"), /* name */
    CIM_ManagedSystemElement_Status_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Status_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Status), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_HealthState_Description_qual_value = MI_T("Indicates the current health of the element. This attribute expresses the health of this element but not necessarily that of its subcomponents. The possible values are 0 to 30, where 5 means the element is entirely healthy and 30 means the element is completely non-functional. The following continuum is defined: \n\"Non-recoverable Error\" (30) - The element has completely failed, and recovery is not possible. All functionality provided by this element has been lost. \n\"Critical Failure\" (25) - The element is non-functional and recovery might not be possible. \n\"Major Failure\" (20) - The element is failing. It is possible that some or all of the functionality of this component is degraded or not working. \n\"Minor Failure\" (15) - All functionality is available but some might be degraded. \n\"Degraded/Warning\" (10) - The element is in working order and all functionality is provided. However, the element is not working to the best of its abilities. For example, the element might not be operating at optimal performance or it might be reporting recoverable errors. \n\"OK\" (5) - The element is fully functional and is operating within normal operational parameters and without error. \n\"Unknown\" (0) - The implementation cannot report on HealthState at this time. \nDMTF has reserved the unused portion of the continuum for additional HealthStates in the future.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_HealthState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_HealthState_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_HealthState_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("5"),
    MI_T("10"),
    MI_T("15"),
    MI_T("20"),
    MI_T("25"),
    MI_T("30"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_HealthState_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_HealthState_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_HealthState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_HealthState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_HealthState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_HealthState_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("OK"),
    MI_T("Degraded/Warning"),
    MI_T("Minor failure"),
    MI_T("Major failure"),
    MI_T("Critical failure"),
    MI_T("Non-recoverable error"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_HealthState_Values_qual_value =
{
    CIM_ManagedSystemElement_HealthState_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_HealthState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_HealthState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_HealthState_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_HealthState_quals[] =
{
    &CIM_ManagedSystemElement_HealthState_Description_qual,
    &CIM_ManagedSystemElement_HealthState_ValueMap_qual,
    &CIM_ManagedSystemElement_HealthState_Values_qual,
};

/* property CIM_ManagedSystemElement.HealthState */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_HealthState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068650B, /* code */
    MI_T("HealthState"), /* name */
    CIM_ManagedSystemElement_HealthState_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_HealthState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, HealthState), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_CommunicationStatus_Description_qual_value = MI_T("CommunicationStatus indicates the ability of the instrumentation to communicate with the underlying ManagedElement. CommunicationStatus consists of one of the following values: Unknown, None, Communication OK, Lost Communication, or No Contact. \nA Null return indicates the implementation (provider) does not implement this property. \n\"Unknown\" indicates the implementation is in general capable of returning this property, but is unable to do so at this time. \n\"Not Available\" indicates that the implementation (provider) is capable of returning a value for this property, but not ever for this particular piece of hardware/software or the property is intentionally not used because it adds no meaningful information (as in the case of a property that is intended to add additional info to another property). \n\"Communication OK \" indicates communication is established with the element, but does not convey any quality of service. \n\"No Contact\" indicates that the monitoring system has knowledge of this element, but has never been able to establish communications with it. \n\"Lost Communication\" indicates that the Managed Element is known to exist and has been contacted successfully in the past, but is currently unreachable.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_CommunicationStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_CommunicationStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T(".."),
    MI_T("0x8000.."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_CommunicationStatus_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Not Available"),
    MI_T("Communication OK"),
    MI_T("Lost Communication"),
    MI_T("No Contact"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_CommunicationStatus_Values_qual_value =
{
    CIM_ManagedSystemElement_CommunicationStatus_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_CommunicationStatus_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_CommunicationStatus_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_CommunicationStatus_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_CommunicationStatus_quals[] =
{
    &CIM_ManagedSystemElement_CommunicationStatus_Description_qual,
    &CIM_ManagedSystemElement_CommunicationStatus_ValueMap_qual,
    &CIM_ManagedSystemElement_CommunicationStatus_Values_qual,
};

/* property CIM_ManagedSystemElement.CommunicationStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_CommunicationStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637313, /* code */
    MI_T("CommunicationStatus"), /* name */
    CIM_ManagedSystemElement_CommunicationStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_CommunicationStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, CommunicationStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_DetailedStatus_Description_qual_value = MI_T("DetailedStatus compliments PrimaryStatus with additional status detail. It consists of one of the following values: Not Available, No Additional Information, Stressed, Predictive Failure, Error, Non-Recoverable Error, SupportingEntityInError. Detailed status is used to expand upon the PrimaryStatus of the element. \nA Null return indicates the implementation (provider) does not implement this property. \n\"Not Available\" indicates that the implementation (provider) is capable of returning a value for this property, but not ever for this particular piece of hardware/software or the property is intentionally not used because it adds no meaningful information (as in the case of a property that is intended to add additional info to another property). \n\"No Additional Information\" indicates that the element is functioning normally as indicated by PrimaryStatus = \"OK\". \n\"Stressed\" indicates that the element is functioning, but needs attention. Examples of \"Stressed\" states are overload, overheated, and so on. \n\"Predictive Failure\" indicates that an element is functioning normally but a failure is predicted in the near future. \n\"Non-Recoverable Error \" indicates that this element is in an error condition that requires human intervention. \n\"Supporting Entity in Error\" indicates that this element might be \"OK\" but that another element, on which it is dependent, is in error. An example is a network service or endpoint that cannot function due to lower-layer networking problems.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_DetailedStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_DetailedStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T(".."),
    MI_T("0x8000.."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_DetailedStatus_Values_qual_data_value[] =
{
    MI_T("Not Available"),
    MI_T("No Additional Information"),
    MI_T("Stressed"),
    MI_T("Predictive Failure"),
    MI_T("Non-Recoverable Error"),
    MI_T("Supporting Entity in Error"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_DetailedStatus_Values_qual_value =
{
    CIM_ManagedSystemElement_DetailedStatus_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_DetailedStatus_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_DetailedStatus_Values_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.PrimaryStatus"),
    MI_T("CIM_ManagedSystemElement.HealthState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_DetailedStatus_quals[] =
{
    &CIM_ManagedSystemElement_DetailedStatus_Description_qual,
    &CIM_ManagedSystemElement_DetailedStatus_ValueMap_qual,
    &CIM_ManagedSystemElement_DetailedStatus_Values_qual,
    &CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.DetailedStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_DetailedStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064730E, /* code */
    MI_T("DetailedStatus"), /* name */
    CIM_ManagedSystemElement_DetailedStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, DetailedStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperatingStatus_Description_qual_value = MI_T("OperatingStatus provides a current status value for the operational condition of the element and can be used for providing more detail with respect to the value of EnabledState. It can also provide the transitional states when an element is transitioning from one state to another, such as when an element is transitioning between EnabledState and RequestedState, as well as other transitional conditions.\nOperatingStatus consists of one of the following values: Unknown, Not Available, In Service, Starting, Stopping, Stopped, Aborted, Dormant, Completed, Migrating, Emmigrating, Immigrating, Snapshotting. Shutting Down, In Test \nA Null return indicates the implementation (provider) does not implement this property. \n\"Unknown\" indicates the implementation is in general capable of returning this property, but is unable to do so at this time. \n\"None\" indicates that the implementation (provider) is capable of returning a value for this property, but not ever for this particular piece of hardware/software or the property is intentionally not used because it adds no meaningful information (as in the case of a property that is intended to add additional info to another property). \n\"Servicing\" describes an element being configured, maintained, cleaned, or otherwise administered. \n\"Starting\" describes an element being initialized. \n\"Stopping\" describes an element being brought to an orderly stop. \n\"Stopped\" and \"Aborted\" are similar, although the former implies a clean and orderly stop, while the latter implies an abrupt stop where the state and configuration of the element might need to be updated. \n\"Dormant\" indicates that the element is inactive or quiesced. \n\"Completed\" indicates that the element has completed its operation. This value should be combined with either OK, Error, or Degraded in the PrimaryStatus so that a client can tell if the complete operation Completed with OK (passed), Completed with Error (failed), or Completed with Degraded (the operation finished, but it did not complete OK or did not report an error). \n\"Migrating\" element is being moved between host elements. \n\"Immigrating\" element is being moved to new host element. \n\"Emigrating\" element is being moved away from host element. \n\"Shutting Down\" describes an element being brought to an abrupt stop. \n\"In Test\" element is performing test functions. \n\"Transitioning\" describes an element that is between states, that is, it is not fully available in either its previous state or its next state. This value should be used if other values indicating a transition to a specific state are not applicable.\n\"In Service\" describes an element that is in service and operational.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperatingStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_OperatingStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual_data_value[] =
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
    MI_T(".."),
    MI_T("0x8000.."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperatingStatus_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Not Available"),
    MI_T("Servicing"),
    MI_T("Starting"),
    MI_T("Stopping"),
    MI_T("Stopped"),
    MI_T("Aborted"),
    MI_T("Dormant"),
    MI_T("Completed"),
    MI_T("Migrating"),
    MI_T("Emigrating"),
    MI_T("Immigrating"),
    MI_T("Snapshotting"),
    MI_T("Shutting Down"),
    MI_T("In Test"),
    MI_T("Transitioning"),
    MI_T("In Service"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperatingStatus_Values_qual_value =
{
    CIM_ManagedSystemElement_OperatingStatus_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperatingStatus_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_OperatingStatus_Values_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_OperatingStatus_quals[] =
{
    &CIM_ManagedSystemElement_OperatingStatus_Description_qual,
    &CIM_ManagedSystemElement_OperatingStatus_ValueMap_qual,
    &CIM_ManagedSystemElement_OperatingStatus_Values_qual,
    &CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.OperatingStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperatingStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F730F, /* code */
    MI_T("OperatingStatus"), /* name */
    CIM_ManagedSystemElement_OperatingStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperatingStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_PrimaryStatus_Description_qual_value = MI_T("PrimaryStatus provides a high level status value, intended to align with Red-Yellow-Green type representation of status. It should be used in conjunction with DetailedStatus to provide high level and detailed health status of the ManagedElement and its subcomponents. \nPrimaryStatus consists of one of the following values: Unknown, OK, Degraded or Error. \"Unknown\" indicates the implementation is in general capable of returning this property, but is unable to do so at this time. \n\"OK\" indicates the ManagedElement is functioning normally. \n\"Degraded\" indicates the ManagedElement is functioning below normal. \n\"Error\" indicates the ManagedElement is in an Error condition.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_PrimaryStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_PrimaryStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T(".."),
    MI_T("0x8000.."),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual_value =
{
    CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_PrimaryStatus_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("OK"),
    MI_T("Degraded"),
    MI_T("Error"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_PrimaryStatus_Values_qual_value =
{
    CIM_ManagedSystemElement_PrimaryStatus_Values_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_PrimaryStatus_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_PrimaryStatus_Values_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.DetailedStatus"),
    MI_T("CIM_ManagedSystemElement.HealthState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_PrimaryStatus_quals[] =
{
    &CIM_ManagedSystemElement_PrimaryStatus_Description_qual,
    &CIM_ManagedSystemElement_PrimaryStatus_ValueMap_qual,
    &CIM_ManagedSystemElement_PrimaryStatus_Values_qual,
    &CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.PrimaryStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_PrimaryStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070730D, /* code */
    MI_T("PrimaryStatus"), /* name */
    CIM_ManagedSystemElement_PrimaryStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, PrimaryStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedSystemElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedSystemElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Description_qual_value = MI_T("CIM_ManagedSystemElement is the base class for the System Element hierarchy. Any distinguishable component of a System is a candidate for inclusion in this class. Examples of system components include: \n- software components such as application servers, databases, and applications \n- operating system components such as files, processes, and threads \n- device components such as disk drives, controllers, processors, and printers \n- physical components such as chips and cards.");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ManagedSystemElement_Description_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_quals[] =
{
    &CIM_ManagedSystemElement_UMLPackagePath_qual,
    &CIM_ManagedSystemElement_Description_qual,
    &CIM_ManagedSystemElement_Version_qual,
};

/* class CIM_ManagedSystemElement */
MI_CONST MI_ClassDecl CIM_ManagedSystemElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637418, /* code */
    MI_T("CIM_ManagedSystemElement"), /* name */
    CIM_ManagedSystemElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_quals), /* numQualifiers */
    CIM_ManagedSystemElement_props, /* properties */
    MI_COUNT(CIM_ManagedSystemElement_props), /* numProperties */
    sizeof(CIM_ManagedSystemElement), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_LogicalElement
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_LogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_LogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_LogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_LogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_LogicalElement_Description_qual_value = MI_T("CIM_LogicalElement is a base class for all the components of a System that represent abstract system components, such as Files, Processes, or LogicalDevices.");

static MI_CONST MI_Qualifier CIM_LogicalElement_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalElement_Description_qual_value
};

static MI_CONST MI_Char* CIM_LogicalElement_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_LogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_LogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalElement_quals[] =
{
    &CIM_LogicalElement_UMLPackagePath_qual,
    &CIM_LogicalElement_Description_qual,
    &CIM_LogicalElement_Version_qual,
};

/* class CIM_LogicalElement */
MI_CONST MI_ClassDecl CIM_LogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_LogicalElement"), /* name */
    CIM_LogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalElement_quals), /* numQualifiers */
    CIM_LogicalElement_props, /* properties */
    MI_COUNT(CIM_LogicalElement_props), /* numProperties */
    sizeof(CIM_LogicalElement), /* size */
    MI_T("CIM_ManagedSystemElement"), /* superClass */
    &CIM_ManagedSystemElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_Job
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Job_JobStatus_Description_qual_value = MI_T("A free-form string that represents the status of the job. The primary status is reflected in the inherited OperationalStatus property. JobStatus provides additional, implementation-specific details.");

static MI_CONST MI_Qualifier CIM_Job_JobStatus_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_JobStatus_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_JobStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_Job_JobStatus_ModelCorrespondence_qual_value =
{
    CIM_Job_JobStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_JobStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_JobStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_JobStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_JobStatus_quals[] =
{
    &CIM_Job_JobStatus_Description_qual,
    &CIM_Job_JobStatus_ModelCorrespondence_qual,
};

/* property CIM_Job.JobStatus */
static MI_CONST MI_PropertyDecl CIM_Job_JobStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A7309, /* code */
    MI_T("JobStatus"), /* name */
    CIM_Job_JobStatus_quals, /* qualifiers */
    MI_COUNT(CIM_Job_JobStatus_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobStatus), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_TimeSubmitted_Description_qual_value = MI_T("The time that the Job was submitted to execute. A value of all zeroes indicates that the owning element is not capable of reporting a date and time. Therefore, the ScheduledStartTime and StartTime are reported as intervals relative to the time their values are requested.");

static MI_CONST MI_Qualifier CIM_Job_TimeSubmitted_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_TimeSubmitted_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_TimeSubmitted_quals[] =
{
    &CIM_Job_TimeSubmitted_Description_qual,
};

/* property CIM_Job.TimeSubmitted */
static MI_CONST MI_PropertyDecl CIM_Job_TimeSubmitted_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074640D, /* code */
    MI_T("TimeSubmitted"), /* name */
    CIM_Job_TimeSubmitted_quals, /* qualifiers */
    MI_COUNT(CIM_Job_TimeSubmitted_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, TimeSubmitted), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ScheduledStartTime_Deprecated_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_ScheduledStartTime_Deprecated_qual_value =
{
    CIM_Job_ScheduledStartTime_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_ScheduledStartTime_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ScheduledStartTime_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_ScheduledStartTime_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_Job_ScheduledStartTime_Description_qual_value = MI_T("The time that the current Job is scheduled to start. This time can be represented by the actual date and time, or an interval relative to the time that this property is requested. A value of all zeroes indicates that the Job is already executing. The property is deprecated in lieu of the more expressive scheduling properties, RunMonth, RunDay, RunDayOfWeek, and RunStartInterval.");

static MI_CONST MI_Qualifier CIM_Job_ScheduledStartTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_ScheduledStartTime_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ScheduledStartTime_quals[] =
{
    &CIM_Job_ScheduledStartTime_Deprecated_qual,
    &CIM_Job_ScheduledStartTime_Description_qual,
};

/* property CIM_Job.ScheduledStartTime */
static MI_CONST MI_PropertyDecl CIM_Job_ScheduledStartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736512, /* code */
    MI_T("ScheduledStartTime"), /* name */
    CIM_Job_ScheduledStartTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ScheduledStartTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ScheduledStartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_StartTime_Description_qual_value = MI_T("The time that the Job was actually started. This time can be represented by an actual date and time, or by an interval relative to the time that this property is requested. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the processing information for recurring Jobs, because only the \'last\' run time can be stored in this single-valued property.");

static MI_CONST MI_Qualifier CIM_Job_StartTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_StartTime_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_StartTime_quals[] =
{
    &CIM_Job_StartTime_Description_qual,
};

/* property CIM_Job.StartTime */
static MI_CONST MI_PropertyDecl CIM_Job_StartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736509, /* code */
    MI_T("StartTime"), /* name */
    CIM_Job_StartTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_StartTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, StartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ElapsedTime_Description_qual_value = MI_T("The time interval that the Job has been executing or the total execution time if the Job is complete. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the processing information for recurring Jobs, because only the \'last\' run time can be stored in this single-valued property.");

static MI_CONST MI_Qualifier CIM_Job_ElapsedTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_ElapsedTime_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ElapsedTime_quals[] =
{
    &CIM_Job_ElapsedTime_Description_qual,
};

/* property CIM_Job.ElapsedTime */
static MI_CONST MI_PropertyDecl CIM_Job_ElapsedTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElapsedTime"), /* name */
    CIM_Job_ElapsedTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ElapsedTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ElapsedTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_JobRunTimes_Description_qual_value = MI_T("The number of times that the Job should be run. A value of 1 indicates that the Job is not recurring, while any non-zero value indicates a limit to the number of times that the Job will recur. Zero indicates that there is no limit to the number of times that the Job can be processed, but that it is terminated either after the UntilTime or by manual intervention. By default, a Job is processed once.");

static MI_CONST MI_Qualifier CIM_Job_JobRunTimes_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_JobRunTimes_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_JobRunTimes_quals[] =
{
    &CIM_Job_JobRunTimes_Description_qual,
};

static MI_CONST MI_Uint32 CIM_Job_JobRunTimes_value = 1U;

/* property CIM_Job.JobRunTimes */
static MI_CONST MI_PropertyDecl CIM_Job_JobRunTimes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A730B, /* code */
    MI_T("JobRunTimes"), /* name */
    CIM_Job_JobRunTimes_quals, /* qualifiers */
    MI_COUNT(CIM_Job_JobRunTimes_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobRunTimes), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &CIM_Job_JobRunTimes_value,
};

static MI_CONST MI_Char* CIM_Job_RunMonth_Description_qual_value = MI_T("The month during which the Job should be processed. Specify 0 for January, 1 for February, and so on.");

static MI_CONST MI_Qualifier CIM_Job_RunMonth_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunMonth_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunMonth_ValueMap_qual_data_value[] =
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
};

static MI_CONST MI_ConstStringA CIM_Job_RunMonth_ValueMap_qual_value =
{
    CIM_Job_RunMonth_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_RunMonth_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunMonth_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_RunMonth_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunMonth_Values_qual_data_value[] =
{
    MI_T("January"),
    MI_T("February"),
    MI_T("March"),
    MI_T("April"),
    MI_T("May"),
    MI_T("June"),
    MI_T("July"),
    MI_T("August"),
    MI_T("September"),
    MI_T("October"),
    MI_T("November"),
    MI_T("December"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunMonth_Values_qual_value =
{
    CIM_Job_RunMonth_Values_qual_data_value,
    MI_COUNT(CIM_Job_RunMonth_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunMonth_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunMonth_Values_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunMonth_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunMonth_ModelCorrespondence_qual_value =
{
    CIM_Job_RunMonth_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunMonth_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunMonth_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunMonth_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunMonth_quals[] =
{
    &CIM_Job_RunMonth_Description_qual,
    &CIM_Job_RunMonth_ValueMap_qual,
    &CIM_Job_RunMonth_Values_qual,
    &CIM_Job_RunMonth_ModelCorrespondence_qual,
};

/* property CIM_Job.RunMonth */
static MI_CONST MI_PropertyDecl CIM_Job_RunMonth_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726808, /* code */
    MI_T("RunMonth"), /* name */
    CIM_Job_RunMonth_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunMonth_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunMonth), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RunDay_Description_qual_value = MI_T("The day in the month on which the Job should be processed. There are two different interpretations for this property, depending on the value of DayOfWeek. In one case, RunDay defines the day-in-month on which the Job is processed. This interpretation is used when the DayOfWeek is 0. A positive or negative integer indicates whether the RunDay should be calculated from the beginning or end of the month. For example, 5 indicates the fifth day in the RunMonth and -1 indicates the last day in the RunMonth. \n\nWhen RunDayOfWeek is not 0, RunDay is the day-in-month on which the Job is processed, defined in conjunction with RunDayOfWeek. For example, if RunDay is 15 and RunDayOfWeek is Saturday, then the Job is processed on the first Saturday on or after the 15th day in the RunMonth (for example, the third Saturday in the month). If RunDay is 20 and RunDayOfWeek is -Saturday, then this indicates the first Saturday on or before the 20th day in the RunMonth. If RunDay is -1 and RunDayOfWeek is -Sunday, then this indicates the last Sunday in the RunMonth.");

static MI_CONST MI_Qualifier CIM_Job_RunDay_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunDay_Description_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MinValue_qual_value = -MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MaxValue_qual_value = MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunDay_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDay_ModelCorrespondence_qual_value =
{
    CIM_Job_RunDay_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunDay_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDay_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunDay_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunDay_quals[] =
{
    &CIM_Job_RunDay_Description_qual,
    &CIM_Job_RunDay_MinValue_qual,
    &CIM_Job_RunDay_MaxValue_qual,
    &CIM_Job_RunDay_ModelCorrespondence_qual,
};

/* property CIM_Job.RunDay */
static MI_CONST MI_PropertyDecl CIM_Job_RunDay_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727906, /* code */
    MI_T("RunDay"), /* name */
    CIM_Job_RunDay_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunDay_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDay), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RunDayOfWeek_Description_qual_value = MI_T("A positive or negative integer used in conjunction with RunDay to indicate the day of the week on which the Job is processed. RunDayOfWeek is set to 0 to indicate an exact day of the month, such as March 1. A positive integer (representing Sunday, Monday, ..., Saturday) means that the day of week is found on or after the specified RunDay. A negative integer (representing -Sunday, -Monday, ..., -Saturday) means that the day of week is found on or BEFORE the RunDay.");

static MI_CONST MI_Qualifier CIM_Job_RunDayOfWeek_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunDayOfWeek_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunDayOfWeek_ValueMap_qual_data_value[] =
{
    MI_T("-7"),
    MI_T("-6"),
    MI_T("-5"),
    MI_T("-4"),
    MI_T("-3"),
    MI_T("-2"),
    MI_T("-1"),
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDayOfWeek_ValueMap_qual_value =
{
    CIM_Job_RunDayOfWeek_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_RunDayOfWeek_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDayOfWeek_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_RunDayOfWeek_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunDayOfWeek_Values_qual_data_value[] =
{
    MI_T("-Saturday"),
    MI_T("-Friday"),
    MI_T("-Thursday"),
    MI_T("-Wednesday"),
    MI_T("-Tuesday"),
    MI_T("-Monday"),
    MI_T("-Sunday"),
    MI_T("ExactDayOfMonth"),
    MI_T("Sunday"),
    MI_T("Monday"),
    MI_T("Tuesday"),
    MI_T("Wednesday"),
    MI_T("Thursday"),
    MI_T("Friday"),
    MI_T("Saturday"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDayOfWeek_Values_qual_value =
{
    CIM_Job_RunDayOfWeek_Values_qual_data_value,
    MI_COUNT(CIM_Job_RunDayOfWeek_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDayOfWeek_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunDayOfWeek_Values_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_value =
{
    CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDayOfWeek_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunDayOfWeek_quals[] =
{
    &CIM_Job_RunDayOfWeek_Description_qual,
    &CIM_Job_RunDayOfWeek_ValueMap_qual,
    &CIM_Job_RunDayOfWeek_Values_qual,
    &CIM_Job_RunDayOfWeek_ModelCorrespondence_qual,
};

/* property CIM_Job.RunDayOfWeek */
static MI_CONST MI_PropertyDecl CIM_Job_RunDayOfWeek_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726B0C, /* code */
    MI_T("RunDayOfWeek"), /* name */
    CIM_Job_RunDayOfWeek_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunDayOfWeek_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDayOfWeek), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RunStartInterval_Description_qual_value = MI_T("The time interval after midnight when the Job should be processed. For example, \n00000000020000.000000:000 \nindicates that the Job should be run on or after two o\'clock, local time or UTC time (distinguished using the LocalOrUtcTime property.");

static MI_CONST MI_Qualifier CIM_Job_RunStartInterval_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RunStartInterval_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunStartInterval_ModelCorrespondence_qual_value =
{
    CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunStartInterval_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunStartInterval_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunStartInterval_quals[] =
{
    &CIM_Job_RunStartInterval_Description_qual,
    &CIM_Job_RunStartInterval_ModelCorrespondence_qual,
};

/* property CIM_Job.RunStartInterval */
static MI_CONST MI_PropertyDecl CIM_Job_RunStartInterval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726C10, /* code */
    MI_T("RunStartInterval"), /* name */
    CIM_Job_RunStartInterval_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunStartInterval_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunStartInterval), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_LocalOrUtcTime_Description_qual_value = MI_T("This property indicates whether the times represented in the RunStartInterval and UntilTime properties represent local times or UTC times. Time values are synchronized worldwide by using the enumeration value 2, \"UTC Time\".");

static MI_CONST MI_Qualifier CIM_Job_LocalOrUtcTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_LocalOrUtcTime_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_LocalOrUtcTime_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
};

static MI_CONST MI_ConstStringA CIM_Job_LocalOrUtcTime_ValueMap_qual_value =
{
    CIM_Job_LocalOrUtcTime_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_LocalOrUtcTime_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_LocalOrUtcTime_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_LocalOrUtcTime_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_LocalOrUtcTime_Values_qual_data_value[] =
{
    MI_T("Local Time"),
    MI_T("UTC Time"),
};

static MI_CONST MI_ConstStringA CIM_Job_LocalOrUtcTime_Values_qual_value =
{
    CIM_Job_LocalOrUtcTime_Values_qual_data_value,
    MI_COUNT(CIM_Job_LocalOrUtcTime_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_LocalOrUtcTime_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_LocalOrUtcTime_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_LocalOrUtcTime_quals[] =
{
    &CIM_Job_LocalOrUtcTime_Description_qual,
    &CIM_Job_LocalOrUtcTime_ValueMap_qual,
    &CIM_Job_LocalOrUtcTime_Values_qual,
};

/* property CIM_Job.LocalOrUtcTime */
static MI_CONST MI_PropertyDecl CIM_Job_LocalOrUtcTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C650E, /* code */
    MI_T("LocalOrUtcTime"), /* name */
    CIM_Job_LocalOrUtcTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_LocalOrUtcTime_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, LocalOrUtcTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_UntilTime_Description_qual_value = MI_T("The time after which the Job is invalid or should be stopped. This time can be represented by an actual date and time, or by an interval relative to the time that this property is requested. A value of all nines indicates that the Job can run indefinitely.");

static MI_CONST MI_Qualifier CIM_Job_UntilTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_UntilTime_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_UntilTime_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.LocalOrUtcTime"),
};

static MI_CONST MI_ConstStringA CIM_Job_UntilTime_ModelCorrespondence_qual_value =
{
    CIM_Job_UntilTime_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_UntilTime_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_UntilTime_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_UntilTime_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_UntilTime_quals[] =
{
    &CIM_Job_UntilTime_Description_qual,
    &CIM_Job_UntilTime_ModelCorrespondence_qual,
};

/* property CIM_Job.UntilTime */
static MI_CONST MI_PropertyDecl CIM_Job_UntilTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756509, /* code */
    MI_T("UntilTime"), /* name */
    CIM_Job_UntilTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_UntilTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, UntilTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_Notify_Description_qual_value = MI_T("The User who is to be notified upon the Job completion or failure.");

static MI_CONST MI_Qualifier CIM_Job_Notify_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_Notify_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_Notify_quals[] =
{
    &CIM_Job_Notify_Description_qual,
};

/* property CIM_Job.Notify */
static MI_CONST MI_PropertyDecl CIM_Job_Notify_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7906, /* code */
    MI_T("Notify"), /* name */
    CIM_Job_Notify_quals, /* qualifiers */
    MI_COUNT(CIM_Job_Notify_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Notify), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_Owner_Description_qual_value = MI_T("The User that submitted the Job, or the Service or method name that caused the job to be created.");

static MI_CONST MI_Qualifier CIM_Job_Owner_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_Owner_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_Owner_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_OwningJobElement"),
};

static MI_CONST MI_ConstStringA CIM_Job_Owner_ModelCorrespondence_qual_value =
{
    CIM_Job_Owner_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_Owner_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_Owner_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_Owner_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_Owner_quals[] =
{
    &CIM_Job_Owner_Description_qual,
    &CIM_Job_Owner_ModelCorrespondence_qual,
};

/* property CIM_Job.Owner */
static MI_CONST MI_PropertyDecl CIM_Job_Owner_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7205, /* code */
    MI_T("Owner"), /* name */
    CIM_Job_Owner_quals, /* qualifiers */
    MI_COUNT(CIM_Job_Owner_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Owner), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_Priority_Description_qual_value = MI_T("Indicates the urgency or importance of execution of the Job. The lower the number, the higher the priority. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the setting information that would influence the results of a job.");

static MI_CONST MI_Qualifier CIM_Job_Priority_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_Priority_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_Priority_quals[] =
{
    &CIM_Job_Priority_Description_qual,
};

/* property CIM_Job.Priority */
static MI_CONST MI_PropertyDecl CIM_Job_Priority_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Priority"), /* name */
    CIM_Job_Priority_quals, /* qualifiers */
    MI_COUNT(CIM_Job_Priority_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Priority), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_Description_qual_value = MI_T("The percentage of the job that has completed at the time that this value is requested. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the processing information for recurring Jobs, because only the \'last\' run data can be stored in this single-valued property. \nNote that the value 101 is undefined and will be not be allowed in the next major revision of the specification.");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_PercentComplete_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_Units_qual_value = MI_T("Percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_PercentComplete_Units_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MinValue_qual_value = MI_LL(0);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MaxValue_qual_value = MI_LL(101);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_PUnit_qual_value = MI_T("percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_Job_PercentComplete_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_PercentComplete_quals[] =
{
    &CIM_Job_PercentComplete_Description_qual,
    &CIM_Job_PercentComplete_Units_qual,
    &CIM_Job_PercentComplete_MinValue_qual,
    &CIM_Job_PercentComplete_MaxValue_qual,
    &CIM_Job_PercentComplete_PUnit_qual,
};

/* property CIM_Job.PercentComplete */
static MI_CONST MI_PropertyDecl CIM_Job_PercentComplete_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650F, /* code */
    MI_T("PercentComplete"), /* name */
    CIM_Job_PercentComplete_quals, /* qualifiers */
    MI_COUNT(CIM_Job_PercentComplete_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, PercentComplete), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_DeleteOnCompletion_Description_qual_value = MI_T("Indicates whether or not the job should be automatically deleted upon completion. Note that the \'completion\' of a recurring job is defined by its JobRunTimes or UntilTime properties, or when the Job is terminated by manual intervention. If this property is set to false and the job completes, then the extrinsic method DeleteInstance must be used to delete the job instead of updating this property.");

static MI_CONST MI_Qualifier CIM_Job_DeleteOnCompletion_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_DeleteOnCompletion_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_DeleteOnCompletion_quals[] =
{
    &CIM_Job_DeleteOnCompletion_Description_qual,
};

/* property CIM_Job.DeleteOnCompletion */
static MI_CONST MI_PropertyDecl CIM_Job_DeleteOnCompletion_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E12, /* code */
    MI_T("DeleteOnCompletion"), /* name */
    CIM_Job_DeleteOnCompletion_quals, /* qualifiers */
    MI_COUNT(CIM_Job_DeleteOnCompletion_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, DeleteOnCompletion), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ErrorCode_Description_qual_value = MI_T("A vendor-specific error code. The value must be set to zero if the Job completed without error. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the processing information for recurring Jobs, because only the \'last\' run error can be stored in this single-valued property.");

static MI_CONST MI_Qualifier CIM_Job_ErrorCode_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_ErrorCode_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.ErrorDescription"),
};

static MI_CONST MI_ConstStringA CIM_Job_ErrorCode_ModelCorrespondence_qual_value =
{
    CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ErrorCode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_ErrorCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ErrorCode_quals[] =
{
    &CIM_Job_ErrorCode_Description_qual,
    &CIM_Job_ErrorCode_ModelCorrespondence_qual,
};

/* property CIM_Job.ErrorCode */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorCode"), /* name */
    CIM_Job_ErrorCode_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ErrorCode_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorCode), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ErrorDescription_Description_qual_value = MI_T("A free-form string that contains the vendor error description. Note that this property is also present in the JobProcessingStatistics class. This class is necessary to capture the processing information for recurring Jobs, because only the \'last\' run error can be stored in this single-valued property.");

static MI_CONST MI_Qualifier CIM_Job_ErrorDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_ErrorDescription_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.ErrorCode"),
};

static MI_CONST MI_ConstStringA CIM_Job_ErrorDescription_ModelCorrespondence_qual_value =
{
    CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ErrorDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_ErrorDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ErrorDescription_quals[] =
{
    &CIM_Job_ErrorDescription_Description_qual,
    &CIM_Job_ErrorDescription_ModelCorrespondence_qual,
};

/* property CIM_Job.ErrorDescription */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656E10, /* code */
    MI_T("ErrorDescription"), /* name */
    CIM_Job_ErrorDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ErrorDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorDescription), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RecoveryAction_Description_qual_value = MI_T("Describes the recovery action to be taken for an unsuccessfully run Job. The possible values are: \n0 = \"Unknown\", meaning it is unknown as to what recovery action to take \n1 = \"Other\", indicating that the recovery action will be specified in the OtherRecoveryAction property \n2 = \"Do Not Continue\", meaning stop the execution of the job and appropriately update its status \n3 = \"Continue With Next Job\", meaning continue with the next job in the queue \n4 = \"Re-run Job\", indicating that the job should be re-run \n5 = \"Run Recovery Job\", meaning run the Job associated using the RecoveryJob relationship. Note that the recovery Job must already be in the queue from which it will run.");

static MI_CONST MI_Qualifier CIM_Job_RecoveryAction_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RecoveryAction_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_RecoveryAction_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
};

static MI_CONST MI_ConstStringA CIM_Job_RecoveryAction_ValueMap_qual_value =
{
    CIM_Job_RecoveryAction_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_RecoveryAction_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RecoveryAction_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_RecoveryAction_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_RecoveryAction_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Do Not Continue"),
    MI_T("Continue With Next Job"),
    MI_T("Re-run Job"),
    MI_T("Run Recovery Job"),
};

static MI_CONST MI_ConstStringA CIM_Job_RecoveryAction_Values_qual_value =
{
    CIM_Job_RecoveryAction_Values_qual_data_value,
    MI_COUNT(CIM_Job_RecoveryAction_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RecoveryAction_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_RecoveryAction_Values_qual_value
};

static MI_CONST MI_Char* CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.OtherRecoveryAction"),
};

static MI_CONST MI_ConstStringA CIM_Job_RecoveryAction_ModelCorrespondence_qual_value =
{
    CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RecoveryAction_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RecoveryAction_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RecoveryAction_quals[] =
{
    &CIM_Job_RecoveryAction_Description_qual,
    &CIM_Job_RecoveryAction_ValueMap_qual,
    &CIM_Job_RecoveryAction_Values_qual,
    &CIM_Job_RecoveryAction_ModelCorrespondence_qual,
};

/* property CIM_Job.RecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_RecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726E0E, /* code */
    MI_T("RecoveryAction"), /* name */
    CIM_Job_RecoveryAction_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RecoveryAction_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_OtherRecoveryAction_Description_qual_value = MI_T("A string describing the recovery action when the RecoveryAction property of the instance is 1 (\"Other\").");

static MI_CONST MI_Qualifier CIM_Job_OtherRecoveryAction_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_OtherRecoveryAction_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RecoveryAction"),
};

static MI_CONST MI_ConstStringA CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_value =
{
    CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_OtherRecoveryAction_quals[] =
{
    &CIM_Job_OtherRecoveryAction_Description_qual,
    &CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual,
};

/* property CIM_Job.OtherRecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_OtherRecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E13, /* code */
    MI_T("OtherRecoveryAction"), /* name */
    CIM_Job_OtherRecoveryAction_quals, /* qualifiers */
    MI_COUNT(CIM_Job_OtherRecoveryAction_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, OtherRecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Job_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
};

static MI_CONST MI_Char* CIM_Job_KillJob_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_Deprecated_qual_value =
{
    CIM_Job_KillJob_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_Description_qual_value = MI_T("KillJob is being deprecated because there is no distinction made between an orderly shutdown and an immediate kill. CIM_ConcreteJob.RequestStateChange() provides \'Terminate\' and \'Kill\' options to allow this distinction. \nA method to kill this job and any underlying processes, and to remove any \'dangling\' associations.");

static MI_CONST MI_Qualifier CIM_Job_KillJob_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_KillJob_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("6"),
    MI_T("7"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_ValueMap_qual_value =
{
    CIM_Job_KillJob_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_KillJob_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_Values_qual_data_value[] =
{
    MI_T("Success"),
    MI_T("Not Supported"),
    MI_T("Unknown"),
    MI_T("Timeout"),
    MI_T("Failed"),
    MI_T("Access Denied"),
    MI_T("Not Found"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_Values_qual_value =
{
    CIM_Job_KillJob_Values_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_KillJob_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_quals[] =
{
    &CIM_Job_KillJob_Deprecated_qual,
    &CIM_Job_KillJob_Description_qual,
    &CIM_Job_KillJob_ValueMap_qual,
    &CIM_Job_KillJob_Values_qual,
};

static MI_CONST MI_Char* CIM_Job_KillJob_DeleteOnKill_Description_qual_value = MI_T("Indicates whether or not the Job should be automatically deleted upon termination. This parameter takes precedence over the property, DeleteOnCompletion.");

static MI_CONST MI_Qualifier CIM_Job_KillJob_DeleteOnKill_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_KillJob_DeleteOnKill_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_DeleteOnKill_quals[] =
{
    &CIM_Job_KillJob_DeleteOnKill_Description_qual,
};

/* parameter CIM_Job.KillJob(): DeleteOnKill */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_DeleteOnKill_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646C0C, /* code */
    MI_T("DeleteOnKill"), /* name */
    CIM_Job_KillJob_DeleteOnKill_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_DeleteOnKill_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, DeleteOnKill), /* offset */
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_MIReturn_Deprecated_qual_value =
{
    CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_MIReturn_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_Description_qual_value = MI_T("KillJob is being deprecated because there is no distinction made between an orderly shutdown and an immediate kill. CIM_ConcreteJob.RequestStateChange() provides \'Terminate\' and \'Kill\' options to allow this distinction. \nA method to kill this job and any underlying processes, and to remove any \'dangling\' associations.");

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_KillJob_MIReturn_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("6"),
    MI_T("7"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_MIReturn_ValueMap_qual_value =
{
    CIM_Job_KillJob_MIReturn_ValueMap_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_MIReturn_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Job_KillJob_MIReturn_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_Values_qual_data_value[] =
{
    MI_T("Success"),
    MI_T("Not Supported"),
    MI_T("Unknown"),
    MI_T("Timeout"),
    MI_T("Failed"),
    MI_T("Access Denied"),
    MI_T("Not Found"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_MIReturn_Values_qual_value =
{
    CIM_Job_KillJob_MIReturn_Values_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_MIReturn_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_KillJob_MIReturn_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_MIReturn_quals[] =
{
    &CIM_Job_KillJob_MIReturn_Deprecated_qual,
    &CIM_Job_KillJob_MIReturn_Description_qual,
    &CIM_Job_KillJob_MIReturn_ValueMap_qual,
    &CIM_Job_KillJob_MIReturn_Values_qual,
};

/* parameter CIM_Job.KillJob(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_Job_KillJob_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_Job_KillJob_params[] =
{
    &CIM_Job_KillJob_MIReturn_param,
    &CIM_Job_KillJob_DeleteOnKill_param,
};

/* method CIM_Job.KillJob() */
MI_CONST MI_MethodDecl CIM_Job_KillJob_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006B6207, /* code */
    MI_T("KillJob"), /* name */
    CIM_Job_KillJob_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_quals), /* numQualifiers */
    CIM_Job_KillJob_params, /* parameters */
    MI_COUNT(CIM_Job_KillJob_params), /* numParameters */
    sizeof(CIM_Job_KillJob), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &test_repos_classDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Job_meths[] =
{
    &CIM_Job_KillJob_rtti,
};

static MI_CONST MI_Char* CIM_Job_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_Job_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Job_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Job_Description_qual_value = MI_T("A Job is a LogicalElement that represents an executing unit of work, such as a script or a print job. A Job is distinct from a Process in that a Job can be scheduled or queued, and its execution is not limited to a single system.");

static MI_CONST MI_Qualifier CIM_Job_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_Description_qual_value
};

static MI_CONST MI_Char* CIM_Job_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_Job_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Job_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_quals[] =
{
    &CIM_Job_UMLPackagePath_qual,
    &CIM_Job_Description_qual,
    &CIM_Job_Version_qual,
};

/* class CIM_Job */
MI_CONST MI_ClassDecl CIM_Job_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636207, /* code */
    MI_T("CIM_Job"), /* name */
    CIM_Job_quals, /* qualifiers */
    MI_COUNT(CIM_Job_quals), /* numQualifiers */
    CIM_Job_props, /* properties */
    MI_COUNT(CIM_Job_props), /* numProperties */
    sizeof(CIM_Job), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_Job_meths, /* methods */
    MI_COUNT(CIM_Job_meths), /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};


/*
**==============================================================================
**
** CIM_ConcreteJob
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ConcreteJob_InstanceID_Description_qual_value = MI_T("Within the scope of the instantiating Namespace, InstanceID opaquely and uniquely identifies an instance of this class. In order to ensure uniqueness within the NameSpace, the value of InstanceID SHOULD be constructed using the following \'preferred\' algorithm: \n<OrgID>:<LocalID> \nWhere <OrgID> and <LocalID> are separated by a colon \':\', and where <OrgID> must include a copyrighted, trademarked or otherwise unique name that is owned by the business entity that is creating or defining the InstanceID, or that is a registered ID that is assigned to the business entity by a recognized global authority. (This requirement is similar to the <Schema Name>_<Class Name> structure of Schema class names.) In addition, to ensure uniqueness <OrgID> must not contain a colon (\':\'). When using this algorithm, the first colon to appear in InstanceID must appear between <OrgID> and <LocalID>. \n<LocalID> is chosen by the business entity and should not be re-used to identify different underlying (real-world) elements. If the above \'preferred\' algorithm is not used, the defining entity must assure that the resulting InstanceID is not re-used across any InstanceIDs produced by this or other providers for the NameSpace of this instance. \nFor DMTF defined instances, the \'preferred\' algorithm must be used with the <OrgID> set to \'CIM\'.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_InstanceID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_InstanceID_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_ConcreteJob_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_InstanceID_quals[] =
{
    &CIM_ConcreteJob_InstanceID_Description_qual,
    &CIM_ConcreteJob_InstanceID_Override_qual,
};

/* property CIM_ConcreteJob.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_ConcreteJob_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ConcreteJob_Name_Description_qual_value = MI_T("The user-friendly name for this instance of a Job. In addition, the user-friendly name can be used as a property for a search or query. (Note: Name does not have to be unique within a namespace.)");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_Name_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_ConcreteJob_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ConcreteJob_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_Name_quals[] =
{
    &CIM_ConcreteJob_Name_Description_qual,
    &CIM_ConcreteJob_Name_MaxLen_qual,
    &CIM_ConcreteJob_Name_Override_qual,
};

/* property CIM_ConcreteJob.Name */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ConcreteJob_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ConcreteJob_JobState_Description_qual_value = MI_T("JobState is an integer enumeration that indicates the operational state of a Job. It can also indicate transitions between these states, for example, \'Shutting Down\' and \'Starting\'. Following is a brief description of the states: \nNew (2) indicates that the job has never been started. \nStarting (3) indicates that the job is moving from the \'New\', \'Suspended\', or \'Service\' states into the \'Running\' state. \nRunning (4) indicates that the Job is running. \nSuspended (5) indicates that the Job is stopped, but can be restarted in a seamless manner. \nShutting Down (6) indicates that the job is moving to a \'Completed\', \'Terminated\', or \'Killed\' state. \nCompleted (7) indicates that the job has completed normally. \nTerminated (8) indicates that the job has been stopped by a \'Terminate\' state change request. The job and all its underlying processes are ended and can be restarted (this is job-specific) only as a new job. \nKilled (9) indicates that the job has been stopped by a \'Kill\' state change request. Underlying processes might have been left running, and cleanup might be required to free up resources. \nException (10) indicates that the Job is in an abnormal state that might be indicative of an error condition. Actual status might be displayed though job-specific objects. \nService (11) indicates that the Job is in a vendor-specific state that supports problem discovery, or resolution, or both.\nQuery pending (12) waiting for a client to resolve a query");

static MI_CONST MI_Qualifier CIM_ConcreteJob_JobState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_JobState_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_JobState_ValueMap_qual_data_value[] =
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
    MI_T("13..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_JobState_ValueMap_qual_value =
{
    CIM_ConcreteJob_JobState_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_JobState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_JobState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_JobState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_JobState_Values_qual_data_value[] =
{
    MI_T("New"),
    MI_T("Starting"),
    MI_T("Running"),
    MI_T("Suspended"),
    MI_T("Shutting Down"),
    MI_T("Completed"),
    MI_T("Terminated"),
    MI_T("Killed"),
    MI_T("Exception"),
    MI_T("Service"),
    MI_T("Query Pending"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_JobState_Values_qual_value =
{
    CIM_ConcreteJob_JobState_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_JobState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_JobState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_JobState_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_JobState_quals[] =
{
    &CIM_ConcreteJob_JobState_Description_qual,
    &CIM_ConcreteJob_JobState_ValueMap_qual,
    &CIM_ConcreteJob_JobState_Values_qual,
};

/* property CIM_ConcreteJob.JobState */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_JobState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A6508, /* code */
    MI_T("JobState"), /* name */
    CIM_ConcreteJob_JobState_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_JobState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, JobState), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ConcreteJob_TimeOfLastStateChange_Description_qual_value = MI_T("The date or time when the state of the Job last changed. If the state of the Job has not changed and this property is populated, then it must be set to a 0 interval value. If a state change was requested, but rejected or not yet processed, the property must not be updated.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_TimeOfLastStateChange_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_TimeOfLastStateChange_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_TimeOfLastStateChange_quals[] =
{
    &CIM_ConcreteJob_TimeOfLastStateChange_Description_qual,
};

/* property CIM_ConcreteJob.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    CIM_ConcreteJob_TimeOfLastStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_TimeOfLastStateChange_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeOfLastStateChange), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ConcreteJob_TimeBeforeRemoval_Description_qual_value = MI_T("The amount of time that the Job is retained after it has finished executing, either succeeding or failing in that execution. The job must remain in existence for some period of time regardless of the value of the DeleteOnCompletion property. \nThe default is five minutes.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_TimeBeforeRemoval_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_TimeBeforeRemoval_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_TimeBeforeRemoval_quals[] =
{
    &CIM_ConcreteJob_TimeBeforeRemoval_Description_qual,
};

static MI_CONST MI_Datetime CIM_ConcreteJob_TimeBeforeRemoval_value = {0,{{0,0,5,0,0}}};

/* property CIM_ConcreteJob.TimeBeforeRemoval */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeBeforeRemoval_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00746C11, /* code */
    MI_T("TimeBeforeRemoval"), /* name */
    CIM_ConcreteJob_TimeBeforeRemoval_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_TimeBeforeRemoval_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeBeforeRemoval), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &CIM_ConcreteJob_TimeBeforeRemoval_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ConcreteJob_props[] =
{
    &CIM_ConcreteJob_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ConcreteJob_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
    &CIM_ConcreteJob_JobState_prop,
    &CIM_ConcreteJob_TimeOfLastStateChange_prop,
    &CIM_ConcreteJob_TimeBeforeRemoval_prop,
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_Description_qual_value = MI_T("Requests that the state of the job be changed to the value specified in the RequestedState parameter. Invoking the RequestStateChange method multiple times could result in earlier requests being overwritten or lost. \nIf 0 is returned, then the task completed successfully. Any other return code indicates an error condition.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("4096"),
    MI_T("4097"),
    MI_T("4098"),
    MI_T("4099"),
    MI_T("4100..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_ValueMap_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_RequestStateChange_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_Values_qual_data_value[] =
{
    MI_T("Completed with No Error"),
    MI_T("Not Supported"),
    MI_T("Unknown/Unspecified Error"),
    MI_T("Can NOT complete within Timeout Period"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("In Use"),
    MI_T("DMTF Reserved"),
    MI_T("Method Parameters Checked - Transition Started"),
    MI_T("Invalid State Transition"),
    MI_T("Use of Timeout Parameter Not Supported"),
    MI_T("Busy"),
    MI_T("Method Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_Values_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_quals[] =
{
    &CIM_ConcreteJob_RequestStateChange_Description_qual,
    &CIM_ConcreteJob_RequestStateChange_ValueMap_qual,
    &CIM_ConcreteJob_RequestStateChange_Values_qual,
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_RequestedState_Description_qual_value = MI_T("RequestStateChange changes the state of a job. The possible values are as follows: \nStart (2) changes the state to \'Running\'. \nSuspend (3) stops the job temporarily. The intention is to subsequently restart the job with \'Start\'. It might be possible to enter the \'Service\' state while suspended. (This is job-specific.) \nTerminate (4) stops the job cleanly, saving data, preserving the state, and shutting down all underlying processes in an orderly manner. \nKill (5) terminates the job immediately with no requirement to save data or preserve the state. \nService (6) puts the job into a vendor-specific service state. It might be possible to restart the job.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_RequestedState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual_data_value[] =
{
    MI_T("Start"),
    MI_T("Suspend"),
    MI_T("Terminate"),
    MI_T("Kill"),
    MI_T("Service"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_RequestedState_quals[] =
{
    &CIM_ConcreteJob_RequestStateChange_RequestedState_Description_qual,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_ValueMap_qual,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_Values_qual,
};

/* parameter CIM_ConcreteJob.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    CIM_ConcreteJob_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, RequestedState), /* offset */
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_Description_qual_value = MI_T("A timeout period that specifies the maximum amount of time that the client expects the transition to the new state to take. The interval format must be used to specify the TimeoutPeriod. A value of 0 or a null parameter indicates that the client has no time requirements for the transition. \nIf this property does not contain 0 or null and the implementation does not support this parameter, a return code of \'Use Of Timeout Parameter Not Supported\' must be returned.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_quals[] =
{
    &CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_Description_qual,
};

/* parameter CIM_ConcreteJob.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_MIReturn_Description_qual_value = MI_T("Requests that the state of the job be changed to the value specified in the RequestedState parameter. Invoking the RequestStateChange method multiple times could result in earlier requests being overwritten or lost. \nIf 0 is returned, then the task completed successfully. Any other return code indicates an error condition.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_MIReturn_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("4096"),
    MI_T("4097"),
    MI_T("4098"),
    MI_T("4099"),
    MI_T("4100..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual_data_value[] =
{
    MI_T("Completed with No Error"),
    MI_T("Not Supported"),
    MI_T("Unknown/Unspecified Error"),
    MI_T("Can NOT complete within Timeout Period"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("In Use"),
    MI_T("DMTF Reserved"),
    MI_T("Method Parameters Checked - Transition Started"),
    MI_T("Invalid State Transition"),
    MI_T("Use of Timeout Parameter Not Supported"),
    MI_T("Busy"),
    MI_T("Method Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual_value =
{
    CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_MIReturn_quals[] =
{
    &CIM_ConcreteJob_RequestStateChange_MIReturn_Description_qual,
    &CIM_ConcreteJob_RequestStateChange_MIReturn_ValueMap_qual,
    &CIM_ConcreteJob_RequestStateChange_MIReturn_Values_qual,
};

/* parameter CIM_ConcreteJob.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_ConcreteJob_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_params[] =
{
    &CIM_ConcreteJob_RequestStateChange_MIReturn_param,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_param,
    &CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_ConcreteJob.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    CIM_ConcreteJob_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_quals), /* numQualifiers */
    CIM_ConcreteJob_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_params), /* numParameters */
    sizeof(CIM_ConcreteJob_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &test_repos_classDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Description_qual_value = MI_T("When the job is executing or has terminated without error, then this method returns no CIM_Error instance. However, if the job has failed because of some internal problem or because the job has been terminated by a client, then a CIM_Error instance is returned.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_GetError_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_ValueMap_qual_value =
{
    CIM_ConcreteJob_GetError_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_GetError_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Values_qual_data_value[] =
{
    MI_T("Success"),
    MI_T("Not Supported"),
    MI_T("Unspecified Error"),
    MI_T("Timeout"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("Access Denied"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_Values_qual_value =
{
    CIM_ConcreteJob_GetError_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_GetError_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_quals[] =
{
    &CIM_ConcreteJob_GetError_Description_qual,
    &CIM_ConcreteJob_GetError_ValueMap_qual,
    &CIM_ConcreteJob_GetError_Values_qual,
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Error_Description_qual_value = MI_T("If the OperationalStatus on the Job is not \"OK\", then this method will return a CIM Error instance. Otherwise, when the Job is \"OK\", null is returned.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_GetError_Error_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value = MI_T("CIM_Error");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_Error_quals[] =
{
    &CIM_ConcreteJob_GetError_Error_Description_qual,
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual,
};

/* parameter CIM_ConcreteJob.GetError(): Error */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_Error_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657205, /* code */
    MI_T("Error"), /* name */
    CIM_ConcreteJob_GetError_Error_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_Error_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("CIM_Error"), /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, Error), /* offset */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_MIReturn_Description_qual_value = MI_T("When the job is executing or has terminated without error, then this method returns no CIM_Error instance. However, if the job has failed because of some internal problem or because the job has been terminated by a client, then a CIM_Error instance is returned.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_GetError_MIReturn_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual_value =
{
    CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_MIReturn_Values_qual_data_value[] =
{
    MI_T("Success"),
    MI_T("Not Supported"),
    MI_T("Unspecified Error"),
    MI_T("Timeout"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("Access Denied"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_MIReturn_Values_qual_value =
{
    CIM_ConcreteJob_GetError_MIReturn_Values_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_MIReturn_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_GetError_MIReturn_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_MIReturn_quals[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_Description_qual,
    &CIM_ConcreteJob_GetError_MIReturn_ValueMap_qual,
    &CIM_ConcreteJob_GetError_MIReturn_Values_qual,
};

/* parameter CIM_ConcreteJob.GetError(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_ConcreteJob_GetError_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_GetError_params[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_param,
    &CIM_ConcreteJob_GetError_Error_param,
};

/* method CIM_ConcreteJob.GetError() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_GetError_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677208, /* code */
    MI_T("GetError"), /* name */
    CIM_ConcreteJob_GetError_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_quals), /* numQualifiers */
    CIM_ConcreteJob_GetError_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_GetError_params), /* numParameters */
    sizeof(CIM_ConcreteJob_GetError), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &test_repos_classDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ConcreteJob_meths[] =
{
    &CIM_Job_KillJob_rtti,
    &CIM_ConcreteJob_RequestStateChange_rtti,
    &CIM_ConcreteJob_GetError_rtti,
};

static MI_CONST MI_Char* CIM_ConcreteJob_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ConcreteJob_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Description_qual_value = MI_T("A concrete version of Job. This class represents a generic and instantiable unit of work, such as a batch or a print job.");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_ConcreteJob_Description_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_quals[] =
{
    &CIM_ConcreteJob_UMLPackagePath_qual,
    &CIM_ConcreteJob_Description_qual,
    &CIM_ConcreteJob_Version_qual,
};

/* class CIM_ConcreteJob */
MI_CONST MI_ClassDecl CIM_ConcreteJob_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063620F, /* code */
    MI_T("CIM_ConcreteJob"), /* name */
    CIM_ConcreteJob_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_quals), /* numQualifiers */
    CIM_ConcreteJob_props, /* properties */
    MI_COUNT(CIM_ConcreteJob_props), /* numProperties */
    sizeof(CIM_ConcreteJob), /* size */
    MI_T("CIM_Job"), /* superClass */
    &CIM_Job_rtti, /* superClassDecl */
    CIM_ConcreteJob_meths, /* methods */
    MI_COUNT(CIM_ConcreteJob_meths), /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_EnabledLogicalElement
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledState_Description_qual_value = MI_T("EnabledState is an integer enumeration that indicates the enabled and disabled states of an element. It can also indicate the transitions between these requested states. For example, shutting down (value=4) and starting (value=10) are transient states between enabled and disabled. The following text briefly summarizes the various enabled and disabled states: \nEnabled (2) indicates that the element is or could be executing commands, will process any queued commands, and queues new requests. \nDisabled (3) indicates that the element will not execute commands and will drop any new requests. \nShutting Down (4) indicates that the element is in the process of going to a Disabled state. \nNot Applicable (5) indicates the element does not support being enabled or disabled. \nEnabled but Offline (6) indicates that the element might be completing commands, and will drop any new requests. \nTest (7) indicates that the element is in a test state. \nDeferred (8) indicates that the element might be completing commands, but will queue any new requests. \nQuiesce (9) indicates that the element is enabled but in a restricted mode.\nStarting (10) indicates that the element is in the process of going to an Enabled state. New requests are queued.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_EnabledState_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledState_ValueMap_qual_data_value[] =
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
    MI_T("11..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledState_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_EnabledState_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_EnabledState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledState_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Shutting Down"),
    MI_T("Not Applicable"),
    MI_T("Enabled but Offline"),
    MI_T("In Test"),
    MI_T("Deferred"),
    MI_T("Quiesce"),
    MI_T("Starting"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledState_Values_qual_value =
{
    CIM_EnabledLogicalElement_EnabledState_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_EnabledState_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.OtherEnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_EnabledState_quals[] =
{
    &CIM_EnabledLogicalElement_EnabledState_Description_qual,
    &CIM_EnabledLogicalElement_EnabledState_ValueMap_qual,
    &CIM_EnabledLogicalElement_EnabledState_Values_qual,
    &CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledState_value = 5;

/* property CIM_EnabledLogicalElement.EnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650C, /* code */
    MI_T("EnabledState"), /* name */
    CIM_EnabledLogicalElement_EnabledState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledState_value,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_OtherEnabledState_Description_qual_value = MI_T("A string that describes the enabled or disabled state of the element when the EnabledState property is set to 1 (\"Other\"). This property must be set to null when EnabledState is any value other than 1.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_OtherEnabledState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_OtherEnabledState_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_OtherEnabledState_quals[] =
{
    &CIM_EnabledLogicalElement_OtherEnabledState_Description_qual,
    &CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElement.OtherEnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_OtherEnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6511, /* code */
    MI_T("OtherEnabledState"), /* name */
    CIM_EnabledLogicalElement_OtherEnabledState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_OtherEnabledState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, OtherEnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestedState_Description_qual_value = MI_T("RequestedState is an integer enumeration that indicates the last requested or desired state for the element, irrespective of the mechanism through which it was requested. The actual state of the element is represented by EnabledState. This property is provided to compare the last requested and current enabled or disabled states. Note that when EnabledState is set to 5 (\"Not Applicable\"), then this property has no meaning. Refer to the EnabledState property description for explanations of the values in the RequestedState enumeration. \n\"Unknown\" (0) indicates the last requested state for the element is unknown.\nNote that the value \"No Change\" (5) has been deprecated in lieu of indicating the last requested state is \"Unknown\" (0). If the last requested or desired state is unknown, RequestedState should have the value \"Unknown\" (0), but may have the value \"No Change\" (5).Offline (6) indicates that the element has been requested to transition to the Enabled but Offline EnabledState. \nIt should be noted that there are two new values in RequestedState that build on the statuses of EnabledState. These are \"Reboot\" (10) and \"Reset\" (11). Reboot refers to doing a \"Shut Down\" and then moving to an \"Enabled\" state. Reset indicates that the element is first \"Disabled\" and then \"Enabled\". The distinction between requesting \"Shut Down\" and \"Disabled\" should also be noted. Shut Down requests an orderly transition to the Disabled state, and might involve removing power, to completely erase any existing state. The Disabled state requests an immediate disabling of the element, such that it will not execute or accept any commands or processing requests. \n\nThis property is set as the result of a method invocation (such as Start or StopService on CIM_Service), or can be overridden and defined as WRITEable in a subclass. The method approach is considered superior to a WRITEable property, because it allows an explicit invocation of the operation and the return of a result code. \n\nIf knowledge of the last RequestedState is not supported for the EnabledLogicalElement, the property shall be NULL or have the value 12 \"Not Applicable\".");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestedState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestedState_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestedState_ValueMap_qual_data_value[] =
{
    MI_T("0"),
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
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestedState_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_RequestedState_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestedState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestedState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestedState_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Shut Down"),
    MI_T("No Change"),
    MI_T("Offline"),
    MI_T("Test"),
    MI_T("Deferred"),
    MI_T("Quiesce"),
    MI_T("Reboot"),
    MI_T("Reset"),
    MI_T("Not Applicable"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestedState_Values_qual_value =
{
    CIM_EnabledLogicalElement_RequestedState_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestedState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestedState_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestedState_quals[] =
{
    &CIM_EnabledLogicalElement_RequestedState_Description_qual,
    &CIM_EnabledLogicalElement_RequestedState_ValueMap_qual,
    &CIM_EnabledLogicalElement_RequestedState_Values_qual,
    &CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_RequestedState_value = 12;

/* property CIM_EnabledLogicalElement.RequestedState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_RequestedState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    CIM_EnabledLogicalElement_RequestedState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, RequestedState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_RequestedState_value,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledDefault_Description_qual_value = MI_T("An enumerated value indicating an administrator\'s default or startup configuration for the Enabled State of an element. By default, the element is \"Enabled\" (value=2).");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledDefault_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_EnabledDefault_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("9"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledDefault_Values_qual_data_value[] =
{
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Not Applicable"),
    MI_T("Enabled but Offline"),
    MI_T("No Default"),
    MI_T("Quiesce"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledDefault_Values_qual_value =
{
    CIM_EnabledLogicalElement_EnabledDefault_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledDefault_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledDefault_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_EnabledDefault_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_EnabledDefault_quals[] =
{
    &CIM_EnabledLogicalElement_EnabledDefault_Description_qual,
    &CIM_EnabledLogicalElement_EnabledDefault_ValueMap_qual,
    &CIM_EnabledLogicalElement_EnabledDefault_Values_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledDefault_value = 2;

/* property CIM_EnabledLogicalElement.EnabledDefault */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledDefault_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065740E, /* code */
    MI_T("EnabledDefault"), /* name */
    CIM_EnabledLogicalElement_EnabledDefault_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_EnabledDefault_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledDefault), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledDefault_value,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TimeOfLastStateChange_Description_qual_value = MI_T("The date or time when the EnabledState of the element last changed. If the state of the element has not changed and this property is populated, then it must be set to a 0 interval value. If a state change was requested, but rejected or not yet processed, the property must not be updated.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TimeOfLastStateChange_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_TimeOfLastStateChange_quals[] =
{
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_Description_qual,
};

/* property CIM_EnabledLogicalElement.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    CIM_EnabledLogicalElement_TimeOfLastStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_TimeOfLastStateChange_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TimeOfLastStateChange), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_AvailableRequestedStates_Description_qual_value = MI_T("AvailableRequestedStates indicates the possible values for the RequestedState parameter of the method RequestStateChange, used to initiate a state change. The values listed shall be a subset of the values contained in the RequestedStatesSupported property of the associated instance of CIM_EnabledLogicalElementCapabilities where the values selected are a function of the current state of the CIM_EnabledLogicalElement. This property may be non-null if an implementation is able to advertise the set of possible values as a function of the current state. This property shall be null if an implementation is unable to determine the set of possible values as a function of the current state.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_AvailableRequestedStates_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual_data_value[] =
{
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Shut Down"),
    MI_T("Offline"),
    MI_T("Test"),
    MI_T("Defer"),
    MI_T("Quiesce"),
    MI_T("Reboot"),
    MI_T("Reset"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual_value =
{
    CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
    MI_T("CIM_EnabledLogicalElementCapabilities.RequestedStatesSupported"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_AvailableRequestedStates_quals[] =
{
    &CIM_EnabledLogicalElement_AvailableRequestedStates_Description_qual,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ValueMap_qual,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_Values_qual,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElement.AvailableRequestedStates */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_AvailableRequestedStates_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617318, /* code */
    MI_T("AvailableRequestedStates"), /* name */
    CIM_EnabledLogicalElement_AvailableRequestedStates_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, AvailableRequestedStates), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TransitioningToState_Description_qual_value = MI_T("TransitioningToState indicates the target state to which the instance is transitioning. \nA value of 5 \"No Change\" shall indicate that no transition is in progress.A value of 12 \"Not Applicable\" shall indicate the implementation does not support representing ongoing transitions. \nA value other than 5 or 12 shall identify the state to which the element is in the process of transitioning.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TransitioningToState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_TransitioningToState_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual_data_value[] =
{
    MI_T("0"),
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
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TransitioningToState_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Shut Down"),
    MI_T("No Change"),
    MI_T("Offline"),
    MI_T("Test"),
    MI_T("Defer"),
    MI_T("Quiesce"),
    MI_T("Reboot"),
    MI_T("Reset"),
    MI_T("Not Applicable"),
    MI_T("DMTF Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_TransitioningToState_Values_qual_value =
{
    CIM_EnabledLogicalElement_TransitioningToState_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TransitioningToState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_TransitioningToState_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_TransitioningToState_quals[] =
{
    &CIM_EnabledLogicalElement_TransitioningToState_Description_qual,
    &CIM_EnabledLogicalElement_TransitioningToState_ValueMap_qual,
    &CIM_EnabledLogicalElement_TransitioningToState_Values_qual,
    &CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_TransitioningToState_value = 12;

/* property CIM_EnabledLogicalElement.TransitioningToState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TransitioningToState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746514, /* code */
    MI_T("TransitioningToState"), /* name */
    CIM_EnabledLogicalElement_TransitioningToState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TransitioningToState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_TransitioningToState_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_Description_qual_value = MI_T("Requests that the state of the element be changed to the value specified in the RequestedState parameter. When the requested state change takes place, the EnabledState and RequestedState of the element will be the same. Invoking the RequestStateChange method multiple times could result in earlier requests being overwritten or lost. \nA return code of 0 shall indicate the state change was successfully initiated. \nA return code of 3 shall indicate that the state transition cannot complete within the interval specified by the TimeoutPeriod parameter. \nA return code of 4096 (0x1000) shall indicate the state change was successfully initiated, a ConcreteJob has been created, and its reference returned in the output parameter Job. Any other return code indicates an error condition.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("4096"),
    MI_T("4097"),
    MI_T("4098"),
    MI_T("4099"),
    MI_T("4100..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_Values_qual_data_value[] =
{
    MI_T("Completed with No Error"),
    MI_T("Not Supported"),
    MI_T("Unknown or Unspecified Error"),
    MI_T("Cannot complete within Timeout Period"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("In Use"),
    MI_T("DMTF Reserved"),
    MI_T("Method Parameters Checked - Job Started"),
    MI_T("Invalid State Transition"),
    MI_T("Use of Timeout Parameter Not Supported"),
    MI_T("Busy"),
    MI_T("Method Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_Values_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_Description_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_ValueMap_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_Values_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Description_qual_value = MI_T("The state requested for the element. This information will be placed into the RequestedState property of the instance if the return code of the RequestStateChange method is 0 (\'Completed with No Error\'), or 4096 (0x1000) (\'Job Started\'). Refer to the description of the EnabledState and RequestedState properties for the detailed explanations of the RequestedState values.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T(".."),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual_data_value[] =
{
    MI_T("Enabled"),
    MI_T("Disabled"),
    MI_T("Shut Down"),
    MI_T("Offline"),
    MI_T("Test"),
    MI_T("Defer"),
    MI_T("Quiesce"),
    MI_T("Reboot"),
    MI_T("Reset"),
    MI_T("DMTF Reserved"),
    MI_T("Vendor Reserved"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Description_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ValueMap_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_Values_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, RequestedState), /* offset */
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_Job_Description_qual_value = MI_T("May contain a reference to the ConcreteJob created to track the state transition initiated by the method invocation.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_Job_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_Job_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_Job_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_Job_Description_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_Job_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_Job_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, Job), /* offset */
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_Description_qual_value = MI_T("A timeout period that specifies the maximum amount of time that the client expects the transition to the new state to take. The interval format must be used to specify the TimeoutPeriod. A value of 0 or a null parameter indicates that the client has no time requirements for the transition. \nIf this property does not contain 0 or null and the implementation does not support this parameter, a return code of \'Use Of Timeout Parameter Not Supported\' shall be returned.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_Description_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Description_qual_value = MI_T("Requests that the state of the element be changed to the value specified in the RequestedState parameter. When the requested state change takes place, the EnabledState and RequestedState of the element will be the same. Invoking the RequestStateChange method multiple times could result in earlier requests being overwritten or lost. \nA return code of 0 shall indicate the state change was successfully initiated. \nA return code of 3 shall indicate that the state transition cannot complete within the interval specified by the TimeoutPeriod parameter. \nA return code of 4096 (0x1000) shall indicate the state change was successfully initiated, a ConcreteJob has been created, and its reference returned in the output parameter Job. Any other return code indicates an error condition.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T(".."),
    MI_T("4096"),
    MI_T("4097"),
    MI_T("4098"),
    MI_T("4099"),
    MI_T("4100..32767"),
    MI_T("32768..65535"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual_data_value[] =
{
    MI_T("Completed with No Error"),
    MI_T("Not Supported"),
    MI_T("Unknown or Unspecified Error"),
    MI_T("Cannot complete within Timeout Period"),
    MI_T("Failed"),
    MI_T("Invalid Parameter"),
    MI_T("In Use"),
    MI_T("DMTF Reserved"),
    MI_T("Method Parameters Checked - Job Started"),
    MI_T("Invalid State Transition"),
    MI_T("Use of Timeout Parameter Not Supported"),
    MI_T("Busy"),
    MI_T("Method Reserved"),
    MI_T("Vendor Specific"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Description_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ValueMap_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_Values_qual,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_params[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param,
    &CIM_EnabledLogicalElement_RequestStateChange_Job_param,
    &CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_EnabledLogicalElement.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_EnabledLogicalElement_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_quals), /* numQualifiers */
    CIM_EnabledLogicalElement_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_params), /* numParameters */
    sizeof(CIM_EnabledLogicalElement_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &test_repos_classDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_EnabledLogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_Description_qual_value = MI_T("This class extends LogicalElement to abstract the concept of an element that is enabled and disabled, such as a LogicalDevice or a ServiceAccessPoint.");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_EnabledLogicalElement_Description_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_EnabledLogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_quals[] =
{
    &CIM_EnabledLogicalElement_UMLPackagePath_qual,
    &CIM_EnabledLogicalElement_Description_qual,
    &CIM_EnabledLogicalElement_Version_qual,
};

/* class CIM_EnabledLogicalElement */
MI_CONST MI_ClassDecl CIM_EnabledLogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637419, /* code */
    MI_T("CIM_EnabledLogicalElement"), /* name */
    CIM_EnabledLogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_quals), /* numQualifiers */
    CIM_EnabledLogicalElement_props, /* properties */
    MI_COUNT(CIM_EnabledLogicalElement_props), /* numProperties */
    sizeof(CIM_EnabledLogicalElement), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_EnabledLogicalElement_meths, /* methods */
    MI_COUNT(CIM_EnabledLogicalElement_meths), /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_Process
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Process_Name_Description_qual_value = MI_T("The name of the process.");

static MI_CONST MI_Qualifier CIM_Process_Name_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_Name_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_Process_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_Process_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Process_Name_Override_qual_value
};

static MI_CONST MI_Char* CIM_Process_Name_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.6"),
};

static MI_CONST MI_ConstStringA CIM_Process_Name_MappingStrings_qual_value =
{
    CIM_Process_Name_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_Name_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_Name_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_Name_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_Name_quals[] =
{
    &CIM_Process_Name_Description_qual,
    &CIM_Process_Name_MaxLen_qual,
    &CIM_Process_Name_Override_qual,
    &CIM_Process_Name_MappingStrings_qual,
};

/* property CIM_Process.Name */
static MI_CONST MI_PropertyDecl CIM_Process_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_Process_Name_quals, /* qualifiers */
    MI_COUNT(CIM_Process_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_CSCreationClassName_Description_qual_value = MI_T("The scoping ComputerSystem\'s CreationClassName.");

static MI_CONST MI_Qualifier CIM_Process_CSCreationClassName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_CSCreationClassName_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_CSCreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_CSCreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_CSCreationClassName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_CSCreationClassName_Propagated_qual_value = MI_T("CIM_OperatingSystem.CSCreationClassName");

static MI_CONST MI_Qualifier CIM_Process_CSCreationClassName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Process_CSCreationClassName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_CSCreationClassName_quals[] =
{
    &CIM_Process_CSCreationClassName_Description_qual,
    &CIM_Process_CSCreationClassName_MaxLen_qual,
    &CIM_Process_CSCreationClassName_Propagated_qual,
};

/* property CIM_Process.CSCreationClassName */
static MI_CONST MI_PropertyDecl CIM_Process_CSCreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636513, /* code */
    MI_T("CSCreationClassName"), /* name */
    CIM_Process_CSCreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_Process_CSCreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, CSCreationClassName), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_CSName_Description_qual_value = MI_T("The scoping ComputerSystem\'s Name.");

static MI_CONST MI_Qualifier CIM_Process_CSName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_CSName_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_CSName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_CSName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_CSName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_CSName_Propagated_qual_value = MI_T("CIM_OperatingSystem.CSName");

static MI_CONST MI_Qualifier CIM_Process_CSName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Process_CSName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_CSName_quals[] =
{
    &CIM_Process_CSName_Description_qual,
    &CIM_Process_CSName_MaxLen_qual,
    &CIM_Process_CSName_Propagated_qual,
};

/* property CIM_Process.CSName */
static MI_CONST MI_PropertyDecl CIM_Process_CSName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636506, /* code */
    MI_T("CSName"), /* name */
    CIM_Process_CSName_quals, /* qualifiers */
    MI_COUNT(CIM_Process_CSName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, CSName), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_OSCreationClassName_Description_qual_value = MI_T("The scoping OperatingSystem\'s CreationClassName.");

static MI_CONST MI_Qualifier CIM_Process_OSCreationClassName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_OSCreationClassName_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_OSCreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_OSCreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_OSCreationClassName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_OSCreationClassName_Propagated_qual_value = MI_T("CIM_OperatingSystem.CreationClassName");

static MI_CONST MI_Qualifier CIM_Process_OSCreationClassName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Process_OSCreationClassName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_OSCreationClassName_quals[] =
{
    &CIM_Process_OSCreationClassName_Description_qual,
    &CIM_Process_OSCreationClassName_MaxLen_qual,
    &CIM_Process_OSCreationClassName_Propagated_qual,
};

/* property CIM_Process.OSCreationClassName */
static MI_CONST MI_PropertyDecl CIM_Process_OSCreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006F6513, /* code */
    MI_T("OSCreationClassName"), /* name */
    CIM_Process_OSCreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_Process_OSCreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, OSCreationClassName), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_OSName_Description_qual_value = MI_T("The scoping OperatingSystem\'s Name.");

static MI_CONST MI_Qualifier CIM_Process_OSName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_OSName_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_OSName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_OSName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_OSName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_OSName_Propagated_qual_value = MI_T("CIM_OperatingSystem.Name");

static MI_CONST MI_Qualifier CIM_Process_OSName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Process_OSName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_OSName_quals[] =
{
    &CIM_Process_OSName_Description_qual,
    &CIM_Process_OSName_MaxLen_qual,
    &CIM_Process_OSName_Propagated_qual,
};

/* property CIM_Process.OSName */
static MI_CONST MI_PropertyDecl CIM_Process_OSName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006F6506, /* code */
    MI_T("OSName"), /* name */
    CIM_Process_OSName_quals, /* qualifiers */
    MI_COUNT(CIM_Process_OSName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, OSName), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_CreationClassName_Description_qual_value = MI_T("CreationClassName indicates the name of the class or the subclass used in the creation of an instance. When used with the other key properties of this class, this property allows all instances of this class and its subclasses to be uniquely identified.");

static MI_CONST MI_Qualifier CIM_Process_CreationClassName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_CreationClassName_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_CreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_CreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_CreationClassName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_CreationClassName_quals[] =
{
    &CIM_Process_CreationClassName_Description_qual,
    &CIM_Process_CreationClassName_MaxLen_qual,
};

/* property CIM_Process.CreationClassName */
static MI_CONST MI_PropertyDecl CIM_Process_CreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636511, /* code */
    MI_T("CreationClassName"), /* name */
    CIM_Process_CreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_Process_CreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, CreationClassName), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_Handle_Description_qual_value = MI_T("A string used to identify the Process. A Process ID is a kind of Process Handle.");

static MI_CONST MI_Qualifier CIM_Process_Handle_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_Handle_Description_qual_value
};

static MI_CONST MI_Uint32 CIM_Process_Handle_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_Process_Handle_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Process_Handle_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Process_Handle_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.1"),
};

static MI_CONST MI_ConstStringA CIM_Process_Handle_MappingStrings_qual_value =
{
    CIM_Process_Handle_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_Handle_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_Handle_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_Handle_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_Handle_quals[] =
{
    &CIM_Process_Handle_Description_qual,
    &CIM_Process_Handle_MaxLen_qual,
    &CIM_Process_Handle_MappingStrings_qual,
};

/* property CIM_Process.Handle */
static MI_CONST MI_PropertyDecl CIM_Process_Handle_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00686506, /* code */
    MI_T("Handle"), /* name */
    CIM_Process_Handle_quals, /* qualifiers */
    MI_COUNT(CIM_Process_Handle_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, Handle), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_Priority_Description_qual_value = MI_T("Priority indicates the urgency or importance of execution of a Process. Lower values reflect more favorable process scheduling. If a priority is not defined for a Process, a value of 0 should be used.");

static MI_CONST MI_Qualifier CIM_Process_Priority_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_Priority_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_Priority_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.10"),
};

static MI_CONST MI_ConstStringA CIM_Process_Priority_MappingStrings_qual_value =
{
    CIM_Process_Priority_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_Priority_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_Priority_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_Priority_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_Priority_quals[] =
{
    &CIM_Process_Priority_Description_qual,
    &CIM_Process_Priority_MappingStrings_qual,
};

/* property CIM_Process.Priority */
static MI_CONST MI_PropertyDecl CIM_Process_Priority_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Priority"), /* name */
    CIM_Process_Priority_quals, /* qualifiers */
    MI_COUNT(CIM_Process_Priority_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, Priority), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_ExecutionState_Description_qual_value = MI_T("Indicates the current operating condition of the Process. Values include ready (2), running (3), and blocked (4), among others. The majority of the enumerated values are obvious. However, a few require additional explanation: \n7 (Terminated) describes that a process has naturally completed \n8 (Stopped) describes that a process has been prematurely \'stopped\' by a user or other request \n10 (Ready but Relinquished Processor) describes that a process is in the Ready state, but has voluntarily relinquished execution time to other processes. For example, this state may indicate a problem when the relinquishing process is not handling items on its queues. If these semantics cannot be detected, the process should report its state as 2 (\"Ready\"). \n11 (Hung) indicates that a process is not responding and should therefore not be given further execution time.");

static MI_CONST MI_Qualifier CIM_Process_ExecutionState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_ExecutionState_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_ExecutionState_ValueMap_qual_data_value[] =
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
};

static MI_CONST MI_ConstStringA CIM_Process_ExecutionState_ValueMap_qual_value =
{
    CIM_Process_ExecutionState_ValueMap_qual_data_value,
    MI_COUNT(CIM_Process_ExecutionState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_ExecutionState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &CIM_Process_ExecutionState_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Process_ExecutionState_Values_qual_data_value[] =
{
    MI_T("Unknown"),
    MI_T("Other"),
    MI_T("Ready"),
    MI_T("Running"),
    MI_T("Blocked"),
    MI_T("Suspended Blocked"),
    MI_T("Suspended Ready"),
    MI_T("Terminated"),
    MI_T("Stopped"),
    MI_T("Growing"),
    MI_T("Ready But Relinquished Processor"),
    MI_T("Hung"),
};

static MI_CONST MI_ConstStringA CIM_Process_ExecutionState_Values_qual_value =
{
    CIM_Process_ExecutionState_Values_qual_data_value,
    MI_COUNT(CIM_Process_ExecutionState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_ExecutionState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_ExecutionState_Values_qual_value
};

static MI_CONST MI_Char* CIM_Process_ExecutionState_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.9"),
    MI_T("MIF.UNIX|Process Information|13.9"),
};

static MI_CONST MI_ConstStringA CIM_Process_ExecutionState_MappingStrings_qual_value =
{
    CIM_Process_ExecutionState_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_ExecutionState_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_ExecutionState_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_ExecutionState_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_ExecutionState_quals[] =
{
    &CIM_Process_ExecutionState_Description_qual,
    &CIM_Process_ExecutionState_ValueMap_qual,
    &CIM_Process_ExecutionState_Values_qual,
    &CIM_Process_ExecutionState_MappingStrings_qual,
};

/* property CIM_Process.ExecutionState */
static MI_CONST MI_PropertyDecl CIM_Process_ExecutionState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650E, /* code */
    MI_T("ExecutionState"), /* name */
    CIM_Process_ExecutionState_quals, /* qualifiers */
    MI_COUNT(CIM_Process_ExecutionState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, ExecutionState), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_OtherExecutionDescription_Description_qual_value = MI_T("A string describing the state - used when the instance\'s ExecutionState property is set to 1 (\"Other\"). Other ExecutionDescription should be set to NULL when the Execution State property is any value other than 1.");

static MI_CONST MI_Qualifier CIM_Process_OtherExecutionDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_OtherExecutionDescription_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_OtherExecutionDescription_quals[] =
{
    &CIM_Process_OtherExecutionDescription_Description_qual,
};

/* property CIM_Process.OtherExecutionDescription */
static MI_CONST MI_PropertyDecl CIM_Process_OtherExecutionDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E19, /* code */
    MI_T("OtherExecutionDescription"), /* name */
    CIM_Process_OtherExecutionDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Process_OtherExecutionDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, OtherExecutionDescription), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_CreationDate_Description_qual_value = MI_T("Time that the Process began executing.");

static MI_CONST MI_Qualifier CIM_Process_CreationDate_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_CreationDate_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_CreationDate_quals[] =
{
    &CIM_Process_CreationDate_Description_qual,
};

/* property CIM_Process.CreationDate */
static MI_CONST MI_PropertyDecl CIM_Process_CreationDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650C, /* code */
    MI_T("CreationDate"), /* name */
    CIM_Process_CreationDate_quals, /* qualifiers */
    MI_COUNT(CIM_Process_CreationDate_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, CreationDate), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_TerminationDate_Description_qual_value = MI_T("Time that the Process was stopped or terminated.");

static MI_CONST MI_Qualifier CIM_Process_TerminationDate_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_TerminationDate_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_TerminationDate_quals[] =
{
    &CIM_Process_TerminationDate_Description_qual,
};

/* property CIM_Process.TerminationDate */
static MI_CONST MI_PropertyDecl CIM_Process_TerminationDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074650F, /* code */
    MI_T("TerminationDate"), /* name */
    CIM_Process_TerminationDate_quals, /* qualifiers */
    MI_COUNT(CIM_Process_TerminationDate_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, TerminationDate), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_KernelModeTime_Description_qual_value = MI_T("Time in kernel mode, in milliseconds. If this information is not available, or if the operating system does not distinguish between time in kernel and in user mode, a value of 0 should be used.");

static MI_CONST MI_Qualifier CIM_Process_KernelModeTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_KernelModeTime_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_KernelModeTime_Units_qual_value = MI_T("MilliSeconds");

static MI_CONST MI_Qualifier CIM_Process_KernelModeTime_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_KernelModeTime_Units_qual_value
};

static MI_CONST MI_Char* CIM_Process_KernelModeTime_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.13"),
};

static MI_CONST MI_ConstStringA CIM_Process_KernelModeTime_MappingStrings_qual_value =
{
    CIM_Process_KernelModeTime_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_KernelModeTime_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_KernelModeTime_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_KernelModeTime_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_KernelModeTime_quals[] =
{
    &CIM_Process_KernelModeTime_Description_qual,
    &CIM_Process_KernelModeTime_Units_qual,
    &CIM_Process_KernelModeTime_MappingStrings_qual,
};

/* property CIM_Process.KernelModeTime */
static MI_CONST MI_PropertyDecl CIM_Process_KernelModeTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B650E, /* code */
    MI_T("KernelModeTime"), /* name */
    CIM_Process_KernelModeTime_quals, /* qualifiers */
    MI_COUNT(CIM_Process_KernelModeTime_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, KernelModeTime), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_UserModeTime_Description_qual_value = MI_T("Time in user mode, in milliseconds. If this information is not available, a value of 0 should be used. If the operating system does not distinguish between time in kernel mode and user mode, the time should be returned in this property.");

static MI_CONST MI_Qualifier CIM_Process_UserModeTime_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_UserModeTime_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_UserModeTime_Units_qual_value = MI_T("MilliSeconds");

static MI_CONST MI_Qualifier CIM_Process_UserModeTime_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_UserModeTime_Units_qual_value
};

static MI_CONST MI_Char* CIM_Process_UserModeTime_MappingStrings_qual_data_value[] =
{
    MI_T("MIF.DMTF|Process Information|001.14"),
};

static MI_CONST MI_ConstStringA CIM_Process_UserModeTime_MappingStrings_qual_value =
{
    CIM_Process_UserModeTime_MappingStrings_qual_data_value,
    MI_COUNT(CIM_Process_UserModeTime_MappingStrings_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Process_UserModeTime_MappingStrings_qual =
{
    MI_T("MappingStrings"),
    MI_STRINGA,
    0,
    &CIM_Process_UserModeTime_MappingStrings_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_UserModeTime_quals[] =
{
    &CIM_Process_UserModeTime_Description_qual,
    &CIM_Process_UserModeTime_Units_qual,
    &CIM_Process_UserModeTime_MappingStrings_qual,
};

/* property CIM_Process.UserModeTime */
static MI_CONST MI_PropertyDecl CIM_Process_UserModeTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650C, /* code */
    MI_T("UserModeTime"), /* name */
    CIM_Process_UserModeTime_quals, /* qualifiers */
    MI_COUNT(CIM_Process_UserModeTime_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, UserModeTime), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Process_WorkingSetSize_Description_qual_value = MI_T("The amount of memory in bytes that a Process needs to execute efficiently, for an OperatingSystem that uses page-based memory management. If an insufficient amount of memory is available (< working set size), thrashing will occur. If this information is not known, NULL or 0 should be entered. If this data is provided, it could be monitored to understand a Process\' changing memory requirements as execution proceeds.");

static MI_CONST MI_Qualifier CIM_Process_WorkingSetSize_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_WorkingSetSize_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_WorkingSetSize_Units_qual_value = MI_T("Bytes");

static MI_CONST MI_Qualifier CIM_Process_WorkingSetSize_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_WorkingSetSize_Units_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_WorkingSetSize_quals[] =
{
    &CIM_Process_WorkingSetSize_Description_qual,
    &CIM_Process_WorkingSetSize_Units_qual,
};

/* property CIM_Process.WorkingSetSize */
static MI_CONST MI_PropertyDecl CIM_Process_WorkingSetSize_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0077650E, /* code */
    MI_T("WorkingSetSize"), /* name */
    CIM_Process_WorkingSetSize_quals, /* qualifiers */
    MI_COUNT(CIM_Process_WorkingSetSize_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Process, WorkingSetSize), /* offset */
    MI_T("CIM_Process"), /* origin */
    MI_T("CIM_Process"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Process_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_Process_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_Process_CSCreationClassName_prop,
    &CIM_Process_CSName_prop,
    &CIM_Process_OSCreationClassName_prop,
    &CIM_Process_OSName_prop,
    &CIM_Process_CreationClassName_prop,
    &CIM_Process_Handle_prop,
    &CIM_Process_Priority_prop,
    &CIM_Process_ExecutionState_prop,
    &CIM_Process_OtherExecutionDescription_prop,
    &CIM_Process_CreationDate_prop,
    &CIM_Process_TerminationDate_prop,
    &CIM_Process_KernelModeTime_prop,
    &CIM_Process_UserModeTime_prop,
    &CIM_Process_WorkingSetSize_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Process_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_Process_UMLPackagePath_qual_value = MI_T("CIM::System::Processing");

static MI_CONST MI_Qualifier CIM_Process_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Process_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Process_Description_qual_value = MI_T("Each instance of the CIM_Process class represents a single instance of a running program. A user of the OperatingSystem will typically see a Process as an application or task. Within an OperatingSystem, a Process is defined by a workspace of memory resources and environmental settings that are allocated to it. On a multitasking System, this workspace prevents intrusion of resources by other Processes. Additionally, a Process can execute as multiple Threads, all which run within the same workspace.");

static MI_CONST MI_Qualifier CIM_Process_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Process_Description_qual_value
};

static MI_CONST MI_Char* CIM_Process_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_Process_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Process_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Process_quals[] =
{
    &CIM_Process_UMLPackagePath_qual,
    &CIM_Process_Description_qual,
    &CIM_Process_Version_qual,
};

/* class CIM_Process */
MI_CONST MI_ClassDecl CIM_Process_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063730B, /* code */
    MI_T("CIM_Process"), /* name */
    CIM_Process_quals, /* qualifiers */
    MI_COUNT(CIM_Process_quals), /* numQualifiers */
    CIM_Process_props, /* properties */
    MI_COUNT(CIM_Process_props), /* numProperties */
    sizeof(CIM_Process), /* size */
    MI_T("CIM_EnabledLogicalElement"), /* superClass */
    &CIM_EnabledLogicalElement_rtti, /* superClassDecl */
    CIM_Process_meths, /* methods */
    MI_COUNT(CIM_Process_meths), /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** MSFT_Process
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Process_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_Process_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_Process_CSCreationClassName_prop,
    &CIM_Process_CSName_prop,
    &CIM_Process_OSCreationClassName_prop,
    &CIM_Process_OSName_prop,
    &CIM_Process_CreationClassName_prop,
    &CIM_Process_Handle_prop,
    &CIM_Process_Priority_prop,
    &CIM_Process_ExecutionState_prop,
    &CIM_Process_OtherExecutionDescription_prop,
    &CIM_Process_CreationDate_prop,
    &CIM_Process_TerminationDate_prop,
    &CIM_Process_KernelModeTime_prop,
    &CIM_Process_UserModeTime_prop,
    &CIM_Process_WorkingSetSize_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_Process_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* MSFT_Process_UMLPackagePath_qual_value = MI_T("CIM::System::Processing");

static MI_CONST MI_Qualifier MSFT_Process_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &MSFT_Process_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* MSFT_Process_Description_qual_value = MI_T("Each instance of the CIM_Process class represents a single instance of a running program. A user of the OperatingSystem will typically see a Process as an application or task. Within an OperatingSystem, a Process is defined by a workspace of memory resources and environmental settings that are allocated to it. On a multitasking System, this workspace prevents intrusion of resources by other Processes. Additionally, a Process can execute as multiple Threads, all which run within the same workspace.");

static MI_CONST MI_Qualifier MSFT_Process_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_Process_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_Process_quals[] =
{
    &MSFT_Process_UMLPackagePath_qual,
    &MSFT_Process_Description_qual,
};

/* class MSFT_Process */
MI_CONST MI_ClassDecl MSFT_Process_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D730C, /* code */
    MI_T("MSFT_Process"), /* name */
    MSFT_Process_quals, /* qualifiers */
    MI_COUNT(MSFT_Process_quals), /* numQualifiers */
    MSFT_Process_props, /* properties */
    MI_COUNT(MSFT_Process_props), /* numProperties */
    sizeof(MSFT_Process), /* size */
    MI_T("CIM_Process"), /* superClass */
    &CIM_Process_rtti, /* superClassDecl */
    MSFT_Process_meths, /* methods */
    MI_COUNT(MSFT_Process_meths), /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** Inner
**
**==============================================================================
*/

/* property Inner.Key */
static MI_CONST MI_PropertyDecl Inner_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Inner, Key), /* offset */
    MI_T("Inner"), /* origin */
    MI_T("Inner"), /* propagator */
    NULL,
};

/* property Inner.Str */
static MI_CONST MI_PropertyDecl Inner_Str_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737203, /* code */
    MI_T("Str"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Inner, Str), /* offset */
    MI_T("Inner"), /* origin */
    MI_T("Inner"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Inner_props[] =
{
    &Inner_Key_prop,
    &Inner_Str_prop,
};

/* class Inner */
MI_CONST MI_ClassDecl Inner_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00697205, /* code */
    MI_T("Inner"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Inner_props, /* properties */
    MI_COUNT(Inner_props), /* numProperties */
    sizeof(Inner), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** Outer
**
**==============================================================================
*/

/* property Outer.Key */
static MI_CONST MI_PropertyDecl Outer_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, Key), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.booleanScalar */
static MI_CONST MI_PropertyDecl Outer_booleanScalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062720D, /* code */
    MI_T("booleanScalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, booleanScalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint8Scalar */
static MI_CONST MI_PropertyDecl Outer_uint8Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075720B, /* code */
    MI_T("uint8Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint8Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint8Scalar */
static MI_CONST MI_PropertyDecl Outer_sint8Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720B, /* code */
    MI_T("sint8Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint8Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint16Scalar */
static MI_CONST MI_PropertyDecl Outer_uint16Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075720C, /* code */
    MI_T("uint16Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint16Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint16Scalar */
static MI_CONST MI_PropertyDecl Outer_sint16Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("sint16Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint16Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint32Scalar */
static MI_CONST MI_PropertyDecl Outer_uint32Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075720C, /* code */
    MI_T("uint32Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint32Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint32Scalar */
static MI_CONST MI_PropertyDecl Outer_sint32Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("sint32Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint32Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint64Scalar */
static MI_CONST MI_PropertyDecl Outer_uint64Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075720C, /* code */
    MI_T("uint64Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint64Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint64Scalar */
static MI_CONST MI_PropertyDecl Outer_sint64Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("sint64Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint64Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.real32Scalar */
static MI_CONST MI_PropertyDecl Outer_real32Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072720C, /* code */
    MI_T("real32Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, real32Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.real64Scalar */
static MI_CONST MI_PropertyDecl Outer_real64Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072720C, /* code */
    MI_T("real64Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, real64Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.char16Scalar */
static MI_CONST MI_PropertyDecl Outer_char16Scalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063720C, /* code */
    MI_T("char16Scalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, char16Scalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.datetimeScalar */
static MI_CONST MI_PropertyDecl Outer_datetimeScalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064720E, /* code */
    MI_T("datetimeScalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, datetimeScalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.stringScalar */
static MI_CONST MI_PropertyDecl Outer_stringScalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("stringScalar"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, stringScalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Outer_instanceScalar_EmbeddedInstance_qual_value = MI_T("Inner");

static MI_CONST MI_Qualifier Outer_instanceScalar_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Outer_instanceScalar_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Outer_instanceScalar_quals[] =
{
    &Outer_instanceScalar_EmbeddedInstance_qual,
};

/* property Outer.instanceScalar */
static MI_CONST MI_PropertyDecl Outer_instanceScalar_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069720E, /* code */
    MI_T("instanceScalar"), /* name */
    Outer_instanceScalar_quals, /* qualifiers */
    MI_COUNT(Outer_instanceScalar_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Inner"), /* className */
    0, /* subscript */
    offsetof(Outer, instanceScalar), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.booleanArray */
static MI_CONST MI_PropertyDecl Outer_booleanArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062790C, /* code */
    MI_T("booleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, booleanArray), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint8Array */
static MI_CONST MI_PropertyDecl Outer_uint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790A, /* code */
    MI_T("uint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint8Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint8Array */
static MI_CONST MI_PropertyDecl Outer_sint8Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790A, /* code */
    MI_T("sint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint8Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint16Array */
static MI_CONST MI_PropertyDecl Outer_uint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint16Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint16Array */
static MI_CONST MI_PropertyDecl Outer_sint16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint16Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint32Array */
static MI_CONST MI_PropertyDecl Outer_uint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint32Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint32Array */
static MI_CONST MI_PropertyDecl Outer_sint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint32Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.uint64Array */
static MI_CONST MI_PropertyDecl Outer_uint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, uint64Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.sint64Array */
static MI_CONST MI_PropertyDecl Outer_sint64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, sint64Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.real32Array */
static MI_CONST MI_PropertyDecl Outer_real32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("real32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, real32Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.real64Array */
static MI_CONST MI_PropertyDecl Outer_real64Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790B, /* code */
    MI_T("real64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, real64Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.char16Array */
static MI_CONST MI_PropertyDecl Outer_char16Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063790B, /* code */
    MI_T("char16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, char16Array), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.datetimeArray */
static MI_CONST MI_PropertyDecl Outer_datetimeArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064790D, /* code */
    MI_T("datetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, datetimeArray), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

/* property Outer.stringArray */
static MI_CONST MI_PropertyDecl Outer_stringArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("stringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Outer, stringArray), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Outer_instanceArray_EmbeddedInstance_qual_value = MI_T("Inner");

static MI_CONST MI_Qualifier Outer_instanceArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Outer_instanceArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Outer_instanceArray_quals[] =
{
    &Outer_instanceArray_EmbeddedInstance_qual,
};

/* property Outer.instanceArray */
static MI_CONST MI_PropertyDecl Outer_instanceArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069790D, /* code */
    MI_T("instanceArray"), /* name */
    Outer_instanceArray_quals, /* qualifiers */
    MI_COUNT(Outer_instanceArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Inner"), /* className */
    0, /* subscript */
    offsetof(Outer, instanceArray), /* offset */
    MI_T("Outer"), /* origin */
    MI_T("Outer"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Outer_props[] =
{
    &Outer_Key_prop,
    &Outer_booleanScalar_prop,
    &Outer_uint8Scalar_prop,
    &Outer_sint8Scalar_prop,
    &Outer_uint16Scalar_prop,
    &Outer_sint16Scalar_prop,
    &Outer_uint32Scalar_prop,
    &Outer_sint32Scalar_prop,
    &Outer_uint64Scalar_prop,
    &Outer_sint64Scalar_prop,
    &Outer_real32Scalar_prop,
    &Outer_real64Scalar_prop,
    &Outer_char16Scalar_prop,
    &Outer_datetimeScalar_prop,
    &Outer_stringScalar_prop,
    &Outer_instanceScalar_prop,
    &Outer_booleanArray_prop,
    &Outer_uint8Array_prop,
    &Outer_sint8Array_prop,
    &Outer_uint16Array_prop,
    &Outer_sint16Array_prop,
    &Outer_uint32Array_prop,
    &Outer_sint32Array_prop,
    &Outer_uint64Array_prop,
    &Outer_sint64Array_prop,
    &Outer_real32Array_prop,
    &Outer_real64Array_prop,
    &Outer_char16Array_prop,
    &Outer_datetimeArray_prop,
    &Outer_stringArray_prop,
    &Outer_instanceArray_prop,
};

/* class Outer */
MI_CONST MI_ClassDecl Outer_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F7205, /* code */
    MI_T("Outer"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Outer_props, /* properties */
    MI_COUNT(Outer_props), /* numProperties */
    sizeof(Outer), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** Octet
**
**==============================================================================
*/

static MI_CONST MI_Boolean Octet_array_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier Octet_array_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Octet_array_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Octet_array_quals[] =
{
    &Octet_array_Octetstring_qual,
};

/* property Octet.array */
static MI_CONST MI_PropertyDecl Octet_array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617905, /* code */
    MI_T("array"), /* name */
    Octet_array_quals, /* qualifiers */
    MI_COUNT(Octet_array_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Octet, array), /* offset */
    MI_T("Octet"), /* origin */
    MI_T("Octet"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Octet_props[] =
{
    &Octet_array_prop,
};

/* class Octet */
MI_CONST MI_ClassDecl Octet_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F7405, /* code */
    MI_T("Octet"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Octet_props, /* properties */
    MI_COUNT(Octet_props), /* numProperties */
    sizeof(Octet), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &test_repos_classDecl, /* schema */
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
    &CIM_ConcreteJob_rtti,
    &CIM_EnabledLogicalElement_rtti,
    &CIM_Job_rtti,
    &CIM_LogicalElement_rtti,
    &CIM_ManagedElement_rtti,
    &CIM_ManagedSystemElement_rtti,
    &CIM_Process_rtti,
    &Inner_rtti,
    &MSFT_AllTypes_rtti,
    &MSFT_Person_rtti,
    &MSFT_Process_rtti,
    &Outer_rtti,
    &Octet_rtti,
};

MI_SchemaDecl test_repos_classDecl =
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

