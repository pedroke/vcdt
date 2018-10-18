all :

OUTDIR := ../build
IDIR =../include
CFLAGS=-I$(IDIR)
OUTNAME = vcdt

_deps := $(wildcard ../include/*.h)

${OUTDIR}/%.o: %.c $(_deps)
	mkdir -p $(@D)
	cc -c -o $@ $< $(CFLAGS)

objects := $(patsubst %.c,${OUTDIR}/%.o,$(wildcard *.c))
objects += $(patsubst %.c,${OUTDIR}/%.o,$(wildcard driver/*.c))

.PHONY: all
all: ${objects} $(_deps)
	cc -o ${OUTDIR}/${OUTNAME} ${objects} $(CFLAGS) -l pigpio -l rt

PREFIX = /usr/local

.PHONY: install
install: ${OUTDIR}/${OUTNAME}
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/${OUTNAME}

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/${OUTNAME}
