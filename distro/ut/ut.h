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

#include <common.h>
#include <string>
#include <cassert>
#include <cstdio>
#include <sstream>

#if !defined(TEST_BUILD)
# define TEST_BUILD
#endif

#if defined(_MSC_VER)
# define CONFIG_ENABLE_NITS
#endif

#if defined(CONFIG_ENABLE_NITS)
# include <../nits/base/nits.h>
#endif

// A constant 'false' value that can be used in a condition with getting the
// 'conditional expression is constant' warning from from Windows.
inline bool __UT_False() { return false; }
#define UT_FALSE __UT_False()

#if !defined(CONFIG_ENABLE_NITS)
# define NitsHere() 0
# define NitsIsActivated() 0
# define NitsTraceExA(P1, P2, P3)
# define NitsTraceExW(P1, P2, P3)
# define NitsTest(NAME) static void NAME() {
# define NitsEndTest }
# define NitsCallSite int
# define NitsAutomatic 0
# define NitsAssertExA(COND, P2, P3, P4) \
    ut::Assert(COND, #COND, __FILE__, __LINE__, __FUNCTION__)
# define NitsAssertExW(COND, P2, P3, P4) \
    ut::Assert(COND, #COND, __FILE__, __LINE__, __FUNCTION__)
#endif

//==============================================================================
//
// NITS version of these macros:
//
//==============================================================================

#if defined(CONFIG_ENABLE_NITS)

# define UT_ASSERT(cond) \
    do \
    { \
        if (NitsIsActivated()) \
            NitsAssertExA((cond) != 0, "", NitsHere(), NitsAutomatic); \
        else if(!(cond))  \
	    throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
		#cond)); \
    } \
    while (__UT_False())

# define UT_ASSERT_EQUAL(v1, v2) \
    do \
    { \
        if (NitsIsActivated()) \
            NitsAssertExA((v1) == (v2), "", NitsHere(), NitsAutomatic); \
        else if((v1) != (v2)) \
        {  \
            std::stringstream ss; \
            ss << #v1;  \
            ss << " == ";   \
            ss << #v2;      \
            ss << "; {";    \
            ss << v1;       \
            ss << " == ";   \
            ss << v2;       \
            ss << "}";      \
\
	        throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
		    ss.str().c_str())); \
        }\
    } \
    while (__UT_False())


# define UT_ASSERT_NOT_EQUAL(v1, v2) \
    do \
    { \
        if (NitsIsActivated()) \
            NitsAssertExA((v1) != (v2), "", NitsHere(), NitsAutomatic); \
        else if((v1) == (v2)) \
        {  \
            std::stringstream ss; \
            ss << #v1;  \
            ss << " != ";   \
            ss << #v2;      \
            ss << "; {";    \
            ss << v1;       \
            ss << " != ";   \
            ss << v2;       \
            ss << "}";      \
\
	        throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
		    ss.str().c_str())); \
        }\
    } \
    while (__UT_False())

# define UT_TEST(test) \
    if (NitsIsActivated()) \
    { \
        struct BodyAdapter {static void Run(TestSystem::Switch &) { test(); }}; \
        struct CleanupAdapter {static void Run(TestSystem::Switch &) { cleanup(); }}; \
        struct SetupAdapter {static void Run(TestSystem::Switch &s) { \
            s.SetCleanup(CleanupAdapter::Run); \
            setUp(); \
        }}; \
        TestSystem::Test *fixture##test = new TestSystem::Test(stringify(test), SetupAdapter::Run, BodyAdapter::Run); \
        MI_UNREFERENCED_PARAMETER(fixture##test);\
    } \
    else \
        __UT_TEST(#test, setUp, cleanup, test)

# define UT_ASSERT_FAILED_MSG(message) \
    do {\
        if (NitsIsActivated()) \
            NitsAssertExA(0, message, NitsHere(), NitsAutomatic); \
        else \
        throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__, (message))); \
    } \
    while (__UT_False())

# define UT_ENTRY_POINT(FUNC) static ut::TestRegister __entry(FUNC);

# define UT_WARNING(text) \
    do { \
        if (NitsIsActivated()) \
            NitsTraceExA(text, NitsHere(), NitsAutomatic); \
        else \
        ut::testWarning(text); \
    } \
    while (__UT_False())

#endif /* defined(CONFIG_ENABLE_NITS) */

//==============================================================================
//
// UT version of these macros:
//
//==============================================================================

#if !defined(CONFIG_ENABLE_NITS)

# define UT_ASSERT(cond) \
    do \
    { \
        if(!(cond))  \
	    throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
		#cond)); \
    } \
    while (__UT_False())

# define UT_ASSERT_EQUAL(v1, v2) \
    do \
    { \
        if((v1) != (v2)) \
        {  \
            std::stringstream ss; \
            ss << #v1;  \
            ss << " == ";   \
            ss << #v2;      \
            ss << "; {";    \
            ss << v1;       \
            ss << " == ";   \
            ss << v2;       \
            ss << "}";      \
	    throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
                ss.str().c_str())); \
        }\
    } \
    while (__UT_False())


# define UT_ASSERT_NOT_EQUAL(v1, v2) \
    do \
    { \
        if((v1) == (v2)) \
        {  \
            std::stringstream ss; \
            ss << #v1;  \
            ss << " != ";   \
            ss << #v2;      \
            ss << "; {";    \
            ss << v1;       \
            ss << " != ";   \
            ss << v2;       \
            ss << "}";      \
            throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__,  \
                ss.str().c_str())); \
        }\
    } \
    while (__UT_False())

# define UT_TEST(test) \
    __UT_TEST(#test, setUp, cleanup, test)

# define UT_ASSERT_FAILED_MSG(message) \
    do \
    { \
        throw(ut::UnittestException(__FILE__, __LINE__, __FUNCTION__, \
            (message))); \
    } \
    while (__UT_False())

# define UT_ENTRY_POINT(FUNC) static ut::TestRegister __entry(FUNC);

# define UT_WARNING(text) \
    do \
    { \
        ut::testWarning(text); \
    } \
    while (__UT_False())

#endif /* !defined(CONFIG_ENABLE_NITS) */

void __UT_TEST(
    const char* testName,
    void (*setUp)(),
    void (*cleanUp)(),
    void (*test)());

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

    ///////////////////////////////
    // registration helper
    struct TestRegister
    {
        TestRegister(MODULE_TEST_CALLBACK pfn)
        {
#if defined(CONFIG_ENABLE_NITS)
            if (NitsIsActivated())
            {
                pfn();
                return;
            }
#endif /* defined(CONFIG_ENABLE_NITS) */

            registerCallback(pfn);
        }
    };

    bool testGetAttr(const std::string& name, std::string& value);
};

#include "utility.h"
#include "strutil.h"

#endif /* _ut_ut_h */
