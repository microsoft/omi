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
#include "MyEmptyClass.h"
#include "MyEmptyDerivedClass.h"
#include "MyEmptySecondDerivedClass.h"
#include "MySimpleQualClass.h"
#include "MyArrayQualClass.h"
#include "MySimplePropertiesClass.h"
#include "MyEmbeddedPropertiesClass.h"
#include "MySimplePropertiesDerivedClass.h"
#include "MyFooClass.h"
#include "MySimplePropertiesSimpleQualsClass.h"
#include "MySimplePropertiesArrayQualsClass.h"
#include "MyArrayPropertiesClass.h"
#include "MyArrayPropertiesSimpleQualsClass.h"
#include "MyArrayPropertiesArrayQualsClass.h"
#include "MyNoParamMethodsClass.h"
#include "MyNoParamSimpleQualsMethodsClass.h"
#include "MyNoParamArrayQualsMethodsClass.h"
#include "MySimpleParamMethodsClass.h"
#include "MyArrayParamMethodsClass.h"
#include "MyArrayParamSimpleQualsMethodsClass.h"
#include "MyArrayParamArrayQualsMethodsClass.h"
#include "MySimpleParamSimpleQualsMethodsClass.h"
#include "MySimpleParamArrayQualsMethodsClass.h"
#include "MyReferenceClass.h"
#include "MyVariousArrayLengthClass.h"
#include "MyOptionTestClass.h"
#include "MyOptionTestDerivedClass.h"
#include "MyClassForTestingAddedEmbeddedQualifier.h"
#include "MyClassRestrictedQualsOnBaseElements.h"
#include "MyDerivedClassOfRestrictedQualsOnBaseElements.h"

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

static MI_CONST MI_QualifierDecl BooleanArrayQual_qual_decl =
{
    MI_T("BooleanArrayQual"), /* name */
    MI_BOOLEANA, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean BooleanQual_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl BooleanQual_qual_decl =
{
    MI_T("BooleanQual"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    &BooleanQual_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Char16ArrayQual_qual_decl =
{
    MI_T("Char16ArrayQual"), /* name */
    MI_CHAR16A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Char16Qual_qual_decl =
{
    MI_T("Char16Qual"), /* name */
    MI_CHAR16, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
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

static MI_CONST MI_QualifierDecl DatetimeArrayQual_qual_decl =
{
    MI_T("DatetimeArrayQual"), /* name */
    MI_DATETIMEA, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl DatetimeQual_qual_decl =
{
    MI_T("DatetimeQual"), /* name */
    MI_DATETIME, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
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

static MI_CONST MI_QualifierDecl Real32ArrayQual_qual_decl =
{
    MI_T("Real32ArrayQual"), /* name */
    MI_REAL32A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Real32Qual_qual_decl =
{
    MI_T("Real32Qual"), /* name */
    MI_REAL32, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Real64ArrayQual_qual_decl =
{
    MI_T("Real64ArrayQual"), /* name */
    MI_REAL64A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Real64Qual_qual_decl =
{
    MI_T("Real64Qual"), /* name */
    MI_REAL64, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
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

static MI_CONST MI_QualifierDecl Sint16ArrayQual_qual_decl =
{
    MI_T("Sint16ArrayQual"), /* name */
    MI_SINT16A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint16Qual_qual_decl =
{
    MI_T("Sint16Qual"), /* name */
    MI_SINT16, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint32ArrayQual_qual_decl =
{
    MI_T("Sint32ArrayQual"), /* name */
    MI_SINT32A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint32Qual_qual_decl =
{
    MI_T("Sint32Qual"), /* name */
    MI_SINT32, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint64ArrayQual_qual_decl =
{
    MI_T("Sint64ArrayQual"), /* name */
    MI_SINT64A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint64Qual_qual_decl =
{
    MI_T("Sint64Qual"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint8ArrayQual_qual_decl =
{
    MI_T("Sint8ArrayQual"), /* name */
    MI_SINT8A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Sint8Qual_qual_decl =
{
    MI_T("Sint8Qual"), /* name */
    MI_SINT8, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
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

static MI_CONST MI_QualifierDecl StringArrayQual_qual_decl =
{
    MI_T("StringArrayQual"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl StringQual_qual_decl =
{
    MI_T("StringQual"), /* name */
    MI_STRING, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
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

static MI_CONST MI_QualifierDecl Uint16ArrayQual_qual_decl =
{
    MI_T("Uint16ArrayQual"), /* name */
    MI_UINT16A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint16Qual_qual_decl =
{
    MI_T("Uint16Qual"), /* name */
    MI_UINT16, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint32ArrayQual_qual_decl =
{
    MI_T("Uint32ArrayQual"), /* name */
    MI_UINT32A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint32Qual_qual_decl =
{
    MI_T("Uint32Qual"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint64ArrayQual_qual_decl =
{
    MI_T("Uint64ArrayQual"), /* name */
    MI_UINT64A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint64Qual_qual_decl =
{
    MI_T("Uint64Qual"), /* name */
    MI_UINT64, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint8ArrayQual_qual_decl =
{
    MI_T("Uint8ArrayQual"), /* name */
    MI_UINT8A, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Uint8Qual_qual_decl =
{
    MI_T("Uint8Qual"), /* name */
    MI_UINT8, /* type */
    MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_TRANSLATABLE, /* flavor */
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
    &BooleanArrayQual_qual_decl,
    &BooleanQual_qual_decl,
    &Char16ArrayQual_qual_decl,
    &Char16Qual_qual_decl,
    &ClassConstraint_qual_decl,
    &Composition_qual_decl,
    &Correlatable_qual_decl,
    &Counter_qual_decl,
    &DatetimeArrayQual_qual_decl,
    &DatetimeQual_qual_decl,
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
    &Real32ArrayQual_qual_decl,
    &Real32Qual_qual_decl,
    &Real64ArrayQual_qual_decl,
    &Real64Qual_qual_decl,
    &Required_qual_decl,
    &Revision_qual_decl,
    &Schema_qual_decl,
    &Sint16ArrayQual_qual_decl,
    &Sint16Qual_qual_decl,
    &Sint32ArrayQual_qual_decl,
    &Sint32Qual_qual_decl,
    &Sint64ArrayQual_qual_decl,
    &Sint64Qual_qual_decl,
    &Sint8ArrayQual_qual_decl,
    &Sint8Qual_qual_decl,
    &Source_qual_decl,
    &SourceType_qual_decl,
    &Static_qual_decl,
    &StringArrayQual_qual_decl,
    &StringQual_qual_decl,
    &Syntax_qual_decl,
    &SyntaxType_qual_decl,
    &Terminal_qual_decl,
    &TriggerType_qual_decl,
    &Uint16ArrayQual_qual_decl,
    &Uint16Qual_qual_decl,
    &Uint32ArrayQual_qual_decl,
    &Uint32Qual_qual_decl,
    &Uint64ArrayQual_qual_decl,
    &Uint64Qual_qual_decl,
    &Uint8ArrayQual_qual_decl,
    &Uint8Qual_qual_decl,
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
** MyEmptyClass
**
**==============================================================================
*/


static MI_CONST MI_ProviderFT MyEmptyClass_funcs =
{
  (MI_ProviderFT_Load)MyEmptyClass_Load,
  (MI_ProviderFT_Unload)MyEmptyClass_Unload,
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

/* class MyEmptyClass */
MI_CONST MI_ClassDecl MyEmptyClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D730C, /* code */
    MI_T("MyEmptyClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyEmptyClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyEmptyClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyEmptyDerivedClass
**
**==============================================================================
*/


static MI_CONST MI_ProviderFT MyEmptyDerivedClass_funcs =
{
  (MI_ProviderFT_Load)MyEmptyDerivedClass_Load,
  (MI_ProviderFT_Unload)MyEmptyDerivedClass_Unload,
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

/* class MyEmptyDerivedClass */
MI_CONST MI_ClassDecl MyEmptyDerivedClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7313, /* code */
    MI_T("MyEmptyDerivedClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyEmptyDerivedClass), /* size */
    MI_T("MyEmptyClass"), /* superClass */
    &MyEmptyClass_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyEmptyDerivedClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyEmptySecondDerivedClass
**
**==============================================================================
*/


static MI_CONST MI_ProviderFT MyEmptySecondDerivedClass_funcs =
{
  (MI_ProviderFT_Load)MyEmptySecondDerivedClass_Load,
  (MI_ProviderFT_Unload)MyEmptySecondDerivedClass_Unload,
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

/* class MyEmptySecondDerivedClass */
MI_CONST MI_ClassDecl MyEmptySecondDerivedClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7319, /* code */
    MI_T("MyEmptySecondDerivedClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyEmptySecondDerivedClass), /* size */
    MI_T("MyEmptyDerivedClass"), /* superClass */
    &MyEmptyDerivedClass_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyEmptySecondDerivedClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimpleQualClass
**
**==============================================================================
*/


static MI_CONST MI_ProviderFT MySimpleQualClass_funcs =
{
  (MI_ProviderFT_Load)MySimpleQualClass_Load,
  (MI_ProviderFT_Unload)MySimpleQualClass_Unload,
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

static MI_CONST MI_Boolean MySimpleQualClass_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MySimpleQualClass_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_BooleanQual_qual_value
};

static MI_CONST MI_Char* MySimpleQualClass_StringQual_qual_value = MI_T("hello&'><\"");

static MI_CONST MI_Qualifier MySimpleQualClass_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_StringQual_qual_value
};

static MI_CONST MI_Char16 MySimpleQualClass_Char16Qual_qual_value = 274;

static MI_CONST MI_Qualifier MySimpleQualClass_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Char16Qual_qual_value
};

static MI_CONST MI_Uint8 MySimpleQualClass_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MySimpleQualClass_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Uint8Qual_qual_value
};

static MI_CONST MI_Sint8 MySimpleQualClass_Sint8Qual_qual_value = -1;

static MI_CONST MI_Qualifier MySimpleQualClass_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Sint8Qual_qual_value
};

static MI_CONST MI_Uint16 MySimpleQualClass_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MySimpleQualClass_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Uint16Qual_qual_value
};

static MI_CONST MI_Sint16 MySimpleQualClass_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MySimpleQualClass_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Sint16Qual_qual_value
};

static MI_CONST MI_Uint32 MySimpleQualClass_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MySimpleQualClass_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Uint32Qual_qual_value
};

static MI_CONST MI_Sint32 MySimpleQualClass_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MySimpleQualClass_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Sint32Qual_qual_value
};

static MI_CONST MI_Uint64 MySimpleQualClass_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MySimpleQualClass_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Uint64Qual_qual_value
};

static MI_CONST MI_Sint64 MySimpleQualClass_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MySimpleQualClass_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Sint64Qual_qual_value
};

static MI_CONST MI_Real32 MySimpleQualClass_Real32Qual_qual_value = (float)1.1;

static MI_CONST MI_Qualifier MySimpleQualClass_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Real32Qual_qual_value
};

static MI_CONST MI_Real64 MySimpleQualClass_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MySimpleQualClass_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_Real64Qual_qual_value
};

static MI_CONST MI_Datetime MySimpleQualClass_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MySimpleQualClass_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MySimpleQualClass_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleQualClass_quals[] =
{
    &MySimpleQualClass_BooleanQual_qual,
    &MySimpleQualClass_StringQual_qual,
    &MySimpleQualClass_Char16Qual_qual,
    &MySimpleQualClass_Uint8Qual_qual,
    &MySimpleQualClass_Sint8Qual_qual,
    &MySimpleQualClass_Uint16Qual_qual,
    &MySimpleQualClass_Sint16Qual_qual,
    &MySimpleQualClass_Uint32Qual_qual,
    &MySimpleQualClass_Sint32Qual_qual,
    &MySimpleQualClass_Uint64Qual_qual,
    &MySimpleQualClass_Sint64Qual_qual,
    &MySimpleQualClass_Real32Qual_qual,
    &MySimpleQualClass_Real64Qual_qual,
    &MySimpleQualClass_DatetimeQual_qual,
};

/* class MySimpleQualClass */
MI_CONST MI_ClassDecl MySimpleQualClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7311, /* code */
    MI_T("MySimpleQualClass"), /* name */
    MySimpleQualClass_quals, /* qualifiers */
    MI_COUNT(MySimpleQualClass_quals), /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MySimpleQualClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MySimpleQualClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayQualClass
**
**==============================================================================
*/


static MI_CONST MI_ProviderFT MyArrayQualClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayQualClass_Load,
  (MI_ProviderFT_Unload)MyArrayQualClass_Unload,
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

static MI_CONST MI_Boolean MyArrayQualClass_BooleanArrayQual_qual_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA MyArrayQualClass_BooleanArrayQual_qual_value =
{
    MyArrayQualClass_BooleanArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_BooleanArrayQual_qual_value
};

static MI_CONST MI_Char* MyArrayQualClass_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("goodbye"),
};

static MI_CONST MI_ConstStringA MyArrayQualClass_StringArrayQual_qual_value =
{
    MyArrayQualClass_StringArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_StringArrayQual_qual_value
};

static MI_CONST MI_Char16 MyArrayQualClass_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MyArrayQualClass_Char16ArrayQual_qual_value =
{
    MyArrayQualClass_Char16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Char16ArrayQual_qual_value
};

static MI_CONST MI_Uint8 MyArrayQualClass_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MyArrayQualClass_Uint8ArrayQual_qual_value =
{
    MyArrayQualClass_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Uint8ArrayQual_qual_value
};

static MI_CONST MI_Sint8 MyArrayQualClass_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MyArrayQualClass_Sint8ArrayQual_qual_value =
{
    MyArrayQualClass_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Sint8ArrayQual_qual_value
};

static MI_CONST MI_Uint16 MyArrayQualClass_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MyArrayQualClass_Uint16ArrayQual_qual_value =
{
    MyArrayQualClass_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Uint16ArrayQual_qual_value
};

static MI_CONST MI_Sint16 MyArrayQualClass_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MyArrayQualClass_Sint16ArrayQual_qual_value =
{
    MyArrayQualClass_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Sint16ArrayQual_qual_value
};

static MI_CONST MI_Uint32 MyArrayQualClass_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MyArrayQualClass_Uint32ArrayQual_qual_value =
{
    MyArrayQualClass_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Uint32ArrayQual_qual_value
};

static MI_CONST MI_Sint32 MyArrayQualClass_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MyArrayQualClass_Sint32ArrayQual_qual_value =
{
    MyArrayQualClass_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Sint32ArrayQual_qual_value
};

static MI_CONST MI_Uint64 MyArrayQualClass_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyArrayQualClass_Uint64ArrayQual_qual_value =
{
    MyArrayQualClass_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Uint64ArrayQual_qual_value
};

static MI_CONST MI_Sint64 MyArrayQualClass_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyArrayQualClass_Sint64ArrayQual_qual_value =
{
    MyArrayQualClass_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Sint64ArrayQual_qual_value
};

static MI_CONST MI_Real32 MyArrayQualClass_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MyArrayQualClass_Real32ArrayQual_qual_value =
{
    MyArrayQualClass_Real32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Real32ArrayQual_qual_value
};

static MI_CONST MI_Real64 MyArrayQualClass_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MyArrayQualClass_Real64ArrayQual_qual_value =
{
    MyArrayQualClass_Real64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_Real64ArrayQual_qual_value
};

static MI_CONST MI_Datetime MyArrayQualClass_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2011,3,14,22,24,12,0,8}}},
    {1,{{2012,3,15,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayQualClass_DatetimeArrayQual_qual_value =
{
    MyArrayQualClass_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MyArrayQualClass_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayQualClass_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayQualClass_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayQualClass_quals[] =
{
    &MyArrayQualClass_BooleanArrayQual_qual,
    &MyArrayQualClass_StringArrayQual_qual,
    &MyArrayQualClass_Char16ArrayQual_qual,
    &MyArrayQualClass_Uint8ArrayQual_qual,
    &MyArrayQualClass_Sint8ArrayQual_qual,
    &MyArrayQualClass_Uint16ArrayQual_qual,
    &MyArrayQualClass_Sint16ArrayQual_qual,
    &MyArrayQualClass_Uint32ArrayQual_qual,
    &MyArrayQualClass_Sint32ArrayQual_qual,
    &MyArrayQualClass_Uint64ArrayQual_qual,
    &MyArrayQualClass_Sint64ArrayQual_qual,
    &MyArrayQualClass_Real32ArrayQual_qual,
    &MyArrayQualClass_Real64ArrayQual_qual,
    &MyArrayQualClass_DatetimeArrayQual_qual,
};

/* class MyArrayQualClass */
MI_CONST MI_ClassDecl MyArrayQualClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7310, /* code */
    MI_T("MyArrayQualClass"), /* name */
    MyArrayQualClass_quals, /* qualifiers */
    MI_COUNT(MyArrayQualClass_quals), /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyArrayQualClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayQualClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimplePropertiesClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MySimplePropertiesClass_booleanProp_value = 1;

/* property MySimplePropertiesClass.booleanProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_booleanProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062700B, /* code */
    MI_T("booleanProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, booleanProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_booleanProp_value,
};

static MI_CONST MI_Char* MySimplePropertiesClass_stringProp_value = MI_T("hello&'><\"\\/");

/* property MySimplePropertiesClass.stringProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_stringProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("stringProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, stringProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_stringProp_value,
};

static MI_CONST MI_Char16 MySimplePropertiesClass_char16Prop_value = 16;

/* property MySimplePropertiesClass.char16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_char16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700A, /* code */
    MI_T("char16Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, char16Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_char16Prop_value,
};

static MI_CONST MI_Uint8 MySimplePropertiesClass_uint8Prop_value = 1;

/* property MySimplePropertiesClass.uint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_uint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757009, /* code */
    MI_T("uint8Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, uint8Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_uint8Prop_value,
};

static MI_CONST MI_Sint8 MySimplePropertiesClass_sint8Prop_value = -1;

/* property MySimplePropertiesClass.sint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_sint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737009, /* code */
    MI_T("sint8Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, sint8Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_sint8Prop_value,
};

static MI_CONST MI_Uint16 MySimplePropertiesClass_uint16Prop_value = 2;

/* property MySimplePropertiesClass.uint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_uint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint16Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, uint16Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_uint16Prop_value,
};

static MI_CONST MI_Sint16 MySimplePropertiesClass_sint16Prop_value = -2;

/* property MySimplePropertiesClass.sint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_sint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint16Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, sint16Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_sint16Prop_value,
};

static MI_CONST MI_Uint32 MySimplePropertiesClass_uint32Prop_value = 3U;

/* property MySimplePropertiesClass.uint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_uint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint32Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, uint32Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_uint32Prop_value,
};

static MI_CONST MI_Sint32 MySimplePropertiesClass_sint32Prop_value = -3;

/* property MySimplePropertiesClass.sint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_sint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint32Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, sint32Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_sint32Prop_value,
};

static MI_CONST MI_Uint64 MySimplePropertiesClass_uint64Prop_value = MI_ULL(4);

/* property MySimplePropertiesClass.uint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_uint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint64Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, uint64Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_uint64Prop_value,
};

static MI_CONST MI_Sint64 MySimplePropertiesClass_sint64Prop_value = -MI_LL(4);

/* property MySimplePropertiesClass.sint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_sint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint64Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, sint64Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_sint64Prop_value,
};

static MI_CONST MI_Real32 MySimplePropertiesClass_real32Prop_value = (float)1.1;

/* property MySimplePropertiesClass.real32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_real32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real32Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, real32Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_real32Prop_value,
};

static MI_CONST MI_Real64 MySimplePropertiesClass_real64Prop_value = (double)-2.2;

/* property MySimplePropertiesClass.real64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_real64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real64Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, real64Prop), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_real64Prop_value,
};

static MI_CONST MI_Datetime MySimplePropertiesClass_datetimeProp_value = {1,{{2011,3,14,22,24,12,0,8}}};

/* property MySimplePropertiesClass.datetimeProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesClass_datetimeProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064700C, /* code */
    MI_T("datetimeProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesClass, datetimeProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesClass"), /* propagator */
    &MySimplePropertiesClass_datetimeProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySimplePropertiesClass_props[] =
{
    &MySimplePropertiesClass_booleanProp_prop,
    &MySimplePropertiesClass_stringProp_prop,
    &MySimplePropertiesClass_char16Prop_prop,
    &MySimplePropertiesClass_uint8Prop_prop,
    &MySimplePropertiesClass_sint8Prop_prop,
    &MySimplePropertiesClass_uint16Prop_prop,
    &MySimplePropertiesClass_sint16Prop_prop,
    &MySimplePropertiesClass_uint32Prop_prop,
    &MySimplePropertiesClass_sint32Prop_prop,
    &MySimplePropertiesClass_uint64Prop_prop,
    &MySimplePropertiesClass_sint64Prop_prop,
    &MySimplePropertiesClass_real32Prop_prop,
    &MySimplePropertiesClass_real64Prop_prop,
    &MySimplePropertiesClass_datetimeProp_prop,
};

static MI_CONST MI_ProviderFT MySimplePropertiesClass_funcs =
{
  (MI_ProviderFT_Load)MySimplePropertiesClass_Load,
  (MI_ProviderFT_Unload)MySimplePropertiesClass_Unload,
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

/* class MySimplePropertiesClass */
MI_CONST MI_ClassDecl MySimplePropertiesClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7317, /* code */
    MI_T("MySimplePropertiesClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimplePropertiesClass_props, /* properties */
    MI_COUNT(MySimplePropertiesClass_props), /* numProperties */
    sizeof(MySimplePropertiesClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MySimplePropertiesClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyEmbeddedPropertiesClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MyEmbeddedPropertiesClass_v_embeddedObject_EmbeddedObject_qual_value = 1;

static MI_CONST MI_Qualifier MyEmbeddedPropertiesClass_v_embeddedObject_EmbeddedObject_qual =
{
    MI_T("EmbeddedObject"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyEmbeddedPropertiesClass_v_embeddedObject_EmbeddedObject_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyEmbeddedPropertiesClass_v_embeddedObject_quals[] =
{
    &MyEmbeddedPropertiesClass_v_embeddedObject_EmbeddedObject_qual,
};

/* property MyEmbeddedPropertiesClass.v_embeddedObject */
static MI_CONST MI_PropertyDecl MyEmbeddedPropertiesClass_v_embeddedObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00767410, /* code */
    MI_T("v_embeddedObject"), /* name */
    MyEmbeddedPropertiesClass_v_embeddedObject_quals, /* qualifiers */
    MI_COUNT(MyEmbeddedPropertiesClass_v_embeddedObject_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyEmbeddedPropertiesClass, v_embeddedObject), /* offset */
    MI_T("MyEmbeddedPropertiesClass"), /* origin */
    MI_T("MyEmbeddedPropertiesClass"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MyEmbeddedPropertiesClass_v_embeddedInstance_EmbeddedInstance_qual_value = MI_T("MySimplePropertiesClass");

static MI_CONST MI_Qualifier MyEmbeddedPropertiesClass_v_embeddedInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &MyEmbeddedPropertiesClass_v_embeddedInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyEmbeddedPropertiesClass_v_embeddedInstance_quals[] =
{
    &MyEmbeddedPropertiesClass_v_embeddedInstance_EmbeddedInstance_qual,
};

/* property MyEmbeddedPropertiesClass.v_embeddedInstance */
static MI_CONST MI_PropertyDecl MyEmbeddedPropertiesClass_v_embeddedInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766512, /* code */
    MI_T("v_embeddedInstance"), /* name */
    MyEmbeddedPropertiesClass_v_embeddedInstance_quals, /* qualifiers */
    MI_COUNT(MyEmbeddedPropertiesClass_v_embeddedInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MySimplePropertiesClass"), /* className */
    0, /* subscript */
    offsetof(MyEmbeddedPropertiesClass, v_embeddedInstance), /* offset */
    MI_T("MyEmbeddedPropertiesClass"), /* origin */
    MI_T("MyEmbeddedPropertiesClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyEmbeddedPropertiesClass_props[] =
{
    &MyEmbeddedPropertiesClass_v_embeddedObject_prop,
    &MyEmbeddedPropertiesClass_v_embeddedInstance_prop,
};

static MI_CONST MI_ProviderFT MyEmbeddedPropertiesClass_funcs =
{
  (MI_ProviderFT_Load)MyEmbeddedPropertiesClass_Load,
  (MI_ProviderFT_Unload)MyEmbeddedPropertiesClass_Unload,
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

/* class MyEmbeddedPropertiesClass */
MI_CONST MI_ClassDecl MyEmbeddedPropertiesClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7319, /* code */
    MI_T("MyEmbeddedPropertiesClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyEmbeddedPropertiesClass_props, /* properties */
    MI_COUNT(MyEmbeddedPropertiesClass_props), /* numProperties */
    sizeof(MyEmbeddedPropertiesClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyEmbeddedPropertiesClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimplePropertiesDerivedClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MySimplePropertiesDerivedClass_booleanProp_value = 0;

/* property MySimplePropertiesDerivedClass.booleanProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesDerivedClass_booleanProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062700B, /* code */
    MI_T("booleanProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesDerivedClass, booleanProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesDerivedClass"), /* propagator */
    &MySimplePropertiesDerivedClass_booleanProp_value,
};

static MI_CONST MI_Char* MySimplePropertiesDerivedClass_stringProp_value = MI_T("goodbye&'><\"\\/");

/* property MySimplePropertiesDerivedClass.stringProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesDerivedClass_stringProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("stringProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesDerivedClass, stringProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesDerivedClass"), /* propagator */
    &MySimplePropertiesDerivedClass_stringProp_value,
};

static MI_CONST MI_Datetime MySimplePropertiesDerivedClass_datetimeProp_value = {1,{{2012,11,30,22,24,12,0,8}}};

/* property MySimplePropertiesDerivedClass.datetimeProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesDerivedClass_datetimeProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064700C, /* code */
    MI_T("datetimeProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesDerivedClass, datetimeProp), /* offset */
    MI_T("MySimplePropertiesClass"), /* origin */
    MI_T("MySimplePropertiesDerivedClass"), /* propagator */
    &MySimplePropertiesDerivedClass_datetimeProp_value,
};

static MI_CONST MI_Boolean MySimplePropertiesDerivedClass_anotherBooleanProp_value = 0;

/* property MySimplePropertiesDerivedClass.anotherBooleanProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesDerivedClass_anotherBooleanProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617012, /* code */
    MI_T("anotherBooleanProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesDerivedClass, anotherBooleanProp), /* offset */
    MI_T("MySimplePropertiesDerivedClass"), /* origin */
    MI_T("MySimplePropertiesDerivedClass"), /* propagator */
    &MySimplePropertiesDerivedClass_anotherBooleanProp_value,
};

static MI_CONST MI_Char* MySimplePropertiesDerivedClass_anotherStringProp_value = MI_T("mystring&'");

/* property MySimplePropertiesDerivedClass.anotherStringProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesDerivedClass_anotherStringProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617011, /* code */
    MI_T("anotherStringProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesDerivedClass, anotherStringProp), /* offset */
    MI_T("MySimplePropertiesDerivedClass"), /* origin */
    MI_T("MySimplePropertiesDerivedClass"), /* propagator */
    &MySimplePropertiesDerivedClass_anotherStringProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySimplePropertiesDerivedClass_props[] =
{
    &MySimplePropertiesDerivedClass_booleanProp_prop,
    &MySimplePropertiesDerivedClass_stringProp_prop,
    &MySimplePropertiesClass_char16Prop_prop,
    &MySimplePropertiesClass_uint8Prop_prop,
    &MySimplePropertiesClass_sint8Prop_prop,
    &MySimplePropertiesClass_uint16Prop_prop,
    &MySimplePropertiesClass_sint16Prop_prop,
    &MySimplePropertiesClass_uint32Prop_prop,
    &MySimplePropertiesClass_sint32Prop_prop,
    &MySimplePropertiesClass_uint64Prop_prop,
    &MySimplePropertiesClass_sint64Prop_prop,
    &MySimplePropertiesClass_real32Prop_prop,
    &MySimplePropertiesClass_real64Prop_prop,
    &MySimplePropertiesDerivedClass_datetimeProp_prop,
    &MySimplePropertiesDerivedClass_anotherBooleanProp_prop,
    &MySimplePropertiesDerivedClass_anotherStringProp_prop,
};

static MI_CONST MI_ProviderFT MySimplePropertiesDerivedClass_funcs =
{
  (MI_ProviderFT_Load)MySimplePropertiesDerivedClass_Load,
  (MI_ProviderFT_Unload)MySimplePropertiesDerivedClass_Unload,
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

/* class MySimplePropertiesDerivedClass */
MI_CONST MI_ClassDecl MySimplePropertiesDerivedClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D731E, /* code */
    MI_T("MySimplePropertiesDerivedClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimplePropertiesDerivedClass_props, /* properties */
    MI_COUNT(MySimplePropertiesDerivedClass_props), /* numProperties */
    sizeof(MySimplePropertiesDerivedClass), /* size */
    MI_T("MySimplePropertiesClass"), /* superClass */
    &MySimplePropertiesClass_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MySimplePropertiesDerivedClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyFooClass
**
**==============================================================================
*/

static MI_CONST MI_Sint64 MyFooClass_sint64Prop_value = -MI_LL(4);

/* property MyFooClass.sint64Prop */
static MI_CONST MI_PropertyDecl MyFooClass_sint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint64Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyFooClass, sint64Prop), /* offset */
    MI_T("MyFooClass"), /* origin */
    MI_T("MyFooClass"), /* propagator */
    &MyFooClass_sint64Prop_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyFooClass_props[] =
{
    &MyFooClass_sint64Prop_prop,
};

static MI_CONST MI_ProviderFT MyFooClass_funcs =
{
  (MI_ProviderFT_Load)MyFooClass_Load,
  (MI_ProviderFT_Unload)MyFooClass_Unload,
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

/* class MyFooClass */
MI_CONST MI_ClassDecl MyFooClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D730A, /* code */
    MI_T("MyFooClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyFooClass_props, /* properties */
    MI_COUNT(MyFooClass_props), /* numProperties */
    sizeof(MyFooClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyFooClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimplePropertiesSimpleQualsClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MySimplePropertiesSimpleQualsClass_booleanProp_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_booleanProp_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_booleanProp_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_booleanProp_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_booleanProp_BooleanQual_qual,
};

static MI_CONST MI_Boolean MySimplePropertiesSimpleQualsClass_booleanProp_value = 0;

/* property MySimplePropertiesSimpleQualsClass.booleanProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_booleanProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062700B, /* code */
    MI_T("booleanProp"), /* name */
    MySimplePropertiesSimpleQualsClass_booleanProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_booleanProp_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, booleanProp), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_booleanProp_value,
};

static MI_CONST MI_Char* MySimplePropertiesSimpleQualsClass_stringProp_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_stringProp_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_stringProp_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_stringProp_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_stringProp_StringQual_qual,
};

static MI_CONST MI_Char* MySimplePropertiesSimpleQualsClass_stringProp_value = MI_T("hello&'><\"\\/");

/* property MySimplePropertiesSimpleQualsClass.stringProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_stringProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("stringProp"), /* name */
    MySimplePropertiesSimpleQualsClass_stringProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_stringProp_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, stringProp), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_stringProp_value,
};

static MI_CONST MI_Char16 MySimplePropertiesSimpleQualsClass_char16Prop_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_char16Prop_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_char16Prop_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_char16Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_char16Prop_Char16Qual_qual,
};

static MI_CONST MI_Char16 MySimplePropertiesSimpleQualsClass_char16Prop_value = 16;

/* property MySimplePropertiesSimpleQualsClass.char16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_char16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700A, /* code */
    MI_T("char16Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_char16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_char16Prop_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, char16Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_char16Prop_value,
};

static MI_CONST MI_Uint8 MySimplePropertiesSimpleQualsClass_uint8Prop_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_uint8Prop_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_uint8Prop_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_uint8Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_uint8Prop_Uint8Qual_qual,
};

static MI_CONST MI_Uint8 MySimplePropertiesSimpleQualsClass_uint8Prop_value = 1;

/* property MySimplePropertiesSimpleQualsClass.uint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_uint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757009, /* code */
    MI_T("uint8Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_uint8Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_uint8Prop_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, uint8Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_uint8Prop_value,
};

static MI_CONST MI_Sint8 MySimplePropertiesSimpleQualsClass_sint8Prop_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_sint8Prop_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_sint8Prop_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_sint8Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_sint8Prop_Sint8Qual_qual,
};

static MI_CONST MI_Sint8 MySimplePropertiesSimpleQualsClass_sint8Prop_value = -1;

/* property MySimplePropertiesSimpleQualsClass.sint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_sint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737009, /* code */
    MI_T("sint8Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_sint8Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_sint8Prop_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, sint8Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_sint8Prop_value,
};

static MI_CONST MI_Uint16 MySimplePropertiesSimpleQualsClass_uint16Prop_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_uint16Prop_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_uint16Prop_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_uint16Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_uint16Prop_Uint16Qual_qual,
};

static MI_CONST MI_Uint16 MySimplePropertiesSimpleQualsClass_uint16Prop_value = 2;

/* property MySimplePropertiesSimpleQualsClass.uint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_uint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint16Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_uint16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_uint16Prop_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, uint16Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_uint16Prop_value,
};

static MI_CONST MI_Sint16 MySimplePropertiesSimpleQualsClass_sint16Prop_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_sint16Prop_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_sint16Prop_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_sint16Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_sint16Prop_Sint16Qual_qual,
};

static MI_CONST MI_Sint16 MySimplePropertiesSimpleQualsClass_sint16Prop_value = -2;

/* property MySimplePropertiesSimpleQualsClass.sint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_sint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint16Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_sint16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_sint16Prop_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, sint16Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_sint16Prop_value,
};

static MI_CONST MI_Uint32 MySimplePropertiesSimpleQualsClass_uint32Prop_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_uint32Prop_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_uint32Prop_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_uint32Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_uint32Prop_Uint32Qual_qual,
};

static MI_CONST MI_Uint32 MySimplePropertiesSimpleQualsClass_uint32Prop_value = 3U;

/* property MySimplePropertiesSimpleQualsClass.uint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_uint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint32Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_uint32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_uint32Prop_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, uint32Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_uint32Prop_value,
};

static MI_CONST MI_Sint32 MySimplePropertiesSimpleQualsClass_sint32Prop_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_sint32Prop_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_sint32Prop_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_sint32Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_sint32Prop_Sint32Qual_qual,
};

static MI_CONST MI_Sint32 MySimplePropertiesSimpleQualsClass_sint32Prop_value = -3;

/* property MySimplePropertiesSimpleQualsClass.sint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_sint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint32Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_sint32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_sint32Prop_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, sint32Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_sint32Prop_value,
};

static MI_CONST MI_Uint64 MySimplePropertiesSimpleQualsClass_uint64Prop_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_uint64Prop_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_uint64Prop_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_uint64Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_uint64Prop_Uint64Qual_qual,
};

static MI_CONST MI_Uint64 MySimplePropertiesSimpleQualsClass_uint64Prop_value = MI_ULL(4);

/* property MySimplePropertiesSimpleQualsClass.uint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_uint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint64Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_uint64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_uint64Prop_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, uint64Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_uint64Prop_value,
};

static MI_CONST MI_Sint64 MySimplePropertiesSimpleQualsClass_sint64Prop_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_sint64Prop_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_sint64Prop_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_sint64Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_sint64Prop_Sint64Qual_qual,
};

static MI_CONST MI_Sint64 MySimplePropertiesSimpleQualsClass_sint64Prop_value = -MI_LL(4);

/* property MySimplePropertiesSimpleQualsClass.sint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_sint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint64Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_sint64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_sint64Prop_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, sint64Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_sint64Prop_value,
};

static MI_CONST MI_Real32 MySimplePropertiesSimpleQualsClass_real32Prop_Real32Qual_qual_value = (float)1.1;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_real32Prop_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_real32Prop_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_real32Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_real32Prop_Real32Qual_qual,
};

static MI_CONST MI_Real32 MySimplePropertiesSimpleQualsClass_real32Prop_value = (float)1.1;

/* property MySimplePropertiesSimpleQualsClass.real32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_real32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real32Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_real32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_real32Prop_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, real32Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_real32Prop_value,
};

static MI_CONST MI_Real64 MySimplePropertiesSimpleQualsClass_real64Prop_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_real64Prop_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_real64Prop_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_real64Prop_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_real64Prop_Real64Qual_qual,
};

static MI_CONST MI_Real64 MySimplePropertiesSimpleQualsClass_real64Prop_value = (double)-2.2;

/* property MySimplePropertiesSimpleQualsClass.real64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_real64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real64Prop"), /* name */
    MySimplePropertiesSimpleQualsClass_real64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_real64Prop_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, real64Prop), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_real64Prop_value,
};

static MI_CONST MI_Datetime MySimplePropertiesSimpleQualsClass_datetimeProp_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MySimplePropertiesSimpleQualsClass_datetimeProp_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesSimpleQualsClass_datetimeProp_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_datetimeProp_quals[] =
{
    &MySimplePropertiesSimpleQualsClass_datetimeProp_DatetimeQual_qual,
};

static MI_CONST MI_Datetime MySimplePropertiesSimpleQualsClass_datetimeProp_value = {1,{{2011,3,14,22,24,12,0,8}}};

/* property MySimplePropertiesSimpleQualsClass.datetimeProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesSimpleQualsClass_datetimeProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064700C, /* code */
    MI_T("datetimeProp"), /* name */
    MySimplePropertiesSimpleQualsClass_datetimeProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_datetimeProp_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesSimpleQualsClass, datetimeProp), /* offset */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* origin */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* propagator */
    &MySimplePropertiesSimpleQualsClass_datetimeProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySimplePropertiesSimpleQualsClass_props[] =
{
    &MySimplePropertiesSimpleQualsClass_booleanProp_prop,
    &MySimplePropertiesSimpleQualsClass_stringProp_prop,
    &MySimplePropertiesSimpleQualsClass_char16Prop_prop,
    &MySimplePropertiesSimpleQualsClass_uint8Prop_prop,
    &MySimplePropertiesSimpleQualsClass_sint8Prop_prop,
    &MySimplePropertiesSimpleQualsClass_uint16Prop_prop,
    &MySimplePropertiesSimpleQualsClass_sint16Prop_prop,
    &MySimplePropertiesSimpleQualsClass_uint32Prop_prop,
    &MySimplePropertiesSimpleQualsClass_sint32Prop_prop,
    &MySimplePropertiesSimpleQualsClass_uint64Prop_prop,
    &MySimplePropertiesSimpleQualsClass_sint64Prop_prop,
    &MySimplePropertiesSimpleQualsClass_real32Prop_prop,
    &MySimplePropertiesSimpleQualsClass_real64Prop_prop,
    &MySimplePropertiesSimpleQualsClass_datetimeProp_prop,
};

static MI_CONST MI_ProviderFT MySimplePropertiesSimpleQualsClass_funcs =
{
  (MI_ProviderFT_Load)MySimplePropertiesSimpleQualsClass_Load,
  (MI_ProviderFT_Unload)MySimplePropertiesSimpleQualsClass_Unload,
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

/* class MySimplePropertiesSimpleQualsClass */
MI_CONST MI_ClassDecl MySimplePropertiesSimpleQualsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7322, /* code */
    MI_T("MySimplePropertiesSimpleQualsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimplePropertiesSimpleQualsClass_props, /* properties */
    MI_COUNT(MySimplePropertiesSimpleQualsClass_props), /* numProperties */
    sizeof(MySimplePropertiesSimpleQualsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MySimplePropertiesSimpleQualsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimplePropertiesArrayQualsClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_booleanProp_quals[] =
{
    &MySimplePropertiesArrayQualsClass_booleanProp_BooleanArrayQual_qual,
};

static MI_CONST MI_Boolean MySimplePropertiesArrayQualsClass_booleanProp_value = 1;

/* property MySimplePropertiesArrayQualsClass.booleanProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_booleanProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062700B, /* code */
    MI_T("booleanProp"), /* name */
    MySimplePropertiesArrayQualsClass_booleanProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_booleanProp_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, booleanProp), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_booleanProp_value,
};

static MI_CONST MI_Char* MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("goodbye"),
};

static MI_CONST MI_ConstStringA MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_stringProp_quals[] =
{
    &MySimplePropertiesArrayQualsClass_stringProp_StringArrayQual_qual,
};

static MI_CONST MI_Char* MySimplePropertiesArrayQualsClass_stringProp_value = MI_T("hello&'><\"\\/");

/* property MySimplePropertiesArrayQualsClass.stringProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_stringProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("stringProp"), /* name */
    MySimplePropertiesArrayQualsClass_stringProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_stringProp_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, stringProp), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_stringProp_value,
};

static MI_CONST MI_Char16 MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_char16Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_char16Prop_Char16ArrayQual_qual,
};

static MI_CONST MI_Char16 MySimplePropertiesArrayQualsClass_char16Prop_value = 16;

/* property MySimplePropertiesArrayQualsClass.char16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_char16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700A, /* code */
    MI_T("char16Prop"), /* name */
    MySimplePropertiesArrayQualsClass_char16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_char16Prop_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, char16Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_char16Prop_value,
};

static MI_CONST MI_Uint8 MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_uint8Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_uint8Prop_Uint8ArrayQual_qual,
};

static MI_CONST MI_Uint8 MySimplePropertiesArrayQualsClass_uint8Prop_value = 1;

/* property MySimplePropertiesArrayQualsClass.uint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_uint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757009, /* code */
    MI_T("uint8Prop"), /* name */
    MySimplePropertiesArrayQualsClass_uint8Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint8Prop_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, uint8Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_uint8Prop_value,
};

static MI_CONST MI_Sint8 MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_sint8Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_sint8Prop_Sint8ArrayQual_qual,
};

static MI_CONST MI_Sint8 MySimplePropertiesArrayQualsClass_sint8Prop_value = -1;

/* property MySimplePropertiesArrayQualsClass.sint8Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_sint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737009, /* code */
    MI_T("sint8Prop"), /* name */
    MySimplePropertiesArrayQualsClass_sint8Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint8Prop_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, sint8Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_sint8Prop_value,
};

static MI_CONST MI_Uint16 MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_uint16Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_uint16Prop_Uint16ArrayQual_qual,
};

static MI_CONST MI_Uint16 MySimplePropertiesArrayQualsClass_uint16Prop_value = 2;

/* property MySimplePropertiesArrayQualsClass.uint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_uint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint16Prop"), /* name */
    MySimplePropertiesArrayQualsClass_uint16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint16Prop_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, uint16Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_uint16Prop_value,
};

static MI_CONST MI_Sint16 MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_sint16Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_sint16Prop_Sint16ArrayQual_qual,
};

static MI_CONST MI_Sint16 MySimplePropertiesArrayQualsClass_sint16Prop_value = -2;

/* property MySimplePropertiesArrayQualsClass.sint16Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_sint16Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint16Prop"), /* name */
    MySimplePropertiesArrayQualsClass_sint16Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint16Prop_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, sint16Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_sint16Prop_value,
};

static MI_CONST MI_Uint32 MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_uint32Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_uint32Prop_Uint32ArrayQual_qual,
};

static MI_CONST MI_Uint32 MySimplePropertiesArrayQualsClass_uint32Prop_value = 3U;

/* property MySimplePropertiesArrayQualsClass.uint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_uint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint32Prop"), /* name */
    MySimplePropertiesArrayQualsClass_uint32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint32Prop_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, uint32Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_uint32Prop_value,
};

static MI_CONST MI_Sint32 MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_sint32Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_sint32Prop_Sint32ArrayQual_qual,
};

static MI_CONST MI_Sint32 MySimplePropertiesArrayQualsClass_sint32Prop_value = -3;

/* property MySimplePropertiesArrayQualsClass.sint32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_sint32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint32Prop"), /* name */
    MySimplePropertiesArrayQualsClass_sint32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint32Prop_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, sint32Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_sint32Prop_value,
};

static MI_CONST MI_Uint64 MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_uint64Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_uint64Prop_Uint64ArrayQual_qual,
};

static MI_CONST MI_Uint64 MySimplePropertiesArrayQualsClass_uint64Prop_value = MI_ULL(4);

/* property MySimplePropertiesArrayQualsClass.uint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_uint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700A, /* code */
    MI_T("uint64Prop"), /* name */
    MySimplePropertiesArrayQualsClass_uint64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_uint64Prop_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, uint64Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_uint64Prop_value,
};

static MI_CONST MI_Sint64 MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_sint64Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_sint64Prop_Sint64ArrayQual_qual,
};

static MI_CONST MI_Sint64 MySimplePropertiesArrayQualsClass_sint64Prop_value = -MI_LL(4);

/* property MySimplePropertiesArrayQualsClass.sint64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_sint64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700A, /* code */
    MI_T("sint64Prop"), /* name */
    MySimplePropertiesArrayQualsClass_sint64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_sint64Prop_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, sint64Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_sint64Prop_value,
};

static MI_CONST MI_Real32 MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_real32Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_real32Prop_Real32ArrayQual_qual,
};

static MI_CONST MI_Real32 MySimplePropertiesArrayQualsClass_real32Prop_value = (float)1.1;

/* property MySimplePropertiesArrayQualsClass.real32Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_real32Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real32Prop"), /* name */
    MySimplePropertiesArrayQualsClass_real32Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_real32Prop_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, real32Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_real32Prop_value,
};

static MI_CONST MI_Real64 MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_real64Prop_quals[] =
{
    &MySimplePropertiesArrayQualsClass_real64Prop_Real64ArrayQual_qual,
};

static MI_CONST MI_Real64 MySimplePropertiesArrayQualsClass_real64Prop_value = (double)-2.2;

/* property MySimplePropertiesArrayQualsClass.real64Prop */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_real64Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700A, /* code */
    MI_T("real64Prop"), /* name */
    MySimplePropertiesArrayQualsClass_real64Prop_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_real64Prop_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, real64Prop), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_real64Prop_value,
};

static MI_CONST MI_Datetime MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual_value =
{
    MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_datetimeProp_quals[] =
{
    &MySimplePropertiesArrayQualsClass_datetimeProp_DatetimeArrayQual_qual,
};

static MI_CONST MI_Datetime MySimplePropertiesArrayQualsClass_datetimeProp_value = {1,{{2011,1,1,22,24,12,0,8}}};

/* property MySimplePropertiesArrayQualsClass.datetimeProp */
static MI_CONST MI_PropertyDecl MySimplePropertiesArrayQualsClass_datetimeProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064700C, /* code */
    MI_T("datetimeProp"), /* name */
    MySimplePropertiesArrayQualsClass_datetimeProp_quals, /* qualifiers */
    MI_COUNT(MySimplePropertiesArrayQualsClass_datetimeProp_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimplePropertiesArrayQualsClass, datetimeProp), /* offset */
    MI_T("MySimplePropertiesArrayQualsClass"), /* origin */
    MI_T("MySimplePropertiesArrayQualsClass"), /* propagator */
    &MySimplePropertiesArrayQualsClass_datetimeProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySimplePropertiesArrayQualsClass_props[] =
{
    &MySimplePropertiesArrayQualsClass_booleanProp_prop,
    &MySimplePropertiesArrayQualsClass_stringProp_prop,
    &MySimplePropertiesArrayQualsClass_char16Prop_prop,
    &MySimplePropertiesArrayQualsClass_uint8Prop_prop,
    &MySimplePropertiesArrayQualsClass_sint8Prop_prop,
    &MySimplePropertiesArrayQualsClass_uint16Prop_prop,
    &MySimplePropertiesArrayQualsClass_sint16Prop_prop,
    &MySimplePropertiesArrayQualsClass_uint32Prop_prop,
    &MySimplePropertiesArrayQualsClass_sint32Prop_prop,
    &MySimplePropertiesArrayQualsClass_uint64Prop_prop,
    &MySimplePropertiesArrayQualsClass_sint64Prop_prop,
    &MySimplePropertiesArrayQualsClass_real32Prop_prop,
    &MySimplePropertiesArrayQualsClass_real64Prop_prop,
    &MySimplePropertiesArrayQualsClass_datetimeProp_prop,
};

static MI_CONST MI_ProviderFT MySimplePropertiesArrayQualsClass_funcs =
{
  (MI_ProviderFT_Load)MySimplePropertiesArrayQualsClass_Load,
  (MI_ProviderFT_Unload)MySimplePropertiesArrayQualsClass_Unload,
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

/* class MySimplePropertiesArrayQualsClass */
MI_CONST MI_ClassDecl MySimplePropertiesArrayQualsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7321, /* code */
    MI_T("MySimplePropertiesArrayQualsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimplePropertiesArrayQualsClass_props, /* properties */
    MI_COUNT(MySimplePropertiesArrayQualsClass_props), /* numProperties */
    sizeof(MySimplePropertiesArrayQualsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MySimplePropertiesArrayQualsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayPropertiesClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MyArrayPropertiesClass_booleanArrayProp_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA MyArrayPropertiesClass_booleanArrayProp_value =
{
    MyArrayPropertiesClass_booleanArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_booleanArrayProp_data_value),
};

/* property MyArrayPropertiesClass.booleanArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_booleanArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627010, /* code */
    MI_T("booleanArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, booleanArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_booleanArrayProp_value,
};

static MI_CONST MI_Char* MyArrayPropertiesClass_stringArrayProp_data_value[] =
{
    MI_T("hello&'><\"\\/"),
    MI_T("&'><\"\\/"),
};

static MI_CONST MI_ConstStringA MyArrayPropertiesClass_stringArrayProp_value =
{
    MyArrayPropertiesClass_stringArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_stringArrayProp_data_value),
};

/* property MyArrayPropertiesClass.stringArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_stringArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("stringArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, stringArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_stringArrayProp_value,
};

static MI_CONST MI_Char16 MyArrayPropertiesClass_char16ArrayProp_data_value[] =
{
    16,
    8,
};

static MI_CONST MI_ConstChar16A MyArrayPropertiesClass_char16ArrayProp_value =
{
    MyArrayPropertiesClass_char16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_char16ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.char16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_char16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700F, /* code */
    MI_T("char16ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, char16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_char16ArrayProp_value,
};

static MI_CONST MI_Uint8 MyArrayPropertiesClass_uint8ArrayProp_data_value[] =
{
    1,
    12,
};

static MI_CONST MI_ConstUint8A MyArrayPropertiesClass_uint8ArrayProp_value =
{
    MyArrayPropertiesClass_uint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_uint8ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.uint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_uint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700E, /* code */
    MI_T("uint8ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, uint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_uint8ArrayProp_value,
};

static MI_CONST MI_Sint8 MyArrayPropertiesClass_sint8ArrayProp_data_value[] =
{
    -1,
    -99,
};

static MI_CONST MI_ConstSint8A MyArrayPropertiesClass_sint8ArrayProp_value =
{
    MyArrayPropertiesClass_sint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_sint8ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.sint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_sint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700E, /* code */
    MI_T("sint8ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, sint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_sint8ArrayProp_value,
};

static MI_CONST MI_Uint16 MyArrayPropertiesClass_uint16ArrayProp_data_value[] =
{
    2,
    22,
};

static MI_CONST MI_ConstUint16A MyArrayPropertiesClass_uint16ArrayProp_value =
{
    MyArrayPropertiesClass_uint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_uint16ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.uint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_uint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint16ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, uint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_uint16ArrayProp_value,
};

static MI_CONST MI_Sint16 MyArrayPropertiesClass_sint16ArrayProp_data_value[] =
{
    2,
    -100,
};

static MI_CONST MI_ConstSint16A MyArrayPropertiesClass_sint16ArrayProp_value =
{
    MyArrayPropertiesClass_sint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_sint16ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.sint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_sint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint16ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, sint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_sint16ArrayProp_value,
};

static MI_CONST MI_Uint32 MyArrayPropertiesClass_uint32ArrayProp_data_value[] =
{
    3U,
    333U,
};

static MI_CONST MI_ConstUint32A MyArrayPropertiesClass_uint32ArrayProp_value =
{
    MyArrayPropertiesClass_uint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_uint32ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.uint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_uint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint32ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, uint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_uint32ArrayProp_value,
};

static MI_CONST MI_Sint32 MyArrayPropertiesClass_sint32ArrayProp_data_value[] =
{
    3,
    -32335,
};

static MI_CONST MI_ConstSint32A MyArrayPropertiesClass_sint32ArrayProp_value =
{
    MyArrayPropertiesClass_sint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_sint32ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.sint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_sint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint32ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, sint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_sint32ArrayProp_value,
};

static MI_CONST MI_Uint64 MyArrayPropertiesClass_uint64ArrayProp_data_value[] =
{
    MI_ULL(4),
    MI_ULL(123456789),
};

static MI_CONST MI_ConstUint64A MyArrayPropertiesClass_uint64ArrayProp_value =
{
    MyArrayPropertiesClass_uint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_uint64ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.uint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_uint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint64ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, uint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_uint64ArrayProp_value,
};

static MI_CONST MI_Sint64 MyArrayPropertiesClass_sint64ArrayProp_data_value[] =
{
    -MI_LL(456789123),
    MI_LL(789123456),
};

static MI_CONST MI_ConstSint64A MyArrayPropertiesClass_sint64ArrayProp_value =
{
    MyArrayPropertiesClass_sint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_sint64ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.sint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_sint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint64ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, sint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_sint64ArrayProp_value,
};

static MI_CONST MI_Real32 MyArrayPropertiesClass_real32ArrayProp_data_value[] =
{
    (float)1.1,
    (float)-2.3,
};

static MI_CONST MI_ConstReal32A MyArrayPropertiesClass_real32ArrayProp_value =
{
    MyArrayPropertiesClass_real32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_real32ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.real32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_real32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real32ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, real32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_real32ArrayProp_value,
};

static MI_CONST MI_Real64 MyArrayPropertiesClass_real64ArrayProp_data_value[] =
{
    (double)-2.2,
    (double)3.4,
};

static MI_CONST MI_ConstReal64A MyArrayPropertiesClass_real64ArrayProp_value =
{
    MyArrayPropertiesClass_real64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_real64ArrayProp_data_value),
};

/* property MyArrayPropertiesClass.real64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_real64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real64ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, real64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_real64ArrayProp_value,
};

static MI_CONST MI_Datetime MyArrayPropertiesClass_datetimeArrayProp_data_value[] =
{
    {1,{{2011,3,14,22,24,12,0,8}}},
    {1,{{2013,10,14,23,44,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayPropertiesClass_datetimeArrayProp_value =
{
    MyArrayPropertiesClass_datetimeArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesClass_datetimeArrayProp_data_value),
};

/* property MyArrayPropertiesClass.datetimeArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesClass_datetimeArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647011, /* code */
    MI_T("datetimeArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesClass, datetimeArrayProp), /* offset */
    MI_T("MyArrayPropertiesClass"), /* origin */
    MI_T("MyArrayPropertiesClass"), /* propagator */
    &MyArrayPropertiesClass_datetimeArrayProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyArrayPropertiesClass_props[] =
{
    &MyArrayPropertiesClass_booleanArrayProp_prop,
    &MyArrayPropertiesClass_stringArrayProp_prop,
    &MyArrayPropertiesClass_char16ArrayProp_prop,
    &MyArrayPropertiesClass_uint8ArrayProp_prop,
    &MyArrayPropertiesClass_sint8ArrayProp_prop,
    &MyArrayPropertiesClass_uint16ArrayProp_prop,
    &MyArrayPropertiesClass_sint16ArrayProp_prop,
    &MyArrayPropertiesClass_uint32ArrayProp_prop,
    &MyArrayPropertiesClass_sint32ArrayProp_prop,
    &MyArrayPropertiesClass_uint64ArrayProp_prop,
    &MyArrayPropertiesClass_sint64ArrayProp_prop,
    &MyArrayPropertiesClass_real32ArrayProp_prop,
    &MyArrayPropertiesClass_real64ArrayProp_prop,
    &MyArrayPropertiesClass_datetimeArrayProp_prop,
};

static MI_CONST MI_ProviderFT MyArrayPropertiesClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayPropertiesClass_Load,
  (MI_ProviderFT_Unload)MyArrayPropertiesClass_Unload,
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

/* class MyArrayPropertiesClass */
MI_CONST MI_ClassDecl MyArrayPropertiesClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7316, /* code */
    MI_T("MyArrayPropertiesClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayPropertiesClass_props, /* properties */
    MI_COUNT(MyArrayPropertiesClass_props), /* numProperties */
    sizeof(MyArrayPropertiesClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayPropertiesClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayPropertiesSimpleQualsClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MyArrayPropertiesSimpleQualsClass_booleanArrayProp_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_booleanArrayProp_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_booleanArrayProp_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_booleanArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_booleanArrayProp_BooleanQual_qual,
};

static MI_CONST MI_Boolean MyArrayPropertiesSimpleQualsClass_booleanArrayProp_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA MyArrayPropertiesSimpleQualsClass_booleanArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_booleanArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_booleanArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.booleanArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_booleanArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627010, /* code */
    MI_T("booleanArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_booleanArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_booleanArrayProp_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, booleanArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_booleanArrayProp_value,
};

static MI_CONST MI_Char* MyArrayPropertiesSimpleQualsClass_stringArrayProp_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_stringArrayProp_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_stringArrayProp_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_stringArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_stringArrayProp_StringQual_qual,
};

static MI_CONST MI_Char* MyArrayPropertiesSimpleQualsClass_stringArrayProp_data_value[] =
{
    MI_T("hello&'><\"\\/"),
    MI_T("&'><\"\\/"),
};

static MI_CONST MI_ConstStringA MyArrayPropertiesSimpleQualsClass_stringArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_stringArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_stringArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.stringArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_stringArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("stringArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_stringArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_stringArrayProp_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, stringArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_stringArrayProp_value,
};

static MI_CONST MI_Char16 MyArrayPropertiesSimpleQualsClass_char16ArrayProp_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_char16ArrayProp_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_char16ArrayProp_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_char16ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_char16ArrayProp_Char16Qual_qual,
};

static MI_CONST MI_Char16 MyArrayPropertiesSimpleQualsClass_char16ArrayProp_data_value[] =
{
    16,
    8,
};

static MI_CONST MI_ConstChar16A MyArrayPropertiesSimpleQualsClass_char16ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_char16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_char16ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.char16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_char16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700F, /* code */
    MI_T("char16ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_char16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_char16ArrayProp_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, char16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_char16ArrayProp_value,
};

static MI_CONST MI_Uint8 MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_Uint8Qual_qual,
};

static MI_CONST MI_Uint8 MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_data_value[] =
{
    1,
    12,
};

static MI_CONST MI_ConstUint8A MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.uint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700E, /* code */
    MI_T("uint8ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, uint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_value,
};

static MI_CONST MI_Sint8 MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_Sint8Qual_qual,
};

static MI_CONST MI_Sint8 MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_data_value[] =
{
    -1,
    -99,
};

static MI_CONST MI_ConstSint8A MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.sint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700E, /* code */
    MI_T("sint8ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, sint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_value,
};

static MI_CONST MI_Uint16 MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_Uint16Qual_qual,
};

static MI_CONST MI_Uint16 MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_data_value[] =
{
    2,
    22,
};

static MI_CONST MI_ConstUint16A MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.uint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint16ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, uint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_value,
};

static MI_CONST MI_Sint16 MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_Sint16Qual_qual,
};

static MI_CONST MI_Sint16 MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_data_value[] =
{
    2,
    -100,
};

static MI_CONST MI_ConstSint16A MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.sint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint16ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, sint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_value,
};

static MI_CONST MI_Uint32 MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_Uint32Qual_qual,
};

static MI_CONST MI_Uint32 MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_data_value[] =
{
    3U,
    333U,
};

static MI_CONST MI_ConstUint32A MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.uint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint32ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, uint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_value,
};

static MI_CONST MI_Sint32 MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_Sint32Qual_qual,
};

static MI_CONST MI_Sint32 MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_data_value[] =
{
    3,
    -32335,
};

static MI_CONST MI_ConstSint32A MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.sint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint32ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, sint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_value,
};

static MI_CONST MI_Uint64 MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_Uint64Qual_qual,
};

static MI_CONST MI_Uint64 MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_data_value[] =
{
    MI_ULL(4),
    MI_ULL(123456789),
};

static MI_CONST MI_ConstUint64A MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.uint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint64ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, uint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_value,
};

static MI_CONST MI_Sint64 MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_Sint64Qual_qual,
};

static MI_CONST MI_Sint64 MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_data_value[] =
{
    -MI_LL(456789123),
    MI_LL(789123456),
};

static MI_CONST MI_ConstSint64A MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.sint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint64ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, sint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_value,
};

static MI_CONST MI_Real32 MyArrayPropertiesSimpleQualsClass_real32ArrayProp_Real32Qual_qual_value = (float)1.1;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_real32ArrayProp_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_real32ArrayProp_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_real32ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_real32ArrayProp_Real32Qual_qual,
};

static MI_CONST MI_Real32 MyArrayPropertiesSimpleQualsClass_real32ArrayProp_data_value[] =
{
    (float)1.1,
    (float)-2.3,
};

static MI_CONST MI_ConstReal32A MyArrayPropertiesSimpleQualsClass_real32ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_real32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_real32ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.real32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_real32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real32ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_real32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_real32ArrayProp_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, real32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_real32ArrayProp_value,
};

static MI_CONST MI_Real64 MyArrayPropertiesSimpleQualsClass_real64ArrayProp_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_real64ArrayProp_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_real64ArrayProp_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_real64ArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_real64ArrayProp_Real64Qual_qual,
};

static MI_CONST MI_Real64 MyArrayPropertiesSimpleQualsClass_real64ArrayProp_data_value[] =
{
    (double)-2.2,
    (double)3.4,
};

static MI_CONST MI_ConstReal64A MyArrayPropertiesSimpleQualsClass_real64ArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_real64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_real64ArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.real64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_real64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real64ArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_real64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_real64ArrayProp_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, real64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_real64ArrayProp_value,
};

static MI_CONST MI_Datetime MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_quals[] =
{
    &MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_DatetimeQual_qual,
};

static MI_CONST MI_Datetime MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_data_value[] =
{
    {1,{{2011,3,14,22,24,12,0,8}}},
    {1,{{2013,10,14,23,44,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_value =
{
    MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_data_value),
};

/* property MyArrayPropertiesSimpleQualsClass.datetimeArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647011, /* code */
    MI_T("datetimeArrayProp"), /* name */
    MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesSimpleQualsClass, datetimeArrayProp), /* offset */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* origin */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* propagator */
    &MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyArrayPropertiesSimpleQualsClass_props[] =
{
    &MyArrayPropertiesSimpleQualsClass_booleanArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_stringArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_char16ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_uint8ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_sint8ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_uint16ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_sint16ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_uint32ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_sint32ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_uint64ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_sint64ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_real32ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_real64ArrayProp_prop,
    &MyArrayPropertiesSimpleQualsClass_datetimeArrayProp_prop,
};

static MI_CONST MI_ProviderFT MyArrayPropertiesSimpleQualsClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayPropertiesSimpleQualsClass_Load,
  (MI_ProviderFT_Unload)MyArrayPropertiesSimpleQualsClass_Unload,
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

/* class MyArrayPropertiesSimpleQualsClass */
MI_CONST MI_ClassDecl MyArrayPropertiesSimpleQualsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7321, /* code */
    MI_T("MyArrayPropertiesSimpleQualsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayPropertiesSimpleQualsClass_props, /* properties */
    MI_COUNT(MyArrayPropertiesSimpleQualsClass_props), /* numProperties */
    sizeof(MyArrayPropertiesSimpleQualsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayPropertiesSimpleQualsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayPropertiesArrayQualsClass
**
**==============================================================================
*/

static MI_CONST MI_Boolean MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual_data_value[] =
{
    0,
    1,
};

static MI_CONST MI_ConstBooleanA MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_booleanArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_booleanArrayProp_BooleanArrayQual_qual,
};

static MI_CONST MI_Boolean MyArrayPropertiesArrayQualsClass_booleanArrayProp_data_value[] =
{
    1,
    0,
};

static MI_CONST MI_ConstBooleanA MyArrayPropertiesArrayQualsClass_booleanArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_booleanArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_booleanArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.booleanArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_booleanArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627010, /* code */
    MI_T("booleanArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_booleanArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_booleanArrayProp_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, booleanArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_booleanArrayProp_value,
};

static MI_CONST MI_Char* MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("goodbye"),
};

static MI_CONST MI_ConstStringA MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_stringArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_stringArrayProp_StringArrayQual_qual,
};

static MI_CONST MI_Char* MyArrayPropertiesArrayQualsClass_stringArrayProp_data_value[] =
{
    MI_T("hello&'><\"\\/"),
    MI_T("&'><\"\\/"),
};

static MI_CONST MI_ConstStringA MyArrayPropertiesArrayQualsClass_stringArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_stringArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_stringArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.stringArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_stringArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("stringArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_stringArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_stringArrayProp_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, stringArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_stringArrayProp_value,
};

static MI_CONST MI_Char16 MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_char16ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_char16ArrayProp_Char16ArrayQual_qual,
};

static MI_CONST MI_Char16 MyArrayPropertiesArrayQualsClass_char16ArrayProp_data_value[] =
{
    16,
    8,
};

static MI_CONST MI_ConstChar16A MyArrayPropertiesArrayQualsClass_char16ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_char16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_char16ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.char16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_char16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063700F, /* code */
    MI_T("char16ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_char16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_char16ArrayProp_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, char16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_char16ArrayProp_value,
};

static MI_CONST MI_Uint8 MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_uint8ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_uint8ArrayProp_Uint8ArrayQual_qual,
};

static MI_CONST MI_Uint8 MyArrayPropertiesArrayQualsClass_uint8ArrayProp_data_value[] =
{
    1,
    12,
};

static MI_CONST MI_ConstUint8A MyArrayPropertiesArrayQualsClass_uint8ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_uint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint8ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.uint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_uint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700E, /* code */
    MI_T("uint8ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_uint8ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint8ArrayProp_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, uint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_uint8ArrayProp_value,
};

static MI_CONST MI_Sint8 MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_sint8ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_sint8ArrayProp_Sint8ArrayQual_qual,
};

static MI_CONST MI_Sint8 MyArrayPropertiesArrayQualsClass_sint8ArrayProp_data_value[] =
{
    -1,
    -99,
};

static MI_CONST MI_ConstSint8A MyArrayPropertiesArrayQualsClass_sint8ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_sint8ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint8ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.sint8ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_sint8ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700E, /* code */
    MI_T("sint8ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_sint8ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint8ArrayProp_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, sint8ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_sint8ArrayProp_value,
};

static MI_CONST MI_Uint16 MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_uint16ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_uint16ArrayProp_Uint16ArrayQual_qual,
};

static MI_CONST MI_Uint16 MyArrayPropertiesArrayQualsClass_uint16ArrayProp_data_value[] =
{
    2,
    22,
};

static MI_CONST MI_ConstUint16A MyArrayPropertiesArrayQualsClass_uint16ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_uint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint16ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.uint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_uint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint16ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_uint16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint16ArrayProp_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, uint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_uint16ArrayProp_value,
};

static MI_CONST MI_Sint16 MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_sint16ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_sint16ArrayProp_Sint16ArrayQual_qual,
};

static MI_CONST MI_Sint16 MyArrayPropertiesArrayQualsClass_sint16ArrayProp_data_value[] =
{
    2,
    -100,
};

static MI_CONST MI_ConstSint16A MyArrayPropertiesArrayQualsClass_sint16ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_sint16ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint16ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.sint16ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_sint16ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint16ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_sint16ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint16ArrayProp_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, sint16ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_sint16ArrayProp_value,
};

static MI_CONST MI_Uint32 MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_uint32ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_uint32ArrayProp_Uint32ArrayQual_qual,
};

static MI_CONST MI_Uint32 MyArrayPropertiesArrayQualsClass_uint32ArrayProp_data_value[] =
{
    3U,
    333U,
};

static MI_CONST MI_ConstUint32A MyArrayPropertiesArrayQualsClass_uint32ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_uint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint32ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.uint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_uint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint32ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_uint32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint32ArrayProp_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, uint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_uint32ArrayProp_value,
};

static MI_CONST MI_Sint32 MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_sint32ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_sint32ArrayProp_Sint32ArrayQual_qual,
};

static MI_CONST MI_Sint32 MyArrayPropertiesArrayQualsClass_sint32ArrayProp_data_value[] =
{
    3,
    -32335,
};

static MI_CONST MI_ConstSint32A MyArrayPropertiesArrayQualsClass_sint32ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_sint32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint32ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.sint32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_sint32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint32ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_sint32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint32ArrayProp_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, sint32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_sint32ArrayProp_value,
};

static MI_CONST MI_Uint64 MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_uint64ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_uint64ArrayProp_Uint64ArrayQual_qual,
};

static MI_CONST MI_Uint64 MyArrayPropertiesArrayQualsClass_uint64ArrayProp_data_value[] =
{
    MI_ULL(4),
    MI_ULL(123456789),
};

static MI_CONST MI_ConstUint64A MyArrayPropertiesArrayQualsClass_uint64ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_uint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint64ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.uint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_uint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint64ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_uint64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_uint64ArrayProp_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, uint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_uint64ArrayProp_value,
};

static MI_CONST MI_Sint64 MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_sint64ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_sint64ArrayProp_Sint64ArrayQual_qual,
};

static MI_CONST MI_Sint64 MyArrayPropertiesArrayQualsClass_sint64ArrayProp_data_value[] =
{
    -MI_LL(456789123),
    MI_LL(789123456),
};

static MI_CONST MI_ConstSint64A MyArrayPropertiesArrayQualsClass_sint64ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_sint64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint64ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.sint64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_sint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073700F, /* code */
    MI_T("sint64ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_sint64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_sint64ArrayProp_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, sint64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_sint64ArrayProp_value,
};

static MI_CONST MI_Real32 MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_real32ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_real32ArrayProp_Real32ArrayQual_qual,
};

static MI_CONST MI_Real32 MyArrayPropertiesArrayQualsClass_real32ArrayProp_data_value[] =
{
    (float)1.1,
    (float)-2.3,
};

static MI_CONST MI_ConstReal32A MyArrayPropertiesArrayQualsClass_real32ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_real32ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real32ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.real32ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_real32ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real32ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_real32ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real32ArrayProp_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, real32ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_real32ArrayProp_value,
};

static MI_CONST MI_Real64 MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_real64ArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_real64ArrayProp_Real64ArrayQual_qual,
};

static MI_CONST MI_Real64 MyArrayPropertiesArrayQualsClass_real64ArrayProp_data_value[] =
{
    (double)-2.2,
    (double)3.4,
};

static MI_CONST MI_ConstReal64A MyArrayPropertiesArrayQualsClass_real64ArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_real64ArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real64ArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.real64ArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_real64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072700F, /* code */
    MI_T("real64ArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_real64ArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_real64ArrayProp_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, real64ArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_real64ArrayProp_value,
};

static MI_CONST MI_Datetime MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual_value =
{
    MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_datetimeArrayProp_quals[] =
{
    &MyArrayPropertiesArrayQualsClass_datetimeArrayProp_DatetimeArrayQual_qual,
};

static MI_CONST MI_Datetime MyArrayPropertiesArrayQualsClass_datetimeArrayProp_data_value[] =
{
    {1,{{2011,3,14,22,24,12,0,8}}},
    {1,{{2013,10,14,23,44,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayPropertiesArrayQualsClass_datetimeArrayProp_value =
{
    MyArrayPropertiesArrayQualsClass_datetimeArrayProp_data_value,
    MI_COUNT(MyArrayPropertiesArrayQualsClass_datetimeArrayProp_data_value),
};

/* property MyArrayPropertiesArrayQualsClass.datetimeArrayProp */
static MI_CONST MI_PropertyDecl MyArrayPropertiesArrayQualsClass_datetimeArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647011, /* code */
    MI_T("datetimeArrayProp"), /* name */
    MyArrayPropertiesArrayQualsClass_datetimeArrayProp_quals, /* qualifiers */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_datetimeArrayProp_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayPropertiesArrayQualsClass, datetimeArrayProp), /* offset */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* origin */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* propagator */
    &MyArrayPropertiesArrayQualsClass_datetimeArrayProp_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyArrayPropertiesArrayQualsClass_props[] =
{
    &MyArrayPropertiesArrayQualsClass_booleanArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_stringArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_char16ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_uint8ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_sint8ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_uint16ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_sint16ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_uint32ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_sint32ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_uint64ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_sint64ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_real32ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_real64ArrayProp_prop,
    &MyArrayPropertiesArrayQualsClass_datetimeArrayProp_prop,
};

static MI_CONST MI_ProviderFT MyArrayPropertiesArrayQualsClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayPropertiesArrayQualsClass_Load,
  (MI_ProviderFT_Unload)MyArrayPropertiesArrayQualsClass_Unload,
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

/* class MyArrayPropertiesArrayQualsClass */
MI_CONST MI_ClassDecl MyArrayPropertiesArrayQualsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7320, /* code */
    MI_T("MyArrayPropertiesArrayQualsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayPropertiesArrayQualsClass_props, /* properties */
    MI_COUNT(MyArrayPropertiesArrayQualsClass_props), /* numProperties */
    sizeof(MyArrayPropertiesArrayQualsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayPropertiesArrayQualsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyNoParamMethodsClass
**
**==============================================================================
*/


/* parameter MyNoParamMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_BooleanMethod_params[] =
{
    &MyNoParamMethodsClass_BooleanMethod_MIReturn_param,
};

/* method MyNoParamMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_BooleanMethod, /* method */
};

/* parameter MyNoParamMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_StringMethod_params[] =
{
    &MyNoParamMethodsClass_StringMethod_MIReturn_param,
};

/* method MyNoParamMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_StringMethod, /* method */
};

/* parameter MyNoParamMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Char16Method_params[] =
{
    &MyNoParamMethodsClass_Char16Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Char16Method, /* method */
};

/* parameter MyNoParamMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Uint8Method_params[] =
{
    &MyNoParamMethodsClass_Uint8Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Uint8Method, /* method */
};

/* parameter MyNoParamMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Sint8Method_params[] =
{
    &MyNoParamMethodsClass_Sint8Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Sint8Method, /* method */
};

/* parameter MyNoParamMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Uint16Method_params[] =
{
    &MyNoParamMethodsClass_Uint16Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Uint16Method, /* method */
};

/* parameter MyNoParamMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Sint16Method_params[] =
{
    &MyNoParamMethodsClass_Sint16Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Sint16Method, /* method */
};

/* parameter MyNoParamMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Uint32Method_params[] =
{
    &MyNoParamMethodsClass_Uint32Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Uint32Method, /* method */
};

/* parameter MyNoParamMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Sint32Method_params[] =
{
    &MyNoParamMethodsClass_Sint32Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Sint32Method, /* method */
};

/* parameter MyNoParamMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Uint64Method_params[] =
{
    &MyNoParamMethodsClass_Uint64Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Uint64Method, /* method */
};

/* parameter MyNoParamMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Sint64Method_params[] =
{
    &MyNoParamMethodsClass_Sint64Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Sint64Method, /* method */
};

/* parameter MyNoParamMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Real32Method_params[] =
{
    &MyNoParamMethodsClass_Real32Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Real32Method, /* method */
};

/* parameter MyNoParamMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_Real64Method_params[] =
{
    &MyNoParamMethodsClass_Real64Method_MIReturn_param,
};

/* method MyNoParamMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_Real64Method, /* method */
};

/* parameter MyNoParamMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamMethodsClass_DatetimeMethod_params[] =
{
    &MyNoParamMethodsClass_DatetimeMethod_MIReturn_param,
};

/* method MyNoParamMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyNoParamMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyNoParamMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyNoParamMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyNoParamMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyNoParamMethodsClass"), /* origin */
    MI_T("MyNoParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyNoParamMethodsClass_meths[] =
{
    &MyNoParamMethodsClass_BooleanMethod_rtti,
    &MyNoParamMethodsClass_StringMethod_rtti,
    &MyNoParamMethodsClass_Char16Method_rtti,
    &MyNoParamMethodsClass_Uint8Method_rtti,
    &MyNoParamMethodsClass_Sint8Method_rtti,
    &MyNoParamMethodsClass_Uint16Method_rtti,
    &MyNoParamMethodsClass_Sint16Method_rtti,
    &MyNoParamMethodsClass_Uint32Method_rtti,
    &MyNoParamMethodsClass_Sint32Method_rtti,
    &MyNoParamMethodsClass_Uint64Method_rtti,
    &MyNoParamMethodsClass_Sint64Method_rtti,
    &MyNoParamMethodsClass_Real32Method_rtti,
    &MyNoParamMethodsClass_Real64Method_rtti,
    &MyNoParamMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyNoParamMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyNoParamMethodsClass_Load,
  (MI_ProviderFT_Unload)MyNoParamMethodsClass_Unload,
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

/* class MyNoParamMethodsClass */
MI_CONST MI_ClassDecl MyNoParamMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7315, /* code */
    MI_T("MyNoParamMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyNoParamMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyNoParamMethodsClass_meths, /* methods */
    MI_COUNT(MyNoParamMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyNoParamMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyNoParamSimpleQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MyNoParamSimpleQualsMethodsClass_BooleanMethod_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_BooleanMethod_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_BooleanMethod_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_BooleanQual_qual,
};

static MI_CONST MI_Boolean MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_BooleanQual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_BooleanMethod_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    MyNoParamSimpleQualsMethodsClass_BooleanMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_BooleanMethod_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MyNoParamSimpleQualsMethodsClass_StringMethod_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_StringMethod_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_StringMethod_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_StringMethod_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_StringMethod_StringQual_qual,
};

static MI_CONST MI_Char* MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_StringQual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_StringMethod_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_StringMethod_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    MyNoParamSimpleQualsMethodsClass_StringMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_StringMethod_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MyNoParamSimpleQualsMethodsClass_Char16Method_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Char16Method_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Char16Method_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Char16Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Char16Method_Char16Qual_qual,
};

static MI_CONST MI_Char16 MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_Char16Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Char16Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Char16Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Char16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Char16Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MyNoParamSimpleQualsMethodsClass_Uint8Method_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint8Method_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint8Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_Uint8Qual_qual,
};

static MI_CONST MI_Uint8 MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_Uint8Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint8Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint8Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint8Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MyNoParamSimpleQualsMethodsClass_Sint8Method_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint8Method_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint8Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_Sint8Qual_qual,
};

static MI_CONST MI_Sint8 MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_Sint8Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint8Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint8Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint8Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MyNoParamSimpleQualsMethodsClass_Uint16Method_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint16Method_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint16Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_Uint16Qual_qual,
};

static MI_CONST MI_Uint16 MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_Uint16Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint16Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint16Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MyNoParamSimpleQualsMethodsClass_Sint16Method_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint16Method_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint16Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_Sint16Qual_qual,
};

static MI_CONST MI_Sint16 MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_Sint16Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint16Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint16Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MyNoParamSimpleQualsMethodsClass_Uint32Method_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint32Method_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint32Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_Uint32Qual_qual,
};

static MI_CONST MI_Uint32 MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_Uint32Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint32Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint32Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MyNoParamSimpleQualsMethodsClass_Sint32Method_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint32Method_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint32Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_Sint32Qual_qual,
};

static MI_CONST MI_Sint32 MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_Sint32Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint32Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint32Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MyNoParamSimpleQualsMethodsClass_Uint64Method_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint64Method_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint64Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_Uint64Qual_qual,
};

static MI_CONST MI_Uint64 MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_Uint64Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Uint64Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Uint64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint64Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MyNoParamSimpleQualsMethodsClass_Sint64Method_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint64Method_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint64Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_Sint64Qual_qual,
};

static MI_CONST MI_Sint64 MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_Sint64Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Sint64Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Sint64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint64Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MyNoParamSimpleQualsMethodsClass_Real32Method_Real32Qual_qual_value = (float)-1.1234;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Real32Method_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Real32Method_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real32Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real32Method_Real32Qual_qual,
};

static MI_CONST MI_Real32 MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_Real32Qual_qual_value = (float)-1.1234;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_Real32Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real32Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real32Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Real32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real32Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MyNoParamSimpleQualsMethodsClass_Real64Method_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Real64Method_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Real64Method_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real64Method_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real64Method_Real64Qual_qual,
};

static MI_CONST MI_Real64 MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_Real64Qual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_Real64Method_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_Real64Method_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    MyNoParamSimpleQualsMethodsClass_Real64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real64Method_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MyNoParamSimpleQualsMethodsClass_DatetimeMethod_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_DatetimeMethod_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_DatetimeMethod_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_DatetimeQual_qual,
};

static MI_CONST MI_Datetime MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_quals[] =
{
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeQual_qual,
};

/* parameter MyNoParamSimpleQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamSimpleQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_DatetimeMethod_params[] =
{
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param,
};

/* method MyNoParamSimpleQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyNoParamSimpleQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_DatetimeMethod_quals), /* numQualifiers */
    MyNoParamSimpleQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyNoParamSimpleQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamSimpleQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyNoParamSimpleQualsMethodsClass_meths[] =
{
    &MyNoParamSimpleQualsMethodsClass_BooleanMethod_rtti,
    &MyNoParamSimpleQualsMethodsClass_StringMethod_rtti,
    &MyNoParamSimpleQualsMethodsClass_Char16Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Uint8Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Sint8Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Uint16Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Sint16Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Uint32Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Sint32Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Uint64Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Sint64Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Real32Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_Real64Method_rtti,
    &MyNoParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyNoParamSimpleQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyNoParamSimpleQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MyNoParamSimpleQualsMethodsClass_Unload,
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

/* class MyNoParamSimpleQualsMethodsClass */
MI_CONST MI_ClassDecl MyNoParamSimpleQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7320, /* code */
    MI_T("MyNoParamSimpleQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyNoParamSimpleQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyNoParamSimpleQualsMethodsClass_meths, /* methods */
    MI_COUNT(MyNoParamSimpleQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyNoParamSimpleQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyNoParamArrayQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual_data_value[] =
{
    0,
    1,
};

static MI_CONST MI_ConstBooleanA MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_BooleanMethod_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_BooleanArrayQual_qual,
};

static MI_CONST MI_Boolean MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual_data_value[] =
{
    0,
    1,
};

static MI_CONST MI_ConstBooleanA MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_BooleanArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_BooleanMethod_params[] =
{
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    MyNoParamArrayQualsMethodsClass_BooleanMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_BooleanMethod_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("\"<>&',.goodbye"),
};

static MI_CONST MI_ConstStringA MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_StringMethod_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_StringMethod_StringArrayQual_qual,
};

static MI_CONST MI_Char* MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("\"<>&',.goodbye"),
};

static MI_CONST MI_ConstStringA MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_StringArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_StringMethod_params[] =
{
    &MyNoParamArrayQualsMethodsClass_StringMethod_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    MyNoParamArrayQualsMethodsClass_StringMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_StringMethod_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Char16Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Char16Method_Char16ArrayQual_qual,
};

static MI_CONST MI_Char16 MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_Char16ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Char16Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Char16Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Char16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Char16Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint8Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint8Method_Uint8ArrayQual_qual,
};

static MI_CONST MI_Uint8 MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_Uint8ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint8Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint8Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint8Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint8Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint8Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint8Method_Sint8ArrayQual_qual,
};

static MI_CONST MI_Sint8 MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_Sint8ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint8Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint8Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint8Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint8Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint16Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint16Method_Uint16ArrayQual_qual,
};

static MI_CONST MI_Uint16 MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_Uint16ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint16Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint16Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint16Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint16Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint16Method_Sint16ArrayQual_qual,
};

static MI_CONST MI_Sint16 MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_Sint16ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint16Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint16Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint16Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint16Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint32Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint32Method_Uint32ArrayQual_qual,
};

static MI_CONST MI_Uint32 MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_Uint32ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint32Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint32Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint32Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint32Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint32Method_Sint32ArrayQual_qual,
};

static MI_CONST MI_Sint32 MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_Sint32ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint32Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint32Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint32Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint64Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint64Method_Uint64ArrayQual_qual,
};

static MI_CONST MI_Uint64 MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_Uint64ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Uint64Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Uint64Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Uint64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint64Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint64Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint64Method_Sint64ArrayQual_qual,
};

static MI_CONST MI_Sint64 MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_Sint64ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Sint64Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Sint64Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Sint64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint64Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real32Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Real32Method_Real32ArrayQual_qual,
};

static MI_CONST MI_Real32 MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_Real32ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real32Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Real32Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Real32Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real32Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real64Method_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Real64Method_Real64ArrayQual_qual,
};

static MI_CONST MI_Real64 MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_Real64ArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_Real64Method_params[] =
{
    &MyNoParamArrayQualsMethodsClass_Real64Method_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    MyNoParamArrayQualsMethodsClass_Real64Method_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real64Method_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_DatetimeMethod_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_DatetimeArrayQual_qual,
};

static MI_CONST MI_Datetime MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual_value =
{
    MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_quals[] =
{
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_DatetimeArrayQual_qual,
};

/* parameter MyNoParamArrayQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyNoParamArrayQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_DatetimeMethod_params[] =
{
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param,
};

/* method MyNoParamArrayQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyNoParamArrayQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    MyNoParamArrayQualsMethodsClass_DatetimeMethod_quals, /* qualifiers */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_DatetimeMethod_quals), /* numQualifiers */
    MyNoParamArrayQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyNoParamArrayQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyNoParamArrayQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyNoParamArrayQualsMethodsClass_meths[] =
{
    &MyNoParamArrayQualsMethodsClass_BooleanMethod_rtti,
    &MyNoParamArrayQualsMethodsClass_StringMethod_rtti,
    &MyNoParamArrayQualsMethodsClass_Char16Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Uint8Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Sint8Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Uint16Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Sint16Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Uint32Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Sint32Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Uint64Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Sint64Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Real32Method_rtti,
    &MyNoParamArrayQualsMethodsClass_Real64Method_rtti,
    &MyNoParamArrayQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyNoParamArrayQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyNoParamArrayQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MyNoParamArrayQualsMethodsClass_Unload,
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

/* class MyNoParamArrayQualsMethodsClass */
MI_CONST MI_ClassDecl MyNoParamArrayQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D731F, /* code */
    MI_T("MyNoParamArrayQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyNoParamArrayQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyNoParamArrayQualsMethodsClass_meths, /* methods */
    MI_COUNT(MyNoParamArrayQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyNoParamArrayQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimpleParamMethodsClass
**
**==============================================================================
*/


/* parameter MySimpleParamMethodsClass.BooleanSimpleParamMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_BooleanSimpleParamMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_BooleanSimpleParamMethod, booleanParam), /* offset */
};

/* parameter MySimpleParamMethodsClass.BooleanSimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_BooleanSimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_BooleanSimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_BooleanSimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_BooleanSimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_BooleanSimpleParamMethod_booleanParam_param,
};

/* method MySimpleParamMethodsClass.BooleanSimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_BooleanSimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00626418, /* code */
    MI_T("BooleanSimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_BooleanSimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_BooleanSimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_BooleanSimpleParamMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_BooleanSimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.StringSimpleParamMethod(): stringParam */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_StringSimpleParamMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_StringSimpleParamMethod, stringParam), /* offset */
};

/* parameter MySimpleParamMethodsClass.StringSimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_StringSimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_StringSimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_StringSimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_StringSimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_StringSimpleParamMethod_stringParam_param,
};

/* method MySimpleParamMethodsClass.StringSimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_StringSimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736417, /* code */
    MI_T("StringSimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_StringSimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_StringSimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_StringSimpleParamMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_StringSimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Char16SimpleParamMethod(): char16Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Char16SimpleParamMethod_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Char16SimpleParamMethod, char16Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Char16SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Char16SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Char16SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Char16SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Char16SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Char16SimpleParamMethod_char16Param_param,
};

/* method MySimpleParamMethodsClass.Char16SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Char16SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00636417, /* code */
    MI_T("Char16SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Char16SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Char16SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Char16SimpleParamMethod), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Char16SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Uint8SimpleParamMethod(): uint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint8SimpleParamMethod_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint8SimpleParamMethod, uint8Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Uint8SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint8SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint8SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Uint8SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Uint8SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Uint8SimpleParamMethod_uint8Param_param,
};

/* method MySimpleParamMethodsClass.Uint8SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint8SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756416, /* code */
    MI_T("Uint8SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Uint8SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Uint8SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Uint8SimpleParamMethod), /* size */
    MI_UINT8, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Uint8SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Sint8SimpleParamMethod(): sint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint8SimpleParamMethod_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint8SimpleParamMethod, sint8Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Sint8SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint8SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint8SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Sint8SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Sint8SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Sint8SimpleParamMethod_sint8Param_param,
};

/* method MySimpleParamMethodsClass.Sint8SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint8SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736416, /* code */
    MI_T("Sint8SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Sint8SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Sint8SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Sint8SimpleParamMethod), /* size */
    MI_SINT8, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Sint8SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Uint16SimpleParamMethod(): uint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint16SimpleParamMethod_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint16SimpleParamMethod, uint16Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Uint16SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint16SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint16SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Uint16SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Uint16SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Uint16SimpleParamMethod_uint16Param_param,
};

/* method MySimpleParamMethodsClass.Uint16SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint16SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756417, /* code */
    MI_T("Uint16SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Uint16SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Uint16SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Uint16SimpleParamMethod), /* size */
    MI_UINT16, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Uint16SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Sint16SimpleParamMethod(): sint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint16SimpleParamMethod_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint16SimpleParamMethod, sint16Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Sint16SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint16SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint16SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Sint16SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Sint16SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Sint16SimpleParamMethod_sint16Param_param,
};

/* method MySimpleParamMethodsClass.Sint16SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint16SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736417, /* code */
    MI_T("Sint16SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Sint16SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Sint16SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Sint16SimpleParamMethod), /* size */
    MI_SINT16, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Sint16SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Uint32SimpleParamMethod(): uint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint32SimpleParamMethod_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint32SimpleParamMethod, uint32Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Uint32SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint32SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint32SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Uint32SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Uint32SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Uint32SimpleParamMethod_uint32Param_param,
};

/* method MySimpleParamMethodsClass.Uint32SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint32SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756417, /* code */
    MI_T("Uint32SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Uint32SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Uint32SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Uint32SimpleParamMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Uint32SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Sint32SimpleParamMethod(): sint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint32SimpleParamMethod_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint32SimpleParamMethod, sint32Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Sint32SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint32SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint32SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Sint32SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Sint32SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Sint32SimpleParamMethod_sint32Param_param,
};

/* method MySimpleParamMethodsClass.Sint32SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint32SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736417, /* code */
    MI_T("Sint32SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Sint32SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Sint32SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Sint32SimpleParamMethod), /* size */
    MI_SINT32, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Sint32SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Uint64SimpleParamMethod(): uint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint64SimpleParamMethod_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint64SimpleParamMethod, uint64Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Uint64SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Uint64SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Uint64SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Uint64SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Uint64SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Uint64SimpleParamMethod_uint64Param_param,
};

/* method MySimpleParamMethodsClass.Uint64SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Uint64SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756417, /* code */
    MI_T("Uint64SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Uint64SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Uint64SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Uint64SimpleParamMethod), /* size */
    MI_UINT64, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Uint64SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Sint64SimpleParamMethod(): sint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint64SimpleParamMethod_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint64SimpleParamMethod, sint64Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Sint64SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Sint64SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Sint64SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Sint64SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Sint64SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Sint64SimpleParamMethod_sint64Param_param,
};

/* method MySimpleParamMethodsClass.Sint64SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Sint64SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736417, /* code */
    MI_T("Sint64SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Sint64SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Sint64SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Sint64SimpleParamMethod), /* size */
    MI_SINT64, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Sint64SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Real32SimpleParamMethod(): real32Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Real32SimpleParamMethod_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Real32SimpleParamMethod, real32Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Real32SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Real32SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Real32SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Real32SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Real32SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Real32SimpleParamMethod_real32Param_param,
};

/* method MySimpleParamMethodsClass.Real32SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Real32SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726417, /* code */
    MI_T("Real32SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Real32SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Real32SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Real32SimpleParamMethod), /* size */
    MI_REAL32, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Real32SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.Real64SimpleParamMethod(): real64Param */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Real64SimpleParamMethod_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Real64SimpleParamMethod, real64Param), /* offset */
};

/* parameter MySimpleParamMethodsClass.Real64SimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_Real64SimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_Real64SimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_Real64SimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_Real64SimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_Real64SimpleParamMethod_real64Param_param,
};

/* method MySimpleParamMethodsClass.Real64SimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_Real64SimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726417, /* code */
    MI_T("Real64SimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_Real64SimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_Real64SimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_Real64SimpleParamMethod), /* size */
    MI_REAL64, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_Real64SimpleParamMethod, /* method */
};

/* parameter MySimpleParamMethodsClass.DatetimeSimpleParamMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_DatetimeSimpleParamMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_DatetimeSimpleParamMethod, datetimeParam), /* offset */
};

/* parameter MySimpleParamMethodsClass.DatetimeSimpleParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamMethodsClass_DatetimeSimpleParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamMethodsClass_DatetimeSimpleParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_DatetimeSimpleParamMethod_params[] =
{
    &MySimpleParamMethodsClass_DatetimeSimpleParamMethod_MIReturn_param,
    &MySimpleParamMethodsClass_DatetimeSimpleParamMethod_datetimeParam_param,
};

/* method MySimpleParamMethodsClass.DatetimeSimpleParamMethod() */
MI_CONST MI_MethodDecl MySimpleParamMethodsClass_DatetimeSimpleParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00646419, /* code */
    MI_T("DatetimeSimpleParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamMethodsClass_DatetimeSimpleParamMethod_params, /* parameters */
    MI_COUNT(MySimpleParamMethodsClass_DatetimeSimpleParamMethod_params), /* numParameters */
    sizeof(MySimpleParamMethodsClass_DatetimeSimpleParamMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MySimpleParamMethodsClass"), /* origin */
    MI_T("MySimpleParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamMethodsClass_Invoke_DatetimeSimpleParamMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySimpleParamMethodsClass_meths[] =
{
    &MySimpleParamMethodsClass_BooleanSimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_StringSimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Char16SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Uint8SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Sint8SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Uint16SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Sint16SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Uint32SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Sint32SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Uint64SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Sint64SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Real32SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_Real64SimpleParamMethod_rtti,
    &MySimpleParamMethodsClass_DatetimeSimpleParamMethod_rtti,
};

static MI_CONST MI_ProviderFT MySimpleParamMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MySimpleParamMethodsClass_Load,
  (MI_ProviderFT_Unload)MySimpleParamMethodsClass_Unload,
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

/* class MySimpleParamMethodsClass */
MI_CONST MI_ClassDecl MySimpleParamMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7319, /* code */
    MI_T("MySimpleParamMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MySimpleParamMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MySimpleParamMethodsClass_meths, /* methods */
    MI_COUNT(MySimpleParamMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySimpleParamMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayParamMethodsClass
**
**==============================================================================
*/


/* parameter MyArrayParamMethodsClass.BooleanMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_BooleanMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_BooleanMethod, booleanParam), /* offset */
};

/* parameter MyArrayParamMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_BooleanMethod_params[] =
{
    &MyArrayParamMethodsClass_BooleanMethod_MIReturn_param,
    &MyArrayParamMethodsClass_BooleanMethod_booleanParam_param,
};

/* method MyArrayParamMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_BooleanMethod, /* method */
};

/* parameter MyArrayParamMethodsClass.StringMethod(): stringParam */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_StringMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_StringMethod, stringParam), /* offset */
};

/* parameter MyArrayParamMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_StringMethod_params[] =
{
    &MyArrayParamMethodsClass_StringMethod_MIReturn_param,
    &MyArrayParamMethodsClass_StringMethod_stringParam_param,
};

/* method MyArrayParamMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_StringMethod, /* method */
};

/* parameter MyArrayParamMethodsClass.Char16Method(): char16Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Char16Method_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Char16Method, char16Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Char16Method_params[] =
{
    &MyArrayParamMethodsClass_Char16Method_MIReturn_param,
    &MyArrayParamMethodsClass_Char16Method_char16Param_param,
};

/* method MyArrayParamMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Char16Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Uint8Method(): uint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint8Method_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint8Method, uint8Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Uint8Method_params[] =
{
    &MyArrayParamMethodsClass_Uint8Method_MIReturn_param,
    &MyArrayParamMethodsClass_Uint8Method_uint8Param_param,
};

/* method MyArrayParamMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Uint8Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Sint8Method(): sint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint8Method_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint8Method, sint8Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Sint8Method_params[] =
{
    &MyArrayParamMethodsClass_Sint8Method_MIReturn_param,
    &MyArrayParamMethodsClass_Sint8Method_sint8Param_param,
};

/* method MyArrayParamMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Sint8Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Uint16Method(): uint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint16Method_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint16Method, uint16Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Uint16Method_params[] =
{
    &MyArrayParamMethodsClass_Uint16Method_MIReturn_param,
    &MyArrayParamMethodsClass_Uint16Method_uint16Param_param,
};

/* method MyArrayParamMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Uint16Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Sint16Method(): sint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint16Method_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint16Method, sint16Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Sint16Method_params[] =
{
    &MyArrayParamMethodsClass_Sint16Method_MIReturn_param,
    &MyArrayParamMethodsClass_Sint16Method_sint16Param_param,
};

/* method MyArrayParamMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Sint16Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Uint32Method(): uint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint32Method_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint32Method, uint32Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Uint32Method_params[] =
{
    &MyArrayParamMethodsClass_Uint32Method_MIReturn_param,
    &MyArrayParamMethodsClass_Uint32Method_uint32Param_param,
};

/* method MyArrayParamMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Uint32Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Sint32Method(): sint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint32Method_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint32Method, sint32Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Sint32Method_params[] =
{
    &MyArrayParamMethodsClass_Sint32Method_MIReturn_param,
    &MyArrayParamMethodsClass_Sint32Method_sint32Param_param,
};

/* method MyArrayParamMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Sint32Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Uint64Method(): uint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint64Method_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint64Method, uint64Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Uint64Method_params[] =
{
    &MyArrayParamMethodsClass_Uint64Method_MIReturn_param,
    &MyArrayParamMethodsClass_Uint64Method_uint64Param_param,
};

/* method MyArrayParamMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Uint64Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Sint64Method(): sint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint64Method_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint64Method, sint64Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Sint64Method_params[] =
{
    &MyArrayParamMethodsClass_Sint64Method_MIReturn_param,
    &MyArrayParamMethodsClass_Sint64Method_sint64Param_param,
};

/* method MyArrayParamMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Sint64Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Real32Method(): real32Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Real32Method_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Real32Method, real32Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Real32Method_params[] =
{
    &MyArrayParamMethodsClass_Real32Method_MIReturn_param,
    &MyArrayParamMethodsClass_Real32Method_real32Param_param,
};

/* method MyArrayParamMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Real32Method, /* method */
};

/* parameter MyArrayParamMethodsClass.Real64Method(): real64Param */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Real64Method_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Real64Method, real64Param), /* offset */
};

/* parameter MyArrayParamMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_Real64Method_params[] =
{
    &MyArrayParamMethodsClass_Real64Method_MIReturn_param,
    &MyArrayParamMethodsClass_Real64Method_real64Param_param,
};

/* method MyArrayParamMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_Real64Method, /* method */
};

/* parameter MyArrayParamMethodsClass.DatetimeMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_DatetimeMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_DatetimeMethod, datetimeParam), /* offset */
};

/* parameter MyArrayParamMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_DatetimeMethod_params[] =
{
    &MyArrayParamMethodsClass_DatetimeMethod_MIReturn_param,
    &MyArrayParamMethodsClass_DatetimeMethod_datetimeParam_param,
};

/* method MyArrayParamMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyArrayParamMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyArrayParamMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyArrayParamMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyArrayParamMethodsClass"), /* origin */
    MI_T("MyArrayParamMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyArrayParamMethodsClass_meths[] =
{
    &MyArrayParamMethodsClass_BooleanMethod_rtti,
    &MyArrayParamMethodsClass_StringMethod_rtti,
    &MyArrayParamMethodsClass_Char16Method_rtti,
    &MyArrayParamMethodsClass_Uint8Method_rtti,
    &MyArrayParamMethodsClass_Sint8Method_rtti,
    &MyArrayParamMethodsClass_Uint16Method_rtti,
    &MyArrayParamMethodsClass_Sint16Method_rtti,
    &MyArrayParamMethodsClass_Uint32Method_rtti,
    &MyArrayParamMethodsClass_Sint32Method_rtti,
    &MyArrayParamMethodsClass_Uint64Method_rtti,
    &MyArrayParamMethodsClass_Sint64Method_rtti,
    &MyArrayParamMethodsClass_Real32Method_rtti,
    &MyArrayParamMethodsClass_Real64Method_rtti,
    &MyArrayParamMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyArrayParamMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayParamMethodsClass_Load,
  (MI_ProviderFT_Unload)MyArrayParamMethodsClass_Unload,
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

/* class MyArrayParamMethodsClass */
MI_CONST MI_ClassDecl MyArrayParamMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7318, /* code */
    MI_T("MyArrayParamMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyArrayParamMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyArrayParamMethodsClass_meths, /* methods */
    MI_COUNT(MyArrayParamMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayParamMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayParamSimpleQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.BooleanMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_BooleanMethod, booleanParam), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_BooleanMethod_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.StringMethod(): stringParam */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_StringMethod, stringParam), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_StringMethod_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_StringMethod_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_StringMethod_stringParam_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Char16Method(): char16Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Char16Method, char16Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Char16Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Char16Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Char16Method_char16Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint8Method(): uint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint8Method, uint8Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint8Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Uint8Method_uint8Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint8Method(): sint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint8Method, sint8Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint8Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Sint8Method_sint8Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint16Method(): uint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint16Method, uint16Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint16Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Uint16Method_uint16Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint16Method(): sint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint16Method, sint16Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint16Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Sint16Method_sint16Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint32Method(): uint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint32Method, uint32Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint32Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Uint32Method_uint32Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint32Method(): sint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint32Method, sint32Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint32Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Sint32Method_sint32Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint64Method(): uint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint64Method, uint64Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Uint64Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Uint64Method_uint64Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint64Method(): sint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint64Method, sint64Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Sint64Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Sint64Method_sint64Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual_value = (float)-1.1234;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Real32Method(): real32Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Real32Method, real32Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Real32Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Real32Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Real32Method_real32Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Real64Method(): real64Param */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Real64Method, real64Param), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_Real64Method_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_Real64Method_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_Real64Method_real64Param_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals[] =
{
    &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual,
};

/* parameter MyArrayParamSimpleQualsMethodsClass.DatetimeMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_DatetimeMethod, datetimeParam), /* offset */
};

/* parameter MyArrayParamSimpleQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamSimpleQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_params[] =
{
    &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param,
    &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_param,
};

/* method MyArrayParamSimpleQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyArrayParamSimpleQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamSimpleQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyArrayParamSimpleQualsMethodsClass_meths[] =
{
    &MyArrayParamSimpleQualsMethodsClass_BooleanMethod_rtti,
    &MyArrayParamSimpleQualsMethodsClass_StringMethod_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Char16Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Uint8Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Sint8Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Uint16Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Sint16Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Uint32Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Sint32Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Uint64Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Sint64Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Real32Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_Real64Method_rtti,
    &MyArrayParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyArrayParamSimpleQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayParamSimpleQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MyArrayParamSimpleQualsMethodsClass_Unload,
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

/* class MyArrayParamSimpleQualsMethodsClass */
MI_CONST MI_ClassDecl MyArrayParamSimpleQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7323, /* code */
    MI_T("MyArrayParamSimpleQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyArrayParamSimpleQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyArrayParamSimpleQualsMethodsClass_meths, /* methods */
    MI_COUNT(MyArrayParamSimpleQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayParamSimpleQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyArrayParamArrayQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value[] =
{
    0,
    1,
};

static MI_CONST MI_ConstBooleanA MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.BooleanMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals), /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_BooleanMethod, booleanParam), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_BooleanMethod_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_BooleanMethod_booleanParam_param,
};

/* method MyArrayParamArrayQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("\"<>&',.goodbye"),
};

static MI_CONST MI_ConstStringA MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.StringMethod(): stringParam */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_StringMethod, stringParam), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_StringMethod_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_StringMethod_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_StringMethod_stringParam_param,
};

/* method MyArrayParamArrayQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Char16Method(): char16Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_quals), /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Char16Method, char16Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Char16Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Char16Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Char16Method_char16Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint8Method(): uint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint8Method, uint8Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint8Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint8Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Uint8Method_uint8Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint8Method(): sint8Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals), /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint8Method, sint8Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint8Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint8Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Sint8Method_sint8Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint16Method(): uint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint16Method, uint16Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint16Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint16Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Uint16Method_uint16Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint16Method(): sint16Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals), /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint16Method, sint16Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint16Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint16Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Sint16Method_sint16Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint32Method(): uint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals), /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint32Method, uint32Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint32Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint32Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Uint32Method_uint32Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint32Method(): sint32Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals), /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint32Method, sint32Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint32Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint32Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Sint32Method_sint32Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint64Method(): uint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals), /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint64Method, uint64Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Uint64Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Uint64Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Uint64Method_uint64Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint64Method(): sint64Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals), /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint64Method, sint64Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Sint64Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Sint64Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Sint64Method_sint64Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Real32Method(): real32Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_quals), /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Real32Method, real32Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Real32Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Real32Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Real32Method_real32Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.Real64Method(): real64Param */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_quals), /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Real64Method, real64Param), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_Real64Method_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_Real64Method_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_Real64Method_real64Param_param,
};

/* method MyArrayParamArrayQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_value =
{
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals[] =
{
    &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual,
};

/* parameter MyArrayParamArrayQualsMethodsClass.DatetimeMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals, /* qualifiers */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals), /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_DatetimeMethod, datetimeParam), /* offset */
};

/* parameter MyArrayParamArrayQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyArrayParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyArrayParamArrayQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_DatetimeMethod_params[] =
{
    &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param,
    &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_param,
};

/* method MyArrayParamArrayQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MyArrayParamArrayQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyArrayParamArrayQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MyArrayParamArrayQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* origin */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyArrayParamArrayQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyArrayParamArrayQualsMethodsClass_meths[] =
{
    &MyArrayParamArrayQualsMethodsClass_BooleanMethod_rtti,
    &MyArrayParamArrayQualsMethodsClass_StringMethod_rtti,
    &MyArrayParamArrayQualsMethodsClass_Char16Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Uint8Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Sint8Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Uint16Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Sint16Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Uint32Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Sint32Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Uint64Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Sint64Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Real32Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_Real64Method_rtti,
    &MyArrayParamArrayQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MyArrayParamArrayQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MyArrayParamArrayQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MyArrayParamArrayQualsMethodsClass_Unload,
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

/* class MyArrayParamArrayQualsMethodsClass */
MI_CONST MI_ClassDecl MyArrayParamArrayQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7322, /* code */
    MI_T("MyArrayParamArrayQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MyArrayParamArrayQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyArrayParamArrayQualsMethodsClass_meths, /* methods */
    MI_COUNT(MyArrayParamArrayQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyArrayParamArrayQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimpleParamSimpleQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_BooleanQual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.BooleanMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_BooleanMethod, booleanParam), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_BooleanMethod_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_booleanParam_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual_value = MI_T("welcome\\&'><\"");

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_StringQual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.StringMethod(): stringParam */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_StringMethod, stringParam), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_StringMethod_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_StringMethod_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_StringMethod_stringParam_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual_value = 18;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual =
{
    MI_T("Char16Qual"),
    MI_CHAR16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_Char16Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Char16Method(): char16Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Char16Method, char16Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Char16Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Char16Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Char16Method_char16Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_Uint8Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint8Method(): uint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint8Method, uint8Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint8Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint8Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Uint8Method_uint8Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual_value = -55;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual =
{
    MI_T("Sint8Qual"),
    MI_SINT8,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_Sint8Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint8Method(): sint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint8Method, sint8Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint8Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint8Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Sint8Method_sint8Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual_value = 20;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual =
{
    MI_T("Uint16Qual"),
    MI_UINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_Uint16Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint16Method(): uint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint16Method, uint16Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint16Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint16Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Uint16Method_uint16Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual_value = -30;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual =
{
    MI_T("Sint16Qual"),
    MI_SINT16,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_Sint16Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint16Method(): sint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint16Method, sint16Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint16Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint16Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Sint16Method_sint16Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual_value = 1234U;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_Uint32Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint32Method(): uint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint32Method, uint32Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint32Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint32Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Uint32Method_uint32Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual_value = -1234;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual =
{
    MI_T("Sint32Qual"),
    MI_SINT32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_Sint32Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint32Method(): sint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint32Method, sint32Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint32Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint32Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Sint32Method_sint32Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual_value = MI_ULL(5678);

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual =
{
    MI_T("Uint64Qual"),
    MI_UINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_Uint64Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint64Method(): uint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint64Method, uint64Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Uint64Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Uint64Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Uint64Method_uint64Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual_value = -MI_LL(9999);

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual =
{
    MI_T("Sint64Qual"),
    MI_SINT64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_Sint64Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint64Method(): sint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint64Method, sint64Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Sint64Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Sint64Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Sint64Method_sint64Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual_value = (float)-1.1234;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual =
{
    MI_T("Real32Qual"),
    MI_REAL32,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_Real32Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Real32Method(): real32Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Real32Method, real32Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Real32Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Real32Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Real32Method_real32Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual_value = (double)2.2;

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual =
{
    MI_T("Real64Qual"),
    MI_REAL64,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_Real64Qual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Real64Method(): real64Param */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Real64Method, real64Param), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_Real64Method_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_Real64Method_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_Real64Method_real64Param_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual_value = {1,{{2011,3,14,22,24,12,0,8}}};

static MI_CONST MI_Qualifier MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual =
{
    MI_T("DatetimeQual"),
    MI_DATETIME,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals[] =
{
    &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeQual_qual,
};

/* parameter MySimpleParamSimpleQualsMethodsClass.DatetimeMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_DatetimeMethod, datetimeParam), /* offset */
};

/* parameter MySimpleParamSimpleQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamSimpleQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_params[] =
{
    &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_MIReturn_param,
    &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_datetimeParam_param,
};

/* method MySimpleParamSimpleQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MySimpleParamSimpleQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamSimpleQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySimpleParamSimpleQualsMethodsClass_meths[] =
{
    &MySimpleParamSimpleQualsMethodsClass_BooleanMethod_rtti,
    &MySimpleParamSimpleQualsMethodsClass_StringMethod_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Char16Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Uint8Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Sint8Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Uint16Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Sint16Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Uint32Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Sint32Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Uint64Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Sint64Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Real32Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_Real64Method_rtti,
    &MySimpleParamSimpleQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MySimpleParamSimpleQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MySimpleParamSimpleQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MySimpleParamSimpleQualsMethodsClass_Unload,
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

/* class MySimpleParamSimpleQualsMethodsClass */
MI_CONST MI_ClassDecl MySimpleParamSimpleQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7324, /* code */
    MI_T("MySimpleParamSimpleQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MySimpleParamSimpleQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MySimpleParamSimpleQualsMethodsClass_meths, /* methods */
    MI_COUNT(MySimpleParamSimpleQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySimpleParamSimpleQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySimpleParamArrayQualsMethodsClass
**
**==============================================================================
*/


static MI_CONST MI_Boolean MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value[] =
{
    0,
    1,
};

static MI_CONST MI_ConstBooleanA MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual =
{
    MI_T("BooleanArrayQual"),
    MI_BOOLEANA,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_BooleanArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.BooleanMethod(): booleanParam */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00626D0C, /* code */
    MI_T("booleanParam"), /* name */
    MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_BooleanMethod, booleanParam), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.BooleanMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_BooleanMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_BooleanMethod_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_BooleanMethod_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_BooleanMethod_booleanParam_param,
};

/* method MySimpleParamArrayQualsMethodsClass.BooleanMethod() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_BooleanMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0062640D, /* code */
    MI_T("BooleanMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_BooleanMethod_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_BooleanMethod_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_BooleanMethod), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_BooleanMethod, /* method */
};

static MI_CONST MI_Char* MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value[] =
{
    MI_T("hello&'><\""),
    MI_T("\"<>&',.goodbye"),
};

static MI_CONST MI_ConstStringA MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual =
{
    MI_T("StringArrayQual"),
    MI_STRINGA,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_StringArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.StringMethod(): stringParam */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("stringParam"), /* name */
    MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_StringMethod, stringParam), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.StringMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_StringMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_StringMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_StringMethod_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_StringMethod_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_StringMethod_stringParam_param,
};

/* method MySimpleParamArrayQualsMethodsClass.StringMethod() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_StringMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("StringMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_StringMethod_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_StringMethod_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_StringMethod), /* size */
    MI_STRING, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_StringMethod, /* method */
};

static MI_CONST MI_Char16 MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value[] =
{
    273,
    16,
};

static MI_CONST MI_ConstChar16A MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual =
{
    MI_T("Char16ArrayQual"),
    MI_CHAR16A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_Char16ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Char16Method(): char16Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00636D0B, /* code */
    MI_T("char16Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_quals), /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Char16Method, char16Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Char16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Char16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Char16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Char16Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Char16Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Char16Method_char16Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Char16Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Char16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063640C, /* code */
    MI_T("Char16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Char16Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Char16Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Char16Method), /* size */
    MI_CHAR16, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Char16Method, /* method */
};

static MI_CONST MI_Uint8 MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value[] =
{
    1,
    10,
};

static MI_CONST MI_ConstUint8A MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual =
{
    MI_T("Uint8ArrayQual"),
    MI_UINT8A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_Uint8ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint8Method(): uint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0A, /* code */
    MI_T("uint8Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint8Method, uint8Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint8Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint8Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Uint8Method_uint8Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Uint8Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640B, /* code */
    MI_T("Uint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Uint8Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint8Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Uint8Method), /* size */
    MI_UINT8, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Uint8Method, /* method */
};

static MI_CONST MI_Sint8 MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value[] =
{
    -1,
    1,
};

static MI_CONST MI_ConstSint8A MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual =
{
    MI_T("Sint8ArrayQual"),
    MI_SINT8A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_Sint8ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint8Method(): sint8Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0A, /* code */
    MI_T("sint8Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint8Method, sint8Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint8Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint8Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint8Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint8Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint8Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Sint8Method_sint8Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Sint8Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint8Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640B, /* code */
    MI_T("Sint8Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Sint8Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint8Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Sint8Method), /* size */
    MI_SINT8, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Sint8Method, /* method */
};

static MI_CONST MI_Uint16 MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value[] =
{
    2,
    20,
};

static MI_CONST MI_ConstUint16A MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual =
{
    MI_T("Uint16ArrayQual"),
    MI_UINT16A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_Uint16ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint16Method(): uint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint16Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint16Method, uint16Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint16Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint16Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Uint16Method_uint16Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Uint16Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Uint16Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint16Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Uint16Method), /* size */
    MI_UINT16, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Uint16Method, /* method */
};

static MI_CONST MI_Sint16 MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value[] =
{
    -2,
    2,
};

static MI_CONST MI_ConstSint16A MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual =
{
    MI_T("Sint16ArrayQual"),
    MI_SINT16A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_Sint16ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint16Method(): sint16Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint16Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint16Method, sint16Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint16Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint16Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint16Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint16Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint16Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Sint16Method_sint16Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Sint16Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint16Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint16Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Sint16Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint16Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Sint16Method), /* size */
    MI_SINT16, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Sint16Method, /* method */
};

static MI_CONST MI_Uint32 MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value[] =
{
    3U,
    30U,
};

static MI_CONST MI_ConstUint32A MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_Uint32ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint32Method(): uint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint32Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint32Method, uint32Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint32Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint32Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Uint32Method_uint32Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Uint32Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Uint32Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint32Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Uint32Method), /* size */
    MI_UINT32, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Uint32Method, /* method */
};

static MI_CONST MI_Sint32 MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value[] =
{
    -3,
    3,
};

static MI_CONST MI_ConstSint32A MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual =
{
    MI_T("Sint32ArrayQual"),
    MI_SINT32A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_Sint32ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint32Method(): sint32Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint32Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint32Method, sint32Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint32Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint32Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Sint32Method_sint32Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Sint32Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Sint32Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint32Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Sint32Method), /* size */
    MI_SINT32, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Sint32Method, /* method */
};

static MI_CONST MI_Uint64 MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_Uint64ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint64Method(): uint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00756D0B, /* code */
    MI_T("uint64Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint64Method, uint64Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Uint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Uint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Uint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Uint64Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Uint64Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Uint64Method_uint64Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Uint64Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Uint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0075640C, /* code */
    MI_T("Uint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Uint64Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Uint64Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Uint64Method), /* size */
    MI_UINT64, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Uint64Method, /* method */
};

static MI_CONST MI_Sint64 MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_Sint64ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint64Method(): sint64Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D0B, /* code */
    MI_T("sint64Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_quals), /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint64Method, sint64Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Sint64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Sint64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Sint64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Sint64Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Sint64Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Sint64Method_sint64Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Sint64Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Sint64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073640C, /* code */
    MI_T("Sint64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Sint64Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Sint64Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Sint64Method), /* size */
    MI_SINT64, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Sint64Method, /* method */
};

static MI_CONST MI_Real32 MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value[] =
{
    (float)1.1,
    (float)-1.1,
};

static MI_CONST MI_ConstReal32A MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual =
{
    MI_T("Real32ArrayQual"),
    MI_REAL32A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_Real32ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Real32Method(): real32Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real32Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Real32Method, real32Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Real32Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Real32Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Real32Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Real32Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Real32Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Real32Method_real32Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Real32Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Real32Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real32Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Real32Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real32Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Real32Method), /* size */
    MI_REAL32, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Real32Method, /* method */
};

static MI_CONST MI_Real64 MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value[] =
{
    (double)2.2,
    (double)-2.2,
};

static MI_CONST MI_ConstReal64A MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual =
{
    MI_T("Real64ArrayQual"),
    MI_REAL64A,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_Real64ArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.Real64Method(): real64Param */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00726D0B, /* code */
    MI_T("real64Param"), /* name */
    MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Real64Method, real64Param), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.Real64Method(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_Real64Method_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_Real64Method, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_Real64Method_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_Real64Method_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_Real64Method_real64Param_param,
};

/* method MySimpleParamArrayQualsMethodsClass.Real64Method() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_Real64Method_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0072640C, /* code */
    MI_T("Real64Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_Real64Method_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_Real64Method_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_Real64Method), /* size */
    MI_REAL64, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_Real64Method, /* method */
};

static MI_CONST MI_Datetime MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value[] =
{
    {1,{{2010,11,14,22,24,12,0,8}}},
    {1,{{2010,12,31,22,24,12,0,8}}},
};

static MI_CONST MI_ConstDatetimeA MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_value =
{
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value,
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual =
{
    MI_T("DatetimeArrayQual"),
    MI_DATETIMEA,
    MI_FLAG_TRANSLATABLE,
    &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals[] =
{
    &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_DatetimeArrayQual_qual,
};

/* parameter MySimpleParamArrayQualsMethodsClass.DatetimeMethod(): datetimeParam */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00646D0D, /* code */
    MI_T("datetimeParam"), /* name */
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals, /* qualifiers */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_DatetimeMethod, datetimeParam), /* offset */
};

/* parameter MySimpleParamArrayQualsMethodsClass.DatetimeMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MySimpleParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySimpleParamArrayQualsMethodsClass_DatetimeMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_DatetimeMethod_params[] =
{
    &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_MIReturn_param,
    &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_datetimeParam_param,
};

/* method MySimpleParamArrayQualsMethodsClass.DatetimeMethod() */
MI_CONST MI_MethodDecl MySimpleParamArrayQualsMethodsClass_DatetimeMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0064640E, /* code */
    MI_T("DatetimeMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySimpleParamArrayQualsMethodsClass_DatetimeMethod_params, /* parameters */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_DatetimeMethod_params), /* numParameters */
    sizeof(MySimpleParamArrayQualsMethodsClass_DatetimeMethod), /* size */
    MI_DATETIME, /* returnType */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* origin */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySimpleParamArrayQualsMethodsClass_Invoke_DatetimeMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySimpleParamArrayQualsMethodsClass_meths[] =
{
    &MySimpleParamArrayQualsMethodsClass_BooleanMethod_rtti,
    &MySimpleParamArrayQualsMethodsClass_StringMethod_rtti,
    &MySimpleParamArrayQualsMethodsClass_Char16Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Uint8Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Sint8Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Uint16Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Sint16Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Uint32Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Sint32Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Uint64Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Sint64Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Real32Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_Real64Method_rtti,
    &MySimpleParamArrayQualsMethodsClass_DatetimeMethod_rtti,
};

static MI_CONST MI_ProviderFT MySimpleParamArrayQualsMethodsClass_funcs =
{
  (MI_ProviderFT_Load)MySimpleParamArrayQualsMethodsClass_Load,
  (MI_ProviderFT_Unload)MySimpleParamArrayQualsMethodsClass_Unload,
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

/* class MySimpleParamArrayQualsMethodsClass */
MI_CONST MI_ClassDecl MySimpleParamArrayQualsMethodsClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7323, /* code */
    MI_T("MySimpleParamArrayQualsMethodsClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MySimpleParamArrayQualsMethodsClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MySimpleParamArrayQualsMethodsClass_meths, /* methods */
    MI_COUNT(MySimpleParamArrayQualsMethodsClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySimpleParamArrayQualsMethodsClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyReferenceClass
**
**==============================================================================
*/

/* property MyReferenceClass.refProp */
static MI_CONST MI_PropertyDecl MyReferenceClass_refProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727007, /* code */
    MI_T("refProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MyEmbeddedPropertiesClass"), /* className */
    0, /* subscript */
    offsetof(MyReferenceClass, refProp), /* offset */
    MI_T("MyReferenceClass"), /* origin */
    MI_T("MyReferenceClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyReferenceClass_props[] =
{
    &MyReferenceClass_refProp_prop,
};

static MI_CONST MI_Boolean MyReferenceClass_GetReferenceValue_ReferenceVal_Out_qual_value = 1;

static MI_CONST MI_Qualifier MyReferenceClass_GetReferenceValue_ReferenceVal_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyReferenceClass_GetReferenceValue_ReferenceVal_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyReferenceClass_GetReferenceValue_ReferenceVal_quals[] =
{
    &MyReferenceClass_GetReferenceValue_ReferenceVal_Out_qual,
};

/* parameter MyReferenceClass.GetReferenceValue(): ReferenceVal */
static MI_CONST MI_ParameterDecl MyReferenceClass_GetReferenceValue_ReferenceVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00726C0C, /* code */
    MI_T("ReferenceVal"), /* name */
    MyReferenceClass_GetReferenceValue_ReferenceVal_quals, /* qualifiers */
    MI_COUNT(MyReferenceClass_GetReferenceValue_ReferenceVal_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MyEmbeddedPropertiesClass"), /* className */
    0, /* subscript */
    offsetof(MyReferenceClass_GetReferenceValue, ReferenceVal), /* offset */
};

/* parameter MyReferenceClass.GetReferenceValue(): MIReturn */
static MI_CONST MI_ParameterDecl MyReferenceClass_GetReferenceValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyReferenceClass_GetReferenceValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyReferenceClass_GetReferenceValue_params[] =
{
    &MyReferenceClass_GetReferenceValue_MIReturn_param,
    &MyReferenceClass_GetReferenceValue_ReferenceVal_param,
};

/* method MyReferenceClass.GetReferenceValue() */
MI_CONST MI_MethodDecl MyReferenceClass_GetReferenceValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676511, /* code */
    MI_T("GetReferenceValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyReferenceClass_GetReferenceValue_params, /* parameters */
    MI_COUNT(MyReferenceClass_GetReferenceValue_params), /* numParameters */
    sizeof(MyReferenceClass_GetReferenceValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyReferenceClass"), /* origin */
    MI_T("MyReferenceClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyReferenceClass_Invoke_GetReferenceValue, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyReferenceClass_meths[] =
{
    &MyReferenceClass_GetReferenceValue_rtti,
};

static MI_CONST MI_ProviderFT MyReferenceClass_funcs =
{
  (MI_ProviderFT_Load)MyReferenceClass_Load,
  (MI_ProviderFT_Unload)MyReferenceClass_Unload,
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

/* class MyReferenceClass */
MI_CONST MI_ClassDecl MyReferenceClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7310, /* code */
    MI_T("MyReferenceClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyReferenceClass_props, /* properties */
    MI_COUNT(MyReferenceClass_props), /* numProperties */
    sizeof(MyReferenceClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyReferenceClass_meths, /* methods */
    MI_COUNT(MyReferenceClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyReferenceClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyVariousArrayLengthClass
**
**==============================================================================
*/

/* property MyVariousArrayLengthClass.uninitializedValue */
static MI_CONST MI_PropertyDecl MyVariousArrayLengthClass_uninitializedValue_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756512, /* code */
    MI_T("uninitializedValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass, uninitializedValue), /* offset */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    NULL,
};

/* property MyVariousArrayLengthClass.booleanUninitializedArray */
static MI_CONST MI_PropertyDecl MyVariousArrayLengthClass_booleanUninitializedArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627919, /* code */
    MI_T("booleanUninitializedArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass, booleanUninitializedArray), /* offset */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    NULL,
};

/* property MyVariousArrayLengthClass.nullArray */
static MI_CONST MI_PropertyDecl MyVariousArrayLengthClass_nullArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7909, /* code */
    MI_T("nullArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass, nullArray), /* offset */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 MyVariousArrayLengthClass_uint32Array_data_value[] =
{
    10U,
};

static MI_CONST MI_ConstUint32A MyVariousArrayLengthClass_uint32Array_value =
{
    MyVariousArrayLengthClass_uint32Array_data_value,
    MI_COUNT(MyVariousArrayLengthClass_uint32Array_data_value),
};

/* property MyVariousArrayLengthClass.uint32Array */
static MI_CONST MI_PropertyDecl MyVariousArrayLengthClass_uint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790B, /* code */
    MI_T("uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass, uint32Array), /* offset */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    &MyVariousArrayLengthClass_uint32Array_value,
};

static MI_CONST MI_Sint32 MyVariousArrayLengthClass_sint32Array_data_value[] =
{
    9999,
    -9999,
};

static MI_CONST MI_ConstSint32A MyVariousArrayLengthClass_sint32Array_value =
{
    MyVariousArrayLengthClass_sint32Array_data_value,
    MI_COUNT(MyVariousArrayLengthClass_sint32Array_data_value),
};

/* property MyVariousArrayLengthClass.sint32Array */
static MI_CONST MI_PropertyDecl MyVariousArrayLengthClass_sint32Array_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073790B, /* code */
    MI_T("sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    2, /* subscript */
    offsetof(MyVariousArrayLengthClass, sint32Array), /* offset */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    &MyVariousArrayLengthClass_sint32Array_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyVariousArrayLengthClass_props[] =
{
    &MyVariousArrayLengthClass_uninitializedValue_prop,
    &MyVariousArrayLengthClass_booleanUninitializedArray_prop,
    &MyVariousArrayLengthClass_nullArray_prop,
    &MyVariousArrayLengthClass_uint32Array_prop,
    &MyVariousArrayLengthClass_sint32Array_prop,
};

/* parameter MyVariousArrayLengthClass.MethodWithArrayParam(): sint64ArrayParam */
static MI_CONST MI_ParameterDecl MyVariousArrayLengthClass_MethodWithArrayParam_sint64ArrayParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D10, /* code */
    MI_T("sint64ArrayParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass_MethodWithArrayParam, sint64ArrayParam), /* offset */
};

/* parameter MyVariousArrayLengthClass.MethodWithArrayParam(): MIReturn */
static MI_CONST MI_ParameterDecl MyVariousArrayLengthClass_MethodWithArrayParam_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass_MethodWithArrayParam, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyVariousArrayLengthClass_MethodWithArrayParam_params[] =
{
    &MyVariousArrayLengthClass_MethodWithArrayParam_MIReturn_param,
    &MyVariousArrayLengthClass_MethodWithArrayParam_sint64ArrayParam_param,
};

/* method MyVariousArrayLengthClass.MethodWithArrayParam() */
MI_CONST MI_MethodDecl MyVariousArrayLengthClass_MethodWithArrayParam_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6D14, /* code */
    MI_T("MethodWithArrayParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyVariousArrayLengthClass_MethodWithArrayParam_params, /* parameters */
    MI_COUNT(MyVariousArrayLengthClass_MethodWithArrayParam_params), /* numParameters */
    sizeof(MyVariousArrayLengthClass_MethodWithArrayParam), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyVariousArrayLengthClass_Invoke_MethodWithArrayParam, /* method */
};

/* parameter MyVariousArrayLengthClass.MethodWithFixedSizeArrayParam(): sint64ArrayParam */
static MI_CONST MI_ParameterDecl MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_sint64ArrayParam_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00736D10, /* code */
    MI_T("sint64ArrayParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    5, /* subscript */
    offsetof(MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam, sint64ArrayParam), /* offset */
};

/* parameter MyVariousArrayLengthClass.MethodWithFixedSizeArrayParam(): MIReturn */
static MI_CONST MI_ParameterDecl MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_params[] =
{
    &MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_MIReturn_param,
    &MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_sint64ArrayParam_param,
};

/* method MyVariousArrayLengthClass.MethodWithFixedSizeArrayParam() */
MI_CONST MI_MethodDecl MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6D1D, /* code */
    MI_T("MethodWithFixedSizeArrayParam"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_params, /* parameters */
    MI_COUNT(MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_params), /* numParameters */
    sizeof(MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyVariousArrayLengthClass"), /* origin */
    MI_T("MyVariousArrayLengthClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyVariousArrayLengthClass_Invoke_MethodWithFixedSizeArrayParam, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyVariousArrayLengthClass_meths[] =
{
    &MyVariousArrayLengthClass_MethodWithArrayParam_rtti,
    &MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam_rtti,
};

static MI_CONST MI_ProviderFT MyVariousArrayLengthClass_funcs =
{
  (MI_ProviderFT_Load)MyVariousArrayLengthClass_Load,
  (MI_ProviderFT_Unload)MyVariousArrayLengthClass_Unload,
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

/* class MyVariousArrayLengthClass */
MI_CONST MI_ClassDecl MyVariousArrayLengthClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7319, /* code */
    MI_T("MyVariousArrayLengthClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyVariousArrayLengthClass_props, /* properties */
    MI_COUNT(MyVariousArrayLengthClass_props), /* numProperties */
    sizeof(MyVariousArrayLengthClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyVariousArrayLengthClass_meths, /* methods */
    MI_COUNT(MyVariousArrayLengthClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyVariousArrayLengthClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyOptionTestClass
**
**==============================================================================
*/

static MI_CONST MI_Uint8 MyOptionTestClass_uint8Prop_value = 5;

/* property MyOptionTestClass.uint8Prop */
static MI_CONST MI_PropertyDecl MyOptionTestClass_uint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757009, /* code */
    MI_T("uint8Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass, uint8Prop), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &MyOptionTestClass_uint8Prop_value,
};

static MI_CONST MI_Uint64 MyOptionTestClass_uint64ArrayProp_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
};

static MI_CONST MI_ConstUint64A MyOptionTestClass_uint64ArrayProp_value =
{
    MyOptionTestClass_uint64ArrayProp_data_value,
    MI_COUNT(MyOptionTestClass_uint64ArrayProp_data_value),
};

/* property MyOptionTestClass.uint64ArrayProp */
static MI_CONST MI_PropertyDecl MyOptionTestClass_uint64ArrayProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075700F, /* code */
    MI_T("uint64ArrayProp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    3, /* subscript */
    offsetof(MyOptionTestClass, uint64ArrayProp), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &MyOptionTestClass_uint64ArrayProp_value,
};

static MI_CONST MI_Uint8 MyOptionTestClass_sint8PropWithSimpleQual_Uint8Qual_qual_value = 9;

static MI_CONST MI_Qualifier MyOptionTestClass_sint8PropWithSimpleQual_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_sint8PropWithSimpleQual_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_sint8PropWithSimpleQual_quals[] =
{
    &MyOptionTestClass_sint8PropWithSimpleQual_Uint8Qual_qual,
};

/* property MyOptionTestClass.sint8PropWithSimpleQual */
static MI_CONST MI_PropertyDecl MyOptionTestClass_sint8PropWithSimpleQual_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736C17, /* code */
    MI_T("sint8PropWithSimpleQual"), /* name */
    MyOptionTestClass_sint8PropWithSimpleQual_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_sint8PropWithSimpleQual_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass, sint8PropWithSimpleQual), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    NULL,
};

static MI_CONST MI_Sint64 MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(999),
    -MI_LL(45),
    MI_LL(0),
    MI_LL(6),
};

static MI_CONST MI_ConstSint64A MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_value =
{
    MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_uint32PropWithArrayQual_quals[] =
{
    &MyOptionTestClass_uint32PropWithArrayQual_Sint64ArrayQual_qual,
};

/* property MyOptionTestClass.uint32PropWithArrayQual */
static MI_CONST MI_PropertyDecl MyOptionTestClass_uint32PropWithArrayQual_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756C17, /* code */
    MI_T("uint32PropWithArrayQual"), /* name */
    MyOptionTestClass_uint32PropWithArrayQual_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_uint32PropWithArrayQual_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass, uint32PropWithArrayQual), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyOptionTestClass_props[] =
{
    &MyOptionTestClass_uint8Prop_prop,
    &MyOptionTestClass_uint64ArrayProp_prop,
    &MyOptionTestClass_sint8PropWithSimpleQual_prop,
    &MyOptionTestClass_uint32PropWithArrayQual_prop,
};

/* parameter MyOptionTestClass.Uint32EmptyParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestClass_Uint32EmptyParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_Uint32EmptyParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestClass_Uint32EmptyParamMethod_params[] =
{
    &MyOptionTestClass_Uint32EmptyParamMethod_MIReturn_param,
};

/* method MyOptionTestClass.Uint32EmptyParamMethod() */
MI_CONST MI_MethodDecl MyOptionTestClass_Uint32EmptyParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756416, /* code */
    MI_T("Uint32EmptyParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyOptionTestClass_Uint32EmptyParamMethod_params, /* parameters */
    MI_COUNT(MyOptionTestClass_Uint32EmptyParamMethod_params), /* numParameters */
    sizeof(MyOptionTestClass_Uint32EmptyParamMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestClass_Invoke_Uint32EmptyParamMethod, /* method */
};

static MI_CONST MI_Boolean MyOptionTestClass_Sint64SimpleParamsMethod_param1_In_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_Sint64SimpleParamsMethod_param1_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param1_In_qual_value
};

static MI_CONST MI_Boolean MyOptionTestClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_Sint64SimpleParamsMethod_param1_quals[] =
{
    &MyOptionTestClass_Sint64SimpleParamsMethod_param1_In_qual,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual,
};

/* parameter MyOptionTestClass.Sint64SimpleParamsMethod(): param1 */
static MI_CONST MI_ParameterDecl MyOptionTestClass_Sint64SimpleParamsMethod_param1_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00703106, /* code */
    MI_T("param1"), /* name */
    MyOptionTestClass_Sint64SimpleParamsMethod_param1_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_Sint64SimpleParamsMethod_param1_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_Sint64SimpleParamsMethod, param1), /* offset */
};

static MI_CONST MI_Boolean MyOptionTestClass_Sint64SimpleParamsMethod_param2_Out_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_Sint64SimpleParamsMethod_param2_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param2_Out_qual_value
};

static MI_CONST MI_Char* MyOptionTestClass_Sint64SimpleParamsMethod_param2_StringQual_qual_value = MI_T("");

static MI_CONST MI_Qualifier MyOptionTestClass_Sint64SimpleParamsMethod_param2_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param2_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_Sint64SimpleParamsMethod_param2_quals[] =
{
    &MyOptionTestClass_Sint64SimpleParamsMethod_param2_Out_qual,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param2_StringQual_qual,
};

/* parameter MyOptionTestClass.Sint64SimpleParamsMethod(): param2 */
static MI_CONST MI_ParameterDecl MyOptionTestClass_Sint64SimpleParamsMethod_param2_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00703206, /* code */
    MI_T("param2"), /* name */
    MyOptionTestClass_Sint64SimpleParamsMethod_param2_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_Sint64SimpleParamsMethod_param2_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_Sint64SimpleParamsMethod, param2), /* offset */
};

/* parameter MyOptionTestClass.Sint64SimpleParamsMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestClass_Sint64SimpleParamsMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_Sint64SimpleParamsMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestClass_Sint64SimpleParamsMethod_params[] =
{
    &MyOptionTestClass_Sint64SimpleParamsMethod_MIReturn_param,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param1_param,
    &MyOptionTestClass_Sint64SimpleParamsMethod_param2_param,
};

/* method MyOptionTestClass.Sint64SimpleParamsMethod() */
MI_CONST MI_MethodDecl MyOptionTestClass_Sint64SimpleParamsMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736418, /* code */
    MI_T("Sint64SimpleParamsMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyOptionTestClass_Sint64SimpleParamsMethod_params, /* parameters */
    MI_COUNT(MyOptionTestClass_Sint64SimpleParamsMethod_params), /* numParameters */
    sizeof(MyOptionTestClass_Sint64SimpleParamsMethod), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestClass_Invoke_Sint64SimpleParamsMethod, /* method */
};

static MI_CONST MI_Char* MyOptionTestClass_MultiQualMethod_StringQual_qual_value = MI_T("~!@#$%^&*()-_=+'\";:.>,</?welcome\\&'><\"");

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_MultiQualMethod_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
};

static MI_CONST MI_ConstUint64A MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual_value =
{
    MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_MultiQualMethod_quals[] =
{
    &MyOptionTestClass_MultiQualMethod_StringQual_qual,
    &MyOptionTestClass_MultiQualMethod_Uint64ArrayQual_qual,
};

static MI_CONST MI_Boolean MyOptionTestClass_MultiQualMethod_inputParam_In_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_inputParam_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestClass_MultiQualMethod_inputParam_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_MultiQualMethod_inputParam_quals[] =
{
    &MyOptionTestClass_MultiQualMethod_inputParam_In_qual,
};

/* parameter MyOptionTestClass.MultiQualMethod(): inputParam */
static MI_CONST MI_ParameterDecl MyOptionTestClass_MultiQualMethod_inputParam_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00696D0A, /* code */
    MI_T("inputParam"), /* name */
    MyOptionTestClass_MultiQualMethod_inputParam_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_MultiQualMethod_inputParam_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_MultiQualMethod, inputParam), /* offset */
};

static MI_CONST MI_Boolean MyOptionTestClass_MultiQualMethod_outputParam_Out_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_outputParam_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestClass_MultiQualMethod_outputParam_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_MultiQualMethod_outputParam_quals[] =
{
    &MyOptionTestClass_MultiQualMethod_outputParam_Out_qual,
};

/* parameter MyOptionTestClass.MultiQualMethod(): outputParam */
static MI_CONST MI_ParameterDecl MyOptionTestClass_MultiQualMethod_outputParam_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6D0B, /* code */
    MI_T("outputParam"), /* name */
    MyOptionTestClass_MultiQualMethod_outputParam_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_MultiQualMethod_outputParam_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_MultiQualMethod, outputParam), /* offset */
};

static MI_CONST MI_Char* MyOptionTestClass_MultiQualMethod_MIReturn_StringQual_qual_value = MI_T("~!@#$%^&*()-_=+'\";:.>,</?welcome\\&'><\"");

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_MIReturn_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_MultiQualMethod_MIReturn_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
};

static MI_CONST MI_ConstUint64A MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_value =
{
    MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_MultiQualMethod_MIReturn_quals[] =
{
    &MyOptionTestClass_MultiQualMethod_MIReturn_StringQual_qual,
    &MyOptionTestClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual,
};

/* parameter MyOptionTestClass.MultiQualMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestClass_MultiQualMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyOptionTestClass_MultiQualMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_MultiQualMethod_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestClass_MultiQualMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestClass_MultiQualMethod_params[] =
{
    &MyOptionTestClass_MultiQualMethod_MIReturn_param,
    &MyOptionTestClass_MultiQualMethod_inputParam_param,
    &MyOptionTestClass_MultiQualMethod_outputParam_param,
};

/* method MyOptionTestClass.MultiQualMethod() */
MI_CONST MI_MethodDecl MyOptionTestClass_MultiQualMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D640F, /* code */
    MI_T("MultiQualMethod"), /* name */
    MyOptionTestClass_MultiQualMethod_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_MultiQualMethod_quals), /* numQualifiers */
    MyOptionTestClass_MultiQualMethod_params, /* parameters */
    MI_COUNT(MyOptionTestClass_MultiQualMethod_params), /* numParameters */
    sizeof(MyOptionTestClass_MultiQualMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestClass_Invoke_MultiQualMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyOptionTestClass_meths[] =
{
    &MyOptionTestClass_Uint32EmptyParamMethod_rtti,
    &MyOptionTestClass_Sint64SimpleParamsMethod_rtti,
    &MyOptionTestClass_MultiQualMethod_rtti,
};

static MI_CONST MI_ProviderFT MyOptionTestClass_funcs =
{
  (MI_ProviderFT_Load)MyOptionTestClass_Load,
  (MI_ProviderFT_Unload)MyOptionTestClass_Unload,
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

static MI_CONST MI_Boolean MyOptionTestClass_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestClass_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_BooleanQual_qual_value
};

static MI_CONST MI_Char* MyOptionTestClass_StringQual_qual_value = MI_T("hello&'><\"");

static MI_CONST MI_Qualifier MyOptionTestClass_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestClass_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyOptionTestClass_Uint64ArrayQual_qual_value =
{
    MyOptionTestClass_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestClass_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestClass_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_Uint64ArrayQual_qual_value
};

static MI_CONST MI_Sint64 MyOptionTestClass_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyOptionTestClass_Sint64ArrayQual_qual_value =
{
    MyOptionTestClass_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestClass_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestClass_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestClass_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestClass_quals[] =
{
    &MyOptionTestClass_BooleanQual_qual,
    &MyOptionTestClass_StringQual_qual,
    &MyOptionTestClass_Uint64ArrayQual_qual,
    &MyOptionTestClass_Sint64ArrayQual_qual,
};

/* class MyOptionTestClass */
MI_CONST MI_ClassDecl MyOptionTestClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7311, /* code */
    MI_T("MyOptionTestClass"), /* name */
    MyOptionTestClass_quals, /* qualifiers */
    MI_COUNT(MyOptionTestClass_quals), /* numQualifiers */
    MyOptionTestClass_props, /* properties */
    MI_COUNT(MyOptionTestClass_props), /* numProperties */
    sizeof(MyOptionTestClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyOptionTestClass_meths, /* methods */
    MI_COUNT(MyOptionTestClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyOptionTestClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyOptionTestDerivedClass
**
**==============================================================================
*/

static MI_CONST MI_Uint8 MyOptionTestDerivedClass_uint8Prop_value = 10;

/* property MyOptionTestDerivedClass.uint8Prop */
static MI_CONST MI_PropertyDecl MyOptionTestDerivedClass_uint8Prop_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757009, /* code */
    MI_T("uint8Prop"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass, uint8Prop), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    &MyOptionTestDerivedClass_uint8Prop_value,
};

static MI_CONST MI_Sint64 MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(111),
    -MI_LL(45),
    MI_LL(0),
    MI_LL(5),
};

static MI_CONST MI_ConstSint64A MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_uint32PropWithArrayQual_quals[] =
{
    &MyOptionTestDerivedClass_uint32PropWithArrayQual_Sint64ArrayQual_qual,
};

/* property MyOptionTestDerivedClass.uint32PropWithArrayQual */
static MI_CONST MI_PropertyDecl MyOptionTestDerivedClass_uint32PropWithArrayQual_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756C17, /* code */
    MI_T("uint32PropWithArrayQual"), /* name */
    MyOptionTestDerivedClass_uint32PropWithArrayQual_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_uint32PropWithArrayQual_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass, uint32PropWithArrayQual), /* offset */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint8 MyOptionTestDerivedClass_uint8Property_value = 7;

/* property MyOptionTestDerivedClass.uint8Property */
static MI_CONST MI_PropertyDecl MyOptionTestDerivedClass_uint8Property_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075790D, /* code */
    MI_T("uint8Property"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass, uint8Property), /* offset */
    MI_T("MyOptionTestDerivedClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    &MyOptionTestDerivedClass_uint8Property_value,
};

static MI_CONST MI_Uint64 MyOptionTestDerivedClass_uint64ArrayProperty_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
    MI_ULL(4),
    MI_ULL(5),
};

static MI_CONST MI_ConstUint64A MyOptionTestDerivedClass_uint64ArrayProperty_value =
{
    MyOptionTestDerivedClass_uint64ArrayProperty_data_value,
    MI_COUNT(MyOptionTestDerivedClass_uint64ArrayProperty_data_value),
};

/* property MyOptionTestDerivedClass.uint64ArrayProperty */
static MI_CONST MI_PropertyDecl MyOptionTestDerivedClass_uint64ArrayProperty_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757913, /* code */
    MI_T("uint64ArrayProperty"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    5, /* subscript */
    offsetof(MyOptionTestDerivedClass, uint64ArrayProperty), /* offset */
    MI_T("MyOptionTestDerivedClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    &MyOptionTestDerivedClass_uint64ArrayProperty_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_props[] =
{
    &MyOptionTestDerivedClass_uint8Prop_prop,
    &MyOptionTestClass_uint64ArrayProp_prop,
    &MyOptionTestClass_sint8PropWithSimpleQual_prop,
    &MyOptionTestDerivedClass_uint32PropWithArrayQual_prop,
    &MyOptionTestDerivedClass_uint8Property_prop,
    &MyOptionTestDerivedClass_uint64ArrayProperty_prop,
};

/* parameter MyOptionTestDerivedClass.Uint32EmptyParamMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_Uint32EmptyParamMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_Uint32EmptyParamMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_Uint32EmptyParamMethod_params[] =
{
    &MyOptionTestDerivedClass_Uint32EmptyParamMethod_MIReturn_param,
};

/* method MyOptionTestDerivedClass.Uint32EmptyParamMethod() */
MI_CONST MI_MethodDecl MyOptionTestDerivedClass_Uint32EmptyParamMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00756416, /* code */
    MI_T("Uint32EmptyParamMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyOptionTestDerivedClass_Uint32EmptyParamMethod_params, /* parameters */
    MI_COUNT(MyOptionTestDerivedClass_Uint32EmptyParamMethod_params), /* numParameters */
    sizeof(MyOptionTestDerivedClass_Uint32EmptyParamMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestDerivedClass_Invoke_Uint32EmptyParamMethod, /* method */
};

static MI_CONST MI_Boolean MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_In_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_In_qual_value
};

static MI_CONST MI_Boolean MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_quals[] =
{
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_In_qual,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_BooleanQual_qual,
};

/* parameter MyOptionTestDerivedClass.Sint64SimpleParamsMethod(): param1 */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00703106, /* code */
    MI_T("param1"), /* name */
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_Sint64SimpleParamsMethod, param1), /* offset */
};

static MI_CONST MI_Boolean MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_Out_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_Out_qual_value
};

static MI_CONST MI_Char* MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_StringQual_qual_value = MI_T("");

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_StringQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_quals[] =
{
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_Out_qual,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_StringQual_qual,
};

/* parameter MyOptionTestDerivedClass.Sint64SimpleParamsMethod(): param2 */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00703206, /* code */
    MI_T("param2"), /* name */
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_quals), /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_Sint64SimpleParamsMethod, param2), /* offset */
};

/* parameter MyOptionTestDerivedClass.Sint64SimpleParamsMethod(): param3 */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param3_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00703306, /* code */
    MI_T("param3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_Sint64SimpleParamsMethod, param3), /* offset */
};

/* parameter MyOptionTestDerivedClass.Sint64SimpleParamsMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_Sint64SimpleParamsMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_Sint64SimpleParamsMethod_params[] =
{
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_MIReturn_param,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param1_param,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param2_param,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_param3_param,
};

/* method MyOptionTestDerivedClass.Sint64SimpleParamsMethod() */
MI_CONST MI_MethodDecl MyOptionTestDerivedClass_Sint64SimpleParamsMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736418, /* code */
    MI_T("Sint64SimpleParamsMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyOptionTestDerivedClass_Sint64SimpleParamsMethod_params, /* parameters */
    MI_COUNT(MyOptionTestDerivedClass_Sint64SimpleParamsMethod_params), /* numParameters */
    sizeof(MyOptionTestDerivedClass_Sint64SimpleParamsMethod), /* size */
    MI_SINT64, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestDerivedClass_Invoke_Sint64SimpleParamsMethod, /* method */
};

static MI_CONST MI_Char* MyOptionTestDerivedClass_MultiQualMethod_StringQual_qual_value = MI_T("~!@#$%^&*()-_=+'\";:.>,</?welcome\\&'><\"");

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_MultiQualMethod_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
};

static MI_CONST MI_ConstUint64A MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_MultiQualMethod_quals[] =
{
    &MyOptionTestDerivedClass_MultiQualMethod_StringQual_qual,
    &MyOptionTestDerivedClass_MultiQualMethod_Uint64ArrayQual_qual,
};

static MI_CONST MI_Boolean MyOptionTestDerivedClass_MultiQualMethod_inputParam_In_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_inputParam_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestDerivedClass_MultiQualMethod_inputParam_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_MultiQualMethod_inputParam_quals[] =
{
    &MyOptionTestDerivedClass_MultiQualMethod_inputParam_In_qual,
};

/* parameter MyOptionTestDerivedClass.MultiQualMethod(): inputParam */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_MultiQualMethod_inputParam_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00696D0A, /* code */
    MI_T("inputParam"), /* name */
    MyOptionTestDerivedClass_MultiQualMethod_inputParam_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_inputParam_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_MultiQualMethod, inputParam), /* offset */
};

static MI_CONST MI_Boolean MyOptionTestDerivedClass_MultiQualMethod_outputParam_Out_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_outputParam_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MyOptionTestDerivedClass_MultiQualMethod_outputParam_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_MultiQualMethod_outputParam_quals[] =
{
    &MyOptionTestDerivedClass_MultiQualMethod_outputParam_Out_qual,
};

/* parameter MyOptionTestDerivedClass.MultiQualMethod(): outputParam */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_MultiQualMethod_outputParam_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6D0B, /* code */
    MI_T("outputParam"), /* name */
    MyOptionTestDerivedClass_MultiQualMethod_outputParam_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_outputParam_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_MultiQualMethod, outputParam), /* offset */
};

static MI_CONST MI_Char* MyOptionTestDerivedClass_MultiQualMethod_MIReturn_StringQual_qual_value = MI_T("~!@#$%^&*()-_=+'\";:.>,</?welcome\\&'><\"");

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_MIReturn_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_MultiQualMethod_MIReturn_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(1),
    MI_ULL(2),
    MI_ULL(3),
};

static MI_CONST MI_ConstUint64A MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_MultiQualMethod_MIReturn_quals[] =
{
    &MyOptionTestDerivedClass_MultiQualMethod_MIReturn_StringQual_qual,
    &MyOptionTestDerivedClass_MultiQualMethod_MIReturn_Uint64ArrayQual_qual,
};

/* parameter MyOptionTestDerivedClass.MultiQualMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_MultiQualMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyOptionTestDerivedClass_MultiQualMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_MultiQualMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_MultiQualMethod_params[] =
{
    &MyOptionTestDerivedClass_MultiQualMethod_MIReturn_param,
    &MyOptionTestDerivedClass_MultiQualMethod_inputParam_param,
    &MyOptionTestDerivedClass_MultiQualMethod_outputParam_param,
};

/* method MyOptionTestDerivedClass.MultiQualMethod() */
MI_CONST MI_MethodDecl MyOptionTestDerivedClass_MultiQualMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D640F, /* code */
    MI_T("MultiQualMethod"), /* name */
    MyOptionTestDerivedClass_MultiQualMethod_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_quals), /* numQualifiers */
    MyOptionTestDerivedClass_MultiQualMethod_params, /* parameters */
    MI_COUNT(MyOptionTestDerivedClass_MultiQualMethod_params), /* numParameters */
    sizeof(MyOptionTestDerivedClass_MultiQualMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyOptionTestClass"), /* origin */
    MI_T("MyOptionTestClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestDerivedClass_Invoke_MultiQualMethod, /* method */
};

/* parameter MyOptionTestDerivedClass.MyMethod(): input */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_MyMethod_input_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00697405, /* code */
    MI_T("input"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_MyMethod, input), /* offset */
};

/* parameter MyOptionTestDerivedClass.MyMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyOptionTestDerivedClass_MyMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyOptionTestDerivedClass_MyMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_MyMethod_params[] =
{
    &MyOptionTestDerivedClass_MyMethod_MIReturn_param,
    &MyOptionTestDerivedClass_MyMethod_input_param,
};

/* method MyOptionTestDerivedClass.MyMethod() */
MI_CONST MI_MethodDecl MyOptionTestDerivedClass_MyMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6408, /* code */
    MI_T("MyMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyOptionTestDerivedClass_MyMethod_params, /* parameters */
    MI_COUNT(MyOptionTestDerivedClass_MyMethod_params), /* numParameters */
    sizeof(MyOptionTestDerivedClass_MyMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyOptionTestDerivedClass"), /* origin */
    MI_T("MyOptionTestDerivedClass"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyOptionTestDerivedClass_Invoke_MyMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyOptionTestDerivedClass_meths[] =
{
    &MyOptionTestDerivedClass_Uint32EmptyParamMethod_rtti,
    &MyOptionTestDerivedClass_Sint64SimpleParamsMethod_rtti,
    &MyOptionTestDerivedClass_MultiQualMethod_rtti,
    &MyOptionTestDerivedClass_MyMethod_rtti,
};

static MI_CONST MI_ProviderFT MyOptionTestDerivedClass_funcs =
{
  (MI_ProviderFT_Load)MyOptionTestDerivedClass_Load,
  (MI_ProviderFT_Unload)MyOptionTestDerivedClass_Unload,
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

static MI_CONST MI_Boolean MyOptionTestDerivedClass_BooleanQual_qual_value = 1;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_BooleanQual_qual =
{
    MI_T("BooleanQual"),
    MI_BOOLEAN,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_BooleanQual_qual_value
};

static MI_CONST MI_Char* MyOptionTestDerivedClass_StringQual_qual_value = MI_T("hello&'><\"");

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_StringQual_qual =
{
    MI_T("StringQual"),
    MI_STRING,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_StringQual_qual_value
};

static MI_CONST MI_Uint64 MyOptionTestDerivedClass_Uint64ArrayQual_qual_data_value[] =
{
    MI_ULL(4),
    MI_ULL(40),
};

static MI_CONST MI_ConstUint64A MyOptionTestDerivedClass_Uint64ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_Uint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_Uint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Uint64ArrayQual_qual =
{
    MI_T("Uint64ArrayQual"),
    MI_UINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Uint64ArrayQual_qual_value
};

static MI_CONST MI_Sint64 MyOptionTestDerivedClass_Sint64ArrayQual_qual_data_value[] =
{
    -MI_LL(4),
    MI_LL(4),
};

static MI_CONST MI_ConstSint64A MyOptionTestDerivedClass_Sint64ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_Sint64ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_Sint64ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Sint64ArrayQual_qual =
{
    MI_T("Sint64ArrayQual"),
    MI_SINT64A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Sint64ArrayQual_qual_value
};

static MI_CONST MI_Uint32 MyOptionTestDerivedClass_Uint32Qual_qual_value = 9U;

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Uint32Qual_qual_value
};

static MI_CONST MI_Uint32 MyOptionTestDerivedClass_Uint32ArrayQual_qual_data_value[] =
{
    9U,
    10U,
    11U,
};

static MI_CONST MI_ConstUint32A MyOptionTestDerivedClass_Uint32ArrayQual_qual_value =
{
    MyOptionTestDerivedClass_Uint32ArrayQual_qual_data_value,
    MI_COUNT(MyOptionTestDerivedClass_Uint32ArrayQual_qual_data_value),
};

static MI_CONST MI_Qualifier MyOptionTestDerivedClass_Uint32ArrayQual_qual =
{
    MI_T("Uint32ArrayQual"),
    MI_UINT32A,
    MI_FLAG_TRANSLATABLE,
    &MyOptionTestDerivedClass_Uint32ArrayQual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyOptionTestDerivedClass_quals[] =
{
    &MyOptionTestDerivedClass_BooleanQual_qual,
    &MyOptionTestDerivedClass_StringQual_qual,
    &MyOptionTestDerivedClass_Uint64ArrayQual_qual,
    &MyOptionTestDerivedClass_Sint64ArrayQual_qual,
    &MyOptionTestDerivedClass_Uint32Qual_qual,
    &MyOptionTestDerivedClass_Uint32ArrayQual_qual,
};

/* class MyOptionTestDerivedClass */
MI_CONST MI_ClassDecl MyOptionTestDerivedClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7318, /* code */
    MI_T("MyOptionTestDerivedClass"), /* name */
    MyOptionTestDerivedClass_quals, /* qualifiers */
    MI_COUNT(MyOptionTestDerivedClass_quals), /* numQualifiers */
    MyOptionTestDerivedClass_props, /* properties */
    MI_COUNT(MyOptionTestDerivedClass_props), /* numProperties */
    sizeof(MyOptionTestDerivedClass), /* size */
    MI_T("MyOptionTestClass"), /* superClass */
    &MyOptionTestClass_rtti, /* superClassDecl */
    MyOptionTestDerivedClass_meths, /* methods */
    MI_COUNT(MyOptionTestDerivedClass_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyOptionTestDerivedClass_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyClassForTestingAddedEmbeddedQualifier
**
**==============================================================================
*/

/* property MyClassForTestingAddedEmbeddedQualifier.v_embeddedObject */
static MI_CONST MI_PropertyDecl MyClassForTestingAddedEmbeddedQualifier_v_embeddedObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00767410, /* code */
    MI_T("v_embeddedObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyClassForTestingAddedEmbeddedQualifier, v_embeddedObject), /* offset */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* origin */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* propagator */
    NULL,
};

/* property MyClassForTestingAddedEmbeddedQualifier.v_embeddedInstance */
static MI_CONST MI_PropertyDecl MyClassForTestingAddedEmbeddedQualifier_v_embeddedInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766512, /* code */
    MI_T("v_embeddedInstance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MySimplePropertiesClass"), /* className */
    0, /* subscript */
    offsetof(MyClassForTestingAddedEmbeddedQualifier, v_embeddedInstance), /* offset */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* origin */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* propagator */
    NULL,
};

/* property MyClassForTestingAddedEmbeddedQualifier.a_embeddedObject */
static MI_CONST MI_PropertyDecl MyClassForTestingAddedEmbeddedQualifier_a_embeddedObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617410, /* code */
    MI_T("a_embeddedObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyClassForTestingAddedEmbeddedQualifier, a_embeddedObject), /* offset */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* origin */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* propagator */
    NULL,
};

/* property MyClassForTestingAddedEmbeddedQualifier.a_embeddedInstance */
static MI_CONST MI_PropertyDecl MyClassForTestingAddedEmbeddedQualifier_a_embeddedInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616512, /* code */
    MI_T("a_embeddedInstance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MySimplePropertiesClass"), /* className */
    0, /* subscript */
    offsetof(MyClassForTestingAddedEmbeddedQualifier, a_embeddedInstance), /* offset */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* origin */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyClassForTestingAddedEmbeddedQualifier_props[] =
{
    &MyClassForTestingAddedEmbeddedQualifier_v_embeddedObject_prop,
    &MyClassForTestingAddedEmbeddedQualifier_v_embeddedInstance_prop,
    &MyClassForTestingAddedEmbeddedQualifier_a_embeddedObject_prop,
    &MyClassForTestingAddedEmbeddedQualifier_a_embeddedInstance_prop,
};

static MI_CONST MI_ProviderFT MyClassForTestingAddedEmbeddedQualifier_funcs =
{
  (MI_ProviderFT_Load)MyClassForTestingAddedEmbeddedQualifier_Load,
  (MI_ProviderFT_Unload)MyClassForTestingAddedEmbeddedQualifier_Unload,
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

/* class MyClassForTestingAddedEmbeddedQualifier */
MI_CONST MI_ClassDecl MyClassForTestingAddedEmbeddedQualifier_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7227, /* code */
    MI_T("MyClassForTestingAddedEmbeddedQualifier"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyClassForTestingAddedEmbeddedQualifier_props, /* properties */
    MI_COUNT(MyClassForTestingAddedEmbeddedQualifier_props), /* numProperties */
    sizeof(MyClassForTestingAddedEmbeddedQualifier), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MyClassForTestingAddedEmbeddedQualifier_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyClassRestrictedQualsOnBaseElements
**
**==============================================================================
*/

static MI_CONST MI_Char* MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual_data_value[] =
{
    MI_T("No Value"),
};

static MI_CONST MI_ConstStringA MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual_value =
{
    MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual_data_value,
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual_value
};

static MI_CONST MI_Uint8 MyClassRestrictedQualsOnBaseElements_myProp_Uint8Qual_qual_value = 10;

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myProp_Uint8Qual_qual =
{
    MI_T("Uint8Qual"),
    MI_UINT8,
    MI_FLAG_TRANSLATABLE,
    &MyClassRestrictedQualsOnBaseElements_myProp_Uint8Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_myProp_quals[] =
{
    &MyClassRestrictedQualsOnBaseElements_myProp_Deprecated_qual,
    &MyClassRestrictedQualsOnBaseElements_myProp_Uint8Qual_qual,
};

/* property MyClassRestrictedQualsOnBaseElements.myProp */
static MI_CONST MI_PropertyDecl MyClassRestrictedQualsOnBaseElements_myProp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D7006, /* code */
    MI_T("myProp"), /* name */
    MyClassRestrictedQualsOnBaseElements_myProp_quals, /* qualifiers */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myProp_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyClassRestrictedQualsOnBaseElements, myProp), /* offset */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* origin */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_props[] =
{
    &MyClassRestrictedQualsOnBaseElements_myProp_prop,
};

static MI_CONST MI_Char* MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value[] =
{
    MI_T("My value"),
};

static MI_CONST MI_ConstStringA MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_value =
{
    MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value,
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_value
};

static MI_CONST MI_Uint32 MyClassRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual_value = 11U;

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyClassRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_myMethod_quals[] =
{
    &MyClassRestrictedQualsOnBaseElements_myMethod_Deprecated_qual,
    &MyClassRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual,
};

static MI_CONST MI_Char* MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("My value"),
};

static MI_CONST MI_ConstStringA MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_value =
{
    MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_value
};

static MI_CONST MI_Uint32 MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual_value = 11U;

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_quals[] =
{
    &MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual,
    &MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual,
};

/* parameter MyClassRestrictedQualsOnBaseElements.myMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyClassRestrictedQualsOnBaseElements_myMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_myMethod_params[] =
{
    &MyClassRestrictedQualsOnBaseElements_myMethod_MIReturn_param,
};

/* method MyClassRestrictedQualsOnBaseElements.myMethod() */
MI_CONST MI_MethodDecl MyClassRestrictedQualsOnBaseElements_myMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6408, /* code */
    MI_T("myMethod"), /* name */
    MyClassRestrictedQualsOnBaseElements_myMethod_quals, /* qualifiers */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myMethod_quals), /* numQualifiers */
    MyClassRestrictedQualsOnBaseElements_myMethod_params, /* parameters */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_myMethod_params), /* numParameters */
    sizeof(MyClassRestrictedQualsOnBaseElements_myMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* origin */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyClassRestrictedQualsOnBaseElements_Invoke_myMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_meths[] =
{
    &MyClassRestrictedQualsOnBaseElements_myMethod_rtti,
};

static MI_CONST MI_ProviderFT MyClassRestrictedQualsOnBaseElements_funcs =
{
  (MI_ProviderFT_Load)MyClassRestrictedQualsOnBaseElements_Load,
  (MI_ProviderFT_Unload)MyClassRestrictedQualsOnBaseElements_Unload,
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

static MI_CONST MI_Char* MyClassRestrictedQualsOnBaseElements_Deprecated_qual_data_value[] =
{
    MI_T("No Value"),
};

static MI_CONST MI_ConstStringA MyClassRestrictedQualsOnBaseElements_Deprecated_qual_value =
{
    MyClassRestrictedQualsOnBaseElements_Deprecated_qual_data_value,
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyClassRestrictedQualsOnBaseElements_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyClassRestrictedQualsOnBaseElements_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyClassRestrictedQualsOnBaseElements_quals[] =
{
    &MyClassRestrictedQualsOnBaseElements_Deprecated_qual,
};

/* class MyClassRestrictedQualsOnBaseElements */
MI_CONST MI_ClassDecl MyClassRestrictedQualsOnBaseElements_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7324, /* code */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* name */
    MyClassRestrictedQualsOnBaseElements_quals, /* qualifiers */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_quals), /* numQualifiers */
    MyClassRestrictedQualsOnBaseElements_props, /* properties */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_props), /* numProperties */
    sizeof(MyClassRestrictedQualsOnBaseElements), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MyClassRestrictedQualsOnBaseElements_meths, /* methods */
    MI_COUNT(MyClassRestrictedQualsOnBaseElements_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyClassRestrictedQualsOnBaseElements_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MyDerivedClassOfRestrictedQualsOnBaseElements
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements_props[] =
{
    &MyClassRestrictedQualsOnBaseElements_myProp_prop,
};

static MI_CONST MI_Char* MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value[] =
{
    MI_T("My value"),
};

static MI_CONST MI_ConstStringA MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_value =
{
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value,
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual_value
};

static MI_CONST MI_Uint32 MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual_value = 11U;

static MI_CONST MI_Qualifier MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_quals[] =
{
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Deprecated_qual,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_Uint32Qual_qual,
};

static MI_CONST MI_Char* MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("My value"),
};

static MI_CONST MI_ConstStringA MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_value =
{
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual_value
};

static MI_CONST MI_Uint32 MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual_value = 11U;

static MI_CONST MI_Qualifier MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual =
{
    MI_T("Uint32Qual"),
    MI_UINT32,
    MI_FLAG_TRANSLATABLE,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_quals[] =
{
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Deprecated_qual,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_Uint32Qual_qual,
};

/* parameter MyDerivedClassOfRestrictedQualsOnBaseElements.myMethod(): MIReturn */
static MI_CONST MI_ParameterDecl MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_quals, /* qualifiers */
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_params[] =
{
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_MIReturn_param,
};

/* method MyDerivedClassOfRestrictedQualsOnBaseElements.myMethod() */
MI_CONST MI_MethodDecl MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6408, /* code */
    MI_T("myMethod"), /* name */
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_quals, /* qualifiers */
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_quals), /* numQualifiers */
    MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_params, /* parameters */
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_params), /* numParameters */
    sizeof(MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* origin */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MyDerivedClassOfRestrictedQualsOnBaseElements_Invoke_myMethod, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MyDerivedClassOfRestrictedQualsOnBaseElements_meths[] =
{
    &MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod_rtti,
};

static MI_CONST MI_ProviderFT MyDerivedClassOfRestrictedQualsOnBaseElements_funcs =
{
  (MI_ProviderFT_Load)MyDerivedClassOfRestrictedQualsOnBaseElements_Load,
  (MI_ProviderFT_Unload)MyDerivedClassOfRestrictedQualsOnBaseElements_Unload,
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

/* class MyDerivedClassOfRestrictedQualsOnBaseElements */
MI_CONST MI_ClassDecl MyDerivedClassOfRestrictedQualsOnBaseElements_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D732D, /* code */
    MI_T("MyDerivedClassOfRestrictedQualsOnBaseElements"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyDerivedClassOfRestrictedQualsOnBaseElements_props, /* properties */
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_props), /* numProperties */
    sizeof(MyDerivedClassOfRestrictedQualsOnBaseElements), /* size */
    MI_T("MyClassRestrictedQualsOnBaseElements"), /* superClass */
    &MyClassRestrictedQualsOnBaseElements_rtti, /* superClassDecl */
    MyDerivedClassOfRestrictedQualsOnBaseElements_meths, /* methods */
    MI_COUNT(MyDerivedClassOfRestrictedQualsOnBaseElements_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MyDerivedClassOfRestrictedQualsOnBaseElements_funcs, /* functions */
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
    &MyArrayParamArrayQualsMethodsClass_rtti,
    &MyArrayParamMethodsClass_rtti,
    &MyArrayParamSimpleQualsMethodsClass_rtti,
    &MyArrayPropertiesArrayQualsClass_rtti,
    &MyArrayPropertiesClass_rtti,
    &MyArrayPropertiesSimpleQualsClass_rtti,
    &MyArrayQualClass_rtti,
    &MyClassForTestingAddedEmbeddedQualifier_rtti,
    &MyClassRestrictedQualsOnBaseElements_rtti,
    &MyDerivedClassOfRestrictedQualsOnBaseElements_rtti,
    &MyEmbeddedPropertiesClass_rtti,
    &MyEmptyClass_rtti,
    &MyEmptyDerivedClass_rtti,
    &MyEmptySecondDerivedClass_rtti,
    &MyFooClass_rtti,
    &MyNoParamArrayQualsMethodsClass_rtti,
    &MyNoParamMethodsClass_rtti,
    &MyNoParamSimpleQualsMethodsClass_rtti,
    &MyOptionTestClass_rtti,
    &MyOptionTestDerivedClass_rtti,
    &MyReferenceClass_rtti,
    &MySimpleParamArrayQualsMethodsClass_rtti,
    &MySimpleParamMethodsClass_rtti,
    &MySimpleParamSimpleQualsMethodsClass_rtti,
    &MySimplePropertiesArrayQualsClass_rtti,
    &MySimplePropertiesClass_rtti,
    &MySimplePropertiesDerivedClass_rtti,
    &MySimplePropertiesSimpleQualsClass_rtti,
    &MySimpleQualClass_rtti,
    &MyVariousArrayLengthClass_rtti,
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

