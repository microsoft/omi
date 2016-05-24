/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
