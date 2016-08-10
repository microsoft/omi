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
** stringids.h
**
**     This file contains stub localization definitions for the mofcodec
**     component.
**
**     NOTE: All strings will be localized on windows platform,
**      while non-windows platform use in-memory strings directly.
**
**     STEPs of add or remove ID
**      (1) Add or remove ID(s) from stringid.h
**      (2) Add or remove corresponding item(s) from codec\mof\strings.h and 
**          strings.c
**      (3) Add or remove corresponding item(s) from codec\mof\mofcodec.rc
**==============================================================================
*/

#ifndef _mof_stringids_h
#define _mof_stringids_h

#define ID_UNKNOWN_PRAGMA 0
#define ID_CLASS_ALREADY_DEFINED 1
#define ID_UNDEFINED_SUPERCLASS 2
#define ID_CLASS_FEATURE_ALREADY_DEFINED 3
#define ID_DUPLICATE_QUALIFIER 4
#define ID_UNDEFINED_QUALIFIER 5
#define ID_MISSING_QUALIFIER_INITIALIZER 6
#define ID_INVALID_QUALIFIER_INITIALIZER 7
#define ID_INVALID_INITIALIZER 8
#define ID_UNDEFINED_CLASS 9
#define ID_IGNORED_INITIALIZER 10
#define ID_PARAMETER_ALREADY_DEFINED 11
#define ID_ILLEGAL_ARRAY_SUBSCRIPT 12
#define ID_INCOMPATIBLE_FLAVORS 13
#define ID_INITIALIZER_OUT_OF_RANGE 14
#define ID_INTERNAL_ERROR 15
#define ID_QUALIFIER_ALREADY_DECLARED 16
#define ID_WRONG_TYPE_FOR_QUALIFIER 17
#define ID_OUT_OF_MEMORY 18
#define ID_ILLEGAL_QUALIFIER_OVERRIDE 19
#define ID_KEY_MUTATION_ERROR 20
#define ID_KEY_TYPE_MUTATION_ERROR 21
#define ID_KEY_STRUCTURE_MUTATION_ERROR 22
#define ID_UNKNOWN_QUALIFIER 23
#define ID_ILLEGAL_SCOPE_FOR_QUALIFIER 24
#define ID_PROPERTY_CONSTRAINT_FAILURE 25
#define ID_PROPERTY_QUALIFIER_INCOMPATIBLE 26
#define ID_OVERRIDE_QUALIFIER_NAME_MISMATCH 27
#define ID_UNDEFINED_CLASS_IN_EMBEDDEDINSTANCE_QUALIFIER 28
#define ID_UNTERMINATED_STRING_LITERAL 29
#define ID_ILLEGAL_HEX_CHARACTER 30
#define ID_INTEGER_OVERFLOW 31
#define ID_ILLEGAL_BINARY_LITERAL 32
#define ID_MOF_STACK_OVERFLOW 33
#define ID_MOF_STACK_UNDERFLOW 34
#define ID_FAILED_TO_READ_INCLUDE_FILE 35
#define ID_SYNTAX_ERROR 36
#define ID_PARSER_STACK_OVERFLOW 37
#define ID_STREAM_QUALIFIER_ON_NON_ARRAY 38
#define ID_STREAM_QUALIFIER_ON_NON_OUTPUT 39
#define ID_UNDEFINED_PROPERTY 40
#define ID_ERROR_DETAILS 41
#define ID_ERROR_DETAILS_INCLUDED_FILE 42
#define ID_ERROR_DETAILS_CONTENT 43
#define ID_UNDEFINED_INSTANCE_ALIAS 44
#define ID_CONVERT_PROPERTY_VALUE_FAILED 45
#define ID_MI_CREATEINSTANCE_FAILED 46
#define ID_MI_SET_PROPERTY_FAILED 47
#define ID_MI_ADD_PROPERTY_FAILED 48
#define ID_ALIAS_DECL_ALREADY_DEFINED 49

/* SYNTAX ERROR IDS */
#define ID_SYNTAX_ERROR_INVALID_ALIAS_DECL 50
#define ID_SYNTAX_ERROR_INVALID_COMMENT 51            
#define ID_SYNTAX_ERROR_INVALID_TOKEN 52          
#define ID_SYNTAX_ERROR_INCOMPLETE_STRING_VALUE 53
#define ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE 54       
#define ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR16_VALUE 55
#define ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR 56  
#define ID_SYNTAX_ERROR_INCOMPLETE_ESCAPED_CHAR16_VALUE 57
#define ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE 58

/* SYNTAX ERROR IDS */
#define ID_CREATE_PARSER_FAILED 59

/* PARAMETER ERROR IDS */
#define ID_PARAMETER_INVALID_OPTIONS_VALUE 60
#define ID_PARAMETER_INVALID_VALUE_STRING 61
#define ID_PARAMETER_INVALID_VALUE_NULL 62
#define ID_PARAMETER_INVALID_VALUE_UNEXPECTED_INTEGER 63
#define ID_PARAMETER_INVALID_VALUE_OUT_OF_RANGE_INTEGER 64
#define ID_PARAMETER_INVALID_BUFFER 65

#define ID_MI_CREATECLASS_FAILED 66

#define ID_PARAMETER_UNEXPECTED_RESULTCLASSCOUNT 67
#define ID_PARAMETER_UNEXPECTED_RESULTINSTANCECOUNT 68

#define ID_INVALID_EMBEDDEDPROPERTYVALUE_WRONG_TYPE 69

#define ID_INITIALIZER_OUT_OF_RANGE_DATETIMEVALUE 70

#endif
