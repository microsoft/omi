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

#ifndef _omi_conf_h
#define _omi_conf_h

#include <common.h>

/*
**==============================================================================
**
** Conf
**
**     Provides processing of configuration files. Configuration files contain
**     options expressed KEY=VALUE pairs. For example:
**
**         # My Configuration File
**         port=1234
**         prefix=/usr/local/bin
**         libdir=/usr/local/lib
**         trace=3
**
**     The following example shows how to read key-value pairs form a 
**     configuration file.
**
**         Conf* conf = Conf_Open("/etc/mine.conf");
**
**         if (!conf)
**         {
**             fprintf(stderr, "error: failed to open file\n");
**             exit(1);
**         }
**
**         for (;;)
**         {
**             const char* key;
**             const char* value;
**             int r;
**
**             r = Conf_Read(conf, &key, &value);
**             if (r == -1)
**             {
**                 fprintf(stderr, "error: %s\n", Conf_Error(conf));
**                 exit(1);
**             }
**
**             printf("key{%s}, value{%s}\n", key, value);
**         }
**
**         Conf_Close(conf);
**
**==============================================================================
*/

BEGIN_EXTERNC

typedef struct _Conf Conf;

Conf* Conf_Open(const char* path);

int Conf_Read(Conf* self, const char** key, const char** value);

const char* Conf_Error(Conf* self);

unsigned int Conf_Line(Conf* self);

void Conf_Close(Conf* self);

END_EXTERNC

#endif /* _omi_conf_h */
