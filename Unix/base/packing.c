/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "packing.h"
#include "naming.h"
#include <pal/format.h>

/** Magic number for MI_Instance objects (binary buffer pack/unpack) */
#define INSTANCE_MAGIC ((MI_Uint32)0x462b9957)

/* The magic number that occurs at the end of an instance serialization */
static const MI_Uint32 _END_MAGIC = 0x76f474e3;

MI_INLINE void* _Alloc(Batch* batch, size_t size)
{
    return batch ?  Batch_Get(batch, size) : PAL_Malloc(size);
}

static MI_Result _PackField(Buf* buf, const void* field, MI_Type type)
{
    switch (type)
    {
        case MI_BOOLEAN:
        case MI_SINT8:
        case MI_UINT8:
        {
            MI_Uint8Field* f = (MI_Uint8Field*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Buf_PackU8(buf, f->value));
            break;
        }
        case MI_SINT16:
        case MI_UINT16:
        case MI_CHAR16:
        {
            MI_Uint16Field* f = (MI_Uint16Field*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Buf_PackU16(buf, f->value));
            break;
        }
        case MI_SINT32:
        case MI_UINT32:
        case MI_REAL32:
        {
            MI_Uint32Field* f = (MI_Uint32Field*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Buf_PackU32(buf, f->value));
            break;
        }
        case MI_SINT64:
        case MI_UINT64:
        case MI_REAL64:
        {
            MI_Uint64Field* f = (MI_Uint64Field*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Buf_PackU64(buf, f->value));
            break;
        }
        case MI_DATETIME:
        {
            MI_DatetimeField* f = (MI_DatetimeField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                Buf_PackDT(buf, &f->value);
            break;
        }
        case MI_STRING:
        {
            MI_StringField* f = (MI_StringField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Buf_PackStr(buf, f->value));
            break;
        }
        case MI_INSTANCE:
        case MI_REFERENCE:
        {
            MI_InstanceField* f = ((MI_InstanceField*)field);

            if (f->exists && !f->value)
                MI_RETURN(MI_RESULT_FAILED);

            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
                MI_RETURN_ERR(Instance_Pack(f->value, type == MI_REFERENCE, 
                    NULL, NULL, buf));

            break;
        }
        case MI_BOOLEANA:
        case MI_SINT8A:
        case MI_UINT8A:
        {
            MI_Uint8AField* f = (MI_Uint8AField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                if (!f->value.data && f->value.size)
                    MI_RETURN(MI_RESULT_FAILED);

                MI_RETURN_ERR(Buf_PackU8A(buf, f->value.data, 
                    f->value.size));
            }
            break;
        }
        case MI_SINT16A:
        case MI_UINT16A:
        case MI_CHAR16A:
        {
            MI_Uint16AField* f = (MI_Uint16AField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                if (!f->value.data && f->value.size)
                    MI_RETURN(MI_RESULT_FAILED);

                MI_RETURN_ERR(Buf_PackU16A(buf, f->value.data, 
                    f->value.size));
            }
            break;
        }
        case MI_SINT32A:
        case MI_UINT32A:
        case MI_REAL32A:
        {
            MI_Uint32AField* f = (MI_Uint32AField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                if (!f->value.data && f->value.size)
                    MI_RETURN(MI_RESULT_FAILED);

                MI_RETURN_ERR(Buf_PackU32A(buf, f->value.data, 
                    f->value.size));
            }
            break;
        }
        case MI_SINT64A:
        case MI_UINT64A:
        case MI_REAL64A:
        {
            MI_Uint64AField* f = (MI_Uint64AField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                if (!f->value.data && f->value.size)
                    MI_RETURN(MI_RESULT_FAILED);

                MI_RETURN_ERR(Buf_PackU64A(buf, f->value.data, 
                    f->value.size));
            }
            break;
        }
        case MI_DATETIMEA:
        {
            MI_DatetimeAField* f = (MI_DatetimeAField*)field;
            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                if (!f->value.data && f->value.size)
                    MI_RETURN(MI_RESULT_FAILED);

                MI_RETURN_ERR(Buf_PackDTA(buf, f->value.data,
                    f->value.size));
            }
            break;
        }
        case MI_STRINGA:
        {
            MI_StringAField* f = (MI_StringAField*)field;

            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                MI_RETURN_ERR(Buf_PackStrA(buf, 
                    (const ZChar**)f->value.data, f->value.size));
            }
            break;
        }
        case MI_INSTANCEA:
        case MI_REFERENCEA:
        {
            MI_InstanceAField* f = ((MI_InstanceAField*)field);

            MI_RETURN_ERR(Buf_PackU8(buf, f->exists));

            if (f->exists)
            {
                MI_Uint32 index;
                MI_RETURN_ERR(Buf_PackU32(buf, f->value.size));

                for ( index = 0; index < f->value.size; index++ )
                {
                    MI_RETURN_ERR(Instance_Pack(f->value.data[index], 
                        type == MI_REFERENCEA, NULL, NULL, buf));
                }
            }
            break;
        }
        default:
            break;
    }

    MI_RETURN(MI_RESULT_OK);
}

static MI_Result _UnpackField(
    Buf* buf, 
    MI_Value* value,
    MI_Boolean* exists,
    MI_Type type,
    Batch* batch,
    MI_Boolean copy)
{
    /* Get exists flag */
    MI_RETURN_ERR(Buf_UnpackU8(buf, exists));

    if (!*exists)
    {
        memset(value, 0, sizeof(MI_Value));
        MI_RETURN(MI_RESULT_OK);
    }

    /* Get value */
    switch (type)
    {
        case MI_UINT8:
        case MI_SINT8:
        case MI_BOOLEAN:
        {
            MI_RETURN_ERR(Buf_UnpackU8(buf, &value->uint8));
            break;
        }
        case MI_UINT16:
        case MI_SINT16:
        case MI_CHAR16:
        {
            MI_RETURN_ERR(Buf_UnpackU16(buf, &value->uint16));
            break;
        }
        case MI_UINT32:
        case MI_SINT32:
        case MI_REAL32:
        {
            MI_RETURN_ERR(Buf_UnpackU32(buf, &value->uint32));
            break;
        }
        case MI_UINT64:
        case MI_SINT64:
        case MI_REAL64:
        {
            MI_RETURN_ERR(Buf_UnpackU64(buf, &value->uint64));
            break;
        }
        case MI_DATETIME:
        {
            MI_RETURN_ERR(Buf_UnpackDT(buf, &value->datetime));
            break;
        }
        case MI_STRING:
        {
            MI_RETURN_ERR(Buf_UnpackStr(
                buf, (const ZChar**)&value->string));

            break;
        }
        case MI_REFERENCE:
        case MI_INSTANCE:
        {
            MI_RETURN(Instance_Unpack((MI_Instance**)&value->instance, buf, batch, copy));
            break;
        }
        case MI_BOOLEANA:
        case MI_UINT8A:
        case MI_SINT8A:
        {
            MI_RETURN_ERR(Buf_UnpackU8A(buf, 
                (const MI_Uint8**)&value->uint8a.data, &value->uint8a.size));
            break;
        }
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_CHAR16A:
        {
            MI_RETURN_ERR(Buf_UnpackU16A(buf, 
                (const MI_Uint16**)&value->uint16a.data, &value->uint16a.size));
            break;
        }
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_REAL32A:
        {
            MI_RETURN_ERR(Buf_UnpackU32A(buf, 
                (const MI_Uint32**)&value->uint32a.data, &value->uint32a.size));
            break;
        }
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_REAL64A:
        {
            MI_RETURN_ERR(Buf_UnpackU64A(buf, 
                (const MI_Uint64**)&value->uint64a.data, &value->uint64a.size));
            break;
        }
        case MI_DATETIMEA:
        {
            MI_RETURN_ERR(Buf_UnpackDTA(buf, 
                (const MI_Datetime**)&value->datetimea.data, 
                &value->datetimea.size));
            break;
        }
        case MI_STRINGA:
        {
            MI_RETURN_ERR(Buf_UnpackStrA(buf, 
                (const ZChar***)&value->stringa.data, &value->stringa.size));
            break;
        }
        case MI_INSTANCEA:
        case MI_REFERENCEA:
        {
            /* Unpack the size of the array */
            MI_RETURN_ERR(Buf_UnpackU32(buf, &value->instancea.size));

            if (!value->instancea.size)
            {
                value->instancea.data = 0;
            }
            else
            {
                MI_Uint32 index;

                value->instancea.data = (MI_Instance**)_Alloc(batch, 
                    sizeof(MI_Instance*) * value->instancea.size);

                index = 0;
                if (!value->instancea.data)
                {
                    MI_RETURN(MI_RESULT_FAILED);
                }

                for ( index = 0; index < value->instancea.size; index++ )
                {
                    MI_RETURN_ERR(Instance_Unpack(
                        &value->instancea.data[index], buf, batch, copy));
                }
            }
            break;
        }
    }

    MI_RETURN(MI_RESULT_OK);
}

MI_Result Instance_Pack(
    const MI_Instance* self_,
    MI_Boolean keysOnly,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    Buf* buf)
{
    Instance* self = Instance_GetSelf( self_ );
    MI_ClassDecl* cd;
    MI_Uint32 i;

    /* Check for null arguments */
    if (!self || !buf)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    cd = (MI_ClassDecl*)self->classDecl;
    
    /* Pack magic number */
    MI_RETURN_ERR(Buf_PackU32(buf, INSTANCE_MAGIC));

    /* Pack flags */
    MI_RETURN_ERR(Buf_PackU32(buf, cd->flags));

    /* Pack the classname */
    MI_RETURN_ERR(Buf_PackStrLen(buf, cd->name, NameLen(cd->name, cd->code)));

    /* namespace */
    MI_RETURN_ERR(Buf_PackStr(buf, self->nameSpace));

    /* Pack the properties */
    if (keysOnly)
    {
        /* adjust number of properties based on Keys number */
        MI_Uint32 keysNum = 0;

        for (i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];

            if (pd->flags & MI_FLAG_KEY)
                keysNum++;
        }

        MI_RETURN_ERR(Buf_PackU32(buf, keysNum));
    }
    else if (filterProperty)
    {
        /* Pack the number of unfiltered properties */
        MI_Uint32 n = 0;

        for (i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];

            if ((*filterProperty)(pd->name, filterPropertyData))
                continue;

            n++;
        }

        MI_RETURN_ERR(Buf_PackU32(buf, n));
    }
    else
    {
        MI_RETURN_ERR(Buf_PackU32(buf, cd->numProperties));
    }

    for (i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];
        const void* value = (char*)self + pd->offset;
        MI_Char* pName;

        /* Skip non-key properties (for references) */
        if (keysOnly && (pd->flags & MI_FLAG_KEY) == 0)
            continue;

        /* Skip filtered properties */
        if (filterProperty && 
            (*filterProperty)(pd->name, filterPropertyData))
        {
            continue;
        }

        /* Pack the flags */
        MI_RETURN_ERR(Buf_PackU32(buf, pd->flags));

        pName = pd->name;
        if ((pd->flags & MI_FLAG_PARAMETER) && (pd->flags & MI_FLAG_OUT))
        {
            if (pName && pName[0] == ZT('M') && Tcscmp(pName, ZT("MIReturn"))== 0)
                pName = ZT("ReturnValue");
        }

        /* Pack the propety name */
        MI_RETURN_ERR(Buf_PackStrLen(
            buf, pName, NameLen(pName, pd->code)));

        /* Pack the propety type */
        MI_RETURN_ERR(Buf_PackU32(buf, pd->type));

        /* Pack the value */
        MI_RETURN_ERR(_PackField(buf, value, (MI_Type)pd->type));
    }

    /* Pack ending magic number */
    MI_RETURN_ERR(Buf_PackU32(buf, _END_MAGIC));

    MI_RETURN(MI_RESULT_OK);
}

MI_Result Instance_Unpack(
    MI_Instance** selfOut,
    Buf* buf,
    Batch* batch,
    MI_Boolean copy)
{
    MI_Uint32 magic;
    MI_Uint32 flags;
    const ZChar* className;
    const ZChar* nameSpace = 0;
    MI_Instance* self;

    /* Check parameters */
    if (!selfOut || !buf)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Clear output parameter */
    *selfOut = NULL;

    /* Unpack magic number */
    MI_RETURN_ERR(Buf_UnpackU32(buf, &magic));

    if (INSTANCE_MAGIC != magic)
        MI_RETURN(MI_RESULT_FAILED);

    /* Unpack flags */
    MI_RETURN_ERR(Buf_UnpackU32(buf, &flags));

    /* Unpack the class name */
    MI_RETURN_ERR(Buf_UnpackStr(buf, &className));

    /* Unpack the namespace */
    MI_RETURN_ERR(Buf_UnpackStr(buf, &nameSpace));

    /* Unpack properties */
    {
        MI_Uint32 numProperties;
        MI_Uint32 i;

        MI_RETURN_ERR(Buf_UnpackU32(buf, &numProperties));

        /* ATTN-B: prevent copying of className and superClass strings */
        /* Create dynamic instance */
        MI_RETURN_ERR(Instance_NewDynamic(&self, className, flags, batch));

        MI_RETURN_ERR(MI_Instance_SetNameSpace(self, nameSpace));

        for (i = 0; i < numProperties; i++)
        {
            const ZChar* name;
            MI_Uint32 type, prop_flags;
            MI_Value value;
            const MI_Value* valuePtr;
            MI_Boolean exists;

            /* ATTN-B: prevent copying of name by Instance_Add */
            /* Unpack the propety type */
            MI_RETURN_ERR(Buf_UnpackU32(buf, &prop_flags));

            /* Unpack the propety name */
            MI_RETURN_ERR(Buf_UnpackStr(buf, &name));

            /* Unpack the propety type */
            MI_RETURN_ERR(Buf_UnpackU32(buf, &type));

            /* Unpack the value */
            MI_RETURN_ERR(_UnpackField(buf, &value, &exists, (MI_Type)type, 
                batch, copy));

            /* Set valuePtr */
            if (exists)
                valuePtr = &value;
            else
                valuePtr = NULL;

            /* ATTN-A: Handle prop_flags and className parameters */
            /* Add the property to the instance */

            if (!copy)
                prop_flags |= MI_FLAG_BORROW;

            MI_RETURN_ERR(MI_Instance_AddElement(self, name, valuePtr, 
                (MI_Type)type, prop_flags));
        }
    }

    /* Check the ending magic number */
    {
        MI_Uint32 endMagic;
        MI_RETURN_ERR(Buf_UnpackU32(buf, &endMagic));

        if (endMagic != _END_MAGIC)
            MI_RETURN(MI_RESULT_INVALID_PARAMETER);
    }

    /* Set output parameter */
    *selfOut = self;

    /* ATTN-A: if batch is non-null, then attach buffer to batch */
    MI_RETURN(MI_RESULT_OK);
}

MI_Result InstanceToBatch(
    const MI_Instance* instance,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    Batch* batch,
    void** ptrOut,
    MI_Uint32* sizeOut)
{
    Buf buf;
    MI_Result r;
    Page* page;

    r = Buf_Init(&buf, 16*1024);

    if (MI_RESULT_OK != r)
        return r;

    r = Instance_Pack(
        instance, MI_FALSE, filterProperty, filterPropertyData, &buf);

    if (MI_RESULT_OK != r)
    {
        Buf_Destroy(&buf);
        return r;
    }

    page = Buf_StealPage(&buf);
    page->u.s.size = buf.size;

    Batch_AttachPage(batch, page);

    *ptrOut = page + 1;
    *sizeOut = (MI_Uint32)page->u.s.size;
    return MI_RESULT_OK;
}
