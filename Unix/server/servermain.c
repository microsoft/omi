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

#include <common.h>

int servermain(int argc, _In_reads_(argc) CharPtr* argv);

#if defined(_MSC_VER)
# pragma warning(disable: 4702)
#endif

#ifdef _MSC_VER
int __cdecl main(int argc, _In_reads_(argc) CharPtr* argv)
#else
int main(int argc, char** argv)
#endif
{
    /* believe it or not but optimized MS compiler produces warning 4702 
     * (warning C4702: unreachable code) for the next line.
     */
    return servermain(argc,argv);
}
