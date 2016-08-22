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
    MI_ClassDecl::ConstPtr const& pClassDecl)
    : m_pClassDecl (pClassDecl)
{
    SCX_BOOKEND ("MI_Instance::ctor");
    assert (pClassDecl);
}


/*ctor*/
MI_Instance::MI_Instance (
    MI_Instance const& ref)
    : m_pClassDecl (ref.m_pClassDecl)
    , m_ValueMap (ref.m_ValueMap)
{
    SCX_BOOKEND ("MI_Instance::ctor (copy)");
}


/*dtor*/
MI_Instance::~MI_Instance ()
{
    SCX_BOOKEND ("MI_Instance::dtor");
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
    if (m_pClassDecl != rval.m_pClassDecl)
    {
        SCX_BOOKEND_PRINT ("Different class type");
    }
    m_pClassDecl = rval.m_pClassDecl;
    m_ValueMap = rval.m_ValueMap;
    return *this;
}


MI_ClassDecl::ConstPtr const&
MI_Instance::getClassDecl () const
{
    return m_pClassDecl;
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
    else if (m_pClassDecl->getPropertyDecl (name))
    {
        // correct: the value was not found in the instance but it is part
        // of the MI_ClassDecl
        rval = EXIT_SUCCESS;
    }
    else
    {
        // error: the property name is not part of the MI_ClassDecl
    }
    return rval;
}


int
MI_Instance::setValue (
    MI_Value<MI_STRING>::type_t const& name,
    MI_ValueBase::Ptr const& pValue)
{
    SCX_BOOKEND ("MI_Instance::setValue");
    int rval = EXIT_FAILURE;
    MI_PropertyDecl::ConstPtr pPropertyDecl =
        m_pClassDecl->getPropertyDecl (name);
    if (pPropertyDecl)
    {
        SCX_BOOKEND_PRINT ("the property does exist");
        // correct: the property name is part of the MI_ClassDecl
        if (pValue)
        {
            // if the value is not NULL, check that the value type matches
            // the MI_ClassDecl
//            if ((~protocol::MI_NULL_FLAG &
            if ((
                 pPropertyDecl->getType ()->getValue ()) ==
                pValue->getType ())
            {
                SCX_BOOKEND_PRINT ("the type matches");
                // correct: the type matches, set the new value
                std::pair<value_map_t::iterator, bool> ret =
                    m_ValueMap.insert (std::make_pair (name, pValue));
                if (!ret.second)
                {
                    SCX_BOOKEND_PRINT ("replace an existing value");
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
        SCX_BOOKEND_PRINT ("the property doesn't exist");
        // error: the property name is not in the MI_ClassDecl
    }
    return rval;
}


int
MI_Instance::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_Instance::send");
    int rval = socket_wrapper::SUCCESS;
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        // todo: sending TYPE should be removed
//        SCX_BOOKEND ("send Type");
//        rval = protocol::send_type (MI_INSTANCE, sock);
//    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send Name");
        rval = m_pClassDecl->getName ()->send (sock);
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
    MI_Instance::Ptr* ppInstanceOut,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("MI_Instance::recv");
    int rval = socket_wrapper::SUCCESS;

    // read classname
    // read values

    MI_Value<MI_STRING>::Ptr pClassName;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read class name");
        rval = MI_Value<MI_STRING>::recv (&pClassName, sock);
    }
    protocol::item_count_t itemCount = 0;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("read item count");
        rval = protocol::recv_item_count (&itemCount, sock);
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
                    // todo
//                    SCX_BOOKEND_PRINT ("MI_DATETIME not implemented");
//                    rval = EXIT_FAILURE;
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
                    // todo
                    SCX_BOOKEND_PRINT ("MI_DATETIMEA is not implemented");
//                    rval = EXIT_FAILURE;
//                    MI_Array<MI_DATETIMEA>::Ptr pTemp;
//                    rval = MI_Array<MI_DATETIMEA>::recv (&pTemp, sock);
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
                        SCX_BOOKEND_PRINT ("replace an existing value");
                        ret.first->second = pValue;
                    }
                }
                else
                {
                    SCX_BOOKEND_PRINT ("error receiving value");
                    // todo: error
                }
            }
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        MI_ClassDecl::ConstPtr pClassDecl =
            pSchemaDecl->getClassDecl (pClassName);
        if (pClassDecl)
        {
            Ptr pInstance (new MI_Instance (pClassDecl));
            int ret = EXIT_SUCCESS;
            for (value_map_t::const_iterator pos = values.begin (),
                     endPos = values.end ();
                 pos != endPos &&
                     EXIT_SUCCESS == ret;
                 ++pos)
            {
                ret = pInstance->setValue (pos->first, pos->second);
            }
            if (EXIT_SUCCESS == ret)
            {
                SCX_BOOKEND_PRINT ("recv succeeded");
                *ppInstanceOut = pInstance;
            }
            else
            {
                SCX_BOOKEND_PRINT ("setValue error");
                // todo: error encountered
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl was not found");
            // todo: error
        }
    }
    return rval;
}


} // namespace scx
