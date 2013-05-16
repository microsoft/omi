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

/* Must be defined first (define MI_CHAR_TYPE) */
#include <mof.h>

#include <string>
#include <map>
#include <iostream>

#if defined(_MSC_VER)
#include  <io.h>
#define CONFIG_CIMSCHEMA "CIM-2.32.0"
#endif

#include <common.h>

#include <ut/ut.h>

#include <io/io.h>
#include <base/paths.h>
#include <base/dir.h>
#include <base/strings.h>

using namespace std;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static char TEMP_FILE[MAX_PATH_SIZE];

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

extern "C" void ErrorCallback(const char* msg, const wchar_t* wmsg, void*)
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

extern "C" void PragmaCallback(const char* pragma, const char* value, void*)
{
    printf("pragma: %s=%s\n", pragma, value);
}

BEGIN_EXTERNC
void ClassDeclCallback(const MI_ClassDecl* decl, void*)
{
    //printf("class: %s\n", decl->name);
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
    else if ( ut::String(MI_T("ToSubClass")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0);
    }
    else
    {
        Zprintf(MI_T("class: %s\n"), decl->name);
        UT_ASSERT(ut::_StrToFalse("unexpected classname"));
    }
}

void ClassDeclCallback_Q(const MI_ClassDecl* decl, void*)
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
    else if ( ut::String(MI_T("ToSubClass")) == decl->name )
    {
        UT_ASSERT( decl->superClass == 0);
    }
    else
    {
        Zprintf(MI_T("class: %s\n"), decl->name);
        UT_ASSERT(ut::_StrToFalse("unexpected classname"));
    }
}

void QualifierDeclCallback(const MI_QualifierDecl* decl, void*)
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
        ut::String(MI_T("BooleanQ")) == decl->name )
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
        ut::String(MI_T("StringQ")) == decl->name )
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
    string root = GetPath(ID_SRCDIR);
    return ut::findSampleFile(root.c_str(), "tests/mof/", file);
}

static int ParseFile(const char* file, bool ignore_callbacks, bool use_quiet_callback)
{
    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);

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

static void setUp()
{
    Strlcpy(TEMP_FILE, GetPath(ID_TMPDIR), sizeof(TEMP_FILE));
    Strlcat(TEMP_FILE, "/test_temp.tmp", sizeof(TEMP_FILE));

#if 0
    string root = GetPath(ID_SRCDIR);
    root += "/unittest";
    Chdir(root.c_str());
#endif
    s_results.clear();

#ifndef _MSC_VER
    Chdir(CONFIG_SRCDIR);
#endif
}

static void cleanup()
{
    ut::removeIfExist( TEMP_FILE );
}

static void TestFailedIfFileDoesNotExist()
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

static void TestParseMofClasses()
{
    MOF_Parser* parser;

    /* Create the parser */
    const char* paths [] = { "." };

    parser = MOF_Parser_New(paths, sizeof(paths)/sizeof(paths[0]));
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);

    /* Parse the file */
    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("classes.mof").c_str()) == 0);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( s_results.m_error.empty() );
}

static void TestAllTypesOfQualifiers()
{
    MOF_Parser* parser;

    /* Create the parser */
    const char* paths [] = { "." };

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

static void TestDumpFunction()
{
    MOF_Parser* parser;

    parser = MOF_Parser_New(0,0);
    MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
    MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    MOF_Parser_SetPragmaCallback(parser, PragmaCallback, NULL);
    MOF_Parser_SetClassDeclCallback(parser, ClassDeclCallback, NULL);
    MOF_Parser_SetQualifierDeclCallback(parser, QualifierDeclCallback, NULL);

    /* Parse the file */
    UT_ASSERT (MOF_Parser_Parse(parser, findMofFile("classes.mof").c_str()) == 0);

    /* Dump */
    FILE* f_null = Fopen(NULL_FILE,"a");

    fprintf(f_null, "test out\n");
    MOF_Parser_Dump(parser, f_null);
    fclose(f_null);

    // if you want to see the output, un-comment next line
    // MOF_Parser_Dump(parser, stdout);

    /* Delete the parser */
    MOF_Parser_Delete(parser);

    UT_ASSERT( s_results.m_error.empty() );
}

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

static void TestValidDateString()
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

static void TestInvalidDateShortString()
{
    // create a mof file with invalid date-time quilifier
    const char content [] =
        "Qualifier DatetimeQ : Datetime = \"20091225123000.123456-36\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidDateInvalidString()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"xxx\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidYear()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"y0091225123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidMonth()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091x25123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidDay()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"2009112z123000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidHour()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v23000.123456-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidMin()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v23000112hh56-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidSec()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"20091121v2300011256ss-360\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidDateFormat2()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQ : Datetime = \"12345?78121212.123456:000\", Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidTimeFormat2()
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


static void TestInvalidDateTimeArray()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQA : Datetime[] = { \"xxx1225123000.123456-360\" } , Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestInvalidDateTimeLongArray()
{
    // create a mof file with invalid date-time quilifier
    const char content [] = "Qualifier DatetimeQA : Datetime[] = { \"20091225123000.123456-360\", \"20091225123000.123456-360\", \"20091225123000.123456-360\",\"xxx\" } , Scope(any), Flavor(DisableOverride);";

    ParseContentExpectToFail(content);
}

static void TestSyntaxErrorThatCausedHanging()
{
    // this specific file caused hanging initially and added for regression purposes
    UT_ASSERT( 0 != ParseFile(findMofFile("syntaxerror.mof").c_str(), false, true) );

    // expect errors
    UT_ASSERT( !s_results.m_error.empty() );
}

static void TestParseMofWithInclude()
{
    // check 'pragma include' works
    string content = "#pragma include(\"";

    content += findMofFile("quals.mof") + "\")";

    ParseContentExpectToSucceed(content.c_str(), false);
}

static void TestMinValueIncompatibleType()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinValue(1234)]ut::String s = \"123\"; /* incompatible type */ };" );
}

static void TestMinValueU8()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(14)]Uint8 x = 15; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(255)]Uint8 x = 255; /* ok */};", true);
}

static void TestInvalidMinValueU8()
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

static void TestMinValueU16()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(1000)]Uint16 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(65535)]Uint16 x = 65535; /* ok */};", true);
}

static void TestInvalidMinValueU16()
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

static void TestMinValueU32()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(999)]Uint32 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(4294967295)]Uint32 x = 4294967295; /* ok */};", true);
}

static void TestInvalidMinValueU32()
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

static void TestMinValueU64()
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

static void TestInvalidMinValueU64()
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

static void TestMinValueS8()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(14)]Sint8 x = 15; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(-128)]Sint8 x = -128; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinValue(127)]Sint8 x = 127; /* ok */};", true);
}

static void TestInvalidMinValueS8()
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

static void TestMinValueS16()
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

static void TestInvalidMinValueS16()
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

static void TestMinValueS32()
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

static void TestInvalidMinValueS32()
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

static void TestMinValueS64()
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

static void TestInvalidMinValueS64()
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

static void TestMinValueR32()
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

static void TestInvalidMinValueR32()
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

static void TestMinValueR64()
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

static void TestInvalidMinValueR64()
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

static void TestMaxValueIncompatibleType()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxValue(1234)]ut::String s = \"123\"; /* incompatible type */ };" );
}


static void TestMaxValueU8()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(14)]Uint8 x = 13; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(255)]Uint8 x = 255; /* ok */};", true);
}

static void TestInvalidMaxValueU8()
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

static void TestMaxValueU16()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(1000)]Uint16 x = 1000; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(65535)]Uint16 x = 65535; /* ok */};", true);
}

static void TestInvalidMaxValueU16()
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

static void TestMaxValueU32()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(999)]Uint32 x = 998; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(4294967295)]Uint32 x = 4294967295; /* ok */};", true);
}

static void TestInvalidMaxValueU32()
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

static void TestMaxValueU64()
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

static void TestInvalidMaxValueU64()
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

static void TestMaxValueS8()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(14)]Sint8 x = 13; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(-128)]Sint8 x = -128; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxValue(127)]Sint8 x = 127; /* ok */};", true);
}

static void TestInvalidMaxValueS8()
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

static void TestMaxValueS16()
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

static void TestInvalidMaxValueS16()
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

static void TestMaxValueS32()

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

static void TestInvalidMaxValueS32()
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

static void TestMaxValueS64()
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

static void TestInvalidMaxValueS64()
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

static void TestMaxValueR32()
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

static void TestInvalidMaxValueR32()
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

static void TestMaxValueR64()
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

static void TestInvalidMaxValueR64()
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

static void TestUint64_Bug741436()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { uint64 p_uint64 = 0xFFFFFFFFFFFFFFAA; /* ok */};", true);
}

static void TestMaxLenAttribute()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxLen(3)] string s = \"123\"; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MaxLen(3)] string s[] = {\"123\",\"ab\"}; /* ok */};", true);
}

static void TestInvalidMaxLenAttribute()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] string s = \"12345\"; /* string too long */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] string s[] = {\"ab\",\"12345\"}; /* string too long */};");
}

static void TestIncompatibleTypeMaxLenAttribute()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MaxLen(3)] uint32 u = 12345; /* n/a for ints */};");
}

static void TestMinLenAttribute()
{
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinLen(3)] string s = \"123\"; /* ok */};", true);
    AddQualifiersParseContentExpectToSucceed(
        "class T { [MinLen(3)] string s[] = {\"123\",\"abcd\"}; /* ok */};", true);
}

static void TestInvalidMinLenAttribute()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] string s = \"12\"; /* string too short */};");
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] string s[] = {\"ab\",\"12345\"}; /* string too short */};");
}

static void TestIncompatibleTypeMinLenAttribute()
{
    AddQualifiersParseContentExpectToFail(
        "class T { [MinLen(3)] uint32 u = 12345; /* n/a for ints */};");
}

static void TestFindingIncludeFile()
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

static void TestDifferentKeyInDerivedClass()
{
    // test different key in derived class
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [key] uint32 kv1; };\n\
Class B: A { [key] uint32 kv2; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}

static void TestDifferentKeyInSkipLevelClass()
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

static void TestDifferentKeyTypeInDerivedClass()
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

static void TestEmbeddedInstanceUndefinedClass()
{
    // test undefined class referred from embedded instance
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
Class A { [embeddedInstance(\"DoesNotExists\")] string s; };\n\
";

    AddQualifiersParseContentExpectToFail( data.c_str(), true, true );
}

static void TestEmbeddedInstanceDifferentCase()
{
    // test undefined class referred from embedded instance
    // Note: this MOF is invalid and MOF parser should catch the error
    string data = "\
class emb { string s;};\n\
Class A { [embeddedInstance(\"eMB\")] string s; };\n\
";

    AddQualifiersParseContentExpectToSucceed( data.c_str(), true, false );
}

static void TestIntConstantOverflow()
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

static void TestUint64ConstantValue()
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

static void TestInt64ConstantValue()
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

static void TestHexInt64ConstantValue()
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

static void TestBinInt64ConstantValue()
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

static void AllMofTests()
{
    UT_TEST(TestFailedIfFileDoesNotExist);
    UT_TEST(TestParseMofClasses);
    UT_TEST(TestAllTypesOfQualifiers);
    UT_TEST(TestDumpFunction);

    UT_TEST(TestValidDateString);

    UT_TEST(TestInvalidDateShortString);
    UT_TEST(TestInvalidDateInvalidString);
    UT_TEST(TestInvalidYear);
    UT_TEST(TestInvalidMonth);
    UT_TEST(TestInvalidDay);
    UT_TEST(TestInvalidHour);
    UT_TEST(TestInvalidMin);
    UT_TEST(TestInvalidSec);
    UT_TEST(TestInvalidDateFormat2);
    UT_TEST(TestInvalidTimeFormat2);

    UT_TEST(TestSyntaxErrorThatCausedHanging);

    UT_TEST(TestInvalidDateTimeArray);
    UT_TEST(TestInvalidDateTimeLongArray);
    UT_TEST(TestParseMofWithInclude);

    UT_TEST(TestMinValueIncompatibleType);

    UT_TEST(TestMinValueU8);
    UT_TEST(TestInvalidMinValueU8);
    UT_TEST(TestMinValueU16);
    UT_TEST(TestInvalidMinValueU16);
    UT_TEST(TestMinValueU32);
    UT_TEST(TestInvalidMinValueU32);
    UT_TEST(TestMinValueU64);
    UT_TEST(TestInvalidMinValueU64);

    UT_TEST(TestMinValueS8);
    UT_TEST(TestInvalidMinValueS8);
    UT_TEST(TestMinValueS16);
    UT_TEST(TestInvalidMinValueS16);
    UT_TEST(TestMinValueS32);
    UT_TEST(TestInvalidMinValueS32);
    UT_TEST(TestMinValueS64);
    UT_TEST(TestInvalidMinValueS64);
    UT_TEST(TestMinValueR32);
    UT_TEST(TestInvalidMinValueR32);
    UT_TEST(TestMinValueR64);
    UT_TEST(TestInvalidMinValueR64);

    UT_TEST(TestMaxValueU8);
    UT_TEST(TestInvalidMaxValueU8);
    UT_TEST(TestMaxValueU16);
    UT_TEST(TestInvalidMaxValueU16);
    UT_TEST(TestMaxValueU32);
    UT_TEST(TestInvalidMaxValueU32);
    UT_TEST(TestMaxValueU64);
    UT_TEST(TestInvalidMaxValueU64);

    UT_TEST(TestMaxValueIncompatibleType);

    UT_TEST(TestMaxValueS8);
    UT_TEST(TestInvalidMaxValueS8);
    UT_TEST(TestMaxValueS16);
    UT_TEST(TestInvalidMaxValueS16);
    UT_TEST(TestMaxValueS32);
    UT_TEST(TestInvalidMaxValueS32);
    UT_TEST(TestMaxValueS64);
    UT_TEST(TestInvalidMaxValueS64);
    UT_TEST(TestMaxValueR32);
    UT_TEST(TestInvalidMaxValueR32);
    UT_TEST(TestMaxValueR64);
    UT_TEST(TestInvalidMaxValueR64);

    UT_TEST(TestUint64_Bug741436);

    UT_TEST(TestMaxLenAttribute);
    UT_TEST(TestInvalidMaxLenAttribute);
    UT_TEST(TestIncompatibleTypeMaxLenAttribute);
    UT_TEST(TestMinLenAttribute);
    UT_TEST(TestInvalidMinLenAttribute);
    UT_TEST(TestIncompatibleTypeMinLenAttribute);

    UT_TEST(TestFindingIncludeFile);

    UT_TEST(TestDifferentKeyInDerivedClass);
    UT_TEST(TestDifferentKeyInSkipLevelClass);
    UT_TEST(TestDifferentKeyTypeInDerivedClass);

    UT_TEST(TestIntConstantOverflow);
    UT_TEST(TestUint64ConstantValue);
    UT_TEST(TestInt64ConstantValue);
    UT_TEST(TestHexInt64ConstantValue);
    UT_TEST(TestBinInt64ConstantValue);

    UT_TEST(TestEmbeddedInstanceUndefinedClass);
    UT_TEST(TestEmbeddedInstanceDifferentCase);
}

UT_ENTRY_POINT(AllMofTests);
