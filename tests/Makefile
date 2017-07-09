IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -std=gnu11
VPATH=../src

ODIR=obj
LDI =../lib

LIBS=-lm -lcriterion

_DEPS = operations.h io.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tests.o operations.o dataset.o io.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statula_tests: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
