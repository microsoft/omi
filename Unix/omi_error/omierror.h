#ifndef _omierror_h
#define _omierror_h

#include "OMI_Error.h"
#include <pal/strings.h>
#include <base/batch.h>

_Success_(return == MI_RESULT_OK)
MI_Result OMI_ErrorFromErrorCode(
    _In_opt_ Batch* batch,
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char *OMI_Type,  
    _In_z_ const MI_Char* OMI_ErrorMessage, 
    _Outptr_opt_result_maybenull_ OMI_Error **omiError_);

MI_ErrorCategory ErrorCategoryFromErrorCode(
    MI_Uint32 OMI_Code, 
    _In_z_ const MI_Char *OMI_Type);

const MI_Char *ErrnoToString(
    MI_Uint32 OMI_Code,
    _Out_writes_z_(len) MI_Char *buffer,
    MI_Uint32 len);

MI_Result FaultString_ToMiResult(
    const ZChar *faultString, 
    MI_Result *result);
#endif /* _omierror_h */
