##==============================================================================
##
## Phony targets.
##
##==============================================================================

.PHONY: gen all clean depend memcheck cachegrind proj

##==============================================================================
##
## UNITTEST
##
##==============================================================================

ifdef CXXUNITTEST
    ifdef ENABLE_NITS
        CXXSHLIBRARY=$(CXXUNITTEST)
    else
        CXXPROGRAM=$(CXXUNITTEST)
    endif
endif

ifdef CUNITTEST
    ifdef ENABLE_NITS
        CSHLIBRARY=$(CUNITTEST)
    else
        CPROGRAM=$(CUNITTEST)
    endif
endif

ifdef ENABLE_NITS
    UNITTESTLIBS = ut io nits
else
    UNITTESTLIBS = ut io
endif

ifdef ENABLE_NITS
    RUNUNITTEST = $(BINDIR)/nits $(TARGET)
else
    RUNUNITTEST = $(TARGET) $(TESTOPTS)
endif

ifdef ENABLE_NITS
    RUNUNITTESTWITHTRACE = $(BINDIR)/nits -trace:verbose $(TARGET)
else
    RUNUNITTESTWITHTRACE = $(TARGET) $(TESTOPTS)
endif

ifdef ENABLE_NITS
    RUNVALGRIND=valgrind --tool=memcheck $(BINDIR)/nits $(TARGET)
else
    RUNVALGRIND=valgrind --tool=memcheck $(TARGET)
endif

##==============================================================================
##
## OpenSSL
##
## OPENSSL_CFLAGS, OPENSSL_LIBS and OPENSSL_LIBDIR describe things on the
## development computer. OPENSSL_STD_LIBDIR describes a location on the target
## computer.
##
##==============================================================================

ifdef CONFIG_TOOLCHAIN
    OPENSSL_CFLAGS=-I$(CONFIG_TOOLCHAIN)/usr/include
    OPENSSL_LIBDIR=$(CONFIG_TOOLCHAIN)/usr/lib
    OPENSSL_LIBS=-L$(OPENSSL_LIBDIR) -lssl -lcrypto
    OPENSSL_STD_LIBDIR=$(OPENSSL_LIBDIR)
    export LD_LIBRARY_PATH=$(CONFIG_TOOLCHAIN)/lib:$(CONFIG_TOOLCHAIN)/usr/lib
else
  ifndef OPENSSL_CFLAGS
    OPENSSL_CFLAGS=$(shell $(PKGCONFIG) --cflags openssl)
  endif
  ifndef OPENSSL_LIBDIR
    OPENSSL_LIBDIR=$(shell $(PKGCONFIG) --variable=libdir openssl)
  endif
  ifndef OPENSSL_LIBS
    OPENSSL_LIBS=$(shell $(PKGCONFIG) --libs openssl)
  endif
  OPENSSL_STD_LIBDIR=$(shell $(PKGCONFIG) --variable=libdir openssl)
endif

##==============================================================================
##
## OBJDIRPATH -- resolve directory where objects will go.
##
##==============================================================================

OBJDIRPATH=$(OBJDIR)$(subst $(ROOT),,$(CURDIR))

ifeq ($(subst $(ROOT),,$(CURDIR)), $(ROOT))
  $(error "current directory seems to be a symbolic link")
endif

##==============================================================================
##
## Obtain build flags with 'buildtool'.
##
##==============================================================================

BUILDTOOL=$(ROOT)/buildtool

CC=$(shell $(BUILDTOOL) cc)

CXX=$(shell $(BUILDTOOL) cxx)

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

CFLAGS=$(shell $(BUILDTOOL) cflags $(__OPTS))
CFLAGS+=$(OPENSSL_CFLAGS)

CXXFLAGS=$(shell $(BUILDTOOL) cxxflags $(__OPTS))
CXXFLAGS+=$(OPENSSL_CFLAGS)

ifdef DISABLE_LIBPATH
  LIBPATHFLAGS=
else
  ifdef DISABLE_OMI_LIBPATH
      LIBPATHFLAGS=-L$(OPENSSL_STD_LIBDIR)
  else
    LIBPATHFLAGS=-L$(shell $(BUILDTOOL) libpath $(CONFIG_LIBDIR)) -L$(OPENSSL_STD_LIBDIR)
  endif
endif

CSHLIBFLAGS=$(shell $(BUILDTOOL) cshlibflags)
CSHLIBFLAGS+=-L$(OPENSSL_LIBDIR)
CSHLIBFLAGS+=$(LIBPATHFLAGS)
CSHLIBFLAGS+=$(OPENSSL_LIBS)
CSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)

CXXSHLIBFLAGS=$(shell $(BUILDTOOL) cxxshlibflags)
CXXSHLIBFLAGS+=-L$(OPENSSL_LIBDIR)
CXXSHLIBFLAGS+=$(LIBPATHFLAGS)
CXXSHLIBFLAGS+=$(OPENSSL_LIBS)
CXXSHLIBFLAGS+=$(shell $(BUILDTOOL) syslibs)

CPROGFLAGS=$(shell $(BUILDTOOL) cprogflags)
CPROGFLAGS+=-L$(OPENSSL_LIBDIR)
CPROGFLAGS+=$(LIBPATHFLAGS)
CPROGFLAGS+=$(OPENSSL_LIBS)
CPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)

CXXPROGFLAGS=$(shell $(BUILDTOOL) cxxprogflags)
CXXPROGFLAGS+=-L$(OPENSSL_LIBDIR)
CXXPROGFLAGS+=$(LIBPATHFLAGS)
CXXPROGFLAGS+=$(OPENSSL_LIBS)
CXXPROGFLAGS+=$(shell $(BUILDTOOL) syslibs)

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
	ar r $(TARGET) $(__OBJECTS)
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
  ifndef DISABLE_OMI_LIBPATH
    LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CSHLIBRARY)))
  endif
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CC) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(__LIBRARIES) $(CSHLIBFLAGS) $(LIBNAMEOPT)
	@ echo

chkshlib:
	$(BINDIR)/chkshlib $(TARGET)

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
  ifndef DISABLE_OMI_LIBPATH
    LIBNAMEOPT=$(shell $(BUILDTOOL) libname $(CONFIG_LIBDIR)/$(shell $(BUILDTOOL) shlibname $(CXXSHLIBRARY)))
  endif
endif

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(__LIBRARIES) $(CXXSHLIBFLAGS) $(LIBNAMEOPT)

# @ ( $(BINDIR)/chkshlib $(TARGET) || ( rm -rf $(TARGET) && false ) )

chkshlib:
	$(BINDIR)/chkshlib $(TARGET)

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
	$(CC) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(__LIBRARIES) $(CPROGFLAGS)
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
	$(CXX) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(__LIBRARIES) $(CXXPROGFLAGS)
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
