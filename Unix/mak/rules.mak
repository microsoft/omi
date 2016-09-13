##==============================================================================
##
## Phony targets.
##
##==============================================================================

.PHONY: gen all clean depend memcheck cachegrind proj

##==============================================================================
##
## DEVBUILD
##
##==============================================================================

ifeq ($(CONFIG_PREFIX),$(ROOT))
    DEVBUILD=1
endif

##==============================================================================
##
## UNITTEST
##
##==============================================================================

ifdef CXXUNITTEST
    CXXSHLIBRARY=$(CXXUNITTEST)
endif

ifdef CUNITTEST
    CSHLIBRARY=$(CUNITTEST)
endif

ifdef DISABLE_LOCALSESSION
else
    MIAPILIB = miapi
endif

ifndef DISABLE_INDICATION
    INDIMGRLIB = indimgr
    INDICMNLIB = indicmn
endif

PALLIBS = pal

BASELIBS = sock base

UNITTESTLIBS = ut nits pal base

NITS_COMMAND_OPTIONS=

ifdef ENABLE_FAULTINJECTION
    NITS_COMMAND_OPTIONS += -install
endif

NITS_COMMAND_OPTIONS += -reset -target:*libtest_ +loglevel:3

RUNUNITTEST = $(BINDIR)/nits $(NITS_COMMAND_OPTIONS) $(TARGET)

RUNUNITTESTWITHTRACE = $(BINDIR)/nits $(NITS_COMMAND_OPTIONS) -trace:verbose $(TARGET)

RUNVALGRIND=valgrind --tool=memcheck $(BINDIR)/nits $(TARGET)

##==============================================================================
##
## OpenSSL
##
##==============================================================================

OPENSSL_CFLAGS=$(OPENSSLCFLAGS)

ifdef OPENSSLLIBS
    OPENSSL_LIBS=$(OPENSSLLIBS)
else
    OPENSSL_LIBS=-lssl -lcrypto
endif

OPENSSL_LIBDIR=$(OPENSSLLIBDIR)
ifeq ($(OPENSSLLIBDIR),"")
  OPENSSL_LIBOPT:=
else
  OPENSSL_LIBOPT:=-L$(OPENSSLLIBDIR)
endif

##==============================================================================
##
## OBJDIRPATH -- resolve directory where objects will go.
##
##==============================================================================

ifdef OBJDIRBASE
    OBJDIRPATH=$(OBJDIR)/$(OBJDIRBASE)
else
    OBJDIRPATH=$(OBJDIR)$(subst $(ROOT),,$(CURDIR))
endif

ifeq ($(subst $(ROOT),,$(CURDIR)), $(ROOT))
  $(error "current directory seems to be a symbolic link")
endif

##==============================================================================
##
## Obtain build flags with 'buildtool'.
##
##==============================================================================

BUILDTOOL=$(ROOT)/buildtool

CC=$(WITH_CC)

CXX=$(WITH_CXX)

AR=$(WITH_AR)

__OPTS=

ifeq ($(ENABLE_DEBUG),1)
  __OPTS += --debug
endif

ifeq ($(ENABLE_WERROR),1)
  __OPTS += --errwarn
endif

ifeq ($(CONFIG_FAVORSIZE),1)
  __OPTS += --size
endif

__OPTS += --pic

ifeq ($(CSHLIBRARY),pal)
  __OPTS += --pal
endif

CFLAGS=$(shell $(BUILDTOOL) cflags $(__OPTS))
CFLAGS+=$(OPENSSL_CFLAGS)

CXXFLAGS=$(shell $(BUILDTOOL) cxxflags $(__OPTS))
CXXFLAGS+=$(OPENSSL_CFLAGS)

ifdef DISABLE_LIBPATH
  LIBPATHFLAGS:=
else
  LIBPATHFLAGS=$(shell $(BUILDTOOL) libpath $(CONFIG_LIBDIR) $(OPENSSL_LIBDIR))
endif

ifdef EXPORTS
EXPORTFLAGS=$(shell $(BUILDTOOL) exports $(EXPORTS))
else
EXPORTFLAGS=
endif

__CSHLIBOPTS=
ifeq ($(CSHLIBRARY),pal)
  __CSHLIBOPTS += --pal
endif

CSHLIBFLAGS=$(shell $(BUILDTOOL) cshlibflags $(__CSHLIBOPTS))
CSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)
CSHLIBFLAGS+=$(OPENSSL_LIBS)
CSHLIBFLAGS+=$(EXPORTFLAGS)
CSHLIBFLAGS+=$(LIBPATHFLAGS)

CXXSHLIBFLAGS=$(shell $(BUILDTOOL) cxxshlibflags)
CXXSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)
CXXSHLIBFLAGS+=$(OPENSSL_LIBS)
CXXSHLIBFLAGS+=$(EXPORTFLAGS)
CXXSHLIBFLAGS+=$(LIBPATHFLAGS)

CPROGFLAGS=$(shell $(BUILDTOOL) cprogflags)
CPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)
CPROGFLAGS+=$(OPENSSL_LIBS)
CPROGFLAGS+=$(LIBPATHFLAGS)

CXXPROGFLAGS=$(shell $(BUILDTOOL) cxxprogflags)
CXXPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)
CXXPROGFLAGS+=$(OPENSSL_LIBS)
CXXPROGFLAGS+=$(LIBPATHFLAGS)

ifdef ENABLE_32BIT
  CFLAGS+=-m32
  CPROGFLAGS+=-m32
  CSHLIBFLAGS+=-m32
  CXXFLAGS+=-m32
  CXXPROGFLAGS+=-m32
  CXXSHLIBFLAGS+=-m32
endif

ifdef ENABLE_SECTIONS
  CFLAGS+=-ffunction-sections -fdata-sections
  CPROGFLAGS+=-Wl,--gc-sections
  CSHLIBFLAGS+=-Wl,--gc-sections
  CXXFLAGS+=-ffunction-sections -fdata-sections
  CXXPROGFLAGS+=-Wl,--gc-sections 
  CXXSHLIBFLAGS+=-Wl,--gc-sections
  #PRINT_UNUSED_SECTIONS=1
  ifdef PRINT_UNUSED_SECTIONS
    CPROGFLAGS+=-Wl,--print-gc-sections
  endif
endif

##==============================================================================
##
## OBJECTS:
##
##==============================================================================

__TMP = $(SOURCES:.c=.o)
__TMP2 = $(__TMP:.s=.o)
OBJECTS = $(__TMP2:.cpp=.o)
__OBJECTS = $(addprefix $(OBJDIRPATH)/,$(OBJECTS))

##==============================================================================
##
## LIBRARY target
##
##==============================================================================

ifdef LIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(LIBDIR)/lib$(LIBRARY).a

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(AR) r $(TARGET) $(__OBJECTS)
	@ echo

# ranlib $(TARGET)

endif

##==============================================================================
##
## CSHLIBRARY target
##
##==============================================================================

ifdef CSHLIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CSHLIBRARY))

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))

ifndef DISABLE_LIBPATH
LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CSHLIBRARY)))
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CC) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(OPENSSL_LIBOPT) $(__LIBRARIES) $(CSHLIBFLAGS) $(LIBNAMEOPT) 
ifdef DEVBUILD
ifndef SUPPRESS_CHKSHLIB
	sudo $(BINDIR)/chkshlib $(TARGET) || ( rm -rf $(TARGET) && false )
endif
endif
	@ echo "Created $(TARGET)"

endif

##==============================================================================
##
## CXXSHLIBRARY target
##
##==============================================================================

ifdef CXXSHLIBRARY

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CXXSHLIBRARY))

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))

ifndef DISABLE_LIBPATH
LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CXXSHLIBRARY)))
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(OPENSSL_LIBOPT) $(__LIBRARIES) $(CXXSHLIBFLAGS) $(LIBNAMEOPT)
ifdef DEVBUILD
ifndef SUPPRESS_CHKSHLIB
	sudo $(BINDIR)/chkshlib $(TARGET) || ( rm -rf $(TARGET) && false )
endif
endif
	@ echo "Created $(TARGET)"

endif

##==============================================================================
##
## CPROGRAM target
##
##==============================================================================

ifdef CPROGRAM

FOUND = 1

$(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(BINDIR)/$(CPROGRAM)

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))
__DEPS=$(wildcard $(addprefix $(LIBDIR)/lib,$(addsuffix .*,$(LIBRARIES))))

$(TARGET): $(__OBJECTS) $(__DEPS)
	mkdir -p $(BINDIR)
	$(CC) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(OPENSSL_LIBOPT) $(__LIBRARIES) $(__LIBRARIES) $(CPROGFLAGS)
	@ echo

endif

##==============================================================================
##
## CXXPROGRAM target
##
##==============================================================================

ifdef CXXPROGRAM

FOUND = 1

    $(shell mkdir -p $(OBJDIRPATH))

ifndef TOP
    $(error "Please define TOP variable")
endif

ifndef SOURCES
    $(error "Please define SOURCES variable")
endif

TARGET = $(BINDIR)/$(CXXPROGRAM)

__LIBRARIES = $(addprefix -l,$(LIBRARIES))
__LIBRARIES += $(addprefix -l,$(SYSLIBRARIES))
__DEPS=$(wildcard $(addprefix $(LIBDIR)/lib,$(addsuffix .*,$(LIBRARIES))))

all: $(TARGET) $(EXTRA_RULE)

$(TARGET): $(__OBJECTS) $(__DEPS)
	mkdir -p $(BINDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(OPENSSL_LIBOPT) $(__LIBRARIES) $(__LIBRARIES) $(CXXPROGFLAGS)
	@ echo

endif

##==============================================================================
##
## DIRECTORIES target
##
##==============================================================================

ifdef DIRECTORIES

FOUND = 1

# define a newline macro
define NL


endef

all:
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i $(NL) )

clean:
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i clean $(NL) )

depend:
	@ $(foreach i, $(DIRECTORIES), $(MAKE) -C $i depend $(NL) )

endif

##==============================================================================
##
## Check that one of the targets above was defined
##
##==============================================================================

ifndef FOUND

TARGETS = \
    LIBRARY \
    LIBDIR \
    CSHLIBRARY \
    CXXSHLIBRARY \
    CPROGRAM \
    CXXPROGRAM \
    DIRECTORIES

$(error "Please define one of the following targets: $(TARGETS)")

endif

##==============================================================================
##
## USECCACHE
##
##==============================================================================

ifdef USECCACHE
    CWRAP=ccache
    CXXWRAP=$(CWRAP)
endif

##==============================================================================
##
## Object file targets
##
##==============================================================================

__INCLUDES = -I$(INCDIR) $(addprefix -I,$(INCLUDES))
__DEFINES = $(addprefix -D,$(DEFINES))

compilec = \
    $(CWRAP) $(CC) -c -o $@ $(CFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

compilecxx = \
    $(CXXWRAP) $(CXX) -c -o $@ $(CXXFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

compiles = \
    $(CC) -c -o $@ $(CFLAGS) $(__INCLUDES) $(__DEFINES) $(1) $(2)

$(OBJDIRPATH)/%.o: %.c
	$(call compilec,$<)
	@ echo

$(OBJDIRPATH)/%.o: %.cpp
	$(call compilecxx,$<)
	@ echo

$(OBJDIRPATH)/%.o: %.s
	$(call compiles,$<)
	@ echo

##==============================================================================
##
## clean target
##
##==============================================================================

ifndef DIRECTORIES
clean:
	rm -rf $(TARGET) $(__OBJECTS) $(OBJDIRPATH)/depend.mak $(CLEANFILES)
endif

##==============================================================================
##
## depend target
##
##==============================================================================

MKDEP=$(BINDIR)/mkdep

ifndef DIRECTORIES
depend: $(BINDIR)/mkdep
	$(MKDEP) --objdir $(OBJDIRPATH) $(__INCLUDES) $(SOURCES) > $(OBJDIRPATH)/depend.mak
endif

# Only build if we are not in the mkdep source directory.
ifndef MAKEDEPSRCDIR
$(BINDIR)/mkdep:
	$(MAKE) -C $(ROOT)/tools/mkdep
endif

##==============================================================================
##
## memcheck target
##
##==============================================================================

MEMCHECK=valgrind --tool=memcheck --leak-check=full --error-exitcode=1 --gen-suppressions=all --track-fds=yes

## --trace-children=yes

ifdef MEMCHECK_SUPPRESS
  __MEMCHECK_SUPPRESS = --suppressions=$(MEMCHECK_SUPPRESS)
endif

memcheck:
	$(MEMCHECK) $(__MEMCHECK_SUPPRESS) $(TARGET) $(MEMCHECK_ARGS)

##==============================================================================
##
## cachegrind target
##
##==============================================================================

CACHEGRIND=valgrind --tool=cachegrind

cachegrind:
	rm -f cachegrind.out*
	valgrind --trace-children=yes --tool=cachegrind $(CACHEGRIND_ARGS)
	cg_annotate --auto=yes cachegrind.out.* > cg_annotate.out
	rm -f cachegrind.out*
	@ echo "Created cg_annotate.out"

##==============================================================================
##
## Include depend.mak
##
##==============================================================================

-include $(OBJDIRPATH)/depend.mak

##==============================================================================
##
## Flags passed to test programs
##
##==============================================================================

ifndef TESTOPTS
export TESTOPTS=-p
endif
