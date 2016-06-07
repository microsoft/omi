/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "field.h"
#include "types.h"
#include "alloc.h"
#include "instance.h"
#include "return.h"
#include "types.h"
#include <pal/strings.h>
#include "miextras.h"
#include <pal/intsafe.h>
#include <pal/format.h>
#include <pal/file.h>
#include "helpers.h"
#include "strarr.h"

#define _BORROW 0x01

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

static unsigned char _fieldSizes[] =
{
    sizeof(MI_BooleanField),
    sizeof(MI_Uint8Field),
    sizeof(MI_Sint8Field),
    sizeof(MI_Uint16Field),
    sizeof(MI_Sint16Field),
    sizeof(MI_Uint32Field),
    sizeof(MI_Sint32Field),
    sizeof(MI_Uint64Field),
    sizeof(MI_Sint64Field),
    sizeof(MI_Real32Field),
    sizeof(MI_Real64Field),
    sizeof(MI_Char16Field),
    sizeof(MI_DatetimeField),
    sizeof(MI_StringField),
    sizeof(MI_ReferenceField),
    sizeof(MI_InstanceField),
    sizeof(MI_BooleanAField),
    sizeof(MI_Uint8AField),
    sizeof(MI_Sint8AField),
    sizeof(MI_Uint16AField),
    sizeof(MI_Sint16AField),
    sizeof(MI_Uint32AField),
    sizeof(MI_Sint32AField),
    sizeof(MI_Uint64AField),
    sizeof(MI_Sint64AField),
    sizeof(MI_Real32AField),
    sizeof(MI_Real64AField),
    sizeof(MI_Char16AField),
    sizeof(MI_DatetimeAField),
    sizeof(MI_StringAField),
    sizeof(MI_ReferenceAField),
    sizeof(MI_InstanceAField),
};

MI_INLINE size_t FieldSizeOf(MI_Type type)
{
    return _fieldSizes[(int)type];
}

static void* _CloneSimpleArray(
    const void* data,
    size_t size,
    MI_Uint32 type,
    Batch* batch)
{
    void* array;
    size_t m;

    /* Handle empty arrays up front */
    if (!data || size == 0)
        return NULL;

    /* Get element size in bytes */
    m = Type_SizeOf(Type_ScalarOf((MI_Type)type));

    /* Allocate memory for array elements */
    array = BAlloc(batch, size * m, CALLSITE);
    if (!array)
        return NULL;

    /* Copy elements to the new array */
    memcpy(array, data, m * size);

    return array;
}

static void* _CloneInstanceArray(
    const void* data_,
    size_t size,
    Batch* batch)
{
    const MI_Instance** data = (const MI_Instance**)data_;
    MI_Instance** array;
    size_t i;

    /* Handle empty arrays up front */
    if (!data || size == 0)
        return NULL;

    /* validate entries */
    for (i = 0; i < size; i++ )
    {
        if (!data[i])
        {
            /* Null elements are illegal */
            return NULL;
        }
    }

    /* Allocate memory for the new array */
    array = BCalloc(batch, size * sizeof(MI_Instance*), CALLSITE);
    if (!array)
        return NULL;

    /* Clone each reference (or instance) */
    for (i = 0; i < size; i++)
    {
        MI_Result r = Instance_Clone(data[i], &array[i], batch);
        if (r != MI_RESULT_OK)
            return NULL;
    }

    return array;
}

INLINE void _Copy(
    Field* dest,
    const Field* src,
    MI_Type type)
{
    memcpy(dest, src, FieldSizeOf(type));
}

static void _Swap(
    Field* field1,
    Field* field2,
    MI_Type type)
{
    Field tmp;
    _Copy(&tmp, field1, type);
    _Copy(field1, field2, type);
    _Copy(field2, &tmp, type);
}

static void _Fill(
    Field* self,
    MI_Type type,
    MI_Uint8 x)
{
    memset(self, x, FieldSizeOf(type));
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

MI_Result Field_Construct(
    Field* self,
    MI_Type type,
    const MI_Value* value,
    MI_Uint32 flags,
    Batch* batch)
{
    MI_Result r;

    /* Zero out self */
    _Fill(self, type, 0);

    /* Handle null case up front */
    if (flags & MI_FLAG_NULL)
        MI_RETURN(MI_RESULT_OK);

    /* Reject null values */
    /* ATTN: Tolerate this for now */
    if (!value)
        MI_RETURN(MI_RESULT_OK);

    switch (type)
    {
        case MI_BOOLEAN:
        {
            self->boolean.value = value->boolean;
            self->boolean.exists = MI_TRUE;
            break;
        }
        case MI_UINT8:
        {
            self->uint8.value = value->uint8;
            self->uint8.exists = MI_TRUE;
            break;
        }
        case MI_SINT8:
        {
            self->sint8.value = value->sint8;
            self->sint8.exists = MI_TRUE;
            break;
        }
        case MI_UINT16:
        {
            self->uint16.value = value->uint16;
            self->uint16.exists = MI_TRUE;
            break;
        }
        case MI_SINT16:
        {
            self->sint16.value = value->sint16;
            self->sint16.exists = MI_TRUE;
            break;
        }
        case MI_UINT32:
        {
            self->uint32.value = value->uint32;
            self->uint32.exists = MI_TRUE;
            printf("Field Construct %d\n", value->uint32);
            printf("Exists address %p\n", (void*)&(self->uint32.exists));
            break;
        }
        case MI_SINT32:
        {
            self->sint32.value = value->sint32;
            self->sint32.exists = MI_TRUE;
            break;
        }
        case MI_UINT64:
        {
            self->uint64.value = value->uint64;
            self->uint64.exists = MI_TRUE;
            break;
        }
        case MI_SINT64:
        {
            self->sint64.value = value->sint64;
            self->sint64.exists = MI_TRUE;
            break;
        }
        case MI_REAL32:
        {
            self->real32.value = value->real32;
            self->real32.exists = MI_TRUE;
            break;
        }
        case MI_REAL64:
        {
            self->real64.value = value->real64;
            self->real64.exists = MI_TRUE;
            break;
        }
        case MI_CHAR16:
        {
            self->char16.value = value->char16;
            self->char16.exists = MI_TRUE;
            break;
        }
        case MI_DATETIME:
        {
            self->datetime.value = value->datetime;
            self->datetime.exists = MI_TRUE;
            break;
        }
        case MI_STRING:
        {
            if (value->string)
            {
                ZChar* str;

                if (flags & MI_FLAG_BORROW)
                {
                    self->string.value = value->string;
                    self->string.exists = MI_TRUE;
                    self->string.flags = _BORROW;
                    break;
                }

                str = BStrdup(batch, value->string, CALLSITE);
                if (!str)
                    MI_RETURN(MI_RESULT_FAILED);

                self->string.value = str;
                self->string.exists = MI_TRUE;
            }
            else
            {
                self->string.value = NULL;
                self->string.exists = MI_FALSE;
                self->string.flags = 0;
            }
            break;
        }
        case MI_INSTANCE:
        case MI_REFERENCE:
        {
            if (value->instance)
            {
                MI_Instance* instance;

                if (flags & MI_FLAG_BORROW)
                {
                    self->instance.value = value->instance;
                    self->instance.exists = MI_TRUE;
                    self->instance.flags = _BORROW;
                    break;
                }

                r = Instance_Clone(value->instance, &instance, batch);
                if (r != MI_RESULT_OK)
                    MI_RETURN(r);

                self->instance.value = instance;
                self->instance.exists = MI_TRUE;
            }
            else
            {
                self->instance.value = NULL;
                self->instance.exists = MI_FALSE;
                self->instance.flags = 0;
            }
            break;
        }
        case MI_BOOLEANA:
        case MI_UINT8A:
        case MI_SINT8A:
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_REAL32A:
        case MI_REAL64A:
        case MI_CHAR16A:
        case MI_DATETIMEA:
        {
            if (value->array.data)
            {
                void* data;

                if (flags & MI_FLAG_BORROW)
                {
                    self->array.value = value->array;
                    self->array.exists = MI_TRUE;
                    self->array.flags = _BORROW;;
                    break;
                }

                data = _CloneSimpleArray(
                    value->array.data, value->array.size, type, batch);

                if ((value->array.size != 0) && !data)
                    MI_RETURN(MI_RESULT_FAILED);

                self->array.value.data = data;
                self->array.value.size = value->array.size;
                self->array.exists = MI_TRUE;
            }
            else
            {
                self->array.value.data = NULL;
                self->array.value.size = 0;
                self->array.exists = MI_TRUE;
            }
            break;
        }
        case MI_STRINGA:
        {
            ZChar** data;

            if (value->array.data)
            {
                if (flags & MI_FLAG_BORROW)
                {
                    self->stringa.value = value->stringa;
                    self->stringa.exists = MI_TRUE;
                    self->stringa.flags = _BORROW;;
                    break;
                }

                data = CloneStringArray((const ZChar**)value->stringa.data,
                    value->stringa.size, batch);
                if (!data)
                    MI_RETURN(MI_RESULT_FAILED);

                self->stringa.value.data = data;
                self->stringa.value.size = value->array.size;
                self->stringa.exists = MI_TRUE;
            }
            else
            {
                self->stringa.value.data = NULL;
                self->stringa.value.size = 0;
                self->stringa.exists = MI_TRUE;
            }
            break;
        }
        case MI_INSTANCEA:
        case MI_REFERENCEA:
        {
            if (value->instancea.data)
            {
                MI_Instance** data;

                if (flags & MI_FLAG_BORROW)
                {
                    self->instancea.value = value->instancea;
                    self->instancea.exists = MI_TRUE;
                    self->instancea.flags = _BORROW;;
                    break;
                }

                data = _CloneInstanceArray(value->instancea.data,
                    value->instancea.size, batch);
                if (!data)
                    MI_RETURN(MI_RESULT_FAILED);

                self->instancea.value.data = data;
                self->instancea.value.size = value->array.size;
                self->instancea.exists = MI_TRUE;
            }
            else
            {
                self->instancea.value.data = NULL;
                self->instancea.value.size = 0;
                self->instancea.exists = MI_TRUE;
            }
            break;
        }
    }

    return MI_RESULT_OK;
}

void Field_Destruct(
    Field* self,
    MI_Type type,
    Batch* batch)
{
    switch (type)
    {
        case MI_STRING:
        {
            MI_StringField* f = &self->string;

            if (!(f->flags & _BORROW) && f->value)
                BFree(batch, f->value, CALLSITE);
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
        case MI_STRINGA:
        {
            MI_ArrayField* f = &self->array;

            if (!(f->flags & _BORROW) && f->value.data)
                BFree(batch, f->value.data, CALLSITE);
            break;
        }
        case MI_INSTANCE:
        case MI_REFERENCE:
        {
            MI_InstanceField* f = &self->instance;

            if (!(f->flags & _BORROW) && f->value)
                MI_Instance_Delete(f->value);
            break;
        }
        case MI_INSTANCEA:
        case MI_REFERENCEA:
        {
            MI_InstanceAField* f = &self->instancea;

            if (!(f->flags & _BORROW) && f->value.data)
            {
                MI_Uint32 j;

                for (j = 0; j < f->value.size; j++ )
                    MI_Instance_Delete(f->value.data[j]);

                BFree(batch, f->value.data, CALLSITE);
            }
            break;
        }
        default:
            break;
    }

    /* Fill with illegal character */
    _Fill(self, type, 0xDD);
}

MI_Result Field_Set(
    Field* self,
    MI_Type type,
    const MI_Value* value,
    MI_Uint32 flags,
    Batch* batch)
{
    Field field;
    MI_Result r;

    /* Initialize new field */
    r = Field_Construct(&field, type, value, flags, batch);
    if (r != MI_RESULT_OK)
        MI_RETURN(r);

    /* Destroy self */
    Field_Destruct(self, type, batch);

    /* Swap new field with self */
    _Swap(self, &field, type);

    return MI_RESULT_OK;
}

MI_Result Field_Copy(
    Field* self,
    MI_Type type,
    const Field* field,
    Batch* batch)
{
    MI_Value value;
    MI_Boolean exists;
    MI_Uint8 flags;
    MI_Uint32 tflags = 0;
    MI_Result r;

    Field_Extract(field, type, &value, &exists, &flags);

    if (!exists)
        tflags |= MI_FLAG_NULL;

    r = Field_Construct(self, type, &value, tflags, batch);

    return r;
}

void Field_Clear(
    Field* self,
    MI_Type type,
    Batch* batch)
{
    Field_Destruct(self, type, batch);
    _Fill(self, type, 0);
}

void Field_Extract(
    const Field* self,
    MI_Type type,
    MI_Value* valueOut,
    MI_Boolean* existsOut,
    MI_Uint8* flagsOut)
{
    size_t size = Type_SizeOf(type);
    memcpy(valueOut, self, size);
    *existsOut = *(MI_Boolean*)((const char*)self + size);
    *flagsOut = *(MI_Uint8*)((const char*)self + size + sizeof(MI_Boolean));
}

static MI_Boolean _MatchDatetime(
    const MI_Datetime* x,
    const MI_Datetime* y)
{
    if (x->isTimestamp)
    {
        if (!y->isTimestamp)
            return MI_FALSE;

        return
            x->u.timestamp.year == y->u.timestamp.year &&
            x->u.timestamp.month == y->u.timestamp.month &&
            x->u.timestamp.day == y->u.timestamp.day &&
            x->u.timestamp.hour == y->u.timestamp.hour &&
            x->u.timestamp.minute == y->u.timestamp.minute &&
            x->u.timestamp.second == y->u.timestamp.second &&
            x->u.timestamp.microseconds == y->u.timestamp.microseconds &&
            x->u.timestamp.utc == y->u.timestamp.utc;
    }
    else
    {
        if (y->isTimestamp)
            return MI_FALSE;

        return
            x->u.interval.days == y->u.interval.days &&
            x->u.interval.hours == y->u.interval.hours &&
            x->u.interval.minutes == y->u.interval.minutes &&
            x->u.interval.seconds == y->u.interval.seconds &&
            x->u.interval.microseconds == y->u.interval.microseconds;
    }
}

MI_Boolean Field_MatchKey(
    const Field* f1,
    const Field* f2,
    MI_Type type)
{
    MI_Boolean e1 = Field_GetExists(f1, type);
    MI_Boolean e2 = Field_GetExists(f2, type);
    int f = MI_FALSE;

    if ((e1 && !e2) || (e2 && !e1))
        return MI_FALSE;

    switch (type)
    {
        case MI_BOOLEAN:
            f = f1->boolean.value == f2->boolean.value;
            break;
        case MI_UINT8:
            f = f1->uint8.value == f2->uint8.value;
            break;
        case MI_SINT8:
            f = f1->sint8.value == f2->sint8.value;
            break;
        case MI_UINT16:
            f = f1->uint16.value == f2->uint16.value;
            break;
        case MI_SINT16:
            f = f1->sint16.value == f2->sint16.value;
            break;
        case MI_UINT32:
            f = f1->uint32.value == f2->uint32.value;
            break;
        case MI_SINT32:
            f = f1->sint32.value == f2->sint32.value;
            break;
        case MI_UINT64:
            f = f1->uint64.value == f2->uint64.value;
            break;
        case MI_SINT64:
            f = f1->sint64.value == f2->sint64.value;
            break;
        case MI_REAL32:
            f = f1->real32.value == f2->real32.value;
            break;
        case MI_REAL64:
            f = f1->real64.value == f2->real64.value;
            break;
        case MI_CHAR16:
            f = f1->char16.value == f2->char16.value;
            break;
        case MI_DATETIME:
            f = _MatchDatetime(&f1->datetime.value, &f2->datetime.value);
            break;
        case MI_STRING:
            f = Tcscmp(f1->string.value, f2->string.value) == 0;
            break;
        case MI_REFERENCE:
        {
            if (!f1->reference.value && !f2->reference.value)
                return MI_TRUE;

            f = Instance_MatchKeys(f1->reference.value, f2->reference.value);
            break;
        }
        case MI_INSTANCE:
            /* Instances cannot be keys */
            f = MI_FALSE;
            break;
        default:
            /* Arrays cannot be keys */
            f = MI_FALSE;
            break;
    }

    return f ? MI_TRUE : MI_FALSE;
}
