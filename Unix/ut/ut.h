/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

//==============================================================================
//
// ut.h : provides helper macro/classes for unit-test framework
//
//==============================================================================

#ifndef _ut_ut_h
#define _ut_ut_h

#if !defined(TEST_BUILD)
# define TEST_BUILD
#endif

#include <common.h>
#include <string>
#include <cassert>
#include <cstdio>
#include <sstream>

#include <nits/base/nits.h>


// A constant 'false' value that can be used in a condition with getting the 
// 'conditional expression is constant' warning from Windows.
inline bool __UT_False() { return false; }
#define UT_FALSE __UT_False()

#define TEST_ASSERT(x) NitsAssert(x, PAL_T(""))

//==============================================================================
//
// NITS version of these macros:
//
//==============================================================================

# define UT_ASSERT(cond) \
    do \
    { \
       NitsAssertExA((cond) != 0, "", NitsHere(), NitsAutomatic); \
    } \
    while (__UT_False())

# define UT_ASSERT_EQUAL(v1, v2) \
    do \
    { \
       NitsAssertExA((v1) == (v2), "", NitsHere(), NitsAutomatic); \
    } \
    while (__UT_False())


# define UT_ASSERT_NOT_EQUAL(v1, v2) \
    do \
    { \
        NitsAssertExA((v1) != (v2), "", NitsHere(), NitsAutomatic); \
    } \
    while (__UT_False())

# define UT_ASSERT_FAILED_MSG(message) \
    do {\
        NitsAssertExA(0, message, NitsHere(), NitsAutomatic); \
    } \
    while (__UT_False())

# define UT_WARNING(text) \
    do { \
        NitsTraceExA(text, NitsHere(), NitsAutomatic); \
    } \
    while (__UT_False())

//==============================================================================
//
// Test framework functions:
//
//==============================================================================

namespace ut
{
    // internal part
    struct UnittestException 
    {
        std::string m_file;
	std::string m_function;
	std::string m_text;
	std::string m_testcase;
        int m_line;

        UnittestException(const char* file, int line, const char* function, 
	    const char* text ) : m_file(file), m_function(function), 
	    m_text(text), m_line(line)
        {
	}
    };

    INLINE int Assert(
        int cond,
        const char* condStr,
        const char* file,
        int line,
        const char* function)
    {
        if (!cond)
            throw(ut::UnittestException(file, line, function, condStr));
        return cond;
    }

    typedef void (*MODULE_TEST_CALLBACK) ();

    // interanl callbacks - used by macros
    void registerCallback(MODULE_TEST_CALLBACK pfn);
    unsigned int testStarted(const char* name);
    void testCompleted(const char* name);
    void testFailed(const UnittestException& ex);

    void testWarning(const char* text);

    bool testGetAttr(const std::string& name, std::string& value);
};

#include "utility.h"
#include "strutil.h"

#endif /* _ut_ut_h */
