// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_DEFAULT_DELETE_TEST_HPP
#define INCLUDED_DEFAULT_DELETE_TEST_HPP


#include "test_helper.hpp"


namespace test
{


class default_delete_test : public test_class<default_delete_test>
{
public:
    /*ctor*/ default_delete_test ();
    
    int test01 ();
    int test02 ();
};


} // namespace test


#endif // INCLUDED_DEFAULT_DELETE_TEST_HPP
