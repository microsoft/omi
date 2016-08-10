/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <common.h>
#include <pal/strings.h>

#include "OIParser.h"
#include "FileGen.h"
#include "EmptyGen.h"
#if !defined(CONFIG_POSIX)
# include "EtwGen.h"
# include "ManifestGen.h"
#endif
#include "Syslog.h"

int genmain(int argc, _In_reads_z_(argc) _Deref_pre_z_ char** argv);

#if defined(_MSC_VER)
# pragma warning(disable: 4702)
#endif

#ifdef _MSC_VER
int __cdecl main(int argc, _In_reads_z_(argc) _Deref_pre_z_ char** argv)
#else
int main(int argc, char** argv)
#endif
{
    /* believe it or not but optimized MS compiler produces warning 4702 
     * (warning C4702: unreachable code) for the next line.
     */
    return genmain(argc, argv);
}

#define FILE_MODE "FILE"
#define SYSLOG_MODE "SYSLOG"
#define ETW_MODE "ETW"
#define NOOP_MODE "NOOP"

static const char HELP[] = "\
Open Instrumentation Generator \n\
\n\
The Open Istrumentation allows developers to \n\
- define event schemas by defining C function signatures\n\
- annotate the signatures with formatting strings\n\
\n\
This generator reads annotated header file, and outputs:\n\
    - .c implementation to produce events\n\
    - For ETW: Manifest\n\
\n\
Usage:\n\
\n\
    oigenc.exe <mode> <more options>\n\
        where <mode> = ETW, SYSLOG, FILE, NOOP\n\
\n\
For ETW (Windows):\n\
    oigenc.exe " ETW_MODE " <headerFile> <provider name> <{guid}> <outputCFile> <outputManifestFile>\n\
    (ETW solution is not fully implemented yet!!!)\n\
For Syslog (Linux):\n\
    oigenc.exe " SYSLOG_MODE " <headerFile> <appName> <syslogOptions> <syslogFacility> <outputCFile>\n\
    see http://pubs.opengroup.org/onlinepubs/007908799/xsh/syslog.h.html for syslog flags\n\
For File logging:\n\
    oigenc.exe " FILE_MODE " <headerFile> <outputCFile>\n\
For No tracing at all:\n\
    oigenc.exe " NOOP_MODE " <headerFile> <outputCFile>\n\
\n\
Example:\n\
\n\
    oigenc.exe SYSLOG Frog.h Frog LOG_NDELAY LOG_LOCAL1 Frog_Gen.c\n\
    oigenc.exe ETW Frog.h Frog {C4CDA692-6B0E-42D7-9E23-5016B32DE397} Frog_Gen.c Manifest.man\n";

int genmain(int argc, _In_reads_z_(argc) _Deref_pre_z_ char** argv)
{
    if (argc < 2)
    {
        printf(HELP);
        return 0;
    }

#if !defined(CONFIG_POSIX)
    if (Strcmp(argv[1], ETW_MODE) == 0 && argc == 8)
    {   
        /* ETW tracing */
        char * header = argv[2];
        char * providerName = argv[3];
        char * providerId = argv[4];
        char * binary = argv[5];
        char * target = argv[6];
        char * manifest = argv[7];

        int count = 0;
        OIEvent * events = 0;
        OIParser parser;
        Buckets etwInfo;

        memset(&parser, 0, sizeof(OIParser));
        memset(&etwInfo, 0, sizeof(Buckets));

        printf("Parsing ...");

        if (!Parser_Init(&parser, header))
        {
            printf("OIGEN: out of memory while parsing the input file '%s'", header);
            return 1;
        }

        if (!Parser_Parse(&parser, &events, &count))
        {
            printf("OIGEN: error parsing the input file '%s'", header);
            return 1;
        }

        printf("Generating ...");

        if (!GenerateTaskOpcodeKeywords(events, &etwInfo))
        {
            printf("OIGEN: GenerateTaskOpcodeKeywords failed");
            return 1;
        }

        if (!GenerateEtw(events, &etwInfo, providerId, target))
        {
            printf("OIGEN: error while writing ETW code, the input file '%s'", header);
            return 1;
        }

        if (!GenerateManifest(events, &etwInfo, providerName, providerId, binary, manifest))
        {
            printf("OIGEN: error while writing manifest, the input file '%s'", header);
            return 1;
        }

        Parser_Destroy(&parser);
        CleanupBuckets(&etwInfo);
    }
    else 
#endif
    if (Strcmp(argv[1], FILE_MODE) == 0 && argc == 4)
    {
        /* file tracing */

        char * header = argv[2];
        char * target = argv[3];

        int count = 0;
        OIEvent * events = 0;
        OIParser parser;

        memset(&parser, 0, sizeof(OIParser));

        if (!Parser_Init(&parser, header))
        {
            printf("OIGEN: out of memory while parsing the input file '%s'", header);
            return 1;
        }

        if (!Parser_Parse(&parser, &events, &count))
        {
            printf("OIGEN: error parsing the input file '%s'", header);
            return 1;
        }

        if (!GenerateFile(events, target))
        {
            printf("OIGEN: error while writing File code, the input file '%s'", header);
            return 1;
        }

        Parser_Destroy(&parser);
    }
    else if (Strcmp(argv[1], SYSLOG_MODE) == 0 && argc == 7)
    {
        char * header = argv[2];
        char * appName = argv[3];
        char * syslogOpt = argv[4];
        char * syslogFac = argv[5];
        char * target = argv[6];

        int count = 0;
        OIEvent * events = 0;
        OIParser parser;

        memset(&parser, 0, sizeof(OIParser));

        if (!Parser_Init(&parser, header))
        {
            printf("OIGEN: out of memory while parsing the input file '%s'", header);
            return 1;
        }

        if (!Parser_Parse(&parser, &events, &count))
        {
            printf("OIGEN: error parsing the input file '%s'", header);
            return 1;
        }

        if (!GenerateSyslog(events, appName, syslogOpt, syslogFac, target))
        {
            printf("OIGEN: error while writing Syslog code, the input file '%s'", header);
            return 1;
        }

        Parser_Destroy(&parser);
    }
    else if (Strcmp(argv[1], NOOP_MODE) == 0 && argc == 4)
    {
        /* no tracing */

        char * header = argv[2];
        char * target = argv[3];

        int count = 0;
        OIEvent * events = 0;
        OIParser parser;

        memset(&parser, 0, sizeof(OIParser));

        if (!Parser_Init(&parser, header))
        {
            printf("OIGEN: out of memory while parsing the input file '%s'", header);
            return 1;
        }

        if (!Parser_Parse(&parser, &events, &count))
        {
            printf("OIGEN: error parsing the input file '%s'", header);
            return 1;
        }

        if (!GenerateEmpty(events, target))
        {
            printf("OIGEN: error while writing Empty code, the input file '%s'", header);
            return 1;
        }

        Parser_Destroy(&parser);
    }
    else
    {
        printf("Unknown mode or incorrect number of parameters! mode=[%s], parameters=[%d]\n", argv[1], argc);
        printf(HELP);
        return 1;
    }

    printf("\nSuccess!\n");

    return 0;
}
