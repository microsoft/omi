/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

enum
{
    WSMANTAG_HEADER = 1,
    WSMANTAG_TO = 2,
    WSMANTAG_RESOURCE_URI = 3,
    WSMANTAG_REPLY_TO = 4,
    WSMANTAG_ACTION = 5,
    WSMANTAG_SELECTOR_SET = 6,
    WSMANTAG_MESSAGE_ID = 7,
    WSMANTAG_ADDRESS = 8,
    WSMANTAG_SELECTOR = 9,
    WSMANTAG_MAX_ENVELOPE_SIZE = 10,
    WSMANTAG_ENUM_ENUMERATE = 11,
    WSMANTAG_ENUM_MAX_ELEMENTS = 12,
    WSMANTAG_ENUM_OPTIMIZE_ENUMERATION = 13,
    WSMANTAG_ENUM_POLYMORPHISM_MODE = 14,
    WSMANTAG_ENUM_POLYMORPHISM_MODE_NONE = 15,
    WSMANTAG_ENUM_POLYMORPHISM_MODE_EXCLUDE_PROPS = 16,
    WSMANTAG_ENUM_POLYMORPHISM_MODE_INCLUDE_PROPS = 17,
    WSMANTAG_ENUM_MODE = 18,
    WSMANTAG_ENUM_MODE_OBJECT = 19,
    WSMANTAG_ENUM_MODE_OBJECT_AND_EPR = 20,
    WSMANTAG_ENUM_MODE_EPR = 21,
    WSMANTAG_ENUM_FILTER = 22,
    WSMANTAG_ENUM_DIALIECT = 23,
    WSMANTAG_ENUM_PULL = 24,
    WSMANTAG_PULL_ENUMERATION_CONTEXT = 25,
    WSMANTAG_PULL_MAX_ELEMENTS = 26,
    WSMANTAG_ENUM_RELEASE = 27,
    WSMANTAG_ACTION_ENUMERATE = 28,
    WSMANTAG_ACTION_PULL = 29,
    WSMANTAG_ACTION_RELEASE = 30,
    WSMANTAG_ACTION_GET = 31,
    WSMANTAG_ACTION_PUT = 32,
    WSMANTAG_ACTION_DELETE = 33,
    WSMANTAG_ACTION_CREATE = 34,
    TAG46 = 35,
    WSMANTAG_IDENTIFY = 36
};

#if !defined(HASHSTR_CHAR)
# define HASHSTR_CHAR char
#endif

#if !defined(HASHSTR_T)
# define HASHSTR_T(STR) STR
#endif

#if !defined(HASHSTR_STRCMP)
# define HASHSTR_STRCMP strcmp
#endif

int HashStr(const HASHSTR_CHAR* s, size_t n);

