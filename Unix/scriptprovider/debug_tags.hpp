#ifndef INCLUDED_DEBUG_TAGS_HPP
#define INCLUDED_DEBUG_TAGS_HPP


#include <iostream>
#include <string>


#ifndef PRINT_BOOKENDS
#define PRINT_BOOKENDS (1)
#endif


#if (PRINT_BOOKENDS)

#define SCX_BOOKEND(title) scx::BookEnd be (title)
#define SCX_BOOKEND_EX(title,sub_title) scx::BookEnd be (title, sub_title)
#define SCX_BOOKEND_PRINT(text) scx::BookEnd::print (text)

#else

#define SCX_BOOKEND(title)
#define SCX_BOOKEND_EX(title,sub_title)
#define SCX_BOOKEND_PRINT(text)

#endif


namespace scx
{


#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))


class EXPORT_PUBLIC BookEnd
{
public:
    EXPORT_PUBLIC /*ctor*/ BookEnd (
        char const* const title,
        char const* const subTitle = 0);

    EXPORT_PUBLIC explicit /*ctor*/ BookEnd (
        std::string const& title);

    EXPORT_PUBLIC /*ctor*/ BookEnd (
        std::string const& title,
        std::string const& subTitle);

    EXPORT_PUBLIC /*dtor*/ ~BookEnd ();

    template<typename T>
    static void print (T const& text);

private:
    std::string const m_Title;
    std::string const m_SubTitle;

    static unsigned int s_nIndent;
    static char const EMPTY_STRING[];
    static char const INDENT[];
};


#undef EXPORT_PUBLIC


template<typename T>
/*static*/ void
BookEnd::print (
    T const& text)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    std::cout << text << std::endl;
    std::cout.flush ();
#endif
}


}


#endif // INCLUDED_DEBUG_TAGS_HPP
