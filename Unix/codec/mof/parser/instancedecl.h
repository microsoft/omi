/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef _mof_instancedecl_h
#define _mof_instancedecl_h

//#ifndef MI_CHAR_TYPE
//# define MI_CHAR_TYPE 1
//#endif

#include <MI.h>

/*
**==============================================================================
**
** struct MI_InstanceDecl
**
**     Represents an instance declaration (as encountered in MOF).
**
**==============================================================================
*/

typedef struct _MI_InstanceDecl MI_InstanceDecl;

struct _MI_InstanceDecl /* extends MI_ObjectDecl */
{
    /* Fields inherited from MI_FeatureDecl */
    MI_Uint32 flags;
    MI_Uint32 code;
    MI_CONST MI_Char* name; /* name of class of which this is an instance */
    struct _MI_Qualifier MI_CONST* MI_CONST* qualifiers; /* unused */
    MI_Uint32 numQualifiers; /* unused */

    /* Fields inherited from MI_ObjectDecl */
    struct _MI_PropertyDecl MI_CONST* MI_CONST* properties;
    MI_Uint32 numProperties;
    MI_Uint32 size;

    /* Extended Fields*/
    MI_Char* alias; /* alias name */
    const MI_ClassDecl * decl; /* corresponding classdecl */
    MI_Uint32 refs; /* referenced times, 0 means no body refer to it */
    MI_Instance *instance; /* finalized instance */
};

#endif /* _mof_instancedecl_h */
