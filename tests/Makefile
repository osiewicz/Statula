IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
VPATH=../src

ODIR=obj
LDI =../lib

LIBS=-lm -lcriterion

_DEPS = basic_operations.h medium_operations.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = basic_operations.o medium_operations.o basic_operations_tests.o medium_operations_tests.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statula_tests: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
