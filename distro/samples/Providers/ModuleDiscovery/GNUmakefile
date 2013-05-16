TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = modulediscover

SOURCES = module.c schema.c PS_Module.c PS_ModuleFile.c PS_ModuleToModuleFile.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = base

include $(TOP)/mak/rules.mak

gen:
	$(BINDIR)/omigen schema.mof PS_Module PS_ModuleFile PS_ModuleToModuleFile

REGFILE=$(CSHLIBRARY).reg

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(REGFILE) "$(CONFIG_SYSCONFDIR)/omiregister/root-cimv2/$(REGFILE)"

unreg:
	rm -f $(REGFILE) "$(CONFIG_SYSCONFDIR)/omiregister/root-cimv2/$(REGFILE)"

gi:
	$(BINDIR)/omicli gi root/cimv2 { PS_Module InstanceID "/samples/Providers/ModuleDiscovery/TorSwitchManagement" }
