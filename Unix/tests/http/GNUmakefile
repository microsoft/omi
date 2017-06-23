TOP = ../..
include $(TOP)/config.mak

CXXUNITTEST = test_http

SOURCES = $(TOP)/ut/omitestcommon.cpp \
    $(TOP)/ut/omifaultsimtest.cpp \
    test_http.cpp \
    test_httpclient.cpp \

INCLUDES = $(TOP) $(TOP)/common

DEFINES = TEST_BUILD

LIBRARIES = http protocol sock base mi $(UNITTESTLIBS) pal omi_error wsman xmlserializer base

include $(TOP)/mak/rules.mak

tests:
	$(call RUNUNITTEST)
