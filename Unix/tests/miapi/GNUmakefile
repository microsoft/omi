TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_miapi

SOURCES = $(TOP)/ut/omitestcli.cpp $(TOP)/ut/omifaultsimtest.cpp main.cpp schema.c TestProtocolHandlerCache.cpp TestTransport.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = test_util xml miapi protocol sock $(UNITTESTLIBS) omi_error wsman http base pal xmlserializer xml base micodec mofparser

include $(TOP)/mak/rules.mak

DEFINES = TEST_BUILD

tests:
	$(call RUNUNITTEST)

vg:
	$(call RUNVALGRIND)
