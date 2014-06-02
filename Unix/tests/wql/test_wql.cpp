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

#include <iostream>
#include <string>
#include <ut/ut.h>
#include <common.h>
#include <wql/wql.h>
#include <wql/like.h>
#include <base/instance.h>
#include <pal/strings.h>
#include <base/helpers.h>
#include <pal/format.h>

#if defined(CONFIG_ENABLE_WCHAR)
# define CT(STR) ((wchar_t*)L##STR)
#else
# define CT(STR) ((char*)STR)
#endif

using namespace std;

static WQL* _Parse(
    const ZChar* text,
    Batch* batch)
{
    return WQL_Parse(text, batch, WQL_DIALECT_WQL);
}

NitsSetup(TestWqlSetup)
NitsEndSetup

NitsCleanup(TestWqlSetup)
NitsEndCleanup

NitsTestWithSetup(Test1, TestWqlSetup)
{
    WQL* wql;

    wql = _Parse(
        CT("SELECT A,B,C FROM X WHERE NOT A > 1 OR B < 1 AND C > 3"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;

    static const WQL _wql =
    {
        /* properties */
        {
            CT("A"),
            CT("B"),
            CT("C"),
        },
        3,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(1) },
            { WQL_TYPE_GT },
            { WQL_TYPE_NOT },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("B")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(1) },
            { WQL_TYPE_LT },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("C")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(3) },
            { WQL_TYPE_GT },
            { WQL_TYPE_AND },
            { WQL_TYPE_OR },
        },
        12,
    };

    TEST_ASSERT(WQL_Identical(wql, &_wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test2, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("CLASS1"),
        /* symbols */
        {
        },
        0,
    };
    wql = _Parse(CT("SELECT * FROM CLASS1"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test3, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
            CT("Width"),
            CT("Height"),
            CT("Depth"),
        },
        3,
        /* className */
        CT("Bookcase"),
        /* symbols */
        {
        },
        0,
    };
    wql = _Parse(CT("SELECT Width, Height, Depth FROM Bookcase"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test4, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
            CT("A"),
            CT("B"),
            CT("C"),
        },
        3,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(10) },
            { WQL_TYPE_GT },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(30) },
            { WQL_TYPE_LT },
            { WQL_TYPE_AND },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("B")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(40) },
            { WQL_TYPE_GT },
            { WQL_TYPE_OR },
        },
        11,
    };
    wql = _Parse(CT("SELECT A,B,C FROM X WHERE (A>10) AND (A<30) OR (B>40)"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test5, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
            CT("A"),
            CT("B"),
            CT("C"),
        },
        3,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(10) },
            { WQL_TYPE_GT },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(30) },
            { WQL_TYPE_LT },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("B")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(40) },
            { WQL_TYPE_GT },
            { WQL_TYPE_AND },
            { WQL_TYPE_OR },
        },
        11,
    };
    wql = _Parse(CT("SELECT A,B,C FROM X WHERE (A>10) OR (A<30) AND (B>40)"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test6, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
            CT("Name"),
        },
        1,
        /* className */
        CT("Animal"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("Name")) },
            { WQL_TYPE_STRING, WQL_VALUE_STRING(CT("Fido")) },
            { WQL_TYPE_EQ },
        },
        3,
    };
    wql = _Parse(CT("SELECT Name FROM Animal WHERE Name = \"Fido\""), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test7, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("NAME")) },
            { WQL_TYPE_STRING, WQL_VALUE_STRING(CT("Fred")) },
            { WQL_TYPE_EQ },
        },
        3,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE NAME=\"Fred\""), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test8, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("NAME")) },
            { WQL_TYPE_STRING, WQL_VALUE_STRING(CT("Wilma \"F\"")) },
            { WQL_TYPE_EQ },
        },
        3,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE NAME='Wilma \"F\"'"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test9, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_INTEGER, WQL_VALUE_INTEGER(10) },
            { WQL_TYPE_GT },
        },
        3,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE A > 10"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test10, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_REAL, WQL_VALUE_REAL(1.000000) },
            { WQL_TYPE_GT },
        },
        3,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE A > 1.0"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test11, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_BOOLEAN, WQL_VALUE_BOOLEAN(1) },
            { WQL_TYPE_EQ },
        },
        3,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE A = TRUE"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test12, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("X"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_BOOLEAN, WQL_VALUE_BOOLEAN(1) },
            { WQL_TYPE_EQ },
            { WQL_TYPE_NOT },
        },
        4,
    };
    wql = _Parse(CT("SELECT * FROM X WHERE NOT A = TRUE"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test13, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("Class1"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("A")) },
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("B")) },
            { WQL_TYPE_GT },
        },
        3,
    };
    wql = _Parse(CT("SELECT * from Class1 WHERE A > B"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

extern "C"
{
    static int _Lookup1(
        const MI_Char* name,
        const MI_Char* embeddedClassName,
        const MI_Char* embeddedPropertyName,
        WQL_Symbol* symbol,
        Batch* batch,
        void* data)
    {
        if (embeddedClassName && !embeddedPropertyName)
        {
            if (Tcscmp(name, CT("X")) != 0)
                return -1;

            if (Tcscmp(embeddedClassName, CT("Y")) != 0)
                return -1;

            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = MI_TRUE;
            return 0;
        }

        if (Tcscmp(name, CT("A")) == 0)
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = 1;
            return 0;
        }
        else if (Tcscmp(name, CT("B")) == 0)
        {
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = CT("B");
            return 0;
        }
        else if (Tcscmp(name, CT("C")) == 0)
        {
            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = 1;
            return 0;
        }
        else if (Tcscmp(name, CT("D")) == 0)
        {
            symbol->type = WQL_TYPE_REAL;
            symbol->value.real = 1.5;
            return 0;
        }
        else if (Tcscmp(name, CT("E")) == 0)
        {
            symbol->type = WQL_TYPE_NULL;
            symbol->value.integer = 0;
            return 0;
        }
        return -1;
    }
}

NitsTestWithSetup(Test14, TestWqlSetup)
{
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A > 1"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A > 0"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A = 1"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A = 0"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A <> 0"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A >= 0"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A <= 1"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A = 1 AND B = \"B\""), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE C = TRUE"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE D >= 1.0"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE E = NULL"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A <> NULL"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE E <> NULL"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE A = NULL"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = _Parse(CT("SELECT * from X WHERE X ISA Y"), NULL);
        if(!TEST_ASSERT(wql != NULL)) NitsReturn;
        TEST_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
}
NitsEndTest

NitsTestWithSetup(Test15, TestWqlSetup)
{
    WQL* wql;
    static const WQL _wql =
    {
        /* properties */
        {
        },
        0,
        /* className */
        CT("x"),
        /* symbols */
        {
            { WQL_TYPE_IDENTIFIER, WQL_VALUE_STRING(CT("a")) },
            { WQL_TYPE_STRING, WQL_VALUE_STRING(CT("one \"two\" three")) },
            { WQL_TYPE_EQ },
        },
        3,
    };
    wql = _Parse(CT("select * from x where a = \"one \\\"two\\\" three\""), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;
    TEST_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(Test16, TestWqlSetup)
{
    MI_Result r;
    MI_Instance* inst = NULL;

    /* Create a dynamic instance */
    r = Instance_NewDynamic(&inst, CT("A"), MI_FLAG_CLASS, NULL);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        NitsReturn;
    TEST_ASSERT(inst != NULL);

    /* Add properties */
    {
        MI_Value v;

        v.boolean = MI_FALSE;
        r = __MI_Instance_AddElement(inst, CT("BooleanS"), &v, MI_BOOLEAN, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.uint8 = 8;
        r = __MI_Instance_AddElement(inst, CT("Uint8S"), &v, MI_UINT8, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.sint8 = -8;
        r = __MI_Instance_AddElement(inst, CT("Sint8S"), &v, MI_SINT8, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.uint16 = 16;
        r = __MI_Instance_AddElement(inst, CT("Uint16S"), &v, MI_UINT16, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.sint16 = -16;
        r = __MI_Instance_AddElement(inst, CT("Sint16S"), &v, MI_SINT16, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.uint32 = 32;
        r = __MI_Instance_AddElement(inst, CT("Uint32S"), &v, MI_UINT32, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.sint32 = -32;
        r = __MI_Instance_AddElement(inst, CT("Sint32S"), &v, MI_SINT32, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.uint64 = 64;
        r = __MI_Instance_AddElement(inst, CT("Uint64S"), &v, MI_UINT64, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.sint64 = -64;
        r = __MI_Instance_AddElement(inst, CT("Sint64S"), &v, MI_SINT64, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.real32 = 32.0;
        r = __MI_Instance_AddElement(inst, CT("Real32S"), &v, MI_REAL32, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.real64 = 64.0;
        r = __MI_Instance_AddElement(inst, CT("Real64S"), &v, MI_REAL64, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.char16 = 16;
        r = __MI_Instance_AddElement(inst, CT("Char16S"), &v, MI_CHAR16, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        int x = StrToDatetime(CT("20101231120000.123456+360"), &v.datetime);
        TEST_ASSERT(x == 0);
        r = __MI_Instance_AddElement(inst, CT("DatetimeS"), &v, MI_DATETIME, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.string = CT("STRING");
        r = __MI_Instance_AddElement(inst, CT("StringS"), &v, MI_STRING, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        v.string = CT("Begin_%End");
        r = __MI_Instance_AddElement(inst, CT("StringL"), &v, MI_STRING, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        r = __MI_Instance_AddElement(
            inst, CT("NullStr"), &v, MI_STRING, MI_FLAG_NULL);
        TEST_ASSERT(r == MI_RESULT_OK);

        /* Add embedded dynamic instance */
        {
            MI_Instance* emb;
            r = Instance_NewDynamic(
                &emb, 
                CT("CIM_StorageVolume"), 
                MI_FLAG_CLASS, 
                NULL);
            if(!TEST_ASSERT(r == MI_RESULT_OK))
                goto cleanup;
            TEST_ASSERT(emb != NULL);

            v.uint32 = 10;
            r = __MI_Instance_AddElement(
                emb,
                CT("Count"), 
                &v, 
                MI_UINT32, 
                0);
            TEST_ASSERT(r == MI_RESULT_OK);

            v.instance = emb;
            r = __MI_Instance_AddElement(
                inst, CT("SourceInstance"), 
                &v, 
                MI_INSTANCE, 
                0);
            TEST_ASSERT(r == MI_RESULT_OK);
        }

#if 0
        Instance_Print(inst, stdout, 0, MI_TRUE, MI_FALSE);
#endif
    }

    /* Perform evaluations against this instance */
    {
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Sint8S = -8"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Uint8S = 8"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Sint16S = -16"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Uint16S = 16"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Sint32S = -32"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Uint32S = 32"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Sint64S = -64"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Uint64S = 64"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Real32S = 32.0"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Real64S = 64.0"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE Real64S = 65.0"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(
                CT("SELECT * from A WHERE StringS = \"STRING\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE DatetimeS = \"20101231120000.123456+360\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT("SELECT * from A WHERE DatetimeS <> \"20101231120000.123456+360\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE NullStr = NULL"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE DatetimeS <> NULL"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE DatetimeS != NULL"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE NullStr = NullStr"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE NULL = NULL"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE StringS LIKE \"s_r%\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE StringL like \"%END\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE StringL like \"begin%\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE StringL like \"begin\\_\\%END\""), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance ISA CIM_StorageVolume"), 
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE NOT SourceInstance ISA CIM_StorageVolume"), 
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance ISA CIM_XYZ"), 
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance.CIM_StorageVolume::Count = 10"),
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance.Count = 10"),
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance.CIM_StorageVolume::Count = 11"),
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance.Count = 11"),
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE SourceInstance.NoSuchClass::Count = 10"),
                NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == -1);
            WQL_Delete(wql);
        }
        {
            /* Note: CQL LIKE is not supported since it would have entirely
             * different patten matching requirements.
             */
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE StringS LIKE \"s_r%\""), NULL,
                WQL_DIALECT_CQL);
            TEST_ASSERT(wql == NULL);
            // This is a negative test case; so ignoring error on OOM
            NitsIgnoringError();
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE Sint8S = -8 AND SourceInstance.CIM_StorageVolume::Count = 10"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Validate(wql, inst->classDecl) == 0);
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = _Parse(CT(
                "SELECT * from A WHERE Sint8S = 0 AND SourceInstance.CIM_StorageVolume::Count = 0"), NULL);
            if(!TEST_ASSERT(wql != NULL)) NitsReturn;
            TEST_ASSERT(WQL_Validate(wql, inst->classDecl) == 0);
            TEST_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
    }

cleanup:

    MI_Instance_Delete(inst);
}
NitsEndTest

NitsTestWithSetup(Test17, TestWqlSetup)
{
    WQL* wql;
    WQL* clone;

    wql = _Parse(
        CT("SELECT A,B,C FROM X WHERE (A>10) AND (A<30) OR (B>40)"), NULL);
    if(!TEST_ASSERT(wql != NULL)) NitsReturn;

    clone = WQL_Clone(wql, NULL);
    if(!TEST_ASSERT(clone != NULL)) NitsReturn;        

    TEST_ASSERT(WQL_Identical(wql, clone));

    WQL_Delete(clone);
    WQL_Delete(wql);
}
NitsEndTest

NitsTestWithSetup(TestLike, TestWqlSetup)
{
    TEST_ASSERT(WQL_MatchLike(CT(""), CT(""), '\0'));
    // There are bunch of negative cases which should return false
    // with or without OOM; so ignorign there errors
    // TODO: The WQL_MatchLike should have some error code propagation mechanism different than return value since return value indicates whether it matched or not
    TEST_ASSERT(!WQL_MatchLike(CT(""), CT("x"), '\0')); 
    TEST_ASSERT(!WQL_MatchLike(CT(""), CT("xxxx"), '\0'));

    TEST_ASSERT(WQL_MatchLike(CT("_"), CT("Y"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_"), CT("xxxxxxxxxx"), '\0'));

    TEST_ASSERT(WQL_MatchLike(CT("_%_%_%%%%"), CT("abc"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("_%_%_%%%%"), CT("xyz"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("_%_%_%%%%"), CT("xyzp"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("_%_%_%%%%"), CT("___"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("_%_%_%%%%"), CT("xxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_%_%_%%%%"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_%_%_%%%%"), CT("x"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_%_%_%%%%"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_%_%_%%%%"), CT("%"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("_%_%_%%%%"), CT("ab"), '\0'));

    TEST_ASSERT(WQL_MatchLike(CT("%"), CT(""), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%"), CT("x"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%"), CT("xx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("x"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("x"), CT("y"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("x"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("x"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("x"), CT("x"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("[xy]"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[xy]"), CT("z"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[xy]"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[xy]"), CT("xy"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[xy]"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[xy]"), CT("x"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[xy]"), CT("y"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT("xy"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT("x"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^xy]"), CT("y"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^xy]"), CT("z"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^xy]"), CT("w"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("[c-e]"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[c-e]"), CT("b"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[c-e]"), CT("f"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[c-e]"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[c-e]"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[c-e]"), CT("c"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[c-e]"), CT("d"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[c-e]"), CT("e"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT("xx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT("c"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT("d"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("[^c-e]"), CT("e"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^c-e]"), CT("b"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^c-e]"), CT("f"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^c-e]"), CT("B"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("[^c-e]"), CT("F"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("f"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("fo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("o"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("oo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("xfoo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("xfoox"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("foo%"), CT("foo"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("foo%"), CT("foox"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("f"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("fo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("o"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("oo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("foox"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("xfoox"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo"), CT("foo"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo"), CT("xfoo"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("f"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("fo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("o"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("oo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("ooo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("xoox"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("xfox"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("%foo%"), CT("xxxxxxxxxxxxxxxxxxxxxx"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo%"), CT("foo"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo%"), CT("xfoo"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo%"), CT("foox"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("%foo%"), CT("xfoox"), '\0'));

    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT(""), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("f"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("o"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("b"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("a"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("t"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("foo"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("bat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("fooba"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("oobat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("fooat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("fobat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("xfoobat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("foobatx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("xfooxbat"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("xfooxbatx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("fooxbatx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("xfooxbatx"), '\0'));
    TEST_ASSERT(!WQL_MatchLike(CT("foo%bat"), CT("xxxxxxxxxxxxxxxxxxxxxx"),'\0'));
    TEST_ASSERT(WQL_MatchLike(CT("foo%bat"), CT("foobat"), '\0'));
    TEST_ASSERT(WQL_MatchLike(CT("foo%bat"), CT("fooxbat"), '\0'));

    {
        const ZChar* PAT = CT("%%%%%%%%%%%%foo%%%%%%%%%%bat%%%%%%%%%%%%%%%%%%");
        TEST_ASSERT(!WQL_MatchLike(PAT, CT(""), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("f"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("o"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("b"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("a"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("t"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("foo"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("bat"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("fooba"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("oobat"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("fooat"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("fobat"), '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, CT("xxxxxxx"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("xfoobat"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("foobatx"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("xfooxbat"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("xfoobatx"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("fooxbatx"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("xfooxbatx"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("foobat"), '\0'));
        TEST_ASSERT(WQL_MatchLike(PAT, CT("fooxbat"), '\0'));
    }

    {
        const ZChar PAT[] = 
            MI_T("a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a")
            MI_T("%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%b");
        TEST_ASSERT(!WQL_MatchLike(PAT, 
            CT("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), 
            '\0'));
        TEST_ASSERT(!WQL_MatchLike(PAT, 
            CT("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaba"), 
            '\0'));
    }

    {
        const ZChar* PAT =
            MI_T("a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a")
            MI_T("%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a%a");
        TEST_ASSERT(WQL_MatchLike(PAT, 
            CT("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            '\0'));
    }

    // This is to take care of all negative cases 
    // which should fail anyways as mentioned above
    NitsIgnoringError();
}
NitsEndTest



