// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_FUNCTOR_HPP
#define INCLUDED_FUNCTOR_HPP


#include <Python.h>


#include "internal_counted_ptr.hpp"
#include "unique_ptr.hpp"


#include "mi_context.hpp"
#include "mi_instance.hpp"
#include "mi_module.hpp"
#include "mi_value.hpp"
#include "py_ptr.hpp"


namespace scx
{


class Load_Unload_Functor
{
public:
    /*ctor*/ Load_Unload_Functor (py_ptr<PyObject>const& pFn);
    /*dtor*/ ~Load_Unload_Functor ();

    int operator () (
        MI_Module::Ptr const&,
        MI_Context::Ptr const&) const;

private:
    py_ptr<PyObject> const m_pFn;
};


} // namespace scx


#endif // INCLUDED_FUNCTOR_HPP
