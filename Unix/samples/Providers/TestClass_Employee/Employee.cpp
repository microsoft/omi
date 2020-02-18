/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "Employee.h"
#include "CIM_Error.h"
#include <vector>
#include <stdlib.h>
#include <pal/format.h>
#include <pal/strings.h>

#define ONLOAD_INSTANCES_EMPLOYEE 10

struct _Employee_Self
{
    std::vector<Employee *> instanceStore;
};

void PopulateCIMError(CIM_Error *error, const MI_Char* message, MI_Uint32 statusCode, const MI_Char* errorSource, MI_ErrorCategory errorType, const MI_Char* messageID)
{
    CIM_Error_Set_Message(error, message);
    CIM_Error_Set_CIMStatusCode(error, statusCode);
    CIM_Error_Set_ErrorSource(error, errorSource);
    CIM_Error_Set_ErrorType(error, errorType);
    CIM_Error_Set_MessageID(error, messageID);
}

bool PreCheckEmployee(Employee_Self* self, CIM_Error *error, MI_Context* context)
{
    if(self->instanceStore.size() <= 0)
    {
        MI_Char message[100];
        MI_Char errorSource[100];
        MI_Char messageID[100];

        memset(message, 0, sizeof(MI_Char) * 100);
        memset(errorSource, 0, sizeof(MI_Char) * 100);
        memset(messageID, 0, sizeof(MI_Char) * 100);

        Stprintf(message, 100, MI_T("%s"), MI_T("No instances exist. Do you want to continue?"));
        Stprintf(errorSource, 100, MI_T("%s"), MI_T("PreCheckEmployee"));
        Stprintf(messageID, 100, MI_T("%s"), MI_T("Message ID"));

        //PopulateCIMError(error, MI_T("No instances exist. Do you want to continue?"), 2, MI_T("PreCheckEmployee"), MI_ERRORCATEGORY_OBJECT_NOT_FOUND, MI_T("Message ID"));
        PopulateCIMError(error, message, 2, errorSource, MI_ERRORCATEGORY_OBJECT_NOT_FOUND, messageID);
        
        MI_Boolean userIntent;

        /* NTE */ 
        MI_WriteCimError(context, &error->__instance, &userIntent);

        if(userIntent == MI_FALSE)
        {
            //MI_PostResultWithMessage(context, MI_RESULT_OK, MI_T("User cancelled"));            
            MI_PostResult(context, MI_RESULT_OK);
            return false;
        }        
    }
    else
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_DEBUG, MI_T("More than 0 instances exist")); 
    }

    return true;
}

void Onload_Employee(Employee_Self *self, MI_Context* context)
{
    Employee temp;
    Employee_Construct(&temp, context);
    Employee *onLoadInstance = NULL;

    for(MI_Uint32 i = 0; i < ONLOAD_INSTANCES_EMPLOYEE; i++)
    {
        //std::wstringstream wStreamSSN;
        //std::wstringstream wStreamfirstName;
        //std::wstringstream wStreamlastName;

        MI_Char streamSSN[100];
        memset(streamSSN, 0, sizeof(MI_Char) * 100);

        MI_Char streamFirstName[100];
        memset(streamFirstName, 0, sizeof(MI_Char) * 100);

        MI_Char streamLastName[100];
        memset(streamLastName, 0, sizeof(MI_Char) * 100);
                
        Employee_Clone(&temp, &onLoadInstance);

        //wStreamSSN << MI_T("111-00-12") << i; 
        Stprintf(streamSSN, 100, MI_T("111-00-12%d"), i);    

        Employee_Set_SSN(onLoadInstance, streamSSN);

        //wStreamfirstName << MI_T("John ") << i;
        Stprintf(streamFirstName, 100, MI_T("John %d"), i);

        Employee_Set_firstName(onLoadInstance, streamFirstName);

        //wStreamlastName << MI_T("Smith ") << i;
        Stprintf(streamLastName, 100, MI_T("Smith %d"), i);
        Employee_Set_lastName(onLoadInstance, streamLastName);

        MI_Datetime date;
        MI_Timestamp timestamp;

        timestamp.day = (1 + i) % 28;
        timestamp.month = (1 + i) % 12;
        timestamp.hour = 0;
        timestamp.microseconds = 0;
        timestamp.minute = 0;
        timestamp.second = 0;
        timestamp.utc = 0;

        timestamp.year = 1984 + i;

        date.isTimestamp = 1;
        date.u.timestamp = timestamp;

        Employee_Set_dateOfBirth(onLoadInstance, date);

        self->instanceStore.push_back(onLoadInstance);
    }

    Employee_Destruct(&temp);
}


void MI_CALL Employee_Load(
    Employee_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = new Employee_Self;

    (*self)->instanceStore.clear();

    Onload_Employee(*self, context);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Employee_Unload(
    Employee_Self* self,
    MI_Context* context)
{
    std::vector<Employee*>::iterator it;
    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        Employee_Delete((*it));
    }

    self->instanceStore.clear();

    delete self;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Employee_EnumerateInstances(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<Employee*>::iterator it;

    CIM_Error error;
    CIM_Error_Construct(&error, context);

    if(!PreCheckEmployee(self, &error, context))
    {
        CIM_Error_Destruct(&error);
        return;
    }

    MI_Uint32 totalEmployees = self->instanceStore.size();
    MI_Uint32 i = 1;

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        result = Employee_Post((*it), context);

        if(result == MI_RESULT_OK)
            MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Posted instance"));
        else
            break;

        MI_WriteProgress(context, MI_T("Employees"), MI_T("Enumeration"), MI_T("Listing all employees"), (MI_Uint32) (i / totalEmployees) * 100 , (MI_Uint32) (totalEmployees - i));
    }

    CIM_Error_Destruct(&error);

    MI_PostResult(context, result);
}

void MI_CALL Employee_GetInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<Employee *>::iterator it;

    MI_Boolean foundInstance = MI_FALSE;
    CIM_Error error;
    CIM_Error_Construct(&error, context);

    if(!PreCheckEmployee(self, &error, context))
    {
        CIM_Error_Destruct(&error);
        return;
    }

    MI_Instance* errorInstance = NULL;

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        if(Tcscasecmp((*it)->SSN.value, instanceName->SSN.value) == 0)
        {
            result = Employee_Post((*it), context);

            if(result == MI_RESULT_OK)
            {
                foundInstance = MI_TRUE;
                MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Posted instance"));                
            }

            break;
        }
    }

    if(foundInstance != MI_TRUE)
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_WARNING, MI_T("Instance not found"));        
        result = MI_RESULT_NOT_FOUND;        
    }    

    if(result != MI_RESULT_OK)
    {
        //MI_Utilities_CimErrorFromErrorCode(result, MI_RESULT_TYPE_MI, MI_T("Instance not found for request key"), &errorInstance);
        MI_PostCimError(context, errorInstance);
        MI_Instance_Delete(errorInstance);
        return;
    }
    else
    {
        MI_PostResult(context, result);
    }
}

void MI_CALL Employee_CreateInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<Employee *>::iterator it;

    CIM_Error error;
    CIM_Error_Construct(&error, context);

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        
        if(Tcscasecmp((*it)->SSN.value, newInstance->SSN.value) == 0) 
        {
            CIM_Error_Set_Message(&error, MI_T("Key already exists"));
            MI_PostCimError(context, &error.__instance);
            CIM_Error_Destruct(&error);
            return;
        }
    }

    if(newInstance->dateOfBirth.exists == 1) 
    {
        if(newInstance->dateOfBirth.value.isTimestamp == 0)
        {
            MI_Boolean userChoice = MI_FALSE;            
            CIM_Error_Set_Message(&error, MI_T("Date of birth cannot be an interval. Do you want to continue?"));
            MI_WriteCimError(context, &error.__instance, &userChoice);

            MI_Char message[100];
            MI_Char errorSource[100];
            MI_Char messageID[100];

            memset(message, 0, sizeof(MI_Char) * 100);
            memset(errorSource, 0, sizeof(MI_Char) * 100);
            memset(messageID, 0, sizeof(MI_Char) * 100);

            Stprintf(message, 100, MI_T("%s"), MI_T("Cannot create a date of birth with interval type date"));
            Stprintf(errorSource, 100, MI_T("%s"), MI_T("Employee_CreateInstance"));
            Stprintf(messageID, 100, MI_T("%s"), MI_T("MessageID"));
            
            if(userChoice == MI_FALSE)
            {
                //PopulateCIMError(&error, MI_T("Cannot create a date of birth with interval type date"), 2, MI_T("Employee_CreateInstance"), MI_ERRORCATEGORY_OBJECT_NOT_FOUND, MI_T("MessageID"));                
                PopulateCIMError(&error, message, 2, errorSource, MI_ERRORCATEGORY_OBJECT_NOT_FOUND, messageID);

                MI_PostCimError(context, &error.__instance);
                CIM_Error_Destruct(&error);
                return;
            }
        }
    }

    MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("No such instance already exists, so attempting to create an instance."));                

    Employee *temp = NULL;
    result = Employee_Clone(newInstance, &temp);

    if(result == MI_RESULT_OK)
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Instance cloning successful."));

        self->instanceStore.push_back(temp);

        result = Employee_Post(temp, context);

        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Instance created successfully"));
    }
    else
    {
        MI_Char message[100];
        MI_Char errorSource[100];
        MI_Char messageID[100];

        memset(message, 0, sizeof(MI_Char) * 100);
        memset(errorSource, 0, sizeof(MI_Char) * 100);
        memset(messageID, 0, sizeof(MI_Char) * 100);

        Stprintf(message, 100, MI_T("%s"), MI_T("Instance Cloning failed"));
        Stprintf(errorSource, 100, MI_T("%s"), MI_T("Employee_CreateInstance"));
        Stprintf(messageID, 100, MI_T("%s"), MI_T("MessageID"));

        //PopulateCIMError(&error, MI_T("Instance Cloning failed"), 2, MI_T("Employee_CreateInstance"), MI_ERRORCATEGORY_OBJECT_NOT_FOUND, MI_T("MessageID"));        
        PopulateCIMError(&error, message, 2, errorSource, MI_ERRORCATEGORY_OBJECT_NOT_FOUND, messageID);

        MI_PostCimError(context, &error.__instance);
        CIM_Error_Destruct(&error);
        return;
    }

    CIM_Error_Destruct(&error);

    MI_PostResult(context, result);
}

void MI_CALL Employee_ModifyInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<Employee *>::iterator it;

    MI_Boolean foundInstance = MI_FALSE;
    CIM_Error error;
    CIM_Error_Construct(&error, context);

    if(!PreCheckEmployee(self, &error, context))
    {
        CIM_Error_Destruct(&error);
        return;
    }

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        if(Tcscasecmp((*it)->SSN.value, modifiedInstance->SSN.value) == 0)
        {
            result = Employee_Clone(modifiedInstance, &(*it));

            if(result == MI_RESULT_OK)
            {
                foundInstance = MI_TRUE;
                MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Modified instance"));                
            }

            break;
        }
    }

    if(foundInstance != MI_TRUE)
    {
        MI_Char message[100];
        MI_Char errorSource[100];
        MI_Char messageID[100];

        memset(message, 0, sizeof(MI_Char) * 100);
        memset(errorSource, 0, sizeof(MI_Char) * 100);
        memset(messageID, 0, sizeof(MI_Char) * 100);

        Stprintf(message, 100, MI_T("%s"), MI_T("Instance not found for specified key"));
        Stprintf(errorSource, 100, MI_T("%s"), MI_T("Employee_ModifyInstance"));
        Stprintf(messageID, 100, MI_T("%s"), MI_T("MessageID"));

        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_WARNING, MI_T("Instance not found"));
        //PopulateCIMError(&error, MI_T("Instance not found for specified key"), 2, MI_T("Employee_ModifyInstance"), MI_ERRORCATEGORY_OBJECT_NOT_FOUND, MI_T("MessageID"));
        PopulateCIMError(&error, message, 2, errorSource, MI_ERRORCATEGORY_OBJECT_NOT_FOUND, messageID);
        result = MI_RESULT_NOT_FOUND;
    }

    if(result != MI_RESULT_OK)
    {
        MI_PostCimError(context, &error.__instance);
    }
    else
    {
        MI_PostResult(context, result);
    }

    CIM_Error_Destruct(&error);
}

void MI_CALL Employee_DeleteInstance(
    Employee_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Employee* instanceName)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<Employee *>::iterator it;

    MI_Boolean foundInstance = MI_FALSE;
    MI_Boolean userIntent = MI_FALSE;
    CIM_Error error;
    CIM_Error_Construct(&error, context);

    if(!PreCheckEmployee(self, &error, context))
    {
        CIM_Error_Destruct(&error);
        return;
    }

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        if(Tcscasecmp((*it)->SSN.value, instanceName->SSN.value) == 0)
        {
            foundInstance = MI_TRUE;

            if((result = MI_PromptUser(context, MI_T("Do you want to delete the employee?"), MI_PROMPTTYPE_CRITICAL, &userIntent)) != MI_RESULT_OK)
                break;

            if(userIntent == MI_TRUE)
            {
                Employee_Delete((*it));
                self->instanceStore.erase(it);                                
                result = MI_RESULT_OK;
                MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Deleted instance"));
            }
            else
            {
                result = MI_RESULT_OK;
                MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("User aborted"));                
            }

            break;
        }
    }

    if(foundInstance != MI_TRUE)
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_WARNING, MI_T("Instance not found"));

        MI_Char message[100];
        MI_Char errorSource[100];
        MI_Char messageID[100];

        memset(message, 0, sizeof(MI_Char) * 100);
        memset(errorSource, 0, sizeof(MI_Char) * 100);
        memset(messageID, 0, sizeof(MI_Char) * 100);

        Stprintf(message, 100, MI_T("%s"), MI_T("Instance not found for specified key"));
        Stprintf(errorSource, 100, MI_T("%s"), MI_T("Employee_DeleteInstance"));
        Stprintf(messageID, 100, MI_T("%s"), MI_T("MessageID"));

        //PopulateCIMError(&error, MI_T("Instance not found for specified key"), 2, MI_T("Employee_DeleteInstance"), MI_ERRORCATEGORY_OBJECT_NOT_FOUND, MI_T("MessageID"));
        PopulateCIMError(&error, message, 2, errorSource, MI_ERRORCATEGORY_OBJECT_NOT_FOUND, messageID);
        result = MI_RESULT_NOT_FOUND;
    }

    if(result != MI_RESULT_OK)
    {
        MI_PostCimError(context, &error.__instance);
    }
    else
    {
        MI_PostResult(context, result);
    }

    CIM_Error_Destruct(&error);
}

