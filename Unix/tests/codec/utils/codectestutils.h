/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _codectestutils_h
#define _codectestutils_h

#include <mi.h>

bool CompareInstances(_In_ MI_Instance* instanceA, _In_ MI_Instance* instanceB);

bool CompareClasses(_In_ MI_Class* classA, _In_ MI_Class* classB);

#endif