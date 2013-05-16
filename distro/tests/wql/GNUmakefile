TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_wql

SOURCES = test_wql.cpp

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = wql base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
