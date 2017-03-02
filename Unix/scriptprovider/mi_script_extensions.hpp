#ifndef INCLUDED_MI_SCRIPT_EXTENSIONS_HPP
#define INCLUDED_MI_SCRIPT_EXTENSIONS_HPP


#include <MI.h>


// struct MI_ClassDeclEx
// purpose: This extends MI_ClassDecl to include MI_ScriptProviderFT.
//------------------------------------------------------------------------------
struct MI_ClassDeclEx : public MI_ClassDecl
{
    MI_Uint32 functionTableFlags;
    MI_Char const* owningClassName;
};


MI_ClassDeclEx const*
findClassDecl (
    MI_Char const* const pClassName,
    MI_SchemaDecl const* const pSchemaDecl);


MI_MethodDecl const*
findMethodDecl (
    MI_Char const* const pMethodName,
    MI_ClassDecl const* const pClassDecl);


#endif // INCLUDED_MI_SCRIPT_EXTENSIONS_HPP
