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
#include "Class1.h"
#include "Class2.h"
#include "Widget.h"
#include "Gadget.h"
#include "Link.h"
#include "Container.h"
#include "Assoc1.h"
#include "SubClass.h"
#include "Thing.h"

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

static MI_CONST MI_QualifierDecl Color_qual_decl =
{
    MI_T("Color"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Colors_qual_decl =
{
    MI_T("Colors"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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

static MI_CONST MI_QualifierDecl Flag_qual_decl =
{
    MI_T("Flag"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
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
    &Color_qual_decl,
    &Colors_qual_decl,
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
    &Flag_qual_decl,
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
** Class1
**
**==============================================================================
*/

static MI_CONST MI_Boolean Class1_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Class1_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Class1_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Class1_Key_quals[] =
{
    &Class1_Key_Key_qual,
};

/* property Class1.Key */
static MI_CONST MI_PropertyDecl Class1_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Class1_Key_quals, /* qualifiers */
    MI_COUNT(Class1_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Key), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Msg */
static MI_CONST MI_PropertyDecl Class1_Msg_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6703, /* code */
    MI_T("Msg"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Msg), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Flag */
static MI_CONST MI_PropertyDecl Class1_Flag_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666704, /* code */
    MI_T("Flag"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Flag), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Numbers */
static MI_CONST MI_PropertyDecl Class1_Numbers_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7307, /* code */
    MI_T("Numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Numbers), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.AlwaysNullProperty */
static MI_CONST MI_PropertyDecl Class1_AlwaysNullProperty_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617912, /* code */
    MI_T("AlwaysNullProperty"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, AlwaysNullProperty), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Colors */
static MI_CONST MI_PropertyDecl Class1_Colors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637306, /* code */
    MI_T("Colors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Colors), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Unprintable */
static MI_CONST MI_PropertyDecl Class1_Unprintable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075650B, /* code */
    MI_T("Unprintable"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Unprintable), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

/* property Class1.Char */
static MI_CONST MI_PropertyDecl Class1_Char_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637204, /* code */
    MI_T("Char"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class1, Char), /* offset */
    MI_T("Class1"), /* origin */
    MI_T("Class1"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Class1_props[] =
{
    &Class1_Key_prop,
    &Class1_Msg_prop,
    &Class1_Flag_prop,
    &Class1_Numbers_prop,
    &Class1_AlwaysNullProperty_prop,
    &Class1_Colors_prop,
    &Class1_Unprintable_prop,
    &Class1_Char_prop,
};

/* class Class1 */
MI_CONST static MI_ClassDecl Class1_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00633106, /* code */
    MI_T("Class1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Class1_props, /* properties */
    MI_COUNT(Class1_props), /* numProperties */
    sizeof(Class1), /* size */
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
** Class2
**
**==============================================================================
*/

static MI_CONST MI_Boolean Class2_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Class2_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Class2_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Class2_Key_quals[] =
{
    &Class2_Key_Key_qual,
};

/* property Class2.Key */
static MI_CONST MI_PropertyDecl Class2_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Class2_Key_quals, /* qualifiers */
    MI_COUNT(Class2_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, Key), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.B */
static MI_CONST MI_PropertyDecl Class2_B_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626201, /* code */
    MI_T("B"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, B), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U8 */
static MI_CONST MI_PropertyDecl Class2_U8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753802, /* code */
    MI_T("U8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U8), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S8 */
static MI_CONST MI_PropertyDecl Class2_S8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733802, /* code */
    MI_T("S8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S8), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U16 */
static MI_CONST MI_PropertyDecl Class2_U16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753603, /* code */
    MI_T("U16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U16), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S16 */
static MI_CONST MI_PropertyDecl Class2_S16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733603, /* code */
    MI_T("S16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S16), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U32 */
static MI_CONST MI_PropertyDecl Class2_U32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753203, /* code */
    MI_T("U32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U32), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S32 */
static MI_CONST MI_PropertyDecl Class2_S32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733203, /* code */
    MI_T("S32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S32), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U64 */
static MI_CONST MI_PropertyDecl Class2_U64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753403, /* code */
    MI_T("U64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U64), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S64 */
static MI_CONST MI_PropertyDecl Class2_S64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733403, /* code */
    MI_T("S64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S64), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.R32 */
static MI_CONST MI_PropertyDecl Class2_R32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723203, /* code */
    MI_T("R32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, R32), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.R64 */
static MI_CONST MI_PropertyDecl Class2_R64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723403, /* code */
    MI_T("R64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, R64), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.DT1 */
static MI_CONST MI_PropertyDecl Class2_DT1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643103, /* code */
    MI_T("DT1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, DT1), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.DT2 */
static MI_CONST MI_PropertyDecl Class2_DT2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643203, /* code */
    MI_T("DT2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, DT2), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S */
static MI_CONST MI_PropertyDecl Class2_S_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737301, /* code */
    MI_T("S"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.C16 */
static MI_CONST MI_PropertyDecl Class2_C16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00633603, /* code */
    MI_T("C16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, C16), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.BA */
static MI_CONST MI_PropertyDecl Class2_BA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626102, /* code */
    MI_T("BA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, BA), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U8A */
static MI_CONST MI_PropertyDecl Class2_U8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756103, /* code */
    MI_T("U8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U8A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S8A */
static MI_CONST MI_PropertyDecl Class2_S8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736103, /* code */
    MI_T("S8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S8A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U16A */
static MI_CONST MI_PropertyDecl Class2_U16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U16A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S16A */
static MI_CONST MI_PropertyDecl Class2_S16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S16A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U32A */
static MI_CONST MI_PropertyDecl Class2_U32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U32A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S32A */
static MI_CONST MI_PropertyDecl Class2_S32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S32A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.U64A */
static MI_CONST MI_PropertyDecl Class2_U64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, U64A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.S64A */
static MI_CONST MI_PropertyDecl Class2_S64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, S64A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.R32A */
static MI_CONST MI_PropertyDecl Class2_R32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("R32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, R32A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.R64A */
static MI_CONST MI_PropertyDecl Class2_R64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("R64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, R64A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.DTA */
static MI_CONST MI_PropertyDecl Class2_DTA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646103, /* code */
    MI_T("DTA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, DTA), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.SA */
static MI_CONST MI_PropertyDecl Class2_SA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736102, /* code */
    MI_T("SA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, SA), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

/* property Class2.C16A */
static MI_CONST MI_PropertyDecl Class2_C16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636104, /* code */
    MI_T("C16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Class2, C16A), /* offset */
    MI_T("Class2"), /* origin */
    MI_T("Class2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Class2_props[] =
{
    &Class2_Key_prop,
    &Class2_B_prop,
    &Class2_U8_prop,
    &Class2_S8_prop,
    &Class2_U16_prop,
    &Class2_S16_prop,
    &Class2_U32_prop,
    &Class2_S32_prop,
    &Class2_U64_prop,
    &Class2_S64_prop,
    &Class2_R32_prop,
    &Class2_R64_prop,
    &Class2_DT1_prop,
    &Class2_DT2_prop,
    &Class2_S_prop,
    &Class2_C16_prop,
    &Class2_BA_prop,
    &Class2_U8A_prop,
    &Class2_S8A_prop,
    &Class2_U16A_prop,
    &Class2_S16A_prop,
    &Class2_U32A_prop,
    &Class2_S32A_prop,
    &Class2_U64A_prop,
    &Class2_S64A_prop,
    &Class2_R32A_prop,
    &Class2_R64A_prop,
    &Class2_DTA_prop,
    &Class2_SA_prop,
    &Class2_C16A_prop,
};

/* class Class2 */
MI_CONST static MI_ClassDecl Class2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00633206, /* code */
    MI_T("Class2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Class2_props, /* properties */
    MI_COUNT(Class2_props), /* numProperties */
    sizeof(Class2), /* size */
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
** Embedded
**
**==============================================================================
*/

static MI_CONST MI_Boolean Embedded_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Embedded_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Embedded_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Embedded_Key_quals[] =
{
    &Embedded_Key_Key_qual,
};

/* property Embedded.Key */
static MI_CONST MI_PropertyDecl Embedded_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Embedded_Key_quals, /* qualifiers */
    MI_COUNT(Embedded_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Embedded, Key), /* offset */
    MI_T("Embedded"), /* origin */
    MI_T("Embedded"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Embedded_props[] =
{
    &Embedded_Key_prop,
};

/* class Embedded */
MI_CONST static MI_ClassDecl Embedded_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00656408, /* code */
    MI_T("Embedded"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Embedded_props, /* properties */
    MI_COUNT(Embedded_props), /* numProperties */
    sizeof(Embedded), /* size */
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
** Widget
**
**==============================================================================
*/

static MI_CONST MI_Boolean Widget_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Widget_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Widget_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Widget_Key_quals[] =
{
    &Widget_Key_Key_qual,
};

/* property Widget.Key */
static MI_CONST MI_PropertyDecl Widget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Widget_Key_quals, /* qualifiers */
    MI_COUNT(Widget_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Key), /* offset */
    MI_T("Widget"), /* origin */
    MI_T("Widget"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Widget_Emb_EmbeddedInstance_qual_value = MI_T("Embedded");

static MI_CONST MI_Qualifier Widget_Emb_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Widget_Emb_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Widget_Emb_quals[] =
{
    &Widget_Emb_EmbeddedInstance_qual,
};

/* property Widget.Emb */
static MI_CONST MI_PropertyDecl Widget_Emb_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656203, /* code */
    MI_T("Emb"), /* name */
    Widget_Emb_quals, /* qualifiers */
    MI_COUNT(Widget_Emb_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Embedded"), /* className */
    0, /* subscript */
    offsetof(Widget, Emb), /* offset */
    MI_T("Widget"), /* origin */
    MI_T("Widget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Widget_props[] =
{
    &Widget_Key_prop,
    &Widget_Emb_prop,
};

/* class Widget */
MI_CONST static MI_ClassDecl Widget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00777406, /* code */
    MI_T("Widget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Widget_props, /* properties */
    MI_COUNT(Widget_props), /* numProperties */
    sizeof(Widget), /* size */
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
** Gadget
**
**==============================================================================
*/

static MI_CONST MI_Boolean Gadget_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Gadget_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Gadget_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Gadget_Key_quals[] =
{
    &Gadget_Key_Key_qual,
};

/* property Gadget.Key */
static MI_CONST MI_PropertyDecl Gadget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Gadget_Key_quals, /* qualifiers */
    MI_COUNT(Gadget_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, Key), /* offset */
    MI_T("Gadget"), /* origin */
    MI_T("Gadget"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Gadget_Emb_EmbeddedInstance_qual_value = MI_T("Embedded");

static MI_CONST MI_Qualifier Gadget_Emb_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Gadget_Emb_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Gadget_Emb_quals[] =
{
    &Gadget_Emb_EmbeddedInstance_qual,
};

/* property Gadget.Emb */
static MI_CONST MI_PropertyDecl Gadget_Emb_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656203, /* code */
    MI_T("Emb"), /* name */
    Gadget_Emb_quals, /* qualifiers */
    MI_COUNT(Gadget_Emb_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Embedded"), /* className */
    0, /* subscript */
    offsetof(Gadget, Emb), /* offset */
    MI_T("Gadget"), /* origin */
    MI_T("Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Gadget_props[] =
{
    &Gadget_Key_prop,
    &Gadget_Emb_prop,
};

/* class Gadget */
MI_CONST static MI_ClassDecl Gadget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00677406, /* code */
    MI_T("Gadget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Gadget_props, /* properties */
    MI_COUNT(Gadget_props), /* numProperties */
    sizeof(Gadget), /* size */
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
** Link
**
**==============================================================================
*/

static MI_CONST MI_Boolean Link_Left_Key_qual_value = 1;

static MI_CONST MI_Qualifier Link_Left_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Link_Left_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Link_Left_quals[] =
{
    &Link_Left_Key_qual,
};

/* property Link.Left */
static MI_CONST MI_PropertyDecl Link_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    Link_Left_quals, /* qualifiers */
    MI_COUNT(Link_Left_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Link, Left), /* offset */
    MI_T("Link"), /* origin */
    MI_T("Link"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean Link_Right_Key_qual_value = 1;

static MI_CONST MI_Qualifier Link_Right_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Link_Right_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Link_Right_quals[] =
{
    &Link_Right_Key_qual,
};

/* property Link.Right */
static MI_CONST MI_PropertyDecl Link_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    Link_Right_quals, /* qualifiers */
    MI_COUNT(Link_Right_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Link, Right), /* offset */
    MI_T("Link"), /* origin */
    MI_T("Link"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Link_props[] =
{
    &Link_Left_prop,
    &Link_Right_prop,
};

static MI_CONST MI_Boolean Link_Association_qual_value = 1;

static MI_CONST MI_Qualifier Link_Association_qual =
{
    MI_T("Association"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Link_Association_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Link_quals[] =
{
    &Link_Association_qual,
};

/* class Link */
MI_CONST static MI_ClassDecl Link_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x006C6B04, /* code */
    MI_T("Link"), /* name */
    Link_quals, /* qualifiers */
    MI_COUNT(Link_quals), /* numQualifiers */
    Link_props, /* properties */
    MI_COUNT(Link_props), /* numProperties */
    sizeof(Link), /* size */
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
** Container
**
**==============================================================================
*/

static MI_CONST MI_Boolean Container_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Container_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Container_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Container_Key_quals[] =
{
    &Container_Key_Key_qual,
};

/* property Container.Key */
static MI_CONST MI_PropertyDecl Container_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Container_Key_quals, /* qualifiers */
    MI_COUNT(Container_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Container, Key), /* offset */
    MI_T("Container"), /* origin */
    MI_T("Container"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Container_Wid_EmbeddedInstance_qual_value = MI_T("Widget");

static MI_CONST MI_Qualifier Container_Wid_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Container_Wid_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Container_Wid_quals[] =
{
    &Container_Wid_EmbeddedInstance_qual,
};

/* property Container.Wid */
static MI_CONST MI_PropertyDecl Container_Wid_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00776403, /* code */
    MI_T("Wid"), /* name */
    Container_Wid_quals, /* qualifiers */
    MI_COUNT(Container_Wid_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Container, Wid), /* offset */
    MI_T("Container"), /* origin */
    MI_T("Container"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Container_Gad_EmbeddedInstance_qual_value = MI_T("Gadget");

static MI_CONST MI_Qualifier Container_Gad_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Container_Gad_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Container_Gad_quals[] =
{
    &Container_Gad_EmbeddedInstance_qual,
};

/* property Container.Gad */
static MI_CONST MI_PropertyDecl Container_Gad_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00676403, /* code */
    MI_T("Gad"), /* name */
    Container_Gad_quals, /* qualifiers */
    MI_COUNT(Container_Gad_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Container, Gad), /* offset */
    MI_T("Container"), /* origin */
    MI_T("Container"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Container_props[] =
{
    &Container_Key_prop,
    &Container_Wid_prop,
    &Container_Gad_prop,
};

/* parameter Container.Foo1(): MIReturn */
static MI_CONST MI_ParameterDecl Container_Foo1_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Container_Foo1, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Container_Foo1_params[] =
{
    &Container_Foo1_MIReturn_param,
};

/* method Container.Foo1() */
MI_CONST MI_MethodDecl Container_Foo1_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00663104, /* code */
    MI_T("Foo1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Container_Foo1_params, /* parameters */
    MI_COUNT(Container_Foo1_params), /* numParameters */
    sizeof(Container_Foo1), /* size */
    MI_UINT32, /* returnType */
    MI_T("Container"), /* origin */
    MI_T("Container"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Boolean Container_Foo2_Wid_In_qual_value = 1;

static MI_CONST MI_Qualifier Container_Foo2_Wid_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Container_Foo2_Wid_In_qual_value
};

static MI_CONST MI_Char* Container_Foo2_Wid_EmbeddedInstance_qual_value = MI_T("Widget");

static MI_CONST MI_Qualifier Container_Foo2_Wid_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Container_Foo2_Wid_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Container_Foo2_Wid_quals[] =
{
    &Container_Foo2_Wid_In_qual,
    &Container_Foo2_Wid_EmbeddedInstance_qual,
};

/* parameter Container.Foo2(): Wid */
static MI_CONST MI_ParameterDecl Container_Foo2_Wid_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00776403, /* code */
    MI_T("Wid"), /* name */
    Container_Foo2_Wid_quals, /* qualifiers */
    MI_COUNT(Container_Foo2_Wid_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Container_Foo2, Wid), /* offset */
};

static MI_CONST MI_Boolean Container_Foo2_Gad_In_qual_value = 0;

static MI_CONST MI_Qualifier Container_Foo2_Gad_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Container_Foo2_Gad_In_qual_value
};

static MI_CONST MI_Boolean Container_Foo2_Gad_Out_qual_value = 1;

static MI_CONST MI_Qualifier Container_Foo2_Gad_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Container_Foo2_Gad_Out_qual_value
};

static MI_CONST MI_Char* Container_Foo2_Gad_EmbeddedInstance_qual_value = MI_T("Gadget");

static MI_CONST MI_Qualifier Container_Foo2_Gad_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Container_Foo2_Gad_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Container_Foo2_Gad_quals[] =
{
    &Container_Foo2_Gad_In_qual,
    &Container_Foo2_Gad_Out_qual,
    &Container_Foo2_Gad_EmbeddedInstance_qual,
};

/* parameter Container.Foo2(): Gad */
static MI_CONST MI_ParameterDecl Container_Foo2_Gad_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00676403, /* code */
    MI_T("Gad"), /* name */
    Container_Foo2_Gad_quals, /* qualifiers */
    MI_COUNT(Container_Foo2_Gad_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Container_Foo2, Gad), /* offset */
};

/* parameter Container.Foo2(): MIReturn */
static MI_CONST MI_ParameterDecl Container_Foo2_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Container_Foo2, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Container_Foo2_params[] =
{
    &Container_Foo2_MIReturn_param,
    &Container_Foo2_Wid_param,
    &Container_Foo2_Gad_param,
};

/* method Container.Foo2() */
MI_CONST MI_MethodDecl Container_Foo2_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00663204, /* code */
    MI_T("Foo2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Container_Foo2_params, /* parameters */
    MI_COUNT(Container_Foo2_params), /* numParameters */
    sizeof(Container_Foo2), /* size */
    MI_UINT32, /* returnType */
    MI_T("Container"), /* origin */
    MI_T("Container"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Container_meths[] =
{
    &Container_Foo1_rtti,
    &Container_Foo2_rtti,
};

/* class Container */
MI_CONST static MI_ClassDecl Container_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637209, /* code */
    MI_T("Container"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Container_props, /* properties */
    MI_COUNT(Container_props), /* numProperties */
    sizeof(Container), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Container_meths, /* methods */
    MI_COUNT(Container_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Assoc0
**
**==============================================================================
*/

static MI_CONST MI_Boolean Assoc0_Left_Key_qual_value = 1;

static MI_CONST MI_Qualifier Assoc0_Left_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc0_Left_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc0_Left_quals[] =
{
    &Assoc0_Left_Key_qual,
};

/* property Assoc0.Left */
static MI_CONST MI_PropertyDecl Assoc0_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    Assoc0_Left_quals, /* qualifiers */
    MI_COUNT(Assoc0_Left_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Assoc0, Left), /* offset */
    MI_T("Assoc0"), /* origin */
    MI_T("Assoc0"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean Assoc0_Right_Key_qual_value = 1;

static MI_CONST MI_Qualifier Assoc0_Right_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc0_Right_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc0_Right_quals[] =
{
    &Assoc0_Right_Key_qual,
};

/* property Assoc0.Right */
static MI_CONST MI_PropertyDecl Assoc0_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    Assoc0_Right_quals, /* qualifiers */
    MI_COUNT(Assoc0_Right_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Assoc0, Right), /* offset */
    MI_T("Assoc0"), /* origin */
    MI_T("Assoc0"), /* propagator */
    NULL,
};

/* property Assoc0.Inherited */
static MI_CONST MI_PropertyDecl Assoc0_Inherited_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696409, /* code */
    MI_T("Inherited"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc0, Inherited), /* offset */
    MI_T("Assoc0"), /* origin */
    MI_T("Assoc0"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Assoc0_props[] =
{
    &Assoc0_Left_prop,
    &Assoc0_Right_prop,
    &Assoc0_Inherited_prop,
};

static MI_CONST MI_Boolean Assoc0_Association_qual_value = 1;

static MI_CONST MI_Qualifier Assoc0_Association_qual =
{
    MI_T("Association"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc0_Association_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc0_quals[] =
{
    &Assoc0_Association_qual,
};

/* class Assoc0 */
MI_CONST static MI_ClassDecl Assoc0_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00613006, /* code */
    MI_T("Assoc0"), /* name */
    Assoc0_quals, /* qualifiers */
    MI_COUNT(Assoc0_quals), /* numQualifiers */
    Assoc0_props, /* properties */
    MI_COUNT(Assoc0_props), /* numProperties */
    sizeof(Assoc0), /* size */
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
** Assoc1
**
**==============================================================================
*/

static MI_CONST MI_Boolean Assoc1_Left_Key_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Left_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Left_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Left_quals[] =
{
    &Assoc1_Left_Key_qual,
};

/* property Assoc1.Left */
static MI_CONST MI_PropertyDecl Assoc1_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    Assoc1_Left_quals, /* qualifiers */
    MI_COUNT(Assoc1_Left_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Assoc1, Left), /* offset */
    MI_T("Assoc0"), /* origin */
    MI_T("Assoc1"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean Assoc1_B_value = 1;

/* property Assoc1.B */
static MI_CONST MI_PropertyDecl Assoc1_B_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626201, /* code */
    MI_T("B"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, B), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_B_value,
};

static MI_CONST MI_Char* Assoc1_U8_Values_qual_data_value[] =
{
    MI_T("PINK"),
    MI_T("CYAN"),
    MI_T("MAGENTA"),
};

static MI_CONST MI_ConstStringA Assoc1_U8_Values_qual_value =
{
    Assoc1_U8_Values_qual_data_value,
    MI_COUNT(Assoc1_U8_Values_qual_data_value),
};

static MI_CONST MI_Qualifier Assoc1_U8_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Assoc1_U8_Values_qual_value
};

static MI_CONST MI_Char* Assoc1_U8_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
};

static MI_CONST MI_ConstStringA Assoc1_U8_ValueMap_qual_value =
{
    Assoc1_U8_ValueMap_qual_data_value,
    MI_COUNT(Assoc1_U8_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier Assoc1_U8_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    0,
    &Assoc1_U8_ValueMap_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_U8_quals[] =
{
    &Assoc1_U8_Values_qual,
    &Assoc1_U8_ValueMap_qual,
};

static MI_CONST MI_Uint8 Assoc1_U8_value = 8;

/* property Assoc1.U8 */
static MI_CONST MI_PropertyDecl Assoc1_U8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753802, /* code */
    MI_T("U8"), /* name */
    Assoc1_U8_quals, /* qualifiers */
    MI_COUNT(Assoc1_U8_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U8), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U8_value,
};

static MI_CONST MI_Char* Assoc1_S8_Colors_qual_data_value[] =
{
    MI_T("RED"),
    MI_T("GREEN"),
    MI_T("BLUE"),
};

static MI_CONST MI_ConstStringA Assoc1_S8_Colors_qual_value =
{
    Assoc1_S8_Colors_qual_data_value,
    MI_COUNT(Assoc1_S8_Colors_qual_data_value),
};

static MI_CONST MI_Qualifier Assoc1_S8_Colors_qual =
{
    MI_T("Colors"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_S8_Colors_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_S8_quals[] =
{
    &Assoc1_S8_Colors_qual,
};

static MI_CONST MI_Sint8 Assoc1_S8_value = -8;

/* property Assoc1.S8 */
static MI_CONST MI_PropertyDecl Assoc1_S8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733802, /* code */
    MI_T("S8"), /* name */
    Assoc1_S8_quals, /* qualifiers */
    MI_COUNT(Assoc1_S8_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S8), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S8_value,
};

static MI_CONST MI_Uint16 Assoc1_U16_value = 16;

/* property Assoc1.U16 */
static MI_CONST MI_PropertyDecl Assoc1_U16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753603, /* code */
    MI_T("U16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U16), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U16_value,
};

static MI_CONST MI_Sint16 Assoc1_S16_value = -16;

/* property Assoc1.S16 */
static MI_CONST MI_PropertyDecl Assoc1_S16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733603, /* code */
    MI_T("S16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S16), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S16_value,
};

static MI_CONST MI_Uint32 Assoc1_U32_value = 32U;

/* property Assoc1.U32 */
static MI_CONST MI_PropertyDecl Assoc1_U32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753203, /* code */
    MI_T("U32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U32), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U32_value,
};

static MI_CONST MI_Sint32 Assoc1_S32_value = -32;

/* property Assoc1.S32 */
static MI_CONST MI_PropertyDecl Assoc1_S32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733203, /* code */
    MI_T("S32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S32), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S32_value,
};

static MI_CONST MI_Uint64 Assoc1_U64_value = MI_ULL(64);

/* property Assoc1.U64 */
static MI_CONST MI_PropertyDecl Assoc1_U64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753403, /* code */
    MI_T("U64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U64), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U64_value,
};

static MI_CONST MI_Sint64 Assoc1_S64_value = -MI_LL(64);

/* property Assoc1.S64 */
static MI_CONST MI_PropertyDecl Assoc1_S64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733403, /* code */
    MI_T("S64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S64), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S64_value,
};

static MI_CONST MI_Real32 Assoc1_R32_value = (float)0;

/* property Assoc1.R32 */
static MI_CONST MI_PropertyDecl Assoc1_R32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723203, /* code */
    MI_T("R32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, R32), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_R32_value,
};

static MI_CONST MI_Real64 Assoc1_R64_value = (double)0;

/* property Assoc1.R64 */
static MI_CONST MI_PropertyDecl Assoc1_R64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723403, /* code */
    MI_T("R64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, R64), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_R64_value,
};

static MI_CONST MI_Datetime Assoc1_DT1_value = {1,{{2010,12,25,12,30,11,123456,-360}}};

/* property Assoc1.DT1 */
static MI_CONST MI_PropertyDecl Assoc1_DT1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643103, /* code */
    MI_T("DT1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, DT1), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_DT1_value,
};

static MI_CONST MI_Datetime Assoc1_DT2_value = {0,{{12345678,15,16,17,123456}}};

/* property Assoc1.DT2 */
static MI_CONST MI_PropertyDecl Assoc1_DT2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643203, /* code */
    MI_T("DT2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, DT2), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_DT2_value,
};

static MI_CONST MI_Char* Assoc1_S_value = MI_T("My String");

/* property Assoc1.S */
static MI_CONST MI_PropertyDecl Assoc1_S_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737301, /* code */
    MI_T("S"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S_value,
};

static MI_CONST MI_Char16 Assoc1_C16_value = 65;

/* property Assoc1.C16 */
static MI_CONST MI_PropertyDecl Assoc1_C16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00633603, /* code */
    MI_T("C16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, C16), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_C16_value,
};

static MI_CONST MI_Boolean Assoc1_BA_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA Assoc1_BA_value =
{
    Assoc1_BA_data_value,
    MI_COUNT(Assoc1_BA_data_value),
};

/* property Assoc1.BA */
static MI_CONST MI_PropertyDecl Assoc1_BA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626102, /* code */
    MI_T("BA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, BA), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_BA_value,
};

static MI_CONST MI_Uint8 Assoc1_U8A_data_value[] =
{
    8,
};

static MI_CONST MI_ConstUint8A Assoc1_U8A_value =
{
    Assoc1_U8A_data_value,
    MI_COUNT(Assoc1_U8A_data_value),
};

/* property Assoc1.U8A */
static MI_CONST MI_PropertyDecl Assoc1_U8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756103, /* code */
    MI_T("U8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U8A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U8A_value,
};

static MI_CONST MI_Sint8 Assoc1_S8A_data_value[] =
{
    -8,
    0,
    8,
};

static MI_CONST MI_ConstSint8A Assoc1_S8A_value =
{
    Assoc1_S8A_data_value,
    MI_COUNT(Assoc1_S8A_data_value),
};

/* property Assoc1.S8A */
static MI_CONST MI_PropertyDecl Assoc1_S8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736103, /* code */
    MI_T("S8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S8A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S8A_value,
};

static MI_CONST MI_Uint16 Assoc1_U16A_data_value[] =
{
    16,
};

static MI_CONST MI_ConstUint16A Assoc1_U16A_value =
{
    Assoc1_U16A_data_value,
    MI_COUNT(Assoc1_U16A_data_value),
};

/* property Assoc1.U16A */
static MI_CONST MI_PropertyDecl Assoc1_U16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U16A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U16A_value,
};

static MI_CONST MI_Sint16 Assoc1_S16A_data_value[] =
{
    -16,
    0,
    16,
};

static MI_CONST MI_ConstSint16A Assoc1_S16A_value =
{
    Assoc1_S16A_data_value,
    MI_COUNT(Assoc1_S16A_data_value),
};

/* property Assoc1.S16A */
static MI_CONST MI_PropertyDecl Assoc1_S16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S16A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S16A_value,
};

static MI_CONST MI_Uint32 Assoc1_U32A_data_value[] =
{
    32U,
};

static MI_CONST MI_ConstUint32A Assoc1_U32A_value =
{
    Assoc1_U32A_data_value,
    MI_COUNT(Assoc1_U32A_data_value),
};

/* property Assoc1.U32A */
static MI_CONST MI_PropertyDecl Assoc1_U32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U32A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U32A_value,
};

static MI_CONST MI_Sint32 Assoc1_S32A_data_value[] =
{
    -32,
    0,
    32,
};

static MI_CONST MI_ConstSint32A Assoc1_S32A_value =
{
    Assoc1_S32A_data_value,
    MI_COUNT(Assoc1_S32A_data_value),
};

/* property Assoc1.S32A */
static MI_CONST MI_PropertyDecl Assoc1_S32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S32A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S32A_value,
};

static MI_CONST MI_Uint64 Assoc1_U64A_data_value[] =
{
    MI_ULL(64),
};

static MI_CONST MI_ConstUint64A Assoc1_U64A_value =
{
    Assoc1_U64A_data_value,
    MI_COUNT(Assoc1_U64A_data_value),
};

/* property Assoc1.U64A */
static MI_CONST MI_PropertyDecl Assoc1_U64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("U64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, U64A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_U64A_value,
};

static MI_CONST MI_Sint64 Assoc1_S64A_data_value[] =
{
    -MI_LL(64),
    MI_LL(0),
    MI_LL(64),
};

static MI_CONST MI_ConstSint64A Assoc1_S64A_value =
{
    Assoc1_S64A_data_value,
    MI_COUNT(Assoc1_S64A_data_value),
};

/* property Assoc1.S64A */
static MI_CONST MI_PropertyDecl Assoc1_S64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("S64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, S64A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_S64A_value,
};

static MI_CONST MI_Real32 Assoc1_R32A_data_value[] =
{
    (float)0,
};

static MI_CONST MI_ConstReal32A Assoc1_R32A_value =
{
    Assoc1_R32A_data_value,
    MI_COUNT(Assoc1_R32A_data_value),
};

/* property Assoc1.R32A */
static MI_CONST MI_PropertyDecl Assoc1_R32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("R32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, R32A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_R32A_value,
};

static MI_CONST MI_Real64 Assoc1_R64A_data_value[] =
{
    (double)0,
};

static MI_CONST MI_ConstReal64A Assoc1_R64A_value =
{
    Assoc1_R64A_data_value,
    MI_COUNT(Assoc1_R64A_data_value),
};

/* property Assoc1.R64A */
static MI_CONST MI_PropertyDecl Assoc1_R64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("R64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, R64A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_R64A_value,
};

static MI_CONST MI_Datetime Assoc1_DTA_data_value[] =
{
    {1,{{2010,12,25,12,30,11,123456,-360}}},
    {0,{{12345678,15,16,17,123456}}},
};

static MI_CONST MI_ConstDatetimeA Assoc1_DTA_value =
{
    Assoc1_DTA_data_value,
    MI_COUNT(Assoc1_DTA_data_value),
};

/* property Assoc1.DTA */
static MI_CONST MI_PropertyDecl Assoc1_DTA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646103, /* code */
    MI_T("DTA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, DTA), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_DTA_value,
};

static MI_CONST MI_Char* Assoc1_SA_data_value[] =
{
    MI_T("One"),
    MI_T("Two"),
};

static MI_CONST MI_ConstStringA Assoc1_SA_value =
{
    Assoc1_SA_data_value,
    MI_COUNT(Assoc1_SA_data_value),
};

/* property Assoc1.SA */
static MI_CONST MI_PropertyDecl Assoc1_SA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736102, /* code */
    MI_T("SA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, SA), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_SA_value,
};

static MI_CONST MI_Char16 Assoc1_C16A_data_value[] =
{
    65,
    66,
    67,
};

static MI_CONST MI_ConstChar16A Assoc1_C16A_value =
{
    Assoc1_C16A_data_value,
    MI_COUNT(Assoc1_C16A_data_value),
};

/* property Assoc1.C16A */
static MI_CONST MI_PropertyDecl Assoc1_C16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636104, /* code */
    MI_T("C16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1, C16A), /* offset */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &Assoc1_C16A_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST Assoc1_props[] =
{
    &Assoc1_Left_prop,
    &Assoc0_Right_prop,
    &Assoc0_Inherited_prop,
    &Assoc1_B_prop,
    &Assoc1_U8_prop,
    &Assoc1_S8_prop,
    &Assoc1_U16_prop,
    &Assoc1_S16_prop,
    &Assoc1_U32_prop,
    &Assoc1_S32_prop,
    &Assoc1_U64_prop,
    &Assoc1_S64_prop,
    &Assoc1_R32_prop,
    &Assoc1_R64_prop,
    &Assoc1_DT1_prop,
    &Assoc1_DT2_prop,
    &Assoc1_S_prop,
    &Assoc1_C16_prop,
    &Assoc1_BA_prop,
    &Assoc1_U8A_prop,
    &Assoc1_S8A_prop,
    &Assoc1_U16A_prop,
    &Assoc1_S16A_prop,
    &Assoc1_U32A_prop,
    &Assoc1_S32A_prop,
    &Assoc1_U64A_prop,
    &Assoc1_S64A_prop,
    &Assoc1_R32A_prop,
    &Assoc1_R64A_prop,
    &Assoc1_DTA_prop,
    &Assoc1_SA_prop,
    &Assoc1_C16A_prop,
};

static MI_CONST MI_Char* Assoc1_Foo_Description_qual_value = MI_T("Fool");

static MI_CONST MI_Qualifier Assoc1_Foo_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Assoc1_Foo_Description_qual_value
};

static MI_CONST MI_Char* Assoc1_Foo_Color_qual_value = MI_T("Blue");

static MI_CONST MI_Qualifier Assoc1_Foo_Color_qual =
{
    MI_T("Color"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_Color_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo_Static_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_Static_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo_quals[] =
{
    &Assoc1_Foo_Description_qual,
    &Assoc1_Foo_Color_qual,
    &Assoc1_Foo_Static_qual,
};

static MI_CONST MI_Boolean Assoc1_Foo_X_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo_X_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_X_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo_X_quals[] =
{
    &Assoc1_Foo_X_In_qual,
};

/* parameter Assoc1.Foo(): X */
static MI_CONST MI_ParameterDecl Assoc1_Foo_X_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00787801, /* code */
    MI_T("X"), /* name */
    Assoc1_Foo_X_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo_X_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo, X), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo_Y_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo_Y_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_Y_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo_Y_quals[] =
{
    &Assoc1_Foo_Y_In_qual,
};

/* parameter Assoc1.Foo(): Y */
static MI_CONST MI_ParameterDecl Assoc1_Foo_Y_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00797901, /* code */
    MI_T("Y"), /* name */
    Assoc1_Foo_Y_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo_Y_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo, Y), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo_Z_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo_Z_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_Z_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo_Z_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo_Z_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_Z_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo_Z_quals[] =
{
    &Assoc1_Foo_Z_In_qual,
    &Assoc1_Foo_Z_Out_qual,
};

/* parameter Assoc1.Foo(): Z */
static MI_CONST MI_ParameterDecl Assoc1_Foo_Z_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x007A7A01, /* code */
    MI_T("Z"), /* name */
    Assoc1_Foo_Z_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo_Z_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo, Z), /* offset */
};

static MI_CONST MI_Char* Assoc1_Foo_MIReturn_Description_qual_value = MI_T("Fool");

static MI_CONST MI_Qualifier Assoc1_Foo_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Assoc1_Foo_MIReturn_Description_qual_value
};

static MI_CONST MI_Char* Assoc1_Foo_MIReturn_Color_qual_value = MI_T("Blue");

static MI_CONST MI_Qualifier Assoc1_Foo_MIReturn_Color_qual =
{
    MI_T("Color"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_MIReturn_Color_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo_MIReturn_Static_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo_MIReturn_quals[] =
{
    &Assoc1_Foo_MIReturn_Description_qual,
    &Assoc1_Foo_MIReturn_Color_qual,
    &Assoc1_Foo_MIReturn_Static_qual,
};

/* parameter Assoc1.Foo(): MIReturn */
static MI_CONST MI_ParameterDecl Assoc1_Foo_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    Assoc1_Foo_MIReturn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Assoc1_Foo_params[] =
{
    &Assoc1_Foo_MIReturn_param,
    &Assoc1_Foo_X_param,
    &Assoc1_Foo_Y_param,
    &Assoc1_Foo_Z_param,
};

/* method Assoc1.Foo() */
MI_CONST MI_MethodDecl Assoc1_Foo_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00666F03, /* code */
    MI_T("Foo"), /* name */
    Assoc1_Foo_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo_quals), /* numQualifiers */
    Assoc1_Foo_params, /* parameters */
    MI_COUNT(Assoc1_Foo_params), /* numParameters */
    sizeof(Assoc1_Foo), /* size */
    MI_UINT32, /* returnType */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* Assoc1_Foo2_Description_qual_value = MI_T("Foo2");

static MI_CONST MI_Qualifier Assoc1_Foo2_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Assoc1_Foo2_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_quals[] =
{
    &Assoc1_Foo2_Description_qual,
};

static MI_CONST MI_Boolean Assoc1_Foo2_WidIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_WidIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_WidIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_WidIn_quals[] =
{
    &Assoc1_Foo2_WidIn_In_qual,
};

/* parameter Assoc1.Foo2(): WidIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_WidIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00776E05, /* code */
    MI_T("WidIn"), /* name */
    Assoc1_Foo2_WidIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_WidIn_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, WidIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_GadIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_GadIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_GadIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_GadIn_quals[] =
{
    &Assoc1_Foo2_GadIn_In_qual,
};

/* parameter Assoc1.Foo2(): GadIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_GadIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00676E05, /* code */
    MI_T("GadIn"), /* name */
    Assoc1_Foo2_GadIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_GadIn_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, GadIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BIn_quals[] =
{
    &Assoc1_Foo2_BIn_In_qual,
};

/* parameter Assoc1.Foo2(): BIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00626E03, /* code */
    MI_T("BIn"), /* name */
    Assoc1_Foo2_BIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BIn_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8In_quals[] =
{
    &Assoc1_Foo2_U8In_In_qual,
};

/* parameter Assoc1.Foo2(): U8In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E04, /* code */
    MI_T("U8In"), /* name */
    Assoc1_Foo2_U8In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8In_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8In_quals[] =
{
    &Assoc1_Foo2_S8In_In_qual,
};

/* parameter Assoc1.Foo2(): S8In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E04, /* code */
    MI_T("S8In"), /* name */
    Assoc1_Foo2_S8In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8In_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16In_quals[] =
{
    &Assoc1_Foo2_U16In_In_qual,
};

/* parameter Assoc1.Foo2(): U16In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E05, /* code */
    MI_T("U16In"), /* name */
    Assoc1_Foo2_U16In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16In_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16In_quals[] =
{
    &Assoc1_Foo2_S16In_In_qual,
};

/* parameter Assoc1.Foo2(): S16In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E05, /* code */
    MI_T("S16In"), /* name */
    Assoc1_Foo2_S16In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16In_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32In_quals[] =
{
    &Assoc1_Foo2_U32In_In_qual,
};

/* parameter Assoc1.Foo2(): U32In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E05, /* code */
    MI_T("U32In"), /* name */
    Assoc1_Foo2_U32In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32In_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32In_quals[] =
{
    &Assoc1_Foo2_S32In_In_qual,
};

/* parameter Assoc1.Foo2(): S32In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E05, /* code */
    MI_T("S32In"), /* name */
    Assoc1_Foo2_S32In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32In_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64In_quals[] =
{
    &Assoc1_Foo2_U64In_In_qual,
};

/* parameter Assoc1.Foo2(): U64In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E05, /* code */
    MI_T("U64In"), /* name */
    Assoc1_Foo2_U64In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64In_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64In_quals[] =
{
    &Assoc1_Foo2_S64In_In_qual,
};

/* parameter Assoc1.Foo2(): S64In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E05, /* code */
    MI_T("S64In"), /* name */
    Assoc1_Foo2_S64In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64In_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32In_quals[] =
{
    &Assoc1_Foo2_R32In_In_qual,
};

/* parameter Assoc1.Foo2(): R32In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00726E05, /* code */
    MI_T("R32In"), /* name */
    Assoc1_Foo2_R32In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32In_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64In_quals[] =
{
    &Assoc1_Foo2_R64In_In_qual,
};

/* parameter Assoc1.Foo2(): R64In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00726E05, /* code */
    MI_T("R64In"), /* name */
    Assoc1_Foo2_R64In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64In_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT1In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT1In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT1In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT1In_quals[] =
{
    &Assoc1_Foo2_DT1In_In_qual,
};

/* parameter Assoc1.Foo2(): DT1In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT1In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646E05, /* code */
    MI_T("DT1In"), /* name */
    Assoc1_Foo2_DT1In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT1In_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT1In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT2In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT2In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT2In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT2In_quals[] =
{
    &Assoc1_Foo2_DT2In_In_qual,
};

/* parameter Assoc1.Foo2(): DT2In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT2In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646E05, /* code */
    MI_T("DT2In"), /* name */
    Assoc1_Foo2_DT2In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT2In_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT2In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SIn_quals[] =
{
    &Assoc1_Foo2_SIn_In_qual,
};

/* parameter Assoc1.Foo2(): SIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E03, /* code */
    MI_T("SIn"), /* name */
    Assoc1_Foo2_SIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SIn_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16In_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16In_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16In_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16In_quals[] =
{
    &Assoc1_Foo2_C16In_In_qual,
};

/* parameter Assoc1.Foo2(): C16In */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16In_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636E05, /* code */
    MI_T("C16In"), /* name */
    Assoc1_Foo2_C16In_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16In_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16In), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BAIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BAIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BAIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BAIn_quals[] =
{
    &Assoc1_Foo2_BAIn_In_qual,
};

/* parameter Assoc1.Foo2(): BAIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BAIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00626E04, /* code */
    MI_T("BAIn"), /* name */
    Assoc1_Foo2_BAIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BAIn_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BAIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8AIn_quals[] =
{
    &Assoc1_Foo2_U8AIn_In_qual,
};

/* parameter Assoc1.Foo2(): U8AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E05, /* code */
    MI_T("U8AIn"), /* name */
    Assoc1_Foo2_U8AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8AIn_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8AIn_quals[] =
{
    &Assoc1_Foo2_S8AIn_In_qual,
};

/* parameter Assoc1.Foo2(): S8AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E05, /* code */
    MI_T("S8AIn"), /* name */
    Assoc1_Foo2_S8AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8AIn_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16AIn_quals[] =
{
    &Assoc1_Foo2_U16AIn_In_qual,
};

/* parameter Assoc1.Foo2(): U16AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E06, /* code */
    MI_T("U16AIn"), /* name */
    Assoc1_Foo2_U16AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16AIn_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16AIn_quals[] =
{
    &Assoc1_Foo2_S16AIn_In_qual,
};

/* parameter Assoc1.Foo2(): S16AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E06, /* code */
    MI_T("S16AIn"), /* name */
    Assoc1_Foo2_S16AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16AIn_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32AIn_quals[] =
{
    &Assoc1_Foo2_U32AIn_In_qual,
};

/* parameter Assoc1.Foo2(): U32AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E06, /* code */
    MI_T("U32AIn"), /* name */
    Assoc1_Foo2_U32AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32AIn_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32AIn_quals[] =
{
    &Assoc1_Foo2_S32AIn_In_qual,
};

/* parameter Assoc1.Foo2(): S32AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E06, /* code */
    MI_T("S32AIn"), /* name */
    Assoc1_Foo2_S32AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32AIn_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64AIn_quals[] =
{
    &Assoc1_Foo2_U64AIn_In_qual,
};

/* parameter Assoc1.Foo2(): U64AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756E06, /* code */
    MI_T("U64AIn"), /* name */
    Assoc1_Foo2_U64AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64AIn_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64AIn_quals[] =
{
    &Assoc1_Foo2_S64AIn_In_qual,
};

/* parameter Assoc1.Foo2(): S64AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E06, /* code */
    MI_T("S64AIn"), /* name */
    Assoc1_Foo2_S64AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64AIn_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32AIn_quals[] =
{
    &Assoc1_Foo2_R32AIn_In_qual,
};

/* parameter Assoc1.Foo2(): R32AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00726E06, /* code */
    MI_T("R32AIn"), /* name */
    Assoc1_Foo2_R32AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32AIn_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64AIn_quals[] =
{
    &Assoc1_Foo2_R64AIn_In_qual,
};

/* parameter Assoc1.Foo2(): R64AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00726E06, /* code */
    MI_T("R64AIn"), /* name */
    Assoc1_Foo2_R64AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64AIn_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DTAIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DTAIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DTAIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DTAIn_quals[] =
{
    &Assoc1_Foo2_DTAIn_In_qual,
};

/* parameter Assoc1.Foo2(): DTAIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DTAIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646E05, /* code */
    MI_T("DTAIn"), /* name */
    Assoc1_Foo2_DTAIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DTAIn_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DTAIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SAIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SAIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SAIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SAIn_quals[] =
{
    &Assoc1_Foo2_SAIn_In_qual,
};

/* parameter Assoc1.Foo2(): SAIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SAIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736E04, /* code */
    MI_T("SAIn"), /* name */
    Assoc1_Foo2_SAIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SAIn_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SAIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16AIn_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16AIn_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16AIn_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16AIn_quals[] =
{
    &Assoc1_Foo2_C16AIn_In_qual,
};

/* parameter Assoc1.Foo2(): C16AIn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16AIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636E06, /* code */
    MI_T("C16AIn"), /* name */
    Assoc1_Foo2_C16AIn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16AIn_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16AIn), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_WidOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_WidOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_WidOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_WidOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_WidOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_WidOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_WidOut_quals[] =
{
    &Assoc1_Foo2_WidOut_In_qual,
    &Assoc1_Foo2_WidOut_Out_qual,
};

/* parameter Assoc1.Foo2(): WidOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_WidOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00777406, /* code */
    MI_T("WidOut"), /* name */
    Assoc1_Foo2_WidOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_WidOut_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, WidOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_GadOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_GadOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_GadOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_GadOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_GadOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_GadOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_GadOut_quals[] =
{
    &Assoc1_Foo2_GadOut_In_qual,
    &Assoc1_Foo2_GadOut_Out_qual,
};

/* parameter Assoc1.Foo2(): GadOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_GadOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00677406, /* code */
    MI_T("GadOut"), /* name */
    Assoc1_Foo2_GadOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_GadOut_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, GadOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_BOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_BOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BOut_quals[] =
{
    &Assoc1_Foo2_BOut_In_qual,
    &Assoc1_Foo2_BOut_Out_qual,
};

/* parameter Assoc1.Foo2(): BOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00627404, /* code */
    MI_T("BOut"), /* name */
    Assoc1_Foo2_BOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BOut_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8Out_quals[] =
{
    &Assoc1_Foo2_U8Out_In_qual,
    &Assoc1_Foo2_U8Out_Out_qual,
};

/* parameter Assoc1.Foo2(): U8Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757405, /* code */
    MI_T("U8Out"), /* name */
    Assoc1_Foo2_U8Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8Out_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8Out_quals[] =
{
    &Assoc1_Foo2_S8Out_In_qual,
    &Assoc1_Foo2_S8Out_Out_qual,
};

/* parameter Assoc1.Foo2(): S8Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737405, /* code */
    MI_T("S8Out"), /* name */
    Assoc1_Foo2_S8Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8Out_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16Out_quals[] =
{
    &Assoc1_Foo2_U16Out_In_qual,
    &Assoc1_Foo2_U16Out_Out_qual,
};

/* parameter Assoc1.Foo2(): U16Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757406, /* code */
    MI_T("U16Out"), /* name */
    Assoc1_Foo2_U16Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16Out_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16Out_quals[] =
{
    &Assoc1_Foo2_S16Out_In_qual,
    &Assoc1_Foo2_S16Out_Out_qual,
};

/* parameter Assoc1.Foo2(): S16Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737406, /* code */
    MI_T("S16Out"), /* name */
    Assoc1_Foo2_S16Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16Out_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32Out_quals[] =
{
    &Assoc1_Foo2_U32Out_In_qual,
    &Assoc1_Foo2_U32Out_Out_qual,
};

/* parameter Assoc1.Foo2(): U32Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757406, /* code */
    MI_T("U32Out"), /* name */
    Assoc1_Foo2_U32Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32Out_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32Out_quals[] =
{
    &Assoc1_Foo2_S32Out_In_qual,
    &Assoc1_Foo2_S32Out_Out_qual,
};

/* parameter Assoc1.Foo2(): S32Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737406, /* code */
    MI_T("S32Out"), /* name */
    Assoc1_Foo2_S32Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32Out_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64Out_quals[] =
{
    &Assoc1_Foo2_U64Out_In_qual,
    &Assoc1_Foo2_U64Out_Out_qual,
};

/* parameter Assoc1.Foo2(): U64Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757406, /* code */
    MI_T("U64Out"), /* name */
    Assoc1_Foo2_U64Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64Out_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64Out_quals[] =
{
    &Assoc1_Foo2_S64Out_In_qual,
    &Assoc1_Foo2_S64Out_Out_qual,
};

/* parameter Assoc1.Foo2(): S64Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737406, /* code */
    MI_T("S64Out"), /* name */
    Assoc1_Foo2_S64Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64Out_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32Out_quals[] =
{
    &Assoc1_Foo2_R32Out_In_qual,
    &Assoc1_Foo2_R32Out_Out_qual,
};

/* parameter Assoc1.Foo2(): R32Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("R32Out"), /* name */
    Assoc1_Foo2_R32Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32Out_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64Out_quals[] =
{
    &Assoc1_Foo2_R64Out_In_qual,
    &Assoc1_Foo2_R64Out_Out_qual,
};

/* parameter Assoc1.Foo2(): R64Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("R64Out"), /* name */
    Assoc1_Foo2_R64Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64Out_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT1Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT1Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT1Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT1Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT1Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT1Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT1Out_quals[] =
{
    &Assoc1_Foo2_DT1Out_In_qual,
    &Assoc1_Foo2_DT1Out_Out_qual,
};

/* parameter Assoc1.Foo2(): DT1Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT1Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00647406, /* code */
    MI_T("DT1Out"), /* name */
    Assoc1_Foo2_DT1Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT1Out_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT1Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT2Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT2Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT2Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT2Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT2Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT2Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT2Out_quals[] =
{
    &Assoc1_Foo2_DT2Out_In_qual,
    &Assoc1_Foo2_DT2Out_Out_qual,
};

/* parameter Assoc1.Foo2(): DT2Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT2Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00647406, /* code */
    MI_T("DT2Out"), /* name */
    Assoc1_Foo2_DT2Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT2Out_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT2Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_SOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_SOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SOut_quals[] =
{
    &Assoc1_Foo2_SOut_In_qual,
    &Assoc1_Foo2_SOut_Out_qual,
};

/* parameter Assoc1.Foo2(): SOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737404, /* code */
    MI_T("SOut"), /* name */
    Assoc1_Foo2_SOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SOut_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16Out_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16Out_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16Out_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16Out_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16Out_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16Out_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16Out_quals[] =
{
    &Assoc1_Foo2_C16Out_In_qual,
    &Assoc1_Foo2_C16Out_Out_qual,
};

/* parameter Assoc1.Foo2(): C16Out */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16Out_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00637406, /* code */
    MI_T("C16Out"), /* name */
    Assoc1_Foo2_C16Out_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16Out_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16Out), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BAOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_BAOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BAOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_BAOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BAOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BAOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BAOut_quals[] =
{
    &Assoc1_Foo2_BAOut_In_qual,
    &Assoc1_Foo2_BAOut_Out_qual,
};

/* parameter Assoc1.Foo2(): BAOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BAOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00627405, /* code */
    MI_T("BAOut"), /* name */
    Assoc1_Foo2_BAOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BAOut_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BAOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8AOut_quals[] =
{
    &Assoc1_Foo2_U8AOut_In_qual,
    &Assoc1_Foo2_U8AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U8AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757406, /* code */
    MI_T("U8AOut"), /* name */
    Assoc1_Foo2_U8AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8AOut_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8AOut_quals[] =
{
    &Assoc1_Foo2_S8AOut_In_qual,
    &Assoc1_Foo2_S8AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S8AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737406, /* code */
    MI_T("S8AOut"), /* name */
    Assoc1_Foo2_S8AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8AOut_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16AOut_quals[] =
{
    &Assoc1_Foo2_U16AOut_In_qual,
    &Assoc1_Foo2_U16AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U16AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757407, /* code */
    MI_T("U16AOut"), /* name */
    Assoc1_Foo2_U16AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16AOut_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16AOut_quals[] =
{
    &Assoc1_Foo2_S16AOut_In_qual,
    &Assoc1_Foo2_S16AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S16AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737407, /* code */
    MI_T("S16AOut"), /* name */
    Assoc1_Foo2_S16AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16AOut_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32AOut_quals[] =
{
    &Assoc1_Foo2_U32AOut_In_qual,
    &Assoc1_Foo2_U32AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U32AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757407, /* code */
    MI_T("U32AOut"), /* name */
    Assoc1_Foo2_U32AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32AOut_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32AOut_quals[] =
{
    &Assoc1_Foo2_S32AOut_In_qual,
    &Assoc1_Foo2_S32AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S32AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737407, /* code */
    MI_T("S32AOut"), /* name */
    Assoc1_Foo2_S32AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32AOut_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64AOut_quals[] =
{
    &Assoc1_Foo2_U64AOut_In_qual,
    &Assoc1_Foo2_U64AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U64AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00757407, /* code */
    MI_T("U64AOut"), /* name */
    Assoc1_Foo2_U64AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64AOut_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64AOut_quals[] =
{
    &Assoc1_Foo2_S64AOut_In_qual,
    &Assoc1_Foo2_S64AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S64AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737407, /* code */
    MI_T("S64AOut"), /* name */
    Assoc1_Foo2_S64AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64AOut_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32AOut_quals[] =
{
    &Assoc1_Foo2_R32AOut_In_qual,
    &Assoc1_Foo2_R32AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R32AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727407, /* code */
    MI_T("R32AOut"), /* name */
    Assoc1_Foo2_R32AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32AOut_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64AOut_quals[] =
{
    &Assoc1_Foo2_R64AOut_In_qual,
    &Assoc1_Foo2_R64AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R64AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727407, /* code */
    MI_T("R64AOut"), /* name */
    Assoc1_Foo2_R64AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64AOut_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DTAOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_DTAOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DTAOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DTAOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DTAOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DTAOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DTAOut_quals[] =
{
    &Assoc1_Foo2_DTAOut_In_qual,
    &Assoc1_Foo2_DTAOut_Out_qual,
};

/* parameter Assoc1.Foo2(): DTAOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DTAOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00647406, /* code */
    MI_T("DTAOut"), /* name */
    Assoc1_Foo2_DTAOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DTAOut_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DTAOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SAOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_SAOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SAOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_SAOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SAOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SAOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SAOut_quals[] =
{
    &Assoc1_Foo2_SAOut_In_qual,
    &Assoc1_Foo2_SAOut_Out_qual,
};

/* parameter Assoc1.Foo2(): SAOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SAOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00737405, /* code */
    MI_T("SAOut"), /* name */
    Assoc1_Foo2_SAOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SAOut_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SAOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16AOut_In_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16AOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16AOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16AOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16AOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16AOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16AOut_quals[] =
{
    &Assoc1_Foo2_C16AOut_In_qual,
    &Assoc1_Foo2_C16AOut_Out_qual,
};

/* parameter Assoc1.Foo2(): C16AOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16AOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00637407, /* code */
    MI_T("C16AOut"), /* name */
    Assoc1_Foo2_C16AOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16AOut_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16AOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_WidInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_WidInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_WidInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_WidInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_WidInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_WidInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_WidInOut_quals[] =
{
    &Assoc1_Foo2_WidInOut_In_qual,
    &Assoc1_Foo2_WidInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): WidInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_WidInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00777408, /* code */
    MI_T("WidInOut"), /* name */
    Assoc1_Foo2_WidInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_WidInOut_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Widget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, WidInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_GadInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_GadInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_GadInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_GadInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_GadInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_GadInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_GadInOut_quals[] =
{
    &Assoc1_Foo2_GadInOut_In_qual,
    &Assoc1_Foo2_GadInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): GadInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_GadInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00677408, /* code */
    MI_T("GadInOut"), /* name */
    Assoc1_Foo2_GadInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_GadInOut_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Gadget"), /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, GadInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_BInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BInOut_quals[] =
{
    &Assoc1_Foo2_BInOut_In_qual,
    &Assoc1_Foo2_BInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): BInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00627406, /* code */
    MI_T("BInOut"), /* name */
    Assoc1_Foo2_BInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BInOut_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8InOut_quals[] =
{
    &Assoc1_Foo2_U8InOut_In_qual,
    &Assoc1_Foo2_U8InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U8InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757407, /* code */
    MI_T("U8InOut"), /* name */
    Assoc1_Foo2_U8InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8InOut_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8InOut_quals[] =
{
    &Assoc1_Foo2_S8InOut_In_qual,
    &Assoc1_Foo2_S8InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S8InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737407, /* code */
    MI_T("S8InOut"), /* name */
    Assoc1_Foo2_S8InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8InOut_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16InOut_quals[] =
{
    &Assoc1_Foo2_U16InOut_In_qual,
    &Assoc1_Foo2_U16InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U16InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757408, /* code */
    MI_T("U16InOut"), /* name */
    Assoc1_Foo2_U16InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16InOut_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16InOut_quals[] =
{
    &Assoc1_Foo2_S16InOut_In_qual,
    &Assoc1_Foo2_S16InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S16InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737408, /* code */
    MI_T("S16InOut"), /* name */
    Assoc1_Foo2_S16InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16InOut_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32InOut_quals[] =
{
    &Assoc1_Foo2_U32InOut_In_qual,
    &Assoc1_Foo2_U32InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U32InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757408, /* code */
    MI_T("U32InOut"), /* name */
    Assoc1_Foo2_U32InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32InOut_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32InOut_quals[] =
{
    &Assoc1_Foo2_S32InOut_In_qual,
    &Assoc1_Foo2_S32InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S32InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737408, /* code */
    MI_T("S32InOut"), /* name */
    Assoc1_Foo2_S32InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32InOut_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64InOut_quals[] =
{
    &Assoc1_Foo2_U64InOut_In_qual,
    &Assoc1_Foo2_U64InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U64InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757408, /* code */
    MI_T("U64InOut"), /* name */
    Assoc1_Foo2_U64InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64InOut_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64InOut_quals[] =
{
    &Assoc1_Foo2_S64InOut_In_qual,
    &Assoc1_Foo2_S64InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S64InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737408, /* code */
    MI_T("S64InOut"), /* name */
    Assoc1_Foo2_S64InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64InOut_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32InOut_quals[] =
{
    &Assoc1_Foo2_R32InOut_In_qual,
    &Assoc1_Foo2_R32InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R32InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00727408, /* code */
    MI_T("R32InOut"), /* name */
    Assoc1_Foo2_R32InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32InOut_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64InOut_quals[] =
{
    &Assoc1_Foo2_R64InOut_In_qual,
    &Assoc1_Foo2_R64InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R64InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00727408, /* code */
    MI_T("R64InOut"), /* name */
    Assoc1_Foo2_R64InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64InOut_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT1InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT1InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT1InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT1InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT1InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT1InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT1InOut_quals[] =
{
    &Assoc1_Foo2_DT1InOut_In_qual,
    &Assoc1_Foo2_DT1InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): DT1InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT1InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00647408, /* code */
    MI_T("DT1InOut"), /* name */
    Assoc1_Foo2_DT1InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT1InOut_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT1InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT2InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT2InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT2InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DT2InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DT2InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DT2InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DT2InOut_quals[] =
{
    &Assoc1_Foo2_DT2InOut_In_qual,
    &Assoc1_Foo2_DT2InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): DT2InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DT2InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00647408, /* code */
    MI_T("DT2InOut"), /* name */
    Assoc1_Foo2_DT2InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DT2InOut_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DT2InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_SInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SInOut_quals[] =
{
    &Assoc1_Foo2_SInOut_In_qual,
    &Assoc1_Foo2_SInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): SInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737406, /* code */
    MI_T("SInOut"), /* name */
    Assoc1_Foo2_SInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SInOut_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16InOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16InOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16InOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16InOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16InOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16InOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16InOut_quals[] =
{
    &Assoc1_Foo2_C16InOut_In_qual,
    &Assoc1_Foo2_C16InOut_Out_qual,
};

/* parameter Assoc1.Foo2(): C16InOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16InOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00637408, /* code */
    MI_T("C16InOut"), /* name */
    Assoc1_Foo2_C16InOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16InOut_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16InOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_BAInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BAInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BAInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_BAInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_BAInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_BAInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_BAInOut_quals[] =
{
    &Assoc1_Foo2_BAInOut_In_qual,
    &Assoc1_Foo2_BAInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): BAInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_BAInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00627407, /* code */
    MI_T("BAInOut"), /* name */
    Assoc1_Foo2_BAInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_BAInOut_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, BAInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U8AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U8AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U8AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U8AInOut_quals[] =
{
    &Assoc1_Foo2_U8AInOut_In_qual,
    &Assoc1_Foo2_U8AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U8AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U8AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757408, /* code */
    MI_T("U8AInOut"), /* name */
    Assoc1_Foo2_U8AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U8AInOut_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U8AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S8AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S8AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S8AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S8AInOut_quals[] =
{
    &Assoc1_Foo2_S8AInOut_In_qual,
    &Assoc1_Foo2_S8AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S8AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S8AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737408, /* code */
    MI_T("S8AInOut"), /* name */
    Assoc1_Foo2_S8AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S8AInOut_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S8AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U16AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U16AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U16AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U16AInOut_quals[] =
{
    &Assoc1_Foo2_U16AInOut_In_qual,
    &Assoc1_Foo2_U16AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U16AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U16AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757409, /* code */
    MI_T("U16AInOut"), /* name */
    Assoc1_Foo2_U16AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U16AInOut_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U16AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S16AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S16AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S16AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S16AInOut_quals[] =
{
    &Assoc1_Foo2_S16AInOut_In_qual,
    &Assoc1_Foo2_S16AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S16AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S16AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737409, /* code */
    MI_T("S16AInOut"), /* name */
    Assoc1_Foo2_S16AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S16AInOut_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S16AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U32AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U32AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U32AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U32AInOut_quals[] =
{
    &Assoc1_Foo2_U32AInOut_In_qual,
    &Assoc1_Foo2_U32AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U32AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U32AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757409, /* code */
    MI_T("U32AInOut"), /* name */
    Assoc1_Foo2_U32AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U32AInOut_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U32AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S32AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S32AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S32AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S32AInOut_quals[] =
{
    &Assoc1_Foo2_S32AInOut_In_qual,
    &Assoc1_Foo2_S32AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S32AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S32AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737409, /* code */
    MI_T("S32AInOut"), /* name */
    Assoc1_Foo2_S32AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S32AInOut_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S32AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_U64AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_U64AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_U64AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_U64AInOut_quals[] =
{
    &Assoc1_Foo2_U64AInOut_In_qual,
    &Assoc1_Foo2_U64AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): U64AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_U64AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00757409, /* code */
    MI_T("U64AInOut"), /* name */
    Assoc1_Foo2_U64AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_U64AInOut_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, U64AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_S64AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_S64AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_S64AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_S64AInOut_quals[] =
{
    &Assoc1_Foo2_S64AInOut_In_qual,
    &Assoc1_Foo2_S64AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): S64AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_S64AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737409, /* code */
    MI_T("S64AInOut"), /* name */
    Assoc1_Foo2_S64AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_S64AInOut_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, S64AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R32AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R32AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R32AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R32AInOut_quals[] =
{
    &Assoc1_Foo2_R32AInOut_In_qual,
    &Assoc1_Foo2_R32AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R32AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R32AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00727409, /* code */
    MI_T("R32AInOut"), /* name */
    Assoc1_Foo2_R32AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R32AInOut_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R32AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_R64AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_R64AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_R64AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_R64AInOut_quals[] =
{
    &Assoc1_Foo2_R64AInOut_In_qual,
    &Assoc1_Foo2_R64AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): R64AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_R64AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00727409, /* code */
    MI_T("R64AInOut"), /* name */
    Assoc1_Foo2_R64AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_R64AInOut_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, R64AInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_DTAInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DTAInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DTAInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_DTAInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_DTAInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_DTAInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_DTAInOut_quals[] =
{
    &Assoc1_Foo2_DTAInOut_In_qual,
    &Assoc1_Foo2_DTAInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): DTAInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_DTAInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00647408, /* code */
    MI_T("DTAInOut"), /* name */
    Assoc1_Foo2_DTAInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_DTAInOut_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, DTAInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_SAInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SAInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SAInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_SAInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_SAInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_SAInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_SAInOut_quals[] =
{
    &Assoc1_Foo2_SAInOut_In_qual,
    &Assoc1_Foo2_SAInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): SAInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_SAInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737407, /* code */
    MI_T("SAInOut"), /* name */
    Assoc1_Foo2_SAInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_SAInOut_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, SAInOut), /* offset */
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16AInOut_In_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16AInOut_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16AInOut_In_qual_value
};

static MI_CONST MI_Boolean Assoc1_Foo2_C16AInOut_Out_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Foo2_C16AInOut_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Foo2_C16AInOut_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_C16AInOut_quals[] =
{
    &Assoc1_Foo2_C16AInOut_In_qual,
    &Assoc1_Foo2_C16AInOut_Out_qual,
};

/* parameter Assoc1.Foo2(): C16AInOut */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_C16AInOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00637409, /* code */
    MI_T("C16AInOut"), /* name */
    Assoc1_Foo2_C16AInOut_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_C16AInOut_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, C16AInOut), /* offset */
};

static MI_CONST MI_Char* Assoc1_Foo2_MIReturn_Description_qual_value = MI_T("Foo2");

static MI_CONST MI_Qualifier Assoc1_Foo2_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Assoc1_Foo2_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_Foo2_MIReturn_quals[] =
{
    &Assoc1_Foo2_MIReturn_Description_qual,
};

/* parameter Assoc1.Foo2(): MIReturn */
static MI_CONST MI_ParameterDecl Assoc1_Foo2_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    Assoc1_Foo2_MIReturn_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_MIReturn_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Assoc1_Foo2, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Assoc1_Foo2_params[] =
{
    &Assoc1_Foo2_MIReturn_param,
    &Assoc1_Foo2_WidIn_param,
    &Assoc1_Foo2_GadIn_param,
    &Assoc1_Foo2_BIn_param,
    &Assoc1_Foo2_U8In_param,
    &Assoc1_Foo2_S8In_param,
    &Assoc1_Foo2_U16In_param,
    &Assoc1_Foo2_S16In_param,
    &Assoc1_Foo2_U32In_param,
    &Assoc1_Foo2_S32In_param,
    &Assoc1_Foo2_U64In_param,
    &Assoc1_Foo2_S64In_param,
    &Assoc1_Foo2_R32In_param,
    &Assoc1_Foo2_R64In_param,
    &Assoc1_Foo2_DT1In_param,
    &Assoc1_Foo2_DT2In_param,
    &Assoc1_Foo2_SIn_param,
    &Assoc1_Foo2_C16In_param,
    &Assoc1_Foo2_BAIn_param,
    &Assoc1_Foo2_U8AIn_param,
    &Assoc1_Foo2_S8AIn_param,
    &Assoc1_Foo2_U16AIn_param,
    &Assoc1_Foo2_S16AIn_param,
    &Assoc1_Foo2_U32AIn_param,
    &Assoc1_Foo2_S32AIn_param,
    &Assoc1_Foo2_U64AIn_param,
    &Assoc1_Foo2_S64AIn_param,
    &Assoc1_Foo2_R32AIn_param,
    &Assoc1_Foo2_R64AIn_param,
    &Assoc1_Foo2_DTAIn_param,
    &Assoc1_Foo2_SAIn_param,
    &Assoc1_Foo2_C16AIn_param,
    &Assoc1_Foo2_WidOut_param,
    &Assoc1_Foo2_GadOut_param,
    &Assoc1_Foo2_BOut_param,
    &Assoc1_Foo2_U8Out_param,
    &Assoc1_Foo2_S8Out_param,
    &Assoc1_Foo2_U16Out_param,
    &Assoc1_Foo2_S16Out_param,
    &Assoc1_Foo2_U32Out_param,
    &Assoc1_Foo2_S32Out_param,
    &Assoc1_Foo2_U64Out_param,
    &Assoc1_Foo2_S64Out_param,
    &Assoc1_Foo2_R32Out_param,
    &Assoc1_Foo2_R64Out_param,
    &Assoc1_Foo2_DT1Out_param,
    &Assoc1_Foo2_DT2Out_param,
    &Assoc1_Foo2_SOut_param,
    &Assoc1_Foo2_C16Out_param,
    &Assoc1_Foo2_BAOut_param,
    &Assoc1_Foo2_U8AOut_param,
    &Assoc1_Foo2_S8AOut_param,
    &Assoc1_Foo2_U16AOut_param,
    &Assoc1_Foo2_S16AOut_param,
    &Assoc1_Foo2_U32AOut_param,
    &Assoc1_Foo2_S32AOut_param,
    &Assoc1_Foo2_U64AOut_param,
    &Assoc1_Foo2_S64AOut_param,
    &Assoc1_Foo2_R32AOut_param,
    &Assoc1_Foo2_R64AOut_param,
    &Assoc1_Foo2_DTAOut_param,
    &Assoc1_Foo2_SAOut_param,
    &Assoc1_Foo2_C16AOut_param,
    &Assoc1_Foo2_WidInOut_param,
    &Assoc1_Foo2_GadInOut_param,
    &Assoc1_Foo2_BInOut_param,
    &Assoc1_Foo2_U8InOut_param,
    &Assoc1_Foo2_S8InOut_param,
    &Assoc1_Foo2_U16InOut_param,
    &Assoc1_Foo2_S16InOut_param,
    &Assoc1_Foo2_U32InOut_param,
    &Assoc1_Foo2_S32InOut_param,
    &Assoc1_Foo2_U64InOut_param,
    &Assoc1_Foo2_S64InOut_param,
    &Assoc1_Foo2_R32InOut_param,
    &Assoc1_Foo2_R64InOut_param,
    &Assoc1_Foo2_DT1InOut_param,
    &Assoc1_Foo2_DT2InOut_param,
    &Assoc1_Foo2_SInOut_param,
    &Assoc1_Foo2_C16InOut_param,
    &Assoc1_Foo2_BAInOut_param,
    &Assoc1_Foo2_U8AInOut_param,
    &Assoc1_Foo2_S8AInOut_param,
    &Assoc1_Foo2_U16AInOut_param,
    &Assoc1_Foo2_S16AInOut_param,
    &Assoc1_Foo2_U32AInOut_param,
    &Assoc1_Foo2_S32AInOut_param,
    &Assoc1_Foo2_U64AInOut_param,
    &Assoc1_Foo2_S64AInOut_param,
    &Assoc1_Foo2_R32AInOut_param,
    &Assoc1_Foo2_R64AInOut_param,
    &Assoc1_Foo2_DTAInOut_param,
    &Assoc1_Foo2_SAInOut_param,
    &Assoc1_Foo2_C16AInOut_param,
};

/* method Assoc1.Foo2() */
MI_CONST MI_MethodDecl Assoc1_Foo2_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00663204, /* code */
    MI_T("Foo2"), /* name */
    Assoc1_Foo2_quals, /* qualifiers */
    MI_COUNT(Assoc1_Foo2_quals), /* numQualifiers */
    Assoc1_Foo2_params, /* parameters */
    MI_COUNT(Assoc1_Foo2_params), /* numParameters */
    sizeof(Assoc1_Foo2), /* size */
    MI_STRING, /* returnType */
    MI_T("Assoc1"), /* origin */
    MI_T("Assoc1"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Assoc1_meths[] =
{
    &Assoc1_Foo_rtti,
    &Assoc1_Foo2_rtti,
};

static MI_CONST MI_Boolean Assoc1_Association_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Association_qual =
{
    MI_T("Association"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Association_qual_value
};

static MI_CONST MI_Char* Assoc1_Color_qual_value = MI_T("PINK");

static MI_CONST MI_Qualifier Assoc1_Color_qual =
{
    MI_T("Color"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Color_qual_value
};

static MI_CONST MI_Boolean Assoc1_Flag_qual_value = 0;

static MI_CONST MI_Qualifier Assoc1_Flag_qual =
{
    MI_T("Flag"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Assoc1_Flag_qual_value
};

static MI_CONST MI_Boolean Assoc1_Terminal_qual_value = 1;

static MI_CONST MI_Qualifier Assoc1_Terminal_qual =
{
    MI_T("Terminal"),
    MI_BOOLEAN,
    0,
    &Assoc1_Terminal_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Assoc1_quals[] =
{
    &Assoc1_Association_qual,
    &Assoc1_Color_qual,
    &Assoc1_Flag_qual,
    &Assoc1_Terminal_qual,
};

/* class Assoc1 */
MI_CONST static MI_ClassDecl Assoc1_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_TERMINAL, /* flags */
    0x00613106, /* code */
    MI_T("Assoc1"), /* name */
    Assoc1_quals, /* qualifiers */
    MI_COUNT(Assoc1_quals), /* numQualifiers */
    Assoc1_props, /* properties */
    MI_COUNT(Assoc1_props), /* numProperties */
    sizeof(Assoc1), /* size */
    MI_T("Assoc0"), /* superClass */
    &Assoc0_rtti, /* superClassDecl */
    Assoc1_meths, /* methods */
    MI_COUNT(Assoc1_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** SuperClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean SuperClass_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier SuperClass_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &SuperClass_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST SuperClass_Key_quals[] =
{
    &SuperClass_Key_Key_qual,
};

/* property SuperClass.Key */
static MI_CONST MI_PropertyDecl SuperClass_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    SuperClass_Key_quals, /* qualifiers */
    MI_COUNT(SuperClass_Key_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(SuperClass, Key), /* offset */
    MI_T("SuperClass"), /* origin */
    MI_T("SuperClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST SuperClass_props[] =
{
    &SuperClass_Key_prop,
};

static MI_CONST MI_Boolean SuperClass_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier SuperClass_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &SuperClass_Abstract_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST SuperClass_quals[] =
{
    &SuperClass_Abstract_qual,
};

/* class SuperClass */
MI_CONST static MI_ClassDecl SuperClass_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x0073730A, /* code */
    MI_T("SuperClass"), /* name */
    SuperClass_quals, /* qualifiers */
    MI_COUNT(SuperClass_quals), /* numQualifiers */
    SuperClass_props, /* properties */
    MI_COUNT(SuperClass_props), /* numProperties */
    sizeof(SuperClass), /* size */
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
** SubClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean SubClass_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier SubClass_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &SubClass_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST SubClass_Key_quals[] =
{
    &SubClass_Key_Key_qual,
};

/* property SubClass.Key */
static MI_CONST MI_PropertyDecl SubClass_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    SubClass_Key_quals, /* qualifiers */
    MI_COUNT(SubClass_Key_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(SubClass, Key), /* offset */
    MI_T("SuperClass"), /* origin */
    MI_T("SubClass"), /* propagator */
    NULL,
};

/* property SubClass.Count */
static MI_CONST MI_PropertyDecl SubClass_Count_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637405, /* code */
    MI_T("Count"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(SubClass, Count), /* offset */
    MI_T("SubClass"), /* origin */
    MI_T("SubClass"), /* propagator */
    NULL,
};

/* property SubClass.Color */
static MI_CONST MI_PropertyDecl SubClass_Color_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637205, /* code */
    MI_T("Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(SubClass, Color), /* offset */
    MI_T("SubClass"), /* origin */
    MI_T("SubClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST SubClass_props[] =
{
    &SubClass_Key_prop,
    &SubClass_Count_prop,
    &SubClass_Color_prop,
};

static MI_CONST MI_Boolean SubClass_Terminal_qual_value = 1;

static MI_CONST MI_Qualifier SubClass_Terminal_qual =
{
    MI_T("Terminal"),
    MI_BOOLEAN,
    0,
    &SubClass_Terminal_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST SubClass_quals[] =
{
    &SubClass_Terminal_qual,
};

/* class SubClass */
MI_CONST static MI_ClassDecl SubClass_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_TERMINAL, /* flags */
    0x00737308, /* code */
    MI_T("SubClass"), /* name */
    SubClass_quals, /* qualifiers */
    MI_COUNT(SubClass_quals), /* numQualifiers */
    SubClass_props, /* properties */
    MI_COUNT(SubClass_props), /* numProperties */
    sizeof(SubClass), /* size */
    MI_T("SuperClass"), /* superClass */
    &SuperClass_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Thing
**
**==============================================================================
*/

static MI_CONST MI_Boolean Thing_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier Thing_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Thing_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Thing_Key_quals[] =
{
    &Thing_Key_Key_qual,
};

/* property Thing.Key */
static MI_CONST MI_PropertyDecl Thing_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    Thing_Key_quals, /* qualifiers */
    MI_COUNT(Thing_Key_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Thing, Key), /* offset */
    MI_T("Thing"), /* origin */
    MI_T("Thing"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean Thing_Obj_EmbeddedObject_qual_value = 1;

static MI_CONST MI_Qualifier Thing_Obj_EmbeddedObject_qual =
{
    MI_T("EmbeddedObject"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Thing_Obj_EmbeddedObject_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Thing_Obj_quals[] =
{
    &Thing_Obj_EmbeddedObject_qual,
};

/* property Thing.Obj */
static MI_CONST MI_PropertyDecl Thing_Obj_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6A03, /* code */
    MI_T("Obj"), /* name */
    Thing_Obj_quals, /* qualifiers */
    MI_COUNT(Thing_Obj_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Thing, Obj), /* offset */
    MI_T("Thing"), /* origin */
    MI_T("Thing"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Thing_props[] =
{
    &Thing_Key_prop,
    &Thing_Obj_prop,
};

/* class Thing */
MI_CONST static MI_ClassDecl Thing_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746705, /* code */
    MI_T("Thing"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Thing_props, /* properties */
    MI_COUNT(Thing_props), /* numProperties */
    sizeof(Thing), /* size */
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
    &Assoc0_rtti,
    &Assoc1_rtti,
    &Class1_rtti,
    &Class2_rtti,
    &Container_rtti,
    &Embedded_rtti,
    &Gadget_rtti,
    &Link_rtti,
    &SubClass_rtti,
    &SuperClass_rtti,
    &Thing_rtti,
    &Widget_rtti,
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

