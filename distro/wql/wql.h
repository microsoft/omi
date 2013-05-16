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
#define WQL_MAX_SYMBOLS 64

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
    WQL_TYPE_IDENTIFIER,
    WQL_TYPE_BOOLEAN,
    WQL_TYPE_INTEGER,
    WQL_TYPE_REAL,
    WQL_TYPE_STRING,
    WQL_TYPE_NULL
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
    MI_Char* string;
}
WQL_Value;

#define WQL_VALUE_BOOLEAN(X) { X, 0, 0, NULL }
#define WQL_VALUE_INTEGER(X) { 0, X, 0, NULL }
#define WQL_VALUE_REAL(X) { 0, 0, X, NULL }
#define WQL_VALUE_STRING(X) { 0, 0, 0, X }

/* Represents an operand or operator appearing in the WHERE clause */
typedef struct _WQL_Symbol
{
    WQL_Type type;
    WQL_Value value;
}
WQL_Symbol;

/* Output structure from WQL parser */
typedef struct _WQL
{
    /* Properties given by SELECT list */
    const MI_Char* properties[WQL_MAX_PROPERTIES];
    size_t nproperties;

    /* Class name given by FROM clause */
    const MI_Char* className;

    /* Condition symbols given by WHERE class (in postfix order) */
    WQL_Symbol symbols[WQL_MAX_SYMBOLS];
    size_t nsymbols;

    /* Allocate blocks from this batch (if provided) */
    Batch* batch;

    /* Whether batch object should be deleted in WQL_Delete() */
    int deleteBatch;

    /* The query text */
    MI_Char* text;
}
WQL;

WQL* WQL_Parse(const MI_Char* text, Batch* batch);

WQL* WQL_Clone(const WQL* self, Batch* batch);

void WQL_Delete(WQL* self);

/* Generate a static C definition of this WQL structure */
int WQL_Define(const WQL* self, Buf* out, size_t nindent);

/* Dump WQL instance to standard output */
int WQL_Dump(const WQL* self, size_t nindent);

/* Return non-zero if the two WQL instances are identical */
int WQL_Identical(const WQL* x, const WQL* y);

/* Lookup function passed to WQL_Eval() */
typedef int (*WQL_Lookup)(
    const MI_Char* name, 
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
    const MI_Char* name_, 
    WQL_Symbol* symbol, 
    Batch* batch,
    void* data);

/* Return non-zero if the WQL property list contains the given property */
MI_Boolean WQL_ContainsProperty(
    const WQL* self,
    const MI_Char* propertyName);

/* Validate the query against the given class declaration */
int WQL_Validate(
    const WQL* self, 
    const MI_ClassDecl* cd);

#ifdef __cplusplus
}
#endif

#endif /* _wql_wql_h */
