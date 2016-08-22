#include "mi_value.hpp"


namespace
{


struct KeyFinder
{
    /*ctor*/ KeyFinder (MI_Char const* const pKey)
        : m_pKey (pKey)
    {
        // empty
    }

    bool operator () (scx::MI_Value<MI_STRING>::ConstPtr pKey)
    {
        return pKey->getValue () == m_pKey;
    }

    MI_Char const* const m_pKey;
};


}


namespace scx
{


/*static*/ int MI_ValueBase::s_count = 0;


template<>
int
MI_Value<MI_BOOLEAN>::send (
    socket_wrapper& sock) const
{
    return protocol::send_boolean (m_Value, sock);
}


template<>
/*static*/ int
MI_Value<MI_BOOLEAN>::recv (
    MI_Value<MI_BOOLEAN>::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Value<MI_BOOLEAN>::recv");
    assert (ppValueOut);
    protocol::boolean_t val;
    int rval = protocol::recv_boolean (&val, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppValueOut = new MI_Value<MI_BOOLEAN> (val ? MI_TRUE : MI_FALSE);
    }
    return rval;
}


#if (MI_STRING_SPECIALIZATION)
/*ctor*/
MI_Value<MI_STRING>::MI_Value ()
    : m_Value ()
{
    //SCX_BOOKEND_EX ("MI_Value<MI_STRING>::ctor", " empty");
    // empty
}


/*ctor*/
MI_Value<MI_STRING>::MI_Value (
    MI_Char const* const val)
    : m_Value (val)
{
    //SCX_BOOKEND_EX ("MI_Value<MI_STRING>::ctor", " pointer");
    // empty
}


/*ctor*/
MI_Value<MI_STRING>::MI_Value (
    MI_Value<MI_STRING>::type_t const& val)
    : m_Value (val)
{
    //SCX_BOOKEND_EX ("MI_Value<MI_STRING>::ctor", " string");
    // empty
}


/*ctor*/
MI_Value<MI_STRING>::MI_Value (
    MI_Value<MI_STRING> const& val)
    : m_Value (val.m_Value)
{
    //SCX_BOOKEND_EX ("MI_Value<MI_STRING>::ctor", " copy");
    // empty
}


/*dtor*/
MI_Value<MI_STRING>::~MI_Value ()
{
    //SCX_BOOKEND ("MI_Value<MI_STRING>::dtor");
    // empty
}


MI_Value<MI_STRING>&
MI_Value<MI_STRING>::operator = (
    MI_Char const* const val)
{
    m_Value = val;
    SCX_BOOKEND_EX ("MI_Value<MI_STRING>::operator =", " pointer");
    return *this;
}


MI_Value<MI_STRING>&
MI_Value<MI_STRING>::operator = (
    MI_Value<MI_STRING>::type_t const& val)
{
    SCX_BOOKEND_EX ("MI_Value<MI_STRING>::operator =", " string");
    m_Value = val;
    return *this;
}


MI_Value<MI_STRING>&
MI_Value<MI_STRING>::operator = (
    MI_Value<MI_STRING> const& val)
{
    SCX_BOOKEND_EX ("MI_Value<MI_STRING>::operator =", " copy");
    m_Value = val.m_Value;
    return *this;
}


TypeID_t
MI_Value<MI_STRING>::getType () const
{
    return MI_STRING;
}


MI_Value<MI_STRING>::type_t const&
MI_Value<MI_STRING>::getValue () const
{
    return m_Value;
}


void
MI_Value<MI_STRING>::setValue (
    MI_Value<MI_STRING>::type_t const& val)
{
    //SCX_BOOKEND ("MI_Value<MI_STRING>::setValue");
    m_Value = val;
}


int
MI_Value<MI_STRING>::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_Value<MI_STRING>::send");
    return protocol::send (m_Value.c_str (), sock);
}


/*static*/ int
MI_Value<MI_STRING>::recv (
    MI_Value<MI_STRING>::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Value<MI_STRING>::recv");
    assert (ppValueOut);
    type_t val;
    int rval = protocol::recv (&val, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppValueOut = new MI_Value<MI_STRING> (val);
    }
    return rval;
}
#endif // MI_STRING_SPECIALIZATION


/*ctor*/
MI_Datetime::MI_Datetime ()
{
    //SCX_BOOKEND ("MI_Datetime::ctor");
    // empty
}


/*ctor*/
MI_Datetime::~MI_Datetime ()
{
    //SCX_BOOKEND ("MI_Datetime::dtor");
    // empty
}


TypeID_t
MI_Datetime::getType () const
{
    return MI_DATETIME;
}


int
MI_Datetime::send (
    socket_wrapper& sock) const
{
    return protocol::send_boolean (isTimestamp (), sock);
}


/*static*/ int
MI_Datetime::recv (
    MI_Datetime::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Datetime::recv");
    assert (ppValueOut);
    MI_Boolean isTimestamp;
    int rval = protocol::recv_boolean (&isTimestamp, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (isTimestamp)
        {
            MI_Timestamp::Ptr pTimestamp;
            rval = MI_Timestamp::recv (&pTimestamp, sock);
            *ppValueOut = pTimestamp;
        }
        else
        {
            MI_Interval::Ptr pInterval;
            rval = MI_Interval::recv (&pInterval, sock);
            *ppValueOut = pInterval;
        }
    }
    else
    {
        SCX_BOOKEND ("Failed to read isTimestamp");
    }
    return rval;
}


/*ctor*/
MI_Timestamp::MI_Timestamp ()
    : m_Year (0)
    , m_Month (0)
    , m_Day (0)
    , m_Hour (0)
    , m_Minute (0)
    , m_Second (0)
    , m_Microseconds (0)
    , m_Utc (0)
{
    //SCX_BOOKEND ("MI_Timestamp::ctor");
    // empty
}


/*ctor*/
MI_Timestamp::MI_Timestamp (
    MI_Uint32 const& year,
    MI_Uint32 const& month,
    MI_Uint32 const& day,
    MI_Uint32 const& hour,
    MI_Uint32 const& minute,
    MI_Uint32 const& second,
    MI_Uint32 const& microseconds,
    MI_Sint32 const& utc)
    : m_Year (year)
    , m_Month (month)
    , m_Day (day)
    , m_Hour (hour)
    , m_Minute (minute)
    , m_Second (second)
    , m_Microseconds (microseconds)
    , m_Utc (utc)
{
    //SCX_BOOKEND ("MI_Timestamp::ctor");
    // empty
}


/*dtor*/
MI_Timestamp::~MI_Timestamp ()
{
    //SCX_BOOKEND ("MI_Timestamp::dtor");
    // empty
}


MI_Datetime::Ptr
MI_Timestamp::clone () const
{
    return MI_Datetime::Ptr (new MI_Timestamp (
                    m_Year, m_Month, m_Day, m_Hour, m_Minute, m_Second,
                    m_Microseconds, m_Utc));
}


int
MI_Timestamp::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_Timestamp::send");
    int rval = MI_Datetime::send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = sock.send (
            reinterpret_cast<socket_wrapper::byte_t const*> (&m_Year),
            8 * sizeof (MI_Uint32));
    }
    return rval;
}


/*static*/ int
MI_Timestamp::recv (
    MI_Timestamp::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Timestamp::recv");
    assert (ppValueOut);
    MI_Timestamp timestamp;
    int rval = sock.recv (
        reinterpret_cast<socket_wrapper::byte_t*> (&(timestamp.m_Year)),
        8 * sizeof (MI_Uint32));
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppValueOut = new MI_Timestamp (timestamp);
    }
    return rval;
}


/*ctor*/
MI_Interval::MI_Interval ()
    : m_Days (0)
    , m_Hours (0)
    , m_Minutes (0)
    , m_Seconds (0)
    , m_Microseconds (0)
{
    //SCX_BOOKEND ("MI_Interval::ctor");
    // empty
}


/*ctor*/
MI_Interval::MI_Interval (
    MI_Uint32 const& days,
    MI_Uint32 const& hours,
    MI_Uint32 const& minutes,
    MI_Uint32 const& seconds,
    MI_Uint32 const& microseconds)
    : m_Days (days)
    , m_Hours (hours)
    , m_Minutes (minutes)
    , m_Seconds (seconds)
    , m_Microseconds (microseconds)
{
    //SCX_BOOKEND ("MI_Interval::ctor");
    // empty
}


/*dtor*/
MI_Interval::~MI_Interval ()
{
    //SCX_BOOKEND ("MI_Interval::dtor");
    // empty
}


MI_Datetime::Ptr
MI_Interval::clone () const
{
    return MI_Datetime::Ptr (new MI_Interval (
                    m_Days, m_Hours, m_Minutes, m_Seconds, m_Microseconds));
}


int
MI_Interval::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_Interval::send");
    int rval = MI_Datetime::send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = sock.send (
            reinterpret_cast<socket_wrapper::byte_t const*> (&m_Days),
            5 * sizeof (MI_Uint32));
    }
    return rval;
}


/*static*/ int
MI_Interval::recv (
    MI_Interval::Ptr* ppValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Interval::recv");
    assert (ppValueOut);
    MI_Interval timestamp;
    int rval = sock.recv (
        reinterpret_cast<socket_wrapper::byte_t*> (&(timestamp.m_Days)),
        5 * sizeof (MI_Uint32));
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppValueOut = new MI_Interval (timestamp);
    }
    return rval;
}

#if (!ARRAY_MI_VALUE)

template<>
int
MI_Array<MI_BOOLEANA>::send (
    socket_wrapper& sock) const
{
    int rval = protocol::send_item_count (m_Array.size (), sock);
    for (Array_t::const_iterator pos = m_Array.begin (),
             endPos = m_Array.end ();
         socket_wrapper::SUCCESS == rval &&
             pos != endPos;
         ++pos)
    {
        rval = protocol::send_boolean (*pos, sock);
    }
    return rval;
}


template<>
/*static*/ int
MI_Array<MI_BOOLEANA>::recv (
    MI_Array<MI_BOOLEANA>::Ptr* ppArrayOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Array<MI_BOOLEANA>::recv");
    assert (ppArrayOut);
    protocol::item_count_t count;
    int rval = protocol::recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        MI_Array<MI_BOOLEANA>::Array_t array;
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
            *ppArrayOut = new MI_Array<MI_BOOLEANA>;
            (*ppArrayOut)->m_Array.swap (array);
        }
    }
    return rval;
}

#endif // ARRAY_MI_VALUE


/*ctor*/
MI_Array<MI_DATETIMEA>::MI_Array ()
    : m_Array ()
{
    SCX_BOOKEND ("MI_Array<MI_DATETIMEA>::ctor");
    // empty
}


/*dtor*/
MI_Array<MI_DATETIMEA>::~MI_Array ()
{
    SCX_BOOKEND ("MI_Array<MI_DATETIMEA>::dtor");
    // empty
}


TypeID_t
MI_Array<MI_DATETIMEA>::getType () const
{
    return MI_DATETIMEA;
}


size_t
MI_Array<MI_DATETIMEA>::size () const
{
    return m_Array.size ();
}


MI_Array<MI_DATETIMEA>::ValuePtr_t
MI_Array<MI_DATETIMEA>::operator[] (
    size_t index) const
{
    return ValuePtr_t (m_Array[index]->clone ());
}


void
MI_Array<MI_DATETIMEA>::push_back (
    MI_Array<MI_DATETIMEA>::Value_t const& value)
{
    m_Array.push_back (value.clone ());
}


void
MI_Array<MI_DATETIMEA>::push_back (
    MI_Array<MI_DATETIMEA>::ValuePtr_t const& pValue)
{
    m_Array.push_back (pValue->clone ());
}


void
MI_Array<MI_DATETIMEA>::insert (
    size_t index,
    MI_Array<MI_DATETIMEA>::Value_t const& value)
{
    if (index < m_Array.size ())
    {
        Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.insert (pos, value.clone ());
    }
    else
    {
        push_back (value.clone ());
    }
}


void
MI_Array<MI_DATETIMEA>::insert (
    size_t index,
    MI_Array<MI_DATETIMEA>::ValuePtr_t const& pValue)
{
    if (index < m_Array.size ())
    {
        Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.insert (pos, pValue->clone ());
    }
    else
    {
        push_back (pValue->clone ());
    }
}


void
MI_Array<MI_DATETIMEA>::erase (
    size_t index)
{
    if (index < m_Array.size ())
    {
        Array_t::iterator pos = m_Array.begin ();
        for (size_t i = 0; i < index; ++i)
        {
            ++pos;
        }
        m_Array.erase (pos);
    }
}


int
MI_Array<MI_DATETIMEA>::send (
    socket_wrapper& sock) const
{
    int rval = protocol::send_item_count (m_Array.size (), sock);
    for (Array_t::const_iterator pos = m_Array.begin (),
             endPos = m_Array.end ();
         socket_wrapper::SUCCESS == rval &&
             pos != endPos;
         ++pos)
    {
        rval = (*pos)->send (sock);
    }
    return rval;
}


/*static*/ int
MI_Array<MI_DATETIMEA>::recv (
    MI_Array<MI_DATETIMEA>::Ptr* ppArrayOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Array<MI_DATETIMEA>::recv");
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
        rval = MI_Datetime::recv (&pValue, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            array.push_back (pValue);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppArrayOut = new MI_Array<MI_DATETIMEA>;
        (*ppArrayOut)->m_Array.swap (array);
    }
    return rval;
}


/*ctor*/
MI_PropertySet::MI_PropertySet ()
    : m_Keys ()
{
    // empty
}


size_t
MI_PropertySet::GetElementCount () const
{
    return m_Keys.size ();
}


bool
MI_PropertySet::ContainsElement (
    MI_Value<MI_STRING>::ConstPtr const& pKey) const
{
    std::vector<MI_Value<MI_STRING>::ConstPtr>::const_iterator endPos =
        m_Keys.end ();
    return endPos != std::find (m_Keys.begin (), endPos, pKey);
}


bool
MI_PropertySet::ContainsElement (
    MI_Type<MI_STRING>::type_t const& key) const
{
    std::vector<MI_Value<MI_STRING>::ConstPtr>::const_iterator endPos =
        m_Keys.end ();
    return endPos != std::find_if (
        m_Keys.begin (), endPos, KeyFinder (key.c_str ()));
}


bool
MI_PropertySet::ContainsElement (
    MI_Char const* const pKey) const
{
    std::vector<MI_Value<MI_STRING>::ConstPtr>::const_iterator endPos =
        m_Keys.end ();
    return endPos != std::find_if (m_Keys.begin (), endPos, KeyFinder (pKey));
}


MI_Value<MI_STRING>::ConstPtr const&
MI_PropertySet::GetElementAt (
    size_t index) const
{
    return m_Keys[index];
}


MI_Value<MI_STRING>::ConstPtr const&
MI_PropertySet::operator [] (
    size_t index) const
{
    return m_Keys[index];
}


/*static*/ int
MI_PropertySet::recv (
    MI_PropertySet::ConstPtr* ppPropertySetOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_PropertySet::recv");
    assert (ppPropertySetOut);
    protocol::item_count_t count;
    SCX_BOOKEND_PRINT ("read property count");
    int rval = protocol::recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (protocol::NULL_COUNT != count)
        {
            std::vector<MI_Value<MI_STRING>::ConstPtr> properties;
            for (protocol::item_count_t i = 0;
                 socket_wrapper::SUCCESS == rval &&
                     i < count;
                 ++i)
            {
                MI_Value<MI_STRING>::Ptr pKey;
                SCX_BOOKEND_PRINT ("read property");
                rval = MI_Value<MI_STRING>::recv (&pKey, sock);
                if (socket_wrapper::SUCCESS == rval)
                {
                    properties.push_back (pKey);
                }
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                MI_PropertySet::Ptr pPropertySet (new MI_PropertySet);
                pPropertySet->m_Keys.swap (properties);
                *ppPropertySetOut = pPropertySet;
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("property set is NULL");
            ppPropertySetOut->reset ();
        }
    }
    return rval;
}


} // namespace scx
