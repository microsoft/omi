TOP = ../../..
include $(TOP)/config.mak

LIBRARY = mofparser

SOURCES = \
	buffer.c \
	moflex.c \
	ptrarray.c \
	types.c \
	utility.c \
	mofparser.c \
	mofyacc.c \
	mofhash.c 

INCLUDES = $(TOP)/common  $(TOP) $(TOP) $(TOP)/codec/common $(TOP)/nits/base 

ifeq ($(ENABLE_DEBUG),1)
ENABLE_DEBUG_DEFINE = ENABLE_DEBUG
endif

DEFINES = MI_CONST= $(ENABLE_DEBUG_DEFINE)

include $(TOP)/mak/rules.mak


