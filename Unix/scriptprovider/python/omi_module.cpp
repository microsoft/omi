#include "Python.h"
#include <MI.h>


#include "mi_instance_wrapper.hpp"

//#include "client_wrapper.hpp"
#include "debug_tags.hpp"
#include "shared.hpp"


#include "mi_value.hpp"


#include <iostream>
#include <new>
#include <sstream>
#include <string>


namespace {


char* KEYWORDS[] = {
    "name",
    NULL
};


PyMethodDefContainer_t g_methods;


}


using namespace scx;


class Foo
{
public:
    PyObject_HEAD

    /*ctor*/ Foo ()
        : m_Name ("Blank")
    {
        std::cout << "Foo::ctor \"" << m_Name << '\"' << std::endl;
    }

    /*ctor*/ Foo (char const* const name)
        : m_Name (name)
    {
        std::cout << "Foo::ctor \"" << m_Name << '\"' << std::endl;
    }

    /*dtor*/ ~Foo ()
    {
        std::cout << "Foo::dtor \"" << m_Name << '\"' << std::endl;
    }

private:
    std::string const m_Name;
};


extern "C" {


static void
Foo_dealloc (
    PyObject* pObj)
{
    std::cout << "<Foo_dealloc>" << std::endl;
    if (NULL != pObj)
    {
        Foo* pFoo = reinterpret_cast<Foo*>(pObj);
        pFoo->~Foo ();
        //pFoo->ob_type->tp_free (reinterpret_cast<PyObject*>(pFoo));
        pFoo->ob_type->tp_free (pObj);
    }
    std::cout << "</Foo_dealloc>" << std::endl;
}


static PyObject*
Foo_new (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    std::cout << "<Foo_new>" << std::endl;
    Foo* pFoo = NULL;

    char const* pName = NULL;

    std::cout << "PyArg_ParseTupleAndKeywords ";
    if (PyArg_ParseTupleAndKeywords (args, keywords, "|s", KEYWORDS, &pName))
    {
        pFoo = reinterpret_cast<Foo*>(pType->tp_alloc (pType, 0));
        std::cout << "Succeeded" << std::endl << "pName is ";
        if (NULL != pName)
        {
            std::cout << pName << std::endl;
            new (pFoo) Foo (pName);
        }
        else
        {
            std::cout << "NULL" << std::endl;
            new (pFoo) Foo ();
        }
    }
    else
    {
        std::cout << "Failed!" << std::endl;
        
    }
    std::cout << "</Foo_new>" << std::endl;

    return reinterpret_cast<PyObject*>(pFoo);
}


static int
Foo_init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    std::cout << "<Foo_init>" << std::endl;

    std::cout << "PyArg_ParseTupleAndKeywords ";
    char const* pName = NULL;
    if (PyArg_ParseTupleAndKeywords (args, keywords, "|s", KEYWORDS, &pName))
    {
        std::cout << "Succeeded" << std::endl;
        std::cout << "pName is ";
        if (NULL != pName)
        {
            //std::cout << PyString_AS_STRING (pName) << std::endl;
            std::cout << pName << std::endl;
        }
        else
        {
            std::cout << "NULL" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed!" << std::endl;
    }

    std::cout << "</Foo_init>" << std::endl;
    return 0;
}


static PyTypeObject omi_FooType = {
    PyObject_HEAD_INIT (NULL)
    0,                      // ob_size
    "omi_module.Foo",       // tp_name
    sizeof (Foo),           // tp_basicsize
    0,                      // tp_itemsize
    Foo_dealloc,            // tp_dealloc
    0,                      // tp_print
    0,                      // tp_getattr
    0,                      // tp_setattr
    0,                      // tp_compare
    0,                      // tp_repr
    0,                      // tp_as_number
    0,                      // tp_as_sequence
    0,                      // tp_as_mapping
    0,                      // tp_hash
    0,                      // tp_call
    0,                      // tp_str
    0,                      // tp_getattro
    0,                      // tp_setattro
    0,                      // tp_as_buffer
    Py_TPFLAGS_DEFAULT,     // tp_flags
    "omi_module.Foo object",// tp_doc
    0,                      // tp_traverse
    0,                      // tp_clear
    0,                      // tp_richcompare
    0,                      // tp_weaklistoffset
    0,                      // tp_iter
    0,                      // tp_iternext
    0,                      // tp_methods
    0,                      // tp_members
    0,                      // tp_getset
    0,                      // tp_base
    0,                      // tp_dict
    0,                      // tp_descr_get
    0,                      // tp_descr_set
    0,                      // tp_dictoffset
    Foo_init,               // tp_init
    0,                      // tp_alloc
    Foo_new                 // tp_new
};


//static PyMethodDef omi_Foo_methods[] = {
//    { NULL, NULL, 0, NULL }
//};


//static PyObject*
//omi_method (
//    PyObject* self,
//    PyObject* args)
//{
//    // args is a tuple
//
//    // use PyArg_ParseTuple to unpack a tuple
//    // use Py_BuildValue to do something like the reverse
//
//    // If the function fails is should return an error value (usually NULL)
//    // And set an exception value.
//    //   Exceptions are stored in a static global vaiable in the interpreter.
//    // A second global variable stores the "associated value" of the exception.
//    //   Second argument to "raise"
//    // A third variable contains the stack traceback.
//
//    // These variables are:
//    //   sys.exc_type
//    //   sys.exc_value
//    //   sys.exc_traceback
//
//    // Use PyErr_SetString to set error.
//    //   PyExc_ZeroDivisionError
//    //   PyErr_SetFromErrno
//    //   PyErr_SetObject
//
//    // Py_XDECREF
//    // Py_DECREF
//
//    // Py_INCREF
//
//    // use Py_RETURN_NONE (return Py_None) to return void
//
//    return Py_None;
//}


//static PyObject*
//omi_MI_STRING (
//    PyObject* self,
//    PyObject* args)
//{
//    return Py_BuildValue ("I", MI_STRING);
//}


//void
PyMODINIT_FUNC
initomi ()
{
    SCX_BOOKEND ("initomi");

//    {
//        SCX_BOOKEND ("MI_Array tests");
//        std::ostringstream strm;
//
//        scx::MI_Array<MI_UINT32A> uint32_array;
//
//        scx::MI_Value<MI_UINT32>::Ptr pVal0 (new scx::MI_Value<MI_UINT32> (12));
//        strm << "pVal0: " << pVal0->getValue ();
//        SCX_BOOKEND_PRINT (strm.str ().c_str ());
//        uint32_array.push_back (pVal0);
//        scx::MI_Value<MI_UINT32>::Ptr pVal1 = uint32_array[0];
//        strm.str ("");
//        strm << "pVal1: " << pVal1->getValue ();
//        SCX_BOOKEND_PRINT (strm.str ().c_str ());
//        pVal0 = new scx::MI_Value<MI_UINT32> (15);
//        uint32_array.insert (0, pVal0);
//        pVal0 = new scx::MI_Value<MI_UINT32> (13);
//        uint32_array.insert (1, pVal0);
//
//        pVal0 = new scx::MI_Value<MI_UINT32> (14);
//        uint32_array.insert (1, pVal0);
//        {
//            SCX_BOOKEND ("MI_Array contents");
//            for (size_t i = 0, count = uint32_array.size (); i < count; ++i)
//            {
//                
//                strm.str ("");
//                strm << i << ": " << uint32_array[i]->getValue ();
//                
//                SCX_BOOKEND_PRINT (strm.str ().c_str ());
//            }
//        }
//
//    }

    // global methods
    get_BookEnd_global_methods (g_methods);
//    get_Client_global_methods (g_methods);
    PyMethodDef const sentinel = { NULL, NULL, 0, NULL };
    g_methods.push_back (sentinel);


    PyObject* pModule =
        Py_InitModule3 ("omi", &(g_methods[0]),
                        "Module that creates the Foo extension type.");


    // classes
//    init_MI_Instance_Wrapper (pModule);
    init_BookEnd_wrapper (pModule);
    init_MI_wrapper (pModule);

    if (0 > PyType_Ready (&omi_FooType))
    {
        return;
    }

    Py_INCREF (&omi_FooType);
    PyModule_AddObject (pModule, "Foo",
                        reinterpret_cast<PyObject*>(&omi_FooType));
}


}
