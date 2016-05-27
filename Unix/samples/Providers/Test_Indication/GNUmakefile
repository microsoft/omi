TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = TestIndication

SOURCES = \
    module.c \
    fire.c \
    impl.c \
    Test_Indication.c \
    L_Indication.c \
    L_IndicationC1.c \
    L_IndicationC2.c \
    L_IndicationC3.c \
    R_IndicationC1.c \
    R_IndicationC2.c \
    R_IndicationC3.c \
    L_Lifecycle.c \
    L_LifecycleC1.c \
    L_LifecycleC2.c \
    R_Lifecycle.c \
    R_LifecycleC1.c \
    R_LifecycleC2.c \
    Test_Class.c \
    Test_IndicationConfig.c \
    schema.c \

INCLUDES = $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak

DEFINES = HOOK_BUILD MI_API_VERSION=2

LIBRARIES = test_util miapi protocol sock wql base $(PALLIBS) omi_error wsman xmlserializer xml base micodec mofparser

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================
CLASSES = Test_IndicationConfig Test_Indication L_IndicationC1 L_IndicationC2 L_IndicationC3 R_IndicationC1 R_IndicationC2 R_IndicationC3

gen:
	$(BINDIR)/omigen -f testindication.mof $(CLASSES)

##==============================================================================
##
## Register
##
##==============================================================================
reg:
	$(BINDIR)/omireg -n root/cimv2 $(TARGET)

regoop:
	$(BINDIR)/omireg -n oop/requestor/indication -o @requestor@ $(TARGET)

regtest:
	$(BINDIR)/omireg -n root/cimomtestprov $(TARGET)
	$(BINDIR)/omireg -n root/cimomtestprov_oop -o @requestor@ $(TARGET)
	
##==============================================================================
##
## dep -- rule to build dependent libraries.
##
##==============================================================================
dep:
	( cd ../../../tests/util; $(MAKE); )
