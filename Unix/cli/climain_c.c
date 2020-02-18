/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <MI.h>

extern MI_Result climain(int argc, const MI_Char* argv[]);

int MI_MAIN_CALL main(int argc, const char* argv[])
{
#if defined (MI_USE_WCHAR)
    /* Going to need to convert the args to MI_Char */
    printf("Do not support %s when using wide char support yet\n", argv[0]);
    return 0;
#else
    exit((int) climain(argc, argv));
#endif
}
