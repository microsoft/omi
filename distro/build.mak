.PHONY: world
.PHONY: check
.PHONY: install
.PHONY: server
.PHONY: tests

ifndef OUTPUTDIR
$(error OUTPUTDIR is undefined)
endif

include $(OUTPUTDIR)/config.mak

TOP=.

##==============================================================================
##
## Export CONFIG_TARGET (buildtool uses it)
##
##==============================================================================

export CONFIG_TARGET

##==============================================================================
##
## WORLD -- the 'WORLD" variable indicates that we are building for test
## (./cofigure-world).
##
##==============================================================================

ifeq ($(CONFIG_PREFIX),$(CONFIGUREDIR))
    WORLD=1
endif

##==============================================================================
##
## Build tests:
##
##==============================================================================

ifdef WORLD
    BUILD_TESTS=1
endif

##==============================================================================
##
## rules targets:
##
##==============================================================================

DIRECTORIES =
DIRECTORIES += chkshlib
DIRECTORIES += tools

ifdef ENABLE_NITS
  DIRECTORIES += nits
endif

DIRECTORIES += io
DIRECTORIES += base
DIRECTORIES += ut
DIRECTORIES += strhash
DIRECTORIES += mof
DIRECTORIES += mofcxx
DIRECTORIES += wql
DIRECTORIES += wqlcxx
DIRECTORIES += gen
DIRECTORIES += provreg
DIRECTORIES += provmgr
DIRECTORIES += disp
DIRECTORIES += micxx
DIRECTORIES += sock
DIRECTORIES += protocol
DIRECTORIES += http
DIRECTORIES += httpclientcxx
DIRECTORIES += wsman
DIRECTORIES += protocol/posthttp
DIRECTORIES += xml
DIRECTORIES += xml/chkxml
DIRECTORIES += omiclient
DIRECTORIES += omireg
DIRECTORIES += cli
DIRECTORIES += providers
DIRECTORIES += check
DIRECTORIES += samples

ifdef CONFIG_SINGLEIMAGE
  DIRECTORIES += image
else
  DIRECTORIES += server agent
endif

DIRECTORIES += ../installbuilder

TESTDIRS += tests/io
TESTDIRS += tests/mof
TESTDIRS += tests/base
TESTDIRS += tests/provreg
TESTDIRS += tests/provmgr
TESTDIRS += tests/micxx
TESTDIRS += tests/sock
TESTDIRS += tests/protocol
TESTDIRS += tests/http
TESTDIRS += tests/httpclientcxx
TESTDIRS += tests/cli
TESTDIRS += tests/wsman
TESTDIRS += tests/wql
TESTDIRS += tests/wqlcxx
TESTDIRS += tests/strhash
TESTDIRS += tests/xml
TESTDIRS += samples/Providers/tests/PersonProvider

ifdef BUILD_TESTS
    DIRECTORIES += $(TESTDIRS)
endif

-include $(ROOT)/mak/rules.mak

##==============================================================================
##
## distclean:
##
##==============================================================================

distclean:
	rm -rf $(OUTPUTDIR)
	rm -rf $(CONFIGUREDIR)/GNUmakefile

##==============================================================================
##
## tests:
##
##==============================================================================

ifdef BUILD_TESTS
tests:
ifdef ENABLE_NITS
	$(BINDIR)/nits -trace -file:$(TOP)/ut/nonWin/nitsargs.txt
else
	@ $(foreach i, $(TESTDIRS), $(MAKE) -C $i tests $(NL) )
endif	
endif

##==============================================================================
##
## world:
##
##==============================================================================

__world:
	$(MAKE) -f $(ROOT)/build.mak clean
	$(MAKE) -f $(ROOT)/build.mak depend
	$(MAKE) -f $(ROOT)/build.mak
	$(MAKE) -f $(ROOT)/build.mak tests

world:
	time $(MAKE) -f $(ROOT)/build.mak __world
	@ echo
	$(MAKE) -f $(ROOT)/build.mak -s size

##==============================================================================
##
## gen:
##
##==============================================================================

GENDIRECTORIES = \
    providers/identify \
    samples/Providers/Color \
    samples/Providers/Connector \
    samples/Providers/ConnectorCXX \
    samples/Providers/Fan \
    samples/Providers/Fastener \
    samples/Providers/Number \
    samples/Providers/Demo-i2 \
    samples/Providers/PersonProvider \
    samples/Providers/PersonProviderCXX \
    samples/Providers/President \
    ut/base/tests \
    doc/omi/samples/frog \
    doc/omi/samples/connector

GENFILES=`grep -r -l '@''migen@' .`

lsgen:
	@ echo $(GENFILES)

gen:
	@ $(foreach i, $(GENDIRECTORIES), $(MAKE) -C $i gen $(NL) )

##==============================================================================
##
## install/uninstall
##
##==============================================================================

SO=$(shell $(BUILDTOOL) shlibext $(BUILDTOOLOPTS)

ifneq ($(WORLD)$(DESTDIR),1)

install:
ifdef DESTDIR
	( cd $(CONFIGUREDIR); $(OUTPUTDIR)/install --destdir=$(DESTDIR) )
else
	( cd $(CONFIGUREDIR); $(OUTPUTDIR)/install )
endif

uninstall:
	( $(OUTPUTDIR)/uninstall )

endif

##==============================================================================
##
## dist:
## dist.zip:
##
##==============================================================================

DISTTMPDIR=/tmp/omi/$(USER)
DIST=omi-$(CONFIG_VERSION)

DISTTAR=$(CONFIGUREDIR)/$(DIST).tar

distcommon:
	@ rm -rf $(DISTTMPDIR)
	@ rm -f $(DISTTAR).gz
	@ mkdir -p $(DISTTMPDIR)/$(DIST)
	@ cp -r . $(DISTTMPDIR)/$(DIST)/
	@ rm -rf $(DISTTMPDIR)/$(DIST)/$(OUTPUTDIRNAME)
	@ ( cd $(DISTTMPDIR); rm -rf `find . -name CVS` )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf nits )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf pal )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf `find . -name "buildchk.*"` )

dist: distcommon
	@ ( cd $(DISTTMPDIR); tar cf $(DISTTAR) $(DIST) )
	@ gzip $(DISTTAR)
	@ rm -rf $(DISTTMPDIR)
	@ echo "Created $(DISTTAR).gz"

DISTZIP=$(CONFIGUREDIR)/$(DIST).zip

dist.zip: distcommon
	@ ( cd $(DISTTMPDIR); zip -r -q $(DISTZIP) $(DIST); )
	@ rm -rf $(DISTTMPDIR)
	@ echo "Created $(DISTZIP)"

##==============================================================================
##
## check: check validity of build.
##
##==============================================================================

CHECKDIR=/tmp/omicheck.$(shell ./buildtool username)

check:
	rm -rf $(CHECKDIR)
	( cd $(CONFIGUREDIR); $(OUTPUTDIR)/install --destdir=$(CHECKDIR) )
	$(CHECKDIR)/$(CONFIG_BINDIR)/omiserver -i -d --livetime 60 --httpport 0 --httpsport 0 --destdir=$(CHECKDIR)
	sleep 2
	( export LD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR); $(CHECKDIR)/$(CONFIG_BINDIR)/omicheck --destdir=$(CHECKDIR) )
	sleep 2
	$(CHECKDIR)/$(CONFIG_BINDIR)/omiserver -s --destdir=$(CHECKDIR)
	sleep 2
	rm -rf $(CHECKDIR)

##==============================================================================
##
## size: print size of omiserver
##
##==============================================================================

size:
	size $(BINDIR)/omiserver

##==============================================================================
##
## timestamp: generate TIMESTAMP file.
##
##==============================================================================

TIMESTAMP=$(shell ./scripts/timestamp)

timestamp:
	@ rm -f ./TIMESTAMP
	@ echo $(TIMESTAMP) > ./TIMESTAMP

##==============================================================================
##
## cleanlog: remove the log files and trace files.
##
##==============================================================================

cleanlog:
	rm -f $(CONFIG_LOCALSTATEDIR)/log/*.log
	rm -f $(CONFIG_LOCALSTATEDIR)/log/*.trc

##==============================================================================
##
## run:
##
##==============================================================================

run:
	$(BINDIR)/omiserver -i --testopts

##==============================================================================
##
## start:
##
##==============================================================================

start:
	$(BINDIR)/omiserver -i -d

##==============================================================================
##
## stop:
##
##==============================================================================

stop:
	$(BINDIR)/omiserver -s

##==============================================================================
##
## cachegrind arguments:
##
##==============================================================================

CACHEGRIND_ARGS = $(BINDIR)/omiserver -i --testopts -l
