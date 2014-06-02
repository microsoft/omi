
/**************************************************************
 * INTRODUCTION
 *
 * strings.def file defines strings that need to be localized.
 *
 * strings.def is used in 2 contexts:
 * 1. when consuming files from C code:
 *      - strings.def is included from strings.h
 *      - the above exposes inline functions like 
 *        Intlstr_SimpleString(), Intlstr_ReorderablePlaceholders(int,int), etc.
 *      - the functions are invoked from main.c
 * 2. when packaging strings for distribution with the product
 *      2a. on Windows, strings.def is included from main.rc
 *      2b. on Linux, currently we dont do anything, but we tested manually that xgettext works fine
 *
 * Below are example definitions of localizable strings.
 */



/**************************************************************
 * EXAMPLE 1 - BASICS
 *
 * Simplest possible example.
 * Arguments of Intlstr_Define macro: numeric id, C identifier, English string 
 */

Intlstr_Define0(1010, SimpleString, "My simple string")



/**************************************************************
 * EXAMPLE 2 - RESOURCE COMMENTING
 *
 * Example of resource commenting [useful to avoid overlocalization in ps-PS builds]
 * For more information see http://localizability/contents/cmt/101/what.asp 
   
 * To verify if the comments were parsed correctly, one can open LCG files in LcxAdmin tool like this:
 * lcxadmin <Path to LCG file>
 * (answer "no" when asked whether to open an extra lci/comments file)
 */

/* {StrContains="Get-Command"} */
Intlstr_Define0(1020, ResourceCommentingExample1, "Cmdlet or API names (like Get-Command) should not be localized")



/**************************************************************
 * EXAMPLE 3 - PLACEHOLDERS
 *
 * Example of how to correctly use format placeholders in localizable strings;
 *
 * Note that not all placeholders are supported (i.e. FormatString on Windows doesnt support %f and/or %g) - the supported/verified ones are:
 * Intlstr_d (int formatted as a decimal number), Intlstr_x (int formatted as hex), Intlstr_p (pointer formatted as hex), Intlstr_tstr (PAL_Char* string)
 * See pal/format.placeholders.h for more details or to add more placeholder kinds.
 *
 * For rationale for enabling reordering of placeholders see http://www.gnu.org/software/gettext/manual/html_node/c_002dformat-Flag.html 
*/

Intlstr_Define2(
    1040, 
    ReorderablePlaceholders, 
    int, firstInteger, 
    int, secondInteger,
    "Second integer = " Intlstr_d(2) ",  First integer = " Intlstr_d(1)
) 



/**************************************************************
 * EXAMPLE 4 - PAL_Char* PLACEHOLDERS
 *
 * Example of use format placeholders for PAL_Char* arguments 
 */
Intlstr_Define2(
    1050, 
    StringPlaceholders, 
    _In_z_ const PAL_Char*, firstString, 
    _In_z_ const PAL_Char*, secondString,
    "Second string = " Intlstr_tstr(2) ",  First string = " Intlstr_tstr(1)
) 


