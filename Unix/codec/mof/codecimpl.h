/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_codecimpl_h
#define _mof_codecimpl_h

#include <errorhandler.h>

/*
**==============================================================================
Issue	    Example	                Option

I1 Schema has elements not included in instance
    Class A{p1,p2 }
    Instance a {p1}	
    A strict interpretation flag may be supplied by the caller, in which case
    this would fail

I2 Instance has elements not listed in schema.
    One special case is the schema is empty (class does not have any property
    defined or class schema cannot be identified)
    Class A{p1,p2 }
    Instance a {p1, p2, p3}
    Can succeed if the caller supplies an option allowing it

I3 Instance and schema each have unique elements
    Class A{p1,p2 }
    Instance a {p1, p3}
    (2) No option: must always fail

I4 Instance and schema have different property type for some element (1)
    Class A{string p1, uint8 p2 }
    Instance a {p1=1, p3="abc"}
    Deserialization must fail

Following are the designed operation options for the handling mismatch between
   instance and schema.
    Issue   "default"  "strict"  "Loose"   "Ignore_propertytype"  "Ignore"
    I1      Success    Fail      Success   Success                Success
    I2      Fail       Fail      Success   Fail                   Success
    I3      Fail       Fail      Success	Fail                   Success
    I4      Fail       Fail      Fail	Success                Success
**==============================================================================
*/

#include <micodec.h>
#include <mofparser.h>


/*
**==============================================================================
**
** ClassesOfInstance structure contains a temporary copy of the schemas of
** returnning instance array; Upon caller release instance array, the
** batch object and classes should be released accordingly;
**
**==============================================================================
*/
typedef struct _ClassesOfInstance
{
    MI_ClassA classes;
    StringHash classesHash;
}ClassesOfInstance;

/*
**==============================================================================
**
** Schemacheck options for instance deserialization
**
**==============================================================================
*/
typedef enum _Codec_Type
{
    DeserializeClassArray,
    DeserializeInstanceArray,
}Codec_Type;

/*
**==============================================================================
**
** MI_MofCodec structure & functions
**      Which holds all input parameter from API; does post-parsing validation
**      of instance schema, etc; isolates mof parser from API
**
**==============================================================================
*/
typedef struct _MI_MofCodec
{
    /* Output data */
    MI_Uint32 bufferreadlength;
    MI_Instance *errorInstance;
    MI_Result errorCode;
    MI_ClassA *classObjects;
    MI_InstanceA *instanceObjects;

    /* Internal data structure */
    Codec_Type type;
    MOF_Parser *parser;
    Batch * resultbatch;

    /* Error handler */
    MOF_ErrorHandler errhandler;

    /* Copy of schema for instance */
    ClassesOfInstance *coi;

    /* Instance_New function */
    Instance_NewFunc Instance_New;
}MI_MofCodec;

/*
**==============================================================================
**
** Setup error handler of codec object, always success
**
**==============================================================================
*/
void MI_MofCodec_SetupErrorHandler(_Out_ MI_MofCodec *self);

/*
**==============================================================================
**
** Checking parameter via codec object, report error if false
**
**==============================================================================
*/
void MI_MofCodec_ParameterIsNull(
    _In_ MI_MofCodec *self,
    _In_z_ const MI_Char* paramname);

void MI_MofCodec_ParameterIsNonZero(
    _In_ MI_MofCodec *self,
    _In_z_ const MI_Char* paramname);

void MI_MofCodec_ParameterOutOfRange(
    _In_ MI_MofCodec *self,
    _In_z_ const MI_Char* paramname,
    _In_ MI_Uint32 lbound,
    _In_ MI_Uint32 mbound,
    _In_ MI_Uint32 value);

void MI_MofCodec_ParameterNotSupportStringValue(
    _In_ MI_MofCodec *self,
    _In_z_ const MI_Char* paramname,
    _In_z_ const MI_Char* value);

void MI_MofCodec_InvalidResultClassCount(
    _In_ MI_MofCodec *self);

void MI_MofCodec_InvalidResultInstanceCount(
    _In_ MI_MofCodec *self);

/*
**==============================================================================
**
** Initialize codec object
**
**==============================================================================
*/
MI_Result MI_MofCodec_Init(
    _In_ MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_ MI_DeserializerCallbacks * callbacks,
    _In_reads_(bufferLength) MI_Uint8 *buffer,
    _In_ MI_Uint32 bufferLength,
    _In_opt_ MI_ClassA *classes,
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_ Codec_Type type,
    _Out_ MI_MofCodec *self);

/*
**==============================================================================
**
** Deserialize one or multiple class(es) from given buffer
**
**==============================================================================
*/
MI_Result MI_MofCodec_Deserialize(_Inout_ MI_MofCodec *self);


/*
**==============================================================================
**
** Clean up codec object
**
**==============================================================================
*/
void MI_MofCodec_Delete(_Inout_ MI_MofCodec *self);


/*
**==============================================================================
**
** Report error details
**
**==============================================================================
*/
void MI_MofCodec_onError(
    _In_ void * onErrorContext,
    MI_Uint32 errorCode,
    MI_Uint16 errorCategory,
    _In_opt_z_ const MI_Char * errorType,
    _In_opt_z_ const MI_Char * errorMessage);



/*
**==============================================================================
**
** Exposed functions for verification, debugging, testing purpose
**
**==============================================================================
*/
BEGIN_EXTERNC

/*
**==============================================================================
**
** delete mofparser
**
**==============================================================================
*/
void MI_CALL MI_MOFParser_Delete(_Inout_ MOF_Parser* self);

/*
**==============================================================================
**
** Initialize mofparser
**
**==============================================================================
*/
MOF_Parser * MI_CALL MI_MOFParser_Init(
    _In_ _Readable_bytes_(nBytes) void* buf,
    _In_ MI_Uint32 nBytes,
    _Inout_ Batch* batch);

/*
**==============================================================================
**
** Parse token
**
**==============================================================================
*/
int MI_CALL MI_MOFParser_Lex(_Inout_ MOF_Parser* self);

/*
**==============================================================================
**
** Parse mof
**
**==============================================================================
*/
int MI_CALL MI_MOFParser_Parse(_Inout_ MOF_Parser* self);

END_EXTERNC

#endif /* _mof_codecimpl_h */
