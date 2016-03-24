TOP = $(shell cd .. ; pwd)
include $(TOP)/../../pal/build/config.mak
include $(TOP)/config.mak

DISTRO_TYPE = $(PF)
ifeq ($(PF),Linux)
DISTRO_TYPE = $(PF)_$(PF_DISTRO)
endif

DATAFILES = Base_OMI.data

ifeq ($(PF),Linux)
DATAFILES += Linux.data
endif
ifeq ($(PF),AIX)
DATAFILES += AIX.data
endif
ifeq ($(PF),HPUX)
DATAFILES += HPUX.data
 ifeq ($(PF_ARCH), pa-risc)
DATAFILES += HPUX_pa-risc.data
 endif
endif
ifeq ($(PF),SunOS)
DATAFILES += SunOS.data
 ifeq ($(PF_MINOR),9)
DATAFILES += SunOS_5.9.data
 endif
 ifeq ($(PF_MINOR),10)
DATAFILES += SunOS_5.10.data
 endif
 ifeq ($(PF_MINOR),11)
DATAFILES += SunOS_5.11.data
 endif
endif

# New output format for OMI on Linux (avoids ugly renaming since we always build universal)
ifeq ($(PF),Linux)
OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).universal.$(PF_ARCH)
endif

# DSC output format (used by DSC installbuilder Makefile)
ifdef SSL_VERSION
OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION).ssl_$(SSL_VERSION).$(PF_ARCH)
endif

all:
ifneq ($(PF),Linux)
	@echo "========================= Make OMI installer $(PF_DISTRO)"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(OUTPUTDIR) \
		--TARGET_DIR=$(OUTPUTDIR)/release \
		--INTERMEDIATE_DIR=$(OUTPUTDIR)/intermediate \
		--STAGING_DIR=$(OUTPUTDIR)/intermediate/staging \
		--PF=$(PF) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=$(CONFIG_PATCH_LEVEL) \
		$(OUTPUTFILE_LINE) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES)
else
 ifeq ($(BUILD_RPM),1)
	@echo "========================= Make OMI installer RPM"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(OUTPUTDIR) \
		--TARGET_DIR=$(OUTPUTDIR)/release \
		--INTERMEDIATE_DIR=$(OUTPUTDIR)/intermediate \
		--STAGING_DIR=$(OUTPUTDIR)/intermediate/staging \
		--PF=$(PF) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=$(CONFIG_PATCH_LEVEL) \
		$(OUTPUTFILE_LINE) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_RPM.data
 endif
 ifeq ($(BUILD_DPKG),1)
	egrep -q "^omiusers:" /etc/group; if [ $$? -ne 0 ]; then echo "Creating omiusers group ..."; sudo groupadd -r omiusers; fi

	echo "========================= Make OMI installer DPKG"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	ls -l $(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-x64
	python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
		--BASE_DIR=$(OUTPUTDIR) \
		--TARGET_DIR=$(OUTPUTDIR)/release \
		--INTERMEDIATE_DIR=$(OUTPUTDIR)/intermediate \
		--STAGING_DIR=$(OUTPUTDIR)/intermediate/staging \
		--PF=$(PF) \
		--PFMAJOR=$(PF_MAJOR) \
		--PFMINOR=$(PF_MINOR) \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=$(PF_DISTRO) \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=$(CONFIG_PATCH_LEVEL) \
		$(OUTPUTFILE_LINE) \
		--DPKG_LOCATION=$(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_DPKG.data
 endif
endif
clean:

#	sudo rm -rf $(OUTPUTDIR)/intermediate
#	sudo rm -rf $(OUTPUTDIR)/release
