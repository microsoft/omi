// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_MI_CONTEXT_WRAPPER_HPP
#define INCLUDED_MI_CONTEXT_WRAPPER_HPP


#include "Python.h"


#include "mi_context.hpp"
#include "py_ptr.hpp"


namespace scx
{


class MI_Context_Wrapper
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_Context_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static PyObject* postResult (PyObject* pSelf,
                                 PyObject* args,
                                 PyObject* keywords);

    static PyObject* postInstance (PyObject* pSelf,
                                   PyObject* args,
                                   PyObject* keywords);

    static PyObject* newInstance (PyObject* pSelf,
                                  PyObject* args,
                                  PyObject* keywords);

    static PyObject* newParameters (PyObject* pSelf,
                                    PyObject* args,
                                    PyObject* keywords);

    static PyPtr createPyPtr (MI_Context::Ptr const& pContext);

    static PyTypeObject const* getPyTypeObject ();

    /*ctor*/ MI_Context_Wrapper (MI_Context::Ptr const& pContext);

    /*dtor*/ ~MI_Context_Wrapper ();

private:
    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    MI_Context::Ptr const m_pContext;
};


} // namespace scx


#endif // INCLUDED_MI_CONTEXT_WRAPPER_HPP
