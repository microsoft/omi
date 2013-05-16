TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = PersonProvider

SOURCES = \
    $(TOP)/base/clientft.cpp \
    module.c \
    MSFT_Alert.c \
    MSFT_Friends.c \
    MSFT_Person.c \
    TestSP_Method.c \
    TestEmbeddedOperations.c \
    X_SingletonWithAllTypes.c \
    X_RefuseUnload.c \
    X_FailedAtLoad.c \
    schema.c

INCLUDES = $(TOP)/common

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = MSFT_Alert MSFT_Friends MSFT_Person TestSP_Method TestEmbeddedOperations X_SingletonWithAllTypes X_FailedAtLoad X_RefuseUnload

gen:
	$(BINDIR)/omigen -f schema.mof -e X_TestEmbeddedObjectNotReferenced $(CLASSES)
