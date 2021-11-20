all: armethyst runtest

testcmd:
	$(CC) $(CFLAGS) -o runtest runtest.cpp Memory.cpp $(TEST_DIR)/MemoryTest.cpp $(IFLAGS) $(TEST_IFLAGS) $(PROC_CFILES) $(CPU_CFILES) $(CPU_TEST_CFILES) 

#
# global
#
CC=g++
CFLAGS=-std=c++14

IDIR=include
ODIR=./obj

# ###################
# # armethyst
# ###################
IFLAGS=-I./$(IDIR) -I./util/$(IDIR) -I$(PROC_IDIR) -I$(CPU_IDIR) $(MEM_IFLAGS)

#
# Processor config (selecionar a implementação de Processador desejada)
#	Processadores disponíveis:
#		- BasicProcessor - A single core processor with a BasicCPU.
#		- OutroProcessador: se houver outra implementação de Processor
#
ProcImpl=BasicProcessor
ProcImplDir=basicprocessor

#
# CPU config (selecionar a implementação de CPU desejada)
#	CPUs disponíveis:
#		- BasicCPU: a basic CPU with the following characteristics:
#			- AArch64 ISA (limited), from ARMv8
#			- MIPS datapath
#		- OutraCPU: se houver outra implementação de CPU
#
CPUImpl=BasicCPU
CPUImplDir=basiccpu

#
# Factory
#
# fábrica de componentes.
$(ODIR)/Factory.o: factory/Factory.cpp $(IDIR)/Factory.h $(IDIR)/config.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

$(ODIR)/Util.o: util/Util.cpp util/$(IDIR)/Util.h $(IDIR)/config.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

#
# Processor
#
PROC_DIR=./processor/$(ProcImplDir)
PROC_IDIR=$(PROC_DIR)/$(IDIR)
PROC_DEPS = $(PROC_IDIR)/$(ProcImpl).h
PROC_CFILES = $(PROC_DIR)/$(ProcImpl).cpp
$(ODIR)/ProcessorImpl.o: $(PROC_CFILES) $(PROC_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)


#
# CPU
#
CPU_DIR=./cpu/$(CPUImplDir)
CPU_IDIR=$(CPU_DIR)/$(IDIR)
CPU_DEPS = $(CPU_IDIR)/$(CPUImpl).h
CPU_CFILES = $(CPU_DIR)/$(CPUImpl).cpp
$(ODIR)/CPUImpl.o: $(CPU_CFILES) $(CPU_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)


#
# Memory
#
MEM_DIR=./memory
MEM_IDIRS=$(IDIR):$(MEM_DIR)/$(IDIR):$(MEM_DIR)/cache/$(IDIR)
MEM_IFLAGS = $(patsubst %,-I%,$(subst :, ,$(MEM_IDIRS)))
MEM_CPPS=Cache.cpp FACache.cpp
MEM_PARTS=Cache FACache SACache
MEM_OBJS=$(patsubst %,$(ODIR)/%.o,$(MEM_PARTS))
MEM_CPP=$(patsubst %,%.cpp,$(MEM_PARTS))
MEM_H=$(patsubst %,%.h,$(MEM_PARTS))
vpath %.cpp $(MEM_DIR):$(MEM_DIR)/cache
vpath %.h $(MEM_IDIRS)

$(ODIR)/Cache.o: Cache.cpp Cache.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) 

$(ODIR)/FACache.o: FACache.cpp FACache.h $(ODIR)/Cache.o
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) 

$(ODIR)/SACache.o: SACache.cpp SACache.h $(ODIR)/Cache.o
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) 
	
$(ODIR)/BasicMemory.o: BasicMemory.cpp BasicMemory.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) 

$(ODIR)/Corei7Memory.o: Corei7Memory.cpp Corei7Memory.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

$(ODIR)/MemoryLoader.o: MemoryLoader.cpp MemoryLoader.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

$(ODIR)/MemoryLogger.o: MemoryLogger.cpp MemoryLogger.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

#
# general
#
_OBJ = BasicMemory.o Corei7Memory.o MemoryLoader.o MemoryLogger.o CPUImpl.o ProcessorImpl.o Factory.o Util.o

#
# armethyst
#
_DEPS = config.h CPU.h Memory.h Processor.h Factory.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_MAINOBJ = armethyst.o $(_OBJ)
MAINOBJ = $(MEM_OBJS) $(patsubst %,$(ODIR)/%,$(_MAINOBJ))

$(ODIR)/armethyst.o: armethyst.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

armethyst: $(MAINOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(IFLAGS)

###################
# armethyst test
###################

TEST_DIR=./test
TEST_IDIR=$(TEST_DIR)/$(IDIR)
TEST_IFLAGS=$(IFLAGS) -I./$(TEST_IDIR) -I$(CPU_DIR)/$(TEST_IDIR) -I$(MEM_DIR)/$(TEST_IDIR)

#
# Memory test
#
MEM_TEST_CFILES = $(MEM_DIR)/$(TEST_DIR)/MemoryTest.cpp
$(ODIR)/MemoryTest.o: $(MEM_TEST_CFILES) $(MEM_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(TEST_IFLAGS)

#
# CPU test
#
CPU_TEST_CFILES = $(CPU_DIR)/$(TEST_DIR)/$(CPUImpl)Test.cpp
$(ODIR)/CPUTest.o: $(CPU_TEST_CFILES) $(CPU_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(TEST_IFLAGS)

#
# test
#

_TESTOBJ = $(_OBJ) runtest.o CPUTest.o MemoryTest.o 
TESTOBJ = $(patsubst %,$(ODIR)/%,$(_TESTOBJ))

$(ODIR)/runtest.o: runtest.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(TEST_IFLAGS)

runtest: $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TEST_IFLAGS)

#
# clean
#
clean:
	rm -f armethyst runtest *.exe
	rm -f *.o.txt saida.txt
	rm -f $(ODIR)/*.o
