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
