#ifndef INCLUDED_REPEAT_TEST_HPP
#define INCLUDED_REPEAT_TEST_HPP


#include "test_helper.hpp"


namespace test
{


class repeat_test : public test_class<repeat_test>
{
public:
    /*ctor*/ repeat_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


} // namespace test


#endif // INCLUDED_REPEAT_TEST_HPP
