#ifndef INCLUDED_MI_SCRIPT_EXTENSIONS_HPP
#define INCLUDED_MI_SCRIPT_EXTENSIONS_HPP


#include <MI.h>


// struct MI_ProviderScriptFT
// purpose: This is a direct comparable to MI_ProviderFT.  This structure
//          provides a list of the names of all of the associated functions in
//          the script.
//------------------------------------------------------------------------------
struct MI_ProviderScriptFT
{
    MI_Char const* Load;
    MI_Char const* Unload;
    MI_Char const* GetInstance;
    MI_Char const* EnumerateInstances;
    MI_Char const* CreateInstance;
    MI_Char const* ModifyInstance;
    MI_Char const* DeleteInstance;
    MI_Char const* AssociatorInstances;
    MI_Char const* ReferenceInstances;
    MI_Char const* EnableIndications;
    MI_Char const* DisableIndications;
    MI_Char const* Subscribe;
    MI_Char const* Unsubscribe;
    MI_Char const* Invoke;
};


// struct MI_ClassDeclEx
// purpose: This extends MI_ClassDecl to include MI_ScriptProviderFT.
//------------------------------------------------------------------------------
struct MI_ClassDeclEx : public MI_ClassDecl
{
    MI_ProviderScriptFT const* scriptFT;
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
