/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* Must be defined first (define MI_CHAR_TYPE) */
#include <mof/mof.h>

#include <string>
#include <map>
#include <iostream>

#if defined(_MSC_VER)
#include  <io.h>
#define CONFIG_CIMSCHEMA "CIM-2.32.0"
#endif

#include <common.h>

#include <ut/ut.h>

#include <pal/format.h>
#include <pal/file.h>
#include <base/paths.h>
#include <pal/dir.h>
#include <pal/strings.h>

using namespace std;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static char TEMP_FILE[PAL_MAX_PATH_SIZE];

static struct MofTestResults {
  string m_error, m_warning;

  map<string,string> m_classes, m_qualifiers;

  void clear()
  {
    m_error.clear();
    m_warning.clear();
    m_classes.clear();
    m_qualifiers.clear();
  }

} s_results;

extern "C" void ErrorCallback(const char* msg, const wchar_t* wmsg, void* )
{
    MI_UNUSED(wmsg);
    s_results.m_error += msg;
    s_results.m_error += "\n";
    fprintf(stderr, "%s\n", msg);
}

extern "C" void ErrorCallback_Quiet(const char* msg, const wchar_t* wmsg, void*)
{
    MI_UNUSED(wmsg);
    s_results.m_error += msg;
    s_results.m_error += "\n";
}

extern "C" void WarningCallback(const char* msg, const wchar_t* wmsg, void*)
{
    MI_UNUSED(wmsg);
    s_results.m_warning += msg;
    s_results.m_warning += "\n";
    //fprintf(stderr, "%s\n", msg);
}

extern "C" void PragmaCallback(const char* pragma, const char* value, void* )
{
    printf("pragma: %s=%s\n", pragma, value);
}

BEGIN_EXTERNC
void ClassDeclCallback(const MI_ClassDecl* decl, void* )
{
    //printf("class: %s, parent: %s\n", decl->name, decl->superClass != 0 ? decl->superClass : "");
    // verify class definition
    if ( ut::String(MI_T("MyClass")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String() == decl->superClass);
    }
    else if ( ut::String(MI_T("MyAssoc")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String() == decl->superClass);
    }
    else if ( ut::String(MI_T("YourClass")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("MyClass")) == decl->superClass);
    }
    else if ( ut::String(MI_T("X")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String() == decl->superClass);
    }
    else if ( ut::String(MI_T("Y")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("X")) == decl->superClass);
    }
    else if ( ut::String(MI_T("Z")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("Y")) == decl->superClass);
    }
    else if ( ut::String(MI_T("Y2")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("X")) == decl->superClass);
    }
    else if ( ut::String(MI_T("Z2")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("Y2")) == decl->superClass);
    }
    else if ( ut::String(MI_T("Class")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String() == decl->superClass);
    }
    else if ( ut::String(MI_T("Tosubclass")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String("Class") == decl->superClass);
    }
    else if ( ut::String(MI_T("SMS_Class_Template")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String("") == decl->superClass);
    }
    else if ( ut::String(MI_T("Test_Misc")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String("SMS_Class_Template") == decl->superClass);
    }
    else
    {
        printf(MI_T("class: %s\n"), decl->name);
        UT_ASSERT(ut::_StrToFalse("unexpected classname"));
    }
}

void ClassDeclCallback_Q(const MI_ClassDecl* decl, void* )
{
    // verify class definition
    if ( ut::String(MI_T("X")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0 ||
            ut::String() == decl->superClass);
    }
    else if ( ut::String(MI_T("Y")) == decl->name )
    {
        UT_ASSERT( decl->superClass != 0 &&
            ut::String(MI_T("X")) == decl->superClass);
    }
    else
    {
        printf(MI_T("class: %s\n"), decl->name);
        UT_ASSERT(ut::_StrToFalse("unexpected classname"));
    }
}

void QualifierDeclCallback(const MI_QualifierDecl* decl, void* )
{
    //printf("qualifier: %s\n", decl->name);
    if ( ut::String(MI_T("Association")) == decl->name ||
         ut::String(MI_T("Indication")) == decl->name ||
         ut::String(MI_T("Abstract")) == decl->name ||
         ut::String(MI_T("Aggregate")) == decl->name ||
         ut::String(MI_T("Aggregation")) == decl->name ||
         ut::String(MI_T("Composition")) == decl->name ||
         ut::String(MI_T("Counter")) == decl->name ||
         ut::String(MI_T("DN")) == decl->name ||
         ut::String(MI_T("EmbeddedObject")) == decl->name ||
         ut::String(MI_T("Exception")) == decl->name ||
         ut::String(MI_T("Experimental")) == decl->name ||
         ut::String(MI_T("Gauge")) == decl->name ||
         ut::String(MI_T("In")) == decl->name ||
         ut::String(MI_T("Key")) == decl->name ||
         ut::String(MI_T("Octetstring")) == decl->name ||
         ut::String(MI_T("Out")) == decl->name ||
         ut::String(MI_T("Read")) == decl->name ||
         ut::String(MI_T("Required")) == decl->name ||
         ut::String(MI_T("Static")) == decl->name ||
         ut::String(MI_T("Terminal")) == decl->name ||
         ut::String(MI_T("Weak")) == decl->name ||
         ut::String(MI_T("Write")) == decl->name ||
         ut::String(MI_T("BooleanQ")) == decl->name ||
         ut::String(MI_T("SMS_Report")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_BOOLEAN );
    }
    else if ( ut::String(MI_T("ArrayType")) == decl->name ||
         ut::String(MI_T("Description")) == decl->name ||
         ut::String(MI_T("DisplayName")) == decl->name ||
         ut::String(MI_T("EmbeddedInstance")) == decl->name ||
         ut::String(MI_T("Nonlocal")) == decl->name ||
         ut::String(MI_T("NonlocalType")) == decl->name ||
         ut::String(MI_T("NullValue")) == decl->name ||
         ut::String(MI_T("Override")) == decl->name ||
         ut::String(MI_T("Propagated")) == decl->name ||
         ut::String(MI_T("Revision")) == decl->name ||
         ut::String(MI_T("Schema")) == decl->name ||
         ut::String(MI_T("Source")) == decl->name ||
         ut::String(MI_T("SourceType")) == decl->name ||
         ut::String(MI_T("UMLPackagePath")) == decl->name ||
         ut::String(MI_T("Units")) == decl->name ||
         ut::String(MI_T("Version")) == decl->name ||
         ut::String(MI_T("StringQ")) == decl->name ||
         ut::String(MI_T("SMS_GroupName")) == decl->name ||
         ut::String(MI_T("SMS_Class_ID")) == decl->name ||
         ut::String(MI_T("SMS_Units")) == decl->name ||
         ut::String(MI_T("SMS_Group_Name")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_STRING );
    }
    else if ( ut::String(MI_T("BitMap")) == decl->name ||
        ut::String(MI_T("BitValues")) == decl->name ||
        ut::String(MI_T("ClassConstraint")) == decl->name ||
        ut::String(MI_T("Deprecated")) == decl->name ||
        ut::String(MI_T("MappingStrings")) == decl->name ||
        ut::String(MI_T("MethodConstraint")) == decl->name ||
        ut::String(MI_T("ModelCorrespondence")) == decl->name ||
        ut::String(MI_T("PropertyConstraint")) == decl->name ||
        ut::String(MI_T("ValueMap")) == decl->name ||
        ut::String(MI_T("Values")) == decl->name ||
        ut::String(MI_T("StringAQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_STRINGA );
    }
    else if ( ut::String(MI_T("Max")) == decl->name ||
        ut::String(MI_T("MaxLen")) == decl->name ||
        ut::String(MI_T("Min")) == decl->name ||
        ut::String(MI_T("MinLen")) == decl->name ||
        ut::String(MI_T("Uint32Q")) == decl->name ||
        ut::String(MI_T("X")) == decl->name ||
        ut::String(MI_T("Y")) == decl->name ||
        ut::String(MI_T("Z")) == decl->name  )
    {
        UT_ASSERT( decl->type == MI_UINT32 );
    }
    else if ( ut::String(MI_T("MaxValue")) == decl->name ||
        ut::String(MI_T("MinValue")) == decl->name ||
        ut::String(MI_T("Sint64Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT64 );
    }
    else if ( ut::String(MI_T("Sint8Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT8 );
    }
    else if ( ut::String(MI_T("Uint8Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT8 );
    }
    else if ( ut::String(MI_T("Sint16Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT16 );
    }
    else if ( ut::String(MI_T("Uint16Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT16 );
    }
    else if ( ut::String(MI_T("Sint32Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT32 );
    }
    else if ( ut::String(MI_T("Uint64Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT64 );
    }
    else if ( ut::String(MI_T("Real32Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_REAL32 );
    }
    else if ( ut::String(MI_T("Real64Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_REAL64 );
    }
    else if ( ut::String(MI_T("Char16Q")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_CHAR16 );
    }
    else if ( ut::String(MI_T("DatetimeQ")) == decl->name ||
        ut::String(MI_T("DatetimeQ2")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_DATETIME );
    }
    else if ( ut::String(MI_T("BooleanAQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_BOOLEANA );
    }
    else if ( ut::String(MI_T("Sint8AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT8A );
    }
    else if ( ut::String(MI_T("Uint8AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT8A );
    }
    else if ( ut::String(MI_T("Sint16AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT16A );
    }
    else if ( ut::String(MI_T("Uint16AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT16A );
    }
    else if ( ut::String(MI_T("Sint32AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT32A );
    }
    else if ( ut::String(MI_T("Uint32AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT32A );
    }
    else if ( ut::String(MI_T("Sint64AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_SINT64A );
    }
    else if ( ut::String(MI_T("Uint64AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_UINT64A );
    }
    else if ( ut::String(MI_T("Real32AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_REAL32A );
    }
    else if ( ut::String(MI_T("Real64AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_REAL64A );
    }
    else if ( ut::String(MI_T("Char16AQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_CHAR16A );
    }
    else if ( ut::String(MI_T("DatetimeAQ")) == decl->name )
    {
        UT_ASSERT( decl->type == MI_DATETIMEA );
    }
    else
    {
        printf(MI_T("qualifier: %s\n"), decl->name);
        UT_ASSERT(ut::_StrToFalse("unexpected qualifier"));
    }
}
END_EXTERNC

static string findMofFile(const char* file)
{
    string root = OMI_GetPath(ID_PREFIX);
    return ut::findSampleFile(root.c_str(), "tests/mof/", file);
}

static int ParseFile(const char* file, bool ignore_callbacks, bool use_quiet_callback)
{
    MOF_Parser* parser;

    parser = MOF_Parser_New(0, 0);

    MOF_Parser_SetErrorCallback(parser, use_quiet_callback ? ErrorCallback_Quiet : ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    if ( !ignore_callbacks)
    {
        MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
        MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback_Q, NULL);
        //MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);
    }

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, file);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    return res;
}

NitsSetup(TestMofSetup)
{
    NitsDisableFaultSim;
    Strlcpy(TEMP_FILE, OMI_GetPath(ID_TMPDIR), sizeof(TEMP_FILE));
    Strlcat(TEMP_FILE, "/test_temp.tmp", sizeof(TEMP_FILE));

#if 0
    string root = OMI_GetPath(ID_PREFIX);
    root += "/unittest";
    Chdir(root.c_str());
#endif
    s_results.clear();

#ifndef _MSC_VER
    Chdir(CONFIG_SRCDIR);
#endif
}
NitsEndSetup

NitsCleanup(TestMofSetup)
{
    ut::removeIfExist( TEMP_FILE );
}
NitsEndCleanup

NitsTestWithSetup(TestFailedIfFileDoesNotExist, TestMofSetup)
{    
    MOF_Parser* parser;

    /* Create the parser */
    const char* paths [] = { "." };

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    //MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);

    /* expecting error */
    int r = MOF_Parser_Parse(parser, "fileThatDoesnotExist.mof");

    MOF_Parser_Delete(parser);

    UT_ASSERT (r != 0);
}
NitsEndTest

NitsTestWithSetup(TestParseMofClasses, TestMofSetup)
{
    MOF_Parser* parser;

    /* Create the parser */
    const char* paths [] = { "." };

    /* Parse the file with extensions enabled */

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);
    MOF_Parser_EnableExtensions(parser, MI_TRUE);

    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("classes.mof").c_str()) == 0);

    UT_ASSERT( s_results.m_error.empty() );

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    /* Parse the file with extensions disabled */

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);
    MOF_Parser_EnableExtensions(parser, MI_FALSE);

    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("classes.mof").c_str()) != 0);

    UT_ASSERT( !s_results.m_error.empty() );

    /* Delete the parser */
    MOF_Parser_Delete(parser);
}
NitsEndTest

static char s_MofString[] =
{
    "Qualifier In : boolean = true, Scope(parameter), Flavor(DisableOverride);\n"
    "\n"
    "Qualifier Out : boolean = true, Scope(parameter), Flavor(DisableOverride);\n"
    "\n"
    "Qualifier Key : boolean = true, Scope(property, reference), Flavor(DisableOverride);\n"
    "\n"
    "Qualifier Static : boolean = true, Scope(method, property), Flavor(DisableOverride);\n"
    "\n"
    "class MyClass\n"
    "{\n"
    "    [Key] MyClass REF Left;\n"
    "    [Key] MyClass REF Right;\n"
    "};\n"
    "\n"
    "class YourClass : MyClass\n"
    "{\n"
    "    [Key] String MyKey;\n"
    "    String YourProperty;\n"
    "    uint32 AnotherProperty;\n"
    "\n"
    "    [Static] Uint32 Foo(\n"
    "        [In] String Arg1,\n"
    "        [In, Out] String Arg2,\n"
    "        [In(false), Out] String Arg3);\n"
    "};\n"
    "\n"
    "instance of YourClass as $Y\n"
    "{\n"
    "    MyKey = \"My Key\";\n"
    "    YourProperty = \"Your Property\";\n"
    "    AnotherProperty = 3;\n"
    "};\n"
};

NitsTestWithSetup(TestParseMofString, TestMofSetup)
{
    MOF_Parser* parser;

    /* Create the parser */
    const char* paths [] = { "." };

    /* Parse the file with extensions disabled */

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);
    MOF_Parser_EnableExtensions(parser, MI_FALSE);

    UT_ASSERT (MOF_Parser_ParseString(parser, s_MofString) != 0);

    UT_ASSERT( !s_results.m_error.empty() );

    /* Delete the parser */
    MOF_Parser_Delete(parser);
}
NitsEndTest

NitsTestWithSetup(TestAllTypesOfQualifiers, TestMofSetup)
{
    MOF_Parser* parser;
 
    /* Create the parser */
    const char* paths [] = {"."};

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback_Q, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);

    /* Parse the file */
    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("quals.mof").c_str()) == 0);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest

NitsTestWithSetup(TestDumpFunction, TestMofSetup)
{
    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);
    MOF_Parser_EnableExtensions(parser, MI_TRUE);

    /* Parse the file */
    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("classes.mof").c_str()) == 0);

    /* Dump */
    FILE* f_null = File_Open(NULL_FILE,"a");

    fprintf(f_null, "test out\n");
    MOF_Parser_Dump(parser, f_null);
    fclose(f_null);

    // if you want to see the output, un-comment next line
    // MOF_Parser_Dump(parser, stdout);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest

static void ParseContentExpectToFail( const char* content, bool ignore_callbacks = true, bool use_quiet_callback = true )
{
    ut::writeFileContent(TEMP_FILE, 
        vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    UT_ASSERT( 0 != ParseFile(TEMP_FILE, ignore_callbacks, use_quiet_callback) );

    // expect errors
    UT_ASSERT( !s_results.m_error.empty() );
}

static void ParseContentExpectToSucceed( const char* content, bool ignore_callbacks = false, bool use_quiet_callback = false )
{
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    UT_ASSERT( 0 == ParseFile(TEMP_FILE, ignore_callbacks, use_quiet_callback) );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}

static void AddQualifiersParseContentExpectToFail(const char* content, bool ignore_callbacks = true, bool use_quiet_callback = true )
{
#if defined(_MSC_VER)
    string data = "\
#pragma include (\"../../share/omischema/" CONFIG_CIMSCHEMA "/qualifiers.mof\")\n\
#pragma include (\"../../share/omischema/" CONFIG_CIMSCHEMA "/qualifiers_optional.mof\")\n\
";
#else
    string data = "\
#pragma include (\"./share/omischema/" CONFIG_CIMSCHEMA "/qualifiers.mof\")\n\
#pragma include (\"./share/omischema/" CONFIG_CIMSCHEMA "/qualifiers_optional.mof\")\n\
";
#endif

    data += content;

    ParseContentExpectToFail(data.c_str(), ignore_callbacks, use_quiet_callback);
}

static void AddQualifiersParseContentExpectToSucceed(const char* content, bool ignore_callbacks = false, bool use_quiet_callback = false)
{
#if defined(_MSC_VER)
        string data = "\
#pragma include (\"../../share/omischema/" CONFIG_CIMSCHEMA "/qualifiers.mof\")\n\
#pragma include (\"../../share/omischema/" CONFIG_CIMSCHEMA "/qualifiers_optional.mof\")\n\
    ";
#else
        string data = "\
#pragma include (\"./share/omischema/" CONFIG_CIMSCHEMA "/qualifiers.mof\")\n\
#pragma include (\"./share/omischema/" CONFIG_CIMSCHEMA "/qualifiers_optional.mof\")\n\
    ";
#endif

    data += content;

    ParseContentExpectToSucceed(data.c_str(), ignore_callbacks, use_quiet_callback);
}


NitsTestWithSetup(TestValidDateString, TestMofSetup)
{
    // create a mof file with valid date-time quilifier
    const char content [] = 
        "Qualifier DatetimeQ : Datetime = \"20091225123000.123456-360\", Scope(any), Flavor(DisableOverride);\n\
        [DatetimeQ(\"12345678121212.123456:000\")] \n\
        class X \n\
        {\n\
        };\n";


    ParseContentExpectToSucceed(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidDateShortString, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier
    const char content [] = 
        "Qualifier DatetimeQ : Datetime = \"20091225123000.123456-36\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidDateInvalidString, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"xxx\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidYear, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"y0091225123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMonth, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091x25123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidDay, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"2009112z123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidHour, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v23000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMin, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v23000112hh56-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidSec, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v2300011256ss-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidDateFormat2, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier                  
    const char content [] = "Qualifier DatetimeQ : Datetime = \"12345?78121212.123456:000\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidTimeFormat2, TestMofSetup)
{
    //hh
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"123456781g1212.123456:000\", Scope(any), Flavor(DisableOverride);");
    //mm
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"1234567812i212.123456:000\", Scope(any), Flavor(DisableOverride);");
    //ss
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"123456781212--.123456:000\", Scope(any), Flavor(DisableOverride);");

    //MMMMMM
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.1!3456:000\", Scope(any), Flavor(DisableOverride);");
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.12.456:000\", Scope(any), Flavor(DisableOverride);");
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.1234--:000\", Scope(any), Flavor(DisableOverride);");

    // .MM
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212!123456:000\", Scope(any), Flavor(DisableOverride);");

    // :000
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.123456:x00\", Scope(any), Flavor(DisableOverride);");
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.123456:0x0\", Scope(any), Flavor(DisableOverride);");
    ParseContentExpectToFail(
        "Qualifier DatetimeQ : Datetime = \"12345678121212.123456:00x\", Scope(any), Flavor(DisableOverride);");

}
NitsEndTest



NitsTestWithSetup(TestInvalidDateTimeArray, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQA : Datetime[] = { \"xxx1225123000.123456-360\" } , Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestInvalidDateTimeLongArray, TestMofSetup)
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQA : Datetime[] = { \"20091225123000.123456-360\", \"20091225123000.123456-360\", \"20091225123000.123456-360\",\"xxx\" } , Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}
NitsEndTest


NitsTestWithSetup(TestSyntaxErrorThatCausedHanging, TestMofSetup)
{
    // this specific file caused hanging initially and added for regression purposes
    UT_ASSERT( 0 != ParseFile(findMofFile("syntaxerror.mof").c_str(), false, true) );

    // expect errors
    UT_ASSERT( !s_results.m_error.empty() );
}
NitsEndTest


NitsTestWithSetup(TestParseMofWithInclude, TestMofSetup)
{
    // check 'pragma include' works
    string content = "#pragma include(\"";

    content += findMofFile("quals.mof") + "\")";

    ParseContentExpectToSucceed(content.c_str(), false);
}
NitsEndTest


NitsTestWithSetup(TestMinValueIncompatibleType, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]ut::String s = \"123\"; /* incompatible type */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueU8, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(14)]Uint8 x = 15; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(255)]Uint8 x = 255; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueU8, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]Uint8 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]Uint8 x = 256; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint8 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint8 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueU16, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(1000)]Uint16 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(65535)]Uint16 x = 65535; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueU16, TestMofSetup)
{
    // u16 range is 0-65535
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(65536)]Uint16 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Uint16 x = 65536; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint16 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint16 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueU32, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Uint32 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(4294967295)]Uint32 x = 4294967295; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueU32, TestMofSetup)
{
    // u32 range is 0-4294967295
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(4294967296)]Uint32 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Uint32 x = 4294967296; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint32 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint32 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueU64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Uint64 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(9223372036854775807)]Uint64 x = 9223372036854775807; /* ok */};", true);
#if 0
    //ATTN: values greater than sint64_max are not supported
    AddQualifiersParseContentExpectToSucceed(
        "class T { Uint64 x = 18446744073709551615; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(NULL)]Uint64 x = 18446744073709551615; /* ok */};", true);
#endif
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueU64, TestMofSetup)
{
    // u64 range is 0-18446744073709551615
    // practically, attributes are limitted by sint64:
    // -9223372036854775807 - 1  - 9223372036854775807
    // however, MinValue is Sint64, so real max for Min value is 9223372036854775807

    //ATTN: values greater than sint64_max are not supported
    //AddQualifiersParseContentExpectToFail(
    //    "class T { [MinValue(18446744073709551616)]Uint64 x = 0; /* overflow */ };" );
    //AddQualifiersParseContentExpectToFail(
    //    "class T { [MinValue(0)]Uint64 x = 18446744073709551616; /* overflow */ };" );

    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint64 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Uint64 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueS8, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(14)]Sint8 x = 15; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-128)]Sint8 x = -128; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(127)]Sint8 x = 127; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueS8, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]Sint8 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]Sint8 x = 256; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint8 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(-11)]Sint8 x = -12; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint8 x = -129; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueS16, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(1000)]Sint16 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(32767)]Sint16 x = 32767; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-32768)]Sint16 x = -32768; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(null)]Sint16 x = -32768; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueS16, TestMofSetup)
{
    // s16 range is -32768 - 32767
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(32768)]Sint16 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Sint16 x = 32768; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint16 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint16 x = -32769; /* underflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint16 x = -32769; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueS32, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Sint32 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-2147483648)]Sint32 x = -2147483648; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-2147483648)]Sint32 x = -2147483647; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(2147483647)]Sint32 x = 2147483647; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueS32, TestMofSetup)
{
    // s32 range is -2147483648  -   2147483647
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(2147483648)]Sint32 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Sint32 x = 2147483648; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint32 x = 0; /* value too small */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint32 x = -2147483649; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueS64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Sint64 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(9223372036854775807)]Sint64 x = 9223372036854775807; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-9223372036854775808)]Sint64 x = -9223372036854775808; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-9223372036854775808)]Sint64 x = -9223372036854775807; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueS64, TestMofSetup)
{
    // u64 range is 0-18446744073709551615
    // practically, attributes are limitted by sint64:
    // -9223372036854775807 - 1  - 9223372036854775807
    //ATTN! int64 errors are not processed correctly yet
#if 0
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(9223372036854775808)]Sint64 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Sint64 x = 9223372036854775808; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint64 x = -9223372036854775809; /* underflow */ };" );
#endif
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1)]Sint64 x = 0; /* value too small */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMinValueR32, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Real32 x = 999.1; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(0)]Real32 x = 0.1e+0; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(9223372036854775807)]Real32 x = 9.3e+18; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-9223372036854775808)]Real32 x = -9.22e18; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueR32, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(999)]Real32 x = 998.1; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Real32 x = -0.1e+0; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(9223372036854775807)]Real32 x = 9.2e18; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(-9223372036854775808)]Real32 x = -9.23e18; /* too small */};");
}
NitsEndTest


NitsTestWithSetup(TestMinValueR64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Real64 x = 999.1; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(0)]Real64 x = 0.1e+0; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(9223372036854775807)]Real64 x = 9.3e+18; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-9223372036854775808)]Real64 x = -9.22e18; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinValueR64, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(999)]Real64 x = 998.1; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(0)]Real64 x = -0.1e+0; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(9223372036854775807)]Real64 x = 9.2e18; /* too small */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(-9223372036854775808)]Real64 x = -9.23e18; /* too small */};");
}
NitsEndTest


NitsTestWithSetup(TestMaxValueIncompatibleType, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1234)]ut::String s = \"123\"; /* incompatible type */ };" );
}
NitsEndTest



NitsTestWithSetup(TestMaxValueU8, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(14)]Uint8 x = 13; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(255)]Uint8 x = 255; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueU8, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(-1)]Uint8 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1234)]Uint8 x = 256; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint8 x = 10; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint8 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueU16, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(1000)]Uint16 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(65535)]Uint16 x = 65535; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueU16, TestMofSetup)
{
    // u16 range is 0-65535
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(65536)]Uint16 x = 65536; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Uint16 x = 65536; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint16 x = 2; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint16 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueU32, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(999)]Uint32 x = 998; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(4294967295)]Uint32 x = 4294967295; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueU32, TestMofSetup)
{
    // u32 range is 0-4294967295
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(4294967296)]Uint32 x = 4294967296; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Uint32 x = 4294967296; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint32 x = 100; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint32 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueU64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(999)]Uint64 x = 997; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(9223372036854775807)]Uint64 x = 9223372036854775807; /* ok */};", true);
#if 0
    //ATTN: values greater than sint64_max are not supported
    AddQualifiersParseContentExpectToSucceed(
        "class T { Uint64 x = 18446744073709551615; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(NULL)]Uint64 x = 18446744073709551615; /* ok */};", true);
#endif
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueU64, TestMofSetup)
{
    // u64 range is 0-18446744073709551615
    // practically, attributes are limitted by sint64:
    // -9223372036854775807 - 1  - 9223372036854775807
    // however, MaxValue is Sint64, so real max for Max value is 9223372036854775807

    //ATTN: values greater than sint64_max are not supported
    //AddQualifiersParseContentExpectToFail(
    //    "class T { [MaxValue(18446744073709551616)]Uint64 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Uint64 x = 18446744073709551616; /* overflow */ };" );

    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint64 x = 10; /* value too large */ };" );
    // ATTN:
    // next line is waiting for some bigger then 64-bit integer 
    // internal representaitons of integers in the parser
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Uint64 x = -1; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueS8, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(14)]Sint8 x = 13; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-128)]Sint8 x = -128; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(127)]Sint8 x = 127; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueS8, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1234)]Sint8 x = 1234; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1234)]Sint8 x = 256; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint8 x = 2; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(-11)]Sint8 x = -10; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint8 x = -129; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueS16, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(1000)]Sint16 x = 0; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(32767)]Sint16 x = 32767; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-32768)]Sint16 x = -32768; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(null)]Sint16 x = -32768; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueS16, TestMofSetup)
{
    // s16 range is -32768 - 32767
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(32768)]Sint16 x = 32768; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Sint16 x = 32768; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint16 x = 2; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint16 x = -32769; /* underflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint16 x = -32769; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueS32, TestMofSetup)

{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(1001)]Sint32 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-2147483648)]Sint32 x = -2147483648; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-2147483647)]Sint32 x = -2147483648; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(2147483647)]Sint32 x = 2147483647; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueS32, TestMofSetup)
{
    // s32 range is -2147483648  -   2147483647
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(2147483648)]Sint32 x = 2147483648; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Sint32 x = 2147483648; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint32 x = 10; /* value too large */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint32 x = -2147483649; /* underflow */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueS64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(1010)]Sint64 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(9223372036854775807)]Sint64 x = 9223372036854775807; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-9223372036854775808)]Sint64 x = -9223372036854775808; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-9223372036854775807)]Sint64 x = -9223372036854775808; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueS64, TestMofSetup)
{
    // u64 range is 0-18446744073709551615
    // practically, attributes are limitted by sint64:
    // -9223372036854775807 - 1  - 9223372036854775807
    //ATTN! int64 errors are not processed correctly yet
#if 0
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(9223372036854775808)]Sint64 x = 0; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Sint64 x = 9223372036854775808; /* overflow */ };" );
    AddQualifiersParseContentExpectToFail(
        "class T { Sint64 x = -9223372036854775809; /* underflow */ };" );
#endif
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(-9223372036854775808)]Sint64 x = -9223372036854775807; /* too large */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1)]Sint64 x = 10; /* value too large */ };" );
}
NitsEndTest


NitsTestWithSetup(TestMaxValueR32, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(999)]Real32 x = 998.9; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(0)]Real32 x = -0.1e-99; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(9223372036854775807)]Real32 x = 9.222e+18; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-9223372036854775808)]Real32 x = -9.224e18; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueR32, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(999)]Real32 x = 999.0001; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Real32 x = 0.1e+0; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(9223372036854775807)]Real32 x = 9.23e18; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(9223372036854775807)]Real32 x = 1.0e38; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(-9223372036854775808)]Real32 x = -9.21e18; /* too big */};");
}
NitsEndTest


NitsTestWithSetup(TestMaxValueR64, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(999)]Real64 x = 998.9; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(0)]Real64 x = -0.1e-99; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(9223372036854775807)]Real64 x = 9.222e+18; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-9223372036854775808)]Real64 x = -9.224e18; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxValueR64, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(999)]Real64 x = 999.00001; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(0)]Real64 x = 0.1e+0; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(9223372036854775807)]Real64 x = 9.23e18; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(9223372036854775807)]Real64 x = 1.0e38; /* too big */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(-9223372036854775808)]Real64 x = -9.21e18; /* too big */};");
}
NitsEndTest


NitsTestWithSetup(TestUint64_Bug741436, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { uint64 p_uint64 = 0xFFFFFFFFFFFFFFAA; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestMaxLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxLen(3)] string s = \"123\"; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxLen(3)] string s[] = {\"123\",\"ab\"}; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMaxLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] string s = \"12345\"; /* string too long */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] string s[] = {\"ab\",\"12345\"}; /* string too long */};");
}
NitsEndTest


NitsTestWithSetup(TestIncompatibleTypeMaxLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] uint32 u = 12345; /* n/a for ints */};");
}
NitsEndTest


NitsTestWithSetup(TestMinLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinLen(3)] string s = \"123\"; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinLen(3)] string s[] = {\"123\",\"abcd\"}; /* ok */};", true);
}
NitsEndTest


NitsTestWithSetup(TestInvalidMinLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] string s = \"12\"; /* string too short */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] string s[] = {\"ab\",\"12345\"}; /* string too short */};");
}
NitsEndTest


NitsTestWithSetup(TestIncompatibleTypeMinLenAttribute, TestMofSetup)
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] uint32 u = 12345; /* n/a for ints */};");
}
NitsEndTest


NitsTestWithSetup(TestFindingIncludeFile, TestMofSetup)
{
    // test include pragma with relative path
    string data = "\
#pragma include (\"qualifiers.mof\")\n\
#pragma include (\"qualifiers_optional.mof\")\n\
                  class T { [MinValue(0)] uint32 u = 12345; };\
";

    const char* content = data.c_str();
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( reinterpret_cast<const unsigned char*>(content), 
        reinterpret_cast<const unsigned char*>(content)+strlen(content)));

    const char* paths[] = {
        "/some-invalid-path/",
#if defined(_MSC_VER)
        "../../share/omischema/" CONFIG_CIMSCHEMA "/"
#else
        "./share/omischema/" CONFIG_CIMSCHEMA "/"
#endif
    };

    MOF_Parser* parser;
    parser = MOF_Parser_New(paths,MI_COUNT(paths));

    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, TEMP_FILE);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( 0 == res );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest


NitsTestWithSetup(TestDifferentKeyInDerivedClass, TestMofSetup)
{
    // test different key in derived class
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [key] uint32 kv1; };\n\
Class B: A { [key] uint32 kv2; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}
NitsEndTest


NitsTestWithSetup(TestDifferentKeyInSkipLevelClass, TestMofSetup)
{
    // test different key in skip-level derived class
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [key] uint32 kv1; };\n\
class b : A {};\n\
Class C: B { [key] uint32 kv2; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}
NitsEndTest


NitsTestWithSetup(TestDifferentKeyTypeInDerivedClass, TestMofSetup)
{
    // test different key type in derived class
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [key] uint32 kv1; };\n\
class b : A {};\n\
Class C: B { [key] uint16 kv1; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}
NitsEndTest


NitsTestWithSetup(TestEmbeddedInstanceUndefinedClass, TestMofSetup)
{
    // test undefined class referred from embedded instance
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [embeddedInstance(\"DoesNotExists\")] string s; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}
NitsEndTest


NitsTestWithSetup(TestEmbeddedInstanceDifferentCase, TestMofSetup)
{
    // test undefined class referred from embedded instance
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
class emb { string s;};\n\
Class A { [embeddedInstance(\"eMB\")] string s; };\n\
";

    AddQualifiersParseContentExpectToSucceed( data.c_str(), true, false );
}
NitsEndTest


NitsTestWithSetup(TestIntConstantOverflow, TestMofSetup)
{
    // test different key type in derived class
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class TestSP_Value\n\
{\n\
uint64 p_uint64 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;\n\
};\n\
";

    //AddQualifiersParseContentExpectToFail( data.c_str(), true, false );
    ParseContentExpectToFail(data.c_str(), true, true);
}
NitsEndTest


BEGIN_EXTERNC
void _Uint64ValueVerificationCallback(const MI_ClassDecl* decl,void*)
{
    UT_ASSERT( ut::String(MI_T("T")) == decl->name );
    UT_ASSERT( decl->numProperties == 1 );
    UT_ASSERT( ut::String(MI_T("p_uint64")) == decl->properties[0]->name );
    UT_ASSERT( MI_UINT64 == decl->properties[0]->type );
    UT_ASSERT( MI_LL(0xFFFFFFFFFFFFFFAA) == *(MI_Uint64*)decl->properties[0]->value );
}
END_EXTERNC

NitsTestWithSetup(TestUint64ConstantValue, TestMofSetup)
{
    // verify that parser correctly interprets vlaue greater than LLONG_MAX
    const unsigned char content [] =
        "class T { uint64 p_uint64 = 0xFFFFFFFFFFFFFFAA; /* ok */};";
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( content, (content)+ sizeof(content) ));

    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);

    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, _Uint64ValueVerificationCallback, NULL);

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, TEMP_FILE);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( 0 == res );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest


BEGIN_EXTERNC
void _Int64ValueVerificationCallback(
    const MI_ClassDecl* decl, void*)
{
    UT_ASSERT( ut::String(MI_T("T")) == decl->name );
    UT_ASSERT( decl->numProperties == 1 );
    UT_ASSERT( ut::String(MI_T("p_int64")) == decl->properties[0]->name );
    UT_ASSERT( MI_SINT64 == decl->properties[0]->type );
    UT_ASSERT( (-MI_LL(9223372036854775807)-0) == *(MI_Sint64*)decl->properties[0]->value );
}
END_EXTERNC

NitsTestWithSetup(TestInt64ConstantValue, TestMofSetup)
{
    // verify that parser correctly interprets vlaue greater than LLONG_MAX
    const unsigned char content [] =
        "class T { sint64 p_int64 = -9223372036854775807; /* ok */};";
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( content, (content)+ sizeof(content) ));

    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);

    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, _Int64ValueVerificationCallback, NULL);

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, TEMP_FILE);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( 0 == res );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest


BEGIN_EXTERNC
void _HexInt64ValueVerificationCallback(
    const MI_ClassDecl* decl, void*)
{
    UT_ASSERT( ut::String(MI_T("T")) == decl->name );
    UT_ASSERT( decl->numProperties == 1 );
    UT_ASSERT( ut::String(MI_T("p_int64")) == decl->properties[0]->name );
    UT_ASSERT( MI_SINT64 == decl->properties[0]->type );
    UT_ASSERT( -MI_LL(0x7FFFFFFFFFFFFFAA) == *(MI_Sint64*)decl->properties[0]->value );
}
END_EXTERNC

NitsTestWithSetup(TestHexInt64ConstantValue, TestMofSetup)
{
    // verify that parser correctly interprets vlaue greater than LLONG_MAX
    const unsigned char content [] =
        "class T { sint64 p_int64 = -0x7FFFFFFFFFFFFFAA; /* ok */};";
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( content, (content)+ sizeof(content) ));

    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);

    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, _HexInt64ValueVerificationCallback, NULL);

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, TEMP_FILE);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( 0 == res );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest


BEGIN_EXTERNC
void _BinInt64ValueVerificationCallback(
    const MI_ClassDecl* decl, void*)
{
    UT_ASSERT( ut::String(MI_T("T")) == decl->name );
    UT_ASSERT( decl->numProperties == 1 );
    UT_ASSERT( ut::String(MI_T("p_int64")) == decl->properties[0]->name );
    UT_ASSERT( MI_SINT64 == decl->properties[0]->type );
    UT_ASSERT( -MI_LL(0x7FFFFFFFFFFFFFFD) == *(MI_Sint64*)decl->properties[0]->value );
}
END_EXTERNC

NitsTestWithSetup(TestBinInt64ConstantValue, TestMofSetup)
{
    // verify that parser correctly interprets vlaue greater than LLONG_MAX
    const unsigned char content [] =
        "class T { sint64 p_int64 = -111111111111111111111111111111111111111111111111111111111111101b; /* ok  dec*/};";
    ut::writeFileContent( TEMP_FILE, vector<unsigned char>( content, (content)+ sizeof(content) ));

    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);

    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, _BinInt64ValueVerificationCallback, NULL);

    /* clear results from previous run */
    s_results.clear();

    /* Parse the file */
    int res = MOF_Parser_Parse(parser, TEMP_FILE);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( 0 == res );

    // expect no errors
    UT_ASSERT( s_results.m_error.empty() );
}
NitsEndTest

