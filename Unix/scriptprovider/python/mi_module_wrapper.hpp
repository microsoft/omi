#ifndef INCLUDED_MI_MODULE_WRAPPER_HPP
#define INCLUDED_MI_MODULE_WRAPPER_HPP


#include "Python.h"


#include "functor.hpp"
#include "mi_module.hpp"
#include "py_ptr.hpp"
#include "mi_schema_wrapper.hpp"


namespace scx
{


//class MI_Module_Py : public MI_Module
//{
//public:
//    typedef util::internal_counted_ptr<MI_Module_Py> Ptr;
//
//
//    /*ctor*/ MI_Module_Py (
//        util::internal_counted_ptr<MI_SchemaDecl const> const& pSchemaDecl,
//        LoadFn::Ptr const& pLoadFn,
//        UnloadFn::Ptr const& pUnloadFn);
//
//    /*dtor*/ ~MI_Module_Py ();
//
//};


class MI_Module_Wrapper
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_Module_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    static PyPtr createPyPtr (MI_Module::Ptr const& pModule);

    /*dtor*/ ~MI_Module_Wrapper ();

    MI_Module::Ptr const& createModule (PyObject* const pPyModule);
//    MI_Module_Py::Ptr const& getModule () const;

private:
    /*ctor*/ MI_Module_Wrapper (
        MI_SchemaDecl_Placeholder::ConstPtr const& pSchemaDecl_PH,
        MI_Module::LoadFn::Ptr const& pLoadFn,
        MI_Module::UnloadFn::Ptr const& pUnloadFn);

    /*ctor*/ MI_Module_Wrapper (MI_Module::Ptr const& pModule);

    /*ctor*/ MI_Module_Wrapper (MI_Module_Wrapper const&); // = delete
    MI_Module_Wrapper& operator = (MI_Module_Wrapper const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    MI_SchemaDecl_Placeholder::ConstPtr const m_pSchemaDecl_PH;
    MI_Module::LoadFn::Ptr const m_pLoadFn;
    MI_Module::UnloadFn::Ptr const m_pUnloadFn;

    MI_Module::Ptr m_pModule;
};


} // namespace scx


#endif // INCLUDED_MI_MODULE_WRAPPER_HPP
