#include "internal_counted_ptr_test.hpp"


#include <cstdlib>
#include <internal_counted_ptr.hpp>


using test::internal_counted_ptr_test;


namespace
{


class BaseType : public util::ref_counted_obj
{
public:
    /*ctor*/ BaseType ()
    {
        ++base_count;
    }
    virtual /*dtor*/ ~BaseType ()
    {
        --base_count;
    }
    bool foo () const { return true; }
    static int base_count;
};


/*static*/ int BaseType::base_count = 0;


class DerivedType : public BaseType
{
public:
    /*ctor*/ DerivedType () { ++derived_count; }
    virtual /*dtor*/ ~DerivedType () { --derived_count; }
    static int derived_count;
};


/*static*/ int DerivedType::derived_count = 0;


struct BaseDeleter
{
    static int base_count;
    void operator () (BaseType*& pBase)
    {
        if (0 != pBase)
        {
            delete pBase;
            pBase = 0;
        }
        ++base_count;
    }

    static int derived_count;
    void operator () (DerivedType*& pDerived)
    {
        if (0 != pDerived)
        {
            delete pDerived;
            pDerived = 0;
        }
        ++derived_count;
    }
};

/*static*/ int BaseDeleter::base_count = 0;
/*static*/ int BaseDeleter::derived_count = 0;


struct DerivedDeleter
{
    static int count;
    void operator () (DerivedType*& pDerived)
    {
        if (0 != pDerived)
        {
            delete pDerived;
            pDerived = 0;
        }
        ++count;
    }
};

/*static*/ int DerivedDeleter::count = 0;


static int base_delete_count = 0;
void
BaseDelete (
    BaseType*& pBase)
{
    if (0 != pBase)
    {
        delete pBase;
        pBase = 0;
    }
    ++base_delete_count;
}


static int derived_delete_count = 0;
void
DerivedDelete (
    DerivedType*& pDerived)
{
    if (0 != pDerived)
    {
        delete pDerived;
        pDerived = 0;
    }
    ++derived_delete_count;
}


struct CompareType : public util::ref_counted_obj
{
    // empty struct
};


struct NonDeleter
{
    void operator () (CompareType*& pCompare)
    {
        pCompare = 0;
    }
};


} // namespace <unnamed>


/*ctor*/
internal_counted_ptr_test::internal_counted_ptr_test ()
{
    add_test (MAKE_TEST (internal_counted_ptr_test::test01));
    add_test (MAKE_TEST (internal_counted_ptr_test::test02));
    add_test (MAKE_TEST (internal_counted_ptr_test::test03));
    add_test (MAKE_TEST (internal_counted_ptr_test::test04));
    add_test (MAKE_TEST (internal_counted_ptr_test::test05));
    add_test (MAKE_TEST (internal_counted_ptr_test::test06));
    add_test (MAKE_TEST (internal_counted_ptr_test::test07));
    add_test (MAKE_TEST (internal_counted_ptr_test::test08));
    add_test (MAKE_TEST (internal_counted_ptr_test::test09));
    add_test (MAKE_TEST (internal_counted_ptr_test::test10));
    add_test (MAKE_TEST (internal_counted_ptr_test::test11));
    add_test (MAKE_TEST (internal_counted_ptr_test::test12));
    add_test (MAKE_TEST (internal_counted_ptr_test::test13));
    add_test (MAKE_TEST (internal_counted_ptr_test::test14));
    add_test (MAKE_TEST (internal_counted_ptr_test::test15));
    add_test (MAKE_TEST (internal_counted_ptr_test::test16));
    add_test (MAKE_TEST (internal_counted_ptr_test::test17));
    add_test (MAKE_TEST (internal_counted_ptr_test::test18));
    add_test (MAKE_TEST (internal_counted_ptr_test::test19));
    add_test (MAKE_TEST (internal_counted_ptr_test::test20));
    add_test (MAKE_TEST (internal_counted_ptr_test::test21));
    add_test (MAKE_TEST (internal_counted_ptr_test::test22));
    add_test (MAKE_TEST (internal_counted_ptr_test::test23));
    add_test (MAKE_TEST (internal_counted_ptr_test::test24));
    add_test (MAKE_TEST (internal_counted_ptr_test::test25));
    add_test (MAKE_TEST (internal_counted_ptr_test::test26));
    add_test (MAKE_TEST (internal_counted_ptr_test::test27));
    add_test (MAKE_TEST (internal_counted_ptr_test::test28));
    add_test (MAKE_TEST (internal_counted_ptr_test::test29));
    add_test (MAKE_TEST (internal_counted_ptr_test::test30));
    add_test (MAKE_TEST (internal_counted_ptr_test::test31));
    add_test (MAKE_TEST (internal_counted_ptr_test::test32));
    add_test (MAKE_TEST (internal_counted_ptr_test::test33));
    add_test (MAKE_TEST (internal_counted_ptr_test::test34));
    add_test (MAKE_TEST (internal_counted_ptr_test::test35));
    add_test (MAKE_TEST (internal_counted_ptr_test::test36));
    add_test (MAKE_TEST (internal_counted_ptr_test::test37));
    add_test (MAKE_TEST (internal_counted_ptr_test::test38));
    add_test (MAKE_TEST (internal_counted_ptr_test::test39));
    add_test (MAKE_TEST (internal_counted_ptr_test::test40));
    add_test (MAKE_TEST (internal_counted_ptr_test::test41));
    add_test (MAKE_TEST (internal_counted_ptr_test::test42));
    add_test (MAKE_TEST (internal_counted_ptr_test::test43));
    add_test (MAKE_TEST (internal_counted_ptr_test::test44));
    add_test (MAKE_TEST (internal_counted_ptr_test::test45));
    add_test (MAKE_TEST (internal_counted_ptr_test::test46));
    add_test (MAKE_TEST (internal_counted_ptr_test::test47));
    add_test (MAKE_TEST (internal_counted_ptr_test::test48));
    add_test (MAKE_TEST (internal_counted_ptr_test::test49));
    add_test (MAKE_TEST (internal_counted_ptr_test::test50));
    add_test (MAKE_TEST (internal_counted_ptr_test::test51));
    add_test (MAKE_TEST (internal_counted_ptr_test::test52));
    add_test (MAKE_TEST (internal_counted_ptr_test::test53));
    add_test (MAKE_TEST (internal_counted_ptr_test::test54));
    add_test (MAKE_TEST (internal_counted_ptr_test::test55));
    add_test (MAKE_TEST (internal_counted_ptr_test::test56));
    add_test (MAKE_TEST (internal_counted_ptr_test::test57));
    add_test (MAKE_TEST (internal_counted_ptr_test::test58));
    add_test (MAKE_TEST (internal_counted_ptr_test::test59));
    add_test (MAKE_TEST (internal_counted_ptr_test::test60));
    add_test (MAKE_TEST (internal_counted_ptr_test::test61));
    add_test (MAKE_TEST (internal_counted_ptr_test::test62));
    add_test (MAKE_TEST (internal_counted_ptr_test::test63));
    add_test (MAKE_TEST (internal_counted_ptr_test::test64));
    add_test (MAKE_TEST (internal_counted_ptr_test::test65));
    add_test (MAKE_TEST (internal_counted_ptr_test::test66));
    add_test (MAKE_TEST (internal_counted_ptr_test::test67));
}


int
internal_counted_ptr_test::test01 ()
{
    // test ref_counted_obj empty constructor
    int rval = EXIT_SUCCESS;
    util::ref_counted_obj obj;
    if (0 != obj.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test02 ()
{
    // test ref_counted_obj::inc_ref_count
    int rval = EXIT_SUCCESS;
    util::ref_counted_obj obj;
    if (1 != obj.inc_ref_count () ||
        1 != obj.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test03 ()
{
    // test ref_counted_obj::dec_ref_count
    int rval = EXIT_SUCCESS;
    util::ref_counted_obj obj;
    obj.inc_ref_count ();
    if (0 != obj.dec_ref_count () ||
        0 != obj.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test04 ()
{
    // test ref_counted_obj copy constructor
    int rval = EXIT_SUCCESS;
    util::ref_counted_obj obj0;
    obj0.inc_ref_count ();
    util::ref_counted_obj obj1 (obj0);
    if (1 != obj0.use_count () ||
        0 != obj1.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test05 ()
{
    // test ref_counted_obj assignment operator
    int rval = EXIT_SUCCESS;
    util::ref_counted_obj obj0;
    obj0.inc_ref_count ();
    obj0.inc_ref_count ();
    util::ref_counted_obj obj1;
    obj1.inc_ref_count ();
    obj0 = obj1;
    if (2 != obj0.use_count () ||
        1 != obj1.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// all of the tests of internal counted pointer include tests using
// 1 - util::default_delete
// 2 - a defined delete functor
// 3 - a delete function (where applicable)
int
internal_counted_ptr_test::test06 ()
{
    // test internal_counted_ptr empty constructor
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        // this creates a pointer with a function that is not initialized and
        // will cause a seg fault if assigned a value
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test07 ()
{
    // test internal_counted_ptr value constructor with NULL
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test08 ()
{
    // test internal_counted_ptr value constructor
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test09 ()
{
    // test internal_counted_ptr with value and deleter constructor
    int rval = EXIT_SUCCESS;
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (
            pType, BaseDeleter ());
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase (
            pType, BaseDelete);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test10 ()
{
    // test internal_counted_ptr value constructor with cast from derived type
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test11 ()
{
    // test internal_counted_ptr value constructor with cast from derived type
    // and deleter
    int rval = EXIT_SUCCESS;
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (
            pType, BaseDeleter ());
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase (
            pType, BaseDelete);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test12 ()
{
    // test copy constructor with empty pointer
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase1;
        util::internal_counted_ptr<BaseType> pBase2 (pBase1);
        if (NULL != pBase1.get () ||
            NULL != pBase2.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase2 (pBase1);
        if (NULL != pBase1.get () ||
            NULL != pBase2.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase2 (
            pBase1);
        if (NULL != pBase1.get () ||
            NULL != pBase2.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test13 ()
{
    // test copy constructor with a pointer that has a value
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pBase = new BaseType;
        util::internal_counted_ptr<BaseType> pBase1 (pBase);
        util::internal_counted_ptr<BaseType> pBase2 (pBase1);
        if (1 != BaseType::base_count ||
            pBase1.get () != pBase ||
            pBase2.get () != pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pBase = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pBase);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase2 (pBase1);
        if (1 != BaseType::base_count ||
            pBase1.get () != pBase ||
            pBase2.get () != pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pBase = new BaseType;
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase1 (
            pBase, BaseDelete);
        util::internal_counted_ptr<BaseType, void(*)(BaseType*&)> pBase2 (
            pBase1);
        if (1 != BaseType::base_count ||
            pBase1.get () != pBase ||
            pBase2.get () != pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test14 ()
{
    // test the copy constructor which casts from an internal_counter_ptr to
    // a derived type (empty case)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<DerivedType> pDerived;
        util::internal_counted_ptr<BaseType> pBase (pDerived);
        if (NULL != pDerived.get () ||
            NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<DerivedType, BaseDeleter> pDerived;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pDerived);
        if (NULL != pBase.get () ||
            NULL != pDerived.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != BaseDeleter::base_count ||
        0 != BaseDeleter::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pDerived);
        if (NULL != pBase.get () ||
            NULL != pDerived.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != BaseDeleter::base_count ||
        0 != BaseDeleter::derived_count ||
        0 != DerivedDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test15 ()
{
    // test the copy constructor which casts from an internal_counter_ptr to
    // a derived type (value assigned case)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType> pDerived (pType);
        util::internal_counted_ptr<BaseType> pBase (pDerived);
        if (1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            pDerived.get () != pType ||
            pBase.get () != pType)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType, BaseDeleter> pDerived (pType);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pDerived);
        if (1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            pDerived.get () != pType ||
            pBase.get () != pType)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count + BaseDeleter::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived (pType);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pDerived);
        if (1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            pDerived.get () != pType ||
            pBase.get () != pType)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != (BaseDeleter::base_count +
              BaseDeleter::derived_count +
              DerivedDeleter::count))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test16 ()
{
    // test the assignment operator (value)
    // assign nothing to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        pBase = NULL;
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        pBase = NULL;
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase = NULL;
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test17 ()
{
    // test the assignment operator (value)
    // assign something to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test18 ()
{
    // test the assignment operator (value)
    // assign nothing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        pBase = NULL;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        pBase = NULL;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        pBase = NULL;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test19 ()
{
    // test the assignment operator (value)
    // assign something to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test20 ()
{
    // test the assignment operator (value)
    // assign the same thing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        BaseType* pType = pBase.get ();
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        BaseType* pType = pBase.get ();
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        BaseType* pType = pBase.get ();
        pBase = pType;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test21 ()
{
    // test the assignment operator (reference)
    // assign nothing to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0;
        util::internal_counted_ptr<BaseType> pBase1;
        pBase0 = pBase1;
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1;
        pBase0 = pBase1;
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase0 = pBase1;
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test22 ()
{
    // test the assignment operator (reference)
    // assign something to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0;
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0;
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test23 ()
{
    // test the assignment operator (reference)
    // assign nothing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0 (new BaseType);
        util::internal_counted_ptr<BaseType> pBase1;
        pBase0 = pBase1;
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (new BaseType);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1;
        pBase0 = pBase1;
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            new BaseType, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase0 = pBase1;
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test24 ()
{
    // test the assignment operator (reference)
    // assign something to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0 (new BaseType);
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (new BaseType);
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            new BaseType, BaseDelete);
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test25 ()
{
    // test the assignment operator (reference)
    // assign the same thing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0 (new BaseType);
        BaseType* pType = pBase0.get ();
        util::internal_counted_ptr<BaseType> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (new BaseType);
        BaseType* pType = pBase0.get ();
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            new BaseType, BaseDelete);
        BaseType* pType = pBase0.get ();
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase0 = pBase1;
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test26 ()
{
    // test the assignment operator (value cast)
    // assign nothing to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        DerivedType* pDerived = NULL;
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        DerivedType* pDerived = NULL;
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        DerivedType* pDerived = NULL;
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test27 ()
{
    // test the assignment operator (value cast)
    // assign something to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test28 ()
{
    // test the assignment operator (value cast)
    // assign nothing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        DerivedType* pDerived = NULL;
        pBase = pDerived;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        DerivedType* pDerived = NULL;
        pBase = pDerived;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        DerivedType* pDerived = NULL;
        pBase = pDerived;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test29 ()
{
    // test the assignment operator (value cast)
    // assign something to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        2 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        DerivedType* pDerived = new DerivedType;
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        2 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test30 ()
{
    // test the assignment operator (value cast)
    // assign the same thing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pDerived = new DerivedType;
        util::internal_counted_ptr<BaseType> pBase (pDerived);
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pDerived = new DerivedType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pDerived);
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pDerived = new DerivedType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pDerived, BaseDelete);
        pBase = pDerived;
        if (pDerived != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test31 ()
{
    // test the assignment operator (reference cast)
    // assign nothing to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        util::internal_counted_ptr<DerivedType> pDerived;
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived;
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != BaseDeleter::base_count ||
        0 != BaseDeleter::derived_count ||
        0 != DerivedDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
            pDerived (NULL, DerivedDelete);
        pBase = pDerived;
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        0 != base_delete_count ||
        0 != derived_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test32 ()
{
    // test the assignment operator (reference cast)
    // assign something to nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType> pBase;
        util::internal_counted_ptr<DerivedType> pDerived (pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived (
            pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != BaseDeleter::base_count ||
            0 != BaseDeleter::derived_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != (BaseDeleter::base_count +
              BaseDeleter::derived_count +
              DerivedDeleter::count))
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
            pDerived (pType , DerivedDelete);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != (base_delete_count + derived_delete_count))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test33 ()
{
    // test the assignment operator (reference cast)
    // assign nothing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        util::internal_counted_ptr<DerivedType> pDerived;
        pBase = pDerived;
        if (NULL != pBase.get () ||
            NULL != pDerived.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived;
        pBase = pDerived;
        if (NULL != pBase.get () ||
            NULL != pDerived.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count ||
            1 != BaseDeleter::base_count ||
            0 != BaseDeleter::derived_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != BaseDeleter::base_count ||
        0 != BaseDeleter::derived_count ||
        0 != DerivedDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
            pDerived (NULL, DerivedDelete);
        pBase = pDerived;
        if (NULL != pBase.get () ||
            NULL != pDerived.get () ||
            0 != BaseType::base_count ||
            0 != DerivedType::derived_count ||
            1 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != base_delete_count ||
        0 != derived_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test34 ()
{
    // test the assignment operator (reference cast)
    // assign something to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType> pDerived (pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived (
            pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != BaseDeleter::base_count ||
            0 != BaseDeleter::derived_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        ((1 != BaseDeleter::base_count && 1 != DerivedDeleter::count) &&
         (2 != BaseDeleter::base_count && 0 != DerivedDeleter::count)))
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
            pDerived (pType, DerivedDelete);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        ((1 != base_delete_count && 1 != derived_delete_count) &&
         (2 != base_delete_count && 0 != derived_delete_count)))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test35 ()
{
    // test the assignment operator (reference cast)
    // assign the same thing to something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        util::internal_counted_ptr<DerivedType> pDerived (pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        BaseDeleter::derived_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived (
            pType);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != BaseDeleter::base_count ||
            0 != BaseDeleter::derived_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != (BaseDeleter::base_count +
              BaseDeleter::derived_count +
              DerivedDeleter::count))
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
            pDerived (pType, DerivedDelete);
        pBase = pDerived;
        if (pType != pBase.get () ||
            pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            0 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        1 != (base_delete_count + derived_delete_count))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test36 ()
{
    // test assignment to itself (empty)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        pBase = pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_SUCCESS;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        pBase = pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_SUCCESS;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase = pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_SUCCESS;
    }
    return rval;
}


int
internal_counted_ptr_test::test37 ()
{
    // test assignment to itself (has value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        pBase = pBase;
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_SUCCESS;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        pBase = pBase;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_SUCCESS;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        pBase = pBase;
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_SUCCESS;
    }
    return rval;
}


int
internal_counted_ptr_test::test38 ()
{
    // test the dtor
    // note: at this point, the dtor has already been tested many times
    //       this tests the case where multiple pointers to the same object
    //       are destroyed at different scopes
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase0 (pType);
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count ())
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<BaseType> pBase1 (pBase0);
            if (pType != pBase0.get () ||
                pType != pBase1.get () ||
                1 != BaseType::base_count ||
                2 != pType->use_count ())
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count ())
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (pType);
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count () ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pBase0);
            if (pType != pBase0.get () ||
                pType != pBase1.get () ||
                1 != BaseType::base_count ||
                2 != pType->use_count () ||
                0 != BaseDeleter::base_count)
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count () ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType, BaseDelete);
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count () ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
                pType, BaseDelete);
            if (pType != pBase0.get () ||
                pType != pBase1.get () ||
                1 != BaseType::base_count ||
                2 != pType->use_count () ||
                0 != base_delete_count)
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pBase0.get () ||
            1 != BaseType::base_count ||
            1 != pType->use_count () ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test39 ()
{
    // test the dtor (using derived and base type pointers)
    // note: at this point, the dtor has already been tested many times
    //       this tests the case where multiple pointers to the same object
    //       are destroyed at different scopes
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count ())
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<DerivedType> pDerived (pType);
            if (pType != pBase.get () ||
                pType != pDerived.get () ||
                1 != BaseType::base_count ||
                1 != DerivedType::derived_count ||
                2 != pType->use_count ())
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count ())
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        DerivedDeleter::count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<DerivedType, DerivedDeleter> pDerived (
            pType);
        if (pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count () ||
            0 != BaseDeleter::base_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
            if (pType != pDerived.get () ||
                pType != pBase.get () ||
                1 != BaseType::base_count ||
                1 != DerivedType::derived_count ||
                2 != pType->use_count () ||
                0 != BaseDeleter::base_count ||
                0 != DerivedDeleter::count)
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pDerived.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count () ||
            0 != BaseDeleter::base_count ||
            0 != DerivedDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        ((1 != BaseDeleter::base_count ||
          0 != DerivedDeleter::count) &&
         (0 != BaseDeleter::base_count ||
          1 != DerivedDeleter::count)))
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        derived_delete_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count () ||
            0 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
        {
            util::internal_counted_ptr<DerivedType, void (*)(DerivedType*&)>
                pDerived (pType, DerivedDelete);
            if (pType != pBase.get () ||
                pType != pDerived.get () ||
                1 != BaseType::base_count ||
                1 != DerivedType::derived_count ||
                2 != pType->use_count () ||
                0 != base_delete_count ||
                0 != derived_delete_count)
            {
                rval = EXIT_FAILURE;
            }
        }
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != DerivedType::derived_count ||
            1 != pType->use_count () ||
            0 != base_delete_count ||
            0 != derived_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != DerivedType::derived_count ||
        ((1 != base_delete_count ||
          0 != derived_delete_count) &&
         (0 != base_delete_count ||
          1 != derived_delete_count)))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test40 ()
{
    // test swap nothing for nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase0;
        util::internal_counted_ptr<BaseType> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test41 ()
{
    // test swap something for nothing
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase0;
        util::internal_counted_ptr<BaseType> pBase1 (pType);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test42 ()
{
    // test swap nothing for something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase0 (pType);
        util::internal_counted_ptr<BaseType> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (pType);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test43 ()
{
    // test swap something for something else
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::internal_counted_ptr<BaseType> pBase0 (pType0);
        util::internal_counted_ptr<BaseType> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (pType0);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType0, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType1, BaseDelete);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test44 ()
{
    // test swap the same thing for something
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase0 (pType);
        util::internal_counted_ptr<BaseType> pBase1 (pType);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase0 (pType);
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType, BaseDelete);
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase0.swap (pBase1);
        if (pType != pBase0.get () ||
            pType != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test45 ()
{
    // test swap with itself (empty)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test46 ()
{
    // test swap with itself (contains value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test47 ()
{
    // test empty reset (empty pointer)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test48 ()
{
    // test empty reset (pointer has value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test49 ()
{
    // test reset (empty pointer with NULL value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test50 ()
{
    // test reset (pointer has value with NULL value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test51 ()
{
    // test reset (empty pointer with value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase;
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test52 ()
{
    // test reset (pointer has value with new value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType> pBase (new BaseType);
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (new BaseType);
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            new BaseType, BaseDelete);
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            1 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test53 ()
{
    // test reset (pointer has value with the same value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != BaseDeleter::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        pBase.reset (pType);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test54 ()
{
    // test get
    int rval = EXIT_SUCCESS;
    {
        util::internal_counted_ptr<BaseType> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test55 ()
{
    // test get_deleter
    int rval = EXIT_SUCCESS;
    {
        util::internal_counted_ptr<BaseType> pBase;
        util::default_delete<BaseType> deleter = pBase.get_deleter ();
    }
    {
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        BaseDeleter deleter = pBase.get_deleter ();
    }
    {
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        void (*pDeleter)(BaseType*&) = pBase.get_deleter ();
        if (BaseDelete != pDeleter)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test56 ()
{
    // test operator *
    int rval = EXIT_SUCCESS;
    {
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType> pBase (pType);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase (pType);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseType* pType = new BaseType;
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test57 ()
{
    // test operator ->
    int rval = EXIT_SUCCESS;
    {
        util::internal_counted_ptr<BaseType> pBase;
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        if (!pBase->foo ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        if (!pBase->foo ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase = pType;
        if (pType != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        if (!pBase->foo ())
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test58 ()
{
    // test use_count
    int rval = EXIT_SUCCESS;
    util::internal_counted_ptr<BaseType> pBase0;
    if (0 != pBase0.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    pBase0 = new BaseType;
    if (1 != pBase0.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    {
        util::internal_counted_ptr<BaseType> pBase1;
        if (0 != pBase1.use_count ())
        {
            rval = EXIT_FAILURE;
        }
        if (1 != pBase0.use_count ())
        {
            rval = EXIT_FAILURE;
        }
        pBase1 = pBase0;
        if (2 != pBase1.use_count ())
        {
            rval = EXIT_FAILURE;
        }
        if (2 != pBase0.use_count ())
        {
            rval = EXIT_FAILURE;
        }
    }
    if (1 != pBase0.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    pBase0.reset ();
    if (0 != pBase0.use_count ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test59 ()
{
    // test unique
    int rval = EXIT_SUCCESS;
    util::internal_counted_ptr<BaseType> pBase0;
    if (pBase0.unique ())
    {
        rval = EXIT_FAILURE;
    }
    pBase0 = new BaseType;
    if (!pBase0.unique ())
    {
        rval = EXIT_FAILURE;
    }
    {
        util::internal_counted_ptr<BaseType> pBase1;
        if (pBase1.unique ())
        {
            rval = EXIT_FAILURE;
        }
        if (!pBase0.unique ())
        {
            rval = EXIT_FAILURE;
        }
        pBase1 = pBase0;
        if (pBase1.unique ())
        {
            rval = EXIT_FAILURE;
        }
        if (pBase0.unique ())
        {
            rval = EXIT_FAILURE;
        }
    }
    if (!pBase0.unique ())
    {
        rval = EXIT_FAILURE;
    }
    pBase0.reset ();
    if (pBase0.unique ())
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test60 ()
{
    // test operator bool
    int rval = EXIT_SUCCESS;
    {
        util::internal_counted_ptr<BaseType> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test61 ()
{
    // test operator not (!)
    int rval = EXIT_SUCCESS;
    {
        util::internal_counted_ptr<BaseType> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, BaseDeleter> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::internal_counted_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase = new BaseType;
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
internal_counted_ptr_test::test62 ()
{
    // test compare ==
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    if (!(pNull0 == pNull0) ||
        !(pVal0_0 == pVal0_0) ||
        !(pNull0 == pNull1) ||
        !(pVal0_0 == pVal0_1) ||
        !(NullPtr == pNull0) ||
        !(pNull0 == NullPtr) ||
        !(vals == pVal0_0) ||
        !(pVal0_0 == vals))
    {
        rval = EXIT_FAILURE;
    }
    if (pNull0 == pVal0_0 ||
        pVal0_0 == pNull0 ||
        pVal1 == pVal0_0 ||
        vals == pNull0 ||
        pNull0 == vals ||
        NullPtr == pVal0_0 ||
        pVal0_0 == NullPtr ||
        vals + 1 == pVal0_0 ||
        pVal0_0 == vals + 1)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test63 ()
{
    // test compare !=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    if (!(pNull0 != pVal0_0) ||
        !(pVal0_0 != pNull0) ||
        !(pVal1 != pVal0_0) ||
        !(vals != pNull0) ||
        !(pNull0 != vals) ||
        !(NullPtr != pVal0_0) ||
        !(pVal0_0 != NullPtr) ||
        !(vals + 1 != pVal0_0) ||
        !(pVal0_0 != vals + 1))
    {
        rval = EXIT_FAILURE;
    }
    if (pNull0 != pNull0 ||
        pVal0_0 != pVal0_0 ||
        pNull0 != pNull1 ||
        pVal0_0 != pVal0_1 ||
        NullPtr != pNull0 ||
        pNull0 != NullPtr ||
        vals != pVal0_0 ||
        pVal0_0 != vals)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test64 ()
{
    // test compare <
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    // null v ptr 
    if (!(pNull0 < pVal0_0) ||
        !(NullPtr < pVal0_0) ||
        !(pNull0 < vals))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal0_0 < pVal1) ||
        !(pVal0_0 < vals + 1) ||
        !(vals < pVal1))
    {
        rval = EXIT_FAILURE;
    }
    // null v ptr
    if (pVal0_0 < pNull0 ||
        pVal0_0 < NullPtr ||
        vals < pNull0)
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (pVal1 < pVal0_0 ||
        vals + 1 < pVal0_0 ||
        pVal1 < vals)
    {
        rval = EXIT_FAILURE;
    }
    // equal
    if (pNull0 < pNull1 ||
        pNull0 < NullPtr ||
        NullPtr < pNull0 ||
        pVal0_0 < pVal0_1 ||
        pVal0_0 < vals ||
        vals < pVal0_0)
    {
        rval = EXIT_FAILURE;
    }
    // same
    if (pNull0 < pNull0 ||
        pVal0_0 < pVal0_0)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test65 ()
{
    // test compare <=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    // null v ptr 
    if (!(pNull0 <= pVal0_0) ||
        !(NullPtr <= pVal0_0) ||
        !(pNull0 <= vals))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal0_0 <= pVal1) ||
        !(pVal0_0 <= vals + 1) ||
        !(vals <= pVal1))
    {
        rval = EXIT_FAILURE;
    }
    // null v ptr
    if (pVal0_0 <= pNull0 ||
        pVal0_0 <= NullPtr ||
        vals <= pNull0)
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (pVal1 <= pVal0_0 ||
        vals + 1 <= pVal0_0 ||
        pVal1 <= vals)
    {
        rval = EXIT_FAILURE;
    }
    // equal
    if (!(pNull0 <= pNull1) ||
        !(pNull0 <= NullPtr) ||
        !(NullPtr <= pNull0) ||
        !(pVal0_0 <= pVal0_1) ||
        !(pVal0_0 <= vals) ||
        !(vals <= pVal0_0))
    {
        rval = EXIT_FAILURE;
    }
    // same
    if (!(pNull0 <= pNull0) ||
        !(pVal0_0 <= pVal0_0))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test66 ()
{
    // test compare >
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    // null v ptr
    if (!(pVal0_0 > pNull0) ||
        !(pVal0_0 > NullPtr) ||
        !(vals > pNull0))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal1 > pVal0_0) ||
        !(vals + 1 > pVal0_0) ||
        !(pVal1 > vals))
    {
        rval = EXIT_FAILURE;
    }
    // null v ptr 
    if (pNull0 > pVal0_0 ||
        NullPtr > pVal0_0 ||
        pNull0 > vals)
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (pVal0_0 > pVal1 ||
        pVal0_0 > vals + 1 ||
        vals > pVal1)
    {
        rval = EXIT_FAILURE;
    }
    // equal
    if (pNull0 > pNull1 ||
        pNull0 > NullPtr ||
        NullPtr > pNull0 ||
        pVal0_0 > pVal0_1 ||
        pVal0_0 > vals ||
        vals > pVal0_0)
    {
        rval = EXIT_FAILURE;
    }
    // same
    if (pNull0 > pNull0 ||
        pVal0_0 > pVal0_0)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
internal_counted_ptr_test::test67 ()
{
    // test compare >=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull0;
    util::internal_counted_ptr<CompareType, NonDeleter> pNull1;
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::internal_counted_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
    // null v ptr
    if (!(pVal0_0 >= pNull0) ||
        !(pVal0_0 >= NullPtr) ||
        !(vals >= pNull0))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal1 >= pVal0_0) ||
        !(vals + 1 >= pVal0_0) ||
        !(pVal1 >= vals))
    {
        rval = EXIT_FAILURE;
    }
    // null v ptr 
    if (pNull0 >= pVal0_0 ||
        NullPtr >= pVal0_0 ||
        pNull0 >= vals)
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (pVal0_0 >= pVal1 ||
        pVal0_0 >= vals + 1 ||
        vals >= pVal1)
    {
        rval = EXIT_FAILURE;
    }
    // equal
    if (!(pNull0 >= pNull1) ||
        !(pNull0 >= NullPtr) ||
        !(NullPtr >= pNull0) ||
        !(pVal0_0 >= pVal0_1) ||
        !(pVal0_0 >= vals) ||
        !(vals >= pVal0_0))
    {
        rval = EXIT_FAILURE;
    }
    // same
    if (!(pNull0 >= pNull0) ||
        !(pVal0_0 >= pVal0_0))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
