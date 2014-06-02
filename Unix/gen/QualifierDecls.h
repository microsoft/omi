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

#ifndef _QualifierDecls_h
#define _QualifierDecls_h

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include <cstddef>

//==============================================================================
//
// Standard qualifier declarations
//
//==============================================================================

extern MI_QualifierDecl* g_qualifierDecls[];
extern size_t g_numQualifierDecls;

#endif /* _QualifierDecls_h */
