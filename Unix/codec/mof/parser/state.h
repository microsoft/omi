/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_state_h
#define _mof_state_h

#include <base/batch.h>
#include <codec/common/micodec.h>
#include "ptrarray.h"
#include "types.h"
#include "mofparser.h"
#include "mofyacc.h"
#include "errorhandler.h"
#include "mofhash.h"

/*
**==============================================================================
**
** MOF_ENCODING_TYPE
**  Buffer Encoding Type
**
**==============================================================================
*/
typedef enum _MOF_ENCODING_TYPE
{
    ANSI,
    UNI,
    UNIBE,
    UTF8,
    UTF16LE,
    UTF16BE
}MOF_ENCODING_TYPE;

/*
**==============================================================================
**
** MOF_Encoding
**  Buffer Encoding Structure, contains encoding type; offset of mof data;
**  and indication of buffer is unicode or ansi
**
**==============================================================================
*/
typedef struct _MOF_Encoding
{
    MI_Uint8 t; /* encoding type */
    MI_Uint8 o; /* offset from beginning */
    MI_Boolean u; /* unicode or not*/
}MOF_Encoding;

/*
**==============================================================================
**
** MOF_Buffer
**  Contains state of mof buffer to be parsed, it maintains original buffer
**  start address, current buffer pointer, current line no, etc.
**
**==============================================================================
*/
typedef struct _MOF_Buffer
{
    /* Mof Buffer, e describes the encoding */
    void * buf;

    /* Buffer length*/
    MI_Uint32 len;

    /* Buffer end position */
    /* If cur == end, then reach the end of the buffer */
    void * end;

    /* Pointer to current char */
    void * cur;

    /* Current Line no */
    MI_Uint32 lineNo;

    /* Char postion of current line */
    MI_Uint32 charPosOfLine;

    /* Encoding of buffer */
    MOF_Encoding e;

    /* Last token start line */
    MI_Uint32 llineNo;

    /* Last token start char */
    MI_Uint32 lcharPosOfLine;
}MOF_Buffer;

/*
** Copied from generated mofy.tab.c file.
** DO NOT TOUCH THIS STRUCTURE.
*/
typedef struct {
        unsigned stacksize;
        short    *s_base;
        short    *s_mark;
        short    *s_last;
        YYSTYPE  *l_base;
        YYSTYPE  *l_mark;
} YYSTACKDATA;

/*
** Struct for making generated YACC code thread safe.
** DO NOT TOUCH THIS STRUCTURE.
*/
typedef struct _MOF_YACC_STATE
{
    int      mofdebug;
    int      mofnerrs;
    int      moferrflag;
    int      mofchar;
    YYSTYPE  mofval;
    YYSTYPE  moflval;

    /* variables for the parser stack */
    YYSTACKDATA mofstack;
}MOF_YACC_STATE;

/*
**==============================================================================
**
** MOF_State_InternalState
**
**     This structure was used for temporary data exchange purpose.
**     (1) FinalizeInstance function might want to know if the classdecl
**          of the instance come from input parameter or from deserialized
**          buffer;
**
**==============================================================================
*/
typedef struct _MOF_State_InternalState
{
    MI_Boolean isClassDeclFromBuffer;
}MOF_State_InternalState;


/*
**==============================================================================
**
** MOF_State
**
**     This structure maintains the static parser state for the current parser
**     invocation. It maintains the heap, errors, warnings, instance declarations,
**     class declarations, and qulifier declarations.
**
**==============================================================================
*/
typedef struct _MOF_State
{
    /* The parser object owning this state object */
    MOF_Parser * parser;

    /* Batch allocator for the state */
    Batch * batch;

    /* Current Mof buffer */
    MOF_Buffer buf;

    /* Mof buffer stack */
    MOF_Buffer *bufStack;
    MI_Uint32 bufTop;

    /* State data for MOF YACC, do not touch this field */
    MOF_YACC_STATE ystate;

    /* Last instance alias line no */
    MI_Uint32 lastAliasDeclLineNo;

    /* Name of file being parsed */
    MI_Char* path;

    /* Maintains a list of errors encountered during parsing */
    PtrArray errors;

    /* Maintains a list of warnings encountered during parsing */
    PtrArray warnings;

    /* Maintains a list of class declarations processed during parsing */
    MOF_ClassDeclList classDecls;

    /* Maintains a hash structure for quick search of class */
    StringHash classDeclsHash;

    /* Maintains a list of instance declarations processed during parsing */
    MOF_InstanceDeclList instanceDecls;
    
    /* Maintains a list of instance alias */
    MOF_InstanceAliasList instanceAliases;

    /* Maintains a hash structure for quick search of class */
    StringHash instanceAliasesHash;

    /* Maintains a list of qualifier declarations processed during parsing */
    MOF_QualifierDeclList qualifierDecls;

    /* Track of EmbeddedInstances qualifiers for post processing */
    MOF_EmbeddedInstanceList embeddedInstanceList;

    /* Paths to search when attempting to locate included files */
    /* PtrArray paths; */

    /* Error handler */
    MOF_ErrorHandler *errhandler;

    /* A copy of classdecl needed */
    void* onNewClassDeclData;
    MI_Result (MI_CALL *onNewClassDecl)(
        _In_ void * data,
        _In_ const MI_ClassDecl* classDecl,
        _Outptr_result_maybenull_ MI_ClassDecl** newClassDecl);

    /* Create dynamic instance */
    void (MI_CALL *onAliasDeclared)(_In_ void *state);

    /* Create static instance */
    Instance_NewFunc Instance_New;

    /* Create dynamic instance */
    MI_Result (MI_CALL *Instance_InitDynamic)(
        _In_z_ const MI_Char* className,
        _In_ MI_Uint32 metaType,
        _Outptr_result_maybenull_ MI_Instance** self);

    /* User callback to invoke when a pragma is recognized */
    void (*pragmaCallback)(const MI_Char* pragma, const MI_Char* value, void* data);
    void* pragmaCallbackData;

    /* Buffer for parser temporary usage */
    _Field_size_(MSG_SIZE) MI_Char buffer[MSG_SIZE];

    /* Internal state object  */
    MOF_State_InternalState internalstate;
}MOF_State;


// PRINTF_FORMAT(3, 4)
extern void yyerrorf(_In_ MOF_ErrorHandler *errhandler, int id, _In_z_ const char *fmt, ...);

#define mof_report_error yyerrorf

#endif /* _mof_state_h */
