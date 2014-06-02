TOP = ../../..

include $(TOP)/config.mak

CXXSHLIBRARY = NetworkProvider

SOURCES = $(wildcard *.c *.cpp)

INCLUDES = $(TOP)/common $(TOP)

LIBRARIES = micxx base $(PALLIBS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = \
    OMI_ACLAppliesToElement \
    OMI_ACL \
    OMI_EthernetPort \
    OMI_NetworkVLAN

SCHEMADIR = $(CONFIG_DATADIR)/networkschema

SCHEMA = $(SCHEMADIR)/CIM_Schema.mof

gen:
	$(BINDIR)/omigen -B -C $(SCHEMA) -I $(SCHEMADIR) -f schema.mof $(CLASSES)

#HOSTING = --hosting @inproc@
#HOSTING = --hosting @requestor@

reg:
	$(BINDIR)/omireg -n root/omi $(HOSTING) $(TARGET)

ei:
	$(BINDIR)/omicli ei root/omi OMI_ACLAppliesToElement

ei2:
	$(BINDIR)/omicli ei root/omi OMI_NetworkVLAN
