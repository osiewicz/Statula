IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -coverage
VPATH=../src

ODIR=../tests/obj
LDI =../lib

LIBS=-lm -lcriterion

_DEPS = operations.h dataset.h io.h misc.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = operations.o dataset.o io.o misc.o tests.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -DSTATULA_TESTS $< $(CFLAGS) -c -o $@ 
statula_tests: $(OBJ)
	$(CC) -DSTATULA_TESTS $^ $(CFLAGS) $(LIBS) -o $@ 
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
