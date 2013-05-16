TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_http

SOURCES = \
    test_http.cpp \
    test_httpclient.cpp

INCLUDES = $(TOP) $(TOP)/common

# DEFINES = DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = http protocol sock base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
