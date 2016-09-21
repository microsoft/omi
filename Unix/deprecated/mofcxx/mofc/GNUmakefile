TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = mofc

SOURCES = mofc.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = mofcxx base

MEMCHECK_ARGS = sample.mof

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
