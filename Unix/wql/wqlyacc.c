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

#include <pal/palcommon.h>

#if defined(_MSC_VER)

/* warning C4127: conditional expression is constant */
# pragma warning( disable : 4127 )

/* warning C4244: '=' : conversion from '?' to '?', possible loss of data */
# pragma warning( disable : 4244 )
# pragma warning( disable : 4242 )

/* warning C4102: 'yyerrlab' : unreferenced label */
# pragma warning( disable : 4102)

/* warning C4706: assignment within conditional expression */
# pragma warning( disable : 4706 )

/* Old-style declarator */
# pragma warning( disable : 4131)

/* PreFast - reviewed and believed to be false-positive*/

/* warning C6385: Invalid data: accessing '??', the readable size is 'x' bytes, but 'y' bytes might be read: Lines: ... */
# pragma warning(disable : 6385)
# pragma warning(disable : 6011)

#ifdef _PREFAST_
#pragma prefast (disable: 26014)
#pragma prefast (disable: 26001)
#endif

#endif /* _MSC_VER */

#include "wqlyaccinc.c"

void WQL_ResetParser()
{
    yydebug = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = 0;
    yyssp = 0;
    yyvsp = 0;

    memset(&yyval, 0, sizeof(yyval));
    memset(&yylval, 0, sizeof(yylval));

    if (yyss)
    {
        PAL_Free(yyss);
        yyss = 0;
    }
    yysslim = 0;

    if (yyvs)
    {
        PAL_Free(yyvs);
        yyvs = 0;
    }
    yystacksize = 0;
}

