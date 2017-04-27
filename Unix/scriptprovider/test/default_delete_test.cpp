#include "default_delete_test.hpp"


#include <cstdlib>
#include <default_delete.hpp>


using test::default_delete_test;


namespace
{


struct Counter
{
    /*ctor*/ Counter () { ++count; }
    /*dtor*/ ~Counter () { --count; }

    static int count;
};


/*static*/ int Counter::count = 0;


typedef util::default_delete<Counter> Deleter;
typedef util::default_delete<Counter[]> ArrayDeleter;


} // namespace <unnamed>


/*ctor*/
default_delete_test::default_delete_test ()
{
    add_test (MAKE_TEST (default_delete_test::test01));
    add_test (MAKE_TEST (default_delete_test::test02));
}


int
default_delete_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    Deleter deleter;
    if (0 != Counter::count)
    {
        rval = EXIT_FAILURE;
    }
    Counter* pCounter = new Counter;
    if (1 != Counter::count)
    {
        rval = EXIT_FAILURE;
    }
    deleter (pCounter);
    if (0 != Counter::count ||
        0 != pCounter)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
default_delete_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    ArrayDeleter deleter;
    if (0 != Counter::count)
    {
        rval = EXIT_FAILURE;
    }
    Counter* pCounter = new Counter[10];
    if (10 != Counter::count)
    {
        rval = EXIT_FAILURE;
    }
    deleter (pCounter);
    if (0 != Counter::count ||
        0 != pCounter)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
