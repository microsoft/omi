#include "CustomizedMethod.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <base/strings.h>
#include <common.h>
#include <stdio.h>
#include <map>

#include "TestClient.h"
using namespace std;
using namespace mi;

// s_fn is a global variable. It is used to customize function index.
std::map<std::string, MODULE_TEST_CALLBACK> s_fn;
 
void RunCommand(const char* command, String &value)
{
    FILE *fpipe;

    if (!(fpipe = popen(command,"r")) )
    {
        return;
    }

    // Clear value.
    value.Clear();

    char ch;
    while (((ch = fgetc(fpipe)) != EOF) &&
        (ch != 0xff))
    {
        value += ch;
    }

	pclose(fpipe);
}

// TODO: Append customized function from here.
static void RunLinuxCommand(mi::String &val)
{
    RunCommand(val.Str(), val);
}

static void RunHardcode(mi::String &val)
{
    // Return value directly.
    return;
}


// Append customized function from above block.
void _registerCallback(mi::String key, MODULE_TEST_CALLBACK pfn)
{
    s_fn.insert(std::pair<std::string, MODULE_TEST_CALLBACK>(key.Str(), pfn));
}

void _RegisterFunction()
{
    // TODO: Declare customized function like format as below.
    APPEND_TEST("RunLinuxCommand", RunLinuxCommand);  
    APPEND_TEST("RunHardcode", RunHardcode);  
}

