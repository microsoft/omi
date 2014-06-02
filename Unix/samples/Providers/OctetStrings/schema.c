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
#include "OMI_OctetStrings.h"

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
** OMI_OctetStrings
**
**==============================================================================
*/

static MI_CONST MI_Boolean OMI_OctetStrings_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier OMI_OctetStrings_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_OctetStrings_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_OctetStrings_Key_quals[] =
{
    &OMI_OctetStrings_Key_Key_qual,
};

/* property OMI_OctetStrings.Key */
static MI_CONST MI_PropertyDecl OMI_OctetStrings_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    OMI_OctetStrings_Key_quals, /* qualifiers */
    MI_COUNT(OMI_OctetStrings_Key_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_OctetStrings, Key), /* offset */
    MI_T("OMI_OctetStrings"), /* origin */
    MI_T("OMI_OctetStrings"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_OctetStrings_Data1_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier OMI_OctetStrings_Data1_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_OctetStrings_Data1_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_OctetStrings_Data1_quals[] =
{
    &OMI_OctetStrings_Data1_Octetstring_qual,
};

/* property OMI_OctetStrings.Data1 */
static MI_CONST MI_PropertyDecl OMI_OctetStrings_Data1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643105, /* code */
    MI_T("Data1"), /* name */
    OMI_OctetStrings_Data1_quals, /* qualifiers */
    MI_COUNT(OMI_OctetStrings_Data1_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_OctetStrings, Data1), /* offset */
    MI_T("OMI_OctetStrings"), /* origin */
    MI_T("OMI_OctetStrings"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_OctetStrings_Data2_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier OMI_OctetStrings_Data2_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_OctetStrings_Data2_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_OctetStrings_Data2_quals[] =
{
    &OMI_OctetStrings_Data2_Octetstring_qual,
};

/* property OMI_OctetStrings.Data2 */
static MI_CONST MI_PropertyDecl OMI_OctetStrings_Data2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00643205, /* code */
    MI_T("Data2"), /* name */
    OMI_OctetStrings_Data2_quals, /* qualifiers */
    MI_COUNT(OMI_OctetStrings_Data2_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_OctetStrings, Data2), /* offset */
    MI_T("OMI_OctetStrings"), /* origin */
    MI_T("OMI_OctetStrings"), /* propagator */
    NULL,
};

/* property OMI_OctetStrings.Str */
static MI_CONST MI_PropertyDecl OMI_OctetStrings_Str_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737203, /* code */
    MI_T("Str"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_OctetStrings, Str), /* offset */
    MI_T("OMI_OctetStrings"), /* origin */
    MI_T("OMI_OctetStrings"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_OctetStrings_props[] =
{
    &OMI_OctetStrings_Key_prop,
    &OMI_OctetStrings_Data1_prop,
    &OMI_OctetStrings_Data2_prop,
    &OMI_OctetStrings_Str_prop,
};

static MI_CONST MI_ProviderFT OMI_OctetStrings_funcs =
{
  (MI_ProviderFT_Load)OMI_OctetStrings_Load,
  (MI_ProviderFT_Unload)OMI_OctetStrings_Unload,
  (MI_ProviderFT_GetInstance)OMI_OctetStrings_GetInstance,
  (MI_ProviderFT_EnumerateInstances)OMI_OctetStrings_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)OMI_OctetStrings_CreateInstance,
  (MI_ProviderFT_ModifyInstance)OMI_OctetStrings_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)OMI_OctetStrings_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class OMI_OctetStrings */
MI_CONST MI_ClassDecl OMI_OctetStrings_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F7310, /* code */
    MI_T("OMI_OctetStrings"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    OMI_OctetStrings_props, /* properties */
    MI_COUNT(OMI_OctetStrings_props), /* numProperties */
    sizeof(OMI_OctetStrings), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &OMI_OctetStrings_funcs, /* functions */
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
    &OMI_OctetStrings_rtti,
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

