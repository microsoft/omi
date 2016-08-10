/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
