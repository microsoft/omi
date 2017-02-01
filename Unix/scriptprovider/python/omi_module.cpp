#include "Python.h"
#include <MI.h>


#include "debug_tags.hpp"
#include "mi_instance_wrapper.hpp"
#include "shared.hpp"


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


extern "C" {


PyMODINIT_FUNC
initomi ()
{
    SCX_BOOKEND ("initomi");
    // global methods
    get_BookEnd_global_methods (g_methods);
    PyMethodDef const sentinel = { NULL, NULL, 0, NULL };
    g_methods.push_back (sentinel);
    PyObject* pModule =
        Py_InitModule3 ("omi", &(g_methods[0]),
                        "Module that creates the Foo extension type.");

    // classes
    init_BookEnd_wrapper (pModule);
    init_MI_wrapper (pModule);
}


}
