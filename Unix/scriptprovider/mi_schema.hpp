// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_MI_SCHEMA_HPP
#define INCLUDED_MI_SCHEMA_HPP


#include "MI.h"


#include "debug_tags.hpp"
#include "internal_counted_ptr.hpp"
#include "mi_context.hpp"
#include "mi_function_table.hpp"
#include "mi_value.hpp"
#include "shared_protocol.hpp"
#include "socket_wrapper.hpp"


#include <string>
#include <vector>


#ifndef EXPORT_PUBLIC
#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))
#endif


namespace scx
{


class MI_SchemaDecl;


class EXPORT_PUBLIC MI_QualifierDecl : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_QualifierDecl> Ptr;
    typedef util::internal_counted_ptr<MI_QualifierDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_QualifierDecl (
        MI_Value<MI_STRING>::ConstPtr const& name,
        MI_Value<MI_UINT32>::ConstPtr const& type,
        MI_Value<MI_UINT32>::ConstPtr const& scope,
        MI_Value<MI_UINT32>::ConstPtr const& flavor,
        MI_ValueBase::ConstPtr const& pValue);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_QualifierDecl ();

    MI_Value<MI_STRING>::ConstPtr const& getName () const;
    MI_Value<MI_UINT32>::ConstPtr const& getType () const;
    MI_Value<MI_UINT32>::ConstPtr const& getScope () const;
    MI_Value<MI_UINT32>::ConstPtr const& getFlavor () const;
    MI_ValueBase::ConstPtr const& getValue () const;

    int send (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_QualifierDecl (MI_QualifierDecl const& ref); // = delete
    MI_QualifierDecl& operator = (MI_QualifierDecl const&); // = delete

    MI_Value<MI_STRING>::ConstPtr const m_pName;
    MI_Value<MI_UINT32>::ConstPtr const m_pType;
    MI_Value<MI_UINT32>::ConstPtr const m_pScope;
    MI_Value<MI_UINT32>::ConstPtr const m_pFlavor;
    MI_ValueBase::ConstPtr const m_pValue;
};


class EXPORT_PUBLIC MI_Qualifier : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_Qualifier> Ptr;
    typedef util::internal_counted_ptr<MI_Qualifier const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_Qualifier (
        MI_Value<MI_STRING>::ConstPtr const& pName,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
        MI_ValueBase::ConstPtr const& pValue);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_Qualifier ();

    MI_Value<MI_STRING>::ConstPtr const& getName () const;
    MI_Value<MI_UINT32>::ConstPtr const& getType () const;
    MI_Value<MI_UINT32>::ConstPtr const& getFlavor () const;
    MI_ValueBase::ConstPtr const& getValue () const;

    int send (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_Qualifier (MI_Qualifier const& ref); // = delete
    MI_Qualifier& operator = (MI_Qualifier const&); // = delete

    MI_Value<MI_STRING>::ConstPtr const m_pName;
    MI_Value<MI_UINT32>::ConstPtr const m_pType;
    MI_Value<MI_UINT32>::ConstPtr const m_pFlavor;
    MI_ValueBase::ConstPtr const m_pValue;
};


class EXPORT_PUBLIC MI_ParameterDecl : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_ParameterDecl> Ptr;
    typedef util::internal_counted_ptr<MI_ParameterDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_ParameterDecl (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        MI_Qualifier::ConstPtr const* const ppQualifiersBegin,
        size_t const& qualifiersCount,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_STRING>::ConstPtr const& pClassName);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_ParameterDecl ();

    MI_Value<MI_UINT32>::ConstPtr const& getFlags () const;
    MI_Value<MI_UINT32>::ConstPtr const& getCode () const;
    MI_Value<MI_STRING>::ConstPtr const& getName () const;
    MI_Value<MI_UINT32>::ConstPtr const& getType () const;
    MI_Value<MI_STRING>::ConstPtr const& getClassName () const;

    virtual int send (socket_wrapper& sock) const;
    virtual int send_type (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_ParameterDecl (MI_ParameterDecl const& ref); // = delete
    MI_ParameterDecl& operator = (MI_ParameterDecl const&); // = delete

    MI_Value<MI_UINT32>::ConstPtr const m_pFlags;
    MI_Value<MI_UINT32>::ConstPtr const m_pCode;
    MI_Value<MI_STRING>::ConstPtr const m_pName;
    std::vector<MI_Qualifier::ConstPtr> const m_Qualifiers;
    MI_Value<MI_UINT32>::ConstPtr const m_pType;
    MI_Value<MI_STRING>::ConstPtr const m_pClassName;
};


class EXPORT_PUBLIC MI_PropertyDecl : public MI_ParameterDecl
{
public:
    typedef util::internal_counted_ptr<MI_PropertyDecl> Ptr;
    typedef util::internal_counted_ptr<MI_PropertyDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_PropertyDecl (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        MI_Qualifier::ConstPtr const* const ppQualifiersBegin,
        size_t const& qualifiersCount,
        MI_Value<MI_UINT32>::ConstPtr const& pType,
        MI_Value<MI_STRING>::ConstPtr const& pClassName,
        MI_Value<MI_STRING>::ConstPtr const& pOrigin,
        MI_Value<MI_STRING>::ConstPtr const& pPropagator,
        MI_ValueBase::ConstPtr const& pValue);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_PropertyDecl ();

    MI_Value<MI_STRING>::ConstPtr const& getOrigin () const;
    MI_Value<MI_STRING>::ConstPtr const& getPropagator () const;
    MI_ValueBase::ConstPtr const& getValue () const;

    int send (socket_wrapper& sock) const;
    int send_type (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_PropertyDecl (MI_PropertyDecl const& ref); // = delete
    MI_PropertyDecl& operator = (MI_PropertyDecl const&); // = delete

    MI_Value<MI_STRING>::ConstPtr const m_pOrigin;
    MI_Value<MI_STRING>::ConstPtr const m_pPropagator;
    MI_ValueBase::ConstPtr const m_pValue;
};


class EXPORT_PUBLIC MI_ObjectDecl : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_ObjectDecl> Ptr;
    typedef util::internal_counted_ptr<MI_ObjectDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_ObjectDecl (
        MI_Value<MI_UINT32>::ConstPtr const& flags,
        MI_Value<MI_UINT32>::ConstPtr const& code,
        MI_Value<MI_STRING>::ConstPtr const& name,
        MI_Qualifier::ConstPtr const* ppQualifiersBegin,
        size_t const& qualifiersCount,
        MI_ParameterDecl::ConstPtr const* ppParametersBegin,
        size_t const& parametersCount);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_ObjectDecl ();

    EXPORT_PUBLIC virtual bool isMethodDecl () const;

    EXPORT_PUBLIC MI_ParameterDecl::ConstPtr getParameterDecl (
        MI_Value<MI_STRING>::type_t const& parameterName) const;

    MI_Value<MI_UINT32>::ConstPtr const& getFlags () const;
    MI_Value<MI_UINT32>::ConstPtr const& getCode () const;
    MI_Value<MI_STRING>::ConstPtr const& getName () const;

    virtual int send (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_ObjectDecl (MI_ObjectDecl const& ref); // = delete
    MI_ObjectDecl& operator = (MI_ObjectDecl const&); // = delete

    MI_Value<MI_UINT32>::ConstPtr const m_pFlags;
    MI_Value<MI_UINT32>::ConstPtr const m_pCode;
    MI_Value<MI_STRING>::ConstPtr const m_pName;
    std::vector<MI_Qualifier::ConstPtr> const m_Qualifiers;
    std::vector<MI_ParameterDecl::ConstPtr> const m_Parameters;

    friend class MI_SchemaDecl;
};


class EXPORT_PUBLIC MI_MethodDecl : public MI_ObjectDecl
{
public:
    typedef util::internal_counted_ptr<MI_MethodDecl> Ptr;
    typedef util::internal_counted_ptr<MI_MethodDecl const> ConstPtr;

    typedef util::function_base<
        void,
        MI_Context::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&,
        MI_Instance::Ptr const&> InvokeFn;

    EXPORT_PUBLIC /*ctor*/ MI_MethodDecl (
        MI_Value<MI_UINT32>::ConstPtr const& flags,
        MI_Value<MI_UINT32>::ConstPtr const& code,
        MI_Value<MI_STRING>::ConstPtr const& name,
        MI_Qualifier::ConstPtr const* ppQualifiersBegin,
        size_t const& qualifiersCount,
        MI_ParameterDecl::ConstPtr const* ppParametersBegin,
        size_t const& parametersCount,
        MI_Value<MI_UINT32>::ConstPtr const& returnType,
        MI_Value<MI_STRING>::ConstPtr const& origin,
        MI_Value<MI_STRING>::ConstPtr const& propagator,
        InvokeFn::ConstPtr const& pInvokeFn);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_MethodDecl ();

    EXPORT_PUBLIC bool isMethodDecl () const;

    MI_Value<MI_UINT32>::ConstPtr const& getReturnType () const;
    MI_Value<MI_STRING>::ConstPtr const& getOrigin () const;
    MI_Value<MI_STRING>::ConstPtr const& getPropagator () const;
    InvokeFn::ConstPtr const& getInvokeFn () const;

    int send (socket_wrapper& sock) const;

    void Invoke (
        MI_Context::Ptr const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Value<MI_STRING>::Ptr const& pMethodName,
        MI_Instance::Ptr const& pInstanceName,
        MI_Instance::Ptr const& pParameters) const;

private:
    /*ctor*/ MI_MethodDecl (MI_MethodDecl const& ref); // = delete
    MI_MethodDecl& operator = (MI_MethodDecl const&); // = delete

    MI_Value<MI_UINT32>::ConstPtr const m_pReturnType;
    MI_Value<MI_STRING>::ConstPtr const m_pOrigin;
    MI_Value<MI_STRING>::ConstPtr const m_pPropagator;
    util::internal_counted_ptr<MI_SchemaDecl const> m_pSchemaDecl;
    InvokeFn::ConstPtr const m_pInvokeFn;

    friend class MI_SchemaDecl;
};


//class EXPORT_PUBLIC MI_ClassDecl : public util::ref_counted_obj
class EXPORT_PUBLIC MI_ClassDecl : public MI_ObjectDecl
{
public:
    typedef util::internal_counted_ptr<MI_ClassDecl> Ptr;
    typedef util::internal_counted_ptr<MI_ClassDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_ClassDecl (
        MI_Value<MI_UINT32>::ConstPtr const& pFlags,
        MI_Value<MI_UINT32>::ConstPtr const& pCode,
        MI_Value<MI_STRING>::ConstPtr const& pName,
        MI_Qualifier::ConstPtr const* ppQualifiersBegin,
        size_t const& qualifiersCount,
        MI_PropertyDecl::ConstPtr const* ppPropertyDeclsBegin,
        size_t const& propertyDeclsCount,
        MI_Value<MI_STRING>::ConstPtr const& pSuperClassName,
        MI_MethodDecl::Ptr const* ppMethodDeclsBegin,
        size_t const& methodDeclsCount,
        MI_FunctionTable::ConstPtr const& pFunctionTable);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_ClassDecl ();

    EXPORT_PUBLIC void setOwningClassDecl (
        MI_ClassDecl::Ptr const& pOwningClassDecl);

    EXPORT_PUBLIC MI_PropertyDecl::ConstPtr getPropertyDecl (
        MI_Value<MI_STRING>::type_t const& propertyName) const;

    EXPORT_PUBLIC MI_MethodDecl::ConstPtr getMethodDecl (
        MI_Value<MI_STRING>::type_t const& methodName) const;

    MI_Value<MI_STRING>::ConstPtr const& getSuperClassName () const;
    MI_ClassDecl::ConstPtr const& getSuperClassDecl () const;
    std::vector<MI_MethodDecl::Ptr> const& getMethodDecls () const;
    util::internal_counted_ptr<MI_SchemaDecl const> const&
    getSchemaDecl () const;
    MI_FunctionTable::ConstPtr const& getFunctionTable () const;
    MI_ClassDecl::ConstPtr const& getOwningClassDecl () const;

    int send (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_ClassDecl (MI_ClassDecl const& ref); // = delete
    MI_ClassDecl& operator = (MI_ClassDecl const&); // = delete

    std::vector<MI_PropertyDecl::ConstPtr> const m_PropertyDecls;
    MI_Value<MI_STRING>::ConstPtr const m_pSuperClassName;
    MI_ClassDecl::ConstPtr m_pSuperClassDecl;
    std::vector<MI_MethodDecl::Ptr> m_MethodDecls;
    util::internal_counted_ptr<MI_SchemaDecl const> m_pSchemaDecl;
    MI_FunctionTable::ConstPtr m_pFunctionTable;
    MI_ClassDecl::ConstPtr m_pOwningClassDecl;

    friend class MI_SchemaDecl;
};


class EXPORT_PUBLIC MI_SchemaDecl : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_SchemaDecl> Ptr;
    typedef util::internal_counted_ptr<MI_SchemaDecl const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_SchemaDecl (
        MI_QualifierDecl::ConstPtr const* const ppQualifierDecls,
        size_t const& qualifierDeclCount,
        MI_ClassDecl::Ptr const* const ppClassDecls,
        size_t const& classDeclCount);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_SchemaDecl ();

    std::vector<MI_QualifierDecl::ConstPtr> const& getQualifierDecls () const;
    std::vector<MI_ClassDecl::Ptr> const& getClassDecls () const;

    EXPORT_PUBLIC MI_ClassDecl::ConstPtr getClassDecl (
        MI_Value<MI_STRING>::ConstPtr const& pClassName) const;

    int send (socket_wrapper& sock) const;

private:
    /*ctor*/ MI_SchemaDecl (MI_SchemaDecl const& ref); // = delete
    MI_SchemaDecl& operator = (MI_SchemaDecl const&); // = delete

    std::vector<MI_QualifierDecl::ConstPtr> const m_QualifierDecls;
    std::vector<MI_ClassDecl::Ptr> m_ClassDecls;
};


} // namespace scx


#undef EXPORT_PUBLIC


#endif // INCLUDED_MI_SCHEMA_HPP
