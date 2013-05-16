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

#ifndef _omi_provreg_h
#define _omi_provreg_h

#include <common.h>
#include <base/stringarray.h>
#include <base/batch.h>

BEGIN_EXTERNC

typedef enum _ProvInterface
{
    PROV_INTERFACE_STATIC = 1
}
ProvInterface;

typedef enum _ProvHosting
{
    PROV_HOSTING_INPROC = 0,
    PROV_HOSTING_REQUESTOR = 1,
    PROV_HOSTING_USER = 2
}
ProvHosting;

#define  PROV_REG_HOSTING_INPROC          "@inproc@"
#define  PROV_REG_HOSTING_REQUESTOR       "@requestor@"

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
}
ProvRegEntry;

typedef struct _ProvReg
{
    Batch batch;
    char buffer[1024];
    ProvRegEntry* head;
    ProvRegEntry* tail;
    struct _ProvRegNamespaceNode* namespaces;
}
ProvReg;


MI_Result ProvReg_Init2(
    ProvReg* self);

void ProvReg_Destroy(
    ProvReg* self);

const ProvRegEntry* ProvReg_FindProviderForClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className);


/* returns ok or not-found; baseClass will be null if no base class exist */
MI_EXPORT MI_Result ProvReg_GetDirectBaseClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    const ZChar** baseClass);

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
    ProvRegPosition* pos);

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

void ProvReg_Dump(
    ProvReg* self,
    FILE* os);

END_EXTERNC

#endif /* _omi_provreg_h */
