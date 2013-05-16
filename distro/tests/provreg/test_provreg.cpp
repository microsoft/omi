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

#include <ut/ut.h>
#include <provreg/provreg.h>
#include <provreg/regfile.h>
#include <base/strings.h>
#include <base/dir.h>
#include <base/paths.h>
#include <algorithm>
#include <io/io.h>

//#define ENABLE_PRINT

static char TEMP_FILE[MAX_PATH_SIZE];

using namespace std;

static FILE* outStream = NULL;

static void setUp()
{
    Strlcpy(TEMP_FILE, GetPath(ID_TMPDIR), sizeof(TEMP_FILE));
    Strlcat(TEMP_FILE, "/test_temp.tmp", sizeof(TEMP_FILE));

#if defined(ENABLE_PRINT)
    outStream = stdout;
#else
    outStream = Fopen(NULL_FILE, "w");
#endif
}

static void cleanup()
{
#if defined(ENABLE_PRINT)
    outStream = NULL;
#else
    fclose(outStream);
    outStream = NULL;
#endif
    ut::removeIfExist( TEMP_FILE );
}

#if 0
static void TestProvReg()
{
    /* Relative to 'unittest' directory */
    std::string path = ut::findSampleFile(0,"","../provreg/tests/omiregister.conf");
    ProvReg reg;
    MI_Result r;
    ProvRegEntry* p;
    size_t index = 0;

    /* Load the registrations */
    r = ProvReg_Init(&reg, path.c_str());

    if (r != MI_RESULT_OK)
    {
        fprintf(stdout, "failed to open: %s\n", path.c_str());
        UT_ASSERT_FAILED_MSG("failed to open register.conf");
    }

    /* Check the registrations */
    for (p = reg.head; p; p = p->next, index++)
    {
        switch (index)
        {
            case 0:
            {
                UT_ASSERT(p->provInterface == PROV_INTERFACE_STATIK);
                UT_ASSERT(Zcmp(p->nameSpace, ZT("root/test")) == 0);
                UT_ASSERT(Zcmp(p->className, ZT("Dog")) == 0);
                UT_ASSERT(strcmp(p->libraryName, "MyProvider") == 0);
                break;
            }
            case 1:
            {
                UT_ASSERT(p->provInterface == PROV_INTERFACE_STATIK);
                UT_ASSERT(Zcmp(p->nameSpace, ZT("root/test")) == 0);
                UT_ASSERT(Zcmp(p->className, ZT("Cat")) == 0);
                UT_ASSERT(strcmp(p->libraryName, "MyProvider") == 0);
                break;
            }
            case 2:
            {
                UT_ASSERT(p->provInterface == PROV_INTERFACE_STATIK);
                UT_ASSERT(Zcmp(p->nameSpace, ZT("root/test")) == 0);
                UT_ASSERT(Zcmp(p->className, ZT("Bird")) == 0);
                UT_ASSERT(strcmp(p->libraryName, "MyProvider") == 0);
                break;
            }
            default:
                UT_ASSERT_FAILED_MSG("unexpected branch");
        }
    }

    ProvReg_Dump(&reg, outStream);

    // Find a provider for the given class.
    {
        const ProvRegEntry* entry;
        MI_Result findResult;
        
        entry = ProvReg_FindProviderForClass(&reg, ZT("root/test"), 
            ZT("Bird"), &findResult);
        UT_ASSERT(entry != NULL);

        entry = ProvReg_FindProviderForClass(&reg, ZT("blah"), ZT("blah"), &findResult);
        UT_ASSERT(entry == NULL);
    }

    // check derived classes
    vector<ut::String>  res;
    ProvRegPosition pos;
    MI_ConstString derived = 0;

    r = ProvReg_BeginClasses( &reg, ZT("root/test"), ZT("Animal"), MI_TRUE, &pos );

    UT_ASSERT (MI_RESULT_OK == r);

    for (;;)
    {
        MI_Boolean done;
        r = ProvReg_NextClass( &pos, &derived, &done);

        if (done)
            break;

        UT_ASSERT (MI_RESULT_OK == r);
        res.push_back( derived );
    }

    r = ProvReg_EndClasses(&pos);
    UT_ASSERT(MI_RESULT_OK == r);


    std::sort< vector< ut::String >::iterator >(res.begin(), res.end());

    vector<ut::String>  expected_res;
    expected_res.push_back(ZT("Bird"));
    expected_res.push_back(ZT("Cat"));
    expected_res.push_back(ZT("Dog"));

    UT_ASSERT(expected_res == res);

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestProvRegInvalidConfigFile()
{
    ProvReg reg;
    MI_Result r;

    /* Load the registrations */
    r = ProvReg_Init(&reg, "non-exisiting-file");

    UT_ASSERT (MI_RESULT_OPEN_FAILED == r);
}
#endif

#if 0
static void VerifyInheritanceChain(ProvReg* reg, MI_ConstString ns, MI_ConstString base, MI_Boolean deep, MI_ConstString expected)
{
    // check derived classes
    vector<ut::String>  res;
    ProvRegPosition pos;
    MI_ConstString derived = 0;

    MI_Result r = ProvReg_BeginClasses( reg, ns, base, deep, &pos );

    UT_ASSERT (MI_RESULT_OK == r);

    for (;;)
    {
        MI_Boolean done;
        r = ProvReg_NextClass( &pos, &derived, &done);

        if (done)
            break;

        UT_ASSERT (MI_RESULT_OK == r);
        res.push_back( derived );
    }

    r = ProvReg_EndClasses(&pos);
    UT_ASSERT(MI_RESULT_OK == r);

    std::sort< vector< ut::String >::iterator >(res.begin(), res.end());

    vector<ut::String>  expected_res;
    ut::StringToArray(expected, expected_res);
    std::sort< vector< ut::String >::iterator >(expected_res.begin(), expected_res.end());

    if(expected_res != res)
    {
        UT_ASSERT_FAILED_MSG(string(string("actual result is different from expected: expected {") + 
            ut::StrToChar(ut::ArrayToString(expected_res)) +
            "} but actual is {" +
            ut::StrToChar(ut::ArrayToString(res)) +
            "}").c_str() );
    }
}
#endif

#if 0
static void VerifyAssociationChain(ProvReg* reg, MI_ConstString ns, MI_ConstString cn, MI_ConstString assocClass, MI_ConstString resultClass, MI_ConstString expected)
{
    // check derived classes
    vector<ut::String>  res;
    ProvRegAssocPosition pos;
    MI_ConstString nextClass = 0;

    MI_Result r = ProvReg_BeginAssocClasses( reg, ns, cn, assocClass, resultClass, &pos );

    UT_ASSERT (MI_RESULT_OK == r);

    for (;;)
    {
        MI_Boolean done;
        r = ProvReg_NextAssocClass( &pos, &nextClass, &done);

        if (done)
            break;

        UT_ASSERT (MI_RESULT_OK == r);
        res.push_back( nextClass );
    }

    r = ProvReg_EndAssocClasses(&pos);
    UT_ASSERT(MI_RESULT_OK == r);

    std::sort< vector< ut::String >::iterator >(res.begin(), res.end());

    vector<ut::String>  expected_res;
    ut::StringToArray(expected, expected_res);
    std::sort< vector< ut::String >::iterator >(expected_res.begin(), expected_res.end());

    if(expected_res != res)
    {
        UT_ASSERT_FAILED_MSG(string(string("actual result is different from expected: expected {") + 
            ut::StrToChar(ut::ArrayToString(expected_res)) +
            "} but actual is {" +
            ut::StrToChar(ut::ArrayToString(res)) +
            "}").c_str() );
    }
}
#endif

#if 0
static void TestClassInheritanceTreeMultipleDerived()
{
    const char* content = "# sample config entry\n"
        "statik:namespace           :Dog,Animal,Base    :provider_name\n"
        "statik:another_namespace   :Dog,Animal,Base    :provider_name\n"
        "statik:another_namespace   :Programmer,Person,Base    :software_provider_name\n"
        "statik:another_namespace   :CEO,Manager,Person,Base    :executive_provider_name\n"
        "statik:another_namespace   :stand_alone_Base    :one_more_provider_name\n"
        ;

    // verify inheritance chains:
    // Base -> Dog,Animal,Person,Programmer,Manager,CEO
    // Animal -> Dog
    // Person -> Programmer, Manager, CEO
    // Manager-> CEO
    // CEO, Programmer, Dog ->

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  another_namespace
    // deep == true
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Base"), MI_TRUE, ZT("Dog,Animal,Person,Programmer,Manager,CEO"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Animal"), MI_TRUE, ZT("Dog"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Person"), MI_TRUE, ZT("Programmer,Manager,CEO"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Manager"), MI_TRUE, ZT("CEO"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("CEO"), MI_TRUE, ZT(""));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Programmer"), MI_TRUE, ZT(""));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Dog"), MI_TRUE, ZT(""));

    // deep == false
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Base"), MI_FALSE, ZT("Animal,Person"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Animal"), MI_FALSE, ZT("Dog"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Person"), MI_FALSE, ZT("Programmer,Manager"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Manager"), MI_FALSE, ZT("CEO"));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("CEO"), MI_FALSE, ZT(""));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Programmer"), MI_FALSE, ZT(""));
    VerifyInheritanceChain(&reg, ZT("another_namespace"), ZT("Dog"), MI_FALSE, ZT(""));

    // ALL CLASSES, deep == true
    VerifyInheritanceChain(&reg, ZT("another_namespace"), 0, MI_TRUE, ZT("Dog,Base,Animal,Person,Programmer,Manager,CEO,stand_alone_Base"));

    // ALL CLASSES, deep == false
    VerifyInheritanceChain(&reg, ZT("another_namespace"), 0, MI_FALSE, ZT("Base,stand_alone_Base"));

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  namespace
    // deep == true
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Base"), MI_TRUE, ZT("Dog,Animal"));
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Animal"), MI_TRUE, ZT("Dog"));
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Dog"), MI_TRUE, ZT(""));

    // deep == false
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Base"), MI_FALSE, ZT("Animal"));
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Animal"), MI_FALSE, ZT("Dog"));
    VerifyInheritanceChain(&reg, ZT("namespace"), ZT("Dog"), MI_FALSE, ZT(""));

    // ALL CLASSES, deep == true
    VerifyInheritanceChain(&reg, ZT("namespace"), 0, MI_TRUE, ZT("Dog,Base,Animal"));

    // ALL CLASSES, deep == false
    VerifyInheritanceChain(&reg, ZT("namespace"), 0, MI_FALSE, ZT("Base"));

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  base classes
    const ZChar* res = 0;
    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("Base"), &res) &&
        0 == res );
    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("Animal"), &res) &&
        ut::String(ZT("Base")) == res );
    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("Dog"), &res) &&
        ut::String(ZT("Animal")) == res );
    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("Programmer"), &res) &&
        ut::String(ZT("Person")) == res );

    // different case
    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("mAnAger"), &res) &&
        ut::String(ZT("Person")) == res );

    UT_ASSERT( MI_RESULT_OK == ProvReg_GetDirectBaseClass(&reg, ZT("Another_Namespace"), ZT("ceo"), &res) &&
        ut::String(ZT("Manager")) == res );

    // invalid class
    UT_ASSERT( MI_RESULT_INVALID_CLASS == ProvReg_GetDirectBaseClass(&reg, ZT("another_namespace"), ZT("not-existing-class"), &res) );

    // invalid namespace
    UT_ASSERT( MI_RESULT_INVALID_NAMESPACE == ProvReg_GetDirectBaseClass(&reg, ZT("not-existing-namespace"), ZT("Base"), &res) );

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestInvalidClassInheritanceTree()
{
    const char* content = "# sample config entry\n"
        "statik:namespace           :Dog,Animal,Base    :provider_name\n"
        "statik:  namespace         :Base,Animal,Dog    :provider_name\n"
        ;

    // entry is invalid - expect error back

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_INVALID_CLASS_HIERARCHY == ProvReg_Init(&reg, TEMP_FILE));
}
#endif

#if 0
static void TestInvalidNamespace()
{
    const char* content = "# sample config entry\n"
        "statik:namespace           :Dog,Animal,Base    :provider_name\n"
        ;

    // entry is invalid - expect error back

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));


    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestAssociations()
{
    const char* content = "# sample config entry\n"
        "# interop namespace\n"
        "statik:interop: Prov_Profile,CIM_RegisteredProfile,CIM_ManagedElement + "
            "Prov_ElementConformsToProfile,CIM_ElementConformsToProfile + "
            "Prov_CS,CIM_ComputerSystem,CIM_ManagedElement:provider_lib\n"
        "statik:interop: Prov_Profile,CIM_RegisteredProfile,CIM_ManagedElement:provider_lib\n"
        "# provider impl namespace\n"
        "statik:provider/impl: Prov_Profile,CIM_RegisteredProfile,CIM_ManagedElement + "
            "Prov_ElementConformsToProfile,CIM_ElementConformsToProfile +"
            "Prov_CS,CIM_ComputerSystem,CIM_ManagedElement:provider_lib\n"

        "statik:provider/impl:Prov_CS,CIM_ComputerSystem,CIM_ManagedElement:provider_lib\n"
        "statik:provider/impl:Prov_CustomCS,Prov_CS,CIM_ComputerSystem,CIM_ManagedElement:provider_lib\n"
        ;

    // verify inheritance chains:
    // CIM_ManagedElement -> CIM_RegisteredProfile, Prov_Profile, CIM_ComputerSystem, Prov_CS
    // CIM_ElementConformsToProfile -> Prov_ElementConformsToProfile
    // CIM_RegisteredProfile -> Prov_Profile
    // CIM_ComputerSystem -> Prov_CS

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  interop
    // deep == true
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ManagedElement"), MI_TRUE, ZT("CIM_RegisteredProfile,Prov_Profile,CIM_ComputerSystem,Prov_CS"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ElementConformsToProfile"), MI_TRUE, ZT("Prov_ElementConformsToProfile"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_RegisteredProfile"), MI_TRUE, ZT("Prov_Profile"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ComputerSystem"), MI_TRUE, ZT("Prov_CS"));

    // deep == false
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ManagedElement"), MI_FALSE, ZT("CIM_RegisteredProfile,CIM_ComputerSystem"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ElementConformsToProfile"), MI_FALSE, ZT("Prov_ElementConformsToProfile"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_RegisteredProfile"), MI_FALSE, ZT("Prov_Profile"));
    VerifyInheritanceChain(&reg, ZT("interop"), ZT("CIM_ComputerSystem"), MI_FALSE, ZT("Prov_CS"));

    // associations
    VerifyAssociationChain(&reg, ZT("provider/impl"), ZT("Prov_CustomCS"), 0, 0, ZT("Prov_ElementConformsToProfile"));
    VerifyAssociationChain(&reg, ZT("provider/impl"), ZT("Prov_CustomCS"), ZT("CIM_ElementConformsToProfile"), 0, ZT("Prov_ElementConformsToProfile"));
    VerifyAssociationChain(&reg, ZT("provider/impl"), ZT("Prov_CustomCS"), ZT("CIM_ElementConformsToProfile"), ZT("CIM_RegisteredProfile"), ZT("Prov_ElementConformsToProfile"));
    VerifyAssociationChain(&reg, ZT("provider/impl"), ZT("Prov_CustomCS"), 0, ZT("CIM_ManagedElement"), ZT("Prov_ElementConformsToProfile"));

    VerifyAssociationChain(&reg, ZT("interop"), ZT("Prov_Profile"), 0, 0, ZT("Prov_ElementConformsToProfile"));

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestMultipleAssociations()
{
    const char* content = "# sample config entry\n"
        "statik:ns:B,C+xb+X,Z:provider_lib\n"
        "statik:ns:B,C+bx+X,Z:provider_lib\n"
        "statik:ns:B,C+bz+Z:provider_lib\n"
        "statik:ns:A,B,C:provider_lib\n"
        "statik:ns:AA,B,C:provider_lib\n"
        "statik:ns:AAA,B,C:provider_lib\n"
        "statik:ns:X,Z + mx,zn + M,N:provider_lib\n"
        "statik:ns:Z + zn + N:provider_lib\n"
        ;

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    // associations
    VerifyAssociationChain(&reg, ZT("ns"), ZT("AAA"), 0,          0, ZT("xb,bx,bz"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("AAA"), ZT("bz"),    0, ZT("bz"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("AAA"), 0,          ZT("X"), ZT("xb,bx,bz"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("AAA"), 0,          ZT("Z"), ZT("xb,bx,bz"));

    VerifyAssociationChain(&reg, ZT("ns"), ZT("X"), 0,        0, ZT("xb,bx,bz,mx,zn"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("Z"), 0,        0, ZT("bz,zn"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("X"), ZT("zn"),  0, ZT("mx,zn"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("X"), ZT("bz"),  0, ZT("bz"));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("X"), ZT("bz"),  ZT("A"), ZT("bz"));

    VerifyAssociationChain(&reg, ZT("ns"), ZT("C"), 0,        0, ZT(""));
    VerifyAssociationChain(&reg, ZT("ns"), ZT("AAA"), ZT("mx"),    0, ZT(""));

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestAssociationsInvalidClass()
{
    const char* content = "# sample config entry\n"
        "statik:ns:B,C+xb+X,Z:provider_lib\n"
        "statik:ns:B,C+bx+X,Z:provider_lib\n"
        "statik:ns:B,C+bz+Z:provider_lib\n"
        "statik:ns:A,B,C:provider_lib\n"
        "statik:ns:AA,B,C:provider_lib\n"
        "statik:ns:AAA,B,C:provider_lib\n"
        "statik:ns:X,Z + mx,zn + M,N:provider_lib\n"
        "statik:ns:Z + zn + N:provider_lib\n"
        ;

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    ProvRegAssocPosition pos;

    UT_ASSERT (MI_RESULT_INVALID_NAMESPACE == ProvReg_BeginAssocClasses( &reg, ZT("notExistingNamespace"), ZT("X"), 0, 0, &pos ));
    UT_ASSERT (MI_RESULT_INVALID_CLASS == ProvReg_BeginAssocClasses( &reg, ZT("ns"), ZT("noExisitingClass"), 0, 0, &pos ));
    UT_ASSERT (MI_RESULT_INVALID_CLASS == ProvReg_BeginAssocClasses( &reg, ZT("ns"), ZT("AA"), ZT("noExisitingClass"), 0, &pos ));
    UT_ASSERT (MI_RESULT_INVALID_CLASS == ProvReg_BeginAssocClasses( &reg, ZT("ns"), ZT("AA"), 0, ZT("noExisitingClass"), &pos ));

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestAssociationsToTheSameClass()
{
    const char* content = "# sample config entry\n"
        "statik:ns:X+a+X:provider_lib\n"
        ;

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    // associations
    VerifyAssociationChain(&reg, ZT("ns"), ZT("X"), 0,          0, ZT("a"));

    ProvReg_Destroy(&reg);
}
#endif

#if 0
static void TestProvRegHosting()
{
    const char* content = "# sample config entry\n"
        "statik:ns:Default:provider_lib\n"
        "statik:ns:Inproc:provider_lib:@inproc@\t \n"
        "statik:ns:Requestor:provider_lib:\t@requestor@\n"
        "statik:ns:User:provider_lib:a_user \n"
        ;

    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    ProvReg reg;

    UT_ASSERT (MI_RESULT_OK == ProvReg_Init(&reg, TEMP_FILE));

    // verify hosting types are set correctly
    const ProvRegEntry* regItem; 
    MI_Result findResult;
    regItem = ProvReg_FindProviderForClass(&reg, ZT("ns"), ZT("Default"), &findResult);
    UT_ASSERT(regItem);
    UT_ASSERT(regItem->hosting == PROV_HOSTING_INPROC);
    UT_ASSERT(regItem->user == 0);

    regItem = ProvReg_FindProviderForClass(&reg, ZT("ns"), ZT("Inproc"), &findResult);
    UT_ASSERT(regItem);
    UT_ASSERT(regItem->hosting == PROV_HOSTING_INPROC);
    UT_ASSERT(regItem->user == 0);

    regItem = ProvReg_FindProviderForClass(&reg, ZT("ns"), ZT("Requestor"), &findResult);
    UT_ASSERT(regItem);
    UT_ASSERT(regItem->hosting == PROV_HOSTING_REQUESTOR);
    UT_ASSERT(regItem->user == 0);

    regItem = ProvReg_FindProviderForClass(&reg, ZT("ns"), ZT("user"), &findResult);
    UT_ASSERT(regItem);
    UT_ASSERT(regItem->hosting == PROV_HOSTING_USER);
    UT_ASSERT(regItem->user != 0);
    UT_ASSERT(string(regItem->user) == "a_user");

    ProvReg_Destroy(&reg);
}
#endif

static void TestRegFile()
{
    string root = GetPath(ID_SRCDIR);
    root += "/tests/provreg/omiregister/root-cimv2/ConnectorProviderCXX.reg";
    RegFile* rf = RegFile_New(root.c_str());

    UT_ASSERT(rf != NULL);

#if 0
    RegFile_Print(rf, stdout);
#endif

    RegFile_Delete(rf);
}

static void TestRegNameSpaces()
{
    vector<string> expected;
    vector<string> names;

    string root = GetPath(ID_SRCDIR);
    root += "/tests/provreg/omiregister";
    Dir* dir = Dir_Open(root.c_str());
    UT_ASSERT(dir != NULL);

    for (;;)
    {
        DirEnt *ent = Dir_Read(dir);
        if (!ent)
            break;

        if (strcmp(ent->name, "..") == 0 || strcmp(ent->name, ".") == 0)
            continue;

        if (strcmp(ent->name, "CVS") == 0)
            continue;

        names.push_back(ent->name);
    }

    Dir_Close(dir);

    expected.push_back("interop");
    expected.push_back("root");
    expected.push_back("root-cimv2");

    UT_ASSERT(names.size() == 3);
    UT_ASSERT(expected.size() == 3);

    sort(names.begin(), names.end());
    sort(expected.begin(), expected.end());
    UT_ASSERT(names == expected);
}

#if defined(CONFIG_POSIX)
static void TestProvReg2()
{
    ProvReg provReg;
    MI_Result r = ProvReg_Init2(&provReg);
    UT_ASSERT(r == MI_RESULT_OK);

    ProvReg_Destroy(&provReg);
}
#endif

static void RunTests()
{
    UT_TEST(TestRegFile);
    UT_TEST(TestRegNameSpaces);
#if defined(CONFIG_POSIX)
    UT_TEST(TestProvReg2);
#endif
}

UT_ENTRY_POINT(RunTests);
