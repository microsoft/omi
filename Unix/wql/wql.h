/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _wql_wql_h
#define _wql_wql_h

#include <common.h>
#include <stddef.h>
#include <base/batch.h>
#include <base/buf.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WQL_MAX_PROPERTIES 128
#define WQL_MAX_SYMBOLS 128

/* Type of symbol appearing in the WHERE clause */
typedef enum _WQL_Type
{
    WQL_TYPE_OR,
    WQL_TYPE_AND,
    WQL_TYPE_NOT,
    WQL_TYPE_EQ,
    WQL_TYPE_NE,
    WQL_TYPE_LT,
    WQL_TYPE_LE,
    WQL_TYPE_GT,
    WQL_TYPE_GE,
    WQL_TYPE_LIKE,
    WQL_TYPE_ISA,
    WQL_TYPE_IDENTIFIER,
    WQL_TYPE_BOOLEAN,
    WQL_TYPE_INTEGER,
    WQL_TYPE_REAL,
    WQL_TYPE_STRING,
    WQL_TYPE_NULL,
    WQL_TYPE_ANY
}
WQL_Type;

/* Value of symbol (if any) appearing in the WHERE clause. We avoid the use
 * of unions here to permit static structure initialization (unions only 
 * support initialization of the first field).
 */
typedef struct _WQL_Value
{
    unsigned char boolean;
    long long integer;
    double real;
    /* property name or literal string */
    ZChar* string;
    /* Example: SourceInstance.CIM_StorageVolume::OperationStatus */
    ZChar* embeddedClassName;
    /* Example: SourceInstance.OperationStatus */
    ZChar* embeddedPropertyName;
}
WQL_Value;

#define WQL_VALUE_BOOLEAN(X) { X, 0, 0, NULL, NULL, NULL }
#define WQL_VALUE_INTEGER(X) { 0, X, 0, NULL , NULL, NULL}
#define WQL_VALUE_REAL(X) { 0, 0, X, NULL , NULL, NULL}
#define WQL_VALUE_STRING(X) { 0, 0, 0, X , NULL, NULL}

/* Represents an operand or operator appearing in the WHERE clause */
typedef struct _WQL_Symbol
{
    WQL_Type type;
    WQL_Value value;
}
WQL_Symbol;

/* This parser supports WQL and CQL dialects */
typedef enum _WQL_Dialect
{
    WQL_DIALECT_WQL,
    WQL_DIALECT_CQL
}
WQL_Dialect;

/* Output structure from WQL parser */
typedef struct _WQL
{
    /* Properties given by SELECT list */
    const ZChar* properties[WQL_MAX_PROPERTIES];
    size_t nproperties;

    /* Class name given by FROM clause */
    const ZChar* className;

    /* Condition symbols given by WHERE class (in postfix order) */
    WQL_Symbol symbols[WQL_MAX_SYMBOLS];
    size_t nsymbols;

    /* Allocate blocks from this batch (if provided) */
    Batch* batch;

    /* Whether batch object should be deleted in WQL_Delete() */
    int deleteBatch;

    /* The query text */
    ZChar* text;

    /* Dialect being parsed: WQL or CQL */
    WQL_Dialect dialect;
}
WQL;

WQL* WQL_Parse(
    const ZChar* text, 
    Batch* batch, 
    WQL_Dialect dialect);

WQL* WQL_Clone(const WQL* self, Batch* batch);

void WQL_Delete(WQL* self);

/* Generate a static C definition of this WQL structure */
int WQL_Define(const WQL* self, Buf* out, size_t nindent);

/* Dump WQL instance to standard output */
int WQL_Dump(const WQL* self, size_t nindent);

/* Return non-zero if the two WQL instances are identical */
int WQL_Identical(const WQL* x, const WQL* y);

/* Signature of Lookup() function called by WQL_Eval().
 *     name -
 *         The property to be looked up.
 *     embeddedClassName -
 *         If non-null, the class type when 'name' is an embedded instance 
 *         property (uses ISA relationship).
 *     embeddedPropertyName -
 *         If non-null, the name of a property of the embedded instances
 *         given by 'name'.
 *     symbol - 
 *         Holds the result of the lookup operation (usually the value
 *         of the property given by 'name'.
 *     batch -
 *         Batch allocator in case any memory must be allocated.
 *     data -
 *         The data argument passed to Lookup() function.
 *
 * More on these parameters:
 *     name
 *     embeddedClassName
 *     embeddedPropertyName
 *
 * There are 4 conditions involving these parameters to consider:
 *
 *     Case 1: (name && !embeddedClassName && !embeddedPropertyName)
 *         Get the value of the property given by the 'name' parameter.
 *
 *     Case 2: (name && embeddedClassName && !embeddedPropertyName)
 *         Perform an ISA operation where the instance is given by the 'name'
 *         embedded instance property and the classname is given by the
 *         'embeddedClassName' parameter.
 *         WQL Example: SourceInstance ISA CIM_StorageVolume
 *             name=SourceInstance
 *             embeddedClassName=CIM_StorageVolume
 *             embeddedPropertyName=NULL
 *
 *     Case 3: (name && !embeddedClassName && embeddedPropertyName)
 *         Get the value of the property given by the 'embeddedPropertyName'
 *         parameter from the instance given by the 'name' parameter.
 *         WQL Example: SourceInstance.OperationalStatus
 *             name=SourceInstance
 *             embeddedClassName=NULL
 *             embeddedPropertyName=OperationalStatus
 *
 *     Case 4: (name && embeddedClassName && embeddedPropertyName)
 *         Get the value of the property given by the 'embeddedPropertyName'
 *         parameter from the instance given by the 'name' parameter and
 *         require that the the class satisfy the ISA relationship with
 *         the 'embeddedClassName' parameter.
 *         WQL Example: SourceInstance.CIM_StorageVolume.OperationalStatus
 *             name=SourceInstance
 *             embeddedClassName=CIM_StorageVolume
 *             embeddedPropertyName=OperationalStatus
 *
 */
typedef int (*WQL_Lookup)(
    const ZChar* name, 
    const ZChar* embeddedClassName, 
    const ZChar* embeddedPropertyName, 
    WQL_Symbol* symbol, 
    Batch* batch,
    void* data);

/* Evaluate WQL expression, obtaining property values with the lookup()
 * callback function. Return value: 0=match, 1=mismatch, -1=error.
 */
int WQL_Eval(
    const WQL* wql, 
    WQL_Lookup lookup,
    void* data);

/* Lookup function that may be passed to WQL_Eval(). This function looks up
 * property values from an MI_Instance( the data parameter is an MI_Instance).
 */
int WQL_LookupInstanceProperty(
    const ZChar* name, 
    const ZChar* embeddedClassName, 
    const ZChar* embeddedPropertyName, 
    WQL_Symbol* symbol, 
    Batch* batch,
    void* data);

/* Return non-zero if the WQL property list contains the given property */
MI_Boolean WQL_ContainsProperty(
    const WQL* self,
    const ZChar* propertyName);

/* Validate the query against the given class declaration: returns 0 or -1 */
int WQL_Validate(
    const WQL* self, 
    const MI_ClassDecl* cd);

#ifdef __cplusplus
}
#endif

#endif /* _wql_wql_h */
