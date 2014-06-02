TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_oi

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp test_oi.cpp

INCLUDES = $(TOP) $(TOP)/common $(TOP)/oi/gen_c/common

LIBRARIES = omi_error wsman xmlserializer xml protocol sock oicommon ut base pal nits

DEFINES = TEST_BUILD

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)

vg:
	$(call RUNVALGRIND)
