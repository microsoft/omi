/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _strset_h
#define _strset_h

#include <pal/hashmap.h>
#include <MI.h>

typedef struct _StrSet
{
    HashMap impl;
}
StrSet;

int StrSet_Init(
    _Out_ StrSet* self);

void StrSet_Destroy(
    _Inout_ StrSet* self);

MI_Boolean StrSet_Contains(
    _Inout_ StrSet* self, 
    _In_z_ const MI_Char* str);

/* returns:
 *      0 - success
 *      1 - already exists
 *     -1 - failed
 */
int StrSet_Add(
    _Inout_ StrSet* self, 
    _In_z_ const MI_Char* str);

/* Commit additions */
void StrSet_Commit(
    _Inout_ StrSet* self);

/* Undo uncommitted additions */
void StrSet_Undo(
    _Inout_ StrSet* self);

void StrSet_Dump(
    _In_ const StrSet* self);

#endif /* _strset_h */
