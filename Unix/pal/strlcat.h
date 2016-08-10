/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#if !defined(SRC) || !defined(STRLCAT)
# error "internal file: do not include!"
#endif

size_t STRLCAT(
    _Inout_updates_z_(size) DEST* dest, 
    _In_z_ const SRC* src, 
    size_t size)
{
    const SRC* start = src;

    if (size)
    {
        DEST* end = dest + size - 1;

        while (*dest && dest != end)
            dest++;

        while (*src && dest != end)
            *dest++ = (DEST)*src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}
