/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
**==============================================================================
** Mof Keyword list and const definitions
**==============================================================================
*/

/*
**==============================================================================
**
** Case-insensitive keywords (see CIM Infrastructure specification).
**
**==============================================================================
*/

/*
**==============================================================================
**
** Following are defitions of mof tokens
**
** True and false
**     TRUE [Tt][Rr][Uu][Ee]
**     FALSE [Ff][Aa][Ll][Ss][Ee]

** Null value
**     NULL [Nn][Uu][Ll][Ll]

** Data types
**     DT_BOOLEAN [Bb][Oo][Oo][Ll][Ee][Aa][Nn]
**     DT_SINT8 [Ss][Ii][Nn][Tt]8
**     DT_UINT8 [Uu][Ii][Nn][Tt]8
**     DT_SINT16 [Ss][Ii][Nn][Tt]16
**     DT_UINT16 [Uu][Ii][Nn][Tt]16
**     DT_SINT32 [Ss][Ii][Nn][Tt]32
**     DT_UINT32 [Uu][Ii][Nn][Tt]32
**     DT_SINT64 [Ss][Ii][Nn][Tt]64
**     DT_UINT64 [Uu][Ii][Nn][Tt]64
**     DT_REAL32 [Rr][Ee][Aa][Ll]32
**     DT_REAL64 [Rr][Ee][Aa][Ll]64
**     DT_DATETIME [Dd][Aa][Tt][Ee][Tt][Ii][Mm][Ee]
**     DT_CHAR16 [Cc][Hh][Aa][Rr]16
**     DT_STRING [Ss][Tt][Rr][Ii][Nn][Gg] 

** Ref
**     REF [Rr][Ee][Ff]

** Scope
**     SCOPE [Ss][Cc][Oo][Pp][Ee]
**     CLASS [Cc][Ll][Aa][Ss][Ss]
**     ASSOCIATION [Aa][Ss][Ss][Oo][Cc][Ii][Aa][Tt][Ii][Oo][Nn]
**     INDICATION [Ii][Nn][Dd][Ii][Cc][Aa][Tt][Ii][Oo][Nn]
**     QUALIFIER [Qq][Uu][Aa][Ll][Ii][Ff][Ii][Ee][Rr]
**     PROPERTY [Pp][Rr][Oo][Pp][Ee][Rr][Tt][Yy]
**     REFERENCE [Rr][Ee][Ff][Ee][Rr][Ee][Nn][Cc][Ee]
**     METHOD [Mm][Ee][Tt][Hh][Oo][Dd]
**     PARAMETER [Pp][Aa][Rr][Aa][Mm][Ee][Tt][Ee][Rr]
**     ANY [Aa][Nn][Yy]

** Flavor
**     FLAVOR [Ff][Ll][Aa][Vv][Oo][Rr]
**     ENABLEOVERRIDE [Ee][Nn][Aa][Bb][Ll][Ee][Oo][Vv][Ee][Rr][Rr][Ii][Dd][Ee]
**     DISABLEOVERRIDE [Dd][Ii][Ss][Aa][Bb][Ll][Ee][Oo][Vv][Ee][Rr][Rr][Ii][Dd][Ee]
**     RESTRICTED [Rr][Ee][Ss][Tt][Rr][Ii][Cc][Tt][Ee][Dd]
**     TOSUBCLASS [Tt][Oo][Ss][Uu][Bb][Cc][Ll][Aa][Ss][Ss]
**     TRANSLATABLE [Tt][Rr][Aa][Nn][Ss][Ll][Aa][Tt][Aa][Bb][Ll][Ee]

** Instance of
**     INSTANCE [Ii][Nn][Ss][Tt][Aa][Nn][Cc][Ee]
**     OF [Oo][Ff]

** Alias
**     AS [Aa][Ss]

** #pragma
**     PRAGMA \#[Pp][Rr][Aa][Gg][Mm][Aa][ ]
**
**==============================================================================
*/


/*
**==============================================================================
**
** Literal productions (see CIM Infrastructure specification).
**
** escapedChar     \'\\[rntfb\"\'\\]\'
** simpleChar      \'[^\']\'
** hexChar         \'\\[xX][A-Fa-f0-9]+\'
** realValue       [+-]?[0-9]*\.[0-9]+([eE][+-]?[0-9]+)?
** hexValue        [+-]?0[xX][A-Fa-f0-9]+
** decimalValue    [+-]?[1-9][0-9]*
** octalValue      [+-]?0[0-7]+
** binaryValue     [+-]?[01]+[Bb]
** blank           [ \r\n\t]
** identifier      [A-Za-z_][A-Za-z_0-9]*
** aliasIdentifier \$[A-Za-z_][A-Za-z_0-9]*
** whiteSpaceChar  [ \r\n\t\b\f]
**==============================================================================
*/

#ifndef _mof_token_h
#define _mof_token_h

typedef union _MOF_String
{
    void * data;
    char * str;
    wchar_t * wstr;
}MOF_String;

typedef struct _MOF_StringLen
{
    MOF_String str;
    size_t len;
    unsigned int code;
}MOF_StringLen;

/*
**==============================================================================
**
** Define token table(s)
**
**  code field is for fast lookup purpose;
**  it is in the format of 0x00[F][L][N]
**      F- first char in lower case
**      L- last char in lower case
**      N- string length
**
** for example, hash code of "TRUE" is 0x00746504
**
**==============================================================================
*/
typedef struct _MOF_Token
{
    MOF_String str;
    unsigned int code;
    unsigned int token;
}MOF_Token;

static const MOF_Token _catokens[] =
{
    {{"TRUE"}, 0x00746504, TOK_BOOLEAN_VALUE},
    {{"FALSE"}, 0x00666505, TOK_BOOLEAN_VALUE},
    {{"NULL"}, 0x006E6C04, TOK_NULL},
    {{"BOOLEAN"}, 0x00626E07, TOK_BOOLEAN},
    {{"SINT8"}, 0x00733805, TOK_SINT8},
    {{"UINT8"}, 0x00753805, TOK_UINT8},
    {{"SINT16"}, 0x00733606, TOK_SINT16},
    {{"UINT16"}, 0x00753606, TOK_UINT16},
    {{"SINT32"}, 0x00733206, TOK_SINT32},
    {{"UINT32"}, 0x00753206, TOK_UINT32},
    {{"SINT64"}, 0x00733406, TOK_SINT64},
    {{"UINT64"}, 0x00753406, TOK_UINT64},
    {{"REAL32"}, 0x00723206, TOK_REAL32},
    {{"REAL64"}, 0x00723406, TOK_REAL64},
    {{"DATETIME"}, 0x00646508, TOK_DATETIME},
    {{"CHAR16"}, 0x00633606, TOK_CHAR16},
    {{"STRING"}, 0x00736706, TOK_STRING},
    {{"REF"}, 0x00726603, TOK_REF},
    {{"SCOPE"}, 0x00736505, TOK_SCOPE},
    {{"CLASS"}, 0x00637305, TOK_CLASS},
    {{"ASSOCIATION"}, 0x00616E0B, TOK_ASSOCIATION},
    {{"INDICATION"}, 0x00696E0A, TOK_INDICATION},
    {{"QUALIFIER"}, 0x00717209, TOK_QUALIFIER},
    {{"PROPERTY"}, 0x00707908, TOK_PROPERTY},
    {{"REFERENCE"}, 0x00726509, TOK_REFERENCE},
    {{"METHOD"}, 0x006D6406, TOK_METHOD},
    {{"PARAMETER"}, 0x00707209, TOK_PARAMETER},
    {{"ANY"}, 0x00617903, TOK_ANY},
    {{"FLAVOR"}, 0x00667206, TOK_FLAVOR},
    {{"ENABLEOVERRIDE"}, 0x0065650E, TOK_ENABLEOVERRIDE},
    {{"DISABLEOVERRIDE"}, 0x0064650F, TOK_DISABLEOVERRIDE},
    {{"RESTRICTED"}, 0x0072640A, TOK_RESTRICTED},
    {{"TOSUBCLASS"}, 0x0074730A, TOK_TOSUBCLASS},
    {{"TRANSLATABLE"}, 0x0074650C, TOK_TRANSLATABLE},
    {{"INSTANCE"}, 0x00696508, TOK_INSTANCE},
    {{"OF"}, 0x006F6602, TOK_OF},
    {{"AS"}, 0x00617302, TOK_AS},
    {{"TOINSTANCE"}, 0x0074650A, TOK_TOINSTANCE},
    {{NULL}, 0, 0},
};

static const MOF_Token _caPragmaToken=
    {{"#PRAGMA"}, 0x00236107, TOK_PRAGMA};

#define L(x) x

static const MOF_Token _cwtokens[] =
{
    {{L"TRUE"}, 0x00746504, TOK_BOOLEAN_VALUE},
    {{L"FALSE"}, 0x00666505, TOK_BOOLEAN_VALUE},
    {{L"NULL"}, 0x006E6C04, TOK_NULL},
    {{L"BOOLEAN"}, 0x00626E07, TOK_BOOLEAN},
    {{L"SINT8"}, 0x00733805, TOK_SINT8},
    {{L"UINT8"}, 0x00753805, TOK_UINT8},
    {{L"SINT16"}, 0x00733606, TOK_SINT16},
    {{L"UINT16"}, 0x00753606, TOK_UINT16},
    {{L"SINT32"}, 0x00733206, TOK_SINT32},
    {{L"UINT32"}, 0x00753206, TOK_UINT32},
    {{L"SINT64"}, 0x00733406, TOK_SINT64},
    {{L"UINT64"}, 0x00753406, TOK_UINT64},
    {{L"REAL32"}, 0x00723206, TOK_REAL32},
    {{L"REAL64"}, 0x00723406, TOK_REAL64},
    {{L"DATETIME"}, 0x00646508, TOK_DATETIME},
    {{L"CHAR16"}, 0x00633606, TOK_CHAR16},
    {{L"STRING"}, 0x00736706, TOK_STRING},
    {{L"REF"}, 0x00726603, TOK_REF},
    {{L"SCOPE"}, 0x00736505, TOK_SCOPE},
    {{L"CLASS"}, 0x00637305, TOK_CLASS},
    {{L"ASSOCIATION"}, 0x00616E0B, TOK_ASSOCIATION},
    {{L"INDICATION"}, 0x00696E0A, TOK_INDICATION},
    {{L"QUALIFIER"}, 0x00717209, TOK_QUALIFIER},
    {{L"PROPERTY"}, 0x00707908, TOK_PROPERTY},
    {{L"REFERENCE"}, 0x00726509, TOK_REFERENCE},
    {{L"METHOD"}, 0x006D6406, TOK_METHOD},
    {{L"PARAMETER"}, 0x00707209, TOK_PARAMETER},
    {{L"ANY"}, 0x00617903, TOK_ANY},
    {{L"FLAVOR"}, 0x00667206, TOK_FLAVOR},
    {{L"ENABLEOVERRIDE"}, 0x0065650E, TOK_ENABLEOVERRIDE},
    {{L"DISABLEOVERRIDE"}, 0x0064650F, TOK_DISABLEOVERRIDE},
    {{L"RESTRICTED"}, 0x0072640A, TOK_RESTRICTED},
    {{L"TOSUBCLASS"}, 0x0074730A, TOK_TOSUBCLASS},
    {{L"TRANSLATABLE"}, 0x0074650C, TOK_TRANSLATABLE},
    {{L"INSTANCE"}, 0x00696508, TOK_INSTANCE},
    {{L"OF"}, 0x006F6602, TOK_OF},
    {{L"AS"}, 0x00617302, TOK_AS},
    {{"TOINSTANCE"}, 0x0074650A, TOK_TOINSTANCE},
    {{NULL}, 0, 0},
};

static const MOF_Token _cwPragmaToken=
    {{L"#PRAGMA"}, 0x00236107, TOK_PRAGMA};

/*
**==============================================================================
**
** Define fast lookup type & table for characters
**
**==============================================================================
*/
typedef enum _CharFlag
{
    TOKEN_SINGLE_CHAR_FLAG = 0x1, // the single char itself as a token
    OTHER_FLAG = 0x2,
}CharFlag;

/*
**==============================================================================
**
** Fast lookup table contains:
**      single char as mof token        = ( ) [ ] { } : ; ,
**
**==============================================================================
*/
static const char scTable[256] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#endif /* _mof_token_h */
