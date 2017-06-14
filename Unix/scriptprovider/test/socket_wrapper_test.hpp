// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_SOCKET_WRAPPER_TEST_HPP
#define INCLUDED_SOCKET_WRAPPER_TEST_HPP


#include "test_helper.hpp"

namespace test
{


class socket_wrapper_test : public test_class<socket_wrapper_test>
{
public:
    /*ctor*/ socket_wrapper_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
};


} // namespace test


#endif // INCLUDED_SOCKET_WRAPPER_TEST_HPP
