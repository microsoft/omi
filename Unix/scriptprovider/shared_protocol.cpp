#include "shared_protocol.hpp"


#include <sstream>


namespace protocol
{


int
send (
    MI_Char const* const str,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::send (MI_Char*)");
    int rval = socket_wrapper::SUCCESS;
    if (NULL != str)
    {
        ssize_t const nStrLen = strlen (str);
#if (PRINT_BOOKENDS)
        std::ostringstream strm;
        strm << "nStrLen: " << nStrLen;
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        strm << "str: \"" << str << '\"';
        SCX_BOOKEND_PRINT (strm.str ());
#endif
        rval = send_item_count (nStrLen, sock);
        if (socket_wrapper::SUCCESS == rval &&
            0 < nStrLen)
        {
            rval = sock.send (
                reinterpret_cast<socket_wrapper::byte_t const*>(str),
                nStrLen);
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("str is NULL");
        rval = send_item_count (NULL_STRING, sock);
    }
    return rval;
}


int
recv (
    MI_Char** const ppStringOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::recv (MI_Char*)");
    assert (ppStringOut);
    item_count_t count;
    int rval = recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        util::unique_ptr<MI_Char[]> pText;
        if (NULL_STRING != count &&
            0 != count)
        {
            pText.reset (new MI_Char[count +1]);
            pText[count] = '\0';
            rval = sock.recv (
                reinterpret_cast<socket_wrapper::byte_t*>(pText.get ()),
                count * sizeof (MI_Char));
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            if (NULL != *ppStringOut)
            {
                delete[] *ppStringOut;
            }
            *ppStringOut = pText.release ();
        }
    }
    return rval;
}


int
recv (
    std::basic_string<MI_Char>* const pStringOut,
    socket_wrapper& sock)
{
    assert (pStringOut);
    MI_Char* pText = NULL;
    int rval = recv (&pText, sock);
    util::unique_ptr<MI_Char[]> holder (pText);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (pText)
        {
            pStringOut->assign (pText);
        }
        else
        {
            pStringOut->erase ();
        }
    }
    return rval;
}


int
recv_boolean (
    MI_Boolean* const pBooleanOut,
    socket_wrapper& sock)
{
    assert (pBooleanOut);
    protocol::boolean_t val;
    int rval = sock.recv (&val, sizeof (protocol::boolean_t));
    if (socket_wrapper::SUCCESS == rval)
    {
        *pBooleanOut = val ? MI_TRUE : MI_FALSE;
    }
    return rval;
}


} // namespace protocol
