/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _wql_state_h
#define _wql_state_h

#include "wql.h"

/* Global parser state */
typedef struct _WQL_State
{
    /* The input buffer */
    const ZChar* text;
    int size;
    int offset;

    /* Current lexer pointer within text */
    const ZChar* ptr;

    /* Error status (0=okay, -1=error) */
    int status;

    /* Parser output structure */
    WQL* wql;
}
WQL_State;

extern WQL_State wqlstate;

#endif /* _wql_state_h */
