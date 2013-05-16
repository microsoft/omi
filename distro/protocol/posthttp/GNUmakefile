TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = posthttp

SOURCES = posthttp.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = protocol sock base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) test.xml

print:
	$(BINDIR)/printxml test.xml
