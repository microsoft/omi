/* @migen@ */
#include <MI.h>
#include "ContactInfo.h"
#include "TestCIM_Error.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <pal/format.h>

#include "common.h"

#ifdef _MSC_VER
#include <Windows.h>
#include <strsafe.h>
#endif

#ifndef ERROR_ALREADY_EXISTS
#define ERROR_ALREADY_EXISTS 183
#endif

#ifndef ERROR_NO_MATCH
#define ERROR_NO_MATCH 1169
#endif

#define WBEM_E_NOT_FOUND  0x80041002
#define ONLOAD_INSTANCES_CONTACTINFO 10

struct _ContactInfo_Self 
{
    std::vector<ContactInfo *> instanceStore;    
};


void PopulateCIMErrorContactInfo(TestCIM_Error *error, MI_Uint32 internalErr, const MI_Char* message, MI_Uint32 statusCode, const MI_Char* errorSource, MI_ErrorCategory errorType, const MI_Char* messageID)
{
    // additional Property code
    TestCIM_Error_Set_errResult(error, internalErr);
    // CIM_Error property
    TestCIM_Error_Set_Message(error, message);
    TestCIM_Error_Set_CIMStatusCode(error, statusCode);
    TestCIM_Error_Set_ErrorSource(error, errorSource);
    TestCIM_Error_Set_ErrorType(error, errorType);
    TestCIM_Error_Set_MessageID(error, messageID);
}

bool PreCheckContactInfo(ContactInfo_Self* self, MI_Context* context, TestCIM_Error *error)
{
    if(self->instanceStore.size() <= 0) 
    {        
        //MI_Utilities_CimErrorFromErrorCode(ERROR_NOT_FOUND, MI_RESULT_TYPE_WIN32, MI_T("No instances exist. Do you want to continue?"), &error);
        //MI_Utilities_CimErrorFromErrorCode(MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("No instances exist. Do you want to continue?"), &error);

        MI_Char message[100];
        memset(message, 0, sizeof(MI_Char) * 100);
        Stprintf(message, 100, MI_T("%s"), MI_T("No instances exist. Do you want to continue?"));
        
        MI_Char errorSource[100];
        memset(errorSource, 0, sizeof(MI_Char) * 100);
        Stprintf(message, 100, MI_T("%s"), MI_T("PreCheckContactInfo"));

        MI_Char messageID[100];
        memset(messageID, 0, sizeof(MI_Char) * 100);

        Stprintf(message, 100, MI_T("%s"), MI_T("MI_RESULT_NOT_FOUND"));        
        PopulateCIMErrorContactInfo(error, ERROR_NO_MATCH, MI_T("No instances exist. Do you want to continue?"), MI_RESULT_NOT_FOUND, MI_T("PreCheckContactInfo"), MI_ERRORCATEGORY_NOT_SPECIFIED, MI_T("MI_RESULT_NOT_FOUND"));

        MI_Boolean userIntent = MI_TRUE;

        /* NTE */ 
#ifdef _MSC_VER
        MI_WriteCimError(context, &error->__instance, &userIntent);
#endif
        if(userIntent == MI_FALSE)
        {    
            //MI_Instance_Delete(error);
            return false;
        }        
    }
    else
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_DEBUG, MI_T("More than 0 instances exist")); 
    }

    //if(error != NULL)
        //MI_Instance_Delete(error);

    return true;
}

void Onload_Contact(ContactInfo_Self *self, MI_Context* context)
{
    ContactInfo temp = {{0}};
    ContactInfo_Construct(&temp, context);
    ContactInfo *onLoadInstance = NULL;

    for(MI_Uint32 i = 0; i < ONLOAD_INSTANCES_CONTACTINFO; i++)
    {
//        std::wstringstream wsStreamCity; 

        MI_Char streamCity[100];
        memset(streamCity, 0, sizeof(MI_Char) * 100);

        ContactInfo_Clone(&temp, &onLoadInstance);

        //wsStreamCity << MI_T("City ") << i; 
        Stprintf(streamCity, 100, MI_T("City %d"), i);
        
        //ContactInfo_Set_City(onLoadInstance, wsStreamCity.str().c_str());
        ContactInfo_Set_City(onLoadInstance, streamCity);

        ContactInfo_Set_zipCode(onLoadInstance, (MI_Uint16) 10000 +  (MI_Uint16) i);

        ContactInfo_Set_addressId(onLoadInstance, i);

        if (i > 0)
        {
            MI_Char ** dataPtr = (MI_Char **) PAL_Malloc(sizeof(MI_Char *) * i);
            
            if (dataPtr != NULL)
            {
                for(MI_Uint32 j = 0; j < i; j++)
                {
                    //std::wstringstream wsStreamPhone; 
                    dataPtr[j] = (MI_Char *) PAL_Malloc(sizeof(MI_Char) * 100);

                    if (dataPtr[j] != NULL)
                    {
                        //wsStreamPhone << L"123-456-789" << j;
                        Stprintf(dataPtr[j], 100, MI_T("123-456-789%d"), j);
                    }
                    //StringCchPrintf((LPWSTR) dataPtr[j], MAX_PATH, L"%s", wsStreamPhone.str().c_str());
                }

                ContactInfo_Set_phoneNumber(onLoadInstance, (const MI_Char**) dataPtr, i);

                for(MI_Uint32 j = 0; j < i; j++)
                {
                    if (dataPtr[j] != NULL)
                    {
                        PAL_Free((void*) dataPtr[j]);
                    }
                }

                PAL_Free(dataPtr);
            }
        }
        
        self->instanceStore.push_back(onLoadInstance);
    }

    ContactInfo_Destruct(&temp);
}

void MI_CALL ContactInfo_Load(
    _Outptr_result_maybenull_ ContactInfo_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    *self = new ContactInfo_Self;
    (*self)->instanceStore.clear();

    Onload_Contact(*self, context);
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_Unload(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context)
{
    if (self != NULL)
    {
        std::vector<ContactInfo *>::iterator it;
        for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
        {    
            ContactInfo_Delete((*it));
        }

        self->instanceStore.clear();

        delete self;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

//To Get a CIM Error call enumerate after deleting all the instances

void MI_CALL ContactInfo_EnumerateInstances(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{    
    MI_Result result = MI_RESULT_FAILED;
    
    if (self != NULL)
    {
        std::vector<ContactInfo *>::iterator it;

        TestCIM_Error error;
        TestCIM_Error_Construct(&error, context);

        if(!PreCheckContactInfo(self, context, &error))
        {        
            MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
            TestCIM_Error_Destruct(&error);        
            return;
        }


        for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
        {
            result = ContactInfo_Post((*it), context);

            if(result == MI_RESULT_OK)
                MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Posted instance"));
            else
                break;
        }
    }

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));
        
    MI_PostResult(context, result);
}

void MI_CALL ContactInfo_GetInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{   
    if (self != NULL)
    {
        MI_Result result = MI_RESULT_FAILED;
        std::vector<ContactInfo *>::iterator it;

        MI_Boolean foundInstance = MI_FALSE;

        TestCIM_Error error;
        TestCIM_Error_Construct(&error, context);
    
        if(!PreCheckContactInfo(self, context, &error))
        {
            MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
            TestCIM_Error_Destruct(&error);
            return;
        }

        for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
        {
            if((*it)->addressId.value == instanceName->addressId.value)
            {
                result = ContactInfo_Post((*it), context);

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
    
        if(result == MI_RESULT_NOT_FOUND)
            // MI type: MI_RESULT_NOT_FOUND
            POST_ERROR(context, MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("Instance not found, sending HRESULT"));

        if(result != MI_RESULT_OK)
        {
            PopulateCIMErrorContactInfo(&error, result, MI_T("No instances exists!"), MI_RESULT_NOT_FOUND, MI_T("GetInstance"), MI_ERRORCATEGORY_INVALID_DATA, MI_T("MI_RESULT_NOT_FOUND Empty"));
            // PostCiMError
            MI_PostCimError(context, &error.__instance);
            TestCIM_Error_Destruct(&error);
            return;
        }
        TestCIM_Error_Destruct(&error);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_CreateInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<ContactInfo *>::iterator it;
    
    MI_Instance *errorInstance = NULL;
    TestCIM_Error error;
    TestCIM_Error_Construct(&error, context);

    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        if((*it)->addressId.value == newInstance->addressId.value)
        {            
            PopulateCIMErrorContactInfo(&error, ERROR_ALREADY_EXISTS, MI_T("Key already exists"), ERROR_ALREADY_EXISTS, MI_T("CreateInstance"), MI_ERRORCATEGORY_RESOURCE_EXISTS, MI_T("ERROR_ALREADY_EXISTS"));
            errorInstance = &error.__instance;
            MI_PostCimError(context, errorInstance);
            TestCIM_Error_Destruct(&error);
            return;
        }
    }
    TestCIM_Error_Destruct(&error);

    MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("No such instance already exists, so attempting to create an instance."));                

    ContactInfo *temp = NULL;
    result = ContactInfo_Clone(newInstance, &temp);

    if(result == MI_RESULT_OK)
    {
        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Instance cloning successful."));

        self->instanceStore.push_back(temp);

        result = ContactInfo_Post(temp, context);

        MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Instance created successfully"));
    }
    else
    {
#ifdef _MSC_VER
        MI_Utilities_CimErrorFromErrorCode(MI_RESULT_SERVER_LIMITS_EXCEEDED, MI_RESULT_TYPE_MI, MI_T("Cloning failed"), &errorInstance);
        MI_PostCimError(context, errorInstance);
#else
        POST_ERROR(context, MI_RESULT_SERVER_LIMITS_EXCEEDED, MI_RESULT_TYPE_MI, MI_T("Cloning failed"));
#endif        
        if(errorInstance != NULL)
            MI_Instance_Delete(errorInstance);
        return;
    }
        
    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

    if(errorInstance != NULL)
        MI_Instance_Delete(errorInstance);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_ModifyInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    if (self != NULL)
    {
        MI_Result result = MI_RESULT_FAILED;

        std::vector<ContactInfo *>::iterator it;

        MI_Boolean foundInstance = MI_FALSE;

        TestCIM_Error error;
        TestCIM_Error_Construct(&error, context);
    
        if(!PreCheckContactInfo(self, context, &error))
        {
            MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
            TestCIM_Error_Destruct(&error);
            return;
        }

        TestCIM_Error_Destruct(&error);

        for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
        {
            if((*it)->addressId.value == modifiedInstance->addressId.value)
            {
                result = ContactInfo_Clone(modifiedInstance, &(*it));

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
            MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_WARNING, MI_T("Instance not found"));
            POST_ERROR(context, ERROR_NO_MATCH, MI_RESULT_TYPE_WIN32, MI_T("Key NOT match"));
        }
        if(result != MI_RESULT_OK)
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_DeleteInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const ContactInfo* instanceName)
{
    if (self != NULL)
    {
        MI_Result result = MI_RESULT_FAILED;
        std::vector<ContactInfo *>::iterator it;

        MI_Boolean foundInstance = MI_FALSE;
        MI_Boolean userIntent = MI_FALSE;

        TestCIM_Error error;
        TestCIM_Error_Construct(&error, context);

        if(!PreCheckContactInfo(self, context, &error))
        {
            MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
            TestCIM_Error_Destruct(&error);
            return;
        }

        TestCIM_Error_Destruct(&error);

        for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
        {
            if((*it)->addressId.value == instanceName->addressId.value)
            {
                if((result = MI_PromptUser(context, MI_T("Do you want to delete the contact info?"), MI_PROMPTTYPE_NORMAL, &userIntent)) != MI_RESULT_OK)
                    break;
                        
                if(userIntent == MI_TRUE)
                {
                    foundInstance = MI_TRUE;
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
            result = MI_RESULT_NOT_FOUND;
        }
        else
        {
            ContactInfo_Delete((*it));
            self->instanceStore.erase(it);
        }

        if(result != MI_RESULT_OK)
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_Invoke_GetPhoneNumbers(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_GetPhoneNumbers* in)
{
    MI_Result result = MI_RESULT_FAILED;
    std::vector<ContactInfo *>::iterator it;

    ContactInfo_GetPhoneNumbers getPhoneNumbers = {{0}};
    ContactInfo_GetPhoneNumbers_Construct(&getPhoneNumbers, context);

    MI_Boolean foundInstance = MI_FALSE;

    TestCIM_Error error;
    TestCIM_Error_Construct(&error, context);
    
    if(!PreCheckContactInfo(self, context, &error))
    {
        MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
        TestCIM_Error_Destruct(&error);
        return;
    }

    TestCIM_Error_Destruct(&error);

    result = MI_RESULT_NOT_FOUND;
    for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
    {
        if((*it)->addressId.value == instanceName->addressId.value)
        {
            MI_Value val;

            if((*it)->phoneNumber.value.size > 0)
            {
                val.stringa.data = (MI_Char**) ((*it)->phoneNumber.value.data);                
                val.stringa.size = ((*it)->phoneNumber.value.size);
#ifdef _MSC_VER
                result = MI_WriteStreamParameter(context, MI_T("numbers"), &val, MI_STRINGA, MI_FLAG_STREAM);
#endif
                foundInstance = MI_TRUE;            
            }
            else
            {
                POST_ERROR(context, MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("Could not post PhoneNumber: null or empty"));
            }
            break;
        }
    }

    //returns 0 when succeeds.
    ContactInfo_GetPhoneNumbers_Set_MIReturn(&getPhoneNumbers, (MI_Uint32) (foundInstance)?0: result);

    result = ContactInfo_GetPhoneNumbers_Post(&getPhoneNumbers, context);

    ContactInfo_GetPhoneNumbers_Destruct(&getPhoneNumbers);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_Invoke_OperationOptionsStatic(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_OperationOptionsStatic* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    POST_ERROR(context, MI_RESULT_NOT_SUPPORTED, MI_RESULT_TYPE_MI, MI_T("Invoke OperationOptionsStatic is not supported"));
}

void MI_CALL ContactInfo_Invoke_OperationOptionsInstance(
    _In_opt_ ContactInfo_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const ContactInfo* instanceName,
    _In_opt_ const ContactInfo_OperationOptionsInstance* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    POST_ERROR(context, MI_RESULT_NOT_SUPPORTED, MI_RESULT_TYPE_MI, MI_T("Invoke OperationOptionsStatic is not supported"));
}

