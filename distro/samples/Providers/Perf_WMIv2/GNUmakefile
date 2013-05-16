TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = Perf_WMIv2

SOURCES = \
    module.c \
    schema.c \
    PerfAssocClass.cpp \
    Perf_Embedded.cpp \
    Perf_Indication.cpp \
    Perf_NoPsSemantics.cpp \
    Perf_WithPsSemantics.cpp \
    ProviderUtil.cpp

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = PerfAssocClass=PerfAssocClass Perf_Embedded=Perf_Embedded Perf_Indication=Perf_Indication Perf_NoPsSemantics=Perf_NoPsSemantics Perf_WithPsSemantics=Perf_WithPsSemantics

LIBRARIES = base

gen:
	$(BINDIR)/omigen -f PerfTestsV2.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

ei:
	$(BINDIR)/omicli ei root/cimv2 Perf_NoPsSemantics

localreg:
	$(BINDIR)/omireg -n root/cimv2 $(TARGET)
