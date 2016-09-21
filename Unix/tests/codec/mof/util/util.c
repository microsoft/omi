/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <MI.h>

#if !defined(_MSC_VER)
#include <pal/file.h>
#include <errno.h>
#endif
#include <stdlib.h>
#include <nits/base/nits.h>
#include "util.h"

/*
 * returns the length of a file (in bytes)
 */
_Use_decl_annotations_
size_t getFileSize(FILE *f)
{
    size_t pos;
    size_t end;
    pos = ftell (f);
    fseek (f, 0, SEEK_END);
    end = ftell (f);
    fseek (f, (long)pos, SEEK_SET);
    return end;
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28196)
#pragma prefast (disable: 26045)
#endif

_Use_decl_annotations_
int getFileContent(char *fileName, char** context, size_t *length)
{
    FILE *fp;
    size_t size;
    *context = NULL;
    *length = 0;

    fp = fopen(fileName, "rb"); //binary mode
    if (fp == NULL) return errno;
    size = getFileSize(fp);
    if (size ==0)
    {
        fclose(fp);
        return -1;
    }
    *context = (char*)malloc(size);
    if (*context == NULL)
    {
        fclose(fp);
        return -1;
    }
    *length = fread(*context, 1, size, fp);
    fclose(fp);
    return 0;
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif

_Use_decl_annotations_
void freeFileContent(char *content, size_t length)
{
    MI_UNREFERENCED_PARAMETER(length);
    free(content);
}


const MI_Uint32 cmagicnumber = 0x12345678;

/*=============================================================================
**
** Set operation options (for schema validation)
**
=============================================================================*/
MI_Result SetSchemaValidationOption(
    _Inout_ MofCodecer * self,
    _In_opt_z_ const MI_Char* option)
{
    MI_Result r = MI_OperationOptions_SetString(
        &self->options,
        MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME,
        (option)?option:MOFCODEC_SCHEMA_VALIDATION_IGNORE,
        0);
#ifdef TEST_BUILD
    TASSERT(r == MI_RESULT_OK, MI_T("Ignore out of memory error in unit test fault injection."));
#endif
    return r;
}

/*=============================================================================
**
** Created deserializer
**
=============================================================================*/
MI_Result CreateMofCodecer(_Inout_ MofCodecer * self)
{
    MI_Result r;
    if (self->appcreated) return MI_RESULT_OK;
    r = MI_Application_Initialize(0, MI_T("test"), NULL, &self->app);
#ifdef TEST_BUILD
    TASSERT(r == MI_RESULT_OK, MI_T("Ignore out of memory error in unit test fault injection."));
#endif
    if (r!=MI_RESULT_OK) return r;
    self->appcreated = MI_TRUE;
    r = MI_Application_NewOperationOptions(&self->app, MI_FALSE, &self->options);
#ifdef TEST_BUILD
    TASSERT(r == MI_RESULT_OK, MI_T("Ignore out of memory error in unit test fault injection."));
#endif
    if (r!=MI_RESULT_OK) return r;
    self->optionscreated = MI_TRUE;
    r = SetSchemaValidationOption(self, NULL);
    if (r!=MI_RESULT_OK) return r;
    r = MI_Application_NewDeserializer_Mof(&self->app, 0, MOFCODEC_FORMAT, &self->de);
#ifdef TEST_BUILD
    TASSERT(r == MI_RESULT_OK, MI_T("Ignore out of memory error in unit test fault injection."));
#endif
    if (r!=MI_RESULT_OK) return r;
    self->decreated = MI_TRUE;
    memset(&self->callbacks, 0, sizeof(MI_DeserializerCallbacks));
    self->magicnumber = cmagicnumber;
    self->retvalueClassNeed = MI_RESULT_OK;
    self->classNeedCallbackOptions = 0;
    self->classNeedCalledTimes = 0;
    self->includeFileCalledTimes = 0;
    self->freeincludeFileCalledTimes = 0;
    self->retvalueIncludeFile = MI_RESULT_OK;
    self->classname = NULL;
    self->servername = NULL;
    self->namespacename = NULL;
    self->stackpos = 0;
    memset(self->includebufferstack, 0, sizeof(MI_Uint8*)*INCLUDE_STACK_SIZE);
    return MI_RESULT_OK;
}

/*=============================================================================
**
** Finalize deserializer
**
=============================================================================*/
void DeleteMofCodecer(_Inout_ MofCodecer * self)
{
    if (self->optionscreated) MI_OperationOptions_Delete(&self->options);
    if (self->decreated) MI_Deserializer_Close(&self->de);
    if (self->appcreated) MI_Application_Close(&self->app);
    memset(self, 0, sizeof(MofCodecer));
}
