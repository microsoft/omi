#include "unique_ptr_test.hpp"


#include <cstdlib>
#include <unique_ptr.hpp>


using test::unique_ptr_test;


namespace
{


class BaseType
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


struct ArrayDeleter
{
    static int count;
    void operator () (BaseType*& pArray)
    {
        if (0 != pArray)
        {
            delete[] pArray;
            pArray = 0;
        }
        ++count;
    }
};

/*static*/ int ArrayDeleter::count = 0;


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


static int array_delete_count = 0;
void
ArrayDelete (
    BaseType*& pArray)
{
    if (0 != pArray)
    {
        delete[] pArray;
        pArray = 0;
    }
    ++array_delete_count;
}


struct CompareType
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
unique_ptr_test::unique_ptr_test ()
{
    add_test (MAKE_TEST (unique_ptr_test::test01));
    add_test (MAKE_TEST (unique_ptr_test::test02));
    add_test (MAKE_TEST (unique_ptr_test::test03));
    add_test (MAKE_TEST (unique_ptr_test::test04));
    add_test (MAKE_TEST (unique_ptr_test::test05));
    add_test (MAKE_TEST (unique_ptr_test::test06));
    add_test (MAKE_TEST (unique_ptr_test::test07));
    add_test (MAKE_TEST (unique_ptr_test::test08));
    add_test (MAKE_TEST (unique_ptr_test::test09));
    add_test (MAKE_TEST (unique_ptr_test::test10));
    add_test (MAKE_TEST (unique_ptr_test::test11));
    add_test (MAKE_TEST (unique_ptr_test::test12));
    add_test (MAKE_TEST (unique_ptr_test::test13));
    add_test (MAKE_TEST (unique_ptr_test::test14));
    add_test (MAKE_TEST (unique_ptr_test::test15));
    add_test (MAKE_TEST (unique_ptr_test::test16));
    add_test (MAKE_TEST (unique_ptr_test::test17));
    add_test (MAKE_TEST (unique_ptr_test::test18));
    add_test (MAKE_TEST (unique_ptr_test::test19));
    add_test (MAKE_TEST (unique_ptr_test::test20));
    add_test (MAKE_TEST (unique_ptr_test::test21));
    add_test (MAKE_TEST (unique_ptr_test::test22));
    add_test (MAKE_TEST (unique_ptr_test::test23));
    add_test (MAKE_TEST (unique_ptr_test::test24));
    add_test (MAKE_TEST (unique_ptr_test::test25));
    add_test (MAKE_TEST (unique_ptr_test::test26));
    add_test (MAKE_TEST (unique_ptr_test::test27));
    add_test (MAKE_TEST (unique_ptr_test::test28));
    add_test (MAKE_TEST (unique_ptr_test::test29));
    add_test (MAKE_TEST (unique_ptr_test::test30));
    add_test (MAKE_TEST (unique_ptr_test::test31));
    add_test (MAKE_TEST (unique_ptr_test::test32));
    add_test (MAKE_TEST (unique_ptr_test::test33));
    add_test (MAKE_TEST (unique_ptr_test::test34));
    add_test (MAKE_TEST (unique_ptr_test::test35));
    add_test (MAKE_TEST (unique_ptr_test::test36));
    add_test (MAKE_TEST (unique_ptr_test::test37));
    add_test (MAKE_TEST (unique_ptr_test::test38));
    add_test (MAKE_TEST (unique_ptr_test::test39));
    add_test (MAKE_TEST (unique_ptr_test::test40));
    add_test (MAKE_TEST (unique_ptr_test::test41));
    add_test (MAKE_TEST (unique_ptr_test::test42));
    add_test (MAKE_TEST (unique_ptr_test::test43));
    add_test (MAKE_TEST (unique_ptr_test::test44));
    add_test (MAKE_TEST (unique_ptr_test::test45));
    add_test (MAKE_TEST (unique_ptr_test::test46));
    add_test (MAKE_TEST (unique_ptr_test::test47));
    add_test (MAKE_TEST (unique_ptr_test::test48));
    add_test (MAKE_TEST (unique_ptr_test::test49));
    add_test (MAKE_TEST (unique_ptr_test::test50));
    add_test (MAKE_TEST (unique_ptr_test::test51));
    add_test (MAKE_TEST (unique_ptr_test::test52));
    add_test (MAKE_TEST (unique_ptr_test::test53));
    add_test (MAKE_TEST (unique_ptr_test::test54));
    add_test (MAKE_TEST (unique_ptr_test::test55));
    add_test (MAKE_TEST (unique_ptr_test::test56));
    add_test (MAKE_TEST (unique_ptr_test::test57));
    add_test (MAKE_TEST (unique_ptr_test::test58));
    add_test (MAKE_TEST (unique_ptr_test::test59));
    add_test (MAKE_TEST (unique_ptr_test::test60));
    add_test (MAKE_TEST (unique_ptr_test::test61));
    add_test (MAKE_TEST (unique_ptr_test::test62));
    add_test (MAKE_TEST (unique_ptr_test::test63));
    add_test (MAKE_TEST (unique_ptr_test::test64));
    add_test (MAKE_TEST (unique_ptr_test::test65));
    add_test (MAKE_TEST (unique_ptr_test::test66));
    add_test (MAKE_TEST (unique_ptr_test::test67));
    add_test (MAKE_TEST (unique_ptr_test::test68));
    add_test (MAKE_TEST (unique_ptr_test::test69));
    add_test (MAKE_TEST (unique_ptr_test::test70));
    add_test (MAKE_TEST (unique_ptr_test::test71));
    add_test (MAKE_TEST (unique_ptr_test::test72));
    add_test (MAKE_TEST (unique_ptr_test::test73));
    add_test (MAKE_TEST (unique_ptr_test::test74));
    add_test (MAKE_TEST (unique_ptr_test::test75));
    add_test (MAKE_TEST (unique_ptr_test::test76));
    add_test (MAKE_TEST (unique_ptr_test::test77));
}


// all of the tests of internal counted pointer include tests using
// 1 - util::default_delete
// 2 - a defined delete functor
// 3 - a delete function (where applicable)
int
unique_ptr_test::test01 ()
{
    // test ctor (empty)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
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
    {
        // this creates a pointer with a function that is not initialized and
        // will cause a seg fault if assigned a value
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType, void(*)(BaseType*&)> pBase;
        if (NULL != pBase.get () ||
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
unique_ptr_test::test02 ()
{
    // test ctor (value is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase (NULL);
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (NULL);
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
    {
        base_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (NULL != pBase.get () ||
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
unique_ptr_test::test03 ()
{
    // test ctor (value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
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
unique_ptr_test::test04 ()
{
    // test ctor (value and deleter)
    int rval = EXIT_SUCCESS;
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (
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
        util::unique_ptr<BaseType, void(*)(BaseType*&)> pBase (
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
unique_ptr_test::test05 ()
{
    // test ctor (value with cast from derived type)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::unique_ptr<BaseType> pBase (pType);
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
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
unique_ptr_test::test06 ()
{
    // test ctor (value and deleter with cast from derived type)
    int rval = EXIT_SUCCESS;
    {
        BaseDeleter::base_count = 0;
        if (0 != BaseType::base_count ||
            0 != DerivedType::derived_count)
        {
            rval = EXIT_FAILURE;
        }
        DerivedType* pType = new DerivedType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType, BaseDeleter ());
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
        util::unique_ptr<BaseType, void(*)(BaseType*&)> pBase (
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
unique_ptr_test::test07 ()
{
    // test move (NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
        util::unique_ptr<BaseType>::move_type move = pBase.move ();
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        util::unique_ptr<BaseType, BaseDeleter>::move_type move = pBase.move ();
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)>::move_type move =
            pBase.move ();
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
unique_ptr_test::test08 ()
{
    // test move (non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
        util::unique_ptr<BaseType>::move_type move = pBase.move ();
        if (NULL != pBase.get () ||
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
        util::unique_ptr<BaseType, BaseDeleter>::move_type move = pBase.move ();
        if (NULL != pBase.get () ||
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)>::move_type move =
            pBase.move ();
        if (NULL != pBase.get () ||
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
unique_ptr_test::test09 ()
{
    // test ctor (move_type NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase0;
        util::unique_ptr<BaseType> pBase1 (pBase0.move ());
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0;
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pBase0.move ());
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pBase0.move ());
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
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
unique_ptr_test::test10 ()
{
    // test ctor (move_type non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase0 (pType);
        util::unique_ptr<BaseType> pBase1 (pBase0.move ());
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0 (pType);
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pBase0.move ());
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pBase0.move ());
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
unique_ptr_test::test11 ()
{
    // test assignment operator (move_type src and dest NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase0;
        util::unique_ptr<BaseType> pBase1;
        pBase1 = pBase0.move ();
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0;
        util::unique_ptr<BaseType, BaseDeleter> pBase1;
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
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
unique_ptr_test::test12 ()
{
    // test assignment operator (move_type src non-NULL and dest NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase0 (pType);
        util::unique_ptr<BaseType> pBase1;
        pBase1 = pBase0.move ();
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0 (pType);
        util::unique_ptr<BaseType, BaseDeleter> pBase1;
        pBase1 = pBase0.move ();
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);
        pBase1 = pBase0.move ();
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
unique_ptr_test::test13 ()
{
    // test assignment operator (move_type src NULL and dest non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase0;
        util::unique_ptr<BaseType> pBase1 (pType);
        pBase1 = pBase0.move ();
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase0;
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pType);
        pBase1 = pBase0.move ();
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType, BaseDelete);
        pBase1 = pBase0.move ();
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
unique_ptr_test::test14 ()
{
    // test assignment operator (move_type src and dest non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType> pBase0 (pType0);
        util::unique_ptr<BaseType> pBase1 (pType1);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
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
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase0 (pType0);
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pType1);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
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
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType0, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType1, BaseDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
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
unique_ptr_test::test15 ()
{
    // test release (NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
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
unique_ptr_test::test16 ()
{
    // test release (non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pType != pReturn ||
            1 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        delete pType;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pType != pReturn ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_FAILURE;
        }
        delete pType;
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pType != pReturn ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_FAILURE;
        }
        delete pType;
    }
    if (0 != BaseType::base_count ||
        0 != base_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test17 ()
{
    // test reset (empty pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
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
unique_ptr_test::test18 ()
{
    // test reset (NULL value and pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
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
unique_ptr_test::test19 ()
{
    // test reset (non-NULL value and pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
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
unique_ptr_test::test20 ()
{
    // test reset (empty pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
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
unique_ptr_test::test21 ()
{
    // test reset (NULL value pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
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
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
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
unique_ptr_test::test22 ()
{
    // test reset (non-NULL value pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType> pBase (pType0);
        pBase.reset (pType1);
        if (pType1 != pBase.get () ||
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
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType0);
        pBase.reset (pType1);
        if (pType1 != pBase.get () ||
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
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType0, BaseDelete);
        pBase.reset (pType1);
        if (pType1 != pBase.get () ||
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
unique_ptr_test::test23 ()
{
    // test swap (nothing for nothing)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase0;
        util::unique_ptr<BaseType> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0;
        util::unique_ptr<BaseType, BaseDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test24 ()
{
    // test swap (something for nothing)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType> pBase0;
        util::unique_ptr<BaseType> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase0;
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            NULL, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType1, BaseDelete);;
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            NULL != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test25 ()
{
    // test swap (nothing for something)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        util::unique_ptr<BaseType> pBase0 (pType0);
        util::unique_ptr<BaseType> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0 (pType0);
        util::unique_ptr<BaseType, BaseDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        BaseType* pType0 = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType0, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            NULL, BaseDelete);;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pType0 != pBase1.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test26 ()
{
    // test swap (something for something else)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType0 = new BaseType;
        BaseType* pType1 = new BaseType;
        util::unique_ptr<BaseType> pBase0 (pType0);
        util::unique_ptr<BaseType> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase0 (pType0);
        util::unique_ptr<BaseType, BaseDeleter> pBase1 (pType1);
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase0 (
            pType0, BaseDelete);
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase1 (
            pType1, BaseDelete);;
        pBase0.swap (pBase1);
        if (pType1 != pBase0.get () ||
            pType0 != pBase1.get () ||
            2 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test27 ()
{
    // test swap (itself NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test28 ()
{
    // test swap (itself non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != BaseDeleter::base_count)
        {
            rval = EXIT_SUCCESS;
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        pBase.swap (pBase);
        if (pType != pBase.get () ||
            1 != BaseType::base_count ||
            0 != base_delete_count)
        {
            rval = EXIT_SUCCESS;
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
unique_ptr_test::test29 ()
{
    // test get
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
        if (pType != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test30 ()
{
    // test get_deleter
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType> pBase;
        util::default_delete<BaseType> deleter = pBase.get_deleter ();
    }
    {
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        BaseDeleter deleter = pBase.get_deleter ();
    }
    {
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
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
unique_ptr_test::test31 ()
{
    // test operator *
    int rval = EXIT_SUCCESS;
    {
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType> pBase (pType);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, BaseDeleter> pBase (pType);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        BaseType* pType = new BaseType;
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            pType, BaseDelete);
        if (pType != &(*pBase))
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test32 ()
{
    // test operator ->
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType> pBase;
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
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
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
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
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (NULL != pBase.operator -> ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType;
        pBase.reset (pType);
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
unique_ptr_test::test33 ()
{
    // test operator bool
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test34 ()
{
    // test operator not (!)
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, BaseDeleter> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType, void (*)(BaseType*&)> pBase (
            NULL, BaseDelete);
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test35 ()
{
    // test compare ==
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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
unique_ptr_test::test36 ()
{
    // test compare !=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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
unique_ptr_test::test37 ()
{
    // test compare <
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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
unique_ptr_test::test38 ()
{
    // test compare <=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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
unique_ptr_test::test39 ()
{
    // test compare >
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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
unique_ptr_test::test40 ()
{
    // test compare >=
    CompareType vals[2];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType, NonDeleter> pNull0;
    util::unique_ptr<CompareType, NonDeleter> pNull1;
    util::unique_ptr<CompareType, NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType, NonDeleter> pVal1 (vals + 1);
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


// array specialization tests begin here
//------------------------------------------------------------------------------
int
unique_ptr_test::test41 ()
{
    // test ctor (empty)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        // this creates a pointer with a function that is not initialized and
        // will cause a seg fault if assigned a value
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType, void(*)(BaseType*&)> pBase;
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test42 ()
{
    // test ctor (value is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase (NULL);
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test43 ()
{
    // test ctor (value)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test44 ()
{
    // test ctor (value and deleter)
    int rval = EXIT_SUCCESS;
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (
            pArray, ArrayDeleter ());
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void(*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test45 ()
{
    // test move (NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
        util::unique_ptr<BaseType[]>::move_type move = pBase.move ();
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        util::unique_ptr<BaseType[], ArrayDeleter>::move_type move =
            pBase.move ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)>::move_type move =
            pBase.move ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test46 ()
{
    // test move (non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pType);
        util::unique_ptr<BaseType[]>::move_type move = pBase.move ();
        if (NULL != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pType);
        util::unique_ptr<BaseType[], ArrayDeleter>::move_type move =
            pBase.move ();
        if (NULL != pBase.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pType, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)>::move_type move =
            pBase.move ();
        if (NULL != pBase.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test47 ()
{
    // test ctor (move_type NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase0;
        util::unique_ptr<BaseType[]> pBase1 (pBase0.move ());
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0;
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pBase0.move ());
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pBase0.move ());
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test48 ()
{
    // test ctor (move_type non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0 (pArray);
        util::unique_ptr<BaseType[]> pBase1 (pBase0.move ());
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0 (pArray);
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pBase0.move ());
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            pArray, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pBase0.move ());
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test49 ()
{
    // test assignment operator (move_type src and dest NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase0;
        util::unique_ptr<BaseType[]> pBase1;
        pBase1 = pBase0.move ();
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0;
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1;
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            NULL, ArrayDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test50 ()
{
    // test assignment operator (move_type src non-NULL and dest NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0 (pArray);
        util::unique_ptr<BaseType[]> pBase1;
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0 (pArray);
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1;
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            pArray, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            NULL, ArrayDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test51 ()
{
    // test assignment operator (move_type src NULL and dest non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0;
        util::unique_ptr<BaseType[]> pBase1 (pArray);
        pBase1 = pBase0.move ();
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pType = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0;
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pType);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            1 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pArray, ArrayDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            1 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test52 ()
{
    // test assignment operator (move_type src and dest non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0 (pArray0);
        util::unique_ptr<BaseType[]> pBase1 (pArray1);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0 (pArray0);
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pArray1);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count ||
            1 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            pArray0, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pArray1, ArrayDelete);
        pBase1 = pBase0.move ();
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count ||
            1 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test53 ()
{
    // test release (NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            NULL != pReturn ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test54 ()
{
    // test release (non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pArray != pReturn ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        delete[] pArray;
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pArray != pReturn ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
        delete[] pArray;
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        BaseType* pReturn = pBase.release ();
        if (NULL != pBase.get () ||
            pArray != pReturn ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
        delete[] pArray;
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test55 ()
{
    // test reset (empty pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test56 ()
{
    // test reset (NULL value and pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test57 ()
{
    // test reset (non-NULL value and pointer is NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase;
        pBase.reset (pArray);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        pBase.reset (pArray);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        pBase.reset (pArray);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test58 ()
{
    // test reset (empty pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        pBase.reset ();
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test59 ()
{
    // test reset (NULL value pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
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
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        pBase.reset (NULL);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            1 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test60 ()
{
    // test reset (non-NULL value pointer is non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray0);
        pBase.reset (pArray1);
        if (pArray1 != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray0);
        pBase.reset (pArray1);
        if (pArray1 != pBase.get () ||
            5 != BaseType::base_count ||
            1 != ArrayDeleter::count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray0, ArrayDelete);
        pBase.reset (pArray1);
        if (pArray1 != pBase.get () ||
            5 != BaseType::base_count ||
            1 != array_delete_count)
        {
            rval = EXIT_FAILURE;
        }
    }
    if (0 != BaseType::base_count ||
        2 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test61 ()
{
    // test swap (nothing for nothing)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase0;
        util::unique_ptr<BaseType[]> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0;
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            NULL, ArrayDelete);;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            NULL != pBase1.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test62 ()
{
    // test swap (something for nothing)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0;
        util::unique_ptr<BaseType[]> pBase1 (pArray1);
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            NULL != pBase1.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0;
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pArray1);
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            NULL != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            NULL, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pArray1, ArrayDelete);;
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            NULL != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test63 ()
{
    // test swap (nothing for something)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0 (pArray0);
        util::unique_ptr<BaseType[]> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0 (pArray0);
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            pArray0, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            NULL, ArrayDelete);;
        pBase0.swap (pBase1);
        if (NULL != pBase0.get () ||
            pArray0 != pBase1.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test64 ()
{
    // test swap (something for something else)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase0 (pArray0);
        util::unique_ptr<BaseType[]> pBase1 (pArray1);
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            pArray0 != pBase1.get () ||
            10 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase0 (pArray0);
        util::unique_ptr<BaseType[], ArrayDeleter> pBase1 (pArray1);
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            pArray0 != pBase1.get () ||
            10 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        2 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray0 = new BaseType[5];
        BaseType* pArray1 = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase0 (
            pArray0, ArrayDelete);
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase1 (
            pArray1, ArrayDelete);;
        pBase0.swap (pBase1);
        if (pArray1 != pBase0.get () ||
            pArray0 != pBase1.get () ||
            10 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        2 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test65 ()
{
    // test swap (itself NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[]> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        0 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        pBase.swap (pBase);
        if (NULL != pBase.get () ||
            0 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        0 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test66 ()
{
    // test swap (itself non-NULL)
    int rval = EXIT_SUCCESS;
    {
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
        pBase.swap (pBase);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count)
    {
        rval = EXIT_FAILURE;
    }
    {
        ArrayDeleter::count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        pBase.swap (pBase);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count ||
            0 != ArrayDeleter::count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != ArrayDeleter::count)
    {
        rval = EXIT_FAILURE;
    }
    {
        array_delete_count = 0;
        if (0 != BaseType::base_count)
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        pBase.swap (pBase);
        if (pArray != pBase.get () ||
            5 != BaseType::base_count ||
            0 != array_delete_count)
        {
            rval = EXIT_SUCCESS;
        }
    }
    if (0 != BaseType::base_count ||
        1 != array_delete_count)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test67 ()
{
    // test get
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType[]> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        pBase.reset (pArray);
        if (pArray != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        pBase.reset (pArray);
        if (pArray != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        if (NULL != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
        BaseType* pArray = new BaseType[5];
        pBase.reset (pArray);
        if (pArray != pBase.get ())
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test68 ()
{
    // test get_deleter
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType[]> pBase;
        util::default_delete<BaseType[]> deleter = pBase.get_deleter ();
    }
    {
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        ArrayDeleter deleter = pBase.get_deleter ();
    }
    {
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        void (*pDeleter)(BaseType*&) = pBase.get_deleter ();
        if (ArrayDelete != pDeleter)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test69 ()
{
    // test operator []
    int rval = EXIT_SUCCESS;
    {
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[]> pBase (pArray);
        for (size_t i = 0; i < 5; ++i)
        {
            if ((pArray + i) != &(pBase[i]))
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    {
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], ArrayDeleter> pBase (pArray);
        for (size_t i = 0; i < 5; ++i)
        {
            if ((pArray + i) != &(pBase[i]))
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    {
        BaseType* pArray = new BaseType[5];
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            pArray, ArrayDelete);
        for (size_t i = 0; i < 5; ++i)
        {
            if ((pArray + i) != &(pBase[i]))
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    return rval;
}


int
unique_ptr_test::test70 ()
{
    // test operator bool
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType[]> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        if (pBase)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        bool result = pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test71 ()
{
    // test operator not (!)
    int rval = EXIT_SUCCESS;
    {
        util::unique_ptr<BaseType[]> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], ArrayDeleter> pBase;
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    {
        util::unique_ptr<BaseType[], void (*)(BaseType*&)> pBase (
            NULL, ArrayDelete);
        bool result = !pBase;
        if (!result)
        {
            rval = EXIT_FAILURE;
        }
        pBase.reset (new BaseType[5]);
        if (!pBase)
        {
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
unique_ptr_test::test72 ()
{
    // test compare ==
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
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
        vals + 5 == pVal0_0 ||
        pVal0_0 == vals + 5)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
unique_ptr_test::test73 ()
{
    // test compare !=
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
    if (!(pNull0 != pVal0_0) ||
        !(pVal0_0 != pNull0) ||
        !(pVal1 != pVal0_0) ||
        !(vals != pNull0) ||
        !(pNull0 != vals) ||
        !(NullPtr != pVal0_0) ||
        !(pVal0_0 != NullPtr) ||
        !(vals + 5 != pVal0_0) ||
        !(pVal0_0 != vals + 5))
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
unique_ptr_test::test74 ()
{
    // test compare <
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
    // null v ptr 
    if (!(pNull0 < pVal0_0) ||
        !(NullPtr < pVal0_0) ||
        !(pNull0 < vals))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal0_0 < pVal1) ||
        !(pVal0_0 < vals + 5) ||
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
        vals + 5 < pVal0_0 ||
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
unique_ptr_test::test75 ()
{
    // test compare <=
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
    // null v ptr 
    if (!(pNull0 <= pVal0_0) ||
        !(NullPtr <= pVal0_0) ||
        !(pNull0 <= vals))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal0_0 <= pVal1) ||
        !(pVal0_0 <= vals + 5) ||
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
        vals + 5 <= pVal0_0 ||
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
unique_ptr_test::test76 ()
{
    // test compare >
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
    // null v ptr
    if (!(pVal0_0 > pNull0) ||
        !(pVal0_0 > NullPtr) ||
        !(vals > pNull0))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal1 > pVal0_0) ||
        !(vals + 5 > pVal0_0) ||
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
        pVal0_0 > vals + 5 ||
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
unique_ptr_test::test77 ()
{
    // test compare >=
    CompareType vals[10];
    int rval = EXIT_SUCCESS;
    CompareType* NullPtr = NULL;
    util::unique_ptr<CompareType[], NonDeleter> pNull0;
    util::unique_ptr<CompareType[], NonDeleter> pNull1;
    util::unique_ptr<CompareType[], NonDeleter> pVal0_0 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal0_1 (vals);
    util::unique_ptr<CompareType[], NonDeleter> pVal1 (vals + 5);
    // null v ptr
    if (!(pVal0_0 >= pNull0) ||
        !(pVal0_0 >= NullPtr) ||
        !(vals >= pNull0))
    {
        rval = EXIT_FAILURE;
    }
    // ptr
    if (!(pVal1 >= pVal0_0) ||
        !(vals + 5 >= pVal0_0) ||
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
        pVal0_0 >= vals + 5 ||
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
