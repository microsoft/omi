TOP = ..
include $(TOP)/config.mak

LIBRARY = protocol

SOURCES = protocol.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

PKGCONFIGPACKAGES = openssl

LIBRARIES = sock base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
