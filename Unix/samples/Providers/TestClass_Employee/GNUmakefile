TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = Employee

SOURCES = \
    module.c \
    Address.cpp \
    ContactInfo.cpp \
    Employee.cpp \
    schema.c 


INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = Address=Address Employee=Employee ContactInfo=ContactInfo

LIBRARIES = base $(PALLIBS)

gen:
	$(BINDIR)/omigen -f TestClass_Employee.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

regtest:
	$(BINDIR)/omireg -n root/cimomtestprov -o @requestor@ $(TARGET)