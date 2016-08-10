/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <MI.h>
#include <assert.h>

extern "C" {
MI_Module* MI_Main(MI_Context* context);
}

int main()
{
    MI_Module* module = MI_Main(NULL);
    assert(module != NULL);
    return 0;
}
