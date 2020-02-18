/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_wqlcxx_h
#define _omi_wqlcxx_h

#include <cstddef>
#include <string>
#include <vector>

#if defined(__GNUC__)
# define WQLCXX_EXPORT __attribute__((visibility("default")))
# define WQLCXX_IMPORT /* empty */
#elif defined(sun)
# define WQLCXX_EXPORT __global
# define WQLCXX_IMPORT /* empty */
#else
# define WQLCXX_EXPORT
# define WQLCXX_IMPORT
#endif

#ifdef BUILDING_WQLCXX
#  define WQLCXX_LINKAGE WQLCXX_EXPORT
#else
#  define WQLCXX_LINKAGE WQLCXX_IMPORT
#endif
#define WQLCXX_BEGIN namespace wqlcxx {
#define WQLCXX_END }

WQLCXX_BEGIN

/* Represents the type of values produced by WQLValueSource::Lookup() */
enum WQLType
{
    WQLTYPE_BOOLEAN,
    WQLTYPE_INTEGER,
    WQLTYPE_REAL,
    WQLTYPE_STRING
};

/* Represents values produced by WQLValueSource::Lookup() */
class WQLValue
{
public:
    bool booleanValue;
    long long integerValue;
    double realValue;
    std::string stringValue;
};

/* Instances of this class lookup values for properties. The user must derive
 * from this class and provide implementations for all pure virtual functions.
 * This instance is passed to WQL::Eval(), which in turn calls these virtual
 * functions.
 */
class WQLCXX_LINKAGE WQLValueSource
{
public:

    virtual ~WQLValueSource();

    virtual bool LookupValue(
        const char* name,
        WQLType& type,
        WQLValue& value) = 0;
};

class WQLCXX_LINKAGE WQL
{
public:

    /* Parse the given WQL text and return a new WQL instance. The caller
     * must eventually pass the instance to delete.
     */
    static WQL* Parse(const char* text);

    /* Destroy instance of WQL (created by Parse) */
    static void Destroy(WQL* wql);

    /* Get the classname given by the FROM clause */
    const char* GetClassName() const;

    /* Get the number of properties given by the SELECT list. A zero property
     * count signifies 'SELECT *', where all properties are required.
     */
    size_t GetPropertyCount() const;

    /* Get the name of the i-th property given by the SELECT list */
    const char* GetPropertyName(size_t i) const;

    /* Evaluate this instance against the given value source */
    bool Evaluate(const WQLValueSource* source) const;

    /* Dump the components of this instance to standard output */
    void Dump() const;

private:
    ~WQL();
    WQL();
    WQL(const WQL&);

    void* _rep;
};

WQLCXX_END

#endif /* _omi_wqlcxx_h */
