TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_httpclientcxx

SOURCES = \
    test_httpclientcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

# DEFINES = DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = httpclientcxx http protocol sock base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
