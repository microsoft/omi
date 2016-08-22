#ifndef INCLUDED_SERVER_HPP
#define INCLUDED_SERVER_HPP


#include "socket_wrapper.hpp"


#include "debug_tags.hpp"
#include "mi_memory_helper.hpp"
#include "unique_ptr.hpp"


#include <MI.h>


#include <cstdlib>
#include <errno.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class Server
{
public:

    enum Result
    {
        SUCCESS = EXIT_SUCCESS,
        INVALID_STATE,
        SOCKETPAIR_FAILED,
        FORK_FAILED,
        SEND_FAILED,
        INVALID_PARAM,
        GET_ELEMENT_FAILED,
        RECV_FAILED,
        UNRECOGNIZED_PARAM_TYPE,
        BAD_ALLOC,
        UNDEFINED_CLASS,
        INSTANCE_ERROR,
    };


    /*ctor*/ Server (
        std::string interpreter,
        std::string moduleName);
    /*dtor*/ ~Server ();

    int open ();

    socket_wrapper::Ptr const& getSocket () const;

    void setSchema (MI_SchemaDecl const* const pSchema);
    
    MI_ClassDeclEx const* findClassDecl (MI_Char const* const className);

    void Module_Load (
        MI_Module_Self** ppSelf,
        struct _MI_Context* pContext);

    void Load (
        size_t const& index,
        void** ppSelf,
        MI_Module_Self* pSelfModule,
        MI_Context* pContext);

    void Module_Unload (
        MI_Module_Self* pSelf,
        struct _MI_Context* pContext);

    void Unload (
        size_t const& index,
        void* pSelf,
        MI_Context* pContext);

    void EnumerateInstances (
        void* const pSelf,
        MI_Context* const pContext,
        MI_Char const* const nameSpace,
        MI_Char const* const className,
        MI_PropertySet const* const pPropertySet,
        MI_Boolean const keysOnly,
        MI_Filter const* const pFilter);

    void GetInstance (
        void* const pSelf,
        MI_Context* const pContext,
        MI_Char const* const nameSpace,
        MI_Char const* const className,
        MI_Instance const* pInstanceName,
        MI_PropertySet const* const pPropertySet);
    
    void CreateInstance (
        void* pSelf,
        MI_Context* pContext,
        MI_Char const* nameSpace,
        MI_Char const* className,
        MI_Instance const* pNewInstance);
    
    void ModifyInstance (
        void* pSelf,
        MI_Context* pContext,
        MI_Char const* nameSpace,
        MI_Char const* className,
        MI_Instance const* pModifiedInstance,
        MI_PropertySet const* pPropertySet);

    void DeleteInstance (
        void* const pSelf,
        MI_Context* const pContext,
        MI_Char const* const nameSpace,
        MI_Char const* const className,
        MI_Instance const* pInstanceName);

private:

    /*ctor*/ Server (Server const&); // delete
    Server& operator = (Server const&); // delete

    std::string const m_Interpreter;
    std::string const m_ModuleName;
    socket_wrapper::Ptr m_pSocket;
    util::unique_ptr<MI_SchemaDecl const, MI_Deleter<MI_SchemaDecl const> >
        m_pSchemaDecl;
    std::vector<MI_Char const*> m_ClassNames;
};


inline socket_wrapper::Ptr const&
Server::getSocket () const
{
    return m_pSocket;
}


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& errnoText (
    std::basic_ostream<char_t, traits_t>& strm);


MI_EXTERN_C void
MI_CALL Load (
    void** ppSelf,
    MI_Module_Self* pSelfModule,
    MI_Context* pContext);

MI_EXTERN_C void
MI_CALL Unload (
    void* pSelf,
    MI_Context* pContext);

MI_EXTERN_C void
MI_CALL EnumerateInstances (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_PropertySet const* pPropertySet,
    MI_Boolean keysOnly,
    MI_Filter const* pFilter);

MI_EXTERN_C void
MI_CALL GetInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName,
    MI_PropertySet const* pPropertySet);

MI_EXTERN_C void
MI_CALL CreateInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pNewInstance);

MI_CALL void
MI_CALL ModifyInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pModifiedInstance,
    MI_PropertySet const* pPropertySet);

MI_CALL void
MI_CALL DeleteInstance (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Instance const* pInstanceName);

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
    MI_Filter const* pFilter);

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
    MI_Filter const* pFilter);

MI_EXTERN_C void
MI_CALL EnableIndications (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className);

MI_EXTERN_C void
MI_CALL DisableIndications (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className);

MI_EXTERN_C void
MI_CALL Subscribe (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Filter const* pFilter,
    MI_Char const* bookmark,
    MI_Uint64 subscriptionID,
    void** ppSubscriptionSelf);

MI_EXTERN_C void
MI_CALL Unsubscribe (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Uint64 subscriptionID,
    void* pSubscriptionSelf);

MI_EXTERN_C void
MI_CALL Invoke (
    void* pSelf,
    MI_Context* pContext,
    MI_Char const* nameSpace,
    MI_Char const* className,
    MI_Char const* methodName,
    MI_Instance const* pInstance,
    MI_Instance const* pInputParameters);


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& errnoText (
    std::basic_ostream<char_t, traits_t>& strm)
{
    static size_t const BUFFER_LEN = 256;
    char errorBuffer[BUFFER_LEN];
    int err = errno;
    char* pErrorText = strerror_r (err, errorBuffer, BUFFER_LEN);
    strm << pErrorText;
    errno = err;
    return strm;
}


#endif // INCLUDED_SERVER_HPP
