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

/*Defines a PMI_Class Type Object which is a Python Object that contains a reference to an intance of MI_Class */
typedef struct{
    PyObject_HEAD
    const MI_Class *miClass;
	PyObject *methods; /*only a list of method names. Will expand to include method signatures */ 
	PyObject *propertyValues; /*dictionary of key value pairs */
	PyObject *propertyTypes;

} PMI_Class;

/*Destructor of the PMI_Class Type Object*/
static void PMI_Class_dealloc(PMI_Class *self)
{
	Py_XDECREF(self->miClass);
	Py_XDECREF(self->methods);
	Py_XDECREF(self->propertyValues); 
	Py_XDECREF(self->propertyTypes);
	/* Free the memory of the type object */
	self->ob_type->tp_free((PyObject*) self); 
}

static PyObject* PMI_Class_new(PyTypeObject *type)
{
    PMI_Class *self;
    self = (PMI_Class *)type->tp_alloc(type,0);
    if(self != NULL)
	{
		self->miClass = NULL;
		self->methods = NULL;
		self->propertyValues = NULL;
		self->propertyTypes = NULL;    
	}
    return (PyObject *)self;
}

static PyTypeObject PMI_ClassType ;

static PyObject* init_PMI_Class()
{
    return PyObject_CallObject((PyObject*) &PMI_ClassType, NULL);
}

static int PMI_Class_init(PMI_Class *self)
{
    self-> miClass = NULL;
    return 0;

}

static PyMethodDef PMI_Class_methods [] = {
    {NULL}
};

static PyObject *MakeMethodsDict(PMI_Class *pmiClass)
{
	MI_Uint32 elementCount;
    MI_Result miResult;
    MI_Uint32 elementIndex;
	const MI_Class *miClass = pmiClass->miClass;

    miResult = MI_Class_GetMethodCount(miClass, &elementCount);
    if(miResult != MI_RESULT_OK)
    {
		PyErr_SetString(PyExc_Exception,"MI_Class_GetMethodCount failed");
		return NULL;
    }

	PyObject *methodsList = PyList_New(0);
	
    for(elementIndex = 0; elementIndex != elementCount; elementIndex++)
    {
		const MI_Char *elementName;
		MI_QualifierSet qualifierSet;
		MI_ParameterSet parameterSet;

		miResult = MI_Class_GetMethodAt(miClass,elementIndex,&elementName,&qualifierSet,&parameterSet);
		if(miResult != MI_RESULT_OK)
		{
			PyErr_SetString(PyExc_Exception,"MI_Class_GetMethod failed");
			return NULL;
		}
		PyList_Append(methodsList,Py_BuildValue("s",elementName));
    }
	pmiClass->methods = methodsList;
	Py_INCREF(Py_None);
	return Py_None;

}

static PyObject *MakePropertyValueAndTypeDict(PMI_Class *pmiClass)
{
	MI_Uint32 elementCount;
    MI_Result miResult;
    MI_Uint32 elementIndex;
	const MI_Class *miClass = pmiClass->miClass;

    miResult = MI_Class_GetElementCount(miClass, &elementCount);
    if(miResult != MI_RESULT_OK)
    {
		PyErr_SetString(PyExc_Exception,"MI_Class_GetElementCount failed");
		return NULL;
    }

	PyObject *propertyValues = PyDict_New();
	PyObject *propertyTypes = PyDict_New();
    for(elementIndex = 0; elementIndex != elementCount; elementIndex++)
    {
		const MI_Char *elementName;
		MI_Value elementValue;
		MI_Type elementType;
		MI_Uint32 elementFlags;
		MI_Boolean exists;
		MI_Char *referenceClass; /* This piece of memory is handled by MI client API */
		MI_QualifierSet qualifierSet;
		miResult = MI_Class_GetElementAt(miClass,elementIndex,&elementName,&elementValue,&exists,&elementType,&referenceClass,&qualifierSet,&elementFlags);
		if(miResult != MI_RESULT_OK)
		{
	  		PyErr_SetString(PyExc_Exception,"MI_Class_GetElement failed");
			return NULL;
		}

		char *key = (char *)elementName;
		PyObject *value = Get_Element_Value(&elementValue,elementType);
		if(PyDict_SetItemString(propertyValues,key,value))
		{
			PyErr_SetString(PyExc_Exception,"Property dictionary insert item failed");
			return NULL;
		}

		PyObject *typeValue =PyInt_FromLong(elementType); 
		if(PyDict_SetItemString(propertyTypes,key,typeValue))
		{
			PyErr_SetString(PyExc_Exception,"PropertyType dictionary insert item failed");
			return NULL;
		}
    }

	pmiClass->propertyValues = propertyValues;
	pmiClass->propertyTypes = propertyTypes;
	Py_INCREF(Py_None);
	return Py_None;
}


static PyObject *EnumerateClassMethods(PMI_Class *pmiClass)
{
	PyObject *methods = pmiClass->methods;
	if(methods != NULL)
	{
		return methods;
	}
	else
	{
		PyErr_SetString(PyExc_Exception,"Class doesn't have any methods");
		return NULL;
	}
}

static PyObject *EnumerateClassProperties(PMI_Class *pmiClass)
{
	PyObject *properties = pmiClass->propertyValues;
	if(properties != NULL)
	{
		return properties;
	}
	else
	{
		PyErr_SetString(PyExc_Exception,"Class doesn't have any properties");
		return NULL;
	}
}

static PyObject *EnumerateClassPropertyTypes(PMI_Class *pmiClass)
{
	PyObject *propertyTypes = pmiClass->propertyTypes;
	if(propertyTypes != NULL)
	{
		return propertyTypes;
	}
	else
	{
		PyErr_SetString(PyExc_Exception,"Class doesn't have any propertyTypes");
		return NULL;
	}
}
static PyObject* PMI_Class_getattr(PMI_Class* self, char* propertyName)
{
    PMI_Class *pmiClass = (PMI_Class *)self;
    const MI_Class* class = pmiClass-> miClass;
    if(class == NULL)
    {
		PyErr_SetString(PyExc_Exception,"MI_Class GetProperty failed due to a null MI_Instance");
		return NULL;
    }
	if(!strcmp(propertyName,"methods"))
	{
		return EnumerateClassMethods(self);
	}
	else if(!strcmp(propertyName,"properties"))
	{
		return EnumerateClassProperties(self);
	}
	else if(!strcmp(propertyName,"className"))
	{
		const MI_Char *className;
		MI_Class_GetClassName(class,&className);
		return Py_BuildValue("s",className);
	}
	else if(!strcmp(propertyName,"nameSpace"))
	{
		const MI_Char *nameSpace;
		MI_Class_GetNameSpace(class,&nameSpace);
		return Py_BuildValue("s",nameSpace);
	}
	else if(!strcmp(propertyName,"propertyTypes"))
	{
		return EnumerateClassPropertyTypes(self);
	}
	else
	{
		PyErr_SetString(PyExc_Exception,"MI_class don't have the property");
		return NULL;
	}
}


static PyTypeObject PMI_ClassType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PMI_Class.PMI_Class",             /* tp_name */
    sizeof(PMI_Class), /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)PMI_Class_dealloc,     /* tp_dealloc */
    0,                         /* tp_print */
    (getattrfunc)PMI_Class_getattr,                         /* tp_getattr */
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
    "MI_Class objects",           /* tp_doc */
    0,			       /* tp_traverse */
    0,		               /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PMI_Class_methods,             /* tp_methods */
    0,		               /* tp_members */
    0,    /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PMI_Class_init,      /* tp_init */
    0,                         /* tp_alloc */
    (newfunc)PMI_Class_new,                 /* tp_new */
};	    


#define PyMODINIT_FUNC void
#ifndef PyMODINIT_FUNC
#endif
PyMODINIT_FUNC
initPMI_Class(void)
{ 
    PyObject *m;
    PMI_ClassType.tp_new = PyType_GenericNew;
    /*Make sure the new type object is initialized properly*/
    if (PyType_Ready(&PMI_ClassType) <0)
	return;
    /*New type objects are all exported into mi module*/
    m = Py_InitModule3("mi",PMI_Class_methods, "MI_Class object");
    Py_INCREF(&PMI_ClassType);
    PyModule_AddObject(m, "PMI_Class", (PyObject *)&PMI_ClassType);
}
