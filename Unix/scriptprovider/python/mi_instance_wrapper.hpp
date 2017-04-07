#ifndef INCLUDED_MI_INSTANCE_WRAPPER_HPP
#define INCLUDED_MI_INSTANCE_WRAPPER_HPP


#include "Python.h"


#include "mi_instance.hpp"
#include "py_ptr.hpp"


namespace scx
{


class MI_Instance_Wrapper
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_Instance_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyObject* getValue (PyObject* pSelf,
                               PyObject* args,
                               PyObject* keywords);
    static PyObject* setValue (PyObject* pSelf,
                               PyObject* args,
                               PyObject* keywords);

    static PyPtr createPyPtr (MI_Instance::Ptr const& pInstance);

    static PyTypeObject* getPyTypeObject ();

    void ctor (MI_Instance::Ptr const& pInstance);
    void dtor ();

    MI_Instance::Ptr const& getInstance () const;

private:
    /*ctor*/ MI_Instance_Wrapper (MI_Instance_Wrapper const&); // delete
    MI_Instance_Wrapper& operator = (MI_Instance_Wrapper const&); // delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    MI_Instance::Ptr m_pInstance;
};


inline MI_Instance::Ptr const&
MI_Instance_Wrapper::getInstance () const
{
    return m_pInstance;
}
    

} // namespace scx


#endif // INCLUDED_MI_INSTANCE_WRAPPER_HPP
