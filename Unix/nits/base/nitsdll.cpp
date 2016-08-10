/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "Globals.h"
#ifdef _MSC_VER
    #include <nitsdll.tmh>
#endif

#include <pal/lock.h>

namespace TestSystem
{

//This object sets up internal cross-process structures automatically.
//No other action is necessary beyond linking to this DLL.
System System::s_system;

NITS_EXPORT DWORD Initialize(_In_z_ const PAL_Char * name,
                 _In_reads_bytes_(bytes) void const *context,
                 _Outptr_result_bytebuffer_(bytes) void **shared,
                 long bytes)
{
    static Lock s_spinlock = LOCK_INITIALIZER;

    Lock_Acquire(&s_spinlock);

    DWORD error = 0;

    Mapping &m = System::GetInstance().GetMapping(name);
    error = m.Initialize(context, bytes);
    *shared = m.m_data;

    Lock_Release(&s_spinlock);
    return error;
}

NITS_EXPORT DWORD GetFaultWin32()
{
    return WIN32_FROM_HRESULT(GetGlobals().GetFaultError());
}

}//namespace TestSystem
