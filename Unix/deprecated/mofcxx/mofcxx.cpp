/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "mofcxx.h"
#include <mof/mof.h>

#ifndef _MSC_VER
# include <pthread.h>
#endif

extern "C" void MOF_PrintClassDecl(
    const MI_ClassDecl* self,
    FILE* file);

extern "C" void MOF_PrintInstanceDecl(
    const MI_InstanceDecl* self,
    FILE* file);

using namespace mofcxx;

//==============================================================================
//
// Mutex
//
//==============================================================================

#ifndef _MSC_VER
static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

//==============================================================================
//
// Callbacks
//
//==============================================================================

extern "C" void errorCallback(
    const char* msg,
    const wchar_t* wmsg,
    void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandleError(msg);
}

extern "C" void warningCallback(
    const char* msg,
    const wchar_t* wmsg,
    void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandleWarning(msg);
}

extern "C" void pragmaCallback(
    const char* name,
    const char* value,
    void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandlePragma(name, value);
}

extern "C" void classDeclCallback(const MI_ClassDecl* decl, void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandleClassDecl(decl);
}

extern "C" void instanceDeclCallback(const MI_InstanceDecl* decl, void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandleInstanceDecl(decl);
}

extern "C" void qualifierDeclCallback(const MI_QualifierDecl* decl, void* data)
{
    MOFParserHandler* handler = (MOFParserHandler*)data;
    handler->HandleQualifierDecl(decl);
}

//==============================================================================
//
// MOFParserHandler
//
//==============================================================================

MOFCXX_BEGIN

MOFParserHandler::~MOFParserHandler()
{
}

void MOFParserHandler::HandleError(const char* msg)
{
}

void MOFParserHandler::HandleWarning(const char* msg)
{
}

void MOFParserHandler::HandlePragma(const char* name, const char* value)
{
}

void MOFParserHandler::HandleClassDecl(const MI_ClassDecl* decl)
{
}

void MOFParserHandler::HandleInstanceDecl(const MI_InstanceDecl* decl)
{
}

void MOFParserHandler::HandleQualifierDecl(const MI_QualifierDecl* decl)
{
}

MOFCXX_END

//==============================================================================
//
// MOFParser
//
//==============================================================================

MOFCXX_BEGIN

MOFParser::MOFParser(
    std::vector<std::string>& paths,
    MOFParserHandler* handler) : m_handler(handler)
{
    char** tmp = new char*[paths.size()];

    for (size_t i = 0; i < paths.size(); i++)
        tmp[i] = (char*)paths[i].c_str();

    m_parser = MOF_Parser_New(tmp, paths.size());
    delete [] tmp;

    MOF_Parser_EnableExtensions(m_parser, MI_TRUE);

    MOF_Parser_SetPragmaCallback(
        m_parser,
        (MOF_PragmaCallback)pragmaCallback,
	m_handler);

    MOF_Parser_SetErrorCallback(
        m_parser,
        (MOF_ErrorCallback)errorCallback,
        m_handler);

    MOF_Parser_SetWarningCallback(
        m_parser,
	(MOF_WarningCallback)warningCallback,
        m_handler);

    MOF_Parser_SetClassDeclCallback(
        m_parser,
	(MOF_ClassDeclCallback)classDeclCallback,
        m_handler);

    MOF_Parser_SetInstanceDeclCallback(
        m_parser,
	(MOF_InstanceDeclCallback)instanceDeclCallback,
        m_handler);

    MOF_Parser_SetQualifierDeclCallback(
        m_parser,
	(MOF_QualifierDeclCallback)qualifierDeclCallback,
        m_handler);
}

MOFParser::~MOFParser()
{
    MOF_Parser_Delete(m_parser);
}

int MOFParser::Parse(const char* path)
{
#ifndef _MSC_VER
    /* Acquire mutex to synchronize access to global Lex/Yacc state */
    pthread_mutex_lock(&_mutex);
#endif

    int r = -1;
    try
    {
        r = MOF_Parser_Parse(m_parser, path);
    }
    catch(...)
    {
       // Not really sure what to do here, but it should probably be something
    }

#ifndef _MSC_VER
    /* Release mutex */
    pthread_mutex_unlock(&_mutex);
#endif

    return r;
}

int MOFParser::ParseString(const char* mof_string)
{
#ifndef _MSC_VER
    /* Acquire mutex to synchronize access to global Lex/Yacc state */
    pthread_mutex_lock(&_mutex);
#endif
    int r = -1;
    try
    {
        r = MOF_Parser_ParseString(m_parser, mof_string);
    }
    catch(...)
    {
       // Not really sure what to do here, but it should probably be something
    }

#ifndef _MSC_VER
    /* Release mutex */
    pthread_mutex_unlock(&_mutex);
#endif

    return r;
}

void MOFParser::Dump(FILE* os)
{
    return MOF_Parser_Dump(m_parser, os);
}

void MOFParser::DumpClassDecl(const MI_ClassDecl* decl, FILE* os)
{
    MOF_PrintClassDecl(decl, os);
}

void MOFParser::DumpInstanceDecl(const MI_InstanceDecl* decl, FILE* os)
{
    MOF_PrintInstanceDecl(decl, os);
}

MOFCXX_END
