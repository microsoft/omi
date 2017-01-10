#ifndef INCLUDED_CLIENT_WRAPPER_HPP
#define INCLUDED_CLIENT_WRAPPER_HPP


#include "Python.h"


#include "client.hpp"
#include "py_ptr.hpp"


namespace scx
{


class Client_Wrapper
{
public:
    PyObject_HEAD

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);
    static PyObject* run (PyObject* pSelf);

    static PyTypeObject const* getPyTypeObject ();

    /*ctor*/ Client_Wrapper (
        PyObject* pPythonModule,
        Client::Ptr const& pClient);

    /*dtor*/ ~Client_Wrapper ();

private:
    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    PyObjPtr m_pPythonModule;
    Client::Ptr m_pClient;
};
    

} // namespace scx


#endif // INCLUDED_CLIENT_WRAPPER_HPP
