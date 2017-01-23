#include "py_gen.hpp"


#include "QualifierDecls.h"


#include <base/types.h>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace
{


#define IF_FLAG_STRM(value,flag) \
    if (flag == (flag & value)) \
    { \
        if (count++) strm << " | "; \
        strm << #flag; \
    } \
    else


static char const STATIC_MARKER[] = "# @" "migen" "@";
static char const WARNING_TEXT[] =
    "WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.";
static char const QUALIFIERDECL_TEXT[] = "Qualifier declarations";


class CommentBox
{
public:
    /*ctor*/ CommentBox (char const* const text)
        : m_Text (text)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        strm << "##======================================"
            "========================================" << std::endl;
        strm << "##" << std::endl;
        strm << "## " << m_Text << std::endl;
        strm << "##" << std::endl;
        strm << "##======================================"
            "========================================" << std::endl;
        return strm;
    }

private:
    char const* const m_Text;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    CommentBox const& comment)
{
    return comment.to_stream (strm);
}


MI_QualifierDecl const*
FindStandardQualifierDecl (
    char const* name)
{
    MI_QualifierDecl const* const* pos = g_qualifierDecls;
    MI_QualifierDecl const* const* const endPos =
        g_qualifierDecls + g_numQualifierDecls;
    for (;
         pos != endPos && !Strcasecmp ((*pos)->name, name);
         ++pos)
    {
        continue;
    }
    return pos != endPos ? *pos : NULL;
}


class GenScope
{
public:
    /*ctor*/ GenScope (MI_Uint32 const& scope)
        : m_Scope (scope)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        if (MI_FLAG_ANY == m_Scope & MI_FLAG_ANY)
        {
            strm << "MI_FLAG_ANY";
        }
        else
        {
            size_t count = 0;
            IF_FLAG_STRM (m_Scope, MI_FLAG_ASSOCIATION);
            IF_FLAG_STRM (m_Scope, MI_FLAG_CLASS);
            IF_FLAG_STRM (m_Scope, MI_FLAG_INDICATION);
            IF_FLAG_STRM (m_Scope, MI_FLAG_METHOD);
            IF_FLAG_STRM (m_Scope, MI_FLAG_PARAMETER);
            IF_FLAG_STRM (m_Scope, MI_FLAG_PROPERTY);
            IF_FLAG_STRM (m_Scope, MI_FLAG_REFERENCE);
            if (0 == count)
            {
                strm << "0";
            }
        }
        return strm;
    }

private:
    MI_Uint32 const m_Scope;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    GenScope const& scope)
{
    return scope.to_stream (strm);
}


class GenFlavor
{
public:
    /*ctor*/ GenFlavor (MI_Uint32 const& flavor)
        : m_Flavor (flavor)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        size_t count = 0;
        IF_FLAG_STRM (m_Flavor, MI_FLAG_ENABLEOVERRIDE);
        IF_FLAG_STRM (m_Flavor, MI_FLAG_DISABLEOVERRIDE);
        IF_FLAG_STRM (m_Flavor, MI_FLAG_TOSUBCLASS);
        IF_FLAG_STRM (m_Flavor, MI_FLAG_TRANSLATABLE);
        IF_FLAG_STRM (m_Flavor, MI_FLAG_RESTRICTED);
        if (0 == count)
        {
            strm << "0";
        }
        return strm;
    }

private:
    MI_Uint32 const m_Flavor;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    GenFlavor const& flavor)
{
    return flavor.to_stream (strm);
}


class GenType
{
public:
    /*ctor*/ GenType (MI_Type const& type)
        : m_Type (type)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        strm << "MI_";
        switch (~MI_ARRAY_BIT & m_Type)
        {
        case MI_BOOLEAN:
            strm << "Boolean";
            break;
        case MI_UINT8:
            strm << "Uint8";
            break;
        case MI_SINT8:
            strm << "Sint8";
            break;
        case MI_UINT16:
            strm << "Uint16";
            break;
        case MI_SINT16:
            strm << "Sint16";
            break;
        case MI_UINT32:
            strm << "Uint32";
            break;
        case MI_SINT32:
            strm << "Sint32";
            break;
        case MI_UINT64:
            strm << "Uint64";
            break;
        case MI_SINT64:
            strm << "Sint64";
            break;
        case MI_REAL32:
            strm << "Real32";
            break;
        case MI_REAL64:
            strm << "Real64";
            break;
        case MI_STRING:
            strm << "String";
            break;
        case MI_CHAR16:
            strm << "Char16";
            break;
        case MI_DATETIME:
            strm << "Datetime";
            break;
        case MI_INSTANCE:
            strm << "Instance";
            break;
        case MI_REFERENCE:
            strm << "Reference";
            break;
        }
        if (MI_ARRAY_BIT & m_Type)
        {
            strm << "A";
        }
        return strm;
    }

private:
    MI_Type const m_Type;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    GenType const& genType)
{
    return genType.to_stream (strm);
}


class GenTYPE
{
public:
    /*ctor*/ GenTYPE (MI_Type const& type)
        : m_Type (type)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        strm << "MI_";
        switch (~MI_ARRAY_BIT & m_Type)
        {
        case MI_BOOLEAN:
            strm << "BOOLEAN";
            break;
        case MI_UINT8:
            strm << "UINT8";
            break;
        case MI_SINT8:
            strm << "SINT8";
            break;
        case MI_UINT16:
            strm << "UINT16";
            break;
        case MI_SINT16:
            strm << "SINT16";
            break;
        case MI_UINT32:
            strm << "UINT32";
            break;
        case MI_SINT32:
            strm << "SINT32";
            break;
        case MI_UINT64:
            strm << "UINT64";
            break;
        case MI_SINT64:
            strm << "SINT64";
            break;
        case MI_REAL32:
            strm << "REAL32";
            break;
        case MI_REAL64:
            strm << "REAL64";
            break;
        case MI_STRING:
            strm << "STRING";
            break;
        case MI_CHAR16:
            strm << "CHAR16";
            break;
        case MI_DATETIME:
            strm << "DATETIME";
            break;
        case MI_INSTANCE:
            strm << "INSTANCE";
            break;
        case MI_REFERENCE:
            strm << "REFERENCE";
            break;
        }
        if (MI_ARRAY_BIT & m_Type)
        {
            strm << "A";
        }
        return strm;
    }
    
private:
    MI_Type const m_Type;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    GenTYPE const& genType)
{
    return genType.to_stream (strm);
}


class GenFlags
{
public:
    /*ctor*/ GenFlags (MI_Uint32 const& flags)
        : m_Flags (flags)
    {
        // empty
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        size_t count = 0;
        IF_FLAG_STRM (m_Flags, MI_FLAG_CLASS);
        IF_FLAG_STRM (m_Flags, MI_FLAG_METHOD);
        IF_FLAG_STRM (m_Flags, MI_FLAG_PROPERTY);
        IF_FLAG_STRM (m_Flags, MI_FLAG_PARAMETER);
        IF_FLAG_STRM (m_Flags, MI_FLAG_ASSOCIATION);
        IF_FLAG_STRM (m_Flags, MI_FLAG_INDICATION);
        IF_FLAG_STRM (m_Flags, MI_FLAG_REFERENCE);
        IF_FLAG_STRM (m_Flags, MI_FLAG_KEY);
        IF_FLAG_STRM (m_Flags, MI_FLAG_IN);
        IF_FLAG_STRM (m_Flags, MI_FLAG_OUT);
        IF_FLAG_STRM (m_Flags, MI_FLAG_REQUIRED);
        IF_FLAG_STRM (m_Flags, MI_FLAG_STATIC);
        IF_FLAG_STRM (m_Flags, MI_FLAG_ABSTRACT);
        IF_FLAG_STRM (m_Flags, MI_FLAG_TERMINAL);
        IF_FLAG_STRM (m_Flags, MI_FLAG_EXPENSIVE);
        IF_FLAG_STRM (m_Flags, MI_FLAG_STREAM);
        IF_FLAG_STRM (m_Flags, MI_FLAG_ENABLEOVERRIDE);
        IF_FLAG_STRM (m_Flags, MI_FLAG_DISABLEOVERRIDE);
        IF_FLAG_STRM (m_Flags, MI_FLAG_RESTRICTED);
        IF_FLAG_STRM (m_Flags, MI_FLAG_TOSUBCLASS);
        IF_FLAG_STRM (m_Flags, MI_FLAG_TRANSLATABLE);
        if (0 == count)
        {
            strm << "0";
        }
        return strm;
    }

private:
    MI_Uint32 const m_Flags;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    GenFlags const& flags)
{
    return flags.to_stream (strm);
}


class InitValue
{
public:
    /*ctor*/ InitValue (
        MI_Type const& type,
        void const* const pValue)
        : m_Type (type)
        , m_pValue (pValue)
    {
        assert (pValue);
        assert (MI_ARRAY_BIT != (type & MI_ARRAY_BIT));
    }

    template<typename CHAR_t, typename TRAITS>
    std::basic_ostream<CHAR_t, TRAITS>&
    to_stream (std::basic_ostream<CHAR_t, TRAITS>& strm) const
    {
        switch (m_Type)
        {
        case MI_BOOLEAN:
            if (MI_FALSE == *reinterpret_cast<MI_Boolean const*>(m_pValue))
            {
                strm << "False";
            }
            else
            {
                strm << "True";
            }
            break;
        case MI_UINT8:
            strm << static_cast<unsigned int>(
                *reinterpret_cast<MI_Uint8 const*>(m_pValue));
            break;
        case MI_SINT8:
            strm << static_cast<int>(
                *reinterpret_cast<MI_Sint8 const*>(m_pValue));
            break;
        case MI_UINT16:
            strm << *reinterpret_cast<MI_Uint16 const*>(m_pValue);
            break;
        case MI_SINT16:
            strm << *reinterpret_cast<MI_Sint16 const*>(m_pValue);
            break;
        case MI_UINT32:
            strm << *reinterpret_cast<MI_Uint32 const*>(m_pValue);
            break;
        case MI_SINT32:
            strm << *reinterpret_cast<MI_Sint32 const*>(m_pValue);
            break;
        case MI_UINT64:
            strm << *reinterpret_cast<MI_Uint64 const*>(m_pValue);
            break;
        case MI_SINT64:
            strm << *reinterpret_cast<MI_Sint64 const*>(m_pValue);
            break;
        case MI_REAL32:
            strm << *reinterpret_cast<MI_Real32 const*>(m_pValue);
            break;
        case MI_REAL64:
            strm << *reinterpret_cast<MI_Real64 const*>(m_pValue);
            break;
        case MI_STRING:
            strm << '\'';
            for (char const* pos =
                     reinterpret_cast<char const*>(m_pValue);
                 *pos;
                 ++pos)
            {
                if (isprint (*pos))
                {
                    strm << *pos;
                }
                else
                {
                    strm << '\\' << std::setw (4) << std::setfill ('0')
                         << static_cast<int const>(*pos);
                }
            }
            strm << '\'';
            break;
        case MI_CHAR16:
            strm << *reinterpret_cast<MI_Char16 const*>(m_pValue);
            break;
        case MI_DATETIME:
        {
            const MI_Datetime& x =
                *reinterpret_cast<MI_Datetime const*>(m_pValue);
            if (x.isTimestamp)
            {
                strm << "MI_TimeStamp ("
                     << x.u.timestamp.year << ','
                     << x.u.timestamp.month << ','
                     << x.u.timestamp.day << ','
                     << x.u.timestamp.hour << ','
                     << x.u.timestamp.minute << ','
                     << x.u.timestamp.second << ','
                     << x.u.timestamp.microseconds << ','
                     << x.u.timestamp.utc << ')';
            }
            else
            {
                strm << "MI_TimeStamp ("
                     << x.u.interval.days << ','
                     << x.u.interval.hours << ','
                     << x.u.interval.minutes << ','
                     << x.u.interval.seconds << ','
                     << x.u.interval.microseconds << ')';
            }
            break;
        }
        case MI_INSTANCE:
        case MI_REFERENCE:
        default:
            // these cases are not implemented!
            break;
        }
        return strm;
    }

private:
    MI_Type const m_Type;
    void const* const m_pValue;
};


template<typename CHAR_t, typename TRAITS>
std::basic_ostream<CHAR_t, TRAITS>&
operator << (
    std::basic_ostream<CHAR_t, TRAITS>& strm,
    InitValue const& value)
{
    return value.to_stream (strm);
}


template<typename CHAR_t, typename TRAITS>
void
GenValue (
    std::string const& name,
    MI_Type const& type,
    void const* pValue,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    if (pValue)
    {
        strm << name << "_value = " << GenType (type) << " ("
             << std::endl;
        if (MI_ARRAY_BIT == (type & MI_ARRAY_BIT))
        {
            strm << "[" << std::endl;
            if (MI_STRINGA == type)
            {
                MI_StringA const* pArray =
                    reinterpret_cast<MI_StringA const*>(pValue);
                for (MI_Char** pos = pArray->data,
                         ** endPos = pArray->data + pArray->size;
                     pos != endPos;
                     ++pos)
                {
                    strm << "    "
                         << InitValue (static_cast<MI_Type>(MI_STRING), *pos)
                         << "," << std::endl;
                }
            }
            else
            {
                MI_Array const* pArray =
                    reinterpret_cast<MI_Array const*>(pValue);
                unsigned char const* pBlob =
                    reinterpret_cast<unsigned char const*>(pArray->data);
                for (MI_Uint32 index = 0; index < pArray->size; ++index)
                {
                    strm << "    "
                         << InitValue (static_cast<MI_Type>(
                                           type & ~MI_ARRAY_BIT),
                                       pBlob)
                         << "," << std::endl;
                    pBlob += Type_SizeOf (static_cast<MI_Type>(
                                              type & ~MI_ARRAY_BIT));
                }
            }
            strm << "    ])" << std::endl << std::endl;
        }
        else
        {
            strm << "    " << InitValue (type, pValue) << ")" << std::endl
                 << std::endl;
        }
    }
}


template<typename CHAR_t, typename TRAITS>
int
GenQualifierDecl (
    GeneratorOptions const& options,
    Parser& parser,
    MI_QualifierDecl const* pQualifierDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::string name (pQualifierDecl->name);
    name.append ("_qual_decl");
    if (pQualifierDecl->value)
    {
        GenValue (name, static_cast<MI_Type>(pQualifierDecl->type),
                  pQualifierDecl->value, strm);
    }
    strm << name << " = MI_QualifierDecl (" << std::endl;
    strm << "    " << pQualifierDecl->name << ", # name" << std::endl;
    strm << "    " << GenTYPE (static_cast<MI_Type>(pQualifierDecl->type))
         << ", # type" << std::endl;
    strm << "    " << GenScope (pQualifierDecl->scope) << ", # scope"
         << std::endl;
    strm << "    " << GenFlavor (pQualifierDecl->flavor) << ", # flavor"
         << std::endl;
    strm << "    ";
    if (pQualifierDecl->value)
    {
        strm << name << "_value";
    }
    else
    {
        strm << "None";
    }
    strm << " # value" << std::endl;
    strm << "    )" << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenQualifierDecls (
    GeneratorOptions const& options,
    Parser& parser,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::basic_ostringstream<CHAR_t, TRAITS> tempStrm;
    tempStrm << "qualifierDecls = [" << std::endl;
    strm << CommentBox (QUALIFIERDECL_TEXT);
    std::vector<std::string> qualifierNames;
    parser.getQualifierDeclNames (qualifierNames);
    if (!options.ignoreAllQualifiers)
    {
        for (std::vector<std::string>::const_iterator
                 pos = qualifierNames.begin (), endPos = qualifierNames.end ();
             EXIT_SUCCESS == rval && pos != endPos;
             ++pos)
        {
            MI_QualifierDecl const* pQualifierDecl =
                parser.findQualifierDecl (*pos);
            if (pQualifierDecl)
            {
                if (options.standardQualifiers &&
                    NULL == FindStandardQualifierDecl (pQualifierDecl->name))
                {
                    rval = GenQualifierDecl (
                        options, parser, pQualifierDecl, strm);
                    tempStrm << "    " << pQualifierDecl->name << "_qual_decl,"
                             << std::endl;
                }
            }
            else
            {
                std::cerr << "unknown qualifier: " << *pos << std::endl;
                rval = EXIT_FAILURE;
            }
        }
    }
    strm << tempStrm.str () << "    ]" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenQualifier (
    GeneratorOptions const& options,
    Parser& parser,
    std::string const& qualifierName,
    MI_Qualifier const* pQualifier,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    MI_QualifierDecl const* pQualifierDecl =
        parser.findQualifierDecl (pQualifier->name);
    if (pQualifierDecl)
    {
        if (pQualifier->value)
        {
            GenValue (qualifierName,
                      static_cast<MI_Type>(pQualifier->type),
                      pQualifier->value, strm);
        }
        strm << qualifierName << " = MI_Qualifier (" << std::endl;
        strm << "    \'" << pQualifier->name << "\'," << std::endl;
        strm << "    " << GenTYPE (static_cast<MI_Type>(pQualifier->type))
             << "," << std::endl;
        strm << "    " << GenFlavor (pQualifier->flavor) <<"," << std::endl;
        if (pQualifier->value)
        {
            strm << "    " << qualifierName << "_value";
        }
        else
        {
            strm << "    None";
        }
        strm << std::endl << "    )" << std::endl << std::endl;
    }
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenQualifiers (
    GeneratorOptions const& options,
    Parser& parser,
    std::string const& baseName,
    MI_Qualifier const* const* ppQualifiers,
    MI_Uint32 numQualifiers,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream tempStrm;
    tempStrm << baseName << "_quals = [" << std::endl;
    if (!options.ignoreAllQualifiers)
    {
        for (MI_Qualifier const* const* pos = ppQualifiers,
                 * const * endPos = ppQualifiers + numQualifiers;
             pos != endPos;
             ++pos)
        {
            if (!options.booleanQualifiers &&
                MI_BOOLEAN == (*pos)->type)
            {
                continue;
            }
            if (!options.descriptions &&
                0 == Strcasecmp ((*pos)->name, "Description"))
            {
                continue;
            }
            if (!options.values &&
                (0 == Strcasecmp ((*pos)->name, "Values") ||
                 0 == Strcasecmp ((*pos)->name, "ValueMap")))
            {
                continue;
            }
            if (!options.mappingStrings &&
                0 == Strcasecmp ((*pos)->name, "MappingStrings"))
            {
                continue;
            }
            if (!options.modelCorrespondence &&
                0 == Strcasecmp ((*pos)->name, "ModelCorrespondence"))
            {
                continue;
            }
            std::ostringstream qualifierName;
            qualifierName << baseName << "_" << (*pos)->name << "_qual";
            GenQualifier (options, parser, qualifierName.str (), *pos, strm);
            tempStrm << "    " << qualifierName.str () << "," << std::endl;
        }
    }
    strm << tempStrm.str () << "    ]" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenPropertyDecl (
    GeneratorOptions const& options,
    Parser& parser,
    MI_ClassDecl const* pClassDecl,
    MI_PropertyDecl const* pPropertyDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream propertyName;
    propertyName << pClassDecl->name << "_" << pPropertyDecl->name;
    rval = GenQualifiers (
        options, parser, propertyName.str (), pPropertyDecl->qualifiers,
        pPropertyDecl->numQualifiers, strm);
    if (pPropertyDecl->value)
    {
        GenValue (propertyName.str (),
                  static_cast<MI_Type>(pPropertyDecl->type),
                  pPropertyDecl->value, strm);
    }
    strm << propertyName.str () << "_prop = MI_PropertyDecl (" << std::endl;
    strm << "    " << GenFlags (pPropertyDecl->flags) << ", # flags"
         << std::endl;
    strm << "    \'" << pPropertyDecl->name << "\', # name" << std::endl;
    strm << "    " << propertyName.str () << "_quals, # qualifiers"
         << std::endl;
    strm << "    " << GenTYPE (static_cast<MI_Type>(pPropertyDecl->type))
         << ", # type" << std::endl;
    strm << "    None, # className" << std::endl;
    strm << "    \'" << pPropertyDecl->origin << "\', # origin" << std::endl;
    strm << "    \'" << pPropertyDecl->propagator << "\', # propagator"
         << std::endl;
    strm << "    ";
    if (pPropertyDecl->value)
    {
        strm << propertyName.str () << "_value";
    }
    else
    {
        strm << "None";
    }
    strm << " # value" << std::endl << "    )" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenPropertyDecls (
    GeneratorOptions const& options,
    Parser& parser,
    MI_ClassDecl const* pClassDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream tempStrm;
    tempStrm << pClassDecl->name << "_properties = [" << std::endl;
    for (MI_PropertyDecl const* const* pPropertyDecl = pClassDecl->properties,
             * const * endPos =
             pClassDecl->properties + pClassDecl->numProperties;
         pPropertyDecl != endPos;
         ++pPropertyDecl)
    {
        GenPropertyDecl (options, parser, pClassDecl, *pPropertyDecl, strm);
        tempStrm << "    " << pClassDecl->name << "_" << (*pPropertyDecl)->name
                 << "_prop," << std::endl;
    }
    strm << tempStrm.str () << "    ]" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenParameterDecl (
    GeneratorOptions const& options,
    Parser& parser,
    std::string const& paramName,
    MI_ParameterDecl const* pParameterDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = GenQualifiers (
        options, parser, paramName, pParameterDecl->qualifiers,
        pParameterDecl->numQualifiers, strm);
    strm << paramName << "_param = MI_ParameterDecl (" << std::endl;
    strm << "    " << GenFlags (pParameterDecl->flags) << ", # flags"
         << std::endl;
    strm << "    \'" << pParameterDecl->name << "\', # name" << std::endl;
    strm << "    " << paramName << "_quals, # qualifiers" << std::endl;
    strm << "    " << GenTYPE (static_cast<MI_Type>(pParameterDecl->type))
         << ", # type" << std::endl;
    strm << "    None # className" << std::endl;
    strm << "    )" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenParameterDecls (
    GeneratorOptions const& options,
    Parser& parser,
    std::string const& nameBase,
    MI_MethodDecl const* pMethodDecl,
    MI_ParameterDecl const* const* parameters,
    MI_Uint32 numParameters,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream tempStrm;
    tempStrm << nameBase << "_params = [" << std::endl;
    for (MI_ParameterDecl const* const* pParameterDecl = parameters,
             * const* endPos = parameters + numParameters;
         pParameterDecl != endPos;
         ++pParameterDecl)
    {
        std::ostringstream paramName;
        paramName << nameBase << "_" << (*pParameterDecl)->name;
        GenParameterDecl (options, parser, paramName.str (), *pParameterDecl,
                          strm);
        tempStrm << "    " << paramName.str () << "_param," << std::endl;
    }
    MI_ParameterDecl returnParam;
    memset (&returnParam, 0, sizeof (returnParam));
    returnParam.flags = MI_FLAG_PARAMETER | MI_FLAG_OUT;
    returnParam.name = "MIReturn";
    returnParam.type = pMethodDecl->returnType;
    returnParam.qualifiers = pMethodDecl->qualifiers;
    returnParam.numQualifiers = pMethodDecl->numQualifiers;
    std::ostringstream paramName;
    paramName << nameBase << "_" << returnParam.name;
    GenParameterDecl (options, parser, paramName.str (), &returnParam, strm);
    strm << tempStrm.str ();
    strm << "    " << paramName.str () << "_param," << std::endl << "    ]"
         << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenMethodDecl (
    GeneratorOptions const& options,
    Parser& parser,
    std::string const& name,
    MI_MethodDecl const* pMethodDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    GenQualifiers (
        options, parser, name, pMethodDecl->qualifiers,
        pMethodDecl->numQualifiers, strm);
    GenParameterDecls (
        options, parser, name, pMethodDecl, pMethodDecl->parameters,
        pMethodDecl->numParameters, strm);
    strm << name << "_method = MI_MethodDecl (" << std::endl;
    strm << "    " << GenFlags (pMethodDecl->flags) << ", # flags" << std::endl;
    strm << "    \'" << pMethodDecl->name << "\', # name" << std::endl;
    strm << "    " << name << "_quals, # qualifiers" << std::endl;
    strm << "    " << name << "_params, # parameters" << std::endl;
    strm << "    " << GenTYPE (static_cast<MI_Type>(pMethodDecl->returnType))
         << ", # returnType" << std::endl;
    strm << "    \'" << pMethodDecl->origin << "\', # origin" << std::endl;
    strm << "    \'" << pMethodDecl->propagator << "\', # propagator"
         << std::endl;
    strm << "    \'" << name << "\' # method" << std::endl;
    strm << "    )" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenMethodDecls (
    GeneratorOptions const& options,
    Parser& parser,
    MI_ClassDecl const* pClassDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream tempStrm;
    tempStrm << pClassDecl->name << "_methods = [" << std::endl;
    for (MI_MethodDecl const* const* pMethodDecl = pClassDecl->methods,
             * const* endPos = pClassDecl->methods + pClassDecl->numMethods;
         pMethodDecl != endPos;
         ++pMethodDecl)
    {
        std::ostringstream methodName;
        methodName << pClassDecl->name << "_" << (*pMethodDecl)->name;
        GenMethodDecl (options, parser, methodName.str (), *pMethodDecl, strm);
        tempStrm << "    " << methodName.str () << "_method," << std::endl;
    }
    strm << tempStrm.str () << "    ]" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenFunctionTable (
    GeneratorOptions const& options,
    Parser& parser,
    MI_ClassDecl const* pClassDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    strm << pClassDecl->name << "_functions = MI_FunctionTable (" << std::endl;
    strm << "    \'" << pClassDecl->name << "_Load\'," << std::endl;
    strm << "    \'" << pClassDecl->name << "_Unload\'," << std::endl;
    strm << "    \'" << pClassDecl->name << "_GetInstance\'," << std::endl;
    strm << "    \'" << pClassDecl->name << "_EnumerateInstances\',"
         << std::endl;
    strm << "    \'" << pClassDecl->name << "_CreateInstance\'," << std::endl;
    strm << "    \'" << pClassDecl->name << "_ModifyInstance\'," << std::endl;
    strm << "    \'" << pClassDecl->name << "_DeleteInstance\'," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None," << std::endl;
    strm << "    None" << std::endl;
    strm << "    )" << std::endl << std::endl;
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenClassDecl (
    GeneratorOptions const& options,
    Parser& parser,
    MI_ClassDecl const* pClassDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    strm << CommentBox (pClassDecl->name);
    GenQualifiers (
        options, parser, pClassDecl->name, pClassDecl->qualifiers,
        pClassDecl->numQualifiers, strm);
    GenPropertyDecls (options, parser, pClassDecl, strm);
    GenMethodDecls (options, parser, pClassDecl, strm);
    GenFunctionTable (options, parser, pClassDecl, strm);
    strm << pClassDecl->name << "_class = MI_ClassDecl (" << std::endl;
    strm << "    " << GenFlags (pClassDecl->flags) << ", # flags" << std::endl;
    strm << "    \'" << pClassDecl->name << "\', # name" << std::endl;
    strm << "    " << pClassDecl->name << "_quals, # gualifiers" << std::endl;
    strm << "    " << pClassDecl->name << "_properties, # properties"
         << std::endl;
    strm << "    None, # superclass" << std::endl;
    strm << "    " << pClassDecl->name << "_methods, # method" << std::endl;
    strm << "    " << pClassDecl->name << "_functions, # FunctionTable"
         << std::endl;
    strm << "    None # owningclass" << std::endl;
    strm << "    )" << std::endl << std::endl;
    return rval;
}


} // namespace unnamed


int
GenSchemaSourceFile_Py (
    GeneratorOptions const& options,
    Parser& parser,
    std::vector<std::string> const& classNames)
{
    int rval = EXIT_SUCCESS;
    std::string outputFileName;
    if (0 < options.dir.size ())
    {
        outputFileName = options.dir + '/';
    }
    outputFileName += "schema.py";
    std::ofstream outputFile (
        outputFileName.c_str (), std::ofstream::out | std::ofstream::trunc);
    if (outputFile.is_open ())
    {
        std::cout << "Creating \"" << outputFileName << "\"" << std::endl;
        outputFile << STATIC_MARKER << std::endl;
        outputFile << CommentBox (WARNING_TEXT);
        outputFile << "import omi" << std::endl;
        outputFile << "from omi import *" << std::endl << std::endl;
        rval = GenQualifierDecls (options, parser, outputFile);
        std::ostringstream tempStrm;
        tempStrm << "classDecls = [" << std::endl;
        for (std::vector<std::string>::const_iterator pos = classNames.begin (),
                 endPos = classNames.end ();
             EXIT_SUCCESS == rval && pos != endPos;
             ++pos)
        {
            MI_ClassDecl const* pClassDecl =
                parser.findClassDecl (pos->c_str ());
            if (pClassDecl)
            {
                GenClassDecl (options, parser, pClassDecl, outputFile);
                tempStrm << "    " << pClassDecl->name << "_class,"
                         << std::endl;
            }
            else
            {
                std::cerr << "unknown class: " << *pos << std::endl;
                rval = EXIT_FAILURE;
            }
        }
        outputFile << tempStrm.str () << "    ]" << std::endl
                   << std::endl;
        outputFile << "schema = MI_SchemaDecl (" << std::endl;
        outputFile << "    qualifierDecls," << std::endl;
        outputFile << "    classDecls" << std::endl;
        outputFile << "    )" << std::endl;
    }
    else
    {
        std::cerr << "failed to open file: \"" << outputFileName << "\""
                  << std::endl;
        rval = EXIT_FAILURE;
    }
    return rval;
}


template<typename CHAR_t, typename TRAITS>
int
GenClassFnDefs (
    MI_ClassDecl const* pClassDecl,
    std::basic_ostream<CHAR_t, TRAITS>& strm)
{
    int rval = EXIT_SUCCESS;
    strm << "def " << pClassDecl->name << "_Load (" << std::endl;
    strm << "    module, context):" << std::endl;
    strm << "    context.PostResult (MI_RESULT_OK)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_Unload (" << std::endl;
    strm << "    context):" << std::endl;
    strm << "    context.PostResult (MI_RESULT_OK)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_EnumerateInstances ("
         << std::endl;
    strm << "    context, nameSpace, className, propertySet, keysOnly):"
         << std::endl;
    strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_GetInstance (" << std::endl;
    strm << "    context, nameSpace, className, instanceName, propertySet):"
         << std::endl;
    strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_CreateInstance (" << std::endl;
    strm << "    context, nameSpace, className, instance):"
         << std::endl;
    strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_ModifyInstance (" << std::endl;
    strm << "    context, nameSpace, className, instance, propertySet):"
         << std::endl;
    strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl;
    strm << std::endl << std::endl;
    strm << "def " << pClassDecl->name << "_DeleteInstance (" << std::endl;
    strm << "    context, nameSpace, className, instanceName):"
         << std::endl;
    strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl;
    strm << std::endl << std::endl;
    for (MI_MethodDecl const* const* pMethodDecl = pClassDecl->methods,
             * const* endPos = pClassDecl->methods + pClassDecl->numMethods;
         pMethodDecl != endPos;
         ++pMethodDecl)
    {
        strm << "def " << pClassDecl->name << "_" << (*pMethodDecl)->name
             << " (" << std::endl;
        strm << "    context, nameSpace, className, methodName, instanceName, "
            "parameters):" << std::endl;
        strm << "    context.PostResult (MI_RESULT_NOT_SUPPORTED)" << std::endl
             << std::endl << std::endl;
    }
    return rval;
}


int
GenMI_Main_Py (
    GeneratorOptions const& options,
    Parser& parser,
    std::vector<std::string> const& classNames)
{
    int rval = EXIT_SUCCESS;
    std::string outputFileName;
    if (0 < options.dir.size ())
    {
        outputFileName = options.dir + '/';
    }
    outputFileName += "mi_main.py";
    std::ofstream outputFile (
        outputFileName.c_str (), std::ofstream::out | std::ofstream::trunc);
    if (outputFile.is_open ())
    {
        std::cout << "Creating \"" << outputFileName << "\"" << std::endl;
        outputFile << "import omi" << std::endl;
        outputFile << "from omi import *" << std::endl;
        outputFile << std::endl;
        outputFile << "import schema" << std::endl;
        outputFile << std::endl << std::endl;
        outputFile << "def Load (module, context):" << std::endl;
        outputFile << "    context.PostResult (MI_RESULT_OK)" << std::endl;
        outputFile << std::endl << std::endl;
        outputFile << "def Unload (module, context):" << std::endl;
        outputFile << "    context.PostResult (MI_RESULT_OK)" << std::endl;
        outputFile << std::endl << std::endl;
        for (std::vector<std::string>::const_iterator pos = classNames.begin (),
                 endPos = classNames.end ();
             EXIT_SUCCESS == rval && pos != endPos;
             ++pos)
        {
            MI_ClassDecl const* pClassDecl =
                parser.findClassDecl (pos->c_str ());
            if (pClassDecl)
            {
                GenClassFnDefs (pClassDecl, outputFile);
            }
            else
            {
                std::cerr << "unknown class: " << *pos << std::endl;
                rval = EXIT_FAILURE;
            }
        }
        outputFile << "def mi_main ():" << std::endl;
        outputFile << "    r = MI_Module (schema.schema, Load, Unload)"
                   << std::endl;
        outputFile << "    return r" << std::endl;
    }
    else
    {
        std::cerr << "failed to open file: \"" << outputFileName << "\""
                  << std::endl;
        rval = EXIT_FAILURE;
    }
    return rval;
}
