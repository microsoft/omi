/* @migen@ */
#include <MI.h>
#include "ContactInfo.h"
#include "CIM_Error.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "common.h"

#ifdef _MSC_VER

#include <Windows.h>
#include <ProviderUtil.h>
#include <WbemProv.h>
#include <strsafe.h>

static FastReentrantLock instanceStoreSync;

#endif

#define ONLOAD_INSTANCES_CONTACTINFO 10

struct _ContactInfo_Self 
{
	std::vector<ContactInfo *> instanceStore;	
};


void PopulateCIMErrorContactInfo(CIM_Error *error, MI_Char* message, MI_Uint32 statusCode, MI_Char* errorSource, MI_ErrorCategory errorType, MI_Char* messageID)
{
	CIM_Error_Set_Message(error, message);
	CIM_Error_Set_CIMStatusCode(error, statusCode);
	CIM_Error_Set_ErrorSource(error, errorSource);
	CIM_Error_Set_ErrorType(error, errorType);
	CIM_Error_Set_MessageID(error, messageID);
}

bool PreCheckContactInfo(ContactInfo_Self* self, MI_Context* context, CIM_Error *error)
{
	//MI_Instance *error = NULL;

#ifdef _MSC_VER

	auto hold(instanceStoreSync.Hold());

#endif

	if(self->instanceStore.size() <= 0) 
	{		
		//MI_Utilities_CimErrorFromErrorCode(ERROR_NOT_FOUND, MI_RESULT_TYPE_WIN32, MI_T("No instances exist. Do you want to continue?"), &error);
		//MI_Utilities_CimErrorFromErrorCode(MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("No instances exist. Do you want to continue?"), &error);

		MI_Char message[100];
		memset(message, 0, sizeof(MI_Char) * 100);
		sprintf(message, MI_T("%s"), MI_T("No instances exist. Do you want to continue?"));
		
		MI_Char errorSource[100];
		memset(errorSource, 0, sizeof(MI_Char) * 100);
		sprintf(message, MI_T("%s"), MI_T("PreCheckContactInfo"));

		MI_Char messageID[100];
		memset(messageID, 0, sizeof(MI_Char) * 100);
		sprintf(message, MI_T("%s"), MI_T("MI_RESULT_NOT_FOUND"));		

		//PopulateCIMErrorContactInfo(error, MI_T("No instances exist. Do you want to continue?"), MI_RESULT_NOT_FOUND, MI_T("PreCheckContactInfo"), MI_ERRORCATEGORY_NOT_SPECIFIED, MI_T("MI_RESULT_NOT_FOUND"));
		PopulateCIMErrorContactInfo(error, message, MI_RESULT_NOT_FOUND, errorSource, MI_ERRORCATEGORY_NOT_SPECIFIED, messageID);
				
		MI_Boolean userIntent;

		/* NTE */ 
		MI_WriteCimError(context, &error->__instance, &userIntent);

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
	ContactInfo temp;
	ContactInfo_Construct(&temp, context);
	ContactInfo *onLoadInstance = NULL;

	for(MI_Uint32 i = 0; i < ONLOAD_INSTANCES_CONTACTINFO; i++)
	{
//		std::wstringstream wsStreamCity; 

		MI_Char streamCity[100];
		memset(streamCity, 0, sizeof(MI_Char) * 100);

		ContactInfo_Clone(&temp, &onLoadInstance);

		//wsStreamCity << MI_T("City ") << i; 

		sprintf(streamCity, MI_T("City %d"), i);
		
		//ContactInfo_Set_City(onLoadInstance, wsStreamCity.str().c_str());
		ContactInfo_Set_City(onLoadInstance, streamCity);

		ContactInfo_Set_zipCode(onLoadInstance, (MI_Uint16) 10000 +  (MI_Uint16) i);

		ContactInfo_Set_addressId(onLoadInstance, i);

		MI_Char ** dataPtr = (MI_Char **) malloc (sizeof(MI_Char *) * i);
		
		for(MI_Uint32 j = 0; j < i; j++)
		{
			//std::wstringstream wsStreamPhone; 
			dataPtr[j] = (MI_Char *) malloc (sizeof(MI_Char) * 100);

			//wsStreamPhone << L"123-456-789" << j;
			sprintf(dataPtr[j], MI_T("123-456-789%d"), j);

			//StringCchPrintf((LPWSTR) dataPtr[j], MAX_PATH, L"%s", wsStreamPhone.str().c_str());
		}

		ContactInfo_Set_phoneNumber(onLoadInstance, (const MI_Char**) dataPtr, i);

		for(MI_Uint32 j = 0; j < i; j++)
		{
			free((void*) dataPtr[j]);
		}

		free(dataPtr);

#ifdef _MSC_VER
		auto hold(instanceStoreSync.Hold());
#endif

		self->instanceStore.push_back(onLoadInstance);
	}

	ContactInfo_Destruct(&temp);
}

void MI_CALL ContactInfo_Load(
	ContactInfo_Self** self,
	MI_Module_Self* selfModule,
	MI_Context* context)
{
	*self = new ContactInfo_Self;
	(*self)->instanceStore.clear();

	Onload_Contact(*self, context);
	
	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_Unload(
	ContactInfo_Self* self,
	MI_Context* context)
{
	std::vector<ContactInfo *>::iterator it;
#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif
	for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
	{	
		ContactInfo_Delete((*it));
	}

	self->instanceStore.clear();

	delete self;

	MI_PostResult(context, MI_RESULT_OK);
}

//To Get a CIM Error call enumerate after deleting all the instances

void MI_CALL ContactInfo_EnumerateInstances(
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_PropertySet* propertySet,
	MI_Boolean keysOnly,
	const MI_Filter* filter)
{	
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;

	CIM_Error error;
	CIM_Error_Construct(&error, context);
		
	if(!PreCheckContactInfo(self, context, &error))
	{		
		//MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
		MI_Context_PostCimError(context, &error.__instance);
		CIM_Error_Destruct(&error);
		return;
	}

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

	for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
	{
		result = ContactInfo_Post((*it), context);

		if(result == MI_RESULT_OK)
			MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_VERBOSE, MI_T("Posted instance"));
		else
			break;
	}

	if(result != MI_RESULT_OK)
		POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));
		
	MI_PostResult(context, result);
}

void MI_CALL ContactInfo_GetInstance(
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const ContactInfo* instanceName,
	const MI_PropertySet* propertySet)
{
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;

	MI_Boolean foundInstance = MI_FALSE;

	CIM_Error error;
	CIM_Error_Construct(&error, context);
	
	if(!PreCheckContactInfo(self, context, &error))
	{
		MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
		CIM_Error_Destruct(&error);
		return;
	}

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

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

#ifdef _MSC_VER
	hold.Unlock();
#endif

	if(foundInstance != MI_TRUE)
	{
		MI_WriteMessage(context, MI_WRITEMESSAGE_CHANNEL_WARNING, MI_T("Instance not found"));
		result = MI_RESULT_NOT_FOUND;
	}
	
	if(result == MI_RESULT_NOT_FOUND)
		POST_ERROR(context, MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("Instance not found, sending HRESULT"));

	if(result != MI_RESULT_OK)
		POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

	CIM_Error_Destruct(&error);

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_CreateInstance(
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const ContactInfo* newInstance)
{
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;
	
	MI_Instance *errorInstance = NULL;

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

	for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
	{
		if((*it)->addressId.value == newInstance->addressId.value)
		{			
			//MI_Utilities_CimErrorFromErrorCode(MI_RESULT_ALREADY_EXISTS, MI_RESULT_TYPE_MI, MI_T("Key already exists"), &errorInstance);

			MI_PostCimError(context, errorInstance);

			MI_Instance_Delete(errorInstance);

			return;
		}
	}

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
		//MI_Utilities_CimErrorFromErrorCode(MI_RESULT_SERVER_LIMITS_EXCEEDED, MI_RESULT_TYPE_MI, MI_T("Cloning failed"), &errorInstance);

		MI_PostCimError(context, errorInstance);
		
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
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const ContactInfo* modifiedInstance,
	const MI_PropertySet* propertySet)
{
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;

	MI_Boolean foundInstance = MI_FALSE;

	CIM_Error error;
	CIM_Error_Construct(&error, context);

	CIM_Error_Destruct(&error);
	
	if(!PreCheckContactInfo(self, context, &error))
	{
		MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
		CIM_Error_Destruct(&error);
		return;
	}

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

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
		result = MI_RESULT_NOT_FOUND;
	}

	if(result == MI_RESULT_NOT_FOUND)
		POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));	

	if(result != MI_RESULT_OK)
		POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

	CIM_Error_Destruct(&error);

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_DeleteInstance(
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const ContactInfo* instanceName)
{
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;

	MI_Boolean foundInstance = MI_FALSE;
	MI_Boolean userIntent = MI_FALSE;

	CIM_Error error;
	CIM_Error_Construct(&error, context);

	if(!PreCheckContactInfo(self, context, &error))
	{
		MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
		CIM_Error_Destruct(&error);
		return;
	}

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

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

#ifdef _MSC_VER
	hold.Unlock();
#endif

	if(result != MI_RESULT_OK)
		POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

	CIM_Error_Destruct(&error);

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ContactInfo_Invoke_GetPhoneNumbers(
	ContactInfo_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const ContactInfo* instanceName,
	const ContactInfo_GetPhoneNumbers* in)
{
	MI_Result result = MI_RESULT_FAILED;
	std::vector<ContactInfo *>::iterator it;

	ContactInfo_GetPhoneNumbers getPhoneNumbers;
	ContactInfo_GetPhoneNumbers_Construct(&getPhoneNumbers, context);

	MI_Boolean foundInstance = MI_FALSE;

	CIM_Error error;
	CIM_Error_Construct(&error, context);
	
	if(!PreCheckContactInfo(self, context, &error))
	{
		MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("User aborted"));
		CIM_Error_Destruct(&error);
		return;
	}

#ifdef _MSC_VER
	auto hold(instanceStoreSync.Hold());
#endif

	for(it = self->instanceStore.begin(); it != self->instanceStore.end(); it++)
	{
		if((*it)->addressId.value == instanceName->addressId.value)
		{
			MI_Value val;

			val.stringa.data = (MI_Char**) ((*it)->phoneNumber.value.data);				
			val.stringa.size = ((*it)->phoneNumber.value.size);

			result = MI_WriteStreamParameter(context, MI_T("numbers"), &val, MI_STRINGA, MI_FLAG_STREAM);

			break;
		}
	}

	//returns 0 when succeeds.
	ContactInfo_GetPhoneNumbers_Set_MIReturn(&getPhoneNumbers, (MI_Uint32) !foundInstance);

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

