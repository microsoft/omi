TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_mofcxx

SOURCES = test_mofcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = mofcxx ut base

MEMCHECK_ARGS = sample.mof

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
