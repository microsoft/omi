TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_strhash

SOURCES = test_strhash.cpp $(TOP)/base/clientft.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
