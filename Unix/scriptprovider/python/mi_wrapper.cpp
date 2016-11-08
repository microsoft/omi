#include "Python.h"


#include "mi_wrapper.hpp"


#include "client_wrapper.hpp"
#include "debug_tags.hpp"
#include "mi_context_wrapper.hpp"
#include "mi_instance_wrapper.hpp"
#include "mi_module_wrapper.hpp"
#include "mi_schema_wrapper.hpp"
#include "mi_function_table_placeholder.hpp"
#include "shared_protocol.hpp"
#include "shared.hpp"


using namespace scx;


namespace
{


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
operator << (
    std::basic_ostream<char_t, traits_t>& strm,
    scx::MI_Timestamp const& timestamp)
{
    strm << scx::MI_Timestamp_Wrapper::NAME
         << "(Year(" << timestamp.getYear ()
         << "),Month(" << timestamp.getMonth ()
         << "),Day(" << timestamp.getDay ()
         << "),Hour(" << timestamp.getHour ()
         << "),Minute(" << timestamp.getMinute ()
         << "),Second(" << timestamp.getSecond ()
         << "),Microseconds(" << timestamp.getMicroseconds ()
         << "),UTC(" << timestamp.getUTC () << "))";
    return strm;
}


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
operator << (
    std::basic_ostream<char_t, traits_t>& strm,
    scx::MI_Interval const& interval)
{
    strm << scx::MI_Interval_Wrapper::NAME
         << "(Days(" << interval.getDays ()
         << "),Hours(" << interval.getHours ()
         << "),Minutes(" << interval.getMinutes ()
         << "),Seconds(" << interval.getSeconds ()
         << "),Microseconds(" << interval.getMicroseconds ()
         << "))";
    return strm;
}


}


void
init_MI_wrapper (
    PyObject* const pModule)
{
    SCX_BOOKEND ("init_MI_wrapper");

    MI_Wrapper<MI_BOOLEAN>::moduleInit (pModule);
    MI_Wrapper<MI_SINT8>::moduleInit (pModule);
    MI_Wrapper<MI_UINT8>::moduleInit (pModule);
    MI_Wrapper<MI_SINT16>::moduleInit (pModule);
    MI_Wrapper<MI_UINT16>::moduleInit (pModule);
    MI_Wrapper<MI_SINT32>::moduleInit (pModule);
    MI_Wrapper<MI_UINT32>::moduleInit (pModule);
    MI_Wrapper<MI_SINT64>::moduleInit (pModule);
    MI_Wrapper<MI_UINT64>::moduleInit (pModule);
    MI_Wrapper<MI_REAL32>::moduleInit (pModule);
    MI_Wrapper<MI_REAL64>::moduleInit (pModule);
    MI_Wrapper<MI_CHAR16>::moduleInit (pModule);
    MI_Wrapper<MI_STRING>::moduleInit (pModule);

    MI_Timestamp_Wrapper::moduleInit (pModule);
    MI_Interval_Wrapper::moduleInit (pModule);

    MI_Array_Wrapper<MI_BOOLEANA>::moduleInit (pModule);
    MI_Array_Wrapper<MI_UINT8A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_SINT8A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_UINT16A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_SINT16A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_UINT32A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_SINT32A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_UINT64A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_SINT64A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_REAL32A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_REAL64A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_CHAR16A>::moduleInit (pModule);
    MI_Array_Wrapper<MI_DATETIMEA>::moduleInit (pModule);
    MI_Array_Wrapper<MI_STRINGA>::moduleInit (pModule);

    MI_Module_Wrapper::moduleInit (pModule);
    MI_Context_Wrapper::moduleInit (pModule);
    MI_Instance_Wrapper::moduleInit (pModule);
    MI_QualifierDecl_Wrapper::moduleInit (pModule);
    MI_Qualifier_Wrapper::moduleInit (pModule);
    MI_PropertyDecl_Wrapper::moduleInit (pModule);
    MI_ParameterDecl_Wrapper::moduleInit (pModule);
    MI_MethodDecl_Placeholder::moduleInit (pModule);
    MI_FunctionTable_Placeholder::moduleInit (pModule);
    MI_ClassDecl_Placeholder::moduleInit (pModule);
    MI_SchemaDecl_Placeholder::moduleInit (pModule);
    MI_PropertySet_Wrapper::moduleInit (pModule);

    Client_Wrapper::moduleInit (pModule);

    PyModule_AddIntConstant (pModule, "MI_BOOLEAN", MI_BOOLEAN);
    PyModule_AddIntConstant (pModule, "MI_UINT8", MI_UINT8);
    PyModule_AddIntConstant (pModule, "MI_SINT8", MI_SINT8);
    PyModule_AddIntConstant (pModule, "MI_UINT16", MI_UINT16);
    PyModule_AddIntConstant (pModule, "MI_SINT16", MI_SINT16);
    PyModule_AddIntConstant (pModule, "MI_UINT32", MI_UINT32);
    PyModule_AddIntConstant (pModule, "MI_SINT32", MI_SINT32);
    PyModule_AddIntConstant (pModule, "MI_UINT64", MI_UINT64);
    PyModule_AddIntConstant (pModule, "MI_SINT64", MI_SINT64);
    PyModule_AddIntConstant (pModule, "MI_REAL32", MI_REAL32);
    PyModule_AddIntConstant (pModule, "MI_REAL64", MI_REAL64);
    PyModule_AddIntConstant (pModule, "MI_CHAR16", MI_CHAR16);
    PyModule_AddIntConstant (pModule, "MI_DATETIME", MI_DATETIME);
    PyModule_AddIntConstant (pModule, "MI_STRING", MI_STRING);
    PyModule_AddIntConstant (pModule, "MI_REFERENCE", MI_REFERENCE);
    PyModule_AddIntConstant (pModule, "MI_INSTANCE", MI_INSTANCE);
    
    PyModule_AddIntConstant (pModule, "MI_BOOLEANA", MI_BOOLEANA);
    PyModule_AddIntConstant (pModule, "MI_UINT8A", MI_UINT8A);
    PyModule_AddIntConstant (pModule, "MI_SINT8A", MI_SINT8A);
    PyModule_AddIntConstant (pModule, "MI_UINT16A", MI_UINT16A);
    PyModule_AddIntConstant (pModule, "MI_SINT16A", MI_SINT16A);
    PyModule_AddIntConstant (pModule, "MI_UINT32A", MI_UINT32A);
    PyModule_AddIntConstant (pModule, "MI_SINT32A", MI_SINT32A);
    PyModule_AddIntConstant (pModule, "MI_UINT64A", MI_UINT64A);
    PyModule_AddIntConstant (pModule, "MI_SINT64A", MI_SINT64A);
    PyModule_AddIntConstant (pModule, "MI_REAL32A", MI_REAL32A);
    PyModule_AddIntConstant (pModule, "MI_REAL64A", MI_REAL64A);
    PyModule_AddIntConstant (pModule, "MI_CHAR16A", MI_CHAR16A);
    PyModule_AddIntConstant (pModule, "MI_DATETIMEA", MI_DATETIMEA);
    PyModule_AddIntConstant (pModule, "MI_STRINGA", MI_STRINGA);
    PyModule_AddIntConstant (pModule, "MI_REFERENCEA", MI_REFERENCEA);
    PyModule_AddIntConstant (pModule, "MI_INSTANCEA", MI_INSTANCEA);

    PyModule_AddIntConstant (pModule, "MI_NULL_FLAG", protocol::MI_NULL_FLAG);

    PyModule_AddIntConstant (pModule, "MI_FLAG_CLASS", MI_FLAG_CLASS);
    PyModule_AddIntConstant (pModule, "MI_FLAG_METHOD", MI_FLAG_METHOD);
    PyModule_AddIntConstant (pModule, "MI_FLAG_PROPERTY", MI_FLAG_PROPERTY);
    PyModule_AddIntConstant (pModule, "MI_FLAG_PARAMETER", MI_FLAG_PARAMETER);
    PyModule_AddIntConstant (
        pModule, "MI_FLAG_ASSOCIATION", MI_FLAG_ASSOCIATION);
    PyModule_AddIntConstant (pModule, "MI_FLAG_INDICATION", MI_FLAG_INDICATION);
    PyModule_AddIntConstant (pModule, "MI_FLAG_REFERENCE", MI_FLAG_REFERENCE);
    PyModule_AddIntConstant (pModule, "MI_FLAG_ANY", MI_FLAG_ANY);

    PyModule_AddIntConstant (
        pModule, "MI_FLAG_ENABLEOVERRIDE", MI_FLAG_ENABLEOVERRIDE);
    PyModule_AddIntConstant (
        pModule, "MI_FLAG_DISABLEOVERRIDE", MI_FLAG_DISABLEOVERRIDE);
    PyModule_AddIntConstant (pModule, "MI_FLAG_RESTRICTED", MI_FLAG_RESTRICTED);
    PyModule_AddIntConstant (pModule, "MI_FLAG_TOSUBCLASS", MI_FLAG_TOSUBCLASS);
    PyModule_AddIntConstant (
        pModule, "MI_FLAG_TRANSLATABLE", MI_FLAG_TRANSLATABLE);

    PyModule_AddIntConstant (pModule, "MI_FLAG_KEY", MI_FLAG_KEY);
    PyModule_AddIntConstant (pModule, "MI_FLAG_IN", MI_FLAG_IN);
    PyModule_AddIntConstant (pModule, "MI_FLAG_OUT", MI_FLAG_OUT);
    PyModule_AddIntConstant (pModule, "MI_FLAG_REQUIRED", MI_FLAG_REQUIRED);
    PyModule_AddIntConstant (pModule, "MI_FLAG_STATIC", MI_FLAG_STATIC);
    PyModule_AddIntConstant (pModule, "MI_FLAG_ABSTRACT", MI_FLAG_ABSTRACT);
    PyModule_AddIntConstant (pModule, "MI_FLAG_TERMINAL", MI_FLAG_TERMINAL);
    PyModule_AddIntConstant (pModule, "MI_FLAG_EXPENSIVE", MI_FLAG_EXPENSIVE);
    PyModule_AddIntConstant (pModule, "MI_FLAG_STREAM", MI_FLAG_STREAM);
    PyModule_AddIntConstant (pModule, "MI_FLAG_READONLY", MI_FLAG_READONLY);

    PyModule_AddIntConstant (pModule, "MI_RESULT_OK", MI_RESULT_OK);
    PyModule_AddIntConstant (pModule, "MI_RESULT_FAILED", MI_RESULT_FAILED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_ACCESS_DENIED",
                             MI_RESULT_ACCESS_DENIED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_NAMESPACE",
                             MI_RESULT_INVALID_NAMESPACE);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_PARAMETER",
                             MI_RESULT_INVALID_PARAMETER);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_CLASS",
                             MI_RESULT_INVALID_CLASS);
    PyModule_AddIntConstant (pModule, "MI_RESULT_NOT_FOUND",
                             MI_RESULT_NOT_FOUND);
    PyModule_AddIntConstant (pModule, "MI_RESULT_NOT_SUPPORTED",
                             MI_RESULT_NOT_SUPPORTED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_CLASS_HAS_CHILDREN",
                             MI_RESULT_CLASS_HAS_CHILDREN);
    PyModule_AddIntConstant (pModule, "MI_RESULT_CLASS_HAS_INSTANCES",
                             MI_RESULT_CLASS_HAS_INSTANCES);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_SUPERCLASS",
                             MI_RESULT_INVALID_SUPERCLASS);
    PyModule_AddIntConstant (pModule, "MI_RESULT_ALREADY_EXISTS",
                             MI_RESULT_ALREADY_EXISTS);
    PyModule_AddIntConstant (pModule, "MI_RESULT_NO_SUCH_PROPERTY",
                             MI_RESULT_NO_SUCH_PROPERTY);
    PyModule_AddIntConstant (pModule, "MI_RESULT_TYPE_MISMATCH",
                             MI_RESULT_TYPE_MISMATCH);
    PyModule_AddIntConstant (pModule, "MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED",
                             MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_QUERY",
                             MI_RESULT_INVALID_QUERY);
    PyModule_AddIntConstant (pModule, "MI_RESULT_METHOD_NOT_AVAILABLE",
                             MI_RESULT_METHOD_NOT_AVAILABLE);
    PyModule_AddIntConstant (pModule, "MI_RESULT_METHOD_NOT_FOUND",
                             MI_RESULT_METHOD_NOT_FOUND);
    PyModule_AddIntConstant (pModule, "MI_RESULT_NAMESPACE_NOT_EMPTY",
                             MI_RESULT_NAMESPACE_NOT_EMPTY);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_ENUMERATION_CONTEXT",
                             MI_RESULT_INVALID_ENUMERATION_CONTEXT);
    PyModule_AddIntConstant (pModule, "MI_RESULT_INVALID_OPERATION_TIMEOUT",
                             MI_RESULT_INVALID_OPERATION_TIMEOUT);
    PyModule_AddIntConstant (pModule, "MI_RESULT_PULL_HAS_BEEN_ABANDONED",
                             MI_RESULT_PULL_HAS_BEEN_ABANDONED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_PULL_CANNOT_BE_ABANDONED",
                             MI_RESULT_PULL_CANNOT_BE_ABANDONED);
    PyModule_AddIntConstant (pModule,
                             "MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED",
                             MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED);
    PyModule_AddIntConstant (pModule,
                             "MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED",
                             MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_SERVER_LIMITS_EXCEEDED",
                             MI_RESULT_SERVER_LIMITS_EXCEEDED);
    PyModule_AddIntConstant (pModule, "MI_RESULT_SERVER_IS_SHUTTING_DOWN",
                             MI_RESULT_SERVER_IS_SHUTTING_DOWN);
}


namespace scx
{


//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_BOOLEAN>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_UINT8>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_SINT8>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_UINT16>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_SINT16>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_UINT32>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_SINT32>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_UINT64>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_SINT64>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_REAL32>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_REAL64>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_CHAR16>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Wrapper<MI_STRING>::s_PyTypeObject = {};

//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_BOOLEANA>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_BOOLEANA>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT8A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_UINT8A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT8A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_SINT8A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT16A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_UINT16A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT16A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_SINT16A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT32A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_UINT32A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT32A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_SINT32A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT64A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_UINT64A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT64A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_SINT64A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_REAL32A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_REAL32A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_REAL64A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_REAL64A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_CHAR16A>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_CHAR16A>::s_PyTypeObject = {};
//
//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_STRINGA>::s_PyTypeObject = {};
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_STRINGA>::s_PyTypeObject = {};
//
///*static*/ PyTypeObject MI_Array_Wrapper<MI_DATETIMEA>::s_PyTypeObject = {};
///*static*/ PyTypeObject MI_Array_Iterator<MI_DATETIMEA>::s_PyTypeObject = {};


// macro to instantiate the static members for the templates
//------------------------------------------------------------------------------
#define MI_WRAPPER_STATIC_DEFS(_TYPE_,_NAME_) \
template<> char const MI_Wrapper<_TYPE_>::NAME[] = #_NAME_; \
template<> char const MI_Wrapper<_TYPE_>::OMI_NAME[] = "omi." #_NAME_; \
template<> char const MI_Wrapper<_TYPE_>::DOC[] = "omi." #_NAME_ " utility"; \
template<> PyGetSetDef MI_Wrapper<_TYPE_>::s_Mutators[] = { \
   { "value", \
     reinterpret_cast<getter>(_getValue), \
     reinterpret_cast<setter>(_setValue), \
     "value type", \
     NULL }, \
   { NULL }, \
}; \
template<> PyMethodDef MI_Wrapper<_TYPE_>::s_Methods[] = { \
    { "getType", reinterpret_cast<PyCFunction>(MI_Wrapper<_TYPE_>::_getType), \
      METH_NOARGS, "return item type" }, \
    { NULL, NULL, 0, NULL } \
}; \
template<> PyTypeObject MI_Wrapper<_TYPE_>::s_PyTypeObject = {}


// instantiate the static members for the templates
//------------------------------------------------------------------------------
MI_WRAPPER_STATIC_DEFS (MI_BOOLEAN, MI_Boolean);
MI_WRAPPER_STATIC_DEFS (MI_SINT8, MI_Sint8);
MI_WRAPPER_STATIC_DEFS (MI_UINT8, MI_Uint8);
MI_WRAPPER_STATIC_DEFS (MI_SINT16, MI_Sint16);
MI_WRAPPER_STATIC_DEFS (MI_UINT16, MI_Uint16);
MI_WRAPPER_STATIC_DEFS (MI_SINT32, MI_Sint32);
MI_WRAPPER_STATIC_DEFS (MI_UINT32, MI_Uint32);
MI_WRAPPER_STATIC_DEFS (MI_SINT64, MI_Sint64);
MI_WRAPPER_STATIC_DEFS (MI_UINT64, MI_Uint64);
MI_WRAPPER_STATIC_DEFS (MI_REAL32, MI_Real32);
MI_WRAPPER_STATIC_DEFS (MI_REAL64, MI_Real64);
MI_WRAPPER_STATIC_DEFS (MI_CHAR16, MI_Char16);
MI_WRAPPER_STATIC_DEFS (MI_STRING, MI_String);


// macro to instantiate the static members for the templates
//------------------------------------------------------------------------------
#define MI_ARRAY_WRAPPER_STATIC_DEFS(_TYPE_,_NAME_) \
template<> char const MI_Array_Wrapper<_TYPE_>::NAME[] = #_NAME_; \
template<> char const MI_Array_Wrapper<_TYPE_>::OMI_NAME[] = "omi." #_NAME_; \
template<> char const MI_Array_Wrapper<_TYPE_>::DOC[] = \
    "omi." #_NAME_ " utility"; \
template<> PyMethodDef MI_Array_Wrapper<_TYPE_>::METHODS[] = { \
    { "getType", \
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_getType), \
      METH_NOARGS, "return item type" }, \
    { "count", reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_count), \
      METH_NOARGS, "return item count" }, \
    { "getValueAt", \
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_getValueAt), \
      METH_KEYWORDS, "return value at index" }, \
    { "setValueAt", \
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_setValueAt), \
      METH_KEYWORDS, "set value at index" }, \
    { "append", \
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_append), \
      METH_KEYWORDS, "append value" }, \
    { "insert", \
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_insert), \
      METH_KEYWORDS, "insert value at index" }, \
    { "pop", reinterpret_cast<PyCFunction>(MI_Array_Wrapper<_TYPE_>::_pop), \
      METH_KEYWORDS, "remove value at index and return it" }, \
    { NULL, NULL, 0, NULL } \
}; \
template<> char const MI_Array_Iterator<_TYPE_>::NAME[] = #_NAME_ "_iterator"; \
template<> char const MI_Array_Iterator<_TYPE_>::OMI_NAME[] = \
    "omi." #_NAME_ "_iterator"; \
template<> char const MI_Array_Iterator<_TYPE_>::DOC[] = \
    "iterator for omi." #_NAME_; \
template<> PyGetSetDef MI_Array_Iterator<_TYPE_>::s_Mutators[] = { \
   { "value", \
     reinterpret_cast<getter>(_getValue), \
     reinterpret_cast<setter>(_setValue), \
     "value type", \
     NULL }, \
   { NULL }, \
}; \
template<> PyTypeObject MI_Array_Wrapper<_TYPE_>::s_PyTypeObject = {}; \
template<> PyTypeObject MI_Array_Iterator<_TYPE_>::s_PyTypeObject = {}


// instantiate the static members for the templates
//------------------------------------------------------------------------------
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_BOOLEANA, MI_BooleanA);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_UINT8A, MI_Uint8A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_SINT8A, MI_Sint8A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_SINT16A, MI_Sint16A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_UINT16A, MI_Uint16A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_SINT32A, MI_Sint32A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_UINT32A, MI_Uint32A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_SINT64A, MI_Sint64A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_UINT64A, MI_Uint64A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_REAL32A, MI_Real32A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_REAL64A, MI_Real64A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_CHAR16A, MI_Char16A);
MI_ARRAY_WRAPPER_STATIC_DEFS (MI_STRINGA, MI_StringA);


// MI_Array_Wrapper<MI_DATETIMEA> specialization static member definitions
//------------------------------------------------------------------------------
char const MI_Array_Wrapper<MI_DATETIMEA>::NAME[] = "MI_DatetimeA";
char const MI_Array_Wrapper<MI_DATETIMEA>::OMI_NAME[] = "omi.MI_DatetimeA";
char const MI_Array_Wrapper<MI_DATETIMEA>::DOC[] = "omi.MI_DatetimeA utility";
PyMethodDef MI_Array_Wrapper<MI_DATETIMEA>::METHODS[] = {
    { "getType",
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<MI_DATETIMEA>::_getType),
      METH_NOARGS, "return item type" },
    { "count",
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<MI_DATETIMEA>::_count),
      METH_NOARGS, "return item count" },
    { "getValueAt",
      reinterpret_cast<PyCFunction>(
          MI_Array_Wrapper<MI_DATETIMEA>::_getValueAt),
      METH_KEYWORDS, "return value at index" },
    { "setValueAt",
      reinterpret_cast<PyCFunction>(
          MI_Array_Wrapper<MI_DATETIMEA>::_setValueAt),
      METH_KEYWORDS, "set value at index" },
    { "append",
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<MI_DATETIMEA>::_append),
      METH_KEYWORDS, "append value" },
    { "insert",
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<MI_DATETIMEA>::_insert),
      METH_KEYWORDS, "insert value at index" },
    { "pop",
      reinterpret_cast<PyCFunction>(MI_Array_Wrapper<MI_DATETIMEA>::_pop),
      METH_KEYWORDS, "remove value at index and return it" },
    { NULL, NULL, 0, NULL }
};
char const MI_Array_Iterator<MI_DATETIMEA>::NAME[] = "MI_DatetimeA_iterator";
char const MI_Array_Iterator<MI_DATETIMEA>::OMI_NAME[] =
    "omi.MI_DatetimeA_iterator";
char const MI_Array_Iterator<MI_DATETIMEA>::DOC[] =
    "iterator for omi.MI_DatetimeA";
PyGetSetDef MI_Array_Iterator<MI_DATETIMEA>::s_Mutators[] = {
   { "value",
     reinterpret_cast<getter>(_getValue),
     reinterpret_cast<setter>(_setValue),
     "value type",
     NULL },
   { NULL },
};
PyTypeObject MI_Array_Wrapper<MI_DATETIMEA>::s_PyTypeObject = {};
PyTypeObject MI_Array_Iterator<MI_DATETIMEA>::s_PyTypeObject = {};


template<>
/*static*/ int
MI_Wrapper<MI_BOOLEAN>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_BOOLEAN>::init");
    int rval = PY_FAILURE;
    MI_Wrapper<MI_BOOLEAN>* pWrapper =
        reinterpret_cast<MI_Wrapper<MI_BOOLEAN>*>(pSelf);
    pWrapper->ctor (MI_Value<MI_BOOLEAN>::Ptr ());
    PyObject* pValue = NULL;
    char* KEYWORDS[] = {
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|O", KEYWORDS, &pValue))
    {
        if (NULL == pValue ||
            Py_None == pValue)
        {
            //SCX_BOOKEND_PRINT ("NULL or PyNone");
            rval = PY_SUCCESS;
        }
#if (__MI_WRAPPER_COPY_CTOR__)
        else if (PyObject_TypeCheck (pValue, &s_PyTypeObject))
        {
            //SCX_BOOKEND_PRINT ("MI_Wrapper<MI_BOOLEAN>");
            MI_Wrapper<MI_BOOLEAN>* pOtherWrapper =
                reinterpret_cast<MI_Wrapper<MI_BOOLEAN>*>(pValue);
            pWrapper->m_pValue = pOtherWrapper->m_pValue;
            rval = PY_SUCCESS;
        }
#endif // __MI_WRAPPER_COPY_CTOR__
        else if (Py_False == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** Py_False");
            pWrapper->m_pValue.reset (new MI_Value<MI_BOOLEAN> (MI_FALSE));
            rval = PY_SUCCESS;
        }
        else if (Py_True == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** Py_True");
            pWrapper->m_pValue.reset (new MI_Value<MI_BOOLEAN> (MI_TRUE));
            rval = PY_SUCCESS;
        }
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "MI_Wrapper invalid arguments.");
    }
    return rval;
}


template<>
/*static*/ MI_Wrapper<MI_BOOLEAN>::PyPtr
MI_Wrapper<MI_BOOLEAN>::createPyPtr (
    MI_Value<MI_BOOLEAN>::Ptr const& pValue)
{
    SCX_BOOKEND ("MI_Wrapper<MI_BOOLEAN>::createPyPtr");
    if (s_PyTypeObject.tp_alloc)
    {
        SCX_BOOKEND_PRINT ("tp_alloc is not NULL");
    }
    else
    {
        SCX_BOOKEND_PRINT ("tp_alloc is NULL");
    }
    PyObjPtr pPyWrapper (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    //SCX_BOOKEND_PRINT ("mark 2");
    if (pPyWrapper)
    {
        //SCX_BOOKEND_PRINT ("mark 4");
        MI_Wrapper<MI_BOOLEAN>* pWrapper =
            reinterpret_cast<MI_Wrapper<MI_BOOLEAN>*>(pPyWrapper.get ());
        //SCX_BOOKEND_PRINT ("mark 6");
        pWrapper->ctor (pValue);
        //SCX_BOOKEND_PRINT ("mark 8");
        return PyPtr (
            reinterpret_cast<MI_Wrapper<MI_BOOLEAN>*>(pPyWrapper.release ()),
            DO_NOT_INC_REF);
    }
    //SCX_BOOKEND_PRINT ("mark 10");
    return PyPtr ();
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_BOOLEAN>::_getValue (
    MI_Wrapper<MI_BOOLEAN>* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_BOOLEAN>::_getValue");
    MI_Value<MI_BOOLEAN> const* pValue = pSelf->getValue ();
    if (NULL != pValue)
    {
        PyObject* rval = pValue->getValue () == MI_FALSE ? Py_False : Py_True;
        Py_INCREF (rval);
        return rval;
    }
    Py_RETURN_NONE;
}


template<>
/*static*/ int
MI_Wrapper<MI_BOOLEAN>::_setValue (
    MI_Wrapper<MI_BOOLEAN>* pSelf,
    PyObject* pValue,
    void*)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_BOOLEAN>::_setValue");
    int rval = PY_FAILURE;
    if (NULL == pValue ||
        Py_None == pValue)
    {
        //SCX_BOOKEND_PRINT ("***** NULL or PyNone");
        pSelf->m_pValue.reset ();
        rval = PY_SUCCESS;
    }
#if (__MI_WRAPPER_ASSIGN_OP__)
    else if (PyObject_TypeCheck (pValue, getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("***** MI_Wrapper<MI_BOOLEAN>");
        MI_Wrapper<MI_BOOLEAN>* pWrapper =
            reinterpret_cast<MI_Wrapper<MI_BOOLEAN>*>(pValue);
        pSelf->m_pValue = pWrapper->m_pValue;
        rval = PY_SUCCESS;
    }
#endif // __MI_WRAPPER_ASSIGN_OP__
    else if (Py_False == pValue)
    {
        //SCX_BOOKEND_PRINT ("***** Py_False");
        pSelf->m_pValue.reset (new MI_Value<MI_BOOLEAN> (MI_FALSE));
        rval = PY_SUCCESS;
    }
    else if (Py_True == pValue)
    {
        //SCX_BOOKEND_PRINT ("***** Py_True");
        pSelf->m_pValue.reset (new MI_Value<MI_BOOLEAN> (MI_TRUE));
        rval = PY_SUCCESS;
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "MI_Wrapper invalid arguments.");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_BOOLEAN>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_BOOLEAN>::to_str");
    MI_Wrapper<MI_BOOLEAN> const* pWrapper =
        reinterpret_cast<MI_Wrapper<MI_BOOLEAN> const*>(pSelf);
    std::ostringstream strm;
    strm << NAME << '(';
    if (pWrapper->m_pValue)
    {
        strm << (pWrapper->m_pValue->getValue () ? "True" : "False");
    }
    else
    {
        strm << "None";
    }
    strm << ')';
    return PyString_FromString (strm.str ().c_str ());
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_SINT8>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_SINT8>::to_str");
    MI_Wrapper<MI_SINT8> const* pWrapper =
        reinterpret_cast<MI_Wrapper<MI_SINT8> const*>(pSelf);
    std::ostringstream strm;
    strm << NAME << '(';
    if (pWrapper->m_pValue)
    {
        strm << static_cast<int>(pWrapper->m_pValue->getValue ());
    }
    else
    {
        strm << "None";
    }
    strm << ')';
    return PyString_FromString (strm.str ().c_str ());
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_UINT8>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper<MI_UINT8>::to_str");
    MI_Wrapper<MI_UINT8> const* pWrapper =
        reinterpret_cast<MI_Wrapper<MI_UINT8> const*>(pSelf);
    std::ostringstream strm;
    strm << NAME << '(';
    if (pWrapper->m_pValue)
    {
        strm << static_cast<unsigned>(pWrapper->m_pValue->getValue ());
    }
    else
    {
        strm << "None";
    }
    strm << ')';
    return PyString_FromString (strm.str ().c_str ());
}


// MI_Timestamp_Wrapper definitions
//------------------------------------------------------------------------------
/*static*/ PyTypeObject MI_Timestamp_Wrapper::s_PyTypeObject;
/*static*/ char const MI_Timestamp_Wrapper::NAME[] = "MI_Timestamp";
/*static*/ char const MI_Timestamp_Wrapper::OMI_NAME[] = "omi.MI_Timestamp";
/*static*/ char const MI_Timestamp_Wrapper::DOC[] = "omi.MI_Timestamp utility";


/*static*/ PyGetSetDef MI_Timestamp_Wrapper::MUTATORS[] = {
    { "year",
      reinterpret_cast<getter>(_getYear),
      reinterpret_cast<setter>(_setYear),
      "year value",
      NULL },
    { "month",
      reinterpret_cast<getter>(_getMonth),
      reinterpret_cast<setter>(_setMonth),
      "month value",
      NULL },
    { "day",
      reinterpret_cast<getter>(_getDay),
      reinterpret_cast<setter>(_setDay),
      "day value",
      NULL },
    { "hour",
      reinterpret_cast<getter>(_getHour),
      reinterpret_cast<setter>(_setHour),
      "hour value",
      NULL },
    { "minute",
      reinterpret_cast<getter>(_getMinute),
      reinterpret_cast<setter>(_setMinute),
      "minute value",
      NULL },
    { "second",
      reinterpret_cast<getter>(_getSecond),
      reinterpret_cast<setter>(_setSecond),
      "second value",
      NULL },
    { "microseconds",
      reinterpret_cast<getter>(_getMicroseconds),
      reinterpret_cast<setter>(_setMicroseconds),
      "microseconds value",
      NULL },
    { "utc",
      reinterpret_cast<getter>(_getUTC),
      reinterpret_cast<setter>(_setUTC),
      "utc value",
      NULL },
    { NULL },
};


/*static*/ PyMethodDef MI_Timestamp_Wrapper::METHODS[] = {
    { "getType", reinterpret_cast<PyCFunction>(MI_Timestamp_Wrapper::_getType),
      METH_NOARGS, "return item type" },
    { "isTimestamp",
      reinterpret_cast<PyCFunction>(MI_Timestamp_Wrapper::_isTimestamp),
      METH_NOARGS, "return true if subclass is MI_Timestamp" },
    { NULL, NULL, 0, NULL }
};


/*static*/ void
MI_Timestamp_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Timestamp_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Timestamp_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
//    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_methods = METHODS;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_getset = MUTATORS;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ PyTypeObject*
MI_Timestamp_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


/*static*/ void
MI_Timestamp_Wrapper::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::dealloc");
    MI_Timestamp_Wrapper* pTimestamp =
        reinterpret_cast<MI_Timestamp_Wrapper*>(pSelf);
    pTimestamp->dtor ();
    pTimestamp->ob_type->tp_free (pSelf);
}


///*static*/ PyObject*
//MI_Timestamp_Wrapper::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    //SCX_BOOKEND ("MI_Timestamp_Wrapper::newObj");
//    return pType->tp_alloc (pType, 0);
//}


/*static*/ int
MI_Timestamp_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::init");
    int rval = PY_FAILURE;
    MI_Timestamp::Ptr pT (new MI_Timestamp);
    PyObject* pYearObj = NULL;
    PyObject* pMonthObj = NULL;
    PyObject* pDayObj = NULL;
    PyObject* pHourObj = NULL;
    PyObject* pMinuteObj = NULL;
    PyObject* pSecondObj = NULL;
    PyObject* pMicrosecondsObj = NULL;
    PyObject* pUtcObj = NULL;
    char* KEYWORDS[] = {
        "year",
        "month",
        "day",
        "hour",
        "minute",
        "second",
        "microseconds",
        "utc",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|OOOOOOOO", KEYWORDS, &pYearObj, &pMonthObj,
            &pDayObj, &pHourObj, &pMinuteObj, &pSecondObj, &pMicrosecondsObj,
            &pUtcObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        rval = PY_SUCCESS;
        MI_Uint32 year = 0;
        if (NULL != pYearObj)
        {
            //SCX_BOOKEND_PRINT ("pYearObj is not NULL");
            rval = fromPyObject (pYearObj, &year);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("pYearObj is NULL");
        }
        MI_Uint32 month = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pMonthObj)
            {
                //SCX_BOOKEND_PRINT ("pMonthObj is not NULL");
                rval = fromPyObject (pMonthObj, &month);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pMonthObj is NULL");
            }
        }
        MI_Uint32 day = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pDayObj)
            {
                //SCX_BOOKEND_PRINT ("pDayObj is not NULL");
                rval = fromPyObject (pDayObj, &day);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pDayObj is NULL");
            }
        }
        MI_Uint32 hour = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pHourObj)
            {
                //SCX_BOOKEND_PRINT ("pHourObj is not NULL");
                rval = fromPyObject (pHourObj, &hour);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pHourObj is NULL");
            }
        }
        MI_Uint32 minute = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pMinuteObj)
            {
                //SCX_BOOKEND_PRINT ("pMinuteObj is not NULL");
                rval = fromPyObject (pMinuteObj, &minute);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pMinuteObj is NULL");
            }
        }
        MI_Uint32 second = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pSecondObj)
            {
                //SCX_BOOKEND_PRINT ("pSecondObj is not NULL");
                rval = fromPyObject (pSecondObj, &second);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pSecondObj is NULL");
            }
        }
        MI_Uint32 microseconds = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pMicrosecondsObj)
            {
                //SCX_BOOKEND_PRINT ("pMicroSecondsObj is not NULL");
                rval = fromPyObject (pMicrosecondsObj, &microseconds);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pMicrosecondsObj is NULL");
            }
        }
        MI_Sint32 utc = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pUtcObj)
            {
                //SCX_BOOKEND_PRINT ("pUtcObj is not NULL");
                rval = fromPyObject (pUtcObj, &utc);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pUtcObj is NULL");
            }
        }
        if (PY_SUCCESS == rval)
        {
            //SCX_BOOKEND_PRINT ("success");
            pT = new MI_Timestamp (year, month, day, hour, minute, second,
                                   microseconds, utc);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("failure");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    MI_Timestamp_Wrapper* pTimestamp =
        reinterpret_cast<MI_Timestamp_Wrapper*>(pSelf);
    pTimestamp->ctor (pT);
    return rval;
}


/*static*/ MI_Timestamp_Wrapper::PyPtr
MI_Timestamp_Wrapper::createPyPtr (
    MI_Timestamp::Ptr const& pValue)
{
    //SCX_BOOKEND ("MI_Timestamp::createPyPtr");
    PyObjPtr pPyWrapper (s_PyTypeObject.tp_base->tp_alloc (&s_PyTypeObject, 0));
    if (pPyWrapper)
    {
        MI_Timestamp_Wrapper* pWrapper =
            reinterpret_cast<MI_Timestamp_Wrapper*>(pPyWrapper.get ());
        pWrapper->ctor (pValue);
        return PyPtr (
            reinterpret_cast<MI_Timestamp_Wrapper*>(pPyWrapper.release ()),
            DO_NOT_INC_REF);
    }
    return PyPtr ();
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getType (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::_getType");
    return PyInt_FromSize_t (MI_DATETIME);
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_isTimestamp (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::_isTimestamp");
    Py_INCREF (Py_True);
    return Py_True;
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getYear (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getYear ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getMonth (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getMonth ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getDay (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getDay ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getHour (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getHour ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getMinute (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getMinute ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getSecond (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getSecond ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getMicroseconds (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getMicroseconds ());
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::_getUTC (
    MI_Timestamp_Wrapper* pSelf,
    void*)
{
    return toPyObject (pSelf->m_pTimestamp->getUTC ());
}


/*static*/ int
MI_Timestamp_Wrapper::_setYear (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setYear (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setMonth (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setMonth (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setDay (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setDay (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setHour (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setHour (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setMinute (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setMinute (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setSecond (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setSecond (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setMicroseconds (
     MI_Timestamp_Wrapper* pSelf,
     PyObject* pValue,
     void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setMicroseconds (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Timestamp_Wrapper::_setUTC (
    MI_Timestamp_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Sint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pTimestamp->setUTC (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ PyObject*
MI_Timestamp_Wrapper::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::to_str");
    MI_Timestamp_Wrapper const* pWrapper =
        reinterpret_cast<MI_Timestamp_Wrapper const*>(pSelf);
    std::ostringstream strm;
    strm << *pWrapper;
    return PyString_FromString (strm.str ().c_str ());
}


void
MI_Timestamp_Wrapper::ctor (
    MI_Timestamp::Ptr const& pTimestamp)
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::ctor");
    new (&m_pTimestamp) MI_Timestamp::Ptr (pTimestamp);
}


void
MI_Timestamp_Wrapper::dtor ()
{
    //SCX_BOOKEND ("MI_Timestamp_Wrapper::dtor");
    m_pTimestamp.~internal_counted_ptr ();
}


MI_Timestamp::Ptr const&
MI_Timestamp_Wrapper::getValue ()
{
    return m_pTimestamp;
}


// MI_Interval_Wrapper definitions
//------------------------------------------------------------------------------
/*static*/ PyTypeObject MI_Interval_Wrapper::s_PyTypeObject;
/*static*/ char const MI_Interval_Wrapper::NAME[] = "MI_Interval";
/*static*/ char const MI_Interval_Wrapper::OMI_NAME[] = "omi.MI_Interval";
/*static*/ char const MI_Interval_Wrapper::DOC[] = "omi.MI_Interval utility";


/*static*/ PyGetSetDef MI_Interval_Wrapper::MUTATORS[] = {
    { "days",
      reinterpret_cast<getter>(_getDays),
      reinterpret_cast<setter>(_setDays),
      "days value",
      NULL },
    { "hours",
      reinterpret_cast<getter>(_getHours),
      reinterpret_cast<setter>(_setHours),
      "hours value",
      NULL },
    { "minutes",
      reinterpret_cast<getter>(_getMinutes),
      reinterpret_cast<setter>(_setMinutes),
      "minutes value",
      NULL },
    { "seconds",
      reinterpret_cast<getter>(_getSeconds),
      reinterpret_cast<setter>(_setSeconds),
      "seconds value",
      NULL },
    { "microseconds",
      reinterpret_cast<getter>(_getMicroseconds),
      reinterpret_cast<setter>(_setMicroseconds),
      "microseconds value",
      NULL },
    { NULL },
};


/*static*/ PyMethodDef MI_Interval_Wrapper::METHODS[] = {
    { "getType", reinterpret_cast<PyCFunction>(MI_Interval_Wrapper::_getType),
      METH_NOARGS, "return item type" },
    { "isTimestamp",
      reinterpret_cast<PyCFunction>(MI_Interval_Wrapper::_isTimestamp),
      METH_NOARGS, "return true if subclass is MI_Timestamp" },
    { NULL, NULL, 0, NULL }
};


/*static*/ void
MI_Interval_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Interval_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Interval_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
//    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_methods = METHODS;
    s_PyTypeObject.tp_getset = MUTATORS;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ PyObject*
MI_Interval_Wrapper::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::to_str");
    MI_Interval_Wrapper const* pWrapper =
        reinterpret_cast<MI_Interval_Wrapper const*>(pSelf);
    std::ostringstream strm;
    strm << *pWrapper;
    return PyString_FromString (strm.str ().c_str ());
}


/*static*/ MI_Interval_Wrapper::PyPtr
MI_Interval_Wrapper::createPyPtr (
    MI_Interval::Ptr const& pValue)
{
    //SCX_BOOKEND ("MI_Interval::createPyPtr");
    PyObjPtr pPyWrapper (s_PyTypeObject.tp_base->tp_alloc (&s_PyTypeObject, 0));
    if (pPyWrapper)
    {
        MI_Interval_Wrapper* pWrapper =
            reinterpret_cast<MI_Interval_Wrapper*>(pPyWrapper.get ());
        pWrapper->ctor (pValue);
        return PyPtr (
            reinterpret_cast<MI_Interval_Wrapper*>(pPyWrapper.release ()),
            DO_NOT_INC_REF);
    }
    return PyPtr ();
}


/*static*/ PyTypeObject*
MI_Interval_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


/*static*/ void
MI_Interval_Wrapper::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::dealloc");
    MI_Interval_Wrapper* pInterval =
        reinterpret_cast<MI_Interval_Wrapper*>(pSelf);
    pInterval->dtor ();
    pInterval->ob_type->tp_free (pSelf);
}


///*static*/ PyObject*
//MI_Interval_Wrapper::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    //SCX_BOOKEND ("MI_Interval_Wrapper::newObj");
//    return pType->tp_alloc (pType, 0);
//}


/*static*/ int
MI_Interval_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::init");
    int rval = PY_FAILURE;
    MI_Interval::Ptr pT (new MI_Interval);
    PyObject* pDaysObj = NULL;
    PyObject* pHoursObj = NULL;
    PyObject* pMinutesObj = NULL;
    PyObject* pSecondsObj = NULL;
    PyObject* pMicrosecondsObj = NULL;
    char* KEYWORDS[] = {
        "days",
        "hours",
        "minutes",
        "seconds",
        "microseconds",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|OOOOO", KEYWORDS, &pDaysObj, &pHoursObj,
            &pMinutesObj, &pSecondsObj, &pMicrosecondsObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        rval = PY_SUCCESS;
        MI_Uint32 days = 0;
        if (NULL != pDaysObj)
        {
            //SCX_BOOKEND_PRINT ("pDaysObj is not NULL");
            rval = fromPyObject (pDaysObj, &days);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("pDaysObj is NULL");
        }
        MI_Uint32 hours = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pHoursObj)
            {
                //SCX_BOOKEND_PRINT ("pHoursObj is not NULL");
                rval = fromPyObject (pHoursObj, &hours);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pHoursObj is NULL");
            }
        }
        MI_Uint32 minutes = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pMinutesObj)
            {
                //SCX_BOOKEND_PRINT ("pMinutesObj is not NULL");
                rval = fromPyObject (pMinutesObj, &minutes);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pMinutesObj is NULL");
            }
        }
        MI_Uint32 seconds = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pSecondsObj)
            {
                //SCX_BOOKEND_PRINT ("pSecondsObj is not NULL");
                rval = fromPyObject (pSecondsObj, &seconds);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pSecondsObj is NULL");
            }
        }
        MI_Uint32 microseconds = 0;
        if (PY_SUCCESS == rval)
        {
            if (NULL != pMicrosecondsObj)
            {
                //SCX_BOOKEND_PRINT ("pMicrosecondsObj is not NULL");
                rval = fromPyObject (pMicrosecondsObj, &microseconds);
            }
            else
            {
                //SCX_BOOKEND_PRINT ("pMicrosecondsObj is NULL");
            }
        }
        if (PY_SUCCESS == rval)
        {
            //SCX_BOOKEND_PRINT ("success");
            pT = new MI_Interval (days, hours, minutes, seconds, microseconds);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("failure");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    MI_Interval_Wrapper* pInterval =
        reinterpret_cast<MI_Interval_Wrapper*>(pSelf);
    pInterval->ctor (pT);
    return rval;
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getType (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::_getType");
    return PyInt_FromSize_t (MI_DATETIME);
}


/*static*/ PyObject*
MI_Interval_Wrapper::_isTimestamp (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::_isTimestamp");
    Py_INCREF (Py_False);
    return Py_False;
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getDays (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    return PyInt_FromSsize_t (pSelf->m_pInterval->getDays ());
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getHours (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    return PyInt_FromSsize_t (pSelf->m_pInterval->getHours ());
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getMinutes (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    return PyInt_FromSsize_t (pSelf->m_pInterval->getMinutes ());
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getSeconds (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    return PyInt_FromSsize_t (pSelf->m_pInterval->getSeconds ());
}


/*static*/ PyObject*
MI_Interval_Wrapper::_getMicroseconds (
    MI_Interval_Wrapper* pSelf,
    void*)
{
    return PyInt_FromSsize_t (pSelf->m_pInterval->getMicroseconds ());
}


/*static*/ int
MI_Interval_Wrapper::_setDays (
    MI_Interval_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pInterval->setDays (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Interval_Wrapper::_setHours (
    MI_Interval_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pInterval->setHours (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Interval_Wrapper::_setMinutes (
    MI_Interval_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pInterval->setMinutes (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Interval_Wrapper::_setSeconds (
    MI_Interval_Wrapper* pSelf,
    PyObject* pValue,
    void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pInterval->setSeconds (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


/*static*/ int
MI_Interval_Wrapper::_setMicroseconds (
     MI_Interval_Wrapper* pSelf,
     PyObject* pValue,
     void*)
{
    MI_Uint32 value;
    int rval = fromPyObject (pValue, &value);
    if (PY_SUCCESS == rval)
    {
        pSelf->m_pInterval->setMicroseconds (value);
    }
    else
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments,");
    }
    return rval;
}


void
MI_Interval_Wrapper::ctor (
    MI_Interval::Ptr const& pInterval)
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::ctor");
    new (&m_pInterval) MI_Interval::Ptr (pInterval);
}


void
MI_Interval_Wrapper::dtor ()
{
    //SCX_BOOKEND ("MI_Interval_Wrapper::dtor");
    m_pInterval.~internal_counted_ptr ();
}


MI_Interval::Ptr const&
MI_Interval_Wrapper::getValue ()
{
    return m_pInterval;
}


// class MI_Array_Iterator<MI_DATETIMEA> specialization definitions
//------------------------------------------------------------------------------
/*static*/ void
MI_Array_Iterator<MI_DATETIMEA>::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Array_Iterator<MI_DATETIMEA>);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_getset = s_Mutators;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_iternext = iterNext;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_Array_Iterator<MI_DATETIMEA>::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::dealloc");
    MI_Array_Iterator<MI_DATETIMEA>* pArray =
        reinterpret_cast<MI_Array_Iterator<MI_DATETIMEA>*>(pObj);
    pArray->dtor ();
    pArray->ob_type->tp_free (pObj);
}


/*static*/ MI_Array_Iterator<MI_DATETIMEA>::PyPtr
MI_Array_Iterator<MI_DATETIMEA>::createPyPtr (
    MI_Array<MI_DATETIMEA>::Ptr const& pArray,
    size_t index)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::createPyPtr");
    PyObjPtr pPyIterator (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyIterator)
    {
        MI_Array_Iterator<MI_DATETIMEA>* pIterator =
            reinterpret_cast<MI_Array_Iterator<MI_DATETIMEA>*>(
                pPyIterator.get ());
        pIterator->ctor (pArray, index);
        return PyPtr (
            reinterpret_cast<MI_Array_Iterator<MI_DATETIMEA>*>(
                pPyIterator.release ()),
            DO_NOT_INC_REF);
    }
    return PyPtr ();
}


/*static*/ PyObject*
MI_Array_Iterator<MI_DATETIMEA>::_getValue (
    MI_Array_Iterator<MI_DATETIMEA>* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::_getValue");
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        MI_Datetime::Ptr pDatetime =
            pSelf->m_pArray->getValueAt (pSelf->m_Index);
        if (pDatetime->isTimestamp ())
        {
            MI_Timestamp::Ptr pTimestamp (
                static_cast<MI_Timestamp*>(pDatetime.get ()));
            MI_Timestamp_Wrapper::PyPtr pyTimestamp (
                MI_Timestamp_Wrapper::createPyPtr (pTimestamp));
            return reinterpret_cast<PyObject*>(pyTimestamp.release ());
        }
        else
        {
            MI_Interval::Ptr pInterval (
                static_cast<MI_Interval*>(pDatetime.get ()));
            MI_Interval_Wrapper::PyPtr pyInterval (
                MI_Interval_Wrapper::createPyPtr (pInterval));
            return reinterpret_cast<PyObject*>(pyInterval.release ());
        }
    }
    PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    return NULL;
}


/*static*/ int
MI_Array_Iterator<MI_DATETIMEA>::_setValue (
    MI_Array_Iterator<MI_DATETIMEA>* pSelf,
    PyObject* pValue,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::_setValue");
    int rval = PY_FAILURE;
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        if (PyObject_TypeCheck (
                pValue, MI_Timestamp_Wrapper::getPyTypeObject ()))
        {
            //SCX_BOOKEND_PRINT ("MI_Timestamp");
            pSelf->m_pArray->setValueAt (
                pSelf->m_Index,
                reinterpret_cast<MI_Timestamp_Wrapper*>(pValue)->getValue ());
            rval = PY_SUCCESS;
        }
        else if (PyObject_TypeCheck (
                     pValue, MI_Interval_Wrapper::getPyTypeObject ()))
        {
            //SCX_BOOKEND_PRINT ("MI_Interval");
            pSelf->m_pArray->setValueAt (
                pSelf->m_Index,
                reinterpret_cast<MI_Interval_Wrapper*>(pValue)->getValue ());
            rval = PY_SUCCESS;
        }
        else
        {
            //SCX_BOOKEND_PRINT ("unhandled type");
            PyErr_SetString (PyExc_ValueError, "incompatible value type.");
        }
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


/*static*/ PyObject*
MI_Array_Iterator<MI_DATETIMEA>::iterNext (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::iterNext");
    PyObject* rval = NULL;
    MI_Array_Iterator<MI_DATETIMEA>* pIterator =
        reinterpret_cast<MI_Array_Iterator<MI_DATETIMEA>*>(pObj);
    if (pIterator->m_pArray->size () > (1 + pIterator->m_Index))
    {
        ++(pIterator->m_Index);
        Py_INCREF (pObj);
        rval = pObj;
    }
    return rval;
}


/*static*/ PyObject*
MI_Array_Iterator<MI_DATETIMEA>::to_str (
    PyObject* pSelf)
{
    PyObject* rval = NULL;
    MI_Array_Iterator<MI_DATETIMEA>* pIterator =
        reinterpret_cast<MI_Array_Iterator<MI_DATETIMEA>*>(pSelf);
    if (pIterator->m_pArray->size () > pIterator->m_Index)
    {
        std::ostringstream strm;
        MI_Datetime::Ptr pDatetime (
            pIterator->m_pArray->getValueAt (pIterator->m_Index));
        if (pDatetime->isTimestamp ())
        {
            strm << *static_cast<MI_Timestamp const*>(pDatetime.get ()) << ')';
        }
        else
        {
            strm << *static_cast<MI_Interval const*>(pDatetime.get ()) << ')';
        }
        rval = PyString_FromString (strm.str ().c_str ());
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


void
MI_Array_Iterator<MI_DATETIMEA>::ctor (
    MI_Array<MI_DATETIMEA>::Ptr const& pArray,
    size_t index)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::ctor");
    new (&m_pArray) MI_Array<MI_DATETIMEA>::Ptr (pArray);
    m_Index = index;
}


void
MI_Array_Iterator<MI_DATETIMEA>::dtor ()
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_DATETIMEA>::dtor");
    typedef util::internal_counted_ptr<MI_Array<MI_DATETIMEA> > ptr;
    m_pArray.~ptr ();
}


// class MI_Array_Iterator specialization definitions
//------------------------------------------------------------------------------
template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_BOOLEANA>::_getValue (
    MI_Array_Iterator<MI_BOOLEANA>* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_BOOLEANA>::_getValue");
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        PyObject* rval = (*(pSelf->m_pArray))[pSelf->m_Index] == MI_FALSE
            ? Py_False : Py_True;
        Py_INCREF (rval);
        return rval;
    }
    PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    return NULL;
}


template<>
/*static*/ int
MI_Array_Iterator<MI_BOOLEANA>::_setValue (
    MI_Array_Iterator<MI_BOOLEANA>* pSelf,
    PyObject* pValueObj,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator<MI_BOOLEANA>::_setValue");
    int rval = PY_FAILURE;
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        if (Py_True == pValueObj)
        {
            (*(pSelf->m_pArray))[pSelf->m_Index] = MI_TRUE;
            rval = PY_SUCCESS;
        }
        else if (Py_False == pValueObj)
        {
            (*(pSelf->m_pArray))[pSelf->m_Index] = MI_FALSE;
            rval = PY_SUCCESS;
        }
        else
        {
            PyErr_SetString (PyExc_ValueError, "invalid argument");
        }
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_BOOLEANA>::to_str (
    PyObject* pSelf)
{
    PyObject* rval = NULL;
    MI_Array_Iterator<MI_BOOLEANA>* pIterator =
        reinterpret_cast<MI_Array_Iterator<MI_BOOLEANA>*>(pSelf);
    if (pIterator->m_pArray->size () > pIterator->m_Index)
    {
        std::ostringstream strm;
        strm << NAME
             << ((*(pIterator->m_pArray))[pIterator->m_Index] == MI_FALSE
                 ? "(False)" : "(True)");
        rval = PyString_FromString (strm.str ().c_str ());
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_UINT8A>::to_str (
    PyObject* pSelf)
{
    PyObject* rval = NULL;
    MI_Array_Iterator<MI_UINT8A>* pIterator =
        reinterpret_cast<MI_Array_Iterator<MI_UINT8A>*>(pSelf);
    if (pIterator->m_pArray->size () > pIterator->m_Index)
    {
        std::ostringstream strm;
        strm << NAME << '('
             << static_cast<unsigned>(
                 (*(pIterator->m_pArray))[pIterator->m_Index])
             << ')';
        rval = PyString_FromString (strm.str ().c_str ());
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_SINT8A>::to_str (
    PyObject* pSelf)
{
    PyObject* rval = NULL;
    MI_Array_Iterator<MI_SINT8A>* pIterator =
        reinterpret_cast<MI_Array_Iterator<MI_SINT8A>*>(pSelf);
    if (pIterator->m_pArray->size () > pIterator->m_Index)
    {
        std::ostringstream strm;
        strm << NAME << '('
             << static_cast<int>((*(pIterator->m_pArray))[pIterator->m_Index])
             << ')';
        rval = PyString_FromString (strm.str ().c_str ());
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


// class MI_Array_Wrapper<MI_DATETIMEA> specialization definitions
//------------------------------------------------------------------------------
/*static*/ void
MI_Array_Wrapper<MI_DATETIMEA>::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Array_Wrapper<MI_DATETIMEA>);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_methods = METHODS;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_iter = getIter;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
        MI_Array_Iterator<MI_DATETIMEA>::moduleInit (pModule);
    }
}


/*static*/ void
MI_Array_Wrapper<MI_DATETIMEA>::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::dealloc");
    MI_Array_Wrapper<MI_DATETIMEA>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
    pArray->dtor ();
    pArray->ob_type->tp_free (pSelf);
}


/*static*/ int
MI_Array_Wrapper<MI_DATETIMEA>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::init");
    int rval = PY_FAILURE;
    MI_Array_Wrapper<MI_DATETIMEA>* pWrapper =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
    pWrapper->ctor ();
    PyObject* pValue = NULL;
    char* KEYWORDS[] = {
        "values",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|O", KEYWORDS, &pValue))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (NULL == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** NULL");
            rval = PY_SUCCESS;
        }
        else if (Py_None == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** Py_None");
            rval = PY_SUCCESS;
        }
        else if (PyList_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyList");
            MI_Array<MI_DATETIMEA>::Ptr pArray (new MI_Array<MI_DATETIMEA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyList_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pItem = PyList_GET_ITEM (pValue, i);
                if (PyObject_TypeCheck (
                        pItem, MI_Timestamp_Wrapper::getPyTypeObject ()))
                {
                    //SCX_BOOKEND_PRINT ("insert new MI_Timestamp");
                    pArray->push_back (
                        reinterpret_cast<MI_Timestamp_Wrapper*>(
                            pItem)->getValue ());
                }
                else if (PyObject_TypeCheck (
                             pItem, MI_Interval_Wrapper::getPyTypeObject ()))
                {
                    //SCX_BOOKEND_PRINT ("insert new MI_Interval");
                    pArray->push_back (
                        reinterpret_cast<MI_Interval_Wrapper*>(
                            pItem)->getValue ());
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("fromPyObject failed");
                    rval = PY_FAILURE;
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("list convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
        else if (PyTuple_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyTuple");
            MI_Array<MI_DATETIMEA>::Ptr pArray (new MI_Array<MI_DATETIMEA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyTuple_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pItem = PyTuple_GET_ITEM (pValue, i);
                if (PyObject_TypeCheck (
                        pItem, MI_Timestamp_Wrapper::getPyTypeObject ()))
                {
                    //SCX_BOOKEND_PRINT ("insert new MI_Timestamp");
                    pArray->push_back (
                        reinterpret_cast<MI_Timestamp_Wrapper*>(
                            pItem)->getValue ());
                }
                else if (PyObject_TypeCheck (
                             pItem, MI_Interval_Wrapper::getPyTypeObject ()))
                {
                    //SCX_BOOKEND_PRINT ("insert new MI_Interval");
                    pArray->push_back (
                        reinterpret_cast<MI_Interval_Wrapper*>(
                            pItem)->getValue ());
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("fromPyObject failed");
                    rval = PY_FAILURE;
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("tuple convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


/*static*/ MI_Array_Wrapper<MI_DATETIMEA>::PyPtr
MI_Array_Wrapper<MI_DATETIMEA>::createPyPtr (
    MI_Array<MI_DATETIMEA>::Ptr const& pArray)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::createPyPtr");
    PyObjPtr pPyArray (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyArray)
    {
        MI_Array_Wrapper<MI_DATETIMEA>* pWrapper =
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pPyArray.get ());
        pWrapper->ctor ();
        pWrapper->m_pArray = pArray;
        return PyPtr (
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(
                pPyArray.release ()), DO_NOT_INC_REF);
    }
    return PyPtr ();
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_getType (
    PyObject* pSelf)
{
    return PyInt_FromSize_t (MI_DATETIMEA);
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_getValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::_getValueAt");
    PyObject* pRval = NULL;
    long index = 0;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_DATETIMEA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            MI_Datetime::Ptr pDatetime =
                pArray->m_pArray->getValueAt (index);
            if (pDatetime->isTimestamp ())
            {
                MI_Timestamp::Ptr pTimestamp (
                    static_cast<MI_Timestamp*>(pDatetime.get ()));

                MI_Timestamp_Wrapper::PyPtr pyTimestamp (
                    MI_Timestamp_Wrapper::createPyPtr (pTimestamp));

                pRval = reinterpret_cast<PyObject*>(pyTimestamp.release ());
            }
            else
            {
                MI_Interval::Ptr pInterval (
                    static_cast<MI_Interval*>(pDatetime.get ()));
                MI_Interval_Wrapper::PyPtr pyInterval (
                    MI_Interval_Wrapper::createPyPtr (pInterval));
                pRval = reinterpret_cast<PyObject*>(pyInterval.release ());
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments");
    }
    return pRval;
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_setValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::_setValueAt");
    PyObject* rval = NULL;
    long index = 0;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_DATETIMEA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            if (PyObject_TypeCheck (
                    pValueObj, MI_Timestamp_Wrapper::getPyTypeObject ()))
            {
                //SCX_BOOKEND_PRINT ("MI_Timestamp");
                pArray->m_pArray->setValueAt (
                    index,
                    reinterpret_cast<MI_Timestamp_Wrapper*>(
                        pValueObj)->getValue ());
                rval = Py_None;
            }
            else if (PyObject_TypeCheck (
                         pValueObj, MI_Interval_Wrapper::getPyTypeObject ()))
            {
                //SCX_BOOKEND_PRINT ("MI_Interval");
                pArray->m_pArray->setValueAt (
                    index,
                    reinterpret_cast<MI_Interval_Wrapper*>(
                        pValueObj)->getValue ());
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("unhandled type");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_append (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::_append");
    PyObject* rval = NULL;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "O", KEYWORDS, &pValueObj))
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_DATETIMEA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
        if (PyObject_TypeCheck (
                pValueObj, MI_Timestamp_Wrapper::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("push_back new MI_Timestamp");
            pArray->m_pArray->push_back (
                reinterpret_cast<MI_Timestamp_Wrapper*>(
                    pValueObj)->getValue ());
            rval = Py_None;
        }
        else if (PyObject_TypeCheck (
                     pValueObj, MI_Interval_Wrapper::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("push_back new MI_Interval");
            pArray->m_pArray->push_back (
                reinterpret_cast<MI_Interval_Wrapper*>(
                    pValueObj)->getValue ());
            rval = Py_None;
        }
        else
        {
            SCX_BOOKEND_PRINT ("unhandled type");
            PyErr_SetString (PyExc_ValueError, "incompatible value type.");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_insert (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::_insert");
    PyObject* rval = NULL;
    long index = 0;;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_DATETIMEA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<long>(pArray->m_pArray->size ()) >= index)
        {
            if (PyObject_TypeCheck (
                    pValueObj, MI_Timestamp_Wrapper::getPyTypeObject ()))
            {
                //SCX_BOOKEND_PRINT ("insert new MI_Timestamp");
                pArray->m_pArray->insert (
                    index,
                    reinterpret_cast<MI_Timestamp_Wrapper*>(
                        pValueObj)->getValue ());
                rval = Py_None;
            }
            else if (PyObject_TypeCheck (
                         pValueObj, MI_Interval_Wrapper::getPyTypeObject ()))
            {
                //SCX_BOOKEND_PRINT ("insert new MI_Interval");
                pArray->m_pArray->insert (
                    index,
                    reinterpret_cast<MI_Interval_Wrapper*>(
                        pValueObj)->getValue ());
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("unhandled type");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    Py_XINCREF (rval);
    return rval;
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_pop (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_pop");
    PyObject* rval = NULL;
    MI_Array_Wrapper<MI_DATETIMEA>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
    long index = static_cast<long>(pArray->m_pArray->size ()) - 1;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            MI_Datetime::Ptr pDatetime =
                pArray->m_pArray->getValueAt (index);
            if (pDatetime->isTimestamp ())
            {
                MI_Timestamp::Ptr pTimestamp (
                    static_cast<MI_Timestamp*>(pDatetime.get ()));
                MI_Timestamp_Wrapper::PyPtr pyTimestamp (
                    MI_Timestamp_Wrapper::createPyPtr (pTimestamp));
                rval = reinterpret_cast<PyObject*>(pyTimestamp.release ());
            }
            else
            {
                MI_Interval::Ptr pInterval (
                    static_cast<MI_Interval*>(pDatetime.get ()));
                MI_Interval_Wrapper::PyPtr pyInterval (
                    MI_Interval_Wrapper::createPyPtr (pInterval));
                rval = reinterpret_cast<PyObject*>(pyInterval.release ());
            }
            pArray->m_pArray->erase (index);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments.");
    }
    return rval;
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::_count (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("static MI_Array_Wrapper<MI_DATETIMEA>::_count");
    MI_Array_Wrapper<MI_DATETIMEA> const* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA> const*>(pSelf);
    return PyLong_FromSsize_t (pArray->m_pArray->size ());
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::getIter (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::getIter");
    MI_Array_Wrapper<MI_DATETIMEA>* pArrayWrapper =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pObj);
    MI_Array_Iterator<MI_DATETIMEA>::PyPtr pIterator (
        MI_Array_Iterator<MI_DATETIMEA>::createPyPtr (
            pArrayWrapper->m_pArray, -1));
    return reinterpret_cast<PyObject*>(pIterator.release ());
}


/*static*/ PyObject*
MI_Array_Wrapper<MI_DATETIMEA>::to_str (
    PyObject* pSelf)
{
    MI_Array_Wrapper<MI_DATETIMEA>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(pSelf);
    std::ostringstream strm;
    strm << NAME << "([";
    size_t const size = pArray->m_pArray->size ();
    if (0 < size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            MI_Datetime::Ptr pDatetime (pArray->m_pArray->getValueAt (i));
            if (0 != i)
            {
                strm << ',';
            }
            if (pDatetime->isTimestamp ())
            {
                strm << *static_cast<MI_Timestamp const*>(pDatetime.get ());
            }
            else
            {
                strm << *static_cast<MI_Interval const*>(pDatetime.get ());
            }
        }
        //rval = PyString_FromString (strm.str ().c_str ());
    }
    strm << "])";
    return PyString_FromString (strm.str ().c_str ());
}


/*static*/ PyTypeObject*
MI_Array_Wrapper<MI_DATETIMEA>::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


void
MI_Array_Wrapper<MI_DATETIMEA>::ctor ()
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_DATETIMEA>::ctor");
    new (&m_pArray) MI_Array<MI_DATETIMEA>::Ptr (new MI_Array<MI_DATETIMEA> ());
}


void
MI_Array_Wrapper<MI_DATETIMEA>::dtor ()
{
    //SCX_BOOKEND ("MI_Array_Wrapper::dtor");
    typedef util::internal_counted_ptr<MI_Array<MI_DATETIMEA> > ptr;
    m_pArray.~ptr ();
}


MI_Array<MI_DATETIMEA>*
MI_Array_Wrapper<MI_DATETIMEA>::getValue () const
{
    return m_pArray.get ();
}


// MI_Array_Wrapper specialization definitions
//------------------------------------------------------------------------------
template<>
/*static*/ int
MI_Array_Wrapper<MI_BOOLEANA>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_BOOLEANA>::init");
    int rval = PY_FAILURE;
    MI_Array_Wrapper<MI_BOOLEANA>* pWrapper =
        reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
    pWrapper->ctor ();
    PyObject* pValue = NULL;
    char* KEYWORDS[] = {
        "values",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|O", KEYWORDS, &pValue))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (NULL == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** NULL");
            rval = PY_SUCCESS;
        }
        else if (Py_None == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** Py_None");
            rval = PY_SUCCESS;
        }
#if (__MI_WRAPPER_COPY_CTOR__)
        else if (PyObject_TypeCheck (pValue, getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("***** MI_Array_Wrapper<MI_BOOLEANA>");
            MI_Array_Wrapper<MI_BOOLEANA>* pOtherWrapper =
                reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pValue);
            pWrapper->m_pArray = pOtherWrapper->m_pArray;
            rval = PY_SUCCESS;
        }
#endif // __MI_WRAPPER_COPY_CTOR__
        else if (PyList_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyList");
            MI_Array<MI_BOOLEANA>::Ptr pArray (new MI_Array<MI_BOOLEANA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyList_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pObj = PyList_GET_ITEM (pValue, i);
                if (Py_False == pObj)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (MI_FALSE);
                }
                else if (Py_True == pObj)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (MI_TRUE);
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("value is not boolean");
                    rval = PY_FAILURE;
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("list convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
        else if (PyTuple_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyTuple");
            MI_Array<MI_BOOLEANA>::Ptr pArray (new MI_Array<MI_BOOLEANA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyTuple_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pObj = PyTuple_GET_ITEM (pValue, i);
                if (Py_False == pObj)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (MI_FALSE);
                }
                else if (Py_True == pObj)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (MI_TRUE);
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("value is not boolean");
                    rval = PY_FAILURE;
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("tuple convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_getValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_BOOLEANA>::_getValueAt");
    PyObject* pRval = NULL;
    long index = 0;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_BOOLEANA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            pRval = (*pArray->m_pArray)[index] == MI_FALSE
                ? Py_False : Py_True;
            Py_INCREF (pRval);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments");
    }
    return pRval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_setValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_setValueAt");
    PyObject* rval = NULL;
    long index = 0;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_BOOLEANA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            if (Py_False == pValueObj)
            {
                (*(pArray->m_pArray))[index] = MI_FALSE;
                rval = Py_None;
            }
            else if (Py_True == pValueObj)
            {
                (*(pArray->m_pArray))[index] = MI_TRUE;
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("value is not boolean");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_append (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_BOOLEANA>::_append");
    PyObject* rval = NULL;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "O", KEYWORDS, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_BOOLEANA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
        if (Py_False == pValueObj)
        {
            pArray->m_pArray->push_back (MI_FALSE);
            rval = Py_None;
        }
        else if (Py_True == pValueObj)
        {
            pArray->m_pArray->push_back (MI_TRUE);
            rval = Py_None;
        }
        else
        {
            //SCX_BOOKEND_PRINT ("value is not boolean");
            PyErr_SetString (PyExc_ValueError, "incompatible value type.");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_insert (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_BOOLEANA>::_insert");
    PyObject* rval = NULL;
    long index = 0;;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<MI_BOOLEANA>* pArray =
            reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<long>(pArray->m_pArray->size ()) >= index)
        {
            if (Py_False == pValueObj)
            {
                pArray->m_pArray->insert (index, MI_FALSE);
                rval = Py_None;
            }
            else if (Py_True == pValueObj)
            {
                pArray->m_pArray->insert (index, MI_TRUE);
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("value is not boolean");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_pop (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper<MI_BOOLEANA>::_pop");
    PyObject* rval = NULL;
    MI_Array_Wrapper<MI_BOOLEANA>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
    long index = static_cast<long>(pArray->m_pArray->size ()) - 1;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            rval = (*(pArray->m_pArray))[index] == MI_FALSE
                ? Py_False : Py_True;
            Py_INCREF (rval);
            pArray->m_pArray->erase (index);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments.");
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::to_str");
    MI_Array_Wrapper<MI_BOOLEANA>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(pSelf);
    std::ostringstream strm;
    strm << NAME << "([";
    size_t const size = pArray->m_pArray->size ();
    if (0 < size)
    {
        strm << ((*(pArray->m_pArray))[0] == MI_FALSE ? "False" : "True");
        for (size_t i = 1; i < size; ++i)
        {
            strm << ','
                 << ((*(pArray->m_pArray))[i] == MI_FALSE ? "False" : "True");
        }
    }
    strm << "])";
    return PyString_FromString (strm.str ().c_str ());
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_UINT8A>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::to_str");
    MI_Array_Wrapper<MI_UINT8A>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_UINT8A>*>(pSelf);
    std::ostringstream strm;
    strm << NAME << "([";
    size_t const size = pArray->m_pArray->size ();
    if (0 < size)
    {
        strm << static_cast<unsigned>((*(pArray->m_pArray))[0]);
        for (size_t i = 1; i < size; ++i)
        {
            strm << ',' << static_cast<unsigned>((*(pArray->m_pArray))[i]);
        }
    }
    strm << "])";
    return PyString_FromString (strm.str ().c_str ());
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_SINT8A>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::to_str");
    MI_Array_Wrapper<MI_SINT8A>* pArray =
        reinterpret_cast<MI_Array_Wrapper<MI_SINT8A>*>(pSelf);
    std::ostringstream strm;
    strm << NAME << "([";
    size_t const size = pArray->m_pArray->size ();
    if (0 < size)
    {
        strm << static_cast<int>((*(pArray->m_pArray))[0]);
        for (size_t i = 1; i < size; ++i)
        {
            strm << ',' << static_cast<int>((*(pArray->m_pArray))[i]);
        }
    }
    strm << "])";
    return PyString_FromString (strm.str ().c_str ());
}


// MI_PropertySet_Wrapper definitions
//------------------------------------------------------------------------------
/*static*/ PyTypeObject MI_PropertySet_Wrapper::s_PyTypeObject = {};
/*static*/ char const MI_PropertySet_Wrapper::NAME[] = "MI_PropertySet";
/*static*/ char const MI_PropertySet_Wrapper::OMI_NAME[] = "omi.MI_PropertySet";
/*static*/ char const MI_PropertySet_Wrapper::DOC[] =
    "omi.MI_PropertySet utility";
/*static*/ PyMethodDef MI_PropertySet_Wrapper::METHODS[] = {
    { "GetElementCount",
      reinterpret_cast<PyCFunction>(MI_PropertySet_Wrapper::_GetElementCount),
      METH_NOARGS, "return item count" },
    { NULL, NULL, 0, NULL }
};


/*static*/ void
MI_PropertySet_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_PropertySet_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_PropertySet_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
//    s_PyTypeObject.tp_init = init;
//    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_methods = METHODS;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
        //MI_Array_Iterator<TYPE_ID>::moduleInit (pModule);
    }
}


/*static*/ PyTypeObject*
MI_PropertySet_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


/*static*/ void
MI_PropertySet_Wrapper::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_PropertySet_Wrapper::dealloc");
    MI_PropertySet_Wrapper* pPropertySet =
        reinterpret_cast<MI_PropertySet_Wrapper*>(pSelf);
    pPropertySet->~MI_PropertySet_Wrapper ();
    pPropertySet->ob_type->tp_free (pSelf);
}


///*static*/ PyObject*
//MI_PropertySet_Wrapper::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_PropertySet_Wrapper::newObj");
//    return pType->tp_alloc (pType, 0);
//}


///*static*/ int
//MI_PropertySet_Wrapper::init (
//    PyObject* pSelf,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_PropertySet_Wrapper::init");
//    int rval = -1;
//    MI_PropertySet_Wrapper* pPropertySet =
//        new (pSelf) MI_PropertySet_Wrapper (MI_PropertySet::ConstPtr ());
//    PyObject* pValueObj = NULL;
//    char* KEYWORDS[] = {
//        "value",
//        NULL
//    };
//    if (PyArg_ParseTupleAndKeywords (
//            args, keywords, "|O", KEYWORDS, &pValueObj))
//    {
//        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
//        if (NULL == pValueObj ||
//            Py_None == pValueObj)
//        {
//            //SCX_BOOKEND_PRINT ("***** NULL or PyNone");
//            rval = 0;
//        }
//        else if (PyObject_TypeCheck (pValueObj, getPyTypeObject ()))
//        {
//            SCX_BOOKEND_PRINT ("***** MI_PropertySet_Wrapper");
//            MI_PropertySet_Wrapper* pOtherPropertySet =
//                reinterpret_cast<MI_PropertySet_Wrapper*>(pValueObj);
//            pPropertySet->m_pPropertySet = pOtherPropertySet->m_pPropertySet;
//            rval = 0;
//        }
//    }
//    if (PY_FAILURE == rval)
//    {
//        PyErr_SetString (PyExc_ValueError,
//                         "MI_PropertySet_Wrapper invalid arguments.");
//        rval = -1;
//    }
//    return rval;
//}


/*static*/ PyObject*
MI_PropertySet_Wrapper::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_PropertySet_Wrapper::to_str");
    MI_PropertySet_Wrapper* pPropertySet =
        reinterpret_cast<MI_PropertySet_Wrapper*>(pSelf);
    std::ostringstream strm;
    strm << "[";
    size_t const size = pPropertySet->m_pPropertySet->GetElementCount ();
    if (0 < size)
    {
        strm << pPropertySet->m_pPropertySet->GetElementAt (0)->getValue ();
        for (size_t i = 1; i < size; ++i)
        {
            strm << ", "
                 << pPropertySet->m_pPropertySet->GetElementAt (0)->getValue ();
        }
    }
    strm << "]";
    return PyString_FromString (strm.str ().c_str ());
}


/*static*/ MI_PropertySet_Wrapper::PyPtr
MI_PropertySet_Wrapper::createPyPtr (
    MI_PropertySet::ConstPtr const& pPropertySet)
{
    //SCX_BOOKEND ("MI_PropertySet_Wrapper::createPyPtr");
    PyObjPtr pPyPropertySet (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyPropertySet)
    {
        return PyPtr (new (pPyPropertySet.release ())
                      MI_PropertySet_Wrapper (pPropertySet));
    }
    return PyPtr ();
}


/*static*/ PyObject*
MI_PropertySet_Wrapper::_GetElementCount (
    MI_PropertySet_Wrapper* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_PropertySet_Wrapper::_GetElementCount");
    if (pSelf->m_pPropertySet)
    {
        return PyLong_FromSize_t (pSelf->m_pPropertySet->GetElementCount ());
    }
    Py_RETURN_NONE;
}


/*static*/ PyObject*
MI_PropertySet_Wrapper::_ContainsElement (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_PropertySet_Wrapper::_ContainsElement");
    PyObject* rval = NULL;
    PyObject* pKeyObj = NULL;
    char* KEYWORDS[] = {
        "key",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "O", KEYWORDS, &pKeyObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Type<MI_STRING>::type_t key;
        if (PY_SUCCESS == fromPyObject (pKeyObj, &key))
        {
            MI_PropertySet_Wrapper* pPropertySet =
                reinterpret_cast<MI_PropertySet_Wrapper*>(pSelf);
            rval = pPropertySet->m_pPropertySet->ContainsElement (key) ?
                Py_True : Py_False;
        }
        else
        {
            //SCX_BOOKEND_PRINT ("fromPyObject failed");
            PyErr_SetString (PyExc_ValueError,
                             "incompatible value type.");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


/*static*/ PyObject*
MI_PropertySet_Wrapper::_GetElementAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_PropertySet_Wrapper::_GetElementAt");
//    MI_Wrapper<MI_STRING>* rval = NULL;
    MI_Wrapper<MI_STRING>::PyPtr rval;
    long index = 0;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "l", KEYWORDS, &index))
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_PropertySet_Wrapper* pPropertySet =
            reinterpret_cast<MI_PropertySet_Wrapper*>(pSelf);
        if (pPropertySet->m_pPropertySet)
        {
            if (0 <= index &&
                static_cast<size_t>(index) <=
                    pPropertySet->m_pPropertySet->GetElementCount ())
            {
                MI_Value<MI_STRING>::ConstPtr const& pValue =
                    pPropertySet->m_pPropertySet->GetElementAt (index);
                rval = MI_Wrapper<MI_STRING>::createPyPtr (
                    MI_Value<MI_STRING>::Ptr (
                        new MI_Value<MI_STRING>(pValue->getValue ())));
//                PyTypeObject* pTypeObject =
//                    MI_Wrapper<MI_STRING>::getPyTypeObject ();
//                rval = new (pTypeObject->tp_alloc (pTypeObject, 0))
//                    MI_Wrapper<MI_STRING>;
//                rval->setValue (pValue->getValue ());
            }
            else
            {
                SCX_BOOKEND_PRINT ("index outside of array bounds");
                PyErr_SetString (PyExc_IndexError,
                                 "index out of array bounds.");
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_PropertySet is empty.");
            PyErr_SetString (PyExc_ValueError, "MI_PropertySet is empty.");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
//    Py_XINCREF (rval);
//    return reinterpret_cast<PyObject*>(rval);
    if (rval)
    {
        return reinterpret_cast<PyObject*>(rval.release ());
    }
    return NULL;
}


/*ctor*/
MI_PropertySet_Wrapper::MI_PropertySet_Wrapper (
    MI_PropertySet::ConstPtr const& pPropertySet)
    : m_pPropertySet (pPropertySet)
{
    SCX_BOOKEND ("MI_PropertySet_Wrapper::ctor");
    // empty
}


/*dtor*/
MI_PropertySet_Wrapper::~MI_PropertySet_Wrapper ()
{
    SCX_BOOKEND ("MI_PropertySet_Wrapper::dtor");
    // empty
}


} // namespace scx
