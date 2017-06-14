// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_FUNCTION_HELPER_HPP
#define INCLUDED_FUNCTION_HELPER_HPP


#include "internal_counted_ptr.hpp"

#include "debug_tags.hpp"


namespace util
{


template<typename RET,
         typename ARG0 = void, typename ARG1 = void, typename ARG2 = void,
         typename ARG3 = void, typename ARG4 = void, typename ARG5 = void,
         typename ARG6 = void, typename ARG7 = void, typename ARG8 = void,
         typename ARG9 = void>
class function_base : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, ARG8, ARG9> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, ARG8, ARG9> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, ARG7, ARG8, ARG9) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6, typename ARG7, typename ARG8>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, ARG7, ARG8, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, ARG8, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, ARG8, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, ARG7, ARG8) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6, typename ARG7>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, ARG7, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, ARG7) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, ARG6) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4,
                    ARG5) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, ARG4,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3, ARG4) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3>
class function_base<RET,
                    ARG0, ARG1, ARG2, ARG3, void,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, void,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, ARG3, void,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2, ARG3) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1, typename ARG2>
class function_base<RET,
                    ARG0, ARG1, ARG2, void, void,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, void, void,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, ARG2, void, void,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1, ARG2) const = 0;
};


template<typename RET,
         typename ARG0, typename ARG1>
class function_base<RET,
                    ARG0, ARG1, void, void, void,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, void, void, void,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, ARG1, void, void, void,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0, ARG1) const = 0;
};


template<typename RET,
         typename ARG0>
class function_base<RET,
                    ARG0, void, void, void, void,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, void, void, void, void,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      ARG0, void, void, void, void,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn (ARG0) const = 0;
};


template<typename RET>
class function_base<RET,
                    void, void, void, void, void,
                    void, void, void, void, void>
    : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<
        function_base<RET,
                      void, void, void, void, void,
                      void, void, void, void, void> > Ptr;
    typedef util::internal_counted_ptr<
        function_base<RET,
                      void, void, void, void, void,
                      void, void, void, void, void> const > ConstPtr;

    virtual /*dtor*/ ~function_base () {}

    virtual RET fn () const = 0;
};


template<typename T, typename RET,
         typename ARG0 = void, typename ARG1 = void, typename ARG2 = void,
         typename ARG3 = void, typename ARG4 = void, typename ARG5 = void,
         typename ARG6 = void, typename ARG7 = void, typename ARG8 = void,
         typename ARG9 = void>
class function_holder
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           ARG5, ARG6, ARG7, ARG8, ARG9>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   ARG5, ARG6, ARG7, ARG8, ARG9>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, ARG5, ARG6, ARG7,
                                   ARG8, ARG9>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4,
            ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8, ARG9 arg9) const
    {
        return m_Op (arg0, arg1, arg2, arg3, arg4,
                     arg5, arg6, arg7, arg8, arg9);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6, typename ARG7, typename ARG8>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, ARG8, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           ARG5, ARG6, ARG7, ARG8, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   ARG5, ARG6, ARG7, ARG8, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, ARG5, ARG6, ARG7,
                                   ARG8, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4,
            ARG5 arg5, ARG6 arg6, ARG7 arg7, ARG8 arg8) const
    {
        return m_Op (arg0, arg1, arg2, arg3, arg4,
                     arg5, arg6, arg7, arg8);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6, typename ARG7>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, ARG7, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           ARG5, ARG6, ARG7, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   ARG5, ARG6, ARG7, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, ARG5, ARG6, ARG7,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4,
            ARG5 arg5, ARG6 arg6, ARG7 arg7) const
    {
        return m_Op (arg0, arg1, arg2, arg3, arg4,
                     arg5, arg6, arg7);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5,
         typename ARG6>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, ARG6, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           ARG5, ARG6, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   ARG5, ARG6, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, ARG5, ARG6, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4,
            ARG5 arg5, ARG6 arg6) const
    {
        return m_Op (arg0, arg1, arg2, arg3, arg4,
                     arg5, arg6);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4, typename ARG5>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      ARG5, void, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           ARG5, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   ARG5, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, ARG5, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        SCX_BOOKEND ("function_holder::ctor");
        // empty
    }

    /*ctor*/ function_holder (function_holder const& ref)
        : m_Op (ref.m_Op)
    {
        SCX_BOOKEND ("function_holder::ctor (copy)");
        // empty
    }

    /*dtor*/ ~function_holder ()
    {
        SCX_BOOKEND ("function_holder::dtor");
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4,
            ARG5 arg5) const
    {
        SCX_BOOKEND ("function_holder::fn");
        return m_Op (arg0, arg1, arg2, arg3, arg4,
                     arg5);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3, typename ARG4>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, ARG4,
                      void, void, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, ARG4,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, ARG4,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   ARG4, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) const
    {
        return m_Op (arg0, arg1, arg2, arg3, arg4);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2,
         typename ARG3>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, ARG3, void,
                      void, void, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, ARG3, void,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3, void,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, ARG3,
                                   void, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3) const
    {
        return m_Op (arg0, arg1, arg2, arg3);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1, typename ARG2>
class function_holder<T, RET,
                      ARG0, ARG1, ARG2, void, void,
                      void, void, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, ARG2, void, void,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, void, void,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, ARG2, void,
                                   void, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1, ARG2 arg2) const
    {
        return m_Op (arg0, arg1, arg2);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0, typename ARG1>
class function_holder<T, RET,
                      ARG0, ARG1, void, void, void,
                      void, void, void, void, void>
    : public function_base<RET,
                           ARG0, ARG1, void, void, void,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, ARG1, void, void, void,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, ARG1, void, void,
                                   void, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0, ARG1 arg1) const
    {
        return m_Op (arg0, arg1);
    }

private:
    T m_Op;
};


template<typename T, typename RET,
         typename ARG0>
class function_holder<T, RET,
                      ARG0, void, void, void, void,
                      void, void, void, void, void>
    : public function_base<RET,
                           ARG0, void, void, void, void,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   ARG0, void, void, void, void,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   ARG0, void, void, void,
                                   void, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn (ARG0 arg0) const
    {
        return m_Op (arg0);
    }

private:
    T m_Op;
};


template<typename T, typename RET>
class function_holder<T, RET,
                      void, void, void, void, void,
                      void, void, void, void, void>
    : public function_base<RET,
                           void, void, void, void, void,
                           void, void, void, void, void>
{
public:
    typedef typename function_base<RET,
                                   void, void, void, void, void,
                                   void, void, void, void, void>::Ptr Ptr;
    typedef typename function_base<RET,
                                   void, void, void, void,
                                   void, void, void, void,
                                   void, void>::ConstPtr ConstPtr;

    /*ctor*/ function_holder (
        typename util::conditional<
            util::is_reference<T>::value, T, T const&>::type op)
        : m_Op (op)
    {
        // empty
    }

    RET fn () const
    {
        return m_Op ();
    }

private:
    T m_Op;
};


} // namespace util


#endif // INCLUDED_FUNCTION_HELPER_HPP
