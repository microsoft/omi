TOP = ..
include $(TOP)/config.mak

##
## Note: on HPUX_PARISC_HP, the server must be linked as C++, since we have
## not found a way to dynamically load a C++ provider from a C program.
##

ifdef HPUX_PARISC_HP
  CXXPROGRAM = omiserver
  SOURCES = server.c servermaincxx.cpp
else
  CPROGRAM = omiserver
  SOURCES = server.c servermain.c
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = wsman http protocol sock disp provreg provmgr wql base xml io

PKGCONFIGPACKAGES = openssl

ARGUMENTS=-i

include $(TOP)/mak/rules.mak

# Support for purify of server libraries

ifeq ($(ENABLE_PURIFY_SERVER),1)

PUREOPTIONS = -follow-child-processes=yes -locking=no \
    -always-use-cache-dir -cache-dir=$(PURIFY_TMP)/cache
PURIFY_WRAPPER = $(PURIFY_HOME)/purify $(PUREOPTIONS)
# May need library: $(PURIFY_HOME)/libpurify_stubs.a

CC:=$(PURIFY_WRAPPER) $(CC)

endif

tests:
	$(TARGET)

#valgrind --tool=cachegrind --cachegrind-out-file=callgrind.out
#
#cachegrind:
#        $(CACHEGRIND) --cachegrind-out-file=callgrind.out $(TARGET) $(ARGUMENTS) $(MEMCHECK_ARGS)
#                cg_annotate --auto=yes callgrind.out > cg_annotate.out
#                        rm -f callgrind.out
#                                @ echo "Created cg_annotate.out"
##
