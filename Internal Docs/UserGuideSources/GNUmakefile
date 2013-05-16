
all:
	texi2dvi nanowbem.texi
	dvipdf nanowbem.dvi nanowbem.pdf
	makeinfo nanowbem.texi
	makeinfo --no-split --html nanowbem.texi

CLEAN = \
    nanowbem.aux \
    nanowbem.cp \
    nanowbem.dvi \
    nanowbem.fn \
    nanowbem.ky \
    nanowbem.log \
    nanowbem.pg \
    nanowbem.toc \
    nanowbem.tp \
    nanowbem.vr

clean:
	rm -f $(CLEAN)

ed:
	$(MAKE) all
	$(MAKE) clean
	acroread nanowbem.pdf &
