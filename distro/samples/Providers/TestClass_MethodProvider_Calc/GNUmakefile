TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = TestClass_MethodProvider_Calc

SOURCES = \
    module.c \
    TestClass_MethodProvider_Calc.cpp \
    NumbersTask.cpp \
    Numbers.cpp \
    schema.c 

	


INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = TestClass_MethodProvider_Calc=TestClass_MethodProvider_Calc NumbersTask=NumbersTask Numbers=Numbers

LIBRARIES = base

gen:
	$(BINDIR)/omigen -f MethodProvider_Properties.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"
