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

#include <stdio.h>
#include <ctype.h>
#include <base/strings.h>
#include <io/io.h>
#include <base/dir.h>
#include <base/paths.h>
#include <base/naming.h>
#include "provreg.h"
#include "regfile.h"

typedef struct _ProvRegNamespaceNode
{
    struct _ProvRegNamespaceNode* next;
    MI_ConstString  ns;
    struct _ProvRegClassInheritanceNode* tree;
}
ProvRegNamespaceNode;

typedef struct _ProvRegAssocBackLinkNode
{
    struct _ProvRegAssocBackLinkNode* next;
    struct _ProvRegClassInheritanceNode* assocClass;
}
ProvRegAssocBackLinkNode;

typedef struct _ProvRegClassInheritanceNode
{
    MI_ConstString  cn;
    struct _ProvRegClassInheritanceNode* parent;
    struct _ProvRegClassInheritanceNode* nextSibling;
    struct _ProvRegClassInheritanceNode* firstChild;
    /* assoc support */
    /* left/right are not-null only for assoc class */
    struct _ProvRegClassInheritanceNode* left;
    struct _ProvRegClassInheritanceNode* right;

    /* linked list of all assoc classes that refer this class */
    ProvRegAssocBackLinkNode* associatorClasses;
}
ProvRegClassInheritanceNode;

#if (MI_CHAR_TYPE == 1)
#define MI_ScasecmpChar_MIChar Zcasecmp
#else
static int MI_ScasecmpChar_MIChar(
    const char* str1,
    const ZChar* str2 )
{
    /* assuming str2 is ascii char-set only */
    for(;;)
    {
        int c1 = tolower((unsigned char)*str1);
        int c2 = tolower((unsigned char)*str2);

        if (c1 != c2 )
        {
            return c1 < c2 ? -1 : 1;
        }
        if (!c1)
            break;

        str1++;
        str2++;
    }

    return 0;
}
#endif

/* returns last segment from the string or string itself;
    for example, for string abc,edf,ghk  function returns 'ghk', 'edf' and 'abc' */
static char* _GetNextReverse(_Inout_ CharPtr* text, char delim)
{
    char* start = *text;
    char* end;
    size_t len;

    /* If at end of string */
    if (!*start)
        return NULL;

    len = strlen(start);

    /* end of string */
    end = start + len;

    /* Remove trailing whitespace */
    for (; end != start && isspace((unsigned char)end[-1]);)
        *--end = '\0';

    /* Skip non-colon character characters */
    for (; end != start && *end != delim; end--)
        ;

    if ( end == start )
    {   /* last block - move position to the end to point to \0 */
        *text = start + len;
    }
    else
    {  /* skip delimiter*/
        *end = 0;
        end++;
    }

    /* Skip leading whitespace */
    while (*end && isspace((unsigned char)*end))
        end++;

    return end;
}

static char* _Strdup(Batch* batch, const char* s)
{
    size_t size = strlen(s) + 1;
    char* p;
    size_t i;

    p = Batch_Get(batch, size * sizeof(char));

    if (!p)
        return NULL;

    for (i = 0; i < size; i++)
        p[i] = s[i];

    return p;
}

static ZChar* _Strdup2(Batch* batch, const char* s)
{
    size_t size = strlen(s) + 1;
    ZChar* p;
    size_t i;

    p = Batch_Get(batch, size * sizeof(ZChar));

    if (!p)
        return NULL;

    for (i = 0; i < size; i++)
        p[i] = (ZChar)s[i];

    return p;
}

/* ********************************************************* */
/* ***           namespace operations                    *** */
/* ********************************************************* */

ProvRegNamespaceNode* _FindNamespace(
    ProvReg* self,
    MI_ConstString ns)
{
    /* find namespace node in the list */
    ProvRegNamespaceNode* current = self->namespaces;

    while (current && Zcasecmp(ns,current->ns) != 0)
        current = current->next;

    return current;
}

ProvRegNamespaceNode* _FindOrCreateNamespace(
    ProvReg* self,
    MI_ConstString ns)
{
    ProvRegNamespaceNode* item = _FindNamespace(self,ns);

    if (item)
        return item;

    item = (ProvRegNamespaceNode*)Batch_GetClear(
        &self->batch, sizeof(ProvRegNamespaceNode));

    if (item)
    {
        item->ns = ns; /* no need to strdup, since it's already in batch*/
        item->next = self->namespaces;
        self->namespaces = item;
    }

    return item;
}

/* ********************************************************* */
/* ***                tree operations                    *** */
/* ********************************************************* */
ProvRegClassInheritanceNode* _GetNextTreeNodeLimittedBy(
    ProvRegClassInheritanceNode* item,
    ProvRegClassInheritanceNode* subtreeRoot)
{
    /* first-child */
    if (item->firstChild)
        return item->firstChild;

    /* sibling */
    if (item->nextSibling)
        return item->nextSibling;

    /* sibling of direct or indirect parent*/
    while (item && item->parent != subtreeRoot)
    {
        item = item->parent;

        if (item && item->nextSibling)
            return item->nextSibling;
    }

    /* end of tree */
    return 0;
}

ProvRegClassInheritanceNode* _GetNextTreeNode(
    ProvRegClassInheritanceNode* item)
{
    return _GetNextTreeNodeLimittedBy(item,0);
}

ProvRegClassInheritanceNode* _FindClassNodeInTreeByChar(
    ProvRegClassInheritanceNode* root,
    const char* cn)
{
    while (root)
    {
        if (MI_ScasecmpChar_MIChar(cn,root->cn)==0)
        {
            return root;
        }
        root = _GetNextTreeNode(root);
    }
    return root;
}

ProvRegClassInheritanceNode* _FindClassNodeInTree(
    ProvRegClassInheritanceNode* root,
    const ZChar* cn)
{
    while (root)
    {
        if (Zcasecmp(cn,root->cn)==0)
        {
            return root;
        }
        root = _GetNextTreeNode(root);
    }
    return root;
}

MI_Boolean _ValidateTreeNodes(
    ProvRegClassInheritanceNode* derivedNode,
    ProvRegClassInheritanceNode* baseNode)
{
    /* if we have no nodes - it's fine - no info yet*/
    if ( !derivedNode && !baseNode )
        return MI_TRUE;

    /* if we have both nodes - check they are child/parent */
    if ( derivedNode && baseNode )
        return derivedNode->parent == baseNode;

    /* base must be specified */
    if ( derivedNode && !baseNode )
        return MI_FALSE;

    /* only one node is known - ok */
    return MI_TRUE;
}

static MI_Result _AddClassInheritanceInfo(
    ProvReg* self,
    MI_ConstString ns,
    const char* derivedClass, /* can be null */
    const char* baseClass )
{
    /* get (or create if needed) namespace item */
    ProvRegNamespaceNode* namespaceNode = _FindOrCreateNamespace(self,ns);
    ProvRegClassInheritanceNode* derivedNode, *baseNode;

    if (!namespaceNode)
        return MI_RESULT_FAILED;

    /* find classes' nodes */
    derivedNode = derivedClass ? _FindClassNodeInTreeByChar(namespaceNode->tree, derivedClass) : 0;
    baseNode = _FindClassNodeInTreeByChar(namespaceNode->tree, baseClass);

    /* validate nodes */
    if (!_ValidateTreeNodes(derivedNode,baseNode))
        return MI_RESULT_INVALID_CLASS_HIERARCHY;

    /* create missing nodes and insert them into tree */
    if ( !baseNode )
    {
        baseNode = (ProvRegClassInheritanceNode*)Batch_GetClear(
                &self->batch, sizeof(ProvRegClassInheritanceNode));

        if ( !baseNode )
            return MI_RESULT_FAILED;

        baseNode->cn = _Strdup2(&self->batch, baseClass);

        if ( !baseNode->cn )
            return MI_RESULT_FAILED;

        /* insert into tree */
        baseNode->nextSibling = namespaceNode->tree;
        namespaceNode->tree = baseNode;
    }

    if ( !derivedNode && derivedClass)
    {
        derivedNode = (ProvRegClassInheritanceNode*)Batch_GetClear(
                &self->batch, sizeof(ProvRegClassInheritanceNode));

        if ( !derivedNode )
            return MI_RESULT_FAILED;

        derivedNode->cn = _Strdup2(&self->batch, derivedClass);

        if ( !derivedNode->cn )
            return MI_RESULT_FAILED;

        /* add as a child */
        derivedNode->parent = baseNode;
        derivedNode->nextSibling = baseNode->firstChild;
        baseNode->firstChild = derivedNode;
    }

    return MI_RESULT_OK;
}

static MI_Result _AddAssociation(
    ProvReg* self,
    MI_ConstString ns,
    const char* assoc,
    const char* left,
    const char* right)
{
    /* find all related nodes */
    ProvRegNamespaceNode* namespaceNode;
    ProvRegClassInheritanceNode  *leftNode, *rightNode, *assocNode;

    /* check namespace */
    namespaceNode = _FindNamespace(self,ns);

    if (!namespaceNode)
        return MI_RESULT_INVALID_NAMESPACE;

    /* find class */
    leftNode = _FindClassNodeInTreeByChar(namespaceNode->tree, left);
    rightNode = _FindClassNodeInTreeByChar(namespaceNode->tree, right);
    assocNode = _FindClassNodeInTreeByChar(namespaceNode->tree, assoc);

    if (!leftNode || !rightNode || !assocNode)
        return MI_RESULT_INVALID_CLASS;

    /* add cross-links */
    assocNode->left = leftNode;
    assocNode->right = rightNode;

    {
        ProvRegAssocBackLinkNode* newLinkItemLeft;
        newLinkItemLeft = (ProvRegAssocBackLinkNode*)Batch_GetClear(
            &self->batch, sizeof(ProvRegAssocBackLinkNode));

        if (!newLinkItemLeft)
            return MI_RESULT_FAILED;

        newLinkItemLeft->assocClass = assocNode;
        newLinkItemLeft->next = leftNode->associatorClasses;
        leftNode->associatorClasses = newLinkItemLeft;
    }

    /* check if assoc links different classes */
    if (leftNode != rightNode)
    {
        ProvRegAssocBackLinkNode* newLinkItemRight;
        newLinkItemRight = (ProvRegAssocBackLinkNode*)Batch_GetClear(
            &self->batch, sizeof(ProvRegAssocBackLinkNode));
        if (!newLinkItemRight)
            return MI_RESULT_FAILED;

        newLinkItemRight->assocClass = assocNode;
        newLinkItemRight->next = rightNode->associatorClasses;
        rightNode->associatorClasses = newLinkItemRight;
    }

    return MI_RESULT_OK;
}

static MI_Result _GetSubclasses2(
    ProvReg* self,
    ProvRegEntry* e,
    _Inout_ CharPtr p)
{
    /* get all sub-classes */
    char* baseClass = _GetNextReverse(&p, ':');
    char* derivedClass = _GetNextReverse(&p, ':');
    MI_Result r;

    /* expecting to find at least one class */
    if (!baseClass)
        return MI_RESULT_INVALID_CLASS;

    while ( derivedClass )
    {
        r = _AddClassInheritanceInfo(self, e->nameSpace, derivedClass,
            baseClass);

        if ( MI_RESULT_OK != r )
            return r;

        baseClass = derivedClass;
        derivedClass = _GetNextReverse(&p, ':');
    }

    /* add base class with no parent */
    r = _AddClassInheritanceInfo(self, e->nameSpace, derivedClass, baseClass);
    if (MI_RESULT_OK != r)
        return r;

    e->className = _Strdup2(&self->batch, baseClass);
    if (!e->className)
    {
        return MI_RESULT_FAILED;
    }
    e->classNameHash = Hash(e->className);

    return MI_RESULT_OK;
}

static int _AddEntry(
    ProvReg* self,
    const char* nameSpace,
    RegFile* regFile,
    RegClass* regClass)
{
    ProvRegEntry* e;

#if 0
    RegFile_Print(regFile, stdout);
#endif

    /* Allocate new provider register entry */
    e = (ProvRegEntry*)Batch_GetClear(&self->batch, sizeof(ProvRegEntry));
    if (!e)
        return -1;

    /* ProvRegEntry.provInterface */
    e->provInterface = PROV_INTERFACE_STATIC;

    /* ProvRegEntry.nameSpace */
    e->nameSpace = _Strdup2(&self->batch, nameSpace);
    if (!e->nameSpace)
        return -1;

    e->nameSpaceHash = Hash(e->nameSpace);

    /* ProvRegEntry.libraryName */
    e->libraryName = _Strdup(&self->batch, regFile->library);
    if (e->libraryName == NULL)
        return -1;
    /* ProvRegEntry.hosting*/
    e->hosting = PROV_HOSTING_INPROC;

    if (regClass->hosting)
    {
        char hosting[64];
        Strlcpy(hosting, regClass->hosting, sizeof(hosting));

        /* it either user name or one of two special values:
         *  @inproc@
         *  @requestor@
         */
        if (strcmp(hosting, PROV_REG_HOSTING_INPROC) == 0)
        {
            e->hosting = PROV_HOSTING_INPROC;
        }
        else if (strcmp(hosting, PROV_REG_HOSTING_REQUESTOR) == 0)
        {
            e->hosting = PROV_HOSTING_REQUESTOR;
        }
        else
        {
            e->hosting = PROV_HOSTING_USER;
            e->user =  _Strdup(&self->batch, hosting);
            if (!e->user)
                return -1;
        }
    }

    /* If an association */
    if (regClass->refName1 && regClass->refName2)
    {
        if (_GetSubclasses2(self, e, regClass->refName1) != MI_RESULT_OK)
            return -1;

        if (_GetSubclasses2(self, e, regClass->refName2) != MI_RESULT_OK)
            return -1;

        if (_GetSubclasses2(self, e, regClass->name) != MI_RESULT_OK)
            return -1;

        if (_AddAssociation(self, e->nameSpace, regClass->name,
            regClass->refName1, regClass->refName2) != MI_RESULT_OK)
        {
            return -1;
        }
    }
    else
    {
        if (_GetSubclasses2(self, e, regClass->name) != MI_RESULT_OK)
            return -1;
    }

    /* Add entry to end of list */
    {
        e->next = NULL;

        if (self->tail)
        {
            self->tail->next = e;
            self->tail = e;
        }
        else
        {
            self->tail = e;
            self->head = e;
        }
    }

    return 0;
}

MI_Result ProvReg_Init2(ProvReg* self)
{
    Dir* dir = NULL;
    Dir* dir2 = NULL;
    RegFile* reg = NULL;

    /* Zero-fill self */
    memset(self, 0, sizeof(*self));

    /* Initialize batch allocator */
    Batch_Init(&self->batch, BATCH_MAX_PAGES);

    /* Open the 'omiregister' directory */

    dir = Dir_Open(GetPath(ID_REGISTERDIR));

    if (!dir)
    {
        return MI_RESULT_FAILED;
    }

    /* For each namespace directory in 'omiregister' */
    for ( ; ; )
    {
        DirEnt* ent = Dir_Read(dir);

        if (!ent)
        {
            break;
        }

        /* Ignore system directories */
        if (strcmp(ent->name, ".") == 0 || strcmp(ent->name, "..") == 0)
            continue;

        /* Skip 'CVS' directories */
        if (strcmp(ent->name, "CVS") == 0)
            continue;

        /* Scan .reg files in the current namespace directory */
        {
            char path[MAX_PATH_SIZE];

            Strlcpy(path, GetPath(ID_REGISTERDIR), sizeof(path));
            Strlcat(path, "/", sizeof(path));
            Strlcat(path, ent->name, sizeof(path));

            dir2 = Dir_Open(path);
            if (!dir2)
            {
                goto failed;
            }

            for ( ; ; )
            {
                DirEnt* ent2 = Dir_Read(dir2);
                if (!ent2)
                {
                    break;
                }

                /* Ignore system directories */
                if (strcmp(ent2->name,".") == 0 || strcmp(ent2->name,"..") == 0)
                {
                    continue;
                }

                /* Load the reg file */
                {
                    char regPath[MAX_PATH_SIZE];

                    /* Form path to .reg file */
                    Strlcpy(regPath, path, sizeof(regPath));
                    Strlcat(regPath, "/", sizeof(regPath));
                    Strlcat(regPath, ent2->name, sizeof(regPath));

                    /* Create new reg file object */
                    reg = RegFile_New(regPath);
                    if (!reg)
                    {
                        Zprintf(ZT("REGFILE{%s}\n"), scs(regPath));
                        goto failed;
                    }

                    /* For each class in the reg file */
                    {
                        RegClass* rc;

                        for (rc = reg->classesHead; rc; rc = rc->next)
                        {
                            char* p = ent->name;

                            /* Transpose NAMESPACE_SEPARATOR characters to '/'
                             * characters
                             */
                            while (*p)
                            {
                                if (*p == NAMESPACE_SEPARATOR)
                                    *p = '/';
                                p++;
                            }

                            if (_AddEntry(self, ent->name, reg, rc) != 0)
                            {
                                goto failed;
                            }
                        }
                    }

                    /* Delete the current entry */
                    RegFile_Delete(reg);
                    reg = NULL;
                }
            }

            /* Close the directory */
            Dir_Close(dir2);
            dir2 = NULL;
        }
    }

    /* Close directory */
    Dir_Close(dir);

    return MI_RESULT_OK;

failed:

    if (dir)
        Dir_Close(dir);

    if (dir2)
        Dir_Close(dir2);

    return MI_RESULT_FAILED;
}

void ProvReg_Destroy(
    ProvReg* self)
{
    Batch_Destroy(&self->batch);
}

void ProvReg_Dump(
    ProvReg* self,
    FILE* os)
{
    ProvRegEntry* p;

    for (p = self->head; p != NULL; p = p->next)
    {
        Fzprintf(os, ZT("==== ProvRegEntry\n"));
        Fzprintf(os, ZT("provInterface[%u]\n"), p->provInterface);
        Fzprintf(os, ZT("nameSpace[%Z]\n"), zcs(p->nameSpace));
        Fzprintf(os, ZT("className[%Z]\n"), zcs(p->className));
        Fzprintf(os, ZT("libraryName[%s]\n"), scs(p->libraryName));
    }
}

const ProvRegEntry* ProvReg_FindProviderForClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className)
{
    ProvRegEntry* p;
    unsigned int nameSpaceHash = Hash(nameSpace);
    unsigned int classNameHash = Hash(className);

    for (p = self->head; p != NULL; p = p->next)
    {
        if (nameSpaceHash == p->nameSpaceHash &&
            classNameHash == p->classNameHash &&
            Zcasecmp(p->nameSpace, nameSpace) == 0 &&
            Zcasecmp(p->className, className) == 0)
        {
            return p;
        }
    }

    /* Not found */
    return NULL;
}

/* returns ok or not-found; baseClass will be null if no base class exist */
MI_Result ProvReg_GetDirectBaseClass(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    const ZChar** baseClass)
{
    ProvRegClassInheritanceNode* classNode;
    ProvRegNamespaceNode* namespaceNode;

    /* clear out param */
    *baseClass = 0;

    /* check namespace */
    namespaceNode = _FindNamespace(self,nameSpace);

    if (!namespaceNode)
        return MI_RESULT_INVALID_NAMESPACE;

    /* find class */
    classNode = _FindClassNodeInTree(namespaceNode->tree, className);

    if (!classNode)
        return MI_RESULT_INVALID_CLASS;

    if (classNode->parent)
    {
        *baseClass = classNode->parent->cn;
    }

    return MI_RESULT_OK;
}

/* enumerates classes derived classes:
 - if deep == false and className == null, returns all root classes
 - if deep == true and className == null, returns all classes
 - if deep == false and className provided, returns all classes directly derived from given
 - if deep == true and className provided, returns all classes derived from given
*/
MI_Result ProvReg_BeginClasses(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    MI_Boolean deep,
    ProvRegPosition* pos)
{
    ProvRegNamespaceNode* namespaceNode;

    /* clear pos */
    memset( pos, 0, sizeof(*pos));
    pos->deep = deep;

    /* check namespace */
    namespaceNode = _FindNamespace(self,nameSpace);

    if (!namespaceNode)
        return MI_RESULT_INVALID_NAMESPACE;

    /* find class */
    if (className)
    {
        pos->start = _FindClassNodeInTree(namespaceNode->tree, className);

        if (!pos->start)
            return MI_RESULT_INVALID_CLASS;

        pos->current = pos->start->firstChild;
    }
    else
    {
        pos->start = 0;
        pos->current = namespaceNode->tree;
    }

    return MI_RESULT_OK;
}

MI_Result ProvReg_NextClass(
    ProvRegPosition* pos,
    const ZChar** className,
    MI_Boolean* done)
{
    if (!pos->current)
    {
        *className = 0;

        if (done)
            *done = MI_TRUE;

        return MI_RESULT_OK;
    }

    *className = pos->current->cn;

    if (pos->deep)
    {
        pos->current = _GetNextTreeNodeLimittedBy(pos->current,pos->start);
    }
    else
    {
        pos->current = pos->current->nextSibling;
    }

    if (done)
        *done = MI_FALSE;

    return MI_RESULT_OK;
}

MI_Result ProvReg_EndClasses(
    ProvRegPosition* pos)
{
    memset( pos, -1, sizeof(*pos));
    return MI_RESULT_OK;
}

/* returns enumerator to all registered association classes by given instance class
  and (optionally) assoc/result classes */
MI_EXPORT MI_Result ProvReg_BeginAssocClasses(
    ProvReg* self,
    const ZChar* nameSpace,
    const ZChar* className,
    const ZChar* assocClassName,  /* can be NULL */
    const ZChar* resultClassName, /* can be NULL */
    ProvRegAssocPosition* pos)
{
    ProvRegNamespaceNode* namespaceNode;

    if (!nameSpace || !className || !pos)
        return MI_RESULT_INVALID_PARAMETER;

    /* clear pos */
    memset( pos, 0, sizeof(*pos));

    /* check namespace */
    namespaceNode = _FindNamespace(self,nameSpace);

    if (!namespaceNode)
        return MI_RESULT_INVALID_NAMESPACE;

    /* find class */
    pos->currentLeft = _FindClassNodeInTree(namespaceNode->tree, className);

    if (!pos->currentLeft)
        return MI_RESULT_INVALID_CLASS;

    //pos->currentAssoc = pos->currentLeft->associatorClasses;

    /* validate optional parameters */
    if (assocClassName)
    {
        ProvRegClassInheritanceNode* assocClassNode = _FindClassNodeInTree(namespaceNode->tree, assocClassName);

        if (!assocClassNode)
            return MI_RESULT_INVALID_CLASS;

        /* store node pointer */
        pos->assocClass = assocClassNode;
    }

    if (resultClassName)
    {
        ProvRegClassInheritanceNode* resultClassNode = _FindClassNodeInTree(namespaceNode->tree, resultClassName);

        if (!resultClassNode)
            return MI_RESULT_INVALID_CLASS;

        /* store node pointer */
        pos->resultClass = resultClassNode;
    }

    return MI_RESULT_OK;
}

static MI_Boolean _GetNextAssoc(
    ProvRegAssocPosition* pos)
{
    /* check if we are at new node */
    if (!pos->currentAssoc || !pos->currentLeft)
    {
        /* find class with assoc link */
        while (pos->currentLeft && !pos->currentLeft->associatorClasses)
            pos->currentLeft = pos->currentLeft->parent;

        if (!pos->currentLeft)
            return MI_FALSE;

        pos->currentAssoc = pos->currentLeft->associatorClasses;
        return MI_TRUE;
    }

    pos->currentAssoc = pos->currentAssoc->next;

    if (pos->currentAssoc)
        return MI_TRUE;

    /* skip to parent */
    pos->currentLeft = pos->currentLeft->parent;
    return _GetNextAssoc(pos);
}

static MI_Boolean _IsNodeOrParentOf(
    ProvRegClassInheritanceNode* parent,
    ProvRegClassInheritanceNode* node)
{
    while (node)
    {
        if (node == parent)
            return MI_TRUE;

        node = node->parent;
    }
    return MI_FALSE;
}

MI_EXPORT MI_Result ProvReg_NextAssocClass(
    ProvRegAssocPosition* pos,
    const ZChar** className,
    MI_Boolean* done)
{
    /* navigate to next */
    if (pos->currentLeft == NULL)
    {
        if (done)
            *done = MI_TRUE;

        return MI_RESULT_OK;
    }

    while (_GetNextAssoc(pos))
    {
        /* check filters */
        if ( (!pos->assocClass || _IsNodeOrParentOf(pos->assocClass, pos->currentAssoc->assocClass))
            && (!pos->resultClass || _IsNodeOrParentOf(pos->resultClass,
                pos->currentAssoc->assocClass->left != pos->currentLeft ? pos->currentAssoc->assocClass->left : pos->currentAssoc->assocClass->right)
                || _IsNodeOrParentOf(
                pos->currentAssoc->assocClass->left != pos->currentLeft ? pos->currentAssoc->assocClass->left : pos->currentAssoc->assocClass->right,
                pos->resultClass)) )
        {
            *className = pos->currentAssoc->assocClass->cn;

            if (done)
                *done = MI_FALSE;

            return MI_RESULT_OK;
        }
    }

    if (done)
        *done = MI_TRUE;

    return MI_RESULT_OK;
}

MI_EXPORT MI_Result ProvReg_EndAssocClasses(
    ProvRegAssocPosition* pos)
{
    memset( pos, -1, sizeof(*pos));
    return MI_RESULT_OK;
}

