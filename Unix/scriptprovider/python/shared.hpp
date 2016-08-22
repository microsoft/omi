#ifndef SHARED_HPP
#define SHARED_HPP


#include "Python.h"


#include <vector>


template<typename T, size_t N>
size_t
card (T const (&)[N])
{
    return N;
}


typedef std::vector<PyMethodDef> PyMethodDefContainer_t;


void
Zero_PyTypeObject (
    PyTypeObject* pObjOut);


void
get_BookEnd_global_methods (
    PyMethodDefContainer_t& container);


void
init_BookEnd_wrapper (
    PyObject* const pModule);


void
init_MI_wrapper (
    PyObject* const pModule);


//extern "C" PyObject*
//BookEnd_print (
//    PyObject* pSelf,
//    PyObject* args);


#endif // SHARED_HPP
