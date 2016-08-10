/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_datetime_h
#define _micxx_datetime_h

#include <MI.h>
#include <string.h>
#include <stdio.h>
#include "linkage.h"

MI_BEGIN_NAMESPACE

class MICXX_LINKAGE Datetime
{
public:

    // Default constructor (initializes the zero-interval).
    Datetime();

    // Initialize from MI_Datetime.
    Datetime(const MI_Datetime& x);

    // Initialize a timestamp:
    Datetime(
        MI_Uint32 year,
        MI_Uint32 month,
        MI_Uint32 day,
        MI_Uint32 hour,
        MI_Uint32 minute,
        MI_Uint32 second,
        MI_Uint32 microseconds,
        MI_Sint32 utc);

    // Initialize an interval:
    Datetime(
        MI_Uint32 days,
        MI_Uint32 hours,
        MI_Uint32 minutes,
        MI_Uint32 seconds,
        MI_Uint32 microseconds);

    // Copy constructor.
    Datetime(const Datetime& x);

    // Assignment operator.
    Datetime& operator=(const Datetime& x);

    // Destructor.
    ~Datetime();

    // Get reference to representation:
    const MI_Datetime& GetData() const;

    // Return true if a timestamp.
    bool IsTimestamp() const;

    // Clear (to zero interval)
    void Clear();

    // Set timestamp:
    bool Set(
        MI_Uint32 year,
        MI_Uint32 month,
        MI_Uint32 day,
        MI_Uint32 hour,
        MI_Uint32 minute,
        MI_Uint32 second,
        MI_Uint32 microseconds,
        MI_Sint32 utc);

    // Set interval:
    bool Set(
        MI_Uint32 days,
        MI_Uint32 hours,
        MI_Uint32 minutes,
        MI_Uint32 seconds,
        MI_Uint32 microseconds);

    // Set form a string:
    bool Set(const MI_Char* str);

    // Set to timestamp for current date and time.
    bool SetCurrent();

    // Get timestamp (return false if not a timestamp)
    bool Get(
        MI_Uint32& year,
        MI_Uint32& month,
        MI_Uint32& day,
        MI_Uint32& hour,
        MI_Uint32& minute,
        MI_Uint32& second,
        MI_Uint32& microseconds,
        MI_Sint32& utc) const;

    // Get interval (return false if not a interval)
    bool Get(
        MI_Uint32& days,
        MI_Uint32& hours,
        MI_Uint32& minutes,
        MI_Uint32& seconds,
        MI_Uint32& microseconds) const;

    // Convert to string.
    void ToString(_Pre_writable_size_(26) MI_Char buffer[26]) const;

    // Return true if the two objects are equivalent.
    bool Equal(const Datetime& x) const;

    // Print the datetime to the given output stream.
    void Print(FILE* os = stdout) const;

    // Get datetime object with current time.
    static Datetime Now();

private:
    MI_Datetime _rep;
};

inline Datetime::Datetime()
{
    memset(&_rep, 0, sizeof(_rep));
}

inline Datetime::Datetime(const MI_Datetime& x)
{
    memcpy(&_rep, &x, sizeof(MI_Datetime));
}

inline Datetime::Datetime(const Datetime& x)
{
    memcpy(&_rep, &x._rep, sizeof(_rep));
}

inline Datetime& Datetime::operator=(const Datetime& x)
{
    if (this != &x)
        memcpy(&_rep, &x._rep, sizeof(_rep));

    return *this;
}

inline Datetime::~Datetime()
{
}

inline bool Datetime::IsTimestamp() const
{
    return _rep.isTimestamp ? true : false;
}

inline void Datetime::Clear()
{
    memset(&_rep, 0, sizeof(_rep));
}

inline const MI_Datetime& Datetime::GetData() const 
{
    return _rep; 
}

inline bool operator==(const Datetime& x, const Datetime& y)
{
    return x.Equal(y);
}

inline bool operator!=(const Datetime& x, const Datetime& y)
{
    return !x.Equal(y);
}

MI_END_NAMESPACE

#endif /* _micxx_datetime_h */
