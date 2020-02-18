/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/palcommon.h>
#include "wqlyaccinc.c"

void WQL_ResetParser()
{
    yydebug = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = 0;

    memset(&yyval, 0, sizeof(yyval));
    memset(&yylval, 0, sizeof(yylval));
}

