#include <cstdlib>

using namespace std;

extern int climain(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    exit(climain(argc, argv));
}
