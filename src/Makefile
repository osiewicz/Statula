IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDI =../lib

LIBS=-lm

_DEPS = basic_operations.h medium_operations.h strings.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = statula.o basic_operations.o medium_operations.o strings.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statula: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
