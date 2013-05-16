TOP = ../../../..
include $(TOP)/config.mak

CSHLIBRARY = fan

SOURCES = \
    ABC_AssociatedCooling.c \
    ABC_AssociatedSensor.c \
    ABC_ComputerSystem.c \
    ABC_ElementCapabilities.c \
    ABC_ElementConformsToProfile.c \
    ABC_EnabledLogicalElementCapabilities.c \
    ABC_Fan.c \
    ABC_HostedCollection.c \
    ABC_IsSpare.c \
    ABC_ManagedSystemElement.c \
    ABC_MemberOfCollection.c \
    ABC_NumericSensor.c \
    ABC_OwningCollectionElement.c \
    ABC_PhysicalPackage.c \
    ABC_Realizes.c \
    ABC_RedundancySet.c \
    ABC_RegisteredProfile.c \
    ABC_Sensor.c \
    ABC_SystemDevice.c \
    module.c \
    schema.c \
    utils.c

INCLUDES = ..

LIBRARIES = fancommon

CLASSES = ABC_Fan ABC_SystemDevice ABC_ComputerSystem ABC_AssociatedCooling ABC_ManagedSystemElement ABC_ElementCapabilities ABC_EnabledLogicalElementCapabilities ABC_ElementConformsToProfile ABC_RegisteredProfile ABC_Realizes ABC_PhysicalPackage ABC_AssociatedSensor ABC_Sensor ABC_IsSpare ABC_MemberOfCollection ABC_OwningCollectionElement ABC_HostedCollection ABC_RedundancySet ABC_NumericSensor

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

gen:
	$(BINDIR)/omigen -m fan schema.mof $(CLASSES)

help:
	$(BINDIR)/omigen -h
