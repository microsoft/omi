// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "getopt_test.hpp"


#include <base/omigetopt.h>


using test::getopt_test;


namespace
{
} // namespace (unnamed)


namespace test
{


/*ctor*/
getopt_test::getopt_test ()
{
    add_test (MAKE_TEST (getopt_test::test01));
    add_test (MAKE_TEST (getopt_test::test02));
    add_test (MAKE_TEST (getopt_test::test03));
    add_test (MAKE_TEST (getopt_test::test04));
    add_test (MAKE_TEST (getopt_test::test05));
    add_test (MAKE_TEST (getopt_test::test06));
    add_test (MAKE_TEST (getopt_test::test07));
    add_test (MAKE_TEST (getopt_test::test08));
    add_test (MAKE_TEST (getopt_test::test09));
    add_test (MAKE_TEST (getopt_test::test10));
}


int
getopt_test::test01 ()
{
    int argc = 0;
    char const* argv[] = {
    };
    char const* opts[] = {
    };
    int rval = EXIT_SUCCESS;
    GetOptState state = GETOPTSTATE_INITIALIZER;
    if (1 != GetOpt (&argc, argv, opts, &state))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
getopt_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test06 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test07 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test08 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test09 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
getopt_test::test10 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


} // namespace test
