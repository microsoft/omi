/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "/usr/include/python2.6/Python.h"
#include "MI.h"
#include <string.h>
#include "structmember.h"
#include "PMI_Session.c"

/*Define a static MI Exception type*/
static PyObject *MIError;

PyObject* CleanupApplication(MI_DestinationOptions miDestinationOptions,
	MI_Application miApplication, MI_Result miResult) {
    if (miDestinationOptions.ft) {
        MI_DestinationOptions_Delete(&miDestinationOptions);
	}

    MI_Application_Close(&miApplication);
	char str[80];
	strcpy(str,"MI_Application_NewSession failed, error = ");
	strcat(str,MI_Result_To_String(miResult));
    PyErr_SetString(MIError,str);
	return NULL;
}

PyObject* CleanupSession(MI_DestinationOptions miDestinationOptions,
	MI_Application miApplication, MI_Result miResult, MI_Session miSession) {
    MI_Session_Close(&miSession, NULL, NULL);
    return CleanupApplication(miDestinationOptions, miApplication, miResult);
}

static PyObject* Connect(PyObject* self, PyObject* args){
	//initiazlie the python module first
	Py_Initialize();
	initPMI_Session();
	initPMI_Instance();
	initPMI_Class();
	PMI_Session* session = (PMI_Session*) InitSession();
	MI_Application miApplication = MI_APPLICATION_NULL;
	MI_Session miSession = MI_SESSION_NULL;	
	MI_Result miResult;
	MI_DestinationOptions miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
	MI_UserCredentials miUserCreds = {0};

	char* domain, *username, *password;
	if(!PyArg_ParseTuple(args,"sss",&domain,&username,&password))
	{
	     PyErr_SetString(MIError,"Connection failed: please input the correct domian, username and password");
	     return NULL;
	}
	
    miUserCreds.authenticationType = MI_AUTH_TYPE_BASIC;
    miUserCreds.credentials.usernamePassword.domain = MI_T(domain);
    miUserCreds.credentials.usernamePassword.username = username;
    miUserCreds.credentials.usernamePassword.password = password;
	
	miResult = MI_Application_Initialize(0, NULL, NULL, &miApplication);
	if (miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"MI_Application_Initialize failed");
		return NULL;
	}		

	miResult = MI_Application_NewDestinationOptions(&miApplication, &miDestinationOptions);
    if (miResult != MI_RESULT_OK) 
	{
        return CleanupApplication(miDestinationOptions, miApplication, miResult);
	}

	miResult = MI_DestinationOptions_AddDestinationCredentials(&miDestinationOptions, &miUserCreds);
    if (miResult != MI_RESULT_OK)
    {
	   return CleanupApplication(miDestinationOptions, miApplication, miResult);
	}

	miResult = MI_Application_NewSession(&miApplication, NULL, NULL, &miDestinationOptions, NULL, NULL, &miSession);
    if (miResult != MI_RESULT_OK)
	{
        return CleanupApplication(miDestinationOptions, miApplication, miResult);
	}
	/*Make sure the connection is successful */
	miResult = TestConnection(&miSession);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"Connection failed.Check the server status and credentials");
		return NULL;
	}

	session->miSession = miSession;
	Py_INCREF(session);
	return (PyObject *)session;
}


static PyObject *CreateLocalInstance(PyObject *self, PyObject *args, PyObject *kwds)
{
	char *className;
	PyObject *propertyDict;
	PyObject *propertyTypes = NULL;
	PyObject *propertyFlags = NULL;
 	static char *kwlist[] = {"className","propertyValues","propertyTypes","propertyFlags",NULL};
	if(!PyArg_ParseTupleAndKeywords(args,kwds,"sO!|OO",kwlist,&className,&PyDict_Type, &propertyDict,&propertyTypes,&propertyFlags))
    {
		PyErr_SetString(MIError,"Please input correct classname and property dictionaries");
		return NULL;
    }

    MI_Result miResult;
    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_Instance *miInstance = NULL;

	miResult = MI_Application_Initialize(0, NULL, NULL, &miApplication);
	if (miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"MI_Application Initialize failed");
		return NULL;
	}		

	miResult = MI_Application_NewInstance(&miApplication,className,NULL,&miInstance);
	if(miResult != MI_RESULT_OK)
	{
		char error[200];
		strcpy(error,"Failed to create an instance of class ");
		strcat(error,className);
		strcat(error,", error = ");
		strcat(error,MI_Result_To_String(miResult));
		PyErr_SetString(MIError,error);
		return NULL;
	}
	
	//Iterate the dictionary and add property values to the instance
	PyObject *key, *value;
	Py_ssize_t pos = 0;
	while (PyDict_Next(propertyDict, &pos, &key, &value))
	{
		MI_Value miValue;
    	MI_Type  miType;
		MI_Uint32  miFlag;
		char *propertyName;
		PyObject *propertyValue;

		if(!PyArg_Parse(key,"s",&propertyName))
		{
			PyErr_SetString(MIError,"Property name is not correct");
			return NULL;
		}		
		if(!PyArg_Parse(value,"O",&propertyValue))
		{
			PyErr_SetString(MIError,"Property value is not correct");
			return NULL;
		}
		/*If the user doesn't specify property type, set the default type to be string */
		if(propertyTypes != NULL)
		{	
			PyObject *typeValue = PyDict_GetItemString(propertyTypes,propertyName);
			if(typeValue != NULL)
			{
				miType = PyInt_AsLong(typeValue);
				SetPropertyValues(miType,propertyValue,&miValue);
			}
			else
			{
				/*Need to check if it's datetime object otherwise server always expects interval for datetime object*/
				if (PyDateTime_Check(propertyValue) || PyDelta_Check(propertyValue))
				{
					miType = MI_DATETIME;
					SetPropertyValues(miType,propertyValue,&miValue);		
				}
				else
				{
	    			miValue.string = PyString_AsString(propertyValue);
					miType = MI_STRING;
				}
			}
		}
		if(propertyFlags != NULL)
		{
			PyObject *flagValue = PyDict_GetItemString(propertyFlags,propertyName);
			if(flagValue != NULL)
			{
				long value = PyInt_AsLong(flagValue);
				miFlag = (MI_Uint32)value;
			}
		}
		miResult = MI_Instance_AddElement(miInstance,propertyName,&miValue,miType,miFlag);
	    
		if(miResult != MI_RESULT_OK)
    	{
			char error[200];
			strcpy(error,"MI_Instance_AddElement failed, error =");
			strcat(error,MI_Result_To_String(miResult));
			PyErr_SetString(MIError,error);
			return NULL;
    	}
	}

	PMI_Instance* pmiInstance = (PMI_Instance*) initPMI();
	pmiInstance->miInstance = miInstance;		
	pmiInstance->propertyValues = propertyDict;		
	pmiInstance->propertyTypes = propertyTypes;
	pmiInstance->propertyFlags = propertyFlags;
   	return (PyObject *)pmiInstance;
}

void DatetimeToStr(const MI_Datetime* x, _Out_writes_z_(26) MI_Char buf[26])
{
    if (x->isTimestamp)
    {
        const MI_Char FMT[] = "%04d%02d%02d%02d%02d%02d.%06d%c%03d";
        MI_Sint32 utc = x->u.timestamp.utc;

        sprintf(buf,FMT,
            x->u.timestamp.year,
            x->u.timestamp.month,
            x->u.timestamp.day,
            x->u.timestamp.hour,
            x->u.timestamp.minute,
            x->u.timestamp.second,
            x->u.timestamp.microseconds,
            utc < 0 ? '-' : '+',
            utc < 0 ? -utc : utc);
    }
    else
    {
        const MI_Char FMT[] = "%08u%02u%02u%02u.%06u:000";
        sprintf(buf,FMT,
            x->u.interval.days,
            x->u.interval.hours,
            x->u.interval.minutes,
            x->u.interval.seconds,
            x->u.interval.microseconds);
    }
}

static char* MI_Type_To_String(MI_Type miType)
{ 
	switch (miType)
    {
    	case MI_BOOLEAN:
        {
			return "MI_BOOLEAN";
        }
		case MI_UINT8:
		{
			return "MI_UINT8";
		}
        case MI_SINT8:
		{
			return "MI_SINT8";
		}  
		case MI_UINT16:
		{
			return "MI_UINT16";
		}
        case MI_SINT16:
		{
			return "MI_SINT16";
		}  
		case MI_UINT32:
		{
			return "MI_UINT32";
		}
        case MI_SINT32:
		{
			return "MI_SINT32";
		}  
		case MI_UINT64:
		{
			return "MI_UINT64";
		}
        case MI_SINT64:
		{
			return "MI_SINT64";
		}  
		case MI_REAL32:
		{
			return "MI_REAL32";
		}
		case MI_REAL64:
		{
			return "MI_REAL64";
		}
		case MI_CHAR16:
		{
			return "MI_CHAR16";
		}
		case MI_DATETIME:
		{
			return "MI_DATETIME";
		}
		case MI_STRING:
		{
			return "MI_STRING";		
		}
		case MI_REFERENCE:
		{
			return "MI_REFERENCE";
		}
		case MI_INSTANCE:
		{
			return "MI_INSTANCE";
		}
		case MI_BOOLEANA:
		{
			return "MI_BOOLEANA";
		}
		case MI_UINT8A:
		{
			return "MI_UINT8A";
		}
        case MI_SINT8A:
		{
			return "MI_SINT8A";
		}  
		case MI_UINT16A:
		{
			return "MI_UINT16A";
		}
        case MI_SINT16A:
		{
			return "MI_SINT16A";
		}  
		case MI_UINT32A:
		{
			return "MI_UINT32A";
		}
        case MI_SINT32A:
		{
			return "MI_SINT32A";
		}  
		case MI_UINT64A:
		{
			return "MI_UINT64A";
		}
        case MI_SINT64A:
		{
			return "MI_SINT64A";
		}  
		case MI_REAL32A:
		{
			return "MI_REAL32A";
		}
		case MI_REAL64A:
		{
			return "MI_REAL64A";
		}
		case MI_CHAR16A:
		{
			return "MI_CHAR16A";
		}
		case MI_DATETIMEA:
		{
			return "MI_DATETIMEA";
		}
		case MI_STRINGA:
		{
			return "MI_STRINGA";		
		}
		case MI_REFERENCEA:
		{
			return "MI_REFERENCEA";
		}
		case MI_INSTANCEA:
		{
			return "MI_INSTANCEA";
		}
	}
	return "";
}

//forward declaration
void Print_Element_Value( const MI_Value *elementValue, MI_Type elementType, size_t level);

void Indent(size_t level)
{
	size_t n = level *4;
	while(n--)
		PySys_WriteStdout(" ");
}

/* Print an element */
void Print_Element(
    const MI_Char *elementName, 
    const MI_Value *elementValue, 
    MI_Type elementType, 
    MI_Uint32 elementFlags, 
    size_t level)
{
    Indent(level);
    PySys_WriteStdout("%s [%s", elementName, MI_Type_To_String(elementType));

    if (elementFlags & MI_FLAG_KEY)
    {
        PySys_WriteStdout(", MI_FLAG_KEY");
    }

    if ((elementFlags & MI_FLAG_NULL) || (elementValue == NULL))
    {
        PySys_WriteStdout(", NULL]");
        return;
    }
    else 
    {
        PySys_WriteStdout("] ");

        Print_Element_Value(elementValue, elementType, level);
    }
}



void Dump_MI_Instance(MI_Instance *miInstance, MI_Boolean keysOnly, size_t level)
{
	if(miInstance == NULL)
	{
		PyErr_SetString(MIError,"MI_Instance is null");
		return;
	}

	MI_Uint32 elementCount;
    MI_Result miResult;
    MI_Uint32 elementIndex;

    miResult = MI_Instance_GetElementCount(miInstance, &elementCount);
    if (miResult != MI_RESULT_OK)
    {
        PyErr_SetString(MIError,"MI_Instance_GetElementCount failed");
    }
    Indent(level);
    PySys_WriteStdout("Class %s\n", miInstance->classDecl->name);
    Indent(level);     
	PySys_WriteStdout("{\n");
    Indent(level);

    for (elementIndex = 0; elementIndex != elementCount; elementIndex++)
    {
        const MI_Char *elementName;
        MI_Value elementValue;
        MI_Type elementType;
        MI_Uint32 elementFlags;

        miResult = MI_Instance_GetElementAt(miInstance, elementIndex, &elementName, &elementValue, &elementType, &elementFlags);
        if (miResult != MI_RESULT_OK)
        {
            PyErr_SetString(MIError,"MI_Instance_GetElementCount failed");
        }
        if ((keysOnly && (elementFlags & MI_FLAG_KEY)) || 
            !keysOnly)
        {
            Print_Element(elementName, &elementValue, elementType, elementFlags, level+1);
            PySys_WriteStdout("\n");
        }
    }
    Indent(level);
    PySys_WriteStdout("}\n");
}

void Print_Element_Value(
    const MI_Value *elementValue, 
    MI_Type elementType, 
    size_t level)
{
        switch (elementType)
        {
            case MI_BOOLEAN:
            {
                PySys_WriteStdout("%s", elementValue->boolean ? "True" : "False");
                break;
            }
            case MI_SINT8:
            {
                PySys_WriteStdout("%hd", elementValue->sint8);
                break;
            }
            case MI_UINT8:
            {
                PySys_WriteStdout("%hu", elementValue->uint8);
                break;
            }
            case MI_SINT16:
            {
                PySys_WriteStdout("%d", elementValue->sint16);
                break;
            }
            case MI_UINT16:
            {
                PySys_WriteStdout("%u", elementValue->uint16);
                break;
            }
            case MI_SINT32:
            {
                PySys_WriteStdout("%i", elementValue->sint32);
                break;
            }
            case MI_UINT32:
            {
                PySys_WriteStdout("%u", elementValue->uint32);
                break;
            }
            case MI_SINT64:
            {
                PySys_WriteStdout("%lld", elementValue->sint64);
                break;
            }
            case MI_UINT64:
            {
                PySys_WriteStdout("%llu", elementValue->uint64);
                break;
            }
            case MI_REAL32:
            {
                PySys_WriteStdout("%g", elementValue->real32);
                break;
            }
            case MI_REAL64:
            {
                PySys_WriteStdout("%lg", elementValue->real64);
                break;
            }
            case MI_CHAR16:
            {
                PySys_WriteStdout("%u", elementValue->char16);
                break;
            }
            case MI_DATETIME:
            {
                MI_Char buf[26];
                DatetimeToStr(&elementValue->datetime, buf);
                PySys_WriteStdout("%s", buf);
                break;
            }
            case MI_STRING:
            {
                PySys_WriteStdout("%s", elementValue->string);
                break;
            }
            case MI_BOOLEANA:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->booleana.size; i++)
                {
                    MI_Value value;
                    value.boolean = elementValue->booleana.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_SINT8A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->sint8a.size; i++)
                {
                    MI_Value value;
                    value.sint8 = elementValue->sint8a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_UINT8A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->uint8a.size; i++)
                {
                    MI_Value value;
                    value.uint8 = elementValue->uint8a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_SINT16A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->sint16a.size; i++)
                {
                    MI_Value value;
                    value.sint16 = elementValue->sint16a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_UINT16A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->uint16a.size; i++)
                {
                    MI_Value value;
                    value.uint16 = elementValue->uint16a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_SINT32A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->sint32a.size; i++)
                {
                    MI_Value value;
                    value.sint32 = elementValue->sint32a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_UINT32A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->uint32a.size; i++)
                {
                    MI_Value value;
                    value.uint32 = elementValue->uint32a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_SINT64A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->sint64a.size; i++)
                {
                    MI_Value value;
                    value.sint64 = elementValue->sint64a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
               PySys_WriteStdout("}");
                break;
            }
            case MI_UINT64A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->uint64a.size; i++)
                {
                    MI_Value value;
                    value.uint64 = elementValue->uint64a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_REAL32A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->real32a.size; i++)
                {
                    MI_Value value;
                    value.real32 = elementValue->real32a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_REAL64A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->real64a.size; i++)
                {
                    MI_Value value;
                    value.real64 = elementValue->real64a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_CHAR16A:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->char16a.size; i++)
                {
                    MI_Value value;
                    value.char16 = elementValue->char16a.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_DATETIMEA:
            {
                MI_Uint32 i;
                MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->datetimea.size; i++)
                {
                    MI_Value value;
                    value.datetime = elementValue->datetimea.data[i];
                    Print_Element_Value(&value, nonArrayType, level);
                    if (i + 1 != elementValue->datetimea.size)
                        PySys_WriteStdout(", ");
                }
                PySys_WriteStdout("}");
                break;
            }
            case MI_STRINGA:
            {
                MI_Uint32 i;

                PySys_WriteStdout("{");

                for (i = 0; i < elementValue->stringa.size; i++)
                {
                    MI_Char *value;
                    value = elementValue->stringa.data[i];
                    PySys_WriteStdout(value);
                    if (i + 1 != elementValue->stringa.size)
                        PySys_WriteStdout(", ");
                }
               PySys_WriteStdout("}");
                break;
            }
            case MI_INSTANCE:
            {
                MI_Instance* inst = elementValue->instance;

                Dump_MI_Instance(inst, MI_FALSE, level);
                break;
            }
            case MI_REFERENCE:
            {
                MI_Instance* inst = elementValue->reference;

                PySys_WriteStdout(" REF ");

                Dump_MI_Instance(inst, MI_TRUE, level);
                break;
            }
            case MI_INSTANCEA:
            {
                const MI_InstanceA* inst = &elementValue->instancea;
                MI_Uint32 i;

                PySys_WriteStdout("\n");

                Indent(level);
                PySys_WriteStdout("{\n");

                for (i = 0; i < inst->size; i++)
                {
                    Dump_MI_Instance(inst->data[i], MI_TRUE, level + 1);
                }

                Indent(level);
                PySys_WriteStdout("}");

                break;
            }
            case MI_REFERENCEA:
            {
                const MI_InstanceA* inst = &elementValue->instancea;
                MI_Uint32 i;

                PySys_WriteStdout(" REF ");

                PySys_WriteStdout("\n");

                Indent(level);
                PySys_WriteStdout("{\n");

                for (i = 0; i < inst->size; i++)
                {
                    Dump_MI_Instance(inst->data[i], MI_FALSE, level + 1);
                }

                Indent(level);
                PySys_WriteStdout("}");

                break;
            }
            default:
                break;
        }
}



static PyObject *Print(PyObject *self,PyObject *args)
{
	PyObject *instance;
	if(!PyArg_ParseTuple(args,"O",&instance))
    {
		PyErr_SetString(MIError,"Please input correct MI_Instance");
		return NULL;
    }
	PMI_Instance *pmiInstance = (PMI_Instance *)instance;
	MI_Instance *miInstance;
	if(pmiInstance != NULL && (PyObject_Compare((PyObject *)pmiInstance,Py_None)))
	{	
		miInstance = pmiInstance->miInstance;
	}
	else
	{
		PyErr_SetString(MIError,"MI_Instance cannot be null!");
		return NULL;
	}

	Dump_MI_Instance(miInstance,MI_FALSE,0);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef mi_funcs[] = {
	{"connect",(PyCFunction)Connect,METH_VARARGS,NULL},
	{"create_local_instance",(PyCFunction)CreateLocalInstance,METH_VARARGS|METH_KEYWORDS,NULL},
	{"print_instance",(PyCFunction)Print,METH_VARARGS,NULL},
	{NULL}
};

void initmi(void) {
	PyObject *m;
	m = Py_InitModule3("mi", mi_funcs, "MI module that wraps up the MI operation from client API");
	/*Add the exception type to the module */
	MIError = PyErr_NewException("mi.error",NULL,NULL);
	Py_INCREF(MIError);
	PyModule_AddObject(m,"MIError",MIError);

	/*enum types */
	PyModule_AddIntConstant(m, "BOOLEAN",0);
	PyModule_AddIntConstant(m,"UINT8",1);
	PyModule_AddIntConstant(m, "SINT8",2);
	PyModule_AddIntConstant(m,"UINT16",3);
	PyModule_AddIntConstant(m,"SINT16",4);
	PyModule_AddIntConstant(m, "UINT32",5);
	PyModule_AddIntConstant(m,"SINT32",6);
	PyModule_AddIntConstant(m, "UINT64",7);
	PyModule_AddIntConstant(m,"SINT64",8);
	PyModule_AddIntConstant(m,"REAL32",9);
	PyModule_AddIntConstant(m, "REAL64",10);
	PyModule_AddIntConstant(m,"CHAR16",11);
	PyModule_AddIntConstant(m, "DATETIME",12);
	PyModule_AddIntConstant(m,"STRING",13);
	PyModule_AddIntConstant(m,"REFERENCE",14);
	PyModule_AddIntConstant(m, "INSTANCE",15);
	PyModule_AddIntConstant(m,"BOOLEANA",16);
	PyModule_AddIntConstant(m, "UINT8A",17);
	PyModule_AddIntConstant(m,"SINT8A",18);
	PyModule_AddIntConstant(m,"UINT16A",19);
	PyModule_AddIntConstant(m, "SINT16A",20);
	PyModule_AddIntConstant(m,"UINT32A",21);
	PyModule_AddIntConstant(m, "SINT32A",22);
	PyModule_AddIntConstant(m,"UINT64A",23);
	PyModule_AddIntConstant(m,"SINT64A",24);
	PyModule_AddIntConstant(m, "REAL32A",25);
	PyModule_AddIntConstant(m,"REAL64A",26);
	PyModule_AddIntConstant(m, "CHAR16A",27);
	PyModule_AddIntConstant(m,"DATETIMEA",28);
	PyModule_AddIntConstant(m,"STRINGA",29);
	PyModule_AddIntConstant(m,"REFERENCEA",30);
	PyModule_AddIntConstant(m,"INSTANCEA",31);

	/*CIM meta types */
	PyModule_AddIntConstant(m,"FLAG_CLASS",1 << 0);
	PyModule_AddIntConstant(m,"FLAG_METHOD",1 << 1);
	PyModule_AddIntConstant(m,"FLAG_PROPERTY",1 << 2);
	PyModule_AddIntConstant(m,"FLAG_PARAMETER", 1 << 3);
	PyModule_AddIntConstant(m,"FLAG_ASSOCIATION",1 << 4);
	PyModule_AddIntConstant(m,"FLAG_INDICATION", 1 << 5);
	PyModule_AddIntConstant(m,"FLAG_REFERENCE", 1 << 6);	
	PyModule_AddIntConstant(m,"FLAG_ANY",1|2|4|8|16|32|64);
	
	/*Qualifier flavors */
	PyModule_AddIntConstant(m,"FLAG_ENABLEOVERRIDE",1 << 7);	
	PyModule_AddIntConstant(m,"FLAG_DISABLEOVERRIDE",1 << 8);
	PyModule_AddIntConstant(m,"FLAG_RESTRICTED",1 << 9);
	PyModule_AddIntConstant(m,"FLAG_TOSUBCLASS",1 << 10);
	PyModule_AddIntConstant(m,"FLAG_PARAMETER", 1 << 11);

	/*Select boolean qualifiers */
	PyModule_AddIntConstant(m,"FLAG_KEY",1 << 12);
	PyModule_AddIntConstant(m,"FLAG_IN",1 << 13);
	PyModule_AddIntConstant(m,"FLAG_OUT",1 << 14);
	PyModule_AddIntConstant(m,"FLAG_REQUIRED",1 << 15);
	PyModule_AddIntConstant(m,"FLAG_STATIC", 1 << 16);
	PyModule_AddIntConstant(m,"FLAG_ABSTRACT",1 << 17);
	PyModule_AddIntConstant(m,"FLAG_TERMINAL",1 << 18);
	PyModule_AddIntConstant(m,"FLAG_EXPENSIVE",1 << 19);
	PyModule_AddIntConstant(m,"FLAG_STREAM",1 << 20);
	PyModule_AddIntConstant(m,"FLAG_READONLY", 1 << 21);
	
	/* Special flags */
	PyModule_AddIntConstant(m,"FLAG_NOT_MODIFIED",1 << 25);
	PyModule_AddIntConstant(m,"FLAG_VERSION",1<<26|1<<27|1<<28);
	PyModule_AddIntConstant(m,"FLAG_NULL",1 << 29);
	PyModule_AddIntConstant(m,"FLAG_BORROW",1 << 30);
	PyModule_AddIntConstant(m,"FLAG_ADOPT", 1 << 31);
}

