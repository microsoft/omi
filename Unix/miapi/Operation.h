/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_operation_h_
#define _miapi_operation_h_

#include <MI.h>

MI_Result MI_CALL Operation_Close(
    _In_ MI_Operation *operation);
MI_Result MI_CALL Operation_Cancel(
    _In_  MI_Operation *operation,
          MI_CancelationReason reason);
MI_Result MI_CALL Operation_GetParentSession(
    _In_      MI_Operation *operation,
    _Out_     MI_Session *session);
MI_Result MI_CALL Operation_GetInstance_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails);
MI_Result MI_CALL Operation_GetIndication_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_       const MI_Instance **instance,
    _Outptr_opt_result_maybenull_z_ const MI_Char **bookmark,
    _Outptr_opt_result_maybenull_z_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_   const MI_Instance **completionDetails);
MI_Result MI_CALL Operation_GetClass_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Class **classResult,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails);

void MI_CALL Operation_Execute_GetInstance(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_       const MI_Instance *inboundInstance,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation);

void MI_CALL Operation_Execute_Invoke(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * className,
    _In_z_     const MI_Char * methodName,
    _In_opt_   const MI_Instance *inboundInstance,
    _In_opt_   const MI_Instance *inboundProperties,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation);

void MI_CALL Operation_Execute_ModifyInstance(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_       const MI_Instance *inboundInstance,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_     MI_Operation *operation);

void MI_CALL Operation_Execute_CreateInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);

void MI_CALL Operation_Execute_DeleteInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);


void MI_CALL Operation_Execute_EnumerateInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * className,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);

void MI_CALL Operation_Execute_QueryInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * queryDialect,
    _In_opt_z_ const MI_Char * queryExpression,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);

void MI_CALL Operation_Execute_AssociatorInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *instanceKey,
    _In_opt_z_ const MI_Char * assocClass,
    _In_opt_z_ const MI_Char * resultClass,
    _In_opt_z_ const MI_Char * role,
    _In_opt_z_ const MI_Char * resultRole,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);

void MI_CALL Operation_Execute_ReferenceInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *instanceKey,
    _In_opt_z_ const MI_Char * resultClass,
    _In_opt_z_ const MI_Char * role,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation);

void MI_CALL Operation_Execute_GetClass(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *className,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation);

void MI_CALL Operation_Execute_EnumerateClasses(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *className,
               MI_Boolean classNamesOnly,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation);

void MI_CALL Operation_Execute_Subscribe(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *queryDialect,
    _In_opt_z_ const MI_Char *queryExpression,
    _In_opt_   const MI_SubscriptionDeliveryOptions *deliverOptions,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation);

void MI_CALL Operation_Execute_TestConnection(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation
    );

#endif /* _miapi_operation_h_ */

