#include "server.hpp"


#include "debug_tags.hpp"
#include "mi_script_extensions.hpp"
#include "server_protocol.hpp"
#include "repeat.hpp"
#include "unique_ptr.hpp"


#include <errno.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>


extern util::unique_ptr<Server> g_pServer;


namespace
{


typedef util::unique_ptr<char[]> char_array;


class ClassFinder
{
public:
    /*ctor*/ ClassFinder (MI_Char const* const name)
        : m_Name (name) {}

    bool operator () (MI_ClassDecl const* pClass)
    {
        SCX_BOOKEND ("ClassFinder::operator ()");
        std::ostringstream strm;
        strm << "m_Name: \"" << m_Name << '\"';
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        strm << "pClass->name: \"" << pClass->name << '\"';
        SCX_BOOKEND_PRINT (strm.str ());
        return m_Name == pClass->name;
    }

private:
    std::string const m_Name;
};


class MethodFinder
{
public:
    /*ctor*/ MethodFinder (MI_Char const* const name)
        : m_Name (name) {}

    bool operator () (MI_MethodDecl const* pMethod)
    {
        SCX_BOOKEND ("MethodFinder::operator ()");
        std::ostringstream strm;
        strm << "m_Name: \"" << m_Name << '\"';
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        strm << "pMethod->name: \"" << pMethod->name << '\"';
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        strm << (m_Name == pMethod->name ? "Equal" : "Not Equal");
        SCX_BOOKEND_PRINT (strm.str ());
        return m_Name == pMethod->name;
    }

private:
    std::string const m_Name;
};


MI_MethodDecl const*
findMethodDecl (
    MI_ClassDeclEx const* const pClassDecl,
    MI_Char const* const methodName)
{
    SCX_BOOKEND ("findMethodDecl");
    MI_MethodDecl const* const* ppMethodDecl =
        std::find_if (
            pClassDecl->methods,
            pClassDecl->methods + pClassDecl->numMethods,
            MethodFinder (methodName));
    return ppMethodDecl != (pClassDecl->methods + pClassDecl->numMethods) ?
        *ppMethodDecl : NULL;
}


int
handle_post_instance (
    MI_Context* const pContext,
    MI_SchemaDecl const* const pSchema,
    MI_Filter const* const pFilter,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("handle_post_instance");
    int rval = socket_wrapper::SUCCESS;
//    protocol::data_type_t type;
    MI_Instance* pInstance = NULL;
//    if (socket_wrapper::SUCCESS == (
//            rval = (protocol::recv_type (&type, sock))) &&
    if (socket_wrapper::SUCCESS == (
            rval = (protocol::recv (&pInstance, pContext, pSchema, sock))))
    {
        SCX_BOOKEND_PRINT ("recv instance succeeded");
        MI_Boolean post = MI_TRUE;
        if (NULL != pFilter)
        {
            if (MI_RESULT_OK == MI_Filter_Evaluate (pFilter, pInstance, &post))
            {
                if (MI_FALSE == post)
                {
                    SCX_BOOKEND_PRINT ("Filtered out");
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("MI_Filter_Evaluate failed");
                post = MI_FALSE;
            }
        }
        if (MI_FALSE != post)
        {
            if (MI_RESULT_OK == MI_Context_PostInstance (pContext, pInstance))
            {
                SCX_BOOKEND_PRINT ("PostInstance succeeded");
            }
            else
            {
                SCX_BOOKEND_PRINT ("PostInstance failed");
            }
        }
        MI_Instance_Delete (pInstance);
    }
    else
    {
        SCX_BOOKEND_PRINT ("something went wrong");
    }
    return rval;
}


int
handle_post_result (
    MI_Context* const pContext,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("handle_post_result");
    MI_Result result;
    int rval = protocol::recv (&result, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("rec'd result");
        MI_Context_PostResult (pContext, result);
    }
    else
    {
        SCX_BOOKEND_PRINT ("recv result failed");
    }
    return rval;
}


int
handle_return (
    MI_Context* const pContext,
    MI_SchemaDecl const* const pSchema,
    MI_Filter const* const pFilter,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("handle_return");
    int rval = socket_wrapper::SUCCESS;
    protocol::opcode_t opcode;
    do
    {
        rval = protocol::recv_opcode (&opcode, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            switch (opcode)
            {
            case protocol::POST_INSTANCE:
                SCX_BOOKEND_PRINT ("rec'ved POST_INSTANCE");
                rval = handle_post_instance (pContext, pSchema, pFilter, sock);
                break;
            case protocol::POST_RESULT:
                SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                rval = handle_post_result (pContext, sock);
                break;
            default:
                SCX_BOOKEND_PRINT ("unexpected opcode");
                // todo: error
                break;
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("error receiving opcode");
            // todo: error
        }
    } while (socket_wrapper::SUCCESS == rval &&
             protocol::POST_RESULT != opcode);
    return rval;
}


}


#define _COUNT 25

#define LOAD_DEF(I) \
MI_EXTERN_C void \
MI_CALL Load##I ( \
    void** ppSelf, \
    MI_Module_Self* pSelfModule, \
    MI_Context* pContext) \
{ \
    g_pServer->Load (I, ppSelf, pSelfModule, pContext); \
}

#define LOAD_DECL(I) Load##I,


REPEAT (_COUNT, LOAD_DEF)

MI_ProviderFT_Load LoadFunctions[] = {
    REPEAT (_COUNT, LOAD_DECL)
};


#define UNLOAD_DEF(I) \
MI_EXTERN_C void \
MI_CALL Unload##I ( \
    void* pSelf, \
    MI_Context* pContext) \
{ \
    g_pServer->Unload (I, pSelf, pContext); \
}

#define UNLOAD_DECL(I) Unload##I,


REPEAT (_COUNT, UNLOAD_DEF)

MI_ProviderFT_Unload UnloadFunctions[] = {
    REPEAT (_COUNT, UNLOAD_DECL)
};


/*ctor*/
Server::Server (
    std::string interpreter,
    std::string moduleName)
    : m_Interpreter (interpreter)
    , m_ModuleName (moduleName)
    , m_pSocket ()
    , m_pSchemaDecl ()
{
    SCX_BOOKEND ("Server::ctor");
}


/*dtor*/
Server::~Server ()
{
    SCX_BOOKEND ("Server::dtor");
}


int
Server::open ()
{
    int rval = SUCCESS;
    std::ostringstream strm;
#if (PRINT_BOOKENDS)
    strm << " Module: \"" << m_ModuleName << "\" (libScriptProvider)";
    SCX_BOOKEND_EX ("Server::open", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    SCX_BOOKEND_PRINT ("4/29/2016");
    if (!m_pSocket)
    {
        int sockets[2];
        int result = socketpair (AF_UNIX, SOCK_STREAM, 0, sockets);
        if (-1 != result)
        {
            // socketpair succeeded
            SCX_BOOKEND_PRINT ("socketpair - succeeded");
            int pid = fork ();
            if (0 == pid)
            {
                // fork succeded, this is the child process
                SCX_BOOKEND_PRINT ("fork - succeeded: this is the child");
                // close the parent socket
                ::close (sockets[1]);
                // create the argument list including the child socket name as a
                // command line arg
                size_t const SOCK_ID_BUF_LEN = 32;
                char socketID[SOCK_ID_BUF_LEN];
                snprintf (socketID, SOCK_ID_BUF_LEN, "%d", sockets[0]);

                chdir ("/home/ermumau/omi-git/Unix/scriptprovider/python");

                char* args[] = { const_cast<char*>(m_Interpreter.c_str ()),
                                 "client.py",
                                 socketID,
                                 const_cast<char*>(m_ModuleName.c_str ()),
                                 0 };

                // exec
                execvp (args[0], args);
                SCX_BOOKEND_PRINT ("execvp - failed");
                // if we got here, exec failed!
                // check errno { EACCES, ENOEXEC }
                strm << "Server::open - exec failed: " << errno << ": \""
                     << errnoText << '\"';
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                rval = FORK_FAILED;
            }
            else if (-1 != pid)
            {
                // fork succeeded, this is the parent process
                SCX_BOOKEND_PRINT ("fork - succeeded: this is the parent");
                ::close (sockets[0]);
                m_pSocket = new socket_wrapper (sockets[1]);
                rval = SUCCESS;
            }
            else
            {
                // fork failed
                // error (check errno { EAGAIN, ENOMEM })
                strm << "Server::open - fork failed: " << errno
                     << ": \"" << errnoText << '\"';
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                rval = FORK_FAILED;
            }
        }
        else
        {
            // socketpair failed
            // error (check errno { EAFNOSUPPORT, EMFILE, ENFILE, EOPNOTSUPP,
            //    EPROTONOSUPPORT, EPROTOTYPE, EACCES, ENOBUFS, ENOMEM })
            strm << "Server::open - socketpair_failed: " << errno
                 << ": \"" << errnoText << '\"';
            SCX_BOOKEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            strm.str ("");
            strm.clear ();
            rval = SOCKETPAIR_FAILED;
        }
    }
    else
    {
        rval = INVALID_STATE;
    }
    return rval;
}


void
Server::setSchema (
    MI_SchemaDecl const* const pSchema)
{
    if (pSchema)
    {
        m_ClassNames.reserve (pSchema->numClassDecls);
        for (MI_Uint32 i = 0; i < pSchema->numClassDecls; ++i)
        {
            MI_ClassDecl const* pClass = pSchema->classDecls[i];
            m_ClassNames.push_back (pClass->name);
            const_cast<MI_ProviderFT*>(pClass->providerFT)->Load =
                LoadFunctions[i];
            const_cast<MI_ProviderFT*>(pClass->providerFT)->Unload =
                UnloadFunctions[i];
        }
    }
    m_pSchemaDecl.reset (pSchema);
}


MI_ClassDeclEx const*
Server::findClassDecl (
    MI_Char const* const className)
{
    SCX_BOOKEND ("Server::finClassDecl");
    MI_ClassDecl const* const* ppClassDecl =
        std::find_if (
            m_pSchemaDecl->classDecls,
            m_pSchemaDecl->classDecls + m_pSchemaDecl->numClassDecls,
            ClassFinder (className));
//    return ppClassDecl ? static_cast<MI_ClassDeclEx const*>(*ppClassDecl)
//                       : NULL;
    return (ppClassDecl != (
        m_pSchemaDecl->classDecls + m_pSchemaDecl->numClassDecls) ?
        static_cast<MI_ClassDeclEx const*>(*ppClassDecl) : NULL);
}


void
Server::Module_Load (
    MI_Module_Self** ppSelf,
    struct _MI_Context* pContext)
{
    SCX_BOOKEND ("Server::Module_Load");
    int rval = protocol::send_opcode (protocol::MODULE_LOAD, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        protocol::opcode_t opcode;
        rval = protocol::recv_opcode (&opcode, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (protocol::POST_RESULT == opcode)
            {
                SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                rval = handle_post_result (pContext, *m_pSocket);
            }
            else
            {
                SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("socket error");
            // socket error
            // todo: error
        }
    }
    if (socket_wrapper::SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }
}


void
Server::Module_Unload (
    MI_Module_Self* pSelf,
    struct _MI_Context* pContext)
{
    SCX_BOOKEND ("Server::Module_Unload");
    int rval = protocol::send_opcode (protocol::MODULE_UNLOAD, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        protocol::opcode_t opcode;
        rval = protocol::recv_opcode (&opcode, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (protocol::POST_RESULT == opcode)
            {
                SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                rval = handle_post_result (pContext, *m_pSocket);
            }
            else
            {
                SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("socket error");
            // socket error
            // todo: error
        }
    }
    if (socket_wrapper::SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }
}


void
Server::Load (
    size_t const& index,
    void** ppSelf,
    MI_Module_Self* pSelfModule,
    MI_Context* pContext)
{
    SCX_BOOKEND ("Server::Load (index)");
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "index: " << index;
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "class: " << m_ClassNames[index];
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    int rval = SUCCESS;
    if (socket_wrapper::SUCCESS == (
            rval = protocol::send_opcode (protocol::CLASS_LOAD, *m_pSocket)) &&
        socket_wrapper::SUCCESS == (
            rval = protocol::send (m_ClassNames[index], *m_pSocket)))
    {
        protocol::opcode_t opcode;
        rval = protocol::recv_opcode (&opcode, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (protocol::POST_RESULT == opcode)
            {
                SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                rval = handle_post_result (pContext, *m_pSocket);
            }
            else
            {
                SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("socket error");
            // socket error
            // todo: error
        }
    }
    if (SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }
}


void
Server::Unload (
    size_t const& index,
    void* pSelf,
    MI_Context* pContext)
{
    SCX_BOOKEND ("Server::Unload (index)");
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "index: " << index;
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "class: " << m_ClassNames[index];
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    int rval = SUCCESS;
    if (socket_wrapper::SUCCESS == (
            rval = protocol::send_opcode (protocol::CLASS_UNLOAD, *m_pSocket)) &&
        socket_wrapper::SUCCESS == (
            rval = protocol::send (m_ClassNames[index], *m_pSocket)))
    {
        protocol::opcode_t opcode;
        rval = protocol::recv_opcode (&opcode, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (protocol::POST_RESULT == opcode)
            {
                SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                rval = handle_post_result (pContext, *m_pSocket);
            }
            else
            {
                SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("socket error");
            // socket error
            // todo: error
        }
    }
    if (SUCCESS != rval)
    {
        MI_Context_PostResult (pContext, MI_RESULT_FAILED);
    }
}


void
Server::EnumerateInstances (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_PropertySet const* pPropertySet,
    MI_Boolean keysOnly,
    MI_Filter const* pFilter)
{
    SCX_BOOKEND ("Server::EnumerateInstances");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    if (NULL != pClassDecl)
    {
        strm << "method for EnumerateInstances: " <<
            (NULL != pClassDecl->scriptFT->EnumerateInstances
                 ? pClassDecl->scriptFT->EnumerateInstances : "NULL");
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
    }
#endif
    if (NULL != pClassDecl)
    {
        // skipping: nameSpace, pPropertySet, pFilter
        if (socket_wrapper::SUCCESS == (
                rval = protocol::send_opcode (
                    protocol::ENUMERATE_INSTANCES, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (nameSpace, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (className, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (pPropertySet, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send_boolean (keysOnly, *m_pSocket)))
        {
            rval = handle_return (pContext, m_pSchemaDecl.get (), pFilter,
                                  *m_pSocket);
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


void
Server::GetInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName,
    MI_PropertySet const* pPropertySet)
{
    SCX_BOOKEND ("Server::GetInstance");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    if (NULL != pClassDecl)
    {
        strm << "method for GetInstance: " <<
            (NULL != pClassDecl->scriptFT->GetInstance
                 ? pClassDecl->scriptFT->GetInstance : "NULL");
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
    }
#endif
    if (NULL != pInstanceName &&
        NULL != pClassDecl)
    {
        // skipping: nameSpace, pPropertySet
        if (socket_wrapper::SUCCESS == (
                rval = protocol::send_opcode (
                    protocol::GET_INSTANCE, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (nameSpace, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (className, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (*pInstanceName, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (pPropertySet, *m_pSocket)))
        {
            rval = handle_return (pContext, m_pSchemaDecl.get (), NULL,
                                  *m_pSocket);
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


void
Server::CreateInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pNewInstance)
{
    SCX_BOOKEND ("Server::CreateInstance");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    if (NULL != pClassDecl)
    {
        strm << "method for CreateInstance: " <<
            (NULL != pClassDecl->scriptFT->CreateInstance
                 ? pClassDecl->scriptFT->CreateInstance : "NULL");
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
    }
#endif
    if (NULL != pNewInstance &&
        NULL != pClassDecl)
    {
        // skipping: nameSpace
        if (socket_wrapper::SUCCESS == (
                rval = protocol::send_opcode (
                    protocol::CREATE_INSTANCE, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (nameSpace, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (className, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (*pNewInstance, *m_pSocket)))
        {
            protocol::opcode_t opcode;
            rval = protocol::recv_opcode (&opcode, *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                if (protocol::POST_RESULT == opcode)
                {
                    SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                    rval = handle_post_result (pContext, *m_pSocket);
                }
                else
                {
                    SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                    // todo: error
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("socket error");
                // socket error
                // todo: error
            }
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


void
Server::ModifyInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pModifiedInstance,
    MI_PropertySet const* pPropertySet)
{
    SCX_BOOKEND ("Server::ModifyInstance");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    if (NULL != pClassDecl)
    {
        strm << "method for ModifyInstance: " <<
            (NULL != pClassDecl->scriptFT->ModifyInstance
                 ? pClassDecl->scriptFT->ModifyInstance : "NULL");
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
    }
#endif
    if (NULL != pModifiedInstance &&
        NULL != pClassDecl)
    {
        // skipping: nameSpace, pPropertySet
        if (socket_wrapper::SUCCESS == (
                rval = protocol::send_opcode (
                    protocol::MODIFY_INSTANCE, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (nameSpace, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (className, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (*pModifiedInstance, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (pPropertySet, *m_pSocket)))
        {
            protocol::opcode_t opcode;
            rval = protocol::recv_opcode (&opcode, *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                if (protocol::POST_RESULT == opcode)
                {
                    SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                    rval = handle_post_result (pContext, *m_pSocket);
                }
                else
                {
                    SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                    // todo: error
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("socket error");
                // socket error
                // todo: error
            }
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


void
Server::DeleteInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName)
{
    SCX_BOOKEND ("Server::DeleteInstance");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    if (NULL != pClassDecl)
    {
        strm << "method for DeleteInstance: " <<
            (NULL != pClassDecl->scriptFT->DeleteInstance
                 ? pClassDecl->scriptFT->DeleteInstance : "NULL");
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
    }
#endif
    if (NULL != pInstanceName &&
        NULL != pClassDecl)
    {
        // skipping: nameSpace
        if (socket_wrapper::SUCCESS == (
                rval = protocol::send_opcode (
                    protocol::DELETE_INSTANCE, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (nameSpace, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (className, *m_pSocket)) &&
            socket_wrapper::SUCCESS == (
                rval = protocol::send (*pInstanceName, *m_pSocket)))
        {
            protocol::opcode_t opcode;
            rval = protocol::recv_opcode (&opcode, *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                if (protocol::POST_RESULT == opcode)
                {
                    SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
                    rval = handle_post_result (pContext, *m_pSocket);
                }
                else
                {
                    SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
                    // todo: error
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("socket error");
                // socket error
                // todo: error
            }
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


void
Server::Invoke (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Char const* methodName,
    MI_Instance const* pInstance,
    MI_Instance const* pInputParameters)
{
    SCX_BOOKEND ("Server::Invoke");
    int rval = SUCCESS;
    MI_ClassDeclEx const* pClassDecl = findClassDecl (className);
#if (PRINT_BOOKENDS)
    std::ostringstream strm;
    strm << "namespace: \"" << nameSpace << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "className: \"" << className << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "methodName: \"" << methodName << '\"';
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
//    if (NULL != pClassDecl)
//    {
//        strm << "method for DeleteInstance: " <<
//            (NULL != pClassDecl->scriptFT->DeleteInstance
//                 ? pClassDecl->scriptFT->DeleteInstance : "NULL");
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//    }
//    else
//    {
//        SCX_BOOKEND_PRINT ("classDecl was NOT found");
//    }
#endif
    if (NULL != pClassDecl)
    {
        MI_MethodDecl const* pMethodDecl =
            findMethodDecl (pClassDecl, methodName);
        if (NULL != pMethodDecl)
        {
            strm << "MI_MethodDecl->name: \"" << pMethodDecl->name << '\"';
            SCX_BOOKEND_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
            SCX_BOOKEND_PRINT ("class and method where found");
//            MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);

//            if (pInstance)
//            {
//                SCX_BOOKEND_PRINT ("pInstance is not NULL");
//            }
//            else
//            {
//                SCX_BOOKEND_PRINT ("pInstance is NULL");
//            }
//            if (pInputParameters)
//            {
//                SCX_BOOKEND_PRINT ("pInputParameters is not NULL");
//            }
//            else
//            {
//                SCX_BOOKEND_PRINT ("pInputParameters is NULL");
//            }

            MI_Uint32 flags =
                (pInstance ? protocol::HAS_INSTANCE_FLAG : 0) |
                (pInputParameters ? protocol::HAS_INPUT_PARAMETERS_FLAG : 0);

            {
                SCX_BOOKEND ("send opcode");
                rval = protocol::send_opcode (protocol::INVOKE, *m_pSocket);
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send namespace");
                rval = protocol::send (nameSpace, *m_pSocket);
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send class name");
                rval = protocol::send (className, *m_pSocket);
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send method name");
                rval = protocol::send (methodName, *m_pSocket);
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send flags");
                rval = protocol::send (flags, *m_pSocket);
            }

//            if (socket_wrapper::SUCCESS == (
//                    rval = protocol::send_opcode (
//                        protocol::INVOKE, *m_pSocket)) &&
//                socket_wrapper::SUCCESS == (
//                    rval = protocol::send (nameSpace, *m_pSocket)) &&
//                socket_wrapper::SUCCESS == (
//                    rval = protocol::send (className, *m_pSocket)) &&
//                socket_wrapper::SUCCESS == (
//                    rval = protocol::send (methodName, *m_pSocket)) &&
//                socket_wrapper::SUCCESS == (
//                    rval = protocol::send (flags, *m_pSocket)))
////                socket_wrapper::SUCCESS == (
////                    rval = protocol::send (*pInstance, *m_pSocket)) &&
////                socket_wrapper::SUCCESS == (
////                    rval = protocol::send (*pInputParameters, *m_pSocket)))

            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send instance");
                if (NULL != pInstance)
                {
                    SCX_BOOKEND_PRINT ("pInstance is not NULL");
                    rval = protocol::send (*pInstance, *m_pSocket);
                }
                else
                {
                    SCX_BOOKEND_PRINT ("pInstance is NULL");
                }
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND ("send input parameters");
                if (NULL != pInputParameters)
                {
                    SCX_BOOKEND_PRINT ("pInputParameters is not NULL");
                    rval = protocol::send (*pInputParameters, *m_pSocket);
                }
                else
                {
                    SCX_BOOKEND_PRINT ("pInputParameters is NULL");
                }
            }





            if (socket_wrapper::SUCCESS == rval)
            {
                
                {
                    rval = handle_return (pContext, m_pSchemaDecl.get (), NULL,
                                          *m_pSocket);
                }
                if (SUCCESS != rval)
                {
                    MI_Context_PostResult (pContext, MI_RESULT_FAILED);
                }




//                protocol::opcode_t opcode;
//                rval = protocol::recv_opcode (&opcode, *m_pSocket);
//                if (socket_wrapper::SUCCESS == rval)
//                {
//                    // I expect that there needs to be a case for return value
//                    if (protocol::POST_RESULT == opcode)
//                    {
//                        SCX_BOOKEND_PRINT ("rec'ved POST_RESULT");
//                        rval = handle_post_result (pContext, *m_pSocket);
//                    }
//                    else
//                    {
//                        SCX_BOOKEND_PRINT ("rec'd unhandled opcode");
//                        // todo: error
//                    }
//                }
//                else
//                {
//                    SCX_BOOKEND_PRINT ("socket error");
//                    // socket error
//                    // todo: error
//                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("something failed");
                MI_Context_PostResult (pContext, MI_RESULT_FAILED);
            }
        }
        else 
        {
            SCX_BOOKEND_PRINT ("methodDecl was NOT found");
            MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
        }
        if (SUCCESS != rval)
        {
            MI_Context_PostResult (pContext, MI_RESULT_FAILED);
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("classDecl was NOT found");
        MI_Context_PostResult (pContext, MI_RESULT_INVALID_CLASS);
    }
}


MI_EXTERN_C void
MI_CALL EnumerateInstances (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_PropertySet const* pPropertySet,
    MI_Boolean keysOnly,
    MI_Filter const* pFilter)
{
    g_pServer->EnumerateInstances (pSelf, pContext, nameSpace, className,
                                   pPropertySet, keysOnly, pFilter);
}


MI_EXTERN_C void
MI_CALL GetInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName,
    MI_PropertySet const* pPropertySet)
{
    g_pServer->GetInstance (pSelf, pContext, nameSpace, className,
                            pInstanceName, pPropertySet);
}


MI_EXTERN_C void
MI_CALL CreateInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pNewInstance)
{
    g_pServer->CreateInstance (pSelf, pContext, nameSpace, className,
                               pNewInstance);
}


MI_CALL void
MI_CALL ModifyInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pModifiedInstance,
    MI_PropertySet const* pPropertySet)
{
    g_pServer->ModifyInstance (pSelf, pContext, nameSpace, className,
                               pModifiedInstance, pPropertySet);
}


MI_CALL void
MI_CALL DeleteInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName)
{
    g_pServer->DeleteInstance (pSelf, pContext, nameSpace, className,
                               pInstanceName);
}


MI_EXTERN_C void
MI_CALL AssociatorInstances (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstance,
    MI_Char const* resultClass,
    MI_Char const* role,
    MI_Char const* resultRole,
    MI_PropertySet const* pPropertySet,
    MI_Boolean keysOnly,
    MI_Filter const* pFilter)
{
    SCX_BOOKEND ("AssociatorInstances: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL ReferenceInstances (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstance,
    MI_Char const* role,
    MI_PropertySet const* pPropertySet,
    MI_Boolean keysOnly,
    MI_Filter const* pFilter)
{
    SCX_BOOKEND ("ReferenceInstances: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL EnableIndications (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className)
{
    SCX_BOOKEND ("EnableIndications: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL DisableIndications (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className)
{
    SCX_BOOKEND ("DisableIndications: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL Subscribe (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Filter const* pFilter,
    MI_Char const* bookmark,
    MI_Uint64 subscriptionID,
    void** ppSubscriptionSelf)
{
    SCX_BOOKEND ("Subscribe: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL Unsubscribe (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Uint64 subscriptionID,
    void* pSubscriptionSelf)
{
    SCX_BOOKEND ("Unsubscribe: server.cpp");
    SCX_BOOKEND_PRINT ("Not implemented!");
    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}


MI_EXTERN_C void
MI_CALL Invoke (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Char const* methodName,
    MI_Instance const* pInstance,
    MI_Instance const* pInputParameters)
{
    SCX_BOOKEND ("Invoke: server.cpp");
    g_pServer->Invoke (pSelf, pContext, nameSpace, className, methodName,
                       pInstance, pInputParameters);
//    SCX_BOOKEND_PRINT ("Not implemented!");
//    MI_Context_PostResult (pContext, MI_RESULT_NOT_SUPPORTED);
}
