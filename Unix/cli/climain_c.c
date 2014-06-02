#include <stdlib.h>
#include <MI.h>

extern MI_Result climain(int argc, const MI_Char* argv[]);

#if defined (_MSC_VER)
int MI_MAIN_CALL wmain(int argc, const MI_Char* argv[])
{
    exit((int) climain(argc, argv));
}
#else
int MI_MAIN_CALL main(int argc, const char* argv[])
{
#if defined (MI_USE_WCHAR)
    /* Going to need to convert the args to MI_Char */
    printf("Do not support %s when using wide char support yet\n", argv[0]);
    return 0;
#else
    exit((int) climain(argc, argv));
#endif
}
#endif
