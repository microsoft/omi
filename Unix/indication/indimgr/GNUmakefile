TOP = ../..
include $(TOP)/config.mak

LIBRARY = indimgr

SOURCES = \
	cimbase.c \
	filter.c \
	filtercol.c \
	listener.c \
	mgr.c \
	mgrstrand.c \
	subscrip.c \
	classlist.c \
	host.c \

INCLUDES = $(TOP) $(TOP)/common $(TOP)/pal $(TOP)/nits/base 

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS HOOK_BUILD

include $(TOP)/mak/rules.mak
