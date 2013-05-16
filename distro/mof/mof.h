/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _mof_mof_h
#define _mof_mof_h

#ifdef MI_CHAR_TYPE
# if (MI_CHAR_TYPE != 1)
#  error "MOF compiler requires MI_CHAR_TYPE == 1"
# endif
#endif

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _MOF_Parser MOF_Parser;

extern MOF_Parser* MOF_Parser_New(
    const char* const* paths,
    size_t numPaths);

typedef void (*MOF_ErrorCallback)(
    const char* msg,
    const wchar_t* wmsg,
    void* data);

extern void MOF_Parser_SetErrorCallback(
    MOF_Parser* self,
    MOF_ErrorCallback callback,
    void* data);

typedef void (*MOF_WarningCallback)(
    const char* msg, const wchar_t* wmsg, void* data);

extern void MOF_Parser_SetWarningCallback(
    MOF_Parser* self,
    MOF_WarningCallback callback,
    void* data);

typedef void (*MOF_PragmaCallback)(
    const char* pragma,
    const char* value,
    void* data);

extern void MOF_Parser_SetPragmaCallback(
    MOF_Parser* self,
    MOF_PragmaCallback callback,
    void* data);

typedef void (*MOF_ClassDeclCallback)(
    const MI_ClassDecl* decl,
    void* data);

typedef void (*MOF_InstanceDeclCallback)(
    const MI_InstanceDecl* decl,
    void* data);

extern void MOF_Parser_SetClassDeclCallback(
    MOF_Parser* self,
    MOF_ClassDeclCallback callback,
    void* data);

extern void MOF_Parser_SetInstanceDeclCallback(
    MOF_Parser* self,
    MOF_InstanceDeclCallback callback,
    void* data);

typedef void (*MOF_QualifierDeclCallback)(
    const MI_QualifierDecl* decl,
    void* data);

extern void MOF_Parser_SetQualifierDeclCallback(
    MOF_Parser* self,
    MOF_QualifierDeclCallback callback,
    void* data);

extern int MOF_Parser_Parse(
    MOF_Parser* self,
    const char* path);

extern int MOF_Parser_ParseString(
    MOF_Parser* self,
    const char* mof_string);

extern void MOF_Parser_Delete(
    MOF_Parser* self);

extern void MOF_Parser_Dump(
    MOF_Parser* self,
    FILE* file);

#ifdef __cplusplus
}
#endif

#endif /* _mof_mof_h */
