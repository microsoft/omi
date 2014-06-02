TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = posthttp

SOURCES = posthttp.cpp

DEFINES = HOOK_BUILD

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = protocol $(BASELIBS) ut $(PALLIBS)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) test.xml

print:
	$(BINDIR)/printxml test.xml
