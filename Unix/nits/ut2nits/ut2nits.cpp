#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <pal/strings.h>
#include <pal/file.h>

using namespace std;

int main(int argc, char *argv[])
{
    ofstream outfile("outfile.cpp");
        
    ifstream infile(argv[1]);
    if (!infile.good())
    {
        cerr << "Error with reading file\n";
        return -1;
    }

    char *inbuf = new char[4002];
    if(!inbuf)
    {
        cerr << "Error with allocating memory\n";
        return -1;
    }

    vector<string> ut_tests;
    while (infile.good())
    {        
        memset(inbuf, 0, 4000);
        infile.getline(inbuf, 4000, '\n');
        size_t len = strlen(inbuf);

        char *utTestPos = strstr(inbuf, "UT_TEST(");
        
        if(utTestPos)
        {
            utTestPos += 8;
            char *utTestEnd = strstr(utTestPos, ")");
            *utTestEnd = '\0';
            string utTestString(utTestPos);
            ut_tests.push_back(utTestString);
            continue;
        }
    }
    for(size_t i = 0; i < ut_tests.size(); i++)
    {
        cout << ut_tests[i].c_str() << endl;
    }

    ifstream infile1(argv[1]);
    infile1.seekg(0, infile.beg);

    bool innitstest = false;
    size_t currentDepth = 0;
    while (infile1.good())
    {        
        memset(inbuf, 0, 4000);
        infile1.getline(inbuf, 4000, '\n');
        size_t len = strlen(inbuf);

        if(strstr(inbuf, "UT_TEST("))
           continue;

        if(innitstest)
        {
            for(size_t i = 0; i < len; i++)
            {
                if(inbuf[i] == '{')
                {
                    currentDepth++;
                }
                else if(inbuf[i] == '}')
                {
                    currentDepth--;
                    if(currentDepth == 0)
                    {
                        outfile << "}\nNitsEndTest\n";
                        innitstest = false;
                        break;
                    }
                }
            }

            if(!innitstest)
               continue;
            char *returnFound = strstr(inbuf, "return;");
            if(returnFound)
            {
            inbuf[len + 4] = '\0';
            for(char *pos = inbuf + len - 1; pos >= returnFound; pos--)
            {
                 pos[4] = pos[0];
            }
            returnFound[0] = 'N'; returnFound[1] = 'i';
            returnFound[2] = 't'; returnFound[3] = 's';
            returnFound[4] = 'R'; returnFound[5] = 'e';
            returnFound[6] = 't'; returnFound[7] = 'u';
            returnFound[8] = 'r'; returnFound[9] = 'n'; returnFound[10] = ';';
            len += 4;
            }
        }

        char *testFoundAt = NULL;
        for(size_t i = 0; i < ut_tests.size(); i++)
        {
            testFoundAt = strstr(inbuf, ut_tests[i].c_str());
            if(testFoundAt)
            {
                innitstest = true;
                currentDepth = 0;
                char *current = inbuf;
                strcpy(current, "NitsTestWithSetup(");
                current += strlen("NitsTestWithSetup(");
                const char *testname = ut_tests[i].c_str();
                strcpy(current, testname);
                current += strlen(testname);
                strcpy(current, ", FooSetup)\n");
                outfile << inbuf;
                ut_tests.erase(ut_tests.begin() + i);
                break;
            }
        }
        if(testFoundAt)
            continue;

        inbuf[len] = '\n';
        inbuf[len+1] = '\0';
        outfile << inbuf;
    }

}