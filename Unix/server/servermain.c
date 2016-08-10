/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
