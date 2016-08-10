/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdio.h>
#include "Frog.h"

void Frog_Jump(int number)
{
	FrogEvents_JumpEvent(number);
}

void Frog_EatFlys(int number)
{
	FrogEvents_EatFlysEvent(number);
}

void Frog_Dive(int depth, int time)
{
	FrogEvents_DiveEvent(depth, time);
}
