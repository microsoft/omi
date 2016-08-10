/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#define WQL_DOT 257
#define WQL_COLON 258
#define WQL_OR 259
#define WQL_AND 260
#define WQL_NOT 261
#define WQL_ERROR 262
#define WQL_LT 263
#define WQL_FROM 264
#define WQL_LE 265
#define WQL_WHERE 266
#define WQL_NE 267
#define WQL_GT 268
#define WQL_EQ 269
#define WQL_SELECT 270
#define WQL_GE 271
#define WQL_NULL 272
#define WQL_LIKE 273
#define WQL_ISA 274
#define WQL_IDENTIFIER 275
#define WQL_BOOLEAN 276
#define WQL_INTEGER 277
#define WQL_REAL 278
#define WQL_STRING 279
typedef union
{
    WQL_Symbol symbol;
    MI_Char* string;
    long long integer;
    double real;
    unsigned char boolean;
} YYSTYPE;
extern YYSTYPE wqllval;
