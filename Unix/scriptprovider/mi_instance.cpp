#include "mi_instance.hpp"


#include <cassert>
#include <cstdlib>


#include "debug_tags.hpp"
#include "mi_schema.hpp"
#include "shared_protocol.hpp"


namespace scx
{


/*ctor*/
MI_Instance::MI_Instance (
    MI_ObjectDecl::ConstPtr const& pObjectDecl)
    : m_pObjectDecl (pObjectDecl)
{
    //SCX_BOOKEND ("MI_Instance::ctor");
    //assert (pObjectDecl);
}


/*ctor*/
MI_Instance::MI_Instance (
    MI_Instance const& ref)
    : m_pObjectDecl (ref.m_pObjectDecl)
    , m_ValueMap (ref.m_ValueMap)
{
    //SCX_BOOKEND ("MI_Instance::ctor (copy)");
}


/*dtor*/
MI_Instance::~MI_Instance ()
{
    //SCX_BOOKEND ("MI_Instance::dtor");
}


TypeID_t
MI_Instance::getType () const
{
    return MI_INSTANCE;
}


MI_Instance&
MI_Instance::operator = (
    MI_Instance const& rval)
{
    SCX_BOOKEND ("MI_Instance::operator = ");
    if (m_pObjectDecl != rval.m_pObjectDecl)
    {
        SCX_BOOKEND_PRINT ("Different object type");
    }
    m_pObjectDecl = rval.m_pObjectDecl;
    m_ValueMap = rval.m_ValueMap;
    return *this;
}


MI_ObjectDecl::ConstPtr const&
MI_Instance::getObjectDecl () const
{
    return m_pObjectDecl;
}


int
MI_Instance::getValue (
    MI_Value<MI_STRING>::type_t const& name,
    MI_ValueBase::Ptr* ppValueOut) const
{
    //SCX_BOOKEND ("MI_Instance::getValue");
    assert (ppValueOut);
    int rval = EXIT_FAILURE;
    value_map_t::const_iterator pos = m_ValueMap.find (name);
    if (m_ValueMap.end () != pos)
    {
        // correct: the value was found, return it
        *ppValueOut = pos->second;
        rval = EXIT_SUCCESS;
    }
    else if (!m_pObjectDecl ||
             m_pObjectDecl->getParameterDecl (name))
    {
        // correct: the value was not found in the instance but it is part
        // of the MI_ObjectDecl
        rval = EXIT_SUCCESS;
    }
    else
    {
        // error: the parameter name is not part of the MI_ObjectDecl
    }
    return rval;
}


int
MI_Instance::setValue (
    MI_Value<MI_STRING>::type_t const& name,
    MI_ValueBase::Ptr const& pValue)
{
    //SCX_BOOKEND ("MI_Instance::setValue");
    int rval = EXIT_FAILURE;
    if (m_pObjectDecl)
    {
        MI_ParameterDecl::ConstPtr pParameterDecl =
            m_pObjectDecl->getParameterDecl (name);
        if (pParameterDecl)
        {
            SCX_BOOKEND_PRINT ("the parameter does exist");
            // correct: the parameter name is part of the MI_ObjectDecl
            if (pValue)
            {
                // if the value is not NULL, check that the value type matches
                // the MI_ParameterDecl
                if ((pParameterDecl->getType ()->getValue ()) ==
                        pValue->getType ())
                {
                    SCX_BOOKEND_PRINT ("the type matches");
                    // correct: the type matches, set the new value
                    std::pair<value_map_t::iterator, bool> ret =
                        m_ValueMap.insert (std::make_pair (name, pValue));
                    if (!ret.second)
                    {
                        //SCX_BOOKEND_PRINT ("replace an existing value");
                        // correct: the value already existed, so replace the
                        // value
                        ret.first->second = pValue;
                    }
                    rval = EXIT_SUCCESS;
                }
                else
                {
                    SCX_BOOKEND_PRINT ("the type doesn't match");
                    // error: the type does not match
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("erase the value");
                // correct: erase the value
                m_ValueMap.erase (name);
                rval = EXIT_SUCCESS;
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("the parameter doesn't exist");
            // error: the property name is not in the MI_ObjectDecl
        }
    }
    else
    {
        if (pValue)
        {
            std::pair<value_map_t::iterator, bool> ret =
                m_ValueMap.insert (std::make_pair (name, pValue));
            if (!ret.second)
            {
                //SCX_BOOKEND_PRINT ("replace an existing value");
                // correct: the value already existed, so replace the
                // value
                ret.first->second = pValue;
            }
            rval = EXIT_SUCCESS;
        }
        else
        {
            SCX_BOOKEND_PRINT ("erase the value");
            // correct: erase the value
            m_ValueMap.erase (name);
            rval = EXIT_SUCCESS;
        }
    }
    return rval;
}


int
MI_Instance::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_Instance::send");
    int rval = socket_wrapper::SUCCESS;
    unsigned int flags = m_pObjectDecl->isMethodDecl () ? 1 : 0;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send flags");
        rval = protocol::send (flags, sock);
    }
    if (socket_wrapper::SUCCESS == rval &&
        protocol::MI_METHOD_FLAG == (protocol::MI_METHOD_FLAG & flags))
    {
        SCX_BOOKEND ("send origin");
        MI_MethodDecl const* pMethodDecl =
            static_cast<MI_MethodDecl const*>(m_pObjectDecl.get ());
        rval = pMethodDecl->getOrigin ()->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send Name");
        rval = m_pObjectDecl->getName ()->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send Size");
        rval = protocol::send_item_count (m_ValueMap.size (), sock);
    }
    for (value_map_t::const_iterator pos = m_ValueMap.begin (),
             endPos = m_ValueMap.end ();
         socket_wrapper::SUCCESS == rval &&
             pos != endPos;
         ++pos)
    {
        SCX_BOOKEND ("send Value");
        SCX_BOOKEND_PRINT ("-- name --");
        rval = protocol::send (pos->first, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("-- type --");
            rval = protocol::send_type (pos->second->getType (), sock);
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("-- value --");
            rval = pos->second->send (sock);
        }
    }
    return rval;
}


/*static*/ int
MI_Instance::recv (
    MI_Instance::Ptr* const ppInstanceOut,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Instance::recv");
    MI_Value<MI_STRING>::Ptr pClassName;
    int rval = MI_Value<MI_STRING>::recv (&pClassName, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        MI_ObjectDecl::ConstPtr pObjectDecl =
            pSchemaDecl->getClassDecl (pClassName);
        if (pObjectDecl)
        {
            rval = recv (ppInstanceOut, pObjectDecl, pSchemaDecl, sock);
        }
        else
        {
            SCX_BOOKEND_PRINT ("ClassDecl not found");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("read name failed");
    }
    return rval;
}


/*static*/ int
MI_Instance::recv (
    MI_Instance::Ptr* const ppInstanceOut,
    MI_ObjectDecl::ConstPtr const& pObjectDecl,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Instance::recv");
    assert (ppInstanceOut);
    assert (pObjectDecl);
    assert (pSchemaDecl);
    value_map_t valueMap;
    int rval = recv_values (&valueMap, pSchemaDecl, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("values read successfully");
        rval = confirm_values (valueMap, pObjectDecl);
        if (EXIT_SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("value confirmation succeeded");
            ppInstanceOut->reset (new MI_Instance (pObjectDecl));
            std::swap ((*ppInstanceOut)->m_ValueMap, valueMap);
        }
        else 
        {
            SCX_BOOKEND_PRINT ("value confirmation failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("failed to read values");
    }
    return rval;
}


/*static*/ int
MI_Instance::recv_values (
    value_map_t* const pValueMapOut,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Instance::recv_values");
    int rval = EXIT_SUCCESS;
    protocol::item_count_t itemCount = 0;
    {
        SCX_BOOKEND ("read item count");
        rval = protocol::recv_item_count (&itemCount, sock);
        std::ostringstream strm;
        strm << "item count: " << itemCount;
        SCX_BOOKEND_PRINT (strm.str ());
    }
    value_map_t values;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read values");
        for (protocol::item_count_t i = 0;
             i < itemCount && socket_wrapper::SUCCESS == rval;
             ++i)
        {
            SCX_BOOKEND ("read value");
            MI_Value<MI_STRING>::Ptr pValueName;
            SCX_BOOKEND_PRINT ("-- name --");
            rval = MI_Value<MI_STRING>::recv (&pValueName, sock);
            protocol::data_type_t type;
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND_PRINT ("-- type --");
                rval = protocol::recv_type (&type, sock);
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                MI_ValueBase::Ptr pValue;
                switch (type)
                {
                case MI_BOOLEAN:
                {
                    MI_Value<MI_BOOLEAN>::Ptr pTemp;
                    rval = MI_Value<MI_BOOLEAN>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT8:
                {
                    MI_Value<MI_UINT8>::Ptr pTemp;
                    rval = MI_Value<MI_UINT8>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT8:
                {
                    MI_Value<MI_SINT8>::Ptr pTemp;
                    rval = MI_Value<MI_SINT8>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT16:
                {
                    MI_Value<MI_UINT16>::Ptr pTemp;
                    rval = MI_Value<MI_UINT16>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT16:
                {
                    MI_Value<MI_SINT16>::Ptr pTemp;
                    rval = MI_Value<MI_SINT16>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT32:
                {
                    MI_Value<MI_UINT32>::Ptr pTemp;
                    rval = MI_Value<MI_UINT32>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT32:
                {
                    MI_Value<MI_SINT32>::Ptr pTemp;
                    rval = MI_Value<MI_SINT32>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT64:
                {
                    MI_Value<MI_UINT64>::Ptr pTemp;
                    rval = MI_Value<MI_UINT64>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT64:
                {
                    MI_Value<MI_SINT16>::Ptr pTemp;
                    rval = MI_Value<MI_SINT16>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REAL32:
                {
                    MI_Value<MI_REAL32>::Ptr pTemp;
                    rval = MI_Value<MI_REAL32>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REAL64:
                {
                    MI_Value<MI_REAL64>::Ptr pTemp;
                    rval = MI_Value<MI_REAL64>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_CHAR16:
                {
                    MI_Value<MI_CHAR16>::Ptr pTemp;
                    rval = MI_Value<MI_CHAR16>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_DATETIME:
                {
                    MI_Datetime::Ptr pTemp;
                    rval = MI_Datetime::recv (&pTemp, sock);
                    break;
                }
                case MI_STRING:
                {
                    MI_Value<MI_STRING>::Ptr pTemp;
                    rval = MI_Value<MI_STRING>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REFERENCE:
                {
                    // todo
                    SCX_BOOKEND_PRINT ("MI_REFERENCE not implemented");
                    rval = EXIT_FAILURE;
                    break;
                }
                case MI_INSTANCE:
                {
                    MI_Instance::Ptr pTemp;
                    rval = recv (&pTemp, pSchemaDecl, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_BOOLEANA:
                {
                    MI_Array<MI_BOOLEANA>::Ptr pTemp;
                    rval = MI_Array<MI_BOOLEANA>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT8A:
                {
                    MI_Array<MI_UINT8A>::Ptr pTemp;
                    rval = MI_Array<MI_UINT8A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT8A:
                {
                    MI_Array<MI_SINT8A>::Ptr pTemp;
                    rval = MI_Array<MI_SINT8A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT16A:
                {
                    MI_Array<MI_UINT16A>::Ptr pTemp;
                    rval = MI_Array<MI_UINT16A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT16A:
                {
                    MI_Array<MI_SINT16A>::Ptr pTemp;
                    rval = MI_Array<MI_SINT16A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT32A:
                {
                    MI_Array<MI_UINT32A>::Ptr pTemp;
                    rval = MI_Array<MI_UINT32A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT32A:
                {
                    MI_Array<MI_SINT32A>::Ptr pTemp;
                    rval = MI_Array<MI_SINT32A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_UINT64A:
                {
                    MI_Array<MI_UINT64A>::Ptr pTemp;
                    rval = MI_Array<MI_UINT64A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_SINT64A:
                {
                    MI_Array<MI_SINT64A>::Ptr pTemp;
                    rval = MI_Array<MI_SINT64A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REAL32A:
                {
                    MI_Array<MI_REAL32A>::Ptr pTemp;
                    rval = MI_Array<MI_REAL32A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REAL64A:
                {
                    MI_Array<MI_REAL64A>::Ptr pTemp;
                    rval = MI_Array<MI_REAL64A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_CHAR16A:
                {
                    MI_Array<MI_CHAR16A>::Ptr pTemp;
                    rval = MI_Array<MI_CHAR16A>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_DATETIMEA:
                {
                    rval = EXIT_FAILURE;
                    MI_Array<MI_DATETIMEA>::Ptr pTemp;
                    rval = MI_Array<MI_DATETIMEA>::recv (&pTemp, sock);
                    break;
                }
                case MI_STRINGA:
                {
                    MI_Array<MI_STRINGA>::Ptr pTemp;
                    rval = MI_Array<MI_STRINGA>::recv (&pTemp, sock);
                    pValue = pTemp.get ();
                    break;
                }
                case MI_REFERENCEA:
                    // todo
                    SCX_BOOKEND_PRINT ("MI_REFERENCEA not implemented");
                    rval = EXIT_FAILURE;
                    break;
                case MI_INSTANCEA:
                    // todo
                    SCX_BOOKEND_PRINT ("MI_INSTANCEA not implemented");
                    rval = EXIT_FAILURE;
                    break;
                }
                if (socket_wrapper::SUCCESS == rval)
                {
                    std::pair<value_map_t::iterator, bool> ret =
                        values.insert (
                            std::make_pair (pValueName->getValue (), pValue));
                    if (!ret.second)
                    {
                        //SCX_BOOKEND_PRINT ("replace an existing value");
                        ret.first->second = pValue;
                    }
                }
                else
                {
                    SCX_BOOKEND_PRINT ("error receiving value");
                }
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        std::swap (values, *pValueMapOut);
    }
    return rval;
}


/*static*/ int
MI_Instance::confirm_values (
    value_map_t const& valueMap,
    MI_ObjectDecl::ConstPtr const& pObjectDecl)
{
    SCX_BOOKEND ("MI_Instance::confirm_values");
    int rval = EXIT_SUCCESS;
    for (value_map_t::const_iterator pos = valueMap.begin (),
             endPos = valueMap.end ();
         EXIT_SUCCESS == rval && pos != endPos;
         ++pos)
    {
        MI_ParameterDecl::ConstPtr pParameterDecl =
            pObjectDecl->getParameterDecl (pos->first);
        if (!pParameterDecl)
        {
            SCX_BOOKEND_PRINT ("the parameter does not exist");
            rval = EXIT_FAILURE;
        }
        else if (pParameterDecl->getType ()->getValue () !=
                 pos->second->getType ())
        {
            SCX_BOOKEND_PRINT ("the type does not match");
        }
    }
    return rval;
}


} // namespace scx
