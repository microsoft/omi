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
#include <set>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include "utils.h"
#include <protocol/protocol.h>
#include <sock/sock.h>
#include <base/base.h>
#include <base/paths.h>
#include <pal/format.h>
#include <base/user.h>
#include <omiclient/client.h>

using namespace std;
using namespace mi;

#if defined(BROKEN)    
inline std::ostream& operator << (std::ostream& ss, const String& str)
{
    ss << str.Str();
    return ss;
}

BEGIN_EXTERNC
static void _StrandTestAck( _In_ Strand* self) 
{
    // do nothing
}

static void _StrandTestFinished( _In_ Strand* self) 
{
    // do nothing
}

static StrandFT strandUserFT1 = { 
        NULL, 
        NULL, 
        _StrandTestAck, 
        NULL, 
        NULL, 
        _StrandTestFinished,
        NULL,
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        NULL };
        
static Strand simpleResult;
END_EXTERNC

static ProtocolSocketAndBase* s_protocol;

NitsSetup(TestAuthSetup)
{
    EnterStrandState strandEnterState;
    
    /* Enable auth so we can verify pre-conditions */
    IgnoreAuthCalls(0);

    // these tests can be executed only when unit-test is 'root'
    // and user omi exists 
    if (0 != IsRoot())
    {
        UT_WARNING("auth tests skipped - root level required");
        return;
    }

    if (0 != AuthenticateUser(USER, PASSWORD))
    {
        UT_WARNING("auth tests skipped - user " USER "/" PASSWORD " not found");
        return;
    }

    Sock_Start();

    Strand_Init( &simpleResult, &strandUserFT1, STRAND_FLAG_ENTERSTRAND, NULL );

    StartServerAndConnect(false, &simpleResult, &s_protocol);
}
NitsEndSetup

NitsCleanup(TestAuthSetup)
{
    StopServerAndDisconnect(&simpleResult, &s_protocol);
    Sock_Stop();
}
NitsEndCleanup

struct ProvInfo
{
    Uint32  pid_user, pid_requestor, pid_inproc;
    String user_user, user_requestor, user_inproc;
    String group_user, group_requestor, group_inproc;
};

static void _GetProvInfo(
    Client& c,
    ProvInfo& info)
{
    /* enumerate instances and return values in 'info' struct
        inproc/requestor/user */

    const Uint64 TIMEOUT = 15 * 1000 * 1000;
    Array<DInstance> instances_user, instances_inproc, instances_requestor;
    MI_Result result;

    UT_ASSERT(c.EnumerateInstances(ZT("oop/user/test/cpp"), ZT("x_numberworld"), true,
        TIMEOUT, instances_user, String(), String(), result));
    UT_ASSERT_EQUAL(result, MI_RESULT_OK);

    UT_ASSERT(c.EnumerateInstances(ZT("oop/requestor/test/cpp"), ZT("x_numberworld"), true,
        TIMEOUT, instances_requestor, String(), String(), result));
    UT_ASSERT_EQUAL(result, MI_RESULT_OK);

    UT_ASSERT(c.EnumerateInstances(ZT("test/cpp"), ZT("x_numberworld"), true,
        TIMEOUT, instances_inproc, String(), String(), result));
    UT_ASSERT_EQUAL(result, MI_RESULT_OK);

    UT_ASSERT_EQUAL(instances_user.GetSize(), 1);
    UT_ASSERT_EQUAL(instances_requestor.GetSize(), 1);
    UT_ASSERT_EQUAL(instances_inproc.GetSize(), 1);


    // extract pid, user, group from all and compare
    bool null, key;

    UT_ASSERT( instances_user[0].GetUint32(ZT("pid"), info.pid_user, null, key));
    UT_ASSERT( instances_requestor[0].GetUint32(ZT("pid"), info.pid_requestor, null, key));
    UT_ASSERT( instances_inproc[0].GetUint32(ZT("pid"), info.pid_inproc, null, key));

    UT_ASSERT( instances_user[0].GetString(ZT("user"), info.user_user, null, key));
    UT_ASSERT( instances_requestor[0].GetString(ZT("user"), info.user_requestor, null, key));
    UT_ASSERT( instances_inproc[0].GetString(ZT("user"), info.user_inproc, null, key));

    UT_ASSERT( instances_user[0].GetString(ZT("group"), info.group_user, null, key));
    UT_ASSERT( instances_requestor[0].GetString(ZT("group"), info.group_requestor, null, key));
    UT_ASSERT( instances_inproc[0].GetString(ZT("group"), info.group_inproc, null, key));

    /*if (result == MI_RESULT_OK)
    {
        for (Uint32 i = 0; i < instances_user.GetSize(); i++)
            instances_user[i].Print();
    }
    if (result == MI_RESULT_OK)
    {
        for (Uint32 i = 0; i < instances_requestor.GetSize(); i++)
            instances_requestor[i].Print();
    }
    if (result == MI_RESULT_OK)
    {
        for (Uint32 i = 0; i < instances_inproc.GetSize(); i++)
            instances_inproc[i].Print();
    }*/
}

NitsTestWithSetup(TestAuthExplicitOOPModes, TestAuthSetup)
{
    /* use explicit credentials for pre-defined user */
    Client c;
    ProvInfo info;

    const Uint64 TIMEOUT = 15 * 1000 * 1000;

    TChar sockfile[PAL_MAX_PATH_SIZE];
    TcsStrlcpy(sockfile, OMI_GetPath(ID_SOCKETFILE), sizeof(sockfile));

    UT_ASSERT(c.Connect(sockfile, USER_Z, PASSWORD_Z, TIMEOUT));

    _GetProvInfo(c, info);

    // Expecting results:
    // user/requestor should be the same (omi as user), in-proc expected to be root
    UT_ASSERT_EQUAL(info.user_user, info.user_requestor);
    UT_ASSERT_EQUAL(info.group_user, info.group_requestor);
    UT_ASSERT_EQUAL(info.pid_user, info.pid_requestor);

    UT_ASSERT_NOT_EQUAL(info.user_user, info.user_inproc);
    UT_ASSERT_NOT_EQUAL(info.group_user, info.group_inproc);
    UT_ASSERT_NOT_EQUAL(info.pid_user, info.pid_inproc);
}
NitsEndTest

NitsTestWithSetup(TestAuthImplicitOOPModes, TestAuthSetup)
{
    /* use explicit credentials for pre-defined user */
    Client c;
    ProvInfo info;

    const Uint64 TIMEOUT = 15 * 1000 * 1000;

    TChar sockfile[PAL_MAX_PATH_SIZE];
    TcsStrlcpy(sockfile, OMI_GetPath(ID_SOCKETFILE), sizeof(sockfile));

    UT_ASSERT(c.Connect(sockfile, ZT(""), ZT(""), TIMEOUT));

    _GetProvInfo(c, info);

    // Expecting results:
    // user should be omi, 
    // requestor/in-proc expected to be root
    // all pids are dufferent
    UT_ASSERT_NOT_EQUAL(info.user_user, info.user_requestor);
    UT_ASSERT_NOT_EQUAL(info.group_user, info.group_requestor);
    UT_ASSERT_NOT_EQUAL(info.pid_user, info.pid_requestor);

    UT_ASSERT_EQUAL(info.user_requestor, info.user_inproc);
    UT_ASSERT_EQUAL(info.group_requestor, info.group_inproc);
    UT_ASSERT_NOT_EQUAL(info.pid_user, info.pid_inproc);
    UT_ASSERT_NOT_EQUAL(info.pid_requestor, info.pid_inproc);
}
NitsEndTest

NitsTestWithSetup(TestAuthInvalidPassword, TestAuthSetup)
{
    /* use explicit credentials for pre-defined user */
    Client c;

    const Uint64 TIMEOUT = 15 * 1000 * 1000;
    string socketFile = OMI_GetPath(ID_SOCKETFILE);

    Array<DInstance> instances_user;
    MI_Result result = MI_RESULT_OK;

    TChar sockfile[PAL_MAX_PATH_SIZE];
    TcsStrlcpy(sockfile, OMI_GetPath(ID_SOCKETFILE), sizeof(sockfile));

    bool b = c.Connect(sockfile, USER_Z, ZT("?"), TIMEOUT);

    //printf("b %d\n", (int)b);

    b = b && c.EnumerateInstances(ZT("oop/user/test/cpp"), ZT("x_numberworld"), true, TIMEOUT, instances_user, String(), String(), result);

    // connect maybe ok, since it only tracks socket connection, but enumerate must fail

    // printf("res %d, size %d\n", result, instances_user.GetSize());

    UT_ASSERT(!b);
    UT_ASSERT(instances_user.GetSize() == 0);
}
NitsEndTest

NitsTestWithSetup(TestAuthNoPassword, TestAuthSetup)
{
    /* use explicit credentials for pre-defined user */
    Client c;

    const Uint64 TIMEOUT = 15 * 1000 * 1000;
    string socketFile = OMI_GetPath(ID_SOCKETFILE);

    Array<DInstance> instances_user;
    MI_Result result = MI_RESULT_OK;

    TChar sockfile[PAL_MAX_PATH_SIZE];
    TcsStrlcpy(sockfile, OMI_GetPath(ID_SOCKETFILE), sizeof(sockfile));

    bool b = c.Connect(sockfile, USER_Z, ZT(""), TIMEOUT);

    //printf("b %d\n", (int)b);

    b = b && c.EnumerateInstances(ZT("oop/user/test/cpp"), ZT("x_numberworld"), true, TIMEOUT, instances_user, String(), String(), result);

    // connect maybe ok, since it only tracks socket connection, but enumerate must fail

    // printf("res %d, size %d\n", result, instances_user.GetSize());

    UT_ASSERT(!b);
    UT_ASSERT(instances_user.GetSize() == 0);
}
NitsEndTest


#endif

