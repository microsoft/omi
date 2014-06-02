TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = TestClass_AllDMTFArrays

SOURCES = \
    module.c \
    TestClass_AllDMTFArrays.cpp \
    TestClass_ForEmbedded.cpp \
    schema.c 
	


INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = TestClass_AllDMTFArrays=TestClass_AllDMTFArrays TestClass_ForEmbedded=TestClass_ForEmbedded

LIBRARIES = base $(PALLIBS)

gen:
	$(BINDIR)/omigen -f InstanceProvider_Properties.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

regtest:
	$(BINDIR)/omireg -n root/cimomtestprov $(TARGET)
	$(BINDIR)/omireg -n root/cimomtestprov_oop -o @requestor@ $(TARGET)