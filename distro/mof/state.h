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

#ifndef _mof_state_h
#define _mof_state_h

#include "heap.h"
#include "ptrarray.h"
#include "types.h"

#define MOF_MAX_PATHS 16

/*
**==============================================================================
**
** MOF_State
**
**     This structure maintains the static parser state for the current parser
**     invocation. It maintains the heap, errors, warnings, class declarations,
**     and qulifier declarations.
**
**==============================================================================
*/

typedef struct _MOF_State
{
    /* Maintains a list of all allocated heap blocks */
    MOF_Heap heap;
    
    /* Name of file being parsed */
    char* path;

    /* Line number of file being parsed */
    unsigned int line;

    /* Maintains a list of errors encountered during parsing */
    MofPtrArray errors;

    /* Maintains a list of warnings encountered during parsing */
    MofPtrArray warnings;

    /* Maintains a list of class declarations processed during parsing */
    MOF_ClassDeclList classDecls;

    /* Maintains a list of instance declarations processed during parsing */
    MOF_InstanceDeclList instanceDecls;

    /* Maintains a list of qualifier declarations processed during parsing */
    MOF_QualifierDeclList qualifierDecls;

    /* Track of EmbeddedInstances qualifiers for post processing */
    MOF_EmbeddedInstanceList embeddedInstanceList;

    /* Paths to search when attempting to locate included files */
    MofPtrArray paths;

    /* User callback to invoke to report an error */
    void (*errorCallback)(const char* msg, const wchar_t* wmsg, void* data);
    void* errorCallbackData;

    /* User callback to invoke to report a warning */
    void (*warningCallback)(const char* msg, const wchar_t* wmsg, void* data);
    void* warningCallbackData;

    /* User callback to invoke when a pragma is recognized */
    void (*pragmaCallback)(const char* pragma, const char* value, void* data);
    void* pragmaCallbackData;

    /* User callback to invoke when a class is recognized */
    void (*classDeclCallback)(const MI_ClassDecl* decl, void* data);
    void* classDeclCallbackData;

    /* User callback to invoke when a qualifier is recognized */
    void (*qualifierDeclCallback)(const MI_QualifierDecl* decl, void* data);
    void* qualifierDeclCallbackData;

    /* User callback to invoke when an instance is recognized */
    void (*instanceDeclCallback)(const MI_InstanceDecl* decl, void* data);
    void* instanceDeclCallbackData;
}
MOF_State;

/* Global parser state object */

extern MOF_State mofstate;
#define state mofstate

#endif /* _mof_state_h */
