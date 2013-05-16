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
#include <cctype>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <map>

using namespace std;
const char* arg0;

typedef pair<string, string> Pair;
typedef vector<Pair> Vector;

void LoadSpecFile(const char* path, Vector& pairs)
{
    // Open input file:
    FILE* is = fopen(path, "r");

    if (!is)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, path);
        exit(1);
    }

    // Read each line:
    char buf[1024];
    unsigned int line = 1;

    for (; fgets(buf, sizeof(buf), is) != NULL; line++)
    {
        char* p;
        vector<string> toks;
        char* str;
        char* tag;

        // Skip leading spaces:
        for (p = buf; isspace(*p); p++)
            ;

        // Skip comments:
        if (p[0] == '#')
            continue;

        // Remove trailing spaces:
        {
            char* end = p + strlen(buf);
            while (end != p && isspace(end[-1]))
                *--end = '\0';
        }

        // Expect string
        {
            str = p;

            while (*p && *p != ',')
                p++;
        }

        // Skip spaces:
        while (isspace(*p))
            p++;

        if (!*p)
        {
            char buf[32];
            sprintf(buf, "TAG%u", line);
            pairs.push_back(Pair(str, buf));
            continue;
        }

        // Expect ':'
        if (*p != ',')
        {
            fprintf(stderr, "%s: syntax error on line %u\n", arg0, line);
            exit(1);
        }

        *p++ = '\0';

        // Skip spaces:
        while (isspace(*p))
            p++;

        // Expect tag
        {
            tag = p;

            if (!isalpha(*p) && *p != '_')
            {
                fprintf(stderr, "%s: syntax error on line %u\n", arg0, line);
                exit(1);
            }

            while (isalnum(*p) || *p == '_')
                p++;
        }

        *p++ = '\0';

        // Skip spaces:
        while (isspace(*p))
            p++;

        if (*p)
        {
            fprintf(stderr, "%s: syntax error on line %u\n", arg0, line);
            exit(1);
        }

        pairs.push_back(Pair(str, tag));
    }
}

static void _GenEnum(FILE* f, const Vector& pairs)
{
    // Generate enumeration:
    {
        fprintf(f, "enum\n");
        fprintf(f, "{\n");

        for (size_t i = 0; i < pairs.size(); i++)
        {
            fprintf(f, "    %s = %u%s\n", pairs[i].second.c_str(), (int)(i + 1), ((i+1) == pairs.size() ? "" : ","));
        }

        fprintf(f, "};\n");
        fprintf(f, "\n");
    }
}

#if 0
static void GenSimpleFunction(const char* fileName, const Vector& pairs)
{
    FILE* f = fopen(fileName, "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName);
        exit(1);
    }


    //_GenEnum(f, pairs);

    /* header */
    fprintf(f, "static int SimpleStr(const char* s, size_t n)\n");
    fprintf(f, "{\n");

    /* generate function body */
    fprintf(f, "n=n;\n   ");
    for (size_t i = 0; i < pairs.size(); i++)
    {
        const string& str = pairs[i].first.c_str();
        const string& tok = pairs[i].second.c_str();

        fprintf(f, " if (strcmp(s, \"%s\") == 0)\n",
               str.c_str());

        fprintf(f, "        ");
        fprintf(f, "return %s;\n", tok.c_str());
        fprintf(f, "    else");
    }

    fprintf(f, "\n        return 0; /* not found */\n");

    /* close the function */
    //fprintf(f, "\n");
    fprintf(f, "}\n\n");


    fclose(f);
}
#endif

#if 0
static void GenHashFunction(const char* fileName, const Vector& pairs)
{
    FILE* f = fopen(fileName, "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName);
        exit(1);
    }

    //_GenEnum(f, pairs);

    // Generate function
    {
        typedef pair<unsigned int, Vector> VPair;
        typedef map<unsigned int, Vector> VMap;
        Map m;

        fprintf(f, "int HashStr(const char* s, size_t n)\n");
        fprintf(f, "{\n");
        fprintf(f, "    unsigned int h = (unsigned int)(n ^ s[0] ^ s[n-1]);\n");
        fprintf(f, "\n");
        fprintf(f, "    switch (h)\n");
        fprintf(f, "    {\n");

        // Conslidate pairs with like hash codes
        for (size_t i = 0; i < pairs.size(); i++)
        {
            const char* s = pairs[i].first.c_str();
            size_t n = pairs[i].first.size();
            unsigned int h = n ^ s[0] ^ s[n-1];

            Map::iterator pos = m.find(h);

            if (pos == m.end())
            {
                Vector v;
                v.push_back(pairs[i]);
                m.insert(VPair(h,v));
            }
            else
            {
                (*pos).second.push_back(pairs[i]);
            }
        }

        // Print cases:
        for (Map::iterator p = m.begin(); p != m.end(); p++)
        {
            const Vector& v = (*p).second;

            fprintf(f, "        case %u:\n", (*p).first);

            for (size_t i = 0; i < v.size(); i++)
            {
                const string& str = v[i].first.c_str();
                const string& tok = v[i].second.c_str();

                fprintf(f, "            ");
                fprintf(f, "if (n == %u && memcmp(s, \"%s\", n) == 0)\n",
                    (int)str.size(), str.c_str());

                fprintf(f, "                ");
                fprintf(f, "return %s;\n", tok.c_str());
            }

            fprintf(f, "            break;\n");
        }

        fprintf(f, "    }\n");
        fprintf(f, "    /* Not found */\n");
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    }
    fclose(f);
}
#endif

static void _GenStringCmp(FILE* f, const Pair& p)
{
    const string& str = p.first.c_str();
    const string& tok = p.second.c_str();

    fprintf(f, "            ");
    fprintf(f, "if (HASHSTR_STRCMP(s, HASHSTR_T(\"%s\")) == 0)\n",
            str.c_str());

    fprintf(f, "                ");
    fprintf(f, "return %s;\n", tok.c_str());
}

typedef multimap<unsigned int, Pair> MMap;
typedef pair<unsigned int, Pair> MPair;

static void _GenSubSwitchForRange(
    FILE* f,
    MMap::const_iterator pos,
    MMap::const_iterator range_end)
{
    // find best character with min. number of collisions
    unsigned int bestIndex = 0;
    unsigned int bestCollision = 0xFFFFFFFF;
    unsigned int n = pos->first;

    for ( unsigned int index = 0; index < n; index++ )
    {
        vector<unsigned int> collisions(256, 0);
        unsigned int currentMax = 0;


        for (MMap::const_iterator it = pos; it != range_end; it++)
        {
            unsigned char c = it->second.first[index];
            collisions[c]++;
            if (collisions[c] > currentMax)
                currentMax = collisions[c];
        }

#if 0
        printf("n is %d, index %d, currentMax %d, best %d\n",
               n, index, currentMax, bestCollision);
#endif

        if (bestCollision > currentMax)
        {
            bestCollision = currentMax;
            bestIndex = index;
        }

        if (1 == bestCollision)
            break;
    }


#if 0
    printf("n is %d, best index %d, best %d\n",
           n, bestIndex, bestCollision);
#endif

    // build a submap based on best index value
    MMap subMap;

    for (MMap::const_iterator it = pos; it != range_end; it++)
    {
        unsigned char c = it->second.first[bestIndex];
        const MMap::value_type mpair((unsigned int)c, it->second);
        subMap.insert(mpair);
    }

    fprintf(f, "        switch (s[%u])\n", bestIndex);
    fprintf(f, "        {\n");

    // process submap
    // generate cases for each length
    MMap::const_iterator posSubMap = subMap.begin();

    while (posSubMap != subMap.end())
    {
        unsigned int n = posSubMap->first;

        MMap::const_iterator range_end = subMap.upper_bound(n);

        fprintf(f, "        case %u:\n", n);

        while (posSubMap != range_end)
        {
            _GenStringCmp(f, posSubMap->second);
            posSubMap++;
        }

        //printf("n is %d, number of items is %d\n", n, distance(posSubMap, range_end));
        fprintf(f, "        break;\n");

        posSubMap = subMap.lower_bound(n+1);
    }

    fprintf(f, "        }\n");
    fprintf(f, "\n");

}

static void GenHashStrHeader(
    const string& fileName,
    const Vector& pairs)
{
    FILE* f = fopen(fileName.c_str(), "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName.c_str());
        exit(1);
    }

    _GenEnum(f, pairs);

    fprintf(f, "#if !defined(HASHSTR_CHAR)\n");
    fprintf(f, "# define HASHSTR_CHAR char\n");
    fprintf(f, "#endif\n\n");

    fprintf(f, "#if !defined(HASHSTR_T)\n");
    fprintf(f, "# define HASHSTR_T(STR) STR\n");
    fprintf(f, "#endif\n\n");

    fprintf(f, "#if !defined(HASHSTR_STRCMP)\n");
    fprintf(f, "# define HASHSTR_STRCMP strcmp\n");
    fprintf(f, "#endif\n\n");

    /* file header */
    fprintf(f, "int HashStr(const HASHSTR_CHAR* s, size_t n);\n");
    fprintf(f, "\n");

    printf("Created %s\n", fileName.c_str());
}

static void GenHashStrFunction(
    const string& fileName,
    const Vector& pairs)
{
    FILE* f = fopen(fileName.c_str(), "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName.c_str());
        exit(1);
    }

    fprintf(f, "#if !defined(HASHSTR_CHAR)\n");
    fprintf(f, "# define HASHSTR_CHAR char\n");
    fprintf(f, "#endif\n\n");

    fprintf(f, "#if !defined(HASHSTR_T)\n");
    fprintf(f, "# define HASHSTR_T(STR) STR\n");
    fprintf(f, "#endif\n\n");

    fprintf(f, "#if !defined(HASHSTR_STRCMP)\n");
    fprintf(f, "# define HASHSTR_STRCMP strcmp\n");
    fprintf(f, "#endif\n\n");

    /* file header */
    fprintf(f, "int HashStr(const HASHSTR_CHAR* s, size_t n)\n");
    fprintf(f, "{\n");
    fprintf(f, "\n");
    fprintf(f, "    switch (n)\n");
    fprintf(f, "    {\n");

    /* create a map based on str len */
    MMap m;

    // Conslidate pairs with like str length
    for (size_t i = 0; i < pairs.size(); i++)
    {
        size_t n = pairs[i].first.size();
        const MMap::value_type mpair((unsigned int)n, pairs[i]);
        m.insert(mpair);
    }

    // generate cases for each length
    MMap::const_iterator pos = m.begin();

    while (pos != m.end())
    {
        unsigned int n = pos->first;

        MMap::const_iterator range_end = m.upper_bound(n);

        fprintf(f, "    case %u:\n", n);

        if (pos != range_end)
        {
            MMap::const_iterator pos2 = pos;
            if (++pos2 == range_end)
            {
                // special case - only a few elements in range
                while (pos != range_end)
                {
                    _GenStringCmp(f, pos->second);
                    pos++;
                }
            }
            else
            {
                _GenSubSwitchForRange(f, pos, range_end);
            }
        }

        //printf("n is %d, number of items is %d\n", n, distance(pos, range_end));
        fprintf(f, "    break;\n");

        pos = m.lower_bound(n+1);
    }


    fprintf(f, "    }\n");
    fprintf(f, "    /* Not found */\n");
    fprintf(f, "    return 0;\n");
    fprintf(f, "}\n");

    fclose(f);

    printf("Created %s\n", fileName.c_str());
}

#if 0
static void GenUnittest(const char* fileName, const Vector& pairs)
{
    FILE* f = fopen(fileName, "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName);
        exit(1);
    }

    /* file header */
    fprintf(f, "#include <ut/ut.h>\n");
    fprintf(f, "#include <string.h>\n");
    fprintf(f, "#include \"../quickstr.h\"\n");
    fprintf(f, "#include \"../quickstr.inc\"\n");
    fprintf(f, "#include \"hash.inc\"\n");
    fprintf(f, "#include \"simple.inc\"\n");

    fprintf(f, "\n");
    fprintf(f, "static void setUp()\n{\n}\n");
    fprintf(f, "static void cleanup()\n{\n}\n");

    fprintf(f, "typedef int (*FN)(const char* s, size_t n);\n");

    fprintf(f, "static void testAllStrings(FN f)\n{\n");

    /* generate all tests */
    for (size_t i = 0; i < pairs.size(); i++)
    {
        const string& str = pairs[i].first.c_str();
        const string& tok = pairs[i].second.c_str();

        fprintf(f, "    UT_ASSERT((*f)(\"%s\", %u) == %s);\n",
                str.c_str(), (int)str.size(), tok.c_str() );
     }

    /* add comparison with not-exisitng strings */
    fprintf(f, "    UT_ASSERT((*f)(\"*\", 1) == 0);\n") ;
    fprintf(f, "    UT_ASSERT((*f)(\"**\", 2) == 0);\n") ;
    fprintf(f, "    UT_ASSERT((*f)(\"***\", 3) == 0);\n") ;
    fprintf(f, "    UT_ASSERT((*f)(\"****\", 4) == 0);\n") ;
    fprintf(f, "    UT_ASSERT((*f)(\"*****\", 5) == 0);\n") ;
    fprintf(f, "    UT_ASSERT((*f)(\"******\", 6) == 0);\n") ;


    /* Generate end of unittest file  */
    fprintf(f, "}\n\n");
    fprintf(f, "static void TestSimple()\n");
    fprintf(f, "{\n");
    fprintf(f, "    for(int i=0; i< 10000; i++) testAllStrings(SimpleStr);\n");
    fprintf(f, "}\n");
    fprintf(f, "\n");

    fprintf(f, "static void TestHash()\n");
    fprintf(f, "{\n");
    fprintf(f, "    for(int i=0; i< 10000; i++) testAllStrings(HashStr);\n");
    fprintf(f, "}\n");
    fprintf(f, "\n");

    fprintf(f, "static void TestHashStr()\n");
    fprintf(f, "{\n");
    fprintf(f, "    for(int i=0; i< 10000; i++) testAllStrings(HashStr);\n");
    fprintf(f, "}\n");
    fprintf(f, "\n");

    fprintf(f, "static void RunTests()\n");
    fprintf(f, "{\n");
    fprintf(f, "    UT_TEST(TestSimple);\n");
    fprintf(f, "    UT_TEST(TestHash);\n");
    fprintf(f, "    UT_TEST(TestHashStr);\n");
    fprintf(f, "}\n");
    fprintf(f, "\n");
    fprintf(f, "UT_ENTRY_POINT(RunTests);\n");


    fclose(f);
}
#endif

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path\n", arg0);
        exit(1);
    }

    Vector pairs;
    LoadSpecFile(argv[1], pairs);

    if (pairs.empty())
    {
        fprintf(stderr, "no data for building hash function\n");
        exit(1);
    }

#if 0
    GenSimpleFunction("simple.inc", pairs);
    GenHashFunction("hash.inc", pairs);
#endif

    // Determine the base filename:
    string base = argv[1];
    {
        size_t pos = base.rfind('/');

        if (pos != string::npos)
            base = base.substr(pos + 1);

        pos = base.rfind('.');

        if (pos != string::npos)
            base = base.substr(0, pos);
    }

    GenHashStrHeader(base + ".h", pairs);
    GenHashStrFunction(base + ".inc", pairs);

#if 0
    GenUnittest("tests/test_strhash.cpp", pairs);
#endif

    return 0;
}
