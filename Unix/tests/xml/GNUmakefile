TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_xml

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_xml.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = omi_error wsman xmlserializer protocol sock xml ut base pal nits

DEFINES = TEST_BUILD

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

vg:
	$(call RUNVALGRIND)
