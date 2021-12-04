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

int TestCase05::run() {
	// create memory
	BasicMemory* basicmemory = new BasicMemory(MEMORY_SIZE);
	MemoryTest* memory = new MemoryTest(basicmemory);

	// create CPU
	BasicCPUTest *cpu = new BasicCPUTest(memory);
	test05(cpu, memory, TEST_FILE_05);
	
	delete memory;
	delete basicmemory;
	
	return 0;
}

/**
 * Testa apenas duas instruções de load e store do arquivo isummation.S.
 */
void TestCase05::test05(BasicCPUTest* cpu, MemoryTest* memory, string fname)
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
}
