#include "client.hpp"


#include "debug_tags.hpp"
#include "mi_context.hpp"
#include "mi_schema.hpp"
#include "shared_protocol.hpp"
//#include "socket_wrapper.hpp"


namespace scx
{


/*ctor*/
Client::Client (
    socket_wrapper::Ptr const& pSocket,
    MI_Module::Ptr const& pModule)
    : m_pSocket (pSocket)
    , m_pModule (pModule)
      , m_pContext (new MI_Context (pSocket, pModule->getSchemaDecl ()))
{
    SCX_BOOKEND ("Client::ctor");
}


/*ctor*/
Client::~Client ()
{
    SCX_BOOKEND ("Client::dtor");
}


int
Client::run ()
{
    SCX_BOOKEND ("Client::run");
    int rval = m_pModule->getSchemaDecl ()->send (*m_pSocket);
    
    // todo deal with rval
    // begin work loop


    bool complete = false;
    while (!complete)
    {
        protocol::opcode_t opcode;
        int rval = protocol::recv_opcode (&opcode, *m_pSocket);
        if (EXIT_SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("an opcode was read");
            switch (opcode)
            {
            case protocol::MODULE_LOAD:
                SCX_BOOKEND_PRINT ("MODULE_LOAD");
                rval = handle_module_load ();
                break;
            case protocol::MODULE_UNLOAD:
                SCX_BOOKEND_PRINT ("MODULE_UNLOAD");
                rval = handle_module_unload ();
                complete = true;
                break;
            case protocol::CLASS_LOAD:
                SCX_BOOKEND_PRINT ("CLASS_LOAD");
                rval = handle_class_load ();
                break;
            case protocol::CLASS_UNLOAD:
                SCX_BOOKEND_PRINT ("CLASS_UNLOAD");
                rval = handle_class_unload ();
                break;
            case protocol::ENUMERATE_INSTANCES:
                SCX_BOOKEND_PRINT ("ENUMERATE_INSTANCES");
                rval = handle_enumerate_instances ();
                break;
            case protocol::GET_INSTANCE:
                SCX_BOOKEND_PRINT ("GET_INSTANCE");
                rval = handle_get_instance ();
                break;
            case protocol::CREATE_INSTANCE:
                SCX_BOOKEND_PRINT ("CREATE_INSTANCE");
                rval = handle_create_instance ();
                break;
            case protocol::MODIFY_INSTANCE:
                SCX_BOOKEND_PRINT ("MODIFY_INSTANCE");
                rval = handle_modify_instance ();
                break;
            case protocol::DELETE_INSTANCE:
                SCX_BOOKEND_PRINT ("DELETE_INSTANCE");
                rval = handle_delete_instance ();
                break;

            case protocol::INVOKE:
                SCX_BOOKEND_PRINT ("INVOKE");
                rval = handle_invoke ();
                break;
            default:
                SCX_BOOKEND_PRINT ("unhandled opcode");
                // todo set pyerr
                rval = EXIT_FAILURE;
                break;
            }
        }
        if (EXIT_SUCCESS != rval)
        {
            complete = true;
        }
    }


//#        #finished = False
//#        #while True != finished:
//#        #    opcode = read_opcode (self.fd)
//#        #    op = {
//#        #        OPCODE_MODULE_LOAD: self.handle_module_load,
//#        #        OPCODE_MODULE_UNLOAD: self.handle_module_unload,
//#        #        OPCODE_CLASS_LOAD: self.handle_class_load,
//#        #        OPCODE_CLASS_UNLOAD: self.handle_class_unload,
//#        #        OPCODE_ENUMERATE_INSTANCES: self.handle_enumerate_instances,
//#        #        OPCODE_GET_INSTANCE: self.handle_get_instance,
//#        #        OPCODE_CREATE_INSTANCE: self.handle_create_instance,
//#        #        OPCODE_MODIFY_INSTANCE: self.handle_modify_instance,
//#        #        OPCODE_DELETE_INSTANCE: self.handle_delete_instance,
//#        #        }.get (opcode, None)
//#        #    if op is not None:
//#        #        finished = op ()
//#        #    else:
//#        #        finished = True

//def read_opcode (fd):
//    be = VerboseBookend ('read_opcode')
//    buf = fd.recv (4)
//    if 0 == len (buf):
//        raise SocketClosed
//    val = struct.unpack ('@I', buf)[0]
//    VerboseBookendPrint ('opcode: ' + str (val))
//    return val

    return rval;
}


int
Client::handle_module_load ()
{
    SCX_BOOKEND ("Client::handle_module_load");
    return m_pModule->getLoadFn ()->fn (m_pModule, m_pContext);
}


int
Client::handle_module_unload ()
{
    SCX_BOOKEND ("Client::handle_module_unload");
    return m_pModule->getUnloadFn ()->fn (m_pModule, m_pContext);
}


int
Client::handle_class_load ()
{
    SCX_BOOKEND ("Client::handle_class_load");
    std::ostringstream strm;
    MI_Value<MI_STRING>::Ptr pClassName;
    int rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->Load (
                m_pModule, m_pContext);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
Client::handle_class_unload ()
{
    SCX_BOOKEND ("Client::handle_class_unload");

    MI_Value<MI_STRING>::Ptr pClassName;
    int rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();

        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->Unload (m_pContext);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
Client::handle_enumerate_instances ()
{
    SCX_BOOKEND ("Client::handle_class_enumerate_instances");
    MI_Value<MI_STRING>::Ptr pNameSpace;
    MI_Value<MI_STRING>::Ptr pClassName;
    MI_PropertySet::ConstPtr pPropertySet;
    MI_Value<MI_BOOLEAN>::Ptr pKeysOnly;
    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_PropertySet::recv (&pPropertySet, *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                rval = MI_Value<MI_BOOLEAN>::recv (&pKeysOnly, *m_pSocket);
                if (socket_wrapper::SUCCESS != rval)
                {
                    SCX_BOOKEND_PRINT ("read keys only failed");
                    // todo set error
                    // return MI_RESULT_INVALID_CLASS
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("read property keys failed");
                // todo set error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("read class name failed");
            // todo set error
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name space failed");
        // todo set error
        rval = EXIT_FAILURE;
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            // todo: add pKeysOnly

            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->EnumerateInstances (
                m_pContext, pNameSpace, pClassName, pPropertySet, pKeysOnly);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


bool
Client::handle_get_instance ()
{
    SCX_BOOKEND ("Client::handle_get_instance");
    MI_Value<MI_STRING>::Ptr pNameSpace;
    MI_Value<MI_STRING>::Ptr pClassName;
    MI_Instance::Ptr pInstance;
    MI_PropertySet::ConstPtr pPropertySet;
    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {

        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                rval = MI_PropertySet::recv (&pPropertySet, *m_pSocket);
                if (socket_wrapper::SUCCESS != rval)
                {
                    SCX_BOOKEND_PRINT ("read property set failed");
                    // todo: error
                    // return MI_RESULT (failure)
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("read instance failed");
                // todo: error
                // return MI_RESULT (failure)
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("read class name failed");
            // todo set error
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name space failed");
        // todo set error
        rval = EXIT_FAILURE;
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            // todo: add pKeysOnly
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->GetInstance (
                m_pContext, pNameSpace, pClassName, pInstance, pPropertySet);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


bool
Client::handle_create_instance ()
{
    SCX_BOOKEND ("Client::handle_create_instance");
    MI_Value<MI_STRING>::Ptr pNameSpace;
    MI_Value<MI_STRING>::Ptr pClassName;
    MI_Instance::Ptr pInstance;
    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS != rval)
            {
                SCX_BOOKEND_PRINT ("read instance failed");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("read class name failed");
            // todo set error
            rval = EXIT_FAILURE;
    }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name space failed");
        // todo error
        rval = EXIT_FAILURE;
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->CreateInstance (
                m_pContext, pNameSpace, pClassName, pInstance);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


bool
Client::handle_modify_instance ()
{
    SCX_BOOKEND ("Client::handle_modify_instance");
    MI_Value<MI_STRING>::Ptr pNameSpace;
    MI_Value<MI_STRING>::Ptr pClassName;
    MI_Instance::Ptr pInstance;
    MI_PropertySet::ConstPtr pPropertySet;
    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                rval = MI_PropertySet::recv (&pPropertySet, *m_pSocket);
                if (socket_wrapper::SUCCESS != rval)
                {
                    SCX_BOOKEND_PRINT ("read propety set failed");
                    // todo set error
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("read instance failed");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("read class name failed");
            // todo set error
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name space failed");
        // todo set error
        rval = EXIT_FAILURE;
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->ModifyInstance (
                m_pContext, pNameSpace, pClassName, pInstance, pPropertySet);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


bool
Client::handle_delete_instance ()
{
    SCX_BOOKEND ("Client::handle_delete_instance");
    MI_Value<MI_STRING>::Ptr pNameSpace;
    MI_Value<MI_STRING>::Ptr pClassName;
    MI_Instance::Ptr pInstance;
    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS != rval)
            {
                SCX_BOOKEND_PRINT ("read instance failed");
                // todo: error
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("read class name failed");
            // todo set error
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name space failed");
        // todo set error
        rval = EXIT_FAILURE;
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        std::ostringstream strm;
        strm << "class name: \"" << pClassName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (pClassDecl)
        {
            // todo: add pKeysOnly
            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
            rval = pClassDecl->getFunctionTable ()->DeleteInstance (
                m_pContext, pNameSpace, pClassName, pInstance);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo set pyerr
            // return MI_RESULT_INVALID_CLASS
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read class name failed");
        // todo set pyerr
        // return MI_RESULT_INVALID_CLASS
        rval = EXIT_FAILURE;
    }
    return rval;
}


bool
Client::handle_invoke ()
{
    SCX_BOOKEND ("Client::handle_invoke");

    MI_Value<MI_STRING>::Ptr pNameSpace;
    int rval = socket_wrapper::SUCCESS;
    {
        SCX_BOOKEND ("read namespace");
        rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
        if (socket_wrapper::SUCCESS != rval)
        {
            SCX_BOOKEND ("recv namespace failed");
        }
    }


    MI_Value<MI_STRING>::Ptr pClassName;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read class name");
        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS != rval)
        {
            SCX_BOOKEND ("recv class name failed");
        }
    }

    MI_Value<MI_STRING>::Ptr pMethodName;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read method name");
        rval = MI_Value<MI_STRING>::recv (&pMethodName, *m_pSocket);
        if (socket_wrapper::SUCCESS != rval)
        {
            SCX_BOOKEND ("recv method name failed");
        }
    }

    MI_ClassDecl::ConstPtr pClassDecl;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("find MI_ClassDecl");
        pClassDecl = m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
        if (!pClassDecl)
        {
            SCX_BOOKEND ("MI_ClassDecl not found");
        }
    }
    
    MI_MethodDecl::ConstPtr pMethodDecl;
    if (pClassDecl)
    {
        SCX_BOOKEND ("find MI_MethodDecl");
        pMethodDecl = pClassDecl->getMethodDecl (pMethodName->getValue ());
        if (!pMethodDecl)
        {
            SCX_BOOKEND ("MI_MethodDecl not found");
        }
    }

    MI_Uint32 flags;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read flags");
//        rval = m_pSocket->recv (
//            reinterpret_cast<socket_wrapper::byte_t*>(&flags),
//            sizeof (MI_Uint32));
        rval = protocol::recv (&flags, *m_pSocket);
        if (socket_wrapper::SUCCESS != rval)
        {
            SCX_BOOKEND ("recv flags failed");
        }
    }

    MI_Instance::Ptr pInstance;
    if (pMethodDecl &&
        socket_wrapper::SUCCESS == rval &&
        protocol::HAS_INSTANCE_FLAG == (flags & protocol::HAS_INSTANCE_FLAG))
    {
        SCX_BOOKEND ("read instance");
        MI_Value<MI_STRING>::Ptr pExtraClassName;
        SCX_BOOKEND_PRINT ("recv extra class name");
        rval = MI_Value<MI_STRING>::recv (&pExtraClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInstance, MI_ObjectDecl::ConstPtr (pClassDecl.get ()),
                m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS != rval)
            {
                SCX_BOOKEND ("recv instance failed");
            }
        }
    }

    MI_Instance::Ptr pInputParameters;
    if (pMethodDecl &&
        socket_wrapper::SUCCESS == rval &&
        protocol::HAS_INPUT_PARAMETERS_FLAG == (
            flags & protocol::HAS_INPUT_PARAMETERS_FLAG))
    {
        SCX_BOOKEND ("read input parameters");
        MI_Value<MI_STRING>::Ptr pExtraClassName;
        SCX_BOOKEND_PRINT ("recv extra class name");
        rval = MI_Value<MI_STRING>::recv (&pExtraClassName, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = MI_Instance::recv (
                &pInputParameters, MI_ObjectDecl::ConstPtr (pMethodDecl.get ()),
                m_pModule->getSchemaDecl (), *m_pSocket);
            if (socket_wrapper::SUCCESS != rval)
            {
                SCX_BOOKEND ("recv input parameters failed");
            }
        }
    }

    if (socket_wrapper::SUCCESS == rval &&
        pMethodDecl)
    {
        SCX_BOOKEND ("call Invoke");
        pMethodDecl->Invoke (
            m_pContext, pNameSpace, pClassName, pMethodName, pInstance,
            pInputParameters);
    }

    return rval;

//    MI_Value<MI_STRING>::Ptr pNameSpace;
//    MI_Value<MI_STRING>::Ptr pClassName;
//    MI_Value<MI_STRING>::Ptr pMethodName;
//    MI_Instance::Ptr pInstance;
//    MI_Instance::Ptr pInputParameters;
//    int rval = MI_Value<MI_STRING>::recv (&pNameSpace, *m_pSocket);
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
//        if (socket_wrapper::SUCCESS == rval)
//        {
//            rval = MI_Value<MI_STRING>::recv (&pMethodName, *m_pSocket);
//            if (socket_wrapper::SUCCESS == rval)
//            {
//
//                MI_ClassDecl::ConstPtr pClassDecl (
//                    m_pModule->getSchemaDecl ()->getClassDecl (pClassName));
//                if (pClassDecl)
//                {
//                    MI_MethodDecl::ConstPtr pMethodDecl (
//                        pClassDecl->getMethodDecl (pMethodName->getValue ()));
//                }
//
//                MI_Uint32 flags;
//                rval = m_pSocket->recv (
//                    reinterpret_cast<socket_wrapper::byte_t*>(&flags),
//                    sizeof (MI_Uint32));
//
//                if (socket_wrapper::SUCCESS == rval &&
//                    protocol::HAS_INSTANCE_FLAG ==
//                        (flags & protocol::HAS_INSTANCE_FLAG))
//                {
//                    rval = MI_Instance::recv (
//                        &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
//                    if (socket_wrapper::SUCCESS != rval)
//                    {
//                        SCX_BOOKEND_PRINT ("recv instance failed");
//                    }
//                }
//                if (socket_wrapper::SUCCESS == rval &&
//                    protocol::HAS_INPUT_PARAMETERS_FLAG ==
//                        (flags & protocol::HAS_INPUT_PARAMETERS_FLAG))
//                {
//                    
////                    rval = MI_Instance::recv_parameters (
////                        &pInputParameters, m_pModule->getSchemaDecl (),
////                        *m_pSocket);
////                    rval = MI_Instance::recv (
////                        &pInputParameters, m_pModule->getSchemaDecl (),
////                         *m_pSocket);
//                    if (socket_wrapper::SUCCESS != rval)
//                    {
//                        SCX_BOOKEND_PRINT ("recv input parameters failed");
//                    }
//                }
//
//
////                rval = MI_Instance::recv (
////                    &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
//                if (socket_wrapper::SUCCESS == rval)
//                {
//                    SCX_BOOKEND_PRINT ("Finished receiving Invoke and params");
//                    // temp
//
//
//                    std::ostringstream strm;
//                    strm << "class name: \""
//                         << pClassName->getValue () << "\"";
//                    SCX_BOOKEND_PRINT (strm.str ());
//                    strm.str ("");
//                    strm.clear ();
//                    MI_ClassDecl::ConstPtr pClassDecl =
//                        m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
//                    if (pClassDecl)
//                    {
//                        SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
//                        
//                        strm << "method name: \""
//                             << pMethodName->getValue () << "\"";
//                        SCX_BOOKEND_PRINT (strm.str ());
//                        strm.str ("");
//                        strm.clear ();
//                        MI_MethodDecl::ConstPtr pMethodDecl ( 
//                            pClassDecl->getMethodDecl (
//                                pMethodName->getValue ()));
//
//                        if (pInstance)
//                        {
//                            SCX_BOOKEND_PRINT ("pInstance is not NULL");
//                        }
//                        else
//                        {
//                            SCX_BOOKEND_PRINT ("pInstance is NULL");
//                        }
//
//                        if (pInputParameters)
//                        {
//                            SCX_BOOKEND_PRINT ("pInputParameters is not NULL");
//                        }
//                        else
//                        {
//                            SCX_BOOKEND_PRINT ("pInputParameters is NULL");
//                        }
//
//                        if (pMethodDecl)
//                        {
//                            SCX_BOOKEND_PRINT ("MI_MethodDecl was found");
//
//
////                            MI_MethodDecl::InvokeFn::Ptr pFN =
////                                pMethodDecl->getInvokeFn ();
////                            if (!pFN)
////                            {
////                                SCX_BOOKEND_PRINT ("InvokeFn is NULL");
////                            }
//                            
//                            pMethodDecl->Invoke (
//                                m_pContext, pNameSpace, pClassName, pMethodName,
//                                pInstance, pInputParameters);
//                            
//
//                            rval = EXIT_SUCCESS;
//
//                        }
//                        else
//                        {
//                            SCX_BOOKEND_PRINT ("MI_MethodDecl was not found");
//                            // todo set pyerr
//                            // return MI_RESULT_INVALID_CLASS
//                            
//                            rval = EXIT_FAILURE;
//                        }
//
//
//                    }
//                    else
//                    {
//                        SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
//                        // todo set pyerr
//                        // return MI_RESULT_INVALID_CLASS
//
//                        rval = EXIT_FAILURE;
//                    }
//
//
//                    rval = EXIT_FAILURE;
//                }
//                else
//                {
//                    SCX_BOOKEND_PRINT ("read instance failed");
//                }
//            }
//            else
//            {
//                SCX_BOOKEND_PRINT ("read method name failed");
//            }
//        }
//        else
//        {
//            SCX_BOOKEND_PRINT ("read class name failed");
//        }
//    }
//    else
//    {
//        SCX_BOOKEND_PRINT ("read namespace failed");
//    }
////    if (socket_wrapper::SUCCESS == rval)
////    {
////        rval = MI_Value<MI_STRING>::recv (&pClassName, *m_pSocket);
////        if (socket_wrapper::SUCCESS == rval)
////        {
////            rval = MI_Instance::recv (
////                &pInstance, m_pModule->getSchemaDecl (), *m_pSocket);
////            if (socket_wrapper::SUCCESS != rval)
////            {
////                SCX_BOOKEND_PRINT ("read instance failed");
////                // todo: error
////            }
////        }
////        else
////        {
////            SCX_BOOKEND_PRINT ("read class name failed");
////            // todo set error
////            rval = EXIT_FAILURE;
////        }
////    }
////    else
////    {
////        SCX_BOOKEND_PRINT ("read name space failed");
////        // todo set error
////        rval = EXIT_FAILURE;
////    }
////    if (socket_wrapper::SUCCESS == rval)
////    {
////        std::ostringstream strm;
////        strm << "class name: \"" << pClassName->getValue () << "\"";
////        SCX_BOOKEND_PRINT (strm.str ());
////        strm.str ("");
////        strm.clear ();
////        MI_ClassDecl::ConstPtr pClassDecl =
////            m_pModule->getSchemaDecl ()->getClassDecl (pClassName);
////        if (pClassDecl)
////        {
////            // todo: add pKeysOnly
////            SCX_BOOKEND_PRINT ("MI_ClassDecl was found");
////            rval = pClassDecl->getFunctionTable ()->DeleteInstance (
////                m_pContext, pNameSpace, pClassName, pInstance);
////        }
////        else
////        {
////            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
////            // todo set pyerr
////            // return MI_RESULT_INVALID_CLASS
////            rval = EXIT_FAILURE;
////        }
////    }
////    else
////    {
////        SCX_BOOKEND_PRINT ("read class name failed");
////        // todo set pyerr
////        // return MI_RESULT_INVALID_CLASS
////        rval = EXIT_FAILURE;
////    }
//    return rval;
}


} // namespace scx
