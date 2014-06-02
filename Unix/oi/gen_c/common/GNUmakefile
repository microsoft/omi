TOP = ../../..
include $(TOP)/config.mak

ifeq ($(OS)-$(ARCH),HPUX-PARISC)
CXXSHLIBRARY = oicommon
else
LIBRARY = oicommon
endif

SOURCES = \
    OIParser.c \
    Syslog.c \
    FileGen.c \
    EmptyGen.c \

DEFINES = HOOK_BUILD

INCLUDES = $(TOP) $(TOP)/common 

LIBRARIES = pal

include $(TOP)/mak/rules.mak
