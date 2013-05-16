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
#include "ABC_Widget.h"
#include "ABC_Gadget.h"
#include "ABC_Connector.h"

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
** _Match()
**
**==============================================================================
*/

int _Match(const MI_Char* p, const MI_Char* q)
{
    if (!p || !q || !p[0] || !q[0])
        return 1;

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

/*
**==============================================================================
**
** ABC_Widget
**
**==============================================================================
*/

/* property ABC_Widget.Key */
static MI_CONST MI_PropertyDecl ABC_Widget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Widget, Key), /* offset */
    MI_T("ABC_Widget"), /* origin */
    MI_T("ABC_Widget"), /* propagator */
    NULL,
};

/* property ABC_Widget.Color */
static MI_CONST MI_PropertyDecl ABC_Widget_Color_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637205, /* code */
    MI_T("Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Widget, Color), /* offset */
    MI_T("ABC_Widget"), /* origin */
    MI_T("ABC_Widget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Widget_props[] =
{
    &ABC_Widget_Key_prop,
    &ABC_Widget_Color_prop,
};

/* class ABC_Widget */
MI_CONST MI_ClassDecl ABC_Widget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0061740A, /* code */
    MI_T("ABC_Widget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Widget_props, /* properties */
    MI_COUNT(ABC_Widget_props), /* numProperties */
    sizeof(ABC_Widget), /* size */
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
** ABC_Gadget
**
**==============================================================================
*/

/* property ABC_Gadget.Key */
static MI_CONST MI_PropertyDecl ABC_Gadget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Gadget, Key), /* offset */
    MI_T("ABC_Gadget"), /* origin */
    MI_T("ABC_Gadget"), /* propagator */
    NULL,
};

/* property ABC_Gadget.Color */
static MI_CONST MI_PropertyDecl ABC_Gadget_Color_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637205, /* code */
    MI_T("Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Gadget, Color), /* offset */
    MI_T("ABC_Gadget"), /* origin */
    MI_T("ABC_Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Gadget_props[] =
{
    &ABC_Gadget_Key_prop,
    &ABC_Gadget_Color_prop,
};

/* class ABC_Gadget */
MI_CONST MI_ClassDecl ABC_Gadget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0061740A, /* code */
    MI_T("ABC_Gadget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Gadget_props, /* properties */
    MI_COUNT(ABC_Gadget_props), /* numProperties */
    sizeof(ABC_Gadget), /* size */
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
** ABC_Connector
**
**==============================================================================
*/

/* property ABC_Connector.Left */
static MI_CONST MI_PropertyDecl ABC_Connector_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_Widget"), /* className */
    0, /* subscript */
    offsetof(ABC_Connector, Left), /* offset */
    MI_T("ABC_Connector"), /* origin */
    MI_T("ABC_Connector"), /* propagator */
    NULL,
};

/* property ABC_Connector.Right */
static MI_CONST MI_PropertyDecl ABC_Connector_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_Gadget"), /* className */
    0, /* subscript */
    offsetof(ABC_Connector, Right), /* offset */
    MI_T("ABC_Connector"), /* origin */
    MI_T("ABC_Connector"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Connector_props[] =
{
    &ABC_Connector_Left_prop,
    &ABC_Connector_Right_prop,
};

/* class ABC_Connector */
MI_CONST MI_ClassDecl ABC_Connector_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0061720D, /* code */
    MI_T("ABC_Connector"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Connector_props, /* properties */
    MI_COUNT(ABC_Connector_props), /* numProperties */
    sizeof(ABC_Connector), /* size */
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
    &ABC_Connector_rtti,
    &ABC_Gadget_rtti,
    &ABC_Widget_rtti,
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

