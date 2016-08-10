/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include "QualifierDecls.h"

//==============================================================================
//
// Standard qualifier declarations
//
//==============================================================================

static MI_Boolean Abstract_qual_decl_value = 0;

static MI_QualifierDecl Abstract_qual_decl =
{
    (char*)"Abstract", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    &Abstract_qual_decl_value, /* value */
};

static MI_Boolean Aggregate_qual_decl_value = 0;

static MI_QualifierDecl Aggregate_qual_decl =
{
    (char*)"Aggregate", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Aggregate_qual_decl_value, /* value */
};

static MI_Boolean Aggregation_qual_decl_value = 0;

static MI_QualifierDecl Aggregation_qual_decl =
{
    (char*)"Aggregation", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Aggregation_qual_decl_value, /* value */
};

static MI_QualifierDecl Alias_qual_decl =
{
    (char*)"Alias", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static const MI_Char* ArrayType_qual_decl_value = "Bag";

static MI_QualifierDecl ArrayType_qual_decl =
{
    (char*)"ArrayType", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &ArrayType_qual_decl_value, /* value */
};

static MI_Boolean Association_qual_decl_value = 0;

static MI_QualifierDecl Association_qual_decl =
{
    (char*)"Association", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Association_qual_decl_value, /* value */
};

static MI_QualifierDecl BitMap_qual_decl =
{
    (char*)"BitMap", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl BitValues_qual_decl =
{
    (char*)"BitValues", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl ClassConstraint_qual_decl =
{
    (char*)"ClassConstraint", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean Composition_qual_decl_value = 0;

static MI_QualifierDecl Composition_qual_decl =
{
    (char*)"Composition", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Composition_qual_decl_value, /* value */
};

static MI_QualifierDecl Correlatable_qual_decl =
{
    (char*)"Correlatable", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean Counter_qual_decl_value = 0;

static MI_QualifierDecl Counter_qual_decl =
{
    (char*)"Counter", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &Counter_qual_decl_value, /* value */
};

static MI_Boolean DN_qual_decl_value = 0;

static MI_QualifierDecl DN_qual_decl =
{
    (char*)"DN", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &DN_qual_decl_value, /* value */
};

static MI_Boolean Delete_qual_decl_value = 0;

static MI_QualifierDecl Delete_qual_decl =
{
    (char*)"Delete", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    &Delete_qual_decl_value, /* value */
};

static MI_QualifierDecl Deprecated_qual_decl =
{
    (char*)"Deprecated", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Description_qual_decl =
{
    (char*)"Description", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl DisplayDescription_qual_decl =
{
    (char*)"DisplayDescription", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl DisplayName_qual_decl =
{
    (char*)"DisplayName", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl EmbeddedInstance_qual_decl =
{
    (char*)"EmbeddedInstance", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean EmbeddedObject_qual_decl_value = 0;

static MI_QualifierDecl EmbeddedObject_qual_decl =
{
    (char*)"EmbeddedObject", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &EmbeddedObject_qual_decl_value, /* value */
};

static MI_Boolean Exception_qual_decl_value = 0;

static MI_QualifierDecl Exception_qual_decl =
{
    (char*)"Exception", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Exception_qual_decl_value, /* value */
};

static MI_Boolean Expensive_qual_decl_value = 0;

static MI_QualifierDecl Expensive_qual_decl =
{
    (char*)"Expensive", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    &Expensive_qual_decl_value, /* value */
};

static MI_Boolean Experimental_qual_decl_value = 0;

static MI_QualifierDecl Experimental_qual_decl =
{
    (char*)"Experimental", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    &Experimental_qual_decl_value, /* value */
};

static MI_Boolean Gauge_qual_decl_value = 0;

static MI_QualifierDecl Gauge_qual_decl =
{
    (char*)"Gauge", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &Gauge_qual_decl_value, /* value */
};

static MI_Boolean Ifdeleted_qual_decl_value = 0;

static MI_QualifierDecl Ifdeleted_qual_decl =
{
    (char*)"Ifdeleted", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    &Ifdeleted_qual_decl_value, /* value */
};

static MI_Boolean In_qual_decl_value = 1;

static MI_QualifierDecl In_qual_decl =
{
    (char*)"In", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &In_qual_decl_value, /* value */
};

static MI_Boolean Indication_qual_decl_value = 0;

static MI_QualifierDecl Indication_qual_decl =
{
    (char*)"Indication", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Indication_qual_decl_value, /* value */
};

static MI_Boolean Invisible_qual_decl_value = 0;

static MI_QualifierDecl Invisible_qual_decl =
{
    (char*)"Invisible", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    &Invisible_qual_decl_value, /* value */
};

static MI_Boolean IsPUnit_qual_decl_value = 0;

static MI_QualifierDecl IsPUnit_qual_decl =
{
    (char*)"IsPUnit", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &IsPUnit_qual_decl_value, /* value */
};

static MI_Boolean Key_qual_decl_value = 0;

static MI_QualifierDecl Key_qual_decl =
{
    (char*)"Key", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Key_qual_decl_value, /* value */
};

static MI_Boolean Large_qual_decl_value = 0;

static MI_QualifierDecl Large_qual_decl =
{
    (char*)"Large", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_CLASS|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &Large_qual_decl_value, /* value */
};

static MI_QualifierDecl MappingStrings_qual_decl =
{
    (char*)"MappingStrings", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Max_qual_decl =
{
    (char*)"Max", /* name */
    MI_UINT32, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl MaxLen_qual_decl =
{
    (char*)"MaxLen", /* name */
    MI_UINT32, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl MaxValue_qual_decl =
{
    (char*)"MaxValue", /* name */
    MI_SINT64, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl MethodConstraint_qual_decl =
{
    (char*)"MethodConstraint", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_METHOD, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Uint32 Min_qual_decl_value = 0;

static MI_QualifierDecl Min_qual_decl =
{
    (char*)"Min", /* name */
    MI_UINT32, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    &Min_qual_decl_value, /* value */
};

static MI_Uint32 MinLen_qual_decl_value = 0;

static MI_QualifierDecl MinLen_qual_decl =
{
    (char*)"MinLen", /* name */
    MI_UINT32, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &MinLen_qual_decl_value, /* value */
};

static MI_QualifierDecl MinValue_qual_decl =
{
    (char*)"MinValue", /* name */
    MI_SINT64, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl ModelCorrespondence_qual_decl =
{
    (char*)"ModelCorrespondence", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Nonlocal_qual_decl =
{
    (char*)"Nonlocal", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl NonlocalType_qual_decl =
{
    (char*)"NonlocalType", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl NullValue_qual_decl =
{
    (char*)"NullValue", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    NULL, /* value */
};

static MI_Boolean Octetstring_qual_decl_value = 0;

static MI_QualifierDecl Octetstring_qual_decl =
{
    (char*)"Octetstring", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Octetstring_qual_decl_value, /* value */
};

static MI_Boolean Out_qual_decl_value = 0;

static MI_QualifierDecl Out_qual_decl =
{
    (char*)"Out", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Out_qual_decl_value, /* value */
};

static MI_QualifierDecl Override_qual_decl =
{
    (char*)"Override", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl PUnit_qual_decl =
{
    (char*)"PUnit", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Propagated_qual_decl =
{
    (char*)"Propagated", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl PropertyConstraint_qual_decl =
{
    (char*)"PropertyConstraint", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static const MI_Char* PropertyUsage_qual_decl_value = "CurrentContext";

static MI_QualifierDecl PropertyUsage_qual_decl =
{
    (char*)"PropertyUsage", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &PropertyUsage_qual_decl_value, /* value */
};

static MI_QualifierDecl Provider_qual_decl =
{
    (char*)"Provider", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ANY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean Read_qual_decl_value = 1;

static MI_QualifierDecl Read_qual_decl =
{
    (char*)"Read", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &Read_qual_decl_value, /* value */
};

static MI_Boolean Required_qual_decl_value = 0;

static MI_QualifierDecl Required_qual_decl =
{
    (char*)"Required", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Required_qual_decl_value, /* value */
};

static MI_QualifierDecl Revision_qual_decl =
{
    (char*)"Revision", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Schema_qual_decl =
{
    (char*)"Schema", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Source_qual_decl =
{
    (char*)"Source", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl SourceType_qual_decl =
{
    (char*)"SourceType", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean Static_qual_decl_value = 0;

static MI_QualifierDecl Static_qual_decl =
{
    (char*)"Static", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Static_qual_decl_value, /* value */
};

static MI_QualifierDecl Syntax_qual_decl =
{
    (char*)"Syntax", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl SyntaxType_qual_decl =
{
    (char*)"SyntaxType", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_Boolean Terminal_qual_decl_value = 0;

static MI_QualifierDecl Terminal_qual_decl =
{
    (char*)"Terminal", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    &Terminal_qual_decl_value, /* value */
};

static MI_QualifierDecl TriggerType_qual_decl =
{
    (char*)"TriggerType", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl UMLPackagePath_qual_decl =
{
    (char*)"UMLPackagePath", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Units_qual_decl =
{
    (char*)"Units", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl UnknownValues_qual_decl =
{
    (char*)"UnknownValues", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl UnsupportedValues_qual_decl =
{
    (char*)"UnsupportedValues", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl ValueMap_qual_decl =
{
    (char*)"ValueMap", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Values_qual_decl =
{
    (char*)"Values", /* name */
    MI_STRINGA, /* type */
    0, /* subscript */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    NULL, /* value */
};

static MI_QualifierDecl Version_qual_decl =
{
    (char*)"Version", /* name */
    MI_STRING, /* type */
    0, /* subscript */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED, /* flavor */
    NULL, /* value */
};

static MI_Boolean Weak_qual_decl_value = 0;

static MI_QualifierDecl Weak_qual_decl =
{
    (char*)"Weak", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    &Weak_qual_decl_value, /* value */
};

static MI_Boolean Write_qual_decl_value = 0;

static MI_QualifierDecl Write_qual_decl =
{
    (char*)"Write", /* name */
    MI_BOOLEAN, /* type */
    0, /* subscript */
    MI_FLAG_PROPERTY, /* scope */
    0, /* flavor */
    &Write_qual_decl_value, /* value */
};

MI_QualifierDecl* g_qualifierDecls[] =
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
    &DN_qual_decl,
    &Delete_qual_decl,
    &Deprecated_qual_decl,
    &Description_qual_decl,
    &DisplayDescription_qual_decl,
    &DisplayName_qual_decl,
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
    &PUnit_qual_decl,
    &Propagated_qual_decl,
    &PropertyConstraint_qual_decl,
    &PropertyUsage_qual_decl,
    &Provider_qual_decl,
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

size_t g_numQualifierDecls = MI_COUNT(g_qualifierDecls);
