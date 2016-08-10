/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _FrogEvents_h
#define _FrogEvents_h

#include "oi.h"

// This is the public interface of the Frog

void Frog_Jump(int number);
void Frog_EatFlys(int number);
void Frog_Dive(int depth, int time);

// These are the Open Instrtumentation callouts from the Frog

OI_SETDEFAULT(LEVEL(3))

OI_EVENT(1, "I have jumped %d feet")
void FrogEvents_JumpEvent(int number);

OI_EVENT(2, "I have eaten %d flys")
void FrogEvents_EatFlysEvent(int number);

OI_EVENT(3, "I have dived %d feet for %d seconds")
void FrogEvents_DiveEvent(int depth, int time);

#endif /* _FrogEvents_h */




