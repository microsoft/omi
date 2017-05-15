#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


#include "test_helper.hpp"
#include "traits_test.hpp"
#include "repeat_test.hpp"
#include "default_delete_test.hpp"
#include "internal_counted_ptr_test.hpp"
#include "unique_ptr_test.hpp"
#include "mi_type_test.hpp"
#include "mi_script_extensions_test.hpp"
#include "mi_memory_helper_test.hpp"
#include "socket_wrapper_test.hpp"
#include "shared_protocol_test.hpp"


int
passing_test ()
{
    return EXIT_SUCCESS;
}


int
failing_test ()
{
    return EXIT_FAILURE;
}


int
exception_test ()
{
    throw (EXIT_FAILURE);
    return EXIT_SUCCESS;
}


int
main ()
{
    int result = EXIT_SUCCESS;

    int seed = static_cast<int>(time (NULL));
    std::cout << "srand: " << seed << std::endl;
    srand (seed);

    test::test_suite test_suite;

    test::integral_constant_test integral_constant_test;
    test_suite.add_test_class (MAKE_TEST (integral_constant_test));
    test::is_lvalue_reference_test is_lvalue_reference_test;
    test_suite.add_test_class (MAKE_TEST (is_lvalue_reference_test));
    test::is_pointer_test is_pointer_test;
    test_suite.add_test_class (MAKE_TEST (is_pointer_test));
    test::is_reference_test is_reference_test;
    test_suite.add_test_class (MAKE_TEST (is_reference_test));
    test::conditional_test conditional_test;
    test_suite.add_test_class (MAKE_TEST (conditional_test));
    test::is_same_test is_same_test;
    test_suite.add_test_class (MAKE_TEST (is_same_test));
    test::remove_reference_test remove_reference_test;
    test_suite.add_test_class (MAKE_TEST (remove_reference_test));
    test::remove_const_test remove_const_test;
    test_suite.add_test_class (MAKE_TEST (remove_const_test));
    test::remove_volatile_test remove_volatile_test;
    test_suite.add_test_class (MAKE_TEST (remove_volatile_test));
    test::remove_cv_test remove_cv_test;
    test_suite.add_test_class (MAKE_TEST (remove_cv_test));
    test::is_integral_test is_integral_test;
    test_suite.add_test_class (MAKE_TEST (is_integral_test));
    test::is_floating_point_test is_floating_point_test;
    test_suite.add_test_class (MAKE_TEST (is_floating_point_test));
    test::is_arithmetic_test is_arithmetic_test;
    test_suite.add_test_class (MAKE_TEST (is_arithmetic_test));
    test::is_signed_test is_signed_test;
    test_suite.add_test_class (MAKE_TEST (is_signed_test));
    test::is_unsigned_test is_unsigned_test;
    test_suite.add_test_class (MAKE_TEST (is_unsigned_test));
    test::repeat_test repeat_test;
    test_suite.add_test_class (MAKE_TEST (repeat_test));
    test::default_delete_test default_delete_test;
    test_suite.add_test_class (MAKE_TEST (default_delete_test));
    test::internal_counted_ptr_test internal_counted_ptr_test;
    test_suite.add_test_class (MAKE_TEST (internal_counted_ptr_test));
    test::unique_ptr_test unique_ptr_test;
    test_suite.add_test_class (MAKE_TEST (unique_ptr_test));
    test::mi_type_test mi_type_test;
    test_suite.add_test_class (MAKE_TEST (mi_type_test));
    test::mi_script_extensions_test mi_script_extensions_test;
    test_suite.add_test_class (MAKE_TEST (mi_script_extensions_test));

    test::mi_memory_helper_test mi_memory_helper_test;
    test_suite.add_test_class (MAKE_TEST (mi_memory_helper_test));

    test::socket_wrapper_test socket_wrapper_test;
    test_suite.add_test_class (MAKE_TEST (socket_wrapper_test));
    test::shared_protocol_test shared_protocol_test;
    test_suite.add_test_class (MAKE_TEST (shared_protocol_test));

    //result = test_suite.run_all ();
    result = test_suite.run_all_print (std::cout);

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "*****************" << std::endl;
    }
    if (EXIT_SUCCESS == result)
    {
        std::cout << std::endl << "All tests passed" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Some tests FAILED" << std::endl << std::endl;  
    }
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "*****************" << std::endl;
    }

    return result;
}
