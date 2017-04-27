#ifndef INCLUDED_TEST_HELPER_HPP
#define INCLUDED_TEST_HELPER_HPP


#include <iosfwd>
#include <iostream>
#include <utility>
#include <vector>


namespace test
{


class test_class_base
{
public:
    virtual /*dtor*/ ~test_class_base () {}

    virtual int run_all () = 0;
    virtual int run_all_print (
        char const* class_name,
        std::ostream& strm) = 0;
};


template<typename T>
class test_class : public test_class_base
{
public:
    typedef int (T::*test_op)();
    typedef std::pair<test_op, char const*> test_pair;

    virtual /*dtor*/ ~test_class () {}

    void add_test (test_pair const& op);

    int run_test (test_op op);
    int run_test_print (
        test_op op,
        char const* test_name,
        std::ostream& strm);

    int run_all ();
    int run_all_print (
        char const* class_name,
        std::ostream& strm);


private:
    std::vector<test_pair> m_tests;
};


#define MAKE_TEST(op) std::make_pair (&op, #op)


class test_suite
{
public:
    typedef std::pair<test_class_base*, char const*> class_pair;

    void add_test_class (class_pair const& op);

    int run_all ();
    int run_all_print (std::ostream& strm);

private:
    std::vector<class_pair> m_test_classes;
};


typedef int (*test_op)();


int
run_test (
    test_op test);


int
run_test_print (
    test_op test,
    char const* test_name,
    std::ostream& strm);


template<typename T>
void
test_class<T>::add_test (
    test_pair const& op)
{
    m_tests.push_back (op);
}


template<typename T>
int
test_class<T>::run_test (
    test_op op)
{
    int rval = EXIT_FAILURE;
    try
    {
        rval = (static_cast<T*>(this)->*op) ();
    }
    catch (...)
    {
        // empty
    }
    return rval;
}


template<typename T>
int
test_class<T>::run_test_print (
    test_op op,
    char const* test_name,
    std::ostream& strm)
{
    int rval = EXIT_FAILURE;
    try
    {
        rval = (static_cast<T*>(this)->*op) ();
        if (EXIT_SUCCESS == rval)
        {
            strm << "    " << test_name << ": passed." << std::endl;
        }
        else
        {
            strm << "    " << test_name << ": FAILED." << std::endl;
        }
    }
    catch (...)
    {
        strm << "    " << test_name << ": FAILED. (unhandled exception caught)"
             << std::endl;
    }
    return rval;
}


template<typename T>
int
test_class<T>::run_all ()
{
    int rval = EXIT_SUCCESS;
    for (typename std::vector<test_pair>::iterator pos = m_tests.begin (),
             endPos = m_tests.end ();
         pos != endPos;
         ++pos)
    {
        rval = EXIT_SUCCESS == run_test (pos->first) ? rval : EXIT_FAILURE;
    }
    return rval;
}


template<typename T>
int
test_class<T>::run_all_print (
    char const* class_name,
    std::ostream& strm)
{
    int rval = EXIT_SUCCESS;
    strm << class_name << "..." << std::endl;
    for (typename std::vector<test_pair>::iterator pos = m_tests.begin (),
             endPos = m_tests.end ();
         pos != endPos;
         ++pos)
    {
        rval = EXIT_SUCCESS == run_test_print (pos->first, pos->second, strm)
            ? rval : EXIT_FAILURE;
    }
    if (EXIT_SUCCESS == rval)
    {
        strm << "..." << class_name << ": all tests passed." << std::endl;
    }
    else
    {
        strm << "..." << class_name << ": tests have FAILED." << std::endl;
    }
    return rval;
}


} // namespace test


#define TEST_NO_PRINT(test_op) test::run_test (test_op)
#define TEST_PRINT(test_op,strm) test::run_test_print (test_op, #test_op, strm)


#endif // INCLUDED_TEST_HELPER_HPP
