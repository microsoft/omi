/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <string>
#include <micodec.h>
#include <nits.h>
#include "Class1.h"
#include "Class2.h"
#include "Widget.h"
#include "Gadget.h"
#include "Link.h"
#include "Container.h"
#include "Assoc1.h"
#include "SubClass.h"
#include "Thing.h"
#include "instance.h"
#include "class.h"

using namespace std;

#if (MI_CHAR_TYPE == 1)
# define T(STR) STR
#else
# define __T(STR) L ## STR
# define T(STR) __T(STR)
#endif

#define TRACE printf("TRACE: %s(%u)\n", __FILE__, __LINE__)

extern "C"
{
    extern MI_SchemaDecl schemaDecl;
}

//=============================================================================
//
// CHECK()
//
//=============================================================================

#define CHECK(COND) NitsAssert(COND, T("CHECK"))

//=============================================================================
//
// STRCMP()
// STRLEN()
// STRCHR()
// PRINTF()
// String
//
//=============================================================================

#if (MI_CHAR_TYPE == 1)
# define STRCMP strcmp
# define STRLEN strlen
# define STRCHR strchr
# define PRINTF printf
typedef string String;
#else
# define STRCMP ::wcscmp
# define STRLEN ::wcslen
# define STRCHR ::wcschr
# define PRINTF ::wprintf
typedef wstring String;
#endif

//=============================================================================
//
// Serializer
//
//     Simple wrapper class for MI_Serializer (to simply tests below).
//
//=============================================================================

class Serializer
{
public:

    Serializer()
    {
        memset(&m_app, 0, sizeof(m_app));

        m_result = MI_Application_NewSerializer_Mof(
            &m_app, 
            0, 
            (MI_Char*)T("MOF"), 
            &m_serializer);
    }

    ~Serializer()
    {
        if (m_result != MI_RESULT_OK)
            return;

        ft()->Close(&m_serializer);
    }

    template<class T>
    bool SerializeInstance(
        const T& instance, 
        MI_Uint32 flags,
        vector<MI_Char>& data)
    {
        return _SerializeInstance(&instance.__instance, flags, data);
    }

    bool SerializeClass(
        const MI_Class* clss,
        MI_Uint32 flags,
        vector<MI_Char>& data)
    {
        if (m_result != MI_RESULT_OK)
            return false;

#if 0
        MI_Uint8* buffer = m_buffer;
        MI_Uint32 bufferLength = sizeof(m_buffer);
        MI_Uint32 bufferNeeded = sizeof(m_buffer);
#else
        MI_Uint8* buffer = NULL;
        MI_Uint32 bufferLength = 0;
        MI_Uint32 bufferNeeded = 0;
#endif

        for (;;)
        {
            MI_Result r = ft()->SerializeClass(
                &m_serializer,
                flags,
                clss,
                buffer,
                bufferLength,
                &bufferNeeded);

            if (r != MI_RESULT_OK && bufferLength < bufferNeeded)
            {
                buffer = (MI_Uint8*)malloc(bufferNeeded);

                if (!buffer)
                    return false;
                bufferLength = bufferNeeded;
                continue;
            }

            if (r != MI_RESULT_OK)
                return false;

            data.insert(
                data.end(),
                (const MI_Char*)buffer,
                (const MI_Char*)(buffer + bufferNeeded));

            if (buffer != m_buffer)
                free(buffer);

            return true;
        }
    }

    operator bool() const
    {
        return m_result == MI_RESULT_OK;
    }

private:

    MI_SerializerFT* ft()
    {
        return (MI_SerializerFT*)m_serializer.reserved2;
    }

    bool _SerializeInstance(
        const MI_Instance* instance, 
        MI_Uint32 flags,
        vector<MI_Char>& data)
    {
        if (m_result != MI_RESULT_OK)
            return false;

#if 0
        MI_Uint8* buffer = m_buffer;
        MI_Uint32 bufferLength = sizeof(m_buffer);
        MI_Uint32 bufferNeeded = sizeof(m_buffer);
#else
        MI_Uint8* buffer = NULL;
        MI_Uint32 bufferLength = 0;
        MI_Uint32 bufferNeeded = 0;
#endif

        for (;;)
        {
            MI_Result r = ft()->SerializeInstance(
                &m_serializer,
                flags,
                instance,
                buffer,
                bufferLength,
                &bufferNeeded);

            if (r != MI_RESULT_OK && bufferLength < bufferNeeded)
            {
                buffer = (MI_Uint8*)malloc(bufferNeeded);

                if (!buffer)
                    return false;
                bufferLength = bufferNeeded;
                continue;
            }

            if (r != MI_RESULT_OK)
                return false;

            data.insert(
                data.end(),
                (const MI_Char*)buffer,
                (const MI_Char*)(buffer + bufferNeeded));

            if (buffer != m_buffer)
                free(buffer);

            return true;
        }
    }

    MI_Result m_result;
    MI_Application m_app;
    MI_Serializer m_serializer;
    MI_Uint8 m_buffer[4096];
};

//=============================================================================
//
// _ConstructInstance()
//
//     Helper function to construct MI_Instances by classname:
//
//=============================================================================

static bool _ConstructInstance(
    MI_Instance* instance,
    const MI_Char* className)
{
    const MI_ClassDecl* cd = 0;

    for (MI_Uint32 i = 0; i < schemaDecl.numClassDecls; i++)
    {
        if (STRCMP(schemaDecl.classDecls[i]->name, className) == 0)
        {
            cd = schemaDecl.classDecls[i];
            break;
        }
    }

    if (!cd)
        return false;

    Test_Instance_Construct(instance, cd);
    return true;
}

//=============================================================================
//
// _ConstructClass()
//
//     Helper function to construct MI_Classs by classname:
//
//=============================================================================

static bool _ConstructClass(
    MI_Class* clss,
    const MI_Char* className)
{
    const MI_ClassDecl* cd = 0;

    for (MI_Uint32 i = 0; i < schemaDecl.numClassDecls; i++)
    {
        if (STRCMP(schemaDecl.classDecls[i]->name, className) == 0)
        {
            cd = schemaDecl.classDecls[i];
            break;
        }
    }

    if (!cd)
        return false;

    Test_Class_Construct(clss, cd);
    return true;
}

//=============================================================================
//
// _Diff()
//
//=============================================================================

static bool _Diff(
    const MI_Char* data1,
    const MI_Char* data2)
{
    const MI_Char* p = data1;
    const MI_Char* q = data2;
    unsigned int line = 1;

    while (*p && *q)
    {
        const MI_Char* pend = STRCHR(p, '\n');

        if (!pend)
            pend = p + STRLEN(p);

        const MI_Char* qend = STRCHR(q, '\n');

        if (!qend)
            qend = q + STRLEN(q);

        String line1(p, pend - p);

        String line2(q, qend - q);

        if (line1 != line2)
        {
            PRINTF(T("\n********** line: %u\n"), line);
            PRINTF(T("< %s\n"), line1.c_str());
            PRINTF(T("> %s\n"), line2.c_str());
            return false;
        }

#if 0
        PRINTF(T("LINE[%s]\n"), line1.c_str());
#endif

        if (*pend == '\n')
            pend++;

        if (*qend == '\n')
            qend++;

        line++;
        p = pend;
        q = qend;
    }

    if (*p)
    {
        PRINTF(T("\n********** line: %u\n"), line);
        PRINTF(T("< %s\n"), p);
        return false;
    }

    if (*q)
    {
        PRINTF(T("\n********** line: %u\n"), line);
        PRINTF(T("> %s\n"), q);
        return false;
    }

    return true;
}

//=============================================================================
//
// TestCreateMofSerializer()
//
//=============================================================================

NitsTest(TestCreateMofSerializer)
{
    Serializer ser;
    CHECK(ser == true);
}
NitsEndTest

//=============================================================================
//
// TestSerializeClass1()
//
//=============================================================================

NitsTest(TestSerializeClass1)
{
    const MI_Char expect[] =
        T("instance of Class1\n")
        T("{\n")
        T("    Key = 56789;\n")
        T("    Msg = \"The answer\\nis \\\"5\\\"\";\n")
        T("    Flag = True;\n")
        T("    Numbers = {1, 2, 3, 4, 5};\n")
        T("    Colors = {\"RED\", \"GREEN\", \"BLUE\"};\n")
        T("    Unprintable = \"\\X01\\X02\\X7F\";\n")
        T("    Char = '\\X7F';\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct Class1:
    Class1 inst;
    CHECK(_ConstructInstance(&inst.__instance, T("Class1")));

    // Class1.Key:
    inst.Key.exists = MI_TRUE;
    inst.Key.value = 56789;

    // Class1.Flag:
    inst.Flag.exists = MI_TRUE;
    inst.Flag.value = MI_TRUE;

    // Class1.Msg:
    inst.Msg.exists = MI_TRUE;
    inst.Msg.value = T("The answer\nis \"5\"");

    // Class1.Numbers:
    {
        static MI_Uint8 data[] = { 1, 2, 3, 4, 5 };
        MI_Uint32 size = MI_COUNT(data);
        inst.Numbers.exists = MI_TRUE;
        inst.Numbers.value.data = data;
        inst.Numbers.value.size = size;
    }

    // Class1.Colors:
    {
        static MI_Char* data[] = { (MI_Char*)T("RED"), (MI_Char*)T("GREEN"), (MI_Char*)T("BLUE") };
        MI_Uint32 size = MI_COUNT(data);
        inst.Colors.exists = MI_TRUE;
        inst.Colors.value.data = data;
        inst.Colors.value.size = size;
    }

    // Class1.Msg:
    {
        inst.Unprintable.exists = MI_TRUE;
        static const MI_Char str[4] = { 1, 2, 127, '\0' };
        inst.Unprintable.value = (MI_Char*)str;
    }

    // Class1.Char:
    inst.Char.exists = MI_TRUE;
    inst.Char.value = (MI_Char)127;

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(inst, 0, data));
    data.push_back('\0');

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeLink()
//
//=============================================================================

NitsTest(TestSerializeLink)
{
    const MI_Char expect[] =
        T("instance of Widget as $Alias00000002\n")
        T("{\n")
        T("    Key = 1001;\n")
        T("};\n")
        T("\n")
        T("instance of Gadget as $Alias00000003\n")
        T("{\n")
        T("    Key = 2001;\n")
        T("};\n")
        T("\n")
        T("instance of Link\n")
        T("{\n")
        T("    Left = $Alias00000002;\n")
        T("    Right = $Alias00000003;\n")
        T("};\n")
        T("\n")
        T("instance of Embedded as $Alias00000009\n")
        T("{\n")
        T("    Key = 3001;\n")
        T("};\n")
        T("\n")
        T("instance of Widget as $Alias0000000A\n")
        T("{\n")
        T("    Key = 1001;\n")
        T("    Emb = $Alias00000009;\n")
        T("};\n")
        T("\n")
        T("instance of Embedded as $Alias0000000B\n")
        T("{\n")
        T("    Key = 3001;\n")
        T("};\n")
        T("\n")
        T("instance of Embedded as $Alias0000000C\n")
        T("{\n")
        T("    Key = 3001;\n")
        T("};\n")
        T("\n")
        T("instance of Gadget as $Alias0000000D\n")
        T("{\n")
        T("    Key = 2001;\n")
        T("    Emb = {$Alias0000000B, $Alias0000000C};\n")
        T("};\n")
        T("\n")
        T("instance of Container\n")
        T("{\n")
        T("    Wid = $Alias0000000A;\n")
        T("    Gad = $Alias0000000D;\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct Embedded:
    Embedded embedded;
    CHECK(_ConstructInstance(&embedded.__instance, T("Embedded")));

    // Construct Widget:
    Widget widget;
    CHECK(_ConstructInstance(&widget.__instance, T("Widget")));

    // Construct Gadget:
    Gadget gadget;
    CHECK(_ConstructInstance(&gadget.__instance, T("Gadget")));

    // Construct Link:
    Link link;
    CHECK(_ConstructInstance(&link.__instance, T("Link")));
    Container container;
    CHECK(_ConstructInstance(&container.__instance, T("Container")));

    // Embedded.Key:
    embedded.Key.exists = MI_TRUE;
    embedded.Key.value = 3001;

    // Widget.Key:
    widget.Key.exists = MI_TRUE;
    widget.Key.value = 1001;

    // Embedded.Key:
    widget.Emb.exists = MI_TRUE;
    widget.Emb.value = &embedded;

    // Gadget.Key:
    gadget.Key.exists = MI_TRUE;
    gadget.Key.value = 2001;

    // Gadget.Emb:
    {
        static const Embedded* data[2];
        data[0] = &embedded;
        data[1] = &embedded;

        gadget.Emb.exists = MI_TRUE;
        gadget.Emb.value.data = (Embedded**)data;
        gadget.Emb.value.size = MI_COUNT(data);
    }

    // Link.Left:
    link.Left.exists = MI_TRUE;
    link.Left.value = &widget;

    // Link.Right:
    link.Right.exists = MI_TRUE;
    link.Right.value = &gadget;

    // Container.Wid:
    container.Wid.exists = MI_TRUE;
    container.Wid.value = &widget;

    // Container.Gad:
    container.Gad.exists = MI_TRUE;
    container.Gad.value = &gadget;

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(link, 0, data));
    CHECK(ser.SerializeInstance(container, 0, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeClass2()
//
//=============================================================================

NitsTest(TestSerializeClass2)
{
    const MI_Char expect[] =
        T("instance of Class2\n")
        T("{\n")
        T("    Key = 12345;\n")
        T("    B = True;\n")
        T("    U8 = 8;\n")
        T("    S8 = -8;\n")
        T("    U16 = 16;\n")
        T("    S16 = -16;\n")
        T("    U32 = 32;\n")
        T("    S32 = -32;\n")
        T("    U64 = 64;\n")
        T("    S64 = -64;\n")
        T("    R32 = 1.00000000000000000000000E+00;\n")
        T("    R64 = 1.0000000000000000000000000000000000000000000000000000E+00;\n")
        T("    DT1 = \"20101225123011.123456-360\";\n")
        T("    DT2 = \"12345678151617.123456:000\";\n")
        T("    S = \"Hello World!\";\n")
        T("    C16 = 'A';\n")
        T("    BA = {True, False, True};\n")
        T("    U8A = {0, 255};\n")
        T("    S8A = {-128, 127};\n")
        T("    U16A = {0, 65535};\n")
        T("    S16A = {-32768, 32767};\n")
        T("    U32A = {0, 4294967295};\n")
        T("    S32A = {-2147483648, 2147483647};\n")
        T("    U64A = {0, 18446744073709551615};\n")
        T("    S64A = {-9223372036854775808, 9223372036854775807};\n")
        T("    R32A = {0.00000000000000000000000E+00};\n")
        T("    R64A = {0.0000000000000000000000000000000000000000000000000000E+00};\n")
        T("    DTA = {\"20101225123011.123456-360\"};\n")
        T("    SA = {\"RED\", \"GREEN\", \"BLUE\"};\n")
        T("    C16A = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct Class2:
    Class2 inst;
    CHECK(_ConstructInstance(&inst.__instance, T("Class2")));

    // Class2.Key:
    inst.Key.exists = MI_TRUE;
    inst.Key.value = 12345;

    // Class2.B:
    inst.B.exists = MI_TRUE;
    inst.B.value = MI_TRUE;

    // Class2.U8:
    inst.U8.exists = MI_TRUE;
    inst.U8.value = 8;

    // Class2.S8:
    inst.S8.exists = MI_TRUE;
    inst.S8.value = -8;

    // Class2.U16:
    inst.U16.exists = MI_TRUE;
    inst.U16.value = 16;

    // Class2.S16:
    inst.S16.exists = MI_TRUE;
    inst.S16.value = -16;

    // Class2.U32:
    inst.U32.exists = MI_TRUE;
    inst.U32.value = 32;

    // Class2.S32:
    inst.S32.exists = MI_TRUE;
    inst.S32.value = -32;

    // Class2.U64:
    inst.U64.exists = MI_TRUE;
    inst.U64.value = 64;

    // Class2.S64:
    inst.S64.exists = MI_TRUE;
    inst.S64.value = -64;

    // Class2.R32:
    inst.R32.exists = MI_TRUE;
    inst.R32.value = 1.0;

    // Class2.R64:
    inst.R64.exists = MI_TRUE;
    inst.R64.value = 1.0;

    // Class2.DT1:
    MI_Datetime dt1;
    dt1.isTimestamp = MI_TRUE;
    dt1.u.timestamp.year = 2010;
    dt1.u.timestamp.month = 12;
    dt1.u.timestamp.day = 25;
    dt1.u.timestamp.hour = 12;
    dt1.u.timestamp.minute = 30;
    dt1.u.timestamp.second = 11;
    dt1.u.timestamp.microseconds = 123456;
    dt1.u.timestamp.utc = -360;
    inst.DT1.exists = MI_TRUE;
    inst.DT1.value = dt1;

    // Class2.DT2:
    MI_Datetime dt2;
    dt2.isTimestamp = MI_FALSE;
    dt2.u.interval.days = 12345678;
    dt2.u.interval.hours = 15;
    dt2.u.interval.minutes = 16;
    dt2.u.interval.seconds = 17;
    dt2.u.interval.microseconds = 123456;
    inst.DT2.exists = MI_TRUE;
    inst.DT2.value = dt2;

    // Class2.S:
    inst.S.exists = MI_TRUE;
    inst.S.value = T("Hello World!");

    // Class2.C16:
    inst.C16.exists = MI_TRUE;
    inst.C16.value = 'A';

    // Class2.BA:
    {
        static MI_Boolean data[] = { MI_TRUE, MI_FALSE, MI_TRUE };
        inst.BA.exists = MI_TRUE;
        inst.BA.value.data = data;
        inst.BA.value.size = MI_COUNT(data);
    }

    // Class2.U8A:
    {
        static MI_Uint8 data[] = { 0, 255 };
        inst.U8A.exists = MI_TRUE;
        inst.U8A.value.data = data;
        inst.U8A.value.size = MI_COUNT(data);
    }

    // Class2.S8A:
    {
        static MI_Sint8 data[] = { -128, 127 };
        inst.S8A.exists = MI_TRUE;
        inst.S8A.value.data = data;
        inst.S8A.value.size = MI_COUNT(data);
    }

    // Class2.U16A:
    {
        static MI_Uint16 data[] = { 0, 65535 };
        inst.U16A.exists = MI_TRUE;
        inst.U16A.value.data = data;
        inst.U16A.value.size = MI_COUNT(data);
    }

    // Class2.S16A:
    {
        static MI_Sint16 data[] = { -32768, 32767 };
        inst.S16A.exists = MI_TRUE;
        inst.S16A.value.data = data;
        inst.S16A.value.size = MI_COUNT(data);
    }

    // Class2.U32A:
    {
        static MI_Uint32 data[] = { 0, 4294967295UL };
        inst.U32A.exists = MI_TRUE;
        inst.U32A.value.data = data;
        inst.U32A.value.size = MI_COUNT(data);
    }

    // Class2.S32A:
    {
        static MI_Sint32 data[] = { -2147483647-1, 2147483647 };
        inst.S32A.exists = MI_TRUE;
        inst.S32A.value.data = data;
        inst.S32A.value.size = MI_COUNT(data);
    }

    // Class2.U64A:
    {
        static MI_Uint64 data[] = { 0, 18446744073709551615ULL };
        inst.U64A.exists = MI_TRUE;
        inst.U64A.value.data = data;
        inst.U64A.value.size = MI_COUNT(data);
    }

    // Class2.S64A:
    {
        static MI_Sint64 data[] = 
        { 
            -9223372036854775807LL-1LL, 
            9223372036854775807LL 
        };
        inst.S64A.exists = MI_TRUE;
        inst.S64A.value.data = data;
        inst.S64A.value.size = MI_COUNT(data);
    }

    // Class2.R32A:
    {
        static MI_Real32 data[] = { 0 };
        inst.R32A.exists = MI_TRUE;
        inst.R32A.value.data = data;
        inst.R32A.value.size = MI_COUNT(data);
    }

    // Class2.R64A:
    {
        static MI_Real64 data[] = { 0 };
        inst.R64A.exists = MI_TRUE;
        inst.R64A.value.data = data;
        inst.R64A.value.size = MI_COUNT(data);
    }

    // Class2.DTA:
    {
        static MI_Datetime data[] = { dt1 };
        inst.DTA.exists = MI_TRUE;
        inst.DTA.value.data = data;
        inst.DTA.value.size = MI_COUNT(data);
    }

    // Class2.SA
    {
        static MI_Char* data[] = { (MI_Char*)T("RED"), (MI_Char*)T("GREEN"), (MI_Char*)T("BLUE") };
        MI_Uint32 size = MI_COUNT(data);
        inst.SA.exists = MI_TRUE;
        inst.SA.value.data = data;
        inst.SA.value.size = size;
    }

    // Class2.C16A:
    {
        static MI_Char16 data[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
        MI_Uint32 size = MI_COUNT(data);
        inst.C16A.exists = MI_TRUE;
        inst.C16A.value.data = data;
        inst.C16A.value.size = size;
    }

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(inst, 0, data));
    data.push_back('\0');

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeClass1Schema()
//
//=============================================================================

NitsTest(TestSerializeClass1Schema)
{
    MI_Class clss;
    const MI_Char expect[] =
        T("[TERMINAL, Association, Color(\"PINK\"), Flag(False)]\n")
        T("class Assoc1 : Assoc0\n")
        T("{\n")
        T("    [KEY]\n")
        T("    Widget REF Left;\n")
        T("    Boolean B = True;\n")
        T("    [Values{\"PINK\", \"CYAN\", \"MAGENTA\"}, ValueMap{\"1\", \"2\", \"3\"}]\n")
        T("    Uint8 U8 = 8;\n")
        T("    [Colors{\"RED\", \"GREEN\", \"BLUE\"}]\n")
        T("    Sint8 S8 = -8;\n")
        T("    Uint16 U16 = 16;\n")
        T("    Sint16 S16 = -16;\n")
        T("    Uint32 U32 = 32;\n")
        T("    Sint32 S32 = -32;\n")
        T("    Uint64 U64 = 64;\n")
        T("    Sint64 S64 = -64;\n")
        T("    Real32 R32 = 0.00000000000000000000000E+00;\n")
        T("    Real64 R64 = 0.0000000000000000000000000000000000000000000000000000E+00;\n")
        T("    Datetime DT1 = \"20101225123011.123456-360\";\n")
        T("    Datetime DT2 = \"12345678151617.123456:000\";\n")
        T("    String S = \"My String\";\n")
        T("    Char16 C16 = 'A';\n")
        T("    Boolean BA[] = {True, False};\n")
        T("    Uint8 U8A[] = {8};\n")
        T("    Sint8 S8A[] = {-8, 0, 8};\n")
        T("    Uint16 U16A[] = {16};\n")
        T("    Sint16 S16A[] = {-16, 0, 16};\n")
        T("    Uint32 U32A[] = {32};\n")
        T("    Sint32 S32A[] = {-32, 0, 32};\n")
        T("    Uint64 U64A[] = {64};\n")
        T("    Sint64 S64A[] = {-64, 0, 64};\n")
        T("    Real32 R32A[] = {0.00000000000000000000000E+00};\n")
        T("    Real64 R64A[] = {0.0000000000000000000000000000000000000000000000000000E+00};\n")
        T("    Datetime DTA[] = {\"20101225123011.123456-360\", \"12345678151617.123456:000\"};\n")
        T("    String SA[] = {\"One\", \"Two\"};\n")
        T("    Char16 C16A[] = {'A', 'B', 'C'};\n")
        T("    [STATIC, Description(\"Fool\"), Color(\"Blue\")]\n")
        T("    Uint32 Foo(\n")
        T("        [IN]\n")
        T("        Real32 X,\n")
        T("        [IN]\n")
        T("        Real32 Y,\n")
        T("        [IN(False), OUT]\n")
        T("        Real32 Z);\n")
        T("    [Description(\"Foo2\")]\n")
        T("    String Foo2(\n")
        T("        [IN]\n")
        T("        Widget REF WidIn,\n")
        T("        [IN]\n")
        T("        Gadget REF GadIn,\n")
        T("        [IN]\n")
        T("        Boolean BIn,\n")
        T("        [IN]\n")
        T("        Uint8 U8In,\n")
        T("        [IN]\n")
        T("        Sint8 S8In,\n")
        T("        [IN]\n")
        T("        Uint16 U16In,\n")
        T("        [IN]\n")
        T("        Sint16 S16In,\n")
        T("        [IN]\n")
        T("        Uint32 U32In,\n")
        T("        [IN]\n")
        T("        Sint32 S32In,\n")
        T("        [IN]\n")
        T("        Uint64 U64In,\n")
        T("        [IN]\n")
        T("        Sint64 S64In,\n")
        T("        [IN]\n")
        T("        Real32 R32In,\n")
        T("        [IN]\n")
        T("        Real64 R64In,\n")
        T("        [IN]\n")
        T("        Datetime DT1In,\n")
        T("        [IN]\n")
        T("        Datetime DT2In,\n")
        T("        [IN]\n")
        T("        String SIn,\n")
        T("        [IN]\n")
        T("        Char16 C16In,\n")
        T("        [IN]\n")
        T("        Boolean BAIn[],\n")
        T("        [IN]\n")
        T("        Uint8 U8AIn[],\n")
        T("        [IN]\n")
        T("        Sint8 S8AIn[],\n")
        T("        [IN]\n")
        T("        Uint16 U16AIn[],\n")
        T("        [IN]\n")
        T("        Sint16 S16AIn[],\n")
        T("        [IN]\n")
        T("        Uint32 U32AIn[],\n")
        T("        [IN]\n")
        T("        Sint32 S32AIn[],\n")
        T("        [IN]\n")
        T("        Uint64 U64AIn[],\n")
        T("        [IN]\n")
        T("        Sint64 S64AIn[],\n")
        T("        [IN]\n")
        T("        Real32 R32AIn[],\n")
        T("        [IN]\n")
        T("        Real64 R64AIn[],\n")
        T("        [IN]\n")
        T("        Datetime DTAIn[],\n")
        T("        [IN]\n")
        T("        String SAIn[],\n")
        T("        [IN]\n")
        T("        Char16 C16AIn[],\n")
        T("        [IN(False), OUT]\n")
        T("        Widget REF WidOut,\n")
        T("        [IN(False), OUT]\n")
        T("        Gadget REF GadOut,\n")
        T("        [IN(False), OUT]\n")
        T("        Boolean BOut,\n")
        T("        [IN(False), OUT]\n")
        T("        Uint8 U8Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Sint8 S8Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Uint16 U16Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Sint16 S16Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Uint32 U32Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Sint32 S32Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Uint64 U64Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Sint64 S64Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Real32 R32Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Real64 R64Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Datetime DT1Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Datetime DT2Out,\n")
        T("        [IN(False), OUT]\n")
        T("        String SOut,\n")
        T("        [IN(False), OUT]\n")
        T("        Char16 C16Out,\n")
        T("        [IN(False), OUT]\n")
        T("        Boolean BAOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Uint8 U8AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Sint8 S8AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Uint16 U16AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Sint16 S16AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Uint32 U32AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Sint32 S32AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Uint64 U64AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Sint64 S64AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Real32 R32AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Real64 R64AOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Datetime DTAOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        String SAOut[],\n")
        T("        [IN(False), OUT]\n")
        T("        Char16 C16AOut[],\n")
        T("        [IN, OUT]\n")
        T("        Widget REF WidInOut,\n")
        T("        [IN, OUT]\n")
        T("        Gadget REF GadInOut,\n")
        T("        [IN, OUT]\n")
        T("        Boolean BInOut,\n")
        T("        [IN, OUT]\n")
        T("        Uint8 U8InOut,\n")
        T("        [IN, OUT]\n")
        T("        Sint8 S8InOut,\n")
        T("        [IN, OUT]\n")
        T("        Uint16 U16InOut,\n")
        T("        [IN, OUT]\n")
        T("        Sint16 S16InOut,\n")
        T("        [IN, OUT]\n")
        T("        Uint32 U32InOut,\n")
        T("        [IN, OUT]\n")
        T("        Sint32 S32InOut,\n")
        T("        [IN, OUT]\n")
        T("        Uint64 U64InOut,\n")
        T("        [IN, OUT]\n")
        T("        Sint64 S64InOut,\n")
        T("        [IN, OUT]\n")
        T("        Real32 R32InOut,\n")
        T("        [IN, OUT]\n")
        T("        Real64 R64InOut,\n")
        T("        [IN, OUT]\n")
        T("        Datetime DT1InOut,\n")
        T("        [IN, OUT]\n")
        T("        Datetime DT2InOut,\n")
        T("        [IN, OUT]\n")
        T("        String SInOut,\n")
        T("        [IN, OUT]\n")
        T("        Char16 C16InOut,\n")
        T("        [IN, OUT]\n")
        T("        Boolean BAInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Uint8 U8AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Sint8 S8AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Uint16 U16AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Sint16 S16AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Uint32 U32AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Sint32 S32AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Uint64 U64AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Sint64 S64AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Real32 R32AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Real64 R64AInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Datetime DTAInOut[],\n")
        T("        [IN, OUT]\n")
        T("        String SAInOut[],\n")
        T("        [IN, OUT]\n")
        T("        Char16 C16AInOut[]);\n")
        T("};\n")
        T("\n");

    // Create the class.
    CHECK(_ConstructClass(&clss, T("Assoc1")));

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Serialize the class:
    vector<MI_Char> data;
    CHECK(ser.SerializeClass(&clss, 0, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeContainerSchema()
//
//=============================================================================

NitsTest(TestSerializeContainerSchema)
{
    MI_Class clss;
    const MI_Char expect[] =
        T("class Container\n")
        T("{\n")
        T("    [KEY]\n")
        T("    Uint32 Key;\n")
        T("    [EmbeddedInstance(\"Widget\")]\n")
        T("    String Wid;\n")
        T("    [EmbeddedInstance(\"Gadget\")]\n")
        T("    String Gad;\n")
        T("    Uint32 Foo1();\n")
        T("    Uint32 Foo2(\n")
        T("        [IN, EmbeddedInstance(\"Widget\")]\n")
        T("        String Wid,\n")
        T("        [IN(False), OUT, EmbeddedInstance(\"Gadget\")]\n")
        T("        String Gad);\n")
        T("};\n")
        T("\n");

    // Create the class.
    CHECK(_ConstructClass(&clss, T("Container")));

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Serialize the class:
    vector<MI_Char> data;
    CHECK(ser.SerializeClass(&clss, 0, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeSubClassSchema()
//
//=============================================================================

NitsTest(TestSerializeSubClassSchema)
{
    MI_Class clss;
    const MI_Char expect[] =
        T("[ABSTRACT]\n")
        T("class SuperClass\n")
        T("{\n")
        T("    [KEY]\n")
        T("    String Key;\n")
        T("};\n")
        T("\n")
        T("[TERMINAL]\n")
        T("class SubClass : SuperClass\n")
        T("{\n")
        T("    [KEY]\n")
        T("    String Key;\n")
        T("    Uint32 Count;\n")
        T("    String Color;\n")
        T("};\n")
        T("\n");

    // Create the class.
    CHECK(_ConstructClass(&clss, T("SubClass")));

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Serialize the class:
    vector<MI_Char> data;
    CHECK(ser.SerializeClass(&clss, MI_SERIALIZER_FLAGS_CLASS_DEEP, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeSubClass()
//
//=============================================================================

NitsTest(TestSerializeSubClass)
{
    const MI_Char expect[] =
        T("[ABSTRACT]\n")
        T("class SuperClass\n")
        T("{\n")
        T("    [KEY]\n")
        T("    String Key;\n")
        T("};\n")
        T("\n")
        T("[TERMINAL]\n")
        T("class SubClass : SuperClass\n")
        T("{\n")
        T("    [KEY]\n")
        T("    String Key;\n")
        T("    Uint32 Count;\n")
        T("    String Color;\n")
        T("};\n")
        T("\n")
        T("instance of SubClass\n")
        T("{\n")
        T("    Key = \"Red\";\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct SubClass:
    SubClass inst;
    CHECK(_ConstructInstance(&inst.__instance, T("SubClass")));

    // SubClass.Key:
    inst.Key.exists = MI_TRUE;
    inst.Key.value = T("Red");

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(
        inst, 
        MI_SERIALIZER_FLAGS_CLASS_DEEP|MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS,
        data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeThing()
//
//=============================================================================

NitsTest(TestSerializeThing)
{
    const MI_Char expect[] =
        T("instance of Embedded as $Alias00000001\n")
        T("{\n")
        T("    Key = 1001;\n")
        T("};\n")
        T("\n")
        T("instance of Thing\n")
        T("{\n")
        T("    Key = 2001;\n")
        T("    Obj = $Alias00000001;\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct Embedded:
    Embedded embedded;
    CHECK(_ConstructInstance(&embedded.__instance, T("Embedded")));

    // Construct Widget:
    Thing thing;
    CHECK(_ConstructInstance(&thing.__instance, T("Thing")));

    // Embedded.Key:
    embedded.Key.exists = MI_TRUE;
    embedded.Key.value = 1001;

    // Thing.Key:
    thing.Key.exists = MI_TRUE;
    thing.Key.value = 2001;

    // Thing.Obj:
    thing.Obj.exists = MI_TRUE;
    thing.Obj.value = &embedded.__instance;

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(thing, 0, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest

//=============================================================================
//
// TestSerializeThingSchema()
//
//=============================================================================

NitsTest(TestSerializeThingSchema)
{
    MI_Class clss;
    const MI_Char expect[] =
        T("class Thing\n")
        T("{\n")
        T("    [KEY]\n")
        T("    Uint32 Key;\n")
        T("    [EmbeddedObject]\n")
        T("    String Obj;\n")
        T("};\n")
        T("\n");

    // Create the class.
    CHECK(_ConstructClass(&clss, T("Thing")));

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Serialize the class:
    vector<MI_Char> data;
    CHECK(ser.SerializeClass(&clss, MI_SERIALIZER_FLAGS_CLASS_DEEP, data));
    data.push_back('\0');

#if 0
    wprintf(L"DATA[%s]\n", &data[0]);
#endif

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest


//=============================================================================
//
// TestSerializeClass2EmptyArray()
//
//=============================================================================

NitsTest(TestSerializeClass2EmptyArray)
{
    const MI_Char expect[] =
        T("instance of Class2\n")
        T("{\n")
        T("    SA = {};\n")
        T("    C16A = {};\n")
        T("};\n")
        T("\n");

    // Construct the serializer:
    Serializer ser;
    CHECK(ser);

    // Construct Class2:
    Class2 inst;
    CHECK(_ConstructInstance(&inst.__instance, T("Class2")));

    // Class2.SA
    {
        inst.SA.exists = MI_TRUE;
        inst.SA.value.data = NULL;
        inst.SA.value.size = 0;
    }

    // Class2.C16A:
    {
        inst.C16A.exists = MI_TRUE;
        inst.C16A.value.data = NULL;
        inst.C16A.value.size = 0;
    }

    // Serialize the instance:
    vector<MI_Char> data;
    CHECK(ser.SerializeInstance(inst, 0, data));
    data.push_back('\0');

    // Check against expected buffer:
    CHECK(_Diff(&data[0], expect));
}
NitsEndTest
