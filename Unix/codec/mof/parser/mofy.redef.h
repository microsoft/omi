/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
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