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

#ifndef _Parser_h
#define _Parser_h

#include <string>
#include <vector>
#include <map>
#include <mof/mof.h>
#include <pal/strings.h>

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <common.h>

extern "C" void errorCallback(
    const char* msg, 
    const wchar_t* wmsg, 
    void*);

extern "C" void warningCallback(
    const char* msg, 
    const wchar_t* wmsg, 
    void*);

extern "C" void pragmaCallback(
    const char* pragma, 
    const char* value, 
    void*);

extern "C" void classDeclCallback(
    const MI_ClassDecl* decl, void*);

extern "C" void qualifierDeclCallback(
    const MI_QualifierDecl* decl, 
    void*);

//==============================================================================
//
// Parser
//     This class wraps the MOF parser adding data structures for maintaining
//     parsed entities and for looking up those entities.
//
//==============================================================================

class Parser
{
public:

    // Construct a parser that looks for MOF inclusions on these paths.
    Parser(const std::vector<std::string>& paths, bool warnings);

    // Parse the MOF file and return 0 on success.
    int parse(const char* path);

    // Return a pointer to the class declaration with the given name (or NULL
    // if not found).
    const MI_ClassDecl* findClassDecl(const std::string& name) const;

    // Return an array of all classnames.
    void getClassNames(std::vector<std::string>& names) const;

    // Return a pointer to the qualifier declaration with the given name 
    // (or NULL if not found).
    const MI_QualifierDecl* findQualifierDecl(const std::string& name) const;

    // Get a list of qualifier declaration names.
    void getQualifierDeclNames(std::vector<std::string>& names) const;

    // Destruct the parser (cleaning up whole parser tree and pointers to
    // objects returned from findClassDecl() and findQualifierDecl().
    ~Parser();

private:

    // Hide the copy constructor.
    Parser(const Parser&);

    // Hide the assignment operator.
    Parser& operator=(const Parser&);

    // Callbacks invoked by the C MOF parser.
    friend void errorCallback(const char* msg, const wchar_t* wmsg, void*);
    friend void warningCallback(const char* msg, const wchar_t* wmsg, void*);
    friend void pragmaCallback(const char* pragma, const char* value, void*);
    friend void classDeclCallback(const MI_ClassDecl* decl, void*);
    friend void qualifierDeclCallback(const MI_QualifierDecl* decl, void*);

    // Instance of C MOF parser.
    MOF_Parser* m_parser;

    // Functor to make map string comparison case insentisive.
    struct Less
    {
        bool operator()(const std::string& x, const std::string& y) const
        {
            return Strcasecmp(x.c_str(), y.c_str()) < 0;
        }
    };

    // Print warnings if true.
    bool m_warnings;

    // Map of qualifier declaration encountered during parsing.
    typedef std::map<std::string, const MI_QualifierDecl*, Less> 
        QualifierDeclMap;
    typedef std::pair<std::string, const MI_QualifierDecl*> QualifierDeclPair;
    QualifierDeclMap m_qualifierDecls;

    typedef std::pair<std::string, const MI_ClassDecl*> ClassDeclPair;
    typedef std::map<std::string, const MI_ClassDecl*, Less> ClassDeclMap;
    ClassDeclMap m_classDecls;
};

#endif /* _Parser_h */
