/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "instanceutil.h"
#if defined(_MSC_VER)
#include <common/instance.h>
#else
#include "base/instance.h"
#endif

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_New(
    const MI_ClassDecl* classDecl,
    MI_Instance **instance)
{
#if defined(_MSC_VER)
    return Instance_New(classDecl, instance);
#else
    return Instance_New(instance, classDecl, NULL);
#endif
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_InitDynamic(
    const MI_Char* className,
    MI_Uint32 metaType,
    MI_Instance** self)
{
#if defined(_MSC_VER)
    return Instance_InitDynamic(self, className, metaType);
#else
    return Instance_NewDynamic(self, className, metaType, NULL);
#endif
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_Construct(
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
#if defined(_MSC_VER)
    return Instance_Construct(classDecl, instance);
#else
    return Instance_Construct( instance, classDecl, NULL);
#endif
}
