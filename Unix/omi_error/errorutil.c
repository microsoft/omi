#include "errorutil.h"
#include "OMI_Error.h"
#include "omierror.h"
#include <base/log.h>
#include <base/packing.h>
#include <wsman/wsbuf.h>

/*
**==============================================================================
**
** Helper to create PostResultMsg
**
**==============================================================================
*/
_Use_decl_annotations_
PostResultMsg* PostResultMsg_NewAndSerialize(
    Message* req,
    const MI_Instance* err,
    const MI_Char* errmsg,
    const MI_Char *errorType,
    MI_Uint32 r)
{
    PostResultMsg* msg = NULL;
    const MI_Instance* error = err;
    MI_Result result = MI_RESULT_OK;
    DEBUG_ASSERT( req );
    msg = PostResultMsg_New(req->operationId);
    if (!msg)
    {
        return NULL;
    }

    if (!error)
    {
        OMI_ErrorFromErrorCode(
            msg->base.batch,
            r,
            errorType,
            errmsg,
            (OMI_Error**)&error);
    }
    if (error)
    {
        MI_Value value;
        MI_Type type;
        MI_Result result;
    
        result = MI_Instance_GetElement(error, MI_T("CIMStatusCode"), &value, &type, NULL, NULL);
        if ((MI_RESULT_OK == result) && (type == MI_UINT32))
        {
            r = value.uint32;
        }
        else
        {
            /* failed to get real status code so assume failed */
            r = MI_RESULT_FAILED;
        }
    }
    else if (Tcscmp(errorType, MI_RESULT_TYPE_MI) != 0)
    {
        /* convert non-MI result to an MI result */
        r = MI_RESULT_FAILED;
    }

    /* create final result message */
    do
    {
        if (error && (errmsg == NULL))
        {
            MI_Value messageValue;
            MI_Type messageType;

            result = MI_Instance_GetElement(error, MI_T("Message"), &messageValue, &messageType, NULL, NULL);
            if ((MI_RESULT_OK == result) && (MI_STRING == messageType))
            {
                errmsg = Batch_Tcsdup(msg->base.batch, messageValue.string);
            }
        }
        msg->result = (MI_Result)r;
        if (errmsg)
        {
            msg->errorMessage = Batch_Tcsdup(msg->base.batch, errmsg);
        }
        else
        {
            msg->errorMessage = NULL;
        }
        msg->cimError = error;
        msg->packedInstancePtr = NULL;
        msg->packedInstanceSize = 0;
        msg->cimErrorClassName = NULL;

        if (error)
        {
            if (req->flags & WSMANFlag)
            {
                /* This puts a pretty bad dependency on a bunch of stuff so we are removing this from 
                 * from minimum size build and relying on default WSman IF and ONLY if that is needed.
                 * The results will have default values for the error case in that case.
                 */
                result = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    error,
                    NULL, /* filterProperty */
                    NULL, /* filterPropertyData */
                    error->classDecl,
                    msg->base.batch,
                    WSMAN_ObjectFlag | WSMAN_IsCimError,
                    &msg->packedInstancePtr, 
                    &msg->packedInstanceSize);
                if (result != MI_RESULT_OK)
                    break;
                msg->base.flags |= req->flags;
            }
            else /* Binary protocol */
            {
                result = InstanceToBatch(
                    error,
                    NULL,
                    NULL,
                    msg->base.batch,
                    &msg->packedInstancePtr,
                    &msg->packedInstanceSize);
                if (result != MI_RESULT_OK)
                    break;
                msg->base.flags |= BinaryProtocolFlag;
            }
            msg->cimErrorClassName = Batch_Tcsdup(msg->base.batch, error->classDecl->name);
        }
    }
    while(0);

    if ((result != MI_RESULT_OK) && (NULL != msg))
    {
        /* TODO: Trace message */
        PostResultMsg_Release(msg);
        msg = NULL;
    }

    return msg;
}

