TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_io

SOURCES = test_io.cpp $(TOP)/base/clientft.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)

vg:
	valgrind --tool=memcheck $(TARGET)
