/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_provreg_h
#define _omi_provreg_h

#include <common.h>
#include <base/stringarray.h>
#include <base/batch.h>
#include <pal/dir.h>

BEGIN_EXTERNC

typedef enum _ProvInterface
{
    PROV_INTERFACE_STATIK = 1
}
ProvInterface;

typedef enum _ProvRegType
{
    PROVREG_DEFAULT = 0,
    PROVREG_INDICATION = 1
} ProvRegType;

typedef enum _ProvHosting
{
//    PROV_HOSTING_INPROC = 0,
    PROV_HOSTING_REQUESTOR = 1,
    PROV_HOSTING_USER = 2,
    PROV_HOSTING_REQUESTOR_SHELL = 3
}
ProvHosting;

#define  PROV_REG_HOSTING_INPROC          "@inproc@"
#define  PROV_REG_HOSTING_REQUESTOR       "@requestor@"
#define  PROV_REG_HOSTING_REQUESTOR_SHELL "@requestor-shell@"

typedef struct _ProvRegPosition
{
    struct _ProvRegClassInheritanceNode* start;
    struct _ProvRegClassInheritanceNode* current;
    MI_Boolean deep;
}
ProvRegPosition;

typedef struct _ProvRegAssocPosition
{
    struct _ProvRegClassInheritanceNode*    assocClass;
    struct _ProvRegClassInheritanceNode*    resultClass;
    struct _ProvRegClassInheritanceNode*    currentLeft;
    struct _ProvRegAssocBackLinkNode*       currentAssoc;
    struct _ProvRegClassInheritanceNode*    currentRight;
}
ProvRegAssocPosition;

typedef struct _ProvRegEntry
{
    /* Pointer to next entry */
    struct _ProvRegEntry* next;

    /* Provider interface type */
    ProvInterface provInterface;

    /* Hosting type for provider execution */
    ProvHosting hosting;

    /* User name for 'USER' mode (when user specified at registration time) */
    const char*     user;

    /* Namespace this provider serves */
    const ZChar* nameSpace;
    unsigned int nameSpaceHash;

    /* Class this provider supplies */
    const ZChar* className;
    unsigned int classNameHash;

    /* The name library of the library containing provider */
    const char* libraryName;

#if defined(CONFIG_ENABLE_PREEXEC)

    /* Name of program to be executed before invoking this provider */
    const char* preexec;

#endif /* defined(CONFIG_ENABLE_PREEXEC) */

    /* The type of the registered class */
    ProvRegType regType;

    /* 1 if lifetime of instance is that of context,
     * 0 otherwise
     */
    int instanceLifetimeContext;
}
ProvRegEntry;

typedef struct _ProvReg
{
    Batch batch;
    char buffer[1024];
    ProvRegEntry* head;
    ProvRegEntry* tail;
    struct _ProvRegNamespaceNode* namespaces;
    struct _ProvRegNamespaceNode* namespacesForExtraClasses;
}
ProvReg;

/* Initialize ProvReg strucutre from given directory */
MI_Result ProvReg_Init(
    _Inout_ ProvReg* self,
    _In_z_ const char* directory);

/* Initialize ProvReg strucutre from omiregister directory */
MI_Result ProvReg_Init2(
    _Inout_ ProvReg* self);

void ProvReg_Destroy(
    ProvReg* self);

const ProvRegEntry* ProvReg_FindProviderForClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    MI_Result *findError);

/* returns ok or not-found; baseClass will be null if no base class exist */
MI_EXPORT MI_Result ProvReg_GetDirectBaseClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    const ZChar** baseClass,
    MI_Boolean extraClass);

/* enumerates classes derived classes:
 - if deep == false and className == null, returns all root classes
 - if deep == true and className == null, returns all classes
 - if deep == false and className provided, returns all classes directly derived from given
 - if deep == true and className provided, returns all classes derived from given
*/
MI_EXPORT MI_Result ProvReg_BeginClasses(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    MI_Boolean deep,
    ProvRegPosition* pos,
    MI_Boolean extraClass);

MI_EXPORT MI_Result ProvReg_NextClass(
    ProvRegPosition* pos,
    const ZChar** className,
    MI_Boolean* done);

MI_EXPORT MI_Result ProvReg_EndClasses(
    ProvRegPosition* pos);


/* returns enumerator to all registered association classes by given instance
 * class and (optionally) assoc/result classes
 */
MI_EXPORT MI_Result ProvReg_BeginAssocClasses(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    const ZChar* assocClassName,  /* can be NULL */
    const ZChar* resultClassName, /* can be NULL */
    ProvRegAssocPosition* pos);

MI_EXPORT MI_Result ProvReg_NextAssocClass(
    ProvRegAssocPosition* pos,
    const ZChar** className,
    MI_Boolean* done);

MI_EXPORT MI_Result ProvReg_EndAssocClasses(
    ProvRegAssocPosition* pos);

void MapRegPositionValuesToRegEntry(
    ProvRegEntry* reg,
    ProvRegPosition* pos);

void ProvReg_Dump(
    ProvReg* self,
    FILE* os);

/* Find provider registration object for class */
const ProvRegEntry* ProvReg_FindProviderForClassByType(
    _In_ ProvReg* self,
    _In_z_ const ZChar* nameSpace,
    _In_opt_z_ const ZChar* className,
    _In_ ProvRegType type,
    _Out_ MI_Result *findError);

END_EXTERNC

#endif /* _omi_provreg_h */
