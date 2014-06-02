TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_micxx

SOURCES = $(TOP)/ut/omitestcommon.cpp \
    $(TOP)/ut/omifaultsimtest.cpp \
    $(TOP)/tests/base/schema.c \
    test_array.cpp \
    test_datetime.cpp  \
    test_micxx.cpp \
    test_string.cpp

INCLUDES = $(TOP) $(TOP)/common $(TOP)/tests/base

DEFINES = TEST_BUILD

LIBRARIES = micxx omi_error wsman xmlserializer protocol sock base pal nits

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
