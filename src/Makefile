all :

OUTDIR := ../output
IDIR =../include
CFLAGS=-I$(IDIR)

_deps := $(wildcard ../include/*.h)

${OUTDIR}/%.o: %.c $(_deps)
	mkdir -p $(@D)
	cc -c -o $@ $< $(CFLAGS)

objects := $(patsubst %.c,${OUTDIR}/%.o,$(wildcard *.c))
objects += $(patsubst %.c,${OUTDIR}/%.o,$(wildcard driver/*.c))

all: ${objects} $(_deps)
	cc -o ${OUTDIR}/vcdt ${objects} $(CFLAGS) -l pigpio -l rt
