/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mofcxx_mofcxx_h
#define _mofcxx_mofcxx_h

#if defined(MI_CHAR_TYPE) && (MI_CHAR_TYPE != 1)
# error "MI_CHAR_TYPE must be equal to 1"
#endif

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <vector>
#include <string>

#include <MI.h>
#include <mof/mof.h>

//==============================================================================
//
// MOFCXX_EXPORT
// MOFCXX_IMPORT
// MOFCXX_LINKAGE
//
//==============================================================================

#if defined(_MSC_VER)
# define MOFCXX_EXPORT __declspec(dllexport)
# define MOFCXX_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define MOFCXX_EXPORT __attribute__((visibility("default")))
# define MOFCXX_IMPORT /* empty */
#elif defined(sun)
# define MOFCXX_EXPORT __global
# define MOFCXX_IMPORT /* empty */
#else
# define MOFCXX_EXPORT
# define MOFCXX_IMPORT
#endif

#ifdef BUILDING_MOFCXX
#  define MOFCXX_LINKAGE MOFCXX_EXPORT
#else
#  define MOFCXX_LINKAGE MOFCXX_IMPORT
#endif

//==============================================================================
//
// MOFCXX_BEGIN
// MOFCXX_END
//
//==============================================================================

#define MOFCXX_BEGIN namespace mofcxx {
#define MOFCXX_END }

//==============================================================================
//
// MOFParserHandler
//
//==============================================================================

MOFCXX_BEGIN

class MOFCXX_LINKAGE MOFParserHandler
{
public:

    virtual ~MOFParserHandler();

    virtual void HandleError(const char* msg);

    virtual void HandleWarning(const char* msg);

    virtual void HandlePragma(const char* name, const char* value);

    virtual void HandleClassDecl(const MI_ClassDecl* decl);

    virtual void HandleInstanceDecl(const MI_InstanceDecl* decl);

    virtual void HandleQualifierDecl(const MI_QualifierDecl* decl);
};

MOFCXX_END

//==============================================================================
//
// MOFParser
//
//     This class is used to parse MOF (Managed Object Format) files. A MOF
//     parser encounters four kinds of entities:
//
//         - class declarations
//         - instance declarations
//         - qualifier declarations
//         - pragma expressions
//
//     The following code fragment shows how to parse a MOF file.
//
//         class Handler : public MOFParserHandler
//         {
//         public:
//
//             virtual ~Handler()
//             {
//             }
//
//             virtual void HandleError(const char* msg)
//             {
//             }
//
//             virtual void HandleWarning(const char* msg)
//             {
//             }
//
//             virtual void HandlePragma(const char* name, const char* value)
//             {
//             }
//
//             virtual void HandleClassDecl(const MI_ClassDecl* decl)
//             {
//             }
//
//             virtual void HandleInstanceDecl(const MI_InstanceDecl* decl)
//             {
//             }
//
//             virtual void HandleQualifierDecl(const MI_QualifierDecl* decl)
//             {
//             }
//         };
//
//         ...
//
//         vector<string> paths;
//         paths.push_back(".");
//
//         Handler* handler = new Handler;
//         MOFParser parser(paths, handler);
//         parser.Parse("sample.mof");
//         delete handler;
//
//     The 'paths' variable specifies search paths for included MOF files. For
//     example, a MOF file may include a pragma expression like this:
//
//         #pragma include("abc/xyz.mof")
//
//     In this example, we tell the parser to search for included files in the
//     current directory.
//
//     The user must define a handler (which derives from MOFParserHandler)
//     and pass an instance to the parser. The virtual functions are called
//     as entities are encountered (class, instance, and qualifier declarations)
//     and in response to errors and warnings. The user is responsible for
//     deleting the handler.
//
//     The MOF parser is not reentrant (since it is based on Lex/YACC), so
//     access to the MOFParser::Parse() method is serialized using a mutex.
//
//     MOFParser::DumpClassDecl() and MOFParser::DumpInstanceDecl() print
//     class declarations and instance declarations, respectively, to a FILE
//     stream.
//
//==============================================================================

typedef struct _MOF_Parser MOF_Parser;

MOFCXX_BEGIN

class MOFCXX_LINKAGE MOFParser
{
public:

    MOFParser(std::vector<std::string>& paths, MOFParserHandler* handler);

    ~MOFParser();

    int Parse(const char* path);

    int ParseString(const char* mof_string);

    void Dump(FILE* os = stdout);

    static void DumpClassDecl(const MI_ClassDecl* decl, FILE* os);

    static void DumpInstanceDecl(const MI_InstanceDecl* decl, FILE* os);

private:
    MOFParser(const MOFParser&);
    MOFParser& operator=(const MOFParser&);

    MOF_Parser* m_parser;
    MOFParserHandler* m_handler;
};

MOFCXX_END

#endif /* _mofcxx_mofcxx_h */
