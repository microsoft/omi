/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */

#ifndef _mof_test_util_h
#define _mof_test_util_h
#include <stdio.h>
#include <codec/common/micodec.h>


#ifdef __cplusplus
extern "C" {
#endif

extern const MI_Uint32 cmagicnumber;

/*=============================================================================
**
** Read File content
**
=============================================================================*/
size_t getFileSize(_In_ FILE *f);

_Success_(return == 0)
int getFileContent(
    _In_z_ char *fileName,
    _Outptr_result_bytebuffer_(*length) char** content,
    _Out_ size_t *length);
void freeFileContent(_In_reads_bytes_(length) char *content, _In_ size_t length);


/*=============================================================================
**
** Structure hold objects for creating mof deserializer
**
=============================================================================*/
#define INCLUDE_STACK_SIZE 32
typedef struct _MofCodecer
{
    MI_Uint32 magicnumber;
    MI_Application app;
    MI_Boolean appcreated;
    MI_OperationOptions options;
    MI_Boolean optionscreated;
    MI_Deserializer de;
    MI_Boolean decreated;
    MI_DeserializerCallbacks callbacks;
    /* options for callback */
    MI_Result retvalueClassNeed;
    MI_Uint32 classNeedCalledTimes;
    MI_Uint32 classNeedCallbackOptions; /*0-default, 1-search extened class*/
    MI_Result retvalueIncludeFile;
    MI_Uint32 includeFileCalledTimes;
    MI_Uint32 freeincludeFileCalledTimes;
    const MI_Char* servername;
    const MI_Char* namespacename;
    MI_Char* classname;
    _Field_size_(INCLUDE_STACK_SIZE) MI_Uint8* includebufferstack[INCLUDE_STACK_SIZE];
    MI_Uint8 stackpos;
}MofCodecer;

/*=============================================================================
**
** Set operation options (for schema validation)
**
=============================================================================*/
MI_Result SetSchemaValidationOption(
    _Inout_ MofCodecer * self,
    _In_opt_z_ const MI_Char* option);

/*=============================================================================
**
** Created deserializer
**
=============================================================================*/
MI_Result CreateMofCodecer(_Inout_ MofCodecer * self);

/*=============================================================================
**
** Finalize deserializer
**
=============================================================================*/
void DeleteMofCodecer(_Inout_ MofCodecer * self);


#ifdef __cplusplus
}
#endif

#endif /* _mof_test_util_h */
