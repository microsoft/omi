TOP = ..
include $(TOP)/config.mak

LIBRARY = http

SOURCES = \
    http.c \
    httpclient.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

PKGCONFIGPACKAGES = openssl

LIBRARIES = protocol sock base io

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )
