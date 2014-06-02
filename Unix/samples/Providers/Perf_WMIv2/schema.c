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
#include "Perf_Embedded.h"
#include "Perf_WithPsSemantics.h"
#include "Perf_NoPsSemantics.h"
#include "Perf_Indication.h"
#include "PerfAssocClass.h"

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
** _Match()
**
**==============================================================================
*/

static int _Match(const MI_Char* p, const MI_Char* q)
{
    if (!p || !q)
        return 0;

    while (*p && *q)
        if (toupper((MI_Uint16)*p++) - toupper((MI_Uint16)*q++))
            return 0;

    return *p == '\0' && *q == '\0';
}

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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ClassVersion_qual_decl =
{
    MI_T("ClassVersion"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Counter_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Counter_qual_decl =
{
    MI_T("Counter"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Counter_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Delete_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Delete_qual_decl =
{
    MI_T("Delete"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Gauge_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Ifdeleted_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Ifdeleted_qual_decl =
{
    MI_T("Ifdeleted"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Invisible_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean IsPUnit_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl IsPUnit_qual_decl =
{
    MI_T("IsPUnit"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Large_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MappingStrings_qual_decl =
{
    MI_T("MappingStrings"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Max_qual_decl =
{
    MI_T("Max"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxLen_qual_decl =
{
    MI_T("MaxLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxValue_qual_decl =
{
    MI_T("MaxValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MethodConstraint_qual_decl =
{
    MI_T("MethodConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Uint32 Min_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl Min_qual_decl =
{
    MI_T("Min"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Min_qual_decl_value, /* value */
};

static MI_CONST MI_Uint32 MinLen_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl MinLen_qual_decl =
{
    MI_T("MinLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &MinLen_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MinValue_qual_decl =
{
    MI_T("MinValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ModelCorrespondence_qual_decl =
{
    MI_T("ModelCorrespondence"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Nonlocal_qual_decl =
{
    MI_T("Nonlocal"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl NonlocalType_qual_decl =
{
    MI_T("NonlocalType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Char* PropertyUsage_qual_decl_value = MI_T("CurrentContext");

static MI_CONST MI_QualifierDecl PropertyUsage_qual_decl =
{
    MI_T("PropertyUsage"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &PropertyUsage_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Provider_qual_decl =
{
    MI_T("Provider"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl PUnit_qual_decl =
{
    MI_T("PUnit"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Read_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl Read_qual_decl =
{
    MI_T("Read"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SourceType_qual_decl =
{
    MI_T("SourceType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SyntaxType_qual_decl =
{
    MI_T("SyntaxType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Terminal_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Terminal_qual_decl =
{
    MI_T("Terminal"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Terminal_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl TriggerType_qual_decl =
{
    MI_T("TriggerType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UMLPackagePath_qual_decl =
{
    MI_T("UMLPackagePath"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
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
    &ClassVersion_qual_decl,
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
** Perf_Embedded
**
**==============================================================================
*/

/* property Perf_Embedded.v_embeddedKey */
static MI_CONST MI_PropertyDecl Perf_Embedded_v_embeddedKey_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0076790D, /* code */
    MI_T("v_embeddedKey"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Embedded, v_embeddedKey), /* offset */
    MI_T("Perf_Embedded"), /* origin */
    MI_T("Perf_Embedded"), /* propagator */
    NULL,
};

/* property Perf_Embedded.v_string */
static MI_CONST MI_PropertyDecl Perf_Embedded_v_string_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766708, /* code */
    MI_T("v_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Embedded, v_string), /* offset */
    MI_T("Perf_Embedded"), /* origin */
    MI_T("Perf_Embedded"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Perf_Embedded_props[] =
{
    &Perf_Embedded_v_embeddedKey_prop,
    &Perf_Embedded_v_string_prop,
};

static MI_CONST MI_ProviderFT Perf_Embedded_funcs =
{
  (MI_ProviderFT_Load)Perf_Embedded_Load,
  (MI_ProviderFT_Unload)Perf_Embedded_Unload,
  (MI_ProviderFT_GetInstance)Perf_Embedded_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Perf_Embedded_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Perf_Embedded_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Perf_Embedded_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Perf_Embedded_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Perf_Embedded */
MI_CONST MI_ClassDecl Perf_Embedded_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0070640D, /* code */
    MI_T("Perf_Embedded"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_Embedded_props, /* properties */
    MI_COUNT(Perf_Embedded_props), /* numProperties */
    sizeof(Perf_Embedded), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Perf_Embedded_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** Perf_WithPsSemantics
**
**==============================================================================
*/

/* property Perf_WithPsSemantics.v_sint8 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_sint8_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763807, /* code */
    MI_T("v_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_sint8), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_uint16 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_uint16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_uint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_uint16), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_sint32 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_sint32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_sint32), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_uint64_key */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_uint64_key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0076790C, /* code */
    MI_T("v_uint64_key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_uint64_key), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_string */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_string_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766708, /* code */
    MI_T("v_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_string), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_boolean */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_boolean_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766E09, /* code */
    MI_T("v_boolean"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_boolean), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_real32 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_real32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_real32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_real32), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_real64 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_real64_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763408, /* code */
    MI_T("v_real64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_real64), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_datetime */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_datetime_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076650A, /* code */
    MI_T("v_datetime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_datetime), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_WithPsSemantics.v_char16 */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_char16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_char16), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Perf_WithPsSemantics_v_embedded_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_WithPsSemantics_v_embedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_WithPsSemantics_v_embedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_WithPsSemantics_v_embedded_quals[] =
{
    &Perf_WithPsSemantics_v_embedded_EmbeddedInstance_qual,
};

/* property Perf_WithPsSemantics.v_embedded */
static MI_CONST MI_PropertyDecl Perf_WithPsSemantics_v_embedded_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076640A, /* code */
    MI_T("v_embedded"), /* name */
    Perf_WithPsSemantics_v_embedded_quals, /* qualifiers */
    MI_COUNT(Perf_WithPsSemantics_v_embedded_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics, v_embedded), /* offset */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Perf_WithPsSemantics_props[] =
{
    &Perf_WithPsSemantics_v_sint8_prop,
    &Perf_WithPsSemantics_v_uint16_prop,
    &Perf_WithPsSemantics_v_sint32_prop,
    &Perf_WithPsSemantics_v_uint64_key_prop,
    &Perf_WithPsSemantics_v_string_prop,
    &Perf_WithPsSemantics_v_boolean_prop,
    &Perf_WithPsSemantics_v_real32_prop,
    &Perf_WithPsSemantics_v_real64_prop,
    &Perf_WithPsSemantics_v_datetime_prop,
    &Perf_WithPsSemantics_v_char16_prop,
    &Perf_WithPsSemantics_v_embedded_prop,
};

/* parameter Perf_WithPsSemantics.SetBehaviour(): maxInstances */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_SetBehaviour_maxInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D730C, /* code */
    MI_T("maxInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_SetBehaviour, maxInstances), /* offset */
};

/* parameter Perf_WithPsSemantics.SetBehaviour(): streamInstances */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_SetBehaviour_streamInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073730F, /* code */
    MI_T("streamInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_SetBehaviour, streamInstances), /* offset */
};

/* parameter Perf_WithPsSemantics.SetBehaviour(): psSemanticsFlags */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_SetBehaviour_psSemanticsFlags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707310, /* code */
    MI_T("psSemanticsFlags"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_SetBehaviour, psSemanticsFlags), /* offset */
};

/* parameter Perf_WithPsSemantics.SetBehaviour(): psSemanticsCount */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_SetBehaviour_psSemanticsCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707410, /* code */
    MI_T("psSemanticsCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_SetBehaviour, psSemanticsCount), /* offset */
};

/* parameter Perf_WithPsSemantics.SetBehaviour(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_SetBehaviour_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_SetBehaviour, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_WithPsSemantics_SetBehaviour_params[] =
{
    &Perf_WithPsSemantics_SetBehaviour_MIReturn_param,
    &Perf_WithPsSemantics_SetBehaviour_maxInstances_param,
    &Perf_WithPsSemantics_SetBehaviour_streamInstances_param,
    &Perf_WithPsSemantics_SetBehaviour_psSemanticsFlags_param,
    &Perf_WithPsSemantics_SetBehaviour_psSemanticsCount_param,
};

/* method Perf_WithPsSemantics.SetBehaviour() */
MI_CONST MI_MethodDecl Perf_WithPsSemantics_SetBehaviour_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0073720C, /* code */
    MI_T("SetBehaviour"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_WithPsSemantics_SetBehaviour_params, /* parameters */
    MI_COUNT(Perf_WithPsSemantics_SetBehaviour_params), /* numParameters */
    sizeof(Perf_WithPsSemantics_SetBehaviour), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_WithPsSemantics_Invoke_SetBehaviour, /* method */
};

static MI_CONST MI_Char* Perf_WithPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_WithPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_WithPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_WithPsSemantics_PingBackParameters_inbound_quals[] =
{
    &Perf_WithPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual,
};

/* parameter Perf_WithPsSemantics.PingBackParameters(): inbound */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_PingBackParameters_inbound_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00696407, /* code */
    MI_T("inbound"), /* name */
    Perf_WithPsSemantics_PingBackParameters_inbound_quals, /* qualifiers */
    MI_COUNT(Perf_WithPsSemantics_PingBackParameters_inbound_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_PingBackParameters, inbound), /* offset */
};

static MI_CONST MI_Char* Perf_WithPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_WithPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_WithPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_WithPsSemantics_PingBackParameters_outbound_quals[] =
{
    &Perf_WithPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual,
};

/* parameter Perf_WithPsSemantics.PingBackParameters(): outbound */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_PingBackParameters_outbound_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6408, /* code */
    MI_T("outbound"), /* name */
    Perf_WithPsSemantics_PingBackParameters_outbound_quals, /* qualifiers */
    MI_COUNT(Perf_WithPsSemantics_PingBackParameters_outbound_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_PingBackParameters, outbound), /* offset */
};

/* parameter Perf_WithPsSemantics.PingBackParameters(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_PingBackParameters_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_PingBackParameters, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_WithPsSemantics_PingBackParameters_params[] =
{
    &Perf_WithPsSemantics_PingBackParameters_MIReturn_param,
    &Perf_WithPsSemantics_PingBackParameters_inbound_param,
    &Perf_WithPsSemantics_PingBackParameters_outbound_param,
};

/* method Perf_WithPsSemantics.PingBackParameters() */
MI_CONST MI_MethodDecl Perf_WithPsSemantics_PingBackParameters_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00707312, /* code */
    MI_T("PingBackParameters"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_WithPsSemantics_PingBackParameters_params, /* parameters */
    MI_COUNT(Perf_WithPsSemantics_PingBackParameters_params), /* numParameters */
    sizeof(Perf_WithPsSemantics_PingBackParameters), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_WithPsSemantics_Invoke_PingBackParameters, /* method */
};

static MI_CONST MI_Char* Perf_WithPsSemantics_streamingInstances_instances_EmbeddedInstance_qual_value = MI_T("Perf_WithPsSemantics");

static MI_CONST MI_Qualifier Perf_WithPsSemantics_streamingInstances_instances_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_WithPsSemantics_streamingInstances_instances_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_WithPsSemantics_streamingInstances_instances_quals[] =
{
    &Perf_WithPsSemantics_streamingInstances_instances_EmbeddedInstance_qual,
};

/* parameter Perf_WithPsSemantics.streamingInstances(): instances */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_streamingInstances_instances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x00697309, /* code */
    MI_T("instances"), /* name */
    Perf_WithPsSemantics_streamingInstances_instances_quals, /* qualifiers */
    MI_COUNT(Perf_WithPsSemantics_streamingInstances_instances_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Perf_WithPsSemantics"), /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
};

/* parameter Perf_WithPsSemantics.streamingInstances(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_streamingInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_streamingInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_WithPsSemantics_streamingInstances_params[] =
{
    &Perf_WithPsSemantics_streamingInstances_MIReturn_param,
    &Perf_WithPsSemantics_streamingInstances_instances_param,
};

/* method Perf_WithPsSemantics.streamingInstances() */
MI_CONST MI_MethodDecl Perf_WithPsSemantics_streamingInstances_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00737312, /* code */
    MI_T("streamingInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_WithPsSemantics_streamingInstances_params, /* parameters */
    MI_COUNT(Perf_WithPsSemantics_streamingInstances_params), /* numParameters */
    sizeof(Perf_WithPsSemantics_streamingInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_WithPsSemantics_Invoke_streamingInstances, /* method */
};

/* parameter Perf_WithPsSemantics.streamingPrimitive(): numbers */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_streamingPrimitive_numbers_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x006E7307, /* code */
    MI_T("numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
};

/* parameter Perf_WithPsSemantics.streamingPrimitive(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_WithPsSemantics_streamingPrimitive_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_WithPsSemantics_streamingPrimitive, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_WithPsSemantics_streamingPrimitive_params[] =
{
    &Perf_WithPsSemantics_streamingPrimitive_MIReturn_param,
    &Perf_WithPsSemantics_streamingPrimitive_numbers_param,
};

/* method Perf_WithPsSemantics.streamingPrimitive() */
MI_CONST MI_MethodDecl Perf_WithPsSemantics_streamingPrimitive_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736512, /* code */
    MI_T("streamingPrimitive"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_WithPsSemantics_streamingPrimitive_params, /* parameters */
    MI_COUNT(Perf_WithPsSemantics_streamingPrimitive_params), /* numParameters */
    sizeof(Perf_WithPsSemantics_streamingPrimitive), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_WithPsSemantics"), /* origin */
    MI_T("Perf_WithPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_WithPsSemantics_Invoke_streamingPrimitive, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Perf_WithPsSemantics_meths[] =
{
    &Perf_WithPsSemantics_SetBehaviour_rtti,
    &Perf_WithPsSemantics_PingBackParameters_rtti,
    &Perf_WithPsSemantics_streamingInstances_rtti,
    &Perf_WithPsSemantics_streamingPrimitive_rtti,
};

static MI_CONST MI_ProviderFT Perf_WithPsSemantics_funcs =
{
  (MI_ProviderFT_Load)Perf_WithPsSemantics_Load,
  (MI_ProviderFT_Unload)Perf_WithPsSemantics_Unload,
  (MI_ProviderFT_GetInstance)Perf_WithPsSemantics_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Perf_WithPsSemantics_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Perf_WithPsSemantics_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Perf_WithPsSemantics_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Perf_WithPsSemantics_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Perf_WithPsSemantics */
MI_CONST MI_ClassDecl Perf_WithPsSemantics_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00707314, /* code */
    MI_T("Perf_WithPsSemantics"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_WithPsSemantics_props, /* properties */
    MI_COUNT(Perf_WithPsSemantics_props), /* numProperties */
    sizeof(Perf_WithPsSemantics), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Perf_WithPsSemantics_meths, /* methods */
    MI_COUNT(Perf_WithPsSemantics_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Perf_WithPsSemantics_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** Perf_NoPsSemantics
**
**==============================================================================
*/

/* property Perf_NoPsSemantics.v_sint8 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_sint8_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763807, /* code */
    MI_T("v_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_sint8), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_uint16 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_uint16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_uint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_uint16), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_sint32 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_sint32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_sint32), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_uint64_key */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_uint64_key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0076790C, /* code */
    MI_T("v_uint64_key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_uint64_key), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_string */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_string_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766708, /* code */
    MI_T("v_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_string), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_boolean */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_boolean_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766E09, /* code */
    MI_T("v_boolean"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_boolean), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_real32 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_real32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_real32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_real32), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_real64 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_real64_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763408, /* code */
    MI_T("v_real64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_real64), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_datetime */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_datetime_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076650A, /* code */
    MI_T("v_datetime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_datetime), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

/* property Perf_NoPsSemantics.v_char16 */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_char16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_char16), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Perf_NoPsSemantics_v_embedded_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_NoPsSemantics_v_embedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_NoPsSemantics_v_embedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_NoPsSemantics_v_embedded_quals[] =
{
    &Perf_NoPsSemantics_v_embedded_EmbeddedInstance_qual,
};

/* property Perf_NoPsSemantics.v_embedded */
static MI_CONST MI_PropertyDecl Perf_NoPsSemantics_v_embedded_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076640A, /* code */
    MI_T("v_embedded"), /* name */
    Perf_NoPsSemantics_v_embedded_quals, /* qualifiers */
    MI_COUNT(Perf_NoPsSemantics_v_embedded_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics, v_embedded), /* offset */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Perf_NoPsSemantics_props[] =
{
    &Perf_NoPsSemantics_v_sint8_prop,
    &Perf_NoPsSemantics_v_uint16_prop,
    &Perf_NoPsSemantics_v_sint32_prop,
    &Perf_NoPsSemantics_v_uint64_key_prop,
    &Perf_NoPsSemantics_v_string_prop,
    &Perf_NoPsSemantics_v_boolean_prop,
    &Perf_NoPsSemantics_v_real32_prop,
    &Perf_NoPsSemantics_v_real64_prop,
    &Perf_NoPsSemantics_v_datetime_prop,
    &Perf_NoPsSemantics_v_char16_prop,
    &Perf_NoPsSemantics_v_embedded_prop,
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): maxInstances */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_maxInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D730C, /* code */
    MI_T("maxInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, maxInstances), /* offset */
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): streamInstances */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_streamInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073730F, /* code */
    MI_T("streamInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, streamInstances), /* offset */
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): psSemanticsFlags */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_psSemanticsFlags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707310, /* code */
    MI_T("psSemanticsFlags"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, psSemanticsFlags), /* offset */
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): psSemanticsCount */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_psSemanticsCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707410, /* code */
    MI_T("psSemanticsCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, psSemanticsCount), /* offset */
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): enablePostNumberInstances */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_enablePostNumberInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657319, /* code */
    MI_T("enablePostNumberInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, enablePostNumberInstances), /* offset */
};

/* parameter Perf_NoPsSemantics.SetBehaviour(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_SetBehaviour_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_SetBehaviour, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_SetBehaviour_params[] =
{
    &Perf_NoPsSemantics_SetBehaviour_MIReturn_param,
    &Perf_NoPsSemantics_SetBehaviour_maxInstances_param,
    &Perf_NoPsSemantics_SetBehaviour_streamInstances_param,
    &Perf_NoPsSemantics_SetBehaviour_psSemanticsFlags_param,
    &Perf_NoPsSemantics_SetBehaviour_psSemanticsCount_param,
    &Perf_NoPsSemantics_SetBehaviour_enablePostNumberInstances_param,
};

/* method Perf_NoPsSemantics.SetBehaviour() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_SetBehaviour_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0073720C, /* code */
    MI_T("SetBehaviour"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_SetBehaviour_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_SetBehaviour_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_SetBehaviour), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_SetBehaviour, /* method */
};

static MI_CONST MI_Char* Perf_NoPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_NoPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_NoPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_NoPsSemantics_PingBackParameters_inbound_quals[] =
{
    &Perf_NoPsSemantics_PingBackParameters_inbound_EmbeddedInstance_qual,
};

/* parameter Perf_NoPsSemantics.PingBackParameters(): inbound */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_PingBackParameters_inbound_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00696407, /* code */
    MI_T("inbound"), /* name */
    Perf_NoPsSemantics_PingBackParameters_inbound_quals, /* qualifiers */
    MI_COUNT(Perf_NoPsSemantics_PingBackParameters_inbound_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_PingBackParameters, inbound), /* offset */
};

static MI_CONST MI_Char* Perf_NoPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_NoPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_NoPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_NoPsSemantics_PingBackParameters_outbound_quals[] =
{
    &Perf_NoPsSemantics_PingBackParameters_outbound_EmbeddedInstance_qual,
};

/* parameter Perf_NoPsSemantics.PingBackParameters(): outbound */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_PingBackParameters_outbound_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6408, /* code */
    MI_T("outbound"), /* name */
    Perf_NoPsSemantics_PingBackParameters_outbound_quals, /* qualifiers */
    MI_COUNT(Perf_NoPsSemantics_PingBackParameters_outbound_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_PingBackParameters, outbound), /* offset */
};

/* parameter Perf_NoPsSemantics.PingBackParameters(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_PingBackParameters_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_PingBackParameters, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_PingBackParameters_params[] =
{
    &Perf_NoPsSemantics_PingBackParameters_MIReturn_param,
    &Perf_NoPsSemantics_PingBackParameters_inbound_param,
    &Perf_NoPsSemantics_PingBackParameters_outbound_param,
};

/* method Perf_NoPsSemantics.PingBackParameters() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_PingBackParameters_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00707312, /* code */
    MI_T("PingBackParameters"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_PingBackParameters_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_PingBackParameters_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_PingBackParameters), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_PingBackParameters, /* method */
};

static MI_CONST MI_Char* Perf_NoPsSemantics_streamingInstances_instances_EmbeddedInstance_qual_value = MI_T("Perf_WithPsSemantics");

static MI_CONST MI_Qualifier Perf_NoPsSemantics_streamingInstances_instances_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_NoPsSemantics_streamingInstances_instances_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_NoPsSemantics_streamingInstances_instances_quals[] =
{
    &Perf_NoPsSemantics_streamingInstances_instances_EmbeddedInstance_qual,
};

/* parameter Perf_NoPsSemantics.streamingInstances(): instances */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_streamingInstances_instances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x00697309, /* code */
    MI_T("instances"), /* name */
    Perf_NoPsSemantics_streamingInstances_instances_quals, /* qualifiers */
    MI_COUNT(Perf_NoPsSemantics_streamingInstances_instances_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Perf_WithPsSemantics"), /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
};

/* parameter Perf_NoPsSemantics.streamingInstances(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_streamingInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_streamingInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_streamingInstances_params[] =
{
    &Perf_NoPsSemantics_streamingInstances_MIReturn_param,
    &Perf_NoPsSemantics_streamingInstances_instances_param,
};

/* method Perf_NoPsSemantics.streamingInstances() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_streamingInstances_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00737312, /* code */
    MI_T("streamingInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_streamingInstances_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_streamingInstances_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_streamingInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_streamingInstances, /* method */
};

/* parameter Perf_NoPsSemantics.streamingPrimitive(): numbers */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_streamingPrimitive_numbers_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x006E7307, /* code */
    MI_T("numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
};

/* parameter Perf_NoPsSemantics.streamingPrimitive(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_streamingPrimitive_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_streamingPrimitive, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_streamingPrimitive_params[] =
{
    &Perf_NoPsSemantics_streamingPrimitive_MIReturn_param,
    &Perf_NoPsSemantics_streamingPrimitive_numbers_param,
};

/* method Perf_NoPsSemantics.streamingPrimitive() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_streamingPrimitive_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736512, /* code */
    MI_T("streamingPrimitive"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_streamingPrimitive_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_streamingPrimitive_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_streamingPrimitive), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_streamingPrimitive, /* method */
};

/* parameter Perf_NoPsSemantics.GetNumberPostedInstances(): numberInstances */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_GetNumberPostedInstances_numberInstances_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006E730F, /* code */
    MI_T("numberInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_GetNumberPostedInstances, numberInstances), /* offset */
};

/* parameter Perf_NoPsSemantics.GetNumberPostedInstances(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_GetNumberPostedInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_GetNumberPostedInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_GetNumberPostedInstances_params[] =
{
    &Perf_NoPsSemantics_GetNumberPostedInstances_MIReturn_param,
    &Perf_NoPsSemantics_GetNumberPostedInstances_numberInstances_param,
};

/* method Perf_NoPsSemantics.GetNumberPostedInstances() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_GetNumberPostedInstances_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00677318, /* code */
    MI_T("GetNumberPostedInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_GetNumberPostedInstances_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_GetNumberPostedInstances_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_GetNumberPostedInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_GetNumberPostedInstances, /* method */
};

/* parameter Perf_NoPsSemantics.StopPosting(): MIReturn */
static MI_CONST MI_ParameterDecl Perf_NoPsSemantics_StopPosting_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_NoPsSemantics_StopPosting, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Perf_NoPsSemantics_StopPosting_params[] =
{
    &Perf_NoPsSemantics_StopPosting_MIReturn_param,
};

/* method Perf_NoPsSemantics.StopPosting() */
MI_CONST MI_MethodDecl Perf_NoPsSemantics_StopPosting_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0073670B, /* code */
    MI_T("StopPosting"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_StopPosting_params, /* parameters */
    MI_COUNT(Perf_NoPsSemantics_StopPosting_params), /* numParameters */
    sizeof(Perf_NoPsSemantics_StopPosting), /* size */
    MI_UINT32, /* returnType */
    MI_T("Perf_NoPsSemantics"), /* origin */
    MI_T("Perf_NoPsSemantics"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Perf_NoPsSemantics_Invoke_StopPosting, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Perf_NoPsSemantics_meths[] =
{
    &Perf_NoPsSemantics_SetBehaviour_rtti,
    &Perf_NoPsSemantics_PingBackParameters_rtti,
    &Perf_NoPsSemantics_streamingInstances_rtti,
    &Perf_NoPsSemantics_streamingPrimitive_rtti,
    &Perf_NoPsSemantics_GetNumberPostedInstances_rtti,
    &Perf_NoPsSemantics_StopPosting_rtti,
};

static MI_CONST MI_ProviderFT Perf_NoPsSemantics_funcs =
{
  (MI_ProviderFT_Load)Perf_NoPsSemantics_Load,
  (MI_ProviderFT_Unload)Perf_NoPsSemantics_Unload,
  (MI_ProviderFT_GetInstance)Perf_NoPsSemantics_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Perf_NoPsSemantics_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Perf_NoPsSemantics_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Perf_NoPsSemantics_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Perf_NoPsSemantics_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Perf_NoPsSemantics */
MI_CONST MI_ClassDecl Perf_NoPsSemantics_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00707312, /* code */
    MI_T("Perf_NoPsSemantics"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Perf_NoPsSemantics_props, /* properties */
    MI_COUNT(Perf_NoPsSemantics_props), /* numProperties */
    sizeof(Perf_NoPsSemantics), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Perf_NoPsSemantics_meths, /* methods */
    MI_COUNT(Perf_NoPsSemantics_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Perf_NoPsSemantics_funcs, /* functions */
    NULL /* owningClass */
};

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
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
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

static MI_CONST MI_Char* CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Indication.IndicationIdentifier"),
};

static MI_CONST MI_ConstStringA CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual_value =
{
    CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_CorrelatedIndications_quals[] =
{
    &CIM_Indication_CorrelatedIndications_ModelCorrespondence_qual,
};

/* property CIM_Indication.CorrelatedIndications */
static MI_CONST MI_PropertyDecl CIM_Indication_CorrelatedIndications_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00637315, /* code */
    MI_T("CorrelatedIndications"), /* name */
    CIM_Indication_CorrelatedIndications_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_CorrelatedIndications_quals), /* numQualifiers */
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
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
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

static MI_CONST MI_Char* CIM_Indication_PerceivedSeverity_ValueMap_qual_data_value[] =
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

static MI_CONST MI_ConstStringA CIM_Indication_PerceivedSeverity_ValueMap_qual_value =
{
    CIM_Indication_PerceivedSeverity_ValueMap_qual_data_value,
    MI_COUNT(CIM_Indication_PerceivedSeverity_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_PerceivedSeverity_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_PerceivedSeverity_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Indication_PerceivedSeverity_Values_qual_data_value[] =
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

static MI_CONST MI_ConstStringA CIM_Indication_PerceivedSeverity_Values_qual_value =
{
    CIM_Indication_PerceivedSeverity_Values_qual_data_value,
    MI_COUNT(CIM_Indication_PerceivedSeverity_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_PerceivedSeverity_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Indication_PerceivedSeverity_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_PerceivedSeverity_quals[] =
{
    &CIM_Indication_PerceivedSeverity_ValueMap_qual,
    &CIM_Indication_PerceivedSeverity_Values_qual,
};

/* property CIM_Indication.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    CIM_Indication_PerceivedSeverity_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_PerceivedSeverity_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, PerceivedSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Indication_OtherSeverity_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_AlertIndication.PerceivedSeverity"),
};

static MI_CONST MI_ConstStringA CIM_Indication_OtherSeverity_ModelCorrespondence_qual_value =
{
    CIM_Indication_OtherSeverity_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Indication_OtherSeverity_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_OtherSeverity_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_OtherSeverity_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_OtherSeverity_quals[] =
{
    &CIM_Indication_OtherSeverity_ModelCorrespondence_qual,
};

/* property CIM_Indication.OtherSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_OtherSeverity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F790D, /* code */
    MI_T("OtherSeverity"), /* name */
    CIM_Indication_OtherSeverity_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_OtherSeverity_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, OtherSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Indication_IndicationFilterName_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_IndicationFilter.Name"),
};

static MI_CONST MI_ConstStringA CIM_Indication_IndicationFilterName_ModelCorrespondence_qual_value =
{
    CIM_Indication_IndicationFilterName_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Indication_IndicationFilterName_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_IndicationFilterName_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_IndicationFilterName_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_IndicationFilterName_quals[] =
{
    &CIM_Indication_IndicationFilterName_ModelCorrespondence_qual,
};

/* property CIM_Indication.IndicationFilterName */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationFilterName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00696514, /* code */
    MI_T("IndicationFilterName"), /* name */
    CIM_Indication_IndicationFilterName_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_IndicationFilterName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationFilterName), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Indication_SequenceContext_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Indication.SequenceNumber"),
};

static MI_CONST MI_ConstStringA CIM_Indication_SequenceContext_ModelCorrespondence_qual_value =
{
    CIM_Indication_SequenceContext_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Indication_SequenceContext_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_SequenceContext_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_SequenceContext_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_SequenceContext_quals[] =
{
    &CIM_Indication_SequenceContext_ModelCorrespondence_qual,
};

/* property CIM_Indication.SequenceContext */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceContext_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0073740F, /* code */
    MI_T("SequenceContext"), /* name */
    CIM_Indication_SequenceContext_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_SequenceContext_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceContext), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Indication_SequenceNumber_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Indication.SequenceContext"),
};

static MI_CONST MI_ConstStringA CIM_Indication_SequenceNumber_ModelCorrespondence_qual_value =
{
    CIM_Indication_SequenceNumber_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Indication_SequenceNumber_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Indication_SequenceNumber_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Indication_SequenceNumber_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_SequenceNumber_quals[] =
{
    &CIM_Indication_SequenceNumber_ModelCorrespondence_qual,
};

/* property CIM_Indication.SequenceNumber */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceNumber_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0073720E, /* code */
    MI_T("SequenceNumber"), /* name */
    CIM_Indication_SequenceNumber_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_SequenceNumber_quals), /* numQualifiers */
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
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
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
    CIM_Indication_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_quals), /* numQualifiers */
    CIM_Indication_props, /* properties */
    MI_COUNT(CIM_Indication_props), /* numProperties */
    sizeof(CIM_Indication), /* size */
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
** Perf_Indication
**
**==============================================================================
*/

/* property Perf_Indication.v_sint8 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_sint8_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763807, /* code */
    MI_T("v_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_sint8), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_uint16 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_uint16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_uint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_uint16), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_sint32 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_sint32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_sint32), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_uint64_key */
static MI_CONST MI_PropertyDecl Perf_Indication_v_uint64_key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0076790C, /* code */
    MI_T("v_uint64_key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_uint64_key), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_string */
static MI_CONST MI_PropertyDecl Perf_Indication_v_string_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766708, /* code */
    MI_T("v_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_string), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_boolean */
static MI_CONST MI_PropertyDecl Perf_Indication_v_boolean_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00766E09, /* code */
    MI_T("v_boolean"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_boolean), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_real32 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_real32_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763208, /* code */
    MI_T("v_real32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_real32), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_real64 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_real64_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763408, /* code */
    MI_T("v_real64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_real64), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_datetime */
static MI_CONST MI_PropertyDecl Perf_Indication_v_datetime_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076650A, /* code */
    MI_T("v_datetime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_datetime), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

/* property Perf_Indication.v_char16 */
static MI_CONST MI_PropertyDecl Perf_Indication_v_char16_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00763608, /* code */
    MI_T("v_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_char16), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Perf_Indication_v_embedded_EmbeddedInstance_qual_value = MI_T("Perf_Embedded");

static MI_CONST MI_Qualifier Perf_Indication_v_embedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_Indication_v_embedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_Indication_v_embedded_quals[] =
{
    &Perf_Indication_v_embedded_EmbeddedInstance_qual,
};

/* property Perf_Indication.v_embedded */
static MI_CONST MI_PropertyDecl Perf_Indication_v_embedded_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0076640A, /* code */
    MI_T("v_embedded"), /* name */
    Perf_Indication_v_embedded_quals, /* qualifiers */
    MI_COUNT(Perf_Indication_v_embedded_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Perf_Embedded"), /* className */
    0, /* subscript */
    offsetof(Perf_Indication, v_embedded), /* offset */
    MI_T("Perf_Indication"), /* origin */
    MI_T("Perf_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Perf_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &Perf_Indication_v_sint8_prop,
    &Perf_Indication_v_uint16_prop,
    &Perf_Indication_v_sint32_prop,
    &Perf_Indication_v_uint64_key_prop,
    &Perf_Indication_v_string_prop,
    &Perf_Indication_v_boolean_prop,
    &Perf_Indication_v_real32_prop,
    &Perf_Indication_v_real64_prop,
    &Perf_Indication_v_datetime_prop,
    &Perf_Indication_v_char16_prop,
    &Perf_Indication_v_embedded_prop,
};

static MI_CONST MI_ProviderFT Perf_Indication_funcs =
{
  (MI_ProviderFT_Load)Perf_Indication_Load,
  (MI_ProviderFT_Unload)Perf_Indication_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)Perf_Indication_EnableIndications,
  (MI_ProviderFT_DisableIndications)Perf_Indication_DisableIndications,
  (MI_ProviderFT_Subscribe)Perf_Indication_Subscribe,
  (MI_ProviderFT_Unsubscribe)Perf_Indication_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* Perf_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier Perf_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Perf_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Perf_Indication_quals[] =
{
    &Perf_Indication_UMLPackagePath_qual,
};

/* class Perf_Indication */
MI_CONST MI_ClassDecl Perf_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00706E0F, /* code */
    MI_T("Perf_Indication"), /* name */
    Perf_Indication_quals, /* qualifiers */
    MI_COUNT(Perf_Indication_quals), /* numQualifiers */
    Perf_Indication_props, /* properties */
    MI_COUNT(Perf_Indication_props), /* numProperties */
    sizeof(Perf_Indication), /* size */
    MI_T("CIM_Indication"), /* superClass */
    &CIM_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Perf_Indication_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** PerfAssocClass
**
**==============================================================================
*/

/* property PerfAssocClass.antecedent */
static MI_CONST MI_PropertyDecl PerfAssocClass_antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0061740A, /* code */
    MI_T("antecedent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Perf_WithPsSemantics"), /* className */
    0, /* subscript */
    offsetof(PerfAssocClass, antecedent), /* offset */
    MI_T("PerfAssocClass"), /* origin */
    MI_T("PerfAssocClass"), /* propagator */
    NULL,
};

/* property PerfAssocClass.dependent */
static MI_CONST MI_PropertyDecl PerfAssocClass_dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00647409, /* code */
    MI_T("dependent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Perf_NoPsSemantics"), /* className */
    0, /* subscript */
    offsetof(PerfAssocClass, dependent), /* offset */
    MI_T("PerfAssocClass"), /* origin */
    MI_T("PerfAssocClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST PerfAssocClass_props[] =
{
    &PerfAssocClass_antecedent_prop,
    &PerfAssocClass_dependent_prop,
};

static void MI_CALL PerfAssocClass_AssociatorInstances(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MI_Instance* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_z_ const MI_Char* role,
    _In_z_ const MI_Char* resultRole,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    if (Perf_WithPsSemantics_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")) && 
            _Match(resultRole, MI_T("dependent")))
        {
            PerfAssocClass_AssociatorInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Perf_WithPsSemantics*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Perf_NoPsSemantics_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")) && 
            _Match(resultRole, MI_T("antecedent")))
        {
            PerfAssocClass_AssociatorInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Perf_NoPsSemantics*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL PerfAssocClass_ReferenceInstances(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MI_Instance* instanceName,
    _In_z_ const MI_Char* role,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    if (Perf_WithPsSemantics_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")))
        {
            PerfAssocClass_ReferenceInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Perf_WithPsSemantics*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Perf_NoPsSemantics_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")))
        {
            PerfAssocClass_ReferenceInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Perf_NoPsSemantics*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT PerfAssocClass_funcs =
{
  (MI_ProviderFT_Load)PerfAssocClass_Load,
  (MI_ProviderFT_Unload)PerfAssocClass_Unload,
  (MI_ProviderFT_GetInstance)PerfAssocClass_GetInstance,
  (MI_ProviderFT_EnumerateInstances)PerfAssocClass_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)PerfAssocClass_CreateInstance,
  (MI_ProviderFT_ModifyInstance)PerfAssocClass_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)PerfAssocClass_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)PerfAssocClass_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)PerfAssocClass_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class PerfAssocClass */
MI_CONST MI_ClassDecl PerfAssocClass_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0070730E, /* code */
    MI_T("PerfAssocClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    PerfAssocClass_props, /* properties */
    MI_COUNT(PerfAssocClass_props), /* numProperties */
    sizeof(PerfAssocClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &PerfAssocClass_funcs, /* functions */
    NULL /* owningClass */
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
    &PerfAssocClass_rtti,
    &Perf_Embedded_rtti,
    &Perf_Indication_rtti,
    &Perf_NoPsSemantics_rtti,
    &Perf_WithPsSemantics_rtti,
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

