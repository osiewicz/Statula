IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99
VPATH=../src

ODIR=../tests/obj
LDI =../lib

LIBS=-lm -lcriterion

_DEPS = operations.h io.h dataset.h misc.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = operations.o dataset.o io.o misc.o tests.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -DTEST $< $(CFLAGS) -c -o $@ 
statula_tests: $(OBJ)
	$(CC) -DTEST $^ $(CFLAGS) $(LIBS) -o $@ 
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
