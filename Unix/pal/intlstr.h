/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* ifndef guards are limited in their scope on purpose (to allow including this again with different INTLSTR_DOMAIN) */
#ifndef _intlstr_h_
#define _intlstr_h_

#include <pal/palcommon.h>

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** Intlstr - datatype for representing localized strings
**
**==============================================================================
*/

typedef struct _Intlstr
{
/* "public" fields */
    _Null_terminated_
    const PAL_Char* str; /* localized string */

/* "private" fields */
    PAL_Boolean _formattedString; 
} Intlstr;

#define Intlstr_Null {NULL, 0}

/*
**==============================================================================
**
** Intlstr_Free function
**
**==============================================================================
*/

PAL_INLINE void _Intlstr_FreeFormattedString(_Frees_ptr_opt_ PAL_Char* localizedString);

PAL_INLINE void Intlstr_Free(Intlstr localizedString)
{
    if (localizedString._formattedString)
    {
        _Intlstr_FreeFormattedString((PAL_Char*)localizedString.str);
    }
}

/*
**==============================================================================
**
** Internal helper functions
**
**==============================================================================
*/

PAL_INLINE Intlstr _Intlstr_ReturnFixedString(const _In_opt_z_ PAL_Char* str)
{
    Intlstr result; 
    result.str = str; 
    result._formattedString = PAL_FALSE; 
    return result; 
}

PAL_INLINE Intlstr _Intlstr_ReturnFormattedString(const _In_opt_z_ PAL_Char* str)
{
    Intlstr result; 
    result.str = str; 
    result._formattedString = PAL_TRUE; 
    return result; 
}

#if defined(_MSC_VER)

    #include <windows.h> /* needed for LocalFree */

    _Ret_z_
    _Success_(return != NULL)
    const PAL_Char* _Intlstr_GetString_LoadString(HINSTANCE hInstance, UINT uID);

    _Ret_z_
    _Success_(return != NULL)
    PAL_Char* _Intlstr_FormatString_FormatMessage(HINSTANCE hInstance, UINT uID, ...);

    PAL_INLINE void _Intlstr_FreeFormattedString(_Frees_ptr_opt_ PAL_Char* localizedString)
    {
        /* LocalFree is marked as "obsolete" by "findapi" tool, but as explained in more details
           in bug WinBlue #355130 it is ok to use LocalFree until FormatMessage is fixed */
        LocalFree(localizedString);
    }

#elif defined(CONFIG_ENABLE_GETTEXT)

    _Ret_z_ \
    _Check_return_ \
    _Success_(return != NULL) \
    const PAL_Char* _Intlstr_GetString_GetText(const char* domain_name, int id, const char* msgid);

    _Ret_z_
    _Success_(return != NULL)
    PAL_Char* _Intlstr_FormatString_gettext_and_snprintf(const char* domain_name, int id, const char* msgid, ...);

    PAL_INLINE void _Intlstr_FreeFormattedString(_Frees_ptr_opt_ PAL_Char* localizedString)
    {
        PAL_Free(localizedString); 
    }

#else

    #include <pal/format.h>

    PAL_INLINE void _Intlstr_FreeFormattedString(_Frees_ptr_opt_ PAL_Char* localizedString)
    {
        PAL_Free(localizedString); 
    }

#endif

PAL_END_EXTERNC

#endif /* !defined(_intlstr_h_) */

/*
**==============================================================================
**
** Translating user-provided INTLSTR_DOMAIN into OS-specific _INTLSTR_DOMAIN
**
**==============================================================================
*/

#if defined (_INTLSTR_DOMAIN)
    #undef _INTLSTR_DOMAIN
#endif

#if defined(INTLSTR_DOMAIN)

    #if defined(_MSC_VER)

        #define _INTLSTR_DOMAIN (GetModuleHandleA(INTLSTR_DOMAIN))

    #else
    
        #define _INTLSTR_DOMAIN (INTLSTR_DOMAIN)
    
    #endif

#else

    #if defined(_MSC_VER)

        #define _INTLSTR_DOMAIN (GetModuleHandle(NULL))

    #else
    
        #define _INTLSTR_DOMAIN ("omi")
    
    #endif

#endif

/*
**==============================================================================
**
** Intlstr_Define0 macro for translating user-provided localized string definitions into OS-specific
** Intlstr_<stringname> helper functions (written on top of _Intlstr_GetString_Xxx)
**
**==============================================================================
*/

#if defined(_MSC_VER)

    #define Intlstr_Define0(id, name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name() \
        { \
            return _Intlstr_ReturnFixedString(_Intlstr_GetString_LoadString(_INTLSTR_DOMAIN, id)); \
        } 

#elif defined(CONFIG_ENABLE_GETTEXT)

    #define Intlstr_Define0(id, name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name() \
        { \
            return _Intlstr_ReturnFixedString(_Intlstr_GetString_GetText(_INTLSTR_DOMAIN, id, text)); \
        } 

#else

    #define Intlstr_Define0(id, name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name() \
        { \
            return _Intlstr_ReturnFixedString(PAL_T(text)); \
        } 

#endif


/*
**==============================================================================
**
** Intlstr_Define1/2/3 macros for translating user-provided localized string templates
** into OS-specific Intlstr_<stringname> helper functions
**
**==============================================================================
*/

#if defined(_MSC_VER)

    #define Intlstr_Define1(id, name, parameter1_type, parameter1_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_FormatMessage(_INTLSTR_DOMAIN, id, parameter1_name)); \
        } 

    #define Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_FormatMessage(_INTLSTR_DOMAIN, id, parameter1_name, parameter2_name)); \
        } 

    #define Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_FormatMessage(_INTLSTR_DOMAIN, id, parameter1_name, parameter2_name, parameter3_name)); \
        } 

#elif defined(CONFIG_ENABLE_GETTEXT)

    #define Intlstr_Define1(id, name, parameter1_type, parameter1_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_gettext_and_snprintf(_INTLSTR_DOMAIN, id, text, parameter1_name)); \
        }

    #define Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_gettext_and_snprintf(_INTLSTR_DOMAIN, id, text, parameter1_name, parameter2_name)); \
        }

    #define Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name) \
        { \
            return _Intlstr_ReturnFormattedString(_Intlstr_FormatString_gettext_and_snprintf(_INTLSTR_DOMAIN, id, text, parameter1_name, parameter2_name, parameter3_name)); \
        }

#else

    #define Intlstr_Define1(id, name, parameter1_type, parameter1_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name) \
        { \
            return _Intlstr_ReturnFormattedString(Stprintf_StrDup(PAL_T(text), parameter1_name)); \
        }

    #define Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name) \
        { \
            return _Intlstr_ReturnFormattedString(Stprintf_StrDup(PAL_T(text), parameter1_name, parameter2_name)); \
        }

    #define Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) \
        _Check_return_ \
        _Success_(return.str != NULL) \
        PAL_INLINE Intlstr Intlstr_ ## name(parameter1_type parameter1_name, parameter2_type parameter2_name, parameter3_type parameter3_name) \
        { \
            return _Intlstr_ReturnFormattedString(Stprintf_StrDup(PAL_T(text), parameter1_name, parameter2_name, parameter3_name)); \
        }

#endif


