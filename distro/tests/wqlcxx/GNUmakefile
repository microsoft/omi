TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_wqlcxx

SOURCES = \
    test_wqlcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = wqlcxx base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
