#include "test_helper.hpp"


#include <iostream>


namespace test
{


void
test_suite::add_test_class (
    class_pair const& op)
{
    m_test_classes.push_back (op);
}


int
test_suite::run_all ()
{
    int result = EXIT_SUCCESS;
    for (std::vector<class_pair>::iterator pos = m_test_classes.begin (),
             endPos = m_test_classes.end ();
         pos != endPos;
         ++pos)
    {
        result = EXIT_SUCCESS == pos->first->run_all () ? result : EXIT_FAILURE;
    }
    return result;
}


int
test_suite::run_all_print (
    std::ostream& strm)
{
    int result = EXIT_SUCCESS;
    for (std::vector<class_pair>::iterator pos = m_test_classes.begin (),
             endPos = m_test_classes.end ();
         pos != endPos;
         ++pos)
    {
        result = EXIT_SUCCESS == pos->first->run_all_print (pos->second, strm)
            ? result : EXIT_FAILURE;
    }
    return result;
}


int
run_test (
    test_op op)
{
    int rval = EXIT_FAILURE;
    try
    {
        rval = op ();
    }
    catch (...)
    {
        // empty
    }
    return rval;
}


int
run_test_print (
    test_op op,
    char const* test_name,
    std::ostream& strm)
{
    int rval = EXIT_FAILURE;
    try
    {
        rval = op ();
        if (EXIT_SUCCESS == rval)
        {
            strm << test_name << ": passed." << std::endl;
        }
        else
        {
            strm << test_name << ": FAILED." << std::endl;
        }
    }
    catch (...)
    {
        strm << test_name << ": FAILED. (unhandled exception caught)"
             << std::endl;
    }
    return rval;
}


} // namespace test
