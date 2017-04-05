TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_pal

$(shell mkdir -p $(OBJDIR)/unittest)

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_pal.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = omi_error wsman http xmlserializer xml protocol sock ut base pal nits

ifeq ($(OS),DARWIN)
    SYSLIBRARIES = 
else
    SYSLIBRARIES = rt
endif

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

