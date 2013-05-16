TOP = ..
include $(TOP)/config.mak

LIBRARY = sock

SOURCES = \
    addr.c \
    selector.c \
    sock.c \
    thread.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

PKGCONFIGPACKAGES = openssl

LIBRARIES = base

include $(TOP)/mak/rules.mak
