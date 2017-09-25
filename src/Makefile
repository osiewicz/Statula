IDIR =../include
CC=gcc
CFLAGS= -g -I$(IDIR) -O3 -std=c99 

ODIR=obj
LDI =../lib

LIBS=-lm 

_DEPS = operations.h io.h misc.h dataset.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = misc.o io.o dataset.o operations.o statula.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) $< $(CFLAGS) -c -o $@ 

statula: $(OBJ)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@
.PHONY: clean reduced_precision

reduced_precision: clean
reduced_precision: CFLAGS+="-DREDUCED_PRECISION"
reduced_precision: statula

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
