IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -O3 -std=c99

ODIR=obj
LDI =../lib

LIBS=-lm

_DEPS = operations.h io.h statula.h dataset.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = statula.o dataset.o operations.o io.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statula: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean reduced_precision

reduced_precision: clean
reduced_precision: CFLAGS+="-DREDUCED_PRECISION"
reduced_precision: statula

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
