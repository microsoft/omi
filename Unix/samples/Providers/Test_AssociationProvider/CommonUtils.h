#ifndef _CommonUtils_h
#define _CommonUtils_h

#include "Test_LogicalDisk.h"
#include "Test_PhysicalDisk.h"
#include "Test_VirtualDisk.h"
#include <vector>

void CreateVirtualDiskInstances(MI_Context* context, std::vector<Test_VirtualDisk*>& virtualStore);
void CreatePhysicalDiskInstances(MI_Context* context, std::vector<Test_PhysicalDisk*>& phyStore);
void CreateLogicalDiskInstances(MI_Context* context, std::vector<Test_LogicalDisk*>& logStore);

#endif
