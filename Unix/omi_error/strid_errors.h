#if defined(_MSC_VER) || defined(RC_INVOKED)
#define STRID_ERRNO 1000
#define STRID_EPERM 1001
#define STRID_ENOENT 1002
#define STRID_ESRCH 1003
#define STRID_EINTR 1004
#define STRID_EIO 1005
#define STRID_ENXIO 1006
#define STRID_E2BIG 1007
#define STRID_ENOEXEC 1008
#define STRID_EBADF 1009
#define STRID_ECHILD 1010
#define STRID_EAGAIN 1011
#define STRID_ENOMEM 1012
#define STRID_EACCES 1013
#define STRID_EFAULT 1014
#define STRID_EBUSY 1015
#define STRID_EEXIST 1016
#define STRID_EXDEV 1017
#define STRID_ENODEV 1018
#define STRID_ENOTDIR 1019
#define STRID_EISDIR 1020
#define STRID_EINVAL 1021
#define STRID_ENFILE 1022
#define STRID_EMFILE 1023
#define STRID_ENOTTY 1024
#define STRID_EFBIG 1025
#define STRID_ENOSPC 1026
#define STRID_ESPIPE 1027
#define STRID_EROFS 1028
#define STRID_EMLINK 1029
#define STRID_EPIPE 1030
#define STRID_EDOM 1031
#define STRID_ERANGE 1032
#define STRID_EDEADLK 1033
#define STRID_ENAMETOOLONG 1034
#define STRID_ENOLCK 1035
#define STRID_ENOSYS 1036
#define STRID_EILSEQ 1037
#define STRID_STRUNCATE 1038
#else
#define STRID_EPERM MI_T("Operation not permitted")
#define STRID_ENOENT MI_T("No such file or directory")
#define STRID_ESRCH MI_T("No such process")
#define STRID_EINTR MI_T("Interrupted function")
#define STRID_EIO MI_T("I/O error")
#define STRID_ENXIO MI_T("No such device or address")
#define STRID_E2BIG MI_T("Argument list too long")
#define STRID_ENOEXEC MI_T("Exec format error")
#define STRID_EBADF MI_T("Bad file number")
#define STRID_ECHILD MI_T("No spawned processes")
#define STRID_EAGAIN MI_T("No more processes or not enough memory or maximum nesting level reached")
#define STRID_ENOMEM MI_T("Not enough memory")
#define STRID_EACCES MI_T("Permission denied")
#define STRID_EFAULT MI_T("Bad address")
#define STRID_EBUSY MI_T("Device or resource busy")
#define STRID_EEXIST MI_T("File exists")
#define STRID_EXDEV MI_T("Cross-device link")
#define STRID_ENODEV MI_T("No such device")
#define STRID_ENOTDIR MI_T("Not a directory")
#define STRID_EISDIR MI_T("Is a directory")
#define STRID_EINVAL MI_T("Invalid argument")
#define STRID_ENFILE MI_T("Too many files open in system")
#define STRID_EMFILE MI_T("Too many open files")
#define STRID_ENOTTY MI_T("Inappropriate I/O control operation")
#define STRID_EFBIG MI_T("File too large")
#define STRID_ENOSPC MI_T("No space left on device")
#define STRID_ESPIPE MI_T("Invalid seek")
#define STRID_EROFS MI_T("Read-only file system")
#define STRID_EMLINK MI_T("Too many links")
#define STRID_EPIPE MI_T("Broken pipe")
#define STRID_EDOM MI_T("Math argument")
#define STRID_ERANGE MI_T("Result too large")
#define STRID_EDEADLK MI_T("Resource deadlock would occur")
#define STRID_ENAMETOOLONG MI_T("Filename too long")
#define STRID_ENOLCK MI_T("No locks available")
#define STRID_ENOSYS MI_T("Function not supported")
#define STRID_EILSEQ MI_T("Illegal byte sequence")
#define STRID_STRUNCATE MI_T("String was truncated")
#endif

#if defined (_MSC_VER) || defined(RC_INVOKED)
#define STRID_MI_RESULT_OK 2000
#define STRID_MI_RESULT_FAILED 2001
#define STRID_MI_RESULT_ACCESS_DENIED 2002
#define STRID_MI_RESULT_INVALID_NAMESPACE 2003
#define STRID_MI_RESULT_INVALID_PARAMETER 2004
#define STRID_MI_RESULT_INVALID_CLASS 2005
#define STRID_MI_RESULT_NOT_FOUND 2006
#define STRID_MI_RESULT_NOT_SUPPORTED 2007
#define STRID_MI_RESULT_CLASS_HAS_CHILDREN 2008
#define STRID_MI_RESULT_CLASS_HAS_INSTANCES 2009
#define STRID_MI_RESULT_INVALID_SUPERCLASS 2010
#define STRID_MI_RESULT_ALREADY_EXISTS 2011
#define STRID_MI_RESULT_NO_SUCH_PROPERTY 2012
#define STRID_MI_RESULT_TYPE_MISMATCH 2013
#define STRID_MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED 2014
#define STRID_MI_RESULT_INVALID_QUERY 2015
#define STRID_MI_RESULT_METHOD_NOT_AVAILABLE 2016
#define STRID_MI_RESULT_METHOD_NOT_FOUND 2017
#define STRID_MI_RESULT_NAMESPACE_NOT_EMPTY 2020
#define STRID_MI_RESULT_INVALID_ENUMERATION_CONTEXT 2021
#define STRID_MI_RESULT_INVALID_OPERATION_TIMEOUT 2022
#define STRID_MI_RESULT_PULL_HAS_BEEN_ABANDONED 2023
#define STRID_MI_RESULT_PULL_CANNOT_BE_ABANDONED 2024
#define STRID_MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED 2025
#define STRID_MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED 2026
#define STRID_MI_RESULT_SERVER_LIMITS_EXCEEDED 2027
#define STRID_MI_RESULT_SERVER_IS_SHUTTING_DOWN 2028
#define STRID_MI_RESULT_CANCELED 2029
#define STRID_MI_RESULT_OPEN_FAILED 2030
#define STRID_MI_RESULT_INVALID_CLASS_HIERARCHY 2031
#define STRID_MI_RESULT_WOULD_BLOCK 2032
#define STRID_MI_RESULT_TIME_OUT 2033
#else
#define STRID_MI_RESULT_OK MI_T("The operation was successful.")
#define STRID_MI_RESULT_FAILED MI_T("A general error occurred, not covered by a more specific error code.")
#define STRID_MI_RESULT_ACCESS_DENIED MI_T("Access to a CIM resource is not available to the client.")
#define STRID_MI_RESULT_INVALID_NAMESPACE MI_T("The target namespace does not exist.")
#define STRID_MI_RESULT_INVALID_PARAMETER MI_T("One or more parameter values passed to the method are not valid.")
#define STRID_MI_RESULT_INVALID_CLASS MI_T("The specified class does not exist.")
#define STRID_MI_RESULT_NOT_FOUND MI_T("The requested object cannot be found.")
#define STRID_MI_RESULT_NOT_SUPPORTED MI_T("The requested operation is not supported.")
#define STRID_MI_RESULT_CLASS_HAS_CHILDREN MI_T("The operation cannot be invoked because the class has subclasses.")
#define STRID_MI_RESULT_CLASS_HAS_INSTANCES MI_T("The operation cannot be invoked because the class has instances.")
#define STRID_MI_RESULT_INVALID_SUPERCLASS MI_T("The operation cannot be invoked because the superclass does not exist.")
#define STRID_MI_RESULT_ALREADY_EXISTS MI_T("The operation cannot be invoked because an object already exists.")
#define STRID_MI_RESULT_NO_SUCH_PROPERTY MI_T("The specified property does not exist.")
#define STRID_MI_RESULT_TYPE_MISMATCH MI_T("The value supplied is not compatible with the type.")
#define STRID_MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED MI_T("The query language is not recognized or supported.")
#define STRID_MI_RESULT_INVALID_QUERY MI_T("The query is not valid for the specified query language.")
#define STRID_MI_RESULT_METHOD_NOT_AVAILABLE MI_T("The extrinsic method cannot be invoked.")
#define STRID_MI_RESULT_METHOD_NOT_FOUND MI_T("The specified extrinsic method does not exist.")
#define STRID_MI_RESULT_NAMESPACE_NOT_EMPTY MI_T("The specified namespace is not empty.")
#define STRID_MI_RESULT_INVALID_ENUMERATION_CONTEXT MI_T("The enumeration identified by the specified context is invalid.")
#define STRID_MI_RESULT_INVALID_OPERATION_TIMEOUT MI_T("The specified operation timeout is not supported by the CIM Server.")
#define STRID_MI_RESULT_PULL_HAS_BEEN_ABANDONED MI_T("The Pull operation has been abandoned.")
#define STRID_MI_RESULT_PULL_CANNOT_BE_ABANDONED MI_T("The attempt to abandon a concurrent Pull operation failed.")
#define STRID_MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED MI_T("Using a filter in the enumeration is not supported by the CIM server.")
#define STRID_MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED MI_T("The CIM server does not support continuation on error.")
#define STRID_MI_RESULT_SERVER_LIMITS_EXCEEDED MI_T("The operation failed because server limits were exceeded.")
#define STRID_MI_RESULT_SERVER_IS_SHUTTING_DOWN MI_T("The CIM server is shutting down and cannot process the operation.")
#define STRID_MI_RESULT_CANCELED MI_T("The operation was canceled")
#define STRID_MI_RESULT_OPEN_FAILED MI_T("The operation failed.")
#define STRID_MI_RESULT_INVALID_CLASS_HIERARCHY MI_T("Invalid class hierarchy.")
#define STRID_MI_RESULT_WOULD_BLOCK MI_T("Socket would block")
#define STRID_MI_RESULT_TIME_OUT MI_T("Result timed out")
#endif
