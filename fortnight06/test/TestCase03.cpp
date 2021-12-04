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
#include "TestCase.h"

#include <iostream>

#include "BasicMemory.h"

using namespace std;

int TestCase03::run() {
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test03(cpu, memory, TEST_FILE_03);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}

/**
 * Testa as instruções de load e store e instruções de branch do
 * arquivo isummation.S.
 */
void TestCase03::test03(BasicCPUTest* cpu, MemoryTest* memory, string fname)
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
