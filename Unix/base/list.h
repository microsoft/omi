/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
