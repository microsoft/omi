#include "Python.h"


#include "debug_tags.hpp"
#include "shared.hpp"


namespace
{


PyTypeObject BookEnd_Type;


char const BOOKEND_NAME[] = "BookEnd";
char const OMI_BOOKEND_NAME[] = "omi.BookEnd";
char const OMI_BOOKEND_DOC[] = "omi.BookEnd utility";

char const BOOKEND_PRINT_NAME[] = "BookEndPrint";
char const BOOKEND_PRINT_DEF[] = "Debuging utility to log output";


struct BookEnd_wrapper
{
    PyObject_HEAD
    scx::BookEnd m_BookEnd;
};


}


extern "C"
{


void
BookEnd_wrapper_dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("BookEnd_wrapper_dealloc");
    if (NULL != pObj)
    {
        BookEnd_wrapper* pBookEnd = reinterpret_cast<BookEnd_wrapper*>(pObj);
        pBookEnd->~BookEnd_wrapper ();
        pBookEnd->ob_type->tp_free (pObj);
    }
}


PyObject*
BookEnd_wrapper_new (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("BookEnd_wrapper_new");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
BookEnd_wrapper_init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("BookEnd_wrapper_init");
    int rval = 0;
    char* KEYWORDS[] = {
        "title",
        "subTitle",
        NULL
    };
    char const* title = NULL;
    char const* subTitle = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "z|z", KEYWORDS, &title, &subTitle))
    {
        BookEnd_wrapper* pBookEnd = reinterpret_cast<BookEnd_wrapper*>(pSelf);
        new (&(pBookEnd->m_BookEnd)) scx::BookEnd (title, subTitle);
    }
    else
    {
        BookEnd_wrapper_dealloc (pSelf);
        PyErr_SetString (PyExc_ValueError,
                         "ERROR: BookEnd_wrapper_init invalid arguments.");
        rval = -1;
    }
    return rval;
}


PyObject*
BookEnd_print (
    PyObject* pSelf,
    PyObject* args)
{
    PyObject* pRet = NULL;
    char const* text = NULL;
    if (1 == PyTuple_Size (args) &&
        PyArg_ParseTuple (args, "s", &text))
    {
        scx::BookEnd::print (text);
        Py_INCREF (Py_None);
        pRet = Py_None;
    }
    else
    {
        PyErr_SetString (PyExc_ValueError,
                         "ERROR: BookEndPrint invalid arguments.");
    }
    return pRet;
}


PyMethodDef const BookEnd_global_methods[] = {
    { BOOKEND_PRINT_NAME, reinterpret_cast<PyCFunction>(BookEnd_print),
      METH_VARARGS, BOOKEND_PRINT_DEF }
};


} // extern "C"


void
get_BookEnd_global_methods (
    PyMethodDefContainer_t& container)
{
    //SCX_BOOKEND ("get_BookEnd_global_methods");
    container.insert (container.end (), BookEnd_global_methods,
                      BookEnd_global_methods + card (BookEnd_global_methods));
}


void
init_BookEnd_wrapper (
    PyObject* const pModule)
{
    //SCX_BOOKEND ("init_BookEnd_wrapper");
    Zero_PyTypeObject (&BookEnd_Type);
    BookEnd_Type.tp_name = OMI_BOOKEND_NAME;
    BookEnd_Type.tp_basicsize = sizeof (BookEnd_wrapper);
    BookEnd_Type.tp_dealloc = BookEnd_wrapper_dealloc;
    BookEnd_Type.tp_flags = Py_TPFLAGS_DEFAULT;
    BookEnd_Type.tp_doc = OMI_BOOKEND_DOC;
    BookEnd_Type.tp_init = BookEnd_wrapper_init;
    BookEnd_Type.tp_new = BookEnd_wrapper_new;
    if (0 == PyType_Ready (&BookEnd_Type))
    {
        Py_INCREF (&BookEnd_Type);
        PyModule_AddObject (pModule, BOOKEND_NAME,
                            reinterpret_cast<PyObject*>(&BookEnd_Type));
    }
}
