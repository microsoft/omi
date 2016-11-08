#ifndef INCLUDED_CLIENT_HPP
#define INCLUDED_CLIENT_HPP


#include "internal_counted_ptr.hpp"
#include "mi_context.hpp"
#include "mi_module.hpp"
#include "socket_wrapper.hpp"


#include <cstdlib>


#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))


namespace scx
{


class Client : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<Client> Ptr;
    
    enum {
        SUCCESS = EXIT_SUCCESS,
    };

    EXPORT_PUBLIC /*ctor*/ Client (
        socket_wrapper::Ptr const& pSocket,
        MI_Module::Ptr const& pModule);
    EXPORT_PUBLIC virtual /*dtor*/ ~Client ();

    EXPORT_PUBLIC int run ();

private:
    int handle_module_load ();
    int handle_module_unload ();
    int handle_class_load ();
    int handle_class_unload ();
    int handle_enumerate_instances ();
    bool handle_get_instance ();
    bool handle_create_instance ();
    bool handle_modify_instance ();
    bool handle_delete_instance ();

    bool handle_invoke ();

    /*ctor*/ Client (Client const&); // = delete
    Client& operator = (Client const&); // = delete
    
    socket_wrapper::Ptr const m_pSocket;
    MI_Module::Ptr const m_pModule;
    MI_Context::Ptr const m_pContext;
};


} // namespace scx


#undef EXPORT_PUBLIC


#endif // INCLUDED_CLIENT_HPP
