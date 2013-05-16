TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_xml

SOURCES = test_xml.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = xml base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)

vg:
	valgrind --tool=memcheck $(TARGET)
