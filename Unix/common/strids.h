/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
**==============================================================================
**
** strids.h
**
**     This file contains stub localization definitions for the generator tool.
**     A legitimate implementation should replace this file with a suitable
**     implementation that (1) provides definitions for each of the ID macros
**     below and (2) defines an implementation of LookupFormatString(), which
**     resolves ids to strings.
**
**==============================================================================
*/

#ifndef _strids_h
#define _strids_h

#include <common.h>
#include <string.h>
#ifdef _MSC_VER
#pragma prefast (disable: 28252)
#pragma prefast (disable: 28253)
#endif
#include <wchar.h>

enum
{
    ID_UNKNOWN_PRAGMA,
    ID_CLASS_ALREADY_DEFINED,
    ID_UNDEFINED_SUPERCLASS,
    ID_CLASS_FEATURE_ALREADY_DEFINED,
    ID_DUPLICATE_QUALIFIER,
    ID_UNDEFINED_QUALIFIER,
    ID_MISSING_QUALIFIER_INITIALIZER,
    ID_INVALID_QUALIFIER_INITIALIZER,
    ID_INVALID_INITIALIZER,
    ID_UNDEFINED_CLASS,
    ID_IGNORED_INITIALIZER,
    ID_PARAMETER_ALREADY_DEFINED,
    ID_ILLEGAL_ARRAY_SUBSCRIPT,
    ID_INCOMPATIBLE_FLAVORS,
    ID_INITIALIZER_OUT_OF_RANGE,
    ID_INTERNAL_ERROR,
    ID_QUALIFIER_ALREADY_DECLARED,
    ID_WRONG_TYPE_FOR_QUALIFIER,
    ID_OUT_OF_MEMORY,
    ID_ILLEGAL_QUALIFIER_OVERRIDE,
    ID_KEY_MUTATION_ERROR,
    ID_KEY_TYPE_MUTATION_ERROR,
    ID_KEY_STRUCTURE_MUTATION_ERROR,
    ID_UNKNOWN_QUALIFIER,
    ID_ILLEGAL_SCOPE_FOR_QUALIFIER,
    ID_PROPERTY_CONSTRAINT_FAILURE,
    ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
    ID_OVERRIDE_QUALIFIER_NAME_MISMATCH,
    ID_UNDEFINED_CLASS_IN_EMBEDDEDINSTANCE_QUALIFIER,
    ID_FAILED_TO_FIND_INCLUDE_FILE,
    ID_UNTERMINATED_STRING_LITERAL,
    ID_FAILED_TO_OPEN_FILE,
    ID_ILLEGAL_HEX_CHARACTER,
    ID_INTEGER_OVERFLOW,
    ID_ILLEGAL_BINARY_LITERAL,
    ID_MOF_STACK_OVERFLOW,
    ID_MOF_STACK_UNDERFLOW,
    ID_EMBEDDEDINSTANCE_ON_NON_STRING,
    ID_UNKNOWN_SUPERCLASS_FOR,
    ID_REFERENCE_ARRAY_AS_PROPERTY,
    ID_RESERVED_PARAMETER_NAME,
    ID_FAILED_TO_READ_FILE,
    ID_CREATING,
    ID_PATCHING,
    ID_CHECKING,
    ID_SKIPPING,
    ID_FAILED_TO_FIND_PATCH_MARKER,
    ID_UNKNOWN_CLASS,
    ID_FAILED_TO_PATCH_MODULE,
    ID_INSUFFICIENT_REFERENCES,
    ID_MISSING_OPTION_ARGUMENT,
    ID_UNKNOWN_OPTION,
    ID_INVALID_SCHEMA_OPTION,
    ID_FAILED_TO_PARSE_MOF_FILE,
    ID_REFUSED_TO_GENERATE_PROVIDER_FOR_ABSTRACT_CLASS,
    ID_USAGE,
    ID_TRY_HELP,
    ID_SYNTAX_ERROR,
    ID_PARSER_STACK_OVERFLOW,
    ID_STREAM_QUALIFIER_ON_NON_ARRAY,
    ID_STREAM_QUALIFIER_ON_NON_OUTPUT,
    ID_UNDEFINED_PROPERTY,
    ID_INVALID_REFERENCE,
    ID_NON_STANDARD_COMPLIANT_CLASSNAME,
    ID_UNSUPPORTED
};

MI_INLINE wchar_t* LookupString(int id)
{
    MI_UNUSED(id);
    return NULL;
}

#endif /* _strids_h */
