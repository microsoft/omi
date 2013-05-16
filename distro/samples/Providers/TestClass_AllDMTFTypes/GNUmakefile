TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = TestClass_AllDMTFTypes

SOURCES = \
    module.c \
    TestClass_AllDMTFTypes.cpp \
    TestClass_ForEmbedded.c \
    schema.c 
	


INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = TestClass_AllDMTFTypes=TestClass_AllDMTFTypes TestClass_ForEmbedded=TestClass_ForEmbedded

LIBRARIES = base io

gen:
	$(BINDIR)/omigen -f InstanceProvider_Properties.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test-c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test-c/"

localreg:
	$(BINDIR)/omireg -n root/omi $(TARGET)
