TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = Test_AssociationProvider

SOURCES = \
    module.c \
    schema.c \
    Test_AssociationLogicalVirtualDisk.cpp \
    Test_AssociationPhysicalLogicalDisk.cpp \
    Test_LogicalDisk.cpp \
    Test_PhysicalDisk.cpp \
    Test_VirtualDisk.cpp

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = Test_AssociationLogicalVirtualDisk Test_AssociationPhysicalLogicalDisk Test_LogicalDisk Test_PhysicalDisk Test_VirtualDisk

LIBRARIES = base $(PALLIBS)

gen:
	$(BINDIR)/omigen -f Test_AssociationProvider.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

regtest:
	$(BINDIR)/omireg -n root/cimomtestprov $(TARGET)
	$(BINDIR)/omireg -n root/cimomtestprov_oop -o @requestor@ $(TARGET)