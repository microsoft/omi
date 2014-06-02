
/* This is just a test file consumed by test_pal.cpp.
   For sample code that uses pal/intlstr* please see ./tests/pal_intlstr_sample directory */

Intlstr_Define0(1010, TestPal_SimpleString, "My simple string") /* {Locked} */

Intlstr_Define2(
    1020, 
    TestPal_ReorderablePlaceholders, 
    int, firstInteger, 
    int, secondInteger,
    "Second integer = " Intlstr_d(2) ",  First integer = " Intlstr_d(1)
) /* {Locked} */ 

Intlstr_Define1(
    2010, 
    TestPal_OnePlaceholder, 
    int, p1, 
    "p1=" Intlstr_d(1) 
) /* {Locked} */ 

Intlstr_Define2(
    2020, 
    TestPal_TwoPlaceholders, 
    int, p1, 
    int, p2,
    "p1=" Intlstr_d(1) ", p2=" Intlstr_d(2)
) /* {Locked} */ 

Intlstr_Define3(
    2030, 
    TestPal_ThreePlaceholders, 
    int, p1, 
    int, p2,
    int, p3, 
    "p1=" Intlstr_d(1) ", p2=" Intlstr_d(2) ", p3=" Intlstr_d(3)
) /* {Locked} */ 

Intlstr_Define1(
    3010, 
    TestPal_Specifier_d, 
    int, p1, 
    "p1=" Intlstr_d(1) 
) /* {Locked} */ 

Intlstr_Define1(
    3020, 
    TestPal_Specifier_tstr, 
    _In_z_ const PAL_Char*, p1, 
    "p1=" Intlstr_tstr(1) 
) /* {Locked} */ 

Intlstr_Define1(
    3022, 
    TestPal_Specifier_tchr, 
    PAL_Char, c, 
    "char=" Intlstr_tchr(1) 
) /* {Locked} */ 

Intlstr_Define1(
    3030, 
    TestPal_Specifier_x, 
    int, p1, 
    "p1=0x" Intlstr_x(1) 
) /* {Locked} */ 

