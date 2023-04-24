TOP = $(shell cd .. ; pwd)
include $(TOP)/../../pal/build/config.mak
include $(TOP)/config.mak

# $(OUTPUTDIRNAME) will be something like:
#    output
#    output_openssl_1.0.0
#    output_openssl_1.1.0
#
# Get this into some reasonable prefix for the package directory.
#
#    omi/Packages - good for only one set of packages
#    omi/Packages/openssl_1.0.0 - good for binaries for OpenSSL 1.0.0
#    omi/Packages/openssl_1.1.0 - good for binaries for OpenSSL 1.1.0
#
# This makes it easier for Jenkins to have a reasonable directory layout
PACKAGE_DIR_SUFFIX = $(shell echo $(OUTPUTDIRNAME) | sed 's/output//' | sed 's~^_open~/open~')
PACKAGE_SSL_DECORATION = $(shell echo $(OUTPUTDIRNAME) | sed 's/output_openssl_1.0.0/ssl_100/' | sed 's/output_openssl_1.1.0/ssl_110/'| sed 's/output_openssl_3.0.0/ssl_300/')
PACKAGE_DIR = $(TOP)/../Packages/$(BUILD_CONFIGURATION)$(PACKAGE_DIR_SUFFIX)

# Selinux policy directories.
SEPOLICY_SRC_DIR=$(TOP)/installbuilder/selinux
SEPOLICY_DIR_LOGROTATE=$(OUTPUTDIR)/intermediate/tmp/selinux.logrotate
SEPOLICY_DIR_COMMON=$(OUTPUTDIR)/intermediate/tmp/selinux.common
SEPOLICY_DIR_COMMON_EL5=$(OUTPUTDIR)/intermediate/tmp/selinux.common.el5

DISTRO_TYPE = $(PF)
ifeq ($(PF),Linux)
DISTRO_TYPE = $(PF)_$(PF_DISTRO)
endif

DATAFILES = Base_OMI.data
COMPRESS_KIT = 0
BUILD_SEMODULE = 0

ifeq ($(PF),Linux)
DATAFILES += Linux.data
endif
ifeq ($(PF_DISTRO),ULINUX)
DATAFILES += ULinux.data
endif

ifeq ($(PF),AIX)
DATAFILES += AIX.data AIX_$(PF_MAJOR).data
endif
ifeq ($(PF),HPUX)
DATAFILES += HPUX.data
COMPRESS_KIT = 1
 ifeq ($(PF_ARCH), pa-risc)
DATAFILES += HPUX_pa-risc.data
 endif
endif
ifeq ($(PF),SunOS)
COMPRESS_KIT = 1
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

ifeq ($(ENABLE_DEBUG),1)
  WITH_SYMBOLS=debug
else
  WITH_SYMBOLS=withsymbols
endif

ifeq ($(ENABLE_SECURITY_HARDENING),1)
  SECURITY_FLAG=.s
else
  SECURITY_FLAG=
endif

# New output format for OMI on Linux (avoids ugly renaming since we always build universal)
ifeq ($(PF),Linux)
  BUILD_SEMODULE = 1
  ifneq ($(PF_ARCH),ppc)
    OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).$(PACKAGE_SSL_DECORATION).ulinux$(SECURITY_FLAG).$(PF_ARCH)
    OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
  else
    ifeq ($(PF_DISTRO),SUSE)
      OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).suse.$(PF_MAJOR).$(PF_ARCH)
      OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
    else
      OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).rhel.$(PF_MAJOR).$(PF_ARCH)
      OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
    endif
  endif
endif
ifeq ($(PF),AIX)
    OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).aix.$(PF_MAJOR).$(PF_ARCH)
    OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
endif
ifeq ($(PF),HPUX)
  ifeq ($(PF_ARCH), pa-risc)
    OUTPUTFILE_LINE_ARCH = parisc
  else
    OUTPUTFILE_LINE_ARCH = $(PF_ARCH)
  endif

  OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).hpux.11iv3.$(OUTPUTFILE_LINE_ARCH)
  OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
endif

ifeq ($(PF),SunOS)
  OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION)-$(CONFIG_PATCH_LEVEL).solaris.$(PF_MINOR).$(PF_ARCH)
  OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
endif

# Where does "strip" utility live?
ifeq ($(PF),Linux)
  STRIP_PATH=strip
else
  ifeq ($(PF),AIX)
    STRIP_PATH=/usr/ccs/bin/strip -X64
  else
    STRIP_PATH=/usr/ccs/bin/strip
  endif
endif

# DSC output format (used by DSC installbuilder Makefile)
ifdef SSL_VERSION
OUTPUTFILE_LINE = --OUTPUTFILE=omi-$(CONFIG_VERSION).ssl_$(SSL_VERSION).$(PF_ARCH)
OUTPUTFILE_LINE_WITHSYMBOLS = $(OUTPUTFILE_LINE).$(WITH_SYMBOLS)
endif

# SSL version we're building for (for package validation in preinstall script)
ifdef SSL_BUILD
  SSL_BUILD_LINE = --SSL_BUILD_VERSION=$(SSL_BUILD)
endif

ifeq ("$(wildcard /usr/bin/dpkg-deb)","")
DPKG_LOCATION="--DPKG_LOCATION=$(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-$(PF_ARCH)"
else
DPKG_LOCATION=
endif

all: sepolicy
ifneq ($(PF),Darwin)
  ifneq ($(PF),Linux)
	@echo "========================= Make OMI installer $(PF_DISTRO) with symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
		$(OUTPUTFILE_LINE_WITHSYMBOLS) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES)
        
    ifeq ($(COMPRESS_KIT),1)
	cd $(OUTPUTDIR)/release; compress -f `cat package_filename`
    endif 
    
    ifneq ($(ENABLE_DEBUG),1)
	@echo "========================= Make OMI installer $(PF_DISTRO) without symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	$(STRIP_PATH) $(OUTPUTDIR)/bin/*
	$(STRIP_PATH) $(OUTPUTDIR)/lib/*.so
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
        
        ifeq ($(COMPRESS_KIT),1)
	    cd $(OUTPUTDIR)/release; compress -f `cat package_filename`
        endif        
    endif


  else # ifneq ($(PF),Linux)
    ifeq ($(BUILD_RPM),1)
	@echo "========================= Make OMI installer RPM with symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
		$(OUTPUTFILE_LINE_WITHSYMBOLS) \
		$(SSL_BUILD_LINE) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_RPM.data
    endif # ifeq ($(BUILD_RPM),1)
    ifeq ($(BUILD_DPKG),1)
	egrep -q "^omiusers:" /etc/group; if [ $$? -ne 0 ]; then echo "Creating omiusers group ..."; sudo /usr/sbin/groupadd -r omiusers; fi
	egrep -q "^omi:" /etc/group; if [ $$? -ne 0 ]; then echo "Creating omi group ..."; sudo groupadd -r omi; fi
	egrep -q "^omi:" /etc/passwd; if [ $$? -ne 0 ]; then echo "Creating omi user ..."; sudo useradd -g omi -s /bin/false -r omi; fi

	@echo "========================= Make OMI installer DPKG with symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	ls -l $(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-x64
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
		$(OUTPUTFILE_LINE_WITHSYMBOLS) \
		$(SSL_BUILD_LINE) \
		$(DPKG_LOCATION) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_DPKG.data
    endif # ifeq ($(BUILD_DPKG),1)

    ifneq ($(ENABLE_DEBUG),1)
	# Strip the symbols from the binary and library files
	$(STRIP_PATH) $(OUTPUTDIR)/bin/*
	$(STRIP_PATH) $(OUTPUTDIR)/lib/*.so

      ifeq ($(BUILD_RPM),1)
	@echo "========================= Make OMI installer RPM without symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
		$(SSL_BUILD_LINE) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_RPM.data
      endif # ifeq ($(BUILD_RPM),1)
      ifeq ($(BUILD_DPKG),1)
	@echo "========================= Make OMI installer DPKG without symbols"
	sudo rm -rf $(OUTPUTDIR)/intermediate/staging
	mkdir -p $(OUTPUTDIR)/release $(OUTPUTDIR)/intermediate
	ls -l $(TOP)/../../pal/installer/InstallBuilder/tools/bin/dpkg-deb-x64
	sudo python $(TOP)/../../pal/installer/InstallBuilder/installbuilder.py \
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
		$(SSL_BUILD_LINE) \
		$(DPKG_LOCATION) \
		--DATAFILE_PATH=$(TOP)/installbuilder/datafiles \
		$(DATAFILES) Linux_DPKG.data
      endif # ifeq ($(BUILD_DPKG),1)
    endif # ifneq ($(ENABLE_DEBUG),1)
  endif # ifneq ($(PF),Linux)

	sudo chown -R $(USER) $(OUTPUTDIR)
	mkdir -p $(PACKAGE_DIR)
	cp $(OUTPUTDIR)/release/omi-* $(PACKAGE_DIR)
endif # ifneq ($(PF),Darwin)

ifeq ($(PF),Darwin)
	# We need a raw copy of omicli (for testing on the Mac platform)
	mkdir -p $(PACKAGE_DIR)
	cp $(OUTPUTDIR)/bin/omicli $(PACKAGE_DIR)

	# copy the libmi_origin.dylib to libmi.dylib 
	cp $(OUTPUTDIR)/lib/libmi_origin.dylib $(PACKAGE_DIR)/libmi.dylib
else #($(PF),Darwin) 
  ifeq ($(PF),Linux)
	# copy the libmi_origin.so to libmi.so 
	mkdir -p $(PACKAGE_DIR)
	cp $(OUTPUTDIR)/lib/libmi_origin.so $(PACKAGE_DIR)/libmi.so
  else #ifeq ($(PF),Linux)
	# copy normal libmi.so for other platforms
	cp $(OUTPUTDIR)/lib/libmi.so $(PACKAGE_DIR)
  endif #ifeq ($(PF),Linux)
endif #($(PF),Darwin) 

sepolicy: $(SEPOLICY_DIR_LOGROTATE)/omi-logrotate.pp $(SEPOLICY_DIR_COMMON)/omi-selinux.pp $(SEPOLICY_DIR_COMMON_EL5)/omi-selinux.pp

clean:
#	sudo rm -rf $(OUTPUTDIR)/intermediate
#	sudo rm -rf $(OUTPUTDIR)/release

#--------------------------------------------------------------------------------
# Build SELinux policy modules for omi-logrotate

	# remove old policy module folders and files
	rm -rf $(SEPOLICY_DIR_LOGROTATE)
	rm -rf $(SEPOLICY_DIR_COMMON)
	rm -rf $(SEPOLICY_DIR_COMMON_EL5)

ifeq ($(BUILD_SEMODULE),1)
$(SEPOLICY_DIR_LOGROTATE)/omi-logrotate.pp : $(SEPOLICY_SRC_DIR)/omi-logrotate.te $(SEPOLICY_SRC_DIR)/omi-logrotate.fc
	@echo "========================= Building selinux policy module for omi-logrotate"
	mkdir -p $(SEPOLICY_DIR_LOGROTATE)
	cp $(SEPOLICY_SRC_DIR)/omi-logrotate.te $(SEPOLICY_DIR_LOGROTATE)
	cp $(SEPOLICY_SRC_DIR)/omi-logrotate.fc $(SEPOLICY_DIR_LOGROTATE)/omi-logrotate.fc
	cd $(SEPOLICY_DIR_LOGROTATE); make -f /usr/share/selinux/devel/Makefile

$(SEPOLICY_DIR_COMMON)/omi-selinux.pp : $(SEPOLICY_SRC_DIR)/omi-selinux.te $(SEPOLICY_SRC_DIR)/omi-selinux.fc
	@echo "========================= Building selinux policy module for omi-selinux"
	mkdir -p $(SEPOLICY_DIR_COMMON)
	cp $(SEPOLICY_SRC_DIR)/omi-selinux.te $(SEPOLICY_DIR_COMMON)
	cp $(SEPOLICY_SRC_DIR)/omi-selinux.fc $(SEPOLICY_DIR_COMMON)/omi-selinux.fc
	cd $(SEPOLICY_DIR_COMMON); make -f /usr/share/selinux/devel/Makefile

$(SEPOLICY_DIR_COMMON_EL5)/omi-selinux.pp : $(SEPOLICY_SRC_DIR)/omi-selinux.el5.te $(SEPOLICY_SRC_DIR)/omi-selinux.fc
	@echo "========================= Building EL5 selinux policy module for omi-selinux"
	mkdir -p $(SEPOLICY_DIR_COMMON_EL5)
	cp $(SEPOLICY_SRC_DIR)/omi-selinux.el5.te $(SEPOLICY_DIR_COMMON_EL5)/omi-selinux.te
	cp $(SEPOLICY_SRC_DIR)/omi-selinux.fc $(SEPOLICY_DIR_COMMON_EL5)/omi-selinux.fc
	cd $(SEPOLICY_DIR_COMMON_EL5); make -f /usr/share/selinux/devel/Makefile
else
$(SEPOLICY_DIR_LOGROTATE)/omi-logrotate.pp : $(SEPOLICY_SRC_DIR)/omi-logrotate.te $(SEPOLICY_SRC_DIR)/omi-logrotate.fc
	@echo "========================= Building omi logrotate selinux policy module"
	mkdir -p $(SEPOLICY_DIR_LOGROTATE)
	touch $(SEPOLICY_DIR_LOGROTATE)/omi-logrotate.pp

$(SEPOLICY_DIR_COMMON)/omi-selinux.pp : $(SEPOLICY_SRC_DIR)/omi-selinux.te $(SEPOLICY_SRC_DIR)/omi-selinux.fc
	@echo "========================= Building omi selinux policy module"
	mkdir -p $(SEPOLICY_DIR_COMMON)
	touch $(SEPOLICY_DIR_COMMON)/omi-selinux.pp

$(SEPOLICY_DIR_COMMON_EL5)/omi-selinux.pp : $(SEPOLICY_SRC_DIR)/omi-selinux.el5.te $(SEPOLICY_SRC_DIR)/omi-selinux.fc
	@echo "========================= Building omi EL5 selinux policy module"
	mkdir -p $(SEPOLICY_DIR_COMMON_EL5)
	touch $(SEPOLICY_DIR_COMMON_EL5)/omi-logrotate.pp
endif
