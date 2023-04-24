/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "shlib.h"
#include "config.h"
#include <pal/strings.h>

Shlib* Shlib_Open_Injected(
    _In_z_ const PAL_Char* path,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
    {
        return NULL;
    }

    if(path == NULL)
        return NULL;
    
    const char *temp = NULL;
    temp = path;


    return (Shlib*)dlopen(temp, PAL_DLOPEN_FLAGS);
}

PAL_Char* Shlib_Err()
{
    char* err = dlerror();
    size_t len = strlen(err) + 1;
    PAL_Char* copy = PAL_Malloc(len * sizeof(PAL_Char));
    if(copy)  TcsStrlcpy(copy, err, len);
    return copy;
}

_Use_decl_annotations_
void Shlib_Format(
    TChar path[PAL_MAX_PATH_SIZE],
    const char* dirName, 
    const char* shortName)
{
    *path = '\0';

    /* Directory */
    if (dirName && dirName[0] != '\0')
    {
        TcsStrlcat(path, dirName, PAL_MAX_PATH_SIZE);
        TcsStrlcat(path, "/", PAL_MAX_PATH_SIZE);
    }

    /* Prefix */
    TcsStrlcat(path, "lib", PAL_MAX_PATH_SIZE);

    /* Library name */
    TcsStrlcat(path, shortName, PAL_MAX_PATH_SIZE);

    /* Suffix */
    TcsStrlcat(path, ".", PAL_MAX_PATH_SIZE);
    TcsStrlcat(path, CONFIG_SHLIBEXT, PAL_MAX_PATH_SIZE);
}
