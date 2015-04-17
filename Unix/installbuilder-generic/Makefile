TOP := ..
BUILD_RPM := 1
BUILD_DPKG := 1

OUTPUT_DIR := $(TOP)/output
STAGING_DIR := $(OUTPUT_DIR)/staging
INTERMEDIATE_DIR := $(OUTPUT_DIR)/intermediate
RELEASE_DIR := $(OUTPUT_DIR)/release

IB_DIR := $(shell cd ../../../pal/installer/InstallBuilder; pwd)
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
 PF_ARCH := x64
else
 PF_ARCH := x86
endif
CONFIG_VERSION := 1.0.8

all:
ifeq ($(BUILD_RPM),1)
	@echo "========================= Make OMI installer"
	sudo rm -rf $(STAGING_DIR) $(INTERMEDIATE_DIR)
	mkdir -p $(RELEASE_DIR) $(STAGING_DIR) $(INTERMEDIATE_DIR)
	python $(IB_DIR)/installbuilder.py \
		--BASE_DIR=$(OUTPUT_DIR) \
		--TARGET_DIR=$(RELEASE_DIR) \
		--INTERMEDIATE_DIR=$(INTERMEDIATE_DIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--PACKAGE_TYPE=RPM \
		--PF=Linux \
		--PFMAJOR=1 \
		--PFMINOR=0 \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=ULINUX \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=1 \
		--OUTPUTFILE=omiserver-$(CONFIG_VERSION).ssl_$(SSL_VERSION).$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder-generic/datafiles \
		Base_OMI.data
endif
ifeq ($(BUILD_DPKG),1)
	@echo "========================= Make OMI installer"
	sudo rm -rf $(STAGING_DIR) $(INTERMEDIATE_DIR) 
	mkdir -p $(RELEASE_DIR) $(STAGING_DIR) $(INTERMEDIATE_DIR)
	python $(IB_DIR)/installbuilder.py \
		--BASE_DIR=$(OUTPUT_DIR) \
		--TARGET_DIR=$(RELEASE_DIR) \
		--INTERMEDIATE_DIR=$(INTERMEDIATE_DIR) \
		--STAGING_DIR=$(STAGING_DIR) \
		--PACKAGE_TYPE=DPKG \
		--PF=Linux \
		--PFMAJOR=1 \
		--PFMINOR=0 \
		--PFARCH=$(PF_ARCH) \
		--PFDISTRO=ULINUX \
		--VERSION=$(CONFIG_VERSION) \
		--RELEASE=1 \
		--OUTPUTFILE=omiserver-$(CONFIG_VERSION).ssl_$(SSL_VERSION).$(PF_ARCH) \
		--DPKG_LOCATION=$(IB_DIR)/tools/bin/dpkg-deb-$(PF_ARCH) \
		--DATAFILE_PATH=$(TOP)/installbuilder-generic/datafiles \
		Base_OMI.data
endif
