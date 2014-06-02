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

#include <vector>
#include <algorithm>
#include <ut/ut.h>
#include <base/credcache.h>

using namespace std;
using namespace ut;

//#define ENABLE_PRINT

// every test needs to start with clean credcache in the test body
// reason is once fault injection runs with nits, it runs the same 
// body multiple times and that causes the credcache not to start clean
// from the fault sim iteration start
NitsTest(TestCredUserAllowed)
{
    CredCache_Clean();

    // First check that user is not allowed (not added yet)
    UT_ASSERT(CredCache_CheckUser("user", "abc") < 0);

    CredCache_PutUser("user", "abc");

    // Verify that user is in cache now
    UT_ASSERT(CredCache_CheckUser("user", "abc") == 0);
}
NitsEndTest

NitsTest(TestCredInvalidPassword)
{
    CredCache_Clean();

    // First check that user is not allowed (not added yet)
    UT_ASSERT(CredCache_CheckUser("user", "abc") < 0);

    CredCache_PutUser("user", "abc");

    // Verify invalid passwords
    UT_ASSERT(CredCache_CheckUser("user", "") < 0);
    UT_ASSERT(CredCache_CheckUser("user", "Abc") < 0);
    UT_ASSERT(CredCache_CheckUser("user", "abc ") < 0);
    UT_ASSERT(CredCache_CheckUser("user", "-abc") < 0);
}
NitsEndTest

NitsTest(TestCredSeveralUsers)
{
    CredCache_Clean();

    CredCache_PutUser("user1", "abc1");
    CredCache_PutUser("user2", "abc2");
    CredCache_PutUser("user3", "abc3");
    CredCache_PutUser("user4", "abc4");

    // Verify that users are in cache now
    UT_ASSERT(CredCache_CheckUser("user1", "abc1") == 0);
    UT_ASSERT(CredCache_CheckUser("user2", "abc2") == 0);
    UT_ASSERT(CredCache_CheckUser("user3", "abc3") == 0);
    UT_ASSERT(CredCache_CheckUser("user4", "abc4") == 0);
}
NitsEndTest

NitsTest(TestCredExpiration)
{
    CredCache_Clean();

    CredCache_PutUser("user1", "abc1");

    CredCache_SetExpirationTimeout(1);

    sleep_ms(1);

    // Verify that users expired
    UT_ASSERT(CredCache_CheckUser("user1", "abc1") < 0);

    /* Restore default one */
    CredCache_SetExpirationTimeout(0);
}
NitsEndTest

NitsTest(TestCredOldestOverwritten)
{
    CredCache_Clean();

    /* create oldest item */
    CredCache_PutUser("oldest", "oldest");

    UT_ASSERT(CredCache_CheckUser("oldest", "oldest") == 0);

    /* make it older than the rest */
    sleep_ms(1);

    for (int i = 0; i < 64; i++)
    {
        char user[64];

        sprintf(user, "user%d", i);
        // Add new user and verify it's added
        CredCache_PutUser(user, user);
        UT_ASSERT(CredCache_CheckUser(user, user) == 0);
    }

    // Verify that users expired
    UT_ASSERT(CredCache_CheckUser("oldest", "oldest") < 0);
}
NitsEndTest

