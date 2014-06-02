TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_sock

SOURCES = $(TOP)/ut/omitestcommon.cpp \
    $(TOP)/ut/omifaultsimtest.cpp \
    test_selector.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = omi_error wsman xmlserializer protocol sock base pal ut nits

DEFINES = TEST_BUILD

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
