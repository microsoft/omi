TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = omigenall

SOURCES = $(wildcard *.c)

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = base

CLEANFILES=$(SOURCES)

include $(TOP)/mak/rules.mak

GENOPTS = -l -D -M -V -S -A

gen:
	$(BINDIR)/omigen $(GENOPTS) -a schema.mof

CLEANFILES = $(wildcard *.h) $(wildcard *.c)
