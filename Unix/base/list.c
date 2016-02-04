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

#include "list.h"

void List_Prepend(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem)
{
    ListElem* head = *head_;
    ListElem* tail = *tail_;

    elem->prev = NULL;

    if (head)
    {
        head->prev = elem;
        elem->next = head;
        head = elem;
    }
    else
    {
        elem->next = NULL;
        head = elem;
        tail = elem;
    }

    *head_ = head;
    *tail_ = tail;
}

void List_Append(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem)
{
    ListElem* head = *head_;
    ListElem* tail = *tail_;

    elem->next = NULL;

    if (tail)
    {
        tail->next = elem;
        elem->prev = tail;
        tail = elem;
    }
    else
    {
        elem->prev = NULL;
        head = elem;
        tail = elem;
    }

    *head_ = head;
    *tail_ = tail;
}

void List_Remove(
    ListElem** head_,
    ListElem** tail_,
    ListElem* elem)
{
    ListElem* head = *head_;
    ListElem* tail = *tail_;

    if (elem->next)
        elem->next->prev = elem->prev;
    else
        tail = elem->prev;

    if (elem->prev)
        elem->prev->next = elem->next;
    else
        head = elem->next;

    *head_ = head;
    *tail_ = tail;
}
