TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = DogProvider

SOURCES = \
    Dog_Class_Provider.cpp \
    module.cpp \
    stubs.cpp \
    schema.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx $(PALLIBS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

REGFILE=$(TOP)/etc/omiregister/root-omi/DogProvider.reg

gen:
	$(BINDIR)/omigen --cpp -f schema.mof XYZ_Dog=Dog

reg:
	$(BINDIR)/omireg --hosting '@requestor@' -n root/omi $(TARGET)
	echo "PREEXEC=DogPreExec" >> $(REGFILE)
	cat $(REGFILE)

ei:
	$(BINDIR)/omicli ei root/omi XYZ_Dog
