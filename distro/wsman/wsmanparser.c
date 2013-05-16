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
//#include "http.h"
//#include "time.h"
//#include <xml/xml.h>
//#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/strings.h>
#include <io/io.h>

#if defined(CONFIG_ENABLE_WCHAR)
# define HASHSTR_CHAR ZChar
# define HASHSTR_T(STR) L##STR
# define HASHSTR_STRCMP wcscmp
#endif

#include "wstags.h"
#include "wstags.inc"
#include <wsman/uri.h>

#if 0
#define ENABLE_TRACING
#endif

#define TRACE_RETURN

#if defined(TRACE_RETURN)
# define RETURN(X) \
    do \
    { \
        LOGD((ZT("RETURN{%d}"), __LINE__)); \
        return X; \
    } \
    while (0)
#else
# define RETURN(X) return X
#endif

/* Trim the namespace prefix from the XML name */
static const ZChar* _TrimNS(const ZChar* s)
{
    const ZChar* colon = Zchr(s, ':');
    return colon ? (colon + 1) : s;
}

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

/****************************************************************************************/
/* soap processing */

static int _MustUnderstandCanBeIgnored(
    const XML_Elem* e)
{
    size_t i;
    for (i = 0; i < e->attrsSize; i++)
    {
        if (Zcmp(e->attrs[i].name, ZT("s:mustUnderstand")) == 0 &&
            Zcmp(e->attrs[i].value, ZT("true")) == 0)
        {
            RETURN(-1);
        }
    }
    return 0;
}

static MI_Boolean IsValidClassname(const ZChar* classname)
{
    const ZChar* p = classname;

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

static int _GetSelector(
    _In_ XML* xml,
    _In_ XML_Elem *e,
    _Inout_ const ZChar** ns,
    _Inout_ const ZChar** classname,
    _Inout_ MI_Instance** instance,
    _Inout_ Batch** batch)
{
    size_t i;

    /* expecting namespace or key */
    for (i = 0; i < e->attrsSize; i++)
    {
        /* To support GetClass */
        if (Zcmp(e->attrs[i].name, ZT("Name")) == 0 &&
            Zcmp(e->attrs[i].value, ZT("ClassName")) == 0)
        {
            if (XML_Expect(xml, e, XML_CHARS, NULL) != 0)
                RETURN(-1);

            if (!IsValidClassname(e->data))
                RETURN(-1);
            *classname = e->data;
        }
        else if(
            Zcmp(e->attrs[i].name, ZT("Name")) == 0 &&
            Zcmp(e->attrs[i].value, ZT("__cimnamespace")) == 0)
        {
            /* namespace */
            if (XML_Expect(xml, e, XML_CHARS, NULL) != 0)
                RETURN(-1);

            *ns = e->data;
        }
        else if (Zcmp(e->attrs[i].name, ZT("Name")) == 0)
        {
            /* keys */
            const ZChar* propName = e->attrs[i].value;

            if (XML_Expect(xml, e, XML_CHARS, NULL) != 0)
                RETURN(-1);

            /* allocate batch and instance if needed */
            if (!(*instance))
            {
                MI_Result r;
                ZChar* cn;

                /* verify that we already received classname */
                if (!(*classname))
                {
                    XML_Raise(
                        xml,
                        ZT("class-name was not found during selector parsing"));
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

                cn = Batch_Zdup(*batch, *classname);
                if (!cn)
                    RETURN(-1);

                r = Instance_NewDynamic(instance, cn, MI_FLAG_CLASS, *batch);

                if (MI_RESULT_OK != r)
                    RETURN(-1);
            }

            /* add next property to the instance */
            {
                const ZChar* wpropName;
                MI_Result r;
                MI_Value value;

                if (!(*batch))
                {
                    *batch = Batch_New(BATCH_MAX_PAGES);

                    if (!(*batch))
                        RETURN(-1);
                }

                wpropName = Batch_Zdup(*batch, propName);
                if (!wpropName)
                    RETURN(-1);

                value.string = Batch_Zdup(*batch, e->data);
                if (!value.string)
                    RETURN(-1);

                // Set the property.
                r = MI_Instance_AddElement(*instance, wpropName, &value,
                    MI_STRING, MI_FLAG_BORROW | MI_FLAG_KEY);

                if (MI_RESULT_OK != r)
                    RETURN(-1);
            }
        }
        else
            continue;

        if (XML_Expect(xml, e, XML_END, ZT("w:Selector")) != 0)
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

    if (XML_Expect(xml, &e, XML_START, ZT("w:Selector")) != 0)
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
    const ZChar* classname = NULL;
    const ZChar* nameSpace = NULL;

    /* extract ResourceURI and SelectorSet */
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (XML_END == e.type)
            break;

        if (0 == Zcmp(ZT("w:ResourceURI"), e.data))
        {
            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                RETURN(-1);

            classname = Zrchr(e.data, '/');

            /* skip '/' */
            if (classname)
                classname++;

            if (XML_Expect(xml, &e, XML_END, ZT("w:ResourceURI")) != 0)
                RETURN(-1);

            continue;
        }

        if (0 == Zcmp(ZT("w:SelectorSet"), e.data))
        {
            /* Allocate an instance */
            if (!*dynamicInstanceParams)
            {
                MI_Result r;
                const ZChar* cn;

                if (!classname)
                {
                    XML_Raise(xml, ZT("ResourceURI tag expected"));
                    RETURN(-1);
                }

                cn = Batch_Zdup(dynamicBatch, classname);
                if (!cn)
                {
                    XML_Raise(xml, ZT("Out of memory"));
                    RETURN(-1);
                }

                r = Instance_NewDynamic(dynamicInstanceParams, cn, MI_FLAG_CLASS, dynamicBatch);
                if (MI_RESULT_OK != r)
                    RETURN(-1);
            }

            /* iterate through all selector tags */
            for (;;)
            {
                const ZChar* ns = NULL;
                _Analysis_assume_(classname);
                if (_GetSelector(
                    xml,
                    &e,
                    &ns,
                    &classname,
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
        if (0 != Zcmp(ZT("a:ReferenceParameters"), e.data))
        {
            if (XML_Skip(xml) != 0)
                RETURN(-1);

            if (XML_Next(xml, &e) != 0)
                RETURN(-1);

            if (e.type == XML_END)
                break;

            continue;
        }

        if (0 != _GetReferenceParameters(xml, dynamicBatch, dynamicInstanceParams))
            RETURN(-1);

        if (XML_Next(xml, &e) != 0)
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
    const ZChar* propNameChar,
    MI_Value* value,
    MI_Type* type,
    MI_Boolean* null)
{
    XML_Elem e;

    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if (e.type == XML_END)
    {
        if (Zcmp(propNameChar, e.data) != 0)
        {
            LOGE((ZT("open/close mismatch: {%Z}{%Z}"),
                zcs(propNameChar), zcs(e.data)));
            RETURN(-1);
        }

        /* Check whether this attribute is null or just empty */
        {
            const ZChar* p = XML_Elem_GetAttr(&e, ZT("xsi:nil"));

            if (p && Zcmp(p, ZT("true")) == 0)
            {
                *null = MI_TRUE;
            }
            else
            {
                *null = MI_FALSE;
                *type = MI_STRING;
                value->string = ZT("");
            }
        }

        return 0;
    }
    else if (e.type == XML_CHARS)
    {
        /* Plain string property */
        value->string = Batch_Zdup(dynamicBatch, e.data);
        if (!value->string)
            RETURN(-1);
        *type = MI_STRING;

        if (XML_Expect(xml, &e, XML_END, propNameChar) != 0)
            RETURN(-1);

        *null = MI_FALSE;
        return 0;
    }
    else if ('a' == e.data[0])
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
            if (Zcasecmp(e.data, ZT("CIM_DateTime")) == 0)
            {
                /* DateTime property XML*/
                /* <p0:datetimeProperty xsi:type="cim:cimDateTime"> */
                /*     <CIM_DateTime>19990929195959.000000-420</CIM_DateTime> */
                /* </p0:datetimeProperty> */
                if (XML_Next(xml, &e) != 0)
                    RETURN(-1);

                if (e.type == XML_CHARS)
                {
                    value->string = Batch_Zdup(dynamicBatch, e.data);
                    if (!value->string)
                        RETURN(-1);
                    *type = MI_STRING;
                }
                else
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, ZT("CIM_DateTime")) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, propNameChar) != 0)
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
    const ZChar* propNameA = 0;
    MI_Value valueA;
    MI_Type typeA = MI_BOOLEAN;
    const ZChar* propNamePrev = 0;
    MI_Value valuePrev;
    MI_Type typePrev = MI_BOOLEAN;

    memset(&valueA, 0, sizeof(valueA));

    /* extract all parameters */
    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        /* Look for closing instance element */

        if (e.type == XML_END && Zcmp(e.data, start->data) == 0)
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
            ZChar* cn;

            // We are trying to parse an Instance, The type of the instance may be specified
            // as a attribute Type or it is same as the element name. We'll attempt to get the
            // type from attribute ... if not we'll use the element name.
            // TODO: At this time we don't have the NS support in the XML parser, so using hardcoded
            // 'xsi:type (good for windows client) once we get the NS support this code should be
            // updated.
            const ZChar* typeName = XML_Elem_GetAttr(start, ZT("xsi:type"));

            if(typeName)
            {
                ZChar* typeStart;
                cn = Batch_Zdup(dynamicBatch, _TrimNS(typeName));

                if (!cn)
                {
                    LOGD((ZT("Batch_Zdup() failed: out of memory")));
                    RETURN(-1);
                }

                // Trim the _Type from the name.
                typeStart = Zrchr(cn, '_');
				
                if (typeStart == NULL)
                {
                    LOGD((ZT("The value of xsi:type is \"%Z\" and it should contain \"_\"."), zcs(cn)));
                    RETURN(-1);
                }

                *typeStart = ZT('\0');
            }
            else
            {
                cn = Batch_Zdup(dynamicBatch, _TrimNS(start->data));
                if (!cn)
                {
                    LOGD((ZT("Batch_Zdup() failed: out of memory")));
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
        if (e.size > 2) /* ?:<name> */
        {
            MI_Result r;
            MI_Value value;
            MI_Type type = MI_BOOLEAN;
            const ZChar* propNameChar;
            const ZChar* propName;
            MI_Boolean null;

            propNameChar = e.data;

            /* Position propName one beyond ':' character */
            propName = Batch_Zdup(dynamicBatch, _TrimNS(propNameChar));

            if (!propName)
            {
                LOGD((ZT("Batch_Zdup() failed: out of memory")));
                RETURN(-1);
            }

            type = MI_BOOLEAN;

            if (_GetSingleProperty(
                xml,
                &e,
                dynamicBatch,
                propNameChar,
                &value,
                &type,
                &null) != 0)
            {
                LOGD((ZT("_GetSingleProperty() failed: %Z"),
                    zcs(propNameChar)));
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
                if (0 == Zcmp(propNameA, propName))
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
                if (0 == Zcmp(propNamePrev, propName))
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
    if (Zcmp(e.data, start->data) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseWSHeader(
    XML* xml,
    WSMAN_WSHeader* wsheader)
{
    XML_Elem e;

    memset(wsheader, 0, sizeof(WSMAN_WSHeader));

    /* Expect <s:Header> */
    if (XML_Expect(xml, &e, XML_START, ZT("s:Header")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)// && strcmp(e.data, "s:Header") == 0)
        {
            int tag = HashStr(e.data, e.size);

            if (WSMANTAG_HEADER != tag)
            {
                LOGW((ZT("wsman: unexpected close tag [%Z] in incoming xml"),
                    zcs(e.data)));
                RETURN(-1);
            }
            //printf("DONE\n");
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data, e.size))
        {
            case WSMANTAG_TO:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, ZT("a:To")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_RESOURCE_URI:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsheader->rqtClassname = Zrchr(e.data, '/');
                /* skip '/' */
                if (wsheader->rqtClassname)
                    wsheader->rqtClassname++;

                if (XML_Expect(xml, &e, XML_END, ZT("w:ResourceURI")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_REPLY_TO:
            {
                if (XML_Expect(xml, &e, XML_START, ZT("a:Address")) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, ZT("a:Address")) != 0)
                    RETURN(-1);

                if (XML_Expect(xml, &e, XML_END, ZT("a:ReplyTo")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_ACTION:
            {
                wsheader->foundAction = MI_TRUE;

                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsheader->rqtAction = HashStr(e.data, e.size);

                if (0 == wsheader->rqtAction)
                {
                    ZChar* s;
                    /* DSP0226; 9: Custom Actions (Methods) just need to have unique URI.
                        We are assuming it has format like http://<server>/wbem/wscim/1/cim-schema/2/<class-name>/<method-name> */

                    if (0 != Zncmp(e.data, ZT("http://"), 7))
                        RETURN(-1);

                    wsheader->rqtServer = e.data + 7;

                    s = Zchr(wsheader->rqtServer, '/');

                    if (!s)
                        RETURN(-1);

                    *s = 0;
                    s++;

                    if (0 != Zncmp(s, ZT("wbem/wscim/1/cim-schema/2/"), 26))
                        RETURN(-1);

                    s += 26;

                    wsheader->rqtClassname = s;
                    s = Zchr(s, '/');

                    if (!s)
                        RETURN(-1);

                    *s = 0;
                    s++;
                    wsheader->rqtMethod = s;
                }

                if (XML_Expect(xml, &e, XML_END, ZT("a:Action")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_SELECTOR_SET:
            {
                if (_GetSelectorSet(xml, wsheader) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_MESSAGE_ID:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsheader->rqtMessageID = e.data;

                if (XML_Expect(xml, &e, XML_END, ZT("a:MessageID")) != 0)
                    RETURN(-1);
            }
            break;

            case WSMANTAG_MAX_ENVELOPE_SIZE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsheader->maxEnvelopeSize = (MI_Uint32)Ztoull(
                    e.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, ZT("w:MaxEnvelopeSize")) != 0)
                    RETURN(-1);
            }
            break;

            default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    wsheader->unknownMandatoryTag = e.data;
                    LOGW((ZT("wsman: unknown mandatory tag [%Z]; aborted"),
                        zcs(e.data)));
                    /* validate header will send correct repsonse to the client */
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }
    return 0;
}

int WS_ParseSoapEnvelope(XML* xml)
{
    XML_Elem e;

    /* Ignore the processing instruction (if any) */
    {
        if (XML_Next(xml, &e) != 0)
        {
            XML_Raise(xml, ZT("missing root element"));
            RETURN(-1);
        }

        if (e.type != XML_INSTRUCTION)
        {
            if (XML_PutBack(xml, &e) != 0)
                RETURN(-1);
        }
    }

    /* Expect <s:Envelope> */
    if (XML_Expect(xml, &e, XML_START, ZT("s:Envelope")) != 0)
        RETURN(-1);

    return 0;
}

static const ZChar* _ExpectCharsAndEnd(
    XML* xml,
    const ZChar* name)
{
    XML_Elem e;
    const ZChar* chars;

    if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
        return NULL;

    chars = e.data;

    if (XML_Expect(xml, &e, XML_END, name) != 0)
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

        if (Zcmp(e.data, ZT("a:ReferenceParameters")) == 0)
        {
            if (_GetReferenceParameters(
                xml,
                batch,
                &filter->referenceParameters) != 0)
            {
                RETURN(-1);
            }
        }
        else if (Zcmp(e.data, ZT("a:Address")) == 0)
        {
            filter->address = _ExpectCharsAndEnd(xml, ZT("a:Address"));

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

    if (XML_Expect(xml, &e, XML_END, ZT("b:Object")) != 0)
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

    if (Zcmp(e.data, ZT("b:AssociatedInstances")) == 0)
    {
        filter->isAssosiatorOperation = MI_TRUE;
    }
    else if (Zcmp(e.data, ZT("b:AssociationInstances")) == 0)
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

        if (Zcmp(e.data, ZT("b:Object")) == 0)
        {
            if (_ParseAssociationFilterObject(xml, batch, filter) != 0)
                RETURN(-1);
        }
        else if (Zcmp(e.data, ZT("b:AssociationClassName")) == 0)
        {
            filter->associationClassName = _ExpectCharsAndEnd(
                xml, ZT("b:AssociationClassName"));

            if (!filter->associationClassName)
                RETURN(-1);
        }
        else if (Zcmp(e.data, ZT("b:Role")) == 0)
        {
            filter->role = _ExpectCharsAndEnd(xml, ZT("b:Role"));

            if (!filter->role)
                RETURN(-1);
        }
        else if (Zcmp(e.data, ZT("b:ResultClassName")) == 0)
        {
            filter->resultClassName = _ExpectCharsAndEnd(
                xml,
                ZT("b:ResultClassName"));

            if (!filter->resultClassName)
                RETURN(-1);
        }
        else if (Zcmp(e.data, ZT("b:ResultRole")) == 0)
        {
            filter->resultRole = _ExpectCharsAndEnd(
                xml,
                ZT("b:ResultRole"));

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
        if (XML_Expect(xml, &e, XML_END, ZT("b:AssociatedInstances")) != 0)
            RETURN(-1);
    }
    else
    {
        /* Expect </AssociationInstances> */
        if (XML_Expect(xml, &e, XML_END, ZT("b:AssociationInstances")) != 0)
            RETURN(-1);
    }

    return 0;
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
    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect <n:Enumerate> */
    if (XML_Expect(xml, &e, XML_START, ZT("n:Enumerate")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data, e.size);

            if (WSMANTAG_ENUM_ENUMERATE != tag)
            {
                LOGW((ZT("wsman: unexpected close tag [%Z] in incoming xml"),
                    zcs(e.data)));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data, e.size))
        {
        case WSMANTAG_ENUM_MAX_ELEMENTS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumbody->maxElements = (MI_Uint32)Ztoull(e.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, ZT("w:MaxElements")) != 0)
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
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumbody->polymorphismMode = HashStr(e.data, e.size);

                if (XML_Expect(xml, &e, XML_END, ZT("b:PolymorphismMode")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_ENUM_MODE:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumbody->enumerationMode = HashStr(e.data, e.size);

                if (XML_Expect(xml, &e, XML_END, ZT("w:EnumerationMode")) != 0)
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
                const ZChar* dialect;
                const ZChar* p;

                /* Get 'Dialect' attribute? */
                dialect = XML_Elem_GetAttr(&e, ZT("Dialect"));
                if (!dialect)
                {
                    LOGW((ZT("wsman: Filter tag missing Dialect attribute")));
                    RETURN(-1);
                }


                /* Reduce long dialect name to final component of path */
                p = Zrchr(dialect, '/');
                if (p)
                    wsenumbody->dialect = p + 1;
                else
                    wsenumbody->dialect = dialect;

                /* Parse the association filter */
                if (Zcmp(dialect, URI_CIMBINDING ZT("/associationFilter")) == 0)
                {
                    wsenumbody->foundAssociationOperation = MI_TRUE;

                    if (_ParseAssociationFilter(xml, *batch,
                        &wsenumbody->associationFilter) != 0)
                    {
                        RETURN(-1);
                    }
                }
                else
                {
                    /* Get the filter text */
                    if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                        RETURN(-1);

                    wsenumbody->filter = e.data;
                }

                /* Check for closing </w:Filter> tag */
                if (XML_Expect(xml, &e, XML_END, ZT("w:Filter")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    LOGW((ZT("wsman: unknown mandatory tag [%Z]; aborted"),
                        zcs(e.data)));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
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
    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
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
    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
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
    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect <?:?> parameter's tag */
    if (XML_Next(xml, &e) != 0)
        RETURN(-1);

    if (0 != _GetInstance(xml, &e, dynamicBatch, dynamicInstanceParams))
        RETURN(-1);

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
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
    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect <n:Enumerate> */
    if (XML_Expect(xml, &e, XML_START, ZT("n:Pull")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data, e.size);

            if (WSMANTAG_ENUM_PULL != tag)
            {
                LOGW((ZT("wsman: unexpected close tag [%Z] in incoming xml"),
                    zcs(e.data)));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data, e.size))
        {
        case WSMANTAG_PULL_MAX_ELEMENTS:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->maxElements = (MI_Uint32)Ztoull(e.data, NULL, 10);
                if (XML_Expect(xml, &e, XML_END, ZT("n:MaxElements")) != 0)
                    RETURN(-1);
            }
            break;

        case WSMANTAG_PULL_ENUMERATION_CONTEXT:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->enumerationContextID = (MI_Uint32)Ztoull(
                    e.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, ZT("n:EnumerationContext")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    LOGW((ZT("wsman: unknown mandatory tag [%Z]; aborted"),
                        zcs(e.data)));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
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
    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect <n:Release> */
    if (XML_Expect(xml, &e, XML_START, ZT("n:Release")) != 0)
        RETURN(-1);

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            RETURN(-1);

        if (e.type == XML_END)
        {
            int tag = HashStr(e.data, e.size);

            if (WSMANTAG_ENUM_RELEASE != tag)
            {
                LOGW((ZT("wsman: unexpected close tag [%Z] in incoming xml"),
                    zcs(e.data)));
                RETURN(-1);
            }
            break;
        }

        /* skip possible comments */
        if (e.type != XML_START)
            continue;

        switch (HashStr(e.data, e.size))
        {
        case WSMANTAG_PULL_ENUMERATION_CONTEXT:
            {
                if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                    RETURN(-1);

                wsenumpullbody->enumerationContextID = (MI_Uint32)Ztoull(
                    e.data, NULL, 10);

                if (XML_Expect(xml, &e, XML_END, ZT("n:EnumerationContext")) != 0)
                    RETURN(-1);
            }
            break;

        default:
            {
                if (_MustUnderstandCanBeIgnored(&e) != 0)
                {
                    LOGW((ZT("wsman: unknown mandatory tag [%Z]; aborted"),
                        zcs(e.data)));
                    RETURN(-1);
                }

                if (XML_Skip(xml) != 0)
                    RETURN(-1);
            }
            break;

        }
    }

    /* Expect <s:Body> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
        RETURN(-1);

    return 0;
}

int WS_ParseIdentifyBody(
    XML* xml)
{
    XML_Elem e;

    if (XML_Expect(xml, &e, XML_START, ZT("s:Body")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_START, ZT("i:Identify")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, ZT("i:Identify")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, ZT("s:Body")) != 0)
        RETURN(-1);

    if (XML_Expect(xml, &e, XML_END, ZT("s:Envelope")) != 0)
        RETURN(-1);

    return 0;
}
