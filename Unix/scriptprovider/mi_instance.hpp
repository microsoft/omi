#ifndef INCLUDED_MI_INSTANCE_HPP
#define INCLUDED_MI_INSTANCE_HPP


#include "internal_counted_ptr.hpp"
#include "mi_value.hpp"
#include "socket_wrapper.hpp"


#include <map>


namespace scx
{


class MI_ObjectDecl;
class MI_SchemaDecl;


#ifndef EXPORT_PUBLIC
#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))
#endif


class EXPORT_PUBLIC MI_Instance : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Instance> Ptr;
    typedef util::internal_counted_ptr<MI_Instance const> ConstPtr;
    typedef std::map<MI_Type<MI_STRING>::type_t, MI_ValueBase::Ptr> value_map_t;

    EXPORT_PUBLIC explicit /*ctor*/ MI_Instance (
        util::internal_counted_ptr<MI_ObjectDecl const> const& pObjectDecl);
    EXPORT_PUBLIC explicit /*ctor*/ MI_Instance (MI_Instance const& ref);
    EXPORT_PUBLIC /*dtor*/ ~MI_Instance ();

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC MI_Instance& operator = (MI_Instance const& rval);

    EXPORT_PUBLIC util::internal_counted_ptr<MI_ObjectDecl const> const&
    getObjectDecl () const;

    EXPORT_PUBLIC int getValue (
        MI_Value<MI_STRING>::type_t const& name,
        MI_ValueBase::Ptr* ppValueOut) const;
    EXPORT_PUBLIC int setValue (
        MI_Value<MI_STRING>::type_t const& name,
        MI_ValueBase::Ptr const& pValue);

    EXPORT_PUBLIC int send (socket_wrapper& sock) const;

    static int recv (
        Ptr* const ppInstanceOut,
        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl,
        socket_wrapper& sock);

    static int recv (
        Ptr* const ppInstanceOut,
        util::internal_counted_ptr<MI_ObjectDecl const> const& pObjectDecl,
        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl,
        socket_wrapper& sock);

private:
    static int recv_values (
        value_map_t* const pValueMapOut,
        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl,
        socket_wrapper& sock);

    static int confirm_values (
        value_map_t const& valueMap,
        util::internal_counted_ptr<MI_ObjectDecl const> const& pObjectDecl);

    util::internal_counted_ptr<MI_ObjectDecl const> m_pObjectDecl;
    value_map_t m_ValueMap;
};


};


#endif // INCLUDED_MI_INSTANCE_HPP
