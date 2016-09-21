/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "/usr/include/python2.6/Python.h"
#include "structmember.h"
#include "MI.h"
#include <stdlib.h>
#include "datetime.h"

static PyObject *MIError;

/*Defines a PMI_Instance Type Object which is a Python Object that contains a reference to an intance of MI_Instance */
typedef struct{
    PyObject_HEAD
    MI_Instance *miInstance;
    PyObject *propertyValues;
    PyObject *propertyTypes;
    PyObject *propertyFlags;
} PMI_Instance;


static void PMI_Instance_dealloc(PMI_Instance *self)
{
	MI_Result miResult = MI_RESULT_OK;	
	miResult = MI_Instance_Delete(self->miInstance);

	Py_CLEAR(self->propertyValues);
	Py_CLEAR(self->propertyTypes);
	Py_CLEAR(self->propertyFlags);
	self->ob_type->tp_free((PyObject*) self); 

}

static PyObject* PMI_Instance_new(PyTypeObject *type)
{
    PMI_Instance *self;
    self = (PMI_Instance *)type->tp_alloc(type,0);
    if(self != NULL){
		self-> miInstance = NULL;
		self-> propertyValues = NULL;
		self-> propertyTypes = NULL;
		self-> propertyFlags = NULL;
    }
    return (PyObject *)self;
}

static PyTypeObject PMI_InstanceType ;

static PyObject* initPMI()
{
    PyObject *instance = PyObject_CallObject((PyObject*) &PMI_InstanceType, NULL);
	Py_INCREF(instance);
	return instance;
}

static PyObject* MakePropertyDict(PMI_Instance *pmiInstance);

static PyObject* Get_Element_Value(const MI_Value *elementValue, MI_Type elementType)

{
	MI_Type nonArrayType = (MI_Type) (elementType & (~MI_ARRAY));
    switch (elementType)
    {
        case MI_BOOLEAN:
        {
			if(elementValue->boolean)
	    		return Py_True;	
			return Py_False;
        }

        case MI_SINT8:
        {
			return Py_BuildValue("b",elementValue->sint8);
        }

        case MI_UINT8:
        {
			return Py_BuildValue("B",elementValue->uint8);
        }

        case MI_SINT16:
        {
            return Py_BuildValue("h",elementValue->sint16);
        }

        case MI_UINT16:
        {
            return Py_BuildValue("H",elementValue->uint16);
        }

        case MI_SINT32:
        {	
			return Py_BuildValue("i",elementValue->sint32);
        }

        case MI_UINT32:
        {	           
			return Py_BuildValue("I",elementValue->uint32);
        }

        case MI_SINT64:
        {
           	return Py_BuildValue("L",elementValue->sint64);
        }

        case MI_UINT64:
        {
			return Py_BuildValue("K",elementValue->uint64);
        }

        case MI_REAL32:
        {
            return Py_BuildValue("f",elementValue->real32);
        }

        case MI_REAL64:
        {
			return Py_BuildValue("d",elementValue->real64);
        }

        case MI_CHAR16:
        {
			return Py_BuildValue("H",elementValue->char16);
        }

        case MI_DATETIME:
        {
			const MI_Datetime* x = &elementValue->datetime;
		
			if(x->isTimestamp)
			{
		    	//MI_Sint32 utc = x->u.timestamp.utc;
	    		PyObject* datetimeObject = PyDateTime_FromDateAndTime(x->u.timestamp.year,x->u.timestamp.month,x->u.timestamp.day,x->u.timestamp.hour,x->u.timestamp.minute,x->u.timestamp.second,x->u.timestamp.microseconds);
	    		return datetimeObject;
			}      
			else
			{
				//Convert MI_Datetime object to PyDatetime object with only day, hour and second attributes
				int hours = x->u.interval.hours;
				int minutes = x->u.interval.minutes;
				int seconds = x->u.interval.seconds;
	    		PyObject* delta = PyDelta_FromDSU(x->u.interval.days,hours*24+minutes*60+seconds,x->u.interval.microseconds);
	    		return delta;                
			}
       	}
		
		case MI_STRING:
        {
	        return Py_BuildValue("s",elementValue->string);
        }

        case MI_BOOLEANA:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->booleana.size);

            for (i = 0; i < elementValue->booleana.size; i++)
            {
                MI_Value value;
                value.boolean = elementValue->booleana.data[i];
                PyObject* propertyValue= Get_Element_Value(&value, nonArrayType);
	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;	
        }

        case MI_SINT8A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->sint8a.size);
            for (i = 0; i < elementValue->sint8a.size; i++)
            {
                MI_Value value;
                value.sint8 = elementValue->sint8a.data[i];
                PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_UINT8A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->uint8a.size);
            for (i = 0; i < elementValue->uint8a.size; i++)
            {
                MI_Value value;
                value.uint8 = elementValue->uint8a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_SINT16A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->sint16a.size);
            for (i = 0; i < elementValue->sint16a.size; i++)
            {
                MI_Value value;
                value.sint16 = elementValue->sint16a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_UINT16A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->uint16a.size);
            for (i = 0; i < elementValue->uint16a.size; i++)
            {
                MI_Value value;
                value.uint16 = elementValue->uint16a.data[i];
	  			PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue); 
            }
			return valueSets;
        }

        case MI_SINT32A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->sint32a.size);
            for (i = 0; i < elementValue->sint32a.size; i++)
            {
                MI_Value value;
                value.sint32 = elementValue->sint32a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);  
            }
			return valueSets;
        }

        case MI_UINT32A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->uint32a.size);
            for (i = 0; i < elementValue->uint32a.size; i++)
            {
                MI_Value value;
                value.uint32 = elementValue->uint32a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
	    		PyTuple_SetItem(valueSets,i,propertyValue);
			}
			return valueSets;
        }

        case MI_SINT64A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->sint64a.size);
            for (i = 0; i < elementValue->sint64a.size; i++)
            {
	            MI_Value value;
                value.sint64 = elementValue->sint64a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_UINT64A:
        {
			MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->uint64a.size);
            for (i = 0; i < elementValue->uint64a.size; i++)
            {
                MI_Value value;
                value.uint64 = elementValue->uint64a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_REAL32A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->real32a.size);
            for (i = 0; i < elementValue->real32a.size; i++)
            {
	            MI_Value value;
                value.real32 = elementValue->real32a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	   		 	PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_REAL64A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->real64a.size);
            for (i = 0; i < elementValue->real64a.size; i++)
            {
                MI_Value value;
                value.real64 = elementValue->real64a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_CHAR16A:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->char16a.size);
            for (i = 0; i < elementValue->char16a.size; i++)
            {
                MI_Value value;
                value.char16 = elementValue->char16a.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_DATETIMEA:
        {
        	MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->datetimea.size);
            for (i = 0; i < elementValue->datetimea.size; i++)
            {
                MI_Value value;
                value.datetime = elementValue->datetimea.data[i];
	    		PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	   			PyTuple_SetItem(valueSets,i,propertyValue); 
            }
			return valueSets;
        }

        case MI_STRINGA:
        {
            MI_Uint32 i;
			PyObject* valueSets = PyTuple_New(elementValue->stringa.size);
            for (i = 0; i < elementValue->stringa.size; i++)
            {
	            MI_Value value;
                value.string = elementValue->stringa.data[i];
	   		 	PyObject* propertyValue = Get_Element_Value(&value, nonArrayType);
 	    		PyTuple_SetItem(valueSets,i,propertyValue);
            }
			return valueSets;
        }

        case MI_INSTANCE:
        {
			MI_Instance* inst = elementValue->instance;
			PMI_Instance* embedded = (PMI_Instance*) initPMI();
			embedded-> miInstance = inst;
			if(inst!=NULL)
			{			
				MakePropertyDict(embedded);
			}			
			return (PyObject *)embedded;
        }

        case MI_REFERENCE:
        {
			MI_Instance* inst = elementValue->reference;
			PMI_Instance* embedded = (PMI_Instance*) initPMI();
			embedded-> miInstance = inst;
			if(inst!=NULL)
			{
				MakePropertyDict(embedded);
			}
			return (PyObject *)embedded;
        }

        case MI_INSTANCEA:
        case MI_REFERENCEA:
        {
 	    	const MI_InstanceA* inst = &elementValue->instancea;
	    	MI_Uint32 i;
		 	PyObject* valueSets = PyTuple_New(inst->size);
			for (i = 0; i< inst->size; i++)
			{
		   		PMI_Instance* embedded = (PMI_Instance*) initPMI();
				if(inst->data[i]!=NULL)
				{	    		
		   			embedded-> miInstance = inst->data[i];
					MakePropertyDict(embedded);
		   			PyTuple_SetItem(valueSets,i,(PyObject *)embedded);
				}
				else
				{
					PyTuple_SetItem(valueSets,i,Py_None);
				}				
			}	
			return valueSets;	
        }

        default:
			Py_INCREF(Py_None);
			return Py_None;
    }
	
}


static PyObject* MakePropertyDict(PMI_Instance *pmiInstance)
{
	MI_Uint32 elementCount;
    MI_Result miResult;
    MI_Uint32 elementIndex;
	const MI_Instance *miInstance = pmiInstance->miInstance;
    if(miInstance == NULL)
    {
		PyErr_SetString(MIError,"MI_Instance is not valid");
		return NULL;
    }

    miResult = MI_Instance_GetElementCount(miInstance, &elementCount);
    if(miResult != MI_RESULT_OK)
    {
		PyErr_SetString(MIError,"MI_Instance_GetElement failed");
		return NULL;
    }

	/*make a property dictionary containing property name and value pairs. */
	PyObject *propertyValues = PyDict_New();
	PyObject *propertyTypes = PyDict_New();
	PyObject *propertyFlags = PyDict_New();
	

	const MI_Char *nameSpace;
	miResult = MI_Instance_GetNameSpace(miInstance,&nameSpace);
	if(miResult != MI_RESULT_OK)
    {
		PyErr_SetString(MIError,"MI_Instance_GetNameSpace failed");
		return NULL;
    }
	PyObject *nameSpaceValue = Py_BuildValue("s",nameSpace);
	PyDict_SetItemString(propertyValues,"nameSpace",nameSpaceValue);
	PyDict_SetItemString(propertyTypes,"nameSpace",Py_BuildValue("i",13));


	const MI_Char *classDecl;
	miResult = MI_Instance_GetClassName(miInstance,&classDecl);
		if(miResult != MI_RESULT_OK)
    {
		PyErr_SetString(MIError,"MI_Instance_GetClassName failed");
		return NULL;
    }
	PyObject *classDeclValue = Py_BuildValue("s",classDecl);	
	PyDict_SetItemString(propertyValues,"classDecl",classDeclValue);
	PyDict_SetItemString(propertyTypes,"classDecl",Py_BuildValue("i",13));
	
    for(elementIndex = 0; elementIndex < elementCount; elementIndex++)
    {
		const MI_Char *key;
		MI_Value elementValue;
		MI_Type elementType;
		MI_Uint32 elementFlags;

		miResult = MI_Instance_GetElementAt(miInstance,elementIndex,&key,&elementValue,&elementType,&elementFlags);
		if(miResult != MI_RESULT_OK)
		{
			PyErr_SetString(MIError,"MI_Instance_GetElement failed");
			return NULL;
		}

		PyObject *value = Get_Element_Value(&elementValue,elementType);
		if(PyDict_SetItemString(propertyValues,key,value))
		{
			PyErr_SetString(MIError,"Property dictionary insert item failed");
			return NULL;
		}
		PyObject *typeValue = PyInt_FromLong(elementType);
		//PyObject *flagValue = PyInt_FromLong(elementFlags); //Are we going to return the dictionary of pair <name,flag> ?
		if(PyDict_SetItemString(propertyTypes,key,typeValue))
		{
			PyErr_SetString(MIError,"Property type dictionary insert item failed");
			return NULL;
		}
		PyObject *flag = Py_BuildValue("s","");
		if(elementFlags & MI_FLAG_KEY)
		{
			flag = Py_BuildValue("s","MI_FLAG_KEY");
		}
		if(PyDict_SetItemString(propertyFlags,key,flag))
		{
			PyErr_SetString(MIError,"Property flag dictionary insert item failed");
			return NULL;
		}
    }

	pmiInstance->propertyValues = propertyValues;
	pmiInstance->propertyTypes = propertyTypes;
	pmiInstance->propertyFlags = propertyFlags;
	Py_INCREF(Py_None);
	return Py_None;
}


void SetPropertyValues(MI_Type elementType, PyObject *propertyValue, MI_Value *miValue)
{
	MI_Value value;
	switch (elementType)
	{
		case MI_BOOLEAN:
		{
			MI_Boolean booleanValue = propertyValue == Py_True? MI_TRUE:MI_FALSE;
			value.boolean = booleanValue;
			*miValue = value;
			break; 
		}
		case MI_SINT8:
		{
			MI_Sint8 sint8Value = PyInt_AsLong(propertyValue);
			value.sint8 = sint8Value;
			*miValue = value;
			break;
		}
		case MI_UINT8:
		{
			MI_Uint8 uint8Value = PyInt_AsLong(propertyValue);
			value.uint8 = uint8Value;
			*miValue = value;
			break;
		}
		case MI_SINT16:
		{
			MI_Sint16 sint16Value = PyInt_AsLong(propertyValue);
			value.sint16 = sint16Value;
			*miValue = value;
			break;
		}
		case MI_UINT16:
		{
			MI_Uint16 uint16Value = PyInt_AsLong(propertyValue);
			value.uint16 = uint16Value;
			*miValue = value;
			break;
		}
		case MI_SINT32:	
		{
			MI_Sint32 sint32Value = PyInt_AsLong(propertyValue);
			value.sint32 = sint32Value;
			*miValue = value;
			break;
		}
		case MI_UINT32:
		{
			MI_Uint32 uint32Value = PyInt_AsLong(propertyValue);
			value.uint32 = uint32Value;
			*miValue = value;
			break;
		}
		case MI_SINT64:
		{
			MI_Sint64 sint64Value = PyLong_AsLong(propertyValue);
			value.sint64 = sint64Value;
			*miValue = value;
			break;
		}
		case MI_UINT64:
		{			
			MI_Uint64 uint64Value = PyLong_AsUnsignedLong(propertyValue);
			value.uint64 = uint64Value;
			*miValue = value;
			break;
		}
		case MI_REAL32:
		{
			MI_Real32 real32Value = PyFloat_AsDouble(propertyValue);
			value.real32 = real32Value;
			*miValue = value;
			break;
		}
		case MI_REAL64:
		{
			MI_Real64 real64Value = PyFloat_AsDouble(propertyValue);
			value.real64 = real64Value;
			*miValue = value;
			break;
		}
		case MI_CHAR16:
		{
			MI_Char16 char16Value = PyInt_AsLong(propertyValue);
			value.char16 = char16Value;
			*miValue = value;
			break;
		}
		case MI_STRING:
		{
			char *stringValue = PyString_AsString(propertyValue);
			value.string = stringValue;
			*miValue = value;
			break;
		}
		
		case MI_DATETIME:
		{
			/*Check whether the input python object is of type DateTime or TimeDelta */
			if(PyDateTime_Check(propertyValue))
			{
			    MI_Datetime dateTime;
			    MI_Timestamp timeStamp;
			    dateTime.isTimestamp = 1;
			    int year = PyDateTime_GET_YEAR(propertyValue);
		 	    int month = PyDateTime_GET_MONTH(propertyValue);
			    int day = PyDateTime_GET_DAY(propertyValue);
			    int hour = PyDateTime_DATE_GET_HOUR(propertyValue);
			    int minute = PyDateTime_DATE_GET_MINUTE(propertyValue);
			    int second = PyDateTime_DATE_GET_SECOND(propertyValue);
			    int microseconds = PyDateTime_DATE_GET_MICROSECOND(propertyValue);
			    timeStamp.year = year;
			    timeStamp.month = month;	
			    timeStamp.day = day;
			    timeStamp.hour = hour;	
			    timeStamp.minute = minute;
			    timeStamp.second = second;
			    timeStamp.microseconds = microseconds;
				//if timezone not specified, set the default to UTC time
			    timeStamp.utc = 5;
			    dateTime.u.timestamp = timeStamp; 
			    value.datetime = dateTime;
			    *miValue = value;
			}
			/* no equivalent way of doing conversions. pydatetime object does not have days */
			else
			{
				MI_Datetime dateTime;
				dateTime.isTimestamp = 0;
				MI_Interval interval;
				int days = PyDateTime_GET_DAY(propertyValue);
				int seconds = PyDateTime_DATE_GET_SECOND(propertyValue);
				int hours = (int)seconds/60/60;
				int minutes = (seconds-hours*60*60)/60;
				seconds = seconds - hours*60*60 - minutes *60;
				int microseconds = PyDateTime_DATE_GET_MICROSECOND(propertyValue);
				interval.days = days;
				interval.hours = hours;
				interval.minutes = minutes;
				interval.seconds = seconds;
				interval.microseconds = microseconds;
				interval.__padding1 = 0;
				interval.__padding2 = 0;
				interval.__padding3 = 0;
				dateTime.u.interval = interval;
				value.datetime = dateTime;
				*miValue = value;		
			} 
			break;
		} 
		case MI_BOOLEANA:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_BooleanA miBooleanA;
			miBooleanA.size = size;
			int i;
			MI_Boolean booleanA[size];
			for (i = 0; i < size; i++)
			{
			    PyObject* boolean = PyList_GetItem(propertyValue,i);
			    if(boolean == Py_False)
			    {
					booleanA[i] = MI_FALSE;
			    }
			    else
			    {
					booleanA[i] = MI_TRUE;
			    }
			}
			miBooleanA.data = booleanA;
			value.booleana = miBooleanA;
			*miValue = value;
			break; 
		}
		case MI_UINT8A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Uint8A miUint8A;
			miUint8A.size = size;
			int i;
			MI_Uint8 uint8A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				uint8A[i] = PyInt_AsLong(value);
			}
			miUint8A.data = uint8A;
			value.uint8a = miUint8A;
			*miValue = value;
			break;
		}
		case MI_SINT8A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Sint8A miSint8A;
			miSint8A.size = size;
			int i;
			MI_Sint8 sint8A[size];	
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				sint8A[i] = PyInt_AsLong(value);
			}
			miSint8A.data = sint8A;
			value.sint8a = miSint8A;
			*miValue = value;
			break;
		}
		case MI_UINT16A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Uint16A miUint16A;
			miUint16A.size = size;
			int i;
			MI_Uint16 uint16A[size];
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				uint16A[i] = PyInt_AsLong(value);
			}
			miUint16A.data = uint16A;
			value.uint16a = miUint16A;
			*miValue = value;
			break;
		}
		case MI_SINT16A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Sint16A miSint16A;
			miSint16A.size = size;
			int i;
			MI_Sint16 sint16A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				sint16A[i] = PyInt_AsLong(value);
			}
			miSint16A.data = sint16A;
			value.sint16a = miSint16A;
			*miValue = value;
			break;
		}
		case MI_UINT32A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Uint32A miUint32A;
			miUint32A.size = size;
			int i;
			MI_Uint32 uint32A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				uint32A[i] = PyLong_AsLong(value);
			}
			miUint32A.data = uint32A;
			value.uint32a = miUint32A;
			*miValue = value;
			break;
		}
		case MI_SINT32A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Sint32A miSint32A;
			miSint32A.size = size;
			int i;
			MI_Sint32 sint32A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				sint32A[i] = PyLong_AsLong(value);
			}
			miSint32A.data = sint32A;
			value.sint32a = miSint32A;
			*miValue = value;
			break;
		}
		case MI_UINT64A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Uint64A miUint64A;
			miUint64A.size = size;
			int i;
			MI_Uint64 uint64A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				uint64A[i] = PyLong_AsUnsignedLong(value);
			}
			miUint64A.data = uint64A;
			value.uint64a = miUint64A;
			*miValue = value;
			break;
		}
		case MI_SINT64A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Sint64A miSint64A;
			miSint64A.size = size;
			int i;
			MI_Sint64 sint64A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				sint64A[i] = PyLong_AsLong(value);
			}
			miSint64A.data = sint64A;
			value.sint64a = miSint64A;
			*miValue = value;
			break;
		}
		case MI_REAL32A:	
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Real32A miReal32A;
			miReal32A.size = size;
			int i;
			MI_Real32 real32A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				real32A[i] = PyFloat_AsDouble(value);
			}
			miReal32A.data = real32A;
			value.real32a = miReal32A;
			*miValue = value;
			break;
		}
		case MI_REAL64A:	
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Real64A miReal64A;
			miReal64A.size = size;
			int i;
			MI_Real64 real64A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				real64A[i] = PyFloat_AsDouble(value);
			}
			miReal64A.data = real64A;
			value.real64a = miReal64A;
			*miValue = value;
			break;
		}
		case MI_CHAR16A:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_Char16A miChar16A;
			miChar16A.size = size;
			int i;
			MI_Char16 char16A[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				char16A[i] = PyInt_AsLong(value);
			}
			miChar16A.data = char16A;
			value.char16a = miChar16A;
			*miValue = value;
			break;
		}
		case MI_STRINGA:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_StringA miStringA;
			miStringA.size = size;
			int i;
			MI_Char *stringA[size];			
			for (i = 0; i < size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				stringA[i] = PyString_AsString(value);
			}
			miStringA.data = stringA;
			value.stringa = miStringA;
			*miValue = value;
			break;
		}
		case MI_DATETIMEA:
		{
			//to implement
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_DatetimeA miDatetimeA;
			miDatetimeA.size = size;
			break;
		}
		case MI_INSTANCE:
		{
			PMI_Instance *pmiInstance = (PMI_Instance *)propertyValue;
			MI_Instance *miInstance = pmiInstance->miInstance;
			value.instance = miInstance;
			*miValue = value;
			break;
		}
		case MI_REFERENCE:
		{
			PMI_Instance *pmiInstance = (PMI_Instance *)propertyValue;
			MI_Instance *miReference = pmiInstance->miInstance;
			value.reference = miReference;
			*miValue = value;
			break;
		}
		case MI_INSTANCEA:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_InstanceA miInstanceA;
			miInstanceA.size = size;
			int i;
			MI_Instance *instanceA[size]; 
			for(i = 0; i< size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				PMI_Instance *pmiInstance = (PMI_Instance *)value;				
				instanceA[i] = pmiInstance->miInstance;
			}
			miInstanceA.data = instanceA;
			value.instancea = miInstanceA;
			*miValue = value;
			break;
		}
		case MI_REFERENCEA:
		{
			Py_ssize_t size = PyList_Size(propertyValue);
			MI_ReferenceA miReferenceA;
			miReferenceA.size = size;
			int i;
			MI_Instance *referenceA[size];			
			for(i = 0; i< size; i++)
			{
				PyObject *value = PyList_GetItem(propertyValue,i);
				PMI_Instance *pmiInstance = (PMI_Instance *)value;
				referenceA[i] = pmiInstance->miInstance;
			}
			miReferenceA.data = referenceA;
			value.referencea = miReferenceA;
			*miValue = value;
			break;
		}
	}
}

static PyObject *EnumerateProperties(PMI_Instance *pmiInstance, char *propertyName)
{
	if(pmiInstance->propertyValues == NULL)
	{
		Py_INCREF(Py_None);
		return Py_None;
	}
	PyObject *propertyValues = pmiInstance->propertyValues;
	if(!strcmp(propertyName,"propertyValues"))
	{
		return propertyValues;
	}
	else if(!strcmp(propertyName,"propertyTypes"))
	{
		PyObject *propertyTypes = pmiInstance->propertyTypes;	
		return propertyTypes;
	}
	else if(!strcmp(propertyName,"propertyFlags"))
	{
		PyObject *propertyFlags = pmiInstance->propertyFlags;
		return propertyFlags;
	}
	else
	{
    	PyObject *value = PyDict_GetItemString(propertyValues,propertyName);
		if(value == NULL)
		{
			PyErr_SetString(MIError,"MI_Instance doesn't have the property");
			return NULL;
		}
		return value;
	}
}

static PyObject *GetProperty(PMI_Instance *self, char* propertyName)
{
    return EnumerateProperties(self,propertyName);
}

static void SetProperty(PMI_Instance *self, char* propertyName, PyObject* value)
{
	MI_Instance *miInstance = self->miInstance;
	PyObject *propertyValues = self->propertyValues;
	PyObject *newValue = PyDict_GetItemString(propertyValues,propertyName);
	if(newValue == NULL)
	{
		PyErr_SetString(MIError,"MI_Instance doesn't have the property");
	}	
	newValue = value;
	if(PyDict_SetItemString(propertyValues,propertyName,newValue)<0)
	{
		PyErr_SetString(MIError,"Set instance property failed");
	}

	PyObject *propertyTypes = self->propertyTypes;
	PyObject *valueType = PyDict_GetItemString(propertyTypes,propertyName);
	if(valueType == NULL)
	{
		PyErr_SetString(MIError,"MI_Instance doesn't have the property");
	}
	MI_Type miType = PyInt_AsLong(valueType);
	MI_Value miValue;
	MI_Result miResult = MI_RESULT_OK;
	SetPropertyValues(miType,value,&miValue);
	miResult = MI_Instance_SetElement(miInstance,propertyName,&miValue,miType,0);
	if(miResult != MI_RESULT_OK)
	{
		PyErr_SetString(MIError,"MI_Instance set element failed");
	}

}

static int PMI_Instance_init(PMI_Instance *self)
{
    self-> miInstance = NULL;
	self->propertyValues = NULL;
	self->propertyTypes = NULL;
	self->propertyFlags = NULL;
    return 0;
}

static PyMethodDef PMI_Instance_methods [] = {
    {NULL}
};

static PyObject* PMI_Instance_getattr(PMI_Instance* self, char* propertyName)
{
    PyObject *propertyValue = GetProperty(self, propertyName);
    Py_INCREF(propertyValue);
    return propertyValue;
}

static int PMI_Instance_setattr(PMI_Instance* self, char* propertyName, PyObject* value)
{
   SetProperty(self,propertyName,value);	
   return 0;
}

static PyTypeObject PMI_InstanceType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PMI_Instance.PMI_Instance",             /* tp_name */
    sizeof(PMI_Instance), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)PMI_Instance_dealloc,     /* tp_dealloc */
    0,                         /* tp_print */
    (getattrfunc)PMI_Instance_getattr,                         /* tp_getattr */
    (setattrfunc)PMI_Instance_setattr,                         /* tp_setattr */
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
    "MI_Instance objects",           /* tp_doc */
    0,			       /* tp_traverse */
    0,		               /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PMI_Instance_methods,             /* tp_methods */
    0,		               /* tp_members */
    0,    /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PMI_Instance_init,      /* tp_init */
    0,                         /* tp_alloc */
    (newfunc)PMI_Instance_new,                 /* tp_new */
};	    


#define PyMODINIT_FUNC void
#ifndef PyMODINIT_FUNC
#endif
PyMODINIT_FUNC
initPMI_Instance(void)
{ 
    PyObject *m;
    /*Make sure the new type object is initialized properly*/
    if (PyType_Ready(&PMI_InstanceType) <0)
		return;
    m = Py_InitModule3("mi",PMI_Instance_methods, "MI_Instance object");
    //Py_INCREF(&PMI_InstanceType);
    
    /*Add the exception type to the module */
    MIError = PyErr_NewException("mi.error",NULL,NULL);
    Py_INCREF(MIError);
    PyModule_AddObject(m,"MIError",MIError);

    /*New type objects are all exported into mi module*/
    PyModule_AddObject(m, "PMI_Instance", (PyObject *)&PMI_InstanceType);
    PyDateTime_IMPORT;
}
