TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_miapi

SOURCES = $(TOP)/ut/omitestcli.cpp $(TOP)/ut/omifaultsimtest.cpp main.cpp schema.c TestProtocolHandlerCache.cpp TestTransport.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = test_util xml base miapi protocol sock $(UNITTESTLIBS) pal omi_error wsman http xmlserializer base micodec mofparser

include $(TOP)/mak/rules.mak

DEFINES = DETECT_FORBIDDEN_FUNCTIONS TEST_BUILD

tests:
	$(call RUNUNITTEST)

vg:
	$(call RUNVALGRIND)
