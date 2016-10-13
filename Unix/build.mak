.PHONY: world
.PHONY: check
.PHONY: install
.PHONY: server
.PHONY: tests

ifndef OUTPUTDIR
$(error OUTPUTDIR is undefined)
endif

ifndef DISTBASE
    DISTBASE=$(`pwd`/../tmp)
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

DIRECTORIES += pal
DIRECTORIES += pal/nitspal

DIRECTORIES += nits

DIRECTORIES += ut
ifeq ($(COMPILER),GNU)
DIRECTORIES += strhash
endif
DIRECTORIES += mof
DIRECTORIES += base
DIRECTORIES += sock
DIRECTORIES += oi/gen_c/common
DIRECTORIES += oi/gen_c/cmdline
DIRECTORIES += wql
DIRECTORIES += gen
DIRECTORIES += provreg
DIRECTORIES += provmgr
DIRECTORIES += disp
DIRECTORIES += omi_error
DIRECTORIES += miapi
DIRECTORIES += protocol
DIRECTORIES += http
DIRECTORIES += wsman
DIRECTORIES += xml
DIRECTORIES += xmlserializer
DIRECTORIES += omiutils
DIRECTORIES += codec/mof
DIRECTORIES += codec/mof/parser
DIRECTORIES += midll
DIRECTORIES += providers
DIRECTORIES += micxx
DIRECTORIES += omiclient
DIRECTORIES += configeditor
DIRECTORIES += cli
DIRECTORIES += omireg
DIRECTORIES += check
DIRECTORIES += samples

ifndef DISABLE_INDICATION
DIRECTORIES += indication/common
DIRECTORIES += indication/indimgr
endif

ifdef CONFIG_SINGLEIMAGE
  DIRECTORIES += image
else
  DIRECTORIES += server agent
endif

TESTDIRS += tests/util
TESTDIRS += tests/io
TESTDIRS += tests/mof
TESTDIRS += tests/base
TESTDIRS += tests/provreg
TESTDIRS += tests/provmgr
TESTDIRS += tests/micxx
TESTDIRS += tests/sock
TESTDIRS += tests/protocol
TESTDIRS += tests/http
TESTDIRS += tests/cli
TESTDIRS += tests/wsman
TESTDIRS += tests/wql
TESTDIRS += tests/strhash
TESTDIRS += tests/xml
TESTDIRS += tests/xmlserializer
TESTDIRS += samples/Providers/tests/PersonProvider
TESTDIRS += tests/miapi
TESTDIRS += tests/oi
TESTDIRS += tests/codec/mof/util
TESTDIRS += tests/codec/mof/blue

ifndef DISABLE_INDICATION
TESTDIRS += samples/Providers/Test_Indication
TESTDIRS += tests/indication
endif

TESTDIRS += tests/pal

##==============================================================================
##
## rules targets for DSC:
##
##==============================================================================

ifdef ENABLE_DSC
DIRECTORIES += omiutils
DIRECTORIES += codec/mof
DIRECTORIES += codec/mof/parser
DIRECTORIES += dsc/engine/EngineHelper
DIRECTORIES += dsc/engine/ca/CAInfrastructure
DIRECTORIES += dsc/engine/ca/CALogInfrastructure
DIRECTORIES += dsc/engine/ConfigurationManager
DIRECTORIES += dsc/engine/ModuleLoader/ModuleLibrary
DIRECTORIES += dsc/engine/lcm
DIRECTORIES += dsc/engine/ConsistencyInvoker
TESTDIRS += dsc/tests/Engine/TestProvider
TESTDIRS += dsc/tests/Engine/TestFileProvider
TESTDIRS += dsc/tests/Engine/CA
TESTDIRS += dsc/tests/Engine/ModuleLoader
TESTDIRS += dsc/tests/Engine/LCM
TESTDIRS += dsc/tests/Engine/E2E
endif

ifdef BUILD_TESTS
    DIRECTORIES += $(TESTDIRS)
endif

-include $(ROOT)/mak/rules.mak

##==============================================================================
##
## deploy DSC:
##
##==============================================================================

deploydsc:
	mkdir -p $(SYSCONFDIR)/dsc
	mkdir -p $(SYSCONFDIR)/dsc/configuration
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/MSFT_LogResource
	mkdir -p $(SYSCONFDIR)/dsc/configuration/baseregistration
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/MSFT_LogResource
	mkdir -p $(SYSCONFDIR)/dsc/configuration/BuiltinProvCache
	mkdir -p $(DATADIR)/dsc
	mkdir -p $(DATADIR)/dsc/configuration
	mkdir -p $(DATADIR)/dsc/configuration/schema
	mkdir -p $(DATADIR)/dsc/configuration/registration
	cp  -r $(ROOT)/dsc/mof/OMI_BaseResourceUE.mof $(SYSCONFDIR)/dsc/configuration/baseregistration/baseresource.schema.mof
	cp  -r $(ROOT)/dsc/mof/MSFT_DSCMetaConfiguration.mof $(SYSCONFDIR)/dsc/configuration/baseregistration/MSFT_DSCMetaConfiguration.mof
	cp  -r $(ROOT)/dsc/mof/MSFT_LogResource.schema.mof $(SYSCONFDIR)/dsc/configuration/schema/MSFT_LogResource
	cp  -r $(ROOT)/dsc/mof/MSFT_LogResource.registration.mof $(SYSCONFDIR)/dsc/configuration/registration/MSFT_LogResource
	$(BINDIR)/omireg -n "dsc" $(LIBDIR)/libdsccore.so


##==============================================================================
##
## deploy DSC Test:
##
##==============================================================================

deploydsctest:
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/TestResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/Test2ResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/Test3UserResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/TestStopResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/registration/MSFT_FileDirectoryConfiguration
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/MSFT_FileDirectoryConfiguration
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/TestResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/Test2ResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/Test3UserResourceModule
	mkdir -p $(SYSCONFDIR)/dsc/configuration/schema/TestStopResourceModule
	cp -r $(ROOT)/dsc/tests/Module/Reg/OMI_TestResourceModule/* $(SYSCONFDIR)/dsc/configuration/registration/TestResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Reg/OMI_Test2ResourceModule/* $(SYSCONFDIR)/dsc/configuration/registration/Test2ResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Reg/OMI_Test3UserResourceModule/* $(SYSCONFDIR)/dsc/configuration/registration/Test3UserResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Reg/OMI_TestStopResourceModule/* $(SYSCONFDIR)/dsc/configuration/registration/TestStopResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Sch/TestResourceModule/* $(SYSCONFDIR)/dsc/configuration/schema/TestResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Sch/Test2ResourceModule/* $(SYSCONFDIR)/dsc/configuration/schema/Test2ResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Sch/Test3UserResourceModule/* $(SYSCONFDIR)/dsc/configuration/schema/Test3UserResourceModule/
	cp -r $(ROOT)/dsc/tests/Module/Sch/TestStopResourceModule/* $(SYSCONFDIR)/dsc/configuration/schema/TestStopResourceModule/
	cp -r $(ROOT)/dsc/tests/Engine/TestFileProvider/MSFT_FileDirectoryConfiguration.schema.mof $(SYSCONFDIR)/dsc/configuration/schema/MSFT_FileDirectoryConfiguration
	cp -r $(ROOT)/dsc/tests/Engine/TestFileProvider/MSFT_FileDirectoryConfiguration.registration.mof $(SYSCONFDIR)/dsc/configuration/registration/MSFT_FileDirectoryConfiguration
	$(BINDIR)/omireg -n "dsc" $(LIBDIR)/libNITSDSCFileTestProvider.so
	$(BINDIR)/omireg -n "dsc" $(LIBDIR)/libNITSDSCTestProvider.so
        
	

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
	( LD_LIBRARY_PATH=$(LIBDIR); export LD_LIBRARY_PATH; DYLD_FALLBACK_LIBRARY_PATH=$(LIBDIR); export DYLD_FALLBACK_LIBRARY_PATH; DYLD_LIBRARY_PATH=$(LIBDIR); export DYLD_LIBRARY_PATH; $(BINDIR)/nits -file:$(TMPDIR)/nitsargs.txt )
dsctests:
	( LD_LIBRARY_PATH=$(LIBDIR); export LD_LIBRARY_PATH; DYLD_LIBRARY_PATH=$(LIBDIR); export DYLD_LIBRARY_PATH; $(BINDIR)/nits -file:$(TMPDIR)/nitsdscargs.txt )
endif

##==============================================================================
##
## dscworld:
##
##==============================================================================

__dscworld:
	$(MAKE) -f $(ROOT)/build.mak clean
	$(MAKE) -f $(ROOT)/build.mak depend
	$(MAKE) -f $(ROOT)/build.mak
	$(MAKE) -f $(ROOT)/build.mak deploydsc
	$(MAKE) -f $(ROOT)/build.mak deploydsctest
	$(BINDIR)/omiserver &
	$(MAKE) -f $(ROOT)/build.mak dsctests
	killall -r omiserver

dscworld:
	time $(MAKE) -f $(ROOT)/build.mak __dscworld
	@ echo
	$(MAKE) -f $(ROOT)/build.mak -s size


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

DISTTMPDIR=$(DISTBASE)/tmp/omi/$(USER)
DIST=omi-$(CONFIG_VERSION)

DISTTAR=$(CONFIGUREDIR)/$(DIST).tar

DISTTestProviders=samples/Providers

distcommon:
	@ rm -rf $(DISTTMPDIR)
	@ rm -f $(DISTTAR).gz
	@ mkdir -p $(DISTTMPDIR)/$(DIST)
	@ cp -r . $(DISTTMPDIR)/$(DIST)/
	@ rm -rf $(DISTTMPDIR)/$(DIST)/$(OUTPUTDIRNAME)
	@ ( cd $(DISTTMPDIR); rm -rf `find . -name CVS` )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf scriptext )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf wmiadapter )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf `find . -name "buildchk.*"` )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -f ./nits/NITS.docx )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf ./tools/changes )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf ./tools/striplic )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf ./tools/dos2unix )
	@ ( cd $(DISTTMPDIR)/$(DIST); rm -rf ./GNUmakefile )
	@ ( cd $(DISTTMPDIR)/$(DIST)/$(DISTTestProviders); rm -rf Test_BigProvider )
	@ ( cd $(DISTTMPDIR)/$(DIST)/$(DISTTestProviders); rm -rf TestClass_ComplexGraphs )
	@ ( cd $(DISTTMPDIR)/$(DIST)/$(DISTTestProviders); rm -rf Test_Perf_WMIv2_SingleThread )	
	@ ( cd $(DISTTMPDIR)/$(DIST)/$(DISTTestProviders); rm -rf Test_TorSwitchSchema )
	@ ( cd $(DISTTMPDIR)/$(DIST)/$(DISTTestProviders); rm -f TestProviders.mak )	
	
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

CHECKDIR=$(DISTBASE)/tmp/omicheck.$(shell ./buildtool username)

check:
	echo $(DISTBASE)
	rm -rf $(CHECKDIR)
	( cd $(CONFIGUREDIR); $(OUTPUTDIR)/install --destdir=$(CHECKDIR) )
	( LD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR);  \
	  export LD_LIBRARY_PATH;  \
	  DYLD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR);  \
	  export DYLD_LIBRARY_PATH; \
	  $(CHECKDIR)/$(CONFIG_BINDIR)/omiserver -i -d --livetime 60 --httpport 0 --httpsport 0 --destdir=$(CHECKDIR) )
	sleep 2
	( LD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR); export LD_LIBRARY_PATH; \
	  DYLD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR); export DYLD_LIBRARY_PATH; $(CHECKDIR)/$(CONFIG_BINDIR)/omicheck --destdir=$(CHECKDIR) )
	sleep 2
	( LD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR);  \
	  export LD_LIBRARY_PATH;  \
	  DYLD_LIBRARY_PATH=$(CHECKDIR)/$(CONFIG_LIBDIR); \
	  export DYLD_LIBRARY_PATH; \
	  $(CHECKDIR)/$(CONFIG_BINDIR)/omiserver -s --destdir=$(CHECKDIR))
	sleep 2
	rm -rf $(CHECKDIR)

##==============================================================================
##
## size: print size of omiserver
##
##==============================================================================

size:
	${shell ./buildtool size} $(BINDIR)/omiserver

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
## oigenc: 
##
##==============================================================================

OIGENC_IN=./base/oi_traces.h
OIGENC_OUT=./base/oiomi.h

oigenc:
	chmod +w $(OIGENC_IN)
	chmod +w $(OIGENC_OUT)
	$(BINDIR)/oigenc FILE $(OIGENC_IN) $(OIGENC_OUT)

##==============================================================================
##
## cachegrind arguments:
##
##==============================================================================

CACHEGRIND_ARGS = $(BINDIR)/omiserver -i --testopts -l
