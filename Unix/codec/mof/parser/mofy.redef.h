/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _mof_yredef_h
#define _mof_yredef_h

#if defined(yyparse)
#define yyparse         mofparse
#endif /* yyparse */

#ifndef yystack
#define yystack         state->ystate.mofstack
#endif /* yystack */

#if defined(yylex)
#undef yylex
#define yylex()         moflex(state)
#endif /* yylex */

#if defined(yyerror)
#undef yyerror
#define yyerror(MSG)    moferror(state->errhandler, MSG)
#endif /* yyerror */

#if defined(yychar)
#undef yychar
#define yychar          state->ystate.mofchar
#endif /* yychar */

#if defined(yyval)
#undef yyval
#define yyval           state->ystate.mofval
#endif /* yyval */

#if defined(yylval)
#undef yylval
#define yylval          state->ystate.moflval
#endif /* yylval */

#if defined(yydebug)
#undef yydebug
#define yydebug         state->ystate.mofdebug
#endif /* yydebug */

#if defined(yynerrs)
#undef yynerrs
#define yynerrs         state->ystate.mofnerrs
#endif /* yynerrs */

#if defined(yyerrflag)
#undef yyerrflag
#define yyerrflag       state->ystate.moferrflag
#endif /* yyerrflag */

#if defined(YYPARSE_DECL)
#undef YYPARSE_DECL
#define YYPARSE_DECL() mymofparser(MOF_State *state)
#endif

#endif /* _mof_yredef_h */
