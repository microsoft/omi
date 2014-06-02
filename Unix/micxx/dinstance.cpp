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

#include "dinstance.h"
#include <cctype>
#include <base/instance.h>
#include <pal/strings.h>
#include <base/naming.h>
#include <base/schemadecl.h>
#include <base/helpers.h>
#include <pal/format.h>

// ATTN: work on object size reduction of this module.

#define T MI_T

MI_BEGIN_NAMESPACE

static MI_Uint32 _FindPropertyDecl(
    const MI_ClassDecl* cd,
    const MI_Char* name)
{
    MI_PropertyDecl** start = cd->properties;
    MI_PropertyDecl** end = start + cd->numProperties;
    MI_PropertyDecl** p = start;
    MI_Uint32 code;

    code = Hash(name);

    while (p != end) 
    {
        if ((*p)->code == code && Tcscasecmp((*p)->name, name) == 0)
            return (MI_Uint32)(p - start);
        p++;
    }

    return (MI_Uint32)-1;
}

void DInstance::COW()
{
    DEBUG_ASSERT(m_self);
    InstanceHeader* h = ((InstanceHeader*)m_self) - 1;

    if (h->u.refs != 1)
    {
        MI_Instance* self = m_self;

//
// Suppressing a false-positive for 28931 - Unused assignment of variable 'r'
//
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28931)
#endif
    
        MI_Result r = MI_Instance_Clone(self, &m_self);
        DEBUG_ASSERT(r == MI_RESULT_OK);
        __MI_Instance_Unref(self);
        MI_UNUSED(r);

#ifdef _MSC_VER
#pragma prefast(pop)
#endif
    }
}

DInstance::DInstance(const String& className, DInstance::MetaType metaType)
{
    MI_Uint32 mt = 0;

    switch (metaType)
    {
        case CLASS:
            mt = MI_FLAG_CLASS;
            break;
        case ASSOCIATION:
            mt = MI_FLAG_ASSOCIATION;
            break;
        case INDICATION:
            mt = MI_FLAG_INDICATION;
            break;
        case METHOD:
            mt = MI_FLAG_METHOD;
            break;
    }

    MI_Result r = Instance_NewDynamic(&m_self, className.Str(), mt, 0);
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);
}

DInstance::DInstance()
{
    MI_Result r = Instance_NewDynamic(&m_self, MI_T("DInstance"), 
        MI_FLAG_CLASS, 0);
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);
}

DInstance::DInstance(const DInstance& a)
{
    __MI_Instance_Ref(m_self = a.m_self);
}

DInstance::~DInstance()
{
    if (m_self)
        __MI_Instance_Unref(m_self);
}

DInstance& DInstance::operator=(const DInstance& a)
{
    if (m_self != a.m_self)
    {
        __MI_Instance_Unref(m_self);
        __MI_Instance_Ref(m_self = a.m_self);
    }

    return *this;
}

void DInstance::Swap(DInstance& a)
{
    MI_Instance* tmp = m_self;
    m_self = a.m_self;
    a.m_self = tmp;
}

const MI_ClassDecl* DInstance::GetClassDecl() const
{
    return m_self->classDecl;
}

#if defined(GetClassName)
# undef GetClassName
#endif

String DInstance::GetClassName() const
{
    return String(m_self->classDecl->name);
}

void DInstance::SetClassName(const String& className)
{
    COW();
    MI_Result r = Instance_SetClassName(m_self, className.Str());
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);
}

String DInstance::GetNamespace() const
{
    const MI_Char* nameSpace = NULL;

//
// Suppressing a false-positive for 28931 - Unused assignment of variable 'r'
//
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28931)
#endif
    
    MI_Result r = MI_Instance_GetNameSpace(m_self, &nameSpace);
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);

#ifdef _MSC_VER
#pragma prefast(pop)
#endif

    return String(nameSpace);
}

void DInstance::SetNamespace(const String& nameSpace)
{
    COW();
    MI_Result r = MI_Instance_SetNameSpace(m_self, nameSpace.Str());
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);
}

Uint32 DInstance::Count() const
{
    return m_self->classDecl->numProperties;
}

Uint32 DInstance::Find(const String& name) const
{
    Uint32 i;
    Uint32 count = Count();

    for (i = 0; i < count; i++)
    {
        const MI_Char* tmpName = NULL;
        MI_Result r;
        r = MI_Instance_GetElementAt(m_self, i, &tmpName, NULL, NULL, NULL);

        if (r != MI_RESULT_OK)
            return (Uint32)-1;

        if (name == tmpName)
            return i;
    }

    return (Uint32)-1;
}

bool DInstance::GetType(Uint32 index, Type& type) const
{
    MI_Result r;
    r = MI_Instance_GetElementAt(m_self, index, NULL, NULL, &type, NULL);
    return r == MI_RESULT_OK ? true : false;
}

bool DInstance::GetName(Uint32 index, String& name) const
{
    MI_Result r;
    const MI_Char* tmpName = NULL;
    r = MI_Instance_GetElementAt(m_self, index, &tmpName, NULL, NULL, NULL);
    if (r != MI_RESULT_OK)
        return false;

    name = String(tmpName);
    return true;
}

bool DInstance::GetFlags(Uint32 index, Uint32& flags) const
{
    MI_Result r;
    r = MI_Instance_GetElementAt(m_self, index, NULL, NULL, NULL, &flags);
    return r == MI_RESULT_OK ? true : false;
}

bool DInstance::Clear(const String& name)
{
    COW();
    MI_Result r;
    r = MI_Instance_ClearElement(m_self, name.Str());
    return (r == MI_RESULT_OK) ? true : false;
}

void DInstance::Print(
    FILE* os, 
    MI_Uint32 level,
    bool showNulls) const
{
    MI_Result r = Instance_Print(m_self, os, level, 
        showNulls ? MI_TRUE : MI_FALSE, MI_FALSE);
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);
}

DInstance::DInstance(MI_Instance* self, DInstance::AdoptTag) : m_self(self)
{
    DEBUG_ASSERT(m_self != 0);
}

DInstance::DInstance(MI_Instance* self, DInstance::CloneTag)
{
    //
    // Suppressing a false-positive for 28931 - Unused assignment of variable 'r'
    //
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28931)
#endif

    MI_Result r = MI_Instance_Clone(self, &m_self);
    DEBUG_ASSERT(r == MI_RESULT_OK);
    MI_UNUSED(r);

#ifdef _MSC_VER
#pragma prefast(pop)
#endif
}

bool DInstance::AddValue(
    const String& name, 
    const MI_Value* value, 
    Type type,
    bool null,
    bool key)
{
    COW();
    MI_Result r;
    MI_Uint32 flags = 0;

    if (key)
        flags |= MI_FLAG_KEY;

    if (!value || null)
        flags |= MI_FLAG_NULL;

    r = MI_Instance_AddElement(m_self, name.Str(), value, type, flags);
    return r == MI_RESULT_OK ? true : false;
}

bool DInstance::SetValue(
    const String& name, 
    const MI_Value* value, 
    Type type,
    bool null)
{
    COW();
    MI_Result r;
    MI_Uint32 flags = 0;

    if (!value || null)
        flags |= MI_FLAG_NULL;

    r = MI_Instance_SetElement(m_self, name.Str(), value, type, flags);
    return r == MI_RESULT_OK ? true : false;
}

bool DInstance::GetValue(
    const String& name, 
    MI_Value* value, 
    Type& type,
    bool& null,
    bool& key) const
{
    if (!value)
        return false;

    MI_Uint32 f;
    MI_Result r;

    r = MI_Instance_GetElement(m_self, name.Str(), value, &type, &f, 0);

    if (r != MI_RESULT_OK)
        return false;

    key = (f & MI_FLAG_KEY) ? true : false;
    null = (f & MI_FLAG_NULL) ? true : false;

    return true;
}

bool DInstance::GetValueAsType(
    const String& name, 
    MI_Value* value, 
    Type expectedType,
    bool& null,
    bool& key) const
{
    MI_Type type;

    if (GetValue(name, value, type, null, key) != MI_RESULT_OK)
        return false;

    return type == expectedType;
}

bool DInstance::GetBoolean(
    const String& name, 
    Boolean& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_BOOLEAN, null, key) == MI_RESULT_OK)
    {
        a = Boolean(v.boolean);
        return true;
    }
    return false;
}

bool DInstance::GetBooleanA(
    const String& name, 
    BooleanA& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_BOOLEANA, null, key) == MI_RESULT_OK)
    {
        a = BooleanA((Boolean*)v.booleana.data, v.booleana.size);
        return true;
    }
    return false;
}

bool DInstance::GetUint8(
    const String& name, 
    Uint8& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT8, null, key) == MI_RESULT_OK)
    {
        a = Uint8(v.uint8);
        return true;
    }
    return false;
}

bool DInstance::GetUint8A(
    const String& name, 
    Uint8A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT8A, null, key) == MI_RESULT_OK)
    {
        a = Uint8A((Uint8*)v.uint8a.data, v.uint8a.size);
        return true;
    }
    return false;
}

bool DInstance::GetSint8(
    const String& name, 
    Sint8& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT8, null, key) == MI_RESULT_OK)
    {
        a = Sint8(v.sint8);
        return true;
    }
    return false;
}

bool DInstance::GetSint8A(
    const String& name, 
    Sint8A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT8A, null, key) == MI_RESULT_OK)
    {
        a = Sint8A((Sint8*)v.sint8a.data, v.sint8a.size);
        return true;
    }
    return false;
}

bool DInstance::GetUint16(
    const String& name, 
    Uint16& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT16, null, key) == MI_RESULT_OK)
    {
        a = Uint16(v.uint16);
        return true;
    }
    return false;
}

bool DInstance::GetUint16A(
    const String& name, 
    Uint16A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT16A, null, key) == MI_RESULT_OK)
    {
        a = Uint16A((Uint16*)v.uint16a.data, v.uint16a.size);
        return true;
    }
    return false;
}

bool DInstance::GetSint16(
    const String& name, 
    Sint16& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT16, null, key) == MI_RESULT_OK)
    {
        a = Sint16(v.sint16);
        return true;
    }
    return false;
}

bool DInstance::GetSint16A(
    const String& name, 
    Sint16A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT16A, null, key) == MI_RESULT_OK)
    {
        a = Sint16A((Sint16*)v.sint16a.data, v.sint16a.size);
        return true;
    }
    return false;
}

bool DInstance::GetUint32(
    const String& name, 
    Uint32& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT32, null, key) == MI_RESULT_OK)
    {
        a = Uint32(v.uint32);
        return true;
    }
    return false;
}

bool DInstance::GetUint32A(
    const String& name, 
    Uint32A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT32A, null, key) == MI_RESULT_OK)
    {
        a = Uint32A((Uint32*)v.uint32a.data, v.uint32a.size);
        return true;
    }
    return false;
}

bool DInstance::GetSint32(
    const String& name, 
    Sint32& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT32, null, key) == MI_RESULT_OK)
    {
        a = Sint32(v.sint32);
        return true;
    }
    return false;
}

bool DInstance::GetSint32A(
    const String& name, 
    Sint32A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT32A, null, key) == MI_RESULT_OK)
    {
        a = Sint32A((Sint32*)v.sint32a.data, v.sint32a.size);
        return true;
    }
    return false;
}

bool DInstance::GetUint64(
    const String& name, 
    Uint64& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT64, null, key) == MI_RESULT_OK)
    {
        a = Uint64(v.uint64);
        return true;
    }
    return false;
}

bool DInstance::GetUint64A(
    const String& name, 
    Uint64A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_UINT64A, null, key) == MI_RESULT_OK)
    {
        a = Uint64A((Uint64*)v.uint64a.data, v.uint64a.size);
        return true;
    }
    return false;
}

bool DInstance::GetSint64(
    const String& name, 
    Sint64& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT64, null, key) == MI_RESULT_OK)
    {
        a = Sint64(v.sint64);
        return true;
    }
    return false;
}

bool DInstance::GetSint64A(
    const String& name, 
    Sint64A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_SINT64A, null, key) == MI_RESULT_OK)
    {
        a = Sint64A((Sint64*)v.sint64a.data, v.sint64a.size);
        return true;
    }
    return false;
}

bool DInstance::GetReal32(
    const String& name, 
    Real32& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REAL32, null, key) == MI_RESULT_OK)
    {
        a = Real32(v.real32);
        return true;
    }
    return false;
}

bool DInstance::GetReal32A(
    const String& name, 
    Real32A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REAL32A, null, key) == MI_RESULT_OK)
    {
        a = Real32A((Real32*)v.real32a.data, v.real32a.size);
        return true;
    }
    return false;
}

bool DInstance::GetReal64(
    const String& name, 
    Real64& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REAL64, null, key) == MI_RESULT_OK)
    {
        a = Real64(v.real64);
        return true;
    }
    return false;
}

bool DInstance::GetReal64A(
    const String& name, 
    Real64A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REAL64A, null, key) == MI_RESULT_OK)
    {
        a = Real64A((Real64*)v.real64a.data, v.real64a.size);
        return true;
    }
    return false;
}

bool DInstance::GetChar16(
    const String& name, 
    Char16& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_CHAR16, null, key) == MI_RESULT_OK)
    {
        a = Char16(v.char16);
        return true;
    }
    return false;
}

bool DInstance::GetChar16A(
    const String& name, 
    Char16A& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_CHAR16A, null, key) == MI_RESULT_OK)
    {
        a = Char16A((Char16*)v.char16a.data, v.char16a.size);
        return true;
    }
    return false;
}

bool DInstance::GetDatetime(
    const String& name, 
    Datetime& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_DATETIME, null, key) == MI_RESULT_OK)
    {
        a = Datetime(v.datetime);
        return true;
    }
    return false;
}

bool DInstance::GetDatetimeA(
    const String& name, 
    DatetimeA& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_DATETIMEA, null, key) == MI_RESULT_OK)
    {
        a = DatetimeA((Datetime*)v.datetimea.data, v.datetimea.size);
        return true;
    }
    return false;
}

bool DInstance::GetString(
    const String& name, 
    String& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_STRING, null, key) == MI_RESULT_OK)
    {
        a = String(v.string);
        return true;
    }
    return false;
}

bool DInstance::GetStringA(
    const String& name, 
    StringA& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_STRINGA, null, key) == MI_RESULT_OK)
    {
        a.Clear();
        for (MI_Uint32 i = 0; i < v.stringa.size; i++)
            a.PushBack(v.stringa.data[i]);
        return true;
    }
    return false;
}

bool DInstance::GetReference(
    const String& name, 
    DInstance& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REFERENCE, null, key) == MI_RESULT_OK)
    {
        __MI_Instance_Ref(v.reference);
        a = DInstance(v.reference, ADOPT);
        return true;
    }
    return false;
}

bool DInstance::GetReferenceA(
    const String& name, 
    DInstanceA& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_REFERENCEA, null, key) == MI_RESULT_OK)
    {
        a.Clear();
        for (MI_Uint32 i = 0; i < v.referencea.size; i++)
        {
            MI_Instance* tmp = v.referencea.data[i];
            __MI_Instance_Ref(tmp);
            a.PushBack(DInstance(tmp, ADOPT));
        }
        return true;
    }
    return false;
}

bool DInstance::GetInstance(
    const String& name, 
    DInstance& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_INSTANCE, null, key) == MI_RESULT_OK)
    {
        __MI_Instance_Ref(v.instance);
        a = DInstance(v.instance, ADOPT);
        return true;
    }
    return false;
}

bool DInstance::GetInstanceA(
    const String& name, 
    DInstanceA& a,
    bool& null,
    bool& key) const
{
    MI_Value v;

    if (GetValueAsType(name, &v, MI_INSTANCEA, null, key) == MI_RESULT_OK)
    {
        a.Clear();

        for (MI_Uint32 i = 0; i < v.instancea.size; i++)
        {
            MI_Instance* tmp = v.instancea.data[i];
            __MI_Instance_Ref(tmp);
            a.PushBack(DInstance(tmp, ADOPT));
        }
    }
    return false;
}

bool DInstance::DynamicToStatic(
    const DInstance& dinst,
    bool keysOnly,
    bool ignoreUnknownProperties,
    Instance& sinst)
{
    if (!sinst.m_instance)
    {
        return false;
    }

    const MI_ClassDecl* cd = sinst.m_instance->classDecl;

    if (!cd)
    {
        return false;
    }

    // Get the property count.
    Uint32 count;
    
    if (MI_Instance_GetElementCount(dinst.m_self, &count) != MI_RESULT_OK)
    {
        return false;
    }

    // For each property in the dynamic instance.
    for (Uint32 i = 0; i < count; i++)
    {
        const MI_Char* name = NULL;
        MI_Value value;
        MI_Type type;
        MI_Uint32 flags;

        // Get the i-th property.
        if (MI_Instance_GetElementAt(
            dinst.m_self, i, &name, &value, &type, &flags) != MI_RESULT_OK)
        {
            return false;
        }

        // Find the index of the property with same name in target instance.
        MI_PropertyDecl* pd;
        {
            MI_Uint32 index = _FindPropertyDecl(cd, name);

            if (index == (MI_Uint32)-1)
            {
                if (ignoreUnknownProperties)
                    continue;

                return false;
            }

            pd = cd->properties[index];
        }

        // Get offset to field:
        size_t off = pd->offset;

        // Skip non-key properties if so requested.
        if (!(pd->flags & MI_FLAG_KEY) && keysOnly)
        {
            continue;
        }

        // Set the property in the target instanced.
        if (type == (MI_Type)pd->type)
        {
            if (flags & MI_FLAG_NULL)
            {
                switch (type)
                {
                    case MI_BOOLEAN:
                    {
                        sinst.GetField<Boolean>(off).Clear();
                        break;
                    }
                    case MI_BOOLEANA:
                        sinst.GetField<BooleanA>(off).Clear();
                        break;
                    case MI_UINT8:
                        sinst.GetField<Uint8>(off).Clear();
                        break;
                    case MI_UINT8A:
                        sinst.GetField<Uint8A>(off).Clear();
                        break;
                    case MI_SINT8:
                        sinst.GetField<Sint8>(off).Clear();
                        break;
                    case MI_SINT8A:
                        sinst.GetField<Sint8A>(off).Clear();
                        break;
                    case MI_UINT16:
                        sinst.GetField<Uint16>(off).Clear();
                        break;
                    case MI_UINT16A:
                        sinst.GetField<Uint16A>(off).Clear();
                        break;
                    case MI_SINT16:
                        sinst.GetField<Sint16>(off).Clear();
                        break;
                    case MI_SINT16A:
                        sinst.GetField<Sint16A>(off).Clear();
                        break;
                    case MI_UINT32:
                        sinst.GetField<Uint32>(off).Clear();
                        break;
                    case MI_UINT32A:
                        sinst.GetField<Uint32A>(off).Clear();
                        break;
                    case MI_SINT32:
                        sinst.GetField<Sint32>(off).Clear();
                        break;
                    case MI_SINT32A:
                        sinst.GetField<Sint32A>(off).Clear();
                        break;
                    case MI_UINT64:
                        sinst.GetField<Uint64>(off).Clear();
                        break;
                    case MI_UINT64A:
                        sinst.GetField<Uint64A>(off).Clear();
                        break;
                    case MI_SINT64:
                        sinst.GetField<Sint64>(off).Clear();
                        break;
                    case MI_SINT64A:
                        sinst.GetField<Sint64A>(off).Clear();
                        break;
                    case MI_REAL32:
                        sinst.GetField<Real32>(off).Clear();
                        break;
                    case MI_REAL32A:
                        sinst.GetField<Real32A>(off).Clear();
                        break;
                    case MI_REAL64:
                        sinst.GetField<Real64>(off).Clear();
                        break;
                    case MI_REAL64A:
                        sinst.GetField<Real64A>(off).Clear();
                        break;
                    case MI_CHAR16:
                        sinst.GetField<Char16>(off).Clear();
                        break;
                    case MI_CHAR16A:
                        sinst.GetField<Char16A>(off).Clear();
                        break;
                    case MI_DATETIME:
                        sinst.GetField<Datetime>(off).Clear();
                        break;
                    case MI_DATETIMEA:
                        sinst.GetField<DatetimeA>(off).Clear();
                        break;
                    case MI_STRING:
                        sinst.GetField<String>(off).Clear();
                        break;
                    case MI_STRINGA:
                        sinst.GetField<StringA>(off).Clear();
                        break;
                    case MI_REFERENCE:
                    case MI_INSTANCE:
                        sinst.GetField<Instance>(off).Clear();
                        break;
                    case MI_REFERENCEA:
                    case MI_INSTANCEA:
                        sinst.GetField<InstanceA>(off).Clear();
                        break;
                }
            }
            else
            {
                switch (type)
                {
                    case MI_BOOLEAN:
                        sinst.GetField<Uint8>(off).Set(value.uint8);
                        break;
                    case MI_UINT8:
                        sinst.GetField<Uint8>(off).Set(value.uint8);
                        break;
                    case MI_SINT8:
                        sinst.GetField<Sint8>(off).Set(value.sint8);
                        break;
                    case MI_UINT16:
                        sinst.GetField<Uint16>(off).Set(value.uint16);
                        break;
                    case MI_SINT16:
                        sinst.GetField<Sint16>(off).Set(value.sint16);
                        break;
                    case MI_UINT32:
                        sinst.GetField<Uint32>(off).Set(value.uint32);
                        break;
                    case MI_SINT32:
                        sinst.GetField<Sint32>(off).Set(value.sint32);
                        break;
                    case MI_UINT64:
                        sinst.GetField<Uint64>(off).Set(value.uint64);
                        break;
                    case MI_SINT64:
                        sinst.GetField<Sint64>(off).Set(value.sint64);
                        break;
                    case MI_REAL32:
                        sinst.GetField<Real32>(off).Set(value.real32);
                        break;
                    case MI_REAL64:
                        sinst.GetField<Real64>(off).Set(value.real64);
                        break;
                    case MI_CHAR16:
                        sinst.GetField<Char16>(off).Set(value.char16);
                        break;
                    case MI_DATETIME:
                        sinst.GetField<Datetime>(off).Set(value.datetime);
                        break;
                    case MI_STRING:
                        sinst.GetField<String>(off).Set(value.string);
                        break;
                    case MI_REFERENCE:
                    case MI_INSTANCE:
                    {
                        if (!value.instance)
                        {
                            return false;
                        }

                        const MI_ClassDecl* tcd = SchemaDecl_FindClassDecl(
                            cd->schema,  pd->className);

                        if (!tcd)
                        {
                            return false;
                        }

                        // ATTN: optimize: avoid cloning.
                        DInstance tdinst(value.instance, CLONE);
                        Instance x(tcd);

                        if (!DynamicToStatic(tdinst, keysOnly, 
                            ignoreUnknownProperties, x))
                        {
                            return false;
                        }

                        sinst.GetField<Instance>(off).Set(x);
                        break;
                    }
                    case MI_BOOLEANA:
                    {
                        BooleanA a(value.booleana.data, value.booleana.size);
                        sinst.GetField<BooleanA>(off).Set(a);
                        break;
                    }
                    case MI_UINT8A:
                    {
                        Uint8A a(value.uint8a.data, value.uint8a.size);
                        sinst.GetField<Uint8A>(off).Set(a);
                        break;
                    }
                    case MI_SINT8A:
                    {
                        Sint8A a(value.sint8a.data, value.sint8a.size);
                        sinst.GetField<Sint8A>(off).Set(a);
                        break;
                    }
                    case MI_UINT16A:
                    {
                        Uint16A a(value.uint16a.data, value.uint16a.size);
                        sinst.GetField<Uint16A>(off).Set(a);
                        break;
                    }
                    case MI_SINT16A:
                    {
                        Sint16A a(value.sint16a.data, value.sint16a.size);
                        sinst.GetField<Sint16A>(off).Set(a);
                        break;
                    }
                    case MI_UINT32A:
                    {
                        Uint32A a(value.uint32a.data, value.uint32a.size);
                        sinst.GetField<Uint32A>(off).Set(a);
                        break;
                    }
                    case MI_SINT32A:
                    {
                        Sint32A a(value.sint32a.data, value.sint32a.size);
                        sinst.GetField<Sint32A>(off).Set(a);
                        break;
                    }
                    case MI_UINT64A:
                    {
                        Uint64A a(value.uint64a.data, value.uint64a.size);
                        sinst.GetField<Uint64A>(off).Set(a);
                        break;
                    }
                    case MI_SINT64A:
                    {
                        Sint64A a(value.sint64a.data, value.sint64a.size);
                        sinst.GetField<Sint64A>(off).Set(a);
                        break;
                    }
                    case MI_REAL32A:
                    {
                        Real32A a(value.real32a.data, value.real32a.size);
                        sinst.GetField<Real32A>(off).Set(a);
                        break;
                    }
                    case MI_REAL64A:
                    {
                        Real64A a(value.real64a.data, value.real64a.size);
                        sinst.GetField<Real64A>(off).Set(a);
                        break;
                    }
                    case MI_CHAR16A:
                    {
                        Char16A a(value.char16a.data, value.char16a.size);
                        sinst.GetField<Char16A>(off).Set(a);
                        break;
                    }
                    case MI_DATETIMEA:
                    {
                        DatetimeA a(
                            reinterpret_cast<Datetime*>(value.datetimea.data), 
                            value.datetimea.size);
                        sinst.GetField<DatetimeA>(off).Set(a);
                        break;
                    }
                    case MI_STRINGA:
                    {
                        StringA a;

                        for (Uint32 j = 0; j < value.stringa.size; j++)
                            a.PushBack(String(value.stringa.data[j]));

                        sinst.GetField<StringA>(off).Set(a);
                        break;
                    }
                    case MI_REFERENCEA:
                    case MI_INSTANCEA:
                    {
                        if (!value.instancea.data)
                        {
                            return false;
                        }

                        const MI_ClassDecl* tcd = SchemaDecl_FindClassDecl(
                            cd->schema,  pd->className);

                        if (!tcd)
                        {
                            return false;
                        }

                        InstanceA a;

                        for (Uint32 j = 0; j < value.instancea.size; j++)
                        {
                            if (!value.instancea.data[j])
                            {
                                return false;
                            }

                            DInstance tdinst(value.instancea.data[j], CLONE);
                            Instance x(tcd);

                            if (!DynamicToStatic(tdinst, keysOnly, 
                                ignoreUnknownProperties, x))
                            {
                                return false;
                            }

                            a.PushBack(x);
                        }

                        sinst.GetField<InstanceA>(off).Set(a);
                        break;
                    }
                }
            }
        }
        else if (type == MI_STRING)
        {
            // Convert string to type of target property.
            switch (pd->type)
            {
                case MI_BOOLEAN:
                {
                    Boolean x;

                    if (StrToBoolean(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Boolean>(off).Set(x);
                    break;
                }
                case MI_UINT8:
                {
                    Uint8 x;

                    if (StrToUint8(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Uint8>(off).Set(x);
                    break;
                }
                case MI_SINT8:
                {
                    Sint8 x;

                    if (StrToSint8(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Sint8>(off).Set(x);
                    break;
                }
                case MI_UINT16:
                {
                    Uint16 x;

                    if (StrToUint16(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Uint16>(off).Set(x);
                    break;
                }
                case MI_SINT16:
                {
                    Sint16 x;

                    if (StrToSint16(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Sint16>(off).Set(x);
                    break;
                }
                case MI_UINT32:
                {
                    Uint32 x;

                    if (StrToUint32(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Uint32>(off).Set(x);
                    break;
                }
                case MI_SINT32:
                {
                    Sint32 x;

                    if (StrToSint32(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Sint32>(off).Set(x);
                    break;
                }
                case MI_UINT64:
                {
                    Uint64 x;

                    if (StrToUint64(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Uint64>(off).Set(x);
                    break;
                }
                case MI_SINT64:
                {
                    Sint64 x;

                    if (StrToSint64(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Sint64>(off).Set(x);
                    break;
                }
                case MI_REAL32:
                {
                    Real32 x;

                    if (StrToReal32(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Real32>(off).Set(x);
                    break;
                }
                case MI_REAL64:
                {
                    Real64 x;

                    if (StrToReal64(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Real64>(off).Set(x);
                    break;
                }
                case MI_CHAR16:
                {
                    Char16 x;

                    if (StrToChar16(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Char16>(off).Set(x);
                    break;
                }
                case MI_DATETIME:
                {
                    MI_Datetime x;

                    if (StrToDatetime(value.string, &x) != 0)
                        return false;

                    sinst.GetField<Datetime>(off).Set(Datetime(x));
                    break;
                }
                default:
                {
                    // Conversion to string to this type is unsupported!
                    return false;
                }
            }
        }
        else if (type == MI_STRINGA)
        {
            switch (pd->type)
            {
                case MI_BOOLEANA:
                {
                    Array<Boolean> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Boolean x;

                        if (StrToBoolean(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<BooleanA>(off).Set(a);
                    break;
                }
                case MI_UINT8A:
                {
                    Array<Uint8> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Uint8 x;

                        if (StrToUint8(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Uint8A>(off).Set(a);
                    break;
                }
                case MI_SINT8A:
                {
                    Array<Sint8> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Sint8 x;

                        if (StrToSint8(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Sint8A>(off).Set(a);
                    break;
                }
                case MI_UINT16A:
                {
                    Array<Uint16> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Uint16 x;

                        if (StrToUint16(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Uint16A>(off).Set(a);
                    break;
                }
                case MI_SINT16A:
                {
                    Array<Sint16> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Sint16 x;

                        if (StrToSint16(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Sint16A>(off).Set(a);
                    break;
                }
                case MI_UINT32A:
                {
                    Array<Uint32> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Uint32 x;

                        if (StrToUint32(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Uint32A>(off).Set(a);
                    break;
                }
                case MI_SINT32A:
                {
                    Array<Sint32> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Sint32 x;

                        if (StrToSint32(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Sint32A>(off).Set(a);
                    break;
                }
                case MI_UINT64A:
                {
                    Array<Uint64> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Uint64 x;

                        if (StrToUint64(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Uint64A>(off).Set(a);
                    break;
                }
                case MI_SINT64A:
                {
                    Array<Sint64> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Sint64 x;

                        if (StrToSint64(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Sint64A>(off).Set(a);
                    break;
                }
                case MI_REAL32A:
                {
                    Array<Real32> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Real32 x;

                        if (StrToReal32(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Real32A>(off).Set(a);
                    break;
                }
                case MI_REAL64A:
                {
                    Array<Real64> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Real64 x;

                        if (StrToReal64(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Real64A>(off).Set(a);
                    break;
                }
                case MI_CHAR16A:
                {
                    Array<Char16> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Char16 x;

                        if (StrToChar16(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<Char16A>(off).Set(a);
                    break;
                }
                case MI_DATETIMEA:
                {
                    Array<Datetime> a;

                    for (Uint32 j = 0; j < value.stringa.size; j++)
                    {
                        MI_Datetime x;

                        if (StrToDatetime(value.stringa.data[j], &x) != 0)
                            return false;

                        a.PushBack(x);
                    }

                    sinst.GetField<DatetimeA>(off).Set(a);
                    break;
                }
                default:
                {
                    // Conversion to string to this type is unsupported!
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool DInstance::StaticToDynamic(
    const Instance& sinst,
    bool keysOnly,
    DInstance& dinst)
{
    // Reject if static instance has no internal instance.
    if (!sinst.m_instance)
    {
        return false;
    }

    // Get class declaration from static instance.
    const MI_ClassDecl* cd = sinst.m_instance->classDecl;
    if (!cd)
    {
        return false;
    }

    // Create new instance with given class name.
    {
        MetaType mt;
        memset(&mt, 0, sizeof(mt));

        if (cd->flags & MI_FLAG_ASSOCIATION)
            mt = ASSOCIATION;
        else if (cd->flags & MI_FLAG_INDICATION)
            mt = INDICATION;
        else if (cd->flags & MI_FLAG_METHOD)
            mt = METHOD;
        else if (cd->flags & MI_FLAG_CLASS)
            mt = CLASS;

        dinst = DInstance(cd->name, mt);
    }

    // Convert each property.
    for (Uint32 i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];
        bool key = (pd->flags & MI_FLAG_KEY) != 0;

        if (!key && keysOnly)
            continue;

        switch (pd->type)
        {
            case MI_BOOLEAN:
            {
                dinst.AddBoolean(
                    pd->name, 
                    sinst.GetField<Boolean>(pd->offset).value,
                    !sinst.GetField<Boolean>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT8:
            {
                dinst.AddUint8(
                    pd->name, 
                    sinst.GetField<Uint8>(pd->offset).value,
                    !sinst.GetField<Uint8>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT8:
            {
                dinst.AddSint8(
                    pd->name, 
                    sinst.GetField<Sint8>(pd->offset).value,
                    !sinst.GetField<Sint8>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT16:
            {
                dinst.AddUint16(
                    pd->name, 
                    sinst.GetField<Uint16>(pd->offset).value,
                    !sinst.GetField<Uint16>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT16:
            {
                dinst.AddSint16(
                    pd->name, 
                    sinst.GetField<Sint16>(pd->offset).value,
                    !sinst.GetField<Sint16>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT32:
            {
                dinst.AddUint32(
                    pd->name, 
                    sinst.GetField<Uint32>(pd->offset).value,
                    !sinst.GetField<Uint32>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT32:
            {
                dinst.AddSint32(
                    pd->name, 
                    sinst.GetField<Sint32>(pd->offset).value,
                    !sinst.GetField<Sint32>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT64:
            {
                dinst.AddUint64(
                    pd->name, 
                    sinst.GetField<Uint64>(pd->offset).value,
                    !sinst.GetField<Uint64>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT64:
            {
                dinst.AddSint64(
                    pd->name, 
                    sinst.GetField<Sint64>(pd->offset).value,
                    !sinst.GetField<Sint64>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REAL32:
            {
                dinst.AddReal32(
                    pd->name, 
                    sinst.GetField<Real32>(pd->offset).value,
                    !sinst.GetField<Real32>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REAL64:
            {
                dinst.AddReal64(
                    pd->name, 
                    sinst.GetField<Real64>(pd->offset).value,
                    !sinst.GetField<Real64>(pd->offset).exists,
                    key);
                break;
            }
            case MI_CHAR16:
            {
                dinst.AddChar16(
                    pd->name, 
                    sinst.GetField<Char16>(pd->offset).value,
                    !sinst.GetField<Char16>(pd->offset).exists,
                    key);
                break;
            }
            case MI_DATETIME:
            {
                dinst.AddDatetime(
                    pd->name, 
                    sinst.GetField<Datetime>(pd->offset).value,
                    !sinst.GetField<Datetime>(pd->offset).exists,
                    key);
                break;
            }
            case MI_STRING:
            {
                dinst.AddString(
                    pd->name, 
                    sinst.GetField<String>(pd->offset).value,
                    !sinst.GetField<String>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REFERENCE:
            case MI_INSTANCE:
            {
                DInstance x;

                if (!DInstance::StaticToDynamic(
                    sinst.GetField<Instance>(pd->offset).value,
                    keysOnly,
                    x))
                {
                    return false;
                }

                dinst.AddInstance(
                    pd->name, 
                    x,
                    !sinst.GetField<Instance>(pd->offset).exists,
                    key);
                break;
            }
            case MI_BOOLEANA:
            {
                dinst.AddBooleanA(
                    pd->name, 
                    sinst.GetField<BooleanA>(pd->offset).value,
                    !sinst.GetField<BooleanA>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT8A:
            {
                dinst.AddUint8A(
                    pd->name, 
                    sinst.GetField<Uint8A>(pd->offset).value,
                    !sinst.GetField<Uint8A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT8A:
            {
                dinst.AddSint8A(
                    pd->name, 
                    sinst.GetField<Sint8A>(pd->offset).value,
                    !sinst.GetField<Sint8A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT16A:
            {
                dinst.AddUint16A(
                    pd->name, 
                    sinst.GetField<Uint16A>(pd->offset).value,
                    !sinst.GetField<Uint16A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT16A:
            {
                dinst.AddSint16A(
                    pd->name, 
                    sinst.GetField<Sint16A>(pd->offset).value,
                    !sinst.GetField<Sint16A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT32A:
            {
                dinst.AddUint32A(
                    pd->name, 
                    sinst.GetField<Uint32A>(pd->offset).value,
                    !sinst.GetField<Uint32A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT32A:
            {
                dinst.AddSint32A(
                    pd->name, 
                    sinst.GetField<Sint32A>(pd->offset).value,
                    !sinst.GetField<Sint32A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_UINT64A:
            {
                dinst.AddUint64A(
                    pd->name, 
                    sinst.GetField<Uint64A>(pd->offset).value,
                    !sinst.GetField<Uint64A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_SINT64A:
            {
                dinst.AddSint64A(
                    pd->name, 
                    sinst.GetField<Sint64A>(pd->offset).value,
                    !sinst.GetField<Sint64A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REAL32A:
            {
                dinst.AddReal32A(
                    pd->name, 
                    sinst.GetField<Real32A>(pd->offset).value,
                    !sinst.GetField<Real32A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REAL64A:
            {
                dinst.AddReal64A(
                    pd->name, 
                    sinst.GetField<Real64A>(pd->offset).value,
                    !sinst.GetField<Real64A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_CHAR16A:
            {
                dinst.AddChar16A(
                    pd->name, 
                    sinst.GetField<Char16A>(pd->offset).value,
                    !sinst.GetField<Char16A>(pd->offset).exists,
                    key);
                break;
            }
            case MI_DATETIMEA:
            {
                dinst.AddDatetimeA(
                    pd->name, 
                    sinst.GetField<DatetimeA>(pd->offset).value,
                    !sinst.GetField<DatetimeA>(pd->offset).exists,
                    key);
                break;
            }
            case MI_STRINGA:
            {
                dinst.AddStringA(
                    pd->name, 
                    sinst.GetField<StringA>(pd->offset).value,
                    !sinst.GetField<StringA>(pd->offset).exists,
                    key);
                break;
            }
            case MI_REFERENCEA:
            case MI_INSTANCEA:
            {
                Array<DInstance> da;
                const Array<Instance>& sa = 
                    sinst.GetField<InstanceA>(pd->offset).value;

                for (Uint32 index = 0; index < sa.GetSize(); index++)
                {
                    DInstance x;

                    if (!DInstance::StaticToDynamic( sa[index], keysOnly, x))
                        return false;

                    da.PushBack(x);
                }

                dinst.AddInstanceA(
                    pd->name, 
                    da,
                    !sinst.GetField<InstanceA>(pd->offset).exists,
                    key);
                break;
            }
            default:
                break;
        }
    }

    return true;
}

MI_END_NAMESPACE
