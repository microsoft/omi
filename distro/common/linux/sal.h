/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _SAL_h
#define _SAL_h

#if !defined(_In_)
# define _In_
#endif

#if !defined(_In_opt_)
# define _In_opt_
#endif

#if !defined(_In_z_)
# define _In_z_
#endif

#if !defined(_In_opt_z_)
# define _In_opt_z_
#endif

#if !defined(_Out_)
# define _Out_
#endif

#if !defined(_Outptr_)
# define _Outptr_
#endif

#if !defined(_Out_writes_z_)
# define _Out_writes_z_(count)
#endif

#if !defined(_Outptr_result_z_)
# define _Outptr_result_z_
#endif

#if !defined(_Outptr_result_maybenull_)
# define _Outptr_result_maybenull_
#endif

#if !defined(_Outptr_opt_result_maybenull_)
# define _Outptr_opt_result_maybenull_
#endif

#if !defined(_Outptr_result_maybenull_z_)
# define _Outptr_result_maybenull_z_
#endif

#if !defined(_Outptr_opt_result_z_)
# define _Outptr_opt_result_z_
#endif

#if !defined(_Outptr_opt_result_maybenull_z_)
# define _Outptr_opt_result_maybenull_z_
#endif

#if !defined(_Return_type_success_)
# define _Return_type_success_(expr)
#endif

#if !defined(_In_reads_opt_)
# define _In_reads_opt_(expr)
#endif

#if !defined(_Out_writes_to_opt_)
# define _Out_writes_to_opt_(length, lengthwritten)
#endif

#if !defined(_Acquires_lock_)
# define _Acquires_lock_(lock)
#endif

#if !defined(_Releases_lock_)
# define _Releases_lock_(lock)
#endif

#if !defined(_Inout_)
# define _Inout_
#endif

#if !defined(_Out_opt_)
# define _Out_opt_
#endif

#if !defined(_Out_writes_bytes_)
# define _Out_writes_bytes_(count)
#endif

#if !defined(_In_reads_)
# define _In_reads_(count)
#endif

#if !defined(_Out_writes_opt_)
# define _Out_writes_opt_(count)
#endif

#if !defined(_Null_terminated_)
#define _Null_terminated_
#endif

#if !defined(_Requires_lock_not_held_)
#define _Requires_lock_not_held_(lock)
#endif

#if !defined(_Requires_lock_held_)
#define _Requires_lock_held_(lock)
#endif

#if !defined(__field_ecount)
#define __field_ecount(count)
#endif

#define _Check_return_
#define _Deref_post_z_
#define _Deref_prepost_opt_z_
#define _Inout_opt_z_
#define _Inout_updates_z_(count)
#define _Out_writes_(count)
#define _Post_readable_size_(count)
#define _Post_ptr_invalid_
#define _Pre_valid_
#define _Pre_writable_size_(count)
#define _Success_(count)
#define _Ret_notnull_
#define _Use_decl_annotations_
#define _Ret_maybenull_
#define _Post_writable_byte_size_(count)
#define _Analysis_assume_(expr)

#endif /* _SAL_h */
