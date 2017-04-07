#ifndef INCLUDED_MI_CONTEXT_HPP
#define INCLUDED_MI_CONTEXT_HPP


#include "internal_counted_ptr.hpp"
#include "mi_value.hpp"
#include "socket_wrapper.hpp"


#ifndef EXPORT_PUBLIC
#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))
#endif


namespace scx
{


class MI_Instance;
class MI_SchemaDecl;


class EXPORT_PUBLIC MI_Context : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_Context> Ptr;

    EXPORT_PUBLIC /*ctor*/ MI_Context (
        socket_wrapper::Ptr const& pSocket,
        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl);
    EXPORT_PUBLIC virtual /*dtor*/ ~MI_Context ();

    EXPORT_PUBLIC int postResult (MI_Result const& result);
    EXPORT_PUBLIC int postInstance (
        util::internal_counted_ptr<MI_Instance const> const& pInstance);

    EXPORT_PUBLIC int newInstance (
        MI_Value<MI_STRING>::ConstPtr const& pClassName,
        util::internal_counted_ptr<MI_Instance>* ppInstanceOut);
    EXPORT_PUBLIC int newParameters (
        MI_Value<MI_STRING>::ConstPtr const& pClassName,
        MI_Value<MI_STRING>::ConstPtr const& pMethodName,
        util::internal_counted_ptr<MI_Instance>* ppInstanceOut);

    bool getResultSent () const;
    void resetResultSent ();

private:
    /*ctor*/ MI_Context (MI_Context const&); // = delete
    MI_Context& operator = (MI_Context const&); // = delete

    socket_wrapper::Ptr const m_pSocket;
    util::internal_counted_ptr<MI_SchemaDecl const> const m_pSchemaDecl;
    bool m_ResultSent;
};


inline bool
MI_Context::getResultSent () const
{
    return m_ResultSent;
}


inline void
MI_Context::resetResultSent ()
{
    m_ResultSent = false;
}


}


#undef EXPORT_PUBLIC


#endif // INCLUDED_MI_CONTEXT_HPP
