/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "field.h"
#include "indent.h"
#include "miextras.h"
#include <pal/format.h>
#include "helpers.h"

#define _BORROW 0x01

void Field_Print(
    const Field* self,
    FILE* os, 
    MI_Type type, 
    MI_Uint32 level,
    MI_Boolean showNulls,
    MI_Boolean isClass)
{
    MI_Value v;
    MI_Boolean e;
    MI_Uint8 f;
    Field_Extract(self, type, &v, &e, &f);

    if (!e)
    {
        Ftprintf(os, ZT("NULL"));
        return;
    }
    else 
    {
        switch (type)
        {
            case MI_BOOLEAN:
            {
                const MI_Boolean* p = (const MI_Boolean*)&v;
                Ftprintf(os, ZT("%s"), scs(*p ? "true" : "false"));
                break;
            }
            case MI_SINT8:
            {
                Ftprintf(os, ZT("%d"), *((const MI_Sint8*)&v));
                break;
            }
            case MI_UINT8:
            {
                Ftprintf(os, ZT("%u"), *((const MI_Uint8*)&v));
                break;
            }
            case MI_SINT16:
            {
                Ftprintf(os, ZT("%d"), *((const MI_Sint16*)&v));
                break;
            }
            case MI_UINT16:
            {
                Ftprintf(os, ZT("%u"), *((const MI_Uint16*)&v));
                break;
            }
            case MI_SINT32:
            {
                Ftprintf(os, ZT("%d"), *((const MI_Sint32*)&v));
                break;
            }
            case MI_UINT32:
            {
                Ftprintf(os, ZT("%u"), *((const MI_Uint32*)&v));
                break;
            }
            case MI_SINT64:
            {
                Ftprintf(os, SINT64_FMT_T, *((const MI_Sint64*)&v));
                break;
            }
            case MI_UINT64:
            {
                Ftprintf(os, UINT64_FMT_T, *((const MI_Uint64*)&v));
                break;
            }
            case MI_REAL32:
            {
                Ftprintf(os, ZT("%g"), *((const MI_Real32*)&v));
                break;
            }
            case MI_REAL64:
            {
                Ftprintf(os, ZT("%g"), *((const MI_Real64*)&v));
                break;
            }
            case MI_CHAR16:
            {
                Ftprintf(os, ZT("%u"), *((const MI_Char16*)&v));
                break;
            }
            case MI_DATETIME:
            {
                ZChar buf[26];
                DatetimeToStr((const MI_Datetime*)&v, buf);
                Ftprintf(os, PAL_T("%T"), tcs(buf));
                break;
            }
            case MI_STRING:
            {
                Ftprintf(os, PAL_T("%T"), tcs(*((TChar**)&v)));
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

                Ftprintf(os, ZT("{"));

                for (i = 0; i < arr->size; i++)
                {
                    MI_Type stype = Type_ScalarOf(type);
                    MI_Type ssize = Type_SizeOf(stype);
                    Field field;

                    /* Build dummy field */
                    _Analysis_assume_(sizeof(field)==(ssize+sizeof(MI_Boolean)+sizeof(MI_Uint8)));
                    memcpy(&field, ptr, ssize);
                    *(MI_Boolean*)((char*)&field + ssize) = MI_TRUE;
                    *(MI_Uint8*)((char*)&field + ssize + 1) = 0;

                    /* Print dummy field */
                    Field_Print(&field, os, stype, level, showNulls, isClass);
                    ptr += ssize;

                    if (i + 1 != arr->size)
                        Ftprintf(os, ZT(", "));
                }

                Ftprintf(os, ZT("}"));
                break;
            }
            case MI_STRINGA:
            {
                MI_StringA* arr = (MI_StringA*)&v;
                MI_Uint32 i;

                Ftprintf(os, ZT("{"));

                for (i = 0; i < arr->size; i++)
                {
                    Ftprintf(os, PAL_T("%T"), tcs(arr->data[i]));

                    if (i + 1 != arr->size)
                        Ftprintf(os, PAL_T(", "));
                }

                Ftprintf(os, PAL_T("}"));
                break;
            }
            case MI_INSTANCE:
            case MI_REFERENCE:
            {
                MI_Instance* inst = *((MI_Instance**)&v);

                if ( type == MI_REFERENCE)
                    Ftprintf(os, ZT(" REF "));

                Instance_Print(inst, os, level, showNulls, isClass);
                break;
            }
            case MI_INSTANCEA:
            case MI_REFERENCEA:
            {
                MI_InstanceA* inst = ((MI_InstanceA*)&v);
                MI_Uint32 i;

                if ( type == MI_REFERENCEA)
                    Ftprintf(os, ZT(" REF "));

#if 0
                Ftprintf(os, "[%d]\n", (int)inst->size);
#endif
                Ftprintf(os, ZT("\n"));

                Indent(os, level);
                Ftprintf(os, ZT("{\n"));

                for (i = 0; i < inst->size; i++)
                {
                    Instance_Print(inst->data[i], os, level + 1, showNulls, isClass);
                }

                Indent(os, level);
                Ftprintf(os, ZT("}"));

                break;
            }
            default:
                break;
        }
    }
}
