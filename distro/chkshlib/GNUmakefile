TOP = ..
include $(TOP)/config.mak

$(shell mkdir -p $(OBJDIR)/base)

CXXPROGRAM = chkshlib

SOURCES = chkshlib.cpp ../base/lib.cpp ../base/strings.cpp ../base/clientft.cpp

INCLUDES = $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

x:

	echo $(OBJDIR)/base
