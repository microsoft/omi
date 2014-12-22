TOP = $(shell cd .. ; pwd)
include $(TOP)/../../pal/build/config.mak
include $(TOP)/config.mak

DISTRO_TYPE = $(PF)
ifeq ($(PF),Linux)
DISTRO_TYPE = $(PF)_$(PF_DISTRO)
 ifeq ($(PF_DISTRO_ULINUX_R),1)
DISTRO_TYPE = $(PF)_$(PF_DISTRO)_R
 endif
 ifeq ($(PF_DISTRO_ULINUX_D),1)
DISTRO_TYPE = $(PF)_$(PF_DISTRO)_D
 endif
endif

DATAFILES = Base_OMI.data

ifeq ($(PF),Linux)
DATAFILES += Linux.data
 ifeq ($(PF_DISTRO), REDHAT)
DATAFILES += Linux_RPM.data Linux_RHEL.data
 endif
 ifeq ($(PF_DISTRO), SUSE)
DATAFILES += Linux_RPM.data Linux_SLES.data
  ifeq ($(PF_MAJOR),12)
DATAFILES += Linux_SLES_12.data
  endif
  ifeq ($(PF_MAJOR),11)
DATAFILES += Linux_SLES_11.data
  endif
  ifeq ($(PF_MAJOR),10)
DATAFILES += Linux_SLES_10.data
  endif
  ifeq ($(PF_MAJOR),9)
DATAFILES += Linux_SLES_9.data
  endif
 endif
 ifeq ($(PF_DISTRO), ULINUX)
DATAFILES += Linux_ULINUX.data
 endif
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

all:
ifneq ($(PF_DISTRO),ULINUX)
	@echo "========================= Make OMI installer"
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
		--RELEASE=1 \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES)  
else
 ifeq ($(BUILD_RPM),1)
	@echo "========================= Make OMI installer"
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
		--RELEASE=1 \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_RPM.data
 endif
 ifeq ($(BUILD_DPKG),1)
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
		--RELEASE=1 \
		--DPKG_LOCATION=$(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_DPKG.data
 endif
endif
clean:

#	sudo rm -rf $(OUTPUTDIR)/intermediate
#	sudo rm -rf $(OUTPUTDIR)/release
