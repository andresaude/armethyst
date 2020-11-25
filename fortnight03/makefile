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
IFLAGS=-I./$(IDIR) -I./util/$(IDIR) -I$(PROC_IDIR) -I$(CPU_IDIR) -I$(MEM_IDIR)

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
# Memory config (selecionar a implementação de Memória desejada)
#	Memórias disponíveis:
#		- BasicMemory - A single Von Neumann memory.
#		- OutraMemoria: se houver outra implementação de Memória
#
MemImpl=BasicMemory
MemImplDir=basicmemory

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
MEM_DIR=./memory/$(MemImplDir)
MEM_IDIR=$(MEM_DIR)/$(IDIR)
MEM_DEPS = $(MEM_IDIR)/$(MemImpl).h
MEM_CFILES = $(MEM_DIR)/$(MemImpl).cpp
$(ODIR)/MemImpl.o: $(MEM_CFILES) $(MEM_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)


#
# general
#
_OBJ = CPUImpl.o ProcessorImpl.o MemImpl.o Factory.o Util.o
$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

#
# armethyst
#
_DEPS = config.h CPU.h Memory.h Processor.h Factory.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_MAINOBJ = armethyst.o $(_OBJ)
MAINOBJ = $(patsubst %,$(ODIR)/%,$(_MAINOBJ))

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
MEM_TEST_CFILES = $(MEM_DIR)/$(TEST_DIR)/$(MemImpl)Test.cpp
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
