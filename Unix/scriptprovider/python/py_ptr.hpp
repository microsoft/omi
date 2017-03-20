#ifndef INCLUDED_PY_PTR_HPP
#define INCLUDED_PY_PTR_HPP


#include "Python.h"


#include "traits.hpp"
#include "unique_ptr.hpp"


#include <algorithm>


namespace scx
{


struct PyObjectDeleter
{
    void operator () (PyObject* const pObj)
    {
        Py_DECREF (pObj);
    }
};


typedef util::unique_ptr<PyObject, PyObjectDeleter> PyObjPtr;


class DoNotIncRef_t {};


const DoNotIncRef_t DO_NOT_INC_REF = DoNotIncRef_t ();


template<typename T>
class py_ptr
{
public:
    typedef T element_type;
    typedef typename util::remove_reference<T>::type* pointer;

    /*ctor*/ py_ptr ();

    explicit /*ctor*/ py_ptr (pointer pT);
    /*ctor*/ py_ptr (pointer pT, DoNotIncRef_t const&);
    /*ctor*/ py_ptr (py_ptr const& ref);

    /*dtor*/ ~py_ptr ();

    py_ptr& operator = (pointer pT);
    py_ptr& operator = (py_ptr const& rhs);

    void swap (py_ptr& other);

    void reset ();
    void reset (pointer pT);

    pointer release ();

    pointer get () const;
    element_type& operator * () const;
    pointer operator -> () const;

    /*bool*/ operator bool () const;
    bool operator ! () const;

private:
    pointer m_pT;
};


template<typename T>
/*ctor*/
py_ptr<T>::py_ptr ()
    : m_pT (0)
{
    // empty
}


template<typename T>
/*ctor*/
py_ptr<T>::py_ptr (
    typename py_ptr<T>::pointer pT)
    : m_pT (pT)
{
    if (0 != m_pT)
    {
        Py_INCREF (m_pT);
    }
}


template<typename T>
/*ctor*/
py_ptr<T>::py_ptr (
    typename py_ptr<T>::pointer pT,
    DoNotIncRef_t const&)
    : m_pT (pT)
{
    // empty
}


template<typename T>
/*ctor*/
py_ptr<T>::py_ptr (
    py_ptr<T> const& ref)
    : m_pT (ref.m_pT)
{
    if (0 != m_pT)
    {
        Py_INCREF (m_pT);
    }
}


template<typename T>
/*dtor*/
py_ptr<T>::~py_ptr ()
{
    if (0 != m_pT)
    {
        Py_DECREF (m_pT);
    }
    m_pT = 0;
}


template<typename T>
py_ptr<T>&
py_ptr<T>::operator = (
    pointer pT)
{
    if (m_pT != pT)
    {
        if (0 != pT)
        {
            Py_INCREF (pT);
        }
        if (0 != m_pT)
        {
            Py_DECREF (m_pT);
        }
        m_pT = pT;
    }
    return *this;
}


template<typename T>
py_ptr<T>&
py_ptr<T>::operator = (
    py_ptr const& rhs)
{
    return operator = (rhs.m_pT);
}


template<typename T>
void
py_ptr<T>::swap (
    py_ptr& other)
{
    std::swap (m_pT, other.m_pT);
}


template<typename T>
void
py_ptr<T>::reset ()
{
    if (0 != m_pT)
    {
        Py_DECREF (m_pT);
        m_pT = 0;
    }
}


template<typename T>
void
py_ptr<T>::reset (
    pointer pT)
{
    if (m_pT != pT)
    {
        if (0 != pT)
        {
            Py_INCREF (pT);
        }
        if (0 != m_pT)
        {
            Py_DECREF (m_pT);
        }
        m_pT = pT;
    }
}


template<typename T>
typename py_ptr<T>::pointer
py_ptr<T>::release ()
{
    pointer pT = m_pT;
    m_pT = 0;
    return pT;
}


template<typename T>
typename py_ptr<T>::pointer
py_ptr<T>::get () const
{
    return m_pT;
}


template<typename T>
typename py_ptr<T>::element_type&
py_ptr<T>::operator * () const
{
    return *m_pT;
}


template<typename T>
typename py_ptr<T>::pointer
py_ptr<T>::operator -> () const
{
    return m_pT;
}


template<typename T>
/*bool*/
py_ptr<T>::operator bool () const
{
    return 0 != m_pT;
}


template<typename T>
bool
py_ptr<T>::operator ! () const
{
    return 0 == m_pT;
}


} // namespace scx


#ifndef COMP_OP_DEF
#define COMP_OP_DEF(COMP_OP) \
    template<typename T> \
    bool operator COMP_OP (scx::py_ptr<T> const& lhs, \
                           T const* const rhs) \
    { \
        return lhs.get () COMP_OP rhs; \
    } \
     \
    template<typename T> \
    bool operator COMP_OP (T const* const lhs, \
                           scx::py_ptr<T> const& rhs) \
    { \
        return rhs COMP_OP rhs.get (); \
    } \
     \
    template<typename T> \
    bool operator COMP_OP (scx::py_ptr<T> const& lhs, \
                           scx::py_ptr<T> const& rhs) \
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


template<typename T>
void
swap (
    scx::py_ptr<T>& left,
    scx::py_ptr<T>& right)
{
    left.swap (right);
}


} // namespace std


#endif // INCLUDED_PY_PTR_HPP
