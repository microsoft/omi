#ifndef INCLUDED_MI_SCRIPT_EXTENSIONS_TEST_HPP
#define INCLUDED_MI_SCRIPT_EXTENSIONS_TEST_HPP


#include "test_helper.hpp"


#include <mi_script_extensions.hpp>


namespace test
{


class mi_script_extensions_test : public test_class<mi_script_extensions_test>
{
public:
    /*ctor*/ mi_script_extensions_test ();

    int test01 ();
    int test02 ();
    int test03 ();

private:
    MI_ClassDeclEx CLASS_0;
    MI_ClassDeclEx CLASS_1;
    MI_ClassDeclEx CLASS_2;

    MI_ClassDecl const* CLASSES[3];

    MI_SchemaDecl SCHEMA;
};


} // namespace test


#endif // INCLUDED_MI_SCRIPT_EXTENSIONS_TEST_HPP
