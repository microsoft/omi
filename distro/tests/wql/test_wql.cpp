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
#include <base/instance.h>
#include <base/strings.h>
#include <base/helpers.h>

#define CT(STR) ((char*)STR)

using namespace std;

static void setUp()
{
}

static void cleanup()
{
}

static void Test1()
{
    WQL* wql;

    wql = WQL_Parse(
        CT("SELECT A,B,C FROM X WHERE NOT A > 1 OR B < 1 AND C > 3"), NULL);
    UT_ASSERT(wql);

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

    UT_ASSERT(WQL_Identical(wql, &_wql));
    WQL_Delete(wql);
}

static void Test2()
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
    wql = WQL_Parse(CT("SELECT * FROM CLASS1"), NULL);
    UT_ASSERT(wql);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test3()
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
    wql = WQL_Parse(CT("SELECT Width, Height, Depth FROM Bookcase"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test4()
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
    wql = WQL_Parse(CT("SELECT A,B,C FROM X WHERE (A>10) AND (A<30) OR (B>40)"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test5()
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
    wql = WQL_Parse(CT("SELECT A,B,C FROM X WHERE (A>10) OR (A<30) AND (B>40)"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test6()
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
    wql = WQL_Parse(CT("SELECT Name FROM Animal WHERE Name = \"Fido\""), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test7()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE NAME=\"Fred\""), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test8()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE NAME='Wilma \"F\"'"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test9()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE A > 10"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test10()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE A > 1.0"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test11()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE A = TRUE"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test12()
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
    wql = WQL_Parse(CT("SELECT * FROM X WHERE NOT A = TRUE"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test13()
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
    wql = WQL_Parse(CT("SELECT * from Class1 WHERE A > B"), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

extern "C"
{
    static int _Lookup1(
        const MI_Char* name,
        WQL_Symbol* symbol,
        Batch* batch,
        void* data)
    {
        if (Zcmp(name, CT("A")) == 0)
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = 1;
            return 0;
        }
        else if (Zcmp(name, CT("B")) == 0)
        {
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = CT("B");
            return 0;
        }
        else if (Zcmp(name, CT("C")) == 0)
        {
            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = 1;
            return 0;
        }
        else if (Zcmp(name, CT("D")) == 0)
        {
            symbol->type = WQL_TYPE_REAL;
            symbol->value.real = 1.5;
            return 0;
        }
        else if (Zcmp(name, CT("E")) == 0)
        {
            symbol->type = WQL_TYPE_NULL;
            symbol->value.integer = 0;
            return 0;
        }

        return -1;
    }
}

static void Test14()
{
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A > 1"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A > 0"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A = 1"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A = 0"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A <> 0"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A >= 0"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A <= 1"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A = 1 AND B = \"B\""), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE C = TRUE"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE D >= 1.0"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE E = NULL"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A <> NULL"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 0);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE E <> NULL"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
    {
        WQL* wql = WQL_Parse(CT("SELECT * from X WHERE A = NULL"), NULL);
        UT_ASSERT(wql != NULL);
        UT_ASSERT(WQL_Eval(wql, _Lookup1, NULL) == 1);
        WQL_Delete(wql);
    }
}

static void Test15()
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
    wql = WQL_Parse(CT("select * from x where a = \"one \\\"two\\\" three\""), NULL);
    UT_ASSERT(wql != NULL);
    UT_ASSERT(WQL_Identical(&_wql, wql));
    WQL_Delete(wql);
}

static void Test16()
{
    MI_Result r;
    MI_Instance* inst = NULL;

    /* Create a dynamic instance */
    r = Instance_NewDynamic(&inst, CT("A"), MI_FLAG_CLASS, NULL);
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst != NULL);

    /* Add properties */
    {
        MI_Value v;

        v.boolean = MI_FALSE;
        r = __MI_Instance_AddElement(inst, CT("BooleanS"), &v, MI_BOOLEAN, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.uint8 = 8;
        r = __MI_Instance_AddElement(inst, CT("Uint8S"), &v, MI_UINT8, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.sint8 = -8;
        r = __MI_Instance_AddElement(inst, CT("Sint8S"), &v, MI_SINT8, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.uint16 = 16;
        r = __MI_Instance_AddElement(inst, CT("Uint16S"), &v, MI_UINT16, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.sint16 = -16;
        r = __MI_Instance_AddElement(inst, CT("Sint16S"), &v, MI_SINT16, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.uint32 = 32;
        r = __MI_Instance_AddElement(inst, CT("Uint32S"), &v, MI_UINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.sint32 = -32;
        r = __MI_Instance_AddElement(inst, CT("Sint32S"), &v, MI_SINT32, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.uint64 = 64;
        r = __MI_Instance_AddElement(inst, CT("Uint64S"), &v, MI_UINT64, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.sint64 = -64;
        r = __MI_Instance_AddElement(inst, CT("Sint64S"), &v, MI_SINT64, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.real32 = 32.0;
        r = __MI_Instance_AddElement(inst, CT("Real32S"), &v, MI_REAL32, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.real64 = 64.0;
        r = __MI_Instance_AddElement(inst, CT("Real64S"), &v, MI_REAL64, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.char16 = 16;
        r = __MI_Instance_AddElement(inst, CT("Char16S"), &v, MI_CHAR16, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        int x = StrToDatetime(CT("20101231120000.123456+360"), &v.datetime);
        UT_ASSERT(x == 0);
        r = __MI_Instance_AddElement(inst, CT("DatetimeS"), &v, MI_DATETIME, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.string = CT("STRING");
        r = __MI_Instance_AddElement(inst, CT("StringS"), &v, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        v.string = CT("Begin_%End");
        r = __MI_Instance_AddElement(inst, CT("StringL"), &v, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        r = __MI_Instance_AddElement(
            inst, CT("NullStr"), &v, MI_STRING, MI_FLAG_NULL);
        UT_ASSERT(r == MI_RESULT_OK);

#if 0
        Instance_Print(inst, stdout, 0, MI_TRUE);
#endif
    }

    /* Perform evaluations against this instance */
    {
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Sint8S = -8"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Uint8S = 8"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Sint16S = -16"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Uint16S = 16"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Sint32S = -32"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Uint32S = 32"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Sint64S = -64"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Uint64S = 64"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Real32S = 32.0"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Real64S = 64.0"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A WHERE Real64S = 65.0"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(
                CT("SELECT * from A WHERE StringS = \"STRING\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A "
                "WHERE DatetimeS = \"20101231120000.123456+360\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT("SELECT * from A "
                "WHERE DatetimeS <> \"20101231120000.123456+360\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 1);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE NullStr = NULL"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE DatetimeS <> NULL"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE DatetimeS != NULL"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE NullStr = NullStr"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE NULL = NULL"), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE StringS like \"s_r%\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE StringL like \"%END\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE StringL like \"begin%\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
        {
            WQL* wql = WQL_Parse(CT(
                "SELECT * from A WHERE StringL like \"begin\\_\\%END\""), NULL);
            UT_ASSERT(wql != NULL);
            UT_ASSERT(WQL_Eval(wql, WQL_LookupInstanceProperty, inst) == 0);
            WQL_Delete(wql);
        }
    }

    MI_Instance_Delete(inst);
}

static void Test17()
{
    WQL* wql;
    WQL* clone;

    wql = WQL_Parse(
        CT("SELECT A,B,C FROM X WHERE (A>10) AND (A<30) OR (B>40)"), NULL);
    UT_ASSERT(wql != NULL);

    clone = WQL_Clone(wql, NULL);
    UT_ASSERT(clone != NULL);

    UT_ASSERT(WQL_Identical(wql, clone));

    WQL_Delete(clone);
    WQL_Delete(wql);
}

static void RunTests()
{
    UT_TEST(Test1);
    UT_TEST(Test2);
    UT_TEST(Test3);
    UT_TEST(Test4);
    UT_TEST(Test5);
    UT_TEST(Test6);
    UT_TEST(Test7);
    UT_TEST(Test8);
    UT_TEST(Test9);
    UT_TEST(Test10);
    UT_TEST(Test11);
    UT_TEST(Test12);
    UT_TEST(Test13);
    UT_TEST(Test14);
    UT_TEST(Test15);
    UT_TEST(Test16);
    UT_TEST(Test17);
}

UT_ENTRY_POINT(RunTests);
