#include "mi_script_extensions_test.hpp"


#include <cstdlib>
#include <mi_script_extensions.hpp>


using test::mi_script_extensions_test;


namespace
{


template<typename T, size_t N>
size_t
card (T const (&)[N])
{
    return N;
}


MI_Char const* const METHOD_NAME_0 = "MethodName0";

MI_MethodDecl const METHOD_0 = {
    0,
    0,
    METHOD_NAME_0,
    NULL,
    0,
    NULL,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL
};


MI_Char const* const METHOD_NAME_1 = "MethodName1";

MI_MethodDecl const METHOD_1 = {
    0,
    0,
    METHOD_NAME_1,
    NULL,
    0,
    NULL,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL
};


MI_Char const* const METHOD_NAME_2 = "MethodName2";

MI_MethodDecl const METHOD_2 = {
    0,
    0,
    METHOD_NAME_2,
    NULL,
    0,
    NULL,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL
};


MI_MethodDecl const* METHODS[] = {
    &METHOD_0,
    &METHOD_1,
    &METHOD_2,
};


MI_Char const* const CLASS_NAME_0 = "ClassName0";
MI_Char const* const CLASS_NAME_1 = "ClassName1";
MI_Char const* const CLASS_NAME_2 = "ClassName2";


} // namespace <unnamed>


/*ctor*/
mi_script_extensions_test::mi_script_extensions_test ()
{
    memset (&CLASS_0, 0, sizeof (CLASS_0));
    CLASS_0.name = CLASS_NAME_0;
    memset (&CLASS_1, 0, sizeof (CLASS_1));
    CLASS_1.name = CLASS_NAME_1;
    CLASS_1.methods = METHODS;
    CLASS_1.numMethods = card (METHODS);
    memset (&CLASS_2, 0, sizeof (CLASS_2));
    CLASS_2.name = CLASS_NAME_2;
    CLASSES[0] = &CLASS_0;
    CLASSES[1] = &CLASS_1;
    CLASSES[2] = &CLASS_2;
    memset (&SCHEMA, 0, sizeof (SCHEMA));
    SCHEMA.classDecls = CLASSES;
    SCHEMA.numClassDecls = card (CLASSES);
    add_test (MAKE_TEST (mi_script_extensions_test::test01));
    add_test (MAKE_TEST (mi_script_extensions_test::test02));
    add_test (MAKE_TEST (mi_script_extensions_test::test03));
}


int
mi_script_extensions_test::test01 ()
{
    // test MI_ClassDeclEx
    int rval = EXIT_SUCCESS;
    if (0 != CLASS_0.functionTableFlags ||
        NULL != CLASS_0.owningClassName)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_script_extensions_test::test02 ()
{
    // test findClassDecl
    int rval = EXIT_SUCCESS;
    if (&CLASS_0 != findClassDecl (CLASS_NAME_0, &SCHEMA) ||
        &CLASS_1 != findClassDecl (CLASS_NAME_1, &SCHEMA) ||
        &CLASS_2 != findClassDecl (CLASS_NAME_2, &SCHEMA))
    {
        rval = EXIT_FAILURE;
    }
    if (NULL != findClassDecl ("FakeName", &SCHEMA))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_script_extensions_test::test03 ()
{
    // test findMethodDecl
    int rval = EXIT_SUCCESS;
    if (&METHOD_0 != findMethodDecl (METHOD_NAME_0, &CLASS_1) ||
        &METHOD_1 != findMethodDecl (METHOD_NAME_1, &CLASS_1) ||
        &METHOD_2 != findMethodDecl (METHOD_NAME_2, &CLASS_1))
    {
        rval = EXIT_FAILURE;
    }
    if (NULL != findMethodDecl ("FakeName", &CLASS_1))
    {
        rval = EXIT_FAILURE;
    }
    if (NULL != findMethodDecl (METHOD_NAME_0, &CLASS_0) ||
        NULL != findMethodDecl (METHOD_NAME_1, &CLASS_0) ||
        NULL != findMethodDecl (METHOD_NAME_2, &CLASS_0))
    {
        rval = EXIT_FAILURE;
    }
    if (NULL != findMethodDecl ("FakeName", &CLASS_0))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
