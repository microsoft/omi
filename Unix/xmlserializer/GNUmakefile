TOP = ..
include $(TOP)/config.mak

LIBRARY = xmlserializer

SOURCES = \
	xmlserializer.c xmldeserializer.c XmlDom.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

PKGCONFIGPACKAGES = openssl

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )

wstags:
	$(BINDIR)/strhash wstags.txt
