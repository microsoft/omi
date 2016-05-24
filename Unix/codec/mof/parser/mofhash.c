/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include "mofhash.h"
#include "base/naming.h"
#include "base/batch.h"

/*
**==============================================================================
**
** string hash function
**
**==============================================================================
*/
MI_Uint32 HashName(_In_z_ const MI_Char* str)
{
    MI_Uint32 hash = HASH_SEED_PRIME_NUMBER;
    const MI_Char* p = str;
    while(*p)
    {  
        hash ^= ((hash << 5) + PAL_tolower(*p) + (hash >> 2));
        p++;
    }
    return hash % HASH_TABLE_SIZE;
}

/*
**==============================================================================
**
** Initialize hash table
**
**==============================================================================
*/
int StringHash_Init(
    _In_ void * mofbatch,
    _Inout_ StringHash *hash)
{
    Batch* batch = (Batch*)mofbatch;
    if (hash->nodes == NULL)
    {
        hash->nodes = (HashNodePtr*)Batch_GetClear(batch, sizeof(HashNodePtr) * (HASH_TABLE_SIZE));
        if (NULL == hash->nodes)
        {
            return -1;
        }
    }
    return 0;
}

/*
**==============================================================================
**
** Add string to hash table
**
**==============================================================================
*/
int StringHash_Add(
    _In_ void* mofbatch,
    _Inout_ StringHash *hash,
    _In_ MI_Uint32 pos,
    _In_ MI_Uint32 code,
    _In_z_ const MI_Char* str)
{
    Batch * batch = (Batch*)mofbatch;
    MI_Uint32 h = HashName(str);
    HashNodePtr node = (HashNodePtr)Batch_GetClear(batch, sizeof(HashNode));
    if (NULL == node)
    {
        return -1;
    }
    node->source = str;
    node->code = code;
    node->pos = pos;
    node->next = hash->nodes[h];
    hash->nodes[h] = node;
    return 0;
}

/*
**==============================================================================
**
** Find string position tring to hash table
**  Return: index of the string in original array
**==============================================================================
*/
MI_Uint32 StringHash_Find(
    _In_ StringHash *hash,
    _In_z_ const MI_Char* name)
{
    if(hash->nodes)
    {
        MI_Uint32 h = HashName(name);
        MI_Uint32 code = Hash(name);
        HashNodePtr node;
        node = hash->nodes[h];
        while (node)
        {
            if ((node->code == code) && (Tcscasecmp(node->source, name) == 0))
            {
                return node->pos;
            }
            node = node->next;
        }
    }
    return HASH_INVALID_POS;
}
