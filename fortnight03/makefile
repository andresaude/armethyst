CC=g++

IDIR=./include
CFLAGS=-std=c++14 -I$(IDIR) 

ODIR=obj

all: armethyst test

#
# armethyst
#
_DEPS = BasicCPU.h BasicProcessor.h config.h CPU.h Memory.h Processor.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = BasicCPU.o BasicProcessor.o Memory.o

_MAINOBJ = armethyst.o $(_OBJ)
MAINOBJ = $(patsubst %,$(ODIR)/%,$(_MAINOBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

armethyst: $(MAINOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#
# test
#
_TESTDEPS = $(_DEPS) BasicCPUTest.h
TESTDEPS = $(patsubst %,$(IDIR)/%,$(_TESTDEPS))

_TESTOBJ = test.o BasicCPUTest.o $(_OBJ)
TESTOBJ = $(patsubst %,$(ODIR)/%,$(_TESTOBJ))

test: $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#
# clean
#
clean:
	rm -f armethyst test *.exe
	rm -f $(ODIR)/*.o
