// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "repeat_test.hpp"


#include <cstdlib>
#include <repeat.hpp>


using test::repeat_test;


#define TEST_SIZE 50
#define _INT(X) static int const value##X (X);
#define _VALUES1(X) X,
#define _VALUES2(X) values[X] = X;


/*ctor*/
repeat_test::repeat_test ()
{
    add_test (MAKE_TEST (repeat_test::test01));
    add_test (MAKE_TEST (repeat_test::test02));
    add_test (MAKE_TEST (repeat_test::test03));
}


int
repeat_test::test01 ()
{
    REPEAT (5, _INT)
    int rval = EXIT_SUCCESS;
    if (0 != value0 ||
        1 != value1 ||
        2 != value2 ||
        3 != value3 ||
        4 != value4)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
repeat_test::test02 ()
{
    int values[] = {
        REPEAT (TEST_SIZE, _VALUES1)
    };

    int rval = EXIT_SUCCESS;
    for (int i = 0;
         rval == EXIT_SUCCESS &&
             i < TEST_SIZE;
         ++i)
    {
        if (i != values[i])
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
repeat_test::test03 ()
{
    int values[TEST_SIZE];    
    REPEAT (TEST_SIZE, _VALUES2)

    int rval = EXIT_SUCCESS;
    for (int i = 0;
         rval == EXIT_SUCCESS &&
             i < TEST_SIZE;
         ++i)
    {
        if (i != values[i])
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}
