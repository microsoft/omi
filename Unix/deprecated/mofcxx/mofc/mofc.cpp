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
