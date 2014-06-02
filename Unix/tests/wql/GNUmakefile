TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_wql

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_wql.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS TEST_BUILD

LIBRARIES = omi_error wsman xmlserializer protocol sock wql base pal ut nits

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
