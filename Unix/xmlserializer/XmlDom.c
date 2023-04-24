/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include <MI.h>
#include <base/batch.h>
#include <xml/xml.h>
#include "XmlDom.h"
#include <omi_error/OMI_Error.h>
#include <omi_error/omierror.h>

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:28196)
#endif

MI_Result XMLDOM_Parse(_In_z_ MI_Char *xmlString, _Outptr_result_z_ MI_Char **endOfXml, _Outptr_ XMLDOM_Doc **xmlDoc, _Outptr_opt_result_maybenull_ MI_Instance **errorObject)
{
    XML *xml = NULL;
    XML_Elem e;
    int r = 1;
    MI_Result miResult;
    size_t i;
    XMLDOM_Elem *parentElement = NULL;
    XMLDOM_Elem *currentElement = NULL;
    size_t currentEDepth = 0;
    Batch* finalBatch;
    MI_Char *errorString = NULL;

    *endOfXml = NULL;

    if (errorObject)
        *errorObject = NULL;

    //Allocate batch from start of batch
    {
        Batch batch = BATCH_INITIALIZER;
        batch.maxPages = (size_t) -1; //Unlimit the number of pages as it could use a lot

        finalBatch = (Batch*)Batch_Get(&batch, sizeof(Batch));

        if (!finalBatch)
        {
            Batch_Destroy(&batch);
            *xmlDoc = NULL;
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }

        //Copy stack-version of batch over allocated batch
        memcpy(finalBatch, &batch, sizeof(Batch));
    }

    //Allocate XML Doc right after batch so we can always get back to
    //batch from doc by subtracting sizeof(OAC_Batch) from doc pointer
    *xmlDoc = (XMLDOM_Doc*)Batch_Get(finalBatch, sizeof(XMLDOM_Doc));
    if (*xmlDoc == NULL)
    {
        miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }


    //Initialize doc
    memset(*xmlDoc, 0, sizeof(**xmlDoc));

    //This is temporary for this function so don't add it to batch
    xml = (XML*)malloc(sizeof(*xml));
    if (xml == NULL)
    {
        miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }

    memset(xml, 0, sizeof(*xml));
    XML_Init(xml);
    XML_SetText(xml, xmlString);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        switch(e.type)
        {
        case (XML_NONE):
            break;
        case (XML_START):
        {
            //create child element and add all attributes
            XMLDOM_Elem *tmpE = (XMLDOM_Elem*) Batch_Get(finalBatch, sizeof(XMLDOM_Elem));
            if (tmpE == NULL)
            {
                miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto cleanup;
            }
            memset(tmpE, 0, sizeof(XMLDOM_Elem));
            tmpE->name = e.data.data;
            tmpE->nameLength = e.data.size;
            tmpE->namespaceUri = e.data.namespaceUri;
            tmpE->namespaceUriLength = e.data.namespaceUriSize;
            tmpE->namespaceId = e.data.namespaceId;

            tmpE->parent = currentElement;
            parentElement = currentElement;
            currentElement = tmpE;
            currentEDepth++;

            //wprintf(L"<%s> (level %I64u, size %I64u)\n", currentElement->name, currentEDepth, e.size);

            if (parentElement == NULL)
            {
                //This is the root node.  XML parser will not allow multiple root nodes
                (*xmlDoc)->root = tmpE;
            }
            else if (parentElement->child_first == NULL)
            {
                //first child
                parentElement->child_first = tmpE;
                parentElement->child_last = tmpE;
            }
            else
            {
                //put at end of list
                parentElement->child_last->sibling_next = tmpE;
                parentElement->child_last = tmpE;
            }
            if (e.attrsSize)
            {
                for (i = 0; i < e.attrsSize; i++)
                {
                    const XML_Attr* attr = &e.attrs[i];
                    XMLDOM_Attr *tmpAttrib = (XMLDOM_Attr*) Batch_Get(finalBatch, sizeof(XMLDOM_Attr));
                    if (tmpAttrib == NULL)
                    {
                        miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                        goto cleanup;
                    }
                    tmpAttrib->name = attr->name.data;
                    tmpAttrib->nameLength = attr->name.size;
                    tmpAttrib->value = attr->value;
                    tmpAttrib->valueLength = attr->valueSize;
                    tmpAttrib->namespaceUri = attr->name.namespaceUri;
                    tmpAttrib->namespaceUriLength = attr->name.namespaceUriSize;
                    tmpAttrib->namespaceId = attr->name.namespaceId;

                    tmpAttrib->next = NULL;
                    if (currentElement->attr_last)
                        currentElement->attr_last->next = tmpAttrib;
                    if (currentElement->attr_first == NULL)
                        currentElement->attr_first = tmpAttrib;
                    currentElement->attr_last = tmpAttrib;
                }
            }
            break;
        }
        case (XML_END):
            //wprintf(L"</%s> (level %I64d)\n", currentElement->name, currentEDepth);

            //more to parent node
            if (parentElement)
            {
                parentElement = parentElement->parent;
            }
            if (currentElement)
                currentElement = currentElement->parent;
            currentEDepth--;
            break;
        case (XML_INSTRUCTION):
            //Add attribute to document
            for (i = 0; i < e.attrsSize; i++)
            {
                const XML_Attr* attr = &e.attrs[i];
                XMLDOM_Attr *tmpAttrib = (XMLDOM_Attr*) Batch_Get(finalBatch, sizeof(XMLDOM_Attr));
                if (tmpAttrib == NULL)
                {
                    miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    goto cleanup;
                }
                tmpAttrib->name = attr->name.data;
                tmpAttrib->nameLength = attr->name.size;
                tmpAttrib->value = attr->value;
                tmpAttrib->valueLength = attr->valueSize;
                if ((*xmlDoc)->instructions_last)
                    (*xmlDoc)->instructions_last->next = tmpAttrib;
                if ((*xmlDoc)->instructions_first == NULL)
                    (*xmlDoc)->instructions_first = tmpAttrib;
            }
            break;
        case (XML_CHARS):
        {
            //Add value to current element
            XMLDOM_ElemValue *tmpValue = (XMLDOM_ElemValue*) Batch_Get(finalBatch, sizeof(XMLDOM_ElemValue));
            if (tmpValue == NULL)
            {
                miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto cleanup;
            }
            tmpValue->value = e.data.data;
            tmpValue->valueLength = e.data.size;
            tmpValue->next = NULL;

            if (currentElement)
            {
                if (currentElement->value_last)
                {
                    currentElement->value_last->next = tmpValue;
                }
            
                currentElement->value_last = tmpValue;

                if (currentElement->value_first == NULL)
                {
                    //first value
                    currentElement->value_first = tmpValue;
                }
            }
            break;
        }
        case (XML_COMMENT):
            //Ignore
            break;
        }

    }
    if (r != 1)
    {
        miResult = MI_RESULT_FAILED;
        errorString = xml->message;
    }
    else
    {
        miResult = MI_RESULT_OK;
    }

cleanup:
    if (miResult == MI_RESULT_OK)
    {
        //If we succeeded update the out pointer to the location where
        //we parsed to
        *endOfXml = (xmlString + (xml->ptr - xml->text));
    }
    else if (errorObject)
    {
        OMI_Error *omiErr;
        if (OMI_ErrorFromErrorCode(NULL, miResult, MI_RESULT_TYPE_MI, errorString, &omiErr) != MI_RESULT_OK)
        {
            //TSASSERT(0, L"This only fails in out of memory and we are ignoring this particular error on purpose.", TLINE);
        }
        else
        {
            if (omiErr)
                *errorObject = &omiErr->__instance;
        }

    }

    free(xml);

    if (r != 1)
    {
        Batch_Destroy(finalBatch);
        *xmlDoc = NULL;
    }

    return miResult;
}
#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

void XMLDOM_Free(_Inout_ XMLDOM_Doc *xmlDoc)
{
    char *buffer = (char*) xmlDoc;
    Batch* batch;
    
    int size8 = (sizeof(Batch) + 7) & ~7; /* Round request size to a multiple of eight... batch allocator does this */

    if (xmlDoc == NULL)
        return;

    batch = (Batch*)(buffer - size8);
    Batch_Destroy(batch);
}
