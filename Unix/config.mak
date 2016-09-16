ifndef OUTPUTDIR
  OUTPUTDIR=$(TOP)/output
endif

-include $(OUTPUTDIR)/config.mak

ifndef CONFIG_MAK
$(error "Please use ./configure script to configure for this platform")
endif
