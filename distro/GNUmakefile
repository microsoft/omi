.PHONY: check
.PHONY: tests

__ROOT=$(HOME)/src/omi/distro
export OUTPUTDIR=$(HOME)/src/omi/distro/output

all:
	( cd $(__ROOT); $(MAKE) -f build.mak )

tests:
	( cd $(__ROOT); $(MAKE) -f build.mak tests )

check:
	( cd $(__ROOT); $(MAKE) -f build.mak check )

%:
	( cd $(__ROOT); $(MAKE) -f build.mak $(MAKECMDGOALS) )
