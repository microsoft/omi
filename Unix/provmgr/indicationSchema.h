/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _indicationSchema_h
#define _indicationSchema_h

#include <MI.h>

/*
 * ==============================================================================
 * 
 *     Instructions for generating Lifecycle Indication Classes:
 *
 * ==============================================================================
 *
 * 1. Build entire code base to generate `omigen`
 * 2. In your home directory, create a dummy mof file:
 *     a. Contents:
 *         class Dummy_A {};
 *     b. Save as dummy.mof
 * 3. Generate the files:
 *     a. <OMI bin dir>/omigen ./dummy.mof Dummy_A -n -e CIM_InstCreation CIM_InstDeletion CIM_InstMethodCall CIM_InstModification CIM_InstRead
 *     b. Note: This will automatically generate CIM_Indication and CIM_InstIndication
 * 4. Remove references to Dummy_A from schema.c
 * 5. Rename schema.c to indicationSchema.c
 * 6. Update the RTTI externs in indicationSchema.h if CIM_Inst* classes were added or removed.
 *
 * ==============================================================================
 */

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Indication_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstIndication_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstCreation_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstDeletion_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstMethodCall_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstModification_rtti;
MI_EXTERN_C MI_CONST MI_ClassDecl CIM_InstRead_rtti;

#endif /* _indicationSchema_h */

