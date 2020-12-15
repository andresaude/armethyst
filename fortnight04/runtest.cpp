/* ----------------------------------------------------------------------------

    (EN) armethyst - A simple ARM Simulator written in C++ for Computer Architecture
    teaching purposes. Free software licensed under the MIT License (see license
    below).

    (PT) armethyst - Um simulador ARM simples escrito em C++ para o ensino de
    Arquitetura de Computadores. Software livre licenciado pela MIT License
    (veja a licença, em inglês, abaixo).

    (EN) MIT LICENSE:

    Copyright 2020 André Vital Saúde

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

   ----------------------------------------------------------------------------
*/

#include "config.h"
#include "Util.h"

#include "BasicMemoryTest.h"
#include "BasicCPUTest.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define STARTSP 0x1000 // endereço inicial da pilha: 4096

/*
 * Macros
 */
#define CALLTEST() test(fpOp,instruction,cpu,memory,startAddress,startSP,xpctdIR,xpctdA,xpctdB,xpctdALUctrl,xpctdMEMctrl,xpctdWBctrl,xpctdALUout,xpctdMDR,xpctdRd)

#define RESETTEST()	fpOp=false;startAddress=-1;xpctdIR=-1;xpctdA=-1;xpctdB=-1;xpctdALUctrl=ALUctrlFlag::ALU_UNDEF;xpctdALUout=-1;xpctdMEMctrl=MEMctrlFlag::MEM_UNDEF;xpctdMDR=-1;xpctdWBctrl=WBctrlFlag::WB_UNDEF;xpctdRd=-1;cpu->resetFlags();memory->resetLastDataMemAccess();

void test01(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test02(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test03(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test04(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test05(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test06(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname);
void test(bool fpOp,
			string instruction,
			BasicCPUTest* cpu,
			BasicMemoryTest* memory,
			uint64_t startAddress,
			uint64_t startSP,
			uint32_t xpctdIR,
			uint64_t xpctdA,
			uint64_t xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl,
			uint64_t xpctdALUout,
			uint64_t xpctdMDR,
			uint64_t xpctdRd);

int main()
{
#define TEST_FILE_01 "isummation.o"
#define TEST_FILE_02 "fpops.o"
#define TEST_FILE_03 "isummation.o"
#define TEST_FILE_04 "fpops.o"

	// create memory
	BasicMemoryTest* memory = new BasicMemoryTest(MEMORY_SIZE);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	
	// Teste:
	//	Como não temos todas as instruções implementadas, faremos apenas testes.
	test01(cpu, memory, TEST_FILE_01);
	test02(cpu, memory, TEST_FILE_02);
	test03(cpu, memory, TEST_FILE_03);
	test04(cpu, memory, TEST_FILE_04);
	
	return 0;
}

void loadBinary (BasicMemoryTest* memory, string fname)
{
	// load executable binary
	memory->loadBinary(fname);
	memory->relocateManual();
	
	// create human readable representation of the binary file
	memory->writeBinaryAsText(fname);

	// create human readable representation of the binary file
	memory->writeBinaryAsTextELF(fname);
}

#define TEST_HEADER bool fpOp;\
		string instruction;\
		uint64_t startAddress;\
		uint64_t startSP = STARTSP;\
		uint32_t xpctdIR;\
		uint64_t xpctdA;\
		uint64_t xpctdB;\
		ALUctrlFlag xpctdALUctrl;\
		MEMctrlFlag xpctdMEMctrl;\
		WBctrlFlag xpctdWBctrl;\
		uint64_t xpctdALUout;\
		uint64_t xpctdMDR;\
		uint64_t xpctdRd;\
		RESETTEST();\
		loadBinary(memory,fname);\
		cout << "##################\n# " + fname + "\n##################\n\n\n";

/**
 * Testa as instruções 'sub sp, sp, #16' e 'add w1, w1, w0' do
 * arquivo isummation.S.
 */
void test01(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname)
{

	TEST_HEADER
	
	//
	// Test SUB
	//
	instruction = "sub sp, sp, #16";
	startAddress = 0x40; // endereço de 'sub sp, sp, #16'
	xpctdIR = 0xD10043FF;
	xpctdA = STARTSP; // SP deve ser lido para A
	xpctdB = 16; 	 // valor imediato da instrução sub
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA - xpctdB;
	
	xpctdRd = xpctdALUout;
	
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test ADD (linha 43)
	//
	instruction = "add w1, w1, w0";
	startAddress = 0x68; // endereço de 'add w1, w1, w0'
	xpctdIR = 0x0B000021;
	xpctdA = 7; 			// valor arbitrário para w1
	xpctdB = 16; 		// valor arbitrário para w0
	cpu->setW(1,xpctdA); // temos que fazer w1 valer xpctdA
	cpu->setW(0,xpctdB); // temos que fazer w0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = xpctdALUout;

	CALLTEST();
	RESETTEST();
}

/**
 * Testa as instruções fadd e fsub do arquivo fpops.S.
 */
void test02(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname)
{
	float fA = -0.7;
	float fB = 0.5;

	TEST_HEADER

	//
	// Test SUB
	//
	instruction = "sub sp, sp, #32";
	startAddress = 0x40; // endereço de 'sub sp, sp, #32'
	xpctdIR = 0xD10083FF;
	xpctdA = STARTSP; // SP deve ser lido para A
	xpctdB = 32; 	 // valor imediato da instrução sub
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA - xpctdB;
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test FSUB (linha 45)
	//
	fpOp = true;
	instruction = "fsub	s0, s1, s0";
	startAddress = 0x8C; // endereço de 'fsub	s0, s1, s0'
	xpctdIR = 0x1E203820;
	xpctdA = Util::floatAsUint64Low(fA);	// valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA-fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
		

	//
	// Test FADD (linha 58)
	//
	fpOp = true;
	instruction = "fadd s1, s1, s0";
	startAddress = 0xBC; // endereço de 'fadd	s1, s1, s0'
	xpctdIR = 0x1E202821;
	xpctdA = Util::floatAsUint64Low(fA);	// valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA+fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
}

/**
 * Testa as instruções de load e store e instruções de branch do
 * arquivo isummation.S.
 */
void test03(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname)
{
	TEST_HEADER
	
	int64_t signedAux;

	//
	// Test ldrsw x1, [sp, 12] (linha 38)
	//
	instruction = "ldrsw x1, [sp, 12]";
	startAddress = 0x54; 	// endereço de 'ldrsw x1, [sp, 12]'
	xpctdIR = 0xB9800FE1;
	xpctdA = STARTSP; 		// SP deve ser lido para A
	xpctdB = 12;			// valor imediato do offset
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ64;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 2;
	memory->writeData64(xpctdALUout, STARTSP << 2);

	CALLTEST();
	RESETTEST();
	
	
	//
	// Test ldr w0, [sp, 12] (linha 51)
	//
	instruction = "ldr w0, [sp, 12]";
	startAddress = 0x84; 	// endereço da linha
	xpctdIR = 0xB9400FE0;
	xpctdA = STARTSP; 		// SP deve ser lido para A
	xpctdB = 12;			// valor imediato do offset
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 2;
	memory->writeData32(xpctdALUout, STARTSP << 2);

	CALLTEST();
	RESETTEST();



	//
	// Test ldr w0, [x0] (linha 42)
	//
	instruction = "ldr w0, [x0]";
	startAddress = 0x64; 	// endereço da linha
	xpctdIR = 0xB9400000;	
	xpctdA = 0x800; 		// valor arbitrário para x0
	xpctdB = 0;
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP << 3;
	memory->writeData32(xpctdALUout, STARTSP << 3);

	CALLTEST();
	RESETTEST();




	//
	// Test str w1, [x0] (linha 46)
	//
	instruction = "str w1, [x0]";
	startAddress = 0x74; 	// endereço da instrução
	xpctdIR = 0xB9000001;
	xpctdA = 0x800; 		// valor arbitrário para x0
	xpctdB = 0;
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	cpu->setW(1,0x77);		// valor arbitrário para w1
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::WRITE32;
	xpctdWBctrl = WBctrlFlag::WB_NONE;
	
	xpctdALUout = xpctdA + xpctdB;

	// force arbitrary data in memory different from xpctdRd
	xpctdRd = 0x77;	
	memory->writeData32(xpctdALUout, 0x54321);

	CALLTEST();
	RESETTEST();


	//
	// Test str w0, [sp, 12] (linha 49)
	//
	instruction = "str w0, [sp, 12]";
	startAddress = 0x80; 	// endereço da instrução
	xpctdIR = 0xB9000FE0;
	xpctdA = STARTSP;
	xpctdB = 12;
	cpu->setW(0,0x12345);		// valor arbitrário para w1
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::WRITE32;
	xpctdWBctrl = WBctrlFlag::WB_NONE;

	xpctdALUout = xpctdA + xpctdB;

	// force arbitrary data in memory different from xpctdRd
	xpctdRd = 0x12345;	
	memory->writeData32(xpctdALUout, 0x54321);

	CALLTEST();
	RESETTEST();


	
	//
	// Test ldr w1, [x0, x1, lsl 2] (linha 39)
	//
	instruction = "ldr w1, [x0, x1, lsl 2]";
	startAddress = 0x58; 	// endereço da linha
	xpctdIR = 0xB8617801;
	xpctdA = 0x800; 		// valor arbitrário para x0
	cpu->setX(0,xpctdA);	// temos que fazer x0 valer xpctdA
	xpctdB = 0x7; 			// valor arbitrário para x1
	cpu->setX(1,xpctdB);	// temos que fazer x1 valer xpctdB
	xpctdB = xpctdB << 2; 	// aplicando lsl 2
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::READ32;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = xpctdA + xpctdB;

	// force data in memory
	xpctdRd = STARTSP >> 2;
	memory->writeData32(xpctdALUout, STARTSP >> 2);

	CALLTEST();
	RESETTEST();


	//
	// Test str wzr, [sp, 12] (linha 33)
	//
	instruction = "str wzr, [sp, 12]";
	startAddress = 0x44; 	// endereço da instrução
	xpctdIR = 0xB9000FFF;
	xpctdA = STARTSP; 
	xpctdB = 12;
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::WRITE32;
	xpctdWBctrl = WBctrlFlag::WB_NONE;

	xpctdALUout = xpctdA + xpctdB;
	
	// force arbitrary data in memory different from xpctdRd
	xpctdRd = 0;	
	memory->writeData32(xpctdALUout, 0x12345);

	CALLTEST();
	RESETTEST();


	//
	// Test b .L2 (linha 34)
	//
	instruction = "b .L2";
	startAddress = 0x48; 	// endereço da instrução
	xpctdIR = 0x1400000F;
	xpctdA = startAddress; 		// valor arbitrário para x0
	xpctdB = 60;
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;

	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = 0x84;

	CALLTEST();
	RESETTEST();

	//
	// Test b .L2 (linha 34)  (alterado, com offset < 0)
	//
	instruction = "b .L2 (alterado, com offset < 0)";
	startAddress = 0x48; 	// endereço da instrução
	xpctdIR = 0x17FFFFFF;  // deslocamento de -4
	memory->writeInstruction32(startAddress, xpctdIR);
	memory->resetLastDataMemAccess();
	xpctdA = startAddress; 		// valor arbitrário para x0
	signedAux = -4;
	xpctdB = signedAux;
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;

	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = 0x44;

	CALLTEST();
	RESETTEST();
	
	
	//
	// Test CMP
	//
	instruction = "cmp w0, 9";
	startAddress = 0x88; // endereço da instrução
	xpctdIR = 0x7100241F;
	xpctdA = 7; 	// valor 7 < 9, para que o branch de BLE seja tomado
	cpu->setW(0,xpctdA);	// temos que fazer w0 valer xpctdA
	xpctdB = 9; 	 // valor imediato da instrução
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::WB_NONE;
	
	xpctdALUout = xpctdA - xpctdB;
	
	CALLTEST();
	RESETTEST();

	//
	// Test ble .L3 (linha 53)
	//
	instruction = "ble .L3";
	startAddress = 0x8C; 	// endereço da instrução
	xpctdIR = 0x54FFFE0D;
	xpctdA = startAddress; 		// valor arbitrário para x0
	signedAux = -64;
	xpctdB = signedAux;
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;

	xpctdALUout = xpctdA + xpctdB;

	xpctdRd = 0x4C;

	CALLTEST();
	RESETTEST();


	//
	// Test ret (linha 56)
	// Implementado como PC <- Xn + 0
	//
	instruction = "ret";
	startAddress = 0x98; 	// endereço da instrução
	xpctdIR = 0xD65F03C0;
	xpctdA = 0x40; 		    // valor arbitrário para x30
	cpu->setX(30,xpctdA);	// temos que fazer x30 valer xpctdA
	xpctdB = 0;
	xpctdALUctrl = ALUctrlFlag::ADD;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;

	xpctdALUout = 0x40;

	xpctdRd = 0x40;

	CALLTEST();
	RESETTEST();
	
}

/**
 * Testa as instruções aritméticas de float de fpops.S.
 */
void test04(BasicCPUTest* cpu, BasicMemoryTest* memory, string fname)
{
	TEST_HEADER
	
	float fA = -0.7;
	float fB = 0.5;

	//
	// Test fneg s1, s0 (linha 40)
	// implementado como s1 = 0 - s0
	//
	fpOp = true;
	instruction = "fneg s1, s0";
	startAddress = 0x78; // endereço da instrução
	xpctdIR = 0x1E214001;
	xpctdA = 0;
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::SUB;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(-fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
	
	
	//
	// Test fdiv s1, s1, s0 (linha 43)
	//
	fpOp = true;
	instruction = "fdiv s1, s1, s0";
	startAddress = 0x84; // endereço da instrução
	xpctdIR = 0x1E201821;
	xpctdA = Util::floatAsUint64Low(fA); // valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::DIV;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA/fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();
	
	//
	// Test fmul s1, s1, s0 (linha 52)
	//
	fpOp = true;
	instruction = "fmul s1, s1, s0";
	startAddress = 0xA4; // endereço da instrução
	xpctdIR = 0x1E200821;
	xpctdA = Util::floatAsUint64Low(fA); // valor arbitrário para s1
	xpctdB = Util::floatAsUint64Low(fB); // valor arbitrário para s0
	cpu->setS(1,fA); // temos que fazer s1 valer xpctdA
	cpu->setS(0,fB); // temos que fazer s0 valer xpctdB
	xpctdALUctrl = ALUctrlFlag::MUL;
	xpctdMEMctrl = MEMctrlFlag::MEM_NONE;
	xpctdWBctrl = WBctrlFlag::RegWrite;
	
	xpctdALUout = Util::floatAsUint64Low(fA*fB);
	
	xpctdRd = xpctdALUout;
	
	CALLTEST();
	RESETTEST();

}


/**
 * Testa o estágio IF.
 */
void testIF(BasicCPUTest* cpu, uint32_t xpctdIR)
{
	//
	// Testa IF
	//
	cout << "Testing IF..." << endl;
	
	// executa
	cpu->runIF();
	cout << "	IR=0x" << cpu->getIR()
			<< ";  Expected IR=0x" << xpctdIR << endl;
	
	// verifica
	if (cpu->getIR() != xpctdIR) {
		cout << "IF() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	cout << "IF() SUCCESS!" << endl << endl;
}

/**
 * Testa o estágio ID.
 */
void testID(BasicCPUTest* cpu,
			uint32_t xpctdIR,
			uint64_t xpctdA,
			uint64_t xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl)
{
	//
	// Testa ID (depende do sucesso no teste de IF)
	//
	cout << "Testing ID..." << endl;
	
	// executa
	int iderror = cpu->runID();
	
	// verifica se a instrução está implementada
	if (iderror) {
		cout << "Instruction not implemented: 0x" << xpctdIR << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	// verifica leitura de registradores
	cout << "ID() testing registers reading..." << endl << endl;
	uint64_t A = cpu->getA();
	uint64_t B = cpu->getB();
	cout << "	A=0x" << setw(16) << A << "; B=0x" << setw(16) << B << endl;
	cout << "Expected: A=0x" << setw(16) << xpctdA << "; B=0x" << setw(16) << xpctdB << endl;
	if ((A != xpctdA) || (B != xpctdB)){
		cout << "ID() FAILED on registers reading!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}

	cout << "ID() succeeded on registers reading!" << endl << endl;

	if (TEST_LEVEL > TEST_LEVEL_ID)
	{

		cout << "ID() testing ALU control set..." << endl << endl;
		
		// verifica ALUctrl
		ALUctrlFlag ALUctrl = cpu->getALUctrl();
		cout << "	ALUctrl=0x" << ALUctrl << "; Expected ALUctrl=0x"
				<< xpctdALUctrl << endl;
		if (ALUctrl != xpctdALUctrl)
		{
			cout << "ID() FAILED on ALU control set!" << endl;
			cout << "Exit..." << endl;
			exit(1);
		}

		cout << "ID() succeeded on ALU control set!" << endl << endl;

		if (TEST_LEVEL > TEST_LEVEL_EX)
		{
			cout << "ID() testing MEM control set..." << endl << endl;
		
			// verifica MEMctrl
			MEMctrlFlag MEMctrl = cpu->getMEMctrl();
			cout << "	MEMctrl=0x" << MEMctrl << "; Expected MEMctrl=0x"
					<< xpctdMEMctrl << endl;
			if (MEMctrl != xpctdMEMctrl)
			{
				cout << "ID() FAILED on MEM control set!" << endl;
				cout << "Exit..." << endl;
				exit(1);
			}

			cout << "ID() succeeded on MEM control set!" << endl << endl;

			if (TEST_LEVEL > TEST_LEVEL_MEM)
			{
				cout << "ID() testing WB control set..." << endl << endl;

				// verifica WBctrl
				WBctrlFlag WBctrl = cpu->getWBctrl();
				cout << "	WBctrl=0x" << WBctrl << "; Expected WBctrl=0x"
						<< xpctdWBctrl << endl;
				if (WBctrl != xpctdWBctrl)
				{
					cout << "ID() FAILED on WB control set!" << endl;
					cout << "Exit..." << endl;
					exit(1);
				}

				cout << "ID() succeeded on WB control set!" << endl << endl;
			}
		}
	}

	cout << "ID() SUCCESS!" << endl << endl;
}

/**
 * Testa o estágio EX.
 */
void testEX(BasicCPUTest* cpu, bool fpOp, uint64_t xpctdALUout)
{
	//
	// Testa EXI (depende do sucesso no teste de ID)
	//
	cout << "Testing EX..." << endl;
	
	// executa
	int exerror;
	if (fpOp) {
		cout << "\tfloat: testing EXF..." << endl;
		exerror = cpu->runEXF();
	} else {
		cout << "\tinteger: testing EXI..." << endl;
		exerror = cpu->runEXI();
	}
	if (exerror) {
		cout << "Control not implemented: 0x" << cpu->getALUctrl() << endl;
		cout << "EX() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	// verifica ALUout
	uint64_t ALUout = cpu->getALUout();
	cout << "	ALUout=0x"
			<< setfill('0') << setw(16) << ALUout
			<< "; Expected ALUout=0x"
			<< setfill('0') << setw(16) << xpctdALUout << endl;
	if (ALUout != xpctdALUout)
	{
		cout << "EX() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	cout << "EX() SUCCESS!" << endl;
}

/**
 * Testa o estágio MEM - NAO IMPLEMENTADO.
 */
void testMEM(BasicCPUTest* cpu,
				BasicMemoryTest* memory,
				MEMctrlFlag xpctdMEMctrl,
				uint64_t xpctdALUout,
				uint64_t xpctdRd)
{
	//
	// Test MEM (depends on the success of previous stages)
	//
	cout << "Testing MEM..." << endl;
	
	// executa
	int memerror = cpu->runMEM();
	if (memerror) {
		cout << "Control not implemented: 0x" << cpu->getMEMctrl() << endl;
		cout << "MEM() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
		
	//
	// Test access type
	//
	
	// map MEMctrlFlag to BasicMemoryTest::MemAccessType
	BasicMemoryTest::MemAccessType xpctdLastDataMemAccess;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::MEM_NONE:
			xpctdLastDataMemAccess = BasicMemoryTest::MemAccessType::MAT_NONE;
			break;
		case MEMctrlFlag::READ32:
			xpctdLastDataMemAccess = BasicMemoryTest::MemAccessType::MAT_READ32;
			break;
		case MEMctrlFlag::READ64:
			xpctdLastDataMemAccess = BasicMemoryTest::MemAccessType::MAT_READ64;
			break;
		case MEMctrlFlag::WRITE32:
			xpctdLastDataMemAccess = BasicMemoryTest::MemAccessType::MAT_WRITE32;
			break;
		case MEMctrlFlag::WRITE64:
			xpctdLastDataMemAccess = BasicMemoryTest::MemAccessType::MAT_WRITE64;
			break;
	}

	BasicMemoryTest::MemAccessType lastDataMemAccess =
			memory->getLastDataMemAccess();
	cout << "	Testing MEM access type..." << endl;
	cout << "		Expected access type: "
			<< xpctdLastDataMemAccess << endl;
	cout << "		Executed access type: "
			<< lastDataMemAccess << endl;
	if (xpctdLastDataMemAccess != lastDataMemAccess) {
		// incorrect memory access type
		cout << "MEM() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	} else {
		cout << "	MEM() executed the correct access type!" << endl;
	}

	//
	// Test content
	//
	
	// no memory access -> success
	if (xpctdMEMctrl == MEMctrlFlag::MEM_NONE) {
		cout << "	No content to be tested!" << endl;
		cout << "MEM() test: SUCCESS!" << endl;
		return;
	}
	
	// get read or written content (access depends on 32 or 64 bit mode)
	uint64_t memData, xpctdMemData;
	switch (xpctdMEMctrl) {
		case MEMctrlFlag::READ32:
			cout << "	READ Mode: testing read content..." << endl;
			memData = (uint64_t)memory->readData32(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::READ64:
			cout << "	READ Mode: testing read content..." << endl;
			memData = memory->readData64(xpctdALUout);
			xpctdMemData = cpu->getMDR();
			break;
		case MEMctrlFlag::WRITE32:
			cout << "	WRITE Mode: testing written content..." << endl;
			memData = (uint64_t)memory->readData32(xpctdALUout);
			xpctdMemData = xpctdRd;//cpu->getRd();
			break;
		case MEMctrlFlag::WRITE64:
			cout << "	WRITE Mode: testing written content..." << endl;
			memData = memory->readData64(xpctdALUout);
			xpctdMemData = cpu->getRd();
			break;
	}
	
	// memory content verbose
	cout << "		Expected memory content: 0x"	<< xpctdMemData << endl;
	cout << "		Effective memory content: 0x"	<< memData << endl;
	cout << "		Address tested: 0x" << xpctdALUout << endl;

	// finish content test
	if (memData == xpctdMemData) {
		cout << "	Memory content OK..." << endl;
		cout << "MEM() test: SUCCESS!" << endl;
		return;
	}
	
	// otherwise
	cout << "	Memory content FAILED..." << endl;
	cout << "MEM() FAILED!" << endl;
	exit(1);
}

/**
 * Testa o estágio WB.
 */
void testWB(BasicCPUTest* cpu,
		WBctrlFlag xpctdWBctrl,
		uint64_t xpctdRd)
{
	//
	// Testa WB (depende do sucesso nos testes de estágios anteriores)
	//
	cout << "Testing WB..." << endl;
	
	// executa
	int wberror = cpu->runWB();
	if (wberror) {
		cout << "Control not implemented: 0x" << cpu->getWBctrl() << endl;
		cout << "WB() FAILED!" << endl;
		cout << "Exit..." << endl;
		exit(1);
	}
	
	bool ok = true;
	uint64_t Rd = cpu->getRd();
	if(xpctdWBctrl == WBctrlFlag::RegWrite)
	{
		cout << "	Rd=0x"
			<< setfill('0') << setw(8) << Rd
			<< "; Expected xpctdRd=0x"
			<< setfill('0') << setw(8) << xpctdRd << endl;
			
		if (Rd != xpctdRd)
		{
			cout << "WB() FAILED!" << endl;
			cout << "Exit..." << endl;
			exit(1);
		}
	}
	
	cout << "WB() SUCCESS!" << endl;
}

/**
 * Testa o estágio IF e testa parcialmente os estágios ID e EXI, somente
 * para a instrução 'sub sp, sp, #16'.
 */
void test(bool fpOp,
			string instruction,
			BasicCPUTest* cpu,
			BasicMemoryTest* memory,
			uint64_t startAddress,
			uint64_t startSP,
			uint32_t xpctdIR,
			uint64_t xpctdA,
			uint64_t xpctdB,
			ALUctrlFlag xpctdALUctrl,
			MEMctrlFlag xpctdMEMctrl,
			WBctrlFlag xpctdWBctrl,
			uint64_t xpctdALUout,
			uint64_t xpctdMDR,
			uint64_t xpctdRd)
{
	cout << "#\n#\n#\n# Testing '" << instruction << "'...\n#\n#\n#\n" << endl;

	cout << "\n\nTEST_LEVEL: Starting processor...\n\n" << endl;
	
	// saídas em hexadecimal
	cout << hex;
	
	cout << "Starting processor..." << endl;
	cout << "	PC: 0x" << startAddress << endl;
	cout << "	SP: 0x" << startSP << endl;
	cpu->run(startAddress);
	cpu->setSP(startSP);
	cout << "processor started!." << endl << endl;

	if (TEST_LEVEL > TEST_LEVEL_START)
	{
		cout << "\n\nTEST_LEVEL: IF\n\n" << endl;
		testIF(cpu, xpctdIR);
		
		if (TEST_LEVEL > TEST_LEVEL_IF)
		{
			cout << "\n\nTEST_LEVEL: ID\n\n" << endl;
			testID(cpu, xpctdIR, xpctdA, xpctdB, xpctdALUctrl,
					xpctdMEMctrl, xpctdWBctrl);

			if (TEST_LEVEL > TEST_LEVEL_ID)
			{
				cout << "\n\nTEST_LEVEL: EX\n\n" << endl;
				testEX(cpu, fpOp, xpctdALUout);

				if (TEST_LEVEL > TEST_LEVEL_EX)
				{
					cout << "\n\nTEST_LEVEL: MEM\n\n" << endl;
					testMEM(cpu, memory, xpctdMEMctrl,
							xpctdALUout, xpctdRd);
					if (TEST_LEVEL > TEST_LEVEL_MEM)
					{
						cout << "\n\nTEST_LEVEL: WB\n\n" << endl;
						testWB(cpu, xpctdWBctrl, xpctdRd);
					}
				}
			}
		}
	}
	cout << "SUCCESS!" << endl;
	
	cout << "End '" << instruction << "'." << endl << endl << endl;
	
}

