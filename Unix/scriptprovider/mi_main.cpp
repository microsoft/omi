#include "debug_tags.hpp"
#include "server_protocol.hpp"
#include "server.hpp"
#include "unique_ptr.hpp"
#include "mi_value.hpp"


#include <MI.h>
#include <sstream>


util::unique_ptr<Server> g_pServer;


namespace
{

MI_Module g_Module;

};


void
MI_CALL Load (
    MI_Module_Self** ppSelf,
    struct _MI_Context* pContext)
{
    SCX_BOOKEND ("Load: mi_main.cpp");
#if (DEMO_SAFE)
    int rval = protocol::write_opcode (protocol::MODULE_LOAD, g_pServer.get ());
    if (Server::SUCCESS == rval)
    {
        rval = protocol::handle_return (g_pServer.get (), pContext);
    }
    if (Server::SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }
#else
    g_pServer->Module_Load (ppSelf, pContext);
#endif // DEMO_SAFE
}


void
MI_CALL Unload (
    MI_Module_Self* pSelf,
    struct _MI_Context* pContext)
{
    SCX_BOOKEND ("Unload: mi_main.cpp");
#if (DEMO_SAFE)
    int rval = protocol::write_opcode (
        protocol::MODULE_UNLOAD, g_pServer.get ());
    if (Server::SUCCESS == rval)
    {
        rval = protocol::handle_return (g_pServer.get (), pContext);
    }
    if (Server::SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }

//    if (NULL != pSelf)
//    {
//        delete pSelf;
//    }
//    MI_Context_PostResult (pContext, MI_RESULT_OK);
#else
    g_pServer->Module_Unload (pSelf, pContext);
#endif // DEMO_SAFE
}


MI_EXTERN_C MI_EXPORT MI_Module*
Start (
    MI_Server* const pServer,
    char const* const interpreter,
    char const* const moduleName)
{
    SCX_BOOKEND_EX ("Start", " (scriptprovider2 mi_main.cpp)");

#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "interpreter: \"" << interpreter << "\"";
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "moduleName: \"" << moduleName << "\"";
    SCX_BOOKEND_PRINT (strm.str ());
#endif

    g_Module.version = MI_VERSION;
    g_Module.generatorVersion = MI_MAKE_VERSION (1,0,8);
    g_Module.flags =
        MI_MODULE_FLAG_STANDARD_QUALIFIERS |
        MI_MODULE_FLAG_CPLUSPLUS;
    g_Module.charSize = sizeof (MI_Char);
    g_Module.schemaDecl = NULL;
    g_Module.Load = Load;
    g_Module.Unload = Unload;
    g_Module.dynamicProviderFT = NULL;

    g_pServer.reset (new Server (interpreter, moduleName));
    g_pServer->open ();


#if (0)
    int rval = protocol::read (&(g_Module.schemaDecl), g_pServer.get ());
#else
    int rval = Server::SUCCESS;
    {
        SCX_BOOKEND ("recv schema decl");
        int rval = protocol::recv (&(g_Module.schemaDecl),
                                   *(g_pServer->getSocket ()));
    }
#endif

    if (Server::SUCCESS != rval)
    {
        SCX_BOOKEND_PRINT ("read (schema): failed");
    }
    else
    {
        SCX_BOOKEND_PRINT ("read (schema): succeeded");
    }

    g_pServer->setSchema (g_Module.schemaDecl);


//    Client::MI_Type<MI_BOOLEAN>::type_t val = MI_FALSE;


    return &g_Module;
}
