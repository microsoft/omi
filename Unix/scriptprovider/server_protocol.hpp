#ifndef INCLUDED_SERVER_PROTOCOL_HPP
#define INCLUDED_SERVER_PROTOCOL_HPP


#include "mi_script_extensions.hpp"
#include "shared_protocol.hpp"


namespace protocol
{


//int
//recv (
//    MI_Datetime* const pDatetimeOut,
//    socket_wrapper& sock);


int
recv (
    MI_Instance** const ppInstanceOut,
    MI_Context* const pContext,
    MI_SchemaDecl const* const pSchema,
    socket_wrapper& sock);


int
recv (
    MI_QualifierDecl** const ppQualifierDeclOut,
    socket_wrapper& sock);


int
recv (
    MI_Qualifier** const ppQualifierOut,
    socket_wrapper& sock);


int
recv (
    MI_PropertyDecl** const ppPropertyDeclOut,
    socket_wrapper& sock);


int
recv (
    MI_ParameterDecl** const ppParameterDeclOut,
    socket_wrapper& sock);


int
recv (
    MI_MethodDecl** const ppMethodDeclOut,
    socket_wrapper& sock);


int
recv (
    MI_ProviderScriptFT** const ppProviderScriptFTOut,
    socket_wrapper& sock);


int
recv (
    MI_ClassDeclEx** const ppClassDeclExOut,
    socket_wrapper& sock);


int
recv (
    MI_SchemaDecl** const ppSchemaOut,
    socket_wrapper& sock);


int
send (
    MI_Instance const& instance,
    socket_wrapper& sock);


int
send (
    MI_PropertySet const* const pPropertySet,
    socket_wrapper& sock);


} // namespace protocol


#endif // INCLUDED_SERVER_PROTOCOL_HPP
