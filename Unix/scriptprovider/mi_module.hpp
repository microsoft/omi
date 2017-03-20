#ifndef INCLUDED_MI_MODULE_HPP
#define INCLUDED_MI_MODULE_HPP


#include "MI.h"


#include "function_helper.hpp"
#include "internal_counted_ptr.hpp"
#include "socket_wrapper.hpp"


#ifndef EXPORT_PUBLIC
#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))
#endif


namespace scx
{


class MI_SchemaDecl;
class MI_Context;


class EXPORT_PUBLIC MI_Module : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_Module> Ptr;
    typedef util::internal_counted_ptr<MI_Module const> ConstPtr;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Module> const&,
        util::internal_counted_ptr<MI_Context> const&> LoadFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Module> const&,
        util::internal_counted_ptr<MI_Context> const&> UnloadFn;


    EXPORT_PUBLIC /*ctor*/ MI_Module (
        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl,
        LoadFn::Ptr const& pLoadFn,
        UnloadFn::Ptr const& pUnloadFn);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_Module ();

    EXPORT_PUBLIC util::internal_counted_ptr<MI_SchemaDecl const> const&
    getSchemaDecl () const;

    LoadFn::Ptr const& getLoadFn () const;
    UnloadFn::Ptr const& getUnloadFn () const;

private:

    MI_Uint32 const m_Version;
    MI_Uint32 const m_GeneratorVersion;
    MI_Uint32 const m_Flags;
    MI_Uint32 const m_CharSize;

    util::internal_counted_ptr<MI_SchemaDecl const> m_pSchemaDecl;
    LoadFn::Ptr m_pLoadFn;
    UnloadFn::Ptr m_pUnloadFn;
};


inline util::internal_counted_ptr<MI_SchemaDecl const> const&
MI_Module::getSchemaDecl () const
{
    return m_pSchemaDecl;
}


inline MI_Module::LoadFn::Ptr const&
MI_Module::getLoadFn () const
{
    return m_pLoadFn;
}


inline MI_Module::UnloadFn::Ptr const&
MI_Module::getUnloadFn () const
{
    return m_pUnloadFn;
}


} // namespace scx


#undef EXPORT_PUBLIC


#endif // INCLUDED_MI_MODULE_HPP
