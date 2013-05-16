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
#include "OMI_Perf.h"

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
** OMI_Perf
**
**==============================================================================
*/

/* property OMI_Perf.Key */
static MI_CONST MI_PropertyDecl OMI_Perf_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Key), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop01 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop01_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703106, /* code */
    MI_T("Prop01"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop01), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop02 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop02_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703206, /* code */
    MI_T("Prop02"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop02), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop03 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop03_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703306, /* code */
    MI_T("Prop03"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop03), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop04 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop04_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703406, /* code */
    MI_T("Prop04"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop04), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop05 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop05_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703506, /* code */
    MI_T("Prop05"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop05), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop06 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop06_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703606, /* code */
    MI_T("Prop06"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop06), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop07 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop07_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703706, /* code */
    MI_T("Prop07"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop07), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop08 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop08_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703806, /* code */
    MI_T("Prop08"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop08), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop09 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop09_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703906, /* code */
    MI_T("Prop09"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop09), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop10 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop10_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703006, /* code */
    MI_T("Prop10"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop10), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop11 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop11_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703106, /* code */
    MI_T("Prop11"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop11), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop12 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop12_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703206, /* code */
    MI_T("Prop12"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop12), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop13 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop13_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703306, /* code */
    MI_T("Prop13"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop13), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop14 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop14_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703406, /* code */
    MI_T("Prop14"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop14), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop15 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop15_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703506, /* code */
    MI_T("Prop15"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop15), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop16 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703606, /* code */
    MI_T("Prop16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop16), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop17 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop17_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703706, /* code */
    MI_T("Prop17"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop17), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop18 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop18_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703806, /* code */
    MI_T("Prop18"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop18), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop19 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop19_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703906, /* code */
    MI_T("Prop19"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop19), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

/* property OMI_Perf.Prop20 */
static MI_CONST MI_PropertyDecl OMI_Perf_Prop20_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703006, /* code */
    MI_T("Prop20"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Perf, Prop20), /* offset */
    MI_T("OMI_Perf"), /* origin */
    MI_T("OMI_Perf"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_Perf_props[] =
{
    &OMI_Perf_Key_prop,
    &OMI_Perf_Prop01_prop,
    &OMI_Perf_Prop02_prop,
    &OMI_Perf_Prop03_prop,
    &OMI_Perf_Prop04_prop,
    &OMI_Perf_Prop05_prop,
    &OMI_Perf_Prop06_prop,
    &OMI_Perf_Prop07_prop,
    &OMI_Perf_Prop08_prop,
    &OMI_Perf_Prop09_prop,
    &OMI_Perf_Prop10_prop,
    &OMI_Perf_Prop11_prop,
    &OMI_Perf_Prop12_prop,
    &OMI_Perf_Prop13_prop,
    &OMI_Perf_Prop14_prop,
    &OMI_Perf_Prop15_prop,
    &OMI_Perf_Prop16_prop,
    &OMI_Perf_Prop17_prop,
    &OMI_Perf_Prop18_prop,
    &OMI_Perf_Prop19_prop,
    &OMI_Perf_Prop20_prop,
};

static MI_CONST MI_ProviderFT OMI_Perf_funcs =
{
  (MI_ProviderFT_Load)OMI_Perf_Load,
  (MI_ProviderFT_Unload)OMI_Perf_Unload,
  (MI_ProviderFT_GetInstance)OMI_Perf_GetInstance,
  (MI_ProviderFT_EnumerateInstances)OMI_Perf_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)OMI_Perf_CreateInstance,
  (MI_ProviderFT_ModifyInstance)OMI_Perf_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)OMI_Perf_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class OMI_Perf */
MI_CONST MI_ClassDecl OMI_Perf_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F6608, /* code */
    MI_T("OMI_Perf"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    OMI_Perf_props, /* properties */
    MI_COUNT(OMI_Perf_props), /* numProperties */
    sizeof(OMI_Perf), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &OMI_Perf_funcs, /* functions */
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
    &OMI_Perf_rtti,
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

