/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef _mof_instance_utility_h
#define _mof_instance_utility_h

#include <MI.h>
#include <micodec.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** Utilities creates instance
**
**==============================================================================
*/
MI_Result MI_CALL Mof_Instance_New(
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_Instance **instance);

MI_Result MI_CALL Mof_Instance_InitDynamic(
    _In_z_ const MI_Char* className,
    _In_ MI_Uint32 metaType,
    _Outptr_result_maybenull_ MI_Instance** self);

MI_Result MI_CALL Mof_Instance_Construct(
    _In_ const MI_ClassDecl* classDecl,
    _Out_ MI_Instance* instance);

END_EXTERNC

#endif /* _mof_instance_utility_h */
