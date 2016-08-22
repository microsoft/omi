#include "mi_script_extensions.hpp"


#include <algorithm>
#include <string>


namespace
{


class ClassFinder
{
public:
    /*ctor*/ ClassFinder (MI_Char const* const pClassName)
        : m_Name (pClassName) {}

    bool operator () (MI_ClassDecl const* pClass)
    {
        return m_Name == pClass->name;
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
    MI_ClassDecl const* const* ppClassDecl =
        std::find_if (
            pSchemaDecl->classDecls,
            pSchemaDecl->classDecls + pSchemaDecl->numClassDecls,
            ClassFinder (pClassName));
    return ppClassDecl ? static_cast<MI_ClassDeclEx const*>(*ppClassDecl)
                       : NULL;
}
