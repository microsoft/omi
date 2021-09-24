/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */


#include <MI.h>
#include <base/class.h>
#include <base/instance.h>
#include <base/helpers.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <omi_error/OMI_Error.h>
#include <omi_error/omierror.h>
#include <base/naming.h>
#include "XmlDom.h"
#include "xmldeserializer.h"
#include "xmldeserializer_ids.h"

//*****************************************max namespace length******************
// After discussion with George we agreed to put a max limit of 1024 on namespace
#define NAMESPACE_LIMIT 1024

typedef struct _NameSpaceBufferData
{
    MI_Char * pNamespaceBuffer;
    void * pNext;
}NameSpaceBufferData;

typedef struct _DeserializationData
{
    enum { DeserializingClass, DeserializingInstance } type;

    //Call-out to get classes from client
    MI_Deserializer_ClassObjectNeeded clientGetClassCallback;
    void *clientGetClassCallbackContext;

    //Error object details
    MI_Instance **errorObject;

    //Namespace buffer
    NameSpaceBufferData * pCurrentNamespaceBufferData;

    union
    {
        struct _classData
        {
            MI_Class *classParent;
            MI_Class *classResult;
            const MI_Char *className;
            const MI_Char *namespaceName;
            const MI_Char *serverName;
            MI_Boolean includePropertiesFromAllOrigins;
            MI_Boolean includeUnknownOrigins;
        } classData;
        struct _instanceData
        {
            //When encoding class/instance, this is what XmlDeserializer_GetInstanceClass needs
            XMLDOM_Elem *declgroupElement;

            //Client passed in client list and count
            MI_Class **classObjects;
            MI_Uint32 numberClassObjects;

            //Main instance class (not for embedded)
            MI_Class *instanceClass;

            //Main instance (not for embedded)
            MI_Instance *instanceResult;

            //Top-level namespace and server name for instances that encode classes in same document
            const MI_Char *namespaceName;
            const MI_Char *serverName;

            //Classes that need deleting when we are done
            MI_Class *foundClasses[50];
            MI_Uint32 foundClassesCount;
        } instanceData;
    } u ;
} DeserializationData;

_Check_return_ static MI_Result _StringToMiBool(_In_z_ const MI_Char *string, _Out_ MI_Boolean *boolValue);
_Check_return_ static MI_Result _StringToMiType(_In_z_ const MI_Char *string, _Out_ MI_Type *type);
_Check_return_ static MI_Result _StringToMiValue(_In_opt_ const DeserializationData *state, _In_z_ const MI_Char *str, MI_Type type, _Out_ MI_Value *value);

//Deserialize a class or instance
_Check_return_ MI_Result XmlDeserializer_DoDeserializeClass(_In_ const XMLDOM_Elem *classNode, MI_Uint32 flags, _In_opt_ const MI_Class *parentClass, _In_opt_z_ const MI_Char *namespaceName, _In_opt_z_ const MI_Char *serverName, _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded, _In_opt_ void *classObjectNeededContext, _Outptr_ MI_Class **resultClass, _Outptr_opt_result_maybenull_ MI_Instance **errorObject);
_Check_return_ static MI_Result XmlDeserializer_DoDeserialization(_Inout_ DeserializationData *state, MI_Uint32 flags, _In_ const XMLDOM_Elem *elementNode);
_Check_return_ MI_Result XmlDeserializer_GetInstanceClass(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *firstElement, MI_Uint32 flags, _In_z_ const MI_Char *instanceClassName, _In_opt_z_ const MI_Char *namespaceName, _In_opt_z_ const MI_Char *serverName, _Outptr_ MI_Class **resultClass);
MI_Result MI_CALL XmlDeserializer_DoDeserializeInstance(_Inout_ DeserializationData *stateData, XMLDOM_Elem *instanceElement);

//Class specific deserializer functions
_Check_return_ MI_Result XmlDeserializer_AddClassQualifier(_In_ const DeserializationData *state, _Inout_ MI_Class *classObject, _In_ const XMLDOM_Elem *qualifierElem);
_Check_return_ MI_Result XmlDeserializer_AddClassMethod(_In_ const DeserializationData *state, _Inout_ MI_Class *classObject, _In_ const XMLDOM_Elem *methodElem);

//Class and instance deserializer functions
_Check_return_ MI_Result XmlDeserializer_AddProperty(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyElem);
_Check_return_ MI_Result XmlDeserializer_AddPropertyArray(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyArrayElem);
_Check_return_ MI_Result XmlDeserializer_AddPropertyReference(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyRefElem);

_Check_return_ static MI_Result _Extract_NAMESPACEPATH(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *namespacePathElem, _Outptr_result_z_ const MI_Char **serverName, _Outptr_result_z_ const MI_Char **namespacePath);
_Check_return_ static MI_Result _Extract_LOCALNAMESPACEPATH(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *localNamespacePathElem, _Outptr_result_z_ const MI_Char **namespacePath);

_Check_return_ static MI_Result _Extract_INSTANCEPATH(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *refChildElem, _Outptr_ MI_Instance **instanceRef);
_Check_return_ static MI_Result _Extract_LOCALINSTANCEPATH(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *refChildElem, _Outptr_ MI_Instance **instanceRef);
_Check_return_ static MI_Result _Extract_INSTANCENAME(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *instanceNameElem,_In_opt_z_ const MI_Char *serverName,_In_opt_z_ const MI_Char *namespaceName,_Outptr_ MI_Instance **refInstance);
_Check_return_ static MI_Result _Extract_VALUE_REFERENCE(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *valueRefElement,_In_opt_z_ const MI_Char *serverName,_In_opt_z_ const MI_Char *namespaceName,_Outptr_ MI_Instance **instanceRef);
_Check_return_ MI_Result XmlDeserializer_GetDerivationParentClass(MI_Uint32 flags,_In_z_ const MI_Char *className, _In_z_ MI_Char *remainingDerivationNameList, _In_z_ const MI_Char *namespaceName, _In_z_ const MI_Char *serverName, _In_ const XMLDOM_Elem *classNode, _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded, _In_opt_ void *classObjectNeededContext, _Outptr_ MI_Class **classObject);
void _ExtractNextTokenFromDerivationString(_In_z_ MI_Char *derivationStringList, _Outptr_result_z_ MI_Char **derivationToken, _Outptr_result_z_ MI_Char **remainingDerivationStringList);

_Success_(1) _Post_equal_to_(miResult)
static MI_Result _CreateErrorObject(MI_Instance **errorObject, MI_Result miResult, const MI_Char *errorString, ...);

void FreeNamespaceBuffer(_In_ DeserializationData *state);

MI_Result MI_CALL XmlDeserializer_Create(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer)
{
    if ((application == NULL) || (flags != 0) || (format == NULL) || (deserializer == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (Tcscmp(format, PAL_T("MI_XML")) != 0) //TODO: Case sensitive?
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
    memset(deserializer, 0, sizeof(*deserializer));

    return MI_RESULT_OK;
}

MI_Result MI_CALL XmlDeserializer_Close(
    _Inout_ MI_Deserializer *deserializer)
{
    return MI_RESULT_OK;
}

MI_Result MI_CALL XmlDeserializer_DeserializeClass(
    _Inout_ MI_Deserializer *deserializer, 
    MI_Uint32 flags, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength,
    _In_opt_ MI_Class *parentClass, 
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_opt_result_maybenull_ MI_Class **classObject,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    XMLDOM_Doc *xmldoc = NULL;
    MI_Uint8 *docCopy = NULL;
    MI_Char *endXmlDoc = NULL;
    MI_Result result = MI_RESULT_OK;

    if (classObject)
    {
        *classObject = NULL;
    }
    if (cimErrorDetails)
    {
        *cimErrorDetails = NULL;
    }
    if ((deserializer == NULL) || (flags != 0) || (serializedBuffer == NULL) || (classObject == NULL))
    {
        result = MI_RESULT_INVALID_PARAMETER;
        goto cleanup;
    }
    
    /* TODO: We do not always need to copy the buffer */
    /* We are going to make sure this buffer is null terminated by pushing
     * 3 extra NULL chars on the end.  3 handles non-wchar aligned last
     * character
     */
    docCopy = (MI_Uint8*) malloc(serializedBufferLength+3);
    if (docCopy == NULL)
    {
        result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }
    memcpy(docCopy, serializedBuffer, serializedBufferLength);
    docCopy[serializedBufferLength] = 0;
    docCopy[serializedBufferLength+1] = 0;
    docCopy[serializedBufferLength+2] = 0;

    result = XMLDOM_Parse((MI_Char*)docCopy, &endXmlDoc, &xmldoc, cimErrorDetails);
    if (result != MI_RESULT_OK)
    {
        goto cleanup;
    }
    
    if ((xmldoc->root == NULL) ||
        (Tcscmp(xmldoc->root->name, PAL_T("CLASS")) != 0))
    {
        result = MI_RESULT_INVALID_PARAMETER;
        goto cleanup;
    }

    result = XmlDeserializer_DoDeserializeClass(xmldoc->root, flags, parentClass, namespaceName, serverName, classObjectNeeded, classObjectNeededContext, classObject, cimErrorDetails);

cleanup:
    if ((result == MI_RESULT_OK) &&
        serializedBufferRead)
    {
        *serializedBufferRead = (MI_Uint32)((endXmlDoc - ((MI_Char*)docCopy))*sizeof(MI_Char));
    }
    //Cleanup memory
    if (xmldoc)
    {
        XMLDOM_Free(xmldoc);
    }

    if (docCopy)
    {
        free(docCopy);
    }

    //If we have not created an error object then create a default one
    if (cimErrorDetails && !*cimErrorDetails && (result != MI_RESULT_OK))
    {
        OMI_Error *omiErr;
        if (OMI_ErrorFromErrorCode(NULL, result, MI_RESULT_TYPE_MI, NULL, &omiErr) != MI_RESULT_OK)
        {
            //TSASSERT(0, PAL_T("This only fails in out of memory and we are ignoring this particular error on purpose."), TLINE);
        }
        else
        {
            if (omiErr)
                *cimErrorDetails = &omiErr->__instance;
        }
    }


    return result;
}


MI_Result MI_CALL XmlDeserializer_Class_GetClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}


MI_Result MI_CALL XmlDeserializer_Class_GetParentClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*parentClassNameLength) MI_Char *parentClassName,
    _Inout_ MI_Uint32 *parentClassNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}

MI_Result MI_CALL XmlDeserializer_DeserializeInstance(
    _Inout_ MI_Deserializer *deserializer, 
    MI_Uint32 flags, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _In_reads_opt_(numberClassObjects) MI_Class **classObjects, 
    MI_Uint32 numberClassObjects,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_opt_result_maybenull_ MI_Instance **instanceObject,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Uint8 *docCopy = NULL;
    MI_Result result = MI_RESULT_OK;
    DeserializationData stateData;
    XMLDOM_Elem *instanceElement = NULL;
    XMLDOM_Doc *xmldoc = NULL;
    MI_Char *xmlEndPtr = NULL;

    memset(&stateData, 0, sizeof(stateData));
    stateData.type = DeserializingInstance;
    stateData.errorObject = cimErrorDetails;
    stateData.clientGetClassCallback = classObjectNeeded;
    stateData.clientGetClassCallbackContext = classObjectNeededContext;
    stateData.u.instanceData.classObjects = classObjects;
    stateData.u.instanceData.numberClassObjects = numberClassObjects;

    if (instanceObject)
    {
        *instanceObject = NULL;
    }
    if (cimErrorDetails)
    {
        *cimErrorDetails = NULL;
    }
    if ((deserializer == NULL) || (flags != 0) || (serializedBuffer == NULL) || (instanceObject == NULL))
    {
        result = MI_RESULT_INVALID_PARAMETER;
        goto cleanup;
    }
    
    /* TODO: We do not always need to copy the buffer */
    /* We are going to make sure this buffer is null terminated by pushing
     * 3 extra NULL chars on the end.  3 handles non-wchar aligned last
     * character
     */
    docCopy = (MI_Uint8*) malloc(serializedBufferLength+3);
    if (docCopy == NULL)
    {
        result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }
    memcpy(docCopy, serializedBuffer, serializedBufferLength);
    docCopy[serializedBufferLength] = 0;
    docCopy[serializedBufferLength+1] = 0;
    docCopy[serializedBufferLength+2] = 0;

    /* TODO: We seriously need a way of getting the error back! */
    result = XMLDOM_Parse((MI_Char*)docCopy, &xmlEndPtr, &xmldoc, cimErrorDetails);
    if (result != MI_RESULT_OK)
    {
        goto cleanup;
    }
    
    if (xmldoc->root == NULL)
    {
        result = MI_RESULT_INVALID_PARAMETER;
        goto cleanup;
    }
    
    //Find the instance element, in case we have classes encoded with the instance
    instanceElement = xmldoc->root;
    //Is it just a simple instance?
    if (Tcscmp(xmldoc->root->name, PAL_T("INSTANCE")) != 0)
    {
        //Then maybe it is a CIM document?
        if ((Tcscmp(xmldoc->root->name, PAL_T("CIM")) == 0) &&
            xmldoc->root->child_first &&
            xmldoc->root->child_first->name &&
            (Tcscmp(xmldoc->root->child_first->name, PAL_T("DECLARATION")) == 0) &&
            xmldoc->root->child_first->child_first &&
            xmldoc->root->child_first->child_first->name &&
            (Tcscmp(xmldoc->root->child_first->child_first->name, PAL_T("DECLGROUP")) == 0))
        {
            //OK, so far so good, next we need to dig through the VALUE.OBJECT entries for an instance
            XMLDOM_Elem *objectElements = xmldoc->root->child_first->child_first->child_first;

            stateData.u.instanceData.declgroupElement = xmldoc->root->child_first->child_first;

            while (objectElements)
            {
                if (Tcscmp(objectElements->name, PAL_T("NAMESPACEPATH"))==0)
                {
                    //Extract the namespace and server from this node
                    result = _Extract_NAMESPACEPATH(&stateData, objectElements, &stateData.u.instanceData.serverName, &stateData.u.instanceData.namespaceName);
                    if (result != MI_RESULT_OK)
                        goto cleanup;
                }
                else if (Tcscmp(objectElements->name, PAL_T("LOCALNAMESPACEPATH"))==0)
                {
                    //Extract the namespace and server from this node
                    result = _Extract_LOCALNAMESPACEPATH(&stateData, objectElements, &stateData.u.instanceData.namespaceName);
                    if (result != MI_RESULT_OK)
                        goto cleanup;
                }
                else if ((Tcscmp(objectElements->name, PAL_T("VALUE.OBJECT"))==0) &&
                    objectElements->child_first &&
                    (Tcscmp(objectElements->child_first->name, PAL_T("INSTANCE")) == 0))
                {
                    instanceElement = objectElements->child_first;
                    break;  //Wow!  That was tough, but we found it
                }
                objectElements = objectElements->sibling_next;
            }

            if (instanceElement == NULL)
            {
                result = MI_RESULT_INVALID_PARAMETER;
                goto cleanup;
            }
        }
        else
        {
            result = MI_RESULT_INVALID_PARAMETER;
            goto cleanup;
        }
    }

    result = XmlDeserializer_DoDeserializeInstance(&stateData, instanceElement);

cleanup:
    if ((result == MI_RESULT_OK) &&
        serializedBufferRead)
    {
        *serializedBufferRead = (MI_Uint32)((xmlEndPtr - ((MI_Char*)docCopy)) * sizeof(MI_Char));
    }

    //Cleanup memory
    if (docCopy)
    {
        free(docCopy);
    }
    if (xmldoc)
    {
        XMLDOM_Free(xmldoc);
    }
    {
        //Cleanup classes we decoded from XML, they will be AddRef-ed if necessary by
        //instance creation
        MI_Uint32 i;
        for (i = 0; i != stateData.u.instanceData.foundClassesCount; i++)
        {
            MI_Class_Delete(stateData.u.instanceData.foundClasses[i]);
        }
    }

    //If we failed then don't return the resultant class
    if ((result != MI_RESULT_OK) && stateData.u.instanceData.instanceResult)
    {
        MI_Instance_Delete(stateData.u.instanceData.instanceResult);
        stateData.u.instanceData.instanceResult = NULL;
    }
    else
    {
        if (instanceObject)
            *instanceObject = stateData.u.instanceData.instanceResult;
    }
    //If we have not created an error object then create a default one
    if (cimErrorDetails && !*cimErrorDetails && (result != MI_RESULT_OK))
    {
        OMI_Error *omiObj = NULL;
        if (OMI_ErrorFromErrorCode(NULL, result, MI_RESULT_TYPE_MI, NULL, &omiObj) != MI_RESULT_OK)
        {
            //TSASSERT(0, PAL_T("This only fails in out of memory and we are ignoring this particular error on purpose."), TLINE);
        }
        else
        {
            if (omiObj)
                *cimErrorDetails = &omiObj->__instance;
        }
    }

    FreeNamespaceBuffer(&stateData);

    return result;
}

MI_Result MI_CALL XmlDeserializer_DoDeserializeInstance(
    _Inout_ DeserializationData *stateData, 
    XMLDOM_Elem *instanceElement)
{
    MI_Result result;
    const MI_Char *instanceClassName = NULL;
    XMLDOM_Attr *cursorAttr;
    MI_Uint32 classIterator;


    //Get the class name of this instance
    cursorAttr = instanceElement->attr_first;
    while (cursorAttr)
    {
        if ((instanceClassName == NULL) && Tcscmp(cursorAttr->name, PAL_T("CLASSNAME")) == 0)
        {
            //Class name
            instanceClassName = cursorAttr->value;
        }
        else
        {
            //dup or unknown attribute
            return _CreateErrorObject(stateData->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("INSTANCE"), cursorAttr->name);
        }
        cursorAttr = cursorAttr->next;
    }
    if (instanceClassName == NULL)
    {
        //missing class name attribute
        return _CreateErrorObject(stateData->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("INSTANCE"), PAL_T("CLASSNAME"));
    }

    //If this is an CIM document then we should try and find the instances in that.
    if (stateData->u.instanceData.declgroupElement)
    {
        MI_Uint32 i;

        //Look through the found ones first
        for (i = 0; i != stateData->u.instanceData.foundClassesCount; i++)
        {
            if ( Tcscasecmp(instanceClassName, stateData->u.instanceData.foundClasses[i]->classDecl->name) == 0)
            {
                stateData->u.instanceData.instanceClass = stateData->u.instanceData.foundClasses[i];
                break;
            }
        }
        if (stateData->u.instanceData.instanceClass == NULL)
        {
            MI_Class *instanceClass = NULL;
            result = XmlDeserializer_GetInstanceClass(stateData, stateData->u.instanceData.declgroupElement, 0, instanceClassName, stateData->u.instanceData.namespaceName, stateData->u.instanceData.serverName, &instanceClass);
            if ((result != MI_RESULT_OK) && (result != MI_RESULT_NOT_FOUND))
            {
                goto cleanup;
            }
            stateData->u.instanceData.instanceClass = (MI_Class*)instanceClass;
            if (stateData->u.instanceData.instanceClass)
            {
                //Add to our cache
                if (stateData->u.instanceData.foundClassesCount == sizeof(stateData->u.instanceData.foundClasses)/sizeof(stateData->u.instanceData.foundClasses[0]))
                {
                    //Eeek, the cache is full
                    MI_Class_Delete(stateData->u.instanceData.instanceClass);
                    stateData->u.instanceData.instanceClass = NULL;
                    return _CreateErrorObject(stateData->errorObject, MI_RESULT_FAILED, ID_MI_DES_XML_INST_TOO_MANY_CLASSES);
                }
                stateData->u.instanceData.foundClasses[stateData->u.instanceData.foundClassesCount] = stateData->u.instanceData.instanceClass;
                stateData->u.instanceData.foundClassesCount++;
            }
        }
    }

    //If no class yet then go through the list of classes we were given
    if (stateData->u.instanceData.instanceClass == NULL)
    {
        if (stateData->u.instanceData.classObjects != NULL)
        {
            for (classIterator = 0; classIterator != stateData->u.instanceData.numberClassObjects; classIterator++)
            {
                const MI_Char *thisClassName;
#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 6054)
#endif
               result = MI_Class_GetClassName(stateData->u.instanceData.classObjects[classIterator], &thisClassName);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
                if (result != MI_RESULT_OK)
                {
                    goto cleanup;
                }
                if (Tcscmp(thisClassName, instanceClassName) == 0)
                {
                    stateData->u.instanceData.instanceClass = stateData->u.instanceData.classObjects[classIterator]; 
                    break;
                }
            }
        }
        if (stateData->u.instanceData.instanceClass == NULL)
        {
            if (stateData->clientGetClassCallback)
            {
                result = stateData->clientGetClassCallback(stateData->clientGetClassCallbackContext, stateData->u.instanceData.serverName, stateData->u.instanceData.namespaceName, instanceClassName, &stateData->u.instanceData.instanceClass );
                if (result != MI_RESULT_OK)
                {
                    return result;
                }
                if (stateData->u.instanceData.foundClassesCount == sizeof(stateData->u.instanceData.foundClasses)/sizeof(stateData->u.instanceData.foundClasses[0]))
                {
                    //Eeek, the cache is full
                    MI_Class_Delete(stateData->u.instanceData.instanceClass);
                    stateData->u.instanceData.instanceClass = NULL;
                    return _CreateErrorObject(stateData->errorObject, MI_RESULT_FAILED, ID_MI_DES_XML_INST_TOO_MANY_CLASSES);
                }
                stateData->u.instanceData.foundClasses[stateData->u.instanceData.foundClassesCount] = stateData->u.instanceData.instanceClass;
                stateData->u.instanceData.foundClassesCount++;
            }
            else
            {
                return _CreateErrorObject(stateData->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_INST_CANNOT_FIND_CLASS, instanceClassName);
            }
        }
    }

    //We have the class object and the instance node.  We are ready to process the instance
    result = XmlDeserializer_DoDeserialization(stateData, 0, instanceElement->child_first);

cleanup:

    return result;
}

MI_Result MI_CALL XmlDeserializer_Instance_GetClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}

_Check_return_ MI_Result XmlDeserializer_GetInstanceClass(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Elem *declgroupElem, 
    MI_Uint32 flags, 
    _In_z_ const MI_Char *instanceClassName, 
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Outptr_ MI_Class **resultClass)
{
    XMLDOM_Elem *elemCursor = declgroupElem->child_first;
    MI_Result result;

    while (elemCursor)
    {
        //Find a class
        if ((Tcscmp(elemCursor->name, PAL_T("VALUE.OBJECT")) == 0) &&
            elemCursor->child_first &&
            (Tcscmp(elemCursor->child_first->name, PAL_T("CLASS")) == 0))
        {
            //Find this class name in attribute list
            XMLDOM_Attr *attrCursor = elemCursor->child_first->attr_first;
            const MI_Char *className = NULL;
            const MI_Char *superclassName = NULL;
            while (attrCursor)
            {
                if (Tcscmp(attrCursor->name, PAL_T("NAME")) == 0)
                {
                    className = attrCursor->value;
                }
                else if (Tcscmp(attrCursor->name, PAL_T("SUPERCLASS")) == 0)
                {
                    superclassName = attrCursor->value;
                }
                else if (Tcscmp(attrCursor->name, PAL_T("DERIVATION")) == 0)
                {
                    /* TODO */
                }
                attrCursor = attrCursor->next;
            }
            if (className == NULL)
            {
                _CreateErrorObject(state->errorObject,  MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("CLASS"), PAL_T("NAME"));
                return MI_RESULT_INVALID_PARAMETER;
            }

            if (Tcscmp(className, instanceClassName)==0)
            {
                MI_Class *parentClass = NULL;
                if (superclassName)
                {
                    //We need to get the superclass class object to pass through to this guy
                    result = XmlDeserializer_GetInstanceClass(state, declgroupElem, flags, superclassName, namespaceName, serverName, &parentClass);
                    if (result != MI_RESULT_OK)
                    {
                        _CreateErrorObject(state->errorObject,  result, ID_MI_DES_XML_INST_CANNOT_FIND_CLASS, superclassName);
                        return result;
                    }
                }
                result = XmlDeserializer_DoDeserializeClass(elemCursor->child_first, flags, parentClass, namespaceName, serverName, state->clientGetClassCallback, state->clientGetClassCallbackContext, resultClass, state->errorObject);
                if (parentClass)
                {
                    MI_Class_Delete(parentClass);
                }
                return result;
            }
        }
        elemCursor = elemCursor->sibling_next;
    }
    return MI_RESULT_NOT_FOUND;
}

_Check_return_ MI_Result XmlDeserializer_DoDeserializeClass(
    _In_ const XMLDOM_Elem *classNode, 
    MI_Uint32 flags,
    _In_opt_ const MI_Class *parentClass, 
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Outptr_ MI_Class **resultClass,
    _Outptr_opt_result_maybenull_ MI_Instance **errorObject)
{
    MI_Result result = MI_RESULT_OK;
    const MI_Char *superClassName = NULL;
    MI_Char *derivationNameList = NULL;
    XMLDOM_Attr *cursorAttr = classNode->attr_first;
    DeserializationData stateData;

    MI_Class *constructedParentClass = NULL;

    memset(&stateData, 0, sizeof(stateData));
    stateData.type = DeserializingClass;
    stateData.errorObject = errorObject;
    stateData.clientGetClassCallback = classObjectNeeded;
    stateData.clientGetClassCallbackContext = classObjectNeededContext;
    stateData.u.classData.classParent = (MI_Class*)parentClass;
    stateData.u.classData.namespaceName = namespaceName;
    stateData.u.classData.serverName = serverName;
    stateData.u.classData.includeUnknownOrigins = MI_TRUE;    //implies those for our class
    stateData.u.classData.includePropertiesFromAllOrigins = MI_TRUE;  //For non-best-case scenario OK to add all properties

    *resultClass = NULL;

    //First node has class name and superClass name in the attribute list
    while (cursorAttr)
    {
        if ((stateData.u.classData.className == NULL) && (Tcscmp(cursorAttr->name, PAL_T("NAME")) == 0))
        {
            //Class name
            stateData.u.classData.className = cursorAttr->value;
        }
        else if ((superClassName == NULL) && (Tcscmp(cursorAttr->name, PAL_T("SUPERCLASS")) == 0))
        {
            //Superclass
            superClassName = cursorAttr->value;
        }
        else if (!derivationNameList && (Tcscmp(cursorAttr->name, PAL_T("DERIVATION")) == 0))
        {
            derivationNameList = (MI_Char*) cursorAttr->value;  //We will be adding NULL terminating characters in it
        }
        else
        {
            _CreateErrorObject(stateData.errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("CLASS"), cursorAttr->name);
            return MI_RESULT_INVALID_PARAMETER;
        }
        cursorAttr = cursorAttr->next;
    }
    if (stateData.u.classData.className == NULL)
    {
        result = MI_RESULT_INVALID_PARAMETER;
        _CreateErrorObject(stateData.errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("CLASS"), PAL_T("NAME"));
        goto cleanup;
    }

    if (superClassName && !parentClass && !derivationNameList)
    {
        //need to treat as flat as derivation tree is unknown
        superClassName = NULL;
        stateData.u.classData.classParent = NULL;
    }
    else if (superClassName && !parentClass && derivationNameList)
    {
        //We need to build a parent class as best we can from the derivation list
        MI_Char *topLevelDerivationItem = NULL;
        MI_Char *remainingDerivationNameList = NULL;
        _ExtractNextTokenFromDerivationString(derivationNameList, &topLevelDerivationItem, &remainingDerivationNameList);

        if (Tcscasecmp(superClassName, topLevelDerivationItem) != 0)
        {
            //Names should match at top level
            result = MI_RESULT_INVALID_PARAMETER;
            _CreateErrorObject(stateData.errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_CLASS_DERIVATION_LIST_WRONG);
            goto cleanup;
        }
        result = XmlDeserializer_GetDerivationParentClass(flags, topLevelDerivationItem, remainingDerivationNameList, namespaceName, serverName, classNode, classObjectNeeded, classObjectNeededContext, &constructedParentClass);
        if (result != MI_RESULT_OK)
        {
            goto cleanup;
        }
        stateData.u.classData.classParent = constructedParentClass;
    }
    else if (!superClassName && parentClass)
    {
        //We have no superclass but a parent class was passed in
        _CreateErrorObject(stateData.errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_CLASS_SUPERCLASS_PARENT_MISMATCH);
        result = MI_RESULT_INVALID_PARAMETER;
        goto cleanup;
    }
    else if (superClassName  && parentClass && (Tcscmp(superClassName, parentClass->classDecl->name) != 0))
    {
        //superclass does not match parent class
        result = MI_RESULT_INVALID_PARAMETER;
        _CreateErrorObject(stateData.errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_CLASS_SUPERCLASS_PARENT_MISMATCH);
        goto cleanup;
    }

    result = XmlDeserializer_DoDeserialization(&stateData, flags, classNode->child_first);

    if ((result != MI_RESULT_OK) &&
        (stateData.u.classData.classResult != NULL))
    {
        MI_Class_Delete(stateData.u.classData.classResult);
        stateData.u.classData.classResult = NULL;
    }
    else if (result == MI_RESULT_OK)
    {
        *resultClass = stateData.u.classData.classResult;
    }

cleanup:
    if (constructedParentClass)
    {
        MI_Class_Delete(constructedParentClass);
    }
    FreeNamespaceBuffer(&stateData);
    return result;
}

_Check_return_ static MI_Result XmlDeserializer_DoDeserialization(_Inout_ DeserializationData *state, MI_Uint32 flags, _In_ const XMLDOM_Elem *elementNode)
{
    //Need to count properties, methods and class qualifiers in order to create a class
    const XMLDOM_Elem *cursorElem = elementNode;
    MI_Uint32 classQualifierTotal = 0;
    MI_Uint32 classElementTotal = 0;
    MI_Uint32 classMethodTotal = 0;
    MI_Result result;

    while (cursorElem)
    {
        if ((Tcscmp(cursorElem->name, PAL_T("QUALIFIER")) == 0) &&
            (state->type == DeserializingClass))
        {
            //Qualifiers only supported on classes
            classQualifierTotal++;
        }
        else if ((Tcscmp(cursorElem->name, PAL_T("PROPERTY")) == 0) ||
                 (Tcscmp(cursorElem->name, PAL_T("PROPERTY.ARRAY")) == 0) ||
                 (Tcscmp(cursorElem->name, PAL_T("PROPERTY.REFERENCE")) == 0))
        {
            classElementTotal++;
        }
        else if ((Tcscmp(cursorElem->name, PAL_T("METHOD")) == 0) &&
                 (state->type == DeserializingClass))
        {
            //Methods only supported on classes
            classMethodTotal++;
        }
        else
        {
            _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, cursorElem->parent->name, cursorElem->name);
            return MI_RESULT_INVALID_PARAMETER;
        }
        cursorElem = cursorElem->sibling_next;
    }

    //We are now ready to start creating the resultant class
    if (state->type == DeserializingClass)
    {
        result = ClassConstructor_New(state->u.classData.classParent, state->u.classData.namespaceName, state->u.classData.serverName, state->u.classData.className, classQualifierTotal, classElementTotal, classMethodTotal, &state->u.classData.classResult);
        if (result != MI_RESULT_OK)
        {
            return result;
        }
    }
    else
    {
        result = Instance_New(&state->u.instanceData.instanceResult, state->u.instanceData.instanceClass->classDecl, NULL);;
        if (result != MI_RESULT_OK)
        {
            return result;
        }
        if (state->u.instanceData.namespaceName)
        {
            result = MI_Instance_SetNameSpace(state->u.instanceData.instanceResult, state->u.instanceData.namespaceName);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
        }
        if (state->u.instanceData.serverName)
        {
            result = MI_Instance_SetServerName(state->u.instanceData.instanceResult, state->u.instanceData.serverName);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
        }
    }
    
    //Now we add all the qualifiers, properties and methods for real
    cursorElem = elementNode;
    while (cursorElem)
    {
        if (Tcscmp(cursorElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //Qualifiers on supported on classes, already validated this is a class
            result = XmlDeserializer_AddClassQualifier(state, state->u.classData.classResult, cursorElem);
        }
        else if (Tcscmp(cursorElem->name, PAL_T("PROPERTY")) == 0)
        {
            result = XmlDeserializer_AddProperty(state, cursorElem);
        }
        else if (Tcscmp(cursorElem->name, PAL_T("PROPERTY.ARRAY")) == 0)
        {
            result = XmlDeserializer_AddPropertyArray(state, cursorElem);
        }
        else if (Tcscmp(cursorElem->name, PAL_T("PROPERTY.REFERENCE")) == 0)
        {
            result = XmlDeserializer_AddPropertyReference(state, cursorElem);
        }
        else if (Tcscmp(cursorElem->name, PAL_T("METHOD")) == 0)
        {
            //Methods on supported on classes and already validated this is a class
            result = XmlDeserializer_AddClassMethod(state, state->u.classData.classResult, cursorElem);
        }
        if (result != MI_RESULT_OK)
        {
            return result;
        }
        cursorElem = cursorElem->sibling_next;
    }

    return MI_RESULT_OK;
}

// Extract the value out from the xml element, it could be like following cases,
//  1. <VALUE/>
//  2. <VALUE>abc</VALUE>
// A real example is <QUALIFIER NAME="MappingStrings" TYPE="string"><VALUE.ARRAY><VALUE/></VALUE.ARRAY></QUALIFIER>
// Case 1 is only applicable to MI_STRING type element, "" will be the output value.
// Otherwise return MI_RESULT_INVALID_PARAMETER.
_Check_return_ static MI_Result _ExtractValueFromVALUEElement(
    _In_ const DeserializationData *state,
    _In_ const XMLDOM_Elem *valueElement,
    _In_ MI_Type type,
    _Outptr_result_z_  const MI_Char *  *value)
{
    *value = PAL_T("");
    if (valueElement->value_first == NULL)
    {
        // value_first here could be null since empty string value will be serialized as <VALUE/>
        if (type != MI_STRING)
        {
            _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_EMPTY_VAL_NOT_STRING);
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else
    {
        if (valueElement->value_first->value == NULL)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        *value = valueElement->value_first->value;
    }
    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _ExtractQualifierAttributes(
    _In_ const DeserializationData *state,
    _In_ const XMLDOM_Elem *qualifierElement, 
    _Outptr_result_z_ const MI_Char * *name, 
    _Out_ MI_Type *type, 
    _Out_ MI_Uint32 *flavor, 
    _Out_ MI_Value *value, 
    _Out_ MI_Boolean *isArray, 
    _Out_ MI_Uint32 *arrayCount)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean foundType = MI_FALSE;
    XMLDOM_Attr *attrList = qualifierElement->attr_first;

    *name = NULL;
    *flavor = MI_FLAG_TOSUBCLASS|MI_FLAG_ENABLEOVERRIDE;
    memset(value, 0, sizeof(*value));
    *isArray = MI_FALSE;
    *arrayCount = 0;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!foundType && Tcscmp(attrList->name, PAL_T("TYPE")) == 0)
        {
            result = _StringToMiType(attrList->value, type);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"), attrList->name);
                return result;
            }
            foundType = MI_TRUE;
        }
        else if (Tcscmp(attrList->name, PAL_T("TOSUBCLASS")) == 0)
        {
            MI_Boolean tmpBool = MI_FALSE;
            result = _StringToMiBool(attrList->value, &tmpBool);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"), attrList->name);
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpBool == MI_TRUE)
            {
                *flavor &= ~MI_FLAG_RESTRICTED;
                *flavor |= MI_FLAG_TOSUBCLASS;
            }
            else
            {
                *flavor &= ~MI_FLAG_TOSUBCLASS;
                *flavor |= MI_FLAG_RESTRICTED;
            }
        }
        else if (Tcscmp(attrList->name, PAL_T("TRANSLATABLE")) == 0)
        {
            MI_Boolean tmpBool = MI_FALSE;
            result = _StringToMiBool(attrList->value, &tmpBool);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"), attrList->name);
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpBool)
            {
                *flavor |= MI_FLAG_TRANSLATABLE;
            }
            else
            {
                *flavor &= ~MI_FLAG_TRANSLATABLE;
            }
        }
        else if (Tcscmp(attrList->name, PAL_T("OVERRIDABLE")) == 0)
        {
            MI_Boolean tmpBool = MI_FALSE;
            result = _StringToMiBool(attrList->value, &tmpBool);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"), attrList->name);
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpBool)
            {
                *flavor &= ~MI_FLAG_DISABLEOVERRIDE;
                *flavor |= MI_FLAG_ENABLEOVERRIDE;
            }
            else
            {
                *flavor &= ~MI_FLAG_ENABLEOVERRIDE;
                *flavor |= MI_FLAG_DISABLEOVERRIDE;
            }
        }
        else if ((Tcscmp(attrList->name, PAL_T("TOINSTANCE")) == 0) ||
            (Tcscmp(attrList->name, PAL_T("PROPAGATED")) == 0))
        {
            //Ignore TOINSTANCE and PROPAGATED
            MI_Boolean boolValue;
            result = _StringToMiBool(attrList->value, &boolValue);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"), attrList->name);
                return result;
            }
        }
        else
        {
            _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("QUALIFIER"), attrList->name);
            return MI_RESULT_INVALID_PARAMETER;
        }
        attrList = attrList->next;
    }

    if (!*name)
    {
        _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("QUALIFIER"), PAL_T("NAME"));
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (!foundType)
    {
        _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("QUALIFIER"), PAL_T("TYPE"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Retrieve value */
    if (qualifierElement->child_first)
    {
        if (Tcscmp(qualifierElement->child_first->name, PAL_T("VALUE.ARRAY")) == 0)
        {
            //count how many elements in array
            XMLDOM_Elem *arrayCursor = qualifierElement->child_first->child_first;
            while (arrayCursor)
            {
                (*arrayCount)++;
                arrayCursor = arrayCursor->sibling_next;
            }
            *isArray = MI_TRUE;
            return MI_RESULT_OK;
        }
        else if (Tcscmp(qualifierElement->child_first->name, PAL_T("VALUE")) == 0)
        {
            const MI_Char * tempValue = NULL;
            result = _ExtractValueFromVALUEElement(state, qualifierElement->child_first, *type, &tempValue);
            if (result != MI_RESULT_OK)
                return result;
            result = _StringToMiValue(NULL, tempValue, *type, value);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"));
                return MI_RESULT_INVALID_PARAMETER;
            }
        }
        else
        {
            _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("QUALIFIER"), qualifierElement->child_first->name);
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else
    {
        _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ELEM_HAS_NO_CHILDREN, PAL_T("QUALIFIER"));
        return MI_RESULT_INVALID_PARAMETER;
    }

    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddClassQualifier(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ const XMLDOM_Elem *cursorElem)
{
    MI_Result result;
    const MI_Char *name;
    MI_Type type;
    MI_Uint32 flavor;
    MI_Value value;
    MI_Boolean isArray;
    MI_Uint32 arrayCount;

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 6054)
#endif
    result = _ExtractQualifierAttributes(state, cursorElem, &name, &type, &flavor, &value, &isArray, &arrayCount);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
    if (result != MI_RESULT_OK)
        return result;

    if (isArray)
    {
        MI_Uint32 qualifierIndex;

        result = Class_AddClassQualifierArray(finalClass, name, type, flavor, arrayCount, &qualifierIndex);
        if (result != MI_RESULT_OK)
        {
            return result;
        }

        cursorElem = cursorElem->child_first->child_first;
        while (cursorElem)
        {
            if ((cursorElem->value_first == NULL) || 
                (cursorElem->value_first->value == NULL))
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            result = _StringToMiValue(NULL, cursorElem->value_first->value, type, &value);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("CLASS QUALIFIER"));
                return MI_RESULT_INVALID_PARAMETER;
            }

            result = Class_AddClassQualifierArrayItem(finalClass, qualifierIndex, value);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
            cursorElem = cursorElem->sibling_next;
        }
    }
    else
    {
        //Plain non-array value
        return Class_AddClassQualifier(finalClass, name, type, value, flavor);
    }
    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _ExtractPropertyAttributes(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList, 
    _Outptr_result_z_ const MI_Char **name, 
    _Out_ MI_Type *type, 
    _Outptr_result_maybenull_z_ const MI_Char **classOrigin, 
    _Out_ MI_Boolean *propagated,
    _Out_ MI_Uint32 *embedded, 
    _Outptr_result_maybenull_z_ const MI_Char **embeddedClassName,
    _Out_opt_ MI_Uint32 *maxArraySize,
    _Out_ MI_Boolean *modified)
{
    MI_Result result;
    MI_Boolean typeExists = MI_FALSE;

    *name = NULL;
    *classOrigin = NULL;

    *embedded = 0;
    *embeddedClassName = NULL;

    *modified = MI_FALSE;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!typeExists && Tcscmp(attrList->name, PAL_T("TYPE")) == 0)
        {
            result = _StringToMiType(attrList->value, type);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"), attrList->name);
                return result;
            }
            typeExists = MI_TRUE;
        }
        else if (Tcscmp(attrList->name, PAL_T("CLASSORIGIN")) == 0)
        {
            *classOrigin = attrList->value;
        }
        else if (Tcscmp(attrList->name, PAL_T("PROPAGATED")) == 0)
        {
            result = _StringToMiBool(attrList->value, propagated);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"), attrList->name);
                return result;
            }
        }
        else if (Tcscmp(attrList->name, PAL_T("EmbeddedObject")) == 0)
        {
            if (Tcscmp(attrList->value, PAL_T("object")) == 0)
                *embedded = 1;
            else if (Tcscmp(attrList->value, PAL_T("instance")) == 0)
                *embedded = 2;
            else
            {
                _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"), attrList->name);
                return MI_RESULT_INVALID_PARAMETER;
            }
        }
        else if (maxArraySize && (Tcscmp(attrList->name, PAL_T("ARRAYSIZE")) == 0))
        {
            MI_Char *tmpEnd = (MI_Char*)attrList->value;

            *maxArraySize =  Tcstoul(attrList->value, &tmpEnd, 10);

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26018, "Esp:692")
#endif
            if ((*tmpEnd) != PAL_T('\0'))
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
            {
                _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"), attrList->name);
                return MI_RESULT_INVALID_PARAMETER;
            }
        }
        else if (Tcscmp(attrList->name, PAL_T("EmbeddedClassName")) == 0)
        {
            *embeddedClassName = attrList->value;
        }
        else if (Tcscmp(attrList->name, PAL_T("MODIFIED")) == 0)
        {
            result = _StringToMiBool(attrList->value, modified);
            if (result != MI_RESULT_OK)
            {
                _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"), attrList->name);
                return result;
            }
        }
        else
        {
            _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("PROPERTY"), attrList->name);
            return MI_RESULT_INVALID_PARAMETER;
        }

        attrList = attrList->next;
    }
    if (!typeExists)
    {
        _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PROPERTY"), PAL_T("TYPE"));
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (!*name)
    {
        _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PROPERTY"), PAL_T("NAME"));
        return MI_RESULT_INVALID_PARAMETER;
    }
    if ((*embedded != 2) && (*embeddedClassName))
    {
        // Linux does not apply the same argument to two different places in formatted string
        _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_INVALID_EMBED_CLASS_NAME, PAL_T("PROPERTY"), PAL_T("PROPERTY"));
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (*embedded)
    {
        *type = MI_INSTANCE;
    }
    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _ExtractPropertyReferenceAttributes(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList, 
    _Outptr_result_z_ const MI_Char **name, 
    _Outptr_result_maybenull_z_ const MI_Char **referenceClass, 
    _Outptr_result_maybenull_z_ const MI_Char **classOrigin, 
    _Out_ MI_Boolean *propagated,
    _Out_ MI_Boolean *modified)
{
    MI_Result result;

    *name = NULL;
    *classOrigin = NULL;
    *referenceClass = NULL;
    *propagated = MI_FALSE;
    *modified = MI_FALSE;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!*referenceClass && Tcscmp(attrList->name, PAL_T("REFERENCECLASS")) == 0)
        {
            *referenceClass = attrList->value;
        }
        else if (!*classOrigin && Tcscmp(attrList->name, PAL_T("CLASSORIGIN")) == 0)
        {
            *classOrigin = attrList->value;
        }
        else if (Tcscmp(attrList->name, PAL_T("PROPAGATED")) == 0)
        {
            result = _StringToMiBool(attrList->value, propagated);
            if (result != MI_RESULT_OK)
            {
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY.REFERENCE"), attrList->name);
            }
        }
        else if (Tcscmp(attrList->name, PAL_T("MODIFIED")) == 0)
        {
            result = _StringToMiBool(attrList->value, modified);
            if (result != MI_RESULT_OK)
            {
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PROPERTY.REFERENCE"), attrList->name);
            }
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("PROPERTY.REFERENCE"), attrList->name);
        }

        attrList = attrList->next;
    }
    if (!*name)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PROPERTY.REFERENCE"), PAL_T("NAME"));
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddPropertyQualifier(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *cursorElem, 
    MI_Uint32 elementId)
{
    MI_Result result;
    const MI_Char *name;
    MI_Type type;
    MI_Uint32 flavor;
    MI_Value value;
    MI_Boolean isArray;
    MI_Uint32 arrayCount;

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 6054)
#endif
    result = _ExtractQualifierAttributes(state, cursorElem, &name, &type, &flavor, &value, &isArray, &arrayCount);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
    if (result != MI_RESULT_OK)
        return result;

    if (isArray)
    {
        MI_Uint32 qualifierIndex;

        result = Class_AddElementQualifierArray(finalClass, elementId, name, type, flavor, arrayCount, &qualifierIndex);
        if (result != MI_RESULT_OK)
        {
            return result;
        }

        cursorElem = cursorElem->child_first->child_first;
        while (cursorElem)
        {
            const MI_Char * tempValue = NULL;
            result = _ExtractValueFromVALUEElement(state, cursorElem, type, &tempValue);
            if (result != MI_RESULT_OK)
                return result;
            result = _StringToMiValue(NULL, tempValue, type, &value);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PROPERTY QUALIFIER"));

            result = Class_AddElementQualifierArrayItem(finalClass, elementId, qualifierIndex, value);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
            cursorElem = cursorElem->sibling_next;
        }
    }
    else
    {
        //Plain non-array value
        return Class_AddElementQualifier(finalClass, elementId, name, type, value, flavor);
    }
    return MI_RESULT_OK;
}

static MI_Boolean ShouldFilterElementForCurrentClass(_In_ const DeserializationData *state, _In_opt_z_ const MI_Char *classOrigin, MI_Boolean overridden)
{
    if (state->type == DeserializingClass)
    {
        if (state->u.classData.includePropertiesFromAllOrigins)
        {
            //want everything
            return MI_FALSE;
        }
        else if (!classOrigin && state->u.classData.includeUnknownOrigins)
        {
            //no origin and asked to include that
            return MI_FALSE;            
        }
        else if (!classOrigin) 
        {
            //no origin and not asked for that
            return MI_TRUE;
        }
        else if (!overridden && (Tcscasecmp(state->u.classData.className, classOrigin) != 0))
        {
            //origin does not match our class
            return MI_TRUE;
        }
        else 
        {
            //origin matches className so we need that
            return MI_FALSE;                        
        }
    }

    return MI_FALSE;
}

static MI_Result ProcessOverrideQualifier(_In_ const DeserializationData *state, _In_ XMLDOM_Elem *currentElem, _In_ const MI_Char *elementBeingProcessed, _Out_ MI_Boolean *overridden)
{
    MI_Result result = MI_RESULT_OK;

    *overridden = MI_FALSE;

    if (currentElem->attr_first && 
        currentElem->attr_first->value &&
        Tcscmp(currentElem->attr_first->value, PAL_T("Overridden")) == 0)
    {
        if (currentElem->child_first &&
            currentElem->child_first->name &&
            (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
            currentElem->child_first->value_first && 
            currentElem->child_first->value_first->value)
        {
            result = _StringToMiBool(currentElem->child_first->value_first->value, overridden);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, elementBeingProcessed, PAL_T("Overridden"));
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"));
        }        
    }

    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddProperty(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyElem)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = propertyElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *classOrigin = NULL;
    const MI_Char *embeddedClassName = NULL;
    MI_Type type = MI_BOOLEAN;
    MI_Value value;
    MI_Boolean propagated = MI_FALSE;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 elementId = 0;
    MI_Boolean valueExists = MI_FALSE;
    MI_Uint32 flags = 0;
    MI_Uint32 embedded = 0;
    MI_Boolean overridden = MI_FALSE;
    MI_Boolean modified = MI_FALSE;

    memset(&value, 0, sizeof(value));

    result =_ExtractPropertyAttributes(state, propertyElem->attr_first, &name, &type, &classOrigin, &propagated, &embedded, &embeddedClassName, NULL, &modified);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Count qualifiers, and determine if this is an embedded class
    while (currentElem)
    {
        if ((state->type == DeserializingClass) && 
            (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0))
            
        {
            //If embedded instance/object then we need to overload the type
            if (currentElem->attr_first &&
                (Tcscmp(currentElem->attr_first->name, PAL_T("NAME"))==0))
            {
                if (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDINSTANCE"))==0)
                    
                {
                    if (currentElem->child_first &&
                        (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
                        currentElem->child_first->value_first)
                    {
                        embeddedClassName = currentElem->child_first->value_first->value;
                        type = MI_INSTANCE;
                    }
                    else
                    {
                        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"));
                    }
                }
                else if (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDOBJECT"))==0)
                {
                    type = MI_INSTANCE;
                }
                else
                {
                    result = ProcessOverrideQualifier(state, currentElem, PAL_T("PROPERTY"), &overridden);
                    if(result != MI_RESULT_OK)
                        return result;
                }
            }
            //Note, instance qualifiers are not supported
            numberQualifiers++;
        }
        else if ((Tcscmp(currentElem->name, PAL_T("VALUE")) != 0) && (Tcscmp(currentElem->name, PAL_T("VALUE.OBJECT")) != 0))
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("PROPERTY"), currentElem->name);
        }

        currentElem = currentElem->sibling_next;
    }

    if(ShouldFilterElementForCurrentClass(state, classOrigin, overridden))
        return MI_RESULT_OK;

    //Now to the values... we needed to know the embedded object stuff so that is why it is not in 
    //same loop
    currentElem = propertyElem->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("VALUE")) == 0)
        {
            const MI_Char * firstElemValue = NULL;
            result = _ExtractValueFromVALUEElement(state, currentElem, type, &firstElemValue);
            if (result != MI_RESULT_OK)
                return result;
            result = _StringToMiValue(state, firstElemValue, type, &value);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"));
            valueExists = MI_TRUE;
        }
        else if (Tcscmp(currentElem->name, PAL_T("VALUE.OBJECT")) == 0)
        {

            DeserializationData embeddedState;
            memset(&embeddedState, 0, sizeof(embeddedState));
            embeddedState.type = DeserializingInstance;
            embeddedState.clientGetClassCallback = state->clientGetClassCallback;
            embeddedState.clientGetClassCallbackContext = state->clientGetClassCallbackContext;
            embeddedState.errorObject = state->errorObject;
            embeddedState.u.instanceData.classObjects = state->u.instanceData.classObjects;
            embeddedState.u.instanceData.numberClassObjects = state->u.instanceData.numberClassObjects;

            if (state->type == DeserializingClass)
            {
                embeddedState.u.instanceData.namespaceName = state->u.classData.namespaceName;
                embeddedState.u.instanceData.serverName = state->u.classData.serverName;
            }
            else
            {
                embeddedState.u.instanceData.declgroupElement = state->u.instanceData.declgroupElement;
                embeddedState.u.instanceData.namespaceName = state->u.instanceData.namespaceName;
                embeddedState.u.instanceData.serverName = state->u.instanceData.serverName;
                memcpy(embeddedState.u.instanceData.foundClasses, state->u.instanceData.foundClasses, sizeof(state->u.instanceData.foundClasses));
                embeddedState.u.instanceData.foundClassesCount = state->u.instanceData.foundClassesCount;
            }

            if ((currentElem->child_first == NULL) || (Tcscmp(currentElem->child_first->name, PAL_T("INSTANCE")) != 0))
            {
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"));
            }

            result = XmlDeserializer_DoDeserializeInstance(&embeddedState, currentElem->child_first);
            FreeNamespaceBuffer(&embeddedState);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PROPERTY"));

            type = MI_INSTANCE;
            value.instance = embeddedState.u.instanceData.instanceResult;

            //Need to delete any cached classes
            if (state->type == DeserializingClass)
            {
                //Class so nothing to keep
                while (embeddedState.u.instanceData.foundClassesCount)
                {
                    embeddedState.u.instanceData.foundClassesCount--;
                    MI_Class_Delete(embeddedState.u.instanceData.foundClasses[embeddedState.u.instanceData.foundClassesCount]);
                }
            }
            else
            {
                //creating from instance so can copy out new cache over the old one
                //and yeah, original was const.  Sorry about that!
                memcpy(((DeserializationData*)state)->u.instanceData.foundClasses, embeddedState.u.instanceData.foundClasses, sizeof(state->u.instanceData.foundClasses));
                ((DeserializationData*)state)->u.instanceData.foundClassesCount = embeddedState.u.instanceData.foundClassesCount;
            }
        }

        currentElem = currentElem->sibling_next;
    }
    if (valueExists == MI_FALSE)
    {
        flags = MI_FLAG_NULL;
    }

    if (state->type == DeserializingClass)
    {
        /* Add element to class */
#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
        result = Class_AddElement(state->u.classData.classResult, name, type, value, flags, embeddedClassName, propagated, classOrigin, numberQualifiers, &elementId);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
    }
    else
    {
        if (modified == MI_FALSE)
        {
            flags |= MI_FLAG_NOT_MODIFIED;
        }

        /* Adopt embedded instance to its parent instance, */
        /* it will be release upon releasing parent instance */
        if (type == MI_INSTANCE && (NULL != value.instance))
        {
            flags |= MI_FLAG_ADOPT;
        }

        /* Add element to instance */
        result = MI_Instance_SetElement(state->u.instanceData.instanceResult, name, ((flags&MI_FLAG_NULL)?NULL:&value), type, flags);
    }
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Now add the element qualifiers
    currentElem = propertyElem->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //Qualifiers are only supported on classes and we already checked that this is a class
            result = XmlDeserializer_AddPropertyQualifier(state, state->u.classData.classResult, currentElem, elementId);
            if (result != MI_RESULT_OK)
                return result;
        }
        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddPropertyArray(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyArrayElem)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = propertyArrayElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *classOrigin = NULL;
    const MI_Char *embeddedClassName = NULL;
    MI_Type type = MI_BOOLEAN;
    MI_Value value;
    MI_Boolean propagated = MI_FALSE;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 numberPropertyArrayItems = 0;
    MI_Uint32 elementId = 0;
    MI_Uint32 maxArraySize = 0;
    MI_Uint32 embedded = 0;
    MI_Boolean modified = MI_FALSE;
    MI_Boolean propertyExists = MI_FALSE;
    MI_Boolean overridden = MI_FALSE;

    result =_ExtractPropertyAttributes(state, propertyArrayElem->attr_first, &name, &type, &classOrigin, &propagated, &embedded, &embeddedClassName, &maxArraySize, &modified);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Count qualifiers and number of elements in array
    while (currentElem)
    {
        if ((state->type == DeserializingClass) && 
            (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0))
        {
            //Only supported on classes
            //If embedded instance/object then we need to overload the type
            if (currentElem->attr_first &&
                (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDINSTANCE"))==0))
            {
                if (currentElem->child_first &&
                    currentElem->child_first->name &&
                    (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
                    currentElem->child_first->value_first)
                {
                    embeddedClassName = currentElem->child_first->value_first->value;
                    type = MI_INSTANCE;
                }
                else
                {
                    return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("QUALIFIER"));
                }
            }        
            else if (currentElem->attr_first &&
                (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDOBJECT"))==0))
            {
                type = MI_INSTANCE;
            }
            else
            {
                result = ProcessOverrideQualifier(state, currentElem, PAL_T("PROPERTY.ARRAY"), &overridden);
                if(result != MI_RESULT_OK)
                    return result;
            }
                        
            numberQualifiers++;
        }
        else if (Tcscmp(currentElem->name, PAL_T("VALUE.ARRAY")) != 0)
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("PROPERTY.ARRAY"), currentElem->name);
        }

        currentElem = currentElem->sibling_next;
    }

    if(ShouldFilterElementForCurrentClass(state, classOrigin, overridden))
        return MI_RESULT_OK;
    
    currentElem = propertyArrayElem->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("VALUE.ARRAY")) == 0)
        {
            XMLDOM_Elem *arrayElem = currentElem->child_first;
            propertyExists = MI_TRUE;
            while (arrayElem)
            {
                numberPropertyArrayItems++;
                arrayElem = arrayElem->sibling_next;
            }
        }

        currentElem = currentElem->sibling_next;
    }
    /* Add element to class */
    if (state->type == DeserializingClass)
    {
#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
        result = Class_AddElementArray(state->u.classData.classResult, name, type, 0, embeddedClassName, propagated, classOrigin, maxArraySize, numberQualifiers, numberPropertyArrayItems, &elementId);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
    }
    else
    {
        MI_Uint32 flag = 0;
        if (modified == MI_FALSE)
        {
            flag = MI_FLAG_NOT_MODIFIED;
        }
        if (!propertyExists)
        {
            flag |= MI_FLAG_NULL;
        }
        result = Instance_SetElementArray(state->u.instanceData.instanceResult, name, type, flag, numberPropertyArrayItems, &elementId);
    }
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Now add the qualifiers and property array items
    currentElem = propertyArrayElem->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //Only supported on classes
            result = XmlDeserializer_AddPropertyQualifier(state, state->u.classData.classResult, currentElem, elementId);
            if (result != MI_RESULT_OK)
                return result;
        }
        else if (Tcscmp(currentElem->name, PAL_T("VALUE.ARRAY")) == 0)
        {
            XMLDOM_Elem *arrayCursor = currentElem->child_first;
            while (arrayCursor)
            {
                if (Tcscmp(arrayCursor->name, PAL_T("VALUE")) == 0)
                {
                    const MI_Char *valueString;
                    if ((arrayCursor->value_first == NULL) && (type == MI_STRING))
                    {//value would not exist if there was no value in the string
                        valueString = PAL_T("");
                    }
                    else if ((arrayCursor->value_first != NULL) &&
                        (arrayCursor->value_first->value != NULL))
                    {
                        valueString = arrayCursor->value_first->value;
                    }
                    else
                    {
                        return MI_RESULT_INVALID_PARAMETER;
                    }
                    result = _StringToMiValue(state, valueString, type, &value);
                    if (result != MI_RESULT_OK)
                        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PROPERTY.ARRAY"));

                    if (state->type == DeserializingClass)
                    {
                        result = Class_AddElementArrayItem(state->u.classData.classResult, elementId, value);
                    }
                    else
                    {
                        result = Instance_SetElementArrayItem(state->u.instanceData.instanceResult, elementId, value);
                    }
                    if (result != MI_RESULT_OK)
                    {
                        return result;
                    }
                }
                else if (Tcscmp(arrayCursor->name, PAL_T("VALUE.NULL")) == 0)
                {
                    //TODO: Null entry in array!
                    return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("PROPERTY.ARRAY"), arrayCursor->name);
                }
                else
                {
                    return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("PROPERTY.ARRAY"), arrayCursor->name);
                }
                arrayCursor = arrayCursor->sibling_next;
            }
        }
        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddPropertyReference(_In_ const DeserializationData *state, _In_ const XMLDOM_Elem *propertyRefElem)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = propertyRefElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *classOrigin = NULL;
    const MI_Char *referenceClass = NULL;
    MI_Boolean propagated = MI_FALSE;
    MI_Uint32 numberQualifiers = 0;
    MI_Boolean valueExists = MI_FALSE;
    MI_Uint32 elementId = 0;
    MI_Value value;
    MI_Uint32 flags = 0;
    MI_Boolean modified = MI_FALSE;
    MI_Boolean overridden = MI_FALSE;

    memset(&value, 0, sizeof(value));
    
    result =_ExtractPropertyReferenceAttributes(state, propertyRefElem->attr_first, &name, &referenceClass, &classOrigin, &propagated, &modified);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Count qualifiers, and get reference instance
    while (currentElem)
    {
        if ((state->type == DeserializingClass) && 
            (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0))
            
        {
            result = ProcessOverrideQualifier(state, currentElem, PAL_T("PROPERTY.REFERENCE"), &overridden);
            if(result != MI_RESULT_OK)
                return result;
        
            numberQualifiers++;
        }
        else if (!valueExists && 
                 (Tcscmp(currentElem->name, PAL_T("VALUE.REFERENCE")) == 0))
        {
            const MI_Char *serverName = NULL;
            const MI_Char *namespaceName = NULL;
            
            if (state->type == DeserializingInstance)
            {
                serverName = state->u.instanceData.serverName;
                namespaceName = state->u.instanceData.namespaceName;
            }
            
            result = _Extract_VALUE_REFERENCE(state, currentElem, serverName, namespaceName, &value.reference);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
            flags |= MI_FLAG_ADOPT;
            valueExists = MI_TRUE;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, "PROPERTY.REFERENCE", currentElem->name);
        }

        currentElem = currentElem->sibling_next;
    }

    if(ShouldFilterElementForCurrentClass(state, classOrigin, overridden))
        return MI_RESULT_OK;
    
    if (valueExists == MI_FALSE)
    {
        flags |= MI_FLAG_NULL;
    }
    if (state->type == DeserializingClass)
    {
        /* Add element to class */
#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
        result = Class_AddElement(state->u.classData.classResult, name, MI_REFERENCE, value, flags, referenceClass, propagated, classOrigin, numberQualifiers, &elementId);
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
    }
    else
    {
        if (modified == MI_FALSE)
        {
            flags |= MI_FLAG_NOT_MODIFIED;
        }
        /* Add element to instance */
        result = MI_Instance_SetElement(state->u.instanceData.instanceResult, name, ((flags&MI_FLAG_NULL)?NULL:&value), MI_REFERENCE, flags);
    }
    if (result != MI_RESULT_OK)
    {
        if (valueExists)
        {
            MI_Instance_Delete(value.reference);
        }
        return result;
    }

    //Now add the element qualifiers
    currentElem = propertyRefElem->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //Qualifiers are only supported on classes and we already checked that this is a class
            result = XmlDeserializer_AddPropertyQualifier(state, state->u.classData.classResult, currentElem, elementId);
            if (result != MI_RESULT_OK)
                return result;
        }
        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddMethodQualifier(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *cursorElem, 
    MI_Uint32 methodId)
{
    MI_Result result;
    const MI_Char *name;
    MI_Type type;
    MI_Uint32 flavor;
    MI_Value value;
    MI_Boolean isArray;
    MI_Uint32 arrayCount;

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 6054)
#endif
    result = _ExtractQualifierAttributes(state, cursorElem, &name, &type, &flavor, &value, &isArray, &arrayCount);
#ifdef _PREFAST_
#pragma prefast(pop)    
#endif
    if (result != MI_RESULT_OK)
        return result;

    if (isArray)
    {
        MI_Uint32 qualifierId;

        result = Class_AddMethodQualifierArray(finalClass, methodId, name, type, flavor, arrayCount, &qualifierId);
        if (result != MI_RESULT_OK)
        {
            return result;
        }

        cursorElem = cursorElem->child_first->child_first;
        while (cursorElem)
        {
            if (Tcscmp(cursorElem->name, PAL_T("VALUE")) != 0)
            {
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("METHOD QUALIFIER"), cursorElem->name);
            }
            if ((cursorElem->value_first == NULL) || 
                (cursorElem->value_first->value == NULL))
            {
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("METHOD QUALIFIER"));
            }
            result = _StringToMiValue(NULL, cursorElem->value_first->value, type, &value);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("METHOD QUALIFIER"));

            result = Class_AddMethodQualifierArrayItem(finalClass, methodId, qualifierId, value);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
            cursorElem = cursorElem->sibling_next;
        }
    }
    else
    {
        //Plain non-array value
        return Class_AddMethodQualifier(finalClass, methodId, name, type, value, flavor);
   }
    return MI_RESULT_OK;
}
_Check_return_ static MI_Result _ExtractMethodAttributes(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList, 
    _Outptr_result_z_ const MI_Char **name, 
    _Out_ MI_Type *type, 
    _Outptr_result_z_ const MI_Char **classOrigin)
{
    MI_Result result;
    MI_Boolean typeExists = MI_FALSE;

    *name = NULL;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!typeExists && Tcscmp(attrList->name, PAL_T("TYPE")) == 0)
        {
            result = _StringToMiType(attrList->value, type);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("METHOD"), attrList->name);
            typeExists = MI_TRUE;
        }
        else if (Tcscmp(attrList->name, PAL_T("CLASSORIGIN")) == 0)
        {
            *classOrigin = attrList->value;
        }
        else if (Tcscmp(attrList->name, PAL_T("PROPAGATED")) == 0)
        {
            //Ignore?
            MI_Boolean boolValue;
            result = _StringToMiBool(attrList->value, &boolValue);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("METHOD"), attrList->name);
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("METHOD"), attrList->name);
        }

        attrList = attrList->next;
    }
    if (!typeExists)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("METHOD"), PAL_T("TYPE"));
    }
    if (!*name)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("METHOD"), PAL_T("NAME"));
    }
    return MI_RESULT_OK;
}
_Check_return_ static MI_Result _ExtractMethodParameterAttribute(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList, 
    _Outptr_result_z_ const MI_Char **name, 
    _Out_ MI_Type *type)
{
    MI_Result result;
    MI_Boolean typeExists = MI_FALSE;

    *name = NULL;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!typeExists && Tcscmp(attrList->name, PAL_T("TYPE")) == 0)
        {
            result = _StringToMiType(attrList->value, type);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PARAMETER"), PAL_T("TYPE"));
            typeExists = MI_TRUE;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("PARAMETER"), attrList->name);
        }

        attrList = attrList->next;
    }
    if (!*name)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PARAMETER"), PAL_T("NAME"));
    }
    if (!typeExists)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PARAMETER"), PAL_T("TYPE"));
    }
    return MI_RESULT_OK;
}
_Check_return_ static MI_Result _ExtractMethodParameterArrayAttribute(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList, 
    _Outptr_result_z_ const MI_Char **name, 
    _Out_ MI_Type *type,
    _Out_ MI_Uint32 *maxArraySize)
{
    MI_Result result;
    MI_Boolean typeFound = MI_FALSE;

    *name = NULL;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!typeFound && Tcscmp(attrList->name, PAL_T("TYPE")) == 0)
        {
            result = _StringToMiType(attrList->value, type);
            if (result != MI_RESULT_OK)
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PARAMETER.ARRAY"), PAL_T("TYPE"));
            typeFound = MI_TRUE;
        }
        else if (Tcscmp(attrList->name, PAL_T("ARRAYSIZE")) == 0)
        {
            MI_Char *tmpEnd = (MI_Char*)attrList->value;

            *maxArraySize = Tcstoul(attrList->value, &tmpEnd, 10);

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26018, "Esp:692")
#endif
            if ((*tmpEnd) != PAL_T('\0'))
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PARAMETER.ARRAY"), PAL_T("ARRAYSIZE"));
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("PARAMETER.ARRAY"), attrList->name);
        }

        attrList = attrList->next;
    }
    if (!*name)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PARAMETER.ARRAY"), PAL_T("NAME"));
    if (!typeFound)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PARAMETER.ARRAY"), PAL_T("TYPE"));

    return MI_RESULT_OK;
}

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:6001)
#endif

_Check_return_ static MI_Result _ExtractMethodParameterReferenceAttribute(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Attr *attrList,
    _Outptr_result_z_ const MI_Char **name,
    _Outptr_result_maybenull_z_ const MI_Char **refClassname,
    _Out_ MI_Uint32 *maxArraySize)
{

    *name = NULL;
    *refClassname = NULL;
    *maxArraySize = 0;

    while (attrList)
    {
        if (!*name && Tcscmp(attrList->name, PAL_T("NAME")) == 0)
        {
            *name = attrList->value;
        }
        else if (!*refClassname && Tcscmp(attrList->name, PAL_T("REFERENCECLASS")) == 0)
        {
            *refClassname = attrList->value;
        }
        else if (Tcscmp(attrList->name, PAL_T("ARRAYSIZE")) == 0)
        {
            MI_Char *tmpEnd = (MI_Char*)attrList->value;

            *maxArraySize = Tcstoul(attrList->value, &tmpEnd, 10);

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 26018, "Esp:692")
#endif
            if ((*tmpEnd) != PAL_T('\0'))
#ifdef _PREFAST_
#pragma prefast(pop)
#endif
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("PARAMETER.REFERENCE"), PAL_T("ARRAYSIZE"));
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("PARAMETER.REFERENCE"), attrList->name);
        }
        attrList = attrList->next;
    }
    if (!*name) // refClassname is optional (for weak reference type)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("PARAMETER.ARRAY"), PAL_T("NAME"));

    return MI_RESULT_OK;
}

#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

_Check_return_ MI_Result XmlDeserializer_AddMethodParameterQualifier(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *cursorElem, 
    MI_Uint32 methodId, 
    MI_Uint32 parameterId)
{
    MI_Result result;
    const MI_Char *name;
    MI_Type type;
    MI_Uint32 flavor;
    MI_Value value;
    MI_Boolean isArray;
    MI_Uint32 arrayCount;

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 6054)
#endif
    result = _ExtractQualifierAttributes(state, cursorElem, &name, &type, &flavor, &value, &isArray, &arrayCount);
#ifdef _PREFAST_
#pragma prefast(pop)    
#endif
    if (result != MI_RESULT_OK)
        return result;

    if (isArray)
    {
        MI_Uint32 qualifierId;

        result = Class_AddMethodParameterQualifierArray(finalClass, methodId, parameterId, name, type, flavor, arrayCount, &qualifierId);
        if (result != MI_RESULT_OK)
        {
            return result;
        }

        cursorElem = cursorElem->child_first->child_first;
        while (cursorElem)
        {
            if (Tcscmp(PAL_T("VALUE"), cursorElem->name) != 0)
            {
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("QUALIFIER"), cursorElem->name);
            }
            else if ((cursorElem->value_first == NULL) || 
                (cursorElem->value_first->value == NULL))
            {
                if (type == MI_STRING)
                {
                    value.string = NULL;
                }
                else
                {
                    //
                    return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_EMPTY_VAL_NOT_STRING);
                }
            }
            else
            {
                result = _StringToMiValue(NULL, cursorElem->value_first->value, type, &value);
                if (result != MI_RESULT_OK)
                    return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("PARAMETER QUALIFIER"));;
            }
            result = Class_AddMethodParameterQualifierArrayItem(finalClass, methodId, parameterId, qualifierId, value);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
            cursorElem = cursorElem->sibling_next;
        }
    }
    else
    {
        //Plain non-array value
        return Class_AddMethodParameterQualifier(finalClass, methodId, parameterId, name, type, value, flavor);
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddMethodParameter(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *paramElem, 
    MI_Uint32 methodId)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = paramElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *embeddedClassName = NULL;
    MI_Type type;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 parameterId;

    /* Extract attributes */
    result = _ExtractMethodParameterAttribute(state, paramElem->attr_first, &name, &type);
    if (result != MI_RESULT_OK)
        return result;

    //count qualifiers
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //If embedded instance/object then we need to overload the type
            if (currentElem->attr_first &&
                (Tcscmp(currentElem->attr_first->name, PAL_T("NAME"))==0))
            {
                if ((Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDINSTANCE"))==0) &&
                    currentElem->child_first &&
                    (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
                    currentElem->child_first->value_first)
                    
                {
                    embeddedClassName = currentElem->child_first->value_first->value;
                    type = MI_INSTANCE;
                }
                else if (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDOBJECT"))==0)
                {
                    type = MI_INSTANCE;
                }
            }
            numberQualifiers++;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("METHOD PARAMETER"), currentElem->name);
        }
        currentElem = currentElem->sibling_next;
    }

    //Add parameter
    //TODO: Flags = ???
    result = Class_AddMethodParameter(finalClass, methodId, name, embeddedClassName, type, 0, 0, numberQualifiers, &parameterId);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Add parameter qualifiers
    currentElem = paramElem->child_first;
    while (currentElem)
    {
        //Already validated only qualifiers exist
        result = XmlDeserializer_AddMethodParameterQualifier(state, finalClass, currentElem, methodId, parameterId);
        if (result != MI_RESULT_OK)
            return result;

        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddMethodParameterArray(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *paramElem, 
    MI_Uint32 methodId)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = paramElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *embeddedClassName = NULL;
    MI_Type type;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 parameterId;
    MI_Uint32 maxArraySize = 0;

    /* Extract attributes */
    result = _ExtractMethodParameterArrayAttribute(state, paramElem->attr_first, &name, &type, &maxArraySize);
    if (result != MI_RESULT_OK)
        return result;

    type = (MI_Type)( type | 0x10);   //convert type to array

    //count qualifiers
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            {
                if ((Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDINSTANCE"))==0) &&
                    currentElem->child_first &&
                    (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
                    currentElem->child_first->value_first)
                    
                {
                    embeddedClassName = currentElem->child_first->value_first->value;
                    type = MI_INSTANCEA;
                }
                else if (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDOBJECT"))==0)
                {
                    type = MI_INSTANCEA;
                }
            }
            numberQualifiers++;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("METHOD PARAMETER.ARRAY"), currentElem->name);
        }
        currentElem = currentElem->sibling_next;
    }

    //Add parameter
    //TODO: Flags = ???
    result = Class_AddMethodParameter(finalClass, methodId, name, embeddedClassName, type, 0, maxArraySize, numberQualifiers, &parameterId);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Add parameter qualifiers
    currentElem = paramElem->child_first;
    while (currentElem)
    {
        //Already validated that we only have qualifiers
        result = XmlDeserializer_AddMethodParameterQualifier(state, finalClass, currentElem, methodId, parameterId);
        if (result != MI_RESULT_OK)
            return result;

        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

// flags == 0 means PARAMETER.REFARRAY
// flags == 1 means PARAMETER.REFERENCE
_Check_return_ MI_Result XmlDeserializer_AddMethodParameterReference(
    _In_ const DeserializationData *state,
    _Inout_ MI_Class *finalClass, 
    _In_ XMLDOM_Elem *paramElem, 
    MI_Uint32 methodId, 
    MI_Uint32 flags)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = paramElem->child_first;
    const MI_Char *name = NULL;
    const MI_Char *refClassname = NULL;
    MI_Uint32 maxArraySize = 0;
    MI_Type type;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 parameterId;

    if (flags != 0 && flags != 1)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    type = (flags == 0) ? MI_REFERENCEA : MI_REFERENCE;

    /* Extract attributes */
    result = _ExtractMethodParameterReferenceAttribute(state, paramElem->attr_first, &name, &refClassname, &maxArraySize);
    if (result != MI_RESULT_OK)
        return result;

    //count qualifiers
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            numberQualifiers++;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("METHOD PARAMETER.REFERENCE"), currentElem->name);
        }
        currentElem = currentElem->sibling_next;
    }

    //Add parameter
    //TODO: Flags = ???
    result = Class_AddMethodParameter(finalClass, methodId, name, refClassname, type, 0, maxArraySize, numberQualifiers, &parameterId);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Add parameter qualifiers
    currentElem = paramElem->child_first;
    while (currentElem)
    {
        //Already validated only have qualifiers
        result = XmlDeserializer_AddMethodParameterQualifier(state, finalClass, currentElem, methodId, parameterId);
        if (result != MI_RESULT_OK)
            return result;

        currentElem = currentElem->sibling_next;
    }
    return MI_RESULT_OK;
}

_Check_return_ MI_Result XmlDeserializer_AddClassMethod(_In_ const DeserializationData *state, _Inout_ MI_Class *finalClass, _In_ const XMLDOM_Elem *methodElement)
{
    MI_Result result;
    XMLDOM_Elem *currentElem = methodElement->child_first;
    const MI_Char *name = NULL;
    const MI_Char *classOrigin = NULL;
    const MI_Char *embeddedClassName = NULL;
    MI_Type type = MI_BOOLEAN;
    MI_Uint32 numberQualifiers = 0;
    MI_Uint32 numberParameters = 1; //Note that we always have a return type and it is stored as a parameter!
    MI_Uint32 methodId = 0;
    MI_Uint32 returnParameterIndex;
    MI_Boolean overridden = MI_FALSE;

    /* Extract attributes */
    result = _ExtractMethodAttributes(state, methodElement->attr_first, &name, &type, &classOrigin);
    if (result != MI_RESULT_OK)
        return result;

    //Calculate the method qualifier and property count
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            //If embedded instance/object then we need to overload the type
            if (currentElem->attr_first &&
                (Tcscmp(currentElem->attr_first->name, PAL_T("NAME"))==0))
            {
                if ((Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDINSTANCE"))==0) &&
                    currentElem->child_first &&
                    (Tcscmp(currentElem->child_first->name, PAL_T("VALUE"))==0) &&
                    currentElem->child_first->value_first)
                {
                    embeddedClassName = currentElem->child_first->value_first->value;
                    type = MI_INSTANCE;
                }
                else if (Tcscasecmp(currentElem->attr_first->value, PAL_T("EMBEDDEDOBJECT"))==0)
                {
                    type = MI_INSTANCE;
                }
            }
            else
            {
                result = ProcessOverrideQualifier(state, currentElem, PAL_T("METHOD"), &overridden);
                if(result != MI_RESULT_OK)
                    return result;
            }
            
            numberQualifiers++;
        }
        else if ((Tcscmp(currentElem->name, PAL_T("PARAMETER")) == 0) ||
                 (Tcscmp(currentElem->name, PAL_T("PARAMETER.REFERENCE")) == 0) ||
                 (Tcscmp(currentElem->name, PAL_T("PARAMETER.ARRAY")) == 0) ||
                 (Tcscmp(currentElem->name, PAL_T("PARAMETER.REFARRAY")) == 0))
        {
            numberParameters++;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("METHOD"), currentElem->name);
        }
        currentElem = currentElem->sibling_next;
    }

    if(ShouldFilterElementForCurrentClass(state, classOrigin, overridden))
        return MI_RESULT_OK;

    //TODO: flags(parameter 3 to Class_AddMethod)?
    result = Class_AddMethod(finalClass, name, 0, numberParameters, numberQualifiers, &methodId);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //TODO: If the return type is an array then we need to know what that length is
    result = Class_AddMethodParameter(finalClass, methodId, PAL_T("MIReturn"), embeddedClassName, type, 0, 0, 0, &returnParameterIndex);

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Now add method qualifiers and parameters
    currentElem = methodElement->child_first;
    while (currentElem)
    {
        if (Tcscmp(currentElem->name, PAL_T("QUALIFIER")) == 0)
        {
            result = XmlDeserializer_AddMethodQualifier(state, finalClass, currentElem, methodId);
            if (result != MI_RESULT_OK)
                return result;
        }
        else if (Tcscmp(currentElem->name, PAL_T("PARAMETER")) == 0)
        {
            result = XmlDeserializer_AddMethodParameter(state, finalClass, currentElem, methodId);
            if (result != MI_RESULT_OK)
                return result;
        }
        else if (Tcscmp(currentElem->name, PAL_T("PARAMETER.ARRAY")) == 0)
        {
            result = XmlDeserializer_AddMethodParameterArray(state, finalClass, currentElem, methodId);
            if (result != MI_RESULT_OK)
                return result;
        }
        else if (Tcscmp(currentElem->name, PAL_T("PARAMETER.REFERENCE")) == 0)
        {
            result = XmlDeserializer_AddMethodParameterReference(state, finalClass, currentElem, methodId, 1);
            if (result != MI_RESULT_OK)
                return result;
        }
        else if (Tcscmp(currentElem->name, PAL_T("PARAMETER.REFARRAY")) == 0)
        {
            result = XmlDeserializer_AddMethodParameterReference(state, finalClass, currentElem, methodId, 0);
            if (result != MI_RESULT_OK)
                return result;
        }
        currentElem = currentElem->sibling_next;
    }

    return MI_RESULT_OK;
}


_Check_return_ static MI_Result _StringToMiBool(_In_z_ const MI_Char *string, _Out_ MI_Boolean *boolValue)
{
    if (Tcscasecmp(string, PAL_T("true")) == 0)
    {
        *boolValue = MI_TRUE;
    }
    else if (Tcscasecmp(string, PAL_T("false")) == 0)
    {
        *boolValue = MI_FALSE;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _StringToMiType(_In_z_ const MI_Char *string, _Out_ MI_Type *type)
{
    int i;
    static struct _mapping { MI_Uint32 hash; MI_Char *string;  MI_Type type;  } mapping[] = 
    { 
        {6450695, PAL_T("boolean"), MI_BOOLEAN},
        {6501894, PAL_T("char16"), MI_CHAR16}, 
        {6579464, PAL_T("datetime"), MI_DATETIME},
        {7483910, PAL_T("real32"), MI_REAL32},
        {7484422, PAL_T("real64"), MI_REAL64},
        {7549446, PAL_T("sint32"), MI_SINT32}, 
        {7549958, PAL_T("sint64"), MI_SINT64},
        {7550470, PAL_T("sint16"), MI_SINT16}, 
        {7550981, PAL_T("sint8"), MI_SINT8},
        {7563014, PAL_T("string"), MI_STRING}, 
        {7680518, PAL_T("uint32"), MI_UINT32}, 
        {7681030, PAL_T("uint64"), MI_UINT64},
        {7681542, PAL_T("uint16"), MI_UINT16}, 
        {7682053, PAL_T("uint8"), MI_UINT8}
    };
    MI_Uint32 hash = Hash(string);

    for (i = 0; i != sizeof(mapping)/sizeof(mapping[0]); i++)
    {
        if ((hash == mapping[i].hash) && (Tcscasecmp(mapping[i].string, string)==0))
        {
            *type = mapping[i].type;
            return MI_RESULT_OK;
        }
        else if (hash < mapping[i].hash)
        {
            break;
        }
    }
    return MI_RESULT_INVALID_PARAMETER;
}


_Check_return_ static MI_Result  _StringToMiValue(
    _In_opt_ const DeserializationData *state,
    _In_z_ const MI_Char *str, 
    MI_Type type, 
    _Out_ MI_Value *value)
{
    MI_Result result = MI_RESULT_OK;
    XMLDOM_Doc *xmldoc = NULL;

    if (type == MI_CHAR16)
    {
        //Apparently OSC_StringToMiValue doesn't work so well for char16's!
        value->char16 = str[0];
    }
    else if (type == MI_INSTANCE)
    {
        //OSC_StringToMiValue cannot handle instances as it has no schema information
        MI_Char *endXmlDoc;
        DeserializationData embeddedState;
        memset(&embeddedState, 0, sizeof(embeddedState));
        embeddedState.type = DeserializingInstance;
        embeddedState.clientGetClassCallback = state->clientGetClassCallback;
        embeddedState.clientGetClassCallbackContext = state->clientGetClassCallbackContext;
        embeddedState.errorObject = state->errorObject;
        embeddedState.u.instanceData.classObjects = state->u.instanceData.classObjects;
        embeddedState.u.instanceData.numberClassObjects = state->u.instanceData.numberClassObjects;
        
        if (state->type == DeserializingClass)
        {
            embeddedState.u.instanceData.namespaceName = state->u.classData.namespaceName;
            embeddedState.u.instanceData.serverName = state->u.classData.serverName;
        }
        else
        {
            embeddedState.u.instanceData.declgroupElement = state->u.instanceData.declgroupElement;
            embeddedState.u.instanceData.namespaceName = state->u.instanceData.namespaceName;
            embeddedState.u.instanceData.serverName = state->u.instanceData.serverName;
            memcpy(embeddedState.u.instanceData.foundClasses, state->u.instanceData.foundClasses, sizeof(state->u.instanceData.foundClasses));
            embeddedState.u.instanceData.foundClassesCount = state->u.instanceData.foundClassesCount;
        }

        //Passing in no errorObject as we don't seem to get one here!
        result = XMLDOM_Parse((MI_Char*)str, &endXmlDoc, &xmldoc, NULL);
        if (result != MI_RESULT_OK)
        {
            goto cleanup;
        }
    
        if (xmldoc->root == NULL)
        {
            result = MI_RESULT_INVALID_PARAMETER;
            goto cleanup;
        }
    
        if (Tcscmp(xmldoc->root->name, PAL_T("INSTANCE")) != 0)
        {
            result = MI_RESULT_INVALID_PARAMETER;
            goto cleanup;
        }

        result = XmlDeserializer_DoDeserializeInstance(&embeddedState, xmldoc->root);
        if (result == MI_RESULT_OK)
        {
            //Yeah!  We got our embedded instance.
            value->instance = embeddedState.u.instanceData.instanceResult;
        }

        //Need to delete any cached classes/copy back to owning instance cache
        if (state->type == DeserializingClass)
        {
            //Class so nothing to keep
            while (embeddedState.u.instanceData.foundClassesCount)
            {
                embeddedState.u.instanceData.foundClassesCount--;
                MI_Class_Delete(embeddedState.u.instanceData.foundClasses[embeddedState.u.instanceData.foundClassesCount]);
            }
        }
        else
        {
            //creating from instance so can copy out new cache over the old one
            //and yeah, original was const.  Sorry about that!
            memcpy(((DeserializationData*)state)->u.instanceData.foundClasses, embeddedState.u.instanceData.foundClasses, sizeof(state->u.instanceData.foundClasses));
            ((DeserializationData*)state)->u.instanceData.foundClassesCount = embeddedState.u.instanceData.foundClassesCount;
        }

        FreeNamespaceBuffer(&embeddedState);
    }
    else
    {
        result = StringToMiValue(str, type, value);
    }
cleanup:
    if (xmldoc)
    {
        XMLDOM_Free(xmldoc);
    }
    return result;
}


//Extract the namespace and server from a NAMESPACEPATH node
_Check_return_ static MI_Result _Extract_NAMESPACEPATH(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Elem *namespacePathElem, 
    _Outptr_result_z_ const MI_Char **serverName, 
    _Outptr_result_z_ const MI_Char **namespacePath)
{
    if (namespacePathElem->child_first &&
        (Tcscmp(namespacePathElem->child_first->name, PAL_T("HOST")) == 0) &&
        namespacePathElem->child_first->value_first)
    {
        *serverName = namespacePathElem->child_first->value_first->value;

        if (namespacePathElem->child_first->sibling_next &&
            (Tcscmp(namespacePathElem->child_first->sibling_next->name, PAL_T("LOCALNAMESPACEPATH")) == 0))
        {
            return _Extract_LOCALNAMESPACEPATH(state, namespacePathElem->child_first->sibling_next, namespacePath);
        }
    }
    if (namespacePathElem->child_first &&
        namespacePathElem->child_first->name)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("NAMESPACEPATH"), namespacePathElem->child_first->name);
    }
    else
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("NAMESPACEPATH"), PAL_T(""));
    }
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26053) // Bogus, we really do have the right buffer length for building the namespace
#endif /* _PREFAST_ */

//Extract the namespace from a LOCALNAMESPACEPATH node
_Check_return_ static MI_Result _Extract_LOCALNAMESPACEPATH(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Elem *localNamespacePathElem, 
    _Outptr_result_z_ const MI_Char **namespacePath)
{
    // LOCALNAMESPACEPATH could be like following, need to concat all elements to form the namespace
    //
    //  <LOCALNAMESPACEPATH>
    //      <NAMESPACE NAME="root"/>
    //      <NAMESPACE NAME="interop"/>
    //  </LOCALNAMESPACEPATH>
    XMLDOM_Elem * namespaceElem = localNamespacePathElem->child_first;
    MI_Result r = MI_RESULT_INVALID_PARAMETER;
    MI_Char * pCurrentNamespace;
    MI_Uint32 namespaceBufferLength = 0;
    NameSpaceBufferData * bufferData = (NameSpaceBufferData *)malloc(sizeof(NameSpaceBufferData));
    if (bufferData == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    bufferData->pNext = state->pCurrentNamespaceBufferData;
    ((DeserializationData *)state)->pCurrentNamespaceBufferData = bufferData;
    bufferData->pNamespaceBuffer = NULL;

    // calculate the total namespace length
    while (namespaceElem != NULL)
    {
        if ((Tcscmp(namespaceElem->name, PAL_T("NAMESPACE")) == 0) &&
            namespaceElem->attr_first &&
            (Tcscmp(namespaceElem->attr_first->name, PAL_T("NAME"))==0))
        {
            const MI_Char * tNamespace = namespaceElem->attr_first->value;
            MI_Uint32 tNamespaceLength =   Tcslen(tNamespace);
            if (tNamespaceLength == 0)
            {
                r = MI_RESULT_INVALID_PARAMETER;
                break;
            }
            namespaceBufferLength += (tNamespaceLength + 1); // +1 either for slash or terminator
            if (r != MI_RESULT_OK)
                r = MI_RESULT_OK;
        }
        else
        {
            r = MI_RESULT_INVALID_PARAMETER;
            break;
        }
        namespaceElem = namespaceElem->sibling_next;
    }

    // build the namespace
    if (r == MI_RESULT_OK)
    {
        MI_Uint32 remainNamespaceBufferLength = namespaceBufferLength;
        // restrict if the namespace length is greater than reasonable limit
        if (namespaceBufferLength > NAMESPACE_LIMIT)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }

        bufferData->pNamespaceBuffer = (MI_Char *)malloc(sizeof(MI_Char) * namespaceBufferLength);
        if (bufferData->pNamespaceBuffer == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
        pCurrentNamespace = bufferData->pNamespaceBuffer;
        *pCurrentNamespace = PAL_T('\0');

        namespaceElem = localNamespacePathElem->child_first;
        while (namespaceElem != NULL)
        {
            const MI_Char * tNamespace = namespaceElem->attr_first->value;
            MI_Uint32 tNamespaceLength = Tcslen(tNamespace);
            Tcslcpy(pCurrentNamespace, tNamespace, remainNamespaceBufferLength);
            pCurrentNamespace += tNamespaceLength;
            *pCurrentNamespace = PAL_T('/');
            pCurrentNamespace ++;
            remainNamespaceBufferLength -= (tNamespaceLength + 1);

            // next namespace item
            namespaceElem = namespaceElem->sibling_next;
        }

        // set output parameter
        pCurrentNamespace --;
        *pCurrentNamespace = PAL_T('\0');
        *namespacePath = bufferData->pNamespaceBuffer;
        return r;
    }

    if (localNamespacePathElem->child_first)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("LOCALNAMESPACEPATH"), localNamespacePathElem->child_first->name);
    }
    else
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_HAS_NO_CHILDREN, PAL_T("LOCALNAMESPACEPATH"));
    }
}
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

_Check_return_ static MI_Result _Extract_INSTANCEPATH(
    _In_ const DeserializationData *state, 
    _In_ XMLDOM_Elem *refChildElem, 
    _Outptr_ MI_Instance **instanceRef)
{
    MI_Result result;
    const MI_Char *serverName = NULL; 
    const MI_Char *namespaceName = NULL;
    XMLDOM_Elem *node = refChildElem->child_first;
    XMLDOM_Elem *instanceNameNode = NULL;

    while (node)
    {
        if ((serverName == NULL) && (namespaceName == NULL) && (Tcscmp(node->name, PAL_T("NAMESPACEPATH"))==0))
        {
            result = _Extract_NAMESPACEPATH(state, node, &serverName, &namespaceName);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
        }
        else if ((instanceNameNode == NULL) && (Tcscmp(node->name, PAL_T("INSTANCENAME")) == 0))
        {
            instanceNameNode = node;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("INSTANCEPATH"), node->name);
        }
        
        node = node->sibling_next;
    }
    if (!serverName || !namespaceName)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ELEM, PAL_T("INSTANCEPATH"), PAL_T("NAMESPACEPATH"));
    }
    if (!instanceNameNode)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ELEM, PAL_T("INSTANCEPATH"), PAL_T("INSTANCENAME"));
    }

    result = _Extract_INSTANCENAME(state, instanceNameNode, serverName, namespaceName, instanceRef);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    result = MI_Instance_SetServerName(*instanceRef, serverName);
    if (result != MI_RESULT_OK)
    {
        MI_Instance_Delete(*instanceRef);
        *instanceRef = NULL;

        return result;
    }
    result = MI_Instance_SetNameSpace(*instanceRef, namespaceName);
    if (result != MI_RESULT_OK)
    {
        MI_Instance_Delete(*instanceRef);
        *instanceRef = NULL;

        return result;
    }

    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _Extract_LOCALINSTANCEPATH(
    _In_ const DeserializationData *state, 
    _In_ XMLDOM_Elem *refChildElem, 
    _Outptr_ MI_Instance **instanceRef)
{
    MI_Result result;
    const MI_Char *serverName = NULL;   //TODO: Need to get the default namespace from caller
    const MI_Char *namespaceName = NULL;
    XMLDOM_Elem *node = refChildElem->child_first;
    XMLDOM_Elem *instNameNode = NULL;

    while (node)
    {
        if ((namespaceName == NULL) && (Tcscmp(node->name, PAL_T("LOCALNAMESPACEPATH"))==0))
        {
            result = _Extract_LOCALNAMESPACEPATH(state, node, &namespaceName);
            if (result != MI_RESULT_OK)
            {
                return result;
            }
        }
        else if (!instNameNode && (Tcscmp(node->name, PAL_T("INSTANCENAME")) == 0))
        {
            instNameNode = node;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("LOCALINSTANCEPATH"), node->name);
        }
        
        node = node->sibling_next;
    }
    if (!namespaceName)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ELEM, PAL_T("LOCALINSTANCEPATH"), PAL_T("LOCALNAMESPACEPATH"));
    }

    if (!instNameNode)
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ELEM, PAL_T("LOCALINSTANCEPATH"), PAL_T("INSTANCENAME"));
    }

    result = _Extract_INSTANCENAME(state, instNameNode, serverName, namespaceName, instanceRef);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    result = MI_Instance_SetNameSpace(*instanceRef, namespaceName);
    if (result != MI_RESULT_OK)
    {
        MI_Instance_Delete(*instanceRef);
        *instanceRef = NULL;
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    return MI_RESULT_OK;
}

_Check_return_ static MI_Result _Extract_VALUE_REFERENCE(
_In_ const DeserializationData *state, 
    _In_ XMLDOM_Elem *valueRefElement,
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _Outptr_ MI_Instance **instanceRef)
{
    XMLDOM_Elem *refChildElem = valueRefElement->child_first;
    MI_Result result = MI_RESULT_INVALID_PARAMETER;

    if (refChildElem == NULL)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_HAS_NO_CHILDREN, valueRefElement->name);

    if (Tcscmp(refChildElem->name, PAL_T("INSTANCEPATH")) == 0)
    {
        result = _Extract_INSTANCEPATH(state, refChildElem, instanceRef);
    }
    else if (Tcscmp(refChildElem->name, PAL_T("LOCALINSTANCEPATH")) == 0)
    {
        result = _Extract_LOCALINSTANCEPATH(state, refChildElem, instanceRef);
    }
    else if (Tcscmp(refChildElem->name, PAL_T("INSTANCENAME")) == 0)
    {
        result = _Extract_INSTANCENAME(state, refChildElem, serverName, namespaceName, instanceRef);
    }
    else if ((Tcscmp(refChildElem->name, PAL_T("CLASSPATH")) == 0) ||
                (Tcscmp(refChildElem->name, PAL_T("LOCALCLASSPATH")) == 0) ||
                (Tcscmp(refChildElem->name, PAL_T("CLASSNAME")) == 0))
    {
        //We do not support references to classes
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_REF_TO_VALUE_NOT_SUPPORTED);
    }
    else
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("VALUE.REFERENCE"), refChildElem->name);
    }
    return result;
}

_Check_return_ static MI_Result _Extract_KEYVALUE(
    _In_ const DeserializationData *state, 
    _In_ XMLDOM_Elem *keyvalueNode,
    _In_z_ const MI_Char *keyPropName,
    _In_ MI_Instance *instanceObject)
{
    //attrib: VALUETYPE='string', 'boolean', 'numeric' -- need to validate with class
    //attrib: %CIMType - implied
    //value: needs to be converted to an MI_Value using the valueType and type in class

    MI_Result result;
    MI_Uint32 propertyIndex = 0;
    MI_Boolean found = MI_FALSE;
    MI_Type type = MI_BOOLEAN;
    const MI_Char *valueType = NULL;
    const MI_Char *cimType = NULL;
    const MI_Char *value = NULL;
    MI_Value miValue;
    XMLDOM_Attr *keyValAttribs = keyvalueNode->attr_first;

    if (keyvalueNode->value_first == NULL)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_VAL_NO_DATA, keyvalueNode->name);

    value = keyvalueNode->value_first->value;

    if (!Instance_IsDynamic(instanceObject))
    {
        for (;propertyIndex != instanceObject->classDecl->numProperties; propertyIndex++)
        {
            if (Tcscasecmp(keyPropName, instanceObject->classDecl->properties[propertyIndex]->name) == 0)
            {
                found = MI_TRUE;
                type = (MI_Type) instanceObject->classDecl->properties[propertyIndex]->type;
                break;
            }
        }
        if (!found)
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_KEYVALUE_FOR_NON_KEY);
    }

    while (keyValAttribs)
    {
        if (!valueType && (Tcscmp(keyValAttribs->name, PAL_T("VALUETYPE")) == 0))
        {
            valueType = keyValAttribs->value;
        }
        else if (!cimType && (Tcscmp(keyValAttribs->name, PAL_T("TYPE")) == 0))
        {
            cimType = keyValAttribs->value;
        }
        else
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_DUP_UNK_ATTR, PAL_T("KEYVALUE"), keyValAttribs->name);
        }
        keyValAttribs = keyValAttribs->next;
    }
    
    if (!valueType)
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("KEYVALUE"), PAL_T("VALUETYPE"));

    if (cimType)
    {
        MI_Type validateType;
        result = _StringToMiType(cimType, &validateType);
        if (result != MI_RESULT_OK)
            return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("KEYVALUE"), PAL_T("TYPE"));

        if (!Instance_IsDynamic(instanceObject) && (validateType != type))
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH);
    }
    if (Tcscmp(valueType, PAL_T("boolean"))==0)
    {
        if (Instance_IsDynamic(instanceObject))
        {
            type = MI_BOOLEAN;
        }
        else if (type != MI_BOOLEAN)
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH);
    }
    else if (Tcscmp(valueType, PAL_T("string"))==0)
    {
        if (Instance_IsDynamic(instanceObject))
        {
            type = MI_STRING;
        }
        else if ((type != MI_STRING) && (type != MI_CHAR16) && (type != MI_DATETIME))
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH);
    }
    else if (Tcscmp(valueType, PAL_T("numeric"))==0)
    {
        if (Instance_IsDynamic(instanceObject))
        {
            type = MI_UINT64;
        }
        else if ((type != MI_UINT8) && (type != MI_SINT8) && (type != MI_UINT16) && (type != MI_SINT16) && 
            (type != MI_UINT32) && (type != MI_SINT32) && (type != MI_UINT64) && (type != MI_SINT64) && 
            (type != MI_REAL32) && (type != MI_REAL64))
        {
            return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH);
        }
    }
    else
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED, PAL_T("KEYVALUE"), PAL_T("VALUETYPE"));
    }

    result = _StringToMiValue(state, value, type, &miValue);
    if (result != MI_RESULT_OK)
        return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED, PAL_T("KEYVALUE"));

    if (Instance_IsDynamic(instanceObject))
    {
        return MI_Instance_AddElement(instanceObject, keyPropName, &miValue, type, MI_FLAG_NOT_MODIFIED);
    }
    else
    {
        return MI_Instance_SetElementAt(instanceObject, propertyIndex, &miValue, type, MI_FLAG_NOT_MODIFIED);
    }
}

_Check_return_ static MI_Result _Extract_INSTANCENAME_simple(
    _In_ const DeserializationData *state, 
    _In_ XMLDOM_Elem *refChildElem,
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_z_ const MI_Char *keyPropName,
    _In_ MI_Instance *refInstance)
{
    MI_Result result = MI_RESULT_INVALID_PARAMETER;

    if (Tcscmp(refChildElem->name, PAL_T("KEYVALUE")) == 0)
    {
        return _Extract_KEYVALUE(state, refChildElem, keyPropName, refInstance); 
    }
    else if (Tcscmp(refChildElem->name, PAL_T("VALUE.REFERENCE")) == 0)
    {
        MI_Value value;

        result = _Extract_VALUE_REFERENCE(state, refChildElem, serverName, namespaceName, &value.reference);
        if (result != MI_RESULT_OK)
        {
            return result;
        }
        if (Instance_IsDynamic(refInstance))
        {
            result = MI_Instance_AddElement(refInstance, keyPropName, &value, MI_REFERENCE, MI_FLAG_ADOPT|MI_FLAG_NOT_MODIFIED);
        }
        else
        {
            result = MI_Instance_SetElement(refInstance, keyPropName, &value, MI_REFERENCE, MI_FLAG_ADOPT|MI_FLAG_NOT_MODIFIED);
        }
        if (result != MI_RESULT_OK)
        {
            MI_Instance_Delete(value.reference);
        }
        return result;
    }
    else
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_CHILD_UNK, PAL_T("INSTANCENAME"), refChildElem->name);
    }
}

_Check_return_ static MI_Result _Extract_INSTANCENAME(
    _In_ const DeserializationData *state,
    _In_ XMLDOM_Elem *instanceNameElem,
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _Outptr_ MI_Instance **refInstance)
{
    MI_Boolean keyBindingFound = MI_FALSE;
    MI_Boolean simpleFound = MI_FALSE;
    MI_Boolean isDynamicInstance = MI_FALSE;
    MI_Class *refClass = NULL;
    const MI_Char *className = NULL;
    MI_Result result;
    XMLDOM_Elem *instNameChildElem;

    XMLDOM_Attr *instanceNameAttribs = instanceNameElem->attr_first;

    if ((instanceNameAttribs == NULL) || 
        (instanceNameAttribs->next) ||
        (Tcscmp(instanceNameAttribs->name, PAL_T("CLASSNAME")) != 0))
    {
        return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("INSTANCENAME"), PAL_T("CLASSNAME"));
    }

    className = instanceNameAttribs->value;

    if (state->type == DeserializingInstance)
    {
        //Can we find the class?
        result = XmlDeserializer_GetInstanceClass(state, state->u.instanceData.declgroupElement, 0, className, namespaceName, serverName, &refClass);
        if ((result != MI_RESULT_OK) && (result != MI_RESULT_NOT_FOUND))
        {
            return result;
        }
    }
    else
    {
        result = MI_RESULT_NOT_FOUND;
    }

    if (result == MI_RESULT_NOT_FOUND)
    {
        // try to get the class from caller
        if (state->clientGetClassCallback == NULL)
        {
            isDynamicInstance = MI_TRUE;
        }
        else
        {
            result = state->clientGetClassCallback(state->clientGetClassCallbackContext, (MI_Char *)serverName, (MI_Char *)namespaceName, (MI_Char *)className, &refClass);
            if (result != MI_RESULT_OK)
            {
                return _CreateErrorObject(state->errorObject, result, ID_MI_DES_XML_INST_CANNOT_FIND_CLASS, className);
            }
        }
    }

    if (isDynamicInstance == MI_FALSE)
    {
        result = Instance_New(refInstance, refClass->classDecl, NULL);
        if (result != MI_RESULT_OK)
        {
            MI_Class_Delete(refClass);
            return result;
        }
    }
    else
    {
        result = Instance_NewDynamic(refInstance, className, MI_FLAG_CLASS, 0);
        if (result != MI_RESULT_OK)
        {
            MI_Class_Delete(refClass);
            return result;
        }
    }

    if (namespaceName)
    {
        result = MI_Instance_SetNameSpace(*refInstance, namespaceName);
        if (result != MI_RESULT_OK)
        {
            MI_Class_Delete(refClass);
            MI_Instance_Delete(*refInstance);
            *refInstance = NULL;
            return result;
        }
    }
    if (serverName)
    {
        result = MI_Instance_SetServerName(*refInstance, serverName);
        if (result != MI_RESULT_OK)
        {
            MI_Class_Delete(refClass);
            MI_Instance_Delete(*refInstance);
            *refInstance = NULL;
            return result;
        }
    }

    instNameChildElem = instanceNameElem->child_first;
    while (instNameChildElem)
    {
        if (!simpleFound && (Tcscmp(instNameChildElem->name, PAL_T("KEYBINDING")) == 0) && instNameChildElem->child_first && !instNameChildElem->child_first->sibling_next)
        {
            //0 or more of these, KEYVALUE|VALUE.REFERENCE inside
            const MI_Char *keyPropName = NULL;  

            if ((instNameChildElem->attr_first == NULL) ||
                (Tcscmp(instNameChildElem->attr_first->name, PAL_T("NAME"))!=0))
            {
                MI_Class_Delete(refClass);
                MI_Instance_Delete(*refInstance);
                *refInstance = NULL;
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_ELEM_MISSING_ATTR, PAL_T("KEYBINDING"), PAL_T("NAME"));
            }

            keyPropName = instNameChildElem->attr_first->value;

            result = _Extract_INSTANCENAME_simple(state, instNameChildElem->child_first, serverName, namespaceName, keyPropName, *refInstance);
            if (result != MI_RESULT_OK)
            {
                MI_Class_Delete(refClass);
                MI_Instance_Delete(*refInstance);
                *refInstance = NULL;
                return result;
            }
            keyBindingFound = MI_TRUE;
        }
        else if (!keyBindingFound && !simpleFound && ((Tcscmp(instNameChildElem->name, PAL_T("KEYVALUE")) == 0) || (Tcscmp(instNameChildElem->name, PAL_T("VALUE.REFERENCE")) == 0)))
        {
            const MI_Char *keyPropName = NULL; 
            MI_Uint32 index = 0;
            if (refClass != NULL)
            {
                for (;index != refClass->classDecl->numProperties; index++)
                {
                    if (refClass->classDecl->properties[index]->flags & MI_FLAG_KEY)
                    {
                        keyPropName = refClass->classDecl->properties[index]->name;
                        break;
                    }
                }
            }
            if (keyPropName == NULL)
            {
                MI_Class_Delete(refClass);
                MI_Instance_Delete(*refInstance);
                *refInstance = NULL;
                return _CreateErrorObject(state->errorObject, MI_RESULT_INVALID_PARAMETER, ID_MI_DES_XML_INSTANCENAME_COULD_NOT_FIND_KEY);
            }
            result = _Extract_INSTANCENAME_simple(state, instNameChildElem, serverName, namespaceName, keyPropName, *refInstance);
            if (result != MI_RESULT_OK)
            {
                MI_Class_Delete(refClass);
                MI_Instance_Delete(*refInstance);
                *refInstance = NULL;
                return result;
            }
            simpleFound = TRUE;
        }
        else
        {
            MI_Class_Delete(refClass);
            MI_Instance_Delete(*refInstance);
            *refInstance = NULL;
            return MI_RESULT_INVALID_PARAMETER;
        }
        instNameChildElem = instNameChildElem->sibling_next;
    }

    MI_Class_Delete(refClass);

    return MI_RESULT_OK;
}

void _ExtractNextTokenFromDerivationString(_In_z_ MI_Char *derivationStringList, _Outptr_result_z_ MI_Char **derivationToken, _Outptr_result_z_ MI_Char **remainingDerivationStringList)
{
    *derivationToken = derivationStringList;
    for (; *derivationStringList != PAL_T('\0') && *derivationStringList != PAL_T(','); derivationStringList++)
    {
    }
    if (*derivationStringList == PAL_T(','))
    {
        *derivationStringList = PAL_T('\0');
        derivationStringList++;
    }
    *remainingDerivationStringList = derivationStringList;
}

_Check_return_ MI_Result XmlDeserializer_GetDerivationParentClass(
    MI_Uint32 flags,
    _In_z_ const MI_Char *className, 
    _In_z_ MI_Char *remainingDerivationNameList, 
    _In_z_ const MI_Char *namespaceName, 
    _In_z_ const MI_Char *serverName, 
    _In_ const XMLDOM_Elem *classNode,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Outptr_ MI_Class **classObject)
{
    MI_Class *parentClass = NULL;
    MI_Result result = MI_RESULT_OK;
    DeserializationData stateData;

    *classObject = NULL;

    //If we have a parent class we need to process that first
    if (*remainingDerivationNameList != PAL_T('\0'))
    {
        MI_Char *parentClassName = NULL;

        _ExtractNextTokenFromDerivationString(remainingDerivationNameList, &parentClassName, &remainingDerivationNameList);

        result = XmlDeserializer_GetDerivationParentClass(flags, parentClassName, remainingDerivationNameList, namespaceName, serverName, classNode, classObjectNeeded, classObjectNeededContext, &parentClass);
        if (result != MI_RESULT_OK)
        {
            return result;
        }
    }

    memset(&stateData, 0, sizeof(stateData));
    stateData.type = DeserializingClass;
    stateData.clientGetClassCallback = classObjectNeeded;
    stateData.clientGetClassCallbackContext = classObjectNeededContext;
    stateData.u.classData.className = className;
    stateData.u.classData.classParent = (MI_Class*)parentClass;
    stateData.u.classData.namespaceName = namespaceName;
    stateData.u.classData.serverName = serverName;
    stateData.u.classData.includeUnknownOrigins = MI_FALSE;   //This implies parent class only and we are that class
    stateData.u.classData.includePropertiesFromAllOrigins = MI_FALSE;

    //Now we have the parent class (if it exists) now we can focus on our properties
    //TODO, how do we tell this to only include properties only from className
    result = XmlDeserializer_DoDeserialization(&stateData, flags, classNode->child_first);

    if (parentClass)
        MI_Class_Delete(parentClass);

    if (result == MI_RESULT_OK)
    {
        *classObject = stateData.u.classData.classResult;
    }

    FreeNamespaceBuffer(&stateData);

    return result;
}

_Success_(1) _Post_equal_to_(miResult)
MI_Result _CreateErrorObject(MI_Instance **errorObject, MI_Result miResult, _In_z_ const MI_Char *errorString, ...)
{

    if ((errorObject == NULL) || (*errorObject != NULL) || (miResult == MI_RESULT_OK))
    {
        return miResult;
    }
    else
    {
        MI_Char formatMsg[MAX_PATH];
        va_list ap;

        memset(&ap, 0, sizeof(ap));

        va_start(ap, errorString);
        if (Vstprintf(formatMsg, MAX_PATH, errorString, ap) > 0)
        {
            OMI_Error *omiErr;
            if (OMI_ErrorFromErrorCode(NULL, miResult, MI_RESULT_TYPE_MI, formatMsg, &omiErr) != MI_RESULT_OK)
            {
                NitsIgnoringError(); // This only fails in out of memory and we are ignoring this particular error on purpose.
            }
            else
            {
                *errorObject = &omiErr->__instance;
            }
        }
        va_end(ap);

        return miResult;
    }
}

// free namespace buffer allocated during Deserialization
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 6001) 
#endif /* _PREFAST_ */
void FreeNamespaceBuffer(_In_ DeserializationData *state)
{
    NameSpaceBufferData * pBufferData = state->pCurrentNamespaceBufferData;
    NameSpaceBufferData * pTempBufferData = NULL;
    state->pCurrentNamespaceBufferData = NULL;
    while (pBufferData != NULL)
    {
        if ((pBufferData->pNamespaceBuffer != NULL))
        {
            free(pBufferData->pNamespaceBuffer);
        }
        pTempBufferData = pBufferData;
        pBufferData = (NameSpaceBufferData *)pBufferData->pNext;
        free(pTempBufferData);
    }
}
#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */
