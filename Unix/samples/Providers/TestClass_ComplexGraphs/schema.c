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
#include "ClassHierarchyTest.h"
#include "Root.h"
#include "Base.h"
#include "Derived.h"
#include "Separate.h"

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
** Qualifier declarations
**
**==============================================================================
*/

static MI_CONST MI_Boolean Abstract_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Abstract_qual_decl =
{
    MI_T("Abstract"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Abstract_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Description_qual_decl =
{
    MI_T("Description"), /* name */
    MI_STRING, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
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

static MI_CONST MI_Boolean Structure_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Structure_qual_decl =
{
    MI_T("Structure"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Structure_qual_decl_value, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &Abstract_qual_decl,
    &Description_qual_decl,
    &EmbeddedInstance_qual_decl,
    &EmbeddedObject_qual_decl,
    &Indication_qual_decl,
    &Key_qual_decl,
    &Structure_qual_decl,
};

/*
**==============================================================================
**
** ClassHierarchyTest
**
**==============================================================================
*/

static MI_CONST MI_Boolean ClassHierarchyTest_TestName_Key_qual_value = 1;

static MI_CONST MI_Qualifier ClassHierarchyTest_TestName_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ClassHierarchyTest_TestName_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ClassHierarchyTest_TestName_quals[] =
{
    &ClassHierarchyTest_TestName_Key_qual,
};

/* property ClassHierarchyTest.TestName */
static MI_CONST MI_PropertyDecl ClassHierarchyTest_TestName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00746508, /* code */
    MI_T("TestName"), /* name */
    ClassHierarchyTest_TestName_quals, /* qualifiers */
    MI_COUNT(ClassHierarchyTest_TestName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ClassHierarchyTest, TestName), /* offset */
    MI_T("ClassHierarchyTest"), /* origin */
    MI_T("ClassHierarchyTest"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean ClassHierarchyTest_TestInstance_EmbeddedObject_qual_value = 1;

static MI_CONST MI_Qualifier ClassHierarchyTest_TestInstance_EmbeddedObject_qual =
{
    MI_T("EmbeddedObject"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ClassHierarchyTest_TestInstance_EmbeddedObject_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ClassHierarchyTest_TestInstance_quals[] =
{
    &ClassHierarchyTest_TestInstance_EmbeddedObject_qual,
};

/* property ClassHierarchyTest.TestInstance */
static MI_CONST MI_PropertyDecl ClassHierarchyTest_TestInstance_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0074650C, /* code */
    MI_T("TestInstance"), /* name */
    ClassHierarchyTest_TestInstance_quals, /* qualifiers */
    MI_COUNT(ClassHierarchyTest_TestInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ClassHierarchyTest, TestInstance), /* offset */
    MI_T("ClassHierarchyTest"), /* origin */
    MI_T("ClassHierarchyTest"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ClassHierarchyTest_props[] =
{
    &ClassHierarchyTest_TestName_prop,
    &ClassHierarchyTest_TestInstance_prop,
};

static MI_CONST MI_ProviderFT ClassHierarchyTest_funcs =
{
  (MI_ProviderFT_Load)ClassHierarchyTest_Load,
  (MI_ProviderFT_Unload)ClassHierarchyTest_Unload,
  (MI_ProviderFT_GetInstance)ClassHierarchyTest_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ClassHierarchyTest_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ClassHierarchyTest_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ClassHierarchyTest_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ClassHierarchyTest_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ClassHierarchyTest_Description_qual_value = MI_T("Class returned by the provider");

static MI_CONST MI_Qualifier ClassHierarchyTest_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ClassHierarchyTest_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ClassHierarchyTest_quals[] =
{
    &ClassHierarchyTest_Description_qual,
};

/* class ClassHierarchyTest */
MI_CONST MI_ClassDecl ClassHierarchyTest_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637412, /* code */
    MI_T("ClassHierarchyTest"), /* name */
    ClassHierarchyTest_quals, /* qualifiers */
    MI_COUNT(ClassHierarchyTest_quals), /* numQualifiers */
    ClassHierarchyTest_props, /* properties */
    MI_COUNT(ClassHierarchyTest_props), /* numProperties */
    sizeof(ClassHierarchyTest), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ClassHierarchyTest_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** Root
**
**==============================================================================
*/

/* property Root.Uint32Property */
static MI_CONST MI_PropertyDecl Root_Uint32Property_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0075790E, /* code */
    MI_T("Uint32Property"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Root, Uint32Property), /* offset */
    MI_T("Root"), /* origin */
    MI_T("Root"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Root_props[] =
{
    &Root_Uint32Property_prop,
};

static MI_CONST MI_Char* Root_Description_qual_value = MI_T("Root class for the inheritnace hierarchy");

static MI_CONST MI_Qualifier Root_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Root_Description_qual_value
};

static MI_CONST MI_Boolean Root_Indication_qual_value = 1;

static MI_CONST MI_Qualifier Root_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Root_Indication_qual_value
};

static MI_CONST MI_Boolean Root_Structure_qual_value = 1;

static MI_CONST MI_Qualifier Root_Structure_qual =
{
    MI_T("Structure"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Root_Structure_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Root_quals[] =
{
    &Root_Description_qual,
    &Root_Indication_qual,
    &Root_Structure_qual,
};

/* class Root */
MI_CONST MI_ClassDecl Root_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00727404, /* code */
    MI_T("Root"), /* name */
    Root_quals, /* qualifiers */
    MI_COUNT(Root_quals), /* numQualifiers */
    Root_props, /* properties */
    MI_COUNT(Root_props), /* numProperties */
    sizeof(Root), /* size */
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
** Separate
**
**==============================================================================
*/

/* property Separate.BooleanProperty */
static MI_CONST MI_PropertyDecl Separate_BooleanProperty_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0062790F, /* code */
    MI_T("BooleanProperty"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Separate, BooleanProperty), /* offset */
    MI_T("Separate"), /* origin */
    MI_T("Separate"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Separate_props[] =
{
    &Separate_BooleanProperty_prop,
};

static MI_CONST MI_Char* Separate_Description_qual_value = MI_T("Class outside of the inheritnace hierarchy");

static MI_CONST MI_Qualifier Separate_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Separate_Description_qual_value
};

static MI_CONST MI_Boolean Separate_Indication_qual_value = 1;

static MI_CONST MI_Qualifier Separate_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Separate_Indication_qual_value
};

static MI_CONST MI_Boolean Separate_Structure_qual_value = 1;

static MI_CONST MI_Qualifier Separate_Structure_qual =
{
    MI_T("Structure"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Separate_Structure_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Separate_quals[] =
{
    &Separate_Description_qual,
    &Separate_Indication_qual,
    &Separate_Structure_qual,
};

/* class Separate */
MI_CONST MI_ClassDecl Separate_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00736508, /* code */
    MI_T("Separate"), /* name */
    Separate_quals, /* qualifiers */
    MI_COUNT(Separate_quals), /* numQualifiers */
    Separate_props, /* properties */
    MI_COUNT(Separate_props), /* numProperties */
    sizeof(Separate), /* size */
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
** Base
**
**==============================================================================
*/

static MI_CONST MI_Char* Base_SeparateReference_EmbeddedInstance_qual_value = MI_T("Separate");

static MI_CONST MI_Qualifier Base_SeparateReference_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_SeparateReference_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Base_SeparateReference_quals[] =
{
    &Base_SeparateReference_EmbeddedInstance_qual,
};

/* property Base.SeparateReference */
static MI_CONST MI_PropertyDecl Base_SeparateReference_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00736511, /* code */
    MI_T("SeparateReference"), /* name */
    Base_SeparateReference_quals, /* qualifiers */
    MI_COUNT(Base_SeparateReference_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Separate"), /* className */
    0, /* subscript */
    offsetof(Base, SeparateReference), /* offset */
    MI_T("Base"), /* origin */
    MI_T("Base"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Base_BaseInstance_EmbeddedInstance_qual_value = MI_T("Base");

static MI_CONST MI_Qualifier Base_BaseInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_BaseInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Base_BaseInstance_quals[] =
{
    &Base_BaseInstance_EmbeddedInstance_qual,
};

/* property Base.BaseInstance */
static MI_CONST MI_PropertyDecl Base_BaseInstance_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0062650C, /* code */
    MI_T("BaseInstance"), /* name */
    Base_BaseInstance_quals, /* qualifiers */
    MI_COUNT(Base_BaseInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Base"), /* className */
    0, /* subscript */
    offsetof(Base, BaseInstance), /* offset */
    MI_T("Base"), /* origin */
    MI_T("Base"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Base_BaseInstanceArray_EmbeddedInstance_qual_value = MI_T("Base");

static MI_CONST MI_Qualifier Base_BaseInstanceArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_BaseInstanceArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Base_BaseInstanceArray_quals[] =
{
    &Base_BaseInstanceArray_EmbeddedInstance_qual,
};

/* property Base.BaseInstanceArray */
static MI_CONST MI_PropertyDecl Base_BaseInstanceArray_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00627911, /* code */
    MI_T("BaseInstanceArray"), /* name */
    Base_BaseInstanceArray_quals, /* qualifiers */
    MI_COUNT(Base_BaseInstanceArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Base"), /* className */
    0, /* subscript */
    offsetof(Base, BaseInstanceArray), /* offset */
    MI_T("Base"), /* origin */
    MI_T("Base"), /* propagator */
    NULL,
};

/* property Base.RootReference */
static MI_CONST MI_PropertyDecl Base_RootReference_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0072650D, /* code */
    MI_T("RootReference"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Root"), /* className */
    0, /* subscript */
    offsetof(Base, RootReference), /* offset */
    MI_T("Base"), /* origin */
    MI_T("Base"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Base_props[] =
{
    &Root_Uint32Property_prop,
    &Base_SeparateReference_prop,
    &Base_BaseInstance_prop,
    &Base_BaseInstanceArray_prop,
    &Base_RootReference_prop,
};

static MI_CONST MI_Char* Base_Description_qual_value = MI_T("Class in the middle of inheritance hierarchy, referencing two other instances.");

static MI_CONST MI_Qualifier Base_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_Description_qual_value
};

static MI_CONST MI_Boolean Base_Indication_qual_value = 1;

static MI_CONST MI_Qualifier Base_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_Indication_qual_value
};

static MI_CONST MI_Boolean Base_Structure_qual_value = 1;

static MI_CONST MI_Qualifier Base_Structure_qual =
{
    MI_T("Structure"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Base_Structure_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Base_quals[] =
{
    &Base_Description_qual,
    &Base_Indication_qual,
    &Base_Structure_qual,
};

/* class Base */
MI_CONST MI_ClassDecl Base_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00626504, /* code */
    MI_T("Base"), /* name */
    Base_quals, /* qualifiers */
    MI_COUNT(Base_quals), /* numQualifiers */
    Base_props, /* properties */
    MI_COUNT(Base_props), /* numProperties */
    sizeof(Base), /* size */
    MI_T("Root"), /* superClass */
    &Root_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** Derived
**
**==============================================================================
*/

/* property Derived.StringProperty */
static MI_CONST MI_PropertyDecl Derived_StringProperty_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0073790E, /* code */
    MI_T("StringProperty"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Derived, StringProperty), /* offset */
    MI_T("Derived"), /* origin */
    MI_T("Derived"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Derived_DerivedInstance_EmbeddedInstance_qual_value = MI_T("Derived");

static MI_CONST MI_Qualifier Derived_DerivedInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Derived_DerivedInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Derived_DerivedInstance_quals[] =
{
    &Derived_DerivedInstance_EmbeddedInstance_qual,
};

/* property Derived.DerivedInstance */
static MI_CONST MI_PropertyDecl Derived_DerivedInstance_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0064650F, /* code */
    MI_T("DerivedInstance"), /* name */
    Derived_DerivedInstance_quals, /* qualifiers */
    MI_COUNT(Derived_DerivedInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Derived"), /* className */
    0, /* subscript */
    offsetof(Derived, DerivedInstance), /* offset */
    MI_T("Derived"), /* origin */
    MI_T("Derived"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Derived_props[] =
{
    &Root_Uint32Property_prop,
    &Base_SeparateReference_prop,
    &Base_BaseInstance_prop,
    &Base_BaseInstanceArray_prop,
    &Base_RootReference_prop,
    &Derived_StringProperty_prop,
    &Derived_DerivedInstance_prop,
};

static MI_CONST MI_Char* Derived_Description_qual_value = MI_T("Leaf in the inheritance hierarchy, referencing one more instance.");

static MI_CONST MI_Qualifier Derived_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Derived_Description_qual_value
};

static MI_CONST MI_Boolean Derived_Indication_qual_value = 1;

static MI_CONST MI_Qualifier Derived_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Derived_Indication_qual_value
};

static MI_CONST MI_Boolean Derived_Structure_qual_value = 1;

static MI_CONST MI_Qualifier Derived_Structure_qual =
{
    MI_T("Structure"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &Derived_Structure_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Derived_quals[] =
{
    &Derived_Description_qual,
    &Derived_Indication_qual,
    &Derived_Structure_qual,
};

/* class Derived */
MI_CONST MI_ClassDecl Derived_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00646407, /* code */
    MI_T("Derived"), /* name */
    Derived_quals, /* qualifiers */
    MI_COUNT(Derived_quals), /* numQualifiers */
    Derived_props, /* properties */
    MI_COUNT(Derived_props), /* numProperties */
    sizeof(Derived), /* size */
    MI_T("Base"), /* superClass */
    &Base_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
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
    &Base_rtti,
    &ClassHierarchyTest_rtti,
    &Derived_rtti,
    &Root_rtti,
    &Separate_rtti,
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

