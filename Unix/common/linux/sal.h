/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _SAL_h
#define _SAL_h

#if !defined(_In_)
# define _In_
#endif

#if !defined(_In_count_)
# define _In_count_(count)
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

#if !defined(_Must_inspect_result_)
# define _Must_inspect_result_
#endif

#if !defined(_Out_)
# define _Out_
#endif

#if !defined(_Outptr_)
# define _Outptr_
#endif

#if !defined(_Outptr_opt_)
# define _Outptr_opt_
#endif

#if !defined(_Out_writes_z_)
# define _Out_writes_z_(count)
#endif

#if !defined(_Outptr_result_z_)
# define _Outptr_result_z_
#endif

#if !defined(_Outptr_result_bytebuffer_)
# define _Outptr_result_bytebuffer_(count)
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

#if !defined(_In_reads_bytes_)
# define _In_reads_bytes_(count)
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

#if !defined(_Inout_opt_)
# define _Inout_opt_
#endif

#if !defined(_Inout_z_)
# define _Inout_z_
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

#if !defined(_In_reads_z_)
# define _In_reads_z_(count)
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

#if !defined(_Check_return_)
#define _Check_return_
#endif

#if !defined(_Deref_post_z_)
#define _Deref_post_z_
#endif

#if !defined(_Deref_prepost_opt_z_)
#define _Deref_prepost_opt_z_
#endif

#if !defined(_Deref_out_range_)
#define _Deref_out_range_(min, max)
#endif

#if !defined(_Inout_opt_z_)
#define _Inout_opt_z_
#endif

#if !defined(_Inout_updates_z_)
#define _Inout_updates_z_(count)
#endif

#if !defined(_Out_writes_)
#define _Out_writes_(count)
#endif

#if !defined(_Post_readable_size_)
#define _Post_readable_size_(count)
#endif

#if !defined(_Post_ptr_invalid_)
#define _Post_ptr_invalid_
#endif

#if !defined(_Pre_valid_)
#define _Pre_valid_
#endif

#if !defined(_Pre_writable_size_)
#define _Pre_writable_size_(count)
#endif

#if !defined(_Success_)
#define _Success_(count)
#endif

#if !defined(_Ret_notnull_)
#define _Ret_notnull_
#endif

#if !defined(_Ret_z_)
#define _Ret_z_
#endif

#if !defined(_Use_decl_annotations_)
#define _Use_decl_annotations_
#endif

#if !defined(_Ret_maybenull_)
#define _Ret_maybenull_
#endif

#if !defined(_Pre_writable_byte_size_)
#define _Pre_writable_byte_size_(count)
#endif

#if !defined(_Post_writable_byte_size_)
#define _Post_writable_byte_size_(count)
#endif

#if !defined(_Analysis_assume_)
#define _Analysis_assume_(expr)
#endif

#if !defined(_Post_satisfies_)
#define _Post_satisfies_(expr)
#endif

#if !defined(_Post_invalid_)
#define _Post_invalid_
#endif

#if !defined(_Post_valid_)
#define _Post_valid_
#endif

#if !defined(_Pre_notnull_)
#define _Pre_notnull_
#endif

#if !defined(_When_)
#define _When_(expr1, expr2)
#endif

#define _Deref_pre_z_

#if !defined(_Inout_updates_)
#define _Inout_updates_(count)
#endif

#if !defined(_Out_writes_opt_z_)
#define _Out_writes_opt_z_(count)
#endif

#if !defined(_Out_cap_post_count_)
#define _Out_cap_post_count_(maxLen,used)
#endif

#if !defined(_Inout_count_)
#define _Inout_count_(size)
#endif

#if !defined(_Post_equal_to_)
#define _Post_equal_to_(expr)
#endif

#if !defined(_Field_size_bytes_)
# define _Field_size_bytes_(count)
#endif

#if !defined(_Field_range_)
# define _Field_range_(count, capacity)
#endif

#if !defined(_Post_z_)
# define _Post_z_
#endif

#if !defined(_Outptr_result_buffer_)
# define _Outptr_result_buffer_(count)
#endif

#if !defined(_Field_size_)
# define _Field_size_(count)
#endif

#if !defined(_Always_)
# define _Always_(expr)
#endif

#if !defined(_Readable_bytes_)
# define _Readable_bytes_(count)
#endif

#if !defined(_Outptr_result_buffer_maybenull_)
# define _Outptr_result_buffer_maybenull_(count)
#endif

#endif /* _SAL_h */
