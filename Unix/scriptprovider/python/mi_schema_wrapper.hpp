#ifndef INCLUDED_MI_SCHEMA_WRAPPER_HPP
#define INCLUDED_MI_SCHEMA_WRAPPER_HPP


#include "Python.h"


#include "mi_function_table_placeholder.hpp"
#include "mi_schema.hpp"
#include "mi_value.hpp"


namespace scx
{


class MI_QualifierDecl_Wrapper
{
public:
    PyObject_HEAD

    typedef MI_QualifierDecl::ConstPtr ValuePtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_QualifierDecl_Wrapper ();

    ValuePtr const& getValuePtr () const;

private:
    /*ctor*/ MI_QualifierDecl_Wrapper (
        MI_Value<MI_STRING>::ConstPtr const& pName,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_UINT32>::ConstPtr const& pScope,
        MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
        MI_ValueBase::ConstPtr const& pValue);

    /*ctor*/ MI_QualifierDecl_Wrapper (
        MI_QualifierDecl_Wrapper const&); // = delete
    MI_QualifierDecl_Wrapper& operator = (
        MI_QualifierDecl_Wrapper const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    ValuePtr m_pValue;
};


inline MI_QualifierDecl_Wrapper::ValuePtr const&
MI_QualifierDecl_Wrapper::getValuePtr () const
{
    return m_pValue;
}


//void init_MI_QualifierDecl_Wrapper (PyObject* const pModule);


class MI_Qualifier_Wrapper
{
public:
    PyObject_HEAD

    typedef MI_Qualifier::ConstPtr ValuePtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_Qualifier_Wrapper ();

    ValuePtr const& getValuePtr () const;

private:
    /*ctor*/ MI_Qualifier_Wrapper (
        MI_Value<MI_STRING>::ConstPtr const& name,
        MI_Value<MI_UINT32>::ConstPtr const& type,
        MI_Value<MI_UINT32>::ConstPtr const& flavor,
        MI_ValueBase::ConstPtr const& pValue);

    /*ctor*/ MI_Qualifier_Wrapper (MI_Qualifier_Wrapper const&); // = delete
    MI_Qualifier_Wrapper& operator = (MI_Qualifier_Wrapper const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    ValuePtr m_pValue;
};


inline MI_Qualifier_Wrapper::ValuePtr const&
MI_Qualifier_Wrapper::getValuePtr () const
{
    return m_pValue;
}


class MI_PropertyDecl_Wrapper
{
public:
    PyObject_HEAD

    typedef MI_PropertyDecl::ConstPtr ValuePtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_PropertyDecl_Wrapper ();

    ValuePtr const& getValuePtr () const;

private:
    /*ctor*/ MI_PropertyDecl_Wrapper (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_STRING>::ConstPtr const& pClassName,
        MI_Value<MI_STRING>::ConstPtr const& pOrigin,
        MI_Value<MI_STRING>::ConstPtr const& pPropagator,
        MI_ValueBase::ConstPtr const& pValue);

    /*ctor*/ MI_PropertyDecl_Wrapper (
        MI_PropertyDecl_Wrapper const&); // = delete
    MI_PropertyDecl_Wrapper& operator = (
        MI_PropertyDecl_Wrapper const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    ValuePtr m_pValue;
};


inline MI_PropertyDecl_Wrapper::ValuePtr const&
MI_PropertyDecl_Wrapper::getValuePtr () const
{
    return m_pValue;
}


class MI_ParameterDecl_Wrapper
{
public:
    PyObject_HEAD

    typedef MI_ParameterDecl::ConstPtr ValuePtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_ParameterDecl_Wrapper ();

    ValuePtr const& getValuePtr () const;

private:
    /*ctor*/ MI_ParameterDecl_Wrapper (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_STRING>::ConstPtr const& pClassName);

    /*ctor*/ MI_ParameterDecl_Wrapper (
        MI_ParameterDecl_Wrapper const&); // = delete
    MI_ParameterDecl_Wrapper& operator = (
        MI_ParameterDecl_Wrapper const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    ValuePtr m_pValue;
};


inline MI_ParameterDecl_Wrapper::ValuePtr const&
MI_ParameterDecl_Wrapper::getValuePtr () const
{
    return m_pValue;
}


class MI_MethodDecl_Placeholder
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_MethodDecl_Placeholder const> ConstPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_MethodDecl_Placeholder ();

    int createMethodDecl (PyObject* const pPyModule,
                          MI_MethodDecl::Ptr* ppMethodDeclOut) const;

private:
    /*ctor*/ MI_MethodDecl_Placeholder (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
        std::vector<MI_ParameterDecl::ConstPtr> const& parameters,
        MI_Value<MI_UINT32>::ConstPtr const& pReturnType,
        MI_Value<MI_STRING>::ConstPtr const& pOrigin,
        MI_Value<MI_STRING>::ConstPtr const& pPropagator,
        MI_Value<MI_STRING>::ConstPtr const& pInvokeFnName);

    /*ctor*/ MI_MethodDecl_Placeholder (
        MI_MethodDecl_Placeholder const&); // = delete
    MI_MethodDecl_Placeholder& operator = (
        MI_MethodDecl_Placeholder const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    MI_Value<MI_UINT32>::ConstPtr const m_pFlags;
    MI_Value<MI_UINT32>::ConstPtr const m_pCode;
    MI_Value<MI_STRING>::ConstPtr const m_pName;
    std::vector<MI_Qualifier::ConstPtr> const m_Qualifiers;
    std::vector<MI_ParameterDecl::ConstPtr> const m_Parameters;
    MI_Value<MI_UINT32>::ConstPtr const m_pReturnType;
    MI_Value<MI_STRING>::ConstPtr const m_pOrigin;
    MI_Value<MI_STRING>::ConstPtr const m_pPropagator;
    MI_Value<MI_STRING>::ConstPtr const m_pInvokeFnName;
};




class MI_ClassDecl_Placeholder
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_ClassDecl_Placeholder const> ConstPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_ClassDecl_Placeholder ();

    MI_ClassDecl::Ptr createClassDecl (PyObject* const pPyModule) const;

    MI_Value<MI_STRING>::ConstPtr const& getName () const;
    MI_Value<MI_STRING>::ConstPtr const& getOwningClassName () const;

private:
    /*ctor*/ MI_ClassDecl_Placeholder (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
        std::vector<MI_PropertyDecl::ConstPtr> const& propertyDecls,
        MI_Value<MI_STRING>::ConstPtr const& pSuperClassName,
        std::vector<MI_MethodDecl_Placeholder::ConstPtr> const& methodDecls,
        MI_FunctionTable_Placeholder::ConstPtr const& pFunctionTable,
        MI_Value<MI_STRING>::ConstPtr const& pOwningClassName);

    /*ctor*/ MI_ClassDecl_Placeholder (
        MI_ClassDecl_Placeholder const&); // = delete
    MI_ClassDecl_Placeholder& operator = (
        MI_ClassDecl_Placeholder const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    MI_Value<MI_UINT32>::ConstPtr const m_pFlags;
    MI_Value<MI_UINT32>::ConstPtr const m_pCode;
    MI_Value<MI_STRING>::ConstPtr const m_pName;
    std::vector<MI_Qualifier::ConstPtr> const m_Qualifiers;
    std::vector<MI_PropertyDecl::ConstPtr> const m_PropertyDecls;
    MI_Value<MI_STRING>::ConstPtr const m_pSuperClassName;
    std::vector<MI_MethodDecl_Placeholder::ConstPtr> const m_MethodDecls;
    MI_FunctionTable_Placeholder::ConstPtr const m_pFunctionTable;
    MI_Value<MI_STRING>::ConstPtr const m_pOwningClassName;
};


class MI_SchemaDecl_Placeholder
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_SchemaDecl_Placeholder const> ConstPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*dtor*/ ~MI_SchemaDecl_Placeholder ();

    MI_SchemaDecl::Ptr createSchemaDecl (PyObject* const pPyModule) const;

private:
    /*ctor*/ MI_SchemaDecl_Placeholder (
        std::vector<MI_QualifierDecl::ConstPtr> const& qualifierDecls,
        std::vector<MI_ClassDecl_Placeholder::ConstPtr> const& classDecls);

    /*ctor*/ MI_SchemaDecl_Placeholder (
        MI_SchemaDecl_Placeholder const&); // = delete
    MI_SchemaDecl_Placeholder& operator = (
        MI_SchemaDecl_Placeholder const&); // = delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    std::vector<MI_QualifierDecl::ConstPtr> const m_QualifierDecls;
    std::vector<MI_ClassDecl_Placeholder::ConstPtr> const m_ClassDecls;
};


} // namespace scx


#endif // INCLUDED_MI_SCHEMA_WRAPPER_HPP
