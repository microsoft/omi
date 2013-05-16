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

#include "field.h"
#include "indent.h"
#include "miextras.h"
#include <io/io.h>
#include "helpers.h"

#define _BORROW 0x01

void Field_Print(
    const Field* self,
    FILE* os, 
    MI_Type type, 
    MI_Uint32 level)
{
    MI_Value v;
    MI_Boolean e;
    MI_Uint8 f;
    Field_Extract(self, type, &v, &e, &f);

    if (!e)
    {
        Fzprintf(os, ZT("NULL"));
        return;
    }
    else 
    {
        switch (type)
        {
            case MI_BOOLEAN:
            {
                const MI_Boolean* p = (const MI_Boolean*)&v;
                Fzprintf(os, ZT("%s"), scs(*p ? "true" : "false"));
                break;
            }
            case MI_SINT8:
            {
                Fzprintf(os, ZT("%d"), *((const MI_Sint8*)&v));
                break;
            }
            case MI_UINT8:
            {
                Fzprintf(os, ZT("%u"), *((const MI_Uint8*)&v));
                break;
            }
            case MI_SINT16:
            {
                Fzprintf(os, ZT("%d"), *((const MI_Sint16*)&v));
                break;
            }
            case MI_UINT16:
            {
                Fzprintf(os, ZT("%u"), *((const MI_Uint16*)&v));
                break;
            }
            case MI_SINT32:
            {
                Fzprintf(os, ZT("%d"), *((const MI_Sint32*)&v));
                break;
            }
            case MI_UINT32:
            {
                Fzprintf(os, ZT("%u"), *((const MI_Uint32*)&v));
                break;
            }
            case MI_SINT64:
            {
                Fzprintf(os, SINT64_FMT_T, *((const MI_Sint64*)&v));
                break;
            }
            case MI_UINT64:
            {
                Fzprintf(os, UINT64_FMT_T, *((const MI_Uint64*)&v));
                break;
            }
            case MI_REAL32:
            {
                Fzprintf(os, ZT("%g"), *((const MI_Real32*)&v));
                break;
            }
            case MI_REAL64:
            {
                Fzprintf(os, ZT("%g"), *((const MI_Real64*)&v));
                break;
            }
            case MI_CHAR16:
            {
                Fzprintf(os, ZT("%u"), *((const MI_Char16*)&v));
                break;
            }
            case MI_DATETIME:
            {
                ZChar buf[26];
                DatetimeToStr((const MI_Datetime*)&v, buf);
                Fzprintf(os, ZT("%Z"), zcs(buf));
                break;
            }
            case MI_STRING:
            {
                Fzprintf(os, ZT("%Z"), zcs(*((ZChar**)&v)));
                break;
            }
            case MI_BOOLEANA:
            case MI_SINT8A:
            case MI_UINT8A:
            case MI_SINT16A:
            case MI_UINT16A:
            case MI_SINT32A:
            case MI_UINT32A:
            case MI_SINT64A:
            case MI_UINT64A:
            case MI_REAL32A:
            case MI_REAL64A:
            case MI_CHAR16A:
            case MI_DATETIMEA:
            {
                MI_BooleanA* arr = (MI_BooleanA*)&v;
                char* ptr = (char*)arr->data;
                MI_Uint32 i;

                Fzprintf(os, ZT("{"));

                for (i = 0; i < arr->size; i++)
                {
                    MI_Type stype = Type_ScalarOf(type);
                    MI_Type ssize = Type_SizeOf(stype);
                    Field field;

                    /* Build dummy field */
                    memcpy(&field, ptr, ssize);
                    *(MI_Boolean*)((char*)&field + ssize) = MI_TRUE;
                    *(MI_Uint8*)((char*)&field + ssize + 1) = 0;

                    /* Print dummy field */
                    Field_Print(&field, os, stype, level);
                    ptr += ssize;

                    if (i + 1 != arr->size)
                        Fzprintf(os, ZT(", "));
                }

                Fzprintf(os, ZT("}"));
                break;
            }
            case MI_STRINGA:
            {
                MI_StringA* arr = (MI_StringA*)&v;
                MI_Uint32 i;

                Fzprintf(os, ZT("{"));

                for (i = 0; i < arr->size; i++)
                {
                    Fzprintf(os, ZT("%Z"), zcs(arr->data[i]));

                    if (i + 1 != arr->size)
                        Fzprintf(os, ZT(", "));
                }

                Fzprintf(os, ZT("}"));
                break;
            }
            case MI_INSTANCE:
            case MI_REFERENCE:
            {
                MI_Instance* inst = *((MI_Instance**)&v);

                if ( type == MI_REFERENCE)
                    Fzprintf(os, ZT(" REF "));

                MI_Instance_Print(inst, os, level);
                break;
            }
            case MI_INSTANCEA:
            case MI_REFERENCEA:
            {
                MI_InstanceA* inst = ((MI_InstanceA*)&v);
                MI_Uint32 i;

                if ( type == MI_REFERENCEA)
                    Fzprintf(os, ZT(" REF "));

#if 0
                Fzprintf(os, "[%d]\n", (int)inst->size);
#endif
                Fzprintf(os, ZT("\n"));

                Indent(os, level);
                Fzprintf(os, ZT("{\n"));

                for (i = 0; i < inst->size; i++)
                {
                    MI_Instance_Print(inst->data[i], os, level + 1);
                }

                Indent(os, level);
                Fzprintf(os, ZT("}"));

                break;
            }
            default:
                break;
        }
    }
}
