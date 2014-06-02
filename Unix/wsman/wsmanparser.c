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

#include <assert.h>
#include <ctype.h>
#include "wsmanparser.h"
#include "wsbuf.h"
#include <base/log.h>
#include <base/result.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <indication/common/indicommon.h>
#include <base/helpers.h>

#if defined(CONFIG_ENABLE_WCHAR)
# define HASHSTR_CHAR TChar
# define HASHSTR_T(STR) L##STR
# define HASHSTR_STRCMP wcscmp
#endif

#include "wstags.h"

#if defined(CONFIG_FAVORSIZE)
# include "wstags_small.inc"
#else
# include "wstags_quick.inc"
#endif

#include <wsman/uri.h>

//#if 0
#define ENABLE_TRACING
//#endif

#define TRACE_RETURN

#if defined(TRACE_RETURN)
# define RETURN(X) \
    do \
    { \
        trace_WsmanReturn( __FILE__, __LINE__ ); \
        return X; \
    } \
    while (0)
#else
# define RETURN(X) return X
#endif

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/
static int _GetInstance(
    XML* xml, 
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);

static int _GetReference(
    XML* xml, 
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams);

/****************************************************************************************/
/* soap processing */

static int _MustUnderstandCanBeIgnored(
    const XML_Elem* e)
{
    size_t i;
    for (i = 0; i < e->attrsSize; i++)
    {
        if (e->attrs[i].name.namespaceId == MI_T('s') &&
            Tcscmp(e->attrs[i].name.data, PAL_T("mustUnderstand")) == 0 &&
            Tcscmp(e->attrs[i].value, PAL_T("true")) == 0)
        {
            RETURN(-1);
        }
    }
    return 0;
}

static MI_Boolean IsValidClassname(const TChar* classname)
{
    const TChar* p = classname;

    if (!isalpha((unsigned int)(*p)) && *p != '_')
        return MI_FALSE;

    p++;

    for (; *p; p++)
    {
        if (!isalnum((unsigned int)(*p)) && *p != '_')
            return MI_FALSE;
    }

    return MI_TRUE;
}

static int _ParseBooleanOption(_In_ XML_Elem *e, _Inout_ MI_Boolean *ptrToOption)
{
    if(Tcscasecmp(e->data.data, PAL_T("true")) == 0)
    {
        *ptrToOption = 1;
    }
    else if(Tcscasecmp(e->data.data, PAL_T("false")) == 0)
    {
        *ptrToOption = 0;
    }
    else
        RETURN(-1);

    return 0;
}

static int _GetOption(
    _In_ XML* xml,
    _In_ XML_Elem *e,
    _Inout_ WSMAN_WSHeader* wsheader)
{
    size_t i;

    for (i = 0; i < e->attrsSize; i++)
    {
        /* To support GetClass */
        if ((e->attrs[i].name.namespaceId == 0) && 
            Tcscmp(e->attrs[i].name.data, PAL_T("Name")) == 0)
        {
            int valueHash = 0;
            
            if (XML_Expect(xml, e, XML_CHARS, 0, NULL) != 0)
                RETURN(-1);

            valueHash = HashStr(0, e->attrs[i].value, e->attrs[i].valueSize);

            // the WSMAN_OPTION_WMI_* is to check for these options included as custom options
            if((valueHash == WSMAN_OPTION_INCLUDE_INHERITANCE_HIERARCHY) ||
                (valueHash == WSMAN_OPTION_WMI_INCLUDE_INHERITANCE_HIERARCHY))
            {
                if(_ParseBooleanOption(e, &(wsheader->includeInheritanceHierarchy)) != 0)
                    RETURN(-1);
            }
            else if((valueHash == WSMAN_OPTION_INCLUDE_INHERITED_ELEMENTS) || 
                    (valueHash == WSMAN_OPTION_WMI_INCLUDE_INHERITED_ELEMENTS))
            {
                if(_ParseBooleanOption(e, &(wsheader->includeInheritedElements)) != 0)
                    RETURN(-1);
            }
            else if((valueHash == WSMAN_OPTION_INCLUDE_QUALIFIERS) || 
                    (valueHash == WSMAN_OPTION_WMI_INCLUDE_QUALIFIERS))
            {
                if(_ParseBooleanOption(e, &(wsheader->includeQualifiers)) != 0)
                    RETURN(-1);
            }
            else if((valueHash == WSMAN_OPTION_INCLUDE_CLASS_ORIGIN) || 
                    (valueHash == WSMAN_OPTION_WMI_INCLUDE_CLASS_ORIGIN))
            {
                if(_ParseBooleanOption(e, &(wsheader->includeClassOrigin)) != 0)
                    RETURN(-1);
            }
            else if(valueHash == WSMAN_OPTION_MSFTWINRM_USE_PRECISE_ARRAYS)
            {
                if(_ParseBooleanOption(e, &(wsheader->usePreciseArrays)) != 0)
                    RETURN(-1);
            }
        }
        else
            continue;

        if (XML_Expect(xml, e, XML_END, PAL_T('w'), PAL_T("Option")) != 0)
            RETURN(-1);

        break;
    }

    return 0;
}

static int _GetOptionSet(
    XML* xml,
    WSMAN_WSHeader* wsheader)
{
    XML_Elem e;

    if (XML_Expect(xml, &e, XML_START, PAL_T('w'), PAL_T("Option")) != 0)
        RETURN(-1);

    /* iterate through all option tags */
    for (;;)
    {
        if (0 != _GetOption(
            xml,
            &e,
            wsheader))
            RETURN(-1);

        /**/
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (XML_END == e.type)
            break;
    }

    return 0;
}

static int _GetSelector(
    _In_ XML* xml,
    _In_ XML_Elem *e,
    _Inout_ const TChar** ns,
    _Inout_ const TChar** classname,
    _Inout_ MI_Instance** instance,
    _Inout_ Batch** batch)
{
    size_t i;

    /* expecting namespace or key */
    for (i = 0; i < e->attrsSize; i++)
    {
        /* To support GetClass */
        if((e->attrs[i].name.namespaceId == 0) && 
           (Tcscmp(e->attrs[i].name.data, PAL_T("Name")) == 0))
        {
            if (Tcscmp(e->attrs[i].value, PAL_T("ClassName")) == 0)
            {
                if (XML_Expect(xml, e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (!IsValidClassname(e->data.data))
                    RETURN(-1);
                *classname = e->data.data;
            }
            else if(Tcscmp(e->attrs[i].value, PAL_T("__cimnamespace")) == 0)
            {
                /* namespace */
                if (XML_Expect(xml, e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                *ns = e->data.data;
            }
            else
            {
                /* keys */
                const TChar* propName = e->attrs[i].value;

                MI_Boolean selectorIsReference = MI_FALSE;

                if (XML_Next(xml, e) != 0)
                {
                    XML_Raise(xml, WSMAN_ERROR_BAD_SELECTOR);
                    RETURN(-1);
                }

                if((e->type == XML_START) &&
                   (e->data.namespaceId == MI_T('a')) &&
                   (Tcscmp(PAL_T("EndpointReference"), e->data.data) == 0))
                {
                    if (XML_Next(xml, e) != 0)
                    {
                        XML_Raise(xml, WSMAN_ERROR_BAD_EPR_IN_SELECTOR);
                        RETURN(-1);
                    }       

                    selectorIsReference = MI_TRUE;
                }
                else if(e->type != XML_CHARS) 
                {
                    XML_Raise(xml, WSMAN_ERROR_BAD_SELECTOR);
                    RETURN(-1);
                }                        

                /* allocate batch and instance if needed */
                if (!(*instance))
                {
                    MI_Result r;
                    TChar* cn;

                    /* verify that we already received classname */
                    if (!(*classname))
                    {
                        XML_Raise(
                            xml, 
                            WSMAN_ERROR_NO_CLASS_NAME_IN_SELECTOR);
                        RETURN(-1);
                    }

                    /* Destroy old batch if it exists (from previous operation) */
                    if (*batch)
                    {
                        Batch_Destroy(*batch);
                    }

                    *batch = Batch_New(BATCH_MAX_PAGES);

                    if (!(*batch))
                        RETURN(-1);

                    cn = Batch_Tcsdup(*batch, *classname);
                    if (!cn)
                        RETURN(-1);

                    r = Instance_NewDynamic(instance, cn, MI_FLAG_CLASS, *batch);

                    if (MI_RESULT_OK != r)
                        RETURN(-1);
                }

                /* add next property to the instance */
                {
                    const TChar* wpropName;
                    MI_Result r;
                    MI_Value value;

                    if (!(*batch))
                    {
                        *batch = Batch_New(BATCH_MAX_PAGES);

                        if (!(*batch))
                            RETURN(-1);
                    }

                    wpropName = Batch_Tcsdup(*batch, propName);
                    if (!wpropName)
                        RETURN(-1);

                    if(selectorIsReference)
                    {
                        value.instance = 0;
                        if (0 != _GetReference(xml, e, *batch, &(value.instance)))
                            RETURN(-1);                
                    }
                    else
                    {
                        value.string = Batch_Tcsdup(*batch, e->data.data);
                        if (!value.string)
                            RETURN(-1);
                    }

                    // Set the property.
                    r = MI_Instance_AddElement(*instance, wpropName, &value, 
                        (selectorIsReference ? MI_REFERENCE : MI_STRING), MI_FLAG_BORROW | MI_FLAG_KEY);

                    if (MI_RESULT_OK != r)
                        RETURN(-1);
                }
            }
        }
        else
            continue;

        if (XML_Expect(xml, e, XML_END, PAL_T('w'), PAL_T("Selector")) != 0)
            RETURN(-1);

        break;
    }

    return 0;
}

static int _GetSelectorSet(
    XML* xml,
    WSMAN_WSHeader* wsheader)
{
    XML_Elem e;

    if (XML_Expect(xml, &e, XML_START, PAL_T('w'), PAL_T("Selector")) != 0)
        RETURN(-1);

    /* iterate through all selector tags */
    for (;;)
    {
        if (0 != _GetSelector(
            xml, 
            &e, 
            &wsheader->rqtNamespace,
            &wsheader->rqtClassname,
            &wsheader->instance,
            &wsheader->instanceBatch))
            RETURN(-1);

        /**/
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (XML_END == e.type)
            break;

    }

    return 0;
}

static int _GetReferenceParameters(
    _In_ XML* xml, 
    _In_ Batch*  dynamicBatch,
    _Inout_ MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    const TChar* classname = NULL;
    const TChar* nameSpace = NULL;

    /* extract ResourceURI and SelectorSet */
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_CHARS)
        {
            continue;
        }

        if (XML_END == e.type)
            break;

        if (PAL_T('w') == e.data.namespaceId &&
            0 == Tcscmp(PAL_T("ResourceURI"), e.data.data))
        {
            if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                RETURN(-1);
            if (XML_StripWhitespace(&e) != 0)
                RETURN(-1);
            classname = Tcsrchr(e.data.data, '/');

            /* skip '/' */
            if (classname)
                classname++;

            if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("ResourceURI")) != 0)
                RETURN(-1);

            continue;
        }

        if (PAL_T('w') == e.data.namespaceId &&
            0 == Tcscmp(PAL_T("SelectorSet"), e.data.data))
        {
            /* Allocate an instance */
            if (!*dynamicInstanceParams)
            {
                MI_Result r;
                const TChar* cn;

                if (!classname)
                {
                    XML_Raise(xml, WSMAN_ERROR_NO_RESOURCE_URI);
                    RETURN(-1);
                }

                cn = Batch_Tcsdup(dynamicBatch, classname);
                if (!cn)
                {
                    XML_Raise(xml, WSMAN_ERROR_OUTOFMEMORY);
                    RETURN(-1);
                }

                r = Instance_NewDynamic(dynamicInstanceParams, cn, MI_FLAG_CLASS, dynamicBatch);
                if (MI_RESULT_OK != r)
                    RETURN(-1);
            }

            /* iterate through all selector tags */
            for (;;)
            {
                const TChar* ns = NULL;
                const TChar* cn = NULL;

                if (_GetSelector(
                    xml, 
                    &e, 
                    &ns, 
                    &cn, 
                    dynamicInstanceParams, 
                    &dynamicBatch) != 0)
                {
                    RETURN(-1);
                }

                if (ns)
                {
                    nameSpace = ns;
                }

                /**/
                if (XML_Next(xml, &e) != 0)
                    RETURN(-1);

                if (e.type == XML_CHARS)
                {
                    if (XML_Next(xml, &e) != 0)
                        RETURN(-1);
                }
                if (XML_END == e.type)
                    break;

            }
            continue;
        }
    }

    if (nameSpace)
        (*dynamicInstanceParams)->nameSpace = nameSpace;

    return 0;
}

static int _GetReference(
    XML* xml, 
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;

    e = *start;

    /* extract all parameters */
    for (;;)
    {
        if (e.data.namespaceId != MI_T('a') ||
            0 != Tcscmp(PAL_T("ReferenceParameters"), e.data.data))
        {
            if (XML_Skip(xml) != 0)
                RETURN(-1);

            if (XML_Next(xml, &e) != 0)
                RETURN(-1);
            if (e.type == XML_CHARS)
            {
                if (XML_Next(xml, &e) != 0)
                    RETURN(-1);
                continue;
            }
            if (e.type == XML_END)
                break;

            continue;
        }

        if (0 != _GetReferenceParameters(xml, dynamicBatch, dynamicInstanceParams))
            RETURN(-1);

        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_CHARS)
        {
            if (XML_Next(xml, &e) != 0)
                RETURN(-1);
        }
        if (e.type == XML_END)
            break;
    }

    return 0;
}

/*
**==============================================================================
**
** _GetSingleProperty()
**
**     This function gets a instance property. The caller has already counsumed
**     the start property element. This function reads the value and the 
**     closing property element.
**
**==============================================================================
*/

static int _GetSingleProperty(
    XML* xml,
    XML_Elem* start,
    Batch*  dynamicBatch,
    MI_Char nsId,
    const TChar* propNameChar,
    MI_Value* value,
    MI_Type* type,
    MI_Boolean* null)
{
    XML_Elem e;

    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    while(1)
    {
        if (e.type == XML_END)
        {
            if (nsId != e.data.namespaceId || 
                Tcscmp(propNameChar, e.data.data) != 0)
            {
                trace_OpenCloseMismatch(tcs(propNameChar), tcs(e.data.data));
                RETURN(-1);
            }

            /* Check whether this attribute is null or just empty */
            {
                const TChar* p = XML_Elem_GetAttr(&e, PAL_T('x'), PAL_T("nil"));

                if (p && Tcscmp(p, PAL_T("true")) == 0)
                {
                    *null = MI_TRUE;
                }
                else
                {
                    *null = MI_FALSE;
                    *type = MI_STRING;
                    value->string = PAL_T("");
                }
            }

            return 0;
        }
        else if (e.type == XML_CHARS)
        {
            XML_Elem tmpElem;

            /* Check to make sure there isn't a start element next */
            if (XML_Next(xml, &tmpElem) != 0)
            {
                RETURN(-1);
            }
            if (tmpElem.type == XML_START)
            {
                /* This means we have text and a child element. Use the child element for now */
                e = tmpElem;
                continue;
            }
            if (XML_PutBack(xml, &tmpElem) != 0)
            {
                RETURN(-1);
            }

            /* Plain string property */
            value->string = Batch_Tcsdup(dynamicBatch, e.data.data);
            if (!value->string)
                RETURN(-1);
            *type = MI_STRING;

            if (XML_Expect(xml, &e, XML_END, nsId, propNameChar) != 0)
                RETURN(-1);

            *null = MI_FALSE;
            return 0;
        }
        else if ('a' == e.data.namespaceId)
        {
            /* Reference as </adddress></ReferenceParameters>*/
            value->instance = 0;
            if (0 != _GetReference(xml, &e, dynamicBatch, &value->instance))
                RETURN(-1);

            *type = MI_REFERENCE;
            *null = MI_FALSE;
            return 0;
        }
        else
        {
            if (e.type == XML_START)
            {
                if (Tcscasecmp(e.data.data, PAL_T("CIM_DateTime")) == 0)
                {
                    /* DateTime property XML*/
                    /* <p0:datetimeProperty xsi:type="cim:cimDateTime"> */
                    /*     <CIM_DateTime>19990929195959.000000-420</CIM_DateTime> */
                    /* </p0:datetimeProperty> */
                    if (XML_Next(xml, &e) != 0)
                    RETURN(-1);
                    if (e.type == XML_CHARS)
                    {
                        value->string = Batch_Tcsdup(dynamicBatch, e.data.data);
                        if (!value->string)
                            RETURN(-1);
                        *type = MI_STRING;
                    }
                    else
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, 0, PAL_T("CIM_DateTime")) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, nsId, propNameChar) != 0)
                        RETURN(-1);

                    *null = MI_FALSE;
                    return 0;
                }
            }
            /* Embedded instance */
            value->instance = 0;
            XML_PutBack(xml, &e);

            if (0 != _GetInstance(xml, start, dynamicBatch, &value->instance))
                RETURN(-1);


            *type = MI_INSTANCE;

            *null = MI_FALSE;
            return 0;
        }
    }
}

static int _AddValueToArray(
    Batch*  dynamicBatch,
    MI_Value* valueA,
    MI_Type typeA,
    const MI_Value* value,
    MI_Type type)
{
    /* does type match? */
    if ((type | MI_ARRAY_BIT) != typeA)
        RETURN(-1);

    /* do we need to realloc array? */
    if ((valueA->array.size % 16) == 0)
    {
        void* newData = Batch_Get(dynamicBatch, (valueA->array.size + 16) * sizeof(void*));

        if (!newData)
            RETURN(-1);

        if (valueA->array.size)
            memcpy(newData, valueA->array.data, valueA->array.size * sizeof(void*));

        valueA->array.data = newData;
    }

    if (type == MI_STRING)
        valueA->stringa.data[valueA->stringa.size] = value->string;
    else
        valueA->instancea.data[valueA->instancea.size] = value->instance;

    valueA->array.size++;
    return 0;
}

static int _GetInstance(
    XML* xml, 
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    const TChar* propNameA = 0;
    MI_Value valueA;
    MI_Type typeA = MI_BOOLEAN;
    const TChar* propNamePrev = 0;
    MI_Value valuePrev;
    MI_Type typePrev = MI_BOOLEAN;

    memset(&valueA, 0, sizeof(valueA));

    /* extract all parameters */
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        /* Look for closing instance element */

        if (e.type == XML_END && Tcscmp(e.data.data, start->data.data) == 0)
        {
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        /* allocate new instance if needed */
        if (!*dynamicInstanceParams)
        {
            MI_Result r;
            TChar* cn = NULL;

            // We are trying to parse an Instance, The type of the instance may be specified
            // as a attribute Type or it is same as the element name. We'll attempt to get the
            // type from attribute ... if not we'll use the element name.
            // TODO: At this time we don't have the NS support in the XML parser, so using hardcoded
            // 'xsi:type (good for windows client) once we get the NS support this code should be
            // updated.
            const TChar* typeName = XML_Elem_GetAttr(start, PAL_T('x'), PAL_T("type"));

            if(typeName)
            {
                TChar* typeStart;
                cn = Batch_Tcsdup(dynamicBatch, typeName);

                if (!cn)
                {
                    trace_BatchTcsDup_Failed();
                    RETURN(-1);
                }

                // Trim the _Type from the name.
                typeStart = Tcsrchr(cn, '_');
                if( typeStart )
                {
                    *typeStart = PAL_T('\0');

                    /* trim namespace start too */
                    {
                        TChar* afterColon;
                        afterColon = Tcschr(cn, PAL_T(':'));
                        if (afterColon)
                        {
                            afterColon++;
                            cn = afterColon;
                        }
                    }
                }
                else
                {
                    trace_XsiTypeInvalidValue( cn );
                    RETURN(-1);
                    // cn is allocated on the batch, so it will be release along with it anyway
                }
            }
            else
            {
                cn = Batch_Tcsdup(dynamicBatch, start->data.data);
                if (!cn)
                {
                    trace_BatchTcsDup_Failed();
                    RETURN(-1);
                }
            }

            r = Instance_NewDynamic(
                dynamicInstanceParams, 
                cn, 
                MI_FLAG_CLASS, 
                dynamicBatch);

            if (MI_RESULT_OK != r)
                RETURN(-1);
        }

        /* add next property to the instance */
        if (e.data.size > 0) /* element name should have some data in it */
        {
            MI_Result r;
            MI_Value value;
            MI_Type type = MI_BOOLEAN;
            const TChar* propNameChar;
            const TChar* propName;
            MI_Boolean null;

            propNameChar = e.data.data;

            /* Position propName one beyond ':' character */
            propName = Batch_Tcsdup(dynamicBatch, propNameChar);

            if (!propName)
            {
                trace_BatchTcsDup_Failed();
                RETURN(-1);
            }

            type = MI_BOOLEAN;

            if (_GetSingleProperty(
                xml,
                &e,
                dynamicBatch, 
                e.data.namespaceId,
                propNameChar, 
                &value, 
                &type,
                &null) != 0)
            {
                trace_GetSingleProperty_Failed( tcs(propNameChar) );
                RETURN(-1);
            }

            if (null)
            {
                /* Skip null attributes */
                continue;
            }

            /* Did we collect array's items? */
            if (propNameA)
            {
                /* if we have array and new property matches array - add new item to the array */
                if (0 == Tcscmp(propNameA, propName))
                {
                    if (0 != _AddValueToArray(dynamicBatch, &valueA, typeA, &value, type))
                        RETURN(-1);
                }
                else
                {
                    r = MI_Instance_AddElement(*dynamicInstanceParams, propNameA, &valueA, 
                        typeA, MI_FLAG_BORROW);

                    if (MI_RESULT_OK != r)
                        RETURN(-1);

                    /* Clear array prop name */
                    propNameA = 0;

                    propNamePrev = propName;
                    valuePrev = value;
                    typePrev = type;
                }
            }
            else if (propNamePrev)
            {
                /* Check if name is the same and we need to create an array */
                if (0 == Tcscmp(propNamePrev, propName))
                {
                    /* create array */
                    valueA.array.size = 0;
                    valueA.array.data = 0;

                    typeA = type | MI_ARRAY_BIT;
                    propNameA = propName;

                    if (0 != _AddValueToArray(dynamicBatch, &valueA, typeA, &valuePrev, typePrev))
                        RETURN(-1);

                    if (0 != _AddValueToArray(dynamicBatch, &valueA, typeA, &value, type))
                        RETURN(-1);

                }
                else
                {
                    r = MI_Instance_AddElement(
                        *dynamicInstanceParams, 
                        propNamePrev, 
                        &valuePrev, 
                        typePrev, 
                        MI_FLAG_BORROW);

                    /* Note that the MI_RESULT_ALREADY_EXISTS error is okay
                     * for key properties added when the selector set was
                     * parsed earlier.
                     */
                    if (r != MI_RESULT_OK && r != MI_RESULT_ALREADY_EXISTS)
                    {
                        RETURN(-1);
                    }

                    propNamePrev = propName;
                    valuePrev = value;
                    typePrev = type;
               }

            }
            else
            {
                /* collecting first item */
                propNamePrev = propName;
                valuePrev = value;
                typePrev = type;
            }
        }
    }

    /* if last property was array - add it */
    if (propNameA)
    {
        MI_Result r;

        r = MI_Instance_AddElement(*dynamicInstanceParams, propNameA, &valueA, 
            typeA, MI_FLAG_BORROW);

        if (MI_RESULT_OK != r)
            RETURN(-1);
    }
    else if (propNamePrev)
    {
        MI_Result r;

        r = MI_Instance_AddElement(*dynamicInstanceParams, propNamePrev, &valuePrev, 
            typePrev, MI_FLAG_BORROW);

        /* Note that the MI_RESULT_ALREADY_EXISTS error is okay
        * for key properties added when the selector set was
        * parsed earlier.
        */
        if (r != MI_RESULT_OK && r != MI_RESULT_ALREADY_EXISTS)
        {
            RETURN(-1);
        }
    }

    /* check closing tag */
    if (Tcscmp(e.data.data, start->data.data) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseWSHeader(
    XML* xml,
    WSMAN_WSHeader* wsheader,
    UserAgent userAgent)
{
    XML_Elem e;

    if (wsheader->instanceBatch)
    {
        Batch_Delete(wsheader->instanceBatch);
    }
    memset(wsheader, 0, sizeof(WSMAN_WSHeader));

    // WinRM client assumes that ClassOrigin is true by default on the server
    // by standards, a wsman option is false by default so in non-WinRM case,
    // the includeClassOrigin and all others are set to 0
    wsheader->includeClassOrigin = (userAgent == USERAGENT_WINRM) ? 1 : 0;
    wsheader->includeInheritanceHierarchy = 0;
    wsheader->includeInheritedElements = 0;
    wsheader->includeQualifiers = 0;

    /* Expect <s:Header> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Header")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)// && strcmp(e.data, "s:Header") == 0)
        {
            int tag = HashStr(e.data.namespaceId, e.data.data, e.data.size);

            if (WSMANTAG_HEADER != tag)
            {
                trace_Wsman_UnexpectedCloseTag(tcs(e.data.data));
                RETURN(-1);
            }
            //printf("DONE\n");
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
        {
            case WSMANTAG_TO:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("To")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_RESOURCE_URI:
            {
                int resourceUriHash = 0;
                
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);
                
                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);

                wsheader->schemaRequestType = NOT_A_SCHEMA_REQUEST;

                resourceUriHash = HashStr(0, e.data.data, e.data.size);

                if(resourceUriHash == WSMAN_RESOURCE_URI_CIM_XML_SCHEMA)
                {
                    wsheader->schemaRequestType = CIM_XML_SCHEMA_REQUEST;                
                }
                else if(resourceUriHash == WSMAN_RESOURCE_URI_WS_CIM_SCHEMA)
                {
                    wsheader->schemaRequestType = WS_CIM_SCHEMA_REQEUST;                
                }

                wsheader->rqtClassname = Tcsrchr(e.data.data, '/');
                /* skip '/' */
                if (wsheader->rqtClassname) 
                    wsheader->rqtClassname++;

                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("ResourceURI")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_REPLY_TO:
            {
                while (1)
                {
                    if (XML_Next(xml, &e) != 0)
                        RETURN(-1);
                    /* skip whitespace and comments */
                    if (e.type == XML_START)
                        break;
                }
                if (HashStr(e.data.namespaceId, e.data.data, e.data.size) != WSMANTAG_ADDRESS)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("Address")) != 0)
                    RETURN(-1);

                while (1)
                {
                    if (XML_Next(xml, &e) != 0)
                        RETURN(-1);
                    /* skip whitespace and comments */
                    if (e.type == XML_END)
                        break;
                }
                if (e.type != XML_END && HashStr(e.data.namespaceId, e.data.data, e.data.size) != WSMANTAG_REPLY_TO)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_ACTION:
            {
                wsheader->foundAction = MI_TRUE;

                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);

                wsheader->rqtAction = HashStr(e.data.namespaceId, e.data.data, e.data.size);

                if (0 == wsheader->rqtAction)
                {
                    TChar* s;
                    /* DSP0226; 9: Custom Actions (Methods) just need to have unique URI.
                        We are assuming it has format like http://<server>/wbem/wscim/1/cim-schema/2/<class-name>/<method-name> */

                    if (0 != Tcsncmp(e.data.data, PAL_T("http://"), 7))
                        RETURN(-1);

                    wsheader->rqtServer = e.data.data + 7;

                    s = Tcschr(wsheader->rqtServer, '/');

                    if (!s)
                        RETURN(-1);

                    *s = 0;
                    s++;

                    if (0 != Tcsncmp(s, PAL_T("wbem/wscim/1/cim-schema/2/"), 26))
                        RETURN(-1);

                    s += 26;

                    wsheader->rqtClassname = s;
                    s = Tcschr(s, '/');

                    if (!s)
                        RETURN(-1);

                    *s = 0;
                    s++;
                    wsheader->rqtMethod = s;
                }

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("Action")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_SELECTOR_SET:
            {
                if (_GetSelectorSet(xml, wsheader) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_OPTION_SET:
            {
                if (_GetOptionSet(xml, wsheader) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_MESSAGE_ID:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);
                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);
                wsheader->rqtMessageID = e.data.data;

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("MessageID")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_MAX_ENVELOPE_SIZE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);
                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);

                wsheader->maxEnvelopeSize = (MI_Uint32)Tcstoull(
                    e.data.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("MaxEnvelopeSize")) != 0)
                    RETURN(-1);
            }
            break;

#ifndef DISABLE_INDICATION
            case WSMANTAG_OPERATION_TIMEOUT:
            {
                /* Expect an xs:duration of form: PnYnMnDTnHnMnS */
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);

                if (-1 == ParseWSManDatetime( e.data.data, &wsheader->operationTimeout.value ) )
                    RETURN(-1);
                
                wsheader->operationTimeout.exists = MI_TRUE;

                if (XML_Expect(xml, &e, XML_END, MI_T('w'), MI_T("OperationTimeout")) != 0)
                    RETURN(-1);
            }
            break;
            
            case WSMANTAG_SUBSCRIBE_IDENTIFIER:
            {
                /* For unsubscribe, parse subscribe identifier from header */
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsheader->contextID = (MI_Uint32)Tcstoull(e.data.data, NULL, 10);
                trace_WsmanUnsubscribe( wsheader->contextID );

                if (XML_Expect(xml, &e, XML_END, MI_T('e'), MI_T("Identifier")) != 0)
                    RETURN(-1);
            }
            break;
#endif /* ifndef DISABLE_INDICATION */

            default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    wsheader->unknownMandatoryTag = e.data.data;
                    trace_Wsman_UnknownMandatoryTag(tcs(e.data.data));
                    /* validate header will send correct repsonse to the client */
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }
    /* DMTF standard requires default namespace to be used */
    /* if _cimnamespace selector is not specified as part of request */
    if (!wsheader->rqtNamespace)
        wsheader->rqtNamespace = DEFAULT_CIMNAMESPACE;
    return 0;
}

int WS_ParseSoapEnvelope(XML* xml)
{
    XML_Elem e;

    /* Ignore the processing instruction (if any) */
    {
        if (XML_Next(xml, &e) != 0)
        {
            XML_Raise(xml, XML_ERROR_ELEMENT_EXPECTED);
            RETURN(-1);
        }

        if (e.type != XML_INSTRUCTION)
        {
            if (XML_PutBack(xml, &e) != 0)
                RETURN(-1);
        }
    }

    /* Expect <s:Envelope> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

static const TChar* _ExpectCharsAndEnd(
    XML* xml,
    TChar nsId,
    const TChar* name)
{
    XML_Elem e;
    const TChar* chars;

    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
        return NULL;

    chars = e.data.data;

    if (XML_Expect(xml, &e, XML_END, nsId, name) != 0)
        return NULL;

    return chars;
}

/*
**==============================================================================
**
** _ParseAssociationFilterObject()
**
** Example:
**   <b:Object>
**     <a:Address>
**       http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous
**     </a:Address>
**     <a:ReferenceParameters>
**       <w:ResourceURI>
**         http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/ABC_Widget
**       </w:ResourceURI>
**       <w:SelectorSet>
**         <w:Selector Name="__cimnamespace">
**           root/cimv2
**         </w:Selector>
**         <w:Selector Name="Key">
**           1001
**         </w:Selector>
**       </w:SelectorSet>
**     </a:ReferenceParameters>
**   </b:Object>
*
**==============================================================================
*/

static int _ParseAssociationFilterObject(
    XML* xml, 
    Batch* batch,
    WSMAN_AssociationFilter* filter)
{
    XML_Elem e;

    /* Parse child elements */

    for (;;)
    {
        /* Get next element */

        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        /* Put it back and break out if not a start tag */

        if (e.type != XML_START)
        {
            if (XML_PutBack(xml, &e) != 0)
                RETURN(-1);

            break;
        }

        /* Handle "Object" tag */

        if (PAL_T('a') == e.data.namespaceId && 
            Tcscmp(e.data.data, PAL_T("ReferenceParameters")) == 0)
        {
            if (_GetReferenceParameters(
                xml, 
                batch, 
                &filter->referenceParameters) != 0)
            {
                RETURN(-1);
            }
        }
        else if (PAL_T('a') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("Address")) == 0)
        {
            filter->address = _ExpectCharsAndEnd(xml, PAL_T('a'), PAL_T("Address"));

            if (!filter->address)
                RETURN(-1);
        }
        else
        {
            if (XML_Skip(xml) != 0)
                RETURN(-1);
        }
    }

    /* Expect </Object> */

    if (XML_Expect(xml, &e, XML_END, PAL_T('b'), PAL_T("Object")) != 0)
        RETURN(-1);

    return 0;
}

/*
**==============================================================================
**
** _ParseAssociationFilter()
**
** Example:
**   <b:AssociatedInstances>
**     <b:Object>
**       <a:Address>
**         http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous
**       </a:Address>
**       <a:ReferenceParameters>
**         <w:ResourceURI>
**           http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/ABC_Widget
**         </w:ResourceURI>
**         <w:SelectorSet>
**           <w:Selector Name="__cimnamespace">
**             root/cimv2
**           </w:Selector>
**           <w:Selector Name="Key">
**             1001
**           </w:Selector>
**         </w:SelectorSet>
**       </a:ReferenceParameters>
**       </b:Object>
**       <b:AssociationClassName>
**           ABC_Connector
**       </b:AssociationClassName>
**       <b:Role>
**           Component
**       </b:Role>
**     <b:ResultClassName>
**       ABC_Gadget
**     </b:ResultClassName>
**     <b:ResultRole>
**       Part
**     </b:ResultRole>
**   </b:AssociatedInstances>
**
**==============================================================================
*/

static int _ParseAssociationFilter(
    XML* xml, 
    Batch* batch,
    WSMAN_AssociationFilter* filter)
{
    XML_Elem e;

    /* Expect <AssociatedInstances> */

    if (XML_Next(xml, &e) != 0 || e.type != XML_START )
    {
    	RETURN(-1);
    }

    if (PAL_T('b') == e.data.namespaceId &&
        Tcscmp(e.data.data, PAL_T("AssociatedInstances")) == 0)
    {
    	filter->isAssosiatorOperation = MI_TRUE;
    }
    else if (PAL_T('b') == e.data.namespaceId &&
        Tcscmp(e.data.data, PAL_T("AssociationInstances")) == 0)
    {
    	filter->isAssosiatorOperation = MI_FALSE;
    }
    else
        RETURN(-1);

    /* Parse child elements */

    for (;;)
    {
        /* Get next element */

        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        /* Put it back and break out if not a start tag */

        if (e.type != XML_START)
        {
            if (XML_PutBack(xml, &e) != 0)
                RETURN(-1);

            break;
        }

        /* Handle "Object" tag */

        if (PAL_T('b') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("Object")) == 0)
        {
            if (_ParseAssociationFilterObject(xml, batch, filter) != 0)
                RETURN(-1);
        }
        else if (PAL_T('b') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("AssociationClassName")) == 0)
        {
            filter->associationClassName = _ExpectCharsAndEnd(
                xml, PAL_T('b'), PAL_T("AssociationClassName"));

            if (!filter->associationClassName)
                RETURN(-1);
        }
        else if (PAL_T('b') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("Role")) == 0)
        {
            filter->role = _ExpectCharsAndEnd(xml, PAL_T('b'), PAL_T("Role"));

            if (!filter->role)
                RETURN(-1);
        }
        else if (PAL_T('b') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("ResultClassName")) == 0)
        {
            filter->resultClassName = _ExpectCharsAndEnd(
                xml, 
                PAL_T('b'),
                PAL_T("ResultClassName"));

            if (!filter->resultClassName)
                RETURN(-1);
        }
        else if (PAL_T('b') == e.data.namespaceId &&
            Tcscmp(e.data.data, PAL_T("ResultRole")) == 0)
        {
            filter->resultRole = _ExpectCharsAndEnd(
                xml, 
                PAL_T('b'),
                PAL_T("ResultRole"));

            if (!filter->resultRole)
                RETURN(-1);
        }
        else
        {
            if (XML_Skip(xml) != 0)
                RETURN(-1);
        }
    }

    if(filter->isAssosiatorOperation == MI_TRUE)
    {
    	/* Expect </AssociatedInstances> */
    	if (XML_Expect(xml, &e, XML_END, PAL_T('b'), PAL_T("AssociatedInstances")) != 0)
    		RETURN(-1);
    }
    else
    {
    	/* Expect </AssociationInstances> */
    	if (XML_Expect(xml, &e, XML_END, PAL_T('b'), PAL_T("AssociationInstances")) != 0)
    		RETURN(-1);
    }

    return 0;
}

/* Parse query dialect */
static const ZChar* _WS_ParseDialect(
    _In_z_ const ZChar* dialect,
    MI_Boolean isSubscribe)
{
    /* See DSP0202.pdf */
    if (Tcscasecmp(ZT("http://schemas.dmtf.org/wbem/cql/1/dsp0202.pdf"), dialect) == 0)
        return MI_QUERY_DIALECT_CQL;

    if (Tcscasecmp(ZT("http://schemas.microsoft.com/wbem/wsman/1/WQL"), dialect) == 0)
        return MI_QUERY_DIALECT_WQL;

    /* Event stream dialect is not supported yet */
    /* if (isSubscribe && Tcscasecmp(ZT("http://schemas.microsoft.com/wbem/wsman/1/MINT"), dialect) == 0)
        return QUERY_LANGUAGE_EVENTSTREAM; */

    if (isSubscribe)
        return dialect;

    return NULL;
}

int WS_ParseEnumerateBody(
    XML* xml, 
    Batch** batch,
    WSMAN_WSEnumeratePullBody* wsenumbody)
{
    XML_Elem e;

    memset(wsenumbody, 0, sizeof(WSMAN_WSEnumeratePullBody));

    /* Allocate batch (owned by WSMAN_ConnectionData object */

    if (*batch == NULL)
    {
        *batch = Batch_New(BATCH_MAX_PAGES);

        if (!*batch)
            RETURN(-1);
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <n:Enumerate> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('n'), PAL_T("Enumerate")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data.namespaceId, e.data.data, e.data.size);

            if (WSMANTAG_ENUM_ENUMERATE != tag)
            {
                trace_Wsman_UnexpectedCloseTag(tcs(e.data.data));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
        {
        case WSMANTAG_ENUM_MAX_ELEMENTS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumbody->maxElements = (MI_Uint32)Tcstoull(e.data.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("MaxElements")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_ENUM_OPTIMIZE_ENUMERATION:
            {
                wsenumbody->allowOptimization = MI_TRUE;

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_ENUM_POLYMORPHISM_MODE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumbody->polymorphismMode = HashStr(e.data.namespaceId, e.data.data, e.data.size);

                if (XML_Expect(xml, &e, XML_END, PAL_T('b'), PAL_T("PolymorphismMode")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_ENUM_MODE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumbody->enumerationMode = HashStr(e.data.namespaceId, e.data.data, e.data.size);

                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("EnumerationMode")) != 0)
                    RETURN(-1);
            }
            break;

        /* 
         * Examples:
         *   <w:Filter Dialect="http://microsoft.com/wbem/wsman/1/WQL">
         *     SELECT Weight FROM Widget WHERE Key = 1001
         *   </w:Filter>
         *
         *   <w:Filter Dialect="http://microsoft.com/wbem/wsman/1/WQL">
         *     <b:AssociatedInstances>
         *       ...
         *     </b:AssociatedInstances>
         *   </w:Filter>
         */
        case WSMANTAG_ENUM_FILTER:
            {
                const TChar* dialect;

                /* Get 'Dialect' attribute? */
                dialect = XML_Elem_GetAttr(&e, 0, PAL_T("Dialect"));
                if (!dialect)
                {
                    trace_Wsman_FilterTagMissingDialectAttribute();
                    RETURN(-1);
                }

                /* Parse the association filter */
                if (Tcscasecmp(dialect, URI_CIMBINDING PAL_T("/associationFilter")) == 0)
                {
                    wsenumbody->dialect = PAL_T("associationFilter");
                    wsenumbody->foundAssociationOperation = MI_TRUE;

                    if (_ParseAssociationFilter(xml, *batch, &wsenumbody->associationFilter) != 0)
                    {
                        RETURN(-1);
                    }
                }
                else
                {
                    /* Parse the dialect */
                    wsenumbody->dialect = _WS_ParseDialect(dialect, MI_FALSE);

                    if (!wsenumbody->dialect)
                    {
                        trace_WsmanEnum_UnknownDialect(tcs(dialect));
                        RETURN(-1);
                    }

                    /* Get the filter text */
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);

                    wsenumbody->filter = e.data.data;
                }

                /* Check for closing </w:Filter> tag */
                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("Filter")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    trace_Wsman_UnknownMandatoryTag(tcs(e.data.data));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseInvokeBody(
    XML* xml, 
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <?:?> parameter's tag */
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        /* empty body? can be valid for methods without parameters */
        if (e.type == XML_END)
            return 0;

        if (e.type == XML_START)
            break;
    }

    if (0 != _GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams))
        RETURN(-1);


    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseCreateBody(
    XML* xml, 
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <?:?> parameter's tag */
    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if (0 != _GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams))
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParsePullBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wsenumpullbody)
{
    XML_Elem e;

    memset(wsenumpullbody, 0, sizeof(WSMAN_WSEnumeratePullBody));

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <n:Enumerate> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('n'), PAL_T("Pull")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data.namespaceId, e.data.data, e.data.size);

            if (WSMANTAG_ENUM_PULL != tag)
            {
                trace_Wsman_UnexpectedCloseTag(tcs(e.data.data));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
        {
        case WSMANTAG_PULL_MAX_ELEMENTS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->maxElements = (MI_Uint32)Tcstoull(e.data.data, NULL, 10);
                if (XML_Expect(xml, &e, XML_END, PAL_T('n'), PAL_T("MaxElements")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_MAX_TIME:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (-1 == ParseWSManDatetime( e.data.data, &wsenumpullbody->maxTime.value ) )
                    RETURN(-1);

                wsenumpullbody->maxTime.exists = MI_TRUE;

                if (XML_Expect(xml, &e, XML_END, PAL_T('n'), PAL_T("MaxTime")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_MAX_CHARACTERS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->maxCharacters.value = Tcstoull(e.data.data, NULL, 10);
                wsenumpullbody->maxCharacters.exists = MI_TRUE;

                if (XML_Expect(xml, &e, XML_END, PAL_T('n'), PAL_T("MaxCharacters")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_PULL_ENUMERATION_CONTEXT:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->enumerationContextID = (MI_Uint32)Tcstoull(
                    e.data.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, PAL_T('n'), PAL_T("EnumerationContext")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    trace_Wsman_UnknownMandatoryTag(tcs(e.data.data));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseReleaseBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wsenumpullbody)
{
    XML_Elem e;

    memset(wsenumpullbody, 0, sizeof(WSMAN_WSEnumeratePullBody));

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <n:Release> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('n'), PAL_T("Release")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data.namespaceId, e.data.data, e.data.size);

            if (WSMANTAG_ENUM_RELEASE != tag)
            {
                trace_Wsman_UnexpectedCloseTag(tcs(e.data.data));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
        {
        case WSMANTAG_PULL_ENUMERATION_CONTEXT:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->enumerationContextID = (MI_Uint32)Tcstoull(
                    e.data.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, PAL_T('n'), PAL_T("EnumerationContext")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    trace_Wsman_UnknownMandatoryTag(tcs(e.data.data));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseIdentifyBody(
    XML* xml)
{
    XML_Elem e;

    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_START, PAL_T('i'), PAL_T("Identify")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, PAL_T('i'), PAL_T("Identify")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}


#ifndef DISABLE_INDICATION

typedef enum _SubscribeSequence
{
    SubscribeSequence_NONE = 0,
    SubscribeSequence_EXPIRES = 1,
    SubscribeSequence_FILTER = 2,
    SubscribeSequence_END = 3
} SubscribeSequence;

/* Parse subscribe body, One example,
    <s:Body>
        <e:Subscribe>
            <e:Delivery Mode="http://schemas.dmtf.org/wbem/wsman/1/wsman/Pull">
                <w:Heartbeats>PT60.000S</w:Heartbeats>
                <w:Locale xml:lang="en-US" s:mustUnderstand="false"/>
                <p:DataLocale xml:lang="en-US" s:mustUnderstand="false"/>
                <w:ContentEncoding>UTF-16</w:ContentEncoding>
            </e:Delivery>
            <e:Expires>
                "PT60.000S"
            </e:Expires>
            <w:Filter Dialect="http://schemas.microsoft.com/wbem/wsman/1/WQL">
                Select * from My_Alarm"
            </w:Filter>
        </e:Subscribe>
    </s:Body>
*/
int WS_ParseSubscribeBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wssubbody)
{
    XML_Elem e;
    SubscribeSequence sequenceState = SubscribeSequence_NONE;

    memset(wssubbody, 0, sizeof(WSMAN_WSEnumeratePullBody));

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, ZT('s'), ZT("Body")) != 0)
        RETURN(-1);

    /* Expect <e:Subscribe> */
    if (XML_Expect(xml, &e, XML_START, ZT('e'), ZT("Subscribe")) != 0)
        RETURN(-1);

    /* A subscribe message body is made up of an xs:sequence of the following:
     * 1 - EndTo    (Optional)
     * 2 - Delivery
     * 3 - Expires  (Optional)
     * 4 - Filter   (Optional)
     */

    /* Expect <e:Delivery> */
    if (XML_Expect(xml, &e, XML_START, ZT('e'), ZT("Delivery")) != 0)
        RETURN(-1);

    {
        const XML_Char* mode = NULL;
        
        /* Read 'Mode' attribute */
        mode = XML_Elem_GetAttr(&e, 0, ZT("Mode"));
        if (mode)
        {
            int tag = HashStr( 0, mode, Tcslen(mode));
            if (WSMAN_DELIVERY_MODE_PULL != tag)
            {
                trace_Wsman_UnsupportedDeliveryMode(mode);
                RETURN(-1);
            }
            else
            {
                trace_Wsman_DeliveryMode(mode);
            }
        }
        else
        {
            trace_Wsman_ExpectedDeliveryMode();
            RETURN(-1);
        }
    }
    
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data.namespaceId, e.data.data, e.data.size);

            /* The end tag for Delivery was encountered, so jump out of the loop. */
            if (WSMANTAG_SUBSCRIBE_DELIVER != tag)
            {
                trace_Wsman_UnexpectedCloseTagWithNamespace(e.data.namespaceId, e.data.data);
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
        {
        case WSMANTAG_SUBSCRIBE_HEARTBEATS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);
                
                if (-1 == ParseWSManDatetime( e.data.data, &wssubbody->heartbeat.value ) )
                    RETURN(-1);

                wssubbody->heartbeat.exists = MI_TRUE;

                if (XML_Expect(xml, &e, XML_END, ZT('w'), ZT("Heartbeats")) != 0)
                    RETURN(-1);
            }
            break;

         case WSMANTAG_SUBSCRIBE_CONTENTENCODING:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, ZT('w'), ZT("ContentEncoding")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_SUBSCRIBE_CONNECTION_RETRY:
           {
               if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                   RETURN(-1);

                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);
                
                if (-1 == ParseWSManDatetime( e.data.data, &wssubbody->connectionRetry.value ) )
                    RETURN(-1);
                
                wssubbody->connectionRetry.exists = MI_TRUE;

               if (XML_Expect(xml, &e, XML_END, ZT('w'), ZT("ConnectionRetry")) != 0)
                   RETURN(-1);
           }
           break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    trace_Wsman_UnknownMandatoryTagWithNamespace(e.data.namespaceId, e.data.data);
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    for (;;)
    {
        /* Get the next element and check for proper order of optional tags 
         * within the sequence. This loop ensures order and stops when it 
         * hits a parse error or encounters the body end tag.*/
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_START)
        {
            switch (HashStr(e.data.namespaceId, e.data.data, e.data.size))
            {
            case WSMANTAG_EXPIRES:
                {
                    /* Parse Expires (if present) */
                    if (sequenceState >= SubscribeSequence_EXPIRES)
                        RETURN(-1);
                    sequenceState = SubscribeSequence_EXPIRES;

                    /* Expect an xs:duration of form: PnYnMnDTnHnMnS */
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);
                    
                    if (XML_StripWhitespace(&e) != 0)
                        RETURN(-1);
                    
                    if (-1 == ParseWSManDatetime( e.data.data, &wssubbody->expires.value ) )
                        RETURN(-1);

                    wssubbody->expires.exists = MI_TRUE;

                    /* Check for closing </w:Expires> tag */
                    if (XML_Expect(xml, &e, XML_END, ZT('e'), ZT("Expires")) != 0)
                        RETURN(-1);
                }
                break;
            case WSMANTAG_ENUM_FILTER:
                {
                    /* Parse filter and dialect */
                    const XML_Char* dialect;
                    if (sequenceState >= SubscribeSequence_FILTER)
                        RETURN(-1);
                    sequenceState = SubscribeSequence_FILTER;

                    /* Read 'Dialect' attribute */
                    dialect = XML_Elem_GetAttr(&e, 0, ZT("Dialect"));
                    if (!dialect)
                    {
                        trace_Wsman_FilterTagMissingDialectAttribute();
                        RETURN(-1);
                    }
                    wssubbody->dialect = _WS_ParseDialect(dialect, MI_TRUE);
                    if (!wssubbody->dialect)
                    {
                        trace_Wsman_UnknownDialect(dialect);
                        RETURN(-1);
                    }
                    else
                        trace_Wsman_SubscribeDialect(dialect);

                    /* Get the filter text */
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);

                    wssubbody->filter = e.data.data;
                    trace_Wsman_SubscribeFilter(wssubbody->filter);

                    /* Check for closing </w:Filter> tag */
                    if (XML_Expect(xml, &e, XML_END, ZT('w'), ZT("Filter")) != 0)
                        RETURN(-1);                
                }
                break;
            case WSMANTAG_SEND_BOOKMARKS:
                {
                    wssubbody->sendBookmarks = MI_TRUE;

                    if (XML_Skip(xml) != 0)
                        RETURN(-1);
                }
                break;
            case WSMANTAG_BOOKMARK:
                {
                    /* Parse Bookmark */
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);
                    
                    if (XML_StripWhitespace(&e) != 0)
                        RETURN(-1);
                    
                    wssubbody->initialBookmark = e.data.data;
                    
                    if (XML_Expect(xml, &e, XML_END, ZT('w'), ZT("Bookmark")) != 0)
                        RETURN(-1);
                }
                break;
            default:
                RETURN(-1);
            }
        }
        else if (e.type == XML_END)
        {
            /* Expect </e:Subscribe> */
            if (ZT('e') == e.data.namespaceId &&
                Tcscmp(e.data.data, ZT("Subscribe")) == 0)
            {
                sequenceState = SubscribeSequence_END;
                /* We reached the end of the subscribe body an the end of the
                 * xs:sequence.  Jump out to proceed. */
                break;
            }
            else
                RETURN(-1);
        }
        else
            RETURN(-1);
    }

    /* Expect </s:Body> */
    if (XML_Expect(xml, &e, XML_END, ZT('s'), ZT("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT('s'), ZT("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

/* Unsubcribe message sample:
<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope" xmlns:a="http://schemas.xmlsoap.org/ws/2004/08/addressing" xmlns:e="http://schemas.xmlsoap.org/ws/2004/08/eventing" xmlns:n="http://schemas.xmlsoap.org/ws/2004/09/enumeration" xmlns:w="http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd" xmlns:p="http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd">
    <s:Header>
        <a:To>http://localhost:5985/wsman</a:To>
        <a:ReplyTo>
            <a:Address s:mustUnderstand="true">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>
        </a:ReplyTo>
        <a:Action s:mustUnderstand="true">http://schemas.xmlsoap.org/ws/2004/08/eventing/Unsubscribe</a:Action>
        ......
        <e:Identifier xmlns:e="http://schemas.xmlsoap.org/ws/2004/08/eventing">0860D524-6F0A-46FE-B95E-7CB0C1A2C1B8</e:Identifier>
    </s:Header>
    <s:Body>
        <e:Unsubscribe/>
    </s:Body>
</s:Envelope>
*/
int WS_ParseUnsubscribeBody(
    XML* xml, 
    WSMAN_WSEnumeratePullBody* wsunsubbody)
{
    XML_Elem e;

    memset(wsunsubbody, 0, sizeof(WSMAN_WSEnumeratePullBody));

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, ZT('s'), ZT("Body")) != 0)
        RETURN(-1);

    /* Expect <e:Subscribe> */
    if (XML_Expect(xml, &e, XML_START, MI_T('e'), ZT("Unsubscribe")) != 0)
        RETURN(-1);

    /* Expect </e:Subscribe> */
    if (XML_Expect(xml, &e, XML_END, MI_T('e'), ZT("Unsubscribe")) != 0)
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, MI_T('s'), ZT("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, MI_T('s'), ZT("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

#endif /* #ifndef DISABLE_INDICATION */
