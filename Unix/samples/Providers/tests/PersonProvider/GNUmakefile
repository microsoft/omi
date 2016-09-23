TOP = ../../../..
include $(TOP)/config.mak

CXXUNITTEST = test_PersonProvider

SOURCES = $(TOP)/ut/omitestcommon.cpp test_PersonProvider.cpp

INCLUDES = $(TOP) $(TOP)/common 

LIBRARIES = omi_error wsman http xmlserializer xml protocol sock base pal nits

DEFINES = TEST_BUILD

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
