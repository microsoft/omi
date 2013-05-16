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

#include <cstdio>
#include <cstdlib>
#include <base/lib.h>

int main(int argc, char** argv)
{
    // Check arguments:

    if (argc != 2)
    {
        fprintf(stderr, "Usage %s SHAREDLIBRARY\n", argv[0]);
        exit(1);
    }

    // Open the library:

    void* handle = Lib_Open(argv[1]);

    if (!handle)
    {
        fprintf(stderr, "%s: %s\n", argv[0], Lib_Err());
        exit(1);
    }

    Lib_Close(handle);

    return 0;
}
