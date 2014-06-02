
all:
	texi2dvi omi.texi
	dvipdf omi.dvi omi.pdf
	makeinfo omi.texi
	makeinfo --no-split --html omi.texi

CLEAN = \
    omi.aux \
    omi.cp \
    omi.dvi \
    omi.fn \
    omi.ky \
    omi.log \
    omi.pg \
    omi.toc \
    omi.tp \
    omi.vr

clean:
	rm -f $(CLEAN)

ed:
	$(MAKE) all
	$(MAKE) clean
	acroread omi.pdf &
