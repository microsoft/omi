/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
static int _GetReference(
    XML* xml,
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean isShell);

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
            else if (IsValidClassname(e->attrs[i].value)) /* Ignore if this is not a valid property name */
            {
                MI_Value value;

                if (wsheader->options == NULL)
                {
                    if (wsheader->instanceBatch == NULL)
                    {
                        wsheader->instanceBatch = Batch_New(BATCH_MAX_PAGES);
                        if (wsheader->instanceBatch == NULL)
                            return(-1);
                    }
                    if (Instance_NewDynamic(&wsheader->options, MI_T("Options"), MI_FLAG_CLASS, wsheader->instanceBatch) != MI_RESULT_OK)    /* TODO: Which batch? */
                        return(-1);
                }

                value.string = e->data.data;
                if (MI_Instance_AddElement(wsheader->options, e->attrs[i].value, &value, MI_STRING, 0) != MI_RESULT_OK)
                    return(-1);
            }
        }
        else
        {
            continue;
        }

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

    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if((e.type == XML_END) &&
        (e.data.namespaceId == MI_T('w')) &&
        (Tcscmp(PAL_T("OptionSet"), e.data.data) == 0))
    {
        /* Empty option set */
        return 0;
    }

    if((e.type != XML_START) ||
        (e.data.namespaceId != MI_T('w')) ||
        (Tcscmp(PAL_T("Option"), e.data.data) != 0))
    {
        RETURN(-1);
    }

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

                    if (!*batch)
                    {
                        *batch = Batch_New(BATCH_MAX_PAGES);
                        if (!(*batch))
                            RETURN(-1);
                    }


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
                        if (0 != _GetReference(xml, e, *batch, &(value.instance), MI_FALSE))
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
static int _GetSelectorFilter(
    XML* xml,
    _In_ Batch*  dynamicBatch,
    _Inout_ MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    MI_Result r;

    r = Instance_NewDynamic(dynamicInstanceParams, MI_T("SelectorFilter"), MI_FLAG_CLASS, dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_START, PAL_T('w'), PAL_T("Selector")) != 0)
        RETURN(-1);

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

    return 0;
}


static int _GetReferenceParameters(
    _In_ XML* xml,
    _In_ Batch*  dynamicBatch,
    _Inout_ MI_Instance** dynamicInstanceParams,
    MI_Boolean isShell)
{
    XML_Elem e;
    const TChar* classname = NULL;
    TChar* resourceURI = NULL;
    const TChar* nameSpace = NULL;

    /* extract ResourceURI and SelectorSet */
    for (;;)
    {
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);

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

            if (isShell)
            {
                classname = MI_T("Shell");
                resourceURI = e.data.data;
            }

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
                if (GetNextSkipCharsAndComments(xml, &e) != 0)
                    RETURN(-1);

                if (XML_END == e.type)
                    break;

            }
            continue;
        }
    }

    if (nameSpace)
        (*dynamicInstanceParams)->nameSpace = nameSpace;

    if (resourceURI)
    {
        MI_Value value;
        value.string = resourceURI;
        if (__MI_Instance_AddElement(*dynamicInstanceParams, MI_T("ResourceUri"), &value, MI_STRING, 0) != MI_RESULT_OK)
            RETURN(-1);
    }

    return 0;
}

static int _GetReference(
    XML* xml,
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean isShell)
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

            if (GetNextSkipCharsAndComments(xml, &e) != 0)
                RETURN(-1);

            if (e.type == XML_END)
                break;

            continue;
        }

        if (0 != _GetReferenceParameters(xml, dynamicBatch, dynamicInstanceParams, isShell))
            RETURN(-1);

        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);
        
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
    MI_Boolean* null,
    MI_Uint32 rqtAction)
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
            /* Reference as </address></ReferenceParameters>*/
            value->instance = 0;
            if (0 != _GetReference(xml, &e, dynamicBatch, &value->instance, MI_FALSE))
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

            if (0 != WS_GetInstance(xml, start, dynamicBatch, &value->instance, rqtAction))
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

int WS_GetInstance(
    XML* xml,
    XML_Elem *start,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction)
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
#ifndef DISABLE_SHELL
        MI_Instance *embeddedShellInstance = NULL;
#endif

        if (GetNextSkipCharsAndComments(xml, &e) != 0)
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

#ifndef DISABLE_SHELL
            if (rqtAction == WSMANTAG_ACTION_SHELL_COMMAND)
            {
               /* If this is the shell Receive Response then we have optional CommandId attribute that 
                * needs to be extracted and put in 
                * the instance
                */
                const TChar* commandId = XML_Elem_GetAttr(start, 0, PAL_T("CommandId"));
                if (commandId)
                {
                    MI_Value value;
                    value.string = (TChar*) commandId;
                    if (__MI_Instance_AddElement(*dynamicInstanceParams, MI_T("CommandId"), &value, MI_STRING, 0) != MI_RESULT_OK)
                    {
                        RETURN(-1);
                    }
                }
            }
#endif
        }

#ifndef DISABLE_SHELL
        if (rqtAction == WSMANTAG_ACTION_SHELL_RECEIVE_RESPONSE)
        {
            MI_Result r;
            const TChar *tmpStr;

            /* Stream and Command State are both embedded instances that require multiple 
             * attributes to get extracted
             */
             r = Instance_NewDynamic(
                    &embeddedShellInstance,
                    e.data.data,
                    MI_FLAG_CLASS,
                    dynamicBatch);

            if (MI_RESULT_OK != r)
                    RETURN(-1);

            /* Both parameters have optional commandId's */
            tmpStr = XML_Elem_GetAttr(&e, 0, PAL_T("CommandId"));
            if (tmpStr)
            {
                MI_Value value;
                value.string = (TChar*) tmpStr;
                if (__MI_Instance_AddElement(embeddedShellInstance, MI_T("CommandId"), &value, MI_STRING, 0) != MI_RESULT_OK)
                {
                    RETURN(-1);
                }
            }

            if (Tcscmp(e.data.data, MI_T("Stream")) == 0)
            {
                tmpStr = XML_Elem_GetAttr(&e, 0, PAL_T("Name"));
                if (tmpStr)
                {
                    MI_Value value;
                    value.string = (TChar*) tmpStr;
                    if (__MI_Instance_AddElement(embeddedShellInstance, MI_T("streamName"), &value, MI_STRING, 0) != MI_RESULT_OK)
                    {
                        RETURN(-1);
                    }
                }

                tmpStr = XML_Elem_GetAttr(&e, 0, PAL_T("End"));
                if (tmpStr && (Tcscmp(tmpStr, MI_T("true")) == 0 || Tcscmp(tmpStr, MI_T("1")) == 0))
                {
                    MI_Value value;
                    value.boolean = 1;
                    if (__MI_Instance_AddElement(embeddedShellInstance, MI_T("endOfStream"), &value, MI_BOOLEAN, 0) != MI_RESULT_OK)
                    {
                        RETURN(-1);
                    }
                }
            }
            else if (Tcscmp(e.data.data, MI_T("CommandState")) == 0)
            {
                tmpStr = XML_Elem_GetAttr(&e, 0, PAL_T("State"));
                if (tmpStr)
                {
                    MI_Value value;
                    value.string = (TChar*) tmpStr;
                    if (__MI_Instance_AddElement(embeddedShellInstance, MI_T("State"), &value, MI_STRING, 0) != MI_RESULT_OK)
                    {
                        RETURN(-1);
                    }
                }

            }
        }
#endif
 
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
                &null, 
                rqtAction) != 0)
            {
                trace_GetSingleProperty_Failed( tcs(propNameChar) );
                RETURN(-1);
            }
#ifndef DISABLE_SHELL
            if (rqtAction == WSMANTAG_ACTION_SHELL_RECEIVE_RESPONSE)
            {
                if (Tcscmp(propName, MI_T("Stream")) == 0)
                {
                    /* Add the data into the embedded object */
                    r = MI_Instance_AddElement(embeddedShellInstance, MI_T("data"), &value, type, MI_FLAG_BORROW);
                    if (MI_RESULT_OK != r)
                        RETURN(-1);
                }

                /* Now make our embedded instance become the real data to add */
                value.instance = embeddedShellInstance;
                type = MI_INSTANCE;
                null = MI_FALSE;
            }
#endif

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
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
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
                wsheader->rqtResourceUri = e.data.data;

#ifndef DISABLE_SHELL
                if (!wsheader->isShellOperation)
                {
#endif
                    wsheader->rqtClassname = Tcsrchr(e.data.data, '/');
                    /* skip '/' */
                    if (wsheader->rqtClassname)
                        wsheader->rqtClassname++;
#ifndef DISABLE_SHELL
                }
                else
                {
                    wsheader->rqtClassname = PAL_T("Shell");
                }
#endif
                if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("ResourceURI")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_REPLY_TO:
            {
                if (XML_Expect(xml, &e, XML_START, PAL_T('a'), PAL_T("Address")) != 0)
                    RETURN(-1);

                if (HashStr(e.data.namespaceId, e.data.data, e.data.size) != WSMANTAG_ADDRESS)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("Address")) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("ReplyTo")) != 0)
                    RETURN(-1);

                if (HashStr(e.data.namespaceId, e.data.data, e.data.size) != WSMANTAG_REPLY_TO)
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

                switch (wsheader->rqtAction)
                {
#ifndef DISABLE_SHELL
                case WSMANTAG_ACTION_SHELL_COMMAND:
                case WSMANTAG_ACTION_SHELL_SIGNAL:
                case WSMANTAG_ACTION_SHELL_RECEIVE:
                case WSMANTAG_ACTION_SHELL_SEND:
                case WSMANTAG_ACTION_SHELL_CONNECT:
                case WSMANTAG_ACTION_SHELL_RECONNECT:
                case WSMANTAG_ACTION_SHELL_DISCONNECT:
#endif
                case 0:
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

                    if (0 == Tcsncmp(s, PAL_T("wbem/wscim/1/cim-schema/2/"), 26))
                    {
                        s += 26;
                    }
#ifndef DISABLE_SHELL
                    else if (0 == Tcsncmp(s, PAL_T("wbem/wsman/1/windows/"), 21))
                    {
                        s += 21;
                        wsheader->isShellOperation = MI_TRUE;
                    }
#endif
                    else
                    {
                        RETURN(-1);
                    }

                    wsheader->rqtClassname = s;
                    s = Tcschr(s, '/');

                    if (!s)
                        RETURN(-1);

                    *s = 0;
                    s++;
                    wsheader->rqtMethod = s;
                }
            }

            if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("Action")) != 0)
                RETURN(-1);
            break;
            }

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

#ifndef DISABLE_SHELL
            case WSMANTAG_COMPRESSION_TYPE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, MI_T("xpress")) != 0)
                    RETURN(-1);
                if (XML_Expect(xml, &e, XML_END, MI_T('h'), MI_T("CompressionType")) != 0)
                    RETURN(-1);
                wsheader->isCompressed = MI_TRUE;
            }
            break;

#endif
            case WSMANTAG_LOCALE:
            {
                const TChar* p = XML_Elem_GetAttr(&e, 0, MI_T("lang"));
                if (p == NULL)
                    RETURN(-1);
                if (XML_Expect(xml, &e, XML_END, MI_T('w'), MI_T("Locale")) != 0)
                    RETURN(-1);
                wsheader->rqtLocale = p;
            }
            break;
            case WSMANTAG_DATA_LOCALE:
            {
                const TChar* p = XML_Elem_GetAttr(&e, 0, MI_T("lang"));
                if (p == NULL)
                    RETURN(-1);
                if (XML_Expect(xml, &e, XML_END, MI_T('p'), MI_T("DataLocale")) != 0)
                    RETURN(-1);
                wsheader->rqtDataLocale = p;
            }
            break;
            
            case WSMANTAG_RELATES_TO:
            {
                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                    RETURN(-1);
                if (XML_StripWhitespace(&e) != 0)
                    RETURN(-1);
                wsheader->rspRelatesTo = e.data.data;

                if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("RelatesTo")) != 0)
                    RETURN(-1);
            }
            break;

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
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
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
                &filter->referenceParameters,
                MI_FALSE) != 0)
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
                else if (Tcscasecmp(dialect, PAL_T("http://schemas.dmtf.org/wbem/wsman/1/wsman/SelectorFilter")) == 0)
                {
                    wsenumbody->dialect = PAL_T("selectorFilter");
                    if (XML_Expect(xml, &e, XML_START, PAL_T('w'), PAL_T("SelectorSet")) != 0)
                    {
                        RETURN(-1);
                    }
                    if (_GetSelectorFilter(xml, *batch, &wsenumbody->selectorFilter) != 0)
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
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction)
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

    if (0 != WS_GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams, rqtAction))
        RETURN(-1);


    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

#ifndef DISABLE_SHELL
int WS_ParseCreateShellBody(
    XML* xml,
    XML_Elem *bodyElem,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    MI_Result r;
    MI_Value value;
    const MI_Char *attr;

    *dynamicInstanceParams = 0;

    /* Already parsed <s:Body><h:Shell> in WS_ParseCreateBody */

    r = Instance_NewDynamic(
        dynamicInstanceParams,
        PAL_T("Shell"),
        MI_FLAG_CLASS,
        dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    attr = XML_Elem_GetAttr(bodyElem, 0, MI_T("Name"));
    if (!attr)
        RETURN(-1);
    value.string = (MI_Char*)attr;
    if (MI_Instance_AddElement(*dynamicInstanceParams, MI_T("Name") , &value, MI_STRING, 0) != MI_RESULT_OK)
        RETURN(-1);
    attr = XML_Elem_GetAttr(bodyElem, 0, MI_T("ShellId"));
    if (!attr)
        RETURN(-1);
    value.string = (MI_Char*)attr;
    if (MI_Instance_AddElement(*dynamicInstanceParams, MI_T("ShellId") , &value, MI_STRING, 0) != MI_RESULT_OK)
        RETURN(-1);

    do
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if ((e.type == XML_START) &&
            (e.data.namespaceId == PAL_T('h')) &&
            ((Tcscmp(e.data.data, PAL_T("WorkingDirectory")) == 0) ||
                (Tcscmp(e.data.data, PAL_T("InputStreams")) == 0) ||
                (Tcscmp(e.data.data, PAL_T("OutputStreams")) == 0)))
        {
            XML_Elem e2;
            if (XML_Expect(xml, &e2, XML_CHARS, 0, 0) != 0)
                RETURN(-1);
            value.string = e2.data.data;
            if (MI_Instance_AddElement(*dynamicInstanceParams, e.data.data, &value, MI_STRING, 0) != MI_RESULT_OK)
                RETURN(-1);

            if (XML_Expect(xml, &e, XML_END, PAL_T('h'), e.data.data) != 0)
                RETURN(-1);
        }
        else if ((e.type == XML_START) && (e.data.namespaceId == PAL_T('h')) && (Tcscmp(e.data.data, PAL_T("Environment")) == 0))
        {
            MI_Value valueA;
            memset(&valueA, 0, sizeof(valueA));

            /* Set of Variable entries */

            do
            {
                if (XML_Next(xml, &e) != 0)
                    RETURN(-1);

                if ((e.data.namespaceId == PAL_T('h')) &&
                    (Tcscmp(e.data.data, PAL_T("Variable")) == 0))
                {
                    /* There is a Name attribute and a string content for the Variable data */
                    XML_Elem e2;
                    MI_Instance *variableInstance;
                    const MI_Char *variableName = XML_Elem_GetAttr(&e, 0, PAL_T("Name"));
                    if (variableName == NULL)
                        RETURN(-1);
                    if (XML_Expect(xml, &e2, XML_CHARS, 0, 0) != 0)
                        RETURN(-1);
                    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Variable")) != 0)
                        RETURN(-1);

                    /* Create a Variable embedded object and add it to the valueA  */
                    r = Instance_NewDynamic(
                        &variableInstance,
                        PAL_T("EnvironmentVariable"),
                        MI_FLAG_CLASS,
                        dynamicBatch);
                    if (MI_RESULT_OK != r)
                        RETURN(-1);
                    value.string = (MI_Char *)variableName;
                    if (MI_Instance_AddElement(variableInstance, PAL_T("Name"), &value, MI_STRING, 0) != MI_RESULT_OK)
                        RETURN(-1);
                    if (MI_Instance_AddElement(variableInstance, PAL_T("Value"), &value, MI_STRING, 0) != MI_RESULT_OK)
                        RETURN(-1);
                    value.instance = variableInstance;
                    if (_AddValueToArray(dynamicBatch, &valueA, MI_INSTANCEA, &value, MI_INSTANCE) != 0)
                        RETURN(-1);

                }
                else if ((e.type == XML_END) && (e.data.namespaceId == PAL_T('h')) && (Tcscmp(e.data.data, PAL_T("Environment")) == 0))
                {
                    /* Ran off the end of our environment data */
                    /* Add the variables we found */
                    if (MI_Instance_AddElement(*dynamicInstanceParams, PAL_T("Environment"), &valueA, MI_INSTANCEA , MI_FLAG_BORROW) != MI_RESULT_OK)
                        RETURN(-1);

                    /* continue with the rest of the shell data */
                    break;
                }
                else
                    RETURN(-1);
            } while (1);
        }
        else if (e.type == XML_START)
        {
            XML_Elem e2;
            /* Additional shell specific initialization XML elements. The one we care about has a single string so lets grab that. */
            if (XML_Expect(xml, &e2, XML_CHARS, 0, 0) != 0)
                RETURN(-1);
            value.string = e2.data.data;
            if (MI_Instance_AddElement(*dynamicInstanceParams, e.data.data, &value, MI_STRING, 0) != MI_RESULT_OK)
                RETURN(-1);

            if (XML_Expect(xml, &e, XML_END, e.data.namespaceId, e.data.data) != 0)
                RETURN(-1);
        }
        else if ((e.type == XML_END) && (e.data.namespaceId == PAL_T('h')) && (Tcscmp(e.data.data, PAL_T("Shell")) == 0))
        {
            /* Ran off the end of our shell parameters so we are done */
            break;
        }
        else
            RETURN(-1);

    } while (1);


    /* </s:Body></s:Envelope> happens in continuation of WS_ParseCreateBody */

    return 0;
}

int WS_ParseReceiveBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    const MI_Char *commandId = 0;
    const MI_Char *streams = 0;
    MI_Result r;
    MI_Value value;
    MI_Uint32 flags;
    MI_Instance *desiredStream = NULL;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <h:Receive> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("Receive")) != 0)
        RETURN(-1);

    r = Instance_NewDynamic(
                    dynamicInstanceParams,
                    PAL_T("ReceiveParamaters"),
                    MI_FLAG_CLASS,
                    dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    r = Instance_NewDynamic(
                    &desiredStream,
                    PAL_T("DesiredStream"),
                    MI_FLAG_CLASS,
                    dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("DesiredStream")) == 0)
    {
        /* Attribute CommandId is optional -- not existing means receive data from shell itself */
        commandId = XML_Elem_GetAttr(&e, 0, PAL_T("CommandId"));

        /* Contents has list of requested streams */
        if (XML_Expect(xml, &e, XML_CHARS, 0, 0) != 0)
            RETURN(-1);

        streams = e.data.data;

        if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("DesiredStream")) != 0)
            RETURN(-1);
    }

    if (commandId == 0)
    {
        flags = MI_FLAG_NULL;
    }
    else
    {
        flags = 0;
    }
    value.string = (MI_Char *) commandId;
    if (MI_Instance_AddElement(desiredStream, PAL_T("commandId"), &value, MI_STRING, flags) != MI_RESULT_OK)
        RETURN(-1);

    if (streams == 0)
    {
        flags = MI_FLAG_NULL;
    }
    else
    {
        flags = 0;
    }

    value.string = (MI_Char *) streams;
    if (MI_Instance_AddElement(desiredStream, PAL_T("streamName"), &value, MI_STRING, 0) != MI_RESULT_OK)
        RETURN(-1);

    value.instance = desiredStream;
    if (MI_Instance_AddElement(*dynamicInstanceParams, PAL_T("DesiredStream"), &value, MI_INSTANCE, MI_FLAG_BORROW) != MI_RESULT_OK)
        RETURN(-1);

    /* Expect <h:Receive> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Receive")) != 0)
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseSendBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    const MI_Char *commandId = 0;
    const MI_Char *streamName = 0;
    const MI_Char *streamData = 0;
    MI_Uint32 streamDataLength = 0;
    const MI_Char *endOfStream = 0;
    MI_Result r;
    MI_Value value;
    MI_Instance *stream = 0;
    MI_Uint32 flags = 0;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <h:Receive> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("Send")) != 0)
        RETURN(-1);

    /* Expect <?:?> parameter's tag */
    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("Stream")) != 0)
        RETURN(-1);

    /* Attribute CommandId is optional -- not existing means receive data from shell itself */
    commandId = XML_Elem_GetAttr(&e, 0, PAL_T("CommandId"));

    /* Attribute End is optional -- not existing means stream has not yet ended */
    endOfStream = XML_Elem_GetAttr(&e, 0, PAL_T("End"));


    /* Attribute Name is the stream name (stdin) */
    streamName = XML_Elem_GetAttr(&e, 0, PAL_T("Name"));
    if (streamName == 0)
        RETURN(-1);

    /* May or may not have body so need to process the body specially */
    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if (e.type == XML_CHARS)
    {
        streamData = e.data.data;
        streamDataLength = e.data.size;

        if (XML_Next(xml, &e) != 0)
            RETURN(-1);
    }
    /* Current one is not the body so put it back so we can process it easier */
    XML_PutBack(xml, &e);

    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Stream")) != 0)
        RETURN(-1);

    r = Instance_NewDynamic(
                    dynamicInstanceParams,
                    PAL_T("SendParamaters"),
                    MI_FLAG_CLASS,
                    dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    r = Instance_NewDynamic(
                    &stream,
                    PAL_T("Stream"),
                    MI_FLAG_CLASS,
                    dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);


    if (commandId == 0)
        flags = MI_FLAG_NULL;
    else
        flags = 0;
    value.string = (MI_Char *) commandId;
    if (MI_Instance_AddElement(stream, PAL_T("commandId"), &value, MI_STRING, flags) != MI_RESULT_OK)
        return -1;

    value.string = (MI_Char *) streamName;
    if (MI_Instance_AddElement(stream, PAL_T("streamName"), &value, MI_STRING, 0) != MI_RESULT_OK)
        return -1;

    value.string = (MI_Char *) streamData;
    if (value.string == 0)
        flags = MI_FLAG_NULL;
    else
        flags = 0;
    if (MI_Instance_AddElement(stream, PAL_T("data"), &value, MI_STRING, flags) != MI_RESULT_OK)
        return -1;

    value.uint32 = streamDataLength;
    flags = 0;
    if (MI_Instance_AddElement(stream, PAL_T("dataLength"), &value, MI_UINT32, flags) != MI_RESULT_OK)
        return -1;

    if (endOfStream &&
            (Tcscasecmp(MI_T("true"), endOfStream) == 0 ||
             Tcscmp(MI_T("1"), endOfStream) == 0))
    {
        value.boolean = MI_TRUE;
    }
    else
    {
        value.boolean = MI_FALSE;
    }
    if (MI_Instance_AddElement(stream, PAL_T("endOfStream"), &value, MI_BOOLEAN, 0) != MI_RESULT_OK)
        return -1;

    value.instance = stream;
    if (MI_Instance_AddElement(*dynamicInstanceParams, PAL_T("streamData"), &value, MI_INSTANCE, MI_FLAG_BORROW) != MI_RESULT_OK)
        return -1;

    /* Expect <h:Send> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Send")) != 0)
        return -1;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        return -1;

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        return -1;

    return 0;
}
int WS_ParseSignalBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams)
{
    XML_Elem e;
    const MI_Char *commandId = 0;
    const MI_Char *signalCode = 0;
    MI_Result r;
    MI_Value value;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <h:Receive> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("Signal")) != 0)
        RETURN(-1);

    /* Attribute CommandId is optional -- not existing means receive data from shell itself */
    commandId = XML_Elem_GetAttr(&e, 0, PAL_T("CommandId"));

    if (XML_Expect(xml, &e, XML_START, PAL_T('h'), PAL_T("Code")) != 0)
        RETURN(-1);

    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if (e.type != XML_CHARS)
        RETURN(-1);

    /* Contents has list of requested streams */
    signalCode = e.data.data;

    r = Instance_NewDynamic(
                    dynamicInstanceParams,
                    PAL_T("SignalParamaters"),
                    MI_FLAG_CLASS,
                    dynamicBatch);
    if (MI_RESULT_OK != r)
        RETURN(-1);

    {
        MI_Uint32 flags = 0;
        if (commandId == 0)
        {
            flags = MI_FLAG_NULL;
        }
        value.string = (MI_Char *) commandId;
        if (MI_Instance_AddElement(*dynamicInstanceParams, PAL_T("CommandId"), &value, MI_STRING, flags) != MI_RESULT_OK)
            RETURN(-1);
    }

    value.string = (MI_Char *) signalCode;
    if (MI_Instance_AddElement(*dynamicInstanceParams, PAL_T("code"), &value, MI_STRING, 0) != MI_RESULT_OK)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Code")) != 0)
        RETURN(-1);

    /* Expect <h:Receive> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('h'), PAL_T("Signal")) != 0)
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}
#endif

int WS_ParseCreateBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean *isShellOperation)
{
    XML_Elem e;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <?:?> parameter's tag */
    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

#ifndef DISABLE_SHELL
    if ((e.data.namespaceId == 'h') && (Tcscmp(e.data.data, PAL_T("Shell")) == 0)) /* This means we have a CreateShell body that needs custom parsing*/
    {
        if (WS_ParseCreateShellBody(xml, &e, dynamicBatch, dynamicInstanceParams) != 0)
            RETURN(-1);
        *isShellOperation = MI_TRUE;
    }
    else
    {
#endif
        if (0 != WS_GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams, 0))
            RETURN(-1);
#ifndef DISABLE_SHELL
    }
#endif

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

int WS_ParseInstanceBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Uint32 rqtAction)
{
    XML_Elem e;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
            return 0;

        if (e.type == XML_START)
            break;
    }

    if (0 != WS_GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams, rqtAction))
        RETURN(-1);


    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseCreateResponseBody(
    XML* xml,
    Batch*  dynamicBatch,
    MI_Char ** epr,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean isShell)
{
    XML_Elem e;

    *dynamicInstanceParams = 0;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_START, 0, PAL_T("ResourceCreated")) != 0)
        RETURN(-1);
    
    for (;;)
    {
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END && Tcscmp(e.data.data, PAL_T("ResourceCreated")) == 0)
            break;

        if (Tcscmp(e.data.data, PAL_T("Address")) == 0)
        {
            if (XML_Expect(xml, &e, XML_CHARS, 0, PAL_T("")) != 0)
                RETURN(-1);

            *epr = e.data.data;

            if (XML_Expect(xml, &e, XML_END, PAL_T('a'), PAL_T("Address")) != 0)
                RETURN(-1);
        }
        else if (Tcscmp(e.data.data, PAL_T("ReferenceParameters")) == 0)
        {
            if (0 != _GetReference(xml, &e, dynamicBatch, dynamicInstanceParams, isShell))
                RETURN(-1);            

            // _GetReference reads one tag ahead - ResourceCreated
                break;
        }
    }

    if (GetNextSkipCharsAndComments(xml, &e) != 0)
        RETURN(-1);

    if (e.type == XML_START)
    {
        /* We have the optional instance following */
        /* Forget the previous keys only instance, it will be cleaned
         * up when the batch goes 
         */
        *dynamicInstanceParams = NULL;
        if (0 != WS_GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams, 0))
            RETURN(-1);

        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);
    }

    /* Expect </s:Body> */
    if ((e.type != XML_END) &&  (e.data.namespaceId != PAL_T('s')) && (Tcscmp(e.data.data, PAL_T("Body")) != 0))
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseEmptyBody(
    XML* xml)
{
    XML_Elem e;

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Body> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

static int _FetchNextInstance(
    XML *xml,
    Batch *dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Char ns,
    XML_Elem *e,
    MI_Boolean *moreInstance)
{
    *moreInstance = MI_FALSE;

    if (e->type != XML_END || ns != e->data.namespaceId || (Tcscmp(e->data.data, ZT("Items")) != 0))
    {
        if (0 != WS_GetInstance(xml, e, dynamicBatch, dynamicInstanceParams, 0))
            RETURN(-1);

        if (GetNextSkipCharsAndComments(xml, e) != 0)
            RETURN(-1);

        if (e->type != XML_END || ns != e->data.namespaceId || (Tcscmp(e->data.data, ZT("Items")) != 0))
        {
            *moreInstance = MI_TRUE;
        }
    }
    return 0;
}

int WS_ParseEnumerateResponse(
    XML* xml, 
    const MI_Char **context,
    MI_Boolean *endOfSequence,
    Batch *dynamicBatch,
    MI_Instance** dynamicInstanceParams,
    MI_Boolean firstResponse,
    MI_Boolean *getNextInstance,
    XML_Elem *e)
{
    MI_Char *responseTag;
    MI_Char responseNS;

    *dynamicInstanceParams = 0;

    if (firstResponse == MI_TRUE)
    {
        responseTag = ZT("EnumerateResponse");
        responseNS = ZT('w');
    }
    else
    {
        responseTag = ZT("PullResponse");
        responseNS = ZT('n');
    }

    if (MI_FALSE == *getNextInstance)
    {
        /* Expect <s:Body> */
        if (XML_Expect(xml, e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
            RETURN(-1);

        /* Expect <n:EnumerateResponse> */
        if (XML_Expect(xml, e, XML_START, PAL_T('n'), responseTag) != 0)
            RETURN(-1);
    }

    for (;;)
    {
        if (MI_TRUE == *getNextInstance)
        {
            if (0 != _FetchNextInstance(xml, dynamicBatch, dynamicInstanceParams, responseNS, e, getNextInstance))
                RETURN(-1);

            if (MI_TRUE == *getNextInstance)
                return 0;
        }
        else
        {
            if (GetNextSkipCharsAndComments(xml, e) != 0)
                RETURN(-1);

            if (e->type == XML_END && (Tcscmp(e->data.data, responseTag) == 0))
                break;

            if (e->type != XML_START)
                continue;

            if (ZT('n') == e->data.namespaceId && (Tcscmp(e->data.data, ZT("EnumerationContext")) == 0))
            {
                if (0 != XML_Next(xml, e))
                    RETURN(-1);

                if (e->type == XML_CHARS)
                {
                    *context = e->data.data;

                    if (XML_Expect(xml, e, XML_END, PAL_T('n'), PAL_T("EnumerationContext")) != 0)
                        RETURN(-1);
                }
                else if (e->type == XML_END && ZT('n') == e->data.namespaceId && (Tcscmp(e->data.data, ZT("EnumerationContext")) == 0))
                    continue;
                else
                    RETURN(-1);
            }
            else if (responseNS == e->data.namespaceId && (Tcscmp(e->data.data, ZT("Items")) == 0))
            {
                if (GetNextSkipCharsAndComments(xml, e) != 0)
                    RETURN(-1);

                if (0 != _FetchNextInstance(xml, dynamicBatch, dynamicInstanceParams, responseNS, e, getNextInstance))
                    RETURN(-1);

                if (MI_TRUE == *getNextInstance)
                    return 0;
            }
            else if (responseNS == e->data.namespaceId && (Tcscmp(e->data.data, ZT("EndOfSequence")) == 0))
            {
                *endOfSequence = MI_TRUE;
            }
        }
    }

    /* Expect </s:Body> */
    if (XML_Expect(xml, e, XML_END, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, e, XML_END, PAL_T('s'), PAL_T("Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseFaultBody(
    XML* xml,
    WSMAN_WSFault *fault)
{
    XML_Elem e;
    fault->code[0] = '\0';
    fault->subcode[0] = '\0';
    fault->reason = NULL;
    fault->detail = NULL;
    fault->mi_result = 0;
    fault->mi_message = NULL;
                        
    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Body")) != 0)
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Fault")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (GetNextSkipCharsAndComments(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END && (Tcscmp(e.data.data, ZT("Fault")) == 0))
            break;

        if (e.type != XML_START)
            continue;

        if (ZT('s') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("Code")) == 0))
        {
            for (;;)
            {
                if (GetNextSkipCharsAndComments(xml, &e) != 0)
                    RETURN(-1);

                if (e.type == XML_END && (Tcscmp(e.data.data, ZT("Code")) == 0))
                    break;

                if (e.type != XML_START)
                    continue;

                if (ZT('s') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("Value")) == 0))
                {
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);

                    if (XML_ParseCharFault(xml, e.data.data, fault->code, sizeof(fault->code)/sizeof(MI_Char)) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Value")) != 0)
                        RETURN(-1);
                }
                else if (ZT('s') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("Subcode")) == 0))
                {
                    if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Value")) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);

                    if (XML_ParseCharFault(xml, e.data.data, fault->subcode, sizeof(fault->subcode)/sizeof(MI_Char)) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Value")) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Subcode")) != 0)
                        RETURN(-1);
                }
            }
        }
        else if (ZT('s') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("Reason")) == 0))
        {
            if (XML_Expect(xml, &e, XML_START, PAL_T('s'), PAL_T("Text")) != 0)
                RETURN(-1);

            if (XML_Next(xml, &e) != 0)
                RETURN(-1);
            
            if (e.type == XML_CHARS)
            {
                fault->reason = e.data.data;

                if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Text")) != 0)
                    RETURN(-1);
            }
            else if (e.type != XML_END || (Tcscmp(e.data.data, ZT("Text")) != 0))
                    RETURN(-1);

            if (XML_Expect(xml, &e, XML_END, PAL_T('s'), PAL_T("Reason")) != 0)
                RETURN(-1);
        }
        else if (ZT('s') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("Detail")) == 0))        
        {
            for (;;)
            {
                if (XML_Next(xml, &e) != 0)
                    RETURN(-1);

                if (e.type == XML_END && (Tcscmp(e.data.data, ZT("Detail")) == 0))
                    break;

                if (e.type != XML_START)
                    continue;

                if (ZT('w') == e.data.namespaceId && (Tcscmp(e.data.data, ZT("FaultDetail")) == 0))
                {
                    if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                        RETURN(-1);

                    fault->detail = e.data.data;

                    if (XML_Expect(xml, &e, XML_END, PAL_T('w'), PAL_T("FaultDetail")) != 0)
                        RETURN(-1);
                }
                else if (Tcscmp(e.data.data, ZT("OMI_Error")) == 0)
                {
                    const XML_Char* value = XML_Elem_GetAttr(&e, PAL_T('b'), ZT("IsCIM_Error"));
                    if (value != NULL && Tcscmp(value, ZT("true")) == 0)
                    {
                        // CIM Error
                        for (;;)
                        {
                            if (XML_Next(xml, &e) != 0)
                                RETURN(-1);

                            if (e.type == XML_END && (Tcscmp(e.data.data, ZT("OMI_Error")) == 0))
                                break;

                            if (e.type != XML_START)
                                continue;

                            if (Tcscmp(e.data.data, ZT("MessageID")) == 0)
                            {
                                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                                    RETURN(-1);

                                if (Tcsncmp(e.data.data, ZT("OMI:MI_Result:"), 14) == 0)
                                {
                                    fault->mi_result = Tcstol(&e.data.data[14], NULL, 10);
                                }

                                if (XML_Expect(xml, &e, XML_END, 0, PAL_T("MessageID")) != 0)
                                    RETURN(-1);
                            }
                            else if (Tcscmp(e.data.data, ZT("Message")) == 0)
                            {
                                if (XML_Expect(xml, &e, XML_CHARS, 0, NULL) != 0)
                                    RETURN(-1);

                                fault->mi_message = e.data.data;

                                if (XML_Expect(xml, &e, XML_END, 0, PAL_T("Message")) != 0)
                                    RETURN(-1);
                            }
                        }
                    }
                }
                else if (Tcscmp(e.data.data, ZT("WSManFault")) == 0)
                {
                    /* fault->mi_result should be MI_RESULT_FAILED for WSManFault */
                    fault->mi_result = MI_RESULT_FAILED;
    
                    if (XML_Expect(xml, &e, XML_START, 0, PAL_T("Message")) != 0)
                        RETURN(-1);

                    /* ProviderFault from Windows response:
                    WSMANTAG_ACTION_FAULT_ADDRESSING case:
                    <f:WSManFault>
                            <f:Message>
                                    <f:ProviderFault>
                                            <f:WSManFault>
                                                    <f:Message>...</f:Message>
                                            </f:WSManFault>
                                            <f:ExtendedError>...</f:ExtendedError>
                                    </f:ProviderFault>
                            </f:Message>
                    </f:WSManFault>
                    
                    Normal ProviderFault respones:
                    ERROR_INTERNAL_ERROR case:
                    <f:WSManFault>
                            <f:Message>
                                    <f:ProviderFault>...</f:ProviderFault>
                            </f:Message>
                    </f:WSManFault>
                    ERROR_WSMAN_OPERATION_TIMEDOUT case:
                    <f:WSManFault>
                            <f:Message>...</f:Message>
                    </f:WSManFault>
                    */
                    MI_Result providerFault = MI_FALSE;
                    MI_Result isSetDetail = MI_FALSE;
                    for (;;)
                    {
                        if (XML_Next(xml, &e) != 0)
                            RETURN(-1);
                        
                        if (e.type == XML_CHARS)
                        {
                            if(isSetDetail == MI_FALSE)
                            {
                                /*we will not set detail again once it is setted.*/
                                fault->detail = e.data.data;
                                isSetDetail = MI_TRUE;
                            }
                            
                            if(providerFault == MI_FALSE)
                            {
                                /*providerFault doesn't exist and the current element is a message string.*/
                                break;
                            }
                        }
                        else if (e.type == XML_START && Tcscmp(e.data.data, ZT("ProviderFault")) == 0)
                        {
                            providerFault = MI_TRUE;
                        }
                        else if (e.type == XML_END && Tcscmp(e.data.data, ZT("ProviderFault")) == 0)
                        {
                            break;
                        }
                    }

                    if (XML_Expect(xml, &e, XML_END, 0, PAL_T("Message")) != 0)
                        RETURN(-1);

                    if (XML_Expect(xml, &e, XML_END, 0, PAL_T("WSManFault")) != 0)
                        RETURN(-1);
                }
            }
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
