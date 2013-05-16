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

#include "conf.h"
#include <stdlib.h>
#include <ctype.h>
#include <io/io.h>

struct _Conf
{
    FILE* is;
    unsigned int line;
    char buf[1024];
    char err[128];
};

Conf* Conf_Open(const char* path)
{
    FILE* is;
    Conf* self;

    /* Open file */
    is = Fopen(path, "rb");
    if (!is)
        return NULL;
    
    /* Allocate self object */
    self = (Conf*)calloc(1, sizeof(Conf));
    if (!self)
    {
        fclose(is);
        return NULL;
    }

    /* initialize self */
    self->is = is;

    return self;
}

int Conf_Read(Conf* self, const char** key, const char** value)
{
    while (fgets(self->buf, sizeof(self->buf), self->is) != NULL)
    {
        char* p = self->buf;
        char* keyEnd;

        /* Increment line counter */
        self->line++;

        /* Skip comment lines */
        if (self->buf[0] == '#')
            continue;

        /* Skip blank lines */
        {
            char* end = p + strlen(p);
            while (end != p && isspace((unsigned char)end[-1]))
                *--end = '\0';

            if (p[0] == '\0')
                continue;
        }

        /* Skip leading whitespace */
        while (*p && isspace((unsigned char)*p))
            p++;

        /* Expect key */
        {
            char* start = p;

            if (!isalpha((unsigned char)*p) && *p != '_')
            {
                Snprintf(self->err, sizeof(self->err), "expected keyword");
                return -1;
            }

            while (*p && (isalnum((unsigned char)*p) || *p == '_'))
                p++;

            keyEnd = p;

            if (key)
                *key = start;
        }

        /* Skip whitespace */
        while (*p && isspace((unsigned char)*p))
            p++;

        /* Expect '=' character */
        if (*p != '=')
        {
            Snprintf(self->err, sizeof(self->err), "expected '='");
            return -1;
        }
        p++;

        /* Terminate key */
        *keyEnd = '\0';

        /* Skip whitespace */
        while (*p && isspace((unsigned char)*p))
            p++;

        /* Get value */
        if (value)
            *value = p;

        /* return success */
        return 0;
    }

    /* End of file */
    return 1;
}

const char* Conf_Error(Conf* self)
{
    return self->err;
}

unsigned int Conf_Line(Conf* self)
{
    return self->line;
}

void Conf_Close(Conf* self)
{
    if (self && self->is)
    {
        fclose(self->is);
        free(self);
    }
}
