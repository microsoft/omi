#include "functor.hpp"


#include "mi_context_wrapper.hpp"
#include "mi_module_wrapper.hpp"
#include "mi_instance_wrapper.hpp"


#include <cassert>


namespace scx
{


/*ctor*/
Load_Unload_Functor::Load_Unload_Functor (
    py_ptr<PyObject> const& pFn)
    : m_pFn (pFn)
{
    //SCX_BOOKEND ("Load_Unload_Functor::ctor");
}


/*dtor*/
Load_Unload_Functor::~Load_Unload_Functor ()
{
    //SCX_BOOKEND ("Load_Unload_Functor::dtor");
}


int
Load_Unload_Functor::operator () (
    scx::MI_Module::Ptr const& pModule,
    scx::MI_Context::Ptr const& pContext) const
{
    SCX_BOOKEND ("Load_Unload_Functor::operator ()");
    int rval = EXIT_SUCCESS;
//    MI_Module_Py::Ptr pPyModule (static_cast<MI_Module_Py*>(pModule.get ()));
//    MI_Module_Wrapper::PyPtr pyModule (
//        MI_Module_Wrapper::createPyPtr (pPyModule));
    MI_Module_Wrapper::PyPtr pyModule (
        MI_Module_Wrapper::createPyPtr (pModule));
    MI_Context_Wrapper::PyPtr pyContext (
        MI_Context_Wrapper::createPyPtr (pContext));
    if (pyModule && pyContext)
    {
        PyObjPtr pArgs (PyTuple_New (2));
        if (pArgs)
        {
            PyTuple_SetItem (pArgs.get (), 0,
                             reinterpret_cast<PyObject*>(pyModule.get ()));
            PyTuple_SetItem (pArgs.get (), 1,
                             reinterpret_cast<PyObject*>(pyContext.get ()));

            if (m_pFn)
            {
                SCX_BOOKEND_PRINT ("m_pFn is not NULL");
            }
            else
            {
                SCX_BOOKEND_PRINT ("m_pFn is NULL");
            }

            PyObjPtr pRval (PyObject_CallObject (m_pFn.get (), pArgs.get ()));

            if (!pRval)
            {
                SCX_BOOKEND_PRINT ("Error returned from call");
                rval = EXIT_FAILURE;
            }
            else
            {
                if (Py_None == pRval.get ())
                {
                    SCX_BOOKEND_PRINT ("an object was returned (Py_None)");
                }
                else
                {
                    SCX_BOOKEND_PRINT ("an object was returned (not Py_None)");
                }
            }
        }
    }
    else
    {
        PyErr_SetString (PyExc_TypeError, "invalid argument");
        rval = EXIT_FAILURE;
    }
    return rval;
}


} // namespace scx
