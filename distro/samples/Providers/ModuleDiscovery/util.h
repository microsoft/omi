
#ifndef _UTIL_h
#define _UTIL_h

#include <io/io.h>
#include "PS_ModuleFile.h"
#include "PS_Module.h"

#define FILECOUNT 10
#define MFILECOUNT (FILECOUNT-1)

typedef struct _PSModuleFile
{
    const char * filename;
    unsigned char *data;
    unsigned int datalength;
}PSModuleFile;

extern PS_Module psmodule;
extern PS_ModuleFile psmodulefiles[];

MI_Result ConstructModuleInstances(_In_ struct _MI_Context* context);
void DestructModuleInstances();
MI_Result ConstructModuleFileInstances(_In_ struct _MI_Context* context);
void DestructModuleFileInstances();
#endif
