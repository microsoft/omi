TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_provreg

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_provreg.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = omi_error wsman xmlserializer protocol sock provreg ut base pal nits

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
