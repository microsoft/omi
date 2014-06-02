TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_xmlcxx

SOURCES = test_xmlcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = xmlcxx ut base

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
