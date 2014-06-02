TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_pal

$(shell mkdir -p $(OBJDIR)/unittest)

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_pal.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS TEST_BUILD

LIBRARIES = omi_error wsman xmlserializer xml protocol sock ut base pal nits

SYSLIBRARIES = rt

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

