#ifndef INCLUDED_UTIL_DEFAULT_DELETE_HPP
#define INCLUDED_UTIL_DEFAULT_DELETE_HPP



namespace util
{


// default_delete
//------------------------------------------------------------------------------
template<typename T>
class default_delete
{
public:
    typedef T* pointer;

    void operator () (pointer& pT)
    {
        if (0 != pT)
        {
            delete pT;
            pT = 0;
        }
    }
};


// default_delete (array specialization)
//------------------------------------------------------------------------------
template<typename T>
class default_delete<T[]>
{
public:
    typedef T* pointer;

    void operator () (pointer& pT)
    {
        if (0 != pT)
        {
            delete[] pT;
            pT = 0;
        }
    }
};


}


#endif // INCLUDED_UTIL_DEFAULT_DELETE_HPP
