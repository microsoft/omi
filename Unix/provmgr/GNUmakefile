TOP = ..
include $(TOP)/config.mak

LIBRARY = provmgr

SOURCES = provmgr.c context.c

ifdef DISABLE_INDICATION
else
SOURCES += AggregationContext.c SubscriptionContext.c LifecycleContext.c filter.c SubMgr.c indicationSchema.c nioproc.c
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= HOOK_BUILD

LIBRARIES = base

include $(TOP)/mak/rules.mak

top:
	( cd $(TOP); make )

GENCLASSES = \
    CIM_Indication \
    CIM_InstCreation \
    CIM_InstDeletion \
    CIM_InstIndication \
    CIM_InstMethodCall \
    CIM_InstModification \
    CIM_InstRead

gen:
	chmod +w *.h *.c
	$(BINDIR)/omigen -n -s indicationSchemaDecl schema.mof $(GENCLASSES)
	mv schema.c indicationSchema.c

