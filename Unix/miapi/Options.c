/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "Options.h"
#include <base/conf.h>
#include <base/log.h>
#include <pal/strings.h>
#include <pal/encrypt.h>
#include <http/httpcommon.h>

extern MI_DestinationOptionsFT g_destinationOptionsFT;
extern MI_OperationOptionsFT g_operationOptionsFT;
extern MI_SubscriptionDeliveryOptionsFT g_subscriptionDeliveryOptionsFT;



MI_Result GenericOptions_Create(
    _Out_ struct _GenericOptions_Handle *options,
    _In_ void *ft)
{
    Batch *batch;
    struct _GenericOptions *genericOptions;

    batch = Batch_New(BATCH_MAX_PAGES);
    if (batch == NULL)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    genericOptions = Batch_Get(batch, sizeof(*genericOptions));
    if (genericOptions == NULL)
    {
        Batch_Delete(batch);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    
    genericOptions->batch = batch;
    genericOptions->credentialInstance = NULL;
    genericOptions->optionsInstance = NULL;
    genericOptions->referenceCount = 1;

    options->reserved1 = 0;
    options->genericOptions = genericOptions;
    options->ft = ft;

    return MI_RESULT_OK;
}


MI_Result MI_CALL GenericOptions_Delete(
    _Inout_ struct _GenericOptions_Handle *options)
{
    if (options && options->genericOptions)
    {
        if (Atomic_Dec(&options->genericOptions->referenceCount) == 0)
        {
            if (options->genericOptions->batch)
                Batch_Delete(options->genericOptions->batch);

            options->genericOptions = NULL;
            options->reserved1 = 0;
            options->ft = NULL;
        }
        return MI_RESULT_OK;
    }
    return MI_RESULT_INVALID_PARAMETER;
}

MI_Result MI_CALL GenericOptions_Clone(
    _In_ const struct _GenericOptions_Handle* options,
    _Out_ struct _GenericOptions_Handle* newOptions)
{
    if (options && newOptions)
    {
        struct _GenericOptions *genericOptions =  options->genericOptions;
        MI_Result miResult;
        miResult = GenericOptions_Create(newOptions, options->ft);
        if (miResult == MI_RESULT_OK)
        {
            if (genericOptions->optionsInstance)
            {
                miResult = Instance_Clone(genericOptions->optionsInstance, &newOptions->genericOptions->optionsInstance, newOptions->genericOptions->batch);
                if (miResult != MI_RESULT_OK)
                {
                    GenericOptions_Delete(newOptions);
                    return miResult;
                }
            }
            if (genericOptions->credentialInstance)
            {
                miResult = Instance_Clone(genericOptions->credentialInstance, &newOptions->genericOptions->credentialInstance, newOptions->genericOptions->batch);
                if (miResult != MI_RESULT_OK)
                {
                    GenericOptions_Delete(newOptions);
                }
            }
        }
        return miResult;
    }
    else
        return MI_RESULT_INVALID_PARAMETER;
}

MI_INLINE MI_Result _AddOrSetElement(_Inout_ MI_Instance *optionsInstance,
    _In_z_ const MI_Char* optionName,
    _In_opt_ const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    MI_Result miResult;

    miResult = MI_Instance_AddElement(optionsInstance, optionName, value, type, flags);
    if (miResult == MI_RESULT_ALREADY_EXISTS)
    {
        miResult = MI_Instance_SetElement(optionsInstance, optionName, value, type, flags);
    }
    return miResult;
}

MI_INLINE MI_Result _AddOrSetCustomElement(_Inout_ MI_Instance *optionsInstance, _Inout_ Batch *batch,
    _In_z_ const MI_Char* optionName,
    _In_opt_ const MI_Value* value,
    MI_Type type,
    MI_Boolean mustUnderstand,
    MI_Uint32 flags)
{
    MI_Instance *elem;
    MI_Result miResult;
    MI_Value tmpValue;
    MI_Type tmpType;

    miResult = MI_Instance_GetElement(optionsInstance, optionName, &tmpValue, &tmpType, NULL, NULL);
    if (miResult == MI_RESULT_NO_SUCH_PROPERTY)
    {
        miResult = Instance_NewDynamic(&elem, MI_T("_OMI_CustomOptionValue"), MI_FLAG_CLASS, batch);
        if (miResult != MI_RESULT_OK)
            return miResult;

        miResult = MI_Instance_AddElement(elem, MI_T("value"), value, type, 0);
        if (miResult != MI_RESULT_OK)
            return miResult;

        tmpValue.boolean = mustUnderstand;
        miResult = MI_Instance_AddElement(elem, MI_T("mustUnderstand"), &tmpValue, MI_BOOLEAN, 0);
        if (miResult != MI_RESULT_OK)
            return miResult;

        tmpValue.instance = elem;
        miResult = MI_Instance_AddElement(optionsInstance, optionName, &tmpValue, MI_INSTANCE, MI_FLAG_BORROW);
        return miResult;
    }
    else if (miResult != MI_RESULT_OK)
        return miResult;
    else
    {
        if (tmpType != MI_INSTANCE)
            return MI_RESULT_INVALID_PARAMETER;
        
        elem = tmpValue.instance;

        /* SetElement will fail if the type is changed */
        miResult = MI_Instance_SetElement(elem, MI_T("value"), value, type, 0);
        if (miResult != MI_RESULT_OK)
            return miResult;

        tmpValue.boolean = mustUnderstand;
        miResult = MI_Instance_SetElement(elem, MI_T("mustUnderstand"), &tmpValue, MI_BOOLEAN, 0);
        return miResult;
    }
}
MI_INLINE MI_Result _AddOrSetGenericOption(_Inout_ struct _GenericOptions *genericOptions,
    _In_z_ const MI_Char* optionName,
    _In_opt_ const MI_Value* optionValue,
    MI_Type optionType,
    MI_Uint32 elementFlags)
{
    MI_Result miResult;
    if ((genericOptions == NULL) || (genericOptions->batch == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (genericOptions->optionsInstance == NULL)
    {
        miResult = Instance_NewDynamic(&genericOptions->optionsInstance, MI_T("_OMI_OptionSet"), MI_FLAG_CLASS, genericOptions->batch);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
    }

    return _AddOrSetElement(genericOptions->optionsInstance, optionName, optionValue, optionType, elementFlags);
}

MI_INLINE MI_Result _AddOrSetGenericCustomOption(_Inout_ struct _GenericOptions *genericOptions,
    _In_z_ const MI_Char* optionName,
    _In_opt_ const MI_Value* optionValue,
    MI_Type optionType,
    MI_Boolean mustUnderstand,
    MI_Uint32 optionFlags)
{
    MI_Result miResult;
    if ((genericOptions == NULL) || (genericOptions->batch == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (genericOptions->optionsInstance == NULL)
    {
        miResult = Instance_NewDynamic(&genericOptions->optionsInstance, MI_T("_OMI_OptionSet"), MI_FLAG_CLASS, genericOptions->batch);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
    }

    return _AddOrSetCustomElement(genericOptions->optionsInstance, genericOptions->batch, optionName, optionValue, optionType, mustUnderstand, optionFlags);
}

MI_INLINE MI_Result _GetGenericOptionsValue(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Out_opt_ MI_Type *type,
    _Out_opt_ MI_Value *value,
    _Out_opt_ MI_Uint32 *index)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        if (genericOptions->optionsInstance)
        {
            return MI_Instance_GetElement(genericOptions->optionsInstance, optionName, value, type, 0, index);
        }
        else
            return MI_RESULT_NO_SUCH_PROPERTY;
    }
}


MI_Result MI_CALL GenericOptions_SetString(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_z_ const MI_Char *value,
            MI_Uint32 flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || flags)
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        MI_Value _value;

        _value.string = (MI_Char*)value;

        return _AddOrSetGenericOption(genericOptions, optionName, &_value, MI_STRING, 0);
    }
}

MI_Result MI_CALL GenericOptions_EnableDisableChannel(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   MI_Uint32 value,
            MI_Uint32 flags)
{
    MI_Type tmpType;
    MI_Value tmpValue;
    MI_Result miResult;
    MI_Uint32 index;

    /* Deal with channel enabling/disabling */
    miResult = _GetGenericOptionsValue(options, optionName, &tmpType, &tmpValue, NULL);
    if (miResult == MI_RESULT_NO_SUCH_PROPERTY)
    {
        /* Not there so we need to add it */
        miResult = MI_RESULT_OK;
        tmpValue.uint32a.data = NULL;
        tmpValue.uint32a.size = 0;
        tmpType = MI_UINT32A;
    }
    else if (miResult != MI_RESULT_OK)
        return miResult;
    else if (tmpType != MI_UINT32A)
        return MI_RESULT_INVALID_PARAMETER;

    for (index = 0; index != tmpValue.uint32a.size ; index++)
    {
        if (tmpValue.uint32a.data[index] == value)
        {
            if (flags == 0)
            {
                /* Already there */
                return MI_RESULT_OK;
            }
            else
            {
                /* need to remove it */
                for (; index+1 != tmpValue.uint32a.size; index++)
                {
                    tmpValue.uint32a.data[index] = tmpValue.uint32a.data[index+1];
                }
                tmpValue.uint32a.size --;

                return _AddOrSetGenericOption(options->genericOptions, optionName, &tmpValue, tmpType, MI_FLAG_BORROW);
            }
        }
    }
    /* Not there */
    if (flags == 1)
    {
        /* Great, it is not there and we are disabling it */
        return MI_RESULT_OK;
    }

    /* We need to add it. Make sure buffer is big enough */
    if ((tmpValue.uint32a.size % 10) == 0)
    {
        /* Need to grow it */
        void *tmpBuff = Batch_Get(options->genericOptions->batch, (tmpValue.uint32a.size+10)*sizeof(MI_Uint32));
        if (tmpBuff == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        if (tmpValue.uint32a.data)
        {
            memcpy(tmpBuff, tmpValue.uint32a.data, tmpValue.uint32a.size*sizeof(MI_Uint32));
            Batch_Put(options->genericOptions->batch, tmpValue.uint32a.data);
        }
        tmpValue.uint32a.data = tmpBuff;
    }

    tmpValue.uint32a.data[tmpValue.uint32a.size] = value;
    tmpValue.uint32a.size++;

    return _AddOrSetGenericOption(options->genericOptions, optionName, &tmpValue, tmpType, MI_FLAG_BORROW);
}

MI_Result MI_CALL GenericOptions_SetNumber(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   MI_Uint32 value,
            MI_Uint32 flags)
{
    if ((options == NULL) || (optionName == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    if ((Tcscmp(optionName, MI_T("__MI_OPERATIONOPTIONS_CHANNEL")) == 0) && (options->ft == &g_operationOptionsFT))
    {
        return GenericOptions_EnableDisableChannel(options, optionName, value, flags);
    }
    else
    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        MI_Value _value;

        if (flags != 0)
            return MI_RESULT_INVALID_PARAMETER;

        _value.uint32 = value;

        return _AddOrSetGenericOption(genericOptions, optionName, &_value, MI_UINT32, 0);
    }
}

MI_Result MI_CALL GenericOptions_SetInterval(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_Interval *value,
            MI_Uint32 flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || flags)
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        MI_Value _value;

        _value.datetime.isTimestamp = MI_FALSE;
        _value.datetime.u.interval = *value;

        return _AddOrSetGenericOption(genericOptions, optionName, &_value, MI_DATETIME, 0);
    }
}
MI_Result MI_CALL GenericOptions_SetDateTime(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_Datetime *value,
            MI_Uint32 flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || flags)
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        MI_Value _value;

        _value.datetime = *value;

        return _AddOrSetGenericOption(genericOptions, optionName, &_value, MI_DATETIME, 0);
    }
}

MI_Result MI_CALL GenericOptions_SetCustomOption(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   MI_Type valueType,
    _In_   const MI_Value *value,
            MI_Boolean mustComply,
            MI_Uint32 flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || flags)
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;

        /* TODO! What about mustComply */
        return _AddOrSetGenericCustomOption(genericOptions, optionName, value, valueType, mustComply, 0);
    }
}


MI_Result MI_CALL GenericOptions_GetString(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Outptr_result_z_ const MI_Char **value,
    _Out_opt_ MI_Uint32 *index,
    _Out_opt_ MI_Uint32 *flags)
{
    MI_Result miResult;
    MI_Value tmpValue;
    MI_Type type;
    
    if ((options == NULL) || (optionName == NULL) || (value == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = _GetGenericOptionsValue(options, optionName, &type, &tmpValue, index);
    if (miResult == MI_RESULT_OK)
    {
        if (type != MI_STRING)
            return MI_RESULT_TYPE_MISMATCH;
        
        if (value)
            *value = tmpValue.string;
        if (flags)
            *flags = 0;
    }
    return miResult;
}

MI_Result MI_CALL GenericOptions_GetNumber(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Out_ MI_Uint32 *value,
    _Out_opt_ MI_Uint32 *index,
    _Out_opt_ MI_Uint32 *flags)
{
    MI_Result miResult;
    MI_Value tmpValue;
    MI_Type type;

    if ((options == NULL) || (optionName == NULL) || (value == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = _GetGenericOptionsValue(options, optionName, &type, &tmpValue, index);
    if (miResult == MI_RESULT_OK)
    {
        if (type != MI_UINT32)
            return MI_RESULT_TYPE_MISMATCH;
        
        if (value)
            *value = tmpValue.uint32;
        if (flags)
            *flags = 0;
    }

    return miResult;
}


MI_Result MI_CALL GenericOptions_GetInterval(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Out_ MI_Interval *value,
    _Out_opt_ MI_Uint32 *index,
    _Out_opt_ MI_Uint32 *flags)
{
    MI_Result miResult;
    MI_Value tmpValue;
    MI_Type type;

    if ((options == NULL) || (optionName == NULL) || (value == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = _GetGenericOptionsValue(options, optionName, &type, &tmpValue, index);
    if (miResult == MI_RESULT_OK)
    {
        if (type != MI_DATETIME)
            return MI_RESULT_TYPE_MISMATCH;
        
        if (value)
        {
            if (tmpValue.datetime.isTimestamp == MI_TRUE)
                miResult = MI_RESULT_TYPE_MISMATCH;
            else
                *value = tmpValue.datetime.u.interval;
        }
        if (flags)
            *flags = 0;
    }
    return miResult;
}

MI_Result MI_CALL GenericOptions_GetDateTime(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Out_ MI_Datetime *value,
    _Out_opt_ MI_Uint32 *index,
    _Out_opt_ MI_Uint32 *flags)
{
    MI_Result miResult;
    MI_Value tmpValue;
    MI_Type type;

    if ((options == NULL) || (optionName == NULL) || (value == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = _GetGenericOptionsValue(options, optionName, &type, &tmpValue, index);
    if (miResult == MI_RESULT_OK)
    {
        if (type != MI_DATETIME)
            return MI_RESULT_TYPE_MISMATCH;
        
        if (value)
        {
            *value = tmpValue.datetime;
        }
        if (flags)
            *flags = 0;
    }
    return miResult;
}

MI_Result MI_CALL GenericOptions_GetOption(
    _In_   const struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _Out_ MI_Value *value,
    _Out_ MI_Type *type,
    _Out_opt_ MI_Uint32 *index,
    _Out_opt_ MI_Uint32 *flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || (type == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    if (flags)
        *flags = 0;
    return _GetGenericOptionsValue(options, optionName, type, value, index);
}

MI_Result MI_CALL GenericOptions_GetOptionCount(
    _In_   const struct _GenericOptions_Handle *options,
    _Out_ MI_Uint32 *count)
{
    if ((options == NULL) || (count == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        if (genericOptions->optionsInstance)
        {
            return MI_Instance_GetElementCount(genericOptions->optionsInstance, count);
        }
        *count = 0;
        return MI_RESULT_OK;
    }
}

#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:28196) 
#endif
MI_Result MI_CALL GenericOptions_GetOptionAt(
    _In_   const struct _GenericOptions_Handle *options,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **optionName,
    _Out_ MI_Value *value,
    _Out_ MI_Type *type,
    _Out_opt_ MI_Uint32 *flags)
{
    if ((options == NULL) || (optionName == NULL) || (value == NULL) || (type == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    {
        struct _GenericOptions *genericOptions = options->genericOptions;
        if (genericOptions->optionsInstance)
        {
            if (flags)
                *flags = 0;

            return  MI_Instance_GetElementAt(genericOptions->optionsInstance, index, optionName, value, type, 0);
        }
    }
    return MI_RESULT_NO_SUCH_PROPERTY;
}
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif

MI_Result MI_CALL GenericOptions_AddCredentials(
    _Inout_   struct _GenericOptions_Handle *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_UserCredentials *credentials,
            MI_Uint32 flags)
{
    struct _GenericOptions *genericOptions;
    MI_Result miResult;
    MI_Value credValue;
    MI_Type credType;
    MI_Uint32 credFlags;
    MI_Instance *namedCredSetInstance;
    MI_Instance *credValueInstance;
    MI_Boolean needToAddCredInstance = MI_FALSE;

    if ((options == NULL) || (options->genericOptions == NULL) || (options->genericOptions->batch == NULL) || (credentials == NULL) || (flags != 0))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    genericOptions = options->genericOptions;

    /* ensure we have the credential set instance */
    if (genericOptions->credentialInstance == NULL)
    {
        miResult = Instance_NewDynamic(&genericOptions->credentialInstance, MI_T("_MI_CredentialSet"), MI_FLAG_CLASS, genericOptions->batch);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
    }

    /* ensure we have a named credential set for this credential  */
    miResult = MI_Instance_GetElement(genericOptions->credentialInstance, optionName, &credValue, &credType, &credFlags, NULL);
    if (miResult == MI_RESULT_NO_SUCH_PROPERTY)
    {
        miResult = Instance_NewDynamic(&credValue.instance, MI_T("_MI_NamedCredentialSet"), MI_FLAG_CLASS, genericOptions->batch);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        miResult = MI_Instance_AddElement(genericOptions->credentialInstance, optionName, &credValue, MI_INSTANCE, MI_FLAG_BORROW);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
    }
    else if (miResult != MI_RESULT_OK)
        return miResult;

    namedCredSetInstance = credValue.instance;

    /* Ensure we have a credential option for this credential type */
    miResult = MI_Instance_GetElement(namedCredSetInstance, credentials->authenticationType, &credValue, &credType, &credFlags, NULL);
    if (miResult == MI_RESULT_NO_SUCH_PROPERTY)
    {
        miResult = Instance_NewDynamic(&credValueInstance, MI_T("_MI_CredentialValue"), MI_FLAG_CLASS, genericOptions->batch);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        needToAddCredInstance = MI_TRUE;
    }
    else if (miResult != MI_RESULT_OK)
        return miResult;
    else
    {
        /* Cannot add the same element more than once, so fail */
        return MI_RESULT_FAILED;
    }

    /* Now we can add the credentials to this credential value */
    if ((Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_NONE) == 0) ||
        (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_NEGO_NO_CREDS) == 0) ||
        (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_DEFAULT) == 0))
    {
        /* We are done as there are no more items to store */
    }
    else if ((Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_DIGEST) == 0) ||
             (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_NEGO_WITH_CREDS) == 0) ||
             (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_BASIC) == 0) ||
             (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_KERBEROS) == 0) ||
             (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_NTLM) == 0)
#if (WINVER >= 0x600)
             || (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_CREDSSP) == 0)
#endif
             )
    {
        /* domain/username/password */
        if (credentials->credentials.usernamePassword.domain == NULL)
        {
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Domain"), NULL, MI_STRING, MI_FLAG_NULL);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Domain"), NULL, MI_STRING, MI_FLAG_NULL);
        }
        else
        {
            credValue.string = (MI_String) credentials->credentials.usernamePassword.domain;
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Domain"), &credValue, MI_STRING, 0);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Domain"), &credValue, MI_STRING, 0);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;

        if (credentials->credentials.usernamePassword.username == NULL)
        {
            /* Illegal to not have a username */
            miResult = MI_RESULT_INVALID_PARAMETER;
        }
        else
        {
            credValue.string = (MI_String) credentials->credentials.usernamePassword.username;
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Username"), &credValue, MI_STRING, 0);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Username"), &credValue, MI_STRING, 0);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;


        if (credentials->credentials.usernamePassword.password == NULL)
        {
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Password"), NULL, MI_UINT8A, MI_FLAG_NULL);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Password"), NULL, MI_UINT8A, MI_FLAG_NULL);
        }
        else
        {
            MI_Uint32 bufferNeeded;
            MI_Uint32 sourceBufferLength = (Tcslen(credentials->credentials.usernamePassword.password)+1)*sizeof(MI_Char);
            int encryptRet;

            encryptRet = EncryptData(credentials->credentials.usernamePassword.password, sourceBufferLength, NULL, 0, &bufferNeeded);
            if (encryptRet != -2)
                return MI_RESULT_FAILED;

            credValue.uint8a.size = bufferNeeded;
            credValue.uint8a.data = Batch_Get(options->genericOptions->batch, bufferNeeded);
            if (credValue.uint8a.data == NULL)
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;

            encryptRet = EncryptData(credentials->credentials.usernamePassword.password, sourceBufferLength, credValue.uint8a.data, bufferNeeded, &bufferNeeded);
            if (encryptRet != 0)
                return MI_RESULT_FAILED;

            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Password"), &credValue, MI_UINT8A, 0);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Password"), &credValue, MI_UINT8A, 0);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;
    }
    else if ((Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_CLIENT_CERTS) == 0) ||
             (Tcscasecmp(credentials->authenticationType, MI_AUTH_TYPE_ISSUER_CERT) == 0))
    {
        /* Certificate thumbprint */
        if (credentials->credentials.certificateThumbprint == NULL)
        {
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Thumbprint"), NULL, MI_STRING, MI_FLAG_NULL);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Thumbprint"), NULL, MI_STRING, MI_FLAG_NULL);
        }
        else
        {
            credValue.string = (MI_String) credentials->credentials.certificateThumbprint;
            if (needToAddCredInstance)
                miResult = MI_Instance_AddElement(credValueInstance, MI_T("Thumbprint"), &credValue, MI_STRING, 0);
            else
                miResult = MI_Instance_SetElement(credValueInstance, MI_T("Thumbprint"), &credValue, MI_STRING, 0);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if ((miResult == MI_RESULT_OK) && needToAddCredInstance)
    {
        credValue.instance = credValueInstance;
        miResult = MI_Instance_AddElement(namedCredSetInstance, credentials->authenticationType, &credValue, MI_INSTANCE, MI_FLAG_BORROW);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
    }
    return miResult;
}

MI_Result MI_CALL GenericOptions_GetCredentialsCount(
    _In_   const struct _GenericOptions_Handle *options,
    _Out_ MI_Uint32 *count)
{
    struct _GenericOptions *genericOptions;
    MI_Result miResult;
    MI_Value credValue;
    MI_Type credType;
    MI_Instance *namedCredSetInstance;
    MI_Uint32 credInstElemCount = 0;
    MI_Uint32 credInstElemIndex = 0;
    MI_Uint32 namedCredValueCount = 0;

    if ((options == NULL) || (options->genericOptions == NULL) || (options->genericOptions->batch == NULL) || (count == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    genericOptions = options->genericOptions;

    *count = 0;

    /* Do we have any creds at all? */
    if (genericOptions->credentialInstance == NULL)
    {
        return MI_RESULT_OK;
    }

    miResult = MI_Instance_GetElementCount(genericOptions->credentialInstance, &credInstElemCount);
    if (miResult != MI_RESULT_OK)
    {
        *count = 0;
        return miResult;
    }

    for (credInstElemIndex = 0; credInstElemIndex != credInstElemCount; credInstElemIndex++)
    {
        /* Count the named credential list  */
        miResult = MI_Instance_GetElementAt(genericOptions->credentialInstance, credInstElemIndex, NULL, &credValue, &credType, NULL);
        if (miResult != MI_RESULT_OK)
        {
            *count = 0;
            return miResult;
        }

        namedCredSetInstance = credValue.instance;

        /* Count the creds inside the named credential list */
        miResult = MI_Instance_GetElementCount(namedCredSetInstance, &namedCredValueCount);
        if (miResult != MI_RESULT_OK)
        {
            *count = 0;
            return miResult;
        }

        *count += namedCredValueCount;
    }
    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result _GetCredentialInstanceAt(_In_   struct _GenericOptions *genericOptions,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **optionName,
    _Outptr_result_z_ const MI_Char **authenticationType,
    _Outptr_ MI_Instance **credsInstance)
{
    MI_Result miResult;
    MI_Value credValue;
    MI_Type credType;
    MI_Instance *namedCredSetInstance;
    MI_Uint32 credInstElemCount = 0;
    MI_Uint32 credInstElemIndex = 0;
    MI_Uint32 namedCredValueCount = 0;
    MI_Uint32 currentCount = 0;

    miResult = MI_Instance_GetElementCount(genericOptions->credentialInstance, &credInstElemCount);
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }

    for (credInstElemIndex = 0; credInstElemIndex != credInstElemCount; credInstElemIndex++)
    {
        const MI_Char *tempCredName;
        /* Count the named credential list  */
        miResult = MI_Instance_GetElementAt(genericOptions->credentialInstance, credInstElemIndex, &tempCredName, &credValue, &credType, NULL);

        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        if (credType != MI_INSTANCE)
            return MI_RESULT_INVALID_PARAMETER;

#ifdef _PREFAST_
        _Analysis_assume_(tempCredName != NULL);
#endif

        namedCredSetInstance = credValue.instance;

        /* Count the creds inside the named credential list */
        miResult = MI_Instance_GetElementCount(namedCredSetInstance, &namedCredValueCount);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }

        if ((currentCount + namedCredValueCount) > index)
        {
            MI_Value credDetailsValue;
            MI_Type credDetailsValueType;
            const MI_Char *credDetailAuthName;
            /* The value is in this batch of items */
            miResult = MI_Instance_GetElementAt(namedCredSetInstance, index - currentCount, &credDetailAuthName, &credDetailsValue, &credDetailsValueType, NULL);

            if (miResult != MI_RESULT_OK)
                return miResult;
            if (credDetailsValueType != MI_INSTANCE)
                return MI_RESULT_INVALID_PARAMETER;

#ifdef _PREFAST_
            _Analysis_assume_(credDetailAuthName != NULL);
#endif

            /* Got the item we need, now set up out parameters */
            *authenticationType = credDetailAuthName;
            *optionName = tempCredName;
            *credsInstance = credDetailsValue.instance;
            return MI_RESULT_OK;
        }
        else
        {
            /* Not in this batch so continue on, counting how many we found this time around */
            currentCount += namedCredValueCount;
        }
    }
    return MI_RESULT_NO_SUCH_PROPERTY;
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL GenericOptions_GetCredentialsAt(
    _In_   const struct _GenericOptions_Handle *options,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **optionName,
    _Out_ MI_UserCredentials *credentials, // output credentials always has password set to '******'
    _Out_opt_ MI_Uint32 *flags)
{
    struct _GenericOptions *genericOptions;
    MI_Instance *credInstance;
    MI_Result miResult;
    const MI_Char *authenticationType;

    if ((options == NULL) || (options->genericOptions == NULL) || (options->genericOptions->batch == NULL) || (options->genericOptions->credentialInstance == NULL) || (credentials == NULL) || (optionName == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    genericOptions = options->genericOptions;

    if (flags)
        *flags = 0;

    miResult = _GetCredentialInstanceAt(genericOptions, index, optionName, &authenticationType, &credInstance);
    if (miResult != MI_RESULT_OK)
        return miResult;

    memset(credentials, 0,  sizeof(*credentials));

    /* Decode instance for cred structure */
    /* Now we can add the credentials to this credential value */
    if ((Tcscasecmp(authenticationType, MI_AUTH_TYPE_NONE) == 0) ||
        (Tcscasecmp(authenticationType, MI_AUTH_TYPE_NEGO_NO_CREDS) == 0) ||
        (Tcscasecmp(authenticationType, MI_AUTH_TYPE_DEFAULT) == 0))
    {
        /* We are done as there are no more items to store */
    }
    else if ((Tcscasecmp(authenticationType, MI_AUTH_TYPE_DIGEST) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_NEGO_WITH_CREDS) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_BASIC) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_KERBEROS) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_NTLM) == 0)
#if (WINVER >= 0x600)
             || (Tcscasecmp(authenticationType, MI_AUTH_TYPE_CREDSSP) == 0)
#endif
             )
    {
        /* domain/username/password */
        MI_Value tmpValue;
        MI_Type tmpType;
        MI_Uint32 tmpFlags;

        miResult = MI_Instance_GetElement(credInstance, MI_T("Domain"), &tmpValue, &tmpType, &tmpFlags, NULL);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        else if (tmpType != MI_STRING)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        if (tmpFlags & MI_FLAG_NULL)
        {
            credentials->credentials.usernamePassword.domain = NULL;
        }
        else
        {
            credentials->credentials.usernamePassword.domain = tmpValue.string;
        }

        miResult = MI_Instance_GetElement(credInstance, MI_T("Username"), &tmpValue, &tmpType, &tmpFlags, NULL);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        else if (tmpType != MI_STRING)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        if (tmpFlags & MI_FLAG_NULL)
        {
            credentials->credentials.usernamePassword.username = NULL;
        }
        else
        {
            credentials->credentials.usernamePassword.username = tmpValue.string;
        }

        credentials->credentials.usernamePassword.password = MI_T("******");
    }
    else if ((Tcscasecmp(authenticationType, MI_AUTH_TYPE_CLIENT_CERTS) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_ISSUER_CERT) == 0))
    {
        /* Certificate thumbprint */
        MI_Value tmpValue;
        MI_Type tmpType;
        MI_Uint32 tmpFlags;
        miResult = MI_Instance_GetElement(credInstance, MI_T("Thumbprint"), &tmpValue, &tmpType, &tmpFlags, NULL);
        if ((miResult != MI_RESULT_OK) || (tmpType != MI_STRING))
        {
            return miResult;
        }
        if (tmpFlags & MI_FLAG_NULL)
        {
            credentials->credentials.certificateThumbprint = NULL;
        }
        else
        {
            credentials->credentials.certificateThumbprint = tmpValue.string;
        }
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    credentials->authenticationType = authenticationType;

    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL GenericOptions_GetCredentialsPasswordAt (
    _In_   const struct _GenericOptions_Handle *options,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **optionName,
    _Out_writes_to_opt_(bufferLength, *passwordLength) MI_Char *password,
    _In_ MI_Uint32 bufferLength,
    _When_(bufferLength == 0, _Out_) MI_Uint32 *passwordLength,
    _Out_opt_ MI_Uint32 *flags)
{
    struct _GenericOptions *genericOptions;
    MI_Instance *credInstance;
    MI_Result miResult;
    const MI_Char *authenticationType;

    if ((options == NULL) || (options->genericOptions == NULL) || (options->genericOptions->batch == NULL) || (options->genericOptions->credentialInstance == NULL) || (optionName == NULL) || (passwordLength == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    genericOptions = options->genericOptions;

    if (flags)
        *flags = 0;

    miResult = _GetCredentialInstanceAt(genericOptions, index, optionName, &authenticationType, &credInstance);
    if (miResult != MI_RESULT_OK)
        return miResult;

    /* Decode instance for password */
    if ((Tcscasecmp(authenticationType, MI_AUTH_TYPE_DIGEST) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_NEGO_WITH_CREDS) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_BASIC) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_KERBEROS) == 0) ||
             (Tcscasecmp(authenticationType, MI_AUTH_TYPE_NTLM) == 0)
#if (WINVER >= 0x600)
             || (Tcscasecmp(authenticationType, MI_AUTH_TYPE_CREDSSP) == 0)
#endif
             )
    {
        /* domain/username/password */
        MI_Value tmpValue;
        MI_Type tmpType;
        MI_Uint32 tmpFlags;

        miResult = MI_Instance_GetElement(credInstance, MI_T("Password"), &tmpValue, &tmpType, &tmpFlags, NULL);
        if (miResult != MI_RESULT_OK)
        {
            return miResult;
        }
        else if (tmpType != MI_UINT8A)
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        if (tmpFlags & MI_FLAG_NULL)
        {
            *passwordLength = 0;
            return MI_RESULT_OK;
        }
        else
        {
            MI_Uint32 neededLength;
            MI_Uint32 allocatedLength;
            MI_Char *tmpPassword = NULL;
            int decryptRet = DecryptData(tmpValue.array.data, tmpValue.array.size, NULL, 0, &neededLength);
            if (decryptRet != -2)
                return MI_RESULT_FAILED;
            allocatedLength = neededLength;
            tmpPassword = PAL_Malloc(allocatedLength);
            if (tmpPassword == NULL)
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;

            decryptRet = DecryptData(tmpValue.array.data, tmpValue.array.size, tmpPassword, neededLength, &neededLength);
            if (decryptRet != 0)
            {
                PAL_Free(tmpPassword);
                return MI_RESULT_FAILED;
            }
            _Analysis_assume_nullterminated_(tmpPassword);
            *passwordLength = Tcslen(tmpPassword)+1;
            if (bufferLength < *passwordLength)
            {
                PAL_Free(tmpPassword);
                if (bufferLength == 0)
                    return MI_RESULT_OK;
                else
                    return MI_RESULT_FAILED;
            }
            Tcslcpy(password, tmpPassword, bufferLength);
            PAL_Free(tmpPassword);
            return MI_RESULT_OK;
        }
    }
    else
        return MI_RESULT_INVALID_PARAMETER;
}


MI_Result MI_CALL GenericOptions_GetEnabledChannels(
        _In_   const MI_OperationOptions *options_,
        _In_z_ const MI_Char *optionName,
        _Out_writes_to_opt_(bufferLength, *channelCount) MI_Uint32 *channels,
        _In_ MI_Uint32 bufferLength,
        _Out_ MI_Uint32 *channelCount,
        _Out_opt_ MI_Uint32 *flags)
{
    struct _GenericOptions_Handle * options = (struct _GenericOptions_Handle *) options_;
    MI_Result miResult;
    MI_Type tmpType;
    MI_Value tmpValue;
    
    if ((options == NULL) || (options->genericOptions == NULL) || (optionName == NULL) || (channelCount == NULL))
        return MI_RESULT_INVALID_PARAMETER;
    
    if (flags)
        *flags = 0;
        
    if (options->genericOptions->optionsInstance == NULL)
    {
        *channelCount = 0;
        return MI_RESULT_OK;
    }
    miResult = _GetGenericOptionsValue(options, optionName, &tmpType, &tmpValue, NULL);
    if (miResult == MI_RESULT_NO_SUCH_PROPERTY)
    {
        *channelCount = 0;
        return MI_RESULT_OK;
    }

    if ((Tcscmp(optionName, MI_T("__MI_OPERATIONOPTIONS_CHANNEL")) != 0) || 
        (tmpType != MI_UINT32A))
    {
        return MI_RESULT_TYPE_MISMATCH;
    }

    *channelCount = tmpValue.uint32a.size;

    if (bufferLength >= tmpValue.uint32a.size)
    {
        if (channels == NULL)
            return MI_RESULT_INVALID_PARAMETER;

        memcpy(channels, tmpValue.uint32a.data, sizeof(MI_Uint32)*tmpValue.uint32a.size);
        return MI_RESULT_OK;
    }
    return MI_RESULT_FAILED;;
}

static MI_Result _GetDefaultOptionsFromConfigFile(MI_DestinationOptions *options)
{
    char path[PAL_MAX_PATH_SIZE];
    SSL_Options sslOptions = 0;
    Conf* conf;

    /* Form the configuration file path */
    Strlcpy(path, OMI_GetPath(ID_CLIENTCONFIGFILE), sizeof(path));

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        trace_MIFailedToOpenConfigFile(scs(path));
        return MI_RESULT_FAILED;
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            trace_MIFailedToReadConfigValue(path, scs(Conf_Error(conf)));
            goto error;
        }

        if (r == 1)
            break;

        if (strcmp(key, "NoSSLv2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_SSL_V2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_SSL_V2;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "NoSSLv3") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_SSL_V3;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_SSL_V3;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "NoTLSv1_0") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_TLS_V1_0;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_TLS_V1_0;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "NoTLSv1_1") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_TLS_V1_1;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_TLS_V1_1;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "NoTLSv1_2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_TLS_V1_2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_TLS_V1_2;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
        else if (strcmp(key, "NoSSLCompression") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                sslOptions |= DISABLE_SSL_COMPRESSION;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                sslOptions &= ~DISABLE_SSL_COMPRESSION;
            }
            else
            {
                trace_MIConfig_InvalidValue(scs(path), Conf_Line(conf), scs(key), scs(value));
                goto error;
            }
        }
    }

    if (sslOptions)
    {
        MI_Result miResult;

        miResult = MI_DestinationOptions_SetSslOptions(options, sslOptions);
        if (miResult != MI_RESULT_OK)
        {
            goto error;
        }
    }

    /* Close configuration file */
    Conf_Close(conf);

    return MI_RESULT_OK;

error:
    Conf_Close(conf);
    return MI_RESULT_INVALID_PARAMETER;
}

MI_Result MI_CALL  DestinationOptions_Create(
    _In_  MI_Application *application,
    _Out_ MI_DestinationOptions *options)
{
    MI_Result miResult;
    
    if ((application == NULL) || (options == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = GenericOptions_Create((struct _GenericOptions_Handle *) options, &g_destinationOptionsFT);
    if (miResult != MI_RESULT_OK)
        return miResult;

    miResult = _GetDefaultOptionsFromConfigFile(options);
    if (miResult != MI_RESULT_OK)
    {
        NitsIgnoringError();
    }

    return MI_RESULT_OK;
}
MI_Result MI_CALL DestinationOptions_MigrateOptions(
    _In_ const MI_DestinationOptions *source, 
    _Inout_ MI_DestinationOptions *destination,
    _In_opt_z_ const MI_Char *protocol,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError)
{
    struct _GenericOptions_Handle *options_Handle = (struct _GenericOptions_Handle *)source;
    MI_Uint32 optionCount, optionIndex;
    MI_Result miResult;

    if ((source == NULL) || (source->ft == NULL))
        return MI_RESULT_OK;

    if (extendedError != NULL)
        *extendedError = NULL;

    miResult = GenericOptions_GetOptionCount(options_Handle, &optionCount);
    if (miResult != MI_RESULT_OK)
        return miResult;

    for (optionIndex = 0; optionIndex != optionCount; optionIndex++)
    {
        MI_Type optionType;
        const MI_Char *optionName;
        MI_Value optionValue;

        miResult = MI_Instance_GetElementAt(options_Handle->genericOptions->optionsInstance, optionIndex, &optionName, &optionValue, &optionType, NULL);
        if (miResult != MI_RESULT_OK)
            return miResult;

        switch(optionType)
        {
        case MI_UINT32:
        {
            miResult = destination->ft->SetNumber(destination, optionName, optionValue.uint32, 0);
            break;
        }
        case MI_STRING:
        {
            miResult = destination->ft->SetString(destination, optionName, optionValue.string, 0);
            break;
        }
        case MI_DATETIME:
        {
            miResult = destination->ft->SetInterval(destination, optionName, &optionValue.datetime.u.interval, 0);
            break;
        }
        default:
            return MI_RESULT_INVALID_PARAMETER;
        }

        if (miResult != MI_RESULT_OK)
            return miResult;
    }

    /* Migrate credentials */
    miResult = GenericOptions_GetCredentialsCount(options_Handle, &optionCount);
    if (miResult != MI_RESULT_OK)
        return miResult;

    for (optionIndex = 0; optionIndex != optionCount; optionIndex++)
    {
        const MI_Char *optionName;
        MI_Instance *credInstance;
        MI_UserCredentials credentials;
        MI_Uint32 passwordBufferSize = 0;
        MI_Char *password = NULL;

        memset(&credentials, 0, sizeof(credentials));

        miResult = _GetCredentialInstanceAt(options_Handle->genericOptions, optionIndex, &optionName, &credentials.authenticationType, &credInstance);
        if (miResult != MI_RESULT_OK)
            return miResult;

        if ((Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_DIGEST) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_NEGO_WITH_CREDS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_BASIC) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_KERBEROS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_NTLM) == 0)
#if (WINVER >= 0x600)
                 || (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_CREDSSP) == 0)
#endif
                 )
        {
                /* domain/Username/password */
            /* domain/username/password */
            MI_Value tmpValue;
            MI_Type tmpType;
            MI_Uint32 tmpFlags;

            miResult = MI_Instance_GetElement(credInstance, MI_T("Domain"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_STRING)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.domain = NULL;
            }
            else
            {
                credentials.credentials.usernamePassword.domain = tmpValue.string;
            }

            miResult = MI_Instance_GetElement(credInstance, MI_T("Username"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_STRING)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.username = NULL;
            }
            else
            {
                credentials.credentials.usernamePassword.username = tmpValue.string;
            }

            miResult = MI_Instance_GetElement(credInstance, MI_T("Password"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_UINT8A)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.password = NULL;
            }
            else
            {
                MI_Uint32 bufferNeeded;

                int decryptRet = DecryptData(tmpValue.uint8a.data, tmpValue.uint8a.size, NULL, 0, &bufferNeeded);
                if (decryptRet != -2)
                    return MI_RESULT_FAILED;

                password = PAL_Malloc(bufferNeeded);
                if (password == NULL)
                    return MI_RESULT_SERVER_LIMITS_EXCEEDED;

                passwordBufferSize = bufferNeeded;

                decryptRet = DecryptData(tmpValue.uint8a.data, tmpValue.uint8a.size, password, passwordBufferSize, &bufferNeeded);
                if (decryptRet != 0)
                    return MI_RESULT_FAILED;

                credentials.credentials.usernamePassword.password = password;
            }
            
        }
        else if ((Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_CLIENT_CERTS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_ISSUER_CERT) == 0))
        {
            /* Thumbprint */
            MI_Value tmpValue;
            MI_Type tmpType;
            MI_Uint32 tmpFlags;
            miResult = MI_Instance_GetElement(credInstance, MI_T("Thumbprint"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
                return miResult;
            if (tmpType != MI_STRING)
                return MI_RESULT_INVALID_PARAMETER;
            credentials.credentials.certificateThumbprint = tmpValue.string;
        }

        miResult = destination->ft->AddCredentials(destination, optionName, &credentials, 0);
        if (password != NULL)
        {
            PAL_Free(password);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;

    }
    return MI_RESULT_OK;
}

void DestinationOptions_Duplicate(
    _Inout_ const MI_DestinationOptions *source, 
    _Out_ MI_DestinationOptions *destination)
{
    struct _GenericOptions_Handle *options = (struct _GenericOptions_Handle *)source;
    memcpy(destination, source, sizeof(MI_DestinationOptions)) ;
    if (options && options->genericOptions)
    {
        Atomic_Inc(&options->genericOptions->referenceCount);
    }
}

MI_Result MI_CALL OperationOptions_Create(
    _In_  MI_Application *application,
    MI_Boolean customOptionsMustUnderstand,
    _Out_ MI_OperationOptions *options_)
{
    MI_Result miResult;
    struct _GenericOptions_Handle * options = (struct _GenericOptions_Handle *)options_;
    
    if ((application == NULL) || (options == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    miResult = GenericOptions_Create(options, &g_operationOptionsFT);

    if (miResult == MI_RESULT_OK)
    {
        /* Create the default channel configuration */
        if (((miResult = GenericOptions_SetNumber(options, MI_T("__MI_OPERATIONOPTIONS_CHANNEL"), MI_WRITEMESSAGE_CHANNEL_WARNING, 0)) == MI_RESULT_OK) &&
            ((miResult = GenericOptions_SetNumber(options, MI_T("__MI_OPERATIONOPTIONS_CHANNEL"), MI_WRITEMESSAGE_CHANNEL_VERBOSE, 0)) == MI_RESULT_OK) &&
            ((miResult = GenericOptions_SetNumber(options, MI_T("__MI_OPERATIONOPTIONS_CHANNEL"), MI_WRITEMESSAGE_CHANNEL_DEBUG, 0)) == MI_RESULT_OK))
        {
        }
    }

    return miResult;
}

MI_Result MI_CALL OperationOptions_MigrateOptions(
    _In_opt_ const MI_OperationOptions *source, 
    _Inout_ MI_OperationOptions *destination)
{
    struct _GenericOptions_Handle *options_Handle = (struct _GenericOptions_Handle *)source;
    MI_Uint32 optionCount, optionIndex;
    MI_Result miResult;

    if ((source == NULL) || (source->ft == NULL))
        return MI_RESULT_OK;

    miResult = GenericOptions_GetOptionCount(options_Handle, &optionCount);
    if (miResult != MI_RESULT_OK)
        return miResult;

    for (optionIndex = 0; optionIndex != optionCount; optionIndex++)
    {
        MI_Type optionType;
        const MI_Char *optionName;
        MI_Value optionValue;

        miResult = MI_Instance_GetElementAt(options_Handle->genericOptions->optionsInstance, optionIndex, &optionName, &optionValue, &optionType, NULL);
        if (miResult != MI_RESULT_OK)
            return miResult;
        switch(optionType)
        {
        case MI_UINT32:
        {
            miResult = destination->ft->SetNumber(destination, optionName, optionValue.uint32, 0);
            break;
        }
        case MI_STRING:
        {
            miResult = destination->ft->SetString(destination, optionName, optionValue.string, 0);
            break;
        }
        case MI_DATETIME:
        {
            if (optionValue.datetime.isTimestamp == MI_TRUE)
                return MI_RESULT_INVALID_PARAMETER;

            miResult = destination->ft->SetInterval(destination, optionName, &optionValue.datetime.u.interval, 0);
            break;
        }
        case MI_UINT32A:
        {
            /* This is potentially the channel settings */
            if (Tcscmp(optionName, MI_T("__MI_OPERATIONOPTIONS_CHANNEL")) == 0)
            {
                MI_Uint32 index;
                for (index = 0; index != optionValue.uint32a.size; index++)
                {
                    miResult = destination->ft->SetNumber(destination, optionName, optionValue.uint32a.data[index], 0);
                    if (miResult != MI_RESULT_OK)
                        return miResult;
                }
            }
            else
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            break;
        }
        case MI_INSTANCE:
        {
            if (Tcscmp(optionValue.instance->classDecl->name, MI_T("_OMI_CustomOptionValue")) == 0)
            {
                MI_Type mustUnderstandType;
                MI_Value mustUnderstandValue;
                MI_Type customOptionType;
                MI_Value customOptionValue;

                miResult = MI_Instance_GetElement(optionValue.instance, MI_T("value"), &customOptionValue, &customOptionType, NULL, NULL);
                if (miResult != MI_RESULT_OK)
                    return miResult;
                
                miResult = MI_Instance_GetElement(optionValue.instance, MI_T("mustUnderstand"), &mustUnderstandValue, &mustUnderstandType, NULL, NULL);
                if (miResult != MI_RESULT_OK)
                    return miResult;
                if (mustUnderstandType != MI_BOOLEAN)
                    return MI_RESULT_INVALID_PARAMETER;

                miResult = destination->ft->SetCustomOption(destination, optionName, customOptionType, &customOptionValue, mustUnderstandValue.boolean, 0);

            }
            else
                return MI_RESULT_INVALID_PARAMETER;
            break;
        }
        default:
            return MI_RESULT_INVALID_PARAMETER;
        }

        if (miResult != MI_RESULT_OK)
            return miResult;
    }

    return MI_RESULT_OK;
}

MI_Result MI_CALL  SubscriptionDeliveryOptions_Create(
    _In_  MI_Application *application,
    _In_  MI_SubscriptionDeliveryType deliveryType,
    _Out_ MI_SubscriptionDeliveryOptions *options)
{
    if ((application == NULL) || (options == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    return GenericOptions_Create((struct _GenericOptions_Handle *) options, &g_subscriptionDeliveryOptionsFT);
}

MI_Result MI_CALL SubscriptionDeliveryOptions_MigrateOptions(
    _In_ const MI_SubscriptionDeliveryOptions *source, 
    _Inout_ MI_SubscriptionDeliveryOptions *destination)
{
     struct _GenericOptions_Handle *options_Handle = (struct _GenericOptions_Handle *)source;
    MI_Uint32 optionCount, optionIndex;
    MI_Result miResult;

    if ((source == NULL) || (source->ft == NULL))
        return MI_RESULT_OK;

    miResult = GenericOptions_GetOptionCount(options_Handle, &optionCount);
    if (miResult != MI_RESULT_OK)
        return miResult;

    for (optionIndex = 0; optionIndex != optionCount; optionIndex++)
    {
        MI_Type optionType;
        const MI_Char *optionName;
        MI_Value optionValue;

        miResult = MI_Instance_GetElementAt(options_Handle->genericOptions->optionsInstance, optionIndex, &optionName, &optionValue, &optionType, NULL);
        if (miResult != MI_RESULT_OK)
            return miResult;

        switch(optionType)
        {
        case MI_UINT32:
        {
            miResult = destination->ft->SetNumber(destination, optionName, optionValue.uint32, 0);
            break;
        }
        case MI_STRING:
        {
            miResult = destination->ft->SetString(destination, optionName, optionValue.string, 0);
            break;
        }
        case MI_DATETIME:
        {
            if (optionValue.datetime.isTimestamp == MI_TRUE)
                return MI_RESULT_INVALID_PARAMETER;

            miResult = destination->ft->SetInterval(destination, optionName, &optionValue.datetime.u.interval, 0);
            break;
        }
        default:
            return MI_RESULT_INVALID_PARAMETER;
        }
    }

    /* Migrate credentials */
    miResult = GenericOptions_GetCredentialsCount(options_Handle, &optionCount);
    if (miResult != MI_RESULT_OK)
        return miResult;

    for (optionIndex = 0; optionIndex != optionCount; optionIndex++)
    {
        const MI_Char *optionName;
        MI_Instance *credInstance;
        MI_UserCredentials credentials;
        MI_Uint32 passwordBufferSize = 0;
        MI_Char *password = NULL;

        memset(&credentials, 0, sizeof(credentials));

        miResult = _GetCredentialInstanceAt(options_Handle->genericOptions, optionIndex, &optionName, &credentials.authenticationType, &credInstance);
        if (miResult != MI_RESULT_OK)
            return miResult;

        if ((Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_DIGEST) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_NEGO_WITH_CREDS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_BASIC) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_KERBEROS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_NTLM) == 0)
#if (WINVER >= 0x600)
                 || (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_CREDSSP) == 0)
#endif
                 )
        {
            /* domain/username/password */
            MI_Value tmpValue;
            MI_Type tmpType;
            MI_Uint32 tmpFlags;

            miResult = MI_Instance_GetElement(credInstance, MI_T("Domain"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_STRING)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.domain = NULL;
            }
            else
            {
                credentials.credentials.usernamePassword.domain = tmpValue.string;
            }

            miResult = MI_Instance_GetElement(credInstance, MI_T("Username"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_STRING)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.username = NULL;
            }
            else
            {
                credentials.credentials.usernamePassword.username = tmpValue.string;
            }

            miResult = MI_Instance_GetElement(credInstance, MI_T("Password"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
            {
                return miResult;
            }
            else if (tmpType != MI_UINT8A)
            {
                return MI_RESULT_INVALID_PARAMETER;
            }
            if (tmpFlags & MI_FLAG_NULL)
            {
                credentials.credentials.usernamePassword.password = NULL;
            }
            else
            {
                MI_Uint32 bufferNeeded;

                int decryptRet = DecryptData(tmpValue.uint8a.data, tmpValue.uint8a.size, NULL, 0, &bufferNeeded);
                if (decryptRet != -2)
                    return MI_RESULT_FAILED;

                password = PAL_Malloc(bufferNeeded);
                if (password == NULL)
                    return MI_RESULT_SERVER_LIMITS_EXCEEDED;

                passwordBufferSize = bufferNeeded;

                decryptRet = DecryptData(tmpValue.uint8a.data, tmpValue.uint8a.size, password, passwordBufferSize, &bufferNeeded);
                if (decryptRet != 0)
                    return MI_RESULT_FAILED;

                credentials.credentials.usernamePassword.password = password;
            }
        }
        else if ((Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_CLIENT_CERTS) == 0) ||
                 (Tcscasecmp(credentials.authenticationType, MI_AUTH_TYPE_ISSUER_CERT) == 0))
        {
            /* Thumbprint */
            MI_Value tmpValue;
            MI_Type tmpType;
            MI_Uint32 tmpFlags;
            miResult = MI_Instance_GetElement(credInstance, MI_T("Thumbprint"), &tmpValue, &tmpType, &tmpFlags, NULL);
            if (miResult != MI_RESULT_OK)
                return miResult;
            if (tmpType != MI_STRING)
                return MI_RESULT_INVALID_PARAMETER;
            credentials.credentials.certificateThumbprint = tmpValue.string;
        }

        miResult = destination->ft->AddCredentials(destination, optionName, &credentials, 0);
        if (password != NULL)
        {
            PAL_Free(password);
        }
        if (miResult != MI_RESULT_OK)
            return miResult;

    }
    return MI_RESULT_OK;
}

MI_DestinationOptionsFT g_destinationOptionsFT = 
{
    (void      (MI_CALL *)(_Inout_   MI_DestinationOptions *options)) GenericOptions_Delete,
    (MI_Result (MI_CALL *)(_Inout_   MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_In_z_ const MI_Char *value,MI_Uint32 flags)) GenericOptions_SetString,
    (MI_Result (MI_CALL *)(_Inout_   MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_In_   MI_Uint32 value,MI_Uint32 flags)) GenericOptions_SetNumber,
    (MI_Result (MI_CALL *)(_Inout_   MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_UserCredentials *credentials,MI_Uint32 flags)) GenericOptions_AddCredentials,
    (MI_Result (MI_CALL *)(_In_      const MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_Outptr_result_z_ const MI_Char **value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetString,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Uint32 *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetNumber,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,_Out_ MI_Uint32 *count)) GenericOptions_GetOptionCount,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOptionAt,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOption,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,_Out_ MI_Uint32 *count)) GenericOptions_GetCredentialsCount,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_ MI_UserCredentials *credentials,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetCredentialsAt,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_writes_to_opt_(bufferLength, *passwordLength) MI_Char *password,_In_ MI_Uint32 bufferLength,_Out_ MI_Uint32 *passwordLength,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetCredentialsPasswordAt,
    (MI_Result (MI_CALL *)(_In_ const MI_DestinationOptions* self,_Out_ MI_DestinationOptions* newDestinationOptions)) GenericOptions_Clone,
    (MI_Result (MI_CALL *)(_Inout_   MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_Interval *value,MI_Uint32 flags)) GenericOptions_SetInterval,
    (MI_Result (MI_CALL *)(_In_   const MI_DestinationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Interval *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetInterval
};

MI_OperationOptionsFT g_operationOptionsFT =
{
    (void (MI_CALL *)(_Inout_ MI_OperationOptions *options)) GenericOptions_Delete,
    (MI_Result (MI_CALL *)(_Inout_   MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_In_z_ const MI_Char *value,MI_Uint32 flags)) GenericOptions_SetString,
    (MI_Result (MI_CALL *)(_Inout_   MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_In_   MI_Uint32 value,MI_Uint32 flags)) GenericOptions_SetNumber,
    (MI_Result (MI_CALL *)(_Inout_   MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_In_   MI_Type valueType,_In_   const MI_Value *value,MI_Boolean mustComply,MI_Uint32 flags)) GenericOptions_SetCustomOption,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_Outptr_result_z_ const MI_Char **value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetString,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Uint32 *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetNumber,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_Out_ MI_Uint32 *count)) GenericOptions_GetOptionCount,
    (MI_Result (MI_CALL *)(_In_  const  MI_OperationOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOptionAt,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOption,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_Out_writes_to_opt_(bufferLength, *channelCount) MI_Uint32 *channels,_In_ MI_Uint32 bufferLength,_Out_ MI_Uint32 *channelCount,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetEnabledChannels,
    (MI_Result (MI_CALL *)(_In_ const MI_OperationOptions* self,_Out_ MI_OperationOptions* newOperationOptions)) GenericOptions_Clone,
    (MI_Result (MI_CALL *)(_Inout_   MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_Interval *value,MI_Uint32 flags)) GenericOptions_SetInterval,
    (MI_Result (MI_CALL *)(_In_   const MI_OperationOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Interval *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetInterval
};

MI_SubscriptionDeliveryOptionsFT g_subscriptionDeliveryOptionsFT = 
{
    (MI_Result (MI_CALL *)(_Inout_   MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_In_z_ const MI_Char *value,MI_Uint32 flags)) GenericOptions_SetString,
    (MI_Result (MI_CALL *)(_Inout_   MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_In_   MI_Uint32 value,MI_Uint32 flags)) GenericOptions_SetNumber,
    (MI_Result (MI_CALL *)(_Inout_   MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_Datetime *value,MI_Uint32 flags)) GenericOptions_SetDateTime,
    (MI_Result (MI_CALL *)(_Inout_   MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_Interval *value,MI_Uint32 flags)) GenericOptions_SetInterval,
    (MI_Result (MI_CALL *)(_Inout_   MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_In_   const MI_UserCredentials *credentials,MI_Uint32 flags)) GenericOptions_AddCredentials,
    (MI_Result (MI_CALL *)(_Inout_ MI_SubscriptionDeliveryOptions* self)) GenericOptions_Delete,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_Outptr_result_z_ const MI_Char **value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetString,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Uint32 *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetNumber,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Datetime *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetDateTime,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Interval *value,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetInterval,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_Out_opt_ MI_Uint32 *count)) GenericOptions_GetOptionCount,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOptionAt,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_In_z_ const MI_Char *optionName,_Out_ MI_Value *value,_Out_ MI_Type *type,_Out_opt_ MI_Uint32 *index,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetOption,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,_Out_ MI_Uint32 *count)) GenericOptions_GetCredentialsCount,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_ MI_UserCredentials *credentials,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetCredentialsAt,
    (MI_Result (MI_CALL *)(_In_   const MI_SubscriptionDeliveryOptions *options,MI_Uint32 index,_Outptr_result_z_ const MI_Char **optionName,_Out_writes_to_opt_(bufferLength, *passwordLength) MI_Char *password,_In_ MI_Uint32 bufferLength,_Out_ MI_Uint32 *passwordLength,_Out_opt_ MI_Uint32 *flags)) GenericOptions_GetCredentialsPasswordAt,
    (MI_Result (MI_CALL *)(_In_ const MI_SubscriptionDeliveryOptions* self,_Out_ MI_SubscriptionDeliveryOptions* newSubscriptionDeliveryOptions)) GenericOptions_Clone
} ;
