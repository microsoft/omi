/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "common.h"
#include "base64.h"

/* Maximum block size to send to Base64EncCallback (a multiple of 4) */

#if defined(CONFIG_FAVORSIZE)
# define BASE64ENC_BLOCK_SIZE 64
#else
# define BASE64ENC_BLOCK_SIZE 512
#endif

/* Maximum block size to send to Base64DecCallback (a multiple of 3) */
#if defined(CONFIG_FAVORSIZE)
# define BASE64DEC_BLOCK_SIZE 64
#else
# define BASE64DEC_BLOCK_SIZE 512
#endif

static const char encTable[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
    'w', 'x', 'y', 'z', '0', '1', '2', '3', 
    '4', '5', '6', '7', '8', '9', '+', '/',
};

MI_INLINE char Enc6Bits(unsigned char x)
{
    return encTable[x];
}

int Base64Enc(
    const void* data_,
    size_t size,
    Base64EncCallback callback,
    void* callbackData)
{
    const unsigned char* data = (const unsigned char*)data_;
    char buf[BASE64ENC_BLOCK_SIZE];
    size_t n = 0;

    /* Encode each group of 3 bytes into a group of 4 characters */

    while (size)
    {
        unsigned int i1 = 0;
        unsigned int i2 = 0;
        unsigned int i3 = 0;
        unsigned int i4 = 0;
        size_t m = 0;
        int done = 0;

        /* Check whether there is room in the buffer for 4 more bytes (the
         * maximum number of bytes that one pass of this loop can inject.
         */

        if (n + 4 > BASE64ENC_BLOCK_SIZE)
        {
            if ((*callback)(buf, n, callbackData) != 0)
                return -1;

            n = 0;
        }

        /*
         * B1       B2       B3
         * +--------+--------+--------+
         * |11111100|00002222|22333333|
         * +--------+--------+--------+
         */

        /* Process byte 1 */
        {
            unsigned char b1 = *data++;
            size--;
            m++;

            i1 |= (b1 & 0xFC) >> 2;
            i2 |= (b1 & 0x03) << 4;
            buf[n++] = Enc6Bits((unsigned char) i1);
        }

        /* Process byte 2 */

        if (size)
        {
            unsigned char b2 = *data++;
            size--;
            m++;

            i2 |= (b2 & 0xF0) >> 4;
            i3 |= (b2 & 0x0F) << 2;
            buf[n++] = Enc6Bits((unsigned char)i2);
        }
        else
        {
            buf[n++] = Enc6Bits((unsigned char)i2);
            done = 1;
        }

        /* Process byte 3 */

        if (size)
        {
            unsigned char b3 = *data++;
            size--;
            m++;

            i3 |= (b3 & 0xCF) >> 6;
            i4 |= b3 & 0x3F;

            buf[n++] = Enc6Bits((unsigned char)i3);
            buf[n++] = Enc6Bits((unsigned char)i4);
        }
        else if (!done)
        {
            buf[n++] = Enc6Bits((unsigned char)i3);
        }

        /* Add padding */

        switch (m)
        {
            case 1:
                buf[n++] = '=';
                /* Fallthorugh intentional */
            case 2:
                buf[n++] = '=';
        }
    }

    /* Send any remaining bytes */

    if (n)
    {
        if ((*callback)(buf, n, callbackData) != 0)
            return -1;
    }

    return 0;
}

#if !defined(CONFIG_FAVORSIZE)

/* decoding table: 0-63 - valid value, 64-padding, 65-skip, 0xFF-invalid */
static const unsigned char decTable[128] = 
{
    /* 0 - 31 */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 

    /* 32 - 39:  !"#$%&' */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 

    /* 40 - 42: ()*+,-./ */
    0xFF, 0xFF, 0xFF, 62, 0xFF, 0xFF, 0xFF, 63,   

    /* 0 -9 */
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 

    /* :;<=>? */
    0xFF,0xFF,0xFF,64,0xFF,0xFF,

    /* @ A-Z */
    0xFF, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 

    /* []\\^_` */
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    /* a-z */
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 


    /* {|} ~ 127 */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

#endif /* CONFIG_FAVORSIZE */

static unsigned char DecChar(unsigned char c)
{
#if defined(CONFIG_FAVORSIZE)

    if (c >= 'A' && c <= 'Z')
        return c - 'A';

    if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;

    if (c >= '0' && c <= '9')
        return c - '0' + 52;

    if (c == '+')
        return 62;

    if (c == '/')
        return 63;

    if (c == '=')
        return 64;

    return 0xFF;

#else /* defined(CONFIG_FAVORSIZE) */

    if (c >= 128)
        return 0xFF;

    return decTable[c];

#endif /* !defined(CONFIG_FAVORSIZE) */
}

int Base64Dec(
    const void* data_,
    size_t size,
    Base64DecCallback callback,
    void* callbackData)
{
    unsigned char* data = (unsigned char*)data_;
    unsigned char* end = data + size;
    unsigned char buf[BASE64DEC_BLOCK_SIZE];
    size_t n = 0;

    /* perform decoding - 4 input bytes are converted into 3 output, 
     * using provided pointers data/tgt
     * since decoding is done inplace and result is smaller than input, 
     * no checks for buffer size is required
     */

    while (data != end)
    {
        unsigned char c1;
        unsigned char c2;
        unsigned char c3;
        unsigned char c4;

        /* Decode character 1 */

        c1 = DecChar((*data++) & 0x7f);

        if (c1 == 0xFF || data == end)
            return -1;

        /* Decode character 2 */

        c2 = DecChar((*data++) & 0x7f);

        if (c2 == 0xFF || data == end)
            return -1;

        /* Decode character 3 */

        c3 = DecChar((*data++) & 0x7f);

        if (c3 == 0xFF || data == end)
            return -1;

        /* Decode character 4 */

        c4 = DecChar((*data++) & 0x7f);

        if (c4 == 0xFF)
            return -1;

        /* Invoke callback if buffer would overflow below */

        if (n + 3 > BASE64ENC_BLOCK_SIZE)
        {
            if ((*callback)(buf, n, callbackData) != 0)
                return -1;

            n = 0;
        }

        /* Convert 4 characters to 3 bytes */

        buf[n++] = (c1 << 2) | (c2 >> 4);

        if (c3 != 64)
            buf[n++] = ((c2 & 0xF) << 4) | (c3 >> 2);

        if (c4 != 64)
            buf[n++] = ((c3 & 0x3) << 6) | c4;
    }

    /* Send any remaining bytes */

    if (n)
    {
        if ((*callback)(buf, n, callbackData) != 0)
            return -1;
    }

    // return the size of the decoded buffer
    return n;
}
