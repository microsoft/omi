TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_mof

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_mof.cpp

INCLUDES = $(TOP) $(TOP)/mof $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = omi_error wsman xmlserializer protocol sock mof ut base pal nits

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
