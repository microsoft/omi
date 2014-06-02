#include "/usr/include/python2.6/Python.h"
#include "structmember.h"
#include "MI.h"
#include "PMI_Instance.c"
#include "PMI_Class.c"
#include <stdlib.h>
#include "datetime.h"

static PyObject *MIError;
static int errorBufferSize = 255;

typedef struct{
    PyObject_HEAD
    MI_Session miSession;

} PMI_Session;


static void PMI_Session_dealloc(PMI_Session *self)
{
   self->ob_type->tp_free((PyObject*) self);
}

static PyObject* PMI_Session_new(PyTypeObject *type)
{
    PMI_Session *self;
	self = (PMI_Session*)type->tp_alloc(type,0);
    MI_Session miSession = MI_SESSION_NULL;
    self ->miSession = miSession;
    return (PyObject *)self;
}

static int PMI_Session_init(PMI_Instance *self)
{
	return 0;
}
static PyMethodDef PMI_Session_methods[];

/* Helper function to convert an MI_Result into a string */
const char *MI_Result_To_String(MI_Result miResult)
{
    static const char *miResultStrings[] = 
    {
        "MI_RESULT_OK",
        "MI_RESULT_FAILED",
        "MI_RESULT_ACCESS_DENIED",
        "MI_RESULT_INVALID_NAMESPACE",
        "MI_RESULT_INVALID_PARAMETER",
        "MI_RESULT_INVALID_CLASS",
        "MI_RESULT_NOT_FOUND",
        "MI_RESULT_NOT_SUPPORTED",
        "MI_RESULT_CLASS_HAS_CHILDREN",
        "MI_RESULT_CLASS_HAS_INSTANCES",
        "MI_RESULT_INVALID_SUPERCLASS",
        "MI_RESULT_ALREADY_EXISTS",
        "MI_RESULT_NO_SUCH_PROPERTY",
        "MI_RESULT_TYPE_MISMATCH",
        "MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED",
        "MI_RESULT_INVALID_QUERY",
        "MI_RESULT_METHOD_NOT_AVAILABLE",
        "MI_RESULT_METHOD_NOT_FOUND",
        "MI_RESULT_NAMESPACE_NOT_EMPTY",
        "MI_RESULT_INVALID_ENUMERATION_CONTEXT",
        "MI_RESULT_INVALID_OPERATION_TIMEOUT",
        "MI_RESULT_PULL_HAS_BEEN_ABANDONED",
        "MI_RESULT_PULL_CANNOT_BE_ABANDONED",
        "MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED",
        "MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED",
        "MI_RESULT_SERVER_LIMITS_EXCEEDED",
        "MI_RESULT_SERVER_IS_SHUTTING_DOWN"
    };

    if (miResult < sizeof(miResultStrings)/sizeof(miResultStrings[0]))
    {
        return miResultStrings[miResult];
    }
    else
    {
        return "Unknown MI_Result";
    }
}

MI_Result TestConnection(MI_Session *miSession)
{
    MI_Result miResult;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
    const MI_Instance *miInstance = NULL;
	MI_Operation miOperation = MI_OPERATION_NULL;

	MI_Session_TestConnection(miSession,0,NULL,&miOperation);   
    _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
	return miResult;        
}



static PyObject* EnumerateInstances(PyObject* self, PyObject* args) 
{
    char *nameSpace,*className;

    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"ss",&nameSpace,&className))
    {
		PyErr_SetString(MIError,"Please input correct nameSpace and className");
		return NULL;
    }

    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult;
    MI_Boolean moreResults;
    const MI_Char* errorString = NULL;
    const MI_Instance *errorDetails = NULL;
    MI_Result _miResult;
   
    MI_Session_EnumerateInstances(&miSession,0, NULL, nameSpace,className, MI_FALSE, NULL, &miOperation);
    PyObject* instances = PyList_New(0);
    do
    {
		const MI_Instance *miInstance;
		MI_Result _miResult;
        _miResult = MI_Operation_GetInstance(&miOperation,&miInstance,&moreResults,&miResult,&errorString,&errorDetails);
	
		if(_miResult != MI_RESULT_OK)
		{
			/* Make sure the string buffer is big enough */
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, error = ");
			strcat(error,MI_Result_To_String(_miResult));
	    	PyErr_SetString(MIError,error);
	    	return NULL;
		}
		if(miInstance)
		{
	   		PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
			/*The miInstance won't exist once the operation is closed.*/
	    	MI_Instance *cloneInstance;
	    	MI_Instance_Clone(miInstance,&cloneInstance);
	    	pmiInstance-> miInstance = cloneInstance;
			MakePropertyDict(pmiInstance);
	    	PyList_Append(instances, (PyObject *)pmiInstance);
		}
    }while (miResult == MI_RESULT_OK && moreResults ==MI_TRUE);

    if(miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"Operation failed, error = ");
		strcat(error,MI_Result_To_String(miResult));
		if(errorString != NULL)
		{
			strcat(error,", errorMessage = ");
			strcat(error,errorString);
		}
		PyErr_SetString(MIError,error); 		
		return NULL;
    }
    
    _miResult = MI_Operation_Close(&miOperation);
    
    if(_miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
    } 
    Py_INCREF(instances);
    return (PyObject *)instances;
}


static PyObject *CreateInboundInstance(MI_Session* miSession, const MI_Char *namespaceName, const MI_Char *className, MI_Boolean keysOnly, const MI_Instance **inboundInstance, PyObject *propertyDict)
{
    MI_Operation miOperation = MI_OPERATION_NULL;
    const MI_Class *miClass = NULL;
    MI_Boolean moreResults;
    MI_Result miResult = 0;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_Instance *miInstance = NULL;
    MI_Uint32 numberElements = 0;
    MI_Uint32 elementIndex;

    *inboundInstance = NULL;

	MI_Session_GetClass(miSession, 0, NULL, namespaceName, className, NULL, &miOperation);
	MI_Operation_GetClass(&miOperation, &miClass, &moreResults, &miResult, &errorMessage, &completionDetails);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"Failed to retrieve class declaration");
		return NULL;
	}
	
	miResult = MI_Session_GetApplication(miSession, &miApplication);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"Failed to get the parent application of the session");
		goto failedGetClass;
	}

	miResult = MI_Application_NewInstance(&miApplication,className,NULL,&miInstance);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"Failed to create an instance");
		goto failedGetClass;
	}
	
	miResult = MI_Class_GetElementCount(miClass, &numberElements);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"Failed to get element count from class");
		goto failedGetClass;
	}
	
	for (elementIndex = 0; elementIndex != numberElements; elementIndex++)
    {
        const MI_Char *elementName;
        MI_Type elementType;
        MI_Uint32 elementFlags;
   
        miResult = MI_Class_GetElementAt(miClass, elementIndex, &elementName, NULL, NULL, &elementType, NULL, NULL, &elementFlags);
        if (miResult != MI_RESULT_OK)
        {
            PyErr_SetString(MIError,"Failed to get element details from class");
            goto failedGetClass;
        }

        if (keysOnly && ((elementFlags & MI_FLAG_KEY) == 0))
        {
            continue;
        }
		//Iterate the dictionary and add property values to the instance
		PyObject *key, *value;
		Py_ssize_t pos = 0;
		while (PyDict_Next(propertyDict, &pos, &key, &value))
		{
			MI_Value miValue;
			char *propertyName;
			PyObject *propertyValue;
			//need to check if the value is array of single instance
			if(!PyArg_Parse(key,"s",&propertyName))
				return Py_BuildValue("s","property name not correct");
			if(!PyArg_Parse(value,"O",&propertyValue))
				return Py_BuildValue("s","property value not correct");

			if(strcmp(propertyName,elementName)==0)
			{
			    SetPropertyValues(elementType,propertyValue, &miValue);
			    miResult = MI_Instance_AddElement(miInstance,elementName,&miValue,elementType,elementFlags);
			    if(miResult != MI_RESULT_OK)
    			{
					PyErr_SetString(MIError,"MI_Instance_SetElement failed");
					return NULL;
    			}
			}
		}   
    }

failedGetClass:

	if ((miResult != MI_RESULT_OK) && miInstance)
    {
        MI_Result _tmpResult = MI_Instance_Delete(miInstance);
        if (_tmpResult != MI_RESULT_OK)
        {
            PyErr_SetString(MIError,"Failed to delete key instance");
			return NULL;
        }
    }

    {
        MI_Result _tmpResult = MI_Operation_Close(&miOperation);
        if (_tmpResult != MI_RESULT_OK)
        {
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_Close failed, error =");
			strcat(error,MI_Result_To_String(_tmpResult));
            PyErr_SetString(MIError,error);
			return NULL;
        }
    }
        
    if (miResult == MI_RESULT_OK)
    {
        *inboundInstance = miInstance;
    }
	
    return NULL;	
}




static PyObject *GetInstance(PyObject *self, PyObject *args)
{
    char *nameSpace,*className;
    PyObject *propertyDict;
    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"ssO!",&nameSpace,&className,&PyDict_Type, &propertyDict))
    {
		PyErr_SetString(MIError,"Please input correct nameSpace and className");
		return NULL;
    }

    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
    const MI_Instance *miInstance = NULL;
    const MI_Instance *keyInstance = NULL;

    CreateInboundInstance(&miSession, nameSpace, className, MI_TRUE, &keyInstance, propertyDict);
    MI_Session_GetInstance(&miSession,0,NULL,nameSpace,keyInstance,NULL,&miOperation);
   
    do
    {
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
        if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
				char error[errorBufferSize];
				strcpy(error,"Operation failed, error =");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");
					strcat(error,errorMessage);
				}
            	PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miInstance)
            {
                PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
				MI_Instance *cloneInstance;
				MI_Instance_Clone(miInstance,&cloneInstance);				
	    		pmiInstance-> miInstance = cloneInstance;
				MakePropertyDict(pmiInstance);
				return (PyObject *)pmiInstance;	
            }
            else if (moreResults == MI_TRUE)
            {
                PyErr_SetString(MIError,"More results are due and we have no instance, we will keep trying!\n");
				return NULL;
            }
        }
    } while (moreResults == MI_TRUE);
	
	_miResult = MI_Operation_Close(&miOperation);
	if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}	

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *ModifyInstances(PyObject *self, PyObject *args)
{
    MI_Char *nameSpace;
    PyObject *instance;
    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"sO",&nameSpace,&instance))
    {
		PyErr_SetString(MIError,"Please input correct nameSpace and instance");
		return NULL;
    }

	PMI_Instance *pmiInstance = (PMI_Instance *)instance;
    const MI_Instance *modifyInstance;
    modifyInstance = pmiInstance->miInstance;
	MI_Result miResult;


    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
	const MI_Instance *miInstance = NULL;

	MI_Session_ModifyInstance(&miSession, 0, NULL, nameSpace, modifyInstance, NULL, &miOperation);
	do
    {
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
        if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
				char error[errorBufferSize];
				strcpy(error,"Get operation failed to retrieve the instance to modify,error = ");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");				
					strcat(error,errorMessage);
				}		            	
				PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miInstance)
            {
            	PMI_Instance* pmiInstance = (PMI_Instance*) initPMI();
				MI_Instance *cloneInstance;
				MI_Instance_Clone(miInstance,&cloneInstance);
				pmiInstance->miInstance = cloneInstance;
		    	MakePropertyDict(pmiInstance);
	        	return (PyObject *)pmiInstance;
            }
            else if (moreResults == MI_TRUE)
            {
                PyErr_SetString(MIError,"More results are due and we have no instance, we will keep trying!\n");
				return NULL;
            }
        }
    } while (moreResults == MI_TRUE);

	_miResult = MI_Operation_Close(&miOperation);
	if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close, error = ");
		strcat(error,MI_Result_To_String(miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}
	Py_INCREF(Py_None);
	return Py_None;
}


static PyObject *CreateInstance(PyObject *self, PyObject *args)
{
	//first get the instance, then modify its properties
	char *nameSpace;
    PyObject *instance;
    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"sO",&nameSpace,&instance))
    {
		PyErr_SetString(MIError,"Please input correct nameSpace and instance");
		return NULL;
    }

	PMI_Instance *pmiInstance = (PMI_Instance *)instance;
    const MI_Instance *createInstance;
    createInstance = pmiInstance->miInstance;

    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
	const MI_Instance *miInstance = NULL;

	MI_Session_CreateInstance(&miSession, 0, NULL, nameSpace, createInstance, NULL, &miOperation);
	do
    {
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
        if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
				char error[errorBufferSize];
				strcpy(error,"Get operation failed to retrieve the instance to create,error =");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");
					strcat(error,errorMessage);
				}
            	PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miInstance)
            {
	            PMI_Instance* pmiInstance = (PMI_Instance*) initPMI();
				MI_Instance *cloneInstance;
				MI_Instance_Clone(miInstance,&cloneInstance);
				pmiInstance->miInstance = cloneInstance;				
				MakePropertyDict(pmiInstance);
	        	return (PyObject *)pmiInstance;
            }
            else if (moreResults == MI_TRUE)
            {
                PyErr_SetString(MIError,"More results are due and we have no instance, we will keep trying!\n");
				return NULL;
            }
        }
    } while (moreResults == MI_TRUE);

	_miResult = MI_Operation_Close(&miOperation);
	if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}
	Py_INCREF(Py_None);
	return Py_None;
	
}


static PyObject *DeleteInstance(PyObject *self, PyObject *args)
{
    const MI_Instance *deleteInstance;
    
    char *nameSpace,*className;
    PyObject *propertyDict;
    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"ssO!",&nameSpace,&className,&PyDict_Type, &propertyDict))
    {
		PyErr_SetString(MIError, "namespace and classname are not provided");
		return NULL;
    }

    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
	
    CreateInboundInstance(&miSession, nameSpace, className, MI_TRUE, &deleteInstance, propertyDict);
    MI_Session_DeleteInstance(&miSession, 0, NULL, nameSpace, deleteInstance, NULL, &miOperation);
   	MI_Result miResult;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;    const MI_Instance *completionDetails = NULL;
	const MI_Instance *miInstance = NULL;
	
	do
    {
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
		if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
				char error[errorBufferSize];
				strcpy(error,"Get operation failed to retrieve the instance to delete, error = ");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");
					strcat(error,errorMessage);
				}
            	PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miInstance)
            {
                PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
				MI_Instance *cloneInstance;
				MI_Instance_Clone(miInstance,&cloneInstance);	    		
				pmiInstance-> miInstance = cloneInstance;
				MakePropertyDict(pmiInstance);
				return (PyObject *)pmiInstance;	
            }
            else if (moreResults == MI_TRUE)
            {
                PyErr_SetString(MIError,"More results are due and we have no instance, we will keep trying!\n");
				return NULL;
            }
            
        }
    } while (moreResults == MI_TRUE);
	
	_miResult = MI_Operation_Close(&miOperation);
	if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *Invoke(PyObject *self, PyObject *args, PyObject *kwds)
{
    char *nameSpace, *className, *methodName;
    PyObject *argList = NULL;
    PyObject *instance = NULL;
    static char *kwlist[] = {"nameSpace","methodName","className","argList","instance",NULL};
    if(!PyArg_ParseTupleAndKeywords(args,kwds, "ss|sOO",kwlist, &nameSpace,&methodName, &className,&argList, &instance))
    {
		PyErr_SetString(MIError,"Please input the correct arguments for invoke operation");
		return NULL;
    }
 	const MI_Instance *methodInstance = NULL;
	MI_Result miResult;
	if(instance != Py_None && (instance != NULL))
	{
		PMI_Instance *pmiInstance = (PMI_Instance *)instance;
		methodInstance = pmiInstance->miInstance;
		const MI_Char *classDecl;
		miResult = 	MI_Instance_GetClassName(methodInstance,&classDecl);
		if(miResult != MI_RESULT_OK)
		{
			PyErr_SetString(MIError,"MI_Instance_GetClassName failed");
			return NULL;
		}
		className = (char *)classDecl;
	}

	if(className == NULL || strlen(className)==0)
	{
		PyErr_SetString(MIError,"Please input the correct classname");
		return NULL;
	}

    PMI_Session *session = (PMI_Session*) self;
    MI_Session miSession = session->miSession;
    MI_Application miApplication = MI_APPLICATION_NULL;   
    MI_Operation miOperation = MI_OPERATION_NULL; 
    

    miResult = MI_Session_GetApplication(&miSession,&miApplication);
    if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"MI_Session_GetApplication failed");
		return NULL;
	}

    /*Create the instance of arguments */
    const MI_Instance *inboundMethodParameters = NULL;
	if(argList!=NULL)
	{
		CreateInboundInstance(&miSession,nameSpace,className,MI_FALSE,&inboundMethodParameters,argList);
	}

    MI_Session_Invoke(&miSession, 0, NULL, nameSpace, className, methodName, methodInstance,inboundMethodParameters, NULL, &miOperation);

    MI_Result _miResult;
    const MI_Char *errorMessage;
    MI_Boolean moreResults;
    const MI_Instance *completionDetails;
    do
    {
    	const MI_Instance *miInstance;
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
		if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
				char error[errorBufferSize];
				strcpy(error,"Get operation failed to retrive the instance to invoke,error =");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");
					strcat(error,errorMessage);
				}
            	PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miInstance)
            {
                PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
				MI_Instance *cloneInstance;
				MI_Instance_Clone(miInstance,&cloneInstance);
	    		pmiInstance-> miInstance = cloneInstance;				
				MakePropertyDict(pmiInstance);
				return (PyObject *)pmiInstance;
            }
        }
    } while (moreResults == MI_TRUE);
    
     _miResult = MI_Operation_Close(&miOperation);
  
    if (_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	} 
	Py_INCREF(Py_None);
	return NULL;
}

static PyObject *Associate(PyObject *self, PyObject *args, PyObject *kwds)
{
    PMI_Instance *instance;
    char *nameSpace;
    char *assocClass = NULL;
    char *resultClass = NULL;
    char *role = NULL;
    char *resultRole = NULL;
    static char *kwlist[] = {"nameSpace","instance","assocClass","resultClass","role","resultRole",NULL};
     //association class, result class, role and resultRoles are all optional filters
    if(!PyArg_ParseTupleAndKeywords(args,kwds,"sO|ssss",kwlist, &nameSpace,&instance,&assocClass,&resultClass,&role,&resultRole))
    {
		PyErr_SetString(MIError,"Please input the correct arguments for association operation");
		return NULL;
    }
	
    PMI_Session *session = (PMI_Session*) self;
    MI_Session miSession = session->miSession;   

    const MI_Instance *assocInstance = instance->miInstance;
    MI_Result miResult = MI_RESULT_OK;
    MI_Result _miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *errorDetails = NULL;
   
	MI_Session_AssociatorInstances(&miSession, 0, NULL, nameSpace, assocInstance, assocClass, resultClass, role, resultRole, MI_FALSE, NULL, &miOperation);
	PyObject *instances = PyList_New(0);	 
	do
    {
    	const MI_Instance *miInstance;
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &errorDetails);
		if (_miResult != MI_RESULT_OK)
        {	
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;
        }

        if (miInstance)
        {
            PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
			MI_Instance *cloneInstance;
			MI_Instance_Clone(miInstance,&cloneInstance);
	    	pmiInstance-> miInstance = cloneInstance;
			MakePropertyDict(pmiInstance);
			PyList_Append(instances,(PyObject *)pmiInstance);
        }

    } while (miResult == MI_RESULT_OK && moreResults == MI_TRUE);

    if (miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"Get operation failed to retrieve the instance to associate,error = ");
		strcat(error,MI_Result_To_String(miResult));
		if(errorMessage != NULL)
		{
			strcat(error,", errorMessage = ");
			strcat(error,errorMessage);
		}        
		PyErr_SetString(MIError,error);
		return NULL;
    }

    _miResult = MI_Operation_Close(&miOperation);
    if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	} 
	return (PyObject *)instances;
}


static PyObject *Reference(PyObject *self, PyObject *args, PyObject *kwds)
{
    char *nameSpace;	
    MI_Char *resultClass = NULL;
    MI_Char *role = NULL;
    PMI_Instance *instance; 
    static char *kwlist[] = {"nameSpace","instance","resultClass","role", NULL};
    if(!PyArg_ParseTupleAndKeywords(args,kwds,"sO|ss",kwlist,&nameSpace,&instance,&resultClass,&role))
    {
		PyErr_SetString(MIError,"Please input the correct arguments for reference operation");
		return NULL;
    }
    PMI_Session *session = (PMI_Session*) self;
    MI_Session miSession = session->miSession;   

    MI_Instance *refInstance =instance->miInstance;
    
    MI_Result miResult = MI_RESULT_OK;
    MI_Result _miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Boolean moreResults;
    const MI_Char *errorString = NULL;
    const MI_Instance *errorDetails = NULL;
    
    MI_Session_ReferenceInstances(&miSession, 0, NULL, nameSpace, refInstance, resultClass, role, MI_FALSE, NULL, &miOperation);
	PyObject *instances = PyList_New(0);
    do
    {
        const MI_Instance *miInstance;

        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorString, &errorDetails);
        if (_miResult != MI_RESULT_OK)
        {
			char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;        
        }
        if (miInstance)
        {
            PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
			MI_Instance *cloneInstance;
			MI_Instance_Clone(miInstance,&cloneInstance);
			pmiInstance-> miInstance = cloneInstance;
			MakePropertyDict(pmiInstance);
			PyList_Append(instances,(PyObject *)pmiInstance);
        }
    } while (miResult == MI_RESULT_OK && moreResults == MI_TRUE);

    if (miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"Get operation failed to retrieve the instance to reference,error =  ");
		strcat(error,MI_Result_To_String(miResult));
		if(errorString != NULL)
		{
			strcat(error,", errorMessage = ");
			strcat(error,errorString);
		}
        PyErr_SetString(MIError,error);
		return NULL;
    }

    _miResult = MI_Operation_Close(&miOperation);
    if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	} 
	return (PyObject *)instances;
}

static PyObject *Query(PyObject *self, PyObject *args)
{
    char *nameSpace, *queryDialect, *queryExpression;
    if(!PyArg_ParseTuple(args,"sss",&nameSpace,&queryDialect,&queryExpression))
    {
		PyErr_SetString(MIError,"Please input the correct arguments for query operation");
		return NULL;
    }
    PMI_Session *session = (PMI_Session*) self;
    MI_Session miSession = session->miSession;   
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult;
    const MI_Char *errorMessage;
    const MI_Instance *errorDetails;
    MI_Boolean moreResults;
    MI_Result _miResult;

    MI_Session_QueryInstances(&miSession,0,NULL,nameSpace,queryDialect,queryExpression,NULL,&miOperation);
	PyObject *instances = PyList_New(0);
    do
    {
        const MI_Instance *miInstance;

        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &errorDetails);
        if (_miResult != MI_RESULT_OK)
        {
        	char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;  
            
        }
        if (miInstance)
        {
            PMI_Instance *pmiInstance = (PMI_Instance*) initPMI();
			MI_Instance *cloneInstance;
			MI_Instance_Clone(miInstance,&cloneInstance);
	    	pmiInstance-> miInstance = cloneInstance;
			MakePropertyDict(pmiInstance);
			PyList_Append(instances,(PyObject *)pmiInstance);
        }

    } while (miResult == MI_RESULT_OK && moreResults == MI_TRUE);
    
    if (miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"Get operation failed to retrieve the instance to query,error =");
		strcat(error,MI_Result_To_String(miResult));
		if(errorMessage != NULL)
		{
			strcat(error,", errorMessage = ");
			strcat(error,errorMessage);
		}
        PyErr_SetString(MIError,error);
		return NULL;
    }

    _miResult = MI_Operation_Close(&miOperation);
    if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	} 
	return (PyObject *)instances;
}



static PyObject *GetClass(PyObject *self, PyObject *args)
{
    char *nameSpace,*className;
    PMI_Session *session = (PMI_Session*) self;
    if(!PyArg_ParseTuple(args,"ss",&nameSpace,&className))
    {
		PyErr_SetString(MIError,"Please provide correct nameSpace and className");
		return NULL;
    }

    MI_Session miSession = session->miSession;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult;
    MI_Result _miResult;
    MI_Boolean moreResults;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
	const MI_Class *miClass;	

    MI_Session_GetClass(&miSession,0,NULL,nameSpace,className,NULL,&miOperation);
   
    do
    {
        _miResult = MI_Operation_GetClass(&miOperation, &miClass, &moreResults, &miResult, &errorMessage, &completionDetails);
        if (_miResult != MI_RESULT_OK)
        {
            char error[errorBufferSize];
			strcpy(error,"MI_Operation_GetInstance failed, errorString =");
			strcat(error,MI_Result_To_String(_miResult));
			PyErr_SetString(MIError,error);
			return NULL;  
        }
        else
        {
            if (miResult != MI_RESULT_OK)
            {
            	char error[errorBufferSize];
				strcpy(error,"Get operation failed to retrieve the class,error ");
				strcat(error,MI_Result_To_String(miResult));
				if(errorMessage != NULL)
				{
					strcat(error,", errorMessage = ");
					strcat(error,errorMessage);
				}
        		PyErr_SetString(MIError,error);
				return NULL;
            }
            else if (miClass)
            {
	            PMI_Class *pmiClass = (PMI_Class*) init_PMI_Class();
		    	pmiClass-> miClass = miClass;
				MakeMethodsDict(pmiClass);
				MakePropertyValueAndTypeDict(pmiClass);
		    	return (PyObject *)pmiClass;	
            }
            else if (moreResults == MI_TRUE)
            {
                PyErr_SetString(MIError,"More results are due and we have no class, we will keep trying!\n");
				return NULL;
            }
            
        }
    } while (moreResults == MI_TRUE);
	
	_miResult = MI_Operation_Close(&miOperation);
	if(_miResult != MI_RESULT_OK)
	{
		char error[errorBufferSize];
		strcpy(error,"MI_Operation_Close failed, error = ");
		strcat(error,MI_Result_To_String(_miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}
	
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *Close(PyObject *self)
{
    MI_Result miResult = MI_RESULT_OK;
    PMI_Session *session = (PMI_Session *)self;
    MI_Session miSession = session->miSession;
    miResult = MI_Session_Close(&miSession,NULL,NULL);
    if(miResult != MI_RESULT_OK)
    {
		char error[errorBufferSize];
		strcpy(error,"MI_Session_Close failed, error = ");
		strcat(error,MI_Result_To_String(miResult));
		PyErr_SetString(MIError,error);
		return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef PMI_Session_methods [] = {
    {"enumerate_instances",(PyCFunction)EnumerateInstances,METH_VARARGS,NULL},
    {"get_instance",(PyCFunction)GetInstance,METH_VARARGS,NULL},
    {"get_class",(PyCFunction)GetClass,METH_VARARGS,NULL},
    {"modify_instance",(PyCFunction)ModifyInstances,METH_VARARGS,NULL},
    {"create_instance",(PyCFunction)CreateInstance,METH_VARARGS,NULL},
    {"delete_instance",(PyCFunction)DeleteInstance,METH_VARARGS,NULL},
    {"associate",(PyCFunction)Associate, METH_VARARGS|METH_KEYWORDS,NULL},
    {"reference",(PyCFunction)Reference,METH_VARARGS|METH_KEYWORDS,NULL},
    {"query",(PyCFunction)Query,METH_VARARGS,NULL},
    {"close",(PyCFunction)Close,METH_NOARGS,NULL},
    {"invoke",(PyCFunction)Invoke,METH_VARARGS|METH_KEYWORDS,NULL},
    {NULL}
};

static PyTypeObject PMI_SessionType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PMI_Session.PMI_Session",             /* tp_name */
    sizeof(PMI_Session), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)PMI_Session_dealloc,     /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "MI_Session objects",           /* tp_doc */
    0,			       /* tp_traverse */
    0,		               /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PMI_Session_methods,             /* tp_methods */
    0,		               /* tp_members */
    0,    			/* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PMI_Session_init,      /* tp_init */
    0,                         /* tp_alloc */
    (newfunc)PMI_Session_new,                 /* tp_new */
};	    


static PyObject *InitSession()
{
	PyObject *session = PyObject_CallObject((PyObject*) &PMI_SessionType, NULL);
	Py_INCREF(session);
	return session;
}

#define PyMODINIT_FUNC void
#ifndef PyMODINIT_FUNC
#endif
PyMODINIT_FUNC
initPMI_Session(void)
{ 
    PyObject *m;
    /*Make sure the new type object is initialized properly*/
    if (PyType_Ready(&PMI_SessionType) <0)
		return;
    m = Py_InitModule3("mi",PMI_Session_methods, "MI_Session object");
    //Py_INCREF(&PMI_SessionType);

    /*Add the exception type to the module */
    MIError = PyErr_NewException("mi.error",NULL,NULL);
    Py_INCREF(MIError);
    PyModule_AddObject(m,"MIError",MIError);

    /*New type objects are all exported into mi module*/
    PyModule_AddObject(m, "PMI_Session", (PyObject *)&PMI_SessionType);
    PyDateTime_IMPORT; 
}
