/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <xml/xml.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

using namespace std;
const char* arg0;

bool Inhale(const char* path, vector<char>& data)
{
    struct stat st;

    if (stat(path, &st) != 0)
    {
        cerr << arg0 << ": failed to stat file: " << path << endl;
        exit(1);
    }

    data.reserve(st.st_size + 1);

    FILE* is = fopen(path, "r");

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

static void Indent(size_t level)
{
    size_t n = level * 2;

    for (size_t i = 0; i < n; i++)
    {
        putchar(' ');
    }
}

static void Print(const char* path)
{
    XML xml;
    XML_Elem e;
    int r;
    vector<char> data;
    size_t level = 0;

    if (!Inhale(path, data))
    {
        cerr << arg0 << ": failed to open " << path << endl;
        exit(1);
    }

    XML_Init(&xml);
    XML_SetText(&xml, &data[0]);

    while ((r = XML_Next(&xml, &e)) == 0)
    {
        switch (e.type)
        {
            case XML_NONE:
                break;
            case XML_INSTRUCTION:
            case XML_START:
            {
                Indent(level);

                if (e.type == XML_START)
                {
                    printf("<%.*s", (int)e.size, e.data);
                    level++;
                }
                else
                    printf("<?%.*s", (int)e.size, e.data);

                if (e.attrsSize)
                    printf(" ");

                for (size_t i = 0; i < e.attrsSize; i++)
                {
                    const XML_Attr& a = e.attrs[i];

                    printf("%s=\"%s\"", a.name, a.value);

                    if (i + 1 != e.attrsSize)
                    {
                        printf(" ");
                    }
                }

                if (e.type == XML_START)
                    printf(">\n");
                else
                    printf("?>\n");
                break;
            }
            case XML_END:
            {
                level--;
                Indent(level);
                printf("</%.*s>\n", (int)e.size, e.data);

                break;
            }
            case XML_CHARS:
            {
                Indent(level);
                printf("%.*s\n", (int)e.size, e.data);
                break;
            }
            case XML_COMMENT:
            {
                Indent(level);
                printf("<!--%.*s-->\n", (int)e.size, e.data);
                break;
            }
        }
    }

    if (r != 1)
    {
        char msg[1024];
        XML_FormatError(&xml, msg, sizeof(msg));
        printf("%s:%s\n", path, msg);
        exit(1);
    }
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 2)
    {
        cerr << "Usage: " << arg0 << " file" << endl;
        exit(1);
    }

    Print(argv[1]);

    return 0;
}
