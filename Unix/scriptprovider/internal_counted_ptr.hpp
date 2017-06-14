// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_UTIL_INTERNAL_COUNTED_PTR_HPP
#define INCLUDED_UTIL_INTERNAL_COUNTED_PTR_HPP


#include <algorithm>


#include "default_delete.hpp"
#include "traits.hpp"


namespace util
{


// internal_counted_ptr
//------------------------------------------------------------------------------
template<typename T, typename D = default_delete<T> >
class internal_counted_ptr
{
public:
    typedef T element_type;
    typedef D deleter_type;
    typedef typename remove_reference<T>::type* pointer;

    /*ctor*/ internal_counted_ptr ();

    explicit /*ctor*/ internal_counted_ptr (pointer pT);

    /*ctor*/ internal_counted_ptr (
        pointer pT,
        typename conditional<is_reference<D>::value, D, D const&>::type del);

    /*ctor*/ internal_counted_ptr (internal_counted_ptr const& ref);

    template<typename T2, typename D2>
    /*ctor*/ internal_counted_ptr (
        internal_counted_ptr<T2, D2> const& ref);

    /*dtor*/ ~internal_counted_ptr ();

    internal_counted_ptr& operator = (pointer pT);
    internal_counted_ptr& operator = (internal_counted_ptr const& rhs);
    template<typename T2, typename D2>
    internal_counted_ptr& operator = (internal_counted_ptr<T2, D2> const& rhs);

    void swap (internal_counted_ptr& ref);

    void reset ();
    void reset (pointer pT);

    element_type* get () const;
    deleter_type get_deleter () const;

    element_type& operator * () const;
    element_type* operator -> () const;

    size_t use_count () const;
    bool unique () const;

    /*bool*/ operator bool () const;
    bool operator ! () const;

private:
    pointer m_pT;
    deleter_type m_deleter;

    template<typename T2, typename D2>
    friend class internal_counted_ptr;
};


// ref_counted_obj
//------------------------------------------------------------------------------
class ref_counted_obj
{
public:
    /*ctor*/ ref_counted_obj ();
    /*ctor*/ ref_counted_obj (ref_counted_obj const& ref);

    ref_counted_obj& operator = (ref_counted_obj const& ref);

    size_t inc_ref_count () const;
    size_t dec_ref_count () const;

    size_t use_count () const;

private:
    mutable size_t m_count;
};


// internal_counted_ptr definitions
//------------------------------------------------------------------------------
template<typename T, typename D>
/*ctor*/
internal_counted_ptr<T, D>::internal_counted_ptr ()
    : m_pT (0)
    , m_deleter (typename internal_counted_ptr<T, D>::deleter_type ())
{
    // empty
}

template<typename T, typename D>
/*ctor*/
internal_counted_ptr<T, D>::internal_counted_ptr (
     typename internal_counted_ptr<T, D>::pointer pT)
    : m_pT (pT)
    , m_deleter (typename internal_counted_ptr<T, D>::deleter_type ())
{
    if (0 != pT)
    {
        m_pT->inc_ref_count ();
    }
}

template<typename T, typename D>
/*ctor*/
internal_counted_ptr<T, D>::internal_counted_ptr (
    typename internal_counted_ptr<T, D>::pointer pT,
    typename conditional<is_reference<D>::value, D, D const&>::type del)
    : m_pT (pT)
    , m_deleter (del)
{
    if (0 != pT)
    {
        m_pT->inc_ref_count ();
    }
}

template<typename T, typename D>
/*ctor*/
internal_counted_ptr<T, D>::internal_counted_ptr (
    internal_counted_ptr<T, D> const& ref)
    : m_pT (ref.m_pT)
    , m_deleter (ref.m_deleter)
{
    if (0 != m_pT)
    {
        m_pT->inc_ref_count ();
    }
}

template<typename T, typename D>
template<typename T2, typename D2>
/*ctor*/
internal_counted_ptr<T, D>::internal_counted_ptr (
    internal_counted_ptr<T2, D2> const& ref)
    : m_pT (ref.m_pT)
    , m_deleter ()
{
    if (0 != m_pT)
    {
        m_pT->inc_ref_count ();
    }
}

template<typename T, typename D>
/*dtor*/
internal_counted_ptr<T, D>::~internal_counted_ptr ()
{
    reset ();
}

template<typename T, typename D>
internal_counted_ptr<T, D>&
internal_counted_ptr<T, D>::operator = (
    typename internal_counted_ptr<T, D>::pointer pT)
{
    if (m_pT != pT)
    {
        if (0 != pT)
        {
            pT->inc_ref_count ();
        }
        if (0 != m_pT &&
            0 == m_pT->dec_ref_count ())
        {
            m_deleter (m_pT);
        }
        m_pT = pT;
    }
    return *this;
}

template<typename T, typename D>
internal_counted_ptr<T, D>&
internal_counted_ptr<T, D>::operator = (
   internal_counted_ptr<T, D> const& rhs)
{
    if (m_pT != rhs.m_pT)
    {
        if (0 != rhs.m_pT)
        {
            rhs.m_pT->inc_ref_count ();
        }
        if (0 != m_pT &&
            0 == m_pT->dec_ref_count ())
        {
            m_deleter (m_pT);
        }
        m_pT = rhs.m_pT;
    }
    return *this;
}

template<typename T, typename D>
template<typename T2, typename D2>
internal_counted_ptr<T, D>&
internal_counted_ptr<T, D>::operator = (
    internal_counted_ptr<T2, D2> const& rhs)
{
    if (m_pT != rhs.m_pT)
    {
        if (0 != rhs.m_pT)
        {
            rhs->inc_ref_count ();
        }
        if (0 != m_pT &&
            0 == m_pT->dec_ref_count ())
        {
            m_deleter (m_pT);
        }
        m_pT = rhs.m_pT;;
    }
    return *this;
}

template<typename T, typename D>
void
internal_counted_ptr<T, D>::swap (
    internal_counted_ptr<T, D>& other)
{
    std::swap (m_pT, other.m_pT);
    std::swap (m_deleter, other.m_deleter);
}

template<typename T, typename D>
void
internal_counted_ptr<T, D>::reset ()
{
    if (0 != m_pT)
    {
        if (0 == m_pT->dec_ref_count ())
        {
            m_deleter (m_pT);
        }
        m_pT = 0;
    }
}

template<typename T, typename D>
void
internal_counted_ptr<T, D>::reset (
    typename internal_counted_ptr<T, D>::pointer pT)
{
    if (m_pT != pT)
    {
        if (0 != pT)
        {
            pT->inc_ref_count ();
        }
        reset ();
        m_pT = pT;
    }
}

template<typename T, typename D>
typename internal_counted_ptr<T, D>::element_type*
internal_counted_ptr<T, D>::get () const
{
    return m_pT;
}

template<typename T, typename D>
typename internal_counted_ptr<T, D>::deleter_type
internal_counted_ptr<T, D>::get_deleter () const
{
    return m_deleter;
}

template<typename T, typename D>
typename internal_counted_ptr<T, D>::element_type&
internal_counted_ptr<T, D>::operator * () const
{
    return *m_pT;
}

template<typename T, typename D>
typename internal_counted_ptr<T, D>::element_type*
internal_counted_ptr<T, D>::operator -> () const
{
    return m_pT;
}

template<typename T, typename D>
size_t
internal_counted_ptr<T, D>::use_count () const
{
    return 0 != m_pT ? m_pT->use_count () : 0;
}

template<typename T, typename D>
bool
internal_counted_ptr<T, D>::unique () const
{
    return 0 != m_pT ? 1 == m_pT->use_count () : false;
}

template<typename T, typename D>
/*bool*/
internal_counted_ptr<T, D>::operator bool () const
{
    return 0 != m_pT;
}

template<typename T, typename D>
bool
internal_counted_ptr<T, D>::operator ! () const
{
    return 0 == m_pT;
}


// ref_counted_obj definitions
//------------------------------------------------------------------------------
inline /*ctor*/
ref_counted_obj::ref_counted_obj ()
    : m_count (0)
{
    // empty
}

inline /*ctor*/
ref_counted_obj::ref_counted_obj (
    ref_counted_obj const& ref)
    : m_count (0)
{
    // empty
}

inline ref_counted_obj&
ref_counted_obj::operator = (
    ref_counted_obj const& ref)
{
    return *this;
}

inline size_t
ref_counted_obj::inc_ref_count () const
{
    return ++m_count;
}

inline size_t
ref_counted_obj::dec_ref_count () const
{
    return --m_count;
}

inline size_t
ref_counted_obj::use_count () const
{
    return m_count;
}


} // namespace util


#ifndef COMP_OP_DEF
#define COMP_OP_DEF(COMP_OP) \
    template<typename T, typename D> \
    bool operator COMP_OP (util::internal_counted_ptr<T, D> const& lhs, \
                           T const* const rhs) \
    { \
        return lhs.get () COMP_OP rhs; \
    } \
     \
    template<typename T, typename D> \
    bool operator COMP_OP (T const* const lhs, \
                           util::internal_counted_ptr<T, D> const& rhs) \
    { \
        return lhs COMP_OP rhs.get (); \
    } \
     \
    template<typename T, typename D> \
    bool operator COMP_OP (util::internal_counted_ptr<T, D> const& lhs, \
                           util::internal_counted_ptr<T, D> const& rhs) \
    { \
        return lhs.get () COMP_OP rhs.get (); \
    }


COMP_OP_DEF (==)
COMP_OP_DEF (!=)
COMP_OP_DEF (<)
COMP_OP_DEF (<=)
COMP_OP_DEF (>)
COMP_OP_DEF (>=)

#undef COMP_OP_DEF
#endif // COMP_OP_DEF


namespace std
{


template<typename T, typename D>
void
swap (
    util::internal_counted_ptr<T, D>& left,
    util::internal_counted_ptr<T, D>& right)
{
    left.swap (right);
}


}


#endif // INCLUDED_UTIL_INTERNAL_COUNTED_PTR_HPP
