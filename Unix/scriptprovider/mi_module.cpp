// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "mi_module.hpp"


#include "debug_tags.hpp"
#include "mi_context.hpp"
#include "mi_schema.hpp"


namespace scx
{


/*ctor*/
MI_Module::MI_Module (
    MI_SchemaDecl::ConstPtr const& pSchemaDecl,
    LoadFn::Ptr const& pLoadFn,
    UnloadFn::Ptr const& pUnloadFn)
    : m_Version (MI_VERSION)
    , m_GeneratorVersion (MI_MAKE_VERSION (1, 0, 8))
    , m_Flags (MI_MODULE_FLAG_STANDARD_QUALIFIERS |
               MI_MODULE_FLAG_CPLUSPLUS)
    , m_CharSize (sizeof (MI_Char))
    , m_pSchemaDecl (pSchemaDecl)
    , m_pLoadFn (pLoadFn)
    , m_pUnloadFn (pUnloadFn)
{
    SCX_BOOKEND ("MI_Module::ctor");
}


/*dtor*/
MI_Module::~MI_Module ()
{
    SCX_BOOKEND ("MI_Module::dtor");
}


} // namespace scx
