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

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <base/instance.h>
#include "instance.h"
#include <base/miextras.h>

MI_BEGIN_NAMESPACE

Instance::Instance(
    const MI_ClassDecl* clDecl)
{
    m_instance = Create(clDecl);
    AddRef(m_instance);
}

Instance::Instance(
    const MI_MethodDecl* methodDecl)
{
    const MI_ClassDecl* clDecl = 
        reinterpret_cast<const MI_ClassDecl*>(methodDecl);
    m_instance = Create(clDecl);
    AddRef(m_instance);
}

// returns new instance
MI_Instance* Instance::Create(const MI_ClassDecl* clDecl)
{
    size_t instance_size = sizeof(Header) + clDecl->size;
    Header* chunk = reinterpret_cast<Header*>(operator new(instance_size));

    // init
    memset(chunk,0,instance_size);

    chunk++;

    ((MI_Instance*)chunk)->classDecl = clDecl;
    return reinterpret_cast<MI_Instance*>(chunk);
}

void Instance::Initialize(
    const MI_ClassDecl* clDecl, 
    const MI_Instance* instance, 
    bool keysOnly)
{
    MI_Instance* chunk = Create(clDecl);
    m_instance = 0;

    AddRef(chunk);

    if (NULL == instance)
    {
        m_instance = chunk;
        return ; 
    }

    // copy relevant data
    memcpy(chunk, instance, clDecl->size);

    // Set the class decl:
    chunk->classDecl = clDecl;

    // Clear reserved part.
    chunk->reserved[0] = 0;
    chunk->reserved[1] = 0;
    chunk->reserved[2] = 0;
    chunk->reserved[3] = 0;

    // namespace
    new(&((MI_Instance*)chunk)->nameSpace) String(
        ((MI_Instance*)instance)->nameSpace);
    
    // some types require extra care (arrays, strings, refs)

    for (size_t i = 0; i < clDecl->numProperties; i++)
    {
        MI_Uint32 offset = clDecl->properties[i]->offset;
        char* p = (char*)chunk + offset;
        const char* q = (const char*)instance + offset;

        switch(clDecl->properties[i]->type)
        {
            case MI_BOOLEAN:
            case MI_UINT8:
            case MI_SINT8:
            case MI_UINT16:
            case MI_SINT16:
            case MI_UINT32:
            case MI_SINT32:
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL32:
            case MI_REAL64:
            case MI_CHAR16:
            case MI_DATETIME:
                break;  // nothing to do

            case MI_STRING:
            {
                // copy string from instance to the dest
                new(p) String(*(const MI_Char**)(q));
                break;
            }
            case MI_REFERENCE:
            case MI_INSTANCE:
            {
                const MI_Instance* ref = *(const MI_Instance**)(q);

                if (ref)
                {
                    // copy instance from 'c' instance pointer
                    new(p) Instance(((MI_Instance*)ref)->classDecl, ref,
                        keysOnly);
                }
                break;
            }
            case MI_BOOLEANA :
            case MI_UINT8A :
            case MI_SINT8A :
            {
                const MI_BooleanA * item = (const MI_BooleanA*)(q);
                new(p) BooleanA(item->data, item->size);
                break;
            }
            case MI_UINT16A :
            case MI_SINT16A :
            case MI_CHAR16A :
            {
                const MI_Uint16A * item = (const MI_Uint16A*)(q);
                new(p) Uint16A(item->data, item->size);
                break;
            }

            case MI_UINT32A :
            case MI_SINT32A :
            case MI_REAL32A :
            {
                const MI_Uint32A * item = (const MI_Uint32A*)(q);
                new(p) Uint32A(item->data, item->size);
                break;
            }
            case MI_UINT64A :
            case MI_SINT64A :
            case MI_REAL64A :
            {
                const MI_Uint64A * item = (const MI_Uint64A*)(q);
                new(p) Uint64A(item->data, item->size);
                break;
            }
            case MI_STRINGA :
            {
                const MI_StringA * item = (const MI_StringA*)(q);
                new(p) StringA();

                reinterpret_cast<StringA*>(p)->Resize(item->size);

                for(Uint32 counter = 0; counter < item->size; counter++)
                {
                    reinterpret_cast<StringA*>(p)->operator[](counter) 
                        = String(item->data[counter]);
                }
                break;
            }
            case MI_DATETIMEA :
            {
                const MI_DatetimeA* item = (const MI_DatetimeA*)(q);
                new(p) DatetimeA((const Datetime*)item->data, item->size);
                break;
            }
            case MI_REFERENCEA :
            case MI_INSTANCEA :
            {
                const MI_InstanceA * item = (const MI_InstanceA*)(q);
                new(p) InstanceA();
                reinterpret_cast<InstanceA*>(p)->Resize(item->size);

                for(Uint32 counter = 0; counter < item->size; counter++)
                {
                    reinterpret_cast<InstanceA*>(p)->operator[](counter) =
                        Instance(((MI_Instance*)item->data[counter])->
                        classDecl, item->data[counter], false);
                }
                break;
            }
            default:
                assert(0);  // want to find it!
        }
    }

    m_instance = chunk; 
}

Instance::Instance(
    const MI_ClassDecl* clDecl, 
    const MI_Instance* instance, 
    bool keysOnly)
{
    Initialize(clDecl, instance, keysOnly);
}

Instance::Instance(
    const MI_MethodDecl* methodDecl, 
    const MI_Instance* instance, 
    bool keysOnly)
{
    const MI_ClassDecl* clDecl = 
        reinterpret_cast<const MI_ClassDecl*>(methodDecl);
    Initialize(clDecl, instance, keysOnly);
}

MI_Instance* Instance::Clone() const
{
    const MI_ClassDecl* clDecl = ((MI_Instance*)m_instance)->classDecl;
    MI_Instance* new_inst = Create(clDecl);

    // most of the data can be copied from 'this'
    memcpy(new_inst, m_instance, clDecl->size);

    new(&((MI_Instance*)new_inst)->nameSpace) String(
        *((const String*)(&((MI_Instance*)m_instance)->nameSpace)));

    char* inst_start = ((char*)new_inst);

    for (size_t i = 0; i < clDecl->numProperties; i++)
    {
        MI_Uint32 offset = clDecl->properties[i]->offset;
        char* p = inst_start + offset;
        const char* q = (((const char*)m_instance) + offset);

        switch(clDecl->properties[i]->type)
        {
            case MI_BOOLEAN:
            case MI_UINT8:
            case MI_SINT8:
            case MI_UINT16:
            case MI_SINT16:
            case MI_UINT32:
            case MI_SINT32:
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL32:
            case MI_REAL64:
            case MI_CHAR16:
            case MI_DATETIME:
                break;  // nothing to do
            case MI_STRING:
            {
                // copy string from instance to the dest
                new(p) String(*(const String*)(q));
                break;
            }
            case MI_REFERENCE:
            case MI_INSTANCE:
            {
                // copy instance from 'c' instance pointer
                MI_Instance* ref = *(MI_Instance**)(q);
                if (ref)
                    AddRef(ref);
                break;
            }
            case MI_BOOLEANA :
            case MI_UINT8A :
            case MI_SINT8A :
                new(p) BooleanA(*(const BooleanA*)(q));
                break;

            case MI_UINT16A :
            case MI_SINT16A :
            case MI_CHAR16A :
                new(p) Uint16A(*(const Uint16A*)(q));
                break;

            case MI_UINT32A :
            case MI_SINT32A :
            case MI_REAL32A :
                new(p) Uint32A(*(const Uint32A*)q);
                break;

            case MI_UINT64A :
            case MI_SINT64A :
            case MI_REAL64A :
                new(p) Uint64A(*(const Uint64A*)(q));
                break;

            case MI_STRINGA :
                new(p) StringA(*(const StringA*)(q));
                break;

            case MI_DATETIMEA :
                new(p) DatetimeA(*(const DatetimeA*)(q));
                break;

            case MI_REFERENCEA :
            case MI_INSTANCEA :
                new(p) InstanceA(*(const InstanceA*)(q));
                break;

            default:
                assert(0);  // want to find it!
        }
    }

    return new_inst;
}

void Instance::Release(MI_Instance* instance)
{
    if (instance && AtomicDec(GetHeader(instance)->u.s.m_refCounter))
    {
        const MI_ClassDecl* clDecl = ((MI_Instance*)instance)->classDecl;

        // namespace
        ((const String*)(&((MI_Instance*)instance)->nameSpace))->~String();

        // destroy objects!!!
        char* inst_start = ((char*)(instance));

        for (size_t i = 0; i < clDecl->numProperties; i++)
        {
            char* p = inst_start + clDecl->properties[i]->offset;

            switch(clDecl->properties[i]->type)
            {
                case MI_BOOLEAN:
                case MI_UINT8:
                case MI_SINT8:
                case MI_UINT16:
                case MI_SINT16:
                case MI_UINT32:
                case MI_SINT32:
                case MI_UINT64:
                case MI_SINT64:
                case MI_REAL32:
                case MI_REAL64:
                case MI_CHAR16:
                case MI_DATETIME:
                    break;  // nothing to do

                case MI_STRING:
                    // copy string from instance to the dest
                    reinterpret_cast<String*>(p)->~String();
                    break;
        
                case MI_REFERENCE:
                case MI_INSTANCE:
                    reinterpret_cast<Instance*>(p)->~Instance();
                    break;

                case MI_BOOLEANA :
                case MI_UINT8A :
                case MI_SINT8A :
                    reinterpret_cast<BooleanA*>(p)->~BooleanA();
                    break;

                case MI_UINT16A :
                case MI_SINT16A :
                case MI_CHAR16A :
                    reinterpret_cast<Uint16A*>(p)->~Uint16A();
                    break;

                case MI_UINT32A :
                case MI_SINT32A :
                case MI_REAL32A :
                    reinterpret_cast<Uint32A*>(p)->~Uint32A();
                    break;

                case MI_UINT64A :
                case MI_SINT64A :
                case MI_REAL64A :
                    reinterpret_cast<Uint64A*>(p)->~Uint64A();
                    break;

                case MI_STRINGA :
                    reinterpret_cast<StringA*>(p)->~StringA();
                    break;

                case MI_DATETIMEA :
                    reinterpret_cast<DatetimeA*>(p)->~DatetimeA();
                    break;

                case MI_REFERENCEA :
                case MI_INSTANCEA :
                    reinterpret_cast<InstanceA*>(p)->~InstanceA();
                    break;

                default:
                    assert(0);  // want to find it!
            }
        }

        operator delete(GetHeader(instance));
    }
}

// namespace support
String  Instance::GetNamespace() const
{
   return *((const String*)(&((MI_Instance*)m_instance)->nameSpace));
}

void  Instance::SetNamespace(const String& ns)
{
    *((String*)(&((MI_Instance*)m_instance)->nameSpace)) = ns;
}

void Instance::CopyRef(
    const Instance& x)
{
    if (x.m_instance != m_instance)
    {
        Release(m_instance);

        m_instance = x.m_instance;

        if (m_instance)
            AddRef(m_instance);
    }
}

void Instance::Print(FILE* os, MI_Uint32 level) const
{
    if (!m_instance)
        return;

    MI_Instance_Print(m_instance, os, level);
}

const MI_ClassDecl* Instance::GetClassDecl()
{
    static MI_ClassDecl _classDecl =
    {
        MI_FLAG_CLASS, /* flags */
        0, /* code */
        (MI_Char*)MI_T("Instance"), /* name */
        NULL, /* qualifiers */
        0, /* numQualifiers */
        NULL, /* properties */
        0, /* numProperties */
        sizeof(MI_Instance), /* size */
        NULL, /* superClass */
        NULL, /* superClassDecl */
        NULL, /* methods */
        0, /* numMethods */
        NULL, /* schema */
        NULL, /* functions */
    };

    return &_classDecl;
}

bool __IsA(const MI_ClassDecl* classDecl, const Instance* instance)
{
    if (classDecl == Instance::GetClassDecl())
        return true;

    if (!instance)
        return false;

    const MI_Instance* inst = instance->m_instance;

    for (const MI_ClassDecl *p = inst->classDecl; p; p = p->superClassDecl)
    {
        if (p == classDecl)
            return true;
    }

    return false;
}

MI_END_NAMESPACE
