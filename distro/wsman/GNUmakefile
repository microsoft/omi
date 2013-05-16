TOP = ..
include $(TOP)/config.mak

LIBRARY = wsman

SOURCES = \
    wsman.c \
    wsmanparser.c \
    wsbuf.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

PKGCONFIGPACKAGES = openssl

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )

wstags:
	$(BINDIR)/strhash wstags.txt
