#ifndef _class_h
#define _class_h

#include <MI.h>

#ifdef __cplusplus
extern "C" {
#endif

MI_Result Test_Class_Construct(
    _Out_ MI_Class* clss,
    _In_ const MI_ClassDecl* classDecl);

#ifdef __cplusplus
}
#endif

#endif /* _class_h */
