.PHONY: gen3
TOP = ..
include $(TOP)/config.mak

LIBRARY = omi_error

SOURCES = schema.c omierror.c errorutil.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

include $(TOP)/mak/rules.mak

gen:
	chmod +w *.c *.h
	$(BINDIR)/omigen -n -s errorSchemaDecl schema.mof OMI_Error

help:
	$(BINDIR)/omigen --help > HELP
