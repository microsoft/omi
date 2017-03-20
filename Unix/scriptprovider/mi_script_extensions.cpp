#include "mi_script_extensions.hpp"


#include "debug_tags.hpp"
#include <algorithm>
#include <string>


namespace
{


template<typename T>
class Finder
{
public:
    /*ctor*/ Finder (MI_Char const* const pName)
        : m_Name (pName) {}

    bool operator () (T const* pItem)
    {
        return m_Name == pItem->name;
    }

private:
    std::basic_string<MI_Char> const m_Name;
};


}


MI_ClassDeclEx const*
findClassDecl (
    MI_Char const* const pClassName,
    MI_SchemaDecl const* const pSchemaDecl)
{
    SCX_BOOKEND ("mi_script_extensions.cpp findClassDecl");
    MI_ClassDecl const* const* ppClassDecl =
        std::find_if (
            pSchemaDecl->classDecls,
            pSchemaDecl->classDecls + pSchemaDecl->numClassDecls,
            Finder<MI_ClassDecl> (pClassName));
    return (ppClassDecl != (pSchemaDecl->classDecls + pSchemaDecl->numClassDecls))
        ? static_cast<MI_ClassDeclEx const*>(*ppClassDecl) : NULL;
}


MI_MethodDecl const*
findMethodDecl (
    MI_Char const* const pMethodName,
    MI_ClassDecl const* const pClassDecl)
{
    SCX_BOOKEND ("mi_script_extensions.cpp findMethodDecl");
    MI_MethodDecl const* const* ppMethodDecl =
        std::find_if (
            pClassDecl->methods,
            pClassDecl->methods + pClassDecl->numMethods,
            Finder<MI_MethodDecl> (pMethodName));
    return (ppMethodDecl != (pClassDecl->methods + pClassDecl->numMethods))
        ? *ppMethodDecl : NULL;
}
