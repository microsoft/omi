/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_instance_h
#define _micxx_instance_h

#include <MI.h>
#include "linkage.h"
#include "atomic.h"
#include "memory.h"
#include "micxx_string.h"
#include "field.h"
#include "array.h"
#include "types.h"

MI_BEGIN_NAMESPACE

//////////////////////////
//  Base class for C++ MI_Instance representation
class MICXX_LINKAGE Instance
{
public:

    Instance();

    Instance(const Instance& x);

    ~Instance();

    Instance& operator=(const Instance& x);

    inline MI_Instance* GetInstance() const
    {
        return m_instance;
    }

    String GetNamespace() const;

    void SetNamespace(const String& nameSpace);

    void Print(FILE* os = stdout, MI_Uint32 level = 0) const;

    static const MI_ClassDecl* GetClassDecl();

    // Sets whether to use copy-on-write behavior. This function is 
    // experimental (as indicated by the leading double underscore).
    void __setCopyOnWrite(bool flag)
    {
        GetHeader(m_instance)->u.s.m_disableCopyOnWrite = flag ? 0 : 1;
    }

    // Gets the copy-on-write flag from the MI_Instance header.
    bool __getCopyOnWrite() const
    {
        return GetHeader(m_instance)->u.s.m_disableCopyOnWrite ? false : true;
    }

    // Forces a copy-on-write operation (if reference count is not 1). After
    // calling this function, the instance will have a pointer to its own
    // copy of MI_Instance whose reference count is 1.
    void __forceCopyOnWrite()
    {
        Header* header = GetHeader(m_instance);

        // Avoid the copy on write if sharing has been enabled.

        if (AtomicGet(header->u.s.m_refCounter) != 1)
        {
            MI_Instance* current = m_instance;
            m_instance = Clone();
            AddRef(m_instance);
            Release(current);
        }
    }

protected:

    Instance(
        const MI_ClassDecl* clDecl, 
        const MI_Instance* instance, 
        bool keysOnly);

    Instance(
        const MI_ClassDecl* clDecl);

    Instance(
        const MI_MethodDecl* methodDecl);

    Instance(
        const MI_MethodDecl* methodDecl, 
        const MI_Instance* instance, 
        bool keysOnly);

    void CopyRef(
        const Instance& x);

    void COW()
    {
        Header* header = GetHeader(m_instance);

        // Avoid the copy on write if sharing has been enabled.

        if (header->u.s.m_disableCopyOnWrite == 0 && 
            AtomicGet(header->u.s.m_refCounter) != 1)
        {
            MI_Instance* current = m_instance;
            m_instance = Clone();
            AddRef(m_instance);
            Release(current);
        }
    }

    template<typename T>
    Field<T>& GetField(size_t offset)
    {
        COW();
        void* ptr = reinterpret_cast<char*>(m_instance) + offset;
        return *(reinterpret_cast<Field<T>*>(ptr));
    }

    template<typename T>
    const Field<T>& GetField(size_t offset) const
    {
        const void* ptr = reinterpret_cast<const char*>(m_instance) + offset;
        return *(reinterpret_cast<const Field<T>*>(ptr));
    }

private:

    // helper data - placed before MI_Instance structure
    struct Header
    {
        union 
        {
            struct _HeaderData
            {
                AtomicType m_refCounter;
                unsigned int m_disableCopyOnWrite;
            } 
            s;
            char alignment[(sizeof(struct _HeaderData) + 15) & ~15];
        }
        u;
    };

    void Initialize(
        const MI_ClassDecl* clDecl, 
        const MI_Instance* instance, 
        bool keysOnly);

    static Header* GetHeader(MI_Instance* instance) 
    {
        return reinterpret_cast<Header*>(
            reinterpret_cast<char*>(instance) - sizeof(Header));
    }

    static void AddRef(MI_Instance* instance) 
    { 
        AtomicInc(GetHeader(instance)->u.s.m_refCounter); 
    }

    static void Release(MI_Instance* instance);

    static MI_Instance* Create(const MI_ClassDecl* clDecl);

    MI_Instance* Clone() const;

    MI_Instance* m_instance;

    friend class Context;
    friend class DInstance;

    MICXX_LINKAGE
    friend bool __IsA(const MI_ClassDecl*, const Instance*);
};

inline Instance::Instance() : m_instance(0) 
{
}

inline Instance::Instance(const Instance& x) : m_instance(0)
{
    CopyRef(x);
}

inline Instance::~Instance()
{
    Release(m_instance);
}

inline Instance& Instance::operator=(const Instance& x)
{
   CopyRef(x);
   return *this;
}

template<>
inline const ArrayTraits* GetArrayTraits<Instance>() 
{
    return __traits[MI_INSTANCE];
};

typedef Array<Instance> InstanceA;

MICXX_LINKAGE
bool __IsA(const MI_ClassDecl* classDecl, const Instance* instance);

template<class CLASS>
bool IsA(const Instance& instance)
{
    return __IsA(((CLASS*)0)->GetClassDecl(), &instance);
}

MI_END_NAMESPACE

#endif /* _micxx_instance_h */
