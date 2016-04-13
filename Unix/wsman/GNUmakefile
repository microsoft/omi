TOP = ..
include $(TOP)/config.mak

LIBRARY = wsman

SOURCES = \
    wsmanclient.c \
    wsman.c \
    wsmanparser.c \
    wsbuf.c \

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

PKGCONFIGPACKAGES = openssl

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )

wstags:
	$(BINDIR)/strhash wstags.txt
