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

#ifndef _omi_list_h
#define _omi_list_h

#include "config.h"
#include <common.h>

BEGIN_EXTERNC

/* Serves as a base type for any structure that may be placed on a list 
* (provided that the first two fields are 'next' and 'prev'.
*/
typedef struct _ListElem
{
    struct _ListElem* next;
    struct _ListElem* prev;
}
ListElem;

/* Insert 'elem' at the front of the doubly-linked list */
void List_Prepend(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem);

/* Insert 'elem' at the end of the doubly-linked list */
void List_Append(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem);

/* Remove 'elem' for the doubly-linked list */
void List_Remove(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem);

END_EXTERNC

#endif /* _omi_list_h */
