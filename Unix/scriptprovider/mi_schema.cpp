#include "mi_schema.hpp"


#include <algorithm>
#include <cassert>
#include "shared_protocol.hpp"


namespace
{


bool
classDeclSort (
    scx::MI_ClassDecl::Ptr pLeft,
    scx::MI_ClassDecl::Ptr pRight)
{
    return pLeft->getName () < pRight->getName ();
}


scx::MI_ClassDecl::ConstPtr
findClassDecl (
    std::vector<scx::MI_ClassDecl::Ptr> const& classDecls,
    scx::MI_Value<MI_STRING>::ConstPtr const& pName)
{
    //SCX_BOOKEND ("findClassDecl");
    if (pName)
    {
        //std::ostringstream strm;
        //strm << "pName: \"" << pName->getValue () << "\"";
        //SCX_BOOKEND_PRINT (strm.str ());
        //strm.str ("");
        //strm.clear ();
        typedef std::vector<scx::MI_ClassDecl::Ptr>::size_type index_t;
        index_t left = 0;
        index_t right = classDecls.size ();
        while (left < right)
        {
            index_t mid = (left + right) / 2;

            //strm << "compare: \"" << classDecls[mid]->getName ()->getValue ()
            //     << "\"";
            //SCX_BOOKEND_PRINT (strm.str ());
            //strm.str ("");
            //strm.clear ();

            int const ret = pName->getValue ().compare (
                classDecls[mid]->getName ()->getValue ());

            if (ret < 0)
            {
                //SCX_BOOKEND_PRINT ("left");
                right = mid;
            }
            else if (0 < ret)
            {
                //SCX_BOOKEND_PRINT ("right");
                left = mid + 1;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("found");
                return scx::MI_ClassDecl::Ptr (classDecls[mid]);
            }
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("pName is NULL");
    }
    return scx::MI_ClassDecl::Ptr ();
}


template<typename OBJECT>
struct Finder
{
    /*ctor*/ Finder (scx::MI_Value<MI_STRING>::type_t const& name)
        : m_Name (name)
    {
        // empty
    }

    bool operator () (typename OBJECT::ConstPtr const& pObject)
    {
        return m_Name == pObject->getName ()->getValue ();
    }

    scx::MI_Value<MI_STRING>::type_t const& m_Name;
};


} // namespace (unnamed)


namespace scx
{


/*ctor*/
MI_QualifierDecl::MI_QualifierDecl (
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_UINT32>::ConstPtr const& pScope,
    MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
    MI_ValueBase::ConstPtr const& pValue)
    : m_pName (pName)
    , m_pType (pType)
    , m_pScope (pScope)
    , m_pFlavor (pFlavor)
    , m_pValue (pValue)
{
    //SCX_BOOKEND ("MI_QualifierDecl::ctor");
    assert (pName);
    assert (pType);
    assert (pScope);
    assert (pFlavor);
    assert (NULL == pValue.get () || pValue->getType () == pType->getValue ());
}


/*dtor*/
MI_QualifierDecl::~MI_QualifierDecl ()
{
    //SCX_BOOKEND ("MI_QualiferDecl::dtor");
}


MI_Value<MI_STRING>::ConstPtr const&
MI_QualifierDecl::getName () const
{
    return m_pName;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_QualifierDecl::getType () const
{
    return m_pType;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_QualifierDecl::getScope () const
{
    return m_pScope;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_QualifierDecl::getFlavor () const
{
    return m_pFlavor;
}


MI_ValueBase::ConstPtr const&
MI_QualifierDecl::getValue () const
{
    return m_pValue;
}


int
MI_QualifierDecl::send (
    socket_wrapper& sock) const
{
    int rval = socket_wrapper::SUCCESS;
    rval = m_pName->send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        protocol::data_type_t const type = static_cast<protocol::data_type_t>(
            m_pType->getValue () | (m_pValue ? 0 : protocol::MI_NULL_FLAG));
        rval = protocol::send (type, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = m_pScope->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = m_pFlavor->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval &&
        m_pValue)
    {
        rval = m_pValue->send (sock);
    }
    return rval;
}


/*ctor*/
MI_Qualifier::MI_Qualifier (
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
    MI_ValueBase::ConstPtr const& pValue)
    : m_pName (pName)
    , m_pType (pType)
    , m_pFlavor (pFlavor)
    , m_pValue (pValue)
{
    //SCX_BOOKEND ("MI_Qualifier::ctor");
    assert (pName);
    assert (pType);
    assert (pFlavor);
    assert (NULL == pValue.get () || pValue->getType () == pType->getValue ());
}


/*dtor*/
MI_Qualifier::~MI_Qualifier ()
{
    //SCX_BOOKEND ("MI_Qualifer::dtor");
    // empty
}


MI_Value<MI_STRING>::ConstPtr const&
MI_Qualifier::getName () const
{
    return m_pName;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_Qualifier::getType () const
{
    return m_pType;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_Qualifier::getFlavor () const
{
    return m_pFlavor;
}


MI_ValueBase::ConstPtr const&
MI_Qualifier::getValue () const
{
    return m_pValue;
}


int
MI_Qualifier::send (
    socket_wrapper& sock) const
{
    int rval = socket_wrapper::SUCCESS;
    rval = m_pName->send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        protocol::data_type_t const type = static_cast<protocol::data_type_t>(
            m_pType->getValue () | (m_pValue ? 0 : protocol::MI_NULL_FLAG));
        rval = protocol::send (type, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = m_pFlavor->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval &&
        m_pValue)
    {
        rval = m_pValue->send (sock);
    }
    return rval;
}


/*ctor*/
MI_ParameterDecl::MI_ParameterDecl (
    MI_Value<MI_UINT32>::ConstPtr const& flags,
    MI_Value<MI_UINT32>::ConstPtr const& code,
    MI_Value<MI_STRING>::ConstPtr const& name,
    MI_Qualifier::ConstPtr const* const ppQualifiersBegin,
    size_t const& qualifiersCount,
    MI_Value<MI_UINT32>::ConstPtr const& type,
    MI_Value<MI_STRING>::ConstPtr const& className)
    : m_pFlags (flags)
    , m_pCode (code)
    , m_pName (name)
    , m_Qualifiers (ppQualifiersBegin, ppQualifiersBegin + qualifiersCount)
    , m_pType (type)
    , m_pClassName (className)
{
    SCX_BOOKEND ("MI_ParameterDecl::ctor");
}


/*dtor*/
MI_ParameterDecl::~MI_ParameterDecl ()
{
    SCX_BOOKEND ("MI_ParameterDecl::dtor");
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_ParameterDecl::getFlags () const
{
    return m_pFlags;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_ParameterDecl::getCode () const
{
    return m_pCode;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_ParameterDecl::getName () const
{
    return m_pName;
}


//std::vector<MI_Qualifier::ConstPtr> const&
//MI_ParameterDecl::getQualifiers () const
//{
//    return m_Qualifiers;
//}


MI_Value<MI_UINT32>::ConstPtr const&
MI_ParameterDecl::getType () const
{
    return m_pType;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_ParameterDecl::getClassName () const
{
    return m_pClassName;
}


int
MI_ParameterDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_ParameterDecl::send");
    int rval = socket_wrapper::SUCCESS;
    std::ostringstream strm;
    strm << "send flags: " << m_pFlags->getValue ();
    SCX_BOOKEND_PRINT (strm.str ());
    strm.clear ();
    strm.str ("");
    rval = m_pFlags->send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "send code: " << m_pCode->getValue ();
        SCX_BOOKEND_PRINT (strm.str ());
        strm.clear ();
        strm.str ("");
        rval = m_pCode->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "send name: \"" << m_pName->getValue () << "\"";
        SCX_BOOKEND_PRINT (strm.str ());
        strm.clear ();
        strm.str ("");
        rval = m_pName->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send qualifiers");
        strm << "send count: " << m_Qualifiers.size ();
        SCX_BOOKEND_PRINT (strm.str ());
        strm.clear ();
        strm.str ("");
        rval = protocol::send_item_count (m_Qualifiers.size (), sock);
        for (std::vector<MI_Qualifier::ConstPtr>::const_iterator
                 pos = m_Qualifiers.begin (),
                 endPos = m_Qualifiers.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            SCX_BOOKEND_PRINT ("send qualifier");
            rval = (*pos)->send (sock);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = send_type (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "send classname: ";
        if (m_pClassName)
        {
            strm << "\"" << m_pClassName->getValue () << "\"";
        }
        else
        {
            strm << "NULL";
        }
        SCX_BOOKEND_PRINT (strm.str ());
        strm.clear ();
        strm.str ("");
        rval = protocol::send (m_pClassName, sock);
    }
    return rval;
}


int
MI_ParameterDecl::send_type (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_ParameterDecl::send_type");
    std::ostringstream strm;
    strm << "send type: " << m_pType->getValue ();
    SCX_BOOKEND_PRINT (strm.str ());
    return protocol::send_type (m_pType->getValue (), sock);
}
    

/*ctor*/
MI_PropertyDecl::MI_PropertyDecl (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Qualifier::ConstPtr const* const ppQualifiersBegin,
    size_t const& qualifiersCount,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_STRING>::ConstPtr const& pClassName,
    MI_Value<MI_STRING>::ConstPtr const& pOrigin,
    MI_Value<MI_STRING>::ConstPtr const& pPropagator,
    MI_ValueBase::ConstPtr const& pValue)
    : MI_ParameterDecl (pFlags, pCode, pName, ppQualifiersBegin,
                        qualifiersCount, pType, pClassName)
//    : m_pFlags (pFlags)
//    , m_pCode (pCode)
//    , m_pName (pName)
//    , m_Qualifiers (ppQualifiersBegin, ppQualifiersBegin + qualifiersCount)
//    , m_pType (pType)
//    , m_pClassName (pClassName)
    , m_pOrigin (pOrigin)
    , m_pPropagator (pPropagator)
    , m_pValue (pValue)
{
    SCX_BOOKEND ("MI_PropertyDecl::ctor");
    assert (pFlags);
    assert (pCode);
    assert (pName);
    assert (pType);
    assert (pOrigin);
    assert (pPropagator);
    assert (NULL == pValue.get () || pValue->getType () == pType->getValue ());
}


/*dtor*/
MI_PropertyDecl::~MI_PropertyDecl ()
{
    SCX_BOOKEND ("MI_PropertyDecl::dtor");
}


//MI_Value<MI_UINT32>::ConstPtr const&
//MI_PropertyDecl::getFlags () const
//{
//    return m_pFlags;
//}


//MI_Value<MI_UINT32>::ConstPtr const&
//MI_PropertyDecl::getCode () const
//{
//    return m_pCode;
//}


//MI_Value<MI_STRING>::ConstPtr const&
//MI_PropertyDecl::getName () const
//{
//    return m_pName;
//}


//std::vector<MI_Qualifier::ConstPtr> const&
//MI_PropertyDecl::getQualifiers () const
//{
//    return m_Qualifiers;
//}


//MI_Value<MI_UINT32>::ConstPtr const&
//MI_PropertyDecl::getType () const
//{
//    return m_pType;
//}


//MI_Value<MI_STRING>::ConstPtr const&
//MI_PropertyDecl::getClassName () const
//{
//    return m_pClassName;
//}


MI_Value<MI_STRING>::ConstPtr const&
MI_PropertyDecl::getOrigin () const
{
    return m_pOrigin;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_PropertyDecl::getPropagator () const
{
    return m_pPropagator;
}


MI_ValueBase::ConstPtr const&
MI_PropertyDecl::getValue () const
{
    return m_pValue;
}


int
MI_PropertyDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_PropertyDecl::send");
    int rval = MI_ParameterDecl::send (sock);
//    int rval = socket_wrapper::SUCCESS;
    std::ostringstream strm;
//    strm << "send flags: " << m_pFlags->getValue ();
//    SCX_BOOKEND_PRINT (strm.str ());
//    strm.str ("");
//    strm.clear ();
//    rval = m_pFlags->send (sock);
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        strm << "send code: " << m_pCode->getValue ();
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = m_pCode->send (sock);
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        strm << "send name: ";
//        if (m_pName)
//        {
//            strm << "\"" << m_pName->getValue () << "\"";
//        }
//        else
//        {
//            strm << "NULL";
//        }
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = m_pName->send (sock);
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        strm << "send qualifier size: " << m_Qualifiers.size ();
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = protocol::send_item_count (m_Qualifiers.size (), sock);
//        for (std::vector<MI_Qualifier::ConstPtr>::const_iterator
//                 pos = m_Qualifiers.begin (),
//                 endPos = m_Qualifiers.end ();
//             socket_wrapper::SUCCESS == rval &&
//                 pos != endPos;
//             ++pos)
//        {
//            SCX_BOOKEND_PRINT ("send qualifier");
//            rval = (*pos)->send (sock);
//        }
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        MI_Uint32 const type =
//            m_pType->getValue () | (m_pValue ? 0 : protocol::MI_NULL_FLAG);
//        strm << "send type: " << type;
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = protocol::send (type, sock);
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        strm << "send class name: ";
//        if (m_pClassName)
//        {
//            strm << "\"" << m_pClassName->getValue () << "\"";
//        }
//        else
//        {
//            strm << "NULL";
//        }
//        SCX_BOOKEND_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = protocol::send (m_pClassName, sock);
//    }
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "send origin: ";
        if (m_pOrigin)
        {
            strm << "\"" << m_pOrigin->getValue () << "\"";
        }
        else
        {
            strm << "NULL";
        }
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        rval = protocol::send (m_pOrigin, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        strm << "send propagator: ";
        if (m_pPropagator)
        {
            strm << "\"" << m_pPropagator->getValue () << "\"";
        }
        else
        {
            strm << "NULL";
        }
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        rval = protocol::send (m_pPropagator, sock);
    }
    if (socket_wrapper::SUCCESS == rval &&
        m_pValue)
    {
        SCX_BOOKEND_PRINT ("send value");
        rval = m_pValue->send (sock);
    }
    return rval;
}


int
MI_PropertyDecl::send_type (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_PropertyDecl::send_type");
    std::ostringstream strm;
    protocol::data_type_t const type = static_cast<protocol::data_type_t>(
        getType ()->getValue () | (m_pValue ? 0 : protocol::MI_NULL_FLAG));
    strm << "send type: " << type;
    SCX_BOOKEND_PRINT (strm.str ());
    return protocol::send_type (type, sock);
}


/*ctor*/
MI_ObjectDecl::MI_ObjectDecl (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Qualifier::ConstPtr const* ppQualifiersBegin,
    size_t const& qualifiersCount,
    MI_ParameterDecl::ConstPtr const* ppParametersBegin,
    size_t const& parametersCount)
    : m_pFlags (pFlags)
    , m_pCode (pCode)
    , m_pName (pName)
    , m_Qualifiers (ppQualifiersBegin, ppQualifiersBegin + qualifiersCount)
    , m_Parameters (ppParametersBegin, ppParametersBegin + parametersCount)
{
    SCX_BOOKEND ("MI_ObjectDecl::ctor");
    assert (pFlags);
    assert (pCode);
    assert (pName);
}


/*dtor*/
MI_ObjectDecl::~MI_ObjectDecl ()
{
    SCX_BOOKEND ("MI_ObjectDecl::dtor");
}


bool
MI_ObjectDecl::isMethodDecl () const
{
    return false;
}


MI_ParameterDecl::ConstPtr
MI_ObjectDecl::getParameterDecl (
    MI_Value<MI_STRING>::type_t const& parameterName) const
{
    //SCX_BOOKEND ("MI_ObjectDecl::getParameterDecl");
    MI_ParameterDecl::ConstPtr pParameterDecl;
    std::vector<MI_ParameterDecl::ConstPtr>::const_iterator
        parameterDeclPos = std::find_if (
            m_Parameters.begin (), m_Parameters.end (),
            Finder<MI_ParameterDecl> (parameterName));
    if (m_Parameters.end () != parameterDeclPos)
    {
        // correct: the parameter name is part of the MI_ClassDecl
        // clear the return value and return success
        pParameterDecl = *parameterDeclPos;
    }
    return pParameterDecl;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_ObjectDecl::getFlags () const
{
    return m_pFlags;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_ObjectDecl::getCode () const
{
    return m_pCode;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_ObjectDecl::getName () const
{
    return m_pName;
}


//std::vector<MI_Qualifier::ConstPtr> const&
//MI_ObjectDecl::getQualifiers () const
//{
//    return m_Qualifiers;
//}


//std::vector<MI_ParameterDecl::ConstPtr> const&
//MI_ObjectDecl::getParameters () const
//{
//    return m_Parameters;
//}


int
MI_ObjectDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_ObjectDecl::send");
    int rval = socket_wrapper::SUCCESS;
    SCX_BOOKEND_PRINT ("send flags");
    rval = m_pFlags->send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send code");
        rval = m_pCode->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send name");
        rval = m_pName->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send qualifier count");
        rval = protocol::send_item_count (m_Qualifiers.size (), sock);
        for (std::vector<MI_Qualifier::ConstPtr>::const_iterator
                 pos = m_Qualifiers.begin (),
                 endPos = m_Qualifiers.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            SCX_BOOKEND_PRINT ("---- send qualifier");
            rval = (*pos)->send (sock);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send_item_count (m_Parameters.size (), sock);
        SCX_BOOKEND_PRINT ("send parameter count");
        for (std::vector<MI_ParameterDecl::ConstPtr>::const_iterator
                 pos = m_Parameters.begin (),
                 endPos = m_Parameters.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            SCX_BOOKEND_PRINT ("---- send parameter");
            rval = (*pos)->send (sock);
        }
    }
    return rval;
}


/*ctor*/
MI_MethodDecl::MI_MethodDecl (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Qualifier::ConstPtr const* ppQualifiersBegin,
    size_t const& qualifiersCount,
    MI_ParameterDecl::ConstPtr const* ppParametersBegin,
    size_t const& parametersCount,
    MI_Value<MI_UINT32>::ConstPtr const& pReturnType,
    MI_Value<MI_STRING>::ConstPtr const& pOrigin,
    MI_Value<MI_STRING>::ConstPtr const& pPropagator,
    MI_MethodDecl::InvokeFn::ConstPtr const& pInvokeFn)
    : MI_ObjectDecl (pFlags, pCode, pName, ppQualifiersBegin, qualifiersCount,
                     ppParametersBegin, parametersCount)
    , m_pReturnType (pReturnType)
    , m_pOrigin (pOrigin)
    , m_pPropagator (pPropagator)
    , m_pInvokeFn (pInvokeFn)
{
    SCX_BOOKEND ("MI_MethodDecl::ctor");
    assert (pFlags);
    assert (pCode);
    assert (pName);
    assert (pReturnType);
    assert (pInvokeFn);
}


/*dtor*/
MI_MethodDecl::~MI_MethodDecl ()
{
    SCX_BOOKEND ("MI_MethodDecl::dtor");
}


bool
MI_MethodDecl::isMethodDecl () const
{
    return true;
}


MI_Value<MI_UINT32>::ConstPtr const&
MI_MethodDecl::getReturnType () const
{
    return m_pReturnType;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_MethodDecl::getOrigin () const
{
    return m_pOrigin;
}


MI_Value<MI_STRING>::ConstPtr const&
MI_MethodDecl::getPropagator () const
{
    return m_pPropagator;
}


MI_MethodDecl::InvokeFn::ConstPtr const&
MI_MethodDecl::getInvokeFn () const
{
    return m_pInvokeFn;
}


int
MI_MethodDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_MethodDecl::send");
    int rval = MI_ObjectDecl::send (sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send return type");
        rval = protocol::send_type (
            static_cast<protocol::data_type_t>(
                m_pReturnType->getValue ()), sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send origin");
        rval = protocol::send (m_pOrigin, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND_PRINT ("send propagator");
        rval = protocol::send (m_pPropagator, sock);
    }
    return rval;
}


void
MI_MethodDecl::Invoke (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Value<MI_STRING>::Ptr const& pMethodName,
    MI_Instance::Ptr const& pInstanceName,
    MI_Instance::Ptr const& pParameters) const
{
    SCX_BOOKEND ("MI_MethodDecl::Invoke");
    return m_pInvokeFn->fn (pContext, pNameSpace, pClassName, pMethodName,
                            pInstanceName, pParameters);
}


std::vector<MI_ParameterDecl::ConstPtr>
convert (MI_PropertyDecl::ConstPtr const* begin, size_t const& count)
{
    typedef std::vector<MI_ParameterDecl::ConstPtr> coll_t;
    coll_t coll;
    std::copy (begin, begin + count, std::back_insert_iterator<coll_t> (coll));
    return coll;
}


/*ctor*/
MI_ClassDecl::MI_ClassDecl (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Qualifier::ConstPtr const* ppQualifiersBegin,
    size_t const& qualifiersCount,
    MI_PropertyDecl::ConstPtr const* ppPropertyDeclsBegin,
    size_t const& propertyDeclsCount,
    MI_Value<MI_STRING>::ConstPtr const& pSuperClassName,
    MI_MethodDecl::Ptr const* ppMethodDeclsBegin,
    size_t const& methodDeclsCount,
    MI_FunctionTable::ConstPtr const& pFunctionTable)
    : MI_ObjectDecl (
        pFlags, pCode, pName, ppQualifiersBegin, qualifiersCount,
        (0 < propertyDeclsCount
         ? &(convert (ppPropertyDeclsBegin, propertyDeclsCount)[0])
            : NULL),
        propertyDeclsCount)
//                     0, 0)
//    : m_pFlags (pFlags)
//    , m_pCode (pCode)
//    , m_pName (pName)
//    , m_Qualifiers (ppQualifiersBegin, ppQualifiersBegin + qualifiersCount)
//    , m_PropertyDecls (ppPropertyDeclsBegin,
//                       ppPropertyDeclsBegin + propertyDeclsCount)
    , m_pSuperClassName (pSuperClassName)
    , m_MethodDecls (ppMethodDeclsBegin, ppMethodDeclsBegin + methodDeclsCount)
    , m_pFunctionTable (pFunctionTable)
{
    SCX_BOOKEND ("MI_ClassDecl::ctor");
}


void
MI_ClassDecl::setOwningClassDecl (
    MI_ClassDecl::Ptr const& pOwningClassDecl)
{
    m_pOwningClassDecl = pOwningClassDecl;
}


MI_PropertyDecl::ConstPtr
MI_ClassDecl::getPropertyDecl (
    MI_Value<MI_STRING>::type_t const& propertyName) const
{
    //SCX_BOOKEND ("MI_ClassDecl::getPropertyDecl");
    MI_ParameterDecl::ConstPtr pParameterDecl (getParameterDecl (propertyName));
    return MI_PropertyDecl::ConstPtr (
        static_cast<MI_PropertyDecl const*>(pParameterDecl.get ()));

//    MI_PropertyDecl::ConstPtr pPropertyDecl;
//    std::vector<MI_PropertyDecl::ConstPtr>::const_iterator
//        propertyDeclPos = std::find_if (
//            m_PropertyDecls.begin (), m_PropertyDecls.end (),
//            Finder<MI_PropertyDecl> (propertyName));
//    if (m_PropertyDecls.end () != propertyDeclPos)
//    {
//        // correct: the property name is part of the MI_ClassDecl
//        // clear the return value and return success
//        pPropertyDecl = *propertyDeclPos;
//    }
//    return pPropertyDecl;
}


MI_MethodDecl::ConstPtr
MI_ClassDecl::getMethodDecl (
    MI_Value<MI_STRING>::type_t const& methodName) const
{
    SCX_BOOKEND ("MI_ClassDecl::getMethodDecl");
    MI_MethodDecl::ConstPtr pMethodDecl;
    std::vector<MI_MethodDecl::Ptr>::const_iterator
        methodDeclPos = std::find_if (
            m_MethodDecls.begin (), m_MethodDecls.end (),
            Finder<MI_MethodDecl> (methodName));
    if (m_MethodDecls.end () != methodDeclPos)
    {
        // correct: the property name is part of the MI_ClassDecl
        // clear the return value and return success
        pMethodDecl = *methodDeclPos;

        if (NULL == methodDeclPos->get ())
        {
            SCX_BOOKEND_PRINT ("methodDeclPos->get () is NULL");
        }
        else
        {
            SCX_BOOKEND_PRINT ("methodDeclPos->get () is not NULL");
        }
    }
    return pMethodDecl;
}


/*dtor*/
MI_ClassDecl::~MI_ClassDecl ()
{
    SCX_BOOKEND ("MI_ClassDecl::dtor");
}


//MI_Value<MI_UINT32>::ConstPtr const&
//MI_ClassDecl::getFlags () const
//{
//    return m_pFlags;
//}


//MI_Value<MI_UINT32>::ConstPtr const&
//MI_ClassDecl::getCode () const
//{
//    return m_pCode;
//}


//MI_Value<MI_STRING>::ConstPtr const&
//MI_ClassDecl::getName () const
//{
//    return m_pName;
//}


//std::vector<MI_Qualifier::ConstPtr> const&
//MI_ClassDecl::getQualifiers () const
//{
//    return m_Qualifiers;
//}


//std::vector<MI_PropertyDecl::ConstPtr> const&
//MI_ClassDecl::getPropertyDecls () const
//{
//    return m_PropertyDecls;
//}


MI_Value<MI_STRING>::ConstPtr const&
MI_ClassDecl::getSuperClassName () const
{
    return m_pSuperClassName;
}


MI_ClassDecl::ConstPtr const&
MI_ClassDecl::getSuperClassDecl () const
{
    return m_pSuperClassDecl;
}


std::vector<MI_MethodDecl::Ptr> const&
MI_ClassDecl::getMethodDecls () const
{
    return m_MethodDecls;
}


MI_SchemaDecl::ConstPtr const&
MI_ClassDecl::getSchemaDecl () const
{
    return m_pSchemaDecl;
}


MI_FunctionTable::ConstPtr const&
MI_ClassDecl::getFunctionTable () const
{
    return m_pFunctionTable;
}


MI_ClassDecl::ConstPtr const&
MI_ClassDecl::getOwningClassDecl () const
{
    return m_pOwningClassDecl;
}


#if (1)
#define CD_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define CD_PRINT(X)
#endif

int
MI_ClassDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("send ClassDecl");
    int rval = MI_ObjectDecl::send (sock);
//    int rval = socket_wrapper::SUCCESS;
//    CD_PRINT ("send flags");
//    rval = m_pFlags->send (sock);
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        CD_PRINT ("send code");
//        rval = m_pCode->send (sock);
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        SCX_BOOKEND ("send name");
//        std::ostringstream strm;
//        strm<< "name: \""<< m_pName->getValue () << "\"";
//        CD_PRINT (strm.str ());
//        rval = m_pName->send (sock);
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        CD_PRINT ("send qualifiers size");
//        rval = protocol::send_item_count (m_Qualifiers.size (), sock);
//        for (std::vector<MI_Qualifier::ConstPtr>::const_iterator
//                 pos = m_Qualifiers.begin (),
//                 endPos = m_Qualifiers.end ();
//             socket_wrapper::SUCCESS == rval &&
//                 pos != endPos;
//             ++pos)
//        {
//            CD_PRINT ("... send qualifier");
//            rval = (*pos)->send (sock);
//        }
//    }
//    if (socket_wrapper::SUCCESS == rval)
//    {
//        std::ostringstream strm;
//        strm << "send property decl size: " << m_PropertyDecls.size ();
//        CD_PRINT (strm.str ());
//        strm.str ("");
//        strm.clear ();
//        rval = protocol::send_item_count (m_PropertyDecls.size (), sock);
//        for (std::vector<MI_PropertyDecl::ConstPtr>::const_iterator
//                 pos = m_PropertyDecls.begin (),
//                 endPos = m_PropertyDecls.end ();
//             socket_wrapper::SUCCESS == rval &&
//                 pos != endPos;
//             ++pos)
//        {
//            CD_PRINT ("... send property decl");
//            rval = (*pos)->send (sock);
//        }
//    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CD_PRINT ("send super class name");
        rval = protocol::send (m_pSuperClassName, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CD_PRINT ("send method decl size");
        rval = protocol::send_item_count (m_MethodDecls.size (), sock);
        for (std::vector<MI_MethodDecl::Ptr>::const_iterator
                 pos = m_MethodDecls.begin (),
                 endPos = m_MethodDecls.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            CD_PRINT ("... send method decl");
            rval = (*pos)->send (sock);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CD_PRINT ("send function table");
        rval = m_pFunctionTable->send (sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CD_PRINT ("send owning class name");
        MI_Char const* const owningClassName =
            m_pOwningClassDecl ?
                m_pOwningClassDecl->getName ()->getValue ().c_str () : 0;
        rval = protocol::send (owningClassName, sock);
    }
    return rval;
}


/*ctor*/
MI_SchemaDecl::MI_SchemaDecl (
    MI_QualifierDecl::ConstPtr const* const ppQualifierDecls,
    size_t const&  qualifierDeclCount,
    MI_ClassDecl::Ptr const* const ppClassDecls,
    size_t const& classDeclCount)
    : m_QualifierDecls (ppQualifierDecls, ppQualifierDecls + qualifierDeclCount)
    , m_ClassDecls (ppClassDecls, ppClassDecls + classDeclCount)
{
    SCX_BOOKEND ("MI_SchemaDecl::ctor");
    // sort the class decls by name
    std::sort (m_ClassDecls.begin (), m_ClassDecls.end (), classDeclSort);
    // loop through all of the class decls to set schema decl members
    for (std::vector<MI_ClassDecl::Ptr>::iterator pos = m_ClassDecls.begin (),
             endPos = m_ClassDecls.end ();
         pos != endPos;
         ++pos)
    {
        (*pos)->m_pSchemaDecl = this;
        for (std::vector<MI_MethodDecl::Ptr>::iterator
                 methodPos = (*pos)->m_MethodDecls.begin (),
                 methodEndPos = (*pos)->m_MethodDecls.end ();
             methodPos != methodEndPos;
             ++methodPos)
        {
            (*methodPos)->m_pSchemaDecl = this;
        }
    }
}


/*dtor*/
MI_SchemaDecl::~MI_SchemaDecl ()
{
    SCX_BOOKEND ("MI_SchemaDecl::dtor");
    // remove the references from the class decls
    for (std::vector<MI_ClassDecl::Ptr>::iterator pos = m_ClassDecls.begin (),
             endPos = m_ClassDecls.end ();
         pos != endPos;
         ++pos)
    {
        (*pos)->m_pSchemaDecl.reset ();
        for (std::vector<MI_MethodDecl::Ptr>::iterator
                 methodPos = (*pos)->m_MethodDecls.begin (),
                 methodEndPos = (*pos)->m_MethodDecls.end ();
             methodPos != methodEndPos;
             ++methodPos)
        {
            (*methodPos)->m_pSchemaDecl.reset ();
        }
    }
}


MI_ClassDecl::ConstPtr
MI_SchemaDecl::getClassDecl (
    MI_Value<MI_STRING>::ConstPtr const& pClassName) const
{
    SCX_BOOKEND ("MI_SchemaDecl::getClassDecl");
    MI_ClassDecl::ConstPtr pClassDecl (
        findClassDecl (m_ClassDecls, pClassName));
    return pClassDecl;
}


int
MI_SchemaDecl::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_SchemaDecl::send");
    int rval = socket_wrapper::SUCCESS;
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send qualifierDecls");
        rval = protocol::send_item_count (m_QualifierDecls.size (), sock);
        for (std::vector<MI_QualifierDecl::ConstPtr>::const_iterator
                 pos = m_QualifierDecls.begin (),
                 endPos = m_QualifierDecls.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            rval = (*pos)->send (sock);
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCX_BOOKEND ("send classDecls");
        rval = protocol::send_item_count (m_ClassDecls.size (), sock);
        for (std::vector<MI_ClassDecl::Ptr>::const_iterator
                 pos = m_ClassDecls.begin (),
                 endPos = m_ClassDecls.end ();
             socket_wrapper::SUCCESS == rval &&
                 pos != endPos;
             ++pos)
        {
            rval = (*pos)->send (sock);
        }
    }
    return rval;
}
    

} // namespace scx
