/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */

#ifndef _mof_parser_h
#define _mof_parser_h

#include <MI.h>
#include <base/batch.h>
#include "instancedecl.h"
#include "mofhash.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
**==============================================================================
**
** Instance_New function
**
** TODO: To link to base.lib directly upon the duplicate code get resolved
**       between wmiv2\common and winomi\base
**
**==============================================================================
*/
typedef MI_Result (MI_CALL *Instance_NewFunc)(
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_Instance **instance);

/*
**==============================================================================
**
** Schemacheck options for instance deserialization
**
**==============================================================================
*/
#define SCHEMA_CHECK_DEFAULT 0X1
#define SCHEMA_CHECK_STRICT 0X2
#define SCHEMA_CHECK_LOOSE 0X4
#define SCHEMA_CHECK_IGNORE_PROPERTYTYPE 0X8
#define SCHEMA_CHECK_IGNORE_PROPERTIES 0x10
#define SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES   (SCHEMA_CHECK_IGNORE_PROPERTIES | SCHEMA_CHECK_DEFAULT)
#define SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES   (SCHEMA_CHECK_IGNORE_PROPERTIES | SCHEMA_CHECK_STRICT)
#define SCHEMA_CHECK_IGNORE (SCHEMA_CHECK_LOOSE|SCHEMA_CHECK_IGNORE_PROPERTYTYPE|SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES|SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES)


/*=============================================================================
**
** Deserialization input parameter
**
=============================================================================*/
typedef struct _MOF_CODEC_PARAM
{
    MI_Uint8 *buffer;
    MI_Uint32 bufferlength;
    MI_Uint32 schemacheck;
    MI_DeserializerCallbacks callbacks;
    MI_ClassA *schemas;
    StringHash schemasHash;
    const MI_Char *serverName;
    const MI_Char *namespaceName;
    MI_StringA ignorePropertyList; 
}MOF_CODEC_PARAM;

/*=============================================================================
**
** MOF parser struct definition
**
=============================================================================*/
typedef struct _MOF_Parser
{
    /* Whether batch object should be deleted in CQL_Delete() */
    MI_Boolean deleteBatch;

    /* Parser state */
    void* state;

    /* Input data */
    MOF_CODEC_PARAM param;

    /* Class array read from classObjectNeeded callback */
    /* Should be freed upon finalizing parser */
    MI_ClassA classaObjectNeeded;
}
MOF_Parser;


/*=============================================================================
**
** MOF parser functions
**
=============================================================================*/
MOF_Parser * MOF_Parser_Init(_In_ _Readable_bytes_(nBytes) void* buf,
    _In_ MI_Uint32 nBytes,
    _Inout_ Batch* batch,
    _Out_opt_ MI_Result *r);

void MOF_Parser_Delete(_Inout_ MOF_Parser* self);

int  MOF_Parser_ParseLex(_Inout_ MOF_Parser* self);

int MOF_Parser_Parse(_Inout_ MOF_Parser* self);

void MOF_Parser_Dump(_In_ MOF_Parser* self, FILE* file);

void GlobalInitialize();

void GlobalFinalize();

#ifdef __cplusplus
}
#endif

#endif /* _mof_parser_h */
