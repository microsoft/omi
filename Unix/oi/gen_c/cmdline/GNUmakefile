TOP = ../../..
include $(TOP)/config.mak

##
## Note: on HPUX_PARISC_HP, the server must be linked as C++, since we have
## not found a way to dynamically load a C++ provider from a C program.
##

ifdef HPUX_PARISC_HP
  CXXPROGRAM = oigenc
  SOURCES = main.c
else
  CPROGRAM = oigenc
  SOURCES = main.c
endif

DEFINES = HOOK_BUILD

INCLUDES = $(TOP) $(TOP)/common $(TOP)/oi/gen_c/common

LIBRARIES = oicommon $(PALLIBS)

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
