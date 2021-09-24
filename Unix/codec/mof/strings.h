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
** strings.h
**
**     This file contains localization string definitions for the mofcodec library.
**     A legitimate implementation should replace this file with a suitable
**     implementation that (1) provides definitions for each of the ID macros
**     below and (2) defines an implementation of LookupFormatString(), which
**     resolves ids to strings.
**
**==============================================================================
*/

#ifndef _mof_strings_h
#define _mof_strings_h

#include "parser/stringids.h"

#define MI_STR(x) MI_T(x)

#define STR_ID_UNKNOWN_PRAGMA                   "Unknown pragma: %T=%T"
#define STR_ID_CLASS_ALREADY_DEFINED            "Class already declared: %T"
#define STR_ID_UNDEFINED_SUPERCLASS             "Class '%T' has undefined super class '%T'"
#define STR_ID_CLASS_FEATURE_ALREADY_DEFINED    "Class feature already defined: %T"
#define STR_ID_DUPLICATE_QUALIFIER              "Duplicate qualifier: %T"
#define STR_ID_UNDEFINED_QUALIFIER              "Undefined qualifier: %T"
#define STR_ID_MISSING_QUALIFIER_INITIALIZER    "Qualifier is missing initializer: %T"
#define STR_ID_INVALID_QUALIFIER_INITIALIZER    "Initializer for qualifier not valid: %T"
#define STR_ID_INVALID_INITIALIZER              "Initializer not valid"
#define STR_ID_UNDEFINED_CLASS                  "Undefined class: %T"
#define STR_ID_IGNORED_INITIALIZER              "Ignored initializer"
#define STR_ID_PARAMETER_ALREADY_DEFINED        "Parameter already defined: %T"
#define STR_ID_ILLEGAL_ARRAY_SUBSCRIPT          "Illegal array subscript: "
#define STR_ID_INCOMPATIBLE_FLAVORS             "Incompatible flavors: %T/%T"
#define STR_ID_INITIALIZER_OUT_OF_RANGE         "Initializer out of range: %I64d"
#define STR_ID_INTERNAL_ERROR                   "Internal error: %T(%u)"
#define STR_ID_QUALIFIER_ALREADY_DECLARED       "Qualifier already declared: %T"
#define STR_ID_WRONG_TYPE_FOR_QUALIFIER         "Wrong type for standard qualifier: %T"
#define STR_ID_OUT_OF_MEMORY                    "Out of memory"
#define STR_ID_ILLEGAL_QUALIFIER_OVERRIDE       "Illegal qualifier override: %T.%T.%T"
#define STR_ID_KEY_MUTATION_ERROR               "Property '%T' defined as [key] in class '%T', but was not key in base class"
#define STR_ID_KEY_TYPE_MUTATION_ERROR          "Key property '%T' redefined with different type in class '%T'"
#define STR_ID_KEY_STRUCTURE_MUTATION_ERROR     "New key property '%T' is introduced by class '%T'"
#define STR_ID_UNKNOWN_QUALIFIER                "Unknown qualifier: %T"
#define STR_ID_ILLEGAL_SCOPE_FOR_QUALIFIER      "Illegal scope for qualifier: %T"
#define STR_ID_PROPERTY_CONSTRAINT_FAILURE      "Value for property '%T' fails constraint given by '%T' qualifier"
#define STR_ID_PROPERTY_QUALIFIER_INCOMPATIBLE  "'%T' qualifier applied to incompatible property: '%T' with type: '%T'"
#define STR_ID_OVERRIDE_QUALIFIER_NAME_MISMATCH    "Name given by Override qualifier (%T) does not match property name (%T)"
#define STR_ID_UNDEFINED_CLASS_IN_EMBEDDEDINSTANCE_QUALIFIER    "Undefined class in EmbeddedInstance qualifier: %T"
#define STR_ID_UNTERMINATED_STRING_LITERAL      "Non-terminated string literal"
#define STR_ID_ILLEGAL_HEX_CHARACTER            "Illegal hex character: %T"
#define STR_ID_INTEGER_OVERFLOW                 "Integer overflow"
#define STR_ID_ILLEGAL_BINARY_LITERAL           "Illegal binary literal"
#define STR_ID_MOF_STACK_OVERFLOW               "MOF file stack overflow"
#define STR_ID_MOF_STACK_UNDERFLOW              "MOF file stack underflow"
#define STR_ID_FAILED_TO_READ_INCLUDE_FILE      "Failed to read content from include file: %T"
#define STR_ID_SYNTAX_ERROR                     "Syntax error: %T"
#define STR_ID_PARSER_STACK_OVERFLOW            "Parser stack overflow"
#define STR_ID_STREAM_QUALIFIER_ON_NON_ARRAY    "Stream qualifiers may only appear on array parameters: %T.%T(): %T"
#define STR_ID_STREAM_QUALIFIER_ON_NON_OUTPUT   "Stream qualifiers may only appear on output parameters: %T.%T(): %T"
#define STR_ID_UNDEFINED_PROPERTY               "Undefined property %T"
#define STR_ID_ERROR_DETAILS                    "\n At line:%d, char:%d"
#define STR_ID_ERROR_DETAILS_INCLUDED_FILE      "\n At file:%T, line:%d, char:%d"
#define STR_ID_ERROR_DETAILS_CONTENT            "\n Buffer:\n%T\n"
#define STR_ID_UNDEFINED_INSTANCE_ALIAS         "Undefined instance alias: %T"
#define STR_ID_CONVERT_PROPERTY_VALUE_FAILED    "Convert property '%T' value from type '%T' to type '%T' failed"
#define STR_ID_MI_CREATEINSTANCE_FAILED         "Create instance of class '%T' failed with error %d"
#define STR_ID_MI_SET_PROPERTY_FAILED           "Set value of property '%T' failed with error %d"
#define STR_ID_MI_ADD_PROPERTY_FAILED           "Add property '%T' failed"
#define STR_ID_ALIAS_DECL_ALREADY_DEFINED       "Instance alias: '%T' already declared at line %d"

#define STR_ID_SYNTAX_ERROR_INVALID_ALIAS_DECL               "Syntax Error. Alias name not valid at line %T"
#define STR_ID_SYNTAX_ERROR_INVALID_COMMENT                  "Syntax Error. Comment(s) incomplete, started at line:%d, char:%d"
#define STR_ID_SYNTAX_ERROR_INVALID_TOKEN                    "Syntax Error. Token not recognized: %T"
#define STR_ID_SYNTAX_ERROR_INCOMPLETE_STRING_VALUE          "Syntax Error. Literal string declaration is not complete, started at line:%d, char:%d"
#define STR_ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE             "Syntax Error. Char16 value declaration is not valid: %T"
#define STR_ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR16_VALUE     "Syntax Error. Escaped Char16 value declaration is not valid: %T, length (%d)"
#define STR_ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR             "Syntax Error. Unrecognized escaped character: %c"
#define STR_ID_SYNTAX_ERROR_INCOMPLETE_ESCAPED_CHAR16_VALUE  "Syntax Error. Escaped Char16 value is incomplete, started at line:%d, char:%d"
#define STR_ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE             "Syntax Error. Number value not valid: %T"

#define STR_ID_CREATE_PARSER_FAILED                          "Initialization of MOF parser failed"

#define STR_ID_PARAMETER_INVALID_OPTIONS_VALUE               "Unsupported value '%T' of operation option '%T'"
#define STR_ID_PARAMETER_INVALID_VALUE_STRING                "Unsupported value '%T' of parameter '%T'"
#define STR_ID_PARAMETER_INVALID_VALUE_NULL                  "Value of parameter '%T' can not be null"
#define STR_ID_PARAMETER_INVALID_VALUE_UNEXPECTED_INTEGER    "Value of parameter '%T' must be %d"
#define STR_ID_PARAMETER_INVALID_VALUE_OUT_OF_RANGE_INTEGER  "Value of parameter '%T' must be in the range of %d and %d, but it's value is %d"
#define STR_ID_PARAMETER_INVALID_BUFFER                      "Buffer is not supported. Check encoding and length of the buffer"

#define STR_ID_MI_CREATECLASS_FAILED            "Create class '%T' failed with error %d"

#define STR_ID_PARAMETER_UNEXPECTED_RESULTCLASSCOUNT         "Specified MOF buffer contains more than one class. Try '%T'"
#define STR_ID_PARAMETER_UNEXPECTED_RESULTINSTANCECOUNT      "Specified MOF buffer contains more than one instance. Try '%T'"

#define STR_ID_INVALID_EMBEDDEDPROPERTYVALUE_WRONG_TYPE      "Embedded (reference) property value not valid. The value object is of class type '%T', which is not '%T' or its derived classes."

#define STR_ID_INITIALIZER_OUT_OF_RANGE_DATETIMEVALUE "Datetime value not valid. Value %d of '%T' is out of valid range."

#endif
