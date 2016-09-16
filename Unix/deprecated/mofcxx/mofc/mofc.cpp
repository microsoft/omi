/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <mofcxx/mofcxx.h>

using namespace mofcxx;
using namespace std;

class Handler : public MOFParserHandler
{
public:

    virtual ~Handler()
    {
    }

    virtual void HandleError(const char* msg)
    {
        printf("==== HandleError: %s\n", msg);
        exit(1);
    }

    virtual void HandleWarning(const char* msg)
    {
        printf("==== HandleWarning: %s\n", msg);
    }

    virtual void HandlePragma(const char* name, const char* value)
    {
        printf("==== HandlePragma: %s %s\n", name, value);
    }

    virtual void HandleClassDecl(const MI_ClassDecl* decl)
    {
        printf("==== HandleClassDecl: %s\n", decl->name);
        MOFParser::DumpClassDecl(decl, stdout);
    }

    virtual void HandleInstanceDecl(const MI_InstanceDecl* decl)
    {
        printf("==== HandleInstanceDecl: %s\n", decl->name);
        MOFParser::DumpInstanceDecl(decl, stdout);
    }

    virtual void HandleQualifierDecl(const MI_QualifierDecl* decl)
    {
        printf("==== HandleQualifierDecl: %s\n", decl->name);
    }
};

int main(int argc, char** argv)
{
    vector<string> paths;
    paths.push_back(".");

    /* Usage */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    /* Create handler */
    Handler* handler = new Handler;

    /* Create parser */
    MOFParser parser(paths, handler);

    /* Parse document */
    parser.Parse(argv[1]);

#if 0
    /* Dump */
    parser.Dump();
#endif

    /* Delete handler */
    delete handler;

    return 0;
}
