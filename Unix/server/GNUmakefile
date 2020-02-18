TOP = ..
include $(TOP)/config.mak

##
## Note: on HPUX_PARISC_HP, the server must be linked as C++, since we have
## not found a way to dynamically load a C++ provider from a C program.
##

ifdef HPUX_PARISC_HP
  CXXPROGRAM = omiserver
  SOURCES = server.c servermaincxx.cpp servercommon.c
else
  CPROGRAM = omiserver
  SOURCES = server.c servermain.c servercommon.c
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = HOOK_BUILD MI_CONST=

LIBRARIES = wsman xmlserializer http protocol sock disp provreg provmgr $(MIAPILIB) wql base xml $(PALLIBS) $(INDIMGRLIB) omi_error $(INDICMNLIB) micodec mofparser

PKGCONFIGPACKAGES = openssl

ARGUMENTS=-i

include $(TOP)/mak/rules.mak

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
