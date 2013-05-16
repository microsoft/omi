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

#include "Parser.h"

extern "C" void errorCallback(
    const char* msg, 
    const wchar_t* wmsg, 
    void* data)
{
    MI_UNUSED(data);

#if defined(_MSC_VER)
    if (wmsg)
    {
        fwprintf(stderr, L"%s\n", wmsg);
    }
    else
#endif
    {
        fprintf(stderr, "%s\n", msg);
    }

    exit(1);
}

extern "C" void warningCallback(
    const char* msg, 
    const wchar_t* wmsg, 
    void* data)
{
    Parser* parser = (Parser*)data;

    if (parser->m_warnings)
    {
#if defined(_MSC_VER)
        if (wmsg)
        {
            fwprintf(stderr, L"%s\n", wmsg);
        }
        else
#endif
        {
            fprintf(stderr, "%s\n", msg);
        }
    }
}

extern "C" void pragmaCallback(
    const char* /*pragma*/, 
    const char* /*value*/, 
    void* /*data*/)
{
}

extern "C" void classDeclCallback(const MI_ClassDecl* decl, void* data)
{
    Parser* parser = (Parser*)data;
    parser->m_classDecls.insert(Parser::ClassDeclPair(decl->name, decl));
}

extern "C" void qualifierDeclCallback(const MI_QualifierDecl* decl, void* data)
{
    Parser* parser = (Parser*)data;
    parser->m_qualifierDecls.insert(
	Parser::QualifierDeclPair(decl->name, decl));
}

Parser::Parser(const std::vector<std::string>& paths, bool warnings) :
    m_warnings(warnings)
{
    char** tmp = new char*[paths.size()];

    for (size_t i = 0; i < paths.size(); i++)
        tmp[i] = (char*)paths[i].c_str();

    m_parser = MOF_Parser_New(tmp, paths.size());
    delete [] tmp;

    MOF_Parser_SetErrorCallback(m_parser, (MOF_ErrorCallback)errorCallback, 
	this);
    MOF_Parser_SetWarningCallback(m_parser, 
	(MOF_WarningCallback)warningCallback, this);
    MOF_Parser_SetPragmaCallback(m_parser, (MOF_PragmaCallback)pragmaCallback, 
	this);
    MOF_Parser_SetClassDeclCallback(m_parser, 
	(MOF_ClassDeclCallback)classDeclCallback, this);
    MOF_Parser_SetQualifierDeclCallback(m_parser, 
	(MOF_QualifierDeclCallback)qualifierDeclCallback, this);
}

int Parser::parse(const char* path)
{
    return MOF_Parser_Parse(m_parser, path);
}

const MI_ClassDecl* Parser::findClassDecl(const std::string& name) const
{
    ClassDeclMap::const_iterator pos = m_classDecls.find(name);

    if (pos == m_classDecls.end())
        return NULL;

    return (*pos).second;
}

void Parser::getClassNames(std::vector<std::string>& names) const
{
    names.clear();

    ClassDeclMap::const_iterator p = m_classDecls.begin();
    ClassDeclMap::const_iterator end = m_classDecls.end();

    for (; p != end; p++)
    {
        names.push_back((*p).first);
    }
}

const MI_QualifierDecl* Parser::findQualifierDecl(const std::string& name) const
{
    QualifierDeclMap::const_iterator pos = m_qualifierDecls.find(name);

    if (pos == m_qualifierDecls.end())
        return NULL;

    return (*pos).second;
}

void Parser::getQualifierDeclNames(std::vector<std::string>& names) const
{
    QualifierDeclMap::const_iterator first = m_qualifierDecls.begin();
    QualifierDeclMap::const_iterator last = m_qualifierDecls.end();

    while (first != last)
    {
        names.push_back((*first).first);
        first++;
    }
}

Parser::~Parser()
{
    MOF_Parser_Delete(m_parser);
}
