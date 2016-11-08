#ifndef INCLUDED_MI_VALUE_HPP
#define INCLUDED_MI_VALUE_HPP


#include "MI.h"


#include "debug_tags.hpp"
#include "internal_counted_ptr.hpp"
#include "mi_type.hpp"
#include "shared_protocol.hpp"
#include "socket_wrapper.hpp"


#include <string>
#include <sstream>
#include <vector>


#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))


namespace scx
{


class MI_ValueBase : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_ValueBase> Ptr;
    typedef util::internal_counted_ptr<MI_ValueBase const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_ValueBase ()
    {
        //SCX_BOOKEND ("MI_ValueBase::ctor");
        ++s_count;
        //std::ostringstream strm;
        //strm << "MI_ValueBase::s_count: " << s_count;
        //SCX_BOOKEND_PRINT (strm.str ().c_str ());
    }

    EXPORT_PUBLIC /*ctor*/ MI_ValueBase (MI_ValueBase const&)
    {
        //SCX_BOOKEND ("MI_ValueBase::ctor (copy)");
        ++s_count;
        //std::ostringstream strm;
        //strm << "MI_ValueBase::s_count: " << s_count;
        //SCX_BOOKEND_PRINT (strm.str ().c_str ());
    }
        
    EXPORT_PUBLIC virtual /*dtor*/ ~MI_ValueBase ()
    {
        //SCX_BOOKEND ("MI_ValueBase::dtor");
        --s_count;
        if (0 == s_count)
        {
            std::ostringstream strm;
            strm << "MI_ValueBase::s_count: " << s_count;
            SCX_BOOKEND_PRINT (strm.str ().c_str ());
        }
    }

    EXPORT_PUBLIC virtual TypeID_t getType () const = 0;

    virtual int send (socket_wrapper& sock) const = 0;

    EXPORT_PUBLIC static int s_count;
};


// class MI_Value declaration
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class EXPORT_PUBLIC MI_Value : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Value<TYPE_ID> > Ptr;
    typedef util::internal_counted_ptr<MI_Value<TYPE_ID> const> ConstPtr;

    typedef typename MI_Type<TYPE_ID>::type_t type_t;

    EXPORT_PUBLIC /*ctor*/ MI_Value ();
    EXPORT_PUBLIC explicit /*ctor*/ MI_Value (type_t const& val);
    EXPORT_PUBLIC /*ctor*/ MI_Value (MI_Value const& val);

    EXPORT_PUBLIC /*dtor*/ ~MI_Value ();

    EXPORT_PUBLIC MI_Value& operator = (type_t const& val);
    EXPORT_PUBLIC MI_Value& operator = (MI_Value const& val);

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC type_t const& getValue () const;
    EXPORT_PUBLIC void setValue (type_t const& val);

    int send (socket_wrapper& sock) const;

    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

private:
    type_t m_Value;
};


template<>
int
MI_Value<MI_BOOLEAN>::send (
    socket_wrapper& sock) const;


template<>
/*static*/ int
MI_Value<MI_BOOLEAN>::recv (
    MI_Value<MI_BOOLEAN>::Ptr* ppValueOut,
    socket_wrapper& sock);


#ifndef MI_STRING_SPECIALIZATION
#define MI_STRING_SPECIALIZATION (1)
#endif

#if (MI_STRING_SPECIALIZATION)
// class MI_Value MI_STRING specialization declaration
//------------------------------------------------------------------------------
template<>
class EXPORT_PUBLIC MI_Value<MI_STRING> : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Value<MI_STRING> > Ptr;
    typedef util::internal_counted_ptr<MI_Value<MI_STRING> const> ConstPtr;

    typedef MI_Type<MI_STRING>::type_t type_t;

    EXPORT_PUBLIC /*ctor*/ MI_Value ();
    EXPORT_PUBLIC explicit /*ctor*/ MI_Value (MI_Char const* const val);
    EXPORT_PUBLIC explicit /*ctor*/ MI_Value (type_t const& val);
    EXPORT_PUBLIC /*ctor*/ MI_Value (MI_Value const& val);

    EXPORT_PUBLIC /*dtor*/ ~MI_Value ();

    EXPORT_PUBLIC MI_Value& operator = (MI_Char const* const val);
    EXPORT_PUBLIC MI_Value& operator = (type_t const& val);
    EXPORT_PUBLIC MI_Value& operator = (MI_Value const& val);

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC type_t const& getValue () const;
    EXPORT_PUBLIC void setValue (type_t const& val);

    int send (socket_wrapper& sock) const;

    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

private:
    type_t m_Value;
};
#endif


// class MI_Datetime
//------------------------------------------------------------------------------
class EXPORT_PUBLIC MI_Datetime : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Datetime> Ptr;
    typedef util::internal_counted_ptr<MI_Datetime const> ConstPtr;

//    typedef MI_Type<MI_DATETIME>::type_t type_t;

    EXPORT_PUBLIC /*ctor*/ MI_Datetime ();
    EXPORT_PUBLIC virtual /*dtor*/ ~MI_Datetime ();

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC virtual bool isTimestamp () const = 0;

    EXPORT_PUBLIC virtual Ptr clone () const = 0;

    virtual int send (socket_wrapper& sock) const;

    static int recv (Ptr* ppValueOut, socket_wrapper& sock);
};


// class MI_Timestamp
//------------------------------------------------------------------------------
class EXPORT_PUBLIC MI_Timestamp : public MI_Datetime
{
public:
    typedef util::internal_counted_ptr<MI_Timestamp> Ptr;
    typedef util::internal_counted_ptr<MI_Timestamp const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_Timestamp ();
    EXPORT_PUBLIC /*ctor*/ MI_Timestamp (
        MI_Uint32 const& year,
        MI_Uint32 const& month,
        MI_Uint32 const& day,
        MI_Uint32 const& hour,
        MI_Uint32 const& minute,
        MI_Uint32 const& second,
        MI_Uint32 const& microseconds,
        MI_Sint32 const& utc);

    EXPORT_PUBLIC /*dtor*/ ~MI_Timestamp ();

    EXPORT_PUBLIC bool isTimestamp () const { return true; }

    EXPORT_PUBLIC MI_Uint32 const& getYear () const;
    EXPORT_PUBLIC MI_Uint32 const& getMonth () const;
    EXPORT_PUBLIC MI_Uint32 const& getDay () const;
    EXPORT_PUBLIC MI_Uint32 const& getHour () const;
    EXPORT_PUBLIC MI_Uint32 const& getMinute () const;
    EXPORT_PUBLIC MI_Uint32 const& getSecond () const;
    EXPORT_PUBLIC MI_Uint32 const& getMicroseconds () const;
    EXPORT_PUBLIC MI_Sint32 const& getUTC () const;

    EXPORT_PUBLIC void setYear (MI_Uint32 const& year);
    EXPORT_PUBLIC void setMonth (MI_Uint32 const& month);
    EXPORT_PUBLIC void setDay (MI_Uint32 const& day);
    EXPORT_PUBLIC void setHour (MI_Uint32 const& hour);
    EXPORT_PUBLIC void setMinute (MI_Uint32 const& minute);
    EXPORT_PUBLIC void setSecond (MI_Uint32 const& second);
    EXPORT_PUBLIC void setMicroseconds (MI_Uint32 const& microseconds);
    EXPORT_PUBLIC void setUTC (MI_Sint32 const& utc);

    EXPORT_PUBLIC MI_Datetime::Ptr clone () const;

    int send (socket_wrapper& sock) const;

private:
    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

    MI_Uint32 m_Year;
    MI_Uint32 m_Month;
    MI_Uint32 m_Day;
    MI_Uint32 m_Hour;
    MI_Uint32 m_Minute;
    MI_Uint32 m_Second;
    MI_Uint32 m_Microseconds;
    MI_Sint32 m_Utc;

    friend int MI_Datetime::recv (MI_Datetime::Ptr*, socket_wrapper&);
};


//class MI_Interval
//------------------------------------------------------------------------------
class EXPORT_PUBLIC MI_Interval : public MI_Datetime
{
public:
    typedef util::internal_counted_ptr<MI_Interval> Ptr;
    typedef util::internal_counted_ptr<MI_Interval const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_Interval ();
    EXPORT_PUBLIC /*ctor*/ MI_Interval (
        MI_Uint32 const& days,
        MI_Uint32 const& hours,
        MI_Uint32 const& minutes,
        MI_Uint32 const& seconds,
        MI_Uint32 const& microseconds);

    EXPORT_PUBLIC /*dtor*/ ~MI_Interval ();

    EXPORT_PUBLIC bool isTimestamp () const { return false; }

    EXPORT_PUBLIC MI_Uint32 const& getDays () const;
    EXPORT_PUBLIC MI_Uint32 const& getHours () const;
    EXPORT_PUBLIC MI_Uint32 const& getMinutes () const;
    EXPORT_PUBLIC MI_Uint32 const& getSeconds () const;
    EXPORT_PUBLIC MI_Uint32 const& getMicroseconds () const;

    EXPORT_PUBLIC void setDays (MI_Uint32 const& days);
    EXPORT_PUBLIC void setHours (MI_Uint32 const& hours);
    EXPORT_PUBLIC void setMinutes (MI_Uint32 const& minutes);
    EXPORT_PUBLIC void setSeconds (MI_Uint32 const& seconds);
    EXPORT_PUBLIC void setMicroseconds (MI_Uint32 const& microseconds);

    EXPORT_PUBLIC MI_Datetime::Ptr clone () const;

    int send (socket_wrapper& sock) const;

private:
    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

    MI_Uint32 m_Days;
    MI_Uint32 m_Hours;
    MI_Uint32 m_Minutes;
    MI_Uint32 m_Seconds;
    MI_Uint32 m_Microseconds;

    friend int MI_Datetime::recv (MI_Datetime::Ptr*, socket_wrapper&);
};


#ifndef ARRAY_MI_VALUES
#define ARRAY_MI_VALUES (0)
#endif

// class MI_Array
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class EXPORT_PUBLIC MI_Array : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Array<TYPE_ID> > Ptr;
    typedef util::internal_counted_ptr<MI_Array<TYPE_ID> const > ConstPtr;

#if (ARRAY_MI_VALUES)
    typedef MI_Value<TYPE_ID & ~MI_ARRAY> Value_t;
    typedef typename Value_t::Ptr ValuePtr_t;
    typedef typename Value_t::ConstPtr ConstValuePtr_t;
    typedef std::vector<ValuePtr_t> Array_t;
#else
    typedef typename MI_Type<TYPE_ID & ~MI_ARRAY>::type_t Value_t;
    typedef std::vector<Value_t> Array_t;
#endif

    EXPORT_PUBLIC /*ctor*/ MI_Array ();
    EXPORT_PUBLIC /*dtor*/ ~MI_Array ();

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC size_t size () const;

#if (ARRAY_MI_VALUES)
    EXPORT_PUBLIC ValuePtr_t& operator [] (size_t index);
    EXPORT_PUBLIC ConstValuePtr_t operator [] (size_t index) const;

    EXPORT_PUBLIC void push_back (Value_t* pValue);
    EXPORT_PUBLIC void push_back (ValuePtr_t const& pValue);
    EXPORT_PUBLIC void insert (size_t index, Value_t* pValue);
    EXPORT_PUBLIC void insert (size_t index, ValuePtr_t const& pValue);
#else
    EXPORT_PUBLIC Value_t& operator [] (size_t index);
    EXPORT_PUBLIC Value_t const& operator [] (size_t index) const;

    EXPORT_PUBLIC void push_back (Value_t const& value);
    EXPORT_PUBLIC void insert (size_t index, Value_t const& value);
#endif
    EXPORT_PUBLIC void erase (size_t index);

    int send (socket_wrapper& sock) const;

    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

private:
    Array_t m_Array;
};


template<>
int
MI_Array<MI_BOOLEAN>::send (
    socket_wrapper& sock) const;


template<>
/*static*/ int
MI_Array<MI_BOOLEAN>::recv (
    MI_Array<MI_BOOLEAN>::Ptr* ppValueOut,
    socket_wrapper& sock);


// class MI_Array<MI_DATETIMEA>
//------------------------------------------------------------------------------
template<>
class EXPORT_PUBLIC MI_Array<MI_DATETIMEA> : public MI_ValueBase
{
public:
    typedef util::internal_counted_ptr<MI_Array<MI_DATETIMEA> > Ptr;
    typedef util::internal_counted_ptr<MI_Array<MI_DATETIMEA> const > ConstPtr;

    typedef MI_Datetime Value_t;
    typedef Value_t::Ptr ValuePtr_t;
    typedef Value_t::ConstPtr ConstValuePtr_t;
    typedef std::vector<ValuePtr_t> Array_t;

    EXPORT_PUBLIC /*ctor*/ MI_Array ();
    EXPORT_PUBLIC /*dtor*/ ~MI_Array ();

    EXPORT_PUBLIC TypeID_t getType () const;

    EXPORT_PUBLIC size_t size () const;

    EXPORT_PUBLIC ValuePtr_t getValueAt (size_t index) const;
    EXPORT_PUBLIC void setValueAt (size_t index, Value_t const& value);
    EXPORT_PUBLIC void setValueAt (size_t index, ValuePtr_t const& pValue);

    EXPORT_PUBLIC void push_back (Value_t const& value);
    EXPORT_PUBLIC void push_back (ValuePtr_t const& pValue);
    EXPORT_PUBLIC void insert (size_t index, Value_t const& value);
    EXPORT_PUBLIC void insert (size_t index, ValuePtr_t const& pValue);

    EXPORT_PUBLIC void erase (size_t index);

    int send (socket_wrapper& sock) const;

    static int recv (Ptr* ppValueOut, socket_wrapper& sock);

private:
    Array_t m_Array;
};


// class MI_PropertySet
//------------------------------------------------------------------------------
class EXPORT_PUBLIC MI_PropertySet : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_PropertySet> Ptr;
    typedef util::internal_counted_ptr<MI_PropertySet const> ConstPtr;

    EXPORT_PUBLIC /*ctor*/ MI_PropertySet ();

    EXPORT_PUBLIC size_t GetElementCount () const;

    EXPORT_PUBLIC bool ContainsElement (
        MI_Value<MI_STRING>::ConstPtr const& pKey) const;
    EXPORT_PUBLIC bool ContainsElement (
        MI_Type<MI_STRING>::type_t const& key) const;
    EXPORT_PUBLIC bool ContainsElement (MI_Char const* const pKey) const;

    EXPORT_PUBLIC MI_Value<MI_STRING>::ConstPtr const&
    GetElementAt (size_t index) const;

    EXPORT_PUBLIC MI_Value<MI_STRING>::ConstPtr const&
    operator[] (size_t index) const;

    static int recv (ConstPtr* ppPropertySetOut, socket_wrapper& sock);

private:
    std::vector<MI_Value<MI_STRING>::ConstPtr> m_Keys;
};


// class MI_Value definitions
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
/*ctor*/
MI_Value<TYPE_ID>::MI_Value ()
    : m_Value ()
{
    //SCX_BOOKEND_EX ("MI_Value::ctor", " empty");
    // empty
}


template<TypeID_t TYPE_ID>
/*ctor*/
MI_Value<TYPE_ID>::MI_Value (
    typename MI_Value<TYPE_ID>::type_t const& val)
    : m_Value (val)
{
    //SCX_BOOKEND_EX ("MI_Value::ctor", " value");
    // empty
}


template<TypeID_t TYPE_ID>
/*ctor*/
MI_Value<TYPE_ID>::MI_Value (
    MI_Value<TYPE_ID> const& val)
    : m_Value (val.m_Value)
{
    //SCX_BOOKEND_EX ("MI_Value::ctor", " copy");
    // empty
}


template<TypeID_t TYPE_ID>
/*dtor*/
MI_Value<TYPE_ID>::~MI_Value ()
{
    //SCX_BOOKEND ("MI_Value::dtor");
    // empty
}


template<TypeID_t TYPE_ID>
MI_Value<TYPE_ID>&
MI_Value<TYPE_ID>::operator = (
    typename MI_Value<TYPE_ID>::type_t const& val)
{
    //SCX_BOOKEND_EX ("MI_Value::operator =", " value");
    m_Value = val;
    return *this;
}


template<TypeID_t TYPE_ID>
MI_Value<TYPE_ID>&
MI_Value<TYPE_ID>::operator = (
    MI_Value<TYPE_ID> const& val)
{
    //SCX_BOOKEND_EX ("MI_Value::operator =", " copy");
    m_Value = val.m_Value;
    return *this;
}


template<TypeID_t TYPE_ID>
TypeID_t
MI_Value<TYPE_ID>::getType () const
{
    return TYPE_ID;
}


template<TypeID_t TYPE_ID>
typename MI_Value<TYPE_ID>::type_t const&
MI_Value<TYPE_ID>::getValue () const
{
//    SCX_BOOKEND ("MI_Value::getValue");
//    std::ostringstream strm;
//    strm << "m_Value: " << m_Value;
//    SCX_BOOKEND_PRINT (strm.str ().c_str ());

    return m_Value;
}


template<TypeID_t TYPE_ID>
void
MI_Value<TYPE_ID>::setValue (
    typename MI_Value<TYPE_ID>::type_t const& val)
{
//    SCX_BOOKEND ("MI_Value::setValue");
    m_Value = val;
}


template<TypeID_t TYPE_ID>
int
MI_Value<TYPE_ID>::send (
    socket_wrapper& sock) const
{
    return sock.send (
        reinterpret_cast<socket_wrapper::byte_t const*> (&m_Value),
        sizeof (type_t));
}


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Value<TYPE_ID>::recv (
    typename MI_Value<TYPE_ID>::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Value<TYPE_ID>::recv");
    assert (ppValueOut);
    type_t val;
    int rval = protocol::recv (&val, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppValueOut = new MI_Value<TYPE_ID> (val);
    }
    return rval;
}


// class MI_Timestamp definitions
//------------------------------------------------------------------------------
inline MI_Uint32 const&
MI_Timestamp::getYear () const
{
    return m_Year;
}


inline MI_Uint32 const&
MI_Timestamp::getMonth () const
{
    return m_Month;
}


inline MI_Uint32 const&
MI_Timestamp::getDay () const
{
    return m_Day;
}


inline MI_Uint32 const&
MI_Timestamp::getHour () const
{
    return m_Hour;
}


inline MI_Uint32 const&
MI_Timestamp::getMinute () const
{
    return m_Minute;
}


inline MI_Uint32 const&
MI_Timestamp::getSecond () const
{
    return m_Second;
}


inline MI_Uint32 const&
MI_Timestamp::getMicroseconds () const
{
    return m_Microseconds;
}


inline MI_Sint32 const&
MI_Timestamp::getUTC () const
{
    return m_Utc;
}


inline void
MI_Timestamp::setYear (
    MI_Uint32 const& year)
{
    m_Year = year;
}


inline void
MI_Timestamp::setMonth (
    MI_Uint32 const& month)
{
    m_Month = month;
}


inline void
MI_Timestamp::setDay (
    MI_Uint32 const& day)
{
    m_Day = day;
}


inline void
MI_Timestamp::setHour (
    MI_Uint32 const& hour)
{
    m_Hour = hour;
}


inline void
MI_Timestamp::setMinute (
    MI_Uint32 const& minute)
{
    m_Minute = minute;
}


inline void
MI_Timestamp::setSecond (
    MI_Uint32 const& second)
{
    m_Second = second;
}


inline void
MI_Timestamp::setMicroseconds (
    MI_Uint32 const& microseconds)
{
    m_Microseconds = microseconds;
}


inline void
MI_Timestamp::setUTC (
    MI_Sint32 const& utc)
{
    m_Utc = utc;
}


// class MI_Interval definitions
//------------------------------------------------------------------------------
inline MI_Uint32 const&
MI_Interval::getDays () const
{
    return m_Days;
}


inline MI_Uint32 const&
MI_Interval::getHours () const
{
    return m_Hours;
}


inline MI_Uint32 const&
MI_Interval::getMinutes () const
{
    return m_Minutes;
}


inline MI_Uint32 const&
MI_Interval::getSeconds () const
{
    return m_Seconds;
}


inline MI_Uint32 const&
MI_Interval::getMicroseconds () const
{
    return m_Microseconds;
}


inline void
MI_Interval::setDays (
    MI_Uint32 const& days)
{
    m_Days = days;
}


inline void
MI_Interval::setHours (
    MI_Uint32 const& hours)
{
    m_Hours = hours;
}


inline void
MI_Interval::setMinutes (
    MI_Uint32 const& minutes)
{
    m_Minutes = minutes;
}


inline void
MI_Interval::setSeconds (
    MI_Uint32 const& seconds)
{
    m_Seconds = seconds;
}


inline void
MI_Interval::setMicroseconds (
    MI_Uint32 const& microseconds)
{
    m_Microseconds = microseconds;
}


// class MI_Array definitions
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
/*ctor*/
MI_Array<TYPE_ID>::MI_Array ()
    : m_Array ()
{
    //SCX_BOOKEND ("MI_Array::ctor");
    // empty
}


template<TypeID_t TYPE_ID>
/*dtor*/
MI_Array<TYPE_ID>::~MI_Array ()
{
    //SCX_BOOKEND ("MI_Array::dtor");
    // empty
}


template<TypeID_t TYPE_ID>
TypeID_t
MI_Array<TYPE_ID>::getType () const
{
    return TYPE_ID;
}


template<TypeID_t TYPE_ID>
size_t
MI_Array<TYPE_ID>::size () const
{
    return m_Array.size ();
}

#if (ARRAY_MI_VALUE)

template<TypeID_t TYPE_ID>
typename MI_Array<TYPE_ID>::ValuePtr_t&
MI_Array<TYPE_ID>::operator[] (
    size_t index)
{
    return m_Array[index];
}


template<TypeID_t TYPE_ID>
typename MI_Array<TYPE_ID>::ConstValuePtr_t
MI_Array<TYPE_ID>::operator[] (
    size_t index) const
{
    return ConstValuePtr_t (m_Array[index].get ());
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::push_back (
    typename MI_Array<TYPE_ID>::Value_t* pValue)
{
    m_Array.push_back (ValuePtr_t (pValue));
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::push_back (
    typename MI_Array<TYPE_ID>::ValuePtr_t const& pValue)
{
    m_Array.push_back (pValue);
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::insert (
    size_t index,
    typename MI_Array<TYPE_ID>::ValuePtr_t const& pValue)
{
    if (index < m_Array.size ())
    {
        typename Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.insert (pos, pValue);
    }
    else
    {
        push_back (pValue);
    }
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::insert (
    size_t index,
    typename MI_Array<TYPE_ID>::Value_t* pValue)
{
    insert (index, ValuePtr_t (pValue));
}

#else // ARRAY_MI_VALUE

template<TypeID_t TYPE_ID>
typename MI_Array<TYPE_ID>::Value_t&
MI_Array<TYPE_ID>::operator[] (
    size_t index)
{
    return m_Array[index];
}


template<TypeID_t TYPE_ID>
typename MI_Array<TYPE_ID>::Value_t const&
MI_Array<TYPE_ID>::operator[] (
    size_t index) const
{
    return m_Array[index];
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::push_back (
    typename MI_Array<TYPE_ID>::Value_t const& value)
{
    m_Array.push_back (value);
}


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::insert (
    size_t index,
    typename MI_Array<TYPE_ID>::Value_t const& value)
{
    if (index < m_Array.size ())
    {
        typename Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.insert (pos, value);
    }
    else
    {
        push_back (value);
    }
}

#endif // ARRAY_MI_VALUE


template<TypeID_t TYPE_ID>
void
MI_Array<TYPE_ID>::erase (
    size_t index)
{
    if (index < m_Array.size ())
    {
        typename Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.erase (pos);
    }
}

#if (ARRAY_MI_VALUE)

template<TypeID_t TYPE_ID>
int
MI_Array<TYPE_ID>::send (
    socket_wrapper& sock) const
{
    int rval = protocol::send_item_count (m_Array.size (), sock);
    for (typename Array_t::const_iterator pos = m_Array.begin (),
             endPos = m_Array.end ();
         socket_wrapper::SUCCESS == rval &&
             pos != endPos;
         ++pos)
    {
        rval = (*pos)->send (sock);
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Array<TYPE_ID>::recv (
    typename MI_Array<TYPE_ID>::Ptr* ppArrayOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Array::recv");
    assert (ppArrayOut);
    protocol::item_count_t count;
    int rval = protocol::recv_item_count (&count, sock);
    Array_t array;
    for (protocol::item_count_t i = 0;
         socket_wrapper::SUCCESS == rval &&
             i < count;
         ++i)
    {
        ValuePtr_t pValue;
        rval = MI_Value<TYPE_ID & ~MI_ARRAY>::recv (&pValue, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            array.push_back (pValue);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppArrayOut = new MI_Array<TYPE_ID>;
        (*ppArrayOut)->m_Array.swap (array);
    }
    return rval;
}

#else // ARRAY_MI_VALUE

template<TypeID_t TYPE_ID>
int
MI_Array<TYPE_ID>::send (
    socket_wrapper& sock) const
{
    int rval = protocol::send_item_count (m_Array.size (), sock);
    for (typename Array_t::const_iterator pos = m_Array.begin (),
             endPos = m_Array.end ();
         socket_wrapper::SUCCESS == rval &&
             pos != endPos;
         ++pos)
    {
        rval = sock.send (
            reinterpret_cast<socket_wrapper::byte_t const*> (&(*pos)),
            sizeof (Value_t));
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Array<TYPE_ID>::recv (
    typename MI_Array<TYPE_ID>::Ptr* ppArrayOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Array::recv");
    assert (ppArrayOut);
    protocol::item_count_t count;
    int rval = protocol::recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        Array_t array;
        array.reserve (count);
        for (protocol::item_count_t i = 0;
             socket_wrapper::SUCCESS == rval &&
                 i < count;
             ++i)
        {
            Value_t value;
            rval = protocol::recv (&value, sock);
            if (socket_wrapper::SUCCESS == rval)
            {
                array.push_back (value);
            }
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            *ppArrayOut = new MI_Array<TYPE_ID>;
            (*ppArrayOut)->m_Array.swap (array);
        }
    }
    return rval;
}

#endif // ARRAY_MI_VALUE

} // namespace scx


namespace protocol
{


inline int
send (scx::MI_Value<MI_STRING>::ConstPtr const& pValue,
      socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::send (MI_Value<MI_STRING>::ConstPtr)");
    MI_Char const* str = pValue ? pValue->getValue ().c_str () : NULL;
    return send (str, sock);
}


} // namespace protocol


template<scx::TypeID_t TYPE>
EXPORT_PUBLIC bool operator == (
    scx::MI_Value<TYPE> const& lhs,
    scx::MI_Value<TYPE> const& rhs)
{
    return lhs.getValue () == rhs.getValue ();
}


#undef EXPORT_PUBLIC


#endif // INCLUDED_MI_VALUE_HPP
