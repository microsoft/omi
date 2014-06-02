TOP = ..
include $(TOP)/config.mak

LIBRARY = http

SOURCES = \
    httpcommon.c \
    http.c \
    httpclient.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

PKGCONFIGPACKAGES = openssl

LIBRARIES = protocol sock base $(PALLIBS)

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
