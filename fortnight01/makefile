CC=g++

IDIR=./include
CFLAGS=-std=c++14 -I$(IDIR). 

ODIR=obj

_DEPS = Memory.h Processor.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = armethyst.o Memory.o Processor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

armethyst: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
