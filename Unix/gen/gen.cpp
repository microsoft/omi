/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "Parser.h"
#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <common.h>
#include <strids.h>

#include "QualifierDecls.h"

#include <pal/strings.h>
#include <base/types.h>
#include <pal/format.h>
#include <pal/file.h>
#include <pal/dir.h>
#include <base/env.h>
#include <base/paths.h>

#if defined(_MSC_VER)
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

#include "gen.h"

// C Provider Templates:
#include "cprototypes_t.h"
#include "cprovider_t.h"
#include "cmodule_t.h"
#include "cmakefile_t.h"

// C++ Provider Templates:
#include "cxxmodule_t.h"
#include "cxxprovider_t.h"
#include "cxxstubs_t.h"
#include "cxxmakefile_t.h"


#include "py_gen.hpp"
using namespace std;

/* xlc doesn't want to use static inline funciotns inside temaplate functions */
int _Scasecmp(const MI_Char* s1, const MI_Char* s2)
{
    return Strcasecmp(s1, s2);
}

//==============================================================================
//
// GeneratorOptions
//
//==============================================================================

GeneratorOptions::GeneratorOptions()
{
    paths.clear();
    descriptions = false;
    values = false;
    mappingStrings = false;
    standardQualifiers = false;
    booleanQualifiers = false;
    ignoreAllQualifiers = false;
    filterSupport = false;
    quiet = false;
    noProviders = false;
    all = false;
    cpp = false;
    schema.clear();
    dir.clear();
    localize = false;
    providerRegistryPath.clear();
    association = false;
    extraClasses.clear();
    entryPoint.clear();
    no_warnings = false;
    modelCorrespondence = false;
    python = false;
}

//==============================================================================
//
// WARNING
//
//     Message included in all generated files that are not intended to be
//     modified by the developer.
//
//==============================================================================

#define WARNING \
    "WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT."

//==============================================================================
//
// arg0
//
//     A global pointer to argv[0] that is set immediately by main().
//
//==============================================================================

static const char* arg0;
static FILE* s_stdout;

//==============================================================================
//
// providerClasses
//
//     The set of class names for which there are providers (used by generator
//     to include or exclude various elements).
//
//==============================================================================

typedef set<string> ProviderClassSet;
static ProviderClassSet providerClasses;

//==============================================================================
//
// generated
//
//     Allows keep tracking of generated classes in 'generateHeader' function
//
//==============================================================================

static set<string> generated_headers;
static set<string> generated_classes;

//==============================================================================
//
// Fprintf()
//
//     Formats and writes a message to FILE.
//
//==============================================================================

PRINTF_FORMAT(3, 4)
static void Fprintf(FILE* os, int id, const MI_Char* format, ...)
{
    va_list ap;
    va_start(ap, format);

#if defined(_MSC_VER)
    wchar_t* wformat = LookupString(id);

    if (wformat)
    {
        vfwprintf(os, wformat, ap);
        PAL_Free(wformat);
    }
    else
#endif
    {
        vfprintf(os, format, ap);
    }

    va_end(ap);
}

//==============================================================================
//
// err()
//
//     Writes a formatted error message to standard error (preceded by argv[0])
//     and then exits.
//
//==============================================================================

PRINTF_FORMAT(2, 3)
void FUNCTION_NEVER_RETURNS err(int id, const char* format, ...)
{
    fprintf(stderr, "%s: ", arg0);

    va_list ap;
    va_start(ap, format);

#if defined(_MSC_VER)
    wchar_t* wformat = LookupString(id);

    if (wformat)
    {
        vfwprintf(stderr, wformat, ap);
        PAL_Free(wformat);
    }
    else
#endif
    {
        vfprintf(stderr, format, ap);
    }

    va_end(ap);

    fputc('\n', stderr);

    exit(1);
}

//==============================================================================
//
// errRefPropCount()
//
//     For assocation class, it must have 2 reference properties count.
//     Otherwise, call this function to write error message and exits.
//
//==============================================================================
void errRefPropCount(const MI_Char* classname)
{
    err(ID_INSUFFICIENT_REFERENCES, "incorrect references properties count: "
        "assocation class %s shall have two references properties", classname);
}

//==============================================================================
//
// put()
//
//     Write formatted output to the given stream (similar to fprintf).
//
//==============================================================================

PRINTF_FORMAT(2, 3)
static void put(FILE* os, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(os, fmt, ap);
    va_end(ap);
}

//==============================================================================
//
// putl()
//
//     Similar to put() but adds a newline at the end.
//
//==============================================================================

PRINTF_FORMAT(2, 3)
static void putl(FILE* os, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(os, fmt, ap);
    va_end(ap);
    fputc('\n', os);
}

//==============================================================================
//
// Exists()
//
//     Return true if the given file exists.
//
//==============================================================================

static bool Exists(const char* path)
{
    return access(path, F_OK) == 0;
}

//==============================================================================
//
// ValidIdent()
//
//     Check whether the given string is a valid C identifier.
//
//==============================================================================

static bool ValidIdent(const string& s)
{
    const char* p = s.c_str();

    if (!isalpha((unsigned char)(*p)) && *p != '_')
        return false;

    p++;

    for (; *p; p++)
    {
        if (!isalnum((unsigned char)(*p)) && *p != '_')
            return false;
    }

    return true;
}

//==============================================================================
//
// Inhale()
//
//     Read the contents of the given file into memory.
//
//==============================================================================

static bool Inhale(const char* path, vector<char>& data)
{
    FILE* is = File_Open(path, "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(is);

    return true;
}

//==============================================================================
//
// puts()
//
//     Put a string onto the output stream.
//
//==============================================================================

static void puts(FILE* os, const string& s)
{
    fprintf(os, "%s", s.c_str());
}

//==============================================================================
//
// eqi()
//
//     Return true if the two strings are identical except for case.
//
//==============================================================================

static bool eqi(const char* s1, const char* s2)
{
    return Strcasecmp(s1, s2) == 0;
}

//==============================================================================
//
// nl()
//
//     Print a newline to the given stream.
//
//==============================================================================

inline void nl(FILE* os)
{
    fputc('\n', os);
}

//==============================================================================
//
// Generate a random key
//
//==============================================================================

#if 0

static MI_Uint64 _GetCurrentTime()
{
#if defined(CONFIG_OS_WINDOWS)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0X19DB1DED53E8000;
    return tmp.QuadPart / (UINT64)10;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return MI_RESULT_FAILED;

    return (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
#endif
}

static void _SleepMsec(MI_Uint64 msec)
{
#if defined(CONFIG_OS_WINDOWS)
    Sleep((DWORD)msec);
#else
    struct timespec rqtp;

    rqtp.tv_sec = static_cast<long>(msec/1000);
    rqtp.tv_nsec = static_cast<long>((msec%1000)*1000*1000);

    nanosleep(&rqtp, NULL);
#endif
}

static void _MakeID(char id[33])
{
    MI_Uint64 s1 = _GetCurrentTime();
    _SleepMsec(10);
    MI_Uint64 s2 = _GetCurrentTime();

    srand((unsigned int)(((s1 >> 32) ^ s1 ^ (s2 >> 32)) | s2));

    static const char XDIGITS[] =
    {
        '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    };

    for (size_t i = 0; i < 32; i++)
    {
        int x = rand() % 16;
        id[i] = XDIGITS[x];
    }

    id[32] = '\0';
}

#endif

//==============================================================================
//
// GeneratorOptions
//
//     This structure defines program options. These include:
//
//==============================================================================

static GeneratorOptions s_options;

static set<string> s_generated;

//==============================================================================
//
// GenStatikGenLine()
//
//==============================================================================

static void GenStatikGenLine(FILE* os)
{
    // Files generated by Statik may be located by searching for files which
    // contain the following string. The ampersands are separted into a format
    // argument to prevent this file (generator.cpp) from containg that string.
    fprintf(os, "/* %cmigen%c */\n", '@', '@');
}

//==============================================================================
//
// aliases
//
//     Maps MOF classnames to aliases. This map is built in main before 
//     classes are generated. The generator consults this table to determine 
//     the real name of the C structure (the alias) which may be different 
//     than the name of the MOF class.
//
//==============================================================================

typedef map<string, string> Aliases;
static Aliases aliases;

//==============================================================================
//
// Quote()
//
//     This function puts quotation marks around a string.
//
//==============================================================================

static string Quote(const string& str)
{
    return "MI_T(\"" + str + "\")";
}

//==============================================================================
//
// ExpandPath()
//
//     Obtain the full path (including directory given by optional -d option).
//
//==============================================================================

static string ExpandPath(const string& str)
{
    if (s_options.dir.size())
    {
        string r = s_options.dir + "/" + str;
        return s_options.dir + "/" + str;
    }
    else
        return str;
}

//==============================================================================
//
// Contains()
//
//     Return true if this vector contains the given string.
//
//==============================================================================

static bool Contains(const vector<string>& v, const string& s)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (s == v[i])
            return true;
    }

    return false;
}

//==============================================================================
//
// MakeFlags()
//
//     This function builds a flags expression from a bit mask. For example,
//     for a key property, the flag expression might look like this:
//
//         MI_FLAG_PROPERTY | MI_FLAG_KEY
//
//     Many structures have a flags field whose bits indicate the type of the
//     object (e.g., MI_FLAG_CLASS, MI_FLAG_METHOD, MI_FLAG_PROPERTY) as well 
//     as any boolean qualifiers whose values are true (e.g., MI_FLAG_KEY, 
//     MI_FLAG_IN, MI_FLAG_OUT).
//
//==============================================================================

static string MakeFlags(MI_Uint32 flags)
{
    struct
    {
        const char* name;
        MI_Uint32 flag;
    }
    _flags[] =
    {
        { "CLASS", MI_FLAG_CLASS },
        { "METHOD", MI_FLAG_METHOD },
        { "PROPERTY", MI_FLAG_PROPERTY },
        { "PARAMETER", MI_FLAG_PARAMETER },
        { "ASSOCIATION", MI_FLAG_ASSOCIATION },
        { "INDICATION", MI_FLAG_INDICATION },
        { "REFERENCE", MI_FLAG_REFERENCE },
        { "KEY", MI_FLAG_KEY },
        { "IN", MI_FLAG_IN },
        { "OUT", MI_FLAG_OUT },
        { "REQUIRED", MI_FLAG_REQUIRED },
        { "STATIC", MI_FLAG_STATIC },
        { "ABSTRACT", MI_FLAG_ABSTRACT },
        { "TERMINAL", MI_FLAG_TERMINAL },
        { "EXPENSIVE", MI_FLAG_EXPENSIVE },
        { "STREAM", MI_FLAG_STREAM },
        { "ENABLEOVERRIDE", MI_FLAG_ENABLEOVERRIDE },
        { "DISABLEOVERRIDE", MI_FLAG_DISABLEOVERRIDE },
        { "RESTRICTED", MI_FLAG_RESTRICTED},
        { "TOSUBCLASS", MI_FLAG_TOSUBCLASS},
        { "TRANSLATABLE", MI_FLAG_TRANSLATABLE},
    };

    string result;
    size_t count = 0;

    for (size_t i = 0; i < MI_COUNT(_flags); i++)
    {
        if (_flags[i].flag & flags)
        {
            if (count)
                result += "|";
            result += string("MI_FLAG_") + _flags[i].name;
            count++;
        }
    }

    if (result.size())
        return result;

    return "0";
}

//==============================================================================
//
// MakeFlavor()
//
//     This function builds a flavor string from the given flavor mask. For
//     example:
//
//         MI_FLAG_TOSUBCLASS | MI_FLAG_DISABLEOVERRIDE
//
//==============================================================================

static string MakeFlavor(MI_Uint32 flavor)
{
    struct
    {
        MI_Uint32 mask;
        const char* name;
    }
    _flavors[] =
    {
        { MI_FLAG_ENABLEOVERRIDE, "MI_FLAG_ENABLEOVERRIDE" },
        { MI_FLAG_DISABLEOVERRIDE, "MI_FLAG_DISABLEOVERRIDE" },
        { MI_FLAG_TOSUBCLASS, "MI_FLAG_TOSUBCLASS" },
        { MI_FLAG_TRANSLATABLE, "MI_FLAG_TRANSLATABLE" },
        { MI_FLAG_RESTRICTED, "MI_FLAG_RESTRICTED" },
    };

    string result;
    size_t count = 0;

    for (size_t i = 0; i < MI_COUNT(_flavors); i++)
    {
        if (_flavors[i].mask & flavor)
        {
            if (count)
                result += "|";
            result += _flavors[i].name;
            count++;
        }
    }

    if (result.size())
        return result;

    return "0";
}

//==============================================================================
//
// MakeScope()
//
//     This function builds a scope string from the given scope mask. For
//     example:
//
//         MI_FLAG_TOSUBCLASS | MI_FLAG_DISABLEOVERRIDE
//
//==============================================================================

static string MakeScope(MI_Uint32 scope)
{
    struct
    {
        MI_Uint32 mask;
        const char* name;
    }
    _scopes[] =
    {
        { MI_FLAG_ASSOCIATION, "MI_FLAG_ASSOCIATION" },
        { MI_FLAG_CLASS, "MI_FLAG_CLASS" },
        { MI_FLAG_INDICATION, "MI_FLAG_INDICATION" },
        { MI_FLAG_METHOD, "MI_FLAG_METHOD" },
        { MI_FLAG_PARAMETER, "MI_FLAG_PARAMETER" },
        { MI_FLAG_PROPERTY, "MI_FLAG_PROPERTY" },
        { MI_FLAG_REFERENCE, "MI_FLAG_REFERENCE" },
    };

    if ((scope & MI_FLAG_ANY) == MI_FLAG_ANY)
        return "MI_FLAG_ANY";

    string result;
    size_t count = 0;

    for (size_t i = 0; i < MI_COUNT(_scopes); i++)
    {
        if (_scopes[i].mask & scope)
        {
            if (count)
                result += "|";
            result += _scopes[i].name;
            count++;
        }
    }

    if (result.size())
        return result;

    return "0";
}

//==============================================================================
//
// MakeType()
//
//     This function returns the type tag string for the given Statik type
//     (given by the MI_Type structure). 
//
//==============================================================================

static string MakeType(MI_Uint32 type)
{
    switch (type)
    {
        case MI_BOOLEAN: return "MI_BOOLEAN";
        case MI_UINT8: return "MI_UINT8";
        case MI_SINT8: return "MI_SINT8";
        case MI_UINT16: return "MI_UINT16";
        case MI_SINT16: return "MI_SINT16";
        case MI_UINT32: return "MI_UINT32";
        case MI_SINT32: return "MI_SINT32";
        case MI_UINT64: return "MI_UINT64";
        case MI_SINT64: return "MI_SINT64";
        case MI_REAL32: return "MI_REAL32";
        case MI_REAL64: return "MI_REAL64";
        case MI_CHAR16: return "MI_CHAR16";
        case MI_DATETIME: return "MI_DATETIME";
        case MI_STRING: return "MI_STRING";
        case MI_REFERENCE: return "MI_REFERENCE";
        case MI_INSTANCE: return "MI_INSTANCE";
        case MI_BOOLEANA: return "MI_BOOLEANA";
        case MI_UINT8A: return "MI_UINT8A";
        case MI_SINT8A: return "MI_SINT8A";
        case MI_UINT16A: return "MI_UINT16A";
        case MI_SINT16A: return "MI_SINT16A";
        case MI_UINT32A: return "MI_UINT32A";
        case MI_SINT32A: return "MI_SINT32A";
        case MI_UINT64A: return "MI_UINT64A";
        case MI_SINT64A: return "MI_SINT64A";
        case MI_REAL32A: return "MI_REAL32A";
        case MI_REAL64A: return "MI_REAL64A";
        case MI_CHAR16A: return "MI_CHAR16A";
        case MI_DATETIMEA: return "MI_DATETIMEA";
        case MI_STRINGA: return "MI_STRINGA";
        case MI_REFERENCEA: return "MI_REFERENCEA";
        case MI_INSTANCEA: return "MI_INSTANCEA";
        default: return "UNKNOWN_TYPE";
    };
}

//==============================================================================
//
// AliasOf()
//
//     The the given class name is in the alias map, return the alias. 
//     Otherwise, just return the class name.
//
//==============================================================================

string AliasOf(const string& className)
{
    Aliases::const_iterator pos = aliases.find(className);

    if (pos != aliases.end())
        return (*pos).second;

    return className;
}

//==============================================================================
//
// PutRule()
//
//     Put a rule line (2 '*' characters followed by 78 '=' characters).
//
//==============================================================================

static void PutRule(FILE* os)
{
    put(os, "**");

    for (size_t i = 0; i < 78; i++)
        put(os, "=");

    nl(os);
}

//==============================================================================
//
// PutCommentBox()
//
//     Put a C comment box with a message in it.
//
//==============================================================================

static void PutCommentBox(FILE* os, const string& msg)
{
    putl(os, "/*");
    PutRule(os);
    putl(os, "**");
    putl(os, "** %s", msg.c_str());
    putl(os, "**");
    PutRule(os);
    putl(os, "*/");
}

//==============================================================================
//
// TypeNameOf()
//
//     Return the C type name for the given Statik type tag. For arrays type
//     tags, return the C type name of the element type. For example:
//
//         TypeNameOf(MI_UINT8) => "Uint8"
//         TypeNameOf(MI_UINT8A) => "Uint8"
// 
//==============================================================================

static const char* TypeNameOf(MI_Uint32 type)
{
    switch (type)
    {
        case MI_BOOLEAN:
            return "Boolean";
        case MI_SINT8:
            return "Sint8";
        case MI_UINT8:
            return "Uint8";
        case MI_SINT16:
            return "Sint16";
        case MI_UINT16:
            return "Uint16";
        case MI_SINT32:
            return "Sint32";
        case MI_UINT32:
            return "Uint32";
        case MI_SINT64:
            return "Sint64";
        case MI_UINT64:
            return "Uint64";
        case MI_REAL32:
            return "Real32";
        case MI_REAL64:
            return "Real64";
        case MI_CHAR16:
            return "Char16";
        case MI_DATETIME:
            return "Datetime";
        case MI_STRING:
            return "String";
        case MI_REFERENCE:
            return "Reference";
        case MI_INSTANCE:
            return "Instance";
        case MI_BOOLEANA:
            return "Boolean";
        case MI_SINT8A:
            return "Sint8";
        case MI_UINT8A:
            return "Uint8";
        case MI_SINT16A:
            return "Sint16";
        case MI_UINT16A:
            return "Uint16";
        case MI_SINT32A:
            return "Sint32";
        case MI_UINT32A:
            return "Uint32";
        case MI_SINT64A:
            return "Sint64";
        case MI_UINT64A:
            return "Uint64";
        case MI_REAL32A:
            return "Real32";
        case MI_REAL64A:
            return "Real64";
        case MI_CHAR16A:
            return "Char16";
        case MI_DATETIMEA:
            return "Datetime";
        case MI_STRINGA:
            return "String";
        case MI_REFERENCEA:
            return "Reference";
        case MI_INSTANCEA:
            return "Instance";
        default:
            return "UNKNOWN";
    }
}

//==============================================================================
//
// CountRefs()
//
//     Count how many roles (references) the given class has.
//
//==============================================================================

static size_t CountRefs(const MI_ClassDecl* cd)
{
    size_t r = 0;

    for (size_t i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        if (pd->type == MI_REFERENCE)
            r++;
    }

    return r;
}

//==============================================================================
//
// CanGenerateAssocRoles()
//
//     returns true if:
//  - association class has two references
//  - ref classes are not inherited from each other
//
//==============================================================================

static bool CanGenerateAssocRoles(const MI_ClassDecl* cd)
{
    if (2 != CountRefs(cd))
        return false;

    int index1 = -1, index2 = -1;

    for (int i = 0; i < (int)cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        if (pd->type == MI_REFERENCE)
        {
            if (-1 == index1)
                index1 = i;
            else 
                index2 = i;
        }
    }

    if (-1 == index2 ||
        !cd->properties[index1]->className ||
        !cd->properties[index2]->className)
        return false;

    return true;
}

//==============================================================================
//
// FullTypeNameOf()
//
//     Same as TypeNameOf() except that it gives the full typedef name.
//
//         TypeNameOf(MI_UINT8) => "MI_Uint8"
// 
//==============================================================================

static string FullTypeNameOf(MI_Uint32 type)
{
    return string("MI_") + TypeNameOf(type);
}

//==============================================================================
//
// CppTypeNameOf()
//
//     Return the Cpp type name for the given Statik type tag. For arrays type
//     tags, return the Cpp type name of the element type. For example:
//
//         CppTypeNameOf(MI_UINT8) => "Uint8"
//         CppTypeNameOf(MI_UINT8A) => "Uint8"
// 
//==============================================================================

const char* CppTypeNameOf(MI_Uint32 type)
{
    const char* res = TypeNameOf(type);

    return res;
}

//==============================================================================
//
// ScalarSizeOf()
//
//     Return the size of the given type; for arrays return the element size.
// 
//==============================================================================

INLINE MI_Uint32 ScalarSizeOf(MI_Uint32 type)
{
    return (MI_Uint32)Type_SizeOf(Type_ScalarOf(MI_Type(type)));
}

//==============================================================================
//
// sub()
//
//     Substitute all occurences of 'pattern' with 'replacement' within the
//     'str' parameter. Return the result.
// 
//==============================================================================

string sub(
    const string& str,
    const string& pattern,
    const string& replacement)
{
    size_t pos = 0;
    string r = str;

    while ((pos = r.find(pattern, pos)) != string::npos)
    {
        r = r.substr(0, pos) + replacement + r.substr(pos + pattern.size());
        pos += replacement.size();
    }

    return r;
}

//==============================================================================
//
// subu()
//
//     Similiar to sub() but substitutes an unsigned integer.
// 
//==============================================================================

static string subu(
    const string& str,
    const string& pattern,
    MI_Uint32 replacement)
{
    char buf[32];
    Snprintf(buf, sizeof(buf), "%u", replacement);
    return sub(str, pattern, buf);
}

//==============================================================================
//
// subx()
//
//     Similiar to sub() but substitutes an unsigned integer (as hex string).
// 
//==============================================================================

static string subx(
    const string& str,
    const string& pattern,
    MI_Uint32 replacement)
{
    char buf[32];
    Snprintf(buf, sizeof(buf), "0x%08X", replacement);
    return sub(str, pattern, buf);
}

//==============================================================================
//
// subd()
//
//     Substitute all occurences of 'pattern' with the string form of 
//     'replacement' within the 'str' parameter.
// 
//==============================================================================

#if 0
static string subd(
    const string& str,
    const string& pattern,
    MI_Sint32 replacement)
{
    char buf[32];
    Snprintf(buf, sizeof(buf), "%d", replacement);
    return sub(str, pattern, buf);
}
#endif

//==============================================================================
//
// FindStandardQualifierDecl()
//
//     Find the standard qualifier declaration with the given name.
// 
//==============================================================================

static const MI_QualifierDecl* FindStandardQualifierDecl(const char* name)
{
    for (size_t i = 0; i < g_numQualifierDecls; i++)
    {
        MI_QualifierDecl* qd = g_qualifierDecls[i];

        if (Strcasecmp(qd->name, name) == 0)
            return qd;
    }
    /* Not found! */
    return NULL;
}

//==============================================================================
//
// FindPropertyDecl()
//
//     Find the named property in the given class declarartion. Return a 
//     pointer if found, else return NULL.
// 
//==============================================================================

static const MI_PropertyDecl* FindPropertyDecl(
    const MI_ClassDecl* cd, 
    const char* name)
{
    for (size_t i = 0; i < cd->numProperties; i++)
    {
        if (Strcasecmp(cd->properties[i]->name, name) == 0)
            return cd->properties[i];
    }

    /* Not found */
    return NULL;
}

//==============================================================================
//
// ExistInstanceQualifier
//
//     returns 'true' if EmbeddedInstance/Object qualifier is set 
//
//==============================================================================
template< typename PropertyDeclType>
bool ExistInstanceQualifier(
    const PropertyDeclType* pd)
{
    for ( MI_Uint32 i = 0; i < pd->numQualifiers; i++ )
    {
        if (_Scasecmp(pd->qualifiers[i]->name,MI_T("EmbeddedInstance")) == 0)
            return true;
        if (_Scasecmp(pd->qualifiers[i]->name,MI_T("EmbeddedObject")) == 0)
            return true;
    }
    return false;
}

//==============================================================================
//
// IsPropertyRefOrInstance
//
//     returns 'true' if property (or parameter) is 
//      REFERENCE, REFERENCEA, EmbeddedInstance [arry], EmbeddedObject [array]
//
//==============================================================================
template< typename PropertyDeclType>
bool IsPropertyRefOrInstance(
    const PropertyDeclType* pd)
{

    if ((pd->type == MI_REFERENCE) || (pd->type == MI_REFERENCEA))
        return true;

    if ((pd->type == MI_INSTANCE) || (pd->type == MI_INSTANCEA))
        return true;

    if ((pd->type == MI_STRING) || (pd->type == MI_STRINGA))
        return ExistInstanceQualifier<PropertyDeclType>(pd);

    return false;
}

//==============================================================================
//
// GetPropertyClassname
//
//     returns 'class-name' of the property; only makes sense for 
//     REFERENCE, REFERENCEA, EmbeddedInstance [arry], EmbeddedObject [array]
//     for EmbeddedObject returns empty string
//
//==============================================================================
template< typename PropertyDeclType>
string GetPropertyClassname(
    const PropertyDeclType* pd)
{

    if ((pd->type == MI_REFERENCE) || (pd->type == MI_REFERENCEA))
        return pd->className;

    if ((pd->type == MI_INSTANCE) || (pd->type == MI_INSTANCEA))
        return pd->className ? pd->className : "";

    if ((pd->type == MI_STRING) || (pd->type == MI_STRINGA))
    {
        for ( MI_Uint32 i = 0; i < pd->numQualifiers; i++ )
        {
            if (_Scasecmp(pd->qualifiers[i]->name,MI_T("EmbeddedInstance"))==0)
            {
                if (pd->qualifiers[i]->type != MI_STRING)
                {
                    err(ID_EMBEDDEDINSTANCE_ON_NON_STRING,
                        "EmbeddedInstance qualifier on non-string type: %s",
                        pd->name);
                }

                return (const MI_Char*)pd->qualifiers[i]->value;
            }
            if (_Scasecmp(pd->qualifiers[i]->name,MI_T("EmbeddedObject")) == 0)
                return string();
        }
        return string();
    }

    return string();
}

//==============================================================================
//
// GenProperties()
//
//     This function writes properties for the MOF class currently being
//     generated (i.e., it generates fields for the corresponing C structure).
//     Properties are written in the order they are encountered when 
//     traversing from the root of the inheritance chain to the current class.
//     A property may be defined more than once in the inheritance chain due
//     to overriding. In that case, overrides by descendent classes have no
//     bearing on the order.
//
//==============================================================================

// Keeps track of property-name/class-name pairs.
typedef map<string,string> NameClassMap;
typedef pair<string,string> NameClassPair;

static void GenProperties(
    FILE* os,
    Parser& parser,
    const MI_ClassDecl* lcd, /* the leaf class in the recursion */
    const MI_ClassDecl* cd,
    NameClassMap& map)
{
    // Inject the property-name and class-name for all reference properties
    // first. During recursion we want to use the class-name of the most
    // derived reference declaration.

    for (size_t i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        if (pd->type == MI_REFERENCE)
        {
            if (map.find(pd->name) == map.end())
                map.insert(NameClassPair(pd->name, pd->className));
        }
    }

    // Recurse on superclass (if any) and print its properties first.
    if (cd->superClass)
    {
        const MI_ClassDecl* scd = parser.findClassDecl(cd->superClass);

        if (!scd)
            err(ID_UNKNOWN_SUPERCLASS_FOR, "unknown superclass for %s: %s", 
                cd->name, cd->superClass);

        GenProperties(os, parser, lcd, scd, map);
    }

    // Print the local properties of this class.
    putl(os, "    /* %s properties */", AliasOf(cd->name).c_str());

    for (size_t i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        // Skip non-local properties:
        if (Strcasecmp(cd->name, pd->origin) != 0)
            continue;

        // Indent this property.
        put(os, "    ");

        // Put the key attribute if the property in the leaf class has
        // the Key qualifier.
        {
            const MI_PropertyDecl* lpd = FindPropertyDecl(lcd, pd->name);

            if (lpd && (lpd->flags & MI_FLAG_KEY))
                put(os, "/*KEY*/ ");
        }

        if (pd->type == MI_REFERENCE)
        {
            // If a derived class defines this property, use the classname
            // that it uses for the property.

            NameClassMap::iterator p = map.find(pd->name);
            string al;

            if (p == map.end())
            {
                al = AliasOf(pd->className);
            }
            else
            {
                al = AliasOf((*p).second);
            }

            putl(os, "%s_ConstRef %s;", al.c_str(), pd->name);
        }
        else if (pd->type == MI_REFERENCEA)
        {
            err(ID_REFERENCE_ARRAY_AS_PROPERTY,
                "reference arrays are not allowed as properties");
        }
        else if (IsPropertyRefOrInstance(pd) && 
            !GetPropertyClassname(pd).empty())
        {   // embedded instance
            const string al = AliasOf(GetPropertyClassname(pd));

            if (pd->type & MI_ARRAY_BIT)
            {
                putl(os, "%s_ConstArrayRef %s;", al.c_str(), pd->name);
            }
            else
            {
                putl(os, "%s_ConstRef %s;", al.c_str(), pd->name);
            }
        }
        else if (IsPropertyRefOrInstance(pd) && GetPropertyClassname(pd).empty())
        {   // embedded object
            if (pd->type & MI_ARRAY_BIT)
            {
                putl(os, "MI_ConstReferenceAField %s;", pd->name);
            }
            else
            {
                putl(os, "MI_ConstReferenceField %s;", pd->name);
            }
        }
        else if (pd->type & MI_ARRAY_BIT)
        {
            putl(os, "MI_Const%sAField %s;", TypeNameOf(pd->type), 
                pd->name);
        }
        else
        {
            putl(os, "MI_Const%sField %s;", TypeNameOf(pd->type), 
                pd->name);
        }
    }
}

//==============================================================================
//
// GenSingleParameter()
//
//     This function generates the parameter structure, which holds the 
//     extrinsic method parameters that are passed to an extrinsic method 
//     provider stub. The return value is also defined in the structure whose
//     field name is "MIReturn".
//
//==============================================================================
static void GenSingleParameter(
    FILE* os,
    const MI_ParameterDecl* pd)
{
    if (pd->flags & MI_FLAG_IN && pd->flags & MI_FLAG_OUT)
        put(os, "    /*IN-OUT*/ ");
    else if (pd->flags & MI_FLAG_IN)
        put(os, "    /*IN*/ ");
    else if (pd->flags & MI_FLAG_OUT)
        put(os, "    /*OUT*/ ");

    if (IsPropertyRefOrInstance(pd) && !GetPropertyClassname(pd).empty())
    {
        const string al = AliasOf(GetPropertyClassname(pd));

        if (pd->type & MI_ARRAY_BIT)
        {
            putl(os, "%s_ConstArrayRef %s;", al.c_str(), pd->name);
        }
        else
        {
            putl(os, "%s_ConstRef %s;", al.c_str(), pd->name);
        }
    }
    else if (IsPropertyRefOrInstance(pd) && GetPropertyClassname(pd).empty())
    {   // embedded object
        if (pd->type & MI_ARRAY_BIT)
        {
            putl(os, "MI_ConstReferenceAField %s;", pd->name);
        }
        else
        {
            putl(os, "MI_ConstReferenceField %s;", pd->name);
        }
    }
    else if (pd->type & MI_ARRAY_BIT)
    {
        putl(os, "MI_Const%sAField %s;", TypeNameOf(pd->type), 
            pd->name);
    }
    else
    {
        putl(os, "MI_Const%sField %s;", TypeNameOf(pd->type), 
            pd->name);
    }
}
//==============================================================================
//
// GenParameters()
//
//     This function generates MOF method parameters (i.e., C fields for the
//     parameters structure).
//
//==============================================================================

static void GenParameters(
    FILE* os,
    const MI_ClassDecl* cd,
    const MI_MethodDecl* md)
{
    for (size_t i = 0; i < md->numParameters; i++)
    {
        const MI_ParameterDecl* pd = md->parameters[i];

        // Skip stream parameters:
        if (pd->flags & MI_FLAG_STREAM)
        {
            if (!(pd->type & MI_ARRAY_BIT))
            {
                err(ID_STREAM_QUALIFIER_ON_NON_ARRAY, 
                    "'Stream' qualifiers may only appear on array parameters: "
                    "%s.%s(): %s",
                    cd->name, md->name, pd->name);
            }

            if (!(pd->flags & MI_FLAG_OUT))
            {
                err(ID_STREAM_QUALIFIER_ON_NON_OUTPUT, 
                    "'Stream' qualifiers may only appear on output parameters: "
                    "%s.%s(): %s",
                    cd->name, md->name, pd->name);
            }
            continue;
        }

        // Reject properties named "MIReturn".
        if (Strcasecmp(pd->name, "MIReturn") == 0)
        {
            err(ID_RESERVED_PARAMETER_NAME, 
                "reserved parameter name: %s.%s(): %s", cd->name, md->name, 
                pd->name);
        }

        GenSingleParameter(os,pd);
    }
}


//==============================================================================
//
// GenParametersStruct()
//
//     This function generates the parameters structure, which holds the 
//     extrinsic method parameters that are passed to an extrinsic method 
//     provider stub. The return value is also defined in the structure whose
//     field name is "MIReturn".
//
//==============================================================================

static void GenParametersStruct(
    FILE* os,
    const MI_ClassDecl* cd, 
    const MI_MethodDecl* md)
{
    const string alias = AliasOf(cd->name);

    // Put comment box for the parameter structure name.
    const string str = alias + "." + md->name +  "()";
    PutCommentBox(os, str);
    nl(os);

    // Put method structure definition.
    putl(os, "typedef struct _%s_%s", alias.c_str(), md->name);
    putl(os, "{");
    putl(os, "    MI_Instance __instance;");

    {
        MI_ParameterDecl pd;
        memset(&pd, 0, sizeof(pd));
        pd.flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
        pd.name = (char*)"MIReturn";
        pd.type = md->returnType;
        pd.offset = sizeof(MI_Instance);
        pd.numQualifiers = md->numQualifiers;
        pd.qualifiers = md->qualifiers;
        GenSingleParameter(os,&pd);
    }
    GenParameters(os, cd, md);
    putl(os, "}");
    putl(os, "%s_%s;", alias.c_str(), md->name);
    nl(os);
}

//==============================================================================
//
// GenSetter()
//
//     This function generates the 'setter' convenience functions for the 
//     given class property or method parameter.
//
//==============================================================================

static void GenSetter(
    FILE* os, 
    const MI_ClassDecl* cd,
    const MI_MethodDecl* md,
    const MI_ParameterDecl* pd)
{
    const string alias = AliasOf(cd->name);
    string r,r_ptr;
    MI_Uint32 index = (MI_Uint32)-1;

    // Form the structure prefix (<ALIAS> for classes, <ALIAS><METH> for
    // methods.
    string prefix = alias;

    if (md)
    {
        prefix += "_";
        prefix += md->name;
    }

    // Find index of this property.
    if (md)
    {
        if (strcmp(pd->name, "MIReturn") == 0)
        {
            index = 0;
        }
        else
        {
            for (MI_Uint32 i = 0; i < md->numParameters; i++)
            {
                if (md->parameters[i] == pd)
                {
                    index = i;
                    break;
                }
            }

            // Increment parameter index to make room for insertion of
            // the "MIReturn" pseudo-parameter.
            index++;
        }
    }
    else
    {
        for (MI_Uint32 i = 0; i < cd->numProperties; i++)
        {
            if (cd->properties[i] == (MI_PropertyDecl*)pd)
            {
                index = i;
                break;
            }
        }
    }

    if (index == (MI_Uint32)-1)
        err(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);

    // Generate *_Set_* and *_SetPtr_* functions.

    if (pd->type & MI_ARRAY_BIT)
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX><SET><PROP>(\n"
            "    <PREFIX>* self,\n"
            "    const <TYPEEXPR>* data,\n"
            "    MI_Uint32 size)\n"
            "{\n"
            "    MI_Array arr;\n"
            "    arr.data = (void*)data;\n"
            "    arr.size = size;\n"
            "    return self->__instance.ft->SetElementAt(\n"
            "        (MI_Instance*)&self->__instance,\n"
            "        <INDEX>,\n"
            "        (MI_Value*)&arr,\n"
            "        <TYPE>,\n"
            "        <COPY_FLAG>);\n"
            "}\n"
            "\n";

        r = T;

        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = subu(r, "<INDEX>", index);

        if (pd->type == MI_REFERENCEA)
            r = sub(r, "<TYPEEXPR>", AliasOf(pd->className) + "* const");
        else if (pd->type == MI_STRINGA && IsPropertyRefOrInstance(pd) && !GetPropertyClassname(pd).empty())
        {
            r = sub(r, "<TYPEEXPR>", AliasOf(GetPropertyClassname(pd)) + string(" * const "));
            r = sub(r, "<TYPE>", "MI_INSTANCEA");
        }
        else if (pd->type == MI_STRINGA && IsPropertyRefOrInstance(pd) && GetPropertyClassname(pd).empty())
        {
            r = sub(r, "<TYPEEXPR>", "MI_Instance * const ");
            r = sub(r, "<TYPE>", "MI_INSTANCEA");
        }
        else if (pd->type == MI_STRINGA)
            r = sub(r, "<TYPEEXPR>", "MI_Char*");
        else
            r = sub(r, "<TYPEEXPR>", FullTypeNameOf(pd->type));

        r = sub(r, "<TYPE>", MakeType(pd->type));

        r_ptr = r;
        // non-copying version has to be created from initial template
        // otherwise name conflict is possible if function name is 'Set'
        r = sub(r, "<SET>", "_Set_");
        r = sub(r, "<COPY_FLAG>", "0");
        r_ptr = sub(r_ptr, "<SET>", "_SetPtr_");
        r_ptr = sub(r_ptr, "<COPY_FLAG>", "MI_FLAG_BORROW");
        puts(os, r);
        puts(os, r_ptr);
    }
    else if (IsPropertyRefOrInstance(pd))
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX><SET><PROP>(\n"
            "    <PREFIX>* self,\n"
            "    const <REFCLASSNAME>* x)\n"
            "{\n"
            "    return self->__instance.ft->SetElementAt(\n"
            "        (MI_Instance*)&self->__instance,\n"
            "        <INDEX>,\n"
            "        (MI_Value*)&x,\n"
            "        <TYPE>,\n"
            "        <COPY_FLAG>);\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = subu(r, "<INDEX>", index);
        r = sub(r, "<TYPE>", pd->type == MI_REFERENCE ? "MI_REFERENCE" : "MI_INSTANCE");

        if (!GetPropertyClassname(pd).empty())
            r = sub(r, "<REFCLASSNAME>", AliasOf(GetPropertyClassname(pd)));
        else
            r = sub(r, "<REFCLASSNAME>", "MI_Instance");

        r_ptr = r;
        // non-copying version has to be created from initial template
        // otherwise name conflict is possible if function name is 'Set'
        r = sub(r, "<SET>", "_Set_");
        r = sub(r, "<COPY_FLAG>", "0");
        r_ptr = sub(r_ptr, "<SET>", "_SetPtr_");
        r_ptr = sub(r_ptr, "<COPY_FLAG>", "MI_FLAG_BORROW");
        puts(os, r);
        puts(os, r_ptr);
    }
    else if (pd->type == MI_STRING)
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX><SET><PROP>(\n"
            "    <PREFIX>* self,\n"
            "    const MI_Char* str)\n"
            "{\n"
            "    return self->__instance.ft->SetElementAt(\n"
            "        (MI_Instance*)&self->__instance,\n"
            "        <INDEX>,\n"
            "        (MI_Value*)&str,\n"
            "        MI_STRING,\n"
            "        <COPY_FLAG>);\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = subu(r, "<INDEX>", index);

        r_ptr = r;
        // non-copying version has to be created from initial template
        // otherwise name conflict is possible if function name is 'Set'
        r = sub(r, "<SET>", "_Set_");
        r = sub(r, "<COPY_FLAG>", "0");
        r_ptr = sub(r_ptr, "<SET>", "_SetPtr_");
        r_ptr = sub(r_ptr, "<COPY_FLAG>", "MI_FLAG_BORROW");
        puts(os, r);
        puts(os, r_ptr);
    }
    else
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX>_Set_<PROP>(\n"
            "    <PREFIX>* self,\n"
            "    MI_<TYPENAME> x)\n"
            "{\n"
            "    ((MI_<TYPENAME>Field*)&self-><PROP>)->value = x;\n"
            "    ((MI_<TYPENAME>Field*)&self-><PROP>)->exists = 1;\n"
            "    return MI_RESULT_OK;\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = sub(r, "<TYPENAME>", TypeNameOf(pd->type));
        puts(os, r);
    }

    // Generate *_Clear_* function.

    if ((pd->type & MI_ARRAY_BIT) != 0 || 
        pd->type == MI_STRING || 
        pd->type == MI_REFERENCE ||
        pd->type == MI_INSTANCE)
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX>_Clear_<PROP>(\n"
            "    <PREFIX>* self)\n"
            "{\n"
            "    return self->__instance.ft->ClearElementAt(\n"
            "        (MI_Instance*)&self->__instance,\n"
            "        <INDEX>);\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = subu(r, "<INDEX>", index);
        puts(os, r);
    }
    else
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX>_Clear_<PROP>(\n"
            "    <PREFIX>* self)\n"
            "{\n"
            "    memset((void*)&self-><PROP>, 0, sizeof(self-><PROP>));\n"
            "    return MI_RESULT_OK;\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        puts(os, r);
    }

#if 0
    // Generate function to obtain the flags for this property:
    {
        const char T[] =
            "MI_INLINE MI_Result MI_CALL <PREFIX>_GetFlags_<PROP>(\n"
            "    const <PREFIX>* self,\n"
            "    MI_Uint32* flags)\n"
            "{\n"
            "    return self->__instance.ft->GetElementAt(&self->__instance,\n"
            "        <INDEX>, NULL, NULL, NULL, flags);\n"
            "}\n"
            "\n";

        r = T;
        r = sub(r, "<PREFIX>", prefix);
        r = sub(r, "<PROP>", pd->name);
        r = subu(r, "<INDEX>", index);
        puts(os, r);
    }
#endif
}

//==============================================================================
//
// GenInstanceFunctions()
//
//     This function generates the 'initInstance' convenience function for the 
//     given class. 
//
//==============================================================================

static void GenInstanceFunctions(
    FILE* os, 
    const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    const char T[] =
        "MI_INLINE MI_Result MI_CALL <ALIAS>_Construct(\n"
        "    <ALIAS>* self,\n"
        "    MI_Context* context)\n"
        "{\n"
        "    return MI_ConstructInstance(context, &<ALIAS>_rtti,\n"
        "        (MI_Instance*)&self->__instance);\n"
        "}\n"
        "\n"
        "MI_INLINE MI_Result MI_CALL <ALIAS>_Clone(\n"
        "    const <ALIAS>* self,\n"
        "    <ALIAS>** newInstance)\n"
        "{\n"
        "    return MI_Instance_Clone(\n"
        "        &self->__instance, (MI_Instance**)newInstance);\n"
        "}\n"
        "\n"
        "MI_INLINE MI_Boolean MI_CALL <ALIAS>_IsA(\n"
        "    const MI_Instance* self)\n"
        "{\n"
        "    MI_Boolean res = MI_FALSE;\n"
        "    return MI_Instance_IsA(self, &<ALIAS>_rtti, &res) == MI_RESULT_OK && res;\n"
        "}\n"
        "\n"
        "MI_INLINE MI_Result MI_CALL <ALIAS>_Destruct(<ALIAS>* self)\n"
        "{\n"
        "    return MI_Instance_Destruct(&self->__instance);\n"
        "}\n"
        "\n"
        "MI_INLINE MI_Result MI_CALL <ALIAS>_Delete(<ALIAS>* self)\n"
        "{\n"
        "    return MI_Instance_Delete(&self->__instance);\n"
        "}\n"
        "\n";

    string r = T;
    if (cd->flags & MI_FLAG_INDICATION)
    {
        r += "MI_INLINE MI_Result MI_CALL <ALIAS>_Post(\n"
        "    const <ALIAS>* self,\n"
        "    MI_Context* context,\n"
        "    MI_Uint32 subscriptionIDCount,\n"
        "    const MI_Char* bookmark)\n"
        "{\n"
        "    return MI_Context_PostIndication(context, &self->__instance, subscriptionIDCount, bookmark);\n"
        "}\n"
        "\n";
    }
    else
    {
        r += "MI_INLINE MI_Result MI_CALL <ALIAS>_Post(\n"
        "    const <ALIAS>* self,\n"
        "    MI_Context* context)\n"
        "{\n"
        "    return MI_PostInstance(context, &self->__instance);\n"
        "}\n"
        "\n";
    }
    r = sub(r, "<ALIAS>", alias);
    puts(os, r);
}

//==============================================================================
//
// GenMethodFunctions()
//
//     This function generates convenience functions for the given method.
//
//==============================================================================

static void GenMethodFunctions(
    FILE* os, 
    const MI_ClassDecl* cd,
    const MI_MethodDecl* md)
{
    const string alias = AliasOf(cd->name);

    const char T[] =
    "MI_EXTERN_C MI_CONST MI_MethodDecl <ALIAS>_<METH>_rtti;\n"
    "\n"
    "MI_INLINE MI_Result MI_CALL <ALIAS>_<METH>_Construct(\n"
    "    <ALIAS>_<METH>* self,\n"
    "    MI_Context* context)\n"
    "{\n"
    "    return MI_ConstructParameters(context, &<ALIAS>_<METH>_rtti,\n"
    "        (MI_Instance*)&self->__instance);\n"
    "}\n"
    "\n"
    "MI_INLINE MI_Result MI_CALL <ALIAS>_<METH>_Clone(\n"
    "    const <ALIAS>_<METH>* self,\n"
    "    <ALIAS>_<METH>** newInstance)\n"
    "{\n"
    "    return MI_Instance_Clone(\n"
    "        &self->__instance, (MI_Instance**)newInstance);\n"
    "}\n"
    "\n"
    "MI_INLINE MI_Result MI_CALL <ALIAS>_<METH>_Destruct(\n"
    "    <ALIAS>_<METH>* self)\n"
    "{\n"
    "    return MI_Instance_Destruct(&self->__instance);\n"
    "}\n"
    "\n"
    "MI_INLINE MI_Result MI_CALL <ALIAS>_<METH>_Delete(\n"
    "    <ALIAS>_<METH>* self)\n"
    "{\n"
    "    return MI_Instance_Delete(&self->__instance);\n"
    "}\n"
    "\n"
    "MI_INLINE MI_Result MI_CALL <ALIAS>_<METH>_Post(\n"
    "    const <ALIAS>_<METH>* self,\n"
    "    MI_Context* context)\n"
    "{\n"
    "    return MI_PostInstance(context, &self->__instance);\n"
    "}\n"
    "\n";

    string r = T;
    r = sub(r, "<ALIAS>", alias);
    r = sub(r, "<METH>", md->name);
    puts(os, r);
}

//==============================================================================
//
// FindDirectDependencies
//
//     Find classes that this class depends (via superclasses and references).
//
//==============================================================================

static void FindDirectDependencies(
    const MI_ClassDecl* cd, 
    vector<string>& deps)
{
    // Find super classes.
    if (cd->superClass)
        deps.push_back(cd->superClass);

    // Find property reference dependencies.
    for (MI_Uint32 i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];

        if (IsPropertyRefOrInstance(pd))
        {
            string cn = GetPropertyClassname(pd);

            if (!cn.empty() && !Contains(deps, cn))
                deps.push_back(cn);
        }
    }

    // Find parameter reference dependencies.
    for (MI_Uint32 i = 0; i < cd->numMethods; i++)
    {
        MI_MethodDecl* md = cd->methods[i];

        // check return type
        {
            MI_ParameterDecl pd;
            memset(&pd, 0, sizeof(pd));
            pd.flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
            pd.name = (char*)"MIReturn";
            pd.type = md->returnType;
            pd.offset = sizeof(MI_Instance);
            pd.numQualifiers = md->numQualifiers;
            pd.qualifiers = md->qualifiers;
            
            if (IsPropertyRefOrInstance(&pd))
            {
                string cn = GetPropertyClassname(&pd);

                if (!cn.empty() && !Contains(deps, cn))
                    deps.push_back(cn);
            }
        }

        for (MI_Uint32 j = 0; j < md->numParameters; j++)
        {
            MI_ParameterDecl* pd = md->parameters[j];

            if (IsPropertyRefOrInstance(pd))
            {
                string cn = GetPropertyClassname(pd);

                if (!cn.empty() && !Contains(deps, cn))
                    deps.push_back(cn);
            }
        }
    }
}

//==============================================================================
//
// PutCppPropertyAccessor
//
//     Generate inline functions to access a single property
//
//==============================================================================
template< typename PropertyDeclType>
void PutCppPropertyAccessor(
    FILE* os,
    const PropertyDeclType* pd,
    const string& alias)
{
    const char T[] =
        "    //\n"
        "    // =ALIAS=_Class.=NAME=\n"
        "    //\n"
        "    \n"
        "    const Field<=TYPE=>& =NAME=() const\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        return GetField<=TYPE=>(n);\n"
        "    }\n"
        "    \n"
        "    void =NAME=(const Field<=TYPE=>& x)\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        GetField<=TYPE=>(n) = x;\n"
        "    }\n"
        "    \n"
        "    const =TYPE=& =NAME=_value() const\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        return GetField<=TYPE=>(n).value;\n"
        "    }\n"
        "    \n"
        "    void =NAME=_value(const =TYPE=& x)\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        GetField<=TYPE=>(n).Set(x);\n"
        "    }\n"
        "    \n"
        "    bool =NAME=_exists() const\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        return GetField<=TYPE=>(n).exists ? true : false;\n"
        "    }\n"
        "    \n"
        "    void =NAME=_clear()\n"
        "    {\n"
        "        const size_t n = offsetof(Self, =NAME=);\n"
        "        GetField<=TYPE=>(n).Clear();\n"
        "    }\n";

    string r = sub(T, "=ALIAS=", alias);

    if (IsPropertyRefOrInstance<PropertyDeclType>(pd) && 
        !GetPropertyClassname<PropertyDeclType>(pd).empty())
    {
        const string al = AliasOf(GetPropertyClassname<PropertyDeclType>(pd));

        if (pd->type & MI_ARRAY_BIT)
        {
            r = sub(r, "=TYPE=", al + "_ClassA");
        }
        else
        {
            r = sub(r, "=TYPE=", al + "_Class");
        }
    }
    else if (IsPropertyRefOrInstance<PropertyDeclType>(pd) && 
        GetPropertyClassname<PropertyDeclType>(pd).empty())
    {   // embedded object
        const string al = AliasOf(GetPropertyClassname<PropertyDeclType>(pd));

        if (pd->type & MI_ARRAY_BIT)
            r = sub(r, "=TYPE=", "InstanceA");
        else
            r = sub(r, "=TYPE=", "Instance");
    }
    else if (pd->type & MI_ARRAY_BIT)
    {
        r = sub(r, "=TYPE=", string(CppTypeNameOf(pd->type)) + "A");
    }
    else
    {
        r = sub(r, "=TYPE=", CppTypeNameOf(pd->type));
    }

    r = sub(r, "=NAME=", pd->name);

    puts(os, r);
}

//==============================================================================
//
// getReturnType
//
//     returns 'return-type' for funciton declaration; for instances return false
//
//==============================================================================
template< typename ClassDeclType, typename PropertyDeclType>
bool getReturnType(const ClassDeclType* cd, MI_Uint32& type);

template<>
bool getReturnType<MI_ClassDecl,_MI_PropertyDecl>(
    const MI_ClassDecl* , 
    MI_Uint32& )
{
    return false;
}

template<>
bool getReturnType<MI_MethodDecl,_MI_ParameterDecl>(
    const MI_MethodDecl* cd, 
    MI_Uint32& type)
{
    type = cd->returnType;
    return true;
}

//==============================================================================
//
// isPropertyLocal
//
//     checks if rpoerty is local
//
//==============================================================================
template< typename ClassDeclType, typename PropertyDeclType>
bool isPropertyLocal(const ClassDeclType* , const PropertyDeclType* );

template<>
bool isPropertyLocal<MI_ClassDecl,_MI_PropertyDecl>(
    const MI_ClassDecl* cd, 
    const _MI_PropertyDecl* pd)
{
    return Strcasecmp(cd->name, pd->origin) == 0;
}

template<>
bool isPropertyLocal<MI_MethodDecl,_MI_ParameterDecl>(
    const MI_MethodDecl*, 
    const _MI_ParameterDecl*)
{
    return true;
}

//==============================================================================
//
// HashKeys()
//
//     Return true if the given class declaration has any key properties.
//
//==============================================================================

static bool HasKeys(const MI_ClassDecl* cd)
{
    for (MI_Uint32 i = 0; i < cd->numProperties; i++)
    {
        if (cd->properties[i]->flags & MI_FLAG_KEY)
            return true;
    }

    // No keys found!
    return false;
}

//==============================================================================
//
// GenCppPropertiesAccessors
//
//     Generate C++ class property accessors funciotns
//
//==============================================================================
template< typename ClassDeclType, typename PropertyDeclType>
void GenCppPropertiesAccessors(
    FILE* os,
    const ClassDeclType* cd,
    const string& alias,
    size_t numProperties,
    PropertyDeclType** const properties )
{
    // Print the local properties of this class.
    {
        // put MIReturn if it's a method
        MI_Uint32 type = 0;
        if (getReturnType<ClassDeclType, PropertyDeclType>(cd,type))
        {
            MI_ParameterDecl pd;
            memset(&pd, 0, sizeof(pd));
            pd.flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
            pd.name = (char*)"MIReturn";
            pd.type = type;
            pd.offset = sizeof(MI_Instance);
            pd.numQualifiers = cd->numQualifiers;
            pd.qualifiers = cd->qualifiers;

            PutCppPropertyAccessor<MI_ParameterDecl>(os,&pd,alias);

            if (numProperties)
                nl(os);
        }
    }

    for (size_t i = 0; i < numProperties; i++)
    {
        const PropertyDeclType* pd = properties[i];

        // Skip non-local properties:
        if (!isPropertyLocal(cd,pd))
            continue;

        // Skip stream parameters:
        if (pd->flags & MI_FLAG_STREAM)
            continue;

        // generate skeleton
        PutCppPropertyAccessor<PropertyDeclType>(os,pd,alias);

        if (i +1 != numProperties)
            nl(os);
    }
}

//==============================================================================
//
// GenCppClassDeclaration
//
//     Generate C++ class
//
//==============================================================================
template< typename ClassDeclType, typename PropertyDeclType>
void GenCppClassDeclaration(
    FILE* os,
    const ClassDeclType* cd,
    const string& alias,
    const char* superClass,
    size_t numProperties,
    PropertyDeclType** const properties )
{
    ////////////////////////////////////////
    // class definition
    {
        const char T[] =
        "class <ALIAS>_Class : public <BASE>\n"
        "{\n"
        "public:\n"
        "    \n"
        "    typedef <ALIAS> Self;\n"
        "    \n"
        "    <ALIAS>_Class() :\n"
        "        <BASE>(&<ALIAS>_rtti)\n"
        "    {\n"
        "    }\n"
        "    \n"
        "    <ALIAS>_Class(\n"
        "        const <ALIAS>* instanceName,\n"
        "        bool keysOnly) :\n"
        "        <BASE>(\n"
        "            &<ALIAS>_rtti,\n"
        "            &instanceName->__instance,\n"
        "            keysOnly)\n"
        "    {\n"
        "    }\n"
        "    \n"
        "    <ALIAS>_Class(\n"
        "        const MI_ClassDecl* clDecl,\n"
        "        const MI_Instance* instance,\n"
        "        bool keysOnly) :\n"
        "        <BASE>(clDecl, instance, keysOnly)\n"
        "    {\n"
        "    }\n"
        "    \n"
        "    <ALIAS>_Class(\n"
        "        const MI_ClassDecl* clDecl) :\n"
        "        <BASE>(clDecl)\n"
        "    {\n"
        "    }\n"
        "    \n"
        "    <ALIAS>_Class& operator=(\n"
        "        const <ALIAS>_Class& x)\n"
        "    {\n"
        "        CopyRef(x);\n"
        "        return *this;\n"
        "    }\n"
        "    \n"
        "    <ALIAS>_Class(\n"
        "        const <ALIAS>_Class& x) :\n"
        "        <BASE>(x)\n"
        "    {\n"
        "    }\n"
        "\n";
        const char S[] =
        "    static const MI_ClassDecl* GetClassDecl()\n"
        "    {\n"
        "        return &<ALIAS>_rtti;\n"
        "    }\n"
        "\n";

        string r = sub(T, "<ALIAS>", alias);

        if (superClass)
        {
            string tmp = AliasOf(superClass) + "_Class";
            r = sub(r, "<BASE>", tmp);
        }
        else
        {
            r = sub(r, "<BASE>", "Instance");
        }
        puts(os, r);

        if (cd->flags & MI_FLAG_CLASS)
        {
            r = sub(S, "<ALIAS>", alias);
            puts(os, r);
        }

    }

    /// inline funciotns for property access
    GenCppPropertiesAccessors<ClassDeclType,PropertyDeclType>(
        os,cd,alias,numProperties,properties);

    /// end class
    {
        const char T[] =
            "};\n"
            "\n"
            "typedef Array<<ALIAS>_Class> <ALIAS>_ClassA;\n"
            "\n"
            ;

        string r = sub(T, "<ALIAS>", alias);
        puts(os, r);
    }
}

//==============================================================================
//
// SubRoles()
//
//     Substitute <ROLE1>, <ROLE2>, <ALIAS1>, and <ALIAS2> with
//     property names and classnames for the first and second references 
//     (roles) in this class.
//
//==============================================================================

static void SubRoles(const MI_ClassDecl* cd, string& r)
{
    size_t role = 1;

    for (size_t i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        if (pd->type == MI_REFERENCE)
        {
            if (role == 1)
            {
                r = sub(r, "<ROLE1>", pd->name);
                r = sub(r, "<ALIAS1>", AliasOf(pd->className).c_str());
                role++;
            }
            else if (role == 2)
            {
                r = sub(r, "<ROLE2>", pd->name);
                r = sub(r, "<ALIAS2>", AliasOf(pd->className).c_str());
                role++;
            }
            else if (role == 3)
            {
                err(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, 
                    __LINE__);
            }
        }
    }
}

//==============================================================================
//
// GenCppClassProviderHeaderNewFile
//
//     Generate class provider declaration 
//     used only to create a new file
//
//==============================================================================
static void GenCppClassProviderHeaderNewFile(
    FILE* os,
    const MI_ClassDecl* cd)
{
    string alias = AliasOf(cd->name);
    GenStatikGenLine(os);

    // Prevent multiple inclusion.
    putl(os, "#ifndef _%s_Class_Provider_h", alias.c_str());
    putl(os, "#define _%s_Class_Provider_h", alias.c_str());
    nl(os);

    // Include instance class
    putl(os, "#include \"%s.h\"", alias.c_str());


    // standard starting part
    putl(os, "#ifdef __cplusplus");
    putl(os, "# include <micxx/micxx.h>");
    putl(os, "# include \"module.h\"");
    nl(os);
    putl(os, "MI_BEGIN_NAMESPACE");
    nl(os);


    // Write the intrinsic provider function prototypes.
    {
        PutCommentBox(os, alias + " provider class declaration");
        nl(os);

        // Generate forward typedef for Self structure.
        string extraDataMemebers;
        
        if (cd->flags & MI_FLAG_ASSOCIATION)
        {
            string r;

            if (CanGenerateAssocRoles(cd))
            {
                if (!s_options.association)
                {
                    r = ASSOCIATION_PROVIDER_CLASS_DECLARATION_ROLES;
                    SubRoles(cd, r);
                }
                else
                    r = ASSOCIATION_PROVIDER_CLASS_DECLARATION;
            }
            else
                errRefPropCount(cd->name);

            r = sub(r, "<ALIAS>", alias);
            r = sub(r, "<DATA_MEMBERS>", extraDataMemebers);
            puts(os, r);
        }
        else if (cd->flags & MI_FLAG_INDICATION)
        {
            string r = INDICATION_PROVIDER_CLASS_DECLARATION;
            extraDataMemebers = "    MI_Context* m_IndicationsContext;\n";
            r = sub(r, "<ALIAS>", alias);
            r = sub(r, "<DATA_MEMBERS>", extraDataMemebers);
            puts(os, r);
        }
        else
        {
            string r = INSTANCE_PROVIDER_CLASS_DECLARATION;
            r = sub(r, "<ALIAS>", alias);
            r = sub(r, "<DATA_MEMBERS>", extraDataMemebers);
            puts(os, r);
        }
    }

    // Write the extrinsic provider function prototypes.
    {
        for (size_t i = 0; i < cd->numMethods; i++)
        {
            const MI_MethodDecl* md = cd->methods[i];
            string r = sub(EXTRINSIC_METHOD_PROVIDER_CLASS_DECLARATION, 
                "<ALIAS>", alias);
            r = sub(r, "<METHOD>", md->name);
            puts(os, r);
        }
    }

    // close class declaration
    putl(os, COMMON_PROVIDER_CLASS_DECLARATION_END);
    putl(os,"};");
    nl(os);


    // end c++ specific part
    putl(os, "MI_END_NAMESPACE");
    nl(os);
    putl(os, "#endif /* __cplusplus */");
    nl(os);
    putl(os, "#endif /* _%s_Class_Provider_h */", alias.c_str());
    nl(os);
}

//==============================================================================
//
// GenCppClassProviderHeader
//
//     Generate class provider declaration 
//     Support patching of methods
//
//==============================================================================
static void GenCppClassProviderHeader(
    const MI_ClassDecl* cd)
{
    string alias = AliasOf(cd->name);

    // create/patch provider class declaration file.
    const string path = ExpandPath(alias + "_Class_Provider.h");
    bool append;
    vector<char> data;
    {
        append = Exists(path.c_str());

        if (append)
        {
            if (!Inhale(path.c_str(), data))
            {
                err(ID_FAILED_TO_READ_FILE, "failed to read file: %s", 
                    path.c_str());
            }
        }
        else
        {
            FILE* os = File_Open(path.c_str(), "w");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                    path.c_str());
            }

            Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());
            GenCppClassProviderHeaderNewFile(os,cd);
            fclose(os);
            return;
        }
    }


    // patch existing file
    data.push_back(0);
    string str_data = &data[0];

    /* remove \r*/
    str_data = sub(str_data, "\r", "");

    if (str_data.find(COMMON_PROVIDER_CLASS_DECLARATION_END) == string::npos)
    {
        err(ID_FAILED_TO_FIND_PATCH_MARKER,
            "failed to find patch marker (%s) in file %s",
            COMMON_PROVIDER_CLASS_DECLARATION_END,
            path.c_str());
    }

    bool patched = false;

    // Add Load/Unload functions if missing
    if (str_data.find("void Unload(") == string::npos)
    {
        if (!patched)
        {
            Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
            patched = true;
        }

        str_data = sub(str_data, COMMON_PROVIDER_CLASS_DECLARATION_END, 
            COMMON_PROVIDER_LOAD_UNLOAD_DECLARATION  COMMON_PROVIDER_CLASS_DECLARATION_END);
    }

    // Generate extrinsic method declarations (only new one).
    for (size_t i = 0; i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];
        string r = sub(EXTRINSIC_METHOD_PROVIDER_CLASS_DECLARATION, "<ALIAS>", 
            alias);
        r = sub(r, "<METHOD>", md->name);

        string name = string("Invoke_") + md->name;

        // Skip methods already found in file.
        if (str_data.find(name) != string::npos)
            continue;

        if (!patched)
        {
            Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
            patched = true;
        }

        str_data = sub(str_data, COMMON_PROVIDER_CLASS_DECLARATION_END, 
            r + COMMON_PROVIDER_CLASS_DECLARATION_END);
    }

    if (!patched)
    {
        Fprintf(s_stdout, ID_CHECKING, "Checking %s\n", path.c_str());
    }
    else
    {
        // Rewrite the file.
        FILE* os = File_Open(path.c_str(), "w");

        if (!os)
            err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s",path.c_str());

        put(os, "%s", &str_data[0]);

        fclose(os);
    }
}


//==============================================================================
//
// GenCppClassHeader
//
//     Generate C++ part of the header file for the given MOF class. This part 
//     contains the c++ wrapper class and provider class definition.
//
//==============================================================================
static void GenCppClassHeader(
    Parser& /*parser*/, 
    const MI_ClassDecl* cd,
    FILE* os
    )
{
    string alias = AliasOf(cd->name);

    // Comment box introducing C++ class definiti9on
    {
        string tmp = alias + "_Class";
        PutCommentBox(os, tmp);
        nl(os);
    }

    // standard starting part
    putl(os, "#ifdef __cplusplus");
    putl(os, "# include <micxx/micxx.h>");
    nl(os);
    putl(os, "MI_BEGIN_NAMESPACE");
    nl(os);


    // instance itself
    GenCppClassDeclaration<MI_ClassDecl,_MI_PropertyDecl>(os, cd, alias, 
        cd->superClass, cd->numProperties, cd->properties);

    // gen parameters classes
    // Put method definitions and setters for each method parameter.
    for (size_t i = 0; !s_options.noProviders && i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];

        string param_alias = alias + "_" + md->name;

        if (Strcasecmp(cd->name, md->propagator) == 0 ||
            providerClasses.find(cd->name) != providerClasses.end())
        {
            GenCppClassDeclaration(os, md, param_alias, 0, md->numParameters, 
                md->parameters);
        }
    }

    // provider class definition - if required
    if (providerClasses.find(cd->name) != providerClasses.end() &&
        !s_options.noProviders)
    {

        GenCppClassProviderHeader(cd);
    }

    // end c++ specific part
    putl(os, "MI_END_NAMESPACE");
    nl(os);
    putl(os, "#endif /* __cplusplus */");
    nl(os);
}


static void _PatchLoadSignature(
    const string& alias, 
    const string& path, 
    vector<char>& data)
{
    /* special case: patch Load funciton signature */
    string old_load = sub(OLD_PROVIDER_LOAD_PROTOTYPES, "<ALIAS>", alias);

    data.push_back(0);
    string str_data = &data[0];

    /* remove \r*/
    str_data = sub(str_data, "\r", "");

    if (str_data.find(old_load) != string::npos)
    {
        string new_load = sub(NEW_PROVIDER_LOAD_PROTOTYPES, "<ALIAS>", alias);

        str_data = sub(str_data, old_load, new_load);

        // Rewrite the file.
        {
            FILE* os = File_Open(path.c_str(), "w");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s",
                    path.c_str());
            }

            Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
            put(os, "%s", &str_data[0]);

            fclose(os);
        }
    }
}

/* Patches old cpp skeletons with load/unload funcitons */
static void _PatchLoadUnloadCPP(
    const string& alias, 
    const string& path, 
    vector<char>& data)
{
    /* special case: check if Load/Unload are declared */
    string old_load = sub("<ALIAS>_Class_Provider::Load(", "<ALIAS>", alias);

    data.push_back(0);
    string str_data = &data[0];

    /* remove \r*/
    str_data = sub(str_data, "\r", "");

    if (str_data.find(old_load) == string::npos)
    {
        string new_load = sub(COMMON_PROVIDER_CLASS_LOAD_UNLOAD_CPP, "<ALIAS>", alias);

        str_data += "MI_BEGIN_NAMESPACE\n";
        str_data += new_load;
        str_data += "MI_END_NAMESPACE\n";

        // Rewrite the file.
        {
            FILE* os = File_Open(path.c_str(), "w");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s",
                    path.c_str());
            }

            Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
            put(os, "%s", &str_data[0]);

            fclose(os);
        }
    }
}

//==============================================================================
//
// GenCppClassSource
//
//     Generate the cpp source file for the given MOF class. This file contains the
//     the provider function stubs.
//
//==============================================================================

static void GenCppClassSource(const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    // Open source file (refuse if it already exists).
    bool append;
    vector<char> data;
    const string path = ExpandPath(alias + "_Class_Provider.cpp");
    FILE* os = 0;
    {
        append = Exists(path.c_str());

        if (append)
        {
            if (!Inhale(path.c_str(), data))
            {
                err(ID_FAILED_TO_READ_FILE, "failed to read file: %s", 
                    path.c_str());
            }

            _PatchLoadUnloadCPP(alias, path, data);

            os = File_Open(path.c_str(), "a");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                    path.c_str());
            }
        }
        else
        {
            os = File_Open(path.c_str(), "w");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                    path.c_str());
            }

            GenStatikGenLine(os);
            Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());
        }
    }

    // Include required headers.
    if (!append)
    {
        putl(os, "#include <MI.h>");
        putl(os, "#include \"%s_Class_Provider.h\"", alias.c_str());
        nl(os);
        putl(os, "MI_BEGIN_NAMESPACE");
        nl(os);
    }

    // spil out provider class implementation (stubs)
    if (!append)
    {
        string r;
        
        if (cd->flags & MI_FLAG_ASSOCIATION)
        {
            if (CanGenerateAssocRoles(cd))
            {
                if (!s_options.association)
                {
                    r = ASSOCIATION_PROVIDER_CLASS_STUBS_CPP_ROLES;
                    SubRoles(cd, r);
                }
                else
                    r = ASSOCIATION_PROVIDER_CLASS_STUBS_CPP;
            }
            else
                errRefPropCount(cd->name);
        }
        else if (cd->flags & MI_FLAG_INDICATION)
            r = INDICATION_PROVIDER_CLASS_STUBS_CPP;
        else
            r = INSTANCE_PROVIDER_CLASS_STUBS_CPP;

        r = sub(r, "<ALIAS>", alias);
        puts(os, r);
    }

    // spil out provider extrinsic method stubs 
    if (!append)
    {
        for (size_t i = 0; i < cd->numMethods; i++)
        {
            const MI_MethodDecl* md = cd->methods[i];
            string r = sub(EXTRINSIC_METHOD_CLASS_STUB_CPP, "<ALIAS>", alias);
            r = sub(r, "<METHOD>", md->name);
            puts(os, r);
        }
    }

    // close namespace
    if (!append)
    {
        nl(os);
        putl(os, "MI_END_NAMESPACE");
    }


    // only if we are updating exisitng one
    if (append)
    {
        bool patched = false;

        // Generate extrinsic method stubs (not already found in file).
        for (size_t i = 0; i < cd->numMethods; i++)
        {
            const MI_MethodDecl* md = cd->methods[i];
            string r = sub(
                "MI_BEGIN_NAMESPACE\n\n" EXTRINSIC_METHOD_CLASS_STUB_CPP "\nMI_END_NAMESPACE\n", "<ALIAS>", alias);
            r = sub(r, "<METHOD>", md->name);

            string name = string("::Invoke_") + md->name;

            // Skip methods already found in file.

            if (strstr(&data[0], name.c_str()))
                continue;
            else
            {
                if (!patched)
                {
                    Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", 
                        path.c_str());
                    patched = true;
                }
                puts(os, r);
            }
        }

        if (!patched)
        {
            Fprintf(s_stdout, ID_CHECKING, "Checking %s\n", path.c_str());
        }
    }

    // Close file.
    fclose(os);
}

//==============================================================================
//
// GenerateClassStub
//
//     Generate wrapper for provider class
//
//==============================================================================

static void GenerateClassStub(FILE* os, const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    // Generate extrinsic method stubs.
    {
        if (cd->flags & MI_FLAG_ASSOCIATION)
        {
            string r;

            if (CanGenerateAssocRoles(cd))
            {
                if (!s_options.association)
                {
                    r = ASSOCIATION_PROVIDER_STUBS_CPP_ROLES;
                    SubRoles(cd, r);
                }
                else
                    r = ASSOCIATION_PROVIDER_STUBS_CPP;
            }
            else
                errRefPropCount(cd->name);

            r = sub(r, "<ALIAS>", alias);
            puts(os, r);
        }
        else if (cd->flags & MI_FLAG_INDICATION)
        {
            string r = INDICATION_PROVIDER_STUBS_CPP;
            r = sub(r, "<ALIAS>", alias);
            puts(os, r);
        }
        else
        {
            if (HasKeys(cd))
            {
                string r = INSTANCE_PROVIDER_STUBS_CPP;
                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
            else 
            {
                string r = COMMON_PROVIDER_STUBS_CPP;
                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
        }
    }

    // generate all extrinsic method stubs (if new one)
    {
        for (size_t i = 0; i < cd->numMethods; i++)
        {
            const MI_MethodDecl* md = cd->methods[i];
            string r = sub(EXTRINSIC_METHOD_STUB_CPP, "<ALIAS>", alias);
            r = sub(r, "<METHOD>", md->name);
            puts(os, r);
        }

    }
}

//==============================================================================
//
// GenClassHeader
//
//     Generate the header file for the given MOF class. This file contains the
//     C structure definition, setter functions, parameter structures, and
//     provider function prototypes.
//
//==============================================================================

static void GenClassHeader(
    Parser& parser, 
    const MI_ClassDecl* cd,
    set<string>& classIdentifiers)
{
    const string alias = AliasOf(cd->name);

    // Refuse to generate same class more than once.

    if (generated_headers.find(cd->name) != generated_headers.end())
        return;

    generated_headers.insert(cd->name);

    // Find direct dependencies of this class.
    vector<string> deps;
    FindDirectDependencies(cd, deps);

    // Recurse on dependencies.
    for (size_t i = 0; i < deps.size(); i++)
    {
        const MI_ClassDecl* tcd = parser.findClassDecl(deps[i].c_str());

        if (!tcd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", deps[i].c_str());

        GenClassHeader(parser, tcd, classIdentifiers);
    }

    // Open class header file.
    string path = ExpandPath(alias + ".h");
    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    FILE* os = File_Open(path.c_str(), "w");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    GenStatikGenLine(os);

    // Put comment header.
    PutCommentBox(os, WARNING);

    // Prevent multiple inclusion.
    putl(os, "#ifndef _%s_h", alias.c_str());
    putl(os, "#define _%s_h", alias.c_str());
    nl(os);

    // Include <MI.h>
    putl(os, "#include <MI.h>");

    // Generate includes for direct dependencies.
    for (size_t i = 0; i < deps.size(); i++)
    {
        string al = AliasOf(deps[i]);
        putl(os, "#include \"%s.h\"", al.c_str());
    }

    nl(os);

    // Put comment box for the class structure. List the key names for this
    // class.
    {
        putl(os, "/*");
        PutRule(os);
        putl(os, "**");
        putl(os, "** %s [%s]", alias.c_str(), cd->name);
        putl(os, "**");
        putl(os, "** Keys:");

        for (size_t i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];

            if (pd->flags & MI_FLAG_KEY)
                putl(os, "**    %s", pd->name);
        }

        putl(os, "**");
        PutRule(os);
        putl(os, "*/");
        nl(os);
    }

    // Put class structure definition with all its properties.
    if (cd->superClass)
    {
        putl(os, "typedef struct _%s /* extends %s */", 
            alias.c_str(), cd->superClass);
    }
    else
    {
        putl(os, "typedef struct _%s", alias.c_str());
    }

    putl(os, "{");
    putl(os, "    MI_Instance __instance;");
    NameClassMap map;
    GenProperties(os, parser, cd, cd, map);
    putl(os, "}");
    putl(os, "%s;", alias.c_str());
    nl(os);

    // Generate a reference of this type (if not an association or indication).
#if 0
    if (!(cd->flags & MI_FLAG_ASSOCIATION || cd->flags & MI_FLAG_INDICATION))
#endif
    // Associations can be used as endpoints in other associations.
    {
        {
            const char T[] =
                "typedef struct _<ALIAS>_Ref\n"
                "{\n"
                "    <ALIAS>* value;\n"
                "    MI_Boolean exists;\n"
                "    MI_Uint8 flags;\n"
                "}\n"
                "<ALIAS>_Ref;\n"
                "\n"
                "typedef struct _<ALIAS>_ConstRef\n"
                "{\n"
                "    MI_CONST <ALIAS>* value;\n"
                "    MI_Boolean exists;\n"
                "    MI_Uint8 flags;\n"
                "}\n"
                "<ALIAS>_ConstRef;\n"
                "\n";

            string r = sub(T, "<ALIAS>", alias);
            puts(os, r);
        }
        {
            const char T[] =
                "typedef struct _<ALIAS>_Array\n"
                "{\n"
                "    struct _<ALIAS>** data;\n"
                "    MI_Uint32 size;\n"
                "}\n"
                "<ALIAS>_Array;\n"
                "\n"
                "typedef struct _<ALIAS>_ConstArray\n"
                "{\n"
                "    struct _<ALIAS> MI_CONST* MI_CONST* data;\n"
                "    MI_Uint32 size;\n"
                "}\n"
                "<ALIAS>_ConstArray;\n"
                "\n"
                "typedef struct _<ALIAS>_ArrayRef\n"
                "{\n"
                "    <ALIAS>_Array value;\n"
                "    MI_Boolean exists;\n"
                "    MI_Uint8 flags;\n"
                "}\n"
                "<ALIAS>_ArrayRef;\n"
                "\n"
                "typedef struct _<ALIAS>_ConstArrayRef\n"
                "{\n"
                "    <ALIAS>_ConstArray value;\n"
                "    MI_Boolean exists;\n"
                "    MI_Uint8 flags;\n"
                "}\n"
                "<ALIAS>_ConstArrayRef;\n"
                "\n";

            string r = sub(T, "<ALIAS>", alias);
            puts(os, r);
        }
    }

    // Generate an external reference to the class RTTI instance.
    if (s_options.cpp || !s_options.noProviders)
    {
        putl(os, "MI_EXTERN_C MI_CONST MI_ClassDecl %s_rtti;", alias.c_str());
        nl(os);
    }

    // Generate Instance function
    if (!s_options.noProviders)
        GenInstanceFunctions(os,cd);

    // Gen setters.
    {
        for (size_t i = 0; i < cd->numProperties; i++)
            GenSetter(os, cd, NULL, (MI_ParameterDecl*)cd->properties[i]);
    }

    // Put method definitions and setters for each method parameter.
    for (size_t i = 0; i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];
        GenParametersStruct(os, cd, md);

        // Generate convenience functions.
        if (!s_options.noProviders)
        {
            if (Strcasecmp(cd->name, md->propagator) == 0 ||
                providerClasses.find(cd->name) != providerClasses.end())
            {
                GenMethodFunctions(os, cd, md);
            }
        }

        // Generate parameter setter for "MIReturn".
        if (!s_options.noProviders)
        {
            MI_ParameterDecl pd;
            memset(&pd, 0, sizeof(pd));
            pd.flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
            pd.name = (char*)"MIReturn";
            pd.type = md->returnType;
            pd.offset = sizeof(MI_Instance);
            pd.numQualifiers = md->numQualifiers;
            pd.qualifiers = md->qualifiers;
            GenSetter(os, cd, md, &pd);
        }

        if (!s_options.noProviders)
        {
            for (size_t j = 0; j < md->numParameters; j++)
            {
                const MI_ParameterDecl* pd = md->parameters[j];

                // Skip stream parameters:
                if (pd->flags & MI_FLAG_STREAM)
                    continue;

                GenSetter(os, cd, md, pd);
            }
        }
    }

    if (providerClasses.find(cd->name) != providerClasses.end())
    {

        // Write the intrinsic provider function prototypes.

        if (!s_options.noProviders)
        {
            PutCommentBox(os, alias + " provider function prototypes");
            nl(os);

            // Generate forward typedef for Self structure.
            putl(os,"/* The developer may optionally define this structure */");
            putl(os, "typedef struct _%s_Self %s_Self;\n", 
                alias.c_str(), alias.c_str());

            if (cd->flags & MI_FLAG_ASSOCIATION)
            {
                string r;

                if (CanGenerateAssocRoles(cd))
                {
                    if (s_options.association)
                        r = ASSOCIATION_PROVIDER_PROTOTYPES;
                    else
                    {
                        r = ROLE_PROVIDER_PROTOTYPES;
                        SubRoles(cd, r);
                    }
                }
                else
                    errRefPropCount(cd->name);

                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
            else if (cd->flags & MI_FLAG_INDICATION)
            {
                string r;
                r = INDICATION_PROVIDER_PROTOTYPES;
                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
            else
            {
                if (HasKeys(cd))
                {
                    string r = INSTANCE_PROVIDER_PROTOTYPES;
                    r = sub(r, "<ALIAS>", alias);
                    puts(os, r);
                }
                else
                {
                    string r = COMMON_PROVIDER_PROTOTYPES;
                    r = sub(r, "<ALIAS>", alias);
                    puts(os, r);
                }
            }
        }

        // Write the extrinsic provider function prototypes.
        if (!s_options.noProviders)
        {
            for (size_t i = 0; i < cd->numMethods; i++)
            {
                const MI_MethodDecl* md = cd->methods[i];
                string r = sub(EXTRINSIC_METHOD_PROTOTYPE, "<ALIAS>", alias);
                r = sub(r, "<METHOD>", md->name);
                puts(os, r);
            }
        }
    }

    // Generate the class identifier:
#if 0
    {
        char id[33];
        _MakeID(id);
        string classIdentifier = alias + "_" + id;
        classIdentifiers.insert(classIdentifier);
        putl(os, "#define %s\n", classIdentifier.c_str());
    }
#endif

    nl(os);

    // c++ part
    if (s_options.cpp)
        GenCppClassHeader(parser, cd, os);

    // End ifdef that Prevents multiple inclusion.
    putl(os, "#endif /* _%s_h */", alias.c_str());

    // Close file.
    fclose(os);
}

//==============================================================================
//
// GenClassSource
//
//     Generate the source file for the given MOF class. This file contains the
//     the provider function stubs.
//
//==============================================================================

static void GenClassSource(const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    // Open source file (refuse if it already exists).
    bool append;
    vector<char> data;
    const string path = ExpandPath(alias + ".c");
    FILE* os = 0;
    {
        append = Exists(path.c_str());

        if (append)
        {
            if (!Inhale(path.c_str(), data))
            {
                err(ID_FAILED_TO_READ_FILE, "failed to read file: %s", 
                    path.c_str());
            }

            _PatchLoadSignature(alias, path, data);

            os = File_Open(path.c_str(), "a");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                    path.c_str());
            }
        }
        else
        {
            os = File_Open(path.c_str(), "w");

            if (!os)
            {
                err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                    path.c_str());
            }

            GenStatikGenLine(os);
            Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());
        }
    }

    // Include required headers.
    if (!append)
    {
        putl(os, "#include <MI.h>");
        putl(os, "#include \"%s.h\"", alias.c_str());
        nl(os);
    }

    // Generate extrinsic method stubs.
    if (!append)
    {
        if (cd->flags & MI_FLAG_ASSOCIATION)
        {
            string r;
            if (CanGenerateAssocRoles(cd))
            {
                if (s_options.association)
                    r = ASSOCIATION_PROVIDER_STUBS;
                else
                {
                    r = ROLE_PROVIDER_STUBS;
                    SubRoles(cd, r);
                }
            }
            else
                errRefPropCount(cd->name);

            r = sub(r, "<ALIAS>", alias);
            puts(os, r);
        }
        else if (cd->flags & MI_FLAG_INDICATION)
        {
            string r = INDICATION_PROVIDER_STUBS;
            r = sub(r, "<ALIAS>", alias);
            puts(os, r);
        }
        else
        {
            if (HasKeys(cd))
            {
                string r = INSTANCE_PROVIDER_STUBS;
                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
            else
            {
                string r = COMMON_PROVIDER_STUBS;
                r = sub(r, "<ALIAS>", alias);
                puts(os, r);
            }
        }

    } 

    bool patched = false;

    // Generate extrinsic method stubs (not already found in file).
    for (size_t i = 0; i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];
        string r = sub(EXTRINSIC_METHOD_STUB, "<ALIAS>", alias);
        r = sub(r, "<METHOD>", md->name);

        string name = alias + "_Invoke_" + md->name;

        // Skip methods already found in file.

        if (append && strstr(&data[0], name.c_str()))
            continue;
        else
        {
            if (!patched)
            {
                Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
                patched = true;
            }
            puts(os, r);
        }
    }

    if (!patched)
    {
        Fprintf(s_stdout, ID_CHECKING, "Checking %s\n", path.c_str());
    }

    // Close file.
    fclose(os);
}

//==============================================================================
//
// PutString()
//
//     Write a string literal.
//
//==============================================================================

static void PutStringLiteral(FILE* os, const char* value)
{
    put(os, "MI_T(\"");

    for (const char* p = value; *p; p++)
    {
        unsigned char c = (unsigned char)*p;

        if (c >= 32 && c <= 127)
            put(os, "%c", c);
        else
            put(os, "\\%04o", c);
    }

    put(os, "\")");
}

//==============================================================================
//
// Localize()
//
//     Add the string to the localization table and return an integer 
//     identifier for that string. The localization id is one greater
//     than its index in the s_localizations.
//
//==============================================================================

static vector<string> s_localizations;

static MI_Uint32 Localize(const string& msg)
{
    for (size_t i = 0; i < s_localizations.size(); i++)
    {
        if (s_localizations[i] == msg)
            return (MI_Uint32)(i + 1);
    }

    s_localizations.push_back(msg);
    return (MI_Uint32)s_localizations.size();
}

//==============================================================================
//
// GenScalarValueInitializer
//
//     Put the value initializer for a property or qualifier value.
//
//==============================================================================

static void GenScalarValueInitializer(
    FILE* os, 
    MI_Type type, 
    const void* value,
    bool localize)
{
    // Unsatisfiable condition.
    assert(value != NULL);

    switch (type)
    {
        case MI_BOOLEAN:
        {
            put(os, "%s", *((MI_Boolean*)value) ? "1" : "0");
            break;
        }
        case MI_UINT8:
        {
            put(os, "%u", *((MI_Uint8*)value));
            break;
        }
        case MI_SINT8:
        {
            put(os, "%d", *((MI_Sint8*)value));
            break;
        }
        case MI_UINT16:
        {
            put(os, "%u", *((MI_Uint16*)value));
            break;
        }
        case MI_SINT16:
        {
            put(os, "%d", *((MI_Sint16*)value));
            break;
        }
        case MI_UINT32:
        {
            MI_Uint32 x = *((MI_Uint32*)value);
            put(os, "%uU", x);
            break;
        }
        case MI_SINT32:
        {
            MI_Sint32 x = *((MI_Sint32*)value);

            if (x == -2147483647-1)
                put(os, "-2147483647-1");
            else
                put(os, "%d", x);
            break;
        }
        case MI_UINT64:
        {
            put(os, "MI_ULL(" UINT64_FMT ")", *((MI_Uint64*)value));
            break;
        }
        case MI_SINT64:
        {
            MI_Sint64 x = *((MI_Sint64*)value);
            if (x == -MI_LL(9223372036854775807)-MI_LL(1))
                put(os, "-MI_LL(9223372036854775807)-MI_LL(1)");
            else
            {
                if (x >= 0)
                    put(os, "MI_LL(" SINT64_FMT ")", x);
                else
                    put(os, "-MI_LL(" SINT64_FMT ")", -x);
            }
            break;
        }
        case MI_REAL32:
        {
            put(os, "(float)%g", *((MI_Real32*)value));
            break;
        }
        case MI_REAL64:
        {
            put(os, "(double)%g", *((MI_Real64*)value));
            break;
        }
        case MI_CHAR16:
        {
            put(os, "%u", *((MI_Char16*)value));
            break;
        }
        case MI_DATETIME:
        {
            const MI_Datetime& x = *((MI_Datetime*)value);

            if (x.isTimestamp)
            {
                put(os,"{1,{{%u,%u,%u,%u,%u,%u,%u,%d}}}",
                    x.u.timestamp.year, 
                    x.u.timestamp.month, 
                    x.u.timestamp.day, 
                    x.u.timestamp.hour, 
                    x.u.timestamp.minute, 
                    x.u.timestamp.second, 
                    x.u.timestamp.microseconds,
                    x.u.timestamp.utc);
            }
            else
            {
                put(os,"{0,{{%u,%u,%u,%u,%u}}}",
                    x.u.interval.days, 
                    x.u.interval.hours, 
                    x.u.interval.minutes,
                    x.u.interval.seconds, 
                    x.u.interval.microseconds);
            }
            break;
        }
        case MI_STRING:
        {
            if (localize && s_options.localize)
            {
                MI_Uint32 id = Localize((char*)value);
                char buf[9];
                Snprintf(buf, MI_COUNT(buf), "%u", id);
                PutStringLiteral(os, buf);
            }
            else
                PutStringLiteral(os, (char*)value);
            break;
        }
        default:
            // Unreachable!
            assert(0);
            break;
    }
}

//==============================================================================
//
// GenValue()
//
//     Generate the value for a property declaration.
//
//==============================================================================

static void GenValue(
    FILE* os, 
    const string& stem,
    MI_Uint32 type,
    const void* value,
    bool localize)
{
    MI_Type stype = (MI_Type)(type & ~MI_ARRAY_BIT);
    string typenameof = sub( TypeNameOf(stype), "String", "Char*");

    // If the value is null, just return.
    if (!value)
        return;

    // Encode array or scalar.
    if (type & MI_ARRAY_BIT)
    {
        // Write the array data elements.

        putl(os, "static MI_CONST MI_%s %s_data_value[] =", 
            typenameof.c_str(), stem.c_str());
        putl(os, "{");

        if (type == MI_STRINGA)
        {
            MI_StringA* arr = (MI_StringA*)value;

            for (MI_Uint32 i = 0; i < arr->size; i++)
            {
                put(os, "    ");
                GenScalarValueInitializer(os, stype, arr->data[i], localize);
                putl(os, ",");
            }
        }
        else
        {
            MI_Uint8A* arr = (MI_Uint8A*)value;
            MI_Uint8* p = arr->data;

            for (MI_Uint32 i = 0; i < arr->size; i++)
            {
                put(os, "    ");
                GenScalarValueInitializer(os, stype, p, localize);
                p += ScalarSizeOf(stype);
                putl(os, ",");
            }
        }

        putl(os, "};");
        nl(os);

        // Write the array itself.

        putl(os, "static MI_CONST MI_Const%sA %s_value =", TypeNameOf(stype), stem.c_str());
        putl(os, "{");
        putl(os, "    %s_data_value,", stem.c_str());
        putl(os, "    MI_COUNT(%s_data_value),", stem.c_str());
        putl(os, "};");
        nl(os);
    }
    else
    {
        put(os, "static MI_CONST MI_%s %s_value = ", typenameof.c_str(), stem.c_str());
        GenScalarValueInitializer(os, (MI_Type)type, value, localize);
        putl(os, ";");
        nl(os);
    }
}

//==============================================================================
//
// MI_Qualifier
//
//     This function generates a qualifier.
//
//==============================================================================

static void GenQualifier(
    Parser& parser,
    FILE* os,
    const MI_Qualifier* q,
    const string& stem_)
{
    string stem = stem_ + "_" + q->name + "_qual";

    /* Find qualifier declaration */
    const MI_QualifierDecl* qd = parser.findQualifierDecl(q->name);

    if (!qd)
        err(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);

    /* Generate the value */
    GenValue(os, stem, q->type, q->value, 
        (q->flavor & MI_FLAG_TRANSLATABLE) ? true : false);

    const char T[] =
        "static MI_CONST MI_Qualifier <STEM> =\n"
        "{\n"
        "    MI_T(\"<NAME>\"),\n"
        "    <TYPE>,\n"
        "    <FLAVOR>,\n"
        "    <VALUE>\n"
        "};\n"
        "\n";

    string r = T;
    r = sub(r, "<STEM>", stem);
    r = sub(r, "<NAME>", q->name);
    r = sub(r, "<TYPE>", MakeType(q->type));
    r = sub(r, "<FLAVOR>", MakeFlavor(q->flavor));

    if (q->value)
        r = sub(r, "<VALUE>", "&" + stem + "_value");
    else
        r = sub(r, "<VALUE>", "NULL");

    puts(os, r);
}

//==============================================================================
//
// GenQualifiers()
//
//     Generate a list of qualifier definitions. Return the number of qualifiers
//     generated (which may be less than numQualifiers due to excluded
//     qualifiers, such as boolean).
//
//==============================================================================

static size_t GenQualifiers(
    Parser& parser,
    FILE* os, 
    MI_Qualifier** qualifiers,
    MI_Uint32 numQualifiers,
    const string& stem)
{
    size_t count = 0;

    if (numQualifiers == 0)
        return 0;

    /* Check if qualifiers are ignored */
    if (s_options.ignoreAllQualifiers)
        return 0;

    // Generate qualifiers.

    for (MI_Uint32 i = 0; i < numQualifiers; i++)
    {
        const MI_Qualifier* q = qualifiers[i];

        if (q->type == MI_BOOLEAN && !s_options.booleanQualifiers)
            continue;

        // Skip Description qualifier if -D option was given.
        if (eqi(q->name, "Description") && !s_options.descriptions)
            continue;

        // Skip Values qualifier if -V option was given.
        if (eqi(q->name, "Values") && !s_options.values)
            continue;

        // Skip ValueMap qualifier if -V option was given.
        if (eqi(q->name, "ValueMap") && !s_options.values)
            continue;

        // Skip MappingStrings qualifier if -M option was given.
        if (eqi(q->name, "MappingStrings") && !s_options.mappingStrings)
            continue;

        // Skip ModelCorrespondence qualifiers?
        if (eqi(q->name, "ModelCorrespondence") && !s_options.modelCorrespondence)
            continue;

        GenQualifier(parser, os, q, stem);
        count++;
    }

    // If no qualifiers were generated, return now to avoid creating an
    // empty array of qualifiers.
    if (count == 0)
        return 0;

    // Generate the array of qualifiers.

    putl(os, "static MI_Qualifier MI_CONST* MI_CONST %s_quals[] =", stem.c_str());
    putl(os, "{");

    for (MI_Uint32 i = 0; i < numQualifiers; i++)
    {
        const MI_Qualifier* q = qualifiers[i];

        if (q->type == MI_BOOLEAN && !s_options.booleanQualifiers)
            continue;

        // Skip Description qualifier if -D option was given.
        if (eqi(q->name, "Description") && !s_options.descriptions)
            continue;

        // Skip Values qualifier if -v option was given.
        if (eqi(q->name, "Values") && !s_options.values)
            continue;

        // Skip ValueMap qualifier if -v option was given.
        if (eqi(q->name, "ValueMap") && !s_options.values)
            continue;

        // Skip Values qualifier if -M option was given.
        if (eqi(q->name, "MappingStrings") && !s_options.mappingStrings)
            continue;

        // Skip ModelCorrespondence qualifiers?
        if (eqi(q->name, "ModelCorrespondence") && !s_options.modelCorrespondence)
            continue;

        putl(os, "    &%s_%s_qual,", stem.c_str(), q->name);
    }

    putl(os, "};");
    nl(os);

    return count;
}

//==============================================================================
//
// HashCode()
//
//     Compute a hash code of the given CIM identifier as follows.
//
//         (name[0] << 16) | (name[len-1] << 8) | len
//
//==============================================================================

static MI_Uint32 HashCode(const string& s)
{
    MI_Uint32 n = (MI_Uint32)s.size();

    if (n == 0)
        err(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);

    return tolower((MI_Uint32)s[0])<<16 | tolower((MI_Uint32)s[n-1])<<8 | n;
}

//==============================================================================
//
// GenPropertyDecl()
//
//     This function generates a property declaration (i.e., a structure 
//     initialization of the MI_PropertyDecl structure) for the given property.
//
//==============================================================================

static void GenPropertyDecl(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd,
    const MI_PropertyDecl* pd)
{
    const string alias = AliasOf(cd->name);

    // Generate the qualifiers first.
    size_t numQualifiers = GenQualifiers(
        parser,
        os, 
        pd->qualifiers, 
        pd->numQualifiers,
        AliasOf(cd->name) + "_" + pd->name);

    // Generate the value.
    if (pd->value)
        GenValue(os, alias + "_" + pd->name, pd->type, pd->value, false);

    static const char T[] =
        "/* property <CLASS>.<PROP> */\n"
        "static MI_CONST MI_PropertyDecl <CLASS>_<PROP>_prop =\n"
        "{\n"
        "    <FLAGS>, /* flags */\n"
        "    <CODE>, /* code */\n"
        "    MI_T(\"<PROP>\"), /* name */\n"
        "    <QUALS>, /* qualifiers */\n"
        "    <NQUALS>, /* numQualifiers */\n"
        "    <TYPE>, /* type */\n"
        "    <CLASSNAME>, /* className */\n"
        "    <SUBSCRIPT>, /* subscript */\n"
        "    offsetof(<CLASS>, <PROP>), /* offset */\n"
        "    <ORIGIN>, /* origin */\n"
        "    <PROPAGATOR>, /* propagator */\n";

    string r = T;
    r = sub(r, "<CLASS>", alias);
    r = subx(r, "<CODE>", HashCode(pd->name));
    r = sub(r, "<PROP>", pd->name);
    r = sub(r, "<FLAGS>", MakeFlags(pd->flags));

    /* check for embedded instances */
    if (MI_STRING == (pd->type & ~MI_ARRAY_BIT) 
        && IsPropertyRefOrInstance(pd))
    {
        r = sub(r, "<TYPE>", ((pd->type & MI_ARRAY_BIT) != 0 ? "MI_INSTANCEA" : "MI_INSTANCE"));
    }
    else
        r = sub(r, "<TYPE>", MakeType(pd->type));

    if (numQualifiers)
    {
        string s = AliasOf(cd->name) + "_" + pd->name + "_quals";
        r = sub(r, "<QUALS>", s);
        r = sub(r, "<NQUALS>", "MI_COUNT(" + s + ")");
    }
    else
    {
        r = sub(r, "<QUALS>", "NULL");
        r = sub(r, "<NQUALS>", "0");
    }

    if (!GetPropertyClassname(pd).empty())
        r = sub(r, "<CLASSNAME>", Quote(GetPropertyClassname(pd)));
    else
        r = sub(r, "<CLASSNAME>", "NULL");

    r = subu(r, "<SUBSCRIPT>", pd->subscript);
    r = sub(r, "<ORIGIN>", Quote(pd->origin));
    r = sub(r, "<PROPAGATOR>", Quote(pd->propagator));

    puts(os, r);

    // Put the value if any.

    if (pd->value)
        putl(os, "    &%s_%s_value,", alias.c_str(), pd->name);
    else
        putl(os, "    NULL,");

    putl(os, "};");
    nl(os);
}

//==============================================================================
//
// GenPropertyDecls()
//
//     This function generates an array of property declaration objects for
//     the given class.
//
//==============================================================================

static void GenPropertyDecls(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    // Generate a property declaration for each property.
    for (size_t i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];

        // Only generate property declarations if this class is the owner.
        if (Strcasecmp(cd->name, pd->propagator) == 0)
        {
            GenPropertyDecl(parser, os, cd, pd);
        }
    }

    // Generate the array of property declarations (if any)

    if (cd->numProperties)
    {
        putl(os, "static MI_PropertyDecl MI_CONST* MI_CONST %s_props[] =", 
            alias.c_str());
        putl(os, "{");

        for (size_t i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];
            const string ownerAlias = AliasOf(pd->propagator);
            putl(os, "    &%s_%s_prop,", ownerAlias.c_str(), pd->name);
        }

        putl(os, "};");
    }

    nl(os);
}

//==============================================================================
//
// GenParameterDecl()
//
//     This function generates a parameter declaration for the given method and
//     class.
//
//==============================================================================

static void GenParameterDecl(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd,
    const MI_MethodDecl* md,
    const MI_ParameterDecl* pd)
{
    const string alias = AliasOf(cd->name);

    // Generate the qualifiers first.
    size_t numQualifiers = GenQualifiers(
        parser,
        os, 
        pd->qualifiers, 
        pd->numQualifiers,
        AliasOf(cd->name) + "_" + md->name + "_" + pd->name);

    static const char T[] =
        "/* parameter <CLASS>.<METH>(): <PARAM> */\n"
        "static MI_CONST MI_ParameterDecl <CLASS>_<METH>_<PARAM>_param =\n"
        "{\n"
        "    <FLAGS>, /* flags */\n"
        "    <CODE>, /* code */\n"
        "    MI_T(\"<PARAM>\"), /* name */\n"
        "    <QUALS>, /* qualifiers */\n"
        "    <NQUALS>, /* numQualifiers */\n"
        "    <TYPE>, /* type */\n"
        "    <CLASSNAME>, /* className */\n"
        "    <SUBSCRIPT>, /* subscript */\n"
        "    <OFFSET>, /* offset */\n"
        "};\n"
        "\n";

    string r = T;

    if (pd->flags & MI_FLAG_STREAM)
        r = sub(r, "<OFFSET>", "0xFFFFFFFF");
    else
        r = sub(r, "<OFFSET>", "offsetof(<CLASS>_<METH>, <PARAM>)");

    r = sub(r, "<CLASS>", alias);
    r = subx(r, "<CODE>", HashCode(pd->name));
    r = sub(r, "<METH>", md->name);
    r = sub(r, "<PARAM>", pd->name);
    r = sub(r, "<FLAGS>", MakeFlags(pd->flags));

    /* check for embedded instances */
    if (MI_STRING == (pd->type & ~MI_ARRAY_BIT) 
        && IsPropertyRefOrInstance(pd))
    {
        r = sub(r, "<TYPE>", ((pd->type & MI_ARRAY_BIT) != 0 ? "MI_INSTANCEA" : "MI_INSTANCE"));
    }
    else
        r = sub(r, "<TYPE>", MakeType(pd->type));

    if (numQualifiers)
    {
        string s = AliasOf(cd->name) + "_" + md->name + "_" +pd->name +"_quals";
        r = sub(r, "<QUALS>", s);
        r = sub(r, "<NQUALS>", "MI_COUNT(" + s + ")");
    }
    else
    {
        r = sub(r, "<QUALS>", "NULL");
        r = sub(r, "<NQUALS>", "0");
    }

    if (!GetPropertyClassname(pd).empty())
        r = sub(r, "<CLASSNAME>", Quote(GetPropertyClassname(pd)));
    else
        r = sub(r, "<CLASSNAME>", "NULL");

    r = subu(r, "<SUBSCRIPT>", pd->subscript);

    puts(os, r);
}

//==============================================================================
//
// GenMethodDecl()
//
//     This function generates a method declaration for the given class.
//
//==============================================================================

static void GenMethodDecl(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd,
    const MI_MethodDecl* md)
{
    // Generate the qualifiers first.
    size_t numQualifiers = GenQualifiers(
        parser,
        os, 
        md->qualifiers, 
        md->numQualifiers,
        AliasOf(cd->name) + "_" + md->name);

    const string alias = AliasOf(cd->name);

    // Generate each parameter declartions.
    for (size_t i = 0; i < md->numParameters; i++)
    {
        const MI_ParameterDecl* pd = md->parameters[i];
        GenParameterDecl(parser, os, cd, md, pd);
    }

    // Generate the return parameter declarations.
    {
        MI_ParameterDecl pd;
        memset(&pd, 0, sizeof(pd));
        pd.flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
        pd.name = (char*)"MIReturn";
        pd.type = md->returnType;
        pd.offset = sizeof(MI_Instance);
        pd.numQualifiers = md->numQualifiers;
        pd.qualifiers = md->qualifiers;
        GenParameterDecl(parser, os, cd, md, &pd);
    }

    // Generate the parmaeter declaration array.
    {
        putl(os, "static MI_ParameterDecl MI_CONST* MI_CONST %s_%s_params[] =",
            alias.c_str(), md->name);
        putl(os, "{");

        putl(os, "    &%s_%s_MIReturn_param,", alias.c_str(), md->name);

        for (size_t i = 0; i < md->numParameters; i++)
        {
            const MI_ParameterDecl* pd = md->parameters[i];
            putl(os, "    &%s_%s_%s_param,", alias.c_str(), md->name, pd->name);
        }

        putl(os, "};");
        nl(os);
    }

    static const char T[] =
        "/* method <ALIAS>.<METH>() */\n"
        "MI_CONST MI_MethodDecl <ALIAS>_<METH>_rtti =\n"
        "{\n"
        "    <FLAGS>, /* flags */\n"
        "    <CODE>, /* code */\n"
        "    MI_T(\"<METH>\"), /* name */\n"
        "    <QUALS>, /* qualifiers */\n"
        "    <NQUALS>, /* numQualifiers */\n"
        "    <ALIAS>_<METH>_params, /* parameters */\n"
        "    MI_COUNT(<ALIAS>_<METH>_params), /* numParameters */\n"
        "    sizeof(<ALIAS>_<METH>), /* size */\n"
        "    <TYPE>, /* returnType */\n"
        "    <ORIGIN>, /* origin */\n"
        "    <PROPAGATOR>, /* propagator */\n"
        "    &<SCHEMA>, /* schema */\n"
        "    <STUB>, /* method */\n"
        "};\n"
        "\n";

    string r = T;

    if (s_options.schema.size())
        r = sub(r, "<SCHEMA>", s_options.schema.c_str());
    else
        r = sub(r, "<SCHEMA>", "schemaDecl");

    r = sub(r, "<ALIAS>", alias);
    r = subx(r, "<CODE>", HashCode(md->name));
    r = sub(r, "<METH>", md->name);
    r = sub(r, "<FLAGS>", MakeFlags(md->flags));

    /* check for embedded instances */
    if (MI_STRING == (md->returnType & ~MI_ARRAY_BIT) 
        && ExistInstanceQualifier(md))
    {
        r = sub(r, "<TYPE>", ((md->returnType & MI_ARRAY_BIT) != 0 ? "MI_INSTANCEA" : "MI_INSTANCE"));
    }
    else
        r = sub(r, "<TYPE>", MakeType(md->returnType));

    r = sub(r, "<ORIGIN>", Quote(md->origin));
    r = sub(r, "<PROPAGATOR>", Quote(md->propagator));

    // If there is no provider for this class, set to NULL
    if (providerClasses.find(cd->name) == providerClasses.end())
    {
        r = sub(r, "<STUB>", "NULL");
    }
    else
    {
        static const char T_template[] =
            "(MI_ProviderFT_Invoke)<ALIAS>_Invoke_<METH>";
        string t = T_template;
        t = sub(t, "<ALIAS>", alias);
        t = sub(t, "<METH>", md->name);
        r = sub(r, "<STUB>", t);
    }

    if (numQualifiers)
    {
        string s = AliasOf(cd->name) + "_" + md->name + "_quals";
        r = sub(r, "<QUALS>", s);
        r = sub(r, "<NQUALS>", "MI_COUNT(" + s + ")");
    }
    else
    {
        r = sub(r, "<QUALS>", "NULL");
        r = sub(r, "<NQUALS>", "0");
    }

    puts(os, r);
}

//==============================================================================
//
// GenMethodDecls()
//
//     This function generates a method declaration array for the given class.
//
//==============================================================================

static void GenMethodDecls(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    if (cd->numMethods == 0)
        return;

    // Generate a property declaration for each property.
    for (size_t i = 0; i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];

        // Only generate this definition for the propagating class unless
        // the derived class is a class for which there will be a provider.
        // In that case we must generate this declaration so it can hold
        // the extrinsic method stub for that provider.
        if (Strcasecmp(cd->name, md->propagator) == 0 ||
            providerClasses.find(cd->name) != providerClasses.end())
        {
            GenMethodDecl(parser, os, cd, md);
        }
    }

    // Generate the array of property declarations.

    putl(os, "static MI_MethodDecl MI_CONST* MI_CONST %s_meths[] =", 
        alias.c_str());
    putl(os, "{");

    for (size_t i = 0; i < cd->numMethods; i++)
    {
        const MI_MethodDecl* md = cd->methods[i];

        if (Strcasecmp(cd->name, md->propagator) == 0 ||
            providerClasses.find(cd->name) != providerClasses.end())
        {
            putl(os, "    &%s_%s_rtti,", alias.c_str(), md->name);
        }
        else
        {
            const string ownerAlias = AliasOf(md->propagator);
            putl(os, "    &%s_%s_rtti,", ownerAlias.c_str(), md->name);
        }
    }

    putl(os, "};");
    nl(os);
}

//==============================================================================
//
// GenFunctionTable()
//
//     This function generates the function table for the given class. This
//     table contains pointers to the provider stubs.
//
//==============================================================================

static void GenFunctionTable(
    FILE* os, 
    const MI_ClassDecl* cd)
{
    const char ROLES[] = 
        "static void MI_CALL <ALIAS>_AssociatorInstances(\n"
        "    <ALIAS>_Self* self,\n"
        "    MI_Context* context,\n"
        "    const MI_Char* nameSpace,\n"
        "    const MI_Char* className,\n"
        "    const MI_Instance* instanceName,\n"
        "    const MI_Char* resultClass,\n"
        "    const MI_Char* role,\n"
        "    const MI_Char* resultRole,\n"
        "    const MI_PropertySet* propertySet,\n"
        "    MI_Boolean keysOnly,\n"
        "    const MI_Filter* filter)\n"
        "{\n"
        "    if (<ALIAS1>_IsA(instanceName))\n"
        "    {\n"
        "        if (_Match(role, MI_T(\"<ROLE1>\")) && \n"
        "            _Match(resultRole, MI_T(\"<ROLE2>\")))\n"
        "        {\n"
        "            <ALIAS>_AssociatorInstances<ROLE1>(\n"
        "                self, \n"
        "                context, \n"
        "                nameSpace, \n"
        "                className, \n"
        "                (<ALIAS1>*)instanceName, \n"
        "                resultClass, \n"
        "                propertySet, \n"
        "                keysOnly, \n"
        "                filter);\n"
        "            return;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    if (<ALIAS2>_IsA(instanceName))\n"
        "    {\n"
        "        if (_Match(role, MI_T(\"<ROLE2>\")) && \n"
        "            _Match(resultRole, MI_T(\"<ROLE1>\")))\n"
        "        {\n"
        "            <ALIAS>_AssociatorInstances<ROLE2>(\n"
        "                self, \n"
        "                context, \n"
        "                nameSpace, \n"
        "                className, \n"
        "                (<ALIAS2>*)instanceName, \n"
        "                resultClass, \n"
        "                propertySet, \n"
        "                keysOnly, \n"
        "                filter);\n"
        "            return;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    MI_Context_PostResult(context, MI_RESULT_OK);\n"
        "}\n"
        "\n"
        "static void MI_CALL <ALIAS>_ReferenceInstances(\n"
        "    <ALIAS>_Self* self,\n"
        "    MI_Context* context,\n"
        "    const MI_Char* nameSpace,\n"
        "    const MI_Char* className,\n"
        "    const MI_Instance* instanceName,\n"
        "    const MI_Char* role,\n"
        "    const MI_PropertySet* propertySet,\n"
        "    MI_Boolean keysOnly,\n"
        "    const MI_Filter* filter)\n"
        "{\n"
        "    if (<ALIAS1>_IsA(instanceName))\n"
        "    {\n"
        "        if (_Match(role, MI_T(\"<ROLE1>\")))\n"
        "        {\n"
        "            <ALIAS>_ReferenceInstances<ROLE1>(\n"
        "                self, \n"
        "                context, \n"
        "                nameSpace, \n"
        "                className, \n"
        "                (<ALIAS1>*)instanceName, \n"
        "                propertySet, \n"
        "                keysOnly, \n"
        "                filter);\n"
        "            return;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    if (<ALIAS2>_IsA(instanceName))\n"
        "    {\n"
        "        if (_Match(role, MI_T(\"<ROLE2>\")))\n"
        "        {\n"
        "            <ALIAS>_ReferenceInstances<ROLE2>(\n"
        "                self, \n"
        "                context, \n"
        "                nameSpace, \n"
        "                className, \n"
        "                (<ALIAS2>*)instanceName, \n"
        "                propertySet, \n"
        "                keysOnly, \n"
        "                filter);\n"
        "            return;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    MI_Context_PostResult(context, MI_RESULT_OK);\n"
        "}\n"
        "\n";

    const string alias = AliasOf(cd->name);

    // Generate the array of property declarations.

    if (cd->flags & MI_FLAG_ASSOCIATION)
    {
        if (CanGenerateAssocRoles(cd))
        {
            if (!s_options.association)
            {
                string r = ROLES;
                r = sub(r, "<ALIAS>", alias);
                SubRoles(cd, r);
                puts(os, r);
            }
        }
        else
            errRefPropCount(cd->name);

        const char T[] =
          "static MI_CONST MI_ProviderFT <ALIAS>_funcs =\n"
          "{\n"
          "  (MI_ProviderFT_Load)<ALIAS>_Load,\n"
          "  (MI_ProviderFT_Unload)<ALIAS>_Unload,\n"
          "  (MI_ProviderFT_GetInstance)<GETINSTANCE>,\n"
          "  (MI_ProviderFT_EnumerateInstances)<ALIAS>_EnumerateInstances,\n"
          "  (MI_ProviderFT_CreateInstance)<ALIAS>_CreateInstance,\n"
          "  (MI_ProviderFT_ModifyInstance)<ALIAS>_ModifyInstance,\n"
          "  (MI_ProviderFT_DeleteInstance)<ALIAS>_DeleteInstance,\n"
          "  (MI_ProviderFT_AssociatorInstances)<ALIAS>_AssociatorInstances,\n"
          "  (MI_ProviderFT_ReferenceInstances)<ALIAS>_ReferenceInstances,\n"
          "  (MI_ProviderFT_EnableIndications)NULL,\n"
          "  (MI_ProviderFT_DisableIndications)NULL,\n"
          "  (MI_ProviderFT_Subscribe)NULL,\n"
          "  (MI_ProviderFT_Unsubscribe)NULL,\n"
          "  (MI_ProviderFT_Invoke)NULL,\n"
          "};\n"
          "\n";

        /* Create substitution for <GETINSTANCE> */
        string gi;
        if (Contains(s_options.noGetInstance, cd->name))
            gi = "NULL";
        else
            gi = sub("<ALIAS>_GetInstance", "<ALIAS>", alias);

        string r = sub(T, "<ALIAS>", alias);
        r = sub(r, "<GETINSTANCE>", gi);

        puts(os, r);
    }
    else if (cd->flags & MI_FLAG_INDICATION)
    {
        const char T[] =
          "static MI_CONST MI_ProviderFT <ALIAS>_funcs =\n"
          "{\n"
          "  (MI_ProviderFT_Load)<ALIAS>_Load,\n"
          "  (MI_ProviderFT_Unload)<ALIAS>_Unload,\n"
          "  (MI_ProviderFT_GetInstance)NULL,\n"
          "  (MI_ProviderFT_EnumerateInstances)NULL,\n"
          "  (MI_ProviderFT_CreateInstance)NULL,\n"
          "  (MI_ProviderFT_ModifyInstance)NULL,\n"
          "  (MI_ProviderFT_DeleteInstance)NULL,\n"
          "  (MI_ProviderFT_AssociatorInstances)NULL,\n"
          "  (MI_ProviderFT_ReferenceInstances)NULL,\n"
          "  (MI_ProviderFT_EnableIndications)<ALIAS>_EnableIndications,\n"
          "  (MI_ProviderFT_DisableIndications)<ALIAS>_DisableIndications,\n"
          "  (MI_ProviderFT_Subscribe)<ALIAS>_Subscribe,\n"
          "  (MI_ProviderFT_Unsubscribe)<ALIAS>_Unsubscribe,\n"
          "  (MI_ProviderFT_Invoke)NULL,\n"
          "};\n"
          "\n";
        string r = sub(T, "<ALIAS>", alias);
        puts(os, r);
    }
    else
    {
        const char T1[] =
          "static MI_CONST MI_ProviderFT <ALIAS>_funcs =\n"
          "{\n"
          "  (MI_ProviderFT_Load)<ALIAS>_Load,\n"
          "  (MI_ProviderFT_Unload)<ALIAS>_Unload,\n"
          "  (MI_ProviderFT_GetInstance)<GETINSTANCE>,\n"
          "  (MI_ProviderFT_EnumerateInstances)<ALIAS>_EnumerateInstances,\n"
          "  (MI_ProviderFT_CreateInstance)<ALIAS>_CreateInstance,\n"
          "  (MI_ProviderFT_ModifyInstance)<ALIAS>_ModifyInstance,\n"
          "  (MI_ProviderFT_DeleteInstance)<ALIAS>_DeleteInstance,\n"
          "  (MI_ProviderFT_AssociatorInstances)NULL,\n"
          "  (MI_ProviderFT_ReferenceInstances)NULL,\n"
          "  (MI_ProviderFT_EnableIndications)NULL,\n"
          "  (MI_ProviderFT_DisableIndications)NULL,\n"
          "  (MI_ProviderFT_Subscribe)NULL,\n"
          "  (MI_ProviderFT_Unsubscribe)NULL,\n"
          "  (MI_ProviderFT_Invoke)NULL,\n"
          "};\n"
          "\n";
        const char T2[] =
          "static MI_CONST MI_ProviderFT <ALIAS>_funcs =\n"
          "{\n"
          "  (MI_ProviderFT_Load)<ALIAS>_Load,\n"
          "  (MI_ProviderFT_Unload)<ALIAS>_Unload,\n"
          "  (MI_ProviderFT_GetInstance)NULL,\n"
          "  (MI_ProviderFT_EnumerateInstances)NULL,\n"
          "  (MI_ProviderFT_CreateInstance)NULL,\n"
          "  (MI_ProviderFT_ModifyInstance)NULL,\n"
          "  (MI_ProviderFT_DeleteInstance)NULL,\n"
          "  (MI_ProviderFT_AssociatorInstances)NULL,\n"
          "  (MI_ProviderFT_ReferenceInstances)NULL,\n"
          "  (MI_ProviderFT_EnableIndications)NULL,\n"
          "  (MI_ProviderFT_DisableIndications)NULL,\n"
          "  (MI_ProviderFT_Subscribe)NULL,\n"
          "  (MI_ProviderFT_Unsubscribe)NULL,\n"
          "  (MI_ProviderFT_Invoke)NULL,\n"
          "};\n"
          "\n";


        // Only generate intrinsics for keyless classes:
        if (HasKeys(cd))
        {
            /* Create substitution for <GETINSTANCE> */
            string gi;
            if (Contains(s_options.noGetInstance, cd->name))
                gi = "NULL";
            else
                gi = sub("<ALIAS>_GetInstance", "<ALIAS>", alias);

            string r = sub(T1, "<ALIAS>", alias);
            r = sub(r, "<GETINSTANCE>", gi);
            puts(os, r);
        }
        else
        {
            string r = sub(T2, "<ALIAS>", alias);
            puts(os, r);
        }
    }
}

//==============================================================================
//
// GenClassDecl()
//
//     This function generates the class declaration for a MOF clas.
//
//==============================================================================

static void GenClassDecl(
    Parser& parser,
    FILE* os, 
    const MI_ClassDecl* cd)
{
    const string alias = AliasOf(cd->name);

    // Generate the qualifiers first.
    size_t numQualifiers = GenQualifiers(
        parser,
        os, 
        cd->qualifiers, 
        cd->numQualifiers,
        AliasOf(cd->name));

    const char T[] =
        "/* class <ALIAS> */\n"
        "MI_CONST <STATIC>MI_ClassDecl <ALIAS>_rtti =\n"
        "{\n"
        "    <FLAGS>, /* flags */\n"
        "    <CODE>, /* code */\n"
        "    MI_T(\"<CLASS>\"), /* name */\n"
        "    <QUALS>, /* qualifiers */\n"
        "    <NQUALS>, /* numQualifiers */\n"
        "    <PROPS>, /* properties */\n"
        "    <NPROPS>, /* numProperties */\n"
        "    sizeof(<ALIAS>), /* size */\n"
        "    <SUPER>, /* superClass */\n"
        "    <SUPERCLASSDECL>, /* superClassDecl */\n"
        "<METHODS>"
        "    &<SCHEMA>, /* schema */\n"
        "    <FUNCS>, /* functions */\n"
        "    NULL, /* owningClass */\n"
        "};\n";

    string r = T;
    r = sub(r, "<ALIAS>", alias);
    r = subx(r, "<CODE>", HashCode(cd->name));
    r = sub(r, "<CLASS>", cd->name);
    r = sub(r, "<FLAGS>", MakeFlags(cd->flags));

    if (s_options.schema.size())
        r = sub(r, "<SCHEMA>", s_options.schema.c_str());
    else
        r = sub(r, "<SCHEMA>", "schemaDecl");

    r = sub(r, "<STATIC>", "");

    if (cd->numProperties)
    {
        string s = alias + "_props";
        r = sub(r, "<PROPS>", s);
        r = sub(r, "<NPROPS>", "MI_COUNT(" + s + ")");
    }
    else
    {
        r = sub(r, "<PROPS>", "NULL");
        r = sub(r, "<NPROPS>", "0");
    }

    if (numQualifiers)
    {
        string s = alias + "_quals";
        r = sub(r, "<QUALS>", s);
        r = sub(r, "<NQUALS>", "MI_COUNT(" + s + ")");
    }
    else
    {
        r = sub(r, "<QUALS>", "NULL");
        r = sub(r, "<NQUALS>", "0");
    }

    if (cd->superClass)
    {
        r = sub(r, "<SUPER>", Quote(cd->superClass));
        string t = "&" + AliasOf(cd->superClass) + "_rtti";
        r = sub(r, "<SUPERCLASSDECL>", t);
    }
    else
    {
        r = sub(r, "<SUPER>", "NULL");
        r = sub(r, "<SUPERCLASSDECL>", "NULL");
    }

    if (cd->numMethods)
    {
        const char T2[] =
            "    <ALIAS>_meths, /* methods */\n"
            "    MI_COUNT(<ALIAS>_meths), /* numMethods */\n";
        string t2 = sub(T2, "<ALIAS>", alias);
        r = sub(r, "<METHODS>", t2);
    }
    else
    {
        const char T2[] =
            "    NULL, /* methods */\n"
            "    0, /* numMethods */\n";
        r = sub(r, "<METHODS>", T2);
    }

    if (providerClasses.find(cd->name) == providerClasses.end())
    {
        r = sub(r, "<FUNCS>", "NULL");
    }
    else
    {
        r = sub(r, "<FUNCS>", "&" + alias + "_funcs");
    }

    puts(os, r);
    nl(os);
}

//==============================================================================
//
// GenQualifierDecl()
//
//     This function generates a single qualifier declaration.
//
//==============================================================================

static void GenQualifierDecl(FILE* os, const MI_QualifierDecl* qd)
{
    const char T[] =
        "static MI_CONST MI_QualifierDecl <NAME>_qual_decl =\n"
        "{\n"
        "    MI_T(\"<NAME>\"), /* name */\n"
        "    <TYPE>, /* type */\n"
        "    <SCOPE>, /* scope */\n"
        "    <FLAVOR>, /* flavor */\n"
        "    <SUBSCRIPT>, /* subscript */\n"
        "    <VALUE>, /* value */\n"
        "};\n"
        "\n";

    string stem = string(qd->name) + "_qual_decl";

    // Generate the value.
    if (qd->value)
    {
        if (qd->flavor & MI_FLAG_TRANSLATABLE)
            GenValue(os, stem, qd->type, qd->value, true);
        else
            GenValue(os, stem, qd->type, qd->value, false);
    }

    string r = T;

    r = sub(r, "<NAME>", qd->name);
    r = sub(r, "<TYPE>", MakeType(qd->type));
    r = subu(r, "<SUBSCRIPT>", qd->subscript);
    r = sub(r, "<FLAVOR>", MakeFlavor(qd->flavor));
    r = sub(r, "<SCOPE>", MakeScope(qd->scope));

    if (qd->value)
        r = sub(r, "<VALUE>", "&" + stem + "_value");
    else
        r = sub(r, "<VALUE>", "NULL");

    puts(os, r);
}

//==============================================================================
//
// GenQualifierDecls()
//
//     This function generates an array of qualifier declarations.
//
//==============================================================================

size_t GenQualifierDecls(Parser& parser, FILE* os)
{
    size_t count = 0;

    /* Check if qualifiers are ignored */
    if (s_options.ignoreAllQualifiers)
        return 0;

    // Put the comment box.
    PutCommentBox(os, "Qualifier declarations");
    nl(os);

    vector<string> names;
    parser.getQualifierDeclNames(names);

    // Generate the individual qualifier declarations.
    for (size_t i = 0; i < names.size(); i++)
    {
        const MI_QualifierDecl* qd = parser.findQualifierDecl(names[i]);

        if (!qd)
        {
            err(ID_UNKNOWN_QUALIFIER, "unknown qualifier: %s", 
                names[i].c_str());
        }

        // Do not generate standard qualifiers.
        if (!s_options.standardQualifiers && 
            FindStandardQualifierDecl(qd->name))
        {
            continue;
        }

        GenQualifierDecl(os, qd);
        count++;
    }

    // Generate the qualifier declaration array.
    if (count)
    {
        putl(os, 
            "static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =");
        putl(os, "{");

        for (size_t i = 0; i < names.size(); i++)
        {
            const MI_QualifierDecl* qd = parser.findQualifierDecl(names[i]);

            // Do not generate standard qualifiers.
            if (!s_options.standardQualifiers && 
                FindStandardQualifierDecl(qd->name))
            {
                continue;
            }

            if (!qd)
            {
                err(ID_UNKNOWN_QUALIFIER, "unknown qualifier: %s", 
                    names[i].c_str());
            }

            put(os, "    &%s_qual_decl,\n", qd->name);
        }

        putl(os, "};");
        nl(os);
    }

    return count;
}

//==============================================================================
//
// GenClassSchema()
//
//     This function generates one class for the schema source file.
//
//==============================================================================

static void GenClassSchema(
    Parser& parser,
    FILE* os,
    const MI_ClassDecl* cd,
    const vector<string>& classNames)
{
    // Prevent recursion.
    {
        if (s_generated.find(cd->name) != s_generated.end())
            return;

        s_generated.insert(cd->name);
    }

    // Find direct dependencies of this class.
    vector<string> deps;
    FindDirectDependencies(cd, deps);

    // Recurse on dependencies.
    for (size_t i = 0; i < deps.size(); i++)
    {
        const MI_ClassDecl* tcd = parser.findClassDecl(deps[i].c_str());

        if (!tcd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", deps[i].c_str());

        GenClassSchema(parser, os, tcd, classNames);
    }

    // Refuse to generate same class more than once.
    if (generated_classes.find(cd->name) != generated_classes.end())
        return;

    generated_classes.insert(cd->name);

    // Generate comment box for this class.
    const string al = AliasOf(cd->name);
    PutCommentBox(os, al);
    nl(os);

    // Generate declarations.
    GenPropertyDecls(parser, os, cd);

    // Generate method declarations.
    GenMethodDecls(parser, os, cd);

    // Generate provider function table.
    if (providerClasses.find(cd->name) != providerClasses.end())
        GenFunctionTable(os, cd);

    // Generate the class declaration.
    GenClassDecl(parser, os, cd);
}

//==============================================================================
//
// GenSchemaSourceFile()
//
//     This function generates the schema.c source file, which contains the
//     qualifier declarations, class declarations, and the schema object that
//     refers to arrays of each.
//
//==============================================================================

static void GenSchemaSourceFile(
    Parser& parser,
    const vector<string>& classNames,
    const set<string>& /*classIdentifiers*/)
{
    // Open the file.
    string path = ExpandPath("schema.c");

    FILE* os = File_Open(path.c_str(), "w");

    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    GenStatikGenLine(os);

    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // Print warning box.
    PutCommentBox(os, WARNING);

    // Include <MI.h> header.
    putl(os, "#include <ctype.h>");
    putl(os, "#include <MI.h>");

    bool generateMatch = false;

    // Include each direct header file (headers will indirectly include others).
    for (size_t i = 0; i < classNames.size(); i++)
    {
        // Find the class.
        const MI_ClassDecl* cd = parser.findClassDecl(classNames[i].c_str());

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", classNames[i].c_str());

        if (cd->flags & MI_FLAG_ASSOCIATION)
        {
            if (CanGenerateAssocRoles(cd))
            {
                if (!s_options.association)
                    generateMatch = true;
            }
            else
                errRefPropCount(cd->name);
        }

        // Include the class header.
        const string alias = AliasOf(cd->name);
        putl(os, "#include \"%s.h\"", alias.c_str());
    }

    nl(os);

    // Generate forward reference to schema declaration.
    {
        PutCommentBox(os, "Schema Declaration");
        nl(os);

        if (s_options.schema.size())
            putl(os, "extern MI_SchemaDecl %s;", s_options.schema.c_str());
        else
            putl(os, "extern MI_SchemaDecl schemaDecl;");

        nl(os);
    }

    // Generate match function (if necessary)
    if (generateMatch)
    {
        const char MATCH[] =
            "static int _Match(const MI_Char* p, const MI_Char* q)\n"
            "{\n"
            "    if (!p || !q || !p[0] || !q[0])\n"
            "        return 1;\n"
            "\n"
            "    while (*p && *q)\n"
            "        if (toupper((MI_Uint16)*p++) - toupper((MI_Uint16)*q++))\n"
            "            return 0;\n"
            "\n"
            "    return *p == '\\0' && *q == '\\0';\n"
            "}\n"
            "\n";

        PutCommentBox(os, "_Match()");
        nl(os);
        puts(os, MATCH);
    }

    // Gen qualifier declarations.
    size_t numQualifierDecls = GenQualifierDecls(parser, os);

    // Generate class declarations.
    for (size_t i = 0; i < classNames.size(); i++)
    {
        // Find the class.
        const MI_ClassDecl* cd = parser.findClassDecl(classNames[i].c_str());

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", classNames[i].c_str());

        GenClassSchema(parser, os, cd, classNames);
    }

    // Generate server declaration.
    PutCommentBox(os, "__mi_server");
    nl(os);
    putl(os, "MI_Server* __mi_server;");

    // Generate MI_SchemaDecl.

    PutCommentBox(os, "Schema");
    nl(os);

    putl(os, "static MI_ClassDecl MI_CONST* MI_CONST classes[] =");
    putl(os, "{");

    set<string>::const_iterator p = generated_classes.begin();
    set<string>::const_iterator end = generated_classes.end();

    for (; p != end; p++)
    {
        // Find the class.
        const MI_ClassDecl* cd = 
            parser.findClassDecl((*p).c_str());

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", (*p).c_str());

        const string alias = AliasOf(cd->name);
        putl(os, "    &%s_rtti,", alias.c_str());
    }

    putl(os, "};");
    nl(os);

    {
        static const char T[] =
            "MI_SchemaDecl <SCHEMADECL> =\n"
            "{\n"
            "    <QUALIFIERDECLS>, /* qualifierDecls */\n"
            "    <NUMQUALIFIERDECLS>, /* numQualifierDecls */\n"
            "    classes, /* classDecls */\n"
            "    MI_COUNT(classes), /* classDecls */\n"
            "};\n"
            "\n";

        string r = T;

        if (s_options.schema.size())
            r = sub(r, "<SCHEMADECL>", s_options.schema);
        else
            r = sub(r, "<SCHEMADECL>", "schemaDecl");

        if (numQualifierDecls)
        {
            r = sub(r, "<QUALIFIERDECLS>", "qualifierDecls");
            r = sub(r, "<NUMQUALIFIERDECLS>", "MI_COUNT(qualifierDecls)");
        }
        else
        {
            r = sub(r, "<QUALIFIERDECLS>", "NULL");
            r = sub(r, "<NUMQUALIFIERDECLS>", "0");
        }

        puts(os, r);
    }

    // Generate MI_Server methods.
    if (!s_options.noProviders)
    {
        const char T[] =
            "MI_Result MI_CALL MI_Server_GetVersion(\n"
            "    MI_Uint32* version)"
            "{\n"
            "    return __mi_server->serverFT->GetVersion(version);\n"
            "}\n"
            "\n"
            "MI_Result MI_CALL MI_Server_GetSystemName(\n"
            "    const MI_Char** systemName)\n"
            "{\n"
            "    return __mi_server->serverFT->GetSystemName(systemName);\n"
            "}\n";

        PutCommentBox(os, "MI_Server Methods");
        nl(os);
        puts(os, T);
        nl(os);
    }

#if 0
    // Generate cross-check with class identifiers:
    {
        set<string>::const_iterator first = classIdentifiers.begin();
        set<string>::const_iterator last = classIdentifiers.end();

        while (first != last)
        {
            const string& s = *first++;
            putl(os, "#ifndef %s", s.c_str());
            putl(os, "# error \"generational inconsistency: %s is undefined\"", 
                s.c_str());
            putl(os, "#endif\n");
        }
    }
#endif

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenerateMI_Main()
//
//     This function generates the MI_Main() entry point. It returns a 
//     string instead of writing to the output stream directory. This is to
//     support patching of module.c.
//
//==============================================================================

string GenerateMI_Main()
{
    string result;

    // MI_Main() preamble:
    {
        string r = MODULE_C_TEMPLATE_2;

        if (s_options.schema.size()) 
            r = sub(r, "<SCHEMADECL>", s_options.schema);
        else
            r = sub(r, "<SCHEMADECL>", "schemaDecl");

        if (s_options.entryPoint.size()) 
            r = sub(r, "<ENTRYPOINT>", s_options.entryPoint);
        else
            r = sub(r, "<ENTRYPOINT>", "MI_Main");

        result += r;
    }

    // MI_Main() flags:
    {
        string r;

        if (!s_options.ignoreAllQualifiers)
        {
            if (!s_options.standardQualifiers)
                r += "    module.flags |= MI_MODULE_FLAG_STANDARD_QUALIFIERS;\n";

            if (s_options.descriptions)
                r += "    module.flags |= MI_MODULE_FLAG_DESCRIPTIONS;\n";

            if (s_options.values)
                r += "    module.flags |= MI_MODULE_FLAG_VALUES;\n";

            if (s_options.mappingStrings)
                r += "    module.flags |= MI_MODULE_FLAG_MAPPING_STRINGS;\n";

            if (s_options.booleanQualifiers)
                r += "    module.flags |= MI_MODULE_FLAG_BOOLEANS;\n";
        }

        if (s_options.cpp)
            r += "    module.flags |= MI_MODULE_FLAG_CPLUSPLUS;\n";

        if (s_options.localize)
            r += "    module.flags |= MI_MODULE_FLAG_LOCALIZED;\n";

        if (s_options.filterSupport)
            r += "    module.flags |= MI_MODULE_FLAG_FILTER_SUPPORT;\n";

        result += r;
    }

    // MI_Main() postamble:
    {
        string r = MODULE_C_TEMPLATE_3;

        if (s_options.schema.size()) 
            r = sub(r, "<SCHEMADECL>", s_options.schema);
        else
            r = sub(r, "<SCHEMADECL>", "schemaDecl");

        {
            char buf[64];
            Snprintf(buf, MI_COUNT(buf), "MI_MAKE_VERSION(%u,%u,%u)", 
                MI_MAJOR, MI_MINOR, MI_REVISION);
            r = sub(r, "<VERSION>", buf);
        }

        result += r;
    }

    return result;
}

//==============================================================================
//
// SkipSpace()
//
//     Skip over whitespace. Return true when the '\0' character is found.
//
//==============================================================================

static bool SkipSpace(const char*& p)
{
    while (isspace((unsigned char)*p))
        p++;

    return *p == '\0';
}

//==============================================================================
//
// GenModuleSourceFile()
//
//     This function generates the module.c source file, which contains the
//     MI_Main() entry point.
//
//==============================================================================

static void GenModuleSourceFile()
{
    // Open the file.
    const string path = ExpandPath("module.c");

    if (Exists(path.c_str()))
    {
        // Read file into memory.
        vector<char> data;

        if (!Inhale(path.c_str(), data))
        {
            err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                path.c_str());
        }


        // Replace MI_Main() body with new MI_Main() body.
        const char* start = &data[0];
        const char* end = &data[data.size()-1];
        const char* p = start;
        bool found = false;

        // Match "MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(...) {}
        while (p != end)
        {
            const char* first = p;

            // Expect 'MI_EXTERN_C' [optionally]
            if (strncmp(p, "MI_EXTERN_C", 11) == 0)
            {
                p += 11;

                // Skip whitespace:
                if (SkipSpace(p))
                    break;
            }

            // Expect 'MI_EXPORT'
            if (strncmp(p, "MI_EXPORT", 9) != 0)
            {
                p++;
                continue;
            }
            p += 9;

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Expect 'MI_Module'
            if (strncmp(p, "MI_Module", 9) != 0)
            {
                p++;
                continue;
            }
            p += 9;

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Expect '*'
            if (*p != '*')
            {
                p++;
                continue;
            }
            p++;

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Skip 'MI_MAIN_CALL'
            {
                const char TMP[] = "MI_MAIN_CALL";

                if (strncmp(p, TMP, sizeof(TMP)-1) == 0)
                    p += sizeof(TMP)-1;
            }

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Expect 'MI_Main'
            {
                const char *TMP = 
                    (s_options.entryPoint.empty() ? "MI_Main" : s_options.entryPoint.c_str());

                if (strncmp(p, TMP, strlen(TMP)) != 0)
                {
                    p++;
                    continue;
                }
                p += strlen(TMP);
            }

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Expect '('
            if (*p != '(')
            {
                p++;
                continue;
            }

            // Skip non ')' chars.
            while (*p && *p != ')')
                p++;

            // Expect ')'
            if (*p != ')')
            {
                p++;
                continue;
            }
            p++;

            // Skip whitespace:
            if (SkipSpace(p))
                break;

            // Expect '{'
            if (*p != '{')
            {
                p++;
                continue;
            }

            // Skip non '}' chars.
            while (*p && *p != '}')
                p++;

            // Expect '}'
            if (*p != '}')
            {
                p++;
                continue;
            }
            p++;

            const char* last = p;

            found = true;
            string tmp = &data[0];
            string r;
            r.append(start, first - start);
            r.append(GenerateMI_Main());
            r.append(last);

            // Rewrite the file.
            {
                FILE* os = File_Open(path.c_str(), "w");

                if (!os)
                {
                    err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", 
                        path.c_str());
                }

                Fprintf(s_stdout, ID_PATCHING, "Patching %s\n", path.c_str());
                put(os, "%s", r.c_str());

                fclose(os);
            }
            break;
        }

        // If MI_Main() not found.
        if (!found)
        {
            err(ID_FAILED_TO_PATCH_MODULE, 
                "Unable to patch module.c: cannot find %s() body: %s",
                (s_options.entryPoint.empty() ? 
                    "MI_Main" : s_options.entryPoint.c_str()),
                path.c_str());
        }

        return;
    }

    FILE* os = File_Open(path.c_str(), "w");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    GenStatikGenLine(os);
    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // Generate part 1:
    {
        string r = MODULE_C_TEMPLATE_1;

        if (s_options.schema.size()) 
            r = sub(r, "<SCHEMADECL>", s_options.schema);
        else
            r = sub(r, "<SCHEMADECL>", "schemaDecl");

        put(os, "%s", r.c_str());
    }

    // Generate MI_Main()
    {
        string r = GenerateMI_Main();
        put(os, "%s\n", r.c_str());
    }

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenModuleCppSourceFile()
//
//     This function generates the module.cpp source file, which contains the
//     Module class definiiton.
//
//==============================================================================

static void GenModuleCppSourceFile()
{
    // Open the file.
    const string path = ExpandPath("module.cpp");

    if (Exists(path.c_str()))
    {
        Fprintf(s_stdout, ID_SKIPPING, "Skipping %s\n", path.c_str());
        return;
    }

    FILE* os = File_Open(path.c_str(), "w");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // simple template - no parameters
    {
        put(os, "%s\n", MODULE_CPP_TEMPLATE);
    }

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenModuleCppHeaderFile()
//
//     This function generates the module.h header file, which contains the
//     Module class declaration.
//
//==============================================================================

static void GenModuleCppHeaderFile()
{
    // Open the file.
    const string path = ExpandPath("module.h");

    if (Exists(path.c_str()))
    {
        Fprintf(s_stdout, ID_SKIPPING, "Skipping %s\n", path.c_str());
        return;
    }

    FILE* os = File_Open(path.c_str(), "w");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // simple template - no parameters
    {
        put(os, "%s\n", MODULE_H_TEMPLATE);
    }

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenModuleStubsFile()
//
//     This function generates the stubs.cpp source file, which contains the
//     wrapper functions to convert 'c' style server calls into provider class 
//     calls
//
//==============================================================================

static void GenModuleStubsFile(
    Parser& parser,
    const vector<string>& classNames)
{
    // Open the file.
    string path = ExpandPath("stubs.cpp");

    FILE* os = File_Open(path.c_str(), "w");

    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    GenStatikGenLine(os);

    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // Print warning box.
    PutCommentBox(os, WARNING);

    // Include <MI.h> header.
    putl(os, "#include <MI.h>");
    putl(os, "#include \"module.h\"");

    // Include each direct header file (headers will indirectly include others).
    for (size_t i = 0; i < classNames.size(); i++)
    {
        // Find the class.
        const MI_ClassDecl* cd = parser.findClassDecl(classNames[i].c_str());

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", classNames[i].c_str());

        /* skip not-requested classes */
        if (providerClasses.find(cd->name) == providerClasses.end())
            continue;

        // Include the class header.
        const string alias = AliasOf(cd->name);
        putl(os, "#include \"%s_Class_Provider.h\"", alias.c_str());
    }

    nl(os);
    putl(os, "using namespace mi;");
    nl(os);

    // generate c++ wrappers
    for (size_t i = 0; i < classNames.size(); i++)
    {
        // Find the class.
        const MI_ClassDecl* cd = parser.findClassDecl(classNames[i].c_str());

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", classNames[i].c_str());

        /* skip not-requested classes */
        if (providerClasses.find(cd->name) == providerClasses.end())
            continue;

        // generate stub for the class
        GenerateClassStub( os, cd );
    }

    // Generate module-level load/unload
    {
        string r = STUBS_LOAD_UNLOAD_TEMPLATE;

        if (s_options.schema.size()) 
            r = sub(r, "<SCHEMADECL>", s_options.schema);
        else
            r = sub(r, "<SCHEMADECL>", "schemaDecl");

        put(os, "%s", r.c_str());
    }

    // Generate MI_Main()
    {
        string r = GenerateMI_Main();
        put(os, "%s\n", r.c_str());
    }

    nl(os);

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenerateStringsFile()
//
//     This function generates the string.rc file, which contains the
//     localized qualifier strings (only called if -l option present)
//
//==============================================================================

static void GenerateStringsFile()
{
    // Open the file.
    const string path = ExpandPath("strings.rc");
    FILE* os = File_Open(path.c_str(), "w");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    GenStatikGenLine(os);
    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // Generate file with the following format.
    //
    //     STRINGTABLE
    //     {
    //         <INTEGER-IDENTIFIER>, <STRING>
    //     }
    {
        fprintf(os, "STRINGTABLE\n");
        fprintf(os, "{\n");

        for (size_t i = 0; i < s_localizations.size(); i++)
        {
            MI_Uint32 id = (MI_Uint32)(i + 1);
            const string& str = s_localizations[i];
            fprintf(os, "    %u, \"%s\"\n", id, str.c_str());
        }

        fprintf(os, "}\n");
    }

    // Close the file.
    fclose(os);
}

static string _GetClassInheritanceRegistrationEntry(
    const MI_ClassDecl* cd
    )
{
    string res = cd->name;

    while (cd->superClassDecl)
    {
        res += ",";
        cd = cd->superClassDecl;
        res += cd->name;
    }

    return res;
}

static string _GetClassRegistrationEntry(
    Parser& parser,
    const MI_ClassDecl* cd
    )
{
    string res;

    if (cd->flags & MI_FLAG_ASSOCIATION)
    {
        const MI_ClassDecl* cd_left = 0, *cd_right = 0;
        // find two ref members
        for (MI_Uint32 i = 0; i < cd->numProperties; i++)
        {
            if (cd->properties[i]->type == MI_REFERENCE)
            {
                const MI_ClassDecl* cd_ref = 
                    parser.findClassDecl(cd->properties[i]->className);

                if (!cd_ref)
                {
                    err(ID_UNKNOWN_CLASS, "unknown class: %s", 
                        cd->properties[i]->className);
                }

                if (!cd_left)
                    cd_left = cd_ref;
                else
                    cd_right = cd_ref;
            }
        }

        if (!cd_right)
            errRefPropCount(cd->name);

        res = _GetClassInheritanceRegistrationEntry(cd_left) +
            "+" +
            _GetClassInheritanceRegistrationEntry(cd) + 
            "+" +
            _GetClassInheritanceRegistrationEntry(cd_right);
    }
    else
    {
        res = _GetClassInheritanceRegistrationEntry(cd);
    }
    return res;
}

//==============================================================================
//
// GenerateRegistryFile()
//
//     This function generates skeleton of the provider registry file, 
//     which contains information server will use to operate with provider 
//     (only called if -reg option present)
//
//==============================================================================

static void GenerateRegistryFile( 
    Parser& parser, 
    const vector<string>& classNames)
{
    // Open the file.
    const string path = ExpandPath(s_options.providerRegistryPath);
    FILE* os = File_Open(path.c_str(), "a");
    
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", path.c_str());

    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", path.c_str());

    // Generate file with the following format.
    //
    //     statik:test/c:MSFT_Person,MSFT_Animal,MSFT_Base + MSFT_Friends + 
    //     MSFT_Person,MSFT_Animal,MSFT_Base:PersonProvider
    //
    {
        fprintf(os, "# auto-generated skeleton of registry file\n");
        fprintf(os, "# please update it with correct namespace[s]\n");

        for (size_t i = 0; i < classNames.size(); i++)
        {
            const char* cn = classNames[i].c_str();
            const MI_ClassDecl* cd = parser.findClassDecl(cn);

            if (!cd)
                err(ID_UNKNOWN_CLASS, "unknown class: %s", cn);

            fprintf(os, "statik:<ns>:%s:<provider>\n",
                _GetClassRegistrationEntry(parser,cd).c_str());

        }

        for (size_t i = 0; i < s_localizations.size(); i++)
        {
            MI_Uint32 id = (MI_Uint32)(i + 1);
            const string& str = s_localizations[i];
            fprintf(os, "    %u, \"%s\"\n", id, str.c_str());
        }

        fprintf(os, "\n");
    }

    // Close the file.
    fclose(os);
}

//==============================================================================
//
// GenMakefile()
//
//     This function generates a 'GNUmakefile' for the given provider.
//
//==============================================================================

static void GenMakefile(
    const string& library,
    const vector<string>& classNames,
    const string& cmdLine)
{
    const char MAKEFILE[] = "GNUmakefile";

    MI_UNUSED(library);

    // If makefile already exists, quit:
    if (Exists(MAKEFILE))
    {
        Fprintf(s_stdout, ID_SKIPPING, "Skipping %s\n", MAKEFILE);
        return;
    }

    // Open Makefile:
    FILE* os = File_Open(MAKEFILE, "w");
    if (!os)
        err(ID_FAILED_TO_OPEN_FILE, "failed to open file: %s", MAKEFILE);

    {
        // 'OMIMAK' variable.
        string OMIMAK = string(OMI_GetPath(ID_DATADIR)) + "/omi.mak";

        // 'PROVIDER' variable.
        string PROVIDER = s_options.providerName;

        // 'SOURCES' variable.
        string SOURCES;
        {
            if (s_options.cpp)
                SOURCES = "$(wildcard *.c *.cpp)";
            else
                SOURCES = "$(wildcard *.c)";
        }

        // 'CLASSNAMES' variable.
        string CLASSES;
        {
            for (size_t i = 0; i < classNames.size(); i++)
            {
                CLASSES += classNames[i];
                if (i + 1 == classNames.size())
                    CLASSES += ' ';
            }
        }

        string r;

        if (s_options.cpp)
            r = CXXMAKEFILE_TEMPLATE;
        else
            r = CMAKEFILE_TEMPLATE;

        r = sub(r, "<OMIMAK>", OMIMAK);
        r = sub(r, "<PROVIDER>", PROVIDER);
        r = sub(r, "<SOURCES>", SOURCES);
        r = sub(r, "<CLASSES>", CLASSES);
        r = sub(r, "<CMDLINE>", cmdLine);
        r = subu(r, "<MIAPIVERSION>", _MIAPIVERSION);
        puts(os, r);
    }

    // Print creation message:
    Fprintf(s_stdout, ID_CREATING, "Creating %s\n", MAKEFILE);

    // Close file:
    fclose(os);
}
//==============================================================================
//
// main()
//
//     This program generates source code from MOF definitions. The source 
//     includes run-time type information for class declarations and qualifier
//     declarations as well as class provider stubs.
//
//==============================================================================

int GeneratorMain(
    const std::string& programNameArg,
    const std::vector<std::string>& mofFilesArg,
    const std::vector<std::string>& classNamesArg,
    const GeneratorOptions& optionsArg)
{
    arg0 = programNameArg.c_str();

    // Make a copy of the vector whose strings we can later modify in place.
    vector<string> localClassNamesArg;
    {
        for (size_t i = 0; i < classNamesArg.size(); i++)
            localClassNamesArg.push_back(classNamesArg[i].c_str());
    }

#ifdef WIN32
    // Platform-specific trick to get compatible float format
    _set_output_format(_TWO_DIGIT_EXPONENT);
#endif

    // clear global params 
    generated_headers.clear();
    generated_classes.clear();
    providerClasses.clear();
    s_generated.clear();
    aliases.clear();
    s_localizations.clear();

    // Save command-line options.
    s_options = optionsArg;

    // Create directory given by -d option.
    if (s_options.dir.size())
        Mkdir(s_options.dir.c_str(), 0777);

    // Check schema given by -s otpion.
    if (s_options.schema.size())
    {
        /* Check whether this is a valid C identifier */
        if (!ValidIdent(s_options.schema))
            err(ID_INVALID_SCHEMA_OPTION, "invalid schema option: %s", 
                s_options.schema.c_str());
    }

    if ( s_options.quiet )
    {
        s_stdout = File_Open(NULL_FILE, "a");
    }
    else
    {
        s_stdout = stdout;
    }

    // Create the parser.
    Parser parser(s_options.paths, !s_options.no_warnings);

    // Parse all the MOF files.
    for (size_t i = 0; i < mofFilesArg.size(); i++)
    {
        const char* path = mofFilesArg[i].c_str();

        if (parser.parse(path) != 0)
        {
            err(ID_FAILED_TO_PARSE_MOF_FILE, "failed to parse MOF file: %s",
                path);
        }
    }

    // Build the alias table, which maps a MOF classname to an alias name.
    // Aliases are introduced by command-line classname arguments of the 
    // form <CLASSNAME>=<ALIAS>. For each command line argument of this
    // form, put an entry in the alias table. Use the lexographical case
    // for the class define in MOF (rather than defined on the command line).
    for (size_t i = 0; i < localClassNamesArg.size(); i++)
    {
        const char* className = localClassNamesArg[i].c_str();
        char* alias = (char*)strchr(className, '=');

        if (alias)
        {
            *alias++ = '\0';

            const MI_ClassDecl* cd = parser.findClassDecl(className);

            if (!cd)
                err(ID_UNKNOWN_CLASS, "unknown class: %s", className);

            aliases[cd->name] = alias;
        }
    }

    // Form a complete list of class names (excluding duplicates).

    vector<string> classNames;

    if (s_options.all)
    {
        parser.getClassNames(classNames);
    }
    else
    {
        for (size_t i = 0; i < localClassNamesArg.size(); i++)
        {
            const char* className = localClassNamesArg[i].c_str();
            const MI_ClassDecl* cd = parser.findClassDecl(className);

            if (!cd)
                err(ID_UNKNOWN_CLASS, "unknown, class: %s", className);

            // Save class name.
            if (!Contains(classNames, cd->name))
                classNames.push_back(cd->name);

            // Reject classes that are abstract.
            if (cd->flags & MI_FLAG_ABSTRACT && !s_options.noProviders)
            {
                err(ID_REFUSED_TO_GENERATE_PROVIDER_FOR_ABSTRACT_CLASS, 
                    "refused to generated provider for abstract class: %s", 
                    cd->name);
            }
        }
    }

    // Form the set of classes for which there are providers (partial 
    // generation is performed on dependent classes (for which there is
    // no actual provider).

    if (!s_options.noProviders)
    {
        for (size_t i = 0; i < classNames.size(); i++)
        {
            providerClasses.insert(classNames[i]);
        }
    }

    // Add extra classes (given by -e option) to class list to be generated.

    for (size_t i = 0; i < s_options.extraClasses.size(); i++)
    {
        const MI_ClassDecl* cd = parser.findClassDecl(
            s_options.extraClasses[i].c_str());

        if (!cd)
        {
            err(ID_UNKNOWN_CLASS, "unknown class: %s", 
                s_options.extraClasses[i].c_str());
        }

        classNames.push_back(cd->name);
    }

    // Generate the classes.

    set<string> classIdentifiers;

    for (size_t i = 0; i < classNames.size(); i++)
    {
        const char* cn = classNames[i].c_str();
        const MI_ClassDecl* cd = parser.findClassDecl(cn);

        if (!cd)
            err(ID_UNKNOWN_CLASS, "unknown class: %s", cn);

        GenClassHeader(parser, cd, classIdentifiers);

        if (providerClasses.find(cd->name) != providerClasses.end())
        {
            if (s_options.cpp)
                GenCppClassSource(cd);
            else
                GenClassSource(cd);
        }
    }

    // Generate the schema.c file.
    GenSchemaSourceFile(parser, classNames, classIdentifiers);

    // generate c++ wrappers - stubs.cpp file
    if (!s_options.noProviders && s_options.cpp)
        GenModuleStubsFile(parser, classNames);

    // Generate the module.h and module.c files.
    if (!s_options.noProviders)
    {
        if (s_options.cpp)
        {
            GenModuleCppSourceFile();
            GenModuleCppHeaderFile();
        }
        else
            GenModuleSourceFile();
    }

    // Generate the strings.rc.
    if (s_options.localize)
        GenerateStringsFile();

    // Generate provider registry file.
    if (!s_options.providerRegistryPath.empty())
        GenerateRegistryFile(parser, classNames);

    if ( s_options.quiet )
    {
        fclose( s_stdout );
        s_stdout = 0;
    }

    // Generate the GNUmakefile.
    if (s_options.providerName.size())
        GenMakefile(s_options.providerName, classNamesArg, s_options.cmdLine);

    if (s_options.python)
    {
        GenSchemaSourceFile_Py (s_options, parser, classNames);
        GenMI_Main_Py (s_options, parser, classNames);
    }

    return 0;
}
