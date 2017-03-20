#include "debug_tags.hpp"


#include <iostream>
#include <sstream>


namespace scx
{


/*static*/ unsigned int BookEnd::s_nIndent (0);
/*static*/ char const BookEnd::EMPTY_STRING[] = "";
/*static*/ char const BookEnd::INDENT[] = "  ";


/*ctor*/
BookEnd::BookEnd (
    char const* const title,
    char const* const subTitle)
  : m_Title (title ? title : EMPTY_STRING)
  , m_SubTitle (subTitle ? subTitle : EMPTY_STRING)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}


/*ctor*/
BookEnd::BookEnd (
    std::string const& title)
  : m_Title (title)
  , m_SubTitle (EMPTY_STRING)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}


/*ctor*/
BookEnd::BookEnd (
    std::string const& title,
    std::string const& subTitle)
  : m_Title (title)
  , m_SubTitle (subTitle)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}


/*dtor*/
BookEnd::~BookEnd ()
{
#if (PRINT_BOOKENDS)
    --s_nIndent;
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    std::cout << "</" << m_Title << '>'  << std::endl;
#endif
}


}
