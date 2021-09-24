/*
**==============================================================================
**
** mof.lex
**
**     This file defines a lexigraphical analyzer for the Managed Object Format
**     (MOF). See the BNF in the CIM Infrastructure Specification.
**
**==============================================================================
*/

%{

/* Do not read from standard input */
#define YY_NEVER_INTERACTIVE 1
#define MOF_STACK_SIZE 32

#include "config.h"
#include "mof.h"
#include "types.h"
#include "mofyacc.h"
#include "buffer.h"
#include "ptrarray.h"
#include "state.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yyparse();
int closeIncludeFile();

struct _MOF_Parser
{
    MOF_State state;
};

typedef struct _StackItem
{
    char* file;
    unsigned int line;
    YY_BUFFER_STATE buffer;
}
StackItem;

/* Stack of parser states for open nested MOF files */
static StackItem s_stack[MOF_STACK_SIZE];

/* Current size of stack s_stack[s_top-1] is the top */
static size_t s_top = 0;

%}

/*
**==============================================================================
**
** Case-insensitive keywords (see CIM Infrastructure specification).
**
**==============================================================================
*/

/* True and false */
TRUE [Tt][Rr][Uu][Ee]
FALSE [Ff][Aa][Ll][Ss][Ee]

/* Null value */
NULL [Nn][Uu][Ll][Ll]

/* Data types */
DT_BOOLEAN [Bb][Oo][Oo][Ll][Ee][Aa][Nn]
DT_SINT8 [Ss][Ii][Nn][Tt]8
DT_UINT8 [Uu][Ii][Nn][Tt]8
DT_SINT16 [Ss][Ii][Nn][Tt]16
DT_UINT16 [Uu][Ii][Nn][Tt]16
DT_SINT32 [Ss][Ii][Nn][Tt]32
DT_UINT32 [Uu][Ii][Nn][Tt]32
DT_SINT64 [Ss][Ii][Nn][Tt]64
DT_UINT64 [Uu][Ii][Nn][Tt]64
DT_REAL32 [Rr][Ee][Aa][Ll]32
DT_REAL64 [Rr][Ee][Aa][Ll]64
DT_DATETIME [Dd][Aa][Tt][Ee][Tt][Ii][Mm][Ee]
DT_CHAR16 [Cc][Hh][Aa][Rr]16
DT_STRING [Ss][Tt][Rr][Ii][Nn][Gg] 

/* Ref */
REF [Rr][Ee][Ff]

/* Scope */
SCOPE [Ss][Cc][Oo][Pp][Ee]
CLASS [Cc][Ll][Aa][Ss][Ss]
ASSOCIATION [Aa][Ss][Ss][Oo][Cc][Ii][Aa][Tt][Ii][Oo][Nn]
INDICATION [Ii][Nn][Dd][Ii][Cc][Aa][Tt][Ii][Oo][Nn]
QUALIFIER [Qq][Uu][Aa][Ll][Ii][Ff][Ii][Ee][Rr]
PROPERTY [Pp][Rr][Oo][Pp][Ee][Rr][Tt][Yy]
REFERENCE [Rr][Ee][Ff][Ee][Rr][Ee][Nn][Cc][Ee]
METHOD [Mm][Ee][Tt][Hh][Oo][Dd]
PARAMETER [Pp][Aa][Rr][Aa][Mm][Ee][Tt][Ee][Rr]
ANY [Aa][Nn][Yy]

/* Flavor */
FLAVOR [Ff][Ll][Aa][Vv][Oo][Rr]
ENABLEOVERRIDE [Ee][Nn][Aa][Bb][Ll][Ee][Oo][Vv][Ee][Rr][Rr][Ii][Dd][Ee]
DISABLEOVERRIDE [Dd][Ii][Ss][Aa][Bb][Ll][Ee][Oo][Vv][Ee][Rr][Rr][Ii][Dd][Ee]
RESTRICTED [Rr][Ee][Ss][Tt][Rr][Ii][Cc][Tt][Ee][Dd]
TOSUBCLASS [Tt][Oo][Ss][Uu][Bb][Cc][Ll][Aa][Ss][Ss]
TOINSTANCE [Tt][Oo][Ii][Nn][Ss][Tt][Aa][Nn][Cc][Ee]
TRANSLATABLE [Tt][Rr][Aa][Nn][Ss][Ll][Aa][Tt][Aa][Bb][Ll][Ee]

/* Instance of */
INSTANCE [Ii][Nn][Ss][Tt][Aa][Nn][Cc][Ee]
OF [Oo][Ff]

/* Object */
OBJECT [Oo][Bb][Jj][Ee][Cc][Tt]

/* Alias */
AS [Aa][Ss]

/* #pragma */
PRAGMA \#[Pp][Rr][Aa][Gg][Mm][Aa][ ]

/*
**==============================================================================
**
** Literal productions (see CIM Infrastructure specification).
**
**==============================================================================
*/

simpleChar \'[^\']\'
escapedChar \'\\[rntfb\"\'\\]\'
hexChar \'\\[xX][A-Fa-f0-9]+\'
realValue [+-]?[0-9]*\.[0-9]+([eE][+-]?[0-9]+)?
hexValue [+-]?0[xX][A-Fa-f0-9]+
decimalValue [+-]?[1-9][0-9]*
octalValue [+-]?0[0-7]+
binaryValue [+-]?[01]+[Bb]
blank [ \r\n\t]
identifier [A-Za-z_][A-Za-z_0-9]*
aliasIdentifier \$[A-Za-z_][A-Za-z_0-9]*
whiteSpaceChar [ \r\n\t\b\f]

/*
**------------------------------------------------------------------------------
**
** Lex productions:
**
**------------------------------------------------------------------------------
*/

%%

<<EOF>> {
    if (s_top == 0)
        yyterminate();
    else
    {
        if (closeIncludeFile() != 0)
            return TOK_ERROR;
    }
}

{TRUE} {
    yylval.boolean = 1;
    return TOK_BOOLEAN_VALUE; 
}

{FALSE} {
    yylval.boolean = 0;
    return TOK_BOOLEAN_VALUE; 
}

{NULL} {
    return TOK_NULL; 
}

{DT_BOOLEAN} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_BOOLEAN; 
}

{DT_SINT8} {
    return TOK_SINT8; 
}

{DT_UINT8} {
    return TOK_UINT8; 
}

{DT_SINT16} {
    return TOK_SINT16; 
}

{DT_UINT16} {
    return TOK_UINT16; 
}

{DT_SINT32} {
    return TOK_SINT32; 
}

{DT_UINT32} {
    return TOK_UINT32; 
}

{DT_SINT64} {
    return TOK_SINT64; 
}

{DT_UINT64} {
    return TOK_UINT64; 
}

{DT_REAL32} {
    return TOK_REAL32; 
}

{DT_REAL64} {
    return TOK_REAL64; 
}

{DT_DATETIME} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_DATETIME; 
}

{DT_CHAR16} {
    return TOK_CHAR16; 
}

{DT_STRING} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_STRING; 
}

{REF} {
    return TOK_REF; 
}

{SCOPE} {
    return TOK_SCOPE; 
}

{CLASS} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_CLASS; 
}

{ASSOCIATION} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_ASSOCIATION; 
}

{INDICATION} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_INDICATION; 
}

{QUALIFIER} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_QUALIFIER; 
}

{PROPERTY} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_PROPERTY; 
}

{REFERENCE} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_REFERENCE; 
}

{METHOD} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_METHOD; 
}

{PARAMETER} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_PARAMETER; 
}

{ANY} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_ANY;
}

{FLAVOR} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_FLAVOR;
}

{ENABLEOVERRIDE} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_ENABLEOVERRIDE;
}

{DISABLEOVERRIDE} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_DISABLEOVERRIDE;
}

{RESTRICTED} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_RESTRICTED;
}

{TOSUBCLASS} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_TOSUBCLASS;
}

{TOINSTANCE} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_TOINSTANCE;
}

{TRANSLATABLE} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_TRANSLATABLE;
}

{INSTANCE} {
    return TOK_INSTANCE;
}

{OF} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_OF;
}

{AS} {
    return TOK_AS;
}

{OBJECT} {
    return TOK_OBJECT;
}

{PRAGMA} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_PRAGMA;
}

\/\* {
    /* C-style comments */
    int c;
    int prev;

    /* Discard C-style comments. Replace with a single space since
     * comments may function as token separators.
     */

    for (c = input(), prev = '\0'; EOF != c; prev = c, c = input())
    {
        /* Check for closing comment */
        if (prev == '*' && c == '/')
            break;

        /* Increment line counter on newlines */
        if (c == '\n')
            state.line++;
    }

    /* Inject a blank character into input */
    unput(' ');
}

\/\/ {
    /* C++-style comments */
    int c;

    /* Discard all characters on this comment line including the newline */

    for (c = input(); EOF != c; c = input())
    {
        /* Increment line counter on newlines */
        if (c == '\n')
        {
            state.line++;
            break;
        }
    }
}

\" {
    /* Read a string literal */
    int c;
    Buffer buf = BUFFER_INITIALIZER;

    /* Scan until the closing quote is found */
    for (;;)
    {
        c = input();

        if (EOF == c || c == '"')
            break;

        if (Buffer_AppendChar(&buf, (char)c) != 0)
        {
            yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
            return TOK_ERROR;
        }

        /* If backslash, get next character */
        if (c == '\\')
        {
            c = input();

            if (EOF == c)
            {
                yyerrorf(ID_UNTERMINATED_STRING_LITERAL, 
                    "unterminated string literal");
                return TOK_ERROR;
            }

            if (Buffer_AppendChar(&buf, (char)c) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return TOK_ERROR;
            }
        }
    }

    /* Append zero-terminator */
    if (Buffer_AppendChar(&buf, '\0') != 0)
    {
        yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
        return TOK_ERROR;
    }

    /* Return the string */
    yylval.string = buf.data;
    return TOK_STRING_VALUE;
}

{simpleChar} {
    yylval.character = yytext[1];
    return TOK_CHAR_VALUE;
}

{escapedChar} {

    switch (yytext[2])
    {
	case 'r':
	    yylval.character = '\r';
	    break;
	case 'n':
	    yylval.character = '\n';
	    break;
	case 't':
	    yylval.character = '\t';
	    break;
	case 'f':
	    yylval.character = '\f';
	    break;
	case 'b':
	    yylval.character = '\b';
	    break;
	case '\"':
	    yylval.character = '"';
	    break;
	case '\'':
	    yylval.character = '\'';
	    break;
	case '\\':
	    yylval.character = '\\';
	    break;
        default:
            yyerrorf(ID_INTERNAL_ERROR, "internal error");
            return TOK_ERROR;
    }

    return TOK_CHAR_VALUE;
}

{hexChar} {
    char* end;

    if (yyleng - 4 > 4)
    {
        yyerrorf(ID_ILLEGAL_HEX_CHARACTER, "illegal hex character");
        return TOK_ERROR;
    }

    yylval.character = (MI_Char16)strtoul(&yytext[3], &end, 16);

    if (*end != '\'')
    {
        yyerrorf(ID_ILLEGAL_HEX_CHARACTER, "illegal hex character");
        return TOK_ERROR;
    }

    return TOK_CHAR_VALUE;
}

[+-]?0 {
    yylval.integer = 0;
    return TOK_INTEGER_VALUE;
}

{decimalValue} {
    errno = 0;
    if (yytext[0] == '-')
        yylval.integer = (MI_Sint64)Strtoll(yytext, NULL, 10);
    else
        yylval.integer = (MI_Sint64)Strtoull(yytext, NULL, 10);
    
    if (errno == ERANGE)
    {
        yyerrorf(ID_INTEGER_OVERFLOW, "integer overflow");
        return TOK_ERROR;
    }
    return TOK_INTEGER_VALUE;
}

{realValue} {
    yylval.real = (double)strtod(yytext, NULL);
    return TOK_REAL_VALUE;
}

{hexValue} {
    errno = 0;
    if (yytext[0] == '-')
        yylval.integer = (MI_Sint64)Strtoll(yytext, NULL, 16);
    else
        yylval.integer = (MI_Sint64)Strtoull(yytext, NULL, 16);
    
    if (errno == ERANGE)
    {
        yyerrorf(ID_INTEGER_OVERFLOW, "integer overflow");
        return TOK_ERROR;
    }
    return TOK_INTEGER_VALUE;
}

{octalValue} {
    errno = 0;
    if (yytext[0] == '-')
        yylval.integer = (MI_Sint64)Strtoll(yytext, NULL, 8);
    else
        yylval.integer = (MI_Sint64)Strtoull(yytext, NULL, 8);
    
    if (errno == ERANGE)
    {
        yyerrorf(ID_INTEGER_OVERFLOW, "integer overflow");
        return TOK_ERROR;
    }
    return TOK_INTEGER_VALUE;
}

{binaryValue} {
    char* end;

    if (yytext[0] == '-')
        yylval.integer = (MI_Sint64)Strtoll(yytext, &end, 2);
    else
        yylval.integer = (MI_Sint64)Strtoull(yytext, &end, 2);

    if (*end != 'B' && *end != 'b')
    {
        yyerrorf(ID_ILLEGAL_BINARY_LITERAL, "illegal binary literal");
        return TOK_ERROR;
    }
    if (errno == ERANGE)
    {
        yyerrorf(ID_INTEGER_OVERFLOW, "integer overflow");
        return TOK_ERROR;
    }

    return TOK_INTEGER_VALUE;
}

{identifier} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_IDENT;
}

{aliasIdentifier} {
    yylval.identifier = MOF_Strdup(&state.heap, yytext);
    return TOK_ALIAS_IDENTIFIER;
}

\= {
    return '=';
}

\( {
    return '(';
}

\) {
    return ')';
}

\[ {
    return '[';
}

\] {
    return ']';
}

\{ {
    return '{';
}

\} {
    return '}';
}

\: {
    return ':';
}

\; {
   return ';';
}

\, {
    return ',';
}

{whiteSpaceChar}+ {
    /* swallow whiteSpaceChar */
    int i;

    for (i = 0; i < yyleng; i++)
    {
        if (yytext[i] == '\n')
            state.line++;
    }
}

. {
    yyterminate();
}

%%

/*
**==============================================================================
**
** Function definitions
**
**==============================================================================
*/

int yywrap()
{
    /* Return 1 to indicate the end of input */
    return 1;
}

static int exists(const char* path)
{
    if (access(path, R_OK) != 0)
        return -1;

    return 0;
}

static char* findIncludeFile(const char* path)
{
    /* First attempt to locate the file relative to the one that included it */
    {
        Buffer buf = BUFFER_INITIALIZER;
        char* p;

        p = strrchr(state.path, '/');

        if (p)
        {
            if (Buffer_Append(&buf, state.path, p - state.path + 1) != 0)
                return NULL;
        }

        if (Buffer_Append(&buf, path, strlen(path) + 1) != 0)
            return NULL;

        if (exists((const char*)buf.data) == 0)
            return (char*)buf.data;
    }

    /* Attempt to open the file relative to the current directory */
    {
        if (exists(path) == 0)
            return MOF_Strdup(&state.heap, path);
    }

    /* Search for file using include path array */
    {
        size_t i;
        for (i = 0; i < state.paths.size; i++)
        {
            const char* p = (const char*)state.paths.data[i];
            Buffer buf = BUFFER_INITIALIZER;

            if (Buffer_Append(&buf, p, strlen(p)) != 0)
                return NULL;

            if (Buffer_AppendChar(&buf, '/') != 0)
                return NULL;

            if (Buffer_Append(&buf, path, strlen(path) + 1) != 0)
                return NULL;

            if (exists((char*)buf.data) == 0)
                return (char*)buf.data;

            MOF_Free(&state.heap, buf.data);
        }
    }

    /* Not found */
    return NULL;
}

int openIncludeFile(const char* path_)
{
    FILE* is;
    char* path;

    if ((path = findIncludeFile(path_)) == NULL)
    {
        yyerrorf(ID_FAILED_TO_FIND_INCLUDE_FILE, 
            "failed to find include file: \"%s\"", path_);
        return -1;
    }

    /* Check for stack overflow. */
    if (s_top >= MOF_STACK_SIZE)
    {
        yyerrorf(ID_MOF_STACK_OVERFLOW, "MOF file stack overflow");
        return -1;
    }

    /* Open the file */
    if ((is = File_Open(path, "rb")) == NULL)
    {
        yyerrorf(ID_FAILED_TO_OPEN_FILE, "failed to open file: \"%s\"", path);
        return -1;
    }

    /* Push current state onto stack. */
    s_stack[s_top].file = state.path;
    s_stack[s_top].line = state.line;
    s_stack[s_top].buffer = YY_CURRENT_BUFFER;
    s_top++;

    /* Setup state for new file */
    yy_switch_to_buffer(yy_create_buffer(is, YY_BUF_SIZE));
    state.path = MOF_Strdup(&state.heap, path);
    state.line = 1;

    return 0;
}

int closeIncludeFile()
{
    /* Check for stack underflow. */
    if (s_top == 0)
    {
        yyerrorf(ID_MOF_STACK_UNDERFLOW, "MOF file stack underflow");
        return -1;
    }

    /* Release current state */
    MOF_Free(&state.heap, state.path);
    fclose(YY_CURRENT_BUFFER->yy_input_file);
    yy_delete_buffer(YY_CURRENT_BUFFER);

    /* Restore state from top of stack */
    s_top--;
    state.path = s_stack[s_top].file;
    state.line = s_stack[s_top].line;
    yy_switch_to_buffer(s_stack[s_top].buffer);

    return 0;
}

/*
**==============================================================================
**
** MOF_Parser
**
**==============================================================================
*/

MOF_Parser* MOF_Parser_New(
    const char* const* paths,
    size_t numPaths)
{
    MOF_Parser* self = (MOF_Parser*)PAL_Calloc(1, sizeof(MOF_Parser));
    size_t i;
    char* str;

    if (!self)
        return NULL;

    for (i = 0; i < numPaths; i++)
    {
        str = MOF_Strdup(&self->state.heap, paths[i]);

        if (!str)
        {
            MOF_Release(&self->state.heap);
            PAL_Free(self);
            return NULL;
        }

        /* PtrArray_Append() uses the global state's heap object to
         * obtain memory, so install self->state as the global state
         * object temporarily.
         */
        {
            state = self->state;
            PtrArray_Append(&state.paths, str);
            self->state = state;
            memset(&state, 0, sizeof(state));
        }
    }

    return self;
}

void MOF_Parser_SetErrorCallback(
    MOF_Parser* self, 
    void (*callback)(const char* msg, const wchar_t* wmsg, void* data),
    void* data)
{
    if (self)
    {
        self->state.errorCallback = callback;
        self->state.errorCallbackData = data;
    }
}

void MOF_Parser_SetWarningCallback(
    MOF_Parser* self, 
    void (*callback)(const char* msg, const wchar_t* wmsg, void* data),
    void* data)
{
    if (self)
    {
        self->state.warningCallback = callback;
        self->state.warningCallbackData = data;
    }
}

void MOF_Parser_SetPragmaCallback(
    MOF_Parser* self, 
    void (*callback)(const char* pragma, const char* value, void* data),
    void* data)
{
    if (self)
    {
        self->state.pragmaCallback = callback;
        self->state.pragmaCallbackData = data;
    }
}

void MOF_Parser_SetClassDeclCallback(
    MOF_Parser* self, 
    void (*callback)(const MI_ClassDecl* decl, void* data),
    void* data)
{
    if (self)
    {
        self->state.classDeclCallback = callback;
        self->state.classDeclCallbackData = data;
    }
}

void MOF_Parser_SetInstanceDeclCallback(
    MOF_Parser* self, 
    void (*callback)(const MI_InstanceDecl* decl, void* data),
    void* data)
{
    if (self)
    {
        self->state.instanceDeclCallback = callback;
        self->state.instanceDeclCallbackData = data;
    }
}

void MOF_Parser_SetQualifierDeclCallback(
    MOF_Parser* self, 
    void (*callback)(const MI_QualifierDecl* decl, void* data),
    void* data)
{
    if (self)
    {
        self->state.qualifierDeclCallback = callback;
        self->state.qualifierDeclCallbackData = data;
    }
}

void MOF_Parser_Delete(MOF_Parser* self)
{
    if (self)
    {
        MOF_Release(&self->state.heap);
        PAL_Free(self);
    }
}

/* Handle multiple calls to this function */
int MOF_Parser_Parse(MOF_Parser* self, const char* path)
{
    /* Reject null parameters */
    if (!self || !path)
        return -1;

    /* Clear stack */
    s_top = 0;

    /* Set global state */
    state = self->state;

    /* Open input */
    yyin = File_Open(path, "rb");

    if (!yyin)
    {
        yyerrorf(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path);
        self->state = state;
        memset(&state.heap, 0, sizeof(state));
        return -1;
    }

    /* Save path */
    state.path = MOF_Strdup(&state.heap, path);

    /* Set initialize line number */
    state.line = 1;

    /* Clear the parser state */
    yy_c_buf_p = 0;
    yy_last_accepting_cpos = 0;
    yy_init = 1;

    /* Run the parser */
    if (yyparse() != 0)
    {
        fclose(yyin);
        yy_delete_buffer(YY_CURRENT_BUFFER);
        self->state = state;
        memset(&state.heap, 0, sizeof(state));
        return -1;
    }

    /* Perform post processing (which requires first pass completion) */
    if (PerformPostProcessing() != 0)
    {
        fclose(yyin);
        yy_delete_buffer(YY_CURRENT_BUFFER);
        self->state = state;
        memset(&state.heap, 0, sizeof(state));
        return -1;
    }

    /* Close stream and release parse buffer */
    fclose(yyin);
    yy_delete_buffer(YY_CURRENT_BUFFER);

    /* Restore state */
    self->state = state;
    memset(&state.heap, 0, sizeof(state));

    return 0;
}

/* Parse a MOF string */
int MOF_Parser_ParseString(MOF_Parser* self, const char* mof_string)
{
    YY_BUFFER_STATE bp;

    /* Reject null parameters */
    if (!self || !mof_string)
        return -1;

    /* Clear stack */
    s_top = 0;

    /* Set global state */
    state = self->state;

    /* Save path */
    state.path = MOF_Strdup(&state.heap, "MOF string");

    /* Set initialize line number */
    state.line = 1;

    /* Clear the parser state */
    yy_c_buf_p = 0;
    yy_last_accepting_cpos = 0;
    yy_init = 1;

    /* Run the parser */
    bp = yy_scan_string(mof_string);
    yy_switch_to_buffer(bp);
    if (yyparse() != 0)
    {
        yy_delete_buffer(bp);
        self->state = state;
        memset(&state.heap, 0, sizeof(state));
        return -1;
    }

    /* Perform post processing (which requires first pass completion) */
    if (PerformPostProcessing() != 0)
    {
        yy_delete_buffer(bp);
        self->state = state;
        memset(&state.heap, 0, sizeof(state));
        return -1;
    }

    /* Close stream and release parse buffer */
    yy_delete_buffer(bp);

    /* Restore state */
    self->state = state;
    memset(&state.heap, 0, sizeof(state));

    return 0;
}

void MOF_Parser_Dump(MOF_Parser* self, FILE* file)
{
    size_t i;

    for (i = 0; i < self->state.qualifierDecls.size; i++)
        MOF_PrintQualifierDecl(self->state.qualifierDecls.data[i], file);

    for (i = 0; i < self->state.classDecls.size; i++)
        MOF_PrintClassDecl(self->state.classDecls.data[i], file);

    for (i = 0; i < self->state.instanceDecls.size; i++)
        MOF_PrintInstanceDecl(self->state.instanceDecls.data[i], file);
}

void MOF_Parser_EnableExtensions(MOF_Parser* self, MI_Boolean enabled)
{
    self->state.extensionsEnabled = enabled;
    return;
}
