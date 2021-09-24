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

struct Tuple
{
    Tuple(char ch_, const string& str_, const string& tag_) :
        ch(ch_), str(str_), tag(tag_)
    {
    }

    char ch;
    string str;
    string tag;
};

typedef vector<Tuple> Vector;

string BaseName(const string& name)
{
    string base = name;

    size_t pos = base.rfind('/');

    if (pos != string::npos)
        base = base.substr(pos + 1);

    pos = base.rfind('.');

    if (pos != string::npos)
        base = base.substr(0, pos);

    return base;
}

void LoadSpecFile(const char* path, Vector& tuples)
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
        char ch;

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

        // Ignore empty lines:

        if (*p == '\0')
            continue;

        // Get tag:
        {
            ch = *p++;

            if (!isalpha(ch) && ch != '0')
            {
                fprintf(stderr, "%s: expected character identifier: %u\n", arg0, line);
                exit(1);
            }

            while (*p && *p != ',')
                p++;

            // Skip spaces:
            while (isspace(*p))
                p++;

            // Expect ','
            if (*p != ',')
            {
                fprintf(stderr, "%s: expected comma and then string: %u\n", arg0, line);
                exit(1);
            }

            p++;
        }

        // Skip spaces:
        while (isspace(*p))
            p++;

        // Get string:
        {
            str = p;

            while (*p && *p != ',')
                p++;

            // Skip spaces:
            while (isspace(*p))
                p++;

            // Expect ','
            if (*p != ',')
            {
                fprintf(stderr, "%s: expected comman and then tag name: %u\n", arg0, line);
                exit(1);
            }

            *p++ = '\0';
        }

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

        tuples.push_back(Tuple(ch, str, tag));
    }
}

static void _GenEnum(FILE* f, const Vector& tuples)
{
    // Generate enumeration:
    {
        fprintf(f, "enum\n");
        fprintf(f, "{\n");

        for (size_t i = 0; i < tuples.size(); i++)
        {
            fprintf(f, "    %s = %u%s\n", 
                tuples[i].tag.c_str(), 
                (int)(i + 1), 
                ((i+1) == tuples.size() ? "" : ","));
        }

        fprintf(f, "};\n");
        fprintf(f, "\n");
    }
}

typedef multimap<unsigned int, Tuple> Map;
typedef pair<unsigned int, Tuple> MTuple;
static void _GenStringCmp(FILE* f, const Tuple& p)
{
    char ch = p.ch;
    const string& str = p.str.c_str();
    const string& tok = p.tag.c_str();
    
    fprintf(f, "            ");

    if (ch == '0')
    {
        fprintf(f, "if (HASHSTR_STRCMP(s, HASHSTR_T(\"%s\")) == 0)\n",
            str.c_str());
    }
    else
    {
        fprintf(f, "if (c == '%c' && HASHSTR_STRCMP(s, HASHSTR_T(\"%s\")) == 0)\n",
            ch, str.c_str());
    }
    
    fprintf(f, "                ");
    fprintf(f, "return %s;\n", tok.c_str());
}


static void _GenSubSwitchForRange(
    FILE* f, 
    Map::const_iterator pos, 
    Map::const_iterator range_end)
{
    // find best character with min. number of collisions
    unsigned int bestIndex = 0;
    unsigned int bestCollision = 0xFFFFFFFF;
    unsigned int n = pos->first;

    for ( unsigned int index = 0; index < n; index++ )
    {
        vector<unsigned int> collisions(256, 0);
        unsigned int currentMax = 0;


        for ( Map::const_iterator it = pos; it != range_end; it++ )
        {
            unsigned char c = it->second.str[index];
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
    Map subMap;

    for ( Map::const_iterator it = pos; it != range_end; it++ )
    {
        unsigned char c = it->second.str[bestIndex];

        subMap.insert(MTuple(c, it->second));
    }

    fprintf(f, "        switch (s[%u])\n", bestIndex);
    fprintf(f, "        {\n");

    // process submap
    // generate cases for each length
    Map::const_iterator posSubMap = subMap.begin();

    while (posSubMap != subMap.end())
    {
        unsigned int n = posSubMap->first;

        Map::const_iterator range_end = subMap.upper_bound(n);

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

static void GenDoNotEditMessage(
    FILE* f)
{
    fprintf(f, "/*\n");
    fprintf(f, "**==============================================================================\n");
    fprintf(f, "**\n");
    fprintf(f, "** DO NOT EDIT THIS FILE!!! IT WAS AUTOMATICALLY GENERATED\n");
    fprintf(f, "**\n");
    fprintf(f, "**==============================================================================\n");
    fprintf(f, "*/\n");
    fprintf(f, "\n");
}

static void GenHashStrHeader(
    const string& fileName,
    const Vector& tuples)
{
    FILE* f = fopen(fileName.c_str(), "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName.c_str());
        exit(1);
    }

    GenDoNotEditMessage(f);

    string base = BaseName(fileName);

    fprintf(f, "#ifndef _%s_h\n", base.c_str());
    fprintf(f, "#define _%s_h\n", base.c_str());
    fprintf(f, "\n");

    _GenEnum(f, tuples);

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
    fprintf(f, "int HashStr(HASHSTR_CHAR c, const HASHSTR_CHAR* s, size_t n);\n");
    fprintf(f, "\n");

    fprintf(f, "#endif /* %s_h */\n", base.c_str());

    printf("Created %s\n", fileName.c_str());
}

static void GenFastHashStrFunction(
    const string& fileName, 
    const string& base,
    const Vector& tuples)
{
    FILE* f = fopen(fileName.c_str(), "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName.c_str());
        exit(1);
    }

    GenDoNotEditMessage(f);

    fprintf(f, "#include \"%s.h\"\n", base.c_str());
    fprintf(f, "\n");

    /* file header */
    fprintf(f, "int HashStr(HASHSTR_CHAR c, const HASHSTR_CHAR* s, size_t n)\n");
    fprintf(f, "{\n");
    fprintf(f, "\n");
    fprintf(f, "    switch (n)\n");
    fprintf(f, "    {\n");
    /* create a map based on str len */

    Map m;

    // Consolidate tuples with like str length
    for (size_t i = 0; i < tuples.size(); i++)
    {
        size_t n = tuples[i].str.size();

        m.insert(MTuple(n, tuples[i]));   
    }

    // generate cases for each length
    Map::const_iterator pos = m.begin();

    while (pos != m.end())
    {
        unsigned int n = pos->first;

        Map::const_iterator range_end = m.upper_bound(n);

        fprintf(f, "    case %u:\n", n);

        if (1 >= distance(pos, range_end))
        {
            // special case - only few elements in range
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

static void GenSmallHashStrFunction(
    const string& fileName, 
    const string& base,
    const Vector& tuples)
{
    FILE* f = fopen(fileName.c_str(), "w");

    if (!f)
    {
        fprintf(stderr, "%s: failed to open: %s\n", arg0, fileName.c_str());
        exit(1);
    }

    GenDoNotEditMessage(f);

    fprintf(f, "#include \"%s.h\"\n", base.c_str());
    fprintf(f, "\n");

    Map m;

    // Consolidate tuples with like hash code:
    for (size_t i = 0; i < tuples.size(); i++)
    {
        const string& s = tuples[i].str;

        size_t n = tuples[i].str.size();

        unsigned char h = (unsigned char)s[0] ^ (unsigned char)s[n-1] ^ (unsigned char)n;

        m.insert(MTuple(h, tuples[i]));   
    }

    // generate cases for each length
    Map::const_iterator pos = m.begin();

    fprintf(f, "typedef struct _HashStrTuple\n");
    fprintf(f, "{\n");
    fprintf(f, "    unsigned char code;\n");
    fprintf(f, "    char ch;\n");
    fprintf(f, "    unsigned short tag;\n");
    fprintf(f, "    const HASHSTR_CHAR* str;\n");
    fprintf(f, "}\n");
    fprintf(f, "HashStrTuple;\n");
    fprintf(f, "\n");

    fprintf(f, "static const HashStrTuple _tuples[] =\n");
    fprintf(f, "{\n");

    while (pos != m.end())
    {
        unsigned int h = pos->first;
        const Tuple& t = pos->second;

        // Lookup tag id:

        size_t tag = size_t(-1);

        for (size_t i = 0; i < tuples.size(); i++)
        {
            if (tuples[i].tag == t.tag)
            {
                tag = i + 1;
            }
        }

        if (tag == size_t(-1))
        {
            fprintf(stderr, "%s: tag not found: %s\n", arg0, t.tag.c_str());
            exit(1);
        }

        fprintf(f, "    {\n");
        fprintf(f, "        0x%02X, /* code */\n", h);

        if (t.ch == '0')
            fprintf(f, "        0, /* ch */\n");
        else
            fprintf(f, "        '%c', /* ch */\n", t.ch);

        fprintf(f, "        %s,\n", t.tag.c_str());
        fprintf(f, "        HASHSTR_T(\"%s\")\n", t.str.c_str());
        fprintf(f, "    },\n");

        pos++;
    }

    fprintf(f, "    {\n");
    fprintf(f, "        0xFF, /* code */\n");
    fprintf(f, "    }\n");

    fprintf(f, "};\n");
    fprintf(f, "\n");
    fprintf(f, "static const size_t _ntuples = sizeof(_tuples) / sizeof(_tuples[0]) - 1;\n");
    fprintf(f, "\n");

    /* file header */
    fprintf(f, "int HashStr(HASHSTR_CHAR c, const HASHSTR_CHAR* s, size_t n)\n");
    fprintf(f, "{\n");
    fprintf(f, "\n");
    fprintf(f, "    size_t i;\n");
    fprintf(f, "    size_t j;\n");
    fprintf(f, "    unsigned char h = (unsigned char)s[0] ^ (unsigned char)s[n-1] ^ (unsigned char)n;\n");
    fprintf(f, "\n");

    fprintf(f, "    for (i = 0; h > _tuples[i].code; i++)\n");
    fprintf(f, "        ;\n");
    fprintf(f, "\n");
    fprintf(f, "    for (j = i; j < _ntuples && h == _tuples[j].code; j++)\n");
    fprintf(f, "    {\n");
    fprintf(f, "        if (c == _tuples[j].ch && HASHSTR_STRCMP(s, _tuples[j].str) == 0)\n");
    fprintf(f, "            return _tuples[j].tag;\n");
    fprintf(f, "    }\n");

    fprintf(f, "\n");

    // ATTN:

    fprintf(f, "    /* Not found */\n");
    fprintf(f, "    return 0;\n");
    fprintf(f, "}\n");

    fclose(f);

    printf("Created %s\n", fileName.c_str());
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path\n", arg0);
        exit(1);
    }

    Vector tuples;
    LoadSpecFile(argv[1], tuples);

#if 0
    for (size_t i = 0; i < tuples.size(); i++)
    {
        const Tuple& t = tuples[i];
        printf("{%c}{%s}{%s}\n", t.ch, t.str.c_str(), t.tag.c_str());
    }
#endif

    if (tuples.empty())
    {
        fprintf(stderr, "no data for building hash function\n");
        exit(1);
    }

    // Determine the base filename:
    string base = BaseName(argv[1]);

    GenHashStrHeader(base + ".h", tuples);
    GenFastHashStrFunction(base + "_quick.inc", base, tuples);
    GenSmallHashStrFunction(base + "_small.inc", base, tuples);

    return 0;
}
