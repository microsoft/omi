TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = PersonProviderCXX

SOURCES = \
    module.cpp \
    MSFT_Alert_Class_Provider.cpp \
    MSFT_Friends_Class_Provider.cpp \
    MSFT_Person_Class_Provider.cpp \
    TestSP_Method_Class_Provider.cpp \
    TestEmbeddedOperations_Class_Provider.cpp \
    X_SingletonWithAllTypes_Class_Provider.cpp \
    X_RefuseUnload_Class_Provider.cpp \
    X_FailedAtLoad_Class_Provider.cpp \
    stubs.cpp \
    schema.c

INCLUDES = $(TOP) $(TOP)/common

ifeq ($(OS),LINUX)
CXXFLAGS = -fno-exceptions -fno-enforce-eh-specs -fno-rtti
endif

LIBRARIES = micxx $(PALLIBS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = MSFT_Alert MSFT_Friends MSFT_Person TestSP_Method TestEmbeddedOperations X_SingletonWithAllTypes X_FailedAtLoad X_RefuseUnload

gen:
	$(BINDIR)/omigen -A --cpp schema.mof -e X_TestEmbeddedObjectNotReferenced $(CLASSES)
